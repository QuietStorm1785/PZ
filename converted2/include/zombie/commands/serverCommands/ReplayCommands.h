#pragma once
#include "zombie/characters/IsoPlayer.h"
#include "zombie/commands/AltCommandArgs.h"
#include "zombie/commands/CommandArgs.h"
#include "zombie/commands/CommandBase.h"
#include "zombie/commands/CommandHelp.h"
#include "zombie/commands/CommandName.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ReplayManager.h"
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

    name = "replay"
)
        required = {"(.+)", "(-record|-play|-stop)", "(.+)"}
    ), @CommandArgs(
        required = {"(.+)", "(-stop)"}
    )
    })
    helpText = "UI_ServerOptionDesc_Replay"
)
    requiredRights = 32
)
class ReplayCommands : public CommandBase {
    public:
      static const std::string RecordPlay = "(-record|-play|-stop)";
      static const std::string Stop = "(-stop)";

    public
      ReplayCommands(const std::string &string0, const std::string &string1,
                     const std::string &string2, UdpConnection udpConnection) {
        super(string0, string1, string2, udpConnection);
      }

      std::string Command() {
        std::string string0 = this.getCommandArg(0);
        std::string string1 = this.getCommandArg(1);
        std::string string2 = this.getCommandArg(2);
        bool boolean0 = false;
        bool boolean1 = false;
        if ("-play" == string1)) {
            boolean1 = true;
        }
        else if ("-stop" == string1)) {
            boolean0 = true;
        }

        IsoPlayer player = GameServer.getPlayerByUserNameForCommand(string0);
        if (player != nullptr) {
          if (player.replay == nullptr) {
            player.replay = new ReplayManager(player);
          }

          if (boolean0) {
            ReplayManager.State state = player.replay.getState();
            if (state == ReplayManager.State.Stop) {
              return "Nothing to stop.";
            } else if (state == ReplayManager.State.Recording) {
              player.replay.stopRecordReplay();
              LoggerManager.getLogger("admin").write(
                  this.getExecutorUsername() + " end record replay for " +
                  string0);
              return "Recording replay is stopped  for " + string0 + ".";
            } else {
              player.replay.stopPlayReplay();
              LoggerManager.getLogger("admin").write(
                  this.getExecutorUsername() + " end play replay for " +
                  string0);
              return "Playing replay is stopped  for " + string0 + ".";
            }
          } else if (boolean1) {
            if (!player.replay.startPlayReplay(player, string2,
                                               this.connection)) {
              return "Can't play replay";
            } else {
              LoggerManager.getLogger("admin").write(
                  this.getExecutorUsername() + " enabled play replay for " +
                  string0);
              return "Replay is playing for " + string0 + " to file \"" +
                     string2 + "\" now.";
            }
          } else if (!player.replay.startRecordReplay(player, string2)) {
            return "Can't record replay";
          } else {
            LoggerManager.getLogger("admin").write(
                this.getExecutorUsername() + " enabled record replay for " +
                string0);
            return "Replay is recording for " + string0 + " to file \"" +
                   string2 + "\" now.";
          }
        } else {
          return "User " + string0 + " not found.";
        }
      }
    }
    } // namespace serverCommands
    } // namespace commands
    } // namespace zombie
