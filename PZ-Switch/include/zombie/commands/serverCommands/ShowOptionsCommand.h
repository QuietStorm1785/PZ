#pragma once
#include "zombie/commands/CommandBase.h"
#include "zombie/commands/CommandHelp.h"
#include "zombie/commands/CommandName.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/ServerOptions.h"
#include <cstdint>
#include <iterator>
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

 name = "showoptions"
)
 helpText = "UI_ServerOptionDesc_ShowOptions"
)
 requiredRights = 63
)
class ShowOptionsCommand : public CommandBase {
 public:
 public
 ShowOptionsCommand(const std::string &string0, const std::string &string1,
 const std::string &string2,
 UdpConnection udpConnection) {
 super(string0, string1, string2, udpConnection);
 }

 std::string Command() {
 Iterator iterator =
 ServerOptions.instance.getPublicOptions().iterator();
 void *object = nullptr;
 std::string string0 = " <LINE> ";
 if (this->connection.empty()) {
 string0 = "\n";
 }

 std::string string1 = "List of Server Options:" + string0;

 while (iterator.hasNext()) {
 object = (String)iterator.next();
 if (!object == "ServerWelcomeMessage")) {
 string1 = string1 + "* " + object + "=" +
 ServerOptions.instance.getOptionByName((String)object)
 .asConfigOption()
 .getValueAsString() +
 string0;
 }
 }

 return string1 + "* ServerWelcomeMessage=" +
 ServerOptions.instance.ServerWelcomeMessage.getValue();
 }
 }
 } // namespace serverCommands
 } // namespace commands
 } // namespace zombie
