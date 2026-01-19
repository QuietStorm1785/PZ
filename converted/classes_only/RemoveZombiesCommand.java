package zombie.commands.serverCommands;

import zombie.characters.IsoZombie;
import zombie.commands.CommandArgs;
import zombie.commands.CommandBase;
import zombie.commands.CommandHelp;
import zombie.commands.CommandName;
import zombie.commands.RequiredRight;
import zombie.core.logger.LoggerManager;
import zombie.core.math.PZMath;
import zombie.core.raknet.UdpConnection;
import zombie.iso.IsoGridSquare;
import zombie.iso.IsoMovingObject;
import zombie.iso.IsoWorld;
import zombie.iso.objects.IsoDeadBody;
import zombie.network.GameServer;
import zombie.popman.NetworkZombiePacker;
import zombie.util.StringUtils;
import zombie.util.Type;

@CommandName(name = "removezombies")
@CommandArgs(varArgs = true)
@CommandHelp(helpText = "UI_ServerOptionDesc_RemoveZombies")
@RequiredRight(requiredRights = 56)
public class RemoveZombiesCommand extends CommandBase {
   public RemoveZombiesCommand(String var1, String var2, String var3, UdpConnection var4) {
      super(var1, var2, var3, var4);
   }

   protected String Command() {
      int var1 = -1;
      int var2 = -1;
      int var3 = -1;
      int var4 = -1;
      boolean var5 = false;
      boolean var6 = false;
      boolean var7 = false;

      for (byte var8 = 0; var8 < this.getCommandArgsCount() - 1; var8 += 2) {
         String var9 = this.getCommandArg(Integer.valueOf(var8));
         String var10 = this.getCommandArg(var8 + 1);
         switch (var9) {
            case "-radius":
               var1 = PZMath.tryParseInt(var10, -1);
               break;
            case "-reanimated":
               var5 = StringUtils.tryParseBoolean(var10);
               break;
            case "-x":
               var2 = PZMath.tryParseInt(var10, -1);
               break;
            case "-y":
               var3 = PZMath.tryParseInt(var10, -1);
               break;
            case "-z":
               var4 = PZMath.tryParseInt(var10, -1);
               break;
            case "-remove":
               var6 = StringUtils.tryParseBoolean(var10);
               break;
            case "-clear":
               var7 = StringUtils.tryParseBoolean(var10);
               break;
            default:
               return this.getHelp();
         }
      }

      if (var6) {
         GameServer.removeZombiesConnection = this.connection;
         return "Zombies removed.";
      } else if (var4 >= 0 && var4 < 8) {
         for (int var13 = var3 - var1; var13 <= var3 + var1; var13++) {
            for (int var14 = var2 - var1; var14 <= var2 + var1; var14++) {
               IsoGridSquare var15 = IsoWorld.instance.CurrentCell.getGridSquare(var14, var13, var4);
               if (var15 != null) {
                  if (var7) {
                     if (!var15.getStaticMovingObjects().isEmpty()) {
                        for (int var16 = var15.getStaticMovingObjects().size() - 1; var16 >= 0; var16--) {
                           IsoDeadBody var18 = (IsoDeadBody)Type.tryCastTo((IsoMovingObject)var15.getStaticMovingObjects().get(var16), IsoDeadBody.class);
                           if (var18 != null) {
                              GameServer.sendRemoveCorpseFromMap(var18);
                              var18.removeFromWorld();
                              var18.removeFromSquare();
                           }
                        }
                     }
                  } else if (!var15.getMovingObjects().isEmpty()) {
                     for (int var11 = var15.getMovingObjects().size() - 1; var11 >= 0; var11--) {
                        IsoZombie var17 = (IsoZombie)Type.tryCastTo((IsoMovingObject)var15.getMovingObjects().get(var11), IsoZombie.class);
                        if (var17 != null && (var5 || !var17.isReanimatedPlayer())) {
                           NetworkZombiePacker.getInstance().deleteZombie(var17);
                           var17.removeFromWorld();
                           var17.removeFromSquare();
                        }
                     }
                  }
               }
            }
         }

         LoggerManager.getLogger("admin").write(this.getExecutorUsername() + " removed zombies near " + var2 + "," + var3, "IMPORTANT");
         return "Zombies removed.";
      } else {
         return "invalid z";
      }
   }
}
