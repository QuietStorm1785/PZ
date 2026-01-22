#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/Lua/LuaManager/GlobalObject.h"
#include "zombie/commands/CommandArgs.h"
#include "zombie/commands/CommandBase.h"
#include "zombie/commands/CommandHelp.h"
#include "zombie/commands/CommandName.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/Rand.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/skinnedmodel/population/OutfitManager.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/util/StringUtils.h"

namespace zombie {
namespace commands {
namespace serverCommands {


class CreateHorde2Command : public CommandBase {
public:
    public CreateHorde2Command(const std::string& var1, const std::string& var2, const std::string& var3, UdpConnection var4) {
      super(var1, var2, var3, var4);
   }

    std::string Command() {
    int var1 = -1;
    int var2 = -1;
    int var3 = -1;
    int var4 = -1;
    int var5 = -1;
    bool var6 = false;
    bool var7 = false;
    bool var8 = false;
    bool var9 = false;
    float var10 = 1.0F;
    std::string var11 = nullptr;

      for (byte var12 = 0; var12 < this.getCommandArgsCount() - 1; var12 += 2) {
    std::string var13 = this.getCommandArg(int.valueOf(var12));
    std::string var14 = this.getCommandArg(var12 + 1);
         switch (var13) {
            case "-count":
               var1 = PZMath.tryParseInt(var14, -1);
               break;
            case "-radius":
               var2 = PZMath.tryParseInt(var14, -1);
               break;
            case "-x":
               var3 = PZMath.tryParseInt(var14, -1);
               break;
            case "-y":
               var4 = PZMath.tryParseInt(var14, -1);
               break;
            case "-z":
               var5 = PZMath.tryParseInt(var14, -1);
               break;
            case "-outfit":
               var11 = StringUtils.discardNullOrWhitespace(var14);
               break;
            case "-crawler":
               var6 = !"false" == var14);
               break;
            case "-isFallOnFront":
               var7 = !"false" == var14);
               break;
            case "-isFakeDead":
               var8 = !"false" == var14);
               break;
            case "-knockedDown":
               var9 = !"false" == var14);
               break;
            case "-health":
               var10 = float.valueOf(var14);
               break;
            default:
               return this.getHelp();
         }
      }

      var1 = PZMath.clamp(var1, 1, 500);
    IsoGridSquare var18 = IsoWorld.instance.CurrentCell.getGridSquare(var3, var4, var5);
      if (var18 == nullptr) {
         return "invalid location";
      } else if (var11 != nullptr && OutfitManager.instance.FindMaleOutfit(var11) == nullptr && OutfitManager.instance.FindFemaleOutfit(var11) == nullptr) {
         return "invalid outfit";
      } else {
    int var19 = nullptr;
         if (var11 != nullptr) {
            if (OutfitManager.instance.FindFemaleOutfit(var11) == nullptr) {
               var19 = int.MIN_VALUE;
            } else if (OutfitManager.instance.FindMaleOutfit(var11) == nullptr) {
               var19 = int.MAX_VALUE;
            }
         }

         for (int var20 = 0; var20 < var1; var20++) {
    int var15 = var2 <= 0 ? var3 : Rand.Next(var3 - var2, var3 + var2 + 1);
    int var21 = var2 <= 0 ? var4 : Rand.Next(var4 - var2, var4 + var2 + 1);
            GlobalObject.addZombiesInOutfit(var15, var21, var5, 1, var11, var19, var6, var7, var8, var9, var10);
         }

         LoggerManager.getLogger("admin").write(this.getExecutorUsername() + " created a horde of " + var1 + " zombies near " + var3 + "," + var4, "IMPORTANT");
         return "Horde spawned.";
      }
   }
}
} // namespace serverCommands
} // namespace commands
} // namespace zombie
