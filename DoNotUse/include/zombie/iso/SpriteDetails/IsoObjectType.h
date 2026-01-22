#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace iso {
namespace SpriteDetails {


enum class IsoObjectType {
   normal(0),
   jukebox(1),
   wall(2),
   stairsTW(3),
   stairsTN(4),
   stairsMW(5),
   stairsMN(6),
   stairsBW(7),
   stairsBN(8),
   UNUSED9(9),
   UNUSED10(10),
   doorW(11),
   doorN(12),
   lightswitch(13),
   radio(14),
   curtainN(15),
   curtainS(16),
   curtainW(17),
   curtainE(18),
   doorFrW(19),
   doorFrN(20),
   tree(21),
   windowFN(22),
   windowFW(23),
   UNUSED24(24),
   WestRoofB(25),
   WestRoofM(26),
   WestRoofT(27),
   isMoveAbleObject(28),
   MAX(29);

    const int index;
   private static const std::unordered_map<std::string, IsoObjectType> fromStringMap = std::make_unique<std::unordered_map<>>();

    private IsoObjectType(int var3) {
      this.index = var3;
   }

    int index() {
      return this.index;
   }

    static IsoObjectType fromIndex(int var0) {
      return IsoObjectType.class.getEnumConstants()[var0];
   }

    static IsoObjectType FromString(const std::string& var0) {
    IsoObjectType var1 = fromStringMap.get(var0);
    return var1 = = nullptr ? MAX : var1;
   }

   static {
      for (IsoObjectType var3 : values()) {
         if (var3 == MAX) {
            break;
         }

         fromStringMap.put(var3.name(), var3);
      }
   }
}
} // namespace SpriteDetails
} // namespace iso
} // namespace zombie
