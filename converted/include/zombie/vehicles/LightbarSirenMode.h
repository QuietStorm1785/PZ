#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/scripting/objects/VehicleScript.h"

namespace zombie {
namespace vehicles {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


/**
 * Created by kroto on 9/20/2017.
 */
class LightbarSirenMode {
public:
 int mode = 0;
 const int modeMax = 3;

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
 }
 }

 bool isEnable() {
 return this->mode != 0;
 }

 std::string getSoundName(VehicleScript.LightBar lightbar) {
 if (this->isEnable()) {
 if (this->mode == 1) {
 return lightbar.soundSiren0;
 }

 if (this->mode == 2) {
 return lightbar.soundSiren1;
 }

 if (this->mode == 3) {
 return lightbar.soundSiren2;
 }
 }

 return "";
 }
}
} // namespace vehicles
} // namespace zombie
