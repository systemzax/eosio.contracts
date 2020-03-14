#include <eosio.system/eosio.system.hpp>
#include <eosio.token/eosio.token.hpp>

#include <cmath>

namespace eosiosystem {

   using eosio::current_time_point;
   using eosio::microseconds;
   using eosio::token;

   void system_contract::onblock( ignore<block_header> ) {
      using namespace eosio;

      require_auth(get_self());

      block_timestamp timestamp;
      name producer;
      _ds >> timestamp >> producer;

      // _gstate2.last_block_num is not used anywhere in the system contract code anymore.
      // Although this field is deprecated, we will continue updating it for now until the last_block_num field
      // is eventually completely removed, at which point this line can be removed.
      _gstate2.last_block_num = timestamp;

      /** until activation, no new rewards are paid */
      if( _gstate.thresh_activated_stake_time == time_point() )
         return;

      if( _gstate.last_pervote_bucket_fill == time_point() )  /// start the presses
         _gstate.last_pervote_bucket_fill = current_time_point();


      /**
       * At startup the initial producer may not be one that is registered / elected
       * and therefore there may be no producer object for them.
       */
      auto prod = _producers.find( producer.value );
      if ( prod != _producers.end() ) {
         _gstate.total_unpaid_blocks++;
         _producers.modify( prod, same_payer, [&](auto& p ) {
               p.unpaid_blocks++;
         });
      }

      /// only update block producers once every minute, block_timestamp is in half seconds
      if( timestamp.slot - _gstate.last_producer_schedule_update.slot > 120 ) {
         update_elected_producers( timestamp );

         if( (timestamp.slot - _gstate.last_name_close.slot) > blocks_per_day ) {
            name_bid_table bids(get_self(), get_self().value);
            auto idx = bids.get_index<"highbid"_n>();
            auto highest = idx.lower_bound( std::numeric_limits<uint64_t>::max()/2 );
            if( highest != idx.end() &&
                highest->high_bid > 0 &&
                (current_time_point() - highest->last_bid_time) > microseconds(useconds_per_day) &&
                _gstate.thresh_activated_stake_time > time_point() &&
                (current_time_point() - _gstate.thresh_activated_stake_time) > microseconds(14 * useconds_per_day)
            ) {
               _gstate.last_name_close = timestamp;
               channel_namebid_to_rex( highest->high_bid );
               idx.modify( highest, same_payer, [&]( auto& b ){
                  b.high_bid = -b.high_bid;
               });
            }
         }
      }
   }

   void system_contract::claim( const name& owner ){ 

     //no auth check needed

      token::reserves rtable( get_self(), owner.value );
      auto itr = rtable.find( ore_symbol.raw()  );
      check( itr != rtable.end(), "no reserve found for account");

      token::stakestats stable( get_self(), ore_symbol.raw()  );

      auto st = stable.find( ore_symbol.raw()  );

      check(st != stable.end(), "no ORE token stats found");

     const auto ct = current_time_point();
     check( ct - itr->last_claimed > microseconds(useconds_per_week), "already claimed rewards within past week" );

     asset staked = eosio::token::get_staked("eosio.token"_n, owner, ore_symbol.code());
     asset total_staked = token::get_total_staked("eosio.token"_n, ore_symbol.code());
     asset pool_rewards = eosio::token::get_balance("eosio.token"_n, upay_account, ore_symbol.code());

     check(staked.amount>0, "cannot claim rewards without tokens staked");
     
     float reward_share = staked.amount / total_staked.amount;
     float reward_amount = reward_share * pool_rewards.amount;

     check( reward_amount > 0, "no rewards to claim" );

     asset rewards = asset{(int64_t)reward_amount, ore_symbol};

     rtable.modify( itr, same_payer, [&]( auto& a ) {
       a.last_claimed = current_time_point();
     });

     token::transfer_action transfer_act{ token_account, {  {upay_account, active_permission}, {owner, active_permission}} };
     transfer_act.send( upay_account, owner, rewards, "staking rewards" );

   }

   void system_contract::claimrewards( const name& owner ) {
      require_auth( owner );

      const auto& prod = _producers.get( owner.value );
      check( prod.active(), "producer does not have an active key" );

      check( _gstate.thresh_activated_stake_time != time_point(),
                    "cannot claim rewards until the chain is activated (at least 15% of all tokens participate in voting)" );

      const auto ct = current_time_point();

      check( ct - prod.last_claim_time > microseconds(useconds_per_day), "already claimed rewards within past day" );

      const asset token_supply   = token::get_supply(token_account, core_symbol().code() );
      const auto usecs_since_last_fill = (ct - _gstate.last_pervote_bucket_fill).count();

      if( usecs_since_last_fill > 0 && _gstate.last_pervote_bucket_fill > time_point() ) {
         double additional_inflation = (_gstate4.continuous_rate * double(token_supply.amount) * double(usecs_since_last_fill)) / double(useconds_per_year);
         check( additional_inflation <= double(std::numeric_limits<int64_t>::max() - ((1ll << 10) - 1)),
                "overflow in calculating new tokens to be issued; inflation rate is too high" );
         int64_t new_tokens = (additional_inflation < 0.0) ? 0 : static_cast<int64_t>(additional_inflation);

         int64_t to_producers     = (new_tokens * uint128_t(pay_factor_precision)) / _gstate4.inflation_pay_factor;
         int64_t to_users         = new_tokens - to_producers;
         int64_t to_per_block_pay = (to_producers * uint128_t(pay_factor_precision)) / _gstate4.votepay_factor;
         int64_t to_per_vote_pay  = to_producers - to_per_block_pay;

         if( new_tokens > 0 ) {
            {
               token::issue_action issue_act{ token_account, { {get_self(), active_permission} } };
               issue_act.send( get_self(), asset(new_tokens, core_symbol()), "issue tokens for producer pay and savings" );
               issue_act.send( get_self(), asset(new_tokens, symbol(symbol_code("ORE"), 4)), "ore issue tokens for producer pay and savings" );
            }
            {
               token::transfer_action transfer_act{ token_account, { {get_self(), active_permission} } };
               if( to_users > 0 ) {
                  transfer_act.send( get_self(), upay_account, asset(to_users, core_symbol()), "fund inflation rewards bucket" );
                  transfer_act.send( get_self(), upay_account, asset(to_users, symbol(symbol_code("ORE"), 4)), "fund inflation rewards bucket" );
               }
               if( to_per_block_pay > 0 ) {
                  transfer_act.send( get_self(), bpay_account, asset(to_per_block_pay, core_symbol()), "fund per-block bucket" );
                  transfer_act.send( get_self(), bpay_account, asset(to_per_block_pay, symbol(symbol_code("ORE"), 4)), "fund per-block bucket" );
               }
               if( to_per_vote_pay > 0 ) {
                  transfer_act.send( get_self(), vpay_account, asset(to_per_vote_pay, core_symbol()), "fund per-vote bucket" );
                  transfer_act.send( get_self(), vpay_account, asset(to_per_vote_pay, symbol(symbol_code("ORE"), 4)), "fund per-vote bucket" );
               }
            }
         }

         _gstate.pervote_bucket          += to_per_vote_pay;
         _gstate.perblock_bucket         += to_per_block_pay;
         _gstate.last_pervote_bucket_fill = ct;
      }

      auto prod2 = _producers2.find( owner.value );

      /// New metric to be used in pervote pay calculation. Instead of vote weight ratio, we combine vote weight and
      /// time duration the vote weight has been held into one metric.
      const auto last_claim_plus_3days = prod.last_claim_time + microseconds(3 * useconds_per_day);

      bool crossed_threshold       = (last_claim_plus_3days <= ct);
      bool updated_after_threshold = true;
      if ( prod2 != _producers2.end() ) {
         updated_after_threshold = (last_claim_plus_3days <= prod2->last_votepay_share_update);
      } else {
         prod2 = _producers2.emplace( owner, [&]( producer_info2& info  ) {
            info.owner                     = owner;
            info.last_votepay_share_update = ct;
         });
      }

      // Note: updated_after_threshold implies cross_threshold (except if claiming rewards when the producers2 table row did not exist).
      // The exception leads to updated_after_threshold to be treated as true regardless of whether the threshold was crossed.
      // This is okay because in this case the producer will not get paid anything either way.
      // In fact it is desired behavior because the producers votes need to be counted in the global total_producer_votepay_share for the first time.

      int64_t producer_per_block_pay = 0;
      if( _gstate.total_unpaid_blocks > 0 ) {
         producer_per_block_pay = (_gstate.perblock_bucket * prod.unpaid_blocks) / _gstate.total_unpaid_blocks;
      }

      double new_votepay_share = update_producer_votepay_share( prod2,
                                    ct,
                                    updated_after_threshold ? 0.0 : prod.total_votes,
                                    true // reset votepay_share to zero after updating
                                 );

      int64_t producer_per_vote_pay = 0;
      if( _gstate2.revision > 0 ) {
         double total_votepay_share = update_total_votepay_share( ct );
         if( total_votepay_share > 0 && !crossed_threshold ) {
            producer_per_vote_pay = int64_t((new_votepay_share * _gstate.pervote_bucket) / total_votepay_share);
            if( producer_per_vote_pay > _gstate.pervote_bucket )
               producer_per_vote_pay = _gstate.pervote_bucket;
         }
      } else {
         if( _gstate.total_producer_vote_weight > 0 ) {
            producer_per_vote_pay = int64_t((_gstate.pervote_bucket * prod.total_votes) / _gstate.total_producer_vote_weight);
         }
      }

      if( producer_per_vote_pay < min_pervote_daily_pay ) {
         producer_per_vote_pay = 0;
      }

      _gstate.pervote_bucket      -= producer_per_vote_pay;
      _gstate.perblock_bucket     -= producer_per_block_pay;
      _gstate.total_unpaid_blocks -= prod.unpaid_blocks;

      update_total_votepay_share( ct, -new_votepay_share, (updated_after_threshold ? prod.total_votes : 0.0) );

      _producers.modify( prod, same_payer, [&](auto& p) {
         p.last_claim_time = ct;
         p.unpaid_blocks   = 0;
      });

      if ( producer_per_block_pay > 0 ) {
         token::transfer_action transfer_act{ token_account, { {bpay_account, active_permission}, {owner, active_permission} } };
         token::transfer_action transfer_act_fund{ token_account, { {bpay_account, active_permission} , {funding_account, active_permission} } };
         transfer_act_fund.send( bpay_account, funding_account, asset(producer_per_block_pay, core_symbol()), "producer block pay" );
         transfer_act.send( bpay_account, owner, asset(producer_per_block_pay, symbol(symbol_code("ORE"), 4)), "producer block pay" );
      }
      if ( producer_per_vote_pay > 0 ) {
         token::transfer_action transfer_act{ token_account, { {vpay_account, active_permission}, {owner, active_permission} } };
         token::transfer_action transfer_act_fund{ token_account, { {vpay_account, active_permission} , {funding_account, active_permission} } };
         transfer_act_fund.send( vpay_account, funding_account, asset(producer_per_vote_pay, core_symbol()), "producer vote pay" );
         transfer_act.send( vpay_account, owner, asset(producer_per_vote_pay, symbol(symbol_code("ORE"), 4)), "producer vote pay" );
      }

      asset staked = token::get_total_staked("eosio.token"_n, symbol_code("ORE"));
      asset supply = token::get_supply("eosio.token"_n, symbol_code("ORE"));

      float current_usage_ratio = staked.amount / supply.amount;

      if (current_usage_ratio==0) return;

      float y = -current_usage_ratio*std::log1p(current_usage_ratio)*e_const;
      float v_tu = y * v_transfer;
      float i_u = (1-current_usage_ratio) / (1-current_usage_ratio-v_tu);
      float g_uy = i_u / current_usage_ratio;
      float b_pru = y*max_bp_rate;
      float u_pu = std::pow(1+g_uy, 1-b_pru)-1;

      float u_pay = std::max(i_u*current_usage_ratio, u_pu*current_usage_ratio);
      float bp_pay = i_u - u_pay;

      int64_t ar = u_pay + bp_pay; //global annualized inflation rate
      int64_t ipf = pay_factor_precision;  //producer pay factor

      int64_t vpf = _gstate4.votepay_factor; // remains constant since there's no voting

      system_contract::setinflation_action setinflation_act{ _self, { {_self, active_permission} } };
      setinflation_act.send(ar, ipf, vpf);

   }

} //namespace eosiosystem
