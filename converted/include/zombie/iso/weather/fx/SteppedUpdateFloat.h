#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace iso {
namespace weather {
namespace fx {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

/**
 * TurboTuTone.
 */
class SteppedUpdateFloat {
public:
 float current;
 float step;
 float target;
 float min;
 float max;

 public SteppedUpdateFloat(float _current, float _step, float _min, float _max) {
 this->current = _current;
 this->step = _step;
 this->target = _current;
 this->min = _min;
 this->max = _max;
 }

 float value() {
 return this->current;
 }

 void setTarget(float _target) {
 this->target = this->clamp(this->min, this->max, _target);
 }

 float getTarget() {
 return this->target;
 }

 void overrideCurrentValue(float f) {
 this->current = f;
 }

 float clamp(float float2, float float1, float float0) {
 float0 = Math.min(float1, float0);
 return Math.max(float2, float0);
 }

 void update(float delta) {
 if (this->current != this->target) {
 if (this->target > this->current) {
 this->current = this->current + this->step * delta;
 if (this->current > this->target) {
 this->current = this->target;
 }
 } else if (this->target < this->current) {
 this->current = this->current - this->step * delta;
 if (this->current < this->target) {
 this->current = this->target;
 }
 }
 }
 }
}
} // namespace fx
} // namespace weather
} // namespace iso
} // namespace zombie
