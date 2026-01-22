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

class ShaderProgram {
public:
    std::string name;
    int size;
    int loc;
    int type;
    int sampler;
}
} // namespace opengl
} // namespace core
} // namespace zombie
