package zombie.characters.BodyDamage;

import java.util.ArrayList;
import java.util.Arrays;
import se.krka.kahlua.j2se.KahluaTableImpl;

public final class Fitness$FitnessExercise {
   String type = null;
   Metabolics metabolics = null;
   ArrayList<String> stiffnessInc = null;
   float xpModifier = 1.0F;

   public Fitness$FitnessExercise(KahluaTableImpl var1) {
      this.type = var1.rawgetStr("type");
      this.metabolics = (Metabolics)var1.rawget("metabolics");
      this.stiffnessInc = new ArrayList<>(Arrays.asList(var1.rawgetStr("stiffness").split(",")));
      if (var1.rawgetFloat("xpMod") > 0.0F) {
         this.xpModifier = var1.rawgetFloat("xpMod");
      }
   }
}
