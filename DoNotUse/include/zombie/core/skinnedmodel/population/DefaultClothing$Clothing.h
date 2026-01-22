#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace population {


class DefaultClothing {
public:
   const std::vector<std::string> hue = std::make_unique<std::vector<>>();
   const std::vector<std::string> texture = std::make_unique<std::vector<>>();
   const std::vector<std::string> tint = std::make_unique<std::vector<>>();

   private DefaultClothing$Clothing() {
   }

    void clear() {
      this.hue.clear();
      this.texture.clear();
      this.tint.clear();
   }
}
} // namespace population
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
