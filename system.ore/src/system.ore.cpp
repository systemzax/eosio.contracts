#include <system.ore/system.ore.hpp>

namespace eosiosystem
{

void system_ore::createoreacc(name creator,
                              name newact,
                              ignore<authority> owner,
                              ignore<authority> active,
                              asset ramquant,
                              uint64_t rambytes = 0,
                              asset stake_net_quantity,
                              asset stake_cpu_quantity)

{

    auto itr = _rammarket.find(ramcore_symbol.raw());
    auto tmp = *itr;
    auto eosout = tmp.convert( asset(bytes, ram_symbol), core_symbol() );


    INLINE_ACTION_SENDER(eosiosystem::native, newaccount)
    (
        "eosio"_n, {{_self, active_permission}},
        {_self, newact, owner, active});

    if (rambytes == 0)
    {
        eosio_assert(ramquant.amount > 0, "Have to buy ram");
        INLINE_ACTION_SENDER(eosiosystem::system_contract, buyram)
        (
            "eosio"_n, {{_self, active_permission}},
            {_self, newact, ramquant});
    } else {
        INLINE_ACTION_SENDER(eosiosystem::system_contract, buyrambytes)
        (
            "eosio"_n, {{_self, active_permission}},
            {_self, newact, rambytes});
    }

    INLINE_ACTION_SENDER(eosiosystem::system_contract, delegatebw)
    (
        "eosio"_n, {{_self, active_permission}},
        {_self, newact, stake_net_quantity, stake_cpu_quantity, transfer});
}

void system_ore::delegatebw(name from, name receiver,
                            asset stake_net_quantity,
                            asset stake_cpu_quantity, bool transfer)

{
    INLINE_ACTION_SENDER(eosiosystem::system_contract, delegatebw)
    (
        "eosio"_n, {{_self, active_permission}},
        {from, receiver, stake_net_quantity, stake_cpu_quantity, transfer});
    //changebw(from, receiver, stake_net_quantity, stake_cpu_quantity, transfer);
} // delegatebw

void system_ore::undelegatebw(name from, name receiver,
                              asset unstake_net_quantity, asset unstake_cpu_quantity)
{
    INLINE_ACTION_SENDER(eosiosystem::system_contract, undelegatebw)
    (
        "eosio"_n, {{_self, active_permission}},
        {from, receiver, -unstake_net_quantity, -unstake_cpu_quantity, false});
    //changebw(from, receiver, -unstake_net_quantity, -unstake_cpu_quantity, false);
} // undelegatebw

void system_ore::buyram(name payer, name receiver, asset quant)
{
    require_auth(payer);

    INLINE_ACTION_SENDER(eosiosystem::system_contract, buyram)
    (
        "eosio"_n, {{_self, active_permission}},
        {name payer, name receiver, asset quant});
}

void system_ore::buyrambytes(name payer, name receiver, uint32_t bytes)
{

    auto itr = _rammarket.find(ramcore_symbol.raw());
    auto tmp = *itr;
    auto eosout = tmp.convert(asset(bytes, ram_symbol), core_symbol());

    buyram(payer, receiver, eosout);
}

void system_ore::sellram(name account, int64_t bytes)
{
    require_auth(account);

    INLINE_ACTION_SENDER(eosiosystem::system_contract, sellram)
    (
        "eosio"_n, {{_self, active_permission}},
        {name account, int64_t bytes});
}

void system_ore::claimrewards(const name owner)
{
    require_auth(owner);

    INLINE_ACTION_SENDER(eosiosystem::system_contract, claimrewards)
    (
        "eosio"_n, {{_self, active_permission}},
        {owner});
}

} // namespace eosiosystem

EOSIO_DISPATCH(eosiosystem::system_ore, ()()()()()()())
