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

class IShaderProgramListener {
public:
    virtual ~IShaderProgramListener() = default;
    void callback(ShaderProgram var1);
}
} // namespace opengl
} // namespace core
} // namespace zombie
