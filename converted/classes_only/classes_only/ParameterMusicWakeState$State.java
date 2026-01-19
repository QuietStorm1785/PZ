package zombie.audio.parameters;

public enum ParameterMusicWakeState$State {
   Awake(0),
   Sleeping(1),
   WakeNormal(2),
   WakeNightmare(3),
   WakeZombies(4);

   final int label;

   private ParameterMusicWakeState$State(int var3) {
      this.label = var3;
   }
}
