#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Core.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/sprite/IsoDirectionFrame.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/network/GameServer.h"

namespace zombie {
namespace erosion {
namespace obj {


class ErosionObjSprites {
public:
   public const std::vector<std::string> sprites = std::make_unique<std::vector<>>();
    int index = -1;

   public ErosionObjSprites$Sprites(std::string var1) {
      if (Core.bDebug || GameServer.bServer && GameServer.bDebug) {
    IsoSprite var2 = IsoSpriteManager.instance.getSprite(var1);
         if (var2.CurrentAnim.Frames.size() == 0
            || !GameServer.bServer && ((IsoDirectionFrame)var2.CurrentAnim.Frames.get(0)).getTexture(IsoDirections.N) == nullptr
            || var2.ID < 10000) {
            DebugLog.log("EMPTY SPRITE " + var1);
         }
      }

      this.sprites.push_back(var1);
   }

   public ErosionObjSprites$Sprites(std::vector<std::string> var1) {
      if (Core.bDebug || GameServer.bServer && GameServer.bDebug) {
         for (int var2 = 0; var2 < var1.size(); var2++) {
    IsoSprite var3 = IsoSpriteManager.instance.getSprite((std::string)var1.get(var2));
            if (var3.CurrentAnim.Frames.size() == 0
               || !GameServer.bServer && ((IsoDirectionFrame)var3.CurrentAnim.Frames.get(0)).getTexture(IsoDirections.N) == nullptr
               || var3.ID < 10000) {
               DebugLog.log("EMPTY SPRITE " + (std::string)var1.get(var2));
            }
         }
      }

      this.sprites.addAll(var1);
   }

    std::string getNext() {
      if (++this.index >= this.sprites.size()) {
         this.index = 0;
      }

      return this.sprites.get(this.index);
   }
}
} // namespace obj
} // namespace erosion
} // namespace zombie
