#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace zombie {
namespace core {
namespace textures {


class TextureCombiner {
public:
    TextureFBO fbo;
   const ArrayDeque<Texture> textures = std::make_unique<ArrayDeque<>>();

   private TextureCombiner$CombinerFBO() {
   }
}
} // namespace textures
} // namespace core
} // namespace zombie
