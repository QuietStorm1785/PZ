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

class SoftwareModelMeshInstance {
public:
    SoftwareModelMesh softwareMesh;
    VertexBufferObject vb;
    std::string name;

    public SoftwareModelMeshInstance(const std::string& var1, SoftwareModelMesh var2) {
      this.name = var1;
      this.softwareMesh = var2;
      this.vb = std::make_unique<VertexBufferObject>();
      this.vb.elements = var2.indicesUnskinned;
   }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
