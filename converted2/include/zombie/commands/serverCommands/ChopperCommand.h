#pragma once
#include "zombie/commands/CommandArgs.h"
#include "zombie/commands/CommandBase.h"
#include "zombie/commands/CommandHelp.h"
#include "zombie/commands/CommandName.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/iso/IsoWorld.h"
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

    name = "chopper"
)
    optional = "([a-zA-Z0-9.-]*[a-zA-Z][a-zA-Z0-9_.-]*)"
)
    helpText = "UI_ServerOptionDesc_Chopper"
)
    requiredRights = 60
)
class ChopperCommand : public CommandBase {
    public:
    public
      ChopperCommand(const std::string &string0, const std::string &string1,
                     const std::string &string2, UdpConnection udpConnection) {
        super(string0, string1, string2, udpConnection);
      }

      std::string Command() {
        std::string string;
        if (this.getCommandArgsCount() == 1) {
          if ("stop" == this.getCommandArg(0))) {
              IsoWorld.instance.helicopter.deactivate();
              string = "Chopper deactivated";
            }
          else if ("start" == this.getCommandArg(0))) {
              IsoWorld.instance.helicopter.pickRandomTarget();
              string = "Chopper activated";
            }
          else {
            string = this.getHelp();
          }
        } else {
          IsoWorld.instance.helicopter.pickRandomTarget();
          string = "Chopper launched";
        }

        LoggerManager.getLogger("admin").write(this.getExecutorUsername() +
                                               " did chopper");
        return string;
      }
    }
    } // namespace serverCommands
    } // namespace commands
    } // namespace zombie
