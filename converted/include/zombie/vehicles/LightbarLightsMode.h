#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace vehicles {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

/**
 * Created by kroto on 9/20/2017.
 */
class LightbarLightsMode {
public:
 long startTime = 0L;
 int light = 0;
 const int modeMax = 3;
 int mode = 0;

 int get() {
 return this->mode;
 }

 void set(int v) {
 if (v > 3) {
 this->mode = 3;
 } else if (v < 0) {
 this->mode = 0;
 } else {
 this->mode = v;
 if (this->mode != 0) {
 this->start();
 }
 }
 }

 void start() {
 this->startTime = System.currentTimeMillis();
 }

 void update() {
 long long0 = System.currentTimeMillis() - this->startTime;
 switch (this->mode) {
 case 1:
 long0 %= 1000L;
 if (long0 < 50L) {
 this->light = 0;
 } else if (long0 < 450L) {
 this->light = 1;
 } else if (long0 < 550L) {
 this->light = 0;
 } else if (long0 < 950L) {
 this->light = 2;
 } else {
 this->light = 0;
 }
 break;
 case 2:
 long0 %= 1000L;
 if (long0 < 50L) {
 this->light = 0;
 } else if (long0 < 250L) {
 this->light = 1;
 } else if (long0 < 300L) {
 this->light = 0;
 } else if (long0 < 500L) {
 this->light = 1;
 } else if (long0 < 550L) {
 this->light = 0;
 } else if (long0 < 750L) {
 this->light = 2;
 } else if (long0 < 800L) {
 this->light = 0;
 } else {
 this->light = 2;
 }
 break;
 case 3:
 long0 %= 300L;
 if (long0 < 25L) {
 this->light = 0;
 } else if (long0 < 125L) {
 this->light = 1;
 } else if (long0 < 175L) {
 this->light = 0;
 } else if (long0 < 275L) {
 this->light = 2;
 } else {
 this->light = 0;
 }
 break;
 default:
 this->light = 0;
 }
 }

 int getLightTexIndex() {
 return this->light;
 }

 bool isEnable() {
 return this->mode != 0;
 }
}
} // namespace vehicles
} // namespace zombie
