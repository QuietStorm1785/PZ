#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameWindow.h"
#include "zombie/core/Core.h"
#include "zombie/core/ThreadGroups.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/objects/IsoTree.h"
#include "zombie/network/MPStatistic.h"
#include <algorithm>

namespace zombie {
namespace iso {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class WorldReuserThread {
public:
 static const WorldReuserThread instance = new WorldReuserThread();
 private ArrayList<IsoObject> objectsToReuse = std::make_unique<ArrayList<>>();
 private ArrayList<IsoTree> treesToReuse = std::make_unique<ArrayList<>>();
 bool finished;
 Thread worldReuser;
 private ConcurrentLinkedQueue<IsoChunk> reuseGridSquares = std::make_unique<ConcurrentLinkedQueue<>>();

 void run() {
 this->worldReuser = new Thread(ThreadGroups.Workers, () -> {
 while (!this->finished) {
 MPStatistic.getInstance().WorldReuser.Start();
 this->testReuseChunk();
 this->reconcileReuseObjects();
 MPStatistic.getInstance().WorldReuser.End();

 try {
 Thread.sleep(1000L);
 } catch (InterruptedException interruptedException) {
 interruptedException.printStackTrace();
 }
 }
 });
 this->worldReuser.setName("WorldReuser");
 this->worldReuser.setDaemon(true);
 this->worldReuser.setUncaughtExceptionHandler(GameWindow::uncaughtException);
 this->worldReuser.start();
 }

 void reconcileReuseObjects() {
 synchronized (this->objectsToReuse) {
 if (!this->objectsToReuse.empty()) {
 synchronized (CellLoader.isoObjectCache) {
 if (CellLoader.isoObjectCache.size() < 320000) {
 CellLoader.isoObjectCache.addAll(this->objectsToReuse);
 }
 }

 this->objectsToReuse.clear();
 }
 }

 synchronized (this->treesToReuse) {
 if (!this->treesToReuse.empty()) {
 synchronized (CellLoader.isoTreeCache) {
 if (CellLoader.isoTreeCache.size() < 40000) {
 CellLoader.isoTreeCache.addAll(this->treesToReuse);
 }
 }

 this->treesToReuse.clear();
 }
 }
 }

 void testReuseChunk() {
 for (IsoChunk chunk = this->reuseGridSquares.poll(); chunk != nullptr; chunk = this->reuseGridSquares.poll()) {
 if (Core.bDebug) {
 if (ChunkSaveWorker.instance.toSaveQueue.contains(chunk) {
 DebugLog.log("ERROR: reusing chunk that needs to be saved");
 }

 if (IsoChunkMap.chunkStore.contains(chunk) {
 DebugLog.log("ERROR: reusing chunk in chunkStore");
 }

 if (!chunk.refs.empty()) {
 DebugLog.log("ERROR: reusing chunk with refs");
 }
 }

 if (Core.bDebug) {
 }

 this->reuseGridSquares(chunk);
 if (this->treesToReuse.size() > 1000 || this->objectsToReuse.size() > 5000) {
 this->reconcileReuseObjects();
 }
 }
 }

 void addReuseChunk(IsoChunk chunk) {
 this->reuseGridSquares.add(chunk);
 }

 void reuseGridSquares(IsoChunk chunk) {
 uint8_t byte0 = 100;

 for (int int0 = 0; int0 < 8; int0++) {
 for (int int1 = 0; int1 < byte0; int1++) {
 IsoGridSquare square = chunk.squares[int0][int1];
 if (square != nullptr) {
 for (int int2 = 0; int2 < square.getObjects().size(); int2++) {
 IsoObject object = square.getObjects().get(int2);
 if (object instanceof IsoTree) {
 object.reset();
 synchronized (this->treesToReuse) {
 this->treesToReuse.add((IsoTree)object);
 }
 } else if (object.getClass() == IsoObject.class) {
 object.reset();
 synchronized (this->objectsToReuse) {
 this->objectsToReuse.add(object);
 }
 } else {
 object.reuseGridSquare();
 }
 }

 square.discard();
 chunk.squares[int0][int1] = nullptr;
 }
 }
 }

 chunk.resetForStore();
 IsoChunkMap.chunkStore.add(chunk);
 }
}
} // namespace iso
} // namespace zombie
