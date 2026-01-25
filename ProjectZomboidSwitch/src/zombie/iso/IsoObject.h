#pragma once
#include <string>
#include <vector>
#include <memory>
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoSprite.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoObjectType.h"
#include "zombie/iso/IsoObjectPicker.h"
#include "zombie/iso/IsoObjectID.h"
// ...include other dependencies as needed

namespace zombie {
namespace iso {


class IsoObject {
public:
    // --- Static fields ---
    static constexpr uint8_t OBF_Highlighted = 1;
    static constexpr uint8_t OBF_HighlightRenderOnce = 2;
    static constexpr uint8_t OBF_Blink = 4;
    // Nested factory and type classes (from IsoObject$N.h and IsoObject$IsoObjectFactory.h)
    class IsoObjectFactory {
    public:
        uint8_t classID;
        std::string objectName;
        int hashCode;

        IsoObjectFactory(uint8_t id, const std::string& name)
            : classID(id), objectName(name), hashCode(std::hash<std::string>{}(name)) {}

        virtual std::shared_ptr<IsoObject> InstantiateObject(/*IsoCell*/ void* var1) {
            // Default implementation, override in subclasses
            return std::make_shared<IsoObject>(var1);
        }

        uint8_t getClassID() const { return classID; }
        const std::string& getObjectName() const { return objectName; }
    };

    // Example: IsoObject$1 - IsoPlayer
    class IsoObject1Factory : public IsoObjectFactory {
    public:
        IsoObject1Factory(uint8_t id, const std::string& name) : IsoObjectFactory(id, name) {}
        std::shared_ptr<IsoObject> InstantiateObject(void* var1) override {
            // return std::make_shared<IsoPlayer>(var1);
            return nullptr; // TODO: implement
        }
    };
    // ...repeat for IsoObject2Factory, IsoObject3Factory, ... up to IsoObject36Factory, adapting type as needed...

    // IsoObject$OutlineShader
    class OutlineShader {
    public:
        // ShaderProgram shaderProgram;
        int stepSize;
        int outlineColor;
        void initShader() {/* TODO: implement */}
        void setOutlineColor(float, float, float, float) {/* TODO: implement */}
        void setStepSize(float, int, int) {/* TODO: implement */}
        bool StartShader() { return false; /* TODO: implement */ }
    };

    // IsoObject$VisionResult
    enum class VisionResult {
        NoEffect,
        Blocked,
        Unblocked
    };

    // IsoObjectPicker nested class
    class IsoObjectPicker {
    public:
        class ClickObject {
        public:
            int height;
            void* square; // IsoGridSquare*
            void* tile;   // IsoObject*
            int width, x, y, lx, ly;
            float scaleX, scaleY;
            bool flip;
            int score;
            int calculateScore() { return 0; /* TODO: port logic */ }
            int getScore() const { return score; }
        };

        int compare(const ClickObject& var1, const ClickObject& var2) {
            int var3 = var1.getScore();
            int var4 = var2.getScore();
            if (var3 > var4) return 1;
            else if (var3 < var4) return -1;
            // TODO: port tile/square logic
            return 0;
        }
    };

    // IsoObjectSyncRequests and SyncData
    class IsoObjectSyncRequests {
    public:
        struct SyncData {
            int x, y, z;
            uint8_t objIndex;
            long reqTime;
            int reqCount;
            SyncData() = default;
        };
        std::vector<SyncData> requests;
        long timeout = 1000L;
        void putRequest(/*IsoGridSquare*/ void* var1, /*IsoObject*/ void* var2) {/* TODO: implement */}
        void putRequestLoad(/*IsoGridSquare*/ void* var1) {/* TODO: implement */}
        void putRequest(int, int, int, uint8_t) {/* TODO: implement */}
        void sendRequests(/*UdpConnection*/ void* var1) {/* TODO: implement */}
        void receiveIsoSync(int, int, int, uint8_t) {/* TODO: implement */}
    };

    // ...add more nested classes/enums as needed...
    static constexpr uint8_t OBF_HighlightRenderOnce = 2;
    static constexpr uint8_t OBF_Blink = 4;
    static constexpr int MAX_WALL_SPLATS = 32;
    static const std::string PropMoveWithWind;
    static IsoObject* lastRendered;
    static IsoObject* lastRenderedRendered;
    static const ColorInfo stCol;
    static float rmod, gmod, bmod;
    static bool LowLightingQualityHack;
    static int DefaultCondition;
    static const ColorInfo stCol2;
    static const ColorInfo colFxMask;

    // --- Member fields ---
    uint8_t highlightFlags = 0;
    int keyId;
    BaseSoundEmitter* emitter;
    float sheetRopeHealth;
    bool sheetRope;
    bool bNeverDoneAlpha;
    bool bAlphaForced;
    std::vector<IsoSpriteInstance*> AttachedAnimSprite;
    std::vector<IsoWallBloodSplat*> wallBloodSplats;
    ItemContainer* container;
    IsoDirections dir;
    short Damage;
    float partialThumpDmg;
    bool NoPicking;
    float offsetX, offsetY;
    bool OutlineOnMouseover;
    IsoObject* rerouteMask;
    IsoSprite* sprite;
    IsoSprite* overlaySprite;
    ColorInfo* overlaySpriteColor;
    IsoGridSquare* square;
    float alpha[4];
    float targetAlpha[4];
    IsoObject* rerouteCollide;
    KahluaTable* table;
    std::string name;
    float tintr, tintg, tintb;
    std::string spriteName;
    float sx, sy;
    bool doNotSync;
    ObjectRenderEffects* windRenderEffects;
    ObjectRenderEffects* objectRenderEffects;
    IsoObject* externalWaterSource;
    bool usesExternalWaterSource;
    std::vector<IsoObject*> Children;
    std::string tile;
    bool specialTooltip;
    ColorInfo* highlightColor = nullptr;
        // --- Highlight logic ---
        bool isHighlighted() const {
            return (highlightFlags & OBF_Highlighted) != 0;
        }

        void setHighlighted(bool value, bool renderOnce = true) {
            if (value) {
                highlightFlags |= OBF_Highlighted;
            } else {
                highlightFlags &= ~OBF_Highlighted;
            }
            if (renderOnce) {
                highlightFlags |= OBF_HighlightRenderOnce;
            } else {
                highlightFlags &= ~OBF_HighlightRenderOnce;
            }
        }

        void setHighlighted(bool value) {
            setHighlighted(value, true);
        }

        ColorInfo* getHighlightColor() const {
            return highlightColor;
        }

        void setHighlightColor(const ColorInfo& color) {
            if (!highlightColor) highlightColor = new ColorInfo(color);
            else *highlightColor = color;
        }

        void setHighlightColor(float r, float g, float b, float a) {
            if (!highlightColor) highlightColor = new ColorInfo(r, g, b, a);
            else highlightColor->set(r, g, b, a);
        }

        bool isBlink() const {
            return (highlightFlags & OBF_Blink) != 0;
        }

        void setBlink(bool value) {
            if (value) highlightFlags |= OBF_Blink;
            else highlightFlags &= ~OBF_Blink;
        }
    std::vector<ItemContainer*> secondaryContainers;
    ColorInfo* customColor;
    float renderYOffset;
    uint8_t isOutlineHighlight;
    uint8_t isOutlineHlAttached;
    uint8_t isOutlineHlBlink;
    int outlineHighlightCol[4];
    float outlineThickness;
    bool bMovedThumpable;
    static std::unordered_map<uint8_t, IsoObjectFactory*> byteToObjectMap;
    static std::unordered_map<int, IsoObjectFactory*> hashCodeToObjectMap;
    static std::unordered_map<std::string, IsoObjectFactory*> nameToObjectMap;
    static IsoObjectFactory* factoryIsoObject;
    static IsoObjectFactory* factoryVehicle;

    // --- Constructors ---
    IsoObject();
    IsoObject(IsoCell* cell);
    IsoObject(IsoCell* cell, IsoGridSquare* square, IsoSprite* sprite);
    IsoObject(IsoCell* cell, IsoGridSquare* square, const std::string& spriteName);
    IsoObject(IsoGridSquare* square, const std::string& spriteName, const std::string& objectName);
    IsoObject(IsoGridSquare* square, const std::string& spriteName, const std::string& objectName, bool someFlag);
    IsoObject(IsoGridSquare* square, const std::string& spriteName, bool someFlag);
    IsoObject(IsoGridSquare* square, const std::string& spriteName);

    // --- Methods (stubs, to be implemented in .cpp) ---
    bool isFloor() const;
    static std::shared_ptr<IsoObject> getNew(IsoGridSquare* square, const std::string& spriteName, const std::string& objectName, bool someFlag);
    static std::shared_ptr<IsoObject> getLastRendered();
    static void setLastRendered(std::shared_ptr<IsoObject> obj);
    // ...other methods from Java/C++ sources

    // --- Inner enums/classes ---

    enum class VisionResult {
        NoEffect,
        Blocked,
        Unblocked
    };

    class IsoObjectFactory {
    public:
        uint8_t classID;
        std::string objectName;
        int hashCode;
        IsoObjectFactory(uint8_t id, const std::string& name);
        virtual std::shared_ptr<IsoObject> InstantiateObject(IsoCell* cell);
        uint8_t getClassID() const;
        std::string getObjectName() const;
        virtual ~IsoObjectFactory() = default;
    };

    class OutlineShader {
    public:
        // ShaderProgram* shaderProgram;
        int stepSize;
        int outlineColor;
        void initShader();
        void setOutlineColor(float r, float g, float b, float a);
        void setStepSize(float value, int w, int h);
        bool StartShader();
    };

    // IsoObjectPicker and ClickObject as inner classes for context
    class IsoObjectPicker {
    public:
        class ClickObject {
        public:
            int height;
            IsoGridSquare* square;
            IsoObject* tile;
            int width;
            int x, y, lx, ly;
            float scaleX, scaleY;
            bool flip;
            int score;
            int calculateScore();
            int getScore();
            // Additional logic and fields as needed
        };
        // Example: comparator for ClickObject
        class Comparator {
        public:
            int compare(const ClickObject& a, const ClickObject& b);
        };
        // Static fields (placeholders)
        static std::vector<ClickObject> choices;
        static std::vector<ClickObject> ThisFrame;
        static Vector2 tempo, tempo2;
        // Instance fields
        std::vector<ClickObject> ClickObjectStore;
        int count, counter, maxcount;
        bool dirty, wasDirty;
        float xOffSinceDirty, yOffSinceDirty;
        ClickObject* LastPickObject;
        float lx, ly;
        // ...other fields/methods as needed
    };

    // IsoObjectSyncRequests and SyncData as inner classes for context
    class IsoObjectSyncRequests {
    public:
        class SyncData {
        public:
            int x, y, z;
            uint8_t objIndex;
            long reqTime;
            int reqCount;
            SyncData(IsoObjectSyncRequests* parent) {}
        };
        // ...other fields/methods as needed
    };

    // Place all other inner classes/enums from Java/C++ here
    // --- IsoObjectFactory subclasses for each IsoObject type ---
    class FactoryIsoObject : public IsoObjectFactory {
    public:
        FactoryIsoObject(uint8_t id, const std::string& name) : IsoObjectFactory(id, name) {}
        std::shared_ptr<IsoObject> InstantiateObject(IsoCell* cell) override { auto obj = std::make_shared<IsoObject>(); obj->sx = 0.0f; return obj; }
    };
    class FactoryPlayer : public IsoObjectFactory {
    public:
        FactoryPlayer(uint8_t id, const std::string& name) : IsoObjectFactory(id, name) {}
        std::shared_ptr<IsoObject> InstantiateObject(IsoCell* cell) override { return std::make_shared<IsoPlayer>(cell); }
    };
    class FactorySurvivor : public IsoObjectFactory {
    public:
        FactorySurvivor(uint8_t id, const std::string& name) : IsoObjectFactory(id, name) {}
        std::shared_ptr<IsoObject> InstantiateObject(IsoCell* cell) override { return std::make_shared<IsoSurvivor>(cell); }
    };
    class FactoryZombie : public IsoObjectFactory {
    public:
        FactoryZombie(uint8_t id, const std::string& name) : IsoObjectFactory(id, name) {}
        std::shared_ptr<IsoObject> InstantiateObject(IsoCell* cell) override { return std::make_shared<IsoZombie>(cell); }
    };
    class FactoryPushable : public IsoObjectFactory {
    public:
        FactoryPushable(uint8_t id, const std::string& name) : IsoObjectFactory(id, name) {}
        std::shared_ptr<IsoObject> InstantiateObject(IsoCell* cell) override { return std::make_shared<IsoPushableObject>(cell); }
    };
    class FactoryWheelieBin : public IsoObjectFactory {
    public:
        FactoryWheelieBin(uint8_t id, const std::string& name) : IsoObjectFactory(id, name) {}
        std::shared_ptr<IsoObject> InstantiateObject(IsoCell* cell) override { return std::make_shared<IsoWheelieBin>(cell); }
    };
    class FactoryWorldInventoryItem : public IsoObjectFactory {
    public:
        FactoryWorldInventoryItem(uint8_t id, const std::string& name) : IsoObjectFactory(id, name) {}
        std::shared_ptr<IsoObject> InstantiateObject(IsoCell* cell) override { return std::make_shared<IsoWorldInventoryObject>(cell); }
    };
    class FactoryJukebox : public IsoObjectFactory {
    public:
        FactoryJukebox(uint8_t id, const std::string& name) : IsoObjectFactory(id, name) {}
        std::shared_ptr<IsoObject> InstantiateObject(IsoCell* cell) override { return std::make_shared<IsoJukebox>(cell); }
    };
    class FactoryCurtain : public IsoObjectFactory {
    public:
        FactoryCurtain(uint8_t id, const std::string& name) : IsoObjectFactory(id, name) {}
        std::shared_ptr<IsoObject> InstantiateObject(IsoCell* cell) override { return std::make_shared<IsoCurtain>(cell); }
    };
    class FactoryRadio : public IsoObjectFactory {
    public:
        FactoryRadio(uint8_t id, const std::string& name) : IsoObjectFactory(id, name) {}
        std::shared_ptr<IsoObject> InstantiateObject(IsoCell* cell) override { return std::make_shared<IsoRadio>(cell); }
    };
    class FactoryTelevision : public IsoObjectFactory {
    public:
        FactoryTelevision(uint8_t id, const std::string& name) : IsoObjectFactory(id, name) {}
        std::shared_ptr<IsoObject> InstantiateObject(IsoCell* cell) override { return std::make_shared<IsoTelevision>(cell); }
    };
    class FactoryDeadBody : public IsoObjectFactory {
    public:
        FactoryDeadBody(uint8_t id, const std::string& name) : IsoObjectFactory(id, name) {}
        std::shared_ptr<IsoObject> InstantiateObject(IsoCell* cell) override { return std::make_shared<IsoDeadBody>(cell); }
    };
    class FactoryBarbecue : public IsoObjectFactory {
    public:
        FactoryBarbecue(uint8_t id, const std::string& name) : IsoObjectFactory(id, name) {}
        std::shared_ptr<IsoObject> InstantiateObject(IsoCell* cell) override { return std::make_shared<IsoBarbecue>(cell); }
    };
    class FactoryClothingDryer : public IsoObjectFactory {
    public:
        FactoryClothingDryer(uint8_t id, const std::string& name) : IsoObjectFactory(id, name) {}
        std::shared_ptr<IsoObject> InstantiateObject(IsoCell* cell) override { return std::make_shared<IsoClothingDryer>(cell); }
    };
    class FactoryClothingWasher : public IsoObjectFactory {
    public:
        FactoryClothingWasher(uint8_t id, const std::string& name) : IsoObjectFactory(id, name) {}
        std::shared_ptr<IsoObject> InstantiateObject(IsoCell* cell) override { return std::make_shared<IsoClothingWasher>(cell); }
    };
    class FactoryFireplace : public IsoObjectFactory {
    public:
        FactoryFireplace(uint8_t id, const std::string& name) : IsoObjectFactory(id, name) {}
        std::shared_ptr<IsoObject> InstantiateObject(IsoCell* cell) override { return std::make_shared<IsoFireplace>(cell); }
    };
    class FactoryStove : public IsoObjectFactory {
    public:
        FactoryStove(uint8_t id, const std::string& name) : IsoObjectFactory(id, name) {}
        std::shared_ptr<IsoObject> InstantiateObject(IsoCell* cell) override { return std::make_shared<IsoStove>(cell); }
    };
    class FactoryDoor : public IsoObjectFactory {
    public:
        FactoryDoor(uint8_t id, const std::string& name) : IsoObjectFactory(id, name) {}
        std::shared_ptr<IsoObject> InstantiateObject(IsoCell* cell) override { return std::make_shared<IsoDoor>(cell); }
    };
    class FactoryThumpable : public IsoObjectFactory {
    public:
        FactoryThumpable(uint8_t id, const std::string& name) : IsoObjectFactory(id, name) {}
        std::shared_ptr<IsoObject> InstantiateObject(IsoCell* cell) override { return std::make_shared<IsoThumpable>(cell); }
    };
    class FactoryIsoTrap : public IsoObjectFactory {
    public:
        FactoryIsoTrap(uint8_t id, const std::string& name) : IsoObjectFactory(id, name) {}
        std::shared_ptr<IsoObject> InstantiateObject(IsoCell* cell) override { return std::make_shared<IsoTrap>(cell); }
    };
    class FactoryIsoBrokenGlass : public IsoObjectFactory {
    public:
        FactoryIsoBrokenGlass(uint8_t id, const std::string& name) : IsoObjectFactory(id, name) {}
        std::shared_ptr<IsoObject> InstantiateObject(IsoCell* cell) override { return std::make_shared<IsoBrokenGlass>(cell); }
    };
    class FactoryIsoCarBatteryCharger : public IsoObjectFactory {
    public:
        FactoryIsoCarBatteryCharger(uint8_t id, const std::string& name) : IsoObjectFactory(id, name) {}
        std::shared_ptr<IsoObject> InstantiateObject(IsoCell* cell) override { return std::make_shared<IsoCarBatteryCharger>(cell); }
    };
    class FactoryIsoGenerator : public IsoObjectFactory {
    public:
        FactoryIsoGenerator(uint8_t id, const std::string& name) : IsoObjectFactory(id, name) {}
        std::shared_ptr<IsoObject> InstantiateObject(IsoCell* cell) override { return std::make_shared<IsoGenerator>(cell); }
    };
    class FactoryIsoCompost : public IsoObjectFactory {
    public:
        FactoryIsoCompost(uint8_t id, const std::string& name) : IsoObjectFactory(id, name) {}
        std::shared_ptr<IsoObject> InstantiateObject(IsoCell* cell) override { return std::make_shared<IsoCompost>(cell); }
    };
    class FactoryMannequin : public IsoObjectFactory {
    public:
        FactoryMannequin(uint8_t id, const std::string& name) : IsoObjectFactory(id, name) {}
        std::shared_ptr<IsoObject> InstantiateObject(IsoCell* cell) override { return std::make_shared<IsoMannequin>(cell); }
    };
    class FactoryStoneFurnace : public IsoObjectFactory {
    public:
        FactoryStoneFurnace(uint8_t id, const std::string& name) : IsoObjectFactory(id, name) {}
        std::shared_ptr<IsoObject> InstantiateObject(IsoCell* cell) override { return std::make_shared<BSFurnace>(cell); }
    };
    class FactoryWindow : public IsoObjectFactory {
    public:
        FactoryWindow(uint8_t id, const std::string& name) : IsoObjectFactory(id, name) {}
        std::shared_ptr<IsoObject> InstantiateObject(IsoCell* cell) override { return std::make_shared<IsoWindow>(cell); }
    };
    class FactoryBarricade : public IsoObjectFactory {
    public:
        FactoryBarricade(uint8_t id, const std::string& name) : IsoObjectFactory(id, name) {}
        std::shared_ptr<IsoObject> InstantiateObject(IsoCell* cell) override { return std::make_shared<IsoBarricade>(cell); }
    };
    class FactoryTree : public IsoObjectFactory {
    public:
        FactoryTree(uint8_t id, const std::string& name) : IsoObjectFactory(id, name) {}
        std::shared_ptr<IsoObject> InstantiateObject(IsoCell* cell) override { return IsoTree::getNew(); }
    };
    class FactoryLightSwitch : public IsoObjectFactory {
    public:
        FactoryLightSwitch(uint8_t id, const std::string& name) : IsoObjectFactory(id, name) {}
        std::shared_ptr<IsoObject> InstantiateObject(IsoCell* cell) override { return std::make_shared<IsoLightSwitch>(cell); }
    };
    class FactoryZombieGiblets : public IsoObjectFactory {
    public:
        FactoryZombieGiblets(uint8_t id, const std::string& name) : IsoObjectFactory(id, name) {}
        std::shared_ptr<IsoObject> InstantiateObject(IsoCell* cell) override { return std::make_shared<IsoZombieGiblets>(cell); }
    };
    class FactoryMolotovCocktail : public IsoObjectFactory {
    public:
        FactoryMolotovCocktail(uint8_t id, const std::string& name) : IsoObjectFactory(id, name) {}
        std::shared_ptr<IsoObject> InstantiateObject(IsoCell* cell) override { return std::make_shared<IsoMolotovCocktail>(cell); }
    };
    class FactoryFire : public IsoObjectFactory {
    public:
        FactoryFire(uint8_t id, const std::string& name) : IsoObjectFactory(id, name) {}
        std::shared_ptr<IsoObject> InstantiateObject(IsoCell* cell) override { return std::make_shared<IsoFire>(cell); }
    };
    class FactoryVehicle : public IsoObjectFactory {
    public:
        FactoryVehicle(uint8_t id, const std::string& name) : IsoObjectFactory(id, name) {}
        std::shared_ptr<IsoObject> InstantiateObject(IsoCell* cell) override { return std::make_shared<BaseVehicle>(cell); }
    };
    class FactoryCombinationWasherDryer : public IsoObjectFactory {
    public:
        FactoryCombinationWasherDryer(uint8_t id, const std::string& name) : IsoObjectFactory(id, name) {}
        std::shared_ptr<IsoObject> InstantiateObject(IsoCell* cell) override { return std::make_shared<IsoCombinationWasherDryer>(cell); }
    };
    class FactoryStackedWasherDryer : public IsoObjectFactory {
    public:
        FactoryStackedWasherDryer(uint8_t id, const std::string& name) : IsoObjectFactory(id, name) {}
        std::shared_ptr<IsoObject> InstantiateObject(IsoCell* cell) override { return std::make_shared<IsoStackedWasherDryer>(cell); }
    };
};

// --- Other related types from Java/C++ sources ---

// IsoMovingObject: Base for moving iso objects (e.g., IsoPlayer, IsoZombie)
class IsoMovingObject : public IsoObject {
public:
    float x, y, z;
    float nx, ny, nz;
    float width, height;
    float angle;
    bool bOnFloor;
    // ...other fields and methods as needed...
    IsoMovingObject();
    virtual ~IsoMovingObject() = default;
};

// IsoPlayer: Main player character class
class IsoPlayer : public IsoMovingObject {
public:
    int playerIndex;
    std::string username;
    // ...other fields and methods as needed...
    IsoPlayer(IsoCell* cell);
    virtual ~IsoPlayer() = default;
};

// IsoZombie: Zombie character class
class IsoZombie : public IsoMovingObject {
public:
    bool isFakeDead;
    // ...other fields and methods as needed...
    IsoZombie(IsoCell* cell);
    virtual ~IsoZombie() = default;
};

// IsoSurvivor: NPC survivor class
class IsoSurvivor : public IsoMovingObject {
public:
    // ...fields and methods as needed...
    IsoSurvivor(IsoCell* cell);
    virtual ~IsoSurvivor() = default;
};

// IsoTrap: Trap object
class IsoTrap : public IsoObject {
public:
    // ...fields and methods as needed...
    IsoTrap(IsoCell* cell);
    virtual ~IsoTrap() = default;
};

// IsoDoor: Door object
class IsoDoor : public IsoObject {
public:
    bool isOpen;
    // ...fields and methods as needed...
    IsoDoor(IsoCell* cell);
    virtual ~IsoDoor() = default;
};

// IsoThumpable: Thumpable object (e.g., barricades, furniture)
class IsoThumpable : public IsoObject {
public:
    int thumpDamage;
    // ...fields and methods as needed...
    IsoThumpable(IsoCell* cell);
    virtual ~IsoThumpable() = default;
};

// IsoWheelieBin: Example object
class IsoWheelieBin : public IsoObject {
public:
    IsoWheelieBin(IsoCell* cell);
    virtual ~IsoWheelieBin() = default;
};

// IsoPushableObject: Example object
class IsoPushableObject : public IsoObject {
public:
    IsoPushableObject(IsoCell* cell);
    virtual ~IsoPushableObject() = default;
};

// IsoWorldInventoryObject: Example object
class IsoWorldInventoryObject : public IsoObject {
public:
    IsoWorldInventoryObject(IsoCell* cell);
    virtual ~IsoWorldInventoryObject() = default;
};

// IsoJukebox: Example object
class IsoJukebox : public IsoObject {
public:
    IsoJukebox(IsoCell* cell);
    virtual ~IsoJukebox() = default;
};

// IsoCurtain: Example object
class IsoCurtain : public IsoObject {
public:
    IsoCurtain(IsoCell* cell);
    virtual ~IsoCurtain() = default;
};

// IsoRadio: Example object
class IsoRadio : public IsoObject {
public:
    IsoRadio(IsoCell* cell);
    virtual ~IsoRadio() = default;
};

// IsoTelevision: Example object
class IsoTelevision : public IsoObject {
public:
    IsoTelevision(IsoCell* cell);
    virtual ~IsoTelevision() = default;
};

// IsoDeadBody: Example object
class IsoDeadBody : public IsoObject {
public:
    IsoDeadBody(IsoCell* cell);
    virtual ~IsoDeadBody() = default;
};

// IsoBarbecue: Example object
class IsoBarbecue : public IsoObject {
public:
    IsoBarbecue(IsoCell* cell);
    virtual ~IsoBarbecue() = default;
};

// IsoClothingDryer: Example object
class IsoClothingDryer : public IsoObject {
public:
    IsoClothingDryer(IsoCell* cell);
    virtual ~IsoClothingDryer() = default;
};

// IsoClothingWasher: Example object
class IsoClothingWasher : public IsoObject {
public:
    IsoClothingWasher(IsoCell* cell);
    virtual ~IsoClothingWasher() = default;
};

// IsoFireplace: Example object
class IsoFireplace : public IsoObject {
public:
    IsoFireplace(IsoCell* cell);
    virtual ~IsoFireplace() = default;
};

// IsoStove: Example object
class IsoStove : public IsoObject {
public:
    IsoStove(IsoCell* cell);
    virtual ~IsoStove() = default;
};

// IsoBrokenGlass: Example object
class IsoBrokenGlass : public IsoObject {
public:
    IsoBrokenGlass(IsoCell* cell);
    virtual ~IsoBrokenGlass() = default;
};

// IsoCarBatteryCharger: Example object
class IsoCarBatteryCharger : public IsoObject {
public:
    IsoCarBatteryCharger(IsoCell* cell);
    virtual ~IsoCarBatteryCharger() = default;
};

// IsoGenerator: Example object
class IsoGenerator : public IsoObject {
public:
    IsoGenerator(IsoCell* cell);
    virtual ~IsoGenerator() = default;
};

// IsoCompost: Example object
class IsoCompost : public IsoObject {
public:
    IsoCompost(IsoCell* cell);
    virtual ~IsoCompost() = default;
};

// IsoMannequin: Example object
class IsoMannequin : public IsoObject {
public:
    IsoMannequin(IsoCell* cell);
    virtual ~IsoMannequin() = default;
};

// BSFurnace: Example object
class BSFurnace : public IsoObject {
public:
    BSFurnace(IsoCell* cell);
    virtual ~BSFurnace() = default;
};

// IsoWindow: Example object
class IsoWindow : public IsoObject {
public:
    IsoWindow(IsoCell* cell);
    virtual ~IsoWindow() = default;
};

// IsoBarricade: Example object
class IsoBarricade : public IsoObject {
public:
    IsoBarricade(IsoCell* cell);
    virtual ~IsoBarricade() = default;
};

// IsoTree: Example object
class IsoTree : public IsoObject {
public:
    static std::shared_ptr<IsoTree> getNew();
    IsoTree();
    virtual ~IsoTree() = default;
};

// IsoLightSwitch: Example object
class IsoLightSwitch : public IsoObject {
public:
    IsoLightSwitch(IsoCell* cell);
    virtual ~IsoLightSwitch() = default;
};

// IsoZombieGiblets: Example object
class IsoZombieGiblets : public IsoObject {
public:
    IsoZombieGiblets(IsoCell* cell);
    virtual ~IsoZombieGiblets() = default;
};

// IsoMolotovCocktail: Example object
class IsoMolotovCocktail : public IsoObject {
public:
    IsoMolotovCocktail(IsoCell* cell);
    virtual ~IsoMolotovCocktail() = default;
};

// IsoFire: Example object
class IsoFire : public IsoObject {
public:
    IsoFire(IsoCell* cell);
    virtual ~IsoFire() = default;
};

// BaseVehicle: Example object
class BaseVehicle : public IsoObject {
public:
    BaseVehicle(IsoCell* cell);
    virtual ~BaseVehicle() = default;
};

// IsoCombinationWasherDryer: Example object
class IsoCombinationWasherDryer : public IsoObject {
public:
    IsoCombinationWasherDryer(IsoCell* cell);
    virtual ~IsoCombinationWasherDryer() = default;
};

// IsoStackedWasherDryer: Example object
class IsoStackedWasherDryer : public IsoObject {
public:
    IsoStackedWasherDryer(IsoCell* cell);
    virtual ~IsoStackedWasherDryer() = default;
};

} // namespace iso
} // namespace zombie
