package zombie.world.logger;

import java.io.FileWriter;
import java.io.IOException;
import zombie.world.logger.Log.BaseLog;

public class Log$Comment extends BaseLog {
   protected String txt;

   public Log$Comment(String var1) {
      this.ignoreSaveCheck = true;
      this.txt = var1;
   }

   public void saveAsText(FileWriter var1, String var2) throws IOException {
      var1.write(var2 + "-- " + this.txt + System.lineSeparator());
   }
}
