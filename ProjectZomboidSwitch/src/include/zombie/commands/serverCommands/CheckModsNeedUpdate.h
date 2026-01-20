#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/Lua/LuaManager/GlobalObject.h"
#include "zombie/commands/CommandBase.h"
#include "zombie/commands/CommandHelp.h"
#include "zombie/commands/CommandName.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/raknet/UdpConnection.h"

namespace zombie {
namespace commands {
namespace serverCommands {


class CheckModsNeedUpdate : public CommandBase {
public:
    public CheckModsNeedUpdate(const std::string& var1, const std::string& var2, const std::string& var3, UdpConnection var4) {
      super(var1, var2, var3, var4);
   }

    std::string Command() {
      GlobalObject.checkModsNeedUpdate(this.connection);
      return "Checking started. The answer will be written in the log file and in the chat";
   }
}
} // namespace serverCommands
} // namespace commands
} // namespace zombie
