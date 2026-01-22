#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/annotation/XmlRootElement.h"
#include "zombie/iso/sprite/shapers/FloorShaperDeDiamond/Settings.h"
#include "zombie/iso/sprite/shapers/SpritePadding/IsoPaddingSettings.h"

namespace zombie {
namespace iso {
namespace sprite {
namespace shapers {


class SpritePaddingSettings {
public:
    IsoPaddingSettings IsoPadding = std::make_shared<IsoPaddingSettings>();
    Settings FloorDeDiamond = std::make_shared<Settings>();
   public zombie.iso.sprite.shapers.FloorShaperAttachedSprites.Settings AttachedSprites = new zombie.iso.sprite.shapers.FloorShaperAttachedSprites.Settings();
}
} // namespace shapers
} // namespace sprite
} // namespace iso
} // namespace zombie
