package zombie.world.logger;

import java.io.FileWriter;
import java.io.IOException;

public abstract class Log$BaseLog {
   protected boolean ignoreSaveCheck = false;

   public boolean isIgnoreSaveCheck() {
      return this.ignoreSaveCheck;
   }

   abstract void saveAsText(FileWriter var1, String var2) throws IOException;
}
