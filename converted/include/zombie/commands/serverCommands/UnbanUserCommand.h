#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/sql/SQLException.h"
#include "zombie/commands/CommandArgs.h"
#include "zombie/commands/CommandBase.h"
#include "zombie/commands/CommandHelp.h"
#include "zombie/commands/CommandName.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/znet/SteamUtils.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerWorldDatabase.h"

namespace zombie {
namespace commands {
namespace serverCommands {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


 name = "unbanuser"
)
 required = {"(.+)"}
)
 helpText = "UI_ServerOptionDesc_UnBanUser"
)
 requiredRights = 48
)
class UnbanUserCommand : public CommandBase {
public:
 public UnbanUserCommand(const std::string& string0, const std::string& string1, const std::string& string2, UdpConnection udpConnection) {
 super(string0, string1, string2, udpConnection);
 }

 std::string Command() {
 std::string string0 = this->getCommandArg(0);
 std::string string1 = ServerWorldDatabase.instance.banUser(string0, false);
 LoggerManager.getLogger("admin").write(this->getExecutorUsername() + " unbanned user " + string0);
 if (!SteamUtils.isSteamModeEnabled()) {
 ServerWorldDatabase.instance.banIp(nullptr, string0, nullptr, false);

 for (int int0 = 0; int0 < GameServer.udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection = GameServer.udpEngine.connections.get(int0);
 if (udpConnection.username == string0) {
 ServerWorldDatabase.instance.banIp(udpConnection.ip, string0, nullptr, false);
 break;
 }
 }
 }

 return string1;
 }
}
} // namespace serverCommands
} // namespace commands
} // namespace zombie
