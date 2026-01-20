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

class TextureNameAlreadyInUseException : public RuntimeException {
public:
    public TextureNameAlreadyInUseException(const std::string& var1) {
      super("Texture Name " + var1 + " is already in use");
   }
}
} // namespace textures
} // namespace core
} // namespace zombie
