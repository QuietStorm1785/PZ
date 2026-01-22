#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/AmbientStreamManager.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/commands/CommandBase.h"
#include "zombie/commands/CommandHelp.h"
#include "zombie/commands/CommandName.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/GameServer.h"

namespace zombie {
namespace commands {
namespace serverCommands {


class AlarmCommand : public CommandBase {
public:
    public AlarmCommand(const std::string& var1, const std::string& var2, const std::string& var3, UdpConnection var4) {
      super(var1, var2, var3, var4);
   }

    std::string Command() {
    IsoPlayer var1 = GameServer.getPlayerByUserName(this.getExecutorUsername());
      if (var1 != nullptr && var1.getSquare() != nullptr && var1.getSquare().getBuilding() != nullptr) {
         var1.getSquare().getBuilding().getDef().bAlarmed = true;
         AmbientStreamManager.instance.doAlarm(var1.getSquare().getRoom().def);
         return "Alarm sounded";
      } else {
         return "Not in a room";
      }
   }
}
} // namespace serverCommands
} // namespace commands
} // namespace zombie
