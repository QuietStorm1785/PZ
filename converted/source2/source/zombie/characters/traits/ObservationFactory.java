package zombie.characters.traits;

import java.util.HashMap;
import zombie.characters.traits.ObservationFactory.Observation;

public final class ObservationFactory {
   public static HashMap<String, Observation> ObservationMap = new HashMap<>();

   public static void init() {
   }

   public static void setMutualExclusive(String var0, String var1) {
      ObservationMap.get(var0).MutuallyExclusive.add(var1);
      ObservationMap.get(var1).MutuallyExclusive.add(var0);
   }

   public static void addObservation(String var0, String var1, String var2) {
      ObservationMap.put(var0, new Observation(var0, var1, var2));
   }

   public static Observation getObservation(String var0) {
      return ObservationMap.containsKey(var0) ? ObservationMap.get(var0) : null;
   }
}
