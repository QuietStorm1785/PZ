#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/map/hash/THashMap.h"
#include "zombie/inventory/ItemPickerJava/ItemPickerContainer.h"

namespace zombie {
namespace inventory {


class ItemPickerJava {
public:
   public THashMap<std::string, ItemPickerContainer> Containers = std::make_unique<THashMap>();
    int fillRand;
    bool isShop;
    std::string specificId = nullptr;
}
} // namespace inventory
} // namespace zombie
