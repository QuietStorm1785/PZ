#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/inventory/ClothingItemsDotTxt/BlockElement.h"
#include "zombie/inventory/ClothingItemsDotTxt/Value.h"

namespace zombie {
namespace inventory {


class ClothingItemsDotTxt {
public:
    std::string type;
    std::string id;
   public std::vector<BlockElement> elements = std::make_unique<std::vector<>>();
   public std::vector<std::string> values = std::make_unique<std::vector<>>();
   public std::vector<ClothingItemsDotTxt$Block> children = std::make_unique<std::vector<>>();

   private ClothingItemsDotTxt$Block() {
   }

   public ClothingItemsDotTxt$Block asBlock() {
    return this;
   }

    Value asValue() {
    return nullptr;
   }

    std::string toString() {
    std::stringstream var1 = new std::stringstream();
      var1.append(this.type + (this.id == nullptr ? "" : " " + this.id) + "\n");
      var1.append("{\n");

      for (BlockElement var3 : this.elements) {
    std::string var4 = var3;

         for (std::string var8 : var4.split("\n")) {
            var1.append("\t" + var8 + "\n");
         }
      }

      var1.append("}\n");
      return var1;
   }

    std::string toXML() {
    std::stringstream var1 = new std::stringstream();
      var1.append("<Block type=\"" + this.type + "\" id=\"" + this.id + "\">\n");

      for (BlockElement var3 : this.elements) {
    std::string var4 = var3.toXML();

         for (std::string var8 : var4.split("\n")) {
            var1.append("    " + var8 + "\n");
         }
      }

      var1.append("</Block>\n");
      return var1;
   }
}
} // namespace inventory
} // namespace zombie
