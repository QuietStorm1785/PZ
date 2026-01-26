#include "zombie/iso/BrokenFences.h"
#include <random>

namespace zombie {
namespace iso {

BrokenFences& BrokenFences::getInstance() {
    static BrokenFences instance;
    return instance;
}

BrokenFences::BrokenFences() = default;

std::string BrokenFences::Tile::pickRandom(const std::vector<std::string>& v) const {
    if (v.empty()) return std::string();
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, v.size() - 1);
    return v[dis(gen)];
}


std::vector<std::string> BrokenFences::tableToTiles(lua_State* L, int tableIndex) const {
    std::vector<std::string> result;
    if (!lua_istable(L, tableIndex)) return result;
    lua_pushnil(L);
    while (lua_next(L, tableIndex) != 0) {
        if (lua_isstring(L, -1)) {
            result.emplace_back(lua_tostring(L, -1));
        }
        lua_pop(L, 1);
    }
    return result;
}


void BrokenFences::addBrokenTiles(lua_State* L, int tableIndex) {
    if (!lua_istable(L, tableIndex)) return;
    lua_pushnil(L);
    while (lua_next(L, tableIndex) != 0) {
        std::string key = lua_tostring(L, -2);
        if (key != "VERSION" && lua_istable(L, -1)) {
            auto tile = std::make_shared<Tile>();
            lua_getfield(L, -1, "self");
            tile->self = tableToTiles(L, lua_gettop(L));
            lua_pop(L, 1);
            lua_getfield(L, -1, "left");
            tile->left = tableToTiles(L, lua_gettop(L));
            lua_pop(L, 1);
            lua_getfield(L, -1, "right");
            tile->right = tableToTiles(L, lua_gettop(L));
            lua_pop(L, 1);
            s_unbrokenMap[key] = tile;
            for (const auto& l : tile->left) s_brokenLeftMap[l] = tile;
            for (const auto& r : tile->right) s_brokenRightMap[r] = tile;
        }
        lua_pop(L, 1);
    }
    s_allMap.insert(s_unbrokenMap.begin(), s_unbrokenMap.end());
    s_allMap.insert(s_brokenLeftMap.begin(), s_brokenLeftMap.end());
    s_allMap.insert(s_brokenRightMap.begin(), s_brokenRightMap.end());
}


void BrokenFences::addDebrisTiles(lua_State* L, int tableIndex) {
    if (!lua_istable(L, tableIndex)) return;
    lua_pushnil(L);
    while (lua_next(L, tableIndex) != 0) {
        std::string key = lua_tostring(L, -2);
        if (key != "VERSION" && lua_istable(L, -1)) {
            auto it = s_unbrokenMap.find(key);
            if (it == s_unbrokenMap.end()) continue;
            auto& tile = it->second;
            lua_getfield(L, -1, "north");
            tile->debrisN = tableToTiles(L, lua_gettop(L));
            lua_pop(L, 1);
            lua_getfield(L, -1, "south");
            tile->debrisS = tableToTiles(L, lua_gettop(L));
            lua_pop(L, 1);
            lua_getfield(L, -1, "west");
            tile->debrisW = tableToTiles(L, lua_gettop(L));
            lua_pop(L, 1);
            lua_getfield(L, -1, "east");
            tile->debrisE = tableToTiles(L, lua_gettop(L));
            lua_pop(L, 1);
        }
        lua_pop(L, 1);
    }
}


void BrokenFences::setDestroyed(IsoObject* obj) {
    if (!obj) return;
    obj->RemoveAttachedAnims();
    if (auto sq = obj->getSquare()) sq->removeBlood(false, true);
    updateSprite(obj, true, true);
}


void BrokenFences::setDamagedLeft(IsoObject* obj) {
    updateSprite(obj, true, false);
}


void BrokenFences::setDamagedRight(IsoObject* obj) {
    updateSprite(obj, false, true);
}


void BrokenFences::updateSprite(IsoObject* obj, bool left, bool right) {
    if (!isBreakableObject(obj)) return;
    auto it = s_allMap.find(obj->sprite->name);
    if (it == s_allMap.end()) return;
    auto& tile = it->second;
    std::string name;
    if (left && right) name = tile->pickRandom(tile->self);
    else if (left) name = tile->pickRandom(tile->left);
    else if (right) name = tile->pickRandom(tile->right);
    if (!name.empty()) {
        IsoSprite* sprite = IsoSpriteManager::instance->getSprite(name);
        sprite->name = name;
        obj->setSprite(sprite);
        obj->transmitUpdatedSprite();
        if (auto sq = obj->getSquare()) {
            sq->RecalcAllWithNeighbours(true);
            MapCollisionData::instance->squareChanged(sq);
            PolygonalMap2::instance->squareChanged(sq);
            IsoRegions::squareChanged(sq);
        }
    }
}


bool BrokenFences::isBreakableObject(IsoObject* obj) const {
    return obj && obj->sprite && !obj->sprite->name.empty() && s_allMap.count(obj->sprite->name) > 0;
}


void BrokenFences::destroyFence(IsoObject* obj, IsoDirections dir) {
    if (!isBreakableObject(obj)) return;
    IsoGridSquare* sq = obj->getSquare();
    // GameServer/SoundManager logic would go here if available
    bool collideN = obj->getProperties() && obj->getProperties()->Is(IsoFlagType::collideN);
    bool collideW = obj->getProperties() && obj->getProperties()->Is(IsoFlagType::collideW);
    // IsoThumpable logic: if obj is a thumpable, replace with new IsoObject
    // (Stub: actual type check and replacement would depend on your engine)
    addDebrisObject(obj, dir);
    setDestroyed(obj);
    if (collideN && collideW) {
        damageAdjacent(sq, IsoDirections::S, dir);
        damageAdjacent(sq, IsoDirections::E, dir);
    } else if (collideN) {
        damageAdjacent(sq, IsoDirections::W, dir);
        damageAdjacent(sq, IsoDirections::E, dir);
    } else if (collideW) {
        damageAdjacent(sq, IsoDirections::N, dir);
        damageAdjacent(sq, IsoDirections::S, dir);
    }
    if (sq) {
        sq->RecalcAllWithNeighbours(true);
        MapCollisionData::instance->squareChanged(sq);
        PolygonalMap2::instance->squareChanged(sq);
        IsoRegions::squareChanged(sq);
    }
}


void BrokenFences::Reset() {
    s_unbrokenMap.clear();
    s_brokenLeftMap.clear();
    s_brokenRightMap.clear();
    s_allMap.clear();
}


void BrokenFences::damageAdjacent(IsoGridSquare* sq, IsoDirections dir, IsoDirections causeDir) {
    if (!sq) return;
    IsoGridSquare* adj = sq->getAdjacentSquare(dir);
    if (!adj) return;
    bool isW = dir == IsoDirections::W || dir == IsoDirections::E;
    IsoObject* obj = getBreakableObject(adj, isW);
    if (obj) {
        bool isN = dir == IsoDirections::N || dir == IsoDirections::E;
        bool isS = dir == IsoDirections::S || dir == IsoDirections::W;
        if (!isNW(obj) || (dir != IsoDirections::S && dir != IsoDirections::E)) {
            if (isN && isBrokenRight(obj)) {
                destroyFence(obj, causeDir);
            } else if (isS && isBrokenLeft(obj)) {
                destroyFence(obj, causeDir);
            } else {
                updateSprite(obj, isN, isS);
            }
        }
    }
}


bool BrokenFences::isNW(IsoObject* obj) const {
    if (!obj || !obj->getProperties()) return false;
    auto* props = obj->getProperties();
    return props->Is(IsoFlagType::collideN) && props->Is(IsoFlagType::collideW);
}


bool BrokenFences::isUnbroken(IsoObject* obj) const {
    return obj && obj->sprite && !obj->sprite->name.empty() && s_unbrokenMap.count(obj->sprite->name) > 0;
}


bool BrokenFences::isBrokenLeft(IsoObject* obj) const {
    return obj && obj->sprite && !obj->sprite->name.empty() && s_brokenLeftMap.count(obj->sprite->name) > 0;
}


bool BrokenFences::isBrokenRight(IsoObject* obj) const {
    return obj && obj->sprite && !obj->sprite->name.empty() && s_brokenRightMap.count(obj->sprite->name) > 0;
}


IsoObject* BrokenFences::getBreakableObject(IsoGridSquare* sq, bool north) const {
    if (!sq) return nullptr;
    for (auto* obj : sq->getObjects()) {
        if (isBreakableObject(obj) && ((north && obj->getProperties() && obj->getProperties()->Is(IsoFlagType::collideN)) || (!north && obj->getProperties() && obj->getProperties()->Is(IsoFlagType::collideW)))) {
            return obj;
        }
    }
    return nullptr;
}


void BrokenFences::addItems(IsoObject* obj, IsoGridSquare* sq) {
    if (!obj || !sq) return;
    auto* props = obj->getProperties();
    if (!props) return;
    std::string mat1 = props->Val("Material");
    std::string mat2 = props->Val("Material2");
    std::string mat3 = props->Val("Material3");
    auto addItem = [&](const std::string& item, int chance) {
        if (chance == 1 || (rand() % chance == 0)) {
            // Create the item and add it to the world inventory at the square
            InventoryItem* newItem = InventoryItemFactory::CreateItem(item);
            if (newItem) {
                // Place at the center of the square, z=0.0f (adjust as needed)
                sq->AddWorldInventoryItem(newItem, sq->getX() + 0.5f, sq->getY() + 0.5f, sq->getZ() + 0.0f);
            }
        }
    };
    if (mat1 == "Wood" || mat2 == "Wood" || mat3 == "Wood") {
        addItem("Base.Plank", 1);
        addItem("Base.Plank", 5);
    }
    if (mat1 == "MetalBars" || mat2 == "MetalBars" || mat3 == "MetalBars") {
        addItem("Base.MetalBar", 2);
    }
    if (mat1 == "MetalWire" || mat2 == "MetalWire" || mat3 == "MetalWire") {
        addItem("Base.Wire", 3);
    }
    if (mat1 == "Nails" || mat2 == "Nails" || mat3 == "Nails") {
        addItem("Base.Nails", 2);
    }
    if (mat1 == "Screws" || mat2 == "Screws" || mat3 == "Screws") {
        addItem("Base.Screws", 2);
    }
}


void BrokenFences::addDebrisObject(IsoObject* obj, IsoDirections dir) {
    if (!isBreakableObject(obj)) return;
    auto it = s_allMap.find(obj->sprite->name);
    if (it == s_allMap.end()) return;
    auto& tile = it->second;
    IsoGridSquare* sq = obj->getSquare();
    std::string name;
    switch (dir) {
        case IsoDirections::N:
            name = tile->pickRandom(tile->debrisN);
            if (sq) sq = sq->getAdjacentSquare(dir);
            break;
        case IsoDirections::S:
            name = tile->pickRandom(tile->debrisS);
            break;
        case IsoDirections::W:
            name = tile->pickRandom(tile->debrisW);
            if (sq) sq = sq->getAdjacentSquare(dir);
            break;
        case IsoDirections::E:
            name = tile->pickRandom(tile->debrisE);
            break;
        default:
            return;
    }
    if (!name.empty() && sq && sq->TreatAsSolidFloor()) {
        // IsoObject* newObj = IsoObject::getNew(sq, name, nullptr, false); // Stub: actual creation
        // sq->transmitAddObjectToSquare(newObj, (sq == obj->getSquare()) ? obj->getObjectIndex() : -1);
        addItems(obj, sq);
    }
}

} // namespace iso
} // namespace zombie
