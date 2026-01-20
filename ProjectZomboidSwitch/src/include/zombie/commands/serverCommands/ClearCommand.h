#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/commands/CommandBase.h"
#include "zombie/commands/CommandName.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/raknet/UdpConnection.h"

namespace zombie {
namespace commands {
namespace serverCommands {


class ClearCommand : public CommandBase {
public:
    public ClearCommand(const std::string& var1, const std::string& var2, const std::string& var3, UdpConnection var4) {
      super(var1, var2, var3, var4);
   }

    std::string Command() {
    std::string var1 = "Console cleared";
      if (this.connection == nullptr) {
         for (int var2 = 0; var2 < 100; var2++) {
            System.out.println();
         }
      } else {
    std::stringstream var4 = new std::stringstream();

         for (int var3 = 0; var3 < 50; var3++) {
            var4.append("<LINE>");
         }

         var1 = var4 + var1;
      }

    return var1;
   }
}
} // namespace serverCommands
} // namespace commands
} // namespace zombie
