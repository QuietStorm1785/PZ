#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/commands/AltCommandArgs.h"
#include "zombie/commands/CommandArgs.h"
#include "zombie/commands/CommandBase.h"
#include "zombie/commands/CommandHelp.h"
#include "zombie/commands/CommandName.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/raknet/VoiceManager.h"
#include "zombie/network/GameServer.h"

namespace zombie {
namespace commands {
namespace serverCommands {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


 name = "voiceban"
)
 required = {"(.+)"},
 optional = "(-true|-false)"
 ), @CommandArgs(
 optional = "(-true|-false)"
 )})
 helpText = "UI_ServerOptionDesc_VoiceBan"
)
 requiredRights = 48
)
class VoiceBanCommand : public CommandBase {
public:
 public VoiceBanCommand(const std::string& string0, const std::string& string1, const std::string& string2, UdpConnection udpConnection) {
 super(string0, string1, string2, udpConnection);
 }

 std::string Command() {
 std::string string = this->getExecutorUsername();
 if (this->getCommandArgsCount() == 2
 || this->getCommandArgsCount() == 1 && !this->getCommandArg(0) == "-true") && !this->getCommandArg(0) == "-false")) {
 string = this->getCommandArg(0);
 }

 bool boolean0 = true;
 if (this->getCommandArgsCount() > 0) {
 boolean0 = !this->getCommandArg(this->getCommandArgsCount() - 1) == "-false");
 }

 IsoPlayer player = GameServer.getPlayerByUserNameForCommand(string);
 if (player != nullptr) {
 string = player.getDisplayName();
 VoiceManager.instance.VMServerBan(player.OnlineID, boolean0);
 if (boolean0) {
 LoggerManager.getLogger("admin").write(this->getExecutorUsername() + " ban voice " + string);
 return "User " + string + " voice is banned.";
 } else {
 LoggerManager.getLogger("admin").write(this->getExecutorUsername() + " unban voice " + string);
 return "User " + string + " voice is unbanned.";
 }
 } else {
 return "User " + string + " not found.";
 }
 }
}
} // namespace serverCommands
} // namespace commands
} // namespace zombie
