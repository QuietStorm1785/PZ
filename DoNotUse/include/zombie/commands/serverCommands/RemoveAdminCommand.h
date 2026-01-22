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
#include "zombie/commands/CommandName.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/raknet/UdpConnection.h"

namespace zombie {
namespace commands {
namespace serverCommands {


class RemoveAdminCommand : public CommandBase {
public:
    public RemoveAdminCommand(const std::string& var1, const std::string& var2, const std::string& var3, UdpConnection var4) {
      super(var1, var2, var3, var4);
   }

    std::string Command() {
      return SetAccessLevelCommand.update(this.getExecutorUsername(), this.connection, this.getCommandArg(0), "");
   }
}
} // namespace serverCommands
} // namespace commands
} // namespace zombie
