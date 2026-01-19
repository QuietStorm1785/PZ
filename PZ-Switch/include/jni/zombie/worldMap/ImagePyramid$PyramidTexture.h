#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/textures/TextureID.h"

namespace zombie {
namespace worldMap {


class ImagePyramid {
:
    std::string m_key;
    int m_requestNumber;
    TextureID m_textureID;
}
} // namespace worldMap
} // namespace zombie
