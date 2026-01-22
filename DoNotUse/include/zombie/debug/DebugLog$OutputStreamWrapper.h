#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Core.h"
#include "zombie/ui/UIDebugConsole.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace debug {


class DebugLog {
public:
   public DebugLog$OutputStreamWrapper(OutputStream var1) {
      super(var1);
   }

    void write(byte[] var1, int var2, int var3) {
      this.out.write(var1, var2, var3);
      if (Core.bDebug && UIDebugConsole.instance != nullptr && DebugOptions.instance.UIDebugConsoleDebugLog.getValue()) {
         UIDebugConsole.instance.addOutput(var1, var2, var3);
      }
   }

    void setStream(OutputStream var1) {
      this.out = var1;
   }
}
} // namespace debug
} // namespace zombie
