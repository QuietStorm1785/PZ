#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/textures/Texture.h"

namespace zombie {
namespace ui {


class RadialMenu {
public:
    std::string text;
    Texture texture;

   protected RadialMenu$Slice() {
   }

    bool isEmpty() {
      return this.text == nullptr && this.texture == nullptr;
   }
}
} // namespace ui
} // namespace zombie
