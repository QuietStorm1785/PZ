#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace textures {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class TextureNameAlreadyInUseException : public RuntimeException {
public:
public
 TextureNameAlreadyInUseException(std::string_view string) {
 super("Texture Name " + string + " is already in use");
 }
}
} // namespace textures
} // namespace core
} // namespace zombie
