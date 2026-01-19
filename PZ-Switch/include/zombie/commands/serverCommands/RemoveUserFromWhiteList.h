#pragma once
#include "java/sql/SQLException.h"
#include "zombie/commands/CommandArgs.h"
#include "zombie/commands/CommandBase.h"
#include "zombie/commands/CommandHelp.h"
#include "zombie/commands/CommandName.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/raknet/UdpConnection.h"
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

 name = "removeuserfromwhitelist"
)
 required = {"(.+)"}
)
 helpText = "UI_ServerOptionDesc_RemoveWhitelist"
)
 requiredRights = 48
)
class RemoveUserFromWhiteList : public CommandBase {
 public:
 public
 RemoveUserFromWhiteList(std::string_view string0,
 std::string_view string1,
 std::string_view string2,
 UdpConnection udpConnection) {
 super(string0, string1, string2, udpConnection);
 }

 std::string Command() {
 std::string string = this->getCommandArg(0);
 LoggerManager.getLogger("admin").write(this->getExecutorUsername() +
 " removed user " + string +
 " from whitelist");
 return ServerWorldDatabase.instance.removeUser(string);
 }
 }
 } // namespace serverCommands
 } // namespace commands
 } // namespace zombie
