#pragma once
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/GameServer.h"
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace znet {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class SteamWorkshop {
public:
 static const SteamWorkshop instance = new SteamWorkshop();
private
 ArrayList<SteamWorkshopItem> stagedItems = std::make_unique<ArrayList<>>();
private
 ArrayList<ISteamWorkshopCallback> callbacks = std::make_unique<ArrayList<>>();

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

 void copyFile(File file0, File file1) {
 try(FileInputStream fileInputStream = new FileInputStream(file0);
 FileOutputStream fileOutputStream = new FileOutputStream(file1);) {
 fileOutputStream.getChannel().transferFrom(fileInputStream.getChannel(),
 0L, file0.length());
 }
 catch (IOException iOException) {
 iOException.printStackTrace();
 }
 }

 void copyFileOrFolder(File file0, File file1) {
 if (file0.isDirectory()) {
 if (!file1.mkdirs()) {
 return;
 }

 String[] strings = file0.list();

 for (int int0 = 0; int0 < strings.length; int0++) {
 this->copyFileOrFolder(new File(file0, strings[int0]),
 new File(file1, strings[int0]));
 }
 } else {
 this->copyFile(file0, file1);
 }
 }

 void initWorkshopFolder() {
 File file0 = new File(this->getWorkshopFolder());
 if (file0.exists() || file0.mkdirs()) {
 File file1 = new File("Workshop" + File.separator + "ModTemplate");
 File file2 =
 new File(this->getWorkshopFolder() + File.separator + "ModTemplate");
 if (file1.exists() && !file2.exists()) {
 this->copyFileOrFolder(file1, file2);
 }
 }
 }

public
 ArrayList<SteamWorkshopItem> loadStagedItems() {
 this->stagedItems.clear();

 for (String string : this->getStageFolders()) {
 SteamWorkshopItem steamWorkshopItem = new SteamWorkshopItem(string);
 steamWorkshopItem.readWorkshopTxt();
 this->stagedItems.add(steamWorkshopItem);
 }

 return this->stagedItems;
 }

 std::string getWorkshopFolder() {
 return ZomboidFileSystem.instance.getCacheDir() + File.separator +
 "Workshop";
 }

public
 ArrayList<String> getStageFolders() {
 std::vector arrayList = new ArrayList();
 Path path0 = FileSystems.getDefault().getPath(this->getWorkshopFolder());

 try {
 if (!Files.isDirectory(path0) {
 Files.createDirectories(path0);
 }
 } catch (IOException iOException) {
 iOException.printStackTrace();
 return arrayList;
 }

 Filter filter = std::make_unique<Filter<Path>>(){
 bool accept(Path path){return Files.isDirectory(path);
 }
};

try(DirectoryStream directoryStream = Files.newDirectoryStream(path0, filter) {
 for (auto &path1 : directoryStream)
 std::string string = path1.toAbsolutePath().toString();
 arrayList.add(string);
}
}
catch (Exception exception) {
 exception.printStackTrace();
}

return arrayList;
}

bool CreateWorkshopItem(SteamWorkshopItem steamWorkshopItem) {
 if (steamWorkshopItem.getID() != nullptr) {
 throw RuntimeException("can't recreate an existing item");
 } else {
 return this->n_CreateItem();
 }
}

bool SubmitWorkshopItem(SteamWorkshopItem steamWorkshopItem) {
 if (steamWorkshopItem.getID() != nullptr &&
 SteamUtils.isValidSteamID(steamWorkshopItem.getID())) {
 long long0 = SteamUtils.convertStringToSteamID(steamWorkshopItem.getID());
 if (!this->n_StartItemUpdate(long0) {
 return false;
 } else if (!this->n_SetItemTitle(steamWorkshopItem.getTitle())) {
 return false;
 } else if (!this->n_SetItemDescription(
 steamWorkshopItem.getSubmitDescription())) {
 return false;
 } else {
 int int0 = steamWorkshopItem.getVisibilityInteger();
 if ("Mod Template" == steamWorkshopItem.getTitle())) {
 int0 = 2;
 }

 if (!this->n_SetItemVisibility(int0) {
 return false;
 } else {
 if (!this->n_SetItemTags(steamWorkshopItem.getSubmitTags())) {
 }

 if (!this->n_SetItemContent(steamWorkshopItem.getContentFolder())) {
 return false;
 } else {
 return !this->n_SetItemPreview(steamWorkshopItem.getPreviewImage())
 ? false
 : this->n_SubmitItemUpdate(
 steamWorkshopItem.getChangeNote());
 }
 }
 }
 } else {
 throw RuntimeException("workshop ID is required");
 }
}

bool GetItemUpdateProgress(long[] longs) {
 return this->n_GetItemUpdateProgress(longs);
}

public
String[] GetInstalledItemFolders() {
 return GameServer.bServer ? GameServer.WorkshopInstallFolders
 : this->n_GetInstalledItemFolders();
}

long GetItemState(long long0) { return this->n_GetItemState(long0); }

std::string GetItemInstallFolder(long long0) {
 return this->n_GetItemInstallFolder(long0);
}

long GetItemInstallTimeStamp(long long0) {
 return this->n_GetItemInstallTimeStamp(long0);
}

bool SubscribeItem(long long0, ISteamWorkshopCallback iSteamWorkshopCallback) {
 if (!this->callbacks.contains(iSteamWorkshopCallback) {
 this->callbacks.add(iSteamWorkshopCallback);
 }

 return this->n_SubscribeItem(long0);
}

bool DownloadItem(long long0, bool boolean0,
 ISteamWorkshopCallback iSteamWorkshopCallback) {
 if (!this->callbacks.contains(iSteamWorkshopCallback) {
 this->callbacks.add(iSteamWorkshopCallback);
 }

 return this->n_DownloadItem(long0, boolean0);
}

bool GetItemDownloadInfo(long long0, long[] longs) {
 return this->n_GetItemDownloadInfo(long0, longs);
}

long CreateQueryUGCDetailsRequest(
 long[] longs, ISteamWorkshopCallback iSteamWorkshopCallback) {
 if (!this->callbacks.contains(iSteamWorkshopCallback) {
 this->callbacks.add(iSteamWorkshopCallback);
 }

 return this->n_CreateQueryUGCDetailsRequest(longs);
}

SteamUGCDetails GetQueryUGCResult(long long0, int int0) {
 return this->n_GetQueryUGCResult(long0, int0);
}

public
long[] GetQueryUGCChildren(long long0, int int0) {
 return this->n_GetQueryUGCChildren(long0, int0);
}

bool ReleaseQueryUGCRequest(long long0) {
 return this->n_ReleaseQueryUGCRequest(long0);
}

void RemoveCallback(ISteamWorkshopCallback iSteamWorkshopCallback) {
 this->callbacks.remove(iSteamWorkshopCallback);
}

std::string getIDFromItemInstallFolder(const std::string &string0) {
 if (string0 != nullptr &&
 string0.replace("\\", "/").contains("/workshop/content/108600/")) {
 File file = new File(string0);
 std::string string1 = file.getName();
 if (SteamUtils.isValidSteamID(string1) {
 return string1;
 }

 DebugLog.log("ERROR: " + string1 + " isn't a valid workshop item ID");
 }

 return nullptr;
}

private
 void n_Init();

private
 void n_Shutdown();

private
 boolean n_CreateItem();

private
 boolean n_StartItemUpdate(long var1);

private
 boolean n_SetItemTitle(String var1);

private
 boolean n_SetItemDescription(String var1);

private
 boolean n_SetItemVisibility(int var1);

private
 boolean n_SetItemTags(String[] var1);

private
 boolean n_SetItemContent(String var1);

private
 boolean n_SetItemPreview(String var1);

private
 boolean n_SubmitItemUpdate(String var1);

private
 boolean n_GetItemUpdateProgress(long[] var1);

private
 String[] n_GetInstalledItemFolders();

private
 long n_GetItemState(long var1);

private
 boolean n_SubscribeItem(long var1);

private
 boolean n_DownloadItem(long var1, boolean var3);

private
 String n_GetItemInstallFolder(long var1);

private
 long n_GetItemInstallTimeStamp(long var1);

private
 boolean n_GetItemDownloadInfo(long var1, long[] var3);

private
 long n_CreateQueryUGCDetailsRequest(long[] var1);

private
 SteamUGCDetails n_GetQueryUGCResult(long var1, int var3);

private
 long[] n_GetQueryUGCChildren(long var1, int var3);

private
 boolean n_ReleaseQueryUGCRequest(long var1);

void onItemCreated(long long0, bool boolean0) {
 LuaEventManager.triggerEvent("OnSteamWorkshopItemCreated",
 SteamUtils.convertSteamIDToString(long0),
 boolean0);
}

void onItemNotCreated(int int0) {
 LuaEventManager.triggerEvent("OnSteamWorkshopItemNotCreated", int0);
}

void onItemUpdated(bool boolean0) {
 LuaEventManager.triggerEvent("OnSteamWorkshopItemUpdated", boolean0);
}

void onItemNotUpdated(int int0) {
 LuaEventManager.triggerEvent("OnSteamWorkshopItemNotUpdated", int0);
}

void onItemSubscribed(long long0) {
 for (int int0 = 0; int0 < this->callbacks.size(); int0++) {
 this->callbacks.get(int0).onItemSubscribed(long0);
 }
}

void onItemNotSubscribed(long long0, int int1) {
 for (int int0 = 0; int0 < this->callbacks.size(); int0++) {
 this->callbacks.get(int0).onItemNotSubscribed(long0, int1);
 }
}

void onItemDownloaded(long long0) {
 for (int int0 = 0; int0 < this->callbacks.size(); int0++) {
 this->callbacks.get(int0).onItemDownloaded(long0);
 }
}

void onItemNotDownloaded(long long0, int int1) {
 for (int int0 = 0; int0 < this->callbacks.size(); int0++) {
 this->callbacks.get(int0).onItemNotDownloaded(long0, int1);
 }
}

void onItemQueryCompleted(long long0, int int1) {
 for (int int0 = 0; int0 < this->callbacks.size(); int0++) {
 this->callbacks.get(int0).onItemQueryCompleted(long0, int1);
 }
}

void onItemQueryNotCompleted(long long0, int int1) {
 for (int int0 = 0; int0 < this->callbacks.size(); int0++) {
 this->callbacks.get(int0).onItemQueryNotCompleted(long0, int1);
 }
}
}
} // namespace znet
} // namespace core
} // namespace zombie
