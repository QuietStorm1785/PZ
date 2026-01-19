#pragma once
#include <string>
#include <string_view>
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


class FileTask_LoadWorldMapBinary :  FileTask {
:
    WorldMapData m_worldMapData;
    std::string m_filename;

     FileTask_LoadWorldMapBinary(WorldMapData var1, std::string_view var2, FileSystem var3, IFileTaskCallback var4) {
      super(var3, var4);
      this.m_worldMapData = var1;
      this.m_filename = var2;
   }

    std::string getErrorMessage() const {
      return this.m_filename;
   }

    void done() {
      this.m_worldMapData = nullptr;
      this.m_filename = nullptr;
   }

    void* call() {
    WorldMapBinary var1 = new WorldMapBinary();
      return var1.read(this.m_filename, this.m_worldMapData) ? Boolean.TRUE : Boolean.FALSE;
   }
}
} // namespace worldMap
} // namespace zombie
