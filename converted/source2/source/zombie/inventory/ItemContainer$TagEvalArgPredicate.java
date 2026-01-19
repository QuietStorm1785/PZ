package zombie.inventory;

import java.util.Objects;
import java.util.function.Predicate;
import se.krka.kahlua.vm.LuaClosure;
import zombie.Lua.LuaManager;

final class ItemContainer$TagEvalArgPredicate implements Predicate<InventoryItem> {
   String tag;
   LuaClosure functionObj;
   Object arg;

   private ItemContainer$TagEvalArgPredicate() {
   }

   ItemContainer$TagEvalArgPredicate init(String var1, LuaClosure var2, Object var3) {
      this.tag = var1;
      this.functionObj = Objects.requireNonNull(var2);
      this.arg = var3;
      return this;
   }

   public boolean test(InventoryItem var1) {
      return var1.hasTag(this.tag) && LuaManager.caller.protectedCallBoolean(LuaManager.thread, this.functionObj, var1, this.arg) == Boolean.TRUE;
   }
}
