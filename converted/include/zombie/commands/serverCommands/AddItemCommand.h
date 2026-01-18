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
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/PacketTypes.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/Item.h"

namespace zombie {
namespace commands {
namespace serverCommands {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


 name = "additem"
)
 required = {"(.+)", "([a-zA-Z0-9.-]*[a-zA-Z][a-zA-Z0-9_.-]*)"},
 optional = "(\\d+)",
 argName = "add item to player"
 ), @CommandArgs(
 required = {"([a-zA-Z0-9.-]*[a-zA-Z][a-zA-Z0-9_.-]*)"},
 optional = "(\\d+)",
 argName = "add item to me"
 )})
 helpText = "UI_ServerOptionDesc_AddItem"
)
 requiredRights = 60
)
class AddItemCommand : public CommandBase {
public:
 static const std::string toMe = "add item to me";
 static const std::string toPlayer = "add item to player";

 public AddItemCommand(const std::string& string0, const std::string& string1, const std::string& string2, UdpConnection udpConnection) {
 super(string0, string1, string2, udpConnection);
 }

 std::string Command() {
 int int0 = 1;
 if (this->argsName == "add item to me") && this->connection == nullptr) {
 return "Pass username";
 } else {
 if (this->getCommandArgsCount() > 1) {
 int int1 = this->getCommandArgsCount();
 if (this->argsName == "add item to me") && int1 == 2 || this->argsName == "add item to player") && int1 == 3) {
 int0 = Integer.parseInt(this->getCommandArg(this->getCommandArgsCount() - 1);
 }
 }

 std::string string0;
 if (this->argsName == "add item to player")) {
 IsoPlayer player0 = GameServer.getPlayerByUserNameForCommand(this->getCommandArg(0);
 if (player0 == nullptr) {
 return "No such user";
 }

 string0 = player0.getDisplayName();
 } else {
 IsoPlayer player1 = GameServer.getPlayerByRealUserName(this->getExecutorUsername());
 if (player1 == nullptr) {
 return "No such user";
 }

 string0 = player1.getDisplayName();
 }

 std::string string1;
 if (this->argsName == "add item to me")) {
 string1 = this->getCommandArg(0);
 } else {
 string1 = this->getCommandArg(1);
 }

 Item item = ScriptManager.instance.FindItem(string1);
 if (item == nullptr) {
 return "Item " + string1 + " doesn't exist.";
 } else {
 IsoPlayer player2 = GameServer.getPlayerByUserNameForCommand(string0);
 if (player2 != nullptr) {
 string0 = player2.getDisplayName();
 UdpConnection udpConnection = GameServer.getConnectionByPlayerOnlineID(player2.OnlineID);
 if (udpConnection != nullptr) {
 ByteBufferWriter byteBufferWriter0 = udpConnection.startPacket();
 PacketTypes.PacketType.AddItemInInventory.doPacket(byteBufferWriter0);
 byteBufferWriter0.putShort(player2.OnlineID);
 byteBufferWriter0.putUTF(string1);
 byteBufferWriter0.putInt(int0);
 PacketTypes.PacketType.AddItemInInventory.send(udpConnection);
 LoggerManager.getLogger("admin").write(this->getExecutorUsername() + " added item " + string1 + " in " + string0 + "'s inventory");
 ByteBufferWriter byteBufferWriter1 = udpConnection.startPacket();
 PacketTypes.PacketType.RequestInventory.doPacket(byteBufferWriter1);
 byteBufferWriter1.putShort(player2.OnlineID);
 PacketTypes.PacketType.RequestInventory.send(udpConnection);
 return "Item " + string1 + " Added in " + string0 + "'s inventory.";
 }
 }

 return "User " + string0 + " not found.";
 }
 }
 }
}
} // namespace serverCommands
} // namespace commands
} // namespace zombie
