#pragma once
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

 name = "banid"
)
 required = {"(.+)"}
)
 helpText = "UI_ServerOptionDesc_BanSteamId"
)
 requiredRights = 48
)
class BanSteamIDCommand : public CommandBase {
 public:
 public
 BanSteamIDCommand(std::string_view string0, std::string_view string1,
 std::string_view string2,
 UdpConnection udpConnection) {
 super(string0, string1, string2, udpConnection);
 }

 std::string Command() {
 std::string string = this->getCommandArg(0);
 if (!SteamUtils.isSteamModeEnabled()) {
 return "Server is not in Steam mode";
 } else if (!SteamUtils.isValidSteamID(string) {
 return "Expected SteamID but got \"" + string + "\"";
 } else {
 LoggerManager.getLogger("admin").write(
 this->getExecutorUsername() + " banned SteamID " + string,
 "IMPORTANT");
 ServerWorldDatabase.instance.banSteamID(string, "", true);
 long long0 = SteamUtils.convertStringToSteamID(string);

 for (int int0 = 0; int0 < GameServer.udpEngine.connections.size();
 int0++) {
 UdpConnection udpConnection =
 GameServer.udpEngine.connections.get(int0);
 if (udpConnection.steamID == long0) {
 GameServer.kick(udpConnection, "UI_Policy_Ban", nullptr);
 udpConnection.forceDisconnect("command-ban-sid");
 break;
 }
 }

 return "SteamID " + string + " is now banned";
 }
 }
 }
 } // namespace serverCommands
 } // namespace commands
 } // namespace zombie
