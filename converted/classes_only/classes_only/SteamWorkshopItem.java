package zombie.core.znet;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.DirectoryStream;
import java.nio.file.FileSystems;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Arrays;
import se.krka.kahlua.vm.KahluaTable;
import zombie.ZomboidFileSystem;
import zombie.core.logger.ExceptionLogger;
import zombie.core.textures.PNGDecoder;

public class SteamWorkshopItem {
   private String workshopFolder;
   private String PublishedFileId;
   private String title = "";
   private String description = "";
   private String visibility = "public";
   private final ArrayList<String> tags = new ArrayList<>();
   private String changeNote = "";
   private boolean bHasMod;
   private boolean bHasMap;
   private final ArrayList<String> modIDs = new ArrayList<>();
   private final ArrayList<String> mapFolders = new ArrayList<>();
   private static final int VERSION1 = 1;
   private static final int LATEST_VERSION = 1;

   public SteamWorkshopItem(String var1) {
      this.workshopFolder = var1;
   }

   public String getContentFolder() {
      return this.workshopFolder + File.separator + "Contents";
   }

   public String getFolderName() {
      return new File(this.workshopFolder).getName();
   }

   public void setID(String var1) {
      if (var1 != null && !SteamUtils.isValidSteamID(var1)) {
         var1 = null;
      }

      this.PublishedFileId = var1;
   }

   public String getID() {
      return this.PublishedFileId;
   }

   public void setTitle(String var1) {
      if (var1 == null) {
         var1 = "";
      }

      this.title = var1;
   }

   public String getTitle() {
      return this.title;
   }

   public void setDescription(String var1) {
      if (var1 == null) {
         var1 = "";
      }

      this.description = var1;
   }

   public String getDescription() {
      return this.description;
   }

   public void setVisibility(String var1) {
      this.visibility = var1;
   }

   public String getVisibility() {
      return this.visibility;
   }

   public void setVisibilityInteger(int var1) {
      switch (var1) {
         case 0:
            this.visibility = "public";
            break;
         case 1:
            this.visibility = "friendsOnly";
            break;
         case 2:
            this.visibility = "private";
            break;
         case 3:
            this.visibility = "unlisted";
            break;
         default:
            this.visibility = "public";
      }
   }

   public int getVisibilityInteger() {
      if ("public".equals(this.visibility)) {
         return 0;
      } else if ("friendsOnly".equals(this.visibility)) {
         return 1;
      } else if ("private".equals(this.visibility)) {
         return 2;
      } else {
         return "unlisted".equals(this.visibility) ? 3 : 0;
      }
   }

   public void setTags(ArrayList<String> var1) {
      this.tags.clear();
      this.tags.addAll(var1);
   }

   public static ArrayList<String> getAllowedTags() {
      ArrayList var0 = new ArrayList();
      File var1 = ZomboidFileSystem.instance.getMediaFile("WorkshopTags.txt");

      String var4;
      try (
         FileReader var2 = new FileReader(var1);
         BufferedReader var3 = new BufferedReader(var2);
      ) {
         while ((var4 = var3.readLine()) != null) {
            var4 = var4.trim();
            if (!var4.isEmpty()) {
               var0.add(var4);
            }
         }
      } catch (Exception var10) {
         ExceptionLogger.logException(var10);
      }

      return var0;
   }

   public ArrayList<String> getTags() {
      return this.tags;
   }

   public String getSubmitDescription() {
      String var1 = this.getDescription();
      if (!var1.isEmpty()) {
         var1 = var1 + "\n\n";
      }

      var1 = var1 + "Workshop ID: " + this.getID();

      for (int var2 = 0; var2 < this.modIDs.size(); var2++) {
         var1 = var1 + "\nMod ID: " + this.modIDs.get(var2);
      }

      for (int var4 = 0; var4 < this.mapFolders.size(); var4++) {
         var1 = var1 + "\nMap Folder: " + this.mapFolders.get(var4);
      }

      return var1;
   }

   public String[] getSubmitTags() {
      ArrayList var1 = new ArrayList();
      var1.addAll(this.tags);
      return var1.toArray(new String[var1.size()]);
   }

   public String getPreviewImage() {
      return this.workshopFolder + File.separator + "preview.png";
   }

   public void setChangeNote(String var1) {
      if (var1 == null) {
         var1 = "";
      }

      this.changeNote = var1;
   }

   public String getChangeNote() {
      return this.changeNote;
   }

   public boolean create() {
      return SteamWorkshop.instance.CreateWorkshopItem(this);
   }

   public boolean submitUpdate() {
      return SteamWorkshop.instance.SubmitWorkshopItem(this);
   }

   public boolean getUpdateProgress(KahluaTable var1) {
      if (var1 == null) {
         throw new NullPointerException("table is null");
      } else {
         long[] var2 = new long[2];
         if (SteamWorkshop.instance.GetItemUpdateProgress(var2)) {
            System.out.println(var2[0] + "/" + var2[1]);
            var1.rawset("processed", (double)var2[0]);
            var1.rawset("total", (double)Math.max(var2[1], 1L));
            return true;
         } else {
            return false;
         }
      }
   }

   public int getUpdateProgressTotal() {
      return 1;
   }

   private String validateFileTypes(Path var1) {
      try {
         try (DirectoryStream var2 = Files.newDirectoryStream(var1)) {
            for (Path var4 : var2) {
               if (Files.isDirectory(var4)) {
                  String var5 = this.validateFileTypes(var4);
                  if (var5 != null) {
                     return var5;
                  }
               } else {
                  String var10 = var4.getFileName().toString();
                  if (!var10.equalsIgnoreCase("pyramid.zip")
                     && (
                        var10.endsWith(".exe")
                           || var10.endsWith(".dll")
                           || var10.endsWith(".bat")
                           || var10.endsWith(".app")
                           || var10.endsWith(".dylib")
                           || var10.endsWith(".sh")
                           || var10.endsWith(".so")
                           || var10.endsWith(".zip")
                     )) {
                     return "FileTypeNotAllowed";
                  }
               }
            }
         }

         return null;
      } catch (Exception var9) {
         var9.printStackTrace();
         return "IOError";
      }
   }

   private String validateModDotInfo(Path var1) {
      String var2 = null;

      String var5;
      try (
         FileReader var3 = new FileReader(var1.toFile());
         BufferedReader var4 = new BufferedReader(var3);
      ) {
         while ((var5 = var4.readLine()) != null) {
            if (var5.startsWith("id=")) {
               var2 = var5.replace("id=", "").trim();
               break;
            }
         }
      } catch (FileNotFoundException var11) {
         return "MissingModDotInfo";
      } catch (IOException var12) {
         var12.printStackTrace();
         return "IOError";
      }

      if (var2 != null && !var2.isEmpty()) {
         this.modIDs.add(var2);
         return null;
      } else {
         return "InvalidModDotInfo";
      }
   }

   private String validateMapDotInfo(Path var1) {
      return null;
   }

   private String validateMapFolder(Path var1) {
      boolean var2 = false;

      try (DirectoryStream var3 = Files.newDirectoryStream(var1)) {
         for (Path var5 : var3) {
            if (!Files.isDirectory(var5) && "map.info".equals(var5.getFileName().toString())) {
               String var6 = this.validateMapDotInfo(var5);
               if (var6 != null) {
                  return var6;
               }

               var2 = true;
            }
         }
      } catch (Exception var10) {
         var10.printStackTrace();
         return "IOError";
      }

      if (!var2) {
         return "MissingMapDotInfo";
      } else {
         this.mapFolders.add(var1.getFileName().toString());
         return null;
      }
   }

   private String validateMapsFolder(Path var1) {
      boolean var2 = false;

      try (DirectoryStream var3 = Files.newDirectoryStream(var1)) {
         for (Path var5 : var3) {
            if (Files.isDirectory(var5)) {
               String var6 = this.validateMapFolder(var5);
               if (var6 != null) {
                  return var6;
               }

               var2 = true;
            }
         }
      } catch (Exception var10) {
         var10.printStackTrace();
         return "IOError";
      }

      if (!var2) {
         return null;
      } else {
         this.bHasMap = true;
         return null;
      }
   }

   private String validateMediaFolder(Path var1) {
      try {
         try (DirectoryStream var2 = Files.newDirectoryStream(var1)) {
            for (Path var4 : var2) {
               if (Files.isDirectory(var4) && "maps".equals(var4.getFileName().toString())) {
                  String var5 = this.validateMapsFolder(var4);
                  if (var5 != null) {
                     return var5;
                  }
               }
            }
         }

         return null;
      } catch (Exception var9) {
         var9.printStackTrace();
         return "IOError";
      }
   }

   private String validateModFolder(Path var1) {
      boolean var2 = false;

      try (DirectoryStream var3 = Files.newDirectoryStream(var1)) {
         for (Path var5 : var3) {
            if (Files.isDirectory(var5)) {
               if ("media".equals(var5.getFileName().toString())) {
                  String var6 = this.validateMediaFolder(var5);
                  if (var6 != null) {
                     return var6;
                  }
               }
            } else if ("mod.info".equals(var5.getFileName().toString())) {
               String var11 = this.validateModDotInfo(var5);
               if (var11 != null) {
                  return var11;
               }

               var2 = true;
            }
         }

         return !var2 ? "MissingModDotInfo" : null;
      } catch (Exception var10) {
         var10.printStackTrace();
         return "IOError";
      }
   }

   private String validateModsFolder(Path var1) {
      boolean var2 = false;

      try (DirectoryStream var3 = Files.newDirectoryStream(var1)) {
         for (Path var5 : var3) {
            if (!Files.isDirectory(var5)) {
               return "FileNotAllowedInMods";
            }

            String var6 = this.validateModFolder(var5);
            if (var6 != null) {
               return var6;
            }

            var2 = true;
         }
      } catch (Exception var10) {
         var10.printStackTrace();
         return "IOError";
      }

      if (!var2) {
         return "EmptyModsFolder";
      } else {
         this.bHasMod = true;
         return null;
      }
   }

   private String validateBuildingsFolder(Path var1) {
      return null;
   }

   private String validateCreativeFolder(Path var1) {
      return null;
   }

   public String validatePreviewImage(Path var1) throws IOException {
      if (Files.exists(var1) && Files.isReadable(var1) && !Files.isDirectory(var1)) {
         if (Files.size(var1) > 1024000L) {
            return "PreviewFileSize";
         } else {
            try {
               try (
                  FileInputStream var2 = new FileInputStream(var1.toFile());
                  BufferedInputStream var3 = new BufferedInputStream(var2);
               ) {
                  PNGDecoder var4 = new PNGDecoder(var3, false);
                  if (var4.getWidth() != 256 || var4.getHeight() != 256) {
                     return "PreviewDimensions";
                  }
               }

               return null;
            } catch (IOException var10) {
               var10.printStackTrace();
               return "PreviewFormat";
            }
         }
      } else {
         return "PreviewNotFound";
      }
   }

   public String validateContents() {
      this.bHasMod = false;
      this.bHasMap = false;
      this.modIDs.clear();
      this.mapFolders.clear();

      try {
         Path var1 = FileSystems.getDefault().getPath(this.getContentFolder());
         if (!Files.isDirectory(var1)) {
            return "MissingContents";
         } else {
            Path var2 = FileSystems.getDefault().getPath(this.getPreviewImage());
            String var3 = this.validatePreviewImage(var2);
            if (var3 != null) {
               return var3;
            } else {
               boolean var4 = false;

               try (DirectoryStream var5 = Files.newDirectoryStream(var1)) {
                  for (Path var7 : var5) {
                     if (!Files.isDirectory(var7)) {
                        return "FileNotAllowedInContents";
                     }

                     if ("buildings".equals(var7.getFileName().toString())) {
                        var3 = this.validateBuildingsFolder(var7);
                        if (var3 != null) {
                           return var3;
                        }
                     } else if ("creative".equals(var7.getFileName().toString())) {
                        var3 = this.validateCreativeFolder(var7);
                        if (var3 != null) {
                           return var3;
                        }
                     } else {
                        if (!"mods".equals(var7.getFileName().toString())) {
                           return "FolderNotAllowedInContents";
                        }

                        var3 = this.validateModsFolder(var7);
                        if (var3 != null) {
                           return var3;
                        }
                     }

                     var4 = true;
                  }

                  return !var4 ? "EmptyContentsFolder" : this.validateFileTypes(var1);
               } catch (Exception var11) {
                  var11.printStackTrace();
                  return "IOError";
               }
            }
         }
      } catch (IOException var12) {
         var12.printStackTrace();
         return "IOError";
      }
   }

   public String getExtendedErrorInfo(String var1) {
      if ("FolderNotAllowedInContents".equals(var1)) {
         return "buildings/ creative/ mods/";
      } else {
         return "FileTypeNotAllowed".equals(var1) ? "*.exe *.dll *.bat *.app *.dylib *.sh *.so *.zip" : "";
      }
   }

   public boolean readWorkshopTxt() {
      String var1 = this.workshopFolder + File.separator + "workshop.txt";
      if (!new File(var1).exists()) {
         return true;
      } else {
         try {
            boolean var12;
            try (
               FileReader var2 = new FileReader(var1);
               BufferedReader var3 = new BufferedReader(var2);
            ) {
               String var4;
               while ((var4 = var3.readLine()) != null) {
                  var4 = var4.trim();
                  if (!var4.isEmpty() && !var4.startsWith("#") && !var4.startsWith("//")) {
                     if (var4.startsWith("id=")) {
                        String var5 = var4.replace("id=", "");
                        this.setID(var5);
                     } else if (var4.startsWith("description=")) {
                        if (!this.description.isEmpty()) {
                           this.description = this.description + "\n";
                        }

                        this.description = this.description + var4.replace("description=", "");
                     } else if (var4.startsWith("tags=")) {
                        this.tags.addAll(Arrays.asList(var4.replace("tags=", "").split(";")));
                     } else if (var4.startsWith("title=")) {
                        this.title = var4.replace("title=", "");
                     } else if (!var4.startsWith("version=") && var4.startsWith("visibility=")) {
                        this.visibility = var4.replace("visibility=", "");
                     }
                  }
               }

               var12 = true;
            }

            return var12;
         } catch (IOException var10) {
            var10.printStackTrace();
            return false;
         }
      }
   }

   public boolean writeWorkshopTxt() {
      String var1 = this.workshopFolder + File.separator + "workshop.txt";
      File var2 = new File(var1);

      try {
         FileWriter var3 = new FileWriter(var2);
         BufferedWriter var4 = new BufferedWriter(var3);
         var4.write("version=1");
         var4.newLine();
         var4.write("id=" + (this.PublishedFileId == null ? "" : this.PublishedFileId));
         var4.newLine();
         var4.write("title=" + this.title);
         var4.newLine();

         for (String var8 : this.description.split("\n")) {
            var4.write("description=" + var8);
            var4.newLine();
         }

         String var10 = "";

         for (int var11 = 0; var11 < this.tags.size(); var11++) {
            var10 = var10 + this.tags.get(var11);
            if (var11 < this.tags.size() - 1) {
               var10 = var10 + ";";
            }
         }

         var4.write("tags=" + var10);
         var4.newLine();
         var4.write("visibility=" + this.visibility);
         var4.newLine();
         var4.close();
         return true;
      } catch (IOException var9) {
         var9.printStackTrace();
         return false;
      }
   }
}
