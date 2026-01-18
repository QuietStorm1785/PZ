#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class SoftwareModelMeshInstance {
public:
  SoftwareModelMesh softwareMesh;
  VertexBufferObject vb;
  std::string name;

public
  SoftwareModelMeshInstance(const std::string &_name,
                            SoftwareModelMesh _softwareMesh) {
    this.name = _name;
    this.softwareMesh = _softwareMesh;
    this.vb = std::make_unique<VertexBufferObject>();
    this.vb.elements = _softwareMesh.indicesUnskinned;
  }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
