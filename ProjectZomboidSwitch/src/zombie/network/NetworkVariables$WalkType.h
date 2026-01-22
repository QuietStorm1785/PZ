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
   WT1("1"),
   WT2("2"),
   WT3("3"),
   WT4("4"),
   WT5("5"),
   WTSprint1("sprint1"),
   WTSprint2("sprint2"),
   WTSprint3("sprint3"),
   WTSprint4("sprint4"),
   WTSprint5("sprint5"),
   WTSlow1("slow1"),
   WTSlow2("slow2"),
   WTSlow3("slow3");

    const std::string walkType;

   private NetworkVariables$WalkType(std::string var3) {
      this.walkType = var3;
   }

    std::string toString() {
      return this.walkType;
   }

   public static NetworkVariables$WalkType fromString(std::string var0) {
      for (NetworkVariables$WalkType var4 : values()) {
         if (var4.walkType.equalsIgnoreCase(var0)) {
    return var4;
         }
      }

    return WT1;
   }

   public static NetworkVariables$WalkType fromByte(byte var0) {
      for (NetworkVariables$WalkType var4 : values()) {
         if (var4.ordinal() == var0) {
    return var4;
         }
      }

    return WT1;
   }
}
} // namespace network
} // namespace zombie
