#pragma once
#include "zombie/commands/AltCommandArgs.h"
#include "zombie/commands/CommandArgs.h"
#include "zombie/commands/CommandBase.h"
#include "zombie/commands/CommandHelp.h"
#include "zombie/commands/CommandName.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/MPStatistic.h"
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

    name = "stats"
)
        required = {"(none|file|console|all)"},
        optional = "(\\d+)"
    ), @CommandArgs(
        optional = "(\\d+)"
    )
    })
    helpText = "UI_ServerOptionDesc_SetStatisticsPeriod"
)
    requiredRights = 32
)
class StatisticsCommand : public CommandBase {
    public:
    public
      StatisticsCommand(const std::string &string0, const std::string &string1,
                        const std::string &string2,
                        UdpConnection udpConnection) {
        super(string0, string1, string2, udpConnection);
      }

      std::string Command() {
        if (this.getCommandArgsCount() != 1 &&
            this.getCommandArgsCount() != 2) {
          return this.getHelp();
        } else {
          try {
            std::string string = this.getCommandArg(0);
            bool boolean0;
            bool boolean1;
            switch (string) {
            case "none":
              boolean0 = false;
              boolean1 = false;
              break;
            case "all":
              boolean0 = true;
              boolean1 = true;
              break;
            case "file":
              boolean0 = true;
              boolean1 = false;
              break;
            case "console":
              boolean0 = false;
              boolean1 = true;
              break;
            default:
              return this.getHelp();
            }

            int int0 = this.getCommandArgsCount() == 2
                           ? Integer.parseInt(this.getCommandArg(1))
                           : 10;
            if (int0 < 1) {
              return this.getHelp();
            } else {
              if (!boolean0 && !boolean1) {
                int0 = 0;
              }

              MPStatistic.getInstance().writeEnabled(boolean0);
              MPStatistic.getInstance().printEnabled(boolean1);
              MPStatistic.getInstance().setPeriod(int0);
              return "Server statistics has been cleared and file is set to " +
                     boolean0 + " and console is set to " + boolean1 +
                     " and period is set to " + int0;
            }
          } catch (Exception exception) {
            return this.getHelp();
          }
        }
      }
    }
    } // namespace serverCommands
    } // namespace commands
    } // namespace zombie
