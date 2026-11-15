#pragma once
#include <unordered_map>
#include <vector>
#include <cstdint>
#include <queue>

#include "item.hpp"

namespace Miserable {
    class Inventory : public std::vector<std::pair<Item, double>> {
        float cents = 1000;
        public:
            std::queue<float> load_dolls; 
            std::queue<float> unload_dolls;
            std::queue<float> bottleCount;
            int dollyLevel = 1;
            int dollCost = 10;
            int bottleCost = 500;
            int upgradeCost = 10;

            explicit Inventory();
            uint64_t getMoney();
            bool charge(uint64_t);
            void give_money(float);
            bool Buy_Bottle();
            bool Buy_Load_Doll(float);
            bool Buy_Unload_Doll(float);
            bool Upgrade_Dolly();

        private:
    };
}