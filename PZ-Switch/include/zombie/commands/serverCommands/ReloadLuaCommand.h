#pragma once
#include "zombie/Lua/LuaManager.h"
#include "zombie/commands/CommandArgs.h"
#include "zombie/commands/CommandBase.h"
#include "zombie/commands/CommandHelp.h"
#include "zombie/commands/CommandName.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/raknet/UdpConnection.h"
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

 name = "reloadlua"
)
 required = {"(\\S+)"}
)
 helpText = "UI_ServerOptionDesc_ReloadLua"
)
 requiredRights = 32
)
class ReloadLuaCommand : public CommandBase {
 public:
 public
 ReloadLuaCommand(std::string_view string0, std::string_view string1,
 std::string_view string2,
 UdpConnection udpConnection) {
 super(string0, string1, string2, udpConnection);
 }

 std::string Command() {
 std::string string0 = this->getCommandArg(0);

 for (String string1 : LuaManager.loaded) {
 if (string1.endsWith(string0) {
 LuaManager.loaded.remove(string1);
 LuaManager.RunLua(string1, true);
 return "Lua file reloaded";
 }
 }

 return "Unknown Lua file";
 }
 }
 } // namespace serverCommands
 } // namespace commands
 } // namespace zombie
