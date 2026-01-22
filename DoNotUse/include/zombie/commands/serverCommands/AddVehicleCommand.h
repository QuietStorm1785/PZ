#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/commands/AltCommandArgs.h"
#include "zombie/commands/CommandArgs.h"
#include "zombie/commands/CommandBase.h"
#include "zombie/commands/CommandHelp.h"
#include "zombie/commands/CommandName.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerMap.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/VehicleScript.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/VehiclesDB2.h"

namespace zombie {
namespace commands {
namespace serverCommands {


   {
   }
)
class AddVehicleCommand : public CommandBase {
public:
    static const std::string scriptOnly = "Script Only";
    static const std::string scriptPlayer = "Script And Player";
    static const std::string scriptCoordinate = "Script And Coordinate";

    public AddVehicleCommand(const std::string& var1, const std::string& var2, const std::string& var3, UdpConnection var4) {
      super(var1, var2, var3, var4);
   }

    std::string Command() {
    std::string var1 = this.getCommandArg(0);
    VehicleScript var2 = ScriptManager.instance.getVehicle(var1);
      if (var2 == nullptr) {
         return "Unknown vehicle script \"" + var1 + "\"";
      } else {
         var1 = var2.getModule().getName() + "." + var2.getName();
    int var4;
    int var5;
    int var6;
         if (this.argsName == "Script And Player")) {
    std::string var3 = this.getCommandArg(1);
    IsoPlayer var7 = GameServer.getPlayerByUserNameForCommand(var3);
            if (var7 == nullptr) {
               return "User \"" + var3 + "\" not found";
            }

            var4 = PZMath.fastfloor(var7.getX());
            var5 = PZMath.fastfloor(var7.getY());
            var6 = PZMath.fastfloor(var7.getZ());
         } else if (this.argsName == "Script And Coordinate")) {
            var4 = PZMath.fastfloor(float.parseFloat(this.getCommandArg(1)));
            var5 = PZMath.fastfloor(float.parseFloat(this.getCommandArg(2)));
            var6 = PZMath.fastfloor(float.parseFloat(this.getCommandArg(3)));
         } else {
            if (this.connection == nullptr) {
               return "Pass a username or coordinate";
            }

    std::string var10 = this.getExecutorUsername();
    IsoPlayer var11 = GameServer.getPlayerByUserNameForCommand(var10);
            if (var11 == nullptr) {
               return "User \"" + var10 + "\" not found";
            }

            var4 = PZMath.fastfloor(var11.getX());
            var5 = PZMath.fastfloor(var11.getY());
            var6 = PZMath.fastfloor(var11.getZ());
         }

         if (var6 > 0) {
            return "Z coordinate must be 0 for now";
         } else {
    IsoGridSquare var12 = ServerMap.instance.getGridSquare(var4, var5, var6);
            if (var12 == nullptr) {
               return "Invalid location " + var4 + "," + var5 + "," + var6;
            } else {
    BaseVehicle var8 = std::make_shared<BaseVehicle>(IsoWorld.instance.CurrentCell);
               var8.setScriptName(var1);
               var8.setX(var4 - 1.0F);
               var8.setY(var5 - 0.1F);
               var8.setZ(var6 + 0.2F);
               if (IsoChunk.doSpawnedVehiclesInInvalidPosition(var8)) {
                  var8.setSquare(var12);
                  var8.square.chunk.vehicles.push_back(var8);
                  var8.chunk = var8.square.chunk;
                  var8.addToWorld();
                  VehiclesDB2.instance.addVehicle(var8);
                  return "Vehicle spawned";
               } else {
                  return "ERROR: I can not spawn the vehicle. Invalid position. Try to change position.";
               }
            }
         }
      }
   }
}
} // namespace serverCommands
} // namespace commands
} // namespace zombie
