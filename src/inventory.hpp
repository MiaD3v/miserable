#pragma once
#include <unordered_map>
#include <vector>
#include <cstdint>
#include <queue>

#include "item.hpp"

namespace Miserable {
    class Inventory : public std::vector<std::pair<Item, double>> {
        uint64_t cents = 10000; //at 10000 for testing;
        public:
            std::queue<int> dolls; 
            int bottleCount = 0;
            int dollyLevel = 0;
            int dollCost = 10;
            int bottleCost = 10;
            int upgradeCost = 10;

            explicit Inventory();
            uint64_t getMoney();
            bool charge(uint64_t);
            void give_money(uint64_t);
            bool Buy_Bottle();
            bool Buy_Doll();
            bool Upgrade_Dolly();

        private:
    };
}