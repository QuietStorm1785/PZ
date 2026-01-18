#pragma once
#include "zombie/characters/IsoPlayer.h"
#include "zombie/commands/CommandArgs.h"
#include "zombie/commands/CommandBase.h"
#include "zombie/commands/CommandHelp.h"
#include "zombie/commands/CommandName.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/iso/weather/ClimateManager.h"
#include "zombie/network/GameServer.h"
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

    name = "lightning"
)
    optional = "(.+)"
)
    helpText = "UI_ServerOptionDesc_Lightning"
)
    requiredRights = 60
)
class LightningCommand : public CommandBase {
    public:
    public
      LightningCommand(const std::string &string0, const std::string &string1,
                       const std::string &string2,
                       UdpConnection udpConnection) {
        super(string0, string1, string2, udpConnection);
      }

      std::string Command() {
        std::string string;
        if (this.getCommandArgsCount() == 0) {
          if (this.connection == nullptr) {
            return "Pass a username";
          }

          string = this.getExecutorUsername();
        } else {
          string = this.getCommandArg(0);
        }

        IsoPlayer player = GameServer.getPlayerByUserNameForCommand(string);
        if (player == nullptr) {
          return "User \"" + string + "\" not found";
        } else {
          int int0 = PZMath.fastfloor(player.getX());
          int int1 = PZMath.fastfloor(player.getY());
          ClimateManager.getInstance().transmitServerTriggerLightning(
              int0, int1, false, true, true);
          LoggerManager.getLogger("admin").write(this.getExecutorUsername() +
                                                 " thunder start");
          return "Lightning triggered";
        }
      }
    }
    } // namespace serverCommands
    } // namespace commands
    } // namespace zombie
