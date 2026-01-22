#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/sql/SQLException.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/commands/CommandBase.h"
#include "zombie/commands/CommandHelp.h"
#include "zombie/commands/CommandName.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/iso/areas/SafeHouse.h"
#include "zombie/network/GameServer.h"

namespace zombie {
namespace commands {
namespace serverCommands {


class ReleaseSafehouseCommand : public CommandBase {
public:
    public ReleaseSafehouseCommand(const std::string& var1, const std::string& var2, const std::string& var3, UdpConnection var4) {
      super(var1, var2, var3, var4);
   }

    std::string Command() {
      if (this.isCommandComeFromServerConsole()) {
    return getCommandName();
      } else {
    std::string var1 = this.getExecutorUsername();
    IsoPlayer var2 = GameServer.getPlayerByUserNameForCommand(var1);
    SafeHouse var3 = SafeHouse.hasSafehouse(var1);
         if (var3 != nullptr) {
            if (!var3.isOwner(var2)) {
               return "Only owner can release safehouse";
            } else {
               var3.removeSafeHouse(var2);
               return "Your safehouse was released";
            }
         } else {
            return "You have no safehouse";
         }
      }
   }
}
} // namespace serverCommands
} // namespace commands
} // namespace zombie
