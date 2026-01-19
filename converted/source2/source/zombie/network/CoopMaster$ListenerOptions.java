package zombie.network;

public class CoopMaster$ListenerOptions {
   public String tag;
   public String cookie;
   public boolean autoRemove;

   public CoopMaster$ListenerOptions(CoopMaster var1, String var2, String var3, boolean var4) {
      this.this$0 = var1;
      this.tag = null;
      this.cookie = null;
      this.autoRemove = false;
      this.tag = var2;
      this.cookie = var3;
      this.autoRemove = var4;
   }

   public CoopMaster$ListenerOptions(CoopMaster var1, String var2, String var3) {
      this(var1, var2, var3, false);
   }

   public CoopMaster$ListenerOptions(CoopMaster var1, String var2) {
      this(var1, var2, null, false);
   }
}
