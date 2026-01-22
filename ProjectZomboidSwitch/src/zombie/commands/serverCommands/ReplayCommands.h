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
#include "zombie/network/GameServer.h"
#include "zombie/network/ReplayManager.h"
#include "zombie/network/ReplayManager/State.h"

namespace zombie {
namespace commands {
namespace serverCommands {


class ReplayCommands : public CommandBase {
public:
    static const std::string RecordPlay = "(-record|-play|-stop)";
    static const std::string Stop = "(-stop)";

    public ReplayCommands(const std::string& var1, const std::string& var2, const std::string& var3, UdpConnection var4) {
      super(var1, var2, var3, var4);
   }

    std::string Command() {
    std::string var1 = this.getCommandArg(0);
    std::string var2 = this.getCommandArg(1);
    std::string var3 = this.getCommandArg(2);
    bool var4 = false;
    bool var5 = false;
      if ("-play" == var2)) {
         var5 = true;
      } else if ("-stop" == var2)) {
         var4 = true;
      }

    IsoPlayer var6 = GameServer.getPlayerByUserNameForCommand(var1);
      if (var6 != nullptr) {
         if (var6.replay == nullptr) {
            var6.replay = std::make_shared<ReplayManager>(var6);
         }

         if (var4) {
    State var7 = var6.replay.getState();
            if (var7 == State.Stop) {
               return "Nothing to stop.";
            } else if (var7 == State.Recording) {
               var6.replay.stopRecordReplay();
               LoggerManager.getLogger("admin").write(this.getExecutorUsername() + " end record replay for " + var1);
               return "Recording replay is stopped  for " + var1 + ".";
            } else {
               var6.replay.stopPlayReplay();
               LoggerManager.getLogger("admin").write(this.getExecutorUsername() + " end play replay for " + var1);
               return "Playing replay is stopped  for " + var1 + ".";
            }
         } else if (var5) {
            if (!var6.replay.startPlayReplay(var6, var3, this.connection)) {
               return "Can't play replay";
            } else {
               LoggerManager.getLogger("admin").write(this.getExecutorUsername() + " enabled play replay for " + var1);
               return "Replay is playing for " + var1 + " to file \"" + var3 + "\" now.";
            }
         } else if (!var6.replay.startRecordReplay(var6, var3)) {
            return "Can't record replay";
         } else {
            LoggerManager.getLogger("admin").write(this.getExecutorUsername() + " enabled record replay for " + var1);
            return "Replay is recording for " + var1 + " to file \"" + var3 + "\" now.";
         }
      } else {
         return "User " + var1 + " not found.";
      }
   }
}
} // namespace serverCommands
} // namespace commands
} // namespace zombie
