package zombie.network;

import java.io.File;
import java.nio.file.DirectoryStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import zombie.ZomboidFileSystem;
import zombie.core.logger.ExceptionLogger;
import zombie.network.ServerSettingsManager.1;

public class ServerSettingsManager {
   public static final ServerSettingsManager instance = new ServerSettingsManager();
   protected ArrayList<ServerSettings> settings = new ArrayList<>();
   protected ArrayList<String> suffixes = new ArrayList<>();

   public String getSettingsFolder() {
      return ZomboidFileSystem.instance.getCacheDir() + File.separator + "Server";
   }

   public String getNameInSettingsFolder(String var1) {
      return this.getSettingsFolder() + File.separator + var1;
   }

   public void readAllSettings() {
      this.settings.clear();
      File var1 = new File(this.getSettingsFolder());
      if (!var1.exists()) {
         var1.mkdirs();
      } else {
         1 var2 = new 1(this);

         try (DirectoryStream var3 = Files.newDirectoryStream(var1.toPath(), var2)) {
            for (Path var5 : var3) {
               ServerSettings var6 = new ServerSettings(var5.getFileName().toString().replace(".ini", ""));
               this.settings.add(var6);
            }
         } catch (Exception var9) {
            ExceptionLogger.logException(var9);
         }
      }
   }

   public int getSettingsCount() {
      return this.settings.size();
   }

   public ServerSettings getSettingsByIndex(int var1) {
      return var1 >= 0 && var1 < this.settings.size() ? this.settings.get(var1) : null;
   }

   public boolean isValidName(String var1) {
      if (var1 == null || var1.isEmpty()) {
         return false;
      } else {
         return var1.contains("/") || var1.contains("\\") || var1.contains(":") || var1.contains(";") || var1.contains("\"") || var1.contains(".")
            ? false
            : !var1.contains("_zombies");
      }
   }

   private boolean anyFilesExist(String var1) {
      this.getSuffixes();

      for (int var2 = 0; var2 < this.suffixes.size(); var2++) {
         File var3 = new File(this.getSettingsFolder() + File.separator + var1 + this.suffixes.get(var2));
         if (var3.exists()) {
            return true;
         }
      }

      return false;
   }

   public boolean isValidNewName(String var1) {
      return !this.isValidName(var1) ? false : !this.anyFilesExist(var1);
   }

   public ArrayList<String> getSuffixes() {
      if (this.suffixes.isEmpty()) {
         this.suffixes.add(".ini");
         this.suffixes.add("_SandboxVars.lua");
         this.suffixes.add("_spawnpoints.lua");
         this.suffixes.add("_spawnregions.lua");
         this.suffixes.add("_zombies.ini");
      }

      return this.suffixes;
   }
}
