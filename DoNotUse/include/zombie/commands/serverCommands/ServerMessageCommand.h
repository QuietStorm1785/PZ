#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/commands/CommandArgs.h"
#include "zombie/commands/CommandBase.h"
#include "zombie/commands/CommandHelp.h"
#include "zombie/commands/CommandName.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/chat/ChatServer.h"

namespace zombie {
namespace commands {
namespace serverCommands {


class ServerMessageCommand : public CommandBase {
public:
    public ServerMessageCommand(const std::string& var1, const std::string& var2, const std::string& var3, UdpConnection var4) {
      super(var1, var2, var3, var4);
   }

    std::string Command() {
    std::string var1 = this.getCommandArg(0);
      if (this.connection == nullptr) {
         ChatServer.getInstance().sendServerAlertMessageToServerChat(var1);
      } else {
    std::string var2 = this.getExecutorUsername();
         ChatServer.getInstance().sendServerAlertMessageToServerChat(var2, var1);
      }

      return "Message sent.";
   }
}
} // namespace serverCommands
} // namespace commands
} // namespace zombie
