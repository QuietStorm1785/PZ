package zombie.world.logger;

import java.io.FileWriter;
import java.io.IOException;
import zombie.world.logger.Log.BaseLog;

public class Log$RegisterObject extends BaseLog {
   protected final String objectName;
   protected final int ID;

   public Log$RegisterObject(String var1, int var2) {
      this.objectName = var1;
      this.ID = var2;
   }

   public void saveAsText(FileWriter var1, String var2) throws IOException {
      var1.write(var2 + "{ type = \"reg_obj\", id = " + this.ID + ", obj = \"" + this.objectName + "\" }" + System.lineSeparator());
   }
}
