#pragma once
#include "zombie/iso/RoomDef.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class BaseAmbientStreamManager {
public:
public
 void stop();

public
 void doAlarm(RoomDef room);

public
 void doGunEvent();

public
 void init();

public
 void addBlend(String name, float vol, boolean bIndoors,
 boolean bRain, boolean bNight, boolean bDay);

protected
 void addRandomAmbient();

public
 void doOneShotAmbients();

public
 void update();

public
 void addAmbient(String name, int x, int y, int radius, float volume);

public
 void addAmbientEmitter(float x, float y, int z, String name);

public
 void addDaytimeAmbientEmitter(float x, float y, int z, String name);
}
} // namespace zombie
