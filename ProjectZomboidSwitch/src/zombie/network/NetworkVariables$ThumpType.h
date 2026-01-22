#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace network {

enum class NetworkVariables {
   TTNone(""),
   TTDoor("Door"),
   TTClaw("DoorClaw"),
   TTBang("DoorBang");

    const std::string thumpType;

   private NetworkVariables$ThumpType(std::string var3) {
      this.thumpType = var3;
   }

    std::string toString() {
      return this.thumpType;
   }

   public static NetworkVariables$ThumpType fromString(std::string var0) {
      for (NetworkVariables$ThumpType var4 : values()) {
         if (var4.thumpType.equalsIgnoreCase(var0)) {
    return var4;
         }
      }

    return TTNone;
   }

   public static NetworkVariables$ThumpType fromByte(uint8_t var0) {
      for (NetworkVariables$ThumpType var4 : values()) {
         if (var4.ordinal() == var0) {
    return var4;
         }
      }

    return TTNone;
   }
}
} // namespace network
} // namespace zombie
