#pragma once
#include "zombie/core/textures/Texture.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace iso {
namespace weather {
namespace fx {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class FogParticle : public WeatherParticle {
public:
 double angleRadians = 0.0;
 float lastAngle = -1.0F;
 float lastIntensity = -1.0F;
 float angleOffset = 0.0F;
 float alphaMod = 0.0F;
 float tmpAngle = 0.0F;

public
 FogParticle(Texture texture, int int0, int int1) {
 super(texture, int0, int1);
 }

 void update(float float0) {
 if (this->lastAngle != IsoWeatherFX.instance.windAngle ||
 this->lastIntensity != IsoWeatherFX.instance.windIntensity.value()) {
 this->tmpAngle =
 IsoWeatherFX.instance.windAngle +
 (this->angleOffset - this->angleOffset * 1.0F *
 IsoWeatherFX.instance.windIntensity.value());
 if (this->tmpAngle > 360.0F) {
 this->tmpAngle -= 360.0F;
 }

 if (this->tmpAngle < 0.0F) {
 this->tmpAngle += 360.0F;
 }

 this->angleRadians = Math.toRadians(this->tmpAngle);
 this->velocity.set((float)Math.cos(this->angleRadians) * this->speed,
 (float)Math.sin(this->angleRadians) * this->speed);
 this->lastAngle = IsoWeatherFX.instance.windAngle;
 }

 this->position.x = this->position.x + this->velocity.x *
 IsoWeatherFX.instance.windSpeedFog *
 float0;
 this->position.y = this->position.y + this->velocity.y *
 IsoWeatherFX.instance.windSpeedFog *
 float0;
 super.update(float0);
 this->alphaMod = IsoWeatherFX.instance.fogIntensity.value();
 this->renderAlpha = this->alpha * this->alphaMod * this->alphaFadeMod.value() *
 IsoWeatherFX.instance.indoorsAlphaMod.value();
 }
}
} // namespace fx
} // namespace weather
} // namespace iso
} // namespace zombie
