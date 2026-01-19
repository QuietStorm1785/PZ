package zombie.network;

public enum Userlog$UserlogType {
   AdminLog(0),
   Kicked(1),
   Banned(2),
   DupeItem(3),
   LuaChecksum(4),
   WarningPoint(5),
   UnauthorizedPacket(6),
   SuspiciousActivity(7);

   private final int index;

   private Userlog$UserlogType(int var3) {
      this.index = var3;
   }

   public int index() {
      return this.index;
   }

   public static Userlog$UserlogType fromIndex(int var0) {
      return Userlog$UserlogType.class.getEnumConstants()[var0];
   }

   public static Userlog$UserlogType FromString(String var0) {
      return valueOf(var0);
   }
}
