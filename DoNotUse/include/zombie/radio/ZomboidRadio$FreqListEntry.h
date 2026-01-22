#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/radio/devices/DeviceData.h"

namespace zombie {
namespace radio {


class ZomboidRadio {
public:
    bool isInvItem = false;
    DeviceData deviceData;
    int sourceX = 0;
    int sourceY = 0;

   public ZomboidRadio$FreqListEntry(boolean var1, DeviceData var2, int var3, int var4) {
      this.isInvItem = var1;
      this.deviceData = var2;
      this.sourceX = var3;
      this.sourceY = var4;
   }
}
} // namespace radio
} // namespace zombie
