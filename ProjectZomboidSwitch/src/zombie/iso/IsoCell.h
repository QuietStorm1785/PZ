#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <QRect>
#include <glm/glm.hpp>
#extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}
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
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/core/textures/TextureDraw/GenericDrawer.h"
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
#include "zombie/iso/IsoCell/1.h"
#include "zombie/iso/IsoCell/s_performance.h"
#include "zombie/iso/IsoCell/s_performance/renderTiles.h"
#include "zombie/iso/IsoCell/s_performance/renderTiles/PperformRenderTilesLayer.h"
#include "zombie/iso/IsoGridOcclusionData/OcclusionFilter.h"
#include "zombie/iso/IsoGridSquare/GetSquare.h"
#include "zombie/iso/LosUtil/TestResults.h"
#include "zombie/iso/RoomDef/RoomRect.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/SpriteDetails/IsoObjectType.h"
#include "zombie/iso/areas/BuildingScore.h"
#include "zombie/iso/areas/IsoBuilding.h"
#include "zombie/iso/areas/IsoRoom.h"
#include "zombie/iso/areas/IsoRoomExit.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/iso/objects/IsoGenerator.h"
#include "zombie/iso/objects/IsoTree.h"
#include "zombie/iso/objects/IsoWindow.h"
#include "zombie/iso/objects/IsoWorldInventoryObject.h"
#include "zombie/iso/sprite/CorpseFlies.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
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
#include "zombie/scripting/objects/VehicleScript/Position.h"
#include "zombie/ui/UIManager.h"
#include "zombie/util/Type.h"
#include "zombie/vehicles/BaseVehicle.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
// --- Begin merged IsoCell subclasses and enums ---
namespace zombie {
namespace iso {

enum class BuildingSearchCriteria {
   Food,
   Defense,
   Wood,
   Weapons,
   General
};

class PerPlayerRender {
public:
   std::shared_ptr<IsoGridStack> GridStacks;
   std::vector<std::vector<std::vector<bool>>> VisiOccludedFlags;
   std::vector<std::vector<bool>> VisiCulledFlags;
   std::vector<std::vector<std::vector<short>>> StencilValues;
   std::vector<std::vector<bool>> FlattenGrassEtc;
   int minX = 0;
   int minY = 0;
   int maxX = 0;
   int maxY = 0;
   PerPlayerRender() : GridStacks(std::make_shared<IsoGridStack>(9)) {}
   void setSize(int w, int h) {
      if (VisiOccludedFlags.size() < w || (VisiOccludedFlags.size() > 0 && VisiOccludedFlags[0].size() < h)) {
         VisiOccludedFlags.resize(w, std::vector<std::vector<bool>>(h, std::vector<bool>(2)));
         VisiCulledFlags.resize(w, std::vector<bool>(h));
         StencilValues.resize(w, std::vector<std::vector<short>>(h, std::vector<short>(2)));
         FlattenGrassEtc.resize(w, std::vector<bool>(h));
      }
   }
};

class SnowGridTiles {
public:
   int8_t ID = -1;
   int counter = -1;
   std::vector<std::shared_ptr<Texture>> textures;
   SnowGridTiles(IsoCell* cell, int8_t id) : ID(id) {}
   void add(std::shared_ptr<Texture> tex) { textures.push_back(tex); }
   std::shared_ptr<Texture> getNext() {
      counter++;
      if (counter >= static_cast<int>(textures.size())) counter = 0;
      return textures[counter];
   }
   std::shared_ptr<Texture> get(int idx) { return textures[idx]; }
   int size() const { return static_cast<int>(textures.size()); }
};

class SnowGrid {
public:
   int w = 256;
   int h = 256;
   int frac = 0;
   static constexpr int N = 0;
   static constexpr int S = 1;
   static constexpr int W = 2;
   static constexpr int E = 3;
   static constexpr int A = 0;
   static constexpr int B = 1;
   std::vector<std::vector<std::vector<std::shared_ptr<Texture>>>> grid;
   std::vector<std::vector<std::vector<int8_t>>> gridType;
   SnowGrid(IsoCell* cell, int var2) : grid(w, std::vector<std::vector<std::shared_ptr<Texture>>>(h, std::vector<std::shared_ptr<Texture>>(2))), gridType(w, std::vector<std::vector<int8_t>>(h, std::vector<int8_t>(2))) {}
   // Additional methods and fields as needed
};

} // namespace iso
} // namespace zombie
// --- End merged IsoCell subclasses and enums ---


namespace zombie {
namespace iso {


class IsoCell {
public:
    static int MaxHeight = 8;
    static Shader m_floorRenderShader;
    static Shader m_wallRenderShader;
   public std::vector<IsoGridSquare> Trees = std::make_unique<std::vector<>>();
   static const std::vector<IsoGridSquare> stchoices = std::make_unique<std::vector<>>();
   public const IsoChunkMap[] ChunkMap = new IsoChunkMap[4];
   public const std::vector<IsoBuilding> BuildingList = std::make_unique<std::vector<>>();
   private const std::vector<IsoWindow> WindowList = std::make_unique<std::vector<>>();
   private const std::vector<IsoMovingObject> ObjectList = std::make_unique<std::vector<>>();
   private const std::vector<IsoPushableObject> PushableObjectList = std::make_unique<std::vector<>>();
   private const std::unordered_map<int, BuildingScore> BuildingScores = std::make_unique<std::unordered_map<>>();
   private const std::vector<IsoRoom> RoomList = std::make_unique<std::vector<>>();
   private const std::vector<IsoObject> StaticUpdaterObjectList = std::make_unique<std::vector<>>();
   private const std::vector<IsoZombie> ZombieList = std::make_unique<std::vector<>>();
   private const std::vector<IsoGameCharacter> RemoteSurvivorList = std::make_unique<std::vector<>>();
   private const std::vector<IsoMovingObject> removeList = std::make_unique<std::vector<>>();
   private const std::vector<IsoMovingObject> addList = std::make_unique<std::vector<>>();
   private const std::vector<IsoObject> ProcessIsoObject = std::make_unique<std::vector<>>();
   private const std::vector<IsoObject> ProcessIsoObjectRemove = std::make_unique<std::vector<>>();
   private const std::vector<InventoryItem> ProcessItems = std::make_unique<std::vector<>>();
   private const std::vector<InventoryItem> ProcessItemsRemove = std::make_unique<std::vector<>>();
   private const std::vector<IsoWorldInventoryObject> ProcessWorldItems = std::make_unique<std::vector<>>();
   public const std::vector<IsoWorldInventoryObject> ProcessWorldItemsRemove = std::make_unique<std::vector<>>();
   private const IsoGridSquare[][] gridSquares = new IsoGridSquare[4][IsoChunkMap.ChunkWidthInTiles * IsoChunkMap.ChunkWidthInTiles * 8];
    static const bool ENABLE_SQUARE_CACHE = true;
    int height;
    int width;
    int worldX;
    int worldY;
    IntGrid DangerScore;
    bool safeToAdd = true;
   private const std::stack<IsoLightSource> LamppostPositions = std::make_unique<std::stack<>>();
   public const std::vector<IsoRoomLight> roomLights = std::make_unique<std::vector<>>();
   private const std::vector<IsoHeatSource> heatSources = std::make_unique<std::vector<>>();
   public const std::vector<BaseVehicle> addVehicles = std::make_unique<std::vector<>>();
   public const std::vector<BaseVehicle> vehicles = std::make_unique<std::vector<>>();
    static const int ISOANGLEFACTOR = 3;
    static const int ZOMBIESCANBUDGET = 10;
    static const float NEARESTZOMBIEDISTSQRMAX = 150.0F;
    int zombieScanCursor = 0;
   private const IsoZombie[] nearestVisibleZombie = new IsoZombie[4];
   private const float[] nearestVisibleZombieDistSqr = new float[4];
   private static std::stack<BuildingScore> buildingscores = std::make_unique<std::stack<>>();
   static std::vector<IsoGridSquare> GridStack = nullptr;
    static const int RTF_SolidFloor = 1;
    static const int RTF_VegetationCorpses = 2;
    static const int RTF_MinusFloorCharacters = 4;
    static const int RTF_ShadedFloor = 8;
    static const int RTF_Shadows = 16;
   private static const std::vector<IsoGridSquare> ShadowSquares = new std::vector<>(1000);
   private static const std::vector<IsoGridSquare> MinusFloorCharacters = new std::vector<>(1000);
   private static const std::vector<IsoGridSquare> SolidFloor = new std::vector<>(5000);
   private static const std::vector<IsoGridSquare> ShadedFloor = new std::vector<>(5000);
   private static const std::vector<IsoGridSquare> VegetationCorpses = new std::vector<>(5000);
   public static const PerPlayerRender[] perPlayerRender = new PerPlayerRender[4];
   private const int[] StencilXY = new int[]{0, 0, -1, 0, 0, -1, -1, -1, -2, -1, -1, -2, -2, -2, -3, -2, -2, -3, -3, -3};
   private const int[] StencilXY2z = new int[]{
      0, 0, -1, 0, 0, -1, -1, -1, -2, -1, -1, -2, -2, -2, -3, -2, -2, -3, -3, -3, -4, -3, -3, -4, -4, -4, -5, -4, -4, -5, -5, -5, -6, -5, -5, -6, -6, -6
   };
    int StencilX1;
    int StencilY1;
    int StencilX2;
    int StencilY2;
    Texture m_stencilTexture = nullptr;
    const DiamondMatrixIterator diamondMatrixIterator = std::make_shared<DiamondMatrixIterator>(123);
    const Vector2i diamondMatrixPos = std::make_shared<Vector2i>();
    int DeferredCharacterTick = 0;
    bool hasSetupSnowGrid = false;
    SnowGridTiles snowGridTiles_Square;
   private SnowGridTiles[] snowGridTiles_Strip;
   private SnowGridTiles[] snowGridTiles_Edge;
   private SnowGridTiles[] snowGridTiles_Cove;
    SnowGridTiles snowGridTiles_Enclosed;
    int m_snowFirstNonSquare = -1;
    Noise2D snowNoise2D = std::make_shared<Noise2D>();
    SnowGrid snowGridCur;
    SnowGrid snowGridPrev;
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
   const KahluaTable[] drag = new KahluaTable[4];
   const std::vector<IsoSurvivor> SurvivorList = std::make_unique<std::vector<>>();
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
   const boolean[] bHideFloors = new boolean[4];
   const int[] unhideFloorsCounter = new int[4];
    bool bOccludedByOrphanStructureFlag = false;
    int playerPeekedRoomId = -1;
   const std::vector<std::vector<IsoBuilding>> playerOccluderBuildings = new std::vector<>(4);
   const IsoBuilding[][] playerOccluderBuildingsArr = new IsoBuilding[4][];
   const int[] playerWindowPeekingRoomId = new int[4];
   const boolean[] playerHidesOrphanStructures = new boolean[4];
   const boolean[] playerCutawaysDirty = new boolean[4];
    const Vector2 tempCutawaySqrVector = std::make_shared<Vector2>();
   std::vector<int> tempPrevPlayerCutawayRoomIDs = std::make_unique<std::vector<>>();
   std::vector<int> tempPlayerCutawayRoomIDs = std::make_unique<std::vector<>>();
   const IsoGridSquare[] lastPlayerSquare = new IsoGridSquare[4];
   const boolean[] lastPlayerSquareHalf = new boolean[4];
   const IsoDirections[] lastPlayerDir = new IsoDirections[4];
   const Vector2[] lastPlayerAngle = new Vector2[4];
    int hidesOrphanStructuresAbove = MaxHeight;
    const Rectangle buildingRectTemp = std::make_shared<Rectangle>();
   const std::vector<std::vector<IsoBuilding>> zombieOccluderBuildings = new std::vector<>(4);
   const IsoBuilding[][] zombieOccluderBuildingsArr = new IsoBuilding[4][];
   const IsoGridSquare[] lastZombieSquare = new IsoGridSquare[4];
   const boolean[] lastZombieSquareHalf = new boolean[4];
   const std::vector<std::vector<IsoBuilding>> otherOccluderBuildings = new std::vector<>(4);
   const IsoBuilding[][] otherOccluderBuildingsArr = new IsoBuilding[4][];
    const int mustSeeSquaresRadius = 4;
    const int mustSeeSquaresGridSize = 10;
   const std::vector<IsoGridSquare> gridSquaresTempLeft = new std::vector<>(100);
   const std::vector<IsoGridSquare> gridSquaresTempRight = new std::vector<>(100);
    IsoWeatherFX weatherFX;
    int minX;
    int maxX;
    int minY;
    int maxY;
    int minZ;
    int maxZ;
    OnceEvery dangerUpdate = std::make_shared<OnceEvery>(0.4F, false);
    Thread LightInfoUpdate = nullptr;
   private const std::stack<IsoRoom> SpottedRooms = std::make_unique<std::stack<>>();
    IsoZombie fakeZombieForHit;

    static int getMaxHeight() {
    return MaxHeight;
   }

    LotHeader getCurrentLotHeader() {
    IsoChunk var1 = this.getChunkForGridSquare((int)IsoCamera.CamCharacter.x, (int)IsoCamera.CamCharacter.y, (int)IsoCamera.CamCharacter.z);
      return var1.lotheader;
   }

    IsoChunkMap getChunkMap(int var1) {
      return this.ChunkMap[var1];
   }

    IsoGridSquare getFreeTile(RoomDef var1) {
      stchoices.clear();

      for (int var2 = 0; var2 < var1.rects.size(); var2++) {
    RoomRect var3 = (RoomRect)var1.rects.get(var2);

         for (int var4 = var3.x; var4 < var3.x + var3.w; var4++) {
            for (int var5 = var3.y; var5 < var3.y + var3.h; var5++) {
    IsoGridSquare var6 = this.getGridSquare(var4, var5, var1.level);
               if (var6 != nullptr) {
                  var6.setCachedIsFree(false);
                  var6.setCacheIsFree(false);
                  if (var6.isFree(false)) {
                     stchoices.push_back(var6);
                  }
               }
            }
         }
      }

      if (stchoices.empty()) {
    return nullptr;
      } else {
    IsoGridSquare var7 = stchoices.get(Rand.Next(stchoices.size()));
         stchoices.clear();
    return var7;
      }
   }

   public static std::stack<BuildingScore> getBuildings() {
    return buildingscores;
   }

    static void setBuildings(std::stack<BuildingScore> var0) {
      buildingscores = var0;
   }

    IsoZombie getNearestVisibleZombie(int var1) {
      return this.nearestVisibleZombie[var1];
   }

    IsoChunk getChunkForGridSquare(int var1, int var2, int var3) {
    int var4 = var1;
    int var5 = var2;

      for (int var6 = 0; var6 < IsoPlayer.numPlayers; var6++) {
         if (!this.ChunkMap[var6].ignore) {
            var1 = var4 - this.ChunkMap[var6].getWorldXMinTiles();
            var2 = var5 - this.ChunkMap[var6].getWorldYMinTiles();
            if (var1 >= 0 && var2 >= 0) {
    IsoChunkMap var10001 = this.ChunkMap[var6];
               var1 /= 10;
               var10001 = this.ChunkMap[var6];
               var2 /= 10;
    IsoChunk var7 = nullptr;
               var7 = this.ChunkMap[var6].getChunk(var1, var2);
               if (var7 != nullptr) {
    return var7;
               }
            }
         }
      }

    return nullptr;
   }

    IsoChunk getChunk(int var1, int var2) {
      for (int var3 = 0; var3 < IsoPlayer.numPlayers; var3++) {
    IsoChunkMap var4 = this.ChunkMap[var3];
         if (!var4.ignore) {
    IsoChunk var5 = var4.getChunk(var1 - var4.getWorldXMin(), var2 - var4.getWorldYMin());
            if (var5 != nullptr) {
    return var5;
            }
         }
      }

    return nullptr;
   }

    public IsoCell(int var1, int var2) {
      IsoWorld.instance.CurrentCell = this;
      instance = this;
      this.width = var1;
      this.height = var2;

      for (int var3 = 0; var3 < 4; var3++) {
         this.ChunkMap[var3] = std::make_shared<IsoChunkMap>(this);
         this.ChunkMap[var3].PlayerID = var3;
         this.ChunkMap[var3].ignore = var3 > 0;
         this.playerOccluderBuildings.push_back(new std::vector<>(5));
         this.zombieOccluderBuildings.push_back(new std::vector<>(5));
         this.otherOccluderBuildings.push_back(new std::vector<>(5));
      }

      WorldReuserThread.instance.run();
   }

    short getStencilValue(int var1, int var2, int var3) {
      short[][][] var4 = perPlayerRender[IsoCamera.frameState.playerIndex].StencilValues;
    int var5 = 0;
    int var6 = 0;

      for (byte var7 = 0; var7 < this.StencilXY.length; var7 += 2) {
    int var8 = -var3 * 3;
    int var9 = var1 + var8 + this.StencilXY[var7];
    int var10 = var2 + var8 + this.StencilXY[var7 + 1];
         if (var9 >= this.minX && var9 < this.maxX && var10 >= this.minY && var10 < this.maxY) {
            short[] var11 = var4[var9 - this.minX][var10 - this.minY];
            if (var11[0] != 0) {
               if (var5 == 0) {
                  var5 = var11[0];
                  var6 = var11[1];
               } else {
                  var5 = Math.min(var11[0], var5);
                  var6 = Math.max(var11[1], var6);
               }
            }
         }
      }

      if (var5 == 0) {
    return 1;
      } else {
         return var5 > 10 ? (short)(var5 - 10) : (short)(var6 + 1);
      }
   }

    void setStencilValue(int var1, int var2, int var3, int var4) {
      short[][][] var5 = perPlayerRender[IsoCamera.frameState.playerIndex].StencilValues;

      for (byte var6 = 0; var6 < this.StencilXY.length; var6 += 2) {
    int var7 = -var3 * 3;
    int var8 = var1 + var7 + this.StencilXY[var6];
    int var9 = var2 + var7 + this.StencilXY[var6 + 1];
         if (var8 >= this.minX && var8 < this.maxX && var9 >= this.minY && var9 < this.maxY) {
            short[] var10 = var5[var8 - this.minX][var9 - this.minY];
            if (var10[0] == 0) {
               var10[0] = (short)var4;
               var10[1] = (short)var4;
            } else {
               var10[0] = (short)Math.min(var10[0], var4);
               var10[1] = (short)Math.max(var10[1], var4);
            }
         }
      }
   }

    short getStencilValue2z(int var1, int var2, int var3) {
      short[][][] var4 = perPlayerRender[IsoCamera.frameState.playerIndex].StencilValues;
    int var5 = 0;
    int var6 = 0;
    int var7 = -var3 * 3;

      for (byte var8 = 0; var8 < this.StencilXY2z.length; var8 += 2) {
    int var9 = var1 + var7 + this.StencilXY2z[var8];
    int var10 = var2 + var7 + this.StencilXY2z[var8 + 1];
         if (var9 >= this.minX && var9 < this.maxX && var10 >= this.minY && var10 < this.maxY) {
            short[] var11 = var4[var9 - this.minX][var10 - this.minY];
            if (var11[0] != 0) {
               if (var5 == 0) {
                  var5 = var11[0];
                  var6 = var11[1];
               } else {
                  var5 = Math.min(var11[0], var5);
                  var6 = Math.max(var11[1], var6);
               }
            }
         }
      }

      if (var5 == 0) {
    return 1;
      } else {
         return var5 > 10 ? (short)(var5 - 10) : (short)(var6 + 1);
      }
   }

    void setStencilValue2z(int var1, int var2, int var3, int var4) {
      short[][][] var5 = perPlayerRender[IsoCamera.frameState.playerIndex].StencilValues;
    int var6 = -var3 * 3;

      for (byte var7 = 0; var7 < this.StencilXY2z.length; var7 += 2) {
    int var8 = var1 + var6 + this.StencilXY2z[var7];
    int var9 = var2 + var6 + this.StencilXY2z[var7 + 1];
         if (var8 >= this.minX && var8 < this.maxX && var9 >= this.minY && var9 < this.maxY) {
            short[] var10 = var5[var8 - this.minX][var9 - this.minY];
            if (var10[0] == 0) {
               var10[0] = (short)var4;
               var10[1] = (short)var4;
            } else {
               var10[0] = (short)Math.min(var10[0], var4);
               var10[1] = (short)Math.max(var10[1], var4);
            }
         }
      }
   }

    void CalculateVertColoursForTile(IsoGridSquare var1, int var2, int var3, int var4, int var5) {
    IsoGridSquare var6 = !IsoGridSquare.getMatrixBit(var1.visionMatrix, 0, 0, 1) ? var1.nav[IsoDirections.NW.index()] : nullptr;
    IsoGridSquare var7 = !IsoGridSquare.getMatrixBit(var1.visionMatrix, 1, 0, 1) ? var1.nav[IsoDirections.N.index()] : nullptr;
    IsoGridSquare var8 = !IsoGridSquare.getMatrixBit(var1.visionMatrix, 2, 0, 1) ? var1.nav[IsoDirections.NE.index()] : nullptr;
    IsoGridSquare var9 = !IsoGridSquare.getMatrixBit(var1.visionMatrix, 2, 1, 1) ? var1.nav[IsoDirections.E.index()] : nullptr;
    IsoGridSquare var10 = !IsoGridSquare.getMatrixBit(var1.visionMatrix, 2, 2, 1) ? var1.nav[IsoDirections.SE.index()] : nullptr;
    IsoGridSquare var11 = !IsoGridSquare.getMatrixBit(var1.visionMatrix, 1, 2, 1) ? var1.nav[IsoDirections.S.index()] : nullptr;
    IsoGridSquare var12 = !IsoGridSquare.getMatrixBit(var1.visionMatrix, 0, 2, 1) ? var1.nav[IsoDirections.SW.index()] : nullptr;
    IsoGridSquare var13 = !IsoGridSquare.getMatrixBit(var1.visionMatrix, 0, 1, 1) ? var1.nav[IsoDirections.W.index()] : nullptr;
      this.CalculateColor(var6, var7, var13, var1, 0, var5);
      this.CalculateColor(var7, var8, var9, var1, 1, var5);
      this.CalculateColor(var10, var11, var9, var1, 2, var5);
      this.CalculateColor(var12, var11, var13, var1, 3, var5);
   }

    Texture getStencilTexture() {
      if (this.m_stencilTexture == nullptr) {
         this.m_stencilTexture = Texture.getSharedTexture("media/mask_circledithernew.png");
      }

      return this.m_stencilTexture;
   }

    void DrawStencilMask() {
    Texture var1 = this.getStencilTexture();
      if (var1 != nullptr) {
         IndieGL.glStencilMask(255);
         IndieGL.glClear(1280);
    int var2 = IsoCamera.getOffscreenWidth(IsoPlayer.getPlayerIndex()) / 2;
    int var3 = IsoCamera.getOffscreenHeight(IsoPlayer.getPlayerIndex()) / 2;
         var2 -= var1.getWidth() / (2 / Core.TileScale);
         var3 -= var1.getHeight() / (2 / Core.TileScale);
         IndieGL.enableStencilTest();
         IndieGL.enableAlphaTest();
         IndieGL.glAlphaFunc(516, 0.1F);
         IndieGL.glStencilFunc(519, 128, 255);
         IndieGL.glStencilOp(7680, 7680, 7681);
         IndieGL.glColorMask(false, false, false, false);
         var1.renderstrip(
            var2 - (int)IsoCamera.getRightClickOffX(),
            var3 - (int)IsoCamera.getRightClickOffY(),
            var1.getWidth() * Core.TileScale,
            var1.getHeight() * Core.TileScale,
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
         this.StencilX1 = var2 - (int)IsoCamera.getRightClickOffX();
         this.StencilY1 = var3 - (int)IsoCamera.getRightClickOffY();
         this.StencilX2 = this.StencilX1 + var1.getWidth() * Core.TileScale;
         this.StencilY2 = this.StencilY1 + var1.getHeight() * Core.TileScale;
      }
   }

    void RenderTiles(int var1) {
      s_performance.isoCellRenderTiles.invokeAndMeasure(this, var1, IsoCell::renderTilesInternal);
   }

    void renderTilesInternal(int var1) {
      if (DebugOptions.instance.Terrain.RenderTiles.Enable.getValue()) {
         if (m_floorRenderShader == nullptr) {
            RenderThread.invokeOnRenderContext(this::initTileShaders);
         }

    int var2 = IsoCamera.frameState.playerIndex;
    IsoPlayer var3 = IsoPlayer.players[var2];
         var3.dirtyRecalcGridStackTime = var3.dirtyRecalcGridStackTime - GameTime.getInstance().getMultiplier() / 4.0F;
    PerPlayerRender var4 = this.getPerPlayerRenderAt(var2);
         var4.setSize(this.maxX - this.minX + 1, this.maxY - this.minY + 1);
    long var5 = System.currentTimeMillis();
         if (this.minX != var4.minX || this.minY != var4.minY || this.maxX != var4.maxX || this.maxY != var4.maxY) {
            var4.minX = this.minX;
            var4.minY = this.minY;
            var4.maxX = this.maxX;
            var4.maxY = this.maxY;
            var3.dirtyRecalcGridStack = true;
            WeatherFxMask.forceMaskUpdate(var2);
         }

         renderTiles.recalculateAnyGridStacks.start();
    bool var7 = var3.dirtyRecalcGridStack;
         this.recalculateAnyGridStacks(var4, var1, var2, var5);
         renderTiles.recalculateAnyGridStacks.end();
         this.DeferredCharacterTick++;
         renderTiles.flattenAnyFoliage.start();
         this.flattenAnyFoliage(var4, var2);
         renderTiles.flattenAnyFoliage.end();
         if (this.SetCutawayRoomsForPlayer() || var7) {
    IsoGridStack var8 = var4.GridStacks;

            for (int var9 = 0; var9 < var1 + 1; var9++) {
               GridStack = (std::vector<IsoGridSquare>)var8.Squares.get(var9);

               for (int var10 = 0; var10 < GridStack.size(); var10++) {
    IsoGridSquare var11 = GridStack.get(var10);
                  var11.setPlayerCutawayFlag(var2, this.IsCutawaySquare(var11, var5), var5);
               }
            }
         }

         renderTiles.performRenderTiles.start();
         this.performRenderTiles(var4, var1, var2, var5);
         renderTiles.performRenderTiles.end();
         this.playerCutawaysDirty[var2] = false;
         ShadowSquares.clear();
         MinusFloorCharacters.clear();
         ShadedFloor.clear();
         SolidFloor.clear();
         VegetationCorpses.clear();
         renderTiles.renderDebugPhysics.start();
         this.renderDebugPhysics(var2);
         renderTiles.renderDebugPhysics.end();
         renderTiles.renderDebugLighting.start();
         this.renderDebugLighting(var4, var1);
         renderTiles.renderDebugLighting.end();
      }
   }

    void initTileShaders() {
      if (DebugLog.isEnabled(DebugType.Shader)) {
         DebugLog.Shader.debugln("Loading shader: \"floorTile\"");
      }

      m_floorRenderShader = std::make_shared<Shader>("floorTile");
      if (DebugLog.isEnabled(DebugType.Shader)) {
         DebugLog.Shader.debugln("Loading shader: \"wallTile\"");
      }

      m_wallRenderShader = std::make_shared<Shader>("wallTile");
   }

    PerPlayerRender getPerPlayerRenderAt(int var1) {
      if (perPlayerRender[var1] == nullptr) {
         perPlayerRender[var1] = std::make_unique<PerPlayerRender>();
      }

      return perPlayerRender[var1];
   }

    void recalculateAnyGridStacks(PerPlayerRender var1, int var2, int var3, long var4) {
    IsoPlayer var6 = IsoPlayer.players[var3];
      if (var6.dirtyRecalcGridStack) {
         var6.dirtyRecalcGridStack = false;
    IsoGridStack var7 = var1.GridStacks;
         boolean[][][] var8 = var1.VisiOccludedFlags;
         boolean[][] var9 = var1.VisiCulledFlags;
    int var10 = -1;
    int var11 = -1;
    int var12 = -1;
         WeatherFxMask.setDiamondIterDone(var3);

         for (int var13 = var2; var13 >= 0; var13--) {
            GridStack = (std::vector<IsoGridSquare>)var7.Squares.get(var13);
            GridStack.clear();
            if (var13 < this.maxZ) {
               if (DebugOptions.instance.Terrain.RenderTiles.NewRender.getValue()) {
    DiamondMatrixIterator var22 = this.diamondMatrixIterator.reset(this.maxX - this.minX);
    IsoGridSquare var23 = nullptr;
    Vector2i var25 = this.diamondMatrixPos;

                  while (var22.next(var25)) {
                     if (var25.y < this.maxY - this.minY + 1) {
                        var23 = this.ChunkMap[var3].getGridSquare(var25.x + this.minX, var25.y + this.minY, var13);
                        if (var13 == 0) {
                           var8[var25.x][var25.y][0] = false;
                           var8[var25.x][var25.y][1] = false;
                           var9[var25.x][var25.y] = false;
                        }

                        if (var23 == nullptr) {
                           WeatherFxMask.addMaskLocation(nullptr, var25.x + this.minX, var25.y + this.minY, var13);
                        } else {
    IsoChunk var26 = var23.getChunk();
                           if (var26 != nullptr && var23.IsOnScreen(true)) {
                              WeatherFxMask.addMaskLocation(var23, var25.x + this.minX, var25.y + this.minY, var13);
    bool var28 = this.IsDissolvedSquare(var23, var3);
                              var23.setIsDissolved(var3, var28, var4);
                              if (!var23.getIsDissolved(var3, var4)) {
                                 var23.cacheLightInfo();
                                 GridStack.push_back(var23);
                              }
                           }
                        }
                     }
                  }
               } else {
                  for (int var14 = this.minY; var14 < this.maxY; var14++) {
    int var15 = this.minX;
    IsoGridSquare var16 = this.ChunkMap[var3].getGridSquare(var15, var14, var13);
    int var17 = IsoDirections.E.index();

                     while (var15 < this.maxX) {
                        if (var13 == 0) {
                           var8[var15 - this.minX][var14 - this.minY][0] = false;
                           var8[var15 - this.minX][var14 - this.minY][1] = false;
                           var9[var15 - this.minX][var14 - this.minY] = false;
                        }

                        if (var16 != nullptr && var16.getY() != var14) {
                           var16 = nullptr;
                        }

    uint8_t var18 = -1;
    uint8_t var19 = -1;
    IsoChunkMap var10002 = this.ChunkMap[var3];
    int var10001 = this.ChunkMap[var3].WorldX - IsoChunkMap.ChunkGridWidth / 2;
                        var10002 = this.ChunkMap[var3];
    int var20 = var15 - var10001 * 10;
                        var10002 = this.ChunkMap[var3];
                        var10001 = this.ChunkMap[var3].WorldY - IsoChunkMap.ChunkGridWidth / 2;
                        var10002 = this.ChunkMap[var3];
    int var21 = var14 - var10001 * 10;
    IsoChunkMap var35 = this.ChunkMap[var3];
                        var20 /= 10;
    IsoChunkMap var36 = this.ChunkMap[var3];
                        var21 /= 10;
                        if (var20 != var10 || var21 != var11) {
    IsoChunk var30 = this.ChunkMap[var3].getChunkForGridSquare(var15, var14);
                           if (var30 != nullptr) {
                              var12 = var30.maxLevel;
                           }
                        }

                        var10 = var20;
                        var11 = var21;
                        if (var12 < var13) {
                           var15++;
                        } else {
                           if (var16 == nullptr) {
                              var16 = this.getGridSquare(var15, var14, var13);
                              if (var16 == nullptr) {
                                 var16 = this.ChunkMap[var3].getGridSquare(var15, var14, var13);
                                 if (var16 == nullptr) {
                                    var15++;
                                    continue;
                                 }
                              }
                           }

    IsoChunk var31 = var16.getChunk();
                           if (var31 != nullptr && var16.IsOnScreen(true)) {
                              WeatherFxMask.addMaskLocation(var16, var16.x, var16.y, var13);
    bool var33 = this.IsDissolvedSquare(var16, var3);
                              var16.setIsDissolved(var3, var33, var4);
                              if (!var16.getIsDissolved(var3, var4)) {
                                 var16.cacheLightInfo();
                                 GridStack.push_back(var16);
                              }
                           }

                           var16 = var16.nav[var17];
                           var15++;
                        }
                     }
                  }
               }
            }
         }

         this.CullFullyOccludedSquares(var7, var8, var9);
      }
   }

    void flattenAnyFoliage(PerPlayerRender var1, int var2) {
      short[][][] var3 = var1.StencilValues;
      boolean[][] var4 = var1.FlattenGrassEtc;

      for (int var5 = this.minY; var5 <= this.maxY; var5++) {
         for (int var6 = this.minX; var6 <= this.maxX; var6++) {
            var3[var6 - this.minX][var5 - this.minY][0] = 0;
            var3[var6 - this.minX][var5 - this.minY][1] = 0;
            var4[var6 - this.minX][var5 - this.minY] = false;
         }
      }

      for (int var11 = 0; var11 < this.vehicles.size(); var11++) {
    BaseVehicle var12 = this.vehicles.get(var11);
         if (!(var12.getAlpha(var2) <= 0.0F)) {
            for (int var7 = -2; var7 < 5; var7++) {
               for (int var8 = -2; var8 < 5; var8++) {
    int var9 = (int)var12.x + var8;
    int var10 = (int)var12.y + var7;
                  if (var9 >= this.minX && var9 <= this.maxX && var10 >= this.minY && var10 <= this.maxY) {
                     var4[var9 - this.minX][var10 - this.minY] = true;
                  }
               }
            }
         }
      }
   }

    void performRenderTiles(PerPlayerRender var1, int var2, int var3, long var4) {
    IsoGridStack var6 = var1.GridStacks;
      boolean[][] var7 = var1.FlattenGrassEtc;
    Shader var8;
    Shader var9;
      if (Core.bDebug && !DebugOptions.instance.Terrain.RenderTiles.UseShaders.getValue()) {
         var8 = nullptr;
         var9 = nullptr;
      } else {
         var8 = m_floorRenderShader;
         var9 = m_wallRenderShader;
      }

      for (int var10 = 0; var10 < var2 + 1; var10++) {
    PperformRenderTilesLayer var11 = (PperformRenderTilesLayer)renderTiles.performRenderTilesLayers.start(var10);
         GridStack = (std::vector<IsoGridSquare>)var6.Squares.get(var10);
         ShadowSquares.clear();
         SolidFloor.clear();
         ShadedFloor.clear();
         VegetationCorpses.clear();
         MinusFloorCharacters.clear();
         IndieGL.glClear(256);
         if (var10 == 0 && DebugOptions.instance.Terrain.RenderTiles.Water.getValue() && DebugOptions.instance.Terrain.RenderTiles.WaterBody.getValue()) {
            var11.renderIsoWater.start();
            IsoWater.getInstance().render(GridStack, false);
            var11.renderIsoWater.end();
         }

         var11.renderFloor.start();

         for (int var12 = 0; var12 < GridStack.size(); var12++) {
    IsoGridSquare var13 = GridStack.get(var12);
            if (var13.chunk == nullptr || !var13.chunk.bLightingNeverDone[var3]) {
               var13.bFlattenGrassEtc = var10 == 0 && var7[var13.x - this.minX][var13.y - this.minY];
    int var14 = var13.renderFloor(var8);
               if (!var13.getStaticMovingObjects().empty()) {
                  var14 |= 2;
                  var14 |= 16;
                  if (var13.HasStairs()) {
                     var14 |= 4;
                  }
               }

               if (!var13.getWorldObjects().empty()) {
                  var14 |= 2;
               }

               if (!var13.getLocalTemporaryObjects().empty()) {
                  var14 |= 4;
               }

               for (int var15 = 0; var15 < var13.getMovingObjects().size(); var15++) {
    IsoMovingObject var16 = (IsoMovingObject)var13.getMovingObjects().get(var15);
    bool var17 = var16.bOnFloor;
                  if (var17 && dynamic_cast<IsoZombie*>(var16) != nullptr var18) {
                     var17 = var18.isProne();
                     if (!BaseVehicle.RENDER_TO_TEXTURE) {
                        var17 = false;
                     }
                  }

                  if (var17) {
                     var14 |= 2;
                  } else {
                     var14 |= 4;
                  }

                  var14 |= 16;
               }

               if (!var13.getDeferedCharacters().empty()) {
                  var14 |= 4;
               }

               if (var13.hasFlies()) {
                  var14 |= 4;
               }

               if ((var14 & 1) != 0) {
                  SolidFloor.push_back(var13);
               }

               if ((var14 & 8) != 0) {
                  ShadedFloor.push_back(var13);
               }

               if ((var14 & 2) != 0) {
                  VegetationCorpses.push_back(var13);
               }

               if ((var14 & 4) != 0) {
                  MinusFloorCharacters.push_back(var13);
               }

               if ((var14 & 16) != 0) {
                  ShadowSquares.push_back(var13);
               }
            }
         }

         var11.renderFloor.end();
         var11.renderPuddles.start();
         IsoPuddles.getInstance().render(SolidFloor, var10);
         var11.renderPuddles.end();
         if (var10 == 0 && DebugOptions.instance.Terrain.RenderTiles.Water.getValue() && DebugOptions.instance.Terrain.RenderTiles.WaterShore.getValue()) {
            var11.renderShore.start();
            IsoWater.getInstance().render(nullptr, true);
            var11.renderShore.end();
         }

         if (!SolidFloor.empty()) {
            var11.renderSnow.start();
            this.RenderSnow(var10);
            var11.renderSnow.end();
         }

         if (!GridStack.empty()) {
            var11.renderBlood.start();
            this.ChunkMap[var3].renderBloodForChunks(var10);
            var11.renderBlood.end();
         }

         if (!ShadedFloor.empty()) {
            var11.renderFloorShading.start();
            this.RenderFloorShading(var10);
            var11.renderFloorShading.end();
         }

         WorldMarkers.instance.renderGridSquareMarkers(var1, var10, var3);
         if (DebugOptions.instance.Terrain.RenderTiles.Shadows.getValue()) {
            var11.renderShadows.start();
            this.renderShadows();
            var11.renderShadows.end();
         }

         if (DebugOptions.instance.Terrain.RenderTiles.Lua.getValue()) {
            var11.luaOnPostFloorLayerDraw.start();
            LuaEventManager.triggerEvent("OnPostFloorLayerDraw", var10);
            var11.luaOnPostFloorLayerDraw.end();
         }

         IsoMarkers.instance.renderIsoMarkers(var1, var10, var3);
         IsoMarkers.instance.renderCircleIsoMarkers(var1, var10, var3);
         if (DebugOptions.instance.Terrain.RenderTiles.VegetationCorpses.getValue()) {
            var11.vegetationCorpses.start();

            for (int var20 = 0; var20 < VegetationCorpses.size(); var20++) {
    IsoGridSquare var22 = VegetationCorpses.get(var20);
               var22.renderMinusFloor(this.maxZ, false, true, false, false, false, var9);
               var22.renderCharacters(this.maxZ, true, true);
            }

            var11.vegetationCorpses.end();
         }

         ImprovedFog.startRender(var3, var10);
         if (DebugOptions.instance.Terrain.RenderTiles.MinusFloorCharacters.getValue()) {
            var11.minusFloorCharacters.start();

            for (int var21 = 0; var21 < MinusFloorCharacters.size(); var21++) {
    IsoGridSquare var23 = MinusFloorCharacters.get(var21);
    IsoGridSquare var26 = var23.nav[IsoDirections.S.index()];
    IsoGridSquare var27 = var23.nav[IsoDirections.E.index()];
    bool var28 = var26 != nullptr && var26.getPlayerCutawayFlag(var3, var4);
    bool var29 = var23.getPlayerCutawayFlag(var3, var4);
    bool var30 = var27 != nullptr && var27.getPlayerCutawayFlag(var3, var4);
               this.currentLY = var23.getY() - this.minY;
               this.currentLZ = var10;
               ImprovedFog.renderRowsBehind(var23);
    bool var19 = var23.renderMinusFloor(this.maxZ, false, false, var28, var29, var30, var9);
               var23.renderDeferredCharacters(this.maxZ);
               var23.renderCharacters(this.maxZ, false, true);
               if (var23.hasFlies()) {
                  CorpseFlies.render(var23.x, var23.y, var23.z);
               }

               if (var19) {
                  var23.renderMinusFloor(this.maxZ, true, false, var28, var29, var30, var9);
               }
            }

            var11.minusFloorCharacters.end();
         }

         IsoMarkers.instance.renderIsoMarkersDeferred(var1, var10, var3);
         ImprovedFog.endRender();
         var11.end();
      }
   }

    void renderShadows() {
    bool var1 = Core.getInstance().getOptionCorpseShadows();

      for (int var2 = 0; var2 < ShadowSquares.size(); var2++) {
    IsoGridSquare var3 = ShadowSquares.get(var2);

         for (int var4 = 0; var4 < var3.getMovingObjects().size(); var4++) {
    IsoMovingObject var5 = (IsoMovingObject)var3.getMovingObjects().get(var4);
    IsoGameCharacter var6 = (IsoGameCharacter)Type.tryCastTo(var5, IsoGameCharacter.class);
            if (var6 != nullptr) {
               var6.renderShadow(var6.getX(), var6.getY(), var6.getZ());
            } else {
    BaseVehicle var7 = (BaseVehicle)Type.tryCastTo(var5, BaseVehicle.class);
               if (var7 != nullptr) {
                  var7.renderShadow();
               }
            }
         }

         if (var1) {
            for (int var8 = 0; var8 < var3.getStaticMovingObjects().size(); var8++) {
    IsoMovingObject var9 = (IsoMovingObject)var3.getStaticMovingObjects().get(var8);
    IsoDeadBody var10 = (IsoDeadBody)Type.tryCastTo(var9, IsoDeadBody.class);
               if (var10 != nullptr) {
                  var10.renderShadow();
               }
            }
         }
      }
   }

    void renderDebugPhysics(int var1) {
      if (Core.bDebug && DebugOptions.instance.PhysicsRender.getValue()) {
    GenericDrawer var2 = WorldSimulation.getDrawer(var1);
         SpriteRenderer.instance.drawGeneric(var2);
      }
   }

    void renderDebugLighting(PerPlayerRender var1, int var2) {
      if (Core.bDebug && DebugOptions.instance.LightingRender.getValue()) {
    IsoGridStack var3 = var1.GridStacks;
    uint8_t var4 = 1;

         for (int var5 = 0; var5 < var2 + 1; var5++) {
            GridStack = (std::vector<IsoGridSquare>)var3.Squares.get(var5);

            for (int var6 = 0; var6 < GridStack.size(); var6++) {
    IsoGridSquare var7 = GridStack.get(var6);
    float var8 = IsoUtils.XToScreenExact(var7.x + 0.3F, var7.y, 0.0F, 0);
    float var9 = IsoUtils.YToScreenExact(var7.x + 0.3F, var7.y, 0.0F, 0);
    float var10 = IsoUtils.XToScreenExact(var7.x + 0.6F, var7.y, 0.0F, 0);
    float var11 = IsoUtils.YToScreenExact(var7.x + 0.6F, var7.y, 0.0F, 0);
    float var12 = IsoUtils.XToScreenExact(var7.x + 1, var7.y + 0.3F, 0.0F, 0);
    float var13 = IsoUtils.YToScreenExact(var7.x + 1, var7.y + 0.3F, 0.0F, 0);
    float var14 = IsoUtils.XToScreenExact(var7.x + 1, var7.y + 0.6F, 0.0F, 0);
    float var15 = IsoUtils.YToScreenExact(var7.x + 1, var7.y + 0.6F, 0.0F, 0);
    float var16 = IsoUtils.XToScreenExact(var7.x + 0.6F, var7.y + 1, 0.0F, 0);
    float var17 = IsoUtils.YToScreenExact(var7.x + 0.6F, var7.y + 1, 0.0F, 0);
    float var18 = IsoUtils.XToScreenExact(var7.x + 0.3F, var7.y + 1, 0.0F, 0);
    float var19 = IsoUtils.YToScreenExact(var7.x + 0.3F, var7.y + 1, 0.0F, 0);
    float var20 = IsoUtils.XToScreenExact(var7.x, var7.y + 0.6F, 0.0F, 0);
    float var21 = IsoUtils.YToScreenExact(var7.x, var7.y + 0.6F, 0.0F, 0);
    float var22 = IsoUtils.XToScreenExact(var7.x, var7.y + 0.3F, 0.0F, 0);
    float var23 = IsoUtils.YToScreenExact(var7.x, var7.y + 0.3F, 0.0F, 0);
               if (IsoGridSquare.getMatrixBit(var7.visionMatrix, 0, 0, var4)) {
                  LineDrawer.drawLine(var8, var9, var10, var11, 1.0F, 0.0F, 0.0F, 1.0F, 0);
               }

               if (IsoGridSquare.getMatrixBit(var7.visionMatrix, 0, 1, var4)) {
                  LineDrawer.drawLine(var10, var11, var12, var13, 1.0F, 0.0F, 0.0F, 1.0F, 0);
               }

               if (IsoGridSquare.getMatrixBit(var7.visionMatrix, 0, 2, var4)) {
                  LineDrawer.drawLine(var12, var13, var14, var15, 1.0F, 0.0F, 0.0F, 1.0F, 0);
               }

               if (IsoGridSquare.getMatrixBit(var7.visionMatrix, 1, 2, var4)) {
                  LineDrawer.drawLine(var14, var15, var16, var17, 1.0F, 0.0F, 0.0F, 1.0F, 0);
               }

               if (IsoGridSquare.getMatrixBit(var7.visionMatrix, 2, 2, var4)) {
                  LineDrawer.drawLine(var16, var17, var18, var19, 1.0F, 0.0F, 0.0F, 1.0F, 0);
               }

               if (IsoGridSquare.getMatrixBit(var7.visionMatrix, 2, 1, var4)) {
                  LineDrawer.drawLine(var18, var19, var20, var21, 1.0F, 0.0F, 0.0F, 1.0F, 0);
               }

               if (IsoGridSquare.getMatrixBit(var7.visionMatrix, 2, 0, var4)) {
                  LineDrawer.drawLine(var20, var21, var22, var23, 1.0F, 0.0F, 0.0F, 1.0F, 0);
               }

               if (IsoGridSquare.getMatrixBit(var7.visionMatrix, 1, 0, var4)) {
                  LineDrawer.drawLine(var22, var23, var8, var9, 1.0F, 0.0F, 0.0F, 1.0F, 0);
               }
            }
         }
      }
   }

    void CullFullyOccludedSquares(IsoGridStack var1, boolean[][][] var2, boolean[][] var3) {
    int var4 = 0;

      for (int var5 = 1; var5 < MaxHeight + 1; var5++) {
         var4 += ((std::vector)var1.Squares.get(var5)).size();
      }

      if (var4 >= 500) {
    int var16 = 0;

         for (int var6 = MaxHeight; var6 >= 0; var6--) {
            GridStack = (std::vector<IsoGridSquare>)var1.Squares.get(var6);

            for (int var7 = GridStack.size() - 1; var7 >= 0; var7--) {
    IsoGridSquare var8 = GridStack.get(var7);
    int var9 = var8.getX() - var6 * 3 - this.minX;
    int var10 = var8.getY() - var6 * 3 - this.minY;
               if (var9 < 0 || var9 >= var3.length) {
                  GridStack.remove(var7);
               } else if (var10 >= 0 && var10 < var3[0].length) {
                  if (var6 < MaxHeight) {
    bool var11 = !var3[var9][var10];
                     if (var11) {
                        var11 = false;
                        if (var9 > 2) {
                           if (var10 > 2) {
                              var11 = !var2[var9 - 3][var10 - 3][0]
                                 || !var2[var9 - 3][var10 - 3][1]
                                 || !var2[var9 - 3][var10 - 2][0]
                                 || !var2[var9 - 2][var10 - 3][1]
                                 || !var2[var9 - 2][var10 - 2][0]
                                 || !var2[var9 - 2][var10 - 2][1]
                                 || !var2[var9 - 2][var10 - 1][0]
                                 || !var2[var9 - 1][var10 - 2][0]
                                 || !var2[var9 - 1][var10 - 1][1]
                                 || !var2[var9 - 1][var10 - 1][0]
                                 || !var2[var9 - 1][var10][0]
                                 || !var2[var9][var10 - 1][1]
                                 || !var2[var9][var10][0]
                                 || !var2[var9][var10][1];
                           } else if (var10 > 1) {
                              var11 = !var2[var9 - 3][var10 - 2][0]
                                 || !var2[var9 - 2][var10 - 2][0]
                                 || !var2[var9 - 2][var10 - 2][1]
                                 || !var2[var9 - 2][var10 - 1][0]
                                 || !var2[var9 - 1][var10 - 2][0]
                                 || !var2[var9 - 1][var10 - 1][1]
                                 || !var2[var9 - 1][var10 - 1][0]
                                 || !var2[var9 - 1][var10][0]
                                 || !var2[var9][var10 - 1][1]
                                 || !var2[var9][var10][0]
                                 || !var2[var9][var10][1];
                           } else if (var10 > 0) {
                              var11 = !var2[var9 - 2][var10 - 1][0]
                                 || !var2[var9 - 1][var10 - 1][1]
                                 || !var2[var9 - 1][var10 - 1][0]
                                 || !var2[var9 - 1][var10][0]
                                 || !var2[var9][var10 - 1][1]
                                 || !var2[var9][var10][0]
                                 || !var2[var9][var10][1];
                           } else {
                              var11 = !var2[var9 - 1][var10][0] || !var2[var9][var10][0] || !var2[var9][var10][1];
                           }
                        } else if (var9 > 1) {
                           if (var10 > 2) {
                              var11 = !var2[var9 - 2][var10 - 3][1]
                                 || !var2[var9 - 2][var10 - 2][0]
                                 || !var2[var9 - 2][var10 - 2][1]
                                 || !var2[var9 - 2][var10 - 1][0]
                                 || !var2[var9 - 1][var10 - 2][0]
                                 || !var2[var9 - 1][var10 - 1][1]
                                 || !var2[var9 - 1][var10 - 1][0]
                                 || !var2[var9 - 1][var10][0]
                                 || !var2[var9][var10 - 1][1]
                                 || !var2[var9][var10][0]
                                 || !var2[var9][var10][1];
                           } else if (var10 > 1) {
                              var11 = !var2[var9 - 2][var10 - 2][0]
                                 || !var2[var9 - 2][var10 - 2][1]
                                 || !var2[var9 - 2][var10 - 1][0]
                                 || !var2[var9 - 1][var10 - 2][0]
                                 || !var2[var9 - 1][var10 - 1][1]
                                 || !var2[var9 - 1][var10 - 1][0]
                                 || !var2[var9 - 1][var10][0]
                                 || !var2[var9][var10 - 1][1]
                                 || !var2[var9][var10][0]
                                 || !var2[var9][var10][1];
                           } else if (var10 > 0) {
                              var11 = !var2[var9 - 2][var10 - 1][0]
                                 || !var2[var9 - 1][var10 - 1][1]
                                 || !var2[var9 - 1][var10 - 1][0]
                                 || !var2[var9 - 1][var10][0]
                                 || !var2[var9][var10 - 1][1]
                                 || !var2[var9][var10][0]
                                 || !var2[var9][var10][1];
                           } else {
                              var11 = !var2[var9 - 1][var10][0] || !var2[var9][var10][0] || !var2[var9][var10][1];
                           }
                        } else if (var9 > 0) {
                           if (var10 > 2) {
                              var11 = !var2[var9 - 1][var10 - 2][0]
                                 || !var2[var9 - 1][var10 - 1][1]
                                 || !var2[var9 - 1][var10 - 1][0]
                                 || !var2[var9 - 1][var10][0]
                                 || !var2[var9][var10 - 1][1]
                                 || !var2[var9][var10][0]
                                 || !var2[var9][var10][1];
                           } else if (var10 > 1) {
                              var11 = !var2[var9 - 1][var10 - 2][0]
                                 || !var2[var9 - 1][var10 - 1][1]
                                 || !var2[var9 - 1][var10 - 1][0]
                                 || !var2[var9 - 1][var10][0]
                                 || !var2[var9][var10 - 1][1]
                                 || !var2[var9][var10][0]
                                 || !var2[var9][var10][1];
                           } else if (var10 > 0) {
                              var11 = !var2[var9 - 1][var10 - 1][1]
                                 || !var2[var9 - 1][var10 - 1][0]
                                 || !var2[var9 - 1][var10][0]
                                 || !var2[var9][var10 - 1][1]
                                 || !var2[var9][var10][0]
                                 || !var2[var9][var10][1];
                           } else {
                              var11 = !var2[var9 - 1][var10][0] || !var2[var9][var10][0] || !var2[var9][var10][1];
                           }
                        } else if (var10 > 2) {
                           var11 = !var2[var9][var10 - 1][1] || !var2[var9][var10][0] || !var2[var9][var10][1];
                        } else if (var10 > 1) {
                           var11 = !var2[var9][var10 - 1][1] || !var2[var9][var10][0] || !var2[var9][var10][1];
                        } else if (var10 > 0) {
                           var11 = !var2[var9][var10 - 1][1] || !var2[var9][var10][0] || !var2[var9][var10][1];
                        } else {
                           var11 = !var2[var9][var10][0] || !var2[var9][var10][1];
                        }
                     }

                     if (!var11) {
                        GridStack.remove(var7);
                        var3[var9][var10] = true;
                        continue;
                     }
                  }

                  var16++;
    bool var18 = IsoGridSquare.getMatrixBit(var8.visionMatrix, 0, 1, 1) && var8.getProperties().Is(IsoFlagType.cutW);
    bool var12 = IsoGridSquare.getMatrixBit(var8.visionMatrix, 1, 0, 1) && var8.getProperties().Is(IsoFlagType.cutN);
    bool var13 = false;
                  if (var18 || var12) {
                     var13 = (var8.x > IsoCamera.frameState.CamCharacterX || var8.y > IsoCamera.frameState.CamCharacterY)
                        && var8.z >= (int)IsoCamera.frameState.CamCharacterZ;
                     if (var13) {
    int var14 = (int)(var8.CachedScreenX - IsoCamera.frameState.OffX);
    int var15 = (int)(var8.CachedScreenY - IsoCamera.frameState.OffY);
                        if (var14 + 32 * Core.TileScale <= this.StencilX1
                           || var14 - 32 * Core.TileScale >= this.StencilX2
                           || var15 + 32 * Core.TileScale <= this.StencilY1
                           || var15 - 96 * Core.TileScale >= this.StencilY2) {
                           var13 = false;
                        }
                     }
                  }

    int var19 = 0;
                  if (var18 && !var13) {
                     var19++;
                     if (var9 > 0) {
                        var2[var9 - 1][var10][0] = true;
                        if (var10 > 0) {
                           var2[var9 - 1][var10 - 1][1] = true;
                        }
                     }

                     if (var9 > 1 && var10 > 0) {
                        var2[var9 - 2][var10 - 1][0] = true;
                        if (var10 > 1) {
                           var2[var9 - 2][var10 - 2][1] = true;
                        }
                     }

                     if (var9 > 2 && var10 > 1) {
                        var2[var9 - 3][var10 - 2][0] = true;
                        if (var10 > 2) {
                           var2[var9 - 3][var10 - 3][1] = true;
                        }
                     }
                  }

                  if (var12 && !var13) {
                     var19++;
                     if (var10 > 0) {
                        var2[var9][var10 - 1][1] = true;
                        if (var9 > 0) {
                           var2[var9 - 1][var10 - 1][0] = true;
                        }
                     }

                     if (var10 > 1 && var9 > 0) {
                        var2[var9 - 1][var10 - 2][1] = true;
                        if (var9 > 1) {
                           var2[var9 - 2][var10 - 2][0] = true;
                        }
                     }

                     if (var10 > 2 && var9 > 1) {
                        var2[var9 - 2][var10 - 3][1] = true;
                        if (var9 > 2) {
                           var2[var9 - 3][var10 - 3][0] = true;
                        }
                     }
                  }

                  if (IsoGridSquare.getMatrixBit(var8.visionMatrix, 1, 1, 0)) {
                     var19++;
                     var2[var9][var10][0] = true;
                     var2[var9][var10][1] = true;
                  }

                  if (var19 == 3) {
                     var3[var9][var10] = true;
                  }
               } else {
                  GridStack.remove(var7);
               }
            }
         }
      }
   }

    void RenderFloorShading(int var1) {
      if (DebugOptions.instance.Terrain.RenderTiles.IsoGridSquare.Floor.LightingOld.getValue()
         && !DebugOptions.instance.Terrain.RenderTiles.IsoGridSquare.Floor.Lighting.getValue()) {
         if (var1 < this.maxZ && PerformanceSettings.LightingFrameSkip < 3) {
            if (!Core.bDebug || !DebugOptions.instance.DebugDraw_SkipWorldShading.getValue()) {
               if (texWhite == nullptr) {
                  texWhite = Texture.getWhite();
               }

    Texture var2 = texWhite;
               if (var2 != nullptr) {
    int var3 = IsoCamera.frameState.playerIndex;
    int var4 = (int)IsoCamera.frameState.OffX;
    int var5 = (int)IsoCamera.frameState.OffY;

                  for (int var6 = 0; var6 < ShadedFloor.size(); var6++) {
    IsoGridSquare var7 = ShadedFloor.get(var6);
                     if (var7.getProperties().Is(IsoFlagType.solidfloor)) {
    float var8 = 0.0F;
    float var9 = 0.0F;
    float var10 = 0.0F;
                        if (var7.getProperties().Is(IsoFlagType.FloorHeightOneThird)) {
                           var9 = -1.0F;
                           var8 = -1.0F;
                        } else if (var7.getProperties().Is(IsoFlagType.FloorHeightTwoThirds)) {
                           var9 = -2.0F;
                           var8 = -2.0F;
                        }

    float var11 = IsoUtils.XToScreen(var7.getX() + var8, var7.getY() + var9, var1 + var10, 0);
    float var12 = IsoUtils.YToScreen(var7.getX() + var8, var7.getY() + var9, var1 + var10, 0);
                        var11 -= var4;
                        var12 -= var5;
    int var13 = var7.getVertLight(0, var3);
    int var14 = var7.getVertLight(1, var3);
    int var15 = var7.getVertLight(2, var3);
    int var16 = var7.getVertLight(3, var3);
                        if (DebugOptions.instance.Terrain.RenderTiles.IsoGridSquare.Floor.LightingDebug.getValue()) {
                           var13 = -65536;
                           var14 = -65536;
                           var15 = -16776961;
                           var16 = -16776961;
                        }

                        var2.renderdiamond(
                           var11 - 32 * Core.TileScale, var12 + 16 * Core.TileScale, 64 * Core.TileScale, 32 * Core.TileScale, var16, var13, var14, var15
                        );
                     }
                  }
               }
            }
         }
      }
   }

    bool IsPlayerWindowPeeking(int var1) {
      return this.playerWindowPeekingRoomId[var1] != -1;
   }

    bool CanBuildingSquareOccludePlayer(IsoGridSquare var1, int var2) {
    std::vector var3 = this.playerOccluderBuildings.get(var2);

      for (int var4 = 0; var4 < var3.size(); var4++) {
    IsoBuilding var5 = (IsoBuilding)var3.get(var4);
    int var6 = var5.getDef().getX();
    int var7 = var5.getDef().getY();
    int var8 = var5.getDef().getX2() - var6;
    int var9 = var5.getDef().getY2() - var7;
         this.buildingRectTemp.setBounds(var6 - 1, var7 - 1, var8 + 2, var9 + 2);
         if (this.buildingRectTemp.contains(var1.getX(), var1.getY())) {
    return true;
         }
      }

    return false;
   }

    int GetEffectivePlayerRoomId() {
    int var1 = IsoCamera.frameState.playerIndex;
    int var2 = this.playerWindowPeekingRoomId[var1];
      if (IsoPlayer.players[var1] != nullptr && IsoPlayer.players[var1].isClimbing()) {
         var2 = -1;
      }

      if (var2 != -1) {
    return var2;
      } else {
    IsoGridSquare var3 = IsoPlayer.players[var1].current;
         return var3 != nullptr ? var3.getRoomID() : -1;
      }
   }

    bool SetCutawayRoomsForPlayer() {
    int var1 = IsoCamera.frameState.playerIndex;
    IsoPlayer var2 = IsoPlayer.players[var1];
    std::vector var3 = this.tempPrevPlayerCutawayRoomIDs;
      this.tempPrevPlayerCutawayRoomIDs = this.tempPlayerCutawayRoomIDs;
      this.tempPlayerCutawayRoomIDs = var3;
      this.tempPlayerCutawayRoomIDs.clear();
    IsoGridSquare var4 = var2.getSquare();
      if (var4 == nullptr) {
    return false;
      } else {
    IsoBuilding var5 = var4.getBuilding();
    int var6 = var4.getRoomID();
    bool var7 = false;
         if (var6 == -1) {
            if (this.playerWindowPeekingRoomId[var1] != -1) {
               this.tempPlayerCutawayRoomIDs.push_back(this.playerWindowPeekingRoomId[var1]);
            } else {
               var7 = this.playerCutawaysDirty[var1];
            }
         } else {
    int var8 = (int)(var2.getX() - 1.5F);
    int var9 = (int)(var2.getY() - 1.5F);
    int var10 = (int)(var2.getX() + 1.5F);
    int var11 = (int)(var2.getY() + 1.5F);

            for (int var12 = var8; var12 <= var10; var12++) {
               for (int var13 = var9; var13 <= var11; var13++) {
    IsoGridSquare var14 = this.getGridSquare(var12, var13, var4.getZ());
                  if (var14 != nullptr) {
    int var15 = var14.getRoomID();
                     if (var14.getCanSee(var1) && var15 != -1 && !this.tempPlayerCutawayRoomIDs.contains(var15)) {
                        this.tempCutawaySqrVector.set(var14.getX() + 0.5F - var2.getX(), var14.getY() + 0.5F - var2.getY());
                        if (var4 == var14 || var2.getForwardDirection().dot(this.tempCutawaySqrVector) > 0.0F) {
                           this.tempPlayerCutawayRoomIDs.push_back(var15);
                        }
                     }
                  }
               }
            }

            Collections.sort(this.tempPlayerCutawayRoomIDs);
         }

         return var7 || !this.tempPlayerCutawayRoomIDs == this.tempPrevPlayerCutawayRoomIDs);
      }
   }

    bool IsCutawaySquare(IsoGridSquare var1, long var2) {
    int var4 = IsoCamera.frameState.playerIndex;
    IsoPlayer var5 = IsoPlayer.players[var4];
      if (var5.current == nullptr) {
    return false;
      } else if (var1 == nullptr) {
    return false;
      } else {
    IsoGridSquare var6 = var5.current;
         if (var6.getZ() != var1.getZ()) {
    return false;
         } else {
            if (this.tempPlayerCutawayRoomIDs.empty()) {
    IsoGridSquare var7 = var1.nav[IsoDirections.N.index()];
    IsoGridSquare var8 = var1.nav[IsoDirections.W.index()];
               if (this.IsCollapsibleBuildingSquare(var1)) {
                  if (var5.getZ() == 0.0F) {
    return true;
                  }

                  if (var1.getBuilding() != nullptr && (var6.getX() < var1.getBuilding().def.x || var6.getY() < var1.getBuilding().def.y)) {
    return true;
                  }

    IsoGridSquare var9 = var1;

                  for (int var10 = 0; var10 < 3; var10++) {
                     var9 = var9.nav[IsoDirections.NW.index()];
                     if (var9 == nullptr) {
                        break;
                     }

                     if (var9.isCanSee(var4)) {
    return true;
                     }
                  }
               }

               if (var7 != nullptr && var7.getRoomID() == -1 && var8 != nullptr && var8.getRoomID() == -1) {
                  return this.DoesSquareHaveValidCutaways(var6, var1, var4, var2);
               }
            } else {
    IsoGridSquare var19 = var1.nav[IsoDirections.N.index()];
    IsoGridSquare var20 = var1.nav[IsoDirections.E.index()];
    IsoGridSquare var21 = var1.nav[IsoDirections.S.index()];
    IsoGridSquare var22 = var1.nav[IsoDirections.W.index()];
    IsoGridSquare var11 = var6.nav[IsoDirections.N.index()];
    IsoGridSquare var12 = var6.nav[IsoDirections.E.index()];
    IsoGridSquare var13 = var6.nav[IsoDirections.S.index()];
    IsoGridSquare var14 = var6.nav[IsoDirections.W.index()];
    bool var15 = false;
    bool var16 = false;

               for (int var17 = 0; var17 < 8; var17++) {
                  if (var1.nav[var17] != nullptr && var1.nav[var17].getRoomID() != var1.getRoomID()) {
                     var15 = true;
                     break;
                  }
               }

               if (!this.tempPlayerCutawayRoomIDs.contains(var1.getRoomID())) {
                  var16 = true;
               }

               if (var15 || var16 || var1.getWall() != nullptr) {
    IsoGridSquare var23 = var1;

                  for (int var18 = 0; var18 < 3; var18++) {
                     var23 = var23.nav[IsoDirections.NW.index()];
                     if (var23 == nullptr) {
                        break;
                     }

                     if (var23.getRoomID() != -1 && this.tempPlayerCutawayRoomIDs.contains(var23.getRoomID())) {
                        if ((var15 || var16) && var23.getCanSee(var4)) {
    return true;
                        }

                        if (var1.getWall() != nullptr && var23.isCouldSee(var4)) {
    return true;
                        }
                     }
                  }
               }

               if (var19 != nullptr
                  && var22 != nullptr
                  && (
                     var19.getThumpableWallOrHoppable(false) != nullptr
                        || var22.getThumpableWallOrHoppable(true) != nullptr
                        || var1.getThumpableWallOrHoppable(true) != nullptr
                        || var1.getThumpableWallOrHoppable(false) != nullptr
                  )) {
                  return this.DoesSquareHaveValidCutaways(var6, var1, var4, var2);
               }

               if (var6.getRoomID() == -1
                  && (
                     var11 != nullptr && var11.getRoomID() != -1
                        || var12 != nullptr && var12.getRoomID() != -1
                        || var13 != nullptr && var13.getRoomID() != -1
                        || var14 != nullptr && var14.getRoomID() != -1
                  )) {
    int var24 = var6.x - var1.x;
    int var25 = var6.y - var1.y;
                  if (var24 < 0 && var25 < 0) {
                     if (var24 >= -3) {
                        if (var25 >= -3) {
    return true;
                        }

                        if (var19 != nullptr
                           && var21 != nullptr
                           && var1.getWall(false) != nullptr
                           && var19.getWall(false) != nullptr
                           && var21.getWall(false) != nullptr
                           && var21.getPlayerCutawayFlag(var4, var2)) {
    return true;
                        }
                     } else if (var20 != nullptr && var22 != nullptr) {
                        if (var1.getWall(true) != nullptr && var22.getWall(true) != nullptr && var20.getWall(true) != nullptr && var20.getPlayerCutawayFlag(var4, var2)) {
    return true;
                        }

                        if (var1.getWall(true) != nullptr && var22.getWall(true) != nullptr && var20.getWall(true) != nullptr && var20.getPlayerCutawayFlag(var4, var2)) {
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

    bool DoesSquareHaveValidCutaways(IsoGridSquare var1, IsoGridSquare var2, int var3, long var4) {
    IsoGridSquare var6 = var2.nav[IsoDirections.N.index()];
    IsoGridSquare var7 = var2.nav[IsoDirections.E.index()];
    IsoGridSquare var8 = var2.nav[IsoDirections.S.index()];
    IsoGridSquare var9 = var2.nav[IsoDirections.W.index()];
    IsoObject var10 = var2.getWall(true);
    IsoObject var11 = var2.getWall(false);
    IsoObject var12 = nullptr;
    IsoObject var13 = nullptr;
      if (var6 != nullptr && var6.nav[IsoDirections.W.index()] != nullptr && var6.nav[IsoDirections.W.index()].getRoomID() == var6.getRoomID()) {
         var13 = var6.getWall(false);
      }

      if (var9 != nullptr && var9.nav[IsoDirections.N.index()] != nullptr && var9.nav[IsoDirections.N.index()].getRoomID() == var9.getRoomID()) {
         var12 = var9.getWall(true);
      }

      if (var11 != nullptr || var10 != nullptr || var13 != nullptr || var12 != nullptr) {
    IsoGridSquare var14 = var2.nav[IsoDirections.NW.index()];

         for (int var15 = 0; var15 < 2 && var14 != nullptr && var14.getRoomID() == var1.getRoomID(); var15++) {
    IsoGridSquare var16 = var14.nav[IsoDirections.S.index()];
    IsoGridSquare var17 = var14.nav[IsoDirections.E.index()];
            if (var16 != nullptr && var16.getBuilding() != nullptr || var17 != nullptr && var17.getBuilding() != nullptr) {
               break;
            }

            if (var14.isCanSee(var3) && var14.isCouldSee(var3) && var14.DistTo(var1) <= 6 - (var15 + 1)) {
    return true;
            }

            if (var14.getBuilding() == nullptr) {
               var14 = var14.nav[IsoDirections.NW.index()];
            }
         }
      }

    int var18 = var1.x - var2.x;
    int var19 = var1.y - var2.y;
      if ((var10 == nullptr || !var10.sprite.name.contains("fencing")) && (var11 == nullptr || !var11.sprite.name.contains("fencing"))) {
         if (var2.DistTo(var1) <= 6.0F
            && var2.nav[IsoDirections.NW.index()] != nullptr
            && var2.nav[IsoDirections.NW.index()].getRoomID() == var2.getRoomID()
            && (var2.getWall(true) == nullptr || var2.getWall(true) == var10)
            && (var2.getWall(false) == nullptr || var2.getWall(false) == var11)) {
            if (var8 != nullptr && var6 != nullptr && var19 != 0) {
               if (var19 > 0 && var11 != nullptr && var8.getWall(false) != nullptr && var6.getWall(false) != nullptr && var8.getPlayerCutawayFlag(var3, var4)) {
    return true;
               }

               if (var19 < 0 && var11 != nullptr && var6.getWall(false) != nullptr && var6.getPlayerCutawayFlag(var3, var4)) {
    return true;
               }
            }

            if (var7 != nullptr && var9 != nullptr && var18 != 0) {
               if (var18 > 0 && var10 != nullptr && var7.getWall(true) != nullptr && var9.getWall(true) != nullptr && var7.getPlayerCutawayFlag(var3, var4)) {
    return true;
               }

               if (var18 < 0 && var10 != nullptr && var9.getWall(true) != nullptr && var9.getPlayerCutawayFlag(var3, var4)) {
    return true;
               }
            }
         }
      } else {
         if (var10 != nullptr && var12 != nullptr && var19 >= -6 && var19 < 0) {
    return true;
         }

         if (var11 != nullptr && var13 != nullptr && var18 >= -6 && var18 < 0) {
    return true;
         }
      }

      if (var2 == var1 && var2.nav[IsoDirections.NW.index()] != nullptr && var2.nav[IsoDirections.NW.index()].getRoomID() == var2.getRoomID()) {
         if (var10 != nullptr && var6 != nullptr && var6.getWall(false) == nullptr && var6.isCanSee(var3) && var6.isCouldSee(var3)) {
    return true;
         }

         if (var11 != nullptr && var9 != nullptr && var9.getWall(true) != nullptr && var9.isCanSee(var3) && var9.isCouldSee(var3)) {
    return true;
         }
      }

      return var6 != nullptr
            && var9 != nullptr
            && var18 != 0
            && var19 != 0
            && var13 != nullptr
            && var12 != nullptr
            && var6.getPlayerCutawayFlag(var3, var4)
            && var9.getPlayerCutawayFlag(var3, var4)
         ? true
         : var18 < 0
            && var18 >= -6
            && var19 < 0
            && var19 >= -6
            && (var11 != nullptr && var2.getWall(true) == nullptr || var10 != nullptr && var2.getWall(false) == nullptr);
   }

    bool IsCollapsibleBuildingSquare(IsoGridSquare var1) {
      if (var1.getProperties().Is(IsoFlagType.forceRender)) {
    return false;
      } else {
         for (int var2 = 0; var2 < 4; var2++) {
    short var3 = 500;

            for (int var4 = 0; var4 < var3 && this.playerOccluderBuildingsArr[var2] != nullptr; var4++) {
    IsoBuilding var5 = this.playerOccluderBuildingsArr[var2][var4];
               if (var5 == nullptr) {
                  break;
               }

    BuildingDef var6 = var5.getDef();
               if (this.collapsibleBuildingSquareAlgorithm(var6, var1, IsoPlayer.players[var2].getSquare())) {
    return true;
               }

               if (var1.getY() - var6.getY2() == 1 && var1.getWall(true) != nullptr) {
    return true;
               }

               if (var1.getX() - var6.getX2() == 1 && var1.getWall(false) != nullptr) {
    return true;
               }
            }
         }

    int var7 = IsoCamera.frameState.playerIndex;
    IsoPlayer var8 = IsoPlayer.players[var7];
         if (var8.getVehicle() != nullptr) {
    return false;
         } else {
            for (int var9 = 0; var9 < 500 && this.zombieOccluderBuildingsArr[var7] != nullptr; var9++) {
    IsoBuilding var11 = this.zombieOccluderBuildingsArr[var7][var9];
               if (var11 == nullptr) {
                  break;
               }

    BuildingDef var13 = var11.getDef();
               if (this.collapsibleBuildingSquareAlgorithm(var13, var1, var8.getSquare())) {
    return true;
               }
            }

            for (int var10 = 0; var10 < 500 && this.otherOccluderBuildingsArr[var7] != nullptr; var10++) {
    IsoBuilding var12 = this.otherOccluderBuildingsArr[var7][var10];
               if (var12 == nullptr) {
                  break;
               }

    BuildingDef var14 = var12.getDef();
               if (this.collapsibleBuildingSquareAlgorithm(var14, var1, var8.getSquare())) {
    return true;
               }
            }

    return false;
         }
      }
   }

    bool collapsibleBuildingSquareAlgorithm(BuildingDef var1, IsoGridSquare var2, IsoGridSquare var3) {
    int var4 = var1.getX();
    int var5 = var1.getY();
    int var6 = var1.getX2() - var4;
    int var7 = var1.getY2() - var5;
      this.buildingRectTemp.setBounds(var4, var5, var6, var7);
      if (var3.getRoomID() == -1 && this.buildingRectTemp.contains(var3.getX(), var3.getY())) {
         this.buildingRectTemp.setBounds(var4 - 1, var5 - 1, var6 + 2, var7 + 2);
    IsoGridSquare var8 = var2.nav[IsoDirections.N.index()];
    IsoGridSquare var9 = var2.nav[IsoDirections.W.index()];
    IsoGridSquare var10 = var2.nav[IsoDirections.NW.index()];
         if (var10 != nullptr && var8 != nullptr && var9 != nullptr) {
    bool var11 = var2.getRoomID() == -1;
    bool var12 = var8.getRoomID() == -1;
    bool var13 = var9.getRoomID() == -1;
    bool var14 = var10.getRoomID() == -1;
    bool var15 = var3.getY() < var2.getY();
    bool var16 = var3.getX() < var2.getX();
            return this.buildingRectTemp.contains(var2.getX(), var2.getY())
               && (
                  var3.getZ() < var2.getZ()
                     || var11 && (!var12 && var15 || !var13 && var16)
                     || var11 && var12 && var13 && !var14
                     || !var11 && (var14 || var12 == var13 || var12 && var16 || var13 && var15)
               );
         } else {
    return false;
         }
      } else {
         this.buildingRectTemp.setBounds(var4 - 1, var5 - 1, var6 + 2, var7 + 2);
         return this.buildingRectTemp.contains(var2.getX(), var2.getY());
      }
   }

    bool IsDissolvedSquare(IsoGridSquare var1, int var2) {
    IsoPlayer var3 = IsoPlayer.players[var2];
      if (var3.current == nullptr) {
    return false;
      } else {
    IsoGridSquare var4 = var3.current;
         if (var4.getZ() >= var1.getZ()) {
    return false;
         } else if (!PerformanceSettings.NewRoofHiding) {
            return this.bHideFloors[var2] && var1.getZ() >= this.maxZ;
         } else {
            if (var1.getZ() > this.hidesOrphanStructuresAbove) {
    IsoBuilding var5 = var1.getBuilding();
               if (var5 == nullptr) {
                  var5 = var1.roofHideBuilding;
               }

               for (int var6 = var1.getZ() - 1; var6 >= 0 && var5 == nullptr; var6--) {
    IsoGridSquare var7 = this.getGridSquare(var1.x, var1.y, var6);
                  if (var7 != nullptr) {
                     var5 = var7.getBuilding();
                     if (var5 == nullptr) {
                        var5 = var7.roofHideBuilding;
                     }
                  }
               }

               if (var5 == nullptr) {
                  if (var1.isSolidFloor()) {
    return true;
                  }

    IsoGridSquare var9 = var1.nav[IsoDirections.N.index()];
                  if (var9 != nullptr && var9.getBuilding() == nullptr) {
                     if (var9.getPlayerBuiltFloor() != nullptr) {
    return true;
                     }

                     if (var9.HasStairsBelow()) {
    return true;
                     }
                  }

    IsoGridSquare var10 = var1.nav[IsoDirections.W.index()];
                  if (var10 != nullptr && var10.getBuilding() == nullptr) {
                     if (var10.getPlayerBuiltFloor() != nullptr) {
    return true;
                     }

                     if (var10.HasStairsBelow()) {
    return true;
                     }
                  }

                  if (var1.Is(IsoFlagType.WallSE)) {
    IsoGridSquare var8 = var1.nav[IsoDirections.NW.index()];
                     if (var8 != nullptr && var8.getBuilding() == nullptr) {
                        if (var8.getPlayerBuiltFloor() != nullptr) {
    return true;
                        }

                        if (var8.HasStairsBelow()) {
    return true;
                        }
                     }
                  }
               }
            }

            return this.IsCollapsibleBuildingSquare(var1);
         }
      }
   }

    int GetBuildingHeightAt(IsoBuilding var1, int var2, int var3, int var4) {
      for (int var5 = MaxHeight; var5 > var4; var5--) {
    IsoGridSquare var6 = this.getGridSquare(var2, var3, var5);
         if (var6 != nullptr && var6.getBuilding() == var1) {
    return var5;
         }
      }

    return var4;
   }

    void updateSnow(int var1) {
      if (this.snowGridCur == nullptr) {
         this.snowGridCur = std::make_shared<SnowGrid>(this, var1);
         this.snowGridPrev = std::make_shared<SnowGrid>(this, 0);
      } else {
         if (var1 != this.snowGridCur.frac) {
            this.snowGridPrev.init(this.snowGridCur.frac);
            this.snowGridCur.init(var1);
            this.snowFadeTime = System.currentTimeMillis();
            DebugLog.log("snow from " + this.snowGridPrev.frac + " to " + this.snowGridCur.frac);
         }
      }
   }

    void setSnowTarget(int var1) {
      if (!SandboxOptions.instance.EnableSnowOnGround.getValue()) {
         var1 = 0;
      }

      this.snowFracTarget = var1;
   }

    bool gridSquareIsSnow(int var1, int var2, int var3) {
    IsoGridSquare var4 = this.getGridSquare(var1, var2, var3);
      if (var4 != nullptr) {
         if (!var4.getProperties().Is(IsoFlagType.solidfloor)) {
    return false;
         } else if (var4.getProperties().Is(IsoFlagType.water)) {
    return false;
         } else if (var4.getProperties().Is(IsoFlagType.exterior) && var4.room == nullptr && !var4.isInARoom()) {
    int var5 = var4.getX() % this.snowGridCur.w;
    int var6 = var4.getY() % this.snowGridCur.h;
            return this.snowGridCur.check(var5, var6);
         } else {
    return false;
         }
      } else {
    return false;
      }
   }

    void RenderSnow(int var1) {
      if (DebugOptions.instance.Weather.Snow.getValue()) {
         this.updateSnow(this.snowFracTarget);
    SnowGrid var2 = this.snowGridCur;
         if (var2 != nullptr) {
    SnowGrid var3 = this.snowGridPrev;
            if (var2.frac > 0 || var3.frac > 0) {
    float var4 = 1.0F;
    float var5 = 0.0F;
    long var6 = System.currentTimeMillis();
    long var8 = var6 - this.snowFadeTime;
               if ((float)var8 < this.snowTransitionTime) {
    float var10 = (float)var8 / this.snowTransitionTime;
                  var4 = var10;
                  var5 = 1.0F - var10;
               }

    Shader var27 = nullptr;
               if (DebugOptions.instance.Terrain.RenderTiles.UseShaders.getValue()) {
                  var27 = m_floorRenderShader;
               }

               FloorShaperAttachedSprites.instance.setShore(false);
               FloorShaperDiamond.instance.setShore(false);
               IndieGL.StartShader(var27, IsoCamera.frameState.playerIndex);
    int var11 = (int)IsoCamera.frameState.OffX;
    int var12 = (int)IsoCamera.frameState.OffY;

               for (int var13 = 0; var13 < SolidFloor.size(); var13++) {
    IsoGridSquare var14 = SolidFloor.get(var13);
                  if (var14.room == nullptr && var14.getProperties().Is(IsoFlagType.exterior) && var14.getProperties().Is(IsoFlagType.solidfloor)) {
    int var15;
                     if (var14.getProperties().Is(IsoFlagType.water)) {
                        var15 = getShoreInt(var14);
                        if (var15 == 0) {
                           continue;
                        }
                     } else {
                        var15 = 0;
                     }

    int var16 = var14.getX() % var2.w;
    int var17 = var14.getY() % var2.h;
    float var18 = IsoUtils.XToScreen(var14.getX(), var14.getY(), var1, 0);
    float var19 = IsoUtils.YToScreen(var14.getX(), var14.getY(), var1, 0);
                     var18 -= var11;
                     var19 -= var12;
    float var20 = 32 * Core.TileScale;
    float var21 = 96 * Core.TileScale;
                     var18 -= var20;
                     var19 -= var21;
    int var22 = IsoCamera.frameState.playerIndex;
    int var23 = var14.getVertLight(0, var22);
    int var24 = var14.getVertLight(1, var22);
    int var25 = var14.getVertLight(2, var22);
    int var26 = var14.getVertLight(3, var22);
                     if (DebugOptions.instance.Terrain.RenderTiles.IsoGridSquare.Floor.LightingDebug.getValue()) {
                        var23 = -65536;
                        var24 = -65536;
                        var25 = -16776961;
                        var26 = -16776961;
                     }

                     FloorShaperAttachedSprites.instance.setVertColors(var23, var24, var25, var26);
                     FloorShaperDiamond.instance.setVertColors(var23, var24, var25, var26);

                     for (int var32 = 0; var32 < 2; var32++) {
                        if (var5 > var4) {
                           this.renderSnowTileGeneral(var2, var4, var14, var15, var16, var17, (int)var18, (int)var19, var32);
                           this.renderSnowTileGeneral(var3, var5, var14, var15, var16, var17, (int)var18, (int)var19, var32);
                        } else {
                           this.renderSnowTileGeneral(var3, var5, var14, var15, var16, var17, (int)var18, (int)var19, var32);
                           this.renderSnowTileGeneral(var2, var4, var14, var15, var16, var17, (int)var18, (int)var19, var32);
                        }
                     }
                  }
               }

               IndieGL.StartShader(nullptr);
            }
         }
      }
   }

    void renderSnowTileGeneral(SnowGrid var1, float var2, IsoGridSquare var3, int var4, int var5, int var6, int var7, int var8, int var9) {
      if (!(var2 <= 0.0F)) {
    Texture var10 = var1.grid[var5][var6][var9];
         if (var10 != nullptr) {
            if (var9 == 0) {
               this.renderSnowTile(var1, var5, var6, var9, var3, var4, var10, var7, var8, var2);
            } else if (var4 == 0) {
    uint8_t var11 = var1.gridType[var5][var6][var9];
               this.renderSnowTileBase(var10, var7, var8, var2, var11 < this.m_snowFirstNonSquare);
            }
         }
      }
   }

    void renderSnowTileBase(Texture var1, int var2, int var3, float var4, bool var5) {
    void* var6 = var5 ? FloorShaperDiamond.instance : FloorShaperAttachedSprites.instance;
      var6.setAlpha4(var4);
      var1.render(var2, var3, var1.getWidth(), var1.getHeight(), 1.0F, 1.0F, 1.0F, var4, (Consumer)var6);
   }

    void renderSnowTile(SnowGrid var1, int var2, int var3, int var4, IsoGridSquare var5, int var6, Texture var7, int var8, int var9, float var10) {
      if (var6 == 0) {
    uint8_t var23 = var1.gridType[var2][var3][var4];
         this.renderSnowTileBase(var7, var8, var9, var10, var23 < this.m_snowFirstNonSquare);
      } else {
    int var11 = 0;
    bool var16 = var1.check(var2, var3);
    bool var12 = (var6 & 1) == 1 && (var16 || var1.check(var2, var3 - 1));
    bool var15 = (var6 & 2) == 2 && (var16 || var1.check(var2 + 1, var3));
    bool var13 = (var6 & 4) == 4 && (var16 || var1.check(var2, var3 + 1));
    bool var14 = (var6 & 8) == 8 && (var16 || var1.check(var2 - 1, var3));
         if (var12) {
            var11++;
         }

         if (var13) {
            var11++;
         }

         if (var15) {
            var11++;
         }

         if (var14) {
            var11++;
         }

    SnowGridTiles var17 = nullptr;
    SnowGridTiles var18 = nullptr;
    bool var19 = false;
         if (var11 != 0) {
            if (var11 == 1) {
               if (var12) {
                  var17 = this.snowGridTiles_Strip[0];
               } else if (var13) {
                  var17 = this.snowGridTiles_Strip[1];
               } else if (var15) {
                  var17 = this.snowGridTiles_Strip[3];
               } else if (var14) {
                  var17 = this.snowGridTiles_Strip[2];
               }
            } else if (var11 == 2) {
               if (var12 && var13) {
                  var17 = this.snowGridTiles_Strip[0];
                  var18 = this.snowGridTiles_Strip[1];
               } else if (var15 && var14) {
                  var17 = this.snowGridTiles_Strip[2];
                  var18 = this.snowGridTiles_Strip[3];
               } else if (var12) {
                  var17 = this.snowGridTiles_Edge[var14 ? 0 : 3];
               } else if (var13) {
                  var17 = this.snowGridTiles_Edge[var14 ? 2 : 1];
               } else if (var14) {
                  var17 = this.snowGridTiles_Edge[var12 ? 0 : 2];
               } else if (var15) {
                  var17 = this.snowGridTiles_Edge[var12 ? 3 : 1];
               }
            } else if (var11 == 3) {
               if (!var12) {
                  var17 = this.snowGridTiles_Cove[1];
               } else if (!var13) {
                  var17 = this.snowGridTiles_Cove[0];
               } else if (!var15) {
                  var17 = this.snowGridTiles_Cove[2];
               } else if (!var14) {
                  var17 = this.snowGridTiles_Cove[3];
               }

               var19 = true;
            } else if (var11 == 4) {
               var17 = this.snowGridTiles_Enclosed;
               var19 = true;
            }

            if (var17 != nullptr) {
    int var20 = (var5.getX() + var5.getY()) % var17.size();
               var7 = var17.get(var20);
               if (var7 != nullptr) {
                  this.renderSnowTileBase(var7, var8, var9, var10, var19);
               }

               if (var18 != nullptr) {
                  var7 = var18.get(var20);
                  if (var7 != nullptr) {
                     this.renderSnowTileBase(var7, var8, var9, var10, false);
                  }
               }
            }
         }
      }
   }

    static int getShoreInt(IsoGridSquare var0) {
    uint8_t var1 = 0;
      if (isSnowShore(var0, 0, -1)) {
         var1 |= 1;
      }

      if (isSnowShore(var0, 1, 0)) {
         var1 |= 2;
      }

      if (isSnowShore(var0, 0, 1)) {
         var1 |= 4;
      }

      if (isSnowShore(var0, -1, 0)) {
         var1 |= 8;
      }

    return var1;
   }

    static bool isSnowShore(IsoGridSquare var0, int var1, int var2) {
    IsoGridSquare var3 = IsoWorld.instance.getCell().getGridSquare(var0.getX() + var1, var0.getY() + var2, 0);
      return var3 != nullptr && !var3.getProperties().Is(IsoFlagType.water);
   }

    IsoBuilding getClosestBuildingExcept(IsoGameCharacter var1, IsoRoom var2) {
    IsoBuilding var3 = nullptr;
    float var4 = 1000000.0F;

      for (int var5 = 0; var5 < this.BuildingList.size(); var5++) {
    IsoBuilding var6 = this.BuildingList.get(var5);

         for (int var7 = 0; var7 < var6.Exits.size(); var7++) {
    float var8 = var1.DistTo(((IsoRoomExit)var6.Exits.get(var7)).x, ((IsoRoomExit)var6.Exits.get(var7)).y);
            if (var8 < var4 && (var2 == nullptr || var2.building != var6)) {
               var3 = var6;
               var4 = var8;
            }
         }
      }

    return var3;
   }

    int getDangerScore(int var1, int var2) {
      return var1 >= 0 && var2 >= 0 && var1 < this.width && var2 < this.height ? this.DangerScore.getValue(var1, var2) : 1000000;
   }

    void ObjectDeletionAddition() {
      for (int var1 = 0; var1 < this.removeList.size(); var1++) {
    IsoMovingObject var2 = this.removeList.get(var1);
         if (dynamic_cast<IsoZombie*>(var2) != nullptr) {
            VirtualZombieManager.instance.RemoveZombie((IsoZombie)var2);
         }

         if (!(dynamic_cast<IsoPlayer*>(var2) != nullptr) || ((IsoPlayer)var2).isDead()) {
            MovingObjectUpdateScheduler.instance.removeObject(var2);
            this.ObjectList.remove(var2);
            if (var2.getCurrentSquare() != nullptr) {
               var2.getCurrentSquare().getMovingObjects().remove(var2);
            }

            if (var2.getLastSquare() != nullptr) {
               var2.getLastSquare().getMovingObjects().remove(var2);
            }
         }
      }

      this.removeList.clear();

      for (int var3 = 0; var3 < this.addList.size(); var3++) {
    IsoMovingObject var5 = this.addList.get(var3);
         this.ObjectList.push_back(var5);
      }

      this.addList.clear();

      for (int var4 = 0; var4 < this.addVehicles.size(); var4++) {
    BaseVehicle var6 = this.addVehicles.get(var4);
         if (!this.ObjectList.contains(var6)) {
            this.ObjectList.push_back(var6);
         }

         if (!this.vehicles.contains(var6)) {
            this.vehicles.push_back(var6);
         }
      }

      this.addVehicles.clear();
   }

    void ProcessItems(Iterator<InventoryItem> var1) {
    int var2 = this.ProcessItems.size();

      for (int var3 = 0; var3 < var2; var3++) {
    InventoryItem var4 = this.ProcessItems.get(var3);
         var4.update();
         if (var4.finishupdate()) {
            this.ProcessItemsRemove.push_back(var4);
         }
      }

      var2 = this.ProcessWorldItems.size();

      for (int var6 = 0; var6 < var2; var6++) {
    IsoWorldInventoryObject var7 = this.ProcessWorldItems.get(var6);
         var7.update();
         if (var7.finishupdate()) {
            this.ProcessWorldItemsRemove.push_back(var7);
         }
      }
   }

    void ProcessIsoObject() {
      this.ProcessIsoObject.removeAll(this.ProcessIsoObjectRemove);
      this.ProcessIsoObjectRemove.clear();
    int var1 = this.ProcessIsoObject.size();

      for (int var2 = 0; var2 < var1; var2++) {
    IsoObject var3 = this.ProcessIsoObject.get(var2);
         if (var3 != nullptr) {
            var3.update();
            if (var1 > this.ProcessIsoObject.size()) {
               var2--;
               var1--;
            }
         }
      }
   }

    void ProcessObjects(Iterator<IsoMovingObject> var1) {
      MovingObjectUpdateScheduler.instance.update();

      for (int var2 = 0; var2 < this.ZombieList.size(); var2++) {
    IsoZombie var3 = this.ZombieList.get(var2);
         var3.updateVocalProperties();
      }
   }

    void ProcessRemoveItems(Iterator<InventoryItem> var1) {
      this.ProcessItems.removeAll(this.ProcessItemsRemove);
      this.ProcessWorldItems.removeAll(this.ProcessWorldItemsRemove);
      this.ProcessItemsRemove.clear();
      this.ProcessWorldItemsRemove.clear();
   }

    void ProcessStaticUpdaters() {
    int var1 = this.StaticUpdaterObjectList.size();

      for (int var2 = 0; var2 < var1; var2++) {
         try {
            this.StaticUpdaterObjectList.get(var2).update();
         } catch (Exception var4) {
            Logger.getLogger(GameWindow.class.getName()).log(Level.SEVERE, nullptr, var4);
         }

         if (var1 > this.StaticUpdaterObjectList.size()) {
            var2--;
            var1--;
         }
      }
   }

    void addToProcessIsoObject(IsoObject var1) {
      if (var1 != nullptr) {
         this.ProcessIsoObjectRemove.remove(var1);
         if (!this.ProcessIsoObject.contains(var1)) {
            this.ProcessIsoObject.push_back(var1);
         }
      }
   }

    void addToProcessIsoObjectRemove(IsoObject var1) {
      if (var1 != nullptr) {
         if (this.ProcessIsoObject.contains(var1)) {
            if (!this.ProcessIsoObjectRemove.contains(var1)) {
               this.ProcessIsoObjectRemove.push_back(var1);
            }
         }
      }
   }

    void addToStaticUpdaterObjectList(IsoObject var1) {
      if (var1 != nullptr) {
         if (!this.StaticUpdaterObjectList.contains(var1)) {
            this.StaticUpdaterObjectList.push_back(var1);
         }
      }
   }

    void addToProcessItems(InventoryItem var1) {
      if (var1 != nullptr) {
         this.ProcessItemsRemove.remove(var1);
         if (!this.ProcessItems.contains(var1)) {
            this.ProcessItems.push_back(var1);
         }
      }
   }

    void addToProcessItems(std::vector<InventoryItem> var1) {
      if (var1 != nullptr) {
         for (int var2 = 0; var2 < var1.size(); var2++) {
    InventoryItem var3 = (InventoryItem)var1.get(var2);
            if (var3 != nullptr) {
               this.ProcessItemsRemove.remove(var3);
               if (!this.ProcessItems.contains(var3)) {
                  this.ProcessItems.push_back(var3);
               }
            }
         }
      }
   }

    void addToProcessItemsRemove(InventoryItem var1) {
      if (var1 != nullptr) {
         if (!this.ProcessItemsRemove.contains(var1)) {
            this.ProcessItemsRemove.push_back(var1);
         }
      }
   }

    void addToProcessItemsRemove(std::vector<InventoryItem> var1) {
      if (var1 != nullptr) {
         for (int var2 = 0; var2 < var1.size(); var2++) {
    InventoryItem var3 = (InventoryItem)var1.get(var2);
            if (var3 != nullptr && !this.ProcessItemsRemove.contains(var3)) {
               this.ProcessItemsRemove.push_back(var3);
            }
         }
      }
   }

    void addToProcessWorldItems(IsoWorldInventoryObject var1) {
      if (var1 != nullptr) {
         this.ProcessWorldItemsRemove.remove(var1);
         if (!this.ProcessWorldItems.contains(var1)) {
            this.ProcessWorldItems.push_back(var1);
         }
      }
   }

    void addToProcessWorldItemsRemove(IsoWorldInventoryObject var1) {
      if (var1 != nullptr) {
         if (!this.ProcessWorldItemsRemove.contains(var1)) {
            this.ProcessWorldItemsRemove.push_back(var1);
         }
      }
   }

    IsoSurvivor getNetworkPlayer(int var1) {
    int var2 = this.RemoteSurvivorList.size();

      for (int var3 = 0; var3 < var2; var3++) {
         if (this.RemoteSurvivorList.get(var3).getRemoteID() == var1) {
            return (IsoSurvivor)this.RemoteSurvivorList.get(var3);
         }
      }

    return nullptr;
   }

    IsoGridSquare ConnectNewSquare(IsoGridSquare var1, bool var2, bool var3) {
    int var4 = var1.getX();
    int var5 = var1.getY();
    int var6 = var1.getZ();
      this.setCacheGridSquare(var4, var5, var6, var1);
      this.DoGridNav(var1, IsoGridSquare.cellGetSquare);
    return var1;
   }

    void DoGridNav(IsoGridSquare var1, GetSquare var2) {
    int var3 = var1.getX();
    int var4 = var1.getY();
    int var5 = var1.getZ();
      var1.nav[IsoDirections.N.index()] = var2.getGridSquare(var3, var4 - 1, var5);
      var1.nav[IsoDirections.NW.index()] = var2.getGridSquare(var3 - 1, var4 - 1, var5);
      var1.nav[IsoDirections.W.index()] = var2.getGridSquare(var3 - 1, var4, var5);
      var1.nav[IsoDirections.SW.index()] = var2.getGridSquare(var3 - 1, var4 + 1, var5);
      var1.nav[IsoDirections.S.index()] = var2.getGridSquare(var3, var4 + 1, var5);
      var1.nav[IsoDirections.SE.index()] = var2.getGridSquare(var3 + 1, var4 + 1, var5);
      var1.nav[IsoDirections.E.index()] = var2.getGridSquare(var3 + 1, var4, var5);
      var1.nav[IsoDirections.NE.index()] = var2.getGridSquare(var3 + 1, var4 - 1, var5);
      if (var1.nav[IsoDirections.N.index()] != nullptr) {
         var1.nav[IsoDirections.N.index()].nav[IsoDirections.S.index()] = var1;
      }

      if (var1.nav[IsoDirections.NW.index()] != nullptr) {
         var1.nav[IsoDirections.NW.index()].nav[IsoDirections.SE.index()] = var1;
      }

      if (var1.nav[IsoDirections.W.index()] != nullptr) {
         var1.nav[IsoDirections.W.index()].nav[IsoDirections.E.index()] = var1;
      }

      if (var1.nav[IsoDirections.SW.index()] != nullptr) {
         var1.nav[IsoDirections.SW.index()].nav[IsoDirections.NE.index()] = var1;
      }

      if (var1.nav[IsoDirections.S.index()] != nullptr) {
         var1.nav[IsoDirections.S.index()].nav[IsoDirections.N.index()] = var1;
      }

      if (var1.nav[IsoDirections.SE.index()] != nullptr) {
         var1.nav[IsoDirections.SE.index()].nav[IsoDirections.NW.index()] = var1;
      }

      if (var1.nav[IsoDirections.E.index()] != nullptr) {
         var1.nav[IsoDirections.E.index()].nav[IsoDirections.W.index()] = var1;
      }

      if (var1.nav[IsoDirections.NE.index()] != nullptr) {
         var1.nav[IsoDirections.NE.index()].nav[IsoDirections.SW.index()] = var1;
      }
   }

    IsoGridSquare ConnectNewSquare(IsoGridSquare var1, bool var2) {
      for (int var3 = 0; var3 < IsoPlayer.numPlayers; var3++) {
         if (!this.ChunkMap[var3].ignore) {
            this.ChunkMap[var3].setGridSquare(var1, var1.getX(), var1.getY(), var1.getZ());
         }
      }

      return this.ConnectNewSquare(var1, var2, false);
   }

    void PlaceLot(const std::string& var1, int var2, int var3, int var4, bool var5) {
   }

    void PlaceLot(IsoLot var1, int var2, int var3, int var4, bool var5) {
    int var6 = Math.min(var4 + var1.info.levels, var4 + 8);

      for (int var7 = var2; var7 < var2 + var1.info.width; var7++) {
         for (int var8 = var3; var8 < var3 + var1.info.height; var8++) {
            for (int var9 = var4; var9 < var6; var9++) {
    int var10 = var7 - var2;
    int var11 = var8 - var3;
    int var12 = var9 - var4;
               if (var7 < this.width && var8 < this.height && var7 >= 0 && var8 >= 0 && var9 >= 0) {
    int var13 = var10 + var11 * 10 + var12 * 100;
    int var14 = var1.m_offsetInData[var13];
                  if (var14 != -1) {
    int var15 = var1.m_data.getQuick(var14);
                     if (var15 > 0) {
    bool var16 = false;

                        for (int var17 = 0; var17 < var15; var17++) {
    std::string var18 = (std::string)var1.info.tilesUsed.get(var1.m_data.getQuick(var14 + 1 + var17));
    IsoSprite var19 = (IsoSprite)IsoSpriteManager.instance.NamedMap.get(var18);
                           if (var19 == nullptr) {
                              Logger.getLogger(GameWindow.class.getName()).log(Level.SEVERE, "Missing tile definition: " + var18);
                           } else {
    IsoGridSquare var20 = this.getGridSquare(var7, var8, var9);
                              if (var20 == nullptr) {
                                 if (IsoGridSquare.loadGridSquareCache != nullptr) {
                                    var20 = IsoGridSquare.getNew(IsoGridSquare.loadGridSquareCache, this, nullptr, var7, var8, var9);
                                 } else {
                                    var20 = IsoGridSquare.getNew(this, nullptr, var7, var8, var9);
                                 }

                                 this.ChunkMap[IsoPlayer.getPlayerIndex()].setGridSquare(var20, var7, var8, var9);
                              } else {
                                 if (var5
                                    && var17 == 0
                                    && var19.getProperties().Is(IsoFlagType.solidfloor)
                                    && (!var19.Properties.Is(IsoFlagType.hidewalls) || var15 > 1)) {
                                    var16 = true;
                                 }

                                 if (var16 && var17 == 0) {
                                    var20.getObjects().clear();
                                 }
                              }

                              CellLoader.DoTileObjectCreation(var19, var19.getType(), var20, this, var7, var8, var9, var18);
                           }
                        }
                     }
                  }
               }
            }
         }
      }
   }

    void PlaceLot(IsoLot var1, int var2, int var3, int var4, IsoChunk var5, int var6, int var7) {
      var6 *= 10;
      var7 *= 10;
    IsoMetaGrid var8 = IsoWorld.instance.getMetaGrid();
    int var9 = Math.min(var4 + var1.info.levels, var4 + 8);

      try {
         for (int var10 = var6 + var2; var10 < var6 + var2 + 10; var10++) {
            for (int var29 = var7 + var3; var29 < var7 + var3 + 10; var29++) {
               for (int var30 = var4; var30 < var9; var30++) {
    int var31 = var10 - var6 - var2;
    int var14 = var29 - var7 - var3;
    int var15 = var30 - var4;
                  if (var10 < var6 + 10 && var29 < var7 + 10 && var10 >= var6 && var29 >= var7 && var30 >= 0) {
    int var16 = var31 + var14 * 10 + var15 * 100;
    int var17 = var1.m_offsetInData[var16];
                     if (var17 != -1) {
    int var18 = var1.m_data.getQuick(var17);
                        if (var18 > 0) {
    IsoGridSquare var19 = var5.getGridSquare(var10 - var6, var29 - var7, var30);
                           if (var19 == nullptr) {
                              if (IsoGridSquare.loadGridSquareCache != nullptr) {
                                 var19 = IsoGridSquare.getNew(IsoGridSquare.loadGridSquareCache, this, nullptr, var10, var29, var30);
                              } else {
                                 var19 = IsoGridSquare.getNew(this, nullptr, var10, var29, var30);
                              }

                              var19.setX(var10);
                              var19.setY(var29);
                              var19.setZ(var30);
                              var5.setSquare(var10 - var6, var29 - var7, var30, var19);
                           }

                           for (int var20 = -1; var20 <= 1; var20++) {
                              for (int var21 = -1; var21 <= 1; var21++) {
                                 if ((var20 != 0 || var21 != 0)
                                    && var20 + var10 - var6 >= 0
                                    && var20 + var10 - var6 < 10
                                    && var21 + var29 - var7 >= 0
                                    && var21 + var29 - var7 < 10) {
    IsoGridSquare var22 = var5.getGridSquare(var10 + var20 - var6, var29 + var21 - var7, var30);
                                    if (var22 == nullptr) {
                                       var22 = IsoGridSquare.getNew(this, nullptr, var10 + var20, var29 + var21, var30);
                                       var5.setSquare(var10 + var20 - var6, var29 + var21 - var7, var30, var22);
                                    }
                                 }
                              }
                           }

    RoomDef var32 = var8.getRoomAt(var10, var29, var30);
    int var34 = var32 != nullptr ? var32.ID : -1;
                           var19.setRoomID(var34);
                           var19.ResetIsoWorldRegion();
                           var32 = var8.getEmptyOutsideAt(var10, var29, var30);
                           if (var32 != nullptr) {
    IsoRoom var36 = var5.getRoom(var32.ID);
                              var19.roofHideBuilding = var36 == nullptr ? nullptr : var36.building;
                           }

    bool var37 = true;

                           for (int var23 = 0; var23 < var18; var23++) {
    std::string var24 = (std::string)var1.info.tilesUsed.get(var1.m_data.get(var17 + 1 + var23));
                              if (!var1.info.bFixed2x) {
                                 var24 = IsoChunk.Fix2x(var24);
                              }

    IsoSprite var25 = (IsoSprite)IsoSpriteManager.instance.NamedMap.get(var24);
                              if (var25 == nullptr) {
                                 Logger.getLogger(GameWindow.class.getName()).log(Level.SEVERE, "Missing tile definition: " + var24);
                              } else {
                                 if (var23 == 0
                                    && var25.getProperties().Is(IsoFlagType.solidfloor)
                                    && (!var25.Properties.Is(IsoFlagType.hidewalls) || var18 > 1)) {
                                    var37 = true;
                                 }

                                 if (var37 && var23 == 0) {
                                    var19.getObjects().clear();
                                 }

                                 CellLoader.DoTileObjectCreation(var25, var25.getType(), var19, this, var10, var29, var30, var24);
                              }
                           }

                           var19.FixStackableObjects();
                        }
                     }
                  }
               }
            }
         }
      } catch (Exception var26) {
         DebugLog.log("Failed to load chunk, blocking out area");
         ExceptionLogger.logException(var26);

         for (int var11 = var6 + var2; var11 < var6 + var2 + 10; var11++) {
            for (int var12 = var7 + var3; var12 < var7 + var3 + 10; var12++) {
               for (int var13 = var4; var13 < var9; var13++) {
                  var5.setSquare(var11 - var6 - var2, var12 - var7 - var3, var13 - var4, nullptr);
                  this.setCacheGridSquare(var11, var12, var13, nullptr);
               }
            }
         }
      }
   }

    void setDrag(KahluaTable var1, int var2) {
      if (var2 >= 0 && var2 < 4) {
         if (this.drag[var2] != nullptr && this.drag[var2] != var1) {
    void* var3 = this.drag[var2].rawget("deactivate");
            if (dynamic_cast<JavaFunction*>(var3) != nullptr || dynamic_cast<LuaClosure*>(var3) != nullptr) {
               LuaManager.caller.pcallvoid(LuaManager.thread, var3, this.drag[var2]);
            }
         }

         this.drag[var2] = var1;
      }
   }

    KahluaTable getDrag(int var1) {
      return var1 >= 0 && var1 < 4 ? this.drag[var1] : nullptr;
   }

    bool DoBuilding(int var1, bool var2) {
    bool var3;
      try {
         s_performance.isoCellDoBuilding.start();
         var3 = this.doBuildingInternal(var1, var2);
      } finally {
         s_performance.isoCellDoBuilding.end();
      }

    return var3;
   }

    bool doBuildingInternal(int var1, bool var2) {
      if (UIManager.getPickedTile() != nullptr && this.drag[var1] != nullptr && JoypadManager.instance.getFromPlayer(var1) == nullptr) {
         if (!IsoWorld.instance.isValidSquare((int)UIManager.getPickedTile().x, (int)UIManager.getPickedTile().y, (int)IsoCamera.CamCharacter.getZ())) {
    return false;
         }

    IsoGridSquare var3 = this.getGridSquare((int)UIManager.getPickedTile().x, (int)UIManager.getPickedTile().y, (int)IsoCamera.CamCharacter.getZ());
         if (!var2) {
            if (var3 == nullptr) {
               var3 = this.createNewGridSquare((int)UIManager.getPickedTile().x, (int)UIManager.getPickedTile().y, (int)IsoCamera.CamCharacter.getZ(), true);
               if (var3 == nullptr) {
    return false;
               }
            }

            var3.EnsureSurroundNotNull();
         }

         LuaEventManager.triggerEvent(
            "OnDoTileBuilding2",
            this.drag[var1],
            var2,
            (int)UIManager.getPickedTile().x,
            (int)UIManager.getPickedTile().y,
            (int)IsoCamera.CamCharacter.getZ(),
            var3
         );
      }

      if (this.drag[var1] != nullptr && JoypadManager.instance.getFromPlayer(var1) != nullptr) {
         LuaEventManager.triggerEvent(
            "OnDoTileBuilding3",
            this.drag[var1],
            var2,
            (int)IsoPlayer.players[var1].getX(),
            (int)IsoPlayer.players[var1].getY(),
            (int)IsoCamera.CamCharacter.getZ()
         );
      }

      if (var2) {
         IndieGL.glBlendFunc(770, 771);
      }

    return false;
   }

    float DistanceFromSupport(int var1, int var2, int var3) {
      return 0.0F;
   }

   public std::vector<IsoBuilding> getBuildingList() {
      return this.BuildingList;
   }

   public std::vector<IsoWindow> getWindowList() {
      return this.WindowList;
   }

    void addToWindowList(IsoWindow var1) {
      if (!GameServer.bServer) {
         if (var1 != nullptr) {
            if (!this.WindowList.contains(var1)) {
               this.WindowList.push_back(var1);
            }
         }
      }
   }

    void removeFromWindowList(IsoWindow var1) {
      this.WindowList.remove(var1);
   }

   public std::vector<IsoMovingObject> getObjectList() {
      return this.ObjectList;
   }

    IsoRoom getRoom(int var1) {
      return this.ChunkMap[IsoPlayer.getPlayerIndex()].getRoom(var1);
   }

   public std::vector<IsoPushableObject> getPushableObjectList() {
      return this.PushableObjectList;
   }

   public std::unordered_map<int, BuildingScore> getBuildingScores() {
      return this.BuildingScores;
   }

   public std::vector<IsoRoom> getRoomList() {
      return this.RoomList;
   }

   public std::vector<IsoObject> getStaticUpdaterObjectList() {
      return this.StaticUpdaterObjectList;
   }

   public std::vector<IsoZombie> getZombieList() {
      return this.ZombieList;
   }

   public std::vector<IsoGameCharacter> getRemoteSurvivorList() {
      return this.RemoteSurvivorList;
   }

   public std::vector<IsoMovingObject> getRemoveList() {
      return this.removeList;
   }

   public std::vector<IsoMovingObject> getAddList() {
      return this.addList;
   }

    void addMovingObject(IsoMovingObject var1) {
      this.addList.push_back(var1);
   }

   public std::vector<InventoryItem> getProcessItems() {
      return this.ProcessItems;
   }

   public std::vector<IsoWorldInventoryObject> getProcessWorldItems() {
      return this.ProcessWorldItems;
   }

   public std::vector<IsoObject> getProcessIsoObjects() {
      return this.ProcessIsoObject;
   }

   public std::vector<InventoryItem> getProcessItemsRemove() {
      return this.ProcessItemsRemove;
   }

   public std::vector<BaseVehicle> getVehicles() {
      return this.vehicles;
   }

    int getHeight() {
      return this.height;
   }

    void setHeight(int var1) {
      this.height = var1;
   }

    int getWidth() {
      return this.width;
   }

    void setWidth(int var1) {
      this.width = var1;
   }

    int getWorldX() {
      return this.worldX;
   }

    void setWorldX(int var1) {
      this.worldX = var1;
   }

    int getWorldY() {
      return this.worldY;
   }

    void setWorldY(int var1) {
      this.worldY = var1;
   }

    bool isSafeToAdd() {
      return this.safeToAdd;
   }

    void setSafeToAdd(bool var1) {
      this.safeToAdd = var1;
   }

   public std::stack<IsoLightSource> getLamppostPositions() {
      return this.LamppostPositions;
   }

    IsoLightSource getLightSourceAt(int var1, int var2, int var3) {
      for (int var4 = 0; var4 < this.LamppostPositions.size(); var4++) {
    IsoLightSource var5 = this.LamppostPositions.get(var4);
         if (var5.getX() == var1 && var5.getY() == var2 && var5.getZ() == var3) {
    return var5;
         }
      }

    return nullptr;
   }

    void addLamppost(IsoLightSource var1) {
      if (var1 != nullptr && !this.LamppostPositions.contains(var1)) {
         this.LamppostPositions.push_back(var1);
         IsoGridSquare.RecalcLightTime = -1;
         GameTime.instance.lightSourceUpdate = 100.0F;
      }
   }

    IsoLightSource addLamppost(int var1, int var2, int var3, float var4, float var5, float var6, int var7) {
    IsoLightSource var8 = std::make_shared<IsoLightSource>(var1, var2, var3, var4, var5, var6, var7);
      this.LamppostPositions.push_back(var8);
      IsoGridSquare.RecalcLightTime = -1;
      GameTime.instance.lightSourceUpdate = 100.0F;
    return var8;
   }

    void removeLamppost(int var1, int var2, int var3) {
      for (int var4 = 0; var4 < this.LamppostPositions.size(); var4++) {
    IsoLightSource var5 = this.LamppostPositions.get(var4);
         if (var5.getX() == var1 && var5.getY() == var2 && var5.getZ() == var3) {
            var5.clearInfluence();
            this.LamppostPositions.remove(var5);
            IsoGridSquare.RecalcLightTime = -1;
            GameTime.instance.lightSourceUpdate = 100.0F;
            return;
         }
      }
   }

    void removeLamppost(IsoLightSource var1) {
      var1.life = 0;
      IsoGridSquare.RecalcLightTime = -1;
      GameTime.instance.lightSourceUpdate = 100.0F;
   }

    int getCurrentLightX() {
      return this.currentLX;
   }

    void setCurrentLightX(int var1) {
      this.currentLX = var1;
   }

    int getCurrentLightY() {
      return this.currentLY;
   }

    void setCurrentLightY(int var1) {
      this.currentLY = var1;
   }

    int getCurrentLightZ() {
      return this.currentLZ;
   }

    void setCurrentLightZ(int var1) {
      this.currentLZ = var1;
   }

    int getMinX() {
      return this.minX;
   }

    void setMinX(int var1) {
      this.minX = var1;
   }

    int getMaxX() {
      return this.maxX;
   }

    void setMaxX(int var1) {
      this.maxX = var1;
   }

    int getMinY() {
      return this.minY;
   }

    void setMinY(int var1) {
      this.minY = var1;
   }

    int getMaxY() {
      return this.maxY;
   }

    void setMaxY(int var1) {
      this.maxY = var1;
   }

    int getMinZ() {
      return this.minZ;
   }

    void setMinZ(int var1) {
      this.minZ = var1;
   }

    int getMaxZ() {
      return this.maxZ;
   }

    void setMaxZ(int var1) {
      this.maxZ = var1;
   }

    OnceEvery getDangerUpdate() {
      return this.dangerUpdate;
   }

    void setDangerUpdate(OnceEvery var1) {
      this.dangerUpdate = var1;
   }

    Thread getLightInfoUpdate() {
      return this.LightInfoUpdate;
   }

    void setLightInfoUpdate(Thread var1) {
      this.LightInfoUpdate = var1;
   }

   public std::vector<IsoSurvivor> getSurvivorList() {
      return this.SurvivorList;
   }

    static int getRComponent(int var0) {
      return var0 & 0xFF;
   }

    static int getGComponent(int var0) {
      return (var0 & 0xFF00) >> 8;
   }

    static int getBComponent(int var0) {
      return (var0 & 0xFF0000) >> 16;
   }

    static int toIntColor(float var0, float var1, float var2, float var3) {
      return (int)(var0 * 255.0F) << 0 | (int)(var1 * 255.0F) << 8 | (int)(var2 * 255.0F) << 16 | (int)(var3 * 255.0F) << 24;
   }

    IsoGridSquare getRandomOutdoorTile() {
    IsoGridSquare var1 = nullptr;

      do {
         var1 = this.getGridSquare(
            this.ChunkMap[IsoPlayer.getPlayerIndex()].getWorldXMin() * 10 + Rand.Next(this.width),
            this.ChunkMap[IsoPlayer.getPlayerIndex()].getWorldYMin() * 10 + Rand.Next(this.height),
            0
         );
         if (var1 != nullptr) {
            var1.setCachedIsFree(false);
         }
      } while (var1 == nullptr || !var1.isFree(false) || var1.getRoom() != nullptr);

    return var1;
   }

    static void InsertAt(int var0, BuildingScore var1, BuildingScore[] var2) {
      for (int var3 = var2.length - 1; var3 > var0; var3--) {
         var2[var3] = var2[var3 - 1];
      }

      var2[var0] = var1;
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    static void Place(BuildingScore var0, BuildingScore[] var1, BuildingSearchCriteria var2) {
      for (int var3 = 0; var3 < var1.length; var3++) {
         if (var1[var3] != nullptr) {
    bool var4 = false;
            if (var1[var3] == nullptr) {
               var4 = true;
            } else {
               switch (1.$SwitchMap$zombie$iso$IsoCell$BuildingSearchCriteria[var2.ordinal()]) {
                  case 1:
                     if (var1[var3].food + var1[var3].defense + var1[var3].size + var1[var3].weapons < var0.food + var0.defense + var0.size + var0.weapons) {
                        var4 = true;
                     }
                     break;
                  case 2:
                     if (var1[var3].food < var0.food) {
                        var4 = true;
                     }
                     break;
                  case 3:
                     if (var1[var3].wood < var0.wood) {
                        var4 = true;
                     }
                     break;
                  case 4:
                     if (var1[var3].weapons < var0.weapons) {
                        var4 = true;
                     }
                     break;
                  case 5:
                     if (var1[var3].defense < var0.defense) {
                        var4 = true;
                     }
               }
            }

            if (var4) {
               InsertAt(var3, var0, var1);
               return;
            }
         }
      }
   }

   public std::stack<BuildingScore> getBestBuildings(BuildingSearchCriteria var1, int var2) {
      BuildingScore[] var3 = new BuildingScore[var2];
      if (this.BuildingScores.empty()) {
    int var4 = this.BuildingList.size();

         for (int var5 = 0; var5 < var4; var5++) {
            this.BuildingList.get(var5).update();
         }
      }

    int var7 = this.BuildingScores.size();

      for (int var8 = 0; var8 < var7; var8++) {
    BuildingScore var6 = this.BuildingScores.get(var8);
         Place(var6, var3, var1);
      }

      buildingscores.clear();
      buildingscores.addAll(Arrays.asList(var3));
    return buildingscores;
   }

    bool blocked(Mover var1, int var2, int var3, int var4, int var5, int var6, int var7) {
    IsoGridSquare var8 = this.getGridSquare(var5, var6, var7);
      if (var8 == nullptr) {
    return true;
      } else {
         if (dynamic_cast<IsoMovingObject*>(var1) != nullptr) {
            if (var8.testPathFindAdjacent((IsoMovingObject)var1, var2 - var5, var3 - var6, var4 - var7)) {
    return true;
            }
         } else if (var8.testPathFindAdjacent(nullptr, var2 - var5, var3 - var6, var4 - var7)) {
    return true;
         }

    return false;
      }
   }

    void Dispose() {
      for (int var1 = 0; var1 < this.ObjectList.size(); var1++) {
    IsoMovingObject var2 = this.ObjectList.get(var1);
         if (dynamic_cast<IsoZombie*>(var2) != nullptr) {
            var2.setCurrent(nullptr);
            var2.setLast(nullptr);
            VirtualZombieManager.instance.addToReusable((IsoZombie)var2);
         }
      }

      for (int var3 = 0; var3 < this.RoomList.size(); var3++) {
         this.RoomList.get(var3).TileList.clear();
         this.RoomList.get(var3).Exits.clear();
         this.RoomList.get(var3).WaterSources.clear();
         this.RoomList.get(var3).lightSwitches.clear();
         this.RoomList.get(var3).Beds.clear();
      }

      for (int var4 = 0; var4 < this.BuildingList.size(); var4++) {
         this.BuildingList.get(var4).Exits.clear();
         this.BuildingList.get(var4).Rooms.clear();
         this.BuildingList.get(var4).container.clear();
         this.BuildingList.get(var4).Windows.clear();
      }

      LuaEventManager.clear();
      LuaHookManager.clear();
      this.LamppostPositions.clear();
      this.ProcessItems.clear();
      this.ProcessItemsRemove.clear();
      this.ProcessWorldItems.clear();
      this.ProcessWorldItemsRemove.clear();
      this.BuildingScores.clear();
      this.BuildingList.clear();
      this.WindowList.clear();
      this.PushableObjectList.clear();
      this.RoomList.clear();
      this.SurvivorList.clear();
      this.ObjectList.clear();
      this.ZombieList.clear();

      for (int var5 = 0; var5 < this.ChunkMap.length; var5++) {
         this.ChunkMap[var5].Dispose();
         this.ChunkMap[var5] = nullptr;
      }

      for (int var6 = 0; var6 < this.gridSquares.length; var6++) {
         if (this.gridSquares[var6] != nullptr) {
            Arrays.fill(this.gridSquares[var6], nullptr);
            this.gridSquares[var6] = nullptr;
         }
      }
   }

    IsoGridSquare getGridSquare(double var1, double var3, double var5) {
      return GameServer.bServer ? ServerMap.instance.getGridSquare((int)var1, (int)var3, (int)var5) : this.getGridSquare((int)var1, (int)var3, (int)var5);
   }

    IsoGridSquare getOrCreateGridSquare(double var1, double var3, double var5) {
      if (GameServer.bServer) {
    IsoGridSquare var8 = ServerMap.instance.getGridSquare((int)var1, (int)var3, (int)var5);
         if (var8 == nullptr) {
            var8 = IsoGridSquare.getNew(this, nullptr, (int)var1, (int)var3, (int)var5);
            ServerMap.instance.setGridSquare((int)var1, (int)var3, (int)var5, var8);
            this.ConnectNewSquare(var8, true);
         }

    return var8;
      } else {
    IsoGridSquare var7 = this.getGridSquare((int)var1, (int)var3, (int)var5);
         if (var7 == nullptr) {
            var7 = IsoGridSquare.getNew(this, nullptr, (int)var1, (int)var3, (int)var5);
            this.ConnectNewSquare(var7, true);
         }

    return var7;
      }
   }

    void setCacheGridSquare(int var1, int var2, int var3, IsoGridSquare var4) {
    assert var4 = = nullptr || var1 == var4.getX() && var2 == var4.getY() && var3 == var4.getZ();

      if (!GameServer.bServer) {
         assert this.getChunkForGridSquare(var1, var2, var3) != nullptr;

    int var5 = IsoChunkMap.ChunkWidthInTiles;

         for (int var6 = 0; var6 < IsoPlayer.numPlayers; var6++) {
            if (!this.ChunkMap[var6].ignore) {
               this.ChunkMap[var6].YMinTiles = -1;
               this.ChunkMap[var6].XMinTiles = -1;
               this.ChunkMap[var6].YMaxTiles = -1;
               this.ChunkMap[var6].XMaxTiles = -1;
    int var7 = var1 - this.ChunkMap[var6].getWorldXMinTiles();
    int var8 = var2 - this.ChunkMap[var6].getWorldYMinTiles();
               if (var3 < 8 && var3 >= 0 && var7 >= 0 && var7 < var5 && var8 >= 0 && var8 < var5) {
                  this.gridSquares[var6][var7 + var8 * var5 + var3 * var5 * var5] = var4;
               }
            }
         }
      }
   }

    void setCacheChunk(IsoChunk var1) {
      if (!GameServer.bServer) {
         for (int var2 = 0; var2 < IsoPlayer.numPlayers; var2++) {
            this.setCacheChunk(var1, var2);
         }
      }
   }

    void setCacheChunk(IsoChunk var1, int var2) {
      if (!GameServer.bServer) {
    int var3 = IsoChunkMap.ChunkWidthInTiles;
    IsoChunkMap var4 = this.ChunkMap[var2];
         if (!var4.ignore) {
    int var5 = var1.wx - var4.getWorldXMin();
    int var6 = var1.wy - var4.getWorldYMin();
            if (var5 >= 0 && var5 < IsoChunkMap.ChunkGridWidth && var6 >= 0 && var6 < IsoChunkMap.ChunkGridWidth) {
               IsoGridSquare[] var7 = this.gridSquares[var2];

               for (int var8 = 0; var8 < 8; var8++) {
                  for (int var9 = 0; var9 < 10; var9++) {
                     for (int var10 = 0; var10 < 10; var10++) {
    IsoGridSquare var11 = var1.squares[var8][var10 + var9 * 10];
    int var12 = var5 * 10 + var10;
    int var13 = var6 * 10 + var9;
                        var7[var12 + var13 * var3 + var8 * var3 * var3] = var11;
                     }
                  }
               }
            }
         }
      }
   }

    void clearCacheGridSquare(int var1) {
      if (!GameServer.bServer) {
    int var2 = IsoChunkMap.ChunkWidthInTiles;
         this.gridSquares[var1] = new IsoGridSquare[var2 * var2 * 8];
      }
   }

    void setCacheGridSquareLocal(int var1, int var2, int var3, IsoGridSquare var4, int var5) {
      if (!GameServer.bServer) {
    int var6 = IsoChunkMap.ChunkWidthInTiles;
         if (var3 < 8 && var3 >= 0 && var1 >= 0 && var1 < var6 && var2 >= 0 && var2 < var6) {
            this.gridSquares[var5][var1 + var2 * var6 + var3 * var6 * var6] = var4;
         }
      }
   }

    IsoGridSquare getGridSquare(double var1, double var2, double var3) {
      return this.getGridSquare(var1.intValue(), var2.intValue(), var3.intValue());
   }

    IsoGridSquare getGridSquare(int var1, int var2, int var3) {
      if (GameServer.bServer) {
         return ServerMap.instance.getGridSquare(var1, var2, var3);
      } else {
    int var4 = IsoChunkMap.ChunkWidthInTiles;

         for (int var5 = 0; var5 < IsoPlayer.numPlayers; var5++) {
            if (!this.ChunkMap[var5].ignore) {
               if (var3 == 0) {
    bool var6 = false;
               }

    int var9 = var1 - this.ChunkMap[var5].getWorldXMinTiles();
    int var7 = var2 - this.ChunkMap[var5].getWorldYMinTiles();
               if (var3 < 8 && var3 >= 0 && var9 >= 0 && var9 < var4 && var7 >= 0 && var7 < var4) {
    IsoGridSquare var8 = this.gridSquares[var5][var9 + var7 * var4 + var3 * var4 * var4];
                  if (var8 != nullptr) {
    return var8;
                  }
               }
            }
         }

    return nullptr;
      }
   }

    void EnsureSurroundNotNull(int var1, int var2, int var3) {
      for (int var4 = -1; var4 <= 1; var4++) {
         for (int var5 = -1; var5 <= 1; var5++) {
            this.createNewGridSquare(var1 + var4, var2 + var5, var3, false);
         }
      }
   }

    void DeleteAllMovingObjects() {
      this.ObjectList.clear();
   }

    int getMaxFloors() {
    return 8;
   }

    KahluaTable getLuaObjectList() {
    KahluaTable var1 = LuaManager.platform.newTable();
      LuaManager.env.rawset("Objects", var1);

      for (int var2 = 0; var2 < this.ObjectList.size(); var2++) {
         var1.rawset(var2 + 1, this.ObjectList.get(var2));
      }

    return var1;
   }

    int getHeightInTiles() {
      return this.ChunkMap[IsoPlayer.getPlayerIndex()].getWidthInTiles();
   }

    int getWidthInTiles() {
      return this.ChunkMap[IsoPlayer.getPlayerIndex()].getWidthInTiles();
   }

    bool isNull(int var1, int var2, int var3) {
    IsoGridSquare var4 = this.getGridSquare(var1, var2, var3);
    return var4 = = nullptr || !var4.isFree(false);
   }

    void Remove(IsoMovingObject var1) {
      if (!(dynamic_cast<IsoPlayer*>(var1) != nullptr) || ((IsoPlayer)var1).isDead()) {
         this.removeList.push_back(var1);
      }
   }

    bool isBlocked(IsoGridSquare var1, IsoGridSquare var2) {
      return var1.room != var2.room;
   }

    int CalculateColor(IsoGridSquare var1, IsoGridSquare var2, IsoGridSquare var3, IsoGridSquare var4, int var5, int var6) {
    float var7 = 0.0F;
    float var8 = 0.0F;
    float var9 = 0.0F;
    float var10 = 1.0F;
      if (var4 == nullptr) {
    return 0;
      } else {
    float var11 = 0.0F;
    bool var12 = true;
         if (var1 != nullptr && var4.room == var1.room && var1.getChunk() != nullptr) {
            var11++;
    ColorInfo var13 = var1.lighting[var6].lightInfo();
            var7 += var13.r;
            var8 += var13.g;
            var9 += var13.b;
         }

         if (var2 != nullptr && var4.room == var2.room && var2.getChunk() != nullptr) {
            var11++;
    ColorInfo var14 = var2.lighting[var6].lightInfo();
            var7 += var14.r;
            var8 += var14.g;
            var9 += var14.b;
         }

         if (var3 != nullptr && var4.room == var3.room && var3.getChunk() != nullptr) {
            var11++;
    ColorInfo var15 = var3.lighting[var6].lightInfo();
            var7 += var15.r;
            var8 += var15.g;
            var9 += var15.b;
         }

         if (var4 != nullptr) {
            var11++;
    ColorInfo var16 = var4.lighting[var6].lightInfo();
            var7 += var16.r;
            var8 += var16.g;
            var9 += var16.b;
         }

         if (var11 != 0.0F) {
            var7 /= var11;
            var8 /= var11;
            var9 /= var11;
         }

         if (var7 > 1.0F) {
            var7 = 1.0F;
         }

         if (var8 > 1.0F) {
            var8 = 1.0F;
         }

         if (var9 > 1.0F) {
            var9 = 1.0F;
         }

         if (var7 < 0.0F) {
            var7 = 0.0F;
         }

         if (var8 < 0.0F) {
            var8 = 0.0F;
         }

         if (var9 < 0.0F) {
            var9 = 0.0F;
         }

         if (var4 != nullptr) {
            var4.setVertLight(var5, (int)(var7 * 255.0F) << 0 | (int)(var8 * 255.0F) << 8 | (int)(var9 * 255.0F) << 16 | 0xFF000000, var6);
            var4.setVertLight(var5 + 4, (int)(var7 * 255.0F) << 0 | (int)(var8 * 255.0F) << 8 | (int)(var9 * 255.0F) << 16 | 0xFF000000, var6);
         }

    return var5;
      }
   }

    static IsoCell getInstance() {
    return instance;
   }

    void render() {
      s_performance.isoCellRender.invokeAndMeasure(this, IsoCell::renderInternal);
   }

    void renderInternal() {
    int var1 = IsoCamera.frameState.playerIndex;
    IsoPlayer var2 = IsoPlayer.players[var1];
      if (var2.dirtyRecalcGridStackTime > 0.0F) {
         var2.dirtyRecalcGridStack = true;
      } else {
         var2.dirtyRecalcGridStack = false;
      }

      if (!PerformanceSettings.NewRoofHiding) {
         if (this.bHideFloors[var1] && this.unhideFloorsCounter[var1] > 0) {
            this.unhideFloorsCounter[var1]--;
         }

         if (this.unhideFloorsCounter[var1] <= 0) {
            this.bHideFloors[var1] = false;
            this.unhideFloorsCounter[var1] = 60;
         }
      }

    int var3 = 8;
      if (var3 < 8) {
         var3++;
      }

      this.recalcShading--;
    uint8_t var4 = 0;
    uint8_t var5 = 0;
    int var6 = var4 + IsoCamera.getOffscreenWidth(var1);
    int var7 = var5 + IsoCamera.getOffscreenHeight(var1);
    float var8 = IsoUtils.XToIso(var4, var5, 0.0F);
    float var9 = IsoUtils.YToIso(var6, var5, 0.0F);
    float var10 = IsoUtils.XToIso(var6, var7, 6.0F);
    float var11 = IsoUtils.YToIso(var4, var7, 6.0F);
      this.minY = (int)var9;
      this.maxY = (int)var11;
      this.minX = (int)var8;
      this.maxX = (int)var10;
      this.minX -= 2;
      this.minY -= 2;
      this.maxZ = MaxHeight;
      if (IsoCamera.CamCharacter == nullptr) {
         this.maxZ = 1;
      }

    uint8_t var12 = 0;
      var12 = 4;
      if (GameTime.instance.FPSMultiplier > 1.5F) {
         var12 = 6;
      }

      if (this.minX != this.lastMinX || this.minY != this.lastMinY) {
         this.lightUpdateCount = 10;
      }

      if (!PerformanceSettings.NewRoofHiding) {
    IsoGridSquare var13 = IsoCamera.CamCharacter == nullptr ? nullptr : IsoCamera.CamCharacter.getCurrentSquare();
         if (var13 != nullptr) {
            IsoGridSquare var14 = this.getGridSquare(
               (double)Math.round(IsoCamera.CamCharacter.getX()), (double)Math.round(IsoCamera.CamCharacter.getY()), (double)IsoCamera.CamCharacter.getZ()
            );
            if (var14 != nullptr && this.IsBehindStuff(var14)) {
               this.bHideFloors[var1] = true;
            }

            if (!this.bHideFloors[var1] && var13.getProperties().Is(IsoFlagType.hidewalls) || !var13.getProperties().Is(IsoFlagType.exterior)) {
               this.bHideFloors[var1] = true;
            }
         }

         if (this.bHideFloors[var1]) {
            this.maxZ = (int)IsoCamera.CamCharacter.getZ() + 1;
         }
      }

      if (PerformanceSettings.LightingFrameSkip < 3) {
         this.DrawStencilMask();
      }

      if (PerformanceSettings.LightingFrameSkip == 3) {
    int var32 = IsoCamera.getOffscreenWidth(var1) / 2;
    int var38 = IsoCamera.getOffscreenHeight(var1) / 2;
    short var15 = 409;
         var32 -= var15 / (2 / Core.TileScale);
         var38 -= var15 / (2 / Core.TileScale);
         this.StencilX1 = var32 - (int)IsoCamera.cameras[var1].RightClickX;
         this.StencilY1 = var38 - (int)IsoCamera.cameras[var1].RightClickY;
         this.StencilX2 = this.StencilX1 + var15 * Core.TileScale;
         this.StencilY2 = this.StencilY1 + var15 * Core.TileScale;
      }

      if (PerformanceSettings.NewRoofHiding && var2.dirtyRecalcGridStack) {
         this.hidesOrphanStructuresAbove = var3;
    IsoGridSquare var34 = nullptr;
         this.otherOccluderBuildings.get(var1).clear();
         if (this.otherOccluderBuildingsArr[var1] != nullptr) {
            this.otherOccluderBuildingsArr[var1][0] = nullptr;
         } else {
            this.otherOccluderBuildingsArr[var1] = new IsoBuilding[500];
         }

         if (IsoCamera.CamCharacter != nullptr && IsoCamera.CamCharacter.getCurrentSquare() != nullptr) {
    IsoGridSquare var41 = IsoCamera.CamCharacter.getCurrentSquare();
    int var45 = 10;
            if (this.ZombieList.size() < 10) {
               var45 = this.ZombieList.size();
            }

            if (this.nearestVisibleZombie[var1] != nullptr) {
               if (this.nearestVisibleZombie[var1].isDead()) {
                  this.nearestVisibleZombie[var1] = nullptr;
               } else {
    float var16 = this.nearestVisibleZombie[var1].x - IsoCamera.CamCharacter.x;
    float var17 = this.nearestVisibleZombie[var1].y - IsoCamera.CamCharacter.y;
                  this.nearestVisibleZombieDistSqr[var1] = var16 * var16 + var17 * var17;
               }
            }

            for (int var48 = 0; var48 < var45; this.zombieScanCursor++) {
               if (this.zombieScanCursor >= this.ZombieList.size()) {
                  this.zombieScanCursor = 0;
               }

    IsoZombie var52 = this.ZombieList.get(this.zombieScanCursor);
               if (var52 != nullptr) {
    IsoGridSquare var18 = var52.getCurrentSquare();
                  if (var18 != nullptr && var41.z == var18.z && var18.getCanSee(var1)) {
                     if (this.nearestVisibleZombie[var1] == nullptr) {
                        this.nearestVisibleZombie[var1] = var52;
    float var19 = this.nearestVisibleZombie[var1].x - IsoCamera.CamCharacter.x;
    float var20 = this.nearestVisibleZombie[var1].y - IsoCamera.CamCharacter.y;
                        this.nearestVisibleZombieDistSqr[var1] = var19 * var19 + var20 * var20;
                     } else {
    float var57 = var52.x - IsoCamera.CamCharacter.x;
    float var59 = var52.y - IsoCamera.CamCharacter.y;
    float var21 = var57 * var57 + var59 * var59;
                        if (var21 < this.nearestVisibleZombieDistSqr[var1]) {
                           this.nearestVisibleZombie[var1] = var52;
                           this.nearestVisibleZombieDistSqr[var1] = var21;
                        }
                     }
                  }
               }

               var48++;
            }

            for (int var49 = 0; var49 < 4; var49++) {
    IsoPlayer var53 = IsoPlayer.players[var49];
               if (var53 != nullptr && var53.getCurrentSquare() != nullptr) {
    IsoGridSquare var55 = var53.getCurrentSquare();
                  if (var49 == var1) {
                     var34 = var55;
                  }

    double var58 = var53.x - Math.floor(var53.x);
    double var61 = var53.y - Math.floor(var53.y);
    bool var23 = var58 > var61;
                  if (this.lastPlayerAngle[var49] == nullptr) {
                     this.lastPlayerAngle[var49] = std::make_shared<Vector2>(var53.getForwardDirection());
                     this.playerCutawaysDirty[var49] = true;
                  } else if (var53.getForwardDirection().dot(this.lastPlayerAngle[var49]) < 0.98F) {
                     this.lastPlayerAngle[var49].set(var53.getForwardDirection());
                     this.playerCutawaysDirty[var49] = true;
                  }

    IsoDirections var24 = IsoDirections.fromAngle(var53.getForwardDirection());
                  if (this.lastPlayerSquare[var49] != var55 || this.lastPlayerSquareHalf[var49] != var23 || this.lastPlayerDir[var49] != var24) {
                     this.playerCutawaysDirty[var49] = true;
                     this.lastPlayerSquare[var49] = var55;
                     this.lastPlayerSquareHalf[var49] = var23;
                     this.lastPlayerDir[var49] = var24;
    IsoBuilding var25 = var55.getBuilding();
                     this.playerWindowPeekingRoomId[var49] = -1;
                     this.GetBuildingsInFrontOfCharacter(this.playerOccluderBuildings.get(var49), var55, var23);
                     if (this.playerOccluderBuildingsArr[var1] == nullptr) {
                        this.playerOccluderBuildingsArr[var1] = new IsoBuilding[500];
                     }

                     this.playerHidesOrphanStructures[var49] = this.bOccludedByOrphanStructureFlag;
                     if (var25 == nullptr && !var53.bRemote) {
                        var25 = this.GetPeekedInBuilding(var55, var24);
                        if (var25 != nullptr) {
                           this.playerWindowPeekingRoomId[var49] = this.playerPeekedRoomId;
                        }
                     }

                     if (var25 != nullptr) {
                        this.AddUniqueToBuildingList(this.playerOccluderBuildings.get(var49), var25);
                     }

    std::vector var26 = this.playerOccluderBuildings.get(var49);

                     for (int var27 = 0; var27 < var26.size(); var27++) {
    IsoBuilding var28 = (IsoBuilding)var26.get(var27);
                        this.playerOccluderBuildingsArr[var1][var27] = var28;
                     }

                     this.playerOccluderBuildingsArr[var1][var26.size()] = nullptr;
                  }

                  if (var49 == var1 && var34 != nullptr) {
                     this.gridSquaresTempLeft.clear();
                     this.gridSquaresTempRight.clear();
                     this.GetSquaresAroundPlayerSquare(var53, var34, this.gridSquaresTempLeft, this.gridSquaresTempRight);

                     for (int var64 = 0; var64 < this.gridSquaresTempLeft.size(); var64++) {
    IsoGridSquare var68 = this.gridSquaresTempLeft.get(var64);
                        if (var68.getCanSee(var1) && (var68.getBuilding() == nullptr || var68.getBuilding() == var34.getBuilding())) {
    std::vector var71 = this.GetBuildingsInFrontOfMustSeeSquare(var68, OcclusionFilter.Right);

                           for (int var74 = 0; var74 < var71.size(); var74++) {
                              this.AddUniqueToBuildingList(this.otherOccluderBuildings.get(var1), (IsoBuilding)var71.get(var74));
                           }

                           this.playerHidesOrphanStructures[var1] = this.playerHidesOrphanStructures[var1] | this.bOccludedByOrphanStructureFlag;
                        }
                     }

                     for (int var65 = 0; var65 < this.gridSquaresTempRight.size(); var65++) {
    IsoGridSquare var69 = this.gridSquaresTempRight.get(var65);
                        if (var69.getCanSee(var1) && (var69.getBuilding() == nullptr || var69.getBuilding() == var34.getBuilding())) {
    std::vector var72 = this.GetBuildingsInFrontOfMustSeeSquare(var69, OcclusionFilter.Left);

                           for (int var75 = 0; var75 < var72.size(); var75++) {
                              this.AddUniqueToBuildingList(this.otherOccluderBuildings.get(var1), (IsoBuilding)var72.get(var75));
                           }

                           this.playerHidesOrphanStructures[var1] = this.playerHidesOrphanStructures[var1] | this.bOccludedByOrphanStructureFlag;
                        }
                     }

    std::vector var66 = this.otherOccluderBuildings.get(var1);
                     if (this.otherOccluderBuildingsArr[var1] == nullptr) {
                        this.otherOccluderBuildingsArr[var1] = new IsoBuilding[500];
                     }

                     for (int var70 = 0; var70 < var66.size(); var70++) {
    IsoBuilding var73 = (IsoBuilding)var66.get(var70);
                        this.otherOccluderBuildingsArr[var1][var70] = var73;
                     }

                     this.otherOccluderBuildingsArr[var1][var66.size()] = nullptr;
                  }

                  if (this.playerHidesOrphanStructures[var49] && this.hidesOrphanStructuresAbove > var55.getZ()) {
                     this.hidesOrphanStructuresAbove = var55.getZ();
                  }
               }
            }

            if (var34 != nullptr && this.hidesOrphanStructuresAbove < var34.getZ()) {
               this.hidesOrphanStructuresAbove = var34.getZ();
            }

    bool var50 = false;
            if (this.nearestVisibleZombie[var1] != nullptr && this.nearestVisibleZombieDistSqr[var1] < 150.0F) {
    IsoGridSquare var54 = this.nearestVisibleZombie[var1].getCurrentSquare();
               if (var54 != nullptr && var54.getCanSee(var1)) {
    double var56 = this.nearestVisibleZombie[var1].x - Math.floor(this.nearestVisibleZombie[var1].x);
    double var60 = this.nearestVisibleZombie[var1].y - Math.floor(this.nearestVisibleZombie[var1].y);
    bool var22 = var56 > var60;
                  var50 = true;
                  if (this.lastZombieSquare[var1] != var54 || this.lastZombieSquareHalf[var1] != var22) {
                     this.lastZombieSquare[var1] = var54;
                     this.lastZombieSquareHalf[var1] = var22;
                     this.GetBuildingsInFrontOfCharacter(this.zombieOccluderBuildings.get(var1), var54, var22);
    std::vector var62 = this.zombieOccluderBuildings.get(var1);
                     if (this.zombieOccluderBuildingsArr[var1] == nullptr) {
                        this.zombieOccluderBuildingsArr[var1] = new IsoBuilding[500];
                     }

                     for (int var63 = 0; var63 < var62.size(); var63++) {
    IsoBuilding var67 = (IsoBuilding)var62.get(var63);
                        this.zombieOccluderBuildingsArr[var1][var63] = var67;
                     }

                     this.zombieOccluderBuildingsArr[var1][var62.size()] = nullptr;
                  }
               }
            }

            if (!var50) {
               this.zombieOccluderBuildings.get(var1).clear();
               if (this.zombieOccluderBuildingsArr[var1] != nullptr) {
                  this.zombieOccluderBuildingsArr[var1][0] = nullptr;
               } else {
                  this.zombieOccluderBuildingsArr[var1] = new IsoBuilding[500];
               }
            }
         } else {
            for (int var40 = 0; var40 < 4; var40++) {
               this.playerOccluderBuildings.get(var40).clear();
               if (this.playerOccluderBuildingsArr[var40] != nullptr) {
                  this.playerOccluderBuildingsArr[var40][0] = nullptr;
               } else {
                  this.playerOccluderBuildingsArr[var40] = new IsoBuilding[500];
               }

               this.lastPlayerSquare[var40] = nullptr;
               this.playerCutawaysDirty[var40] = true;
            }

            this.playerWindowPeekingRoomId[var1] = -1;
            this.zombieOccluderBuildings.get(var1).clear();
            if (this.zombieOccluderBuildingsArr[var1] != nullptr) {
               this.zombieOccluderBuildingsArr[var1][0] = nullptr;
            } else {
               this.zombieOccluderBuildingsArr[var1] = new IsoBuilding[500];
            }

            this.lastZombieSquare[var1] = nullptr;
         }
      }

      if (!PerformanceSettings.NewRoofHiding) {
         for (int var35 = 0; var35 < IsoPlayer.numPlayers; var35++) {
            this.playerWindowPeekingRoomId[var35] = -1;
    IsoPlayer var42 = IsoPlayer.players[var35];
            if (var42 != nullptr) {
    IsoBuilding var46 = var42.getCurrentBuilding();
               if (var46 == nullptr) {
    IsoDirections var51 = IsoDirections.fromAngle(var42.getForwardDirection());
                  var46 = this.GetPeekedInBuilding(var42.getCurrentSquare(), var51);
                  if (var46 != nullptr) {
                     this.playerWindowPeekingRoomId[var35] = this.playerPeekedRoomId;
                  }
               }
            }
         }
      }

      if (IsoCamera.CamCharacter != nullptr
         && IsoCamera.CamCharacter.getCurrentSquare() != nullptr
         && IsoCamera.CamCharacter.getCurrentSquare().getProperties().Is(IsoFlagType.hidewalls)) {
         this.maxZ = (int)IsoCamera.CamCharacter.getZ() + 1;
      }

      this.bRendering = true;

      try {
         this.RenderTiles(var3);
      } catch (Exception var29) {
         this.bRendering = false;
         Logger.getLogger(GameWindow.class.getName()).log(Level.SEVERE, nullptr, var29);
      }

      this.bRendering = false;
      if (IsoGridSquare.getRecalcLightTime() < 0) {
         IsoGridSquare.setRecalcLightTime(60);
      }

      if (IsoGridSquare.getLightcache() <= 0) {
         IsoGridSquare.setLightcache(90);
      }

      for (int var36 = 0; var36 < this.ObjectList.size(); var36++) {
    IsoMovingObject var43 = this.ObjectList.get(var36);
         var43.renderlast();
      }

      for (int var37 = 0; var37 < this.StaticUpdaterObjectList.size(); var37++) {
    IsoObject var44 = this.StaticUpdaterObjectList.get(var37);
         var44.renderlast();
      }

      IsoTree.renderChopTreeIndicators();
      if (Core.bDebug) {
      }

      this.lastMinX = this.minX;
      this.lastMinY = this.minY;
      this.DoBuilding(IsoPlayer.getPlayerIndex(), true);
      this.renderRain();
   }

    void invalidatePeekedRoom(int var1) {
      this.lastPlayerDir[var1] = IsoDirections.Max;
   }

    bool initWeatherFx() {
      if (GameServer.bServer) {
    return false;
      } else {
         if (this.weatherFX == nullptr) {
            this.weatherFX = std::make_unique<IsoWeatherFX>();
            this.weatherFX.init();
         }

    return true;
      }
   }

    void updateWeatherFx() {
      if (this.initWeatherFx()) {
         this.weatherFX.update();
      }
   }

    void renderWeatherFx() {
      if (this.initWeatherFx()) {
         this.weatherFX.render();
      }
   }

    IsoWeatherFX getWeatherFX() {
      return this.weatherFX;
   }

    void renderRain() {
   }

    void setRainAlpha(int var1) {
      this.rainAlphaMax = var1 / 100.0F;
   }

    void setRainIntensity(int var1) {
      this.rainIntensity = var1;
   }

    void setRainSpeed(int var1) {
      this.rainSpeed = var1;
   }

    void reloadRainTextures() {
   }

    void GetBuildingsInFrontOfCharacter(std::vector<IsoBuilding> var1, IsoGridSquare var2, bool var3) {
      var1.clear();
      this.bOccludedByOrphanStructureFlag = false;
      if (var2 != nullptr) {
    int var4 = var2.getX();
    int var5 = var2.getY();
    int var6 = var2.getZ();
         this.GetBuildingsInFrontOfCharacterSquare(var4, var5, var6, var3, var1);
         if (var6 < MaxHeight) {
            this.GetBuildingsInFrontOfCharacterSquare(var4 - 1 + 3, var5 - 1 + 3, var6 + 1, var3, var1);
            this.GetBuildingsInFrontOfCharacterSquare(var4 - 2 + 3, var5 - 2 + 3, var6 + 1, var3, var1);
            if (var3) {
               this.GetBuildingsInFrontOfCharacterSquare(var4 + 3, var5 - 1 + 3, var6 + 1, !var3, var1);
               this.GetBuildingsInFrontOfCharacterSquare(var4 - 1 + 3, var5 - 2 + 3, var6 + 1, !var3, var1);
            } else {
               this.GetBuildingsInFrontOfCharacterSquare(var4 - 1 + 3, var5 + 3, var6 + 1, !var3, var1);
               this.GetBuildingsInFrontOfCharacterSquare(var4 - 2 + 3, var5 - 1 + 3, var6 + 1, !var3, var1);
            }
         }
      }
   }

    void GetBuildingsInFrontOfCharacterSquare(int var1, int var2, int var3, bool var4, std::vector<IsoBuilding> var5) {
    IsoGridSquare var6 = this.getGridSquare(var1, var2, var3);
      if (var6 == nullptr) {
         if (var3 < MaxHeight) {
            this.GetBuildingsInFrontOfCharacterSquare(var1 + 3, var2 + 3, var3 + 1, var4, var5);
         }
      } else {
    IsoGridOcclusionData var7 = var6.getOrCreateOcclusionData();
    OcclusionFilter var8 = var4 ? OcclusionFilter.Right : OcclusionFilter.Left;
         this.bOccludedByOrphanStructureFlag = this.bOccludedByOrphanStructureFlag | var7.getCouldBeOccludedByOrphanStructures(var8);
    std::vector var9 = var7.getBuildingsCouldBeOccluders(var8);

         for (int var10 = 0; var10 < var9.size(); var10++) {
            this.AddUniqueToBuildingList(var5, (IsoBuilding)var9.get(var10));
         }
      }
   }

   private std::vector<IsoBuilding> GetBuildingsInFrontOfMustSeeSquare(IsoGridSquare var1, OcclusionFilter var2) {
    IsoGridOcclusionData var3 = var1.getOrCreateOcclusionData();
      this.bOccludedByOrphanStructureFlag = var3.getCouldBeOccludedByOrphanStructures(OcclusionFilter.All);
      return var3.getBuildingsCouldBeOccluders(var2);
   }

    IsoBuilding GetPeekedInBuilding(IsoGridSquare var1, IsoDirections var2) {
      this.playerPeekedRoomId = -1;
      if (var1 == nullptr) {
    return nullptr;
      } else {
         if ((var2 == IsoDirections.NW || var2 == IsoDirections.N || var2 == IsoDirections.NE)
            && LosUtil.lineClear(this, var1.x, var1.y, var1.z, var1.x, var1.y - 1, var1.z, false) != TestResults.Blocked) {
    IsoGridSquare var3 = var1.nav[IsoDirections.N.index()];
            if (var3 != nullptr) {
    IsoBuilding var4 = var3.getBuilding();
               if (var4 != nullptr) {
                  this.playerPeekedRoomId = var3.getRoomID();
    return var4;
               }
            }
         }

         if ((var2 == IsoDirections.SW || var2 == IsoDirections.W || var2 == IsoDirections.NW)
            && LosUtil.lineClear(this, var1.x, var1.y, var1.z, var1.x - 1, var1.y, var1.z, false) != TestResults.Blocked) {
    IsoGridSquare var5 = var1.nav[IsoDirections.W.index()];
            if (var5 != nullptr) {
    IsoBuilding var8 = var5.getBuilding();
               if (var8 != nullptr) {
                  this.playerPeekedRoomId = var5.getRoomID();
    return var8;
               }
            }
         }

         if ((var2 == IsoDirections.SE || var2 == IsoDirections.S || var2 == IsoDirections.SW)
            && LosUtil.lineClear(this, var1.x, var1.y, var1.z, var1.x, var1.y + 1, var1.z, false) != TestResults.Blocked) {
    IsoGridSquare var6 = var1.nav[IsoDirections.S.index()];
            if (var6 != nullptr) {
    IsoBuilding var9 = var6.getBuilding();
               if (var9 != nullptr) {
                  this.playerPeekedRoomId = var6.getRoomID();
    return var9;
               }
            }
         }

         if ((var2 == IsoDirections.NE || var2 == IsoDirections.E || var2 == IsoDirections.SE)
            && LosUtil.lineClear(this, var1.x, var1.y, var1.z, var1.x + 1, var1.y, var1.z, false) != TestResults.Blocked) {
    IsoGridSquare var7 = var1.nav[IsoDirections.E.index()];
            if (var7 != nullptr) {
    IsoBuilding var10 = var7.getBuilding();
               if (var10 != nullptr) {
                  this.playerPeekedRoomId = var7.getRoomID();
    return var10;
               }
            }
         }

    return nullptr;
      }
   }

    void GetSquaresAroundPlayerSquare(IsoPlayer var1, IsoGridSquare var2, std::vector<IsoGridSquare> var3, std::vector<IsoGridSquare> var4) {
    float var5 = var1.x - 4.0F;
    float var6 = var1.y - 4.0F;
    int var7 = (int)var5;
    int var8 = (int)var6;
    int var9 = var2.getZ();

      for (int var10 = var8; var10 < var8 + 10; var10++) {
         for (int var11 = var7; var11 < var7 + 10; var11++) {
            if ((var11 >= (int)var1.x || var10 >= (int)var1.y) && (var11 != (int)var1.x || var10 != (int)var1.y)) {
    float var12 = var11 - var1.x;
    float var13 = var10 - var1.y;
               if (var13 < var12 + 4.5 && var13 > var12 - 4.5) {
    IsoGridSquare var14 = this.getGridSquare(var11, var10, var9);
                  if (var14 != nullptr) {
                     if (var13 >= var12) {
                        var3.push_back(var14);
                     }

                     if (var13 <= var12) {
                        var4.push_back(var14);
                     }
                  }
               }
            }
         }
      }
   }

    bool IsBehindStuff(IsoGridSquare var1) {
      if (!var1.getProperties().Is(IsoFlagType.exterior)) {
    return true;
      } else {
         for (int var2 = 1; var2 < 8 && var1.getZ() + var2 < MaxHeight; var2++) {
            for (int var3 = -5; var3 <= 6; var3++) {
               for (int var4 = -5; var4 <= 6; var4++) {
                  if (var4 >= var3 - 5 && var4 <= var3 + 5) {
    IsoGridSquare var6 = this.getGridSquare(var1.getX() + var4 + var2 * 3, var1.getY() + var3 + var2 * 3, var1.getZ() + var2);
                     if (var6 != nullptr && !var6.getObjects().empty()) {
                        if (var2 != 1 || var6.getObjects().size() != 1) {
    return true;
                        }

    IsoObject var7 = (IsoObject)var6.getObjects().get(0);
                        if (var7.sprite == nullptr || var7.sprite.name == nullptr || !var7.sprite.name.startsWith("lighting_outdoor")) {
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
    IsoDirections var0 = IsoDirections.N;
    float var1 = UIManager.getPickedTileLocal().x;
    float var2 = UIManager.getPickedTileLocal().y;
    float var3 = 0.5F - Math.abs(0.5F - var2);
    float var4 = 0.5F - Math.abs(0.5F - var1);
      if (var1 > 0.5F && var4 < var3) {
         var0 = IsoDirections.E;
      } else if (var2 > 0.5F && var4 > var3) {
         var0 = IsoDirections.S;
      } else if (var1 < 0.5F && var4 < var3) {
         var0 = IsoDirections.W;
      } else if (var2 < 0.5F && var4 > var3) {
         var0 = IsoDirections.N;
      }

    return var0;
   }

    void update() {
      s_performance.isoCellUpdate.invokeAndMeasure(this, IsoCell::updateInternal);
   }

    void updateInternal() {
      MovingObjectUpdateScheduler.instance.startFrame();
      IsoSprite.alphaStep = 0.075F * (GameTime.getInstance().getMultiplier() / 1.6F);
      IsoGridSquare.gridSquareCacheEmptyTimer++;
      this.ProcessSpottedRooms();
      if (!GameServer.bServer) {
         for (int var1 = 0; var1 < IsoPlayer.numPlayers; var1++) {
            if (IsoPlayer.players[var1] != nullptr && (!IsoPlayer.players[var1].isDead() || IsoPlayer.players[var1].ReanimatedCorpse != nullptr)) {
               IsoPlayer.setInstance(IsoPlayer.players[var1]);
               IsoCamera.CamCharacter = IsoPlayer.players[var1];
               this.ChunkMap[var1].update();
            }
         }
      }

      this.ProcessRemoveItems(nullptr);
      this.ProcessItems(nullptr);
      this.ProcessRemoveItems(nullptr);
      this.ProcessIsoObject();
      this.safeToAdd = false;
      this.ProcessObjects(nullptr);
      if (GameClient.bClient
         && (
            NetworkZombieSimulator.getInstance().anyUnknownZombies() && GameClient.instance.sendZombieRequestsTimer.Check()
               || GameClient.instance.sendZombieTimer.Check()
         )) {
         NetworkZombieSimulator.getInstance().send();
         GameClient.instance.sendZombieTimer.Reset();
         GameClient.instance.sendZombieRequestsTimer.Reset();
      }

      this.safeToAdd = true;
      this.ProcessStaticUpdaters();
      this.ObjectDeletionAddition();
      IsoDeadBody.updateBodies();
      IsoGridSquare.setLightcache(IsoGridSquare.getLightcache() - 1);
      IsoGridSquare.setRecalcLightTime(IsoGridSquare.getRecalcLightTime() - 1);
      if (GameServer.bServer) {
         this.LamppostPositions.clear();
         this.roomLights.clear();
      }

      if (!GameTime.isGamePaused()) {
         this.rainScroll = this.rainScroll + this.rainSpeed / 10.0F * 0.075F * (30.0F / PerformanceSettings.getLockFPS());
         if (this.rainScroll > 1.0F) {
            this.rainScroll = 0.0F;
         }
      }

      if (!GameServer.bServer) {
         this.updateWeatherFx();
      }
   }

    IsoGridSquare getRandomFreeTile() {
    IsoGridSquare var1 = nullptr;
    bool var2 = true;

      do {
         var2 = true;
         var1 = this.getGridSquare(Rand.Next(this.width), Rand.Next(this.height), 0);
         if (var1 == nullptr) {
            var2 = false;
         } else if (!var1.isFree(false)) {
            var2 = false;
         } else if (var1.getProperties().Is(IsoFlagType.solid) || var1.getProperties().Is(IsoFlagType.solidtrans)) {
            var2 = false;
         } else if (var1.getMovingObjects().size() > 0) {
            var2 = false;
         } else if (var1.Has(IsoObjectType.stairsBN) || var1.Has(IsoObjectType.stairsMN) || var1.Has(IsoObjectType.stairsTN)) {
            var2 = false;
         } else if (var1.Has(IsoObjectType.stairsBW) || var1.Has(IsoObjectType.stairsMW) || var1.Has(IsoObjectType.stairsTW)) {
            var2 = false;
         }
      } while (!var2);

    return var1;
   }

    IsoGridSquare getRandomOutdoorFreeTile() {
    IsoGridSquare var1 = nullptr;
    bool var2 = true;

      do {
         var2 = true;
         var1 = this.getGridSquare(Rand.Next(this.width), Rand.Next(this.height), 0);
         if (var1 == nullptr) {
            var2 = false;
         } else if (!var1.isFree(false)) {
            var2 = false;
         } else if (var1.getRoom() != nullptr) {
            var2 = false;
         } else if (var1.getProperties().Is(IsoFlagType.solid) || var1.getProperties().Is(IsoFlagType.solidtrans)) {
            var2 = false;
         } else if (var1.getMovingObjects().size() > 0) {
            var2 = false;
         } else if (var1.Has(IsoObjectType.stairsBN) || var1.Has(IsoObjectType.stairsMN) || var1.Has(IsoObjectType.stairsTN)) {
            var2 = false;
         } else if (var1.Has(IsoObjectType.stairsBW) || var1.Has(IsoObjectType.stairsMW) || var1.Has(IsoObjectType.stairsTW)) {
            var2 = false;
         }
      } while (!var2);

    return var1;
   }

    IsoGridSquare getRandomFreeTileInRoom() {
    std::stack var1 = new std::stack();

      for (int var2 = 0; var2 < this.RoomList.size(); var2++) {
         if (this.RoomList.get(var2).TileList.size() > 9
            && !this.RoomList.get(var2).Exits.empty()
            && ((IsoGridSquare)this.RoomList.get(var2).TileList.get(0)).getProperties().Is(IsoFlagType.solidfloor)) {
            var1.push_back(this.RoomList.get(var2));
         }
      }

      if (var1.empty()) {
    return nullptr;
      } else {
    IsoRoom var3 = (IsoRoom)var1.get(Rand.Next(var1.size()));
         return var3.getFreeTile();
      }
   }

    void roomSpotted(IsoRoom var1) {
      /* synchronized - TODO: add std::mutex */ (this.SpottedRooms) {
         if (!this.SpottedRooms.contains(var1)) {
            this.SpottedRooms.push(var1);
         }
      }
   }

    void ProcessSpottedRooms() {
      /* synchronized - TODO: add std::mutex */ (this.SpottedRooms) {
         for (int var2 = 0; var2 < this.SpottedRooms.size(); var2++) {
    IsoRoom var3 = this.SpottedRooms.get(var2);
            if (!var3.def.bDoneSpawn) {
               var3.def.bDoneSpawn = true;
               LuaEventManager.triggerEvent("OnSeeNewRoom", var3);
               VirtualZombieManager.instance.roomSpotted(var3);
               if (!GameClient.bClient
                  && !Core.bLastStand
                  && ("shed" == var3.def.name) || "garagestorage" == var3.def.name) || "storageunit" == var3.def.name))) {
    uint8_t var4 = 7;
                  if ("shed" == var3.def.name) || "garagestorage" == var3.def.name)) {
                     var4 = 4;
                  }

                  switch (SandboxOptions.instance.GeneratorSpawning.getValue()) {
                     case 1:
                        var4 += 3;
                        break;
                     case 2:
                        var4 += 2;
                     case 3:
                     default:
                        break;
                     case 4:
                        var4 -= 2;
                        break;
                     case 5:
                        var4 -= 3;
                  }

                  if (Rand.Next(var4) == 0) {
    IsoGridSquare var5 = var3.getRandomFreeSquare();
                     if (var5 != nullptr) {
    IsoGenerator var6 = std::make_shared<IsoGenerator>(InventoryItemFactory.CreateItem("Base.Generator"), this, var5);
                        if (GameServer.bServer) {
                           var6.transmitCompleteItemToClients();
                        }
                     }
                  }
               }
            }
         }

         this.SpottedRooms.clear();
      }
   }

    void savePlayer() {
      if (IsoPlayer.players[0] != nullptr && !IsoPlayer.players[0].isDead()) {
         IsoPlayer.players[0].save();
      }

      GameClient.instance.sendPlayerSave(IsoPlayer.players[0]);
   }

    void save(DataOutputStream var1, bool var2) {
      while (ChunkSaveWorker.instance.bSaving) {
         try {
            Thread.sleep(30L);
         } catch (InterruptedException var5) {
            var5.printStackTrace();
         }
      }

      for (int var3 = 0; var3 < IsoPlayer.numPlayers; var3++) {
         this.ChunkMap[var3].Save();
      }

      var1.writeInt(this.width);
      var1.writeInt(this.height);
      var1.writeInt(MaxHeight);
    File var7 = ZomboidFileSystem.instance.getFileInCurrentSave("map_t.bin");
    FileOutputStream var4 = std::make_shared<FileOutputStream>(var7);
      var1 = std::make_shared<DataOutputStream>(std::make_shared<BufferedOutputStream>(var4));
      GameTime.instance.save(var1);
      var1.flush();
      var1.close();
      IsoWorld.instance.MetaGrid.save();
      if (PlayerDB.isAllow()) {
         PlayerDB.getInstance().savePlayers();
      }

      ReanimatedPlayers.instance.saveReanimatedPlayers();
   }

    bool LoadPlayer(int var1) {
      if (GameClient.bClient) {
         return ClientPlayerDB.getInstance().loadNetworkPlayer();
      } else {
    File var2 = ZomboidFileSystem.instance.getFileInCurrentSave("map_p.bin");
         if (!var2.exists()) {
            PlayerDB.getInstance().importPlayersFromVehiclesDB();
            return PlayerDB.getInstance().loadLocalPlayer(1);
         } else {
    FileInputStream var3 = std::make_shared<FileInputStream>(var2);
    BufferedInputStream var4 = std::make_shared<BufferedInputStream>(var3);
            /* synchronized - TODO: add std::mutex */ (SliceY.SliceBufferLock) {
               SliceY.SliceBuffer.clear();
    int var6 = var4.read(SliceY.SliceBuffer.array());
               SliceY.SliceBuffer.limit(var6);
    uint8_t var7 = SliceY.SliceBuffer.get();
    uint8_t var8 = SliceY.SliceBuffer.get();
    uint8_t var9 = SliceY.SliceBuffer.get();
    uint8_t var10 = SliceY.SliceBuffer.get();
               if (var7 == 80 && var8 == 76 && var9 == 89 && var10 == 82) {
                  var1 = SliceY.SliceBuffer.getInt();
               } else {
                  SliceY.SliceBuffer.rewind();
               }

               if (var1 >= 69) {
    std::string var11 = GameWindow.ReadString(SliceY.SliceBuffer);
                  if (GameClient.bClient && var1 < 71) {
                     var11 = ServerOptions.instance.ServerPlayerID.getValue();
                  }

                  if (GameClient.bClient && !IsoPlayer.isServerPlayerIDValid(var11)) {
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
                  IsoPlayer.setInstance(std::make_shared<IsoPlayer>(instance));
                  IsoPlayer.players[0] = IsoPlayer.getInstance();
               }

               IsoPlayer.getInstance().load(SliceY.SliceBuffer, var1);
               var3.close();
            }

            PlayerDB.getInstance().saveLocalPlayersForce();
            var2.delete();
            PlayerDB.getInstance().uploadLocalPlayers2DB();
    return true;
         }
      }
   }

    IsoGridSquare getRelativeGridSquare(int var1, int var2, int var3) {
    int var10000 = this.ChunkMap[0].getWorldXMin();
    IsoChunkMap var10001 = this.ChunkMap[0];
    int var4 = var10000 * 10;
      var10000 = this.ChunkMap[0].getWorldYMin();
      var10001 = this.ChunkMap[0];
    int var5 = var10000 * 10;
      var1 += var4;
      var2 += var5;
      return this.getGridSquare(var1, var2, var3);
   }

    IsoGridSquare createNewGridSquare(int var1, int var2, int var3, bool var4) {
      if (!IsoWorld.instance.isValidSquare(var1, var2, var3)) {
    return nullptr;
      } else {
    IsoGridSquare var5 = this.getGridSquare(var1, var2, var3);
         if (var5 != nullptr) {
    return var5;
         } else {
            if (GameServer.bServer) {
    int var6 = var1 / 10;
    int var7 = var2 / 10;
               if (ServerMap.instance.getChunk(var6, var7) != nullptr) {
                  var5 = IsoGridSquare.getNew(this, nullptr, var1, var2, var3);
                  ServerMap.instance.setGridSquare(var1, var2, var3, var5);
               }
            } else if (this.getChunkForGridSquare(var1, var2, var3) != nullptr) {
               var5 = IsoGridSquare.getNew(this, nullptr, var1, var2, var3);
               this.ConnectNewSquare(var5, true);
            }

            if (var5 != nullptr && var4) {
               var5.RecalcAllWithNeighbours(true);
            }

    return var5;
         }
      }
   }

    IsoGridSquare getGridSquareDirect(int var1, int var2, int var3, int var4) {
    int var5 = IsoChunkMap.ChunkWidthInTiles;
      return this.gridSquares[var4][var1 + var2 * var5 + var3 * var5 * var5];
   }

    bool isInChunkMap(int var1, int var2) {
      for (int var3 = 0; var3 < IsoPlayer.numPlayers; var3++) {
    int var4 = this.ChunkMap[var3].getWorldXMinTiles();
    int var5 = this.ChunkMap[var3].getWorldXMaxTiles();
    int var6 = this.ChunkMap[var3].getWorldYMinTiles();
    int var7 = this.ChunkMap[var3].getWorldYMaxTiles();
         if (var1 >= var4 && var1 < var5 && var2 >= var6 && var2 < var7) {
    return true;
         }
      }

    return false;
   }

   public std::vector<IsoObject> getProcessIsoObjectRemove() {
      return this.ProcessIsoObjectRemove;
   }

    void checkHaveRoof(int var1, int var2) {
    bool var3 = false;

      for (int var4 = 8; var4 >= 0; var4--) {
    IsoGridSquare var5 = this.getGridSquare(var1, var2, var4);
         if (var5 != nullptr) {
            if (var3 != var5.haveRoof) {
               var5.haveRoof = var3;
               var5.RecalcAllWithNeighbours(true);
            }

            if (var5.Is(IsoFlagType.solidfloor)) {
               var3 = true;
            }
         }
      }
   }

    IsoZombie getFakeZombieForHit() {
      if (this.fakeZombieForHit == nullptr) {
         this.fakeZombieForHit = std::make_shared<IsoZombie>(this);
      }

      return this.fakeZombieForHit;
   }

    void addHeatSource(IsoHeatSource var1) {
      if (!GameServer.bServer) {
         if (this.heatSources.contains(var1)) {
            DebugLog.log("ERROR addHeatSource called again with the same HeatSource");
         } else {
            this.heatSources.push_back(var1);
         }
      }
   }

    void removeHeatSource(IsoHeatSource var1) {
      if (!GameServer.bServer) {
         this.heatSources.remove(var1);
      }
   }

    void updateHeatSources() {
      if (!GameServer.bServer) {
         for (int var1 = this.heatSources.size() - 1; var1 >= 0; var1--) {
    IsoHeatSource var2 = this.heatSources.get(var1);
            if (!var2.isInBounds()) {
               this.heatSources.remove(var1);
            }
         }
      }
   }

    int getHeatSourceTemperature(int var1, int var2, int var3) {
    int var4 = 0;

      for (int var5 = 0; var5 < this.heatSources.size(); var5++) {
    IsoHeatSource var6 = this.heatSources.get(var5);
         if (var6.getZ() == var3) {
    float var7 = IsoUtils.DistanceToSquared(var1, var2, var6.getX(), var6.getY());
            if (var7 < var6.getRadius() * var6.getRadius()) {
    TestResults var8 = LosUtil.lineClear(this, var6.getX(), var6.getY(), var6.getZ(), var1, var2, var3, false);
               if (var8 == TestResults.Clear || var8 == TestResults.ClearThroughOpenDoor) {
                  var4 = (int)(var4 + var6.getTemperature() * (1.0 - Math.sqrt(var7) / var6.getRadius()));
               }
            }
         }
      }

    return var4;
   }

    float getHeatSourceHighestTemperature(float var1, int var2, int var3, int var4) {
    float var5 = var1;
    float var6 = var1;
    float var7 = 0.0F;
    void* var8 = nullptr;
    float var9 = 0.0F;

      for (int var10 = 0; var10 < this.heatSources.size(); var10++) {
    IsoHeatSource var11 = this.heatSources.get(var10);
         if (var11.getZ() == var4) {
    float var12 = IsoUtils.DistanceToSquared(var2, var3, var11.getX(), var11.getY());
            var8 = this.getGridSquare(var11.getX(), var11.getY(), var11.getZ());
            var9 = 0.0F;
            if (var8 != nullptr) {
               if (!var8.isInARoom()) {
                  var9 = var5 - 30.0F;
                  if (var9 < -15.0F) {
                     var9 = -15.0F;
                  } else if (var9 > 5.0F) {
                     var9 = 5.0F;
                  }
               } else {
                  var9 = var5 - 30.0F;
                  if (var9 < -7.0F) {
                     var9 = -7.0F;
                  } else if (var9 > 7.0F) {
                     var9 = 7.0F;
                  }
               }
            }

            var7 = ClimateManager.lerp((float)(1.0 - Math.sqrt(var12) / var11.getRadius()), var5, var11.getTemperature() + var9);
            if (!(var7 <= var6) && var12 < var11.getRadius() * var11.getRadius()) {
    TestResults var13 = LosUtil.lineClear(this, var11.getX(), var11.getY(), var11.getZ(), var2, var3, var4, false);
               if (var13 == TestResults.Clear || var13 == TestResults.ClearThroughOpenDoor) {
                  var6 = var7;
               }
            }
         }
      }

    return var6;
   }

    void putInVehicle(IsoGameCharacter var1) {
      if (var1 != nullptr && var1.savedVehicleSeat != -1) {
    int var2 = ((int)var1.getX() - 4) / 10;
    int var3 = ((int)var1.getY() - 4) / 10;
    int var4 = ((int)var1.getX() + 4) / 10;
    int var5 = ((int)var1.getY() + 4) / 10;

         for (int var6 = var3; var6 <= var5; var6++) {
            for (int var7 = var2; var7 <= var4; var7++) {
    IsoChunk var8 = this.getChunkForGridSquare(var7 * 10, var6 * 10, (int)var1.getZ());
               if (var8 != nullptr) {
                  for (int var9 = 0; var9 < var8.vehicles.size(); var9++) {
    BaseVehicle var10 = (BaseVehicle)var8.vehicles.get(var9);
                     if ((int)var10.getZ() == (int)var1.getZ()
                        && IsoUtils.DistanceToSquared(var10.getX(), var10.getY(), var1.savedVehicleX, var1.savedVehicleY) < 0.010000001F) {
                        if (var10.VehicleID == -1) {
                           return;
                        }

    Position var11 = var10.getPassengerPosition(var1.savedVehicleSeat, "inside");
                        if (var11 != nullptr && !var10.isSeatOccupied(var1.savedVehicleSeat)) {
                           var10.enter(var1.savedVehicleSeat, var1, var11.offset);
                           LuaEventManager.triggerEvent("OnEnterVehicle", var1);
                           if (var10.getCharacter(var1.savedVehicleSeat) == var1 && var1.savedVehicleRunning) {
                              var10.resumeRunningAfterLoad();
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

    void resumeVehicleSounds(IsoGameCharacter var1) {
      if (var1 != nullptr && var1.savedVehicleSeat != -1) {
    int var2 = ((int)var1.getX() - 4) / 10;
    int var3 = ((int)var1.getY() - 4) / 10;
    int var4 = ((int)var1.getX() + 4) / 10;
    int var5 = ((int)var1.getY() + 4) / 10;

         for (int var6 = var3; var6 <= var5; var6++) {
            for (int var7 = var2; var7 <= var4; var7++) {
    IsoChunk var8 = this.getChunkForGridSquare(var7 * 10, var6 * 10, (int)var1.getZ());
               if (var8 != nullptr) {
                  for (int var9 = 0; var9 < var8.vehicles.size(); var9++) {
    BaseVehicle var10 = (BaseVehicle)var8.vehicles.get(var9);
                     if (var10.lightbarSirenMode.isEnable()) {
                        var10.setLightbarSirenMode(var10.lightbarSirenMode.get());
                     }
                  }
               }
            }
         }
      }
   }

    void AddUniqueToBuildingList(std::vector<IsoBuilding> var1, IsoBuilding var2) {
      for (int var3 = 0; var3 < var1.size(); var3++) {
         if (var1.get(var3) == var2) {
            return;
         }
      }

      var1.push_back(var2);
   }

    IsoSpriteManager getSpriteManager() {
      return IsoSpriteManager.instance;
   }
}
} // namespace iso
} // namespace zombie
