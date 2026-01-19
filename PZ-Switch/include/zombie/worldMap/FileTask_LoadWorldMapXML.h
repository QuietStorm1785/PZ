#pragma once
#include "zombie/fileSystem/FileSystem.h"
#include "zombie/fileSystem/FileTask.h"
#include "zombie/fileSystem/IFileTaskCallback.h"
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace worldMap {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class FileTask_LoadWorldMapXML : public FileTask {
public:
 WorldMapData m_worldMapData;
 std::string m_filename;

public
 FileTask_LoadWorldMapXML(WorldMapData worldMapData, std::string_view string,
 FileSystem fileSystem,
 IFileTaskCallback iFileTaskCallback) {
 super(fileSystem, iFileTaskCallback);
 this->m_worldMapData = worldMapData;
 this->m_filename = string;
 }

 std::string getErrorMessage() { return this->m_filename; }

 void done() {
 this->m_worldMapData = nullptr;
 this->m_filename = nullptr;
 }

 void *call() {
 WorldMapXML worldMapXML = new WorldMapXML();
 return worldMapXML.read(this->m_filename, this->m_worldMapData)
 ? Boolean.TRUE
 : Boolean.FALSE;
 }
}
} // namespace worldMap
} // namespace zombie
