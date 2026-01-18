#include "zombie/ai/MapKnowledge.h"

namespace zombie {
namespace ai {

KnownBlockedEdges MapKnowledge::getKnownBlockedEdges(int x, int y, int z) {
 // TODO: Implement getKnownBlockedEdges
 return nullptr;
}

KnownBlockedEdges MapKnowledge::createKnownBlockedEdges(int int0, int int1, int int2) {
 // TODO: Implement createKnownBlockedEdges
 return nullptr;
}

KnownBlockedEdges MapKnowledge::getOrCreateKnownBlockedEdges(int x, int y, int z) {
 // TODO: Implement getOrCreateKnownBlockedEdges
 return nullptr;
}

void MapKnowledge::releaseIfEmpty(KnownBlockedEdges knownBlockedEdgesx) {
 // TODO: Implement releaseIfEmpty
}

void MapKnowledge::setKnownBlockedEdgeW(int x, int y, int z, bool blocked) {
 // TODO: Implement setKnownBlockedEdgeW
}

void MapKnowledge::setKnownBlockedEdgeN(int x, int y, int z, bool blocked) {
 // TODO: Implement setKnownBlockedEdgeN
}

void MapKnowledge::setKnownBlockedDoor(IsoDoor object, bool blocked) {
 // TODO: Implement setKnownBlockedDoor
}

void MapKnowledge::setKnownBlockedDoor(IsoThumpable object, bool blocked) {
 // TODO: Implement setKnownBlockedDoor
}

void MapKnowledge::setKnownBlockedWindow(IsoWindow object, bool blocked) {
 // TODO: Implement setKnownBlockedWindow
}

void MapKnowledge::setKnownBlockedWindowFrame(IsoObject object, bool blocked) {
 // TODO: Implement setKnownBlockedWindowFrame
}

void MapKnowledge::forget() {
 // TODO: Implement forget
}

} // namespace ai
} // namespace zombie
