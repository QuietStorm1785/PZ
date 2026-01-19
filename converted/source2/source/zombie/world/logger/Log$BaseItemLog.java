package zombie.world.logger;

import java.io.FileWriter;
import java.io.IOException;
import zombie.world.ItemInfo;
import zombie.world.logger.Log.BaseLog;

public abstract class Log$BaseItemLog extends BaseLog {
   protected final ItemInfo itemInfo;

   public Log$BaseItemLog(ItemInfo var1) {
      this.itemInfo = var1;
   }

   abstract void saveAsText(FileWriter var1, String var2) throws IOException;

   protected String getItemString() {
      return "fulltype = \""
         + this.itemInfo.getFullType()
         + "\", registeryID = "
         + this.itemInfo.getRegistryID()
         + ", existsVanilla = "
         + this.itemInfo.isExistsAsVanilla()
         + ", isModded = "
         + this.itemInfo.isModded()
         + ", modID = \""
         + this.itemInfo.getModID()
         + "\", obsolete = "
         + this.itemInfo.isObsolete()
         + ", removed = "
         + this.itemInfo.isRemoved()
         + ", isLoaded = "
         + this.itemInfo.isLoaded();
   }
}
