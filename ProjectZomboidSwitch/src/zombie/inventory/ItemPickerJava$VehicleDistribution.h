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
   public const std::vector<ItemPickerRoom> Specific = std::make_unique<std::vector<>>();
}
} // namespace inventory
} // namespace zombie
