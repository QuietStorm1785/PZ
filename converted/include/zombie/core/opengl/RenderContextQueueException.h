#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace opengl {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class RenderContextQueueException : public RuntimeException {
public:
 public RenderContextQueueException(std::exception throwable) {
 super(throwable);
 }
}
} // namespace opengl
} // namespace core
} // namespace zombie
