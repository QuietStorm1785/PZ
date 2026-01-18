#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/math/PZMath.h"
#include <filesystem>

namespace zombie {
namespace worldMap {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class WorldMapImages {
public:
 private static HashMap<String, WorldMapImages> s_filenameToImages = std::make_unique<HashMap<>>();
 std::string m_directory;
 ImagePyramid m_pyramid;

 static WorldMapImages getOrCreate(const std::string& directory) {
 std::string string = ZomboidFileSystem.instance.getString(directory + "/pyramid.zip");
 if (!Files.exists(Paths.get(string) {
 return nullptr;
 } else {
 WorldMapImages worldMapImages = s_filenameToImages.get(string);
 if (worldMapImages.empty()) {
 worldMapImages = std::make_unique<WorldMapImages>();
 worldMapImages.m_directory = directory;
 worldMapImages.m_pyramid = std::make_unique<ImagePyramid>();
 worldMapImages.m_pyramid.setZipFile(string);
 s_filenameToImages.put(string, worldMapImages);
 }

 return worldMapImages;
 }
 }

 ImagePyramid getPyramid() {
 return this->m_pyramid;
 }

 int getMinX() {
 return this->m_pyramid.m_minX;
 }

 int getMinY() {
 return this->m_pyramid.m_minY;
 }

 int getMaxX() {
 return this->m_pyramid.m_maxX;
 }

 int getMaxY() {
 return this->m_pyramid.m_maxY;
 }

 int getZoom(float zoomF) {
 uint8_t byte0 = 4;
 if (zoomF >= 16.0) {
 byte0 = 0;
 } else if (zoomF >= 15.0F) {
 byte0 = 1;
 } else if (zoomF >= 14.0F) {
 byte0 = 2;
 } else if (zoomF >= 13.0F) {
 byte0 = 3;
 }

 return PZMath.clamp(byte0, this->m_pyramid.m_minZ, this->m_pyramid.m_maxZ);
 }

 float getResolution() {
 return this->m_pyramid.m_resolution;
 }

 void destroy() {
 this->m_pyramid.destroy();
 }

 static void Reset() {
 for (WorldMapImages worldMapImages : s_filenameToImages.values()) {
 worldMapImages.destroy();
 }

 s_filenameToImages.clear();
 }
}
} // namespace worldMap
} // namespace zombie
