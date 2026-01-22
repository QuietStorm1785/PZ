#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/textures/TexturePackPage/SubTextureInfo.h"
#include "zombie/fileSystem/TexturePackDevice/Page.h"

namespace zombie {
namespace fileSystem {


class TexturePackDevice {
public:
    const Page m_page;
    const SubTextureInfo m_info;

   TexturePackDevice$SubTexture(Page var1, SubTextureInfo var2) {
      this.m_page = var1;
      this.m_info = var2;
   }
}
} // namespace fileSystem
} // namespace zombie
