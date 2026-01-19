package zombie;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.nio.file.DirectoryStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import zombie.MapGroups.MapDirectory;
import zombie.MapGroups.MapGroup;
import zombie.core.Core;
import zombie.core.logger.ExceptionLogger;
import zombie.debug.DebugLog;
import zombie.gameStates.ChooseGameInfo;
import zombie.gameStates.ChooseGameInfo.Mod;
import zombie.iso.IsoWorld;
import zombie.modding.ActiveMods;

public final class MapGroups {
   private final ArrayList<MapGroup> groups = new ArrayList<>();
   private final ArrayList<MapDirectory> realDirectories = new ArrayList<>();

   private static ArrayList<String> getVanillaMapDirectories(boolean var0) {
      ArrayList var1 = new ArrayList();
      File var2 = ZomboidFileSystem.instance.getMediaFile("maps");
      String[] var3 = var2.list();
      if (var3 != null) {
         for (int var4 = 0; var4 < var3.length; var4++) {
            String var5 = var3[var4];
            if (var5.equalsIgnoreCase("challengemaps")) {
               if (var0) {
                  try (DirectoryStream var6 = Files.newDirectoryStream(
                        Paths.get(var2.getPath(), var5), var0x -> Files.isDirectory(var0x) && Files.exists(var0x.resolve("map.info"))
                     )) {
                     for (Path var8 : var6) {
                        var1.add(var5 + "/" + var8.getFileName().toString());
                     }
                  } catch (Exception var11) {
                  }
               }
            } else {
               var1.add(var5);
            }
         }
      }

      return var1;
   }

   public static String addMissingVanillaDirectories(String var0) {
      ArrayList var1 = getVanillaMapDirectories(false);
      boolean var2 = false;
      String[] var3 = var0.split(";");

      for (String var7 : var3) {
         var7 = var7.trim();
         if (!var7.isEmpty() && var1.contains(var7)) {
            var2 = true;
            break;
         }
      }

      if (!var2) {
         return var0;
      } else {
         ArrayList var9 = new ArrayList();

         for (String var8 : var3) {
            var8 = var8.trim();
            if (!var8.isEmpty()) {
               var9.add(var8);
            }
         }

         for (String var14 : var1) {
            if (!var9.contains(var14)) {
               var9.add(var14);
            }
         }

         String var12 = "";

         for (String var18 : var9) {
            if (!var12.isEmpty()) {
               var12 = var12 + ";";
            }

            var12 = var12 + var18;
         }

         return var12;
      }
   }

   public void createGroups() {
      this.createGroups(ActiveMods.getById("currentGame"), true);
   }

   public void createGroups(ActiveMods var1, boolean var2) {
      this.createGroups(var1, var2, false);
   }

   public void createGroups(ActiveMods var1, boolean var2, boolean var3) {
      this.groups.clear();
      this.realDirectories.clear();

      for (String var5 : var1.getMods()) {
         Mod var6 = ChooseGameInfo.getAvailableModDetails(var5);
         if (var6 != null) {
            File var7 = new File(var6.getDir() + "/media/maps/");
            if (var7.exists()) {
               String[] var8 = var7.list();
               if (var8 != null) {
                  for (int var9 = 0; var9 < var8.length; var9++) {
                     String var10 = var8[var9];
                     if (var10.equalsIgnoreCase("challengemaps")) {
                        if (var3) {
                        }
                     } else {
                        this.handleMapDirectory(var10, var6.getDir() + "/media/maps/" + var10);
                     }
                  }
               }
            }
         }
      }

      if (var2) {
         ArrayList var11 = getVanillaMapDirectories(var3);
         String var16 = ZomboidFileSystem.instance.getMediaPath("maps");

         for (String var24 : var11) {
            this.handleMapDirectory(var24, var16 + File.separator + var24);
         }
      }

      for (MapDirectory var17 : this.realDirectories) {
         ArrayList var22 = new ArrayList();
         this.getDirsRecursively(var17, var22);
         MapGroup var25 = this.findGroupWithAnyOfTheseDirectories(var22);
         if (var25 == null) {
            var25 = new MapGroup(this);
            this.groups.add(var25);
         }

         for (MapDirectory var29 : var22) {
            if (!var25.hasDirectory(var29.name)) {
               var25.addDirectory(var29);
            }
         }
      }

      for (MapGroup var18 : this.groups) {
         var18.setPriority();
      }

      for (MapGroup var19 : this.groups) {
         var19.setOrder(var1);
      }

      if (Core.bDebug) {
         int var15 = 1;

         for (MapGroup var23 : this.groups) {
            DebugLog.log("MapGroup " + var15 + "/" + this.groups.size());

            for (MapDirectory var28 : var23.directories) {
               DebugLog.log("  " + var28.name);
            }

            var15++;
         }

         DebugLog.log("-----");
      }
   }

   private void getDirsRecursively(MapDirectory var1, ArrayList<MapDirectory> var2) {
      if (!var2.contains(var1)) {
         var2.add(var1);

         for (String var4 : var1.lotDirs) {
            for (MapDirectory var6 : this.realDirectories) {
               if (var6.name.equals(var4)) {
                  this.getDirsRecursively(var6, var2);
                  break;
               }
            }
         }
      }
   }

   public int getNumberOfGroups() {
      return this.groups.size();
   }

   public ArrayList<String> getMapDirectoriesInGroup(int var1) {
      if (var1 >= 0 && var1 < this.groups.size()) {
         ArrayList var2 = new ArrayList();

         for (MapDirectory var4 : this.groups.get(var1).directories) {
            var2.add(var4.name);
         }

         return var2;
      } else {
         throw new RuntimeException("invalid MapGroups index " + var1);
      }
   }

   public void setWorld(int var1) {
      ArrayList var2 = this.getMapDirectoriesInGroup(var1);
      String var3 = "";

      for (int var4 = 0; var4 < var2.size(); var4++) {
         var3 = var3 + (String)var2.get(var4);
         if (var4 < var2.size() - 1) {
            var3 = var3 + ";";
         }
      }

      IsoWorld.instance.setMap(var3);
   }

   private void handleMapDirectory(String var1, String var2) {
      ArrayList var3 = this.getLotDirectories(var2);
      if (var3 != null) {
         MapDirectory var4 = new MapDirectory(this, var1, var2, var3);
         this.realDirectories.add(var4);
      }
   }

   private ArrayList<String> getLotDirectories(String var1) {
      File var2 = new File(var1 + "/map.info");
      if (!var2.exists()) {
         return null;
      } else {
         ArrayList var3 = new ArrayList();

         try {
            String var6;
            try (
               FileReader var4 = new FileReader(var2.getAbsolutePath());
               BufferedReader var5 = new BufferedReader(var4);
            ) {
               while ((var6 = var5.readLine()) != null) {
                  var6 = var6.trim();
                  if (var6.startsWith("lots=")) {
                     var3.add(var6.replace("lots=", "").trim());
                  }
               }
            }

            return var3;
         } catch (Exception var12) {
            ExceptionLogger.logException(var12);
            return null;
         }
      }
   }

   private MapGroup findGroupWithAnyOfTheseDirectories(ArrayList<MapDirectory> var1) {
      for (MapGroup var3 : this.groups) {
         if (var3.hasAnyOfTheseDirectories(var1)) {
            return var3;
         }
      }

      return null;
   }

   public ArrayList<String> getAllMapsInOrder() {
      ArrayList var1 = new ArrayList();

      for (MapGroup var3 : this.groups) {
         for (MapDirectory var5 : var3.directories) {
            var1.add(var5.name);
         }
      }

      return var1;
   }

   public boolean checkMapConflicts() {
      boolean var1 = false;

      for (MapGroup var3 : this.groups) {
         var1 |= var3.checkMapConflicts();
      }

      return var1;
   }

   public ArrayList<String> getMapConflicts(String var1) {
      for (MapGroup var3 : this.groups) {
         MapDirectory var4 = var3.getDirectoryByName(var1);
         if (var4 != null) {
            ArrayList var5 = new ArrayList();
            var5.addAll(var4.conflicts);
            return var5;
         }
      }

      return null;
   }
}
