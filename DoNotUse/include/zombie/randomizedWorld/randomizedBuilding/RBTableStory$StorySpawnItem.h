#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace zombie {
namespace randomizedWorld {
namespace randomizedBuilding {


class RBTableStory {
public:
   LinkedHashMap<std::string, int> eitherObject;
    std::string object;
    int chanceToSpawn;
    float forcedOffset;

   public RBTableStory$StorySpawnItem(LinkedHashMap<std::string, int> var1, std::string var2, int var3, int var4) {
      this.this$0 = var1;
      this.eitherObject = nullptr;
      this.object = nullptr;
      this.chanceToSpawn = nullptr;
      this.forcedOffset = 0.0F;
      this.eitherObject = var2;
      this.object = var3;
      this.chanceToSpawn = var4;
   }

   public RBTableStory$StorySpawnItem(LinkedHashMap<std::string, int> var1, std::string var2, int var3, float var4, float var5) {
      this.this$0 = var1;
      this.eitherObject = nullptr;
      this.object = nullptr;
      this.chanceToSpawn = nullptr;
      this.forcedOffset = 0.0F;
      this.eitherObject = var2;
      this.object = var3;
      this.chanceToSpawn = var4;
      this.forcedOffset = var5;
   }
}
} // namespace randomizedBuilding
} // namespace randomizedWorld
} // namespace zombie
