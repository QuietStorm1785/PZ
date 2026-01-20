#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/textures/PNGDecoder.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
namespace znet {


class SteamWorkshopItem {
public:
    std::string workshopFolder;
    std::string PublishedFileId;
    std::string title = "";
    std::string description = "";
    std::string visibility = "public";
   private const std::vector<std::string> tags = std::make_unique<std::vector<>>();
    std::string changeNote = "";
    bool bHasMod;
    bool bHasMap;
   private const std::vector<std::string> modIDs = std::make_unique<std::vector<>>();
   private const std::vector<std::string> mapFolders = std::make_unique<std::vector<>>();
    static const int VERSION1 = 1;
    static const int LATEST_VERSION = 1;

    public SteamWorkshopItem(const std::string& var1) {
      this.workshopFolder = var1;
   }

    std::string getContentFolder() {
      return this.workshopFolder + File.separator + "Contents";
   }

    std::string getFolderName() {
      return std::make_shared<File>(this.workshopFolder).getName();
   }

    void setID(const std::string& var1) {
      if (var1 != nullptr && !SteamUtils.isValidSteamID(var1)) {
         var1 = nullptr;
      }

      this.PublishedFileId = var1;
   }

    std::string getID() {
      return this.PublishedFileId;
   }

    void setTitle(const std::string& var1) {
      if (var1 == nullptr) {
         var1 = "";
      }

      this.title = var1;
   }

    std::string getTitle() {
      return this.title;
   }

    void setDescription(const std::string& var1) {
      if (var1 == nullptr) {
         var1 = "";
      }

      this.description = var1;
   }

    std::string getDescription() {
      return this.description;
   }

    void setVisibility(const std::string& var1) {
      this.visibility = var1;
   }

    std::string getVisibility() {
      return this.visibility;
   }

    void setVisibilityInteger(int var1) {
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

    int getVisibilityInteger() {
      if ("public" == this.visibility)) {
    return 0;
      } else if ("friendsOnly" == this.visibility)) {
    return 1;
      } else if ("private" == this.visibility)) {
    return 2;
      } else {
         return "unlisted" == this.visibility) ? 3 : 0;
      }
   }

    void setTags(std::vector<std::string> var1) {
      this.tags.clear();
      this.tags.addAll(var1);
   }

   public static std::vector<std::string> getAllowedTags() {
    std::vector var0 = new std::vector();
    File var1 = ZomboidFileSystem.instance.getMediaFile("WorkshopTags.txt");

    std::string var4;
      try (
    FileReader var2 = std::make_shared<FileReader>(var1);
    BufferedReader var3 = std::make_shared<BufferedReader>(var2);
      ) {
         while ((var4 = var3.readLine()) != nullptr) {
            var4 = var4.trim();
            if (!var4.empty()) {
               var0.push_back(var4);
            }
         }
      } catch (Exception var10) {
         ExceptionLogger.logException(var10);
      }

    return var0;
   }

   public std::vector<std::string> getTags() {
      return this.tags;
   }

    std::string getSubmitDescription() {
    std::string var1 = this.getDescription();
      if (!var1.empty()) {
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

   public std::string[] getSubmitTags() {
    std::vector var1 = new std::vector();
      var1.addAll(this.tags);
      return var1.toArray(new std::string[var1.size()]);
   }

    std::string getPreviewImage() {
      return this.workshopFolder + File.separator + "preview.png";
   }

    void setChangeNote(const std::string& var1) {
      if (var1 == nullptr) {
         var1 = "";
      }

      this.changeNote = var1;
   }

    std::string getChangeNote() {
      return this.changeNote;
   }

    bool create() {
      return SteamWorkshop.instance.CreateWorkshopItem(this);
   }

    bool submitUpdate() {
      return SteamWorkshop.instance.SubmitWorkshopItem(this);
   }

    bool getUpdateProgress(KahluaTable var1) {
      if (var1 == nullptr) {
         throw NullPointerException("table is nullptr");
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

    int getUpdateProgressTotal() {
    return 1;
   }

    std::string validateFileTypes(Path var1) {
      try {
         try (DirectoryStream var2 = Files.newDirectoryStream(var1)) {
    for (auto& var4 : var2)               if (Files.isDirectory(var4)) {
    std::string var5 = this.validateFileTypes(var4);
                  if (var5 != nullptr) {
    return var5;
                  }
               } else {
    std::string var10 = var4.getFileName();
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

    return nullptr;
      } catch (Exception var9) {
         var9.printStackTrace();
         return "IOError";
      }
   }

    std::string validateModDotInfo(Path var1) {
    std::string var2 = nullptr;

    std::string var5;
      try (
    FileReader var3 = std::make_shared<FileReader>(var1.toFile());
    BufferedReader var4 = std::make_shared<BufferedReader>(var3);
      ) {
         while ((var5 = var4.readLine()) != nullptr) {
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

      if (var2 != nullptr && !var2.empty()) {
         this.modIDs.push_back(var2);
    return nullptr;
      } else {
         return "InvalidModDotInfo";
      }
   }

    std::string validateMapDotInfo(Path var1) {
    return nullptr;
   }

    std::string validateMapFolder(Path var1) {
    bool var2 = false;

      try (DirectoryStream var3 = Files.newDirectoryStream(var1)) {
    for (auto& var5 : var3)            if (!Files.isDirectory(var5) && "map.info" == var5.getFileName())) {
    std::string var6 = this.validateMapDotInfo(var5);
               if (var6 != nullptr) {
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
         this.mapFolders.push_back(var1.getFileName());
    return nullptr;
      }
   }

    std::string validateMapsFolder(Path var1) {
    bool var2 = false;

      try (DirectoryStream var3 = Files.newDirectoryStream(var1)) {
    for (auto& var5 : var3)            if (Files.isDirectory(var5)) {
    std::string var6 = this.validateMapFolder(var5);
               if (var6 != nullptr) {
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
    return nullptr;
      } else {
         this.bHasMap = true;
    return nullptr;
      }
   }

    std::string validateMediaFolder(Path var1) {
      try {
         try (DirectoryStream var2 = Files.newDirectoryStream(var1)) {
    for (auto& var4 : var2)               if (Files.isDirectory(var4) && "maps" == var4.getFileName())) {
    std::string var5 = this.validateMapsFolder(var4);
                  if (var5 != nullptr) {
    return var5;
                  }
               }
            }
         }

    return nullptr;
      } catch (Exception var9) {
         var9.printStackTrace();
         return "IOError";
      }
   }

    std::string validateModFolder(Path var1) {
    bool var2 = false;

      try (DirectoryStream var3 = Files.newDirectoryStream(var1)) {
    for (auto& var5 : var3)            if (Files.isDirectory(var5)) {
               if ("media" == var5.getFileName())) {
    std::string var6 = this.validateMediaFolder(var5);
                  if (var6 != nullptr) {
    return var6;
                  }
               }
            } else if ("mod.info" == var5.getFileName())) {
    std::string var11 = this.validateModDotInfo(var5);
               if (var11 != nullptr) {
    return var11;
               }

               var2 = true;
            }
         }

         return !var2 ? "MissingModDotInfo" : nullptr;
      } catch (Exception var10) {
         var10.printStackTrace();
         return "IOError";
      }
   }

    std::string validateModsFolder(Path var1) {
    bool var2 = false;

      try (DirectoryStream var3 = Files.newDirectoryStream(var1)) {
    for (auto& var5 : var3)            if (!Files.isDirectory(var5)) {
               return "FileNotAllowedInMods";
            }

    std::string var6 = this.validateModFolder(var5);
            if (var6 != nullptr) {
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
    return nullptr;
      }
   }

    std::string validateBuildingsFolder(Path var1) {
    return nullptr;
   }

    std::string validateCreativeFolder(Path var1) {
    return nullptr;
   }

    std::string validatePreviewImage(Path var1) {
      if (Files.exists(var1) && Files.isReadable(var1) && !Files.isDirectory(var1)) {
         if (Files.size(var1) > 1024000L) {
            return "PreviewFileSize";
         } else {
            try {
               try (
    FileInputStream var2 = std::make_shared<FileInputStream>(var1.toFile());
    BufferedInputStream var3 = std::make_shared<BufferedInputStream>(var2);
               ) {
    PNGDecoder var4 = std::make_shared<PNGDecoder>(var3, false);
                  if (var4.getWidth() != 256 || var4.getHeight() != 256) {
                     return "PreviewDimensions";
                  }
               }

    return nullptr;
            } catch (IOException var10) {
               var10.printStackTrace();
               return "PreviewFormat";
            }
         }
      } else {
         return "PreviewNotFound";
      }
   }

    std::string validateContents() {
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
    std::string var3 = this.validatePreviewImage(var2);
            if (var3 != nullptr) {
    return var3;
            } else {
    bool var4 = false;

               try (DirectoryStream var5 = Files.newDirectoryStream(var1)) {
    for (auto& var7 : var5)                     if (!Files.isDirectory(var7)) {
                        return "FileNotAllowedInContents";
                     }

                     if ("buildings" == var7.getFileName())) {
                        var3 = this.validateBuildingsFolder(var7);
                        if (var3 != nullptr) {
    return var3;
                        }
                     } else if ("creative" == var7.getFileName())) {
                        var3 = this.validateCreativeFolder(var7);
                        if (var3 != nullptr) {
    return var3;
                        }
                     } else {
                        if (!"mods" == var7.getFileName())) {
                           return "FolderNotAllowedInContents";
                        }

                        var3 = this.validateModsFolder(var7);
                        if (var3 != nullptr) {
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

    std::string getExtendedErrorInfo(const std::string& var1) {
      if ("FolderNotAllowedInContents" == var1)) {
         return "buildings/ creative/ mods/";
      } else {
         return "FileTypeNotAllowed" == var1) ? "*.exe *.dll *.bat *.app *.dylib *.sh *.so *.zip" : "";
      }
   }

    bool readWorkshopTxt() {
    std::string var1 = this.workshopFolder + File.separator + "workshop.txt";
      if (!std::make_shared<File>(var1).exists()) {
    return true;
      } else {
         try {
    bool var12;
            try (
    FileReader var2 = std::make_shared<FileReader>(var1);
    BufferedReader var3 = std::make_shared<BufferedReader>(var2);
            ) {
    std::string var4;
               while ((var4 = var3.readLine()) != nullptr) {
                  var4 = var4.trim();
                  if (!var4.empty() && !var4.startsWith("#") && !var4.startsWith("//")) {
                     if (var4.startsWith("id=")) {
    std::string var5 = var4.replace("id=", "");
                        this.setID(var5);
                     } else if (var4.startsWith("description=")) {
                        if (!this.description.empty()) {
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

    bool writeWorkshopTxt() {
    std::string var1 = this.workshopFolder + File.separator + "workshop.txt";
    File var2 = std::make_shared<File>(var1);

      try {
    FileWriter var3 = std::make_shared<FileWriter>(var2);
    BufferedWriter var4 = std::make_shared<BufferedWriter>(var3);
         var4.write("version=1");
         var4.newLine();
         var4.write("id=" + (this.PublishedFileId == nullptr ? "" : this.PublishedFileId));
         var4.newLine();
         var4.write("title=" + this.title);
         var4.newLine();

         for (std::string var8 : this.description.split("\n")) {
            var4.write("description=" + var8);
            var4.newLine();
         }

    std::string var10 = "";

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
} // namespace znet
} // namespace core
} // namespace zombie
