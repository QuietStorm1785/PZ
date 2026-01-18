#pragma once
#include "org/joml/Math.h"
#include "org/lwjgl/opengl/GL11.h"
#include "zombie/core/Core.h"
#include "zombie/core/skinnedmodel/ModelCamera.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace vehicles {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class VehicleModelCamera : public ModelCamera {
public:
 static const VehicleModelCamera instance = new VehicleModelCamera();

 void Begin() {
 if (this->m_bUseWorldIso) {
 Core.getInstance().DoPushIsoStuff(this->m_x, this->m_y, this->m_z,
 this->m_useAngle, true);
 GL11.glDepthMask(this->bDepthMask);
 } else {
 GL11.glMatrixMode(5889);
 GL11.glPushMatrix();
 GL11.glLoadIdentity();
 GL11.glOrtho(-192.0, 192.0, -192.0, 192.0, -1000.0, 1000.0);
 float float0 = Math.sqrt(2048.0F);
 GL11.glScalef(-float0, float0, float0);
 GL11.glMatrixMode(5888);
 GL11.glPushMatrix();
 GL11.glLoadIdentity();
 GL11.glRotatef(30.0F, 1.0F, 0.0F, 0.0F);
 GL11.glRotatef(45.0F, 0.0F, 1.0F, 0.0F);
 }
 }

 void End() {
 if (this->m_bUseWorldIso) {
 Core.getInstance().DoPopIsoStuff();
 } else {
 GL11.glDepthFunc(519);
 GL11.glMatrixMode(5889);
 GL11.glPopMatrix();
 GL11.glMatrixMode(5888);
 GL11.glPopMatrix();
 }
 }
}
} // namespace vehicles
} // namespace zombie
