#pragma once
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjglx/input/Keyboard.h"
#include "zombie/AmbientStreamManager.h"
#include "zombie/ChunkMapFilenames.h"
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/Lua/LuaManager/GlobalObject.h"
#include "zombie/SoundManager.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/ThreadGroups.h"
#include "zombie/core/Translator.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/raknet/UdpConnection/ConnectionType.h"
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/core/skinnedmodel/population/OutfitManager.h"
#include "zombie/core/skinnedmodel/runtime/RuntimeAnimationScript.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/core/znet/SteamUtils.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/gameStates/GameLoadingState/1.h"
#include "zombie/gameStates/GameStateMachine/StateAction.h"
#include "zombie/input/GameKeyboard.h"
#include "zombie/input/JoypadManager.h"
#include "zombie/input/Mouse.h"
#include "zombie/inventory/RecipeManager.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoChunkMap.h"
#include "zombie/iso/IsoPuddles.h"
#include "zombie/iso/IsoWater.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/LosUtil.h"
#include "zombie/iso/WorldStreamer.h"
#include "zombie/iso/areas/SafeHouse.h"
#include "zombie/iso/sprite/SkyBox.h"
#include "zombie/modding/ActiveMods.h"
#include "zombie/modding/ActiveModsFile.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/NetworkAIParams.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/ui/TextManager.h"
#include "zombie/ui/UIFont.h"
#include "zombie/ui/UIManager.h"
#include "zombie/world/WorldDictionary.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace gameStates {


class GameLoadingState : public GameState {
public:
    static Thread loader = nullptr;
    static bool newGame = true;
    static long startTime;
    static bool build23Stop = false;
    static bool unexpectedError = false;
    static std::string GameLoadingString = "";
    static bool playerWrongIP = false;
    static bool bShowedUI = false;
    static bool bShowedClickToSkip = false;
    static bool mapDownloadFailed = false;
   private volatile boolean bWaitForAssetLoadingToFinish1 = false;
   private volatile boolean bWaitForAssetLoadingToFinish2 = false;
    const void* assetLock1 = "Asset Lock 1";
    const void* assetLock2 = "Asset Lock 2";
    std::string text;
    float width;
    static bool playerCreated = false;
    static bool bDone = false;
    static bool convertingWorld = false;
    static int convertingFileCount = -1;
    static int convertingFileMax = -1;
    int Stage = 0;
    float TotalTime = 33.0F;
    float loadingDotTick = 0.0F;
    std::string loadingDot = "";
    float clickToSkipAlpha = 1.0F;
    bool clickToSkipFadeIn = false;
    float Time = 0.0F;
    bool bForceDone = false;

    void enter() {
      if (GameClient.bClient) {
         this.text = Translator.getText("UI_DirectConnectionPortWarning", ServerOptions.getInstance().UDPPort.getValue());
         this.width = TextManager.instance.MeasureStringX(UIFont.NewMedium, this.text) + 8;
      }

      GameWindow.bLoadedAsClient = GameClient.bClient;
      GameWindow.OkToSaveOnExit = false;
      bShowedUI = false;
      ChunkMapFilenames.instance.clear();
      DebugLog.log("Savefile name is \"" + Core.GameSaveWorld + "\"");
      GameLoadingString = "";

      try {
         LuaManager.LoadDirBase("server");
         LuaManager.finishChecksum();
      } catch (Exception var7) {
         ExceptionLogger.logException(var7);
      }

      RecipeManager.LoadedAfterLua();
      Core.getInstance().initFBOs();
      Core.getInstance().initShaders();
      SkyBox.getInstance();
      IsoPuddles.getInstance();
      IsoWater.getInstance();
      GameWindow.bServerDisconnected = false;
      if (GameClient.bClient && !GameClient.instance.bConnected) {
         GameClient.instance.init();

         for (Core.GameMode = "Multiplayer"; GameClient.instance.ID == -1; GameClient.instance.update()) {
            try {
               Thread.sleep(10L);
            } catch (InterruptedException var6) {
               var6.printStackTrace();
            }
         }

         Core.GameSaveWorld = "clienttest" + GameClient.instance.ID;
         GlobalObject.deleteSave("clienttest" + GameClient.instance.ID);
         GlobalObject.createWorld("clienttest" + GameClient.instance.ID);
      }

      if (Core.GameSaveWorld.empty()) {
         DebugLog.log("No savefile directory was specified.  It's a bug.");
         GameWindow.DoLoadingText("No savefile directory was specified.  The game will now close.  Sorry!");

         try {
            Thread.sleep(4000L);
         } catch (Exception var5) {
         }

         System.exit(-1);
      }

    File var1 = std::make_shared<File>(ZomboidFileSystem.instance.getCurrentSaveDir());
      if (!var1.exists() && !Core.getInstance().isNoSave()) {
         DebugLog.log("The savefile directory doesn't exist.  It's a bug.");
         GameWindow.DoLoadingText("The savefile directory doesn't exist.  The game will now close.  Sorry!");

         try {
            Thread.sleep(4000L);
         } catch (Exception var4) {
         }

         System.exit(-1);
      }

      try {
         if (!GameClient.bClient && !GameServer.bServer && !Core.bTutorial && !Core.isLastStand() && !"Multiplayer" == Core.GameMode)) {
    FileWriter var2 = std::make_shared<FileWriter>(std::make_shared<File>(ZomboidFileSystem.instance.getCacheDir() + File.separator + "latestSave.ini"));
            var2.write(IsoWorld.instance.getWorld() + "\r\n");
            var2.write(Core.getInstance().getGameMode() + "\r\n");
            var2.write(IsoWorld.instance.getDifficulty() + "\r\n");
            var2.flush();
            var2.close();
         }
      } catch (IOException var3) {
         var3.printStackTrace();
      }

      bDone = false;
      this.bForceDone = false;
      IsoChunkMap.CalcChunkWidth();
      LosUtil.init(IsoChunkMap.ChunkGridWidth * 10, IsoChunkMap.ChunkGridWidth * 10);
      this.Time = 0.0F;
      this.Stage = 0;
      this.clickToSkipAlpha = 1.0F;
      this.clickToSkipFadeIn = false;
      startTime = System.currentTimeMillis();
      SoundManager.instance.Purge();
      SoundManager.instance.setMusicState("Loading");
      LuaEventManager.triggerEvent("OnPreMapLoad");
      newGame = true;
      build23Stop = false;
      unexpectedError = false;
      mapDownloadFailed = false;
      playerCreated = false;
      convertingWorld = false;
      convertingFileCount = 0;
      convertingFileMax = -1;
    File var8 = ZomboidFileSystem.instance.getFileInCurrentSave("map_ver.bin");
      if (var8.exists()) {
         newGame = false;
      }

      if (GameClient.bClient) {
         newGame = false;
      }

      WorldDictionary.setIsNewGame(newGame);
      GameKeyboard.bNoEventsWhileLoading = true;
      loader = std::make_shared<Thread>(ThreadGroups.Workers, std::make_shared<1>(this));
      UIManager.bSuspend = true;
      loader.setName("GameLoadingThread");
      loader.setUncaughtExceptionHandler(GameWindow::uncaughtException);
      loader.start();
   }

    static void SendDone() {
      DebugLog.log("game loading took " + (System.currentTimeMillis() - startTime + 999L) / 1000L + " seconds");
      if (!GameClient.bClient) {
         bDone = true;
         GameKeyboard.bNoEventsWhileLoading = false;
      } else {
         GameClient.instance.sendLoginQueueDone2(System.currentTimeMillis() - startTime);
      }
   }

    static void Done() {
      bDone = true;
      GameKeyboard.bNoEventsWhileLoading = false;
   }

    GameState redirectState() {
      return std::make_unique<IngameState>();
   }

    void exit() {
      if (GameClient.bClient) {
         NetworkAIParams.Init();
      }

      UIManager.init();
      LuaEventManager.triggerEvent("OnCreatePlayer", 0, IsoPlayer.players[0]);
      loader = nullptr;
      bDone = false;
      this.Stage = 0;
      IsoCamera.SetCharacterToFollow(IsoPlayer.getInstance());
      if (GameClient.bClient && !ServerOptions.instance.SafehouseAllowTrepass.getValue()) {
    SafeHouse var1 = SafeHouse.isSafeHouse(IsoPlayer.getInstance().getCurrentSquare(), GameClient.username, true);
         if (var1 != nullptr) {
            IsoPlayer.getInstance().setX(var1.getX() - 1);
            IsoPlayer.getInstance().setY(var1.getY() - 1);
         }
      }

      SoundManager.instance.stopMusic("");
      AmbientStreamManager.instance.init();
      if (IsoPlayer.getInstance() != nullptr && IsoPlayer.getInstance().isAsleep()) {
         UIManager.setFadeBeforeUI(IsoPlayer.getInstance().getPlayerNum(), true);
         UIManager.FadeOut(IsoPlayer.getInstance().getPlayerNum(), 2.0);
         UIManager.setFadeTime(IsoPlayer.getInstance().getPlayerNum(), 0.0);
         UIManager.getSpeedControls().SetCurrentGameSpeed(3);
      }

      if (!GameClient.bClient) {
    ActiveMods var4 = ActiveMods.getById("currentGame");
         var4.checkMissingMods();
         var4.checkMissingMaps();
         ActiveMods.setLoadedMods(var4);
    std::string var2 = ZomboidFileSystem.instance.getFileNameInCurrentSave("mods.txt");
    ActiveModsFile var3 = std::make_shared<ActiveModsFile>();
         var3.write(var2, var4);
      }

      GameWindow.OkToSaveOnExit = true;
   }

    void render() {
      this.loadingDotTick = this.loadingDotTick + GameTime.getInstance().getMultiplier();
      if (this.loadingDotTick > 20.0F) {
         this.loadingDot = ".";
      }

      if (this.loadingDotTick > 40.0F) {
         this.loadingDot = "..";
      }

      if (this.loadingDotTick > 60.0F) {
         this.loadingDot = "...";
      }

      if (this.loadingDotTick > 80.0F) {
         this.loadingDot = "";
         this.loadingDotTick = 0.0F;
      }

      this.Time = this.Time + GameTime.instance.getTimeDelta();
    float var1 = 0.0F;
    float var2 = 0.0F;
    float var3 = 0.0F;
      if (this.Stage == 0) {
    float var4 = this.Time;
    float var5 = 0.0F;
    float var6 = 1.0F;
    float var7 = 5.0F;
    float var8 = 7.0F;
    float var9 = 0.0F;
         if (var4 > var5 && var4 < var6) {
            var9 = (var4 - var5) / (var6 - var5);
         }

         if (var4 >= var6 && var4 <= var7) {
            var9 = 1.0F;
         }

         if (var4 > var7 && var4 < var8) {
            var9 = 1.0F - (var4 - var7) / (var8 - var7);
         }

         if (var4 >= var8) {
            this.Stage++;
         }

         var1 = var9;
      }

      if (this.Stage == 1) {
    float var14 = this.Time;
    float var17 = 7.0F;
    float var28 = 8.0F;
    float var38 = 13.0F;
    float var44 = 15.0F;
    float var50 = 0.0F;
         if (var14 > var17 && var14 < var28) {
            var50 = (var14 - var17) / (var28 - var17);
         }

         if (var14 >= var28 && var14 <= var38) {
            var50 = 1.0F;
         }

         if (var14 > var38 && var14 < var44) {
            var50 = 1.0F - (var14 - var38) / (var44 - var38);
         }

         if (var14 >= var44) {
            this.Stage++;
         }

         var2 = var50;
      }

      if (this.Stage == 2) {
    float var15 = this.Time;
    float var18 = 15.0F;
    float var29 = 16.0F;
    float var39 = 31.0F;
    float var45 = this.TotalTime;
    float var51 = 0.0F;
         if (var15 > var18 && var15 < var29) {
            var51 = (var15 - var18) / (var29 - var18);
         }

         if (var15 >= var29 && var15 <= var39) {
            var51 = 1.0F;
         }

         if (var15 > var39 && var15 < var45) {
            var51 = 1.0F - (var15 - var39) / (var45 - var39);
         }

         if (var15 >= var45) {
            this.Stage++;
         }

         var3 = var51;
      }

      Core.getInstance().StartFrame();
      Core.getInstance().EndFrame();
    bool var16 = UIManager.useUIFBO;
      UIManager.useUIFBO = false;
      Core.getInstance().StartFrameUI();
      SpriteRenderer.instance.renderi(nullptr, 0, 0, Core.getInstance().getScreenWidth(), Core.getInstance().getScreenHeight(), 0.0F, 0.0F, 0.0F, 1.0F, nullptr);
      if (mapDownloadFailed) {
    int var27 = Core.getInstance().getScreenWidth() / 2;
    int var37 = Core.getInstance().getScreenHeight() / 2;
    int var43 = TextManager.instance.getFontFromEnum(UIFont.Medium).getLineHeight();
    int var49 = var37 - var43 / 2;
    std::string var55 = Translator.getText("UI_GameLoad_MapDownloadFailed");
         TextManager.instance.DrawStringCentre(UIFont.Medium, var27, var49, var55, 0.8, 0.1, 0.1, 1.0);
         UIManager.render();
         Core.getInstance().EndFrameUI();
      } else if (unexpectedError) {
    int var26 = TextManager.instance.getFontFromEnum(UIFont.Medium).getLineHeight();
    int var36 = TextManager.instance.getFontFromEnum(UIFont.Small).getLineHeight();
    uint8_t var42 = 8;
    uint8_t var48 = 2;
    int var54 = var26 + var42 + var36 + var48 + var36;
    int var57 = Core.getInstance().getScreenWidth() / 2;
    int var11 = Core.getInstance().getScreenHeight() / 2;
    int var12 = var11 - var54 / 2;
         TextManager.instance.DrawStringCentre(UIFont.Medium, var57, var12, Translator.getText("UI_GameLoad_UnexpectedError1"), 0.8, 0.1, 0.1, 1.0);
         TextManager.instance
            .DrawStringCentre(UIFont.Small, var57, var12 + var26 + var42, Translator.getText("UI_GameLoad_UnexpectedError2"), 1.0, 1.0, 1.0, 1.0);
    std::string var13 = ZomboidFileSystem.instance.getCacheDir() + File.separator + "console.txt";
         TextManager.instance.DrawStringCentre(UIFont.Small, var57, var12 + var26 + var42 + var36 + var48, var13, 1.0, 1.0, 1.0, 1.0);
         UIManager.render();
         Core.getInstance().EndFrameUI();
      } else if (GameWindow.bServerDisconnected) {
    int var25 = Core.getInstance().getScreenWidth() / 2;
    int var35 = Core.getInstance().getScreenHeight() / 2;
    int var41 = TextManager.instance.getFontFromEnum(UIFont.Medium).getLineHeight();
    uint8_t var47 = 2;
    int var53 = var35 - (var41 + var47 + var41) / 2;
    std::string var56 = GameWindow.kickReason;
         if (var56 == nullptr) {
            var56 = Translator.getText("UI_OnConnectFailed_ConnectionLost");
         }

         TextManager.instance.DrawStringCentre(UIFont.Medium, var25, var53, var56, 0.8, 0.1, 0.1, 1.0);
         UIManager.render();
         Core.getInstance().EndFrameUI();
      } else {
         if (build23Stop) {
            TextManager.instance
               .DrawStringCentre(
                  UIFont.Small,
                  Core.getInstance().getScreenWidth() / 2,
                  Core.getInstance().getScreenHeight() - 100,
                  "This save is incompatible. Please switch to Steam branch \"build23\" to continue this save.",
                  0.8,
                  0.1,
                  0.1,
                  1.0
               );
         } else if (convertingWorld) {
            TextManager.instance
               .DrawStringCentre(
                  UIFont.Small,
                  Core.getInstance().getScreenWidth() / 2,
                  Core.getInstance().getScreenHeight() - 100,
                  Translator.getText("UI_ConvertWorld"),
                  0.5,
                  0.5,
                  0.5,
                  1.0
               );
            if (convertingFileMax != -1) {
               TextManager.instance
                  .DrawStringCentre(
                     UIFont.Small,
                     Core.getInstance().getScreenWidth() / 2,
                     Core.getInstance().getScreenHeight() - 100 + TextManager.instance.getFontFromEnum(UIFont.Small).getLineHeight() + 8,
                     convertingFileCount + " / " + convertingFileMax,
                     0.5,
                     0.5,
                     0.5,
                     1.0
                  );
            }
         }

         if (playerWrongIP) {
    int var24 = Core.getInstance().getScreenWidth() / 2;
    int var34 = Core.getInstance().getScreenHeight() / 2;
    int var40 = TextManager.instance.getFontFromEnum(UIFont.Medium).getLineHeight();
    uint8_t var46 = 2;
    int var52 = var34 - (var40 + var46 + var40) / 2;
    std::string var10 = GameLoadingString;
            if (GameLoadingString == nullptr) {
               var10 = "";
            }

            TextManager.instance.DrawStringCentre(UIFont.Medium, var24, var52, var10, 0.8, 0.1, 0.1, 1.0);
            UIManager.render();
            Core.getInstance().EndFrameUI();
         } else {
            if (GameClient.bClient) {
    std::string var19 = GameLoadingString;
               if (GameLoadingString == nullptr) {
                  var19 = "";
               }

               TextManager.instance
                  .DrawStringCentre(UIFont.Small, Core.getInstance().getScreenWidth() / 2, Core.getInstance().getScreenHeight() - 60, var19, 0.5, 0.5, 0.5, 1.0);
               if (GameClient.connection.getConnectionType() == ConnectionType.Steam) {
                  SpriteRenderer.instance
                     .render(
                        nullptr,
                        (Core.getInstance().getScreenWidth() - this.width) / 2.0F,
                        Core.getInstance().getScreenHeight() - 32,
                        this.width,
                        18.0F,
                        1.0F,
                        0.4F,
                        0.35F,
                        0.8F,
                        nullptr
                     );
                  TextManager.instance
                     .DrawStringCentre(
                        UIFont.Medium, Core.getInstance().getScreenWidth() / 2, Core.getInstance().getScreenHeight() - 32, this.text, 0.1, 0.1, 0.1, 1.0
                     );
               }
            } else if (!playerCreated && newGame && !Core.isLastStand()) {
               TextManager.instance
                  .DrawStringCentre(
                     UIFont.Small,
                     Core.getInstance().getScreenWidth() / 2,
                     Core.getInstance().getScreenHeight() - 60,
                     Translator.getText("UI_Loading").replace(".", ""),
                     0.5,
                     0.5,
                     0.5,
                     1.0
                  );
               TextManager.instance
                  .DrawString(
                     UIFont.Small,
                     Core.getInstance().getScreenWidth() / 2
                        + TextManager.instance.MeasureStringX(UIFont.Small, Translator.getText("UI_Loading").replace(".", "")) / 2
                        + 1,
                     Core.getInstance().getScreenHeight() - 60,
                     this.loadingDot,
                     0.5,
                     0.5,
                     0.5,
                     1.0
                  );
            }

            if (this.Stage == 0) {
    int var20 = Core.getInstance().getScreenWidth() / 2;
    int var30 = Core.getInstance().getScreenHeight() / 2 - TextManager.instance.getFontFromEnum(UIFont.Intro).getLineHeight() / 2;
               TextManager.instance.DrawStringCentre(UIFont.Intro, var20, var30, Translator.getText("UI_Intro1"), 1.0, 1.0, 1.0, var1);
            }

            if (this.Stage == 1) {
    int var21 = Core.getInstance().getScreenWidth() / 2;
    int var31 = Core.getInstance().getScreenHeight() / 2 - TextManager.instance.getFontFromEnum(UIFont.Intro).getLineHeight() / 2;
               TextManager.instance.DrawStringCentre(UIFont.Intro, var21, var31, Translator.getText("UI_Intro2"), 1.0, 1.0, 1.0, var2);
            }

            if (this.Stage == 2) {
    int var22 = Core.getInstance().getScreenWidth() / 2;
    int var32 = Core.getInstance().getScreenHeight() / 2 - TextManager.instance.getFontFromEnum(UIFont.Intro).getLineHeight() / 2;
               TextManager.instance.DrawStringCentre(UIFont.Intro, var22, var32, Translator.getText("UI_Intro3"), 1.0, 1.0, 1.0, var3);
            }

            if (Core.getInstance().getDebug()) {
               bShowedClickToSkip = true;
            }

            if (bDone && playerCreated && (!newGame || this.Time >= this.TotalTime || Core.isLastStand() || "Tutorial" == Core.GameMode))) {
               if (this.clickToSkipFadeIn) {
                  this.clickToSkipAlpha = this.clickToSkipAlpha + GameTime.getInstance().getMultiplier() / 1.6F / 30.0F;
                  if (this.clickToSkipAlpha > 1.0F) {
                     this.clickToSkipAlpha = 1.0F;
                     this.clickToSkipFadeIn = false;
                  }
               } else {
                  bShowedClickToSkip = true;
                  this.clickToSkipAlpha = this.clickToSkipAlpha - GameTime.getInstance().getMultiplier() / 1.6F / 30.0F;
                  if (this.clickToSkipAlpha < 0.25F) {
                     this.clickToSkipFadeIn = true;
                  }
               }

               if (GameWindow.ActivatedJoyPad != nullptr && !JoypadManager.instance.JoypadList.empty()) {
    Texture var23 = Texture.getSharedTexture("media/ui/xbox/XBOX_A.png");
                  if (var23 != nullptr) {
    int var33 = TextManager.instance.getFontFromEnum(UIFont.Small).getLineHeight();
                     SpriteRenderer.instance
                        .renderi(
                           var23,
                           Core.getInstance().getScreenWidth() / 2
                              - TextManager.instance.MeasureStringX(UIFont.Small, Translator.getText("UI_PressAToStart")) / 2
                              - 8
                              - var23.getWidth(),
                           Core.getInstance().getScreenHeight() - 60 + var33 / 2 - var23.getHeight() / 2,
                           var23.getWidth(),
                           var23.getHeight(),
                           1.0F,
                           1.0F,
                           1.0F,
                           this.clickToSkipAlpha,
                           nullptr
                        );
                  }

                  TextManager.instance
                     .DrawStringCentre(
                        UIFont.Small,
                        Core.getInstance().getScreenWidth() / 2,
                        Core.getInstance().getScreenHeight() - 60,
                        Translator.getText("UI_PressAToStart"),
                        1.0,
                        1.0,
                        1.0,
                        this.clickToSkipAlpha
                     );
               } else {
                  TextManager.instance
                     .DrawStringCentre(
                        UIFont.NewLarge,
                        Core.getInstance().getScreenWidth() / 2,
                        Core.getInstance().getScreenHeight() - 60,
                        Translator.getText("UI_ClickToSkip"),
                        1.0,
                        1.0,
                        1.0,
                        this.clickToSkipAlpha
                     );
               }
            }

            ActiveMods.renderUI();
            Core.getInstance().EndFrameUI();
            UIManager.useUIFBO = var16;
         }
      }
   }

    StateAction update() {
      if (this.bWaitForAssetLoadingToFinish1 && !OutfitManager.instance.isLoadingClothingItems()) {
         if (Core.bDebug) {
            OutfitManager.instance.debugOutfits();
         }

         /* synchronized - TODO: add std::mutex */ (this.assetLock1) {
            this.bWaitForAssetLoadingToFinish1 = false;
            this.assetLock1.notifyAll();
         }
      }

      if (this.bWaitForAssetLoadingToFinish2 && !ModelManager.instance.isLoadingAnimations() && !GameWindow.fileSystem.hasWork()) {
         /* synchronized - TODO: add std::mutex */ (this.assetLock2) {
            this.bWaitForAssetLoadingToFinish2 = false;
            this.assetLock2.notifyAll();

            for (RuntimeAnimationScript var4 : ScriptManager.instance.getAllRuntimeAnimationScripts()) {
               var4.exec();
            }
         }
      }

      if (!unexpectedError && !GameWindow.bServerDisconnected && !playerWrongIP) {
         if (!bDone) {
            return StateAction.Remain;
         } else if (WorldStreamer.instance.isBusy()) {
            return StateAction.Remain;
         } else if (ModelManager.instance.isLoadingAnimations()) {
            return StateAction.Remain;
         } else if (!bShowedClickToSkip) {
            return StateAction.Remain;
         } else {
            if (Mouse.isButtonDown(0)) {
               this.bForceDone = true;
            }

            if (GameWindow.ActivatedJoyPad != nullptr && GameWindow.ActivatedJoyPad.isAPressed()) {
               this.bForceDone = true;
            }

            if (this.bForceDone) {
               SoundManager.instance.playUISound("UIClickToStart");
               this.bForceDone = false;
               return StateAction.Continue;
            } else {
               return StateAction.Remain;
            }
         }
      } else {
         if (!bShowedUI) {
            bShowedUI = true;
            IsoPlayer.setInstance(nullptr);
            IsoPlayer.players[0] = nullptr;
            UIManager.UI.clear();
            LuaEventManager.Reset();
            LuaManager.call("ISGameLoadingUI_OnGameLoadingUI", "");
            UIManager.bSuspend = false;
         }

         if (Keyboard.isKeyDown(1)) {
            GameClient.instance.Shutdown();
            SteamUtils.shutdown();
            System.exit(1);
         }

         return StateAction.Remain;
      }
   }
}
} // namespace gameStates
} // namespace zombie
