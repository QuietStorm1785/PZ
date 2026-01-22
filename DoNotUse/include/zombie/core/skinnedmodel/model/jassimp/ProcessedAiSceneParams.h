#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "jassimp/AiScene.h"
#include "org/lwjgl/util/vector/Quaternion.h"
#include "zombie/core/skinnedmodel/model/SkinningData.h"
#include "zombie/core/skinnedmodel/model/jassimp/JAssImpImporter/LoadMode.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {
namespace jassimp {


class ProcessedAiSceneParams {
public:
    AiScene scene = nullptr;
    LoadMode mode = LoadMode.Normal;
    SkinningData skinnedTo = nullptr;
    std::string meshName = nullptr;
    float animBonesScaleModifier = 1.0F;
    Quaternion animBonesRotateModifier = nullptr;

   ProcessedAiSceneParams() {
   }

    static ProcessedAiSceneParams create() {
      return std::make_unique<ProcessedAiSceneParams>();
   }

    void set(ProcessedAiSceneParams var1) {
      this.scene = var1.scene;
      this.mode = var1.mode;
      this.skinnedTo = var1.skinnedTo;
      this.meshName = var1.meshName;
      this.animBonesScaleModifier = var1.animBonesScaleModifier;
      this.animBonesRotateModifier = var1.animBonesRotateModifier;
   }
}
} // namespace jassimp
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
