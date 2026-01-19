package zombie.world.logger;

import java.io.FileWriter;
import java.io.IOException;
import zombie.world.ItemInfo;
import zombie.world.logger.Log.BaseItemLog;

public class Log$RemovedItem extends BaseItemLog {
   protected final boolean isScriptMissing;

   public Log$RemovedItem(ItemInfo var1, boolean var2) {
      super(var1);
      this.isScriptMissing = var2;
   }

   public void saveAsText(FileWriter var1, String var2) throws IOException {
      var1.write(var2 + "{ type = \"removed_item\", scriptMissing = " + this.isScriptMissing + ", " + this.getItemString() + " }" + System.lineSeparator());
   }
}
