#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/skinnedmodel/advancedanimation/AnimatedModel/AnimatedModelInstanceRenderData.h"
#include "zombie/core/skinnedmodel/model/ModelInstance.h"
#include "zombie/core/skinnedmodel/model/ModelInstanceTextureCreator.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {


class AnimatedModel {
public:
    ModelInstance modelInstance;
    ModelInstanceTextureCreator textureCreator;
   const std::vector<AnimatedModelInstanceRenderData> instData = std::make_unique<std::vector<>>();
   const std::vector<AnimatedModelInstanceRenderData> readyData = std::make_unique<std::vector<>>();
    bool bModelsReady;
    bool bRendered;

    AnimatedModelInstanceRenderData getParentData(ModelInstance var1) {
      for (int var2 = 0; var2 < this.readyData.size(); var2++) {
    AnimatedModelInstanceRenderData var3 = this.readyData.get(var2);
         if (var3.modelInstance == var1.parent) {
    return var3;
         }
      }

    return nullptr;
   }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
