#include "ContainerOverlays.h"
#include <iostream>

#include <algorithm>

namespace zombie {
namespace iso {

std::shared_ptr<ContainerOverlays> ContainerOverlays::instance = nullptr;
std::vector<std::shared_ptr<ContainerOverlayEntry>> ContainerOverlays::tempEntries;

ContainerOverlays::ContainerOverlays() {
    // Initialize overlayMap and overlayNameToUnderlyingName if needed
}

ContainerOverlays::~ContainerOverlays() {
    // Cleanup if needed
}

// ---- ContainerOverlayEntry Implementation ----
ContainerOverlayEntry::ContainerOverlayEntry(const std::string& name, std::shared_ptr<Texture> texture)
    : name(name), texture(texture) {}

ContainerOverlayEntry::~ContainerOverlayEntry() = default;

void ContainerOverlayEntry::addTag(const std::string& tag) {
    tags.push_back(tag);
}

bool ContainerOverlayEntry::hasTag(const std::string& tag) const {
    return std::find(tags.begin(), tags.end(), tag) != tags.end();
}

// ---- ContainerOverlay Implementation ----
ContainerOverlay::ContainerOverlay(const std::string& name)
    : name(name) {}

ContainerOverlay::~ContainerOverlay() = default;

void ContainerOverlay::addEntry(const std::shared_ptr<ContainerOverlayEntry>& entry) {
    entries.push_back(entry);
}

std::shared_ptr<ContainerOverlayEntry> ContainerOverlay::getEntry(const std::string& entryName) const {
    for (const auto& entry : entries) {
        if (entry->name == entryName) {
            return entry;
        }
    }
    return nullptr;
}

void ContainerOverlays::Reset() {
    overlayMap.clear();
    overlayNameToUnderlyingName.clear();
    tempEntries.clear();
}

void ContainerOverlays::addOverlays(lua_State* L, int tableIndex) {
    if (!L || !lua_istable(L, tableIndex)) return;
    lua_getfield(L, tableIndex, "VERSION");
    int version = -1;
    if (lua_isnumber(L, -1)) {
        version = (int)lua_tointeger(L, -1);
    }
    lua_pop(L, 1);
    if (version == -1) {
        parseContainerOverlayMapV0(L, tableIndex);
    } else if (version == 1) {
        parseContainerOverlayMapV1(L, tableIndex);
    } else {
        throw std::runtime_error("unknown overlayMap.VERSION " + std::to_string(version));
    }
}

std::vector<std::string> ContainerOverlays::getUnderlyingSpriteNames(const std::string& name) {
    auto it = overlayNameToUnderlyingName.find(name);
    if (it != overlayNameToUnderlyingName.end()) {
        return it->second;
    }
    return {};
}

bool ContainerOverlays::hasOverlays(const std::shared_ptr<IsoObject>& obj) const {
    // Check if the object has overlays by looking up overlayMap
    if (!obj) return false;
    auto name = obj->getSpriteName();
    return overlayMap.find(name) != overlayMap.end();
}

void ContainerOverlays::updateContainerOverlaySprite(const std::shared_ptr<IsoObject>& obj) {
    if (!obj) return;
    // Skip IsoStove objects (dynamic_cast or type check as needed)
    if (obj->isA("IsoStove")) return;
    auto sq = obj->getSquare();
    if (!sq) return;
    std::string overlaySprite;
    auto container = obj->getContainer();
    auto name = obj->getSpriteName();
    if (!name.empty() && container && !container->isEmpty()) {
        auto it = overlayMap.find(name);
        if (it != overlayMap.end()) {
            auto& overlay = it->second;
            std::string roomName = "other";
            if (auto room = sq->getRoom()) {
                roomName = room->getName();
            }
            // Pick a random overlay entry for this room/coords
            auto entry = overlay->pickRandom(roomName, sq->getX(), sq->getY(), sq->getZ());
            if (!entry) {
                entry = overlay->pickRandom("other", sq->getX(), sq->getY(), sq->getZ());
            }
            if (entry) {
                overlaySprite = entry->manyItems;
                if (!entry->fewItems.empty() && container->getItems().size() < 7) {
                    overlaySprite = entry->fewItems;
                }
            }
        }
    }
    // Only set overlay if valid and texture exists (and not on server)
    if (!overlaySprite.empty() && !GameServer::bServer && !Texture::getSharedTexture(overlaySprite)) {
        overlaySprite.clear();
    }
    obj->setOverlaySprite(overlaySprite);
}

void ContainerOverlays::parseContainerOverlayMapV0(lua_State* L, int tableIndex) {
    if (!L || !lua_istable(L, tableIndex)) return;
    // Iterate over top-level table: overlay name -> overlay table
    lua_pushnil(L);
    while (lua_next(L, tableIndex) != 0) {
        // key at -2, value at -1
        if (lua_type(L, -2) == LUA_TSTRING && lua_istable(L, -1)) {
            std::string overlayName = lua_tostring(L, -2);
            auto overlay = std::make_shared<ContainerOverlay>(overlayName);
            overlayMap[overlayName] = overlay;
            // Iterate overlay table: room name -> entry table
            lua_pushnil(L);
            while (lua_next(L, lua_gettop(L)) != 0) {
                if (lua_type(L, -2) == LUA_TSTRING && lua_istable(L, -1)) {
                    std::string roomName = lua_tostring(L, -2);
                    std::string manyItems, fewItems;
                    // 1: manyItems, 2: fewItems
                    lua_rawgeti(L, -1, 1);
                    if (lua_isstring(L, -1)) {
                        manyItems = lua_tostring(L, -1);
                    }
                    lua_pop(L, 1);
                    lua_rawgeti(L, -1, 2);
                    if (lua_isstring(L, -1)) {
                        fewItems = lua_tostring(L, -1);
                    }
                    lua_pop(L, 1);
                    auto entry = std::make_shared<ContainerOverlayEntry>(roomName, nullptr);
                    entry->manyItems = manyItems;
                    entry->fewItems = fewItems;
                    entry->room = roomName;
                    overlay->addEntry(entry);
                }
                lua_pop(L, 1);
            }
        }
        lua_pop(L, 1);
    }
}

void ContainerOverlays::parseContainerOverlayMapV1(lua_State* L, int tableIndex) {
    if (!L || !lua_istable(L, tableIndex)) return;
    lua_pushnil(L);
    while (lua_next(L, tableIndex) != 0) {
        // key at -2, value at -1
        if (lua_type(L, -2) == LUA_TSTRING && lua_istable(L, -1)) {
            std::string overlayName = lua_tostring(L, -2);
            if (overlayName == "VERSION") {
                lua_pop(L, 1);
                continue;
            }
            auto overlay = std::make_shared<ContainerOverlay>(overlayName);
            // Iterate overlay table: each value is an entry table
            lua_pushnil(L);
            while (lua_next(L, lua_gettop(L)) != 0) {
                if (lua_istable(L, -1)) {
                    // entry table: get 'name' and 'tiles'
                    std::string roomName;
                    std::string manyItems, fewItems;
                    lua_getfield(L, -1, "name");
                    if (lua_isstring(L, -1)) {
                        roomName = lua_tostring(L, -1);
                    }
                    lua_pop(L, 1);
                    lua_getfield(L, -1, "tiles");
                    if (lua_istable(L, -1)) {
                        lua_rawgeti(L, -1, 1);
                        if (lua_isstring(L, -1)) {
                            manyItems = lua_tostring(L, -1);
                        }
                        lua_pop(L, 1);
                        lua_rawgeti(L, -1, 2);
                        if (lua_isstring(L, -1)) {
                            fewItems = lua_tostring(L, -1);
                        }
                        lua_pop(L, 1);
                    }
                    lua_pop(L, 1); // pop 'tiles' table
                    // Clean up values
                    if (manyItems.empty() || manyItems == "none") manyItems.clear();
                    if (fewItems.empty() || fewItems == "none") fewItems.clear();
                    auto entry = std::make_shared<ContainerOverlayEntry>(roomName, nullptr);
                    entry->manyItems = manyItems;
                    entry->fewItems = fewItems;
                    entry->room = roomName;
                    overlay->addEntry(entry);
                }
                lua_pop(L, 1);
            }
            overlayMap[overlayName] = overlay;
        }
        lua_pop(L, 1);
    }
}

} // namespace iso
} // namespace zombie
