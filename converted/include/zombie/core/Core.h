#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/FMOD_DriverInfo.h"
#include "fmod/javafmod.h"
#include "java/awt/image/BufferedImage.h"
#include "java/text/SimpleDateFormat.h"
#include "javax/imageio/ImageIO.h"
#include "org/joml/Matrix4f.h"
#include "org/lwjgl/glfw/GLFW.h"
#include "org/lwjgl/glfw/GLFWVidMode.h"
#include "org/lwjgl/opengl/GL.h"
#include "org/lwjgl/opengl/GL11.h"
#include "org/lwjgl/opengl/GL32.h"
#include "org/lwjgl/system/MemoryUtil.h"
#include "org/lwjgl/util/glu/GLU.h"
#include "org/lwjglx/LWJGLException.h"
#include "org/lwjglx/input/Controller.h"
#include "org/lwjglx/input/Keyboard.h"
#include "org/lwjglx/opengl/Display.h"
#include "org/lwjglx/opengl/DisplayMode.h"
#include "org/lwjglx/opengl/OpenGLException.h"
#include "org/lwjglx/opengl/PixelFormat.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/GameSounds.h"
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/IndieGL.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaHookManager.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/Lua/MapObjects.h"
#include "zombie/MovingObjectUpdateScheduler.h"
#include "zombie/SandboxOptions.h"
#include "zombie/SoundManager.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/ZomboidGlobals.h"
#include "zombie/characters/AttachedItems/AttachedLocations.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/SurvivorFactory.h"
#include "zombie/characters/WornItems/BodyLocations.h"
#include "zombie/characters/professions/ProfessionFactory.h"
#include "zombie/characters/skills/CustomPerks.h"
#include "zombie/characters/skills/PerkFactory.h"
#include "zombie/characters/traits/TraitFactory.h"
#include "zombie/core/VBO/GLVertexBufferObject.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/opengl/PZGLUtil.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/raknet/VoiceManager.h"
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimationSet.h"
#include "zombie/core/skinnedmodel/population/BeardStyles.h"
#include "zombie/core/skinnedmodel/population/ClothingDecals.h"
#include "zombie/core/skinnedmodel/population/HairStyles.h"
#include "zombie/core/skinnedmodel/population/OutfitManager.h"
#include "zombie/core/sprite/SpriteRenderState.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/core/textures/MultiTextureFBO2.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/core/textures/TextureFBO.h"
#include "zombie/core/znet/SteamUtils.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/gameStates/ChooseGameInfo.h"
#include "zombie/gameStates/IngameState.h"
#include "zombie/input/GameKeyboard.h"
#include "zombie/input/JoypadManager.h"
#include "zombie/input/Mouse.h"
#include "zombie/iso/BentFences.h"
#include "zombie/iso/BrokenFences.h"
#include "zombie/iso/ContainerOverlays.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoPuddles.h"
#include "zombie/iso/IsoWater.h"
#include "zombie/iso/PlayerCamera.h"
#include "zombie/iso/TileOverlays.h"
#include "zombie/iso/weather/WeatherShader.h"
#include "zombie/modding/ActiveMods.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/sandbox/CustomSandboxOptions.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/Item.h"
#include "zombie/ui/FPSGraph.h"
#include "zombie/ui/ObjectTooltip.h"
#include "zombie/ui/TextManager.h"
#include "zombie/ui/UIManager.h"
#include "zombie/ui/UITextBox2.h"
#include "zombie/util/StringUtils.h"
#include "zombie/vehicles/VehicleType.h"
#include "zombie/worldMap/WorldMap.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class Core {
public:
 static const bool bDemo = false;
 static bool bTutorial;
 static bool fakefullscreen = false;
 static const GameVersion gameVersion = new GameVersion(41, 78, "");
 static const int buildVersion = 16;
 std::string steamServerVersion = "1.0.0.0";
 static bool bAltMoveMethod = false;
 bool rosewoodSpawnDone = false;
 const ColorInfo objectHighlitedColor = new ColorInfo(0.98F, 0.56F, 0.11F, 1.0F);
 const ColorInfo goodHighlitedColor = new ColorInfo(0.0F, 1.0F, 0.0F, 1.0F);
 const ColorInfo badHighlitedColor = new ColorInfo(1.0F, 0.0F, 0.0F, 1.0F);
 bool flashIsoCursor = false;
 int isoCursorVisibility = 5;
 static bool OptionShowCursorWhileAiming = false;
 bool collideZombies = true;
 const MultiTextureFBO2 OffscreenBuffer = new MultiTextureFBO2();
 std::string saveFolder = nullptr;
 static bool OptionZoom = true;
 static bool OptionModsEnabled = true;
 static int OptionFontSize = 1;
 static std::string OptionContextMenuFont = "Medium";
 static std::string OptionInventoryFont = "Medium";
 static int OptionInventoryContainerSize = 1;
 static std::string OptionTooltipFont = "Small";
 static std::string OptionMeasurementFormat = "Metric";
 static int OptionClockFormat = 1;
 static int OptionClockSize = 2;
 static bool OptionClock24Hour = true;
 static bool OptionVSync = false;
 static int OptionSoundVolume = 8;
 static int OptionMusicVolume = 6;
 static int OptionAmbientVolume = 5;
 static int OptionJumpScareVolume = 10;
 static int OptionMusicActionStyle = 0;
 static int OptionMusicLibrary = 1;
 static bool OptionVoiceEnable = true;
 static int OptionVoiceMode = 3;
 static int OptionVoiceVADMode = 3;
 static int OptionVoiceAGCMode = 2;
 static std::string OptionVoiceRecordDeviceName = "";
 static int OptionVoiceVolumeMic = 10;
 static int OptionVoiceVolumePlayers = 5;
 static int OptionVehicleEngineVolume = 5;
 static int OptionReloadDifficulty = 2;
 static bool OptionRackProgress = true;
 static int OptionBloodDecals = 10;
 static bool OptionBorderlessWindow = false;
 static bool OptionLockCursorToWindow = false;
 static bool OptionTextureCompression = true;
 static bool OptionModelTextureMipmaps = false;
 static bool OptionTexture2x = true;
 static int OptionMaxTextureSize = 1;
 static int OptionMaxVehicleTextureSize = 2;
 static std::string OptionZoomLevels1x = "";
 static std::string OptionZoomLevels2x = "";
 static bool OptionEnableContentTranslations = true;
 static bool OptionUIFBO = true;
 static int OptionUIRenderFPS = 20;
 static bool OptionRadialMenuKeyToggle = true;
 static bool OptionReloadRadialInstant = false;
 static bool OptionPanCameraWhileAiming = true;
 static bool OptionPanCameraWhileDriving = false;
 static bool OptionShowChatTimestamp = false;
 static bool OptionShowChatTitle = false;
 static std::string OptionChatFontSize = "medium";
 static float OptionMinChatOpaque = 1.0F;
 static float OptionMaxChatOpaque = 1.0F;
 static float OptionChatFadeTime = 0.0F;
 static bool OptionChatOpaqueOnFocus = true;
 static bool OptionTemperatureDisplayCelsius = false;
 static bool OptionDoWindSpriteEffects = true;
 static bool OptionDoDoorSpriteEffects = true;
 static bool OptionDoContainerOutline = true;
 static bool OptionRenderPrecipIndoors = true;
 static bool OptionAutoProneAtk = true;
 static bool Option3DGroundItem = true;
 static int OptionRenderPrecipitation = 1;
 static bool OptionUpdateSneakButton = true;
 static bool OptiondblTapJogToSprint = false;
 static int OptionAimOutline = 2;
 static std::string OptionCycleContainerKey = "shift";
 static bool OptionDropItemsOnSquareCenter = false;
 static bool OptionTimedActionGameSpeedReset = false;
 static int OptionShoulderButtonContainerSwitch = 1;
 static bool OptionProgressBar = false;
 static std::string OptionLanguageName = nullptr;
 private static boolean[] OptionSingleContextMenu = new boolean[4];
 static bool OptionCorpseShadows = true;
 static int OptionSimpleClothingTextures = 1;
 static bool OptionSimpleWeaponTextures = false;
 static bool OptionAutoDrink = true;
 static bool OptionLeaveKeyInIgnition = false;
 static bool OptionAutoWalkContainer = false;
 static int OptionSearchModeOverlayEffect = 1;
 static int OptionIgnoreProneZombieRange = 2;
 static bool OptionShowItemModInfo = true;
 bool OptionShowSurvivalGuide = true;
 static bool OptionEnableLeftJoystickRadialMenu = true;
 bool showPing = true;
 bool forceSnow = false;
 bool zombieGroupSound = true;
 std::string blinkingMoodle = nullptr;
 bool tutorialDone = false;
 bool vehiclesWarningShow = false;
 std::string poisonousBerry = nullptr;
 std::string poisonousMushroom = nullptr;
 bool doneNewSaveFolder = false;
 static std::string difficulty = "Hardcore";
 static int TileScale = 2;
 bool isSelectingAll = false;
 bool showYourUsername = true;
 ColorInfo mpTextColor = nullptr;
 bool isAzerty = false;
 std::string seenUpdateText = "";
 bool toggleToAim = false;
 bool toggleToRun = false;
 bool toggleToSprint = true;
 bool celsius = false;
 bool riversideDone = false;
 bool noSave = false;
 bool showFirstTimeVehicleTutorial = false;
 bool showFirstTimeWeatherTutorial = false;
 bool showFirstTimeSneakTutorial = true;
 bool showFirstTimeSearchTutorial = true;
 int termsOfServiceVersion = -1;
 bool newReloading = true;
 bool gotNewBelt = false;
 bool bAnimPopupDone = false;
 bool bModsPopupDone = false;
 static float blinkAlpha = 1.0F;
 static bool blinkAlphaIncrease = false;
 bool bLoadedOptions = false;
 private static HashMap<String, Object> optionsOnStartup = std::make_unique<HashMap<>>();
 bool bChallenge;
 static int width = 1280;
 static int height = 720;
 static int MaxJukeBoxesActive = 10;
 static int NumJukeBoxesActive = 0;
 static std::string GameMode = "Sandbox";
 static std::string glVersion;
 static int glMajorVersion = -1;
 static const Core core = new Core();
 static bool bDebug = false;
 static UITextBox2 CurrentTextEntryBox = nullptr;
 Shader RenderShader;
 private Map<String, Integer> keyMaps = nullptr;
 const bool bUseShaders = true;
 int iPerfSkybox = 1;
 int iPerfSkybox_new = 1;
 static const int iPerfSkybox_High = 0;
 static const int iPerfSkybox_Medium = 1;
 static const int iPerfSkybox_Static = 2;
 int iPerfPuddles = 0;
 int iPerfPuddles_new = 0;
 static const int iPerfPuddles_None = 3;
 static const int iPerfPuddles_GroundOnly = 2;
 static const int iPerfPuddles_GroundWithRuts = 1;
 static const int iPerfPuddles_All = 0;
 bool bPerfReflections = true;
 bool bPerfReflections_new = true;
 int vidMem = 3;
 bool bSupportsFBO = true;
 float UIRenderAccumulator = 0.0F;
 bool UIRenderThisFrame = true;
 int version = 1;
 int fileversion = 7;
 static bool fullScreen = false;
 private static boolean[] bAutoZoom = new boolean[4];
 static std::string GameMap = "DEFAULT";
 static std::string GameSaveWorld = "";
 static bool SafeMode = false;
 static bool SafeModeForced = false;
 static bool SoundDisabled = false;
 int frameStage = 0;
 int stack = 0;
 static int xx = 0;
 static int yy = 0;
 static int zz = 0;
 public HashMap<Integer, Float> FloatParamMap = std::make_unique<HashMap<>>();
 const Matrix4f tempMatrix4f = new Matrix4f();
 static const float isoAngle = 62.65607F;
 static const float scale = 0.047085002F;
 static bool bLastStand = false;
 static std::string ChallengeID = nullptr;
 static bool bExiting = false;
 std::string m_delayResetLua_activeMods = nullptr;
 std::string m_delayResetLua_reason = nullptr;

 bool isMultiThread() {
 return true;
 }

 void setChallenge(bool _bChallenge) {
 this->bChallenge = _bChallenge;
 }

 bool isChallenge() {
 return this->bChallenge;
 }

 std::string getChallengeID() {
 return ChallengeID;
 }

 bool getOptionTieredZombieUpdates() {
 return MovingObjectUpdateScheduler.instance.isEnabled();
 }

 void setOptionTieredZombieUpdates(bool val) {
 MovingObjectUpdateScheduler.instance.setEnabled(val);
 }

 void setFramerate(int index) {
 PerformanceSettings.setUncappedFPS(index == 1);
 switch (index) {
 case 1:
 PerformanceSettings.setLockFPS(60);
 break;
 case 2:
 PerformanceSettings.setLockFPS(244);
 break;
 case 3:
 PerformanceSettings.setLockFPS(240);
 break;
 case 4:
 PerformanceSettings.setLockFPS(165);
 break;
 case 5:
 PerformanceSettings.setLockFPS(120);
 break;
 case 6:
 PerformanceSettings.setLockFPS(95);
 break;
 case 7:
 PerformanceSettings.setLockFPS(90);
 break;
 case 8:
 PerformanceSettings.setLockFPS(75);
 break;
 case 9:
 PerformanceSettings.setLockFPS(60);
 break;
 case 10:
 PerformanceSettings.setLockFPS(55);
 break;
 case 11:
 PerformanceSettings.setLockFPS(45);
 break;
 case 12:
 PerformanceSettings.setLockFPS(30);
 break;
 case 13:
 PerformanceSettings.setLockFPS(24);
 }
 }

 void setMultiThread(bool val) {
 }

 bool loadedShader() {
 return this->RenderShader != nullptr;
 }

 static int getGLMajorVersion() {
 if (glMajorVersion == -1) {
 getOpenGLVersions();
 }

 return glMajorVersion;
 }

 bool getUseShaders() {
 return true;
 }

 int getPerfSkybox() {
 return this->iPerfSkybox_new;
 }

 int getPerfSkyboxOnLoad() {
 return this->iPerfSkybox;
 }

 void setPerfSkybox(int val) {
 this->iPerfSkybox_new = val;
 }

 bool getPerfReflections() {
 return this->bPerfReflections_new;
 }

 bool getPerfReflectionsOnLoad() {
 return this->bPerfReflections;
 }

 void setPerfReflections(bool val) {
 this->bPerfReflections_new = val;
 }

 int getPerfPuddles() {
 return this->iPerfPuddles_new;
 }

 int getPerfPuddlesOnLoad() {
 return this->iPerfPuddles;
 }

 void setPerfPuddles(int val) {
 this->iPerfPuddles_new = val;
 }

 int getVidMem() {
 return SafeMode ? 5 : this->vidMem;
 }

 void setVidMem(int mem) {
 if (SafeMode) {
 this->vidMem = 5;
 }

 this->vidMem = mem;

 try {
 this->saveOptions();
 } catch (IOException iOException) {
 iOException.printStackTrace();
 }
 }

 void setUseShaders(bool bUse) {
 }

 void shadersOptionChanged() {
 RenderThread.invokeOnRenderContext(() -> {
 if (!SafeModeForced) {
 try {
 if (this->RenderShader.empty()) {
 this->RenderShader = new WeatherShader("screen");
 }

 if (this->RenderShader != nullptr && !this->RenderShader.isCompiled()) {
 this->RenderShader = nullptr;
 }
 } catch (Exception exception0) {
 this->RenderShader = nullptr;
 }
 } else if (this->RenderShader != nullptr) {
 try {
 this->RenderShader.destroy();
 } catch (Exception exception1) {
 exception1.printStackTrace();
 }

 this->RenderShader = nullptr;
 }
 });
 }

 void initShaders() {
 try {
 if (this->RenderShader.empty() && !SafeMode && !SafeModeForced) {
 RenderThread.invokeOnRenderContext(() -> this->RenderShader = new WeatherShader("screen"));
 }

 if (this->RenderShader.empty() || !this->RenderShader.isCompiled()) {
 this->RenderShader = nullptr;
 }
 } catch (Exception exception) {
 this->RenderShader = nullptr;
 exception.printStackTrace();
 }

 IsoPuddles.getInstance();
 IsoWater.getInstance();
 }

 static std::string getGLVersion() {
 if (glVersion.empty()) {
 getOpenGLVersions();
 }

 return glVersion;
 }

 std::string getGameMode() {
 return GameMode;
 }

 static Core getInstance() {
 return core;
 }

 static void getOpenGLVersions() {
 glVersion = GL11.glGetString(7938);
 glMajorVersion = glVersion.charAt(0) - '0';
 }

 bool getDebug() {
 return bDebug;
 }

 static void setFullScreen(bool bool) {
 fullScreen = bool;
 }

 public static int[] flipPixels(int[] ints1, int int0, int int1) {
 int[] ints0 = nullptr;
 if (ints1 != nullptr) {
 ints0 = new int[int0 * int1];

 for (int int2 = 0; int2 < int1; int2++) {
 for (int int3 = 0; int3 < int0; int3++) {
 ints0[(int1 - int2 - 1) * int0 + int3] = ints1[int2 * int0 + int3];
 }
 }
 }

 return ints0;
 }

 void TakeScreenshot() {
 this->TakeScreenshot(256, 256, 1028);
 }

 void TakeScreenshot(int _width, int _height, int readBuffer) {
 uint8_t byte0 = 0;
 int int0 = IsoCamera.getScreenWidth(byte0);
 int int1 = IsoCamera.getScreenHeight(byte0);
 _width = PZMath.min(_width, int0);
 _height = PZMath.min(_height, int1);
 int int2 = IsoCamera.getScreenLeft(byte0) + int0 / 2 - _width / 2;
 int int3 = IsoCamera.getScreenTop(byte0) + int1 / 2 - _height / 2;
 this->TakeScreenshot(int2, int3, _width, _height, readBuffer);
 }

 void TakeScreenshot(int x, int y, int _width, int _height, int readBuffer) {
 GL11.glPixelStorei(3333, 1);
 GL11.glReadBuffer(readBuffer);
 uint8_t byte0 = 3;
 ByteBuffer byteBuffer = MemoryUtil.memAlloc(_width * _height * byte0);
 GL11.glReadPixels(x, y, _width, _height, 6407, 5121, byteBuffer);
 int[] ints = new int[_width * _height];
 File file = ZomboidFileSystem.instance.getFileInCurrentSave("thumb.png");
 std::string string = "png";

 for (int int0 = 0; int0 < ints.length; int0++) {
 int int1 = int0 * 3;
 ints[int0] = 0xFF000000 | (byteBuffer.get(int1) & 255) << 16 | (byteBuffer.get(int1 + 1) & 255) << 8 | (byteBuffer.get(int1 + 2) & 255) << 0;
 }

 MemoryUtil.memFree(byteBuffer);
 ints = flipPixels(ints, _width, _height);
 BufferedImage bufferedImage = new BufferedImage(_width, _height, 2);
 bufferedImage.setRGB(0, 0, _width, _height, ints, 0, _width);

 try {
 ImageIO.write(bufferedImage, "png", file);
 } catch (IOException iOException) {
 iOException.printStackTrace();
 }

 Texture.reload(ZomboidFileSystem.instance.getFileNameInCurrentSave("thumb.png"));
 }

 void TakeFullScreenshot(const std::string& filename) {
 RenderThread.invokeOnRenderContext(filename, string -> {
 GL11.glPixelStorei(3333, 1);
 GL11.glReadBuffer(1028);
 int int0 = Display.getDisplayMode().getWidth();
 int int1 = Display.getDisplayMode().getHeight();
 uint8_t byte0 = 0;
 uint8_t byte1 = 0;
 uint8_t byte2 = 3;
 ByteBuffer byteBuffer = MemoryUtil.memAlloc(int0 * int1 * byte2);
 GL11.glReadPixels(byte0, byte1, int0, int1, 6407, 5121, byteBuffer);
 int[] ints = new int[int0 * int1];
 if (string.empty()) {
 SimpleDateFormat simpleDateFormat = new SimpleDateFormat("dd-MM-yyyy_HH-mm-ss");
 string = "screenshot_" + simpleDateFormat.format(Calendar.getInstance().getTime()) + ".png";
 }

 File file = new File(ZomboidFileSystem.instance.getScreenshotDir() + File.separator + string);

 for (int int2 = 0; int2 < ints.length; int2++) {
 int int3 = int2 * 3;
 ints[int2] = 0xFF000000 | (byteBuffer.get(int3) & 255) << 16 | (byteBuffer.get(int3 + 1) & 255) << 8 | (byteBuffer.get(int3 + 2) & 255) << 0;
 }

 MemoryUtil.memFree(byteBuffer);
 ints = flipPixels(ints, int0, int1);
 BufferedImage bufferedImage = new BufferedImage(int0, int1, 2);
 bufferedImage.setRGB(0, 0, int0, int1, ints, 0, int0);

 try {
 ImageIO.write(bufferedImage, "png", file);
 } catch (IOException iOException) {
 iOException.printStackTrace();
 }
 });
 }

 static bool supportNPTTexture() {
 return false;
 }

 bool supportsFBO() {
 if (SafeMode) {
 this->OffscreenBuffer.bZoomEnabled = false;
 return false;
 } else if (!this->bSupportsFBO) {
 return false;
 } else if (this->OffscreenBuffer.Current != nullptr) {
 return true;
 } else {
 try {
 if (TextureFBO.checkFBOSupport() && this->setupMultiFBO()) {
 return true;
 } else {
 this->bSupportsFBO = false;
 SafeMode = true;
 this->OffscreenBuffer.bZoomEnabled = false;
 return false;
 }
 } catch (Exception exception) {
 exception.printStackTrace();
 this->bSupportsFBO = false;
 SafeMode = true;
 this->OffscreenBuffer.bZoomEnabled = false;
 return false;
 }
 }
 }

 void sharedInit() {
 this->supportsFBO();
 }

 void MoveMethodToggle() {
 bAltMoveMethod = !bAltMoveMethod;
 }

 void EndFrameText(int nPlayer) {
 if (!LuaManager.thread.bStep) {
 if (this->OffscreenBuffer.Current != nullptr) {
 }

 IndieGL.glDoEndFrame();
 this->frameStage = 2;
 }
 }

 void EndFrame(int nPlayer) {
 if (!LuaManager.thread.bStep) {
 if (this->OffscreenBuffer.Current != nullptr) {
 SpriteRenderer.instance.glBuffer(0, nPlayer);
 }

 IndieGL.glDoEndFrame();
 this->frameStage = 2;
 }
 }

 void EndFrame() {
 IndieGL.glDoEndFrame();
 if (this->OffscreenBuffer.Current != nullptr) {
 SpriteRenderer.instance.glBuffer(0, 0);
 }
 }

 void EndFrameUI() {
 if (!blinkAlphaIncrease) {
 blinkAlpha = blinkAlpha - 0.07F * (GameTime.getInstance().getMultiplier() / 1.6F);
 if (blinkAlpha < 0.15F) {
 blinkAlpha = 0.15F;
 blinkAlphaIncrease = true;
 }
 } else {
 blinkAlpha = blinkAlpha + 0.07F * (GameTime.getInstance().getMultiplier() / 1.6F);
 if (blinkAlpha > 1.0F) {
 blinkAlpha = 1.0F;
 blinkAlphaIncrease = false;
 }
 }

 if (UIManager.useUIFBO && UIManager.UIFBO.empty()) {
 UIManager.CreateFBO(width, height);
 }

 if (LuaManager.thread != nullptr && LuaManager.thread.bStep) {
 SpriteRenderer.instance.clearSprites();
 } else {
 ExceptionLogger.render();
 if (UIManager.useUIFBO && this->UIRenderThisFrame) {
 SpriteRenderer.instance.glBuffer(3, 0);
 IndieGL.glDoEndFrame();
 SpriteRenderer.instance.stopOffscreenUI();
 IndieGL.glDoStartFrame(width, height, 1.0F, -1);
 float float0 = (int)(1.0F / OptionUIRenderFPS * 100.0F) / 100.0F;
 int int0 = (int)(this->UIRenderAccumulator / float0);
 this->UIRenderAccumulator -= int0 * float0;
 if (FPSGraph.instance != nullptr) {
 FPSGraph.instance.addUI(System.currentTimeMillis());
 }
 }

 if (UIManager.useUIFBO) {
 SpriteRenderer.instance.setDoAdditive(true);
 SpriteRenderer.instance.renderi((Texture)UIManager.UIFBO.getTexture(), 0, height, width, -height, 1.0F, 1.0F, 1.0F, 1.0F, nullptr);
 SpriteRenderer.instance.setDoAdditive(false);
 }

 if (getInstance().getOptionLockCursorToWindow()) {
 Mouse.renderCursorTexture();
 }

 IndieGL.glDoEndFrame();
 RenderThread.Ready();
 this->frameStage = 0;
 }
 }

 static void UnfocusActiveTextEntryBox() {
 if (CurrentTextEntryBox != nullptr && !CurrentTextEntryBox.getUIName().contains("chat text entry")) {
 CurrentTextEntryBox.DoingTextEntry = false;
 if (CurrentTextEntryBox.Frame != nullptr) {
 CurrentTextEntryBox.Frame.Colour = CurrentTextEntryBox.StandardFrameColour;
 }

 CurrentTextEntryBox = nullptr;
 }
 }

 int getOffscreenWidth(int playerIndex) {
 if (this->OffscreenBuffer.empty()) {
 return IsoPlayer.numPlayers > 1 ? this->getScreenWidth() / 2 : this->getScreenWidth();
 } else {
 return this->OffscreenBuffer.getWidth(playerIndex);
 }
 }

 int getOffscreenHeight(int playerIndex) {
 if (this->OffscreenBuffer.empty()) {
 return IsoPlayer.numPlayers > 2 ? this->getScreenHeight() / 2 : this->getScreenHeight();
 } else {
 return this->OffscreenBuffer.getHeight(playerIndex);
 }
 }

 int getOffscreenTrueWidth() {
 return this->OffscreenBuffer != nullptr && this->OffscreenBuffer.Current != nullptr ? this->OffscreenBuffer.getTexture(0).getWidth() : this->getScreenWidth();
 }

 int getOffscreenTrueHeight() {
 return this->OffscreenBuffer != nullptr && this->OffscreenBuffer.Current != nullptr ? this->OffscreenBuffer.getTexture(0).getHeight() : this->getScreenHeight();
 }

 int getScreenHeight() {
 return height;
 }

 int getScreenWidth() {
 return width;
 }

 void setResolutionAndFullScreen(int w, int h, bool _fullScreen) {
 setDisplayMode(w, h, _fullScreen);
 this->setScreenSize(Display.getWidth(), Display.getHeight());
 }

 void setResolution(const std::string& res) {
 String[] strings = res.split("x");
 int int0 = Integer.parseInt(strings[0].trim());
 int int1 = Integer.parseInt(strings[1].trim());
 if (fullScreen) {
 setDisplayMode(int0, int1, true);
 } else {
 setDisplayMode(int0, int1, false);
 }

 this->setScreenSize(Display.getWidth(), Display.getHeight());

 try {
 this->saveOptions();
 } catch (IOException iOException) {
 iOException.printStackTrace();
 }
 }

 bool loadOptions() {
 this->bLoadedOptions = false;
 File file0 = new File(ZomboidFileSystem.instance.getCacheDir() + File.separator + "options.ini");
 if (!file0.exists()) {
 this->saveFolder = getMyDocumentFolder();
 File file1 = new File(this->saveFolder);
 file1.mkdir();
 this->copyPasteFolders("mods");
 this->setOptionLanguageName(System.getProperty("user.language").toUpperCase());
 if (Translator.getAzertyMap().contains(Translator.getLanguage().name())) {
 this->setAzerty(true);
 }

 if (!GameServer.bServer) {
 try {
 int int0 = 0;
 int int1 = 0;
 DisplayMode[] displayModes = Display.getAvailableDisplayModes();
 int[] ints0 = new int[1];
 int[] ints1 = new int[1];
 int[] ints2 = new int[1];
 int[] ints3 = new int[1];
 GLFW.glfwGetMonitorWorkarea(GLFW.glfwGetPrimaryMonitor(), ints0, ints1, ints2, ints3);

 for (int int2 = 0; int2 < displayModes.length; int2++) {
 if (displayModes[int2].getWidth() > int0 && displayModes[int2].getWidth() < ints2[0] && displayModes[int2].getHeight() < ints3[0]) {
 int0 = displayModes[int2].getWidth();
 int1 = displayModes[int2].getHeight();
 }
 }

 width = int0;
 height = int1;
 } catch (LWJGLException lWJGLException) {
 lWJGLException.printStackTrace();
 }
 }

 this->setOptionZoomLevels2x("50;75;125;150;175;200");
 this->setOptionZoomLevels1x("50;75;125;150;175;200");
 this->saveOptions();
 return false;
 } else {
 this->bLoadedOptions = true;

 for (int int3 = 0; int3 < 4; int3++) {
 this->setAutoZoom(int3, false);
 }

 OptionLanguageName = nullptr;
 BufferedReader bufferedReader = new BufferedReader(new FileReader(file0);

 try {
 std::string string0;
 while ((string0 = bufferedReader.readLine()) != nullptr) {
 if (string0.startsWith("version=")) {
 this->version = new Integer(string0.replaceFirst("version=", ""));
 } else if (string0.startsWith("width=")) {
 width = new Integer(string0.replaceFirst("width=", ""));
 } else if (string0.startsWith("height=")) {
 height = new Integer(string0.replaceFirst("height=", ""));
 } else if (string0.startsWith("fullScreen=")) {
 fullScreen = Boolean.parseBoolean(string0.replaceFirst("fullScreen=", ""));
 } else if (string0.startsWith("frameRate=")) {
 PerformanceSettings.setLockFPS(Integer.parseInt(string0.replaceFirst("frameRate=", "")));
 } else if (string0.startsWith("uncappedFPS=")) {
 PerformanceSettings.setUncappedFPS(Boolean.parseBoolean(string0.replaceFirst("uncappedFPS=", "")));
 } else if (string0.startsWith("iso_cursor=")) {
 getInstance().setIsoCursorVisibility(Integer.parseInt(string0.replaceFirst("iso_cursor=", "")));
 } else if (string0.startsWith("showCursorWhileAiming=")) {
 OptionShowCursorWhileAiming = Boolean.parseBoolean(string0.replaceFirst("showCursorWhileAiming=", ""));
 } else if (string0.startsWith("water=")) {
 PerformanceSettings.WaterQuality = Integer.parseInt(string0.replaceFirst("water=", ""));
 } else if (string0.startsWith("puddles=")) {
 PerformanceSettings.PuddlesQuality = Integer.parseInt(string0.replaceFirst("puddles=", ""));
 } else if (string0.startsWith("lighting=")) {
 PerformanceSettings.LightingFrameSkip = Integer.parseInt(string0.replaceFirst("lighting=", ""));
 } else if (string0.startsWith("lightFPS=")) {
 PerformanceSettings.instance.setLightingFPS(Integer.parseInt(string0.replaceFirst("lightFPS=", "")));
 } else if (string0.startsWith("perfSkybox=")) {
 this->iPerfSkybox = Integer.parseInt(string0.replaceFirst("perfSkybox=", ""));
 this->iPerfSkybox_new = this->iPerfSkybox;
 } else if (string0.startsWith("perfPuddles=")) {
 this->iPerfPuddles = Integer.parseInt(string0.replaceFirst("perfPuddles=", ""));
 this->iPerfPuddles_new = this->iPerfPuddles;
 } else if (string0.startsWith("bPerfReflections=")) {
 this->bPerfReflections = Boolean.parseBoolean(string0.replaceFirst("bPerfReflections=", ""));
 this->bPerfReflections_new = this->bPerfReflections;
 } else if (string0.startsWith("language=")) {
 OptionLanguageName = string0.replaceFirst("language=", "").trim();
 } else if (string0.startsWith("zoom=")) {
 OptionZoom = Boolean.parseBoolean(string0.replaceFirst("zoom=", ""));
 } else if (string0.startsWith("autozoom=")) {
 String[] strings0 = string0.replaceFirst("autozoom=", "").split(",");

 for (int int4 = 0; int4 < strings0.length; int4++) {
 if (!strings0[int4].empty()) {
 int int5 = Integer.parseInt(strings0[int4]);
 if (int5 >= 1 && int5 <= 4) {
 this->setAutoZoom(int5 - 1, true);
 }
 }
 }
 } else if (string0.startsWith("fontSize=")) {
 this->setOptionFontSize(Integer.parseInt(string0.replaceFirst("fontSize=", "").trim()));
 } else if (string0.startsWith("contextMenuFont=")) {
 OptionContextMenuFont = string0.replaceFirst("contextMenuFont=", "").trim();
 } else if (string0.startsWith("inventoryFont=")) {
 OptionInventoryFont = string0.replaceFirst("inventoryFont=", "").trim();
 } else if (string0.startsWith("inventoryContainerSize=")) {
 OptionInventoryContainerSize = PZMath.tryParseInt(string0.replaceFirst("inventoryContainerSize=", ""), 1);
 OptionInventoryContainerSize = PZMath.clamp(OptionInventoryContainerSize, 1, 3);
 } else if (string0.startsWith("tooltipFont=")) {
 OptionTooltipFont = string0.replaceFirst("tooltipFont=", "").trim();
 } else if (string0.startsWith("measurementsFormat=")) {
 OptionMeasurementFormat = string0.replaceFirst("measurementsFormat=", "").trim();
 } else if (string0.startsWith("clockFormat=")) {
 OptionClockFormat = Integer.parseInt(string0.replaceFirst("clockFormat=", ""));
 } else if (string0.startsWith("clockSize=")) {
 OptionClockSize = Integer.parseInt(string0.replaceFirst("clockSize=", ""));
 } else if (string0.startsWith("clock24Hour=")) {
 OptionClock24Hour = Boolean.parseBoolean(string0.replaceFirst("clock24Hour=", ""));
 } else if (string0.startsWith("vsync=")) {
 OptionVSync = Boolean.parseBoolean(string0.replaceFirst("vsync=", ""));
 } else if (string0.startsWith("voiceEnable=")) {
 OptionVoiceEnable = Boolean.parseBoolean(string0.replaceFirst("voiceEnable=", ""));
 } else if (string0.startsWith("voiceMode=")) {
 OptionVoiceMode = Integer.parseInt(string0.replaceFirst("voiceMode=", ""));
 } else if (string0.startsWith("voiceVADMode=")) {
 OptionVoiceVADMode = Integer.parseInt(string0.replaceFirst("voiceVADMode=", ""));
 } else if (string0.startsWith("voiceAGCMode=")) {
 OptionVoiceAGCMode = Integer.parseInt(string0.replaceFirst("voiceAGCMode=", ""));
 } else if (string0.startsWith("voiceVolumeMic=")) {
 OptionVoiceVolumeMic = Integer.parseInt(string0.replaceFirst("voiceVolumeMic=", ""));
 } else if (string0.startsWith("voiceVolumePlayers=")) {
 OptionVoiceVolumePlayers = Integer.parseInt(string0.replaceFirst("voiceVolumePlayers=", ""));
 } else if (string0.startsWith("voiceRecordDeviceName=")) {
 OptionVoiceRecordDeviceName = string0.replaceFirst("voiceRecordDeviceName=", "");
 } else if (string0.startsWith("soundVolume=")) {
 OptionSoundVolume = Integer.parseInt(string0.replaceFirst("soundVolume=", ""));
 } else if (string0.startsWith("musicVolume=")) {
 OptionMusicVolume = Integer.parseInt(string0.replaceFirst("musicVolume=", ""));
 } else if (string0.startsWith("ambientVolume=")) {
 OptionAmbientVolume = Integer.parseInt(string0.replaceFirst("ambientVolume=", ""));
 } else if (string0.startsWith("jumpScareVolume=")) {
 OptionJumpScareVolume = Integer.parseInt(string0.replaceFirst("jumpScareVolume=", ""));
 } else if (string0.startsWith("musicActionStyle=")) {
 OptionMusicActionStyle = Integer.parseInt(string0.replaceFirst("musicActionStyle=", ""));
 } else if (string0.startsWith("musicLibrary=")) {
 OptionMusicLibrary = Integer.parseInt(string0.replaceFirst("musicLibrary=", ""));
 } else if (string0.startsWith("vehicleEngineVolume=")) {
 OptionVehicleEngineVolume = Integer.parseInt(string0.replaceFirst("vehicleEngineVolume=", ""));
 } else if (string0.startsWith("reloadDifficulty=")) {
 OptionReloadDifficulty = Integer.parseInt(string0.replaceFirst("reloadDifficulty=", ""));
 } else if (string0.startsWith("rackProgress=")) {
 OptionRackProgress = Boolean.parseBoolean(string0.replaceFirst("rackProgress=", ""));
 } else if (string0.startsWith("controller=")) {
 std::string string1 = string0.replaceFirst("controller=", "");
 if (!string1.empty()) {
 JoypadManager.instance.setControllerActive(string1, true);
 }
 } else if (string0.startsWith("tutorialDone=")) {
 this->tutorialDone = Boolean.parseBoolean(string0.replaceFirst("tutorialDone=", ""));
 } else if (string0.startsWith("vehiclesWarningShow=")) {
 this->vehiclesWarningShow = Boolean.parseBoolean(string0.replaceFirst("vehiclesWarningShow=", ""));
 } else if (string0.startsWith("bloodDecals=")) {
 this->setOptionBloodDecals(Integer.parseInt(string0.replaceFirst("bloodDecals=", "")));
 } else if (string0.startsWith("borderless=")) {
 OptionBorderlessWindow = Boolean.parseBoolean(string0.replaceFirst("borderless=", ""));
 } else if (string0.startsWith("lockCursorToWindow=")) {
 OptionLockCursorToWindow = Boolean.parseBoolean(string0.replaceFirst("lockCursorToWindow=", ""));
 } else if (string0.startsWith("textureCompression=")) {
 OptionTextureCompression = Boolean.parseBoolean(string0.replaceFirst("textureCompression=", ""));
 } else if (string0.startsWith("modelTextureMipmaps=")) {
 OptionModelTextureMipmaps = Boolean.parseBoolean(string0.replaceFirst("modelTextureMipmaps=", ""));
 } else if (string0.startsWith("texture2x=")) {
 OptionTexture2x = Boolean.parseBoolean(string0.replaceFirst("texture2x=", ""));
 } else if (string0.startsWith("maxTextureSize=")) {
 OptionMaxTextureSize = Integer.parseInt(string0.replaceFirst("maxTextureSize=", ""));
 OptionMaxTextureSize = PZMath.clamp(OptionMaxTextureSize, 1, 4);
 } else if (string0.startsWith("maxVehicleTextureSize=")) {
 OptionMaxVehicleTextureSize = Integer.parseInt(string0.replaceFirst("maxVehicleTextureSize=", ""));
 OptionMaxVehicleTextureSize = PZMath.clamp(OptionMaxVehicleTextureSize, 1, 4);
 } else if (string0.startsWith("zoomLevels1x=")) {
 OptionZoomLevels1x = string0.replaceFirst("zoomLevels1x=", "");
 } else if (string0.startsWith("zoomLevels2x=")) {
 OptionZoomLevels2x = string0.replaceFirst("zoomLevels2x=", "");
 } else if (string0.startsWith("showChatTimestamp=")) {
 OptionShowChatTimestamp = Boolean.parseBoolean(string0.replaceFirst("showChatTimestamp=", ""));
 } else if (string0.startsWith("showChatTitle=")) {
 OptionShowChatTitle = Boolean.parseBoolean(string0.replaceFirst("showChatTitle=", ""));
 } else if (string0.startsWith("chatFontSize=")) {
 OptionChatFontSize = string0.replaceFirst("chatFontSize=", "");
 } else if (string0.startsWith("minChatOpaque=")) {
 OptionMinChatOpaque = Float.parseFloat(string0.replaceFirst("minChatOpaque=", ""));
 } else if (string0.startsWith("maxChatOpaque=")) {
 OptionMaxChatOpaque = Float.parseFloat(string0.replaceFirst("maxChatOpaque=", ""));
 } else if (string0.startsWith("chatFadeTime=")) {
 OptionChatFadeTime = Float.parseFloat(string0.replaceFirst("chatFadeTime=", ""));
 } else if (string0.startsWith("chatOpaqueOnFocus=")) {
 OptionChatOpaqueOnFocus = Boolean.parseBoolean(string0.replaceFirst("chatOpaqueOnFocus=", ""));
 } else if (string0.startsWith("doneNewSaveFolder=")) {
 this->doneNewSaveFolder = Boolean.parseBoolean(string0.replaceFirst("doneNewSaveFolder=", ""));
 } else if (string0.startsWith("contentTranslationsEnabled=")) {
 OptionEnableContentTranslations = Boolean.parseBoolean(string0.replaceFirst("contentTranslationsEnabled=", ""));
 } else if (string0.startsWith("showYourUsername=")) {
 this->showYourUsername = Boolean.parseBoolean(string0.replaceFirst("showYourUsername=", ""));
 } else if (string0.startsWith("riversideDone=")) {
 this->riversideDone = Boolean.parseBoolean(string0.replaceFirst("riversideDone=", ""));
 } else if (string0.startsWith("rosewoodSpawnDone=")) {
 this->rosewoodSpawnDone = Boolean.parseBoolean(string0.replaceFirst("rosewoodSpawnDone=", ""));
 } else if (string0.startsWith("gotNewBelt=")) {
 this->gotNewBelt = Boolean.parseBoolean(string0.replaceFirst("gotNewBelt=", ""));
 } else if (string0.startsWith("mpTextColor=")) {
 String[] strings1 = string0.replaceFirst("mpTextColor=", "").split(",");
 float float0 = Float.parseFloat(strings1[0]);
 float float1 = Float.parseFloat(strings1[1]);
 float float2 = Float.parseFloat(strings1[2]);
 if (float0 < 0.19F) {
 float0 = 0.19F;
 }

 if (float1 < 0.19F) {
 float1 = 0.19F;
 }

 if (float2 < 0.19F) {
 float2 = 0.19F;
 }

 this->mpTextColor = new ColorInfo(float0, float1, float2, 1.0F);
 } else if (string0.startsWith("objHighlightColor=")) {
 String[] strings2 = string0.replaceFirst("objHighlightColor=", "").split(",");
 float float3 = Float.parseFloat(strings2[0]);
 float float4 = Float.parseFloat(strings2[1]);
 float float5 = Float.parseFloat(strings2[2]);
 if (float3 < 0.19F) {
 float3 = 0.19F;
 }

 if (float4 < 0.19F) {
 float4 = 0.19F;
 }

 if (float5 < 0.19F) {
 float5 = 0.19F;
 }

 this->objectHighlitedColor.set(float3, float4, float5, 1.0F);
 } else if (string0.startsWith("goodHighlightColor=")) {
 String[] strings3 = string0.replaceFirst("goodHighlightColor=", "").split(",");
 float float6 = Float.parseFloat(strings3[0]);
 float float7 = Float.parseFloat(strings3[1]);
 float float8 = Float.parseFloat(strings3[2]);
 this->goodHighlitedColor.set(float6, float7, float8, 1.0F);
 } else if (string0.startsWith("badHighlightColor=")) {
 String[] strings4 = string0.replaceFirst("badHighlightColor=", "").split(",");
 float float9 = Float.parseFloat(strings4[0]);
 float float10 = Float.parseFloat(strings4[1]);
 float float11 = Float.parseFloat(strings4[2]);
 this->badHighlitedColor.set(float9, float10, float11, 1.0F);
 } else if (string0.startsWith("seenNews=")) {
 this->setSeenUpdateText(string0.replaceFirst("seenNews=", ""));
 } else if (string0.startsWith("toggleToAim=")) {
 this->setToggleToAim(Boolean.parseBoolean(string0.replaceFirst("toggleToAim=", "")));
 } else if (string0.startsWith("toggleToRun=")) {
 this->setToggleToRun(Boolean.parseBoolean(string0.replaceFirst("toggleToRun=", "")));
 } else if (string0.startsWith("toggleToSprint=")) {
 this->setToggleToSprint(Boolean.parseBoolean(string0.replaceFirst("toggleToSprint=", "")));
 } else if (string0.startsWith("celsius=")) {
 this->setCelsius(Boolean.parseBoolean(string0.replaceFirst("celsius=", "")));
 } else if (!string0.startsWith("mapOrder=")) {
 if (string0.startsWith("showFirstTimeSneakTutorial=")) {
 this->setShowFirstTimeSneakTutorial(Boolean.parseBoolean(string0.replaceFirst("showFirstTimeSneakTutorial=", "")));
 } else if (string0.startsWith("showFirstTimeSearchTutorial=")) {
 this->setShowFirstTimeSearchTutorial(Boolean.parseBoolean(string0.replaceFirst("showFirstTimeSearchTutorial=", "")));
 } else if (string0.startsWith("termsOfServiceVersion=")) {
 this->termsOfServiceVersion = Integer.parseInt(string0.replaceFirst("termsOfServiceVersion=", ""));
 } else if (string0.startsWith("uiRenderOffscreen=")) {
 OptionUIFBO = Boolean.parseBoolean(string0.replaceFirst("uiRenderOffscreen=", ""));
 } else if (string0.startsWith("uiRenderFPS=")) {
 OptionUIRenderFPS = Integer.parseInt(string0.replaceFirst("uiRenderFPS=", ""));
 } else if (string0.startsWith("radialMenuKeyToggle=")) {
 OptionRadialMenuKeyToggle = Boolean.parseBoolean(string0.replaceFirst("radialMenuKeyToggle=", ""));
 } else if (string0.startsWith("reloadRadialInstant=")) {
 OptionReloadRadialInstant = Boolean.parseBoolean(string0.replaceFirst("reloadRadialInstant=", ""));
 } else if (string0.startsWith("panCameraWhileAiming=")) {
 OptionPanCameraWhileAiming = Boolean.parseBoolean(string0.replaceFirst("panCameraWhileAiming=", ""));
 } else if (string0.startsWith("panCameraWhileDriving=")) {
 OptionPanCameraWhileDriving = Boolean.parseBoolean(string0.replaceFirst("panCameraWhileDriving=", ""));
 } else if (string0.startsWith("temperatureDisplayCelsius=")) {
 OptionTemperatureDisplayCelsius = Boolean.parseBoolean(string0.replaceFirst("temperatureDisplayCelsius=", ""));
 } else if (string0.startsWith("doWindSpriteEffects=")) {
 OptionDoWindSpriteEffects = Boolean.parseBoolean(string0.replaceFirst("doWindSpriteEffects=", ""));
 } else if (string0.startsWith("doDoorSpriteEffects=")) {
 OptionDoDoorSpriteEffects = Boolean.parseBoolean(string0.replaceFirst("doDoorSpriteEffects=", ""));
 } else if (string0.startsWith("doContainerOutline=")) {
 OptionDoContainerOutline = Boolean.parseBoolean(string0.replaceFirst("doContainerOutline=", ""));
 } else if (string0.startsWith("updateSneakButton2=")) {
 OptionUpdateSneakButton = true;
 } else if (string0.startsWith("updateSneakButton=")) {
 OptionUpdateSneakButton = Boolean.parseBoolean(string0.replaceFirst("updateSneakButton=", ""));
 } else if (string0.startsWith("dblTapJogToSprint=")) {
 OptiondblTapJogToSprint = Boolean.parseBoolean(string0.replaceFirst("dblTapJogToSprint=", ""));
 } else if (string0.startsWith("aimOutline=")) {
 this->setOptionAimOutline(PZMath.tryParseInt(string0.replaceFirst("aimOutline=", ""), 2);
 } else if (string0.startsWith("cycleContainerKey=")) {
 OptionCycleContainerKey = string0.replaceFirst("cycleContainerKey=", "");
 } else if (string0.startsWith("dropItemsOnSquareCenter=")) {
 OptionDropItemsOnSquareCenter = Boolean.parseBoolean(string0.replaceFirst("dropItemsOnSquareCenter=", ""));
 } else if (string0.startsWith("timedActionGameSpeedReset=")) {
 OptionTimedActionGameSpeedReset = Boolean.parseBoolean(string0.replaceFirst("timedActionGameSpeedReset=", ""));
 } else if (string0.startsWith("shoulderButtonContainerSwitch=")) {
 OptionShoulderButtonContainerSwitch = Integer.parseInt(string0.replaceFirst("shoulderButtonContainerSwitch=", ""));
 } else if (string0.startsWith("singleContextMenu=")) {
 this->readPerPlayerBoolean(string0.replaceFirst("singleContextMenu=", ""), OptionSingleContextMenu);
 } else if (string0.startsWith("renderPrecipIndoors=")) {
 OptionRenderPrecipIndoors = Boolean.parseBoolean(string0.replaceFirst("renderPrecipIndoors=", ""));
 } else if (string0.startsWith("autoProneAtk=")) {
 OptionAutoProneAtk = Boolean.parseBoolean(string0.replaceFirst("autoProneAtk=", ""));
 } else if (string0.startsWith("3DGroundItem=")) {
 Option3DGroundItem = Boolean.parseBoolean(string0.replaceFirst("3DGroundItem=", ""));
 } else if (string0.startsWith("tieredZombieUpdates=")) {
 this->setOptionTieredZombieUpdates(Boolean.parseBoolean(string0.replaceFirst("tieredZombieUpdates=", "")));
 } else if (string0.startsWith("progressBar=")) {
 this->setOptionProgressBar(Boolean.parseBoolean(string0.replaceFirst("progressBar=", "")));
 } else if (string0.startsWith("corpseShadows=")) {
 OptionCorpseShadows = Boolean.parseBoolean(string0.replaceFirst("corpseShadows=", ""));
 } else if (string0.startsWith("simpleClothingTextures=")) {
 this->setOptionSimpleClothingTextures(PZMath.tryParseInt(string0.replaceFirst("simpleClothingTextures=", ""), 1);
 } else if (string0.startsWith("simpleWeaponTextures=")) {
 OptionSimpleWeaponTextures = Boolean.parseBoolean(string0.replaceFirst("simpleWeaponTextures=", ""));
 } else if (string0.startsWith("autoDrink=")) {
 OptionAutoDrink = Boolean.parseBoolean(string0.replaceFirst("autoDrink=", ""));
 } else if (string0.startsWith("leaveKeyInIgnition=")) {
 OptionLeaveKeyInIgnition = Boolean.parseBoolean(string0.replaceFirst("leaveKeyInIgnition=", ""));
 } else if (string0.startsWith("autoWalkContainer=")) {
 OptionAutoWalkContainer = Boolean.parseBoolean(string0.replaceFirst("autoWalkContainer=", ""));
 } else if (string0.startsWith("searchModeOverlayEffect=")) {
 OptionSearchModeOverlayEffect = Integer.parseInt(string0.replaceFirst("searchModeOverlayEffect=", ""));
 } else if (string0.startsWith("ignoreProneZombieRange=")) {
 this->setOptionIgnoreProneZombieRange(PZMath.tryParseInt(string0.replaceFirst("ignoreProneZombieRange=", ""), 1);
 } else if (string0.startsWith("fogQuality=")) {
 PerformanceSettings.FogQuality = Integer.parseInt(string0.replaceFirst("fogQuality=", ""));
 } else if (string0.startsWith("renderPrecipitation=")) {
 OptionRenderPrecipitation = Integer.parseInt(string0.replaceFirst("renderPrecipitation=", ""));
 } else if (string0.startsWith("showItemModInfo=")) {
 OptionShowItemModInfo = Boolean.parseBoolean(string0.replaceFirst("showItemModInfo=", ""));
 } else if (string0.startsWith("showSurvivalGuide=")) {
 this->OptionShowSurvivalGuide = Boolean.parseBoolean(string0.replaceFirst("showSurvivalGuide=", ""));
 } else if (string0.startsWith("enableLeftJoystickRadialMenu=")) {
 OptionEnableLeftJoystickRadialMenu = Boolean.parseBoolean(string0.replaceFirst("enableLeftJoystickRadialMenu=", ""));
 }
 } else {
 if (this->version < 7) {
 string0 = "mapOrder=";
 }

 String[] strings5 = string0.replaceFirst("mapOrder=", "").split(";");

 for (auto& string2 : strings5) string2 = string2.trim();
 if (!string2.empty()) {
 ActiveMods.getById("default").getMapOrder().add(string2);
 }
 }

 ZomboidFileSystem.instance.saveModsFile();
 }
 }

 if (OptionLanguageName.empty()) {
 OptionLanguageName = System.getProperty("user.language").toUpperCase();
 }

 if (!this->doneNewSaveFolder) {
 File file2 = new File(ZomboidFileSystem.instance.getSaveDir());
 file2.mkdir();
 std::vector arrayList = new ArrayList();
 arrayList.add("Beginner");
 arrayList.add("Survival");
 arrayList.add("A Really CD DA");
 arrayList.add("LastStand");
 arrayList.add("Opening Hours");
 arrayList.add("Sandbox");
 arrayList.add("Tutorial");
 arrayList.add("Winter is Coming");
 arrayList.add("You Have One Day");
 void* object = nullptr;
 File file3 = nullptr;

 try {
 for (auto& string3 : arrayList) object = new File(ZomboidFileSystem.instance.getCacheDir() + File.separator + string3);
 file3 = new File(ZomboidFileSystem.instance.getSaveDir() + File.separator + string3);
 if (object.exists()) {
 file3.mkdir();
 Files.move(object.toPath(), file3.toPath(), StandardCopyOption.REPLACE_EXISTING);
 }
 }
 } catch (Exception exception0) {
 }

 this->doneNewSaveFolder = true;
 }
 } catch (Exception exception1) {
 exception1.printStackTrace();
 } finally {
 bufferedReader.close();
 }

 this->saveOptions();
 return true;
 }
 }

 bool isDefaultOptions() {
 return !this->bLoadedOptions;
 }

 bool isDedicated() {
 return GameServer.bServer;
 }

 void copyPasteFolders(const std::string& string) {
 File file = new File(string).getAbsoluteFile();
 if (file.exists()) {
 this->searchFolders(file, string);
 }
 }

 void searchFolders(File file0, const std::string& string) {
 if (file0.isDirectory()) {
 File file1 = new File(this->saveFolder + File.separator + string);
 file1.mkdir();
 String[] strings = file0.list();

 for (int int0 = 0; int0 < strings.length; int0++) {
 this->searchFolders(new File(file0.getAbsolutePath() + File.separator + strings[int0]), string + File.separator + strings[int0]);
 }
 } else {
 this->copyPasteFile(file0, string);
 }
 }

 void copyPasteFile(File file1, const std::string& string) {
 FileOutputStream fileOutputStream = nullptr;
 FileInputStream fileInputStream = nullptr;

 try {
 File file0 = new File(this->saveFolder + File.separator + string);
 file0.createNewFile();
 fileOutputStream = new FileOutputStream(file0);
 fileInputStream = new FileInputStream(file1);
 fileOutputStream.getChannel().transferFrom(fileInputStream.getChannel(), 0L, file1.length());
 } catch (Exception exception) {
 exception.printStackTrace();
 } finally {
 try {
 if (fileInputStream != nullptr) {
 fileInputStream.close();
 }

 if (fileOutputStream != nullptr) {
 fileOutputStream.close();
 }
 } catch (IOException iOException) {
 iOException.printStackTrace();
 }
 }
 }

 static std::string getMyDocumentFolder() {
 return ZomboidFileSystem.instance.getCacheDir();
 }

 void saveOptions() {
 File file = new File(ZomboidFileSystem.instance.getCacheDir() + File.separator + "options.ini");
 if (!file.exists()) {
 file.createNewFile();
 }

 FileWriter fileWriter = new FileWriter(file);

 try {
 fileWriter.write("version=" + this->fileversion + "\r\n");
 fileWriter.write("width=" + this->getScreenWidth() + "\r\n");
 fileWriter.write("height=" + this->getScreenHeight() + "\r\n");
 fileWriter.write("fullScreen=" + fullScreen + "\r\n");
 fileWriter.write("frameRate=" + PerformanceSettings.getLockFPS() + "\r\n");
 fileWriter.write("uncappedFPS=" + PerformanceSettings.isUncappedFPS() + "\r\n");
 fileWriter.write("iso_cursor=" + getInstance().getIsoCursorVisibility() + "\r\n");
 fileWriter.write("showCursorWhileAiming=" + OptionShowCursorWhileAiming + "\r\n");
 fileWriter.write("water=" + PerformanceSettings.WaterQuality + "\r\n");
 fileWriter.write("puddles=" + PerformanceSettings.PuddlesQuality + "\r\n");
 fileWriter.write("lighting=" + PerformanceSettings.LightingFrameSkip + "\r\n");
 fileWriter.write("lightFPS=" + PerformanceSettings.LightingFPS + "\r\n");
 fileWriter.write("perfSkybox=" + this->iPerfSkybox_new + "\r\n");
 fileWriter.write("perfPuddles=" + this->iPerfPuddles_new + "\r\n");
 fileWriter.write("bPerfReflections=" + this->bPerfReflections_new + "\r\n");
 fileWriter.write("vidMem=" + this->vidMem + "\r\n");
 fileWriter.write("language=" + this->getOptionLanguageName() + "\r\n");
 fileWriter.write("zoom=" + OptionZoom + "\r\n");
 fileWriter.write("fontSize=" + OptionFontSize + "\r\n");
 fileWriter.write("contextMenuFont=" + OptionContextMenuFont + "\r\n");
 fileWriter.write("inventoryFont=" + OptionInventoryFont + "\r\n");
 fileWriter.write("inventoryContainerSize=" + OptionInventoryContainerSize + "\r\n");
 fileWriter.write("tooltipFont=" + OptionTooltipFont + "\r\n");
 fileWriter.write("clockFormat=" + OptionClockFormat + "\r\n");
 fileWriter.write("clockSize=" + OptionClockSize + "\r\n");
 fileWriter.write("clock24Hour=" + OptionClock24Hour + "\r\n");
 fileWriter.write("measurementsFormat=" + OptionMeasurementFormat + "\r\n");
 std::string string0 = "";

 for (int int0 = 0; int0 < 4; int0++) {
 if (bAutoZoom[int0]) {
 if (!string0.empty()) {
 string0 = string0 + ",";
 }

 string0 = string0 + (int0 + 1);
 }
 }

 fileWriter.write("autozoom=" + string0 + "\r\n");
 fileWriter.write("vsync=" + OptionVSync + "\r\n");
 fileWriter.write("soundVolume=" + OptionSoundVolume + "\r\n");
 fileWriter.write("ambientVolume=" + OptionAmbientVolume + "\r\n");
 fileWriter.write("musicVolume=" + OptionMusicVolume + "\r\n");
 fileWriter.write("jumpScareVolume=" + OptionJumpScareVolume + "\r\n");
 fileWriter.write("musicActionStyle=" + OptionMusicActionStyle + "\r\n");
 fileWriter.write("musicLibrary=" + OptionMusicLibrary + "\r\n");
 fileWriter.write("vehicleEngineVolume=" + OptionVehicleEngineVolume + "\r\n");
 fileWriter.write("voiceEnable=" + OptionVoiceEnable + "\r\n");
 fileWriter.write("voiceMode=" + OptionVoiceMode + "\r\n");
 fileWriter.write("voiceVADMode=" + OptionVoiceVADMode + "\r\n");
 fileWriter.write("voiceAGCMode=" + OptionVoiceAGCMode + "\r\n");
 fileWriter.write("voiceVolumeMic=" + OptionVoiceVolumeMic + "\r\n");
 fileWriter.write("voiceVolumePlayers=" + OptionVoiceVolumePlayers + "\r\n");
 fileWriter.write("voiceRecordDeviceName=" + OptionVoiceRecordDeviceName + "\r\n");
 fileWriter.write("reloadDifficulty=" + OptionReloadDifficulty + "\r\n");
 fileWriter.write("rackProgress=" + OptionRackProgress + "\r\n");

 for (String string1 : JoypadManager.instance.ActiveControllerGUIDs) {
 fileWriter.write("controller=" + string1 + "\r\n");
 }

 fileWriter.write("tutorialDone=" + this->isTutorialDone() + "\r\n");
 fileWriter.write("vehiclesWarningShow=" + this->isVehiclesWarningShow() + "\r\n");
 fileWriter.write("bloodDecals=" + OptionBloodDecals + "\r\n");
 fileWriter.write("borderless=" + OptionBorderlessWindow + "\r\n");
 fileWriter.write("lockCursorToWindow=" + OptionLockCursorToWindow + "\r\n");
 fileWriter.write("textureCompression=" + OptionTextureCompression + "\r\n");
 fileWriter.write("modelTextureMipmaps=" + OptionModelTextureMipmaps + "\r\n");
 fileWriter.write("texture2x=" + OptionTexture2x + "\r\n");
 fileWriter.write("maxTextureSize=" + OptionMaxTextureSize + "\r\n");
 fileWriter.write("maxVehicleTextureSize=" + OptionMaxVehicleTextureSize + "\r\n");
 fileWriter.write("zoomLevels1x=" + OptionZoomLevels1x + "\r\n");
 fileWriter.write("zoomLevels2x=" + OptionZoomLevels2x + "\r\n");
 fileWriter.write("showChatTimestamp=" + OptionShowChatTimestamp + "\r\n");
 fileWriter.write("showChatTitle=" + OptionShowChatTitle + "\r\n");
 fileWriter.write("chatFontSize=" + OptionChatFontSize + "\r\n");
 fileWriter.write("minChatOpaque=" + OptionMinChatOpaque + "\r\n");
 fileWriter.write("maxChatOpaque=" + OptionMaxChatOpaque + "\r\n");
 fileWriter.write("chatFadeTime=" + OptionChatFadeTime + "\r\n");
 fileWriter.write("chatOpaqueOnFocus=" + OptionChatOpaqueOnFocus + "\r\n");
 fileWriter.write("doneNewSaveFolder=" + this->doneNewSaveFolder + "\r\n");
 fileWriter.write("contentTranslationsEnabled=" + OptionEnableContentTranslations + "\r\n");
 fileWriter.write("showYourUsername=" + this->showYourUsername + "\r\n");
 fileWriter.write("rosewoodSpawnDone=" + this->rosewoodSpawnDone + "\r\n");
 if (this->mpTextColor != nullptr) {
 fileWriter.write("mpTextColor=" + this->mpTextColor.r + "," + this->mpTextColor.g + "," + this->mpTextColor.b + "\r\n");
 }

 fileWriter.write(
 "objHighlightColor=" + this->objectHighlitedColor.r + "," + this->objectHighlitedColor.g + "," + this->objectHighlitedColor.b + "\r\n"
 );
 fileWriter.write("seenNews=" + this->getSeenUpdateText() + "\r\n");
 fileWriter.write("toggleToAim=" + this->isToggleToAim() + "\r\n");
 fileWriter.write("toggleToRun=" + this->isToggleToRun() + "\r\n");
 fileWriter.write("toggleToSprint=" + this->isToggleToSprint() + "\r\n");
 fileWriter.write("celsius=" + this->isCelsius() + "\r\n");
 fileWriter.write("riversideDone=" + this->isRiversideDone() + "\r\n");
 fileWriter.write("showFirstTimeSneakTutorial=" + this->isShowFirstTimeSneakTutorial() + "\r\n");
 fileWriter.write("showFirstTimeSearchTutorial=" + this->isShowFirstTimeSearchTutorial() + "\r\n");
 fileWriter.write("termsOfServiceVersion=" + this->termsOfServiceVersion + "\r\n");
 fileWriter.write("uiRenderOffscreen=" + OptionUIFBO + "\r\n");
 fileWriter.write("uiRenderFPS=" + OptionUIRenderFPS + "\r\n");
 fileWriter.write("radialMenuKeyToggle=" + OptionRadialMenuKeyToggle + "\r\n");
 fileWriter.write("reloadRadialInstant=" + OptionReloadRadialInstant + "\r\n");
 fileWriter.write("panCameraWhileAiming=" + OptionPanCameraWhileAiming + "\r\n");
 fileWriter.write("panCameraWhileDriving=" + OptionPanCameraWhileDriving + "\r\n");
 fileWriter.write("temperatureDisplayCelsius=" + OptionTemperatureDisplayCelsius + "\r\n");
 fileWriter.write("doWindSpriteEffects=" + OptionDoWindSpriteEffects + "\r\n");
 fileWriter.write("doDoorSpriteEffects=" + OptionDoDoorSpriteEffects + "\r\n");
 fileWriter.write("doDoContainerOutline=" + OptionDoContainerOutline + "\r\n");
 fileWriter.write("updateSneakButton=" + OptionUpdateSneakButton + "\r\n");
 fileWriter.write("dblTapJogToSprint=" + OptiondblTapJogToSprint + "\r\n");
 fileWriter.write("gotNewBelt=" + this->gotNewBelt + "\r\n");
 fileWriter.write("aimOutline=" + OptionAimOutline + "\r\n");
 fileWriter.write("cycleContainerKey=" + OptionCycleContainerKey + "\r\n");
 fileWriter.write("dropItemsOnSquareCenter=" + OptionDropItemsOnSquareCenter + "\r\n");
 fileWriter.write("timedActionGameSpeedReset=" + OptionTimedActionGameSpeedReset + "\r\n");
 fileWriter.write("shoulderButtonContainerSwitch=" + OptionShoulderButtonContainerSwitch + "\r\n");
 fileWriter.write("singleContextMenu=" + this->getPerPlayerBooleanString(OptionSingleContextMenu) + "\r\n");
 fileWriter.write("renderPrecipIndoors=" + OptionRenderPrecipIndoors + "\r\n");
 fileWriter.write("autoProneAtk=" + OptionAutoProneAtk + "\r\n");
 fileWriter.write("3DGroundItem=" + Option3DGroundItem + "\r\n");
 fileWriter.write("tieredZombieUpdates=" + this->getOptionTieredZombieUpdates() + "\r\n");
 fileWriter.write("progressBar=" + this->isOptionProgressBar() + "\r\n");
 fileWriter.write("corpseShadows=" + this->getOptionCorpseShadows() + "\r\n");
 fileWriter.write("simpleClothingTextures=" + this->getOptionSimpleClothingTextures() + "\r\n");
 fileWriter.write("simpleWeaponTextures=" + this->getOptionSimpleWeaponTextures() + "\r\n");
 fileWriter.write("autoDrink=" + this->getOptionAutoDrink() + "\r\n");
 fileWriter.write("leaveKeyInIgnition=" + this->getOptionLeaveKeyInIgnition() + "\r\n");
 fileWriter.write("autoWalkContainer=" + this->getOptionAutoWalkContainer() + "\r\n");
 fileWriter.write("searchModeOverlayEffect=" + this->getOptionSearchModeOverlayEffect() + "\r\n");
 fileWriter.write("ignoreProneZombieRange=" + this->getOptionIgnoreProneZombieRange() + "\r\n");
 fileWriter.write("fogQuality=" + PerformanceSettings.FogQuality + "\r\n");
 fileWriter.write("renderPrecipitation=" + OptionRenderPrecipitation + "\r\n");
 fileWriter.write("showItemModInfo=" + OptionShowItemModInfo + "\r\n");
 fileWriter.write("showSurvivalGuide=" + this->OptionShowSurvivalGuide + "\r\n");
 fileWriter.write("enableLeftJoystickRadialMenu=" + OptionEnableLeftJoystickRadialMenu + "\r\n");
 fileWriter.write("doContainerOutline=" + OptionDoContainerOutline + "\r\n");
 fileWriter.write("goodHighlightColor=" + this->goodHighlitedColor.r + "," + this->goodHighlitedColor.g + "," + this->goodHighlitedColor.b + "\r\n");
 fileWriter.write("badHighlightColor=" + this->badHighlitedColor.r + "," + this->badHighlitedColor.g + "," + this->badHighlitedColor.b + "\r\n");
 } catch (Exception exception) {
 exception.printStackTrace();
 } finally {
 fileWriter.close();
 }
 }

 void setWindowed(bool b) {
 RenderThread.invokeOnRenderContext(() -> {
 if (b != fullScreen) {
 setDisplayMode(this->getScreenWidth(), this->getScreenHeight(), b);
 }

 fullScreen = b;
 if (fakefullscreen) {
 Display.setResizable(false);
 } else {
 Display.setResizable(!b);
 }

 try {
 this->saveOptions();
 } catch (IOException iOException) {
 iOException.printStackTrace();
 }
 });
 }

 bool isFullScreen() {
 return fullScreen;
 }

 KahluaTable getScreenModes() {
 std::vector arrayList = new ArrayList();
 KahluaTable table = LuaManager.platform.newTable();
 File file = new File(LuaManager.getLuaCacheDir() + File.separator + "screenresolution.ini");
 int int0 = 1;

 try {
 if (!file.exists()) {
 file.createNewFile();
 FileWriter fileWriter = new FileWriter(file);
 int integer0 = 0;
 int integer1 = 0;
 DisplayMode[] displayModes = Display.getAvailableDisplayModes();

 for (int int1 = 0; int1 < displayModes.length; int1++) {
 integer0 = displayModes[int1].getWidth();
 integer1 = displayModes[int1].getHeight();
 if (!arrayList.contains(integer0 + " x " + integer1) {
 table.rawset(int0, integer0 + " x " + integer1);
 fileWriter.write(integer0 + " x " + integer1 + " \r\n");
 arrayList.add(integer0 + " x " + integer1);
 int0++;
 }
 }

 fileWriter.close();
 } else {
 BufferedReader bufferedReader = new BufferedReader(new FileReader(file);

 std::string string;
 for (string = nullptr; (string = bufferedReader.readLine()) != nullptr; int0++) {
 table.rawset(int0, string.trim());
 }

 bufferedReader.close();
 }
 } catch (Exception exception) {
 exception.printStackTrace();
 }

 return table;
 }

 static void setDisplayMode(int _width, int _height, bool fullscreen) {
 RenderThread.invokeOnRenderContext(
 () -> {
 if (Display.getWidth() != _width
 || Display.getHeight() != _height
 || Display.isFullscreen() != fullscreen
 || Display.isBorderlessWindow() != OptionBorderlessWindow) {
 fullScreen = fullscreen;

 try {
 DisplayMode displayMode0 = nullptr;
 if (!fullscreen) {
 if (OptionBorderlessWindow) {
 if (Display.getWindow() != 0L && Display.isFullscreen()) {
 Display.setFullscreen(false);
 }

 long long0 = GLFW.glfwGetPrimaryMonitor();
 GLFWVidMode gLFWVidMode = GLFW.glfwGetVideoMode(long0);
 displayMode0 = new DisplayMode(gLFWVidMode.width(), gLFWVidMode.height());
 } else {
 displayMode0 = new DisplayMode(_width, _height);
 }
 } else {
 DisplayMode[] displayModes = Display.getAvailableDisplayModes();
 int int2 = 0;
 DisplayMode displayMode1 = nullptr;

 for (auto& displayMode2 : displayModes) if (displayMode2.getWidth() == _width && displayMode2.getHeight() == _height && displayMode2.isFullscreenCapable()) {
 if ((displayMode0.empty() || displayMode2.getFrequency() >= int2)
 && (displayMode0.empty() || displayMode2.getBitsPerPixel() > displayMode0.getBitsPerPixel())) {
 displayMode0 = displayMode2;
 int2 = displayMode2.getFrequency();
 }

 if (displayMode2.getBitsPerPixel() == Display.getDesktopDisplayMode().getBitsPerPixel()
 && displayMode2.getFrequency() == Display.getDesktopDisplayMode().getFrequency()) {
 displayMode0 = displayMode2;
 break;
 }
 }

 if (displayMode2.isFullscreenCapable()
 && (
 displayMode1.empty()
 || Math.abs(displayMode2.getWidth() - _width) < Math.abs(displayMode1.getWidth() - _width)
 || displayMode2.getWidth() == displayMode1.getWidth() && displayMode2.getFrequency() > int2
 )) {
 displayMode1 = displayMode2;
 int2 = displayMode2.getFrequency();
 System.out.println("closest width=" + displayMode2.getWidth() + " freq=" + displayMode2.getFrequency());
 }
 }

 if (displayMode0.empty() && displayMode1 != nullptr) {
 displayMode0 = displayMode1;
 }
 }

 if (displayMode0.empty()) {
 DebugLog.log("Failed to find value mode: " + _width + "x" + _height + " fs=" + fullscreen);
 return;
 }

 Display.setBorderlessWindow(OptionBorderlessWindow);
 if (fullscreen) {
 Display.setDisplayModeAndFullscreen(displayMode0);
 } else {
 Display.setDisplayMode(displayMode0);
 Display.setFullscreen(false);
 }

 if (!fullscreen && OptionBorderlessWindow) {
 Display.setResizable(false);
 } else if (!fullscreen && !fakefullscreen) {
 Display.setResizable(false);
 Display.setResizable(true);
 }

 if (Display.isCreated()) {
 DebugLog.log(
 "Display mode changed to "
 + Display.getWidth()
 + "x"
 + Display.getHeight()
 + " freq="
 + Display.getDisplayMode().getFrequency()
 + " fullScreen="
 + Display.isFullscreen()
 );
 }
 } catch (LWJGLException lWJGLException) {
 DebugLog.log("Unable to setup mode " + _width + "x" + _height + " fullscreen=" + fullscreen + lWJGLException);
 }
 }
 }
 );
 }

 bool isFunctionKey(int int0) {
 return int0 >= 59 && int0 <= 68 || int0 >= 87 && int0 <= 105 || int0 == 113;
 }

 bool isDoingTextEntry() {
 if (CurrentTextEntryBox.empty()) {
 return false;
 } else {
 return !CurrentTextEntryBox.IsEditable ? false : CurrentTextEntryBox.DoingTextEntry;
 }
 }

 void updateKeyboardAux(UITextBox2 uITextBox2, int int0) {
 bool boolean0 = Keyboard.isKeyDown(29) || Keyboard.isKeyDown(157);
 bool boolean1 = Keyboard.isKeyDown(42) || Keyboard.isKeyDown(54);
 if (int0 == 28 || int0 == 156) {
 bool boolean2 = false;
 if (UIManager.getDebugConsole() != nullptr && uITextBox2 == UIManager.getDebugConsole().CommandLine) {
 boolean2 = true;
 }

 if (uITextBox2.multipleLine) {
 if (uITextBox2.Lines.size() < uITextBox2.getMaxLines()) {
 if (uITextBox2.TextEntryCursorPos != uITextBox2.ToSelectionIndex) {
 int int1 = Math.min(uITextBox2.TextEntryCursorPos, uITextBox2.ToSelectionIndex);
 int int2 = Math.max(uITextBox2.TextEntryCursorPos, uITextBox2.ToSelectionIndex);
 if (uITextBox2.internalText.length() > 0) {
 uITextBox2.internalText = uITextBox2.internalText.substring(0, int1) + "\n" + uITextBox2.internalText.substring(int2);
 } else {
 uITextBox2.internalText = "\n";
 }

 uITextBox2.TextEntryCursorPos = int1 + 1;
 } else {
 int int3 = uITextBox2.TextEntryCursorPos;
 std::string string0 = uITextBox2.internalText.substring(0, int3) + "\n" + uITextBox2.internalText.substring(int3);
 uITextBox2.SetText(string0);
 uITextBox2.TextEntryCursorPos = int3 + 1;
 }

 uITextBox2.ToSelectionIndex = uITextBox2.TextEntryCursorPos;
 uITextBox2.CursorLine = uITextBox2.toDisplayLine(uITextBox2.TextEntryCursorPos);
 }
 } else {
 uITextBox2.onCommandEntered();
 }

 if (boolean2
 && (!GameClient.bClient || GameClient.connection.accessLevel != 1 || GameClient.connection != nullptr && GameClient.connection.isCoopHost) {
 UIManager.getDebugConsole().ProcessCommand();
 }
 } else if (int0 == 1) {
 uITextBox2.onOtherKey(1);
 GameKeyboard.eatKeyPress(1);
 } else if (int0 == 15) {
 uITextBox2.onOtherKey(15);
 LuaEventManager.triggerEvent("SwitchChatStream");
 } else if (int0 != 58) {
 if (int0 == 199) {
 uITextBox2.TextEntryCursorPos = 0;
 if (!uITextBox2.Lines.empty()) {
 uITextBox2.TextEntryCursorPos = uITextBox2.TextOffsetOfLineStart.get(uITextBox2.CursorLine);
 }

 if (!boolean1) {
 uITextBox2.ToSelectionIndex = uITextBox2.TextEntryCursorPos;
 }

 uITextBox2.resetBlink();
 } else if (int0 == 207) {
 uITextBox2.TextEntryCursorPos = uITextBox2.internalText.length();
 if (!uITextBox2.Lines.empty()) {
 uITextBox2.TextEntryCursorPos = uITextBox2.TextOffsetOfLineStart.get(uITextBox2.CursorLine)
 + uITextBox2.Lines.get(uITextBox2.CursorLine).length();
 }

 if (!boolean1) {
 uITextBox2.ToSelectionIndex = uITextBox2.TextEntryCursorPos;
 }

 uITextBox2.resetBlink();
 } else if (int0 == 200) {
 if (uITextBox2.CursorLine > 0) {
 int int4 = uITextBox2.TextEntryCursorPos - uITextBox2.TextOffsetOfLineStart.get(uITextBox2.CursorLine);
 uITextBox2.CursorLine--;
 if (int4 > uITextBox2.Lines.get(uITextBox2.CursorLine).length()) {
 int4 = uITextBox2.Lines.get(uITextBox2.CursorLine).length();
 }

 uITextBox2.TextEntryCursorPos = uITextBox2.TextOffsetOfLineStart.get(uITextBox2.CursorLine) + int4;
 if (!boolean1) {
 uITextBox2.ToSelectionIndex = uITextBox2.TextEntryCursorPos;
 }
 }

 uITextBox2.onPressUp();
 } else if (int0 == 208) {
 if (uITextBox2.Lines.size() - 1 > uITextBox2.CursorLine && uITextBox2.CursorLine + 1 < uITextBox2.getMaxLines()) {
 int int5 = uITextBox2.TextEntryCursorPos - uITextBox2.TextOffsetOfLineStart.get(uITextBox2.CursorLine);
 uITextBox2.CursorLine++;
 if (int5 > uITextBox2.Lines.get(uITextBox2.CursorLine).length()) {
 int5 = uITextBox2.Lines.get(uITextBox2.CursorLine).length();
 }

 uITextBox2.TextEntryCursorPos = uITextBox2.TextOffsetOfLineStart.get(uITextBox2.CursorLine) + int5;
 if (!boolean1) {
 uITextBox2.ToSelectionIndex = uITextBox2.TextEntryCursorPos;
 }
 }

 uITextBox2.onPressDown();
 } else if (int0 != 29) {
 if (int0 != 157) {
 if (int0 != 42) {
 if (int0 != 54) {
 if (int0 != 56) {
 if (int0 != 184) {
 if (int0 == 203) {
 uITextBox2.TextEntryCursorPos--;
 if (uITextBox2.TextEntryCursorPos < 0) {
 uITextBox2.TextEntryCursorPos = 0;
 }

 if (!boolean1) {
 uITextBox2.ToSelectionIndex = uITextBox2.TextEntryCursorPos;
 }

 uITextBox2.resetBlink();
 } else if (int0 == 205) {
 uITextBox2.TextEntryCursorPos++;
 if (uITextBox2.TextEntryCursorPos > uITextBox2.internalText.length()) {
 uITextBox2.TextEntryCursorPos = uITextBox2.internalText.length();
 }

 if (!boolean1) {
 uITextBox2.ToSelectionIndex = uITextBox2.TextEntryCursorPos;
 }

 uITextBox2.resetBlink();
 } else if (!this->isFunctionKey(int0) {
 if ((int0 == 211 || int0 == 14) && uITextBox2.TextEntryCursorPos != uITextBox2.ToSelectionIndex) {
 int int6 = Math.min(uITextBox2.TextEntryCursorPos, uITextBox2.ToSelectionIndex);
 int int7 = Math.max(uITextBox2.TextEntryCursorPos, uITextBox2.ToSelectionIndex);
 uITextBox2.internalText = uITextBox2.internalText.substring(0, int6) + uITextBox2.internalText.substring(int7);
 uITextBox2.CursorLine = uITextBox2.toDisplayLine(int6);
 uITextBox2.ToSelectionIndex = int6;
 uITextBox2.TextEntryCursorPos = int6;
 uITextBox2.onTextChange();
 } else if (int0 == 211) {
 if (uITextBox2.internalText.length() != 0 && uITextBox2.TextEntryCursorPos < uITextBox2.internalText.length()) {
 if (uITextBox2.TextEntryCursorPos > 0) {
 uITextBox2.internalText = uITextBox2.internalText.substring(0, uITextBox2.TextEntryCursorPos)
 + uITextBox2.internalText.substring(uITextBox2.TextEntryCursorPos + 1);
 } else {
 uITextBox2.internalText = uITextBox2.internalText.substring(1);
 }

 uITextBox2.onTextChange();
 }
 } else if (int0 == 14) {
 if (uITextBox2.internalText.length() != 0 && uITextBox2.TextEntryCursorPos > 0) {
 if (uITextBox2.TextEntryCursorPos > uITextBox2.internalText.length()) {
 uITextBox2.internalText = uITextBox2.internalText.substring(0, uITextBox2.internalText.length() - 1);
 } else {
 int int8 = uITextBox2.TextEntryCursorPos;
 uITextBox2.internalText = uITextBox2.internalText.substring(0, int8 - 1)
 + uITextBox2.internalText.substring(int8);
 }

 uITextBox2.TextEntryCursorPos--;
 uITextBox2.ToSelectionIndex = uITextBox2.TextEntryCursorPos;
 uITextBox2.onTextChange();
 }
 } else if (boolean0 && int0 == 47) {
 std::string string1 = Clipboard.getClipboard();
 if (string1 != nullptr) {
 if (uITextBox2.TextEntryCursorPos != uITextBox2.ToSelectionIndex) {
 int int9 = Math.min(uITextBox2.TextEntryCursorPos, uITextBox2.ToSelectionIndex);
 int int10 = Math.max(uITextBox2.TextEntryCursorPos, uITextBox2.ToSelectionIndex);
 uITextBox2.internalText = uITextBox2.internalText.substring(0, int9)
 + string1
 + uITextBox2.internalText.substring(int10);
 uITextBox2.ToSelectionIndex = int9 + string1.length();
 uITextBox2.TextEntryCursorPos = int9 + string1.length();
 } else {
 if (uITextBox2.TextEntryCursorPos < uITextBox2.internalText.length()) {
 uITextBox2.internalText = uITextBox2.internalText.substring(0, uITextBox2.TextEntryCursorPos)
 + string1
 + uITextBox2.internalText.substring(uITextBox2.TextEntryCursorPos);
 } else {
 uITextBox2.internalText = uITextBox2.internalText + string1;
 }

 uITextBox2.TextEntryCursorPos = uITextBox2.TextEntryCursorPos + string1.length();
 uITextBox2.ToSelectionIndex = uITextBox2.ToSelectionIndex + string1.length();
 }

 uITextBox2.onTextChange();
 }
 } else if (boolean0 && int0 == 46) {
 if (uITextBox2.TextEntryCursorPos != uITextBox2.ToSelectionIndex) {
 uITextBox2.updateText();
 int int11 = Math.min(uITextBox2.TextEntryCursorPos, uITextBox2.ToSelectionIndex);
 int int12 = Math.max(uITextBox2.TextEntryCursorPos, uITextBox2.ToSelectionIndex);
 std::string string2 = uITextBox2.Text.substring(int11, int12);
 if (string2 != nullptr && string2.length() > 0) {
 Clipboard.setClipboard(string2);
 }
 }
 } else if (boolean0 && int0 == 45) {
 if (uITextBox2.TextEntryCursorPos != uITextBox2.ToSelectionIndex) {
 uITextBox2.updateText();
 int int13 = Math.min(uITextBox2.TextEntryCursorPos, uITextBox2.ToSelectionIndex);
 int int14 = Math.max(uITextBox2.TextEntryCursorPos, uITextBox2.ToSelectionIndex);
 std::string string3 = uITextBox2.Text.substring(int13, int14);
 if (string3 != nullptr && string3.length() > 0) {
 Clipboard.setClipboard(string3);
 }

 uITextBox2.internalText = uITextBox2.internalText.substring(0, int13)
 + uITextBox2.internalText.substring(int14);
 uITextBox2.ToSelectionIndex = int13;
 uITextBox2.TextEntryCursorPos = int13;
 }
 } else if (boolean0 && int0 == 30) {
 uITextBox2.selectAll();
 } else if (!uITextBox2.ignoreFirst) {
 if (uITextBox2.internalText.length() < uITextBox2.TextEntryMaxLength) {
 char char0 = Keyboard.getEventCharacter();
 if (char0 != 0) {
 if (uITextBox2.isOnlyNumbers() && char0 != '.' && char0 != '-') {
 try {
 Double.parseDouble(String.valueOf(char0);
 } catch (Exception exception) {
 return;
 }
 }

 if (uITextBox2.TextEntryCursorPos == uITextBox2.ToSelectionIndex) {
 int int15 = uITextBox2.TextEntryCursorPos;
 if (int15 < uITextBox2.internalText.length()) {
 uITextBox2.internalText = uITextBox2.internalText.substring(0, int15)
 + char0
 + uITextBox2.internalText.substring(int15);
 } else {
 uITextBox2.internalText = uITextBox2.internalText + char0;
 }

 uITextBox2.TextEntryCursorPos++;
 uITextBox2.ToSelectionIndex++;
 uITextBox2.onTextChange();
 } else {
 int int16 = Math.min(uITextBox2.TextEntryCursorPos, uITextBox2.ToSelectionIndex);
 int int17 = Math.max(uITextBox2.TextEntryCursorPos, uITextBox2.ToSelectionIndex);
 if (uITextBox2.internalText.length() > 0) {
 uITextBox2.internalText = uITextBox2.internalText.substring(0, int16)
 + char0
 + uITextBox2.internalText.substring(int17);
 } else {
 uITextBox2.internalText = char0 + "";
 }

 uITextBox2.ToSelectionIndex = int16 + 1;
 uITextBox2.TextEntryCursorPos = int16 + 1;
 uITextBox2.onTextChange();
 }
 }
 }
 }
 }
 }
 }
 }
 }
 }
 }
 }
 }

 void updateKeyboard() {
 if (this->isDoingTextEntry()) {
 while (Keyboard.next()) {
 if (this->isDoingTextEntry() && Keyboard.getEventKeyState()) {
 int int0 = Keyboard.getEventKey();
 this->updateKeyboardAux(CurrentTextEntryBox, int0);
 }
 }

 if (CurrentTextEntryBox != nullptr && CurrentTextEntryBox.ignoreFirst) {
 CurrentTextEntryBox.ignoreFirst = false;
 }
 }
 }

 void quit() {
 DebugLog.log("EXITDEBUG: Core.quit 1");
 if (IsoPlayer.getInstance() != nullptr) {
 DebugLog.log("EXITDEBUG: Core.quit 2");
 bExiting = true;
 } else {
 DebugLog.log("EXITDEBUG: Core.quit 3");

 try {
 this->saveOptions();
 } catch (IOException iOException) {
 iOException.printStackTrace();
 }

 GameClient.instance.Shutdown();
 SteamUtils.shutdown();
 DebugLog.log("EXITDEBUG: Core.quit 4");
 System.exit(0);
 }
 }

 void exitToMenu() {
 DebugLog.log("EXITDEBUG: Core.exitToMenu");
 bExiting = true;
 }

 void quitToDesktop() {
 DebugLog.log("EXITDEBUG: Core.quitToDesktop");
 GameWindow.closeRequested = true;
 }

 bool supportRes(int _width, int _height) {
 DisplayMode[] displayModes = Display.getAvailableDisplayModes();
 bool boolean0 = false;

 for (int int0 = 0; int0 < displayModes.length; int0++) {
 if (displayModes[int0].getWidth() == _width && displayModes[int0].getHeight() == _height && displayModes[int0].isFullscreenCapable()) {
 return true;
 }
 }

 return false;
 }

 void init(int _width, int _height) {
 System.setProperty("org.lwjgl.opengl.Window.undecorated", OptionBorderlessWindow ? "true" : "false");
 if (!System.getProperty("os.name").contains("OS X") && !System.getProperty("os.name").startsWith("Win")) {
 DebugLog.log("Creating display. If this fails, you may need to install xrandr.");
 }

 setDisplayMode(_width, _height, fullScreen);

 try {
 Display.create(new PixelFormat(32, 0, 24, 8, 0);
 } catch (LWJGLException lWJGLException) {
 Display.destroy();
 Display.setDisplayModeAndFullscreen(Display.getDesktopDisplayMode());
 Display.create(new PixelFormat(32, 0, 24, 8, 0);
 }

 fullScreen = Display.isFullscreen();
 DebugLog.log("GraphicsCard: " + GL11.glGetString(7936) + " " + GL11.glGetString(7937);
 DebugLog.log("OpenGL version: " + GL11.glGetString(7938);
 DebugLog.log("Desktop resolution " + Display.getDesktopDisplayMode().getWidth() + "x" + Display.getDesktopDisplayMode().getHeight());
 DebugLog.log("Initial resolution " + width + "x" + height + " fullScreen=" + fullScreen);
 GLVertexBufferObject.init();
 DebugLog.General.println("VSync: %s", OptionVSync ? "ON" : "OFF");
 Display.setVSyncEnabled(OptionVSync);
 GL11.glEnable(3553);
 IndieGL.glBlendFunc(770, 771);
 GL32.glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
 }

 bool setupMultiFBO() {
 try {
 if (!this->OffscreenBuffer.test()) {
 return false;
 } else {
 this->OffscreenBuffer.setZoomLevelsFromOption(TileScale == 2 ? OptionZoomLevels2x : OptionZoomLevels1x);
 this->OffscreenBuffer.create(Display.getWidth(), Display.getHeight());
 return true;
 }
 } catch (Exception exception) {
 exception.printStackTrace();
 return false;
 }
 }

 void setScreenSize(int _width, int _height) {
 if (width != _width || _height != height) {
 int int0 = width;
 int int1 = height;
 DebugLog.log("Screen resolution changed from " + int0 + "x" + int1 + " to " + _width + "x" + _height + " fullScreen=" + fullScreen);
 width = _width;
 height = _height;
 if (this->OffscreenBuffer != nullptr && this->OffscreenBuffer.Current != nullptr) {
 this->OffscreenBuffer.destroy();

 try {
 this->OffscreenBuffer.setZoomLevelsFromOption(TileScale == 2 ? OptionZoomLevels2x : OptionZoomLevels1x);
 this->OffscreenBuffer.create(_width, _height);
 } catch (Exception exception0) {
 exception0.printStackTrace();
 }
 }

 try {
 LuaEventManager.triggerEvent("OnResolutionChange", int0, int1, _width, _height);
 } catch (Exception exception1) {
 exception1.printStackTrace();
 }

 for (int int2 = 0; int2 < IsoPlayer.numPlayers; int2++) {
 IsoPlayer player = IsoPlayer.players[int2];
 if (player != nullptr) {
 player.dirtyRecalcGridStackTime = 2.0F;
 }
 }
 }
 }

 static bool supportCompressedTextures() {
 return GL.getCapabilities().GL_EXT_texture_compression_latc;
 }

 void StartFrame() {
 if (LuaManager.thread.empty() || !LuaManager.thread.bStep) {
 if (this->RenderShader != nullptr && this->OffscreenBuffer.Current != nullptr) {
 this->RenderShader.setTexture(this->OffscreenBuffer.getTexture(0);
 }

 SpriteRenderer.instance.prePopulating();
 UIManager.resize();
 bool boolean0 = false;
 Texture.BindCount = 0;
 if (!boolean0) {
 IndieGL.glClear(18176);
 if (DebugOptions.instance.Terrain.RenderTiles.HighContrastBg.getValue()) {
 SpriteRenderer.instance.glClearColor(255, 0, 255, 255);
 SpriteRenderer.instance.glClear(16384);
 }
 }

 if (this->OffscreenBuffer.Current != nullptr) {
 SpriteRenderer.instance.glBuffer(1, 0);
 }

 IndieGL.glDoStartFrame(this->getScreenWidth(), this->getScreenWidth(), this->getCurrentPlayerZoom(), 0);
 this->frameStage = 1;
 }
 }

 void StartFrame(int nPlayer, bool clear) {
 if (!LuaManager.thread.bStep) {
 this->OffscreenBuffer.update();
 if (this->RenderShader != nullptr && this->OffscreenBuffer.Current != nullptr) {
 this->RenderShader.setTexture(this->OffscreenBuffer.getTexture(nPlayer);
 }

 if (clear) {
 SpriteRenderer.instance.prePopulating();
 }

 if (!clear) {
 SpriteRenderer.instance.initFromIsoCamera(nPlayer);
 }

 Texture.BindCount = 0;
 IndieGL.glLoadIdentity();
 if (this->OffscreenBuffer.Current != nullptr) {
 SpriteRenderer.instance.glBuffer(1, nPlayer);
 }

 IndieGL.glDoStartFrame(this->getScreenWidth(), this->getScreenHeight(), this->getZoom(nPlayer), nPlayer);
 IndieGL.glClear(17664);
 if (DebugOptions.instance.Terrain.RenderTiles.HighContrastBg.getValue()) {
 SpriteRenderer.instance.glClearColor(255, 0, 255, 255);
 SpriteRenderer.instance.glClear(16384);
 }

 this->frameStage = 1;
 }
 }

 TextureFBO getOffscreenBuffer() {
 return this->OffscreenBuffer.getCurrent(0);
 }

 TextureFBO getOffscreenBuffer(int nPlayer) {
 return this->OffscreenBuffer.getCurrent(nPlayer);
 }

 void setLastRenderedFBO(TextureFBO fbo) {
 this->OffscreenBuffer.FBOrendered = fbo;
 }

 void DoStartFrameStuff(int w, int h, float zoom, int player) {
 this->DoStartFrameStuff(w, h, zoom, player, false);
 }

 void DoStartFrameStuff(int w, int h, float zoom, int player, bool isTextFrame) {
 this->DoStartFrameStuffInternal(w, h, zoom, player, isTextFrame, false, false);
 }

 void DoEndFrameStuffFx(int w, int h, int player) {
 GL11.glPopAttrib();
 this->stack--;
 GL11.glMatrixMode(5889);
 GL11.glPopMatrix();
 this->stack--;
 GL11.glMatrixMode(5888);
 GL11.glLoadIdentity();
 }

 void DoStartFrameStuffSmartTextureFx(int w, int h, int player) {
 this->DoStartFrameStuffInternal(w, h, 1.0F, player, false, true, true);
 }

 void DoStartFrameStuffInternal(int int2, int int3, float float0, int int4, bool boolean2, bool boolean0, bool boolean1) {
 GL32.glEnable(3042);
 GL32.glDepthFunc(519);
 int int0 = this->getScreenWidth();
 int int1 = this->getScreenHeight();
 if (!boolean1 && !boolean0) {
 int2 = int0;
 }

 if (!boolean1 && !boolean0) {
 int3 = int1;
 }

 if (!boolean1 && int4 != -1) {
 int2 /= IsoPlayer.numPlayers > 1 ? 2 : 1;
 int3 /= IsoPlayer.numPlayers > 2 ? 2 : 1;
 }

 GL32.glMatrixMode(5889);
 if (!boolean0) {
 while (this->stack > 0) {
 try {
 GL11.glPopMatrix();
 GL11.glPopAttrib();
 this->stack -= 2;
 } catch (OpenGLException openGLException) {
 int int5 = GL11.glGetInteger(2992);

 while (int5-- > 0) {
 GL11.glPopAttrib();
 }

 int int6 = GL11.glGetInteger(2980);

 while (int6-- > 1) {
 GL11.glPopMatrix();
 }

 this->stack = 0;
 }
 }
 }

 GL11.glAlphaFunc(516, 0.0F);
 GL11.glPushAttrib(2048);
 this->stack++;
 GL11.glPushMatrix();
 this->stack++;
 GL11.glLoadIdentity();
 if (!boolean1 && !boolean2) {
 GLU.gluOrtho2D(0.0F, int2 * float0, int3 * float0, 0.0F);
 } else {
 GLU.gluOrtho2D(0.0F, int2, int3, 0.0F);
 }

 GL11.glMatrixMode(5888);
 GL11.glLoadIdentity();
 if (int4 != -1) {
 int int7 = int2;
 int int8 = int3;
 int int9;
 int int10;
 if (boolean2) {
 int9 = int2;
 int10 = int3;
 } else {
 int9 = int0;
 int10 = int1;
 if (IsoPlayer.numPlayers > 1) {
 int9 = int0 / 2;
 }

 if (IsoPlayer.numPlayers > 2) {
 int10 = int1 / 2;
 }
 }

 if (boolean0) {
 int7 = int9;
 int8 = int10;
 }

 float float1 = 0.0F;
 float float2 = int9 * (int4 % 2);
 if (int4 >= 2) {
 float1 += int10;
 }

 if (boolean2) {
 float1 = getInstance().getScreenHeight() - int8 - float1;
 }

 GL11.glViewport((int)float2, (int)float1, int7, int8);
 GL11.glEnable(3089);
 GL11.glScissor((int)float2, (int)float1, int7, int8);
 SpriteRenderer.instance.setRenderingPlayerIndex(int4);
 } else {
 GL11.glViewport(0, 0, int2, int3);
 }
 }

 void DoPushIsoStuff(float ox, float oy, float oz, float useangle, bool vehicle) {
 float float0 = getInstance().FloatParamMap.get(0);
 float float1 = getInstance().FloatParamMap.get(1);
 float float2 = getInstance().FloatParamMap.get(2);
 double double0 = float0;
 double double1 = float1;
 double double2 = float2;
 SpriteRenderState spriteRenderState = SpriteRenderer.instance.getRenderingState();
 int int0 = spriteRenderState.playerIndex;
 PlayerCamera playerCamera = spriteRenderState.playerCamera[int0];
 float float3 = playerCamera.RightClickX;
 float float4 = playerCamera.RightClickY;
 float float5 = playerCamera.getTOffX();
 float float6 = playerCamera.getTOffY();
 float float7 = playerCamera.DeferedX;
 float float8 = playerCamera.DeferedY;
 double0 -= playerCamera.XToIso(-float5 - float3, -float6 - float4, 0.0F);
 double1 -= playerCamera.YToIso(-float5 - float3, -float6 - float4, 0.0F);
 double0 += float7;
 double1 += float8;
 double double3 = playerCamera.OffscreenWidth / 1920.0F;
 double double4 = playerCamera.OffscreenHeight / 1920.0F;
 Matrix4f matrix4f0 = this->tempMatrix4f;
 matrix4f0.setOrtho(-((float)double3) / 2.0F, (float)double3 / 2.0F, -((float)double4) / 2.0F, (float)double4 / 2.0F, -10.0F, 10.0F);
 PZGLUtil.pushAndLoadMatrix(5889, matrix4f0);
 Matrix4f matrix4f1 = this->tempMatrix4f;
 float float9 = (float)(2.0 / Math.sqrt(2048.0);
 matrix4f1.scaling(0.047085002F);
 matrix4f1.scale(TileScale / 2.0F);
 matrix4f1.rotate((float) (Math.PI / 6), 1.0F, 0.0F, 0.0F);
 matrix4f1.rotate((float) (Math.PI * 3.0 / 4.0), 0.0F, 1.0F, 0.0F);
 double double5 = ox - double0;
 double double6 = oy - double1;
 matrix4f1.translate(-((float)double5), (float)(oz - double2) * 2.5F, -((float)double6);
 if (vehicle) {
 matrix4f1.scale(-1.0F, 1.0F, 1.0F);
 } else {
 matrix4f1.scale(-1.5F, 1.5F, 1.5F);
 }

 matrix4f1.rotate(useangle + (float) Math.PI, 0.0F, 1.0F, 0.0F);
 if (!vehicle) {
 matrix4f1.translate(0.0F, -0.48F, 0.0F);
 }

 PZGLUtil.pushAndLoadMatrix(5888, matrix4f1);
 GL11.glDepthRange(0.0, 1.0);
 }

 void DoPushIsoParticleStuff(float ox, float oy, float oz) {
 GL11.glMatrixMode(5889);
 GL11.glPushMatrix();
 float float0 = getInstance().FloatParamMap.get(0);
 float float1 = getInstance().FloatParamMap.get(1);
 float float2 = getInstance().FloatParamMap.get(2);
 GL11.glLoadIdentity();
 double double0 = float0;
 double double1 = float1;
 double double2 = float2;
 double double3 = Math.abs(getInstance().getOffscreenWidth(0) / 1920.0F;
 double double4 = Math.abs(getInstance().getOffscreenHeight(0) / 1080.0F;
 GL11.glLoadIdentity();
 GL11.glOrtho(-double3 / 2.0, double3 / 2.0, -double4 / 2.0, double4 / 2.0, -10.0, 10.0);
 GL11.glMatrixMode(5888);
 GL11.glPushMatrix();
 GL11.glLoadIdentity();
 GL11.glScaled(0.047085002F, 0.047085002F, 0.047085002F);
 GL11.glRotatef(62.65607F, 1.0F, 0.0F, 0.0F);
 GL11.glTranslated(0.0, -2.72F, 0.0);
 GL11.glRotatef(135.0F, 0.0F, 1.0F, 0.0F);
 GL11.glScalef(1.7099999F, 14.193F, 1.7099999F);
 GL11.glScalef(0.59F, 0.59F, 0.59F);
 GL11.glTranslated(-(ox - double0), oz - double2, -(oy - double1);
 GL11.glDepthRange(0.0, 1.0);
 }

 void DoPopIsoStuff() {
 GL11.glEnable(3008);
 GL11.glDepthFunc(519);
 GL11.glDepthMask(false);
 GL11.glMatrixMode(5889);
 GL11.glPopMatrix();
 GL11.glMatrixMode(5888);
 GL11.glPopMatrix();
 }

 void DoEndFrameStuff(int w, int h) {
 try {
 GL11.glPopAttrib();
 this->stack--;
 GL11.glMatrixMode(5889);
 GL11.glPopMatrix();
 this->stack--;
 } catch (Exception exception) {
 int int0 = GL11.glGetInteger(2992);

 while (int0-- > 0) {
 GL11.glPopAttrib();
 }

 GL11.glMatrixMode(5889);
 int int1 = GL11.glGetInteger(2980);

 while (int1-- > 1) {
 GL11.glPopMatrix();
 }

 this->stack = 0;
 }

 GL11.glMatrixMode(5888);
 GL11.glLoadIdentity();
 GL11.glDisable(3089);
 }

 void RenderOffScreenBuffer() {
 if (LuaManager.thread.empty() || !LuaManager.thread.bStep) {
 if (this->OffscreenBuffer.Current != nullptr) {
 IndieGL.disableStencilTest();
 IndieGL.glDoStartFrame(width, height, 1.0F, -1);
 IndieGL.glDisable(3042);
 this->OffscreenBuffer.render();
 IndieGL.glDoEndFrame();
 }
 }
 }

 void StartFrameText(int nPlayer) {
 if (LuaManager.thread.empty() || !LuaManager.thread.bStep) {
 IndieGL.glDoStartFrame(IsoCamera.getScreenWidth(nPlayer), IsoCamera.getScreenHeight(nPlayer), 1.0F, nPlayer, true);
 this->frameStage = 2;
 }
 }

 bool StartFrameUI() {
 if (LuaManager.thread != nullptr && LuaManager.thread.bStep) {
 return false;
 } else {
 bool boolean0 = true;
 if (UIManager.useUIFBO) {
 if (UIManager.defaultthread == LuaManager.debugthread) {
 this->UIRenderThisFrame = true;
 } else {
 this->UIRenderAccumulator = this->UIRenderAccumulator + GameTime.getInstance().getMultiplier() / 1.6F;
 this->UIRenderThisFrame = this->UIRenderAccumulator >= 30.0F / OptionUIRenderFPS;
 }

 if (this->UIRenderThisFrame) {
 SpriteRenderer.instance.startOffscreenUI();
 SpriteRenderer.instance.glBuffer(2, 0);
 } else {
 boolean0 = false;
 }
 }

 IndieGL.glDoStartFrame(width, height, 1.0F, -1);
 IndieGL.glClear(1024);
 UIManager.resize();
 this->frameStage = 3;
 return boolean0;
 }
 }

 public Map<String, Integer> getKeyMaps() {
 return this->keyMaps;
 }

 void setKeyMaps(Integer> _keyMaps) {
 this->keyMaps = _keyMaps;
 }

 void reinitKeyMaps() {
 this->keyMaps = std::make_unique<HashMap<>>();
 }

 int getKey(const std::string& keyName) {
 if (this->keyMaps.empty()) {
 return 0;
 } else {
 return this->keyMaps.get(keyName) != nullptr ? this->keyMaps.get(keyName) : 0;
 }
 }

 void addKeyBinding(const std::string& keyName, int key) {
 if (this->keyMaps.empty()) {
 this->keyMaps = std::make_unique<HashMap<>>();
 }

 this->keyMaps.put(keyName, key);
 }

 static bool isLastStand() {
 return bLastStand;
 }

 std::string getVersion() {
 return gameVersion + ".16";
 }

 GameVersion getGameVersion() {
 return gameVersion;
 }

 std::string getSteamServerVersion() {
 return this->steamServerVersion;
 }

 void DoFrameReady() {
 this->updateKeyboard();
 }

 float getCurrentPlayerZoom() {
 int int0 = IsoCamera.frameState.playerIndex;
 return this->getZoom(int0);
 }

 float getZoom(int playerIndex) {
 return this->OffscreenBuffer != nullptr ? this->OffscreenBuffer.zoom[playerIndex] * (TileScale / 2.0F) : 1.0F;
 }

 float getNextZoom(int playerIndex, int del) {
 return this->OffscreenBuffer != nullptr ? this->OffscreenBuffer.getNextZoom(playerIndex, del) : 1.0F;
 }

 float getMinZoom() {
 return this->OffscreenBuffer != nullptr ? this->OffscreenBuffer.getMinZoom() * (TileScale / 2.0F) : 1.0F;
 }

 float getMaxZoom() {
 return this->OffscreenBuffer != nullptr ? this->OffscreenBuffer.getMaxZoom() * (TileScale / 2.0F) : 1.0F;
 }

 void doZoomScroll(int playerIndex, int del) {
 if (this->OffscreenBuffer != nullptr) {
 this->OffscreenBuffer.doZoomScroll(playerIndex, del);
 }
 }

 std::string getSaveFolder() {
 return this->saveFolder;
 }

 bool getOptionZoom() {
 return OptionZoom;
 }

 void setOptionZoom(bool zoom) {
 OptionZoom = zoom;
 }

 void zoomOptionChanged(bool inGame) {
 if (inGame) {
 RenderThread.invokeOnRenderContext(() -> {
 if (OptionZoom && !SafeModeForced) {
 SafeMode = false;
 this->bSupportsFBO = true;
 this->OffscreenBuffer.bZoomEnabled = true;
 this->supportsFBO();
 } else {
 this->OffscreenBuffer.destroy();
 SafeMode = true;
 this->bSupportsFBO = false;
 this->OffscreenBuffer.bZoomEnabled = false;
 }
 });
 DebugLog.log("SafeMode is " + (SafeMode ? "on" : "off"));
 } else {
 SafeMode = SafeModeForced;
 this->OffscreenBuffer.bZoomEnabled = OptionZoom && !SafeModeForced;
 }
 }

 void zoomLevelsChanged() {
 if (this->OffscreenBuffer.Current != nullptr) {
 RenderThread.invokeOnRenderContext(() -> {
 this->OffscreenBuffer.destroy();
 this->zoomOptionChanged(true);
 });
 }
 }

 bool isZoomEnabled() {
 return this->OffscreenBuffer.bZoomEnabled;
 }

 void initFBOs() {
 if (OptionZoom && !SafeModeForced) {
 RenderThread.invokeOnRenderContext(this::supportsFBO);
 } else {
 SafeMode = true;
 this->OffscreenBuffer.bZoomEnabled = false;
 }

 DebugLog.log("SafeMode is " + (SafeMode ? "on" : "off"));
 }

 bool getAutoZoom(int playerIndex) {
 return bAutoZoom[playerIndex];
 }

 void setAutoZoom(int playerIndex, bool auto) {
 bAutoZoom[playerIndex] = auto;
 if (this->OffscreenBuffer != nullptr) {
 this->OffscreenBuffer.bAutoZoom[playerIndex] = auto;
 }
 }

 bool getOptionVSync() {
 return OptionVSync;
 }

 void setOptionVSync(bool sync) {
 OptionVSync = sync;
 RenderThread.invokeOnRenderContext(() -> Display.setVSyncEnabled(sync);
 }

 int getOptionSoundVolume() {
 return OptionSoundVolume;
 }

 float getRealOptionSoundVolume() {
 return OptionSoundVolume / 10.0F;
 }

 void setOptionSoundVolume(int volume) {
 OptionSoundVolume = Math.max(0, Math.min(10, volume);
 if (SoundManager.instance != nullptr) {
 SoundManager.instance.setSoundVolume(volume / 10.0F);
 }
 }

 int getOptionMusicVolume() {
 return OptionMusicVolume;
 }

 void setOptionMusicVolume(int volume) {
 OptionMusicVolume = Math.max(0, Math.min(10, volume);
 if (SoundManager.instance != nullptr) {
 SoundManager.instance.setMusicVolume(volume / 10.0F);
 }
 }

 int getOptionAmbientVolume() {
 return OptionAmbientVolume;
 }

 void setOptionAmbientVolume(int volume) {
 OptionAmbientVolume = Math.max(0, Math.min(10, volume);
 if (SoundManager.instance != nullptr) {
 SoundManager.instance.setAmbientVolume(volume / 10.0F);
 }
 }

 int getOptionJumpScareVolume() {
 return OptionJumpScareVolume;
 }

 void setOptionJumpScareVolume(int volume) {
 OptionJumpScareVolume = PZMath.clamp(volume, 0, 10);
 }

 int getOptionMusicActionStyle() {
 return OptionMusicActionStyle;
 }

 void setOptionMusicActionStyle(int v) {
 OptionMusicActionStyle = PZMath.clamp(v, 1, 2);
 }

 int getOptionMusicLibrary() {
 return OptionMusicLibrary;
 }

 void setOptionMusicLibrary(int m) {
 if (m < 1) {
 m = 1;
 }

 if (m > 3) {
 m = 3;
 }

 OptionMusicLibrary = m;
 }

 int getOptionVehicleEngineVolume() {
 return OptionVehicleEngineVolume;
 }

 void setOptionVehicleEngineVolume(int volume) {
 OptionVehicleEngineVolume = Math.max(0, Math.min(10, volume);
 if (SoundManager.instance != nullptr) {
 SoundManager.instance.setVehicleEngineVolume(OptionVehicleEngineVolume / 10.0F);
 }
 }

 bool getOptionVoiceEnable() {
 return OptionVoiceEnable;
 }

 void setOptionVoiceEnable(bool option) {
 if (OptionVoiceEnable != option) {
 OptionVoiceEnable = option;
 VoiceManager.instance.VoiceRestartClient(option);
 }
 }

 int getOptionVoiceMode() {
 return OptionVoiceMode;
 }

 void setOptionVoiceMode(int option) {
 OptionVoiceMode = option;
 VoiceManager.instance.setMode(option);
 }

 int getOptionVoiceVADMode() {
 return OptionVoiceVADMode;
 }

 void setOptionVoiceVADMode(int option) {
 OptionVoiceVADMode = option;
 VoiceManager.instance.setVADMode(option);
 }

 int getOptionVoiceAGCMode() {
 return OptionVoiceAGCMode;
 }

 void setOptionVoiceAGCMode(int option) {
 OptionVoiceAGCMode = option;
 VoiceManager.instance.setAGCMode(option);
 }

 int getOptionVoiceVolumeMic() {
 return OptionVoiceVolumeMic;
 }

 void setOptionVoiceVolumeMic(int option) {
 OptionVoiceVolumeMic = option;
 VoiceManager.instance.setVolumeMic(option);
 }

 int getOptionVoiceVolumePlayers() {
 return OptionVoiceVolumePlayers;
 }

 void setOptionVoiceVolumePlayers(int option) {
 OptionVoiceVolumePlayers = option;
 VoiceManager.instance.setVolumePlayers(option);
 }

 std::string getOptionVoiceRecordDeviceName() {
 return OptionVoiceRecordDeviceName;
 }

 void setOptionVoiceRecordDeviceName(const std::string& option) {
 OptionVoiceRecordDeviceName = option;
 VoiceManager.instance.UpdateRecordDevice();
 }

 int getOptionVoiceRecordDevice() {
 if (!SoundDisabled && !VoiceManager.VoipDisabled) {
 int int0 = javafmod.FMOD_System_GetRecordNumDrivers();

 for (int int1 = 0; int1 < int0; int1++) {
 FMOD_DriverInfo fMOD_DriverInfo = new FMOD_DriverInfo();
 javafmod.FMOD_System_GetRecordDriverInfo(int1, fMOD_DriverInfo);
 if (fMOD_DriverInfo.name == OptionVoiceRecordDeviceName) {
 return int1 + 1;
 }
 }

 return 0;
 } else {
 return 0;
 }
 }

 void setOptionVoiceRecordDevice(int option) {
 if (!SoundDisabled && !VoiceManager.VoipDisabled) {
 if (option >= 1) {
 FMOD_DriverInfo fMOD_DriverInfo = new FMOD_DriverInfo();
 javafmod.FMOD_System_GetRecordDriverInfo(option - 1, fMOD_DriverInfo);
 OptionVoiceRecordDeviceName = fMOD_DriverInfo.name;
 VoiceManager.instance.UpdateRecordDevice();
 }
 }
 }

 int getMicVolumeIndicator() {
 return VoiceManager.instance.getMicVolumeIndicator();
 }

 bool getMicVolumeError() {
 return VoiceManager.instance.getMicVolumeError();
 }

 bool getServerVOIPEnable() {
 return VoiceManager.instance.getServerVOIPEnable();
 }

 void setTestingMicrophone(bool testing) {
 VoiceManager.instance.setTestingMicrophone(testing);
 }

 int getOptionReloadDifficulty() {
 return 2;
 }

 void setOptionReloadDifficulty(int d) {
 OptionReloadDifficulty = Math.max(1, Math.min(3, d);
 }

 bool getOptionRackProgress() {
 return OptionRackProgress;
 }

 void setOptionRackProgress(bool b) {
 OptionRackProgress = b;
 }

 int getOptionFontSize() {
 return OptionFontSize;
 }

 void setOptionFontSize(int size) {
 OptionFontSize = PZMath.clamp(size, 1, 5);
 }

 std::string getOptionContextMenuFont() {
 return OptionContextMenuFont;
 }

 void setOptionContextMenuFont(const std::string& font) {
 OptionContextMenuFont = font;
 }

 std::string getOptionInventoryFont() {
 return OptionInventoryFont;
 }

 void setOptionInventoryFont(const std::string& font) {
 OptionInventoryFont = font;
 }

 int getOptionInventoryContainerSize() {
 return OptionInventoryContainerSize;
 }

 void setOptionInventoryContainerSize(int size) {
 OptionInventoryContainerSize = size;
 }

 std::string getOptionTooltipFont() {
 return OptionTooltipFont;
 }

 void setOptionTooltipFont(const std::string& font) {
 OptionTooltipFont = font;
 ObjectTooltip.checkFont();
 }

 std::string getOptionMeasurementFormat() {
 return OptionMeasurementFormat;
 }

 void setOptionMeasurementFormat(const std::string& format) {
 OptionMeasurementFormat = format;
 }

 int getOptionClockFormat() {
 return OptionClockFormat;
 }

 int getOptionClockSize() {
 return OptionClockSize;
 }

 void setOptionClockFormat(int fmt) {
 if (fmt < 1) {
 fmt = 1;
 }

 if (fmt > 2) {
 fmt = 2;
 }

 OptionClockFormat = fmt;
 }

 void setOptionClockSize(int size) {
 if (size < 1) {
 size = 1;
 }

 if (size > 2) {
 size = 2;
 }

 OptionClockSize = size;
 }

 bool getOptionClock24Hour() {
 return OptionClock24Hour;
 }

 void setOptionClock24Hour(bool b24Hour) {
 OptionClock24Hour = b24Hour;
 }

 bool getOptionModsEnabled() {
 return OptionModsEnabled;
 }

 void setOptionModsEnabled(bool enabled) {
 OptionModsEnabled = enabled;
 }

 int getOptionBloodDecals() {
 return OptionBloodDecals;
 }

 void setOptionBloodDecals(int n) {
 if (n < 0) {
 n = 0;
 }

 if (n > 10) {
 n = 10;
 }

 OptionBloodDecals = n;
 }

 bool getOptionBorderlessWindow() {
 return OptionBorderlessWindow;
 }

 void setOptionBorderlessWindow(bool b) {
 OptionBorderlessWindow = b;
 }

 bool getOptionLockCursorToWindow() {
 return OptionLockCursorToWindow;
 }

 void setOptionLockCursorToWindow(bool b) {
 OptionLockCursorToWindow = b;
 }

 bool getOptionTextureCompression() {
 return OptionTextureCompression;
 }

 void setOptionTextureCompression(bool b) {
 OptionTextureCompression = b;
 }

 bool getOptionTexture2x() {
 return OptionTexture2x;
 }

 void setOptionTexture2x(bool b) {
 OptionTexture2x = b;
 }

 int getOptionMaxTextureSize() {
 return OptionMaxTextureSize;
 }

 void setOptionMaxTextureSize(int int0) {
 OptionMaxTextureSize = PZMath.clamp(int0, 1, 4);
 }

 int getOptionMaxVehicleTextureSize() {
 return OptionMaxVehicleTextureSize;
 }

 void setOptionMaxVehicleTextureSize(int int0) {
 OptionMaxVehicleTextureSize = PZMath.clamp(int0, 1, 4);
 }

 int getMaxTextureSizeFromFlags(int int0) {
 if ((int0 & 128) != 0) {
 return this->getMaxTextureSize();
 } else {
 return (int0 & 256) != 0 ? this->getMaxVehicleTextureSize() : 32768;
 }
 }

 int getMaxTextureSizeFromOption(int int0) {
 return switch() {
 case 1 -> 256;
 case 2 -> 512;
 case 3 -> 1024;
 case 4 -> 2048;
 default -> throw IllegalStateException("Unexpected value: " + int0);
 };
 }

 int getMaxTextureSize() {
 return this->getMaxTextureSizeFromOption(OptionMaxTextureSize);
 }

 int getMaxVehicleTextureSize() {
 return this->getMaxTextureSizeFromOption(OptionMaxVehicleTextureSize);
 }

 bool getOptionModelTextureMipmaps() {
 return OptionModelTextureMipmaps;
 }

 void setOptionModelTextureMipmaps(bool b) {
 OptionModelTextureMipmaps = b;
 }

 std::string getOptionZoomLevels1x() {
 return OptionZoomLevels1x;
 }

 void setOptionZoomLevels1x(const std::string& levels) {
 OptionZoomLevels1x = levels.empty() ? "" : levels;
 }

 std::string getOptionZoomLevels2x() {
 return OptionZoomLevels2x;
 }

 void setOptionZoomLevels2x(const std::string& levels) {
 OptionZoomLevels2x = levels.empty() ? "" : levels;
 }

 public ArrayList<Integer> getDefaultZoomLevels() {
 return this->OffscreenBuffer.getDefaultZoomLevels();
 }

 void setOptionActiveController(int controllerIndex, bool active) {
 if (controllerIndex >= 0 && controllerIndex < GameWindow.GameInput.getControllerCount()) {
 Controller controller = GameWindow.GameInput.getController(controllerIndex);
 if (controller != nullptr) {
 JoypadManager.instance.setControllerActive(controller.getGUID(), active);
 }
 }
 }

 bool getOptionActiveController(const std::string& guid) {
 return JoypadManager.instance.ActiveControllerGUIDs.contains(guid);
 }

 bool isOptionShowChatTimestamp() {
 return OptionShowChatTimestamp;
 }

 void setOptionShowChatTimestamp(bool optionShowChatTimestamp) {
 OptionShowChatTimestamp = optionShowChatTimestamp;
 }

 bool isOptionShowChatTitle() {
 return OptionShowChatTitle;
 }

 std::string getOptionChatFontSize() {
 return OptionChatFontSize;
 }

 void setOptionChatFontSize(const std::string& optionChatFontSize) {
 OptionChatFontSize = optionChatFontSize;
 }

 void setOptionShowChatTitle(bool optionShowChatTitle) {
 OptionShowChatTitle = optionShowChatTitle;
 }

 float getOptionMinChatOpaque() {
 return OptionMinChatOpaque;
 }

 void setOptionMinChatOpaque(float optionMinChatOpaque) {
 OptionMinChatOpaque = optionMinChatOpaque;
 }

 float getOptionMaxChatOpaque() {
 return OptionMaxChatOpaque;
 }

 void setOptionMaxChatOpaque(float optionMaxChatOpaque) {
 OptionMaxChatOpaque = optionMaxChatOpaque;
 }

 float getOptionChatFadeTime() {
 return OptionChatFadeTime;
 }

 void setOptionChatFadeTime(float optionChatFadeTime) {
 OptionChatFadeTime = optionChatFadeTime;
 }

 bool getOptionChatOpaqueOnFocus() {
 return OptionChatOpaqueOnFocus;
 }

 void setOptionChatOpaqueOnFocus(bool optionChatOpaqueOnFocus) {
 OptionChatOpaqueOnFocus = optionChatOpaqueOnFocus;
 }

 bool getOptionUIFBO() {
 return OptionUIFBO;
 }

 void setOptionUIFBO(bool use) {
 OptionUIFBO = use;
 if (GameWindow.states.current == IngameState.instance) {
 UIManager.useUIFBO = getInstance().supportsFBO() && OptionUIFBO;
 }
 }

 int getOptionAimOutline() {
 return OptionAimOutline;
 }

 void setOptionAimOutline(int choice) {
 OptionAimOutline = PZMath.clamp(choice, 1, 3);
 }

 int getOptionUIRenderFPS() {
 return OptionUIRenderFPS;
 }

 void setOptionUIRenderFPS(int fps) {
 OptionUIRenderFPS = fps;
 }

 void setOptionRadialMenuKeyToggle(bool toggle) {
 OptionRadialMenuKeyToggle = toggle;
 }

 bool getOptionRadialMenuKeyToggle() {
 return OptionRadialMenuKeyToggle;
 }

 void setOptionReloadRadialInstant(bool enable) {
 OptionReloadRadialInstant = enable;
 }

 bool getOptionReloadRadialInstant() {
 return OptionReloadRadialInstant;
 }

 void setOptionPanCameraWhileAiming(bool enable) {
 OptionPanCameraWhileAiming = enable;
 }

 bool getOptionPanCameraWhileAiming() {
 return OptionPanCameraWhileAiming;
 }

 void setOptionPanCameraWhileDriving(bool enable) {
 OptionPanCameraWhileDriving = enable;
 }

 bool getOptionPanCameraWhileDriving() {
 return OptionPanCameraWhileDriving;
 }

 std::string getOptionCycleContainerKey() {
 return OptionCycleContainerKey;
 }

 void setOptionCycleContainerKey(const std::string& s) {
 OptionCycleContainerKey = s;
 }

 bool getOptionDropItemsOnSquareCenter() {
 return OptionDropItemsOnSquareCenter;
 }

 void setOptionDropItemsOnSquareCenter(bool b) {
 OptionDropItemsOnSquareCenter = b;
 }

 bool getOptionTimedActionGameSpeedReset() {
 return OptionTimedActionGameSpeedReset;
 }

 void setOptionTimedActionGameSpeedReset(bool b) {
 OptionTimedActionGameSpeedReset = b;
 }

 int getOptionShoulderButtonContainerSwitch() {
 return OptionShoulderButtonContainerSwitch;
 }

 void setOptionShoulderButtonContainerSwitch(int v) {
 OptionShoulderButtonContainerSwitch = v;
 }

 bool getOptionSingleContextMenu(int playerIndex) {
 return OptionSingleContextMenu[playerIndex];
 }

 void setOptionSingleContextMenu(int playerIndex, bool b) {
 OptionSingleContextMenu[playerIndex] = b;
 }

 bool getOptionAutoDrink() {
 return OptionAutoDrink;
 }

 void setOptionAutoDrink(bool enable) {
 OptionAutoDrink = enable;
 }

 bool getOptionAutoWalkContainer() {
 return OptionAutoWalkContainer;
 }

 void setOptionAutoWalkContainer(bool boolean0) {
 OptionAutoWalkContainer = boolean0;
 }

 bool getOptionCorpseShadows() {
 return OptionCorpseShadows;
 }

 void setOptionCorpseShadows(bool enable) {
 OptionCorpseShadows = enable;
 }

 bool getOptionLeaveKeyInIgnition() {
 return OptionLeaveKeyInIgnition;
 }

 void setOptionLeaveKeyInIgnition(bool enable) {
 OptionLeaveKeyInIgnition = enable;
 }

 int getOptionSearchModeOverlayEffect() {
 return OptionSearchModeOverlayEffect;
 }

 void setOptionSearchModeOverlayEffect(int v) {
 OptionSearchModeOverlayEffect = v;
 }

 int getOptionSimpleClothingTextures() {
 return OptionSimpleClothingTextures;
 }

 void setOptionSimpleClothingTextures(int v) {
 OptionSimpleClothingTextures = PZMath.clamp(v, 1, 3);
 }

 bool isOptionSimpleClothingTextures(bool bZombie) {
 switch (OptionSimpleClothingTextures) {
 case 1:
 return false;
 case 2:
 return bZombie;
 default:
 return true;
 }
 }

 bool getOptionSimpleWeaponTextures() {
 return OptionSimpleWeaponTextures;
 }

 void setOptionSimpleWeaponTextures(bool enable) {
 OptionSimpleWeaponTextures = enable;
 }

 int getOptionIgnoreProneZombieRange() {
 return OptionIgnoreProneZombieRange;
 }

 void setOptionIgnoreProneZombieRange(int i) {
 OptionIgnoreProneZombieRange = PZMath.clamp(i, 1, 5);
 }

 float getIgnoreProneZombieRange() {
 switch (OptionIgnoreProneZombieRange) {
 case 1:
 return -1.0F;
 case 2:
 return 1.5F;
 case 3:
 return 2.0F;
 case 4:
 return 2.5F;
 case 5:
 return 3.0F;
 default:
 return -1.0F;
 }
 }

 void readPerPlayerBoolean(const std::string& string, boolean[] booleans) {
 Arrays.fill(booleans, false);
 String[] strings = string.split(",");

 for (int int0 = 0; int0 < strings.length && int0 != 4; int0++) {
 booleans[int0] = StringUtils.tryParseBoolean(strings[int0]);
 }
 }

 std::string getPerPlayerBooleanString(boolean[] booleans) {
 return String.format("%b,%b,%b,%b", booleans[0], booleans[1], booleans[2], booleans[3]);
 }

 void ResetLua(bool sp, const std::string& reason) {
 this->ResetLua("default", reason);
 }

 void ResetLua(const std::string& activeMods, const std::string& reason) {
 if (SpriteRenderer.instance != nullptr) {
 GameWindow.DrawReloadingLua = true;
 GameWindow.render();
 GameWindow.DrawReloadingLua = false;
 }

 RenderThread.setWaitForRenderState(false);
 SpriteRenderer.instance.notifyRenderStateQueue();
 ScriptManager.instance.Reset();
 ClothingDecals.Reset();
 BeardStyles.Reset();
 HairStyles.Reset();
 OutfitManager.Reset();
 AnimationSet.Reset();
 GameSounds.Reset();
 VehicleType.Reset();
 LuaEventManager.Reset();
 MapObjects.Reset();
 UIManager.init();
 SurvivorFactory.Reset();
 ProfessionFactory.Reset();
 TraitFactory.Reset();
 ChooseGameInfo.Reset();
 AttachedLocations.Reset();
 BodyLocations.Reset();
 ContainerOverlays.instance.Reset();
 BentFences.getInstance().Reset();
 BrokenFences.getInstance().Reset();
 TileOverlays.instance.Reset();
 LuaHookManager.Reset();
 CustomPerks.Reset();
 PerkFactory.Reset();
 CustomSandboxOptions.Reset();
 SandboxOptions.Reset();
 WorldMap.Reset();
 LuaManager.init();
 JoypadManager.instance.Reset();
 GameKeyboard.doLuaKeyPressed = true;
 Texture.nullTextures.clear();
 ZomboidFileSystem.instance.Reset();
 ZomboidFileSystem.instance.init();
 ZomboidFileSystem.instance.loadMods(activeMods);
 ZomboidFileSystem.instance.loadModPackFiles();
 Languages.instance.init();
 Translator.loadFiles();
 CustomPerks.instance.init();
 CustomPerks.instance.initLua();
 CustomSandboxOptions.instance.init();
 CustomSandboxOptions.instance.initInstance(SandboxOptions.instance);
 ScriptManager.instance.Load();
 ModelManager.instance.initAnimationMeshes(true);
 ModelManager.instance.loadModAnimations();
 ClothingDecals.init();
 BeardStyles.init();
 HairStyles.init();
 OutfitManager.init();

 try {
 TextManager.instance.Init();
 LuaManager.LoadDirBase();
 } catch (Exception exception) {
 ExceptionLogger.logException(exception);
 GameWindow.DoLoadingText("Reloading Lua - ERRORS!");

 try {
 Thread.sleep(2000L);
 } catch (InterruptedException interruptedException) {
 }
 }

 ZomboidGlobals.Load();
 RenderThread.setWaitForRenderState(true);
 LuaEventManager.triggerEvent("OnGameBoot");
 LuaEventManager.triggerEvent("OnMainMenuEnter");
 LuaEventManager.triggerEvent("OnResetLua", reason);
 }

 void DelayResetLua(const std::string& activeMods, const std::string& reason) {
 this->m_delayResetLua_activeMods = activeMods;
 this->m_delayResetLua_reason = reason;
 }

 void CheckDelayResetLua() {
 if (this->m_delayResetLua_activeMods != nullptr) {
 std::string string0 = this->m_delayResetLua_activeMods;
 std::string string1 = this->m_delayResetLua_reason;
 this->m_delayResetLua_activeMods = nullptr;
 this->m_delayResetLua_reason = nullptr;
 this->ResetLua(string0, string1);
 }
 }

 bool isShowPing() {
 return this->showPing;
 }

 void setShowPing(bool _showPing) {
 this->showPing = _showPing;
 }

 bool isForceSnow() {
 return this->forceSnow;
 }

 void setForceSnow(bool _forceSnow) {
 this->forceSnow = _forceSnow;
 }

 bool isZombieGroupSound() {
 return this->zombieGroupSound;
 }

 void setZombieGroupSound(bool _zombieGroupSound) {
 this->zombieGroupSound = _zombieGroupSound;
 }

 std::string getBlinkingMoodle() {
 return this->blinkingMoodle;
 }

 void setBlinkingMoodle(const std::string& _blinkingMoodle) {
 this->blinkingMoodle = _blinkingMoodle;
 }

 bool isTutorialDone() {
 return this->tutorialDone;
 }

 void setTutorialDone(bool done) {
 this->tutorialDone = done;
 }

 bool isVehiclesWarningShow() {
 return this->vehiclesWarningShow;
 }

 void setVehiclesWarningShow(bool done) {
 this->vehiclesWarningShow = done;
 }

 void initPoisonousBerry() {
 std::vector arrayList = new ArrayList();
 arrayList.add("Base.BerryGeneric1");
 arrayList.add("Base.BerryGeneric2");
 arrayList.add("Base.BerryGeneric3");
 arrayList.add("Base.BerryGeneric4");
 arrayList.add("Base.BerryGeneric5");
 arrayList.add("Base.BerryPoisonIvy");
 this->setPoisonousBerry((String)arrayList.get(Rand.Next(0, arrayList.size() - 1));
 }

 void initPoisonousMushroom() {
 std::vector arrayList = new ArrayList();
 arrayList.add("Base.MushroomGeneric1");
 arrayList.add("Base.MushroomGeneric2");
 arrayList.add("Base.MushroomGeneric3");
 arrayList.add("Base.MushroomGeneric4");
 arrayList.add("Base.MushroomGeneric5");
 arrayList.add("Base.MushroomGeneric6");
 arrayList.add("Base.MushroomGeneric7");
 this->setPoisonousMushroom((String)arrayList.get(Rand.Next(0, arrayList.size() - 1));
 }

 std::string getPoisonousBerry() {
 return this->poisonousBerry;
 }

 void setPoisonousBerry(const std::string& _poisonousBerry) {
 this->poisonousBerry = _poisonousBerry;
 }

 std::string getPoisonousMushroom() {
 return this->poisonousMushroom;
 }

 void setPoisonousMushroom(const std::string& _poisonousMushroom) {
 this->poisonousMushroom = _poisonousMushroom;
 }

 static std::string getDifficulty() {
 return difficulty;
 }

 static void setDifficulty(const std::string& vdifficulty) {
 difficulty = vdifficulty;
 }

 bool isDoneNewSaveFolder() {
 return this->doneNewSaveFolder;
 }

 void setDoneNewSaveFolder(bool _doneNewSaveFolder) {
 this->doneNewSaveFolder = _doneNewSaveFolder;
 }

 static int getTileScale() {
 return TileScale;
 }

 bool isSelectingAll() {
 return this->isSelectingAll;
 }

 void setIsSelectingAll(bool _isSelectingAll) {
 this->isSelectingAll = _isSelectingAll;
 }

 bool getContentTranslationsEnabled() {
 return OptionEnableContentTranslations;
 }

 void setContentTranslationsEnabled(bool b) {
 OptionEnableContentTranslations = b;
 }

 bool isShowYourUsername() {
 return this->showYourUsername;
 }

 void setShowYourUsername(bool _showYourUsername) {
 this->showYourUsername = _showYourUsername;
 }

 ColorInfo getMpTextColor() {
 if (this->mpTextColor.empty()) {
 this->mpTextColor = new ColorInfo((Rand.Next(135) + 120) / 255.0F, (Rand.Next(135) + 120) / 255.0F, (Rand.Next(135) + 120) / 255.0F, 1.0F);
 }

 return this->mpTextColor;
 }

 void setMpTextColor(ColorInfo _mpTextColor) {
 if (_mpTextColor.r < 0.19F) {
 _mpTextColor.r = 0.19F;
 }

 if (_mpTextColor.g < 0.19F) {
 _mpTextColor.g = 0.19F;
 }

 if (_mpTextColor.b < 0.19F) {
 _mpTextColor.b = 0.19F;
 }

 this->mpTextColor = _mpTextColor;
 }

 bool isAzerty() {
 return this->isAzerty;
 }

 void setAzerty(bool _isAzerty) {
 this->isAzerty = _isAzerty;
 }

 ColorInfo getObjectHighlitedColor() {
 return this->objectHighlitedColor;
 }

 void setObjectHighlitedColor(ColorInfo _objectHighlitedColor) {
 this->objectHighlitedColor.set(_objectHighlitedColor);
 }

 ColorInfo getGoodHighlitedColor() {
 return this->goodHighlitedColor;
 }

 void setGoodHighlitedColor(ColorInfo colorInfo) {
 this->goodHighlitedColor.set(colorInfo);
 }

 ColorInfo getBadHighlitedColor() {
 return this->badHighlitedColor;
 }

 void setBadHighlitedColor(ColorInfo colorInfo) {
 this->badHighlitedColor.set(colorInfo);
 }

 std::string getSeenUpdateText() {
 return this->seenUpdateText;
 }

 void setSeenUpdateText(const std::string& _seenUpdateText) {
 this->seenUpdateText = _seenUpdateText;
 }

 bool isToggleToAim() {
 return this->toggleToAim;
 }

 void setToggleToAim(bool enable) {
 this->toggleToAim = enable;
 }

 bool isToggleToRun() {
 return this->toggleToRun;
 }

 void setToggleToRun(bool _toggleToRun) {
 this->toggleToRun = _toggleToRun;
 }

 int getXAngle(int _width, float angle) {
 double double0 = Math.toRadians(225.0F + angle);
 return new Long(Math.round((Math.sqrt(2.0) * Math.cos(double0) + 1.0) * (_width / 2)).intValue();
 }

 int getYAngle(int _width, float angle) {
 double double0 = Math.toRadians(225.0F + angle);
 return new Long(Math.round((Math.sqrt(2.0) * Math.sin(double0) + 1.0) * (_width / 2)).intValue();
 }

 bool isCelsius() {
 return this->celsius;
 }

 void setCelsius(bool _celsius) {
 this->celsius = _celsius;
 }

 bool isInDebug() {
 return bDebug;
 }

 bool isRiversideDone() {
 return this->riversideDone;
 }

 void setRiversideDone(bool _riversideDone) {
 this->riversideDone = _riversideDone;
 }

 bool isNoSave() {
 return this->noSave;
 }

 void setNoSave(bool _noSave) {
 this->noSave = _noSave;
 }

 bool isShowFirstTimeVehicleTutorial() {
 return this->showFirstTimeVehicleTutorial;
 }

 void setShowFirstTimeVehicleTutorial(bool _showFirstTimeVehicleTutorial) {
 this->showFirstTimeVehicleTutorial = _showFirstTimeVehicleTutorial;
 }

 bool getOptionDisplayAsCelsius() {
 return OptionTemperatureDisplayCelsius;
 }

 void setOptionDisplayAsCelsius(bool b) {
 OptionTemperatureDisplayCelsius = b;
 }

 bool isShowFirstTimeWeatherTutorial() {
 return this->showFirstTimeWeatherTutorial;
 }

 void setShowFirstTimeWeatherTutorial(bool _showFirstTimeWeatherTutorial) {
 this->showFirstTimeWeatherTutorial = _showFirstTimeWeatherTutorial;
 }

 bool getOptionDoWindSpriteEffects() {
 return OptionDoWindSpriteEffects;
 }

 void setOptionDoWindSpriteEffects(bool b) {
 OptionDoWindSpriteEffects = b;
 }

 bool getOptionDoDoorSpriteEffects() {
 return OptionDoDoorSpriteEffects;
 }

 void setOptionDoDoorSpriteEffects(bool b) {
 OptionDoDoorSpriteEffects = b;
 }

 bool getOptionDoContainerOutline() {
 return OptionDoContainerOutline;
 }

 void setOptionDoContainerOutline(bool boolean0) {
 OptionDoContainerOutline = boolean0;
 }

 void setOptionUpdateSneakButton(bool b) {
 OptionUpdateSneakButton = b;
 }

 bool getOptionUpdateSneakButton() {
 return OptionUpdateSneakButton;
 }

 bool isNewReloading() {
 return this->newReloading;
 }

 void setNewReloading(bool _newReloading) {
 this->newReloading = _newReloading;
 }

 bool isShowFirstTimeSneakTutorial() {
 return this->showFirstTimeSneakTutorial;
 }

 void setShowFirstTimeSneakTutorial(bool _showFirstTimeSneakTutorial) {
 this->showFirstTimeSneakTutorial = _showFirstTimeSneakTutorial;
 }

 bool isShowFirstTimeSearchTutorial() {
 return this->showFirstTimeSearchTutorial;
 }

 void setShowFirstTimeSearchTutorial(bool _showFirstTimeSearchTutorial) {
 this->showFirstTimeSearchTutorial = _showFirstTimeSearchTutorial;
 }

 int getTermsOfServiceVersion() {
 return this->termsOfServiceVersion;
 }

 void setTermsOfServiceVersion(int int0) {
 this->termsOfServiceVersion = int0;
 }

 void setOptiondblTapJogToSprint(bool dbltap) {
 OptiondblTapJogToSprint = dbltap;
 }

 bool isOptiondblTapJogToSprint() {
 return OptiondblTapJogToSprint;
 }

 bool isToggleToSprint() {
 return this->toggleToSprint;
 }

 void setToggleToSprint(bool _toggleToSprint) {
 this->toggleToSprint = _toggleToSprint;
 }

 int getIsoCursorVisibility() {
 return this->isoCursorVisibility;
 }

 void setIsoCursorVisibility(int _isoCursorVisibility) {
 this->isoCursorVisibility = _isoCursorVisibility;
 }

 bool getOptionShowCursorWhileAiming() {
 return OptionShowCursorWhileAiming;
 }

 void setOptionShowCursorWhileAiming(bool show) {
 OptionShowCursorWhileAiming = show;
 }

 bool gotNewBelt() {
 return this->gotNewBelt;
 }

 void setGotNewBelt(bool gotit) {
 this->gotNewBelt = gotit;
 }

 void setAnimPopupDone(bool done) {
 this->bAnimPopupDone = done;
 }

 bool isAnimPopupDone() {
 return this->bAnimPopupDone;
 }

 void setModsPopupDone(bool done) {
 this->bModsPopupDone = done;
 }

 bool isModsPopupDone() {
 return this->bModsPopupDone;
 }

 bool isRenderPrecipIndoors() {
 return OptionRenderPrecipIndoors;
 }

 void setRenderPrecipIndoors(bool optionRenderPrecipIndoors) {
 OptionRenderPrecipIndoors = optionRenderPrecipIndoors;
 }

 bool isCollideZombies() {
 return this->collideZombies;
 }

 void setCollideZombies(bool _collideZombies) {
 this->collideZombies = _collideZombies;
 }

 bool isFlashIsoCursor() {
 return this->flashIsoCursor;
 }

 void setFlashIsoCursor(bool _flashIsoCursor) {
 this->flashIsoCursor = _flashIsoCursor;
 }

 bool isOptionProgressBar() {
 return true;
 }

 void setOptionProgressBar(bool optionProgressBar) {
 OptionProgressBar = optionProgressBar;
 }

 void setOptionLanguageName(const std::string& name) {
 OptionLanguageName = name;
 }

 std::string getOptionLanguageName() {
 return OptionLanguageName;
 }

 int getOptionRenderPrecipitation() {
 return OptionRenderPrecipitation;
 }

 void setOptionRenderPrecipitation(int optionRenderPrecipitation) {
 OptionRenderPrecipitation = optionRenderPrecipitation;
 }

 void setOptionAutoProneAtk(bool optionAutoProneAtk) {
 OptionAutoProneAtk = optionAutoProneAtk;
 }

 bool isOptionAutoProneAtk() {
 return OptionAutoProneAtk;
 }

 void setOption3DGroundItem(bool option3Dgrounditem) {
 Option3DGroundItem = option3Dgrounditem;
 }

 bool isOption3DGroundItem() {
 return Option3DGroundItem;
 }

 void* getOptionOnStartup(const std::string& name) {
 return optionsOnStartup.get(name);
 }

 void setOptionOnStartup(const std::string& name, void* value) {
 optionsOnStartup.put(name, value);
 }

 void countMissing3DItems() {
 std::vector arrayList = ScriptManager.instance.getAllItems();
 int int0 = 0;

 for (auto& item : arrayList) if (item.type != Item.Type.Weapon
 && item.type != Item.Type.Moveable
 && !item.name.contains("ZedDmg")
 && !item.name.contains("Wound")
 && !item.name.contains("MakeUp")
 && !item.name.contains("Bandage")
 && !item.name.contains("Hat")
 && !item.getObsolete()
 && StringUtils.isNullOrEmpty(item.worldObjectSprite)
 && StringUtils.isNullOrEmpty(item.worldStaticModel) {
 System.out.println("Missing: " + item.name);
 int0++;
 }
 }

 System.out.println("total missing: " + int0 + "/" + arrayList.size());
 }

 bool getOptionShowItemModInfo() {
 return OptionShowItemModInfo;
 }

 void setOptionShowItemModInfo(bool b) {
 OptionShowItemModInfo = b;
 }

 bool getOptionShowSurvivalGuide() {
 return this->OptionShowSurvivalGuide;
 }

 void setOptionShowSurvivalGuide(bool b) {
 this->OptionShowSurvivalGuide = b;
 }

 bool getOptionEnableLeftJoystickRadialMenu() {
 return OptionEnableLeftJoystickRadialMenu;
 }

 void setOptionEnableLeftJoystickRadialMenu(bool b) {
 OptionEnableLeftJoystickRadialMenu = b;
 }

 std::string getVersionNumber() {
 return gameVersion.toString();
 }
}
} // namespace core
} // namespace zombie
