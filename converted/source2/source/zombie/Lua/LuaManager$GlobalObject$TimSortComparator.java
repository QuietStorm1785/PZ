package zombie.Lua;

import java.util.Comparator;
import java.util.Objects;

final class LuaManager$GlobalObject$TimSortComparator implements Comparator<Object> {
   Object comp;

   private LuaManager$GlobalObject$TimSortComparator() {
   }

   @Override
   public int compare(Object var1, Object var2) {
      if (Objects.equals(var1, var2)) {
         return 0;
      } else {
         Boolean var3 = LuaManager.thread.pcallBoolean(this.comp, var1, var2);
         return var3 == Boolean.TRUE ? -1 : 1;
      }
   }
}
