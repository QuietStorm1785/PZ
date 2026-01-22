#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/Vector2.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedVehicleStory {


class VehicleStorySpawner {
public:
    std::string id;
    const Vector2 position = std::make_shared<Vector2>();
    float direction;
    float width;
    float height;
    float z;
    IsoGridSquare square;

   VehicleStorySpawner$Element init(std::string var1, float var2, float var3, float var4, float var5, float var6) {
      this.id = var1;
      this.position.set(var2, var3);
      this.direction = var4;
      this.width = var5;
      this.height = var6;
      this.z = 0.0F;
      this.square = nullptr;
    return this;
   }
}
} // namespace randomizedVehicleStory
} // namespace randomizedWorld
} // namespace zombie
