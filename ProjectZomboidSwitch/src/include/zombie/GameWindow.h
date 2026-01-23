#pragma once
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/FMODManager.h"
#include "fmod/fmod/FMODSoundBank.h"
#include "GraphicsWrapper/GL.h"
#include "GraphicsWrapper/GL11.h"
#include "GraphicsWrapper/GraphicsExceptions.h"
#include "GraphicsWrapper/Controller.h"
#include "GraphicsWrapper/Display.h"
#include "GraphicsWrapper/DisplayMode.h"
#include "GraphicsWrapper/OpenGLException.h"
#include "zombie/GameWindow/StringUTF.h"
#include "zombie/GameWindow/TexturePack.h"
#include "zombie/GameWindow/s_performance.h"
#include "zombie/Lua/LuaEventManager.h"
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "zombie/asset/AssetManagers.h"
#include "zombie/audio/BaseSoundBank.h"
#include "zombie/audio/DummySoundBank.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/professions/ProfessionFactory.h"
#include "zombie/characters/skills/CustomPerks.h"
#include "zombie/characters/skills/PerkFactory.h"
#include "zombie/characters/traits/TraitFactory.h"
#include "zombie/core/Core.h"
#include "zombie/core/Languages.h"
#include "zombie/core/PerformanceSettings.h"
#include "zombie/core/Rand.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/ThreadGroups.h"
#include "zombie/core/Translator.h"
#include "zombie/core/input/Input.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/logger/ZipLogs.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/core/particle/MuzzleFlash.h"
#include "zombie/core/physics/Bullet.h"
#include "zombie/core/raknet/RakNetPeerInterface.h"
#include "zombie/core/raknet/VoiceManager.h"
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/core/skinnedmodel/population/BeardStyles.h"
#include "zombie/core/skinnedmodel/population/ClothingDecals.h"
#include "zombie/core/skinnedmodel/population/HairStyles.h"
#include "zombie/core/skinnedmodel/population/OutfitManager.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/core/textures/TextureID.h"
#include "zombie/core/textures/TexturePackPage.h"
#include "zombie/core/znet/ServerBrowser.h"
#include "zombie/core/znet/SteamFriends.h"
#include "zombie/core/znet/SteamUtils.h"
#include "zombie/core/znet/SteamWorkshop.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/debug/LineDrawer.h"
#include "zombie/fileSystem/FileSystem.h"
#include "zombie/fileSystem/FileSystem/TexturePackTextures.h"
#include "zombie/fileSystem/FileSystemImpl.h"
#include "zombie/gameStates/GameLoadingState.h"
#include "zombie/gameStates/GameStateMachine.h"
#include "zombie/gameStates/IngameState.h"
#include "zombie/gameStates/MainScreenState.h"
#include "zombie/gameStates/TISLogoState.h"
#include "zombie/gameStates/TermsOfServiceState.h"
#include "zombie/globalObjects/SGlobalObjects.h"
#include "zombie/input/GameKeyboard.h"
#include "zombie/input/JoypadManager.h"
#include "zombie/input/JoypadManager/Joypad.h"
#include "zombie/input/Mouse.h"
#include "zombie/inventory/types/MapItem.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoObjectPicker.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/LightingJNI.h"
#include "zombie/iso/LightingThread.h"
#include "zombie/iso/SliceY.h"
#include "zombie/iso/WorldStreamer.h"
#include "zombie/network/CoopMaster.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/popman/ZombiePopulationManager.h"
#include "zombie/radio/ZomboidRadio.h"
#include "zombie/sandbox/CustomSandboxOptions.h"
#include "zombie/savefile/ClientPlayerDB.h"
#include "zombie/savefile/PlayerDB.h"
#include "zombie/savefile/SavefileThumbnail.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/spnetwork/SinglePlayerClient.h"
#include "zombie/spnetwork/SinglePlayerServer.h"
#include "zombie/ui/TextManager.h"
#include "zombie/ui/UIDebugConsole.h"
#include "zombie/ui/UIManager.h"
#include "zombie/util/PZSQLUtils.h"
#include "zombie/util/PublicServerUtil.h"
#include "zombie/vehicles/Clipper.h"
#include "zombie/vehicles/PolygonalMap2.h"
#include "zombie/world/moddata/GlobalModData.h"
#include "zombie/worldMap/WorldMapJNI.h"
#include "zombie/worldMap/WorldMapVisited.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {


class GameWindow {
   // Trigger a Lua event (call a global Lua function by name, with optional arguments)
   template<typename... Args>
   static bool TriggerLuaEvent(const std::string& eventName, Args... args) {
      if (!L) return false;
      lua_getglobal(L, eventName.c_str());
      if (!lua_isfunction(L, -1)) {
         lua_pop(L, 1);
         return false;
      }
      // Push arguments
      PushLuaArgs(args...);
      if (lua_pcall(L, sizeof...(Args), 0, 0) != LUA_OK) {
         const char* err = lua_tostring(L, -1);
         std::cerr << "Lua event error: " << (err ? err : "unknown") << std::endl;
         lua_pop(L, 1);
         return false;
      }
      return true;
   }

   // Helper to push arguments to Lua stack (recursive variadic template)
   static void PushLuaArgs() {}
   template<typename T, typename... Args>
   static void PushLuaArgs(T value, Args... args) {
      PushLuaArg(value);
      PushLuaArgs(args...);
   }
   // Overloads for supported types
   static void PushLuaArg(int v) { lua_pushinteger(L, v); }
   static void PushLuaArg(double v) { lua_pushnumber(L, v); }
   static void PushLuaArg(float v) { lua_pushnumber(L, v); }
   static void PushLuaArg(const std::string& v) { lua_pushlstring(L, v.c_str(), v.size()); }
   static void PushLuaArg(const char* v) { lua_pushstring(L, v); }
   static void PushLuaArg(bool v) { lua_pushboolean(L, v); }

   // Register a C++ function as a global Lua function
   static void RegisterLuaFunction(const char* name, lua_CFunction fn) {
      if (L) lua_register(L, name, fn);
   }

   // Example: Register all core C++ functions to Lua (expand as needed)
   static void RegisterCoreLuaFunctions() {
      // Example: RegisterLuaFunction("cpp_print", &CppPrint);
   }

   // Recursively load all Lua scripts in a directory
   static void LoadLuaDir(const std::string& dirPath) {
      namespace fs = std::filesystem;
      for (const auto& entry : fs::recursive_directory_iterator(dirPath)) {
         if (entry.is_regular_file() && entry.path().extension() == ".lua") {
            RunLuaScript(entry.path().string());
         }
      }
   }
public:
   // Lua state for scripting
   static lua_State* L;

   // Initialize Lua state
   static void InitLua() {
      L = luaL_newstate();
      luaL_openlibs(L);
      // TODO: Load base scripts, set up environment, register C++ functions if needed
      RegisterCoreLuaFunctions();
   }

   // Shutdown Lua state
   static void ShutdownLua() {
      if (L) {
         lua_close(L);
         L = nullptr;
      }
   }

   // Load and run a Lua script file
   static bool RunLuaScript(const std::string& filename) {
      if (!L) return false;
      if (luaL_dofile(L, filename.c_str()) != LUA_OK) {
         // Print error
         const char* err = lua_tostring(L, -1);
         std::cerr << "Lua error: " << (err ? err : "unknown") << std::endl;
         lua_pop(L, 1);
         return false;
      }
      return true;
   }
    static const std::string GAME_TITLE = "Project Zomboid";
    static const FPSTracking s_fpsTracking = std::make_shared<FPSTracking>();
   private static const ThreadLocal<StringUTF> stringUTF = ThreadLocal.withInitial(StringUTF::new);
    static const Input GameInput = std::make_shared<Input>();
    static bool DEBUG_SAVE = false;
    static bool OkToSaveOnExit = false;
    static std::string lastP = nullptr;
    static GameStateMachine states = std::make_shared<GameStateMachine>();
    static bool bServerDisconnected;
    static bool bLoadedAsClient = false;
    static std::string kickReason;
    static bool DrawReloadingLua = false;
    static Joypad ActivatedJoyPad = nullptr;
    static std::string version = "RC3";
   public static volatile boolean closeRequested;
    static float averageFPS = PerformanceSettings.getLockFPS();
    static bool doRenderEvent = false;
    static bool bLuaDebuggerKeyDown = false;
    static FileSystem fileSystem = std::make_shared<FileSystemImpl>();
    static AssetManagers assetManagers = std::make_shared<AssetManagers>(fileSystem);
    static bool bGameThreadExited = false;
    static Thread GameThread;
   public static const std::vector<TexturePack> texturePacks = std::make_unique<std::vector<>>();
    static const TexturePackTextures texturePackTextures = std::make_shared<TexturePackTextures>();

    static void initShared() {
    std::string var0 = ZomboidFileSystem.instance.getCacheDir() + File.separator;
    File var1 = std::make_shared<File>(var0);
      if (!var1.exists()) {
         var1.mkdirs();
      }

      TexturePackPage.bIgnoreWorldItemTextures = true;
    uint8_t var2 = 2;
      LoadTexturePack("UI", var2);
      LoadTexturePack("UI2", var2);
      LoadTexturePack("IconsMoveables", var2);
      LoadTexturePack("RadioIcons", var2);
      LoadTexturePack("ApComUI", var2);
      LoadTexturePack("Mechanics", var2);
      LoadTexturePack("WeatherFx", var2);
      setTexturePackLookup();
      PerkFactory.init();
      CustomPerks.instance.init();
      DoLoadingText(Translator.getText("UI_Loading_Scripts"));
      ScriptManager.instance.Load();
      DoLoadingText(Translator.getText("UI_Loading_Clothing"));
      ClothingDecals.init();
      BeardStyles.init();
      HairStyles.init();
      OutfitManager.init();
      DoLoadingText("");
      TraitFactory.init();
      ProfessionFactory.init();
      Rand.init();
      TexturePackPage.bIgnoreWorldItemTextures = false;
      TextureID.bUseCompression = TextureID.bUseCompressionOption;
      MuzzleFlash.init();
      Mouse.initCustomCursor();
      if (!Core.bDebug) {
         states.States.push_back(std::make_unique<TISLogoState>());
      }

      states.States.push_back(std::make_unique<TermsOfServiceState>());
      states.States.push_back(std::make_unique<MainScreenState>());
      if (!Core.bDebug) {
         states.LoopToState = 1;
      }

      GameInput.initControllers();
      if (Core.getInstance().isDefaultOptions() && SteamUtils.isSteamModeEnabled() && SteamUtils.isRunningOnSteamDeck()) {
         Core.getInstance().setOptionActiveController(0, true);
      }

    int var3 = GameInput.getControllerCount();
      DebugLog.Input.println("----------------------------------------------");
      DebugLog.Input.println("--    Information about controllers     ");
      DebugLog.Input.println("----------------------------------------------");

      for (int var4 = 0; var4 < var3; var4++) {
    Controller var5 = GameInput.getController(var4);
         if (var5 != nullptr) {
            DebugLog.Input.println("----------------------------------------------");
            DebugLog.Input.println("--  Joypad: " + var5.getGamepadName());
            DebugLog.Input.println("----------------------------------------------");
    int var6 = var5.getAxisCount();
            if (var6 > 1) {
               DebugLog.Input.println("----------------------------------------------");
               DebugLog.Input.println("--    Axis definitions for controller " + var4);
               DebugLog.Input.println("----------------------------------------------");

               for (int var7 = 0; var7 < var6; var7++) {
    std::string var8 = var5.getAxisName(var7);
                  DebugLog.Input.println("Axis: " + var8);
               }
            }

            var6 = var5.getButtonCount();
            if (var6 > 1) {
               DebugLog.Input.println("----------------------------------------------");
               DebugLog.Input.println("--    Button definitions for controller " + var4);
               DebugLog.Input.println("----------------------------------------------");

               for (int var10 = 0; var10 < var6; var10++) {
    std::string var11 = var5.getButtonName(var10);
                  DebugLog.Input.println("Button: " + var11);
               }
            }
         }
      }
   }

    static void logic() {
      if (GameClient.bClient) {
         try {
            GameClient.instance.update();
         } catch (Exception var3) {
            ExceptionLogger.logException(var3);
         }
      }

      try {
         SinglePlayerServer.update();
         SinglePlayerClient.update();
      } catch (Throwable var2) {
         ExceptionLogger.logException(var2);
      }

      SteamUtils.runLoop();
      Mouse.update();
      GameKeyboard.update();
      GameInput.updateGameThread();
      if (CoopMaster.instance != nullptr) {
         CoopMaster.instance.update();
      }

      if (IsoPlayer.players[0] != nullptr) {
         IsoPlayer.setInstance(IsoPlayer.players[0]);
         IsoCamera.CamCharacter = IsoPlayer.players[0];
      }

      UIManager.update();
      VoiceManager.instance.update();
      LineDrawer.clear();
      if (JoypadManager.instance.isAPressed(-1)) {
         for (int var0 = 0; var0 < JoypadManager.instance.JoypadList.size(); var0++) {
    Joypad var1 = (Joypad)JoypadManager.instance.JoypadList.get(var0);
            if (var1.isAPressed()) {
               if (ActivatedJoyPad == nullptr) {
                  ActivatedJoyPad = var1;
               }

               if (IsoPlayer.getInstance() != nullptr) {
                  LuaEventManager.triggerEvent("OnJoypadActivate", var1.getID());
               } else {
                  LuaEventManager.triggerEvent("OnJoypadActivateUI", var1.getID());
               }
               break;
            }
         }
      }

      SoundManager.instance.Update();
    bool var4 = true;
      if (GameTime.isGamePaused()) {
         var4 = false;
      }

      MapCollisionData.instance.updateGameState();
      Mouse.setCursorVisible(true);
      if (var4) {
         states.update();
      } else {
         IsoCamera.updateAll();
         if (IngameState.instance != nullptr && (states.current == IngameState.instance || states.States.contains(IngameState.instance))) {
            LuaEventManager.triggerEvent("OnTickEvenPaused", 0.0);
         }
      }

      UIManager.resize();
      fileSystem.updateAsyncTransactions();
      if (GameKeyboard.isKeyPressed(Core.getInstance().getKey("Take screenshot"))) {
         Core.getInstance().TakeFullScreenshot(nullptr);
      }
   }

    static void render() {
      IsoCamera.frameState.frameCount++;
      renderInternal();
   }

    static void renderInternal() {
      if (!PerformanceSettings.LightingThread && LightingJNI.init && !LightingJNI.WaitingForMain()) {
         LightingJNI.DoLightingUpdateNew(System.nanoTime());
      }

      IsoObjectPicker.Instance.StartRender();
      s_performance.statesRender.invokeAndMeasure(states, GameStateMachine::render);
   }

    static void InitDisplay() {
      Display.setTitle("Project Zomboid");
      if (!Core.getInstance().loadOptions()) {
    int var0 = Runtime.getRuntime().availableProcessors();
         if (var0 == 1) {
            PerformanceSettings.LightingFrameSkip = 3;
         } else if (var0 == 2) {
            PerformanceSettings.LightingFrameSkip = 2;
         } else if (var0 <= 4) {
            PerformanceSettings.LightingFrameSkip = 1;
         }

         Core.setFullScreen(true);
         Display.setFullscreen(true);
         Display.setResizable(false);
    DisplayMode var1 = Display.getDesktopDisplayMode();
         Core.getInstance().init(var1.getWidth(), var1.getHeight());
         if (!GL.getCapabilities().GL_ATI_meminfo && !GL.getCapabilities().GL_NVX_gpu_memory_info) {
            DebugLog.General.warn("Unable to determine available GPU memory, texture compression defaults to on");
            TextureID.bUseCompressionOption = true;
            TextureID.bUseCompression = true;
         }

         DebugLog.log("Init language : " + System.getProperty("user.language"));
         Core.getInstance().setOptionLanguageName(System.getProperty("user.language").toUpperCase());
         Core.getInstance().saveOptions();
      } else {
         Core.getInstance().init(Core.getInstance().getScreenWidth(), Core.getInstance().getScreenHeight());
      }

      if (GL.getCapabilities().GL_ATI_meminfo) {
    int var2 = GL11.glGetInteger(34812);
         DebugLog.log("ATI: available texture memory is " + var2 / 1024 + " MB");
      }

      if (GL.getCapabilities().GL_NVX_gpu_memory_info) {
    int var3 = GL11.glGetInteger(36937);
         DebugLog.log("NVIDIA: current available GPU memory is " + var3 / 1024 + " MB");
         var3 = GL11.glGetInteger(36935);
         DebugLog.log("NVIDIA: dedicated available GPU memory is " + var3 / 1024 + " MB");
         var3 = GL11.glGetInteger(36936);
         DebugLog.log("NVIDIA: total available GPU memory is " + var3 / 1024 + " MB");
      }

      SpriteRenderer.instance.create();
   }

    static void InitGameThread() {
      Thread.setDefaultUncaughtExceptionHandler(GameWindow::uncaughtGlobalException);
    Thread var0 = std::make_shared<Thread>(ThreadGroups.Main, GameWindow::mainThread, "MainThread");
      var0.setUncaughtExceptionHandler(GameWindow::uncaughtExceptionMainThread);
      GameThread = var0;
      var0.start();
   }

    static void uncaughtExceptionMainThread(Thread var0, std::exception var1) {
      if (dynamic_cast<ThreadDeath*>(var1) != nullptr) {
         DebugLog.General.println("Game Thread exited: ", var0.getName());
      } else {
         try {
            uncaughtException(var0, var1);
         } finally {
            onGameThreadExited();
         }
      }
   }

    static void uncaughtGlobalException(Thread var0, std::exception var1) {
      if (dynamic_cast<ThreadDeath*>(var1) != nullptr) {
         DebugLog.General.println("External Thread exited: ", var0.getName());
      } else {
         uncaughtException(var0, var1);
      }
   }

    static void uncaughtException(Thread var0, std::exception var1) {
      if (dynamic_cast<ThreadDeath*>(var1) != nullptr) {
         DebugLog.General.println("Internal Thread exited: ", var0.getName());
      } else {
    std::string var2 = std::string.format("Unhandled %s thrown by thread %s.", var1.getClass().getName(), var0.getName());
         DebugLog.General.error(var2);
         ExceptionLogger.logException(var1, var2);
      }
   }

    static void mainThread() {
      mainThreadInit();
      enter();
      RenderThread.setWaitForRenderState(true);
      run_ez();
   }

    static void mainThreadInit() {
    std::string var0 = System.getProperty("debug");
    std::string var1 = System.getProperty("nosave");
      if (var1 != nullptr) {
         Core.getInstance().setNoSave(true);
      }

      if (var0 != nullptr) {
         Core.bDebug = true;
      }

      if (!Core.SoundDisabled) {
         FMODManager.instance.init();
      }

      DebugOptions.instance.init();
      GameProfiler.init();
      SoundManager.instance = (BaseSoundManager)(Core.SoundDisabled ? std::make_unique<DummySoundManager>() : std::make_unique<SoundManager>());
      AmbientStreamManager.instance = (BaseAmbientStreamManager)(Core.SoundDisabled ? std::make_unique<DummyAmbientStreamManager>() : std::make_unique<AmbientStreamManager>());
      BaseSoundBank.instance = (BaseSoundBank)(Core.SoundDisabled ? std::make_unique<DummySoundBank>() : std::make_unique<FMODSoundBank>());
      VoiceManager.instance.loadConfig();
      TextureID.bUseCompressionOption = Core.SafeModeForced || Core.getInstance().getOptionTextureCompression();
      TextureID.bUseCompression = TextureID.bUseCompressionOption;
      SoundManager.instance.setSoundVolume(Core.getInstance().getOptionSoundVolume() / 10.0F);
      SoundManager.instance.setMusicVolume(Core.getInstance().getOptionMusicVolume() / 10.0F);
      SoundManager.instance.setAmbientVolume(Core.getInstance().getOptionAmbientVolume() / 10.0F);
      SoundManager.instance.setVehicleEngineVolume(Core.getInstance().getOptionVehicleEngineVolume() / 10.0F);

      try {
         ZomboidFileSystem.instance.init();
      } catch (Exception var7) {
         throw RuntimeException(var7);
      }

      DebugFileWatcher.instance.init();
    std::string var2 = System.getProperty("server");
    std::string var3 = System.getProperty("client");
    std::string var4 = System.getProperty("nozombies");
      if (var4 != nullptr) {
         IsoWorld.NoZombies = true;
      }

      if (var2 != nullptr && var2 == "true")) {
         GameServer.bServer = true;
      }

      try {
         renameSaveFolders();
         init();
      } catch (Exception var6) {
         throw RuntimeException(var6);
      }
   }

    static void renameSaveFolders() {
    std::string var0 = ZomboidFileSystem.instance.getSaveDir();
    File var1 = std::make_shared<File>(var0);
      if (var1.exists() && var1.isDirectory()) {
    File var2 = std::make_shared<File>(var1, "Fighter");
    File var3 = std::make_shared<File>(var1, "Survivor");
         if (var2.exists() && var2.isDirectory() && var3.exists() && var3.isDirectory()) {
            DebugLog.log("RENAMING Saves/Survivor to Saves/Apocalypse");
            DebugLog.log("RENAMING Saves/Fighter to Saves/Survivor");
            var3.renameTo(std::make_shared<File>(var1, "Apocalypse"));
            var2.renameTo(std::make_shared<File>(var1, "Survivor"));
    File var4 = std::make_shared<File>(ZomboidFileSystem.instance.getCacheDir() + File.separator + "latestSave.ini");
            if (var4.exists()) {
               var4.delete();
            }
         }
      }
   }

    static long readLong(DataInputStream var0) {
    int var1 = var0.read();
    int var2 = var0.read();
    int var3 = var0.read();
    int var4 = var0.read();
    int var5 = var0.read();
    int var6 = var0.read();
    int var7 = var0.read();
    int var8 = var0.read();
      if ((var1 | var2 | var3 | var4 | var5 | var6 | var7 | var8) < 0) {
         throw std::make_unique<EOFException>();
      } else {
         return var1 + (var2 << 8) + (var3 << 16) + (var4 << 24) + (var5 << 32) + (var6 << 40) + (var7 << 48) + (var8 << 56);
      }
   }

    static int readInt(DataInputStream var0) {
    int var1 = var0.read();
    int var2 = var0.read();
    int var3 = var0.read();
    int var4 = var0.read();
      if ((var1 | var2 | var3 | var4) < 0) {
         throw std::make_unique<EOFException>();
      } else {
         return var1 + (var2 << 8) + (var3 << 16) + (var4 << 24);
      }
   }

    static void run_ez() {
    long var0 = System.nanoTime();
    long var2 = 0L;

      while (!RenderThread.isCloseRequested() && !closeRequested) {
    long var4 = System.nanoTime();
         if (var4 < var0) {
            var0 = var4;
         } else {
    long var6 = var4 - var0;
            var0 = var4;
            if (PerformanceSettings.isUncappedFPS()) {
               frameStep();
            } else {
               var2 += var6;
    long var8 = PZMath.secondsToNanos / PerformanceSettings.getLockFPS();
               if (var2 >= var8) {
                  frameStep();
                  var2 %= var8;
               }
            }

            if (Core.bDebug && DebugOptions.instance.ThreadCrash_Enabled.getValue()) {
               DebugOptions.testThreadCrash(0);
               RenderThread.invokeOnRenderContext(() -> DebugOptions.testThreadCrash(1));
            }

            Thread.yield();
         }
      }

      exit();
   }

    static void enter() {
      Core.TileScale = Core.getInstance().getOptionTexture2x() ? 2 : 1;
      if (Core.SafeModeForced) {
         Core.TileScale = 1;
      }

      IsoCamera.init();
    int var0 = TextureID.bUseCompression ? 4 : 0;
      var0 |= 64;
      if (Core.TileScale == 1) {
         LoadTexturePack("Tiles1x", var0);
         LoadTexturePack("Overlays1x", var0);
         LoadTexturePack("JumboTrees1x", var0);
         LoadTexturePack("Tiles1x.floor", var0 & -5);
      }

      if (Core.TileScale == 2) {
         LoadTexturePack("Tiles2x", var0);
         LoadTexturePack("Overlays2x", var0);
         LoadTexturePack("JumboTrees2x", var0);
         LoadTexturePack("Tiles2x.floor", var0 & -5);
      }

      setTexturePackLookup();
      if (Texture.getSharedTexture("TileIndieStoneTentFrontLeft") == nullptr) {
         throw RuntimeException("Rebuild Tiles.pack with \"1 Include This in .pack\" as individual images not tilesheets");
      } else {
         DebugLog.log("LOADED UP A TOTAL OF " + Texture.totalTextureID + " TEXTURES");
         s_fpsTracking.init();
         DoLoadingText(Translator.getText("UI_Loading_ModelsAnimations"));
         ModelManager.instance.create();
         if (!SteamUtils.isSteamModeEnabled()) {
            DoLoadingText(Translator.getText("UI_Loading_InitPublicServers"));
            PublicServerUtil.init();
         }

         VoiceManager.instance.InitVMClient();
         DoLoadingText(Translator.getText("UI_Loading_OnGameBoot"));
         LuaEventManager.triggerEvent("OnGameBoot");
      }
   }

    static void frameStep() {
      try {
         IsoCamera.frameState.frameCount++;
         s_performance.frameStep.start();
         s_fpsTracking.frameStep();
         s_performance.logic.invokeAndMeasure(GameWindow::logic);
         Core.getInstance().setScreenSize(RenderThread.getDisplayWidth(), RenderThread.getDisplayHeight());
         renderInternal();
         if (doRenderEvent) {
            LuaEventManager.triggerEvent("OnRenderTick");
         }

         Core.getInstance().DoFrameReady();
         LightingThread.instance.update();
         if (Core.bDebug) {
            if (GameKeyboard.isKeyDown(Core.getInstance().getKey("Toggle Lua Debugger"))) {
               if (!bLuaDebuggerKeyDown) {
                  UIManager.setShowLuaDebuggerOnError(true);
                  // TODO: Replace with Lua C API debug hooks if needed
                  bLuaDebuggerKeyDown = true;
                  if (GameClient.bClient && states.current == IngameState.instance) {
                     GameClient.sendServerPing(-1L);
                  }
               }
            } else {
               bLuaDebuggerKeyDown = false;
            }

            if (GameKeyboard.isKeyPressed(Core.getInstance().getKey("ToggleLuaConsole"))) {
    UIDebugConsole var0 = UIManager.getDebugConsole();
               if (var0 != nullptr) {
                  var0.setVisible(!var0.isVisible());
               }
            }
         }
      } catch (OpenGLException var5) {
         RenderThread.logGLException(var5);
      } catch (Exception var6) {
         ExceptionLogger.logException(var6);
      } finally {
         s_performance.frameStep.end();
      }
   }

    static void exit() {
      DebugLog.log("EXITDEBUG: GameWindow.exit 1");
      if (GameClient.bClient) {
         for (int var0 = 0; var0 < IsoPlayer.numPlayers; var0++) {
    IsoPlayer var1 = IsoPlayer.players[var0];
            if (var1 != nullptr) {
               ClientPlayerDB.getInstance().clientSendNetworkPlayerInt(var1);
            }
         }

         WorldStreamer.instance.stop();
         GameClient.instance.doDisconnect("exit");
         VoiceManager.instance.DeinitVMClient();
      }

      if (OkToSaveOnExit) {
         try {
            WorldStreamer.instance.quit();
         } catch (Exception var7) {
            var7.printStackTrace();
         }

         if (PlayerDB.isAllow()) {
            PlayerDB.getInstance().saveLocalPlayersForce();
            PlayerDB.getInstance().m_canSavePlayers = false;
         }

         if (ClientPlayerDB.isAllow()) {
            ClientPlayerDB.getInstance().canSavePlayers = false;
         }

         try {
            if (GameClient.bClient && GameClient.connection != nullptr) {
               GameClient.connection.username = nullptr;
            }

            save(true);
         } catch (Throwable var6) {
            var6.printStackTrace();
         }

         try {
            if (IsoWorld.instance.CurrentCell != nullptr) {
               LuaEventManager.triggerEvent("OnPostSave");
            }
         } catch (Exception var5) {
            var5.printStackTrace();
         }

         try {
            if (IsoWorld.instance.CurrentCell != nullptr) {
               LuaEventManager.triggerEvent("OnPostSave");
            }
         } catch (Exception var4) {
            var4.printStackTrace();
         }

         try {
            LightingThread.instance.stop();
            MapCollisionData.instance.stop();
            ZombiePopulationManager.instance.stop();
            PolygonalMap2.instance.stop();
            ZombieSpawnRecorder.instance.quit();
         } catch (Exception var3) {
            var3.printStackTrace();
         }
      }

      DebugLog.log("EXITDEBUG: GameWindow.exit 2");
      if (GameClient.bClient) {
         WorldStreamer.instance.stop();
         GameClient.instance.doDisconnect("exit-saving");

         try {
            Thread.sleep(500L);
         } catch (InterruptedException var2) {
            var2.printStackTrace();
         }
      }

      DebugLog.log("EXITDEBUG: GameWindow.exit 3");
      if (PlayerDB.isAvailable()) {
         PlayerDB.getInstance().close();
      }

      if (ClientPlayerDB.isAvailable()) {
         ClientPlayerDB.getInstance().close();
      }

      DebugLog.log("EXITDEBUG: GameWindow.exit 4");
      GameClient.instance.Shutdown();
      SteamUtils.shutdown();
      ZipLogs.addZipFile(true);
      onGameThreadExited();
      DebugLog.log("EXITDEBUG: GameWindow.exit 5");
   }

    static void onGameThreadExited() {
      bGameThreadExited = true;
      RenderThread.onGameThreadExited();
   }

    static void setTexturePackLookup() {
      texturePackTextures.clear();

      for (int var0 = texturePacks.size() - 1; var0 >= 0; var0--) {
    TexturePack var1 = texturePacks.get(var0);
         if (var1.modID == nullptr) {
            texturePackTextures.putAll(var1.textures);
         }
      }

    std::vector var3 = ZomboidFileSystem.instance.getModIDs();

      for (int var4 = texturePacks.size() - 1; var4 >= 0; var4--) {
    TexturePack var2 = texturePacks.get(var4);
         if (var2.modID != nullptr && var3.contains(var2.modID)) {
            texturePackTextures.putAll(var2.textures);
         }
      }

      Texture.onTexturePacksChanged();
   }

    static void LoadTexturePack(const std::string& var0, int var1) {
      LoadTexturePack(var0, var1, nullptr);
   }

    static void LoadTexturePack(const std::string& var0, int var1, const std::string& var2) {
      DebugLog.General.println("texturepack: loading " + var0);
      DoLoadingText(Translator.getText("UI_Loading_Texturepack", var0));
    std::string var3 = ZomboidFileSystem.instance.getString("media/texturepacks/" + var0 + ".pack");
    TexturePack var4 = std::make_shared<TexturePack>();
      var4.packName = var0;
      var4.fileName = var3;
      var4.modID = var2;
      fileSystem.mountTexturePack(var0, var4.textures, var1);
      texturePacks.push_back(var4);
   }

    static void LoadTexturePackDDS(const std::string& var0) {
      DebugLog.log("texturepack: loading " + var0);
      if (SpriteRenderer.instance != nullptr) {
         Core.getInstance().StartFrame();
         Core.getInstance().EndFrame(0);
         Core.getInstance().StartFrameUI();
         SpriteRenderer.instance.renderi(nullptr, 0, 0, Core.getInstance().getScreenWidth(), Core.getInstance().getScreenHeight(), 0.0F, 0.0F, 0.0F, 1.0F, nullptr);
         TextManager.instance
            .DrawStringCentre(
               Core.getInstance().getScreenWidth() / 2,
               Core.getInstance().getScreenHeight() / 2,
               Translator.getText("UI_Loading_Texturepack", var0),
               1.0,
               1.0,
               1.0,
               1.0
            );
         Core.getInstance().EndFrameUI();
      }

    FileInputStream var1 = nullptr;

      try {
         var1 = std::make_shared<FileInputStream>(ZomboidFileSystem.instance.getString("media/texturepacks/" + var0 + ".pack"));
      } catch (FileNotFoundException var7) {
         Logger.getLogger(GameLoadingState.class.getName()).log(Level.SEVERE, nullptr, var7);
      }

      try (BufferedInputStream var2 = std::make_shared<BufferedInputStream>(var1)) {
    int var3 = TexturePackPage.readInt(var2);

         for (int var4 = 0; var4 < var3; var4++) {
    TexturePackPage var5 = std::make_shared<TexturePackPage>();
            if (var4 % 100 == 0 && SpriteRenderer.instance != nullptr) {
               Core.getInstance().StartFrame();
               Core.getInstance().EndFrame();
               Core.getInstance().StartFrameUI();
               TextManager.instance
                  .DrawStringCentre(
                     Core.getInstance().getScreenWidth() / 2,
                     Core.getInstance().getScreenHeight() / 2,
                     Translator.getText("UI_Loading_Texturepack", var0),
                     1.0,
                     1.0,
                     1.0,
                     1.0
                  );
               Core.getInstance().EndFrameUI();
               RenderThread.invokeOnRenderContext(Display::update);
            }

            var5.loadFromPackFileDDS(var2);
         }

         DebugLog.log("texturepack: finished loading " + var0);
      } catch (Exception var9) {
         DebugLog.log("media/texturepacks/" + var0 + ".pack");
         var9.printStackTrace();
      }

      Texture.nullTextures.clear();
   }

    static void installRequiredLibrary(const std::string& var0, const std::string& var1) {
      if (std::make_shared<File>(var0).exists()) {
         DebugLog.log("Attempting to install " + var1);
         DebugLog.log("Running " + var0 + ".");
    ProcessBuilder var2 = std::make_shared<ProcessBuilder>(var0, "/quiet", "/norestart");

         try {
    Process var3 = var2.start();
    int var4 = var3.waitFor();
            DebugLog.log("Process exited with code " + var4);
            return;
         } catch (InterruptedException | IOException var5) {
            var5.printStackTrace();
         }
      }

      DebugLog.log("Please install " + var1);
   }

    static void checkRequiredLibraries() {
      if (System.getProperty("os.name").startsWith("Win")) {
    std::string var0;
    std::string var1;
    std::string var2;
    std::string var3;
         if (System.getProperty("sun.arch.data.model") == "64")) {
            var0 = "Lighting64";
            var1 = "_CommonRedist\\vcredist\\2010\\vcredist_x64.exe";
            var2 = "_CommonRedist\\vcredist\\2012\\vcredist_x64.exe";
            var3 = "_CommonRedist\\vcredist\\2013\\vcredist_x64.exe";
         } else {
            var0 = "Lighting32";
            var1 = "_CommonRedist\\vcredist\\2010\\vcredist_x86.exe";
            var2 = "_CommonRedist\\vcredist\\2012\\vcredist_x86.exe";
            var3 = "_CommonRedist\\vcredist\\2013\\vcredist_x86.exe";
         }

         if ("1" == System.getProperty("zomboid.debuglibs.lighting"))) {
            DebugLog.log("***** Loading debug version of Lighting");
            var0 = var0 + "d";
         }

         try {
            System.loadLibrary(var0);
         } catch (UnsatisfiedLinkError var5) {
            DebugLog.log("Error loading " + var0 + ".dll.  Your system may be missing a required DLL.");
            installRequiredLibrary(var1, "the Microsoft Visual C++ 2010 Redistributable.");
            installRequiredLibrary(var2, "the Microsoft Visual C++ 2012 Redistributable.");
            installRequiredLibrary(var3, "the Microsoft Visual C++ 2013 Redistributable.");
         }
      }
   }

    static void init() {
      initFonts();
      checkRequiredLibraries();
      SteamUtils.init();
      ServerBrowser.init();
      SteamFriends.init();
      SteamWorkshop.init();
      RakNetPeerInterface.init();
      LightingJNI.init();
      ZombiePopulationManager.init();
      PZSQLUtils.init();
      Clipper.init();
      WorldMapJNI.init();
      Bullet.init();
    int var0 = Runtime.getRuntime().availableProcessors();
    std::string var1 = ZomboidFileSystem.instance.getCacheDir() + File.separator;
    File var2 = std::make_shared<File>(var1);
      if (!var2.exists()) {
         var2.mkdirs();
      }

      DoLoadingText("Loading Mods");
      ZomboidFileSystem.instance.resetDefaultModsForNewRelease("41_51");
      ZomboidFileSystem.instance.loadMods("default");
      ZomboidFileSystem.instance.loadModPackFiles();
      if (Core.getInstance().isDefaultOptions() && SteamUtils.isSteamModeEnabled() && SteamUtils.isRunningOnSteamDeck()) {
         Core.getInstance().setOptionFontSize(2);
         Core.getInstance().setOptionSingleContextMenu(0, true);
         Core.getInstance().setOptionShoulderButtonContainerSwitch(1);
         Core.getInstance().setAutoZoom(0, true);
         Core.getInstance().setOptionZoomLevels2x("75;125;150;175;200;225");
         Core.getInstance().setOptionPanCameraWhileAiming(true);
         Core.getInstance().setOptionPanCameraWhileDriving(true);
         Core.getInstance().setOptionTextureCompression(true);
         Core.getInstance();
         Core.OptionVoiceEnable = false;
      }

      DoLoadingText("Loading Translations");
      Languages.instance.init();
      Translator.language = nullptr;
      initFonts();
      Translator.loadFiles();
      initShared();
      DoLoadingText(Translator.getText("UI_Loading_Lua"));
      // TODO: Initialize Lua state and load base scripts using Lua C API
      CustomPerks.instance.initLua();
      CustomSandboxOptions.instance.init();
      CustomSandboxOptions.instance.initInstance(SandboxOptions.instance);
      // TODO: Load Lua base scripts using Lua C API
      ZomboidGlobals.Load();
      LuaEventManager.triggerEvent("OnLoadSoundBanks");
   }

    static void initFonts() {
      TextManager.instance.Init();

      while (TextManager.instance.font.empty()) {
         fileSystem.updateAsyncTransactions();

         try {
            Thread.sleep(10L);
         } catch (InterruptedException var1) {
         }
      }
   }

    static void save(bool var0) {
      if (!Core.getInstance().isNoSave()) {
         if (IsoWorld.instance.CurrentCell != nullptr
            && !"LastStand" == Core.getInstance().getGameMode())
            && !"Tutorial" == Core.getInstance().getGameMode())) {
    File var1 = ZomboidFileSystem.instance.getFileInCurrentSave("map_ver.bin");

            try (
    FileOutputStream var2 = std::make_shared<FileOutputStream>(var1);
    DataOutputStream var3 = std::make_shared<DataOutputStream>(var2);
            ) {
               var3.writeInt(195);
               WriteString(var3, Core.GameMap);
               WriteString(var3, IsoWorld.instance.getDifficulty());
            }

            var1 = ZomboidFileSystem.instance.getFileInCurrentSave("map_sand.bin");

            try (
    FileOutputStream var23 = std::make_shared<FileOutputStream>(var1);
    BufferedOutputStream var26 = std::make_shared<BufferedOutputStream>(var23);
            ) {
               SliceY.SliceBuffer.clear();
               SandboxOptions.instance.save(SliceY.SliceBuffer);
               var26.write(SliceY.SliceBuffer.array(), 0, SliceY.SliceBuffer.position());
            }

            LuaEventManager.triggerEvent("OnSave");

            try {
               try {
                  try {
                     if (Thread.currentThread() == GameThread) {
                        SavefileThumbnail.create();
                     }
                  } catch (Exception var14) {
                     ExceptionLogger.logException(var14);
                  }

                  var1 = ZomboidFileSystem.instance.getFileInCurrentSave("map.bin");

                  try (FileOutputStream var25 = std::make_shared<FileOutputStream>(var1)) {
    DataOutputStream var27 = std::make_shared<DataOutputStream>(var25);
                     IsoWorld.instance.CurrentCell.save(var27, var0);
                  } catch (Exception var13) {
                     ExceptionLogger.logException(var13);
                  }

                  try {
                     MapCollisionData.instance.save();
                     if (!bLoadedAsClient) {
                        SGlobalObjects.save();
                     }
                  } catch (Exception var10) {
                     ExceptionLogger.logException(var10);
                  }

                  ZomboidRadio.getInstance().Save();
                  GlobalModData.instance.save();
                  MapItem.SaveWorldMap();
                  WorldMapVisited.SaveAll();
               } catch (IOException var15) {
                  throw RuntimeException(var15);
               }
            } catch (RuntimeException var20) {
    std::exception var24 = var20.getCause();
               if (dynamic_cast<IOException*>(var24) != nullptr) {
                  throw (IOException)var24;
               } else {
    throw var20;
               }
            }
         }
      }
   }

    static std::string getCoopServerHome() {
    File var0 = std::make_shared<File>(ZomboidFileSystem.instance.getCacheDir());
      return var0.getParent();
   }

    static void WriteString(ByteBuffer var0, const std::string& var1) {
      WriteStringUTF(var0, var1);
   }

    static void WriteStringUTF(ByteBuffer var0, const std::string& var1) {
      stringUTF.get().save(var0, var1);
   }

    static void WriteString(DataOutputStream var0, const std::string& var1) {
      if (var1 == nullptr) {
         var0.writeInt(0);
      } else {
         var0.writeInt(var1.length());
         if (var1 != nullptr && var1.length() >= 0) {
            var0.writeChars(var1);
         }
      }
   }

    static std::string ReadStringUTF(ByteBuffer var0) {
      return stringUTF.get().load(var0);
   }

    static std::string ReadString(ByteBuffer var0) {
    return ReadStringUTF();
   }

    static std::string ReadString(DataInputStream var0) {
    int var1 = var0.readInt();
      if (var1 == 0) {
         return "";
      } else if (var1 > 65536) {
         throw RuntimeException("GameWindow.ReadString: string is too long, corrupted save?");
      } else {
    std::stringstream var2 = new std::stringstream(var1);

         for (int var3 = 0; var3 < var1; var3++) {
            var2.append(var0.readChar());
         }

         return var2;
      }
   }

    static void doRenderEvent(bool var0) {
      doRenderEvent = var0;
   }

    static void DoLoadingText(const std::string& var0) {
      if (SpriteRenderer.instance != nullptr && TextManager.instance.font != nullptr) {
         Core.getInstance().StartFrame();
         Core.getInstance().EndFrame();
         Core.getInstance().StartFrameUI();
         SpriteRenderer.instance.renderi(nullptr, 0, 0, Core.getInstance().getScreenWidth(), Core.getInstance().getScreenHeight(), 0.0F, 0.0F, 0.0F, 1.0F, nullptr);
         TextManager.instance.DrawStringCentre(Core.getInstance().getScreenWidth() / 2, Core.getInstance().getScreenHeight() / 2, var0, 1.0, 1.0, 1.0, 1.0);
         Core.getInstance().EndFrameUI();
      }
   }
}
} // namespace zombie
