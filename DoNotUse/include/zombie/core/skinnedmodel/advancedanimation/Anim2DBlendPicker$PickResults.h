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
namespace advancedanimation {

class Anim2DBlendPicker {
public:
    int numNodes;
    Anim2DBlend node1;
    Anim2DBlend node2;
    Anim2DBlend node3;
    float scale1;
    float scale2;
    float scale3;
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
