package zombie.network;

public enum NetworkVariables$ThumpType {
   TTNone(""),
   TTDoor("Door"),
   TTClaw("DoorClaw"),
   TTBang("DoorBang");

   private final String thumpType;

   private NetworkVariables$ThumpType(String var3) {
      this.thumpType = var3;
   }

   @Override
   public String toString() {
      return this.thumpType;
   }

   public static NetworkVariables$ThumpType fromString(String var0) {
      for (NetworkVariables$ThumpType var4 : values()) {
         if (var4.thumpType.equalsIgnoreCase(var0)) {
            return var4;
         }
      }

      return TTNone;
   }

   public static NetworkVariables$ThumpType fromByte(Byte var0) {
      for (NetworkVariables$ThumpType var4 : values()) {
         if (var4.ordinal() == var0) {
            return var4;
         }
      }

      return TTNone;
   }
}
