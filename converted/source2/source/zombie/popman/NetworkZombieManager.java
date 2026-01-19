package zombie.popman;

import java.nio.ByteBuffer;
import java.util.LinkedList;
import zombie.SystemDisabler;
import zombie.ai.State;
import zombie.ai.states.ZombieEatBodyState;
import zombie.ai.states.ZombieIdleState;
import zombie.ai.states.ZombieSittingState;
import zombie.ai.states.ZombieTurnAlerted;
import zombie.characters.IsoPlayer;
import zombie.characters.IsoZombie;
import zombie.core.Core;
import zombie.core.raknet.UdpConnection;
import zombie.debug.DebugLog;
import zombie.debug.DebugType;
import zombie.iso.IsoChunkMap;
import zombie.iso.IsoGridSquare;
import zombie.iso.IsoMovingObject;
import zombie.iso.IsoUtils;
import zombie.iso.IsoWorld;
import zombie.network.GameServer;
import zombie.popman.NetworkZombieList.NetworkZombie;
import zombie.util.Type;

public class NetworkZombieManager {
   private static final NetworkZombieManager instance = new NetworkZombieManager();
   private final NetworkZombieList owns = new NetworkZombieList();
   private static final float NospottedDistanceSquared = 16.0F;

   public static NetworkZombieManager getInstance() {
      return instance;
   }

   public int getAuthorizedZombieCount(UdpConnection var1) {
      return (int)IsoWorld.instance.CurrentCell.getZombieList().stream().filter(var1x -> var1x.authOwner == var1).count();
   }

   public int getUnauthorizedZombieCount() {
      return (int)IsoWorld.instance.CurrentCell.getZombieList().stream().filter(var0 -> var0.authOwner == null).count();
   }

   public static boolean canSpotted(IsoZombie var0) {
      if (var0.isRemoteZombie()) {
         return false;
      } else if (var0.target != null && IsoUtils.DistanceToSquared(var0.x, var0.y, var0.target.x, var0.target.y) < 16.0F) {
         return false;
      } else {
         State var1 = var0.getCurrentState();
         return var1 == null
            || var1 == ZombieIdleState.instance()
            || var1 == ZombieEatBodyState.instance()
            || var1 == ZombieSittingState.instance()
            || var1 == ZombieTurnAlerted.instance();
      }
   }

   public void updateAuth(IsoZombie var1) {
      if (GameServer.bServer) {
         if (System.currentTimeMillis() - var1.lastChangeOwner >= 2000L || var1.authOwner == null) {
            if (SystemDisabler.zombiesSwitchOwnershipEachUpdate && GameServer.getPlayerCount() > 1) {
               if (var1.authOwner == null) {
                  for (int var13 = 0; var13 < GameServer.udpEngine.connections.size(); var13++) {
                     UdpConnection var16 = (UdpConnection)GameServer.udpEngine.connections.get(var13);
                     if (var16 != null) {
                        this.moveZombie(var1, var16, null);
                        break;
                     }
                  }
               } else {
                  int var14 = GameServer.udpEngine.connections.indexOf(var1.authOwner) + 1;

                  for (int var17 = 0; var17 < GameServer.udpEngine.connections.size(); var17++) {
                     UdpConnection var18 = (UdpConnection)GameServer.udpEngine.connections.get((var17 + var14) % GameServer.udpEngine.connections.size());
                     if (var18 != null) {
                        this.moveZombie(var1, var18, null);
                        break;
                     }
                  }
               }
            } else {
               if (var1.target instanceof IsoPlayer) {
                  UdpConnection var2 = GameServer.getConnectionFromPlayer((IsoPlayer)var1.target);
                  if (var2 != null && var2.isFullyConnected()) {
                     float var3 = ((IsoPlayer)var1.target).getRelevantAndDistance(var1.x, var1.y, var2.ReleventRange - 2);
                     if (!Float.isInfinite(var3)) {
                        this.moveZombie(var1, var2, (IsoPlayer)var1.target);
                        if (Core.bDebug) {
                           DebugLog.log(
                              DebugType.Ownership,
                              String.format("Zombie (%d) owner (\"%s\"): zombie has target", var1.getOnlineID(), ((IsoPlayer)var1.target).getUsername())
                           );
                        }

                        return;
                     }
                  }
               }

               UdpConnection var12 = var1.authOwner;
               IsoPlayer var15 = var1.authOwnerPlayer;
               float var4 = Float.POSITIVE_INFINITY;
               if (var12 != null) {
                  var4 = var12.getRelevantAndDistance(var1.x, var1.y, var1.z);
               }

               for (int var5 = 0; var5 < GameServer.udpEngine.connections.size(); var5++) {
                  UdpConnection var6 = (UdpConnection)GameServer.udpEngine.connections.get(var5);
                  if (var6 != var12) {
                     for (IsoPlayer var10 : var6.players) {
                        if (var10 != null && var10.isAlive()) {
                           float var11 = var10.getRelevantAndDistance(var1.x, var1.y, var6.ReleventRange - 2);
                           if (!Float.isInfinite(var11) && (var12 == null || var4 > var11 * 1.618034F)) {
                              var12 = var6;
                              var4 = var11;
                              var15 = var10;
                           }
                        }
                     }
                  }
               }

               if (Core.bDebug && var15 != null && var15 != var1.authOwnerPlayer) {
                  DebugLog.log(DebugType.Ownership, String.format("Zombie (%d) owner (\"%s\"): zombie is closer", var1.getOnlineID(), var15.getUsername()));
               }

               if (var12 == null && var1.isReanimatedPlayer()) {
                  for (int var19 = 0; var19 < GameServer.udpEngine.connections.size(); var19++) {
                     UdpConnection var20 = (UdpConnection)GameServer.udpEngine.connections.get(var19);
                     if (var20 != var12) {
                        for (IsoPlayer var24 : var20.players) {
                           if (var24 != null && var24.isDead() && var24.ReanimatedCorpse == var1) {
                              var12 = var20;
                              var15 = var24;
                              if (Core.bDebug) {
                                 DebugLog.log(
                                    DebugType.Ownership,
                                    String.format("Zombie (%d) owner (\"%s\"): zombie is reanimated", var1.getOnlineID(), var24.getUsername())
                                 );
                              }
                           }
                        }
                     }
                  }
               }

               if (var12 != null && !var12.RelevantTo(var1.x, var1.y, (var12.ReleventRange - 2) * 10)) {
                  var12 = null;
               }

               this.moveZombie(var1, var12, var15);
            }
         }
      }
   }

   public void moveZombie(IsoZombie var1, UdpConnection var2, IsoPlayer var3) {
      if (var1.isDead()) {
         if (var1.authOwner == null && var1.authOwnerPlayer == null) {
            var1.becomeCorpse();
         } else {
            synchronized (this.owns.lock) {
               var1.authOwner = null;
               var1.authOwnerPlayer = null;
               var1.getNetworkCharacterAI().resetSpeedLimiter();
            }

            NetworkZombiePacker.getInstance().setExtraUpdate();
         }

         if (Core.bDebug) {
            DebugLog.log(
               DebugType.Ownership,
               String.format("Zombie (%d) owner (\"%s\" / null): zombie is dead", var1.getOnlineID(), var3 == null ? "" : var3.getUsername())
            );
         }
      } else {
         if (var3 != null
            && var3.getVehicle() != null
            && var3.getVehicle().getSpeed2D() > 2.0F
            && var3.getVehicle().getDriver() != var3
            && var3.getVehicle().getDriver() instanceof IsoPlayer) {
            var3 = (IsoPlayer)var3.getVehicle().getDriver();
            var2 = GameServer.getConnectionFromPlayer(var3);
            if (Core.bDebug) {
               DebugLog.log(
                  DebugType.Ownership,
                  String.format("Zombie (%d) owner (\"%s\"): zombie owner is driver", var1.getOnlineID(), var3 == null ? "" : var3.getUsername())
               );
            }
         }

         if (var1.authOwner != var2) {
            synchronized (this.owns.lock) {
               if (var1.authOwner != null) {
                  NetworkZombie var5 = this.owns.getNetworkZombie(var1.authOwner);
                  if (var5 != null && !var5.zombies.remove(var1)) {
                     DebugLog.log("moveZombie: There are no zombies in nz.zombies.");
                  }
               }

               if (var2 != null) {
                  NetworkZombie var10 = this.owns.getNetworkZombie(var2);
                  if (var10 != null) {
                     var10.zombies.add(var1);
                     var1.authOwner = var2;
                     var1.authOwnerPlayer = var3;
                     var1.getNetworkCharacterAI().resetSpeedLimiter();
                     var2.timerSendZombie.reset(0L);
                  }
               } else {
                  var1.authOwner = null;
                  var1.authOwnerPlayer = null;
                  var1.getNetworkCharacterAI().resetSpeedLimiter();
               }
            }

            var1.lastChangeOwner = System.currentTimeMillis();
            NetworkZombiePacker.getInstance().setExtraUpdate();
         }
      }
   }

   public void getZombieAuth(UdpConnection var1, ByteBuffer var2) {
      NetworkZombie var3 = this.owns.getNetworkZombie(var1);
      int var4 = var3.zombies.size();
      int var5 = 0;
      int var6 = var2.position();
      var2.putShort((short)var4);
      synchronized (this.owns.lock) {
         var3.zombies.removeIf(var0 -> var0.OnlineID == -1);

         for (IsoZombie var9 : var3.zombies) {
            if (var9.OnlineID != -1) {
               var2.putShort(var9.OnlineID);
               var5++;
            } else {
               DebugLog.General.error("getZombieAuth: zombie.OnlineID == -1");
            }
         }
      }

      if (var5 < var4) {
         int var12 = var2.position();
         var2.position(var6);
         var2.putShort((short)var5);
         var2.position(var12);
      }
   }

   public LinkedList<IsoZombie> getZombieList(UdpConnection var1) {
      NetworkZombie var2 = this.owns.getNetworkZombie(var1);
      return var2.zombies;
   }

   public void clearTargetAuth(UdpConnection var1, IsoPlayer var2) {
      if (Core.bDebug) {
         DebugLog.log(DebugType.Multiplayer, "Clear zombies target and auth for player id=" + var2.getOnlineID());
      }

      if (GameServer.bServer) {
         for (IsoZombie var4 : IsoWorld.instance.CurrentCell.getZombieList()) {
            if (var4.target == var2) {
               var4.setTarget(null);
            }

            if (var4.authOwner == var1) {
               var4.authOwner = null;
               var4.authOwnerPlayer = null;
               var4.getNetworkCharacterAI().resetSpeedLimiter();
               getInstance().updateAuth(var4);
            }
         }
      }
   }

   public static void removeZombies(UdpConnection var0) {
      int var1 = (IsoChunkMap.ChunkGridWidth / 2 + 2) * 10;

      for (IsoPlayer var5 : var0.players) {
         if (var5 != null) {
            int var6 = (int)var5.getX();
            int var7 = (int)var5.getY();

            for (int var8 = 0; var8 < 8; var8++) {
               for (int var9 = var7 - var1; var9 <= var7 + var1; var9++) {
                  for (int var10 = var6 - var1; var10 <= var6 + var1; var10++) {
                     IsoGridSquare var11 = IsoWorld.instance.CurrentCell.getGridSquare(var10, var9, var8);
                     if (var11 != null && !var11.getMovingObjects().isEmpty()) {
                        for (int var12 = var11.getMovingObjects().size() - 1; var12 >= 0; var12--) {
                           IsoZombie var13 = (IsoZombie)Type.tryCastTo((IsoMovingObject)var11.getMovingObjects().get(var12), IsoZombie.class);
                           if (var13 != null) {
                              NetworkZombiePacker.getInstance().deleteZombie(var13);
                              var13.removeFromWorld();
                              var13.removeFromSquare();
                           }
                        }
                     }
                  }
               }
            }
         }
      }
   }

   public void recheck(UdpConnection var1) {
      synchronized (this.owns.lock) {
         NetworkZombie var3 = this.owns.getNetworkZombie(var1);
         if (var3 != null) {
            var3.zombies.removeIf(var1x -> var1x.authOwner != var1);
         }
      }
   }
}
