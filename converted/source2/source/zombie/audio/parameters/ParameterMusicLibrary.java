package zombie.audio.parameters;

import zombie.audio.FMODGlobalParameter;
import zombie.audio.parameters.ParameterMusicLibrary.Library;
import zombie.core.Core;

public final class ParameterMusicLibrary extends FMODGlobalParameter {
   public ParameterMusicLibrary() {
      super("MusicLibrary");
   }

   public float calculateCurrentValue() {
      return switch (Core.getInstance().getOptionMusicLibrary()) {
         case 2 -> Library.EarlyAccess.label;
         case 3 -> Library.Random.label;
         default -> Library.Official.label;
      };
   }
}
