#pragma once
#include "java/sql/SQLException.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/commands/CommandArgs.h"
#include "zombie/commands/CommandBase.h"
#include "zombie/commands/CommandHelp.h"
#include "zombie/commands/CommandName.h"
#include "zombie/commands/PlayerType.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerWorldDatabase.h"
#include "zombie/network/chat/ChatServer.h"
#include <cstdint>
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

    name = "setaccesslevel"
)
    required = {"(.+)", "(\\w+)"}
)
    helpText = "UI_ServerOptionDesc_SetAccessLevel"
)
    requiredRights = 48
)
class SetAccessLevelCommand : public CommandBase {
    public:
    public
      SetAccessLevelCommand(const std::string &string0,
                            const std::string &string1,
                            const std::string &string2,
                            UdpConnection udpConnection) {
        super(string0, string1, string2, udpConnection);
      }

      std::string Command() {
        std::string string0 = this.getCommandArg(0);
        std::string string1 =
            "none".equals(this.getCommandArg(1)) ? "" : this.getCommandArg(1);
        return update();
      }

      static std::string update(const std::string &string2,
                                UdpConnection udpConnection0,
                                const std::string &string0,
                                const std::string &string1) {
        if ((udpConnection0 == nullptr || !udpConnection0.isCoopHost) &&
            !ServerWorldDatabase.instance.containsUser(string0) &&
            udpConnection0 != nullptr) {
          return "User \"" + string0 +
                 "\" is not in the whitelist, use /adduser first";
        } else {
          IsoPlayer player = GameServer.getPlayerByUserName(string0);
          uint8_t byte0 = PlayerType.fromString(string1.trim().toLowerCase());
          if (udpConnection0 != nullptr && udpConnection0.accessLevel == 16 &&
              byte0 == 32) {
            return "Moderators can't set Admin access level";
          } else if (byte0 == 0) {
            return "Access Level '" + byte0 +
                   "' unknown, list of access level: player, admin, moderator, "
                   "overseer, gm, observer";
          } else {
            if (player != nullptr) {
              if (player.networkAI != nullptr) {
                player.networkAI.setCheckAccessLevelDelay(5000L);
              }

              UdpConnection udpConnection1 =
                  GameServer.getConnectionFromPlayer(player);
              uint8_t byte1;
              if (udpConnection1 != nullptr) {
                byte1 = udpConnection1.accessLevel;
              } else {
                byte1 = PlayerType.fromString(player.accessLevel.toLowerCase());
              }

              if (byte1 != byte0) {
                if (byte0 == 32) {
                  ChatServer.getInstance().joinAdminChat(player.OnlineID);
                } else if (byte1 == 32 && byte0 != 32) {
                  ChatServer.getInstance().leaveAdminChat(player.OnlineID);
                }
              }

              if (byte1 != 1 && byte0 == 1) {
                player.setGhostMode(false);
                player.setNoClip(false);
              }

              player.accessLevel = PlayerType.toString(byte0);
              if (udpConnection1 != nullptr) {
                udpConnection1.accessLevel = byte0;
              }

              if ((byte0 & 62) != 0) {
                player.setGodMod(true);
                player.setGhostMode(true);
                player.setInvisible(true);
              } else {
                player.setGodMod(false);
                player.setGhostMode(false);
                player.setInvisible(false);
              }

              GameServer.sendPlayerExtraInfo(player, nullptr);
            }

            LoggerManager.getLogger("admin").write(
                string2 + " granted " + byte0 + " access level on " + string0);
            return udpConnection0 != nullptr && udpConnection0.isCoopHost
                       ? "Your access level is now: " + byte0
                       : ServerWorldDatabase.instance.setAccessLevel(
                             string0, PlayerType.toString(byte0));
          }
        }
      }
    }
    } // namespace serverCommands
    } // namespace commands
    } // namespace zombie
