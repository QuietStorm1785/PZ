#pragma once
#include "zombie/core/Rand.h"
#include "zombie/core/SpriteRenderer.h"
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

class RainParticle : public WeatherParticle {
public:
 double angleRadians = 0.0;
 float lastAngle = -1.0F;
 float lastIntensity = -1.0F;
 float angleOffset = 0.0F;
 float alphaMod = 0.0F;
 float incarnateAlpha = 1.0F;
 float life = 0.0F;
private
 RainParticle.RenderPoints rp;
 bool angleUpdate = false;
 float tmpAngle = 0.0F;

public
 RainParticle(Texture texture, int int0) {
 super(texture);
 if (int0 > 6) {
 this->bounds.setSize(Rand.Next(1, 2), int0);
 } else {
 this->bounds.setSize(1, int0);
 }

 this->oWidth = this->bounds.getWidth();
 this->oHeight = this->bounds.getHeight();
 this->recalcSizeOnZoom = true;
 this->zoomMultiW = 0.0F;
 this->zoomMultiH = 2.0F;
 this->setLife();
 this->rp = new RainParticle.RenderPoints();
 this->rp.setDimensions(this->oWidth, this->oHeight);
 }

 void setLife() { this->life = Rand.Next(20, 60); }

 void update(float float0) {
 this->angleUpdate = false;
 if (this->updateZoomSize()) {
 this->rp.setDimensions(this->oWidth, this->oHeight);
 this->angleUpdate = true;
 }

 if (this->angleUpdate || this->lastAngle != IsoWeatherFX.instance.windAngle ||
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
 this->lastIntensity = IsoWeatherFX.instance.windPrecipIntensity.value();
 this->angleUpdate = true;
 }

 this->position.x =
 this->position.x + this->velocity.x *
 (1.0F + IsoWeatherFX.instance.windSpeed * 0.1F) *
 float0;
 this->position.y =
 this->position.y + this->velocity.y *
 (1.0F + IsoWeatherFX.instance.windSpeed * 0.1F) *
 float0;
 this->life--;
 if (this->life < 0.0F) {
 this->setLife();
 this->incarnateAlpha = 0.0F;
 this->position.set(Rand.Next(0, this->parent.getWidth()),
 Rand.Next(0, this->parent.getHeight()));
 }

 if (this->incarnateAlpha < 1.0F) {
 this->incarnateAlpha += 0.035F;
 if (this->incarnateAlpha > 1.0F) {
 this->incarnateAlpha = 1.0F;
 }
 }

 super.update(float0, false);
 this->bounds.setLocation((int)this->position.x, (int)this->position.y);
 if (this->angleUpdate) {
 this->tmpAngle += 90.0F;
 if (this->tmpAngle > 360.0F) {
 this->tmpAngle -= 360.0F;
 }

 if (this->tmpAngle < 0.0F) {
 this->tmpAngle += 360.0F;
 }

 this->angleRadians = Math.toRadians(this->tmpAngle);
 this->rp.rotate(this->angleRadians);
 }

 this->alphaMod = 1.0F - 0.2F * IsoWeatherFX.instance.windIntensity.value();
 this->renderAlpha = this->alpha * this->alphaMod * this->alphaFadeMod.value() *
 IsoWeatherFX.instance.indoorsAlphaMod.value() *
 this->incarnateAlpha;
 this->renderAlpha *= 0.55F;
 if (IsoWeatherFX.instance.playerIndoors) {
 this->renderAlpha *= 0.5F;
 }
 }

 void render(float float0, float float1) {
 double double0 = float0 + this->bounds.getX();
 double double1 = float1 + this->bounds.getY();
 SpriteRenderer.instance.render(
 this->texture, double0 + this->rp.getX(0), double1 + this->rp.getY(0),
 double0 + this->rp.getX(1), double1 + this->rp.getY(1),
 double0 + this->rp.getX(2), double1 + this->rp.getY(2),
 double0 + this->rp.getX(3), double1 + this->rp.getY(3), this->color.r,
 this->color.g, this->color.b, this->renderAlpha, nullptr);
 }

class Point {
 double origx;
 double origy;
 double x;
 double y;

 void setOrig(double double0, double double1) {
 this->origx = double0;
 this->origy = double1;
 this->x = double0;
 this->y = double1;
 }

 void set(double double0, double double1) {
 this->x = double0;
 this->y = double1;
 }
 }

 class RenderPoints {
 RainParticle.Point[] points = new RainParticle.Point[4];
 RainParticle.Point center = RainParticle.this->std::make_unique<Point>();
 RainParticle.Point dim = RainParticle.this->std::make_unique<Point>();

 public
 RenderPoints() {
 for (int int0 = 0; int0 < this->points.length; int0++) {
 this->points[int0] = RainParticle.this->std::make_unique<Point>();
 }
 }

 double getX(int int0) { return this->points[int0].x; }

 double getY(int int0) { return this->points[int0].y; }

 void setCenter(float float1, float float0) {
 this->center.set(float1, float0);
 }

 void setDimensions(float float1, float float0) {
 this->dim.set(float1, float0);
 this->points[0].setOrig(-float1 / 2.0F, -float0 / 2.0F);
 this->points[1].setOrig(float1 / 2.0F, -float0 / 2.0F);
 this->points[2].setOrig(float1 / 2.0F, float0 / 2.0F);
 this->points[3].setOrig(-float1 / 2.0F, float0 / 2.0F);
 }

 void rotate(double double1) {
 double double0 = Math.cos(double1);
 double double2 = Math.sin(double1);

 for (int int0 = 0; int0 < this->points.length; int0++) {
 this->points[int0].x = this->points[int0].origx * double0 -
 this->points[int0].origy * double2;
 this->points[int0].y = this->points[int0].origx * double2 +
 this->points[int0].origy * double0;
 }
 }
 }
}
} // namespace fx
} // namespace weather
} // namespace iso
} // namespace zombie
