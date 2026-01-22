#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/fileSystem/FileSystem.h"
#include "zombie/fileSystem/FileTask.h"
#include "zombie/fileSystem/IFileTaskCallback.h"

namespace zombie {
namespace worldMap {


class FileTask_LoadWorldMapXML : public FileTask {
public:
    WorldMapData m_worldMapData;
    std::string m_filename;

    public FileTask_LoadWorldMapXML(WorldMapData var1, const std::string& var2, FileSystem var3, IFileTaskCallback var4) {
      super(var3, var4);
      this.m_worldMapData = var1;
      this.m_filename = var2;
   }

    std::string getErrorMessage() {
      return this.m_filename;
   }

    void done() {
      this.m_worldMapData = nullptr;
      this.m_filename = nullptr;
   }

    void* call() {
    WorldMapXML var1 = std::make_shared<WorldMapXML>();
      return var1.read(this.m_filename, this.m_worldMapData) ? bool.TRUE : bool.FALSE;
   }
}
} // namespace worldMap
} // namespace zombie
