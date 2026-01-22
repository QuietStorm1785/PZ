#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace textures {

class ImageData {
public:
   const int[] pixelRGBA = new int[4];
   const int[] newPixelRGBA = new int[4];
   const int[] pixelRGBA_neighbor = new int[4];
}
} // namespace textures
} // namespace core
} // namespace zombie
