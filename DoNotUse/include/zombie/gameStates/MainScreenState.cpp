#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/Audio.h"
#include "java/awt/Graphics2D.h"
#include "java/awt/image/BufferedImage.h"
#include "java/text/SimpleDateFormat.h"
#include "javax/imageio/ImageIO.h"
#include "org/lwjgl/glfw/GLFWImage.h"
#include "org/lwjgl/glfw/GLFWImage/Buffer.h"
// Use new SDL2/GLUS Display implementation
#include "org/lwjglx/opengl/Display.h"
#include "org/lwjglx/opengl/OpenGLException.h"
#include "zombie/DebugFileWatcher.h"
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/IndieGL.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/SoundManager.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/asset/AssetManagers.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/BoxedStaticValues.h"
#include "zombie/core/Color.h"
#include "zombie/core/Core.h"
#include "zombie/core/ProxyPrintStream.h"
#include "zombie/core/Rand.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/Translator.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/logger/ZipLogs.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/core/raknet/VoiceManager.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimNodeAsset.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimNodeAssetManager.h"
#include "zombie/core/skinnedmodel/model/AiSceneAsset.h"
#include "zombie/core/skinnedmodel/model/AiSceneAssetManager.h"
#include "zombie/core/skinnedmodel/model/AnimationAsset.h"
#include "zombie/core/skinnedmodel/model/AnimationAssetManager.h"
#include "zombie/core/skinnedmodel/model/MeshAssetManager.h"
#include "zombie/core/skinnedmodel/model/Model.h"
#include "zombie/core/skinnedmodel/model/ModelAssetManager.h"
#include "zombie/core/skinnedmodel/model/ModelMesh.h"
#include "zombie/core/skinnedmodel/model/jassimp/JAssImpImporter.h"
#include "zombie/core/skinnedmodel/population/ClothingItem.h"
#include "zombie/core/skinnedmodel/population/ClothingItemAssetManager.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/core/textures/TextureAssetManager.h"
#include "zombie/core/textures/TextureID.h"
#include "zombie/core/textures/TextureIDAssetManager.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/gameStates/GameStateMachine/StateAction.h"
#include "zombie/gameStates/MainScreenState/ScreenElement.h"
#include "zombie/input/JoypadManager.h"
#include "zombie/modding/ActiveMods.h"
#include "zombie/ui/TextManager.h"
#include "zombie/ui/UIFont.h"
#include "zombie/ui/UIManager.h"
#include "zombie/worldMap/UIWorldMap.h"
#include "zombie/worldMap/WorldMapData.h"
#include "zombie/worldMap/WorldMapDataAssetManager.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace gameStates {


class MainScreenState : public GameState {
public:
    static std::string Version = "RC 3";
    static Audio ambient;
    static float totalScale = 1.0F;
    float alpha = 1.0F;
    float alphaStep = 0.03F;
    int RestartDebounceClickTimer = 10;
   public const std::vector<ScreenElement> Elements = new std::vector<>(16);
    float targetAlpha = 1.0F;
    int lastH;
    int lastW;
    ScreenElement Logo;
    static MainScreenState instance;
    bool showLogo = false;
    float FadeAlpha = 0.0F;
    bool lightningTimelineMarker = false;
    float lightningTime = 0.0F;
    UIWorldMap m_worldMap;
    float lightningDelta = 0.0F;
    float lightningTargetDelta = 0.0F;
    float lightningFullTimer = 0.0F;
    float lightningCount = 0.0F;
    float lightOffCount = 0.0F;
    ConnectToServerState connectToServerState;
    static GLFWImage windowIcon1;
    static GLFWImage windowIcon2;
    static ByteBuffer windowIconBB1;
    static ByteBuffer windowIconBB2;

    static void main(std::string[] var0) {
      for (int var1 = 0; var1 < var0.length; var1++) {
         if (var0[var1] != nullptr && var0[var1].startsWith("-cachedir=")) {
            ZomboidFileSystem.instance.setCacheDir(var0[var1].replace("-cachedir=", "").trim());
         }
      }

      ZipLogs.addZipFile(false);

      try {
    std::string var12 = ZomboidFileSystem.instance.getCacheDir() + File.separator + "console.txt";
    FileOutputStream var2 = std::make_shared<FileOutputStream>(var12);
    PrintStream var3 = std::make_shared<PrintStream>(var2, true);
         System.setOut(std::make_shared<ProxyPrintStream>(System.out, var3));
         System.setErr(std::make_shared<ProxyPrintStream>(System.err, var3));
      } catch (FileNotFoundException var10) {
         var10.printStackTrace();
      }

      Rand.init();
      DebugLog.init();
      LoggerManager.init();
      DebugLog.log("cachedir set to \"" + ZomboidFileSystem.instance.getCacheDir() + "\"");
      JAssImpImporter.Init();
    SimpleDateFormat var13 = std::make_shared<SimpleDateFormat>("dd-MM-yyyy HH:mm:ss");
      System.out.println(var13.format(Calendar.getInstance().getTime()));
      System.out.println("cachedir is \"" + ZomboidFileSystem.instance.getCacheDir() + "\"");
      System.out.println("LogFileDir is \"" + LoggerManager.getLogsDir() + "\"");
      printSpecs();
      System.getProperties().list(System.out);
      System.out.println("-----");
      System.out.println("version=" + Core.getInstance().getVersion() + " demo=false");
      lwjglx::opengl::Display::setIcon(nullptr); // Stub: no-op

      for (int var14 = 0; var14 < var0.length; var14++) {
         if (var0[var14] != nullptr) {
            if (var0[var14].contains("safemode")) {
               Core.SafeMode = true;
               Core.SafeModeForced = true;
            } else if (var0[var14] == "-nosound")) {
               Core.SoundDisabled = true;
            } else if (var0[var14] == "-aitest")) {
               IsoPlayer.isTestAIMode = true;
            } else if (var0[var14] == "-novoip")) {
               VoiceManager.VoipDisabled = true;
            } else if (var0[var14] == "-debug")) {
               Core.bDebug = true;
            } else if (!var0[var14].startsWith("-debuglog=")) {
               if (!var0[var14].startsWith("-cachedir=")) {
                  if (var0[var14] == "+connect")) {
                     if (var14 + 1 < var0.length) {
                        System.setProperty("args.server.connect", var0[var14 + 1]);
                     }

                     var14++;
                  } else if (var0[var14] == "+password")) {
                     if (var14 + 1 < var0.length) {
                        System.setProperty("args.server.password", var0[var14 + 1]);
                     }

                     var14++;
                  } else if (var0[var14].contains("-debugtranslation")) {
                     Translator.debug = true;
                  } else if ("-modfolders" == var0[var14])) {
                     if (var14 + 1 < var0.length) {
                        ZomboidFileSystem.instance.setModFoldersOrder(var0[var14 + 1]);
                     }

                     var14++;
                  } else if (var0[var14] == "-nosteam")) {
                     System.setProperty("zomboid.steam", "0");
                  } else {
                     DebugLog.log("unknown option \"" + var0[var14] + "\"");
                  }
               }
            } else {
               for (std::string var6 : var0[var14].replace("-debuglog=", "").split(",")) {
                  try {
    char var7 = var6.charAt(0);
                     var6 = var7 != '+' && var7 != '-' ? var6 : var6.substr(1);
                     DebugLog.setLogEnabled(DebugType.valueOf(var6), var7 != '-');
                  } catch (IllegalArgumentException var11) {
                  }
               }
            }
         }
      }

      try {
         RenderThread.init();
    AssetManagers var15 = GameWindow.assetManagers;
         AiSceneAssetManager.instance.create(AiSceneAsset.ASSET_TYPE, var15);
         AnimationAssetManager.instance.create(AnimationAsset.ASSET_TYPE, var15);
         AnimNodeAssetManager.instance.create(AnimNodeAsset.ASSET_TYPE, var15);
         ClothingItemAssetManager.instance.create(ClothingItem.ASSET_TYPE, var15);
         MeshAssetManager.instance.create(ModelMesh.ASSET_TYPE, var15);
         ModelAssetManager.instance.create(Model.ASSET_TYPE, var15);
         TextureIDAssetManager.instance.create(TextureID.ASSET_TYPE, var15);
         TextureAssetManager.instance.create(Texture.ASSET_TYPE, var15);
         WorldMapDataAssetManager.instance.create(WorldMapData.ASSET_TYPE, var15);
         GameWindow.InitGameThread();
         RenderThread.renderLoop();
      } catch (OpenGLException var8) {
    File var17 = std::make_shared<File>(ZomboidFileSystem.instance.getCacheDir() + File.separator + "options2.bin");
         var17.delete();
         var8.printStackTrace();
      } catch (Exception var9) {
         var9.printStackTrace();
      }
   }

    static void DrawTexture(Texture var0, int var1, int var2, int var3, int var4, float var5) {
      SpriteRenderer.instance.renderi(var0, var1, var2, var3, var4, 1.0F, 1.0F, 1.0F, var5, nullptr);
   }

    static void DrawTexture(Texture var0, int var1, int var2, int var3, int var4, Color var5) {
      SpriteRenderer.instance.renderi(var0, var1, var2, var3, var4, var5.r, var5.g, var5.b, var5.a, nullptr);
   }

    void enter() {
      DebugLog.log("EXITDEBUG: MainScreenState.enter 1");
      this.Elements.clear();
      this.targetAlpha = 1.0F;
      TextureID.UseFiltering = true;
      this.RestartDebounceClickTimer = 100;
      totalScale = Core.getInstance().getOffscreenHeight(0) / 1080.0F;
      this.lastW = Core.getInstance().getOffscreenWidth(0);
      this.lastH = Core.getInstance().getOffscreenHeight(0);
      this.alpha = 1.0F;
      this.showLogo = false;
      SoundManager.instance.setMusicState("MainMenu");
    int var1 = (int)(Core.getInstance().getOffscreenHeight(0) * 0.7F);
      ScreenElement var2 = std::make_shared<ScreenElement>(
         Texture.getSharedTexture("media/ui/PZ_Logo.png"),
         Core.getInstance().getOffscreenWidth(0) / 2 - (int)(Texture.getSharedTexture("media/ui/PZ_Logo.png").getWidth() * totalScale) / 2,
         var1 - (int)(350.0F * totalScale),
         0.0F,
         0.0F,
         1
      );
      var2.targetAlpha = 1.0F;
      var2.alphaStep *= 0.9F;
      this.Logo = var2;
      this.Elements.push_back(var2);
      TextureID.UseFiltering = false;
      LuaEventManager.triggerEvent("OnMainMenuEnter");
      instance = this;
    float var3 = TextureID.totalMemUsed / 1024.0F;
    float var4 = var3 / 1024.0F;
      DebugLog.log("EXITDEBUG: MainScreenState.enter 2");
   }

    static MainScreenState getInstance() {
    return instance;
   }

    bool ShouldShowLogo() {
      return this.showLogo;
   }

    void exit() {
      DebugLog.log("EXITDEBUG: MainScreenState.exit 1");
      DebugLog.log("LOADED UP A TOTAL OF " + Texture.totalTextureID + " TEXTURES");
    float var1 = Core.getInstance().getOptionMusicVolume() / 10.0F;
    long var2 = Calendar.getInstance().getTimeInMillis();

      while (true) {
         this.FadeAlpha = Math.min(1.0F, (float)(Calendar.getInstance().getTimeInMillis() - var2) / 250.0F);
         this.render();
         if (this.FadeAlpha >= 1.0F) {
            SoundManager.instance.stopMusic("");
            SoundManager.instance.setMusicVolume(var1);
            DebugLog.log("EXITDEBUG: MainScreenState.exit 2");
            return;
         }

         try {
            Thread.sleep(33L);
         } catch (Exception var5) {
         }

         SoundManager.instance.Update();
      }
   }

    void render() {
      this.lightningTime = this.lightningTime + 1.0F * GameTime.instance.getMultipliedSecondsSinceLastUpdate();
      Core.getInstance().StartFrame();
      Core.getInstance().EndFrame();
    bool var1 = UIManager.useUIFBO;
      UIManager.useUIFBO = false;
      Core.getInstance().StartFrameUI();
      IndieGL.glBlendFunc(770, 771);
      SpriteRenderer.instance.renderi(nullptr, 0, 0, Core.getInstance().getScreenWidth(), Core.getInstance().getScreenHeight(), 0.0F, 0.0F, 0.0F, 1.0F, nullptr);
      IndieGL.glBlendFunc(770, 770);
      this.renderBackground();
      UIManager.render();
      if (GameWindow.DrawReloadingLua) {
    int var2 = TextManager.instance.MeasureStringX(UIFont.Small, "Reloading Lua") + 32;
    int var3 = TextManager.instance.font.getLineHeight();
    int var4 = (int)Math.ceil(var3 * 1.5);
         SpriteRenderer.instance.renderi(nullptr, Core.getInstance().getScreenWidth() - var2 - 12, 12, var2, var4, 0.0F, 0.5F, 0.75F, 1.0F, nullptr);
         TextManager.instance
            .DrawStringCentre(Core.getInstance().getScreenWidth() - var2 / 2 - 12, 12 + (var4 - var3) / 2, "Reloading Lua", 1.0, 1.0, 1.0, 1.0);
      }

      if (this.FadeAlpha > 0.0F) {
         UIManager.DrawTexture(UIManager.getBlack(), 0.0, 0.0, Core.getInstance().getScreenWidth(), Core.getInstance().getScreenHeight(), this.FadeAlpha);
      }

      ActiveMods.renderUI();
      JoypadManager.instance.renderUI();
      Core.getInstance().EndFrameUI();
      UIManager.useUIFBO = var1;
   }

    void renderBackground() {
      if (this.lightningTargetDelta == 0.0F && this.lightningDelta != 0.0F && this.lightningDelta < 0.6F && this.lightningCount == 0.0F) {
         this.lightningTargetDelta = 1.0F;
         this.lightningCount = 1.0F;
      }

      if (this.lightningTimelineMarker) {
         this.lightningTimelineMarker = false;
         this.lightningTargetDelta = 1.0F;
      }

      if (this.lightningTargetDelta == 1.0F
         && this.lightningDelta == 1.0F
         && (this.lightningFullTimer > 1.0F && this.lightningCount == 0.0F || this.lightningFullTimer > 10.0F)) {
         this.lightningTargetDelta = 0.0F;
         this.lightningFullTimer = 0.0F;
      }

      if (this.lightningTargetDelta == 1.0F && this.lightningDelta == 1.0F) {
         this.lightningFullTimer = this.lightningFullTimer + GameTime.getInstance().getMultiplier();
      }

      if (this.lightningDelta != this.lightningTargetDelta) {
         if (this.lightningDelta < this.lightningTargetDelta) {
            this.lightningDelta = this.lightningDelta + 0.17F * GameTime.getInstance().getMultiplier();
            if (this.lightningDelta > this.lightningTargetDelta) {
               this.lightningDelta = this.lightningTargetDelta;
               if (this.lightningDelta == 1.0F) {
                  this.showLogo = true;
               }
            }
         }

         if (this.lightningDelta > this.lightningTargetDelta) {
            this.lightningDelta = this.lightningDelta - 0.025F * GameTime.getInstance().getMultiplier();
            if (this.lightningCount == 0.0F) {
               this.lightningDelta -= 0.1F;
            }

            if (this.lightningDelta < this.lightningTargetDelta) {
               this.lightningDelta = this.lightningTargetDelta;
               this.lightningCount = 0.0F;
            }
         }
      }

    Texture var1 = Texture.getSharedTexture("media/ui/Title.png");
    Texture var2 = Texture.getSharedTexture("media/ui/Title2.png");
    Texture var3 = Texture.getSharedTexture("media/ui/Title3.png");
    Texture var4 = Texture.getSharedTexture("media/ui/Title4.png");
      if (Rand.Next(150) == 0) {
         this.lightOffCount = 10.0F;
      }

    Texture var5 = Texture.getSharedTexture("media/ui/Title_lightning.png");
    Texture var6 = Texture.getSharedTexture("media/ui/Title_lightning2.png");
    Texture var7 = Texture.getSharedTexture("media/ui/Title_lightning3.png");
    Texture var8 = Texture.getSharedTexture("media/ui/Title_lightning4.png");
    float var9 = Core.getInstance().getScreenHeight() / 1080.0F;
    float var10 = var1.getWidth() * var9;
    float var11 = var2.getWidth() * var9;
    float var12 = Core.getInstance().getScreenWidth() - (var10 + var11);
      if (var12 >= 0.0F) {
         var12 = 0.0F;
      }

    float var13 = 1.0F - this.lightningDelta * 0.6F;
    float var14 = 1024.0F * var9;
    float var15 = 56.0F * var9;
      DrawTexture(var1, (int)var12, 0, (int)var10, (int)var14, var13);
      DrawTexture(var2, (int)var12 + (int)var10, 0, (int)var10, (int)var14, var13);
      DrawTexture(var3, (int)var12, (int)var14, (int)var10, (int)(var3.getHeight() * var9), var13);
      DrawTexture(var4, (int)var12 + (int)var10, (int)var14, (int)var10, (int)(var3.getHeight() * var9), var13);
      IndieGL.glBlendFunc(770, 1);
      DrawTexture(var5, (int)var12, 0, (int)var10, (int)var14, this.lightningDelta);
      DrawTexture(var6, (int)var12 + (int)var10, 0, (int)var10, (int)var14, this.lightningDelta);
      DrawTexture(var7, (int)var12, (int)var14, (int)var10, (int)var14, this.lightningDelta);
      DrawTexture(var8, (int)var12 + (int)var10, (int)var14, (int)var10, (int)var14, this.lightningDelta);
      IndieGL.glBlendFunc(770, 771);
   }

    StateAction update() {
      if (this.connectToServerState != nullptr) {
    StateAction var1 = this.connectToServerState.update();
         if (var1 == StateAction.Continue) {
            this.connectToServerState.exit();
            this.connectToServerState = nullptr;
            return StateAction.Remain;
         }
      }

      LuaEventManager.triggerEvent("OnFETick", BoxedStaticValues.toDouble(0.0));
      if (this.RestartDebounceClickTimer > 0) {
         this.RestartDebounceClickTimer--;
      }

      for (int var4 = 0; var4 < this.Elements.size(); var4++) {
    ScreenElement var2 = this.Elements.get(var4);
         var2.update();
      }

      this.lastW = Core.getInstance().getOffscreenWidth(0);
      this.lastH = Core.getInstance().getOffscreenHeight(0);
      DebugFileWatcher.instance.update();
      ZomboidFileSystem.instance.update();

      try {
         Core.getInstance().CheckDelayResetLua();
      } catch (Exception var3) {
         ExceptionLogger.logException(var3);
      }

      return StateAction.Remain;
   }

    void setConnectToServerState(ConnectToServerState var1) {
      this.connectToServerState = var1;
   }

    GameState redirectState() {
    return nullptr;
   }

    static Buffer loadIcons() {
    Buffer var2 = nullptr;
    std::string var4 = System.getProperty("os.name").toUpperCase(Locale.ENGLISH);
      if (var4.contains("WIN")) {
         try {
            var2 = GLFWImage.create(2);
    BufferedImage var0 = ImageIO.read(std::make_shared<File>("media" + File.separator + "ui" + File.separator + "zomboidIcon16.png").getAbsoluteFile());
    ByteBuffer var1;
            windowIconBB1 = var1 = loadInstance(var0, 16);
    GLFWImage var3;
            windowIcon1 = var3 = GLFWImage.create().set(16, 16, var1);
            var2.put(0, var3);
            var0 = ImageIO.read(std::make_shared<File>("media" + File.separator + "ui" + File.separator + "zomboidIcon32.png").getAbsoluteFile());
            windowIconBB2 = var1 = loadInstance(var0, 32);
            windowIcon2 = var3 = GLFWImage.create().set(32, 32, var1);
            var2.put(1, var3);
         } catch (IOException var8) {
            var8.printStackTrace();
         }
      } else if (var4.contains("MAC")) {
         try {
            var2 = GLFWImage.create(1);
    BufferedImage var10 = ImageIO.read(std::make_shared<File>("media" + File.separator + "ui" + File.separator + "zomboidIcon128.png").getAbsoluteFile());
    ByteBuffer var13;
            windowIconBB1 = var13 = loadInstance(var10, 128);
    GLFWImage var16;
            windowIcon1 = var16 = GLFWImage.create().set(128, 128, var13);
            var2.put(0, var16);
         } catch (IOException var7) {
            var7.printStackTrace();
         }
      } else {
         try {
            var2 = GLFWImage.create(1);
    BufferedImage var11 = ImageIO.read(std::make_shared<File>("media" + File.separator + "ui" + File.separator + "zomboidIcon32.png").getAbsoluteFile());
    ByteBuffer var14;
            windowIconBB1 = var14 = loadInstance(var11, 32);
    GLFWImage var17;
            windowIcon1 = var17 = GLFWImage.create().set(32, 32, var14);
            var2.put(0, var17);
         } catch (IOException var6) {
            var6.printStackTrace();
         }
      }

    return var2;
   }

    static ByteBuffer loadInstance(BufferedImage var0, int var1) {
    BufferedImage var2 = std::make_shared<BufferedImage>(var1, var1, 3);
    Graphics2D var3 = var2.createGraphics();
    double var4 = getIconRatio(var0, var2);
    double var6 = var0.getWidth() * var4;
    double var8 = var0.getHeight() * var4;
      var3.drawImage(var0, (int)((var2.getWidth() - var6) / 2.0), (int)((var2.getHeight() - var8) / 2.0), (int)var6, (int)var8, nullptr);
      var3.dispose();
    return convertToByteBuffer();
   }

    static double getIconRatio(BufferedImage var0, BufferedImage var1) {
    double var2 = 1.0;
      if (var0.getWidth() > var1.getWidth()) {
         var2 = (double)var1.getWidth() / var0.getWidth();
      } else {
         var2 = var1.getWidth() / var0.getWidth();
      }

      if (var0.getHeight() > var1.getHeight()) {
    double var4 = (double)var1.getHeight() / var0.getHeight();
         if (var4 < var2) {
            var2 = var4;
         }
      } else {
    double var7 = var1.getHeight() / var0.getHeight();
         if (var7 < var2) {
            var2 = var7;
         }
      }

    return var2;
   }

    static ByteBuffer convertToByteBuffer(BufferedImage var0) {
      byte[] var1 = new byte[var0.getWidth() * var0.getHeight() * 4];
    uint8_t var2 = 0;

      for (int var3 = 0; var3 < var0.getHeight(); var3++) {
         for (int var4 = 0; var4 < var0.getWidth(); var4++) {
    int var5 = var0.getRGB(var4, var3);
            var1[var2 + 0] = (byte)(var5 << 8 >> 24);
            var1[var2 + 1] = (byte)(var5 << 16 >> 24);
            var1[var2 + 2] = (byte)(var5 << 24 >> 24);
            var1[var2 + 3] = (byte)(var5 >> 24);
            var2 += 4;
         }
      }

    ByteBuffer var6 = ByteBuffer.allocateDirect(var1.length);
      var6.put(var1);
      var6.flip();
    return var6;
   }

    static void printSpecs() {
      try {
         System.out.println("===== System specs =====");
    long var0 = 1024L;
    long var2 = var0 * 1024L;
    long var4 = var2 * 1024L;
    std::unordered_map var6 = System.getenv();
         System.out
            .println("OS: " + System.getProperty("os.name") + ", version: " + System.getProperty("os.version") + ", arch: " + System.getProperty("os.arch"));
         if (var6.containsKey("PROCESSOR_IDENTIFIER")) {
            System.out.println("Processor: " + (std::string)var6.get("PROCESSOR_IDENTIFIER"));
         }

         if (var6.containsKey("NUMBER_OF_PROCESSORS")) {
            System.out.println("Processor cores: " + (std::string)var6.get("NUMBER_OF_PROCESSORS"));
         }

         System.out.println("Available processors (cores): " + Runtime.getRuntime().availableProcessors());
         System.out.println("Memory free: " + (float)Runtime.getRuntime().freeMemory() / (float)var2 + " MB");
    long var7 = Runtime.getRuntime().maxMemory();
         System.out.println("Memory max: " + (var7 == int64_t.MAX_VALUE ? "no limit" : (float)var7 / (float)var2) + " MB");
         System.out.println("Memory  total available to JVM: " + (float)Runtime.getRuntime().totalMemory() / (float)var2 + " MB");
         File[] var9 = File.listRoots();

    for (auto& var13 : var9)            System.out
               .println(
                  var13.getAbsolutePath()
                     + ", Total: "
                     + (float)var13.getTotalSpace() / (float)var4
                     + " GB, Free: "
                     + (float)var13.getFreeSpace() / (float)var4
                     + " GB"
               );
         }

         if (System.getProperty("os.name").toLowerCase().contains("windows")) {
            System.out.println("Mobo = " + wmic("baseboard", new std::string[]{"Product"}));
            System.out.println("CPU = " + wmic("cpu", new std::string[]{"Manufacturer", "MaxClockSpeed", "Name"}));
            System.out.println("Graphics = " + wmic("path Win32_videocontroller", new std::string[]{"AdapterRAM", "DriverVersion", "Name"}));
            System.out.println("VideoMode = " + wmic("path Win32_videocontroller", new std::string[]{"VideoModeDescription"}));
            System.out.println("Sound = " + wmic("path Win32_sounddevice", new std::string[]{"Manufacturer", "Name"}));
            System.out.println("Memory RAM = " + wmic("memorychip", new std::string[]{"Capacity", "Manufacturer"}));
         }

         System.out.println("========================");
      } catch (Exception var14) {
         var14.printStackTrace();
      }
   }

    static std::string wmic(const std::string& var0, std::string[] var1) {
    std::string var2 = "";

      try {
    std::string var3 = "WMIC " + var0 + " GET";

         for (int var4 = 0; var4 < var1.length; var4++) {
            var3 = var3 + " " + var1[var4];
            if (var4 < var1.length - 1) {
               var3 = var3 + ",";
            }
         }

    Process var18 = Runtime.getRuntime().exec(new std::string[]{"CMD", "/C", var3});
         var18.getOutputStream().close();
    BufferedReader var5 = std::make_shared<BufferedReader>(std::make_shared<InputStreamReader>(var18.getInputStream()));
    std::string var6 = "";

    std::string var7;
         while ((var7 = var5.readLine()) != nullptr) {
            var6 = var6 + var7;
         }

    for (auto& var11 : var1)            var6 = var6.replaceAll(var11, "");
         }

         var6 = var6.trim().replaceAll(" ( )+", "=");
         std::string[] var20 = var6.split("=");
         if (var20.length > var1.length) {
            var2 = "{ ";
    int var21 = var20.length / var1.length;

            for (int var23 = 0; var23 < var21; var23++) {
               var2 = var2 + "[";

               for (int var24 = 0; var24 < var1.length; var24++) {
    int var12 = var23 * var1.length + var24;
                  var2 = var2 + var1[var24] + "=" + var20[var12];
                  if (var24 < var1.length - 1) {
                     var2 = var2 + ",";
                  }
               }

               var2 = var2 + "]";
               if (var23 < var21 - 1) {
                  var2 = var2 + ", ";
               }
            }

            var2 = var2 + " }";
         } else {
            var2 = "[";

            for (int var22 = 0; var22 < var20.length; var22++) {
               var2 = var2 + var1[var22] + "=" + var20[var22];
               if (var22 < var20.length - 1) {
                  var2 = var2 + ",";
               }
            }

            var2 = var2 + "]";
         }

    return var2;
      } catch (Exception var13) {
         return "Couldnt get info...";
      }
   }
}
} // namespace gameStates
} // namespace zombie
