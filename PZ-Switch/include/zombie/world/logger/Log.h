#pragma once
#include "zombie/world/ItemInfo.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace world {
namespace logger {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Log {
public:
public
 static class BaseItemLog extends Log.BaseLog {
 const ItemInfo itemInfo;

 public
 BaseItemLog(ItemInfo itemInfox) { this->itemInfo = itemInfox; }

 void saveAsText(FileWriter var1, String var2) throws IOException;

 std::string getItemString() {
 return "fulltype = \"" + this->itemInfo.getFullType() +
 "\", registeryID = " + this->itemInfo.getRegistryID() +
 ", existsVanilla = " + this->itemInfo.isExistsAsVanilla() +
 ", isModded = " + this->itemInfo.isModded() + ", modID = \"" +
 this->itemInfo.getModID() +
 "\", obsolete = " + this->itemInfo.isObsolete() +
 ", removed = " + this->itemInfo.isRemoved() +
 ", isLoaded = " + this->itemInfo.isLoaded();
 }
 }

public
 static class BaseLog {
 bool ignoreSaveCheck = false;

 bool isIgnoreSaveCheck() { return this->ignoreSaveCheck; }

 void saveAsText(FileWriter var1, String var2) throws IOException;
 }

 public static class Comment extends Log.BaseLog {
 std::string txt;

 public
 Comment(std::string_view string) {
 this->ignoreSaveCheck = true;
 this->txt = string;
 }

 void saveAsText(FileWriter fileWriter, std::string_view string) {
 fileWriter.write(string + "-- " + this->txt + System.lineSeparator());
 }
 }

public
 static class Info extends Log.BaseLog {
 protected
 List<String> mods;
 const std::string timeStamp;
 const std::string saveWorld;
 const int worldVersion;
 bool HasErrored = false;

 public
 Info(std::string_view string0, std::string_view string1, int int0,
 List<String> list) {
 this->ignoreSaveCheck = true;
 this->timeStamp = string0;
 this->saveWorld = string1;
 this->worldVersion = int0;
 this->mods = list;
 }

 void saveAsText(FileWriter fileWriter, std::string_view string) {
 fileWriter.write(string + "{" + System.lineSeparator());
 fileWriter.write(string + "\ttype = \"info\"," + System.lineSeparator());
 fileWriter.write(string + "\ttimeStamp = \"" + this->timeStamp + "\"," +
 System.lineSeparator());
 fileWriter.write(string + "\tsaveWorld = \"" + this->saveWorld + "\"," +
 System.lineSeparator());
 fileWriter.write(string + "\tworldVersion = " + this->worldVersion + "," +
 System.lineSeparator());
 fileWriter.write(string + "\thasErrored = " + this->HasErrored + "," +
 System.lineSeparator());
 fileWriter.write(string + "\titemMods = {" + System.lineSeparator());

 for (int int0 = 0; int0 < this->mods.size(); int0++) {
 fileWriter.write(string + "\t\t\"" + this->mods.get(int0) + "\"," +
 System.lineSeparator());
 }

 fileWriter.write(string + "\t}," + System.lineSeparator());
 fileWriter.write(string + "}," + System.lineSeparator());
 }
 }

public
 static class ModIDChangedItem extends Log.BaseItemLog {
 const std::string oldModID;
 const std::string newModID;

 public
 ModIDChangedItem(ItemInfo itemInfo, std::string_view string0,
 std::string_view string1) {
 super(itemInfo);
 this->oldModID = string0;
 this->newModID = string1;
 }

 void saveAsText(FileWriter fileWriter, std::string_view string) {
 fileWriter.write(string + "{ type = \"modchange_item\", oldModID = \"" +
 this->oldModID + "\", " + this->getItemString() + " }" +
 System.lineSeparator());
 }
 }

public
 static class ObsoleteItem extends Log.BaseItemLog {
 public
 ObsoleteItem(ItemInfo itemInfo) { super(itemInfo); }

 void saveAsText(FileWriter fileWriter, std::string_view string) {
 fileWriter.write(string + "{ type = \"obsolete_item\", " +
 this->getItemString() + " }" + System.lineSeparator());
 }
 }

public
 static class RegisterItem extends Log.BaseItemLog {
 public
 RegisterItem(ItemInfo itemInfo) { super(itemInfo); }

 void saveAsText(FileWriter fileWriter, std::string_view string) {
 fileWriter.write(string + "{ type = \"reg_item\", " +
 this->getItemString() + " }" + System.lineSeparator());
 }
 }

public
 static class RegisterObject extends Log.BaseLog {
 const std::string objectName;
 const int ID;

 public
 RegisterObject(std::string_view string, int int0) {
 this->objectName = string;
 this->ID = int0;
 }

 void saveAsText(FileWriter fileWriter, std::string_view string) {
 fileWriter.write(string + "{ type = \"reg_obj\", id = " + this->ID +
 ", obj = \"" + this->objectName + "\" }" +
 System.lineSeparator());
 }
 }

public
 static class ReinstateItem extends Log.BaseItemLog {
 public
 ReinstateItem(ItemInfo itemInfo) { super(itemInfo); }

 void saveAsText(FileWriter fileWriter, std::string_view string) {
 fileWriter.write(string + "{ type = \"reinstate_item\", " +
 this->getItemString() + " }" + System.lineSeparator());
 }
 }

public
 static class RemovedItem extends Log.BaseItemLog {
 const bool isScriptMissing;

 public
 RemovedItem(ItemInfo itemInfo, bool boolean0) {
 super(itemInfo);
 this->isScriptMissing = boolean0;
 }

 void saveAsText(FileWriter fileWriter, std::string_view string) {
 fileWriter.write(string + "{ type = \"removed_item\", scriptMissing = " +
 this->isScriptMissing + ", " + this->getItemString() +
 " }" + System.lineSeparator());
 }
 }
}
} // namespace logger
} // namespace world
} // namespace zombie
