#pragma once
#include <stack>
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
#include "zombie/core/secure/PZcrypt.h"
#include "zombie/network/ServerWorldDatabase.h"

namespace zombie {
namespace commands {
namespace serverCommands {


class AddUserCommand : public CommandBase {
public:
    public AddUserCommand(const std::string& var1, const std::string& var2, const std::string& var3, UdpConnection var4) {
      super(var1, var2, var3, var4);
   }

    std::string Command() {
    std::string var1 = this.getCommandArg(0);
    std::string var2 = PZcrypt.hash(ServerWorldDatabase.encrypt(this.getCommandArg(1)));
      if (!ServerWorldDatabase.isValidUserName(var1)) {
         return "Invalid username \"" + var1 + "\"";
      } else {
         LoggerManager.getLogger("admin").write(this.getExecutorUsername() + " created user " + var1.trim() + " with password " + var2.trim());

         try {
            return ServerWorldDatabase.instance.addUser(var1.trim(), var2.trim());
         } catch (SQLException var4) {
            var4.printStackTrace();
            return "exception occurs";
         }
      }
   }
}
} // namespace serverCommands
} // namespace commands
} // namespace zombie
