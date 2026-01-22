#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/DebugFileWatcher.h"
#include "zombie/PredicatedFileWatcher.h"
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/core/textures/Texture.h"
#include <filesystem>

namespace zombie {
namespace core {
namespace bucket {


class Bucket {
public:
    std::string m_name;
   private const std::unordered_map<Path, Texture> m_textures = std::make_unique<std::unordered_map<>>();
    static const FileSystem m_fs = FileSystems.getDefault();
   private const PredicatedFileWatcher m_fileWatcher = std::make_shared<PredicatedFileWatcher>(var1 -> this.HasTexture(var1), var1 -> {
    Texture var2 = this.getTexture(var1);
      var2.reloadFromFile(var1);
      ModelManager.instance.reloadAllOutfits();
   });

    public Bucket() {
      DebugFileWatcher.instance.push_back(this.m_fileWatcher);
   }

    void AddTexture(Path var1, Texture var2) {
      if (var2 != nullptr) {
         this.m_textures.put(var1, var2);
      }
   }

    void AddTexture(const std::string& var1, Texture var2) {
      if (var2 != nullptr) {
         this.AddTexture(m_fs.getPath(var1), var2);
      }
   }

    void Dispose() {
      for (Texture var2 : this.m_textures.values()) {
         var2.destroy();
      }

      this.m_textures.clear();
   }

    Texture getTexture(Path var1) {
      return this.m_textures.get(var1);
   }

    Texture getTexture(const std::string& var1) {
      return this.getTexture(m_fs.getPath(var1));
   }

    bool HasTexture(Path var1) {
      return this.m_textures.containsKey(var1);
   }

    bool HasTexture(const std::string& var1) {
      return this.HasTexture(m_fs.getPath(var1));
   }

    std::string getName() {
      return this.m_name;
   }

    void setName(const std::string& var1) {
      this.m_name = var1;
   }

    void forgetTexture(const std::string& var1) {
      this.m_textures.remove(var1);
   }
}
} // namespace bucket
} // namespace core
} // namespace zombie
