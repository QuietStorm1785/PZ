#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Color.h"
#include "zombie/core/skinnedmodel/HelperFunctions.h"
#include "zombie/core/skinnedmodel/Vector3.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {


class VertexDefinitions {
public:
    Vector3 Position;
    int Colour;

   public VertexDefinitions$VertexPositionColour(VertexDefinitions var1, Vector3 var2, Color var3) {
      this.this$0 = var1;
      this.Position = var2;
      this.Colour = HelperFunctions.ToRgba(var3);
   }

   public VertexDefinitions$VertexPositionColour(VertexDefinitions var1, float var2, float var3, float var4, Color var5) {
      this.this$0 = var1;
      this.Position = std::make_shared<Vector3>(var2, var3, var4);
      this.Colour = HelperFunctions.ToRgba(var5);
   }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
