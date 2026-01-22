#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/DebugFileWatcher.h"
#include "zombie/GameWindow.h"
#include "zombie/PredicatedFileWatcher.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/config/ConfigFile.h"
#include "zombie/config/ConfigOption.h"
#include "zombie/core/Core.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/debug/DebugOptions/Checks.h"
#include "zombie/debug/DebugOptionsXml/OptionNode.h"
#include "zombie/debug/options/Animation.h"
#include "zombie/debug/options/char.h"
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
#include <fstream>
#include <iostream>

namespace zombie {
namespace debug {


class DebugOptions {
public:
    static const int VERSION = 1;
    static const DebugOptions instance = std::make_shared<DebugOptions>();
   private const std::vector<BooleanDebugOption> options = std::make_unique<std::vector<>>();
   private const std::vector<IDebugOption> m_options = std::make_unique<std::vector<>>();
    const BooleanDebugOption AssetSlowLoad = this.newOption("Asset.SlowLoad", false);
    const BooleanDebugOption MultiplayerShowZombieMultiplier = this.newDebugOnlyOption("Multiplayer.Debug.ZombieMultiplier", false);
    const BooleanDebugOption MultiplayerShowZombieOwner = this.newDebugOnlyOption("Multiplayer.Debug.ZombieOwner", false);
    const BooleanDebugOption MultiplayerShowPosition = this.newDebugOnlyOption("Multiplayer.Debug.Position", false);
    const BooleanDebugOption MultiplayerShowTeleport = this.newDebugOnlyOption("Multiplayer.Debug.Teleport", false);
    const BooleanDebugOption MultiplayerShowHit = this.newDebugOnlyOption("Multiplayer.Debug.Hit", false);
    const BooleanDebugOption MultiplayerLogPrediction = this.newDebugOnlyOption("Multiplayer.Debug.LogPrediction", false);
    const BooleanDebugOption MultiplayerShowPlayerPrediction = this.newDebugOnlyOption("Multiplayer.Debug.PlayerPrediction", false);
    const BooleanDebugOption MultiplayerShowPlayerStatus = this.newDebugOnlyOption("Multiplayer.Debug.PlayerStatus", false);
    const BooleanDebugOption MultiplayerShowZombiePrediction = this.newDebugOnlyOption("Multiplayer.Debug.ZombiePrediction", false);
    const BooleanDebugOption MultiplayerShowZombieDesync = this.newDebugOnlyOption("Multiplayer.Debug.ZombieDesync", false);
    const BooleanDebugOption MultiplayerShowZombieStatus = this.newDebugOnlyOption("Multiplayer.Debug.ZombieStatus", false);
    const BooleanDebugOption MultiplayerCriticalHit = this.newDebugOnlyOption("Multiplayer.Debug.CriticalHit", false);
    const BooleanDebugOption MultiplayerTorsoHit = this.newDebugOnlyOption("Multiplayer.Debug.TorsoHit", false);
    const BooleanDebugOption MultiplayerZombieCrawler = this.newDebugOnlyOption("Multiplayer.Debug.ZombieCrawler", false);
    const BooleanDebugOption MultiplayerHotKey = this.newDebugOnlyOption("Multiplayer.Debug.HotKey", false);
    const BooleanDebugOption MultiplayerPlayerZombie = this.newDebugOnlyOption("Multiplayer.Debug.PlayerZombie", false);
    const BooleanDebugOption MultiplayerAttackPlayer = this.newDebugOnlyOption("Multiplayer.Debug.Attack.Player", false);
    const BooleanDebugOption MultiplayerFollowPlayer = this.newDebugOnlyOption("Multiplayer.Debug.Follow.Player", false);
    const BooleanDebugOption MultiplayerAutoEquip = this.newDebugOnlyOption("Multiplayer.Debug.AutoEquip", false);
    const BooleanDebugOption MultiplayerSeeNonPvpZones = this.newDebugOnlyOption("Multiplayer.Debug.SeeNonPvpZones", false);
    const BooleanDebugOption MultiplayerFailChecksum = this.newDebugOnlyOption("Multiplayer.Debug.FailChecksum", false);
    const BooleanDebugOption CheatClockVisible = this.newDebugOnlyOption("Cheat.Clock.Visible", false);
    const BooleanDebugOption CheatDoorUnlock = this.newDebugOnlyOption("Cheat.Door.Unlock", false);
    const BooleanDebugOption CheatPlayerStartInvisible = this.newDebugOnlyOption("Cheat.Player.StartInvisible", false);
    const BooleanDebugOption CheatPlayerInvisibleSprint = this.newDebugOnlyOption("Cheat.Player.InvisibleSprint", false);
    const BooleanDebugOption CheatPlayerSeeEveryone = this.newDebugOnlyOption("Cheat.Player.SeeEveryone", false);
    const BooleanDebugOption CheatUnlimitedAmmo = this.newDebugOnlyOption("Cheat.Player.UnlimitedAmmo", false);
    const BooleanDebugOption CheatRecipeKnowAll = this.newDebugOnlyOption("Cheat.Recipe.KnowAll", false);
    const BooleanDebugOption CheatTimedActionInstant = this.newDebugOnlyOption("Cheat.TimedAction.Instant", false);
    const BooleanDebugOption CheatVehicleMechanicsAnywhere = this.newDebugOnlyOption("Cheat.Vehicle.MechanicsAnywhere", false);
    const BooleanDebugOption CheatVehicleStartWithoutKey = this.newDebugOnlyOption("Cheat.Vehicle.StartWithoutKey", false);
    const BooleanDebugOption CheatWindowUnlock = this.newDebugOnlyOption("Cheat.Window.Unlock", false);
    const BooleanDebugOption CollideWithObstaclesRenderRadius = this.newOption("CollideWithObstacles.Render.Radius", false);
    const BooleanDebugOption CollideWithObstaclesRenderObstacles = this.newOption("CollideWithObstacles.Render.Obstacles", false);
    const BooleanDebugOption CollideWithObstaclesRenderNormals = this.newOption("CollideWithObstacles.Render.Normals", false);
    const BooleanDebugOption DeadBodyAtlasRender = this.newOption("DeadBodyAtlas.Render", false);
    const BooleanDebugOption WorldItemAtlasRender = this.newDebugOnlyOption("WorldItemAtlas.Render", false);
    const BooleanDebugOption DebugScenarioForceLaunch = this.newOption("DebugScenario.ForceLaunch", false);
    const BooleanDebugOption MechanicsRenderHitbox = this.newOption("Mechanics.Render.Hitbox", false);
    const BooleanDebugOption JoypadRenderUI = this.newDebugOnlyOption("Joypad.Render.UI", false);
    const BooleanDebugOption ModelRenderAttachments = this.newOption("Model.Render.Attachments", false);
    const BooleanDebugOption ModelRenderAxis = this.newOption("Model.Render.Axis", false);
    const BooleanDebugOption ModelRenderBones = this.newOption("Model.Render.Bones", false);
    const BooleanDebugOption ModelRenderBounds = this.newOption("Model.Render.Bounds", false);
    const BooleanDebugOption ModelRenderLights = this.newOption("Model.Render.Lights", false);
    const BooleanDebugOption ModelRenderMuzzleflash = this.newOption("Model.Render.Muzzleflash", false);
    const BooleanDebugOption ModelRenderSkipVehicles = this.newOption("Model.Render.SkipVehicles", false);
    const BooleanDebugOption ModelRenderWeaponHitPoint = this.newOption("Model.Render.WeaponHitPoint", false);
    const BooleanDebugOption ModelRenderWireframe = this.newOption("Model.Render.Wireframe", false);
    const BooleanDebugOption ModelSkeleton = this.newOption("Model.Force.Skeleton", false);
    const BooleanDebugOption ModRenderLoaded = this.newDebugOnlyOption("Mod.Render.Loaded", false);
    const BooleanDebugOption PathfindPathToMouseAllowCrawl = this.newOption("Pathfind.PathToMouse.AllowCrawl", false);
    const BooleanDebugOption PathfindPathToMouseAllowThump = this.newOption("Pathfind.PathToMouse.AllowThump", false);
    const BooleanDebugOption PathfindPathToMouseEnable = this.newOption("Pathfind.PathToMouse.Enable", false);
    const BooleanDebugOption PathfindPathToMouseIgnoreCrawlCost = this.newOption("Pathfind.PathToMouse.IgnoreCrawlCost", false);
    const BooleanDebugOption PathfindRenderPath = this.newOption("Pathfind.Render.Path", false);
    const BooleanDebugOption PathfindRenderWaiting = this.newOption("Pathfind.Render.Waiting", false);
    const BooleanDebugOption PhysicsRender = this.newOption("Physics.Render", false);
    const BooleanDebugOption PolymapRenderClusters = this.newOption("Pathfind.Render.Clusters", false);
    const BooleanDebugOption PolymapRenderConnections = this.newOption("Pathfind.Render.Connections", false);
    const BooleanDebugOption PolymapRenderCrawling = this.newOption("Pathfind.Render.Crawling", false);
    const BooleanDebugOption PolymapRenderLineClearCollide = this.newOption("Pathfind.Render.LineClearCollide", false);
    const BooleanDebugOption PolymapRenderNodes = this.newOption("Pathfind.Render.Nodes", false);
    const BooleanDebugOption TooltipInfo = this.newOption("Tooltip.Info", false);
    const BooleanDebugOption TooltipModName = this.newDebugOnlyOption("Tooltip.ModName", false);
    const BooleanDebugOption TranslationPrefix = this.newOption("Translation.Prefix", false);
    const BooleanDebugOption UIRenderOutline = this.newOption("UI.Render.Outline", false);
    const BooleanDebugOption UIDebugConsoleStartVisible = this.newOption("UI.DebugConsole.StartVisible", true);
    const BooleanDebugOption UIDebugConsoleDebugLog = this.newOption("UI.DebugConsole.DebugLog", true);
    const BooleanDebugOption UIDebugConsoleEchoCommand = this.newOption("UI.DebugConsole.EchoCommand", true);
    const BooleanDebugOption UIDisableWelcomeMessage = this.newOption("UI.DisableWelcomeMessage", false);
    const BooleanDebugOption VehicleCycleColor = this.newDebugOnlyOption("Vehicle.CycleColor", false);
    const BooleanDebugOption VehicleRenderBlood0 = this.newDebugOnlyOption("Vehicle.Render.Blood0", false);
    const BooleanDebugOption VehicleRenderBlood50 = this.newDebugOnlyOption("Vehicle.Render.Blood50", false);
    const BooleanDebugOption VehicleRenderBlood100 = this.newDebugOnlyOption("Vehicle.Render.Blood100", false);
    const BooleanDebugOption VehicleRenderDamage0 = this.newDebugOnlyOption("Vehicle.Render.Damage0", false);
    const BooleanDebugOption VehicleRenderDamage1 = this.newDebugOnlyOption("Vehicle.Render.Damage1", false);
    const BooleanDebugOption VehicleRenderDamage2 = this.newDebugOnlyOption("Vehicle.Render.Damage2", false);
    const BooleanDebugOption VehicleRenderRust0 = this.newDebugOnlyOption("Vehicle.Render.Rust0", false);
    const BooleanDebugOption VehicleRenderRust50 = this.newDebugOnlyOption("Vehicle.Render.Rust50", false);
    const BooleanDebugOption VehicleRenderRust100 = this.newDebugOnlyOption("Vehicle.Render.Rust100", false);
    const BooleanDebugOption VehicleRenderOutline = this.newOption("Vehicle.Render.Outline", false);
    const BooleanDebugOption VehicleRenderArea = this.newOption("Vehicle.Render.Area", false);
    const BooleanDebugOption VehicleRenderAuthorizations = this.newOption("Vehicle.Render.Authorizations", false);
    const BooleanDebugOption VehicleRenderInterpolateBuffer = this.newOption("Vehicle.Render.InterpolateBuffer", false);
    const BooleanDebugOption VehicleRenderAttackPositions = this.newOption("Vehicle.Render.AttackPositions", false);
    const BooleanDebugOption VehicleRenderExit = this.newOption("Vehicle.Render.Exit", false);
    const BooleanDebugOption VehicleRenderIntersectedSquares = this.newOption("Vehicle.Render.IntersectedSquares", false);
    const BooleanDebugOption VehicleRenderTrailerPositions = this.newDebugOnlyOption("Vehicle.Render.TrailerPositions", false);
    const BooleanDebugOption VehicleSpawnEverywhere = this.newDebugOnlyOption("Vehicle.Spawn.Everywhere", false);
    const BooleanDebugOption WorldSoundRender = this.newOption("Sound.WorldSound.Render", false);
    const BooleanDebugOption ObjectAmbientEmitterRender = this.newDebugOnlyOption("Sound.ObjectAmbientEmitter.Render", false);
    const BooleanDebugOption LightingRender = this.newOption("Lighting.Render", false);
    const BooleanDebugOption SkyboxShow = this.newOption("Skybox.Show", false);
    const BooleanDebugOption WorldStreamerSlowLoad = this.newOption("WorldStreamer.SlowLoad", false);
    const BooleanDebugOption DebugDraw_SkipVBODraw = this.newOption("DebugDraw.SkipVBODraw", false);
    const BooleanDebugOption DebugDraw_SkipDrawNonSkinnedModel = this.newOption("DebugDraw.SkipDrawNonSkinnedModel", false);
    const BooleanDebugOption DebugDraw_SkipWorldShading = this.newOption("DebugDraw.SkipWorldShading", false);
    const BooleanDebugOption GameProfilerEnabled = this.newOption("GameProfiler.Enabled", false);
    const BooleanDebugOption GameTimeSpeedHalf = this.newOption("GameTime.Speed.Half", false);
    const BooleanDebugOption GameTimeSpeedQuarter = this.newOption("GameTime.Speed.Quarter", false);
    const BooleanDebugOption ThreadCrash_Enabled = this.newDebugOnlyOption("ThreadCrash.Enable", false);
   public const BooleanDebugOption[] ThreadCrash_GameThread = new BooleanDebugOption[]{
      this.newDebugOnlyOption("ThreadCrash.MainThread.0", false),
      this.newDebugOnlyOption("ThreadCrash.MainThread.1", false),
      this.newDebugOnlyOption("ThreadCrash.MainThread.2", false)
   };
   public const BooleanDebugOption[] ThreadCrash_GameLoadingThread = new BooleanDebugOption[]{
      this.newDebugOnlyOption("ThreadCrash.GameLoadingThread.0", false)
   };
   public const BooleanDebugOption[] ThreadCrash_RenderThread = new BooleanDebugOption[]{
      this.newDebugOnlyOption("ThreadCrash.RenderThread.0", false),
      this.newDebugOnlyOption("ThreadCrash.RenderThread.1", false),
      this.newDebugOnlyOption("ThreadCrash.RenderThread.2", false)
   };
    const BooleanDebugOption WorldChunkMap5x5 = this.newDebugOnlyOption("World.ChunkMap.5x5", false);
    const BooleanDebugOption ZombieRenderCanCrawlUnderVehicle = this.newDebugOnlyOption("Zombie.Render.CanCrawlUnderVehicle", false);
    const BooleanDebugOption ZombieRenderFakeDead = this.newDebugOnlyOption("Zombie.Render.FakeDead", false);
    const BooleanDebugOption ZombieRenderMemory = this.newDebugOnlyOption("Zombie.Render.Memory", false);
    const BooleanDebugOption ZombieOutfitRandom = this.newDebugOnlyOption("Zombie.Outfit.Random", false);
    const Checks Checks = this.newOptionGroup(std::make_shared<Checks>());
    const IsoSprite IsoSprite = this.newOptionGroup(std::make_shared<IsoSprite>());
    const Network Network = this.newOptionGroup(std::make_shared<Network>());
    const OffscreenBuffer OffscreenBuffer = this.newOptionGroup(std::make_shared<OffscreenBuffer>());
    const Terrain Terrain = this.newOptionGroup(std::make_shared<Terrain>());
    const Weather Weather = this.newOptionGroup(std::make_shared<Weather>());
    const Animation Animation = this.newOptionGroup(std::make_shared<Animation>());
    const char char = this.newOptionGroup(std::make_shared<char>());
    static PredicatedFileWatcher m_triggerWatcher;

    void init() {
      this.load();
      this.initMessaging();
   }

    void initMessaging() {
      if (m_triggerWatcher == nullptr) {
         m_triggerWatcher = std::make_shared<PredicatedFileWatcher>(
            ZomboidFileSystem.instance.getMessagingDirSub("Trigger_SetDebugOptions.xml"), this::onTrigger_SetDebugOptions
         );
         DebugFileWatcher.instance.push_back(m_triggerWatcher);
      }

    DebugOptionsXml var1 = std::make_shared<DebugOptionsXml>();
      var1.setDebugMode = true;
      var1.debugMode = Core.bDebug;

      for (BooleanDebugOption var3 : this.options) {
         var1.options.push_back(std::make_shared<OptionNode>(var3.getName(), var3.getValue()));
      }

    std::string var4 = ZomboidFileSystem.instance.getMessagingDirSub("DebugOptions_list.xml");
      PZXmlUtil.tryWrite(var1, std::make_shared<File>(var4));
   }

    void onTrigger_SetDebugOptions(const std::string& var1) {
      try {
         DebugOptionsXml var2 = (DebugOptionsXml)PZXmlUtil.parse(
            DebugOptionsXml.class, ZomboidFileSystem.instance.getMessagingDirSub("Trigger_SetDebugOptions.xml")
         );

         for (OptionNode var4 : var2.options) {
            this.setBoolean(var4.name, var4.value);
         }

         if (var2.setDebugMode) {
            DebugLog.General.println("DebugMode: %s", var2.debugMode ? "ON" : "OFF");
            Core.bDebug = var2.debugMode;
         }
      } catch (PZXmlParserException var5) {
         ExceptionLogger.logException(var5, "Exception thrown parsing Trigger_SetDebugOptions.xml");
      }
   }

   public Iterable<IDebugOption> getChildren() {
      return PZArrayUtil.listConvert(this.options, var0 -> var0);
   }

    void addChild(IDebugOption var1) {
      this.m_options.push_back(var1);
      var1.setParent(this);
      this.onChildAdded(var1);
   }

    void onChildAdded(IDebugOption var1) {
      this.onDescendantAdded(var1);
   }

    void onDescendantAdded(IDebugOption var1) {
      this.addOption(var1);
   }

    void addOption(IDebugOption var1) {
    BooleanDebugOption var2 = (BooleanDebugOption)Type.tryCastTo(var1, BooleanDebugOption.class);
      if (var2 != nullptr) {
         this.options.push_back(var2);
      }

    IDebugOptionGroup var3 = (IDebugOptionGroup)Type.tryCastTo(var1, IDebugOptionGroup.class);
      if (var3 != nullptr) {
         this.addDescendantOptions(var3);
      }
   }

    void addDescendantOptions(IDebugOptionGroup var1) {
      for (IDebugOption var3 : var1.getChildren()) {
         this.addOption(var3);
      }
   }

    std::string getName() {
      return "DebugOptions";
   }

    IDebugOptionGroup getParent() {
    return nullptr;
   }

    void setParent(IDebugOptionGroup var1) {
      throw UnsupportedOperationException("DebugOptions is a root not. Cannot have a parent.");
   }

    BooleanDebugOption newOption(const std::string& var1, bool var2) {
    BooleanDebugOption var3 = OptionGroup.newOption(var1, var2);
      this.addChild(var3);
    return var3;
   }

    BooleanDebugOption newDebugOnlyOption(const std::string& var1, bool var2) {
    BooleanDebugOption var3 = OptionGroup.newDebugOnlyOption(var1, var2);
      this.addChild(var3);
    return var3;
   }

   private <E : public IDebugOptionGroup> E newOptionGroup(E var1) {
      this.addChild(var1);
      return (E)var1;
   }

    BooleanDebugOption getOptionByName(const std::string& var1) {
      for (int var2 = 0; var2 < this.options.size(); var2++) {
    BooleanDebugOption var3 = this.options.get(var2);
         if (var3.getName() == var1)) {
    return var3;
         }
      }

    return nullptr;
   }

    int getOptionCount() {
      return this.options.size();
   }

    BooleanDebugOption getOptionByIndex(int var1) {
      return this.options.get(var1);
   }

    void setBoolean(const std::string& var1, bool var2) {
    BooleanDebugOption var3 = this.getOptionByName(var1);
      if (var3 != nullptr) {
         var3.setValue(var2);
      }
   }

    bool getBoolean(const std::string& var1) {
    BooleanDebugOption var2 = this.getOptionByName(var1);
      return var2 != nullptr ? var2.getValue() : false;
   }

    void save() {
    std::string var1 = ZomboidFileSystem.instance.getCacheDirSub("debug-options.ini");
    ConfigFile var2 = std::make_shared<ConfigFile>();
      var2.write(var1, 1, this.options);
   }

    void load() {
    std::string var1 = ZomboidFileSystem.instance.getCacheDirSub("debug-options.ini");
    ConfigFile var2 = std::make_shared<ConfigFile>();
      if (var2.read(var1)) {
         for (int var3 = 0; var3 < var2.getOptions().size(); var3++) {
    ConfigOption var4 = (ConfigOption)var2.getOptions().get(var3);
    BooleanDebugOption var5 = this.getOptionByName(var4.getName());
            if (var5 != nullptr) {
               var5.parse(var4.getValueAsString());
            }
         }
      }
   }

    static void testThreadCrash(int var0) {
      instance.testThreadCrashInternal(var0);
   }

    void testThreadCrashInternal(int var1) {
      if (Core.bDebug) {
         if (this.ThreadCrash_Enabled.getValue()) {
    Thread var2 = Thread.currentThread();
            BooleanDebugOption[] var3;
            if (var2 == RenderThread.RenderThread) {
               var3 = this.ThreadCrash_RenderThread;
            } else if (var2 == GameWindow.GameThread) {
               var3 = this.ThreadCrash_GameThread;
            } else {
               if (var2 != GameLoadingState.loader) {
                  return;
               }

               var3 = this.ThreadCrash_GameLoadingThread;
            }

            if (var3[var1].getValue()) {
               throw Error("ThreadCrash Test! " + var2.getName());
            }
         }
      }
   }
}
} // namespace debug
} // namespace zombie
