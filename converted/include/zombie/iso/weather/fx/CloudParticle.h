#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/textures/Texture.h"

namespace zombie {
namespace iso {
namespace weather {
namespace fx {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class CloudParticle : public WeatherParticle {
public:
 double angleRadians = 0.0;
 float lastAngle = -1.0F;
 float lastIntensity = -1.0F;
 float angleOffset = 0.0F;
 float alphaMod = 0.0F;
 float tmpAngle = 0.0F;

 public CloudParticle(Texture texture) {
 super(texture);
 }

 public CloudParticle(Texture texture, int int0, int int1) {
 super(texture, int0, int1);
 }

 void update(float float0) {
 if (this->lastAngle != IsoWeatherFX.instance.windAngleClouds || this->lastIntensity != IsoWeatherFX.instance.windIntensity.value()) {
 this->tmpAngle = IsoWeatherFX.instance.windAngleClouds;
 if (this->tmpAngle > 360.0F) {
 this->tmpAngle -= 360.0F;
 }

 if (this->tmpAngle < 0.0F) {
 this->tmpAngle += 360.0F;
 }

 this->angleRadians = Math.toRadians(this->tmpAngle);
 this->velocity.set((float)Math.cos(this->angleRadians) * this->speed, (float)Math.sin(this->angleRadians) * this->speed);
 this->lastAngle = IsoWeatherFX.instance.windAngleClouds;
 }

 this->position.x = this->position.x + this->velocity.x * IsoWeatherFX.instance.windSpeedFog * float0;
 this->position.y = this->position.y + this->velocity.y * IsoWeatherFX.instance.windSpeedFog * float0;
 super.update(float0);
 this->alphaMod = IsoWeatherFX.instance.cloudIntensity.value() * 0.3F;
 this->renderAlpha = this->alpha * this->alphaMod * this->alphaFadeMod.value() * IsoWeatherFX.instance.indoorsAlphaMod.value();
 }
}
} // namespace fx
} // namespace weather
} // namespace iso
} // namespace zombie
