package zombie.world.logger;

import java.io.FileWriter;
import java.io.IOException;
import java.util.List;
import zombie.world.logger.Log.BaseLog;

public class Log$Info extends BaseLog {
   protected final List<String> mods;
   protected final String timeStamp;
   protected final String saveWorld;
   protected final int worldVersion;
   public boolean HasErrored = false;

   public Log$Info(String var1, String var2, int var3, List<String> var4) {
      this.ignoreSaveCheck = true;
      this.timeStamp = var1;
      this.saveWorld = var2;
      this.worldVersion = var3;
      this.mods = var4;
   }

   public void saveAsText(FileWriter var1, String var2) throws IOException {
      var1.write(var2 + "{" + System.lineSeparator());
      var1.write(var2 + "\ttype = \"info\"," + System.lineSeparator());
      var1.write(var2 + "\ttimeStamp = \"" + this.timeStamp + "\"," + System.lineSeparator());
      var1.write(var2 + "\tsaveWorld = \"" + this.saveWorld + "\"," + System.lineSeparator());
      var1.write(var2 + "\tworldVersion = " + this.worldVersion + "," + System.lineSeparator());
      var1.write(var2 + "\thasErrored = " + this.HasErrored + "," + System.lineSeparator());
      var1.write(var2 + "\titemMods = {" + System.lineSeparator());

      for (int var3 = 0; var3 < this.mods.size(); var3++) {
         var1.write(var2 + "\t\t\"" + this.mods.get(var3) + "\"," + System.lineSeparator());
      }

      var1.write(var2 + "\t}," + System.lineSeparator());
      var1.write(var2 + "}," + System.lineSeparator());
   }
}
