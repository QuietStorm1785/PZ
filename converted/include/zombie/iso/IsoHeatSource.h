#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"

namespace zombie {
namespace iso {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class IsoHeatSource {
public:
 int x;
 int y;
 int z;
 int radius;
 int temperature;

 public IsoHeatSource(int _x, int _y, int _z, int _radius, int _temperature) {
 this->x = _x;
 this->y = _y;
 this->z = _z;
 this->radius = _radius;
 this->temperature = _temperature;
 }

 int getX() {
 return this->x;
 }

 int getY() {
 return this->y;
 }

 int getZ() {
 return this->z;
 }

 int getRadius() {
 return this->radius;
 }

 void setRadius(int _radius) {
 this->radius = _radius;
 }

 int getTemperature() {
 return this->temperature;
 }

 void setTemperature(int _temperature) {
 this->temperature = _temperature;
 }

 bool isInBounds(int minX, int minY, int maxX, int maxY) {
 return this->x >= minX && this->x < maxX && this->y >= minY && this->y < maxY;
 }

 bool isInBounds() {
 IsoChunkMap[] chunkMaps = IsoWorld.instance.CurrentCell.ChunkMap;

 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 if (!chunkMaps[int0].ignore) {
 int int1 = chunkMaps[int0].getWorldXMinTiles();
 int int2 = chunkMaps[int0].getWorldXMaxTiles();
 int int3 = chunkMaps[int0].getWorldYMinTiles();
 int int4 = chunkMaps[int0].getWorldYMaxTiles();
 if (this->isInBounds(int1, int3, int2, int4) {
 return true;
 }
 }
 }

 return false;
 }
}
} // namespace iso
} // namespace zombie
