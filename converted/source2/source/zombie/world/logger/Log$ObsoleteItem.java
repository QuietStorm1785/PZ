package zombie.world.logger;

import java.io.FileWriter;
import java.io.IOException;
import zombie.world.ItemInfo;
import zombie.world.logger.Log.BaseItemLog;

public class Log$ObsoleteItem extends BaseItemLog {
   public Log$ObsoleteItem(ItemInfo var1) {
      super(var1);
   }

   public void saveAsText(FileWriter var1, String var2) throws IOException {
      var1.write(var2 + "{ type = \"obsolete_item\", " + this.getItemString() + " }" + System.lineSeparator());
   }
}
