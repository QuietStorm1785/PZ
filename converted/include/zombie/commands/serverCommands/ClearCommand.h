#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/commands/CommandBase.h"
#include "zombie/commands/CommandName.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/raknet/UdpConnection.h"

namespace zombie {
namespace commands {
namespace serverCommands {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


 name = "clear"
)
 requiredRights = 32
)
class ClearCommand : public CommandBase {
public:
 public ClearCommand(const std::string& string0, const std::string& string1, const std::string& string2, UdpConnection udpConnection) {
 super(string0, string1, string2, udpConnection);
 }

 std::string Command() {
 std::string string = "Console cleared";
 if (this->connection.empty()) {
 for (int int0 = 0; int0 < 100; int0++) {
 System.out.println();
 }
 } else {
 StringBuilder stringBuilder = new StringBuilder();

 for (int int1 = 0; int1 < 50; int1++) {
 stringBuilder.append("<LINE>");
 }

 string = stringBuilder.toString() + string;
 }

 return string;
 }
}
} // namespace serverCommands
} // namespace commands
} // namespace zombie
