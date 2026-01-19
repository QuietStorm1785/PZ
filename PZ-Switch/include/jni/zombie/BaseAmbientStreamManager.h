#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/RoomDef.h"

namespace zombie {


class BaseAmbientStreamManager {
:
    abstract void stop();

    abstract void doAlarm(RoomDef var1);

    abstract void doGunEvent();

    abstract void init();

    abstract void addBlend(String var1, float var2, boolean var3, boolean var4, boolean var5, boolean var6);

   protected abstract void addRandomAmbient();

    abstract void doOneShotAmbients();

    abstract void update();

    abstract void addAmbient(String var1, int var2, int var3, int var4, float var5);

    abstract void addAmbientEmitter(float var1, float var2, int var3, String var4);

    abstract void addDaytimeAmbientEmitter(float var1, float var2, int var3, String var4);
}
} // namespace zombie
