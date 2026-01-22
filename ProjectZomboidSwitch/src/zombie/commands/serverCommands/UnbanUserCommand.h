#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/sql/SQLException.h"
#include "zombie/commands/CommandArgs.h"
#include "zombie/commands/CommandBase.h"
#include "zombie/commands/CommandHelp.h"
#include "zombie/commands/CommandName.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/znet/SteamUtils.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerWorldDatabase.h"

namespace zombie {
namespace commands {
namespace serverCommands {


class UnbanUserCommand : public CommandBase {
public:
    public UnbanUserCommand(const std::string& var1, const std::string& var2, const std::string& var3, UdpConnection var4) {
      super(var1, var2, var3, var4);
   }

    std::string Command() {
    std::string var1 = this.getCommandArg(0);
    std::string var2 = ServerWorldDatabase.instance.banUser(var1, false);
      LoggerManager.getLogger("admin").write(this.getExecutorUsername() + " unbanned user " + var1);
      if (!SteamUtils.isSteamModeEnabled()) {
         ServerWorldDatabase.instance.banIp(nullptr, var1, nullptr, false);

         for (int var3 = 0; var3 < GameServer.udpEngine.connections.size(); var3++) {
    UdpConnection var4 = (UdpConnection)GameServer.udpEngine.connections.get(var3);
            if (var4.username == var1)) {
               ServerWorldDatabase.instance.banIp(var4.ip, var1, nullptr, false);
               break;
            }
         }
      }

    return var2;
   }
}
} // namespace serverCommands
} // namespace commands
} // namespace zombie
