#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/skills/PerkFactory.h"
#include "zombie/characters/skills/PerkFactory/Perks.h"
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
#include "zombie/network/packets/AddXp.h"

namespace zombie {
namespace commands {
namespace serverCommands {


class AddXPCommand : public CommandBase {
public:
    public AddXPCommand(const std::string& var1, const std::string& var2, const std::string& var3, UdpConnection var4) {
      super(var1, var2, var3, var4);
   }

    std::string Command() {
    std::string var1 = this.getCommandArg(0);
    std::string var2 = this.getCommandArg(1);
    IsoPlayer var3 = GameServer.getPlayerByUserNameForCommand(var1);
      if (var3 == nullptr) {
         return "No such user";
      } else {
    std::string var4 = var3.getDisplayName();
    void* var5 = nullptr;
    int var6 = 0;
         std::string[] var7 = var2.split("=", 2);
         if (var7.length != 2) {
            return this.getHelp();
         } else {
            var5 = var7[0].trim();
            if (Perks.FromString((std::string)var5) == Perks.MAX) {
    std::string var15 = this.connection == nullptr ? "\n" : " LINE ";
    std::stringstream var16 = new std::stringstream();

               for (int var17 = 0; var17 < PerkFactory.PerkList.size(); var17++) {
                  if (PerkFactory.PerkList.get(var17) != Perks.Passiv) {
                     var16.append(PerkFactory.PerkList.get(var17));
                     if (var17 < PerkFactory.PerkList.size()) {
                        var16.append(var15);
                     }
                  }
               }

               return "List of available perks :" + var15 + var16;
            } else {
               try {
                  var6 = int.parseInt(var7[1]);
               } catch (NumberFormatException var12) {
                  return this.getHelp();
               }

    IsoPlayer var8 = GameServer.getPlayerByUserNameForCommand(var4);
               if (var8 != nullptr) {
                  var4 = var8.getDisplayName();
    UdpConnection var9 = GameServer.getConnectionFromPlayer(var8);
                  if (var9 != nullptr) {
    AddXp var10 = std::make_shared<AddXp>();
                     var10.set(var3, Perks.FromString((std::string)var5), var6);
    ByteBufferWriter var11 = var9.startPacket();
                     PacketType.AddXP.doPacket(var11);
                     var10.write(var11);
                     PacketType.AddXP.send(var9);
                     LoggerManager.getLogger("admin").write(this.getExecutorUsername() + " added " + var6 + " " + var5 + " xp's to " + var4);
                     return "Added " + var6 + " " + var5 + " xp's to " + var4;
                  }
               }

               return "User " + var4 + " not found.";
            }
         }
      }
   }
}
} // namespace serverCommands
} // namespace commands
} // namespace zombie
