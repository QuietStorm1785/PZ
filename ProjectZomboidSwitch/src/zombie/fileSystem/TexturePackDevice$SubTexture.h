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

class SubTexture {
public:
   std::shared_ptr<Page> m_page;
   std::shared_ptr<SubTextureInfo> m_info;

   SubTexture(std::shared_ptr<Page> page, std::shared_ptr<SubTextureInfo> info)
      : m_page(std::move(page)), m_info(std::move(info)) {}
};

} // namespace fileSystem
} // namespace zombie
