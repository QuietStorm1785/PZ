#pragma once
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
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/ServerOptions.h"
#include <iterator>

namespace zombie {
namespace commands {
namespace serverCommands {


class ShowOptionsCommand : public CommandBase {
public:
    public ShowOptionsCommand(const std::string& var1, const std::string& var2, const std::string& var3, UdpConnection var4) {
      super(var1, var2, var3, var4);
   }

    std::string Command() {
    Iterator var1 = ServerOptions.instance.getPublicOptions().iterator();
    void* var2 = nullptr;
    std::string var3 = " <LINE> ";
      if (this.connection == nullptr) {
         var3 = "\n";
      }

    std::string var4 = "List of Server Options:" + var3;

      while (var1.hasNext()) {
         var2 = (std::string)var1.next();
         if (!var2 == "ServerWelcomeMessage")) {
            var4 = var4 + "* " + var2 + "=" + ServerOptions.instance.getOptionByName((std::string)var2).asConfigOption().getValueAsString() + var3;
         }
      }

      return var4 + "* ServerWelcomeMessage=" + ServerOptions.instance.ServerWelcomeMessage.getValue();
   }
}
} // namespace serverCommands
} // namespace commands
} // namespace zombie
