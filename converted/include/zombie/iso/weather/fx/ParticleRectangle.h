#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/debug/LineDrawer.h"
#include "zombie/iso/IsoCamera.h"

namespace zombie {
namespace iso {
namespace weather {
namespace fx {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


/**
 * TurboTuTone.
 */
class ParticleRectangle {
public:
 bool DEBUG_BOUNDS = false;
 int width;
 int height;
 private WeatherParticle[] particles;
 int particlesToRender;
 int particlesReqUpdCnt = 0;

 public ParticleRectangle(int w, int h) {
 this->width = w;
 this->height = h;
 }

 int getWidth() {
 return this->width;
 }

 int getHeight() {
 return this->height;
 }

 void SetParticles(WeatherParticle[] weatherParticles) {
 for (int int0 = 0; int0 < weatherParticles.length; int0++) {
 weatherParticles[int0].setParent(this);
 }

 this->particles = weatherParticles;
 this->particlesToRender = weatherParticles.length;
 }

 void SetParticlesStrength(float str) {
 this->particlesToRender = (int)(this->particles.length * str);
 }

 bool requiresUpdate() {
 return this->particlesToRender > 0 || this->particlesReqUpdCnt > 0;
 }

 void update(float delta) {
 this->particlesReqUpdCnt = 0;

 for (int int0 = 0; int0 < this->particles.length; int0++) {
 WeatherParticle weatherParticle = this->particles[int0];
 if (int0 < this->particlesToRender) {
 weatherParticle.alphaFadeMod.setTarget(1.0F);
 } else if (int0 >= this->particlesToRender) {
 weatherParticle.alphaFadeMod.setTarget(0.0F);
 }

 weatherParticle.update(delta);
 if (weatherParticle.renderAlpha > 0.0F) {
 this->particlesReqUpdCnt++;
 }
 }
 }

 void render() {
 int int0 = IsoCamera.frameState.playerIndex;
 int int1 = IsoCamera.frameState.OffscreenWidth;
 int int2 = IsoCamera.frameState.OffscreenHeight;
 int int3 = (int)Math.ceil(int1 / this->width) + 2;
 int int4 = (int)Math.ceil(int2 / this->height) + 2;
 int int5;
 if (IsoCamera.frameState.OffX >= 0.0F) {
 int5 = (int)IsoCamera.frameState.OffX % this->width;
 } else {
 int5 = this->width - (int)Math.abs(IsoCamera.frameState.OffX) % this->width;
 }

 int int6;
 if (IsoCamera.frameState.OffY >= 0.0F) {
 int6 = (int)IsoCamera.frameState.OffY % this->height;
 } else {
 int6 = this->height - (int)Math.abs(IsoCamera.frameState.OffY) % this->height;
 }

 int int7 = -int5;
 int int8 = -int6;

 for (int int9 = -1; int9 < int4; int9++) {
 for (int int10 = -1; int10 < int3; int10++) {
 int int11 = int7 + int10 * this->width;
 int int12 = int8 + int9 * this->height;
 if (this->DEBUG_BOUNDS || IsoWeatherFX.DEBUG_BOUNDS) {
 LineDrawer.drawRect(int11, int12, this->width, this->height, 0.0F, 1.0F, 0.0F, 1.0F, 1);
 }

 for (int int13 = 0; int13 < this->particles.length; int13++) {
 WeatherParticle weatherParticle = this->particles[int13];
 if (!(weatherParticle.renderAlpha <= 0.0F) && weatherParticle.isOnScreen(int11, int12) {
 weatherParticle.render(int11, int12);
 if (this->DEBUG_BOUNDS || IsoWeatherFX.DEBUG_BOUNDS) {
 LineDrawer.drawRect(
 int11 + weatherParticle.bounds.getX(),
 int12 + weatherParticle.bounds.getY(),
 weatherParticle.bounds.getWidth(),
 weatherParticle.bounds.getHeight(),
 0.0F,
 0.0F,
 1.0F,
 0.5F,
 1
 );
 }
 }
 }
 }
 }
 }
}
} // namespace fx
} // namespace weather
} // namespace iso
} // namespace zombie
