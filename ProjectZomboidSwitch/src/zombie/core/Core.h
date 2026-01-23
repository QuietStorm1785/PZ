#pragma once
#include <queue>
#include <stack>
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
#include "GraphicsWrapper/GraphicsExceptions.h"
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
#include "zombie/scripting/objects/Item/Type.h"
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


class Core {
public:
    static const bool bDemo = false;
    static bool bTutorial;
    static bool fakefullscreen = false;
    static const GameVersion gameVersion = std::make_shared<GameVersion>(41, 78, "");
    static const int buildVersion = 16;
    std::string steamServerVersion = "1.0.0.0";
    static bool bAltMoveMethod = false;
    bool rosewoodSpawnDone = false;
    const ColorInfo objectHighlitedColor = std::make_shared<ColorInfo>(0.98F, 0.56F, 0.11F, 1.0F);
    const ColorInfo goodHighlitedColor = std::make_shared<ColorInfo>(0.0F, 1.0F, 0.0F, 1.0F);
    const ColorInfo badHighlitedColor = std::make_shared<ColorInfo>(1.0F, 0.0F, 0.0F, 1.0F);
    bool flashIsoCursor = false;
    int isoCursorVisibility = 5;
    static bool OptionShowCursorWhileAiming = false;
    bool collideZombies = true;
    const MultiTextureFBO2 OffscreenBuffer = std::make_shared<MultiTextureFBO2>();
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
   private static const boolean[] OptionSingleContextMenu = new boolean[4];
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
   private static const std::unordered_map<std::string, Object> optionsOnStartup = std::make_unique<std::unordered_map<>>();
    bool bChallenge;
    static int width = 1280;
    static int height = 720;
    static int MaxJukeBoxesActive = 10;
    static int NumJukeBoxesActive = 0;
    static std::string GameMode = "Sandbox";
    static std::string glVersion;
    static int glMajorVersion = -1;
    static const Core core = std::make_shared<Core>();
    static bool bDebug = false;
    static UITextBox2 CurrentTextEntryBox = nullptr;
    Shader RenderShader;
   private Map<std::string, int> keyMaps = nullptr;
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
   private static const boolean[] bAutoZoom = new boolean[4];
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
   public const std::unordered_map<int, float> FloatParamMap = std::make_unique<std::unordered_map<>>();
    const Matrix4f tempMatrix4f = std::make_shared<Matrix4f>();
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

    void setChallenge(bool var1) {
      this.bChallenge = var1;
   }

    bool isChallenge() {
      return this.bChallenge;
   }

    std::string getChallengeID() {
    return ChallengeID;
   }

    bool getOptionTieredZombieUpdates() {
      return MovingObjectUpdateScheduler.instance.isEnabled();
   }

    void setOptionTieredZombieUpdates(bool var1) {
      MovingObjectUpdateScheduler.instance.setEnabled(var1);
   }

    void setFramerate(int var1) {
      PerformanceSettings.setUncappedFPS(var1 == 1);
      switch (var1) {
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

    void setMultiThread(bool var1) {
   }

    bool loadedShader() {
      return this.RenderShader != nullptr;
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
      return this.iPerfSkybox_new;
   }

    int getPerfSkyboxOnLoad() {
      return this.iPerfSkybox;
   }

    void setPerfSkybox(int var1) {
      this.iPerfSkybox_new = var1;
   }

    bool getPerfReflections() {
      return this.bPerfReflections_new;
   }

    bool getPerfReflectionsOnLoad() {
      return this.bPerfReflections;
   }

    void setPerfReflections(bool var1) {
      this.bPerfReflections_new = var1;
   }

    int getPerfPuddles() {
      return this.iPerfPuddles_new;
   }

    int getPerfPuddlesOnLoad() {
      return this.iPerfPuddles;
   }

    void setPerfPuddles(int var1) {
      this.iPerfPuddles_new = var1;
   }

    int getVidMem() {
      return SafeMode ? 5 : this.vidMem;
   }

    void setVidMem(int var1) {
      if (SafeMode) {
         this.vidMem = 5;
      }

      this.vidMem = var1;

      try {
         this.saveOptions();
      } catch (IOException var3) {
         var3.printStackTrace();
      }
   }

    void setUseShaders(bool var1) {
   }

    void shadersOptionChanged() {
      RenderThread.invokeOnRenderContext(() -> {
         if (!SafeModeForced) {
            try {
               if (this.RenderShader == nullptr) {
                  this.RenderShader = std::make_shared<WeatherShader>("screen");
               }

               if (this.RenderShader != nullptr && !this.RenderShader.isCompiled()) {
                  this.RenderShader = nullptr;
               }
            } catch (Exception var3) {
               this.RenderShader = nullptr;
            }
         } else if (this.RenderShader != nullptr) {
            try {
               this.RenderShader.destroy();
            } catch (Exception var2) {
               var2.printStackTrace();
            }

            this.RenderShader = nullptr;
         }
      });
   }

    void initShaders() {
      try {
         if (this.RenderShader == nullptr && !SafeMode && !SafeModeForced) {
            RenderThread.invokeOnRenderContext(() -> this.RenderShader = std::make_shared<WeatherShader>("screen"));
         }

         if (this.RenderShader == nullptr || !this.RenderShader.isCompiled()) {
            this.RenderShader = nullptr;
         }
      } catch (Exception var2) {
         this.RenderShader = nullptr;
         var2.printStackTrace();
      }

      IsoPuddles.getInstance();
      IsoWater.getInstance();
   }

    static std::string getGLVersion() {
      if (glVersion == nullptr) {
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

    static void setFullScreen(bool var0) {
      fullScreen = var0;
   }

   public static int[] flipPixels(int[] var0, int var1, int var2) {
      int[] var3 = nullptr;
      if (var0 != nullptr) {
         var3 = new int[var1 * var2];

         for (int var4 = 0; var4 < var2; var4++) {
            for (int var5 = 0; var5 < var1; var5++) {
               var3[(var2 - var4 - 1) * var1 + var5] = var0[var4 * var1 + var5];
            }
         }
      }

    return var3;
   }

    void TakeScreenshot() {
      this.TakeScreenshot(256, 256, 1028);
   }

    void TakeScreenshot(int var1, int var2, int var3) {
    uint8_t var4 = 0;
    int var5 = IsoCamera.getScreenWidth(var4);
    int var6 = IsoCamera.getScreenHeight(var4);
      var1 = PZMath.min(var1, var5);
      var2 = PZMath.min(var2, var6);
    int var7 = IsoCamera.getScreenLeft(var4) + var5 / 2 - var1 / 2;
    int var8 = IsoCamera.getScreenTop(var4) + var6 / 2 - var2 / 2;
      this.TakeScreenshot(var7, var8, var1, var2, var3);
   }

    void TakeScreenshot(int var1, int var2, int var3, int var4, int var5) {
      GL11.glPixelStorei(3333, 1);
      GL11.glReadBuffer(var5);
    uint8_t var6 = 3;
    ByteBuffer var7 = MemoryUtil.memAlloc(var3 * var4 * var6);
      GL11.glReadPixels(var1, var2, var3, var4, 6407, 5121, var7);
      int[] var8 = new int[var3 * var4];
    File var10 = ZomboidFileSystem.instance.getFileInCurrentSave("thumb.png");
    std::string var11 = "png";

      for (int var12 = 0; var12 < var8.length; var12++) {
    int var9 = var12 * 3;
         var8[var12] = 0xFF000000 | (var7.get(var9) & 255) << 16 | (var7.get(var9 + 1) & 255) << 8 | (var7.get(var9 + 2) & 255) << 0;
      }

      MemoryUtil.memFree(var7);
      var8 = flipPixels(var8, var3, var4);
    BufferedImage var16 = std::make_shared<BufferedImage>(var3, var4, 2);
      var16.setRGB(0, 0, var3, var4, var8, 0, var3);

      try {
         ImageIO.write(var16, "png", var10);
      } catch (IOException var14) {
         var14.printStackTrace();
      }

      Texture.reload(ZomboidFileSystem.instance.getFileNameInCurrentSave("thumb.png"));
   }

    void TakeFullScreenshot(const std::string& var1) {
      RenderThread.invokeOnRenderContext(var1, var0 -> {
         GL11.glPixelStorei(3333, 1);
         GL11.glReadBuffer(1028);
    int var1x = Display.getDisplayMode().getWidth();
    int var2 = Display.getDisplayMode().getHeight();
    uint8_t var3 = 0;
    uint8_t var4 = 0;
    uint8_t var5 = 3;
    ByteBuffer var6 = MemoryUtil.memAlloc(var1x * var2 * var5);
         GL11.glReadPixels(var3, var4, var1x, var2, 6407, 5121, var6);
         int[] var7 = new int[var1x * var2];
         if (var0 == nullptr) {
    SimpleDateFormat var9 = std::make_shared<SimpleDateFormat>("dd-MM-yyyy_HH-mm-ss");
            var0 = "screenshot_" + var9.format(Calendar.getInstance().getTime()) + ".png";
         }

    File var14 = std::make_shared<File>(ZomboidFileSystem.instance.getScreenshotDir() + File.separator + var0);

         for (int var10 = 0; var10 < var7.length; var10++) {
    int var8 = var10 * 3;
            var7[var10] = 0xFF000000 | (var6.get(var8) & 255) << 16 | (var6.get(var8 + 1) & 255) << 8 | (var6.get(var8 + 2) & 255) << 0;
         }

         MemoryUtil.memFree(var6);
         var7 = flipPixels(var7, var1x, var2);
    BufferedImage var15 = std::make_shared<BufferedImage>(var1x, var2, 2);
         var15.setRGB(0, 0, var1x, var2, var7, 0, var1x);

         try {
            ImageIO.write(var15, "png", var14);
         } catch (IOException var12) {
            var12.printStackTrace();
         }
      });
   }

    static bool supportNPTTexture() {
    return false;
   }

    bool supportsFBO() {
      if (SafeMode) {
         this.OffscreenBuffer.bZoomEnabled = false;
    return false;
      } else if (!this.bSupportsFBO) {
    return false;
      } else if (this.OffscreenBuffer.Current != nullptr) {
    return true;
      } else {
         try {
            if (TextureFBO.checkFBOSupport() && this.setupMultiFBO()) {
    return true;
            } else {
               this.bSupportsFBO = false;
               SafeMode = true;
               this.OffscreenBuffer.bZoomEnabled = false;
    return false;
            }
         } catch (Exception var2) {
            var2.printStackTrace();
            this.bSupportsFBO = false;
            SafeMode = true;
            this.OffscreenBuffer.bZoomEnabled = false;
    return false;
         }
      }
   }

    void sharedInit() {
      this.supportsFBO();
   }

    void MoveMethodToggle() {
      bAltMoveMethod = !bAltMoveMethod;
   }

    void EndFrameText(int var1) {
      if (!LuaManager.thread.bStep) {
         if (this.OffscreenBuffer.Current != nullptr) {
         }

         IndieGL.glDoEndFrame();
         this.frameStage = 2;
      }
   }

    void EndFrame(int var1) {
      if (!LuaManager.thread.bStep) {
         if (this.OffscreenBuffer.Current != nullptr) {
            SpriteRenderer.instance.glBuffer(0, var1);
         }

         IndieGL.glDoEndFrame();
         this.frameStage = 2;
      }
   }

    void EndFrame() {
      IndieGL.glDoEndFrame();
      if (this.OffscreenBuffer.Current != nullptr) {
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

      if (UIManager.useUIFBO && UIManager.UIFBO == nullptr) {
         UIManager.CreateFBO(width, height);
      }

      if (LuaManager.thread != nullptr && LuaManager.thread.bStep) {
         SpriteRenderer.instance.clearSprites();
      } else {
         ExceptionLogger.render();
         if (UIManager.useUIFBO && this.UIRenderThisFrame) {
            SpriteRenderer.instance.glBuffer(3, 0);
            IndieGL.glDoEndFrame();
            SpriteRenderer.instance.stopOffscreenUI();
            IndieGL.glDoStartFrame(width, height, 1.0F, -1);
    float var1 = (int)(1.0F / OptionUIRenderFPS * 100.0F) / 100.0F;
    int var2 = (int)(this.UIRenderAccumulator / var1);
            this.UIRenderAccumulator -= var2 * var1;
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
         this.frameStage = 0;
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

    int getOffscreenWidth(int var1) {
      if (this.OffscreenBuffer == nullptr) {
         return IsoPlayer.numPlayers > 1 ? this.getScreenWidth() / 2 : this.getScreenWidth();
      } else {
         return this.OffscreenBuffer.getWidth(var1);
      }
   }

    int getOffscreenHeight(int var1) {
      if (this.OffscreenBuffer == nullptr) {
         return IsoPlayer.numPlayers > 2 ? this.getScreenHeight() / 2 : this.getScreenHeight();
      } else {
         return this.OffscreenBuffer.getHeight(var1);
      }
   }

    int getOffscreenTrueWidth() {
      return this.OffscreenBuffer != nullptr && this.OffscreenBuffer.Current != nullptr ? this.OffscreenBuffer.getTexture(0).getWidth() : this.getScreenWidth();
   }

    int getOffscreenTrueHeight() {
      return this.OffscreenBuffer != nullptr && this.OffscreenBuffer.Current != nullptr ? this.OffscreenBuffer.getTexture(0).getHeight() : this.getScreenHeight();
   }

    int getScreenHeight() {
    return height;
   }

    int getScreenWidth() {
    return width;
   }

    void setResolutionAndFullScreen(int var1, int var2, bool var3) {
      setDisplayMode(var1, var2, var3);
      this.setScreenSize(Display.getWidth(), Display.getHeight());
   }

    void setResolution(const std::string& var1) {
      std::string[] var2 = var1.split("x");
    int var3 = int.parseInt(var2[0].trim());
    int var4 = int.parseInt(var2[1].trim());
      if (fullScreen) {
         setDisplayMode(var3, var4, true);
      } else {
         setDisplayMode(var3, var4, false);
      }

      this.setScreenSize(Display.getWidth(), Display.getHeight());

      try {
         this.saveOptions();
      } catch (IOException var6) {
         var6.printStackTrace();
      }
   }

    bool loadOptions() {
      this.bLoadedOptions = false;
    File var1 = std::make_shared<File>(ZomboidFileSystem.instance.getCacheDir() + File.separator + "options.ini");
      if (!var1.exists()) {
         this.saveFolder = getMyDocumentFolder();
    File var21 = std::make_shared<File>(this.saveFolder);
         var21.mkdir();
         this.copyPasteFolders("mods");
         this.setOptionLanguageName(System.getProperty("user.language").toUpperCase());
         if (Translator.getAzertyMap().contains(Translator.getLanguage().name())) {
            this.setAzerty(true);
         }

         if (!GameServer.bServer) {
            try {
    int var30 = 0;
    int var37 = 0;
               DisplayMode[] var22 = Display.getAvailableDisplayModes();
               int[] var45 = new int[1];
               int[] var52 = new int[1];
               int[] var55 = new int[1];
               int[] var56 = new int[1];
               GLFW.glfwGetMonitorWorkarea(GLFW.glfwGetPrimaryMonitor(), var45, var52, var55, var56);

               for (int var10 = 0; var10 < var22.length; var10++) {
                  if (var22[var10].getWidth() > var30 && var22[var10].getWidth() < var55[0] && var22[var10].getHeight() < var56[0]) {
                     var30 = var22[var10].getWidth();
                     var37 = var22[var10].getHeight();
                  }
               }

               width = var30;
               height = var37;
            } catch (LWJGLException var16) {
               var16.printStackTrace();
            }
         }

         this.setOptionZoomLevels2x("50;75;125;150;175;200");
         this.setOptionZoomLevels1x("50;75;125;150;175;200");
         this.saveOptions();
    return false;
      } else {
         this.bLoadedOptions = true;

         for (int var2 = 0; var2 < 4; var2++) {
            this.setAutoZoom(var2, false);
         }

         OptionLanguageName = nullptr;
    BufferedReader var20 = std::make_shared<BufferedReader>(std::make_shared<FileReader>(var1));

         try {
    std::string var3;
            while ((var3 = var20.readLine()) != nullptr) {
               if (var3.startsWith("version=")) {
                  this.version = std::make_shared<int>(var3.replaceFirst("version=", ""));
               } else if (var3.startsWith("width=")) {
                  width = std::make_shared<int>(var3.replaceFirst("width=", ""));
               } else if (var3.startsWith("height=")) {
                  height = std::make_shared<int>(var3.replaceFirst("height=", ""));
               } else if (var3.startsWith("fullScreen=")) {
                  fullScreen = bool.parseBoolean(var3.replaceFirst("fullScreen=", ""));
               } else if (var3.startsWith("frameRate=")) {
                  PerformanceSettings.setLockFPS(int.parseInt(var3.replaceFirst("frameRate=", "")));
               } else if (var3.startsWith("uncappedFPS=")) {
                  PerformanceSettings.setUncappedFPS(bool.parseBoolean(var3.replaceFirst("uncappedFPS=", "")));
               } else if (var3.startsWith("iso_cursor=")) {
                  getInstance().setIsoCursorVisibility(int.parseInt(var3.replaceFirst("iso_cursor=", "")));
               } else if (var3.startsWith("showCursorWhileAiming=")) {
                  OptionShowCursorWhileAiming = bool.parseBoolean(var3.replaceFirst("showCursorWhileAiming=", ""));
               } else if (var3.startsWith("water=")) {
                  PerformanceSettings.WaterQuality = int.parseInt(var3.replaceFirst("water=", ""));
               } else if (var3.startsWith("puddles=")) {
                  PerformanceSettings.PuddlesQuality = int.parseInt(var3.replaceFirst("puddles=", ""));
               } else if (var3.startsWith("lighting=")) {
                  PerformanceSettings.LightingFrameSkip = int.parseInt(var3.replaceFirst("lighting=", ""));
               } else if (var3.startsWith("lightFPS=")) {
                  PerformanceSettings.instance.setLightingFPS(int.parseInt(var3.replaceFirst("lightFPS=", "")));
               } else if (var3.startsWith("perfSkybox=")) {
                  this.iPerfSkybox = int.parseInt(var3.replaceFirst("perfSkybox=", ""));
                  this.iPerfSkybox_new = this.iPerfSkybox;
               } else if (var3.startsWith("perfPuddles=")) {
                  this.iPerfPuddles = int.parseInt(var3.replaceFirst("perfPuddles=", ""));
                  this.iPerfPuddles_new = this.iPerfPuddles;
               } else if (var3.startsWith("bPerfReflections=")) {
                  this.bPerfReflections = bool.parseBoolean(var3.replaceFirst("bPerfReflections=", ""));
                  this.bPerfReflections_new = this.bPerfReflections;
               } else if (var3.startsWith("language=")) {
                  OptionLanguageName = var3.replaceFirst("language=", "").trim();
               } else if (var3.startsWith("zoom=")) {
                  OptionZoom = bool.parseBoolean(var3.replaceFirst("zoom=", ""));
               } else if (var3.startsWith("autozoom=")) {
                  std::string[] var28 = var3.replaceFirst("autozoom=", "").split(",");

                  for (int var35 = 0; var35 < var28.length; var35++) {
                     if (!var28[var35].empty()) {
    int var42 = int.parseInt(var28[var35]);
                        if (var42 >= 1 && var42 <= 4) {
                           this.setAutoZoom(var42 - 1, true);
                        }
                     }
                  }
               } else if (var3.startsWith("fontSize=")) {
                  this.setOptionFontSize(int.parseInt(var3.replaceFirst("fontSize=", "").trim()));
               } else if (var3.startsWith("contextMenuFont=")) {
                  OptionContextMenuFont = var3.replaceFirst("contextMenuFont=", "").trim();
               } else if (var3.startsWith("inventoryFont=")) {
                  OptionInventoryFont = var3.replaceFirst("inventoryFont=", "").trim();
               } else if (var3.startsWith("inventoryContainerSize=")) {
                  OptionInventoryContainerSize = PZMath.tryParseInt(var3.replaceFirst("inventoryContainerSize=", ""), 1);
                  OptionInventoryContainerSize = PZMath.clamp(OptionInventoryContainerSize, 1, 3);
               } else if (var3.startsWith("tooltipFont=")) {
                  OptionTooltipFont = var3.replaceFirst("tooltipFont=", "").trim();
               } else if (var3.startsWith("measurementsFormat=")) {
                  OptionMeasurementFormat = var3.replaceFirst("measurementsFormat=", "").trim();
               } else if (var3.startsWith("clockFormat=")) {
                  OptionClockFormat = int.parseInt(var3.replaceFirst("clockFormat=", ""));
               } else if (var3.startsWith("clockSize=")) {
                  OptionClockSize = int.parseInt(var3.replaceFirst("clockSize=", ""));
               } else if (var3.startsWith("clock24Hour=")) {
                  OptionClock24Hour = bool.parseBoolean(var3.replaceFirst("clock24Hour=", ""));
               } else if (var3.startsWith("vsync=")) {
                  OptionVSync = bool.parseBoolean(var3.replaceFirst("vsync=", ""));
               } else if (var3.startsWith("voiceEnable=")) {
                  OptionVoiceEnable = bool.parseBoolean(var3.replaceFirst("voiceEnable=", ""));
               } else if (var3.startsWith("voiceMode=")) {
                  OptionVoiceMode = int.parseInt(var3.replaceFirst("voiceMode=", ""));
               } else if (var3.startsWith("voiceVADMode=")) {
                  OptionVoiceVADMode = int.parseInt(var3.replaceFirst("voiceVADMode=", ""));
               } else if (var3.startsWith("voiceAGCMode=")) {
                  OptionVoiceAGCMode = int.parseInt(var3.replaceFirst("voiceAGCMode=", ""));
               } else if (var3.startsWith("voiceVolumeMic=")) {
                  OptionVoiceVolumeMic = int.parseInt(var3.replaceFirst("voiceVolumeMic=", ""));
               } else if (var3.startsWith("voiceVolumePlayers=")) {
                  OptionVoiceVolumePlayers = int.parseInt(var3.replaceFirst("voiceVolumePlayers=", ""));
               } else if (var3.startsWith("voiceRecordDeviceName=")) {
                  OptionVoiceRecordDeviceName = var3.replaceFirst("voiceRecordDeviceName=", "");
               } else if (var3.startsWith("soundVolume=")) {
                  OptionSoundVolume = int.parseInt(var3.replaceFirst("soundVolume=", ""));
               } else if (var3.startsWith("musicVolume=")) {
                  OptionMusicVolume = int.parseInt(var3.replaceFirst("musicVolume=", ""));
               } else if (var3.startsWith("ambientVolume=")) {
                  OptionAmbientVolume = int.parseInt(var3.replaceFirst("ambientVolume=", ""));
               } else if (var3.startsWith("jumpScareVolume=")) {
                  OptionJumpScareVolume = int.parseInt(var3.replaceFirst("jumpScareVolume=", ""));
               } else if (var3.startsWith("musicActionStyle=")) {
                  OptionMusicActionStyle = int.parseInt(var3.replaceFirst("musicActionStyle=", ""));
               } else if (var3.startsWith("musicLibrary=")) {
                  OptionMusicLibrary = int.parseInt(var3.replaceFirst("musicLibrary=", ""));
               } else if (var3.startsWith("vehicleEngineVolume=")) {
                  OptionVehicleEngineVolume = int.parseInt(var3.replaceFirst("vehicleEngineVolume=", ""));
               } else if (var3.startsWith("reloadDifficulty=")) {
                  OptionReloadDifficulty = int.parseInt(var3.replaceFirst("reloadDifficulty=", ""));
               } else if (var3.startsWith("rackProgress=")) {
                  OptionRackProgress = bool.parseBoolean(var3.replaceFirst("rackProgress=", ""));
               } else if (var3.startsWith("controller=")) {
    std::string var27 = var3.replaceFirst("controller=", "");
                  if (!var27.empty()) {
                     JoypadManager.instance.setControllerActive(var27, true);
                  }
               } else if (var3.startsWith("tutorialDone=")) {
                  this.tutorialDone = bool.parseBoolean(var3.replaceFirst("tutorialDone=", ""));
               } else if (var3.startsWith("vehiclesWarningShow=")) {
                  this.vehiclesWarningShow = bool.parseBoolean(var3.replaceFirst("vehiclesWarningShow=", ""));
               } else if (var3.startsWith("bloodDecals=")) {
                  this.setOptionBloodDecals(int.parseInt(var3.replaceFirst("bloodDecals=", "")));
               } else if (var3.startsWith("borderless=")) {
                  OptionBorderlessWindow = bool.parseBoolean(var3.replaceFirst("borderless=", ""));
               } else if (var3.startsWith("lockCursorToWindow=")) {
                  OptionLockCursorToWindow = bool.parseBoolean(var3.replaceFirst("lockCursorToWindow=", ""));
               } else if (var3.startsWith("textureCompression=")) {
                  OptionTextureCompression = bool.parseBoolean(var3.replaceFirst("textureCompression=", ""));
               } else if (var3.startsWith("modelTextureMipmaps=")) {
                  OptionModelTextureMipmaps = bool.parseBoolean(var3.replaceFirst("modelTextureMipmaps=", ""));
               } else if (var3.startsWith("texture2x=")) {
                  OptionTexture2x = bool.parseBoolean(var3.replaceFirst("texture2x=", ""));
               } else if (var3.startsWith("maxTextureSize=")) {
                  OptionMaxTextureSize = int.parseInt(var3.replaceFirst("maxTextureSize=", ""));
                  OptionMaxTextureSize = PZMath.clamp(OptionMaxTextureSize, 1, 4);
               } else if (var3.startsWith("maxVehicleTextureSize=")) {
                  OptionMaxVehicleTextureSize = int.parseInt(var3.replaceFirst("maxVehicleTextureSize=", ""));
                  OptionMaxVehicleTextureSize = PZMath.clamp(OptionMaxVehicleTextureSize, 1, 4);
               } else if (var3.startsWith("zoomLevels1x=")) {
                  OptionZoomLevels1x = var3.replaceFirst("zoomLevels1x=", "");
               } else if (var3.startsWith("zoomLevels2x=")) {
                  OptionZoomLevels2x = var3.replaceFirst("zoomLevels2x=", "");
               } else if (var3.startsWith("showChatTimestamp=")) {
                  OptionShowChatTimestamp = bool.parseBoolean(var3.replaceFirst("showChatTimestamp=", ""));
               } else if (var3.startsWith("showChatTitle=")) {
                  OptionShowChatTitle = bool.parseBoolean(var3.replaceFirst("showChatTitle=", ""));
               } else if (var3.startsWith("chatFontSize=")) {
                  OptionChatFontSize = var3.replaceFirst("chatFontSize=", "");
               } else if (var3.startsWith("minChatOpaque=")) {
                  OptionMinChatOpaque = float.parseFloat(var3.replaceFirst("minChatOpaque=", ""));
               } else if (var3.startsWith("maxChatOpaque=")) {
                  OptionMaxChatOpaque = float.parseFloat(var3.replaceFirst("maxChatOpaque=", ""));
               } else if (var3.startsWith("chatFadeTime=")) {
                  OptionChatFadeTime = float.parseFloat(var3.replaceFirst("chatFadeTime=", ""));
               } else if (var3.startsWith("chatOpaqueOnFocus=")) {
                  OptionChatOpaqueOnFocus = bool.parseBoolean(var3.replaceFirst("chatOpaqueOnFocus=", ""));
               } else if (var3.startsWith("doneNewSaveFolder=")) {
                  this.doneNewSaveFolder = bool.parseBoolean(var3.replaceFirst("doneNewSaveFolder=", ""));
               } else if (var3.startsWith("contentTranslationsEnabled=")) {
                  OptionEnableContentTranslations = bool.parseBoolean(var3.replaceFirst("contentTranslationsEnabled=", ""));
               } else if (var3.startsWith("showYourUsername=")) {
                  this.showYourUsername = bool.parseBoolean(var3.replaceFirst("showYourUsername=", ""));
               } else if (var3.startsWith("riversideDone=")) {
                  this.riversideDone = bool.parseBoolean(var3.replaceFirst("riversideDone=", ""));
               } else if (var3.startsWith("rosewoodSpawnDone=")) {
                  this.rosewoodSpawnDone = bool.parseBoolean(var3.replaceFirst("rosewoodSpawnDone=", ""));
               } else if (var3.startsWith("gotNewBelt=")) {
                  this.gotNewBelt = bool.parseBoolean(var3.replaceFirst("gotNewBelt=", ""));
               } else if (var3.startsWith("mpTextColor=")) {
                  std::string[] var26 = var3.replaceFirst("mpTextColor=", "").split(",");
    float var34 = float.parseFloat(var26[0]);
    float var41 = float.parseFloat(var26[1]);
    float var49 = float.parseFloat(var26[2]);
                  if (var34 < 0.19F) {
                     var34 = 0.19F;
                  }

                  if (var41 < 0.19F) {
                     var41 = 0.19F;
                  }

                  if (var49 < 0.19F) {
                     var49 = 0.19F;
                  }

                  this.mpTextColor = std::make_shared<ColorInfo>(var34, var41, var49, 1.0F);
               } else if (var3.startsWith("objHighlightColor=")) {
                  std::string[] var25 = var3.replaceFirst("objHighlightColor=", "").split(",");
    float var33 = float.parseFloat(var25[0]);
    float var40 = float.parseFloat(var25[1]);
    float var48 = float.parseFloat(var25[2]);
                  if (var33 < 0.19F) {
                     var33 = 0.19F;
                  }

                  if (var40 < 0.19F) {
                     var40 = 0.19F;
                  }

                  if (var48 < 0.19F) {
                     var48 = 0.19F;
                  }

                  this.objectHighlitedColor.set(var33, var40, var48, 1.0F);
               } else if (var3.startsWith("goodHighlightColor=")) {
                  std::string[] var24 = var3.replaceFirst("goodHighlightColor=", "").split(",");
    float var32 = float.parseFloat(var24[0]);
    float var39 = float.parseFloat(var24[1]);
    float var47 = float.parseFloat(var24[2]);
                  this.goodHighlitedColor.set(var32, var39, var47, 1.0F);
               } else if (var3.startsWith("badHighlightColor=")) {
                  std::string[] var23 = var3.replaceFirst("badHighlightColor=", "").split(",");
    float var31 = float.parseFloat(var23[0]);
    float var38 = float.parseFloat(var23[1]);
    float var46 = float.parseFloat(var23[2]);
                  this.badHighlitedColor.set(var31, var38, var46, 1.0F);
               } else if (var3.startsWith("seenNews=")) {
                  this.setSeenUpdateText(var3.replaceFirst("seenNews=", ""));
               } else if (var3.startsWith("toggleToAim=")) {
                  this.setToggleToAim(bool.parseBoolean(var3.replaceFirst("toggleToAim=", "")));
               } else if (var3.startsWith("toggleToRun=")) {
                  this.setToggleToRun(bool.parseBoolean(var3.replaceFirst("toggleToRun=", "")));
               } else if (var3.startsWith("toggleToSprint=")) {
                  this.setToggleToSprint(bool.parseBoolean(var3.replaceFirst("toggleToSprint=", "")));
               } else if (var3.startsWith("celsius=")) {
                  this.setCelsius(bool.parseBoolean(var3.replaceFirst("celsius=", "")));
               } else if (!var3.startsWith("mapOrder=")) {
                  if (var3.startsWith("showFirstTimeSneakTutorial=")) {
                     this.setShowFirstTimeSneakTutorial(bool.parseBoolean(var3.replaceFirst("showFirstTimeSneakTutorial=", "")));
                  } else if (var3.startsWith("showFirstTimeSearchTutorial=")) {
                     this.setShowFirstTimeSearchTutorial(bool.parseBoolean(var3.replaceFirst("showFirstTimeSearchTutorial=", "")));
                  } else if (var3.startsWith("termsOfServiceVersion=")) {
                     this.termsOfServiceVersion = int.parseInt(var3.replaceFirst("termsOfServiceVersion=", ""));
                  } else if (var3.startsWith("uiRenderOffscreen=")) {
                     OptionUIFBO = bool.parseBoolean(var3.replaceFirst("uiRenderOffscreen=", ""));
                  } else if (var3.startsWith("uiRenderFPS=")) {
                     OptionUIRenderFPS = int.parseInt(var3.replaceFirst("uiRenderFPS=", ""));
                  } else if (var3.startsWith("radialMenuKeyToggle=")) {
                     OptionRadialMenuKeyToggle = bool.parseBoolean(var3.replaceFirst("radialMenuKeyToggle=", ""));
                  } else if (var3.startsWith("reloadRadialInstant=")) {
                     OptionReloadRadialInstant = bool.parseBoolean(var3.replaceFirst("reloadRadialInstant=", ""));
                  } else if (var3.startsWith("panCameraWhileAiming=")) {
                     OptionPanCameraWhileAiming = bool.parseBoolean(var3.replaceFirst("panCameraWhileAiming=", ""));
                  } else if (var3.startsWith("panCameraWhileDriving=")) {
                     OptionPanCameraWhileDriving = bool.parseBoolean(var3.replaceFirst("panCameraWhileDriving=", ""));
                  } else if (var3.startsWith("temperatureDisplayCelsius=")) {
                     OptionTemperatureDisplayCelsius = bool.parseBoolean(var3.replaceFirst("temperatureDisplayCelsius=", ""));
                  } else if (var3.startsWith("doWindSpriteEffects=")) {
                     OptionDoWindSpriteEffects = bool.parseBoolean(var3.replaceFirst("doWindSpriteEffects=", ""));
                  } else if (var3.startsWith("doDoorSpriteEffects=")) {
                     OptionDoDoorSpriteEffects = bool.parseBoolean(var3.replaceFirst("doDoorSpriteEffects=", ""));
                  } else if (var3.startsWith("doContainerOutline=")) {
                     OptionDoContainerOutline = bool.parseBoolean(var3.replaceFirst("doContainerOutline=", ""));
                  } else if (var3.startsWith("updateSneakButton2=")) {
                     OptionUpdateSneakButton = true;
                  } else if (var3.startsWith("updateSneakButton=")) {
                     OptionUpdateSneakButton = bool.parseBoolean(var3.replaceFirst("updateSneakButton=", ""));
                  } else if (var3.startsWith("dblTapJogToSprint=")) {
                     OptiondblTapJogToSprint = bool.parseBoolean(var3.replaceFirst("dblTapJogToSprint=", ""));
                  } else if (var3.startsWith("aimOutline=")) {
                     this.setOptionAimOutline(PZMath.tryParseInt(var3.replaceFirst("aimOutline=", ""), 2));
                  } else if (var3.startsWith("cycleContainerKey=")) {
                     OptionCycleContainerKey = var3.replaceFirst("cycleContainerKey=", "");
                  } else if (var3.startsWith("dropItemsOnSquareCenter=")) {
                     OptionDropItemsOnSquareCenter = bool.parseBoolean(var3.replaceFirst("dropItemsOnSquareCenter=", ""));
                  } else if (var3.startsWith("timedActionGameSpeedReset=")) {
                     OptionTimedActionGameSpeedReset = bool.parseBoolean(var3.replaceFirst("timedActionGameSpeedReset=", ""));
                  } else if (var3.startsWith("shoulderButtonContainerSwitch=")) {
                     OptionShoulderButtonContainerSwitch = int.parseInt(var3.replaceFirst("shoulderButtonContainerSwitch=", ""));
                  } else if (var3.startsWith("singleContextMenu=")) {
                     this.readPerPlayerBoolean(var3.replaceFirst("singleContextMenu=", ""), OptionSingleContextMenu);
                  } else if (var3.startsWith("renderPrecipIndoors=")) {
                     OptionRenderPrecipIndoors = bool.parseBoolean(var3.replaceFirst("renderPrecipIndoors=", ""));
                  } else if (var3.startsWith("autoProneAtk=")) {
                     OptionAutoProneAtk = bool.parseBoolean(var3.replaceFirst("autoProneAtk=", ""));
                  } else if (var3.startsWith("3DGroundItem=")) {
                     Option3DGroundItem = bool.parseBoolean(var3.replaceFirst("3DGroundItem=", ""));
                  } else if (var3.startsWith("tieredZombieUpdates=")) {
                     this.setOptionTieredZombieUpdates(bool.parseBoolean(var3.replaceFirst("tieredZombieUpdates=", "")));
                  } else if (var3.startsWith("progressBar=")) {
                     this.setOptionProgressBar(bool.parseBoolean(var3.replaceFirst("progressBar=", "")));
                  } else if (var3.startsWith("corpseShadows=")) {
                     OptionCorpseShadows = bool.parseBoolean(var3.replaceFirst("corpseShadows=", ""));
                  } else if (var3.startsWith("simpleClothingTextures=")) {
                     this.setOptionSimpleClothingTextures(PZMath.tryParseInt(var3.replaceFirst("simpleClothingTextures=", ""), 1));
                  } else if (var3.startsWith("simpleWeaponTextures=")) {
                     OptionSimpleWeaponTextures = bool.parseBoolean(var3.replaceFirst("simpleWeaponTextures=", ""));
                  } else if (var3.startsWith("autoDrink=")) {
                     OptionAutoDrink = bool.parseBoolean(var3.replaceFirst("autoDrink=", ""));
                  } else if (var3.startsWith("leaveKeyInIgnition=")) {
                     OptionLeaveKeyInIgnition = bool.parseBoolean(var3.replaceFirst("leaveKeyInIgnition=", ""));
                  } else if (var3.startsWith("autoWalkContainer=")) {
                     OptionAutoWalkContainer = bool.parseBoolean(var3.replaceFirst("autoWalkContainer=", ""));
                  } else if (var3.startsWith("searchModeOverlayEffect=")) {
                     OptionSearchModeOverlayEffect = int.parseInt(var3.replaceFirst("searchModeOverlayEffect=", ""));
                  } else if (var3.startsWith("ignoreProneZombieRange=")) {
                     this.setOptionIgnoreProneZombieRange(PZMath.tryParseInt(var3.replaceFirst("ignoreProneZombieRange=", ""), 1));
                  } else if (var3.startsWith("fogQuality=")) {
                     PerformanceSettings.FogQuality = int.parseInt(var3.replaceFirst("fogQuality=", ""));
                  } else if (var3.startsWith("renderPrecipitation=")) {
                     OptionRenderPrecipitation = int.parseInt(var3.replaceFirst("renderPrecipitation=", ""));
                  } else if (var3.startsWith("showItemModInfo=")) {
                     OptionShowItemModInfo = bool.parseBoolean(var3.replaceFirst("showItemModInfo=", ""));
                  } else if (var3.startsWith("showSurvivalGuide=")) {
                     this.OptionShowSurvivalGuide = bool.parseBoolean(var3.replaceFirst("showSurvivalGuide=", ""));
                  } else if (var3.startsWith("enableLeftJoystickRadialMenu=")) {
                     OptionEnableLeftJoystickRadialMenu = bool.parseBoolean(var3.replaceFirst("enableLeftJoystickRadialMenu=", ""));
                  }
               } else {
                  if (this.version < 7) {
                     var3 = "mapOrder=";
                  }

                  std::string[] var4 = var3.replaceFirst("mapOrder=", "").split(";");

    for (auto& var8 : var4)                     var8 = var8.trim();
                     if (!var8.empty()) {
                        ActiveMods.getById("default").getMapOrder().push_back(var8);
                     }
                  }

                  ZomboidFileSystem.instance.saveModsFile();
               }
            }

            if (OptionLanguageName == nullptr) {
               OptionLanguageName = System.getProperty("user.language").toUpperCase();
            }

            if (!this.doneNewSaveFolder) {
    File var29 = std::make_shared<File>(ZomboidFileSystem.instance.getSaveDir());
               var29.mkdir();
    std::vector var36 = new std::vector();
               var36.push_back("Beginner");
               var36.push_back("Survival");
               var36.push_back("A Really CD DA");
               var36.push_back("LastStand");
               var36.push_back("Opening Hours");
               var36.push_back("Sandbox");
               var36.push_back("Tutorial");
               var36.push_back("Winter is Coming");
               var36.push_back("You Have One Day");
    void* var43 = nullptr;
    File var50 = nullptr;

               try {
    for (auto& var9 : var36)                     var43 = std::make_shared<File>(ZomboidFileSystem.instance.getCacheDir() + File.separator + var9);
                     var50 = std::make_shared<File>(ZomboidFileSystem.instance.getSaveDir() + File.separator + var9);
                     if (var43.exists()) {
                        var50.mkdir();
                        Files.move(var43.toPath(), var50.toPath(), StandardCopyOption.REPLACE_EXISTING);
                     }
                  }
               } catch (Exception var17) {
               }

               this.doneNewSaveFolder = true;
            }
         } catch (Exception var18) {
            var18.printStackTrace();
         } finally {
            var20.close();
         }

         this.saveOptions();
    return true;
      }
   }

    bool isDefaultOptions() {
      return !this.bLoadedOptions;
   }

    bool isDedicated() {
      return GameServer.bServer;
   }

    void copyPasteFolders(const std::string& var1) {
    File var2 = std::make_shared<File>(var1).getAbsoluteFile();
      if (var2.exists()) {
         this.searchFolders(var2, var1);
      }
   }

    void searchFolders(File var1, const std::string& var2) {
      if (var1.isDirectory()) {
    File var3 = std::make_shared<File>(this.saveFolder + File.separator + var2);
         var3.mkdir();
         std::string[] var4 = var1.list();

         for (int var5 = 0; var5 < var4.length; var5++) {
            this.searchFolders(std::make_shared<File>(var1.getAbsolutePath() + File.separator + var4[var5]), var2 + File.separator + var4[var5]);
         }
      } else {
         this.copyPasteFile(var1, var2);
      }
   }

    void copyPasteFile(File var1, const std::string& var2) {
    FileOutputStream var3 = nullptr;
    FileInputStream var4 = nullptr;

      try {
    File var5 = std::make_shared<File>(this.saveFolder + File.separator + var2);
         var5.createNewFile();
         var3 = std::make_shared<FileOutputStream>(var5);
         var4 = std::make_shared<FileInputStream>(var1);
         var3.getChannel().transferFrom(var4.getChannel(), 0L, var1.length());
      } catch (Exception var14) {
         var14.printStackTrace();
      } finally {
         try {
            if (var4 != nullptr) {
               var4.close();
            }

            if (var3 != nullptr) {
               var3.close();
            }
         } catch (IOException var13) {
            var13.printStackTrace();
         }
      }
   }

    static std::string getMyDocumentFolder() {
      return ZomboidFileSystem.instance.getCacheDir();
   }

    void saveOptions() {
    File var1 = std::make_shared<File>(ZomboidFileSystem.instance.getCacheDir() + File.separator + "options.ini");
      if (!var1.exists()) {
         var1.createNewFile();
      }

    FileWriter var2 = std::make_shared<FileWriter>(var1);

      try {
         var2.write("version=" + this.fileversion + "\r\n");
         var2.write("width=" + this.getScreenWidth() + "\r\n");
         var2.write("height=" + this.getScreenHeight() + "\r\n");
         var2.write("fullScreen=" + fullScreen + "\r\n");
         var2.write("frameRate=" + PerformanceSettings.getLockFPS() + "\r\n");
         var2.write("uncappedFPS=" + PerformanceSettings.isUncappedFPS() + "\r\n");
         var2.write("iso_cursor=" + getInstance().getIsoCursorVisibility() + "\r\n");
         var2.write("showCursorWhileAiming=" + OptionShowCursorWhileAiming + "\r\n");
         var2.write("water=" + PerformanceSettings.WaterQuality + "\r\n");
         var2.write("puddles=" + PerformanceSettings.PuddlesQuality + "\r\n");
         var2.write("lighting=" + PerformanceSettings.LightingFrameSkip + "\r\n");
         var2.write("lightFPS=" + PerformanceSettings.LightingFPS + "\r\n");
         var2.write("perfSkybox=" + this.iPerfSkybox_new + "\r\n");
         var2.write("perfPuddles=" + this.iPerfPuddles_new + "\r\n");
         var2.write("bPerfReflections=" + this.bPerfReflections_new + "\r\n");
         var2.write("vidMem=" + this.vidMem + "\r\n");
         var2.write("language=" + this.getOptionLanguageName() + "\r\n");
         var2.write("zoom=" + OptionZoom + "\r\n");
         var2.write("fontSize=" + OptionFontSize + "\r\n");
         var2.write("contextMenuFont=" + OptionContextMenuFont + "\r\n");
         var2.write("inventoryFont=" + OptionInventoryFont + "\r\n");
         var2.write("inventoryContainerSize=" + OptionInventoryContainerSize + "\r\n");
         var2.write("tooltipFont=" + OptionTooltipFont + "\r\n");
         var2.write("clockFormat=" + OptionClockFormat + "\r\n");
         var2.write("clockSize=" + OptionClockSize + "\r\n");
         var2.write("clock24Hour=" + OptionClock24Hour + "\r\n");
         var2.write("measurementsFormat=" + OptionMeasurementFormat + "\r\n");
    std::string var3 = "";

         for (int var4 = 0; var4 < 4; var4++) {
            if (bAutoZoom[var4]) {
               if (!var3.empty()) {
                  var3 = var3 + ",";
               }

               var3 = var3 + (var4 + 1);
            }
         }

         var2.write("autozoom=" + var3 + "\r\n");
         var2.write("vsync=" + OptionVSync + "\r\n");
         var2.write("soundVolume=" + OptionSoundVolume + "\r\n");
         var2.write("ambientVolume=" + OptionAmbientVolume + "\r\n");
         var2.write("musicVolume=" + OptionMusicVolume + "\r\n");
         var2.write("jumpScareVolume=" + OptionJumpScareVolume + "\r\n");
         var2.write("musicActionStyle=" + OptionMusicActionStyle + "\r\n");
         var2.write("musicLibrary=" + OptionMusicLibrary + "\r\n");
         var2.write("vehicleEngineVolume=" + OptionVehicleEngineVolume + "\r\n");
         var2.write("voiceEnable=" + OptionVoiceEnable + "\r\n");
         var2.write("voiceMode=" + OptionVoiceMode + "\r\n");
         var2.write("voiceVADMode=" + OptionVoiceVADMode + "\r\n");
         var2.write("voiceAGCMode=" + OptionVoiceAGCMode + "\r\n");
         var2.write("voiceVolumeMic=" + OptionVoiceVolumeMic + "\r\n");
         var2.write("voiceVolumePlayers=" + OptionVoiceVolumePlayers + "\r\n");
         var2.write("voiceRecordDeviceName=" + OptionVoiceRecordDeviceName + "\r\n");
         var2.write("reloadDifficulty=" + OptionReloadDifficulty + "\r\n");
         var2.write("rackProgress=" + OptionRackProgress + "\r\n");

         for (std::string var5 : JoypadManager.instance.ActiveControllerGUIDs) {
            var2.write("controller=" + var5 + "\r\n");
         }

         var2.write("tutorialDone=" + this.isTutorialDone() + "\r\n");
         var2.write("vehiclesWarningShow=" + this.isVehiclesWarningShow() + "\r\n");
         var2.write("bloodDecals=" + OptionBloodDecals + "\r\n");
         var2.write("borderless=" + OptionBorderlessWindow + "\r\n");
         var2.write("lockCursorToWindow=" + OptionLockCursorToWindow + "\r\n");
         var2.write("textureCompression=" + OptionTextureCompression + "\r\n");
         var2.write("modelTextureMipmaps=" + OptionModelTextureMipmaps + "\r\n");
         var2.write("texture2x=" + OptionTexture2x + "\r\n");
         var2.write("maxTextureSize=" + OptionMaxTextureSize + "\r\n");
         var2.write("maxVehicleTextureSize=" + OptionMaxVehicleTextureSize + "\r\n");
         var2.write("zoomLevels1x=" + OptionZoomLevels1x + "\r\n");
         var2.write("zoomLevels2x=" + OptionZoomLevels2x + "\r\n");
         var2.write("showChatTimestamp=" + OptionShowChatTimestamp + "\r\n");
         var2.write("showChatTitle=" + OptionShowChatTitle + "\r\n");
         var2.write("chatFontSize=" + OptionChatFontSize + "\r\n");
         var2.write("minChatOpaque=" + OptionMinChatOpaque + "\r\n");
         var2.write("maxChatOpaque=" + OptionMaxChatOpaque + "\r\n");
         var2.write("chatFadeTime=" + OptionChatFadeTime + "\r\n");
         var2.write("chatOpaqueOnFocus=" + OptionChatOpaqueOnFocus + "\r\n");
         var2.write("doneNewSaveFolder=" + this.doneNewSaveFolder + "\r\n");
         var2.write("contentTranslationsEnabled=" + OptionEnableContentTranslations + "\r\n");
         var2.write("showYourUsername=" + this.showYourUsername + "\r\n");
         var2.write("rosewoodSpawnDone=" + this.rosewoodSpawnDone + "\r\n");
         if (this.mpTextColor != nullptr) {
            var2.write("mpTextColor=" + this.mpTextColor.r + "," + this.mpTextColor.g + "," + this.mpTextColor.b + "\r\n");
         }

         var2.write("objHighlightColor=" + this.objectHighlitedColor.r + "," + this.objectHighlitedColor.g + "," + this.objectHighlitedColor.b + "\r\n");
         var2.write("seenNews=" + this.getSeenUpdateText() + "\r\n");
         var2.write("toggleToAim=" + this.isToggleToAim() + "\r\n");
         var2.write("toggleToRun=" + this.isToggleToRun() + "\r\n");
         var2.write("toggleToSprint=" + this.isToggleToSprint() + "\r\n");
         var2.write("celsius=" + this.isCelsius() + "\r\n");
         var2.write("riversideDone=" + this.isRiversideDone() + "\r\n");
         var2.write("showFirstTimeSneakTutorial=" + this.isShowFirstTimeSneakTutorial() + "\r\n");
         var2.write("showFirstTimeSearchTutorial=" + this.isShowFirstTimeSearchTutorial() + "\r\n");
         var2.write("termsOfServiceVersion=" + this.termsOfServiceVersion + "\r\n");
         var2.write("uiRenderOffscreen=" + OptionUIFBO + "\r\n");
         var2.write("uiRenderFPS=" + OptionUIRenderFPS + "\r\n");
         var2.write("radialMenuKeyToggle=" + OptionRadialMenuKeyToggle + "\r\n");
         var2.write("reloadRadialInstant=" + OptionReloadRadialInstant + "\r\n");
         var2.write("panCameraWhileAiming=" + OptionPanCameraWhileAiming + "\r\n");
         var2.write("panCameraWhileDriving=" + OptionPanCameraWhileDriving + "\r\n");
         var2.write("temperatureDisplayCelsius=" + OptionTemperatureDisplayCelsius + "\r\n");
         var2.write("doWindSpriteEffects=" + OptionDoWindSpriteEffects + "\r\n");
         var2.write("doDoorSpriteEffects=" + OptionDoDoorSpriteEffects + "\r\n");
         var2.write("doDoContainerOutline=" + OptionDoContainerOutline + "\r\n");
         var2.write("updateSneakButton=" + OptionUpdateSneakButton + "\r\n");
         var2.write("dblTapJogToSprint=" + OptiondblTapJogToSprint + "\r\n");
         var2.write("gotNewBelt=" + this.gotNewBelt + "\r\n");
         var2.write("aimOutline=" + OptionAimOutline + "\r\n");
         var2.write("cycleContainerKey=" + OptionCycleContainerKey + "\r\n");
         var2.write("dropItemsOnSquareCenter=" + OptionDropItemsOnSquareCenter + "\r\n");
         var2.write("timedActionGameSpeedReset=" + OptionTimedActionGameSpeedReset + "\r\n");
         var2.write("shoulderButtonContainerSwitch=" + OptionShoulderButtonContainerSwitch + "\r\n");
         var2.write("singleContextMenu=" + this.getPerPlayerBooleanString(OptionSingleContextMenu) + "\r\n");
         var2.write("renderPrecipIndoors=" + OptionRenderPrecipIndoors + "\r\n");
         var2.write("autoProneAtk=" + OptionAutoProneAtk + "\r\n");
         var2.write("3DGroundItem=" + Option3DGroundItem + "\r\n");
         var2.write("tieredZombieUpdates=" + this.getOptionTieredZombieUpdates() + "\r\n");
         var2.write("progressBar=" + this.isOptionProgressBar() + "\r\n");
         var2.write("corpseShadows=" + this.getOptionCorpseShadows() + "\r\n");
         var2.write("simpleClothingTextures=" + this.getOptionSimpleClothingTextures() + "\r\n");
         var2.write("simpleWeaponTextures=" + this.getOptionSimpleWeaponTextures() + "\r\n");
         var2.write("autoDrink=" + this.getOptionAutoDrink() + "\r\n");
         var2.write("leaveKeyInIgnition=" + this.getOptionLeaveKeyInIgnition() + "\r\n");
         var2.write("autoWalkContainer=" + this.getOptionAutoWalkContainer() + "\r\n");
         var2.write("searchModeOverlayEffect=" + this.getOptionSearchModeOverlayEffect() + "\r\n");
         var2.write("ignoreProneZombieRange=" + this.getOptionIgnoreProneZombieRange() + "\r\n");
         var2.write("fogQuality=" + PerformanceSettings.FogQuality + "\r\n");
         var2.write("renderPrecipitation=" + OptionRenderPrecipitation + "\r\n");
         var2.write("showItemModInfo=" + OptionShowItemModInfo + "\r\n");
         var2.write("showSurvivalGuide=" + this.OptionShowSurvivalGuide + "\r\n");
         var2.write("enableLeftJoystickRadialMenu=" + OptionEnableLeftJoystickRadialMenu + "\r\n");
         var2.write("doContainerOutline=" + OptionDoContainerOutline + "\r\n");
         var2.write("goodHighlightColor=" + this.goodHighlitedColor.r + "," + this.goodHighlitedColor.g + "," + this.goodHighlitedColor.b + "\r\n");
         var2.write("badHighlightColor=" + this.badHighlitedColor.r + "," + this.badHighlitedColor.g + "," + this.badHighlitedColor.b + "\r\n");
      } catch (Exception var9) {
         var9.printStackTrace();
      } finally {
         var2.close();
      }
   }

    void setWindowed(bool var1) {
      RenderThread.invokeOnRenderContext(() -> {
         if (var1 != fullScreen) {
            setDisplayMode(this.getScreenWidth(), this.getScreenHeight(), var1);
         }

         fullScreen = var1;
         if (fakefullscreen) {
            Display.setResizable(false);
         } else {
            Display.setResizable(!var1);
         }

         try {
            this.saveOptions();
         } catch (IOException var3) {
            var3.printStackTrace();
         }
      });
   }

    bool isFullScreen() {
    return fullScreen;
   }

    KahluaTable getScreenModes() {
    std::vector var1 = new std::vector();
    KahluaTable var2 = LuaManager.platform.newTable();
    File var3 = std::make_shared<File>(LuaManager.getLuaCacheDir() + File.separator + "screenresolution.ini");
    int var4 = 1;

      try {
         if (!var3.exists()) {
            var3.createNewFile();
    FileWriter var5 = std::make_shared<FileWriter>(var3);
    int var6 = 0;
    int var7 = 0;
            DisplayMode[] var8 = Display.getAvailableDisplayModes();

            for (int var9 = 0; var9 < var8.length; var9++) {
               var6 = var8[var9].getWidth();
               var7 = var8[var9].getHeight();
               if (!var1.contains(var6 + " x " + var7)) {
                  var2.rawset(var4, var6 + " x " + var7);
                  var5.write(var6 + " x " + var7 + " \r\n");
                  var1.push_back(var6 + " x " + var7);
                  var4++;
               }
            }

            var5.close();
         } else {
    BufferedReader var11 = std::make_shared<BufferedReader>(std::make_shared<FileReader>(var3));

    std::string var14;
            for (var14 = nullptr; (var14 = var11.readLine()) != nullptr; var4++) {
               var2.rawset(var4, var14.trim());
            }

            var11.close();
         }
      } catch (Exception var10) {
         var10.printStackTrace();
      }

    return var2;
   }

    static void setDisplayMode(int var0, int var1, bool var2) {
      RenderThread.invokeOnRenderContext(
         () -> {
            if (Display.getWidth() != var0
               || Display.getHeight() != var1
               || Display.isFullscreen() != var2
               || Display.isBorderlessWindow() != OptionBorderlessWindow) {
               fullScreen = var2;

               try {
    DisplayMode var3 = nullptr;
                  if (!var2) {
                     if (OptionBorderlessWindow) {
                        if (Display.getWindow() != 0L && Display.isFullscreen()) {
                           Display.setFullscreen(false);
                        }

    long var12 = GLFW.glfwGetPrimaryMonitor();
    GLFWVidMode var13 = GLFW.glfwGetVideoMode(var12);
                        var3 = std::make_shared<DisplayMode>(var13.width(), var13.height());
                     } else {
                        var3 = std::make_shared<DisplayMode>(var0, var1);
                     }
                  } else {
                     DisplayMode[] var4 = Display.getAvailableDisplayModes();
    int var5 = 0;
    DisplayMode var6 = nullptr;

    for (auto& var10 : var4)                        if (var10.getWidth() == var0 && var10.getHeight() == var1 && var10.isFullscreenCapable()) {
                           if ((var3 == nullptr || var10.getFrequency() >= var5) && (var3 == nullptr || var10.getBitsPerPixel() > var3.getBitsPerPixel())) {
                              var3 = var10;
                              var5 = var10.getFrequency();
                           }

                           if (var10.getBitsPerPixel() == Display.getDesktopDisplayMode().getBitsPerPixel()
                              && var10.getFrequency() == Display.getDesktopDisplayMode().getFrequency()) {
                              var3 = var10;
                              break;
                           }
                        }

                        if (var10.isFullscreenCapable()
                           && (
                              var6 == nullptr
                                 || Math.abs(var10.getWidth() - var0) < Math.abs(var6.getWidth() - var0)
                                 || var10.getWidth() == var6.getWidth() && var10.getFrequency() > var5
                           )) {
                           var6 = var10;
                           var5 = var10.getFrequency();
                           System.out.println("closest width=" + var10.getWidth() + " freq=" + var10.getFrequency());
                        }
                     }

                     if (var3 == nullptr && var6 != nullptr) {
                        var3 = var6;
                     }
                  }

                  if (var3 == nullptr) {
                     DebugLog.log("Failed to find value mode: " + var0 + "x" + var1 + " fs=" + var2);
                     return;
                  }

                  Display.setBorderlessWindow(OptionBorderlessWindow);
                  if (var2) {
                     Display.setDisplayModeAndFullscreen(var3);
                  } else {
                     Display.setDisplayMode(var3);
                     Display.setFullscreen(false);
                  }

                  if (!var2 && OptionBorderlessWindow) {
                     Display.setResizable(false);
                  } else if (!var2 && !fakefullscreen) {
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
               } catch (LWJGLException var11) {
                  DebugLog.log("Unable to setup mode " + var0 + "x" + var1 + " fullscreen=" + var2 + var11);
               }
            }
         }
      );
   }

    bool isFunctionKey(int var1) {
      return var1 >= 59 && var1 <= 68 || var1 >= 87 && var1 <= 105 || var1 == 113;
   }

    bool isDoingTextEntry() {
      if (CurrentTextEntryBox == nullptr) {
    return false;
      } else {
         return !CurrentTextEntryBox.IsEditable ? false : CurrentTextEntryBox.DoingTextEntry;
      }
   }

    void updateKeyboardAux(UITextBox2 var1, int var2) {
    bool var3 = Keyboard.isKeyDown(29) || Keyboard.isKeyDown(157);
    bool var4 = Keyboard.isKeyDown(42) || Keyboard.isKeyDown(54);
      if (var2 == 28 || var2 == 156) {
    bool var17 = false;
         if (UIManager.getDebugConsole() != nullptr && var1 == UIManager.getDebugConsole().CommandLine) {
            var17 = true;
         }

         if (var1.multipleLine) {
            if (var1.Lines.size() < var1.getMaxLines()) {
               if (var1.TextEntryCursorPos != var1.ToSelectionIndex) {
    int var26 = Math.min(var1.TextEntryCursorPos, var1.ToSelectionIndex);
    int var8 = Math.max(var1.TextEntryCursorPos, var1.ToSelectionIndex);
                  if (var1.internalText.length() > 0) {
                     var1.internalText = var1.internalText.substr(0, var26) + "\n" + var1.internalText.substr(var8);
                  } else {
                     var1.internalText = "\n";
                  }

                  var1.TextEntryCursorPos = var26 + 1;
               } else {
    int var27 = var1.TextEntryCursorPos;
    std::string var28 = var1.internalText.substr(0, var27) + "\n" + var1.internalText.substr(var27);
                  var1.SetText(var28);
                  var1.TextEntryCursorPos = var27 + 1;
               }

               var1.ToSelectionIndex = var1.TextEntryCursorPos;
               var1.CursorLine = var1.toDisplayLine(var1.TextEntryCursorPos);
            }
         } else {
            var1.onCommandEntered();
         }

         if (var17 && (!GameClient.bClient || GameClient.connection.accessLevel != 1 || GameClient.connection != nullptr && GameClient.connection.isCoopHost)) {
            UIManager.getDebugConsole().ProcessCommand();
         }
      } else if (var2 == 1) {
         var1.onOtherKey(1);
         GameKeyboard.eatKeyPress(1);
      } else if (var2 == 15) {
         var1.onOtherKey(15);
         LuaEventManager.triggerEvent("SwitchChatStream");
      } else if (var2 != 58) {
         if (var2 == 199) {
            var1.TextEntryCursorPos = 0;
            if (!var1.Lines.empty()) {
               var1.TextEntryCursorPos = var1.TextOffsetOfLineStart.get(var1.CursorLine);
            }

            if (!var4) {
               var1.ToSelectionIndex = var1.TextEntryCursorPos;
            }

            var1.resetBlink();
         } else if (var2 == 207) {
            var1.TextEntryCursorPos = var1.internalText.length();
            if (!var1.Lines.empty()) {
               var1.TextEntryCursorPos = var1.TextOffsetOfLineStart.get(var1.CursorLine) + ((std::string)var1.Lines.get(var1.CursorLine)).length();
            }

            if (!var4) {
               var1.ToSelectionIndex = var1.TextEntryCursorPos;
            }

            var1.resetBlink();
         } else if (var2 == 200) {
            if (var1.CursorLine > 0) {
    int var16 = var1.TextEntryCursorPos - var1.TextOffsetOfLineStart.get(var1.CursorLine);
               var1.CursorLine--;
               if (var16 > ((std::string)var1.Lines.get(var1.CursorLine)).length()) {
                  var16 = ((std::string)var1.Lines.get(var1.CursorLine)).length();
               }

               var1.TextEntryCursorPos = var1.TextOffsetOfLineStart.get(var1.CursorLine) + var16;
               if (!var4) {
                  var1.ToSelectionIndex = var1.TextEntryCursorPos;
               }
            }

            var1.onPressUp();
         } else if (var2 == 208) {
            if (var1.Lines.size() - 1 > var1.CursorLine && var1.CursorLine + 1 < var1.getMaxLines()) {
    int var15 = var1.TextEntryCursorPos - var1.TextOffsetOfLineStart.get(var1.CursorLine);
               var1.CursorLine++;
               if (var15 > ((std::string)var1.Lines.get(var1.CursorLine)).length()) {
                  var15 = ((std::string)var1.Lines.get(var1.CursorLine)).length();
               }

               var1.TextEntryCursorPos = var1.TextOffsetOfLineStart.get(var1.CursorLine) + var15;
               if (!var4) {
                  var1.ToSelectionIndex = var1.TextEntryCursorPos;
               }
            }

            var1.onPressDown();
         } else if (var2 != 29) {
            if (var2 != 157) {
               if (var2 != 42) {
                  if (var2 != 54) {
                     if (var2 != 56) {
                        if (var2 != 184) {
                           if (var2 == 203) {
                              var1.TextEntryCursorPos--;
                              if (var1.TextEntryCursorPos < 0) {
                                 var1.TextEntryCursorPos = 0;
                              }

                              if (!var4) {
                                 var1.ToSelectionIndex = var1.TextEntryCursorPos;
                              }

                              var1.resetBlink();
                           } else if (var2 == 205) {
                              var1.TextEntryCursorPos++;
                              if (var1.TextEntryCursorPos > var1.internalText.length()) {
                                 var1.TextEntryCursorPos = var1.internalText.length();
                              }

                              if (!var4) {
                                 var1.ToSelectionIndex = var1.TextEntryCursorPos;
                              }

                              var1.resetBlink();
                           } else if (!this.isFunctionKey(var2)) {
                              if ((var2 == 211 || var2 == 14) && var1.TextEntryCursorPos != var1.ToSelectionIndex) {
    int var14 = Math.min(var1.TextEntryCursorPos, var1.ToSelectionIndex);
    int var22 = Math.max(var1.TextEntryCursorPos, var1.ToSelectionIndex);
                                 var1.internalText = var1.internalText.substr(0, var14) + var1.internalText.substr(var22);
                                 var1.CursorLine = var1.toDisplayLine(var14);
                                 var1.ToSelectionIndex = var14;
                                 var1.TextEntryCursorPos = var14;
                                 var1.onTextChange();
                              } else if (var2 == 211) {
                                 if (var1.internalText.length() != 0 && var1.TextEntryCursorPos < var1.internalText.length()) {
                                    if (var1.TextEntryCursorPos > 0) {
                                       var1.internalText = var1.internalText.substr(0, var1.TextEntryCursorPos)
                                          + var1.internalText.substr(var1.TextEntryCursorPos + 1);
                                    } else {
                                       var1.internalText = var1.internalText.substr(1);
                                    }

                                    var1.onTextChange();
                                 }
                              } else if (var2 == 14) {
                                 if (var1.internalText.length() != 0 && var1.TextEntryCursorPos > 0) {
                                    if (var1.TextEntryCursorPos > var1.internalText.length()) {
                                       var1.internalText = var1.internalText.substr(0, var1.internalText.length() - 1);
                                    } else {
    int var13 = var1.TextEntryCursorPos;
                                       var1.internalText = var1.internalText.substr(0, var13 - 1) + var1.internalText.substr(var13);
                                    }

                                    var1.TextEntryCursorPos--;
                                    var1.ToSelectionIndex = var1.TextEntryCursorPos;
                                    var1.onTextChange();
                                 }
                              } else if (var3 && var2 == 47) {
    std::string var12 = Clipboard.getClipboard();
                                 if (var12 != nullptr) {
                                    if (var1.TextEntryCursorPos != var1.ToSelectionIndex) {
    int var21 = Math.min(var1.TextEntryCursorPos, var1.ToSelectionIndex);
    int var25 = Math.max(var1.TextEntryCursorPos, var1.ToSelectionIndex);
                                       var1.internalText = var1.internalText.substr(0, var21) + var12 + var1.internalText.substr(var25);
                                       var1.ToSelectionIndex = var21 + var12.length();
                                       var1.TextEntryCursorPos = var21 + var12.length();
                                    } else {
                                       if (var1.TextEntryCursorPos < var1.internalText.length()) {
                                          var1.internalText = var1.internalText.substr(0, var1.TextEntryCursorPos)
                                             + var12
                                             + var1.internalText.substr(var1.TextEntryCursorPos);
                                       } else {
                                          var1.internalText = var1.internalText + var12;
                                       }

                                       var1.TextEntryCursorPos = var1.TextEntryCursorPos + var12.length();
                                       var1.ToSelectionIndex = var1.ToSelectionIndex + var12.length();
                                    }

                                    var1.onTextChange();
                                 }
                              } else if (var3 && var2 == 46) {
                                 if (var1.TextEntryCursorPos != var1.ToSelectionIndex) {
                                    var1.updateText();
    int var11 = Math.min(var1.TextEntryCursorPos, var1.ToSelectionIndex);
    int var20 = Math.max(var1.TextEntryCursorPos, var1.ToSelectionIndex);
    std::string var24 = var1.Text.substr(var11, var20);
                                    if (var24 != nullptr && var24.length() > 0) {
                                       Clipboard.setClipboard(var24);
                                    }
                                 }
                              } else if (var3 && var2 == 45) {
                                 if (var1.TextEntryCursorPos != var1.ToSelectionIndex) {
                                    var1.updateText();
    int var10 = Math.min(var1.TextEntryCursorPos, var1.ToSelectionIndex);
    int var19 = Math.max(var1.TextEntryCursorPos, var1.ToSelectionIndex);
    std::string var23 = var1.Text.substr(var10, var19);
                                    if (var23 != nullptr && var23.length() > 0) {
                                       Clipboard.setClipboard(var23);
                                    }

                                    var1.internalText = var1.internalText.substr(0, var10) + var1.internalText.substr(var19);
                                    var1.ToSelectionIndex = var10;
                                    var1.TextEntryCursorPos = var10;
                                 }
                              } else if (var3 && var2 == 30) {
                                 var1.selectAll();
                              } else if (!var1.ignoreFirst) {
                                 if (var1.internalText.length() < var1.TextEntryMaxLength) {
    char var5 = Keyboard.getEventCharacter();
                                    if (var5 != 0) {
                                       if (var1.isOnlyNumbers() && var5 != '.' && var5 != '-') {
                                          try {
                                             double.parseDouble(std::string.valueOf(var5));
                                          } catch (Exception var9) {
                                             return;
                                          }
                                       }

                                       if (var1.TextEntryCursorPos == var1.ToSelectionIndex) {
    int var6 = var1.TextEntryCursorPos;
                                          if (var6 < var1.internalText.length()) {
                                             var1.internalText = var1.internalText.substr(0, var6) + var5 + var1.internalText.substr(var6);
                                          } else {
                                             var1.internalText = var1.internalText + var5;
                                          }

                                          var1.TextEntryCursorPos++;
                                          var1.ToSelectionIndex++;
                                          var1.onTextChange();
                                       } else {
    int var18 = Math.min(var1.TextEntryCursorPos, var1.ToSelectionIndex);
    int var7 = Math.max(var1.TextEntryCursorPos, var1.ToSelectionIndex);
                                          if (var1.internalText.length() > 0) {
                                             var1.internalText = var1.internalText.substr(0, var18) + var5 + var1.internalText.substr(var7);
                                          } else {
                                             var1.internalText = var5 + "";
                                          }

                                          var1.ToSelectionIndex = var18 + 1;
                                          var1.TextEntryCursorPos = var18 + 1;
                                          var1.onTextChange();
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
      if (this.isDoingTextEntry()) {
         while (Keyboard.next()) {
            if (this.isDoingTextEntry() && Keyboard.getEventKeyState()) {
    int var1 = Keyboard.getEventKey();
               this.updateKeyboardAux(CurrentTextEntryBox, var1);
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
            this.saveOptions();
         } catch (IOException var2) {
            var2.printStackTrace();
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

    bool supportRes(int var1, int var2) {
      DisplayMode[] var3 = Display.getAvailableDisplayModes();
    bool var4 = false;

      for (int var5 = 0; var5 < var3.length; var5++) {
         if (var3[var5].getWidth() == var1 && var3[var5].getHeight() == var2 && var3[var5].isFullscreenCapable()) {
    return true;
         }
      }

    return false;
   }

    void init(int var1, int var2) {
      System.setProperty("org.lwjgl.opengl.Window.undecorated", OptionBorderlessWindow ? "true" : "false");
      if (!System.getProperty("os.name").contains("OS X") && !System.getProperty("os.name").startsWith("Win")) {
         DebugLog.log("Creating display. If this fails, you may need to install xrandr.");
      }

      setDisplayMode(var1, var2, fullScreen);

      try {
         Display.create(std::make_shared<PixelFormat>(32, 0, 24, 8, 0));
      } catch (LWJGLException var4) {
         Display.destroy();
         Display.setDisplayModeAndFullscreen(Display.getDesktopDisplayMode());
         Display.create(std::make_shared<PixelFormat>(32, 0, 24, 8, 0));
      }

      fullScreen = Display.isFullscreen();
      DebugLog.log("GraphicsCard: " + GL11.glGetString(7936) + " " + GL11.glGetString(7937));
      DebugLog.log("OpenGL version: " + GL11.glGetString(7938));
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
         if (!this.OffscreenBuffer.test()) {
    return false;
         } else {
            this.OffscreenBuffer.setZoomLevelsFromOption(TileScale == 2 ? OptionZoomLevels2x : OptionZoomLevels1x);
            this.OffscreenBuffer.create(Display.getWidth(), Display.getHeight());
    return true;
         }
      } catch (Exception var2) {
         var2.printStackTrace();
    return false;
      }
   }

    void setScreenSize(int var1, int var2) {
      if (width != var1 || var2 != height) {
    int var3 = width;
    int var4 = height;
         DebugLog.log("Screen resolution changed from " + var3 + "x" + var4 + " to " + var1 + "x" + var2 + " fullScreen=" + fullScreen);
         width = var1;
         height = var2;
         if (this.OffscreenBuffer != nullptr && this.OffscreenBuffer.Current != nullptr) {
            this.OffscreenBuffer.destroy();

            try {
               this.OffscreenBuffer.setZoomLevelsFromOption(TileScale == 2 ? OptionZoomLevels2x : OptionZoomLevels1x);
               this.OffscreenBuffer.create(var1, var2);
            } catch (Exception var8) {
               var8.printStackTrace();
            }
         }

         try {
            LuaEventManager.triggerEvent("OnResolutionChange", var3, var4, var1, var2);
         } catch (Exception var7) {
            var7.printStackTrace();
         }

         for (int var5 = 0; var5 < IsoPlayer.numPlayers; var5++) {
    IsoPlayer var6 = IsoPlayer.players[var5];
            if (var6 != nullptr) {
               var6.dirtyRecalcGridStackTime = 2.0F;
            }
         }
      }
   }

    static bool supportCompressedTextures() {
      return GL.getCapabilities().GL_EXT_texture_compression_latc;
   }

    void StartFrame() {
      if (LuaManager.thread == nullptr || !LuaManager.thread.bStep) {
         if (this.RenderShader != nullptr && this.OffscreenBuffer.Current != nullptr) {
            this.RenderShader.setTexture(this.OffscreenBuffer.getTexture(0));
         }

         SpriteRenderer.instance.prePopulating();
         UIManager.resize();
    bool var1 = false;
         Texture.BindCount = 0;
         if (!var1) {
            IndieGL.glClear(18176);
            if (DebugOptions.instance.Terrain.RenderTiles.HighContrastBg.getValue()) {
               SpriteRenderer.instance.glClearColor(255, 0, 255, 255);
               SpriteRenderer.instance.glClear(16384);
            }
         }

         if (this.OffscreenBuffer.Current != nullptr) {
            SpriteRenderer.instance.glBuffer(1, 0);
         }

         IndieGL.glDoStartFrame(this.getScreenWidth(), this.getScreenWidth(), this.getCurrentPlayerZoom(), 0);
         this.frameStage = 1;
      }
   }

    void StartFrame(int var1, bool var2) {
      if (!LuaManager.thread.bStep) {
         this.OffscreenBuffer.update();
         if (this.RenderShader != nullptr && this.OffscreenBuffer.Current != nullptr) {
            this.RenderShader.setTexture(this.OffscreenBuffer.getTexture(var1));
         }

         if (var2) {
            SpriteRenderer.instance.prePopulating();
         }

         if (!var2) {
            SpriteRenderer.instance.initFromIsoCamera(var1);
         }

         Texture.BindCount = 0;
         IndieGL.glLoadIdentity();
         if (this.OffscreenBuffer.Current != nullptr) {
            SpriteRenderer.instance.glBuffer(1, var1);
         }

         IndieGL.glDoStartFrame(this.getScreenWidth(), this.getScreenHeight(), this.getZoom(var1), var1);
         IndieGL.glClear(17664);
         if (DebugOptions.instance.Terrain.RenderTiles.HighContrastBg.getValue()) {
            SpriteRenderer.instance.glClearColor(255, 0, 255, 255);
            SpriteRenderer.instance.glClear(16384);
         }

         this.frameStage = 1;
      }
   }

    TextureFBO getOffscreenBuffer() {
      return this.OffscreenBuffer.getCurrent(0);
   }

    TextureFBO getOffscreenBuffer(int var1) {
      return this.OffscreenBuffer.getCurrent(var1);
   }

    void setLastRenderedFBO(TextureFBO var1) {
      this.OffscreenBuffer.FBOrendered = var1;
   }

    void DoStartFrameStuff(int var1, int var2, float var3, int var4) {
      this.DoStartFrameStuff(var1, var2, var3, var4, false);
   }

    void DoStartFrameStuff(int var1, int var2, float var3, int var4, bool var5) {
      this.DoStartFrameStuffInternal(var1, var2, var3, var4, var5, false, false);
   }

    void DoEndFrameStuffFx(int var1, int var2, int var3) {
      GL11.glPopAttrib();
      this.stack--;
      GL11.glMatrixMode(5889);
      GL11.glPopMatrix();
      this.stack--;
      GL11.glMatrixMode(5888);
      GL11.glLoadIdentity();
   }

    void DoStartFrameStuffSmartTextureFx(int var1, int var2, int var3) {
      this.DoStartFrameStuffInternal(var1, var2, 1.0F, var3, false, true, true);
   }

    void DoStartFrameStuffInternal(int var1, int var2, float var3, int var4, bool var5, bool var6, bool var7) {
      GL32.glEnable(3042);
      GL32.glDepthFunc(519);
    int var8 = this.getScreenWidth();
    int var9 = this.getScreenHeight();
      if (!var7 && !var6) {
         var1 = var8;
      }

      if (!var7 && !var6) {
         var2 = var9;
      }

      if (!var7 && var4 != -1) {
         var1 /= IsoPlayer.numPlayers > 1 ? 2 : 1;
         var2 /= IsoPlayer.numPlayers > 2 ? 2 : 1;
      }

      GL32.glMatrixMode(5889);
      if (!var6) {
         while (this.stack > 0) {
            try {
               GL11.glPopMatrix();
               GL11.glPopAttrib();
               this.stack -= 2;
            } catch (OpenGLException var16) {
    int var11 = GL11.glGetInteger(2992);

               while (var11-- > 0) {
                  GL11.glPopAttrib();
               }

    int var12 = GL11.glGetInteger(2980);

               while (var12-- > 1) {
                  GL11.glPopMatrix();
               }

               this.stack = 0;
            }
         }
      }

      GL11.glAlphaFunc(516, 0.0F);
      GL11.glPushAttrib(2048);
      this.stack++;
      GL11.glPushMatrix();
      this.stack++;
      GL11.glLoadIdentity();
      if (!var7 && !var5) {
         GLU.gluOrtho2D(0.0F, var1 * var3, var2 * var3, 0.0F);
      } else {
         GLU.gluOrtho2D(0.0F, var1, var2, 0.0F);
      }

      GL11.glMatrixMode(5888);
      GL11.glLoadIdentity();
      if (var4 != -1) {
    int var18 = var1;
    int var13 = var2;
    int var10;
    int var17;
         if (var5) {
            var10 = var1;
            var17 = var2;
         } else {
            var10 = var8;
            var17 = var9;
            if (IsoPlayer.numPlayers > 1) {
               var10 = var8 / 2;
            }

            if (IsoPlayer.numPlayers > 2) {
               var17 = var9 / 2;
            }
         }

         if (var6) {
            var18 = var10;
            var13 = var17;
         }

    float var14 = 0.0F;
    float var15 = var10 * (var4 % 2);
         if (var4 >= 2) {
            var14 += var17;
         }

         if (var5) {
            var14 = getInstance().getScreenHeight() - var13 - var14;
         }

         GL11.glViewport((int)var15, (int)var14, var18, var13);
         GL11.glEnable(3089);
         GL11.glScissor((int)var15, (int)var14, var18, var13);
         SpriteRenderer.instance.setRenderingPlayerIndex(var4);
      } else {
         GL11.glViewport(0, 0, var1, var2);
      }
   }

    void DoPushIsoStuff(float var1, float var2, float var3, float var4, bool var5) {
    float var6 = getInstance().FloatParamMap.get(0);
    float var7 = getInstance().FloatParamMap.get(1);
    float var8 = getInstance().FloatParamMap.get(2);
    double var9 = var6;
    double var11 = var7;
    double var13 = var8;
    SpriteRenderState var15 = SpriteRenderer.instance.getRenderingState();
    int var16 = var15.playerIndex;
    PlayerCamera var17 = var15.playerCamera[var16];
    float var18 = var17.RightClickX;
    float var19 = var17.RightClickY;
    float var20 = var17.getTOffX();
    float var21 = var17.getTOffY();
    float var22 = var17.DeferedX;
    float var23 = var17.DeferedY;
      var9 -= var17.XToIso(-var20 - var18, -var21 - var19, 0.0F);
      var11 -= var17.YToIso(-var20 - var18, -var21 - var19, 0.0F);
      var9 += var22;
      var11 += var23;
    double var24 = var17.OffscreenWidth / 1920.0F;
    double var26 = var17.OffscreenHeight / 1920.0F;
    Matrix4f var28 = this.tempMatrix4f;
      var28.setOrtho(-((float)var24) / 2.0F, (float)var24 / 2.0F, -((float)var26) / 2.0F, (float)var26 / 2.0F, -10.0F, 10.0F);
      PZGLUtil.pushAndLoadMatrix(5889, var28);
    Matrix4f var29 = this.tempMatrix4f;
    float var30 = (float)(2.0 / Math.sqrt(2048.0));
      var29.scaling(0.047085002F);
      var29.scale(TileScale / 2.0F);
      var29.rotate((float) (Math.PI / 6), 1.0F, 0.0F, 0.0F);
      var29.rotate((float) (Math.PI * 3.0 / 4.0), 0.0F, 1.0F, 0.0F);
    double var31 = var1 - var9;
    double var33 = var2 - var11;
      var29.translate(-((float)var31), (float)(var3 - var13) * 2.5F, -((float)var33));
      if (var5) {
         var29.scale(-1.0F, 1.0F, 1.0F);
      } else {
         var29.scale(-1.5F, 1.5F, 1.5F);
      }

      var29.rotate(var4 + (float) Math.PI, 0.0F, 1.0F, 0.0F);
      if (!var5) {
         var29.translate(0.0F, -0.48F, 0.0F);
      }

      PZGLUtil.pushAndLoadMatrix(5888, var29);
      GL11.glDepthRange(0.0, 1.0);
   }

    void DoPushIsoParticleStuff(float var1, float var2, float var3) {
      GL11.glMatrixMode(5889);
      GL11.glPushMatrix();
    float var4 = getInstance().FloatParamMap.get(0);
    float var5 = getInstance().FloatParamMap.get(1);
    float var6 = getInstance().FloatParamMap.get(2);
      GL11.glLoadIdentity();
    double var7 = var4;
    double var9 = var5;
    double var11 = var6;
    double var13 = Math.abs(getInstance().getOffscreenWidth(0)) / 1920.0F;
    double var15 = Math.abs(getInstance().getOffscreenHeight(0)) / 1080.0F;
      GL11.glLoadIdentity();
      GL11.glOrtho(-var13 / 2.0, var13 / 2.0, -var15 / 2.0, var15 / 2.0, -10.0, 10.0);
      GL11.glMatrixMode(5888);
      GL11.glPushMatrix();
      GL11.glLoadIdentity();
      GL11.glScaled(0.047085002F, 0.047085002F, 0.047085002F);
      GL11.glRotatef(62.65607F, 1.0F, 0.0F, 0.0F);
      GL11.glTranslated(0.0, -2.72F, 0.0);
      GL11.glRotatef(135.0F, 0.0F, 1.0F, 0.0F);
      GL11.glScalef(1.7099999F, 14.193F, 1.7099999F);
      GL11.glScalef(0.59F, 0.59F, 0.59F);
      GL11.glTranslated(-(var1 - var7), var3 - var11, -(var2 - var9));
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

    void DoEndFrameStuff(int var1, int var2) {
      try {
         GL11.glPopAttrib();
         this.stack--;
         GL11.glMatrixMode(5889);
         GL11.glPopMatrix();
         this.stack--;
      } catch (Exception var6) {
    int var4 = GL11.glGetInteger(2992);

         while (var4-- > 0) {
            GL11.glPopAttrib();
         }

         GL11.glMatrixMode(5889);
    int var5 = GL11.glGetInteger(2980);

         while (var5-- > 1) {
            GL11.glPopMatrix();
         }

         this.stack = 0;
      }

      GL11.glMatrixMode(5888);
      GL11.glLoadIdentity();
      GL11.glDisable(3089);
   }

    void RenderOffScreenBuffer() {
      if (LuaManager.thread == nullptr || !LuaManager.thread.bStep) {
         if (this.OffscreenBuffer.Current != nullptr) {
            IndieGL.disableStencilTest();
            IndieGL.glDoStartFrame(width, height, 1.0F, -1);
            IndieGL.glDisable(3042);
            this.OffscreenBuffer.render();
            IndieGL.glDoEndFrame();
         }
      }
   }

    void StartFrameText(int var1) {
      if (LuaManager.thread == nullptr || !LuaManager.thread.bStep) {
         IndieGL.glDoStartFrame(IsoCamera.getScreenWidth(var1), IsoCamera.getScreenHeight(var1), 1.0F, var1, true);
         this.frameStage = 2;
      }
   }

    bool StartFrameUI() {
      if (LuaManager.thread != nullptr && LuaManager.thread.bStep) {
    return false;
      } else {
    bool var1 = true;
         if (UIManager.useUIFBO) {
            if (UIManager.defaultthread == LuaManager.debugthread) {
               this.UIRenderThisFrame = true;
            } else {
               this.UIRenderAccumulator = this.UIRenderAccumulator + GameTime.getInstance().getMultiplier() / 1.6F;
               this.UIRenderThisFrame = this.UIRenderAccumulator >= 30.0F / OptionUIRenderFPS;
            }

            if (this.UIRenderThisFrame) {
               SpriteRenderer.instance.startOffscreenUI();
               SpriteRenderer.instance.glBuffer(2, 0);
            } else {
               var1 = false;
            }
         }

         IndieGL.glDoStartFrame(width, height, 1.0F, -1);
         IndieGL.glClear(1024);
         UIManager.resize();
         this.frameStage = 3;
    return var1;
      }
   }

   public Map<std::string, int> getKeyMaps() {
      return this.keyMaps;
   }

    void setKeyMaps(int> var1) {
      this.keyMaps = var1;
   }

    void reinitKeyMaps() {
      this.keyMaps = std::make_unique<std::unordered_map<>>();
   }

    int getKey(const std::string& var1) {
      if (this.keyMaps == nullptr) {
    return 0;
      } else {
         return this.keyMaps.get(var1) != nullptr ? this.keyMaps.get(var1) : 0;
      }
   }

    void addKeyBinding(const std::string& var1, int var2) {
      if (this.keyMaps == nullptr) {
         this.keyMaps = std::make_unique<std::unordered_map<>>();
      }

      this.keyMaps.put(var1, var2);
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
      return this.steamServerVersion;
   }

    void DoFrameReady() {
      this.updateKeyboard();
   }

    float getCurrentPlayerZoom() {
    int var1 = IsoCamera.frameState.playerIndex;
      return this.getZoom(var1);
   }

    float getZoom(int var1) {
      return this.OffscreenBuffer != nullptr ? this.OffscreenBuffer.zoom[var1] * (TileScale / 2.0F) : 1.0F;
   }

    float getNextZoom(int var1, int var2) {
      return this.OffscreenBuffer != nullptr ? this.OffscreenBuffer.getNextZoom(var1, var2) : 1.0F;
   }

    float getMinZoom() {
      return this.OffscreenBuffer != nullptr ? this.OffscreenBuffer.getMinZoom() * (TileScale / 2.0F) : 1.0F;
   }

    float getMaxZoom() {
      return this.OffscreenBuffer != nullptr ? this.OffscreenBuffer.getMaxZoom() * (TileScale / 2.0F) : 1.0F;
   }

    void doZoomScroll(int var1, int var2) {
      if (this.OffscreenBuffer != nullptr) {
         this.OffscreenBuffer.doZoomScroll(var1, var2);
      }
   }

    std::string getSaveFolder() {
      return this.saveFolder;
   }

    bool getOptionZoom() {
    return OptionZoom;
   }

    void setOptionZoom(bool var1) {
      OptionZoom = var1;
   }

    void zoomOptionChanged(bool var1) {
      if (var1) {
         RenderThread.invokeOnRenderContext(() -> {
            if (OptionZoom && !SafeModeForced) {
               SafeMode = false;
               this.bSupportsFBO = true;
               this.OffscreenBuffer.bZoomEnabled = true;
               this.supportsFBO();
            } else {
               this.OffscreenBuffer.destroy();
               SafeMode = true;
               this.bSupportsFBO = false;
               this.OffscreenBuffer.bZoomEnabled = false;
            }
         });
         DebugLog.log("SafeMode is " + (SafeMode ? "on" : "off"));
      } else {
         SafeMode = SafeModeForced;
         this.OffscreenBuffer.bZoomEnabled = OptionZoom && !SafeModeForced;
      }
   }

    void zoomLevelsChanged() {
      if (this.OffscreenBuffer.Current != nullptr) {
         RenderThread.invokeOnRenderContext(() -> {
            this.OffscreenBuffer.destroy();
            this.zoomOptionChanged(true);
         });
      }
   }

    bool isZoomEnabled() {
      return this.OffscreenBuffer.bZoomEnabled;
   }

    void initFBOs() {
      if (OptionZoom && !SafeModeForced) {
         RenderThread.invokeOnRenderContext(this::supportsFBO);
      } else {
         SafeMode = true;
         this.OffscreenBuffer.bZoomEnabled = false;
      }

      DebugLog.log("SafeMode is " + (SafeMode ? "on" : "off"));
   }

    bool getAutoZoom(int var1) {
      return bAutoZoom[var1];
   }

    void setAutoZoom(int var1, bool var2) {
      bAutoZoom[var1] = var2;
      if (this.OffscreenBuffer != nullptr) {
         this.OffscreenBuffer.bAutoZoom[var1] = var2;
      }
   }

    bool getOptionVSync() {
    return OptionVSync;
   }

    void setOptionVSync(bool var1) {
      OptionVSync = var1;
      RenderThread.invokeOnRenderContext(() -> Display.setVSyncEnabled(var1));
   }

    int getOptionSoundVolume() {
    return OptionSoundVolume;
   }

    float getRealOptionSoundVolume() {
      return OptionSoundVolume / 10.0F;
   }

    void setOptionSoundVolume(int var1) {
      OptionSoundVolume = Math.max(0, Math.min(10, var1));
      if (SoundManager.instance != nullptr) {
         SoundManager.instance.setSoundVolume(var1 / 10.0F);
      }
   }

    int getOptionMusicVolume() {
    return OptionMusicVolume;
   }

    void setOptionMusicVolume(int var1) {
      OptionMusicVolume = Math.max(0, Math.min(10, var1));
      if (SoundManager.instance != nullptr) {
         SoundManager.instance.setMusicVolume(var1 / 10.0F);
      }
   }

    int getOptionAmbientVolume() {
    return OptionAmbientVolume;
   }

    void setOptionAmbientVolume(int var1) {
      OptionAmbientVolume = Math.max(0, Math.min(10, var1));
      if (SoundManager.instance != nullptr) {
         SoundManager.instance.setAmbientVolume(var1 / 10.0F);
      }
   }

    int getOptionJumpScareVolume() {
    return OptionJumpScareVolume;
   }

    void setOptionJumpScareVolume(int var1) {
      OptionJumpScareVolume = PZMath.clamp(var1, 0, 10);
   }

    int getOptionMusicActionStyle() {
    return OptionMusicActionStyle;
   }

    void setOptionMusicActionStyle(int var1) {
      OptionMusicActionStyle = PZMath.clamp(var1, 1, 2);
   }

    int getOptionMusicLibrary() {
    return OptionMusicLibrary;
   }

    void setOptionMusicLibrary(int var1) {
      if (var1 < 1) {
         var1 = 1;
      }

      if (var1 > 3) {
         var1 = 3;
      }

      OptionMusicLibrary = var1;
   }

    int getOptionVehicleEngineVolume() {
    return OptionVehicleEngineVolume;
   }

    void setOptionVehicleEngineVolume(int var1) {
      OptionVehicleEngineVolume = Math.max(0, Math.min(10, var1));
      if (SoundManager.instance != nullptr) {
         SoundManager.instance.setVehicleEngineVolume(OptionVehicleEngineVolume / 10.0F);
      }
   }

    bool getOptionVoiceEnable() {
    return OptionVoiceEnable;
   }

    void setOptionVoiceEnable(bool var1) {
      if (OptionVoiceEnable != var1) {
         OptionVoiceEnable = var1;
         VoiceManager.instance.VoiceRestartClient(var1);
      }
   }

    int getOptionVoiceMode() {
    return OptionVoiceMode;
   }

    void setOptionVoiceMode(int var1) {
      OptionVoiceMode = var1;
      VoiceManager.instance.setMode(var1);
   }

    int getOptionVoiceVADMode() {
    return OptionVoiceVADMode;
   }

    void setOptionVoiceVADMode(int var1) {
      OptionVoiceVADMode = var1;
      VoiceManager.instance.setVADMode(var1);
   }

    int getOptionVoiceAGCMode() {
    return OptionVoiceAGCMode;
   }

    void setOptionVoiceAGCMode(int var1) {
      OptionVoiceAGCMode = var1;
      VoiceManager.instance.setAGCMode(var1);
   }

    int getOptionVoiceVolumeMic() {
    return OptionVoiceVolumeMic;
   }

    void setOptionVoiceVolumeMic(int var1) {
      OptionVoiceVolumeMic = var1;
      VoiceManager.instance.setVolumeMic(var1);
   }

    int getOptionVoiceVolumePlayers() {
    return OptionVoiceVolumePlayers;
   }

    void setOptionVoiceVolumePlayers(int var1) {
      OptionVoiceVolumePlayers = var1;
      VoiceManager.instance.setVolumePlayers(var1);
   }

    std::string getOptionVoiceRecordDeviceName() {
    return OptionVoiceRecordDeviceName;
   }

    void setOptionVoiceRecordDeviceName(const std::string& var1) {
      OptionVoiceRecordDeviceName = var1;
      VoiceManager.instance.UpdateRecordDevice();
   }

    int getOptionVoiceRecordDevice() {
      if (!SoundDisabled && !VoiceManager.VoipDisabled) {
    int var1 = javafmod.FMOD_System_GetRecordNumDrivers();

         for (int var2 = 0; var2 < var1; var2++) {
    FMOD_DriverInfo var3 = std::make_shared<FMOD_DriverInfo>();
            javafmod.FMOD_System_GetRecordDriverInfo(var2, var3);
            if (var3.name == OptionVoiceRecordDeviceName)) {
               return var2 + 1;
            }
         }

    return 0;
      } else {
    return 0;
      }
   }

    void setOptionVoiceRecordDevice(int var1) {
      if (!SoundDisabled && !VoiceManager.VoipDisabled) {
         if (var1 >= 1) {
    FMOD_DriverInfo var2 = std::make_shared<FMOD_DriverInfo>();
            javafmod.FMOD_System_GetRecordDriverInfo(var1 - 1, var2);
            OptionVoiceRecordDeviceName = var2.name;
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

    void setTestingMicrophone(bool var1) {
      VoiceManager.instance.setTestingMicrophone(var1);
   }

    int getOptionReloadDifficulty() {
    return 2;
   }

    void setOptionReloadDifficulty(int var1) {
      OptionReloadDifficulty = Math.max(1, Math.min(3, var1));
   }

    bool getOptionRackProgress() {
    return OptionRackProgress;
   }

    void setOptionRackProgress(bool var1) {
      OptionRackProgress = var1;
   }

    int getOptionFontSize() {
    return OptionFontSize;
   }

    void setOptionFontSize(int var1) {
      OptionFontSize = PZMath.clamp(var1, 1, 5);
   }

    std::string getOptionContextMenuFont() {
    return OptionContextMenuFont;
   }

    void setOptionContextMenuFont(const std::string& var1) {
      OptionContextMenuFont = var1;
   }

    std::string getOptionInventoryFont() {
    return OptionInventoryFont;
   }

    void setOptionInventoryFont(const std::string& var1) {
      OptionInventoryFont = var1;
   }

    int getOptionInventoryContainerSize() {
    return OptionInventoryContainerSize;
   }

    void setOptionInventoryContainerSize(int var1) {
      OptionInventoryContainerSize = var1;
   }

    std::string getOptionTooltipFont() {
    return OptionTooltipFont;
   }

    void setOptionTooltipFont(const std::string& var1) {
      OptionTooltipFont = var1;
      ObjectTooltip.checkFont();
   }

    std::string getOptionMeasurementFormat() {
    return OptionMeasurementFormat;
   }

    void setOptionMeasurementFormat(const std::string& var1) {
      OptionMeasurementFormat = var1;
   }

    int getOptionClockFormat() {
    return OptionClockFormat;
   }

    int getOptionClockSize() {
    return OptionClockSize;
   }

    void setOptionClockFormat(int var1) {
      if (var1 < 1) {
         var1 = 1;
      }

      if (var1 > 2) {
         var1 = 2;
      }

      OptionClockFormat = var1;
   }

    void setOptionClockSize(int var1) {
      if (var1 < 1) {
         var1 = 1;
      }

      if (var1 > 2) {
         var1 = 2;
      }

      OptionClockSize = var1;
   }

    bool getOptionClock24Hour() {
    return OptionClock24Hour;
   }

    void setOptionClock24Hour(bool var1) {
      OptionClock24Hour = var1;
   }

    bool getOptionModsEnabled() {
    return OptionModsEnabled;
   }

    void setOptionModsEnabled(bool var1) {
      OptionModsEnabled = var1;
   }

    int getOptionBloodDecals() {
    return OptionBloodDecals;
   }

    void setOptionBloodDecals(int var1) {
      if (var1 < 0) {
         var1 = 0;
      }

      if (var1 > 10) {
         var1 = 10;
      }

      OptionBloodDecals = var1;
   }

    bool getOptionBorderlessWindow() {
    return OptionBorderlessWindow;
   }

    void setOptionBorderlessWindow(bool var1) {
      OptionBorderlessWindow = var1;
   }

    bool getOptionLockCursorToWindow() {
    return OptionLockCursorToWindow;
   }

    void setOptionLockCursorToWindow(bool var1) {
      OptionLockCursorToWindow = var1;
   }

    bool getOptionTextureCompression() {
    return OptionTextureCompression;
   }

    void setOptionTextureCompression(bool var1) {
      OptionTextureCompression = var1;
   }

    bool getOptionTexture2x() {
    return OptionTexture2x;
   }

    void setOptionTexture2x(bool var1) {
      OptionTexture2x = var1;
   }

    int getOptionMaxTextureSize() {
    return OptionMaxTextureSize;
   }

    void setOptionMaxTextureSize(int var1) {
      OptionMaxTextureSize = PZMath.clamp(var1, 1, 4);
   }

    int getOptionMaxVehicleTextureSize() {
    return OptionMaxVehicleTextureSize;
   }

    void setOptionMaxVehicleTextureSize(int var1) {
      OptionMaxVehicleTextureSize = PZMath.clamp(var1, 1, 4);
   }

    int getMaxTextureSizeFromFlags(int var1) {
      if ((var1 & 128) != 0) {
         return this.getMaxTextureSize();
      } else {
         return (var1 & 256) != 0 ? this.getMaxVehicleTextureSize() : 32768;
      }
   }

    int getMaxTextureSizeFromOption(int var1) {
    return switch() {
         case 1 -> 256;
         case 2 -> 512;
         case 3 -> 1024;
         case 4 -> 2048;
         default -> throw IllegalStateException("Unexpected value: " + var1);
      };
   }

    int getMaxTextureSize() {
      return this.getMaxTextureSizeFromOption(OptionMaxTextureSize);
   }

    int getMaxVehicleTextureSize() {
      return this.getMaxTextureSizeFromOption(OptionMaxVehicleTextureSize);
   }

    bool getOptionModelTextureMipmaps() {
    return OptionModelTextureMipmaps;
   }

    void setOptionModelTextureMipmaps(bool var1) {
      OptionModelTextureMipmaps = var1;
   }

    std::string getOptionZoomLevels1x() {
    return OptionZoomLevels1x;
   }

    void setOptionZoomLevels1x(const std::string& var1) {
      OptionZoomLevels1x = var1 == nullptr ? "" : var1;
   }

    std::string getOptionZoomLevels2x() {
    return OptionZoomLevels2x;
   }

    void setOptionZoomLevels2x(const std::string& var1) {
      OptionZoomLevels2x = var1 == nullptr ? "" : var1;
   }

   public std::vector<int> getDefaultZoomLevels() {
      return this.OffscreenBuffer.getDefaultZoomLevels();
   }

    void setOptionActiveController(int var1, bool var2) {
      if (var1 >= 0 && var1 < GameWindow.GameInput.getControllerCount()) {
    Controller var3 = GameWindow.GameInput.getController(var1);
         if (var3 != nullptr) {
            JoypadManager.instance.setControllerActive(var3.getGUID(), var2);
         }
      }
   }

    bool getOptionActiveController(const std::string& var1) {
      return JoypadManager.instance.ActiveControllerGUIDs.contains(var1);
   }

    bool isOptionShowChatTimestamp() {
    return OptionShowChatTimestamp;
   }

    void setOptionShowChatTimestamp(bool var1) {
      OptionShowChatTimestamp = var1;
   }

    bool isOptionShowChatTitle() {
    return OptionShowChatTitle;
   }

    std::string getOptionChatFontSize() {
    return OptionChatFontSize;
   }

    void setOptionChatFontSize(const std::string& var1) {
      OptionChatFontSize = var1;
   }

    void setOptionShowChatTitle(bool var1) {
      OptionShowChatTitle = var1;
   }

    float getOptionMinChatOpaque() {
    return OptionMinChatOpaque;
   }

    void setOptionMinChatOpaque(float var1) {
      OptionMinChatOpaque = var1;
   }

    float getOptionMaxChatOpaque() {
    return OptionMaxChatOpaque;
   }

    void setOptionMaxChatOpaque(float var1) {
      OptionMaxChatOpaque = var1;
   }

    float getOptionChatFadeTime() {
    return OptionChatFadeTime;
   }

    void setOptionChatFadeTime(float var1) {
      OptionChatFadeTime = var1;
   }

    bool getOptionChatOpaqueOnFocus() {
    return OptionChatOpaqueOnFocus;
   }

    void setOptionChatOpaqueOnFocus(bool var1) {
      OptionChatOpaqueOnFocus = var1;
   }

    bool getOptionUIFBO() {
    return OptionUIFBO;
   }

    void setOptionUIFBO(bool var1) {
      OptionUIFBO = var1;
      if (GameWindow.states.current == IngameState.instance) {
         UIManager.useUIFBO = getInstance().supportsFBO() && OptionUIFBO;
      }
   }

    int getOptionAimOutline() {
    return OptionAimOutline;
   }

    void setOptionAimOutline(int var1) {
      OptionAimOutline = PZMath.clamp(var1, 1, 3);
   }

    int getOptionUIRenderFPS() {
    return OptionUIRenderFPS;
   }

    void setOptionUIRenderFPS(int var1) {
      OptionUIRenderFPS = var1;
   }

    void setOptionRadialMenuKeyToggle(bool var1) {
      OptionRadialMenuKeyToggle = var1;
   }

    bool getOptionRadialMenuKeyToggle() {
    return OptionRadialMenuKeyToggle;
   }

    void setOptionReloadRadialInstant(bool var1) {
      OptionReloadRadialInstant = var1;
   }

    bool getOptionReloadRadialInstant() {
    return OptionReloadRadialInstant;
   }

    void setOptionPanCameraWhileAiming(bool var1) {
      OptionPanCameraWhileAiming = var1;
   }

    bool getOptionPanCameraWhileAiming() {
    return OptionPanCameraWhileAiming;
   }

    void setOptionPanCameraWhileDriving(bool var1) {
      OptionPanCameraWhileDriving = var1;
   }

    bool getOptionPanCameraWhileDriving() {
    return OptionPanCameraWhileDriving;
   }

    std::string getOptionCycleContainerKey() {
    return OptionCycleContainerKey;
   }

    void setOptionCycleContainerKey(const std::string& var1) {
      OptionCycleContainerKey = var1;
   }

    bool getOptionDropItemsOnSquareCenter() {
    return OptionDropItemsOnSquareCenter;
   }

    void setOptionDropItemsOnSquareCenter(bool var1) {
      OptionDropItemsOnSquareCenter = var1;
   }

    bool getOptionTimedActionGameSpeedReset() {
    return OptionTimedActionGameSpeedReset;
   }

    void setOptionTimedActionGameSpeedReset(bool var1) {
      OptionTimedActionGameSpeedReset = var1;
   }

    int getOptionShoulderButtonContainerSwitch() {
    return OptionShoulderButtonContainerSwitch;
   }

    void setOptionShoulderButtonContainerSwitch(int var1) {
      OptionShoulderButtonContainerSwitch = var1;
   }

    bool getOptionSingleContextMenu(int var1) {
      return OptionSingleContextMenu[var1];
   }

    void setOptionSingleContextMenu(int var1, bool var2) {
      OptionSingleContextMenu[var1] = var2;
   }

    bool getOptionAutoDrink() {
    return OptionAutoDrink;
   }

    void setOptionAutoDrink(bool var1) {
      OptionAutoDrink = var1;
   }

    bool getOptionAutoWalkContainer() {
    return OptionAutoWalkContainer;
   }

    void setOptionAutoWalkContainer(bool var1) {
      OptionAutoWalkContainer = var1;
   }

    bool getOptionCorpseShadows() {
    return OptionCorpseShadows;
   }

    void setOptionCorpseShadows(bool var1) {
      OptionCorpseShadows = var1;
   }

    bool getOptionLeaveKeyInIgnition() {
    return OptionLeaveKeyInIgnition;
   }

    void setOptionLeaveKeyInIgnition(bool var1) {
      OptionLeaveKeyInIgnition = var1;
   }

    int getOptionSearchModeOverlayEffect() {
    return OptionSearchModeOverlayEffect;
   }

    void setOptionSearchModeOverlayEffect(int var1) {
      OptionSearchModeOverlayEffect = var1;
   }

    int getOptionSimpleClothingTextures() {
    return OptionSimpleClothingTextures;
   }

    void setOptionSimpleClothingTextures(int var1) {
      OptionSimpleClothingTextures = PZMath.clamp(var1, 1, 3);
   }

    bool isOptionSimpleClothingTextures(bool var1) {
      switch (OptionSimpleClothingTextures) {
         case 1:
    return false;
         case 2:
    return var1;
         default:
    return true;
      }
   }

    bool getOptionSimpleWeaponTextures() {
    return OptionSimpleWeaponTextures;
   }

    void setOptionSimpleWeaponTextures(bool var1) {
      OptionSimpleWeaponTextures = var1;
   }

    int getOptionIgnoreProneZombieRange() {
    return OptionIgnoreProneZombieRange;
   }

    void setOptionIgnoreProneZombieRange(int var1) {
      OptionIgnoreProneZombieRange = PZMath.clamp(var1, 1, 5);
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

    void readPerPlayerBoolean(const std::string& var1, boolean[] var2) {
      Arrays.fill(var2, false);
      std::string[] var3 = var1.split(",");

      for (int var4 = 0; var4 < var3.length && var4 != 4; var4++) {
         var2[var4] = StringUtils.tryParseBoolean(var3[var4]);
      }
   }

    std::string getPerPlayerBooleanString(boolean[] var1) {
      return std::string.format("%b,%b,%b,%b", var1[0], var1[1], var1[2], var1[3]);
   }

    void ResetLua(bool var1, const std::string& var2) {
      this.ResetLua("default", var2);
   }

    void ResetLua(const std::string& var1, const std::string& var2) {
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
      ZomboidFileSystem.instance.loadMods(var1);
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
      } catch (Exception var6) {
         ExceptionLogger.logException(var6);
         GameWindow.DoLoadingText("Reloading Lua - ERRORS!");

         try {
            Thread.sleep(2000L);
         } catch (InterruptedException var5) {
         }
      }

      ZomboidGlobals.Load();
      RenderThread.setWaitForRenderState(true);
      LuaEventManager.triggerEvent("OnGameBoot");
      LuaEventManager.triggerEvent("OnMainMenuEnter");
      LuaEventManager.triggerEvent("OnResetLua", var2);
   }

    void DelayResetLua(const std::string& var1, const std::string& var2) {
      this.m_delayResetLua_activeMods = var1;
      this.m_delayResetLua_reason = var2;
   }

    void CheckDelayResetLua() {
      if (this.m_delayResetLua_activeMods != nullptr) {
    std::string var1 = this.m_delayResetLua_activeMods;
    std::string var2 = this.m_delayResetLua_reason;
         this.m_delayResetLua_activeMods = nullptr;
         this.m_delayResetLua_reason = nullptr;
         this.ResetLua(var1, var2);
      }
   }

    bool isShowPing() {
      return this.showPing;
   }

    void setShowPing(bool var1) {
      this.showPing = var1;
   }

    bool isForceSnow() {
      return this.forceSnow;
   }

    void setForceSnow(bool var1) {
      this.forceSnow = var1;
   }

    bool isZombieGroupSound() {
      return this.zombieGroupSound;
   }

    void setZombieGroupSound(bool var1) {
      this.zombieGroupSound = var1;
   }

    std::string getBlinkingMoodle() {
      return this.blinkingMoodle;
   }

    void setBlinkingMoodle(const std::string& var1) {
      this.blinkingMoodle = var1;
   }

    bool isTutorialDone() {
      return this.tutorialDone;
   }

    void setTutorialDone(bool var1) {
      this.tutorialDone = var1;
   }

    bool isVehiclesWarningShow() {
      return this.vehiclesWarningShow;
   }

    void setVehiclesWarningShow(bool var1) {
      this.vehiclesWarningShow = var1;
   }

    void initPoisonousBerry() {
    std::vector var1 = new std::vector();
      var1.push_back("Base.BerryGeneric1");
      var1.push_back("Base.BerryGeneric2");
      var1.push_back("Base.BerryGeneric3");
      var1.push_back("Base.BerryGeneric4");
      var1.push_back("Base.BerryGeneric5");
      var1.push_back("Base.BerryPoisonIvy");
      this.setPoisonousBerry((std::string)var1.get(Rand.Next(0, var1.size() - 1)));
   }

    void initPoisonousMushroom() {
    std::vector var1 = new std::vector();
      var1.push_back("Base.MushroomGeneric1");
      var1.push_back("Base.MushroomGeneric2");
      var1.push_back("Base.MushroomGeneric3");
      var1.push_back("Base.MushroomGeneric4");
      var1.push_back("Base.MushroomGeneric5");
      var1.push_back("Base.MushroomGeneric6");
      var1.push_back("Base.MushroomGeneric7");
      this.setPoisonousMushroom((std::string)var1.get(Rand.Next(0, var1.size() - 1)));
   }

    std::string getPoisonousBerry() {
      return this.poisonousBerry;
   }

    void setPoisonousBerry(const std::string& var1) {
      this.poisonousBerry = var1;
   }

    std::string getPoisonousMushroom() {
      return this.poisonousMushroom;
   }

    void setPoisonousMushroom(const std::string& var1) {
      this.poisonousMushroom = var1;
   }

    static std::string getDifficulty() {
    return difficulty;
   }

    static void setDifficulty(const std::string& var0) {
      difficulty = var0;
   }

    bool isDoneNewSaveFolder() {
      return this.doneNewSaveFolder;
   }

    void setDoneNewSaveFolder(bool var1) {
      this.doneNewSaveFolder = var1;
   }

    static int getTileScale() {
    return TileScale;
   }

    bool isSelectingAll() {
      return this.isSelectingAll;
   }

    void setIsSelectingAll(bool var1) {
      this.isSelectingAll = var1;
   }

    bool getContentTranslationsEnabled() {
    return OptionEnableContentTranslations;
   }

    void setContentTranslationsEnabled(bool var1) {
      OptionEnableContentTranslations = var1;
   }

    bool isShowYourUsername() {
      return this.showYourUsername;
   }

    void setShowYourUsername(bool var1) {
      this.showYourUsername = var1;
   }

    ColorInfo getMpTextColor() {
      if (this.mpTextColor == nullptr) {
         this.mpTextColor = std::make_shared<ColorInfo>((Rand.Next(135) + 120) / 255.0F, (Rand.Next(135) + 120) / 255.0F, (Rand.Next(135) + 120) / 255.0F, 1.0F);
      }

      return this.mpTextColor;
   }

    void setMpTextColor(ColorInfo var1) {
      if (var1.r < 0.19F) {
         var1.r = 0.19F;
      }

      if (var1.g < 0.19F) {
         var1.g = 0.19F;
      }

      if (var1.b < 0.19F) {
         var1.b = 0.19F;
      }

      this.mpTextColor = var1;
   }

    bool isAzerty() {
      return this.isAzerty;
   }

    void setAzerty(bool var1) {
      this.isAzerty = var1;
   }

    ColorInfo getObjectHighlitedColor() {
      return this.objectHighlitedColor;
   }

    void setObjectHighlitedColor(ColorInfo var1) {
      this.objectHighlitedColor.set(var1);
   }

    ColorInfo getGoodHighlitedColor() {
      return this.goodHighlitedColor;
   }

    void setGoodHighlitedColor(ColorInfo var1) {
      this.goodHighlitedColor.set(var1);
   }

    ColorInfo getBadHighlitedColor() {
      return this.badHighlitedColor;
   }

    void setBadHighlitedColor(ColorInfo var1) {
      this.badHighlitedColor.set(var1);
   }

    std::string getSeenUpdateText() {
      return this.seenUpdateText;
   }

    void setSeenUpdateText(const std::string& var1) {
      this.seenUpdateText = var1;
   }

    bool isToggleToAim() {
      return this.toggleToAim;
   }

    void setToggleToAim(bool var1) {
      this.toggleToAim = var1;
   }

    bool isToggleToRun() {
      return this.toggleToRun;
   }

    void setToggleToRun(bool var1) {
      this.toggleToRun = var1;
   }

    int getXAngle(int var1, float var2) {
    double var3 = Math.toRadians(225.0F + var2);
      return std::make_shared<int64_t>(Math.round((Math.sqrt(2.0) * Math.cos(var3) + 1.0) * (var1 / 2))).intValue();
   }

    int getYAngle(int var1, float var2) {
    double var3 = Math.toRadians(225.0F + var2);
      return std::make_shared<int64_t>(Math.round((Math.sqrt(2.0) * Math.sin(var3) + 1.0) * (var1 / 2))).intValue();
   }

    bool isCelsius() {
      return this.celsius;
   }

    void setCelsius(bool var1) {
      this.celsius = var1;
   }

    bool isInDebug() {
    return bDebug;
   }

    bool isRiversideDone() {
      return this.riversideDone;
   }

    void setRiversideDone(bool var1) {
      this.riversideDone = var1;
   }

    bool isNoSave() {
      return this.noSave;
   }

    void setNoSave(bool var1) {
      this.noSave = var1;
   }

    bool isShowFirstTimeVehicleTutorial() {
      return this.showFirstTimeVehicleTutorial;
   }

    void setShowFirstTimeVehicleTutorial(bool var1) {
      this.showFirstTimeVehicleTutorial = var1;
   }

    bool getOptionDisplayAsCelsius() {
    return OptionTemperatureDisplayCelsius;
   }

    void setOptionDisplayAsCelsius(bool var1) {
      OptionTemperatureDisplayCelsius = var1;
   }

    bool isShowFirstTimeWeatherTutorial() {
      return this.showFirstTimeWeatherTutorial;
   }

    void setShowFirstTimeWeatherTutorial(bool var1) {
      this.showFirstTimeWeatherTutorial = var1;
   }

    bool getOptionDoWindSpriteEffects() {
    return OptionDoWindSpriteEffects;
   }

    void setOptionDoWindSpriteEffects(bool var1) {
      OptionDoWindSpriteEffects = var1;
   }

    bool getOptionDoDoorSpriteEffects() {
    return OptionDoDoorSpriteEffects;
   }

    void setOptionDoDoorSpriteEffects(bool var1) {
      OptionDoDoorSpriteEffects = var1;
   }

    bool getOptionDoContainerOutline() {
    return OptionDoContainerOutline;
   }

    void setOptionDoContainerOutline(bool var1) {
      OptionDoContainerOutline = var1;
   }

    void setOptionUpdateSneakButton(bool var1) {
      OptionUpdateSneakButton = var1;
   }

    bool getOptionUpdateSneakButton() {
    return OptionUpdateSneakButton;
   }

    bool isNewReloading() {
      return this.newReloading;
   }

    void setNewReloading(bool var1) {
      this.newReloading = var1;
   }

    bool isShowFirstTimeSneakTutorial() {
      return this.showFirstTimeSneakTutorial;
   }

    void setShowFirstTimeSneakTutorial(bool var1) {
      this.showFirstTimeSneakTutorial = var1;
   }

    bool isShowFirstTimeSearchTutorial() {
      return this.showFirstTimeSearchTutorial;
   }

    void setShowFirstTimeSearchTutorial(bool var1) {
      this.showFirstTimeSearchTutorial = var1;
   }

    int getTermsOfServiceVersion() {
      return this.termsOfServiceVersion;
   }

    void setTermsOfServiceVersion(int var1) {
      this.termsOfServiceVersion = var1;
   }

    void setOptiondblTapJogToSprint(bool var1) {
      OptiondblTapJogToSprint = var1;
   }

    bool isOptiondblTapJogToSprint() {
    return OptiondblTapJogToSprint;
   }

    bool isToggleToSprint() {
      return this.toggleToSprint;
   }

    void setToggleToSprint(bool var1) {
      this.toggleToSprint = var1;
   }

    int getIsoCursorVisibility() {
      return this.isoCursorVisibility;
   }

    void setIsoCursorVisibility(int var1) {
      this.isoCursorVisibility = var1;
   }

    bool getOptionShowCursorWhileAiming() {
    return OptionShowCursorWhileAiming;
   }

    void setOptionShowCursorWhileAiming(bool var1) {
      OptionShowCursorWhileAiming = var1;
   }

    bool gotNewBelt() {
      return this.gotNewBelt;
   }

    void setGotNewBelt(bool var1) {
      this.gotNewBelt = var1;
   }

    void setAnimPopupDone(bool var1) {
      this.bAnimPopupDone = var1;
   }

    bool isAnimPopupDone() {
      return this.bAnimPopupDone;
   }

    void setModsPopupDone(bool var1) {
      this.bModsPopupDone = var1;
   }

    bool isModsPopupDone() {
      return this.bModsPopupDone;
   }

    bool isRenderPrecipIndoors() {
    return OptionRenderPrecipIndoors;
   }

    void setRenderPrecipIndoors(bool var1) {
      OptionRenderPrecipIndoors = var1;
   }

    bool isCollideZombies() {
      return this.collideZombies;
   }

    void setCollideZombies(bool var1) {
      this.collideZombies = var1;
   }

    bool isFlashIsoCursor() {
      return this.flashIsoCursor;
   }

    void setFlashIsoCursor(bool var1) {
      this.flashIsoCursor = var1;
   }

    bool isOptionProgressBar() {
    return true;
   }

    void setOptionProgressBar(bool var1) {
      OptionProgressBar = var1;
   }

    void setOptionLanguageName(const std::string& var1) {
      OptionLanguageName = var1;
   }

    std::string getOptionLanguageName() {
    return OptionLanguageName;
   }

    int getOptionRenderPrecipitation() {
    return OptionRenderPrecipitation;
   }

    void setOptionRenderPrecipitation(int var1) {
      OptionRenderPrecipitation = var1;
   }

    void setOptionAutoProneAtk(bool var1) {
      OptionAutoProneAtk = var1;
   }

    bool isOptionAutoProneAtk() {
    return OptionAutoProneAtk;
   }

    void setOption3DGroundItem(bool var1) {
      Option3DGroundItem = var1;
   }

    bool isOption3DGroundItem() {
    return Option3DGroundItem;
   }

    void* getOptionOnStartup(const std::string& var1) {
      return optionsOnStartup.get(var1);
   }

    void setOptionOnStartup(const std::string& var1, void* var2) {
      optionsOnStartup.put(var1, var2);
   }

    void countMissing3DItems() {
    std::vector var1 = ScriptManager.instance.getAllItems();
    int var2 = 0;

    for (auto& var4 : var1)         if (var4.type != Type.Weapon
            && var4.type != Type.Moveable
            && !var4.name.contains("ZedDmg")
            && !var4.name.contains("Wound")
            && !var4.name.contains("MakeUp")
            && !var4.name.contains("Bandage")
            && !var4.name.contains("Hat")
            && !var4.getObsolete()
            && StringUtils.isNullOrEmpty(var4.worldObjectSprite)
            && StringUtils.isNullOrEmpty(var4.worldStaticModel)) {
            System.out.println("Missing: " + var4.name);
            var2++;
         }
      }

      System.out.println("total missing: " + var2 + "/" + var1.size());
   }

    bool getOptionShowItemModInfo() {
    return OptionShowItemModInfo;
   }

    void setOptionShowItemModInfo(bool var1) {
      OptionShowItemModInfo = var1;
   }

    bool getOptionShowSurvivalGuide() {
      return this.OptionShowSurvivalGuide;
   }

    void setOptionShowSurvivalGuide(bool var1) {
      this.OptionShowSurvivalGuide = var1;
   }

    bool getOptionEnableLeftJoystickRadialMenu() {
    return OptionEnableLeftJoystickRadialMenu;
   }

    void setOptionEnableLeftJoystickRadialMenu(bool var1) {
      OptionEnableLeftJoystickRadialMenu = var1;
   }

    std::string getVersionNumber() {
      return gameVersion;
   }
}
} // namespace core
} // namespace zombie
