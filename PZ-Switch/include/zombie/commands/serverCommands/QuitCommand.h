#pragma once
#include "zombie/commands/CommandBase.h"
#include "zombie/commands/CommandHelp.h"
#include "zombie/commands/CommandName.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/ServerMap.h"
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

 name = "quit"
)
 helpText = "UI_ServerOptionDesc_Quit"
)
 requiredRights = 32
)
class QuitCommand : public CommandBase {
 public:
 public
 QuitCommand(std::string_view string0, std::string_view string1,
 std::string_view string2, UdpConnection udpConnection) {
 super(string0, string1, string2, udpConnection);
 }

 std::string Command() {
 DebugLog.Multiplayer.debugln(this->description);
 ServerMap.instance.QueueSaveAll();
 ServerMap.instance.QueueQuit();
 LoggerManager.getLogger("admin").write(this->getExecutorUsername() +
 " closed server");
 return "Quit";
 }
 }
 } // namespace serverCommands
 } // namespace commands
 } // namespace zombie
