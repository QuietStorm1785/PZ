#pragma once
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
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace commands {
namespace serverCommands {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

    name = "addusertowhitelist"
)
    required = {"(.+)"}
)
    helpText = "UI_ServerOptionDesc_AddWhitelist"
)
    requiredRights = 48
)
class AddUserToWhiteListCommand : public CommandBase {
    public:
    public
      AddUserToWhiteListCommand(const std::string &string0,
                                const std::string &string1,
                                const std::string &string2,
                                UdpConnection udpConnection) {
        super(string0, string1, string2, udpConnection);
      }

      std::string Command() {
        std::string string = this.getCommandArg(0);
        if (!ServerWorldDatabase.isValidUserName(string)) {
          return "Invalid username \"" + string + "\"";
        } else {
          for (int int0 = 0; int0 < GameServer.udpEngine.connections.size();
               int0++) {
            UdpConnection udpConnection =
                GameServer.udpEngine.connections.get(int0);
            if (udpConnection.username == string)) {
                if (udpConnection.password != nullptr &&
                    !udpConnection.password == "")) {
                    LoggerManager.getLogger("admin").write(
                        this.getExecutorUsername() + " created user " +
                        udpConnection.username + " with password " +
                        udpConnection.password);
                    return ServerWorldDatabase.instance.addUser(
                        udpConnection.username, udpConnection.password);
                  }

                return "User " + string + " doesn't have a password.";
              }
          }

          return "User " + string + " not found.";
        }
      }
    }
    } // namespace serverCommands
    } // namespace commands
    } // namespace zombie
