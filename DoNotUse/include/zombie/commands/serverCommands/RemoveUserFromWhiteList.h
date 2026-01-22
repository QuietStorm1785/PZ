#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/sql/SQLException.h"
#include "zombie/commands/CommandArgs.h"
#include "zombie/commands/CommandBase.h"
#include "zombie/commands/CommandHelp.h"
#include "zombie/commands/CommandName.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/ServerWorldDatabase.h"

namespace zombie {
namespace commands {
namespace serverCommands {


class RemoveUserFromWhiteList : public CommandBase {
public:
    public RemoveUserFromWhiteList(const std::string& var1, const std::string& var2, const std::string& var3, UdpConnection var4) {
      super(var1, var2, var3, var4);
   }

    std::string Command() {
    std::string var1 = this.getCommandArg(0);
      LoggerManager.getLogger("admin").write(this.getExecutorUsername() + " removed user " + var1 + " from whitelist");
      return ServerWorldDatabase.instance.removeUser(var1);
   }
}
} // namespace serverCommands
} // namespace commands
} // namespace zombie
