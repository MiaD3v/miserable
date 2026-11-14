#pragma once
#include "inventory.hpp"

namespace Miserable {
    class Store {
        std::unordered_map<Miserable::Item, uint64_t> prices;
        public:
        explicit Store();
        std::unordered_map<Miserable::Item, uint64_t> getPrices();
        int buy(Item, Inventory&);
    };
}