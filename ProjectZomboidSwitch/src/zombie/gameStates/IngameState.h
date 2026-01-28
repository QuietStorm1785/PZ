#include "zombie/audio/OpenALSoundEmitter.h"
#pragma once
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

#include "zombie/AmbientStreamManager.h"
#include "zombie/DebugFileWatcher.h"
#include "zombie/FliesSound.h"
#include "zombie/GameSounds.h"
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/IndieGL.h"
#include "zombie/LootRespawn.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaHookManager.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/Lua/MapObjects.h"
#include "zombie/MapCollisionData.h"
#include "zombie/ReanimatedPlayers.h"
#include "zombie/SandboxOptions.h"
#include "zombie/SoundManager.h"
#include "zombie/SystemDisabler.h"
#include "zombie/VirtualZombieManager.h"
#include "zombie/WorldSoundManager.h"
#include "zombie/ZombieSpawnRecorder.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/ZomboidGlobals.h"
#include "zombie/audio/ObjectAmbientEmitters.h"
#include "zombie/characters/AttachedItems/AttachedLocations.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/SurvivorFactory.h"
#include "zombie/characters/WornItems/BodyLocations.h"
#include "zombie/characters/professions/ProfessionFactory.h"
#include "zombie/characters/skills/CustomPerks.h"
#include "zombie/characters/skills/PerkFactory.h"
#include "zombie/characters/traits/TraitFactory.h"
#include "zombie/chat/ChatElement.h"
#include "zombie/core/BoxedStaticValues.h"
#include "zombie/core/Core.h"
#include "zombie/core/Languages.h"
#include "zombie/core/Rand.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/Translator.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/opengl/RenderSettings.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/core/physics/WorldSimulation.h"
#include "zombie/core/skinnedmodel/DeadBodyAtlas.h"
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/core/skinnedmodel/advancedanimation/AdvancedAnimator.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimationSet.h"
#include "zombie/core/skinnedmodel/model/ModelOutlines.h"
#include "zombie/core/skinnedmodel/model/WorldItemAtlas.h"
#include "zombie/core/skinnedmodel/population/BeardStyles.h"
#include "zombie/core/skinnedmodel/population/ClothingDecals.h"
#include "zombie/core/skinnedmodel/population/HairStyles.h"
#include "zombie/core/skinnedmodel/population/OutfitManager.h"
#include "zombie/core/stash/StashSystem.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/core/znet/SteamFriends.h"
#include "zombie/core/znet/SteamUtils.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/debug/LineDrawer.h"
#include "zombie/erosion/ErosionGlobals.h"
#include "zombie/gameStates/GameStateMachine/StateAction.h"
#include "zombie/gameStates/IngameState/s_performance.h"
#include "zombie/globalObjects/CGlobalObjects.h"
#include "zombie/globalObjects/SGlobalObjects.h"
#include "zombie/input/GameKeyboard.h"
#include "zombie/input/JoypadManager.h"
#include "zombie/input/Mouse.h"
#include "zombie/inventory/ItemSoundManager.h"
#include "zombie/iso/BentFences.h"
#include "zombie/iso/BrokenFences.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/ContainerOverlays.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoChunkMap.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMarkers.h"
#include "zombie/iso/IsoMetaCell.h"
#include "zombie/iso/IsoMetaGrid.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/LightingThread.h"
#include "zombie/iso/LotHeader.h"
#include "zombie/iso/SearchMode.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/SpriteDetails/IsoObjectType.h"
#include "zombie/iso/TileOverlays.h"
#include "zombie/iso/WorldMarkers.h"
#include "zombie/iso/WorldStreamer.h"
#include "zombie/iso/areas/isoregion/IsoRegions.h"
#include "zombie/iso/objects/IsoFireManager.h"
#include "zombie/iso/objects/IsoGenerator.h"
#include "zombie/iso/objects/IsoWaveSignal.h"
#include "zombie/iso/objects/RainManager.h"
#include "zombie/iso/sprite/CorpseFlies.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/SkyBox.h"
#include "zombie/iso/weather/ClimateManager.h"
#include "zombie/iso/weather/Temperature.h"
#include "zombie/iso/weather/fx/WeatherFxMask.h"
#include "zombie/meta/Meta.h"
#include "zombie/modding/ActiveMods.h"
#include "zombie/network/BodyDamageSync.h"
#include "zombie/network/ChunkChecksum.h"
#include "zombie/network/ClientServerMap.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ItemTransactionManager.h"
#include "zombie/network/MPStatistics.h"
#include "zombie/network/PassengerMap.h"
#include "zombie/network/ServerGUI.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/popman/ZombiePopulationManager.h"
#include "zombie/radio/ZomboidRadio.h"
#include "zombie/sandbox/CustomSandboxOptions.h"
#include "zombie/savefile/ClientPlayerDB.h"
#include "zombie/savefile/PlayerDB.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/spnetwork/SinglePlayerClient.h"
#include "zombie/spnetwork/SinglePlayerServer.h"
#include "zombie/text/templating/TemplateText.h"
#include "zombie/ui/ActionProgressBar.h"
#include "zombie/ui/FPSGraph.h"
#include "zombie/ui/TextDrawObject.h"
#include "zombie/ui/TextManager.h"
#include "zombie/ui/TutorialManager.h"
#include "zombie/ui/UIElement.h"
#include "zombie/ui/UIManager.h"
#include "zombie/util/StringUtils.h"
#include "zombie/vehicles/EditVehicleState.h"
#include "zombie/vehicles/PolygonalMap2.h"
#include "zombie/vehicles/VehicleCache.h"
#include "zombie/vehicles/VehicleIDMap.h"
#include "zombie/vehicles/VehicleType.h"
#include "zombie/vehicles/VehiclesDB2.h"
#include "zombie/worldMap/WorldMap.h"
#include "zombie/worldMap/WorldMapVisited.h"
#include "zombie/worldMap/editor/WorldMapEditorState.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace gameStates {


class IngameState : public GameState {
public:
    static int WaitMul = 20;
    static IngameState instance;
    static float draww;
    static float drawh;
    static long GameID = 0L;
    static int last = -1;
    static float xPos;
    static float yPos;
    static float offx;
    static float offy;
    static float zoom;
   static std::unordered_map<std::string, int> ContainerTypes = std::make_unique<std::unordered_map<>>();
    static int nSaveCycle = 1800;
    static bool bDoChars = false;
    static bool keySpacePreviousFrame = false;
    long numberTicks = 0L;
    bool Paused = false;
    float SaveDelay = 0.0F;
    bool alt = false;
    int insanityScareCount = 5;
    int insanitypic = -1;
    int timesincelastinsanity = 10000000;
    GameState RedirectState = nullptr;
    bool bDidServerDisconnectState = false;
    bool fpsKeyDown = false;
   private const std::vector<int64_t> debugTimes = std::make_unique<std::vector<>>();
    int tickCount = 0;
    float SadisticMusicDirectorTime;
    bool showAnimationViewer = false;
    bool showAttachmentEditor = false;
    bool showChunkDebugger = false;
    bool showGlobalObjectDebugger = false;
    std::string showVehicleEditor = nullptr;
    std::string showWorldMapEditor = nullptr;

    public IngameState() {
      instance = this;
   }

    static void renderDebugOverhead(IsoCell var0, int var1, int var2, int var3, int var4) {
      Mouse.update();
    int var5 = Mouse.getX();
    int var6 = Mouse.getY();
      var5 -= var3;
      var6 -= var4;
      var5 /= var2;
      var6 /= var2;
      SpriteRenderer.instance.renderi(nullptr, var3, var4, var2 * var0.getWidthInTiles(), var2 * var0.getHeightInTiles(), 0.7F, 0.7F, 0.7F, 1.0F, nullptr);
    IsoGridSquare var7 = var0.getGridSquare(var5 + var0.ChunkMap[0].getWorldXMinTiles(), var6 + var0.ChunkMap[0].getWorldYMinTiles(), 0);
      if (var7 != nullptr) {
    int var8 = 48;
    int var9 = 48;
         TextManager.instance.DrawString(var9, var8, "SQUARE FLAGS", 1.0, 1.0, 1.0, 1.0);
         var8 += 20;
         var9 += 8;

         for (int var10 = 0; var10 < IsoFlagType.MAX.index(); var10++) {
            if (var7.Is(IsoFlagType.fromIndex(var10))) {
               TextManager.instance.DrawString(var9, var8, IsoFlagType.fromIndex(var10), 0.6, 0.6, 0.8, 1.0);
               var8 += 18;
            }
         }

    int var20 = 48;
         var8 += 16;
         TextManager.instance.DrawString(var20, var8, "SQUARE OBJECT TYPES", 1.0, 1.0, 1.0, 1.0);
         var8 += 20;
         var20 += 8;

         for (int var23 = 0; var23 < 64; var23++) {
            if (var7.getHasTypes().isSet(var23)) {
               TextManager.instance.DrawString(var20, var8, IsoObjectType.fromIndex(var23), 0.6, 0.6, 0.8, 1.0);
               var8 += 18;
            }
         }
      }

      for (int var18 = 0; var18 < var0.getWidthInTiles(); var18++) {
         for (int var22 = 0; var22 < var0.getHeightInTiles(); var22++) {
    IsoGridSquare var24 = var0.getGridSquare(var18 + var0.ChunkMap[0].getWorldXMinTiles(), var22 + var0.ChunkMap[0].getWorldYMinTiles(), var1);
            if (var24 != nullptr) {
               if (var24.getProperties().Is(IsoFlagType.solid) || var24.getProperties().Is(IsoFlagType.solidtrans)) {
                  SpriteRenderer.instance.renderi(nullptr, var3 + var18 * var2, var4 + var22 * var2, var2, var2, 0.5F, 0.5F, 0.5F, 255.0F, nullptr);
               } else if (!var24.getProperties().Is(IsoFlagType.exterior)) {
                  SpriteRenderer.instance.renderi(nullptr, var3 + var18 * var2, var4 + var22 * var2, var2, var2, 0.8F, 0.8F, 0.8F, 1.0F, nullptr);
               }

               if (var24.Has(IsoObjectType.tree)) {
                  SpriteRenderer.instance.renderi(nullptr, var3 + var18 * var2, var4 + var22 * var2, var2, var2, 0.4F, 0.8F, 0.4F, 1.0F, nullptr);
               }

               if (var24.getProperties().Is(IsoFlagType.collideN)) {
                  SpriteRenderer.instance.renderi(nullptr, var3 + var18 * var2, var4 + var22 * var2, var2, 1, 0.2F, 0.2F, 0.2F, 1.0F, nullptr);
               }

               if (var24.getProperties().Is(IsoFlagType.collideW)) {
                  SpriteRenderer.instance.renderi(nullptr, var3 + var18 * var2, var4 + var22 * var2, 1, var2, 0.2F, 0.2F, 0.2F, 1.0F, nullptr);
               }
            }
         }
      }
   }

    static float translatePointX(float var0, float var1, float var2, float var3) {
      var0 -= var1;
      var0 *= var2;
      var0 += var3;
      return var0 + draww / 2.0F;
   }

    static float invTranslatePointX(float var0, float var1, float var2, float var3) {
      var0 -= draww / 2.0F;
      var0 -= var3;
      var0 /= var2;
      return var0 + var1;
   }

    static float invTranslatePointY(float var0, float var1, float var2, float var3) {
      var0 -= drawh / 2.0F;
      var0 -= var3;
      var0 /= var2;
      return var0 + var1;
   }

    static float translatePointY(float var0, float var1, float var2, float var3) {
      var0 -= var1;
      var0 *= var2;
      var0 += var3;
      return var0 + drawh / 2.0F;
   }

    static void renderRect(float var0, float var1, float var2, float var3, float var4, float var5, float var6, float var7) {
    float var8 = translatePointX(var0, xPos, zoom, offx);
    float var9 = translatePointY(var1, yPos, zoom, offy);
    float var10 = translatePointX(var0 + var2, xPos, zoom, offx);
    float var11 = translatePointY(var1 + var3, yPos, zoom, offy);
      var2 = var10 - var8;
      var3 = var11 - var9;
      if (!(var8 >= Core.getInstance().getScreenWidth()) && !(var10 < 0.0F) && !(var9 >= Core.getInstance().getScreenHeight()) && !(var11 < 0.0F)) {
         SpriteRenderer.instance.render(nullptr, var8, var9, var2, var3, var4, var5, var6, var7, nullptr);
      }
   }

    static void renderLine(float var0, float var1, float var2, float var3, float var4, float var5, float var6, float var7) {
    float var8 = translatePointX(var0, xPos, zoom, offx);
    float var9 = translatePointY(var1, yPos, zoom, offy);
    float var10 = translatePointX(var2, xPos, zoom, offx);
    float var11 = translatePointY(var3, yPos, zoom, offy);
      if ((!(var8 >= Core.getInstance().getScreenWidth()) || !(var10 >= Core.getInstance().getScreenWidth()))
         && (!(var9 >= Core.getInstance().getScreenHeight()) || !(var11 >= Core.getInstance().getScreenHeight()))
         && (!(var8 < 0.0F) || !(var10 < 0.0F))
         && (!(var9 < 0.0F) || !(var11 < 0.0F))) {
         SpriteRenderer.instance.renderline(nullptr, (int)var8, (int)var9, (int)var10, (int)var11, var4, var5, var6, var7);
      }
   }

    static void renderDebugOverhead2(IsoCell var0, int var1, float var2, int var3, int var4, float var5, float var6, int var7, int var8) {
      draww = var7;
      drawh = var8;
      xPos = var5;
      yPos = var6;
      offx = var3;
      offy = var4;
      zoom = var2;
    float var9 = var0.ChunkMap[0].getWorldXMinTiles();
    float var10 = var0.ChunkMap[0].getWorldYMinTiles();
    float var11 = var0.ChunkMap[0].getWorldXMaxTiles();
    float var12 = var0.ChunkMap[0].getWorldYMaxTiles();
      renderRect(var9, var10, var0.getWidthInTiles(), var0.getWidthInTiles(), 0.7F, 0.7F, 0.7F, 1.0F);

      for (int var13 = 0; var13 < var0.getWidthInTiles(); var13++) {
         for (int var14 = 0; var14 < var0.getHeightInTiles(); var14++) {
    IsoGridSquare var15 = var0.getGridSquare(var13 + var0.ChunkMap[0].getWorldXMinTiles(), var14 + var0.ChunkMap[0].getWorldYMinTiles(), var1);
    float var16 = var13 + var9;
    float var17 = var14 + var10;
            if (var15 != nullptr) {
               if (var15.getProperties().Is(IsoFlagType.solid) || var15.getProperties().Is(IsoFlagType.solidtrans)) {
                  renderRect(var16, var17, 1.0F, 1.0F, 0.5F, 0.5F, 0.5F, 1.0F);
               } else if (!var15.getProperties().Is(IsoFlagType.exterior)) {
                  renderRect(var16, var17, 1.0F, 1.0F, 0.8F, 0.8F, 0.8F, 1.0F);
               }

               if (var15.Has(IsoObjectType.tree)) {
                  renderRect(var16, var17, 1.0F, 1.0F, 0.4F, 0.8F, 0.4F, 1.0F);
               }

               if (var15.getProperties().Is(IsoFlagType.collideN)) {
                  renderRect(var16, var17, 1.0F, 0.2F, 0.2F, 0.2F, 0.2F, 1.0F);
               }

               if (var15.getProperties().Is(IsoFlagType.collideW)) {
                  renderRect(var16, var17, 0.2F, 1.0F, 0.2F, 0.2F, 0.2F, 1.0F);
               }
            }
         }
      }

    IsoMetaGrid var20 = IsoWorld.instance.MetaGrid;
      renderRect(var20.minX * 300, var20.minY * 300, var20.getWidth() * 300, var20.getHeight() * 300, 1.0F, 1.0F, 1.0F, 0.05F);
      if (var2 > 0.1) {
         for (int var21 = var20.minY; var21 <= var20.maxY; var21++) {
            renderLine(var20.minX * 300, var21 * 300, (var20.maxX + 1) * 300, var21 * 300, 1.0F, 1.0F, 1.0F, 0.15F);
         }

         for (int var22 = var20.minX; var22 <= var20.maxX; var22++) {
            renderLine(var22 * 300, var20.minY * 300, var22 * 300, (var20.maxY + 1) * 300, 1.0F, 1.0F, 1.0F, 0.15F);
         }
      }

      IsoMetaCell[][] var23 = IsoWorld.instance.MetaGrid.Grid;

      for (int var24 = 0; var24 < var23.length; var24++) {
         for (int var25 = 0; var25 < var23[0].length; var25++) {
    LotHeader var26 = var23[var24][var25].info;
            if (var26 == nullptr) {
               renderRect((var20.minX + var24) * 300 + 1, (var20.minY + var25) * 300 + 1, 298.0F, 298.0F, 0.2F, 0.0F, 0.0F, 0.3F);
            } else {
               for (int var18 = 0; var18 < var26.Buildings.size(); var18++) {
    BuildingDef var19 = (BuildingDef)var26.Buildings.get(var18);
                  if (var19.bAlarmed) {
                     renderRect(var19.getX(), var19.getY(), var19.getW(), var19.getH(), 0.8F, 0.8F, 0.5F, 0.3F);
                  } else {
                     renderRect(var19.getX(), var19.getY(), var19.getW(), var19.getH(), 0.5F, 0.5F, 0.8F, 0.3F);
                  }
               }
            }
         }
      }
   }

    static void copyWorld(const std::string& var0, const std::string& var1) {
    std::string var2 = ZomboidFileSystem.instance.getGameModeCacheDir() + File.separator + var0 + File.separator;
      var2 = var2.replace("/", File.separator);
      var2 = var2.replace("\\", File.separator);
    std::string var3 = var2.substr(0, var2.lastIndexOf(File.separator));
      var3 = var3.replace("\\", "/");
    File var4 = std::make_shared<File>(var3);
      var2 = ZomboidFileSystem.instance.getGameModeCacheDir() + File.separator + var1 + File.separator;
      var2 = var2.replace("/", File.separator);
      var2 = var2.replace("\\", File.separator);
    std::string var5 = var2.substr(0, var2.lastIndexOf(File.separator));
      var5 = var5.replace("\\", "/");
    File var6 = std::make_shared<File>(var5);

      try {
         copyDirectory(var4, var6);
      } catch (IOException var8) {
         var8.printStackTrace();
      }
   }

    static void copyDirectory(File var0, File var1) {
      if (var0.isDirectory()) {
         if (!var1.exists()) {
            var1.mkdir();
         }

         std::string[] var2 = var0.list();
    bool var3 = GameLoadingState.convertingFileMax == -1;
         if (var3) {
            GameLoadingState.convertingFileMax = var2.length;
         }

         for (int var4 = 0; var4 < var2.length; var4++) {
            if (var3) {
               GameLoadingState.convertingFileCount++;
            }

            copyDirectory(std::make_shared<File>(var0, var2[var4]), std::make_shared<File>(var1, var2[var4]));
         }
      } else {
    FileInputStream var5 = std::make_shared<FileInputStream>(var0);
    FileOutputStream var6 = std::make_shared<FileOutputStream>(var1);
         var6.getChannel().transferFrom(var5.getChannel(), 0L, var0.length());
         var5.close();
         var6.close();
      }
   }

    static void createWorld(const std::string& var0) {
      var0 = var0.replace(" ", "_").trim();
    std::string var1 = ZomboidFileSystem.instance.getGameModeCacheDir() + File.separator + var0 + File.separator;
      var1 = var1.replace("/", File.separator);
      var1 = var1.replace("\\", File.separator);
    std::string var2 = var1.substr(0, var1.lastIndexOf(File.separator));
      var2 = var2.replace("\\", "/");
    File var3 = std::make_shared<File>(var2);
      if (!var3.exists()) {
         var3.mkdirs();
      }

      Core.GameSaveWorld = var0;
   }

    void debugFullyStreamedIn(int var1, int var2) {
    IsoGridSquare var3 = IsoWorld.instance.CurrentCell.getGridSquare(var1, var2, 0);
      if (var3 != nullptr) {
         if (var3.getBuilding() != nullptr) {
    BuildingDef var4 = var3.getBuilding().getDef();
            if (var4 != nullptr) {
    bool var5 = var4.isFullyStreamedIn();

               for (byte var6 = 0; var6 < var4.overlappedChunks.size(); var6 += 2) {
    short var7 = var4.overlappedChunks.get(var6);
    short var8 = var4.overlappedChunks.get(var6 + 1);
                  if (var5) {
                     renderRect(var7 * 10, var8 * 10, 10.0F, 10.0F, 0.0F, 1.0F, 0.0F, 0.5F);
                  } else {
                     renderRect(var7 * 10, var8 * 10, 10.0F, 10.0F, 1.0F, 0.0F, 0.0F, 0.5F);
                  }
               }
            }
         }
      }
   }

    void UpdateStuff() {
      GameClient.bIngame = true;
      this.SaveDelay = this.SaveDelay + GameTime.instance.getMultiplier();
      if (this.SaveDelay / 60.0F > 30.0F) {
         this.SaveDelay = 0.0F;
      }

      GameTime.instance.LastLastTimeOfDay = GameTime.instance.getLastTimeOfDay();
      GameTime.instance.setLastTimeOfDay(GameTime.getInstance().getTimeOfDay());
    bool var1 = false;
      if (!GameServer.bServer && IsoPlayer.getInstance() != nullptr) {
         var1 = IsoPlayer.allPlayersAsleep();
      }

      GameTime.getInstance().update(var1 && UIManager.getFadeAlpha() == 1.0);
      if (!this.Paused) {
         ScriptManager.instance.update();
      }

      if (!this.Paused) {
    long var2 = System.nanoTime();

         try {
            WorldSoundManager.instance.update();
         } catch (Exception var14) {
            ExceptionLogger.logException(var14);
         }

         try {
            IsoFireManager.Update();
         } catch (Exception var13) {
            ExceptionLogger.logException(var13);
         }

         try {
            RainManager.Update();
         } catch (Exception var12) {
            ExceptionLogger.logException(var12);
         }

         Meta.instance.update();

         try {
            VirtualZombieManager.instance.update();
            MapCollisionData.instance.updateMain();
            ZombiePopulationManager.instance.updateMain();
            PolygonalMap2.instance.updateMain();
         } catch (Exception var10) {
            ExceptionLogger.logException(var10);
         } catch (Error var11) {
            var11.printStackTrace();
         }

         try {
            LootRespawn.update();
         } catch (Exception var9) {
            ExceptionLogger.logException(var9);
         }

         if (GameServer.bServer) {
            try {
               AmbientStreamManager.instance.update();
            } catch (Exception var8) {
               ExceptionLogger.logException(var8);
            }
         } else {
            ObjectAmbientEmitters.getInstance().update();
         }

         if (GameClient.bClient) {
            try {
               BodyDamageSync.instance.update();
            } catch (Exception var7) {
               ExceptionLogger.logException(var7);
            }
         }

         if (!GameServer.bServer) {
            try {
               ItemSoundManager.update();
               FliesSound.instance.update();
               CorpseFlies.update();
               LuaManager.call("SadisticMusicDirectorTick", nullptr);
               WorldMapVisited.update();
            } catch (Exception var6) {
               ExceptionLogger.logException(var6);
            }
         }

         SearchMode.getInstance().update();
         RenderSettings.getInstance().update();
    long var4 = System.nanoTime();
      }
   }

    void enter() {
      UIManager.useUIFBO = Core.getInstance().supportsFBO() && Core.OptionUIFBO;
      if (!Core.getInstance().getUseShaders()) {
         Core.getInstance().RenderShader = nullptr;
      }

      GameSounds.fix3DListenerPosition(false);
      IsoPlayer.getInstance().updateUsername();
      IsoPlayer.getInstance().setSceneCulled(false);
      IsoPlayer.getInstance().getInventory().addItemsToProcessItems();
      GameID = (long)Rand.Next(10000000);
      GameID = GameID + Rand.Next(10000000);
      GameID = GameID + Rand.Next(10000000);
      GameID = GameID + Rand.Next(10000000);
      GameID = GameID + Rand.Next(10000000);
      GameID = GameID + Rand.Next(10000000);
      GameID = GameID + Rand.Next(10000000);
      GameID = GameID + Rand.Next(10000000);
      GameID = GameID + Rand.Next(10000000);
      GameID = GameID + Rand.Next(10000000);
      GameID = GameID + Rand.Next(10000000);
      GameID = GameID + Rand.Next(10000000);
      GameID = GameID + Rand.Next(10000000);
      GameID = GameID + Rand.Next(10000000);
      GameID = GameID + Rand.Next(10000000);
      GameID = GameID + Rand.Next(10000000);
      GameID = GameID + Rand.Next(10000000);
      GameID = GameID + Rand.Next(10000000);
      GameID = GameID + Rand.Next(10000000);
      GameID = GameID + Rand.Next(10000000);
      GameID = GameID + Rand.Next(10000000);
      GameID = GameID + Rand.Next(10000000);
      ZombieSpawnRecorder.instance.init();
      if (!GameServer.bServer) {
         IsoWorld.instance.CurrentCell.ChunkMap[0].processAllLoadGridSquare();
         IsoWorld.instance.CurrentCell.ChunkMap[0].update();
         if (!GameClient.bClient) {
            LightingThread.instance.GameLoadingUpdate();
         }
      }

      try {
         MapCollisionData.instance.startGame();
      } catch (Throwable var3) {
         ExceptionLogger.logException(var3);
      }

      IsoWorld.instance.CurrentCell.putInVehicle(IsoPlayer.getInstance());
      SoundManager.instance.setMusicState("Tutorial" == Core.GameMode) ? "Tutorial" : "InGame");
      ClimateManager.getInstance().update();
      LuaEventManager.triggerEvent("OnGameStart");
      LuaEventManager.triggerEvent("OnLoad");
      if (GameClient.bClient) {
         GameClient.instance.sendPlayerConnect(IsoPlayer.getInstance());
         DebugLog.log("Waiting for player-connect response from server");

         for (; IsoPlayer.getInstance().OnlineID == -1; GameClient.instance.update()) {
            try {
               Thread.sleep(10L);
            } catch (InterruptedException var2) {
               var2.printStackTrace();
            }
         }

         ClimateManager.getInstance().update();
         LightingThread.instance.GameLoadingUpdate();
      }

      if (GameClient.bClient && SteamUtils.isSteamModeEnabled()) {
         SteamFriends.UpdateRichPresenceConnectionInfo("In game", "+connect " + GameClient.ip + ":" + GameClient.port);
      }
   }

    void exit() {
      DebugLog.log("EXITDEBUG: IngameState.exit 1");
      if (SteamUtils.isSteamModeEnabled()) {
         SteamFriends.UpdateRichPresenceConnectionInfo("", "");
      }

      UIManager.useUIFBO = false;
      if (FPSGraph.instance != nullptr) {
         FPSGraph.instance.setVisible(false);
      }

      UIManager.updateBeforeFadeOut();
      SoundManager.instance.setMusicState("MainMenu");
    long var1 = System.currentTimeMillis();
    bool var3 = UIManager.useUIFBO;
      UIManager.useUIFBO = false;
      DebugLog.log("EXITDEBUG: IngameState.exit 2");

      while (true) {
    float var4 = Math.min(1.0F, (float)(System.currentTimeMillis() - var1) / 500.0F);
    bool var5 = true;

         for (int var6 = 0; var6 < IsoPlayer.numPlayers; var6++) {
            if (IsoPlayer.players[var6] != nullptr) {
               IsoPlayer.setInstance(IsoPlayer.players[var6]);
               IsoCamera.CamCharacter = IsoPlayer.players[var6];
               IsoSprite.globalOffsetX = -1.0F;
               Core.getInstance().StartFrame(var6, var5);
               IsoCamera.frameState.set(var6);
               IsoWorld.instance.render();
               Core.getInstance().EndFrame(var6);
               var5 = false;
            }
         }

         Core.getInstance().RenderOffScreenBuffer();
         Core.getInstance().StartFrameUI();
         UIManager.render();
         UIManager.DrawTexture(UIManager.getBlack(), 0.0, 0.0, Core.getInstance().getScreenWidth(), Core.getInstance().getScreenHeight(), var4);
         Core.getInstance().EndFrameUI();
         DebugLog.log("EXITDEBUG: IngameState.exit 3 (alpha=" + var4 + ")");
         if (var4 >= 1.0F) {
            UIManager.useUIFBO = var3;
            DebugLog.log("EXITDEBUG: IngameState.exit 4");
            RenderThread.setWaitForRenderState(false);
            SpriteRenderer.instance.notifyRenderStateQueue();

            while (WorldStreamer.instance.isBusy()) {
               try {
                  Thread.sleep(1L);
               } catch (InterruptedException var10) {
                  var10.printStackTrace();
               }
            }

            DebugLog.log("EXITDEBUG: IngameState.exit 5");
            WorldStreamer.instance.stop();
            LightingThread.instance.stop();
            MapCollisionData.instance.stop();
            ZombiePopulationManager.instance.stop();
            PolygonalMap2.instance.stop();
            DebugLog.log("EXITDEBUG: IngameState.exit 6");

            for (int var12 = 0; var12 < IsoWorld.instance.CurrentCell.ChunkMap.length; var12++) {
    IsoChunkMap var15 = IsoWorld.instance.CurrentCell.ChunkMap[var12];

               for (int var17 = 0; var17 < IsoChunkMap.ChunkGridWidth * IsoChunkMap.ChunkGridWidth; var17++) {
    IsoChunk var7 = var15.getChunk(var17 % IsoChunkMap.ChunkGridWidth, var17 / IsoChunkMap.ChunkGridWidth);
                  if (var7 != nullptr && var7.refs.contains(var15)) {
                     var7.refs.remove(var15);
                     if (var7.refs.empty()) {
                        var7.removeFromWorld();
                        var7.doReuseGridsquares();
                     }
                  }
               }
            }

            ModelManager.instance.Reset();

            for (int var13 = 0; var13 < 4; var13++) {
               IsoPlayer.players[var13] = nullptr;
            }

            IsoPlayer.Reset();
            ZombieSpawnRecorder.instance.quit();
            DebugLog.log("EXITDEBUG: IngameState.exit 7");
            IsoPlayer.numPlayers = 1;
            Core.getInstance().OffscreenBuffer.destroy();
            WeatherFxMask.destroy();
            IsoRegions.reset();
            Temperature.reset();
            WorldMarkers.instance.reset();
            IsoMarkers.instance.reset();
            SearchMode.reset();
            ZomboidRadio.getInstance().Reset();
            IsoWaveSignal.Reset();
            ErosionGlobals.Reset();
            IsoGenerator.Reset();
            StashSystem.Reset();
            LootRespawn.Reset();
            VehicleCache.Reset();
            VehicleIDMap.instance.Reset();
            IsoWorld.instance.KillCell();
            ItemSoundManager.Reset();
            IsoChunk.Reset();
            ChunkChecksum.Reset();
            ClientServerMap.Reset();
            SinglePlayerClient.Reset();
            SinglePlayerServer.Reset();
            PassengerMap.Reset();
            DeadBodyAtlas.instance.Reset();
            WorldItemAtlas.instance.Reset();
            CorpseFlies.Reset();
            if (PlayerDB.isAvailable()) {
               PlayerDB.getInstance().close();
            }

            VehiclesDB2.instance.Reset();
            WorldMap.Reset();
            WorldStreamer.instance = std::make_unique<WorldStreamer>();
            WorldSimulation.instance.destroy();
            WorldSimulation.instance = std::make_unique<WorldSimulation>();
            DebugLog.log("EXITDEBUG: IngameState.exit 8");
            VirtualZombieManager.instance.Reset();
            VirtualZombieManager.instance = std::make_unique<VirtualZombieManager>();
            ReanimatedPlayers.instance = std::make_unique<ReanimatedPlayers>();
            ScriptManager.instance.Reset();
            GameSounds.Reset();
            VehicleType.Reset();
            TemplateText.Reset();
            LuaEventManager.Reset();
            MapObjects.Reset();
            CGlobalObjects.Reset();
            SGlobalObjects.Reset();
            AmbientStreamManager.instance.stop();
            SoundManager.instance.stop();
            IsoPlayer.setInstance(nullptr);
            IsoCamera.CamCharacter = nullptr;
            TutorialManager.instance.StealControl = false;
            UIManager.init();
            ScriptManager.instance.Reset();
            ClothingDecals.Reset();
            BeardStyles.Reset();
            HairStyles.Reset();
            OutfitManager.Reset();
            AnimationSet.Reset();
            GameSounds.Reset();
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
            LuaManager.init();
            JoypadManager.instance.Reset();
            GameKeyboard.doLuaKeyPressed = true;
            GameWindow.ActivatedJoyPad = nullptr;
            GameWindow.OkToSaveOnExit = false;
            GameWindow.bLoadedAsClient = false;
            Core.bLastStand = false;
            Core.ChallengeID = nullptr;
            Core.bTutorial = false;
            Core.getInstance().setChallenge(false);
            Core.getInstance().setForceSnow(false);
            Core.getInstance().setZombieGroupSound(true);
            Core.getInstance().setFlashIsoCursor(false);
            SystemDisabler.Reset();
            Texture.nullTextures.clear();
            DebugLog.log("EXITDEBUG: IngameState.exit 9");
            ZomboidFileSystem.instance.Reset();
            if (!Core.SoundDisabled && !GameServer.bServer) {

            }

            try {
               ZomboidFileSystem.instance.init();
            } catch (IOException var9) {
               ExceptionLogger.logException(var9);
            }

            Core.OptionModsEnabled = true;
            DebugLog.log("EXITDEBUG: IngameState.exit 10");
            ZomboidFileSystem.instance.loadMods("default");
            ZomboidFileSystem.instance.loadModPackFiles();
            Languages.instance.init();
            Translator.loadFiles();
            DebugLog.log("EXITDEBUG: IngameState.exit 11");
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
            DebugLog.log("EXITDEBUG: IngameState.exit 12");

            try {
               TextManager.instance.Init();
               LuaManager.LoadDirBase();
            } catch (Exception var8) {
               ExceptionLogger.logException(var8);
            }

            ZomboidGlobals.Load();
            DebugLog.log("EXITDEBUG: IngameState.exit 13");
            LuaEventManager.triggerEvent("OnGameBoot");
            SoundManager.instance.resumeSoundAndMusic();

            for (IsoPlayer var19 : IsoPlayer.players) {
               if (var19 != nullptr) {
                  var19.dirtyRecalcGridStack = true;
               }
            }

            RenderThread.setWaitForRenderState(true);
            DebugLog.log("EXITDEBUG: IngameState.exit 14");
            return;
         }

         try {
            Thread.sleep(33L);
         } catch (Exception var11) {
         }
      }
   }

    void yield() {
      SoundManager.instance.setMusicState("PauseMenu");
   }

    GameState redirectState() {
      if (this.RedirectState != nullptr) {
    GameState var1 = this.RedirectState;
         this.RedirectState = nullptr;
    return var1;
      } else {
         return std::make_unique<MainScreenState>();
      }
   }

    void reenter() {
      SoundManager.instance.setMusicState("InGame");
   }

    void renderframetext(int var1) {
      s_performance.renderFrameText.invokeAndMeasure(this, var1, IngameState::renderFrameTextInternal);
   }

    void renderFrameTextInternal(int var1) {
      IndieGL.disableAlphaTest();
      IndieGL.glDisable(2929);
    std::vector var2 = UIManager.getUI();

      for (int var3 = 0; var3 < var2.size(); var3++) {
    UIElement var4 = (UIElement)var2.get(var3);
         if (!(dynamic_cast<ActionProgressBar*>(var4) != nullptr)
            && var4.isVisible()
            && var4.isFollowGameWorld()
            && (var4.getRenderThisPlayerOnly() == -1 || var4.getRenderThisPlayerOnly() == var1)) {
            var4.render();
         }
      }

    ActionProgressBar var6 = UIManager.getProgressBar(var1);
      if (var6 != nullptr && var6.isVisible()) {
         var6.render();
      }

      WorldMarkers.instance.render();
      IsoMarkers.instance.render();
      TextDrawObject.RenderBatch(var1);
      ChatElement.RenderBatch(var1);

      try {
         Core.getInstance().EndFrameText(var1);
      } catch (Exception var5) {
      }
   }

    void renderframe(int var1) {
      s_performance.renderFrame.invokeAndMeasure(this, var1, IngameState::renderFrameInternal);
   }

    void renderFrameInternal(int var1) {
      if (IsoPlayer.getInstance() == nullptr) {
         IsoPlayer.setInstance(IsoPlayer.players[0]);
         IsoCamera.CamCharacter = IsoPlayer.getInstance();
      }

      RenderSettings.getInstance().applyRenderSettings(var1);
    ActionProgressBar var2 = UIManager.getProgressBar(var1);
      if (var2 != nullptr) {
         var2.update(var1);
      }

      IndieGL.disableAlphaTest();
      IndieGL.glDisable(2929);
      if (IsoPlayer.getInstance() != nullptr && !IsoPlayer.getInstance().isAsleep() || UIManager.getFadeAlpha(var1) < 1.0F) {
         ModelOutlines.instance.startFrameMain(var1);
         IsoWorld.instance.render();
         ModelOutlines.instance.endFrameMain(var1);
         RenderSettings.getInstance().legacyPostRender(var1);
         LuaEventManager.triggerEvent("OnPostRender");
      }

      LineDrawer.clear();
      if (Core.bDebug && GameKeyboard.isKeyPressed(Core.getInstance().getKey("ToggleAnimationText"))) {
         DebugOptions.instance.Animation.Debug.setValue(!DebugOptions.instance.Animation.Debug.getValue());
      }

      try {
         Core.getInstance().EndFrame(var1);
      } catch (Exception var4) {
      }
   }

    void renderframeui() {
      s_performance.renderFrameUI.invokeAndMeasure(this, IngameState::renderFrameUI);
   }

    void renderFrameUI() {
      if (Core.getInstance().StartFrameUI()) {
         TextManager.instance.DrawTextFromGameWorld();
         SkyBox.getInstance().draw();
         UIManager.render();
         ZomboidRadio.getInstance().render();
         if (Core.bDebug && IsoPlayer.getInstance() != nullptr && IsoPlayer.getInstance().isGhostMode()) {
            IsoWorld.instance.CurrentCell.ChunkMap[0].drawDebugChunkMap();
         }

         DeadBodyAtlas.instance.renderUI();
         WorldItemAtlas.instance.renderUI();
         if (Core.bDebug) {
            if (GameKeyboard.isKeyDown(Core.getInstance().getKey("Display FPS"))) {
               if (!this.fpsKeyDown) {
                  this.fpsKeyDown = true;
                  if (FPSGraph.instance == nullptr) {
                     FPSGraph.instance = std::make_unique<FPSGraph>();
                  }

                  FPSGraph.instance.setVisible(!FPSGraph.instance.isVisible());
               }
            } else {
               this.fpsKeyDown = false;
            }

            if (FPSGraph.instance != nullptr) {
               FPSGraph.instance.render();
            }
         }

         if (!GameServer.bServer) {
            for (int var1 = 0; var1 < IsoPlayer.numPlayers; var1++) {
    IsoPlayer var2 = IsoPlayer.players[var1];
               if (var2 != nullptr && !var2.isDead() && var2.isAsleep()) {
    float var3 = GameClient.bFastForward ? GameTime.getInstance().ServerTimeOfDay : GameTime.getInstance().getTimeOfDay();
    float var4 = (var3 - (int)var3) * 60.0F;
    std::string var5 = "media/ui/SleepClock" + (int)var4 / 10 + ".png";
    Texture var6 = Texture.getSharedTexture(var5);
                  if (var6 == nullptr) {
                     break;
                  }

    int var7 = IsoCamera.getScreenLeft(var1);
    int var8 = IsoCamera.getScreenTop(var1);
    int var9 = IsoCamera.getScreenWidth(var1);
    int var10 = IsoCamera.getScreenHeight(var1);
                  SpriteRenderer.instance
                     .renderi(
                        var6,
                        var7 + var9 / 2 - var6.getWidth() / 2,
                        var8 + var10 / 2 - var6.getHeight() / 2,
                        var6.getWidth(),
                        var6.getHeight(),
                        1.0F,
                        1.0F,
                        1.0F,
                        1.0F,
                        nullptr
                     );
               }
            }
         }

         ActiveMods.renderUI();
         JoypadManager.instance.renderUI();
      }

      if (Core.bDebug && DebugOptions.instance.Animation.AnimRenderPicker.getValue() && IsoPlayer.players[0] != nullptr) {
         IsoPlayer.players[0].advancedAnimator.render();
      }

      if (Core.bDebug) {
         ModelOutlines.instance.renderDebug();
      }

      Core.getInstance().EndFrameUI();
   }

    void render() {
      s_performance.render.invokeAndMeasure(this, IngameState::renderInternal);
   }

    void renderInternal() {
    bool var1 = true;

      for (int var2 = 0; var2 < IsoPlayer.numPlayers; var2++) {
         if (IsoPlayer.players[var2] == nullptr) {
            if (var2 == 0) {
               SpriteRenderer.instance.prePopulating();
            }
         } else {
            IsoPlayer.setInstance(IsoPlayer.players[var2]);
            IsoCamera.CamCharacter = IsoPlayer.players[var2];
            Core.getInstance().StartFrame(var2, var1);
            IsoCamera.frameState.set(var2);
            var1 = false;
            IsoSprite.globalOffsetX = -1.0F;
            this.renderframe(var2);
         }
      }

      if (DebugOptions.instance.OffscreenBuffer.Render.getValue()) {
         Core.getInstance().RenderOffScreenBuffer();
      }

      for (int var3 = 0; var3 < IsoPlayer.numPlayers; var3++) {
         if (IsoPlayer.players[var3] != nullptr) {
            IsoPlayer.setInstance(IsoPlayer.players[var3]);
            IsoCamera.CamCharacter = IsoPlayer.players[var3];
            IsoCamera.frameState.set(var3);
            Core.getInstance().StartFrameText(var3);
            this.renderframetext(var3);
         }
      }

      UIManager.resize();
      this.renderframeui();
   }

    StateAction update() {
    StateAction var1;
      try {
         s_performance.update.start();
         var1 = this.updateInternal();
      } finally {
         s_performance.update.end();
      }

    return var1;
   }

    StateAction updateInternal() {
      this.tickCount++;
      if (this.tickCount < 60) {
         for (int var1 = 0; var1 < IsoPlayer.numPlayers; var1++) {
            if (IsoPlayer.players[var1] != nullptr) {
               IsoPlayer.players[var1].dirtyRecalcGridStackTime = 20.0F;
            }
         }
      }

      LuaEventManager.triggerEvent("OnTickEvenPaused", BoxedStaticValues.toDouble(this.numberTicks));
      DebugFileWatcher.instance.update();
      AdvancedAnimator.checkModifiedFiles();
      if (Core.bDebug) {
         this.debugTimes.clear();
         this.debugTimes.push_back(System.nanoTime());
      }

      if (Core.bExiting) {
         DebugLog.log("EXITDEBUG: IngameState.updateInternal 1");
         Core.bExiting = false;
         if (GameClient.bClient) {
            for (int var16 = 0; var16 < IsoPlayer.numPlayers; var16++) {
    IsoPlayer var18 = IsoPlayer.players[var16];
               if (var18 != nullptr) {
                  ClientPlayerDB.getInstance().clientSendNetworkPlayerInt(var18);
               }
            }

            try {
               Thread.sleep(500L);
            } catch (InterruptedException var6) {
            }

            WorldStreamer.instance.stop();
            GameClient.instance.doDisconnect("exiting");
         }

         DebugLog.log("EXITDEBUG: IngameState.updateInternal 2");
         if (PlayerDB.isAllow()) {
            PlayerDB.getInstance().saveLocalPlayersForce();
            PlayerDB.getInstance().m_canSavePlayers = false;
         }

         if (ClientPlayerDB.isAllow()) {
            ClientPlayerDB.getInstance().canSavePlayers = false;
         }

         try {
            GameWindow.save(true);
         } catch (Throwable var5) {
            ExceptionLogger.logException(var5);
         }

         DebugLog.log("EXITDEBUG: IngameState.updateInternal 3");

         try {
            LuaEventManager.triggerEvent("OnPostSave");
         } catch (Exception var4) {
            ExceptionLogger.logException(var4);
         }

         if (ClientPlayerDB.isAllow()) {
            ClientPlayerDB.getInstance().close();
         }

         return StateAction.Continue;
      } else if (GameWindow.bServerDisconnected) {
         TutorialManager.instance.StealControl = true;
         if (!this.bDidServerDisconnectState) {
            this.bDidServerDisconnectState = true;
            this.RedirectState = std::make_unique<ServerDisconnectState>();
            return StateAction.Yield;
         } else {
            GameClient.connection = nullptr;
            GameClient.instance.bConnected = false;
            GameClient.bClient = false;
            GameWindow.bServerDisconnected = false;
            return StateAction.Continue;
         }
      } else {
         if (Core.bDebug) {
            if (this.showGlobalObjectDebugger || GameKeyboard.isKeyPressed(60) && GameKeyboard.isKeyDown(29)) {
               this.showGlobalObjectDebugger = false;
               DebugLog.General.debugln("Activating DebugGlobalObjectState.");
               this.RedirectState = std::make_unique<DebugGlobalObjectState>();
               return StateAction.Yield;
            }

            if (this.showChunkDebugger || GameKeyboard.isKeyPressed(60)) {
               this.showChunkDebugger = false;
               DebugLog.General.debugln("Activating DebugChunkState.");
               this.RedirectState = DebugChunkState.checkInstance();
               return StateAction.Yield;
            }

            if (this.showAnimationViewer || GameKeyboard.isKeyPressed(65) && GameKeyboard.isKeyDown(29)) {
               this.showAnimationViewer = false;
               DebugLog.General.debugln("Activating AnimationViewerState.");
    AnimationViewerState var15 = AnimationViewerState.checkInstance();
               this.RedirectState = var15;
               return StateAction.Yield;
            }

            if (this.showAttachmentEditor || GameKeyboard.isKeyPressed(65) && GameKeyboard.isKeyDown(42)) {
               this.showAttachmentEditor = false;
               DebugLog.General.debugln("Activating AttachmentEditorState.");
    AttachmentEditorState var14 = AttachmentEditorState.checkInstance();
               this.RedirectState = var14;
               return StateAction.Yield;
            }

            if (this.showVehicleEditor != nullptr || GameKeyboard.isKeyPressed(65)) {
               DebugLog.General.debugln("Activating EditVehicleState.");
    EditVehicleState var13 = EditVehicleState.checkInstance();
               if (!StringUtils.isNullOrWhitespace(this.showVehicleEditor)) {
                  var13.setScript(this.showVehicleEditor);
               }

               this.showVehicleEditor = nullptr;
               this.RedirectState = var13;
               return StateAction.Yield;
            }

            if (this.showWorldMapEditor != nullptr || GameKeyboard.isKeyPressed(66)) {
    WorldMapEditorState var12 = WorldMapEditorState.checkInstance();
               this.showWorldMapEditor = nullptr;
               this.RedirectState = var12;
               return StateAction.Yield;
            }
         }

         if (Core.bDebug) {
            this.debugTimes.push_back(System.nanoTime());
         }

         this.timesincelastinsanity++;
         if (Core.bDebug) {
            this.debugTimes.push_back(System.nanoTime());
         }

         try {
            if (!GameServer.bServer && IsoPlayer.getInstance() != nullptr && IsoPlayer.allPlayersDead()) {
               if (IsoPlayer.getInstance() != nullptr) {
                  UIManager.getSpeedControls().SetCurrentGameSpeed(1);
               }

               IsoCamera.update();
            }

            this.alt = !this.alt;
            if (!GameServer.bServer) {
               WaitMul = 1;
               if (UIManager.getSpeedControls() != nullptr) {
                  if (UIManager.getSpeedControls().getCurrentGameSpeed() == 2) {
                     WaitMul = 15;
                  }

                  if (UIManager.getSpeedControls().getCurrentGameSpeed() == 3) {
                     WaitMul = 30;
                  }
               }
            }

            if (Core.bDebug) {
               this.debugTimes.push_back(System.nanoTime());
            }

            if (GameServer.bServer) {
               if (GameServer.Players.empty() && ServerOptions.instance.PauseEmpty.getValue()) {
                  this.Paused = true;
               } else {
                  this.Paused = false;
               }
            }

            if (!this.Paused || GameClient.bClient) {
               try {
                  if (IsoCamera.CamCharacter != nullptr && IsoWorld.instance.bDoChunkMapUpdate) {
                     for (int var11 = 0; var11 < IsoPlayer.numPlayers; var11++) {
                        if (IsoPlayer.players[var11] != nullptr && !IsoWorld.instance.CurrentCell.ChunkMap[var11].ignore) {
                           if (!GameServer.bServer) {
                              IsoCamera.CamCharacter = IsoPlayer.players[var11];
                              IsoPlayer.setInstance(IsoPlayer.players[var11]);
                           }

                           if (!GameServer.bServer) {
                              IsoWorld.instance.CurrentCell.ChunkMap[var11].ProcessChunkPos(IsoCamera.CamCharacter);
                           }
                        }
                     }
                  }

                  if (Core.bDebug) {
                     this.debugTimes.push_back(System.nanoTime());
                  }

                  IsoWorld.instance.update();
                  if (Core.bDebug) {
                     this.debugTimes.push_back(System.nanoTime());
                  }

                  ZomboidRadio.getInstance().update();
                  this.UpdateStuff();
                  LuaEventManager.triggerEvent("OnTick", (double)this.numberTicks);
                  this.numberTicks = Math.max(this.numberTicks + 1L, 0L);
               } catch (Exception var9) {
                  ExceptionLogger.logException(var9);
                  if (!GameServer.bServer) {
                     if (GameClient.bClient) {
                        for (int var2 = 0; var2 < IsoPlayer.numPlayers; var2++) {
    IsoPlayer var3 = IsoPlayer.players[var2];
                           if (var3 != nullptr) {
                              ClientPlayerDB.getInstance().clientSendNetworkPlayerInt(var3);
                           }
                        }

                        WorldStreamer.instance.stop();
                     }

    std::string var17 = Core.GameSaveWorld;
                     createWorld(Core.GameSaveWorld + "_crash");
                     copyWorld(var17, Core.GameSaveWorld);
                     if (GameClient.bClient) {
                        if (PlayerDB.isAllow()) {
                           PlayerDB.getInstance().saveLocalPlayersForce();
                           PlayerDB.getInstance().m_canSavePlayers = false;
                        }

                        if (ClientPlayerDB.isAllow()) {
                           ClientPlayerDB.getInstance().canSavePlayers = false;
                        }
                     }

                     try {
                        GameWindow.save(true);
                     } catch (Throwable var8) {
                        ExceptionLogger.logException(var8);
                     }

                     if (GameClient.bClient) {
                        try {
                           LuaEventManager.triggerEvent("OnPostSave");
                        } catch (Exception var7) {
                           ExceptionLogger.logException(var7);
                        }

                        if (ClientPlayerDB.isAllow()) {
                           ClientPlayerDB.getInstance().close();
                        }
                     }
                  }

                  if (GameClient.bClient) {
                     GameClient.instance.doDisconnect("crash");
                  }

                  return StateAction.Continue;
               }
            }
         } catch (Exception var10) {
            System.err.println("IngameState.update caught an exception.");
            ExceptionLogger.logException(var10);
         }

         if (Core.bDebug) {
            this.debugTimes.push_back(System.nanoTime());
         }

         if (!GameServer.bServer || ServerGUI.isCreated()) {
            ModelManager.instance.update();
         }

         if (Core.bDebug && FPSGraph.instance != nullptr) {
            FPSGraph.instance.addUpdate(System.currentTimeMillis());
            FPSGraph.instance.update();
         }

         if (GameClient.bClient || GameServer.bServer) {
            ItemTransactionManager.update();
            MPStatistics.Update();
         }

         return StateAction.Remain;
      }
   }
}
} // namespace gameStates
} // namespace zombie
