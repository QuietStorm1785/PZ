#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/commands/CommandBase.h"
#include "zombie/commands/CommandHelp.h"
#include "zombie/commands/CommandName.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/ServerMap.h"

namespace zombie {
namespace commands {
namespace serverCommands {


class QuitCommand : public CommandBase {
public:
    public QuitCommand(const std::string& var1, const std::string& var2, const std::string& var3, UdpConnection var4) {
      super(var1, var2, var3, var4);
   }

    std::string Command() {
      DebugLog.Multiplayer.debugln(this.description);
      ServerMap.instance.QueueSaveAll();
      ServerMap.instance.QueueQuit();
      LoggerManager.getLogger("admin").write(this.getExecutorUsername() + " closed server");
      return "Quit";
   }
}
} // namespace serverCommands
} // namespace commands
} // namespace zombie
