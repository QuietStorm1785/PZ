#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace ui {

class TextDrawObject {
public:
    int playerNum;
    TextDrawObject element;
    TextDrawHorizontal horz;
    double x;
    double y;
    float r;
    float g;
    float b;
    float a;
    bool drawOutlines;

   private TextDrawObject$RenderBatch() {
   }
}
} // namespace ui
} // namespace zombie
