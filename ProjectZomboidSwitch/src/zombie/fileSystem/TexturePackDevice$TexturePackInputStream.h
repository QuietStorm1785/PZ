
#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>
#include "zombie/core/textures/TexturePackPage.h"
#include "zombie/fileSystem/TexturePackDevice/Page.h"

namespace zombie {
namespace fileSystem {

class TexturePackDevice;

class TexturePackInputStream : public std::ifstream {
public:
    std::shared_ptr<TexturePackDevice> m_device;
    std::shared_ptr<Page> m_page;

    TexturePackInputStream(const std::string& subtextureName, std::shared_ptr<TexturePackDevice> device);
};

} // namespace fileSystem
} // namespace zombie
