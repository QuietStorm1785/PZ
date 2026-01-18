#pragma once
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

    name = "adduser"
)
    required = {"(.+)", "(.+)"}
)
    helpText = "UI_ServerOptionDesc_AddUser"
)
    requiredRights = 48
)
class AddUserCommand : public CommandBase {
    public:
    public
      AddUserCommand(const std::string &string0, const std::string &string1,
                     const std::string &string2, UdpConnection udpConnection) {
        super(string0, string1, string2, udpConnection);
      }

      std::string Command() {
        std::string string0 = this.getCommandArg(0);
        std::string string1 =
            PZcrypt.hash(ServerWorldDatabase.encrypt(this.getCommandArg(1)));
        if (!ServerWorldDatabase.isValidUserName(string0)) {
          return "Invalid username \"" + string0 + "\"";
        } else {
          LoggerManager.getLogger("admin").write(
              this.getExecutorUsername() + " created user " + string0.trim() +
              " with password " + string1.trim());

          try {
            return ServerWorldDatabase.instance.addUser(string0.trim(),
                                                        string1.trim());
          } catch (SQLException sQLException) {
            sQLException.printStackTrace();
            return "exception occurs";
          }
        }
      }
    }
    } // namespace serverCommands
    } // namespace commands
    } // namespace zombie
