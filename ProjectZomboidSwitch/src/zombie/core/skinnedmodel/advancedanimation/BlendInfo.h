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

class BlendInfo {
public:
    std::string name;
    BlendType Type;
    std::string mulDec;
    std::string mulInc;
    float dec;
    float inc;
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
