#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/sprite/shapers/SpritePadding/IsoPaddingSettings/IsoBorderSetting.h"
#include "zombie/iso/sprite/shapers/SpritePaddingSettings/GenericZoomBasedSettingGroup.h"

namespace zombie {
namespace iso {
namespace sprite {
namespace shapers {


class SpritePadding {
public:
    IsoBorderSetting ZoomedIn = std::make_shared<IsoBorderSetting>(1.0F, 0.99F);
    IsoBorderSetting NotZoomed = std::make_shared<IsoBorderSetting>(1.0F, 0.99F);
    IsoBorderSetting ZoomedOut = std::make_shared<IsoBorderSetting>(2.0F, 0.01F);

    IsoBorderSetting getCurrentZoomSetting() {
      return (IsoBorderSetting)getCurrentZoomSetting(this.ZoomedIn, this.NotZoomed, this.ZoomedOut);
   }
}
} // namespace shapers
} // namespace sprite
} // namespace iso
} // namespace zombie
