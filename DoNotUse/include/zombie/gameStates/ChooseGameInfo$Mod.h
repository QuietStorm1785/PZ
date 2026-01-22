#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Core.h"
#include "zombie/core/GameVersion.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/core/znet/SteamWorkshop.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/gameStates/ChooseGameInfo/PackFile.h"
#include "zombie/gameStates/ChooseGameInfo/TileDef.h"
#include "zombie/util/StringUtils.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace gameStates {


class ChooseGameInfo {
public:
    std::string dir;
    const File baseFile;
    const File mediaFile;
    const File actionGroupsFile;
    const File animSetsFile;
    const File animsXFile;
   private const std::vector<std::string> posters = std::make_unique<std::vector<>>();
    Texture tex;
   private std::vector<std::string> require;
    std::string name = "Unnamed Mod";
    std::string desc = "";
    std::string id;
    std::string url;
    std::string workshopID;
    bool bAvailableDone = false;
    bool available = true;
    GameVersion versionMin;
    GameVersion versionMax;
   private const std::vector<PackFile> packs = std::make_unique<std::vector<>>();
   private const std::vector<TileDef> tileDefs = std::make_unique<std::vector<>>();
    bool bRead = false;
    bool bValid = false;

   public ChooseGameInfo$Mod(std::string var1) {
      this.dir = var1;
    File var2 = std::make_shared<File>(var1).getAbsoluteFile();

      try {
         var2 = var2.getCanonicalFile();
      } catch (Exception var4) {
         ExceptionLogger.logException(var4);
      }

      this.baseFile = var2;
      this.mediaFile = std::make_shared<File>(var2, "media");
      this.actionGroupsFile = std::make_shared<File>(this.mediaFile, "actiongroups");
      this.animSetsFile = std::make_shared<File>(this.mediaFile, "AnimSets");
      this.animsXFile = std::make_shared<File>(this.mediaFile, "anims_X");
    File var3 = var2.getParentFile();
      if (var3 != nullptr) {
         var3 = var3.getParentFile();
         if (var3 != nullptr) {
            this.workshopID = SteamWorkshop.instance.getIDFromItemInstallFolder(var3.getAbsolutePath());
         }
      }
   }

    Texture getTexture() {
      if (this.tex == nullptr) {
    std::string var1 = this.posters.empty() ? nullptr : this.posters.get(0);
         if (!StringUtils.isNullOrWhitespace(var1)) {
            this.tex = Texture.getSharedTexture(var1);
         }

         if (this.tex == nullptr || this.tex.isFailure()) {
            if (Core.bDebug && this.tex == nullptr) {
               DebugLog.Mod.println("failed to load poster " + (var1 == nullptr ? this.id : var1));
            }

            this.tex = Texture.getWhite();
         }
      }

      return this.tex;
   }

    void setTexture(Texture var1) {
      this.tex = var1;
   }

    int getPosterCount() {
      return this.posters.size();
   }

    std::string getPoster(int var1) {
      return var1 >= 0 && var1 < this.posters.size() ? this.posters.get(var1) : nullptr;
   }

    std::string getName() {
      return this.name;
   }

    void setName(const std::string& var1) {
      this.name = var1;
   }

    std::string getDir() {
      return this.dir;
   }

    std::string getDescription() {
      return this.desc;
   }

   public std::vector<std::string> getRequire() {
      return this.require;
   }

    void setRequire(std::vector<std::string> var1) {
      this.require = var1;
   }

    std::string getId() {
      return this.id;
   }

    void setId(const std::string& var1) {
      this.id = var1;
   }

    bool isAvailable() {
      if (this.bAvailableDone) {
         return this.available;
      } else {
         this.bAvailableDone = true;
         if (!this.isAvailableSelf()) {
            this.available = false;
    return false;
         } else {
            ChooseGameInfo.tempStrings.clear();
            ChooseGameInfo.tempStrings.push_back(this.getId());
            if (!this.isAvailableRequired(ChooseGameInfo.tempStrings)) {
               this.available = false;
    return false;
            } else {
               this.available = true;
    return true;
            }
         }
      }
   }

    bool isAvailableSelf() {
    GameVersion var1 = Core.getInstance().getGameVersion();
      return this.versionMin != nullptr && this.versionMin.isGreaterThan(var1) ? false : this.versionMax == nullptr || !this.versionMax.isLessThan(var1);
   }

    bool isAvailableRequired(std::vector<std::string> var1) {
      if (this.require != nullptr && !this.require.empty()) {
         for (int var2 = 0; var2 < this.require.size(); var2++) {
    std::string var3 = this.require.get(var2).trim();
            if (!var1.contains(var3)) {
               var1.push_back(var3);
               ChooseGameInfo$Mod var4 = ChooseGameInfo.getModDetails(var3);
               if (var4 == nullptr) {
    return false;
               }

               if (!var4.isAvailableSelf()) {
    return false;
               }

               if (!var4.isAvailableRequired(var1)) {
    return false;
               }
            }
         }

    return true;
      } else {
    return true;
      }
   }

    void setAvailable(bool var1) {
   }

    std::string getUrl() {
      return this.url == nullptr ? "" : this.url;
   }

    void setUrl(const std::string& var1) {
      if (var1.startsWith("http://theindiestone.com")
         || var1.startsWith("http://www.theindiestone.com")
         || var1.startsWith("http://pz-mods.net")
         || var1.startsWith("http://www.pz-mods.net")) {
         this.url = var1;
      }
   }

    GameVersion getVersionMin() {
      return this.versionMin;
   }

    GameVersion getVersionMax() {
      return this.versionMax;
   }

    void addPack(const std::string& var1, int var2) {
      this.packs.push_back(std::make_shared<PackFile>(var1, var2));
   }

    void addTileDef(const std::string& var1, int var2) {
      this.tileDefs.push_back(std::make_shared<TileDef>(var1, var2));
   }

   public std::vector<PackFile> getPacks() {
      return this.packs;
   }

   public std::vector<TileDef> getTileDefs() {
      return this.tileDefs;
   }

    std::string getWorkshopID() {
      return this.workshopID;
   }
}
} // namespace gameStates
} // namespace zombie
