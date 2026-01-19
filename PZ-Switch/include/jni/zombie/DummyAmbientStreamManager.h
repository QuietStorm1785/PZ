#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/RoomDef.h"

namespace zombie {


class DummyAmbientStreamManager :  BaseAmbientStreamManager {
:
    void stop() {
   }

    void doAlarm(RoomDef var1) {
   }

    void doGunEvent() {
   }

    void init() {
   }

    void addBlend(std::string_view var1, float var2, bool var3, bool var4, bool var5, bool var6) {
   }

    void addRandomAmbient() {
   }

    void doOneShotAmbients() {
   }

    void update() {
   }

    void addAmbient(std::string_view var1, int var2, int var3, int var4, float var5) {
   }

    void addAmbientEmitter(float var1, float var2, int var3, std::string_view var4) {
   }

    void addDaytimeAmbientEmitter(float var1, float var2, int var3, std::string_view var4) {
   }
}
} // namespace zombie
