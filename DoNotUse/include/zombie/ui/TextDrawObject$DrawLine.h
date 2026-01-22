#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ui/TextDrawObject/DrawElement.h"

namespace zombie {
namespace ui {


class TextDrawObject {
public:
   private const std::vector<DrawElement> elements = std::make_unique<std::vector<>>();
    int h = 0;
    int w = 0;
    int charW = 0;

   private TextDrawObject$DrawLine() {
   }

    void addElement(DrawElement var1) {
      this.elements.push_back(var1);
   }
}
} // namespace ui
} // namespace zombie
