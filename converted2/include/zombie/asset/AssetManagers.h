#pragma once
#include "gnu/trove/map/hash/TLongObjectHashMap.h"
#include "zombie/fileSystem/FileSystem.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace asset {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class AssetManagers {
public:
private
  final AssetManagers.AssetManagerTable m_managers =
      new AssetManagers.AssetManagerTable();
  const FileSystem m_file_system;

public
  AssetManagers(FileSystem fileSystem) { this.m_file_system = fileSystem; }

  AssetManager get(AssetType type) { return this.m_managers.get(type.type); }

  void add(AssetType type, AssetManager rm) {
    this.m_managers.put(type.type, rm);
  }

  FileSystem getFileSystem() { return this.m_file_system; }

public
  static final class AssetManagerTable extends
      TLongObjectHashMap<AssetManager> {}
}
} // namespace asset
} // namespace zombie
