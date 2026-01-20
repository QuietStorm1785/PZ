#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/opengl/GL11.h"
#include "org/lwjglx/opengl/Display.h"
#include "org/lwjglx/opengl/DisplayMode.h"
#include "org/lwjglx/opengl/PixelFormat.h"
#include "zombie/GameWindow.h"
#include "zombie/IndieGL.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/WorldSoundManager.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Core.h"
#include "zombie/core/PerformanceSettings.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/VBO/GLVertexBufferObject.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/core/physics/WorldSimulation.h"
#include "zombie/core/properties/PropertyContainer.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/core/textures/TextureDraw/GenericDrawer.h"
#include "zombie/core/textures/TexturePackPage.h"
#include "zombie/debug/LineDrawer.h"
#include "zombie/gameStates/MainScreenState.h"
#include "zombie/input/GameKeyboard.h"
#include "zombie/input/Mouse.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoCamera/FrameState.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoCell/PerPlayerRender.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoObjectPicker.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/PlayerCamera.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/SpriteDetails/IsoObjectType.h"
#include "zombie/iso/areas/IsoRoom.h"
#include "zombie/iso/objects/IsoBarricade.h"
#include "zombie/iso/objects/IsoCurtain.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/iso/objects/IsoTree.h"
#include "zombie/iso/objects/IsoWindow.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/ui/TextManager.h"
#include "zombie/vehicles/BaseVehicle.h"

namespace zombie {
namespace network {


class ServerGUI {
public:
    static bool created;
    static int minX;
    static int minY;
    static int maxX;
    static int maxY;
    static int maxZ;
   private static const std::vector<IsoGridSquare> GridStack = std::make_unique<std::vector<>>();
   private static const std::vector<IsoGridSquare> MinusFloorCharacters = new std::vector<>(1000);
   private static const std::vector<IsoGridSquare> SolidFloor = new std::vector<>(5000);
   private static const std::vector<IsoGridSquare> VegetationCorpses = new std::vector<>(5000);
    static const ColorInfo defColorInfo = std::make_shared<ColorInfo>();

    static bool isCreated() {
    return created;
   }

    static void init() {
      created = true;

      try {
         Display.setFullscreen(false);
         Display.setResizable(false);
         Display.setVSyncEnabled(false);
         Display.setTitle("Project Zomboid Server");
         System.setProperty("org.lwjgl.opengl.Window.undecorated", "false");
         Core.width = 1366;
         Core.height = 768;
         Display.setDisplayMode(std::make_shared<DisplayMode>(Core.width, Core.height));
         Display.create(std::make_shared<PixelFormat>(32, 0, 24, 8, 0));
         Display.setIcon(MainScreenState.loadIcons());
         GLVertexBufferObject.init();
         Display.makeCurrent();
         SpriteRenderer.instance.create();
         TextManager.instance.Init();

         while (TextManager.instance.font.empty()) {
            GameWindow.fileSystem.updateAsyncTransactions();

            try {
               Thread.sleep(10L);
            } catch (InterruptedException var1) {
            }
         }

         TexturePackPage.bIgnoreWorldItemTextures = true;
    uint8_t var0 = 2;
         GameWindow.LoadTexturePack("UI", var0);
         GameWindow.LoadTexturePack("UI2", var0);
         GameWindow.LoadTexturePack("IconsMoveables", var0);
         GameWindow.LoadTexturePack("RadioIcons", var0);
         GameWindow.LoadTexturePack("ApComUI", var0);
         GameWindow.LoadTexturePack("WeatherFx", var0);
         TexturePackPage.bIgnoreWorldItemTextures = false;
         var0 = 0;
         GameWindow.LoadTexturePack("Tiles2x", var0);
         GameWindow.LoadTexturePack("JumboTrees2x", var0);
         GameWindow.LoadTexturePack("Overlays2x", var0);
         GameWindow.LoadTexturePack("Tiles2x.floor", 0);
         GameWindow.DoLoadingText("");
         GameWindow.setTexturePackLookup();
         IsoObjectPicker.Instance.Init();
         Display.makeCurrent();
         GL11.glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
         Display.releaseContext();
         RenderThread.initServerGUI();
         RenderThread.startRendering();
         Core.getInstance().initFBOs();
      } catch (Exception var2) {
         var2.printStackTrace();
         created = false;
      }
   }

    static void init2() {
      if (created) {
         BaseVehicle.LoadAllVehicleTextures();
      }
   }

    static void shutdown() {
      if (created) {
         RenderThread.shutdown();
      }
   }

    static void update() {
      if (created) {
         Mouse.update();
         GameKeyboard.update();
         Display.processMessages();
         if (RenderThread.isCloseRequested()) {
         }

    int var0 = Mouse.getWheelState();
         if (var0 != 0) {
    int var1 = var0 - 0 < 0 ? 1 : -1;
            Core.getInstance().doZoomScroll(0, var1);
         }

    uint8_t var2 = 0;
    IsoPlayer var3 = getPlayerToFollow();
         if (var3 == nullptr) {
            Core.getInstance().StartFrame();
            Core.getInstance().EndFrame();
            Core.getInstance().StartFrameUI();
            SpriteRenderer.instance
               .renderi(nullptr, 0, 0, Core.getInstance().getScreenWidth(), Core.getInstance().getScreenHeight(), 0.0F, 0.0F, 0.0F, 1.0F, nullptr);
            Core.getInstance().EndFrameUI();
         } else {
            IsoPlayer.setInstance(var3);
            IsoPlayer.players[var2] = var3;
            IsoCamera.CamCharacter = var3;
            Core.getInstance().StartFrame(var2, true);
            renderWorld();
            Core.getInstance().EndFrame(var2);
            Core.getInstance().RenderOffScreenBuffer();
            Core.getInstance().StartFrameUI();
            renderUI();
            Core.getInstance().EndFrameUI();
         }
      }
   }

    static IsoPlayer getPlayerToFollow() {
      for (int var0 = 0; var0 < GameServer.udpEngine.connections.size(); var0++) {
    UdpConnection var1 = (UdpConnection)GameServer.udpEngine.connections.get(var0);
         if (var1.isFullyConnected()) {
            for (int var2 = 0; var2 < 4; var2++) {
    IsoPlayer var3 = var1.players[var2];
               if (var3 != nullptr && var3.OnlineID != -1) {
    return var3;
               }
            }
         }
      }

    return nullptr;
   }

    static void updateCamera(IsoPlayer var0) {
    uint8_t var2 = 0;
    PlayerCamera var3 = IsoCamera.cameras[var2];
    float var4 = IsoUtils.XToScreen(var0.x + var3.DeferedX, var0.y + var3.DeferedY, var0.z, 0);
    float var5 = IsoUtils.YToScreen(var0.x + var3.DeferedX, var0.y + var3.DeferedY, var0.z, 0);
      var4 -= IsoCamera.getOffscreenWidth(var2) / 2;
      var5 -= IsoCamera.getOffscreenHeight(var2) / 2;
      var5 -= var0.getOffsetY() * 1.5F;
      var4 += IsoCamera.PLAYER_OFFSET_X;
      var5 += IsoCamera.PLAYER_OFFSET_Y;
      var3.OffX = var4;
      var3.OffY = var5;
    FrameState var6 = IsoCamera.frameState;
      var6.Paused = false;
      var6.playerIndex = var2;
      var6.CamCharacter = var0;
      var6.CamCharacterX = IsoCamera.CamCharacter.getX();
      var6.CamCharacterY = IsoCamera.CamCharacter.getY();
      var6.CamCharacterZ = IsoCamera.CamCharacter.getZ();
      var6.CamCharacterSquare = IsoCamera.CamCharacter.getCurrentSquare();
      var6.CamCharacterRoom = var6.CamCharacterSquare == nullptr ? nullptr : var6.CamCharacterSquare.getRoom();
      var6.OffX = IsoCamera.getOffX();
      var6.OffY = IsoCamera.getOffY();
      var6.OffscreenWidth = IsoCamera.getOffscreenWidth(var2);
      var6.OffscreenHeight = IsoCamera.getOffscreenHeight(var2);
   }

    static void renderWorld() {
    IsoPlayer var0 = getPlayerToFollow();
      if (var0 != nullptr) {
    uint8_t var1 = 0;
         IsoPlayer.setInstance(var0);
         IsoPlayer.players[0] = var0;
         IsoCamera.CamCharacter = var0;
         updateCamera(var0);
         SpriteRenderer.instance.doCoreIntParam(0, IsoCamera.CamCharacter.x);
         SpriteRenderer.instance.doCoreIntParam(1, IsoCamera.CamCharacter.y);
         SpriteRenderer.instance.doCoreIntParam(2, IsoCamera.CamCharacter.z);
         IsoWorld.instance.sceneCullZombies();
         IsoSprite.globalOffsetX = -1.0F;
    uint8_t var2 = 0;
    uint8_t var3 = 0;
    int var4 = var2 + IsoCamera.getOffscreenWidth(var1);
    int var5 = var3 + IsoCamera.getOffscreenHeight(var1);
    float var6 = IsoUtils.XToIso(var2, var3, 0.0F);
    float var7 = IsoUtils.YToIso(var4, var3, 0.0F);
    float var8 = IsoUtils.XToIso(var4, var5, 6.0F);
    float var9 = IsoUtils.YToIso(var2, var5, 6.0F);
         minY = (int)var7;
         maxY = (int)var9;
         minX = (int)var6;
         maxX = (int)var8;
         minX -= 2;
         minY -= 2;
         maxZ = (int)var0.getZ();
    IsoCell var10 = IsoWorld.instance.CurrentCell;
         var10.DrawStencilMask();
         IsoObjectPicker.Instance.StartRender();
         RenderTiles();

         for (int var11 = 0; var11 < var10.getObjectList().size(); var11++) {
    IsoMovingObject var12 = (IsoMovingObject)var10.getObjectList().get(var11);
            var12.renderlast();
         }

         for (int var13 = 0; var13 < var10.getStaticUpdaterObjectList().size(); var13++) {
    IsoObject var15 = (IsoObject)var10.getStaticUpdaterObjectList().get(var13);
            var15.renderlast();
         }

         if (WorldSimulation.instance.created) {
    GenericDrawer var14 = WorldSimulation.getDrawer(var1);
            SpriteRenderer.instance.drawGeneric(var14);
         }

         WorldSoundManager.instance.render();
         LineDrawer.clear();
      }
   }

    static void RenderTiles() {
    IsoCell var0 = IsoWorld.instance.CurrentCell;
      if (IsoCell.perPlayerRender[0] == nullptr) {
         IsoCell.perPlayerRender[0] = std::make_unique<PerPlayerRender>();
      }

    PerPlayerRender var1 = IsoCell.perPlayerRender[0];
      if (var1 == nullptr) {
         IsoCell.perPlayerRender[0] = std::make_unique<PerPlayerRender>();
      }

      var1.setSize(maxX - minX + 1, maxY - minY + 1);
      short[][][] var2 = var1.StencilValues;

      for (int var3 = 0; var3 <= maxZ; var3++) {
         GridStack.clear();

         for (int var4 = minY; var4 < maxY; var4++) {
    int var5 = minX;
    IsoGridSquare var6 = ServerMap.instance.getGridSquare(var5, var4, var3);
    int var7 = IsoDirections.E.index();

            while (var5 < maxX) {
               if (var3 == 0) {
                  var2[var5 - minX][var4 - minY][0] = 0;
                  var2[var5 - minX][var4 - minY][1] = 0;
               }

               if (var6 != nullptr && var6.getY() != var4) {
                  var6 = nullptr;
               }

               if (var6 == nullptr) {
                  var6 = ServerMap.instance.getGridSquare(var5, var4, var3);
                  if (var6 == nullptr) {
                     var5++;
                     continue;
                  }
               }

    IsoChunk var8 = var6.getChunk();
               if (var8 != nullptr && var6.IsOnScreen()) {
                  GridStack.push_back(var6);
               }

               var6 = var6.nav[var7];
               var5++;
            }
         }

         SolidFloor.clear();
         VegetationCorpses.clear();
         MinusFloorCharacters.clear();

         for (int var11 = 0; var11 < GridStack.size(); var11++) {
    IsoGridSquare var14 = GridStack.get(var11);
            var14.setLightInfoServerGUIOnly(defColorInfo);
    int var17 = renderFloor(var14);
            if (!var14.getStaticMovingObjects().empty()) {
               var17 |= 2;
            }

            for (int var19 = 0; var19 < var14.getMovingObjects().size(); var19++) {
    IsoMovingObject var20 = (IsoMovingObject)var14.getMovingObjects().get(var19);
    bool var9 = var20.isOnFloor();
               if (var9 && dynamic_cast<IsoZombie*>(var20) != nullptr var10) {
                  var9 = var10.bCrawling
                     || var10.legsSprite.CurrentAnim != nullptr && var10.legsSprite.CurrentAnim.name == "ZombieDeath") && var10.def.isFinished();
               }

               if (var9) {
                  var17 |= 2;
               } else {
                  var17 |= 4;
               }
            }

            if ((var17 & 1) != 0) {
               SolidFloor.push_back(var14);
            }

            if ((var17 & 2) != 0) {
               VegetationCorpses.push_back(var14);
            }

            if ((var17 & 4) != 0) {
               MinusFloorCharacters.push_back(var14);
            }
         }

         LuaEventManager.triggerEvent("OnPostFloorLayerDraw", var3);

         for (int var12 = 0; var12 < VegetationCorpses.size(); var12++) {
    IsoGridSquare var15 = VegetationCorpses.get(var12);
            renderMinusFloor(var15, false, true);
            renderCharacters(var15, true);
         }

         for (int var13 = 0; var13 < MinusFloorCharacters.size(); var13++) {
    IsoGridSquare var16 = MinusFloorCharacters.get(var13);
    bool var18 = renderMinusFloor(var16, false, false);
            renderCharacters(var16, false);
            if (var18) {
               renderMinusFloor(var16, true, false);
            }
         }
      }

      MinusFloorCharacters.clear();
      SolidFloor.clear();
      VegetationCorpses.clear();
   }

    static int renderFloor(IsoGridSquare var0) {
    uint8_t var1 = 0;
    uint8_t var2 = 0;

      for (int var3 = 0; var3 < var0.getObjects().size(); var3++) {
    IsoObject var4 = (IsoObject)var0.getObjects().get(var3);
    bool var5 = true;
         if (var4.sprite != nullptr && !var4.sprite.Properties.Is(IsoFlagType.solidfloor)) {
            var5 = false;
            var1 |= 4;
         }

         if (var5) {
            IndieGL.glAlphaFunc(516, 0.0F);
            var4.setAlphaAndTarget(var2, 1.0F);
            var4.render(var0.x, var0.y, var0.z, defColorInfo, true, false, nullptr);
            var4.renderObjectPicker(var0.x, var0.y, var0.z, defColorInfo);
            if ((var4.highlightFlags & 2) != 0) {
               var4.highlightFlags &= -2;
            }

            var1 |= 1;
         }

         if (!var5 && var4.sprite != nullptr && (var4.sprite.Properties.Is(IsoFlagType.canBeRemoved) || var4.sprite.Properties.Is(IsoFlagType.attachedFloor))) {
            var1 |= 2;
         }
      }

    return var1;
   }

    static bool isSpriteOnSouthOrEastWall(IsoObject var0) {
      if (dynamic_cast<IsoBarricade*>(var0) != nullptr) {
         return var0.getDir() == IsoDirections.S || var0.getDir() == IsoDirections.E;
      } else if (dynamic_cast<IsoCurtain*>(var0) != nullptr var2) {
         return var2.getType() == IsoObjectType.curtainS || var2.getType() == IsoObjectType.curtainE;
      } else {
    PropertyContainer var1 = var0.getProperties();
         return var1 != nullptr && (var1.Is(IsoFlagType.attachedE) || var1.Is(IsoFlagType.attachedS));
      }
   }

    static int DoWallLightingN(IsoGridSquare var0, IsoObject var1, int var2) {
      var1.render(var0.x, var0.y, var0.z, defColorInfo, true, false, nullptr);
    return var2;
   }

    static int DoWallLightingW(IsoGridSquare var0, IsoObject var1, int var2) {
      var1.render(var0.x, var0.y, var0.z, defColorInfo, true, false, nullptr);
    return var2;
   }

    static int DoWallLightingNW(IsoGridSquare var0, IsoObject var1, int var2) {
      var1.render(var0.x, var0.y, var0.z, defColorInfo, true, false, nullptr);
    return var2;
   }

    static bool renderMinusFloor(IsoGridSquare var0, bool var1, bool var2) {
    int var3 = var1 ? var0.getObjects().size() - 1 : 0;
    int var4 = var1 ? 0 : var0.getObjects().size() - 1;
    int var5 = IsoCamera.frameState.playerIndex;
    IsoGridSquare var6 = IsoCamera.frameState.CamCharacterSquare;
    IsoRoom var7 = IsoCamera.frameState.CamCharacterRoom;
    int var8 = (int)(IsoUtils.XToScreenInt(var0.x, var0.y, var0.z, 0) - IsoCamera.frameState.OffX);
    int var9 = (int)(IsoUtils.YToScreenInt(var0.x, var0.y, var0.z, 0) - IsoCamera.frameState.OffY);
    bool var10 = true;
    IsoCell var11 = var0.getCell();
      if (var8 + 32 * Core.TileScale <= var11.StencilX1
         || var8 - 32 * Core.TileScale >= var11.StencilX2
         || var9 + 32 * Core.TileScale <= var11.StencilY1
         || var9 - 96 * Core.TileScale >= var11.StencilY2) {
         var10 = false;
      }

    int var12 = 0;
    bool var13 = false;

      for (int var14 = var3; var1 ? var14 >= var4 : var14 <= var4; var14 += var1 ? -1 : 1) {
    IsoObject var15 = (IsoObject)var0.getObjects().get(var14);
    bool var16 = true;
         IsoGridSquare.CircleStencil = false;
         if (var15.sprite != nullptr && var15.sprite.getProperties().Is(IsoFlagType.solidfloor)) {
            var16 = false;
         }

         if ((!var2 || var15.sprite == nullptr || var15.sprite.Properties.Is(IsoFlagType.canBeRemoved) || var15.sprite.Properties.Is(IsoFlagType.attachedFloor))
            && (var2 || var15.sprite == nullptr || !var15.sprite.Properties.Is(IsoFlagType.canBeRemoved) && !var15.sprite.Properties.Is(IsoFlagType.attachedFloor))
            )
          {
            if (var15.sprite != nullptr
               && (
                  var15.sprite.getType() == IsoObjectType.WestRoofB
                     || var15.sprite.getType() == IsoObjectType.WestRoofM
                     || var15.sprite.getType() == IsoObjectType.WestRoofT
               )
               && var0.z == maxZ
               && var0.z == (int)IsoCamera.CamCharacter.getZ()) {
               var16 = false;
            }

            if (IsoCamera.CamCharacter.isClimbing() && var15.sprite != nullptr && !var15.sprite.getProperties().Is(IsoFlagType.solidfloor)) {
               var16 = true;
            }

            if (isSpriteOnSouthOrEastWall(var15)) {
               if (!var1) {
                  var16 = false;
               }

               var13 = true;
            } else if (var1) {
               var16 = false;
            }

            if (var16) {
               IndieGL.glAlphaFunc(516, 0.0F);
               if (var15.sprite != nullptr
                  && !var0.getProperties().Is(IsoFlagType.blueprint)
                  && (
                     var15.sprite.getType() == IsoObjectType.doorFrW
                        || var15.sprite.getType() == IsoObjectType.doorFrN
                        || var15.sprite.getType() == IsoObjectType.doorW
                        || var15.sprite.getType() == IsoObjectType.doorN
                        || var15.sprite.getProperties().Is(IsoFlagType.cutW)
                        || var15.sprite.getProperties().Is(IsoFlagType.cutN)
                  )
                  && PerformanceSettings.LightingFrameSkip < 3) {
                  if (var15.getTargetAlpha(var5) < 1.0F) {
    bool var20 = false;
                     if (var20) {
                        if (var15.sprite.getProperties().Is(IsoFlagType.cutW) && var0.getProperties().Is(IsoFlagType.WallSE)) {
    IsoGridSquare var24 = var0.nav[IsoDirections.NW.index()];
                           if (var24 == nullptr || var24.getRoom() == nullptr) {
                              var20 = false;
                           }
                        } else if (var15.sprite.getType() != IsoObjectType.doorFrW
                           && var15.sprite.getType() != IsoObjectType.doorW
                           && !var15.sprite.getProperties().Is(IsoFlagType.cutW)) {
                           if (var15.sprite.getType() == IsoObjectType.doorFrN
                              || var15.sprite.getType() == IsoObjectType.doorN
                              || var15.sprite.getProperties().Is(IsoFlagType.cutN)) {
    IsoGridSquare var23 = var0.nav[IsoDirections.N.index()];
                              if (var23 == nullptr || var23.getRoom() == nullptr) {
                                 var20 = false;
                              }
                           }
                        } else {
    IsoGridSquare var22 = var0.nav[IsoDirections.W.index()];
                           if (var22 == nullptr || var22.getRoom() == nullptr) {
                              var20 = false;
                           }
                        }
                     }

                     if (!var20) {
                        IsoGridSquare.CircleStencil = var10;
                     }

                     var15.setAlphaAndTarget(var5, 1.0F);
                  }

                  if (var15.sprite.getProperties().Is(IsoFlagType.cutW) && var15.sprite.getProperties().Is(IsoFlagType.cutN)) {
                     var12 = DoWallLightingNW(var0, var15, var12);
                  } else if (var15.sprite.getType() == IsoObjectType.doorFrW
                     || var15.sprite.getType() == IsoObjectType.doorW
                     || var15.sprite.getProperties().Is(IsoFlagType.cutW)) {
                     var12 = DoWallLightingW(var0, var15, var12);
                  } else if (var15.sprite.getType() == IsoObjectType.doorFrN
                     || var15.sprite.getType() == IsoObjectType.doorN
                     || var15.sprite.getProperties().Is(IsoFlagType.cutN)) {
                     var12 = DoWallLightingN(var0, var15, var12);
                  }
               } else {
                  if (var6 != nullptr) {
                  }

                  var15.setTargetAlpha(var5, 1.0F);
                  if (IsoCamera.CamCharacter != nullptr
                     && var15.getProperties() != nullptr
                     && (var15.getProperties().Is(IsoFlagType.solid) || var15.getProperties().Is(IsoFlagType.solidtrans))) {
    int var17 = var0.getX() - (int)IsoCamera.CamCharacter.getX();
    int var18 = var0.getY() - (int)IsoCamera.CamCharacter.getY();
                     if (var17 > 0 && var17 < 3 && var18 >= 0 && var18 < 3 || var18 > 0 && var18 < 3 && var17 >= 0 && var17 < 3) {
                        var15.setTargetAlpha(var5, 0.99F);
                     }
                  }

                  if (dynamic_cast<IsoWindow*>(var15) != nullptr && var15.getTargetAlpha(var5) < 1.0E-4F) {
    IsoWindow var19 = (IsoWindow)var15;
    IsoGridSquare var21 = var19.getOppositeSquare();
                     if (var21 != nullptr && var21 != var0 && var21.lighting[var5].bSeen()) {
                        var15.setTargetAlpha(var5, var21.lighting[var5].darkMulti() * 2.0F);
                     }
                  }

                  if (dynamic_cast<IsoTree*>(var15) != nullptr) {
                     if (var10
                        && var0.x >= (int)IsoCamera.frameState.CamCharacterX
                        && var0.y >= (int)IsoCamera.frameState.CamCharacterY
                        && var6 != nullptr
                        && var6.Is(IsoFlagType.exterior)) {
                        ((IsoTree)var15).bRenderFlag = true;
                     } else {
                        ((IsoTree)var15).bRenderFlag = false;
                     }
                  }

                  var15.render(var0.x, var0.y, var0.z, defColorInfo, true, false, nullptr);
               }

               if (var15.sprite != nullptr) {
                  var15.renderObjectPicker(var0.x, var0.y, var0.z, defColorInfo);
               }

               if ((var15.highlightFlags & 2) != 0) {
                  var15.highlightFlags &= -2;
               }
            }
         }
      }

    return var13;
   }

    static void renderCharacters(IsoGridSquare var0, bool var1) {
    int var2 = var0.getStaticMovingObjects().size();

      for (int var3 = 0; var3 < var2; var3++) {
    IsoMovingObject var4 = (IsoMovingObject)var0.getStaticMovingObjects().get(var3);
         if (var4.sprite != nullptr && (!var1 || dynamic_cast<IsoDeadBody*>(var4) != nullptr) && (var1 || !(dynamic_cast<IsoDeadBody*>(var4) != nullptr))) {
            var4.render(var4.getX(), var4.getY(), var4.getZ(), defColorInfo, true, false, nullptr);
            var4.renderObjectPicker(var4.getX(), var4.getY(), var4.getZ(), defColorInfo);
         }
      }

      var2 = var0.getMovingObjects().size();

      for (int var8 = 0; var8 < var2; var8++) {
    IsoMovingObject var9 = (IsoMovingObject)var0.getMovingObjects().get(var8);
         if (var9 != nullptr && var9.sprite != nullptr) {
    bool var5 = var9.isOnFloor();
            if (var5 && dynamic_cast<IsoZombie*>(var9) != nullptr var6) {
               var5 = var6.bCrawling || var6.legsSprite.CurrentAnim != nullptr && var6.legsSprite.CurrentAnim.name == "ZombieDeath") && var6.def.isFinished();
            }

            if ((!var1 || var5) && (var1 || !var5)) {
               var9.setAlphaAndTarget(0, 1.0F);
               if (dynamic_cast<IsoGameCharacter*>(var9) != nullptr var10) {
                  var10.renderServerGUI();
               } else {
                  var9.render(var9.getX(), var9.getY(), var9.getZ(), defColorInfo, true, false, nullptr);
               }

               var9.renderObjectPicker(var9.getX(), var9.getY(), var9.getZ(), defColorInfo);
            }
         }
      }
   }

    static void renderUI() {
   }
}
} // namespace network
} // namespace zombie
