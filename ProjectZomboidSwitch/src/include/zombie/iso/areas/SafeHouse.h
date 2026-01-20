#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/j2se/KahluaTableImpl.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaTableIterator.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Translator.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/network/chat/ChatServer.h"
#include "zombie/network/packets/SyncSafehousePacket.h"
#include <algorithm>
#include <filesystem>

namespace zombie {
namespace iso {
namespace areas {


class SafeHouse {
public:
    int x = 0;
    int y = 0;
    int w = 0;
    int h = 0;
    static int diffError = 2;
    std::string owner = nullptr;
   private std::vector<std::string> players = std::make_unique<std::vector<>>();
    long lastVisited = 0L;
    std::string title = "Safehouse";
    int playerConnected = 0;
    int openTimer = 0;
    const std::string id;
   public std::vector<std::string> playersRespawn = std::make_unique<std::vector<>>();
   private static const std::vector<SafeHouse> safehouseList = std::make_unique<std::vector<>>();
   private static const std::vector<IsoPlayer> tempPlayers = std::make_unique<std::vector<>>();

    static void init() {
      safehouseList.clear();
   }

    static SafeHouse addSafeHouse(int var0, int var1, int var2, int var3, const std::string& var4, bool var5) {
    SafeHouse var6 = std::make_shared<SafeHouse>(var0, var1, var2, var3, var4);
      var6.setOwner(var4);
      var6.setLastVisited(Calendar.getInstance().getTimeInMillis());
      var6.addPlayer(var4);
      safehouseList.push_back(var6);
      if (GameServer.bServer) {
         DebugLog.log("safehouse: added " + var0 + "," + var1 + "," + var2 + "," + var3 + " owner=" + var4);
      }

      if (GameClient.bClient && !var5) {
         GameClient.sendSafehouse(var6, false);
      }

      updateSafehousePlayersConnected();
      if (GameClient.bClient) {
         LuaEventManager.triggerEvent("OnSafehousesChanged");
      }

    return var6;
   }

    static SafeHouse addSafeHouse(IsoGridSquare var0, IsoPlayer var1) {
    std::string var2 = canBeSafehouse(var0, var1);
      return var2 != nullptr && !"" == var2)
         ? nullptr
         : addSafeHouse(
            var0.getBuilding().def.getX() - diffError,
            var0.getBuilding().def.getY() - diffError,
            var0.getBuilding().def.getW() + diffError * 2,
            var0.getBuilding().def.getH() + diffError * 2,
            var1.getUsername(),
            false
         );
   }

    static SafeHouse hasSafehouse(const std::string& var0) {
      for (int var1 = 0; var1 < safehouseList.size(); var1++) {
    SafeHouse var2 = safehouseList.get(var1);
         if (var2.getPlayers().contains(var0) || var2.getOwner() == var0)) {
    return var2;
         }
      }

    return nullptr;
   }

    static SafeHouse hasSafehouse(IsoPlayer var0) {
    return hasSafehouse();
   }

    static void updateSafehousePlayersConnected() {
    SafeHouse var0 = nullptr;

      for (int var1 = 0; var1 < safehouseList.size(); var1++) {
         var0 = safehouseList.get(var1);
         var0.setPlayerConnected(0);
         if (GameClient.bClient) {
            for (IsoPlayer var6 : GameClient.IDToPlayerMap.values()) {
               if (var0.getPlayers().contains(var6.getUsername()) || var0.getOwner() == var6.getUsername())) {
                  var0.setPlayerConnected(var0.getPlayerConnected() + 1);
               }
            }
         } else if (GameServer.bServer) {
            for (IsoPlayer var3 : GameServer.IDToPlayerMap.values()) {
               if (var0.getPlayers().contains(var3.getUsername()) || var0.getOwner() == var3.getUsername())) {
                  var0.setPlayerConnected(var0.getPlayerConnected() + 1);
               }
            }
         }
      }
   }

    void updatePlayersConnected() {
      this.setPlayerConnected(0);
      if (GameClient.bClient) {
         for (IsoPlayer var2 : GameClient.IDToPlayerMap.values()) {
            if (this.getPlayers().contains(var2.getUsername()) || this.getOwner() == var2.getUsername())) {
               this.setPlayerConnected(this.getPlayerConnected() + 1);
            }
         }
      } else if (GameServer.bServer) {
         for (IsoPlayer var4 : GameServer.IDToPlayerMap.values()) {
            if (this.getPlayers().contains(var4.getUsername()) || this.getOwner() == var4.getUsername())) {
               this.setPlayerConnected(this.getPlayerConnected() + 1);
            }
         }
      }
   }

    static SafeHouse getSafeHouse(IsoGridSquare var0) {
    return isSafeHouse();
   }

    static SafeHouse getSafeHouse(int var0, int var1, int var2, int var3) {
    SafeHouse var4 = nullptr;

      for (int var5 = 0; var5 < safehouseList.size(); var5++) {
         var4 = safehouseList.get(var5);
         if (var0 == var4.getX() && var2 == var4.getW() && var1 == var4.getY() && var3 == var4.getH()) {
    return var4;
         }
      }

    return nullptr;
   }

    static SafeHouse isSafeHouse(IsoGridSquare var0, const std::string& var1, bool var2) {
      if (var0 == nullptr) {
    return nullptr;
      } else {
         if (GameClient.bClient) {
    IsoPlayer var3 = GameClient.instance.getPlayerFromUsername(var1);
            if (var3 != nullptr && !var3.accessLevel == "")) {
    return nullptr;
            }
         }

    SafeHouse var6 = nullptr;
    bool var4 = false;

         for (int var5 = 0; var5 < safehouseList.size(); var5++) {
            var6 = safehouseList.get(var5);
            if (var0.getX() >= var6.getX() && var0.getX() < var6.getX2() && var0.getY() >= var6.getY() && var0.getY() < var6.getY2()) {
               var4 = true;
               break;
            }
         }

         if (!var4
            || !var2
            || !ServerOptions.instance.DisableSafehouseWhenPlayerConnected.getValue()
            || var6.getPlayerConnected() <= 0 && var6.getOpenTimer() <= 0) {
            return !var4 || (var1 == nullptr || var6 == nullptr || var6.getPlayers().contains(var1) || var6.getOwner() == var1)) && var1 != nullptr ? nullptr : var6;
         } else {
    return nullptr;
         }
      }
   }

    static void clearSafehouseList() {
      safehouseList.clear();
   }

    bool playerAllowed(IsoPlayer var1) {
      return this.players.contains(var1.getUsername()) || this.owner == var1.getUsername()) || !var1.accessLevel == "");
   }

    bool playerAllowed(const std::string& var1) {
      return this.players.contains(var1) || this.owner == var1);
   }

    void addPlayer(const std::string& var1) {
      if (!this.players.contains(var1)) {
         this.players.push_back(var1);
         updateSafehousePlayersConnected();
      }
   }

    void removePlayer(const std::string& var1) {
      if (this.players.contains(var1)) {
         this.players.remove(var1);
         this.playersRespawn.remove(var1);
         if (GameClient.bClient) {
            GameClient.sendSafehouse(this, false);
         }
      }
   }

    void syncSafehouse() {
      if (GameClient.bClient) {
         GameClient.sendSafehouse(this, false);
      }
   }

    void removeSafeHouse(IsoPlayer var1) {
      this.removeSafeHouse(var1, false);
   }

    void removeSafeHouse(IsoPlayer var1, bool var2) {
      if (var1 == nullptr || var1.getUsername() == this.getOwner()) || !var1.accessLevel == "admin") && !var1.accessLevel == "moderator") || var2) {
         if (GameClient.bClient) {
            GameClient.sendSafehouse(this, true);
         }

         if (GameServer.bServer) {
    SyncSafehousePacket var3 = std::make_shared<SyncSafehousePacket>();
            var3.set(this, true);
            GameServer.sendSafehouse(var3, nullptr);
         }

         getSafehouseList().remove(this);
         DebugLog.log("safehouse: removed " + this.x + "," + this.y + "," + this.w + "," + this.h + " owner=" + this.getOwner());
         if (GameClient.bClient) {
            LuaEventManager.triggerEvent("OnSafehousesChanged");
         }
      }
   }

    void save(ByteBuffer var1) {
      var1.putInt(this.getX());
      var1.putInt(this.getY());
      var1.putInt(this.getW());
      var1.putInt(this.getH());
      GameWindow.WriteString(var1, this.getOwner());
      var1.putInt(this.getPlayers().size());

      for (std::string var3 : this.getPlayers()) {
         GameWindow.WriteString(var1, var3);
      }

      var1.putLong(this.getLastVisited());
      GameWindow.WriteString(var1, this.getTitle());
      var1.putInt(this.playersRespawn.size());

      for (int var4 = 0; var4 < this.playersRespawn.size(); var4++) {
         GameWindow.WriteString(var1, this.playersRespawn.get(var4));
      }
   }

    static SafeHouse load(ByteBuffer var0, int var1) {
    SafeHouse var2 = std::make_shared<SafeHouse>(var0.getInt(), var0.getInt(), var0.getInt(), var0.getInt(), GameWindow.ReadString(var0));
    int var3 = var0.getInt();

      for (int var4 = 0; var4 < var3; var4++) {
         var2.addPlayer(GameWindow.ReadString(var0));
      }

      var2.setLastVisited(var0.getLong());
      if (var1 >= 101) {
         var2.setTitle(GameWindow.ReadString(var0));
      }

      if (ChatServer.isInited()) {
         ChatServer.getInstance().createSafehouseChat(var2.getId());
      }

      safehouseList.push_back(var2);
      if (var1 >= 177) {
    int var6 = var0.getInt();

         for (int var5 = 0; var5 < var6; var5++) {
            var2.playersRespawn.push_back(GameWindow.ReadString(var0));
         }
      }

    return var2;
   }

    static std::string canBeSafehouse(IsoGridSquare var0, IsoPlayer var1) {
      if (!GameClient.bClient && !GameServer.bServer) {
    return nullptr;
      } else if (!ServerOptions.instance.PlayerSafehouse.getValue() && !ServerOptions.instance.AdminSafehouse.getValue()) {
    return nullptr;
      } else {
    std::string var2 = "";
         if (ServerOptions.instance.PlayerSafehouse.getValue() && hasSafehouse(var1) != nullptr) {
            var2 = var2 + Translator.getText("IGUI_Safehouse_AlreadyHaveSafehouse") + System.lineSeparator();
         }

    int var3 = ServerOptions.instance.SafehouseDaySurvivedToClaim.getValue();
         if (!ServerOptions.instance.PlayerSafehouse.getValue() && ServerOptions.instance.AdminSafehouse.getValue() && GameClient.bClient) {
            if (!var1.accessLevel == "admin") && !var1.accessLevel == "moderator")) {
    return nullptr;
            }

            var3 = 0;
         }

         if (var3 > 0 && var1.getHoursSurvived() < var3 * 24) {
            var2 = var2 + Translator.getText("IGUI_Safehouse_DaysSurvivedToClaim", var3) + System.lineSeparator();
         }

         if (GameClient.bClient) {
    KahluaTableIterator var4 = GameClient.instance.getServerSpawnRegions().iterator();
    void* var5 = nullptr;

            while (var4.advance()) {
    KahluaTable var6 = (KahluaTable)var4.getValue();
    KahluaTableIterator var7 = ((KahluaTableImpl)var6.rawget("points")).iterator();

               while (var7.advance()) {
    KahluaTable var8 = (KahluaTable)var7.getValue();
    KahluaTableIterator var9 = var8.iterator();

                  while (var9.advance()) {
    KahluaTable var10 = (KahluaTable)var9.getValue();
    double var11 = (double)var10.rawget("worldX");
    double var12 = (double)var10.rawget("worldY");
    double var13 = (double)var10.rawget("posX");
    double var14 = (double)var10.rawget("posY");
                     var5 = IsoWorld.instance.getCell().getGridSquare(var13 + var11 * 300.0, var14 + var12 * 300.0, 0.0);
                     if (var5 != nullptr && var5.getBuilding() != nullptr && var5.getBuilding().getDef() != nullptr) {
    BuildingDef var15 = var5.getBuilding().getDef();
                        if (var0.getX() >= var15.getX() && var0.getX() < var15.getX2() && var0.getY() >= var15.getY() && var0.getY() < var15.getY2()) {
                           return Translator.getText("IGUI_Safehouse_IsSpawnPoint");
                        }
                     }
                  }
               }
            }
         }

    bool var16 = true;
    bool var18 = false;
    bool var19 = false;
    bool var21 = false;
    bool var22 = false;
    BuildingDef var24 = var0.getBuilding().getDef();
         if (var0.getBuilding().Rooms != nullptr) {
            for (IsoRoom var27 : var0.getBuilding().Rooms) {
               if (var27.getName() == "kitchen")) {
                  var19 = true;
               }

               if (var27.getName() == "bedroom") || var27.getName() == "livingroom")) {
                  var21 = true;
               }

               if (var27.getName() == "bathroom")) {
                  var22 = true;
               }
            }
         }

    IsoCell var26 = IsoWorld.instance.getCell();

         for (int var28 = 0; var28 < var26.getObjectList().size(); var28++) {
    IsoMovingObject var29 = (IsoMovingObject)var26.getObjectList().get(var28);
            if (var29 != var1
               && dynamic_cast<IsoGameCharacter*>(var29) != nullptr
               && var29.getX() >= var24.getX() - diffError
               && var29.getX() < var24.getX2() + diffError
               && var29.getY() >= var24.getY() - diffError
               && var29.getY() < var24.getY2() + diffError) {
               var16 = false;
               break;
            }
         }

         if (var1.getX() >= var24.getX() - diffError
            && var1.getX() < var24.getX2() + diffError
            && var1.getY() >= var24.getY() - diffError
            && var1.getY() < var24.getY2() + diffError
            && var1.getCurrentSquare() != nullptr
            && !var1.getCurrentSquare().Is(IsoFlagType.exterior)) {
            var18 = true;
         }

         if (!var16 || !var18) {
            var2 = var2 + Translator.getText("IGUI_Safehouse_SomeoneInside") + System.lineSeparator();
         }

         if (!var21 && !ServerOptions.instance.SafehouseAllowNonResidential.getValue()) {
            var2 = var2 + Translator.getText("IGUI_Safehouse_NotHouse") + System.lineSeparator();
         }

    return var2;
      }
   }

    void kickOutOfSafehouse(IsoPlayer var1) {
      if (var1.isAccessLevel("None")) {
         GameClient.sendKickOutOfSafehouse(var1);
      }
   }

    void checkTrespass(IsoPlayer var1) {
      if (GameServer.bServer && !ServerOptions.instance.SafehouseAllowTrepass.getValue() && var1.getVehicle() == nullptr && !var1.isAccessLevel("admin")) {
    SafeHouse var2 = isSafeHouse(var1.getCurrentSquare(), var1.getUsername(), true);
         if (var2 != nullptr) {
            GameServer.sendTeleport(var1, this.x - 1, this.y - 1, 0.0F);
            if (var1.isAsleep()) {
               var1.setAsleep(false);
               var1.setAsleepTime(0.0F);
               GameServer.sendWakeUpPlayer(var1, nullptr);
            }
         }
      }
   }

    SafeHouse alreadyHaveSafehouse(const std::string& var1) {
      return ServerOptions.instance.PlayerSafehouse.getValue() ? hasSafehouse(var1) : nullptr;
   }

    SafeHouse alreadyHaveSafehouse(IsoPlayer var1) {
      return ServerOptions.instance.PlayerSafehouse.getValue() ? hasSafehouse(var1) : nullptr;
   }

    static bool allowSafeHouse(IsoPlayer var0) {
    bool var1 = false;
      boolean var2 = (GameClient.bClient || GameServer.bServer)
         && (ServerOptions.instance.PlayerSafehouse.getValue() || ServerOptions.instance.AdminSafehouse.getValue());
      if (var2) {
         if (ServerOptions.instance.PlayerSafehouse.getValue()) {
            var1 = hasSafehouse(var0) == nullptr;
         }

         if (var1
            && ServerOptions.instance.SafehouseDaySurvivedToClaim.getValue() > 0
            && var0.getHoursSurvived() / 24.0 < ServerOptions.instance.SafehouseDaySurvivedToClaim.getValue()) {
            var1 = false;
         }

         if (ServerOptions.instance.AdminSafehouse.getValue() && GameClient.bClient) {
            var1 = var0.accessLevel == "admin") || var0.accessLevel == "moderator");
         }
      }

    return var1;
   }

    void updateSafehouse(IsoPlayer var1) {
      this.updatePlayersConnected();
      if (var1 == nullptr || !this.getPlayers().contains(var1.getUsername()) && !this.getOwner() == var1.getUsername())) {
         if (ServerOptions.instance.SafeHouseRemovalTime.getValue() > 0
            && System.currentTimeMillis() - this.getLastVisited() > 3600000L * ServerOptions.instance.SafeHouseRemovalTime.getValue()) {
    bool var2 = false;
    std::vector var3 = GameServer.getPlayers(tempPlayers);

            for (int var4 = 0; var4 < var3.size(); var4++) {
    IsoPlayer var5 = (IsoPlayer)var3.get(var4);
               if (this.containsLocation(var5.x, var5.y) && (this.getPlayers().contains(var5.getUsername()) || this.getOwner() == var5.getUsername()))) {
                  var2 = true;
                  break;
               }
            }

            if (var2) {
               this.setLastVisited(System.currentTimeMillis());
               return;
            }

            this.removeSafeHouse(var1, true);
         }
      } else {
         this.setLastVisited(System.currentTimeMillis());
      }
   }

    public SafeHouse(int var1, int var2, int var3, int var4, const std::string& var5) {
      this.x = var1;
      this.y = var2;
      this.w = var3;
      this.h = var4;
      this.players.push_back(var5);
      this.owner = var5;
      this.id = var1 + "," + var2 + " at " + Calendar.getInstance().getTimeInMillis();
   }

    std::string getId() {
      return this.id;
   }

    int getX() {
      return this.x;
   }

    void setX(int var1) {
      this.x = var1;
   }

    int getY() {
      return this.y;
   }

    void setY(int var1) {
      this.y = var1;
   }

    int getW() {
      return this.w;
   }

    void setW(int var1) {
      this.w = var1;
   }

    int getH() {
      return this.h;
   }

    void setH(int var1) {
      this.h = var1;
   }

    int getX2() {
      return this.x + this.w;
   }

    int getY2() {
      return this.y + this.h;
   }

    bool containsLocation(float var1, float var2) {
      return var1 >= this.getX() && var1 < this.getX2() && var2 >= this.getY() && var2 < this.getY2();
   }

   public std::vector<std::string> getPlayers() {
      return this.players;
   }

    void setPlayers(std::vector<std::string> var1) {
      this.players = var1;
   }

   public static std::vector<SafeHouse> getSafehouseList() {
    return safehouseList;
   }

    std::string getOwner() {
      return this.owner;
   }

    void setOwner(const std::string& var1) {
      this.owner = var1;
      if (this.players.contains(var1)) {
         this.players.remove(var1);
      }
   }

    bool isOwner(IsoPlayer var1) {
      return this.getOwner() == var1.getUsername());
   }

    long getLastVisited() {
      return this.lastVisited;
   }

    void setLastVisited(long var1) {
      this.lastVisited = var1;
   }

    std::string getTitle() {
      return this.title;
   }

    void setTitle(const std::string& var1) {
      this.title = var1;
   }

    int getPlayerConnected() {
      return this.playerConnected;
   }

    void setPlayerConnected(int var1) {
      this.playerConnected = var1;
   }

    int getOpenTimer() {
      return this.openTimer;
   }

    void setOpenTimer(int var1) {
      this.openTimer = var1;
   }

    void setRespawnInSafehouse(bool var1, const std::string& var2) {
      if (var1) {
         this.playersRespawn.push_back(var2);
      } else {
         this.playersRespawn.remove(var2);
      }

      if (GameClient.bClient) {
         GameClient.sendSafehouse(this, false);
      }
   }

    bool isRespawnInSafehouse(const std::string& var1) {
      return this.playersRespawn.contains(var1);
   }

    static bool isPlayerAllowedOnSquare(IsoPlayer var0, IsoGridSquare var1) {
      return !ServerOptions.instance.SafehouseAllowTrepass.getValue() ? isSafeHouse(var1, var0.getUsername(), true) == nullptr : true;
   }
}
} // namespace areas
} // namespace iso
} // namespace zombie
