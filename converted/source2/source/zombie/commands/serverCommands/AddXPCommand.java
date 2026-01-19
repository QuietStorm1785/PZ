package zombie.commands.serverCommands;

import zombie.characters.IsoPlayer;
import zombie.characters.skills.PerkFactory;
import zombie.characters.skills.PerkFactory.Perks;
import zombie.commands.CommandArgs;
import zombie.commands.CommandBase;
import zombie.commands.CommandHelp;
import zombie.commands.CommandName;
import zombie.commands.RequiredRight;
import zombie.core.logger.LoggerManager;
import zombie.core.network.ByteBufferWriter;
import zombie.core.raknet.UdpConnection;
import zombie.network.GameServer;
import zombie.network.PacketTypes.PacketType;
import zombie.network.packets.AddXp;

@CommandName(name = "addxp")
@CommandArgs(required = {"(.+)", "(\\S+)"})
@CommandHelp(helpText = "UI_ServerOptionDesc_AddXp")
@RequiredRight(requiredRights = 60)
public class AddXPCommand extends CommandBase {
   public AddXPCommand(String var1, String var2, String var3, UdpConnection var4) {
      super(var1, var2, var3, var4);
   }

   protected String Command() {
      String var1 = this.getCommandArg(0);
      String var2 = this.getCommandArg(1);
      IsoPlayer var3 = GameServer.getPlayerByUserNameForCommand(var1);
      if (var3 == null) {
         return "No such user";
      } else {
         String var4 = var3.getDisplayName();
         Object var5 = null;
         int var6 = 0;
         String[] var7 = var2.split("=", 2);
         if (var7.length != 2) {
            return this.getHelp();
         } else {
            var5 = var7[0].trim();
            if (Perks.FromString((String)var5) == Perks.MAX) {
               String var15 = this.connection == null ? "\n" : " LINE ";
               StringBuilder var16 = new StringBuilder();

               for (int var17 = 0; var17 < PerkFactory.PerkList.size(); var17++) {
                  if (PerkFactory.PerkList.get(var17) != Perks.Passiv) {
                     var16.append(PerkFactory.PerkList.get(var17));
                     if (var17 < PerkFactory.PerkList.size()) {
                        var16.append(var15);
                     }
                  }
               }

               return "List of available perks :" + var15 + var16.toString();
            } else {
               try {
                  var6 = Integer.parseInt(var7[1]);
               } catch (NumberFormatException var12) {
                  return this.getHelp();
               }

               IsoPlayer var8 = GameServer.getPlayerByUserNameForCommand(var4);
               if (var8 != null) {
                  var4 = var8.getDisplayName();
                  UdpConnection var9 = GameServer.getConnectionFromPlayer(var8);
                  if (var9 != null) {
                     AddXp var10 = new AddXp();
                     var10.set(var3, Perks.FromString((String)var5), var6);
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
