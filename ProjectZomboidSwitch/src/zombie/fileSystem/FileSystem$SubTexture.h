#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/textures/TexturePackPage/SubTextureInfo.h"

namespace zombie {
namespace fileSystem {


class FileSystem {
public:
    std::string m_pack_name;
    std::string m_page_name;
    SubTextureInfo m_info;

   public FileSystem$SubTexture(std::string var1, std::string var2, SubTextureInfo var3) {
      this.m_pack_name = var1;
      this.m_page_name = var2;
      this.m_info = var3;
   }
}
} // namespace fileSystem
} // namespace zombie
