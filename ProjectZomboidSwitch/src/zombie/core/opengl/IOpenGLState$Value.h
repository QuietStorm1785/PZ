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

class IOpenGLState {
public:
    virtual ~IOpenGLState() = default;
   IOpenGLState$Value set(IOpenGLState$Value var1);
}
} // namespace opengl
} // namespace core
} // namespace zombie
