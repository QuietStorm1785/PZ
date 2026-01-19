#pragma once
#include "zombie/commands/CommandBase.h"
#include "zombie/commands/CommandHelp.h"
#include "zombie/commands/CommandName.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/GameServer.h"
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

 name = "players"
)
 helpText = "UI_ServerOptionDesc_Players"
)
 requiredRights = 62
)
class PlayersCommand : public CommandBase {
 public:
 public
 PlayersCommand(std::string_view string0, std::string_view string1,
 std::string_view string2, UdpConnection udpConnection) {
 super(string0, string1, string2, udpConnection);
 }

 std::string Command() {
 std::vector arrayList = new ArrayList();

 for (int int0 = 0; int0 < GameServer.udpEngine.connections.size();
 int0++) {
 UdpConnection udpConnection =
 GameServer.udpEngine.connections.get(int0);

 for (int int1 = 0; int1 < 4; int1++) {
 if (udpConnection.usernames[int1] != nullptr) {
 arrayList.add(udpConnection.usernames[int1]);
 }
 }
 }

 StringBuilder stringBuilder =
 new StringBuilder("Players connected (" + arrayList.size() + "): ");
 std::string string0 = " <LINE> ";
 if (this->connection.empty()) {
 string0 = "\n";
 }

 stringBuilder.append(string0);

 for (auto &string1 : arrayList)
 stringBuilder.append("-").append(string1).append(string0);
 }

 return stringBuilder.toString();
 }
 }
 } // namespace serverCommands
 } // namespace commands
 } // namespace zombie
