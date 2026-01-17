#pragma once
#include "zombie/AmbientStreamManager.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/commands/CommandBase.h"
#include "zombie/commands/CommandHelp.h"
#include "zombie/commands/CommandName.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/raknet/UdpConnection.h"
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

    name = "alarm"
)
    helpText = "UI_ServerOptionDesc_Alarm"
)
    requiredRights = 60
)
class AlarmCommand : public CommandBase {
    public:
    public
      AlarmCommand(const std::string &string0, const std::string &string1,
                   const std::string &string2, UdpConnection udpConnection) {
        super(string0, string1, string2, udpConnection);
      }

      std::string Command() {
        IsoPlayer player =
            GameServer.getPlayerByUserName(this.getExecutorUsername());
        if (player != nullptr && player.getSquare() != nullptr &&
            player.getSquare().getBuilding() != nullptr) {
          player.getSquare().getBuilding().getDef().bAlarmed = true;
          AmbientStreamManager.instance.doAlarm(
              player.getSquare().getRoom().def);
          return "Alarm sounded";
        } else {
          return "Not in a room";
        }
      }
    }
    } // namespace serverCommands
    } // namespace commands
    } // namespace zombie
