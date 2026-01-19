package zombie.inventory;

import java.util.Objects;
import java.util.function.Predicate;
import se.krka.kahlua.vm.LuaClosure;
import zombie.Lua.LuaManager;

final class ItemContainer$EvalArgPredicate implements Predicate<InventoryItem> {
   LuaClosure functionObj;
   Object arg;

   private ItemContainer$EvalArgPredicate() {
   }

   ItemContainer$EvalArgPredicate init(LuaClosure var1, Object var2) {
      this.functionObj = Objects.requireNonNull(var1);
      this.arg = var2;
      return this;
   }

   public boolean test(InventoryItem var1) {
      return LuaManager.caller.protectedCallBoolean(LuaManager.thread, this.functionObj, var1, this.arg) == Boolean.TRUE;
   }
}
