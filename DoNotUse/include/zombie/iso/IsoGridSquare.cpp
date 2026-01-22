#pragma once
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/net/MalformedURLException.h"
#include "java/net/URL.h"
#include "java/net/URLConnection.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/IndieGL.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/MapCollisionData.h"
#include "zombie/SandboxOptions.h"
#include "zombie/SoundManager.h"
#include "zombie/ZomboidBitFlag.h"
#include "zombie/ai/states/ZombieIdleState.h"
#include "zombie/audio/BaseSoundEmitter.h"
#include "zombie/characters/BodyDamage/BodyPart.h"
#include "zombie/characters/BodyDamage/BodyPartType.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoGameCharacter/LightInfo.h"
#include "zombie/characters/IsoGameCharacter/TorchInfo.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoSurvivor.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/characters/Moodles/MoodleType.h"
#include "zombie/core/Color.h"
#include "zombie/core/Core.h"
#include "zombie/core/PerformanceSettings.h"
#include "zombie/core/Rand.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/SpriteRenderer/WallShaderTexRender.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/opengl/RenderSettings.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/properties/PropertyContainer.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/core/textures/TextureDraw.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/debug/DebugType.h"
#include "zombie/erosion/ErosionData/Square.h"
#include "zombie/erosion/categories/ErosionCategory/Data.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/inventory/types/Food.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/iso/IsoGridSquare/1.h"
#include "zombie/iso/IsoGridSquare/CellGetSquare.h"
#include "zombie/iso/IsoGridSquare/CircleStencilShader.h"
#include "zombie/iso/IsoGridSquare/GetSquare.h"
#include "zombie/iso/IsoGridSquare/ILighting.h"
#include "zombie/iso/IsoGridSquare/Lighting.h"
#include "zombie/iso/IsoGridSquare/PuddlesDirection.h"
#include "zombie/iso/IsoGridSquare/s_performance.h"
#include "zombie/iso/IsoMetaGrid/Zone.h"
#include "zombie/iso/IsoObject/VisionResult.h"
#include "zombie/iso/LightingJNI/JNILighting.h"
#include "zombie/iso/LosUtil/TestResults.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/SpriteDetails/IsoObjectType.h"
#include "zombie/iso/areas/IsoBuilding.h"
#include "zombie/iso/areas/IsoRoom.h"
#include "zombie/iso/areas/NonPvpZone.h"
#include "zombie/iso/areas/SafeHouse.h"
#include "zombie/iso/areas/isoregion/IsoRegions.h"
#include "zombie/iso/areas/isoregion/regions/IWorldRegion.h"
#include "zombie/iso/areas/isoregion/regions/IsoWorldRegion.h"
#include "zombie/iso/objects/IsoBarricade.h"
#include "zombie/iso/objects/IsoBrokenGlass.h"
#include "zombie/iso/objects/IsoCarBatteryCharger.h"
#include "zombie/iso/objects/IsoCompost.h"
#include "zombie/iso/objects/IsoCurtain.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/iso/objects/IsoDoor.h"
#include "zombie/iso/objects/IsoFire.h"
#include "zombie/iso/objects/IsoFireManager.h"
#include "zombie/iso/objects/IsoGenerator.h"
#include "zombie/iso/objects/IsoLightSwitch.h"
#include "zombie/iso/objects/IsoMannequin.h"
#include "zombie/iso/objects/IsoRainSplash.h"
#include "zombie/iso/objects/IsoRaindrop.h"
#include "zombie/iso/objects/IsoThumpable.h"
#include "zombie/iso/objects/IsoTrap.h"
#include "zombie/iso/objects/IsoTrap/ExplosionMode.h"
#include "zombie/iso/objects/IsoTree.h"
#include "zombie/iso/objects/IsoWaveSignal.h"
#include "zombie/iso/objects/IsoWindow.h"
#include "zombie/iso/objects/IsoWindowFrame.h"
#include "zombie/iso/objects/IsoWorldInventoryObject.h"
#include "zombie/iso/objects/RainManager.h"
#include "zombie/iso/objects/interfaces/BarricadeAble.h"
#include "zombie/iso/sprite/IsoDirectionFrame.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteInstance.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/iso/sprite/shapers/FloorShaperAttachedSprites.h"
#include "zombie/iso/sprite/shapers/FloorShaperDeDiamond.h"
#include "zombie/iso/sprite/shapers/FloorShaperDiamond.h"
#include "zombie/iso/sprite/shapers/WallShaperN.h"
#include "zombie/iso/sprite/shapers/WallShaperW.h"
#include "zombie/iso/sprite/shapers/WallShaperWhole.h"
#include "zombie/iso/weather/fx/WeatherFxMask.h"
#include "zombie/meta/Meta.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/PacketTypes/PacketType.h"
#include "zombie/network/ServerLOS/ServerLighting.h"
#include "zombie/network/ServerMap.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/Item.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/Type.h"
#include "zombie/util/io/BitHeader.h"
#include "zombie/util/io/BitHeader/HeaderSize.h"
#include "zombie/util/io/BitHeaderRead.h"
#include "zombie/util/io/BitHeaderWrite.h"
#include "zombie/util/list/PZArrayList.h"
#include "zombie/util/list/PZArrayUtil.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/PolygonalMap2.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {


class IsoGridSquare {
public:
    bool hasTree;
   private std::vector<float> LightInfluenceB;
   private std::vector<float> LightInfluenceG;
   private std::vector<float> LightInfluenceR;
   public const IsoGridSquare[] nav = new IsoGridSquare[8];
    int collideMatrix = -1;
    int pathMatrix = -1;
    int visionMatrix = -1;
    IsoRoom room = nullptr;
    IsoGridSquare w;
    IsoGridSquare nw;
    IsoGridSquare sw;
    IsoGridSquare s;
    IsoGridSquare n;
    IsoGridSquare ne;
    IsoGridSquare se;
    IsoGridSquare e;
    bool haveSheetRope = false;
    IWorldRegion isoWorldRegion;
    bool hasSetIsoWorldRegion = false;
    int ObjectsSyncCount = 0;
    IsoBuilding roofHideBuilding;
    bool bFlattenGrassEtc;
    static const long VisiFlagTimerPeriod_ms = 750L;
   private const boolean[] playerCutawayFlags = new boolean[4];
   private const long[] playerCutawayFlagLockUntilTimes = new long[4];
   private const boolean[] targetPlayerCutawayFlags = new boolean[4];
   private const boolean[] playerIsDissolvedFlags = new boolean[4];
   private const long[] playerIsDissolvedFlagLockUntilTimes = new long[4];
   private const boolean[] targetPlayerIsDissolvedFlags = new boolean[4];
    IsoWaterGeometry water = nullptr;
    IsoPuddlesGeometry puddles = nullptr;
    float puddlesCacheSize = -1.0F;
    float puddlesCacheLevel = -1.0F;
   public const ILighting[] lighting = new ILighting[4];
    int x;
    int y;
    int z;
    int CachedScreenValue = -1;
    float CachedScreenX;
    float CachedScreenY;
    static long torchTimer = 0L;
    bool SolidFloorCached = false;
    bool SolidFloor = false;
    bool CacheIsFree = false;
    bool CachedIsFree = false;
    IsoChunk chunk;
    int roomID = -1;
    int ID = -999;
    Zone zone;
   private const std::vector<IsoGameCharacter> DeferedCharacters = std::make_unique<std::vector<>>();
    int DeferredCharacterTick = -1;
   private const std::vector<IsoMovingObject> StaticMovingObjects = new std::vector<>(0);
   private const std::vector<IsoMovingObject> MovingObjects = new std::vector<>(0);
   protected const PZArrayList<IsoObject> Objects = std::make_shared<PZArrayList>(IsoObject.class, 2);
   protected const PZArrayList<IsoObject> localTemporaryObjects = std::make_shared<PZArrayList>(IsoObject.class, 2);
   private const std::vector<IsoWorldInventoryObject> WorldObjects = std::make_unique<std::vector<>>();
    const ZomboidBitFlag hasTypes = std::make_shared<ZomboidBitFlag>(IsoObjectType.MAX.index());
    const PropertyContainer Properties = std::make_shared<PropertyContainer>();
   private const std::vector<IsoObject> SpecialObjects = new std::vector<>(0);
    bool haveRoof = false;
    bool burntOut = false;
    bool bHasFlies = false;
    IsoGridOcclusionData OcclusionDataCache = nullptr;
   private static const PZArrayList<IsoWorldInventoryObject> tempWorldInventoryObjects = std::make_shared<PZArrayList>(IsoWorldInventoryObject.class, 16);
   public static const ConcurrentLinkedQueue<IsoGridSquare> isoGridSquareCache = std::make_unique<ConcurrentLinkedQueue<>>();
   public static ArrayDeque<IsoGridSquare> loadGridSquareCache;
    bool overlayDone = false;
    KahluaTable table = nullptr;
    int trapPositionX = -1;
    int trapPositionY = -1;
    int trapPositionZ = -1;
    bool haveElectricity = false;
    static int gridSquareCacheEmptyTimer = 0;
    static float darkStep = 0.06F;
    static int RecalcLightTime = 0;
    static int lightcache = 0;
   public static const std::vector<IsoGridSquare> choices = std::make_unique<std::vector<>>();
    static bool USE_WALL_SHADER = true;
    static const int cutawayY = 0;
    static const int cutawayNWWidth = 66;
    static const int cutawayNWHeight = 226;
    static const int cutawaySEXCut = 1084;
    static const int cutawaySEXUncut = 1212;
    static const int cutawaySEWidth = 6;
    static const int cutawaySEHeight = 196;
    static const int cutawayNXFullyCut = 700;
    static const int cutawayNXCutW = 444;
    static const int cutawayNXUncut = 828;
    static const int cutawayNXCutE = 956;
    static const int cutawayWXFullyCut = 512;
    static const int cutawayWXCutS = 768;
    static const int cutawayWXUncut = 896;
    static const int cutawayWXCutN = 256;
    static const int cutawayFenceXOffset = 1;
    static const int cutawayLogWallXOffset = 1;
    static const int cutawayMedicalCurtainWXOffset = -3;
    static const int cutawaySpiffoWindowXOffset = -24;
    static const int cutawayRoof4XOffset = -60;
    static const int cutawayRoof17XOffset = -46;
    static const int cutawayRoof28XOffset = -60;
    static const int cutawayRoof41XOffset = -46;
    static const ColorInfo lightInfoTemp = std::make_shared<ColorInfo>();
    static const float doorWindowCutawayLightMin = 0.3F;
    static bool bWallCutawayW;
    static bool bWallCutawayN;
    bool isSolidFloorCache;
    bool isExteriorCache;
    bool isVegitationCache;
    int hourLastSeen = int.MIN_VALUE;
    static IsoGridSquare lastLoaded = nullptr;
    static int IDMax = -1;
    static int col = -1;
    static int path = -1;
    static int pathdoor = -1;
    static int vision = -1;
    long hashCodeObjects;
    static const Color tr = std::make_shared<Color>(1, 1, 1, 1);
    static const Color tl = std::make_shared<Color>(1, 1, 1, 1);
    static const Color br = std::make_shared<Color>(1, 1, 1, 1);
    static const Color bl = std::make_shared<Color>(1, 1, 1, 1);
    static const Color interp1 = std::make_shared<Color>(1, 1, 1, 1);
    static const Color interp2 = std::make_shared<Color>(1, 1, 1, 1);
    static const Color finalCol = std::make_shared<Color>(1, 1, 1, 1);
    static const CellGetSquare cellGetSquare = std::make_shared<CellGetSquare>();
    bool propertiesDirty = true;
    static bool UseSlowCollision = false;
    static bool bDoSlowPathfinding = false;
   private static const Comparator<IsoMovingObject> comp = (var0, var1) -> var0.compareToY(var1);
    static bool isOnScreenLast = false;
    float splashX;
    float splashY;
    float splashFrame = -1.0F;
    int splashFrameNum;
   private const ColorInfo[] lightInfo = new ColorInfo[4];
   static std::string[] rainsplashCache = new std::string[50];
    static const ColorInfo defColorInfo = std::make_shared<ColorInfo>();
    static const ColorInfo blackColorInfo = std::make_shared<ColorInfo>();
    static int colu = 0;
    static int coll = 0;
    static int colr = 0;
    static int colu2 = 0;
    static int coll2 = 0;
    static int colr2 = 0;
    static bool CircleStencil = false;
    static float rmod = 0.0F;
    static float gmod = 0.0F;
    static float bmod = 0.0F;
    static const Vector2 tempo = std::make_shared<Vector2>();
    static const Vector2 tempo2 = std::make_shared<Vector2>();
    IsoRaindrop RainDrop = nullptr;
    IsoRainSplash RainSplash = nullptr;
    Square erosion;
   private static const int[] SURFACE_OFFSETS = new int[8];
    static const int WALL_TYPE_N = 1;
    static const int WALL_TYPE_S = 2;
    static const int WALL_TYPE_W = 4;
    static const int WALL_TYPE_E = 8;

    static bool getMatrixBit(int var0, int var1, int var2, int var3) {
    return getMatrixBit();
   }

    static bool getMatrixBit(int var0, uint8_t var1, uint8_t var2, uint8_t var3) {
      return (var0 >> var1 + var2 * 3 + var3 * 9 & 1) != 0;
   }

    static int setMatrixBit(int var0, int var1, int var2, int var3, bool var4) {
    return setMatrixBit();
   }

    static int setMatrixBit(int var0, uint8_t var1, uint8_t var2, uint8_t var3, bool var4) {
      return var4 ? var0 | 1 << var1 + var2 * 3 + var3 * 9 : var0 & ~(1 << var1 + var2 * 3 + var3 * 9);
   }

    void setPlayerCutawayFlag(int var1, bool var2, long var3) {
      this.targetPlayerCutawayFlags[var1] = var2;
      if (var3 > this.playerCutawayFlagLockUntilTimes[var1] && this.playerCutawayFlags[var1] != this.targetPlayerCutawayFlags[var1]) {
         this.playerCutawayFlags[var1] = this.targetPlayerCutawayFlags[var1];
         this.playerCutawayFlagLockUntilTimes[var1] = var3 + 750L;
      }
   }

    bool getPlayerCutawayFlag(int var1, long var2) {
      return var2 > this.playerCutawayFlagLockUntilTimes[var1] ? this.targetPlayerCutawayFlags[var1] : this.playerCutawayFlags[var1];
   }

    void setIsDissolved(int var1, bool var2, long var3) {
      this.targetPlayerIsDissolvedFlags[var1] = var2;
      if (var3 > this.playerIsDissolvedFlagLockUntilTimes[var1] && this.playerIsDissolvedFlags[var1] != this.targetPlayerIsDissolvedFlags[var1]) {
         this.playerIsDissolvedFlags[var1] = this.targetPlayerIsDissolvedFlags[var1];
         this.playerIsDissolvedFlagLockUntilTimes[var1] = var3 + 750L;
      }
   }

    bool getIsDissolved(int var1, long var2) {
      return var2 > this.playerIsDissolvedFlagLockUntilTimes[var1] ? this.targetPlayerIsDissolvedFlags[var1] : this.playerIsDissolvedFlags[var1];
   }

    IsoWaterGeometry getWater() {
      if (this.water != nullptr && this.water.m_adjacentChunkLoadedCounter != this.chunk.m_adjacentChunkLoadedCounter) {
         this.water.m_adjacentChunkLoadedCounter = this.chunk.m_adjacentChunkLoadedCounter;
         if (this.water.hasWater || this.water.bShore) {
            this.clearWater();
         }
      }

      if (this.water == nullptr) {
         try {
            this.water = (IsoWaterGeometry)IsoWaterGeometry.pool.alloc();
            this.water.m_adjacentChunkLoadedCounter = this.chunk.m_adjacentChunkLoadedCounter;
            if (this.water.init(this) == nullptr) {
               IsoWaterGeometry.pool.release(this.water);
               this.water = nullptr;
            }
         } catch (Exception var2) {
            this.clearWater();
         }
      }

      return this.water;
   }

    void clearWater() {
      if (this.water != nullptr) {
         IsoWaterGeometry.pool.release(this.water);
         this.water = nullptr;
      }
   }

    IsoPuddlesGeometry getPuddles() {
      if (this.puddles == nullptr) {
         try {
            /* synchronized - TODO: add std::mutex */ (IsoPuddlesGeometry.pool) {
               this.puddles = (IsoPuddlesGeometry)IsoPuddlesGeometry.pool.alloc();
            }

            this.puddles.square = this;
            this.puddles.bRecalc = true;
         } catch (Exception var4) {
            this.clearPuddles();
         }
      }

      return this.puddles;
   }

    void clearPuddles() {
      if (this.puddles != nullptr) {
         this.puddles.square = nullptr;
         /* synchronized - TODO: add std::mutex */ (IsoPuddlesGeometry.pool) {
            IsoPuddlesGeometry.pool.release(this.puddles);
         }

         this.puddles = nullptr;
      }
   }

    float getPuddlesInGround() {
      if (this.isInARoom()) {
         return -1.0F;
      } else {
         if (Math.abs(
               IsoPuddles.getInstance().getPuddlesSize() + Core.getInstance().getPerfPuddles() + IsoCamera.frameState.OffscreenWidth - this.puddlesCacheSize
            )
            > 0.01) {
            this.puddlesCacheSize = IsoPuddles.getInstance().getPuddlesSize() + Core.getInstance().getPerfPuddles() + IsoCamera.frameState.OffscreenWidth;
            this.puddlesCacheLevel = IsoPuddlesCompute.computePuddle(this);
         }

         return this.puddlesCacheLevel;
      }
   }

    IsoGridOcclusionData getOcclusionData() {
      return this.OcclusionDataCache;
   }

    IsoGridOcclusionData getOrCreateOcclusionData() {
      assert !GameServer.bServer;

      if (this.OcclusionDataCache == nullptr) {
         this.OcclusionDataCache = std::make_shared<IsoGridOcclusionData>(this);
      }

      return this.OcclusionDataCache;
   }

    void softClear() {
      this.zone = nullptr;
      this.room = nullptr;
      this.w = nullptr;
      this.nw = nullptr;
      this.sw = nullptr;
      this.s = nullptr;
      this.n = nullptr;
      this.ne = nullptr;
      this.se = nullptr;
      this.e = nullptr;
      this.isoWorldRegion = nullptr;
      this.hasSetIsoWorldRegion = false;

      for (int var1 = 0; var1 < 8; var1++) {
         this.nav[var1] = nullptr;
      }
   }

    float getGridSneakModifier(bool var1) {
      if (!var1) {
         if (this.Properties.Is("CloseSneakBonus")) {
            return int.parseInt(this.Properties.Val("CloseSneakBonus")) / 100.0F;
         }

         if (this.Properties.Is(IsoFlagType.collideN)
            || this.Properties.Is(IsoFlagType.collideW)
            || this.Properties.Is(IsoFlagType.WindowN)
            || this.Properties.Is(IsoFlagType.WindowW)
            || this.Properties.Is(IsoFlagType.doorN)
            || this.Properties.Is(IsoFlagType.doorW)) {
            return 8.0F;
         }
      } else if (this.Properties.Is(IsoFlagType.solidtrans)) {
         return 4.0F;
      }

      return 1.0F;
   }

    bool isSomethingTo(IsoGridSquare var1) {
      return this.isWallTo(var1) || this.isWindowTo(var1) || this.isDoorTo(var1);
   }

    IsoObject getTransparentWallTo(IsoGridSquare var1) {
      if (var1 == nullptr || var1 == this || !this.isWallTo(var1)) {
    return nullptr;
      } else if (var1.x > this.x && var1.Properties.Is(IsoFlagType.SpearOnlyAttackThrough) && !var1.Properties.Is(IsoFlagType.WindowW)) {
         return var1.getWall();
      } else if (this.x > var1.x && this.Properties.Is(IsoFlagType.SpearOnlyAttackThrough) && !this.Properties.Is(IsoFlagType.WindowW)) {
         return this.getWall();
      } else if (var1.y > this.y && var1.Properties.Is(IsoFlagType.SpearOnlyAttackThrough) && !var1.Properties.Is(IsoFlagType.WindowN)) {
         return var1.getWall();
      } else if (this.y > var1.y && this.Properties.Is(IsoFlagType.SpearOnlyAttackThrough) && !this.Properties.Is(IsoFlagType.WindowN)) {
         return this.getWall();
      } else {
         if (var1.x != this.x && var1.y != this.y) {
    IsoObject var2 = this.getTransparentWallTo(IsoWorld.instance.CurrentCell.getGridSquare(var1.x, this.y, this.z));
    IsoObject var3 = this.getTransparentWallTo(IsoWorld.instance.CurrentCell.getGridSquare(this.x, var1.y, this.z));
            if (var2 != nullptr) {
    return var2;
            }

            if (var3 != nullptr) {
    return var3;
            }

            var2 = var1.getTransparentWallTo(IsoWorld.instance.CurrentCell.getGridSquare(var1.x, this.y, this.z));
            var3 = var1.getTransparentWallTo(IsoWorld.instance.CurrentCell.getGridSquare(this.x, var1.y, this.z));
            if (var2 != nullptr) {
    return var2;
            }

            if (var3 != nullptr) {
    return var3;
            }
         }

    return nullptr;
      }
   }

    bool isWallTo(IsoGridSquare var1) {
      if (var1 == nullptr || var1 == this) {
    return false;
      } else if (var1.x > this.x && var1.Properties.Is(IsoFlagType.collideW) && !var1.Properties.Is(IsoFlagType.WindowW)) {
    return true;
      } else if (this.x > var1.x && this.Properties.Is(IsoFlagType.collideW) && !this.Properties.Is(IsoFlagType.WindowW)) {
    return true;
      } else if (var1.y > this.y && var1.Properties.Is(IsoFlagType.collideN) && !var1.Properties.Is(IsoFlagType.WindowN)) {
    return true;
      } else if (this.y > var1.y && this.Properties.Is(IsoFlagType.collideN) && !this.Properties.Is(IsoFlagType.WindowN)) {
    return true;
      } else {
         if (var1.x != this.x && var1.y != this.y) {
            if (this.isWallTo(IsoWorld.instance.CurrentCell.getGridSquare(var1.x, this.y, this.z))
               || this.isWallTo(IsoWorld.instance.CurrentCell.getGridSquare(this.x, var1.y, this.z))) {
    return true;
            }

            if (var1.isWallTo(IsoWorld.instance.CurrentCell.getGridSquare(var1.x, this.y, this.z))
               || var1.isWallTo(IsoWorld.instance.CurrentCell.getGridSquare(this.x, var1.y, this.z))) {
    return true;
            }
         }

    return false;
      }
   }

    bool isWindowTo(IsoGridSquare var1) {
      if (var1 == nullptr || var1 == this) {
    return false;
      } else if (var1.x > this.x && var1.Properties.Is(IsoFlagType.windowW)) {
    return true;
      } else if (this.x > var1.x && this.Properties.Is(IsoFlagType.windowW)) {
    return true;
      } else if (var1.y > this.y && var1.Properties.Is(IsoFlagType.windowN)) {
    return true;
      } else if (this.y > var1.y && this.Properties.Is(IsoFlagType.windowN)) {
    return true;
      } else {
         if (var1.x != this.x && var1.y != this.y) {
            if (this.isWindowTo(IsoWorld.instance.CurrentCell.getGridSquare(var1.x, this.y, this.z))
               || this.isWindowTo(IsoWorld.instance.CurrentCell.getGridSquare(this.x, var1.y, this.z))) {
    return true;
            }

            if (var1.isWindowTo(IsoWorld.instance.CurrentCell.getGridSquare(var1.x, this.y, this.z))
               || var1.isWindowTo(IsoWorld.instance.CurrentCell.getGridSquare(this.x, var1.y, this.z))) {
    return true;
            }
         }

    return false;
      }
   }

    bool haveDoor() {
      for (int var1 = 0; var1 < this.Objects.size(); var1++) {
         if (this.Objects.get(var1) instanceof IsoDoor) {
    return true;
         }
      }

    return false;
   }

    bool hasDoorOnEdge(IsoDirections var1, bool var2) {
      for (int var3 = 0; var3 < this.SpecialObjects.size(); var3++) {
    IsoDoor var4 = (IsoDoor)Type.tryCastTo(this.SpecialObjects.get(var3), IsoDoor.class);
         if (var4 != nullptr && var4.getSpriteEdge(var2) == var1) {
    return true;
         }

    IsoThumpable var5 = (IsoThumpable)Type.tryCastTo(this.SpecialObjects.get(var3), IsoThumpable.class);
         if (var5 != nullptr && var5.getSpriteEdge(var2) == var1) {
    return true;
         }
      }

    return false;
   }

    bool hasClosedDoorOnEdge(IsoDirections var1) {
    bool var2 = false;

      for (int var3 = 0; var3 < this.SpecialObjects.size(); var3++) {
    IsoDoor var4 = (IsoDoor)Type.tryCastTo(this.SpecialObjects.get(var3), IsoDoor.class);
         if (var4 != nullptr && !var4.IsOpen() && var4.getSpriteEdge(var2) == var1) {
    return true;
         }

    IsoThumpable var5 = (IsoThumpable)Type.tryCastTo(this.SpecialObjects.get(var3), IsoThumpable.class);
         if (var5 != nullptr && !var5.IsOpen() && var5.getSpriteEdge(var2) == var1) {
    return true;
         }
      }

    return false;
   }

    bool hasOpenDoorOnEdge(IsoDirections var1) {
    bool var2 = false;

      for (int var3 = 0; var3 < this.SpecialObjects.size(); var3++) {
    IsoDoor var4 = (IsoDoor)Type.tryCastTo(this.SpecialObjects.get(var3), IsoDoor.class);
         if (var4 != nullptr && var4.IsOpen() && var4.getSpriteEdge(var2) == var1) {
    return true;
         }

    IsoThumpable var5 = (IsoThumpable)Type.tryCastTo(this.SpecialObjects.get(var3), IsoThumpable.class);
         if (var5 != nullptr && var5.IsOpen() && var5.getSpriteEdge(var2) == var1) {
    return true;
         }
      }

    return false;
   }

    bool isDoorTo(IsoGridSquare var1) {
      if (var1 == nullptr || var1 == this) {
    return false;
      } else if (var1.x > this.x && var1.Properties.Is(IsoFlagType.doorW)) {
    return true;
      } else if (this.x > var1.x && this.Properties.Is(IsoFlagType.doorW)) {
    return true;
      } else if (var1.y > this.y && var1.Properties.Is(IsoFlagType.doorN)) {
    return true;
      } else if (this.y > var1.y && this.Properties.Is(IsoFlagType.doorN)) {
    return true;
      } else {
         if (var1.x != this.x && var1.y != this.y) {
            if (this.isDoorTo(IsoWorld.instance.CurrentCell.getGridSquare(var1.x, this.y, this.z))
               || this.isDoorTo(IsoWorld.instance.CurrentCell.getGridSquare(this.x, var1.y, this.z))) {
    return true;
            }

            if (var1.isDoorTo(IsoWorld.instance.CurrentCell.getGridSquare(var1.x, this.y, this.z))
               || var1.isDoorTo(IsoWorld.instance.CurrentCell.getGridSquare(this.x, var1.y, this.z))) {
    return true;
            }
         }

    return false;
      }
   }

    bool isBlockedTo(IsoGridSquare var1) {
      return this.isWallTo(var1) || this.isWindowBlockedTo(var1) || this.isDoorBlockedTo(var1);
   }

    bool isWindowBlockedTo(IsoGridSquare var1) {
      if (var1 == nullptr) {
    return false;
      } else if (var1.x > this.x && var1.hasBlockedWindow(false)) {
    return true;
      } else if (this.x > var1.x && this.hasBlockedWindow(false)) {
    return true;
      } else if (var1.y > this.y && var1.hasBlockedWindow(true)) {
    return true;
      } else if (this.y > var1.y && this.hasBlockedWindow(true)) {
    return true;
      } else {
         if (var1.x != this.x && var1.y != this.y) {
            if (this.isWindowBlockedTo(IsoWorld.instance.CurrentCell.getGridSquare(var1.x, this.y, this.z))
               || this.isWindowBlockedTo(IsoWorld.instance.CurrentCell.getGridSquare(this.x, var1.y, this.z))) {
    return true;
            }

            if (var1.isWindowBlockedTo(IsoWorld.instance.CurrentCell.getGridSquare(var1.x, this.y, this.z))
               || var1.isWindowBlockedTo(IsoWorld.instance.CurrentCell.getGridSquare(this.x, var1.y, this.z))) {
    return true;
            }
         }

    return false;
      }
   }

    bool hasBlockedWindow(bool var1) {
      for (int var2 = 0; var2 < this.Objects.size(); var2++) {
    IsoObject var3 = (IsoObject)this.Objects.get(var2);
         if (dynamic_cast<IsoWindow*>(var3) != nullptr var4 && var4.getNorth() == var1) {
            return !var4.isDestroyed() && !var4.open || var4.isBarricaded();
         }
      }

    return false;
   }

    bool isDoorBlockedTo(IsoGridSquare var1) {
      if (var1 == nullptr) {
    return false;
      } else if (var1.x > this.x && var1.hasBlockedDoor(false)) {
    return true;
      } else if (this.x > var1.x && this.hasBlockedDoor(false)) {
    return true;
      } else if (var1.y > this.y && var1.hasBlockedDoor(true)) {
    return true;
      } else if (this.y > var1.y && this.hasBlockedDoor(true)) {
    return true;
      } else {
         if (var1.x != this.x && var1.y != this.y) {
            if (this.isDoorBlockedTo(IsoWorld.instance.CurrentCell.getGridSquare(var1.x, this.y, this.z))
               || this.isDoorBlockedTo(IsoWorld.instance.CurrentCell.getGridSquare(this.x, var1.y, this.z))) {
    return true;
            }

            if (var1.isDoorBlockedTo(IsoWorld.instance.CurrentCell.getGridSquare(var1.x, this.y, this.z))
               || var1.isDoorBlockedTo(IsoWorld.instance.CurrentCell.getGridSquare(this.x, var1.y, this.z))) {
    return true;
            }
         }

    return false;
      }
   }

    bool hasBlockedDoor(bool var1) {
      for (int var2 = 0; var2 < this.Objects.size(); var2++) {
    IsoObject var3 = (IsoObject)this.Objects.get(var2);
         if (dynamic_cast<IsoDoor*>(var3) != nullptr var4 && var4.getNorth() == var1) {
            return !var4.open || var4.isBarricaded();
         }

         if (dynamic_cast<IsoThumpable*>(var3) != nullptr var5 && var5.isDoor() && var5.getNorth() == var1) {
            return !var5.open || var5.isBarricaded();
         }
      }

    return false;
   }

    IsoCurtain getCurtain(IsoObjectType var1) {
      for (int var2 = 0; var2 < this.getSpecialObjects().size(); var2++) {
    IsoCurtain var3 = (IsoCurtain)Type.tryCastTo(this.getSpecialObjects().get(var2), IsoCurtain.class);
         if (var3 != nullptr && var3.getType() == var1) {
    return var3;
         }
      }

    return nullptr;
   }

    IsoObject getHoppable(bool var1) {
      for (int var2 = 0; var2 < this.Objects.size(); var2++) {
    IsoObject var3 = (IsoObject)this.Objects.get(var2);
    PropertyContainer var4 = var3.getProperties();
         if (var4 != nullptr && var4.Is(var1 ? IsoFlagType.HoppableN : IsoFlagType.HoppableW)) {
    return var3;
         }

         if (var4 != nullptr && var4.Is(var1 ? IsoFlagType.WindowN : IsoFlagType.WindowW)) {
    return var3;
         }
      }

    return nullptr;
   }

    IsoObject getHoppableTo(IsoGridSquare var1) {
      if (var1 != nullptr && var1 != this) {
         if (var1.x < this.x && var1.y == this.y) {
    IsoObject var2 = this.getHoppable(false);
            if (var2 != nullptr) {
    return var2;
            }
         }

         if (var1.x == this.x && var1.y < this.y) {
    IsoObject var5 = this.getHoppable(true);
            if (var5 != nullptr) {
    return var5;
            }
         }

         if (var1.x > this.x && var1.y == this.y) {
    IsoObject var6 = var1.getHoppable(false);
            if (var6 != nullptr) {
    return var6;
            }
         }

         if (var1.x == this.x && var1.y > this.y) {
    IsoObject var7 = var1.getHoppable(true);
            if (var7 != nullptr) {
    return var7;
            }
         }

         if (var1.x != this.x && var1.y != this.y) {
    IsoGridSquare var3 = this.getCell().getGridSquare(this.x, var1.y, this.z);
    IsoGridSquare var4 = this.getCell().getGridSquare(var1.x, this.y, this.z);
    IsoObject var8 = this.getHoppableTo(var3);
            if (var8 != nullptr) {
    return var8;
            }

            var8 = this.getHoppableTo(var4);
            if (var8 != nullptr) {
    return var8;
            }

            var8 = var1.getHoppableTo(var3);
            if (var8 != nullptr) {
    return var8;
            }

            var8 = var1.getHoppableTo(var4);
            if (var8 != nullptr) {
    return var8;
            }
         }

    return nullptr;
      } else {
    return nullptr;
      }
   }

    bool isHoppableTo(IsoGridSquare var1) {
      if (var1 == nullptr) {
    return false;
      } else if (var1.x != this.x && var1.y != this.y) {
    return false;
      } else if (var1.x > this.x && var1.Properties.Is(IsoFlagType.HoppableW)) {
    return true;
      } else if (this.x > var1.x && this.Properties.Is(IsoFlagType.HoppableW)) {
    return true;
      } else {
         return var1.y > this.y && var1.Properties.Is(IsoFlagType.HoppableN) ? true : this.y > var1.y && this.Properties.Is(IsoFlagType.HoppableN);
      }
   }

    void discard() {
      this.hourLastSeen = -32768;
      this.chunk = nullptr;
      this.zone = nullptr;
      this.LightInfluenceB = nullptr;
      this.LightInfluenceG = nullptr;
      this.LightInfluenceR = nullptr;
      this.room = nullptr;
      this.w = nullptr;
      this.nw = nullptr;
      this.sw = nullptr;
      this.s = nullptr;
      this.n = nullptr;
      this.ne = nullptr;
      this.se = nullptr;
      this.e = nullptr;
      this.isoWorldRegion = nullptr;
      this.hasSetIsoWorldRegion = false;
      this.nav[0] = nullptr;
      this.nav[1] = nullptr;
      this.nav[2] = nullptr;
      this.nav[3] = nullptr;
      this.nav[4] = nullptr;
      this.nav[5] = nullptr;
      this.nav[6] = nullptr;
      this.nav[7] = nullptr;

      for (int var1 = 0; var1 < 4; var1++) {
         if (this.lighting[var1] != nullptr) {
            this.lighting[var1].reset();
         }
      }

      this.SolidFloorCached = false;
      this.SolidFloor = false;
      this.CacheIsFree = false;
      this.CachedIsFree = false;
      this.chunk = nullptr;
      this.roomID = -1;
      this.DeferedCharacters.clear();
      this.DeferredCharacterTick = -1;
      this.StaticMovingObjects.clear();
      this.MovingObjects.clear();
      this.Objects.clear();
      this.WorldObjects.clear();
      this.hasTypes.clear();
      this.table = nullptr;
      this.Properties.Clear();
      this.SpecialObjects.clear();
      this.RainDrop = nullptr;
      this.RainSplash = nullptr;
      this.overlayDone = false;
      this.haveRoof = false;
      this.burntOut = false;
      this.trapPositionX = this.trapPositionY = this.trapPositionZ = -1;
      this.haveElectricity = false;
      this.haveSheetRope = false;
      if (this.erosion != nullptr) {
         this.erosion.reset();
      }

      if (this.OcclusionDataCache != nullptr) {
         this.OcclusionDataCache.Reset();
      }

      this.roofHideBuilding = nullptr;
      this.bHasFlies = false;
      isoGridSquareCache.push_back(this);
   }

    static bool validateUser(const std::string& var0, const std::string& var1) {
    URL var2 = std::make_shared<URL>("http://www.projectzomboid.com/scripts/auth.php?username=" + var0 + "&password=" + var1);
    URLConnection var3 = var2.openConnection();
    BufferedReader var4 = std::make_shared<BufferedReader>(std::make_shared<InputStreamReader>(var3.getInputStream()));

    std::string var5;
      while ((var5 = var4.readLine()) != nullptr) {
         if (var5.contains("success")) {
    return true;
         }
      }

    return false;
   }

    float DistTo(int var1, int var2) {
      return IsoUtils.DistanceManhatten(var1 + 0.5F, var2 + 0.5F, this.x, this.y);
   }

    float DistTo(IsoGridSquare var1) {
      return IsoUtils.DistanceManhatten(this.x + 0.5F, this.y + 0.5F, var1.x + 0.5F, var1.y + 0.5F);
   }

    float DistToProper(IsoGridSquare var1) {
      return IsoUtils.DistanceTo(this.x + 0.5F, this.y + 0.5F, var1.x + 0.5F, var1.y + 0.5F);
   }

    float DistTo(IsoMovingObject var1) {
      return IsoUtils.DistanceManhatten(this.x + 0.5F, this.y + 0.5F, var1.getX(), var1.getY());
   }

    float DistToProper(IsoMovingObject var1) {
      return IsoUtils.DistanceTo(this.x + 0.5F, this.y + 0.5F, var1.getX(), var1.getY());
   }

    bool isSafeToSpawn() {
      choices.clear();
      this.isSafeToSpawn(this, 0);
      if (choices.size() > 7) {
         choices.clear();
    return true;
      } else {
         choices.clear();
    return false;
      }
   }

    void isSafeToSpawn(IsoGridSquare var1, int var2) {
      if (var2 <= 5) {
         choices.push_back(var1);
         if (var1.n != nullptr && !choices.contains(var1.n)) {
            this.isSafeToSpawn(var1.n, var2 + 1);
         }

         if (var1.s != nullptr && !choices.contains(var1.s)) {
            this.isSafeToSpawn(var1.s, var2 + 1);
         }

         if (var1.e != nullptr && !choices.contains(var1.e)) {
            this.isSafeToSpawn(var1.e, var2 + 1);
         }

         if (var1.w != nullptr && !choices.contains(var1.w)) {
            this.isSafeToSpawn(var1.w, var2 + 1);
         }
      }
   }

    static bool auth(const std::string& var0, char[] var1) {
      if (var0.length() > 64) {
    return false;
      } else {
    std::string var2 = var1;
         if (var2.length() > 64) {
    return false;
         } else {
            try {
    return validateUser();
            } catch (MalformedURLException var4) {
               Logger.getLogger(IsoGridSquare.class.getName()).log(Level.SEVERE, nullptr, var4);
            } catch (IOException var5) {
               Logger.getLogger(IsoGridSquare.class.getName()).log(Level.SEVERE, nullptr, var5);
            }

    return false;
         }
      }
   }

    void renderAttachedSpritesWithNoWallLighting(IsoObject var1, ColorInfo var2) {
      if (var1.AttachedAnimSprite != nullptr && !var1.AttachedAnimSprite.empty()) {
    bool var3 = false;

         for (int var4 = 0; var4 < var1.AttachedAnimSprite.size(); var4++) {
    IsoSpriteInstance var5 = (IsoSpriteInstance)var1.AttachedAnimSprite.get(var4);
            if (var5.parentSprite != nullptr && var5.parentSprite.Properties.Is(IsoFlagType.NoWallLighting)) {
               var3 = true;
               break;
            }
         }

         if (var3) {
            defColorInfo.r = var2.r;
            defColorInfo.g = var2.g;
            defColorInfo.b = var2.b;
    float var7 = defColorInfo.a;
            if (CircleStencil) {
            }

            for (int var8 = 0; var8 < var1.AttachedAnimSprite.size(); var8++) {
    IsoSpriteInstance var6 = (IsoSpriteInstance)var1.AttachedAnimSprite.get(var8);
               if (var6.parentSprite != nullptr && var6.parentSprite.Properties.Is(IsoFlagType.NoWallLighting)) {
                  defColorInfo.a = var6.alpha;
                  var6.render(var1, this.x, this.y, this.z, var1.dir, var1.offsetX, var1.offsetY + var1.getRenderYOffset() * Core.TileScale, defColorInfo);
                  var6.update();
               }
            }

            defColorInfo.r = 1.0F;
            defColorInfo.g = 1.0F;
            defColorInfo.b = 1.0F;
            defColorInfo.a = var7;
         }
      }
   }

   public void DoCutawayShader(
      IsoObject var1,
      IsoDirections var2,
      boolean var3,
      boolean var4,
      boolean var5,
      boolean var6,
      boolean var7,
      boolean var8,
      boolean var9,
      WallShaperWhole var10
   ) {
    Texture var11 = Texture.getSharedTexture("media/wallcutaways.png");
      if (var11 != nullptr && var11.getID() != -1) {
    bool var12 = var1.sprite.getProperties().Is(IsoFlagType.NoWallLighting);
    int var13 = IsoCamera.frameState.playerIndex;
    ColorInfo var14 = this.lightInfo[var13];
    int var15 = 2 / Core.TileScale;

         try {
    Texture var16 = var1.getCurrentFrameTex();
    float var17 = 0.0F;
    float var18 = var1.getCurrentFrameTex().getOffsetY();
    int var19 = 0;
    int var20 = 226 - var16.getHeight() * var15;
            if (var2 != IsoDirections.NW) {
               var19 = 66 - var16.getWidth() * var15;
            }

            if (var1.sprite.getProperties().Is(IsoFlagType.WallSE)) {
               var19 = 6 - var16.getWidth() * var15;
               var20 = 196 - var16.getHeight() * var15;
            }

            if (var1.sprite.name.contains("fencing_01_11")) {
               var17 = 1.0F;
            } else if (var1.sprite.name.contains("carpentry_02_80")) {
               var17 = 1.0F;
            } else if (var1.sprite.name.contains("spiffos_01_71")) {
               var17 = -24.0F;
            } else if (var1.sprite.name.contains("location_community_medical")) {
    std::string var29 = var1.sprite.name.replaceAll("(.*)_", "");
    int var31 = int.parseInt(var29);
               switch (var31) {
                  case 45:
                  case 46:
                  case 47:
                  case 147:
                  case 148:
                  case 149:
                     var17 = -3.0F;
               }
            } else if (var1.sprite.name.contains("walls_exterior_roofs")) {
    std::string var21 = var1.sprite.name.replaceAll("(.*)_", "");
    int var22 = int.parseInt(var21);
               if (var22 == 4) {
                  var17 = -60.0F;
               } else if (var22 == 17) {
                  var17 = -46.0F;
               } else if (var22 == 28 && !var1.sprite.name.contains("03")) {
                  var17 = -60.0F;
               } else if (var22 == 41) {
                  var17 = -46.0F;
               }
            }

    CircleStencilShader var30 = CircleStencilShader.instance;
            if (var2 == IsoDirections.N || var2 == IsoDirections.NW) {
    short var32 = 700;
    short var23 = 1084;
               if (var4) {
                  var23 = 1212;
                  if (!var5) {
                     var32 = 444;
                  }
               } else if (!var5) {
                  var32 = 828;
               } else {
                  var32 = 956;
               }

    short var24 = 0;
               if (var6) {
                  var24 = 904;
                  if (var1.sprite.name.contains("garage") || var1.sprite.name.contains("industry_trucks")) {
    int var25 = var1.sprite.tileSheetIndex;
                     if (var25 % 8 == 5) {
                        var24 = 1356;
                     } else if (var25 % 8 == 4) {
                        var24 = 1582;
                     } else if (var25 % 8 == 3) {
                        var24 = 1130;
                     }
                  }

                  if (var1.sprite.name.contains("community_church")) {
    int var36 = var1.sprite.tileSheetIndex;
                     if (var36 == 19) {
                        var24 = 1356;
                     } else if (var36 == 18) {
                        var24 = 1130;
                     }
                  }
               } else if (var8) {
                  var24 = 226;
                  if (var1.sprite.name.contains("trailer")) {
    int var37 = var1.sprite.tileSheetIndex;
                     if (var37 == 14 || var37 == 38) {
                        var24 = 678;
                     } else if (var37 == 15 || var37 == 39) {
                        var24 = 452;
                     }
                  }

                  if (var1.sprite.name.contains("sunstarmotel")) {
    int var38 = var1.sprite.tileSheetIndex;
                     if (var38 == 22 || var38 == 18) {
                        var24 = 678;
                     } else if (var38 == 23 || var38 == 19) {
                        var24 = 452;
                     }
                  }
               }

               colu = this.getVertLight(0, var13);
               coll = this.getVertLight(1, var13);
               colu2 = this.getVertLight(4, var13);
               coll2 = this.getVertLight(5, var13);
               if (Core.bDebug && DebugOptions.instance.DebugDraw_SkipWorldShading.getValue()) {
                  coll2 = -1;
                  colu2 = -1;
                  coll = -1;
                  colu = -1;
                  var14 = defColorInfo;
               }

               if (var1.sprite.getProperties().Is(IsoFlagType.WallSE)) {
                  SpriteRenderer.instance.setCutawayTexture(var11, var23 + (int)var17, var24 + (int)var18, 6 - var19, 196 - var20);
               } else {
                  SpriteRenderer.instance.setCutawayTexture(var11, var32 + (int)var17, var24 + (int)var18, 66 - var19, 226 - var20);
               }

               if (var2 == IsoDirections.N) {
                  SpriteRenderer.instance.setExtraWallShaderParams(WallShaderTexRender.All);
               } else {
                  SpriteRenderer.instance.setExtraWallShaderParams(WallShaderTexRender.RightOnly);
               }

               var10.col[0] = colu2;
               var10.col[1] = coll2;
               var10.col[2] = coll;
               var10.col[3] = colu;
               var1.renderWallTileOnly(this.x, this.y, this.z, var12 ? var14 : defColorInfo, var30, var10);
            }

            if (var2 == IsoDirections.W || var2 == IsoDirections.NW) {
    short var33 = 512;
    short var34 = 1084;
               if (var3) {
                  if (!var4) {
                     var33 = 768;
                     var34 = 1212;
                  }
               } else if (!var4) {
                  var33 = 896;
                  var34 = 1212;
               } else {
                  var33 = 256;
               }

    short var35 = 0;
               if (var7) {
                  var35 = 904;
                  if (var1.sprite.name.contains("garage") || var1.sprite.name.contains("industry_trucks")) {
    int var41 = var1.sprite.tileSheetIndex;
                     if (var41 % 8 == 0) {
                        var35 = 1356;
                     } else if (var41 % 8 == 1) {
                        var35 = 1582;
                     } else if (var41 % 8 == 2) {
                        var35 = 1130;
                     }
                  }

                  if (var1.sprite.name.contains("community_church")) {
    int var42 = var1.sprite.tileSheetIndex;
                     if (var42 == 16) {
                        var35 = 1356;
                     } else if (var42 == 17) {
                        var35 = 1130;
                     }
                  }
               } else if (var9) {
                  var35 = 226;
                  if (var1.sprite.name.contains("trailer")) {
    int var39 = var1.sprite.tileSheetIndex;
                     if (var39 == 13 || var39 == 37) {
                        var35 = 678;
                     } else if (var39 == 12 || var39 == 36) {
                        var35 = 452;
                     }
                  }

                  if (var1.sprite.name.contains("sunstarmotel")) {
    int var40 = var1.sprite.tileSheetIndex;
                     if (var40 == 17) {
                        var35 = 678;
                     } else if (var40 == 16) {
                        var35 = 452;
                     }
                  }
               }

               colu = this.getVertLight(0, var13);
               coll = this.getVertLight(3, var13);
               colu2 = this.getVertLight(4, var13);
               coll2 = this.getVertLight(7, var13);
               if (Core.bDebug && DebugOptions.instance.DebugDraw_SkipWorldShading.getValue()) {
                  coll2 = -1;
                  colu2 = -1;
                  coll = -1;
                  colu = -1;
                  var14 = defColorInfo;
               }

               if (var1.sprite.getProperties().Is(IsoFlagType.WallSE)) {
                  SpriteRenderer.instance.setCutawayTexture(var11, var34 + (int)var17, var35 + (int)var18, 6 - var19, 196 - var20);
               } else {
                  SpriteRenderer.instance.setCutawayTexture(var11, var33 + (int)var17, var35 + (int)var18, 66 - var19, 226 - var20);
               }

               if (var2 == IsoDirections.W) {
                  SpriteRenderer.instance.setExtraWallShaderParams(WallShaderTexRender.All);
               } else {
                  SpriteRenderer.instance.setExtraWallShaderParams(WallShaderTexRender.LeftOnly);
               }

               var10.col[0] = coll2;
               var10.col[1] = colu2;
               var10.col[2] = colu;
               var10.col[3] = coll;
               var1.renderWallTileOnly(this.x, this.y, this.z, var12 ? var14 : defColorInfo, var30, var10);
            }
         } finally {
            SpriteRenderer.instance.setExtraWallShaderParams(nullptr);
            SpriteRenderer.instance.clearCutawayTexture();
            SpriteRenderer.instance.clearUseVertColorsArray();
         }

         var1.renderAttachedAndOverlaySprites(this.x, this.y, this.z, var12 ? var14 : defColorInfo, false, !var12, nullptr, var10);
      }
   }

    void DoCutawayShaderSprite(IsoSprite var1, IsoDirections var2, bool var3, bool var4, bool var5) {
    CircleStencilShader var6 = CircleStencilShader.instance;
    WallShaperWhole var7 = WallShaperWhole.instance;
    int var8 = IsoCamera.frameState.playerIndex;
    Texture var9 = Texture.getSharedTexture("media/wallcutaways.png");
      if (var9 != nullptr && var9.getID() != -1) {
    int var10 = 2 / Core.TileScale;

         try {
    Texture var11 = ((IsoDirectionFrame)var1.CurrentAnim.Frames.get((int)var1.def.Frame)).getTexture(var2);
    float var12 = 0.0F;
    float var13 = var11.getOffsetY();
    int var14 = 0;
    int var15 = 226 - var11.getHeight() * var10;
            if (var2 != IsoDirections.NW) {
               var14 = 66 - var11.getWidth() * var10;
            }

            if (var1.getProperties().Is(IsoFlagType.WallSE)) {
               var14 = 6 - var11.getWidth() * var10;
               var15 = 196 - var11.getHeight() * var10;
            }

            if (var1.name.contains("fencing_01_11")) {
               var12 = 1.0F;
            } else if (var1.name.contains("carpentry_02_80")) {
               var12 = 1.0F;
            } else if (var1.name.contains("spiffos_01_71")) {
               var12 = -24.0F;
            } else if (var1.name.contains("location_community_medical")) {
    std::string var21 = var1.name.replaceAll("(.*)_", "");
    int var24 = int.parseInt(var21);
               switch (var24) {
                  case 45:
                  case 46:
                  case 47:
                  case 147:
                  case 148:
                  case 149:
                     var12 = -3.0F;
               }
            } else if (var1.name.contains("walls_exterior_roofs")) {
    std::string var16 = var1.name.replaceAll("(.*)_", "");
    int var17 = int.parseInt(var16);
               if (var17 == 4) {
                  var12 = -60.0F;
               } else if (var17 == 17) {
                  var12 = -46.0F;
               } else if (var17 == 28 && !var1.name.contains("03")) {
                  var12 = -60.0F;
               } else if (var17 == 41) {
                  var12 = -46.0F;
               }
            }

            if (var2 == IsoDirections.N || var2 == IsoDirections.NW) {
    short var22 = 700;
    short var25 = 1084;
               if (var4) {
                  var25 = 1212;
                  if (!var5) {
                     var22 = 444;
                  }
               } else if (!var5) {
                  var22 = 828;
               } else {
                  var22 = 956;
               }

               colu = this.getVertLight(0, var8);
               coll = this.getVertLight(1, var8);
               colu2 = this.getVertLight(4, var8);
               coll2 = this.getVertLight(5, var8);
               if (var1.getProperties().Is(IsoFlagType.WallSE)) {
                  SpriteRenderer.instance.setCutawayTexture(var9, var25 + (int)var12, 0 + (int)var13, 6 - var14, 196 - var15);
               } else {
                  SpriteRenderer.instance.setCutawayTexture(var9, var22 + (int)var12, 0 + (int)var13, 66 - var14, 226 - var15);
               }

               if (var2 == IsoDirections.N) {
                  SpriteRenderer.instance.setExtraWallShaderParams(WallShaderTexRender.All);
               } else {
                  SpriteRenderer.instance.setExtraWallShaderParams(WallShaderTexRender.RightOnly);
               }

               var7.col[0] = colu2;
               var7.col[1] = coll2;
               var7.col[2] = coll;
               var7.col[3] = colu;
               IndieGL.bindShader(
                  var6,
                  var1,
                  var2,
                  var7,
                  (var1x, var2x, var3x) -> var1x.render(
                     nullptr, this.x, this.y, this.z, var2x, WeatherFxMask.offsetX, WeatherFxMask.offsetY, defColorInfo, false, var3x
                  )
               );
            }

            if (var2 == IsoDirections.W || var2 == IsoDirections.NW) {
    short var23 = 512;
    short var26 = 1084;
               if (var3) {
                  if (!var4) {
                     var23 = 768;
                     var26 = 1212;
                  }
               } else if (!var4) {
                  var23 = 896;
                  var26 = 1212;
               } else {
                  var23 = 256;
               }

               colu = this.getVertLight(0, var8);
               coll = this.getVertLight(3, var8);
               colu2 = this.getVertLight(4, var8);
               coll2 = this.getVertLight(7, var8);
               if (var1.getProperties().Is(IsoFlagType.WallSE)) {
                  SpriteRenderer.instance.setCutawayTexture(var9, var26 + (int)var12, 0 + (int)var13, 6 - var14, 196 - var15);
               } else {
                  SpriteRenderer.instance.setCutawayTexture(var9, var23 + (int)var12, 0 + (int)var13, 66 - var14, 226 - var15);
               }

               if (var2 == IsoDirections.W) {
                  SpriteRenderer.instance.setExtraWallShaderParams(WallShaderTexRender.All);
               } else {
                  SpriteRenderer.instance.setExtraWallShaderParams(WallShaderTexRender.LeftOnly);
               }

               var7.col[0] = coll2;
               var7.col[1] = colu2;
               var7.col[2] = colu;
               var7.col[3] = coll;
               IndieGL.bindShader(
                  var6,
                  var1,
                  var2,
                  var7,
                  (var1x, var2x, var3x) -> var1x.render(
                     nullptr, this.x, this.y, this.z, var2x, WeatherFxMask.offsetX, WeatherFxMask.offsetY, defColorInfo, false, var3x
                  )
               );
            }
         } finally {
            SpriteRenderer.instance.setExtraWallShaderParams(nullptr);
            SpriteRenderer.instance.clearCutawayTexture();
            SpriteRenderer.instance.clearUseVertColorsArray();
         }
      }
   }

   public int DoWallLightingNW(
      IsoObject var1, int var2, boolean var3, boolean var4, boolean var5, boolean var6, boolean var7, boolean var8, boolean var9, Shader var10
   ) {
      if (!DebugOptions.instance.Terrain.RenderTiles.IsoGridSquare.Walls.NW.getValue()) {
    return var2;
      } else {
    bool var11 = var3 || var4 || var5;
    IsoDirections var12 = IsoDirections.NW;
    int var13 = IsoCamera.frameState.playerIndex;
         colu = this.getVertLight(0, var13);
         coll = this.getVertLight(3, var13);
         colr = this.getVertLight(1, var13);
         colu2 = this.getVertLight(4, var13);
         coll2 = this.getVertLight(7, var13);
         colr2 = this.getVertLight(5, var13);
         if (DebugOptions.instance.Terrain.RenderTiles.IsoGridSquare.Walls.LightingDebug.getValue()) {
            colu = -65536;
            coll = -16711936;
            colr = -16711681;
            colu2 = -16776961;
            coll2 = -65281;
            colr2 = -256;
         }

    bool var14 = CircleStencil;
         if (this.z != (int)IsoCamera.CamCharacter.z) {
            var14 = false;
         }

    bool var15 = var1.sprite.getType() == IsoObjectType.doorFrN || var1.sprite.getType() == IsoObjectType.doorN;
    bool var16 = var1.sprite.getType() == IsoObjectType.doorFrW || var1.sprite.getType() == IsoObjectType.doorW;
    bool var17 = false;
    bool var18 = false;
    bool var19 = (var15 || var17 || var16 || var17) && var11 || var1.sprite.getProperties().Is(IsoFlagType.NoWallLighting);
         var14 = this.calculateWallAlphaAndCircleStencilCorner(var1, var3, var4, var5, var6, var7, var8, var9, var14, var13, var15, var16, var17, var18);
         if (USE_WALL_SHADER && var14 && var11) {
            this.DoCutawayShader(var1, var12, var3, var4, var5, var6, var7, var8, var9, WallShaperWhole.instance);
            bWallCutawayN = true;
            bWallCutawayW = true;
    return var2;
         } else {
            WallShaperWhole.instance.col[0] = colu2;
            WallShaperWhole.instance.col[1] = colr2;
            WallShaperWhole.instance.col[2] = colr;
            WallShaperWhole.instance.col[3] = colu;
    WallShaperN var20 = WallShaperN.instance;
            var20.col[0] = colu2;
            var20.col[1] = colr2;
            var20.col[2] = colr;
            var20.col[3] = colu;
            var2 = this.performDrawWall(var1, var2, var13, var19, var20, var10);
            WallShaperWhole.instance.col[0] = coll2;
            WallShaperWhole.instance.col[1] = colu2;
            WallShaperWhole.instance.col[2] = colu;
            WallShaperWhole.instance.col[3] = coll;
    WallShaperW var21 = WallShaperW.instance;
            var21.col[0] = coll2;
            var21.col[1] = colu2;
            var21.col[2] = colu;
            var21.col[3] = coll;
            return this.performDrawWall(var1, var2, var13, var19, var21, var10);
         }
      }
   }

    int DoWallLightingN(IsoObject var1, int var2, bool var3, bool var4, bool var5, bool var6, Shader var7) {
      if (!DebugOptions.instance.Terrain.RenderTiles.IsoGridSquare.Walls.N.getValue()) {
    return var2;
      } else {
    bool var8 = !var5;
    bool var9 = !var6;
    IsoObjectType var10 = IsoObjectType.doorFrN;
    IsoObjectType var11 = IsoObjectType.doorN;
    bool var12 = var3 || var4;
    IsoFlagType var13 = IsoFlagType.transparentN;
    IsoFlagType var14 = IsoFlagType.WindowN;
    IsoFlagType var15 = IsoFlagType.HoppableN;
    IsoDirections var16 = IsoDirections.N;
    bool var17 = CircleStencil;
    int var18 = IsoCamera.frameState.playerIndex;
         colu = this.getVertLight(0, var18);
         coll = this.getVertLight(1, var18);
         colu2 = this.getVertLight(4, var18);
         coll2 = this.getVertLight(5, var18);
         if (DebugOptions.instance.Terrain.RenderTiles.IsoGridSquare.Walls.LightingDebug.getValue()) {
            colu = -65536;
            coll = -16711936;
            colu2 = -16776961;
            coll2 = -65281;
         }

    WallShaperWhole var19 = WallShaperWhole.instance;
         var19.col[0] = colu2;
         var19.col[1] = coll2;
         var19.col[2] = coll;
         var19.col[3] = colu;
         return this.performDrawWallSegmentSingle(
            var1, var2, false, var3, false, false, var4, var5, var6, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var19, var7
         );
      }
   }

    int DoWallLightingW(IsoObject var1, int var2, bool var3, bool var4, bool var5, bool var6, Shader var7) {
      if (!DebugOptions.instance.Terrain.RenderTiles.IsoGridSquare.Walls.W.getValue()) {
    return var2;
      } else {
    bool var8 = !var5;
    bool var9 = !var6;
    IsoObjectType var10 = IsoObjectType.doorFrW;
    IsoObjectType var11 = IsoObjectType.doorW;
    bool var12 = var3 || var4;
    IsoFlagType var13 = IsoFlagType.transparentW;
    IsoFlagType var14 = IsoFlagType.WindowW;
    IsoFlagType var15 = IsoFlagType.HoppableW;
    IsoDirections var16 = IsoDirections.W;
    bool var17 = CircleStencil;
    int var18 = IsoCamera.frameState.playerIndex;
         colu = this.getVertLight(0, var18);
         coll = this.getVertLight(3, var18);
         colu2 = this.getVertLight(4, var18);
         coll2 = this.getVertLight(7, var18);
         if (DebugOptions.instance.Terrain.RenderTiles.IsoGridSquare.Walls.LightingDebug.getValue()) {
            colu = -65536;
            coll = -16711936;
            colu2 = -16776961;
            coll2 = -65281;
         }

    WallShaperWhole var19 = WallShaperWhole.instance;
         var19.col[0] = coll2;
         var19.col[1] = colu2;
         var19.col[2] = colu;
         var19.col[3] = coll;
         return this.performDrawWallSegmentSingle(
            var1, var2, var3, var4, var5, var6, false, false, false, var8, var9, var10, var11, var12, var13, var14, var15, var16, var17, var19, var7
         );
      }
   }

   private int performDrawWallSegmentSingle(
      IsoObject var1,
      int var2,
      boolean var3,
      boolean var4,
      boolean var5,
      boolean var6,
      boolean var7,
      boolean var8,
      boolean var9,
      boolean var10,
      boolean var11,
      IsoObjectType var12,
      IsoObjectType var13,
      boolean var14,
      IsoFlagType var15,
      IsoFlagType var16,
      IsoFlagType var17,
      IsoDirections var18,
      boolean var19,
      WallShaperWhole var20,
      Shader var21
   ) {
    int var22 = IsoCamera.frameState.playerIndex;
      if (this.z != (int)IsoCamera.CamCharacter.z) {
         var19 = false;
      }

    bool var23 = var1.sprite.getType() == var12 || var1.sprite.getType() == var13;
    bool var24 = dynamic_cast<IsoWindow*>(var1) != nullptr;
    bool var25 = (var23 || var24) && var14 || var1.sprite.getProperties().Is(IsoFlagType.NoWallLighting);
      var19 = this.calculateWallAlphaAndCircleStencilEdge(var1, var10, var11, var14, var15, var16, var17, var19, var22, var23, var24);
      if (USE_WALL_SHADER && var19 && var14) {
         this.DoCutawayShader(var1, var18, var3, var4, var7, var8, var5, var9, var6, var20);
         bWallCutawayN = bWallCutawayN | var18 == IsoDirections.N;
         bWallCutawayW = bWallCutawayW | var18 == IsoDirections.W;
    return var2;
      } else {
         return this.performDrawWall(var1, var2, var22, var25, var20, var21);
      }
   }

    int performDrawWallOnly(IsoObject var1, int var2, int var3, bool var4, Consumer<TextureDraw> var5, Shader var6) {
      if (var2 == 0 && !var4) {
         var2 = this.getCell().getStencilValue(this.x, this.y, this.z);
      }

      IndieGL.enableAlphaTest();
      IndieGL.glAlphaFunc(516, 0.0F);
      IndieGL.glStencilFunc(519, var2, 127);
      if (!var4) {
         IndieGL.glStencilOp(7680, 7680, 7681);
      }

      if (DebugOptions.instance.Terrain.RenderTiles.IsoGridSquare.Walls.Render.getValue()) {
         var1.renderWallTile(this.x, this.y, this.z, var4 ? lightInfoTemp : defColorInfo, true, !var4, var6, var5);
      }

      var1.setAlpha(var3, 1.0F);
      if (var4) {
         IndieGL.glStencilFunc(519, 1, 255);
         IndieGL.glStencilOp(7680, 7680, 7680);
    return var2;
      } else {
         this.getCell().setStencilValue(this.x, this.y, this.z, var2);
         return var2 + 1;
      }
   }

    int performDrawWall(IsoObject var1, int var2, int var3, bool var4, Consumer<TextureDraw> var5, Shader var6) {
      lightInfoTemp.set(this.lightInfo[var3]);
      if (Core.bDebug && DebugOptions.instance.DebugDraw_SkipWorldShading.getValue()) {
         var1.render(this.x, this.y, this.z, defColorInfo, true, !var4, nullptr);
    return var2;
      } else {
    int var7 = this.performDrawWallOnly(var1, var2, var3, var4, var5, var6);
         if (DebugOptions.instance.Terrain.RenderTiles.IsoGridSquare.Walls.AttachedSprites.getValue()) {
            this.renderAttachedSpritesWithNoWallLighting(var1, lightInfoTemp);
         }

    return var7;
      }
   }

    void calculateWallAlphaCommon(IsoObject var1, bool var2, bool var3, bool var4, int var5, bool var6, bool var7) {
      if (var6 || var7) {
         if (var2) {
            var1.setAlpha(var5, 0.4F);
            var1.setTargetAlpha(var5, 0.4F);
            lightInfoTemp.r = Math.max(0.3F, lightInfoTemp.r);
            lightInfoTemp.g = Math.max(0.3F, lightInfoTemp.g);
            lightInfoTemp.b = Math.max(0.3F, lightInfoTemp.b);
            if (var6 && !var3) {
               var1.setAlpha(var5, 0.0F);
               var1.setTargetAlpha(var5, 0.0F);
            }

            if (var7 && !var4) {
               var1.setAlpha(var5, 0.0F);
               var1.setTargetAlpha(var5, 0.0F);
            }
         }
      }
   }

   private boolean calculateWallAlphaAndCircleStencilEdge(
      IsoObject var1,
      boolean var2,
      boolean var3,
      boolean var4,
      IsoFlagType var5,
      IsoFlagType var6,
      IsoFlagType var7,
      boolean var8,
      int var9,
      boolean var10,
      boolean var11
   ) {
      if (var10 || var11) {
         if (!var1.sprite.getProperties().Is("GarageDoor")) {
            var8 = false;
         }

         this.calculateWallAlphaCommon(var1, var4, !var2, !var3, var9, var10, var11);
      }

      if (var8
         && var1.sprite.getType() == IsoObjectType.wall
         && var1.sprite.getProperties().Is(var5)
         && !var1.getSprite().getProperties().Is(IsoFlagType.exterior)
         && !var1.sprite.getProperties().Is(var6)) {
         var8 = false;
      }

    return var8;
   }

   private boolean calculateWallAlphaAndCircleStencilCorner(
      IsoObject var1,
      boolean var2,
      boolean var3,
      boolean var4,
      boolean var5,
      boolean var6,
      boolean var7,
      boolean var8,
      boolean var9,
      int var10,
      boolean var11,
      boolean var12,
      boolean var13,
      boolean var14
   ) {
      this.calculateWallAlphaCommon(var1, var3 || var4, var5, var7, var10, var11, var13);
      this.calculateWallAlphaCommon(var1, var3 || var2, var6, var8, var10, var12, var14);
      var9 = var9 && !var11 && !var13;
      if (var9
         && var1.sprite.getType() == IsoObjectType.wall
         && (var1.sprite.getProperties().Is(IsoFlagType.transparentN) || var1.sprite.getProperties().Is(IsoFlagType.transparentW))
         && !var1.getSprite().getProperties().Is(IsoFlagType.exterior)
         && !var1.sprite.getProperties().Is(IsoFlagType.WindowN)
         && !var1.sprite.getProperties().Is(IsoFlagType.WindowW)) {
         var9 = false;
      }

    return var9;
   }

    KahluaTable getLuaMovingObjectList() {
    KahluaTable var1 = LuaManager.platform.newTable();
      LuaManager.env.rawset("Objects", var1);

      for (int var2 = 0; var2 < this.MovingObjects.size(); var2++) {
         var1.rawset(var2 + 1, this.MovingObjects.get(var2));
      }

    return var1;
   }

    bool Is(IsoFlagType var1) {
      return this.Properties.Is(var1);
   }

    bool Is(const std::string& var1) {
      return this.Properties.Is(var1);
   }

    bool Has(IsoObjectType var1) {
      return this.hasTypes.isSet(var1);
   }

    void DeleteTileObject(IsoObject var1) {
      this.Objects.remove(var1);
      this.RecalcAllWithNeighbours(true);
   }

    KahluaTable getLuaTileObjectList() {
    KahluaTable var1 = LuaManager.platform.newTable();
      LuaManager.env.rawset("Objects", var1);

      for (int var2 = 0; var2 < this.Objects.size(); var2++) {
         var1.rawset(var2 + 1, this.Objects.get(var2));
      }

    return var1;
   }

    bool HasDoor(bool var1) {
      for (int var2 = 0; var2 < this.SpecialObjects.size(); var2++) {
         if (this.SpecialObjects.get(var2) instanceof IsoDoor && ((IsoDoor)this.SpecialObjects.get(var2)).north == var1) {
    return true;
         }

         if (this.SpecialObjects.get(var2) instanceof IsoThumpable
            && ((IsoThumpable)this.SpecialObjects.get(var2)).isDoor
            && ((IsoThumpable)this.SpecialObjects.get(var2)).north == var1) {
    return true;
         }
      }

    return false;
   }

    bool HasStairs() {
      return this.HasStairsNorth() || this.HasStairsWest();
   }

    bool HasStairsNorth() {
      return this.Has(IsoObjectType.stairsTN) || this.Has(IsoObjectType.stairsMN) || this.Has(IsoObjectType.stairsBN);
   }

    bool HasStairsWest() {
      return this.Has(IsoObjectType.stairsTW) || this.Has(IsoObjectType.stairsMW) || this.Has(IsoObjectType.stairsBW);
   }

    bool HasStairsBelow() {
      if (this.z == 0) {
    return false;
      } else {
    IsoGridSquare var1 = this.getCell().getGridSquare(this.x, this.y, this.z - 1);
         return var1 != nullptr && var1.HasStairs();
      }
   }

    bool HasElevatedFloor() {
      return this.Has(IsoObjectType.stairsTN) || this.Has(IsoObjectType.stairsMN) || this.Has(IsoObjectType.stairsTW) || this.Has(IsoObjectType.stairsMW);
   }

    bool isSameStaircase(int var1, int var2, int var3) {
      if (var3 != this.getZ()) {
    return false;
      } else {
    int var4 = this.getX();
    int var5 = this.getY();
    int var6 = var4;
    int var7 = var5;
         if (this.Has(IsoObjectType.stairsTN)) {
            var7 = var5 + 2;
         } else if (this.Has(IsoObjectType.stairsMN)) {
            var5--;
            var7++;
         } else if (this.Has(IsoObjectType.stairsBN)) {
            var5 -= 2;
         } else if (this.Has(IsoObjectType.stairsTW)) {
            var6 = var4 + 2;
         } else if (this.Has(IsoObjectType.stairsMW)) {
            var4--;
            var6++;
         } else {
            if (!this.Has(IsoObjectType.stairsBW)) {
    return false;
            }

            var4 -= 2;
         }

         if (var1 >= var4 && var2 >= var5 && var1 <= var6 && var2 <= var7) {
    IsoGridSquare var8 = this.getCell().getGridSquare(var1, var2, var3);
            return var8 != nullptr && var8.HasStairs();
         } else {
    return false;
         }
      }
   }

    bool HasSlopedRoof() {
      return this.HasSlopedRoofWest() || this.HasSlopedRoofNorth();
   }

    bool HasSlopedRoofWest() {
      return this.Has(IsoObjectType.WestRoofB) || this.Has(IsoObjectType.WestRoofM) || this.Has(IsoObjectType.WestRoofT);
   }

    bool HasSlopedRoofNorth() {
      return this.Has(IsoObjectType.WestRoofB) || this.Has(IsoObjectType.WestRoofM) || this.Has(IsoObjectType.WestRoofT);
   }

    bool HasTree() {
      return this.hasTree;
   }

    IsoTree getTree() {
      for (int var1 = 0; var1 < this.Objects.size(); var1++) {
    IsoTree var2 = (IsoTree)Type.tryCastTo((IsoObject)this.Objects.get(var1), IsoTree.class);
         if (var2 != nullptr) {
    return var2;
         }
      }

    return nullptr;
   }

    void fudgeShadowsToAlpha(IsoObject var1, Color var2) {
    float var3 = 1.0F - var1.getAlpha();
      if (var2.r < var3) {
         var2.r = var3;
      }

      if (var2.g < var3) {
         var2.g = var3;
      }

      if (var2.b < var3) {
         var2.b = var3;
      }
   }

    bool shouldSave() {
      return !this.Objects.empty();
   }

    void save(ByteBuffer var1, ObjectOutputStream var2) {
      this.save(var1, var2, false);
   }

    void save(ByteBuffer var1, ObjectOutputStream var2, bool var3) {
      this.getErosionData().save(var1);
    BitHeaderWrite var4 = BitHeader.allocWrite(HeaderSize.uint8_t, var1);
    int var5 = this.Objects.size();
      if (this.Objects.size() > 0) {
         var4.addFlags(1);
         if (var5 == 2) {
            var4.addFlags(2);
         } else if (var5 == 3) {
            var4.addFlags(4);
         } else if (var5 >= 4) {
            var4.addFlags(8);
         }

         if (var3) {
            GameWindow.WriteString(var1, "Number of objects (" + var5 + ")");
         }

         if (var5 >= 4) {
            var1.putShort((short)this.Objects.size());
         }

         for (int var6 = 0; var6 < this.Objects.size(); var6++) {
    int var7 = var1.position();
            if (var3) {
               var1.putInt(0);
            }

    uint8_t var8 = 0;
            if (this.SpecialObjects.contains(this.Objects.get(var6))) {
               var8 = (byte)(var8 | 2);
            }

            if (this.WorldObjects.contains(this.Objects.get(var6))) {
               var8 = (byte)(var8 | 4);
            }

            var1.put(var8);
            if (var3) {
               GameWindow.WriteStringUTF(var1, ((IsoObject)this.Objects.get(var6)).getClass().getName());
            }

            ((IsoObject)this.Objects.get(var6)).save(var1, var3);
            if (var3) {
    int var9 = var1.position();
               var1.position(var7);
               var1.putInt(var9 - var7);
               var1.position(var9);
            }
         }

         if (var3) {
            var1.put((byte)67);
            var1.put((byte)82);
            var1.put((byte)80);
            var1.put((byte)83);
         }
      }

      if (this.isOverlayDone()) {
         var4.addFlags(16);
      }

      if (this.haveRoof) {
         var4.addFlags(32);
      }

    BitHeaderWrite var10 = BitHeader.allocWrite(HeaderSize.uint8_t, var1);
    int var11 = 0;

      for (int var12 = 0; var12 < this.StaticMovingObjects.size(); var12++) {
         if (this.StaticMovingObjects.get(var12) instanceof IsoDeadBody) {
            var11++;
         }
      }

      if (var11 > 0) {
         var10.addFlags(1);
         if (var3) {
            GameWindow.WriteString(var1, "Number of bodies");
         }

         var1.putShort((short)var11);

         for (int var13 = 0; var13 < this.StaticMovingObjects.size(); var13++) {
    IsoMovingObject var14 = this.StaticMovingObjects.get(var13);
            if (dynamic_cast<IsoDeadBody*>(var14) != nullptr) {
               if (var3) {
                  GameWindow.WriteStringUTF(var1, var14.getClass().getName());
               }

               var14.save(var1, var3);
            }
         }
      }

      if (this.table != nullptr && !this.table.empty()) {
         var10.addFlags(2);
         this.table.save(var1);
      }

      if (this.burntOut) {
         var10.addFlags(4);
      }

      if (this.getTrapPositionX() > 0) {
         var10.addFlags(8);
         var1.putInt(this.getTrapPositionX());
         var1.putInt(this.getTrapPositionY());
         var1.putInt(this.getTrapPositionZ());
      }

      if (this.haveSheetRope) {
         var10.addFlags(16);
      }

      if (!var10 == 0)) {
         var4.addFlags(64);
         var10.write();
      } else {
         var1.position(var10.getStartPosition());
      }

      var4.write();
      var4.release();
      var10.release();
   }

    static void loadmatrix(boolean[][][] var0, DataInputStream var1) {
   }

    static void savematrix(boolean[][][] var0, DataOutputStream var1) {
      for (int var2 = 0; var2 < 3; var2++) {
         for (int var3 = 0; var3 < 3; var3++) {
            for (int var4 = 0; var4 < 3; var4++) {
               var1.writeBoolean(var0[var2][var3][var4]);
            }
         }
      }
   }

    bool isCommonGrass() {
      if (this.Objects.empty()) {
    return false;
      } else {
    IsoObject var1 = (IsoObject)this.Objects.get(0);
         return var1.sprite.getProperties().Is(IsoFlagType.solidfloor) && ("TileFloorExt_3" == var1.tile) || "TileFloorExt_4" == var1.tile));
      }
   }

    static bool toBoolean(byte[] var0) {
      return var0 != nullptr && var0.length != 0 ? var0[0] != 0 : false;
   }

    void removeCorpse(IsoDeadBody var1, bool var2) {
      if (GameClient.bClient && !var2) {
         try {
            GameClient.instance.checkAddedRemovedItems(var1);
         } catch (Exception var4) {
            GameClient.connection.cancelPacket();
            ExceptionLogger.logException(var4);
         }

         GameClient.sendRemoveCorpseFromMap(var1);
      }

      var1.removeFromWorld();
      var1.removeFromSquare();
      if (!GameServer.bServer) {
         LuaEventManager.triggerEvent("OnContainerUpdate", this);
      }
   }

    IsoDeadBody getDeadBody() {
      for (int var1 = 0; var1 < this.StaticMovingObjects.size(); var1++) {
         if (this.StaticMovingObjects.get(var1) instanceof IsoDeadBody) {
            return (IsoDeadBody)this.StaticMovingObjects.get(var1);
         }
      }

    return nullptr;
   }

   public List<IsoDeadBody> getDeadBodys() {
    std::vector var1 = new std::vector();

      for (int var2 = 0; var2 < this.StaticMovingObjects.size(); var2++) {
         if (this.StaticMovingObjects.get(var2) instanceof IsoDeadBody) {
            var1.push_back((IsoDeadBody)this.StaticMovingObjects.get(var2));
         }
      }

    return var1;
   }

    void addCorpse(IsoDeadBody var1, bool var2) {
      if (GameClient.bClient && !var2) {
    ByteBufferWriter var3 = GameClient.connection.startPacket();
         PacketType.AddCorpseToMap.doPacket(var3);
         var3.putShort(var1.getObjectID());
         var3.putShort(var1.getOnlineID());
         var3.putInt(this.x);
         var3.putInt(this.y);
         var3.putInt(this.z);
         var1.writeToRemoteBuffer(var3);
         PacketType.AddCorpseToMap.send(GameClient.connection);
      }

      if (!this.StaticMovingObjects.contains(var1)) {
         this.StaticMovingObjects.push_back(var1);
      }

      var1.addToWorld();
      this.burntOut = false;
      this.Properties.UnSet(IsoFlagType.burntOut);
   }

    IsoBrokenGlass getBrokenGlass() {
      for (int var1 = 0; var1 < this.SpecialObjects.size(); var1++) {
    IsoObject var2 = this.SpecialObjects.get(var1);
         if (dynamic_cast<IsoBrokenGlass*>(var2) != nullptr) {
            return (IsoBrokenGlass)var2;
         }
      }

    return nullptr;
   }

    IsoBrokenGlass addBrokenGlass() {
      if (!this.isFree(false)) {
         return this.getBrokenGlass();
      } else {
    IsoBrokenGlass var1 = this.getBrokenGlass();
         if (var1 == nullptr) {
            var1 = std::make_shared<IsoBrokenGlass>(this.getCell());
            var1.setSquare(this);
            this.AddSpecialObject(var1);
            if (GameServer.bServer) {
               GameServer.transmitBrokenGlass(this);
            }
         }

    return var1;
      }
   }

    void load(ByteBuffer var1, int var2) {
      this.load(var1, var2, false);
   }

    void load(ByteBuffer var1, int var2, bool var3) {
      this.getErosionData().load(var1, var2);
    BitHeaderRead var4 = BitHeader.allocRead(HeaderSize.uint8_t, var1);
      if (!var4 == 0)) {
         if (var4.hasFlags(1)) {
            if (var3) {
    std::string var5 = GameWindow.ReadStringUTF(var1);
               DebugLog.log(var5);
            }

    short var19 = 1;
            if (var4.hasFlags(2)) {
               var19 = 2;
            } else if (var4.hasFlags(4)) {
               var19 = 3;
            } else if (var4.hasFlags(8)) {
               var19 = var1.getShort();
            }

            for (int var6 = 0; var6 < var19; var6++) {
    int var7 = var1.position();
    int var8 = 0;
               if (var3) {
                  var8 = var1.getInt();
               }

    uint8_t var9 = var1.get();
    bool var10 = (var9 & 2) != 0;
    bool var11 = (var9 & 4) != 0;
    IsoObject var12 = nullptr;
               if (var3) {
    std::string var13 = GameWindow.ReadStringUTF(var1);
                  DebugLog.log(var13);
               }

               var12 = IsoObject.factoryFromFileInput(this.getCell(), var1);
               if (var12 == nullptr) {
                  if (var3) {
    int var32 = var1.position();
                     if (var32 - var7 != var8) {
                        DebugLog.log(
                           "***** Object loaded size " + (var32 - var7) + " != saved size " + var8 + ", reading obj size: " + var19 + ", Object == nullptr"
                        );
                        if (var12.getSprite() != nullptr && var12.getSprite().getName() != nullptr) {
                           DebugLog.log("Obj sprite = " + var12.getSprite().getName());
                        }
                     }
                  }
               } else {
                  var12.square = this;

                  try {
                     var12.load(var1, var2, var3);
                  } catch (Exception var18) {
                     this.debugPrintGridSquare();
                     if (lastLoaded != nullptr) {
                        lastLoaded.debugPrintGridSquare();
                     }

                     throw RuntimeException(var18);
                  }

                  if (var3) {
    int var33 = var1.position();
                     if (var33 - var7 != var8) {
                        DebugLog.log("***** Object loaded size " + (var33 - var7) + " != saved size " + var8 + ", reading obj size: " + var19);
                        if (var12.getSprite() != nullptr && var12.getSprite().getName() != nullptr) {
                           DebugLog.log("Obj sprite = " + var12.getSprite().getName());
                        }
                     }
                  }

                  if (dynamic_cast<IsoWorldInventoryObject*>(var12) != nullptr) {
                     if (((IsoWorldInventoryObject)var12).getItem() == nullptr) {
                        continue;
                     }

    std::string var34 = ((IsoWorldInventoryObject)var12).getItem().getFullType();
    Item var14 = ScriptManager.instance.FindItem(var34);
                     if (var14 != nullptr && var14.getObsolete()) {
                        continue;
                     }

                     std::string[] var15 = var34.split("_");
                     if (((IsoWorldInventoryObject)var12).dropTime > -1.0
                        && SandboxOptions.instance.HoursForWorldItemRemoval.getValue() > 0.0
                        && (
                           SandboxOptions.instance.WorldItemRemovalList.getValue().contains(var15[0])
                                 && !SandboxOptions.instance.ItemRemovalListBlacklistToggle.getValue()
                              || !SandboxOptions.instance.WorldItemRemovalList.getValue().contains(var15[0])
                                 && SandboxOptions.instance.ItemRemovalListBlacklistToggle.getValue()
                        )
                        && !((IsoWorldInventoryObject)var12).isIgnoreRemoveSandbox()
                        && GameTime.instance.getWorldAgeHours()
                           > ((IsoWorldInventoryObject)var12).dropTime + SandboxOptions.instance.HoursForWorldItemRemoval.getValue()) {
                        continue;
                     }
                  }

                  if (!(dynamic_cast<IsoWindow*>(var12) != nullptr)
                     || var12.getSprite() == nullptr
                     || !"walls_special_01_8" == var12.getSprite().getName()) && !"walls_special_01_9" == var12.getSprite().getName())) {
                     this.Objects.push_back(var12);
                     if (var10) {
                        this.SpecialObjects.push_back(var12);
                     }

                     if (var11) {
                        if (Core.bDebug && !(dynamic_cast<IsoWorldInventoryObject*>(var12) != nullptr)) {
                           DebugLog.log(
                              "Bitflags = "
                                 + var9
                                 + ", obj name = "
                                 + var12.getObjectName()
                                 + ", sprite = "
                                 + (var12.getSprite() != nullptr ? var12.getSprite().getName() : "unknown")
                           );
                        }

                        this.WorldObjects.push_back((IsoWorldInventoryObject)var12);
                        var12.square.chunk.recalcHashCodeObjects();
                     }
                  }
               }
            }

            if (var3) {
    uint8_t var21 = var1.get();
    uint8_t var24 = var1.get();
    uint8_t var26 = var1.get();
    uint8_t var29 = var1.get();
               if (var21 != 67 || var24 != 82 || var26 != 80 || var29 != 83) {
                  DebugLog.log("***** Expected CRPS here");
               }
            }
         }

         this.setOverlayDone(var4.hasFlags(16));
         this.haveRoof = var4.hasFlags(32);
         if (var4.hasFlags(64)) {
    BitHeaderRead var20 = BitHeader.allocRead(HeaderSize.uint8_t, var1);
            if (var20.hasFlags(1)) {
               if (var3) {
    std::string var22 = GameWindow.ReadStringUTF(var1);
                  DebugLog.log(var22);
               }

    short var23 = var1.getShort();

               for (int var25 = 0; var25 < var23; var25++) {
    IsoMovingObject var27 = nullptr;
                  if (var3) {
    std::string var30 = GameWindow.ReadStringUTF(var1);
                     DebugLog.log(var30);
                  }

                  try {
                     var27 = (IsoMovingObject)IsoObject.factoryFromFileInput(this.getCell(), var1);
                  } catch (Exception var17) {
                     this.debugPrintGridSquare();
                     if (lastLoaded != nullptr) {
                        lastLoaded.debugPrintGridSquare();
                     }

                     throw RuntimeException(var17);
                  }

                  if (var27 != nullptr) {
                     var27.square = this;
                     var27.current = this;

                     try {
                        var27.load(var1, var2, var3);
                     } catch (Exception var16) {
                        this.debugPrintGridSquare();
                        if (lastLoaded != nullptr) {
                           lastLoaded.debugPrintGridSquare();
                        }

                        throw RuntimeException(var16);
                     }

                     this.StaticMovingObjects.push_back(var27);
                     this.recalcHashCodeObjects();
                  }
               }
            }

            if (var20.hasFlags(2)) {
               if (this.table == nullptr) {
                  this.table = LuaManager.platform.newTable();
               }

               this.table.load(var1, var2);
            }

            this.burntOut = var20.hasFlags(4);
            if (var20.hasFlags(8)) {
               this.setTrapPositionX(var1.getInt());
               this.setTrapPositionY(var1.getInt());
               this.setTrapPositionZ(var1.getInt());
            }

            this.haveSheetRope = var20.hasFlags(16);
            var20.release();
         }
      }

      var4.release();
      lastLoaded = this;
   }

    void debugPrintGridSquare() {
      System.out.println("x=" + this.x + " y=" + this.y + " z=" + this.z);
      System.out.println("objects");

      for (int var1 = 0; var1 < this.Objects.size(); var1++) {
         ((IsoObject)this.Objects.get(var1)).debugPrintout();
      }

      System.out.println("staticmovingobjects");

      for (int var2 = 0; var2 < this.StaticMovingObjects.size(); var2++) {
         ((IsoObject)this.Objects.get(var2)).debugPrintout();
      }
   }

    float scoreAsWaypoint(int var1, int var2) {
    float var3 = 2.0F;
      return var3 - IsoUtils.DistanceManhatten(var1, var2, this.getX(), this.getY()) * 5.0F;
   }

    void InvalidateSpecialObjectPaths() {
   }

    bool isSolid() {
      return this.Properties.Is(IsoFlagType.solid);
   }

    bool isSolidTrans() {
      return this.Properties.Is(IsoFlagType.solidtrans);
   }

    bool isFree(bool var1) {
      if (var1 && this.MovingObjects.size() > 0) {
    return false;
      } else if (this.CachedIsFree) {
         return this.CacheIsFree;
      } else {
         this.CachedIsFree = true;
         this.CacheIsFree = true;
         if (this.Properties.Is(IsoFlagType.solid) || this.Properties.Is(IsoFlagType.solidtrans) || this.Has(IsoObjectType.tree)) {
            this.CacheIsFree = false;
         }

         if (!this.Properties.Is(IsoFlagType.solidfloor)) {
            this.CacheIsFree = false;
         }

         if (this.Has(IsoObjectType.stairsBN) || this.Has(IsoObjectType.stairsMN) || this.Has(IsoObjectType.stairsTN)) {
            this.CacheIsFree = true;
         } else if (this.Has(IsoObjectType.stairsBW) || this.Has(IsoObjectType.stairsMW) || this.Has(IsoObjectType.stairsTW)) {
            this.CacheIsFree = true;
         }

         return this.CacheIsFree;
      }
   }

    bool isFreeOrMidair(bool var1) {
      if (var1 && this.MovingObjects.size() > 0) {
    return false;
      } else {
    bool var2 = true;
         if (this.Properties.Is(IsoFlagType.solid) || this.Properties.Is(IsoFlagType.solidtrans) || this.Has(IsoObjectType.tree)) {
            var2 = false;
         }

         if (this.Has(IsoObjectType.stairsBN) || this.Has(IsoObjectType.stairsMN) || this.Has(IsoObjectType.stairsTN)) {
            var2 = true;
         } else if (this.Has(IsoObjectType.stairsBW) || this.Has(IsoObjectType.stairsMW) || this.Has(IsoObjectType.stairsTW)) {
            var2 = true;
         }

    return var2;
      }
   }

    bool isFreeOrMidair(bool var1, bool var2) {
      if (var1 && this.MovingObjects.size() > 0) {
         if (!var2) {
    return false;
         }

         for (int var3 = 0; var3 < this.MovingObjects.size(); var3++) {
    IsoMovingObject var4 = this.MovingObjects.get(var3);
            if (!(dynamic_cast<IsoDeadBody*>(var4) != nullptr)) {
    return false;
            }
         }
      }

    bool var5 = true;
      if (this.Properties.Is(IsoFlagType.solid) || this.Properties.Is(IsoFlagType.solidtrans) || this.Has(IsoObjectType.tree)) {
         var5 = false;
      }

      if (this.Has(IsoObjectType.stairsBN) || this.Has(IsoObjectType.stairsMN) || this.Has(IsoObjectType.stairsTN)) {
         var5 = true;
      } else if (this.Has(IsoObjectType.stairsBW) || this.Has(IsoObjectType.stairsMW) || this.Has(IsoObjectType.stairsTW)) {
         var5 = true;
      }

    return var5;
   }

    bool connectedWithFloor() {
      if (this.getZ() == 0) {
    return true;
      } else {
    void* var1 = nullptr;
         var1 = this.getCell().getGridSquare(this.getX() - 1, this.getY(), this.getZ());
         if (var1 != nullptr && ((IsoGridSquare)var1).Properties.Is(IsoFlagType.solidfloor)) {
    return true;
         } else {
            var1 = this.getCell().getGridSquare(this.getX() + 1, this.getY(), this.getZ());
            if (var1 != nullptr && ((IsoGridSquare)var1).Properties.Is(IsoFlagType.solidfloor)) {
    return true;
            } else {
               var1 = this.getCell().getGridSquare(this.getX(), this.getY() - 1, this.getZ());
               if (var1 != nullptr && ((IsoGridSquare)var1).Properties.Is(IsoFlagType.solidfloor)) {
    return true;
               } else {
                  var1 = this.getCell().getGridSquare(this.getX(), this.getY() + 1, this.getZ());
                  return var1 != nullptr && ((IsoGridSquare)var1).Properties.Is(IsoFlagType.solidfloor);
               }
            }
         }
      }
   }

    bool hasFloor(bool var1) {
      if (this.Properties.Is(IsoFlagType.solidfloor)) {
    return true;
      } else {
    void* var2 = nullptr;
         if (var1) {
            var2 = this.getCell().getGridSquare(this.getX(), this.getY() - 1, this.getZ());
         } else {
            var2 = this.getCell().getGridSquare(this.getX() - 1, this.getY(), this.getZ());
         }

         return var2 != nullptr && ((IsoGridSquare)var2).Properties.Is(IsoFlagType.solidfloor);
      }
   }

    bool isNotBlocked(bool var1) {
      if (!this.CachedIsFree) {
         this.CacheIsFree = true;
         this.CachedIsFree = true;
         if (this.Properties.Is(IsoFlagType.solid) || this.Properties.Is(IsoFlagType.solidtrans)) {
            this.CacheIsFree = false;
         }

         if (!this.Properties.Is(IsoFlagType.solidfloor)) {
            this.CacheIsFree = false;
         }
      } else if (!this.CacheIsFree) {
    return false;
      }

      return !var1 || this.MovingObjects.size() <= 0;
   }

    IsoObject getDoor(bool var1) {
      for (int var2 = 0; var2 < this.SpecialObjects.size(); var2++) {
    IsoObject var3 = this.SpecialObjects.get(var2);
         if (dynamic_cast<IsoThumpable*>(var3) != nullptr var4 && var4.isDoor() && var1 == var4.north) {
    return var4;
         }

         if (dynamic_cast<IsoDoor*>(var3) != nullptr var5 && var1 == var5.north) {
    return var5;
         }
      }

    return nullptr;
   }

    IsoDoor getIsoDoor() {
      for (int var1 = 0; var1 < this.SpecialObjects.size(); var1++) {
    IsoObject var2 = this.SpecialObjects.get(var1);
         if (dynamic_cast<IsoDoor*>(var2) != nullptr) {
            return (IsoDoor)var2;
         }
      }

    return nullptr;
   }

    IsoObject getDoorTo(IsoGridSquare var1) {
      if (var1 != nullptr && var1 != this) {
    IsoObject var2 = nullptr;
         if (var1.x < this.x) {
            var2 = this.getDoor(false);
            if (var2 != nullptr) {
    return var2;
            }
         }

         if (var1.y < this.y) {
            var2 = this.getDoor(true);
            if (var2 != nullptr) {
    return var2;
            }
         }

         if (var1.x > this.x) {
            var2 = var1.getDoor(false);
            if (var2 != nullptr) {
    return var2;
            }
         }

         if (var1.y > this.y) {
            var2 = var1.getDoor(true);
            if (var2 != nullptr) {
    return var2;
            }
         }

         if (var1.x != this.x && var1.y != this.y) {
    IsoGridSquare var3 = this.getCell().getGridSquare(this.x, var1.y, this.z);
    IsoGridSquare var4 = this.getCell().getGridSquare(var1.x, this.y, this.z);
            var2 = this.getDoorTo(var3);
            if (var2 != nullptr) {
    return var2;
            }

            var2 = this.getDoorTo(var4);
            if (var2 != nullptr) {
    return var2;
            }

            var2 = var1.getDoorTo(var3);
            if (var2 != nullptr) {
    return var2;
            }

            var2 = var1.getDoorTo(var4);
            if (var2 != nullptr) {
    return var2;
            }
         }

    return nullptr;
      } else {
    return nullptr;
      }
   }

    IsoWindow getWindow(bool var1) {
      for (int var2 = 0; var2 < this.SpecialObjects.size(); var2++) {
    IsoObject var3 = this.SpecialObjects.get(var2);
         if (dynamic_cast<IsoWindow*>(var3) != nullptr var4 && var1 == var4.north) {
    return var4;
         }
      }

    return nullptr;
   }

    IsoWindow getWindow() {
      for (int var1 = 0; var1 < this.SpecialObjects.size(); var1++) {
    IsoObject var2 = this.SpecialObjects.get(var1);
         if (dynamic_cast<IsoWindow*>(var2) != nullptr) {
            return (IsoWindow)var2;
         }
      }

    return nullptr;
   }

    IsoWindow getWindowTo(IsoGridSquare var1) {
      if (var1 != nullptr && var1 != this) {
    IsoWindow var2 = nullptr;
         if (var1.x < this.x) {
            var2 = this.getWindow(false);
            if (var2 != nullptr) {
    return var2;
            }
         }

         if (var1.y < this.y) {
            var2 = this.getWindow(true);
            if (var2 != nullptr) {
    return var2;
            }
         }

         if (var1.x > this.x) {
            var2 = var1.getWindow(false);
            if (var2 != nullptr) {
    return var2;
            }
         }

         if (var1.y > this.y) {
            var2 = var1.getWindow(true);
            if (var2 != nullptr) {
    return var2;
            }
         }

         if (var1.x != this.x && var1.y != this.y) {
    IsoGridSquare var3 = this.getCell().getGridSquare(this.x, var1.y, this.z);
    IsoGridSquare var4 = this.getCell().getGridSquare(var1.x, this.y, this.z);
            var2 = this.getWindowTo(var3);
            if (var2 != nullptr) {
    return var2;
            }

            var2 = this.getWindowTo(var4);
            if (var2 != nullptr) {
    return var2;
            }

            var2 = var1.getWindowTo(var3);
            if (var2 != nullptr) {
    return var2;
            }

            var2 = var1.getWindowTo(var4);
            if (var2 != nullptr) {
    return var2;
            }
         }

    return nullptr;
      } else {
    return nullptr;
      }
   }

    bool isAdjacentToWindow() {
      if (this.getWindow() != nullptr) {
    return true;
      } else if (this.hasWindowFrame()) {
    return true;
      } else if (this.getThumpableWindow(false) == nullptr && this.getThumpableWindow(true) == nullptr) {
    IsoGridSquare var1 = this.nav[IsoDirections.S.index()];
         if (var1 == nullptr || var1.getWindow(true) == nullptr && var1.getWindowFrame(true) == nullptr && var1.getThumpableWindow(true) == nullptr) {
    IsoGridSquare var2 = this.nav[IsoDirections.E.index()];
            return var2 != nullptr && (var2.getWindow(false) != nullptr || var2.getWindowFrame(false) != nullptr || var2.getThumpableWindow(false) != nullptr);
         } else {
    return true;
         }
      } else {
    return true;
      }
   }

    IsoThumpable getThumpableWindow(bool var1) {
      for (int var2 = 0; var2 < this.SpecialObjects.size(); var2++) {
    IsoObject var3 = this.SpecialObjects.get(var2);
         if (dynamic_cast<IsoThumpable*>(var3) != nullptr var4 && var4.isWindow() && var1 == var4.north) {
    return var4;
         }
      }

    return nullptr;
   }

    IsoThumpable getWindowThumpableTo(IsoGridSquare var1) {
      if (var1 != nullptr && var1 != this) {
    IsoThumpable var2 = nullptr;
         if (var1.x < this.x) {
            var2 = this.getThumpableWindow(false);
            if (var2 != nullptr) {
    return var2;
            }
         }

         if (var1.y < this.y) {
            var2 = this.getThumpableWindow(true);
            if (var2 != nullptr) {
    return var2;
            }
         }

         if (var1.x > this.x) {
            var2 = var1.getThumpableWindow(false);
            if (var2 != nullptr) {
    return var2;
            }
         }

         if (var1.y > this.y) {
            var2 = var1.getThumpableWindow(true);
            if (var2 != nullptr) {
    return var2;
            }
         }

         if (var1.x != this.x && var1.y != this.y) {
    IsoGridSquare var3 = this.getCell().getGridSquare(this.x, var1.y, this.z);
    IsoGridSquare var4 = this.getCell().getGridSquare(var1.x, this.y, this.z);
            var2 = this.getWindowThumpableTo(var3);
            if (var2 != nullptr) {
    return var2;
            }

            var2 = this.getWindowThumpableTo(var4);
            if (var2 != nullptr) {
    return var2;
            }

            var2 = var1.getWindowThumpableTo(var3);
            if (var2 != nullptr) {
    return var2;
            }

            var2 = var1.getWindowThumpableTo(var4);
            if (var2 != nullptr) {
    return var2;
            }
         }

    return nullptr;
      } else {
    return nullptr;
      }
   }

    IsoThumpable getHoppableThumpable(bool var1) {
      for (int var2 = 0; var2 < this.SpecialObjects.size(); var2++) {
    IsoObject var3 = this.SpecialObjects.get(var2);
         if (dynamic_cast<IsoThumpable*>(var3) != nullptr var4 && var4.isHoppable() && var1 == var4.north) {
    return var4;
         }
      }

    return nullptr;
   }

    IsoThumpable getHoppableThumpableTo(IsoGridSquare var1) {
      if (var1 != nullptr && var1 != this) {
    IsoThumpable var2 = nullptr;
         if (var1.x < this.x) {
            var2 = this.getHoppableThumpable(false);
            if (var2 != nullptr) {
    return var2;
            }
         }

         if (var1.y < this.y) {
            var2 = this.getHoppableThumpable(true);
            if (var2 != nullptr) {
    return var2;
            }
         }

         if (var1.x > this.x) {
            var2 = var1.getHoppableThumpable(false);
            if (var2 != nullptr) {
    return var2;
            }
         }

         if (var1.y > this.y) {
            var2 = var1.getHoppableThumpable(true);
            if (var2 != nullptr) {
    return var2;
            }
         }

         if (var1.x != this.x && var1.y != this.y) {
    IsoGridSquare var3 = this.getCell().getGridSquare(this.x, var1.y, this.z);
    IsoGridSquare var4 = this.getCell().getGridSquare(var1.x, this.y, this.z);
            var2 = this.getHoppableThumpableTo(var3);
            if (var2 != nullptr) {
    return var2;
            }

            var2 = this.getHoppableThumpableTo(var4);
            if (var2 != nullptr) {
    return var2;
            }

            var2 = var1.getHoppableThumpableTo(var3);
            if (var2 != nullptr) {
    return var2;
            }

            var2 = var1.getHoppableThumpableTo(var4);
            if (var2 != nullptr) {
    return var2;
            }
         }

    return nullptr;
      } else {
    return nullptr;
      }
   }

    IsoObject getWallHoppable(bool var1) {
      for (int var2 = 0; var2 < this.Objects.size(); var2++) {
         if (((IsoObject)this.Objects.get(var2)).isHoppable() && var1 == ((IsoObject)this.Objects.get(var2)).isNorthHoppable()) {
            return (IsoObject)this.Objects.get(var2);
         }
      }

    return nullptr;
   }

    IsoObject getWallHoppableTo(IsoGridSquare var1) {
      if (var1 != nullptr && var1 != this) {
    IsoObject var2 = nullptr;
         if (var1.x < this.x) {
            var2 = this.getWallHoppable(false);
            if (var2 != nullptr) {
    return var2;
            }
         }

         if (var1.y < this.y) {
            var2 = this.getWallHoppable(true);
            if (var2 != nullptr) {
    return var2;
            }
         }

         if (var1.x > this.x) {
            var2 = var1.getWallHoppable(false);
            if (var2 != nullptr) {
    return var2;
            }
         }

         if (var1.y > this.y) {
            var2 = var1.getWallHoppable(true);
            if (var2 != nullptr) {
    return var2;
            }
         }

         if (var1.x != this.x && var1.y != this.y) {
    IsoGridSquare var3 = this.getCell().getGridSquare(this.x, var1.y, this.z);
    IsoGridSquare var4 = this.getCell().getGridSquare(var1.x, this.y, this.z);
            var2 = this.getWallHoppableTo(var3);
            if (var2 != nullptr) {
    return var2;
            }

            var2 = this.getWallHoppableTo(var4);
            if (var2 != nullptr) {
    return var2;
            }

            var2 = var1.getWallHoppableTo(var3);
            if (var2 != nullptr) {
    return var2;
            }

            var2 = var1.getWallHoppableTo(var4);
            if (var2 != nullptr) {
    return var2;
            }
         }

    return nullptr;
      } else {
    return nullptr;
      }
   }

    IsoObject getBedTo(IsoGridSquare var1) {
    std::vector var2 = nullptr;
      if (var1.y >= this.y && var1.x >= this.x) {
         var2 = var1.SpecialObjects;
      } else {
         var2 = this.SpecialObjects;
      }

      for (int var3 = 0; var3 < var2.size(); var3++) {
    IsoObject var4 = (IsoObject)var2.get(var3);
         if (var4.getProperties().Is(IsoFlagType.bed)) {
    return var4;
         }
      }

    return nullptr;
   }

    IsoObject getWindowFrame(bool var1) {
      for (int var2 = 0; var2 < this.Objects.size(); var2++) {
    IsoObject var3 = (IsoObject)this.Objects.get(var2);
         if (!(dynamic_cast<IsoWorldInventoryObject*>(var3) != nullptr) && IsoWindowFrame.isWindowFrame(var3, var1)) {
    return var3;
         }
      }

    return nullptr;
   }

    IsoObject getWindowFrameTo(IsoGridSquare var1) {
      if (var1 != nullptr && var1 != this) {
    IsoObject var2 = nullptr;
         if (var1.x < this.x) {
            var2 = this.getWindowFrame(false);
            if (var2 != nullptr) {
    return var2;
            }
         }

         if (var1.y < this.y) {
            var2 = this.getWindowFrame(true);
            if (var2 != nullptr) {
    return var2;
            }
         }

         if (var1.x > this.x) {
            var2 = var1.getWindowFrame(false);
            if (var2 != nullptr) {
    return var2;
            }
         }

         if (var1.y > this.y) {
            var2 = var1.getWindowFrame(true);
            if (var2 != nullptr) {
    return var2;
            }
         }

         if (var1.x != this.x && var1.y != this.y) {
    IsoGridSquare var3 = this.getCell().getGridSquare(this.x, var1.y, this.z);
    IsoGridSquare var4 = this.getCell().getGridSquare(var1.x, this.y, this.z);
            var2 = this.getWindowFrameTo(var3);
            if (var2 != nullptr) {
    return var2;
            }

            var2 = this.getWindowFrameTo(var4);
            if (var2 != nullptr) {
    return var2;
            }

            var2 = var1.getWindowFrameTo(var3);
            if (var2 != nullptr) {
    return var2;
            }

            var2 = var1.getWindowFrameTo(var4);
            if (var2 != nullptr) {
    return var2;
            }
         }

    return nullptr;
      } else {
    return nullptr;
      }
   }

    bool hasWindowFrame() {
      for (int var1 = 0; var1 < this.Objects.size(); var1++) {
    IsoObject var2 = (IsoObject)this.Objects.get(var1);
         if (!(dynamic_cast<IsoWorldInventoryObject*>(var2) != nullptr) && IsoWindowFrame.isWindowFrame(var2)) {
    return true;
         }
      }

    return false;
   }

    bool hasWindowOrWindowFrame() {
      for (int var1 = 0; var1 < this.Objects.size(); var1++) {
    IsoObject var2 = (IsoObject)this.Objects.get(var1);
         if (!(dynamic_cast<IsoWorldInventoryObject*>(var2) != nullptr) && (this.isWindowOrWindowFrame(var2, true) || this.isWindowOrWindowFrame(var2, false))) {
    return true;
         }
      }

    return false;
   }

    IsoObject getSpecialWall(bool var1) {
      for (int var2 = this.SpecialObjects.size() - 1; var2 >= 0; var2--) {
    IsoObject var3 = this.SpecialObjects.get(var2);
         if (dynamic_cast<IsoThumpable*>(var3) != nullptr var4) {
            if (var4.isStairs() || !var4.isThumpable() && !var4.isWindow() && !var4.isDoor() || var4.isDoor() && var4.open || var4.isBlockAllTheSquare()) {
               continue;
            }

            if (var1 == var4.north && !var4.isCorner()) {
    return var4;
            }
         }

         if (dynamic_cast<IsoWindow*>(var3) != nullptr var6 && var1 == var6.north) {
    return var6;
         }

         if (dynamic_cast<IsoDoor*>(var3) != nullptr var7 && var1 == var7.north && !var7.open) {
    return var7;
         }
      }

      if ((!var1 || this.Is(IsoFlagType.WindowN)) && (var1 || this.Is(IsoFlagType.WindowW))) {
    IsoObject var5 = this.getWindowFrame(var1);
         return var5 != nullptr ? var5 : nullptr;
      } else {
    return nullptr;
      }
   }

    IsoObject getSheetRope() {
      for (int var1 = 0; var1 < this.getObjects().size(); var1++) {
    IsoObject var2 = (IsoObject)this.getObjects().get(var1);
         if (var2.sheetRope) {
    return var2;
         }
      }

    return nullptr;
   }

    bool damageSpriteSheetRopeFromBottom(IsoPlayer var1, bool var2) {
    IsoGridSquare var4 = this;
    IsoFlagType var3;
      if (var2) {
         if (this.Is(IsoFlagType.climbSheetN)) {
            var3 = IsoFlagType.climbSheetN;
         } else {
            if (!this.Is(IsoFlagType.climbSheetS)) {
    return false;
            }

            var3 = IsoFlagType.climbSheetS;
         }
      } else if (this.Is(IsoFlagType.climbSheetW)) {
         var3 = IsoFlagType.climbSheetW;
      } else {
         if (!this.Is(IsoFlagType.climbSheetE)) {
    return false;
         }

         var3 = IsoFlagType.climbSheetE;
      }

      while (var4 != nullptr) {
         for (int var5 = 0; var5 < var4.getObjects().size(); var5++) {
    IsoObject var6 = (IsoObject)var4.getObjects().get(var5);
            if (var6.getProperties() != nullptr && var6.getProperties().Is(var3)) {
    int var7 = int.parseInt(var6.getSprite().getName().split("_")[2]);
               if (var7 > 14) {
    return false;
               }

    std::string var8 = var6.getSprite().getName().split("_")[0] + "_" + var6.getSprite().getName().split("_")[1];
               var7 += 40;
               var6.setSprite(IsoSpriteManager.instance.getSprite(var8 + "_" + var7));
               var6.transmitUpdatedSprite();
               break;
            }
         }

         if (var4.getZ() == 7) {
            break;
         }

         var4 = var4.getCell().getGridSquare(var4.getX(), var4.getY(), var4.getZ() + 1);
      }

    return true;
   }

    bool removeSheetRopeFromBottom(IsoPlayer var1, bool var2) {
    IsoGridSquare var6 = this;
    IsoFlagType var3;
    IsoFlagType var4;
      if (var2) {
         if (this.Is(IsoFlagType.climbSheetN)) {
            var3 = IsoFlagType.climbSheetTopN;
            var4 = IsoFlagType.climbSheetN;
         } else {
            if (!this.Is(IsoFlagType.climbSheetS)) {
    return false;
            }

            var3 = IsoFlagType.climbSheetTopS;
            var4 = IsoFlagType.climbSheetS;
    std::string var5 = "crafted_01_4";

            for (int var7 = 0; var7 < var6.getObjects().size(); var7++) {
    IsoObject var8 = (IsoObject)var6.getObjects().get(var7);
               if (var8.sprite != nullptr && var8.sprite.getName() != nullptr && var8.sprite.getName() == var5)) {
                  var6.transmitRemoveItemFromSquare(var8);
                  break;
               }
            }
         }
      } else if (this.Is(IsoFlagType.climbSheetW)) {
         var3 = IsoFlagType.climbSheetTopW;
         var4 = IsoFlagType.climbSheetW;
      } else {
         if (!this.Is(IsoFlagType.climbSheetE)) {
    return false;
         }

         var3 = IsoFlagType.climbSheetTopE;
         var4 = IsoFlagType.climbSheetE;
    std::string var12 = "crafted_01_3";

         for (int var14 = 0; var14 < var6.getObjects().size(); var14++) {
    IsoObject var16 = (IsoObject)var6.getObjects().get(var14);
            if (var16.sprite != nullptr && var16.sprite.getName() != nullptr && var16.sprite.getName() == var12)) {
               var6.transmitRemoveItemFromSquare(var16);
               break;
            }
         }
      }

    bool var15 = false;

    IsoGridSquare var17;
      for (var17 = nullptr; var6 != nullptr; var15 = false) {
         for (int var9 = 0; var9 < var6.getObjects().size(); var9++) {
    IsoObject var10 = (IsoObject)var6.getObjects().get(var9);
            if (var10.getProperties() != nullptr && (var10.getProperties().Is(var3) || var10.getProperties().Is(var4))) {
               var17 = var6;
               var15 = true;
               var6.transmitRemoveItemFromSquare(var10);
               if (GameServer.bServer) {
                  if (var1 != nullptr) {
                     var1.sendObjectChange("addItemOfType", new Object[]{"type", var10.getName()});
                  }
               } else if (var1 != nullptr) {
                  var1.getInventory().AddItem(var10.getName());
               }
               break;
            }
         }

         if (var6.getZ() == 7) {
            break;
         }

         var6 = var6.getCell().getGridSquare(var6.getX(), var6.getY(), var6.getZ() + 1);
      }

      if (!var15) {
         var6 = var17.getCell().getGridSquare(var17.getX(), var17.getY(), var17.getZ());
    IsoGridSquare var18 = var2 ? var6.nav[IsoDirections.S.index()] : var6.nav[IsoDirections.E.index()];
         if (var18 == nullptr) {
    return true;
         }

         for (int var19 = 0; var19 < var18.getObjects().size(); var19++) {
    IsoObject var11 = (IsoObject)var18.getObjects().get(var19);
            if (var11.getProperties() != nullptr && (var11.getProperties().Is(var3) || var11.getProperties().Is(var4))) {
               var18.transmitRemoveItemFromSquare(var11);
               break;
            }
         }
      }

    return true;
   }

    IsoObject getSpecialSolid() {
      for (int var1 = 0; var1 < this.SpecialObjects.size(); var1++) {
    IsoObject var2 = this.SpecialObjects.get(var1);
         if (dynamic_cast<IsoThumpable*>(var2) != nullptr var3 && !var3.isStairs() && var3.isThumpable() && var3.isBlockAllTheSquare()) {
            if (var3.getProperties().Is(IsoFlagType.solidtrans) && this.isAdjacentToWindow()) {
    return nullptr;
            }

    return var3;
         }
      }

      for (int var4 = 0; var4 < this.Objects.size(); var4++) {
    IsoObject var5 = (IsoObject)this.Objects.get(var4);
         if (var5.isMovedThumpable()) {
            if (this.isAdjacentToWindow()) {
    return nullptr;
            }

    return var5;
         }
      }

    return nullptr;
   }

    IsoObject testCollideSpecialObjects(IsoGridSquare var1) {
      if (var1 == nullptr || var1 == this) {
    return nullptr;
      } else if (var1.x < this.x && var1.y == this.y) {
         if (var1.z == this.z && this.Has(IsoObjectType.stairsTW)) {
    return nullptr;
         } else {
    IsoObject var37 = this.getSpecialWall(false);
            if (var37 != nullptr) {
    return var37;
            } else if (this.isBlockedTo(var1)) {
    return nullptr;
            } else {
               var37 = var1.getSpecialSolid();
               return var37 != nullptr ? var37 : nullptr;
            }
         }
      } else if (var1.x == this.x && var1.y < this.y) {
         if (var1.z == this.z && this.Has(IsoObjectType.stairsTN)) {
    return nullptr;
         } else {
    IsoObject var35 = this.getSpecialWall(true);
            if (var35 != nullptr) {
    return var35;
            } else if (this.isBlockedTo(var1)) {
    return nullptr;
            } else {
               var35 = var1.getSpecialSolid();
               return var35 != nullptr ? var35 : nullptr;
            }
         }
      } else if (var1.x > this.x && var1.y == this.y) {
    IsoObject var33 = var1.getSpecialWall(false);
         if (var33 != nullptr) {
    return var33;
         } else if (this.isBlockedTo(var1)) {
    return nullptr;
         } else {
            var33 = var1.getSpecialSolid();
            return var33 != nullptr ? var33 : nullptr;
         }
      } else if (var1.x == this.x && var1.y > this.y) {
    IsoObject var31 = var1.getSpecialWall(true);
         if (var31 != nullptr) {
    return var31;
         } else if (this.isBlockedTo(var1)) {
    return nullptr;
         } else {
            var31 = var1.getSpecialSolid();
            return var31 != nullptr ? var31 : nullptr;
         }
      } else if (var1.x < this.x && var1.y < this.y) {
    IsoObject var24 = this.getSpecialWall(true);
         if (var24 != nullptr) {
    return var24;
         } else {
            var24 = this.getSpecialWall(false);
            if (var24 != nullptr) {
    return var24;
            } else {
    IsoGridSquare var41 = this.getCell().getGridSquare(this.x, this.y - 1, this.z);
               if (var41 != nullptr && !this.isBlockedTo(var41)) {
                  var24 = var41.getSpecialSolid();
                  if (var24 != nullptr) {
    return var24;
                  }

                  var24 = var41.getSpecialWall(false);
                  if (var24 != nullptr) {
    return var24;
                  }
               }

    IsoGridSquare var44 = this.getCell().getGridSquare(this.x - 1, this.y, this.z);
               if (var44 != nullptr && !this.isBlockedTo(var44)) {
                  var24 = var44.getSpecialSolid();
                  if (var24 != nullptr) {
    return var24;
                  }

                  var24 = var44.getSpecialWall(true);
                  if (var24 != nullptr) {
    return var24;
                  }
               }

               if (var41 == nullptr || this.isBlockedTo(var41) || var44 == nullptr || this.isBlockedTo(var44)) {
    return nullptr;
               } else if (!var41.isBlockedTo(var1) && !var44.isBlockedTo(var1)) {
                  var24 = var1.getSpecialSolid();
                  return var24 != nullptr ? var24 : nullptr;
               } else {
    return nullptr;
               }
            }
         }
      } else if (var1.x > this.x && var1.y < this.y) {
    IsoObject var17 = this.getSpecialWall(true);
         if (var17 != nullptr) {
    return var17;
         } else {
    IsoGridSquare var40 = this.getCell().getGridSquare(this.x, this.y - 1, this.z);
            if (var40 != nullptr && !this.isBlockedTo(var40)) {
               var17 = var40.getSpecialSolid();
               if (var17 != nullptr) {
    return var17;
               }
            }

    IsoGridSquare var43 = this.getCell().getGridSquare(this.x + 1, this.y, this.z);
            if (var43 != nullptr) {
               var17 = var43.getSpecialWall(false);
               if (var17 != nullptr) {
    return var17;
               }

               if (!this.isBlockedTo(var43)) {
                  var17 = var43.getSpecialSolid();
                  if (var17 != nullptr) {
    return var17;
                  }

                  var17 = var43.getSpecialWall(true);
                  if (var17 != nullptr) {
    return var17;
                  }
               }
            }

            if (var40 != nullptr && !this.isBlockedTo(var40) && var43 != nullptr && !this.isBlockedTo(var43)) {
               var17 = var1.getSpecialWall(false);
               if (var17 != nullptr) {
    return var17;
               } else if (!var40.isBlockedTo(var1) && !var43.isBlockedTo(var1)) {
                  var17 = var1.getSpecialSolid();
                  return var17 != nullptr ? var17 : nullptr;
               } else {
    return nullptr;
               }
            } else {
    return nullptr;
            }
         }
      } else if (var1.x > this.x && var1.y > this.y) {
    IsoGridSquare var39 = this.getCell().getGridSquare(this.x, this.y + 1, this.z);
         if (var39 != nullptr) {
    IsoObject var10 = var39.getSpecialWall(true);
            if (var10 != nullptr) {
    return var10;
            }

            if (!this.isBlockedTo(var39)) {
               var10 = var39.getSpecialSolid();
               if (var10 != nullptr) {
    return var10;
               }
            }
         }

    IsoGridSquare var42 = this.getCell().getGridSquare(this.x + 1, this.y, this.z);
         if (var42 != nullptr) {
    IsoObject var12 = var42.getSpecialWall(false);
            if (var12 != nullptr) {
    return var12;
            }

            if (!this.isBlockedTo(var42)) {
               var12 = var42.getSpecialSolid();
               if (var12 != nullptr) {
    return var12;
               }
            }
         }

         if (var39 != nullptr && !this.isBlockedTo(var39) && var42 != nullptr && !this.isBlockedTo(var42)) {
    IsoObject var14 = var1.getSpecialWall(false);
            if (var14 != nullptr) {
    return var14;
            } else {
               var14 = var1.getSpecialWall(true);
               if (var14 != nullptr) {
    return var14;
               } else if (!var39.isBlockedTo(var1) && !var42.isBlockedTo(var1)) {
                  var14 = var1.getSpecialSolid();
                  return var14 != nullptr ? var14 : nullptr;
               } else {
    return nullptr;
               }
            }
         } else {
    return nullptr;
         }
      } else if (var1.x < this.x && var1.y > this.y) {
    IsoObject var2 = this.getSpecialWall(false);
         if (var2 != nullptr) {
    return var2;
         } else {
    IsoGridSquare var3 = this.getCell().getGridSquare(this.x, this.y + 1, this.z);
            if (var3 != nullptr) {
               var2 = var3.getSpecialWall(true);
               if (var2 != nullptr) {
    return var2;
               }

               if (!this.isBlockedTo(var3)) {
                  var2 = var3.getSpecialSolid();
                  if (var2 != nullptr) {
    return var2;
                  }
               }
            }

    IsoGridSquare var4 = this.getCell().getGridSquare(this.x - 1, this.y, this.z);
            if (var4 != nullptr && !this.isBlockedTo(var4)) {
               var2 = var4.getSpecialSolid();
               if (var2 != nullptr) {
    return var2;
               }
            }

            if (var3 != nullptr && !this.isBlockedTo(var3) && var4 != nullptr && !this.isBlockedTo(var4)) {
               var2 = var1.getSpecialWall(true);
               if (var2 != nullptr) {
    return var2;
               } else if (!var3.isBlockedTo(var1) && !var4.isBlockedTo(var1)) {
                  var2 = var1.getSpecialSolid();
                  return var2 != nullptr ? var2 : nullptr;
               } else {
    return nullptr;
               }
            } else {
    return nullptr;
            }
         }
      } else {
    return nullptr;
      }
   }

    IsoObject getDoorFrameTo(IsoGridSquare var1) {
    std::vector var2 = nullptr;
      if (var1.y >= this.y && var1.x >= this.x) {
         var2 = var1.SpecialObjects;
      } else {
         var2 = this.SpecialObjects;
      }

      for (int var3 = 0; var3 < var2.size(); var3++) {
         if (var2.get(var3) instanceof IsoDoor) {
    IsoDoor var4 = (IsoDoor)var2.get(var3);
    bool var5 = var4.north;
            if (var5 && var1.y != this.y) {
    return var4;
            }

            if (!var5 && var1.x != this.x) {
    return var4;
            }
         } else if (var2.get(var3) instanceof IsoThumpable && ((IsoThumpable)var2.get(var3)).isDoor) {
    IsoThumpable var7 = (IsoThumpable)var2.get(var3);
    bool var8 = var7.north;
            if (var8 && var1.y != this.y) {
    return var7;
            }

            if (!var8 && var1.x != this.x) {
    return var7;
            }
         }
      }

    return nullptr;
   }

    static void getSquaresForThread(ArrayDeque<IsoGridSquare> var0, int var1) {
      for (int var2 = 0; var2 < var1; var2++) {
    IsoGridSquare var3 = isoGridSquareCache.poll();
         if (var3 == nullptr) {
            var0.push_back(std::make_shared<IsoGridSquare>(nullptr, nullptr, 0, 0, 0));
         } else {
            var0.push_back(var3);
         }
      }
   }

    static IsoGridSquare getNew(IsoCell var0, SliceY var1, int var2, int var3, int var4) {
    IsoGridSquare var5 = isoGridSquareCache.poll();
      if (var5 == nullptr) {
         return std::make_shared<IsoGridSquare>(var0, var1, var2, var3, var4);
      } else {
         var5.x = var2;
         var5.y = var3;
         var5.z = var4;
         var5.CachedScreenValue = -1;
         col = 0;
         path = 0;
         pathdoor = 0;
         vision = 0;
         var5.collideMatrix = 134217727;
         var5.pathMatrix = 134217727;
         var5.visionMatrix = 0;
    return var5;
      }
   }

    static IsoGridSquare getNew(ArrayDeque<IsoGridSquare> var0, IsoCell var1, SliceY var2, int var3, int var4, int var5) {
    IsoGridSquare var6 = nullptr;
      if (var0.empty()) {
         return std::make_shared<IsoGridSquare>(var1, var2, var3, var4, var5);
      } else {
         var6 = (IsoGridSquare)var0.pop();
         var6.x = var3;
         var6.y = var4;
         var6.z = var5;
         var6.CachedScreenValue = -1;
         col = 0;
         path = 0;
         pathdoor = 0;
         vision = 0;
         var6.collideMatrix = 134217727;
         var6.pathMatrix = 134217727;
         var6.visionMatrix = 0;
    return var6;
      }
   }

    long getHashCodeObjects() {
      this.recalcHashCodeObjects();
      return this.hashCodeObjects;
   }

    int getHashCodeObjectsInt() {
      this.recalcHashCodeObjects();
      return (int)this.hashCodeObjects;
   }

    void recalcHashCodeObjects() {
    long var1 = 0L;
      this.hashCodeObjects = var1;
   }

    int hashCodeNoOverride() {
    int var1 = 0;
      this.recalcHashCodeObjects();
      var1 = var1 * 2 + this.Objects.size();
      var1 = (int)(var1 + this.getHashCodeObjects());

      for (int var2 = 0; var2 < this.Objects.size(); var2++) {
         var1 = var1 * 2 + ((IsoObject)this.Objects.get(var2)).hashCode();
      }

    int var13 = 0;

      for (int var3 = 0; var3 < this.StaticMovingObjects.size(); var3++) {
         if (this.StaticMovingObjects.get(var3) instanceof IsoDeadBody) {
            var13++;
         }
      }

      var1 = var1 * 2 + var13;

      for (int var14 = 0; var14 < this.StaticMovingObjects.size(); var14++) {
    IsoMovingObject var4 = this.StaticMovingObjects.get(var14);
         if (dynamic_cast<IsoDeadBody*>(var4) != nullptr) {
            var1 = var1 * 2 + var4.hashCode();
         }
      }

      if (this.table != nullptr && !this.table.empty()) {
         var1 = var1 * 2 + this.table.hashCode();
      }

    uint8_t var15 = 0;
      if (this.isOverlayDone()) {
         var15 = (byte)(var15 | 1);
      }

      if (this.haveRoof) {
         var15 = (byte)(var15 | 2);
      }

      if (this.burntOut) {
         var15 = (byte)(var15 | 4);
      }

      var1 = var1 * 2 + var15;
      var1 = var1 * 2 + this.getErosionData().hashCode();
      if (this.getTrapPositionX() > 0) {
         var1 = var1 * 2 + this.getTrapPositionX();
         var1 = var1 * 2 + this.getTrapPositionY();
         var1 = var1 * 2 + this.getTrapPositionZ();
      }

      var1 = var1 * 2 + (this.haveElectricity() ? 1 : 0);
      return var1 * 2 + (this.haveSheetRope ? 1 : 0);
   }

    public IsoGridSquare(IsoCell var1, SliceY var2, int var3, int var4, int var5) {
      this.ID = ++IDMax;
      this.x = var3;
      this.y = var4;
      this.z = var5;
      this.CachedScreenValue = -1;
      col = 0;
      path = 0;
      pathdoor = 0;
      vision = 0;
      this.collideMatrix = 134217727;
      this.pathMatrix = 134217727;
      this.visionMatrix = 0;

      for (int var6 = 0; var6 < 4; var6++) {
         if (GameServer.bServer) {
            if (var6 == 0) {
               this.lighting[var6] = std::make_unique<ServerLighting>();
            }
         } else if (LightingJNI.init) {
            this.lighting[var6] = std::make_shared<JNILighting>(var6, this);
         } else {
            this.lighting[var6] = std::make_unique<Lighting>();
         }
      }
   }

    IsoGridSquare getTileInDirection(IsoDirections var1) {
      if (var1 == IsoDirections.N) {
         return this.getCell().getGridSquare(this.x, this.y - 1, this.z);
      } else if (var1 == IsoDirections.NE) {
         return this.getCell().getGridSquare(this.x + 1, this.y - 1, this.z);
      } else if (var1 == IsoDirections.NW) {
         return this.getCell().getGridSquare(this.x - 1, this.y - 1, this.z);
      } else if (var1 == IsoDirections.E) {
         return this.getCell().getGridSquare(this.x + 1, this.y, this.z);
      } else if (var1 == IsoDirections.W) {
         return this.getCell().getGridSquare(this.x - 1, this.y, this.z);
      } else if (var1 == IsoDirections.SE) {
         return this.getCell().getGridSquare(this.x + 1, this.y + 1, this.z);
      } else if (var1 == IsoDirections.SW) {
         return this.getCell().getGridSquare(this.x - 1, this.y + 1, this.z);
      } else {
    return var1 = = IsoDirections.S ? this.getCell().getGridSquare(this.x, this.y + 1, this.z) : nullptr;
      }
   }

    IsoObject getWall() {
      for (int var1 = 0; var1 < this.Objects.size(); var1++) {
    IsoObject var2 = (IsoObject)this.Objects.get(var1);
         if (var2 != nullptr && var2.sprite != nullptr && (var2.sprite.cutW || var2.sprite.cutN)) {
    return var2;
         }
      }

    return nullptr;
   }

    IsoObject getThumpableWall(bool var1) {
    IsoObject var2 = this.getWall(var1);
      return var2 != nullptr && dynamic_cast<IsoThumpable*>(var2) != nullptr ? var2 : nullptr;
   }

    IsoObject getHoppableWall(bool var1) {
      for (int var2 = 0; var2 < this.Objects.size(); var2++) {
    IsoObject var3 = (IsoObject)this.Objects.get(var2);
         if (var3 != nullptr && var3.sprite != nullptr) {
    PropertyContainer var4 = var3.getProperties();
    bool var5 = var4.Is(IsoFlagType.TallHoppableW) && !var4.Is(IsoFlagType.WallWTrans);
    bool var6 = var4.Is(IsoFlagType.TallHoppableN) && !var4.Is(IsoFlagType.WallNTrans);
            if (var5 && !var1 || var6 && var1) {
    return var3;
            }
         }
      }

    return nullptr;
   }

    IsoObject getThumpableWallOrHoppable(bool var1) {
    IsoObject var2 = this.getThumpableWall(var1);
    IsoObject var3 = this.getHoppableWall(var1);
      if (var2 != nullptr && var3 != nullptr && var2 == var3) {
    return var2;
      } else if (var2 == nullptr && var3 != nullptr) {
    return var3;
      } else {
         return var2 != nullptr && var3 == nullptr ? var2 : nullptr;
      }
   }

    bool getWallFull() {
      for (int var1 = 0; var1 < this.Objects.size(); var1++) {
    IsoObject var2 = (IsoObject)this.Objects.get(var1);
         if (var2 != nullptr
            && var2.sprite != nullptr
            && (var2.sprite.cutN || var2.sprite.cutW || var2.sprite.getProperties().Is(IsoFlagType.WallN) || var2.sprite.getProperties().Is(IsoFlagType.WallW))
            )
          {
    return true;
         }
      }

    return false;
   }

    IsoObject getWall(bool var1) {
      for (int var2 = 0; var2 < this.Objects.size(); var2++) {
    IsoObject var3 = (IsoObject)this.Objects.get(var2);
         if (var3 != nullptr && var3.sprite != nullptr && (var3.sprite.cutN && var1 || var3.sprite.cutW && !var1)) {
    return var3;
         }
      }

    return nullptr;
   }

    IsoObject getWallSE() {
      for (int var1 = 0; var1 < this.Objects.size(); var1++) {
    IsoObject var2 = (IsoObject)this.Objects.get(var1);
         if (var2 != nullptr && var2.sprite != nullptr && var2.sprite.getProperties().Is(IsoFlagType.WallSE)) {
    return var2;
         }
      }

    return nullptr;
   }

    IsoObject getFloor() {
      for (int var1 = 0; var1 < this.Objects.size(); var1++) {
    IsoObject var2 = (IsoObject)this.Objects.get(var1);
         if (var2.sprite != nullptr && var2.sprite.getProperties().Is(IsoFlagType.solidfloor)) {
    return var2;
         }
      }

    return nullptr;
   }

    IsoObject getPlayerBuiltFloor() {
      return this.getBuilding() == nullptr && this.roofHideBuilding == nullptr ? this.getFloor() : nullptr;
   }

    void interpolateLight(ColorInfo var1, float var2, float var3) {
    IsoCell var4 = this.getCell();
      if (var2 < 0.0F) {
         var2 = 0.0F;
      }

      if (var2 > 1.0F) {
         var2 = 1.0F;
      }

      if (var3 < 0.0F) {
         var3 = 0.0F;
      }

      if (var3 > 1.0F) {
         var3 = 1.0F;
      }

    int var5 = IsoCamera.frameState.playerIndex;
    int var6 = this.getVertLight(0, var5);
    int var7 = this.getVertLight(1, var5);
    int var8 = this.getVertLight(2, var5);
    int var9 = this.getVertLight(3, var5);
      tl.fromColor(var6);
      bl.fromColor(var9);
      tr.fromColor(var7);
      br.fromColor(var8);
      tl.interp(tr, var2, interp1);
      bl.interp(br, var2, interp2);
      interp1.interp(interp2, var3, finalCol);
      var1.r = finalCol.r;
      var1.g = finalCol.g;
      var1.b = finalCol.b;
      var1.a = finalCol.a;
   }

    void EnsureSurroundNotNull() {
      assert !GameServer.bServer;

      for (int var1 = -1; var1 <= 1; var1++) {
         for (int var2 = -1; var2 <= 1; var2++) {
            if ((var1 != 0 || var2 != 0)
               && IsoWorld.instance.isValidSquare(this.x + var1, this.y + var2, this.z)
               && this.getCell().getChunkForGridSquare(this.x + var1, this.y + var2, this.z) != nullptr) {
    IsoGridSquare var3 = this.getCell().getGridSquare(this.x + var1, this.y + var2, this.z);
               if (var3 == nullptr) {
                  var3 = getNew(this.getCell(), nullptr, this.x + var1, this.y + var2, this.z);
    IsoGridSquare var4 = this.getCell().ConnectNewSquare(var3, false);
               }
            }
         }
      }
   }

    IsoObject addFloor(const std::string& var1) {
      IsoRegions.setPreviousFlags(this);
    IsoObject var2 = std::make_shared<IsoObject>(this.getCell(), this, var1);
    bool var3 = false;

      for (int var4 = 0; var4 < this.getObjects().size(); var4++) {
    IsoObject var5 = (IsoObject)this.getObjects().get(var4);
    IsoSprite var6 = var5.sprite;
         if (var6 != nullptr
            && (
               var6.getProperties().Is(IsoFlagType.solidfloor)
                  || var6.getProperties().Is(IsoFlagType.noStart)
                  || var6.getProperties().Is(IsoFlagType.vegitation) && var5.getType() != IsoObjectType.tree
                  || var6.getName() != nullptr && var6.getName().startsWith("blends_grassoverlays")
            )) {
            if (var6.getName() != nullptr && var6.getName().startsWith("floors_rugs")) {
               var3 = true;
            } else {
               this.transmitRemoveItemFromSquare(var5);
               var4--;
            }
         }
      }

      var2.sprite.getProperties().Set(IsoFlagType.solidfloor);
      if (var3) {
         this.getObjects().push_back(0, var2);
      } else {
         this.getObjects().push_back(var2);
      }

      this.EnsureSurroundNotNull();
      this.RecalcProperties();
      this.getCell().checkHaveRoof(this.x, this.y);

      for (int var7 = 0; var7 < IsoPlayer.numPlayers; var7++) {
         LosUtil.cachecleared[var7] = true;
      }

      setRecalcLightTime(-1);
      GameTime.getInstance().lightSourceUpdate = 100.0F;
      var2.transmitCompleteItemToServer();
      this.RecalcAllWithNeighbours(true);

      for (int var8 = this.z - 1; var8 > 0; var8--) {
    IsoGridSquare var9 = this.getCell().getGridSquare(this.x, this.y, var8);
         if (var9 == nullptr) {
            var9 = getNew(this.getCell(), nullptr, this.x, this.y, var8);
            this.getCell().ConnectNewSquare(var9, false);
         }

         var9.EnsureSurroundNotNull();
         var9.RecalcAllWithNeighbours(true);
      }

      this.setCachedIsFree(false);
      PolygonalMap2.instance.squareChanged(this);
      IsoGridOcclusionData.SquareChanged();
      IsoRegions.squareChanged(this);
      this.clearWater();
    return var2;
   }

    IsoThumpable AddStairs(bool var1, int var2, const std::string& var3, const std::string& var4, KahluaTable var5) {
      IsoRegions.setPreviousFlags(this);
      this.EnsureSurroundNotNull();
    bool var6 = !this.TreatAsSolidFloor() && !this.HasStairsBelow();
      this.CachedIsFree = false;
    IsoThumpable var7 = std::make_shared<IsoThumpable>(this.getCell(), this, var3, var1, var5);
      if (var1) {
         if (var2 == 0) {
            var7.setType(IsoObjectType.stairsBN);
         }

         if (var2 == 1) {
            var7.setType(IsoObjectType.stairsMN);
         }

         if (var2 == 2) {
            var7.setType(IsoObjectType.stairsTN);
            var7.sprite.getProperties().Set(var1 ? IsoFlagType.cutN : IsoFlagType.cutW);
         }
      }

      if (!var1) {
         if (var2 == 0) {
            var7.setType(IsoObjectType.stairsBW);
         }

         if (var2 == 1) {
            var7.setType(IsoObjectType.stairsMW);
         }

         if (var2 == 2) {
            var7.setType(IsoObjectType.stairsTW);
            var7.sprite.getProperties().Set(var1 ? IsoFlagType.cutN : IsoFlagType.cutW);
         }
      }

      this.AddSpecialObject(var7);
      if (var6 && var2 == 2) {
    int var8 = this.z - 1;
    IsoGridSquare var9 = this.getCell().getGridSquare(this.x, this.y, var8);
         if (var9 == nullptr) {
            var9 = std::make_shared<IsoGridSquare>(this.getCell(), nullptr, this.x, this.y, var8);
            this.getCell().ConnectNewSquare(var9, true);
         }

         while (var8 >= 0) {
    IsoThumpable var10 = std::make_shared<IsoThumpable>(this.getCell(), var9, var4, var1, var5);
            var9.AddSpecialObject(var10);
            var10.transmitCompleteItemToServer();
            if (var9.TreatAsSolidFloor()) {
               break;
            }

            if (this.getCell().getGridSquare(var9.x, var9.y, --var8) == nullptr) {
               var9 = std::make_shared<IsoGridSquare>(this.getCell(), nullptr, var9.x, var9.y, var8);
               this.getCell().ConnectNewSquare(var9, true);
            } else {
               var9 = this.getCell().getGridSquare(var9.x, var9.y, var8);
            }
         }
      }

      if (var2 == 2) {
    IsoGridSquare var12 = nullptr;
         if (var1) {
            if (IsoWorld.instance.isValidSquare(this.x, this.y - 1, this.z + 1)) {
               var12 = this.getCell().getGridSquare(this.x, this.y - 1, this.z + 1);
               if (var12 == nullptr) {
                  var12 = std::make_shared<IsoGridSquare>(this.getCell(), nullptr, this.x, this.y - 1, this.z + 1);
                  this.getCell().ConnectNewSquare(var12, false);
               }

               if (!var12.Properties.Is(IsoFlagType.solidfloor)) {
                  var12.addFloor("carpentry_02_57");
               }
            }
         } else if (IsoWorld.instance.isValidSquare(this.x - 1, this.y, this.z + 1)) {
            var12 = this.getCell().getGridSquare(this.x - 1, this.y, this.z + 1);
            if (var12 == nullptr) {
               var12 = std::make_shared<IsoGridSquare>(this.getCell(), nullptr, this.x - 1, this.y, this.z + 1);
               this.getCell().ConnectNewSquare(var12, false);
            }

            if (!var12.Properties.Is(IsoFlagType.solidfloor)) {
               var12.addFloor("carpentry_02_57");
            }
         }

         var12.getModData().rawset("ConnectedToStairs" + var1, true);
         var12 = this.getCell().getGridSquare(this.x, this.y, this.z + 1);
         if (var12 == nullptr) {
            var12 = std::make_shared<IsoGridSquare>(this.getCell(), nullptr, this.x, this.y, this.z + 1);
            this.getCell().ConnectNewSquare(var12, false);
         }
      }

      for (int var15 = this.getX() - 1; var15 <= this.getX() + 1; var15++) {
         for (int var16 = this.getY() - 1; var16 <= this.getY() + 1; var16++) {
            for (int var17 = this.getZ() - 1; var17 <= this.getZ() + 1; var17++) {
               if (IsoWorld.instance.isValidSquare(var15, var16, var17)) {
    IsoGridSquare var11 = this.getCell().getGridSquare(var15, var16, var17);
                  if (var11 == nullptr) {
                     var11 = std::make_shared<IsoGridSquare>(this.getCell(), nullptr, var15, var16, var17);
                     this.getCell().ConnectNewSquare(var11, false);
                  }

                  var11.ReCalculateCollide(this);
                  var11.ReCalculateVisionBlocked(this);
                  var11.ReCalculatePathFind(this);
                  this.ReCalculateCollide(var11);
                  this.ReCalculatePathFind(var11);
                  this.ReCalculateVisionBlocked(var11);
                  var11.CachedIsFree = false;
               }
            }
         }
      }

    return var7;
   }

    void ReCalculateAll(IsoGridSquare var1) {
      this.ReCalculateAll(var1, cellGetSquare);
   }

    void ReCalculateAll(IsoGridSquare var1, GetSquare var2) {
      if (var1 != nullptr && var1 != this) {
         this.SolidFloorCached = false;
         var1.SolidFloorCached = false;
         this.RecalcPropertiesIfNeeded();
         var1.RecalcPropertiesIfNeeded();
         this.ReCalculateCollide(var1, var2);
         var1.ReCalculateCollide(this, var2);
         this.ReCalculatePathFind(var1, var2);
         var1.ReCalculatePathFind(this, var2);
         this.ReCalculateVisionBlocked(var1, var2);
         var1.ReCalculateVisionBlocked(this, var2);
         this.setBlockedGridPointers(var2);
         var1.setBlockedGridPointers(var2);
      }
   }

    void ReCalculateAll(bool var1, IsoGridSquare var2, GetSquare var3) {
      if (var2 != nullptr && var2 != this) {
         this.SolidFloorCached = false;
         var2.SolidFloorCached = false;
         this.RecalcPropertiesIfNeeded();
         if (var1) {
            var2.RecalcPropertiesIfNeeded();
         }

         this.ReCalculateCollide(var2, var3);
         if (var1) {
            var2.ReCalculateCollide(this, var3);
         }

         this.ReCalculatePathFind(var2, var3);
         if (var1) {
            var2.ReCalculatePathFind(this, var3);
         }

         this.ReCalculateVisionBlocked(var2, var3);
         if (var1) {
            var2.ReCalculateVisionBlocked(this, var3);
         }

         this.setBlockedGridPointers(var3);
         if (var1) {
            var2.setBlockedGridPointers(var3);
         }
      }
   }

    void ReCalculateMineOnly(IsoGridSquare var1) {
      this.SolidFloorCached = false;
      this.RecalcProperties();
      this.ReCalculateCollide(var1);
      this.ReCalculatePathFind(var1);
      this.ReCalculateVisionBlocked(var1);
      this.setBlockedGridPointers(cellGetSquare);
   }

    void RecalcAllWithNeighbours(bool var1) {
      this.RecalcAllWithNeighbours(var1, cellGetSquare);
   }

    void RecalcAllWithNeighbours(bool var1, GetSquare var2) {
      this.SolidFloorCached = false;
      this.RecalcPropertiesIfNeeded();

      for (int var3 = this.getX() - 1; var3 <= this.getX() + 1; var3++) {
         for (int var4 = this.getY() - 1; var4 <= this.getY() + 1; var4++) {
            for (int var5 = this.getZ() - 1; var5 <= this.getZ() + 1; var5++) {
               if (IsoWorld.instance.isValidSquare(var3, var4, var5)) {
    int var6 = var3 - this.getX();
    int var7 = var4 - this.getY();
    int var8 = var5 - this.getZ();
                  if (var6 != 0 || var7 != 0 || var8 != 0) {
    IsoGridSquare var9 = var2.getGridSquare(var3, var4, var5);
                     if (var9 != nullptr) {
                        var9.DirtySlice();
                        this.ReCalculateAll(var1, var9, var2);
                     }
                  }
               }
            }
         }
      }

      IsoWorld.instance.CurrentCell.DoGridNav(this, var2);
    IsoGridSquare var10 = this.nav[IsoDirections.N.index()];
    IsoGridSquare var11 = this.nav[IsoDirections.S.index()];
    IsoGridSquare var12 = this.nav[IsoDirections.W.index()];
    IsoGridSquare var13 = this.nav[IsoDirections.E.index()];
      if (var10 != nullptr && var12 != nullptr) {
         var10.ReCalculateAll(var12, var2);
      }

      if (var10 != nullptr && var13 != nullptr) {
         var10.ReCalculateAll(var13, var2);
      }

      if (var11 != nullptr && var12 != nullptr) {
         var11.ReCalculateAll(var12, var2);
      }

      if (var11 != nullptr && var13 != nullptr) {
         var11.ReCalculateAll(var13, var2);
      }
   }

    void RecalcAllWithNeighboursMineOnly() {
      this.SolidFloorCached = false;
      this.RecalcProperties();

      for (int var1 = this.getX() - 1; var1 <= this.getX() + 1; var1++) {
         for (int var2 = this.getY() - 1; var2 <= this.getY() + 1; var2++) {
            for (int var3 = this.getZ() - 1; var3 <= this.getZ() + 1; var3++) {
               if (var3 >= 0) {
    int var4 = var1 - this.getX();
    int var5 = var2 - this.getY();
    int var6 = var3 - this.getZ();
                  if (var4 != 0 || var5 != 0 || var6 != 0) {
    IsoGridSquare var7 = this.getCell().getGridSquare(var1, var2, var3);
                     if (var7 != nullptr) {
                        var7.DirtySlice();
                        this.ReCalculateMineOnly(var7);
                     }
                  }
               }
            }
         }
      }
   }

    bool IsWindow(int var1, int var2, int var3) {
    IsoGridSquare var4 = this.getCell().getGridSquare(this.x + var1, this.y + var2, this.z + var3);
      return this.getWindowTo(var4) != nullptr || this.getWindowThumpableTo(var4) != nullptr;
   }

    void RemoveAllWith(IsoFlagType var1) {
      for (int var2 = 0; var2 < this.Objects.size(); var2++) {
    IsoObject var3 = (IsoObject)this.Objects.get(var2);
         if (var3.sprite != nullptr && var3.sprite.getProperties().Is(var1)) {
            this.Objects.remove(var3);
            this.SpecialObjects.remove(var3);
            var2--;
         }
      }

      this.RecalcAllWithNeighbours(true);
   }

    bool hasSupport() {
    IsoGridSquare var1 = this.getCell().getGridSquare(this.x, this.y + 1, this.z);
    IsoGridSquare var2 = this.getCell().getGridSquare(this.x + 1, this.y, this.z);

      for (int var3 = 0; var3 < this.Objects.size(); var3++) {
    IsoObject var4 = (IsoObject)this.Objects.get(var3);
         if (var4.sprite != nullptr
            && (
               var4.sprite.getProperties().Is(IsoFlagType.solid)
                  || (var4.sprite.getProperties().Is(IsoFlagType.cutW) || var4.sprite.getProperties().Is(IsoFlagType.cutN))
                     && !var4.sprite.Properties.Is(IsoFlagType.halfheight)
            )) {
    return true;
         }
      }

      return var1 != nullptr && var1.Properties.Is(IsoFlagType.cutN) && !var1.Properties.Is(IsoFlagType.halfheight)
         ? true
         : var2 != nullptr && var2.Properties.Is(IsoFlagType.cutW) && !var1.Properties.Is(IsoFlagType.halfheight);
   }

    int getID() {
      return this.ID;
   }

    void setID(int var1) {
      this.ID = var1;
   }

    int savematrix(boolean[][][] var1, byte[] var2, int var3) {
      for (int var4 = 0; var4 <= 2; var4++) {
         for (int var5 = 0; var5 <= 2; var5++) {
            for (int var6 = 0; var6 <= 2; var6++) {
               var2[var3] = (byte)(var1[var4][var5][var6] ? 1 : 0);
               var3++;
            }
         }
      }

    return var3;
   }

    int loadmatrix(boolean[][][] var1, byte[] var2, int var3) {
      for (int var4 = 0; var4 <= 2; var4++) {
         for (int var5 = 0; var5 <= 2; var5++) {
            for (int var6 = 0; var6 <= 2; var6++) {
               var1[var4][var5][var6] = var2[var3] != 0;
               var3++;
            }
         }
      }

    return var3;
   }

    void savematrix(boolean[][][] var1, ByteBuffer var2) {
      for (int var3 = 0; var3 <= 2; var3++) {
         for (int var4 = 0; var4 <= 2; var4++) {
            for (int var5 = 0; var5 <= 2; var5++) {
               var2.put((byte)(var1[var3][var4][var5] ? 1 : 0));
            }
         }
      }
   }

    void loadmatrix(boolean[][][] var1, ByteBuffer var2) {
      for (int var3 = 0; var3 <= 2; var3++) {
         for (int var4 = 0; var4 <= 2; var4++) {
            for (int var5 = 0; var5 <= 2; var5++) {
               var1[var3][var4][var5] = var2.get() != 0;
            }
         }
      }
   }

    void DirtySlice() {
   }

    void setHourSeenToCurrent() {
      this.hourLastSeen = (int)GameTime.instance.getWorldAgeHours();
   }

    void splatBlood(int var1, float var2) {
      var2 *= 2.0F;
      var2 *= 3.0F;
      if (var2 > 1.0F) {
         var2 = 1.0F;
      }

    IsoGridSquare var3 = this;
    IsoGridSquare var4 = this;

      for (int var5 = 0; var5 < var1; var5++) {
         if (var3 != nullptr) {
            var3 = this.getCell().getGridSquare(this.getX(), this.getY() - var5, this.getZ());
         }

         if (var4 != nullptr) {
            var4 = this.getCell().getGridSquare(this.getX() - var5, this.getY(), this.getZ());
         }

    float var6 = 0.0F;
         if (var4 != nullptr && var4.testCollideAdjacent(nullptr, -1, 0, 0)) {
    bool var7 = false;
    bool var8 = false;
    uint8_t var9 = 0;
    uint8_t var10 = 0;
            if (var4.getS() != nullptr && var4.getS().testCollideAdjacent(nullptr, -1, 0, 0)) {
               var7 = true;
            }

            if (var4.getN() != nullptr && var4.getN().testCollideAdjacent(nullptr, -1, 0, 0)) {
               var8 = true;
            }

            if (var7) {
               var9 = -1;
            }

            if (var8) {
               var10 = 1;
            }

    int var11 = var10 - var9;
    bool var12 = false;
    uint8_t var13 = 0;
    uint8_t var14 = 0;
            if (var11 > 0 && Rand.Next(2) == 0) {
               var12 = true;
               if (var11 > 1) {
                  if (Rand.Next(2) == 0) {
                     var13 = -1;
                     var14 = 0;
                  } else {
                     var13 = 0;
                     var14 = 1;
                  }
               } else {
                  var13 = var9;
                  var14 = var10;
               }
            }

    float var15 = Rand.Next(100) / 300.0F;
    IsoGridSquare var16 = this.getCell().getGridSquare(var4.getX(), var4.getY() + var13, var4.getZ());
    IsoGridSquare var17 = this.getCell().getGridSquare(var4.getX(), var4.getY() + var14, var4.getZ());
            if (var16 == nullptr
               || var17 == nullptr
               || !var16.Is(IsoFlagType.cutW)
               || !var17.Is(IsoFlagType.cutW)
               || var16.getProperties().Is(IsoFlagType.WallSE)
               || var17.getProperties().Is(IsoFlagType.WallSE)
               || var16.Is(IsoFlagType.HoppableW)
               || var17.Is(IsoFlagType.HoppableW)) {
               var12 = false;
            }

            if (var12) {
    int var32 = 24 + Rand.Next(2) * 2;
               if (Rand.Next(2) == 0) {
                  var32 += 8;
               }

               var16.DoSplat("overlay_blood_wall_01_" + (var32 + 1), false, IsoFlagType.cutW, var6, var15, var2);
               var17.DoSplat("overlay_blood_wall_01_" + (var32 + 0), false, IsoFlagType.cutW, var6, var15, var2);
            } else {
    int var18 = 0;
               switch (Rand.Next(3)) {
                  case 0:
                     var18 = 0 + Rand.Next(4);
                     break;
                  case 1:
                     var18 = 8 + Rand.Next(4);
                     break;
                  case 2:
                     var18 = 16 + Rand.Next(4);
               }

               if (var18 == 17 || var18 == 19) {
                  var15 = 0.0F;
               }

               if (var4.Is(IsoFlagType.HoppableW)) {
                  var4.DoSplat("overlay_blood_fence_01_" + var18, false, IsoFlagType.HoppableW, var6, 0.0F, var2);
               } else {
                  var4.DoSplat("overlay_blood_wall_01_" + var18, false, IsoFlagType.cutW, var6, var15, var2);
               }
            }

            var4 = nullptr;
         }

         if (var3 != nullptr && var3.testCollideAdjacent(nullptr, 0, -1, 0)) {
    bool var21 = false;
    bool var22 = false;
    uint8_t var23 = 0;
    uint8_t var24 = 0;
            if (var3.getW() != nullptr && var3.getW().testCollideAdjacent(nullptr, 0, -1, 0)) {
               var21 = true;
            }

            if (var3.getE() != nullptr && var3.getE().testCollideAdjacent(nullptr, 0, -1, 0)) {
               var22 = true;
            }

            if (var21) {
               var23 = -1;
            }

            if (var22) {
               var24 = 1;
            }

    int var25 = var24 - var23;
    bool var26 = false;
    uint8_t var27 = 0;
    uint8_t var28 = 0;
            if (var25 > 0 && Rand.Next(2) == 0) {
               var26 = true;
               if (var25 > 1) {
                  if (Rand.Next(2) == 0) {
                     var27 = -1;
                     var28 = 0;
                  } else {
                     var27 = 0;
                     var28 = 1;
                  }
               } else {
                  var27 = var23;
                  var28 = var24;
               }
            }

    float var29 = Rand.Next(100) / 300.0F;
    IsoGridSquare var30 = this.getCell().getGridSquare(var3.getX() + var27, var3.getY(), var3.getZ());
    IsoGridSquare var31 = this.getCell().getGridSquare(var3.getX() + var28, var3.getY(), var3.getZ());
            if (var30 == nullptr
               || var31 == nullptr
               || !var30.Is(IsoFlagType.cutN)
               || !var31.Is(IsoFlagType.cutN)
               || var30.getProperties().Is(IsoFlagType.WallSE)
               || var31.getProperties().Is(IsoFlagType.WallSE)
               || var30.Is(IsoFlagType.HoppableN)
               || var31.Is(IsoFlagType.HoppableN)) {
               var26 = false;
            }

            if (var26) {
    int var34 = 28 + Rand.Next(2) * 2;
               if (Rand.Next(2) == 0) {
                  var34 += 8;
               }

               var30.DoSplat("overlay_blood_wall_01_" + (var34 + 0), false, IsoFlagType.cutN, var6, var29, var2);
               var31.DoSplat("overlay_blood_wall_01_" + (var34 + 1), false, IsoFlagType.cutN, var6, var29, var2);
            } else {
    int var33 = 0;
               switch (Rand.Next(3)) {
                  case 0:
                     var33 = 4 + Rand.Next(4);
                     break;
                  case 1:
                     var33 = 12 + Rand.Next(4);
                     break;
                  case 2:
                     var33 = 20 + Rand.Next(4);
               }

               if (var33 == 20 || var33 == 22) {
                  var29 = 0.0F;
               }

               if (var3.Is(IsoFlagType.HoppableN)) {
                  var3.DoSplat("overlay_blood_fence_01_" + var33, false, IsoFlagType.HoppableN, var6, var29, var2);
               } else {
                  var3.DoSplat("overlay_blood_wall_01_" + var33, false, IsoFlagType.cutN, var6, var29, var2);
               }
            }

            var3 = nullptr;
         }
      }
   }

    bool haveBlood() {
      if (Core.OptionBloodDecals == 0) {
    return false;
      } else {
         for (int var1 = 0; var1 < this.getObjects().size(); var1++) {
    IsoObject var2 = (IsoObject)this.getObjects().get(var1);
            if (var2.wallBloodSplats != nullptr && !var2.wallBloodSplats.empty()) {
    return true;
            }
         }

         for (int var5 = 0; var5 < this.getChunk().FloorBloodSplats.size(); var5++) {
    IsoFloorBloodSplat var6 = (IsoFloorBloodSplat)this.getChunk().FloorBloodSplats.get(var5);
    float var3 = var6.x + this.getChunk().wx * 10;
    float var4 = var6.y + this.getChunk().wy * 10;
            if ((int)var3 - 1 <= this.x && (int)var3 + 1 >= this.x && (int)var4 - 1 <= this.y && (int)var4 + 1 >= this.y) {
    return true;
            }
         }

    return false;
      }
   }

    void removeBlood(bool var1, bool var2) {
      for (int var3 = 0; var3 < this.getObjects().size(); var3++) {
    IsoObject var4 = (IsoObject)this.getObjects().get(var3);
         if (var4.wallBloodSplats != nullptr) {
            var4.wallBloodSplats.clear();
         }
      }

      if (!var2) {
         for (int var7 = 0; var7 < this.getChunk().FloorBloodSplats.size(); var7++) {
    IsoFloorBloodSplat var9 = (IsoFloorBloodSplat)this.getChunk().FloorBloodSplats.get(var7);
    int var5 = (int)(this.getChunk().wx * 10 + var9.x);
    int var6 = (int)(this.getChunk().wy * 10 + var9.y);
            if (var5 >= this.getX() - 1 && var5 <= this.getX() + 1 && var6 >= this.getY() - 1 && var6 <= this.getY() + 1) {
               this.getChunk().FloorBloodSplats.remove(var7);
               var7--;
            }
         }
      }

      if (GameClient.bClient && !var1) {
    ByteBufferWriter var8 = GameClient.connection.startPacket();
         PacketType.RemoveBlood.doPacket(var8);
         var8.putInt(this.x);
         var8.putInt(this.y);
         var8.putInt(this.z);
         var8.putBoolean(var2);
         PacketType.RemoveBlood.send(GameClient.connection);
      }
   }

    void DoSplat(const std::string& var1, bool var2, IsoFlagType var3, float var4, float var5, float var6) {
      for (int var7 = 0; var7 < this.getObjects().size(); var7++) {
    IsoObject var8 = (IsoObject)this.getObjects().get(var7);
         if (var8.sprite != nullptr && var8.sprite.getProperties().Is(var3) && (!(dynamic_cast<IsoWindow*>(var8) != nullptr) || !var8.isDestroyed())) {
    IsoSprite var9 = IsoSprite.getSprite(IsoSpriteManager.instance, var1, 0);
            if (var9 == nullptr) {
               return;
            }

            if (var8.wallBloodSplats == nullptr) {
               var8.wallBloodSplats = std::make_unique<std::vector>();
            }

    IsoWallBloodSplat var10 = std::make_shared<IsoWallBloodSplat>((float)GameTime.getInstance().getWorldAgeHours(), var9);
            var8.wallBloodSplats.push_back(var10);
         }
      }
   }

    void ClearTileObjects() {
      this.Objects.clear();
      this.RecalcProperties();
   }

    void ClearTileObjectsExceptFloor() {
      for (int var1 = 0; var1 < this.Objects.size(); var1++) {
    IsoObject var2 = (IsoObject)this.Objects.get(var1);
         if (var2.sprite == nullptr || !var2.sprite.getProperties().Is(IsoFlagType.solidfloor)) {
            this.Objects.remove(var2);
            var1--;
         }
      }

      this.RecalcProperties();
   }

    int RemoveTileObject(IsoObject var1) {
      IsoRegions.setPreviousFlags(this);
    int var2 = this.Objects.indexOf(var1);
      if (!this.Objects.contains(var1)) {
         var2 = this.SpecialObjects.indexOf(var1);
      }

      if (var1 != nullptr && this.Objects.contains(var1)) {
         if (var1.isTableSurface()) {
            for (int var3 = this.Objects.indexOf(var1) + 1; var3 < this.Objects.size(); var3++) {
    IsoObject var4 = (IsoObject)this.Objects.get(var3);
               if (var4.isTableTopObject() || var4.isTableSurface()) {
                  var4.setRenderYOffset(var4.getRenderYOffset() - var1.getSurfaceOffset());
                  var4.sx = 0.0F;
                  var4.sy = 0.0F;
               }
            }
         }

    IsoObject var5 = this.getPlayerBuiltFloor();
         if (var1 == var5) {
            IsoGridOcclusionData.SquareChanged();
         }

         LuaEventManager.triggerEvent("OnObjectAboutToBeRemoved", var1);
         if (!this.Objects.contains(var1)) {
            throw IllegalArgumentException("OnObjectAboutToBeRemoved not allowed to remove the object");
         }

         var2 = this.Objects.indexOf(var1);
         var1.removeFromWorld();
         var1.removeFromSquare();

         assert !this.Objects.contains(var1);

         assert !this.SpecialObjects.contains(var1);

         if (!(dynamic_cast<IsoWorldInventoryObject*>(var1) != nullptr)) {
            this.RecalcAllWithNeighbours(true);
            this.getCell().checkHaveRoof(this.getX(), this.getY());

            for (int var6 = 0; var6 < IsoPlayer.numPlayers; var6++) {
               LosUtil.cachecleared[var6] = true;
            }

            setRecalcLightTime(-1);
            GameTime.instance.lightSourceUpdate = 100.0F;
         }

         this.fixPlacedItemRenderOffsets();
      }

      MapCollisionData.instance.squareChanged(this);
      LuaEventManager.triggerEvent("OnTileRemoved", var1);
      PolygonalMap2.instance.squareChanged(this);
      IsoRegions.squareChanged(this, true);
    return var2;
   }

    int RemoveTileObjectErosionNoRecalc(IsoObject var1) {
    int var2 = this.Objects.indexOf(var1);
    IsoGridSquare var3 = var1.square;
      var1.removeFromWorld();
      var1.removeFromSquare();
      var3.RecalcPropertiesIfNeeded();

      assert !this.Objects.contains(var1);

      assert !this.SpecialObjects.contains(var1);

    return var2;
   }

    void AddSpecialObject(IsoObject var1) {
      this.AddSpecialObject(var1, -1);
   }

    void AddSpecialObject(IsoObject var1, int var2) {
      if (var1 != nullptr) {
         IsoRegions.setPreviousFlags(this);
         var2 = this.placeWallAndDoorCheck(var1, var2);
         if (var2 != -1 && var2 >= 0 && var2 <= this.Objects.size()) {
            this.Objects.push_back(var2, var1);
         } else {
            this.Objects.push_back(var1);
         }

         this.SpecialObjects.push_back(var1);
         this.burntOut = false;
         var1.addToWorld();
         if (!GameServer.bServer && !GameClient.bClient) {
            this.restackSheetRope();
         }

         this.RecalcAllWithNeighbours(true);
         this.fixPlacedItemRenderOffsets();
         if (!(dynamic_cast<IsoWorldInventoryObject*>(var1) != nullptr)) {
            for (int var3 = 0; var3 < IsoPlayer.numPlayers; var3++) {
               LosUtil.cachecleared[var3] = true;
            }

            setRecalcLightTime(-1);
            GameTime.instance.lightSourceUpdate = 100.0F;
            if (var1 == this.getPlayerBuiltFloor()) {
               IsoGridOcclusionData.SquareChanged();
            }
         }

         MapCollisionData.instance.squareChanged(this);
         PolygonalMap2.instance.squareChanged(this);
         IsoRegions.squareChanged(this);
      }
   }

    void AddTileObject(IsoObject var1) {
      this.AddTileObject(var1, -1);
   }

    void AddTileObject(IsoObject var1, int var2) {
      if (var1 != nullptr) {
         IsoRegions.setPreviousFlags(this);
         var2 = this.placeWallAndDoorCheck(var1, var2);
         if (var2 != -1 && var2 >= 0 && var2 <= this.Objects.size()) {
            this.Objects.push_back(var2, var1);
         } else {
            this.Objects.push_back(var1);
         }

         this.burntOut = false;
         var1.addToWorld();
         this.RecalcAllWithNeighbours(true);
         this.fixPlacedItemRenderOffsets();
         if (!(dynamic_cast<IsoWorldInventoryObject*>(var1) != nullptr)) {
            for (int var3 = 0; var3 < IsoPlayer.numPlayers; var3++) {
               LosUtil.cachecleared[var3] = true;
            }

            setRecalcLightTime(-1);
            GameTime.instance.lightSourceUpdate = 100.0F;
            if (var1 == this.getPlayerBuiltFloor()) {
               IsoGridOcclusionData.SquareChanged();
            }
         }

         MapCollisionData.instance.squareChanged(this);
         PolygonalMap2.instance.squareChanged(this);
         IsoRegions.squareChanged(this);
      }
   }

    int placeWallAndDoorCheck(IsoObject var1, int var2) {
    int var4 = -1;
      if (var1.sprite != nullptr) {
    IsoObjectType var3 = var1.sprite.getType();
    bool var5 = var3 == IsoObjectType.doorN || var3 == IsoObjectType.doorW;
         boolean var6 = !var5
            && (var1.sprite.cutW || var1.sprite.cutN || var3 == IsoObjectType.doorFrN || var3 == IsoObjectType.doorFrW || var1.sprite.treatAsWallOrder);
         if (var6 || var5) {
            for (int var8 = 0; var8 < this.Objects.size(); var8++) {
    IsoObject var7 = (IsoObject)this.Objects.get(var8);
               var3 = IsoObjectType.MAX;
               if (var7.sprite != nullptr) {
                  var3 = var7.sprite.getType();
                  if (var6 && (var3 == IsoObjectType.doorN || var3 == IsoObjectType.doorW)) {
                     var4 = var8;
                  }

                  if (var5
                     && (var3 == IsoObjectType.doorFrN || var3 == IsoObjectType.doorFrW || var7.sprite.cutW || var7.sprite.cutN || var7.sprite.treatAsWallOrder)
                     )
                   {
                     var4 = var8;
                  }
               }
            }

            if (var5 && var4 > var2) {
               return var4 + 1;
            }

            if (var6 && var4 >= 0 && (var4 < var2 || var2 < 0)) {
    return var4;
            }
         }
      }

    return var2;
   }

    void transmitAddObjectToSquare(IsoObject var1, int var2) {
      if (var1 != nullptr && !this.Objects.contains(var1)) {
         this.AddTileObject(var1, var2);
         if (GameClient.bClient) {
            var1.transmitCompleteItemToServer();
         }

         if (GameServer.bServer) {
            var1.transmitCompleteItemToClients();
         }
      }
   }

    int transmitRemoveItemFromSquare(IsoObject var1) {
      if (var1 != nullptr && this.Objects.contains(var1)) {
         if (GameClient.bClient) {
            try {
               GameClient.instance.checkAddedRemovedItems(var1);
            } catch (Exception var3) {
               GameClient.connection.cancelPacket();
               ExceptionLogger.logException(var3);
            }

    ByteBufferWriter var2 = GameClient.connection.startPacket();
            PacketType.RemoveItemFromSquare.doPacket(var2);
            var2.putInt(this.getX());
            var2.putInt(this.getY());
            var2.putInt(this.getZ());
            var2.putInt(this.Objects.indexOf(var1));
            PacketType.RemoveItemFromSquare.send(GameClient.connection);
         }

         return GameServer.bServer ? GameServer.RemoveItemFromMap(var1) : this.RemoveTileObject(var1);
      } else {
         return -1;
      }
   }

    void transmitRemoveItemFromSquareOnServer(IsoObject var1) {
      if (var1 != nullptr && this.Objects.contains(var1)) {
         if (GameServer.bServer) {
            GameServer.RemoveItemFromMap(var1);
         }
      }
   }

    void transmitModdata() {
      if (GameClient.bClient) {
    ByteBufferWriter var1 = GameClient.connection.startPacket();
         PacketType.SendModData.doPacket(var1);
         var1.putInt(this.getX());
         var1.putInt(this.getY());
         var1.putInt(this.getZ());

         try {
            this.getModData().save(var1.bb);
         } catch (IOException var3) {
            var3.printStackTrace();
         }

         PacketType.SendModData.send(GameClient.connection);
      } else if (GameServer.bServer) {
         GameServer.loadModData(this);
      }
   }

    void AddWorldInventoryItem(const std::string& var1, float var2, float var3, float var4, int var5) {
      for (int var6 = 0; var6 < var5; var6++) {
         this.AddWorldInventoryItem(var1, var2, var3, var4);
      }
   }

    InventoryItem AddWorldInventoryItem(const std::string& var1, float var2, float var3, float var4) {
    InventoryItem var5 = InventoryItemFactory.CreateItem(var1);
      if (var5 == nullptr) {
    return nullptr;
      } else {
    IsoWorldInventoryObject var6 = std::make_shared<IsoWorldInventoryObject>(var5, this, var2, var3, var4);
         var5.setAutoAge();
         var5.setWorldItem(var6);
         var6.setKeyId(var5.getKeyId());
         var6.setName(var5.getName());
         this.Objects.push_back(var6);
         this.WorldObjects.push_back(var6);
         var6.square.chunk.recalcHashCodeObjects();
         if (GameClient.bClient) {
            var6.transmitCompleteItemToServer();
         }

         if (GameServer.bServer) {
            var6.transmitCompleteItemToClients();
         }

    return var5;
      }
   }

    InventoryItem AddWorldInventoryItem(InventoryItem var1, float var2, float var3, float var4) {
      return this.AddWorldInventoryItem(var1, var2, var3, var4, true);
   }

    InventoryItem AddWorldInventoryItem(InventoryItem var1, float var2, float var3, float var4, bool var5) {
      if (!var1.getFullType().contains(".Corpse")) {
         if (var1.getFullType().contains(".Generator")) {
    std::make_shared<IsoGenerator>();
    return var1;
         } else {
    IsoWorldInventoryObject var14 = std::make_shared<IsoWorldInventoryObject>(var1, this, var2, var3, var4);
            var14.setName(var1.getName());
            var14.setKeyId(var1.getKeyId());
            this.Objects.push_back(var14);
            this.WorldObjects.push_back(var14);
            var14.square.chunk.recalcHashCodeObjects();
            var1.setWorldItem(var14);
            var14.addToWorld();
            if (var5) {
               if (GameClient.bClient) {
                  var14.transmitCompleteItemToServer();
               }

               if (GameServer.bServer) {
                  var14.transmitCompleteItemToClients();
               }
            }

    return var1;
         }
      } else if (var1.byteData == nullptr) {
    IsoZombie var13 = std::make_shared<IsoZombie>(IsoWorld.instance.CurrentCell);
         var13.setDir(IsoDirections.fromIndex(Rand.Next(8)));
         var13.getForwardDirection().set(var13.dir.ToVector());
         var13.setFakeDead(false);
         var13.setHealth(0.0F);
         var13.upKillCount = false;
         var13.setX(this.x + var2);
         var13.setY(this.y + var3);
         var13.setZ(this.z);
         var13.square = this;
         var13.current = this;
         var13.dressInRandomOutfit();
         var13.DoZombieInventory();
    IsoDeadBody var15 = std::make_shared<IsoDeadBody>(var13, true);
         this.addCorpse(var15, false);
         if (GameServer.bServer) {
            GameServer.sendCorpse(var15);
         }

    return var1;
      } else {
    IsoDeadBody var6 = std::make_shared<IsoDeadBody>(IsoWorld.instance.CurrentCell);

         try {
    uint8_t var7 = var1.byteData.get();
    uint8_t var16 = var1.byteData.get();
    uint8_t var9 = var1.byteData.get();
    uint8_t var10 = var1.byteData.get();
    int var11 = 56;
            if (var7 == 87 && var16 == 86 && var9 == 69 && var10 == 82) {
               var11 = var1.byteData.getInt();
            } else {
               var1.byteData.rewind();
            }

            var6.load(var1.byteData, var11);
         } catch (IOException var12) {
            var12.printStackTrace();
    IsoZombie var8 = std::make_shared<IsoZombie>(nullptr);
            var8.dir = var6.dir;
            var8.current = this;
            var8.x = var6.x;
            var8.y = var6.y;
            var8.z = var6.z;
            var6 = std::make_shared<IsoDeadBody>(var8);
         }

         var6.setX(this.x + var2);
         var6.setY(this.y + var3);
         var6.setZ(this.z);
         var6.square = this;
         this.addCorpse(var6, false);
         if (GameServer.bServer) {
            GameServer.sendCorpse(var6);
         }

    return var1;
      }
   }

    void restackSheetRope() {
      if (this.Is(IsoFlagType.climbSheetW) || this.Is(IsoFlagType.climbSheetN) || this.Is(IsoFlagType.climbSheetE) || this.Is(IsoFlagType.climbSheetS)) {
         for (int var1 = 0; var1 < this.getObjects().size() - 1; var1++) {
    IsoObject var2 = (IsoObject)this.getObjects().get(var1);
            if (var2.getProperties() != nullptr
               && (
                  var2.getProperties().Is(IsoFlagType.climbSheetW)
                     || var2.getProperties().Is(IsoFlagType.climbSheetN)
                     || var2.getProperties().Is(IsoFlagType.climbSheetE)
                     || var2.getProperties().Is(IsoFlagType.climbSheetS)
               )) {
               if (GameServer.bServer) {
                  this.transmitRemoveItemFromSquare(var2);
                  this.Objects.push_back(var2);
                  var2.transmitCompleteItemToClients();
               } else if (!GameClient.bClient) {
                  this.Objects.remove(var2);
                  this.Objects.push_back(var2);
               }
               break;
            }
         }
      }
   }

    void Burn() {
      if (!GameServer.bServer && !GameClient.bClient || !ServerOptions.instance.NoFire.getValue()) {
         if (this.getCell() != nullptr) {
            this.BurnWalls(true);
            LuaEventManager.triggerEvent("OnGridBurnt", this);
         }
      }
   }

    void Burn(bool var1) {
      if (!GameServer.bServer && !GameClient.bClient || !ServerOptions.instance.NoFire.getValue()) {
         if (this.getCell() != nullptr) {
            this.BurnWalls(var1);
         }
      }
   }

    void BurnWalls(bool var1) {
      if (!GameClient.bClient) {
         if (GameServer.bServer && SafeHouse.isSafeHouse(this, nullptr, false) != nullptr) {
            if (ServerOptions.instance.NoFire.getValue()) {
               return;
            }

            if (!ServerOptions.instance.SafehouseAllowFire.getValue()) {
               return;
            }
         }

         for (int var2 = 0; var2 < this.SpecialObjects.size(); var2++) {
    IsoObject var3 = this.SpecialObjects.get(var2);
            if (dynamic_cast<IsoThumpable*>(var3) != nullptr && ((IsoThumpable)var3).haveSheetRope()) {
               ((IsoThumpable)var3).removeSheetRope(nullptr);
            }

            if (dynamic_cast<IsoWindow*>(var3) != nullptr) {
               if (((IsoWindow)var3).haveSheetRope()) {
                  ((IsoWindow)var3).removeSheetRope(nullptr);
               }

               ((IsoWindow)var3).removeSheet(nullptr);
            }

            if (IsoWindowFrame.isWindowFrame(var3) && IsoWindowFrame.haveSheetRope(var3)) {
               IsoWindowFrame.removeSheetRope(var3, nullptr);
            }

            if (dynamic_cast<BarricadeAble*>(var3) != nullptr) {
    IsoBarricade var4 = ((BarricadeAble)var3).getBarricadeOnSameSquare();
    IsoBarricade var5 = ((BarricadeAble)var3).getBarricadeOnOppositeSquare();
               if (var4 != nullptr) {
                  if (GameServer.bServer) {
                     GameServer.RemoveItemFromMap(var4);
                  } else {
                     this.RemoveTileObject(var4);
                  }
               }

               if (var5 != nullptr) {
                  if (GameServer.bServer) {
                     GameServer.RemoveItemFromMap(var5);
                  } else {
                     var5.getSquare().RemoveTileObject(var5);
                  }
               }
            }
         }

         this.SpecialObjects.clear();
    bool var10 = false;
         if (!this.getProperties().Is(IsoFlagType.burntOut)) {
    uint8_t var11 = 0;

            for (int var12 = 0; var12 < this.Objects.size(); var12++) {
    IsoObject var13 = (IsoObject)this.Objects.get(var12);
    bool var6 = false;
               if (var13.getSprite() != nullptr
                  && var13.getSprite().getName() != nullptr
                  && !var13.getSprite().getProperties().Is(IsoFlagType.water)
                  && !var13.getSprite().getName().contains("_burnt_")) {
                  if (dynamic_cast<IsoThumpable*>(var13) != nullptr && var13.getSprite().burntTile != nullptr) {
    IsoObject var17 = IsoObject.getNew();
                     var17.setSprite(IsoSpriteManager.instance.getSprite(var13.getSprite().burntTile));
                     var17.setSquare(this);
                     if (GameServer.bServer) {
                        var13.sendObjectChange("replaceWith", new Object[]{"object", var17});
                     }

                     var13.removeFromWorld();
                     this.Objects.set(var12, var17);
                  } else if (var13.getSprite().burntTile != nullptr) {
                     var13.sprite = IsoSpriteManager.instance.getSprite(var13.getSprite().burntTile);
                     var13.RemoveAttachedAnims();
                     if (var13.Children != nullptr) {
                        var13.Children.clear();
                     }

                     var13.transmitUpdatedSpriteToClients();
                     var13.setOverlaySprite(nullptr);
                  } else if (var13.getType() == IsoObjectType.tree) {
                     var13.sprite = IsoSpriteManager.instance.getSprite("fencing_burnt_01_" + (Rand.Next(15, 19) + 1));
                     var13.RemoveAttachedAnims();
                     if (var13.Children != nullptr) {
                        var13.Children.clear();
                     }

                     var13.transmitUpdatedSpriteToClients();
                     var13.setOverlaySprite(nullptr);
                  } else if (!(dynamic_cast<IsoTrap*>(var13) != nullptr)) {
                     if (!(dynamic_cast<IsoBarricade*>(var13) != nullptr) && !(dynamic_cast<IsoMannequin*>(var13) != nullptr)) {
                        if (dynamic_cast<IsoGenerator*>(var13) != nullptr var16) {
                           if (var16.getFuel() > 0.0F) {
                              var11 += 20;
                           }

                           if (var16.isActivated()) {
                              var16.activated = false;
                              var16.setSurroundingElectricity();
                              if (GameServer.bServer) {
                                 var16.syncIsoObject(false, (byte)0, nullptr, nullptr);
                              }
                           }

                           if (GameServer.bServer) {
                              GameServer.RemoveItemFromMap(var13);
                           } else {
                              this.RemoveTileObject(var13);
                           }

                           var12--;
                        } else {
                           if (var13.getType() == IsoObjectType.wall
                              && !var13.getProperties().Is(IsoFlagType.DoorWallW)
                              && !var13.getProperties().Is(IsoFlagType.DoorWallN)
                              && !var13.getProperties().Is("WindowN")
                              && !var13.getProperties().Is(IsoFlagType.WindowW)
                              && !var13.getSprite().getName().startsWith("walls_exterior_roofs_")
                              && !var13.getSprite().getName().startsWith("fencing_")
                              && !var13.getSprite().getName().startsWith("fixtures_railings_")) {
                              if (var13.getSprite().getProperties().Is(IsoFlagType.collideW) && !var13.getSprite().getProperties().Is(IsoFlagType.collideN)) {
                                 var13.sprite = IsoSpriteManager.instance.getSprite("walls_burnt_01_" + (Rand.Next(2) == 0 ? "0" : "4"));
                              } else if (var13.getSprite().getProperties().Is(IsoFlagType.collideN)
                                 && !var13.getSprite().getProperties().Is(IsoFlagType.collideW)) {
                                 var13.sprite = IsoSpriteManager.instance.getSprite("walls_burnt_01_" + (Rand.Next(2) == 0 ? "1" : "5"));
                              } else if (var13.getSprite().getProperties().Is(IsoFlagType.collideW)
                                 && var13.getSprite().getProperties().Is(IsoFlagType.collideN)) {
                                 var13.sprite = IsoSpriteManager.instance.getSprite("walls_burnt_01_" + (Rand.Next(2) == 0 ? "2" : "6"));
                              } else if (var13.getProperties().Is(IsoFlagType.WallSE)) {
                                 var13.sprite = IsoSpriteManager.instance.getSprite("walls_burnt_01_" + (Rand.Next(2) == 0 ? "3" : "7"));
                              }
                           } else {
                              if (dynamic_cast<IsoDoor*>(var13) != nullptr || dynamic_cast<IsoWindow*>(var13) != nullptr || dynamic_cast<IsoCurtain*>(var13) != nullptr) {
                                 if (GameServer.bServer) {
                                    GameServer.RemoveItemFromMap(var13);
                                 } else {
                                    this.RemoveTileObject(var13);
                                    var10 = true;
                                 }

                                 var12--;
                                 continue;
                              }

                              if (var13.getProperties().Is(IsoFlagType.WindowW)) {
                                 var13.sprite = IsoSpriteManager.instance.getSprite("walls_burnt_01_" + (Rand.Next(2) == 0 ? "8" : "12"));
                              } else if (var13.getProperties().Is("WindowN")) {
                                 var13.sprite = IsoSpriteManager.instance.getSprite("walls_burnt_01_" + (Rand.Next(2) == 0 ? "9" : "13"));
                              } else if (var13.getProperties().Is(IsoFlagType.DoorWallW)) {
                                 var13.sprite = IsoSpriteManager.instance.getSprite("walls_burnt_01_" + (Rand.Next(2) == 0 ? "10" : "14"));
                              } else if (var13.getProperties().Is(IsoFlagType.DoorWallN)) {
                                 var13.sprite = IsoSpriteManager.instance.getSprite("walls_burnt_01_" + (Rand.Next(2) == 0 ? "11" : "15"));
                              } else if (var13.getSprite().getProperties().Is(IsoFlagType.solidfloor)
                                 && !var13.getSprite().getProperties().Is(IsoFlagType.exterior)) {
                                 var13.sprite = IsoSpriteManager.instance.getSprite("floors_burnt_01_0");
                              } else {
                                 if (dynamic_cast<IsoWaveSignal*>(var13) != nullptr) {
                                    if (GameServer.bServer) {
                                       GameServer.RemoveItemFromMap(var13);
                                    } else {
                                       this.RemoveTileObject(var13);
                                       var10 = true;
                                    }

                                    var12--;
                                    continue;
                                 }

                                 if (var13.getContainer() != nullptr && var13.getContainer().getItems() != nullptr) {
    void* var7 = nullptr;

                                    for (int var8 = 0; var8 < var13.getContainer().getItems().size(); var8++) {
                                       var7 = (InventoryItem)var13.getContainer().getItems().get(var8);
                                       if (dynamic_cast<Food*>(var7) != nullptr && ((Food)var7).isAlcoholic()
                                          || var7.getType() == "PetrolCan")
                                          || var7.getType() == "Bleach")) {
                                          var11 += 20;
                                          if (var11 > 100) {
                                             var11 = 100;
                                             break;
                                          }
                                       }
                                    }

                                    var13.sprite = IsoSpriteManager.instance.getSprite("floors_burnt_01_" + Rand.Next(1, 2));

                                    for (int var18 = 0; var18 < var13.getContainerCount(); var18++) {
    ItemContainer var9 = var13.getContainerByIndex(var18);
                                       var9.removeItemsFromProcessItems();
                                       var9.removeAllItems();
                                    }

                                    var13.removeAllContainers();
                                    if (var13.getOverlaySprite() != nullptr) {
                                       var13.setOverlaySprite(nullptr);
                                    }

                                    var6 = true;
                                 } else if (var13.getSprite().getProperties().Is(IsoFlagType.solidtrans)
                                    || var13.getSprite().getProperties().Is(IsoFlagType.bed)
                                    || var13.getSprite().getProperties().Is(IsoFlagType.waterPiped)) {
                                    var13.sprite = IsoSpriteManager.instance.getSprite("floors_burnt_01_" + Rand.Next(1, 2));
                                    if (var13.getOverlaySprite() != nullptr) {
                                       var13.setOverlaySprite(nullptr);
                                    }
                                 } else if (var13.getSprite().getName().startsWith("walls_exterior_roofs_")) {
                                    var13.sprite = IsoSpriteManager.instance
                                       .getSprite(
                                          "walls_burnt_roofs_01_"
                                             + var13.getSprite()
                                                .getName()
                                                .substr(var13.getSprite().getName().lastIndexOf("_") + 1, var13.getSprite().getName().length())
                                       );
                                 } else if (!var13.getSprite().getName().startsWith("roofs_accents")) {
                                    if (var13.getSprite().getName().startsWith("roofs_")) {
                                       var13.sprite = IsoSpriteManager.instance
                                          .getSprite(
                                             "roofs_burnt_01_"
                                                + var13.getSprite()
                                                   .getName()
                                                   .substr(var13.getSprite().getName().lastIndexOf("_") + 1, var13.getSprite().getName().length())
                                          );
                                    } else if ((
                                          var13.getSprite().getName().startsWith("fencing_") || var13.getSprite().getName().startsWith("fixtures_railings_")
                                       )
                                       && (
                                          var13.getSprite().getProperties().Is(IsoFlagType.HoppableN)
                                             || var13.getSprite().getProperties().Is(IsoFlagType.HoppableW)
                                       )) {
                                       if (var13.getSprite().getProperties().Is(IsoFlagType.transparentW)
                                          && !var13.getSprite().getProperties().Is(IsoFlagType.transparentN)) {
                                          var13.sprite = IsoSpriteManager.instance.getSprite("fencing_burnt_01_0");
                                       } else if (var13.getSprite().getProperties().Is(IsoFlagType.transparentN)
                                          && !var13.getSprite().getProperties().Is(IsoFlagType.transparentW)) {
                                          var13.sprite = IsoSpriteManager.instance.getSprite("fencing_burnt_01_1");
                                       } else {
                                          var13.sprite = IsoSpriteManager.instance.getSprite("fencing_burnt_01_2");
                                       }
                                    }
                                 }
                              }
                           }

                           if (!var6 && !(dynamic_cast<IsoThumpable*>(var13) != nullptr)) {
                              var13.RemoveAttachedAnims();
                              var13.transmitUpdatedSpriteToClients();
                              var13.setOverlaySprite(nullptr);
                           } else {
    IsoObject var15 = IsoObject.getNew();
                              var15.setSprite(var13.getSprite());
                              var15.setSquare(this);
                              if (GameServer.bServer) {
                                 var13.sendObjectChange("replaceWith", new Object[]{"object", var15});
                              }

                              this.Objects.set(var12, var15);
                           }

                           if (var13.emitter != nullptr) {
                              var13.emitter.stopAll();
                              var13.emitter = nullptr;
                           }
                        }
                     } else {
                        if (GameServer.bServer) {
                           GameServer.RemoveItemFromMap(var13);
                        } else {
                           this.Objects.remove(var13);
                        }

                        var12--;
                     }
                  }
               }
            }

            if (var11 > 0 && var1) {
               if (GameServer.bServer) {
                  GameServer.PlayWorldSoundServer("BurnedObjectExploded", false, this, 0.0F, 50.0F, 1.0F, false);
               } else {
                  SoundManager.instance.PlayWorldSound("BurnedObjectExploded", this, 0.0F, 50.0F, 1.0F, false);
               }

               IsoFireManager.explode(this.getCell(), this, var11);
            }
         }

         if (!var10) {
            this.RecalcProperties();
         }

         this.getProperties().Set(IsoFlagType.burntOut);
         this.burntOut = true;
         MapCollisionData.instance.squareChanged(this);
         PolygonalMap2.instance.squareChanged(this);
      }
   }

    void BurnWallsTCOnly() {
      for (int var1 = 0; var1 < this.Objects.size(); var1++) {
    IsoObject var2 = (IsoObject)this.Objects.get(var1);
         if (var2.sprite == nullptr) {
         }
      }
   }

    void BurnTick() {
      if (!GameClient.bClient) {
         for (int var1 = 0; var1 < this.StaticMovingObjects.size(); var1++) {
    IsoMovingObject var2 = this.StaticMovingObjects.get(var1);
            if (dynamic_cast<IsoDeadBody*>(var2) != nullptr) {
               ((IsoDeadBody)var2).Burn();
               if (!this.StaticMovingObjects.contains(var2)) {
                  var1--;
               }
            }
         }
      }
   }

    bool CalculateCollide(IsoGridSquare var1, bool var2, bool var3, bool var4) {
      return this.CalculateCollide(var1, var2, var3, var4, false);
   }

    bool CalculateCollide(IsoGridSquare var1, bool var2, bool var3, bool var4, bool var5) {
      return this.CalculateCollide(var1, var2, var3, var4, var5, cellGetSquare);
   }

    bool CalculateCollide(IsoGridSquare var1, bool var2, bool var3, bool var4, bool var5, GetSquare var6) {
      if (var1 == nullptr && var3) {
    return true;
      } else if (var1 == nullptr) {
    return false;
      } else {
         if (var2 && var1.Properties.Is(IsoFlagType.trans)) {
         }

    bool var7 = false;
    bool var8 = false;
    bool var9 = false;
    bool var10 = false;
         if (var1.x < this.x) {
            var7 = true;
         }

         if (var1.y < this.y) {
            var9 = true;
         }

         if (var1.x > this.x) {
            var8 = true;
         }

         if (var1.y > this.y) {
            var10 = true;
         }

         if (!var5 && var1.Properties.Is(IsoFlagType.solid)) {
            return this.Has(IsoObjectType.stairsTW) && !var3 && var1.x < this.x && var1.y == this.y && var1.z == this.z
               ? false
               : !this.Has(IsoObjectType.stairsTN) || var3 || var1.x != this.x || var1.y >= this.y || var1.z != this.z;
         } else {
            if (!var4 && var1.Properties.Is(IsoFlagType.solidtrans)) {
               if (this.Has(IsoObjectType.stairsTW) && !var3 && var1.x < this.x && var1.y == this.y && var1.z == this.z) {
    return false;
               }

               if (this.Has(IsoObjectType.stairsTN) && !var3 && var1.x == this.x && var1.y < this.y && var1.z == this.z) {
    return false;
               }

    bool var11 = false;
               if (var1.Properties.Is(IsoFlagType.windowW) || var1.Properties.Is(IsoFlagType.windowN)) {
                  var11 = true;
               }

               if (!var11 && (var1.Properties.Is(IsoFlagType.WindowW) || var1.Properties.Is(IsoFlagType.WindowN))) {
                  var11 = true;
               }

               if (!var11) {
    IsoGridSquare var12 = var6.getGridSquare(var1.x, var1.y + 1, this.z);
                  if (var12 != nullptr && (var12.Is(IsoFlagType.windowN) || var12.Is(IsoFlagType.WindowN))) {
                     var11 = true;
                  }
               }

               if (!var11) {
    IsoGridSquare var21 = var6.getGridSquare(var1.x + 1, var1.y, this.z);
                  if (var21 != nullptr && (var21.Is(IsoFlagType.windowW) || var21.Is(IsoFlagType.WindowW))) {
                     var11 = true;
                  }
               }

               if (!var11) {
    return true;
               }
            }

            if (var1.x != this.x && var1.y != this.y && this.z != var1.z && var3) {
    return true;
            } else if (!var3 || var1.z >= this.z || (this.SolidFloorCached ? this.SolidFloor : this.TreatAsSolidFloor())) {
               if (var3 && var1.z == this.z) {
                  if (var1.x > this.x && var1.y == this.y && var1.Properties.Is(IsoFlagType.windowW)) {
    return false;
                  }

                  if (var1.y > this.y && var1.x == this.x && var1.Properties.Is(IsoFlagType.windowN)) {
    return false;
                  }

                  if (var1.x < this.x && var1.y == this.y && this.Properties.Is(IsoFlagType.windowW)) {
    return false;
                  }

                  if (var1.y < this.y && var1.x == this.x && this.Properties.Is(IsoFlagType.windowN)) {
    return false;
                  }
               }

               if (var1.x > this.x && var1.z < this.z && var1.Has(IsoObjectType.stairsTW)) {
    return false;
               } else if (var1.y > this.y && var1.z < this.z && var1.Has(IsoObjectType.stairsTN)) {
    return false;
               } else {
    IsoGridSquare var19 = var6.getGridSquare(var1.x, var1.y, var1.z - 1);
                  if (var1.x == this.x || var1.z != this.z || !var1.Has(IsoObjectType.stairsTN) || var19 != nullptr && var19.Has(IsoObjectType.stairsTN) && !var3) {
                     if (var1.y <= this.y
                        || var1.x != this.x
                        || var1.z != this.z
                        || !var1.Has(IsoObjectType.stairsTN)
                        || var19 != nullptr && var19.Has(IsoObjectType.stairsTN) && !var3) {
                        if (var1.x <= this.x
                           || var1.y != this.y
                           || var1.z != this.z
                           || !var1.Has(IsoObjectType.stairsTW)
                           || var19 != nullptr && var19.Has(IsoObjectType.stairsTW) && !var3) {
                           if (var1.y == this.y
                              || var1.z != this.z
                              || !var1.Has(IsoObjectType.stairsTW)
                              || var19 != nullptr && var19.Has(IsoObjectType.stairsTW) && !var3) {
                              if (var1.x != this.x && var1.z == this.z && var1.Has(IsoObjectType.stairsMN)) {
    return true;
                              } else if (var1.y != this.y && var1.z == this.z && var1.Has(IsoObjectType.stairsMW)) {
    return true;
                              } else if (var1.x != this.x && var1.z == this.z && var1.Has(IsoObjectType.stairsBN)) {
    return true;
                              } else if (var1.y != this.y && var1.z == this.z && var1.Has(IsoObjectType.stairsBW)) {
    return true;
                              } else if (var1.x != this.x && var1.z == this.z && this.Has(IsoObjectType.stairsTN)) {
    return true;
                              } else if (var1.y != this.y && var1.z == this.z && this.Has(IsoObjectType.stairsTW)) {
    return true;
                              } else if (var1.x != this.x && var1.z == this.z && this.Has(IsoObjectType.stairsMN)) {
    return true;
                              } else if (var1.y != this.y && var1.z == this.z && this.Has(IsoObjectType.stairsMW)) {
    return true;
                              } else if (var1.x != this.x && var1.z == this.z && this.Has(IsoObjectType.stairsBN)) {
    return true;
                              } else if (var1.y != this.y && var1.z == this.z && this.Has(IsoObjectType.stairsBW)) {
    return true;
                              } else if (var1.y < this.y && var1.x == this.x && var1.z > this.z && this.Has(IsoObjectType.stairsTN)) {
    return false;
                              } else if (var1.x < this.x && var1.y == this.y && var1.z > this.z && this.Has(IsoObjectType.stairsTW)) {
    return false;
                              } else if (var1.y > this.y && var1.x == this.x && var1.z < this.z && var1.Has(IsoObjectType.stairsTN)) {
    return false;
                              } else if (var1.x > this.x && var1.y == this.y && var1.z < this.z && var1.Has(IsoObjectType.stairsTW)) {
    return false;
                              } else if (var1.z == this.z && (var1.SolidFloorCached ? !var1.SolidFloor : !var1.TreatAsSolidFloor()) && var3) {
    return true;
                              } else {
                                 if (var1.z == this.z && (var1.SolidFloorCached ? !var1.SolidFloor : !var1.TreatAsSolidFloor()) && var1.z > 0) {
                                    var19 = var6.getGridSquare(var1.x, var1.y, var1.z - 1);
                                    if (var19 == nullptr) {
    return true;
                                    }
                                 }

                                 if (this.z == var1.z) {
    bool var22 = var9 && this.Properties.Is(IsoFlagType.collideN);
    bool var13 = var7 && this.Properties.Is(IsoFlagType.collideW);
    bool var14 = var10 && var1.Properties.Is(IsoFlagType.collideN);
    bool var15 = var8 && var1.Properties.Is(IsoFlagType.collideW);
                                    if (var22 && var3 && this.Properties.Is(IsoFlagType.canPathN)) {
                                       var22 = false;
                                    }

                                    if (var13 && var3 && this.Properties.Is(IsoFlagType.canPathW)) {
                                       var13 = false;
                                    }

                                    if (var14 && var3 && var1.Properties.Is(IsoFlagType.canPathN)) {
                                       var14 = false;
                                    }

                                    if (var15 && var3 && var1.Properties.Is(IsoFlagType.canPathW)) {
                                       var15 = false;
                                    }

                                    if (var13 && this.Has(IsoObjectType.stairsTW) && !var3) {
                                       var13 = false;
                                    }

                                    if (var22 && this.Has(IsoObjectType.stairsTN) && !var3) {
                                       var22 = false;
                                    }

                                    if (!var22 && !var13 && !var14 && !var15) {
    bool var16 = var1.x != this.x && var1.y != this.y;
                                       if (var16) {
    IsoGridSquare var17 = var6.getGridSquare(this.x, var1.y, this.z);
    IsoGridSquare var18 = var6.getGridSquare(var1.x, this.y, this.z);
                                          if (var17 != nullptr && var17 != this && var17 != var1) {
                                             var17.RecalcPropertiesIfNeeded();
                                          }

                                          if (var18 != nullptr && var18 != this && var18 != var1) {
                                             var18.RecalcPropertiesIfNeeded();
                                          }

                                          if (var1 == this || var17 == var18 || var17 == this || var18 == this || var17 == var1 || var18 == var1) {
    return true;
                                          }

                                          if (var1.x == this.x + 1
                                             && var1.y == this.y + 1
                                             && var17 != nullptr
                                             && var18 != nullptr
                                             && var17.Is(IsoFlagType.windowN)
                                             && var18.Is(IsoFlagType.windowW)) {
    return true;
                                          }

                                          if (var1.x == this.x - 1
                                             && var1.y == this.y - 1
                                             && var17 != nullptr
                                             && var18 != nullptr
                                             && var17.Is(IsoFlagType.windowW)
                                             && var18.Is(IsoFlagType.windowN)) {
    return true;
                                          }

                                          if (this.CalculateCollide(var17, var2, var3, var4, false, var6)) {
    return true;
                                          }

                                          if (this.CalculateCollide(var18, var2, var3, var4, false, var6)) {
    return true;
                                          }

                                          if (var1.CalculateCollide(var17, var2, var3, var4, false, var6)) {
    return true;
                                          }

                                          if (var1.CalculateCollide(var18, var2, var3, var4, false, var6)) {
    return true;
                                          }
                                       }

    return false;
                                    } else {
    return true;
                                    }
                                 } else {
                                    return var1.z >= this.z
                                       || var1.x != this.x
                                       || var1.y != this.y
                                       || (this.SolidFloorCached ? this.SolidFloor : this.TreatAsSolidFloor());
                                 }
                              }
                           } else {
    return true;
                           }
                        } else {
    return true;
                        }
                     } else {
    return true;
                     }
                  } else {
    return true;
                  }
               }
            } else {
               return var1.Has(IsoObjectType.stairsTN) || var1.Has(IsoObjectType.stairsTW);
            }
         }
      }
   }

    bool CalculateVisionBlocked(IsoGridSquare var1) {
      return this.CalculateVisionBlocked(var1, cellGetSquare);
   }

    bool CalculateVisionBlocked(IsoGridSquare var1, GetSquare var2) {
      if (var1 == nullptr) {
    return false;
      } else if (Math.abs(var1.getX() - this.getX()) <= 1 && Math.abs(var1.getY() - this.getY()) <= 1) {
    bool var3 = false;
    bool var4 = false;
    bool var5 = false;
    bool var6 = false;
         if (var1.x < this.x) {
            var3 = true;
         }

         if (var1.y < this.y) {
            var5 = true;
         }

         if (var1.x > this.x) {
            var4 = true;
         }

         if (var1.y > this.y) {
            var6 = true;
         }

         if (!var1.Properties.Is(IsoFlagType.trans) && !this.Properties.Is(IsoFlagType.trans)) {
            if (this.z != var1.z) {
               if (var1.z > this.z) {
                  if ((var1.SolidFloorCached ? var1.SolidFloor : var1.TreatAsSolidFloor()) && !var1.getProperties().Is(IsoFlagType.transparentFloor)) {
    return true;
                  }

                  if (this.Properties.Is(IsoFlagType.noStart)) {
    return true;
                  }

    IsoGridSquare var7 = var2.getGridSquare(this.x, this.y, var1.z);
                  if (var7 == nullptr) {
    return false;
                  }

                  if ((var7.SolidFloorCached ? var7.SolidFloor : var7.TreatAsSolidFloor()) && !var7.getProperties().Is(IsoFlagType.transparentFloor)) {
    return true;
                  }
               } else {
                  if ((this.SolidFloorCached ? this.SolidFloor : this.TreatAsSolidFloor()) && !this.getProperties().Is(IsoFlagType.transparentFloor)) {
    return true;
                  }

                  if (this.Properties.Is(IsoFlagType.noStart)) {
    return true;
                  }

    IsoGridSquare var14 = var2.getGridSquare(var1.x, var1.y, this.z);
                  if (var14 == nullptr) {
    return false;
                  }

                  if ((var14.SolidFloorCached ? var14.SolidFloor : var14.TreatAsSolidFloor()) && !var14.getProperties().Is(IsoFlagType.transparentFloor)) {
    return true;
                  }
               }
            }

            if (var1.x > this.x && var1.Properties.Is(IsoFlagType.transparentW)) {
    return false;
            } else if (var1.y > this.y && var1.Properties.Is(IsoFlagType.transparentN)) {
    return false;
            } else if (var1.x < this.x && this.Properties.Is(IsoFlagType.transparentW)) {
    return false;
            } else if (var1.y < this.y && this.Properties.Is(IsoFlagType.transparentN)) {
    return false;
            } else if (var1.x > this.x && var1.Properties.Is(IsoFlagType.doorW)) {
    return false;
            } else if (var1.y > this.y && var1.Properties.Is(IsoFlagType.doorN)) {
    return false;
            } else if (var1.x < this.x && this.Properties.Is(IsoFlagType.doorW)) {
    return false;
            } else if (var1.y < this.y && this.Properties.Is(IsoFlagType.doorN)) {
    return false;
            } else {
    bool var15 = var5 && this.Properties.Is(IsoFlagType.collideN);
    bool var8 = var3 && this.Properties.Is(IsoFlagType.collideW);
    bool var9 = var6 && var1.Properties.Is(IsoFlagType.collideN);
    bool var10 = var4 && var1.Properties.Is(IsoFlagType.collideW);
               if (!var15 && !var8 && !var9 && !var10) {
    bool var11 = var1.x != this.x && var1.y != this.y;
                  if (!var1.Properties.Is(IsoFlagType.solid) && !var1.Properties.Is(IsoFlagType.blocksight)) {
                     if (var11) {
    IsoGridSquare var12 = var2.getGridSquare(this.x, var1.y, this.z);
    IsoGridSquare var13 = var2.getGridSquare(var1.x, this.y, this.z);
                        if (var12 != nullptr && var12 != this && var12 != var1) {
                           var12.RecalcPropertiesIfNeeded();
                        }

                        if (var13 != nullptr && var13 != this && var13 != var1) {
                           var13.RecalcPropertiesIfNeeded();
                        }

                        if (this.CalculateVisionBlocked(var12)) {
    return true;
                        }

                        if (this.CalculateVisionBlocked(var13)) {
    return true;
                        }

                        if (var1.CalculateVisionBlocked(var12)) {
    return true;
                        }

                        if (var1.CalculateVisionBlocked(var13)) {
    return true;
                        }
                     }

    return false;
                  } else {
    return true;
                  }
               } else {
    return true;
               }
            }
         } else {
    return false;
         }
      } else {
    return true;
      }
   }

    IsoGameCharacter FindFriend(IsoGameCharacter var1, int var2, std::stack<IsoGameCharacter> var3) {
    std::stack var4 = new std::stack();

      for (int var5 = 0; var5 < var1.getLocalList().size(); var5++) {
    IsoMovingObject var6 = (IsoMovingObject)var1.getLocalList().get(var5);
         if (var6 != var1 && var6 != var1.getFollowingTarget() && dynamic_cast<IsoGameCharacter*>(var6) != nullptr && !(dynamic_cast<IsoZombie*>(var6) != nullptr) && !var3.contains(var6)) {
            var4.push_back((IsoGameCharacter)var6);
         }
      }

    float var10 = 1000000.0F;
    IsoGameCharacter var11 = nullptr;

    for (auto& var8 : var4)    float var9 = 0.0F;
         var9 += Math.abs(this.getX() - var8.getX());
         var9 += Math.abs(this.getY() - var8.getY());
         var9 += Math.abs(this.getZ() - var8.getZ());
         if (var9 < var10) {
            var11 = var8;
            var10 = var9;
         }

         if (var8 == IsoPlayer.getInstance()) {
            var11 = var8;
            var9 = 0.0F;
         }
      }

      return var10 > var2 ? nullptr : var11;
   }

    IsoGameCharacter FindEnemy(IsoGameCharacter var1, int var2, std::vector<IsoMovingObject> var3, IsoGameCharacter var4, int var5) {
    float var6 = 1000000.0F;
    IsoGameCharacter var7 = nullptr;

      for (int var8 = 0; var8 < var3.size(); var8++) {
    IsoGameCharacter var9 = (IsoGameCharacter)var3.get(var8);
    float var10 = 0.0F;
         var10 += Math.abs(this.getX() - var9.getX());
         var10 += Math.abs(this.getY() - var9.getY());
         var10 += Math.abs(this.getZ() - var9.getZ());
         if (var10 < var2 && var10 < var6 && var9.DistTo(var4) < var5) {
            var7 = var9;
            var6 = var10;
         }
      }

      return var6 > var2 ? nullptr : var7;
   }

    IsoGameCharacter FindEnemy(IsoGameCharacter var1, int var2, std::vector<IsoMovingObject> var3) {
    float var4 = 1000000.0F;
    IsoGameCharacter var5 = nullptr;

      for (int var6 = 0; var6 < var3.size(); var6++) {
    IsoGameCharacter var7 = (IsoGameCharacter)var3.get(var6);
    float var8 = 0.0F;
         var8 += Math.abs(this.getX() - var7.getX());
         var8 += Math.abs(this.getY() - var7.getY());
         var8 += Math.abs(this.getZ() - var7.getZ());
         if (var8 < var4) {
            var5 = var7;
            var4 = var8;
         }
      }

      return var4 > var2 ? nullptr : var5;
   }

    int getX() {
      return this.x;
   }

    int getY() {
      return this.y;
   }

    int getZ() {
      return this.z;
   }

    void RecalcProperties() {
      this.CachedIsFree = false;
    std::string var1 = nullptr;
      if (this.Properties.Is("waterAmount")) {
         var1 = this.Properties.Val("waterAmount");
      }

    std::string var2 = nullptr;
      if (this.Properties.Is("fuelAmount")) {
         var2 = this.Properties.Val("fuelAmount");
      }

      if (this.zone == nullptr) {
         this.zone = IsoWorld.instance.MetaGrid.getZoneAt(this.x, this.y, this.z);
      }

      this.Properties.Clear();
      this.hasTypes.clear();
      this.hasTree = false;
    bool var3 = false;
    bool var4 = false;
    bool var5 = false;
    bool var6 = false;
    bool var7 = false;
    bool var8 = false;
    bool var9 = false;
    bool var10 = false;
    int var11 = this.Objects.size();
      IsoObject[] var12 = (IsoObject[])this.Objects.getElements();

      for (int var13 = 0; var13 < var11; var13++) {
    IsoObject var14 = var12[var13];
         if (var14 != nullptr) {
    PropertyContainer var15 = var14.getProperties();
            if (var15 != nullptr && !var15.Is(IsoFlagType.blueprint)) {
               if (var14.sprite.forceRender) {
                  var10 = true;
               }

               if (var14.getType() == IsoObjectType.tree) {
                  this.hasTree = true;
               }

               this.hasTypes.set(var14.getType(), true);
               this.Properties.AddProperties(var15);
               if (var15.Is(IsoFlagType.water)) {
                  var4 = false;
               } else {
                  if (!var4 && var15.Is(IsoFlagType.solidfloor)) {
                     var4 = true;
                  }

                  if (!var3 && var15.Is(IsoFlagType.solidtrans)) {
                     var3 = true;
                  }

                  if (!var5 && var15.Is(IsoFlagType.solidfloor) && !var15.Is(IsoFlagType.transparentFloor)) {
                     var5 = true;
                  }
               }

               if (!var6 && var15.Is(IsoFlagType.collideN) && !var15.Is(IsoFlagType.HoppableN)) {
                  var6 = true;
               }

               if (!var7 && var15.Is(IsoFlagType.collideW) && !var15.Is(IsoFlagType.HoppableW)) {
                  var7 = true;
               }

               if (!var8 && var15.Is(IsoFlagType.cutN) && !var15.Is(IsoFlagType.transparentN)) {
                  var8 = true;
               }

               if (!var9 && var15.Is(IsoFlagType.cutW) && !var15.Is(IsoFlagType.transparentW)) {
                  var9 = true;
               }
            }
         }
      }

      if (this.roomID == -1 && !this.haveRoof) {
         this.getProperties().Set(IsoFlagType.exterior);

         try {
            this.getPuddles().bRecalc = true;
         } catch (Exception var16) {
            var16.printStackTrace();
         }
      } else {
         this.getProperties().UnSet(IsoFlagType.exterior);

         try {
            this.getPuddles().bRecalc = true;
         } catch (Exception var17) {
            var17.printStackTrace();
         }
      }

      if (var1 != nullptr) {
         this.getProperties().Set("waterAmount", var1, false);
      }

      if (var2 != nullptr) {
         this.getProperties().Set("fuelAmount", var2, false);
      }

      if (this.RainDrop != nullptr) {
         this.Properties.Set(IsoFlagType.HasRaindrop);
      }

      if (var10) {
         this.Properties.Set(IsoFlagType.forceRender);
      }

      if (this.RainSplash != nullptr) {
         this.Properties.Set(IsoFlagType.HasRainSplashes);
      }

      if (this.burntOut) {
         this.Properties.Set(IsoFlagType.burntOut);
      }

      if (!var3 && var4 && this.Properties.Is(IsoFlagType.water)) {
         this.Properties.UnSet(IsoFlagType.solidtrans);
      }

      if (var5 && this.Properties.Is(IsoFlagType.transparentFloor)) {
         this.Properties.UnSet(IsoFlagType.transparentFloor);
      }

      if (var6 && this.Properties.Is(IsoFlagType.HoppableN)) {
         this.Properties.UnSet(IsoFlagType.canPathN);
         this.Properties.UnSet(IsoFlagType.HoppableN);
      }

      if (var7 && this.Properties.Is(IsoFlagType.HoppableW)) {
         this.Properties.UnSet(IsoFlagType.canPathW);
         this.Properties.UnSet(IsoFlagType.HoppableW);
      }

      if (var8 && this.Properties.Is(IsoFlagType.transparentN)) {
         this.Properties.UnSet(IsoFlagType.transparentN);
      }

      if (var9 && this.Properties.Is(IsoFlagType.transparentW)) {
         this.Properties.UnSet(IsoFlagType.transparentW);
      }

      this.propertiesDirty = this.chunk == nullptr || this.chunk.bLoaded;
      if (this.chunk != nullptr) {
         this.chunk.lightCheck[0] = this.chunk.lightCheck[1] = this.chunk.lightCheck[2] = this.chunk.lightCheck[3] = true;
      }

      if (this.chunk != nullptr) {
         this.chunk.physicsCheck = true;
         this.chunk.collision.clear();
      }

      this.isExteriorCache = this.Is(IsoFlagType.exterior);
      this.isSolidFloorCache = this.Is(IsoFlagType.solidfloor);
      this.isVegitationCache = this.Is(IsoFlagType.vegitation);
   }

    void RecalcPropertiesIfNeeded() {
      if (this.propertiesDirty) {
         this.RecalcProperties();
      }
   }

    void ReCalculateCollide(IsoGridSquare var1) {
      this.ReCalculateCollide(var1, cellGetSquare);
   }

    void ReCalculateCollide(IsoGridSquare var1, GetSquare var2) {
      if (1 + (var1.x - this.x) < 0 || 1 + (var1.y - this.y) < 0 || 1 + (var1.z - this.z) < 0) {
         DebugLog.log("ERROR");
      }

    bool var3 = this.CalculateCollide(var1, false, false, false, false, var2);
      this.collideMatrix = setMatrixBit(this.collideMatrix, 1 + (var1.x - this.x), 1 + (var1.y - this.y), 1 + (var1.z - this.z), var3);
   }

    void ReCalculatePathFind(IsoGridSquare var1) {
      this.ReCalculatePathFind(var1, cellGetSquare);
   }

    void ReCalculatePathFind(IsoGridSquare var1, GetSquare var2) {
    bool var3 = this.CalculateCollide(var1, false, true, false, false, var2);
      this.pathMatrix = setMatrixBit(this.pathMatrix, 1 + (var1.x - this.x), 1 + (var1.y - this.y), 1 + (var1.z - this.z), var3);
   }

    void ReCalculateVisionBlocked(IsoGridSquare var1) {
      this.ReCalculateVisionBlocked(var1, cellGetSquare);
   }

    void ReCalculateVisionBlocked(IsoGridSquare var1, GetSquare var2) {
    bool var3 = this.CalculateVisionBlocked(var1, var2);
      this.visionMatrix = setMatrixBit(this.visionMatrix, 1 + (var1.x - this.x), 1 + (var1.y - this.y), 1 + (var1.z - this.z), var3);
   }

    static bool testCollideSpecialObjects(IsoMovingObject var0, IsoGridSquare var1, IsoGridSquare var2) {
      for (int var3 = 0; var3 < var2.SpecialObjects.size(); var3++) {
    IsoObject var4 = var2.SpecialObjects.get(var3);
         if (var4.TestCollide(var0, var1, var2)) {
            if (dynamic_cast<IsoDoor*>(var4) != nullptr) {
               var0.setCollidedWithDoor(true);
            } else if (dynamic_cast<IsoThumpable*>(var4) != nullptr && ((IsoThumpable)var4).isDoor) {
               var0.setCollidedWithDoor(true);
            }

            var0.setCollidedObject(var4);
    return true;
         }
      }

    return false;
   }

    bool testCollideAdjacent(IsoMovingObject var1, int var2, int var3, int var4) {
      if (dynamic_cast<IsoPlayer*>(var1) != nullptr && ((IsoPlayer)var1).isNoClip()) {
    return false;
      } else if (this.collideMatrix == -1) {
    return true;
      } else if (var2 >= -1 && var2 <= 1 && var3 >= -1 && var3 <= 1 && var4 >= -1 && var4 <= 1) {
         if (this.x + var2 >= 0 && this.y + var3 >= 0 && IsoWorld.instance.MetaGrid.isValidChunk((this.x + var2) / 10, (this.y + var3) / 10)) {
    IsoGridSquare var5 = this.getCell().getGridSquare(this.x + var2, this.y + var3, this.z + var4);
    SafeHouse var6 = nullptr;
            if ((GameServer.bServer || GameClient.bClient) && dynamic_cast<IsoPlayer*>(var1) != nullptr && !ServerOptions.instance.SafehouseAllowTrepass.getValue()) {
    IsoGridSquare var7 = this.getCell().getGridSquare(this.x + var2, this.y + var3, 0);
               var6 = SafeHouse.isSafeHouse(var7, ((IsoPlayer)var1).getUsername(), true);
            }

            if (var6 != nullptr) {
    return true;
            } else {
               if (var5 != nullptr && var1 != nullptr) {
    IsoObject var8 = this.testCollideSpecialObjects(var5);
                  if (var8 != nullptr) {
                     var1.collideWith(var8);
                     if (dynamic_cast<IsoDoor*>(var8) != nullptr) {
                        var1.setCollidedWithDoor(true);
                     } else if (dynamic_cast<IsoThumpable*>(var8) != nullptr && ((IsoThumpable)var8).isDoor) {
                        var1.setCollidedWithDoor(true);
                     }

                     var1.setCollidedObject(var8);
    return true;
                  }
               }

               if (UseSlowCollision) {
                  return this.CalculateCollide(var5, false, false, false);
               } else {
                  if (dynamic_cast<IsoPlayer*>(var1) != nullptr && getMatrixBit(this.collideMatrix, var2 + 1, var3 + 1, var4 + 1)) {
                     this.RecalcAllWithNeighbours(true);
                  }

    return getMatrixBit(var2 +, var3 +, var4 +);
               }
            }
         } else {
    return true;
         }
      } else {
    return true;
      }
   }

    bool testCollideAdjacentAdvanced(int var1, int var2, int var3, bool var4) {
      if (this.collideMatrix == -1) {
    return true;
      } else if (var1 >= -1 && var1 <= 1 && var2 >= -1 && var2 <= 1 && var3 >= -1 && var3 <= 1) {
    IsoGridSquare var5 = this.getCell().getGridSquare(this.x + var1, this.y + var2, this.z + var3);
         if (var5 != nullptr) {
            if (!var5.SpecialObjects.empty()) {
               for (int var6 = 0; var6 < var5.SpecialObjects.size(); var6++) {
    IsoObject var7 = var5.SpecialObjects.get(var6);
                  if (var7.TestCollide(nullptr, this, var5)) {
    return true;
                  }
               }
            }

            if (!this.SpecialObjects.empty()) {
               for (int var8 = 0; var8 < this.SpecialObjects.size(); var8++) {
    IsoObject var9 = this.SpecialObjects.get(var8);
                  if (var9.TestCollide(nullptr, this, var5)) {
    return true;
                  }
               }
            }
         }

         return UseSlowCollision ? this.CalculateCollide(var5, false, false, false) : getMatrixBit(this.collideMatrix, var1 + 1, var2 + 1, var3 + 1);
      } else {
    return true;
      }
   }

    static void setCollisionMode() {
      UseSlowCollision = !UseSlowCollision;
   }

    bool testPathFindAdjacent(IsoMovingObject var1, int var2, int var3, int var4) {
      return this.testPathFindAdjacent(var1, var2, var3, var4, cellGetSquare);
   }

    bool testPathFindAdjacent(IsoMovingObject var1, int var2, int var3, int var4, GetSquare var5) {
      if (var2 >= -1 && var2 <= 1 && var3 >= -1 && var3 <= 1 && var4 >= -1 && var4 <= 1) {
         if (this.Has(IsoObjectType.stairsTN) || this.Has(IsoObjectType.stairsTW)) {
    IsoGridSquare var6 = var5.getGridSquare(var2 + this.x, var3 + this.y, var4 + this.z);
            if (var6 == nullptr) {
    return true;
            }

            if (this.Has(IsoObjectType.stairsTN) && var6.y < this.y && var6.z == this.z) {
    return true;
            }

            if (this.Has(IsoObjectType.stairsTW) && var6.x < this.x && var6.z == this.z) {
    return true;
            }
         }

         if (bDoSlowPathfinding) {
    IsoGridSquare var7 = var5.getGridSquare(var2 + this.x, var3 + this.y, var4 + this.z);
            return this.CalculateCollide(var7, false, true, false, false, var5);
         } else {
    return getMatrixBit(var2 +, var3 +, var4 +);
         }
      } else {
    return true;
      }
   }

    TestResults testVisionAdjacent(int var1, int var2, int var3, bool var4, bool var5) {
      if (var1 >= -1 && var1 <= 1 && var2 >= -1 && var2 <= 1 && var3 >= -1 && var3 <= 1) {
         if (var3 == 1 && (var1 != 0 || var2 != 0) && this.HasElevatedFloor()) {
    IsoGridSquare var6 = this.getCell().getGridSquare(this.x, this.y, this.z + var3);
            if (var6 != nullptr) {
               return var6.testVisionAdjacent(var1, var2, 0, var4, var5);
            }
         }

         if (var3 == -1 && (var1 != 0 || var2 != 0)) {
    IsoGridSquare var12 = this.getCell().getGridSquare(this.x + var1, this.y + var2, this.z + var3);
            if (var12 != nullptr && var12.HasElevatedFloor()) {
               return this.testVisionAdjacent(var1, var2, 0, var4, var5);
            }
         }

    TestResults var13 = TestResults.Clear;
         if (var1 != 0 && var2 != 0 && var4) {
            var13 = this.DoDiagnalCheck(var1, var2, var3, var5);
            if (var13 == TestResults.Clear
               || var13 == TestResults.ClearThroughWindow
               || var13 == TestResults.ClearThroughOpenDoor
               || var13 == TestResults.ClearThroughClosedDoor) {
    IsoGridSquare var15 = this.getCell().getGridSquare(this.x + var1, this.y + var2, this.z + var3);
               if (var15 != nullptr) {
                  var13 = var15.DoDiagnalCheck(-var1, -var2, -var3, var5);
               }
            }

    return var13;
         } else {
    IsoGridSquare var7 = this.getCell().getGridSquare(this.x + var1, this.y + var2, this.z + var3);
    TestResults var8 = TestResults.Clear;
            if (var7 != nullptr && var7.z == this.z) {
               if (!this.SpecialObjects.empty()) {
                  for (int var9 = 0; var9 < this.SpecialObjects.size(); var9++) {
    IsoObject var10 = this.SpecialObjects.get(var9);
                     if (var10 == nullptr) {
                        return TestResults.Clear;
                     }

    VisionResult var11 = var10.TestVision(this, var7);
                     if (var11 != VisionResult.NoEffect) {
                        if (var11 == VisionResult.Unblocked && dynamic_cast<IsoDoor*>(var10) != nullptr) {
                           var8 = ((IsoDoor)var10).IsOpen() ? TestResults.ClearThroughOpenDoor : TestResults.ClearThroughClosedDoor;
                        } else if (var11 == VisionResult.Unblocked && dynamic_cast<IsoThumpable*>(var10) != nullptr && ((IsoThumpable)var10).isDoor) {
                           var8 = TestResults.ClearThroughOpenDoor;
                        } else if (var11 == VisionResult.Unblocked && dynamic_cast<IsoWindow*>(var10) != nullptr) {
                           var8 = TestResults.ClearThroughWindow;
                        } else {
                           if (var11 == VisionResult.Blocked && dynamic_cast<IsoDoor*>(var10) != nullptr && !var5) {
                              return TestResults.Blocked;
                           }

                           if (var11 == VisionResult.Blocked && dynamic_cast<IsoThumpable*>(var10) != nullptr && ((IsoThumpable)var10).isDoor && !var5) {
                              return TestResults.Blocked;
                           }

                           if (var11 == VisionResult.Blocked && dynamic_cast<IsoThumpable*>(var10) != nullptr && ((IsoThumpable)var10).isWindow()) {
                              return TestResults.Blocked;
                           }

                           if (var11 == VisionResult.Blocked && dynamic_cast<IsoCurtain*>(var10) != nullptr) {
                              return TestResults.Blocked;
                           }

                           if (var11 == VisionResult.Blocked && dynamic_cast<IsoWindow*>(var10) != nullptr) {
                              return TestResults.Blocked;
                           }

                           if (var11 == VisionResult.Blocked && dynamic_cast<IsoBarricade*>(var10) != nullptr) {
                              return TestResults.Blocked;
                           }
                        }
                     }
                  }
               }

               if (!var7.SpecialObjects.empty()) {
                  for (int var16 = 0; var16 < var7.SpecialObjects.size(); var16++) {
    IsoObject var17 = var7.SpecialObjects.get(var16);
                     if (var17 == nullptr) {
                        return TestResults.Clear;
                     }

    VisionResult var18 = var17.TestVision(this, var7);
                     if (var18 != VisionResult.NoEffect) {
                        if (var18 == VisionResult.Unblocked && dynamic_cast<IsoDoor*>(var17) != nullptr) {
                           var8 = ((IsoDoor)var17).IsOpen() ? TestResults.ClearThroughOpenDoor : TestResults.ClearThroughClosedDoor;
                        } else if (var18 == VisionResult.Unblocked && dynamic_cast<IsoThumpable*>(var17) != nullptr && ((IsoThumpable)var17).isDoor) {
                           var8 = TestResults.ClearThroughOpenDoor;
                        } else if (var18 == VisionResult.Unblocked && dynamic_cast<IsoWindow*>(var17) != nullptr) {
                           var8 = TestResults.ClearThroughWindow;
                        } else {
                           if (var18 == VisionResult.Blocked && dynamic_cast<IsoDoor*>(var17) != nullptr && !var5) {
                              return TestResults.Blocked;
                           }

                           if (var18 == VisionResult.Blocked && dynamic_cast<IsoThumpable*>(var17) != nullptr && ((IsoThumpable)var17).isDoor && !var5) {
                              return TestResults.Blocked;
                           }

                           if (var18 == VisionResult.Blocked && dynamic_cast<IsoThumpable*>(var17) != nullptr && ((IsoThumpable)var17).isWindow()) {
                              return TestResults.Blocked;
                           }

                           if (var18 == VisionResult.Blocked && dynamic_cast<IsoCurtain*>(var17) != nullptr) {
                              return TestResults.Blocked;
                           }

                           if (var18 == VisionResult.Blocked && dynamic_cast<IsoWindow*>(var17) != nullptr) {
                              return TestResults.Blocked;
                           }

                           if (var18 == VisionResult.Blocked && dynamic_cast<IsoBarricade*>(var17) != nullptr) {
                              return TestResults.Blocked;
                           }
                        }
                     }
                  }
               }
            }

            return !getMatrixBit(this.visionMatrix, var1 + 1, var2 + 1, var3 + 1) ? var8 : TestResults.Blocked;
         }
      } else {
         return TestResults.Blocked;
      }
   }

    bool TreatAsSolidFloor() {
      if (this.SolidFloorCached) {
         return this.SolidFloor;
      } else {
         if (!this.Properties.Is(IsoFlagType.solidfloor) && !this.HasStairs()) {
            this.SolidFloor = false;
         } else {
            this.SolidFloor = true;
         }

         this.SolidFloorCached = true;
         return this.SolidFloor;
      }
   }

    void AddSpecialTileObject(IsoObject var1) {
      this.AddSpecialObject(var1);
   }

    void renderCharacters(int var1, bool var2, bool var3) {
      if (this.z < var1) {
         if (!isOnScreenLast) {
         }

         if (var3) {
            IndieGL.glBlendFunc(770, 771);
         }

         if (this.MovingObjects.size() > 1) {
            Collections.sort(this.MovingObjects, comp);
         }

    int var4 = IsoCamera.frameState.playerIndex;
    ColorInfo var5 = this.lightInfo[var4];
    int var6 = this.StaticMovingObjects.size();

         for (int var7 = 0; var7 < var6; var7++) {
    IsoMovingObject var8 = this.StaticMovingObjects.get(var7);
            if ((var8.sprite != nullptr || dynamic_cast<IsoDeadBody*>(var8) != nullptr)
               && (!var2 || dynamic_cast<IsoDeadBody*>(var8) != nullptr && !this.HasStairs())
               && (var2 || !(dynamic_cast<IsoDeadBody*>(var8) != nullptr) || this.HasStairs())) {
               var8.render(var8.getX(), var8.getY(), var8.getZ(), var5, true, false, nullptr);
            }
         }

         var6 = this.MovingObjects.size();

         for (int var12 = 0; var12 < var6; var12++) {
    IsoMovingObject var13 = this.MovingObjects.get(var12);
            if (var13 != nullptr && var13.sprite != nullptr) {
    bool var9 = var13.bOnFloor;
               if (var9 && dynamic_cast<IsoZombie*>(var13) != nullptr var10) {
                  var9 = var10.isProne();
                  if (!BaseVehicle.RENDER_TO_TEXTURE) {
                     var9 = false;
                  }
               }

               if ((!var2 || var9) && (var2 || !var9)) {
                  var13.render(var13.getX(), var13.getY(), var13.getZ(), var5, true, false, nullptr);
               }
            }
         }
      }
   }

    void renderDeferredCharacters(int var1) {
      if (!this.DeferedCharacters.empty()) {
         if (this.DeferredCharacterTick != this.getCell().DeferredCharacterTick) {
            this.DeferedCharacters.clear();
         } else if (this.z >= var1) {
            this.DeferedCharacters.clear();
         } else if (PerformanceSettings.LightingFrameSkip != 3) {
    short var2 = this.getCell().getStencilValue2z(this.x, this.y, this.z - 1);
            this.getCell().setStencilValue2z(this.x, this.y, this.z - 1, var2);
            IndieGL.enableAlphaTest();
            IndieGL.glAlphaFunc(516, 0.0F);
            IndieGL.glStencilFunc(519, var2, 127);
            IndieGL.glStencilOp(7680, 7680, 7681);
    float var3 = IsoUtils.XToScreen(this.x, this.y, this.z, 0);
    float var4 = IsoUtils.YToScreen(this.x, this.y, this.z, 0);
            var3 -= IsoCamera.frameState.OffX;
            var4 -= IsoCamera.frameState.OffY;
            IndieGL.glColorMask(false, false, false, false);
            Texture.getWhite().renderwallnw(var3, var4, 64 * Core.TileScale, 32 * Core.TileScale, -1, -1, -1, -1, -1, -1);
            IndieGL.glColorMask(true, true, true, true);
            IndieGL.enableAlphaTest();
            IndieGL.glAlphaFunc(516, 0.0F);
            IndieGL.glStencilFunc(514, var2, 127);
            IndieGL.glStencilOp(7680, 7680, 7680);
    ColorInfo var5 = this.lightInfo[IsoCamera.frameState.playerIndex];
            Collections.sort(this.DeferedCharacters, comp);

            for (int var6 = 0; var6 < this.DeferedCharacters.size(); var6++) {
    IsoGameCharacter var7 = this.DeferedCharacters.get(var6);
               if (var7.sprite != nullptr) {
                  var7.setbDoDefer(false);
                  var7.render(var7.getX(), var7.getY(), var7.getZ(), var5, true, false, nullptr);
                  var7.renderObjectPicker(var7.getX(), var7.getY(), var7.getZ(), var5);
                  var7.setbDoDefer(true);
               }
            }

            this.DeferedCharacters.clear();
            IndieGL.glAlphaFunc(516, 0.0F);
            IndieGL.glStencilFunc(519, 1, 255);
            IndieGL.glStencilOp(7680, 7680, 7680);
         }
      }
   }

    void switchLight(bool var1) {
      for (int var2 = 0; var2 < this.Objects.size(); var2++) {
    IsoObject var3 = (IsoObject)this.Objects.get(var2);
         if (dynamic_cast<IsoLightSwitch*>(var3) != nullptr) {
            ((IsoLightSwitch)var3).setActive(var1);
         }
      }
   }

    void removeLightSwitch() {
      for (int var1 = 0; var1 < this.Objects.size(); var1++) {
    IsoObject var2 = (IsoObject)this.Objects.get(var1);
         if (dynamic_cast<IsoLightSwitch*>(var2) != nullptr) {
            this.Objects.remove(var1);
            var1--;
         }
      }
   }

    bool IsOnScreen() {
      return this.IsOnScreen(false);
   }

    bool IsOnScreen(bool var1) {
      if (this.CachedScreenValue != Core.TileScale) {
         this.CachedScreenX = IsoUtils.XToScreen(this.x, this.y, this.z, 0);
         this.CachedScreenY = IsoUtils.YToScreen(this.x, this.y, this.z, 0);
         this.CachedScreenValue = Core.TileScale;
      }

    float var2 = this.CachedScreenX;
    float var3 = this.CachedScreenY;
      var2 -= IsoCamera.frameState.OffX;
      var3 -= IsoCamera.frameState.OffY;
    int var4 = var1 ? 32 * Core.TileScale : 0;
      if (this.hasTree) {
    int var5 = 384 * Core.TileScale / 2 - 96 * Core.TileScale;
    int var6 = 256 * Core.TileScale - 32 * Core.TileScale;
         if (var2 + var5 <= 0 - var4) {
    return false;
         } else if (var3 + 32 * Core.TileScale <= 0 - var4) {
    return false;
         } else {
            return var2 - var5 >= IsoCamera.frameState.OffscreenWidth + var4 ? false : !(var3 - var6 >= IsoCamera.frameState.OffscreenHeight + var4);
         }
      } else if (var2 + 32 * Core.TileScale <= 0 - var4) {
    return false;
      } else if (var3 + 32 * Core.TileScale <= 0 - var4) {
    return false;
      } else {
         return var2 - 32 * Core.TileScale >= IsoCamera.frameState.OffscreenWidth + var4
            ? false
            : !(var3 - 96 * Core.TileScale >= IsoCamera.frameState.OffscreenHeight + var4);
      }
   }

    void cacheLightInfo() {
    int var1 = IsoCamera.frameState.playerIndex;
      this.lightInfo[var1] = this.lighting[var1].lightInfo();
   }

    void setLightInfoServerGUIOnly(ColorInfo var1) {
      this.lightInfo[0] = var1;
   }

    int renderFloor(Shader var1) {
    int var2;
      try {
         s_performance.renderFloor.start();
         var2 = this.renderFloorInternal(var1);
      } finally {
         s_performance.renderFloor.end();
      }

    return var2;
   }

    int renderFloorInternal(Shader var1) {
    int var2 = IsoCamera.frameState.playerIndex;
    ColorInfo var3 = this.lightInfo[var2];
    IsoGridSquare var4 = IsoCamera.frameState.CamCharacterSquare;
    bool var5 = this.lighting[var2].bCouldSee();
    float var6 = this.lighting[var2].darkMulti();
    bool var7 = GameClient.bClient && IsoPlayer.players[var2] != nullptr && IsoPlayer.players[var2].isSeeNonPvpZone();
    bool var8 = Core.bDebug && GameClient.bClient && SafeHouse.isSafeHouse(this, nullptr, true) != nullptr;
    bool var9 = true;
    float var10 = 1.0F;
    float var11 = 1.0F;
      if (var4 != nullptr) {
    int var12 = this.getRoomID();
         if (var12 != -1) {
    int var13 = IsoWorld.instance.CurrentCell.GetEffectivePlayerRoomId();
            if (var13 == -1 && IsoWorld.instance.CurrentCell.CanBuildingSquareOccludePlayer(this, var2)) {
               var9 = false;
               var10 = 1.0F;
               var11 = 1.0F;
            } else if (!var5 && var12 != var13 && var6 < 0.5F) {
               var9 = false;
               var10 = 0.0F;
               var11 = var6 * 2.0F;
            }
         }
      }

    IsoWaterGeometry var30 = this.z == 0 ? this.getWater() : nullptr;
    bool var31 = var30 != nullptr && var30.bShore;
    float var14 = var30 == nullptr ? 0.0F : var30.depth[0];
    float var15 = var30 == nullptr ? 0.0F : var30.depth[3];
    float var16 = var30 == nullptr ? 0.0F : var30.depth[2];
    float var17 = var30 == nullptr ? 0.0F : var30.depth[1];
    uint8_t var18 = 0;
    int var19 = this.Objects.size();
      IsoObject[] var20 = (IsoObject[])this.Objects.getElements();

      for (int var21 = 0; var21 < var19; var21++) {
    IsoObject var22 = var20[var21];
         if (var7 && (var22.highlightFlags & 1) == 0) {
            var22.setHighlighted(true);
            if (NonPvpZone.getNonPvpZone(this.x, this.y) != nullptr) {
               var22.setHighlightColor(0.6F, 0.6F, 1.0F, 0.5F);
            } else {
               var22.setHighlightColor(1.0F, 0.6F, 0.6F, 0.5F);
            }
         }

         if (var8) {
            var22.setHighlighted(true);
            var22.setHighlightColor(1.0F, 0.0F, 0.0F, 1.0F);
         }

    bool var23 = true;
         if (var22.sprite != nullptr && !var22.sprite.solidfloor && var22.sprite.renderLayer != 1) {
            var23 = false;
            var18 |= 4;
         }

         if (dynamic_cast<IsoFire*>(var22) != nullptr || dynamic_cast<IsoCarBatteryCharger*>(var22) != nullptr) {
            var23 = false;
            var18 |= 4;
         }

         if (!var23) {
    bool var24 = var22.sprite != nullptr && (var22.sprite.isBush || var22.sprite.canBeRemoved || var22.sprite.attachedFloor);
            if (this.bFlattenGrassEtc && var24) {
               var18 |= 2;
            }
         } else {
            IndieGL.glAlphaFunc(516, 0.0F);
            var22.setTargetAlpha(var2, var11);
            if (var9) {
               var22.setAlpha(var2, var10);
            }

            if (DebugOptions.instance.Terrain.RenderTiles.RenderGridSquares.getValue() && var22.sprite != nullptr) {
               IndieGL.StartShader(var1, var2);
    FloorShaperAttachedSprites var25 = FloorShaperAttachedSprites.instance;
    void* var37;
               if (!var22.getProperties().Is(IsoFlagType.diamondFloor) && !var22.getProperties().Is(IsoFlagType.water)) {
                  var37 = FloorShaperDeDiamond.instance;
               } else {
                  var37 = FloorShaperDiamond.instance;
               }

    int var26 = this.getVertLight(0, var2);
    int var27 = this.getVertLight(1, var2);
    int var28 = this.getVertLight(2, var2);
    int var29 = this.getVertLight(3, var2);
               if (DebugOptions.instance.Terrain.RenderTiles.IsoGridSquare.Floor.LightingDebug.getValue()) {
                  var26 = -65536;
                  var27 = -65536;
                  var28 = -16776961;
                  var29 = -16776961;
               }

               var25.setShore(var31);
               var25.setWaterDepth(var14, var15, var16, var17);
               var25.setVertColors(var26, var27, var28, var29);
               var37.setShore(var31);
               var37.setWaterDepth(var14, var15, var16, var17);
               var37.setVertColors(var26, var27, var28, var29);
               var22.renderFloorTile(
                  this.x, this.y, this.z, PerformanceSettings.LightingFrameSkip < 3 ? defColorInfo : var3, true, false, var1, (Consumer)var37, var25
               );
               IndieGL.StartShader(nullptr);
            }

            var18 |= 1;
            if ((var22.highlightFlags & 1) == 0) {
               var18 |= 8;
            }

            if ((var22.highlightFlags & 2) != 0) {
               var22.highlightFlags &= -4;
            }
         }
      }

      if ((this.getCell().rainIntensity > 0 || RainManager.isRaining() && RainManager.RainIntensity > 0.0F)
         && this.isExteriorCache
         && !this.isVegitationCache
         && this.isSolidFloorCache
         && this.isCouldSee(var2)) {
         if (!IsoCamera.frameState.Paused) {
            int var32 = this.getCell().rainIntensity == 0
               ? (int)Math.min(Math.floor(RainManager.RainIntensity / 0.2F) + 1.0, 5.0)
               : this.getCell().rainIntensity;
            if (this.splashFrame < 0.0F && Rand.Next(Rand.AdjustForFramerate((int)(5.0F / var32) * 100)) == 0) {
               this.splashFrame = 0.0F;
            }
         }

         if (this.splashFrame >= 0.0F) {
    int var33 = (int)(this.splashFrame * 4.0F);
            if (rainsplashCache[var33] == nullptr) {
               rainsplashCache[var33] = "RainSplash_00_" + var33;
            }

    Texture var34 = Texture.getSharedTexture(rainsplashCache[var33]);
            if (var34 != nullptr) {
    float var35 = IsoUtils.XToScreen(this.x + this.splashX, this.y + this.splashY, this.z, 0) - IsoCamera.frameState.OffX;
    float var38 = IsoUtils.YToScreen(this.x + this.splashX, this.y + this.splashY, this.z, 0) - IsoCamera.frameState.OffY;
               var35 -= var34.getWidth() / 2 * Core.TileScale;
               var38 -= var34.getHeight() / 2 * Core.TileScale;
    float var40 = 0.6F * (this.getCell().rainIntensity > 0 ? 1.0F : RainManager.RainIntensity);
    float var41 = Core.getInstance().RenderShader != nullptr ? 0.6F : 1.0F;
               SpriteRenderer.instance
                  .render(
                     var34,
                     var35,
                     var38,
                     var34.getWidth() * Core.TileScale,
                     var34.getHeight() * Core.TileScale,
                     0.8F * var3.r,
                     0.9F * var3.g,
                     1.0F * var3.b,
                     var40 * var41,
                     nullptr
                  );
            }

            if (!IsoCamera.frameState.Paused && this.splashFrameNum != IsoCamera.frameState.frameCount) {
               this.splashFrame = this.splashFrame + 0.08F * (30.0F / PerformanceSettings.getLockFPS());
               if (this.splashFrame >= 1.0F) {
                  this.splashX = Rand.Next(0.1F, 0.9F);
                  this.splashY = Rand.Next(0.1F, 0.9F);
                  this.splashFrame = -1.0F;
               }

               this.splashFrameNum = IsoCamera.frameState.frameCount;
            }
         }
      } else {
         this.splashFrame = -1.0F;
      }

    return var18;
   }

    bool isSpriteOnSouthOrEastWall(IsoObject var1) {
      if (dynamic_cast<IsoBarricade*>(var1) != nullptr) {
         return var1.getDir() == IsoDirections.S || var1.getDir() == IsoDirections.E;
      } else if (dynamic_cast<IsoCurtain*>(var1) != nullptr var3) {
         return var3.getType() == IsoObjectType.curtainS || var3.getType() == IsoObjectType.curtainE;
      } else {
    PropertyContainer var2 = var1.getProperties();
         return var2 != nullptr && (var2.Is(IsoFlagType.attachedE) || var2.Is(IsoFlagType.attachedS));
      }
   }

    void RenderOpenDoorOnly() {
    int var1 = this.Objects.size();
      IsoObject[] var2 = (IsoObject[])this.Objects.getElements();

      try {
    uint8_t var3 = 0;
    int var4 = var1 - 1;

         for (int var5 = var3; var5 <= var4; var5++) {
    IsoObject var6 = var2[var5];
            if (var6.sprite != nullptr && (var6.sprite.getProperties().Is(IsoFlagType.attachedN) || var6.sprite.getProperties().Is(IsoFlagType.attachedW))) {
               var6.renderFxMask(this.x, this.y, this.z, false);
            }
         }
      } catch (Exception var7) {
         ExceptionLogger.logException(var7);
      }
   }

    bool RenderMinusFloorFxMask(int var1, bool var2, bool var3) {
    bool var4 = false;
    int var5 = this.Objects.size();
      IsoObject[] var6 = (IsoObject[])this.Objects.getElements();
    long var7 = System.currentTimeMillis();

      try {
    int var9 = var2 ? var5 - 1 : 0;
    int var10 = var2 ? 0 : var5 - 1;

         for (int var11 = var9; var2 ? var11 >= var10 : var11 <= var10; var11 += var2 ? -1 : 1) {
    IsoObject var12 = var6[var11];
            if (var12.sprite != nullptr) {
    bool var13 = true;
    IsoObjectType var14 = var12.sprite.getType();
               if (var12.sprite.solidfloor || var12.sprite.renderLayer == 1) {
                  var13 = false;
               }

               if (this.z >= var1 && !var12.sprite.alwaysDraw) {
                  var13 = false;
               }

    bool var15 = var12.sprite.isBush || var12.sprite.canBeRemoved || var12.sprite.attachedFloor;
               if ((!var3 || var15 && this.bFlattenGrassEtc) && (var3 || !var15 || !this.bFlattenGrassEtc)) {
                  if ((var14 == IsoObjectType.WestRoofB || var14 == IsoObjectType.WestRoofM || var14 == IsoObjectType.WestRoofT)
                     && this.z == var1 - 1
                     && this.z == (int)IsoCamera.CamCharacter.getZ()) {
                     var13 = false;
                  }

                  if (this.isSpriteOnSouthOrEastWall(var12)) {
                     if (!var2) {
                        var13 = false;
                     }

                     var4 = true;
                  } else if (var2) {
                     var13 = false;
                  }

                  if (var13) {
                     if (!var12.sprite.cutW && !var12.sprite.cutN) {
                        var12.renderFxMask(this.x, this.y, this.z, false);
                     } else {
    int var16 = IsoCamera.frameState.playerIndex;
    bool var17 = var12.sprite.cutN;
    bool var18 = var12.sprite.cutW;
    IsoGridSquare var19 = this.nav[IsoDirections.S.index()];
    IsoGridSquare var20 = this.nav[IsoDirections.E.index()];
    bool var21 = var19 != nullptr && var19.getPlayerCutawayFlag(var16, var7);
    bool var22 = this.getPlayerCutawayFlag(var16, var7);
    bool var23 = var20 != nullptr && var20.getPlayerCutawayFlag(var16, var7);
    IsoDirections var24;
                        if (var17 && var18) {
                           var24 = IsoDirections.NW;
                        } else if (var17) {
                           var24 = IsoDirections.N;
                        } else if (var18) {
                           var24 = IsoDirections.W;
                        } else {
                           var24 = IsoDirections.W;
                        }

                        this.DoCutawayShaderSprite(var12.sprite, var24, var21, var22, var23);
                     }
                  }
               }
            }
         }
      } catch (Exception var25) {
         ExceptionLogger.logException(var25);
      }

    return var4;
   }

    bool isWindowOrWindowFrame(IsoObject var1, bool var2) {
      if (var1 != nullptr && var1.sprite != nullptr) {
         if (var2 && var1.sprite.getProperties().Is(IsoFlagType.windowN)) {
    return true;
         } else if (!var2 && var1.sprite.getProperties().Is(IsoFlagType.windowW)) {
    return true;
         } else {
    IsoThumpable var3 = (IsoThumpable)Type.tryCastTo(var1, IsoThumpable.class);
            return var3 != nullptr && var3.isWindow() ? var2 == var3.getNorth() : IsoWindowFrame.isWindowFrame(var1, var2);
         }
      } else {
    return false;
      }
   }

    bool renderMinusFloor(int var1, bool var2, bool var3, bool var4, bool var5, bool var6, Shader var7) {
    bool var8 = false;
      if (!this.localTemporaryObjects.empty()) {
         var8 = this.renderMinusFloor(this.localTemporaryObjects, var1, var2, var3, var4, var5, var6, var7);
      }

      return this.renderMinusFloor(this.Objects, var1, var2, var3, var4, var5, var6, var7) || var8;
   }

    bool renderMinusFloor(PZArrayList<IsoObject> var1, int var2, bool var3, bool var4, bool var5, bool var6, bool var7, Shader var8) {
      if (!DebugOptions.instance.Terrain.RenderTiles.IsoGridSquare.RenderMinusFloor.getValue()) {
    return false;
      } else {
         IndieGL.glBlendFunc(770, 771);
    int var9 = 0;
         isOnScreenLast = this.IsOnScreen();
    int var10 = IsoCamera.frameState.playerIndex;
    IsoGridSquare var11 = IsoCamera.frameState.CamCharacterSquare;
    ColorInfo var12 = this.lightInfo[var10];
    bool var13 = this.lighting[var10].bCouldSee();
    float var14 = this.lighting[var10].darkMulti();
    bool var15 = IsoWorld.instance.CurrentCell.CanBuildingSquareOccludePlayer(this, var10);
         var12.a = 1.0F;
         defColorInfo.r = 1.0F;
         defColorInfo.g = 1.0F;
         defColorInfo.b = 1.0F;
         defColorInfo.a = 1.0F;
         if (Core.bDebug && DebugOptions.instance.DebugDraw_SkipWorldShading.getValue()) {
            var12 = defColorInfo;
         }

    float var16 = this.CachedScreenX - IsoCamera.frameState.OffX;
    float var17 = this.CachedScreenY - IsoCamera.frameState.OffY;
    bool var18 = true;
    IsoCell var19 = this.getCell();
         if (var16 + 32 * Core.TileScale <= var19.StencilX1
            || var16 - 32 * Core.TileScale >= var19.StencilX2
            || var17 + 32 * Core.TileScale <= var19.StencilY1
            || var17 - 96 * Core.TileScale >= var19.StencilY2) {
            var18 = false;
         }

    bool var20 = false;
    int var21 = var1.size();
         IsoObject[] var22 = (IsoObject[])var1.getElements();
         tempWorldInventoryObjects.clear();
    int var23 = var3 ? var21 - 1 : 0;
    int var24 = var3 ? 0 : var21 - 1;
    bool var25 = false;
    bool var26 = false;
    bool var27 = false;
    bool var28 = false;
         if (!var3) {
            for (int var29 = var23; var29 <= var24; var29++) {
    IsoObject var30 = var22[var29];
               if (this.isWindowOrWindowFrame(var30, true) && (var6 || var7)) {
    IsoGridSquare var31 = this.nav[IsoDirections.N.index()];
                  var27 = var13 || var31 != nullptr && var31.isCouldSee(var10);
               }

               if (this.isWindowOrWindowFrame(var30, false) && (var6 || var5)) {
    IsoGridSquare var50 = this.nav[IsoDirections.W.index()];
                  var28 = var13 || var50 != nullptr && var50.isCouldSee(var10);
               }

               if (var30.sprite != nullptr && (var30.sprite.getType() == IsoObjectType.doorFrN || var30.sprite.getType() == IsoObjectType.doorN) && (var6 || var7)
                  )
                {
    IsoGridSquare var51 = this.nav[IsoDirections.N.index()];
                  var25 = var13 || var51 != nullptr && var51.isCouldSee(var10);
               }

               if (var30.sprite != nullptr && (var30.sprite.getType() == IsoObjectType.doorFrW || var30.sprite.getType() == IsoObjectType.doorW) && (var6 || var5)
                  )
                {
    IsoGridSquare var52 = this.nav[IsoDirections.W.index()];
                  var26 = var13 || var52 != nullptr && var52.isCouldSee(var10);
               }
            }
         }

    int var47 = IsoWorld.instance.CurrentCell.GetEffectivePlayerRoomId();
         bWallCutawayN = false;
         bWallCutawayW = false;

         for (int var48 = var23; var3 ? var48 >= var24 : var48 <= var24; var48 += var3 ? -1 : 1) {
    IsoObject var53 = var22[var48];
    bool var32 = true;
    IsoObjectType var33 = IsoObjectType.MAX;
            if (var53.sprite != nullptr) {
               var33 = var53.sprite.getType();
            }

            CircleStencil = false;
            if (var53.sprite != nullptr && (var53.sprite.solidfloor || var53.sprite.renderLayer == 1)) {
               var32 = false;
            }

            if (dynamic_cast<IsoFire*>(var53) != nullptr) {
               var32 = !var4;
            }

            if (this.z >= var2 && (var53.sprite == nullptr || !var53.sprite.alwaysDraw)) {
               var32 = false;
            }

    bool var34 = var53.sprite != nullptr && (var53.sprite.isBush || var53.sprite.canBeRemoved || var53.sprite.attachedFloor);
            if ((!var4 || var34 && this.bFlattenGrassEtc) && (var4 || !var34 || !this.bFlattenGrassEtc)) {
               if (var53.sprite != nullptr
                  && (var33 == IsoObjectType.WestRoofB || var33 == IsoObjectType.WestRoofM || var33 == IsoObjectType.WestRoofT)
                  && this.z == var2 - 1
                  && this.z == (int)IsoCamera.CamCharacter.getZ()) {
                  var32 = false;
               }

    bool var35 = var33 == IsoObjectType.doorFrW || var33 == IsoObjectType.doorW || var53.sprite != nullptr && var53.sprite.cutW;
    bool var36 = var33 == IsoObjectType.doorFrN || var33 == IsoObjectType.doorN || var53.sprite != nullptr && var53.sprite.cutN;
    bool var37 = dynamic_cast<IsoDoor*>(var53) != nullptr && ((IsoDoor)var53).open || dynamic_cast<IsoThumpable*>(var53) != nullptr && ((IsoThumpable)var53).open;
    bool var38 = var53.container != nullptr;
    bool var39 = var53.sprite != nullptr && var53.sprite.getProperties().Is(IsoFlagType.waterPiped);
               if (var53.sprite != nullptr && var33 == IsoObjectType.MAX && !(dynamic_cast<IsoDoor*>(var53) != nullptr) && !(dynamic_cast<IsoWindow*>(var53) != nullptr) && !var38 && !var39) {
                  if (var35 || !var53.sprite.getProperties().Is(IsoFlagType.attachedW) || !var15 && !var5 && !var6) {
                     if (!var36 && var53.sprite.getProperties().Is(IsoFlagType.attachedN) && (var15 || var6 || var7)) {
                        var32 = !bWallCutawayN;
                     }
                  } else {
                     var32 = !bWallCutawayW;
                  }
               }

               if (var53.sprite != nullptr && !var53.sprite.solidfloor && IsoPlayer.getInstance().isClimbing()) {
                  var32 = true;
               }

               if (this.isSpriteOnSouthOrEastWall(var53)) {
                  if (!var3) {
                     var32 = false;
                  }

                  var20 = true;
               } else if (var3) {
                  var32 = false;
               }

               if (var32) {
                  IndieGL.glAlphaFunc(516, 0.0F);
                  var53.bAlphaForced = false;
                  if (var37) {
                     var53.setTargetAlpha(var10, 0.6F);
                     var53.setAlpha(var10, 0.6F);
                  }

                  if (var53.sprite == nullptr || !var35 && !var36) {
                     if (DebugOptions.instance.Terrain.RenderTiles.IsoGridSquare.Objects.getValue()) {
                        if (this.getRoomID() != -1
                           && this.getRoomID() != var47
                           && IsoPlayer.players[var10].isSeatedInVehicle()
                           && IsoPlayer.players[var10].getVehicle().getCurrentSpeedKmHour() >= 50.0F) {
                           break;
                        }

                        if (var33 != IsoObjectType.WestRoofB && var33 != IsoObjectType.WestRoofM && var33 != IsoObjectType.WestRoofT
                           || (
                                 this.getRoomID() != -1
                                    || !var7 && !var5
                                    || (!(IsoPlayer.players[var10].getX() < this.x) || !(IsoPlayer.players[var10].getY() < this.y))
                                       && !(IsoPlayer.players[var10].getZ() < this.z)
                              )
                              && (
                                 this.getRoomID() == -1 && var47 == -1
                                    || !(IsoPlayer.players[var10].getX() + IsoPlayer.players[var10].getY() <= this.x + this.y + 6)
                                    || !(IsoPlayer.players[var10].getZ() < this.z + 1)
                              )) {
                           if (var11 != nullptr && !var13 && this.getRoomID() != var47 && var14 < 0.5F) {
                              var53.setTargetAlpha(var10, var14 * 2.0F);
                           } else {
                              if (!var37) {
                                 var53.setTargetAlpha(var10, 1.0F);
                              }

                              if (IsoPlayer.getInstance() != nullptr
                                    && var53.getProperties() != nullptr
                                    && (
                                       var53.getProperties().Is(IsoFlagType.solid)
                                          || var53.getProperties().Is(IsoFlagType.solidtrans)
                                          || var53.getProperties().Is(IsoFlagType.attachedCeiling)
                                          || var53.getSprite().getProperties().Is(IsoFlagType.attachedE)
                                          || var53.getSprite().getProperties().Is(IsoFlagType.attachedS)
                                    )
                                 || var33.index() > 2 && var33.index() < 9 && IsoCamera.frameState.CamCharacterZ <= var53.getZ()) {
    uint8_t var40 = 2;
    float var41 = 0.75F;
                                 if (var33.index() > 2 && var33.index() < 9
                                    || var53.getSprite().getProperties().Is(IsoFlagType.attachedE)
                                    || var53.getSprite().getProperties().Is(IsoFlagType.attachedS)) {
                                    var40 = 4;
                                    if (var33.index() > 2 && var33.index() < 9) {
                                       var41 = 0.5F;
                                    }
                                 }

    int var42 = this.getX() - (int)IsoPlayer.getInstance().getX();
    int var43 = this.getY() - (int)IsoPlayer.getInstance().getY();
                                 if (var42 > 0 && var42 < var40 && var43 >= 0 && var43 < var40 || var43 > 0 && var43 < var40 && var42 >= 0 && var42 < var40) {
                                    var53.setTargetAlpha(var10, var41);
                                 }

    IsoZombie var44 = IsoCell.getInstance().getNearestVisibleZombie(var10);
                                 if (var44 != nullptr && var44.getCurrentSquare() != nullptr && var44.getCurrentSquare().isCanSee(var10)) {
    int var45 = this.getX() - (int)var44.x;
    int var46 = this.getY() - (int)var44.y;
                                    if (var45 > 0 && var45 < var40 && var46 >= 0 && var46 < var40 || var46 > 0 && var46 < var40 && var45 >= 0 && var45 < var40) {
                                       var53.setTargetAlpha(var10, var41);
                                    }
                                 }
                              }
                           }
                        } else {
                           var53.setTargetAlpha(var10, 0.0F);
                        }

                        if (dynamic_cast<IsoWindow*>(var53) != nullptr var55) {
                           if (var53.getTargetAlpha(var10) < 1.0E-4F) {
    IsoGridSquare var57 = var55.getOppositeSquare();
                              if (var57 != nullptr && var57 != this && var57.lighting[var10].bSeen()) {
                                 var53.setTargetAlpha(var10, var57.lighting[var10].darkMulti() * 2.0F);
                              }
                           }

                           if (var53.getTargetAlpha(var10) > 0.4F
                              && var6
                              && (var7 && var53.sprite.getProperties().Is(IsoFlagType.windowN) || var5 && var53.sprite.getProperties().Is(IsoFlagType.windowW))
                              )
                            {
    float var58 = 0.4F;
    float var59 = 0.1F;
    IsoPlayer var60 = IsoPlayer.players[var10];
                              if (var60 != nullptr) {
    float var61 = 5.0F;
                                 float var62 = Math.abs(var60.x - this.x) * Math.abs(var60.x - this.x)
                                    + Math.abs(var60.y - this.y) * Math.abs(var60.y - this.y);
    float var63 = var58 * (float)(1.0 - Math.sqrt(var62 / var61));
                                 var53.setTargetAlpha(var10, Math.max(var63, var59));
                              } else {
                                 var53.setTargetAlpha(var10, var59);
                              }

                              if (var7) {
                                 bWallCutawayN = true;
                              } else {
                                 bWallCutawayW = true;
                              }
                           }
                        }

                        if (dynamic_cast<IsoTree*>(var53) != nullptr) {
                           if (var18
                              && this.x >= (int)IsoCamera.frameState.CamCharacterX
                              && this.y >= (int)IsoCamera.frameState.CamCharacterY
                              && var11 != nullptr
                              && var11.Is(IsoFlagType.exterior)) {
                              ((IsoTree)var53).bRenderFlag = true;
                              var53.setTargetAlpha(var10, Math.min(0.99F, var53.getTargetAlpha(var10)));
                           } else {
                              ((IsoTree)var53).bRenderFlag = false;
                           }
                        }

    IsoWorldInventoryObject var56 = (IsoWorldInventoryObject)Type.tryCastTo(var53, IsoWorldInventoryObject.class);
                        if (var56 != nullptr) {
                           tempWorldInventoryObjects.push_back(var56);
                        }

                        var53.render(this.x, this.y, this.z, var12, true, false, nullptr);
                     }
                  } else if (PerformanceSettings.LightingFrameSkip < 3) {
                     if (DebugOptions.instance.Terrain.RenderTiles.IsoGridSquare.DoorsAndWalls.getValue()) {
                        CircleStencil = true;
                        if (var11 != nullptr && this.getRoomID() != -1 && var47 == -1 && var15) {
                           var53.setTargetAlpha(var10, 0.5F);
                           var53.setAlpha(var10, 0.5F);
                        } else if (this.getRoomID() == var47
                           || var13
                           || !var53.getProperties().Is(IsoFlagType.transparentN) && !var53.getProperties().Is(IsoFlagType.transparentW)) {
                           if (!var37) {
                              var53.setTargetAlpha(var10, 1.0F);
                              var53.setAlpha(var10, 1.0F);
                           }
                        } else {
                           var53.setTargetAlpha(var10, 0.0F);
                           var53.setAlpha(var10, 0.0F);
                        }

                        var53.bAlphaForced = true;
                        if (var53.sprite.cutW && var53.sprite.cutN) {
                           var9 = this.DoWallLightingNW(var53, var9, var5, var6, var7, var25, var26, var27, var28, var8);
                        } else if (var53.sprite.getType() == IsoObjectType.doorFrW || var33 == IsoObjectType.doorW || var53.sprite.cutW) {
                           var9 = this.DoWallLightingW(var53, var9, var5, var6, var26, var28, var8);
                        } else if (var33 == IsoObjectType.doorFrN || var33 == IsoObjectType.doorN || var53.sprite.cutN) {
                           var9 = this.DoWallLightingN(var53, var9, var6, var7, var25, var27, var8);
                        }

                        if (dynamic_cast<IsoWindow*>(var53) != nullptr && var53.getTargetAlpha(var10) < 1.0F) {
                           bWallCutawayN = bWallCutawayN | var53.sprite.cutN;
                           bWallCutawayW = bWallCutawayW | var53.sprite.cutW;
                        }
                     }
                  } else if (DebugOptions.instance.Terrain.RenderTiles.IsoGridSquare.DoorsAndWalls_SimpleLighting.getValue()) {
                     if (this.z != (int)IsoCamera.frameState.CamCharacterZ
                        || var33 == IsoObjectType.doorFrW
                        || var33 == IsoObjectType.doorFrN
                        || dynamic_cast<IsoWindow*>(var53) != nullptr) {
                        var18 = false;
                     }

                     if (var53.getTargetAlpha(var10) < 1.0F) {
                        if (!var18) {
                           var53.setTargetAlpha(var10, 1.0F);
                        }

                        var53.setAlphaToTarget(var10);
                        IsoObject.LowLightingQualityHack = false;
                        var53.render(this.x, this.y, this.z, var12, true, false, nullptr);
                        if (!IsoObject.LowLightingQualityHack) {
                           var53.setTargetAlpha(var10, 1.0F);
                        }
                     } else {
                        var53.render(this.x, this.y, this.z, var12, true, false, nullptr);
                     }
                  }

                  if ((var53.highlightFlags & 2) != 0) {
                     var53.highlightFlags &= -4;
                  }
               }
            }
         }

         Arrays.sort(
            (IsoWorldInventoryObject[])tempWorldInventoryObjects.getElements(),
            0,
            tempWorldInventoryObjects.size(),
            (var0, var1x) -> {
               float var2x = ((IsoWorldInventoryObject)var0).xoff * ((IsoWorldInventoryObject)var0).xoff
                  + ((IsoWorldInventoryObject)var0).yoff * ((IsoWorldInventoryObject)var0).yoff;
               float var3x = ((IsoWorldInventoryObject)var1x).xoff * ((IsoWorldInventoryObject)var1x).xoff
                  + ((IsoWorldInventoryObject)var1x).yoff * ((IsoWorldInventoryObject)var1x).yoff;
               if (var2x == var3x) {
    return 0;
               } else {
                  return var2x > var3x ? 1 : -1;
               }
            }
         );

         for (int var49 = 0; var49 < tempWorldInventoryObjects.size(); var49++) {
    IsoWorldInventoryObject var54 = (IsoWorldInventoryObject)tempWorldInventoryObjects.get(var49);
            var54.render(this.x, this.y, this.z, var12, true, false, nullptr);
         }

    return var20;
      }
   }

    void RereouteWallMaskTo(IsoObject var1) {
      for (int var2 = 0; var2 < this.Objects.size(); var2++) {
    IsoObject var3 = (IsoObject)this.Objects.get(var2);
         if (var3.sprite.getProperties().Is(IsoFlagType.collideW) || var3.sprite.getProperties().Is(IsoFlagType.collideN)) {
            var3.rerouteMask = var1;
         }
      }
   }

    void setBlockedGridPointers(GetSquare var1) {
      this.w = var1.getGridSquare(this.x - 1, this.y, this.z);
      this.e = var1.getGridSquare(this.x + 1, this.y, this.z);
      this.s = var1.getGridSquare(this.x, this.y + 1, this.z);
      this.n = var1.getGridSquare(this.x, this.y - 1, this.z);
      this.ne = var1.getGridSquare(this.x + 1, this.y - 1, this.z);
      this.nw = var1.getGridSquare(this.x - 1, this.y - 1, this.z);
      this.se = var1.getGridSquare(this.x + 1, this.y + 1, this.z);
      this.sw = var1.getGridSquare(this.x - 1, this.y + 1, this.z);
      if (this.s != nullptr && this.testPathFindAdjacent(nullptr, this.s.x - this.x, this.s.y - this.y, this.s.z - this.z, var1)) {
         this.s = nullptr;
      }

      if (this.w != nullptr && this.testPathFindAdjacent(nullptr, this.w.x - this.x, this.w.y - this.y, this.w.z - this.z, var1)) {
         this.w = nullptr;
      }

      if (this.n != nullptr && this.testPathFindAdjacent(nullptr, this.n.x - this.x, this.n.y - this.y, this.n.z - this.z, var1)) {
         this.n = nullptr;
      }

      if (this.e != nullptr && this.testPathFindAdjacent(nullptr, this.e.x - this.x, this.e.y - this.y, this.e.z - this.z, var1)) {
         this.e = nullptr;
      }

      if (this.sw != nullptr && this.testPathFindAdjacent(nullptr, this.sw.x - this.x, this.sw.y - this.y, this.sw.z - this.z, var1)) {
         this.sw = nullptr;
      }

      if (this.se != nullptr && this.testPathFindAdjacent(nullptr, this.se.x - this.x, this.se.y - this.y, this.se.z - this.z, var1)) {
         this.se = nullptr;
      }

      if (this.nw != nullptr && this.testPathFindAdjacent(nullptr, this.nw.x - this.x, this.nw.y - this.y, this.nw.z - this.z, var1)) {
         this.nw = nullptr;
      }

      if (this.ne != nullptr && this.testPathFindAdjacent(nullptr, this.ne.x - this.x, this.ne.y - this.y, this.ne.z - this.z, var1)) {
         this.ne = nullptr;
      }
   }

    IsoObject getContainerItem(const std::string& var1) {
    int var2 = this.getObjects().size();
      IsoObject[] var3 = (IsoObject[])this.getObjects().getElements();

      for (int var4 = 0; var4 < var2; var4++) {
    IsoObject var5 = var3[var4];
         if (var5.getContainer() != nullptr && var1 == var5.getContainer().getType())) {
    return var5;
         }
      }

    return nullptr;
   }

    void StartFire() {
   }

    void explode() {
      IsoFireManager.explode(this.getCell(), this, 100000);
   }

    int getHourLastSeen() {
      return this.hourLastSeen;
   }

    float getHoursSinceLastSeen() {
      return (float)GameTime.instance.getWorldAgeHours() - this.hourLastSeen;
   }

    void CalcVisibility(int var1) {
    IsoPlayer var2 = IsoPlayer.players[var1];
    ILighting var3 = this.lighting[var1];
      var3.bCanSee(false);
      var3.bCouldSee(false);
      if (GameServer.bServer || var2 != nullptr && (!var2.isDead() || var2.ReanimatedCorpse != nullptr)) {
         if (var2 != nullptr) {
    LightInfo var4 = var2.getLightInfo2();
    IsoGridSquare var5 = var4.square;
            if (var5 != nullptr) {
    IsoChunk var6 = this.getChunk();
               if (var6 != nullptr) {
                  tempo.x = this.x + 0.5F;
                  tempo.y = this.y + 0.5F;
                  tempo2.x = var4.x;
                  tempo2.y = var4.y;
                  tempo2.x = tempo2.x - tempo.x;
                  tempo2.y = tempo2.y - tempo.y;
    Vector2 var7 = tempo;
    float var8 = tempo2.getLength();
                  tempo2.normalize();
                  if (dynamic_cast<IsoSurvivor*>(var2) != nullptr) {
                     var2.setForwardDirection(var7);
                     var4.angleX = var7.x;
                     var4.angleY = var7.y;
                  }

                  var7.x = var4.angleX;
                  var7.y = var4.angleY;
                  var7.normalize();
    float var9 = tempo2.dot(var7);
                  if (var5 == this) {
                     var9 = -1.0F;
                  }

                  if (!GameServer.bServer) {
    float var10 = var2.getStats().fatigue - 0.6F;
                     if (var10 < 0.0F) {
                        var10 = 0.0F;
                     }

                     var10 *= 2.5F;
                     if (var2.Traits.HardOfHearing.isSet() && var10 < 0.7F) {
                        var10 = 0.7F;
                     }

    float var11 = 2.0F;
                     if (var2.Traits.KeenHearing.isSet()) {
                        var11 += 3.0F;
                     }

                     if (var8 < var11 * (1.0F - var10) && !var2.Traits.Deaf.isSet()) {
                        var9 = -1.0F;
                     }
                  }

    TestResults var19 = LosUtil.lineClearCached(this.getCell(), this.x, this.y, this.z, (int)var4.x, (int)var4.y, (int)var4.z, false, var1);
    float var20 = -0.2F;
                  var20 -= var2.getStats().fatigue - 0.6F;
                  if (var20 > -0.2F) {
                     var20 = -0.2F;
                  }

                  if (var2.getStats().fatigue >= 1.0F) {
                     var20 -= 0.2F;
                  }

                  if (var2.getMoodles().getMoodleLevel(MoodleType.Panic) == 4) {
                     var20 -= 0.2F;
                  }

                  if (var20 < -0.9F) {
                     var20 = -0.9F;
                  }

                  if (var2.Traits.EagleEyed.isSet()) {
                     var20 += 0.2F;
                  }

                  if (dynamic_cast<IsoPlayer*>(var2) != nullptr && var2.getVehicle() != nullptr) {
                     var20 = 1.0F;
                  }

                  if (!(var9 > var20) && var19 != TestResults.Blocked) {
                     var3.bCouldSee(true);
                     if (this.room != nullptr && this.room.def != nullptr && !this.room.def.bExplored) {
    uint8_t var23 = 10;
                        if (var4.square != nullptr && var4.square.getBuilding() == this.room.building) {
                           var23 = 50;
                        }

                        if ((!GameServer.bServer || !(dynamic_cast<IsoPlayer*>(var2) != nullptr) || !var2.isGhostMode())
                           && IsoUtils.DistanceManhatten(var4.x, var4.y, this.x, this.y) < var23
                           && this.z == (int)var4.z) {
                           if (GameServer.bServer) {
                              DebugLog.log(DebugType.Zombie, "bExplored room=" + this.room.def.ID);
                           }

                           this.room.def.bExplored = true;
                           this.room.onSee();
                           this.room.seen = 0;
                        }
                     }

                     if (!GameClient.bClient) {
                        Meta.instance.dealWithSquareSeen(this);
                     }

                     var3.bCanSee(true);
                     var3.bSeen(true);
                     var3.targetDarkMulti(1.0F);
                  } else {
                     if (var19 == TestResults.Blocked) {
                        var3.bCouldSee(false);
                     } else {
                        var3.bCouldSee(true);
                     }

                     if (!GameServer.bServer) {
                        if (var3.bSeen()) {
    float var12 = RenderSettings.getInstance().getAmbientForPlayer(IsoPlayer.getPlayerIndex());
                           if (!var3.bCouldSee()) {
                              var12 *= 0.5F;
                           } else {
                              var12 *= 0.94F;
                           }

                           if (this.room == nullptr && var5.getRoom() == nullptr) {
                              var3.targetDarkMulti(var12);
                           } else if (this.room != nullptr && var5.getRoom() != nullptr && this.room.building == var5.getRoom().building) {
                              if (this.room != var5.getRoom() && !var3.bCouldSee()) {
                                 var3.targetDarkMulti(0.0F);
                              } else {
                                 var3.targetDarkMulti(var12);
                              }
                           } else if (this.room == nullptr) {
                              var3.targetDarkMulti(var12 / 2.0F);
                           } else if (var3.lampostTotalR() + var3.lampostTotalG() + var3.lampostTotalB() == 0.0F) {
                              var3.targetDarkMulti(0.0F);
                           }

                           if (this.room != nullptr) {
                              var3.targetDarkMulti(var3.targetDarkMulti() * 0.7F);
                           }
                        } else {
                           var3.targetDarkMulti(0.0F);
                           var3.darkMulti(0.0F);
                        }
                     }
                  }

                  if (var9 > var20) {
                     var3.targetDarkMulti(var3.targetDarkMulti() * 0.85F);
                  }

                  if (!GameServer.bServer) {
                     for (int var24 = 0; var24 < var4.torches.size(); var24++) {
    TorchInfo var13 = (TorchInfo)var4.torches.get(var24);
                        tempo2.x = var13.x;
                        tempo2.y = var13.y;
                        tempo2.x = tempo2.x - (this.x + 0.5F);
                        tempo2.y = tempo2.y - (this.y + 0.5F);
                        var8 = tempo2.getLength();
                        tempo2.normalize();
                        var7.x = var13.angleX;
                        var7.y = var13.angleY;
                        var7.normalize();
                        var9 = tempo2.dot(var7);
                        if ((int)var13.x == this.getX() && (int)var13.y == this.getY() && (int)var13.z == this.getZ()) {
                           var9 = -1.0F;
                        }

    bool var14 = false;
                        if (IsoUtils.DistanceManhatten(this.getX(), this.getY(), var13.x, var13.y) < var13.dist
                           && (var13.bCone && var9 < -var13.dot || var9 == -1.0F || !var13.bCone && var9 < 0.8F)) {
                           var14 = true;
                        }

                        if ((var13.bCone && var8 < var13.dist || !var13.bCone && var8 < var13.dist) && var3.bCanSee() && var14 && this.z == (int)var2.getZ()) {
    float var15 = var8 / var13.dist;
                           if (var15 > 1.0F) {
                              var15 = 1.0F;
                           }

                           if (var15 < 0.0F) {
                              var15 = 0.0F;
                           }

                           var3.targetDarkMulti(var3.targetDarkMulti() + var13.strength * (1.0F - var15) * 3.0F);
                           if (var3.targetDarkMulti() > 2.5F) {
                              var3.targetDarkMulti(2.5F);
                           }

                           torchTimer = var4.time;
                        }
                     }
                  }
               }
            }
         }
      } else {
         var3.bSeen(true);
         var3.bCanSee(true);
         var3.bCouldSee(true);
      }
   }

    TestResults DoDiagnalCheck(int var1, int var2, int var3, bool var4) {
    TestResults var5 = this.testVisionAdjacent(var1, 0, var3, false, var4);
      if (var5 == TestResults.Blocked) {
         return TestResults.Blocked;
      } else {
    TestResults var6 = this.testVisionAdjacent(0, var2, var3, false, var4);
         if (var6 == TestResults.Blocked) {
            return TestResults.Blocked;
         } else {
            return var5 != TestResults.ClearThroughWindow && var6 != TestResults.ClearThroughWindow
               ? this.testVisionAdjacent(var1, var2, var3, false, var4)
               : TestResults.ClearThroughWindow;
         }
      }
   }

    bool HasNoCharacters() {
      for (int var1 = 0; var1 < this.MovingObjects.size(); var1++) {
         if (this.MovingObjects.get(var1) instanceof IsoGameCharacter) {
    return false;
         }
      }

      for (int var2 = 0; var2 < this.SpecialObjects.size(); var2++) {
         if (this.SpecialObjects.get(var2) instanceof IsoBarricade) {
    return false;
         }
      }

    return true;
   }

    IsoZombie getZombie() {
      for (int var1 = 0; var1 < this.MovingObjects.size(); var1++) {
         if (this.MovingObjects.get(var1) instanceof IsoZombie) {
            return (IsoZombie)this.MovingObjects.get(var1);
         }
      }

    return nullptr;
   }

    IsoPlayer getPlayer() {
      for (int var1 = 0; var1 < this.MovingObjects.size(); var1++) {
         if (this.MovingObjects.get(var1) instanceof IsoPlayer) {
            return (IsoPlayer)this.MovingObjects.get(var1);
         }
      }

    return nullptr;
   }

    static float getDarkStep() {
    return darkStep;
   }

    static void setDarkStep(float var0) {
      darkStep = var0;
   }

    static int getRecalcLightTime() {
    return RecalcLightTime;
   }

    static void setRecalcLightTime(int var0) {
      RecalcLightTime = var0;
   }

    static int getLightcache() {
    return lightcache;
   }

    static void setLightcache(int var0) {
      lightcache = var0;
   }

    bool isCouldSee(int var1) {
      return this.lighting[var1].bCouldSee();
   }

    void setCouldSee(int var1, bool var2) {
      this.lighting[var1].bCouldSee(var2);
   }

    bool isCanSee(int var1) {
      return this.lighting[var1].bCanSee();
   }

    void setCanSee(int var1, bool var2) {
      this.lighting[var1].bCanSee(var2);
   }

    IsoCell getCell() {
      return IsoWorld.instance.CurrentCell;
   }

    IsoGridSquare getE() {
      return this.e;
   }

    void setE(IsoGridSquare var1) {
      this.e = var1;
   }

   public std::vector<float> getLightInfluenceB() {
      return this.LightInfluenceB;
   }

    void setLightInfluenceB(std::vector<float> var1) {
      this.LightInfluenceB = var1;
   }

   public std::vector<float> getLightInfluenceG() {
      return this.LightInfluenceG;
   }

    void setLightInfluenceG(std::vector<float> var1) {
      this.LightInfluenceG = var1;
   }

   public std::vector<float> getLightInfluenceR() {
      return this.LightInfluenceR;
   }

    void setLightInfluenceR(std::vector<float> var1) {
      this.LightInfluenceR = var1;
   }

   public std::vector<IsoMovingObject> getStaticMovingObjects() {
      return this.StaticMovingObjects;
   }

   public std::vector<IsoMovingObject> getMovingObjects() {
      return this.MovingObjects;
   }

    IsoGridSquare getN() {
      return this.n;
   }

    void setN(IsoGridSquare var1) {
      this.n = var1;
   }

   public PZArrayList<IsoObject> getObjects() {
      return this.Objects;
   }

    PropertyContainer getProperties() {
      return this.Properties;
   }

    IsoRoom getRoom() {
      return this.roomID == -1 ? nullptr : this.room;
   }

    void setRoom(IsoRoom var1) {
      this.room = var1;
   }

    IsoBuilding getBuilding() {
    IsoRoom var1 = this.getRoom();
      return var1 != nullptr ? var1.getBuilding() : nullptr;
   }

    IsoGridSquare getS() {
      return this.s;
   }

    void setS(IsoGridSquare var1) {
      this.s = var1;
   }

   public std::vector<IsoObject> getSpecialObjects() {
      return this.SpecialObjects;
   }

    IsoGridSquare getW() {
      return this.w;
   }

    void setW(IsoGridSquare var1) {
      this.w = var1;
   }

    float getLampostTotalR() {
      return this.lighting[0].lampostTotalR();
   }

    void setLampostTotalR(float var1) {
      this.lighting[0].lampostTotalR(var1);
   }

    float getLampostTotalG() {
      return this.lighting[0].lampostTotalG();
   }

    void setLampostTotalG(float var1) {
      this.lighting[0].lampostTotalG(var1);
   }

    float getLampostTotalB() {
      return this.lighting[0].lampostTotalB();
   }

    void setLampostTotalB(float var1) {
      this.lighting[0].lampostTotalB(var1);
   }

    bool isSeen(int var1) {
      return this.lighting[var1].bSeen();
   }

    void setIsSeen(int var1, bool var2) {
      this.lighting[var1].bSeen(var2);
   }

    float getDarkMulti(int var1) {
      return this.lighting[var1].darkMulti();
   }

    void setDarkMulti(int var1, float var2) {
      this.lighting[var1].darkMulti(var2);
   }

    float getTargetDarkMulti(int var1) {
      return this.lighting[var1].targetDarkMulti();
   }

    void setTargetDarkMulti(int var1, float var2) {
      this.lighting[var1].targetDarkMulti(var2);
   }

    void setX(int var1) {
      this.x = var1;
      this.CachedScreenValue = -1;
   }

    void setY(int var1) {
      this.y = var1;
      this.CachedScreenValue = -1;
   }

    void setZ(int var1) {
      this.z = var1;
      this.CachedScreenValue = -1;
   }

   public std::vector<IsoGameCharacter> getDeferedCharacters() {
      return this.DeferedCharacters;
   }

    void addDeferredCharacter(IsoGameCharacter var1) {
      if (this.DeferredCharacterTick != this.getCell().DeferredCharacterTick) {
         if (!this.DeferedCharacters.empty()) {
            this.DeferedCharacters.clear();
         }

         this.DeferredCharacterTick = this.getCell().DeferredCharacterTick;
      }

      this.DeferedCharacters.push_back(var1);
   }

    bool isCacheIsFree() {
      return this.CacheIsFree;
   }

    void setCacheIsFree(bool var1) {
      this.CacheIsFree = var1;
   }

    bool isCachedIsFree() {
      return this.CachedIsFree;
   }

    void setCachedIsFree(bool var1) {
      this.CachedIsFree = var1;
   }

    static bool isbDoSlowPathfinding() {
    return bDoSlowPathfinding;
   }

    static void setbDoSlowPathfinding(bool var0) {
      bDoSlowPathfinding = var0;
   }

    bool isSolidFloorCached() {
      return this.SolidFloorCached;
   }

    void setSolidFloorCached(bool var1) {
      this.SolidFloorCached = var1;
   }

    bool isSolidFloor() {
      return this.SolidFloor;
   }

    void setSolidFloor(bool var1) {
      this.SolidFloor = var1;
   }

    static ColorInfo getDefColorInfo() {
    return defColorInfo;
   }

    bool isOutside() {
      return this.Properties.Is(IsoFlagType.exterior);
   }

    bool HasPushable() {
    int var1 = this.MovingObjects.size();

      for (int var2 = 0; var2 < var1; var2++) {
         if (this.MovingObjects.get(var2) instanceof IsoPushableObject) {
    return true;
         }
      }

    return false;
   }

    void setRoomID(int var1) {
      this.roomID = var1;
      if (var1 != -1) {
         this.getProperties().UnSet(IsoFlagType.exterior);
         this.room = this.chunk.getRoom(var1);
      }
   }

    int getRoomID() {
      return this.roomID;
   }

    bool getCanSee(int var1) {
      return this.lighting[var1].bCanSee();
   }

    bool getSeen(int var1) {
      return this.lighting[var1].bSeen();
   }

    IsoChunk getChunk() {
      return this.chunk;
   }

    IsoObject getDoorOrWindow(bool var1) {
      for (int var2 = this.SpecialObjects.size() - 1; var2 >= 0; var2--) {
    IsoObject var3 = this.SpecialObjects.get(var2);
         if (dynamic_cast<IsoDoor*>(var3) != nullptr && ((IsoDoor)var3).north == var1) {
    return var3;
         }

         if (dynamic_cast<IsoThumpable*>(var3) != nullptr && ((IsoThumpable)var3).north == var1 && (((IsoThumpable)var3).isDoor() || ((IsoThumpable)var3).isWindow())) {
    return var3;
         }

         if (dynamic_cast<IsoWindow*>(var3) != nullptr && ((IsoWindow)var3).north == var1) {
    return var3;
         }
      }

    return nullptr;
   }

    IsoObject getDoorOrWindowOrWindowFrame(IsoDirections var1, bool var2) {
      for (int var3 = this.Objects.size() - 1; var3 >= 0; var3--) {
    IsoObject var4 = (IsoObject)this.Objects.get(var3);
    IsoDoor var5 = (IsoDoor)Type.tryCastTo(var4, IsoDoor.class);
    IsoThumpable var6 = (IsoThumpable)Type.tryCastTo(var4, IsoThumpable.class);
    IsoWindow var7 = (IsoWindow)Type.tryCastTo(var4, IsoWindow.class);
         if (var5 != nullptr && var5.getSpriteEdge(var2) == var1) {
    return var4;
         }

         if (var6 != nullptr && var6.getSpriteEdge(var2) == var1) {
    return var4;
         }

         if (var7 != nullptr) {
            if (var7.north && var1 == IsoDirections.N) {
    return var4;
            }

            if (!var7.north && var1 == IsoDirections.W) {
    return var4;
            }
         }

         if (IsoWindowFrame.isWindowFrame(var4)) {
            if (IsoWindowFrame.isWindowFrame(var4, true) && var1 == IsoDirections.N) {
    return var4;
            }

            if (IsoWindowFrame.isWindowFrame(var4, false) && var1 == IsoDirections.W) {
    return var4;
            }
         }
      }

    return nullptr;
   }

    IsoObject getOpenDoor(IsoDirections var1) {
      for (int var2 = 0; var2 < this.SpecialObjects.size(); var2++) {
    IsoObject var3 = this.SpecialObjects.get(var2);
    IsoDoor var4 = (IsoDoor)Type.tryCastTo(var3, IsoDoor.class);
    IsoThumpable var5 = (IsoThumpable)Type.tryCastTo(var3, IsoThumpable.class);
         if (var4 != nullptr && var4.open && var4.getSpriteEdge(false) == var1) {
    return var4;
         }

         if (var5 != nullptr && var5.open && var5.getSpriteEdge(false) == var1) {
    return var5;
         }
      }

    return nullptr;
   }

    void removeWorldObject(IsoWorldInventoryObject var1) {
      if (var1 != nullptr) {
         var1.removeFromWorld();
         var1.removeFromSquare();
      }
   }

    void removeAllWorldObjects() {
      for (int var1 = 0; var1 < this.getWorldObjects().size(); var1++) {
    IsoObject var2 = (IsoObject)this.getWorldObjects().get(var1);
         var2.removeFromWorld();
         var2.removeFromSquare();
         var1--;
      }
   }

   public std::vector<IsoWorldInventoryObject> getWorldObjects() {
      return this.WorldObjects;
   }

   public PZArrayList<IsoObject> getLocalTemporaryObjects() {
      return this.localTemporaryObjects;
   }

    KahluaTable getModData() {
      if (this.table == nullptr) {
         this.table = LuaManager.platform.newTable();
      }

      return this.table;
   }

    bool hasModData() {
      return this.table != nullptr && !this.table.empty();
   }

    ZomboidBitFlag getHasTypes() {
      return this.hasTypes;
   }

    void setVertLight(int var1, int var2, int var3) {
      this.lighting[var3].lightverts(var1, var2);
   }

    int getVertLight(int var1, int var2) {
      return this.lighting[var2].lightverts(var1);
   }

    void setRainDrop(IsoRaindrop var1) {
      this.RainDrop = var1;
   }

    IsoRaindrop getRainDrop() {
      return this.RainDrop;
   }

    void setRainSplash(IsoRainSplash var1) {
      this.RainSplash = var1;
   }

    IsoRainSplash getRainSplash() {
      return this.RainSplash;
   }

    Zone getZone() {
      return this.zone;
   }

    std::string getZoneType() {
      return this.zone != nullptr ? this.zone.getType() : nullptr;
   }

    bool isOverlayDone() {
      return this.overlayDone;
   }

    void setOverlayDone(bool var1) {
      this.overlayDone = var1;
   }

    Square getErosionData() {
      if (this.erosion == nullptr) {
         this.erosion = std::make_unique<Square>();
      }

      return this.erosion;
   }

    void disableErosion() {
    Square var1 = this.getErosionData();
      if (var1 != nullptr && !var1.doNothing) {
         var1.doNothing = true;
      }
   }

    void removeErosionObject(const std::string& var1) {
      if (this.erosion != nullptr) {
         if ("WallVines" == var1)) {
            for (int var2 = 0; var2 < this.erosion.regions.size(); var2++) {
    Data var3 = (Data)this.erosion.regions.get(var2);
               if (var3.regionID == 2 && var3.categoryID == 0) {
                  this.erosion.regions.remove(var2);
                  break;
               }
            }
         }
      }
   }

    void syncIsoTrap(HandWeapon var1) {
    ByteBufferWriter var2 = GameClient.connection.startPacket();
      PacketType.AddExplosiveTrap.doPacket(var2);
      var2.putInt(this.getX());
      var2.putInt(this.getY());
      var2.putInt(this.getZ());

      try {
         var1.saveWithSize(var2.bb, false);
      } catch (Exception var4) {
         ExceptionLogger.logException(var4);
      }

      PacketType.AddExplosiveTrap.send(GameClient.connection);
   }

    void drawCircleExplosion(int var1, IsoTrap var2, ExplosionMode var3) {
      if (var1 > 15) {
         var1 = 15;
      }

      for (int var4 = this.getX() - var1; var4 <= this.getX() + var1; var4++) {
         for (int var5 = this.getY() - var1; var5 <= this.getY() + var1; var5++) {
            if (!(IsoUtils.DistanceTo(var4 + 0.5F, var5 + 0.5F, this.getX() + 0.5F, this.getY() + 0.5F) > var1)) {
    TestResults var6 = LosUtil.lineClear(this.getCell(), (int)var2.getX(), (int)var2.getY(), (int)var2.getZ(), var4, var5, this.z, false);
               if (var6 != TestResults.Blocked && var6 != TestResults.ClearThroughClosedDoor) {
    IsoGridSquare var7 = this.getCell().getGridSquare(var4, var5, this.getZ());
                  if (var7 != nullptr && NonPvpZone.getNonPvpZone(var7.getX(), var7.getY()) == nullptr) {
                     if (var3 == ExplosionMode.Smoke) {
                        if (!GameClient.bClient && Rand.Next(2) == 0) {
                           IsoFireManager.StartSmoke(this.getCell(), var7, true, 40, 0);
                        }

                        var7.smoke();
                     }

                     if (var3 == ExplosionMode.Explosion) {
                        if (!GameClient.bClient && var2.getExplosionPower() > 0 && Rand.Next(80 - var2.getExplosionPower()) <= 0) {
                           var7.Burn();
                        }

                        var7.explosion(var2);
                        if (!GameClient.bClient && var2.getExplosionPower() > 0 && Rand.Next(100 - var2.getExplosionPower()) == 0) {
                           IsoFireManager.StartFire(this.getCell(), var7, true, 20);
                        }
                     }

                     if (var3 == ExplosionMode.Fire && !GameClient.bClient && Rand.Next(100 - var2.getFirePower()) == 0) {
                        IsoFireManager.StartFire(this.getCell(), var7, true, 40);
                     }

                     if (var3 == ExplosionMode.Sensor) {
                        var7.setTrapPositionX(this.getX());
                        var7.setTrapPositionY(this.getY());
                        var7.setTrapPositionZ(this.getZ());
                     }
                  }
               }
            }
         }
      }
   }

    void explosion(IsoTrap var1) {
      if (!GameServer.bServer || !var1.isInstantExplosion()) {
         for (int var2 = 0; var2 < this.getMovingObjects().size(); var2++) {
    IsoMovingObject var3 = this.getMovingObjects().get(var2);
            if (dynamic_cast<IsoGameCharacter*>(var3) != nullptr) {
               if (GameServer.bServer || !(dynamic_cast<IsoZombie*>(var3) != nullptr) || ((IsoZombie)var3).isLocal()) {
    int var4 = Math.min(var1.getExplosionPower(), 80);
                  var3.Hit(
                     (HandWeapon)InventoryItemFactory.CreateItem("Base.Axe"),
                     IsoWorld.instance.CurrentCell.getFakeZombieForHit(),
                     Rand.Next(var4 / 30.0F, var4 / 30.0F * 2.0F) + var1.getExtraDamage(),
                     false,
                     1.0F
                  );
                  if (var1.getExplosionPower() > 0) {
    bool var5 = !(dynamic_cast<IsoZombie*>(var3) != nullptr);

                     while (var5) {
                        var5 = false;
    BodyPart var6 = ((IsoGameCharacter)var3).getBodyDamage().getBodyPart(BodyPartType.FromIndex(Rand.Next(15)));
                        var6.setBurned();
                        if (Rand.Next((100 - var4) / 2) == 0) {
                           var5 = true;
                        }
                     }
                  }
               }

               if (GameClient.bClient && dynamic_cast<IsoZombie*>(var3) != nullptr && ((IsoZombie)var3).isRemoteZombie()) {
                  var3.Hit((HandWeapon)InventoryItemFactory.CreateItem("Base.Axe"), IsoWorld.instance.CurrentCell.getFakeZombieForHit(), 0.0F, true, 0.0F);
               }
            }
         }
      }
   }

    void smoke() {
      for (int var1 = 0; var1 < this.getMovingObjects().size(); var1++) {
    IsoMovingObject var2 = this.getMovingObjects().get(var1);
         if (dynamic_cast<IsoZombie*>(var2) != nullptr) {
            ((IsoZombie)var2).setTarget(nullptr);
            ((IsoZombie)var2).changeState(ZombieIdleState.instance());
         }
      }
   }

    void explodeTrap() {
    IsoGridSquare var1 = this.getCell().getGridSquare(this.getTrapPositionX(), this.getTrapPositionY(), this.getTrapPositionZ());
      if (var1 != nullptr) {
         for (int var2 = 0; var2 < var1.getObjects().size(); var2++) {
    IsoObject var3 = (IsoObject)var1.getObjects().get(var2);
            if (dynamic_cast<IsoTrap*>(var3) != nullptr var4) {
               var4.triggerExplosion(false);
    IsoGridSquare var5 = nullptr;
    int var6 = var4.getSensorRange();

               for (int var7 = var1.getX() - var6; var7 <= var1.getX() + var6; var7++) {
                  for (int var8 = var1.getY() - var6; var8 <= var1.getY() + var6; var8++) {
                     if (IsoUtils.DistanceTo(var7 + 0.5F, var8 + 0.5F, var1.getX() + 0.5F, var1.getY() + 0.5F) <= var6) {
                        var5 = this.getCell().getGridSquare(var7, var8, this.getZ());
                        if (var5 != nullptr) {
                           var5.setTrapPositionX(-1);
                           var5.setTrapPositionY(-1);
                           var5.setTrapPositionZ(-1);
                        }
                     }
                  }
               }

               return;
            }
         }
      }
   }

    int getTrapPositionX() {
      return this.trapPositionX;
   }

    void setTrapPositionX(int var1) {
      this.trapPositionX = var1;
   }

    int getTrapPositionY() {
      return this.trapPositionY;
   }

    void setTrapPositionY(int var1) {
      this.trapPositionY = var1;
   }

    int getTrapPositionZ() {
      return this.trapPositionZ;
   }

    void setTrapPositionZ(int var1) {
      this.trapPositionZ = var1;
   }

    bool haveElectricity() {
      if ((this.chunk == nullptr || !this.chunk.bLoaded) && this.haveElectricity) {
    return true;
      } else {
         return !SandboxOptions.getInstance().AllowExteriorGenerator.getValue() && this.Is(IsoFlagType.exterior)
            ? false
            : this.chunk != nullptr && this.chunk.isGeneratorPoweringSquare(this.x, this.y, this.z);
      }
   }

    void setHaveElectricity(bool var1) {
      if (!var1) {
         this.haveElectricity = false;
      }

      if (this.getObjects() != nullptr) {
         for (int var2 = 0; var2 < this.getObjects().size(); var2++) {
            if (this.getObjects().get(var2) instanceof IsoLightSwitch) {
               ((IsoLightSwitch)this.getObjects().get(var2)).update();
            }
         }
      }
   }

    IsoGenerator getGenerator() {
      if (this.getSpecialObjects() != nullptr) {
         for (int var1 = 0; var1 < this.getSpecialObjects().size(); var1++) {
            if (this.getSpecialObjects().get(var1) instanceof IsoGenerator) {
               return (IsoGenerator)this.getSpecialObjects().get(var1);
            }
         }
      }

    return nullptr;
   }

    void stopFire() {
      IsoFireManager.RemoveAllOn(this);
      this.getProperties().Set(IsoFlagType.burntOut);
      this.getProperties().UnSet(IsoFlagType.burning);
      this.burntOut = true;
   }

    void transmitStopFire() {
      if (GameClient.bClient) {
         GameClient.sendStopFire(this);
      }
   }

    long playSound(const std::string& var1) {
    BaseSoundEmitter var2 = IsoWorld.instance.getFreeEmitter(this.x + 0.5F, this.y + 0.5F, this.z);
      return var2.playSound(var1);
   }

    long playSound(const std::string& var1, bool var2) {
    BaseSoundEmitter var3 = IsoWorld.instance.getFreeEmitter(this.x + 0.5F, this.y + 0.5F, this.z);
      return var3.playSound(var1, var2);
   }

    void FixStackableObjects() {
    IsoObject var1 = nullptr;

      for (int var2 = 0; var2 < this.Objects.size(); var2++) {
    IsoObject var3 = (IsoObject)this.Objects.get(var2);
         if (!(dynamic_cast<IsoWorldInventoryObject*>(var3) != nullptr) && var3.sprite != nullptr) {
    PropertyContainer var4 = var3.sprite.getProperties();
            if (var4.getStackReplaceTileOffset() != 0) {
               var3.sprite = IsoSprite.getSprite(IsoSpriteManager.instance, var3.sprite.ID + var4.getStackReplaceTileOffset());
               if (var3.sprite == nullptr) {
                  continue;
               }

               var4 = var3.sprite.getProperties();
            }

            if (var4.isTable() || var4.isTableTop()) {
    float var5 = var4.isSurfaceOffset() ? var4.getSurface() : 0.0F;
               if (var1 != nullptr) {
                  var3.setRenderYOffset(var1.getRenderYOffset() + var1.getSurfaceOffset() - var5);
               } else {
                  var3.setRenderYOffset(0.0F - var5);
               }
            }

            if (var4.isTable()) {
               var1 = var3;
            }

            if (dynamic_cast<IsoLightSwitch*>(var3) != nullptr && var4.isTableTop() && var1 != nullptr && !var4.Is("IgnoreSurfaceSnap")) {
    int var14 = PZMath.tryParseInt(var4.Val("Noffset"), 0);
    int var6 = PZMath.tryParseInt(var4.Val("Soffset"), 0);
    int var7 = PZMath.tryParseInt(var4.Val("Woffset"), 0);
    int var8 = PZMath.tryParseInt(var4.Val("Eoffset"), 0);
    std::string var9 = var4.Val("Facing");
    PropertyContainer var10 = var1.getProperties();
    std::string var11 = var10.Val("Facing");
               if (!StringUtils.isNullOrWhitespace(var11) && !var11 == var9)) {
    int var12 = 0;
                  if ("N" == var11)) {
                     if (var14 != 0) {
                        var12 = var14;
                     } else if (var6 != 0) {
                        var12 = var6;
                     }
                  } else if ("S" == var11)) {
                     if (var6 != 0) {
                        var12 = var6;
                     } else if (var14 != 0) {
                        var12 = var14;
                     }
                  } else if ("W" == var11)) {
                     if (var7 != 0) {
                        var12 = var7;
                     } else if (var8 != 0) {
                        var12 = var8;
                     }
                  } else if ("E" == var11)) {
                     if (var8 != 0) {
                        var12 = var8;
                     } else if (var7 != 0) {
                        var12 = var7;
                     }
                  }

                  if (var12 != 0) {
    IsoSprite var13 = IsoSpriteManager.instance.getSprite(var3.sprite.ID + var12);
                     if (var13 != nullptr) {
                        var3.setSprite(var13);
                     }
                  }
               }
            }
         }
      }
   }

    void fixPlacedItemRenderOffsets() {
      IsoObject[] var1 = (IsoObject[])this.Objects.getElements();
    int var2 = this.Objects.size();
    int var3 = 0;

      for (int var4 = 0; var4 < var2; var4++) {
    IsoObject var5 = var1[var4];
    int var6 = PZMath.roundToInt(var5.getSurfaceOffsetNoTable());
         if (!(var6 <= 0.0F) && !PZArrayUtil.contains(SURFACE_OFFSETS, var3, var6)) {
            SURFACE_OFFSETS[var3++] = var6;
         }
      }

      if (var3 == 0) {
         SURFACE_OFFSETS[var3++] = 0;
      }

      for (int var10 = 0; var10 < var2; var10++) {
    IsoObject var11 = var1[var10];
    IsoWorldInventoryObject var12 = (IsoWorldInventoryObject)Type.tryCastTo(var11, IsoWorldInventoryObject.class);
         if (var12 != nullptr) {
    int var7 = PZMath.roundToInt(var12.zoff * 96.0F);
    int var8 = 0;

            for (int var9 = 0; var9 < var3; var9++) {
               if (var7 <= SURFACE_OFFSETS[var9]) {
                  var8 = SURFACE_OFFSETS[var9];
                  break;
               }

               var8 = SURFACE_OFFSETS[var9];
               if (var9 < var3 - 1 && var7 < SURFACE_OFFSETS[var9 + 1]) {
                  break;
               }
            }

            var12.zoff = var8 / 96.0F;
         }
      }
   }

    BaseVehicle getVehicleContainer() {
    int var1 = (int)((this.x - 4.0F) / 10.0F);
    int var2 = (int)((this.y - 4.0F) / 10.0F);
    int var3 = (int)Math.ceil((this.x + 4.0F) / 10.0F);
    int var4 = (int)Math.ceil((this.y + 4.0F) / 10.0F);

      for (int var5 = var2; var5 < var4; var5++) {
         for (int var6 = var1; var6 < var3; var6++) {
    IsoChunk var7 = GameServer.bServer ? ServerMap.instance.getChunk(var6, var5) : IsoWorld.instance.CurrentCell.getChunk(var6, var5);
            if (var7 != nullptr) {
               for (int var8 = 0; var8 < var7.vehicles.size(); var8++) {
    BaseVehicle var9 = (BaseVehicle)var7.vehicles.get(var8);
                  if (var9.isIntersectingSquare(this.x, this.y, this.z)) {
    return var9;
                  }
               }
            }
         }
      }

    return nullptr;
   }

    bool isVehicleIntersecting() {
    int var1 = (int)((this.x - 4.0F) / 10.0F);
    int var2 = (int)((this.y - 4.0F) / 10.0F);
    int var3 = (int)Math.ceil((this.x + 4.0F) / 10.0F);
    int var4 = (int)Math.ceil((this.y + 4.0F) / 10.0F);

      for (int var5 = var2; var5 < var4; var5++) {
         for (int var6 = var1; var6 < var3; var6++) {
    IsoChunk var7 = GameServer.bServer ? ServerMap.instance.getChunk(var6, var5) : IsoWorld.instance.CurrentCell.getChunk(var6, var5);
            if (var7 != nullptr) {
               for (int var8 = 0; var8 < var7.vehicles.size(); var8++) {
    BaseVehicle var9 = (BaseVehicle)var7.vehicles.get(var8);
                  if (var9.isIntersectingSquare(this.x, this.y, this.z)) {
    return true;
                  }
               }
            }
         }
      }

    return false;
   }

    IsoCompost getCompost() {
      if (this.getSpecialObjects() != nullptr) {
         for (int var1 = 0; var1 < this.getSpecialObjects().size(); var1++) {
            if (this.getSpecialObjects().get(var1) instanceof IsoCompost) {
               return (IsoCompost)this.getSpecialObjects().get(var1);
            }
         }
      }

    return nullptr;
   }

    void setIsoWorldRegion(IsoWorldRegion var1) {
      this.hasSetIsoWorldRegion = var1 != nullptr;
      this.isoWorldRegion = var1;
   }

    IWorldRegion getIsoWorldRegion() {
      if (GameServer.bServer) {
         return IsoRegions.getIsoWorldRegion(this.x, this.y, this.z);
      } else {
         if (!this.hasSetIsoWorldRegion) {
            this.isoWorldRegion = IsoRegions.getIsoWorldRegion(this.x, this.y, this.z);
            this.hasSetIsoWorldRegion = true;
         }

         return this.isoWorldRegion;
      }
   }

    void ResetIsoWorldRegion() {
      this.isoWorldRegion = nullptr;
      this.hasSetIsoWorldRegion = false;
   }

    bool isInARoom() {
      return this.getRoom() != nullptr || this.getIsoWorldRegion() != nullptr && this.getIsoWorldRegion().isPlayerRoom();
   }

    int getRoomSize() {
      if (this.getRoom() != nullptr) {
         return this.getRoom().getSquares().size();
      } else {
         return this.getIsoWorldRegion() != nullptr && this.getIsoWorldRegion().isPlayerRoom() ? this.getIsoWorldRegion().getSquareSize() : -1;
      }
   }

    int getWallType() {
    uint8_t var1 = 0;
      if (this.getProperties().Is(IsoFlagType.WallN)) {
         var1 |= 1;
      }

      if (this.getProperties().Is(IsoFlagType.WallW)) {
         var1 |= 4;
      }

      if (this.getProperties().Is(IsoFlagType.WallNW)) {
         var1 |= 5;
      }

    IsoGridSquare var2 = this.nav[IsoDirections.E.index()];
      if (var2 != nullptr && (var2.getProperties().Is(IsoFlagType.WallW) || var2.getProperties().Is(IsoFlagType.WallNW))) {
         var1 |= 8;
      }

    IsoGridSquare var3 = this.nav[IsoDirections.S.index()];
      if (var3 != nullptr && (var3.getProperties().Is(IsoFlagType.WallN) || var3.getProperties().Is(IsoFlagType.WallNW))) {
         var1 |= 2;
      }

    return var1;
   }

    int getPuddlesDir() {
    uint8_t var1 = PuddlesDirection.PUDDLES_DIR_ALL;
      if (this.isInARoom()) {
         return PuddlesDirection.PUDDLES_DIR_NONE;
      } else {
         for (int var2 = 0; var2 < this.getObjects().size(); var2++) {
    IsoObject var3 = (IsoObject)this.getObjects().get(var2);
            if (var3.AttachedAnimSprite != nullptr) {
               for (int var4 = 0; var4 < var3.AttachedAnimSprite.size(); var4++) {
    IsoSprite var5 = ((IsoSpriteInstance)var3.AttachedAnimSprite.get(var4)).parentSprite;
                  if (var5.name != nullptr) {
                     if (var5.name == "street_trafficlines_01_2")
                        || var5.name == "street_trafficlines_01_6")
                        || var5.name == "street_trafficlines_01_22")
                        || var5.name == "street_trafficlines_01_32")) {
                        var1 = PuddlesDirection.PUDDLES_DIR_NW;
                     }

                     if (var5.name == "street_trafficlines_01_4")
                        || var5.name == "street_trafficlines_01_0")
                        || var5.name == "street_trafficlines_01_16")) {
                        var1 = PuddlesDirection.PUDDLES_DIR_NE;
                     }
                  }
               }
            }
         }

    return var1;
      }
   }

    bool haveFire() {
    int var1 = this.Objects.size();
      IsoObject[] var2 = (IsoObject[])this.Objects.getElements();

      for (int var3 = 0; var3 < var1; var3++) {
    IsoObject var4 = var2[var3];
         if (dynamic_cast<IsoFire*>(var4) != nullptr) {
    return true;
         }
      }

    return false;
   }

    IsoBuilding getRoofHideBuilding() {
      return this.roofHideBuilding;
   }

    IsoGridSquare getAdjacentSquare(IsoDirections var1) {
      return this.nav[var1.index()];
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    IsoGridSquare getAdjacentPathSquare(IsoDirections var1) {
      switch (1.$SwitchMap$zombie$iso$IsoDirections[var1.ordinal()]) {
         case 1:
            return this.nw;
         case 2:
            return this.n;
         case 3:
            return this.ne;
         case 4:
            return this.w;
         case 5:
            return this.e;
         case 6:
            return this.sw;
         case 7:
            return this.s;
         case 8:
            return this.se;
         default:
    return nullptr;
      }
   }

    float getApparentZ(float var1, float var2) {
      var1 = PZMath.clamp(var1, 0.0F, 1.0F);
      var2 = PZMath.clamp(var2, 0.0F, 1.0F);
      if (this.Has(IsoObjectType.stairsTN)) {
         return this.getZ() + PZMath.lerp(0.6666F, 1.0F, 1.0F - var2);
      } else if (this.Has(IsoObjectType.stairsTW)) {
         return this.getZ() + PZMath.lerp(0.6666F, 1.0F, 1.0F - var1);
      } else if (this.Has(IsoObjectType.stairsMN)) {
         return this.getZ() + PZMath.lerp(0.3333F, 0.6666F, 1.0F - var2);
      } else if (this.Has(IsoObjectType.stairsMW)) {
         return this.getZ() + PZMath.lerp(0.3333F, 0.6666F, 1.0F - var1);
      } else if (this.Has(IsoObjectType.stairsBN)) {
         return this.getZ() + PZMath.lerp(0.01F, 0.3333F, 1.0F - var2);
      } else {
         return this.Has(IsoObjectType.stairsBW) ? this.getZ() + PZMath.lerp(0.01F, 0.3333F, 1.0F - var1) : this.getZ();
      }
   }

    float getTotalWeightOfItemsOnFloor() {
    float var1 = 0.0F;

      for (int var2 = 0; var2 < this.WorldObjects.size(); var2++) {
    InventoryItem var3 = this.WorldObjects.get(var2).getItem();
         if (var3 != nullptr) {
            var1 += var3.getUnequippedWeight();
         }
      }

    return var1;
   }

    bool getCollideMatrix(int var1, int var2, int var3) {
    return getMatrixBit(var1 +, var2 +, var3 +);
   }

    bool getPathMatrix(int var1, int var2, int var3) {
    return getMatrixBit(var1 +, var2 +, var3 +);
   }

    bool getVisionMatrix(int var1, int var2, int var3) {
    return getMatrixBit(var1 +, var2 +, var3 +);
   }

    void checkRoomSeen(int var1) {
    IsoRoom var2 = this.getRoom();
      if (var2 != nullptr && var2.def != nullptr && !var2.def.bExplored) {
    IsoPlayer var3 = IsoPlayer.players[var1];
         if (var3 != nullptr) {
            if (this.z == (int)var3.z) {
    uint8_t var4 = 10;
               if (var3.getBuilding() == var2.building) {
                  var4 = 50;
               }

               if (IsoUtils.DistanceToSquared(var3.x, var3.y, this.x + 0.5F, this.y + 0.5F) < var4 * var4) {
                  var2.def.bExplored = true;
                  var2.onSee();
                  var2.seen = 0;
               }
            }
         }
      }
   }

    bool hasFlies() {
      return this.bHasFlies;
   }

    void setHasFlies(bool var1) {
      this.bHasFlies = var1;
   }

    float getLightLevel(int var1) {
      return (this.lighting[var1].lightInfo().r + this.lighting[var1].lightInfo().g + this.lighting[var1].lightInfo().b) / 3.0F;
   }
}
} // namespace iso
} // namespace zombie
