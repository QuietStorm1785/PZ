#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/commands/AltCommandArgs.h"
#include "zombie/commands/CommandArgs.h"
#include "zombie/commands/CommandBase.h"
#include "zombie/commands/CommandHelp.h"
#include "zombie/commands/CommandName.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/MPStatistic.h"

namespace zombie {
namespace commands {
namespace serverCommands {


class StatisticsCommand : public CommandBase {
public:
    public StatisticsCommand(const std::string& var1, const std::string& var2, const std::string& var3, UdpConnection var4) {
      super(var1, var2, var3, var4);
   }

    std::string Command() {
      if (this.getCommandArgsCount() != 1 && this.getCommandArgsCount() != 2) {
         return this.getHelp();
      } else {
         try {
    std::string var1 = this.getCommandArg(0);
    bool var2;
    bool var3;
            switch (var1) {
               case "none":
                  var2 = false;
                  var3 = false;
                  break;
               case "all":
                  var2 = true;
                  var3 = true;
                  break;
               case "file":
                  var2 = true;
                  var3 = false;
                  break;
               case "console":
                  var2 = false;
                  var3 = true;
                  break;
               default:
                  return this.getHelp();
            }

    int var4 = this.getCommandArgsCount() == 2 ? int.parseInt(this.getCommandArg(1)) : 10;
            if (var4 < 1) {
               return this.getHelp();
            } else {
               if (!var2 && !var3) {
                  var4 = 0;
               }

               MPStatistic.getInstance().writeEnabled(var2);
               MPStatistic.getInstance().printEnabled(var3);
               MPStatistic.getInstance().setPeriod(var4);
               return "Server statistics has been cleared and file is set to " + var2 + " and console is set to " + var3 + " and period is set to " + var4;
            }
         } catch (Exception var6) {
            return this.getHelp();
         }
      }
   }
}
} // namespace serverCommands
} // namespace commands
} // namespace zombie
