#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/commands/CommandArgs.h"
#include "zombie/commands/CommandBase.h"
#include "zombie/commands/CommandName.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/GameServer.h"

namespace zombie {
namespace commands {
namespace serverCommands {


class DebugPlayerCommand : public CommandBase {
public:
    public DebugPlayerCommand(const std::string& var1, const std::string& var2, const std::string& var3, UdpConnection var4) {
      super(var1, var2, var3, var4);
   }

    std::string Command() {
      if (this.getCommandArgsCount() != 1) {
         return "/debugplayer \"username\"";
      } else {
    std::string var1 = this.getCommandArg(0);
    IsoPlayer var2 = GameServer.getPlayerByUserNameForCommand(var1);
         if (var2 == nullptr) {
            return "no such user";
         } else {
    UdpConnection var3 = GameServer.getConnectionByPlayerOnlineID(var2.OnlineID);
            if (var3 == nullptr) {
               return "no connection for user";
            } else if (GameServer.DebugPlayer.contains(var3)) {
               GameServer.DebugPlayer.remove(var3);
               return "debug off";
            } else {
               GameServer.DebugPlayer.push_back(var3);
               return "debug on";
            }
         }
      }
   }
}
} // namespace serverCommands
} // namespace commands
} // namespace zombie
