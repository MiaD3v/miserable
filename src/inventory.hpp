#pragma once
#include <unordered_map>
#include <vector>
#include <cstdint>

#include "item.hpp"

namespace Miserable {
    class Inventory : public std::vector<std::pair<Item, double>> {
        uint64_t cents = 0;
        public:
        explicit Inventory();
        uint64_t getMoney();
        void charge(uint64_t);
        void give_money(uint64_t);
    };
}