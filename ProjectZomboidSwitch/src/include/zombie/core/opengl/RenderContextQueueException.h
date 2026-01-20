#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace opengl {

class RenderContextQueueException : public RuntimeException {
public:
    public RenderContextQueueException(std::exception var1) {
      super(var1);
   }
}
} // namespace opengl
} // namespace core
} // namespace zombie
