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
:
    std::string packName;
    std::string fileName;
    std::string modID;
    const TexturePackTextures textures = new TexturePackTextures();

   private GameWindow$TexturePack() {
   }
}
} // namespace zombie
