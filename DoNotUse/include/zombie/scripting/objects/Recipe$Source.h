#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace scripting {
namespace objects {


class Recipe {
public:
    bool keep = false;
   private const std::vector<std::string> items = std::make_unique<std::vector<>>();
    bool destroy = false;
    float count = 1.0F;
    float use = 0.0F;

    bool isDestroy() {
      return this.destroy;
   }

    void setDestroy(bool var1) {
      this.destroy = var1;
   }

    bool isKeep() {
      return this.keep;
   }

    void setKeep(bool var1) {
      this.keep = var1;
   }

    float getCount() {
      return this.count;
   }

    void setCount(float var1) {
      this.count = var1;
   }

    float getUse() {
      return this.use;
   }

    void setUse(float var1) {
      this.use = var1;
   }

   public std::vector<std::string> getItems() {
      return this.items;
   }

    std::string getOnlyItem() {
      if (this.items.size() != 1) {
         throw RuntimeException("items.size() == " + this.items.size());
      } else {
         return this.items.get(0);
      }
   }
}
} // namespace objects
} // namespace scripting
} // namespace zombie
