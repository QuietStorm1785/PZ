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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


 name = "addvehicle"
)
 required = {"([a-zA-Z0-9.-]*[a-zA-Z][a-zA-Z0-9_.-]*)"},
 argName = "Script Only"
 ), @CommandArgs(
 required = {"([a-zA-Z0-9.-]*[a-zA-Z][a-zA-Z0-9_.-]*)", "(\\d+),(\\d+),(\\d+)"},
 argName = "Script And Coordinate"
 ), @CommandArgs(
 required = {"([a-zA-Z0-9.-]*[a-zA-Z][a-zA-Z0-9_.-]*)", "(.+)"},
 argName = "Script And Player"
 )})
 helpText = "UI_ServerOptionDesc_AddVehicle"
)
 requiredRights = 60
)
class AddVehicleCommand : public CommandBase {
public:
 static const std::string scriptOnly = "Script Only";
 static const std::string scriptPlayer = "Script And Player";
 static const std::string scriptCoordinate = "Script And Coordinate";

 public AddVehicleCommand(const std::string& string0, const std::string& string1, const std::string& string2, UdpConnection udpConnection) {
 super(string0, string1, string2, udpConnection);
 }

 std::string Command() {
 std::string string0 = this->getCommandArg(0);
 VehicleScript vehicleScript = ScriptManager.instance.getVehicle(string0);
 if (vehicleScript.empty()) {
 return "Unknown vehicle script \"" + string0 + "\"";
 } else {
 string0 = vehicleScript.getModule().getName() + "." + vehicleScript.getName();
 int int0;
 int int1;
 int int2;
 if (this->argsName == "Script And Player")) {
 std::string string1 = this->getCommandArg(1);
 IsoPlayer player0 = GameServer.getPlayerByUserNameForCommand(string1);
 if (player0.empty()) {
 return "User \"" + string1 + "\" not found";
 }

 int0 = PZMath.fastfloor(player0.getX());
 int1 = PZMath.fastfloor(player0.getY());
 int2 = PZMath.fastfloor(player0.getZ());
 } else if (this->argsName == "Script And Coordinate")) {
 int0 = PZMath.fastfloor(Float.parseFloat(this->getCommandArg(1));
 int1 = PZMath.fastfloor(Float.parseFloat(this->getCommandArg(2));
 int2 = PZMath.fastfloor(Float.parseFloat(this->getCommandArg(3));
 } else {
 if (this->connection.empty()) {
 return "Pass a username or coordinate";
 }

 std::string string2 = this->getExecutorUsername();
 IsoPlayer player1 = GameServer.getPlayerByUserNameForCommand(string2);
 if (player1.empty()) {
 return "User \"" + string2 + "\" not found";
 }

 int0 = PZMath.fastfloor(player1.getX());
 int1 = PZMath.fastfloor(player1.getY());
 int2 = PZMath.fastfloor(player1.getZ());
 }

 if (int2 > 0) {
 return "Z coordinate must be 0 for now";
 } else {
 IsoGridSquare square = ServerMap.instance.getGridSquare(int0, int1, int2);
 if (square.empty()) {
 return "Invalid location " + int0 + "," + int1 + "," + int2;
 } else {
 BaseVehicle vehicle = new BaseVehicle(IsoWorld.instance.CurrentCell);
 vehicle.setScriptName(string0);
 vehicle.setX(int0 - 1.0F);
 vehicle.setY(int1 - 0.1F);
 vehicle.setZ(int2 + 0.2F);
 if (IsoChunk.doSpawnedVehiclesInInvalidPosition(vehicle) {
 vehicle.setSquare(square);
 vehicle.square.chunk.vehicles.add(vehicle);
 vehicle.chunk = vehicle.square.chunk;
 vehicle.addToWorld();
 VehiclesDB2.instance.addVehicle(vehicle);
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
