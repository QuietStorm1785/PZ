#pragma once
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
#include "zombie/characters/IsoGameCharacter.h"
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
#include "zombie/iso/areas/isoregion/regions/IsoWorldRegion.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/network/GameServer.h"

namespace zombie {
namespace iso {
namespace weather {
namespace fx {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


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
 static ColorInfo defColorInfo = new ColorInfo();
 static int DIAMOND_ROWS = 1000;
 int x;
 int y;
 int z;
 int flags;
 IsoGridSquare gs;
 bool enabled;
 private static WeatherFxMask.PlayerFxMask[] playerMasks = new WeatherFxMask.PlayerFxMask[4];
 static DiamondMatrixIterator dmiter = new DiamondMatrixIterator(0);
 static const Vector2i diamondMatrixPos = new Vector2i();
 static Vector3f tmpVec = new Vector3f();
 private static IsoGameCharacter.TorchInfo tmpTorch = new IsoGameCharacter.TorchInfo();
 static ColorInfo tmpColInfo = new ColorInfo();
 private static int[] test = new int[]{0, 1, 768, 769, 774, 775, 770, 771, 772, 773, 32769, 32770, 32771, 32772, 776, 35065, 35066, 34185, 35067};
 private static String[] testNames = new String[]{
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
 for (int int0 = 0; int0 < playerMasks.length; int0++) {
 playerMasks[int0] = new WeatherFxMask.PlayerFxMask();
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
 TextureFBO textureFBO = Core.getInstance().getOffscreenBuffer();
 if (Core.getInstance().getOffscreenBuffer() == nullptr) {
 DebugLog.log("fbo=" + (textureFBO != nullptr);
 return false;
 } else {
 int int0 = Core.getInstance().getScreenWidth();
 int int1 = Core.getInstance().getScreenHeight();
 if (fboMask != nullptr && fboParticles != nullptr && fboMask.getTexture().getWidth() == int0 && fboMask.getTexture().getHeight() == int1) {
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
 Texture texture0 = new Texture(int0, int1, 16);
 fboMask = new TextureFBO(texture0);
 } catch (Exception exception0) {
 DebugLog.log(exception0.getStackTrace());
 exception0.printStackTrace();
 }

 try {
 Texture texture1 = new Texture(int0, int1, 16);
 fboParticles = new TextureFBO(texture1);
 } catch (Exception exception1) {
 DebugLog.log(exception1.getStackTrace());
 exception1.printStackTrace();
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

 static bool isOnScreen(int int0, int int1, int int2) {
 float float0 = (int)IsoUtils.XToScreenInt(int0, int1, int2, 0);
 float float1 = (int)IsoUtils.YToScreenInt(int0, int1, int2, 0);
 float0 -= (int)IsoCamera.frameState.OffX;
 float1 -= (int)IsoCamera.frameState.OffY;
 if (float0 + 32 * Core.TileScale <= 0.0F) {
 return false;
 } else if (float1 + 32 * Core.TileScale <= 0.0F) {
 return false;
 } else {
 return float0 - 32 * Core.TileScale >= IsoCamera.frameState.OffscreenWidth
 ? false
 : !(float1 - 96 * Core.TileScale >= IsoCamera.frameState.OffscreenHeight);
 }
 }

 bool isLoc(int int2, int int1, int int0) {
 return this->x == int2 && this->y == int1 && this->z == int0;
 }

 static bool playerHasMaskToDraw(int int0) {
 return int0 < playerMasks.length ? playerMasks[int0].hasMaskToDraw : false;
 }

 static void setDiamondIterDone(int int0) {
 if (int0 < playerMasks.length) {
 playerMasks[int0].DIAMOND_ITER_DONE = true;
 }
 }

 static void forceMaskUpdate(int int0) {
 if (int0 < playerMasks.length) {
 playerMasks[int0].plrSquare = nullptr;
 }
 }

 static void forceMaskUpdateAll() {
 if (!GameServer.bServer) {
 for (int int0 = 0; int0 < playerMasks.length; int0++) {
 playerMasks[int0].plrSquare = nullptr;
 }
 }
 }

 static bool getIsStairs(IsoGridSquare square) {
 return square != nullptr
 && (
 square.Has(IsoObjectType.stairsBN)
 || square.Has(IsoObjectType.stairsBW)
 || square.Has(IsoObjectType.stairsMN)
 || square.Has(IsoObjectType.stairsMW)
 || square.Has(IsoObjectType.stairsTN)
 || square.Has(IsoObjectType.stairsTW)
 );
 }

 static bool getHasDoor(IsoGridSquare square) {
 return square != nullptr
 && (square.Is(IsoFlagType.cutN) || square.Is(IsoFlagType.cutW)
 && (square.Is(IsoFlagType.DoorWallN) || square.Is(IsoFlagType.DoorWallW)
 && !square.Is(IsoFlagType.doorN)
 && !square.Is(IsoFlagType.doorW)
 ? square.getCanSee(curPlayerIndex)
 : false;
 }

 static void addMaskLocation(IsoGridSquare square0, int int1, int int2, int int0) {
 if (!GameServer.bServer) {
 WeatherFxMask.PlayerFxMask playerFxMask = playerMasks[curPlayerIndex];
 if (playerFxMask.requiresUpdate) {
 if (playerFxMask.hasMaskToDraw && playerFxMask.playerZ == int0) {
 if (isInPlayerBuilding(square0, int1, int2, int0) {
 IsoGridSquare square1 = IsoWorld.instance.getCell().getChunkMap(curPlayerIndex).getGridSquare(int1, int2 - 1, int0);
 bool boolean0 = !isInPlayerBuilding(square1, int1, int2 - 1, int0);
 square1 = IsoWorld.instance.getCell().getChunkMap(curPlayerIndex).getGridSquare(int1 - 1, int2, int0);
 bool boolean1 = !isInPlayerBuilding(square1, int1 - 1, int2, int0);
 square1 = IsoWorld.instance.getCell().getChunkMap(curPlayerIndex).getGridSquare(int1 - 1, int2 - 1, int0);
 bool boolean2 = !isInPlayerBuilding(square1, int1 - 1, int2 - 1, int0);
 uint8_t byte0 = 0;
 if (boolean0) {
 byte0 |= 1;
 }

 if (boolean1) {
 byte0 |= 2;
 }

 if (boolean2) {
 byte0 |= 32;
 }

 bool boolean3 = false;
 bool boolean4 = getIsStairs(square0);
 if (square0 != nullptr && (boolean0 || boolean1 || boolean2) {
 uint8_t byte1 = 24;
 if (boolean0 && !square0.getProperties().Is(IsoFlagType.WallN) && !square0.Is(IsoFlagType.WallNW) {
 playerFxMask.addMask(int1 - 1, int2, int0, nullptr, 8, false);
 playerFxMask.addMask(int1, int2, int0, square0, byte1);
 playerFxMask.addMask(int1 + 1, int2, int0, nullptr, byte1, false);
 playerFxMask.addMask(int1 + 2, int2, int0, nullptr, 8, false);
 playerFxMask.addMask(int1, int2 + 1, int0, nullptr, 8, false);
 playerFxMask.addMask(int1 + 1, int2 + 1, int0, nullptr, byte1, false);
 playerFxMask.addMask(int1 + 2, int2 + 1, int0, nullptr, byte1, false);
 playerFxMask.addMask(int1 + 2, int2 + 2, int0, nullptr, 16, false);
 playerFxMask.addMask(int1 + 3, int2 + 2, int0, nullptr, 16, false);
 boolean3 = true;
 }

 if (boolean1 && !square0.getProperties().Is(IsoFlagType.WallW) && !square0.getProperties().Is(IsoFlagType.WallNW) {
 playerFxMask.addMask(int1, int2 - 1, int0, nullptr, 8, false);
 playerFxMask.addMask(int1, int2, int0, square0, byte1);
 playerFxMask.addMask(int1, int2 + 1, int0, nullptr, byte1, false);
 playerFxMask.addMask(int1, int2 + 2, int0, nullptr, 8, false);
 playerFxMask.addMask(int1 + 1, int2, int0, nullptr, 8, false);
 playerFxMask.addMask(int1 + 1, int2 + 1, int0, nullptr, byte1, false);
 playerFxMask.addMask(int1 + 1, int2 + 2, int0, nullptr, byte1, false);
 playerFxMask.addMask(int1 + 2, int2 + 2, int0, nullptr, 16, false);
 playerFxMask.addMask(int1 + 2, int2 + 3, int0, nullptr, 16, false);
 boolean3 = true;
 }

 if (boolean2) {
 uint8_t byte2 = boolean4 ? byte1 : byte0;
 playerFxMask.addMask(int1, int2, int0, square0, byte2);
 boolean3 = true;
 }
 }

 if (!boolean3) {
 uint8_t byte3 = boolean4 ? 24 : byte0;
 playerFxMask.addMask(int1, int2, int0, square0, byte3);
 }
 } else {
 IsoGridSquare square2 = IsoWorld.instance.getCell().getChunkMap(curPlayerIndex).getGridSquare(int1, int2 - 1, int0);
 bool boolean5 = isInPlayerBuilding(square2, int1, int2 - 1, int0);
 square2 = IsoWorld.instance.getCell().getChunkMap(curPlayerIndex).getGridSquare(int1 - 1, int2, int0);
 bool boolean6 = isInPlayerBuilding(square2, int1 - 1, int2, int0);
 if (!boolean5 && !boolean6) {
 square2 = IsoWorld.instance.getCell().getChunkMap(curPlayerIndex).getGridSquare(int1 - 1, int2 - 1, int0);
 if (isInPlayerBuilding(square2, int1 - 1, int2 - 1, int0) {
 playerFxMask.addMask(int1, int2, int0, square0, 4);
 }
 } else {
 uint8_t byte4 = 4;
 if (boolean5) {
 byte4 |= 1;
 }

 if (boolean6) {
 byte4 |= 2;
 }

 if (getHasDoor(square0) {
 byte4 |= 64;
 }

 playerFxMask.addMask(int1, int2, int0, square0, byte4);
 }
 }
 }
 }
 }
 }

 static bool isInPlayerBuilding(IsoGridSquare square, int int0, int int1, int int2) {
 WeatherFxMask.PlayerFxMask playerFxMask = playerMasks[curPlayerIndex];
 if (square != nullptr && square.Is(IsoFlagType.solidfloor) {
 if (square.getBuilding() != nullptr && square.getBuilding() == playerFxMask.player.getBuilding()) {
 return true;
 }

 if (square.getBuilding() == nullptr) {
 return playerFxMask.curIsoWorldRegion != nullptr
 && square.getIsoWorldRegion() != nullptr
 && square.getIsoWorldRegion().isFogMask()
 && (square.getIsoWorldRegion() == playerFxMask.curIsoWorldRegion || playerFxMask.curConnectedRegions.contains(square.getIsoWorldRegion()));
 }
 } else {
 if (isInteriorLocation(int0, int1, int2) {
 return true;
 }

 if (square != nullptr && square.getBuilding() == nullptr) {
 return playerFxMask.curIsoWorldRegion != nullptr
 && square.getIsoWorldRegion() != nullptr
 && square.getIsoWorldRegion().isFogMask()
 && (square.getIsoWorldRegion() == playerFxMask.curIsoWorldRegion || playerFxMask.curConnectedRegions.contains(square.getIsoWorldRegion()));
 }

 if (square == nullptr && playerFxMask.curIsoWorldRegion != nullptr) {
 IWorldRegion iWorldRegion = IsoRegions.getIsoWorldRegion(int0, int1, int2);
 return iWorldRegion != nullptr
 && iWorldRegion.isFogMask()
 && (iWorldRegion == playerFxMask.curIsoWorldRegion || playerFxMask.curConnectedRegions.contains(iWorldRegion);
 }
 }

 return false;
 }

 static bool isInteriorLocation(int int2, int int3, int int1) {
 WeatherFxMask.PlayerFxMask playerFxMask = playerMasks[curPlayerIndex];

 for (int int0 = int1; int0 >= 0; int0--) {
 IsoGridSquare square = IsoWorld.instance.getCell().getChunkMap(curPlayerIndex).getGridSquare(int2, int3, int0);
 if (square != nullptr) {
 if (square.getBuilding() != nullptr && square.getBuilding() == playerFxMask.player.getBuilding()) {
 return true;
 }

 if (square.Is(IsoFlagType.exterior) {
 return false;
 }
 }
 }

 return false;
 }

 static void scanForTiles(int int0) {
 WeatherFxMask.PlayerFxMask playerFxMask = playerMasks[curPlayerIndex];
 if (!playerFxMask.DIAMOND_ITER_DONE) {
 IsoPlayer player = IsoPlayer.players[int0];
 int int1 = (int)player.getZ();
 uint8_t byte0 = 0;
 uint8_t byte1 = 0;
 int int2 = byte0 + IsoCamera.getOffscreenWidth(int0);
 int int3 = byte1 + IsoCamera.getOffscreenHeight(int0);
 float float0 = IsoUtils.XToIso(byte0, byte1, 0.0F);
 float float1 = IsoUtils.YToIso(int2, byte1, 0.0F);
 float float2 = IsoUtils.XToIso(int2, int3, 6.0F);
 float float3 = IsoUtils.YToIso(byte0, int3, 6.0F);
 float float4 = IsoUtils.XToIso(int2, byte1, 0.0F);
 int int4 = (int)float1;
 int int5 = (int)float3;
 int int6 = (int)float0;
 int int7 = (int)float2;
 DIAMOND_ROWS = (int)float4 * 4;
 int6 -= 2;
 int4 -= 2;
 dmiter.reset(int7 - int6);
 Vector2i vector2i = diamondMatrixPos;
 IsoChunkMap chunkMap = IsoWorld.instance.getCell().getChunkMap(int0);

 while (dmiter.next(vector2i) {
 if (vector2i != nullptr) {
 IsoGridSquare square = chunkMap.getGridSquare(vector2i.x + int6, vector2i.y + int4, int1);
 if (square == nullptr) {
 addMaskLocation(nullptr, vector2i.x + int6, vector2i.y + int4, int1);
 } else {
 IsoChunk chunk = square.getChunk();
 if (chunk != nullptr && square.IsOnScreen()) {
 addMaskLocation(square, vector2i.x + int6, vector2i.y + int4, int1);
 }
 }
 }
 }
 }
 }

 static void renderMaskFloor(int int2, int int1, int int0) {
 floorSprite.render(nullptr, int2, int1, int0, IsoDirections.N, offsetX, offsetY, defColorInfo, false);
 }

 static void renderMaskWall(IsoGridSquare square0, int var1x, int var2x, int var3x, bool boolean3, bool boolean4, int int0) {
 if (square0 != nullptr) {
 IsoGridSquare square1 = square0.nav[IsoDirections.S.index()];
 IsoGridSquare square2 = square0.nav[IsoDirections.E.index()];
 long long0 = System.currentTimeMillis();
 bool boolean0 = square1 != nullptr && square1.getPlayerCutawayFlag(int0, long0);
 bool boolean1 = square0.getPlayerCutawayFlag(int0, long0);
 bool boolean2 = square2 != nullptr && square2.getPlayerCutawayFlag(int0, long0);
 IsoSprite sprite;
 IsoDirections directions;
 if (boolean3 && boolean4) {
 sprite = wallNWSprite;
 directions = IsoDirections.NW;
 } else if (boolean3) {
 sprite = wallNSprite;
 directions = IsoDirections.N;
 } else if (boolean4) {
 sprite = wallWSprite;
 directions = IsoDirections.W;
 } else {
 sprite = wallSESprite;
 directions = IsoDirections.W;
 }

 square0.DoCutawayShaderSprite(sprite, directions, boolean0, boolean1, boolean2);
 }
 }

 static void renderMaskWallNoCuts(int int2, int int1, int int0, bool boolean0, bool boolean1) {
 if (boolean0 && boolean1) {
 wallNWSprite.render(nullptr, int2, int1, int0, IsoDirections.N, offsetX, offsetY, defColorInfo, false);
 } else if (boolean0) {
 wallNSprite.render(nullptr, int2, int1, int0, IsoDirections.N, offsetX, offsetY, defColorInfo, false);
 } else if (boolean1) {
 wallWSprite.render(nullptr, int2, int1, int0, IsoDirections.N, offsetX, offsetY, defColorInfo, false);
 } else {
 wallSESprite.render(nullptr, int2, int1, int0, IsoDirections.N, offsetX, offsetY, defColorInfo, false);
 }
 }

 static void renderFxMask(int int0) {
 if (DebugOptions.instance.Weather.Fx.getValue()) {
 if (!GameServer.bServer) {
 if (IsoWeatherFX.instance != nullptr) {
 if (LuaManager.thread == nullptr || !LuaManager.thread.bStep) {
 if (DEBUG_KEYS && Core.bDebug) {
 updateDebugKeys();
 }

 if (playerMasks[int0].maskEnabled) {
 WeatherFxMask.PlayerFxMask playerFxMask = playerMasks[curPlayerIndex];
 if (playerFxMask.maskEnabled) {
 if (MASKING_ENABLED && !checkFbos()) {
 MASKING_ENABLED = false;
 }

 if (MASKING_ENABLED && playerFxMask.hasMaskToDraw) {
 scanForTiles(int0);
 int int1 = IsoCamera.getOffscreenLeft(int0);
 int int2 = IsoCamera.getOffscreenTop(int0);
 int int3 = IsoCamera.getOffscreenWidth(int0);
 int int4 = IsoCamera.getOffscreenHeight(int0);
 int int5 = IsoCamera.getScreenWidth(int0);
 int int6 = IsoCamera.getScreenHeight(int0);
 SpriteRenderer.instance.glIgnoreStyles(true);
 if (MASKING_ENABLED) {
 SpriteRenderer.instance.glBuffer(4, int0);
 SpriteRenderer.instance.glDoStartFrameFx(int3, int4, int0);
 if (PerformanceSettings.LightingFrameSkip < 3) {
 IsoWorld.instance.getCell().DrawStencilMask();
 SpriteRenderer.instance.glClearColor(0, 0, 0, 0);
 SpriteRenderer.instance.glClear(16640);
 SpriteRenderer.instance.glClearColor(0, 0, 0, 255);
 }

 bool boolean0 = true;
 bool boolean1 = false;
 WeatherFxMask[] weatherFxMasks = playerMasks[int0].masks;
 int int7 = playerMasks[int0].maskPointer;

 for (int int8 = 0; int8 < int7; int8++) {
 WeatherFxMask weatherFxMask = weatherFxMasks[int8];
 if (weatherFxMask.enabled) {
 if ((weatherFxMask.flags & 4) == 4) {
 SpriteRenderer.GL_BLENDFUNC_ENABLED = true;
 SpriteRenderer.instance.glBlendFunc(SCR_MASK_SUB, DST_MASK_SUB);
 SpriteRenderer.instance.glBlendEquation(32779);
 IndieGL.enableAlphaTest();
 IndieGL.glAlphaFunc(516, 0.02F);
 SpriteRenderer.GL_BLENDFUNC_ENABLED = false;
 bool boolean2 = (weatherFxMask.flags & 1) == 1;
 bool boolean3 = (weatherFxMask.flags & 2) == 2;
 renderMaskWall(
 weatherFxMask.gs, weatherFxMask.x, weatherFxMask.y, weatherFxMask.z, boolean2, boolean3, int0
 );
 SpriteRenderer.GL_BLENDFUNC_ENABLED = true;
 SpriteRenderer.instance.glBlendEquation(32774);
 SpriteRenderer.GL_BLENDFUNC_ENABLED = false;
 bool boolean4 = (weatherFxMask.flags & 64) == 64;
 if (boolean4 && weatherFxMask.gs != nullptr) {
 SpriteRenderer.GL_BLENDFUNC_ENABLED = true;
 SpriteRenderer.instance.glBlendFunc(SCR_MASK_ADD, DST_MASK_ADD);
 SpriteRenderer.GL_BLENDFUNC_ENABLED = false;
 weatherFxMask.gs.RenderOpenDoorOnly();
 }
 } else {
 SpriteRenderer.GL_BLENDFUNC_ENABLED = true;
 SpriteRenderer.instance.glBlendFunc(SCR_MASK_ADD, DST_MASK_ADD);
 SpriteRenderer.GL_BLENDFUNC_ENABLED = false;
 renderMaskFloor(weatherFxMask.x, weatherFxMask.y, weatherFxMask.z);
 boolean1 = (weatherFxMask.flags & 16) == 16;
 bool boolean5 = (weatherFxMask.flags & 8) == 8;
 if (!boolean1) {
 bool boolean6 = (weatherFxMask.flags & 1) == 1;
 bool boolean7 = (weatherFxMask.flags & 2) == 2;
 if (!boolean6 && !boolean7) {
 if ((weatherFxMask.flags & 32) == 32) {
 renderMaskWall(
 weatherFxMask.gs, weatherFxMask.x, weatherFxMask.y, weatherFxMask.z, false, false, int0
 );
 }
 } else {
 renderMaskWall(
 weatherFxMask.gs, weatherFxMask.x, weatherFxMask.y, weatherFxMask.z, boolean6, boolean7, int0
 );
 }
 }

 if (boolean1 && weatherFxMask.gs != nullptr) {
 weatherFxMask.gs.RenderMinusFloorFxMask(weatherFxMask.z + 1, false, false);
 }

 if (boolean5 && weatherFxMask.gs != nullptr) {
 weatherFxMask.gs.renderCharacters(weatherFxMask.z + 1, false, false);
 SpriteRenderer.GL_BLENDFUNC_ENABLED = true;
 SpriteRenderer.instance.glBlendFunc(SCR_MASK_ADD, DST_MASK_ADD);
 SpriteRenderer.GL_BLENDFUNC_ENABLED = false;
 }
 }
 }
 }

 SpriteRenderer.instance.glBlendFunc(770, 771);
 SpriteRenderer.instance.glBuffer(5, int0);
 SpriteRenderer.instance.glDoEndFrameFx(int0);
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

 if (!RenderSettings.getInstance().getPlayerSettings(int0).isExterior()) {
 drawFxLayered(int0, false, false, false);
 }

 if (IsoWeatherFX.instance.hasCloudsToRender()) {
 drawFxLayered(int0, true, false, false);
 }

 if (IsoWeatherFX.instance.hasFogToRender() && PerformanceSettings.FogQuality == 2) {
 drawFxLayered(int0, false, true, false);
 }

 if (Core.OptionRenderPrecipitation == 1 && IsoWeatherFX.instance.hasPrecipitationToRender()) {
 drawFxLayered(int0, false, false, true);
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

 static void drawFxLayered(int int1, bool boolean2, bool boolean1, bool boolean0) {
 int int0 = IsoCamera.getOffscreenLeft(int1);
 int int2 = IsoCamera.getOffscreenTop(int1);
 int int3 = IsoCamera.getOffscreenWidth(int1);
 int int4 = IsoCamera.getOffscreenHeight(int1);
 int int5 = IsoCamera.getScreenLeft(int1);
 int int6 = IsoCamera.getScreenTop(int1);
 int int7 = IsoCamera.getScreenWidth(int1);
 int int8 = IsoCamera.getScreenHeight(int1);
 SpriteRenderer.instance.glBuffer(6, int1);
 SpriteRenderer.instance.glDoStartFrameFx(int3, int4, int1);
 if (!boolean2 && !boolean1 && !boolean0) {
 Color color = RenderSettings.getInstance().getMaskClearColorForPlayer(int1);
 SpriteRenderer.GL_BLENDFUNC_ENABLED = true;
 SpriteRenderer.instance.glBlendFuncSeparate(SCR_PARTICLES, DST_PARTICLES, 1, 771);
 SpriteRenderer.GL_BLENDFUNC_ENABLED = false;
 SpriteRenderer.instance.renderi(texWhite, 0, 0, int3, int4, color.r, color.g, color.b, color.a, nullptr);
 SpriteRenderer.GL_BLENDFUNC_ENABLED = true;
 } else if (IsoWorld.instance.getCell() != nullptr && IsoWorld.instance.getCell().getWeatherFX() != nullptr) {
 SpriteRenderer.GL_BLENDFUNC_ENABLED = true;
 SpriteRenderer.instance.glBlendFuncSeparate(SCR_PARTICLES, DST_PARTICLES, 1, 771);
 SpriteRenderer.GL_BLENDFUNC_ENABLED = false;
 IsoWorld.instance.getCell().getWeatherFX().renderLayered(boolean2, boolean1, boolean0);
 SpriteRenderer.GL_BLENDFUNC_ENABLED = true;
 }

 if (MASKING_ENABLED) {
 SpriteRenderer.instance.glBlendFunc(SCR_MERGE, DST_MERGE);
 SpriteRenderer.instance.glBlendEquation(32779);
 ((Texture)fboMask.getTexture()).rendershader2(0.0F, 0.0F, int3, int4, int5, int6, int7, int8, 1.0F, 1.0F, 1.0F, 1.0F);
 SpriteRenderer.instance.glBlendEquation(32774);
 }

 SpriteRenderer.instance.glBlendFunc(770, 771);
 SpriteRenderer.instance.glBuffer(7, int1);
 SpriteRenderer.instance.glDoEndFrameFx(int1);
 Texture texture;
 if ((DEBUG_MASK || DEBUG_MASK_AND_PARTICLES) && !DEBUG_MASK_AND_PARTICLES) {
 texture = (Texture)fboMask.getTexture();
 SpriteRenderer.instance.glBlendFunc(770, 771);
 } else {
 texture = (Texture)fboParticles.getTexture();
 SpriteRenderer.instance.glBlendFunc(SCR_FINAL, DST_FINAL);
 }

 float float0 = 1.0F;
 float float1 = 1.0F;
 float float2 = 1.0F;
 float float3 = 1.0F;
 float float4 = (float)int5 / texture.getWidthHW();
 float float5 = (float)int6 / texture.getHeightHW();
 float float6 = (float)(int5 + int7) / texture.getWidthHW();
 float float7 = (float)(int6 + int8) / texture.getHeightHW();
 SpriteRenderer.instance
 .render(texture, 0.0F, 0.0F, int3, int4, float0, float1, float2, float3, float4, float7, float6, float7, float6, float5, float4, float5);
 }

 static void initGlIds() {
 for (int int0 = 0; int0 < test.length; int0++) {
 if (test[int0] == SCR_MASK_ADD) {
 ID_SCR_MASK_ADD = int0;
 } else if (test[int0] == DST_MASK_ADD) {
 ID_DST_MASK_ADD = int0;
 } else if (test[int0] == SCR_MASK_SUB) {
 ID_SCR_MASK_SUB = int0;
 } else if (test[int0] == DST_MASK_SUB) {
 ID_DST_MASK_SUB = int0;
 } else if (test[int0] == SCR_PARTICLES) {
 ID_SCR_PARTICLES = int0;
 } else if (test[int0] == DST_PARTICLES) {
 ID_DST_PARTICLES = int0;
 } else if (test[int0] == SCR_MERGE) {
 ID_SCR_MERGE = int0;
 } else if (test[int0] == DST_MERGE) {
 ID_DST_MERGE = int0;
 } else if (test[int0] == SCR_FINAL) {
 ID_SCR_FINAL = int0;
 } else if (test[int0] == DST_FINAL) {
 ID_DST_FINAL = int0;
 }
 }
 }

 static void updateDebugKeys() {
 if (keypause > 0) {
 keypause--;
 }

 if (keypause == 0) {
 bool boolean0 = false;
 bool boolean1 = false;
 bool boolean2 = false;
 bool boolean3 = false;
 bool boolean4 = false;
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

 if (GameKeyboard.isKeyDown(79) {
 var1--;
 if (var1 < 0) {
 var1 = test.length - 1;
 }

 boolean0 = true;
 } else if (GameKeyboard.isKeyDown(81) {
 var1++;
 if (var1 >= test.length) {
 var1 = 0;
 }

 boolean0 = true;
 } else if (GameKeyboard.isKeyDown(75) {
 var2--;
 if (var2 < 0) {
 var2 = test.length - 1;
 }

 boolean0 = true;
 } else if (GameKeyboard.isKeyDown(77) {
 var2++;
 if (var2 >= test.length) {
 var2 = 0;
 }

 boolean0 = true;
 } else if (GameKeyboard.isKeyDown(71) {
 TARGET_BLEND--;
 if (TARGET_BLEND < 0) {
 TARGET_BLEND = 4;
 }

 boolean0 = true;
 boolean1 = true;
 } else if (GameKeyboard.isKeyDown(73) {
 TARGET_BLEND++;
 if (TARGET_BLEND >= 5) {
 TARGET_BLEND = 0;
 }

 boolean0 = true;
 boolean1 = true;
 } else if (MASKING_ENABLED && GameKeyboard.isKeyDown(82) {
 DEBUG_MASK = !DEBUG_MASK;
 boolean0 = true;
 boolean2 = true;
 } else if (MASKING_ENABLED && GameKeyboard.isKeyDown(80) {
 DEBUG_MASK_AND_PARTICLES = !DEBUG_MASK_AND_PARTICLES;
 boolean0 = true;
 boolean3 = true;
 } else if (!GameKeyboard.isKeyDown(72) && GameKeyboard.isKeyDown(76) {
 MASKING_ENABLED = !MASKING_ENABLED;
 boolean0 = true;
 boolean4 = true;
 }

 if (boolean0) {
 if (boolean1) {
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
 } else if (boolean2) {
 DebugLog.log("DEBUG_MASK = " + DEBUG_MASK);
 } else if (boolean3) {
 DebugLog.log("DEBUG_MASK_AND_PARTICLES = " + DEBUG_MASK_AND_PARTICLES);
 } else if (boolean4) {
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

 public static class PlayerFxMask {
 private WeatherFxMask[] masks;
 int maskPointer = 0;
 bool maskEnabled = false;
 IsoGridSquare plrSquare;
 int DISABLED_MASKS = 0;
 bool requiresUpdate = false;
 bool hasMaskToDraw = true;
 int playerIndex;
 IsoPlayer player;
 int playerZ;
 IWorldRegion curIsoWorldRegion;
 private ArrayList<IWorldRegion> curConnectedRegions = std::make_unique<ArrayList<>>();
 private ArrayList<IWorldRegion> isoWorldRegionTemp = std::make_unique<ArrayList<>>();
 bool DIAMOND_ITER_DONE = false;
 bool isFirstSquare = true;
 IsoGridSquare firstSquare;

 void init() {
 this->masks = new WeatherFxMask[30000];

 for (int int0 = 0; int0 < this->masks.length; int0++) {
 if (this->masks[int0] == nullptr) {
 this->masks[int0] = std::make_unique<WeatherFxMask>();
 }
 }

 this->maskEnabled = true;
 }

 void initMask() {
 if (!GameServer.bServer) {
 if (!this->maskEnabled) {
 this->init();
 }

 this->playerIndex = IsoCamera.frameState.playerIndex;
 this->player = IsoPlayer.players[this->playerIndex];
 this->playerZ = (int)this->player.getZ();
 this->DIAMOND_ITER_DONE = false;
 this->requiresUpdate = false;
 if (this->player != nullptr) {
 if (this->isFirstSquare || this->plrSquare == nullptr || this->plrSquare != this->player.getSquare()) {
 this->plrSquare = this->player.getSquare();
 this->maskPointer = 0;
 this->DISABLED_MASKS = 0;
 this->requiresUpdate = true;
 if (this->firstSquare == nullptr) {
 this->firstSquare = this->plrSquare;
 }

 if (this->firstSquare != nullptr && this->firstSquare != this->plrSquare) {
 this->isFirstSquare = false;
 }
 }

 this->curIsoWorldRegion = this->player.getMasterRegion();
 this->curConnectedRegions.clear();
 if (this->curIsoWorldRegion != nullptr && this->player.getMasterRegion().isFogMask()) {
 this->isoWorldRegionTemp.clear();
 this->isoWorldRegionTemp.add(this->curIsoWorldRegion);

 while (this->isoWorldRegionTemp.size() > 0) {
 IWorldRegion iWorldRegion = this->isoWorldRegionTemp.remove(0);
 this->curConnectedRegions.add(iWorldRegion);
 if (iWorldRegion.getNeighbors().size() != 0) {
 for (IsoWorldRegion worldRegion : iWorldRegion.getNeighbors()) {
 if (!this->isoWorldRegionTemp.contains(worldRegion)
 && !this->curConnectedRegions.contains(worldRegion)
 && worldRegion.isFogMask()) {
 this->isoWorldRegionTemp.add(worldRegion);
 }
 }
 }
 }
 } else {
 this->curIsoWorldRegion = nullptr;
 }
 }

 if (IsoWeatherFX.instance == nullptr) {
 this->hasMaskToDraw = false;
 } else {
 this->hasMaskToDraw = true;
 if (this->hasMaskToDraw) {
 if ((
 this->player.getSquare() == nullptr
 || this->player.getSquare().getBuilding() == nullptr && this->player.getSquare().Is(IsoFlagType.exterior)
 )
 && (this->curIsoWorldRegion == nullptr || !this->curIsoWorldRegion.isFogMask())) {
 this->hasMaskToDraw = false;
 } else {
 this->hasMaskToDraw = true;
 }
 }
 }
 }
 }

 void addMask(int int0, int int1, int int2, IsoGridSquare square, int int3) {
 this->addMask(int0, int1, int2, square, int3, true);
 }

 void addMask(int int0, int int1, int int2, IsoGridSquare square, int int3, bool boolean0) {
 if (this->hasMaskToDraw && this->requiresUpdate) {
 if (!this->maskEnabled) {
 this->init();
 }

 WeatherFxMask weatherFxMask0 = this->getMask(int0, int1, int2);
 if (weatherFxMask0 == nullptr) {
 WeatherFxMask weatherFxMask1 = this->getFreeMask();
 weatherFxMask1.x = int0;
 weatherFxMask1.y = int1;
 weatherFxMask1.z = int2;
 weatherFxMask1.flags = int3;
 weatherFxMask1.gs = square;
 weatherFxMask1.enabled = boolean0;
 if (!boolean0 && this->DISABLED_MASKS < WeatherFxMask.DIAMOND_ROWS) {
 this->DISABLED_MASKS++;
 }
 } else {
 if (weatherFxMask0.flags != int3) {
 weatherFxMask0.flags |= int3;
 }

 if (!weatherFxMask0.enabled && boolean0) {
 WeatherFxMask weatherFxMask2 = this->getFreeMask();
 weatherFxMask2.x = int0;
 weatherFxMask2.y = int1;
 weatherFxMask2.z = int2;
 weatherFxMask2.flags = weatherFxMask0.flags;
 weatherFxMask2.gs = square;
 weatherFxMask2.enabled = boolean0;
 } else {
 weatherFxMask0.enabled = weatherFxMask0.enabled ? weatherFxMask0.enabled : boolean0;
 if (boolean0 && square != nullptr && weatherFxMask0.gs == nullptr) {
 weatherFxMask0.gs = square;
 }
 }
 }
 }
 }

 WeatherFxMask getFreeMask() {
 if (this->maskPointer >= this->masks.length) {
 DebugLog.log("Weather Mask buffer out of bounds. Increasing cache.");
 WeatherFxMask[] weatherFxMasks = this->masks;
 this->masks = new WeatherFxMask[this->masks.length + 10000];

 for (int int0 = 0; int0 < this->masks.length; int0++) {
 if (weatherFxMasks[int0] != nullptr) {
 this->masks[int0] = weatherFxMasks[int0];
 } else {
 this->masks[int0] = std::make_unique<WeatherFxMask>();
 }
 }
 }

 return this->masks[this->maskPointer++];
 }

 bool masksContains(int int0, int int1, int int2) {
 return this->getMask(int0, int1, int2) != nullptr;
 }

 WeatherFxMask getMask(int int2, int int3, int int4) {
 if (this->maskPointer <= 0) {
 return nullptr;
 } else {
 int int0 = this->maskPointer - 1 - (WeatherFxMask.DIAMOND_ROWS + this->DISABLED_MASKS);
 if (int0 < 0) {
 int0 = 0;
 }

 for (int int1 = this->maskPointer - 1; int1 >= int0; int1--) {
 if (this->masks[int1].isLoc(int2, int3, int4) {
 return this->masks[int1];
 }
 }

 return nullptr;
 }
 }
 }
}
} // namespace fx
} // namespace weather
} // namespace iso
} // namespace zombie
