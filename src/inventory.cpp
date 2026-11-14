#include "inventory.hpp"

Miserable::Inventory::Inventory() {
}
uint64_t Miserable::Inventory::getMoney() {
    return cents;
}
bool Miserable::Inventory::charge(uint64_t cost) {
    if(cents >= cost){
        cents -= cost;
        return true;
    }
    return false;
}
bool Miserable::Inventory::Buy_Doll() {
    if(charge(dollCost)){
        dolls.push(1);
        return true;
    }
    return false;
}
bool Miserable::Inventory::Buy_Bottle() {
    if(charge(bottleCost)){
        bottleCount++;
        return true;
    }
    return false;
}
bool Miserable::Inventory::Upgrade_Dolly() {
    if(charge(upgradeCost)){
        dollyLevel++;
        return true;
    }
    return false;
}