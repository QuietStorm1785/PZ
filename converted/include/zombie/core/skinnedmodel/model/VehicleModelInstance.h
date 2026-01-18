#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Vector3f.h"
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/iso/IsoLightSource.h"
#include <algorithm>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class VehicleModelInstance : public ModelInstance {
public:
 Texture textureRust = nullptr;
 Texture textureMask = nullptr;
 Texture textureLights = nullptr;
 Texture textureDamage1Overlay = nullptr;
 Texture textureDamage1Shell = nullptr;
 Texture textureDamage2Overlay = nullptr;
 Texture textureDamage2Shell = nullptr;
 public float[] textureUninstall1 = new float[16];
 public float[] textureUninstall2 = new float[16];
 public float[] textureLightsEnables1 = new float[16];
 public float[] textureLightsEnables2 = new float[16];
 public float[] textureDamage1Enables1 = new float[16];
 public float[] textureDamage1Enables2 = new float[16];
 public float[] textureDamage2Enables1 = new float[16];
 public float[] textureDamage2Enables2 = new float[16];
 public float[] matrixBlood1Enables1 = new float[16];
 public float[] matrixBlood1Enables2 = new float[16];
 public float[] matrixBlood2Enables1 = new float[16];
 public float[] matrixBlood2Enables2 = new float[16];
 float textureRustA = 0.0F;
 float refWindows = 0.5F;
 float refBody = 0.4F;
 const Vector3f painColor = new Vector3f(0.0F, 0.5F, 0.5F);
 private IsoLightSource[] m_lights = new IsoLightSource[3];
 const void* m_lightsLock = "Model Lights Lock";

 void reset() {
 super.reset();
 Arrays.fill(this->textureUninstall1, 0.0F);
 Arrays.fill(this->textureUninstall2, 0.0F);
 Arrays.fill(this->textureLightsEnables1, 0.0F);
 Arrays.fill(this->textureLightsEnables2, 0.0F);
 Arrays.fill(this->textureDamage1Enables1, 0.0F);
 Arrays.fill(this->textureDamage1Enables2, 0.0F);
 Arrays.fill(this->textureDamage2Enables1, 0.0F);
 Arrays.fill(this->textureDamage2Enables2, 0.0F);
 Arrays.fill(this->matrixBlood1Enables1, 0.0F);
 Arrays.fill(this->matrixBlood1Enables2, 0.0F);
 Arrays.fill(this->matrixBlood2Enables1, 0.0F);
 Arrays.fill(this->matrixBlood2Enables2, 0.0F);
 this->textureRustA = 0.0F;
 this->refWindows = 0.5F;
 this->refBody = 0.4F;
 this->painColor.set(0.0F, 0.5F, 0.5F);
 Arrays.fill(this->m_lights, nullptr);
 }

 void setLights(IsoLightSource[] lightSources) {
 this->m_lights = lightSources;
 }

 public IsoLightSource[] getLights() {
 return this->m_lights;
 }

 void UpdateLights() {
 synchronized (this->m_lightsLock) {
 ModelManager.instance.getClosestThreeLights(this->object, this->m_lights);
 }
 }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
