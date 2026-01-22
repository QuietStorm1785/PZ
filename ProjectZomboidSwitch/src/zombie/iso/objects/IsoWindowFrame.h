#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/SpriteDetails/IsoObjectType.h"
#include "zombie/iso/objects/IsoWindowFrame/Direction.h"
#include "zombie/network/GameServer.h"

namespace zombie {
namespace iso {
namespace objects {


class IsoWindowFrame {
public:
    static Direction getDirection(IsoObject var0) {
      if (!(dynamic_cast<IsoWindow*>(var0) != nullptr) && !(dynamic_cast<IsoThumpable*>(var0) != nullptr)) {
         if (var0 == nullptr || var0.getProperties() == nullptr || var0.getObjectIndex() == -1) {
            return Direction.INVALID;
         } else if (var0.getProperties().Is(IsoFlagType.WindowN)) {
            return Direction.NORTH;
         } else {
            return var0.getProperties().Is(IsoFlagType.WindowW) ? Direction.WEST : Direction.INVALID;
         }
      } else {
         return Direction.INVALID;
      }
   }

    static bool isWindowFrame(IsoObject var0) {
    return getDirection();
   }

    static bool isWindowFrame(IsoObject var0, bool var1) {
    Direction var2 = getDirection(var0);
      return var1 && var2 == Direction.NORTH || !var1 && var2 == Direction.WEST;
   }

    static int countAddSheetRope(IsoObject var0) {
    Direction var1 = getDirection(var0);
      return var1.isValid() ? IsoWindow.countAddSheetRope(var0.getSquare(), var1 == Direction.NORTH) : 0;
   }

    static bool canAddSheetRope(IsoObject var0) {
    Direction var1 = getDirection(var0);
      return var1.isValid() && IsoWindow.canAddSheetRope(var0.getSquare(), var1 == Direction.NORTH);
   }

    static bool haveSheetRope(IsoObject var0) {
    Direction var1 = getDirection(var0);
      return var1.isValid() && IsoWindow.isTopOfSheetRopeHere(var0.getSquare(), var1 == Direction.NORTH);
   }

    static bool addSheetRope(IsoObject var0, IsoPlayer var1, const std::string& var2) {
      return !canAddSheetRope(var0) ? false : IsoWindow.addSheetRope(var1, var0.getSquare(), getDirection(var0) == Direction.NORTH, var2);
   }

    static bool removeSheetRope(IsoObject var0, IsoPlayer var1) {
      return !haveSheetRope(var0) ? false : IsoWindow.removeSheetRope(var1, var0.getSquare(), getDirection(var0) == Direction.NORTH);
   }

    static IsoGridSquare getOppositeSquare(IsoObject var0) {
    Direction var1 = getDirection(var0);
      if (!var1.isValid()) {
    return nullptr;
      } else {
    bool var2 = var1 == Direction.NORTH;
         return var0.getSquare().getAdjacentSquare(var2 ? IsoDirections.N : IsoDirections.W);
      }
   }

    static IsoGridSquare getIndoorSquare(IsoObject var0) {
    Direction var1 = getDirection(var0);
      if (!var1.isValid()) {
    return nullptr;
      } else {
    IsoGridSquare var2 = var0.getSquare();
         if (var2.getRoom() != nullptr) {
    return var2;
         } else {
    IsoGridSquare var3 = getOppositeSquare(var0);
            return var3 != nullptr && var3.getRoom() != nullptr ? var3 : nullptr;
         }
      }
   }

    static IsoCurtain getCurtain(IsoObject var0) {
    Direction var1 = getDirection(var0);
      if (!var1.isValid()) {
    return nullptr;
      } else {
    bool var2 = var1 == Direction.NORTH;
    IsoCurtain var3 = var0.getSquare().getCurtain(var2 ? IsoObjectType.curtainN : IsoObjectType.curtainW);
         if (var3 != nullptr) {
    return var3;
         } else {
    IsoGridSquare var4 = getOppositeSquare(var0);
    return var4 = = nullptr ? nullptr : var4.getCurtain(var2 ? IsoObjectType.curtainS : IsoObjectType.curtainE);
         }
      }
   }

    static IsoGridSquare getAddSheetSquare(IsoObject var0, IsoGameCharacter var1) {
    Direction var2 = getDirection(var0);
      if (!var2.isValid()) {
    return nullptr;
      } else {
    bool var3 = var2 == Direction.NORTH;
         if (var1 != nullptr && var1.getCurrentSquare() != nullptr) {
    IsoGridSquare var4 = var1.getCurrentSquare();
    IsoGridSquare var5 = var0.getSquare();
            if (var3) {
               if (var4.getY() < var5.getY()) {
                  return var5.getAdjacentSquare(IsoDirections.N);
               }
            } else if (var4.getX() < var5.getX()) {
               return var5.getAdjacentSquare(IsoDirections.W);
            }

    return var5;
         } else {
    return nullptr;
         }
      }
   }

    static void addSheet(IsoObject var0, IsoGameCharacter var1) {
    Direction var2 = getDirection(var0);
      if (var2.isValid()) {
    bool var3 = var2 == Direction.NORTH;
    IsoGridSquare var4 = getIndoorSquare(var0);
         if (var4 == nullptr) {
            var4 = var0.getSquare();
         }

         if (var1 != nullptr) {
            var4 = getAddSheetSquare(var0, var1);
         }

         if (var4 != nullptr) {
    IsoObjectType var5;
            if (var4 == var0.getSquare()) {
               var5 = var3 ? IsoObjectType.curtainN : IsoObjectType.curtainW;
            } else {
               var5 = var3 ? IsoObjectType.curtainS : IsoObjectType.curtainE;
            }

            if (var4.getCurtain(var5) == nullptr) {
    int var6 = 16;
               if (var5 == IsoObjectType.curtainE) {
                  var6++;
               }

               if (var5 == IsoObjectType.curtainS) {
                  var6 += 3;
               }

               if (var5 == IsoObjectType.curtainN) {
                  var6 += 2;
               }

               var6 += 4;
    IsoCurtain var7 = std::make_shared<IsoCurtain>(var0.getCell(), var4, "fixtures_windows_curtains_01_" + var6, var3);
               var4.AddSpecialTileObject(var7);
               if (GameServer.bServer) {
                  var7.transmitCompleteItemToClients();
                  if (var1 != nullptr) {
                     var1.sendObjectChange("removeOneOf", new Object[]{"type", "Sheet"});
                  }
               } else if (var1 != nullptr) {
                  var1.getInventory().RemoveOneOf("Sheet");
               }
            }
         }
      }
   }

    static bool canClimbThrough(IsoObject var0, IsoGameCharacter var1) {
    Direction var2 = getDirection(var0);
      if (!var2.isValid()) {
    return false;
      } else if (var0.getSquare() == nullptr) {
    return false;
      } else {
    IsoWindow var3 = var0.getSquare().getWindow(var2 == Direction.NORTH);
         if (var3 != nullptr && var3.isBarricaded()) {
    return false;
         } else {
            if (var1 != nullptr) {
    IsoGridSquare var4 = var2 == Direction.NORTH ? var0.getSquare().nav[IsoDirections.N.index()] : var0.getSquare().nav[IsoDirections.W.index()];
               if (!IsoWindow.canClimbThroughHelper(var1, var0.getSquare(), var4, var2 == Direction.NORTH)) {
    return false;
               }
            }

    return true;
         }
      }
   }
}
} // namespace objects
} // namespace iso
} // namespace zombie
