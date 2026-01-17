#pragma once
#include "java/sql/SQLException.h"
#include "zombie/commands/CommandArgs.h"
#include "zombie/commands/CommandBase.h"
#include "zombie/commands/CommandHelp.h"
#include "zombie/commands/CommandName.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/znet/SteamUtils.h"
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

    name = "unbanid"
)
    required = {"(.+)"}
)
    helpText = "UI_ServerOptionDesc_UnBanSteamId"
)
    requiredRights = 48
)
class UnbanSteamIDCommand : public CommandBase {
    public:
    public
      UnbanSteamIDCommand(const std::string &string0,
                          const std::string &string1,
                          const std::string &string2,
                          UdpConnection udpConnection) {
        super(string0, string1, string2, udpConnection);
      }

      std::string Command() {
        std::string string = this.getCommandArg(0);
        if (!SteamUtils.isSteamModeEnabled()) {
          return "Server is not in Steam mode";
        } else if (!SteamUtils.isValidSteamID(string)) {
          return "Expected SteamID but got \"" + string + "\"";
        } else {
          LoggerManager.getLogger("admin").write(
              this.getExecutorUsername() + " unbanned steamid " + string,
              "IMPORTANT");
          ServerWorldDatabase.instance.banSteamID(string, "", false);
          return "SteamID " + string + " is now unbanned";
        }
      }
    }
    } // namespace serverCommands
    } // namespace commands
    } // namespace zombie
