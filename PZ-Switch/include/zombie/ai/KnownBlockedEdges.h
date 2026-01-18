#pragma once
#include "zombie/GameWindow.h"
#include "zombie/network/GameServer.h"
#include "zombie/popman/ObjectPool.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace ai {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class KnownBlockedEdges {
public:
 int x;
 int y;
 int z;
 bool w;
 bool n;
 static ObjectPool<KnownBlockedEdges> pool =
 new ObjectPool<>(KnownBlockedEdges::new);

 KnownBlockedEdges init(KnownBlockedEdges other) {
 return this->init(other.x, other.y, other.z, other.w, other.n);
 }

 KnownBlockedEdges init(int _x, int _y, int _z) {
 return this->init(_x, _y, _z, false, false);
 }

 KnownBlockedEdges init(int _x, int _y, int _z, bool _w, bool _n) {
 this->x = _x;
 this->y = _y;
 this->z = _z;
 this->w = _w;
 this->n = _n;
 return this;
 }

 bool isBlocked(int otherX, int otherY) {
 return this->x > otherX && this->w ? true : this->y > otherY && this->n;
 }

 static KnownBlockedEdges alloc() {
 assert GameServer.bServer ||
 Thread.currentThread() == GameWindow.GameThread;

 return pool.alloc();
 }

 static void releaseAll(ArrayList<KnownBlockedEdges> objs) {
 assert GameServer.bServer ||
 Thread.currentThread() == GameWindow.GameThread;

 pool.release(objs);
 }

 void release() {
 assert GameServer.bServer ||
 Thread.currentThread() == GameWindow.GameThread;

 pool.release(this);
 }
}
} // namespace ai
} // namespace zombie
