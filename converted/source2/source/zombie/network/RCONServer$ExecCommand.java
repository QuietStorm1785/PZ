package zombie.network;

import zombie.network.RCONServer.ClientThread;

class RCONServer$ExecCommand {
   public int ID;
   public String command;
   public String response;
   public ClientThread thread;

   public RCONServer$ExecCommand(int var1, String var2, ClientThread var3) {
      this.ID = var1;
      this.command = var2;
      this.thread = var3;
   }

   public void update() {
      this.response = GameServer.rcon(this.command);
      if (this.thread.isAlive()) {
         this.thread.toThread.add(this);
      }
   }
}
