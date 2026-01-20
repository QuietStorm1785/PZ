#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/annotation/XmlType.h"
#include "zombie/iso/sprite/shapers/FloorShaperDeDiamond/Settings/BorderSetting.h"
#include "zombie/iso/sprite/shapers/SpritePaddingSettings/GenericZoomBasedSettingGroup.h"

namespace zombie {
namespace iso {
namespace sprite {
namespace shapers {


class FloorShaperDeDiamond {
public:
    BorderSetting ZoomedIn = std::make_shared<BorderSetting>(2.0F, 1.0F, 2.0F, 0.01F);
    BorderSetting NotZoomed = std::make_shared<BorderSetting>(2.0F, 1.0F, 2.0F, 0.01F);
    BorderSetting ZoomedOut = std::make_shared<BorderSetting>(2.0F, 0.0F, 2.5F, 0.0F);

    BorderSetting getCurrentZoomSetting() {
      return (BorderSetting)getCurrentZoomSetting(this.ZoomedIn, this.NotZoomed, this.ZoomedOut);
   }
}
} // namespace shapers
} // namespace sprite
} // namespace iso
} // namespace zombie
