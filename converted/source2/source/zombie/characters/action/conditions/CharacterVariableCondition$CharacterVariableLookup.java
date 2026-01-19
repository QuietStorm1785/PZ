package zombie.characters.action.conditions;

import zombie.core.Core;
import zombie.core.skinnedmodel.advancedanimation.debug.AnimatorDebugMonitor;

class CharacterVariableCondition$CharacterVariableLookup {
   public String variableName;

   public CharacterVariableCondition$CharacterVariableLookup(String var1) {
      this.variableName = var1;
      if (Core.bDebug) {
         AnimatorDebugMonitor.registerVariable(var1);
      }
   }

   @Override
   public String toString() {
      return this.variableName;
   }
}
