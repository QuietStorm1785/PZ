#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace textures {

class TextureDraw {
public:
   public abstract void render();

    void postRender() {
   }
}
} // namespace textures
} // namespace core
} // namespace zombie
