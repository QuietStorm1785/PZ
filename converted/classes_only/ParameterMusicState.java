package zombie.audio.parameters;

import zombie.audio.FMODGlobalParameter;
import zombie.audio.parameters.ParameterMusicState.State;

public final class ParameterMusicState extends FMODGlobalParameter {
   private State state = State.MainMenu;

   public ParameterMusicState() {
      super("MusicState");
   }

   public float calculateCurrentValue() {
      return this.state.label;
   }

   public void setState(State var1) {
      this.state = var1;
   }
}
