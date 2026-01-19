package zombie.ai;

import java.util.ArrayDeque;
import java.util.ArrayList;
import zombie.GameTime;
import zombie.SandboxOptions;
import zombie.VirtualZombieManager;
import zombie.ai.states.PathFindState;
import zombie.ai.states.WalkTowardState;
import zombie.ai.states.ZombieIdleState;
import zombie.characters.IsoPlayer;
import zombie.characters.IsoZombie;
import zombie.characters.ZombieGroup;
import zombie.core.Core;
import zombie.core.Rand;
import zombie.iso.IsoCell;
import zombie.iso.IsoGridSquare;
import zombie.iso.IsoMovingObject;
import zombie.iso.IsoUtils;
import zombie.iso.IsoWorld;
import zombie.iso.Vector2;
import zombie.iso.Vector3;
import zombie.iso.IsoMetaGrid.Zone;
import zombie.network.GameClient;
import zombie.network.GameServer;

public final class ZombieGroupManager {
   public static final ZombieGroupManager instance = new ZombieGroupManager();
   private final ArrayList<ZombieGroup> groups = new ArrayList<>();
   private final ArrayDeque<ZombieGroup> freeGroups = new ArrayDeque<>();
   private final Vector2 tempVec2 = new Vector2();
   private final Vector3 tempVec3 = new Vector3();
   private float tickCount = 30.0F;

   public void preupdate() {
      this.tickCount = this.tickCount + GameTime.getInstance().getMultiplier() / 1.6F;
      if (this.tickCount >= 30.0F) {
         this.tickCount = 0.0F;
      }

      int var1 = SandboxOptions.instance.zombieConfig.RallyGroupSize.getValue();

      for (int var2 = 0; var2 < this.groups.size(); var2++) {
         ZombieGroup var3 = this.groups.get(var2);
         var3.update();
         if (var3.isEmpty()) {
            this.freeGroups.push(var3);
            this.groups.remove(var2--);
         }
      }
   }

   public void Reset() {
      this.freeGroups.addAll(this.groups);
      this.groups.clear();
   }

   public boolean shouldBeInGroup(IsoZombie var1) {
      if (var1 == null) {
         return false;
      } else if (SandboxOptions.instance.zombieConfig.RallyGroupSize.getValue() <= 1) {
         return false;
      } else if (!Core.getInstance().isZombieGroupSound()) {
         return false;
      } else if (var1.isUseless()) {
         return false;
      } else if (var1.isDead() || var1.isFakeDead()) {
         return false;
      } else if (var1.isSitAgainstWall()) {
         return false;
      } else if (var1.target != null) {
         return false;
      } else if (var1.getCurrentBuilding() != null) {
         return false;
      } else if (VirtualZombieManager.instance.isReused(var1)) {
         return false;
      } else {
         IsoGridSquare var2 = var1.getSquare();
         Zone var3 = var2 == null ? null : var2.getZone();
         return var3 == null || !"Forest".equals(var3.getType()) && !"DeepForest".equals(var3.getType());
      }
   }

   public void update(IsoZombie var1) {
      if (!GameClient.bClient || !var1.isRemoteZombie()) {
         if (!this.shouldBeInGroup(var1)) {
            if (var1.group != null) {
               var1.group.remove(var1);
            }
         } else if (this.tickCount == 0.0F) {
            if (var1.group == null) {
               ZombieGroup var2 = this.findNearestGroup(var1.getX(), var1.getY(), var1.getZ());
               if (var2 == null) {
                  var2 = this.freeGroups.isEmpty() ? new ZombieGroup() : this.freeGroups.pop().reset();
                  var2.add(var1);
                  this.groups.add(var2);
                  return;
               }

               var2.add(var1);
            }

            if (var1.getCurrentState() == ZombieIdleState.instance()) {
               if (var1 == var1.group.getLeader()) {
                  float var11 = (float)GameTime.getInstance().getWorldAgeHours();
                  var1.group.lastSpreadOutTime = Math.min(var1.group.lastSpreadOutTime, var11);
                  if (!(var1.group.lastSpreadOutTime + 0.083333336F > var11)) {
                     var1.group.lastSpreadOutTime = var11;
                     int var13 = SandboxOptions.instance.zombieConfig.RallyGroupSeparation.getValue();
                     Vector2 var14 = this.tempVec2.set(0.0F, 0.0F);

                     for (int var15 = 0; var15 < this.groups.size(); var15++) {
                        ZombieGroup var17 = this.groups.get(var15);
                        if (var17.getLeader() != null && var17 != var1.group && (int)var17.getLeader().getZ() == (int)var1.getZ()) {
                           float var7 = var17.getLeader().getX();
                           float var8 = var17.getLeader().getY();
                           float var9 = IsoUtils.DistanceToSquared(var1.x, var1.y, var7, var8);
                           if (!(var9 > var13 * var13)) {
                              var14.x = var14.x - var7 + var1.x;
                              var14.y = var14.y - var8 + var1.y;
                           }
                        }
                     }

                     int var16 = this.lineClearCollideCount(
                        var1,
                        var1.getCell(),
                        (int)(var1.x + var14.x),
                        (int)(var1.y + var14.y),
                        (int)var1.z,
                        (int)var1.x,
                        (int)var1.y,
                        (int)var1.z,
                        10,
                        this.tempVec3
                     );
                     if (var16 >= 1) {
                        if (GameClient.bClient || GameServer.bServer || !(IsoPlayer.getInstance().getHoursSurvived() < 2.0)) {
                           if (!(this.tempVec3.x < 0.0F)
                              && !(this.tempVec3.y < 0.0F)
                              && IsoWorld.instance.MetaGrid.isValidChunk((int)this.tempVec3.x / 10, (int)this.tempVec3.y / 10)) {
                              var1.pathToLocation((int)(this.tempVec3.x + 0.5F), (int)(this.tempVec3.y + 0.5F), (int)this.tempVec3.z);
                              if (var1.getCurrentState() == PathFindState.instance() || var1.getCurrentState() == WalkTowardState.instance()) {
                                 var1.setLastHeardSound(var1.getPathTargetX(), var1.getPathTargetY(), var1.getPathTargetZ());
                                 var1.AllowRepathDelay = 400.0F;
                              }
                           }
                        }
                     }
                  }
               } else {
                  float var10 = var1.group.getLeader().getX();
                  float var3 = var1.group.getLeader().getY();
                  int var4 = SandboxOptions.instance.zombieConfig.RallyGroupRadius.getValue();
                  if (!(IsoUtils.DistanceToSquared(var1.x, var1.y, var10, var3) < var4 * var4)) {
                     if (GameClient.bClient || GameServer.bServer || !(IsoPlayer.getInstance().getHoursSurvived() < 2.0) || Core.bDebug) {
                        int var5 = (int)(var10 + Rand.Next(-var4, var4));
                        int var6 = (int)(var3 + Rand.Next(-var4, var4));
                        if (var5 >= 0 && var6 >= 0 && IsoWorld.instance.MetaGrid.isValidChunk(var5 / 10, var6 / 10)) {
                           var1.pathToLocation(var5, var6, (int)var1.group.getLeader().getZ());
                           if (var1.getCurrentState() == PathFindState.instance() || var1.getCurrentState() == WalkTowardState.instance()) {
                              var1.setLastHeardSound(var1.getPathTargetX(), var1.getPathTargetY(), var1.getPathTargetZ());
                              var1.AllowRepathDelay = 400.0F;
                           }
                        }
                     }
                  }
               }
            }
         }
      }
   }

   public ZombieGroup findNearestGroup(float var1, float var2, float var3) {
      ZombieGroup var4 = null;
      float var5 = Float.MAX_VALUE;
      int var6 = SandboxOptions.instance.zombieConfig.RallyTravelDistance.getValue();

      for (int var7 = 0; var7 < this.groups.size(); var7++) {
         ZombieGroup var8 = this.groups.get(var7);
         if (var8.isEmpty()) {
            this.groups.remove(var7--);
         } else if ((int)var8.getLeader().getZ() == (int)var3 && var8.size() < SandboxOptions.instance.zombieConfig.RallyGroupSize.getValue()) {
            float var9 = IsoUtils.DistanceToSquared(var1, var2, var8.getLeader().getX(), var8.getLeader().getY());
            if (var9 < var6 * var6 && var9 < var5) {
               var5 = var9;
               var4 = var8;
            }
         }
      }

      return var4;
   }

   private int lineClearCollideCount(IsoMovingObject var1, IsoCell var2, int var3, int var4, int var5, int var6, int var7, int var8, int var9, Vector3 var10) {
      int var11 = 0;
      int var12 = var4 - var7;
      int var13 = var3 - var6;
      int var14 = var5 - var8;
      float var15 = 0.5F;
      float var16 = 0.5F;
      IsoGridSquare var20 = var2.getGridSquare(var6, var7, var8);
      var10.set(var6, var7, var8);
      if (Math.abs(var13) > Math.abs(var12) && Math.abs(var13) > Math.abs(var14)) {
         float var40 = (float)var12 / var13;
         float var45 = (float)var14 / var13;
         var15 += var7;
         var16 += var8;
         var13 = var13 < 0 ? -1 : 1;
         var40 *= var13;
         var45 *= var13;

         while (var6 != var3) {
            var6 += var13;
            var15 += var40;
            var16 += var45;
            IsoGridSquare var48 = var2.getGridSquare(var6, (int)var15, (int)var16);
            if (var48 != null && var20 != null) {
               boolean var50 = var48.testCollideAdjacent(var1, var20.getX() - var48.getX(), var20.getY() - var48.getY(), var20.getZ() - var48.getZ());
               if (var50) {
                  return var11;
               }
            }

            var20 = var48;
            int var35 = (int)var15;
            int var36 = (int)var16;
            var10.set(var6, var35, var36);
            if (++var11 >= var9) {
               return var11;
            }
         }
      } else if (Math.abs(var12) >= Math.abs(var13) && Math.abs(var12) > Math.abs(var14)) {
         float var38 = (float)var13 / var12;
         float var43 = (float)var14 / var12;
         var15 += var6;
         var16 += var8;
         var12 = var12 < 0 ? -1 : 1;
         var38 *= var12;
         var43 *= var12;

         while (var7 != var4) {
            var7 += var12;
            var15 += var38;
            var16 += var43;
            IsoGridSquare var47 = var2.getGridSquare((int)var15, var7, (int)var16);
            if (var47 != null && var20 != null) {
               boolean var49 = var47.testCollideAdjacent(var1, var20.getX() - var47.getX(), var20.getY() - var47.getY(), var20.getZ() - var47.getZ());
               if (var49) {
                  return var11;
               }
            }

            var20 = var47;
            int var34 = (int)var15;
            int var19 = (int)var16;
            var10.set(var34, var7, var19);
            if (++var11 >= var9) {
               return var11;
            }
         }
      } else {
         float var21 = (float)var13 / var14;
         float var22 = (float)var12 / var14;
         var15 += var6;
         var16 += var7;
         var14 = var14 < 0 ? -1 : 1;
         var21 *= var14;
         var22 *= var14;

         while (var8 != var5) {
            var8 += var14;
            var15 += var21;
            var16 += var22;
            IsoGridSquare var23 = var2.getGridSquare((int)var15, (int)var16, var8);
            if (var23 != null && var20 != null) {
               boolean var24 = var23.testCollideAdjacent(var1, var20.getX() - var23.getX(), var20.getY() - var23.getY(), var20.getZ() - var23.getZ());
               if (var24) {
                  return var11;
               }
            }

            var20 = var23;
            int var17 = (int)var15;
            int var18 = (int)var16;
            var10.set(var17, var18, var8);
            if (++var11 >= var9) {
               return var11;
            }
         }
      }

      return var11;
   }
}
