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
   const int[] pixelBytes = new int[4];
   const int[] originalPixel = new int[4];
   const int[] resultPixelBytes = new int[4];

   private ImageData$L_generateMipMaps() {
   }
}
} // namespace textures
} // namespace core
} // namespace zombie
