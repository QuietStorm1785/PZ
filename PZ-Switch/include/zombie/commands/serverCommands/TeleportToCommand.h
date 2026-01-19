#pragma once
#include "zombie/characters/IsoPlayer.h"
#include "zombie/commands/AltCommandArgs.h"
#include "zombie/commands/CommandArgs.h"
#include "zombie/commands/CommandBase.h"
#include "zombie/commands/CommandHelp.h"
#include "zombie/commands/CommandName.h"
#include "zombie/commands/CommandNames.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/PacketTypes.h"
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace commands {
namespace serverCommands {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

 name = "teleportto"
 ), @CommandName(
 name = "tpto"
 )
 })
 required = {"(.+)", "(\\d+),(\\d+),(\\d+)"},
 argName = "Teleport user"
 ), @CommandArgs(
 required = {"(\\d+),(\\d+),(\\d+)"},
 argName = "teleport me"
 )
 })
 helpText = "UI_ServerOptionDesc_TeleportTo"
)
 requiredRights = 62
)
class TeleportToCommand : public CommandBase {
 public:
 static const std::string teleportMe = "teleport me";
 static const std::string teleportUser = "Teleport user";
 std::string username;
 private
 Float[] coords;

 public
 TeleportToCommand(std::string_view string0,
 std::string_view string1,
 std::string_view string2,
 UdpConnection udpConnection) {
 super(string0, string1, string2, udpConnection);
 }

 std::string Command() {
 std::string string = this->argsName;
 switch (string) {
 case "teleport me":
 this->coords = new Float[3];

 for (int int0 = 0; int0 < 3; int0++) {
 this->coords[int0] = Float.parseFloat(this->getCommandArg(int0);
 }

 return this->TeleportMeToCoords();
 case "Teleport user":
 this->username = this->getCommandArg(0);
 this->coords = new Float[3];

 for (int int1 = 0; int1 < 3; int1++) {
 this->coords[int1] =
 Float.parseFloat(this->getCommandArg(int1 + 1);
 }

 return this->TeleportUserToCoords();
 default:
 return this->CommandArgumentsNotMatch();
 }
 }

 std::string TeleportMeToCoords() {
 float float0 = this->coords[0];
 float float1 = this->coords[1];
 float float2 = this->coords[2];
 if (this->connection.empty()) {
 return "Error";
 } else {
 ByteBufferWriter byteBufferWriter = this->connection.startPacket();
 PacketTypes.PacketType.Teleport.doPacket(byteBufferWriter);
 byteBufferWriter.putByte((byte)0);
 byteBufferWriter.putFloat(float0);
 byteBufferWriter.putFloat(float1);
 byteBufferWriter.putFloat(float2);
 PacketTypes.PacketType.Teleport.send(this->connection);
 if (this->connection.players[0] != nullptr &&
 this->connection.players[0].getNetworkCharacterAI() !=
 nullptr) {
 this->connection.players[0]
 .getNetworkCharacterAI()
 .resetSpeedLimiter();
 }

 LoggerManager.getLogger("admin").write(
 this->getExecutorUsername() + " teleported to " + (int)float0 +
 "," + (int)float1 + "," + (int)float2);
 return "teleported to " + (int)float0 + "," + (int)float1 + "," +
 (int)float2 +
 " please wait two seconds to show the map around you.";
 }
 }

 std::string TeleportUserToCoords() {
 float float0 = this->coords[0];
 float float1 = this->coords[1];
 float float2 = this->coords[2];
 if (this->connection != nullptr &&
 this->connection.accessLevel == 2 &&
 !this->username == this->getExecutorUsername())) {
 return "An Observer can only teleport himself";
 }
 else {
 IsoPlayer player =
 GameServer.getPlayerByUserNameForCommand(this->username);
 if (player.empty()) {
 return "Can't find player " + this->username;
 } else {
 UdpConnection udpConnection =
 GameServer.getConnectionFromPlayer(player);
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.Teleport.doPacket(byteBufferWriter);
 byteBufferWriter.putByte((byte)0);
 byteBufferWriter.putFloat(float0);
 byteBufferWriter.putFloat(float1);
 byteBufferWriter.putFloat(float2);
 PacketTypes.PacketType.Teleport.send(udpConnection);
 if (player.getNetworkCharacterAI() != nullptr) {
 player.getNetworkCharacterAI().resetSpeedLimiter();
 }

 LoggerManager.getLogger("admin").write(
 this->getExecutorUsername() + " teleported to " +
 (int)float0 + "," + (int)float1 + "," + (int)float2);
 return this->username + " teleported to " + (int)float0 + "," +
 (int)float1 + "," + (int)float2 +
 " please wait two seconds to show the map around you.";
 }
 }
 }

 std::string CommandArgumentsNotMatch() { return this->getHelp(); }
 }
 } // namespace serverCommands
 } // namespace commands
 } // namespace zombie
