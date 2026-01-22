#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/textures/Mask.h"

namespace zombie {
namespace interfaces {


class IMaskerable {
public:
    virtual ~IMaskerable() = default;
    Mask getMask();
}
} // namespace interfaces
} // namespace zombie
