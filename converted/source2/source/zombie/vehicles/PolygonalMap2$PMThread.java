package zombie.vehicles;

import zombie.core.logger.ExceptionLogger;
import zombie.network.MPStatistic;

final class PolygonalMap2$PMThread extends Thread {
   public boolean bStop;
   public final Object notifier;

   private PolygonalMap2$PMThread(PolygonalMap2 var1) {
      this.this$0 = var1;
      this.notifier = new Object();
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
      MPStatistic.getInstance().PolyPathThread.Start();
      this.this$0.sync.startFrame();
      synchronized (this.this$0.renderLock) {
         PolygonalMap2.instance.updateThread();
      }

      this.this$0.sync.endFrame();
      MPStatistic.getInstance().PolyPathThread.End();

      while (this.shouldWait()) {
         synchronized (this.notifier) {
            try {
               this.notifier.wait();
            } catch (InterruptedException var4) {
            }
         }
      }
   }

   private boolean shouldWait() {
      if (this.bStop) {
         return false;
      } else if (!PolygonalMap2.instance.chunkTaskQueue.isEmpty()) {
         return false;
      } else if (!PolygonalMap2.instance.squareTaskQueue.isEmpty()) {
         return false;
      } else if (!PolygonalMap2.instance.vehicleTaskQueue.isEmpty()) {
         return false;
      } else {
         return !PolygonalMap2.instance.requestTaskQueue.isEmpty() ? false : PolygonalMap2.instance.requests.isEmpty();
      }
   }

   void wake() {
      synchronized (this.notifier) {
         this.notifier.notify();
      }
   }
}
