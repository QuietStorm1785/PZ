#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Vector2i.h"
#include "org/joml/Vector3f.h"
#include "zombie/IndieGL.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/characters/IsoGameCharacter/TorchInfo.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Color.h"
#include "zombie/core/Core.h"
#include "zombie/core/PerformanceSettings.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/opengl/RenderSettings.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/core/textures/TextureFBO.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/input/GameKeyboard.h"
#include "zombie/iso/DiamondMatrixIterator.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoChunkMap.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/SpriteDetails/IsoObjectType.h"
#include "zombie/iso/areas/isoregion/IsoRegions.h"
#include "zombie/iso/areas/isoregion/regions/IWorldRegion.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/iso/weather/fx/WeatherFxMask/PlayerFxMask.h"
#include "zombie/network/GameServer.h"

namespace zombie {
namespace iso {
namespace weather {
namespace fx {


class WeatherFxMask {
public:
    static bool DEBUG_KEYS = false;
    static TextureFBO fboMask;
    static TextureFBO fboParticles;
    static IsoSprite floorSprite;
    static IsoSprite wallNSprite;
    static IsoSprite wallWSprite;
    static IsoSprite wallNWSprite;
    static IsoSprite wallSESprite;
    static Texture texWhite;
    static int curPlayerIndex;
    static const int BIT_FLOOR = 0;
    static const int BIT_WALLN = 1;
    static const int BIT_WALLW = 2;
    static const int BIT_IS_CUT = 4;
    static const int BIT_CHARS = 8;
    static const int BIT_OBJECTS = 16;
    static const int BIT_WALL_SE = 32;
    static const int BIT_DOOR = 64;
    static float offsetX = 32 * Core.TileScale;
    static float offsetY = 96 * Core.TileScale;
    static ColorInfo defColorInfo = std::make_shared<ColorInfo>();
    static int DIAMOND_ROWS = 1000;
    int x;
    int y;
    int z;
    int flags;
    IsoGridSquare gs;
    bool enabled;
   private static PlayerFxMask[] playerMasks = new PlayerFxMask[4];
    static DiamondMatrixIterator dmiter = std::make_shared<DiamondMatrixIterator>(0);
    static const Vector2i diamondMatrixPos = std::make_shared<Vector2i>();
    static Vector3f tmpVec = std::make_shared<Vector3f>();
    static TorchInfo tmpTorch = std::make_shared<TorchInfo>();
    static ColorInfo tmpColInfo = std::make_shared<ColorInfo>();
   private static int[] test = new int[]{0, 1, 768, 769, 774, 775, 770, 771, 772, 773, 32769, 32770, 32771, 32772, 776, 35065, 35066, 34185, 35067};
   private static std::string[] testNames = new std::string[]{
      "GL_ZERO",
      "GL_ONE",
      "GL_SRC_COLOR",
      "GL_ONE_MINUS_SRC_COLOR",
      "GL_DST_COLOR",
      "GL_ONE_MINUS_DST_COLOR",
      "GL_SRC_ALPHA",
      "GL_ONE_MINUS_SRC_ALPHA",
      "GL_DST_ALPHA",
      "GL_ONE_MINUS_DST_ALPHA",
      "GL_CONSTANT_COLOR",
      "GL_ONE_MINUS_CONSTANT_COLOR",
      "GL_CONSTANT_ALPHA",
      "GL_ONE_MINUS_CONSTANT_ALPHA",
      "GL_SRC_ALPHA_SATURATE",
      "GL_SRC1_COLOR (33)",
      "GL_ONE_MINUS_SRC1_COLOR (33)",
      "GL_SRC1_ALPHA (15)",
      "GL_ONE_MINUS_SRC1_ALPHA (33)"
   };
    static int var1 = 1;
    static int var2 = 1;
    static float var3 = 1.0F;
    static int SCR_MASK_ADD = 770;
    static int DST_MASK_ADD = 771;
    static int SCR_MASK_SUB = 0;
    static int DST_MASK_SUB = 0;
    static int SCR_PARTICLES = 1;
    static int DST_PARTICLES = 771;
    static int SCR_MERGE = 770;
    static int DST_MERGE = 771;
    static int SCR_FINAL = 770;
    static int DST_FINAL = 771;
    static int ID_SCR_MASK_ADD;
    static int ID_DST_MASK_ADD;
    static int ID_SCR_MASK_SUB;
    static int ID_DST_MASK_SUB;
    static int ID_SCR_MERGE;
    static int ID_DST_MERGE;
    static int ID_SCR_FINAL;
    static int ID_DST_FINAL;
    static int ID_SCR_PARTICLES;
    static int ID_DST_PARTICLES;
    static int TARGET_BLEND = 0;
    static bool DEBUG_MASK = false;
    static bool MASKING_ENABLED = true;
    static bool DEBUG_MASK_AND_PARTICLES = false;
    static const bool DEBUG_THROTTLE_KEYS = true;
    static int keypause = 0;

    static TextureFBO getFboMask() {
    return fboMask;
   }

    static TextureFBO getFboParticles() {
    return fboParticles;
   }

    static void init() {
      if (!GameServer.bServer) {
         for (int var0 = 0; var0 < playerMasks.length; var0++) {
            playerMasks[var0] = std::make_unique<PlayerFxMask>();
         }

         playerMasks[0].init();
         initGlIds();
         floorSprite = IsoSpriteManager.instance.getSprite("floors_interior_tilesandwood_01_16");
         wallNSprite = IsoSpriteManager.instance.getSprite("walls_interior_house_01_21");
         wallWSprite = IsoSpriteManager.instance.getSprite("walls_interior_house_01_20");
         wallNWSprite = IsoSpriteManager.instance.getSprite("walls_interior_house_01_22");
         wallSESprite = IsoSpriteManager.instance.getSprite("walls_interior_house_01_23");
         texWhite = Texture.getSharedTexture("media/textures/weather/fogwhite.png");
      }
   }

    static bool checkFbos() {
      if (GameServer.bServer) {
    return false;
      } else {
    TextureFBO var0 = Core.getInstance().getOffscreenBuffer();
         if (Core.getInstance().getOffscreenBuffer() == nullptr) {
            DebugLog.log("fbo=" + (var0 != nullptr));
    return false;
         } else {
    int var1x = Core.getInstance().getScreenWidth();
    int var2x = Core.getInstance().getScreenHeight();
            if (fboMask != nullptr && fboParticles != nullptr && fboMask.getTexture().getWidth() == var1x && fboMask.getTexture().getHeight() == var2x) {
               return fboMask != nullptr && fboParticles != nullptr;
            } else {
               if (fboMask != nullptr) {
                  fboMask.destroy();
               }

               if (fboParticles != nullptr) {
                  fboParticles.destroy();
               }

               fboMask = nullptr;
               fboParticles = nullptr;

               try {
    Texture var3x = std::make_shared<Texture>(var1x, var2x, 16);
                  fboMask = std::make_shared<TextureFBO>(var3x);
               } catch (Exception var5) {
                  DebugLog.log(var5.getStackTrace());
                  var5.printStackTrace();
               }

               try {
    Texture var6 = std::make_shared<Texture>(var1x, var2x, 16);
                  fboParticles = std::make_shared<TextureFBO>(var6);
               } catch (Exception var4) {
                  DebugLog.log(var4.getStackTrace());
                  var4.printStackTrace();
               }

               return fboMask != nullptr && fboParticles != nullptr;
            }
         }
      }
   }

    static void destroy() {
      if (fboMask != nullptr) {
         fboMask.destroy();
      }

      fboMask = nullptr;
      if (fboParticles != nullptr) {
         fboParticles.destroy();
      }

      fboParticles = nullptr;
   }

    static void initMask() {
      if (!GameServer.bServer) {
         curPlayerIndex = IsoCamera.frameState.playerIndex;
         playerMasks[curPlayerIndex].initMask();
      }
   }

    static bool isOnScreen(int var0, int var1x, int var2x) {
    float var3x = (int)IsoUtils.XToScreenInt(var0, var1x, var2x, 0);
    float var4 = (int)IsoUtils.YToScreenInt(var0, var1x, var2x, 0);
      var3x -= (int)IsoCamera.frameState.OffX;
      var4 -= (int)IsoCamera.frameState.OffY;
      if (var3x + 32 * Core.TileScale <= 0.0F) {
    return false;
      } else if (var4 + 32 * Core.TileScale <= 0.0F) {
    return false;
      } else {
         return var3x - 32 * Core.TileScale >= IsoCamera.frameState.OffscreenWidth
            ? false
            : !(var4 - 96 * Core.TileScale >= IsoCamera.frameState.OffscreenHeight);
      }
   }

    bool isLoc(int var1x, int var2x, int var3x) {
      return this.x == var1x && this.y == var2x && this.z == var3x;
   }

    static bool playerHasMaskToDraw(int var0) {
      return var0 < playerMasks.length ? playerMasks[var0].hasMaskToDraw : false;
   }

    static void setDiamondIterDone(int var0) {
      if (var0 < playerMasks.length) {
         playerMasks[var0].DIAMOND_ITER_DONE = true;
      }
   }

    static void forceMaskUpdate(int var0) {
      if (var0 < playerMasks.length) {
         playerMasks[var0].plrSquare = nullptr;
      }
   }

    static void forceMaskUpdateAll() {
      if (!GameServer.bServer) {
         for (int var0 = 0; var0 < playerMasks.length; var0++) {
            playerMasks[var0].plrSquare = nullptr;
         }
      }
   }

    static bool getIsStairs(IsoGridSquare var0) {
      return var0 != nullptr
         && (
            var0.Has(IsoObjectType.stairsBN)
               || var0.Has(IsoObjectType.stairsBW)
               || var0.Has(IsoObjectType.stairsMN)
               || var0.Has(IsoObjectType.stairsMW)
               || var0.Has(IsoObjectType.stairsTN)
               || var0.Has(IsoObjectType.stairsTW)
         );
   }

    static bool getHasDoor(IsoGridSquare var0) {
      return var0 != nullptr
            && (var0.Is(IsoFlagType.cutN) || var0.Is(IsoFlagType.cutW))
            && (var0.Is(IsoFlagType.DoorWallN) || var0.Is(IsoFlagType.DoorWallW))
            && !var0.Is(IsoFlagType.doorN)
            && !var0.Is(IsoFlagType.doorW)
         ? var0.getCanSee(curPlayerIndex)
         : false;
   }

    static void addMaskLocation(IsoGridSquare var0, int var1x, int var2x, int var3x) {
      if (!GameServer.bServer) {
    PlayerFxMask var4 = playerMasks[curPlayerIndex];
         if (var4.requiresUpdate) {
            if (var4.hasMaskToDraw && var4.playerZ == var3x) {
               if (isInPlayerBuilding(var0, var1x, var2x, var3x)) {
    IsoGridSquare var5 = IsoWorld.instance.getCell().getChunkMap(curPlayerIndex).getGridSquare(var1x, var2x - 1, var3x);
    bool var6 = !isInPlayerBuilding(var5, var1x, var2x - 1, var3x);
                  var5 = IsoWorld.instance.getCell().getChunkMap(curPlayerIndex).getGridSquare(var1x - 1, var2x, var3x);
    bool var7 = !isInPlayerBuilding(var5, var1x - 1, var2x, var3x);
                  var5 = IsoWorld.instance.getCell().getChunkMap(curPlayerIndex).getGridSquare(var1x - 1, var2x - 1, var3x);
    bool var8 = !isInPlayerBuilding(var5, var1x - 1, var2x - 1, var3x);
    uint8_t var9 = 0;
                  if (var6) {
                     var9 |= 1;
                  }

                  if (var7) {
                     var9 |= 2;
                  }

                  if (var8) {
                     var9 |= 32;
                  }

    bool var10 = false;
    bool var11 = getIsStairs(var0);
                  if (var0 != nullptr && (var6 || var7 || var8)) {
    uint8_t var12 = 24;
                     if (var6 && !var0.getProperties().Is(IsoFlagType.WallN) && !var0.Is(IsoFlagType.WallNW)) {
                        var4.addMask(var1x - 1, var2x, var3x, nullptr, 8, false);
                        var4.addMask(var1x, var2x, var3x, var0, var12);
                        var4.addMask(var1x + 1, var2x, var3x, nullptr, var12, false);
                        var4.addMask(var1x + 2, var2x, var3x, nullptr, 8, false);
                        var4.addMask(var1x, var2x + 1, var3x, nullptr, 8, false);
                        var4.addMask(var1x + 1, var2x + 1, var3x, nullptr, var12, false);
                        var4.addMask(var1x + 2, var2x + 1, var3x, nullptr, var12, false);
                        var4.addMask(var1x + 2, var2x + 2, var3x, nullptr, 16, false);
                        var4.addMask(var1x + 3, var2x + 2, var3x, nullptr, 16, false);
                        var10 = true;
                     }

                     if (var7 && !var0.getProperties().Is(IsoFlagType.WallW) && !var0.getProperties().Is(IsoFlagType.WallNW)) {
                        var4.addMask(var1x, var2x - 1, var3x, nullptr, 8, false);
                        var4.addMask(var1x, var2x, var3x, var0, var12);
                        var4.addMask(var1x, var2x + 1, var3x, nullptr, var12, false);
                        var4.addMask(var1x, var2x + 2, var3x, nullptr, 8, false);
                        var4.addMask(var1x + 1, var2x, var3x, nullptr, 8, false);
                        var4.addMask(var1x + 1, var2x + 1, var3x, nullptr, var12, false);
                        var4.addMask(var1x + 1, var2x + 2, var3x, nullptr, var12, false);
                        var4.addMask(var1x + 2, var2x + 2, var3x, nullptr, 16, false);
                        var4.addMask(var1x + 2, var2x + 3, var3x, nullptr, 16, false);
                        var10 = true;
                     }

                     if (var8) {
    uint8_t var13 = var11 ? var12 : var9;
                        var4.addMask(var1x, var2x, var3x, var0, var13);
                        var10 = true;
                     }
                  }

                  if (!var10) {
    uint8_t var22 = var11 ? 24 : var9;
                     var4.addMask(var1x, var2x, var3x, var0, var22);
                  }
               } else {
    IsoGridSquare var16 = IsoWorld.instance.getCell().getChunkMap(curPlayerIndex).getGridSquare(var1x, var2x - 1, var3x);
    bool var19 = isInPlayerBuilding(var16, var1x, var2x - 1, var3x);
                  var16 = IsoWorld.instance.getCell().getChunkMap(curPlayerIndex).getGridSquare(var1x - 1, var2x, var3x);
    bool var20 = isInPlayerBuilding(var16, var1x - 1, var2x, var3x);
                  if (!var19 && !var20) {
                     var16 = IsoWorld.instance.getCell().getChunkMap(curPlayerIndex).getGridSquare(var1x - 1, var2x - 1, var3x);
                     if (isInPlayerBuilding(var16, var1x - 1, var2x - 1, var3x)) {
                        var4.addMask(var1x, var2x, var3x, var0, 4);
                     }
                  } else {
    uint8_t var21 = 4;
                     if (var19) {
                        var21 |= 1;
                     }

                     if (var20) {
                        var21 |= 2;
                     }

                     if (getHasDoor(var0)) {
                        var21 |= 64;
                     }

                     var4.addMask(var1x, var2x, var3x, var0, var21);
                  }
               }
            }
         }
      }
   }

    static bool isInPlayerBuilding(IsoGridSquare var0, int var1x, int var2x, int var3x) {
    PlayerFxMask var4 = playerMasks[curPlayerIndex];
      if (var0 != nullptr && var0.Is(IsoFlagType.solidfloor)) {
         if (var0.getBuilding() != nullptr && var0.getBuilding() == var4.player.getBuilding()) {
    return true;
         }

         if (var0.getBuilding() == nullptr) {
            return var4.curIsoWorldRegion != nullptr
               && var0.getIsoWorldRegion() != nullptr
               && var0.getIsoWorldRegion().isFogMask()
               && (var0.getIsoWorldRegion() == var4.curIsoWorldRegion || var4.curConnectedRegions.contains(var0.getIsoWorldRegion()));
         }
      } else {
         if (isInteriorLocation(var1x, var2x, var3x)) {
    return true;
         }

         if (var0 != nullptr && var0.getBuilding() == nullptr) {
            return var4.curIsoWorldRegion != nullptr
               && var0.getIsoWorldRegion() != nullptr
               && var0.getIsoWorldRegion().isFogMask()
               && (var0.getIsoWorldRegion() == var4.curIsoWorldRegion || var4.curConnectedRegions.contains(var0.getIsoWorldRegion()));
         }

         if (var0 == nullptr && var4.curIsoWorldRegion != nullptr) {
    IWorldRegion var5 = IsoRegions.getIsoWorldRegion(var1x, var2x, var3x);
            return var5 != nullptr && var5.isFogMask() && (var5 == var4.curIsoWorldRegion || var4.curConnectedRegions.contains(var5));
         }
      }

    return false;
   }

    static bool isInteriorLocation(int var0, int var1x, int var2x) {
    PlayerFxMask var3x = playerMasks[curPlayerIndex];

      for (int var5 = var2x; var5 >= 0; var5--) {
    IsoGridSquare var4 = IsoWorld.instance.getCell().getChunkMap(curPlayerIndex).getGridSquare(var0, var1x, var5);
         if (var4 != nullptr) {
            if (var4.getBuilding() != nullptr && var4.getBuilding() == var3x.player.getBuilding()) {
    return true;
            }

            if (var4.Is(IsoFlagType.exterior)) {
    return false;
            }
         }
      }

    return false;
   }

    static void scanForTiles(int var0) {
    PlayerFxMask var1x = playerMasks[curPlayerIndex];
      if (!var1x.DIAMOND_ITER_DONE) {
    IsoPlayer var2x = IsoPlayer.players[var0];
    int var3x = (int)var2x.getZ();
    uint8_t var4 = 0;
    uint8_t var5 = 0;
    int var6 = var4 + IsoCamera.getOffscreenWidth(var0);
    int var7 = var5 + IsoCamera.getOffscreenHeight(var0);
    float var8 = IsoUtils.XToIso(var4, var5, 0.0F);
    float var9 = IsoUtils.YToIso(var6, var5, 0.0F);
    float var10 = IsoUtils.XToIso(var6, var7, 6.0F);
    float var11 = IsoUtils.YToIso(var4, var7, 6.0F);
    float var12 = IsoUtils.XToIso(var6, var5, 0.0F);
    int var13 = (int)var9;
    int var14 = (int)var11;
    int var15 = (int)var8;
    int var16 = (int)var10;
         DIAMOND_ROWS = (int)var12 * 4;
         var15 -= 2;
         var13 -= 2;
         dmiter.reset(var16 - var15);
    Vector2i var18 = diamondMatrixPos;
    IsoChunkMap var19 = IsoWorld.instance.getCell().getChunkMap(var0);

         while (dmiter.next(var18)) {
            if (var18 != nullptr) {
    IsoGridSquare var17 = var19.getGridSquare(var18.x + var15, var18.y + var13, var3x);
               if (var17 == nullptr) {
                  addMaskLocation(nullptr, var18.x + var15, var18.y + var13, var3x);
               } else {
    IsoChunk var20 = var17.getChunk();
                  if (var20 != nullptr && var17.IsOnScreen()) {
                     addMaskLocation(var17, var18.x + var15, var18.y + var13, var3x);
                  }
               }
            }
         }
      }
   }

    static void renderMaskFloor(int var0, int var1x, int var2x) {
      floorSprite.render(nullptr, var0, var1x, var2x, IsoDirections.N, offsetX, offsetY, defColorInfo, false);
   }

    static void renderMaskWall(IsoGridSquare var0, int var1x, int var2x, int var3x, bool var4, bool var5, int var6) {
      if (var0 != nullptr) {
    IsoGridSquare var7 = var0.nav[IsoDirections.S.index()];
    IsoGridSquare var8 = var0.nav[IsoDirections.E.index()];
    long var9 = System.currentTimeMillis();
    bool var11 = var7 != nullptr && var7.getPlayerCutawayFlag(var6, var9);
    bool var12 = var0.getPlayerCutawayFlag(var6, var9);
    bool var13 = var8 != nullptr && var8.getPlayerCutawayFlag(var6, var9);
    IsoSprite var14;
    IsoDirections var15;
         if (var4 && var5) {
            var14 = wallNWSprite;
            var15 = IsoDirections.NW;
         } else if (var4) {
            var14 = wallNSprite;
            var15 = IsoDirections.N;
         } else if (var5) {
            var14 = wallWSprite;
            var15 = IsoDirections.W;
         } else {
            var14 = wallSESprite;
            var15 = IsoDirections.W;
         }

         var0.DoCutawayShaderSprite(var14, var15, var11, var12, var13);
      }
   }

    static void renderMaskWallNoCuts(int var0, int var1x, int var2x, bool var3x, bool var4) {
      if (var3x && var4) {
         wallNWSprite.render(nullptr, var0, var1x, var2x, IsoDirections.N, offsetX, offsetY, defColorInfo, false);
      } else if (var3x) {
         wallNSprite.render(nullptr, var0, var1x, var2x, IsoDirections.N, offsetX, offsetY, defColorInfo, false);
      } else if (var4) {
         wallWSprite.render(nullptr, var0, var1x, var2x, IsoDirections.N, offsetX, offsetY, defColorInfo, false);
      } else {
         wallSESprite.render(nullptr, var0, var1x, var2x, IsoDirections.N, offsetX, offsetY, defColorInfo, false);
      }
   }

    static void renderFxMask(int var0) {
      if (DebugOptions.instance.Weather.Fx.getValue()) {
         if (!GameServer.bServer) {
            if (IsoWeatherFX.instance != nullptr) {
               if (LuaManager.thread == nullptr || !LuaManager.thread.bStep) {
                  if (DEBUG_KEYS && Core.bDebug) {
                     updateDebugKeys();
                  }

                  if (playerMasks[var0].maskEnabled) {
    PlayerFxMask var1x = playerMasks[curPlayerIndex];
                     if (var1x.maskEnabled) {
                        if (MASKING_ENABLED && !checkFbos()) {
                           MASKING_ENABLED = false;
                        }

                        if (MASKING_ENABLED && var1x.hasMaskToDraw) {
                           scanForTiles(var0);
    int var2x = IsoCamera.getOffscreenLeft(var0);
    int var3x = IsoCamera.getOffscreenTop(var0);
    int var4 = IsoCamera.getOffscreenWidth(var0);
    int var5 = IsoCamera.getOffscreenHeight(var0);
    int var6 = IsoCamera.getScreenWidth(var0);
    int var7 = IsoCamera.getScreenHeight(var0);
                           SpriteRenderer.instance.glIgnoreStyles(true);
                           if (MASKING_ENABLED) {
                              SpriteRenderer.instance.glBuffer(4, var0);
                              SpriteRenderer.instance.glDoStartFrameFx(var4, var5, var0);
                              if (PerformanceSettings.LightingFrameSkip < 3) {
                                 IsoWorld.instance.getCell().DrawStencilMask();
                                 SpriteRenderer.instance.glClearColor(0, 0, 0, 0);
                                 SpriteRenderer.instance.glClear(16640);
                                 SpriteRenderer.instance.glClearColor(0, 0, 0, 255);
                              }

    bool var8 = true;
    bool var9 = false;
                              WeatherFxMask[] var14 = playerMasks[var0].masks;
    int var15 = playerMasks[var0].maskPointer;

                              for (int var16 = 0; var16 < var15; var16++) {
    WeatherFxMask var17 = var14[var16];
                                 if (var17.enabled) {
                                    if ((var17.flags & 4) == 4) {
                                       SpriteRenderer.GL_BLENDFUNC_ENABLED = true;
                                       SpriteRenderer.instance.glBlendFunc(SCR_MASK_SUB, DST_MASK_SUB);
                                       SpriteRenderer.instance.glBlendEquation(32779);
                                       IndieGL.enableAlphaTest();
                                       IndieGL.glAlphaFunc(516, 0.02F);
                                       SpriteRenderer.GL_BLENDFUNC_ENABLED = false;
    bool var11 = (var17.flags & 1) == 1;
    bool var12 = (var17.flags & 2) == 2;
                                       renderMaskWall(var17.gs, var17.x, var17.y, var17.z, var11, var12, var0);
                                       SpriteRenderer.GL_BLENDFUNC_ENABLED = true;
                                       SpriteRenderer.instance.glBlendEquation(32774);
                                       SpriteRenderer.GL_BLENDFUNC_ENABLED = false;
    bool var13 = (var17.flags & 64) == 64;
                                       if (var13 && var17.gs != nullptr) {
                                          SpriteRenderer.GL_BLENDFUNC_ENABLED = true;
                                          SpriteRenderer.instance.glBlendFunc(SCR_MASK_ADD, DST_MASK_ADD);
                                          SpriteRenderer.GL_BLENDFUNC_ENABLED = false;
                                          var17.gs.RenderOpenDoorOnly();
                                       }
                                    } else {
                                       SpriteRenderer.GL_BLENDFUNC_ENABLED = true;
                                       SpriteRenderer.instance.glBlendFunc(SCR_MASK_ADD, DST_MASK_ADD);
                                       SpriteRenderer.GL_BLENDFUNC_ENABLED = false;
                                       renderMaskFloor(var17.x, var17.y, var17.z);
                                       var9 = (var17.flags & 16) == 16;
    bool var10 = (var17.flags & 8) == 8;
                                       if (!var9) {
    bool var19 = (var17.flags & 1) == 1;
    bool var20 = (var17.flags & 2) == 2;
                                          if (!var19 && !var20) {
                                             if ((var17.flags & 32) == 32) {
                                                renderMaskWall(var17.gs, var17.x, var17.y, var17.z, false, false, var0);
                                             }
                                          } else {
                                             renderMaskWall(var17.gs, var17.x, var17.y, var17.z, var19, var20, var0);
                                          }
                                       }

                                       if (var9 && var17.gs != nullptr) {
                                          var17.gs.RenderMinusFloorFxMask(var17.z + 1, false, false);
                                       }

                                       if (var10 && var17.gs != nullptr) {
                                          var17.gs.renderCharacters(var17.z + 1, false, false);
                                          SpriteRenderer.GL_BLENDFUNC_ENABLED = true;
                                          SpriteRenderer.instance.glBlendFunc(SCR_MASK_ADD, DST_MASK_ADD);
                                          SpriteRenderer.GL_BLENDFUNC_ENABLED = false;
                                       }
                                    }
                                 }
                              }

                              SpriteRenderer.instance.glBlendFunc(770, 771);
                              SpriteRenderer.instance.glBuffer(5, var0);
                              SpriteRenderer.instance.glDoEndFrameFx(var0);
                           }

                           if (DEBUG_MASK_AND_PARTICLES) {
                              SpriteRenderer.instance.glClearColor(0, 0, 0, 255);
                              SpriteRenderer.instance.glClear(16640);
                              SpriteRenderer.instance.glClearColor(0, 0, 0, 255);
                           } else if (DEBUG_MASK) {
                              SpriteRenderer.instance.glClearColor(0, 255, 0, 255);
                              SpriteRenderer.instance.glClear(16640);
                              SpriteRenderer.instance.glClearColor(0, 0, 0, 255);
                           }

                           if (!RenderSettings.getInstance().getPlayerSettings(var0).isExterior()) {
                              drawFxLayered(var0, false, false, false);
                           }

                           if (IsoWeatherFX.instance.hasCloudsToRender()) {
                              drawFxLayered(var0, true, false, false);
                           }

                           if (IsoWeatherFX.instance.hasFogToRender() && PerformanceSettings.FogQuality == 2) {
                              drawFxLayered(var0, false, true, false);
                           }

                           if (Core.OptionRenderPrecipitation == 1 && IsoWeatherFX.instance.hasPrecipitationToRender()) {
                              drawFxLayered(var0, false, false, true);
                           }

                           SpriteRenderer.GL_BLENDFUNC_ENABLED = true;
                           SpriteRenderer.instance.glIgnoreStyles(false);
                        } else {
                           if (IsoWorld.instance.getCell() != nullptr && IsoWorld.instance.getCell().getWeatherFX() != nullptr) {
                              SpriteRenderer.instance.glIgnoreStyles(true);
                              SpriteRenderer.instance.glBlendFunc(770, 771);
                              IsoWorld.instance.getCell().getWeatherFX().render();
                              SpriteRenderer.instance.glIgnoreStyles(false);
                           }
                        }
                     }
                  }
               }
            }
         }
      }
   }

    static void drawFxLayered(int var0, bool var1x, bool var2x, bool var3x) {
    int var4 = IsoCamera.getOffscreenLeft(var0);
    int var5 = IsoCamera.getOffscreenTop(var0);
    int var6 = IsoCamera.getOffscreenWidth(var0);
    int var7 = IsoCamera.getOffscreenHeight(var0);
    int var8 = IsoCamera.getScreenLeft(var0);
    int var9 = IsoCamera.getScreenTop(var0);
    int var10 = IsoCamera.getScreenWidth(var0);
    int var11 = IsoCamera.getScreenHeight(var0);
      SpriteRenderer.instance.glBuffer(6, var0);
      SpriteRenderer.instance.glDoStartFrameFx(var6, var7, var0);
      if (!var1x && !var2x && !var3x) {
    Color var12 = RenderSettings.getInstance().getMaskClearColorForPlayer(var0);
         SpriteRenderer.GL_BLENDFUNC_ENABLED = true;
         SpriteRenderer.instance.glBlendFuncSeparate(SCR_PARTICLES, DST_PARTICLES, 1, 771);
         SpriteRenderer.GL_BLENDFUNC_ENABLED = false;
         SpriteRenderer.instance.renderi(texWhite, 0, 0, var6, var7, var12.r, var12.g, var12.b, var12.a, nullptr);
         SpriteRenderer.GL_BLENDFUNC_ENABLED = true;
      } else if (IsoWorld.instance.getCell() != nullptr && IsoWorld.instance.getCell().getWeatherFX() != nullptr) {
         SpriteRenderer.GL_BLENDFUNC_ENABLED = true;
         SpriteRenderer.instance.glBlendFuncSeparate(SCR_PARTICLES, DST_PARTICLES, 1, 771);
         SpriteRenderer.GL_BLENDFUNC_ENABLED = false;
         IsoWorld.instance.getCell().getWeatherFX().renderLayered(var1x, var2x, var3x);
         SpriteRenderer.GL_BLENDFUNC_ENABLED = true;
      }

      if (MASKING_ENABLED) {
         SpriteRenderer.instance.glBlendFunc(SCR_MERGE, DST_MERGE);
         SpriteRenderer.instance.glBlendEquation(32779);
         ((Texture)fboMask.getTexture()).rendershader2(0.0F, 0.0F, var6, var7, var8, var9, var10, var11, 1.0F, 1.0F, 1.0F, 1.0F);
         SpriteRenderer.instance.glBlendEquation(32774);
      }

      SpriteRenderer.instance.glBlendFunc(770, 771);
      SpriteRenderer.instance.glBuffer(7, var0);
      SpriteRenderer.instance.glDoEndFrameFx(var0);
    Texture var25;
      if ((DEBUG_MASK || DEBUG_MASK_AND_PARTICLES) && !DEBUG_MASK_AND_PARTICLES) {
         var25 = (Texture)fboMask.getTexture();
         SpriteRenderer.instance.glBlendFunc(770, 771);
      } else {
         var25 = (Texture)fboParticles.getTexture();
         SpriteRenderer.instance.glBlendFunc(SCR_FINAL, DST_FINAL);
      }

    float var13 = 1.0F;
    float var14 = 1.0F;
    float var15 = 1.0F;
    float var16 = 1.0F;
    float var21 = (float)var8 / var25.getWidthHW();
    float var22 = (float)var9 / var25.getHeightHW();
    float var23 = (float)(var8 + var10) / var25.getWidthHW();
    float var24 = (float)(var9 + var11) / var25.getHeightHW();
      SpriteRenderer.instance.render(var25, 0.0F, 0.0F, var6, var7, var13, var14, var15, var16, var21, var24, var23, var24, var23, var22, var21, var22);
   }

    static void initGlIds() {
      for (int var0 = 0; var0 < test.length; var0++) {
         if (test[var0] == SCR_MASK_ADD) {
            ID_SCR_MASK_ADD = var0;
         } else if (test[var0] == DST_MASK_ADD) {
            ID_DST_MASK_ADD = var0;
         } else if (test[var0] == SCR_MASK_SUB) {
            ID_SCR_MASK_SUB = var0;
         } else if (test[var0] == DST_MASK_SUB) {
            ID_DST_MASK_SUB = var0;
         } else if (test[var0] == SCR_PARTICLES) {
            ID_SCR_PARTICLES = var0;
         } else if (test[var0] == DST_PARTICLES) {
            ID_DST_PARTICLES = var0;
         } else if (test[var0] == SCR_MERGE) {
            ID_SCR_MERGE = var0;
         } else if (test[var0] == DST_MERGE) {
            ID_DST_MERGE = var0;
         } else if (test[var0] == SCR_FINAL) {
            ID_SCR_FINAL = var0;
         } else if (test[var0] == DST_FINAL) {
            ID_DST_FINAL = var0;
         }
      }
   }

    static void updateDebugKeys() {
      if (keypause > 0) {
         keypause--;
      }

      if (keypause == 0) {
    bool var0 = false;
    bool var1x = false;
    bool var2x = false;
    bool var3x = false;
    bool var4 = false;
         if (TARGET_BLEND == 0) {
            var1 = ID_SCR_MASK_ADD;
            var2 = ID_DST_MASK_ADD;
         } else if (TARGET_BLEND == 1) {
            var1 = ID_SCR_MASK_SUB;
            var2 = ID_DST_MASK_SUB;
         } else if (TARGET_BLEND == 2) {
            var1 = ID_SCR_MERGE;
            var2 = ID_DST_MERGE;
         } else if (TARGET_BLEND == 3) {
            var1 = ID_SCR_FINAL;
            var2 = ID_DST_FINAL;
         } else if (TARGET_BLEND == 4) {
            var1 = ID_SCR_PARTICLES;
            var2 = ID_DST_PARTICLES;
         }

         if (GameKeyboard.isKeyDown(79)) {
            var1--;
            if (var1 < 0) {
               var1 = test.length - 1;
            }

            var0 = true;
         } else if (GameKeyboard.isKeyDown(81)) {
            var1++;
            if (var1 >= test.length) {
               var1 = 0;
            }

            var0 = true;
         } else if (GameKeyboard.isKeyDown(75)) {
            var2--;
            if (var2 < 0) {
               var2 = test.length - 1;
            }

            var0 = true;
         } else if (GameKeyboard.isKeyDown(77)) {
            var2++;
            if (var2 >= test.length) {
               var2 = 0;
            }

            var0 = true;
         } else if (GameKeyboard.isKeyDown(71)) {
            TARGET_BLEND--;
            if (TARGET_BLEND < 0) {
               TARGET_BLEND = 4;
            }

            var0 = true;
            var1x = true;
         } else if (GameKeyboard.isKeyDown(73)) {
            TARGET_BLEND++;
            if (TARGET_BLEND >= 5) {
               TARGET_BLEND = 0;
            }

            var0 = true;
            var1x = true;
         } else if (MASKING_ENABLED && GameKeyboard.isKeyDown(82)) {
            DEBUG_MASK = !DEBUG_MASK;
            var0 = true;
            var2x = true;
         } else if (MASKING_ENABLED && GameKeyboard.isKeyDown(80)) {
            DEBUG_MASK_AND_PARTICLES = !DEBUG_MASK_AND_PARTICLES;
            var0 = true;
            var3x = true;
         } else if (!GameKeyboard.isKeyDown(72) && GameKeyboard.isKeyDown(76)) {
            MASKING_ENABLED = !MASKING_ENABLED;
            var0 = true;
            var4 = true;
         }

         if (var0) {
            if (var1x) {
               if (TARGET_BLEND == 0) {
                  DebugLog.log("TargetBlend = MASK_ADD");
               } else if (TARGET_BLEND == 1) {
                  DebugLog.log("TargetBlend = MASK_SUB");
               } else if (TARGET_BLEND == 2) {
                  DebugLog.log("TargetBlend = MERGE");
               } else if (TARGET_BLEND == 3) {
                  DebugLog.log("TargetBlend = FINAL");
               } else if (TARGET_BLEND == 4) {
                  DebugLog.log("TargetBlend = PARTICLES");
               }
            } else if (var2x) {
               DebugLog.log("DEBUG_MASK = " + DEBUG_MASK);
            } else if (var3x) {
               DebugLog.log("DEBUG_MASK_AND_PARTICLES = " + DEBUG_MASK_AND_PARTICLES);
            } else if (var4) {
               DebugLog.log("MASKING_ENABLED = " + MASKING_ENABLED);
            } else {
               if (TARGET_BLEND == 0) {
                  ID_SCR_MASK_ADD = var1;
                  ID_DST_MASK_ADD = var2;
                  SCR_MASK_ADD = test[ID_SCR_MASK_ADD];
                  DST_MASK_ADD = test[ID_DST_MASK_ADD];
               } else if (TARGET_BLEND == 1) {
                  ID_SCR_MASK_SUB = var1;
                  ID_DST_MASK_SUB = var2;
                  SCR_MASK_SUB = test[ID_SCR_MASK_SUB];
                  DST_MASK_SUB = test[ID_DST_MASK_SUB];
               } else if (TARGET_BLEND == 2) {
                  ID_SCR_MERGE = var1;
                  ID_DST_MERGE = var2;
                  SCR_MERGE = test[ID_SCR_MERGE];
                  DST_MERGE = test[ID_DST_MERGE];
               } else if (TARGET_BLEND == 3) {
                  ID_SCR_FINAL = var1;
                  ID_DST_FINAL = var2;
                  SCR_FINAL = test[ID_SCR_FINAL];
                  DST_FINAL = test[ID_DST_FINAL];
               } else if (TARGET_BLEND == 4) {
                  ID_SCR_PARTICLES = var1;
                  ID_DST_PARTICLES = var2;
                  SCR_PARTICLES = test[ID_SCR_PARTICLES];
                  DST_PARTICLES = test[ID_DST_PARTICLES];
               }

               DebugLog.log("Blendmode = " + testNames[var1] + " -> " + testNames[var2]);
            }

            keypause = 30;
         }
      }
   }
}
} // namespace fx
} // namespace weather
} // namespace iso
} // namespace zombie
