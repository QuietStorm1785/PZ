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

enum class ModelLoader {
   Version,
   ModelName,
   VertexStrideElementCount,
   VertexStrideSize,
   VertexStrideData,
   VertexCount,
   VertexBuffer,
   NumberOfFaces,
   FaceData,
   NumberOfBones,
   SkeletonHierarchy,
   BindPose,
   InvBindPose,
   SkinOffsetMatrices,
   NumberOfAnims,
   Anim;
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
