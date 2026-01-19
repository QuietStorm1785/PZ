package zombie.inventory;

import java.util.Objects;
import java.util.function.Predicate;
import se.krka.kahlua.vm.LuaClosure;
import zombie.Lua.LuaManager;

final class ItemContainer$TagEvalPredicate implements Predicate<InventoryItem> {
   String tag;
   LuaClosure functionObj;

   private ItemContainer$TagEvalPredicate() {
   }

   ItemContainer$TagEvalPredicate init(String var1, LuaClosure var2) {
      this.tag = var1;
      this.functionObj = Objects.requireNonNull(var2);
      return this;
   }

   public boolean test(InventoryItem var1) {
      return var1.hasTag(this.tag) && LuaManager.caller.protectedCallBoolean(LuaManager.thread, this.functionObj, var1) == Boolean.TRUE;
   }
}
