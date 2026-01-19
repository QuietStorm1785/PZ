#pragma once
#include "zombie/iso/RoomDef.h"
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class DummyAmbientStreamManager : public BaseAmbientStreamManager {
public:
 void stop() {}

 void doAlarm(RoomDef var1) {}

 void doGunEvent() {}

 void init() {}

 void addBlend(std::string_view var1, float var2, bool var3, bool var4,
 bool var5, bool var6) {}

 void addRandomAmbient() {}

 void doOneShotAmbients() {}

 void update() {}

 void addAmbient(std::string_view var1, int var2, int var3, int var4,
 float var5) {}

 void addAmbientEmitter(float var1, float var2, int var3,
 std::string_view var4) {}

 void addDaytimeAmbientEmitter(float var1, float var2, int var3,
 std::string_view var4) {}
}
} // namespace zombie
