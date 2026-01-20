#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/annotation/XmlType.h"
#include "zombie/iso/sprite/shapers/FloorShaperAttachedSprites/Settings/ASBorderSetting.h"
#include "zombie/iso/sprite/shapers/SpritePaddingSettings/GenericZoomBasedSettingGroup.h"

namespace zombie {
namespace iso {
namespace sprite {
namespace shapers {


class FloorShaperAttachedSprites {
public:
    ASBorderSetting ZoomedIn = std::make_shared<ASBorderSetting>(2.0F, 1.0F, 3.0F, 0.01F);
    ASBorderSetting NotZoomed = std::make_shared<ASBorderSetting>(2.0F, 1.0F, 3.0F, 0.01F);
    ASBorderSetting ZoomedOut = std::make_shared<ASBorderSetting>(2.0F, 0.0F, 2.5F, 0.0F);

    ASBorderSetting getCurrentZoomSetting() {
      return (ASBorderSetting)getCurrentZoomSetting(this.ZoomedIn, this.NotZoomed, this.ZoomedOut);
   }
}
} // namespace shapers
} // namespace sprite
} // namespace iso
} // namespace zombie
