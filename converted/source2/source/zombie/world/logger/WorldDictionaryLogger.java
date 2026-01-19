package zombie.world.logger;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import zombie.ZomboidFileSystem;
import zombie.debug.DebugLog;
import zombie.network.GameClient;
import zombie.world.logger.Log.BaseLog;
import zombie.world.logger.Log.Comment;

public class WorldDictionaryLogger {
   private static final ArrayList<BaseLog> _logItems = new ArrayList<>();

   public static void reset() {
      _logItems.clear();
   }

   public static void startLogging() {
      reset();
   }

   public static void log(BaseLog var0) {
      if (!GameClient.bClient) {
         _logItems.add(var0);
      }
   }

   public static void log(String var0) {
      log(var0, true);
   }

   public static void log(String var0, boolean var1) {
      if (!GameClient.bClient) {
         if (var1) {
            DebugLog.log("WorldDictionary: " + var0);
         }

         _logItems.add(new Comment(var0));
      }
   }

   public static void saveLog(String var0) throws IOException {
      if (!GameClient.bClient) {
         boolean var1 = false;

         for (int var3 = 0; var3 < _logItems.size(); var3++) {
            BaseLog var2 = _logItems.get(var3);
            if (!var2.isIgnoreSaveCheck()) {
               var1 = true;
               break;
            }
         }

         if (var1) {
            File var13 = new File(ZomboidFileSystem.instance.getCurrentSaveDir() + File.separator);
            if (var13.exists() && var13.isDirectory()) {
               String var4 = ZomboidFileSystem.instance.getFileNameInCurrentSave(var0);
               File var5 = new File(var4);

               try (FileWriter var6 = new FileWriter(var5, true)) {
                  var6.write("log = log or {};" + System.lineSeparator());
                  var6.write("table.insert(log, {" + System.lineSeparator());

                  for (int var7 = 0; var7 < _logItems.size(); var7++) {
                     BaseLog var12 = _logItems.get(var7);
                     var12.saveAsText(var6, "\t");
                  }

                  var6.write("};" + System.lineSeparator());
               } catch (Exception var11) {
                  var11.printStackTrace();
                  throw new IOException("Error saving WorldDictionary log.");
               }
            }
         }
      }
   }
}
