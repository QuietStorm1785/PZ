package zombie.network;

public enum NetworkVariables$PredictionTypes {
   None,
   Moving,
   Static,
   Thump,
   Climb,
   Lunge,
   LungeHalf,
   Walk,
   WalkHalf,
   PathFind;

   public static NetworkVariables$PredictionTypes fromByte(byte var0) {
      for (NetworkVariables$PredictionTypes var4 : values()) {
         if (var4.ordinal() == var0) {
            return var4;
         }
      }

      return None;
   }
}
