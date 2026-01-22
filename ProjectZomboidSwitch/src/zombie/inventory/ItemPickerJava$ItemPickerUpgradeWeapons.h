#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace inventory {


class ItemPickerJava {
public:
    std::string name;
   public std::vector<std::string> Upgrades = std::make_unique<std::vector<>>();
}
} // namespace inventory
} // namespace zombie
