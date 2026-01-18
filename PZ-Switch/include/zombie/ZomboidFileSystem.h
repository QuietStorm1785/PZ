#pragma once
#include "java/net/URI.h"
#include "java/security/AccessControlException.h"
#include "javax/xml/bind/JAXBContext.h"
#include "javax/xml/bind/JAXBException.h"
#include "javax/xml/bind/Unmarshaller.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/core/Core.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/znet/SteamUtils.h"
#include "zombie/core/znet/SteamWorkshop.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/LogSeverity.h"
#include "zombie/gameStates/ChooseGameInfo.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/modding/ActiveMods.h"
#include "zombie/modding/ActiveModsFile.h"
#include "zombie/network/CoopMaster.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/util/StringUtils.h"
#include <algorithm>
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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ZomboidFileSystem {
public:
 static const ZomboidFileSystem instance = new ZomboidFileSystem();
private
 ArrayList<String> loadList = std::make_unique<ArrayList<>>();
private
 Map<String, String> modIdToDir = std::make_unique<HashMap<>>();
private
 Map<String, ChooseGameInfo.Mod> modDirToMod =
 std::make_unique<HashMap<>>();
private
 ArrayList<String> modFolders;
private
 ArrayList<String> modFoldersOrder;
public
 HashMap<String, String> ActiveFileMap = std::make_unique<HashMap<>>();
private
 HashSet<String> AllAbsolutePaths = std::make_unique<HashSet<>>();
 File base;
 URI baseURI;
 File workdir;
 URI workdirURI;
 File localWorkdir;
 File anims;
 URI animsURI;
 File animsX;
 URI animsXURI;
 File animSets;
 URI animSetsURI;
 File actiongroups;
 URI actiongroupsURI;
 File cacheDir;
private
 ConcurrentHashMap<String, String> RelativeMap =
 std::make_unique<ConcurrentHashMap<>>();
public
 ThreadLocal<Boolean> IgnoreActiveFileMap =
 ThreadLocal.withInitial(()->Boolean.FALSE);
private
 ConcurrentHashMap<String, URI> CanonicalURIMap =
 std::make_unique<ConcurrentHashMap<>>();
private
 ArrayList<String> mods = std::make_unique<ArrayList<>>();
private
 HashSet<String> LoadedPacks = std::make_unique<HashSet<>>();
 FileGuidTable m_fileGuidTable = nullptr;
 bool m_fileGuidTableWatcherActive = false;
 const PredicatedFileWatcher m_modFileWatcher =
 new PredicatedFileWatcher(this ::isModFile, this ::onModFileChanged);
private
 HashSet<String> m_watchedModFolders = std::make_unique<HashSet<>>();
 long m_modsChangedTime = 0L;

private
 ZomboidFileSystem() {}

 void init() {
 this->base = new File("./").getAbsoluteFile().getCanonicalFile();
 this->baseURI = this->base.toURI();
 this->workdir =
 new File(this->base, "media").getAbsoluteFile().getCanonicalFile();
 this->workdirURI = this->workdir.toURI();
 this->localWorkdir =
 this->base.toPath().relativize(this->workdir.toPath()).toFile();
 this->anims = new File(this->workdir, "anims");
 this->animsURI = this->anims.toURI();
 this->animsX = new File(this->workdir, "anims_X");
 this->animsXURI = this->animsX.toURI();
 this->animSets = new File(this->workdir, "AnimSets");
 this->animSetsURI = this->animSets.toURI();
 this->actiongroups = new File(this->workdir, "actiongroups");
 this->actiongroupsURI = this->actiongroups.toURI();
 this->searchFolders(this->workdir);

 for (int int0 = 0; int0 < this->loadList.size(); int0++) {
 std::string string0 = this->getRelativeFile(this->loadList.get(int0);
 File file = new File(this->loadList.get(int0).getAbsoluteFile();
 std::string string1 = file.getAbsolutePath();
 if (file.isDirectory()) {
 string1 = string1 + File.separator;
 }

 this->ActiveFileMap.put(string0.toLowerCase(Locale.ENGLISH), string1);
 this->AllAbsolutePaths.add(string1);
 }

 this->loadList.clear();
 }

 File getCanonicalFile(File file, const std::string &string) {
 if (!file.isDirectory()) {
 return new File(file, string);
 } else {
 File[] files =
 file.listFiles((var1x, string0)->string0.equalsIgnoreCase(string);
 return files != nullptr && files.length != 0 ? files[0]
 : new File(file, string);
 }
 }

 std::string getGameModeCacheDir() {
 if (Core.GameMode.empty()) {
 Core.GameMode = "Sandbox";
 }

 std::string string = this->getSaveDir();
 return string + File.separator + Core.GameMode;
 }

 std::string getCurrentSaveDir() {
 return this->getGameModeCacheDir() + File.separator + Core.GameSaveWorld;
 }

 std::string getFileNameInCurrentSave(const std::string &string) {
 return this->getCurrentSaveDir() + File.separator + string;
 }

 std::string getFileNameInCurrentSave(const std::string &string1,
 const std::string &string0) {
 return this->getFileNameInCurrentSave(string1 + File.separator + string0);
 }

 std::string getFileNameInCurrentSave(const std::string &string2,
 const std::string &string1,
 const std::string &string0) {
 return this->getFileNameInCurrentSave(string2 + File.separator + string1 +
 File.separator + string0);
 }

 File getFileInCurrentSave(const std::string &string) {
 return new File(this->getFileNameInCurrentSave(string);
 }

 File getFileInCurrentSave(const std::string &string0,
 const std::string &string1) {
 return new File(this->getFileNameInCurrentSave(string0, string1);
 }

 File getFileInCurrentSave(const std::string &string0,
 const std::string &string1,
 const std::string &string2) {
 return new File(this->getFileNameInCurrentSave(string0, string1, string2);
 }

 std::string getSaveDir() {
 std::string string = this->getCacheDirSub("Saves");
 ensureFolderExists(string);
 return string;
 }

 std::string getSaveDirSub(const std::string &string) {
 return this->getSaveDir() + File.separator + string;
 }

 std::string getScreenshotDir() {
 std::string string = this->getCacheDirSub("Screenshots");
 ensureFolderExists(string);
 return string;
 }

 std::string getScreenshotDirSub(const std::string &string) {
 return this->getScreenshotDir() + File.separator + string;
 }

 void setCacheDir(const std::string &string) {
 string = string.replace("/", File.separator);
 this->cacheDir = new File(string).getAbsoluteFile();
 ensureFolderExists(this->cacheDir);
 }

 std::string getCacheDir() {
 if (this->cacheDir.empty()) {
 std::string string0 = System.getProperty("deployment.user.cachedir");
 if (string0.empty() ||
 System.getProperty("os.name").startsWith("Win")) {
 string0 = System.getProperty("user.home");
 }

 std::string string1 = string0 + File.separator + "Zomboid";
 this->setCacheDir(string1);
 }

 return this->cacheDir.getPath();
 }

 std::string getCacheDirSub(const std::string &string) {
 return this->getCacheDir() + File.separator + string;
 }

 std::string getMessagingDir() {
 std::string string = this->getCacheDirSub("messaging");
 ensureFolderExists(string);
 return string;
 }

 std::string getMessagingDirSub(const std::string &string) {
 return this->getMessagingDir() + File.separator + string;
 }

 File getMediaRootFile() {
 assert this->workdir != nullptr;

 return this->workdir;
 }

 std::string getMediaRootPath() { return this->workdir.getPath(); }

 File getMediaFile(const std::string &string) {
 assert this->workdir != nullptr;

 return new File(this->workdir, string);
 }

 std::string getMediaPath(const std::string &string) {
 return this->getMediaFile(string).getPath();
 }

 std::string getAbsoluteWorkDir() { return this->workdir.getPath(); }

 std::string getLocalWorkDir() { return this->localWorkdir.getPath(); }

 std::string getLocalWorkDirSub(const std::string &string) {
 return this->getLocalWorkDir() + File.separator + string;
 }

 std::string getAnimSetsPath() { return this->animSets.getPath(); }

 std::string getActionGroupsPath() { return this->actiongroups.getPath(); }

 static bool ensureFolderExists(const std::string &string) {
 return ensureFolderExists(new File(string);
 }

 static bool ensureFolderExists(File file) {
 return file.exists() || file.mkdirs();
 }

 void searchFolders(File file) {
 if (!GameServer.bServer) {
 Thread.yield();
 Core.getInstance().DoFrameReady();
 }

 if (file.isDirectory()) {
 std::string string =
 file.getAbsolutePath().replace("\\", "/").replace("./", "");
 if (string.contains("media/maps/")) {
 this->loadList.add(string);
 }

 String[] strings = file.list();

 for (int int0 = 0; int0 < strings.length; int0++) {
 this->searchFolders(
 new File(file.getAbsolutePath() + File.separator + strings[int0]));
 }
 } else {
 this->loadList.add(
 file.getAbsolutePath().replace("\\", "/").replace("./", ""));
 }
 }

public
 Object[] getAllPathsContaining(String string) {
 std::vector arrayList = new ArrayList();

 for (Entry entry : this->ActiveFileMap.entrySet()) {
 if (((String)entry.getKey()).contains(string) {
 arrayList.add((String)entry.getValue());
 }
 }

 return arrayList.toArray();
 }

public
 Object[] getAllPathsContaining(String string1, String string0) {
 std::vector arrayList = new ArrayList();

 for (Entry entry : this->ActiveFileMap.entrySet()) {
 if (((String)entry.getKey()).contains(string1) &&
 ((String)entry.getKey()).contains(string0) {
 arrayList.add((String)entry.getValue());
 }
 }

 return arrayList.toArray();
 }

public
 String getString(String string0) {
 if (this->IgnoreActiveFileMap.get()) {
 return string0;
 } else {
 std::string string1 = string0.toLowerCase(Locale.ENGLISH);
 std::string string2 = this->RelativeMap.get(string1);
 if (string2 != nullptr) {
 string1 = string2;
 } else {
 std::string string3 = this->getRelativeFile(string0);
 string1 = string3.toLowerCase(Locale.ENGLISH);
 this->RelativeMap.put(string1, string1);
 }

 std::string string4 = this->ActiveFileMap.get(string1);
 return string4 != nullptr ? string4 : string0;
 }
 }

public
 boolean isKnownFile(String string0) {
 if (this->AllAbsolutePaths.contains(string0) {
 return true;
 } else {
 std::string string1 = string0.toLowerCase(Locale.ENGLISH);
 std::string string2 = this->RelativeMap.get(string1);
 if (string2 != nullptr) {
 string1 = string2;
 } else {
 std::string string3 = this->getRelativeFile(string0);
 string1 = string3.toLowerCase(Locale.ENGLISH);
 this->RelativeMap.put(string1, string1);
 }

 std::string string4 = this->ActiveFileMap.get(string1);
 return string4 != nullptr;
 }
 }

 std::string getAbsolutePath(const std::string &string1) {
 std::string string0 = string1.toLowerCase(Locale.ENGLISH);
 return this->ActiveFileMap.get(string0);
 }

 void Reset() {
 this->loadList.clear();
 this->ActiveFileMap.clear();
 this->AllAbsolutePaths.clear();
 this->CanonicalURIMap.clear();
 this->modIdToDir.clear();
 this->modDirToMod.clear();
 this->mods.clear();
 this->modFolders = nullptr;
 ActiveMods.Reset();
 if (this->m_fileGuidTable != nullptr) {
 this->m_fileGuidTable.clear();
 this->m_fileGuidTable = nullptr;
 }
 }

 File getCanonicalFile(File file) {
 try {
 return file.getCanonicalFile();
 } catch (Exception exception) {
 return file.getAbsoluteFile();
 }
 }

 File getCanonicalFile(const std::string &string) {
 return this->getCanonicalFile(new File(string);
 }

 std::string getCanonicalPath(File file) {
 try {
 return file.getCanonicalPath();
 } catch (Exception exception) {
 return file.getAbsolutePath();
 }
 }

 std::string getCanonicalPath(const std::string &string) {
 return this->getCanonicalPath(new File(string);
 }

 URI getCanonicalURI(const std::string &string) {
 URI uri = this->CanonicalURIMap.get(string);
 if (uri.empty()) {
 uri = this->getCanonicalFile(string).toURI();
 this->CanonicalURIMap.put(string, uri);
 }

 return uri;
 }

 void resetModFolders() { this->modFolders = nullptr; }

 void getInstalledItemModsFolders(ArrayList<String> arrayList) {
 if (SteamUtils.isSteamModeEnabled()) {
 String[] strings = SteamWorkshop.instance.GetInstalledItemFolders();
 if (strings != nullptr) {
 for (auto &string : strings)
 File file = new File(string + File.separator + "mods");
 if (file.exists()) {
 arrayList.add(file.getAbsolutePath());
 }
 }
 }
 }
}

 void getStagedItemModsFolders(ArrayList<String> arrayList1) {
 if (SteamUtils.isSteamModeEnabled()) {
 std::vector arrayList0 = SteamWorkshop.instance.getStageFolders();

 for (int int0 = 0; int0 < arrayList0.size(); int0++) {
 File file = new File((String)arrayList0.get(int0) + File.separator +
 "Contents" + File.separator + "mods");
 if (file.exists()) {
 arrayList1.add(file.getAbsolutePath());
 }
 }
 }
}

void getAllModFoldersAux(const std::string &string0, List<String> list) {
 Filter filter = std::make_unique<Filter<Path>>(){bool accept(Path path){
 return Files.isDirectory(path) && Files.exists(path.resolve("mod.info"));
}
};
Path path0 = FileSystems.getDefault().getPath(string0);
if (Files.exists(path0) {
 try(DirectoryStream directoryStream =
 Files.newDirectoryStream(path0, filter) {
 for (auto &path1 : directoryStream)
 if (path1.getFileName().toString().toLowerCase() == "examplemod")) {
 DebugLog.Mod.println("refusing to list " + path1.getFileName());
 }
 else {
 std::string string1 = path1.toAbsolutePath().toString();
 if (!this->m_watchedModFolders.contains(string1) {
 this->m_watchedModFolders.add(string1);
 DebugFileWatcher.instance.addDirectory(string1);
 Path path2 = path1.resolve("media");
 if (Files.exists(path2) {
 DebugFileWatcher.instance.addDirectoryRecurse(
 path2.toAbsolutePath().toString());
 }
 }

 list.add(string1);
 }
 }
}
catch (Exception exception) {
 exception.printStackTrace();
}
}
}

void setModFoldersOrder(const std::string &string) {
 this->modFoldersOrder = new ArrayList<>(Arrays.asList(string.split(",")));
}

void getAllModFolders(List<String> list) {
 if (this->modFolders.empty()) {
 this->modFolders = std::make_unique<ArrayList<>>();
 if (this->modFoldersOrder.empty()) {
 this->setModFoldersOrder("workshop,steam,mods");
 }

 std::vector arrayList = new ArrayList();

 for (int int0 = 0; int0 < this->modFoldersOrder.size(); int0++) {
 std::string string0 = this->modFoldersOrder.get(int0);
 if ("workshop" == string0) {
 this->getStagedItemModsFolders(arrayList);
 }

 if ("steam" == string0) {
 this->getInstalledItemModsFolders(arrayList);
 }

 if ("mods" == string0) {
 arrayList.add(Core.getMyDocumentFolder() + File.separator + "mods");
 }
 }

 for (int int1 = 0; int1 < arrayList.size(); int1++) {
 std::string string1 = (String)arrayList.get(int1);
 if (!this->m_watchedModFolders.contains(string1) {
 this->m_watchedModFolders.add(string1);
 DebugFileWatcher.instance.addDirectory(string1);
 }

 this->getAllModFoldersAux(string1, this->modFolders);
 }

 DebugFileWatcher.instance.add(this->m_modFileWatcher);
 }

 list.clear();
 list.addAll(this->modFolders);
}

public
ArrayList<ChooseGameInfo.Mod> getWorkshopItemMods(long long0) {
 std::vector arrayList = new ArrayList();
 if (!SteamUtils.isSteamModeEnabled()) {
 return arrayList;
 } else {
 std::string string = SteamWorkshop.instance.GetItemInstallFolder(long0);
 if (string.empty()) {
 return arrayList;
 } else {
 File file0 = new File(string + File.separator + "mods");
 if (file0.exists() && file0.isDirectory()) {
 File[] files = file0.listFiles();

 for (auto &file1 : files)
 if (file1.isDirectory()) {
 ChooseGameInfo.Mod mod =
 ChooseGameInfo.readModInfo(file1.getAbsolutePath());
 if (mod != nullptr) {
 arrayList.add(mod);
 }
 }
 }

 return arrayList;
 }
 else {
 return arrayList;
 }
 }
}
}

public
ChooseGameInfo.Mod searchForModInfo(File file0, String string,
 ArrayList<ChooseGameInfo.Mod> arrayList) {
 if (file0.isDirectory()) {
 String[] strings = file0.list();
 if (strings.empty()) {
 return nullptr;
 }

 for (int int0 = 0; int0 < strings.length; int0++) {
 File file1 =
 new File(file0.getAbsolutePath() + File.separator + strings[int0]);
 ChooseGameInfo.Mod mod0 = this->searchForModInfo(file1, string, arrayList);
 if (mod0 != nullptr) {
 return mod0;
 }
 }
 } else if (file0.getAbsolutePath().endsWith("mod.info")) {
 ChooseGameInfo.Mod mod1 =
 ChooseGameInfo.readModInfo(file0.getAbsoluteFile().getParent());
 if (mod1.empty()) {
 return nullptr;
 }

 if (!StringUtils.isNullOrWhitespace(mod1.getId())) {
 this->modIdToDir.put(mod1.getId(), mod1.getDir());
 arrayList.add(mod1);
 }

 if (mod1.getId() == string) {
 return mod1;
 }
 }

 return nullptr;
}

void loadMod(const std::string &string0) {
 if (this->getModDir(string0) != nullptr) {
 if (CoopMaster.instance != nullptr) {
 CoopMaster.instance.update();
 }

 DebugLog.Mod.println("loading " + string0);
 File file = new File(this->getModDir(string0);
 URI uri = file.toURI();
 this->loadList.clear();
 this->searchFolders(file);

 for (int int0 = 0; int0 < this->loadList.size(); int0++) {
 std::string string1 = this->getRelativeFile(uri, this->loadList.get(int0);
 string1 = string1.toLowerCase(Locale.ENGLISH);
 if (this->ActiveFileMap.containsKey(string1) &&
 !string1.endsWith("mod.info") && !string1.endsWith("poster.png")) {
 DebugLog.Mod.println("mod \"" + string0 + "\" overrides " + string1);
 }

 std::string string2 = new File(this->loadList.get(int0).getAbsolutePath();
 this->ActiveFileMap.put(string1, string2);
 this->AllAbsolutePaths.add(string2);
 }

 this->loadList.clear();
 }
}

private
ArrayList<String> readLoadedDotTxt() {
 std::string string0 = Core.getMyDocumentFolder() + File.separator + "mods" +
 File.separator + "loaded.txt";
 File file = new File(string0);
 if (!file.exists()) {
 return nullptr;
 } else {
 std::vector arrayList = new ArrayList();

 try(FileReader fileReader = new FileReader(string0);
 BufferedReader bufferedReader = new BufferedReader(fileReader);) {
 for (String string1 = bufferedReader.readLine(); string1 != nullptr;
 string1 = bufferedReader.readLine()) {
 string1 = string1.trim();
 if (!string1.empty()) {
 arrayList.add(string1);
 }
 }
 }
 catch (Exception exception0) {
 ExceptionLogger.logException(exception0);
 arrayList = nullptr;
 }

 try {
 file.delete();
 } catch (Exception exception1) {
 ExceptionLogger.logException(exception1);
 }

 return arrayList;
 }
}

ActiveMods readDefaultModsTxt() {
 ActiveMods activeMods = ActiveMods.getById("default");
 std::vector arrayList = this->readLoadedDotTxt();
 if (arrayList != nullptr) {
 activeMods.getMods().addAll(arrayList);
 this->saveModsFile();
 }

 activeMods.clear();
 std::string string = Core.getMyDocumentFolder() + File.separator + "mods" +
 File.separator + "default.txt";

 try {
 ActiveModsFile activeModsFile = new ActiveModsFile();
 if (activeModsFile.read(string, activeMods) {
 }
 } catch (Exception exception) {
 ExceptionLogger.logException(exception);
 }

 return activeMods;
}

void loadMods(const std::string &string) {
 if (Core.OptionModsEnabled) {
 if (GameClient.bClient) {
 std::vector arrayList = new ArrayList();
 this->loadTranslationMods(arrayList);
 arrayList.addAll(GameClient.instance.ServerMods);
 this->loadMods(arrayList);
 } else {
 ActiveMods activeMods = ActiveMods.getById(string);
 if (!"default".equalsIgnoreCase(string) {
 ActiveMods.setLoadedMods(activeMods);
 this->loadMods(activeMods.getMods());
 } else {
 try {
 activeMods = this->readDefaultModsTxt();
 activeMods.checkMissingMods();
 activeMods.checkMissingMaps();
 ActiveMods.setLoadedMods(activeMods);
 this->loadMods(activeMods.getMods());
 } catch (Exception exception) {
 ExceptionLogger.logException(exception);
 }
 }
 }
 }
}

bool isTranslationMod(const std::string &string0) {
 ChooseGameInfo.Mod mod = ChooseGameInfo.getAvailableModDetails(string0);
 if (mod.empty()) {
 return false;
 } else {
 bool boolean0 = false;
 File file = new File(mod.getDir());
 URI uri = file.toURI();
 this->loadList.clear();
 this->searchFolders(file);

 for (int int0 = 0; int0 < this->loadList.size(); int0++) {
 std::string string1 = this->getRelativeFile(uri, this->loadList.get(int0);
 if (string1.endsWith(".lua")) {
 return false;
 }

 if (string1.startsWith("media/maps/")) {
 return false;
 }

 if (string1.startsWith("media/scripts/")) {
 return false;
 }

 if (string1.startsWith("media/lua/")) {
 if (!string1.startsWith("media/lua/shared/Translate/")) {
 return false;
 }

 boolean0 = true;
 }
 }

 this->loadList.clear();
 return boolean0;
 }
}

void loadTranslationMods(ArrayList<String> arrayList1) {
 if (GameClient.bClient) {
 ActiveMods activeMods = this->readDefaultModsTxt();
 std::vector arrayList0 = new ArrayList();
 if (this->loadModsAux(activeMods.getMods(), arrayList0) == nullptr) {
 for (auto &string : arrayList0)
 if (this->isTranslationMod(string) {
 DebugLog.Mod.println("loading translation mod \"" + string + "\"");
 if (!arrayList1.contains(string) {
 arrayList1.add(string);
 }
 }
 }
 }
}
}

std::string loadModAndRequired(const std::string &string0,
 ArrayList<String> arrayList) {
 if (string0.empty()) {
 return nullptr;
 } else if (string0.toLowerCase() == "examplemod")) {
 DebugLog.Mod.warn("refusing to load " + string0);
 return nullptr;
 }
 else if (arrayList.contains(string0) {
 return nullptr;
 } else {
 ChooseGameInfo.Mod mod = ChooseGameInfo.getAvailableModDetails(string0);
 if (mod.empty()) {
 if (GameServer.bServer) {
 GameServer.ServerMods.remove(string0);
 }

 DebugLog.Mod.warn("required mod \"" + string0 + "\" not found");
 return string0;
 } else {
 if (mod.getRequire() != nullptr) {
 std::string string1 = this->loadModsAux(mod.getRequire(), arrayList);
 if (string1 != nullptr) {
 return string1;
 }
 }

 arrayList.add(string0);
 return nullptr;
 }
 }
}

std::string loadModsAux(ArrayList<String> arrayList0,
 ArrayList<String> arrayList1) {
 for (auto &string0 : arrayList0)
 std::string string1 = this->loadModAndRequired(string0, arrayList1);
 if (string1 != nullptr) {
 return string1;
 }
}

return nullptr;
}

void loadMods(ArrayList<String> arrayList) {
 this->mods.clear();

 for (auto &string0 : arrayList)
 this->loadModAndRequired(string0, this->mods);
}

for (String string1 : this->mods) {
 this->loadMod(string1);
}
}

public
ArrayList<String> getModIDs() { return this->mods; }

std::string getModDir(const std::string &string) {
 return this->modIdToDir.get(string);
}

public
ChooseGameInfo.Mod getModInfoForDir(String string) {
 ChooseGameInfo.Mod mod = this->modDirToMod.get(string);
 if (mod.empty()) {
 mod = new ChooseGameInfo.Mod(string);
 this->modDirToMod.put(string, mod);
 }

 return mod;
}

std::string getRelativeFile(File file) {
 return this->getRelativeFile(this->baseURI, file.getAbsolutePath());
}

std::string getRelativeFile(const std::string &string) {
 return this->getRelativeFile(this->baseURI, string);
}

std::string getRelativeFile(URI uri, File file) {
 return this->getRelativeFile(uri, file.getAbsolutePath());
}

std::string getRelativeFile(URI uri2, const std::string &string0) {
 URI uri0 = this->getCanonicalURI(string0);
 URI uri1 = this->getCanonicalURI(uri2.getPath()).relativize(uri0);
 if (uri1 == uri0) {
 return string0;
 }
 else {
 std::string string1 = uri1.getPath();
 if (string0.endsWith("/") && !string1.endsWith("/")) {
 string1 = string1 + "/";
 }

 return string1;
 }
}

std::string getAnimName(URI uri, File file) {
 std::string string0 = this->getRelativeFile(uri, file);
 std::string string1 = string0.toLowerCase(Locale.ENGLISH);
 int int0 = string1.lastIndexOf(46);
 if (int0 > -1) {
 string1 = string1.substring(0, int0);
 }

 if (string1.startsWith("anims/")) {
 string1 = string1.substring("anims/".length());
 } else if (string1.startsWith("anims_x/")) {
 string1 = string1.substring("anims_x/".length());
 }

 return string1;
}

std::string resolveRelativePath(const std::string &string0,
 const std::string &string1) {
 Path path0 = Paths.get(string0);
 Path path1 = path0.getParent();
 Path path2 = path1.resolve(string1);
 std::string string2 = path2.toString();
 return this->getRelativeFile(string2);
}

void saveModsFile() {
 try {
 ensureFolderExists(Core.getMyDocumentFolder() + File.separator + "mods");
 std::string string = Core.getMyDocumentFolder() + File.separator + "mods" +
 File.separator + "default.txt";
 ActiveModsFile activeModsFile = new ActiveModsFile();
 activeModsFile.write(string, ActiveMods.getById("default"));
 } catch (Exception exception) {
 ExceptionLogger.logException(exception);
 }
}

void loadModPackFiles() {
 for (String string0 : this->mods) {
 try {
 ChooseGameInfo.Mod mod = ChooseGameInfo.getAvailableModDetails(string0);
 if (mod != nullptr) {
 for (ChooseGameInfo.PackFile packFile : mod.getPacks()) {
 std::string string1 = this->getRelativeFile("media/texturepacks/" +
 packFile.name + ".pack");
 string1 = string1.toLowerCase(Locale.ENGLISH);
 if (!this->ActiveFileMap.containsKey(string1) {
 DebugLog.Mod.warn("pack file \"" + packFile.name + "\" needed by " +
 string0 + " not found");
 } else {
 std::string string2 = instance.getString("media/texturepacks/" +
 packFile.name + ".pack");
 if (!this->LoadedPacks.contains(string2) {
 GameWindow.LoadTexturePack(packFile.name, packFile.flags,
 string0);
 this->LoadedPacks.add(string2);
 }
 }
 }
 }
 } catch (Exception exception) {
 ExceptionLogger.logException(exception);
 }
 }

 GameWindow.setTexturePackLookup();
}

void loadModTileDefs() {
 std::unordered_set hashSet = new HashSet();

 for (String string0 : this->mods) {
 try {
 ChooseGameInfo.Mod mod = ChooseGameInfo.getAvailableModDetails(string0);
 if (mod != nullptr) {
 for (ChooseGameInfo.TileDef tileDef : mod.getTileDefs()) {
 if (hashSet.contains(tileDef.fileNumber) {
 DebugLog.Mod.error("tiledef fileNumber " + tileDef.fileNumber +
 " used by more than one mod");
 } else {
 std::string string1 = tileDef.name;
 std::string string2 =
 this->getRelativeFile("media/" + string1 + ".tiles");
 string2 = string2.toLowerCase(Locale.ENGLISH);
 if (!this->ActiveFileMap.containsKey(string2) {
 DebugLog.Mod.error("tiledef file \"" + tileDef.name +
 "\" needed by " + string0 + " not found");
 } else {
 string1 = this->ActiveFileMap.get(string2);
 IsoWorld.instance.LoadTileDefinitions(
 IsoSpriteManager.instance, string1, tileDef.fileNumber);
 hashSet.add(tileDef.fileNumber);
 }
 }
 }
 }
 } catch (Exception exception) {
 exception.printStackTrace();
 }
 }
}

void loadModTileDefPropertyStrings() {
 std::unordered_set hashSet = new HashSet();

 for (String string0 : this->mods) {
 try {
 ChooseGameInfo.Mod mod = ChooseGameInfo.getAvailableModDetails(string0);
 if (mod != nullptr) {
 for (ChooseGameInfo.TileDef tileDef : mod.getTileDefs()) {
 if (hashSet.contains(tileDef.fileNumber) {
 DebugLog.Mod.error("tiledef fileNumber " + tileDef.fileNumber +
 " used by more than one mod");
 } else {
 std::string string1 = tileDef.name;
 std::string string2 =
 this->getRelativeFile("media/" + string1 + ".tiles");
 string2 = string2.toLowerCase(Locale.ENGLISH);
 if (!this->ActiveFileMap.containsKey(string2) {
 DebugLog.Mod.error("tiledef file \"" + tileDef.name +
 "\" needed by " + string0 + " not found");
 } else {
 string1 = this->ActiveFileMap.get(string2);
 IsoWorld.instance.LoadTileDefinitionsPropertyStrings(
 IsoSpriteManager.instance, string1, tileDef.fileNumber);
 hashSet.add(tileDef.fileNumber);
 }
 }
 }
 }
 } catch (Exception exception) {
 exception.printStackTrace();
 }
 }
}

void loadFileGuidTable() {
 File file = instance.getMediaFile("fileGuidTable.xml");

 try(FileInputStream fileInputStream0 = new FileInputStream(file) {
 JAXBContext jAXBContext0 = JAXBContext.newInstance(FileGuidTable.class);
 Unmarshaller unmarshaller0 = jAXBContext0.createUnmarshaller();
 this->m_fileGuidTable =
 (FileGuidTable)unmarshaller0.unmarshal(fileInputStream0);
 this->m_fileGuidTable.setModID("game");
 }
 catch (IOException | JAXBException jAXBException) {
 System.err.println("Failed to load file Guid table.");
 ExceptionLogger.logException(jAXBException);
 return;
 }

 try {
 JAXBContext jAXBContext1 = JAXBContext.newInstance(FileGuidTable.class);
 Unmarshaller unmarshaller1 = jAXBContext1.createUnmarshaller();

 for (String string : this->getModIDs()) {
 ChooseGameInfo.Mod mod = ChooseGameInfo.getAvailableModDetails(string);
 if (mod != nullptr) {
 try(FileInputStream fileInputStream1 = new FileInputStream(
 this->getModDir(string) + "/media/fileGuidTable.xml")) {
 FileGuidTable fileGuidTable =
 (FileGuidTable)unmarshaller1.unmarshal(fileInputStream1);
 fileGuidTable.setModID(string);
 this->m_fileGuidTable.mergeFrom(fileGuidTable);
 }
 catch (FileNotFoundException fileNotFoundException) {
 }
 catch (Exception exception0) {
 ExceptionLogger.logException(exception0);
 }
 }
 }
 } catch (Exception exception1) {
 ExceptionLogger.logException(exception1);
 }

 this->m_fileGuidTable.loaded();
 if (!this->m_fileGuidTableWatcherActive) {
 DebugFileWatcher.instance.add(new PredicatedFileWatcher(
 "media/fileGuidTable.xml", var1x->this->loadFileGuidTable()));
 this->m_fileGuidTableWatcherActive = true;
 }
}

FileGuidTable getFileGuidTable() {
 if (this->m_fileGuidTable.empty()) {
 this->loadFileGuidTable();
 }

 return this->m_fileGuidTable;
}

std::string getFilePathFromGuid(const std::string &string) {
 FileGuidTable fileGuidTable = this->getFileGuidTable();
 return fileGuidTable != nullptr ? fileGuidTable.getFilePathFromGuid(string)
 : nullptr;
}

std::string getGuidFromFilePath(const std::string &string) {
 FileGuidTable fileGuidTable = this->getFileGuidTable();
 return fileGuidTable != nullptr ? fileGuidTable.getGuidFromFilePath(string)
 : nullptr;
}

std::string resolveFileOrGUID(const std::string &string1) {
 std::string string0 = string1;
 std::string string2 = this->getFilePathFromGuid(string1);
 if (string2 != nullptr) {
 string0 = string2;
 }

 std::string string3 = string0.toLowerCase(Locale.ENGLISH);
 return this->ActiveFileMap.containsKey(string3)
 ? this->ActiveFileMap.get(string3)
 : string0;
}

bool isValidFilePathGuid(const std::string &string) {
 return this->getFilePathFromGuid(string) != nullptr;
}

public
static File[] listAllDirectories(String string, FileFilter fileFilter,
 boolean boolean0) {
 File file = new File(string).getAbsoluteFile();
 return listAllDirectories();
}

public
static File[] listAllDirectories(File file, FileFilter fileFilter,
 boolean boolean0) {
 if (!file.isDirectory()) {
 return new File[0];
 } else {
 std::vector arrayList = new ArrayList();
 listAllDirectoriesInternal(file, fileFilter, boolean0, arrayList);
 return arrayList.toArray(new File[0]);
 }
}

static void listAllDirectoriesInternal(File file0, FileFilter fileFilter,
 bool boolean0,
 ArrayList<File> arrayList) {
 File[] files = file0.listFiles();
 if (files != nullptr) {
 for (auto &file1 : files)
 if (!file1.isFile() && file1.isDirectory()) {
 if (fileFilter.accept(file1) {
 arrayList.add(file1);
 }

 if (boolean0) {
 listAllFilesInternal(file1, fileFilter, true, arrayList);
 }
 }
 }
}
}

public
static File[] listAllFiles(String string, FileFilter fileFilter,
 boolean boolean0) {
 File file = new File(string).getAbsoluteFile();
 return listAllFiles();
}

public
static File[] listAllFiles(File file, FileFilter fileFilter, boolean boolean0) {
 if (!file.isDirectory()) {
 return new File[0];
 } else {
 std::vector arrayList = new ArrayList();
 listAllFilesInternal(file, fileFilter, boolean0, arrayList);
 return arrayList.toArray(new File[0]);
 }
}

static void listAllFilesInternal(File file0, FileFilter fileFilter,
 bool boolean0, ArrayList<File> arrayList) {
 File[] files = file0.listFiles();
 if (files != nullptr) {
 for (auto &file1 : files)
 if (file1.isFile()) {
 if (fileFilter.accept(file1) {
 arrayList.add(file1);
 }
 } else if (file1.isDirectory() && boolean0) {
 listAllFilesInternal(file1, fileFilter, true, arrayList);
 }
 }
}
}

void walkGameAndModFiles(
 const std::string &string0, bool boolean0,
 ZomboidFileSystem.IWalkFilesVisitor iWalkFilesVisitor) {
 this->walkGameAndModFilesInternal(this->base, string0, boolean0,
 iWalkFilesVisitor);
 std::vector arrayList = this->getModIDs();

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 std::string string1 = this->getModDir((String)arrayList.get(int0);
 if (string1 != nullptr) {
 this->walkGameAndModFilesInternal(new File(string1), string0, boolean0,
 iWalkFilesVisitor);
 }
 }
}

void walkGameAndModFilesInternal(
 File file1, const std::string &string, bool boolean0,
 ZomboidFileSystem.IWalkFilesVisitor iWalkFilesVisitor) {
 File file0 = new File(file1, string);
 if (file0.isDirectory()) {
 File[] files = file0.listFiles();
 if (files != nullptr) {
 for (auto &file2 : files)
 iWalkFilesVisitor.visit(file2, string);
 if (boolean0 && file2.isDirectory()) {
 this->walkGameAndModFilesInternal(file1, string + "/" + file2.getName(),
 true, iWalkFilesVisitor);
 }
 }
 }
}
}

public
String[] resolveAllDirectories(String string, FileFilter fileFilter,
 boolean boolean0) {
 std::vector arrayList = new ArrayList();
 this->walkGameAndModFiles(
 string, boolean0, (file, string1)->{
 if (file.isDirectory() && fileFilter.accept(file) {
 std::string string0 = string1 + "/" + file.getName();
 if (!arrayList.contains(string0) {
 arrayList.add(string0);
 }
 }
 });
 return arrayList.toArray(new String[0]);
}

public
String[] resolveAllFiles(String string, FileFilter fileFilter,
 boolean boolean0) {
 std::vector arrayList = new ArrayList();
 this->walkGameAndModFiles(
 string, boolean0, (file, string1)->{
 if (file.isFile() && fileFilter.accept(file) {
 std::string string0 = string1 + "/" + file.getName();
 if (!arrayList.contains(string0) {
 arrayList.add(string0);
 }
 }
 });
 return arrayList.toArray(new String[0]);
}

std::string normalizeFolderPath(const std::string &string) {
 string = string.toLowerCase(Locale.ENGLISH).replace('\\', '/');
 string = string + "/";
 return string.replace("///", "/").replace("//", "/");
}

static std::string processFilePath(const std::string &string, char char0) {
 if (char0 != '\\') {
 string = string.replace('\\', char0);
 }

 if (char0 != '/') {
 string = string.replace('/', char0);
 }

 return string;
}

bool tryDeleteFile(const std::string &string) {
 if (StringUtils.isNullOrWhitespace(string) {
 return false;
 } else {
 try {
 return this->deleteFile(string);
 } catch (AccessControlException | IOException iOException) {
 ExceptionLogger.logException(
 iOException, String.format("Failed to delete file: \"%s\"", string),
 DebugLog.FileIO, LogSeverity.General);
 return false;
 }
 }
}

bool deleteFile(const std::string &string) {
 File file = new File(string).getAbsoluteFile();
 if (!file.isFile()) {
 throw FileNotFoundException(
 String.format("File path not found: \"%s\"", string);
 } else if (file.delete()) {
 DebugLog.FileIO.debugln("File deleted successfully: \"%s\"", string);
 return true;
 } else {
 DebugLog.FileIO.debugln("Failed to delete file: \"%s\"", string);
 return false;
 }
}

void update() {
 if (this->m_modsChangedTime != 0L) {
 long long0 = System.currentTimeMillis();
 if (this->m_modsChangedTime <= long0) {
 this->m_modsChangedTime = 0L;
 this->modFolders = nullptr;
 this->modIdToDir.clear();
 this->modDirToMod.clear();
 ChooseGameInfo.Reset();

 for (String string : this->getModIDs()) {
 ChooseGameInfo.getModDetails(string);
 }

 LuaEventManager.triggerEvent("OnModsModified");
 }
 }
}

bool isModFile(const std::string &string0) {
 if (this->m_modsChangedTime > 0L) {
 return false;
 } else if (this->modFolders.empty()) {
 return false;
 } else {
 string0 = string0.toLowerCase().replace('\\', '/');
 if (string0.endsWith("/mods/default.txt")) {
 return false;
 } else {
 for (int int0 = 0; int0 < this->modFolders.size(); int0++) {
 std::string string1 =
 this->modFolders.get(int0).toLowerCase().replace('\\', '/');
 if (string0.startsWith(string1) {
 return true;
 }
 }

 return false;
 }
 }
}

void onModFileChanged(const std::string &var1) {
 this->m_modsChangedTime = System.currentTimeMillis() + 2000L;
}

void cleanMultiplayerSaves() {
 DebugLog.FileIO.println("Start cleaning save fs");
 std::string string0 = this->getSaveDir();
 std::string string1 =
 string0 + File.separator + "Multiplayer" + File.separator;
 File file0 = new File(string1);
 if (!file0.exists()) {
 file0.mkdir();
 }

 try {
 File[] files = file0.listFiles();

 for (auto &file1 : files)
 DebugLog.FileIO.println("Checking " + file1.getAbsoluteFile() + " dir");
 if (file1.isDirectory()) {
 File file2 = new File(file1.toString() + File.separator + "map.bin");
 if (file2.exists()) {
 DebugLog.FileIO.println("Processing " + file1.getAbsoluteFile() +
 " dir");

 try {
 Stream stream = Files.walk(file1.toPath());
 stream.forEach(path->{
 if (path.getFileName().toString().matches("map_\\d+_\\d+.bin")) {
 DebugLog.FileIO.println("Delete " +
 path.getFileName().toString());
 path.toFile().delete();
 }
 });
 } catch (IOException iOException) {
 throw RuntimeException(iOException);
 }
 }
 }
 }
}
catch (RuntimeException runtimeException) {
 runtimeException.printStackTrace();
}
}

void resetDefaultModsForNewRelease(const std::string &string1) {
 ensureFolderExists(this->getCacheDirSub("mods"));
 std::string string0 = this->getCacheDirSub("mods") + File.separator +
 "reset-mods-" + string1 + ".txt";
 File file = new File(string0);
 if (!file.exists()) {
 try(FileWriter fileWriter = new FileWriter(file);
 BufferedWriter bufferedWriter = new BufferedWriter(fileWriter);) {
 std::string string2 = "If this file does not exist, default.txt will be "
 "reset to empty (no mods active).";
 bufferedWriter.write(string2);
 }
 catch (Exception exception) {
 ExceptionLogger.logException(exception);
 return;
 }

 ActiveMods activeMods = ActiveMods.getById("default");
 activeMods.clear();
 this->saveModsFile();
 }
}

public
interface IWalkFilesVisitor { void visit(File var1, const std::string &var2); }
}
} // namespace zombie
