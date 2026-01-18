#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/commands/CommandArgs.h"
#include "zombie/commands/CommandBase.h"
#include "zombie/commands/CommandHelp.h"
#include "zombie/commands/CommandName.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerOptions.h"
#include <algorithm>

namespace zombie {
namespace commands {
namespace serverCommands {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


 name = "help"
)
 optional = "(\\w+)"
)
 helpText = "UI_ServerOptionDesc_Help"
)
 requiredRights = 32
)
class HelpCommand : public CommandBase {
public:
 public HelpCommand(const std::string& string0, const std::string& string1, const std::string& string2, UdpConnection udpConnection) {
 super(string0, string1, string2, udpConnection);
 }

 std::string Command() {
 std::string string0 = this->getCommandArg(0);
 if (string0 != nullptr) {
 Class clazz0 = findCommandCls(string0);
 return clazz0 != nullptr ? getHelp(clazz0) : "Unknown command /" + string0;
 } else {
 std::string string1 = " <LINE> ";
 StringBuilder stringBuilder = new StringBuilder();
 if (this->connection == nullptr) {
 string1 = "\n";
 }

 if (!GameServer.bServer) {
 for (String string2 : ServerOptions.getClientCommandList(this->connection != nullptr) {
 stringBuilder.append(string2);
 }
 }

 stringBuilder.append("List of ").append("server").append(" commands : ");
 std::string string3 = "";
 TreeMap treeMap = new TreeMap();

 for (Class clazz1 : getSubClasses()) {
 if (!isDisabled(clazz1) {
 string3 = getHelp(clazz1);
 if (string3 != nullptr) {
 treeMap.put(getCommandName(clazz1), string3);
 }
 }
 }

 for (Entry entry : treeMap.entrySet()) {
 stringBuilder.append(string1).append("* ").append((String)entry.getKey()).append(" : ").append((String)entry.getValue());
 }

 return stringBuilder.toString();
 }
 }
}
} // namespace serverCommands
} // namespace commands
} // namespace zombie
