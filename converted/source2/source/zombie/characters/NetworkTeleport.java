package zombie.characters;

import zombie.Lua.LuaManager.GlobalObject;
import zombie.characters.NetworkTeleport.1;
import zombie.characters.NetworkTeleport.NetworkTeleportDebug;
import zombie.characters.NetworkTeleport.Type;
import zombie.core.Core;
import zombie.debug.DebugOptions;
import zombie.iso.IsoDirections;
import zombie.iso.IsoGridSquare;
import zombie.iso.IsoWorld;
import zombie.network.MPStatisticClient;
import zombie.network.packets.PlayerPacket;

public class NetworkTeleport {
   public static boolean enable = true;
   public static boolean enableInstantTeleport = true;
   private Type teleportType = Type.none;
   private IsoGameCharacter character = null;
   private boolean setNewPos = false;
   private float nx = 0.0F;
   private float ny = 0.0F;
   private byte nz = 0;
   public float ndirection;
   private float tx = 0.0F;
   private float ty = 0.0F;
   private byte tz = 0;
   private long startTime;
   private long duration;

   public NetworkTeleport(IsoGameCharacter var1, Type var2, float var3, float var4, byte var5, float var6) {
      this.character = var1;
      this.setNewPos = false;
      this.nx = var3;
      this.ny = var4;
      this.nz = var5;
      this.teleportType = var2;
      this.startTime = System.currentTimeMillis();
      this.duration = (long)(1000.0 * var6);
      var1.setTeleport(this);
      if (Core.bDebug && var1.getNetworkCharacterAI() != null && DebugOptions.instance.MultiplayerShowTeleport.getValue()) {
         var1.getNetworkCharacterAI()
            .setTeleportDebug(
               new NetworkTeleportDebug(var1.getOnlineID(), var1.x, var1.y, var1.z, var3, var4, var5, var1.getNetworkCharacterAI().predictionType)
            );
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
   public void process(int var1) {
      if (!enable) {
         this.character.setX(this.nx);
         this.character.setY(this.ny);
         this.character.setZ(this.nz);
         this.character.ensureOnTile();
         this.character.setTeleport(null);
         this.character = null;
      } else {
         boolean var2 = this.character.getCurrentSquare().isCanSee(var1);
         float var3 = Math.min(1.0F, (float)(System.currentTimeMillis() - this.startTime) / (float)this.duration);
         switch (1.$SwitchMap$zombie$characters$NetworkTeleport$Type[this.teleportType.ordinal()]) {
            case 1:
               if (var3 < 0.99F) {
                  this.character.setAlpha(var1, Math.min(this.character.getAlpha(var1), 1.0F - var3));
               } else {
                  this.stop(var1);
               }
               break;
            case 2:
               if (var3 < 0.5F) {
                  if (this.character.isoPlayer == null || this.character.isoPlayer != null && this.character.isoPlayer.spottedByPlayer) {
                     this.character.setAlpha(var1, Math.min(this.character.getAlpha(var1), 1.0F - var3 * 2.0F));
                  }
               } else if (var3 < 0.99F) {
                  if (!this.setNewPos) {
                     this.setNewPos = true;
                     this.character.setX(this.nx);
                     this.character.setY(this.ny);
                     this.character.setZ(this.nz);
                     this.character.ensureOnTile();
                     this.character.getNetworkCharacterAI().resetSpeedLimiter();
                  }

                  if (this.character.isoPlayer == null || this.character.isoPlayer != null && this.character.isoPlayer.spottedByPlayer) {
                     this.character.setAlpha(var1, Math.min(this.character.getTargetAlpha(var1), (var3 - 0.5F) * 2.0F));
                  }
               } else {
                  this.stop(var1);
               }
               break;
            case 3:
               if (var3 < 0.99F) {
                  this.character.setAlpha(var1, Math.min(this.character.getTargetAlpha(var1), var3));
               } else {
                  this.stop(var1);
               }
         }
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
   public void stop(int var1) {
      this.character.setTeleport(null);
      switch (1.$SwitchMap$zombie$characters$NetworkTeleport$Type[this.teleportType.ordinal()]) {
         case 1:
            this.character.setAlpha(var1, Math.min(this.character.getAlpha(var1), 0.0F));
         default:
            this.character = null;
      }
   }

   public static boolean teleport(IsoGameCharacter var0, Type var1, float var2, float var3, byte var4, float var5) {
      if (!enable) {
         return false;
      } else {
         if (var0.getCurrentSquare() != null && enableInstantTeleport) {
            boolean var6 = false;

            for (int var7 = 0; var7 < 4; var7++) {
               if (var0.getCurrentSquare().isCanSee(var7)) {
                  var6 = true;
                  break;
               }
            }

            IsoGridSquare var9 = GlobalObject.getCell().getGridSquare((int)var2, (int)var3, var4);
            if (var9 != null) {
               for (int var8 = 0; var8 < 4; var8++) {
                  if (var9.isCanSee(var8)) {
                     var6 = true;
                     break;
                  }
               }
            }

            if (!var6) {
               var0.setX(var2);
               var0.setY(var3);
               var0.setZ(var4);
               var0.ensureOnTile();
               return false;
            }
         }

         if (!var0.isTeleporting()) {
            if (var0 instanceof IsoZombie) {
               MPStatisticClient.getInstance().incrementZombiesTeleports();
            } else {
               MPStatisticClient.getInstance().incrementRemotePlayersTeleports();
            }

            new NetworkTeleport(var0, var1, var2, var3, var4, var5);
            return true;
         } else {
            return false;
         }
      }
   }

   public static boolean teleport(IsoGameCharacter var0, PlayerPacket var1, float var2) {
      if (!enable) {
         return false;
      } else {
         if (GlobalObject.getCell().getGridSquare((int)var1.x, (int)var1.y, var1.z) == null) {
            var0.setX(var1.x);
            var0.setY(var1.y);
            var0.setZ(var1.z);
            var0.realx = var1.realx;
            var0.realy = var1.realy;
            var0.realz = var1.realz;
            var0.realdir = IsoDirections.fromIndex(var1.realdir);
            var0.ensureOnTile();
         }

         if (var0.getCurrentSquare() != null && enableInstantTeleport) {
            boolean var3 = false;

            for (int var4 = 0; var4 < 4; var4++) {
               if (var0.getCurrentSquare().isCanSee(var4)) {
                  var3 = true;
                  break;
               }
            }

            IsoGridSquare var8 = GlobalObject.getCell().getGridSquare((int)var1.x, (int)var1.y, var1.z);
            if (var8 != null) {
               for (int var5 = 0; var5 < 4; var5++) {
                  if (var8.isCanSee(var5)) {
                     var3 = true;
                     break;
                  }
               }
            }

            if (!var3) {
               var0.setX(var1.x);
               var0.setY(var1.y);
               var0.setZ(var1.z);
               var0.ensureOnTile();
               return false;
            }
         }

         if (!var0.isTeleporting()) {
            if (var0 instanceof IsoZombie) {
               MPStatisticClient.getInstance().incrementZombiesTeleports();
            } else {
               MPStatisticClient.getInstance().incrementRemotePlayersTeleports();
            }

            IsoGridSquare var7 = IsoWorld.instance.CurrentCell.getGridSquare(var0.x, var0.y, var0.z);
            if (var7 == null) {
               IsoGridSquare var10 = IsoWorld.instance.CurrentCell.getGridSquare(var1.realx, var1.realy, var1.realz);
               var0.setAlphaAndTarget(0.0F);
               var0.setX(var1.realx);
               var0.setY(var1.realy);
               var0.setZ(var1.realz);
               var0.ensureOnTile();
               float var12 = 0.5F;
               NetworkTeleport var6 = new NetworkTeleport(
                  var0,
                  Type.materialization,
                  var12 * var1.x + (1.0F - var12) * var1.realx,
                  var12 * var1.y + (1.0F - var12) * var1.realy,
                  (byte)(var12 * var1.z + (1.0F - var12) * var1.realz),
                  var2
               );
               var6.ndirection = var1.direction;
               var6.tx = var1.x;
               var6.ty = var1.y;
               var6.tz = var1.z;
               return true;
            } else {
               float var9 = 0.5F;
               NetworkTeleport var11 = new NetworkTeleport(
                  var0,
                  Type.teleportation,
                  var9 * var1.x + (1.0F - var9) * var1.realx,
                  var9 * var1.y + (1.0F - var9) * var1.realy,
                  (byte)(var9 * var1.z + (1.0F - var9) * var1.realz),
                  var2
               );
               var11.ndirection = var1.direction;
               var11.tx = var1.x;
               var11.ty = var1.y;
               var11.tz = var1.z;
               return true;
            }
         } else {
            return false;
         }
      }
   }

   public static void update(IsoGameCharacter var0, PlayerPacket var1) {
      if (var0.isTeleporting()) {
         NetworkTeleport var2 = var0.getTeleport();
         if (var2.teleportType == Type.teleportation) {
            float var3 = Math.min(1.0F, (float)(System.currentTimeMillis() - var2.startTime) / (float)var2.duration);
            if (var3 < 0.5F) {
               float var4 = 0.5F;
               var2.nx = var4 * var1.x + (1.0F - var4) * var1.realx;
               var2.ny = var4 * var1.y + (1.0F - var4) * var1.realy;
               var2.nz = (byte)(var4 * var1.z + (1.0F - var4) * var1.realz);
            }

            var2.ndirection = var1.direction;
            var2.tx = var1.x;
            var2.ty = var1.y;
            var2.tz = var1.z;
         }
      }
   }
}
