#pragma once
#include "zombie/commands/CommandArgs.h"
#include "zombie/commands/CommandBase.h"
#include "zombie/commands/CommandHelp.h"
#include "zombie/commands/CommandName.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/chat/ChatServer.h"
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

 name = "servermsg"
)
 required = {"(.+)"}
)
 helpText = "UI_ServerOptionDesc_ServerMsg"
)
 requiredRights = 56
)
class ServerMessageCommand : public CommandBase {
 public:
 public
 ServerMessageCommand(std::string_view string0,
 std::string_view string1,
 std::string_view string2,
 UdpConnection udpConnection) {
 super(string0, string1, string2, udpConnection);
 }

 std::string Command() {
 std::string string0 = this->getCommandArg(0);
 if (this->connection.empty()) {
 ChatServer.getInstance().sendServerAlertMessageToServerChat(string0);
 } else {
 std::string string1 = this->getExecutorUsername();
 ChatServer.getInstance().sendServerAlertMessageToServerChat(string1,
 string0);
 }

 return "Message sent.";
 }
 }
 } // namespace serverCommands
 } // namespace commands
 } // namespace zombie
