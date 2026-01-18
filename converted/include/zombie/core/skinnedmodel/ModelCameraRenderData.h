#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/core/textures/TextureDraw.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/popman/ObjectPool.h"
#include "zombie/util/Type.h"
#include "zombie/vehicles/BaseVehicle.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ModelCameraRenderData : public TextureDraw {
public:
 ModelCamera m_camera;
 float m_angle;
 bool m_bUseWorldIso;
 float m_x;
 float m_y;
 float m_z;
 bool m_bInVehicle;
 public static ObjectPool<ModelCameraRenderData> s_pool = new ObjectPool<>(ModelCameraRenderData::new);

 ModelCameraRenderData init(ModelCamera modelCamera, ModelManager.ModelSlot modelSlot) {
 IsoMovingObject movingObject = modelSlot.model.object;
 IsoGameCharacter character = Type.tryCastTo(movingObject, IsoGameCharacter.class);
 this->m_camera = modelCamera;
 this->m_x = movingObject.x;
 this->m_y = movingObject.y;
 this->m_z = movingObject.z;
 if (character == nullptr) {
 this->m_angle = 0.0F;
 this->m_bInVehicle = false;
 this->m_bUseWorldIso = !BaseVehicle.RENDER_TO_TEXTURE;
 } else {
 this->m_bInVehicle = character.isSeatedInVehicle();
 if (this->m_bInVehicle) {
 this->m_angle = 0.0F;
 BaseVehicle vehicle = character.getVehicle();
 this->m_x = vehicle.x;
 this->m_y = vehicle.y;
 this->m_z = vehicle.z;
 } else {
 this->m_angle = character.getAnimationPlayer().getRenderedAngle();
 }

 this->m_bUseWorldIso = true;
 }

 return this;
 }

 ModelCameraRenderData init(ModelCamera modelCamera, float float0, bool boolean0, float float1, float float2, float float3, bool boolean1) {
 this->m_camera = modelCamera;
 this->m_angle = float0;
 this->m_bUseWorldIso = boolean0;
 this->m_x = float1;
 this->m_y = float2;
 this->m_z = float3;
 this->m_bInVehicle = boolean1;
 return this;
 }

 void render() {
 this->m_camera.m_useAngle = this->m_angle;
 this->m_camera.m_bUseWorldIso = this->m_bUseWorldIso;
 this->m_camera.m_x = this->m_x;
 this->m_camera.m_y = this->m_y;
 this->m_camera.m_z = this->m_z;
 this->m_camera.m_bInVehicle = this->m_bInVehicle;
 ModelCamera.instance = this->m_camera;
 }

 void postRender() {
 s_pool.release(this);
 }
}
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
