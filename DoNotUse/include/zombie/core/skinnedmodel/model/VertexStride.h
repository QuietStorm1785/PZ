#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/skinnedmodel/model/VertexBufferObject/VertexType.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {


class VertexStride {
public:
    VertexType Type;
    int Offset;
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
