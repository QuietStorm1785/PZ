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


class SubTexture {
public:
   std::string m_pack_name;
   std::string m_page_name;
   std::shared_ptr<SubTextureInfo> m_info;

   SubTexture(const std::string& pack_name, const std::string& page_name, std::shared_ptr<SubTextureInfo> info)
      : m_pack_name(pack_name), m_page_name(page_name), m_info(std::move(info)) {}
};
} // namespace fileSystem
} // namespace zombie
