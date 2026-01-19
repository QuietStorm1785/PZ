package zombie.world.logger;

import java.io.FileWriter;
import java.io.IOException;
import zombie.world.ItemInfo;
import zombie.world.logger.Log.BaseItemLog;

public class Log$ModIDChangedItem extends BaseItemLog {
   protected final String oldModID;
   protected final String newModID;

   public Log$ModIDChangedItem(ItemInfo var1, String var2, String var3) {
      super(var1);
      this.oldModID = var2;
      this.newModID = var3;
   }

   public void saveAsText(FileWriter var1, String var2) throws IOException {
      var1.write(var2 + "{ type = \"modchange_item\", oldModID = \"" + this.oldModID + "\", " + this.getItemString() + " }" + System.lineSeparator());
   }
}
