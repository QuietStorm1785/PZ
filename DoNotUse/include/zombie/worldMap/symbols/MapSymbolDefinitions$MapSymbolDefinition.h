#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace worldMap {
namespace symbols {

class MapSymbolDefinitions {
public:
    std::string id;
    std::string texturePath;
    int width;
    int height;

    std::string getId() {
      return this.id;
   }

    std::string getTexturePath() {
      return this.texturePath;
   }

    int getWidth() {
      return this.width;
   }

    int getHeight() {
      return this.height;
   }
}
} // namespace symbols
} // namespace worldMap
} // namespace zombie
