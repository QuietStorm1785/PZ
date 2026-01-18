#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/awt/Rectangle.h"
#include "org/joml/Vector2i.h"
#include "se/krka/kahlua/integration/annotations/LuaMethod.h"
#include "se/krka/kahlua/vm/JavaFunction.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/LuaClosure.h"
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/IndieGL.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaHookManager.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/MovingObjectUpdateScheduler.h"
#include "zombie/ReanimatedPlayers.h"
#include "zombie/SandboxOptions.h"
#include "zombie/VirtualZombieManager.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/ai/astar/Mover.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoSurvivor.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Core.h"
#include "zombie/core/PerformanceSettings.h"
#include "zombie/core/Rand.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/Translator.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/physics/WorldSimulation.h"
#include "zombie/core/profiling/PerformanceProfileProbe.h"
#include "zombie/core/profiling/PerformanceProfileProbeList.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/core/textures/TextureDraw.h"
#include "zombie/core/utils/IntGrid.h"
#include "zombie/core/utils/OnceEvery.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/debug/DebugType.h"
#include "zombie/debug/LineDrawer.h"
#include "zombie/erosion/utils/Noise2D.h"
#include "zombie/gameStates/GameLoadingState.h"
#include "zombie/input/JoypadManager.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/SpriteDetails/IsoObjectType.h"
#include "zombie/iso/areas/BuildingScore.h"
#include "zombie/iso/areas/IsoBuilding.h"
#include "zombie/iso/areas/IsoRoom.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/iso/objects/IsoGenerator.h"
#include "zombie/iso/objects/IsoTree.h"
#include "zombie/iso/objects/IsoWindow.h"
#include "zombie/iso/objects/IsoWorldInventoryObject.h"
#include "zombie/iso/sprite/CorpseFlies.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/iso/sprite/shapers/FloorShaper.h"
#include "zombie/iso/sprite/shapers/FloorShaperAttachedSprites.h"
#include "zombie/iso/sprite/shapers/FloorShaperDiamond.h"
#include "zombie/iso/weather/ClimateManager.h"
#include "zombie/iso/weather/fog/ImprovedFog.h"
#include "zombie/iso/weather/fx/IsoWeatherFX.h"
#include "zombie/iso/weather/fx/WeatherFxMask.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerMap.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/popman/NetworkZombieSimulator.h"
#include "zombie/savefile/ClientPlayerDB.h"
#include "zombie/savefile/PlayerDB.h"
#include "zombie/scripting/objects/VehicleScript.h"
#include "zombie/ui/UIManager.h"
#include "zombie/util/Type.h"
#include "zombie/vehicles/BaseVehicle.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace zombie {
namespace iso {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


/**
 * Loaded area 'reality bubble' around the player(s). Don't confuse this with map cells - the name is a relic from when it did actually represent these. Only one instance should ever exist. Instantiating this class during gameplay will likely immediately crash.
 */
class IsoCell {
public:
 static int MaxHeight = 8;
 static Shader m_floorRenderShader;
 static Shader m_wallRenderShader;
 public ArrayList<IsoGridSquare> Trees = std::make_unique<ArrayList<>>();
 static ArrayList<IsoGridSquare> stchoices = std::make_unique<ArrayList<>>();
 public IsoChunkMap[] ChunkMap = new IsoChunkMap[4];
 public ArrayList<IsoBuilding> BuildingList = std::make_unique<ArrayList<>>();
 private ArrayList<IsoWindow> WindowList = std::make_unique<ArrayList<>>();
 private ArrayList<IsoMovingObject> ObjectList = std::make_unique<ArrayList<>>();
 private ArrayList<IsoPushableObject> PushableObjectList = std::make_unique<ArrayList<>>();
 private HashMap<Integer, BuildingScore> BuildingScores = std::make_unique<HashMap<>>();
 private ArrayList<IsoRoom> RoomList = std::make_unique<ArrayList<>>();
 private ArrayList<IsoObject> StaticUpdaterObjectList = std::make_unique<ArrayList<>>();
 private ArrayList<IsoZombie> ZombieList = std::make_unique<ArrayList<>>();
 private ArrayList<IsoGameCharacter> RemoteSurvivorList = std::make_unique<ArrayList<>>();
 private ArrayList<IsoMovingObject> removeList = std::make_unique<ArrayList<>>();
 private ArrayList<IsoMovingObject> addList = std::make_unique<ArrayList<>>();
 private ArrayList<IsoObject> ProcessIsoObject = std::make_unique<ArrayList<>>();
 private ArrayList<IsoObject> ProcessIsoObjectRemove = std::make_unique<ArrayList<>>();
 private ArrayList<InventoryItem> ProcessItems = std::make_unique<ArrayList<>>();
 private ArrayList<InventoryItem> ProcessItemsRemove = std::make_unique<ArrayList<>>();
 private ArrayList<IsoWorldInventoryObject> ProcessWorldItems = std::make_unique<ArrayList<>>();
 public ArrayList<IsoWorldInventoryObject> ProcessWorldItemsRemove = std::make_unique<ArrayList<>>();
 private IsoGridSquare[][] gridSquares = new IsoGridSquare[4][IsoChunkMap.ChunkWidthInTiles * IsoChunkMap.ChunkWidthInTiles * 8];
 static const bool ENABLE_SQUARE_CACHE = true;
 int height;
 int width;
 int worldX;
 int worldY;
 IntGrid DangerScore;
 bool safeToAdd = true;
 private Stack<IsoLightSource> LamppostPositions = std::make_unique<Stack<>>();
 public ArrayList<IsoRoomLight> roomLights = std::make_unique<ArrayList<>>();
 private ArrayList<IsoHeatSource> heatSources = std::make_unique<ArrayList<>>();
 public ArrayList<BaseVehicle> addVehicles = std::make_unique<ArrayList<>>();
 public ArrayList<BaseVehicle> vehicles = std::make_unique<ArrayList<>>();
 static const int ISOANGLEFACTOR = 3;
 static const int ZOMBIESCANBUDGET = 10;
 static const float NEARESTZOMBIEDISTSQRMAX = 150.0F;
 int zombieScanCursor = 0;
 private IsoZombie[] nearestVisibleZombie = new IsoZombie[4];
 private float[] nearestVisibleZombieDistSqr = new float[4];
 private static Stack<BuildingScore> buildingscores = std::make_unique<Stack<>>();
 static ArrayList<IsoGridSquare> GridStack = nullptr;
 static const int RTF_SolidFloor = 1;
 static const int RTF_VegetationCorpses = 2;
 static const int RTF_MinusFloorCharacters = 4;
 static const int RTF_ShadedFloor = 8;
 static const int RTF_Shadows = 16;
 private static ArrayList<IsoGridSquare> ShadowSquares = new ArrayList<>(1000);
 private static ArrayList<IsoGridSquare> MinusFloorCharacters = new ArrayList<>(1000);
 private static ArrayList<IsoGridSquare> SolidFloor = new ArrayList<>(5000);
 private static ArrayList<IsoGridSquare> ShadedFloor = new ArrayList<>(5000);
 private static ArrayList<IsoGridSquare> VegetationCorpses = new ArrayList<>(5000);
 public static IsoCell.PerPlayerRender[] perPlayerRender = new IsoCell.PerPlayerRender[4];
 private int[] StencilXY = new int[]{0, 0, -1, 0, 0, -1, -1, -1, -2, -1, -1, -2, -2, -2, -3, -2, -2, -3, -3, -3};
 private int[] StencilXY2z = new int[]{
 0, 0, -1, 0, 0, -1, -1, -1, -2, -1, -1, -2, -2, -2, -3, -2, -2, -3, -3, -3, -4, -3, -3, -4, -4, -4, -5, -4, -4, -5, -5, -5, -6, -5, -5, -6, -6, -6
 };
 int StencilX1;
 int StencilY1;
 int StencilX2;
 int StencilY2;
 Texture m_stencilTexture = nullptr;
 const DiamondMatrixIterator diamondMatrixIterator = new DiamondMatrixIterator(123);
 const Vector2i diamondMatrixPos = new Vector2i();
 int DeferredCharacterTick = 0;
 bool hasSetupSnowGrid = false;
 private IsoCell.SnowGridTiles snowGridTiles_Square;
 private IsoCell.SnowGridTiles[] snowGridTiles_Strip;
 private IsoCell.SnowGridTiles[] snowGridTiles_Edge;
 private IsoCell.SnowGridTiles[] snowGridTiles_Cove;
 private IsoCell.SnowGridTiles snowGridTiles_Enclosed;
 int m_snowFirstNonSquare = -1;
 Noise2D snowNoise2D = new Noise2D();
 private IsoCell.SnowGrid snowGridCur;
 private IsoCell.SnowGrid snowGridPrev;
 int snowFracTarget = 0;
 long snowFadeTime = 0L;
 float snowTransitionTime = 5000.0F;
 int raport = 0;
 static const int SNOWSHORE_NONE = 0;
 static const int SNOWSHORE_N = 1;
 static const int SNOWSHORE_E = 2;
 static const int SNOWSHORE_S = 4;
 static const int SNOWSHORE_W = 8;
 bool recalcFloors = false;
 static int wx;
 static int wy;
 KahluaTable[] drag = new KahluaTable[4];
 ArrayList<IsoSurvivor> SurvivorList = std::make_unique<ArrayList<>>();
 static Texture texWhite;
 static IsoCell instance;
 int currentLX = 0;
 int currentLY = 0;
 int currentLZ = 0;
 int recalcShading = 30;
 int lastMinX = -1234567;
 int lastMinY = -1234567;
 float rainScroll;
 private int[] rainX = new int[4];
 private int[] rainY = new int[4];
 private Texture[] rainTextures = new Texture[5];
 private long[] rainFileTime = new long[5];
 float rainAlphaMax = 0.6F;
 private float[] rainAlpha = new float[4];
 int rainIntensity = 0;
 int rainSpeed = 6;
 int lightUpdateCount = 11;
 bool bRendering = false;
 boolean[] bHideFloors = new boolean[4];
 int[] unhideFloorsCounter = new int[4];
 bool bOccludedByOrphanStructureFlag = false;
 int playerPeekedRoomId = -1;
 ArrayList<ArrayList<IsoBuilding>> playerOccluderBuildings = new ArrayList<>(4);
 IsoBuilding[][] playerOccluderBuildingsArr = new IsoBuilding[4][];
 int[] playerWindowPeekingRoomId = new int[4];
 boolean[] playerHidesOrphanStructures = new boolean[4];
 boolean[] playerCutawaysDirty = new boolean[4];
 const Vector2 tempCutawaySqrVector = new Vector2();
 ArrayList<Integer> tempPrevPlayerCutawayRoomIDs = std::make_unique<ArrayList<>>();
 ArrayList<Integer> tempPlayerCutawayRoomIDs = std::make_unique<ArrayList<>>();
 IsoGridSquare[] lastPlayerSquare = new IsoGridSquare[4];
 boolean[] lastPlayerSquareHalf = new boolean[4];
 IsoDirections[] lastPlayerDir = new IsoDirections[4];
 Vector2[] lastPlayerAngle = new Vector2[4];
 int hidesOrphanStructuresAbove = MaxHeight;
 const Rectangle buildingRectTemp = new Rectangle();
 ArrayList<ArrayList<IsoBuilding>> zombieOccluderBuildings = new ArrayList<>(4);
 IsoBuilding[][] zombieOccluderBuildingsArr = new IsoBuilding[4][];
 IsoGridSquare[] lastZombieSquare = new IsoGridSquare[4];
 boolean[] lastZombieSquareHalf = new boolean[4];
 ArrayList<ArrayList<IsoBuilding>> otherOccluderBuildings = new ArrayList<>(4);
 IsoBuilding[][] otherOccluderBuildingsArr = new IsoBuilding[4][];
 const int mustSeeSquaresRadius = 4;
 const int mustSeeSquaresGridSize = 10;
 ArrayList<IsoGridSquare> gridSquaresTempLeft = new ArrayList<>(100);
 ArrayList<IsoGridSquare> gridSquaresTempRight = new ArrayList<>(100);
 IsoWeatherFX weatherFX;
 int minX;
 int maxX;
 int minY;
 int maxY;
 int minZ;
 int maxZ;
 OnceEvery dangerUpdate = new OnceEvery(0.4F, false);
 Thread LightInfoUpdate = nullptr;
 private Stack<IsoRoom> SpottedRooms = std::make_unique<Stack<>>();
 IsoZombie fakeZombieForHit;

 /**
 * @return the MaxHeight
 */
 static int getMaxHeight() {
 return MaxHeight;
 }

 LotHeader getCurrentLotHeader() {
 IsoChunk chunk = this->getChunkForGridSquare((int)IsoCamera.CamCharacter.x, (int)IsoCamera.CamCharacter.y, (int)IsoCamera.CamCharacter.z);
 return chunk.lotheader;
 }

 IsoChunkMap getChunkMap(int pl) {
 return this->ChunkMap[pl];
 }

 IsoGridSquare getFreeTile(RoomDef def) {
 stchoices.clear();

 for (int int0 = 0; int0 < def.rects.size(); int0++) {
 RoomDef.RoomRect roomRect = def.rects.get(int0);

 for (int int1 = roomRect.x; int1 < roomRect.x + roomRect.w; int1++) {
 for (int int2 = roomRect.y; int2 < roomRect.y + roomRect.h; int2++) {
 IsoGridSquare square0 = this->getGridSquare(int1, int2, def.level);
 if (square0 != nullptr) {
 square0.setCachedIsFree(false);
 square0.setCacheIsFree(false);
 if (square0.isFree(false) {
 stchoices.add(square0);
 }
 }
 }
 }
 }

 if (stchoices.empty()) {
 return nullptr;
 } else {
 IsoGridSquare square1 = stchoices.get(Rand.Next(stchoices.size()));
 stchoices.clear();
 return square1;
 }
 }

 /**
 * @return the getBuildings
 */
 public static Stack<BuildingScore> getBuildings() {
 return buildingscores;
 }

 static void setBuildings(Stack<BuildingScore> scores) {
 buildingscores = scores;
 }

 IsoZombie getNearestVisibleZombie(int playerIndex) {
 return this->nearestVisibleZombie[playerIndex];
 }

 IsoChunk getChunkForGridSquare(int x, int y, int z) {
 int int0 = x;
 int int1 = y;

 for (int int2 = 0; int2 < IsoPlayer.numPlayers; int2++) {
 if (!this->ChunkMap[int2].ignore) {
 x = int0 - this->ChunkMap[int2].getWorldXMinTiles();
 y = int1 - this->ChunkMap[int2].getWorldYMinTiles();
 if (x >= 0 && y >= 0) {
 IsoChunkMap chunkMap = this->ChunkMap[int2];
 x /= 10;
 chunkMap = this->ChunkMap[int2];
 y /= 10;
 IsoChunk chunk = nullptr;
 chunk = this->ChunkMap[int2].getChunk(x, y);
 if (chunk != nullptr) {
 return chunk;
 }
 }
 }
 }

 return nullptr;
 }

 IsoChunk getChunk(int _wx, int _wy) {
 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 IsoChunkMap chunkMap = this->ChunkMap[int0];
 if (!chunkMap.ignore) {
 IsoChunk chunk = chunkMap.getChunk(_wx - chunkMap.getWorldXMin(), _wy - chunkMap.getWorldYMin());
 if (chunk != nullptr) {
 return chunk;
 }
 }
 }

 return nullptr;
 }

 public IsoCell(int _width, int _height) {
 IsoWorld.instance.CurrentCell = this;
 instance = this;
 this->width = _width;
 this->height = _height;

 for (int int0 = 0; int0 < 4; int0++) {
 this->ChunkMap[int0] = new IsoChunkMap(this);
 this->ChunkMap[int0].PlayerID = int0;
 this->ChunkMap[int0].ignore = int0 > 0;
 this->playerOccluderBuildings.add(new ArrayList<>(5);
 this->zombieOccluderBuildings.add(new ArrayList<>(5);
 this->otherOccluderBuildings.add(new ArrayList<>(5);
 }

 WorldReuserThread.instance.run();
 }

 short getStencilValue(int x, int y, int z) {
 short[][][] shorts0 = perPlayerRender[IsoCamera.frameState.playerIndex].StencilValues;
 int int0 = 0;
 int int1 = 0;

 for (byte byte0 = 0; byte0 < this->StencilXY.length; byte0 += 2) {
 int int2 = -z * 3;
 int int3 = x + int2 + this->StencilXY[byte0];
 int int4 = y + int2 + this->StencilXY[byte0 + 1];
 if (int3 >= this->minX && int3 < this->maxX && int4 >= this->minY && int4 < this->maxY) {
 short[] shorts1 = shorts0[int3 - this->minX][int4 - this->minY];
 if (shorts1[0] != 0) {
 if (int0 == 0) {
 int0 = shorts1[0];
 int1 = shorts1[1];
 } else {
 int0 = Math.min(shorts1[0], int0);
 int1 = Math.max(shorts1[1], int1);
 }
 }
 }
 }

 if (int0 == 0) {
 return 1;
 } else {
 return int0 > 10 ? (short)(int0 - 10) : (short)(int1 + 1);
 }
 }

 void setStencilValue(int x, int y, int z, int stencil) {
 short[][][] shorts0 = perPlayerRender[IsoCamera.frameState.playerIndex].StencilValues;

 for (byte byte0 = 0; byte0 < this->StencilXY.length; byte0 += 2) {
 int int0 = -z * 3;
 int int1 = x + int0 + this->StencilXY[byte0];
 int int2 = y + int0 + this->StencilXY[byte0 + 1];
 if (int1 >= this->minX && int1 < this->maxX && int2 >= this->minY && int2 < this->maxY) {
 short[] shorts1 = shorts0[int1 - this->minX][int2 - this->minY];
 if (shorts1[0] == 0) {
 shorts1[0] = (short)stencil;
 shorts1[1] = (short)stencil;
 } else {
 shorts1[0] = (short)Math.min(shorts1[0], stencil);
 shorts1[1] = (short)Math.max(shorts1[1], stencil);
 }
 }
 }
 }

 short getStencilValue2z(int x, int y, int z) {
 short[][][] shorts0 = perPlayerRender[IsoCamera.frameState.playerIndex].StencilValues;
 int int0 = 0;
 int int1 = 0;
 int int2 = -z * 3;

 for (byte byte0 = 0; byte0 < this->StencilXY2z.length; byte0 += 2) {
 int int3 = x + int2 + this->StencilXY2z[byte0];
 int int4 = y + int2 + this->StencilXY2z[byte0 + 1];
 if (int3 >= this->minX && int3 < this->maxX && int4 >= this->minY && int4 < this->maxY) {
 short[] shorts1 = shorts0[int3 - this->minX][int4 - this->minY];
 if (shorts1[0] != 0) {
 if (int0 == 0) {
 int0 = shorts1[0];
 int1 = shorts1[1];
 } else {
 int0 = Math.min(shorts1[0], int0);
 int1 = Math.max(shorts1[1], int1);
 }
 }
 }
 }

 if (int0 == 0) {
 return 1;
 } else {
 return int0 > 10 ? (short)(int0 - 10) : (short)(int1 + 1);
 }
 }

 void setStencilValue2z(int x, int y, int z, int stencil) {
 short[][][] shorts0 = perPlayerRender[IsoCamera.frameState.playerIndex].StencilValues;
 int int0 = -z * 3;

 for (byte byte0 = 0; byte0 < this->StencilXY2z.length; byte0 += 2) {
 int int1 = x + int0 + this->StencilXY2z[byte0];
 int int2 = y + int0 + this->StencilXY2z[byte0 + 1];
 if (int1 >= this->minX && int1 < this->maxX && int2 >= this->minY && int2 < this->maxY) {
 short[] shorts1 = shorts0[int1 - this->minX][int2 - this->minY];
 if (shorts1[0] == 0) {
 shorts1[0] = (short)stencil;
 shorts1[1] = (short)stencil;
 } else {
 shorts1[0] = (short)Math.min(shorts1[0], stencil);
 shorts1[1] = (short)Math.max(shorts1[1], stencil);
 }
 }
 }
 }

 void CalculateVertColoursForTile(IsoGridSquare sqThis, int x, int y, int zz, int playerIndex) {
 IsoGridSquare square0 = !IsoGridSquare.getMatrixBit(sqThis.visionMatrix, 0, 0, 1) ? sqThis.nav[IsoDirections.NW.index()] : nullptr;
 IsoGridSquare square1 = !IsoGridSquare.getMatrixBit(sqThis.visionMatrix, 1, 0, 1) ? sqThis.nav[IsoDirections.N.index()] : nullptr;
 IsoGridSquare square2 = !IsoGridSquare.getMatrixBit(sqThis.visionMatrix, 2, 0, 1) ? sqThis.nav[IsoDirections.NE.index()] : nullptr;
 IsoGridSquare square3 = !IsoGridSquare.getMatrixBit(sqThis.visionMatrix, 2, 1, 1) ? sqThis.nav[IsoDirections.E.index()] : nullptr;
 IsoGridSquare square4 = !IsoGridSquare.getMatrixBit(sqThis.visionMatrix, 2, 2, 1) ? sqThis.nav[IsoDirections.SE.index()] : nullptr;
 IsoGridSquare square5 = !IsoGridSquare.getMatrixBit(sqThis.visionMatrix, 1, 2, 1) ? sqThis.nav[IsoDirections.S.index()] : nullptr;
 IsoGridSquare square6 = !IsoGridSquare.getMatrixBit(sqThis.visionMatrix, 0, 2, 1) ? sqThis.nav[IsoDirections.SW.index()] : nullptr;
 IsoGridSquare square7 = !IsoGridSquare.getMatrixBit(sqThis.visionMatrix, 0, 1, 1) ? sqThis.nav[IsoDirections.W.index()] : nullptr;
 this->CalculateColor(square0, square1, square7, sqThis, 0, playerIndex);
 this->CalculateColor(square1, square2, square3, sqThis, 1, playerIndex);
 this->CalculateColor(square4, square5, square3, sqThis, 2, playerIndex);
 this->CalculateColor(square6, square5, square7, sqThis, 3, playerIndex);
 }

 Texture getStencilTexture() {
 if (this->m_stencilTexture.empty()) {
 this->m_stencilTexture = Texture.getSharedTexture("media/mask_circledithernew.png");
 }

 return this->m_stencilTexture;
 }

 void DrawStencilMask() {
 Texture texture = this->getStencilTexture();
 if (texture != nullptr) {
 IndieGL.glStencilMask(255);
 IndieGL.glClear(1280);
 int int0 = IsoCamera.getOffscreenWidth(IsoPlayer.getPlayerIndex()) / 2;
 int int1 = IsoCamera.getOffscreenHeight(IsoPlayer.getPlayerIndex()) / 2;
 int0 -= texture.getWidth() / (2 / Core.TileScale);
 int1 -= texture.getHeight() / (2 / Core.TileScale);
 IndieGL.enableStencilTest();
 IndieGL.enableAlphaTest();
 IndieGL.glAlphaFunc(516, 0.1F);
 IndieGL.glStencilFunc(519, 128, 255);
 IndieGL.glStencilOp(7680, 7680, 7681);
 IndieGL.glColorMask(false, false, false, false);
 texture.renderstrip(
 int0 - (int)IsoCamera.getRightClickOffX(),
 int1 - (int)IsoCamera.getRightClickOffY(),
 texture.getWidth() * Core.TileScale,
 texture.getHeight() * Core.TileScale,
 1.0F,
 1.0F,
 1.0F,
 1.0F,
 nullptr
 );
 IndieGL.glColorMask(true, true, true, true);
 IndieGL.glStencilFunc(519, 0, 255);
 IndieGL.glStencilOp(7680, 7680, 7680);
 IndieGL.glStencilMask(127);
 IndieGL.glAlphaFunc(519, 0.0F);
 this->StencilX1 = int0 - (int)IsoCamera.getRightClickOffX();
 this->StencilY1 = int1 - (int)IsoCamera.getRightClickOffY();
 this->StencilX2 = this->StencilX1 + texture.getWidth() * Core.TileScale;
 this->StencilY2 = this->StencilY1 + texture.getHeight() * Core.TileScale;
 }
 }

 void RenderTiles(int _MaxHeight) {
 IsoCell.s_performance.isoCellRenderTiles.invokeAndMeasure(this, _MaxHeight, IsoCell::renderTilesInternal);
 }

 void renderTilesInternal(int int1) {
 if (DebugOptions.instance.Terrain.RenderTiles.Enable.getValue()) {
 if (m_floorRenderShader.empty()) {
 RenderThread.invokeOnRenderContext(this::initTileShaders);
 }

 int int0 = IsoCamera.frameState.playerIndex;
 IsoPlayer player = IsoPlayer.players[int0];
 player.dirtyRecalcGridStackTime = player.dirtyRecalcGridStackTime - GameTime.getInstance().getMultiplier() / 4.0F;
 IsoCell.PerPlayerRender perPlayerRenderx = this->getPerPlayerRenderAt(int0);
 perPlayerRenderx.setSize(this->maxX - this->minX + 1, this->maxY - this->minY + 1);
 long long0 = System.currentTimeMillis();
 if (this->minX != perPlayerRenderx.minX
 || this->minY != perPlayerRenderx.minY
 || this->maxX != perPlayerRenderx.maxX
 || this->maxY != perPlayerRenderx.maxY) {
 perPlayerRenderx.minX = this->minX;
 perPlayerRenderx.minY = this->minY;
 perPlayerRenderx.maxX = this->maxX;
 perPlayerRenderx.maxY = this->maxY;
 player.dirtyRecalcGridStack = true;
 WeatherFxMask.forceMaskUpdate(int0);
 }

 IsoCell.s_performance.renderTiles.recalculateAnyGridStacks.start();
 bool boolean0 = player.dirtyRecalcGridStack;
 this->recalculateAnyGridStacks(perPlayerRenderx, (int)int1, int0, long0);
 IsoCell.s_performance.renderTiles.recalculateAnyGridStacks.end();
 this->DeferredCharacterTick++;
 IsoCell.s_performance.renderTiles.flattenAnyFoliage.start();
 this->flattenAnyFoliage(perPlayerRenderx, int0);
 IsoCell.s_performance.renderTiles.flattenAnyFoliage.end();
 if (this->SetCutawayRoomsForPlayer() || boolean0) {
 IsoGridStack gridStack = perPlayerRenderx.GridStacks;

 for (int int2 = 0; int2 < int1 + 1; int2++) {
 GridStack = gridStack.Squares.get(int2);

 for (int int3 = 0; int3 < GridStack.size(); int3++) {
 IsoGridSquare square = GridStack.get(int3);
 square.setPlayerCutawayFlag(int0, this->IsCutawaySquare(square, long0), long0);
 }
 }
 }

 IsoCell.s_performance.renderTiles.performRenderTiles.start();
 this->performRenderTiles(perPlayerRenderx, (int)int1, int0, long0);
 IsoCell.s_performance.renderTiles.performRenderTiles.end();
 this->playerCutawaysDirty[int0] = false;
 ShadowSquares.clear();
 MinusFloorCharacters.clear();
 ShadedFloor.clear();
 SolidFloor.clear();
 VegetationCorpses.clear();
 IsoCell.s_performance.renderTiles.renderDebugPhysics.start();
 this->renderDebugPhysics(int0);
 IsoCell.s_performance.renderTiles.renderDebugPhysics.end();
 IsoCell.s_performance.renderTiles.renderDebugLighting.start();
 this->renderDebugLighting(perPlayerRenderx, (int)int1);
 IsoCell.s_performance.renderTiles.renderDebugLighting.end();
 }
 }

 void initTileShaders() {
 if (DebugLog.isEnabled(DebugType.Shader) {
 DebugLog.Shader.debugln("Loading shader: \"floorTile\"");
 }

 m_floorRenderShader = new Shader("floorTile");
 if (DebugLog.isEnabled(DebugType.Shader) {
 DebugLog.Shader.debugln("Loading shader: \"wallTile\"");
 }

 m_wallRenderShader = new Shader("wallTile");
 }

 private IsoCell.PerPlayerRender getPerPlayerRenderAt(int int0) {
 if (perPlayerRender[int0] == nullptr) {
 perPlayerRender[int0] = new IsoCell.PerPlayerRender();
 }

 return perPlayerRender[int0];
 }

 void recalculateAnyGridStacks(IsoCell.PerPlayerRender perPlayerRenderx, int int5, int int0, long long0) {
 IsoPlayer player = IsoPlayer.players[int0];
 if (player.dirtyRecalcGridStack) {
 player.dirtyRecalcGridStack = false;
 IsoGridStack gridStack = perPlayerRenderx.GridStacks;
 boolean[][][] booleans0 = perPlayerRenderx.VisiOccludedFlags;
 boolean[][] booleans1 = perPlayerRenderx.VisiCulledFlags;
 int int1 = -1;
 int int2 = -1;
 int int3 = -1;
 WeatherFxMask.setDiamondIterDone(int0);

 for (int int4 = int5; int4 >= 0; int4--) {
 GridStack = gridStack.Squares.get(int4);
 GridStack.clear();
 if (int4 < this->maxZ) {
 if (DebugOptions.instance.Terrain.RenderTiles.NewRender.getValue()) {
 DiamondMatrixIterator diamondMatrixIteratorx = this->diamondMatrixIterator.reset(this->maxX - this->minX);
 IsoGridSquare square0 = nullptr;
 Vector2i vector2i = this->diamondMatrixPos;

 while (diamondMatrixIteratorx.next(vector2i) {
 if (vector2i.y < this->maxY - this->minY + 1) {
 square0 = this->ChunkMap[int0].getGridSquare(vector2i.x + this->minX, vector2i.y + this->minY, int4);
 if (int4 == 0) {
 booleans0[vector2i.x][vector2i.y][0] = false;
 booleans0[vector2i.x][vector2i.y][1] = false;
 booleans1[vector2i.x][vector2i.y] = false;
 }

 if (square0.empty()) {
 WeatherFxMask.addMaskLocation(nullptr, vector2i.x + this->minX, vector2i.y + this->minY, int4);
 } else {
 IsoChunk chunk0 = square0.getChunk();
 if (chunk0 != nullptr && square0.IsOnScreen(true) {
 WeatherFxMask.addMaskLocation(square0, vector2i.x + this->minX, vector2i.y + this->minY, int4);
 bool boolean0 = this->IsDissolvedSquare(square0, int0);
 square0.setIsDissolved(int0, boolean0, long0);
 if (!square0.getIsDissolved(int0, long0) {
 square0.cacheLightInfo();
 GridStack.add(square0);
 }
 }
 }
 }
 }
 } else {
 for (int int6 = this->minY; int6 < this->maxY; int6++) {
 int int7 = this->minX;
 IsoGridSquare square1 = this->ChunkMap[int0].getGridSquare(int7, int6, int4);
 int int8 = IsoDirections.E.index();

 while (int7 < this->maxX) {
 if (int4 == 0) {
 booleans0[int7 - this->minX][int6 - this->minY][0] = false;
 booleans0[int7 - this->minX][int6 - this->minY][1] = false;
 booleans1[int7 - this->minX][int6 - this->minY] = false;
 }

 if (square1 != nullptr && square1.getY() != int6) {
 square1 = nullptr;
 }

 uint8_t byte0 = -1;
 uint8_t byte1 = -1;
 IsoChunkMap chunkMap0 = this->ChunkMap[int0];
 int int9 = this->ChunkMap[int0].WorldX - IsoChunkMap.ChunkGridWidth / 2;
 chunkMap0 = this->ChunkMap[int0];
 int int10 = int7 - int9 * 10;
 chunkMap0 = this->ChunkMap[int0];
 int9 = this->ChunkMap[int0].WorldY - IsoChunkMap.ChunkGridWidth / 2;
 chunkMap0 = this->ChunkMap[int0];
 int int11 = int6 - int9 * 10;
 IsoChunkMap chunkMap1 = this->ChunkMap[int0];
 int10 /= 10;
 IsoChunkMap chunkMap2 = this->ChunkMap[int0];
 int11 /= 10;
 if (int10 != int1 || int11 != int2) {
 IsoChunk chunk1 = this->ChunkMap[int0].getChunkForGridSquare(int7, int6);
 if (chunk1 != nullptr) {
 int3 = chunk1.maxLevel;
 }
 }

 int1 = int10;
 int2 = int11;
 if (int3 < int4) {
 int7++;
 } else {
 if (square1.empty()) {
 square1 = this->getGridSquare(int7, int6, int4);
 if (square1.empty()) {
 square1 = this->ChunkMap[int0].getGridSquare(int7, int6, int4);
 if (square1.empty()) {
 int7++;
 continue;
 }
 }
 }

 IsoChunk chunk2 = square1.getChunk();
 if (chunk2 != nullptr && square1.IsOnScreen(true) {
 WeatherFxMask.addMaskLocation(square1, square1.x, square1.y, int4);
 bool boolean1 = this->IsDissolvedSquare(square1, int0);
 square1.setIsDissolved(int0, boolean1, long0);
 if (!square1.getIsDissolved(int0, long0) {
 square1.cacheLightInfo();
 GridStack.add(square1);
 }
 }

 square1 = square1.nav[int8];
 int7++;
 }
 }
 }
 }
 }
 }

 this->CullFullyOccludedSquares(gridStack, booleans0, booleans1);
 }
 }

 void flattenAnyFoliage(IsoCell.PerPlayerRender perPlayerRenderx, int int3) {
 short[][][] shorts = perPlayerRenderx.StencilValues;
 boolean[][] booleans = perPlayerRenderx.FlattenGrassEtc;

 for (int int0 = this->minY; int0 <= this->maxY; int0++) {
 for (int int1 = this->minX; int1 <= this->maxX; int1++) {
 shorts[int1 - this->minX][int0 - this->minY][0] = 0;
 shorts[int1 - this->minX][int0 - this->minY][1] = 0;
 booleans[int1 - this->minX][int0 - this->minY] = false;
 }
 }

 for (int int2 = 0; int2 < this->vehicles.size(); int2++) {
 BaseVehicle vehicle = this->vehicles.get(int2);
 if (!(vehicle.getAlpha(int3) <= 0.0F) {
 for (int int4 = -2; int4 < 5; int4++) {
 for (int int5 = -2; int5 < 5; int5++) {
 int int6 = (int)vehicle.x + int5;
 int int7 = (int)vehicle.y + int4;
 if (int6 >= this->minX && int6 <= this->maxX && int7 >= this->minY && int7 <= this->maxY) {
 booleans[int6 - this->minX][int7 - this->minY] = true;
 }
 }
 }
 }
 }
 }

 void performRenderTiles(IsoCell.PerPlayerRender perPlayerRenderx, int int1, int int3, long long0) {
 IsoGridStack gridStack = perPlayerRenderx.GridStacks;
 boolean[][] booleans = perPlayerRenderx.FlattenGrassEtc;
 Shader shader0;
 Shader shader1;
 if (Core.bDebug && !DebugOptions.instance.Terrain.RenderTiles.UseShaders.getValue()) {
 shader0 = nullptr;
 shader1 = nullptr;
 } else {
 shader0 = m_floorRenderShader;
 shader1 = m_wallRenderShader;
 }

 for (int int0 = 0; int0 < int1 + 1; int0++) {
 IsoCell.s_performance.renderTiles.PperformRenderTilesLayer pperformRenderTilesLayer = IsoCell.s_performance.renderTiles.performRenderTilesLayers
 .start(int0);
 GridStack = gridStack.Squares.get(int0);
 ShadowSquares.clear();
 SolidFloor.clear();
 ShadedFloor.clear();
 VegetationCorpses.clear();
 MinusFloorCharacters.clear();
 IndieGL.glClear(256);
 if (int0 == 0 && DebugOptions.instance.Terrain.RenderTiles.Water.getValue() && DebugOptions.instance.Terrain.RenderTiles.WaterBody.getValue()) {
 pperformRenderTilesLayer.renderIsoWater.start();
 IsoWater.getInstance().render(GridStack, false);
 pperformRenderTilesLayer.renderIsoWater.end();
 }

 pperformRenderTilesLayer.renderFloor.start();

 for (int int2 = 0; int2 < GridStack.size(); int2++) {
 IsoGridSquare square0 = GridStack.get(int2);
 if (square0.chunk.empty() || !square0.chunk.bLightingNeverDone[int3]) {
 square0.bFlattenGrassEtc = int0 == 0 && booleans[square0.x - this->minX][square0.y - this->minY];
 int int4 = square0.renderFloor(shader0);
 if (!square0.getStaticMovingObjects().empty()) {
 int4 |= 2;
 int4 |= 16;
 if (square0.HasStairs()) {
 int4 |= 4;
 }
 }

 if (!square0.getWorldObjects().empty()) {
 int4 |= 2;
 }

 if (!square0.getLocalTemporaryObjects().empty()) {
 int4 |= 4;
 }

 for (int int5 = 0; int5 < square0.getMovingObjects().size(); int5++) {
 IsoMovingObject movingObject = square0.getMovingObjects().get(int5);
 bool boolean0 = movingObject.bOnFloor;
 if (boolean0 && movingObject instanceof IsoZombie zombie0) {
 boolean0 = zombie0.isProne();
 if (!BaseVehicle.RENDER_TO_TEXTURE) {
 boolean0 = false;
 }
 }

 if (boolean0) {
 int4 |= 2;
 } else {
 int4 |= 4;
 }

 int4 |= 16;
 }

 if (!square0.getDeferedCharacters().empty()) {
 int4 |= 4;
 }

 if (square0.hasFlies()) {
 int4 |= 4;
 }

 if ((int4 & 1) != 0) {
 SolidFloor.add(square0);
 }

 if ((int4 & 8) != 0) {
 ShadedFloor.add(square0);
 }

 if ((int4 & 2) != 0) {
 VegetationCorpses.add(square0);
 }

 if ((int4 & 4) != 0) {
 MinusFloorCharacters.add(square0);
 }

 if ((int4 & 16) != 0) {
 ShadowSquares.add(square0);
 }
 }
 }

 pperformRenderTilesLayer.renderFloor.end();
 pperformRenderTilesLayer.renderPuddles.start();
 IsoPuddles.getInstance().render(SolidFloor, int0);
 pperformRenderTilesLayer.renderPuddles.end();
 if (int0 == 0 && DebugOptions.instance.Terrain.RenderTiles.Water.getValue() && DebugOptions.instance.Terrain.RenderTiles.WaterShore.getValue()) {
 pperformRenderTilesLayer.renderShore.start();
 IsoWater.getInstance().render(nullptr, true);
 pperformRenderTilesLayer.renderShore.end();
 }

 if (!SolidFloor.empty()) {
 pperformRenderTilesLayer.renderSnow.start();
 this->RenderSnow(int0);
 pperformRenderTilesLayer.renderSnow.end();
 }

 if (!GridStack.empty()) {
 pperformRenderTilesLayer.renderBlood.start();
 this->ChunkMap[int3].renderBloodForChunks(int0);
 pperformRenderTilesLayer.renderBlood.end();
 }

 if (!ShadedFloor.empty()) {
 pperformRenderTilesLayer.renderFloorShading.start();
 this->RenderFloorShading(int0);
 pperformRenderTilesLayer.renderFloorShading.end();
 }

 WorldMarkers.instance.renderGridSquareMarkers(perPlayerRenderx, int0, int3);
 if (DebugOptions.instance.Terrain.RenderTiles.Shadows.getValue()) {
 pperformRenderTilesLayer.renderShadows.start();
 this->renderShadows();
 pperformRenderTilesLayer.renderShadows.end();
 }

 if (DebugOptions.instance.Terrain.RenderTiles.Lua.getValue()) {
 pperformRenderTilesLayer.luaOnPostFloorLayerDraw.start();
 LuaEventManager.triggerEvent("OnPostFloorLayerDraw", int0);
 pperformRenderTilesLayer.luaOnPostFloorLayerDraw.end();
 }

 IsoMarkers.instance.renderIsoMarkers(perPlayerRenderx, int0, int3);
 IsoMarkers.instance.renderCircleIsoMarkers(perPlayerRenderx, int0, int3);
 if (DebugOptions.instance.Terrain.RenderTiles.VegetationCorpses.getValue()) {
 pperformRenderTilesLayer.vegetationCorpses.start();

 for (int int6 = 0; int6 < VegetationCorpses.size(); int6++) {
 IsoGridSquare square1 = VegetationCorpses.get(int6);
 square1.renderMinusFloor(this->maxZ, false, true, false, false, false, shader1);
 square1.renderCharacters(this->maxZ, true, true);
 }

 pperformRenderTilesLayer.vegetationCorpses.end();
 }

 ImprovedFog.startRender(int3, int0);
 if (DebugOptions.instance.Terrain.RenderTiles.MinusFloorCharacters.getValue()) {
 pperformRenderTilesLayer.minusFloorCharacters.start();

 for (int int7 = 0; int7 < MinusFloorCharacters.size(); int7++) {
 IsoGridSquare square2 = MinusFloorCharacters.get(int7);
 IsoGridSquare square3 = square2.nav[IsoDirections.S.index()];
 IsoGridSquare square4 = square2.nav[IsoDirections.E.index()];
 bool boolean1 = square3 != nullptr && square3.getPlayerCutawayFlag(int3, long0);
 bool boolean2 = square2.getPlayerCutawayFlag(int3, long0);
 bool boolean3 = square4 != nullptr && square4.getPlayerCutawayFlag(int3, long0);
 this->currentLY = square2.getY() - this->minY;
 this->currentLZ = int0;
 ImprovedFog.renderRowsBehind(square2);
 bool boolean4 = square2.renderMinusFloor(this->maxZ, false, false, boolean1, boolean2, boolean3, shader1);
 square2.renderDeferredCharacters(this->maxZ);
 square2.renderCharacters(this->maxZ, false, true);
 if (square2.hasFlies()) {
 CorpseFlies.render(square2.x, square2.y, square2.z);
 }

 if (boolean4) {
 square2.renderMinusFloor(this->maxZ, true, false, boolean1, boolean2, boolean3, shader1);
 }
 }

 pperformRenderTilesLayer.minusFloorCharacters.end();
 }

 IsoMarkers.instance.renderIsoMarkersDeferred(perPlayerRenderx, int0, int3);
 ImprovedFog.endRender();
 pperformRenderTilesLayer.end();
 }
 }

 void renderShadows() {
 bool boolean0 = Core.getInstance().getOptionCorpseShadows();

 for (int int0 = 0; int0 < ShadowSquares.size(); int0++) {
 IsoGridSquare square = ShadowSquares.get(int0);

 for (int int1 = 0; int1 < square.getMovingObjects().size(); int1++) {
 IsoMovingObject movingObject0 = square.getMovingObjects().get(int1);
 IsoGameCharacter character = Type.tryCastTo(movingObject0, IsoGameCharacter.class);
 if (character != nullptr) {
 character.renderShadow(character.getX(), character.getY(), character.getZ());
 } else {
 BaseVehicle vehicle = Type.tryCastTo(movingObject0, BaseVehicle.class);
 if (vehicle != nullptr) {
 vehicle.renderShadow();
 }
 }
 }

 if (boolean0) {
 for (int int2 = 0; int2 < square.getStaticMovingObjects().size(); int2++) {
 IsoMovingObject movingObject1 = square.getStaticMovingObjects().get(int2);
 IsoDeadBody deadBody = Type.tryCastTo(movingObject1, IsoDeadBody.class);
 if (deadBody != nullptr) {
 deadBody.renderShadow();
 }
 }
 }
 }
 }

 void renderDebugPhysics(int int0) {
 if (Core.bDebug && DebugOptions.instance.PhysicsRender.getValue()) {
 TextureDraw.GenericDrawer genericDrawer = WorldSimulation.getDrawer(int0);
 SpriteRenderer.instance.drawGeneric(genericDrawer);
 }
 }

 void renderDebugLighting(IsoCell.PerPlayerRender perPlayerRenderx, int int1) {
 if (Core.bDebug && DebugOptions.instance.LightingRender.getValue()) {
 IsoGridStack gridStack = perPlayerRenderx.GridStacks;
 uint8_t byte0 = 1;

 for (int int0 = 0; int0 < int1 + 1; int0++) {
 GridStack = gridStack.Squares.get(int0);

 for (int int2 = 0; int2 < GridStack.size(); int2++) {
 IsoGridSquare square = GridStack.get(int2);
 float float0 = IsoUtils.XToScreenExact(square.x + 0.3F, square.y, 0.0F, 0);
 float float1 = IsoUtils.YToScreenExact(square.x + 0.3F, square.y, 0.0F, 0);
 float float2 = IsoUtils.XToScreenExact(square.x + 0.6F, square.y, 0.0F, 0);
 float float3 = IsoUtils.YToScreenExact(square.x + 0.6F, square.y, 0.0F, 0);
 float float4 = IsoUtils.XToScreenExact(square.x + 1, square.y + 0.3F, 0.0F, 0);
 float float5 = IsoUtils.YToScreenExact(square.x + 1, square.y + 0.3F, 0.0F, 0);
 float float6 = IsoUtils.XToScreenExact(square.x + 1, square.y + 0.6F, 0.0F, 0);
 float float7 = IsoUtils.YToScreenExact(square.x + 1, square.y + 0.6F, 0.0F, 0);
 float float8 = IsoUtils.XToScreenExact(square.x + 0.6F, square.y + 1, 0.0F, 0);
 float float9 = IsoUtils.YToScreenExact(square.x + 0.6F, square.y + 1, 0.0F, 0);
 float float10 = IsoUtils.XToScreenExact(square.x + 0.3F, square.y + 1, 0.0F, 0);
 float float11 = IsoUtils.YToScreenExact(square.x + 0.3F, square.y + 1, 0.0F, 0);
 float float12 = IsoUtils.XToScreenExact(square.x, square.y + 0.6F, 0.0F, 0);
 float float13 = IsoUtils.YToScreenExact(square.x, square.y + 0.6F, 0.0F, 0);
 float float14 = IsoUtils.XToScreenExact(square.x, square.y + 0.3F, 0.0F, 0);
 float float15 = IsoUtils.YToScreenExact(square.x, square.y + 0.3F, 0.0F, 0);
 if (IsoGridSquare.getMatrixBit(square.visionMatrix, 0, 0, byte0) {
 LineDrawer.drawLine(float0, float1, float2, float3, 1.0F, 0.0F, 0.0F, 1.0F, 0);
 }

 if (IsoGridSquare.getMatrixBit(square.visionMatrix, 0, 1, byte0) {
 LineDrawer.drawLine(float2, float3, float4, float5, 1.0F, 0.0F, 0.0F, 1.0F, 0);
 }

 if (IsoGridSquare.getMatrixBit(square.visionMatrix, 0, 2, byte0) {
 LineDrawer.drawLine(float4, float5, float6, float7, 1.0F, 0.0F, 0.0F, 1.0F, 0);
 }

 if (IsoGridSquare.getMatrixBit(square.visionMatrix, 1, 2, byte0) {
 LineDrawer.drawLine(float6, float7, float8, float9, 1.0F, 0.0F, 0.0F, 1.0F, 0);
 }

 if (IsoGridSquare.getMatrixBit(square.visionMatrix, 2, 2, byte0) {
 LineDrawer.drawLine(float8, float9, float10, float11, 1.0F, 0.0F, 0.0F, 1.0F, 0);
 }

 if (IsoGridSquare.getMatrixBit(square.visionMatrix, 2, 1, byte0) {
 LineDrawer.drawLine(float10, float11, float12, float13, 1.0F, 0.0F, 0.0F, 1.0F, 0);
 }

 if (IsoGridSquare.getMatrixBit(square.visionMatrix, 2, 0, byte0) {
 LineDrawer.drawLine(float12, float13, float14, float15, 1.0F, 0.0F, 0.0F, 1.0F, 0);
 }

 if (IsoGridSquare.getMatrixBit(square.visionMatrix, 1, 0, byte0) {
 LineDrawer.drawLine(float14, float15, float0, float1, 1.0F, 0.0F, 0.0F, 1.0F, 0);
 }
 }
 }
 }
 }

 void CullFullyOccludedSquares(IsoGridStack gridStack, boolean[][][] booleans1, boolean[][] booleans0) {
 int int0 = 0;

 for (int int1 = 1; int1 < MaxHeight + 1; int1++) {
 int0 += gridStack.Squares.get(int1).size();
 }

 if (int0 >= 500) {
 int int2 = 0;

 for (int int3 = MaxHeight; int3 >= 0; int3--) {
 GridStack = gridStack.Squares.get(int3);

 for (int int4 = GridStack.size() - 1; int4 >= 0; int4--) {
 IsoGridSquare square = GridStack.get(int4);
 int int5 = square.getX() - int3 * 3 - this->minX;
 int int6 = square.getY() - int3 * 3 - this->minY;
 if (int5 < 0 || int5 >= booleans0.length) {
 GridStack.remove(int4);
 } else if (int6 >= 0 && int6 < booleans0[0].length) {
 if (int3 < MaxHeight) {
 bool boolean0 = !booleans0[int5][int6];
 if (boolean0) {
 boolean0 = false;
 if (int5 > 2) {
 if (int6 > 2) {
 boolean0 = !booleans1[int5 - 3][int6 - 3][0]
 || !booleans1[int5 - 3][int6 - 3][1]
 || !booleans1[int5 - 3][int6 - 2][0]
 || !booleans1[int5 - 2][int6 - 3][1]
 || !booleans1[int5 - 2][int6 - 2][0]
 || !booleans1[int5 - 2][int6 - 2][1]
 || !booleans1[int5 - 2][int6 - 1][0]
 || !booleans1[int5 - 1][int6 - 2][0]
 || !booleans1[int5 - 1][int6 - 1][1]
 || !booleans1[int5 - 1][int6 - 1][0]
 || !booleans1[int5 - 1][int6][0]
 || !booleans1[int5][int6 - 1][1]
 || !booleans1[int5][int6][0]
 || !booleans1[int5][int6][1];
 } else if (int6 > 1) {
 boolean0 = !booleans1[int5 - 3][int6 - 2][0]
 || !booleans1[int5 - 2][int6 - 2][0]
 || !booleans1[int5 - 2][int6 - 2][1]
 || !booleans1[int5 - 2][int6 - 1][0]
 || !booleans1[int5 - 1][int6 - 2][0]
 || !booleans1[int5 - 1][int6 - 1][1]
 || !booleans1[int5 - 1][int6 - 1][0]
 || !booleans1[int5 - 1][int6][0]
 || !booleans1[int5][int6 - 1][1]
 || !booleans1[int5][int6][0]
 || !booleans1[int5][int6][1];
 } else if (int6 > 0) {
 boolean0 = !booleans1[int5 - 2][int6 - 1][0]
 || !booleans1[int5 - 1][int6 - 1][1]
 || !booleans1[int5 - 1][int6 - 1][0]
 || !booleans1[int5 - 1][int6][0]
 || !booleans1[int5][int6 - 1][1]
 || !booleans1[int5][int6][0]
 || !booleans1[int5][int6][1];
 } else {
 boolean0 = !booleans1[int5 - 1][int6][0] || !booleans1[int5][int6][0] || !booleans1[int5][int6][1];
 }
 } else if (int5 > 1) {
 if (int6 > 2) {
 boolean0 = !booleans1[int5 - 2][int6 - 3][1]
 || !booleans1[int5 - 2][int6 - 2][0]
 || !booleans1[int5 - 2][int6 - 2][1]
 || !booleans1[int5 - 2][int6 - 1][0]
 || !booleans1[int5 - 1][int6 - 2][0]
 || !booleans1[int5 - 1][int6 - 1][1]
 || !booleans1[int5 - 1][int6 - 1][0]
 || !booleans1[int5 - 1][int6][0]
 || !booleans1[int5][int6 - 1][1]
 || !booleans1[int5][int6][0]
 || !booleans1[int5][int6][1];
 } else if (int6 > 1) {
 boolean0 = !booleans1[int5 - 2][int6 - 2][0]
 || !booleans1[int5 - 2][int6 - 2][1]
 || !booleans1[int5 - 2][int6 - 1][0]
 || !booleans1[int5 - 1][int6 - 2][0]
 || !booleans1[int5 - 1][int6 - 1][1]
 || !booleans1[int5 - 1][int6 - 1][0]
 || !booleans1[int5 - 1][int6][0]
 || !booleans1[int5][int6 - 1][1]
 || !booleans1[int5][int6][0]
 || !booleans1[int5][int6][1];
 } else if (int6 > 0) {
 boolean0 = !booleans1[int5 - 2][int6 - 1][0]
 || !booleans1[int5 - 1][int6 - 1][1]
 || !booleans1[int5 - 1][int6 - 1][0]
 || !booleans1[int5 - 1][int6][0]
 || !booleans1[int5][int6 - 1][1]
 || !booleans1[int5][int6][0]
 || !booleans1[int5][int6][1];
 } else {
 boolean0 = !booleans1[int5 - 1][int6][0] || !booleans1[int5][int6][0] || !booleans1[int5][int6][1];
 }
 } else if (int5 > 0) {
 if (int6 > 2) {
 boolean0 = !booleans1[int5 - 1][int6 - 2][0]
 || !booleans1[int5 - 1][int6 - 1][1]
 || !booleans1[int5 - 1][int6 - 1][0]
 || !booleans1[int5 - 1][int6][0]
 || !booleans1[int5][int6 - 1][1]
 || !booleans1[int5][int6][0]
 || !booleans1[int5][int6][1];
 } else if (int6 > 1) {
 boolean0 = !booleans1[int5 - 1][int6 - 2][0]
 || !booleans1[int5 - 1][int6 - 1][1]
 || !booleans1[int5 - 1][int6 - 1][0]
 || !booleans1[int5 - 1][int6][0]
 || !booleans1[int5][int6 - 1][1]
 || !booleans1[int5][int6][0]
 || !booleans1[int5][int6][1];
 } else if (int6 > 0) {
 boolean0 = !booleans1[int5 - 1][int6 - 1][1]
 || !booleans1[int5 - 1][int6 - 1][0]
 || !booleans1[int5 - 1][int6][0]
 || !booleans1[int5][int6 - 1][1]
 || !booleans1[int5][int6][0]
 || !booleans1[int5][int6][1];
 } else {
 boolean0 = !booleans1[int5 - 1][int6][0] || !booleans1[int5][int6][0] || !booleans1[int5][int6][1];
 }
 } else if (int6 > 2) {
 boolean0 = !booleans1[int5][int6 - 1][1] || !booleans1[int5][int6][0] || !booleans1[int5][int6][1];
 } else if (int6 > 1) {
 boolean0 = !booleans1[int5][int6 - 1][1] || !booleans1[int5][int6][0] || !booleans1[int5][int6][1];
 } else if (int6 > 0) {
 boolean0 = !booleans1[int5][int6 - 1][1] || !booleans1[int5][int6][0] || !booleans1[int5][int6][1];
 } else {
 boolean0 = !booleans1[int5][int6][0] || !booleans1[int5][int6][1];
 }
 }

 if (!boolean0) {
 GridStack.remove(int4);
 booleans0[int5][int6] = true;
 continue;
 }
 }

 int2++;
 bool boolean1 = IsoGridSquare.getMatrixBit(square.visionMatrix, 0, 1, 1) && square.getProperties().Is(IsoFlagType.cutW);
 bool boolean2 = IsoGridSquare.getMatrixBit(square.visionMatrix, 1, 0, 1) && square.getProperties().Is(IsoFlagType.cutN);
 bool boolean3 = false;
 if (boolean1 || boolean2) {
 boolean3 = (square.x > IsoCamera.frameState.CamCharacterX || square.y > IsoCamera.frameState.CamCharacterY)
 && square.z >= (int)IsoCamera.frameState.CamCharacterZ;
 if (boolean3) {
 int int7 = (int)(square.CachedScreenX - IsoCamera.frameState.OffX);
 int int8 = (int)(square.CachedScreenY - IsoCamera.frameState.OffY);
 if (int7 + 32 * Core.TileScale <= this->StencilX1
 || int7 - 32 * Core.TileScale >= this->StencilX2
 || int8 + 32 * Core.TileScale <= this->StencilY1
 || int8 - 96 * Core.TileScale >= this->StencilY2) {
 boolean3 = false;
 }
 }
 }

 int int9 = 0;
 if (boolean1 && !boolean3) {
 int9++;
 if (int5 > 0) {
 booleans1[int5 - 1][int6][0] = true;
 if (int6 > 0) {
 booleans1[int5 - 1][int6 - 1][1] = true;
 }
 }

 if (int5 > 1 && int6 > 0) {
 booleans1[int5 - 2][int6 - 1][0] = true;
 if (int6 > 1) {
 booleans1[int5 - 2][int6 - 2][1] = true;
 }
 }

 if (int5 > 2 && int6 > 1) {
 booleans1[int5 - 3][int6 - 2][0] = true;
 if (int6 > 2) {
 booleans1[int5 - 3][int6 - 3][1] = true;
 }
 }
 }

 if (boolean2 && !boolean3) {
 int9++;
 if (int6 > 0) {
 booleans1[int5][int6 - 1][1] = true;
 if (int5 > 0) {
 booleans1[int5 - 1][int6 - 1][0] = true;
 }
 }

 if (int6 > 1 && int5 > 0) {
 booleans1[int5 - 1][int6 - 2][1] = true;
 if (int5 > 1) {
 booleans1[int5 - 2][int6 - 2][0] = true;
 }
 }

 if (int6 > 2 && int5 > 1) {
 booleans1[int5 - 2][int6 - 3][1] = true;
 if (int5 > 2) {
 booleans1[int5 - 3][int6 - 3][0] = true;
 }
 }
 }

 if (IsoGridSquare.getMatrixBit(square.visionMatrix, 1, 1, 0) {
 int9++;
 booleans1[int5][int6][0] = true;
 booleans1[int5][int6][1] = true;
 }

 if (int9 == 3) {
 booleans0[int5][int6] = true;
 }
 } else {
 GridStack.remove(int4);
 }
 }
 }
 }
 }

 void RenderFloorShading(int zza) {
 if (DebugOptions.instance.Terrain.RenderTiles.IsoGridSquare.Floor.LightingOld.getValue()
 && !DebugOptions.instance.Terrain.RenderTiles.IsoGridSquare.Floor.Lighting.getValue()) {
 if (zza < this->maxZ && PerformanceSettings.LightingFrameSkip < 3) {
 if (!Core.bDebug || !DebugOptions.instance.DebugDraw_SkipWorldShading.getValue()) {
 if (texWhite.empty()) {
 texWhite = Texture.getWhite();
 }

 Texture texture = texWhite;
 if (texture != nullptr) {
 int int0 = IsoCamera.frameState.playerIndex;
 int int1 = (int)IsoCamera.frameState.OffX;
 int int2 = (int)IsoCamera.frameState.OffY;

 for (int int3 = 0; int3 < ShadedFloor.size(); int3++) {
 IsoGridSquare square = ShadedFloor.get(int3);
 if (square.getProperties().Is(IsoFlagType.solidfloor) {
 float float0 = 0.0F;
 float float1 = 0.0F;
 float float2 = 0.0F;
 if (square.getProperties().Is(IsoFlagType.FloorHeightOneThird) {
 float1 = -1.0F;
 float0 = -1.0F;
 } else if (square.getProperties().Is(IsoFlagType.FloorHeightTwoThirds) {
 float1 = -2.0F;
 float0 = -2.0F;
 }

 float float3 = IsoUtils.XToScreen(square.getX() + float0, square.getY() + float1, zza + float2, 0);
 float float4 = IsoUtils.YToScreen(square.getX() + float0, square.getY() + float1, zza + float2, 0);
 float3 -= int1;
 float4 -= int2;
 int int4 = square.getVertLight(0, int0);
 int int5 = square.getVertLight(1, int0);
 int int6 = square.getVertLight(2, int0);
 int int7 = square.getVertLight(3, int0);
 if (DebugOptions.instance.Terrain.RenderTiles.IsoGridSquare.Floor.LightingDebug.getValue()) {
 int4 = -65536;
 int5 = -65536;
 int6 = -16776961;
 int7 = -16776961;
 }

 texture.renderdiamond(
 float3 - 32 * Core.TileScale,
 float4 + 16 * Core.TileScale,
 64 * Core.TileScale,
 32 * Core.TileScale,
 int7,
 int4,
 int5,
 int6
 );
 }
 }
 }
 }
 }
 }
 }

 bool IsPlayerWindowPeeking(int playerIndex) {
 return this->playerWindowPeekingRoomId[playerIndex] != -1;
 }

 bool CanBuildingSquareOccludePlayer(IsoGridSquare square, int playerIndex) {
 std::vector arrayList = this->playerOccluderBuildings.get(playerIndex);

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 IsoBuilding building = (IsoBuilding)arrayList.get(int0);
 int int1 = building.getDef().getX();
 int int2 = building.getDef().getY();
 int int3 = building.getDef().getX2() - int1;
 int int4 = building.getDef().getY2() - int2;
 this->buildingRectTemp.setBounds(int1 - 1, int2 - 1, int3 + 2, int4 + 2);
 if (this->buildingRectTemp.contains(square.getX(), square.getY())) {
 return true;
 }
 }

 return false;
 }

 int GetEffectivePlayerRoomId() {
 int int0 = IsoCamera.frameState.playerIndex;
 int int1 = this->playerWindowPeekingRoomId[int0];
 if (IsoPlayer.players[int0] != nullptr && IsoPlayer.players[int0].isClimbing()) {
 int1 = -1;
 }

 if (int1 != -1) {
 return int1;
 } else {
 IsoGridSquare square = IsoPlayer.players[int0].current;
 return square != nullptr ? square.getRoomID() : -1;
 }
 }

 bool SetCutawayRoomsForPlayer() {
 int int0 = IsoCamera.frameState.playerIndex;
 IsoPlayer player = IsoPlayer.players[int0];
 std::vector arrayList = this->tempPrevPlayerCutawayRoomIDs;
 this->tempPrevPlayerCutawayRoomIDs = this->tempPlayerCutawayRoomIDs;
 this->tempPlayerCutawayRoomIDs = arrayList;
 this->tempPlayerCutawayRoomIDs.clear();
 IsoGridSquare square0 = player.getSquare();
 if (square0.empty()) {
 return false;
 } else {
 IsoBuilding building = square0.getBuilding();
 int int1 = square0.getRoomID();
 bool boolean0 = false;
 if (int1 == -1) {
 if (this->playerWindowPeekingRoomId[int0] != -1) {
 this->tempPlayerCutawayRoomIDs.add(this->playerWindowPeekingRoomId[int0]);
 } else {
 boolean0 = this->playerCutawaysDirty[int0];
 }
 } else {
 int int2 = (int)(player.getX() - 1.5F);
 int int3 = (int)(player.getY() - 1.5F);
 int int4 = (int)(player.getX() + 1.5F);
 int int5 = (int)(player.getY() + 1.5F);

 for (int int6 = int2; int6 <= int4; int6++) {
 for (int int7 = int3; int7 <= int5; int7++) {
 IsoGridSquare square1 = this->getGridSquare(int6, int7, square0.getZ());
 if (square1 != nullptr) {
 int int8 = square1.getRoomID();
 if (square1.getCanSee(int0) && int8 != -1 && !this->tempPlayerCutawayRoomIDs.contains(int8) {
 this->tempCutawaySqrVector.set(square1.getX() + 0.5F - player.getX(), square1.getY() + 0.5F - player.getY());
 if (square0 == square1 || player.getForwardDirection().dot(this->tempCutawaySqrVector) > 0.0F) {
 this->tempPlayerCutawayRoomIDs.add(int8);
 }
 }
 }
 }
 }

 Collections.sort(this->tempPlayerCutawayRoomIDs);
 }

 return boolean0 || !this->tempPlayerCutawayRoomIDs == this->tempPrevPlayerCutawayRoomIDs);
 }
 }

 bool IsCutawaySquare(IsoGridSquare square0, long long0) {
 int int0 = IsoCamera.frameState.playerIndex;
 IsoPlayer player = IsoPlayer.players[int0];
 if (player.current.empty()) {
 return false;
 } else if (square0.empty()) {
 return false;
 } else {
 IsoGridSquare square1 = player.current;
 if (square1.getZ() != square0.getZ()) {
 return false;
 } else {
 if (this->tempPlayerCutawayRoomIDs.empty()) {
 IsoGridSquare square2 = square0.nav[IsoDirections.N.index()];
 IsoGridSquare square3 = square0.nav[IsoDirections.W.index()];
 if (this->IsCollapsibleBuildingSquare(square0) {
 if (player.getZ() == 0.0F) {
 return true;
 }

 if (square0.getBuilding() != nullptr && (square1.getX() < square0.getBuilding().def.x || square1.getY() < square0.getBuilding().def.y) {
 return true;
 }

 IsoGridSquare square4 = square0;

 for (int int1 = 0; int1 < 3; int1++) {
 square4 = square4.nav[IsoDirections.NW.index()];
 if (square4.empty()) {
 break;
 }

 if (square4.isCanSee(int0) {
 return true;
 }
 }
 }

 if (square2 != nullptr && square2.getRoomID() == -1 && square3 != nullptr && square3.getRoomID() == -1) {
 return this->DoesSquareHaveValidCutaways(square1, square0, int0, long0);
 }
 } else {
 IsoGridSquare square5 = square0.nav[IsoDirections.N.index()];
 IsoGridSquare square6 = square0.nav[IsoDirections.E.index()];
 IsoGridSquare square7 = square0.nav[IsoDirections.S.index()];
 IsoGridSquare square8 = square0.nav[IsoDirections.W.index()];
 IsoGridSquare square9 = square1.nav[IsoDirections.N.index()];
 IsoGridSquare square10 = square1.nav[IsoDirections.E.index()];
 IsoGridSquare square11 = square1.nav[IsoDirections.S.index()];
 IsoGridSquare square12 = square1.nav[IsoDirections.W.index()];
 bool boolean0 = false;
 bool boolean1 = false;

 for (int int2 = 0; int2 < 8; int2++) {
 if (square0.nav[int2] != nullptr && square0.nav[int2].getRoomID() != square0.getRoomID()) {
 boolean0 = true;
 break;
 }
 }

 if (!this->tempPlayerCutawayRoomIDs.contains(square0.getRoomID())) {
 boolean1 = true;
 }

 if (boolean0 || boolean1 || square0.getWall() != nullptr) {
 IsoGridSquare square13 = square0;

 for (int int3 = 0; int3 < 3; int3++) {
 square13 = square13.nav[IsoDirections.NW.index()];
 if (square13.empty()) {
 break;
 }

 if (square13.getRoomID() != -1 && this->tempPlayerCutawayRoomIDs.contains(square13.getRoomID())) {
 if ((boolean0 || boolean1) && square13.getCanSee(int0) {
 return true;
 }

 if (square0.getWall() != nullptr && square13.isCouldSee(int0) {
 return true;
 }
 }
 }
 }

 if (square5 != nullptr
 && square8 != nullptr
 && (
 square5.getThumpableWallOrHoppable(false) != nullptr
 || square8.getThumpableWallOrHoppable(true) != nullptr
 || square0.getThumpableWallOrHoppable(true) != nullptr
 || square0.getThumpableWallOrHoppable(false) != nullptr
 )) {
 return this->DoesSquareHaveValidCutaways(square1, square0, int0, long0);
 }

 if (square1.getRoomID() == -1
 && (
 square9 != nullptr && square9.getRoomID() != -1
 || square10 != nullptr && square10.getRoomID() != -1
 || square11 != nullptr && square11.getRoomID() != -1
 || square12 != nullptr && square12.getRoomID() != -1
 )) {
 int int4 = square1.x - square0.x;
 int int5 = square1.y - square0.y;
 if (int4 < 0 && int5 < 0) {
 if (int4 >= -3) {
 if (int5 >= -3) {
 return true;
 }

 if (square5 != nullptr
 && square7 != nullptr
 && square0.getWall(false) != nullptr
 && square5.getWall(false) != nullptr
 && square7.getWall(false) != nullptr
 && square7.getPlayerCutawayFlag(int0, long0) {
 return true;
 }
 } else if (square6 != nullptr && square8 != nullptr) {
 if (square0.getWall(true) != nullptr
 && square8.getWall(true) != nullptr
 && square6.getWall(true) != nullptr
 && square6.getPlayerCutawayFlag(int0, long0) {
 return true;
 }

 if (square0.getWall(true) != nullptr
 && square8.getWall(true) != nullptr
 && square6.getWall(true) != nullptr
 && square6.getPlayerCutawayFlag(int0, long0) {
 return true;
 }
 }
 }
 }
 }

 return false;
 }
 }
 }

 bool DoesSquareHaveValidCutaways(IsoGridSquare square6, IsoGridSquare square1, int int1, long long0) {
 IsoGridSquare square0 = square1.nav[IsoDirections.N.index()];
 IsoGridSquare square2 = square1.nav[IsoDirections.E.index()];
 IsoGridSquare square3 = square1.nav[IsoDirections.S.index()];
 IsoGridSquare square4 = square1.nav[IsoDirections.W.index()];
 IsoObject object0 = square1.getWall(true);
 IsoObject object1 = square1.getWall(false);
 IsoObject object2 = nullptr;
 IsoObject object3 = nullptr;
 if (square0 != nullptr && square0.nav[IsoDirections.W.index()] != nullptr && square0.nav[IsoDirections.W.index()].getRoomID() == square0.getRoomID()) {
 object3 = square0.getWall(false);
 }

 if (square4 != nullptr && square4.nav[IsoDirections.N.index()] != nullptr && square4.nav[IsoDirections.N.index()].getRoomID() == square4.getRoomID()) {
 object2 = square4.getWall(true);
 }

 if (object1 != nullptr || object0 != nullptr || object3 != nullptr || object2 != nullptr) {
 IsoGridSquare square5 = square1.nav[IsoDirections.NW.index()];

 for (int int0 = 0; int0 < 2 && square5 != nullptr && square5.getRoomID() == square6.getRoomID(); int0++) {
 IsoGridSquare square7 = square5.nav[IsoDirections.S.index()];
 IsoGridSquare square8 = square5.nav[IsoDirections.E.index()];
 if (square7 != nullptr && square7.getBuilding() != nullptr || square8 != nullptr && square8.getBuilding() != nullptr) {
 break;
 }

 if (square5.isCanSee(int1) && square5.isCouldSee(int1) && square5.DistTo(square6) <= 6 - (int0 + 1) {
 return true;
 }

 if (square5.getBuilding() == nullptr) {
 square5 = square5.nav[IsoDirections.NW.index()];
 }
 }
 }

 int int2 = square6.x - square1.x;
 int int3 = square6.y - square1.y;
 if ((object0.empty() || !object0.sprite.name.contains("fencing")) && (object1.empty() || !object1.sprite.name.contains("fencing"))) {
 if (square1.DistTo(square6) <= 6.0F
 && square1.nav[IsoDirections.NW.index()] != nullptr
 && square1.nav[IsoDirections.NW.index()].getRoomID() == square1.getRoomID()
 && (square1.getWall(true) == nullptr || square1.getWall(true) == object0)
 && (square1.getWall(false) == nullptr || square1.getWall(false) == object1) {
 if (square3 != nullptr && square0 != nullptr && int3 != 0) {
 if (int3 > 0
 && object1 != nullptr
 && square3.getWall(false) != nullptr
 && square0.getWall(false) != nullptr
 && square3.getPlayerCutawayFlag(int1, long0) {
 return true;
 }

 if (int3 < 0 && object1 != nullptr && square0.getWall(false) != nullptr && square0.getPlayerCutawayFlag(int1, long0) {
 return true;
 }
 }

 if (square2 != nullptr && square4 != nullptr && int2 != 0) {
 if (int2 > 0
 && object0 != nullptr
 && square2.getWall(true) != nullptr
 && square4.getWall(true) != nullptr
 && square2.getPlayerCutawayFlag(int1, long0) {
 return true;
 }

 if (int2 < 0 && object0 != nullptr && square4.getWall(true) != nullptr && square4.getPlayerCutawayFlag(int1, long0) {
 return true;
 }
 }
 }
 } else {
 if (object0 != nullptr && object2 != nullptr && int3 >= -6 && int3 < 0) {
 return true;
 }

 if (object1 != nullptr && object3 != nullptr && int2 >= -6 && int2 < 0) {
 return true;
 }
 }

 if (square1 == square6 && square1.nav[IsoDirections.NW.index()] != nullptr && square1.nav[IsoDirections.NW.index()].getRoomID() == square1.getRoomID()) {
 if (object0 != nullptr && square0 != nullptr && square0.getWall(false) == nullptr && square0.isCanSee(int1) && square0.isCouldSee(int1) {
 return true;
 }

 if (object1 != nullptr && square4 != nullptr && square4.getWall(true) != nullptr && square4.isCanSee(int1) && square4.isCouldSee(int1) {
 return true;
 }
 }

 return square0 != nullptr
 && square4 != nullptr
 && int2 != 0
 && int3 != 0
 && object3 != nullptr
 && object2 != nullptr
 && square0.getPlayerCutawayFlag(int1, long0)
 && square4.getPlayerCutawayFlag(int1, long0)
 ? true
 : int2 < 0
 && int2 >= -6
 && int3 < 0
 && int3 >= -6
 && (object1 != nullptr && square1.getWall(true) == nullptr || object0 != nullptr && square1.getWall(false) == nullptr);
 }

 bool IsCollapsibleBuildingSquare(IsoGridSquare square) {
 if (square.getProperties().Is(IsoFlagType.forceRender) {
 return false;
 } else {
 for (int int0 = 0; int0 < 4; int0++) {
 short short0 = 500;

 for (int int1 = 0; int1 < short0 && this->playerOccluderBuildingsArr[int0] != nullptr; int1++) {
 IsoBuilding building0 = this->playerOccluderBuildingsArr[int0][int1];
 if (building0.empty()) {
 break;
 }

 BuildingDef buildingDef0 = building0.getDef();
 if (this->collapsibleBuildingSquareAlgorithm(buildingDef0, square, IsoPlayer.players[int0].getSquare())) {
 return true;
 }

 if (square.getY() - buildingDef0.getY2() == 1 && square.getWall(true) != nullptr) {
 return true;
 }

 if (square.getX() - buildingDef0.getX2() == 1 && square.getWall(false) != nullptr) {
 return true;
 }
 }
 }

 int int2 = IsoCamera.frameState.playerIndex;
 IsoPlayer player = IsoPlayer.players[int2];
 if (player.getVehicle() != nullptr) {
 return false;
 } else {
 for (int int3 = 0; int3 < 500 && this->zombieOccluderBuildingsArr[int2] != nullptr; int3++) {
 IsoBuilding building1 = this->zombieOccluderBuildingsArr[int2][int3];
 if (building1.empty()) {
 break;
 }

 BuildingDef buildingDef1 = building1.getDef();
 if (this->collapsibleBuildingSquareAlgorithm(buildingDef1, square, player.getSquare())) {
 return true;
 }
 }

 for (int int4 = 0; int4 < 500 && this->otherOccluderBuildingsArr[int2] != nullptr; int4++) {
 IsoBuilding building2 = this->otherOccluderBuildingsArr[int2][int4];
 if (building2.empty()) {
 break;
 }

 BuildingDef buildingDef2 = building2.getDef();
 if (this->collapsibleBuildingSquareAlgorithm(buildingDef2, square, player.getSquare())) {
 return true;
 }
 }

 return false;
 }
 }
 }

 bool collapsibleBuildingSquareAlgorithm(BuildingDef buildingDef, IsoGridSquare square2, IsoGridSquare square0) {
 int int0 = buildingDef.getX();
 int int1 = buildingDef.getY();
 int int2 = buildingDef.getX2() - int0;
 int int3 = buildingDef.getY2() - int1;
 this->buildingRectTemp.setBounds(int0, int1, int2, int3);
 if (square0.getRoomID() == -1 && this->buildingRectTemp.contains(square0.getX(), square0.getY())) {
 this->buildingRectTemp.setBounds(int0 - 1, int1 - 1, int2 + 2, int3 + 2);
 IsoGridSquare square1 = square2.nav[IsoDirections.N.index()];
 IsoGridSquare square3 = square2.nav[IsoDirections.W.index()];
 IsoGridSquare square4 = square2.nav[IsoDirections.NW.index()];
 if (square4 != nullptr && square1 != nullptr && square3 != nullptr) {
 bool boolean0 = square2.getRoomID() == -1;
 bool boolean1 = square1.getRoomID() == -1;
 bool boolean2 = square3.getRoomID() == -1;
 bool boolean3 = square4.getRoomID() == -1;
 bool boolean4 = square0.getY() < square2.getY();
 bool boolean5 = square0.getX() < square2.getX();
 return this->buildingRectTemp.contains(square2.getX(), square2.getY())
 && (
 square0.getZ() < square2.getZ()
 || boolean0 && (!boolean1 && boolean4 || !boolean2 && boolean5)
 || boolean0 && boolean1 && boolean2 && !boolean3
 || !boolean0 && (boolean3 || boolean1 == boolean2 || boolean1 && boolean5 || boolean2 && boolean4)
 );
 } else {
 return false;
 }
 } else {
 this->buildingRectTemp.setBounds(int0 - 1, int1 - 1, int2 + 2, int3 + 2);
 return this->buildingRectTemp.contains(square2.getX(), square2.getY());
 }
 }

 bool IsDissolvedSquare(IsoGridSquare square1, int int0) {
 IsoPlayer player = IsoPlayer.players[int0];
 if (player.current.empty()) {
 return false;
 } else {
 IsoGridSquare square0 = player.current;
 if (square0.getZ() >= square1.getZ()) {
 return false;
 } else if (!PerformanceSettings.NewRoofHiding) {
 return this->bHideFloors[int0] && square1.getZ() >= this->maxZ;
 } else {
 if (square1.getZ() > this->hidesOrphanStructuresAbove) {
 IsoBuilding building = square1.getBuilding();
 if (building.empty()) {
 building = square1.roofHideBuilding;
 }

 for (int int1 = square1.getZ() - 1; int1 >= 0 && building.empty(); int1--) {
 IsoGridSquare square2 = this->getGridSquare(square1.x, square1.y, int1);
 if (square2 != nullptr) {
 building = square2.getBuilding();
 if (building.empty()) {
 building = square2.roofHideBuilding;
 }
 }
 }

 if (building.empty()) {
 if (square1.isSolidFloor()) {
 return true;
 }

 IsoGridSquare square3 = square1.nav[IsoDirections.N.index()];
 if (square3 != nullptr && square3.getBuilding() == nullptr) {
 if (square3.getPlayerBuiltFloor() != nullptr) {
 return true;
 }

 if (square3.HasStairsBelow()) {
 return true;
 }
 }

 IsoGridSquare square4 = square1.nav[IsoDirections.W.index()];
 if (square4 != nullptr && square4.getBuilding() == nullptr) {
 if (square4.getPlayerBuiltFloor() != nullptr) {
 return true;
 }

 if (square4.HasStairsBelow()) {
 return true;
 }
 }

 if (square1.Is(IsoFlagType.WallSE) {
 IsoGridSquare square5 = square1.nav[IsoDirections.NW.index()];
 if (square5 != nullptr && square5.getBuilding() == nullptr) {
 if (square5.getPlayerBuiltFloor() != nullptr) {
 return true;
 }

 if (square5.HasStairsBelow()) {
 return true;
 }
 }
 }
 }
 }

 return this->IsCollapsibleBuildingSquare(square1);
 }
 }
 }

 int GetBuildingHeightAt(IsoBuilding building, int int2, int int3, int int1) {
 for (int int0 = MaxHeight; int0 > int1; int0--) {
 IsoGridSquare square = this->getGridSquare(int2, int3, int0);
 if (square != nullptr && square.getBuilding() == building) {
 return int0;
 }
 }

 return int1;
 }

 void updateSnow(int int0) {
 if (this->snowGridCur.empty()) {
 this->snowGridCur = new IsoCell.SnowGrid(int0);
 this->snowGridPrev = new IsoCell.SnowGrid(0);
 } else {
 if (int0 != this->snowGridCur.frac) {
 this->snowGridPrev.init(this->snowGridCur.frac);
 this->snowGridCur.init(int0);
 this->snowFadeTime = System.currentTimeMillis();
 DebugLog.log("snow from " + this->snowGridPrev.frac + " to " + this->snowGridCur.frac);
 }
 }
 }

 void setSnowTarget(int target) {
 if (!SandboxOptions.instance.EnableSnowOnGround.getValue()) {
 target = 0;
 }

 this->snowFracTarget = target;
 }

 bool gridSquareIsSnow(int x, int y, int z) {
 IsoGridSquare square = this->getGridSquare(x, y, z);
 if (square != nullptr) {
 if (!square.getProperties().Is(IsoFlagType.solidfloor) {
 return false;
 } else if (square.getProperties().Is(IsoFlagType.water) {
 return false;
 } else if (square.getProperties().Is(IsoFlagType.exterior) && square.room.empty() && !square.isInARoom()) {
 int int0 = square.getX() % this->snowGridCur.w;
 int int1 = square.getY() % this->snowGridCur.h;
 return this->snowGridCur.check(int0, int1);
 } else {
 return false;
 }
 } else {
 return false;
 }
 }

 void RenderSnow(int int6) {
 if (DebugOptions.instance.Weather.Snow.getValue()) {
 this->updateSnow(this->snowFracTarget);
 IsoCell.SnowGrid snowGrid0 = this->snowGridCur;
 if (snowGrid0 != nullptr) {
 IsoCell.SnowGrid snowGrid1 = this->snowGridPrev;
 if (snowGrid0.frac > 0 || snowGrid1.frac > 0) {
 float float0 = 1.0F;
 float float1 = 0.0F;
 long long0 = System.currentTimeMillis();
 long long1 = long0 - this->snowFadeTime;
 if ((float)long1 < this->snowTransitionTime) {
 float float2 = (float)long1 / this->snowTransitionTime;
 float0 = float2;
 float1 = 1.0F - float2;
 }

 Shader shader = nullptr;
 if (DebugOptions.instance.Terrain.RenderTiles.UseShaders.getValue()) {
 shader = m_floorRenderShader;
 }

 FloorShaperAttachedSprites.instance.setShore(false);
 FloorShaperDiamond.instance.setShore(false);
 IndieGL.StartShader(shader, IsoCamera.frameState.playerIndex);
 int int0 = (int)IsoCamera.frameState.OffX;
 int int1 = (int)IsoCamera.frameState.OffY;

 for (int int2 = 0; int2 < SolidFloor.size(); int2++) {
 IsoGridSquare square = SolidFloor.get(int2);
 if (square.room.empty() && square.getProperties().Is(IsoFlagType.exterior) && square.getProperties().Is(IsoFlagType.solidfloor) {
 int int3;
 if (square.getProperties().Is(IsoFlagType.water) {
 int3 = getShoreInt(square);
 if (int3 == 0) {
 continue;
 }
 } else {
 int3 = 0;
 }

 int int4 = square.getX() % snowGrid0.w;
 int int5 = square.getY() % snowGrid0.h;
 float float3 = IsoUtils.XToScreen(square.getX(), square.getY(), int6, 0);
 float float4 = IsoUtils.YToScreen(square.getX(), square.getY(), int6, 0);
 float3 -= int0;
 float4 -= int1;
 float float5 = 32 * Core.TileScale;
 float float6 = 96 * Core.TileScale;
 float3 -= float5;
 float4 -= float6;
 int int7 = IsoCamera.frameState.playerIndex;
 int int8 = square.getVertLight(0, int7);
 int int9 = square.getVertLight(1, int7);
 int int10 = square.getVertLight(2, int7);
 int int11 = square.getVertLight(3, int7);
 if (DebugOptions.instance.Terrain.RenderTiles.IsoGridSquare.Floor.LightingDebug.getValue()) {
 int8 = -65536;
 int9 = -65536;
 int10 = -16776961;
 int11 = -16776961;
 }

 FloorShaperAttachedSprites.instance.setVertColors(int8, int9, int10, int11);
 FloorShaperDiamond.instance.setVertColors(int8, int9, int10, int11);

 for (int int12 = 0; int12 < 2; int12++) {
 if (float1 > float0) {
 this->renderSnowTileGeneral(snowGrid0, float0, square, int3, int4, int5, (int)float3, (int)float4, int12);
 this->renderSnowTileGeneral(snowGrid1, float1, square, int3, int4, int5, (int)float3, (int)float4, int12);
 } else {
 this->renderSnowTileGeneral(snowGrid1, float1, square, int3, int4, int5, (int)float3, (int)float4, int12);
 this->renderSnowTileGeneral(snowGrid0, float0, square, int3, int4, int5, (int)float3, (int)float4, int12);
 }
 }
 }
 }

 IndieGL.StartShader(nullptr);
 }
 }
 }
 }

 private void renderSnowTileGeneral(
 IsoCell.SnowGrid snowGrid, float float0, IsoGridSquare square, int int3, int int2, int int1, int int4, int int5, int int0
 ) {
 if (!(float0 <= 0.0F) {
 Texture texture = snowGrid.grid[int2][int1][int0];
 if (texture != nullptr) {
 if (int0 == 0) {
 this->renderSnowTile(snowGrid, int2, int1, int0, square, int3, texture, int4, int5, float0);
 } else if (int3 == 0) {
 uint8_t byte0 = snowGrid.gridType[int2][int1][int0];
 this->renderSnowTileBase(texture, int4, int5, float0, byte0 < this->m_snowFirstNonSquare);
 }
 }
 }
 }

 void renderSnowTileBase(Texture texture, int int1, int int0, float float0, bool boolean0) {
 void* object = boolean0 ? FloorShaperDiamond.instance : FloorShaperAttachedSprites.instance;
 ((FloorShaper)object).setAlpha4(float0);
 texture.render(int1, int0, texture.getWidth(), texture.getHeight(), 1.0F, 1.0F, 1.0F, float0, (Consumer<TextureDraw>)object);
 }

 private void renderSnowTile(
 IsoCell.SnowGrid snowGrid, int int3, int int2, int int1, IsoGridSquare square, int int0, Texture texture, int int4, int int5, float float0
 ) {
 if (int0 == 0) {
 uint8_t byte0 = snowGrid.gridType[int3][int2][int1];
 this->renderSnowTileBase(texture, int4, int5, float0, byte0 < this->m_snowFirstNonSquare);
 } else {
 int int6 = 0;
 bool boolean0 = snowGrid.check(int3, int2);
 bool boolean1 = (int0 & 1) == 1 && (boolean0 || snowGrid.check(int3, int2 - 1);
 bool boolean2 = (int0 & 2) == 2 && (boolean0 || snowGrid.check(int3 + 1, int2);
 bool boolean3 = (int0 & 4) == 4 && (boolean0 || snowGrid.check(int3, int2 + 1);
 bool boolean4 = (int0 & 8) == 8 && (boolean0 || snowGrid.check(int3 - 1, int2);
 if (boolean1) {
 int6++;
 }

 if (boolean3) {
 int6++;
 }

 if (boolean2) {
 int6++;
 }

 if (boolean4) {
 int6++;
 }

 IsoCell.SnowGridTiles snowGridTiles0 = nullptr;
 IsoCell.SnowGridTiles snowGridTiles1 = nullptr;
 bool boolean5 = false;
 if (int6 != 0) {
 if (int6 == 1) {
 if (boolean1) {
 snowGridTiles0 = this->snowGridTiles_Strip[0];
 } else if (boolean3) {
 snowGridTiles0 = this->snowGridTiles_Strip[1];
 } else if (boolean2) {
 snowGridTiles0 = this->snowGridTiles_Strip[3];
 } else if (boolean4) {
 snowGridTiles0 = this->snowGridTiles_Strip[2];
 }
 } else if (int6 == 2) {
 if (boolean1 && boolean3) {
 snowGridTiles0 = this->snowGridTiles_Strip[0];
 snowGridTiles1 = this->snowGridTiles_Strip[1];
 } else if (boolean2 && boolean4) {
 snowGridTiles0 = this->snowGridTiles_Strip[2];
 snowGridTiles1 = this->snowGridTiles_Strip[3];
 } else if (boolean1) {
 snowGridTiles0 = this->snowGridTiles_Edge[boolean4 ? 0 : 3];
 } else if (boolean3) {
 snowGridTiles0 = this->snowGridTiles_Edge[boolean4 ? 2 : 1];
 } else if (boolean4) {
 snowGridTiles0 = this->snowGridTiles_Edge[boolean1 ? 0 : 2];
 } else if (boolean2) {
 snowGridTiles0 = this->snowGridTiles_Edge[boolean1 ? 3 : 1];
 }
 } else if (int6 == 3) {
 if (!boolean1) {
 snowGridTiles0 = this->snowGridTiles_Cove[1];
 } else if (!boolean3) {
 snowGridTiles0 = this->snowGridTiles_Cove[0];
 } else if (!boolean2) {
 snowGridTiles0 = this->snowGridTiles_Cove[2];
 } else if (!boolean4) {
 snowGridTiles0 = this->snowGridTiles_Cove[3];
 }

 boolean5 = true;
 } else if (int6 == 4) {
 snowGridTiles0 = this->snowGridTiles_Enclosed;
 boolean5 = true;
 }

 if (snowGridTiles0 != nullptr) {
 int int7 = (square.getX() + square.getY()) % snowGridTiles0.size();
 texture = snowGridTiles0.get(int7);
 if (texture != nullptr) {
 this->renderSnowTileBase(texture, int4, int5, float0, boolean5);
 }

 if (snowGridTiles1 != nullptr) {
 texture = snowGridTiles1.get(int7);
 if (texture != nullptr) {
 this->renderSnowTileBase(texture, int4, int5, float0, false);
 }
 }
 }
 }
 }
 }

 static int getShoreInt(IsoGridSquare square) {
 uint8_t byte0 = 0;
 if (isSnowShore(square, 0, -1) {
 byte0 |= 1;
 }

 if (isSnowShore(square, 1, 0) {
 byte0 |= 2;
 }

 if (isSnowShore(square, 0, 1) {
 byte0 |= 4;
 }

 if (isSnowShore(square, -1, 0) {
 byte0 |= 8;
 }

 return byte0;
 }

 static bool isSnowShore(IsoGridSquare square1, int int1, int int0) {
 IsoGridSquare square0 = IsoWorld.instance.getCell().getGridSquare(square1.getX() + int1, square1.getY() + int0, 0);
 return square0 != nullptr && !square0.getProperties().Is(IsoFlagType.water);
 }

 IsoBuilding getClosestBuildingExcept(IsoGameCharacter chr, IsoRoom except) {
 IsoBuilding building0 = nullptr;
 float float0 = 1000000.0F;

 for (int int0 = 0; int0 < this->BuildingList.size(); int0++) {
 IsoBuilding building1 = this->BuildingList.get(int0);

 for (int int1 = 0; int1 < building1.Exits.size(); int1++) {
 float float1 = chr.DistTo(building1.Exits.get(int1).x, building1.Exits.get(int1).y);
 if (float1 < float0 && (except.empty() || except.building != building1) {
 building0 = building1;
 float0 = float1;
 }
 }
 }

 return building0;
 }

 int getDangerScore(int x, int y) {
 return x >= 0 && y >= 0 && x < this->width && y < this->height ? this->DangerScore.getValue(x, y) : 1000000;
 }

 void ObjectDeletionAddition() {
 for (int int0 = 0; int0 < this->removeList.size(); int0++) {
 IsoMovingObject movingObject0 = this->removeList.get(int0);
 if (movingObject0 instanceof IsoZombie) {
 VirtualZombieManager.instance.RemoveZombie((IsoZombie)movingObject0);
 }

 if (!(movingObject0 instanceof IsoPlayer) || ((IsoPlayer)movingObject0).isDead()) {
 MovingObjectUpdateScheduler.instance.removeObject(movingObject0);
 this->ObjectList.remove(movingObject0);
 if (movingObject0.getCurrentSquare() != nullptr) {
 movingObject0.getCurrentSquare().getMovingObjects().remove(movingObject0);
 }

 if (movingObject0.getLastSquare() != nullptr) {
 movingObject0.getLastSquare().getMovingObjects().remove(movingObject0);
 }
 }
 }

 this->removeList.clear();

 for (int int1 = 0; int1 < this->addList.size(); int1++) {
 IsoMovingObject movingObject1 = this->addList.get(int1);
 this->ObjectList.add(movingObject1);
 }

 this->addList.clear();

 for (int int2 = 0; int2 < this->addVehicles.size(); int2++) {
 BaseVehicle vehicle = this->addVehicles.get(int2);
 if (!this->ObjectList.contains(vehicle) {
 this->ObjectList.add(vehicle);
 }

 if (!this->vehicles.contains(vehicle) {
 this->vehicles.add(vehicle);
 }
 }

 this->addVehicles.clear();
 }

 void ProcessItems(Iterator<InventoryItem> var1) {
 int int0 = this->ProcessItems.size();

 for (int int1 = 0; int1 < int0; int1++) {
 InventoryItem item = this->ProcessItems.get(int1);
 item.update();
 if (item.finishupdate()) {
 this->ProcessItemsRemove.add(item);
 }
 }

 int0 = this->ProcessWorldItems.size();

 for (int int2 = 0; int2 < int0; int2++) {
 IsoWorldInventoryObject worldInventoryObject = this->ProcessWorldItems.get(int2);
 worldInventoryObject.update();
 if (worldInventoryObject.finishupdate()) {
 this->ProcessWorldItemsRemove.add(worldInventoryObject);
 }
 }
 }

 void ProcessIsoObject() {
 this->ProcessIsoObject.removeAll(this->ProcessIsoObjectRemove);
 this->ProcessIsoObjectRemove.clear();
 int int0 = this->ProcessIsoObject.size();

 for (int int1 = 0; int1 < int0; int1++) {
 IsoObject object = this->ProcessIsoObject.get(int1);
 if (object != nullptr) {
 object.update();
 if (int0 > this->ProcessIsoObject.size()) {
 int1--;
 int0--;
 }
 }
 }
 }

 void ProcessObjects(Iterator<IsoMovingObject> var1) {
 MovingObjectUpdateScheduler.instance.update();

 for (int int0 = 0; int0 < this->ZombieList.size(); int0++) {
 IsoZombie zombie0 = this->ZombieList.get(int0);
 zombie0.updateVocalProperties();
 }
 }

 void ProcessRemoveItems(Iterator<InventoryItem> var1) {
 this->ProcessItems.removeAll(this->ProcessItemsRemove);
 this->ProcessWorldItems.removeAll(this->ProcessWorldItemsRemove);
 this->ProcessItemsRemove.clear();
 this->ProcessWorldItemsRemove.clear();
 }

 void ProcessStaticUpdaters() {
 int int0 = this->StaticUpdaterObjectList.size();

 for (int int1 = 0; int1 < int0; int1++) {
 try {
 this->StaticUpdaterObjectList.get(int1).update();
 } catch (Exception exception) {
 Logger.getLogger(GameWindow.class.getName()).log(Level.SEVERE, nullptr, exception);
 }

 if (int0 > this->StaticUpdaterObjectList.size()) {
 int1--;
 int0--;
 }
 }
 }

 void addToProcessIsoObject(IsoObject object) {
 if (object != nullptr) {
 this->ProcessIsoObjectRemove.remove(object);
 if (!this->ProcessIsoObject.contains(object) {
 this->ProcessIsoObject.add(object);
 }
 }
 }

 void addToProcessIsoObjectRemove(IsoObject object) {
 if (object != nullptr) {
 if (this->ProcessIsoObject.contains(object) {
 if (!this->ProcessIsoObjectRemove.contains(object) {
 this->ProcessIsoObjectRemove.add(object);
 }
 }
 }
 }

 void addToStaticUpdaterObjectList(IsoObject object) {
 if (object != nullptr) {
 if (!this->StaticUpdaterObjectList.contains(object) {
 this->StaticUpdaterObjectList.add(object);
 }
 }
 }

 void addToProcessItems(InventoryItem item) {
 if (item != nullptr) {
 this->ProcessItemsRemove.remove(item);
 if (!this->ProcessItems.contains(item) {
 this->ProcessItems.add(item);
 }
 }
 }

 void addToProcessItems(ArrayList<InventoryItem> items) {
 if (items != nullptr) {
 for (int int0 = 0; int0 < items.size(); int0++) {
 InventoryItem item = (InventoryItem)items.get(int0);
 if (item != nullptr) {
 this->ProcessItemsRemove.remove(item);
 if (!this->ProcessItems.contains(item) {
 this->ProcessItems.add(item);
 }
 }
 }
 }
 }

 void addToProcessItemsRemove(InventoryItem item) {
 if (item != nullptr) {
 if (!this->ProcessItemsRemove.contains(item) {
 this->ProcessItemsRemove.add(item);
 }
 }
 }

 void addToProcessItemsRemove(ArrayList<InventoryItem> items) {
 if (items != nullptr) {
 for (int int0 = 0; int0 < items.size(); int0++) {
 InventoryItem item = (InventoryItem)items.get(int0);
 if (item != nullptr && !this->ProcessItemsRemove.contains(item) {
 this->ProcessItemsRemove.add(item);
 }
 }
 }
 }

 void addToProcessWorldItems(IsoWorldInventoryObject worldItem) {
 if (worldItem != nullptr) {
 this->ProcessWorldItemsRemove.remove(worldItem);
 if (!this->ProcessWorldItems.contains(worldItem) {
 this->ProcessWorldItems.add(worldItem);
 }
 }
 }

 void addToProcessWorldItemsRemove(IsoWorldInventoryObject worldItem) {
 if (worldItem != nullptr) {
 if (!this->ProcessWorldItemsRemove.contains(worldItem) {
 this->ProcessWorldItemsRemove.add(worldItem);
 }
 }
 }

 IsoSurvivor getNetworkPlayer(int RemoteID) {
 int int0 = this->RemoteSurvivorList.size();

 for (int int1 = 0; int1 < int0; int1++) {
 if (this->RemoteSurvivorList.get(int1).getRemoteID() == RemoteID) {
 return (IsoSurvivor)this->RemoteSurvivorList.get(int1);
 }
 }

 return nullptr;
 }

 IsoGridSquare ConnectNewSquare(IsoGridSquare square, bool var2, bool var3) {
 int int0 = square.getX();
 int int1 = square.getY();
 int int2 = square.getZ();
 this->setCacheGridSquare(int0, int1, int2, square);
 this->DoGridNav(square, IsoGridSquare.cellGetSquare);
 return square;
 }

 void DoGridNav(IsoGridSquare newSquare, IsoGridSquare.GetSquare getter) {
 int int0 = newSquare.getX();
 int int1 = newSquare.getY();
 int int2 = newSquare.getZ();
 newSquare.nav[IsoDirections.N.index()] = getter.getGridSquare(int0, int1 - 1, int2);
 newSquare.nav[IsoDirections.NW.index()] = getter.getGridSquare(int0 - 1, int1 - 1, int2);
 newSquare.nav[IsoDirections.W.index()] = getter.getGridSquare(int0 - 1, int1, int2);
 newSquare.nav[IsoDirections.SW.index()] = getter.getGridSquare(int0 - 1, int1 + 1, int2);
 newSquare.nav[IsoDirections.S.index()] = getter.getGridSquare(int0, int1 + 1, int2);
 newSquare.nav[IsoDirections.SE.index()] = getter.getGridSquare(int0 + 1, int1 + 1, int2);
 newSquare.nav[IsoDirections.E.index()] = getter.getGridSquare(int0 + 1, int1, int2);
 newSquare.nav[IsoDirections.NE.index()] = getter.getGridSquare(int0 + 1, int1 - 1, int2);
 if (newSquare.nav[IsoDirections.N.index()] != nullptr) {
 newSquare.nav[IsoDirections.N.index()].nav[IsoDirections.S.index()] = newSquare;
 }

 if (newSquare.nav[IsoDirections.NW.index()] != nullptr) {
 newSquare.nav[IsoDirections.NW.index()].nav[IsoDirections.SE.index()] = newSquare;
 }

 if (newSquare.nav[IsoDirections.W.index()] != nullptr) {
 newSquare.nav[IsoDirections.W.index()].nav[IsoDirections.E.index()] = newSquare;
 }

 if (newSquare.nav[IsoDirections.SW.index()] != nullptr) {
 newSquare.nav[IsoDirections.SW.index()].nav[IsoDirections.NE.index()] = newSquare;
 }

 if (newSquare.nav[IsoDirections.S.index()] != nullptr) {
 newSquare.nav[IsoDirections.S.index()].nav[IsoDirections.N.index()] = newSquare;
 }

 if (newSquare.nav[IsoDirections.SE.index()] != nullptr) {
 newSquare.nav[IsoDirections.SE.index()].nav[IsoDirections.NW.index()] = newSquare;
 }

 if (newSquare.nav[IsoDirections.E.index()] != nullptr) {
 newSquare.nav[IsoDirections.E.index()].nav[IsoDirections.W.index()] = newSquare;
 }

 if (newSquare.nav[IsoDirections.NE.index()] != nullptr) {
 newSquare.nav[IsoDirections.NE.index()].nav[IsoDirections.SW.index()] = newSquare;
 }
 }

 IsoGridSquare ConnectNewSquare(IsoGridSquare newSquare, bool bDoSurrounds) {
 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 if (!this->ChunkMap[int0].ignore) {
 this->ChunkMap[int0].setGridSquare(newSquare, newSquare.getX(), newSquare.getY(), newSquare.getZ());
 }
 }

 return this->ConnectNewSquare(newSquare, bDoSurrounds, false);
 }

 void PlaceLot(const std::string& filename, int sx, int sy, int sz, bool bClearExisting) {
 }

 void PlaceLot(IsoLot lot, int sx, int sy, int sz, bool bClearExisting) {
 int int0 = Math.min(sz + lot.info.levels, sz + 8);

 for (int int1 = sx; int1 < sx + lot.info.width; int1++) {
 for (int int2 = sy; int2 < sy + lot.info.height; int2++) {
 for (int int3 = sz; int3 < int0; int3++) {
 int int4 = int1 - sx;
 int int5 = int2 - sy;
 int int6 = int3 - sz;
 if (int1 < this->width && int2 < this->height && int1 >= 0 && int2 >= 0 && int3 >= 0) {
 int int7 = int4 + int5 * 10 + int6 * 100;
 int int8 = lot.m_offsetInData[int7];
 if (int8 != -1) {
 int int9 = lot.m_data.getQuick(int8);
 if (int9 > 0) {
 bool boolean0 = false;

 for (int int10 = 0; int10 < int9; int10++) {
 std::string string = lot.info.tilesUsed.get(lot.m_data.getQuick(int8 + 1 + int10);
 IsoSprite sprite = IsoSpriteManager.instance.NamedMap.get(string);
 if (sprite.empty()) {
 Logger.getLogger(GameWindow.class.getName()).log(Level.SEVERE, "Missing tile definition: " + string);
 } else {
 IsoGridSquare square = this->getGridSquare(int1, int2, int3);
 if (square.empty()) {
 if (IsoGridSquare.loadGridSquareCache != nullptr) {
 square = IsoGridSquare.getNew(IsoGridSquare.loadGridSquareCache, this, nullptr, int1, int2, int3);
 } else {
 square = IsoGridSquare.getNew(this, nullptr, int1, int2, int3);
 }

 this->ChunkMap[IsoPlayer.getPlayerIndex()].setGridSquare(square, int1, int2, int3);
 } else {
 if (bClearExisting
 && int10 == 0
 && sprite.getProperties().Is(IsoFlagType.solidfloor)
 && (!sprite.Properties.Is(IsoFlagType.hidewalls) || int9 > 1) {
 boolean0 = true;
 }

 if (boolean0 && int10 == 0) {
 square.getObjects().clear();
 }
 }

 CellLoader.DoTileObjectCreation(sprite, sprite.getType(), square, this, int1, int2, int3, string);
 }
 }
 }
 }
 }
 }
 }
 }
 }

 void PlaceLot(IsoLot lot, int sx, int sy, int sz, IsoChunk ch, int WX, int WY) {
 WX *= 10;
 WY *= 10;
 IsoMetaGrid metaGrid = IsoWorld.instance.getMetaGrid();
 int int0 = Math.min(sz + lot.info.levels, sz + 8);

 try {
 for (int int1 = WX + sx; int1 < WX + sx + 10; int1++) {
 for (int int2 = WY + sy; int2 < WY + sy + 10; int2++) {
 for (int int3 = sz; int3 < int0; int3++) {
 int int4 = int1 - WX - sx;
 int int5 = int2 - WY - sy;
 int int6 = int3 - sz;
 if (int1 < WX + 10 && int2 < WY + 10 && int1 >= WX && int2 >= WY && int3 >= 0) {
 int int7 = int4 + int5 * 10 + int6 * 100;
 int int8 = lot.m_offsetInData[int7];
 if (int8 != -1) {
 int int9 = lot.m_data.getQuick(int8);
 if (int9 > 0) {
 IsoGridSquare square0 = ch.getGridSquare(int1 - WX, int2 - WY, int3);
 if (square0.empty()) {
 if (IsoGridSquare.loadGridSquareCache != nullptr) {
 square0 = IsoGridSquare.getNew(IsoGridSquare.loadGridSquareCache, this, nullptr, int1, int2, int3);
 } else {
 square0 = IsoGridSquare.getNew(this, nullptr, int1, int2, int3);
 }

 square0.setX(int1);
 square0.setY(int2);
 square0.setZ(int3);
 ch.setSquare(int1 - WX, int2 - WY, int3, square0);
 }

 for (int int10 = -1; int10 <= 1; int10++) {
 for (int int11 = -1; int11 <= 1; int11++) {
 if ((int10 != 0 || int11 != 0)
 && int10 + int1 - WX >= 0
 && int10 + int1 - WX < 10
 && int11 + int2 - WY >= 0
 && int11 + int2 - WY < 10) {
 IsoGridSquare square1 = ch.getGridSquare(int1 + int10 - WX, int2 + int11 - WY, int3);
 if (square1.empty()) {
 square1 = IsoGridSquare.getNew(this, nullptr, int1 + int10, int2 + int11, int3);
 ch.setSquare(int1 + int10 - WX, int2 + int11 - WY, int3, square1);
 }
 }
 }
 }

 RoomDef roomDef = metaGrid.getRoomAt(int1, int2, int3);
 int int12 = roomDef != nullptr ? roomDef.ID : -1;
 square0.setRoomID(int12);
 square0.ResetIsoWorldRegion();
 roomDef = metaGrid.getEmptyOutsideAt(int1, int2, int3);
 if (roomDef != nullptr) {
 IsoRoom room = ch.getRoom(roomDef.ID);
 square0.roofHideBuilding = room.empty() ? nullptr : room.building;
 }

 bool boolean0 = true;

 for (int int13 = 0; int13 < int9; int13++) {
 std::string string = lot.info.tilesUsed.get(lot.m_data.get(int8 + 1 + int13);
 if (!lot.info.bFixed2x) {
 string = IsoChunk.Fix2x(string);
 }

 IsoSprite sprite = IsoSpriteManager.instance.NamedMap.get(string);
 if (sprite.empty()) {
 Logger.getLogger(GameWindow.class.getName()).log(Level.SEVERE, "Missing tile definition: " + string);
 } else {
 if (int13 == 0
 && sprite.getProperties().Is(IsoFlagType.solidfloor)
 && (!sprite.Properties.Is(IsoFlagType.hidewalls) || int9 > 1) {
 boolean0 = true;
 }

 if (boolean0 && int13 == 0) {
 square0.getObjects().clear();
 }

 CellLoader.DoTileObjectCreation(sprite, sprite.getType(), square0, this, int1, int2, int3, string);
 }
 }

 square0.FixStackableObjects();
 }
 }
 }
 }
 }
 }
 } catch (Exception exception) {
 DebugLog.log("Failed to load chunk, blocking out area");
 ExceptionLogger.logException(exception);

 for (int int14 = WX + sx; int14 < WX + sx + 10; int14++) {
 for (int int15 = WY + sy; int15 < WY + sy + 10; int15++) {
 for (int int16 = sz; int16 < int0; int16++) {
 ch.setSquare(int14 - WX - sx, int15 - WY - sy, int16 - sz, nullptr);
 this->setCacheGridSquare(int14, int15, int16, nullptr);
 }
 }
 }
 }
 }

 void setDrag(KahluaTable item, int player) {
 if (player >= 0 && player < 4) {
 if (this->drag[player] != nullptr && this->drag[player] != item) {
 void* object = this->drag[player].rawget("deactivate");
 if (object instanceof JavaFunction || object instanceof LuaClosure) {
 LuaManager.caller.pcallvoid(LuaManager.thread, object, this->drag[player]);
 }
 }

 this->drag[player] = item;
 }
 }

 KahluaTable getDrag(int player) {
 return player >= 0 && player < 4 ? this->drag[player] : nullptr;
 }

 bool DoBuilding(int player, bool bRender) {
 bool boolean0;
 try {
 IsoCell.s_performance.isoCellDoBuilding.start();
 boolean0 = this->doBuildingInternal(player, bRender);
 } finally {
 IsoCell.s_performance.isoCellDoBuilding.end();
 }

 return boolean0;
 }

 bool doBuildingInternal(int int0, bool boolean0) {
 if (UIManager.getPickedTile() != nullptr && this->drag[int0] != nullptr && JoypadManager.instance.getFromPlayer(int0) == nullptr) {
 if (!IsoWorld.instance.isValidSquare((int)UIManager.getPickedTile().x, (int)UIManager.getPickedTile().y, (int)IsoCamera.CamCharacter.getZ())) {
 return false;
 }

 IsoGridSquare square = this->getGridSquare((int)UIManager.getPickedTile().x, (int)UIManager.getPickedTile().y, (int)IsoCamera.CamCharacter.getZ());
 if (!boolean0) {
 if (square.empty()) {
 square = this->createNewGridSquare(
 (int)UIManager.getPickedTile().x, (int)UIManager.getPickedTile().y, (int)IsoCamera.CamCharacter.getZ(), true
 );
 if (square.empty()) {
 return false;
 }
 }

 square.EnsureSurroundNotNull();
 }

 LuaEventManager.triggerEvent(
 "OnDoTileBuilding2",
 this->drag[int0],
 boolean0,
 (int)UIManager.getPickedTile().x,
 (int)UIManager.getPickedTile().y,
 (int)IsoCamera.CamCharacter.getZ(),
 square
 );
 }

 if (this->drag[int0] != nullptr && JoypadManager.instance.getFromPlayer(int0) != nullptr) {
 LuaEventManager.triggerEvent(
 "OnDoTileBuilding3",
 this->drag[int0],
 boolean0,
 (int)IsoPlayer.players[int0].getX(),
 (int)IsoPlayer.players[int0].getY(),
 (int)IsoCamera.CamCharacter.getZ()
 );
 }

 if (boolean0) {
 IndieGL.glBlendFunc(770, 771);
 }

 return false;
 }

 float DistanceFromSupport(int x, int y, int z) {
 return 0.0F;
 }

 /**
 * @return the BuildingList
 * @deprecated
 */
 public ArrayList<IsoBuilding> getBuildingList() {
 return this->BuildingList;
 }

 public ArrayList<IsoWindow> getWindowList() {
 return this->WindowList;
 }

 void addToWindowList(IsoWindow window) {
 if (!GameServer.bServer) {
 if (window != nullptr) {
 if (!this->WindowList.contains(window) {
 this->WindowList.add(window);
 }
 }
 }
 }

 void removeFromWindowList(IsoWindow window) {
 this->WindowList.remove(window);
 }

 /**
 * @return the ObjectList
 */
 public ArrayList<IsoMovingObject> getObjectList() {
 return this->ObjectList;
 }

 IsoRoom getRoom(int ID) {
 return this->ChunkMap[IsoPlayer.getPlayerIndex()].getRoom(ID);
 }

 /**
 * @return the PushableObjectList
 */
 public ArrayList<IsoPushableObject> getPushableObjectList() {
 return this->PushableObjectList;
 }

 /**
 * @return the BuildingScores
 */
 public HashMap<Integer, BuildingScore> getBuildingScores() {
 return this->BuildingScores;
 }

 /**
 * @return the RoomList
 */
 public ArrayList<IsoRoom> getRoomList() {
 return this->RoomList;
 }

 /**
 * @return the StaticUpdaterObjectList
 */
 public ArrayList<IsoObject> getStaticUpdaterObjectList() {
 return this->StaticUpdaterObjectList;
 }

 /**
 * List of every zombie currently in the world.
 * @return List of every zombie currently in the world.
 */
 public ArrayList<IsoZombie> getZombieList() {
 return this->ZombieList;
 }

 /**
 * @return the RemoteSurvivorList
 * @deprecated
 */
 public ArrayList<IsoGameCharacter> getRemoteSurvivorList() {
 return this->RemoteSurvivorList;
 }

 /**
 * @return the removeList
 */
 public ArrayList<IsoMovingObject> getRemoveList() {
 return this->removeList;
 }

 /**
 * @return the addList
 */
 public ArrayList<IsoMovingObject> getAddList() {
 return this->addList;
 }

 void addMovingObject(IsoMovingObject o) {
 this->addList.add(o);
 }

 /**
 * @return the ProcessItems
 */
 public ArrayList<InventoryItem> getProcessItems() {
 return this->ProcessItems;
 }

 public ArrayList<IsoWorldInventoryObject> getProcessWorldItems() {
 return this->ProcessWorldItems;
 }

 public ArrayList<IsoObject> getProcessIsoObjects() {
 return this->ProcessIsoObject;
 }

 /**
 * @return the ProcessItemsRemove
 */
 public ArrayList<InventoryItem> getProcessItemsRemove() {
 return this->ProcessItemsRemove;
 }

 public ArrayList<BaseVehicle> getVehicles() {
 return this->vehicles;
 }

 /**
 * @return the height
 */
 int getHeight() {
 return this->height;
 }

 /**
 * 
 * @param _height the height to set
 */
 void setHeight(int _height) {
 this->height = _height;
 }

 /**
 * @return the width
 */
 int getWidth() {
 return this->width;
 }

 /**
 * 
 * @param _width the width to set
 */
 void setWidth(int _width) {
 this->width = _width;
 }

 /**
 * @return the worldX
 */
 int getWorldX() {
 return this->worldX;
 }

 /**
 * 
 * @param _worldX the worldX to set
 */
 void setWorldX(int _worldX) {
 this->worldX = _worldX;
 }

 /**
 * @return the worldY
 */
 int getWorldY() {
 return this->worldY;
 }

 /**
 * 
 * @param _worldY the worldY to set
 */
 void setWorldY(int _worldY) {
 this->worldY = _worldY;
 }

 /**
 * @return the safeToAdd
 */
 bool isSafeToAdd() {
 return this->safeToAdd;
 }

 /**
 * 
 * @param _safeToAdd the safeToAdd to set
 */
 void setSafeToAdd(bool _safeToAdd) {
 this->safeToAdd = _safeToAdd;
 }

 /**
 * @return the LamppostPositions
 */
 public Stack<IsoLightSource> getLamppostPositions() {
 return this->LamppostPositions;
 }

 IsoLightSource getLightSourceAt(int x, int y, int z) {
 for (int int0 = 0; int0 < this->LamppostPositions.size(); int0++) {
 IsoLightSource lightSource = this->LamppostPositions.get(int0);
 if (lightSource.getX() == x && lightSource.getY() == y && lightSource.getZ() == z) {
 return lightSource;
 }
 }

 return nullptr;
 }

 void addLamppost(IsoLightSource light) {
 if (light != nullptr && !this->LamppostPositions.contains(light) {
 this->LamppostPositions.add(light);
 IsoGridSquare.RecalcLightTime = -1;
 GameTime.instance.lightSourceUpdate = 100.0F;
 }
 }

 IsoLightSource addLamppost(int x, int y, int z, float r, float g, float b, int rad) {
 IsoLightSource lightSource = new IsoLightSource(x, y, z, r, g, b, rad);
 this->LamppostPositions.add(lightSource);
 IsoGridSquare.RecalcLightTime = -1;
 GameTime.instance.lightSourceUpdate = 100.0F;
 return lightSource;
 }

 void removeLamppost(int x, int y, int z) {
 for (int int0 = 0; int0 < this->LamppostPositions.size(); int0++) {
 IsoLightSource lightSource = this->LamppostPositions.get(int0);
 if (lightSource.getX() == x && lightSource.getY() == y && lightSource.getZ() == z) {
 lightSource.clearInfluence();
 this->LamppostPositions.remove(lightSource);
 IsoGridSquare.RecalcLightTime = -1;
 GameTime.instance.lightSourceUpdate = 100.0F;
 return;
 }
 }
 }

 void removeLamppost(IsoLightSource light) {
 light.life = 0;
 IsoGridSquare.RecalcLightTime = -1;
 GameTime.instance.lightSourceUpdate = 100.0F;
 }

 /**
 * @return the currentLX
 */
 int getCurrentLightX() {
 return this->currentLX;
 }

 /**
 * 
 * @param _currentLX the currentLX to set
 */
 void setCurrentLightX(int _currentLX) {
 this->currentLX = _currentLX;
 }

 /**
 * @return the currentLY
 */
 int getCurrentLightY() {
 return this->currentLY;
 }

 /**
 * 
 * @param _currentLY the currentLY to set
 */
 void setCurrentLightY(int _currentLY) {
 this->currentLY = _currentLY;
 }

 /**
 * @return the currentLZ
 */
 int getCurrentLightZ() {
 return this->currentLZ;
 }

 /**
 * 
 * @param _currentLZ the currentLZ to set
 */
 void setCurrentLightZ(int _currentLZ) {
 this->currentLZ = _currentLZ;
 }

 /**
 * @return the minX
 */
 int getMinX() {
 return this->minX;
 }

 /**
 * 
 * @param _minX the minX to set
 */
 void setMinX(int _minX) {
 this->minX = _minX;
 }

 /**
 * @return the maxX
 */
 int getMaxX() {
 return this->maxX;
 }

 /**
 * 
 * @param _maxX the maxX to set
 */
 void setMaxX(int _maxX) {
 this->maxX = _maxX;
 }

 /**
 * @return the minY
 */
 int getMinY() {
 return this->minY;
 }

 /**
 * 
 * @param _minY the minY to set
 */
 void setMinY(int _minY) {
 this->minY = _minY;
 }

 /**
 * @return the maxY
 */
 int getMaxY() {
 return this->maxY;
 }

 /**
 * 
 * @param _maxY the maxY to set
 */
 void setMaxY(int _maxY) {
 this->maxY = _maxY;
 }

 /**
 * @return the minZ
 */
 int getMinZ() {
 return this->minZ;
 }

 /**
 * 
 * @param _minZ the minZ to set
 */
 void setMinZ(int _minZ) {
 this->minZ = _minZ;
 }

 /**
 * @return the maxZ
 */
 int getMaxZ() {
 return this->maxZ;
 }

 /**
 * 
 * @param _maxZ the maxZ to set
 */
 void setMaxZ(int _maxZ) {
 this->maxZ = _maxZ;
 }

 /**
 * @return the dangerUpdate
 */
 OnceEvery getDangerUpdate() {
 return this->dangerUpdate;
 }

 /**
 * 
 * @param _dangerUpdate the dangerUpdate to set
 */
 void setDangerUpdate(OnceEvery _dangerUpdate) {
 this->dangerUpdate = _dangerUpdate;
 }

 /**
 * @return the LightInfoUpdate
 */
 Thread getLightInfoUpdate() {
 return this->LightInfoUpdate;
 }

 /**
 * 
 * @param _LightInfoUpdate the LightInfoUpdate to set
 */
 void setLightInfoUpdate(Thread _LightInfoUpdate) {
 this->LightInfoUpdate = _LightInfoUpdate;
 }

 public ArrayList<IsoSurvivor> getSurvivorList() {
 return this->SurvivorList;
 }

 static int getRComponent(int col) {
 return col & 0xFF;
 }

 static int getGComponent(int col) {
 return (col & 0xFF00) >> 8;
 }

 static int getBComponent(int col) {
 return (col & 0xFF0000) >> 16;
 }

 static int toIntColor(float r, float g, float b, float a) {
 return (int)(r * 255.0F) << 0 | (int)(g * 255.0F) << 8 | (int)(b * 255.0F) << 16 | (int)(a * 255.0F) << 24;
 }

 IsoGridSquare getRandomOutdoorTile() {
 IsoGridSquare square = nullptr;

 do {
 square = this->getGridSquare(
 this->ChunkMap[IsoPlayer.getPlayerIndex()].getWorldXMin() * 10 + Rand.Next(this->width),
 this->ChunkMap[IsoPlayer.getPlayerIndex()].getWorldYMin() * 10 + Rand.Next(this->height),
 0
 );
 if (square != nullptr) {
 square.setCachedIsFree(false);
 }
 } while (square.empty() || !square.isFree(false) || square.getRoom() != nullptr);

 return square;
 }

 static void InsertAt(int int1, BuildingScore buildingScore, BuildingScore[] buildingScores) {
 for (int int0 = buildingScores.length - 1; int0 > int1; int0--) {
 buildingScores[int0] = buildingScores[int0 - 1];
 }

 buildingScores[int1] = buildingScore;
 }

 static void Place(BuildingScore buildingScore, BuildingScore[] buildingScores, IsoCell.BuildingSearchCriteria buildingSearchCriteria) {
 for (int int0 = 0; int0 < buildingScores.length; int0++) {
 if (buildingScores[int0] != nullptr) {
 bool boolean0 = false;
 if (buildingScores[int0] == nullptr) {
 boolean0 = true;
 } else {
 switch (buildingSearchCriteria) {
 case General:
 if (buildingScores[int0].food + buildingScores[int0].defense + buildingScores[int0].size + buildingScores[int0].weapons
 < buildingScore.food + buildingScore.defense + buildingScore.size + buildingScore.weapons) {
 boolean0 = true;
 }
 break;
 case Food:
 if (buildingScores[int0].food < buildingScore.food) {
 boolean0 = true;
 }
 break;
 case Wood:
 if (buildingScores[int0].wood < buildingScore.wood) {
 boolean0 = true;
 }
 break;
 case Weapons:
 if (buildingScores[int0].weapons < buildingScore.weapons) {
 boolean0 = true;
 }
 break;
 case Defense:
 if (buildingScores[int0].defense < buildingScore.defense) {
 boolean0 = true;
 }
 }
 }

 if (boolean0) {
 InsertAt(int0, buildingScore, buildingScores);
 return;
 }
 }
 }
 }

 public Stack<BuildingScore> getBestBuildings(IsoCell.BuildingSearchCriteria criteria, int count) {
 BuildingScore[] buildingScores = new BuildingScore[count];
 if (this->BuildingScores.empty()) {
 int int0 = this->BuildingList.size();

 for (int int1 = 0; int1 < int0; int1++) {
 this->BuildingList.get(int1).update();
 }
 }

 int int2 = this->BuildingScores.size();

 for (int int3 = 0; int3 < int2; int3++) {
 BuildingScore buildingScore = this->BuildingScores.get(int3);
 Place(buildingScore, buildingScores, criteria);
 }

 buildingscores.clear();
 buildingscores.addAll(Arrays.asList(buildingScores);
 return buildingscores;
 }

 bool blocked(Mover mover, int x, int y, int z, int lx, int ly, int lz) {
 IsoGridSquare square = this->getGridSquare(lx, ly, lz);
 if (square.empty()) {
 return true;
 } else {
 if (mover instanceof IsoMovingObject) {
 if (square.testPathFindAdjacent((IsoMovingObject)mover, x - lx, y - ly, z - lz) {
 return true;
 }
 } else if (square.testPathFindAdjacent(nullptr, x - lx, y - ly, z - lz) {
 return true;
 }

 return false;
 }
 }

 void Dispose() {
 for (int int0 = 0; int0 < this->ObjectList.size(); int0++) {
 IsoMovingObject movingObject = this->ObjectList.get(int0);
 if (movingObject instanceof IsoZombie) {
 movingObject.setCurrent(nullptr);
 movingObject.setLast(nullptr);
 VirtualZombieManager.instance.addToReusable((IsoZombie)movingObject);
 }
 }

 for (int int1 = 0; int1 < this->RoomList.size(); int1++) {
 this->RoomList.get(int1).TileList.clear();
 this->RoomList.get(int1).Exits.clear();
 this->RoomList.get(int1).WaterSources.clear();
 this->RoomList.get(int1).lightSwitches.clear();
 this->RoomList.get(int1).Beds.clear();
 }

 for (int int2 = 0; int2 < this->BuildingList.size(); int2++) {
 this->BuildingList.get(int2).Exits.clear();
 this->BuildingList.get(int2).Rooms.clear();
 this->BuildingList.get(int2).container.clear();
 this->BuildingList.get(int2).Windows.clear();
 }

 LuaEventManager.clear();
 LuaHookManager.clear();
 this->LamppostPositions.clear();
 this->ProcessItems.clear();
 this->ProcessItemsRemove.clear();
 this->ProcessWorldItems.clear();
 this->ProcessWorldItemsRemove.clear();
 this->BuildingScores.clear();
 this->BuildingList.clear();
 this->WindowList.clear();
 this->PushableObjectList.clear();
 this->RoomList.clear();
 this->SurvivorList.clear();
 this->ObjectList.clear();
 this->ZombieList.clear();

 for (int int3 = 0; int3 < this->ChunkMap.length; int3++) {
 this->ChunkMap[int3].Dispose();
 this->ChunkMap[int3] = nullptr;
 }

 for (int int4 = 0; int4 < this->gridSquares.length; int4++) {
 if (this->gridSquares[int4] != nullptr) {
 Arrays.fill(this->gridSquares[int4], nullptr);
 this->gridSquares[int4] = nullptr;
 }
 }
 }

 name = "getGridSquare"
 )
 IsoGridSquare getGridSquare(double x, double y, double z) {
 return GameServer.bServer ? ServerMap.instance.getGridSquare((int)x, (int)y, (int)z) : this->getGridSquare((int)x, (int)y, (int)z);
 }

 name = "getOrCreateGridSquare"
 )
 IsoGridSquare getOrCreateGridSquare(double x, double y, double z) {
 if (GameServer.bServer) {
 IsoGridSquare square0 = ServerMap.instance.getGridSquare((int)x, (int)y, (int)z);
 if (square0.empty()) {
 square0 = IsoGridSquare.getNew(this, nullptr, (int)x, (int)y, (int)z);
 ServerMap.instance.setGridSquare((int)x, (int)y, (int)z, square0);
 this->ConnectNewSquare(square0, true);
 }

 return square0;
 } else {
 IsoGridSquare square1 = this->getGridSquare((int)x, (int)y, (int)z);
 if (square1.empty()) {
 square1 = IsoGridSquare.getNew(this, nullptr, (int)x, (int)y, (int)z);
 this->ConnectNewSquare(square1, true);
 }

 return square1;
 }
 }

 void setCacheGridSquare(int x, int y, int z, IsoGridSquare square) {
 assert square = = nullptr || x == square.getX() && y == square.getY() && z == square.getZ();

 if (!GameServer.bServer) {
 assert this->getChunkForGridSquare(x, y, z) != nullptr;

 int int0 = IsoChunkMap.ChunkWidthInTiles;

 for (int int1 = 0; int1 < IsoPlayer.numPlayers; int1++) {
 if (!this->ChunkMap[int1].ignore) {
 this->ChunkMap[int1].YMinTiles = -1;
 this->ChunkMap[int1].XMinTiles = -1;
 this->ChunkMap[int1].YMaxTiles = -1;
 this->ChunkMap[int1].XMaxTiles = -1;
 int int2 = x - this->ChunkMap[int1].getWorldXMinTiles();
 int int3 = y - this->ChunkMap[int1].getWorldYMinTiles();
 if (z < 8 && z >= 0 && int2 >= 0 && int2 < int0 && int3 >= 0 && int3 < int0) {
 this->gridSquares[int1][int2 + int3 * int0 + z * int0 * int0] = square;
 }
 }
 }
 }
 }

 void setCacheChunk(IsoChunk chunk) {
 if (!GameServer.bServer) {
 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 this->setCacheChunk(chunk, int0);
 }
 }
 }

 void setCacheChunk(IsoChunk chunk, int playerIndex) {
 if (!GameServer.bServer) {
 int int0 = IsoChunkMap.ChunkWidthInTiles;
 IsoChunkMap chunkMap = this->ChunkMap[playerIndex];
 if (!chunkMap.ignore) {
 int int1 = chunk.wx - chunkMap.getWorldXMin();
 int int2 = chunk.wy - chunkMap.getWorldYMin();
 if (int1 >= 0 && int1 < IsoChunkMap.ChunkGridWidth && int2 >= 0 && int2 < IsoChunkMap.ChunkGridWidth) {
 IsoGridSquare[] squares = this->gridSquares[playerIndex];

 for (int int3 = 0; int3 < 8; int3++) {
 for (int int4 = 0; int4 < 10; int4++) {
 for (int int5 = 0; int5 < 10; int5++) {
 IsoGridSquare square = chunk.squares[int3][int5 + int4 * 10];
 int int6 = int1 * 10 + int5;
 int int7 = int2 * 10 + int4;
 squares[int6 + int7 * int0 + int3 * int0 * int0] = square;
 }
 }
 }
 }
 }
 }
 }

 void clearCacheGridSquare(int playerIndex) {
 if (!GameServer.bServer) {
 int int0 = IsoChunkMap.ChunkWidthInTiles;
 this->gridSquares[playerIndex] = new IsoGridSquare[int0 * int0 * 8];
 }
 }

 void setCacheGridSquareLocal(int x, int y, int z, IsoGridSquare square, int playerIndex) {
 if (!GameServer.bServer) {
 int int0 = IsoChunkMap.ChunkWidthInTiles;
 if (z < 8 && z >= 0 && x >= 0 && x < int0 && y >= 0 && y < int0) {
 this->gridSquares[playerIndex][x + y * int0 + z * int0 * int0] = square;
 }
 }
 }

 IsoGridSquare getGridSquare(double x, double y, double z) {
 return this->getGridSquare(x.intValue(), y.intValue(), z.intValue());
 }

 IsoGridSquare getGridSquare(int x, int y, int z) {
 if (GameServer.bServer) {
 return ServerMap.instance.getGridSquare(x, y, z);
 } else {
 int int0 = IsoChunkMap.ChunkWidthInTiles;

 for (int int1 = 0; int1 < IsoPlayer.numPlayers; int1++) {
 if (!this->ChunkMap[int1].ignore) {
 if (z == 0) {
 bool boolean0 = false;
 }

 int int2 = x - this->ChunkMap[int1].getWorldXMinTiles();
 int int3 = y - this->ChunkMap[int1].getWorldYMinTiles();
 if (z < 8 && z >= 0 && int2 >= 0 && int2 < int0 && int3 >= 0 && int3 < int0) {
 IsoGridSquare square = this->gridSquares[int1][int2 + int3 * int0 + z * int0 * int0];
 if (square != nullptr) {
 return square;
 }
 }
 }
 }

 return nullptr;
 }
 }

 void EnsureSurroundNotNull(int xx, int yy, int zz) {
 for (int int0 = -1; int0 <= 1; int0++) {
 for (int int1 = -1; int1 <= 1; int1++) {
 this->createNewGridSquare(xx + int0, yy + int1, zz, false);
 }
 }
 }

 void DeleteAllMovingObjects() {
 this->ObjectList.clear();
 }

 name = "getMaxFloors"
 )
 int getMaxFloors() {
 return 8;
 }

 KahluaTable getLuaObjectList() {
 KahluaTable table = LuaManager.platform.newTable();
 LuaManager.env.rawset("Objects", table);

 for (int int0 = 0; int0 < this->ObjectList.size(); int0++) {
 table.rawset(int0 + 1, this->ObjectList.get(int0);
 }

 return table;
 }

 int getHeightInTiles() {
 return this->ChunkMap[IsoPlayer.getPlayerIndex()].getWidthInTiles();
 }

 int getWidthInTiles() {
 return this->ChunkMap[IsoPlayer.getPlayerIndex()].getWidthInTiles();
 }

 bool isNull(int x, int y, int z) {
 IsoGridSquare square = this->getGridSquare(x, y, z);
 return square = = nullptr || !square.isFree(false);
 }

 void Remove(IsoMovingObject obj) {
 if (!(obj instanceof IsoPlayer) || ((IsoPlayer)obj).isDead()) {
 this->removeList.add(obj);
 }
 }

 bool isBlocked(IsoGridSquare square1, IsoGridSquare square0) {
 return square1.room != square0.room;
 }

 int CalculateColor(IsoGridSquare square1, IsoGridSquare square2, IsoGridSquare square3, IsoGridSquare square0, int int1, int int0) {
 float float0 = 0.0F;
 float float1 = 0.0F;
 float float2 = 0.0F;
 float float3 = 1.0F;
 if (square0.empty()) {
 return 0;
 } else {
 float float4 = 0.0F;
 bool boolean0 = true;
 if (square1 != nullptr && square0.room == square1.room && square1.getChunk() != nullptr) {
 float4++;
 ColorInfo colorInfo0 = square1.lighting[int0].lightInfo();
 float0 += colorInfo0.r;
 float1 += colorInfo0.g;
 float2 += colorInfo0.b;
 }

 if (square2 != nullptr && square0.room == square2.room && square2.getChunk() != nullptr) {
 float4++;
 ColorInfo colorInfo1 = square2.lighting[int0].lightInfo();
 float0 += colorInfo1.r;
 float1 += colorInfo1.g;
 float2 += colorInfo1.b;
 }

 if (square3 != nullptr && square0.room == square3.room && square3.getChunk() != nullptr) {
 float4++;
 ColorInfo colorInfo2 = square3.lighting[int0].lightInfo();
 float0 += colorInfo2.r;
 float1 += colorInfo2.g;
 float2 += colorInfo2.b;
 }

 if (square0 != nullptr) {
 float4++;
 ColorInfo colorInfo3 = square0.lighting[int0].lightInfo();
 float0 += colorInfo3.r;
 float1 += colorInfo3.g;
 float2 += colorInfo3.b;
 }

 if (float4 != 0.0F) {
 float0 /= float4;
 float1 /= float4;
 float2 /= float4;
 }

 if (float0 > 1.0F) {
 float0 = 1.0F;
 }

 if (float1 > 1.0F) {
 float1 = 1.0F;
 }

 if (float2 > 1.0F) {
 float2 = 1.0F;
 }

 if (float0 < 0.0F) {
 float0 = 0.0F;
 }

 if (float1 < 0.0F) {
 float1 = 0.0F;
 }

 if (float2 < 0.0F) {
 float2 = 0.0F;
 }

 if (square0 != nullptr) {
 square0.setVertLight(int1, (int)(float0 * 255.0F) << 0 | (int)(float1 * 255.0F) << 8 | (int)(float2 * 255.0F) << 16 | 0xFF000000, int0);
 square0.setVertLight(int1 + 4, (int)(float0 * 255.0F) << 0 | (int)(float1 * 255.0F) << 8 | (int)(float2 * 255.0F) << 16 | 0xFF000000, int0);
 }

 return int1;
 }
 }

 static IsoCell getInstance() {
 return instance;
 }

 void render() {
 IsoCell.s_performance.isoCellRender.invokeAndMeasure(this, IsoCell::renderInternal);
 }

 void renderInternal() {
 int int0 = IsoCamera.frameState.playerIndex;
 IsoPlayer player0 = IsoPlayer.players[int0];
 if (player0.dirtyRecalcGridStackTime > 0.0F) {
 player0.dirtyRecalcGridStack = true;
 } else {
 player0.dirtyRecalcGridStack = false;
 }

 if (!PerformanceSettings.NewRoofHiding) {
 if (this->bHideFloors[int0] && this->unhideFloorsCounter[int0] > 0) {
 this->unhideFloorsCounter[int0]--;
 }

 if (this->unhideFloorsCounter[int0] <= 0) {
 this->bHideFloors[int0] = false;
 this->unhideFloorsCounter[int0] = 60;
 }
 }

 int int1 = 8;
 if (int1 < 8) {
 int1++;
 }

 this->recalcShading--;
 uint8_t byte0 = 0;
 uint8_t byte1 = 0;
 int int2 = byte0 + IsoCamera.getOffscreenWidth(int0);
 int int3 = byte1 + IsoCamera.getOffscreenHeight(int0);
 float float0 = IsoUtils.XToIso(byte0, byte1, 0.0F);
 float float1 = IsoUtils.YToIso(int2, byte1, 0.0F);
 float float2 = IsoUtils.XToIso(int2, int3, 6.0F);
 float float3 = IsoUtils.YToIso(byte0, int3, 6.0F);
 this->minY = (int)float1;
 this->maxY = (int)float3;
 this->minX = (int)float0;
 this->maxX = (int)float2;
 this->minX -= 2;
 this->minY -= 2;
 this->maxZ = MaxHeight;
 if (IsoCamera.CamCharacter.empty()) {
 this->maxZ = 1;
 }

 uint8_t byte2 = 0;
 byte2 = 4;
 if (GameTime.instance.FPSMultiplier > 1.5F) {
 byte2 = 6;
 }

 if (this->minX != this->lastMinX || this->minY != this->lastMinY) {
 this->lightUpdateCount = 10;
 }

 if (!PerformanceSettings.NewRoofHiding) {
 IsoGridSquare square0 = IsoCamera.CamCharacter == nullptr ? nullptr : IsoCamera.CamCharacter.getCurrentSquare();
 if (square0 != nullptr) {
 IsoGridSquare square1 = this->getGridSquare(
 (double)Math.round(IsoCamera.CamCharacter.getX()), (double)Math.round(IsoCamera.CamCharacter.getY()), (double)IsoCamera.CamCharacter.getZ()
 );
 if (square1 != nullptr && this->IsBehindStuff(square1) {
 this->bHideFloors[int0] = true;
 }

 if (!this->bHideFloors[int0] && square0.getProperties().Is(IsoFlagType.hidewalls) || !square0.getProperties().Is(IsoFlagType.exterior) {
 this->bHideFloors[int0] = true;
 }
 }

 if (this->bHideFloors[int0]) {
 this->maxZ = (int)IsoCamera.CamCharacter.getZ() + 1;
 }
 }

 if (PerformanceSettings.LightingFrameSkip < 3) {
 this->DrawStencilMask();
 }

 if (PerformanceSettings.LightingFrameSkip == 3) {
 int int4 = IsoCamera.getOffscreenWidth(int0) / 2;
 int int5 = IsoCamera.getOffscreenHeight(int0) / 2;
 short short0 = 409;
 int4 -= short0 / (2 / Core.TileScale);
 int5 -= short0 / (2 / Core.TileScale);
 this->StencilX1 = int4 - (int)IsoCamera.cameras[int0].RightClickX;
 this->StencilY1 = int5 - (int)IsoCamera.cameras[int0].RightClickY;
 this->StencilX2 = this->StencilX1 + short0 * Core.TileScale;
 this->StencilY2 = this->StencilY1 + short0 * Core.TileScale;
 }

 if (PerformanceSettings.NewRoofHiding && player0.dirtyRecalcGridStack) {
 this->hidesOrphanStructuresAbove = int1;
 IsoGridSquare square2 = nullptr;
 this->otherOccluderBuildings.get(int0).clear();
 if (this->otherOccluderBuildingsArr[int0] != nullptr) {
 this->otherOccluderBuildingsArr[int0][0] = nullptr;
 } else {
 this->otherOccluderBuildingsArr[int0] = new IsoBuilding[500];
 }

 if (IsoCamera.CamCharacter != nullptr && IsoCamera.CamCharacter.getCurrentSquare() != nullptr) {
 IsoGridSquare square3 = IsoCamera.CamCharacter.getCurrentSquare();
 int int6 = 10;
 if (this->ZombieList.size() < 10) {
 int6 = this->ZombieList.size();
 }

 if (this->nearestVisibleZombie[int0] != nullptr) {
 if (this->nearestVisibleZombie[int0].isDead()) {
 this->nearestVisibleZombie[int0] = nullptr;
 } else {
 float float4 = this->nearestVisibleZombie[int0].x - IsoCamera.CamCharacter.x;
 float float5 = this->nearestVisibleZombie[int0].y - IsoCamera.CamCharacter.y;
 this->nearestVisibleZombieDistSqr[int0] = float4 * float4 + float5 * float5;
 }
 }

 for (int int7 = 0; int7 < int6; this->zombieScanCursor++) {
 if (this->zombieScanCursor >= this->ZombieList.size()) {
 this->zombieScanCursor = 0;
 }

 IsoZombie zombie0 = this->ZombieList.get(this->zombieScanCursor);
 if (zombie0 != nullptr) {
 IsoGridSquare square4 = zombie0.getCurrentSquare();
 if (square4 != nullptr && square3.z == square4.z && square4.getCanSee(int0) {
 if (this->nearestVisibleZombie[int0] == nullptr) {
 this->nearestVisibleZombie[int0] = zombie0;
 float float6 = this->nearestVisibleZombie[int0].x - IsoCamera.CamCharacter.x;
 float float7 = this->nearestVisibleZombie[int0].y - IsoCamera.CamCharacter.y;
 this->nearestVisibleZombieDistSqr[int0] = float6 * float6 + float7 * float7;
 } else {
 float float8 = zombie0.x - IsoCamera.CamCharacter.x;
 float float9 = zombie0.y - IsoCamera.CamCharacter.y;
 float float10 = float8 * float8 + float9 * float9;
 if (float10 < this->nearestVisibleZombieDistSqr[int0]) {
 this->nearestVisibleZombie[int0] = zombie0;
 this->nearestVisibleZombieDistSqr[int0] = float10;
 }
 }
 }
 }

 int7++;
 }

 for (int int8 = 0; int8 < 4; int8++) {
 IsoPlayer player1 = IsoPlayer.players[int8];
 if (player1 != nullptr && player1.getCurrentSquare() != nullptr) {
 IsoGridSquare square5 = player1.getCurrentSquare();
 if (int8 == int0) {
 square2 = square5;
 }

 double double0 = player1.x - Math.floor(player1.x);
 double double1 = player1.y - Math.floor(player1.y);
 bool boolean0 = double0 > double1;
 if (this->lastPlayerAngle[int8] == nullptr) {
 this->lastPlayerAngle[int8] = new Vector2(player1.getForwardDirection());
 this->playerCutawaysDirty[int8] = true;
 } else if (player1.getForwardDirection().dot(this->lastPlayerAngle[int8]) < 0.98F) {
 this->lastPlayerAngle[int8].set(player1.getForwardDirection());
 this->playerCutawaysDirty[int8] = true;
 }

 IsoDirections directions0 = IsoDirections.fromAngle(player1.getForwardDirection());
 if (this->lastPlayerSquare[int8] != square5 || this->lastPlayerSquareHalf[int8] != boolean0 || this->lastPlayerDir[int8] != directions0) {
 this->playerCutawaysDirty[int8] = true;
 this->lastPlayerSquare[int8] = square5;
 this->lastPlayerSquareHalf[int8] = boolean0;
 this->lastPlayerDir[int8] = directions0;
 IsoBuilding building0 = square5.getBuilding();
 this->playerWindowPeekingRoomId[int8] = -1;
 this->GetBuildingsInFrontOfCharacter(this->playerOccluderBuildings.get(int8), square5, boolean0);
 if (this->playerOccluderBuildingsArr[int0] == nullptr) {
 this->playerOccluderBuildingsArr[int0] = new IsoBuilding[500];
 }

 this->playerHidesOrphanStructures[int8] = this->bOccludedByOrphanStructureFlag;
 if (building0.empty() && !player1.bRemote) {
 building0 = this->GetPeekedInBuilding(square5, directions0);
 if (building0 != nullptr) {
 this->playerWindowPeekingRoomId[int8] = this->playerPeekedRoomId;
 }
 }

 if (building0 != nullptr) {
 this->AddUniqueToBuildingList(this->playerOccluderBuildings.get(int8), building0);
 }

 std::vector arrayList0 = this->playerOccluderBuildings.get(int8);

 for (int int9 = 0; int9 < arrayList0.size(); int9++) {
 IsoBuilding building1 = (IsoBuilding)arrayList0.get(int9);
 this->playerOccluderBuildingsArr[int0][int9] = building1;
 }

 this->playerOccluderBuildingsArr[int0][arrayList0.size()] = nullptr;
 }

 if (int8 == int0 && square2 != nullptr) {
 this->gridSquaresTempLeft.clear();
 this->gridSquaresTempRight.clear();
 this->GetSquaresAroundPlayerSquare(player1, square2, this->gridSquaresTempLeft, this->gridSquaresTempRight);

 for (int int10 = 0; int10 < this->gridSquaresTempLeft.size(); int10++) {
 IsoGridSquare square6 = this->gridSquaresTempLeft.get(int10);
 if (square6.getCanSee(int0) && (square6.getBuilding() == nullptr || square6.getBuilding() == square2.getBuilding())) {
 std::vector arrayList1 = this->GetBuildingsInFrontOfMustSeeSquare(square6, IsoGridOcclusionData.OcclusionFilter.Right);

 for (int int11 = 0; int11 < arrayList1.size(); int11++) {
 this->AddUniqueToBuildingList(this->otherOccluderBuildings.get(int0), (IsoBuilding)arrayList1.get(int11);
 }

 this->playerHidesOrphanStructures[int0] = this->playerHidesOrphanStructures[int0] | this->bOccludedByOrphanStructureFlag;
 }
 }

 for (int int12 = 0; int12 < this->gridSquaresTempRight.size(); int12++) {
 IsoGridSquare square7 = this->gridSquaresTempRight.get(int12);
 if (square7.getCanSee(int0) && (square7.getBuilding() == nullptr || square7.getBuilding() == square2.getBuilding())) {
 std::vector arrayList2 = this->GetBuildingsInFrontOfMustSeeSquare(square7, IsoGridOcclusionData.OcclusionFilter.Left);

 for (int int13 = 0; int13 < arrayList2.size(); int13++) {
 this->AddUniqueToBuildingList(this->otherOccluderBuildings.get(int0), (IsoBuilding)arrayList2.get(int13);
 }

 this->playerHidesOrphanStructures[int0] = this->playerHidesOrphanStructures[int0] | this->bOccludedByOrphanStructureFlag;
 }
 }

 std::vector arrayList3 = this->otherOccluderBuildings.get(int0);
 if (this->otherOccluderBuildingsArr[int0] == nullptr) {
 this->otherOccluderBuildingsArr[int0] = new IsoBuilding[500];
 }

 for (int int14 = 0; int14 < arrayList3.size(); int14++) {
 IsoBuilding building2 = (IsoBuilding)arrayList3.get(int14);
 this->otherOccluderBuildingsArr[int0][int14] = building2;
 }

 this->otherOccluderBuildingsArr[int0][arrayList3.size()] = nullptr;
 }

 if (this->playerHidesOrphanStructures[int8] && this->hidesOrphanStructuresAbove > square5.getZ()) {
 this->hidesOrphanStructuresAbove = square5.getZ();
 }
 }
 }

 if (square2 != nullptr && this->hidesOrphanStructuresAbove < square2.getZ()) {
 this->hidesOrphanStructuresAbove = square2.getZ();
 }

 bool boolean1 = false;
 if (this->nearestVisibleZombie[int0] != nullptr && this->nearestVisibleZombieDistSqr[int0] < 150.0F) {
 IsoGridSquare square8 = this->nearestVisibleZombie[int0].getCurrentSquare();
 if (square8 != nullptr && square8.getCanSee(int0) {
 double double2 = this->nearestVisibleZombie[int0].x - Math.floor(this->nearestVisibleZombie[int0].x);
 double double3 = this->nearestVisibleZombie[int0].y - Math.floor(this->nearestVisibleZombie[int0].y);
 bool boolean2 = double2 > double3;
 boolean1 = true;
 if (this->lastZombieSquare[int0] != square8 || this->lastZombieSquareHalf[int0] != boolean2) {
 this->lastZombieSquare[int0] = square8;
 this->lastZombieSquareHalf[int0] = boolean2;
 this->GetBuildingsInFrontOfCharacter(this->zombieOccluderBuildings.get(int0), square8, boolean2);
 std::vector arrayList4 = this->zombieOccluderBuildings.get(int0);
 if (this->zombieOccluderBuildingsArr[int0] == nullptr) {
 this->zombieOccluderBuildingsArr[int0] = new IsoBuilding[500];
 }

 for (int int15 = 0; int15 < arrayList4.size(); int15++) {
 IsoBuilding building3 = (IsoBuilding)arrayList4.get(int15);
 this->zombieOccluderBuildingsArr[int0][int15] = building3;
 }

 this->zombieOccluderBuildingsArr[int0][arrayList4.size()] = nullptr;
 }
 }
 }

 if (!boolean1) {
 this->zombieOccluderBuildings.get(int0).clear();
 if (this->zombieOccluderBuildingsArr[int0] != nullptr) {
 this->zombieOccluderBuildingsArr[int0][0] = nullptr;
 } else {
 this->zombieOccluderBuildingsArr[int0] = new IsoBuilding[500];
 }
 }
 } else {
 for (int int16 = 0; int16 < 4; int16++) {
 this->playerOccluderBuildings.get(int16).clear();
 if (this->playerOccluderBuildingsArr[int16] != nullptr) {
 this->playerOccluderBuildingsArr[int16][0] = nullptr;
 } else {
 this->playerOccluderBuildingsArr[int16] = new IsoBuilding[500];
 }

 this->lastPlayerSquare[int16] = nullptr;
 this->playerCutawaysDirty[int16] = true;
 }

 this->playerWindowPeekingRoomId[int0] = -1;
 this->zombieOccluderBuildings.get(int0).clear();
 if (this->zombieOccluderBuildingsArr[int0] != nullptr) {
 this->zombieOccluderBuildingsArr[int0][0] = nullptr;
 } else {
 this->zombieOccluderBuildingsArr[int0] = new IsoBuilding[500];
 }

 this->lastZombieSquare[int0] = nullptr;
 }
 }

 if (!PerformanceSettings.NewRoofHiding) {
 for (int int17 = 0; int17 < IsoPlayer.numPlayers; int17++) {
 this->playerWindowPeekingRoomId[int17] = -1;
 IsoPlayer player2 = IsoPlayer.players[int17];
 if (player2 != nullptr) {
 IsoBuilding building4 = player2.getCurrentBuilding();
 if (building4.empty()) {
 IsoDirections directions1 = IsoDirections.fromAngle(player2.getForwardDirection());
 building4 = this->GetPeekedInBuilding(player2.getCurrentSquare(), directions1);
 if (building4 != nullptr) {
 this->playerWindowPeekingRoomId[int17] = this->playerPeekedRoomId;
 }
 }
 }
 }
 }

 if (IsoCamera.CamCharacter != nullptr
 && IsoCamera.CamCharacter.getCurrentSquare() != nullptr
 && IsoCamera.CamCharacter.getCurrentSquare().getProperties().Is(IsoFlagType.hidewalls) {
 this->maxZ = (int)IsoCamera.CamCharacter.getZ() + 1;
 }

 this->bRendering = true;

 try {
 this->RenderTiles(int1);
 } catch (Exception exception) {
 this->bRendering = false;
 Logger.getLogger(GameWindow.class.getName()).log(Level.SEVERE, nullptr, exception);
 }

 this->bRendering = false;
 if (IsoGridSquare.getRecalcLightTime() < 0) {
 IsoGridSquare.setRecalcLightTime(60);
 }

 if (IsoGridSquare.getLightcache() <= 0) {
 IsoGridSquare.setLightcache(90);
 }

 for (int int18 = 0; int18 < this->ObjectList.size(); int18++) {
 IsoMovingObject movingObject = this->ObjectList.get(int18);
 movingObject.renderlast();
 }

 for (int int19 = 0; int19 < this->StaticUpdaterObjectList.size(); int19++) {
 IsoObject object = this->StaticUpdaterObjectList.get(int19);
 object.renderlast();
 }

 IsoTree.renderChopTreeIndicators();
 if (Core.bDebug) {
 }

 this->lastMinX = this->minX;
 this->lastMinY = this->minY;
 this->DoBuilding(IsoPlayer.getPlayerIndex(), true);
 this->renderRain();
 }

 void invalidatePeekedRoom(int playerIndex) {
 this->lastPlayerDir[playerIndex] = IsoDirections.Max;
 }

 bool initWeatherFx() {
 if (GameServer.bServer) {
 return false;
 } else {
 if (this->weatherFX.empty()) {
 this->weatherFX = std::make_unique<IsoWeatherFX>();
 this->weatherFX.init();
 }

 return true;
 }
 }

 void updateWeatherFx() {
 if (this->initWeatherFx()) {
 this->weatherFX.update();
 }
 }

 void renderWeatherFx() {
 if (this->initWeatherFx()) {
 this->weatherFX.render();
 }
 }

 IsoWeatherFX getWeatherFX() {
 return this->weatherFX;
 }

 void renderRain() {
 }

 void setRainAlpha(int alpha) {
 this->rainAlphaMax = alpha / 100.0F;
 }

 void setRainIntensity(int intensity) {
 this->rainIntensity = intensity;
 }

 void setRainSpeed(int speed) {
 this->rainSpeed = speed;
 }

 void reloadRainTextures() {
 }

 void GetBuildingsInFrontOfCharacter(ArrayList<IsoBuilding> arrayList, IsoGridSquare square, bool boolean0) {
 arrayList.clear();
 this->bOccludedByOrphanStructureFlag = false;
 if (square != nullptr) {
 int int0 = square.getX();
 int int1 = square.getY();
 int int2 = square.getZ();
 this->GetBuildingsInFrontOfCharacterSquare(int0, int1, int2, boolean0, arrayList);
 if (int2 < MaxHeight) {
 this->GetBuildingsInFrontOfCharacterSquare(int0 - 1 + 3, int1 - 1 + 3, int2 + 1, boolean0, arrayList);
 this->GetBuildingsInFrontOfCharacterSquare(int0 - 2 + 3, int1 - 2 + 3, int2 + 1, boolean0, arrayList);
 if (boolean0) {
 this->GetBuildingsInFrontOfCharacterSquare(int0 + 3, int1 - 1 + 3, int2 + 1, !boolean0, arrayList);
 this->GetBuildingsInFrontOfCharacterSquare(int0 - 1 + 3, int1 - 2 + 3, int2 + 1, !boolean0, arrayList);
 } else {
 this->GetBuildingsInFrontOfCharacterSquare(int0 - 1 + 3, int1 + 3, int2 + 1, !boolean0, arrayList);
 this->GetBuildingsInFrontOfCharacterSquare(int0 - 2 + 3, int1 - 1 + 3, int2 + 1, !boolean0, arrayList);
 }
 }
 }
 }

 void GetBuildingsInFrontOfCharacterSquare(int int0, int int1, int int2, bool boolean0, ArrayList<IsoBuilding> arrayList0) {
 IsoGridSquare square = this->getGridSquare(int0, int1, int2);
 if (square.empty()) {
 if (int2 < MaxHeight) {
 this->GetBuildingsInFrontOfCharacterSquare(int0 + 3, int1 + 3, int2 + 1, boolean0, arrayList0);
 }
 } else {
 IsoGridOcclusionData gridOcclusionData = square.getOrCreateOcclusionData();
 IsoGridOcclusionData.OcclusionFilter occlusionFilter = boolean0
 ? IsoGridOcclusionData.OcclusionFilter.Right
 : IsoGridOcclusionData.OcclusionFilter.Left;
 this->bOccludedByOrphanStructureFlag = this->bOccludedByOrphanStructureFlag | gridOcclusionData.getCouldBeOccludedByOrphanStructures(occlusionFilter);
 std::vector arrayList1 = gridOcclusionData.getBuildingsCouldBeOccluders(occlusionFilter);

 for (int int3 = 0; int3 < arrayList1.size(); int3++) {
 this->AddUniqueToBuildingList(arrayList0, (IsoBuilding)arrayList1.get(int3);
 }
 }
 }

 private ArrayList<IsoBuilding> GetBuildingsInFrontOfMustSeeSquare(IsoGridSquare square, IsoGridOcclusionData.OcclusionFilter occlusionFilter) {
 IsoGridOcclusionData gridOcclusionData = square.getOrCreateOcclusionData();
 this->bOccludedByOrphanStructureFlag = gridOcclusionData.getCouldBeOccludedByOrphanStructures(IsoGridOcclusionData.OcclusionFilter.All);
 return gridOcclusionData.getBuildingsCouldBeOccluders(occlusionFilter);
 }

 IsoBuilding GetPeekedInBuilding(IsoGridSquare square0, IsoDirections directions) {
 this->playerPeekedRoomId = -1;
 if (square0.empty()) {
 return nullptr;
 } else {
 if ((directions == IsoDirections.NW || directions == IsoDirections.N || directions == IsoDirections.NE)
 && LosUtil.lineClear(this, square0.x, square0.y, square0.z, square0.x, square0.y - 1, square0.z, false) != LosUtil.TestResults.Blocked) {
 IsoGridSquare square1 = square0.nav[IsoDirections.N.index()];
 if (square1 != nullptr) {
 IsoBuilding building0 = square1.getBuilding();
 if (building0 != nullptr) {
 this->playerPeekedRoomId = square1.getRoomID();
 return building0;
 }
 }
 }

 if ((directions == IsoDirections.SW || directions == IsoDirections.W || directions == IsoDirections.NW)
 && LosUtil.lineClear(this, square0.x, square0.y, square0.z, square0.x - 1, square0.y, square0.z, false) != LosUtil.TestResults.Blocked) {
 IsoGridSquare square2 = square0.nav[IsoDirections.W.index()];
 if (square2 != nullptr) {
 IsoBuilding building1 = square2.getBuilding();
 if (building1 != nullptr) {
 this->playerPeekedRoomId = square2.getRoomID();
 return building1;
 }
 }
 }

 if ((directions == IsoDirections.SE || directions == IsoDirections.S || directions == IsoDirections.SW)
 && LosUtil.lineClear(this, square0.x, square0.y, square0.z, square0.x, square0.y + 1, square0.z, false) != LosUtil.TestResults.Blocked) {
 IsoGridSquare square3 = square0.nav[IsoDirections.S.index()];
 if (square3 != nullptr) {
 IsoBuilding building2 = square3.getBuilding();
 if (building2 != nullptr) {
 this->playerPeekedRoomId = square3.getRoomID();
 return building2;
 }
 }
 }

 if ((directions == IsoDirections.NE || directions == IsoDirections.E || directions == IsoDirections.SE)
 && LosUtil.lineClear(this, square0.x, square0.y, square0.z, square0.x + 1, square0.y, square0.z, false) != LosUtil.TestResults.Blocked) {
 IsoGridSquare square4 = square0.nav[IsoDirections.E.index()];
 if (square4 != nullptr) {
 IsoBuilding building3 = square4.getBuilding();
 if (building3 != nullptr) {
 this->playerPeekedRoomId = square4.getRoomID();
 return building3;
 }
 }
 }

 return nullptr;
 }
 }

 void GetSquaresAroundPlayerSquare(IsoPlayer player, IsoGridSquare square0, ArrayList<IsoGridSquare> arrayList0, ArrayList<IsoGridSquare> arrayList1) {
 float float0 = player.x - 4.0F;
 float float1 = player.y - 4.0F;
 int int0 = (int)float0;
 int int1 = (int)float1;
 int int2 = square0.getZ();

 for (int int3 = int1; int3 < int1 + 10; int3++) {
 for (int int4 = int0; int4 < int0 + 10; int4++) {
 if ((int4 >= (int)player.x || int3 >= (int)player.y) && (int4 != (int)player.x || int3 != (int)player.y) {
 float float2 = int4 - player.x;
 float float3 = int3 - player.y;
 if (float3 < float2 + 4.5 && float3 > float2 - 4.5) {
 IsoGridSquare square1 = this->getGridSquare(int4, int3, int2);
 if (square1 != nullptr) {
 if (float3 >= float2) {
 arrayList0.add(square1);
 }

 if (float3 <= float2) {
 arrayList1.add(square1);
 }
 }
 }
 }
 }
 }
 }

 bool IsBehindStuff(IsoGridSquare square0) {
 if (!square0.getProperties().Is(IsoFlagType.exterior) {
 return true;
 } else {
 for (int int0 = 1; int0 < 8 && square0.getZ() + int0 < MaxHeight; int0++) {
 for (int int1 = -5; int1 <= 6; int1++) {
 for (int int2 = -5; int2 <= 6; int2++) {
 if (int2 >= int1 - 5 && int2 <= int1 + 5) {
 IsoGridSquare square1 = this->getGridSquare(
 square0.getX() + int2 + int0 * 3, square0.getY() + int1 + int0 * 3, square0.getZ() + int0
 );
 if (square1 != nullptr && !square1.getObjects().empty()) {
 if (int0 != 1 || square1.getObjects().size() != 1) {
 return true;
 }

 IsoObject object = square1.getObjects().get(0);
 if (object.sprite.empty() || object.sprite.name.empty() || !object.sprite.name.startsWith("lighting_outdoor")) {
 return true;
 }
 }
 }
 }
 }
 }

 return false;
 }
 }

 static IsoDirections FromMouseTile() {
 IsoDirections directions = IsoDirections.N;
 float float0 = UIManager.getPickedTileLocal().x;
 float float1 = UIManager.getPickedTileLocal().y;
 float float2 = 0.5F - Math.abs(0.5F - float1);
 float float3 = 0.5F - Math.abs(0.5F - float0);
 if (float0 > 0.5F && float3 < float2) {
 directions = IsoDirections.E;
 } else if (float1 > 0.5F && float3 > float2) {
 directions = IsoDirections.S;
 } else if (float0 < 0.5F && float3 < float2) {
 directions = IsoDirections.W;
 } else if (float1 < 0.5F && float3 > float2) {
 directions = IsoDirections.N;
 }

 return directions;
 }

 void update() {
 IsoCell.s_performance.isoCellUpdate.invokeAndMeasure(this, IsoCell::updateInternal);
 }

 void updateInternal() {
 MovingObjectUpdateScheduler.instance.startFrame();
 IsoSprite.alphaStep = 0.075F * (GameTime.getInstance().getMultiplier() / 1.6F);
 IsoGridSquare.gridSquareCacheEmptyTimer++;
 this->ProcessSpottedRooms();
 if (!GameServer.bServer) {
 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 if (IsoPlayer.players[int0] != nullptr && (!IsoPlayer.players[int0].isDead() || IsoPlayer.players[int0].ReanimatedCorpse != nullptr) {
 IsoPlayer.setInstance(IsoPlayer.players[int0]);
 IsoCamera.CamCharacter = IsoPlayer.players[int0];
 this->ChunkMap[int0].update();
 }
 }
 }

 this->ProcessRemoveItems(nullptr);
 this->ProcessItems(nullptr);
 this->ProcessRemoveItems(nullptr);
 this->ProcessIsoObject();
 this->safeToAdd = false;
 this->ProcessObjects(nullptr);
 if (GameClient.bClient
 && (
 NetworkZombieSimulator.getInstance().anyUnknownZombies() && GameClient.instance.sendZombieRequestsTimer.Check()
 || GameClient.instance.sendZombieTimer.Check()
 )) {
 NetworkZombieSimulator.getInstance().send();
 GameClient.instance.sendZombieTimer.Reset();
 GameClient.instance.sendZombieRequestsTimer.Reset();
 }

 this->safeToAdd = true;
 this->ProcessStaticUpdaters();
 this->ObjectDeletionAddition();
 IsoDeadBody.updateBodies();
 IsoGridSquare.setLightcache(IsoGridSquare.getLightcache() - 1);
 IsoGridSquare.setRecalcLightTime(IsoGridSquare.getRecalcLightTime() - 1);
 if (GameServer.bServer) {
 this->LamppostPositions.clear();
 this->roomLights.clear();
 }

 if (!GameTime.isGamePaused()) {
 this->rainScroll = this->rainScroll + this->rainSpeed / 10.0F * 0.075F * (30.0F / PerformanceSettings.getLockFPS());
 if (this->rainScroll > 1.0F) {
 this->rainScroll = 0.0F;
 }
 }

 if (!GameServer.bServer) {
 this->updateWeatherFx();
 }
 }

 IsoGridSquare getRandomFreeTile() {
 IsoGridSquare square = nullptr;
 bool boolean0 = true;

 do {
 boolean0 = true;
 square = this->getGridSquare(Rand.Next(this->width), Rand.Next(this->height), 0);
 if (square.empty()) {
 boolean0 = false;
 } else if (!square.isFree(false) {
 boolean0 = false;
 } else if (square.getProperties().Is(IsoFlagType.solid) || square.getProperties().Is(IsoFlagType.solidtrans) {
 boolean0 = false;
 } else if (square.getMovingObjects().size() > 0) {
 boolean0 = false;
 } else if (square.Has(IsoObjectType.stairsBN) || square.Has(IsoObjectType.stairsMN) || square.Has(IsoObjectType.stairsTN) {
 boolean0 = false;
 } else if (square.Has(IsoObjectType.stairsBW) || square.Has(IsoObjectType.stairsMW) || square.Has(IsoObjectType.stairsTW) {
 boolean0 = false;
 }
 } while (!boolean0);

 return square;
 }

 IsoGridSquare getRandomOutdoorFreeTile() {
 IsoGridSquare square = nullptr;
 bool boolean0 = true;

 do {
 boolean0 = true;
 square = this->getGridSquare(Rand.Next(this->width), Rand.Next(this->height), 0);
 if (square.empty()) {
 boolean0 = false;
 } else if (!square.isFree(false) {
 boolean0 = false;
 } else if (square.getRoom() != nullptr) {
 boolean0 = false;
 } else if (square.getProperties().Is(IsoFlagType.solid) || square.getProperties().Is(IsoFlagType.solidtrans) {
 boolean0 = false;
 } else if (square.getMovingObjects().size() > 0) {
 boolean0 = false;
 } else if (square.Has(IsoObjectType.stairsBN) || square.Has(IsoObjectType.stairsMN) || square.Has(IsoObjectType.stairsTN) {
 boolean0 = false;
 } else if (square.Has(IsoObjectType.stairsBW) || square.Has(IsoObjectType.stairsMW) || square.Has(IsoObjectType.stairsTW) {
 boolean0 = false;
 }
 } while (!boolean0);

 return square;
 }

 IsoGridSquare getRandomFreeTileInRoom() {
 std::stack stack = new Stack();

 for (int int0 = 0; int0 < this->RoomList.size(); int0++) {
 if (this->RoomList.get(int0).TileList.size() > 9
 && !this->RoomList.get(int0).Exits.empty()
 && this->RoomList.get(int0).TileList.get(0).getProperties().Is(IsoFlagType.solidfloor) {
 stack.add(this->RoomList.get(int0);
 }
 }

 if (stack.empty()) {
 return nullptr;
 } else {
 IsoRoom room = (IsoRoom)stack.get(Rand.Next(stack.size()));
 return room.getFreeTile();
 }
 }

 void roomSpotted(IsoRoom room) {
 synchronized (this->SpottedRooms) {
 if (!this->SpottedRooms.contains(room) {
 this->SpottedRooms.push(room);
 }
 }
 }

 void ProcessSpottedRooms() {
 synchronized (this->SpottedRooms) {
 for (int int0 = 0; int0 < this->SpottedRooms.size(); int0++) {
 IsoRoom room = this->SpottedRooms.get(int0);
 if (!room.def.bDoneSpawn) {
 room.def.bDoneSpawn = true;
 LuaEventManager.triggerEvent("OnSeeNewRoom", room);
 VirtualZombieManager.instance.roomSpotted(room);
 if (!GameClient.bClient
 && !Core.bLastStand
 && ("shed" == room.def.name) || "garagestorage" == room.def.name) || "storageunit" == room.def.name)) {
 uint8_t byte0 = 7;
 if ("shed" == room.def.name) || "garagestorage" == room.def.name) {
 byte0 = 4;
 }

 switch (SandboxOptions.instance.GeneratorSpawning.getValue()) {
 case 1:
 byte0 += 3;
 break;
 case 2:
 byte0 += 2;
 case 3:
 default:
 break;
 case 4:
 byte0 -= 2;
 break;
 case 5:
 byte0 -= 3;
 }

 if (Rand.Next((int)byte0) == 0) {
 IsoGridSquare square = room.getRandomFreeSquare();
 if (square != nullptr) {
 IsoGenerator generator = new IsoGenerator(InventoryItemFactory.CreateItem("Base.Generator"), this, square);
 if (GameServer.bServer) {
 generator.transmitCompleteItemToClients();
 }
 }
 }
 }
 }
 }

 this->SpottedRooms.clear();
 }
 }

 void savePlayer() {
 if (IsoPlayer.players[0] != nullptr && !IsoPlayer.players[0].isDead()) {
 IsoPlayer.players[0].save();
 }

 GameClient.instance.sendPlayerSave(IsoPlayer.players[0]);
 }

 void save(DataOutputStream output, bool bDoChars) {
 while (ChunkSaveWorker.instance.bSaving) {
 try {
 Thread.sleep(30L);
 } catch (InterruptedException interruptedException) {
 interruptedException.printStackTrace();
 }
 }

 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 this->ChunkMap[int0].Save();
 }

 output.writeInt(this->width);
 output.writeInt(this->height);
 output.writeInt(MaxHeight);
 File file = ZomboidFileSystem.instance.getFileInCurrentSave("map_t.bin");
 FileOutputStream fileOutputStream = new FileOutputStream(file);
 output = new DataOutputStream(new BufferedOutputStream(fileOutputStream);
 GameTime.instance.save(output);
 output.flush();
 output.close();
 IsoWorld.instance.MetaGrid.save();
 if (PlayerDB.isAllow()) {
 PlayerDB.getInstance().savePlayers();
 }

 ReanimatedPlayers.instance.saveReanimatedPlayers();
 }

 bool LoadPlayer(int WorldVersion) {
 if (GameClient.bClient) {
 return ClientPlayerDB.getInstance().loadNetworkPlayer();
 } else {
 File file = ZomboidFileSystem.instance.getFileInCurrentSave("map_p.bin");
 if (!file.exists()) {
 PlayerDB.getInstance().importPlayersFromVehiclesDB();
 return PlayerDB.getInstance().loadLocalPlayer(1);
 } else {
 FileInputStream fileInputStream = new FileInputStream(file);
 BufferedInputStream bufferedInputStream = new BufferedInputStream(fileInputStream);
 synchronized (SliceY.SliceBufferLock) {
 SliceY.SliceBuffer.clear();
 int int0 = bufferedInputStream.read(SliceY.SliceBuffer.array());
 SliceY.SliceBuffer.limit(int0);
 uint8_t byte0 = SliceY.SliceBuffer.get();
 uint8_t byte1 = SliceY.SliceBuffer.get();
 uint8_t byte2 = SliceY.SliceBuffer.get();
 uint8_t byte3 = SliceY.SliceBuffer.get();
 if (byte0 == 80 && byte1 == 76 && byte2 == 89 && byte3 == 82) {
 WorldVersion = SliceY.SliceBuffer.getInt();
 } else {
 SliceY.SliceBuffer.rewind();
 }

 if (WorldVersion >= 69) {
 std::string string = GameWindow.ReadString(SliceY.SliceBuffer);
 if (GameClient.bClient && WorldVersion < 71) {
 string = ServerOptions.instance.ServerPlayerID.getValue();
 }

 if (GameClient.bClient && !IsoPlayer.isServerPlayerIDValid(string) {
 GameLoadingState.GameLoadingString = Translator.getText("IGUI_MP_ServerPlayerIDMismatch");
 GameLoadingState.playerWrongIP = true;
 return false;
 }
 }

 instance.ChunkMap[IsoPlayer.getPlayerIndex()].WorldX = SliceY.SliceBuffer.getInt() + IsoWorld.saveoffsetx * 30;
 instance.ChunkMap[IsoPlayer.getPlayerIndex()].WorldY = SliceY.SliceBuffer.getInt() + IsoWorld.saveoffsety * 30;
 SliceY.SliceBuffer.getInt();
 SliceY.SliceBuffer.getInt();
 SliceY.SliceBuffer.getInt();
 if (IsoPlayer.getInstance() == nullptr) {
 IsoPlayer.setInstance(new IsoPlayer(instance);
 IsoPlayer.players[0] = IsoPlayer.getInstance();
 }

 IsoPlayer.getInstance().load(SliceY.SliceBuffer, WorldVersion);
 fileInputStream.close();
 }

 PlayerDB.getInstance().saveLocalPlayersForce();
 file.delete();
 PlayerDB.getInstance().uploadLocalPlayers2DB();
 return true;
 }
 }
 }

 IsoGridSquare getRelativeGridSquare(int x, int y, int z) {
 int int0 = this->ChunkMap[0].getWorldXMin();
 IsoChunkMap chunkMap = this->ChunkMap[0];
 int int1 = int0 * 10;
 int0 = this->ChunkMap[0].getWorldYMin();
 chunkMap = this->ChunkMap[0];
 int int2 = int0 * 10;
 x += int1;
 y += int2;
 return this->getGridSquare(x, y, z);
 }

 IsoGridSquare createNewGridSquare(int x, int y, int z, bool recalcAll) {
 if (!IsoWorld.instance.isValidSquare(x, y, z) {
 return nullptr;
 } else {
 IsoGridSquare square = this->getGridSquare(x, y, z);
 if (square != nullptr) {
 return square;
 } else {
 if (GameServer.bServer) {
 int int0 = x / 10;
 int int1 = y / 10;
 if (ServerMap.instance.getChunk(int0, int1) != nullptr) {
 square = IsoGridSquare.getNew(this, nullptr, x, y, z);
 ServerMap.instance.setGridSquare(x, y, z, square);
 }
 } else if (this->getChunkForGridSquare(x, y, z) != nullptr) {
 square = IsoGridSquare.getNew(this, nullptr, x, y, z);
 this->ConnectNewSquare(square, true);
 }

 if (square != nullptr && recalcAll) {
 square.RecalcAllWithNeighbours(true);
 }

 return square;
 }
 }
 }

 IsoGridSquare getGridSquareDirect(int x, int y, int z, int playerIndex) {
 int int0 = IsoChunkMap.ChunkWidthInTiles;
 return this->gridSquares[playerIndex][x + y * int0 + z * int0 * int0];
 }

 bool isInChunkMap(int x, int y) {
 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 int int1 = this->ChunkMap[int0].getWorldXMinTiles();
 int int2 = this->ChunkMap[int0].getWorldXMaxTiles();
 int int3 = this->ChunkMap[int0].getWorldYMinTiles();
 int int4 = this->ChunkMap[int0].getWorldYMaxTiles();
 if (x >= int1 && x < int2 && y >= int3 && y < int4) {
 return true;
 }
 }

 return false;
 }

 public ArrayList<IsoObject> getProcessIsoObjectRemove() {
 return this->ProcessIsoObjectRemove;
 }

 void checkHaveRoof(int x, int y) {
 bool boolean0 = false;

 for (int int0 = 8; int0 >= 0; int0--) {
 IsoGridSquare square = this->getGridSquare(x, y, int0);
 if (square != nullptr) {
 if (boolean0 != square.haveRoof) {
 square.haveRoof = boolean0;
 square.RecalcAllWithNeighbours(true);
 }

 if (square.Is(IsoFlagType.solidfloor) {
 boolean0 = true;
 }
 }
 }
 }

 IsoZombie getFakeZombieForHit() {
 if (this->fakeZombieForHit.empty()) {
 this->fakeZombieForHit = new IsoZombie(this);
 }

 return this->fakeZombieForHit;
 }

 void addHeatSource(IsoHeatSource heatSource) {
 if (!GameServer.bServer) {
 if (this->heatSources.contains(heatSource) {
 DebugLog.log("ERROR addHeatSource called again with the same HeatSource");
 } else {
 this->heatSources.add(heatSource);
 }
 }
 }

 void removeHeatSource(IsoHeatSource heatSource) {
 if (!GameServer.bServer) {
 this->heatSources.remove(heatSource);
 }
 }

 void updateHeatSources() {
 if (!GameServer.bServer) {
 for (int int0 = this->heatSources.size() - 1; int0 >= 0; int0--) {
 IsoHeatSource heatSource = this->heatSources.get(int0);
 if (!heatSource.isInBounds()) {
 this->heatSources.remove(int0);
 }
 }
 }
 }

 int getHeatSourceTemperature(int x, int y, int z) {
 int int0 = 0;

 for (int int1 = 0; int1 < this->heatSources.size(); int1++) {
 IsoHeatSource heatSource = this->heatSources.get(int1);
 if (heatSource.getZ() == z) {
 float float0 = IsoUtils.DistanceToSquared(x, y, heatSource.getX(), heatSource.getY());
 if (float0 < heatSource.getRadius() * heatSource.getRadius()) {
 LosUtil.TestResults testResults = LosUtil.lineClear(this, heatSource.getX(), heatSource.getY(), heatSource.getZ(), x, y, z, false);
 if (testResults == LosUtil.TestResults.Clear || testResults == LosUtil.TestResults.ClearThroughOpenDoor) {
 int0 = (int)(int0 + heatSource.getTemperature() * (1.0 - Math.sqrt(float0) / heatSource.getRadius()));
 }
 }
 }
 }

 return int0;
 }

 float getHeatSourceHighestTemperature(float surroundingAirTemperature, int x, int y, int z) {
 float float0 = surroundingAirTemperature;
 float float1 = surroundingAirTemperature;
 float float2 = 0.0F;
 void* object = nullptr;
 float float3 = 0.0F;

 for (int int0 = 0; int0 < this->heatSources.size(); int0++) {
 IsoHeatSource heatSource = this->heatSources.get(int0);
 if (heatSource.getZ() == z) {
 float float4 = IsoUtils.DistanceToSquared(x, y, heatSource.getX(), heatSource.getY());
 object = this->getGridSquare(heatSource.getX(), heatSource.getY(), heatSource.getZ());
 float3 = 0.0F;
 if (object != nullptr) {
 if (!((IsoGridSquare)object).isInARoom()) {
 float3 = float0 - 30.0F;
 if (float3 < -15.0F) {
 float3 = -15.0F;
 } else if (float3 > 5.0F) {
 float3 = 5.0F;
 }
 } else {
 float3 = float0 - 30.0F;
 if (float3 < -7.0F) {
 float3 = -7.0F;
 } else if (float3 > 7.0F) {
 float3 = 7.0F;
 }
 }
 }

 float2 = ClimateManager.lerp((float)(1.0 - Math.sqrt(float4) / heatSource.getRadius()), float0, heatSource.getTemperature() + float3);
 if (!(float2 <= float1) && float4 < heatSource.getRadius() * heatSource.getRadius()) {
 LosUtil.TestResults testResults = LosUtil.lineClear(this, heatSource.getX(), heatSource.getY(), heatSource.getZ(), x, y, z, false);
 if (testResults == LosUtil.TestResults.Clear || testResults == LosUtil.TestResults.ClearThroughOpenDoor) {
 float1 = float2;
 }
 }
 }
 }

 return float1;
 }

 void putInVehicle(IsoGameCharacter chr) {
 if (chr != nullptr && chr.savedVehicleSeat != -1) {
 int int0 = ((int)chr.getX() - 4) / 10;
 int int1 = ((int)chr.getY() - 4) / 10;
 int int2 = ((int)chr.getX() + 4) / 10;
 int int3 = ((int)chr.getY() + 4) / 10;

 for (int int4 = int1; int4 <= int3; int4++) {
 for (int int5 = int0; int5 <= int2; int5++) {
 IsoChunk chunk = this->getChunkForGridSquare(int5 * 10, int4 * 10, (int)chr.getZ());
 if (chunk != nullptr) {
 for (int int6 = 0; int6 < chunk.vehicles.size(); int6++) {
 BaseVehicle vehicle = chunk.vehicles.get(int6);
 if ((int)vehicle.getZ() == (int)chr.getZ()
 && IsoUtils.DistanceToSquared(vehicle.getX(), vehicle.getY(), chr.savedVehicleX, chr.savedVehicleY) < 0.010000001F) {
 if (vehicle.VehicleID == -1) {
 return;
 }

 VehicleScript.Position position = vehicle.getPassengerPosition(chr.savedVehicleSeat, "inside");
 if (position != nullptr && !vehicle.isSeatOccupied(chr.savedVehicleSeat) {
 vehicle.enter(chr.savedVehicleSeat, chr, position.offset);
 LuaEventManager.triggerEvent("OnEnterVehicle", chr);
 if (vehicle.getCharacter(chr.savedVehicleSeat) == chr && chr.savedVehicleRunning) {
 vehicle.resumeRunningAfterLoad();
 }
 }

 return;
 }
 }
 }
 }
 }
 }
 }

 void resumeVehicleSounds(IsoGameCharacter chr) {
 if (chr != nullptr && chr.savedVehicleSeat != -1) {
 int int0 = ((int)chr.getX() - 4) / 10;
 int int1 = ((int)chr.getY() - 4) / 10;
 int int2 = ((int)chr.getX() + 4) / 10;
 int int3 = ((int)chr.getY() + 4) / 10;

 for (int int4 = int1; int4 <= int3; int4++) {
 for (int int5 = int0; int5 <= int2; int5++) {
 IsoChunk chunk = this->getChunkForGridSquare(int5 * 10, int4 * 10, (int)chr.getZ());
 if (chunk != nullptr) {
 for (int int6 = 0; int6 < chunk.vehicles.size(); int6++) {
 BaseVehicle vehicle = chunk.vehicles.get(int6);
 if (vehicle.lightbarSirenMode.isEnable()) {
 vehicle.setLightbarSirenMode(vehicle.lightbarSirenMode.get());
 }
 }
 }
 }
 }
 }
 }

 void AddUniqueToBuildingList(ArrayList<IsoBuilding> arrayList, IsoBuilding building) {
 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 if (arrayList.get(int0) == building) {
 return;
 }
 }

 arrayList.add(building);
 }

 IsoSpriteManager getSpriteManager() {
 return IsoSpriteManager.instance;
 }

 public static enum BuildingSearchCriteria {
 Food,
 Defense,
 Wood,
 Weapons,
 General;
 }

 public static class PerPlayerRender {
 const IsoGridStack GridStacks = new IsoGridStack(9);
 public boolean[][][] VisiOccludedFlags;
 public boolean[][] VisiCulledFlags;
 public short[][][] StencilValues;
 public boolean[][] FlattenGrassEtc;
 int minX;
 int minY;
 int maxX;
 int maxY;

 void setSize(int w, int h) {
 if (this->VisiOccludedFlags.empty() || this->VisiOccludedFlags.length < w || this->VisiOccludedFlags[0].length < h) {
 this->VisiOccludedFlags = new boolean[w][h][2];
 this->VisiCulledFlags = new boolean[w][h];
 this->StencilValues = new short[w][h][2];
 this->FlattenGrassEtc = new boolean[w][h];
 }
 }
 }

 class SnowGrid {
 int w = 256;
 int h = 256;
 int frac = 0;
 static const int N = 0;
 static const int S = 1;
 static const int W = 2;
 static const int E = 3;
 static const int A = 0;
 static const int B = 1;
 public Texture[][][] grid = new Texture[this->w][this->h][2];
 public byte[][][] gridType = new byte[this->w][this->h][2];

 public SnowGrid(int arg1) {
 this->init(arg1);
 }

 public IsoCell.SnowGrid init(int arg0) {
 if (!IsoCell.this->hasSetupSnowGrid) {
 IsoCell.this->snowNoise2D = std::make_unique<Noise2D>();
 IsoCell.this->snowNoise2D.addLayer(16, 0.5F, 3.0F);
 IsoCell.this->snowNoise2D.addLayer(32, 2.0F, 5.0F);
 IsoCell.this->snowNoise2D.addLayer(64, 5.0F, 8.0F);
 uint8_t byte0 = 0;
 IsoCell.this->snowGridTiles_Square = IsoCell.this->new SnowGridTiles(byte0++);
 uint8_t byte1 = 40;

 for (int int0 = 0; int0 < 4; int0++) {
 IsoCell.this->snowGridTiles_Square.add(Texture.getSharedTexture("e_newsnow_ground_1_" + (byte1 + int0));
 }

 IsoCell.this->snowGridTiles_Enclosed = IsoCell.this->new SnowGridTiles(byte0++);
 byte1 = 0;

 for (int int1 = 0; int1 < 4; int1++) {
 IsoCell.this->snowGridTiles_Enclosed.add(Texture.getSharedTexture("e_newsnow_ground_1_" + (byte1 + int1));
 }

 IsoCell.this->snowGridTiles_Cove = new IsoCell.SnowGridTiles[4];

 for (int int2 = 0; int2 < 4; int2++) {
 IsoCell.this->snowGridTiles_Cove[int2] = IsoCell.this->new SnowGridTiles(byte0++);
 if (int2 == 0) {
 byte1 = 7;
 }

 if (int2 == 2) {
 byte1 = 4;
 }

 if (int2 == 1) {
 byte1 = 5;
 }

 if (int2 == 3) {
 byte1 = 6;
 }

 for (int int3 = 0; int3 < 3; int3++) {
 IsoCell.this->snowGridTiles_Cove[int2].add(Texture.getSharedTexture("e_newsnow_ground_1_" + (byte1 + int3 * 4));
 }
 }

 IsoCell.this->m_snowFirstNonSquare = byte0;
 IsoCell.this->snowGridTiles_Edge = new IsoCell.SnowGridTiles[4];

 for (int int4 = 0; int4 < 4; int4++) {
 IsoCell.this->snowGridTiles_Edge[int4] = IsoCell.this->new SnowGridTiles(byte0++);
 if (int4 == 0) {
 byte1 = 16;
 }

 if (int4 == 2) {
 byte1 = 18;
 }

 if (int4 == 1) {
 byte1 = 17;
 }

 if (int4 == 3) {
 byte1 = 19;
 }

 for (int int5 = 0; int5 < 3; int5++) {
 IsoCell.this->snowGridTiles_Edge[int4].add(Texture.getSharedTexture("e_newsnow_ground_1_" + (byte1 + int5 * 4));
 }
 }

 IsoCell.this->snowGridTiles_Strip = new IsoCell.SnowGridTiles[4];

 for (int int6 = 0; int6 < 4; int6++) {
 IsoCell.this->snowGridTiles_Strip[int6] = IsoCell.this->new SnowGridTiles(byte0++);
 if (int6 == 0) {
 byte1 = 28;
 }

 if (int6 == 2) {
 byte1 = 29;
 }

 if (int6 == 1) {
 byte1 = 31;
 }

 if (int6 == 3) {
 byte1 = 30;
 }

 for (int int7 = 0; int7 < 3; int7++) {
 IsoCell.this->snowGridTiles_Strip[int6].add(Texture.getSharedTexture("e_newsnow_ground_1_" + (byte1 + int7 * 4));
 }
 }

 IsoCell.this->hasSetupSnowGrid = true;
 }

 IsoCell.this->snowGridTiles_Square.resetCounter();
 IsoCell.this->snowGridTiles_Enclosed.resetCounter();

 for (int int8 = 0; int8 < 4; int8++) {
 IsoCell.this->snowGridTiles_Cove[int8].resetCounter();
 IsoCell.this->snowGridTiles_Edge[int8].resetCounter();
 IsoCell.this->snowGridTiles_Strip[int8].resetCounter();
 }

 this->frac = arg0;
 Noise2D noise2D = IsoCell.this->snowNoise2D;

 for (int int9 = 0; int9 < this->h; int9++) {
 for (int int10 = 0; int10 < this->w; int10++) {
 for (int int11 = 0; int11 < 2; int11++) {
 this->grid[int10][int9][int11] = nullptr;
 this->gridType[int10][int9][int11] = -1;
 }

 if (noise2D.layeredNoise(int10 / 10.0F, int9 / 10.0F) <= arg0 / 100.0F) {
 this->grid[int10][int9][0] = IsoCell.this->snowGridTiles_Square.getNext();
 this->gridType[int10][int9][0] = IsoCell.this->snowGridTiles_Square.ID;
 }
 }
 }

 for (int int12 = 0; int12 < this->h; int12++) {
 for (int int13 = 0; int13 < this->w; int13++) {
 Texture texture = this->grid[int13][int12][0];
 if (texture.empty()) {
 bool boolean0 = this->check(int13, int12 - 1);
 bool boolean1 = this->check(int13, int12 + 1);
 bool boolean2 = this->check(int13 - 1, int12);
 bool boolean3 = this->check(int13 + 1, int12);
 int int14 = 0;
 if (boolean0) {
 int14++;
 }

 if (boolean1) {
 int14++;
 }

 if (boolean3) {
 int14++;
 }

 if (boolean2) {
 int14++;
 }

 if (int14 != 0) {
 if (int14 == 1) {
 if (boolean0) {
 this->set(int13, int12, 0, IsoCell.this->snowGridTiles_Strip[0]);
 } else if (boolean1) {
 this->set(int13, int12, 0, IsoCell.this->snowGridTiles_Strip[1]);
 } else if (boolean3) {
 this->set(int13, int12, 0, IsoCell.this->snowGridTiles_Strip[3]);
 } else if (boolean2) {
 this->set(int13, int12, 0, IsoCell.this->snowGridTiles_Strip[2]);
 }
 } else if (int14 == 2) {
 if (boolean0 && boolean1) {
 this->set(int13, int12, 0, IsoCell.this->snowGridTiles_Strip[0]);
 this->set(int13, int12, 1, IsoCell.this->snowGridTiles_Strip[1]);
 } else if (boolean3 && boolean2) {
 this->set(int13, int12, 0, IsoCell.this->snowGridTiles_Strip[2]);
 this->set(int13, int12, 1, IsoCell.this->snowGridTiles_Strip[3]);
 } else if (boolean0) {
 this->set(int13, int12, 0, IsoCell.this->snowGridTiles_Edge[boolean2 ? 0 : 3]);
 } else if (boolean1) {
 this->set(int13, int12, 0, IsoCell.this->snowGridTiles_Edge[boolean2 ? 2 : 1]);
 } else if (boolean2) {
 this->set(int13, int12, 0, IsoCell.this->snowGridTiles_Edge[boolean0 ? 0 : 2]);
 } else if (boolean3) {
 this->set(int13, int12, 0, IsoCell.this->snowGridTiles_Edge[boolean0 ? 3 : 1]);
 }
 } else if (int14 == 3) {
 if (!boolean0) {
 this->set(int13, int12, 0, IsoCell.this->snowGridTiles_Cove[1]);
 } else if (!boolean1) {
 this->set(int13, int12, 0, IsoCell.this->snowGridTiles_Cove[0]);
 } else if (!boolean3) {
 this->set(int13, int12, 0, IsoCell.this->snowGridTiles_Cove[2]);
 } else if (!boolean2) {
 this->set(int13, int12, 0, IsoCell.this->snowGridTiles_Cove[3]);
 }
 } else if (int14 == 4) {
 this->set(int13, int12, 0, IsoCell.this->snowGridTiles_Enclosed);
 }
 }
 }
 }
 }

 return this;
 }

 bool check(int arg0, int arg1) {
 if (arg0 == this->w) {
 arg0 = 0;
 }

 if (arg0 == -1) {
 arg0 = this->w - 1;
 }

 if (arg1 == this->h) {
 arg1 = 0;
 }

 if (arg1 == -1) {
 arg1 = this->h - 1;
 }

 if (arg0 < 0 || arg0 >= this->w) {
 return false;
 } else if (arg1 >= 0 && arg1 < this->h) {
 Texture texture = this->grid[arg0][arg1][0];
 return IsoCell.this->snowGridTiles_Square.contains(texture);
 } else {
 return false;
 }
 }

 bool checkAny(int arg0, int arg1) {
 if (arg0 == this->w) {
 arg0 = 0;
 }

 if (arg0 == -1) {
 arg0 = this->w - 1;
 }

 if (arg1 == this->h) {
 arg1 = 0;
 }

 if (arg1 == -1) {
 arg1 = this->h - 1;
 }

 if (arg0 < 0 || arg0 >= this->w) {
 return false;
 } else {
 return arg1 >= 0 && arg1 < this->h ? this->grid[arg0][arg1][0] != nullptr : false;
 }
 }

 void set(int arg0, int arg1, int arg2, IsoCell.SnowGridTiles arg3) {
 if (arg0 == this->w) {
 arg0 = 0;
 }

 if (arg0 == -1) {
 arg0 = this->w - 1;
 }

 if (arg1 == this->h) {
 arg1 = 0;
 }

 if (arg1 == -1) {
 arg1 = this->h - 1;
 }

 if (arg0 >= 0 && arg0 < this->w) {
 if (arg1 >= 0 && arg1 < this->h) {
 this->grid[arg0][arg1][arg2] = arg3.getNext();
 this->gridType[arg0][arg1][arg2] = arg3.ID;
 }
 }
 }

 void subtract(IsoCell.SnowGrid arg0) {
 for (int int0 = 0; int0 < this->h; int0++) {
 for (int int1 = 0; int1 < this->w; int1++) {
 for (int int2 = 0; int2 < 2; int2++) {
 if (arg0.gridType[int1][int0][int2] == this->gridType[int1][int0][int2]) {
 this->grid[int1][int0][int2] = nullptr;
 this->gridType[int1][int0][int2] = -1;
 }
 }
 }
 }
 }
 }

 class SnowGridTiles {
 uint8_t ID = -1;
 int counter = -1;
 private ArrayList<Texture> textures = std::make_unique<ArrayList<>>();

 public SnowGridTiles(uint8_t arg1) {
 this->ID = arg1;
 }

 void add(Texture texture) {
 this->textures.add(texture);
 }

 Texture getNext() {
 this->counter++;
 if (this->counter >= this->textures.size()) {
 this->counter = 0;
 }

 return this->textures.get(this->counter);
 }

 Texture get(int int0) {
 return this->textures.get(int0);
 }

 int size() {
 return this->textures.size();
 }

 Texture getRand() {
 return this->textures.get(Rand.Next(4);
 }

 bool contains(Texture texture) {
 return this->textures.contains(texture);
 }

 void resetCounter() {
 this->counter = 0;
 }
 }

 private static class s_performance {
 static const PerformanceProfileProbe isoCellUpdate = new PerformanceProfileProbe("IsoCell.update");
 static const PerformanceProfileProbe isoCellRender = new PerformanceProfileProbe("IsoCell.render");
 static const PerformanceProfileProbe isoCellRenderTiles = new PerformanceProfileProbe("IsoCell.renderTiles");
 static const PerformanceProfileProbe isoCellDoBuilding = new PerformanceProfileProbe("IsoCell.doBuilding");

 static class renderTiles {
 static const PerformanceProfileProbe performRenderTiles = new PerformanceProfileProbe("performRenderTiles");
 static const PerformanceProfileProbe recalculateAnyGridStacks = new PerformanceProfileProbe("recalculateAnyGridStacks");
 static const PerformanceProfileProbe flattenAnyFoliage = new PerformanceProfileProbe("flattenAnyFoliage");
 static const PerformanceProfileProbe renderDebugPhysics = new PerformanceProfileProbe("renderDebugPhysics");
 static const PerformanceProfileProbe renderDebugLighting = new PerformanceProfileProbe("renderDebugLighting");
 static PerformanceProfileProbeList<IsoCell.s_performance.renderTiles.PperformRenderTilesLayer> performRenderTilesLayers = PerformanceProfileProbeList.construct(
 "performRenderTiles",
 8,
 IsoCell.s_performance.renderTiles.PperformRenderTilesLayer.class,
 IsoCell.s_performance.renderTiles.PperformRenderTilesLayer::new
 );

 static class PperformRenderTilesLayer extends PerformanceProfileProbe {
 const PerformanceProfileProbe renderIsoWater = new PerformanceProfileProbe("renderIsoWater");
 const PerformanceProfileProbe renderFloor = new PerformanceProfileProbe("renderFloor");
 const PerformanceProfileProbe renderPuddles = new PerformanceProfileProbe("renderPuddles");
 const PerformanceProfileProbe renderShore = new PerformanceProfileProbe("renderShore");
 const PerformanceProfileProbe renderSnow = new PerformanceProfileProbe("renderSnow");
 const PerformanceProfileProbe renderBlood = new PerformanceProfileProbe("renderBlood");
 const PerformanceProfileProbe vegetationCorpses = new PerformanceProfileProbe("vegetationCorpses");
 const PerformanceProfileProbe renderFloorShading = new PerformanceProfileProbe("renderFloorShading");
 const PerformanceProfileProbe renderShadows = new PerformanceProfileProbe("renderShadows");
 const PerformanceProfileProbe luaOnPostFloorLayerDraw = new PerformanceProfileProbe("luaOnPostFloorLayerDraw");
 const PerformanceProfileProbe minusFloorCharacters = new PerformanceProfileProbe("minusFloorCharacters");

 PperformRenderTilesLayer(String string) {
 super(string);
 }
 }
 }
 }
}
} // namespace iso
} // namespace zombie
