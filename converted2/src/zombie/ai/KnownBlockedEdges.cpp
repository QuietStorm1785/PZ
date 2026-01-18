#include "zombie/ai/KnownBlockedEdges.h"

namespace zombie {
namespace ai {

KnownBlockedEdges KnownBlockedEdges::init(KnownBlockedEdges other) {
  // TODO: Implement init
  return nullptr;
}

KnownBlockedEdges KnownBlockedEdges::init(int _x, int _y, int _z) {
  // TODO: Implement init
  return nullptr;
}

KnownBlockedEdges KnownBlockedEdges::init(int _x, int _y, int _z, bool _w,
                                          bool _n) {
  // TODO: Implement init
  return nullptr;
}

bool KnownBlockedEdges::isBlocked(int otherX, int otherY) {
  // TODO: Implement isBlocked
  return false;
}

KnownBlockedEdges KnownBlockedEdges::alloc() {
  // TODO: Implement alloc
  return nullptr;
}

void KnownBlockedEdges::releaseAll(ArrayList<KnownBlockedEdges> objs) {
  // TODO: Implement releaseAll
}

void KnownBlockedEdges::release() {
  // TODO: Implement release
}

} // namespace ai
} // namespace zombie
