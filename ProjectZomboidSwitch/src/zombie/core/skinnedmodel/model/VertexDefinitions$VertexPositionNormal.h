#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/skinnedmodel/Vector3.h"
#include "zombie/iso/Vector2.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {


class VertexDefinitions {
public:
    Vector3 Position;
    Vector3 Normal;

   public VertexDefinitions$VertexPositionNormal(VertexDefinitions var1, Vector3 var2, Vector3 var3, Vector2 var4) {
      this.this$0 = var1;
      this.Position = var2;
      this.Normal = var3;
   }

   public VertexDefinitions$VertexPositionNormal(VertexDefinitions var1, float var2, float var3, float var4, float var5, float var6, float var7) {
      this.this$0 = var1;
      this.Position = std::make_shared<Vector3>(var2, var3, var4);
      this.Normal = std::make_shared<Vector3>(var5, var6, var7);
   }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
