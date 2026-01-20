#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Matrix4f.h"
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/core/skinnedmodel/animation/AnimationPlayer.h"
#include "zombie/core/skinnedmodel/animation/AnimationTrack.h"
#include "zombie/core/skinnedmodel/model/VehicleSubModelInstance.h"
#include "zombie/scripting/objects/ModelScript.h"
#include "zombie/scripting/objects/VehicleScript/Model.h"
#include "zombie/util/Pool.h"

namespace zombie {
namespace vehicles {


class BaseVehicle {
public:
    VehiclePart part;
    Model scriptModel;
    ModelScript modelScript;
    int wheelIndex;
    const Matrix4f renderTransform = std::make_shared<Matrix4f>();
    VehicleSubModelInstance modelInstance;
    AnimationPlayer m_animPlayer;
    AnimationTrack m_track;

    AnimationPlayer getAnimationPlayer() {
      if (this.part != nullptr && this.part.getParent() != nullptr) {
         BaseVehicle$ModelInfo var1 = this.part.getVehicle().getModelInfoForPart(this.part.getParent());
         if (var1 != nullptr) {
            return var1.getAnimationPlayer();
         }
      }

    std::string var3 = this.scriptModel.file;
      zombie.core.skinnedmodel.model.Model var2 = ModelManager.instance.getLoadedModel(var3);
      if (var2 != nullptr && !var2.bStatic) {
         if (this.m_animPlayer != nullptr && this.m_animPlayer.getModel() != var2) {
            this.m_animPlayer = (AnimationPlayer)Pool.tryRelease(this.m_animPlayer);
         }

         if (this.m_animPlayer == nullptr) {
            this.m_animPlayer = AnimationPlayer.alloc(var2);
         }

         return this.m_animPlayer;
      } else {
    return nullptr;
      }
   }

    void releaseAnimationPlayer() {
      this.m_animPlayer = (AnimationPlayer)Pool.tryRelease(this.m_animPlayer);
   }
}
} // namespace vehicles
} // namespace zombie
