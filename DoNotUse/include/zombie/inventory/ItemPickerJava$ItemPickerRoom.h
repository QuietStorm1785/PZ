#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/inventory/ItemPickerJava/ItemPickerContainer.h"

namespace zombie {
namespace inventory {

class ItemPickerJava {
public:
    std::unordered_map<std::string, std::shared_ptr<ItemPickerContainer>> Containers;
    int fillRand;
    bool isShop;
    std::string specificId;
};

} // namespace inventory
} // namespace zombie
