#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace network {

enum class Userlog {
   AdminLog(0),
   Kicked(1),
   Banned(2),
   DupeItem(3),
   LuaChecksum(4),
   WarningPoint(5),
   UnauthorizedPacket(6),
   SuspiciousActivity(7);

    const int index;

   private Userlog$UserlogType(int var3) {
      this.index = var3;
   }

    int index() {
      return this.index;
   }

   public static Userlog$UserlogType fromIndex(int var0) {
      return Userlog$UserlogType.class.getEnumConstants()[var0];
   }

   public static Userlog$UserlogType FromString(std::string var0) {
    return valueOf();
   }
}
} // namespace network
} // namespace zombie
