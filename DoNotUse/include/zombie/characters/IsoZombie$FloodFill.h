#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ai/astar/Mover.h"
#include "zombie/core/Rand.h"
#include "zombie/core/utils/BooleanGrid.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/SpriteDetails/IsoObjectType.h"
#include "zombie/iso/areas/IsoBuilding.h"
#include <algorithm>

namespace zombie {
namespace characters {


class IsoZombie {
public:
    IsoGridSquare start = nullptr;
    const int FLOOD_SIZE = 11;
    const BooleanGrid visited = std::make_shared<BooleanGrid>(11, 11);
   private const std::stack<IsoGridSquare> stack = std::make_unique<std::stack<>>();
    IsoBuilding building = nullptr;
    Mover mover = nullptr;
   private const std::vector<IsoGridSquare> choices = new std::vector<>(121);

   private IsoZombie$FloodFill() {
   }

    void calculate(Mover var1, IsoGridSquare var2) {
      this.start = var2;
      this.mover = var1;
      if (this.start.getRoom() != nullptr) {
         this.building = this.start.getRoom().getBuilding();
      }

    bool var3 = false;
    bool var4 = false;
      this.push(this.start.getX(), this.start.getY());

      while ((var2 = this.pop()) != nullptr) {
    int var6 = var2.getX();
    int var5 = var2.getY();

         while (this.shouldVisit(var6, var5, var6, var5 - 1)) {
            var5--;
         }

         var4 = false;
         var3 = false;

         do {
            this.visited.setValue(this.gridX(var6), this.gridY(var5), true);
    IsoGridSquare var7 = IsoWorld.instance.CurrentCell.getGridSquare(var6, var5, this.start.getZ());
            if (var7 != nullptr) {
               this.choices.push_back(var7);
            }

            if (!var3 && this.shouldVisit(var6, var5, var6 - 1, var5)) {
               this.push(var6 - 1, var5);
               var3 = true;
            } else if (var3 && !this.shouldVisit(var6, var5, var6 - 1, var5)) {
               var3 = false;
            } else if (var3 && !this.shouldVisit(var6 - 1, var5, var6 - 1, var5 - 1)) {
               this.push(var6 - 1, var5);
            }

            if (!var4 && this.shouldVisit(var6, var5, var6 + 1, var5)) {
               this.push(var6 + 1, var5);
               var4 = true;
            } else if (var4 && !this.shouldVisit(var6, var5, var6 + 1, var5)) {
               var4 = false;
            } else if (var4 && !this.shouldVisit(var6 + 1, var5, var6 + 1, var5 - 1)) {
               this.push(var6 + 1, var5);
            }

            var5++;
         } while (this.shouldVisit(var6, var5 - 1, var6, var5));
      }
   }

    bool shouldVisit(int var1, int var2, int var3, int var4) {
      if (this.gridX(var3) < 11 && this.gridX(var3) >= 0) {
         if (this.gridY(var4) < 11 && this.gridY(var4) >= 0) {
            if (this.visited.getValue(this.gridX(var3), this.gridY(var4))) {
    return false;
            } else {
    IsoGridSquare var5 = IsoWorld.instance.CurrentCell.getGridSquare(var3, var4, this.start.getZ());
               if (var5 == nullptr) {
    return false;
               } else if (var5.Has(IsoObjectType.stairsBN) || var5.Has(IsoObjectType.stairsMN) || var5.Has(IsoObjectType.stairsTN)) {
    return false;
               } else if (var5.Has(IsoObjectType.stairsBW) || var5.Has(IsoObjectType.stairsMW) || var5.Has(IsoObjectType.stairsTW)) {
    return false;
               } else if (var5.getRoom() != nullptr && this.building == nullptr) {
    return false;
               } else {
                  return var5.getRoom() == nullptr && this.building != nullptr
                     ? false
                     : !IsoWorld.instance.CurrentCell.blocked(this.mover, var3, var4, this.start.getZ(), var1, var2, this.start.getZ());
               }
            }
         } else {
    return false;
         }
      } else {
    return false;
      }
   }

    void push(int var1, int var2) {
    IsoGridSquare var3 = IsoWorld.instance.CurrentCell.getGridSquare(var1, var2, this.start.getZ());
      this.stack.push(var3);
   }

    IsoGridSquare pop() {
      return this.stack.empty() ? nullptr : this.stack.pop();
   }

    int gridX(int var1) {
      return var1 - (this.start.getX() - 5);
   }

    int gridY(int var1) {
      return var1 - (this.start.getY() - 5);
   }

    int gridX(IsoGridSquare var1) {
      return var1.getX() - (this.start.getX() - 5);
   }

    int gridY(IsoGridSquare var1) {
      return var1.getY() - (this.start.getY() - 5);
   }

    IsoGridSquare choose() {
      if (this.choices.empty()) {
    return nullptr;
      } else {
    int var1 = Rand.Next(this.choices.size());
         return this.choices.get(var1);
      }
   }

    void reset() {
      this.building = nullptr;
      this.choices.clear();
      this.stack.clear();
      this.visited.clear();
   }
}
} // namespace characters
} // namespace zombie
