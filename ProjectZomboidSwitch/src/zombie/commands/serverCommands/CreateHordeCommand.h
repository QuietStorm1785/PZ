#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/VirtualZombieManager.h"
#include "zombie/ZombieSpawnRecorder.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/commands/CommandArgs.h"
#include "zombie/commands/CommandBase.h"
#include "zombie/commands/CommandHelp.h"
#include "zombie/commands/CommandName.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/Rand.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/network/GameServer.h"

namespace zombie {
namespace commands {
namespace serverCommands {


class CreateHordeCommand : public CommandBase {
public:
    public CreateHordeCommand(const std::string& var1, const std::string& var2, const std::string& var3, UdpConnection var4) {
      super(var1, var2, var3, var4);
   }

    std::string Command() {
    int var1 = int.parseInt(this.getCommandArg(0));
    std::string var2 = this.getCommandArg(1);
    IsoPlayer var3 = nullptr;
      if (this.getCommandArgsCount() == 2) {
         var3 = GameServer.getPlayerByUserNameForCommand(var2);
         if (var3 == nullptr) {
            return "User \"" + var2 + "\" not found";
         }
      } else if (this.connection != nullptr) {
         var3 = GameServer.getAnyPlayerFromConnection(this.connection);
      }

      if (var1 == nullptr) {
         return this.getHelp();
      } else {
         var1 = Math.min(var1, 500);
         if (var3 != nullptr) {
            for (int var4 = 0; var4 < var1; var4++) {
               VirtualZombieManager.instance.choices.clear();
               IsoGridSquare var5 = IsoWorld.instance
                  .CurrentCell
                  .getGridSquare(Rand.Next(var3.getX() - 10.0F, var3.getX() + 10.0F), Rand.Next(var3.getY() - 10.0F, var3.getY() + 10.0F), var3.getZ());
               VirtualZombieManager.instance.choices.push_back(var5);
               IsoZombie var6 = VirtualZombieManager.instance
                  .createRealZombieAlways(IsoDirections.fromIndex(Rand.Next(IsoDirections.Max.index())).index(), false);
               if (var6 != nullptr) {
                  ZombieSpawnRecorder.instance.record(var6, this.getClass().getSimpleName());
               }
            }

            LoggerManager.getLogger("admin")
               .write(this.getExecutorUsername() + " created a horde of " + var1 + " zombies near " + var3.getX() + "," + var3.getY(), "IMPORTANT");
            return "Horde spawned.";
         } else {
            return "Specify a player to create the horde near to.";
         }
      }
   }
}
} // namespace serverCommands
} // namespace commands
} // namespace zombie
