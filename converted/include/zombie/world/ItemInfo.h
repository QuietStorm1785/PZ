#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameWindow.h"
#include "zombie/core/utils/Bits.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/scripting/objects/Item.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace world {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ItemInfo {
public:
 std::string itemName;
 std::string moduleName;
 std::string fullType;
 short registryID;
 bool existsAsVanilla = false;
 bool isModded = false;
 std::string modID;
 bool obsolete = false;
 bool removed = false;
 bool isLoaded = false;
 protected List<String> modOverrides;
 Item scriptItem;

 std::string getFullType() {
 return this->fullType;
 }

 short getRegistryID() {
 return this->registryID;
 }

 bool isExistsAsVanilla() {
 return this->existsAsVanilla;
 }

 bool isModded() {
 return this->isModded;
 }

 std::string getModID() {
 return this->modID;
 }

 bool isObsolete() {
 return this->obsolete;
 }

 bool isRemoved() {
 return this->removed;
 }

 bool isLoaded() {
 return this->isLoaded;
 }

 Item getScriptItem() {
 return this->scriptItem;
 }

 public List<String> getModOverrides() {
 return this->modOverrides;
 }

 ItemInfo copy() {
 ItemInfo itemInfo0 = new ItemInfo();
 itemInfo0.fullType = this->fullType;
 itemInfo0.registryID = this->registryID;
 itemInfo0.existsAsVanilla = this->existsAsVanilla;
 itemInfo0.isModded = this->isModded;
 itemInfo0.modID = this->modID;
 itemInfo0.obsolete = this->obsolete;
 itemInfo0.removed = this->removed;
 itemInfo0.isLoaded = this->isLoaded;
 itemInfo0.scriptItem = this->scriptItem;
 if (this->modOverrides != nullptr) {
 itemInfo0.modOverrides = std::make_unique<ArrayList<>>();
 itemInfo0.modOverrides.addAll(this->modOverrides);
 }

 return itemInfo0;
 }

 bool isValid() {
 return !this->obsolete && !this->removed && this->isLoaded;
 }

 void DebugPrint() {
 DebugLog.log(this->GetDebugString());
 }

 std::string GetDebugString() {
 String string = "=== Dictionary Item Debug Print ===\nregistryID = "
 + this->registryID
 + ",\nfulltype = \""
 + this->fullType
 + "\",\nmodID = \""
 + this->modID
 + "\",\nexistsAsVanilla = "
 + this->existsAsVanilla
 + ",\nisModded = "
 + this->isModded
 + ",\nobsolete = "
 + this->obsolete
 + ",\nremoved = "
 + this->removed
 + ",\nisModdedOverride = "
 + (this->modOverrides != nullptr ? this->modOverrides.size() : 0)
 + ",\n";
 if (this->modOverrides != nullptr) {
 string = string + "modOverrides = { ";
 if (this->existsAsVanilla) {
 string = string + "PZ-Vanilla, ";
 }

 for (int int0 = 0; int0 < this->modOverrides.size(); int0++) {
 string = string + "\"" + this->modOverrides.get(int0) + "\"";
 if (int0 < this->modOverrides.size() - 1) {
 string = string + ", ";
 }
 }

 string = string + " },\n";
 }

 return string + "===================================\n";
 }

 std::string ToString() {
 return "registryID = "
 + this->registryID
 + ",fulltype = \""
 + this->fullType
 + "\",modID = \""
 + this->modID
 + "\",existsAsVanilla = "
 + this->existsAsVanilla
 + ",isModded = "
 + this->isModded
 + ",obsolete = "
 + this->obsolete
 + ",removed = "
 + this->removed
 + ",modOverrides = "
 + (this->modOverrides != nullptr ? this->modOverrides.size() : 0)
 + ",";
 }

 void saveAsText(FileWriter fileWriter, const std::string& string0) {
 fileWriter.write(string0 + "registryID = " + this->registryID + "," + System.lineSeparator());
 fileWriter.write(string0 + "fulltype = \"" + this->fullType + "\"," + System.lineSeparator());
 fileWriter.write(string0 + "modID = \"" + this->modID + "\"," + System.lineSeparator());
 fileWriter.write(string0 + "existsAsVanilla = " + this->existsAsVanilla + "," + System.lineSeparator());
 fileWriter.write(string0 + "isModded = " + this->isModded + "," + System.lineSeparator());
 fileWriter.write(string0 + "obsolete = " + this->obsolete + "," + System.lineSeparator());
 fileWriter.write(string0 + "removed = " + this->removed + "," + System.lineSeparator());
 if (this->modOverrides != nullptr) {
 std::string string1 = "modOverrides = { ";

 for (int int0 = 0; int0 < this->modOverrides.size(); int0++) {
 string1 = string1 + "\"" + this->modOverrides.get(int0) + "\"";
 if (int0 < this->modOverrides.size() - 1) {
 string1 = string1 + ", ";
 }
 }

 string1 = string1 + " },";
 fileWriter.write(string0 + string1 + System.lineSeparator());
 }
 }

 void save(ByteBuffer byteBuffer, List<String> list1, List<String> list0) {
 byteBuffer.putShort(this->registryID);
 if (list0.size() > 127) {
 byteBuffer.putShort((short)list0.indexOf(this->moduleName);
 } else {
 byteBuffer.put((byte)list0.indexOf(this->moduleName);
 }

 GameWindow.WriteString(byteBuffer, this->itemName);
 uint8_t byte0 = 0;
 int int0 = byteBuffer.position();
 byteBuffer.put((byte)0);
 if (this->isModded) {
 byte0 = Bits.addFlags(byte0, 1);
 if (list1.size() > 127) {
 byteBuffer.putShort((short)list1.indexOf(this->modID);
 } else {
 byteBuffer.put((byte)list1.indexOf(this->modID);
 }
 }

 if (this->existsAsVanilla) {
 byte0 = Bits.addFlags(byte0, 2);
 }

 if (this->obsolete) {
 byte0 = Bits.addFlags(byte0, 4);
 }

 if (this->removed) {
 byte0 = Bits.addFlags(byte0, 8);
 }

 if (this->modOverrides != nullptr) {
 byte0 = Bits.addFlags(byte0, 16);
 if (this->modOverrides.size() == 1) {
 if (list1.size() > 127) {
 byteBuffer.putShort((short)list1.indexOf(this->modOverrides.get(0);
 } else {
 byteBuffer.put((byte)list1.indexOf(this->modOverrides.get(0);
 }
 } else {
 byte0 = Bits.addFlags(byte0, 32);
 byteBuffer.put((byte)this->modOverrides.size());

 for (int int1 = 0; int1 < this->modOverrides.size(); int1++) {
 if (list1.size() > 127) {
 byteBuffer.putShort((short)list1.indexOf(this->modOverrides.get(int1);
 } else {
 byteBuffer.put((byte)list1.indexOf(this->modOverrides.get(int1);
 }
 }
 }
 }

 int int2 = byteBuffer.position();
 byteBuffer.position(int0);
 byteBuffer.put(byte0);
 byteBuffer.position(int2);
 }

 void load(ByteBuffer byteBuffer, int var2, List<String> list1, List<String> list0) {
 this->registryID = byteBuffer.getShort();
 this->moduleName = (String)list0.get(list0.size() > 127 ? byteBuffer.getShort() : byteBuffer.get());
 this->itemName = GameWindow.ReadString(byteBuffer);
 this->fullType = this->moduleName + "." + this->itemName;
 uint8_t byte0 = byteBuffer.get();
 if (Bits.hasFlags(byte0, 1) {
 this->modID = (String)list1.get(list1.size() > 127 ? byteBuffer.getShort() : byteBuffer.get());
 this->isModded = true;
 } else {
 this->modID = "pz-vanilla";
 this->isModded = false;
 }

 this->existsAsVanilla = Bits.hasFlags(byte0, 2);
 this->obsolete = Bits.hasFlags(byte0, 4);
 this->removed = Bits.hasFlags(byte0, 8);
 if (Bits.hasFlags(byte0, 16) {
 if (this->modOverrides == nullptr) {
 this->modOverrides = std::make_unique<ArrayList<>>();
 }

 this->modOverrides.clear();
 if (!Bits.hasFlags(byte0, 32) {
 this->modOverrides.add((String)list1.get(list1.size() > 127 ? byteBuffer.getShort() : byteBuffer.get()));
 } else {
 uint8_t byte1 = byteBuffer.get();

 for (int int0 = 0; int0 < byte1; int0++) {
 this->modOverrides.add((String)list1.get(list1.size() > 127 ? byteBuffer.getShort() : byteBuffer.get()));
 }
 }
 }
 }
}
} // namespace world
} // namespace zombie
