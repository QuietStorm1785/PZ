#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace fonts {

class AngelCodeFont {
public:
    short height;
    int id;
    std::string text;
    short width;
    short yOffset;

   private AngelCodeFont$DisplayList() {
   }
}
} // namespace fonts
} // namespace core
} // namespace zombie
