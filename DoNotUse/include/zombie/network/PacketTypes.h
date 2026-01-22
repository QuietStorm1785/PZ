#pragma once
#include <map>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/PacketTypes/PacketType.h"

namespace zombie {
namespace network {


class PacketTypes {
public:
    static const short ContainerDeadBody = 0;
    static const short ContainerWorldObject = 1;
    static const short ContainerObject = 2;
    static const short ContainerVehicle = 3;
   public static const Map<int16_t, PacketType> packetTypes = std::make_unique<std::map<>>();
    static const KahluaTable packetCountTable = LuaManager.platform.newTable();

    static void doPingPacket(ByteBufferWriter var0) {
      var0.putInt(28);
   }

    static KahluaTable getPacketCounts(int var0) {
      packetCountTable.wipe();
      if (GameClient.bClient) {
         for (PacketType var2 : packetTypes.values()) {
            if (var0 == 1) {
               packetCountTable.rawset(std::string.format("%03d-%s", var2.id, var2.name()), std::string.valueOf(var2.serverPacketCount));
            } else {
               packetCountTable.rawset(std::string.format("%03d-%s", var2.id, var2.name()), std::string.valueOf(var2.clientPacketCount));
            }
         }
      }

    return packetCountTable;
   }

   static {
      for (PacketType var3 : PacketType.values()) {
    PacketType var4 = packetTypes.put(var3.getId(), var3);
         if (var4 != nullptr) {
            DebugLog.Multiplayer.error(std::string.format("PacketType: duplicate \"%s\" \"%s\" id=%d", var4.name(), var3.name(), var3.getId()));
         }
      }
   }
}
} // namespace network
} // namespace zombie
