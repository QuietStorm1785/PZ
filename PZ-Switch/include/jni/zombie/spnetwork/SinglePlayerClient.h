#pragma once
#include <string>
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
#include "zombie/core/Core.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/globalObjects/CGlobalObjectNetwork.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/objects/IsoWorldInventoryObject.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/PacketTypes.h"
#include "zombie/network/PacketTypes/PacketType.h"
#include "zombie/network/TableNetworkUtils.h"
#include "zombie/spnetwork/SinglePlayerClient/1.h"
#include "zombie/spnetwork/SinglePlayerClient/UdpEngineClient.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/VehicleManager.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace spnetwork {


class SinglePlayerClient {
:
   private static ArrayList<ZomboidNetData> MainLoopNetData = std::make_unique<ArrayList<>>();
    static const UdpEngine udpEngine = new UdpEngineClient();
    static const UdpConnection connection = new UdpConnection(udpEngine);

    static void addIncoming(short var0, ByteBuffer var1) {
    ZomboidNetData var2;
      if (var1.remaining() > 2048) {
         var2 = ZomboidNetDataPool.instance.getLong(var1.remaining());
      } else {
         var2 = ZomboidNetDataPool.instance.get();
      }

      var2.read(var0, var1, connection);
      synchronized (MainLoopNetData) {
         MainLoopNetData.add(var2);
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

               try {
                  mainLoopDealWithNetData(var2);
               } finally {
                  MainLoopNetData.remove(var1--);
               }
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
               receiveServerCommand(var1);
               break;
            case 2:
               CGlobalObjectNetwork.receive(var1);
               break;
            case 3:
               receiveObjectChange(var1);
               break;
            default:
               throw IllegalStateException("Unexpected value: " + var2);
         }
      } finally {
         ZomboidNetDataPool.instance.discard(var0);
      }
   }

    static void delayPacket(int var0, int var1, int var2) {
   }

    static IsoPlayer getPlayerByID(int var0) {
      return IsoPlayer.players[var0];
   }

    static void receiveObjectChange(ByteBuffer var0) {
    uint8_t var1 = var0.get();
      if (var1 == 1) {
    short var2 = var0.getShort();
    std::string var3 = GameWindow.ReadString(var0);
         if (Core.bDebug) {
            DebugLog.log("receiveObjectChange " + var3);
         }

    IsoPlayer var4 = getPlayerByID(var2);
         if (var4 != nullptr) {
            var4.loadChange(var3, var0);
         }
      } else if (var1 == 2) {
    short var10 = var0.getShort();
    std::string var13 = GameWindow.ReadString(var0);
         if (Core.bDebug) {
            DebugLog.log("receiveObjectChange " + var13);
         }

    BaseVehicle var16 = VehicleManager.instance.getVehicleByID(var10);
         if (var16 != nullptr) {
            var16.loadChange(var13, var0);
         } else if (Core.bDebug) {
            DebugLog.log("receiveObjectChange: unknown vehicle id=" + var10);
         }
      } else if (var1 == 3) {
    int var11 = var0.getInt();
    int var14 = var0.getInt();
    int var17 = var0.getInt();
    int var5 = var0.getInt();
    std::string var6 = GameWindow.ReadString(var0);
         if (Core.bDebug) {
            DebugLog.log("receiveObjectChange " + var6);
         }

    IsoGridSquare var7 = IsoWorld.instance.CurrentCell.getGridSquare(var11, var14, var17);
         if (var7 == nullptr) {
            delayPacket(var11, var14, var17);
            return;
         }

         for (int var8 = 0; var8 < var7.getWorldObjects().size(); var8++) {
    IsoWorldInventoryObject var9 = (IsoWorldInventoryObject)var7.getWorldObjects().get(var8);
            if (var9.getItem() != nullptr && var9.getItem().getID() == var5) {
               var9.loadChange(var6, var0);
               return;
            }
         }

         if (Core.bDebug) {
            DebugLog.log("receiveObjectChange: itemID=" + var5 + " is invalid x,y,z=" + var11 + "," + var14 + "," + var17);
         }
      } else {
    int var12 = var0.getInt();
    int var15 = var0.getInt();
    int var18 = var0.getInt();
    int var19 = var0.getInt();
    std::string var20 = GameWindow.ReadString(var0);
         if (Core.bDebug) {
            DebugLog.log("receiveObjectChange " + var20);
         }

    IsoGridSquare var21 = IsoWorld.instance.CurrentCell.getGridSquare(var12, var15, var18);
         if (var21 == nullptr) {
            delayPacket(var12, var15, var18);
            return;
         }

         if (var19 >= 0 && var19 < var21.getObjects().size()) {
    IsoObject var22 = (IsoObject)var21.getObjects().get(var19);
            var22.loadChange(var20, var0);
         } else if (Core.bDebug) {
            DebugLog.log("receiveObjectChange: index=" + var19 + " is invalid x,y,z=" + var12 + "," + var15 + "," + var18);
         }
      }
   }

    static void sendClientCommand(IsoPlayer var0, const std::string& var1, const std::string& var2, KahluaTable var3) {
    ByteBufferWriter var4 = connection.startPacket();
      PacketType.ClientCommand.doPacket(var4);
      var4.putByte((byte)(var0 != nullptr ? var0.PlayerIndex : -1));
      var4.putUTF(var1);
      var4.putUTF(var2);
      if (var3 != nullptr && !var3.isEmpty()) {
         var4.putByte((byte)1);

         try {
    KahluaTableIterator var5 = var3.iterator();

            while (var5.advance()) {
               if (!TableNetworkUtils.canSave(var5.getKey(), var5.getValue())) {
                  DebugLog.log("ERROR: sendClientCommand: can't save key,value=" + var5.getKey() + "," + var5.getValue());
               }
            }

            TableNetworkUtils.save(var3, var4.bb);
         } catch (IOException var6) {
            var6.printStackTrace();
         }
      } else {
         var4.putByte((byte)0);
      }

      connection.endPacketImmediate();
   }

    static void receiveServerCommand(ByteBuffer var0) {
    std::string var1 = GameWindow.ReadString(var0);
    std::string var2 = GameWindow.ReadString(var0);
    bool var3 = var0.get() == 1;
    KahluaTable var4 = nullptr;
      if (var3) {
         var4 = LuaManager.platform.newTable();

         try {
            TableNetworkUtils.load(var4, var0);
         } catch (Exception var6) {
            var6.printStackTrace();
            return;
         }
      }

      LuaEventManager.triggerEvent("OnServerCommand", var1, var2, var4);
   }

    static void Reset() {
    for (auto& var1 : MainLoopNetData)         ZomboidNetDataPool.instance.discard(var1);
      }

      MainLoopNetData.clear();
   }
}
} // namespace spnetwork
} // namespace zombie
