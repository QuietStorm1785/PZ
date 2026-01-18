#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace ui {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class UITransition {
public:
 float duration;
 float elapsed;
 float frac;
 bool fadeOut;
 bool bIgnoreUpdateTime = false;
 long updateTimeMS;
 static long currentTimeMS;
 static long elapsedTimeMS;

 static void UpdateAll() {
 long long0 = System.currentTimeMillis();
 elapsedTimeMS = long0 - currentTimeMS;
 currentTimeMS = long0;
 }

 public UITransition() {
 this->duration = 100.0F;
 }

 void init(float _duration, bool _fadeOut) {
 this->duration = Math.max(_duration, 1.0F);
 if (this->frac >= 1.0F) {
 this->elapsed = 0.0F;
 } else if (this->fadeOut != _fadeOut) {
 this->elapsed = (1.0F - this->frac) * this->duration;
 } else {
 this->elapsed = this->frac * this->duration;
 }

 this->fadeOut = _fadeOut;
 }

 void update() {
 if (!this->bIgnoreUpdateTime && this->updateTimeMS != 0L) {
 long long0 = (long)this->duration;
 if (this->updateTimeMS + long0 < currentTimeMS) {
 this->elapsed = this->duration;
 }
 }

 this->updateTimeMS = currentTimeMS;
 this->frac = this->elapsed / this->duration;
 this->elapsed = Math.min(this->elapsed + (float)elapsedTimeMS, this->duration);
 }

 float fraction() {
 return this->fadeOut ? 1.0F - this->frac : this->frac;
 }

 void setFadeIn(bool fadeIn) {
 if (fadeIn) {
 if (this->fadeOut) {
 this->init(100.0F, false);
 }
 } else if (!this->fadeOut) {
 this->init(200.0F, true);
 }
 }

 void reset() {
 this->elapsed = 0.0F;
 }

 void setIgnoreUpdateTime(bool ignore) {
 this->bIgnoreUpdateTime = ignore;
 }

 float getElapsed() {
 return this->elapsed;
 }

 void setElapsed(float _elapsed) {
 this->elapsed = _elapsed;
 }
}
} // namespace ui
} // namespace zombie
