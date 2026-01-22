#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaManager/GlobalObject.h"
#include "zombie/SandboxOptions.h"
#include "zombie/SystemDisabler.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/commands/PlayerType.h"
#include "zombie/core/Core.h"
#include "zombie/core/Translator.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/znet/SteamUGCDetails.h"
#include "zombie/core/znet/SteamUtils.h"
#include "zombie/core/znet/SteamWorkshop.h"
#include "zombie/core/znet/SteamWorkshopItem/ItemState.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/LogSeverity.h"
#include "zombie/erosion/ErosionConfig.h"
#include "zombie/gameStates/ChooseGameInfo/Mod.h"
#include "zombie/gameStates/ConnectToServerState/1.h"
#include "zombie/gameStates/ConnectToServerState/ItemQuery.h"
#include "zombie/gameStates/ConnectToServerState/State.h"
#include "zombie/gameStates/ConnectToServerState/WorkshopItem.h"
#include "zombie/gameStates/ConnectToServerState/WorkshopItemState.h"
#include "zombie/gameStates/GameStateMachine/StateAction.h"
#include "zombie/globalObjects/CGlobalObjects.h"
#include "zombie/iso/IsoChunkMap.h"
#include "zombie/network/ConnectionManager.h"
#include "zombie/network/CoopMaster.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/savefile/ClientPlayerDB.h"
#include "zombie/world/WorldDictionary.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace gameStates {


class ConnectToServerState : public GameState {
public:
    static ConnectToServerState instance;
    ByteBuffer connectionDetails;
    State state;
   private std::vector<WorkshopItem> workshopItems = std::make_unique<std::vector<>>();
   private std::vector<WorkshopItem> confirmItems = std::make_unique<std::vector<>>();
    ItemQuery query;

    static void noise(const std::string& var0) {
      DebugLog.log("ConnectToServerState: " + var0);
   }

    public ConnectToServerState(ByteBuffer var1) {
      this.connectionDetails = ByteBuffer.allocate(var1.capacity());
      this.connectionDetails.put(var1);
      this.connectionDetails.rewind();
   }

    void enter() {
      instance = this;
      ConnectionManager.log("connect-state", State.Start.name().toLowerCase(), nullptr);
      this.state = State.Start;
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    StateAction update() {
      switch (1.$SwitchMap$zombie$gameStates$ConnectToServerState$State[this.state.ordinal()]) {
         case 1:
            this.Start();
            break;
         case 2:
            this.TestTCP();
            break;
         case 3:
            this.WorkshopInit();
            break;
         case 4:
            this.WorkshopQuery();
            break;
         case 5:
            this.WorkshopConfirm();
            break;
         case 6:
            this.ServerWorkshopItemScreen();
            break;
         case 7:
            this.WorkshopUpdate();
            break;
         case 8:
            this.CheckMods();
            break;
         case 9:
            this.Finish();
            break;
         case 10:
            return StateAction.Continue;
      }

      return StateAction.Remain;
   }

    void receiveStartLocation(ByteBuffer var1) {
      LuaEventManager.triggerEvent("OnConnectionStateChanged", "Connected");
      IsoChunkMap.MPWorldXA = var1.getInt();
      IsoChunkMap.MPWorldYA = var1.getInt();
      IsoChunkMap.MPWorldZA = var1.getInt();
      GameClient.username = GameClient.username.trim();
      Core.GameMode = "Multiplayer";
      GlobalObject.createWorld(Core.GameSaveWorld);
      GameClient.instance.bConnected = true;
   }

    void receiveServerOptions(ByteBuffer var1) {
    int var2 = var1.getInt();

      for (int var3 = 0; var3 < var2; var3++) {
    std::string var4 = GameWindow.ReadString(var1);
    std::string var5 = GameWindow.ReadString(var1);
         ServerOptions.instance.putOption(var4, var5);
      }

      Core.getInstance().ResetLua("client", "ConnectedToServer");
      Core.GameMode = "Multiplayer";
      GameClient.connection.ip = GameClient.ip;
   }

    void receiveSandboxOptions(ByteBuffer var1) {
      SandboxOptions.instance.load(var1);
      SandboxOptions.instance.applySettings();
      SandboxOptions.instance.toLua();
   }

    void receiveGameTime(ByteBuffer var1) {
      GameTime.getInstance().load(var1);
      GameTime.getInstance().save();
   }

    void receiveErosionMain(ByteBuffer var1) {
      GameClient.instance.erosionConfig = std::make_unique<ErosionConfig>();
      GameClient.instance.erosionConfig.load(var1);
   }

    void receiveGlobalObjects(ByteBuffer var1) {
      CGlobalObjects.loadInitialState(var1);
   }

    void receiveResetID(ByteBuffer var1) {
    int var2 = var1.getInt();
      GameClient.instance.setResetID(var2);
   }

    void receiveBerries(ByteBuffer var1) {
      Core.getInstance().setPoisonousBerry(GameWindow.ReadString(var1));
      GameClient.poisonousBerry = Core.getInstance().getPoisonousBerry();
      Core.getInstance().setPoisonousMushroom(GameWindow.ReadString(var1));
      GameClient.poisonousMushroom = Core.getInstance().getPoisonousMushroom();
   }

    void receiveWorldDictionary(ByteBuffer var1) {
      WorldDictionary.loadDataFromServer(var1);
      ClientPlayerDB.setAllow(true);
      LuaEventManager.triggerEvent("OnConnected");
   }

    void Start() {
      noise("Start");
    ByteBuffer var1 = this.connectionDetails;
      GameClient.connection.isCoopHost = var1.get() == 1;
      GameClient.connection.maxPlayers = var1.getInt();
      if (var1.get() == 1) {
    long var2 = var1.getLong();
    std::string var4 = GameWindow.ReadStringUTF(var1);
         Core.GameSaveWorld = var2 + "_" + var4 + "_player";
      }

      GameClient.instance.ID = var1.get();
      ConnectionManager.log("connect-state-" + this.state.name().toLowerCase(), State.TestTCP.name().toLowerCase(), nullptr);
      this.state = State.TestTCP;
   }

    void TestTCP() {
      noise("TestTCP");
    ByteBuffer var1 = this.connectionDetails;
      GameClient.connection.accessLevel = PlayerType.fromString(GameWindow.ReadStringUTF(var1));
      if (!SystemDisabler.getAllowDebugConnections()
         && Core.bDebug
         && !SystemDisabler.getOverrideServerConnectDebugCheck()
         && GameClient.connection.accessLevel != 32
         && !CoopMaster.instance.isRunning()) {
         LuaEventManager.triggerEvent("OnConnectFailed", Translator.getText("UI_OnConnectFailed_DebugNotAllowed"));
         GameClient.connection.forceDisconnect("connect-debug-used");
         ConnectionManager.log("connect-state-" + this.state.name().toLowerCase(), State.Exit.name().toLowerCase(), nullptr);
         this.state = State.Exit;
      } else {
         GameClient.GameMap = GameWindow.ReadStringUTF(var1);
         if (GameClient.GameMap.contains(";")) {
            std::string[] var2 = GameClient.GameMap.split(";");
            Core.GameMap = var2[0].trim();
         } else {
            Core.GameMap = GameClient.GameMap.trim();
         }

         if (SteamUtils.isSteamModeEnabled()) {
            ConnectionManager.log("connect-state-" + this.state.name().toLowerCase(), State.WorkshopInit.name().toLowerCase(), nullptr);
            this.state = State.WorkshopInit;
         } else {
            ConnectionManager.log("connect-state-" + this.state.name().toLowerCase(), State.CheckMods.name().toLowerCase(), nullptr);
            this.state = State.CheckMods;
         }
      }
   }

    void WorkshopInit() {
    ByteBuffer var1 = this.connectionDetails;
    short var2 = var1.getShort();

      for (int var3 = 0; var3 < var2; var3++) {
    long var4 = var1.getLong();
    long var6 = var1.getLong();
    WorkshopItem var8 = std::make_shared<WorkshopItem>(var4, var6);
         this.workshopItems.push_back(var8);
      }

      if (this.workshopItems.empty()) {
         ConnectionManager.log("connect-state-" + this.state.name().toLowerCase(), State.WorkshopUpdate.name().toLowerCase(), nullptr);
         this.state = State.WorkshopUpdate;
      } else {
         long[] var9 = new long[this.workshopItems.size()];

         for (int var10 = 0; var10 < this.workshopItems.size(); var10++) {
    WorkshopItem var5 = this.workshopItems.get(var10);
            var9[var10] = var5.ID;
         }

         this.query = std::make_shared<ItemQuery>(this);
         this.query.handle = SteamWorkshop.instance.CreateQueryUGCDetailsRequest(var9, this.query);
         if (this.query.handle != 0L) {
            ConnectionManager.log("connect-state-" + this.state.name().toLowerCase(), State.WorkshopQuery.name().toLowerCase(), nullptr);
            this.state = State.WorkshopQuery;
         } else {
            this.query = nullptr;
            LuaEventManager.triggerEvent("OnConnectFailed", Translator.getText("UI_OnConnectFailed_CreateQueryUGCDetailsRequest"));
            GameClient.connection.forceDisconnect("connect-workshop-query");
            ConnectionManager.log("connect-state-" + this.state.name().toLowerCase(), State.Exit.name().toLowerCase(), nullptr);
            this.state = State.Exit;
         }
      }
   }

    void WorkshopConfirm() {
      this.confirmItems.clear();

      for (int var1 = 0; var1 < this.workshopItems.size(); var1++) {
    WorkshopItem var2 = this.workshopItems.get(var1);
    long var3 = SteamWorkshop.instance.GetItemState(var2.ID);
         noise("WorkshopConfirm GetItemState()=" + ItemState.toString(var3) + " ID=" + var2.ID);
         if (ItemState.Installed.and(var3)
            && ItemState.NeedsUpdate.not(var3)
            && var2.details != nullptr
            && var2.details.getTimeCreated() != 0L
            && var2.details.getTimeUpdated() != SteamWorkshop.instance.GetItemInstallTimeStamp(var2.ID)) {
            noise("Installed status but timeUpdated doesn't match!!!");
            var3 |= ItemState.NeedsUpdate.getValue();
         }

         if (var3 != (ItemState.Subscribed.getValue() | ItemState.Installed.getValue())) {
            this.confirmItems.push_back(var2);
         }
      }

      if (this.confirmItems.empty()) {
         this.query = nullptr;
         ConnectionManager.log("connect-state-" + this.state.name().toLowerCase(), State.WorkshopUpdate.name().toLowerCase(), nullptr);
         this.state = State.WorkshopUpdate;
      } else if (this.query == nullptr) {
         ConnectionManager.log("connect-state-" + this.state.name().toLowerCase(), State.WorkshopUpdate.name().toLowerCase(), nullptr);
         this.state = State.WorkshopUpdate;
      } else {
         assert this.query.isCompleted();

    std::vector var5 = new std::vector();

         for (int var6 = 0; var6 < this.workshopItems.size(); var6++) {
    WorkshopItem var8 = this.workshopItems.get(var6);
            var5.push_back(SteamUtils.convertSteamIDToString(var8.ID));
         }

         LuaEventManager.triggerEvent("OnServerWorkshopItems", "Required", var5);
    std::vector var7 = this.query.details;
         this.query = nullptr;
         ConnectionManager.log("connect-state-" + this.state.name().toLowerCase(), State.ServerWorkshopItemScreen.name().toLowerCase(), nullptr);
         this.state = State.ServerWorkshopItemScreen;
         LuaEventManager.triggerEvent("OnServerWorkshopItems", "Details", var7);
      }
   }

    void WorkshopQuery() {
      if (!this.query.isCompleted()) {
         if (this.query.isNotCompleted()) {
            this.query = nullptr;
            ConnectionManager.log("connect-state-" + this.state.name().toLowerCase(), State.ServerWorkshopItemScreen.name().toLowerCase(), nullptr);
            this.state = State.ServerWorkshopItemScreen;
            LuaEventManager.triggerEvent("OnServerWorkshopItems", "Error", "ItemQueryNotCompleted");
         }
      } else {
         for (SteamUGCDetails var2 : this.query.details) {
            for (WorkshopItem var4 : this.workshopItems) {
               if (var4.ID == var2.getID()) {
                  var4.details = var2;
                  break;
               }
            }
         }

         ConnectionManager.log("connect-state-" + this.state.name().toLowerCase(), State.WorkshopConfirm.name().toLowerCase(), nullptr);
         this.state = State.WorkshopConfirm;
      }
   }

    void ServerWorkshopItemScreen() {
   }

    void WorkshopUpdate() {
      for (int var1 = 0; var1 < this.workshopItems.size(); var1++) {
    WorkshopItem var2 = this.workshopItems.get(var1);
         var2.update();
         if (var2.state == WorkshopItemState.Fail) {
            ConnectionManager.log("connect-state-" + this.state.name().toLowerCase(), State.ServerWorkshopItemScreen.name().toLowerCase(), nullptr);
            this.state = State.ServerWorkshopItemScreen;
            LuaEventManager.triggerEvent("OnServerWorkshopItems", "Error", var2.ID, var2.error);
            return;
         }

         if (var2.state != WorkshopItemState.Ready) {
            return;
         }
      }

      ZomboidFileSystem.instance.resetModFolders();
      LuaEventManager.triggerEvent("OnServerWorkshopItems", "Success");
      ConnectionManager.log("connect-state-" + this.state.name().toLowerCase(), State.CheckMods.name().toLowerCase(), nullptr);
      this.state = State.CheckMods;
   }

    void CheckMods() {
    ByteBuffer var1 = this.connectionDetails;
    std::vector var2 = new std::vector();
    std::unordered_map var3 = new std::unordered_map();
    int var4 = var1.getInt();

      for (int var5 = 0; var5 < var4; var5++) {
    Mod var6 = std::make_shared<Mod>(GameWindow.ReadStringUTF(var1));
         var6.setUrl(GameWindow.ReadStringUTF(var1));
         var6.setName(GameWindow.ReadStringUTF(var1));
         var2.push_back(var6.getDir());
         var3.put(var6.getDir(), var6);
      }

      GameClient.instance.ServerMods.clear();
      GameClient.instance.ServerMods.addAll(var2);
      var2.clear();
    std::string var7 = ZomboidFileSystem.instance.loadModsAux(GameClient.instance.ServerMods, var2);
      if (var7 != nullptr) {
    std::string var8 = Translator.getText("UI_OnConnectFailed_ModRequired", var7);
         if (var3.get(var7) != nullptr && !"" == ((Mod)var3.get(var7)).getUrl())) {
            var8 = var8 + " MODURL=" + ((Mod)var3.get(var7)).getUrl();
         }

         LuaEventManager.triggerEvent("OnConnectFailed", var8);
         GameClient.connection.forceDisconnect("connect-mod-required");
         ConnectionManager.log("connect-state-" + this.state.name().toLowerCase(), State.Exit.name().toLowerCase(), nullptr);
         this.state = State.Exit;
      } else {
         ConnectionManager.log("connect-state-" + this.state.name().toLowerCase(), State.Finish.name().toLowerCase(), nullptr);
         this.state = State.Finish;
      }
   }

    void Finish() {
    ByteBuffer var1 = this.connectionDetails;

      try {
         try {
            this.receiveStartLocation(var1);
         } catch (Exception var11) {
            DebugLog.Multiplayer.printException(var11, "receiveStartLocation error", LogSeverity.Error);
    throw var11;
         }

         try {
            this.receiveServerOptions(var1);
         } catch (IOException var10) {
            DebugLog.Multiplayer.printException(var10, "receiveServerOptions error", LogSeverity.Error);
    throw var10;
         }

         try {
            this.receiveSandboxOptions(var1);
         } catch (IOException var9) {
            DebugLog.Multiplayer.printException(var9, "receiveSandboxOptions error", LogSeverity.Error);
    throw var9;
         }

         try {
            this.receiveGameTime(var1);
         } catch (IOException var8) {
            DebugLog.Multiplayer.printException(var8, "receiveGameTime error", LogSeverity.Error);
    throw var8;
         }

         try {
            this.receiveErosionMain(var1);
         } catch (Exception var7) {
            DebugLog.Multiplayer.printException(var7, "receiveErosionMain error", LogSeverity.Error);
    throw var7;
         }

         try {
            this.receiveGlobalObjects(var1);
         } catch (IOException var6) {
            DebugLog.Multiplayer.printException(var6, "receiveGlobalObjects error", LogSeverity.Error);
    throw var6;
         }

         try {
            this.receiveResetID(var1);
         } catch (Exception var5) {
            DebugLog.Multiplayer.printException(var5, "receiveResetID error", LogSeverity.Error);
    throw var5;
         }

         try {
            this.receiveBerries(var1);
         } catch (Exception var4) {
            DebugLog.Multiplayer.printException(var4, "receiveBerries error", LogSeverity.Error);
    throw var4;
         }

         try {
            this.receiveWorldDictionary(var1);
         } catch (IOException var3) {
            DebugLog.Multiplayer.printException(var3, "receiveWorldDictionary error", LogSeverity.Error);
    throw var3;
         }
      } catch (Exception var12) {
         ExceptionLogger.logException(var12);
         LuaEventManager.triggerEvent("OnConnectFailed", "WorldDictionary error");
         GameClient.connection.forceDisconnect("connection-details-error");
      }

      ConnectionManager.log("connect-state-" + this.state.name().toLowerCase(), State.Exit.name().toLowerCase(), nullptr);
      this.state = State.Exit;
   }

    void FromLua(const std::string& var1) {
      if (this.state != State.ServerWorkshopItemScreen) {
         throw IllegalStateException("state != ServerWorkshopItemScreen");
      } else if ("install" == var1)) {
         ConnectionManager.log("connect-state-lua-" + this.state.name().toLowerCase(), State.WorkshopUpdate.name().toLowerCase(), nullptr);
         this.state = State.WorkshopUpdate;
      } else if ("disconnect" == var1)) {
         LuaEventManager.triggerEvent("OnConnectFailed", "ServerWorkshopItemsCancelled");
         if (GameClient.connection != nullptr) {
            GameClient.connection.forceDisconnect("connect-workshop-canceled");
         }

         ConnectionManager.log("connect-state-lua-" + this.state.name().toLowerCase(), State.Exit.name().toLowerCase(), nullptr);
         this.state = State.Exit;
      }
   }

    void exit() {
      instance = nullptr;
   }
}
} // namespace gameStates
} // namespace zombie
