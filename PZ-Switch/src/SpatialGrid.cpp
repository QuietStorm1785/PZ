#include "SpatialGrid.h"
#include "IsoObject.h"
#include "IsoPlayer.h"
#include <cmath>
#include <algorithm>

// ===== SpatialGrid =====

SpatialGrid::SpatialGrid(int cellSize)
 : cellSize(cellSize) {
}

SpatialGrid::~SpatialGrid() {
 clear();
}

int SpatialGrid::getCellKey(float x, float y) const {
 int cx, cy;
 getCellCoords(x, y, cx, cy);
 return cx + cy * 10000;
}

void SpatialGrid::getCellCoords(float x, float y, int& cellX, int& cellY) const {
 cellX = static_cast<int>(std::floor(x / cellSize));
 cellY = static_cast<int>(std::floor(y / cellSize));
}

void SpatialGrid::insertObject(float x, float y, IsoObject* obj) {
 if (!obj) return;
 int key = getCellKey(x, y);
 grid[key].push_back(obj);
}

void SpatialGrid::removeObject(float x, float y, IsoObject* obj) {
 if (!obj) return;
 int key = getCellKey(x, y);
 auto it = grid.find(key);
 if (it != grid.end()) {
 auto& vec = it->second;
 vec.erase(std::remove(vec.begin(), vec.end(), obj), vec.end());
 if (vec.empty()) {
 grid.erase(it);
 }
 }
}

void SpatialGrid::updateObject(float oldX, float oldY, float newX, float newY, IsoObject* obj) {
 int oldKey = getCellKey(oldX, oldY);
 int newKey = getCellKey(newX, newY);
 
 if (oldKey == newKey) return; // Same cell, no update needed
 
 removeObject(oldX, oldY, obj);
 insertObject(newX, newY, obj);
}

std::vector<IsoObject*> SpatialGrid::queryObjects(float x, float y, float radius) {
 std::vector<IsoObject*> result;
 
 int centerX, centerY;
 getCellCoords(x, y, centerX, centerY);
 
 int cellRadius = static_cast<int>(std::ceil(radius / cellSize)) + 1;
 
 // Check surrounding cells
 for (int dy = -cellRadius; dy <= cellRadius; ++dy) {
 for (int dx = -cellRadius; dx <= cellRadius; ++dx) {
 int key = (centerX + dx) + (centerY + dy) * 10000;
 auto it = grid.find(key);
 if (it != grid.end()) {
 for (auto* obj : it->second) {
 if (!obj) continue;
 float ox = obj->getX();
 float oy = obj->getY();
 float distSq = (ox - x) * (ox - x) + (oy - y) * (oy - y);
 if (distSq <= radius * radius) {
 result.push_back(obj);
 }
 }
 }
 }
 }
 
 return result;
}

std::vector<IsoObject*> SpatialGrid::queryObjectsBox(float x, float y, float width, float height) {
 std::vector<IsoObject*> result;
 
 int minX, minY, maxX, maxY;
 getCellCoords(x, y, minX, minY);
 getCellCoords(x + width, y + height, maxX, maxY);
 
 for (int cy = minY; cy <= maxY; ++cy) {
 for (int cx = minX; cx <= maxX; ++cx) {
 int key = cx + cy * 10000;
 auto it = grid.find(key);
 if (it != grid.end()) {
 for (auto* obj : it->second) {
 result.push_back(obj);
 }
 }
 }
 }
 
 return result;
}

void SpatialGrid::clear() {
 grid.clear();
}

// ===== EntitySpatialGrid =====

EntitySpatialGrid::EntitySpatialGrid(int cellSize)
 : cellSize(cellSize) {
}

EntitySpatialGrid::~EntitySpatialGrid() {
 clear();
}

int EntitySpatialGrid::getCellKey(float x, float y) const {
 int cx, cy;
 getCellCoords(x, y, cx, cy);
 return cx + cy * 10000;
}

void EntitySpatialGrid::getCellCoords(float x, float y, int& cellX, int& cellY) const {
 cellX = static_cast<int>(std::floor(x / cellSize));
 cellY = static_cast<int>(std::floor(y / cellSize));
}

void EntitySpatialGrid::updateEntity(float oldX, float oldY, float newX, float newY, IsoPlayer* entity) {
 if (!entity) return;
 
 int oldKey = getCellKey(oldX, oldY);
 int newKey = getCellKey(newX, newY);
 
 if (oldKey == newKey) return;
 
 // Remove from old cell
 auto oldIt = grid.find(oldKey);
 if (oldIt != grid.end()) {
 auto& vec = oldIt->second;
 vec.erase(std::remove(vec.begin(), vec.end(), entity), vec.end());
 if (vec.empty()) {
 grid.erase(oldIt);
 }
 }
 
 // Add to new cell
 grid[newKey].push_back(entity);
}

void EntitySpatialGrid::insertEntity(float x, float y, IsoPlayer* entity) {
 if (!entity) return;
 int key = getCellKey(x, y);
 grid[key].push_back(entity);
}

void EntitySpatialGrid::removeEntity(float x, float y, IsoPlayer* entity) {
 if (!entity) return;
 
 int key = getCellKey(x, y);
 auto it = grid.find(key);
 if (it != grid.end()) {
 auto& vec = it->second;
 vec.erase(std::remove(vec.begin(), vec.end(), entity), vec.end());
 if (vec.empty()) {
 grid.erase(it);
 }
 }
}

std::vector<IsoPlayer*> EntitySpatialGrid::queryEntities(float x, float y, float radius) {
 std::vector<IsoPlayer*> result;
 
 int centerX, centerY;
 getCellCoords(x, y, centerX, centerY);
 
 int cellRadius = static_cast<int>(std::ceil(radius / cellSize)) + 1;
 
 for (int dy = -cellRadius; dy <= cellRadius; ++dy) {
 for (int dx = -cellRadius; dx <= cellRadius; ++dx) {
 int key = (centerX + dx) + (centerY + dy) * 10000;
 auto it = grid.find(key);
 if (it != grid.end()) {
 for (auto* entity : it->second) {
 if (!entity) continue;
 float ex = entity->getX();
 float ey = entity->getY();
 float distSq = (ex - x) * (ex - x) + (ey - y) * (ey - y);
 if (distSq <= radius * radius) {
 result.push_back(entity);
 }
 }
 }
 }
 }
 
 return result;
}

void EntitySpatialGrid::clear() {
 grid.clear();
}
