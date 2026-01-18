#pragma once
#include "java/sql/SQLException.h"
#include "zombie/commands/CommandArgs.h"
#include "zombie/commands/CommandBase.h"
#include "zombie/commands/CommandHelp.h"
#include "zombie/commands/CommandName.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/znet/SteamGameServer.h"
#include "zombie/core/znet/SteamUtils.h"
#include "zombie/network/CoopSlave.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerOptions.h"
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

    name = "changeoption"
)
    required = {"(\\w+)", "(.*)"}
)
    helpText = "UI_ServerOptionDesc_ChangeOptions"
)
    requiredRights = 32
)
class ChangeOptionCommand : public CommandBase {
    public:
    public
      ChangeOptionCommand(const std::string &string0,
                          const std::string &string1,
                          const std::string &string2,
                          UdpConnection udpConnection) {
        super(string0, string1, string2, udpConnection);
      }

      std::string Command() {
        std::string string0 = this.getCommandArg(0);
        std::string string1 = this.getCommandArg(1);
        std::string string2 =
            ServerOptions.instance.changeOption(string0, string1);
        if (string0 == "Password")) {
            GameServer.udpEngine.SetServerPassword(
                GameServer.udpEngine.hashServerPassword(
                    ServerOptions.instance.Password.getValue()));
          }

        if (string0 == "ClientCommandFilter")) {
            GameServer.initClientCommandFilter();
        }

        if (SteamUtils.isSteamModeEnabled()) {
          SteamGameServer.SetServerName(
              ServerOptions.instance.PublicName.getValue());
          SteamGameServer.SetKeyValue(
              "description",
              ServerOptions.instance.PublicDescription.getValue());
          SteamGameServer.SetKeyValue(
              "open", ServerOptions.instance.Open.getValue() ? "1" : "0");
          SteamGameServer.SetKeyValue(
              "public", ServerOptions.instance.Public.getValue() ? "1" : "0");
          SteamGameServer.SetKeyValue("mods",
                                      ServerOptions.instance.Mods.getValue());
          SteamGameServer.SetKeyValue(
              "pvp", ServerOptions.instance.PVP.getValue() ? "1" : "0");
          if (ServerOptions.instance.Public.getValue()) {
            SteamGameServer.SetGameTags(CoopSlave.instance != nullptr ? "hosted"
                                                                      : "");
          } else {
            SteamGameServer.SetGameTags(
                "hidden" + (CoopSlave.instance != nullptr ? ";hosted" : ""));
          }
        }

        LoggerManager.getLogger("admin").write(this.getExecutorUsername() +
                                               " changed option " + string0 +
                                               "=" + string1);
        return string2;
      }
    }
    } // namespace serverCommands
    } // namespace commands
    } // namespace zombie
