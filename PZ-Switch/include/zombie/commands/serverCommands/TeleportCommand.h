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

 name = "teleport"
 ), @CommandName(
 name = "tp"
 )
 })
 required = {"(.+)"},
 argName = "just port to user"
 ), @CommandArgs(
 required = {"(.+)", "(.+)"},
 argName = "teleport user1 to user 2"
 )
 })
 helpText = "UI_ServerOptionDesc_Teleport"
)
 requiredRights = 62
)
class TeleportCommand : public CommandBase {
 public:
 static const std::string justToUser = "just port to user";
 static const std::string portUserToUser = "teleport user1 to user 2";
 std::string username1;
 std::string username2;

 public
 TeleportCommand(std::string_view string0,
 std::string_view string1,
 std::string_view string2,
 UdpConnection udpConnection) {
 super(string0, string1, string2, udpConnection);
 }

 std::string Command() {
 std::string string = this->argsName;
 switch (string) {
 case "just port to user":
 this->username1 = this->getCommandArg(0);
 return this->TeleportMeToUser();
 case "teleport user1 to user 2":
 this->username1 = this->getCommandArg(0);
 this->username2 = this->getCommandArg(1);
 return this->TeleportUser1ToUser2();
 default:
 return this->CommandArgumentsNotMatch();
 }
 }

 std::string TeleportMeToUser() {
 if (this->connection.empty()) {
 return "Need player to teleport to, ex /teleport user1 user2";
 } else {
 IsoPlayer player =
 GameServer.getPlayerByUserNameForCommand(this->username1);
 if (player != nullptr) {
 this->username1 = player.getDisplayName();
 ByteBufferWriter byteBufferWriter =
 this->connection.startPacket();
 PacketTypes.PacketType.Teleport.doPacket(byteBufferWriter);
 byteBufferWriter.putByte((byte)0);
 byteBufferWriter.putFloat(player.getX());
 byteBufferWriter.putFloat(player.getY());
 byteBufferWriter.putFloat(player.getZ());
 PacketTypes.PacketType.Teleport.send(this->connection);
 if (this->connection.players[0] != nullptr &&
 this->connection.players[0].getNetworkCharacterAI() !=
 nullptr) {
 this->connection.players[0]
 .getNetworkCharacterAI()
 .resetSpeedLimiter();
 }

 LoggerManager.getLogger("admin").write(
 this->getExecutorUsername() + " teleport to " +
 this->username1);
 return "teleported to " + this->username1 +
 " please wait two seconds to show the map around you.";
 } else {
 return "Can't find player " + this->username1;
 }
 }
 }

 std::string TeleportUser1ToUser2() {
 if (this->getAccessLevel() == 2 &&
 !this->username1 == this->getExecutorUsername())) {
 return "An Observer can only teleport himself";
 }
 else {
 IsoPlayer player0 =
 GameServer.getPlayerByUserNameForCommand(this->username1);
 IsoPlayer player1 =
 GameServer.getPlayerByUserNameForCommand(this->username2);
 if (player0.empty()) {
 return "Can't find player " + this->username1;
 } else if (player1.empty()) {
 return "Can't find player " + this->username2;
 } else {
 this->username1 = player0.getDisplayName();
 this->username2 = player1.getDisplayName();
 UdpConnection udpConnection =
 GameServer.getConnectionFromPlayer(player0);
 if (udpConnection.empty()) {
 return "No connection for player " + this->username1;
 } else {
 ByteBufferWriter byteBufferWriter =
 udpConnection.startPacket();
 PacketTypes.PacketType.Teleport.doPacket(byteBufferWriter);
 byteBufferWriter.putByte((byte)player0.PlayerIndex);
 byteBufferWriter.putFloat(player1.getX());
 byteBufferWriter.putFloat(player1.getY());
 byteBufferWriter.putFloat(player1.getZ());
 PacketTypes.PacketType.Teleport.send(udpConnection);
 if (player0.getNetworkCharacterAI() != nullptr) {
 player0.getNetworkCharacterAI().resetSpeedLimiter();
 }

 LoggerManager.getLogger("admin").write(
 this->getExecutorUsername() + " teleported " +
 this->username1 + " to " + this->username2);
 return "teleported " + this->username1 + " to " +
 this->username2;
 }
 }
 }
 }

 std::string CommandArgumentsNotMatch() { return this->getHelp(); }
 }
 } // namespace serverCommands
 } // namespace commands
 } // namespace zombie
