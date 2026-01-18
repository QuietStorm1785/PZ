#pragma once
#include "zombie/core/Rand.h"
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

class SnowParticle : public WeatherParticle {
public:
 double angleRadians = 0.0;
 float lastAngle = -1.0F;
 float lastIntensity = -1.0F;
 float angleOffset = 0.0F;
 float alphaMod = 0.0F;
 float incarnateAlpha = 1.0F;
 float life = 0.0F;
 float fadeTime = 80.0F;
 float tmpAngle = 0.0F;

public
 SnowParticle(Texture texture) {
 super(texture);
 this->recalcSizeOnZoom = true;
 this->zoomMultiW = 1.0F;
 this->zoomMultiH = 1.0F;
 }

 void setLife() { this->life = this->fadeTime + Rand.Next(60, 500); }

 void update(float float0) {
 if (this->lastAngle != IsoWeatherFX.instance.windAngle ||
 this->lastIntensity !=
 IsoWeatherFX.instance.windPrecipIntensity.value()) {
 this->tmpAngle = IsoWeatherFX.instance.windAngle +
 (this->angleOffset -
 this->angleOffset * 0.5F *
 IsoWeatherFX.instance.windPrecipIntensity.value());
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

 if (this->life >= this->fadeTime) {
 this->position.x = this->position.x + this->velocity.x *
 IsoWeatherFX.instance.windSpeed *
 float0;
 this->position.y = this->position.y + this->velocity.y *
 IsoWeatherFX.instance.windSpeed *
 float0;
 } else {
 this->incarnateAlpha = this->life / this->fadeTime;
 }

 this->life--;
 if (this->life < 0.0F) {
 this->setLife();
 this->incarnateAlpha = 0.0F;
 this->position.set(Rand.Next(0, this->parent.getWidth()),
 Rand.Next(0, this->parent.getHeight()));
 }

 if (this->incarnateAlpha < 1.0F) {
 this->incarnateAlpha += 0.05F;
 if (this->incarnateAlpha > 1.0F) {
 this->incarnateAlpha = 1.0F;
 }
 }

 super.update(float0);
 this->updateZoomSize();
 this->alphaMod = 1.0F - 0.2F * IsoWeatherFX.instance.windIntensity.value();
 this->renderAlpha = this->alpha * this->alphaMod * this->alphaFadeMod.value() *
 IsoWeatherFX.instance.indoorsAlphaMod.value() *
 this->incarnateAlpha;
 this->renderAlpha *= 0.7F;
 }

 void render(float float0, float float1) { super.render(float0, float1); }
}
} // namespace fx
} // namespace weather
} // namespace iso
} // namespace zombie
