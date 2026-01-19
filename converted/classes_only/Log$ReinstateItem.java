package zombie.world.logger;

import java.io.FileWriter;
import java.io.IOException;
import zombie.world.ItemInfo;
import zombie.world.logger.Log.BaseItemLog;

public class Log$ReinstateItem extends BaseItemLog {
   public Log$ReinstateItem(ItemInfo var1) {
      super(var1);
   }

   public void saveAsText(FileWriter var1, String var2) throws IOException {
      var1.write(var2 + "{ type = \"reinstate_item\", " + this.getItemString() + " }" + System.lineSeparator());
   }
}
