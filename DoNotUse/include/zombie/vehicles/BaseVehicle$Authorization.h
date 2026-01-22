#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace zombie {
namespace vehicles {


enum class BaseVehicle {
   Server,
   LocalCollide,
   RemoteCollide,
   Local,
   Remote;

   private static const std::unordered_map<uint8_t, BaseVehicle$Authorization> authorizations = std::make_unique<std::unordered_map<>>();

   public static BaseVehicle$Authorization valueOf(byte var0) {
      return authorizations.getOrDefault(var0, Server);
   }

    uint8_t index() {
      return (byte)this.ordinal();
   }

   static {
      Arrays.stream(values()).forEach(var0 -> authorizations.put(var0.index(), var0));
   }
}
} // namespace vehicles
} // namespace zombie
