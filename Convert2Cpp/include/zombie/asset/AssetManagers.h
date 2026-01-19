#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/asset/AssetManagers/AssetManagerTable.h"
#include "zombie/fileSystem/FileSystem.h"

namespace zombie {
namespace asset {


class AssetManagers {
public:
    const AssetManagerTable m_managers = new AssetManagerTable();
    const FileSystem m_file_system;

    public AssetManagers(FileSystem var1) {
      this.m_file_system = var1;
   }

    AssetManager get(AssetType var1) {
      return (AssetManager)this.m_managers.get(var1.type);
   }

    void add(AssetType var1, AssetManager var2) {
      this.m_managers.put(var1.type, var2);
   }

    FileSystem getFileSystem() {
      return this.m_file_system;
   }
}
} // namespace asset
} // namespace zombie
