#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/j2se/KahluaTableImpl.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/util/Type.h"

namespace zombie {
namespace core {
namespace stash {


class StashAnnotation {
public:
    std::string symbol;
    std::string text;
    float x;
    float y;
    float r;
    float g;
    float b;

    void fromLua(KahluaTable var1) {
    KahluaTableImpl var2 = (KahluaTableImpl)var1;
      this.symbol = (std::string)Type.tryCastTo(var1.rawget("symbol"), std::string.class);
      this.text = (std::string)Type.tryCastTo(var1.rawget("text"), std::string.class);
      this.x = var2.rawgetFloat("x");
      this.y = var2.rawgetFloat("y");
      this.r = var2.rawgetFloat("r");
      this.g = var2.rawgetFloat("g");
      this.b = var2.rawgetFloat("b");
   }
}
} // namespace stash
} // namespace core
} // namespace zombie
