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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


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
 private static HashMap<String, IsoObjectType> fromStringMap = std::make_unique<HashMap<>>();

 private IsoObjectType(int int1) {
 this->index = int1;
 }

 int index() {
 return this->index;
 }

 static IsoObjectType fromIndex(int value) {
 return IsoObjectType.class.getEnumConstants()[value];
 }

 static IsoObjectType FromString(const std::string& str) {
 IsoObjectType objectType = fromStringMap.get(str);
 return objectType = = nullptr ? MAX : objectType;
 }

 static {
 for (IsoObjectType objectType : values()) {
 if (objectType == MAX) {
 break;
 }

 fromStringMap.put(objectType.name(), objectType);
 }
 }
}
} // namespace SpriteDetails
} // namespace iso
} // namespace zombie
