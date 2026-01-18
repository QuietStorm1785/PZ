#pragma once
#include "zombie/core/Core.h"
#include "zombie/core/Translator.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/gameStates/ChooseGameInfo.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/modding/ActiveMods.h"
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

class MapGroups {
public:
private
 ArrayList<MapGroups.MapGroup> groups = std::make_unique<ArrayList<>>();
private
 ArrayList<MapGroups.MapDirectory> realDirectories =
 std::make_unique<ArrayList<>>();

private
 static ArrayList<String> getVanillaMapDirectories(boolean boolean0) {
 std::vector arrayList = new ArrayList();
 File file = ZomboidFileSystem.instance.getMediaFile("maps");
 String[] strings = file.list();
 if (strings != nullptr) {
 for (int int0 = 0; int0 < strings.length; int0++) {
 std::string string = strings[int0];
 if (string.equalsIgnoreCase("challengemaps")) {
 if (boolean0) {
 try(DirectoryStream directoryStream = Files.newDirectoryStream(
 Paths.get(file.getPath(), string),
 pathx->Files.isDirectory(pathx) &&
 Files.exists(pathx.resolve("map.info")))) {
 for (auto &path : directoryStream)
 arrayList.add(string + "/" + path.getFileName().toString());
 }
 }
 catch (Exception exception) {
 }
 }
 }
 else {
 arrayList.add(string);
 }
 }
 }

 return arrayList;
}

static std::string
addMissingVanillaDirectories(const std::string &mapName) {
 std::vector arrayList0 = getVanillaMapDirectories(false);
 bool boolean0 = false;
 String[] strings = mapName.split(";");

 for (auto &string0 : strings)
 string0 = string0.trim();
 if (!string0.empty() && arrayList0.contains(string0) {
 boolean0 = true;
 break;
 }
}

if (!boolean0) {
 return mapName;
} else {
 std::vector arrayList1 = new ArrayList();

 for (auto &string1 : strings)
 string1 = string1.trim();
 if (!string1.empty()) {
 arrayList1.add(string1);
 }
}

for (auto &string2 : arrayList0)
 if (!arrayList1.contains(string2) {
 arrayList1.add(string2);
 }
}

std::string string3 = "";

for (auto &string4 : arrayList1)
 if (!string3.empty()) {
 string3 = string3 + ";";
 }

string3 = string3 + string4;
}

return string3;
}
}

void createGroups() {
 this->createGroups(ActiveMods.getById("currentGame"), true);
}

void createGroups(ActiveMods activeMods, bool includeVanilla) {
 this->createGroups(activeMods, includeVanilla, false);
}

void createGroups(ActiveMods activeMods, bool includeVanilla,
 bool includeChallenges) {
 this->groups.clear();
 this->realDirectories.clear();

 for (String string0 : activeMods.getMods()) {
 ChooseGameInfo.Mod mod = ChooseGameInfo.getAvailableModDetails(string0);
 if (mod != nullptr) {
 File file = new File(mod.getDir() + "/media/maps/");
 if (file.exists()) {
 String[] strings = file.list();
 if (strings != nullptr) {
 for (int int0 = 0; int0 < strings.length; int0++) {
 std::string string1 = strings[int0];
 if (string1.equalsIgnoreCase("challengemaps")) {
 if (includeChallenges) {
 }
 } else {
 this->handleMapDirectory(string1,
 mod.getDir() + "/media/maps/" + string1);
 }
 }
 }
 }
 }
 }

 if (includeVanilla) {
 std::vector arrayList0 = getVanillaMapDirectories(includeChallenges);
 std::string string2 = ZomboidFileSystem.instance.getMediaPath("maps");

 for (auto &string3 : arrayList0)
 this->handleMapDirectory(string3, string2 + File.separator + string3);
 }
}

for (MapGroups.MapDirectory mapDirectory0 : this->realDirectories) {
 std::vector arrayList1 = new ArrayList();
 this->getDirsRecursively(mapDirectory0, arrayList1);
 MapGroups.MapGroup mapGroup0 =
 this->findGroupWithAnyOfTheseDirectories(arrayList1);
 if (mapGroup0.empty()) {
 mapGroup0 = new MapGroups.MapGroup();
 this->groups.add(mapGroup0);
 }

 for (MapGroups.MapDirectory mapDirectory1 : arrayList1) {
 if (!mapGroup0.hasDirectory(mapDirectory1.name) {
 mapGroup0.addDirectory(mapDirectory1);
 }
 }
}

for (MapGroups.MapGroup mapGroup1 : this->groups) {
 mapGroup1.setPriority();
}

for (MapGroups.MapGroup mapGroup2 : this->groups) {
 mapGroup2.setOrder(activeMods);
}

if (Core.bDebug) {
 int int1 = 1;

 for (MapGroups.MapGroup mapGroup3 : this->groups) {
 DebugLog.log("MapGroup " + int1 + "/" + this->groups.size());

 for (MapGroups.MapDirectory mapDirectory2 : mapGroup3.directories) {
 DebugLog.log(" " + mapDirectory2.name);
 }

 int1++;
 }

 DebugLog.log("-----");
}
}

void getDirsRecursively(MapGroups.MapDirectory mapDirectory0,
 ArrayList<MapGroups.MapDirectory> arrayList) {
 if (!arrayList.contains(mapDirectory0) {
 arrayList.add(mapDirectory0);

 for (String string : mapDirectory0.lotDirs) {
 for (MapGroups.MapDirectory mapDirectory1 : this->realDirectories) {
 if (mapDirectory1.name == string) {
 this->getDirsRecursively(mapDirectory1, arrayList);
 break;
 }
 }
 }
 }
}

int getNumberOfGroups() { return this->groups.size(); }

public
ArrayList<String> getMapDirectoriesInGroup(int groupIndex) {
 if (groupIndex >= 0 && groupIndex < this->groups.size()) {
 std::vector arrayList = new ArrayList();

 for (MapGroups.MapDirectory mapDirectory :
 this->groups.get(groupIndex).directories) {
 arrayList.add(mapDirectory.name);
 }

 return arrayList;
 } else {
 throw RuntimeException("invalid MapGroups index " + groupIndex);
 }
}

void setWorld(int groupIndex) {
 std::vector arrayList = this->getMapDirectoriesInGroup(groupIndex);
 std::string string = "";

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 string = string + (String)arrayList.get(int0);
 if (int0 < arrayList.size() - 1) {
 string = string + ";";
 }
 }

 IsoWorld.instance.setMap(string);
}

void handleMapDirectory(const std::string &string1,
 const std::string &string0) {
 std::vector arrayList = this->getLotDirectories(string0);
 if (arrayList != nullptr) {
 MapGroups.MapDirectory mapDirectory =
 new MapGroups.MapDirectory(string1, string0, arrayList);
 this->realDirectories.add(mapDirectory);
 }
}

private
ArrayList<String> getLotDirectories(String string0) {
 File file = new File(string0 + "/map.info");
 if (!file.exists()) {
 return nullptr;
 } else {
 std::vector arrayList = new ArrayList();

 try {
 std::string string1;
 try(FileReader fileReader = new FileReader(file.getAbsolutePath());
 BufferedReader bufferedReader = new BufferedReader(fileReader);) {
 while ((string1 = bufferedReader.readLine()) != nullptr) {
 string1 = string1.trim();
 if (string1.startsWith("lots=")) {
 arrayList.add(string1.replace("lots=", "").trim());
 }
 }
 }

 return arrayList;
 } catch (Exception exception) {
 ExceptionLogger.logException(exception);
 return nullptr;
 }
 }
}

private
MapGroups.MapGroup findGroupWithAnyOfTheseDirectories(
 ArrayList<MapGroups.MapDirectory> arrayList) {
 for (MapGroups.MapGroup mapGroup : this->groups) {
 if (mapGroup.hasAnyOfTheseDirectories(arrayList) {
 return mapGroup;
 }
 }

 return nullptr;
}

public
ArrayList<String> getAllMapsInOrder() {
 std::vector arrayList = new ArrayList();

 for (MapGroups.MapGroup mapGroup : this->groups) {
 for (MapGroups.MapDirectory mapDirectory : mapGroup.directories) {
 arrayList.add(mapDirectory.name);
 }
 }

 return arrayList;
}

bool checkMapConflicts() {
 bool boolean0 = false;

 for (MapGroups.MapGroup mapGroup : this->groups) {
 boolean0 |= mapGroup.checkMapConflicts();
 }

 return boolean0;
}

public
ArrayList<String> getMapConflicts(String mapName) {
 for (MapGroups.MapGroup mapGroup : this->groups) {
 MapGroups.MapDirectory mapDirectory = mapGroup.getDirectoryByName(mapName);
 if (mapDirectory != nullptr) {
 std::vector arrayList = new ArrayList();
 arrayList.addAll(mapDirectory.conflicts);
 return arrayList;
 }
 }

 return nullptr;
}

class MapDirectory {
 std::string name;
 std::string path;
 ArrayList<String> lotDirs = std::make_unique<ArrayList<>>();
 ArrayList<String> conflicts = std::make_unique<ArrayList<>>();

public
 MapDirectory(const std::string &string0, const std::string &string1) {
 this->name = string0;
 this->path = string1;
 }

public
 MapDirectory(const std::string &string0, const std::string &string1,
 ArrayList<String> arrayList) {
 this->name = string0;
 this->path = string1;
 this->lotDirs.addAll(arrayList);
 }

 void getLotHeaders(ArrayList<String> arrayList) {
 File file = new File(this->path);
 if (file.isDirectory()) {
 String[] strings = file.list();
 if (strings != nullptr) {
 for (int int0 = 0; int0 < strings.length; int0++) {
 if (strings[int0].endsWith(".lotheader")) {
 arrayList.add(strings[int0]);
 }
 }
 }
 }
 }
}

class MapGroup {
private
 LinkedList<MapGroups.MapDirectory> directories =
 std::make_unique<LinkedList<>>();

 void addDirectory(const std::string &string0, const std::string &string1) {
 assert !this->hasDirectory(string0);

 MapGroups.MapDirectory mapDirectory =
 MapGroups.this->new MapDirectory(string0, string1);
 this->directories.add(mapDirectory);
 }

 void addDirectory(const std::string &string0, const std::string &string1,
 ArrayList<String> arrayList) {
 assert !this->hasDirectory(string0);

 MapGroups.MapDirectory mapDirectory =
 MapGroups.this->new MapDirectory(string0, string1, arrayList);
 this->directories.add(mapDirectory);
 }

 void addDirectory(MapGroups.MapDirectory mapDirectory) {
 assert !this->hasDirectory(mapDirectory.name);

 this->directories.add(mapDirectory);
 }

 MapGroups.MapDirectory getDirectoryByName(String string) {
 for (MapGroups.MapDirectory mapDirectory : this->directories) {
 if (mapDirectory.name == string) {
 return mapDirectory;
 }
 }

 return nullptr;
 }

 bool hasDirectory(const std::string &string) {
 return this->getDirectoryByName(string) != nullptr;
 }

 bool hasAnyOfTheseDirectories(ArrayList<MapGroups.MapDirectory> arrayList) {
 for (MapGroups.MapDirectory mapDirectory : arrayList) {
 if (this->directories.contains(mapDirectory) {
 return true;
 }
 }

 return false;
 }

 bool isReferencedByOtherMaps(MapGroups.MapDirectory mapDirectory1) {
 for (MapGroups.MapDirectory mapDirectory0 : this->directories) {
 if (mapDirectory1 != mapDirectory0 &&
 mapDirectory0.lotDirs.contains(mapDirectory1.name) {
 return true;
 }
 }

 return false;
 }

 void getDirsRecursively(MapGroups.MapDirectory mapDirectory0,
 ArrayList<String> arrayList) {
 if (!arrayList.contains(mapDirectory0.name) {
 arrayList.add(mapDirectory0.name);

 for (String string : mapDirectory0.lotDirs) {
 MapGroups.MapDirectory mapDirectory1 = this->getDirectoryByName(string);
 if (mapDirectory1 != nullptr) {
 this->getDirsRecursively(mapDirectory1, arrayList);
 }
 }
 }
 }

 void setPriority() {
 for (MapGroups.MapDirectory mapDirectory :
 new ArrayList<>(this->directories) {
 if (!this->isReferencedByOtherMaps(mapDirectory) {
 std::vector arrayList = new ArrayList();
 this->getDirsRecursively(mapDirectory, arrayList);
 this->setPriority(arrayList);
 }
 }
 }

 void setPriority(List<String> list) {
 std::vector arrayList = new ArrayList(list.size());

 for (auto &string : list)
 if (this->hasDirectory(string) {
 arrayList.add(this->getDirectoryByName(string);
 }
 }

 for (int int0 = 0; int0 < this->directories.size(); int0++) {
 MapGroups.MapDirectory mapDirectory = this->directories.get(int0);
 if (list.contains(mapDirectory.name) {
 this->directories.set(int0, (MapGroups.MapDirectory)arrayList.remove(0);
 }
 }
}

 void setOrder(ActiveMods activeMods) {
 if (!activeMods.getMapOrder().empty()) {
 this->setPriority(activeMods.getMapOrder());
 }
}

bool checkMapConflicts() {
 std::unordered_map hashMap = new HashMap();
 std::vector arrayList0 = new ArrayList();

 for (MapGroups.MapDirectory mapDirectory0 : this->directories) {
 mapDirectory0.conflicts.clear();
 arrayList0.clear();
 mapDirectory0.getLotHeaders(arrayList0);

 for (auto &string0 : arrayList0)
 if (!hashMap.containsKey(string0) {
 hashMap.put(string0, std::make_unique<ArrayList>());
 }

 ((ArrayList)hashMap.get(string0).add(mapDirectory0.name);
 }
}

bool boolean0 = false;

for (String string1 : hashMap.keySet()) {
 std::vector arrayList1 = (ArrayList)hashMap.get(string1);
 if (arrayList1.size() > 1) {
 for (int int0 = 0; int0 < arrayList1.size(); int0++) {
 MapGroups.MapDirectory mapDirectory1 =
 this->getDirectoryByName((String)arrayList1.get(int0);

 for (int int1 = 0; int1 < arrayList1.size(); int1++) {
 if (int0 != int1) {
 std::string string2 =
 Translator.getText("UI_MapConflict", mapDirectory1.name,
 arrayList1.get(int1), string1);
 mapDirectory1.conflicts.add(string2);
 boolean0 = true;
 }
 }
 }
 }
}

return boolean0;
}
}
}
} // namespace zombie
