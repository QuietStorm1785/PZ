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


// $VF: synthetic class
class VertexBufferObject {
public:
   static {
      try {
         $SwitchMap$zombie$core$skinnedmodel$model$VertexBufferObject$VertexType[VertexType.VertexArray.ordinal()] = 1;
      } catch (NoSuchFieldError var7) {
      }

      try {
         $SwitchMap$zombie$core$skinnedmodel$model$VertexBufferObject$VertexType[VertexType.NormalArray.ordinal()] = 2;
      } catch (NoSuchFieldError var6) {
      }

      try {
         $SwitchMap$zombie$core$skinnedmodel$model$VertexBufferObject$VertexType[VertexType.ColorArray.ordinal()] = 3;
      } catch (NoSuchFieldError var5) {
      }

      try {
         $SwitchMap$zombie$core$skinnedmodel$model$VertexBufferObject$VertexType[VertexType.TextureCoordArray.ordinal()] = 4;
      } catch (NoSuchFieldError var4) {
      }

      try {
         $SwitchMap$zombie$core$skinnedmodel$model$VertexBufferObject$VertexType[VertexType.TangentArray.ordinal()] = 5;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$zombie$core$skinnedmodel$model$VertexBufferObject$VertexType[VertexType.BlendWeightArray.ordinal()] = 6;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$zombie$core$skinnedmodel$model$VertexBufferObject$VertexType[VertexType.BlendIndexArray.ordinal()] = 7;
      } catch (NoSuchFieldError var1) {
      }
   }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
