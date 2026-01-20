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
#include "zombie/commands/DisabledCommand.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerWorldDatabase.h"

namespace zombie {
namespace commands {
namespace serverCommands {


class AddUserToWhiteListCommand : public CommandBase {
public:
    public AddUserToWhiteListCommand(const std::string& var1, const std::string& var2, const std::string& var3, UdpConnection var4) {
      super(var1, var2, var3, var4);
   }

    std::string Command() {
    std::string var1 = this.getCommandArg(0);
      if (!ServerWorldDatabase.isValidUserName(var1)) {
         return "Invalid username \"" + var1 + "\"";
      } else {
         for (int var2 = 0; var2 < GameServer.udpEngine.connections.size(); var2++) {
    UdpConnection var3 = (UdpConnection)GameServer.udpEngine.connections.get(var2);
            if (var3.username == var1)) {
               if (var3.password != nullptr && !var3.password == "")) {
                  LoggerManager.getLogger("admin").write(this.getExecutorUsername() + " created user " + var3.username + " with password " + var3.password);
                  return ServerWorldDatabase.instance.addUser(var3.username, var3.password);
               }

               return "User " + var1 + " doesn't have a password.";
            }
         }

         return "User " + var1 + " not found.";
      }
   }
}
} // namespace serverCommands
} // namespace commands
} // namespace zombie
