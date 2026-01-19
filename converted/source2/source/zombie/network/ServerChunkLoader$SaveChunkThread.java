package zombie.network;

import java.util.ArrayList;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.zip.CRC32;
import zombie.GameTime;
import zombie.core.logger.LoggerManager;
import zombie.iso.IsoChunk;
import zombie.network.ClientChunkRequest.Chunk;
import zombie.network.ServerChunkLoader.QuitThreadTask;
import zombie.network.ServerChunkLoader.SaveGameTimeTask;
import zombie.network.ServerChunkLoader.SaveLoadedTask;
import zombie.network.ServerChunkLoader.SaveTask;
import zombie.network.ServerChunkLoader.SaveUnloadedTask;

class ServerChunkLoader$SaveChunkThread extends Thread {
   private final LinkedBlockingQueue<SaveTask> toThread;
   private final LinkedBlockingQueue<SaveTask> fromThread;
   private boolean quit;
   private final CRC32 crc32;
   private final ClientChunkRequest ccr;
   private final ArrayList<SaveTask> toSaveChunk;
   private final ArrayList<SaveTask> savedChunks;

   private ServerChunkLoader$SaveChunkThread(ServerChunkLoader var1) {
      this.this$0 = var1;
      this.toThread = new LinkedBlockingQueue<>();
      this.fromThread = new LinkedBlockingQueue<>();
      this.quit = false;
      this.crc32 = new CRC32();
      this.ccr = new ClientChunkRequest();
      this.toSaveChunk = new ArrayList<>();
      this.savedChunks = new ArrayList<>();
   }

   @Override
   public void run() {
      do {
         SaveTask var1 = null;

         try {
            MPStatistic.getInstance().SaveThread.End();
            var1 = this.toThread.take();
            MPStatistic.getInstance().SaveThread.Start();
            MPStatistic.getInstance().IncrementSaveCellToDisk();
            var1.save();
            this.fromThread.add(var1);
            MPStatistic.getInstance().SaveTasks.Processed();
         } catch (InterruptedException var3) {
         } catch (Exception var4) {
            var4.printStackTrace();
            if (var1 != null) {
               LoggerManager.getLogger("map").write("Error saving chunk " + var1.wx() + "," + var1.wy());
            }

            LoggerManager.getLogger("map").write(var4);
         }
      } while (!this.quit || !this.toThread.isEmpty());
   }

   public void addUnloadedJob(IsoChunk var1) {
      this.toThread.add(new SaveUnloadedTask(this.this$0, var1));
      MPStatistic.getInstance().SaveTasks.SaveUnloadedTasksAdded();
   }

   public void addLoadedJob(IsoChunk var1) {
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

      this.toThread.add(new SaveLoadedTask(this.this$0, this.ccr, var2));
      MPStatistic.getInstance().SaveTasks.SaveLoadedTasksAdded();
   }

   public void saveLater(GameTime var1) {
      this.toThread.add(new SaveGameTimeTask(this.this$0, var1));
      MPStatistic.getInstance().SaveTasks.SaveGameTimeTasksAdded();
   }

   public void saveNow(int var1, int var2) {
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
            this.fromThread.add(var4);
         }
      }

      this.toThread.addAll(this.toSaveChunk);
   }

   public void quit() {
      this.toThread.add(new QuitThreadTask(this.this$0));
      MPStatistic.getInstance().SaveTasks.QuitThreadTasksAdded();
   }

   public void update() {
      this.savedChunks.clear();
      this.fromThread.drainTo(this.savedChunks);

      for (int var1 = 0; var1 < this.savedChunks.size(); var1++) {
         this.savedChunks.get(var1).release();
      }

      this.savedChunks.clear();
   }
}
