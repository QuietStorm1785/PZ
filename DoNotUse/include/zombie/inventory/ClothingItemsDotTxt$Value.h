#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/inventory/ClothingItemsDotTxt/Block.h"
#include "zombie/inventory/ClothingItemsDotTxt/BlockElement.h"

namespace zombie {
namespace inventory {


class ClothingItemsDotTxt {
public:
    std::string string;

   private ClothingItemsDotTxt$Value() {
   }

    Block asBlock() {
    return nullptr;
   }

   public ClothingItemsDotTxt$Value asValue() {
    return this;
   }

    std::string toString() {
      return this.string + ",\n";
   }

    std::string toXML() {
      return "<Value>" + this.string + "</Value>\n";
   }
}
} // namespace inventory
} // namespace zombie
