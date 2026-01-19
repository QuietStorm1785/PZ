#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/math/PZMath.h"
#include <filesystem>

namespace zombie {
namespace worldMap {


class WorldMapImages {
public:
   private static final HashMap<String, WorldMapImages> s_filenameToImages = std::make_unique<HashMap<>>();
    std::string m_directory;
    ImagePyramid m_pyramid;

    static WorldMapImages getOrCreate(const std::string& var0) {
    std::string var1 = ZomboidFileSystem.instance.getString(var0 + "/pyramid.zip");
      if (!Files.exists(Paths.get(var1))) {
    return null;
      } else {
    WorldMapImages var2 = s_filenameToImages.get(var1);
         if (var2 == nullptr) {
            var2 = std::make_unique<WorldMapImages>();
            var2.m_directory = var0;
            var2.m_pyramid = std::make_unique<ImagePyramid>();
            var2.m_pyramid.setZipFile(var1);
            s_filenameToImages.put(var1, var2);
         }

    return var2;
      }
   }

    ImagePyramid getPyramid() {
      return this.m_pyramid;
   }

    int getMinX() {
      return this.m_pyramid.m_minX;
   }

    int getMinY() {
      return this.m_pyramid.m_minY;
   }

    int getMaxX() {
      return this.m_pyramid.m_maxX;
   }

    int getMaxY() {
      return this.m_pyramid.m_maxY;
   }

    int getZoom(float var1) {
    uint8_t var2 = 4;
      if (var1 >= 16.0) {
         var2 = 0;
      } else if (var1 >= 15.0F) {
         var2 = 1;
      } else if (var1 >= 14.0F) {
         var2 = 2;
      } else if (var1 >= 13.0F) {
         var2 = 3;
      }

      return PZMath.clamp(var2, this.m_pyramid.m_minZ, this.m_pyramid.m_maxZ);
   }

    float getResolution() {
      return this.m_pyramid.m_resolution;
   }

    void destroy() {
      this.m_pyramid.destroy();
   }

    static void Reset() {
      for (WorldMapImages var1 : s_filenameToImages.values()) {
         var1.destroy();
      }

      s_filenameToImages.clear();
   }
}
} // namespace worldMap
} // namespace zombie
