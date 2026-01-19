package zombie.gameStates;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.HashMap;
import zombie.GameTime;
import zombie.GameWindow;
import zombie.SandboxOptions;
import zombie.SystemDisabler;
import zombie.ZomboidFileSystem;
import zombie.Lua.LuaEventManager;
import zombie.Lua.LuaManager.GlobalObject;
import zombie.commands.PlayerType;
import zombie.core.Core;
import zombie.core.Translator;
import zombie.core.logger.ExceptionLogger;
import zombie.core.znet.SteamUGCDetails;
import zombie.core.znet.SteamUtils;
import zombie.core.znet.SteamWorkshop;
import zombie.core.znet.SteamWorkshopItem.ItemState;
import zombie.debug.DebugLog;
import zombie.debug.LogSeverity;
import zombie.erosion.ErosionConfig;
import zombie.gameStates.ChooseGameInfo.Mod;
import zombie.gameStates.ConnectToServerState.1;
import zombie.gameStates.ConnectToServerState.ItemQuery;
import zombie.gameStates.ConnectToServerState.State;
import zombie.gameStates.ConnectToServerState.WorkshopItem;
import zombie.gameStates.ConnectToServerState.WorkshopItemState;
import zombie.gameStates.GameStateMachine.StateAction;
import zombie.globalObjects.CGlobalObjects;
import zombie.iso.IsoChunkMap;
import zombie.network.ConnectionManager;
import zombie.network.CoopMaster;
import zombie.network.GameClient;
import zombie.network.ServerOptions;
import zombie.savefile.ClientPlayerDB;
import zombie.world.WorldDictionary;

public final class ConnectToServerState extends GameState {
   public static ConnectToServerState instance;
   private ByteBuffer connectionDetails;
   private State state;
   private ArrayList<WorkshopItem> workshopItems = new ArrayList<>();
   private ArrayList<WorkshopItem> confirmItems = new ArrayList<>();
   private ItemQuery query;

   private static void noise(String var0) {
      DebugLog.log("ConnectToServerState: " + var0);
   }

   public ConnectToServerState(ByteBuffer var1) {
      this.connectionDetails = ByteBuffer.allocate(var1.capacity());
      this.connectionDetails.put(var1);
      this.connectionDetails.rewind();
   }

   public void enter() {
      instance = this;
      ConnectionManager.log("connect-state", State.Start.name().toLowerCase(), null);
      this.state = State.Start;
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
   public StateAction update() {
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

   private void receiveStartLocation(ByteBuffer var1) {
      LuaEventManager.triggerEvent("OnConnectionStateChanged", "Connected");
      IsoChunkMap.MPWorldXA = var1.getInt();
      IsoChunkMap.MPWorldYA = var1.getInt();
      IsoChunkMap.MPWorldZA = var1.getInt();
      GameClient.username = GameClient.username.trim();
      Core.GameMode = "Multiplayer";
      GlobalObject.createWorld(Core.GameSaveWorld);
      GameClient.instance.bConnected = true;
   }

   private void receiveServerOptions(ByteBuffer var1) throws IOException {
      int var2 = var1.getInt();

      for (int var3 = 0; var3 < var2; var3++) {
         String var4 = GameWindow.ReadString(var1);
         String var5 = GameWindow.ReadString(var1);
         ServerOptions.instance.putOption(var4, var5);
      }

      Core.getInstance().ResetLua("client", "ConnectedToServer");
      Core.GameMode = "Multiplayer";
      GameClient.connection.ip = GameClient.ip;
   }

   private void receiveSandboxOptions(ByteBuffer var1) throws IOException {
      SandboxOptions.instance.load(var1);
      SandboxOptions.instance.applySettings();
      SandboxOptions.instance.toLua();
   }

   private void receiveGameTime(ByteBuffer var1) throws IOException {
      GameTime.getInstance().load(var1);
      GameTime.getInstance().save();
   }

   private void receiveErosionMain(ByteBuffer var1) {
      GameClient.instance.erosionConfig = new ErosionConfig();
      GameClient.instance.erosionConfig.load(var1);
   }

   private void receiveGlobalObjects(ByteBuffer var1) throws IOException {
      CGlobalObjects.loadInitialState(var1);
   }

   private void receiveResetID(ByteBuffer var1) {
      int var2 = var1.getInt();
      GameClient.instance.setResetID(var2);
   }

   private void receiveBerries(ByteBuffer var1) {
      Core.getInstance().setPoisonousBerry(GameWindow.ReadString(var1));
      GameClient.poisonousBerry = Core.getInstance().getPoisonousBerry();
      Core.getInstance().setPoisonousMushroom(GameWindow.ReadString(var1));
      GameClient.poisonousMushroom = Core.getInstance().getPoisonousMushroom();
   }

   private void receiveWorldDictionary(ByteBuffer var1) throws IOException {
      WorldDictionary.loadDataFromServer(var1);
      ClientPlayerDB.setAllow(true);
      LuaEventManager.triggerEvent("OnConnected");
   }

   private void Start() {
      noise("Start");
      ByteBuffer var1 = this.connectionDetails;
      GameClient.connection.isCoopHost = var1.get() == 1;
      GameClient.connection.maxPlayers = var1.getInt();
      if (var1.get() == 1) {
         long var2 = var1.getLong();
         String var4 = GameWindow.ReadStringUTF(var1);
         Core.GameSaveWorld = var2 + "_" + var4 + "_player";
      }

      GameClient.instance.ID = var1.get();
      ConnectionManager.log("connect-state-" + this.state.name().toLowerCase(), State.TestTCP.name().toLowerCase(), null);
      this.state = State.TestTCP;
   }

   private void TestTCP() {
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
         ConnectionManager.log("connect-state-" + this.state.name().toLowerCase(), State.Exit.name().toLowerCase(), null);
         this.state = State.Exit;
      } else {
         GameClient.GameMap = GameWindow.ReadStringUTF(var1);
         if (GameClient.GameMap.contains(";")) {
            String[] var2 = GameClient.GameMap.split(";");
            Core.GameMap = var2[0].trim();
         } else {
            Core.GameMap = GameClient.GameMap.trim();
         }

         if (SteamUtils.isSteamModeEnabled()) {
            ConnectionManager.log("connect-state-" + this.state.name().toLowerCase(), State.WorkshopInit.name().toLowerCase(), null);
            this.state = State.WorkshopInit;
         } else {
            ConnectionManager.log("connect-state-" + this.state.name().toLowerCase(), State.CheckMods.name().toLowerCase(), null);
            this.state = State.CheckMods;
         }
      }
   }

   private void WorkshopInit() {
      ByteBuffer var1 = this.connectionDetails;
      short var2 = var1.getShort();

      for (int var3 = 0; var3 < var2; var3++) {
         long var4 = var1.getLong();
         long var6 = var1.getLong();
         WorkshopItem var8 = new WorkshopItem(var4, var6);
         this.workshopItems.add(var8);
      }

      if (this.workshopItems.isEmpty()) {
         ConnectionManager.log("connect-state-" + this.state.name().toLowerCase(), State.WorkshopUpdate.name().toLowerCase(), null);
         this.state = State.WorkshopUpdate;
      } else {
         long[] var9 = new long[this.workshopItems.size()];

         for (int var10 = 0; var10 < this.workshopItems.size(); var10++) {
            WorkshopItem var5 = this.workshopItems.get(var10);
            var9[var10] = var5.ID;
         }

         this.query = new ItemQuery(this);
         this.query.handle = SteamWorkshop.instance.CreateQueryUGCDetailsRequest(var9, this.query);
         if (this.query.handle != 0L) {
            ConnectionManager.log("connect-state-" + this.state.name().toLowerCase(), State.WorkshopQuery.name().toLowerCase(), null);
            this.state = State.WorkshopQuery;
         } else {
            this.query = null;
            LuaEventManager.triggerEvent("OnConnectFailed", Translator.getText("UI_OnConnectFailed_CreateQueryUGCDetailsRequest"));
            GameClient.connection.forceDisconnect("connect-workshop-query");
            ConnectionManager.log("connect-state-" + this.state.name().toLowerCase(), State.Exit.name().toLowerCase(), null);
            this.state = State.Exit;
         }
      }
   }

   private void WorkshopConfirm() {
      this.confirmItems.clear();

      for (int var1 = 0; var1 < this.workshopItems.size(); var1++) {
         WorkshopItem var2 = this.workshopItems.get(var1);
         long var3 = SteamWorkshop.instance.GetItemState(var2.ID);
         noise("WorkshopConfirm GetItemState()=" + ItemState.toString(var3) + " ID=" + var2.ID);
         if (ItemState.Installed.and(var3)
            && ItemState.NeedsUpdate.not(var3)
            && var2.details != null
            && var2.details.getTimeCreated() != 0L
            && var2.details.getTimeUpdated() != SteamWorkshop.instance.GetItemInstallTimeStamp(var2.ID)) {
            noise("Installed status but timeUpdated doesn't match!!!");
            var3 |= ItemState.NeedsUpdate.getValue();
         }

         if (var3 != (ItemState.Subscribed.getValue() | ItemState.Installed.getValue())) {
            this.confirmItems.add(var2);
         }
      }

      if (this.confirmItems.isEmpty()) {
         this.query = null;
         ConnectionManager.log("connect-state-" + this.state.name().toLowerCase(), State.WorkshopUpdate.name().toLowerCase(), null);
         this.state = State.WorkshopUpdate;
      } else if (this.query == null) {
         ConnectionManager.log("connect-state-" + this.state.name().toLowerCase(), State.WorkshopUpdate.name().toLowerCase(), null);
         this.state = State.WorkshopUpdate;
      } else {
         assert this.query.isCompleted();

         ArrayList var5 = new ArrayList();

         for (int var6 = 0; var6 < this.workshopItems.size(); var6++) {
            WorkshopItem var8 = this.workshopItems.get(var6);
            var5.add(SteamUtils.convertSteamIDToString(var8.ID));
         }

         LuaEventManager.triggerEvent("OnServerWorkshopItems", "Required", var5);
         ArrayList var7 = this.query.details;
         this.query = null;
         ConnectionManager.log("connect-state-" + this.state.name().toLowerCase(), State.ServerWorkshopItemScreen.name().toLowerCase(), null);
         this.state = State.ServerWorkshopItemScreen;
         LuaEventManager.triggerEvent("OnServerWorkshopItems", "Details", var7);
      }
   }

   private void WorkshopQuery() {
      if (!this.query.isCompleted()) {
         if (this.query.isNotCompleted()) {
            this.query = null;
            ConnectionManager.log("connect-state-" + this.state.name().toLowerCase(), State.ServerWorkshopItemScreen.name().toLowerCase(), null);
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

         ConnectionManager.log("connect-state-" + this.state.name().toLowerCase(), State.WorkshopConfirm.name().toLowerCase(), null);
         this.state = State.WorkshopConfirm;
      }
   }

   private void ServerWorkshopItemScreen() {
   }

   private void WorkshopUpdate() {
      for (int var1 = 0; var1 < this.workshopItems.size(); var1++) {
         WorkshopItem var2 = this.workshopItems.get(var1);
         var2.update();
         if (var2.state == WorkshopItemState.Fail) {
            ConnectionManager.log("connect-state-" + this.state.name().toLowerCase(), State.ServerWorkshopItemScreen.name().toLowerCase(), null);
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
      ConnectionManager.log("connect-state-" + this.state.name().toLowerCase(), State.CheckMods.name().toLowerCase(), null);
      this.state = State.CheckMods;
   }

   private void CheckMods() {
      ByteBuffer var1 = this.connectionDetails;
      ArrayList var2 = new ArrayList();
      HashMap var3 = new HashMap();
      int var4 = var1.getInt();

      for (int var5 = 0; var5 < var4; var5++) {
         Mod var6 = new Mod(GameWindow.ReadStringUTF(var1));
         var6.setUrl(GameWindow.ReadStringUTF(var1));
         var6.setName(GameWindow.ReadStringUTF(var1));
         var2.add(var6.getDir());
         var3.put(var6.getDir(), var6);
      }

      GameClient.instance.ServerMods.clear();
      GameClient.instance.ServerMods.addAll(var2);
      var2.clear();
      String var7 = ZomboidFileSystem.instance.loadModsAux(GameClient.instance.ServerMods, var2);
      if (var7 != null) {
         String var8 = Translator.getText("UI_OnConnectFailed_ModRequired", var7);
         if (var3.get(var7) != null && !"".equals(((Mod)var3.get(var7)).getUrl())) {
            var8 = var8 + " MODURL=" + ((Mod)var3.get(var7)).getUrl();
         }

         LuaEventManager.triggerEvent("OnConnectFailed", var8);
         GameClient.connection.forceDisconnect("connect-mod-required");
         ConnectionManager.log("connect-state-" + this.state.name().toLowerCase(), State.Exit.name().toLowerCase(), null);
         this.state = State.Exit;
      } else {
         ConnectionManager.log("connect-state-" + this.state.name().toLowerCase(), State.Finish.name().toLowerCase(), null);
         this.state = State.Finish;
      }
   }

   private void Finish() {
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

      ConnectionManager.log("connect-state-" + this.state.name().toLowerCase(), State.Exit.name().toLowerCase(), null);
      this.state = State.Exit;
   }

   public void FromLua(String var1) {
      if (this.state != State.ServerWorkshopItemScreen) {
         throw new IllegalStateException("state != ServerWorkshopItemScreen");
      } else if ("install".equals(var1)) {
         ConnectionManager.log("connect-state-lua-" + this.state.name().toLowerCase(), State.WorkshopUpdate.name().toLowerCase(), null);
         this.state = State.WorkshopUpdate;
      } else if ("disconnect".equals(var1)) {
         LuaEventManager.triggerEvent("OnConnectFailed", "ServerWorkshopItemsCancelled");
         if (GameClient.connection != null) {
            GameClient.connection.forceDisconnect("connect-workshop-canceled");
         }

         ConnectionManager.log("connect-state-lua-" + this.state.name().toLowerCase(), State.Exit.name().toLowerCase(), null);
         this.state = State.Exit;
      }
   }

   public void exit() {
      instance = null;
   }
}
