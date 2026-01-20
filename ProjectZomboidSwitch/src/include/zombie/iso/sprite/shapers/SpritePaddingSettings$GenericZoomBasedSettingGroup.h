#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Core.h"

namespace zombie {
namespace iso {
namespace sprite {
namespace shapers {


class SpritePaddingSettings {
public:
   public abstract <ZoomBasedSetting> ZoomBasedSetting getCurrentZoomSetting();

   public static <ZoomBasedSetting> ZoomBasedSetting getCurrentZoomSetting(ZoomBasedSetting var0, ZoomBasedSetting var1, ZoomBasedSetting var2) {
    float var3 = Core.getInstance().getCurrentPlayerZoom();
      if (var3 < 1.0F) {
         return (ZoomBasedSetting)var0;
      } else {
         return (ZoomBasedSetting)(var3 == 1.0F ? var1 : var2);
      }
   }
}
} // namespace shapers
} // namespace sprite
} // namespace iso
} // namespace zombie
