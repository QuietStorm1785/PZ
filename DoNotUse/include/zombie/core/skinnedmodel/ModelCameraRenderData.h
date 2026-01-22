#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/core/skinnedmodel/ModelManager/ModelSlot.h"
#include "zombie/core/textures/TextureDraw/GenericDrawer.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/popman/ObjectPool.h"
#include "zombie/util/Type.h"
#include "zombie/vehicles/BaseVehicle.h"

namespace zombie {
namespace core {
namespace skinnedmodel {


class ModelCameraRenderData : public GenericDrawer {
public:
    ModelCamera m_camera;
    float m_angle;
    bool m_bUseWorldIso;
    float m_x;
    float m_y;
    float m_z;
    bool m_bInVehicle;
   public static const ObjectPool<ModelCameraRenderData> s_pool = std::make_shared<ObjectPool>(ModelCameraRenderData::new);

    ModelCameraRenderData init(ModelCamera var1, ModelSlot var2) {
    IsoMovingObject var3 = var2.model.object;
    IsoGameCharacter var4 = (IsoGameCharacter)Type.tryCastTo(var3, IsoGameCharacter.class);
      this.m_camera = var1;
      this.m_x = var3.x;
      this.m_y = var3.y;
      this.m_z = var3.z;
      if (var4 == nullptr) {
         this.m_angle = 0.0F;
         this.m_bInVehicle = false;
         this.m_bUseWorldIso = !BaseVehicle.RENDER_TO_TEXTURE;
      } else {
         this.m_bInVehicle = var4.isSeatedInVehicle();
         if (this.m_bInVehicle) {
            this.m_angle = 0.0F;
    BaseVehicle var5 = var4.getVehicle();
            this.m_x = var5.x;
            this.m_y = var5.y;
            this.m_z = var5.z;
         } else {
            this.m_angle = var4.getAnimationPlayer().getRenderedAngle();
         }

         this.m_bUseWorldIso = true;
      }

    return this;
   }

    ModelCameraRenderData init(ModelCamera var1, float var2, bool var3, float var4, float var5, float var6, bool var7) {
      this.m_camera = var1;
      this.m_angle = var2;
      this.m_bUseWorldIso = var3;
      this.m_x = var4;
      this.m_y = var5;
      this.m_z = var6;
      this.m_bInVehicle = var7;
    return this;
   }

    void render() {
      this.m_camera.m_useAngle = this.m_angle;
      this.m_camera.m_bUseWorldIso = this.m_bUseWorldIso;
      this.m_camera.m_x = this.m_x;
      this.m_camera.m_y = this.m_y;
      this.m_camera.m_z = this.m_z;
      this.m_camera.m_bInVehicle = this.m_bInVehicle;
      ModelCamera.instance = this.m_camera;
   }

    void postRender() {
      s_pool.release(this);
   }
}
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
