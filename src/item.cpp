#include <utility>

#include "item.hpp"

std::pair<const char*, size_t> Miserable::getItemName(Item it){
    switch(it) {
        case doll:
            return std::pair("Doll", (size_t)4);
        case empty_bottle:
            return std::pair("Empty Bottle", (size_t)12);
    }
    return std::pair("Idk, maybe a granny?", (size_t)20);
}