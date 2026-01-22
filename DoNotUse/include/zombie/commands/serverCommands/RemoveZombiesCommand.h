#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoZombie.h"
#include "zombie/commands/CommandArgs.h"
#include "zombie/commands/CommandBase.h"
#include "zombie/commands/CommandHelp.h"
#include "zombie/commands/CommandName.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/network/GameServer.h"
#include "zombie/popman/NetworkZombiePacker.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/Type.h"

namespace zombie {
namespace commands {
namespace serverCommands {


class RemoveZombiesCommand : public CommandBase {
public:
    public RemoveZombiesCommand(const std::string& var1, const std::string& var2, const std::string& var3, UdpConnection var4) {
      super(var1, var2, var3, var4);
   }

    std::string Command() {
    int var1 = -1;
    int var2 = -1;
    int var3 = -1;
    int var4 = -1;
    bool var5 = false;
    bool var6 = false;
    bool var7 = false;

      for (byte var8 = 0; var8 < this.getCommandArgsCount() - 1; var8 += 2) {
    std::string var9 = this.getCommandArg(int.valueOf(var8));
    std::string var10 = this.getCommandArg(var8 + 1);
         switch (var9) {
            case "-radius":
               var1 = PZMath.tryParseInt(var10, -1);
               break;
            case "-reanimated":
               var5 = StringUtils.tryParseBoolean(var10);
               break;
            case "-x":
               var2 = PZMath.tryParseInt(var10, -1);
               break;
            case "-y":
               var3 = PZMath.tryParseInt(var10, -1);
               break;
            case "-z":
               var4 = PZMath.tryParseInt(var10, -1);
               break;
            case "-remove":
               var6 = StringUtils.tryParseBoolean(var10);
               break;
            case "-clear":
               var7 = StringUtils.tryParseBoolean(var10);
               break;
            default:
               return this.getHelp();
         }
      }

      if (var6) {
         GameServer.removeZombiesConnection = this.connection;
         return "Zombies removed.";
      } else if (var4 >= 0 && var4 < 8) {
         for (int var13 = var3 - var1; var13 <= var3 + var1; var13++) {
            for (int var14 = var2 - var1; var14 <= var2 + var1; var14++) {
    IsoGridSquare var15 = IsoWorld.instance.CurrentCell.getGridSquare(var14, var13, var4);
               if (var15 != nullptr) {
                  if (var7) {
                     if (!var15.getStaticMovingObjects().empty()) {
                        for (int var16 = var15.getStaticMovingObjects().size() - 1; var16 >= 0; var16--) {
    IsoDeadBody var18 = (IsoDeadBody)Type.tryCastTo((IsoMovingObject)var15.getStaticMovingObjects().get(var16), IsoDeadBody.class);
                           if (var18 != nullptr) {
                              GameServer.sendRemoveCorpseFromMap(var18);
                              var18.removeFromWorld();
                              var18.removeFromSquare();
                           }
                        }
                     }
                  } else if (!var15.getMovingObjects().empty()) {
                     for (int var11 = var15.getMovingObjects().size() - 1; var11 >= 0; var11--) {
    IsoZombie var17 = (IsoZombie)Type.tryCastTo((IsoMovingObject)var15.getMovingObjects().get(var11), IsoZombie.class);
                        if (var17 != nullptr && (var5 || !var17.isReanimatedPlayer())) {
                           NetworkZombiePacker.getInstance().deleteZombie(var17);
                           var17.removeFromWorld();
                           var17.removeFromSquare();
                        }
                     }
                  }
               }
            }
         }

         LoggerManager.getLogger("admin").write(this.getExecutorUsername() + " removed zombies near " + var2 + "," + var3, "IMPORTANT");
         return "Zombies removed.";
      } else {
         return "invalid z";
      }
   }
}
} // namespace serverCommands
} // namespace commands
} // namespace zombie
