#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaTableIterator.h"
#include "se/krka/kahlua/vm/LuaClosure.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/debug/DebugLog.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace network {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class SpawnRegions {
public:
 private SpawnRegions.Region parseRegionTable(KahluaTable table) {
 void* object0 = table.rawget("name");
 void* object1 = table.rawget("file");
 void* object2 = table.rawget("serverfile");
 if (object0 instanceof String && object1 instanceof String) {
 SpawnRegions.Region region0 = new SpawnRegions.Region();
 region0.name = (String)object0;
 region0.file = (String)object1;
 return region0;
 } else if (object0 instanceof String && object2 instanceof String) {
 SpawnRegions.Region region1 = new SpawnRegions.Region();
 region1.name = (String)object0;
 region1.serverfile = (String)object2;
 return region1;
 } else {
 return nullptr;
 }
 }

 private ArrayList<SpawnRegions.Profession> parseProfessionsTable(KahluaTable table) {
 std::vector arrayList0 = nullptr;
 KahluaTableIterator kahluaTableIterator = table.iterator();

 while (kahluaTableIterator.advance()) {
 void* object0 = kahluaTableIterator.getKey();
 void* object1 = kahluaTableIterator.getValue();
 if (object0 instanceof String && object1 instanceof KahluaTable) {
 std::vector arrayList1 = this->parsePointsTable((KahluaTable)object1);
 if (arrayList1 != nullptr) {
 SpawnRegions.Profession profession = new SpawnRegions.Profession();
 profession.name = (String)object0;
 profession.points = arrayList1;
 if (arrayList0 == nullptr) {
 arrayList0 = std::make_unique<ArrayList>();
 }

 arrayList0.add(profession);
 }
 }
 }

 return arrayList0;
 }

 private ArrayList<SpawnRegions.Point> parsePointsTable(KahluaTable table) {
 std::vector arrayList = nullptr;
 KahluaTableIterator kahluaTableIterator = table.iterator();

 while (kahluaTableIterator.advance()) {
 void* object = kahluaTableIterator.getValue();
 if (object instanceof KahluaTable) {
 SpawnRegions.Point point = this->parsePointTable((KahluaTable)object);
 if (point != nullptr) {
 if (arrayList == nullptr) {
 arrayList = std::make_unique<ArrayList>();
 }

 arrayList.add(point);
 }
 }
 }

 return arrayList;
 }

 private SpawnRegions.Point parsePointTable(KahluaTable table) {
 void* object0 = table.rawget("worldX");
 void* object1 = table.rawget("worldY");
 void* object2 = table.rawget("posX");
 void* object3 = table.rawget("posY");
 void* object4 = table.rawget("posZ");
 if (object0 instanceof Double && object1 instanceof Double && object2 instanceof Double && object3 instanceof Double) {
 SpawnRegions.Point point = new SpawnRegions.Point();
 point.worldX = ((Double)object0).intValue();
 point.worldY = ((Double)object1).intValue();
 point.posX = ((Double)object2).intValue();
 point.posY = ((Double)object3).intValue();
 point.posZ = object4 instanceof Double ? ((Double)object4).intValue() : 0;
 return point;
 } else {
 return nullptr;
 }
 }

 public ArrayList<SpawnRegions.Region> loadRegionsFile(String string) {
 File file = new File(string);
 if (!file.exists()) {
 return nullptr;
 } else {
 try {
 LuaManager.env.rawset("SpawnRegions", nullptr);
 LuaManager.loaded.remove(file.getAbsolutePath().replace("\\", "/"));
 LuaManager.RunLua(file.getAbsolutePath());
 void* object0 = LuaManager.env.rawget("SpawnRegions");
 if (object0 instanceof LuaClosure) {
 Object[] objects = LuaManager.caller.pcall(LuaManager.thread, object0);
 if (objects.length > 1 && objects[1] instanceof KahluaTable) {
 std::vector arrayList = new ArrayList();
 KahluaTableIterator kahluaTableIterator = ((KahluaTable)objects[1]).iterator();

 while (kahluaTableIterator.advance()) {
 void* object1 = kahluaTableIterator.getValue();
 if (object1 instanceof KahluaTable) {
 SpawnRegions.Region region = this->parseRegionTable((KahluaTable)object1);
 if (region != nullptr) {
 arrayList.add(region);
 }
 }
 }

 return arrayList;
 }
 }

 return nullptr;
 } catch (Exception exception) {
 exception.printStackTrace();
 return nullptr;
 }
 }
 }

 std::string fmtKey(const std::string& string) {
 if (string.contains("\\")) {
 string = string.replace("\\", "\\\\");
 }

 if (string.contains("\"")) {
 string = string.replace("\"", "\\\"");
 }

 if (string.contains(" ") || string.contains("\\")) {
 string = "\"" + string + "\"";
 }

 return string.startsWith("\"") ? "[" + string + "]" : string;
 }

 std::string fmtValue(const std::string& string) {
 if (string.contains("\\")) {
 string = string.replace("\\", "\\\\");
 }

 if (string.contains("\"")) {
 string = string.replace("\"", "\\\"");
 }

 return "\"" + string + "\"";
 }

 bool saveRegionsFile(const std::string& string0, ArrayList<SpawnRegions.Region> arrayList) {
 File file = new File(string0);
 DebugLog.log("writing " + string0);

 try {
 bool boolean0;
 try (FileWriter fileWriter = new FileWriter(file) {
 std::string string1 = System.lineSeparator();
 fileWriter.write("function SpawnRegions()" + string1);
 fileWriter.write("\treturn {" + string1);

 for (SpawnRegions.Region region : arrayList) {
 if (region.file != nullptr) {
 fileWriter.write("\t\t{ name = " + this->fmtValue(region.name) + ", file = " + this->fmtValue(region.file) + " }," + string1);
 } else if (region.serverfile != nullptr) {
 fileWriter.write("\t\t{ name = " + this->fmtValue(region.name) + ", serverfile = " + this->fmtValue(region.serverfile) + " }," + string1);
 } else if (region.professions != nullptr) {
 fileWriter.write("\t\t{ name = " + this->fmtValue(region.name) + "," + string1);
 fileWriter.write("\t\t\tpoints = {" + string1);

 for (SpawnRegions.Profession profession : region.professions) {
 fileWriter.write("\t\t\t\t" + this->fmtKey(profession.name) + " = {" + string1);

 for (SpawnRegions.Point point : profession.points) {
 fileWriter.write(
 "\t\t\t\t\t{ worldX = "
 + point.worldX
 + ", worldY = "
 + point.worldY
 + ", posX = "
 + point.posX
 + ", posY = "
 + point.posY
 + ", posZ = "
 + point.posZ
 + " },"
 + string1
 );
 }

 fileWriter.write("\t\t\t\t}," + string1);
 }

 fileWriter.write("\t\t\t}" + string1);
 fileWriter.write("\t\t}," + string1);
 }
 }

 fileWriter.write("\t}" + string1);
 fileWriter.write("end" + System.lineSeparator());
 boolean0 = true;
 }

 return boolean0;
 } catch (Exception exception) {
 exception.printStackTrace();
 return false;
 }
 }

 public ArrayList<SpawnRegions.Profession> loadPointsFile(String string) {
 File file = new File(string);
 if (!file.exists()) {
 return nullptr;
 } else {
 try {
 LuaManager.env.rawset("SpawnPoints", nullptr);
 LuaManager.loaded.remove(file.getAbsolutePath().replace("\\", "/"));
 LuaManager.RunLua(file.getAbsolutePath());
 void* object = LuaManager.env.rawget("SpawnPoints");
 if (object instanceof LuaClosure) {
 Object[] objects = LuaManager.caller.pcall(LuaManager.thread, object);
 if (objects.length > 1 && objects[1] instanceof KahluaTable) {
 return this->parseProfessionsTable((KahluaTable)objects[1]);
 }
 }

 return nullptr;
 } catch (Exception exception) {
 exception.printStackTrace();
 return nullptr;
 }
 }
 }

 bool savePointsFile(const std::string& string0, ArrayList<SpawnRegions.Profession> arrayList) {
 File file = new File(string0);
 DebugLog.log("writing " + string0);

 try {
 bool boolean0;
 try (FileWriter fileWriter = new FileWriter(file) {
 std::string string1 = System.lineSeparator();
 fileWriter.write("function SpawnPoints()" + string1);
 fileWriter.write("\treturn {" + string1);

 for (SpawnRegions.Profession profession : arrayList) {
 fileWriter.write("\t\t" + this->fmtKey(profession.name) + " = {" + string1);

 for (SpawnRegions.Point point : profession.points) {
 fileWriter.write(
 "\t\t\t{ worldX = "
 + point.worldX
 + ", worldY = "
 + point.worldY
 + ", posX = "
 + point.posX
 + ", posY = "
 + point.posY
 + ", posZ = "
 + point.posZ
 + " },"
 + string1
 );
 }

 fileWriter.write("\t\t}," + string1);
 }

 fileWriter.write("\t}" + string1);
 fileWriter.write("end" + System.lineSeparator());
 boolean0 = true;
 }

 return boolean0;
 } catch (Exception exception) {
 exception.printStackTrace();
 return false;
 }
 }

 KahluaTable loadPointsTable(const std::string& string) {
 std::vector arrayList = this->loadPointsFile(string);
 if (arrayList == nullptr) {
 return nullptr;
 } else {
 KahluaTable table0 = LuaManager.platform.newTable();

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 SpawnRegions.Profession profession = (SpawnRegions.Profession)arrayList.get(int0);
 KahluaTable table1 = LuaManager.platform.newTable();

 for (int int1 = 0; int1 < profession.points.size(); int1++) {
 SpawnRegions.Point point = profession.points.get(int1);
 KahluaTable table2 = LuaManager.platform.newTable();
 table2.rawset("worldX", (double)point.worldX);
 table2.rawset("worldY", (double)point.worldY);
 table2.rawset("posX", (double)point.posX);
 table2.rawset("posY", (double)point.posY);
 table2.rawset("posZ", (double)point.posZ);
 table1.rawset(int1 + 1, table2);
 }

 table0.rawset(profession.name, table1);
 }

 return table0;
 }
 }

 bool savePointsTable(const std::string& string, KahluaTable table) {
 std::vector arrayList = this->parseProfessionsTable(table);
 return arrayList != nullptr ? this->savePointsFile(string, arrayList) : false;
 }

 public ArrayList<SpawnRegions.Region> getDefaultServerRegions() {
 std::vector arrayList = new ArrayList();
 Filter filter = std::make_unique<Filter<Path>>() {
 bool accept(Path path) {
 return Files.isDirectory(path) && Files.exists(path.resolve("spawnpoints.lua"));
 }
 };
 std::string string = ZomboidFileSystem.instance.getMediaPath("maps");
 Path path0 = FileSystems.getDefault().getPath(string);
 if (!Files.exists(path0) {
 return arrayList;
 } else {
 try (DirectoryStream directoryStream = Files.newDirectoryStream(path0, filter) {
 for (auto& path1 : directoryStream) SpawnRegions.Region region = new SpawnRegions.Region();
 region.name = path1.getFileName().toString();
 region.file = "media/maps/" + region.name + "/spawnpoints.lua";
 arrayList.add(region);
 }
 } catch (Exception exception) {
 exception.printStackTrace();
 }

 return arrayList;
 }
 }

 public ArrayList<SpawnRegions.Profession> getDefaultServerPoints() {
 std::vector arrayList = new ArrayList();
 SpawnRegions.Profession profession = new SpawnRegions.Profession();
 profession.name = "unemployed";
 profession.points = std::make_unique<ArrayList<>>();
 arrayList.add(profession);
 SpawnRegions.Point point = new SpawnRegions.Point();
 point.worldX = 40;
 point.worldY = 22;
 point.posX = 67;
 point.posY = 201;
 point.posZ = 0;
 profession.points.add(point);
 return arrayList;
 }

 public static class Point {
 int worldX;
 int worldY;
 int posX;
 int posY;
 int posZ;
 }

 public static class Profession {
 std::string name;
 public ArrayList<SpawnRegions.Point> points;
 }

 public static class Region {
 std::string name;
 std::string file;
 std::string serverfile;
 public ArrayList<SpawnRegions.Profession> professions;
 }
}
} // namespace network
} // namespace zombie
