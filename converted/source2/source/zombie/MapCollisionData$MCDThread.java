package zombie;

import java.util.ArrayDeque;
import java.util.Queue;
import zombie.MapCollisionData.PathTask;
import zombie.core.logger.ExceptionLogger;
import zombie.network.MPStatistic;
import zombie.popman.ZombiePopulationManager;

final class MapCollisionData$MCDThread extends Thread {
   public final Object notifier;
   public boolean bStop;
   public volatile boolean bSave;
   public volatile boolean bWaiting;
   public Queue<PathTask> pathTasks;

   private MapCollisionData$MCDThread(MapCollisionData var1) {
      this.this$0 = var1;
      this.notifier = new Object();
      this.pathTasks = new ArrayDeque<>();
   }

   @Override
   public void run() {
      while (!this.bStop) {
         try {
            this.runInner();
         } catch (Exception var2) {
            ExceptionLogger.logException(var2);
         }
      }
   }

   private void runInner() {
      MPStatistic.getInstance().MapCollisionThread.Start();
      this.this$0.sync.startFrame();
      synchronized (this.this$0.renderLock) {
         for (PathTask var2 = (PathTask)this.this$0.pathTaskQueue.poll(); var2 != null; var2 = (PathTask)this.this$0.pathTaskQueue.poll()) {
            var2.execute();
            var2.release();
         }

         if (this.bSave) {
            MapCollisionData.n_save();
            ZombiePopulationManager.instance.save();
            this.bSave = false;
         }

         MapCollisionData.n_update();
         ZombiePopulationManager.instance.updateThread();
      }

      this.this$0.sync.endFrame();
      MPStatistic.getInstance().MapCollisionThread.End();

      while (this.shouldWait()) {
         synchronized (this.notifier) {
            this.bWaiting = true;

            try {
               this.notifier.wait();
            } catch (InterruptedException var5) {
            }
         }
      }

      this.bWaiting = false;
   }

   private boolean shouldWait() {
      if (this.bStop || this.bSave) {
         return false;
      } else if (!MapCollisionData.n_shouldWait()) {
         return false;
      } else {
         return !ZombiePopulationManager.instance.shouldWait() ? false : this.this$0.pathTaskQueue.isEmpty() && this.pathTasks.isEmpty();
      }
   }
}
