#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/inventory/ItemPickerJava/ItemPickerRoom.h"

namespace zombie {
namespace inventory {

class ItemPickerJava {
public:
    ItemPickerRoom Normal;
    std::vector<ItemPickerRoom> Specific;
};

} // namespace inventory
} // namespace zombie
