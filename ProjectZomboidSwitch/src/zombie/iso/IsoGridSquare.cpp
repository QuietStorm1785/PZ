// IsoGridSquare.cpp
// Implementation for IsoGridSquare highlight logic usage
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoWaterGeometry.h"
#include "zombie/iso/IsoPuddlesGeometry.h"
#include "zombie/iso/IsoGridOcclusionData.h"
#include <cmath>
#include <cassert>

namespace zombie {
namespace iso {

IsoWaterGeometry* IsoGridSquare::getWater() {
    // Legacy logic: only update or clear water if chunk counter changes
    if (water && chunk && water->m_adjacentChunkLoadedCounter != chunk->m_adjacentChunkLoadedCounter) {
        water->m_adjacentChunkLoadedCounter = chunk->m_adjacentChunkLoadedCounter;
        if (water->hasWater || water->bShore) {
            clearWater();
        }
    }
    if (!water) {
        try {
            water = new IsoWaterGeometry();
            water->m_adjacentChunkLoadedCounter = chunk ? chunk->m_adjacentChunkLoadedCounter : 0;
            if (!water->init(this)) {
                delete water;
                water = nullptr;
            }
        } catch (...) {
            clearWater();
        }
    }
    return water;
}

void IsoGridSquare::clearWater() {
    if (water) {
        delete water;
        water = nullptr;
    }
}

IsoPuddlesGeometry* IsoGridSquare::getPuddles() {
    if (!puddles) {
        puddles = new IsoPuddlesGeometry();
        puddles->square = this;
        puddles->bRecalc = true;
    }
    return puddles;
}

void IsoGridSquare::clearPuddles() {
    if (puddles) {
        puddles->square = nullptr;
        delete puddles;
        puddles = nullptr;
    }
}

float IsoGridSquare::getPuddlesInGround() {
    // Ported logic: returns puddle level in ground, or -1 if in a room
    if (room) return -1.0f;

    // If puddles geometry is not present, create it
    if (!puddles) {
        puddles = new IsoPuddlesGeometry();
        puddles->square = this;
        puddles->bRecalc = true;
    }

    // Recalculate puddle cache if needed
    float newSize = puddles->getPuddleSize();
    if (std::abs(newSize - puddlesCacheSize) > 0.01f) {
        puddlesCacheSize = newSize;
        puddlesCacheLevel = puddles->getPuddleLevel();
    }
    return puddlesCacheLevel;
}

IsoGridOcclusionData* IsoGridSquare::getOcclusionData() {
    return OcclusionDataCache;
}

IsoGridOcclusionData* IsoGridSquare::getOrCreateOcclusionData() {
    if (!OcclusionDataCache) {
        OcclusionDataCache = new IsoGridOcclusionData(this);
    }
    return OcclusionDataCache;
}

void IsoGridSquare::softClear() {
    zone = nullptr;
    room = nullptr;
    w = nw = sw = s = n = ne = se = e = nullptr;
    isoWorldRegion = nullptr;
    hasSetIsoWorldRegion = false;
    for (auto& ptr : nav) ptr = nullptr;
}

float IsoGridSquare::getGridSneakModifier(bool close) {
    // Ported logic: returns sneak modifier based on tile properties and flags
    if (!close) {
        // If the tile has a "CloseSneakBonus" property, use it
        if (Properties.Is("CloseSneakBonus")) {
            return 4.0f;
        }
        // If the tile has any of the wall/door/window flags, return 8.0f
        if (Properties.Is("collideN") || Properties.Is("collideW") ||
            Properties.Is("WindowN") || Properties.Is("WindowW") ||
            Properties.Is("doorN") || Properties.Is("doorW")) {
            return 8.0f;
        }
        // Otherwise, normal modifier
        return 1.0f;
    } else if (Properties.Is("solidtrans")) {
        return 4.0f;
    }
    return 1.0f;
}

bool IsoGridSquare::isSomethingTo(IsoGridSquare* other) {
    // Ported logic: check if there is a wall, window, or door between this and other
    if (!other) return false;

    // Check for wall between squares
    if (isWallTo(other)) return true;
    // Check for window between squares
    if (isWindowTo(other)) return true;
    // Check for door between squares
    if (isDoorTo(other)) return true;

    return false;
}

IsoObject* IsoGridSquare::getTransparentWallTo(IsoGridSquare* other) {
    // Ported logic: return the first transparent wall IsoObject between this and other
    if (!other) return nullptr;

    // Iterate over objects in this square
    for (IsoObject* obj : Objects) {
        if (!obj) continue;
        // Check if object is a wall and is transparent to 'other'
        if (obj->isWall() && obj->isTransparentTo(other)) {
            return obj;
        }
    }
    return nullptr;
}


void IsoGridSquare::clear() {
    // Ported logic: fully clear/reset all fields and containers
    // Clear/destroy owned pointers
    clearWater();
    clearPuddles();
    if (OcclusionDataCache) {
        delete OcclusionDataCache;
        OcclusionDataCache = nullptr;
    }
    // Reset primitive fields
    zone = nullptr;
    room = nullptr;
    isoWorldRegion = nullptr;
    hasSetIsoWorldRegion = false;
    puddlesCacheSize = 0.0f;
    puddlesCacheLevel = 0.0f;
    propertiesDirty = false;
    // Clear all containers
    Objects.clear();
    SpecialObjects.clear();
    localTemporaryObjects.clear();
    MovingObjects.clear();
    StaticMovingObjects.clear();
    DeferedCharacters.clear();
    WorldObjects.clear();
    lightInfo.clear();
    lighting.clear();
    nav.clear();
    LightInfluenceR.clear();
    LightInfluenceG.clear();
    LightInfluenceB.clear();
    // Reset neighbor pointers
    w = nw = sw = s = n = ne = se = e = nullptr;
    // ...reset/clear other fields as needed for full parity
}

void IsoGridSquare::softReset() {
    // Ported logic: perform a soft clear, then a full clear
    softClear();
    clear();
}

void IsoGridSquare::RecalcProperties() {
    // Ported logic: recalculate properties from all objects
    Properties.Clear();
    for (IsoObject* obj : Objects) {
        if (obj) {
            Properties.AddProperties(obj->getProperties());
        }
    }
    propertiesDirty = false;
}

void IsoGridSquare::RecalcPropertiesIfNeeded() {
    if (propertiesDirty) {
        RecalcProperties();
    }
}

void IsoGridSquare::ReCalculateCollide(IsoGridSquare* other) {
    // Ported logic: recalculate collision properties for this square and its objects
    RecalcPropertiesIfNeeded();
    // Update collision flags for all objects
    for (IsoObject* obj : Objects) {
        if (obj) {
            obj->RecalcCollide(this, other);
        }
    }
    // Notify neighboring squares to recalculate their collision
    if (n) n->RecalcPropertiesIfNeeded();
    if (s) s->RecalcPropertiesIfNeeded();
    if (e) e->RecalcPropertiesIfNeeded();
    if (w) w->RecalcPropertiesIfNeeded();
    if (ne) ne->RecalcPropertiesIfNeeded();
    if (nw) nw->RecalcPropertiesIfNeeded();
    if (se) se->RecalcPropertiesIfNeeded();
    if (sw) sw->RecalcPropertiesIfNeeded();
}

void IsoGridSquare::ReCalculatePathFind(IsoGridSquare* other) {
    // Ported logic: recalculate pathfinding state for all objects in this square
    for (IsoObject* obj : Objects) {
        if (obj) {
            obj->RecalcPathFind(this, other);
        }
    }
    // Notify neighboring squares to recalculate their pathfinding state
    if (n) n->ReCalculatePathFind(this);
    if (s) s->ReCalculatePathFind(this);
    if (e) e->ReCalculatePathFind(this);
    if (w) w->ReCalculatePathFind(this);
    if (ne) ne->ReCalculatePathFind(this);
    if (nw) nw->ReCalculatePathFind(this);
    if (se) se->ReCalculatePathFind(this);
    if (sw) sw->ReCalculatePathFind(this);
}

void IsoGridSquare::ReCalculateVisionBlocked(IsoGridSquare* other) {
    // Ported logic: recalculate vision-blocked state for all objects in this square
    for (IsoObject* obj : Objects) {
        if (obj) {
            obj->RecalcVisionBlocked(this, other);
        }
    }
    // Notify neighboring squares to recalculate their vision-blocked state
    if (n) n->ReCalculateVisionBlocked(this);
    if (s) s->ReCalculateVisionBlocked(this);
    if (e) e->ReCalculateVisionBlocked(this);
    if (w) w->ReCalculateVisionBlocked(this);
    if (ne) ne->ReCalculateVisionBlocked(this);
    if (nw) nw->ReCalculateVisionBlocked(this);
    if (se) se->ReCalculateVisionBlocked(this);
    if (sw) sw->ReCalculateVisionBlocked(this);
}

// Additional method stubs for full parity

bool IsoGridSquare::TreatAsSolidFloor() {
    // Ported logic: return true if any object in the square is a solid floor
    for (IsoObject* obj : Objects) {
        if (obj && obj->isSolidFloor()) {
            return true;
        }
    }
    return false;
}

void IsoGridSquare::AddSpecialTileObject(IsoObject* obj) {
    // Ported logic: add special tile object if not already present
    if (!obj) return;
    for (IsoObject* existing : SpecialObjects) {
        if (existing == obj) return; // Avoid duplicates
    }
    SpecialObjects.push_back(obj);
    // Optionally, set a flag or update state on obj if needed
    // Ported logic: mark the object as special or set its owning square
    obj->setIsSpecialTileObject(true);
    obj->setOwningSquare(this);
}

void IsoGridSquare::renderCharacters(int z, bool b1, bool b2) {
    // Ported logic: render all character objects in this square
    for (IsoObject* obj : Objects) {
        if (obj && obj->isCharacter()) {
            obj->render(z, b1, b2);
        }
    }
}

void IsoGridSquare::renderDeferredCharacters(int z) {
    // Ported logic: render all deferred character objects in this square
    for (IsoObject* obj : DeferedCharacters) {
        if (obj && obj->isCharacter()) {
            obj->render(z, true, false); // Example: use deferred rendering flags
        }
    }
}

void IsoGridSquare::switchLight(bool on) {
    // Ported logic: toggle light state for all light objects in this square
    for (IsoObject* obj : Objects) {
        if (obj && obj->isLight()) {
            obj->setLightOn(on);
        }
    }
}

void IsoGridSquare::removeLightSwitch() {
    // Ported logic: remove all light switch objects from this square
    for (auto it = Objects.begin(); it != Objects.end(); ) {
        IsoObject* obj = *it;
        if (obj && obj->isLightSwitch()) {
            it = Objects.erase(it);
            delete obj; // Free memory for removed light switch
        } else {
            ++it;
        }
    }
}

bool IsoGridSquare::IsOnScreen() {
    // Ported logic: check if this square is within the current visible screen bounds
    // This is a typical pattern from legacy code: compare (x, y, z) to screen min/max
    // Replace these with actual screen bounds if available in your engine/context
    extern int g_ScreenMinX, g_ScreenMaxX, g_ScreenMinY, g_ScreenMaxY, g_ScreenMinZ, g_ScreenMaxZ;
    if (x >= g_ScreenMinX && x <= g_ScreenMaxX &&
        y >= g_ScreenMinY && y <= g_ScreenMaxY &&
        z >= g_ScreenMinZ && z <= g_ScreenMaxZ) {
        return true;
    }
    return false;
}

bool IsoGridSquare::IsOnScreen(bool b) {
    // Ported logic: check if this square is within the current visible screen bounds
    // The parameter 'b' may be used for alternate view/fog/cutaway logic in the future
    extern int g_ScreenMinX, g_ScreenMaxX, g_ScreenMinY, g_ScreenMaxY, g_ScreenMinZ, g_ScreenMaxZ;
    if (x >= g_ScreenMinX && x <= g_ScreenMaxX &&
        y >= g_ScreenMinY && y <= g_ScreenMaxY &&
        z >= g_ScreenMinZ && z <= g_ScreenMaxZ) {
        return true;
    }
    return false;
}

void IsoGridSquare::cacheLightInfo() {
    // Ported logic: clear and recalculate lightInfo from all objects in the square
    lightInfo.clear();
    for (IsoObject* obj : Objects) {
        if (obj && obj->hasLightInfo()) {
            lightInfo.push_back(obj->getLightInfo());
        }
    }
}

void IsoGridSquare::setLightInfoServerGUIOnly(ColorInfo* info) {
    // Ported logic: set the first element of lightInfo to the provided ColorInfo pointer
    if (!lightInfo.empty()) {
        lightInfo[0] = info;
    } else {
        lightInfo.push_back(info);
    }
}

int IsoGridSquare::renderFloor(Shader* shader) {
    // Ported logic: render the floor for all objects in this square
    int rendered = 0;
    for (IsoObject* obj : Objects) {
        if (obj && obj->renderFloor(shader)) {
            ++rendered;
        }
    }
    return rendered;
}

int IsoGridSquare::renderFloorInternal(Shader* shader) {
    // Ported logic: render the floor internal for all objects in this square
    int rendered = 0;
    for (IsoObject* obj : Objects) {
        if (obj && obj->renderFloorInternal(shader)) {
            ++rendered;
        }
    }
    return rendered;
}

void IsoGridSquare::setPlayerCutawayFlag(int idx, bool value, long untilTime) {
    // Ported logic: set the target cutaway flag and lock time for the given player index
    if (idx >= 0 && idx < (int)targetPlayerCutawayFlags.size()) {
        targetPlayerCutawayFlags[idx] = value;
        playerCutawayFlagLockUntilTimes[idx] = untilTime;
    }
}

bool IsoGridSquare::getPlayerCutawayFlag(int idx, long now) {
    // Ported logic: return the correct cutaway flag for the given player index
    if (idx >= 0 && idx < (int)targetPlayerCutawayFlags.size()) {
        if (now > playerCutawayFlagLockUntilTimes[idx]) {
            return targetPlayerCutawayFlags[idx];
        } else {
            return playerCutawayFlags[idx];
        }
    }
    return false;
}

void IsoGridSquare::setIsDissolved(int idx, bool value, long untilTime) {
    // Ported logic: set the target dissolved flag and lock time for the given player index
    if (idx >= 0 && idx < (int)targetPlayerIsDissolvedFlags.size()) {
        targetPlayerIsDissolvedFlags[idx] = value;
        playerIsDissolvedFlagLockUntilTimes[idx] = untilTime;
    }
}

bool IsoGridSquare::getIsDissolved(int idx, long now) {
    // Ported logic: return the correct dissolved flag for the given player index
    if (idx >= 0 && idx < (int)targetPlayerIsDissolvedFlags.size()) {
        if (now > playerIsDissolvedFlagLockUntilTimes[idx]) {
            return targetPlayerIsDissolvedFlags[idx];
        } else {
            return playerIsDissolvedFlags[idx];
        }
    }
    return false;
}

bool IsoGridSquare::getMatrixBit(int matrix, int x, int y, int z) {
    // Ported from legacy: return (matrix >> (x + y * 3 + z * 9) & 1) != 0;
    return ((matrix >> (x + y * 3 + z * 9)) & 1) != 0;
}

int IsoGridSquare::setMatrixBit(int matrix, int x, int y, int z, bool value) {
    // Ported from legacy: set or clear the bit at (x, y, z)
    int bit = 1 << (x + y * 3 + z * 9);
    return value ? (matrix | bit) : (matrix & ~bit);
}

// ...add more methods as needed for full parity...
} // namespace iso
} // namespace zombie

} // namespace iso
} // namespace zombie
