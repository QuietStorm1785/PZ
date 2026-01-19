package zombie.inventory;

import java.util.Comparator;
import java.util.Objects;
import se.krka.kahlua.integration.LuaReturn;
import se.krka.kahlua.vm.LuaClosure;
import zombie.Lua.LuaManager;

final class ItemContainer$EvalComparator implements Comparator<InventoryItem> {
   LuaClosure functionObj;

   private ItemContainer$EvalComparator() {
   }

   ItemContainer$EvalComparator init(LuaClosure var1) {
      this.functionObj = Objects.requireNonNull(var1);
      return this;
   }

   public int compare(InventoryItem var1, InventoryItem var2) {
      LuaReturn var3 = LuaManager.caller.protectedCall(LuaManager.thread, this.functionObj, new Object[]{var1, var2});
      if (var3.isSuccess() && !var3.isEmpty() && var3.getFirst() instanceof Double) {
         double var4 = (Double)var3.getFirst();
         return Double.compare(var4, 0.0);
      } else {
         return 0;
      }
   }
}
