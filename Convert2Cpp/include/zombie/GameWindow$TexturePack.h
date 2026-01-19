#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/fileSystem/FileSystem/TexturePackTextures.h"

namespace zombie {


class GameWindow {
public:
    std::string packName;
    std::string fileName;
    std::string modID;
    auto textures = std::make_shared<TexturePackTextures>();

   private GameWindow$TexturePack() {
   }
}
} // namespace zombie
