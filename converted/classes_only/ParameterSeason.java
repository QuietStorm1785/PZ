package zombie.audio.parameters;

import zombie.audio.FMODGlobalParameter;
import zombie.iso.weather.ClimateManager;
import zombie.iso.weather.ClimateManager.DayInfo;

public final class ParameterSeason extends FMODGlobalParameter {
   public ParameterSeason() {
      super("Season");
   }

   public float calculateCurrentValue() {
      DayInfo var1 = ClimateManager.getInstance().getCurrentDay();
      if (var1 == null) {
         return 0.0F;
      } else {
         return switch (var1.season.getSeason()) {
            case 1 -> 0.0F;
            case 2, 3 -> 1.0F;
            case 4 -> 2.0F;
            case 5 -> 3.0F;
            default -> 1.0F;
         };
      }
   }
}
