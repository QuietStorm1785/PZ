package zombie.Lua;

import gnu.trove.list.array.TShortArrayList;
import java.util.ArrayList;
import se.krka.kahlua.vm.LuaClosure;

final class MapObjects$Callback {
   final String spriteName;
   final ArrayList<LuaClosure> functions = new ArrayList<>();
   final TShortArrayList priority = new TShortArrayList();

   MapObjects$Callback(String var1) {
      this.spriteName = var1;
   }
}
