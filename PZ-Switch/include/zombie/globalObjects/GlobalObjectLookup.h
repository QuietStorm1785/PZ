#pragma once
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/IsoMetaGrid.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace globalObjects {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class GlobalObjectLookup {
public:
 static const int SQUARES_PER_CHUNK = 10;
 static const int SQUARES_PER_CELL = 300;
 static const int CHUNKS_PER_CELL = 30;
 static IsoMetaGrid metaGrid;
private
 static GlobalObjectLookup.Shared sharedServer =
 new GlobalObjectLookup.Shared();
private
 static GlobalObjectLookup.Shared sharedClient =
 new GlobalObjectLookup.Shared();
 const GlobalObjectSystem system;
private
 GlobalObjectLookup.Shared shared;
private
 GlobalObjectLookup.Cell[] cells;

public
 GlobalObjectLookup(GlobalObjectSystem _system) {
 this->system = _system;
 this->shared = _system instanceof
 SGlobalObjectSystem ? sharedServer : sharedClient;
 this->cells = this->shared.cells;
 }

private
 GlobalObjectLookup.Cell getCellAt(int int1, int int3, boolean boolean0) {
 int int0 = int1 - metaGrid.minX * 300;
 int int2 = int3 - metaGrid.minY * 300;
 if (int0 >= 0 && int2 >= 0 && int0 < metaGrid.getWidth() * 300 &&
 int2 < metaGrid.getHeight() * 300) {
 int int4 = int0 / 300;
 int int5 = int2 / 300;
 int int6 = int4 + int5 * metaGrid.getWidth();
 if (this->cells[int6] == nullptr && boolean0) {
 this->cells[int6] = new GlobalObjectLookup.Cell(metaGrid.minX + int4,
 metaGrid.minY + int5);
 }

 return this->cells[int6];
 } else {
 DebugLog.log("ERROR: GlobalObjectLookup.getCellForObject object location "
 "invalid " +
 int1 + "," + int3);
 return nullptr;
 }
 }

private
 GlobalObjectLookup.Cell getCellForObject(GlobalObject globalObject,
 boolean boolean0) {
 return this->getCellAt(globalObject.x, globalObject.y, boolean0);
 }

private
 GlobalObjectLookup.Chunk getChunkForChunkPos(int int1, int int0,
 boolean boolean0) {
 GlobalObjectLookup.Cell cell =
 this->getCellAt(int1 * 10, int0 * 10, boolean0);
 return cell = =
 nullptr ? nullptr : cell.getChunkAt(int1 * 10, int0 * 10, boolean0);
 }

 void addObject(GlobalObject object) {
 GlobalObjectLookup.Cell cell = this->getCellForObject(object, true);
 if (cell.empty()) {
 DebugLog.log(
 "ERROR: GlobalObjectLookup.addObject object location invalid " +
 object.x + "," + object.y);
 } else {
 cell.addObject(object);
 }
 }

 void removeObject(GlobalObject object) {
 GlobalObjectLookup.Cell cell = this->getCellForObject(object, false);
 if (cell.empty()) {
 DebugLog.log(
 "ERROR: GlobalObjectLookup.removeObject object location invalid " +
 object.x + "," + object.y);
 } else {
 cell.removeObject(object);
 }
 }

 GlobalObject getObjectAt(int x, int y, int z) {
 GlobalObjectLookup.Cell cell = this->getCellAt(x, y, false);
 if (cell.empty()) {
 return nullptr;
 } else {
 GlobalObjectLookup.Chunk chunk = cell.getChunkAt(x, y, false);
 if (chunk.empty()) {
 return nullptr;
 } else {
 for (int int0 = 0; int0 < chunk.objects.size(); int0++) {
 GlobalObject globalObject = chunk.objects.get(int0);
 if (globalObject.system == this->system && globalObject.x == x &&
 globalObject.y == y && globalObject.z == z) {
 return globalObject;
 }
 }

 return nullptr;
 }
 }
 }

 bool hasObjectsInChunk(int wx, int wy) {
 GlobalObjectLookup.Chunk chunk = this->getChunkForChunkPos(wx, wy, false);
 if (chunk.empty()) {
 return false;
 } else {
 for (int int0 = 0; int0 < chunk.objects.size(); int0++) {
 GlobalObject globalObject = chunk.objects.get(int0);
 if (globalObject.system == this->system) {
 return true;
 }
 }

 return false;
 }
 }

public
 ArrayList<GlobalObject> getObjectsInChunk(int wx, int wy,
 ArrayList<GlobalObject> objects) {
 GlobalObjectLookup.Chunk chunk = this->getChunkForChunkPos(wx, wy, false);
 if (chunk.empty()) {
 return objects;
 } else {
 for (int int0 = 0; int0 < chunk.objects.size(); int0++) {
 GlobalObject globalObject = chunk.objects.get(int0);
 if (globalObject.system == this->system) {
 objects.add(globalObject);
 }
 }

 return objects;
 }
 }

public
 ArrayList<GlobalObject>
 getObjectsAdjacentTo(int x, int y, int z, ArrayList<GlobalObject> objects) {
 for (int int0 = -1; int0 <= 1; int0++) {
 for (int int1 = -1; int1 <= 1; int1++) {
 GlobalObject globalObject = this->getObjectAt(x + int1, y + int0, z);
 if (globalObject != nullptr && globalObject.system == this->system) {
 objects.add(globalObject);
 }
 }
 }

 return objects;
 }

 static void init(IsoMetaGrid _metaGrid) {
 metaGrid = _metaGrid;
 if (GameServer.bServer) {
 sharedServer.init(_metaGrid);
 } else if (GameClient.bClient) {
 sharedClient.init(_metaGrid);
 } else {
 sharedServer.init(_metaGrid);
 sharedClient.init(_metaGrid);
 }
 }

 static void Reset() {
 sharedServer.reset();
 sharedClient.reset();
 }

private
 static class Cell {
 const int cx;
 const int cy;
 GlobalObjectLookup.Chunk[] chunks = new GlobalObjectLookup.Chunk[900];

 Cell(int int0, int int1) {
 this->cx = int0;
 this->cy = int1;
 }

 GlobalObjectLookup.Chunk getChunkAt(int int1, int int3, boolean boolean0) {
 int int0 = (int1 - this->cx * 300) / 10;
 int int2 = (int3 - this->cy * 300) / 10;
 int int4 = int0 + int2 * 30;
 if (this->chunks[int4] == nullptr && boolean0) {
 this->chunks[int4] = new GlobalObjectLookup.Chunk();
 }

 return this->chunks[int4];
 }

 GlobalObjectLookup.Chunk getChunkForObject(GlobalObject globalObject,
 boolean boolean0) {
 return this->getChunkAt(globalObject.x, globalObject.y, boolean0);
 }

 void addObject(GlobalObject globalObject) {
 GlobalObjectLookup.Chunk chunk =
 this->getChunkForObject(globalObject, true);
 if (chunk.objects.contains(globalObject) {
 throw IllegalStateException("duplicate object");
 } else {
 chunk.objects.add(globalObject);
 }
 }

 void removeObject(GlobalObject globalObject) {
 GlobalObjectLookup.Chunk chunk =
 this->getChunkForObject(globalObject, false);
 if (chunk != nullptr && chunk.objects.contains(globalObject) {
 chunk.objects.remove(globalObject);
 } else {
 throw IllegalStateException("chunk doesn't contain object");
 }
 }

 void Reset() {
 for (int int0 = 0; int0 < this->chunks.length; int0++) {
 GlobalObjectLookup.Chunk chunk = this->chunks[int0];
 if (chunk != nullptr) {
 chunk.Reset();
 }
 }

 Arrays.fill(this->chunks, nullptr);
 }
 }

 private static class Chunk {
 ArrayList<GlobalObject> objects = std::make_unique<ArrayList<>>();

 void Reset() { this->objects.clear(); }
 }

 private static class Shared {
 GlobalObjectLookup.Cell[] cells;

 void init(IsoMetaGrid metaGrid) {
 this->cells = new GlobalObjectLookup
 .Cell[metaGrid.getWidth() * metaGrid.getHeight()];
 }

 void reset() {
 if (this->cells != nullptr) {
 for (int int0 = 0; int0 < this->cells.length; int0++) {
 GlobalObjectLookup.Cell cell = this->cells[int0];
 if (cell != nullptr) {
 cell.Reset();
 }
 }

 this->cells = nullptr;
 }
 }
 }
}
} // namespace globalObjects
} // namespace zombie
