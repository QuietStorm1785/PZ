package zombie.commands.serverCommands;

import zombie.characters.IsoPlayer;
import zombie.commands.AltCommandArgs;
import zombie.commands.CommandArgs;
import zombie.commands.CommandBase;
import zombie.commands.CommandHelp;
import zombie.commands.CommandName;
import zombie.commands.RequiredRight;
import zombie.core.logger.LoggerManager;
import zombie.core.raknet.UdpConnection;
import zombie.network.GameServer;
import zombie.network.ReplayManager;
import zombie.network.ReplayManager.State;

@CommandName(name = "replay")
@AltCommandArgs({@CommandArgs(required = {"(.+)", "(-record|-play|-stop)", "(.+)"}), @CommandArgs(required = {"(.+)", "(-stop)"})})
@CommandHelp(helpText = "UI_ServerOptionDesc_Replay")
@RequiredRight(requiredRights = 32)
public class ReplayCommands extends CommandBase {
   public static final String RecordPlay = "(-record|-play|-stop)";
   public static final String Stop = "(-stop)";

   public ReplayCommands(String var1, String var2, String var3, UdpConnection var4) {
      super(var1, var2, var3, var4);
   }

   protected String Command() {
      String var1 = this.getCommandArg(0);
      String var2 = this.getCommandArg(1);
      String var3 = this.getCommandArg(2);
      boolean var4 = false;
      boolean var5 = false;
      if ("-play".equals(var2)) {
         var5 = true;
      } else if ("-stop".equals(var2)) {
         var4 = true;
      }

      IsoPlayer var6 = GameServer.getPlayerByUserNameForCommand(var1);
      if (var6 != null) {
         if (var6.replay == null) {
            var6.replay = new ReplayManager(var6);
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
