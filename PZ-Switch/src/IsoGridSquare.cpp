#include "IsoGridSquare.h"
#include "IsoCell.h"
#include "IsoPlayer.h"
#include "IsoZombie.h"
#include "IsoObject.h"
#include <cmath>
#include <algorithm>

IsoGridSquare::IsoGridSquare()
 : cell(nullptr)
 , x(0), y(0), z(0)
 , solid(false)
 , solidFloor(true)
 , seen(false)
 , terrain(TerrainType::GRASS)
 , n(nullptr), s(nullptr), e(nullptr), w(nullptr)
 , ne(nullptr), nw(nullptr), se(nullptr), sw(nullptr) {
}

IsoGridSquare::IsoGridSquare(IsoCell* cell, int x, int y, int z)
 : cell(cell)
 , x(x), y(y), z(z)
 , solid(false)
 , solidFloor(true)
 , seen(false)
 , terrain(TerrainType::GRASS)
 , n(nullptr), s(nullptr), e(nullptr), w(nullptr)
 , ne(nullptr), nw(nullptr), se(nullptr), sw(nullptr) {
}

IsoGridSquare::~IsoGridSquare() {
 // Clean up objects
 for (auto obj : objects) {
 delete obj;
 }
 objects.clear();
 characters.clear();
 zombies.clear();
}

void IsoGridSquare::setSolid(bool s) {
 bool wasBlocked = isBlocked();
 solid = s;
 bool nowBlocked = isBlocked();
 if (cell && wasBlocked != nowBlocked) {
 cell->notifyWalkabilityChanged(x, y, z, !nowBlocked);
 }
}

void IsoGridSquare::setSolidFloor(bool sf) {
 bool wasBlocked = isBlocked();
 solidFloor = sf;
 bool nowBlocked = isBlocked();
 if (cell && wasBlocked != nowBlocked) {
 cell->notifyWalkabilityChanged(x, y, z, !nowBlocked);
 }
}

void IsoGridSquare::addObject(IsoObject* obj) {
 if (obj) {
 bool wasBlocked = isBlocked();
 objects.push_back(obj);
 obj->setSquare(this);
 
 // Update solid status based on object
 if (obj->isSolid()) {
 solid = true;
 }

 bool nowBlocked = isBlocked();
 if (cell && wasBlocked != nowBlocked) {
 cell->notifyWalkabilityChanged(x, y, z, !nowBlocked);
 }
 }
}

void IsoGridSquare::removeObject(IsoObject* obj) {
 bool wasBlocked = isBlocked();
 auto it = std::find(objects.begin(), objects.end(), obj);
 if (it != objects.end()) {
 objects.erase(it);
 
 // Recalculate solid status
 solid = false;
 for (auto o : objects) {
 if (o->isSolid()) {
 solid = true;
 break;
 }
 }

 bool nowBlocked = isBlocked();
 if (cell && wasBlocked != nowBlocked) {
 cell->notifyWalkabilityChanged(x, y, z, !nowBlocked);
 }
 }
}

void IsoGridSquare::addCharacter(IsoPlayerPtr player) {
 if (player) {
 // Check if already exists
 for (auto& wp : characters) {
 if (auto sp = wp.lock()) {
 if (sp == player) return;
 }
 }
 characters.push_back(player);
 }
}

void IsoGridSquare::addZombie(IsoZombiePtr zombie) {
 if (zombie) {
 // Check if already exists
 for (auto& wp : zombies) {
 if (auto sp = wp.lock()) {
 if (sp == zombie) return;
 }
 }
 zombies.push_back(zombie);
 }
}

void IsoGridSquare::removeCharacter(IsoPlayerPtr player) {
 characters.erase(
 std::remove_if(characters.begin(), characters.end(),
 [&player](const IsoPlayerWeakPtr& wp) {
 auto sp = wp.lock();
 return !sp || sp == player;
 }),
 characters.end()
 );
}

void IsoGridSquare::removeZombie(IsoZombiePtr zombie) {
 zombies.erase(
 std::remove_if(zombies.begin(), zombies.end(),
 [&zombie](const IsoZombieWeakPtr& wp) {
 auto sp = wp.lock();
 return !sp || sp == zombie;
 }),
 zombies.end()
 );
}

std::vector<IsoPlayerPtr> IsoGridSquare::getCharacters() const {
 std::vector<IsoPlayerPtr> result;
 for (const auto& wp : characters) {
 if (auto sp = wp.lock()) {
 result.push_back(sp);
 }
 }
 return result;
}

std::vector<IsoZombiePtr> IsoGridSquare::getZombies() const {
 std::vector<IsoZombiePtr> result;
 for (const auto& wp : zombies) {
 if (auto sp = wp.lock()) {
 result.push_back(sp);
 }
 }
 return result;
}

bool IsoGridSquare::hasCharacters() const {
 for (const auto& wp : characters) {
 if (wp.lock()) return true;
 }
 return false;
}

bool IsoGridSquare::hasZombies() const {
 for (const auto& wp : zombies) {
 if (wp.lock()) return true;
 }
 return false;
}

bool IsoGridSquare::isFree(bool checkCharacters) const {
 if (solid || !solidFloor) {
 return false;
 }
 
 if (checkCharacters && (hasCharacters() || hasZombies())) {
 return false;
 }
 
 return true;
}

float IsoGridSquare::distanceTo(IsoGridSquare* other) const {
 if (!other) return 999999.0f;
 
 int dx = x - other->x;
 int dy = y - other->y;
 int dz = z - other->z;
 
 return std::sqrt((float)(dx*dx + dy*dy + dz*dz));
}

void IsoGridSquare::update() {
 // Update all objects on this square
 for (auto obj : objects) {
 if (obj) {
 obj->update();
 }
 }
}
