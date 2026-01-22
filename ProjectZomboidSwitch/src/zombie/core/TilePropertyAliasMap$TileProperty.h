#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {


class TilePropertyAliasMap {
public:
    std::string propertyName;
   public const std::vector<std::string> possibleValues = std::make_unique<std::vector<>>();
   public const std::unordered_map<std::string, int> idMap = std::make_unique<std::unordered_map<>>();
}
} // namespace core
} // namespace zombie
