#pragma once

#include <eosio.system/eosio.system.hpp>


namespace eosiosystem {

   class [[eosio::contract("system.ore")]] system_ore : public contract {
      public:
         using contract::contract;

         [[eosio::action]]
         void createoreacc( name      creator,
                          name             name,
                          ignore<authority> owner,
                          ignore<authority> active,
                          asset ramquant,
                          uint64_t rambytes,
                          asset stake_net_quantity,
                          asset stake_cpu_quantity, 
                          bool transfer);

         [[eosio::action]]
         void delegatebw( name from, name receiver,
                          asset stake_net_quantity, asset stake_cpu_quantity, bool transfer );

         [[eosio::action]]
         void undelegatebw( name from, name receiver,
                            asset unstake_net_quantity, asset unstake_cpu_quantity );

         [[eosio::action]]
         void buyram( name payer, name receiver, asset quant );

         [[eosio::action]]
         void buyrambytes( name payer, name receiver, uint32_t bytes );

         [[eosio::action]]
         void sellram( name account, int64_t bytes );

         [[eosio::action]]
         void claimrewards( const name owner );

         

   };

} /// namespace eosio
