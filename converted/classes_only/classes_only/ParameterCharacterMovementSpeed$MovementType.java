package zombie.audio.parameters;

public enum ParameterCharacterMovementSpeed$MovementType {
   SneakWalk(0),
   SneakRun(1),
   Strafe(2),
   Walk(3),
   Run(4),
   Sprint(5);

   public final int label;

   private ParameterCharacterMovementSpeed$MovementType(int var3) {
      this.label = var3;
   }
}
