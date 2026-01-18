#pragma once
#include "gnu/trove/map/hash/TIntObjectHashMap.h"
#include "zombie/GameWindow.h"
#include "zombie/util/SharedStrings.h"
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
namespace worldMap {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class WorldMapBinary {
public:
 static const int VERSION1 = 1;
 static const int VERSION_LATEST = 1;
 const SharedStrings m_sharedStrings = new SharedStrings();
private
 TIntObjectHashMap<String> m_stringTable =
 std::make_unique<TIntObjectHashMap<>>();
 const WorldMapProperties m_properties = new WorldMapProperties();
private
 ArrayList<WorldMapProperties> m_sharedProperties =
 std::make_unique<ArrayList<>>();

 bool read(const std::string &string, WorldMapData worldMapData) {
 try(FileInputStream fileInputStream = new FileInputStream(string);
 BufferedInputStream bufferedInputStream =
 new BufferedInputStream(fileInputStream);) {
 int int0 = bufferedInputStream.read();
 int int1 = bufferedInputStream.read();
 int int2 = bufferedInputStream.read();
 int int3 = bufferedInputStream.read();
 if (int0 == 73 && int1 == 71 && int2 == 77 && int3 == 66) {
 int int4 = this->readInt(bufferedInputStream);
 if (int4 >= 1 && int4 <= 1) {
 int int5 = this->readInt(bufferedInputStream);
 int int6 = this->readInt(bufferedInputStream);
 this->readStringTable(bufferedInputStream);

 for (int int7 = 0; int7 < int6; int7++) {
 for (int int8 = 0; int8 < int5; int8++) {
 WorldMapCell worldMapCell = this->parseCell(bufferedInputStream);
 if (worldMapCell != nullptr) {
 worldMapData.m_cells.add(worldMapCell);
 }
 }
 }

 return true;
 } else {
 throw IOException("unrecognized version " + int4);
 }
 } else {
 throw IOException("invalid format (magic doesn't match)");
 }
 }
 }

 int readByte(InputStream inputStream) { return inputStream.read(); }

 int readInt(InputStream inputStream) {
 int int0 = inputStream.read();
 int int1 = inputStream.read();
 int int2 = inputStream.read();
 int int3 = inputStream.read();
 if ((int0 | int1 | int2 | int3) < 0) {
 throw std::make_unique<EOFException>();
 } else {
 return (int0 << 0) + (int1 << 8) + (int2 << 16) + (int3 << 24);
 }
 }

 int readShort(InputStream inputStream) {
 int int0 = inputStream.read();
 int int1 = inputStream.read();
 if ((int0 | int1) < 0) {
 throw std::make_unique<EOFException>();
 } else {
 return (short)((int0 << 0) + (int1 << 8);
 }
 }

 void readStringTable(InputStream inputStream) {
 ByteBuffer byteBuffer = ByteBuffer.allocate(1024);
 byte[] bytes = new byte[1024];
 int int0 = this->readInt(inputStream);

 for (int int1 = 0; int1 < int0; int1++) {
 byteBuffer.clear();
 int int2 = this->readShort(inputStream);
 byteBuffer.putShort((short)int2);
 inputStream.read(bytes, 0, int2);
 byteBuffer.put(bytes, 0, int2);
 byteBuffer.flip();
 this->m_stringTable.put(int1, GameWindow.ReadStringUTF(byteBuffer);
 }
 }

 std::string readStringIndexed(InputStream inputStream) {
 int int0 = this->readShort(inputStream);
 if (!this->m_stringTable.containsKey(int0) {
 throw IOException("invalid string-table index " + int0);
 } else {
 return this->m_stringTable.get(int0);
 }
 }

 WorldMapCell parseCell(InputStream inputStream) {
 int int0 = this->readInt(inputStream);
 if (int0 == -1) {
 return nullptr;
 } else {
 int int1 = this->readInt(inputStream);
 WorldMapCell worldMapCell = new WorldMapCell();
 worldMapCell.m_x = int0;
 worldMapCell.m_y = int1;
 int int2 = this->readInt(inputStream);

 for (int int3 = 0; int3 < int2; int3++) {
 WorldMapFeature worldMapFeature =
 this->parseFeature(worldMapCell, inputStream);
 worldMapCell.m_features.add(worldMapFeature);
 }

 return worldMapCell;
 }
 }

 WorldMapFeature parseFeature(WorldMapCell worldMapCell,
 InputStream inputStream) {
 WorldMapFeature worldMapFeature = new WorldMapFeature(worldMapCell);
 WorldMapGeometry worldMapGeometry = this->parseGeometry(inputStream);
 worldMapFeature.m_geometries.add(worldMapGeometry);
 this->parseFeatureProperties(inputStream, worldMapFeature);
 return worldMapFeature;
 }

 void parseFeatureProperties(InputStream inputStream,
 WorldMapFeature worldMapFeature) {
 this->m_properties.clear();
 int int0 = this->readByte(inputStream);

 for (int int1 = 0; int1 < int0; int1++) {
 std::string string0 =
 this->m_sharedStrings.get(this->readStringIndexed(inputStream);
 std::string string1 =
 this->m_sharedStrings.get(this->readStringIndexed(inputStream);
 this->m_properties.put(string0, string1);
 }

 worldMapFeature.m_properties =
 this->getOrCreateProperties(this->m_properties);
 }

 WorldMapProperties
 getOrCreateProperties(WorldMapProperties worldMapProperties0) {
 for (int int0 = 0; int0 < this->m_sharedProperties.size(); int0++) {
 if (this->m_sharedProperties.get(int0) == worldMapProperties0) {
 return this->m_sharedProperties.get(int0);
 }
 }

 WorldMapProperties worldMapProperties1 = new WorldMapProperties();
 worldMapProperties1.putAll(worldMapProperties0);
 this->m_sharedProperties.add(worldMapProperties1);
 return worldMapProperties1;
 }

 WorldMapGeometry parseGeometry(InputStream inputStream) {
 WorldMapGeometry worldMapGeometry = new WorldMapGeometry();
 worldMapGeometry.m_type =
 WorldMapGeometry.Type.valueOf(this->readStringIndexed(inputStream);
 int int0 = this->readByte(inputStream);

 for (int int1 = 0; int1 < int0; int1++) {
 WorldMapPoints worldMapPoints = new WorldMapPoints();
 this->parseGeometryCoordinates(inputStream, worldMapPoints);
 worldMapGeometry.m_points.add(worldMapPoints);
 }

 worldMapGeometry.calculateBounds();
 return worldMapGeometry;
 }

 void parseGeometryCoordinates(InputStream inputStream,
 WorldMapPoints worldMapPoints) {
 int int0 = this->readShort(inputStream);

 for (int int1 = 0; int1 < int0; int1++) {
 worldMapPoints.add(this->readShort(inputStream);
 worldMapPoints.add(this->readShort(inputStream);
 }
 }
}
} // namespace worldMap
} // namespace zombie
