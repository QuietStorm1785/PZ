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
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerMap.h"

namespace zombie {
namespace commands {
namespace serverCommands {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


 name = "save"
)
 helpText = "UI_ServerOptionDesc_Save"
)
 requiredRights = 32
)
class SaveCommand : public CommandBase {
public:
 public SaveCommand(const std::string& string0, const std::string& string1, const std::string& string2, UdpConnection udpConnection) {
 super(string0, string1, string2, udpConnection);
 }

 std::string Command() {
 ServerMap.instance.QueueSaveAll();
 GameServer.PauseAllClients();
 return "World saved";
 }
}
} // namespace serverCommands
} // namespace commands
} // namespace zombie
