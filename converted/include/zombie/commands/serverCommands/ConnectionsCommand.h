#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/commands/CommandBase.h"
#include "zombie/commands/CommandHelp.h"
#include "zombie/commands/CommandName.h"
#include "zombie/commands/CommandNames.h"
#include "zombie/commands/DisabledCommand.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/GameServer.h"

namespace zombie {
namespace commands {
namespace serverCommands {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


 name = "connections"
 ), @CommandName(
 name = "list"
 )})
 helpText = "UI_ServerOptionDesc_Connections"
)
 requiredRights = 56
)
class ConnectionsCommand : public CommandBase {
public:
 public ConnectionsCommand(const std::string& string0, const std::string& string1, const std::string& string2, UdpConnection udpConnection) {
 super(string0, string1, string2, udpConnection);
 }

 std::string Command() {
 std::string string0 = "";
 std::string string1 = " <LINE> ";
 if (this->connection == nullptr) {
 string1 = "\n";
 }

 for (int int0 = 0; int0 < GameServer.udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection = GameServer.udpEngine.connections.get(int0);

 for (int int1 = 0; int1 < 4; int1++) {
 if (udpConnection.usernames[int1] != nullptr) {
 string0 = string0
 + "connection="
 + (int0 + 1)
 + "/"
 + GameServer.udpEngine.connections.size()
 + " "
 + udpConnection.idStr
 + " player="
 + (int1 + 1)
 + "/4 id="
 + udpConnection.playerIDs[int1]
 + " username=\""
 + udpConnection.usernames[int1]
 + "\" fullyConnected="
 + udpConnection.isFullyConnected()
 + string1;
 }
 }
 }

 return string0 + "Players listed";
 }
}
} // namespace serverCommands
} // namespace commands
} // namespace zombie
