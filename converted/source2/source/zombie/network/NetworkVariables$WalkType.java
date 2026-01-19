package zombie.network;

public enum NetworkVariables$WalkType {
   WT1("1"),
   WT2("2"),
   WT3("3"),
   WT4("4"),
   WT5("5"),
   WTSprint1("sprint1"),
   WTSprint2("sprint2"),
   WTSprint3("sprint3"),
   WTSprint4("sprint4"),
   WTSprint5("sprint5"),
   WTSlow1("slow1"),
   WTSlow2("slow2"),
   WTSlow3("slow3");

   private final String walkType;

   private NetworkVariables$WalkType(String var3) {
      this.walkType = var3;
   }

   @Override
   public String toString() {
      return this.walkType;
   }

   public static NetworkVariables$WalkType fromString(String var0) {
      for (NetworkVariables$WalkType var4 : values()) {
         if (var4.walkType.equalsIgnoreCase(var0)) {
            return var4;
         }
      }

      return WT1;
   }

   public static NetworkVariables$WalkType fromByte(byte var0) {
      for (NetworkVariables$WalkType var4 : values()) {
         if (var4.ordinal() == var0) {
            return var4;
         }
      }

      return WT1;
   }
}
