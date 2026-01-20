#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/SandboxOptions.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/Core.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/znet/SteamUtils.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/erosion/ErosionMain.h"
#include "zombie/gameStates/ChooseGameInfo.h"
#include "zombie/gameStates/ChooseGameInfo/Mod.h"
#include "zombie/gameStates/ConnectToServerState.h"
#include "zombie/gameStates/MainScreenState.h"
#include "zombie/globalObjects/SGlobalObjects.h"
#include "zombie/iso/Vector3.h"
#include "zombie/network/ServerWorldDatabase/LogonResult.h"
#include "zombie/world/WorldDictionary.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace network {


class ConnectionDetails {
public:
    static void write(UdpConnection var0, LogonResult var1, ByteBuffer var2) {
      try {
         writeServerDetails(var2, var0, var1);
         writeGameMap(var2);
         if (SteamUtils.isSteamModeEnabled()) {
            writeWorkshopItems(var2);
         }

         writeMods(var2);
         writeStartLocation(var2);
         writeServerOptions(var2);
         writeSandboxOptions(var2);
         writeGameTime(var2);
         writeErosionMain(var2);
         writeGlobalObjects(var2);
         writeResetID(var2);
         writeBerries(var2);
         writeWorldDictionary(var2);
      } catch (Throwable var4) {
         throw RuntimeException(var4);
      }
   }

    static void parse(ByteBuffer var0) {
      ConnectionManager.log("receive-packet", "connection-details", nullptr);
    Calendar var1 = Calendar.getInstance();
    ConnectToServerState var2 = std::make_shared<ConnectToServerState>(var0);
      var2.enter();
      MainScreenState.getInstance().setConnectToServerState(var2);
      DebugLog.General.println("LOGGED INTO : %d millisecond", var1.getTimeInMillis() - GameClient.startAuth.getTimeInMillis());
   }

    static void writeServerDetails(ByteBuffer var0, UdpConnection var1, LogonResult var2) {
      var0.put((byte)(var1.isCoopHost ? 1 : 0));
      var0.putInt(ServerOptions.getInstance().getMaxPlayers());
      if (SteamUtils.isSteamModeEnabled() && CoopSlave.instance != nullptr && !var1.isCoopHost) {
         var0.put((byte)1);
         var0.putLong(CoopSlave.instance.hostSteamID);
         GameWindow.WriteString(var0, GameServer.ServerName);
      } else {
         var0.put((byte)0);
      }

    int var3 = var1.playerIDs[0] / 4;
      var0.put((byte)var3);
      GameWindow.WriteString(var0, var2.accessLevel);
   }

    static void writeGameMap(ByteBuffer var0) {
      GameWindow.WriteString(var0, GameServer.GameMap);
   }

    static void writeWorkshopItems(ByteBuffer var0) {
      var0.putShort((short)GameServer.WorkshopItems.size());

      for (int var1 = 0; var1 < GameServer.WorkshopItems.size(); var1++) {
         var0.putLong((int64_t)GameServer.WorkshopItems.get(var1));
         var0.putLong(GameServer.WorkshopTimeStamps[var1]);
      }
   }

    static void writeMods(ByteBuffer var0) {
    std::vector var1 = new std::vector();

      for (std::string var4 : GameServer.ServerMods) {
    std::string var5 = ZomboidFileSystem.instance.getModDir(var4);
    Mod var2;
         if (var5 != nullptr) {
            try {
               var2 = ChooseGameInfo.readModInfo(var5);
            } catch (Exception var7) {
               ExceptionLogger.logException(var7);
               var2 = std::make_shared<Mod>(var4);
               var2.setId(var4);
               var2.setName(var4);
            }
         } else {
            var2 = std::make_shared<Mod>(var4);
            var2.setId(var4);
            var2.setName(var4);
         }

         var1.push_back(var2);
      }

      var0.putInt(var1.size());

    for (auto& var9 : var1)         GameWindow.WriteString(var0, var9.getId());
         GameWindow.WriteString(var0, var9.getUrl());
         GameWindow.WriteString(var0, var9.getName());
      }
   }

    static void writeStartLocation(ByteBuffer var0) {
    void* var1 = nullptr;
    Vector3 var2 = ServerMap.instance.getStartLocation((LogonResult)var1);
      var0.putInt((int)var2.x);
      var0.putInt((int)var2.y);
      var0.putInt((int)var2.z);
   }

    static void writeServerOptions(ByteBuffer var0) {
      var0.putInt(ServerOptions.instance.getPublicOptions().size());

      for (std::string var2 : ServerOptions.instance.getPublicOptions()) {
         GameWindow.WriteString(var0, var2);
         GameWindow.WriteString(var0, ServerOptions.instance.getOption(var2));
      }
   }

    static void writeSandboxOptions(ByteBuffer var0) {
      SandboxOptions.instance.save(var0);
   }

    static void writeGameTime(ByteBuffer var0) {
      GameTime.getInstance().saveToPacket(var0);
   }

    static void writeErosionMain(ByteBuffer var0) {
      ErosionMain.getInstance().getConfig().save(var0);
   }

    static void writeGlobalObjects(ByteBuffer var0) {
      SGlobalObjects.saveInitialStateForClient(var0);
   }

    static void writeResetID(ByteBuffer var0) {
      var0.putInt(GameServer.ResetID);
   }

    static void writeBerries(ByteBuffer var0) {
      GameWindow.WriteString(var0, Core.getInstance().getPoisonousBerry());
      GameWindow.WriteString(var0, Core.getInstance().getPoisonousMushroom());
   }

    static void writeWorldDictionary(ByteBuffer var0) {
      WorldDictionary.saveDataForClient(var0);
   }
}
} // namespace network
} // namespace zombie
