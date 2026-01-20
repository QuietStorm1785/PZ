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
namespace model {

enum class VertexBufferObject {
   VertexArray,
   NormalArray,
   ColorArray,
   IndexArray,
   TextureCoordArray,
   TangentArray,
   BlendWeightArray,
   BlendIndexArray;
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
