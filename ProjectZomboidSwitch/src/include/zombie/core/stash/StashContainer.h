#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace stash {

class StashContainer {
public:
    std::string room;
    std::string containerSprite;
    std::string containerType;
    int contX = -1;
    int contY = -1;
    int contZ = -1;
    std::string containerItem;

    public StashContainer(const std::string& var1, const std::string& var2, const std::string& var3) {
      if (var1 == nullptr) {
         this.room = "all";
      } else {
         this.room = var1;
      }

      this.containerSprite = var2;
      this.containerType = var3;
   }
}
} // namespace stash
} // namespace core
} // namespace zombie
