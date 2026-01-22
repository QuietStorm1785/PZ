#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoSurvivor.h"
#include "zombie/characters/IsoZombie.h"
#include <iterator>

namespace zombie {
namespace iso {


class IsoWorld {
public:
   public std::vector<int> xPos;
   public std::vector<int> yPos;
   public std::vector<int> Type;

   public IsoWorld$Frame(IsoWorld var1) {
      this.this$0 = var1;
      this.xPos = std::make_unique<std::vector<>>();
      this.yPos = std::make_unique<std::vector<>>();
      this.Type = std::make_unique<std::vector<>>();
    Iterator var2 = IsoWorld.instance.CurrentCell.getObjectList().iterator();

      while (var2 != nullptr && var2.hasNext()) {
    IsoMovingObject var3 = (IsoMovingObject)var2.next();
    uint8_t var4 = 2;
         if (dynamic_cast<IsoPlayer*>(var3) != nullptr) {
            var4 = 0;
         } else if (dynamic_cast<IsoSurvivor*>(var3) != nullptr) {
            var4 = 1;
         } else {
            if (!(dynamic_cast<IsoZombie*>(var3) != nullptr) || ((IsoZombie)var3).Ghost) {
               continue;
            }

            var4 = 2;
         }

         this.xPos.push_back((int)var3.getX());
         this.yPos.push_back((int)var3.getY());
         this.Type.push_back(int.valueOf(var4));
      }
   }
}
} // namespace iso
} // namespace zombie
