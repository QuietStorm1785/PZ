#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace utils {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class UpdateLimit {
public:
 long delay;
 long last;
 long lastPeriod;

 public UpdateLimit(long ms) {
 this->delay = ms;
 this->last = System.currentTimeMillis();
 this->lastPeriod = this->last;
 }

 public UpdateLimit(long ms, long shift) {
 this->delay = ms;
 this->last = System.currentTimeMillis() - shift;
 this->lastPeriod = this->last;
 }

 void BlockCheck() {
 this->last = System.currentTimeMillis() + this->delay;
 }

 void Reset(long ms) {
 this->delay = ms;
 this->Reset();
 }

 void Reset() {
 this->last = System.currentTimeMillis();
 this->lastPeriod = System.currentTimeMillis();
 }

 void setUpdatePeriod(long ms) {
 this->delay = ms;
 }

 void setSmoothUpdatePeriod(long ms) {
 this->delay = (long)((float)this->delay + 0.1F * (float)(ms - this->delay);
 }

 bool Check() {
 long long0 = System.currentTimeMillis();
 if (long0 - this->last > this->delay) {
 if (long0 - this->last > 3L * this->delay) {
 this->last = long0;
 } else {
 this->last = this->last + this->delay;
 }

 return true;
 } else {
 return false;
 }
 }

 long getLast() {
 return this->last;
 }

 void updateTimePeriod() {
 long long0 = System.currentTimeMillis();
 if (long0 - this->last > this->delay) {
 if (long0 - this->last > 3L * this->delay) {
 this->last = long0;
 } else {
 this->last = this->last + this->delay;
 }
 }

 this->lastPeriod = long0;
 }

 double getTimePeriod() {
 return Math.min(((double)System.currentTimeMillis() - this->lastPeriod) / this->delay, 1.0);
 }

 long getDelay() {
 return this->delay;
 }
}
} // namespace utils
} // namespace core
} // namespace zombie
