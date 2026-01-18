#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace com {
namespace evildevil {
namespace engines {
namespace bubble {
namespace texture {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class TextureFormatException : public Exception {
public:
 static const long serialVersionUID = 24L;

public
 TextureFormatException() {}

public
 TextureFormatException(const std::string &string) { super(string); }
}
} // namespace texture
} // namespace bubble
} // namespace engines
} // namespace evildevil
} // namespace com
