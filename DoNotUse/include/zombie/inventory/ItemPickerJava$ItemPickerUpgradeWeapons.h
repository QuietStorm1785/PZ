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
    std::vector<std::string> Upgrades;
};

} // namespace inventory
} // namespace zombie
