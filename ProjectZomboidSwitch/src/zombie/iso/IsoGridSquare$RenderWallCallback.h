#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/textures/Texture.h"

namespace zombie {
namespace iso {


class IsoGridSquare {
public:
    virtual ~IsoGridSquare() = default;
    void invoke(Texture var1, float var2, float var3);
}
} // namespace iso
} // namespace zombie
