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

class TextureNotFoundException : public RuntimeException {
public:
    public TextureNotFoundException(const std::string& var1) {
      super("Image " + var1 + " not found! ");
   }
}
} // namespace textures
} // namespace core
} // namespace zombie
