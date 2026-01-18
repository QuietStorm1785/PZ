#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/sprite/IsoSpriteInstance.h"

namespace zombie {
namespace iso {
namespace objects {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class IsoZombieHead : public IsoMovingObject {
public:
 float tintb = 1.0F;
 float tintg = 1.0F;
 float tintr = 1.0F;
 float time = 0.0F;

 public IsoZombieHead(IsoCell cell) {
 super(cell);
 }

 bool Serialize() {
 return false;
 }

 std::string getObjectName() {
 return "ZombieHead";
 }

 void update() {
 super.update();
 this->time = this->time + GameTime.instance.getMultipliedSecondsSinceLastUpdate();
 this->sx = this->sy = 0.0F;
 }

 void render(float float0, float float1, float float2, ColorInfo colorInfo, bool boolean0, bool boolean1, Shader shader) {
 this->setTargetAlpha(1.0F);
 super.render(float0, float1, float2, colorInfo, boolean0, boolean1, shader);
 }

 public IsoZombieHead(IsoZombieHead.GibletType gibletType, IsoCell cell, float float0, float float1, float float2) {
 super(cell);
 this->solid = false;
 this->shootable = false;
 this->x = float0;
 this->y = float1;
 this->z = float2;
 this->nx = float0;
 this->ny = float1;
 this->setAlpha(0.5F);
 this->def = IsoSpriteInstance.get(this->sprite);
 this->def.alpha = 1.0F;
 this->sprite.def.alpha = 1.0F;
 this->offsetX = -26.0F;
 this->offsetY = -242.0F;
 switch (gibletType) {
 case A:
 this->sprite.LoadFramesNoDirPageDirect("media/gibs/Giblet", "00", 3);
 break;
 case B:
 this->sprite.LoadFramesNoDirPageDirect("media/gibs/Giblet", "01", 3);
 }
 }

 public static enum GibletType {
 A,
 B,
 Eye;
 }
}
} // namespace objects
} // namespace iso
} // namespace zombie
