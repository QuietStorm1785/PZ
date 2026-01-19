package zombie.network;

public class ServerWorldDatabase$LogonResult {
   public boolean bAuthorized;
   public int x;
   public int y;
   public int z;
   public boolean newUser;
   public boolean admin;
   public boolean banned;
   public boolean priority;
   public String bannedReason;
   public String dcReason;
   public String accessLevel;
   public int transactionID;

   public ServerWorldDatabase$LogonResult(ServerWorldDatabase var1) {
      this.this$0 = var1;
      this.bAuthorized = false;
      this.newUser = false;
      this.admin = false;
      this.banned = false;
      this.priority = false;
      this.bannedReason = null;
      this.dcReason = null;
      this.accessLevel = "";
      this.transactionID = 0;
   }
}
