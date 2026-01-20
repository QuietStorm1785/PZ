#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/JavaFunction.h"
#include "se/krka/kahlua/vm/LuaCallFrame.h"

namespace zombie {
namespace core {
namespace raknet {


class VoiceManager {
public:
   VoiceManager$1(VoiceManager var1) {
      this.this$0 = var1;
   }

    int call(LuaCallFrame var1, int var2) {
    void* var3 = var1.get(1);
      VoiceManager.playerSetMute((std::string)var3);
    return 1;
   }
}
} // namespace raknet
} // namespace core
} // namespace zombie
