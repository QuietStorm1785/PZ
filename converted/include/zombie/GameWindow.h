#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/FMODManager.h"
#include "fmod/fmod/FMODSoundBank.h"
#include "org/lwjgl/opengl/GL.h"
#include "org/lwjgl/opengl/GL11.h"
#include "org/lwjglx/LWJGLException.h"
#include "org/lwjglx/input/Controller.h"
#include "org/lwjglx/opengl/Display.h"
#include "org/lwjglx/opengl/DisplayMode.h"
#include "org/lwjglx/opengl/OpenGLException.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaManager.h"
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
#include "zombie/core/profiling/PerformanceProfileFrameProbe.h"
#include "zombie/core/profiling/PerformanceProfileProbe.h"
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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class GameWindow {
public:
 static const std::string GAME_TITLE = "Project Zomboid";
 static const FPSTracking s_fpsTracking = new FPSTracking();
 private static ThreadLocal<GameWindow.StringUTF> stringUTF = ThreadLocal.withInitial(GameWindow.StringUTF::new);
 static const Input GameInput = new Input();
 static bool DEBUG_SAVE = false;
 static bool OkToSaveOnExit = false;
 static std::string lastP = nullptr;
 static GameStateMachine states = new GameStateMachine();
 static bool bServerDisconnected;
 static bool bLoadedAsClient = false;
 static std::string kickReason;
 static bool DrawReloadingLua = false;
 public static JoypadManager.Joypad ActivatedJoyPad = nullptr;
 static std::string version = "RC3";
 public static boolean closeRequested;
 static float averageFPS = PerformanceSettings.getLockFPS();
 static bool doRenderEvent = false;
 static bool bLuaDebuggerKeyDown = false;
 static FileSystem fileSystem = new FileSystemImpl();
 static AssetManagers assetManagers = new AssetManagers(fileSystem);
 static bool bGameThreadExited = false;
 static Thread GameThread;
 public static ArrayList<GameWindow.TexturePack> texturePacks = std::make_unique<ArrayList<>>();
 public static FileSystem.TexturePackTextures texturePackTextures = new FileSystem.TexturePackTextures();

 static void initShared() {
 std::string string0 = ZomboidFileSystem.instance.getCacheDir() + File.separator;
 File file = new File(string0);
 if (!file.exists()) {
 file.mkdirs();
 }

 TexturePackPage.bIgnoreWorldItemTextures = true;
 uint8_t byte0 = 2;
 LoadTexturePack("UI", byte0);
 LoadTexturePack("UI2", byte0);
 LoadTexturePack("IconsMoveables", byte0);
 LoadTexturePack("RadioIcons", byte0);
 LoadTexturePack("ApComUI", byte0);
 LoadTexturePack("Mechanics", byte0);
 LoadTexturePack("WeatherFx", byte0);
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
 states.States.add(std::make_unique<TISLogoState>());
 }

 states.States.add(std::make_unique<TermsOfServiceState>());
 states.States.add(std::make_unique<MainScreenState>());
 if (!Core.bDebug) {
 states.LoopToState = 1;
 }

 GameInput.initControllers();
 if (Core.getInstance().isDefaultOptions() && SteamUtils.isSteamModeEnabled() && SteamUtils.isRunningOnSteamDeck()) {
 Core.getInstance().setOptionActiveController(0, true);
 }

 int int0 = GameInput.getControllerCount();
 DebugLog.Input.println("----------------------------------------------");
 DebugLog.Input.println("-- Information about controllers ");
 DebugLog.Input.println("----------------------------------------------");

 for (int int1 = 0; int1 < int0; int1++) {
 Controller controller = GameInput.getController(int1);
 if (controller != nullptr) {
 DebugLog.Input.println("----------------------------------------------");
 DebugLog.Input.println("-- Joypad: " + controller.getGamepadName());
 DebugLog.Input.println("----------------------------------------------");
 int int2 = controller.getAxisCount();
 if (int2 > 1) {
 DebugLog.Input.println("----------------------------------------------");
 DebugLog.Input.println("-- Axis definitions for controller " + int1);
 DebugLog.Input.println("----------------------------------------------");

 for (int int3 = 0; int3 < int2; int3++) {
 std::string string1 = controller.getAxisName(int3);
 DebugLog.Input.println("Axis: " + string1);
 }
 }

 int2 = controller.getButtonCount();
 if (int2 > 1) {
 DebugLog.Input.println("----------------------------------------------");
 DebugLog.Input.println("-- Button definitions for controller " + int1);
 DebugLog.Input.println("----------------------------------------------");

 for (int int4 = 0; int4 < int2; int4++) {
 std::string string2 = controller.getButtonName(int4);
 DebugLog.Input.println("Button: " + string2);
 }
 }
 }
 }
 }

 static void logic() {
 if (GameClient.bClient) {
 try {
 GameClient.instance.update();
 } catch (Exception exception) {
 ExceptionLogger.logException(exception);
 }
 }

 try {
 SinglePlayerServer.update();
 SinglePlayerClient.update();
 } catch (Throwable throwable) {
 ExceptionLogger.logException(throwable);
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
 if (JoypadManager.instance.isAPressed(-1) {
 for (int int0 = 0; int0 < JoypadManager.instance.JoypadList.size(); int0++) {
 JoypadManager.Joypad joypad = JoypadManager.instance.JoypadList.get(int0);
 if (joypad.isAPressed()) {
 if (ActivatedJoyPad == nullptr) {
 ActivatedJoyPad = joypad;
 }

 if (IsoPlayer.getInstance() != nullptr) {
 LuaEventManager.triggerEvent("OnJoypadActivate", joypad.getID());
 } else {
 LuaEventManager.triggerEvent("OnJoypadActivateUI", joypad.getID());
 }
 break;
 }
 }
 }

 SoundManager.instance.Update();
 bool boolean0 = true;
 if (GameTime.isGamePaused()) {
 boolean0 = false;
 }

 MapCollisionData.instance.updateGameState();
 Mouse.setCursorVisible(true);
 if (boolean0) {
 states.update();
 } else {
 IsoCamera.updateAll();
 if (IngameState.instance != nullptr && (states.current == IngameState.instance || states.States.contains(IngameState.instance) {
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
 GameWindow.s_performance.statesRender.invokeAndMeasure(states, GameStateMachine::render);
 }

 static void InitDisplay() {
 Display.setTitle("Project Zomboid");
 if (!Core.getInstance().loadOptions()) {
 int int0 = Runtime.getRuntime().availableProcessors();
 if (int0 == 1) {
 PerformanceSettings.LightingFrameSkip = 3;
 } else if (int0 == 2) {
 PerformanceSettings.LightingFrameSkip = 2;
 } else if (int0 <= 4) {
 PerformanceSettings.LightingFrameSkip = 1;
 }

 Core.setFullScreen(true);
 Display.setFullscreen(true);
 Display.setResizable(false);
 DisplayMode displayMode = Display.getDesktopDisplayMode();
 Core.getInstance().init(displayMode.getWidth(), displayMode.getHeight());
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
 int int1 = GL11.glGetInteger(34812);
 DebugLog.log("ATI: available texture memory is " + int1 / 1024 + " MB");
 }

 if (GL.getCapabilities().GL_NVX_gpu_memory_info) {
 int int2 = GL11.glGetInteger(36937);
 DebugLog.log("NVIDIA: current available GPU memory is " + int2 / 1024 + " MB");
 int2 = GL11.glGetInteger(36935);
 DebugLog.log("NVIDIA: dedicated available GPU memory is " + int2 / 1024 + " MB");
 int2 = GL11.glGetInteger(36936);
 DebugLog.log("NVIDIA: total available GPU memory is " + int2 / 1024 + " MB");
 }

 SpriteRenderer.instance.create();
 }

 static void InitGameThread() {
 Thread.setDefaultUncaughtExceptionHandler(GameWindow::uncaughtGlobalException);
 Thread thread = new Thread(ThreadGroups.Main, GameWindow::mainThread, "MainThread");
 thread.setUncaughtExceptionHandler(GameWindow::uncaughtExceptionMainThread);
 GameThread = thread;
 thread.start();
 }

 static void uncaughtExceptionMainThread(Thread thread, std::exception throwable) {
 if (throwable instanceof ThreadDeath) {
 DebugLog.General.println("Game Thread exited: ", thread.getName());
 } else {
 try {
 uncaughtException(thread, throwable);
 } finally {
 onGameThreadExited();
 }
 }
 }

 static void uncaughtGlobalException(Thread thread, std::exception throwable) {
 if (throwable instanceof ThreadDeath) {
 DebugLog.General.println("External Thread exited: ", thread.getName());
 } else {
 uncaughtException(thread, throwable);
 }
 }

 static void uncaughtException(Thread thread, std::exception e) {
 if (e instanceof ThreadDeath) {
 DebugLog.General.println("Internal Thread exited: ", thread.getName());
 } else {
 std::string string = String.format("Unhandled %s thrown by thread %s.", e.getClass().getName(), thread.getName());
 DebugLog.General.error(string);
 ExceptionLogger.logException(e, string);
 }
 }

 static void mainThread() {
 mainThreadInit();
 enter();
 RenderThread.setWaitForRenderState(true);
 run_ez();
 }

 static void mainThreadInit() {
 std::string string0 = System.getProperty("debug");
 std::string string1 = System.getProperty("nosave");
 if (string1 != nullptr) {
 Core.getInstance().setNoSave(true);
 }

 if (string0 != nullptr) {
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
 } catch (Exception exception0) {
 throw RuntimeException(exception0);
 }

 DebugFileWatcher.instance.init();
 std::string string2 = System.getProperty("server");
 std::string string3 = System.getProperty("client");
 std::string string4 = System.getProperty("nozombies");
 if (string4 != nullptr) {
 IsoWorld.NoZombies = true;
 }

 if (string2 != nullptr && string2 == "true")) {
 GameServer.bServer = true;
 }

 try {
 renameSaveFolders();
 init();
 } catch (Exception exception1) {
 throw RuntimeException(exception1);
 }
 }

 static void renameSaveFolders() {
 std::string string = ZomboidFileSystem.instance.getSaveDir();
 File file0 = new File(string);
 if (file0.exists() && file0.isDirectory()) {
 File file1 = new File(file0, "Fighter");
 File file2 = new File(file0, "Survivor");
 if (file1.exists() && file1.isDirectory() && file2.exists() && file2.isDirectory()) {
 DebugLog.log("RENAMING Saves/Survivor to Saves/Apocalypse");
 DebugLog.log("RENAMING Saves/Fighter to Saves/Survivor");
 file2.renameTo(new File(file0, "Apocalypse"));
 file1.renameTo(new File(file0, "Survivor"));
 File file3 = new File(ZomboidFileSystem.instance.getCacheDir() + File.separator + "latestSave.ini");
 if (file3.exists()) {
 file3.delete();
 }
 }
 }
 }

 static long readLong(DataInputStream __in__) {
 int int0 = __in__.read();
 int int1 = __in__.read();
 int int2 = __in__.read();
 int int3 = __in__.read();
 int int4 = __in__.read();
 int int5 = __in__.read();
 int int6 = __in__.read();
 int int7 = __in__.read();
 if ((int0 | int1 | int2 | int3 | int4 | int5 | int6 | int7) < 0) {
 throw std::make_unique<EOFException>();
 } else {
 return int0 + (int1 << 8) + (int2 << 16) + (int3 << 24) + (int4 << 32) + (int5 << 40) + (int6 << 48) + (int7 << 56);
 }
 }

 static int readInt(DataInputStream __in__) {
 int int0 = __in__.read();
 int int1 = __in__.read();
 int int2 = __in__.read();
 int int3 = __in__.read();
 if ((int0 | int1 | int2 | int3) < 0) {
 throw std::make_unique<EOFException>();
 } else {
 return int0 + (int1 << 8) + (int2 << 16) + (int3 << 24);
 }
 }

 static void run_ez() {
 long long0 = System.nanoTime();
 long long1 = 0L;

 while (!RenderThread.isCloseRequested() && !closeRequested) {
 long long2 = System.nanoTime();
 if (long2 < long0) {
 long0 = long2;
 } else {
 long long3 = long2 - long0;
 long0 = long2;
 if (PerformanceSettings.isUncappedFPS()) {
 frameStep();
 } else {
 long1 += long3;
 long long4 = PZMath.secondsToNanos / PerformanceSettings.getLockFPS();
 if (long1 >= long4) {
 frameStep();
 long1 %= long4;
 }
 }

 if (Core.bDebug && DebugOptions.instance.ThreadCrash_Enabled.getValue()) {
 DebugOptions.testThreadCrash(0);
 RenderThread.invokeOnRenderContext(() -> DebugOptions.testThreadCrash(1);
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
 int int0 = TextureID.bUseCompression ? 4 : 0;
 int0 |= 64;
 if (Core.TileScale == 1) {
 LoadTexturePack("Tiles1x", int0);
 LoadTexturePack("Overlays1x", int0);
 LoadTexturePack("JumboTrees1x", int0);
 LoadTexturePack("Tiles1x.floor", int0 & -5);
 }

 if (Core.TileScale == 2) {
 LoadTexturePack("Tiles2x", int0);
 LoadTexturePack("Overlays2x", int0);
 LoadTexturePack("JumboTrees2x", int0);
 LoadTexturePack("Tiles2x.floor", int0 & -5);
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
 GameWindow.s_performance.frameStep.start();
 s_fpsTracking.frameStep();
 GameWindow.s_performance.logic.invokeAndMeasure(GameWindow::logic);
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
 LuaManager.thread.bStep = true;
 LuaManager.thread.bStepInto = true;
 bLuaDebuggerKeyDown = true;
 if (GameClient.bClient && states.current == IngameState.instance) {
 GameClient.sendServerPing(-1L);
 }
 }
 } else {
 bLuaDebuggerKeyDown = false;
 }

 if (GameKeyboard.isKeyPressed(Core.getInstance().getKey("ToggleLuaConsole"))) {
 UIDebugConsole uIDebugConsole = UIManager.getDebugConsole();
 if (uIDebugConsole != nullptr) {
 uIDebugConsole.setVisible(!uIDebugConsole.isVisible());
 }
 }
 }
 } catch (OpenGLException openGLException) {
 RenderThread.logGLException(openGLException);
 } catch (Exception exception) {
 ExceptionLogger.logException(exception);
 } finally {
 GameWindow.s_performance.frameStep.end();
 }
 }

 static void exit() {
 DebugLog.log("EXITDEBUG: GameWindow.exit 1");
 if (GameClient.bClient) {
 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 IsoPlayer player = IsoPlayer.players[int0];
 if (player != nullptr) {
 ClientPlayerDB.getInstance().clientSendNetworkPlayerInt(player);
 }
 }

 WorldStreamer.instance.stop();
 GameClient.instance.doDisconnect("exit");
 VoiceManager.instance.DeinitVMClient();
 }

 if (OkToSaveOnExit) {
 try {
 WorldStreamer.instance.quit();
 } catch (Exception exception0) {
 exception0.printStackTrace();
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
 } catch (Throwable throwable) {
 throwable.printStackTrace();
 }

 try {
 if (IsoWorld.instance.CurrentCell != nullptr) {
 LuaEventManager.triggerEvent("OnPostSave");
 }
 } catch (Exception exception1) {
 exception1.printStackTrace();
 }

 try {
 if (IsoWorld.instance.CurrentCell != nullptr) {
 LuaEventManager.triggerEvent("OnPostSave");
 }
 } catch (Exception exception2) {
 exception2.printStackTrace();
 }

 try {
 LightingThread.instance.stop();
 MapCollisionData.instance.stop();
 ZombiePopulationManager.instance.stop();
 PolygonalMap2.instance.stop();
 ZombieSpawnRecorder.instance.quit();
 } catch (Exception exception3) {
 exception3.printStackTrace();
 }
 }

 DebugLog.log("EXITDEBUG: GameWindow.exit 2");
 if (GameClient.bClient) {
 WorldStreamer.instance.stop();
 GameClient.instance.doDisconnect("exit-saving");

 try {
 Thread.sleep(500L);
 } catch (InterruptedException interruptedException) {
 interruptedException.printStackTrace();
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

 for (int int0 = texturePacks.size() - 1; int0 >= 0; int0--) {
 GameWindow.TexturePack texturePack0 = texturePacks.get(int0);
 if (texturePack0.modID == nullptr) {
 texturePackTextures.putAll(texturePack0.textures);
 }
 }

 std::vector arrayList = ZomboidFileSystem.instance.getModIDs();

 for (int int1 = texturePacks.size() - 1; int1 >= 0; int1--) {
 GameWindow.TexturePack texturePack1 = texturePacks.get(int1);
 if (texturePack1.modID != nullptr && arrayList.contains(texturePack1.modID) {
 texturePackTextures.putAll(texturePack1.textures);
 }
 }

 Texture.onTexturePacksChanged();
 }

 static void LoadTexturePack(const std::string& pack, int flags) {
 LoadTexturePack(pack, flags, nullptr);
 }

 static void LoadTexturePack(const std::string& pack, int flags, const std::string& modID) {
 DebugLog.General.println("texturepack: loading " + pack);
 DoLoadingText(Translator.getText("UI_Loading_Texturepack", pack);
 std::string string = ZomboidFileSystem.instance.getString("media/texturepacks/" + pack + ".pack");
 GameWindow.TexturePack texturePack = new GameWindow.TexturePack();
 texturePack.packName = pack;
 texturePack.fileName = string;
 texturePack.modID = modID;
 fileSystem.mountTexturePack(pack, texturePack.textures, flags);
 texturePacks.add(texturePack);
 }

 static void LoadTexturePackDDS(const std::string& pack) {
 DebugLog.log("texturepack: loading " + pack);
 if (SpriteRenderer.instance != nullptr) {
 Core.getInstance().StartFrame();
 Core.getInstance().EndFrame(0);
 Core.getInstance().StartFrameUI();
 SpriteRenderer.instance
 .renderi(nullptr, 0, 0, Core.getInstance().getScreenWidth(), Core.getInstance().getScreenHeight(), 0.0F, 0.0F, 0.0F, 1.0F, nullptr);
 TextManager.instance
 .DrawStringCentre(
 Core.getInstance().getScreenWidth() / 2,
 Core.getInstance().getScreenHeight() / 2,
 Translator.getText("UI_Loading_Texturepack", pack),
 1.0,
 1.0,
 1.0,
 1.0
 );
 Core.getInstance().EndFrameUI();
 }

 FileInputStream fileInputStream = nullptr;

 try {
 fileInputStream = new FileInputStream(ZomboidFileSystem.instance.getString("media/texturepacks/" + pack + ".pack"));
 } catch (FileNotFoundException fileNotFoundException) {
 Logger.getLogger(GameLoadingState.class.getName()).log(Level.SEVERE, nullptr, fileNotFoundException);
 }

 try (BufferedInputStream bufferedInputStream = new BufferedInputStream(fileInputStream) {
 int int0 = TexturePackPage.readInt(bufferedInputStream);

 for (int int1 = 0; int1 < int0; int1++) {
 TexturePackPage texturePackPage = new TexturePackPage();
 if (int1 % 100 == 0 && SpriteRenderer.instance != nullptr) {
 Core.getInstance().StartFrame();
 Core.getInstance().EndFrame();
 Core.getInstance().StartFrameUI();
 TextManager.instance
 .DrawStringCentre(
 Core.getInstance().getScreenWidth() / 2,
 Core.getInstance().getScreenHeight() / 2,
 Translator.getText("UI_Loading_Texturepack", pack),
 1.0,
 1.0,
 1.0,
 1.0
 );
 Core.getInstance().EndFrameUI();
 RenderThread.invokeOnRenderContext(Display::update);
 }

 texturePackPage.loadFromPackFileDDS(bufferedInputStream);
 }

 DebugLog.log("texturepack: finished loading " + pack);
 } catch (Exception exception) {
 DebugLog.log("media/texturepacks/" + pack + ".pack");
 exception.printStackTrace();
 }

 Texture.nullTextures.clear();
 }

 static void installRequiredLibrary(const std::string& string0, const std::string& string1) {
 if (new File(string0).exists()) {
 DebugLog.log("Attempting to install " + string1);
 DebugLog.log("Running " + string0 + ".");
 ProcessBuilder processBuilder = new ProcessBuilder(string0, "/quiet", "/norestart");

 try {
 Process process = processBuilder.start();
 int int0 = process.waitFor();
 DebugLog.log("Process exited with code " + int0);
 return;
 } catch (InterruptedException | IOException iOException) {
 iOException.printStackTrace();
 }
 }

 DebugLog.log("Please install " + string1);
 }

 static void checkRequiredLibraries() {
 if (System.getProperty("os.name").startsWith("Win")) {
 std::string string0;
 std::string string1;
 std::string string2;
 std::string string3;
 if (System.getProperty("sun.arch.data.model") == "64")) {
 string0 = "Lighting64";
 string1 = "_CommonRedist\\vcredist\\2010\\vcredist_x64.exe";
 string2 = "_CommonRedist\\vcredist\\2012\\vcredist_x64.exe";
 string3 = "_CommonRedist\\vcredist\\2013\\vcredist_x64.exe";
 } else {
 string0 = "Lighting32";
 string1 = "_CommonRedist\\vcredist\\2010\\vcredist_x86.exe";
 string2 = "_CommonRedist\\vcredist\\2012\\vcredist_x86.exe";
 string3 = "_CommonRedist\\vcredist\\2013\\vcredist_x86.exe";
 }

 if ("1" == System.getProperty("zomboid.debuglibs.lighting"))) {
 DebugLog.log("***** Loading debug version of Lighting");
 string0 = string0 + "d";
 }

 try {
 System.loadLibrary(string0);
 } catch (UnsatisfiedLinkError unsatisfiedLinkError) {
 DebugLog.log("Error loading " + string0 + ".dll. Your system may be missing a required DLL.");
 installRequiredLibrary(string1, "the Microsoft Visual C++ 2010 Redistributable.");
 installRequiredLibrary(string2, "the Microsoft Visual C++ 2012 Redistributable.");
 installRequiredLibrary(string3, "the Microsoft Visual C++ 2013 Redistributable.");
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
 int int0 = Runtime.getRuntime().availableProcessors();
 std::string string = ZomboidFileSystem.instance.getCacheDir() + File.separator;
 File file = new File(string);
 if (!file.exists()) {
 file.mkdirs();
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
 LuaManager.init();
 CustomPerks.instance.initLua();
 CustomSandboxOptions.instance.init();
 CustomSandboxOptions.instance.initInstance(SandboxOptions.instance);
 LuaManager.LoadDirBase();
 ZomboidGlobals.Load();
 LuaEventManager.triggerEvent("OnLoadSoundBanks");
 }

 static void initFonts() {
 TextManager.instance.Init();

 while (TextManager.instance.font.empty()) {
 fileSystem.updateAsyncTransactions();

 try {
 Thread.sleep(10L);
 } catch (InterruptedException interruptedException) {
 }
 }
 }

 static void save(bool bDoChars) {
 if (!Core.getInstance().isNoSave()) {
 if (IsoWorld.instance.CurrentCell != nullptr
 && !"LastStand" == Core.getInstance().getGameMode())
 && !"Tutorial" == Core.getInstance().getGameMode())) {
 File file = ZomboidFileSystem.instance.getFileInCurrentSave("map_ver.bin");

 try (
 FileOutputStream fileOutputStream0 = new FileOutputStream(file);
 DataOutputStream dataOutputStream0 = new DataOutputStream(fileOutputStream0);
 ) {
 dataOutputStream0.writeInt(195);
 WriteString(dataOutputStream0, Core.GameMap);
 WriteString(dataOutputStream0, IsoWorld.instance.getDifficulty());
 }

 file = ZomboidFileSystem.instance.getFileInCurrentSave("map_sand.bin");

 try (
 FileOutputStream fileOutputStream1 = new FileOutputStream(file);
 BufferedOutputStream bufferedOutputStream = new BufferedOutputStream(fileOutputStream1);
 ) {
 SliceY.SliceBuffer.clear();
 SandboxOptions.instance.save(SliceY.SliceBuffer);
 bufferedOutputStream.write(SliceY.SliceBuffer.array(), 0, SliceY.SliceBuffer.position());
 }

 LuaEventManager.triggerEvent("OnSave");

 try {
 try {
 try {
 if (Thread.currentThread() == GameThread) {
 SavefileThumbnail.create();
 }
 } catch (Exception exception0) {
 ExceptionLogger.logException(exception0);
 }

 file = ZomboidFileSystem.instance.getFileInCurrentSave("map.bin");

 try (FileOutputStream fileOutputStream2 = new FileOutputStream(file) {
 DataOutputStream dataOutputStream1 = new DataOutputStream(fileOutputStream2);
 IsoWorld.instance.CurrentCell.save(dataOutputStream1, bDoChars);
 } catch (Exception exception1) {
 ExceptionLogger.logException(exception1);
 }

 try {
 MapCollisionData.instance.save();
 if (!bLoadedAsClient) {
 SGlobalObjects.save();
 }
 } catch (Exception exception2) {
 ExceptionLogger.logException(exception2);
 }

 ZomboidRadio.getInstance().Save();
 GlobalModData.instance.save();
 MapItem.SaveWorldMap();
 WorldMapVisited.SaveAll();
 } catch (IOException iOException) {
 throw RuntimeException(iOException);
 }
 } catch (RuntimeException runtimeException) {
 std::exception throwable2 = runtimeException.getCause();
 if (throwable2 instanceof IOException) {
 throw (IOException)throwable2;
 } else {
 throw runtimeException;
 }
 }
 }
 }
 }

 static std::string getCoopServerHome() {
 File file = new File(ZomboidFileSystem.instance.getCacheDir());
 return file.getParent();
 }

 static void WriteString(ByteBuffer output, const std::string& str) {
 WriteStringUTF(output, str);
 }

 static void WriteStringUTF(ByteBuffer output, const std::string& str) {
 stringUTF.get().save(output, str);
 }

 static void WriteString(DataOutputStream output, const std::string& str) {
 if (str == nullptr) {
 output.writeInt(0);
 } else {
 output.writeInt(str.length());
 if (str != nullptr && str.length() >= 0) {
 output.writeChars(str);
 }
 }
 }

 static std::string ReadStringUTF(ByteBuffer input) {
 return stringUTF.get().load(input);
 }

 static std::string ReadString(ByteBuffer input) {
 return ReadStringUTF();
 }

 static std::string ReadString(DataInputStream input) {
 int int0 = input.readInt();
 if (int0 == 0) {
 return "";
 } else if (int0 > 65536) {
 throw RuntimeException("GameWindow.ReadString: string is too long, corrupted save?");
 } else {
 StringBuilder stringBuilder = new StringBuilder(int0);

 for (int int1 = 0; int1 < int0; int1++) {
 stringBuilder.append(input.readChar());
 }

 return stringBuilder.toString();
 }
 }

 static void doRenderEvent(bool b) {
 doRenderEvent = b;
 }

 static void DoLoadingText(const std::string& text) {
 if (SpriteRenderer.instance != nullptr && TextManager.instance.font != nullptr) {
 Core.getInstance().StartFrame();
 Core.getInstance().EndFrame();
 Core.getInstance().StartFrameUI();
 SpriteRenderer.instance
 .renderi(nullptr, 0, 0, Core.getInstance().getScreenWidth(), Core.getInstance().getScreenHeight(), 0.0F, 0.0F, 0.0F, 1.0F, nullptr);
 TextManager.instance.DrawStringCentre(Core.getInstance().getScreenWidth() / 2, Core.getInstance().getScreenHeight() / 2, text, 1.0, 1.0, 1.0, 1.0);
 Core.getInstance().EndFrameUI();
 }
 }

 public static class OSValidator {
 static std::string OS = System.getProperty("os.name").toLowerCase();

 static bool isWindows() {
 return OS.indexOf("win") >= 0;
 }

 static bool isMac() {
 return OS.indexOf("mac") >= 0;
 }

 static bool isUnix() {
 return OS.indexOf("nix") >= 0 || OS.indexOf("nux") >= 0 || OS.indexOf("aix") > 0;
 }

 static bool isSolaris() {
 return OS.indexOf("sunos") >= 0;
 }
 }

 private static class StringUTF {
 private char[] chars;
 ByteBuffer byteBuffer;
 CharBuffer charBuffer;
 CharsetEncoder ce;
 CharsetDecoder cd;

 int encode(const std::string& string) {
 if (this->chars == nullptr || this->chars.length < string.length()) {
 int int0 = (string.length() + 128 - 1) / 128 * 128;
 this->chars = new char[int0];
 this->charBuffer = CharBuffer.wrap(this->chars);
 }

 string.getChars(0, string.length(), this->chars, 0);
 this->charBuffer.limit(string.length());
 this->charBuffer.position(0);
 if (this->ce == nullptr) {
 this->ce = StandardCharsets.UTF_8.newEncoder().onMalformedInput(CodingErrorAction.REPLACE).onUnmappableCharacter(CodingErrorAction.REPLACE);
 }

 this->ce.reset();
 int int1 = (int)((double)string.length() * this->ce.maxBytesPerChar());
 int1 = (int1 + 128 - 1) / 128 * 128;
 if (this->byteBuffer == nullptr || this->byteBuffer.capacity() < int1) {
 this->byteBuffer = ByteBuffer.allocate(int1);
 }

 this->byteBuffer.clear();
 CoderResult coderResult = this->ce.encode(this->charBuffer, this->byteBuffer, true);
 return this->byteBuffer.position();
 }

 std::string decode(int int1) {
 if (this->cd == nullptr) {
 this->cd = StandardCharsets.UTF_8.newDecoder().onMalformedInput(CodingErrorAction.REPLACE).onUnmappableCharacter(CodingErrorAction.REPLACE);
 }

 this->cd.reset();
 int int0 = (int)((double)int1 * this->cd.maxCharsPerByte());
 if (this->chars == nullptr || this->chars.length < int0) {
 int int2 = (int0 + 128 - 1) / 128 * 128;
 this->chars = new char[int2];
 this->charBuffer = CharBuffer.wrap(this->chars);
 }

 this->charBuffer.clear();
 CoderResult coderResult = this->cd.decode(this->byteBuffer, this->charBuffer, true);
 return new String(this->chars, 0, this->charBuffer.position());
 }

 void save(ByteBuffer byteBufferx, const std::string& string) {
 if (string != nullptr && !string.empty()) {
 int int0 = this->encode(string);
 byteBufferx.putShort((short)int0);
 this->byteBuffer.flip();
 byteBufferx.put(this->byteBuffer);
 } else {
 byteBufferx.putShort((short)0);
 }
 }

 std::string load(ByteBuffer byteBufferx) {
 short short0 = byteBufferx.getShort();
 if (short0 <= 0) {
 return "";
 } else {
 int int0 = (short0 + 128 - 1) / 128 * 128;
 if (this->byteBuffer == nullptr || this->byteBuffer.capacity() < int0) {
 this->byteBuffer = ByteBuffer.allocate(int0);
 }

 this->byteBuffer.clear();
 if (byteBufferx.remaining() < short0) {
 DebugLog.General
 .error("GameWindow.StringUTF.load> numBytes:" + short0 + " is higher than the remaining bytes in the buffer:" + byteBufferx.remaining());
 }

 int int1 = byteBufferx.limit();
 byteBufferx.limit(byteBufferx.position() + short0);
 this->byteBuffer.put(byteBufferx);
 byteBufferx.limit(int1);
 this->byteBuffer.flip();
 return this->decode(short0);
 }
 }
 }

 private static class TexturePack {
 std::string packName;
 std::string fileName;
 std::string modID;
 FileSystem.TexturePackTextures textures = new FileSystem.TexturePackTextures();
 }

 private static class s_performance {
 static const PerformanceProfileFrameProbe frameStep = new PerformanceProfileFrameProbe("GameWindow.frameStep");
 static const PerformanceProfileProbe statesRender = new PerformanceProfileProbe("GameWindow.states.render");
 static const PerformanceProfileProbe logic = new PerformanceProfileProbe("GameWindow.logic");
 }
}
} // namespace zombie
