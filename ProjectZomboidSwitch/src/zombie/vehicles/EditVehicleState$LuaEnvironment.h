#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/converter/KahluaConverterManager.h"
#include "se/krka/kahlua/integration/LuaCaller.h"
#include "se/krka/kahlua/j2se/J2SEPlatform.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaThread.h"
#include "zombie/Lua/LuaManager.h"

namespace zombie {
namespace vehicles {


class EditVehicleState {
public:
    J2SEPlatform platform;
    KahluaTable env;
    KahluaThread thread;
    LuaCaller caller;

   public EditVehicleState$LuaEnvironment(J2SEPlatform var1, KahluaConverterManager var2, KahluaTable var3) {
      this.platform = var1;
      this.env = var3;
      this.thread = LuaManager.thread;
      this.caller = LuaManager.caller;
   }
}
} // namespace vehicles
} // namespace zombie
