#include "inventory.hpp"

Miserable::Inventory::Inventory() {
    cents = 0;
}
uint64_t Miserable::Inventory::getMoney() {
    return cents;
}
void Miserable::Inventory::charge(uint64_t cost) {
    cents -= cost;
}
void Miserable::Inventory::give_money(uint64_t wage) {
    cents += wage;
}