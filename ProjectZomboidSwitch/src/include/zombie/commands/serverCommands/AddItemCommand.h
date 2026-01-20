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
#include "zombie/network/PacketTypes/PacketType.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/Item.h"

namespace zombie {
namespace commands {
namespace serverCommands {


   {
   }
)
class AddItemCommand : public CommandBase {
public:
    static const std::string toMe = "add item to me";
    static const std::string toPlayer = "add item to player";

    public AddItemCommand(const std::string& var1, const std::string& var2, const std::string& var3, UdpConnection var4) {
      super(var1, var2, var3, var4);
   }

    std::string Command() {
    int var1 = 1;
      if (this.argsName == "add item to me") && this.connection == nullptr) {
         return "Pass username";
      } else {
         if (this.getCommandArgsCount() > 1) {
    int var2 = this.getCommandArgsCount();
            if (this.argsName == "add item to me") && var2 == 2 || this.argsName == "add item to player") && var2 == 3) {
               var1 = int.parseInt(this.getCommandArg(this.getCommandArgsCount() - 1));
            }
         }

    std::string var9;
         if (this.argsName == "add item to player")) {
    IsoPlayer var3 = GameServer.getPlayerByUserNameForCommand(this.getCommandArg(0));
            if (var3 == nullptr) {
               return "No such user";
            }

            var9 = var3.getDisplayName();
         } else {
    IsoPlayer var10 = GameServer.getPlayerByRealUserName(this.getExecutorUsername());
            if (var10 == nullptr) {
               return "No such user";
            }

            var9 = var10.getDisplayName();
         }

    std::string var11;
         if (this.argsName == "add item to me")) {
            var11 = this.getCommandArg(0);
         } else {
            var11 = this.getCommandArg(1);
         }

    Item var4 = ScriptManager.instance.FindItem(var11);
         if (var4 == nullptr) {
            return "Item " + var11 + " doesn't exist.";
         } else {
    IsoPlayer var5 = GameServer.getPlayerByUserNameForCommand(var9);
            if (var5 != nullptr) {
               var9 = var5.getDisplayName();
    UdpConnection var6 = GameServer.getConnectionByPlayerOnlineID(var5.OnlineID);
               if (var6 != nullptr) {
    ByteBufferWriter var7 = var6.startPacket();
                  PacketType.AddItemInInventory.doPacket(var7);
                  var7.putShort(var5.OnlineID);
                  var7.putUTF(var11);
                  var7.putInt(var1);
                  PacketType.AddItemInInventory.send(var6);
                  LoggerManager.getLogger("admin").write(this.getExecutorUsername() + " added item " + var11 + " in " + var9 + "'s inventory");
    ByteBufferWriter var8 = var6.startPacket();
                  PacketType.RequestInventory.doPacket(var8);
                  var8.putShort(var5.OnlineID);
                  PacketType.RequestInventory.send(var6);
                  return "Item " + var11 + " Added in " + var9 + "'s inventory.";
               }
            }

            return "User " + var9 + " not found.";
         }
      }
   }
}
} // namespace serverCommands
} // namespace commands
} // namespace zombie
