#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Matrix4f.h"
#include "org/lwjgl/opengl/GL11.h"
#include "zombie/core/opengl/PZGLUtil.h"
#include "zombie/core/textures/Texture.h"

namespace zombie {
namespace core {
namespace particle {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class MuzzleFlash {
public:
 static Texture muzzleFlashStar;
 static Texture muzzleFlashSide;

 static void init() {
 muzzleFlashStar = Texture.getSharedTexture("media/textures/muzzle-flash-star.png");
 muzzleFlashSide = Texture.getSharedTexture("media/textures/muzzle-flash-side.png");
 }

 static void render(Matrix4f matrix4f) {
 if (muzzleFlashStar != nullptr && muzzleFlashStar.isReady()) {
 if (muzzleFlashSide != nullptr && muzzleFlashSide.isReady()) {
 PZGLUtil.pushAndMultMatrix(5888, matrix4f);
 GL11.glDisable(2884);
 GL11.glColor3f(1.0F, 1.0F, 1.0F);
 muzzleFlashStar.bind();
 float float0 = 0.15F;
 GL11.glBegin(7);
 GL11.glTexCoord2f(0.0F, 1.0F);
 GL11.glVertex3f(-float0 / 2.0F, float0 / 2.0F, 0.0F);
 GL11.glTexCoord2f(1.0F, 1.0F);
 GL11.glVertex3f(float0 / 2.0F, float0 / 2.0F, 0.0F);
 GL11.glTexCoord2f(1.0F, 0.0F);
 GL11.glVertex3f(float0 / 2.0F, -float0 / 2.0F, 0.0F);
 GL11.glTexCoord2f(0.0F, 0.0F);
 GL11.glVertex3f(-float0 / 2.0F, -float0 / 2.0F, 0.0F);
 GL11.glEnd();
 muzzleFlashSide.bind();
 float0 = 0.05F;
 GL11.glBegin(7);
 GL11.glTexCoord2f(0.0F, 1.0F);
 GL11.glVertex3f(0.0F, float0 / 2.0F, 0.0F);
 GL11.glTexCoord2f(1.0F, 1.0F);
 GL11.glVertex3f(0.0F, float0 / 2.0F, float0 * 2.0F);
 GL11.glTexCoord2f(1.0F, 0.0F);
 GL11.glVertex3f(0.0F, -float0 / 2.0F, float0 * 2.0F);
 GL11.glTexCoord2f(0.0F, 0.0F);
 GL11.glVertex3f(0.0F, -float0 / 2.0F, 0.0F);
 GL11.glEnd();
 GL11.glEnable(2884);
 PZGLUtil.popMatrix(5888);
 }
 }
 }
}
} // namespace particle
} // namespace core
} // namespace zombie
