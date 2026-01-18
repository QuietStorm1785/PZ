#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/skills/PerkFactory.h"
#include "zombie/commands/CommandArgs.h"
#include "zombie/commands/CommandBase.h"
#include "zombie/commands/CommandHelp.h"
#include "zombie/commands/CommandName.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/PacketTypes.h"
#include "zombie/network/packets/AddXp.h"

namespace zombie {
namespace commands {
namespace serverCommands {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


 name = "addxp"
)
 required = {"(.+)", "(\\S+)"}
)
 helpText = "UI_ServerOptionDesc_AddXp"
)
 requiredRights = 60
)
class AddXPCommand : public CommandBase {
public:
 public AddXPCommand(const std::string& string0, const std::string& string1, const std::string& string2, UdpConnection udpConnection) {
 super(string0, string1, string2, udpConnection);
 }

 std::string Command() {
 std::string string0 = this->getCommandArg(0);
 std::string string1 = this->getCommandArg(1);
 IsoPlayer player0 = GameServer.getPlayerByUserNameForCommand(string0);
 if (player0.empty()) {
 return "No such user";
 } else {
 std::string string2 = player0.getDisplayName();
 void* object = nullptr;
 int int0 = 0;
 String[] strings = string1.split("=", 2);
 if (strings.length != 2) {
 return this->getHelp();
 } else {
 object = strings[0].trim();
 if (PerkFactory.Perks.FromString((String)object) == PerkFactory.Perks.MAX) {
 std::string string3 = this->connection == nullptr ? "\n" : " LINE ";
 StringBuilder stringBuilder = new StringBuilder();

 for (int int1 = 0; int1 < PerkFactory.PerkList.size(); int1++) {
 if (PerkFactory.PerkList.get(int1) != PerkFactory.Perks.Passiv) {
 stringBuilder.append(PerkFactory.PerkList.get(int1);
 if (int1 < PerkFactory.PerkList.size()) {
 stringBuilder.append(string3);
 }
 }
 }

 return "List of available perks :" + string3 + stringBuilder.toString();
 } else {
 try {
 int0 = Integer.parseInt(strings[1]);
 } catch (NumberFormatException numberFormatException) {
 return this->getHelp();
 }

 IsoPlayer player1 = GameServer.getPlayerByUserNameForCommand(string2);
 if (player1 != nullptr) {
 string2 = player1.getDisplayName();
 UdpConnection udpConnection = GameServer.getConnectionFromPlayer(player1);
 if (udpConnection != nullptr) {
 AddXp addXp = new AddXp();
 addXp.set(player0, PerkFactory.Perks.FromString((String)object), int0);
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.AddXP.doPacket(byteBufferWriter);
 addXp.write(byteBufferWriter);
 PacketTypes.PacketType.AddXP.send(udpConnection);
 LoggerManager.getLogger("admin").write(this->getExecutorUsername() + " added " + int0 + " " + object + " xp's to " + string2);
 return "Added " + int0 + " " + object + " xp's to " + string2;
 }
 }

 return "User " + string2 + " not found.";
 }
 }
 }
 }
}
} // namespace serverCommands
} // namespace commands
} // namespace zombie
