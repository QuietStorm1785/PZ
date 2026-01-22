#pragma once
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/sql/Connection.h"
#include "java/sql/DatabaseMetaData.h"
#include "java/sql/PreparedStatement.h"
#include "java/sql/ResultSet.h"
#include "java/sql/SQLException.h"
#include "java/sql/Statement.h"
#include "zombie/core/Core.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/znet/SteamUtils.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/PacketTypes/PacketType.h"
#include "zombie/savefile/ServerPlayerDB/NetworkCharacterData.h"
#include <algorithm>
#include <filesystem>

namespace zombie {
namespace savefile {


class ServerPlayerDB {
public:
    static ServerPlayerDB instance = nullptr;
    static bool allow = false;
    Connection conn = nullptr;
   private ConcurrentLinkedQueue<NetworkCharacterData> CharactersToSave;

    static void setAllow(bool var0) {
      allow = var0;
   }

    static bool isAllow() {
    return allow;
   }

   public static /* synchronized - TODO: add std::mutex */ ServerPlayerDB getInstance() {
      if (instance == nullptr && allow) {
         instance = std::make_unique<ServerPlayerDB>();
      }

    return instance;
   }

    static bool isAvailable() {
      return instance != nullptr;
   }

    public ServerPlayerDB() {
      if (!Core.getInstance().isNoSave()) {
         this.create();
      }
   }

    void close() {
      instance = nullptr;
      allow = false;
   }

    void create() {
      this.conn = PlayerDBHelper.create();
      this.CharactersToSave = std::make_unique<ConcurrentLinkedQueue<>>();
    DatabaseMetaData var1 = nullptr;

      try {
         var1 = this.conn.getMetaData();
    Statement var2 = this.conn.createStatement();
    ResultSet var3 = var1.getColumns(nullptr, nullptr, "networkPlayers", "steamid");
         if (!var3.next()) {
            var2.executeUpdate("ALTER TABLE 'networkPlayers' ADD 'steamid' STRING NULL");
         }

         var3.close();
         var2.close();
      } catch (SQLException var4) {
         var4.printStackTrace();
      }
   }

    void process() {
      if (!this.CharactersToSave.empty()) {
         for (NetworkCharacterData var1 = this.CharactersToSave.poll(); var1 != nullptr; var1 = this.CharactersToSave.poll()) {
            this.serverUpdateNetworkCharacterInt(var1);
         }
      }
   }

    void serverUpdateNetworkCharacter(ByteBuffer var1, UdpConnection var2) {
      this.CharactersToSave.push_back(std::make_shared<NetworkCharacterData>(var1, var2));
   }

    void serverUpdateNetworkCharacterInt(NetworkCharacterData var1) {
      if (var1.playerIndex >= 0 && var1.playerIndex < 4) {
         if (this.conn != nullptr) {
    std::string var2;
            if (GameServer.bCoop && SteamUtils.isSteamModeEnabled()) {
               var2 = "SELECT id FROM networkPlayers WHERE steamid=? AND world=? AND playerIndex=?";
            } else {
               var2 = "SELECT id FROM networkPlayers WHERE username=? AND world=? AND playerIndex=?";
            }

    std::string var3 = "INSERT INTO networkPlayers(world,username,steamid, playerIndex,name,x,y,z,worldversion,isDead,data) VALUES(?,?,?,?,?,?,?,?,?,?,?)";
    std::string var4 = "UPDATE networkPlayers SET x=?, y=?, z=?, worldversion = ?, isDead = ?, data = ?, name = ? WHERE id=?";

            try {
               try (PreparedStatement var5 = this.conn.prepareStatement(var2)) {
                  if (GameServer.bCoop && SteamUtils.isSteamModeEnabled()) {
                     var5.setString(1, var1.steamid);
                  } else {
                     var5.setString(1, var1.username);
                  }

                  var5.setString(2, Core.GameSaveWorld);
                  var5.setInt(3, var1.playerIndex);
    ResultSet var6 = var5.executeQuery();
                  if (var6.next()) {
    int var7 = var6.getInt(1);

                     try (PreparedStatement var8 = this.conn.prepareStatement(var4)) {
                        var8.setFloat(1, var1.x);
                        var8.setFloat(2, var1.y);
                        var8.setFloat(3, var1.z);
                        var8.setInt(4, var1.worldVersion);
                        var8.setBoolean(5, var1.isDead);
                        var8.setBytes(6, var1.buffer);
                        var8.setString(7, var1.playerName);
                        var8.setInt(8, var7);
    int var9 = var8.executeUpdate();
                        this.conn.commit();
                        return;
                     }
                  }
               }

               try (PreparedStatement var18 = this.conn.prepareStatement(var3)) {
                  var18.setString(1, Core.GameSaveWorld);
                  var18.setString(2, var1.username);
                  var18.setString(3, var1.steamid);
                  var18.setInt(4, var1.playerIndex);
                  var18.setString(5, var1.playerName);
                  var18.setFloat(6, var1.x);
                  var18.setFloat(7, var1.y);
                  var18.setFloat(8, var1.z);
                  var18.setInt(9, var1.worldVersion);
                  var18.setBoolean(10, var1.isDead);
                  var18.setBytes(11, var1.buffer);
    int var19 = var18.executeUpdate();
                  this.conn.commit();
               }
            } catch (Exception var17) {
               ExceptionLogger.logException(var17);
               PlayerDBHelper.rollback(this.conn);
            }
         }
      }
   }

    void serverConvertNetworkCharacter(const std::string& var1, const std::string& var2) {
      try {
    std::string var3 = "UPDATE networkPlayers SET steamid=? WHERE username=? AND world=? AND (steamid is nullptr or steamid = '')";

         try (PreparedStatement var4 = this.conn.prepareStatement(var3)) {
            var4.setString(1, var2);
            var4.setString(2, var1);
            var4.setString(3, Core.GameSaveWorld);
    int var5 = var4.executeUpdate();
            if (var5 > 0) {
               DebugLog.General.warn("serverConvertNetworkCharacter: The steamid was set for the '" + var1 + "' for " + var5 + " players. ");
            }

            this.conn.commit();
         }
      } catch (SQLException var9) {
         ExceptionLogger.logException(var9);
      }
   }

    void serverLoadNetworkCharacter(ByteBuffer var1, UdpConnection var2) {
    uint8_t var3 = var1.get();
      if (var3 < 0 || var3 >= 4) {
    ByteBufferWriter var18 = var2.startPacket();
         PacketType.LoadPlayerProfile.doPacket(var18);
         var18.putByte((byte)0);
         var18.putInt(var3);
         PacketType.LoadPlayerProfile.send(var2);
      } else if (this.conn != nullptr) {
         if (GameServer.bCoop && SteamUtils.isSteamModeEnabled()) {
            this.serverConvertNetworkCharacter(var2.username, var2.idStr);
         }

    std::string var4;
         if (GameServer.bCoop && SteamUtils.isSteamModeEnabled()) {
            var4 = "SELECT id, x, y, z, data, worldversion, isDead FROM networkPlayers WHERE steamid=? AND world=? AND playerIndex=?";
         } else {
            var4 = "SELECT id, x, y, z, data, worldversion, isDead FROM networkPlayers WHERE username=? AND world=? AND playerIndex=?";
         }

         try (PreparedStatement var5 = this.conn.prepareStatement(var4)) {
            if (GameServer.bCoop && SteamUtils.isSteamModeEnabled()) {
               var5.setString(1, var2.idStr);
            } else {
               var5.setString(1, var2.username);
            }

            var5.setString(2, Core.GameSaveWorld);
            var5.setInt(3, var3);
    ResultSet var6 = var5.executeQuery();
            if (var6.next()) {
    int var7 = var6.getInt(1);
    float var8 = var6.getFloat(2);
    float var9 = var6.getFloat(3);
    float var10 = var6.getFloat(4);
               byte[] var11 = var6.getBytes(5);
    int var12 = var6.getInt(6);
    bool var13 = var6.getBoolean(7);
    ByteBufferWriter var14 = var2.startPacket();
               PacketType.LoadPlayerProfile.doPacket(var14);
               var14.putByte((byte)1);
               var14.putInt(var3);
               var14.putFloat(var8);
               var14.putFloat(var9);
               var14.putFloat(var10);
               var14.putInt(var12);
               var14.putByte((byte)(var13 ? 1 : 0));
               var14.putInt(var11.length);
               var14.bb.put(var11);
               PacketType.LoadPlayerProfile.send(var2);
            } else {
    ByteBufferWriter var19 = var2.startPacket();
               PacketType.LoadPlayerProfile.doPacket(var19);
               var19.putByte((byte)0);
               var19.putInt(var3);
               PacketType.LoadPlayerProfile.send(var2);
            }
         } catch (SQLException var17) {
            ExceptionLogger.logException(var17);
         }
      }
   }
}
} // namespace savefile
} // namespace zombie
