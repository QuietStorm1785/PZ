package zombie.inventory;

import java.util.Objects;
import java.util.function.Predicate;
import se.krka.kahlua.vm.LuaClosure;
import zombie.Lua.LuaManager;

final class ItemContainer$TypeEvalArgPredicate implements Predicate<InventoryItem> {
   String type;
   LuaClosure functionObj;
   Object arg;

   private ItemContainer$TypeEvalArgPredicate() {
   }

   ItemContainer$TypeEvalArgPredicate init(String var1, LuaClosure var2, Object var3) {
      this.type = var1;
      this.functionObj = Objects.requireNonNull(var2);
      this.arg = var3;
      return this;
   }

   public boolean test(InventoryItem var1) {
      return ItemContainer.compareType(this.type, var1)
         && LuaManager.caller.protectedCallBoolean(LuaManager.thread, this.functionObj, var1, this.arg) == Boolean.TRUE;
   }
}
