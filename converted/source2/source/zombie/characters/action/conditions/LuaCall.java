package zombie.characters.action.conditions;

import zombie.characters.action.ActionContext;
import zombie.characters.action.IActionCondition;

public final class LuaCall implements IActionCondition {
   public String getDescription() {
      return "<luaCheck>";
   }

   public boolean passes(ActionContext var1, int var2) {
      return false;
   }

   public IActionCondition clone() {
      return new LuaCall();
   }
}
