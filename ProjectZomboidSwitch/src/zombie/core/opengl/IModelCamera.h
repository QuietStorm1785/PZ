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

class IModelCamera {
public:
    virtual ~IModelCamera() = default;
    void Begin();

    void End();
}
} // namespace opengl
} // namespace core
} // namespace zombie
