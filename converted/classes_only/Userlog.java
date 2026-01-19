package zombie.network;

public class Userlog {
   private final String username;
   private final String type;
   private final String text;
   private final String issuedBy;
   private final String lastUpdate;
   private int amount;

   public Userlog(String var1, String var2, String var3, String var4, int var5, String var6) {
      this.username = var1;
      this.type = var2;
      this.text = var3;
      this.issuedBy = var4;
      this.amount = var5;
      this.lastUpdate = var6;
   }

   public String getUsername() {
      return this.username;
   }

   public String getType() {
      return this.type;
   }

   public String getText() {
      return this.text;
   }

   public String getIssuedBy() {
      return this.issuedBy;
   }

   public int getAmount() {
      return this.amount;
   }

   public void setAmount(int var1) {
      this.amount = var1;
   }

   public String getLastUpdate() {
      return this.lastUpdate;
   }
}
