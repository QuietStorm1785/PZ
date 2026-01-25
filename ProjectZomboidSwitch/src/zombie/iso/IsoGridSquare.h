#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

// Forward declarations for dependencies
namespace zombie { namespace iso {
    class IsoObject;
    class IsoDoor;
    class IsoThumpable;
    class IsoWindow;
    class IsoCurtain;
    class IsoDeadBody;
    class IsoBrokenGlass;
    class IsoTree;
    class IsoWorldInventoryObject;
    class IsoGameCharacter;
    class IsoChunk;
    class IsoRoom;
    class IsoBuilding;
    class IsoGridOcclusionData;
    class IsoWaterGeometry;
    class IsoPuddlesGeometry;
    class PropertyContainer;
    class ZomboidBitFlag;
    class ColorInfo;
    class Vector2;
    class Square;
    class Zone;
    class IWorldRegion;
    class KahluaTable;
    class Item;
    class Texture;
    class Shader;
    class ShaderProgram;
    class PerformanceProfileProbe;
    class TextureDraw;
    class WallShaperWhole;
    class WallShaperN;
    class WallShaperW;
    class FloorShaperDiamond;
    class FloorShaperDeDiamond;
    class FloorShaperAttachedSprites;
    class RainManager;
    class PolygonalMap2;
    class BaseVehicle;
    class CellGetSquare;
    class IsoDirections;
    class IsoObjectType;
    class IsoFlagType;
    class IsoCamera;
    class IsoSprite;
    class IsoSpriteInstance;
    class IsoSpriteManager;
    class WeatherFxMask;
    class GameClient;
    class GameServer;
    class PacketType;
    class ServerLighting;
    class ServerMap;
    class ServerOptions;
    class ScriptManager;
    class StringUtils;
    class Type;
    class BitHeader;
    class BitHeaderRead;
    class BitHeaderWrite;
    class PZArrayList;
    class PZArrayUtil;
    class IndieGL;
    class DebugLog;
    class DebugOptions;
    class DebugType;
    class ErosionData;
    class ErosionCategoryData;
    class InventoryItem;
    class InventoryItemFactory;
    class Food;
    class HandWeapon;
    class BodyPart;
    class BodyPartType;
    class BaseSoundEmitter;
    class LuaEventManager;
    class LuaManager;
    class GameTime;
    class GameWindow;
    class ExceptionLogger;
    class RenderSettings;
    class SpriteRenderer;
    class WallShaderTexRender;
    class Meta;
    class NonPvpZone;
    class SafeHouse;
    class IsoRegions;
    class IsoWorldRegion;
    class RainSplash;
    class Raindrop;
    class IsoMetaGrid;
    class IsoGridStack;
    class IsoHeatSource;
    class IsoLightSource;
    class IsoLot;
    class IsoLuaMover;
    class IsoMarkers;
    class IsoMetaCell;
    class IsoMetaChunk;
    class IsoMetaGridLoaderThread;
    class IsoMetaGridRoomTone;
    class IsoMetaGridTrigger;
    class IsoMetaGridVehicleZone;
    class IsoMetaGridZonePolygonHit;
    class IsoMetaGridZone;
    class IsoMetaGridZoneGeometryType;
    class IsoMovingObject;
    class IsoPhysicsObject;
    class IsoPuddles;
    class IsoPuddlesCompute;
    class IsoRoofFixer;
    class IsoRoomLight;
    class IsoUtils;
    class IsoWallBloodSplat;
    class IsoWater;
    class IsoWaterFlow;
    class IsoWorld;
    class LightingJNI;
    class LightingThread;
    class LosUtilTestResults;
    class LotHeader;
    class MetaObject;
    class MultiStageBuilding;
    class NearestWalls;
    class ObjectsSyncRequests;
    class Particles;
    class ParticlesArray;
    class ParticlesFire;
    class PlayerCamera;
    class PuddlesShader;
    class RoomDef;
    class SearchMode;
    class SliceY;
    class SmokeShader;
    class SpawnPoints;
    class TallFenceShader;
    class TileOverlays;
    class WaterShader;
    class WorldConverter;
    class WorldMarkers;
    class WorldObjectsSyncRequests;
    class WorldReuserThread;
    class WorldStreamer;
}}

namespace zombie {
namespace iso {

class IsoGridSquare {
public:
    // --- Nested and related types ---
    // 1. Synthetic switch map for IsoDirections
    struct SwitchMapIsoDirections {
        int map[8] = {1,2,3,4,5,6,7,8};
    };

    // 2. GetSquare interface
    struct GetSquare {
        virtual IsoGridSquare* getGridSquare(int x, int y, int z) = 0;
        virtual ~GetSquare() = default;
    };

    // 3. CellGetSquare implementation
    struct CellGetSquare : public GetSquare {
        IsoGridSquare* getGridSquare(int x, int y, int z) override;
    };

    // 4. ILighting interface
    struct ILighting {
        virtual int lightverts(int idx) = 0;
        virtual float lampostTotalR() = 0;
        virtual float lampostTotalG() = 0;
        virtual float lampostTotalB() = 0;
        virtual bool bSeen() = 0;
        virtual bool bCanSee() = 0;
        virtual bool bCouldSee() = 0;
        virtual float darkMulti() = 0;
        virtual float targetDarkMulti() = 0;
        virtual ColorInfo* lightInfo() = 0;
        virtual void lightverts(int idx, int val) = 0;
        virtual void lampostTotalR(float val) = 0;
        virtual void lampostTotalG(float val) = 0;
        virtual void lampostTotalB(float val) = 0;
        virtual void bSeen(bool val) = 0;
        virtual void bCanSee(bool val) = 0;
        virtual void bCouldSee(bool val) = 0;
        virtual void darkMulti(float val) = 0;
        virtual void targetDarkMulti(float val) = 0;
        virtual int resultLightCount() = 0;
        virtual void reset() = 0;
        virtual ~ILighting() = default;
    };

    // 5. Lighting implementation
    struct Lighting : public ILighting {
        int lightvertsArr[8] = {0};
        float lampostTotalR_ = 0.0f, lampostTotalG_ = 0.0f, lampostTotalB_ = 0.0f;
        bool bSeen_ = false, bCanSee_ = false, bCouldSee_ = false;
        float darkMulti_ = 0.0f, targetDarkMulti_ = 0.0f;
        std::unique_ptr<ColorInfo> lightInfo_;
        Lighting();
        int lightverts(int idx) override;
        float lampostTotalR() override;
        float lampostTotalG() override;
        float lampostTotalB() override;
        bool bSeen() override;
        bool bCanSee() override;
        bool bCouldSee() override;
        float darkMulti() override;
        float targetDarkMulti() override;
        ColorInfo* lightInfo() override;
        void lightverts(int idx, int val) override;
        void lampostTotalR(float val) override;
        void lampostTotalG(float val) override;
        void lampostTotalB(float val) override;
        void bSeen(bool val) override;
        void bCanSee(bool val) override;
        void bCouldSee(bool val) override;
        void darkMulti(float val) override;
        void targetDarkMulti(float val) override;
        int resultLightCount() override;
        void reset() override;
    };

    // 6. ResultLight
    struct ResultLight {
        int id, x, y, z, radius, flags;
        float r, g, b;
        static constexpr int RLF_NONE = 0;
        static constexpr int RLF_ROOMLIGHT = 1;
        static constexpr int RLF_TORCH = 2;
        ResultLight& copyFrom(const ResultLight& other);
    };

    // 7. PuddlesDirection
    struct PuddlesDirection {
        static constexpr uint8_t PUDDLES_DIR_NONE = 1;
        static constexpr uint8_t PUDDLES_DIR_NE = 2;
        static constexpr uint8_t PUDDLES_DIR_NW = 4;
        static constexpr uint8_t PUDDLES_DIR_ALL = 8;
    };

    // 8. RenderWallCallback
    struct RenderWallCallback {
        virtual void invoke(Texture* tex, float x, float y) = 0;
        virtual ~RenderWallCallback() = default;
    };

    // 9. CircleStencilShader
    struct CircleStencilShader /*: public Shader*/ {
        static CircleStencilShader instance;
        int a_wallShadeColor = -1;
        CircleStencilShader();
        void onCompileSuccess(ShaderProgram* prog);
    };

    // 10. NoCircleStencilShader
    struct NoCircleStencilShader {
        static NoCircleStencilShader instance;
        std::unique_ptr<ShaderProgram> shaderProgram;
        int ShaderID = -1;
        int a_wallShadeColor = -1;
        void initShader();
    };

    // 11. s_performance
    struct s_performance {
        static std::unique_ptr<PerformanceProfileProbe> renderFloor;
        s_performance() = default;
    };

    // --- Main IsoGridSquare fields and methods ---
    // Fields (ported from legacy C++/Java sources)
    int x = 0, y = 0, z = 0;
    int roomID = -1, ID = -999;
    IsoRoom* room = nullptr;
    IsoChunk* chunk = nullptr;
    Zone* zone = nullptr;
    bool haveRoof = false, burntOut = false, bHasFlies = false, haveElectricity = false;
    bool isSolidFloorCache = false, isExteriorCache = false, isVegitationCache = false, propertiesDirty = true;
    bool bFlattenGrassEtc = false, haveSheetRope = false, hasTree = false, hasSetIsoWorldRegion = false;
    int collideMatrix = -1, pathMatrix = -1, visionMatrix = -1;
    int CachedScreenValue = -1;
    float CachedScreenX = 0.0f, CachedScreenY = 0.0f;
    long hashCodeObjects = 0;
    IsoGridOcclusionData* OcclusionDataCache = nullptr;
    IWorldRegion* isoWorldRegion = nullptr;
    IsoGridSquare *w = nullptr, *nw = nullptr, *sw = nullptr, *s = nullptr, *n = nullptr, *ne = nullptr, *se = nullptr, *e = nullptr;
    std::vector<IsoGridSquare*> nav;
    std::vector<IsoObject*> Objects, SpecialObjects, localTemporaryObjects;
    std::vector<IsoMovingObject*> MovingObjects, StaticMovingObjects;
    std::vector<IsoGameCharacter*> DeferedCharacters;
    std::vector<IsoWorldInventoryObject*> WorldObjects;
    std::vector<ColorInfo*> lightInfo;
    std::vector<ILighting*> lighting;
    IsoWaterGeometry* water = nullptr;
    IsoPuddlesGeometry* puddles = nullptr;
    float puddlesCacheSize = -1.0f, puddlesCacheLevel = -1.0f;
    KahluaTable* table = nullptr;
    PropertyContainer Properties;
    ZomboidBitFlag hasTypes;
    int DeferredCharacterTick = -1, ObjectsSyncCount = 0, hourLastSeen = INT32_MIN;
    int trapPositionX = -1, trapPositionY = -1, trapPositionZ = -1;
    IsoRaindrop* RainDrop = nullptr;
    IsoRainSplash* RainSplash = nullptr;
    Square* erosion = nullptr;
    float splashX = 0.0f, splashY = 0.0f, splashFrame = -1.0f;
    int splashFrameNum = 0;
    bool overlayDone = false;
    IsoBuilding* roofHideBuilding = nullptr;
    std::vector<float> LightInfluenceR, LightInfluenceG, LightInfluenceB;
    // Static fields (as static members)
    static IsoGridSquare* lastLoaded;
    static int IDMax;
    static CellGetSquare cellGetSquare;
    static bool UseSlowCollision, bDoSlowPathfinding;
    static int gridSquareCacheEmptyTimer;
    static float darkStep;
    static int RecalcLightTime, lightcache;
    static bool USE_WALL_SHADER;
    static bool bWallCutawayW, bWallCutawayN;
    static bool isOnScreenLast;
    static std::vector<std::string> rainsplashCache;
    static ColorInfo defColorInfo, blackColorInfo, lightInfoTemp;
    static int col, path, pathdoor, vision;
    static int colu, coll, colr, colu2, coll2, colr2;
    static int cutawayY, cutawayNWWidth, cutawayNWHeight, cutawaySEXCut, cutawaySEXUncut, cutawaySEWidth, cutawaySEHeight;
    static int cutawayNXFullyCut, cutawayNXCutW, cutawayNXUncut, cutawayNXCutE;
    static int cutawayWXFullyCut, cutawayWXCutS, cutawayWXUncut, cutawayWXCutN;
    static int cutawayFenceXOffset, cutawayLogWallXOffset, cutawayMedicalCurtainWXOffset, cutawaySpiffoWindowXOffset;
    static int cutawayRoof4XOffset, cutawayRoof17XOffset, cutawayRoof28XOffset, cutawayRoof41XOffset;
    static int WALL_TYPE_N, WALL_TYPE_S, WALL_TYPE_W, WALL_TYPE_E;
    static int SURFACE_OFFSETS[8];
    static long torchTimer;
    static std::vector<IsoGridSquare*> choices;
    static std::deque<IsoGridSquare*> loadGridSquareCache;
    static std::queue<IsoGridSquare*> isoGridSquareCache;

    // --- Methods (ported from legacy C++/Java sources) ---
    IsoWaterGeometry* getWater();
    void clearWater();
    IsoPuddlesGeometry* getPuddles();
    void clearPuddles();
    float getPuddlesInGround();
    IsoGridOcclusionData* getOcclusionData();
    IsoGridOcclusionData* getOrCreateOcclusionData();
    void softClear();
    float getGridSneakModifier(bool);
    bool isSomethingTo(IsoGridSquare*);
    IsoObject* getTransparentWallTo(IsoGridSquare*);
    void setPlayerCutawayFlag(int, bool, long);
    bool getPlayerCutawayFlag(int, long);
    void setIsDissolved(int, bool, long);
    bool getIsDissolved(int, long);
    static bool getMatrixBit(int, int, int, int);
    static int setMatrixBit(int, int, int, int, bool);

    // Additional methods from legacy sources (declarations only)
    void clear();
    void softReset();
    void RecalcProperties();
    void RecalcPropertiesIfNeeded();
    void ReCalculateCollide(IsoGridSquare*);
    void ReCalculatePathFind(IsoGridSquare*);
    void ReCalculateVisionBlocked(IsoGridSquare*);
    bool TreatAsSolidFloor();
    void AddSpecialTileObject(IsoObject*);
    void renderCharacters(int, bool, bool);
    void renderDeferredCharacters(int);
    void switchLight(bool);
    void removeLightSwitch();
    bool IsOnScreen();
    bool IsOnScreen(bool);
    void cacheLightInfo();
    void setLightInfoServerGUIOnly(ColorInfo*);
    int renderFloor(Shader*);
    int renderFloorInternal(Shader*);
    // ...add more as needed for full parity...
};

} // namespace iso
} // namespace zombie
