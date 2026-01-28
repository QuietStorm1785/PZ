#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/utils/BufferUtils.h"
#include <filesystem>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {


class VertexBufferObject {
public:
    const IntBuffer b = BufferUtils::createIntBuffer(4);
    int VboID;
    int EboID;
    int NumElements;
    int VertexStride;
    bool FaceDataOnly;
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
