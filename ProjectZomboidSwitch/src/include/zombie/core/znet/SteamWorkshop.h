#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/znet/SteamWorkshop/1.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/GameServer.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
namespace znet {


class SteamWorkshop {
public:
    static const SteamWorkshop instance = std::make_shared<SteamWorkshop>();
   private std::vector<SteamWorkshopItem> stagedItems = std::make_unique<std::vector<>>();
   private std::vector<ISteamWorkshopCallback> callbacks = std::make_unique<std::vector<>>();

    static void init() {
      if (SteamUtils.isSteamModeEnabled()) {
         instance.n_Init();
      }

      if (!GameServer.bServer) {
         instance.initWorkshopFolder();
      }
   }

    static void shutdown() {
      if (SteamUtils.isSteamModeEnabled()) {
         instance.n_Shutdown();
      }
   }

    void copyFile(File var1, File var2) {
      try (
    FileInputStream var3 = std::make_shared<FileInputStream>(var1);
    FileOutputStream var4 = std::make_shared<FileOutputStream>(var2);
      ) {
         var4.getChannel().transferFrom(var3.getChannel(), 0L, var1.length());
      } catch (IOException var11) {
         var11.printStackTrace();
      }
   }

    void copyFileOrFolder(File var1, File var2) {
      if (var1.isDirectory()) {
         if (!var2.mkdirs()) {
            return;
         }

         std::string[] var3 = var1.list();

         for (int var4 = 0; var4 < var3.length; var4++) {
            this.copyFileOrFolder(std::make_shared<File>(var1, var3[var4]), std::make_shared<File>(var2, var3[var4]));
         }
      } else {
         this.copyFile(var1, var2);
      }
   }

    void initWorkshopFolder() {
    File var1 = std::make_shared<File>(this.getWorkshopFolder());
      if (var1.exists() || var1.mkdirs()) {
    File var2 = std::make_shared<File>("Workshop" + File.separator + "ModTemplate");
    File var3 = std::make_shared<File>(this.getWorkshopFolder() + File.separator + "ModTemplate");
         if (var2.exists() && !var3.exists()) {
            this.copyFileOrFolder(var2, var3);
         }
      }
   }

   public std::vector<SteamWorkshopItem> loadStagedItems() {
      this.stagedItems.clear();

      for (std::string var2 : this.getStageFolders()) {
    SteamWorkshopItem var3 = std::make_shared<SteamWorkshopItem>(var2);
         var3.readWorkshopTxt();
         this.stagedItems.push_back(var3);
      }

      return this.stagedItems;
   }

    std::string getWorkshopFolder() {
      return ZomboidFileSystem.instance.getCacheDir() + File.separator + "Workshop";
   }

   public std::vector<std::string> getStageFolders() {
    std::vector var1 = new std::vector();
    Path var2 = FileSystems.getDefault().getPath(this.getWorkshopFolder());

      try {
         if (!Files.isDirectory(var2)) {
            Files.createDirectories(var2);
         }
      } catch (IOException var11) {
         var11.printStackTrace();
    return var1;
      }

    1 var3 = std::make_shared<1>(this);

      try (DirectoryStream var4 = Files.newDirectoryStream(var2, var3)) {
    for (auto& var6 : var4)    std::string var7 = var6.toAbsolutePath();
            var1.push_back(var7);
         }
      } catch (Exception var10) {
         var10.printStackTrace();
      }

    return var1;
   }

    bool CreateWorkshopItem(SteamWorkshopItem var1) {
      if (var1.getID() != nullptr) {
         throw RuntimeException("can't recreate an existing item");
      } else {
         return this.n_CreateItem();
      }
   }

    bool SubmitWorkshopItem(SteamWorkshopItem var1) {
      if (var1.getID() != nullptr && SteamUtils.isValidSteamID(var1.getID())) {
    long var2 = SteamUtils.convertStringToSteamID(var1.getID());
         if (!this.n_StartItemUpdate(var2)) {
    return false;
         } else if (!this.n_SetItemTitle(var1.getTitle())) {
    return false;
         } else if (!this.n_SetItemDescription(var1.getSubmitDescription())) {
    return false;
         } else {
    int var4 = var1.getVisibilityInteger();
            if ("Mod Template" == var1.getTitle())) {
               var4 = 2;
            }

            if (!this.n_SetItemVisibility(var4)) {
    return false;
            } else {
               if (!this.n_SetItemTags(var1.getSubmitTags())) {
               }

               if (!this.n_SetItemContent(var1.getContentFolder())) {
    return false;
               } else {
                  return !this.n_SetItemPreview(var1.getPreviewImage()) ? false : this.n_SubmitItemUpdate(var1.getChangeNote());
               }
            }
         }
      } else {
         throw RuntimeException("workshop ID is required");
      }
   }

    bool GetItemUpdateProgress(long[] var1) {
      return this.n_GetItemUpdateProgress(var1);
   }

   public std::string[] GetInstalledItemFolders() {
      return GameServer.bServer ? GameServer.WorkshopInstallFolders : this.n_GetInstalledItemFolders();
   }

    long GetItemState(long var1) {
      return this.n_GetItemState(var1);
   }

    std::string GetItemInstallFolder(long var1) {
      return this.n_GetItemInstallFolder(var1);
   }

    long GetItemInstallTimeStamp(long var1) {
      return this.n_GetItemInstallTimeStamp(var1);
   }

    bool SubscribeItem(long var1, ISteamWorkshopCallback var3) {
      if (!this.callbacks.contains(var3)) {
         this.callbacks.push_back(var3);
      }

      return this.n_SubscribeItem(var1);
   }

    bool DownloadItem(long var1, bool var3, ISteamWorkshopCallback var4) {
      if (!this.callbacks.contains(var4)) {
         this.callbacks.push_back(var4);
      }

      return this.n_DownloadItem(var1, var3);
   }

    bool GetItemDownloadInfo(long var1, long[] var3) {
      return this.n_GetItemDownloadInfo(var1, var3);
   }

    long CreateQueryUGCDetailsRequest(long[] var1, ISteamWorkshopCallback var2) {
      if (!this.callbacks.contains(var2)) {
         this.callbacks.push_back(var2);
      }

      return this.n_CreateQueryUGCDetailsRequest(var1);
   }

    SteamUGCDetails GetQueryUGCResult(long var1, int var3) {
      return this.n_GetQueryUGCResult(var1, var3);
   }

   public long[] GetQueryUGCChildren(long var1, int var3) {
      return this.n_GetQueryUGCChildren(var1, var3);
   }

    bool ReleaseQueryUGCRequest(long var1) {
      return this.n_ReleaseQueryUGCRequest(var1);
   }

    void RemoveCallback(ISteamWorkshopCallback var1) {
      this.callbacks.remove(var1);
   }

    std::string getIDFromItemInstallFolder(const std::string& var1) {
      if (var1 != nullptr && var1.replace("\\", "/").contains("/workshop/content/108600/")) {
    File var2 = std::make_shared<File>(var1);
    std::string var3 = var2.getName();
         if (SteamUtils.isValidSteamID(var3)) {
    return var3;
         }

         DebugLog.log("ERROR: " + var3 + " isn't a valid workshop item ID");
      }

    return nullptr;
   }

   private native void n_Init();

   private native void n_Shutdown();

   private native boolean n_CreateItem();

   private native boolean n_StartItemUpdate(long var1);

   private native boolean n_SetItemTitle(std::string var1);

   private native boolean n_SetItemDescription(std::string var1);

   private native boolean n_SetItemVisibility(int var1);

   private native boolean n_SetItemTags(std::string[] var1);

   private native boolean n_SetItemContent(std::string var1);

   private native boolean n_SetItemPreview(std::string var1);

   private native boolean n_SubmitItemUpdate(std::string var1);

   private native boolean n_GetItemUpdateProgress(long[] var1);

   private native std::string[] n_GetInstalledItemFolders();

   private native long n_GetItemState(long var1);

   private native boolean n_SubscribeItem(long var1);

   private native boolean n_DownloadItem(long var1, boolean var3);

   private native std::string n_GetItemInstallFolder(long var1);

   private native long n_GetItemInstallTimeStamp(long var1);

   private native boolean n_GetItemDownloadInfo(long var1, long[] var3);

   private native long n_CreateQueryUGCDetailsRequest(long[] var1);

   private native SteamUGCDetails n_GetQueryUGCResult(long var1, int var3);

   private native long[] n_GetQueryUGCChildren(long var1, int var3);

   private native boolean n_ReleaseQueryUGCRequest(long var1);

    void onItemCreated(long var1, bool var3) {
      LuaEventManager.triggerEvent("OnSteamWorkshopItemCreated", SteamUtils.convertSteamIDToString(var1), var3);
   }

    void onItemNotCreated(int var1) {
      LuaEventManager.triggerEvent("OnSteamWorkshopItemNotCreated", var1);
   }

    void onItemUpdated(bool var1) {
      LuaEventManager.triggerEvent("OnSteamWorkshopItemUpdated", var1);
   }

    void onItemNotUpdated(int var1) {
      LuaEventManager.triggerEvent("OnSteamWorkshopItemNotUpdated", var1);
   }

    void onItemSubscribed(long var1) {
      for (int var3 = 0; var3 < this.callbacks.size(); var3++) {
         this.callbacks.get(var3).onItemSubscribed(var1);
      }
   }

    void onItemNotSubscribed(long var1, int var3) {
      for (int var4 = 0; var4 < this.callbacks.size(); var4++) {
         this.callbacks.get(var4).onItemNotSubscribed(var1, var3);
      }
   }

    void onItemDownloaded(long var1) {
      for (int var3 = 0; var3 < this.callbacks.size(); var3++) {
         this.callbacks.get(var3).onItemDownloaded(var1);
      }
   }

    void onItemNotDownloaded(long var1, int var3) {
      for (int var4 = 0; var4 < this.callbacks.size(); var4++) {
         this.callbacks.get(var4).onItemNotDownloaded(var1, var3);
      }
   }

    void onItemQueryCompleted(long var1, int var3) {
      for (int var4 = 0; var4 < this.callbacks.size(); var4++) {
         this.callbacks.get(var4).onItemQueryCompleted(var1, var3);
      }
   }

    void onItemQueryNotCompleted(long var1, int var3) {
      for (int var4 = 0; var4 < this.callbacks.size(); var4++) {
         this.callbacks.get(var4).onItemQueryNotCompleted(var1, var3);
      }
   }
}
} // namespace znet
} // namespace core
} // namespace zombie
