package zombie.inventory;

import java.util.Objects;
import java.util.function.Predicate;
import se.krka.kahlua.vm.LuaClosure;
import zombie.Lua.LuaManager;

final class ItemContainer$EvalPredicate implements Predicate<InventoryItem> {
   LuaClosure functionObj;

   private ItemContainer$EvalPredicate() {
   }

   ItemContainer$EvalPredicate init(LuaClosure var1) {
      this.functionObj = Objects.requireNonNull(var1);
      return this;
   }

   public boolean test(InventoryItem var1) {
      return LuaManager.caller.protectedCallBoolean(LuaManager.thread, this.functionObj, var1) == Boolean.TRUE;
   }
}
