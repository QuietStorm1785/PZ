#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/debug/options/Terrain/RenderTiles.h"

namespace zombie {
namespace debug {
namespace options {


class Terrain : public OptionGroup {
public:
    const RenderTiles RenderTiles = std::make_shared<RenderTiles>(this, this.Group);

    public Terrain() {
      super("Terrain");
   }
}
} // namespace options
} // namespace debug
} // namespace zombie
