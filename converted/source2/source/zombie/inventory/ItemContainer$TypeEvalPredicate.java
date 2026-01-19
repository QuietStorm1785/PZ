package zombie.inventory;

import java.util.Objects;
import java.util.function.Predicate;
import se.krka.kahlua.vm.LuaClosure;
import zombie.Lua.LuaManager;

final class ItemContainer$TypeEvalPredicate implements Predicate<InventoryItem> {
   String type;
   LuaClosure functionObj;

   private ItemContainer$TypeEvalPredicate() {
   }

   ItemContainer$TypeEvalPredicate init(String var1, LuaClosure var2) {
      this.type = var1;
      this.functionObj = Objects.requireNonNull(var2);
      return this;
   }

   public boolean test(InventoryItem var1) {
      return ItemContainer.compareType(this.type, var1) && LuaManager.caller.protectedCallBoolean(LuaManager.thread, this.functionObj, var1) == Boolean.TRUE;
   }
}
