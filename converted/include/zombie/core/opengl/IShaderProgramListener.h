#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace opengl {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class IShaderProgramListener {
public:
  virtual ~IShaderProgramListener() = default;
  void callback(ShaderProgram sender);
}
} // namespace opengl
} // namespace core
} // namespace zombie
