package zombie.core.fonts;

import java.util.LinkedHashMap;
import java.util.Map.Entry;
import zombie.core.fonts.AngelCodeFont.DisplayList;

class AngelCodeFont$1 extends LinkedHashMap {
   AngelCodeFont$1(AngelCodeFont var1, int var2, float var3, boolean var4) {
      super(var2, var3, var4);
      this.this$0 = var1;
   }

   @Override
   protected boolean removeEldestEntry(Entry var1) {
      this.this$0.eldestDisplayList = (DisplayList)var1.getValue();
      this.this$0.eldestDisplayListID = this.this$0.eldestDisplayList.id;
      return false;
   }
}
