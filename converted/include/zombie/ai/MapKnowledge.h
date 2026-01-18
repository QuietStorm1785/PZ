#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/objects/IsoDoor.h"
#include "zombie/iso/objects/IsoThumpable.h"
#include "zombie/iso/objects/IsoWindow.h"
#include "zombie/iso/objects/IsoWindowFrame.h"

namespace zombie {
namespace ai {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class MapKnowledge {
public:
 private ArrayList<KnownBlockedEdges> knownBlockedEdges = std::make_unique<ArrayList<>>();

 public ArrayList<KnownBlockedEdges> getKnownBlockedEdges() {
 return this->knownBlockedEdges;
 }

 KnownBlockedEdges getKnownBlockedEdges(int x, int y, int z) {
 for (int int0 = 0; int0 < this->knownBlockedEdges.size(); int0++) {
 KnownBlockedEdges knownBlockedEdgesx = this->knownBlockedEdges.get(int0);
 if (knownBlockedEdgesx.x == x && knownBlockedEdgesx.y == y && knownBlockedEdgesx.z == z) {
 return knownBlockedEdgesx;
 }
 }

 return nullptr;
 }

 KnownBlockedEdges createKnownBlockedEdges(int int0, int int1, int int2) {
 assert this->getKnownBlockedEdges(int0, int1, int2) == nullptr;

 KnownBlockedEdges knownBlockedEdgesx = KnownBlockedEdges.alloc();
 knownBlockedEdgesx.init(int0, int1, int2);
 this->knownBlockedEdges.add(knownBlockedEdgesx);
 return knownBlockedEdgesx;
 }

 KnownBlockedEdges getOrCreateKnownBlockedEdges(int x, int y, int z) {
 KnownBlockedEdges knownBlockedEdgesx = this->getKnownBlockedEdges(x, y, z);
 if (knownBlockedEdgesx.empty()) {
 knownBlockedEdgesx = this->createKnownBlockedEdges(x, y, z);
 }

 return knownBlockedEdgesx;
 }

 void releaseIfEmpty(KnownBlockedEdges knownBlockedEdgesx) {
 if (!knownBlockedEdgesx.n && !knownBlockedEdgesx.w) {
 this->knownBlockedEdges.remove(knownBlockedEdgesx);
 knownBlockedEdgesx.release();
 }
 }

 void setKnownBlockedEdgeW(int x, int y, int z, bool blocked) {
 KnownBlockedEdges knownBlockedEdgesx = this->getOrCreateKnownBlockedEdges(x, y, z);
 knownBlockedEdgesx.w = blocked;
 this->releaseIfEmpty(knownBlockedEdgesx);
 }

 void setKnownBlockedEdgeN(int x, int y, int z, bool blocked) {
 KnownBlockedEdges knownBlockedEdgesx = this->getOrCreateKnownBlockedEdges(x, y, z);
 knownBlockedEdgesx.n = blocked;
 this->releaseIfEmpty(knownBlockedEdgesx);
 }

 void setKnownBlockedDoor(IsoDoor object, bool blocked) {
 IsoGridSquare square = object.getSquare();
 if (object.getNorth()) {
 this->setKnownBlockedEdgeN(square.x, square.y, square.z, blocked);
 } else {
 this->setKnownBlockedEdgeW(square.x, square.y, square.z, blocked);
 }
 }

 void setKnownBlockedDoor(IsoThumpable object, bool blocked) {
 if (object.isDoor()) {
 IsoGridSquare square = object.getSquare();
 if (object.getNorth()) {
 this->setKnownBlockedEdgeN(square.x, square.y, square.z, blocked);
 } else {
 this->setKnownBlockedEdgeW(square.x, square.y, square.z, blocked);
 }
 }
 }

 void setKnownBlockedWindow(IsoWindow object, bool blocked) {
 IsoGridSquare square = object.getSquare();
 if (object.getNorth()) {
 this->setKnownBlockedEdgeN(square.x, square.y, square.z, blocked);
 } else {
 this->setKnownBlockedEdgeW(square.x, square.y, square.z, blocked);
 }
 }

 void setKnownBlockedWindowFrame(IsoObject object, bool blocked) {
 IsoGridSquare square = object.getSquare();
 if (IsoWindowFrame.isWindowFrame(object, true) {
 this->setKnownBlockedEdgeN(square.x, square.y, square.z, blocked);
 } else if (IsoWindowFrame.isWindowFrame(object, false) {
 this->setKnownBlockedEdgeW(square.x, square.y, square.z, blocked);
 }
 }

 void forget() {
 KnownBlockedEdges.releaseAll(this->knownBlockedEdges);
 this->knownBlockedEdges.clear();
 }
}
} // namespace ai
} // namespace zombie
