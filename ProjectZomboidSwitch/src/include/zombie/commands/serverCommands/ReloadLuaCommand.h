#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/Lua/LuaManager.h"
#include "zombie/commands/CommandArgs.h"
#include "zombie/commands/CommandBase.h"
#include "zombie/commands/CommandHelp.h"
#include "zombie/commands/CommandName.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/raknet/UdpConnection.h"

namespace zombie {
namespace commands {
namespace serverCommands {


class ReloadLuaCommand : public CommandBase {
public:
    public ReloadLuaCommand(const std::string& var1, const std::string& var2, const std::string& var3, UdpConnection var4) {
      super(var1, var2, var3, var4);
   }

    std::string Command() {
    std::string var1 = this.getCommandArg(0);

      for (std::string var3 : LuaManager.loaded) {
         if (var3.endsWith(var1)) {
            LuaManager.loaded.remove(var3);
            LuaManager.RunLua(var3, true);
            return "Lua file reloaded";
         }
      }

      return "Unknown Lua file";
   }
}
} // namespace serverCommands
} // namespace commands
} // namespace zombie
