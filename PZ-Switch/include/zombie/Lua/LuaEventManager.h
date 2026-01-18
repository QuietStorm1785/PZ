#pragma once
#include <mutex>
#include "se/krka/kahlua/vm/JavaFunction.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/LuaCallFrame.h"
#include "se/krka/kahlua/vm/LuaClosure.h"
#include "se/krka/kahlua/vm/Platform.h"
#include "se/krka/kahlua/vm/Prototype.h"
#include "zombie/debug/DebugLog.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace Lua {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class LuaEventManager {
public:

 // Mutexes for synchronized blocks
 static std::mutex EventMap_mutex;
public
 static ArrayList<LuaClosure> OnTickCallbacks =
 std::make_unique<ArrayList<>>();
 static Object[][] a1 = new Object[1][1];
 static Object[][] a2 = new Object[1][2];
 static Object[][] a3 = new Object[1][3];
 static Object[][] a4 = new Object[1][4];
 static Object[][] a5 = new Object[1][5];
 static Object[][] a6 = new Object[1][6];
 static Object[][] a7 = new Object[1][7];
 static Object[][] a8 = new Object[1][8];
 static int a1index = 0;
 static int a2index = 0;
 static int a3index = 0;
 static int a4index = 0;
 static int a5index = 0;
 static int a6index = 0;
 static int a7index = 0;
 static int a8index = 0;
private
 static ArrayList<Event> EventList = std::make_unique<ArrayList<>>();
private
 static HashMap<String, Event> EventMap = std::make_unique<HashMap<>>();

 static Event checkEvent(const std::string &string) {
 Event event = EventMap.get(string);
 if (event.empty()) {
 DebugLog.log("LuaEventManager: adding unknown event \"" + string + "\"");
 event = AddEvent(string);
 }

 return event.callbacks.empty() ? nullptr : event;
 }

 static void triggerEvent(const std::string &event) {
 { std::lock_guard<std::mutex> __sync_lock__(EventMap_mutex);
 Event _event = checkEvent(event);
 if (_event != nullptr) {
 _event.trigger(LuaManager.env, LuaManager.caller, nullptr);
 }
 }
 }

 static void triggerEvent(const std::string &event, void *param1) {
 { std::lock_guard<std::mutex> __sync_lock__(EventMap_mutex);
 Event _event = checkEvent(event);
 if (_event != nullptr) {
 if (a1index == a1.length) {
 a1 = Arrays.copyOf(a1, a1.length * 2);

 for (int int0 = a1index; int0 < a1.length; int0++) {
 a1[int0] = new Object[1];
 }
 }

 Object[] objects = a1[a1index];
 objects[0] = param1;
 a1index++;

 try {
 _event.trigger(LuaManager.env, LuaManager.caller, objects);
 } finally {
 a1index--;
 objects[0] = nullptr;
 }
 }
 }
 }

 static void triggerEventGarbage(const std::string &event, void *param1) {
 triggerEvent(event, param1);
 }

 static void triggerEventUnique(const std::string &event, void *param1) {
 triggerEvent(event, param1);
 }

 static void triggerEvent(const std::string &event, void *param1,
 void *param2) {
 { std::lock_guard<std::mutex> __sync_lock__(EventMap_mutex);
 Event _event = checkEvent(event);
 if (_event != nullptr) {
 if (a2index == a2.length) {
 a2 = Arrays.copyOf(a2, a2.length * 2);

 for (int int0 = a2index; int0 < a2.length; int0++) {
 a2[int0] = new Object[2];
 }
 }

 Object[] objects = a2[a2index];
 objects[0] = param1;
 objects[1] = param2;
 a2index++;

 try {
 _event.trigger(LuaManager.env, LuaManager.caller, objects);
 } finally {
 a2index--;
 objects[0] = nullptr;
 objects[1] = nullptr;
 }
 }
 }
 }

 static void triggerEventGarbage(const std::string &event, void *param1,
 void *param2) {
 triggerEvent(event, param1, param2);
 }

 static void triggerEvent(const std::string &event, void *param1, void *param2,
 void *param3) {
 { std::lock_guard<std::mutex> __sync_lock__(EventMap_mutex);
 Event _event = checkEvent(event);
 if (_event != nullptr) {
 if (a3index == a3.length) {
 a3 = Arrays.copyOf(a3, a3.length * 2);

 for (int int0 = a3index; int0 < a3.length; int0++) {
 a3[int0] = new Object[3];
 }
 }

 Object[] objects = a3[a3index];
 objects[0] = param1;
 objects[1] = param2;
 objects[2] = param3;
 a3index++;

 try {
 _event.trigger(LuaManager.env, LuaManager.caller, objects);
 } finally {
 a3index--;
 objects[0] = nullptr;
 objects[1] = nullptr;
 objects[2] = nullptr;
 }
 }
 }
 }

 static void triggerEventGarbage(const std::string &event, void *param1,
 void *param2, void *param3) {
 triggerEvent(event, param1, param2, param3);
 }

 static void triggerEvent(const std::string &event, void *param1, void *param2,
 void *param3, void *param4) {
 { std::lock_guard<std::mutex> __sync_lock__(EventMap_mutex);
 Event _event = checkEvent(event);
 if (_event != nullptr) {
 if (a4index == a4.length) {
 a4 = Arrays.copyOf(a4, a4.length * 2);

 for (int int0 = a4index; int0 < a4.length; int0++) {
 a4[int0] = new Object[4];
 }
 }

 Object[] objects = a4[a4index];
 objects[0] = param1;
 objects[1] = param2;
 objects[2] = param3;
 objects[3] = param4;
 a4index++;

 try {
 _event.trigger(LuaManager.env, LuaManager.caller, objects);
 } finally {
 a4index--;
 objects[0] = nullptr;
 objects[1] = nullptr;
 objects[2] = nullptr;
 objects[3] = nullptr;
 }
 }
 }
 }

 static void triggerEventGarbage(const std::string &event, void *param1,
 void *param2, void *param3, void *param4) {
 triggerEvent(event, param1, param2, param3, param4);
 }

 static void triggerEvent(const std::string &event, void *param1, void *param2,
 void *param3, void *param4, void *param5) {
 { std::lock_guard<std::mutex> __sync_lock__(EventMap_mutex);
 Event _event = checkEvent(event);
 if (_event != nullptr) {
 if (a5index == a5.length) {
 a5 = Arrays.copyOf(a5, a5.length * 2);

 for (int int0 = a5index; int0 < a5.length; int0++) {
 a5[int0] = new Object[5];
 }
 }

 Object[] objects = a5[a5index];
 objects[0] = param1;
 objects[1] = param2;
 objects[2] = param3;
 objects[3] = param4;
 objects[4] = param5;
 a5index++;

 try {
 _event.trigger(LuaManager.env, LuaManager.caller, objects);
 } finally {
 a5index--;
 objects[0] = nullptr;
 objects[1] = nullptr;
 objects[2] = nullptr;
 objects[3] = nullptr;
 objects[4] = nullptr;
 }
 }
 }
 }

 static void triggerEvent(const std::string &event, void *param1, void *param2,
 void *param3, void *param4, void *param5,
 void *param6) {
 { std::lock_guard<std::mutex> __sync_lock__(EventMap_mutex);
 Event _event = checkEvent(event);
 if (_event != nullptr) {
 if (a6index == a6.length) {
 a6 = Arrays.copyOf(a6, a6.length * 2);

 for (int int0 = a6index; int0 < a6.length; int0++) {
 a6[int0] = new Object[6];
 }
 }

 Object[] objects = a6[a6index];
 objects[0] = param1;
 objects[1] = param2;
 objects[2] = param3;
 objects[3] = param4;
 objects[4] = param5;
 objects[5] = param6;
 a6index++;

 try {
 _event.trigger(LuaManager.env, LuaManager.caller, objects);
 } finally {
 a6index--;
 objects[0] = nullptr;
 objects[1] = nullptr;
 objects[2] = nullptr;
 objects[3] = nullptr;
 objects[4] = nullptr;
 objects[5] = nullptr;
 }
 }
 }
 }

 static void triggerEvent(const std::string &event, void *param1, void *param2,
 void *param3, void *param4, void *param5,
 void *param6, void *param7) {
 { std::lock_guard<std::mutex> __sync_lock__(EventMap_mutex);
 Event _event = checkEvent(event);
 if (_event != nullptr) {
 if (a7index == a7.length) {
 a7 = Arrays.copyOf(a7, a7.length * 2);

 for (int int0 = a7index; int0 < a7.length; int0++) {
 a7[int0] = new Object[7];
 }
 }

 Object[] objects = a7[a7index];
 objects[0] = param1;
 objects[1] = param2;
 objects[2] = param3;
 objects[3] = param4;
 objects[4] = param5;
 objects[5] = param6;
 objects[6] = param7;
 a7index++;

 try {
 _event.trigger(LuaManager.env, LuaManager.caller, objects);
 } finally {
 a7index--;
 objects[0] = nullptr;
 objects[1] = nullptr;
 objects[2] = nullptr;
 objects[3] = nullptr;
 objects[4] = nullptr;
 objects[5] = nullptr;
 objects[6] = nullptr;
 }
 }
 }
 }

public
 static void triggerEvent(String event, Object param1, Object param2,
 Object param3, Object param4, Object param5,
 Object param6, Object param7, Object param8) {
 { std::lock_guard<std::mutex> __sync_lock__(EventMap_mutex);
 Event _event = checkEvent(event);
 if (_event != nullptr) {
 if (a8index == a8.length) {
 a8 = Arrays.copyOf(a8, a8.length * 2);

 for (int int0 = a8index; int0 < a8.length; int0++) {
 a8[int0] = new Object[8];
 }
 }

 Object[] objects = a8[a8index];
 objects[0] = param1;
 objects[1] = param2;
 objects[2] = param3;
 objects[3] = param4;
 objects[4] = param5;
 objects[5] = param6;
 objects[6] = param7;
 objects[7] = param8;
 a8index++;

 try {
 _event.trigger(LuaManager.env, LuaManager.caller, objects);
 } finally {
 a8index--;
 objects[0] = nullptr;
 objects[1] = nullptr;
 objects[2] = nullptr;
 objects[3] = nullptr;
 objects[4] = nullptr;
 objects[5] = nullptr;
 objects[6] = nullptr;
 objects[7] = nullptr;
 }
 }
 }
 }

 static Event AddEvent(const std::string &name) {
 Event event = EventMap.get(name);
 if (event != nullptr) {
 return event;
 } else {
 event = new Event(name, EventList.size());
 EventList.add(event);
 EventMap.put(name, event);
 if (LuaManager.env.rawget("Events") instanceof KahluaTable table) {
 event.register(LuaManager.platform, table);
 } else {
 DebugLog.log("ERROR: 'Events' table not found or not a table");
 }

 return event;
 }
 }

 static void AddEvents() {
 AddEvent("OnGameBoot");
 AddEvent("OnPreGameStart");
 AddEvent("OnTick");
 AddEvent("OnTickEvenPaused");
 AddEvent("OnRenderUpdate");
 AddEvent("OnFETick");
 AddEvent("OnGameStart");
 AddEvent("OnPreUIDraw");
 AddEvent("OnPostUIDraw");
 AddEvent("OnCharacterCollide");
 AddEvent("OnKeyStartPressed");
 AddEvent("OnKeyPressed");
 AddEvent("OnObjectCollide");
 AddEvent("OnNPCSurvivorUpdate");
 AddEvent("OnPlayerUpdate");
 AddEvent("OnZombieUpdate");
 AddEvent("OnTriggerNPCEvent");
 AddEvent("OnMultiTriggerNPCEvent");
 AddEvent("OnLoadMapZones");
 AddEvent("OnLoadedMapZones");
 AddEvent("OnAddBuilding");
 AddEvent("OnCreateLivingCharacter");
 AddEvent("OnChallengeQuery");
 AddEvent("OnFillInventoryObjectContextMenu");
 AddEvent("OnPreFillInventoryObjectContextMenu");
 AddEvent("OnFillWorldObjectContextMenu");
 AddEvent("OnPreFillWorldObjectContextMenu");
 AddEvent("OnRefreshInventoryWindowContainers");
 AddEvent("OnGamepadConnect");
 AddEvent("OnGamepadDisconnect");
 AddEvent("OnJoypadActivate");
 AddEvent("OnJoypadActivateUI");
 AddEvent("OnJoypadBeforeDeactivate");
 AddEvent("OnJoypadDeactivate");
 AddEvent("OnJoypadBeforeReactivate");
 AddEvent("OnJoypadReactivate");
 AddEvent("OnJoypadRenderUI");
 AddEvent("OnMakeItem");
 AddEvent("OnWeaponHitCharacter");
 AddEvent("OnWeaponSwing");
 AddEvent("OnWeaponHitTree");
 AddEvent("OnWeaponHitXp");
 AddEvent("OnWeaponSwingHitPoint");
 AddEvent("OnPlayerAttackFinished");
 AddEvent("OnLoginState");
 AddEvent("OnLoginStateSuccess");
 AddEvent("OnCharacterCreateStats");
 AddEvent("OnLoadSoundBanks");
 AddEvent("OnObjectLeftMouseButtonDown");
 AddEvent("OnObjectLeftMouseButtonUp");
 AddEvent("OnObjectRightMouseButtonDown");
 AddEvent("OnObjectRightMouseButtonUp");
 AddEvent("OnDoTileBuilding");
 AddEvent("OnDoTileBuilding2");
 AddEvent("OnDoTileBuilding3");
 AddEvent("OnConnectFailed");
 AddEvent("OnConnected");
 AddEvent("OnDisconnect");
 AddEvent("OnConnectionStateChanged");
 AddEvent("OnScoreboardUpdate");
 AddEvent("OnMouseMove");
 AddEvent("OnMouseDown");
 AddEvent("OnMouseUp");
 AddEvent("OnRightMouseDown");
 AddEvent("OnRightMouseUp");
 AddEvent("OnNewSurvivorGroup");
 AddEvent("OnPlayerSetSafehouse");
 AddEvent("OnLoad");
 AddEvent("AddXP");
 AddEvent("LevelPerk");
 AddEvent("OnSave");
 AddEvent("OnMainMenuEnter");
 AddEvent("OnGameStateEnter");
 AddEvent("OnPreMapLoad");
 AddEvent("OnPostFloorSquareDraw");
 AddEvent("OnPostFloorLayerDraw");
 AddEvent("OnPostTilesSquareDraw");
 AddEvent("OnPostTileDraw");
 AddEvent("OnPostWallSquareDraw");
 AddEvent("OnPostCharactersSquareDraw");
 AddEvent("OnCreateUI");
 AddEvent("OnMapLoadCreateIsoObject");
 AddEvent("OnCreateSurvivor");
 AddEvent("OnCreatePlayer");
 AddEvent("OnPlayerDeath");
 AddEvent("OnZombieDead");
 AddEvent("OnCharacterDeath");
 AddEvent("OnCharacterMeet");
 AddEvent("OnSpawnRegionsLoaded");
 AddEvent("OnPostMapLoad");
 AddEvent("OnAIStateExecute");
 AddEvent("OnAIStateEnter");
 AddEvent("OnAIStateExit");
 AddEvent("OnAIStateChange");
 AddEvent("OnPlayerMove");
 AddEvent("OnInitWorld");
 AddEvent("OnNewGame");
 AddEvent("OnIsoThumpableLoad");
 AddEvent("OnIsoThumpableSave");
 AddEvent("ReuseGridsquare");
 AddEvent("LoadGridsquare");
 AddEvent("EveryOneMinute");
 AddEvent("EveryTenMinutes");
 AddEvent("EveryDays");
 AddEvent("EveryHours");
 AddEvent("OnDusk");
 AddEvent("OnDawn");
 AddEvent("OnEquipPrimary");
 AddEvent("OnEquipSecondary");
 AddEvent("OnClothingUpdated");
 AddEvent("OnWeatherPeriodStart");
 AddEvent("OnWeatherPeriodStage");
 AddEvent("OnWeatherPeriodComplete");
 AddEvent("OnWeatherPeriodStop");
 AddEvent("OnRainStart");
 AddEvent("OnRainStop");
 AddEvent("OnAmbientSound");
 AddEvent("OnWorldSound");
 AddEvent("OnResetLua");
 AddEvent("OnModsModified");
 AddEvent("OnSeeNewRoom");
 AddEvent("OnNewFire");
 AddEvent("OnFillContainer");
 AddEvent("OnChangeWeather");
 AddEvent("OnRenderTick");
 AddEvent("OnDestroyIsoThumpable");
 AddEvent("OnPostSave");
 AddEvent("OnResolutionChange");
 AddEvent("OnWaterAmountChange");
 AddEvent("OnClientCommand");
 AddEvent("OnServerCommand");
 AddEvent("OnContainerUpdate");
 AddEvent("OnObjectAdded");
 AddEvent("OnObjectAboutToBeRemoved");
 AddEvent("onLoadModDataFromServer");
 AddEvent("OnGameTimeLoaded");
 AddEvent("OnCGlobalObjectSystemInit");
 AddEvent("OnSGlobalObjectSystemInit");
 AddEvent("OnWorldMessage");
 AddEvent("OnKeyKeepPressed");
 AddEvent("SendCustomModData");
 AddEvent("ServerPinged");
 AddEvent("OnServerStarted");
 AddEvent("OnLoadedTileDefinitions");
 AddEvent("OnPostRender");
 AddEvent("DoSpecialTooltip");
 AddEvent("OnCoopJoinFailed");
 AddEvent("OnServerWorkshopItems");
 AddEvent("OnVehicleDamageTexture");
 AddEvent("OnCustomUIKey");
 AddEvent("OnCustomUIKeyPressed");
 AddEvent("OnCustomUIKeyReleased");
 AddEvent("OnDeviceText");
 AddEvent("OnRadioInteraction");
 AddEvent("OnLoadRadioScripts");
 AddEvent("OnAcceptInvite");
 AddEvent("OnCoopServerMessage");
 AddEvent("OnReceiveUserlog");
 AddEvent("OnAdminMessage");
 AddEvent("OnGetDBSchema");
 AddEvent("OnGetTableResult");
 AddEvent("ReceiveFactionInvite");
 AddEvent("AcceptedFactionInvite");
 AddEvent("ReceiveSafehouseInvite");
 AddEvent("AcceptedSafehouseInvite");
 AddEvent("ViewTickets");
 AddEvent("SyncFaction");
 AddEvent("OnReceiveItemListNet");
 AddEvent("OnMiniScoreboardUpdate");
 AddEvent("OnSafehousesChanged");
 AddEvent("RequestTrade");
 AddEvent("AcceptedTrade");
 AddEvent("TradingUIAddItem");
 AddEvent("TradingUIRemoveItem");
 AddEvent("TradingUIUpdateState");
 AddEvent("OnGridBurnt");
 AddEvent("OnPreDistributionMerge");
 AddEvent("OnDistributionMerge");
 AddEvent("OnPostDistributionMerge");
 AddEvent("MngInvReceiveItems");
 AddEvent("OnTileRemoved");
 AddEvent("OnServerStartSaving");
 AddEvent("OnServerFinishSaving");
 AddEvent("OnMechanicActionDone");
 AddEvent("OnClimateTick");
 AddEvent("OnThunderEvent");
 AddEvent("OnEnterVehicle");
 AddEvent("OnSteamGameJoin");
 AddEvent("OnTabAdded");
 AddEvent("OnSetDefaultTab");
 AddEvent("OnTabRemoved");
 AddEvent("OnAddMessage");
 AddEvent("SwitchChatStream");
 AddEvent("OnChatWindowInit");
 AddEvent("OnInitSeasons");
 AddEvent("OnClimateTickDebug");
 AddEvent("OnInitModdedWeatherStage");
 AddEvent("OnUpdateModdedWeatherStage");
 AddEvent("OnClimateManagerInit");
 AddEvent("OnPressReloadButton");
 AddEvent("OnPressRackButton");
 AddEvent("OnPressWalkTo");
 AddEvent("OnHitZombie");
 AddEvent("OnBeingHitByZombie");
 AddEvent("OnServerStatisticReceived");
 AddEvent("OnDynamicMovableRecipe");
 AddEvent("OnInitGlobalModData");
 AddEvent("OnReceiveGlobalModData");
 AddEvent("OnInitRecordedMedia");
 AddEvent("onUpdateIcon");
 AddEvent("preAddForageDefs");
 AddEvent("preAddSkillDefs");
 AddEvent("preAddZoneDefs");
 AddEvent("preAddCatDefs");
 AddEvent("preAddItemDefs");
 AddEvent("onAddForageDefs");
 AddEvent("onFillSearchIconContextMenu");
 AddEvent("onItemFall");
 AddEvent("OnTemplateTextInit");
 AddEvent("OnPlayerGetDamage");
 AddEvent("OnWeaponHitThumpable");
 AddEvent("OnThrowableExplode");
 }

 static void clear() {}

 static void register(Platform platform, KahluaTable environment) {
 KahluaTable table = platform.newTable();
 environment.rawset("Events", table);
 AddEvents();
 }

 static void reroute(Prototype prototype, LuaClosure luaClosure) {
 for (int int0 = 0; int0 < EventList.size(); int0++) {
 Event event = EventList.get(int0);

 for (int int1 = 0; int1 < event.callbacks.size(); int1++) {
 LuaClosure _luaClosure = event.callbacks.get(int1);
 if (_luaClosure.prototype.filename == prototype.filename) && _luaClosure.prototype.name == prototype.name) {
 event.callbacks.set(int1, luaClosure);
 }
 }
 }
 }

 static void Reset() {
 for (int int0 = 0; int0 < EventList.size(); int0++) {
 Event event = EventList.get(int0);
 event.callbacks.clear();
 }

 EventList.clear();
 EventMap.clear();
 }

 static void ResetCallbacks() {
 for (int int0 = 0; int0 < EventList.size(); int0++) {
 Event event = EventList.get(int0);
 event.callbacks.clear();
 }
 }

 /**
 * Description copied from interface: se.krka.kahlua.vm.JavaFunction
 * @return N, number of return values. The top N objects on the stack are
 * considered the return values.
 */
 int call(LuaCallFrame callFrame, int nArguments) { return 0; }

 int OnTick(LuaCallFrame var1, int var2) { return 0; }
}
} // namespace Lua
} // namespace zombie
