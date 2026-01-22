#pragma once
#include <map>
#include <sstream>
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
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerOptions.h"
#include <algorithm>

namespace zombie {
namespace commands {
namespace serverCommands {


class HelpCommand : public CommandBase {
public:
    public HelpCommand(const std::string& var1, const std::string& var2, const std::string& var3, UdpConnection var4) {
      super(var1, var2, var3, var4);
   }

    std::string Command() {
    std::string var1 = this.getCommandArg(0);
      if (var1 != nullptr) {
    Class var10 = findCommandCls(var1);
         return var10 != nullptr ? getHelp(var10) : "Unknown command /" + var1;
      } else {
    std::string var2 = " <LINE> ";
    std::stringstream var3 = new std::stringstream();
         if (this.connection == nullptr) {
            var2 = "\n";
         }

         if (!GameServer.bServer) {
            for (std::string var6 : ServerOptions.getClientCommandList(this.connection != nullptr)) {
               var3.append(var6);
            }
         }

         var3.append("List of ").append("server").append(" commands : ");
    std::string var11 = "";
    std::map var13 = new std::map();

         for (Class var9 : getSubClasses()) {
            if (!isDisabled(var9)) {
               var11 = getHelp(var9);
               if (var11 != nullptr) {
                  var13.put(getCommandName(var9), var11);
               }
            }
         }

         for (Entry var16 : var13.entrySet()) {
            var3.append(var2).append("* ").append((std::string)var16.getKey()).append(" : ").append((std::string)var16.getValue());
         }

         return var3;
      }
   }
}
} // namespace serverCommands
} // namespace commands
} // namespace zombie
