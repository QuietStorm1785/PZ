package zombie.network;

import zombie.network.ServerPlayersVehicles.SPVThread;

public class ServerPlayersVehicles {
   public static final ServerPlayersVehicles instance = new ServerPlayersVehicles();
   private SPVThread m_thread = null;

   public void init() {
      this.m_thread = new SPVThread();
      this.m_thread.setName("ServerPlayersVehicles");
      this.m_thread.setDaemon(true);
      this.m_thread.start();
   }

   public void stop() {
      if (this.m_thread != null) {
         this.m_thread.m_bStop = true;

         while (this.m_thread.isAlive()) {
            try {
               Thread.sleep(100L);
            } catch (InterruptedException var2) {
            }
         }

         this.m_thread = null;
      }
   }
}
