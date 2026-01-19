package zombie.network;

import zombie.core.logger.ExceptionLogger;
import zombie.savefile.ServerPlayerDB;
import zombie.vehicles.VehiclesDB2;

final class ServerPlayersVehicles$SPVThread extends Thread {
   boolean m_bStop = false;

   private ServerPlayersVehicles$SPVThread() {
   }

   @Override
   public void run() {
      while (!this.m_bStop) {
         try {
            this.runInner();
         } catch (Throwable var2) {
            ExceptionLogger.logException(var2);
         }
      }
   }

   void runInner() {
      ServerPlayerDB.getInstance().process();
      VehiclesDB2.instance.updateWorldStreamer();

      try {
         Thread.sleep(500L);
      } catch (InterruptedException var2) {
      }
   }
}
