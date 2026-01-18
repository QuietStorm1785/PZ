#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/sql/SQLException.h"
#include "zombie/commands/AltCommandArgs.h"
#include "zombie/commands/CommandArgs.h"
#include "zombie/commands/CommandBase.h"
#include "zombie/commands/CommandHelp.h"
#include "zombie/commands/CommandName.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/znet/SteamUtils.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/network/ServerWorldDatabase.h"
#include "zombie/network/Userlog.h"

namespace zombie {
namespace commands {
namespace serverCommands {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


 name = "banuser"
)
 required = {"(.+)"},
 argName = "Ban User Only"
 ), @CommandArgs(
 required = {"(.+)", "-ip"},
 argName = "Ban User And IP"
 ), @CommandArgs(
 required = {"(.+)", "-r", "(.+)"},
 argName = "Ban User And Supply Reason"
 ), @CommandArgs(
 required = {"(.+)", "-ip", "-r", "(.+)"},
 argName = "Ban User And IP And Supply Reason"
 )})
 helpText = "UI_ServerOptionDesc_BanUser"
)
 requiredRights = 48
)
class BanUserCommand : public CommandBase {
public:
 std::string reason = "";
 static const std::string banUser = "Ban User Only";
 static const std::string banWithIP = "Ban User And IP";
 static const std::string banWithReason = "Ban User And Supply Reason";
 static const std::string banWithReasonIP = "Ban User And IP And Supply Reason";

 public BanUserCommand(const std::string& string0, const std::string& string1, const std::string& string2, UdpConnection udpConnection) {
 super(string0, string1, string2, udpConnection);
 }

 std::string Command() {
 std::string string0 = this->getCommandArg(0);
 if (this->hasOptionalArg(1) {
 this->reason = this->getCommandArg(1);
 }

 bool boolean0 = false;
 std::string string1 = this->argsName;
 switch (string1) {
 case "Ban User And IP":
 case "Ban User And IP And Supply Reason":
 boolean0 = true;
 default:
 string1 = ServerWorldDatabase.instance.banUser(string0, true);
 ServerWorldDatabase.instance.addUserlog(string0, Userlog.UserlogType.Banned, this->reason, this->getExecutorUsername(), 1);
 LoggerManager.getLogger("admin")
 .write(this->getExecutorUsername() + " banned user " + string0 + (this->reason != nullptr ? this->reason : ""), "IMPORTANT");
 bool boolean1 = false;

 for (int int0 = 0; int0 < GameServer.udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection = GameServer.udpEngine.connections.get(int0);
 if (udpConnection.username == string0) {
 boolean1 = true;
 if (SteamUtils.isSteamModeEnabled()) {
 LoggerManager.getLogger("admin")
 .write(
 this->getExecutorUsername()
 + " banned steamid "
 + udpConnection.steamID
 + "("
 + udpConnection.username
 + ")"
 + (this->reason != nullptr ? this->reason : ""),
 "IMPORTANT"
 );
 std::string string2 = SteamUtils.convertSteamIDToString(udpConnection.steamID);
 ServerWorldDatabase.instance.banSteamID(string2, this->reason, true);
 }

 if (boolean0) {
 LoggerManager.getLogger("admin")
 .write(
 this->getExecutorUsername()
 + " banned ip "
 + udpConnection.ip
 + "("
 + udpConnection.username
 + ")"
 + (this->reason != nullptr ? this->reason : ""),
 "IMPORTANT"
 );
 ServerWorldDatabase.instance.banIp(udpConnection.ip, string0, this->reason, true);
 }

 if ("" == this->reason) {
 GameServer.kick(udpConnection, "UI_Policy_Ban", nullptr);
 } else {
 GameServer.kick(udpConnection, "You have been banned from this server for the following reason: " + this->reason, nullptr);
 }

 udpConnection.forceDisconnect("command-ban-ip");
 break;
 }
 }

 if (boolean1 && ServerOptions.instance.BanKickGlobalSound.getValue()) {
 GameServer.PlaySoundAtEveryPlayer("Thunder");
 }

 return string1;
 }
 }
}
} // namespace serverCommands
} // namespace commands
} // namespace zombie
