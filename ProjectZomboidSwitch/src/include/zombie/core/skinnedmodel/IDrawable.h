#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace skinnedmodel {

class IDrawable {
public:
    virtual ~IDrawable() = default;
    void Draw();
}
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
