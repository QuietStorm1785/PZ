package zombie.network;

import java.io.IOException;
import java.net.Socket;
import java.util.ArrayList;
import zombie.debug.DebugLog;
import zombie.network.RCONServer.ClientThread;

class RCONServer$ServerThread extends Thread {
   private ArrayList<ClientThread> connections;
   public boolean bQuit;

   public RCONServer$ServerThread(RCONServer var1) {
      this.this$0 = var1;
      this.connections = new ArrayList<>();
      this.setName("RCONServer");
   }

   @Override
   public void run() {
      while (!this.bQuit) {
         this.runInner();
      }
   }

   private void runInner() {
      try {
         Socket var1 = this.this$0.welcomeSocket.accept();

         for (int var2 = 0; var2 < this.connections.size(); var2++) {
            ClientThread var3 = this.connections.get(var2);
            if (!var3.isAlive()) {
               this.connections.remove(var2--);
            }
         }

         if (this.connections.size() >= 5) {
            var1.close();
            return;
         }

         DebugLog.log("RCON: new connection " + var1.toString());
         ClientThread var5 = new ClientThread(var1, this.this$0.password);
         this.connections.add(var5);
         var5.start();
      } catch (IOException var4) {
         if (!this.bQuit) {
            var4.printStackTrace();
         }
      }
   }

   public void quit() {
      this.bQuit = true;

      while (this.isAlive()) {
         try {
            Thread.sleep(50L);
         } catch (InterruptedException var3) {
            var3.printStackTrace();
         }
      }

      for (int var1 = 0; var1 < this.connections.size(); var1++) {
         ClientThread var2 = this.connections.get(var1);
         var2.quit();
      }
   }
}
