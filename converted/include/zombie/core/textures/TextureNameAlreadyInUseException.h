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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class TextureNameAlreadyInUseException : public RuntimeException {
public:
 public TextureNameAlreadyInUseException(const std::string& string) {
 super("Texture Name " + string + " is already in use");
 }
}
} // namespace textures
} // namespace core
} // namespace zombie
