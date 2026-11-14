#pragma once
#include <utility>
#include <cstddef>
namespace Miserable {
    typedef enum {
        doll,
        empty_bottle,
        upgrade,
    } Item;

    std::pair<const char*, size_t> getItemName(Item);
}