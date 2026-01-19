#pragma once
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/SandboxOptions.h"
#include "zombie/SystemDisabler.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/commands/PlayerType.h"
#include "zombie/core/Core.h"
#include "zombie/core/Translator.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/znet/ISteamWorkshopCallback.h"
#include "zombie/core/znet/SteamUGCDetails.h"
#include "zombie/core/znet/SteamUtils.h"
#include "zombie/core/znet/SteamWorkshop.h"
#include "zombie/core/znet/SteamWorkshopItem.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/LogSeverity.h"
#include "zombie/erosion/ErosionConfig.h"
#include "zombie/globalObjects/CGlobalObjects.h"
#include "zombie/iso/IsoChunkMap.h"
#include "zombie/network/ConnectionManager.h"
#include "zombie/network/CoopMaster.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/savefile/ClientPlayerDB.h"
#include "zombie/world/WorldDictionary.h"
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace gameStates {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ConnectToServerState : public GameState {
public:
 static ConnectToServerState instance;
 ByteBuffer connectionDetails;
private
 ConnectToServerState.State state;
private
 ArrayList<ConnectToServerState.WorkshopItem> workshopItems =
 std::make_unique<ArrayList<>>();
private
 ArrayList<ConnectToServerState.WorkshopItem> confirmItems =
 std::make_unique<ArrayList<>>();
private
 ConnectToServerState.ItemQuery query;

 static void noise(std::string_view string) {
 DebugLog.log("ConnectToServerState: " + string);
 }

public
 ConnectToServerState(ByteBuffer bb) {
 this->connectionDetails = ByteBuffer.allocate(bb.capacity());
 this->connectionDetails.put(bb);
 this->connectionDetails.rewind();
 }

 void enter() {
 instance = this;
 ConnectionManager.log("connect-state",
 ConnectToServerState.State.Start.name().toLowerCase(),
 nullptr);
 this->state = ConnectToServerState.State.Start;
 }

public
 GameStateMachine.StateAction update() {
 switch (this->state) {
 case Start:
 this->Start();
 break;
 case TestTCP:
 this->TestTCP();
 break;
 case WorkshopInit:
 this->WorkshopInit();
 break;
 case WorkshopQuery:
 this->WorkshopQuery();
 break;
 case WorkshopConfirm:
 this->WorkshopConfirm();
 break;
 case ServerWorkshopItemScreen:
 this->ServerWorkshopItemScreen();
 break;
 case WorkshopUpdate:
 this->WorkshopUpdate();
 break;
 case CheckMods:
 this->CheckMods();
 break;
 case Finish:
 this->Finish();
 break;
 case Exit:
 return GameStateMachine.StateAction.Continue;
 }

 return GameStateMachine.StateAction.Remain;
 }

 void receiveStartLocation(ByteBuffer byteBuffer) {
 LuaEventManager.triggerEvent("OnConnectionStateChanged", "Connected");
 IsoChunkMap.MPWorldXA = byteBuffer.getInt();
 IsoChunkMap.MPWorldYA = byteBuffer.getInt();
 IsoChunkMap.MPWorldZA = byteBuffer.getInt();
 GameClient.username = GameClient.username.trim();
 Core.GameMode = "Multiplayer";
 LuaManager.GlobalObject.createWorld(Core.GameSaveWorld);
 GameClient.instance.bConnected = true;
 }

 void receiveServerOptions(ByteBuffer byteBuffer) {
 int int0 = byteBuffer.getInt();

 for (int int1 = 0; int1 < int0; int1++) {
 std::string string0 = GameWindow.ReadString(byteBuffer);
 std::string string1 = GameWindow.ReadString(byteBuffer);
 ServerOptions.instance.putOption(string0, string1);
 }

 Core.getInstance().ResetLua("client", "ConnectedToServer");
 Core.GameMode = "Multiplayer";
 GameClient.connection.ip = GameClient.ip;
 }

 void receiveSandboxOptions(ByteBuffer byteBuffer) {
 SandboxOptions.instance.load(byteBuffer);
 SandboxOptions.instance.applySettings();
 SandboxOptions.instance.toLua();
 }

 void receiveGameTime(ByteBuffer byteBuffer) {
 GameTime.getInstance().load(byteBuffer);
 GameTime.getInstance().save();
 }

 void receiveErosionMain(ByteBuffer byteBuffer) {
 GameClient.instance.erosionConfig = std::make_unique<ErosionConfig>();
 GameClient.instance.erosionConfig.load(byteBuffer);
 }

 void receiveGlobalObjects(ByteBuffer byteBuffer) {
 CGlobalObjects.loadInitialState(byteBuffer);
 }

 void receiveResetID(ByteBuffer byteBuffer) {
 int int0 = byteBuffer.getInt();
 GameClient.instance.setResetID(int0);
 }

 void receiveBerries(ByteBuffer byteBuffer) {
 Core.getInstance().setPoisonousBerry(GameWindow.ReadString(byteBuffer);
 GameClient.poisonousBerry = Core.getInstance().getPoisonousBerry();
 Core.getInstance().setPoisonousMushroom(GameWindow.ReadString(byteBuffer);
 GameClient.poisonousMushroom = Core.getInstance().getPoisonousMushroom();
 }

 void receiveWorldDictionary(ByteBuffer byteBuffer) {
 WorldDictionary.loadDataFromServer(byteBuffer);
 ClientPlayerDB.setAllow(true);
 LuaEventManager.triggerEvent("OnConnected");
 }

 void Start() {
 noise("Start");
 ByteBuffer byteBuffer = this->connectionDetails;
 GameClient.connection.isCoopHost = byteBuffer.get() == 1;
 GameClient.connection.maxPlayers = byteBuffer.getInt();
 if (byteBuffer.get() == 1) {
 long long0 = byteBuffer.getLong();
 std::string string = GameWindow.ReadStringUTF(byteBuffer);
 Core.GameSaveWorld = long0 + "_" + string + "_player";
 }

 GameClient.instance.ID = byteBuffer.get();
 ConnectionManager.log(
 "connect-state-" + this->state.name().toLowerCase(),
 ConnectToServerState.State.TestTCP.name().toLowerCase(), nullptr);
 this->state = ConnectToServerState.State.TestTCP;
 }

 void TestTCP() {
 noise("TestTCP");
 ByteBuffer byteBuffer = this->connectionDetails;
 GameClient.connection.accessLevel =
 PlayerType.fromString(GameWindow.ReadStringUTF(byteBuffer);
 if (!SystemDisabler.getAllowDebugConnections() && Core.bDebug &&
 !SystemDisabler.getOverrideServerConnectDebugCheck() &&
 GameClient.connection.accessLevel != 32 &&
 !CoopMaster.instance.isRunning()) {
 LuaEventManager.triggerEvent(
 "OnConnectFailed",
 Translator.getText("UI_OnConnectFailed_DebugNotAllowed"));
 GameClient.connection.forceDisconnect("connect-debug-used");
 ConnectionManager.log(
 "connect-state-" + this->state.name().toLowerCase(),
 ConnectToServerState.State.Exit.name().toLowerCase(), nullptr);
 this->state = ConnectToServerState.State.Exit;
 } else {
 GameClient.GameMap = GameWindow.ReadStringUTF(byteBuffer);
 if (GameClient.GameMap.contains(";")) {
 String[] strings = GameClient.GameMap.split(";");
 Core.GameMap = strings[0].trim();
 } else {
 Core.GameMap = GameClient.GameMap.trim();
 }

 if (SteamUtils.isSteamModeEnabled()) {
 ConnectionManager.log(
 "connect-state-" + this->state.name().toLowerCase(),
 ConnectToServerState.State.WorkshopInit.name().toLowerCase(),
 nullptr);
 this->state = ConnectToServerState.State.WorkshopInit;
 } else {
 ConnectionManager.log(
 "connect-state-" + this->state.name().toLowerCase(),
 ConnectToServerState.State.CheckMods.name().toLowerCase(), nullptr);
 this->state = ConnectToServerState.State.CheckMods;
 }
 }
 }

 void WorkshopInit() {
 ByteBuffer byteBuffer = this->connectionDetails;
 short short0 = byteBuffer.getShort();

 for (int int0 = 0; int0 < short0; int0++) {
 long long0 = byteBuffer.getLong();
 long long1 = byteBuffer.getLong();
 ConnectToServerState.WorkshopItem workshopItem0 =
 new ConnectToServerState.WorkshopItem(long0, long1);
 this->workshopItems.add(workshopItem0);
 }

 if (this->workshopItems.empty()) {
 ConnectionManager.log(
 "connect-state-" + this->state.name().toLowerCase(),
 ConnectToServerState.State.WorkshopUpdate.name().toLowerCase(),
 nullptr);
 this->state = ConnectToServerState.State.WorkshopUpdate;
 } else {
 long[] longs = new long[this->workshopItems.size()];

 for (int int1 = 0; int1 < this->workshopItems.size(); int1++) {
 ConnectToServerState.WorkshopItem workshopItem1 =
 this->workshopItems.get(int1);
 longs[int1] = workshopItem1.ID;
 }

 this->query = new ConnectToServerState.ItemQuery();
 this->query.handle = SteamWorkshop.instance.CreateQueryUGCDetailsRequest(
 longs, this->query);
 if (this->query.handle != 0L) {
 ConnectionManager.log(
 "connect-state-" + this->state.name().toLowerCase(),
 ConnectToServerState.State.WorkshopQuery.name().toLowerCase(),
 nullptr);
 this->state = ConnectToServerState.State.WorkshopQuery;
 } else {
 this->query = nullptr;
 LuaEventManager.triggerEvent(
 "OnConnectFailed",
 Translator.getText(
 "UI_OnConnectFailed_CreateQueryUGCDetailsRequest"));
 GameClient.connection.forceDisconnect("connect-workshop-query");
 ConnectionManager.log(
 "connect-state-" + this->state.name().toLowerCase(),
 ConnectToServerState.State.Exit.name().toLowerCase(), nullptr);
 this->state = ConnectToServerState.State.Exit;
 }
 }
 }

 void WorkshopConfirm() {
 this->confirmItems.clear();

 for (int int0 = 0; int0 < this->workshopItems.size(); int0++) {
 ConnectToServerState.WorkshopItem workshopItem0 =
 this->workshopItems.get(int0);
 long long0 = SteamWorkshop.instance.GetItemState(workshopItem0.ID);
 noise("WorkshopConfirm GetItemState()=" +
 SteamWorkshopItem.ItemState.toString(long0) +
 " ID=" + workshopItem0.ID);
 if (SteamWorkshopItem.ItemState.Installed.and (long0) &&
 SteamWorkshopItem.ItemState.NeedsUpdate.not(long0) &&
 workshopItem0.details != nullptr &&
 workshopItem0.details.getTimeCreated() != 0L &&
 workshopItem0.details.getTimeUpdated() !=
 SteamWorkshop.instance.GetItemInstallTimeStamp(
 workshopItem0.ID) {
 noise("Installed status but timeUpdated doesn't match!!!");
 long0 |= SteamWorkshopItem.ItemState.NeedsUpdate.getValue();
 }

 if (long0 != (SteamWorkshopItem.ItemState.Subscribed.getValue() |
 SteamWorkshopItem.ItemState.Installed.getValue())) {
 this->confirmItems.add(workshopItem0);
 }
 }

 if (this->confirmItems.empty()) {
 this->query = nullptr;
 ConnectionManager.log(
 "connect-state-" + this->state.name().toLowerCase(),
 ConnectToServerState.State.WorkshopUpdate.name().toLowerCase(),
 nullptr);
 this->state = ConnectToServerState.State.WorkshopUpdate;
 } else if (this->query.empty()) {
 ConnectionManager.log(
 "connect-state-" + this->state.name().toLowerCase(),
 ConnectToServerState.State.WorkshopUpdate.name().toLowerCase(),
 nullptr);
 this->state = ConnectToServerState.State.WorkshopUpdate;
 } else {
 assert this->query.isCompleted();

 std::vector arrayList0 = new ArrayList();

 for (int int1 = 0; int1 < this->workshopItems.size(); int1++) {
 ConnectToServerState.WorkshopItem workshopItem1 =
 this->workshopItems.get(int1);
 arrayList0.add(SteamUtils.convertSteamIDToString(workshopItem1.ID);
 }

 LuaEventManager.triggerEvent("OnServerWorkshopItems", "Required",
 arrayList0);
 std::vector arrayList1 = this->query.details;
 this->query = nullptr;
 ConnectionManager.log(
 "connect-state-" + this->state.name().toLowerCase(),
 ConnectToServerState.State.ServerWorkshopItemScreen.name()
 .toLowerCase(),
 nullptr);
 this->state = ConnectToServerState.State.ServerWorkshopItemScreen;
 LuaEventManager.triggerEvent("OnServerWorkshopItems", "Details",
 arrayList1);
 }
 }

 void WorkshopQuery() {
 if (!this->query.isCompleted()) {
 if (this->query.isNotCompleted()) {
 this->query = nullptr;
 ConnectionManager.log(
 "connect-state-" + this->state.name().toLowerCase(),
 ConnectToServerState.State.ServerWorkshopItemScreen.name()
 .toLowerCase(),
 nullptr);
 this->state = ConnectToServerState.State.ServerWorkshopItemScreen;
 LuaEventManager.triggerEvent("OnServerWorkshopItems", "Error",
 "ItemQueryNotCompleted");
 }
 } else {
 for (SteamUGCDetails steamUGCDetails : this->query.details) {
 for (ConnectToServerState.WorkshopItem workshopItem :
 this->workshopItems) {
 if (workshopItem.ID == steamUGCDetails.getID()) {
 workshopItem.details = steamUGCDetails;
 break;
 }
 }
 }

 ConnectionManager.log(
 "connect-state-" + this->state.name().toLowerCase(),
 ConnectToServerState.State.WorkshopConfirm.name().toLowerCase(),
 nullptr);
 this->state = ConnectToServerState.State.WorkshopConfirm;
 }
 }

 void ServerWorkshopItemScreen() {}

 void WorkshopUpdate() {
 for (int int0 = 0; int0 < this->workshopItems.size(); int0++) {
 ConnectToServerState.WorkshopItem workshopItem =
 this->workshopItems.get(int0);
 workshopItem.update();
 if (workshopItem.state == ConnectToServerState.WorkshopItemState.Fail) {
 ConnectionManager.log(
 "connect-state-" + this->state.name().toLowerCase(),
 ConnectToServerState.State.ServerWorkshopItemScreen.name()
 .toLowerCase(),
 nullptr);
 this->state = ConnectToServerState.State.ServerWorkshopItemScreen;
 LuaEventManager.triggerEvent("OnServerWorkshopItems", "Error",
 workshopItem.ID, workshopItem.error);
 return;
 }

 if (workshopItem.state != ConnectToServerState.WorkshopItemState.Ready) {
 return;
 }
 }

 ZomboidFileSystem.instance.resetModFolders();
 LuaEventManager.triggerEvent("OnServerWorkshopItems", "Success");
 ConnectionManager.log(
 "connect-state-" + this->state.name().toLowerCase(),
 ConnectToServerState.State.CheckMods.name().toLowerCase(), nullptr);
 this->state = ConnectToServerState.State.CheckMods;
 }

 void CheckMods() {
 ByteBuffer byteBuffer = this->connectionDetails;
 std::vector arrayList = new ArrayList();
 std::unordered_map hashMap = new HashMap();
 int int0 = byteBuffer.getInt();

 for (int int1 = 0; int1 < int0; int1++) {
 ChooseGameInfo.Mod mod =
 new ChooseGameInfo.Mod(GameWindow.ReadStringUTF(byteBuffer);
 mod.setUrl(GameWindow.ReadStringUTF(byteBuffer);
 mod.setName(GameWindow.ReadStringUTF(byteBuffer);
 arrayList.add(mod.getDir());
 hashMap.put(mod.getDir(), mod);
 }

 GameClient.instance.ServerMods.clear();
 GameClient.instance.ServerMods.addAll(arrayList);
 arrayList.clear();
 std::string string0 = ZomboidFileSystem.instance.loadModsAux(
 GameClient.instance.ServerMods, arrayList);
 if (string0 != nullptr) {
 std::string string1 =
 Translator.getText("UI_OnConnectFailed_ModRequired", string0);
 if (hashMap.get(string0) != nullptr &&
 !"" == ((ChooseGameInfo.Mod)hashMap.get(string0).getUrl())) {
 string1 = string1 + " MODURL=" +
 ((ChooseGameInfo.Mod)hashMap.get(string0).getUrl();
 }

 LuaEventManager.triggerEvent("OnConnectFailed", string1);
 GameClient.connection.forceDisconnect("connect-mod-required");
 ConnectionManager.log(
 "connect-state-" + this->state.name().toLowerCase(),
 ConnectToServerState.State.Exit.name().toLowerCase(), nullptr);
 this->state = ConnectToServerState.State.Exit;
 } else {
 ConnectionManager.log(
 "connect-state-" + this->state.name().toLowerCase(),
 ConnectToServerState.State.Finish.name().toLowerCase(), nullptr);
 this->state = ConnectToServerState.State.Finish;
 }
 }

 void Finish() {
 ByteBuffer byteBuffer = this->connectionDetails;

 try {
 try {
 this->receiveStartLocation(byteBuffer);
 } catch (Exception exception0) {
 DebugLog.Multiplayer.printException(
 exception0, "receiveStartLocation error", LogSeverity.Error);
 throw exception0;
 }

 try {
 this->receiveServerOptions(byteBuffer);
 } catch (IOException iOException0) {
 DebugLog.Multiplayer.printException(
 iOException0, "receiveServerOptions error", LogSeverity.Error);
 throw iOException0;
 }

 try {
 this->receiveSandboxOptions(byteBuffer);
 } catch (IOException iOException1) {
 DebugLog.Multiplayer.printException(
 iOException1, "receiveSandboxOptions error", LogSeverity.Error);
 throw iOException1;
 }

 try {
 this->receiveGameTime(byteBuffer);
 } catch (IOException iOException2) {
 DebugLog.Multiplayer.printException(
 iOException2, "receiveGameTime error", LogSeverity.Error);
 throw iOException2;
 }

 try {
 this->receiveErosionMain(byteBuffer);
 } catch (Exception exception1) {
 DebugLog.Multiplayer.printException(
 exception1, "receiveErosionMain error", LogSeverity.Error);
 throw exception1;
 }

 try {
 this->receiveGlobalObjects(byteBuffer);
 } catch (IOException iOException3) {
 DebugLog.Multiplayer.printException(
 iOException3, "receiveGlobalObjects error", LogSeverity.Error);
 throw iOException3;
 }

 try {
 this->receiveResetID(byteBuffer);
 } catch (Exception exception2) {
 DebugLog.Multiplayer.printException(exception2, "receiveResetID error",
 LogSeverity.Error);
 throw exception2;
 }

 try {
 this->receiveBerries(byteBuffer);
 } catch (Exception exception3) {
 DebugLog.Multiplayer.printException(exception3, "receiveBerries error",
 LogSeverity.Error);
 throw exception3;
 }

 try {
 this->receiveWorldDictionary(byteBuffer);
 } catch (IOException iOException4) {
 DebugLog.Multiplayer.printException(
 iOException4, "receiveWorldDictionary error", LogSeverity.Error);
 throw iOException4;
 }
 } catch (Exception exception4) {
 ExceptionLogger.logException(exception4);
 LuaEventManager.triggerEvent("OnConnectFailed", "WorldDictionary error");
 GameClient.connection.forceDisconnect("connection-details-error");
 }

 ConnectionManager.log("connect-state-" + this->state.name().toLowerCase(),
 ConnectToServerState.State.Exit.name().toLowerCase(),
 nullptr);
 this->state = ConnectToServerState.State.Exit;
 }

 void FromLua(std::string_view button) {
 if (this->state != ConnectToServerState.State.ServerWorkshopItemScreen) {
 throw IllegalStateException("state != ServerWorkshopItemScreen");
 } else if ("install" == button) {
 ConnectionManager.log(
 "connect-state-lua-" + this->state.name().toLowerCase(),
 ConnectToServerState.State.WorkshopUpdate.name().toLowerCase(),
 nullptr);
 this->state = ConnectToServerState.State.WorkshopUpdate;
 }
 else if ("disconnect" == button) {
 LuaEventManager.triggerEvent("OnConnectFailed",
 "ServerWorkshopItemsCancelled");
 if (GameClient.connection != nullptr) {
 GameClient.connection.forceDisconnect("connect-workshop-canceled");
 }

 ConnectionManager.log(
 "connect-state-lua-" + this->state.name().toLowerCase(),
 ConnectToServerState.State.Exit.name().toLowerCase(), nullptr);
 this->state = ConnectToServerState.State.Exit;
 }
 }

 void exit() { instance = nullptr; }

class ItemQuery implements ISteamWorkshopCallback {
 long handle;
 ArrayList<SteamUGCDetails> details;
 bool bCompleted;
 bool bNotCompleted;

 bool isCompleted() { return this->bCompleted; }

 bool isNotCompleted() { return this->bNotCompleted; }

 void onItemCreated(long arg0, bool arg1) {}

 void onItemNotCreated(int arg0) {}

 void onItemUpdated(bool arg0) {}

 void onItemNotUpdated(int arg0) {}

 void onItemSubscribed(long arg0) {}

 void onItemNotSubscribed(long arg0, int arg1) {}

 void onItemDownloaded(long arg0) {}

 void onItemNotDownloaded(long arg0, int arg1) {}

 void onItemQueryCompleted(long arg0, int arg1) {
 ConnectToServerState.noise("onItemQueryCompleted handle=" + arg0 +
 " numResult=" + arg1);
 if (arg0 == this->handle) {
 SteamWorkshop.instance.RemoveCallback(this);
 std::vector arrayList = new ArrayList();

 for (int int0 = 0; int0 < arg1; int0++) {
 SteamUGCDetails steamUGCDetails =
 SteamWorkshop.instance.GetQueryUGCResult(arg0, int0);
 if (steamUGCDetails != nullptr) {
 arrayList.add(steamUGCDetails);
 }
 }

 this->details = arrayList;
 SteamWorkshop.instance.ReleaseQueryUGCRequest(arg0);
 this->bCompleted = true;
 }
 }

 void onItemQueryNotCompleted(long arg0, int arg1) {
 ConnectToServerState.noise("onItemQueryNotCompleted handle=" + arg0 +
 " result=" + arg1);
 if (arg0 == this->handle) {
 SteamWorkshop.instance.RemoveCallback(this);
 SteamWorkshop.instance.ReleaseQueryUGCRequest(arg0);
 this->bNotCompleted = true;
 }
 }
 }

 private static enum State {
 Start,
 TestTCP,
 WorkshopInit,
 WorkshopQuery,
 WorkshopConfirm,
 ServerWorkshopItemScreen,
 WorkshopUpdate,
 CheckMods,
 Finish,
 Exit;
 }

 private static class WorkshopItem implements ISteamWorkshopCallback {
 long ID;
 long serverTimeStamp;
 ConnectToServerState.WorkshopItemState state =
 ConnectToServerState.WorkshopItemState.CheckItemState;
 bool subscribed;
 long downloadStartTime;
 long downloadQueryTime;
 std::string error;
 SteamUGCDetails details;

 WorkshopItem(long long0, long long1) {
 this->ID = long0;
 this->serverTimeStamp = long1;
 }

 void update() {
 switch (this->state) {
 case CheckItemState:
 this->CheckItemState();
 break;
 case SubscribePending:
 this->SubscribePending();
 break;
 case DownloadPending:
 this->DownloadPending();
 case Ready:
 }
 }

 void setState(ConnectToServerState.WorkshopItemState workshopItemState) {
 ConnectToServerState.noise("item state " + this->state + " -> " +
 workshopItemState + " ID=" + this->ID);
 this->state = workshopItemState;
 }

 void CheckItemState() {
 long long0 = SteamWorkshop.instance.GetItemState(this->ID);
 ConnectToServerState.noise(
 "GetItemState()=" + SteamWorkshopItem.ItemState.toString(long0) +
 " ID=" + this->ID);
 if (!SteamWorkshopItem.ItemState.Subscribed.and (long0) {
 if (SteamWorkshop.instance.SubscribeItem(this->ID, this) {
 this->setState(
 ConnectToServerState.WorkshopItemState.SubscribePending);
 } else {
 this->error = "SubscribeItemFalse";
 this->setState(ConnectToServerState.WorkshopItemState.Fail);
 }
 } else {
 if (SteamWorkshopItem.ItemState.Installed.and (long0) &&
 SteamWorkshopItem.ItemState.NeedsUpdate.not(long0) &&
 this->details != nullptr && this->details.getTimeCreated() != 0L &&
 this->details.getTimeUpdated() !=
 SteamWorkshop.instance.GetItemInstallTimeStamp(this->ID) {
 ConnectToServerState.noise(
 "Installed status but timeUpdated doesn't match!!!");
 long0 |= SteamWorkshopItem.ItemState.NeedsUpdate.getValue();
 }

 if (SteamWorkshopItem.ItemState.NeedsUpdate.and (long0) {
 if (SteamWorkshop.instance.DownloadItem(this->ID, true, this) {
 this->setState(
 ConnectToServerState.WorkshopItemState.DownloadPending);
 this->downloadStartTime = System.currentTimeMillis();
 } else {
 this->error = "DownloadItemFalse";
 this->setState(ConnectToServerState.WorkshopItemState.Fail);
 }
 } else if (SteamWorkshopItem.ItemState.Installed.and (long0) {
 long long1 = SteamWorkshop.instance.GetItemInstallTimeStamp(this->ID);
 if (long1 == 0L) {
 this->error = "GetItemInstallTimeStamp";
 this->setState(ConnectToServerState.WorkshopItemState.Fail);
 } else if (long1 != this->serverTimeStamp) {
 this->error = "VersionMismatch";
 this->setState(ConnectToServerState.WorkshopItemState.Fail);
 } else {
 this->setState(ConnectToServerState.WorkshopItemState.Ready);
 }
 } else {
 this->error = "UnknownItemState";
 this->setState(ConnectToServerState.WorkshopItemState.Fail);
 }
 }
 }

 void SubscribePending() {
 if (this->subscribed) {
 long long0 = SteamWorkshop.instance.GetItemState(this->ID);
 if (SteamWorkshopItem.ItemState.Subscribed.and (long0) {
 this->setState(ConnectToServerState.WorkshopItemState.CheckItemState);
 }
 }
 }

 void DownloadPending() {
 long long0 = System.currentTimeMillis();
 if (this->downloadQueryTime + 100L <= long0) {
 this->downloadQueryTime = long0;
 long long1 = SteamWorkshop.instance.GetItemState(this->ID);
 if (SteamWorkshopItem.ItemState.NeedsUpdate.and (long1) {
 long[] longs = new long[2];
 if (SteamWorkshop.instance.GetItemDownloadInfo(this->ID, longs) {
 ConnectToServerState.noise("download " + longs[0] + "/" + longs[1] +
 " ID=" + this->ID);
 LuaEventManager.triggerEvent(
 "OnServerWorkshopItems", "Progress",
 SteamUtils.convertSteamIDToString(this->ID), longs[0],
 Math.max(longs[1], 1L);
 }
 }
 }
 }

 void onItemCreated(long var1, bool var3) {}

 void onItemNotCreated(int var1) {}

 void onItemUpdated(bool var1) {}

 void onItemNotUpdated(int var1) {}

 void onItemSubscribed(long long0) {
 ConnectToServerState.noise("onItemSubscribed itemID=" + long0);
 if (long0 == this->ID) {
 SteamWorkshop.instance.RemoveCallback(this);
 this->subscribed = true;
 }
 }

 void onItemNotSubscribed(long long0, int int0) {
 ConnectToServerState.noise("onItemNotSubscribed itemID=" + long0 +
 " result=" + int0);
 if (long0 == this->ID) {
 SteamWorkshop.instance.RemoveCallback(this);
 this->error = "ItemNotSubscribed";
 this->setState(ConnectToServerState.WorkshopItemState.Fail);
 }
 }

 void onItemDownloaded(long long0) {
 ConnectToServerState.noise(
 "onItemDownloaded itemID=" + long0 + " time=" +
 (System.currentTimeMillis() - this->downloadStartTime) + " ms");
 if (long0 == this->ID) {
 SteamWorkshop.instance.RemoveCallback(this);
 this->setState(ConnectToServerState.WorkshopItemState.CheckItemState);
 }
 }

 void onItemNotDownloaded(long long0, int int0) {
 ConnectToServerState.noise("onItemNotDownloaded itemID=" + long0 +
 " result=" + int0);
 if (long0 == this->ID) {
 SteamWorkshop.instance.RemoveCallback(this);
 this->error = "ItemNotDownloaded";
 this->setState(ConnectToServerState.WorkshopItemState.Fail);
 }
 }

 void onItemQueryCompleted(long var1, int var3) {}

 void onItemQueryNotCompleted(long var1, int var3) {}
 }

 private static enum WorkshopItemState {
 CheckItemState, SubscribePending, DownloadPending, Ready, Fail;
 }
}
} // namespace gameStates
} // namespace zombie
