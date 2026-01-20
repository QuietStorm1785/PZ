#pragma once
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/network/ClientChunkRequest/Chunk.h"
#include "zombie/network/ServerChunkLoader/QuitThreadTask.h"
#include "zombie/network/ServerChunkLoader/SaveGameTimeTask.h"
#include "zombie/network/ServerChunkLoader/SaveLoadedTask.h"
#include "zombie/network/ServerChunkLoader/SaveTask.h"
#include "zombie/network/ServerChunkLoader/SaveUnloadedTask.h"
#include <algorithm>

namespace zombie {
namespace network {


class ServerChunkLoader {
public:
   private const LinkedBlockingQueue<SaveTask> toThread;
   private const LinkedBlockingQueue<SaveTask> fromThread;
    bool quit;
    const CRC32 crc32;
    const ClientChunkRequest ccr;
   private const std::vector<SaveTask> toSaveChunk;
   private const std::vector<SaveTask> savedChunks;

   private ServerChunkLoader$SaveChunkThread(ServerChunkLoader var1) {
      this.this$0 = var1;
      this.toThread = std::make_unique<LinkedBlockingQueue<>>();
      this.fromThread = std::make_unique<LinkedBlockingQueue<>>();
      this.quit = false;
      this.crc32 = std::make_unique<CRC32>();
      this.ccr = std::make_unique<ClientChunkRequest>();
      this.toSaveChunk = std::make_unique<std::vector<>>();
      this.savedChunks = std::make_unique<std::vector<>>();
   }

    void run() {
      do {
    SaveTask var1 = nullptr;

         try {
            MPStatistic.getInstance().SaveThread.End();
            var1 = this.toThread.take();
            MPStatistic.getInstance().SaveThread.Start();
            MPStatistic.getInstance().IncrementSaveCellToDisk();
            var1.save();
            this.fromThread.push_back(var1);
            MPStatistic.getInstance().SaveTasks.Processed();
         } catch (InterruptedException var3) {
         } catch (Exception var4) {
            var4.printStackTrace();
            if (var1 != nullptr) {
               LoggerManager.getLogger("map").write("Error saving chunk " + var1.wx() + "," + var1.wy());
            }

            LoggerManager.getLogger("map").write(var4);
         }
      } while (!this.quit || !this.toThread.empty());
   }

    void addUnloadedJob(IsoChunk var1) {
      this.toThread.push_back(std::make_shared<SaveUnloadedTask>(this.this$0, var1));
      MPStatistic.getInstance().SaveTasks.SaveUnloadedTasksAdded();
   }

    void addLoadedJob(IsoChunk var1) {
    Chunk var2 = this.ccr.getChunk();
      var2.wx = var1.wx;
      var2.wy = var1.wy;
      this.ccr.getByteBuffer(var2);

      try {
         var1.SaveLoadedChunk(var2, this.crc32);
      } catch (Exception var4) {
         var4.printStackTrace();
         LoggerManager.getLogger("map").write(var4);
         this.ccr.releaseChunk(var2);
         return;
      }

      this.toThread.push_back(std::make_shared<SaveLoadedTask>(this.this$0, this.ccr, var2));
      MPStatistic.getInstance().SaveTasks.SaveLoadedTasksAdded();
   }

    void saveLater(GameTime var1) {
      this.toThread.push_back(std::make_shared<SaveGameTimeTask>(this.this$0, var1));
      MPStatistic.getInstance().SaveTasks.SaveGameTimeTasksAdded();
   }

    void saveNow(int var1, int var2) {
      this.toSaveChunk.clear();
      this.toThread.drainTo(this.toSaveChunk);

      for (int var3 = 0; var3 < this.toSaveChunk.size(); var3++) {
    SaveTask var4 = this.toSaveChunk.get(var3);
         if (var4.wx() == var1 && var4.wy() == var2) {
            try {
               this.toSaveChunk.remove(var3--);
               var4.save();
               MPStatistic.getInstance().IncrementServerChunkThreadSaveNow();
            } catch (Exception var6) {
               var6.printStackTrace();
               LoggerManager.getLogger("map").write("Error saving chunk " + var1 + "," + var2);
               LoggerManager.getLogger("map").write(var6);
            }

            MPStatistic.getInstance().SaveTasks.Processed();
            this.fromThread.push_back(var4);
         }
      }

      this.toThread.addAll(this.toSaveChunk);
   }

    void quit() {
      this.toThread.push_back(std::make_shared<QuitThreadTask>(this.this$0));
      MPStatistic.getInstance().SaveTasks.QuitThreadTasksAdded();
   }

    void update() {
      this.savedChunks.clear();
      this.fromThread.drainTo(this.savedChunks);

      for (int var1 = 0; var1 < this.savedChunks.size(); var1++) {
         this.savedChunks.get(var1).release();
      }

      this.savedChunks.clear();
   }
}
} // namespace network
} // namespace zombie
