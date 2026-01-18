#pragma once
#include "java/sql/SQLException.h"
#include "zombie/commands/CommandBase.h"
#include "zombie/commands/CommandHelp.h"
#include "zombie/commands/CommandName.h"
#include "zombie/commands/DisabledCommand.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerWorldDatabase.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace commands {
namespace serverCommands {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

 name = "addalltowhitelist"
)
 helpText = "UI_ServerOptionDesc_AddAllWhitelist"
)
 requiredRights = 48
)
class AddAllToWhiteListCommand : public CommandBase {
 public:
 public
 AddAllToWhiteListCommand(const std::string &string0,
 const std::string &string1,
 const std::string &string2,
 UdpConnection udpConnection) {
 super(string0, string1, string2, udpConnection);
 }

 std::string Command() {
 StringBuilder stringBuilder = new StringBuilder("");

 for (int int0 = 0; int0 < GameServer.udpEngine.connections.size();
 int0++) {
 UdpConnection udpConnection =
 GameServer.udpEngine.connections.get(int0);
 if (udpConnection.password != nullptr &&
 !udpConnection.password == "")) {
 LoggerManager.getLogger("admin").write(
 this->getExecutorUsername() + " created user " +
 udpConnection.username + " with password " +
 udpConnection.password);

 try {
 stringBuilder
 .append(ServerWorldDatabase.instance.addUser(
 udpConnection.username, udpConnection.password)
 .append(" <LINE> ");
 } catch (SQLException sQLException) {
 sQLException.printStackTrace();
 }
 }
 else {
 stringBuilder.append("User ")
 .append(udpConnection.username)
 .append(" doesn't have a password. <LINE> ");
 }
 }

 stringBuilder.append("Done.");
 return stringBuilder.toString();
 }
 }
 } // namespace serverCommands
 } // namespace commands
 } // namespace zombie
