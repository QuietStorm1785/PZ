package zombie.audio.parameters;

import zombie.audio.FMODGlobalParameter;
import zombie.audio.parameters.ParameterMusicActionStyle.State;
import zombie.core.Core;

public final class ParameterMusicActionStyle extends FMODGlobalParameter {
   public ParameterMusicActionStyle() {
      super("MusicActionStyle");
   }

   public float calculateCurrentValue() {
      return Core.getInstance().getOptionMusicActionStyle() == 2 ? State.Legacy.label : State.Official.label;
   }
}
