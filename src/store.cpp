#include <unordered_map>
#include <utility>

#include "item.hpp"
#include "inventory.hpp"
#include "store.hpp"

#define DOLL_PRICE 420
#define BOTTLE_PRICE 69
std::unordered_map<Miserable::Item, uint64_t> Miserable::Store::getPrices() {
    return prices;
}
Miserable::Store::Store() {
    prices[Miserable::doll] = DOLL_PRICE;
    prices[Miserable::empty_bottle] = BOTTLE_PRICE;
}

int Miserable::Store::buy(Item it, Inventory& inv) {
    if (inv.getMoney() < prices[it])
        return -1;
    inv.charge(prices[it]);
    inv.push_back(std::pair(it, 1.0));
    return 0;
}