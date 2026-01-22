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


class VertexBufferObject {
public:
    VertexType m_type;
    int m_byteSize;
    int m_byteOffset;
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
