#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/randomizedWorld/randomizedBuilding/RBTableStory/StorySpawnItem.h"

namespace zombie {
namespace randomizedWorld {
namespace randomizedBuilding {


class RBTableStory {
public:
   public std::vector<StorySpawnItem> items;
    bool addBlood;
   public std::vector<std::string> rooms;

   public RBTableStory$StoryDef(std::vector<StorySpawnItem> var1, std::vector var2) {
      this.this$0 = var1;
      this.items = nullptr;
      this.addBlood = false;
      this.rooms = nullptr;
      this.items = var2;
   }

   public RBTableStory$StoryDef(std::vector<StorySpawnItem> var1, std::vector<std::string> var2, std::vector var3) {
      this.this$0 = var1;
      this.items = nullptr;
      this.addBlood = false;
      this.rooms = nullptr;
      this.items = var2;
      this.rooms = var3;
   }
}
} // namespace randomizedBuilding
} // namespace randomizedWorld
} // namespace zombie
