#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/debug/DebugType.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/network/ServerChunkLoader/LoaderThread.h"
#include "zombie/network/ServerChunkLoader/RecalcAllThread.h"
#include "zombie/network/ServerChunkLoader/SaveChunkThread.h"
#include "zombie/network/ServerMap/ServerCell.h"
#include <algorithm>

namespace zombie {
namespace network {


class ServerChunkLoader {
public:
    long debugSlowMapLoadingDelay = 0L;
    bool MapLoading = false;
    LoaderThread threadLoad;
    SaveChunkThread threadSave;
    const CRC32 crcSave = std::make_shared<CRC32>();
    RecalcAllThread threadRecalc;

    public ServerChunkLoader() {
      this.threadLoad = std::make_shared<LoaderThread>(this);
      this.threadLoad.setName("LoadChunk");
      this.threadLoad.setDaemon(true);
      this.threadLoad.start();
      this.threadRecalc = std::make_shared<RecalcAllThread>(this);
      this.threadRecalc.setName("RecalcAll");
      this.threadRecalc.setDaemon(true);
      this.threadRecalc.setPriority(10);
      this.threadRecalc.start();
      this.threadSave = std::make_shared<SaveChunkThread>(this);
      this.threadSave.setName("SaveChunk");
      this.threadSave.setDaemon(true);
      this.threadSave.start();
   }

    void addJob(ServerCell var1) {
      this.MapLoading = DebugType.Do(DebugType.MapLoading);
      this.threadLoad.toThread.push_back(var1);
      MPStatistic.getInstance().LoaderThreadTasks.Added();
   }

    void getLoaded(std::vector<ServerCell> var1) {
      this.threadLoad.fromThread.drainTo(var1);
   }

    void quit() {
      this.threadLoad.quit();

      while (this.threadLoad.isAlive()) {
         try {
            Thread.sleep(500L);
         } catch (InterruptedException var3) {
         }
      }

      this.threadSave.quit();

      while (this.threadSave.isAlive()) {
         try {
            Thread.sleep(500L);
         } catch (InterruptedException var2) {
         }
      }
   }

    void addSaveUnloadedJob(IsoChunk var1) {
      this.threadSave.addUnloadedJob(var1);
   }

    void addSaveLoadedJob(IsoChunk var1) {
      this.threadSave.addLoadedJob(var1);
   }

    void saveLater(GameTime var1) {
      this.threadSave.saveLater(var1);
   }

    void updateSaved() {
      this.threadSave.update();
   }

    void addRecalcJob(ServerCell var1) {
      this.threadRecalc.toThread.push_back(var1);
      MPStatistic.getInstance().RecalcThreadTasks.Added();
   }

    void getRecalc(std::vector<ServerCell> var1) {
      MPStatistic.getInstance().ServerMapLoaded2.Added(this.threadRecalc.fromThread.size());
      this.threadRecalc.fromThread.drainTo(var1);
      MPStatistic.getInstance().RecalcThreadTasks.Processed();
   }
}
} // namespace network
} // namespace zombie
