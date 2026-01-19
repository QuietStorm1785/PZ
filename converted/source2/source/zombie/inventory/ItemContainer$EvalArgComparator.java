package zombie.inventory;

import java.util.Comparator;
import java.util.Objects;
import se.krka.kahlua.integration.LuaReturn;
import se.krka.kahlua.vm.LuaClosure;
import zombie.Lua.LuaManager;

final class ItemContainer$EvalArgComparator implements Comparator<InventoryItem> {
   LuaClosure functionObj;
   Object arg;

   private ItemContainer$EvalArgComparator() {
   }

   ItemContainer$EvalArgComparator init(LuaClosure var1, Object var2) {
      this.functionObj = Objects.requireNonNull(var1);
      this.arg = var2;
      return this;
   }

   public int compare(InventoryItem var1, InventoryItem var2) {
      LuaReturn var3 = LuaManager.caller.protectedCall(LuaManager.thread, this.functionObj, new Object[]{var1, var2, this.arg});
      if (var3.isSuccess() && !var3.isEmpty() && var3.getFirst() instanceof Double) {
         double var4 = (Double)var3.getFirst();
         return Double.compare(var4, 0.0);
      } else {
         return 0;
      }
   }
}
