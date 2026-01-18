#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameWindow.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/iso/SliceY.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/Item.h"
#include "zombie/worldMap/symbols/WorldMapSymbols.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace inventory {
namespace types {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class MapItem : public InventoryItem {
public:
 static MapItem WORLD_MAP_INSTANCE;
 private static byte[] FILE_MAGIC = new byte[]{87, 77, 83, 89};
 std::string m_mapID;
 const WorldMapSymbols m_symbols = new WorldMapSymbols();

 static MapItem getSingleton() {
 if (WORLD_MAP_INSTANCE.empty()) {
 Item item = ScriptManager.instance.FindItem("Base.Map");
 if (item.empty()) {
 return nullptr;
 }

 WORLD_MAP_INSTANCE = new MapItem("Base", "World Map", "WorldMap", item);
 }

 return WORLD_MAP_INSTANCE;
 }

 static void SaveWorldMap() {
 if (WORLD_MAP_INSTANCE != nullptr) {
 try {
 ByteBuffer byteBuffer = SliceY.SliceBuffer;
 byteBuffer.clear();
 byteBuffer.put(FILE_MAGIC);
 byteBuffer.putInt(195);
 WORLD_MAP_INSTANCE.getSymbols().save(byteBuffer);
 File file = new File(ZomboidFileSystem.instance.getFileNameInCurrentSave("map_symbols.bin"));

 try (
 FileOutputStream fileOutputStream = new FileOutputStream(file);
 BufferedOutputStream bufferedOutputStream = new BufferedOutputStream(fileOutputStream);
 ) {
 bufferedOutputStream.write(byteBuffer.array(), 0, byteBuffer.position());
 }
 } catch (Exception exception) {
 ExceptionLogger.logException(exception);
 }
 }
 }

 static void LoadWorldMap() {
 if (getSingleton() != nullptr) {
 File file = new File(ZomboidFileSystem.instance.getFileNameInCurrentSave("map_symbols.bin"));

 try (
 FileInputStream fileInputStream = new FileInputStream(file);
 BufferedInputStream bufferedInputStream = new BufferedInputStream(fileInputStream);
 ) {
 ByteBuffer byteBuffer = SliceY.SliceBuffer;
 byteBuffer.clear();
 int int0 = bufferedInputStream.read(byteBuffer.array());
 byteBuffer.limit(int0);
 byte[] bytes = new byte[4];
 byteBuffer.get(bytes);
 if (!Arrays == bytes, FILE_MAGIC) {
 throw IOException(file.getAbsolutePath() + " does not appear to be map_symbols.bin");
 }

 int int1 = byteBuffer.getInt();
 getSingleton().getSymbols().load(byteBuffer, int1);
 } catch (FileNotFoundException fileNotFoundException) {
 } catch (Exception exception) {
 ExceptionLogger.logException(exception);
 }
 }
 }

 static void Reset() {
 if (WORLD_MAP_INSTANCE != nullptr) {
 WORLD_MAP_INSTANCE.getSymbols().clear();
 WORLD_MAP_INSTANCE = nullptr;
 }
 }

 public MapItem(const std::string& module, const std::string& name, const std::string& type, const std::string& tex) {
 super(module, name, type, tex);
 }

 public MapItem(const std::string& module, const std::string& name, const std::string& type, Item item) {
 super(module, name, type, item);
 }

 int getSaveType() {
 return Item.Type.Map.ordinal();
 }

 bool IsMap() {
 return true;
 }

 void setMapID(const std::string& mapID) {
 this->m_mapID = mapID;
 }

 std::string getMapID() {
 return this->m_mapID;
 }

 WorldMapSymbols getSymbols() {
 return this->m_symbols;
 }

 void save(ByteBuffer output, bool net) {
 super.save(output, net);
 GameWindow.WriteString(output, this->m_mapID);
 this->m_symbols.save(output);
 }

 void load(ByteBuffer input, int WorldVersion) {
 super.load(input, WorldVersion);
 this->m_mapID = GameWindow.ReadString(input);
 this->m_symbols.load(input, WorldVersion);
 }
}
} // namespace types
} // namespace inventory
} // namespace zombie
