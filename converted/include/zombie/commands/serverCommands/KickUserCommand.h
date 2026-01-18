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
#include "zombie/commands/CommandNames.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/network/ServerWorldDatabase.h"
#include "zombie/network/Userlog.h"

namespace zombie {
namespace commands {
namespace serverCommands {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


 name = "kick"
 ), @CommandName(
 name = "kickuser"
 )})
 required = {"(.+)"}
 ), @CommandArgs(
 required = {"(.+)", "-r", "(.+)"}
 )})
 helpText = "UI_ServerOptionDesc_Kick"
)
 requiredRights = 56
)
class KickUserCommand : public CommandBase {
public:
 std::string reason = "";

 public KickUserCommand(const std::string& string0, const std::string& string1, const std::string& string2, UdpConnection udpConnection) {
 super(string0, string1, string2, udpConnection);
 }

 std::string Command() {
 std::string string = this->getCommandArg(0);
 if (this->hasOptionalArg(1) {
 this->reason = this->getCommandArg(1);
 }

 LoggerManager.getLogger("admin").write(this->getExecutorUsername() + " kicked user " + string);
 ServerWorldDatabase.instance.addUserlog(string, Userlog.UserlogType.Kicked, this->reason, this->getExecutorUsername(), 1);
 bool boolean0 = false;

 for (int int0 = 0; int0 < GameServer.udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection = GameServer.udpEngine.connections.get(int0);

 for (int int1 = 0; int1 < 4; int1++) {
 if (string == udpConnection.usernames[int1])) {
 boolean0 = true;
 if ("" == this->reason) {
 GameServer.kick(udpConnection, "UI_Policy_Kick", nullptr);
 } else {
 GameServer.kick(udpConnection, "You have been kicked from this server for the following reason: " + this->reason, nullptr);
 }

 udpConnection.forceDisconnect("command-kick");
 GameServer.addDisconnect(udpConnection);
 break;
 }
 }
 }

 if (boolean0 && ServerOptions.instance.BanKickGlobalSound.getValue()) {
 GameServer.PlaySoundAtEveryPlayer("RumbleThunder");
 }

 return boolean0 ? "User " + string + " kicked." : "User " + string + " doesn't exist.";
 }
}
} // namespace serverCommands
} // namespace commands
} // namespace zombie
