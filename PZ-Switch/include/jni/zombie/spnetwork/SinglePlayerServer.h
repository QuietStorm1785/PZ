#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaTableIterator.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/globalObjects/SGlobalObjectNetwork.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/objects/IsoWorldInventoryObject.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/PacketTypes.h"
#include "zombie/network/PacketTypes/PacketType.h"
#include "zombie/network/TableNetworkUtils.h"
#include "zombie/spnetwork/SinglePlayerServer/1.h"
#include "zombie/spnetwork/SinglePlayerServer/UdpEngineServer.h"
#include "zombie/vehicles/BaseVehicle.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace spnetwork {


class SinglePlayerServer {
:
   private static ArrayList<ZomboidNetData> MainLoopNetData = std::make_unique<ArrayList<>>();
    static const UdpEngineServer udpEngine = new UdpEngineServer();

    static void addIncoming(short var0, ByteBuffer var1, UdpConnection var2) {
    ZomboidNetData var3;
      if (var1.remaining() > 2048) {
         var3 = ZomboidNetDataPool.instance.getLong(var1.remaining());
      } else {
         var3 = ZomboidNetDataPool.instance.get();
      }

      var3.read(var0, var1, var2);
      synchronized (MainLoopNetData) {
         MainLoopNetData.add(var3);
      }
   }

    static void sendObjectChange(IsoObject var0, std::string_view var1, KahluaTable var2, UdpConnection var3) {
      if (var0.getSquare() != nullptr) {
    ByteBufferWriter var4 = var3.startPacket();
         PacketType.ObjectChange.doPacket(var4);
         if (var0 instanceof IsoPlayer) {
            var4.putByte((byte)1);
            var4.putShort(((IsoPlayer)var0).OnlineID);
         } else if (var0 instanceof BaseVehicle) {
            var4.putByte((byte)2);
            var4.putShort(((BaseVehicle)var0).getId());
         } else if (var0 instanceof IsoWorldInventoryObject) {
            var4.putByte((byte)3);
            var4.putInt(var0.getSquare().getX());
            var4.putInt(var0.getSquare().getY());
            var4.putInt(var0.getSquare().getZ());
            var4.putInt(((IsoWorldInventoryObject)var0).getItem().getID());
         } else {
            var4.putByte((byte)0);
            var4.putInt(var0.getSquare().getX());
            var4.putInt(var0.getSquare().getY());
            var4.putInt(var0.getSquare().getZ());
            var4.putInt(var0.getSquare().getObjects().indexOf(var0));
         }

         var4.putUTF(var1);
         var0.saveChange(var1, var2, var4.bb);
         var3.endPacketImmediate();
      }
   }

    static void sendObjectChange(IsoObject var0, std::string_view var1, KahluaTable var2) {
      if (var0 != nullptr) {
         for (int var3 = 0; var3 < udpEngine.connections.size(); var3++) {
    UdpConnection var4 = (UdpConnection)udpEngine.connections.get(var3);
            if (var4.ReleventTo(var0.getX(), var0.getY())) {
               sendObjectChange(var0, var1, var2, var4);
            }
         }
      }
   }

    static void sendObjectChange(IsoObject var0, std::string_view var1, Object... var2) {
      if (var2.length == 0) {
         sendObjectChange(var0, var1, (KahluaTable)nullptr);
      } else if (var2.length % 2 == 0) {
    KahluaTable var3 = LuaManager.platform.newTable();

         for (byte var4 = 0; var4 < var2.length; var4 += 2) {
    void* var5 = var2[var4 + 1];
            if (var5 instanceof Float) {
               var3.rawset(var2[var4], ((Float)var5).doubleValue());
            } else if (var5 instanceof Integer) {
               var3.rawset(var2[var4], ((Integer)var5).doubleValue());
            } else if (var5 instanceof Short) {
               var3.rawset(var2[var4], ((Short)var5).doubleValue());
            } else {
               var3.rawset(var2[var4], var5);
            }
         }

         sendObjectChange(var0, var1, var3);
      }
   }

    static void sendServerCommand(std::string_view var0, std::string_view var1, KahluaTable var2, UdpConnection var3) {
    ByteBufferWriter var4 = var3.startPacket();
      PacketType.ClientCommand.doPacket(var4);
      var4.putUTF(var0);
      var4.putUTF(var1);
      if (var2 != nullptr && !var2.isEmpty()) {
         var4.putByte((byte)1);

         try {
    KahluaTableIterator var5 = var2.iterator();

            while (var5.advance()) {
               if (!TableNetworkUtils.canSave(var5.getKey(), var5.getValue())) {
                  DebugLog.log("ERROR: sendServerCommand: can't save key,value=" + var5.getKey() + "," + var5.getValue());
               }
            }

            TableNetworkUtils.save(var2, var4.bb);
         } catch (IOException var6) {
            var6.printStackTrace();
         }
      } else {
         var4.putByte((byte)0);
      }

      var3.endPacketImmediate();
   }

    static void sendServerCommand(std::string_view var0, std::string_view var1, KahluaTable var2) {
      for (int var3 = 0; var3 < udpEngine.connections.size(); var3++) {
    UdpConnection var4 = (UdpConnection)udpEngine.connections.get(var3);
         sendServerCommand(var0, var1, var2, var4);
      }
   }

    static void update() {
      if (!GameClient.bClient) {
         for (short var0 = 0; var0 < IsoPlayer.numPlayers; var0++) {
            if (IsoPlayer.players[var0] != nullptr) {
               IsoPlayer.players[var0].setOnlineID(var0);
            }
         }

         synchronized (MainLoopNetData) {
            for (int var1 = 0; var1 < MainLoopNetData.size(); var1++) {
    ZomboidNetData var2 = MainLoopNetData.get(var1);
               mainLoopDealWithNetData(var2);
               MainLoopNetData.remove(var1--);
            }
         }
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    static void mainLoopDealWithNetData(ZomboidNetData var0) {
    ByteBuffer var1 = var0.buffer;

      try {
    PacketType var2 = (PacketType)PacketTypes.packetTypes.get(var0.type);
         switch (1.$SwitchMap$zombie$network$PacketTypes$PacketType[var2.ordinal()]) {
            case 1:
               receiveClientCommand(var1, var0.connection);
               break;
            case 2:
               receiveGlobalObjects(var1, var0.connection);
         }
      } finally {
         ZomboidNetDataPool.instance.discard(var0);
      }
   }

    static IsoPlayer getAnyPlayerFromConnection(UdpConnection var0) {
      for (int var1 = 0; var1 < 4; var1++) {
         if (var0.players[var1] != nullptr) {
            return var0.players[var1];
         }
      }

    return nullptr;
   }

    static IsoPlayer getPlayerFromConnection(UdpConnection var0, int var1) {
      return var1 >= 0 && var1 < 4 ? var0.players[var1] : nullptr;
   }

    static void receiveClientCommand(ByteBuffer var0, UdpConnection var1) {
    uint8_t var2 = var0.get();
    std::string var3 = GameWindow.ReadString(var0);
    std::string var4 = GameWindow.ReadString(var0);
    bool var5 = var0.get() == 1;
    KahluaTable var6 = nullptr;
      if (var5) {
         var6 = LuaManager.platform.newTable();

         try {
            TableNetworkUtils.load(var6, var0);
         } catch (Exception var8) {
            var8.printStackTrace();
            return;
         }
      }

    IsoPlayer var7 = getPlayerFromConnection(var1, var2);
      if (var2 == -1) {
         var7 = getAnyPlayerFromConnection(var1);
      }

      if (var7 == nullptr) {
         DebugLog.log("receiveClientCommand: player is nullptr");
      } else {
         LuaEventManager.triggerEvent("OnClientCommand", var3, var4, var7, var6);
      }
   }

    static void receiveGlobalObjects(ByteBuffer var0, UdpConnection var1) {
    uint8_t var2 = var0.get();
    IsoPlayer var3 = getPlayerFromConnection(var1, var2);
      if (var2 == -1) {
         var3 = getAnyPlayerFromConnection(var1);
      }

      if (var3 == nullptr) {
         DebugLog.log("receiveGlobalObjects: player is nullptr");
      } else {
         SGlobalObjectNetwork.receive(var0, var3);
      }
   }

    static void Reset() {
    for (auto& var1 : MainLoopNetData)         ZomboidNetDataPool.instance.discard(var1);
      }

      MainLoopNetData.clear();
   }
}
} // namespace spnetwork
} // namespace zombie
