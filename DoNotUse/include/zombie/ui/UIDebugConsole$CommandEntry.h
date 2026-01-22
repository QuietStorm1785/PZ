#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace ui {

class UIDebugConsole {
public:
   public UIDebugConsole$CommandEntry(UIDebugConsole var1, UIFont var2, int var3, int var4, int var5, int var6, std::string var7, boolean var8) {
      super(var2, var3, var4, var5, var6, var7, var8);
      this.this$0 = var1;
   }

    void onPressUp() {
      this.this$0.historyPrev();
   }

    void onPressDown() {
      this.this$0.historyNext();
   }

    void onOtherKey(int var1) {
      this.this$0.onOtherKey(var1);
   }
}
} // namespace ui
} // namespace zombie
