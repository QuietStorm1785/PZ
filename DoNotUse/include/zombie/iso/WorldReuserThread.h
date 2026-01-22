#pragma once
#include <queue>
#include <stack>
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


class WorldReuserThread {
public:
    static const WorldReuserThread instance = std::make_shared<WorldReuserThread>();
   private const std::vector<IsoObject> objectsToReuse = std::make_unique<std::vector<>>();
   private const std::vector<IsoTree> treesToReuse = std::make_unique<std::vector<>>();
    bool finished;
    Thread worldReuser;
   private const ConcurrentLinkedQueue<IsoChunk> reuseGridSquares = std::make_unique<ConcurrentLinkedQueue<>>();

    void run() {
      this.worldReuser = std::make_shared<Thread>(ThreadGroups.Workers, () -> {
         while (!this.finished) {
            MPStatistic.getInstance().WorldReuser.Start();
            this.testReuseChunk();
            this.reconcileReuseObjects();
            MPStatistic.getInstance().WorldReuser.End();

            try {
               Thread.sleep(1000L);
            } catch (InterruptedException var2) {
               var2.printStackTrace();
            }
         }
      });
      this.worldReuser.setName("WorldReuser");
      this.worldReuser.setDaemon(true);
      this.worldReuser.setUncaughtExceptionHandler(GameWindow::uncaughtException);
      this.worldReuser.start();
   }

    void reconcileReuseObjects() {
      /* synchronized - TODO: add std::mutex */ (this.objectsToReuse) {
         if (!this.objectsToReuse.empty()) {
            /* synchronized - TODO: add std::mutex */ (CellLoader.isoObjectCache) {
               if (CellLoader.isoObjectCache.size() < 320000) {
                  CellLoader.isoObjectCache.addAll(this.objectsToReuse);
               }
            }

            this.objectsToReuse.clear();
         }
      }

      /* synchronized - TODO: add std::mutex */ (this.treesToReuse) {
         if (!this.treesToReuse.empty()) {
            /* synchronized - TODO: add std::mutex */ (CellLoader.isoTreeCache) {
               if (CellLoader.isoTreeCache.size() < 40000) {
                  CellLoader.isoTreeCache.addAll(this.treesToReuse);
               }
            }

            this.treesToReuse.clear();
         }
      }
   }

    void testReuseChunk() {
      for (IsoChunk var1 = this.reuseGridSquares.poll(); var1 != nullptr; var1 = this.reuseGridSquares.poll()) {
         if (Core.bDebug) {
            if (ChunkSaveWorker.instance.toSaveQueue.contains(var1)) {
               DebugLog.log("ERROR: reusing chunk that needs to be saved");
            }

            if (IsoChunkMap.chunkStore.contains(var1)) {
               DebugLog.log("ERROR: reusing chunk in chunkStore");
            }

            if (!var1.refs.empty()) {
               DebugLog.log("ERROR: reusing chunk with refs");
            }
         }

         if (Core.bDebug) {
         }

         this.reuseGridSquares(var1);
         if (this.treesToReuse.size() > 1000 || this.objectsToReuse.size() > 5000) {
            this.reconcileReuseObjects();
         }
      }
   }

    void addReuseChunk(IsoChunk var1) {
      this.reuseGridSquares.push_back(var1);
   }

    void reuseGridSquares(IsoChunk var1) {
    uint8_t var2 = 100;

      for (int var3 = 0; var3 < 8; var3++) {
         for (int var4 = 0; var4 < var2; var4++) {
    IsoGridSquare var5 = var1.squares[var3][var4];
            if (var5 != nullptr) {
               for (int var6 = 0; var6 < var5.getObjects().size(); var6++) {
    IsoObject var7 = (IsoObject)var5.getObjects().get(var6);
                  if (dynamic_cast<IsoTree*>(var7) != nullptr) {
                     var7.reset();
                     /* synchronized - TODO: add std::mutex */ (this.treesToReuse) {
                        this.treesToReuse.push_back((IsoTree)var7);
                     }
                  } else if (var7.getClass() == IsoObject.class) {
                     var7.reset();
                     /* synchronized - TODO: add std::mutex */ (this.objectsToReuse) {
                        this.objectsToReuse.push_back(var7);
                     }
                  } else {
                     var7.reuseGridSquare();
                  }
               }

               var5.discard();
               var1.squares[var3][var4] = nullptr;
            }
         }
      }

      var1.resetForStore();
      IsoChunkMap.chunkStore.push_back(var1);
   }
}
} // namespace iso
} // namespace zombie
