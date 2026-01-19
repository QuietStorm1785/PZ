package zombie.iso;

import java.util.ArrayList;
import zombie.characters.IsoGameCharacter;
import zombie.iso.MultiStageBuilding.Stage;

public final class MultiStageBuilding {
   public static final ArrayList<Stage> stages = new ArrayList<>();

   public static ArrayList<Stage> getStages(IsoGameCharacter var0, IsoObject var1, boolean var2) {
      ArrayList var3 = new ArrayList();

      for (int var4 = 0; var4 < stages.size(); var4++) {
         Stage var5 = stages.get(var4);
         if (var5.canBeDone(var0, var1, var2) && !var3.contains(var5)) {
            var3.add(var5);
         }
      }

      return var3;
   }

   public static void addStage(Stage var0) {
      for (int var1 = 0; var1 < stages.size(); var1++) {
         if (stages.get(var1).ID.equals(var0.ID)) {
            return;
         }
      }

      stages.add(var0);
   }
}
