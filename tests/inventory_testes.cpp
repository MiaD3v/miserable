#include <cstdlib>
#include <cassert>
#include <print>

#include "inventory.hpp"
#include "store.hpp"
#include "item.hpp"

#define NUM_TESTES 100

int random_teste() {
    Miserable::Inventory inv;
    Miserable::Store store;
    unsigned int budget = ((unsigned int)rand()) % 6000;
    inv.give_money(budget);
    int total_succ = 0;
    for (int i = 0; i < 45; i++) {
        Miserable::Item prod;
        if (rand() & 1) {
            prod = Miserable::doll;
        } else {
            prod = Miserable::empty_bottle;
        }
        if (store.getPrices()[prod] <= budget) {
            assert(store.buy(prod, inv) == 0);
            budget -= store.getPrices()[prod];
            assert(inv.getMoney() == budget);
            total_succ++;
            assert(inv.back().first == prod);
        } else {
            assert(store.buy(prod, inv) != 0);
            assert(inv.getMoney() == budget);
        }
    }
    return 0;
}

int main() {
    for (int i = 0; i < NUM_TESTES; i++){
        random_teste();
    }
}