#pragma once
#include "zombie/DebugFileWatcher.h"
#include "zombie/GameWindow.h"
#include "zombie/PredicatedFileWatcher.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/config/ConfigFile.h"
#include "zombie/config/ConfigOption.h"
#include "zombie/core/Core.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/debug/options/Animation.h"
#include "zombie/debug/options/Character.h"
#include "zombie/debug/options/IDebugOption.h"
#include "zombie/debug/options/IDebugOptionGroup.h"
#include "zombie/debug/options/IsoSprite.h"
#include "zombie/debug/options/Network.h"
#include "zombie/debug/options/OffscreenBuffer.h"
#include "zombie/debug/options/OptionGroup.h"
#include "zombie/debug/options/Terrain.h"
#include "zombie/debug/options/Weather.h"
#include "zombie/gameStates/GameLoadingState.h"
#include "zombie/util/PZXmlParserException.h"
#include "zombie/util/PZXmlUtil.h"
#include "zombie/util/Type.h"
#include "zombie/util/list/PZArrayUtil.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace debug {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class DebugOptions {
public:
 static const int VERSION = 1;
 static const DebugOptions instance = new DebugOptions();
private
 ArrayList<BooleanDebugOption> options = std::make_unique<ArrayList<>>();
private
 ArrayList<IDebugOption> m_options = std::make_unique<ArrayList<>>();
 const BooleanDebugOption AssetSlowLoad =
 this->newOption("Asset.SlowLoad", false);
 const BooleanDebugOption MultiplayerShowZombieMultiplier =
 this->newDebugOnlyOption("Multiplayer.Debug.ZombieMultiplier", false);
 const BooleanDebugOption MultiplayerShowZombieOwner =
 this->newDebugOnlyOption("Multiplayer.Debug.ZombieOwner", false);
 const BooleanDebugOption MultiplayerShowPosition =
 this->newDebugOnlyOption("Multiplayer.Debug.Position", false);
 const BooleanDebugOption MultiplayerShowTeleport =
 this->newDebugOnlyOption("Multiplayer.Debug.Teleport", false);
 const BooleanDebugOption MultiplayerShowHit =
 this->newDebugOnlyOption("Multiplayer.Debug.Hit", false);
 const BooleanDebugOption MultiplayerLogPrediction =
 this->newDebugOnlyOption("Multiplayer.Debug.LogPrediction", false);
 const BooleanDebugOption MultiplayerShowPlayerPrediction =
 this->newDebugOnlyOption("Multiplayer.Debug.PlayerPrediction", false);
 const BooleanDebugOption MultiplayerShowPlayerStatus =
 this->newDebugOnlyOption("Multiplayer.Debug.PlayerStatus", false);
 const BooleanDebugOption MultiplayerShowZombiePrediction =
 this->newDebugOnlyOption("Multiplayer.Debug.ZombiePrediction", false);
 const BooleanDebugOption MultiplayerShowZombieDesync =
 this->newDebugOnlyOption("Multiplayer.Debug.ZombieDesync", false);
 const BooleanDebugOption MultiplayerShowZombieStatus =
 this->newDebugOnlyOption("Multiplayer.Debug.ZombieStatus", false);
 const BooleanDebugOption MultiplayerCriticalHit =
 this->newDebugOnlyOption("Multiplayer.Debug.CriticalHit", false);
 const BooleanDebugOption MultiplayerTorsoHit =
 this->newDebugOnlyOption("Multiplayer.Debug.TorsoHit", false);
 const BooleanDebugOption MultiplayerZombieCrawler =
 this->newDebugOnlyOption("Multiplayer.Debug.ZombieCrawler", false);
 const BooleanDebugOption MultiplayerHotKey =
 this->newDebugOnlyOption("Multiplayer.Debug.HotKey", false);
 const BooleanDebugOption MultiplayerPlayerZombie =
 this->newDebugOnlyOption("Multiplayer.Debug.PlayerZombie", false);
 const BooleanDebugOption MultiplayerAttackPlayer =
 this->newDebugOnlyOption("Multiplayer.Debug.Attack.Player", false);
 const BooleanDebugOption MultiplayerFollowPlayer =
 this->newDebugOnlyOption("Multiplayer.Debug.Follow.Player", false);
 const BooleanDebugOption MultiplayerAutoEquip =
 this->newDebugOnlyOption("Multiplayer.Debug.AutoEquip", false);
 const BooleanDebugOption MultiplayerSeeNonPvpZones =
 this->newDebugOnlyOption("Multiplayer.Debug.SeeNonPvpZones", false);
 const BooleanDebugOption MultiplayerFailChecksum =
 this->newDebugOnlyOption("Multiplayer.Debug.FailChecksum", false);
 const BooleanDebugOption CheatClockVisible =
 this->newDebugOnlyOption("Cheat.Clock.Visible", false);
 const BooleanDebugOption CheatDoorUnlock =
 this->newDebugOnlyOption("Cheat.Door.Unlock", false);
 const BooleanDebugOption CheatPlayerStartInvisible =
 this->newDebugOnlyOption("Cheat.Player.StartInvisible", false);
 const BooleanDebugOption CheatPlayerInvisibleSprint =
 this->newDebugOnlyOption("Cheat.Player.InvisibleSprint", false);
 const BooleanDebugOption CheatPlayerSeeEveryone =
 this->newDebugOnlyOption("Cheat.Player.SeeEveryone", false);
 const BooleanDebugOption CheatUnlimitedAmmo =
 this->newDebugOnlyOption("Cheat.Player.UnlimitedAmmo", false);
 const BooleanDebugOption CheatRecipeKnowAll =
 this->newDebugOnlyOption("Cheat.Recipe.KnowAll", false);
 const BooleanDebugOption CheatTimedActionInstant =
 this->newDebugOnlyOption("Cheat.TimedAction.Instant", false);
 const BooleanDebugOption CheatVehicleMechanicsAnywhere =
 this->newDebugOnlyOption("Cheat.Vehicle.MechanicsAnywhere", false);
 const BooleanDebugOption CheatVehicleStartWithoutKey =
 this->newDebugOnlyOption("Cheat.Vehicle.StartWithoutKey", false);
 const BooleanDebugOption CheatWindowUnlock =
 this->newDebugOnlyOption("Cheat.Window.Unlock", false);
 const BooleanDebugOption CollideWithObstaclesRenderRadius =
 this->newOption("CollideWithObstacles.Render.Radius", false);
 const BooleanDebugOption CollideWithObstaclesRenderObstacles =
 this->newOption("CollideWithObstacles.Render.Obstacles", false);
 const BooleanDebugOption CollideWithObstaclesRenderNormals =
 this->newOption("CollideWithObstacles.Render.Normals", false);
 const BooleanDebugOption DeadBodyAtlasRender =
 this->newOption("DeadBodyAtlas.Render", false);
 const BooleanDebugOption WorldItemAtlasRender =
 this->newDebugOnlyOption("WorldItemAtlas.Render", false);
 const BooleanDebugOption DebugScenarioForceLaunch =
 this->newOption("DebugScenario.ForceLaunch", false);
 const BooleanDebugOption MechanicsRenderHitbox =
 this->newOption("Mechanics.Render.Hitbox", false);
 const BooleanDebugOption JoypadRenderUI =
 this->newDebugOnlyOption("Joypad.Render.UI", false);
 const BooleanDebugOption ModelRenderAttachments =
 this->newOption("Model.Render.Attachments", false);
 const BooleanDebugOption ModelRenderAxis =
 this->newOption("Model.Render.Axis", false);
 const BooleanDebugOption ModelRenderBones =
 this->newOption("Model.Render.Bones", false);
 const BooleanDebugOption ModelRenderBounds =
 this->newOption("Model.Render.Bounds", false);
 const BooleanDebugOption ModelRenderLights =
 this->newOption("Model.Render.Lights", false);
 const BooleanDebugOption ModelRenderMuzzleflash =
 this->newOption("Model.Render.Muzzleflash", false);
 const BooleanDebugOption ModelRenderSkipVehicles =
 this->newOption("Model.Render.SkipVehicles", false);
 const BooleanDebugOption ModelRenderWeaponHitPoint =
 this->newOption("Model.Render.WeaponHitPoint", false);
 const BooleanDebugOption ModelRenderWireframe =
 this->newOption("Model.Render.Wireframe", false);
 const BooleanDebugOption ModelSkeleton =
 this->newOption("Model.Force.Skeleton", false);
 const BooleanDebugOption ModRenderLoaded =
 this->newDebugOnlyOption("Mod.Render.Loaded", false);
 const BooleanDebugOption PathfindPathToMouseAllowCrawl =
 this->newOption("Pathfind.PathToMouse.AllowCrawl", false);
 const BooleanDebugOption PathfindPathToMouseAllowThump =
 this->newOption("Pathfind.PathToMouse.AllowThump", false);
 const BooleanDebugOption PathfindPathToMouseEnable =
 this->newOption("Pathfind.PathToMouse.Enable", false);
 const BooleanDebugOption PathfindPathToMouseIgnoreCrawlCost =
 this->newOption("Pathfind.PathToMouse.IgnoreCrawlCost", false);
 const BooleanDebugOption PathfindRenderPath =
 this->newOption("Pathfind.Render.Path", false);
 const BooleanDebugOption PathfindRenderWaiting =
 this->newOption("Pathfind.Render.Waiting", false);
 const BooleanDebugOption PhysicsRender =
 this->newOption("Physics.Render", false);
 const BooleanDebugOption PolymapRenderClusters =
 this->newOption("Pathfind.Render.Clusters", false);
 const BooleanDebugOption PolymapRenderConnections =
 this->newOption("Pathfind.Render.Connections", false);
 const BooleanDebugOption PolymapRenderCrawling =
 this->newOption("Pathfind.Render.Crawling", false);
 const BooleanDebugOption PolymapRenderLineClearCollide =
 this->newOption("Pathfind.Render.LineClearCollide", false);
 const BooleanDebugOption PolymapRenderNodes =
 this->newOption("Pathfind.Render.Nodes", false);
 const BooleanDebugOption TooltipInfo = this->newOption("Tooltip.Info", false);
 const BooleanDebugOption TooltipModName =
 this->newDebugOnlyOption("Tooltip.ModName", false);
 const BooleanDebugOption TranslationPrefix =
 this->newOption("Translation.Prefix", false);
 const BooleanDebugOption UIRenderOutline =
 this->newOption("UI.Render.Outline", false);
 const BooleanDebugOption UIDebugConsoleStartVisible =
 this->newOption("UI.DebugConsole.StartVisible", true);
 const BooleanDebugOption UIDebugConsoleDebugLog =
 this->newOption("UI.DebugConsole.DebugLog", true);
 const BooleanDebugOption UIDebugConsoleEchoCommand =
 this->newOption("UI.DebugConsole.EchoCommand", true);
 const BooleanDebugOption UIDisableWelcomeMessage =
 this->newOption("UI.DisableWelcomeMessage", false);
 const BooleanDebugOption VehicleCycleColor =
 this->newDebugOnlyOption("Vehicle.CycleColor", false);
 const BooleanDebugOption VehicleRenderBlood0 =
 this->newDebugOnlyOption("Vehicle.Render.Blood0", false);
 const BooleanDebugOption VehicleRenderBlood50 =
 this->newDebugOnlyOption("Vehicle.Render.Blood50", false);
 const BooleanDebugOption VehicleRenderBlood100 =
 this->newDebugOnlyOption("Vehicle.Render.Blood100", false);
 const BooleanDebugOption VehicleRenderDamage0 =
 this->newDebugOnlyOption("Vehicle.Render.Damage0", false);
 const BooleanDebugOption VehicleRenderDamage1 =
 this->newDebugOnlyOption("Vehicle.Render.Damage1", false);
 const BooleanDebugOption VehicleRenderDamage2 =
 this->newDebugOnlyOption("Vehicle.Render.Damage2", false);
 const BooleanDebugOption VehicleRenderRust0 =
 this->newDebugOnlyOption("Vehicle.Render.Rust0", false);
 const BooleanDebugOption VehicleRenderRust50 =
 this->newDebugOnlyOption("Vehicle.Render.Rust50", false);
 const BooleanDebugOption VehicleRenderRust100 =
 this->newDebugOnlyOption("Vehicle.Render.Rust100", false);
 const BooleanDebugOption VehicleRenderOutline =
 this->newOption("Vehicle.Render.Outline", false);
 const BooleanDebugOption VehicleRenderArea =
 this->newOption("Vehicle.Render.Area", false);
 const BooleanDebugOption VehicleRenderAuthorizations =
 this->newOption("Vehicle.Render.Authorizations", false);
 const BooleanDebugOption VehicleRenderInterpolateBuffer =
 this->newOption("Vehicle.Render.InterpolateBuffer", false);
 const BooleanDebugOption VehicleRenderAttackPositions =
 this->newOption("Vehicle.Render.AttackPositions", false);
 const BooleanDebugOption VehicleRenderExit =
 this->newOption("Vehicle.Render.Exit", false);
 const BooleanDebugOption VehicleRenderIntersectedSquares =
 this->newOption("Vehicle.Render.IntersectedSquares", false);
 const BooleanDebugOption VehicleRenderTrailerPositions =
 this->newDebugOnlyOption("Vehicle.Render.TrailerPositions", false);
 const BooleanDebugOption VehicleSpawnEverywhere =
 this->newDebugOnlyOption("Vehicle.Spawn.Everywhere", false);
 const BooleanDebugOption WorldSoundRender =
 this->newOption("Sound.WorldSound.Render", false);
 const BooleanDebugOption ObjectAmbientEmitterRender =
 this->newDebugOnlyOption("Sound.ObjectAmbientEmitter.Render", false);
 const BooleanDebugOption LightingRender =
 this->newOption("Lighting.Render", false);
 const BooleanDebugOption SkyboxShow = this->newOption("Skybox.Show", false);
 const BooleanDebugOption WorldStreamerSlowLoad =
 this->newOption("WorldStreamer.SlowLoad", false);
 const BooleanDebugOption DebugDraw_SkipVBODraw =
 this->newOption("DebugDraw.SkipVBODraw", false);
 const BooleanDebugOption DebugDraw_SkipDrawNonSkinnedModel =
 this->newOption("DebugDraw.SkipDrawNonSkinnedModel", false);
 const BooleanDebugOption DebugDraw_SkipWorldShading =
 this->newOption("DebugDraw.SkipWorldShading", false);
 const BooleanDebugOption GameProfilerEnabled =
 this->newOption("GameProfiler.Enabled", false);
 const BooleanDebugOption GameTimeSpeedHalf =
 this->newOption("GameTime.Speed.Half", false);
 const BooleanDebugOption GameTimeSpeedQuarter =
 this->newOption("GameTime.Speed.Quarter", false);
 const BooleanDebugOption ThreadCrash_Enabled =
 this->newDebugOnlyOption("ThreadCrash.Enable", false);
public
 BooleanDebugOption[] ThreadCrash_GameThread = new BooleanDebugOption[]{
 this->newDebugOnlyOption("ThreadCrash.MainThread.0", false),
 this->newDebugOnlyOption("ThreadCrash.MainThread.1", false),
 this->newDebugOnlyOption("ThreadCrash.MainThread.2", false)};
public
 BooleanDebugOption[] ThreadCrash_GameLoadingThread =
 new BooleanDebugOption[]{
 this->newDebugOnlyOption("ThreadCrash.GameLoadingThread.0", false)};
public
 BooleanDebugOption[] ThreadCrash_RenderThread =
 new BooleanDebugOption[]{
 this->newDebugOnlyOption("ThreadCrash.RenderThread.0", false),
 this->newDebugOnlyOption("ThreadCrash.RenderThread.1", false),
 this->newDebugOnlyOption("ThreadCrash.RenderThread.2", false)};
 const BooleanDebugOption WorldChunkMap5x5 =
 this->newDebugOnlyOption("World.ChunkMap.5x5", false);
 const BooleanDebugOption ZombieRenderCanCrawlUnderVehicle =
 this->newDebugOnlyOption("Zombie.Render.CanCrawlUnderVehicle", false);
 const BooleanDebugOption ZombieRenderFakeDead =
 this->newDebugOnlyOption("Zombie.Render.FakeDead", false);
 const BooleanDebugOption ZombieRenderMemory =
 this->newDebugOnlyOption("Zombie.Render.Memory", false);
 const BooleanDebugOption ZombieOutfitRandom =
 this->newDebugOnlyOption("Zombie.Outfit.Random", false);
public
 DebugOptions.Checks Checks =
 this->newOptionGroup(new DebugOptions.Checks());
 const IsoSprite IsoSprite = this->newOptionGroup(new IsoSprite());
 const Network Network = this->newOptionGroup(new Network());
 const OffscreenBuffer OffscreenBuffer =
 this->newOptionGroup(new OffscreenBuffer());
 const Terrain Terrain = this->newOptionGroup(new Terrain());
 const Weather Weather = this->newOptionGroup(new Weather());
 const Animation Animation = this->newOptionGroup(new Animation());
 const char Character = this->newOptionGroup(new Character());
 static PredicatedFileWatcher m_triggerWatcher;

 void init() {
 this->load();
 this->initMessaging();
 }

 void initMessaging() {
 if (m_triggerWatcher.empty()) {
 m_triggerWatcher = new PredicatedFileWatcher(
 ZomboidFileSystem.instance.getMessagingDirSub(
 "Trigger_SetDebugOptions.xml"),
 this ::onTrigger_SetDebugOptions);
 DebugFileWatcher.instance.add(m_triggerWatcher);
 }

 DebugOptionsXml debugOptionsXml = new DebugOptionsXml();
 debugOptionsXml.setDebugMode = true;
 debugOptionsXml.debugMode = Core.bDebug;

 for (BooleanDebugOption booleanDebugOption : this->options) {
 debugOptionsXml.options.add(new DebugOptionsXml.OptionNode(
 booleanDebugOption.getName(), booleanDebugOption.getValue()));
 }

 std::string string =
 ZomboidFileSystem.instance.getMessagingDirSub("DebugOptions_list.xml");
 PZXmlUtil.tryWrite(debugOptionsXml, new File(string);
 }

 void onTrigger_SetDebugOptions(std::string_view var1) {
 try {
 DebugOptionsXml debugOptionsXml = PZXmlUtil.parse(
 DebugOptionsXml.class, ZomboidFileSystem.instance.getMessagingDirSub(
 "Trigger_SetDebugOptions.xml"));

 for (DebugOptionsXml.OptionNode optionNode : debugOptionsXml.options) {
 this->setBoolean(optionNode.name, optionNode.value);
 }

 if (debugOptionsXml.setDebugMode) {
 DebugLog.General.println("DebugMode: %s",
 debugOptionsXml.debugMode ? "ON" : "OFF");
 Core.bDebug = debugOptionsXml.debugMode;
 }
 } catch (PZXmlParserException pZXmlParserException) {
 ExceptionLogger.logException(
 pZXmlParserException,
 "Exception thrown parsing Trigger_SetDebugOptions.xml");
 }
 }

public
 Iterable<IDebugOption> getChildren() {
 return PZArrayUtil.listConvert(this->options,
 booleanDebugOption->booleanDebugOption);
 }

 void addChild(IDebugOption newChild) {
 this->m_options.add(newChild);
 newChild.setParent(this);
 this->onChildAdded(newChild);
 }

 void onChildAdded(IDebugOption newOption) {
 this->onDescendantAdded(newOption);
 }

 void onDescendantAdded(IDebugOption newOption) { this->addOption(newOption); }

 void addOption(IDebugOption iDebugOption) {
 BooleanDebugOption booleanDebugOption =
 Type.tryCastTo(iDebugOption, BooleanDebugOption.class);
 if (booleanDebugOption != nullptr) {
 this->options.add(booleanDebugOption);
 }

 IDebugOptionGroup iDebugOptionGroup =
 Type.tryCastTo(iDebugOption, IDebugOptionGroup.class);
 if (iDebugOptionGroup != nullptr) {
 this->addDescendantOptions(iDebugOptionGroup);
 }
 }

 void addDescendantOptions(IDebugOptionGroup iDebugOptionGroup) {
 for (IDebugOption iDebugOption : iDebugOptionGroup.getChildren()) {
 this->addOption(iDebugOption);
 }
 }

 std::string getName() { return "DebugOptions"; }

 IDebugOptionGroup getParent() { return nullptr; }

 void setParent(IDebugOptionGroup parent) {
 throw UnsupportedOperationException(
 "DebugOptions is a root not. Cannot have a parent.");
 }

 BooleanDebugOption newOption(std::string_view string, bool boolean0) {
 BooleanDebugOption booleanDebugOption =
 OptionGroup.newOption(string, boolean0);
 this->addChild(booleanDebugOption);
 return booleanDebugOption;
 }

 BooleanDebugOption newDebugOnlyOption(std::string_view string,
 bool boolean0) {
 BooleanDebugOption booleanDebugOption =
 OptionGroup.newDebugOnlyOption(string, boolean0);
 this->addChild(booleanDebugOption);
 return booleanDebugOption;
 }

 private<E extends IDebugOptionGroup> E newOptionGroup(E iDebugOptionGroup) {
 this->addChild(iDebugOptionGroup);
 return (E)iDebugOptionGroup;
 }

 BooleanDebugOption getOptionByName(std::string_view name) {
 for (int int0 = 0; int0 < this->options.size(); int0++) {
 BooleanDebugOption booleanDebugOption = this->options.get(int0);
 if (booleanDebugOption.getName() == name) {
 return booleanDebugOption;
 }
 }

 return nullptr;
 }

 int getOptionCount() noexcept{ return this->options.size(); }

 BooleanDebugOption getOptionByIndex(int index) {
 return this->options.get(index);
 }

 void setBoolean(std::string_view name, bool value) {
 BooleanDebugOption booleanDebugOption = this->getOptionByName(name);
 if (booleanDebugOption != nullptr) {
 booleanDebugOption.setValue(value);
 }
 }

 bool getBoolean(std::string_view name) {
 BooleanDebugOption booleanDebugOption = this->getOptionByName(name);
 return booleanDebugOption != nullptr ? booleanDebugOption.getValue()
 : false;
 }

 void save() {
 std::string string =
 ZomboidFileSystem.instance.getCacheDirSub("debug-options.ini");
 ConfigFile configFile = new ConfigFile();
 configFile.write(string, 1, this->options);
 }

 void load() {
 std::string string =
 ZomboidFileSystem.instance.getCacheDirSub("debug-options.ini");
 ConfigFile configFile = new ConfigFile();
 if (configFile.read(string) {
 for (int int0 = 0; int0 < configFile.getOptions().size(); int0++) {
 ConfigOption configOption = configFile.getOptions().get(int0);
 BooleanDebugOption booleanDebugOption =
 this->getOptionByName(configOption.getName());
 if (booleanDebugOption != nullptr) {
 booleanDebugOption.parse(configOption.getValueAsString());
 }
 }
 }
 }

 static void testThreadCrash(int idx) {
 instance.testThreadCrashInternal(idx);
 }

 void testThreadCrashInternal(int int0) {
 if (Core.bDebug) {
 if (this->ThreadCrash_Enabled.getValue()) {
 Thread thread = Thread.currentThread();
 BooleanDebugOption[] booleanDebugOptions;
 if (thread == RenderThread.RenderThread) {
 booleanDebugOptions = this->ThreadCrash_RenderThread;
 } else if (thread == GameWindow.GameThread) {
 booleanDebugOptions = this->ThreadCrash_GameThread;
 } else {
 if (thread != GameLoadingState.loader) {
 return;
 }

 booleanDebugOptions = this->ThreadCrash_GameLoadingThread;
 }

 if (booleanDebugOptions[int0].getValue()) {
 throw Error("ThreadCrash Test! " + thread.getName());
 }
 }
 }
 }

public
 static class Checks extends OptionGroup {
 const BooleanDebugOption BoundTextures =
 newDebugOnlyOption(this->Group, "BoundTextures", false);
 const BooleanDebugOption SlowLuaEvents =
 newDebugOnlyOption(this->Group, "SlowLuaEvents", false);

 public
 Checks() { super("Checks"); }
 }
}
} // namespace debug
} // namespace zombie
