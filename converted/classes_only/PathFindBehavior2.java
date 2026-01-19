package zombie.vehicles;

import gnu.trove.list.array.TFloatArrayList;
import java.util.ArrayList;
import org.joml.Vector2f;
import org.joml.Vector3f;
import se.krka.kahlua.vm.KahluaTable;
import zombie.SandboxOptions;
import zombie.ai.State;
import zombie.ai.WalkingOnTheSpot;
import zombie.ai.astar.Mover;
import zombie.ai.astar.AStarPathFinder.PathFindProgress;
import zombie.ai.states.ClimbOverFenceState;
import zombie.ai.states.ClimbThroughWindowState;
import zombie.ai.states.CollideWithWallState;
import zombie.ai.states.WalkTowardState;
import zombie.ai.states.ZombieGetDownState;
import zombie.characters.IsoGameCharacter;
import zombie.characters.IsoPlayer;
import zombie.characters.IsoZombie;
import zombie.core.Core;
import zombie.debug.DebugOptions;
import zombie.debug.LineDrawer;
import zombie.iso.IsoCell;
import zombie.iso.IsoDirections;
import zombie.iso.IsoGridSquare;
import zombie.iso.IsoMovingObject;
import zombie.iso.IsoObject;
import zombie.iso.IsoUtils;
import zombie.iso.IsoWorld;
import zombie.iso.Vector2;
import zombie.iso.SpriteDetails.IsoFlagType;
import zombie.iso.objects.IsoDoor;
import zombie.iso.objects.IsoThumpable;
import zombie.iso.objects.IsoWindow;
import zombie.network.GameClient;
import zombie.popman.ObjectPool;
import zombie.scripting.objects.VehicleScript;
import zombie.scripting.objects.VehicleScript.Area;
import zombie.scripting.objects.VehicleScript.Position;
import zombie.util.Type;
import zombie.vehicles.BaseVehicle.Vector2ObjectPool;
import zombie.vehicles.BaseVehicle.Vector3fObjectPool;
import zombie.vehicles.PathFindBehavior2.BehaviorResult;
import zombie.vehicles.PathFindBehavior2.DebugPt;
import zombie.vehicles.PathFindBehavior2.Goal;
import zombie.vehicles.PathFindBehavior2.NPCData;
import zombie.vehicles.PathFindBehavior2.PointOnPath;
import zombie.vehicles.PolygonalMap2.IPathfinder;
import zombie.vehicles.PolygonalMap2.Path;
import zombie.vehicles.PolygonalMap2.PathFindRequest;
import zombie.vehicles.PolygonalMap2.PathNode;

public final class PathFindBehavior2 implements IPathfinder {
   private static final Vector2 tempVector2 = new Vector2();
   private static final Vector2f tempVector2f = new Vector2f();
   private static final Vector2 tempVector2_2 = new Vector2();
   private static final Vector3f tempVector3f_1 = new Vector3f();
   private static final PointOnPath pointOnPath = new PointOnPath();
   public boolean pathNextIsSet = false;
   public float pathNextX;
   public float pathNextY;
   public ArrayList<zombie.ai.astar.IPathfinder> Listeners = new ArrayList<>();
   public NPCData NPCData = new NPCData(this);
   private IsoGameCharacter chr;
   private float startX;
   private float startY;
   private float startZ;
   private float targetX;
   private float targetY;
   private float targetZ;
   private final TFloatArrayList targetXYZ = new TFloatArrayList();
   private final Path path = new Path();
   private int pathIndex;
   private boolean isCancel = true;
   public boolean bStopping = false;
   public final WalkingOnTheSpot walkingOnTheSpot = new WalkingOnTheSpot();
   private final ArrayList<DebugPt> actualPos = new ArrayList<>();
   private static final ObjectPool<DebugPt> actualPool = new ObjectPool(DebugPt::new);
   private Goal goal = Goal.None;
   private IsoGameCharacter goalCharacter;
   private BaseVehicle goalVehicle;
   private String goalVehicleArea;
   private int goalVehicleSeat;

   public PathFindBehavior2(IsoGameCharacter var1) {
      this.chr = var1;
   }

   public boolean isGoalNone() {
      return this.goal == Goal.None;
   }

   public boolean isGoalCharacter() {
      return this.goal == Goal.Character;
   }

   public boolean isGoalLocation() {
      return this.goal == Goal.Location;
   }

   public boolean isGoalSound() {
      return this.goal == Goal.Sound;
   }

   public boolean isGoalVehicleAdjacent() {
      return this.goal == Goal.VehicleAdjacent;
   }

   public boolean isGoalVehicleArea() {
      return this.goal == Goal.VehicleArea;
   }

   public boolean isGoalVehicleSeat() {
      return this.goal == Goal.VehicleSeat;
   }

   public void reset() {
      this.startX = this.chr.getX();
      this.startY = this.chr.getY();
      this.startZ = this.chr.getZ();
      this.targetX = this.startX;
      this.targetY = this.startY;
      this.targetZ = this.startZ;
      this.targetXYZ.resetQuick();
      this.pathIndex = 0;
      this.chr.getFinder().progress = PathFindProgress.notrunning;
      this.walkingOnTheSpot.reset(this.startX, this.startY);
   }

   public void pathToCharacter(IsoGameCharacter var1) {
      this.isCancel = false;
      this.goal = Goal.Character;
      this.goalCharacter = var1;
      if (var1.getVehicle() != null) {
         Vector3f var2 = var1.getVehicle().chooseBestAttackPosition(var1, this.chr, tempVector3f_1);
         if (var2 != null) {
            this.setData(var2.x, var2.y, (int)var1.getVehicle().z);
            return;
         }

         this.setData(var1.getVehicle().x, var1.getVehicle().y, (int)var1.getVehicle().z);
         if (this.chr.DistToSquared(var1.getVehicle()) < 100.0F) {
            IsoZombie var3 = (IsoZombie)Type.tryCastTo(this.chr, IsoZombie.class);
            if (var3 != null) {
               var3.AllowRepathDelay = 100.0F;
            }

            this.chr.getFinder().progress = PathFindProgress.failed;
         }
      }

      this.setData(var1.getX(), var1.getY(), var1.getZ());
   }

   public void pathToLocation(int var1, int var2, int var3) {
      this.isCancel = false;
      this.goal = Goal.Location;
      this.setData(var1 + 0.5F, var2 + 0.5F, var3);
   }

   public void pathToLocationF(float var1, float var2, float var3) {
      this.isCancel = false;
      this.goal = Goal.Location;
      this.setData(var1, var2, var3);
   }

   public void pathToSound(int var1, int var2, int var3) {
      this.isCancel = false;
      this.goal = Goal.Sound;
      this.setData(var1 + 0.5F, var2 + 0.5F, var3);
   }

   public void pathToNearest(TFloatArrayList var1) {
      if (var1 != null && !var1.isEmpty()) {
         if (var1.size() % 3 != 0) {
            throw new IllegalArgumentException("locations should be multiples of x,y,z");
         } else {
            this.isCancel = false;
            this.goal = Goal.Location;
            this.setData(var1.get(0), var1.get(1), var1.get(2));

            for (byte var2 = 3; var2 < var1.size(); var2 += 3) {
               this.targetXYZ.add(var1.get(var2));
               this.targetXYZ.add(var1.get(var2 + 1));
               this.targetXYZ.add(var1.get(var2 + 2));
            }
         }
      } else {
         throw new IllegalArgumentException("locations is null or empty");
      }
   }

   public void pathToNearestTable(KahluaTable var1) {
      if (var1 != null && !var1.isEmpty()) {
         if (var1.len() % 3 != 0) {
            throw new IllegalArgumentException("locations table should be multiples of x,y,z");
         } else {
            TFloatArrayList var2 = new TFloatArrayList(var1.size());
            byte var3 = 1;

            for (int var4 = var1.len(); var3 <= var4; var3 += 3) {
               Double var5 = (Double)Type.tryCastTo(var1.rawget(var3), Double.class);
               Double var6 = (Double)Type.tryCastTo(var1.rawget(var3 + 1), Double.class);
               Double var7 = (Double)Type.tryCastTo(var1.rawget(var3 + 2), Double.class);
               if (var5 == null || var6 == null || var7 == null) {
                  throw new IllegalArgumentException("locations table should be multiples of x,y,z");
               }

               var2.add(var5.floatValue());
               var2.add(var6.floatValue());
               var2.add(var7.floatValue());
            }

            this.pathToNearest(var2);
         }
      } else {
         throw new IllegalArgumentException("locations table is null or empty");
      }
   }

   public void pathToVehicleAdjacent(BaseVehicle var1) {
      this.isCancel = false;
      this.goal = Goal.VehicleAdjacent;
      this.goalVehicle = var1;
      VehicleScript var2 = var1.getScript();
      Vector3f var3 = var2.getExtents();
      Vector3f var4 = var2.getCenterOfMassOffset();
      float var5 = var3.x;
      float var6 = var3.z;
      float var7 = 0.3F;
      float var8 = var4.x - var5 / 2.0F - var7;
      float var9 = var4.z - var6 / 2.0F - var7;
      float var10 = var4.x + var5 / 2.0F + var7;
      float var11 = var4.z + var6 / 2.0F + var7;
      TFloatArrayList var12 = new TFloatArrayList();
      Vector3f var13 = var1.getWorldPos(var8, var4.y, var4.z, tempVector3f_1);
      if (PolygonalMap2.instance.canStandAt(var13.x, var13.y, (int)this.targetZ, var1, false, true)) {
         var12.add(var13.x);
         var12.add(var13.y);
         var12.add(this.targetZ);
      }

      var13 = var1.getWorldPos(var10, var4.y, var4.z, tempVector3f_1);
      if (PolygonalMap2.instance.canStandAt(var13.x, var13.y, (int)this.targetZ, var1, false, true)) {
         var12.add(var13.x);
         var12.add(var13.y);
         var12.add(this.targetZ);
      }

      var13 = var1.getWorldPos(var4.x, var4.y, var9, tempVector3f_1);
      if (PolygonalMap2.instance.canStandAt(var13.x, var13.y, (int)this.targetZ, var1, false, true)) {
         var12.add(var13.x);
         var12.add(var13.y);
         var12.add(this.targetZ);
      }

      var13 = var1.getWorldPos(var4.x, var4.y, var11, tempVector3f_1);
      if (PolygonalMap2.instance.canStandAt(var13.x, var13.y, (int)this.targetZ, var1, false, true)) {
         var12.add(var13.x);
         var12.add(var13.y);
         var12.add(this.targetZ);
      }

      this.setData(var12.get(0), var12.get(1), var12.get(2));

      for (byte var14 = 3; var14 < var12.size(); var14 += 3) {
         this.targetXYZ.add(var12.get(var14));
         this.targetXYZ.add(var12.get(var14 + 1));
         this.targetXYZ.add(var12.get(var14 + 2));
      }
   }

   public void pathToVehicleArea(BaseVehicle var1, String var2) {
      Vector2 var3 = var1.getAreaCenter(var2);
      if (var3 == null) {
         this.targetX = this.chr.getX();
         this.targetY = this.chr.getY();
         this.targetZ = this.chr.getZ();
         this.chr.getFinder().progress = PathFindProgress.failed;
      } else {
         this.isCancel = false;
         this.goal = Goal.VehicleArea;
         this.goalVehicle = var1;
         this.goalVehicleArea = var2;
         this.setData(var3.getX(), var3.getY(), (int)var1.getZ());
         if (this.chr instanceof IsoPlayer
            && (int)this.chr.z == (int)this.targetZ
            && !PolygonalMap2.instance.lineClearCollide(this.chr.x, this.chr.y, this.targetX, this.targetY, (int)this.targetZ, null)) {
            this.path.clear();
            this.path.addNode(this.chr.x, this.chr.y, this.chr.z);
            this.path.addNode(this.targetX, this.targetY, this.targetZ);
            this.chr.getFinder().progress = PathFindProgress.found;
         }
      }
   }

   public void pathToVehicleSeat(BaseVehicle var1, int var2) {
      Position var3 = var1.getPassengerPosition(var2, "outside2");
      if (var3 != null) {
         Vector3f var4 = (Vector3f)((Vector3fObjectPool)BaseVehicle.TL_vector3f_pool.get()).alloc();
         if (var3.area == null) {
            var1.getPassengerPositionWorldPos(var3, var4);
         } else {
            Vector2 var5 = (Vector2)((Vector2ObjectPool)BaseVehicle.TL_vector2_pool.get()).alloc();
            Area var6 = var1.script.getAreaById(var3.area);
            Vector2 var7 = var1.areaPositionWorld4PlayerInteract(var6, var5);
            var4.x = var7.x;
            var4.y = var7.y;
            var4.z = 0.0F;
            ((Vector2ObjectPool)BaseVehicle.TL_vector2_pool.get()).release(var5);
         }

         var4.sub(this.chr.x, this.chr.y, this.chr.z);
         if (var4.length() < 2.0F) {
            var1.getPassengerPositionWorldPos(var3, var4);
            this.setData(var4.x(), var4.y(), (int)var4.z());
            if (this.chr instanceof IsoPlayer && (int)this.chr.z == (int)this.targetZ) {
               ((Vector3fObjectPool)BaseVehicle.TL_vector3f_pool.get()).release(var4);
               this.path.clear();
               this.path.addNode(this.chr.x, this.chr.y, this.chr.z);
               this.path.addNode(this.targetX, this.targetY, this.targetZ);
               this.chr.getFinder().progress = PathFindProgress.found;
               return;
            }
         }

         ((Vector3fObjectPool)BaseVehicle.TL_vector3f_pool.get()).release(var4);
      }

      var3 = var1.getPassengerPosition(var2, "outside");
      if (var3 == null) {
         VehiclePart var10 = var1.getPassengerDoor(var2);
         if (var10 == null) {
            this.targetX = this.chr.getX();
            this.targetY = this.chr.getY();
            this.targetZ = this.chr.getZ();
            this.chr.getFinder().progress = PathFindProgress.failed;
         } else {
            this.pathToVehicleArea(var1, var10.getArea());
         }
      } else {
         this.isCancel = false;
         this.goal = Goal.VehicleSeat;
         this.goalVehicle = var1;
         Vector3f var9 = (Vector3f)((Vector3fObjectPool)BaseVehicle.TL_vector3f_pool.get()).alloc();
         if (var3.area == null) {
            var1.getPassengerPositionWorldPos(var3, var9);
         } else {
            Vector2 var11 = (Vector2)((Vector2ObjectPool)BaseVehicle.TL_vector2_pool.get()).alloc();
            Area var12 = var1.script.getAreaById(var3.area);
            Vector2 var13 = var1.areaPositionWorld4PlayerInteract(var12, var11);
            var9.x = var13.x;
            var9.y = var13.y;
            var9.z = 0.0F;
            ((Vector2ObjectPool)BaseVehicle.TL_vector2_pool.get()).release(var11);
         }

         this.setData(var9.x(), var9.y(), (int)var9.z());
         ((Vector3fObjectPool)BaseVehicle.TL_vector3f_pool.get()).release(var9);
         if (this.chr instanceof IsoPlayer
            && (int)this.chr.z == (int)this.targetZ
            && !PolygonalMap2.instance.lineClearCollide(this.chr.x, this.chr.y, this.targetX, this.targetY, (int)this.targetZ, null)) {
            this.path.clear();
            this.path.addNode(this.chr.x, this.chr.y, this.chr.z);
            this.path.addNode(this.targetX, this.targetY, this.targetZ);
            this.chr.getFinder().progress = PathFindProgress.found;
         }
      }
   }

   public void cancel() {
      this.isCancel = true;
   }

   public boolean getIsCancelled() {
      return this.isCancel;
   }

   public void setData(float var1, float var2, float var3) {
      this.startX = this.chr.getX();
      this.startY = this.chr.getY();
      this.startZ = this.chr.getZ();
      this.targetX = var1;
      this.targetY = var2;
      this.targetZ = var3;
      this.targetXYZ.resetQuick();
      this.pathIndex = 0;
      PolygonalMap2.instance.cancelRequest(this.chr);
      this.chr.getFinder().progress = PathFindProgress.notrunning;
      this.bStopping = false;
      actualPool.release(this.actualPos);
      this.actualPos.clear();
   }

   public float getTargetX() {
      return this.targetX;
   }

   public float getTargetY() {
      return this.targetY;
   }

   public float getTargetZ() {
      return this.targetZ;
   }

   public float getPathLength() {
      if (this.path != null && this.path.nodes.size() != 0) {
         if (this.pathIndex + 1 >= this.path.nodes.size()) {
            return (float)Math.sqrt((this.chr.x - this.targetX) * (this.chr.x - this.targetX) + (this.chr.y - this.targetY) * (this.chr.y - this.targetY));
         } else {
            float var1 = (float)Math.sqrt(
               (this.chr.x - ((PathNode)this.path.nodes.get(this.pathIndex + 1)).x) * (this.chr.x - ((PathNode)this.path.nodes.get(this.pathIndex + 1)).x)
                  + (this.chr.y - ((PathNode)this.path.nodes.get(this.pathIndex + 1)).y) * (this.chr.y - ((PathNode)this.path.nodes.get(this.pathIndex + 1)).y)
            );

            for (int var2 = this.pathIndex + 2; var2 < this.path.nodes.size(); var2++) {
               var1 += (float)Math.sqrt(
                  (((PathNode)this.path.nodes.get(var2 - 1)).x - ((PathNode)this.path.nodes.get(var2)).x)
                        * (((PathNode)this.path.nodes.get(var2 - 1)).x - ((PathNode)this.path.nodes.get(var2)).x)
                     + (((PathNode)this.path.nodes.get(var2 - 1)).y - ((PathNode)this.path.nodes.get(var2)).y)
                        * (((PathNode)this.path.nodes.get(var2 - 1)).y - ((PathNode)this.path.nodes.get(var2)).y)
               );
            }

            return var1;
         }
      } else {
         return (float)Math.sqrt((this.chr.x - this.targetX) * (this.chr.x - this.targetX) + (this.chr.y - this.targetY) * (this.chr.y - this.targetY));
      }
   }

   public IsoGameCharacter getTargetChar() {
      return this.goal == Goal.Character ? this.goalCharacter : null;
   }

   public boolean isTargetLocation(float var1, float var2, float var3) {
      return this.goal == Goal.Location && var1 == this.targetX && var2 == this.targetY && (int)var3 == (int)this.targetZ;
   }

   public BehaviorResult update() {
      if (this.chr.getFinder().progress == PathFindProgress.notrunning) {
         PathFindRequest var10 = PolygonalMap2.instance
            .addRequest(this, this.chr, this.startX, this.startY, this.startZ, this.targetX, this.targetY, this.targetZ);
         var10.targetXYZ.resetQuick();
         var10.targetXYZ.addAll(this.targetXYZ);
         this.chr.getFinder().progress = PathFindProgress.notyetfound;
         this.walkingOnTheSpot.reset(this.chr.x, this.chr.y);
         this.updateWhileRunningPathfind();
         return BehaviorResult.Working;
      } else if (this.chr.getFinder().progress == PathFindProgress.notyetfound) {
         this.updateWhileRunningPathfind();
         return BehaviorResult.Working;
      } else if (this.chr.getFinder().progress == PathFindProgress.failed) {
         return BehaviorResult.Failed;
      } else {
         State var1 = this.chr.getCurrentState();
         if (Core.bDebug && DebugOptions.instance.PathfindRenderPath.getValue() && this.chr instanceof IsoPlayer) {
            this.actualPos
               .add(
                  ((DebugPt)actualPool.alloc())
                     .init(this.chr.x, this.chr.y, this.chr.z, var1 == ClimbOverFenceState.instance() || var1 == ClimbThroughWindowState.instance())
               );
         }

         if (var1 != ClimbOverFenceState.instance() && var1 != ClimbThroughWindowState.instance()) {
            if (this.chr.getVehicle() != null) {
               return BehaviorResult.Failed;
            } else if (this.walkingOnTheSpot.check(this.chr.x, this.chr.y)) {
               return BehaviorResult.Failed;
            } else {
               this.chr.setMoving(true);
               this.chr.setPath2(this.path);
               IsoZombie var2 = (IsoZombie)Type.tryCastTo(this.chr, IsoZombie.class);
               if (this.goal == Goal.Character
                  && var2 != null
                  && this.goalCharacter != null
                  && this.goalCharacter.getVehicle() != null
                  && this.chr.DistToSquared(this.targetX, this.targetY) < 16.0F) {
                  Vector3f var3 = this.goalCharacter.getVehicle().chooseBestAttackPosition(this.goalCharacter, this.chr, tempVector3f_1);
                  if (var3 == null) {
                     return BehaviorResult.Failed;
                  }

                  if (Math.abs(var3.x - this.targetX) > 0.1F || Math.abs(var3.y - this.targetY) > 0.1F) {
                     if (Math.abs(this.goalCharacter.getVehicle().getCurrentSpeedKmHour()) > 0.8F) {
                        if (!PolygonalMap2.instance.lineClearCollide(this.chr.x, this.chr.y, var3.x, var3.y, (int)this.targetZ, this.goalCharacter)) {
                           this.path.clear();
                           this.path.addNode(this.chr.x, this.chr.y, this.chr.z);
                           this.path.addNode(var3.x, var3.y, var3.z);
                        } else if (IsoUtils.DistanceToSquared(var3.x, var3.y, this.targetX, this.targetY)
                           > IsoUtils.DistanceToSquared(this.chr.x, this.chr.y, var3.x, var3.y)) {
                           return BehaviorResult.Working;
                        }
                     } else if (var2.AllowRepathDelay <= 0.0F) {
                        var2.AllowRepathDelay = 6.25F;
                        if (PolygonalMap2.instance.lineClearCollide(this.chr.x, this.chr.y, var3.x, var3.y, (int)this.targetZ, null)) {
                           this.setData(var3.x, var3.y, this.targetZ);
                           return BehaviorResult.Working;
                        }

                        this.path.clear();
                        this.path.addNode(this.chr.x, this.chr.y, this.chr.z);
                        this.path.addNode(var3.x, var3.y, var3.z);
                     }
                  }
               }

               closestPointOnPath(this.chr.x, this.chr.y, this.chr.z, this.chr, this.path, pointOnPath);
               this.pathIndex = pointOnPath.pathIndex;
               if (this.pathIndex == this.path.nodes.size() - 2) {
                  PathNode var11 = (PathNode)this.path.nodes.get(this.path.nodes.size() - 1);
                  if (IsoUtils.DistanceToSquared(this.chr.x, this.chr.y, var11.x, var11.y) <= 0.0025000002F) {
                     this.chr.getDeferredMovement(tempVector2);
                     if (!(tempVector2.getLength() > 0.0F)) {
                        this.pathNextIsSet = false;
                        return BehaviorResult.Succeeded;
                     }

                     if (var2 != null || this.chr instanceof IsoPlayer) {
                        this.chr.setMoving(false);
                     }

                     this.bStopping = true;
                     return BehaviorResult.Working;
                  }
               } else if (this.pathIndex < this.path.nodes.size() - 2 && pointOnPath.dist > 0.999F) {
                  this.pathIndex++;
               }

               PathNode var12 = (PathNode)this.path.nodes.get(this.pathIndex);
               PathNode var4 = (PathNode)this.path.nodes.get(this.pathIndex + 1);
               this.pathNextX = var4.x;
               this.pathNextY = var4.y;
               this.pathNextIsSet = true;
               Vector2 var5 = tempVector2.set(this.pathNextX - this.chr.x, this.pathNextY - this.chr.y);
               var5.normalize();
               this.chr.getDeferredMovement(tempVector2_2);
               float var6 = tempVector2_2.getLength();
               if (var2 != null) {
                  var2.bRunning = false;
                  if (SandboxOptions.instance.Lore.Speed.getValue() == 1) {
                     var2.bRunning = true;
                  }
               }

               float var7 = 1.0F;
               float var8 = var6 * var7;
               float var9 = IsoUtils.DistanceTo(this.pathNextX, this.pathNextY, this.chr.x, this.chr.y);
               if (var8 >= var9) {
                  var6 *= var9 / var8;
                  this.pathIndex++;
               }

               if (var2 != null) {
                  this.checkCrawlingTransition(var12, var4, var9);
               }

               if (var2 == null && var9 >= 0.5F) {
                  if (this.checkDoorHoppableWindow(this.chr.x + var5.x * Math.max(0.5F, var6), this.chr.y + var5.y * Math.max(0.5F, var6), this.chr.z)) {
                     return BehaviorResult.Failed;
                  }

                  if (var1 != this.chr.getCurrentState()) {
                     return BehaviorResult.Working;
                  }
               }

               if (var6 <= 0.0F) {
                  this.walkingOnTheSpot.reset(this.chr.x, this.chr.y);
                  return BehaviorResult.Working;
               } else {
                  tempVector2_2.set(var5);
                  tempVector2_2.setLength(var6);
                  this.chr.MoveUnmodded(tempVector2_2);
                  if (this.isStrafing()) {
                     if ((this.goal == Goal.VehicleAdjacent || this.goal == Goal.VehicleArea || this.goal == Goal.VehicleSeat) && this.goalVehicle != null) {
                        this.chr.faceThisObject(this.goalVehicle);
                     }
                  } else if (!this.chr.isAiming()) {
                     this.chr.faceLocationF(this.pathNextX, this.pathNextY);
                  }

                  return BehaviorResult.Working;
               }
            }
         } else {
            if (GameClient.bClient && this.chr instanceof IsoPlayer && !((IsoPlayer)this.chr).isLocalPlayer()) {
               this.chr.getDeferredMovement(tempVector2_2);
               this.chr.MoveUnmodded(tempVector2_2);
            }

            return BehaviorResult.Working;
         }
      }
   }

   private void updateWhileRunningPathfind() {
      if (this.pathNextIsSet) {
         this.moveToPoint(this.pathNextX, this.pathNextY, 1.0F);
      }
   }

   public void moveToPoint(float var1, float var2, float var3) {
      if (!(this.chr instanceof IsoPlayer) || this.chr.getCurrentState() != CollideWithWallState.instance()) {
         IsoZombie var4 = (IsoZombie)Type.tryCastTo(this.chr, IsoZombie.class);
         Vector2 var5 = tempVector2.set(var1 - this.chr.x, var2 - this.chr.y);
         if ((int)var1 != (int)this.chr.x || (int)var2 != (int)this.chr.y || !(var5.getLength() <= 0.1F)) {
            var5.normalize();
            this.chr.getDeferredMovement(tempVector2_2);
            float var6 = tempVector2_2.getLength();
            var6 *= var3;
            if (var4 != null) {
               var4.bRunning = false;
               if (SandboxOptions.instance.Lore.Speed.getValue() == 1) {
                  var4.bRunning = true;
               }
            }

            if (!(var6 <= 0.0F)) {
               tempVector2_2.set(var5);
               tempVector2_2.setLength(var6);
               this.chr.MoveUnmodded(tempVector2_2);
               this.chr.faceLocation(var1 - 0.5F, var2 - 0.5F);
               this.chr.getForwardDirection().set(var1 - this.chr.x, var2 - this.chr.y);
               this.chr.getForwardDirection().normalize();
            }
         }
      }
   }

   public void moveToDir(IsoMovingObject var1, float var2) {
      Vector2 var3 = tempVector2.set(var1.x - this.chr.x, var1.y - this.chr.y);
      if (!(var3.getLength() <= 0.1F)) {
         var3.normalize();
         this.chr.getDeferredMovement(tempVector2_2);
         float var4 = tempVector2_2.getLength();
         var4 *= var2;
         if (this.chr instanceof IsoZombie) {
            ((IsoZombie)this.chr).bRunning = false;
            if (SandboxOptions.instance.Lore.Speed.getValue() == 1) {
               ((IsoZombie)this.chr).bRunning = true;
            }
         }

         if (!(var4 <= 0.0F)) {
            tempVector2_2.set(var3);
            tempVector2_2.setLength(var4);
            this.chr.MoveUnmodded(tempVector2_2);
            this.chr.faceLocation(var1.x - 0.5F, var1.y - 0.5F);
            this.chr.getForwardDirection().set(var1.x - this.chr.x, var1.y - this.chr.y);
            this.chr.getForwardDirection().normalize();
         }
      }
   }

   private boolean checkDoorHoppableWindow(float var1, float var2, float var3) {
      IsoGridSquare var4 = this.chr.getCurrentSquare();
      if (var4 == null) {
         return false;
      } else {
         IsoGridSquare var5 = IsoWorld.instance.CurrentCell.getGridSquare(var1, var2, var3);
         if (var5 != null && var5 != var4) {
            int var6 = var5.x - var4.x;
            int var7 = var5.y - var4.y;
            if (var6 != 0 && var7 != 0) {
               return false;
            } else {
               IsoObject var8 = this.chr.getCurrentSquare().getDoorTo(var5);
               if (var8 instanceof IsoDoor var9) {
                  if (!var9.open) {
                     var9.ToggleDoor(this.chr);
                     if (!var9.open) {
                        return true;
                     }
                  }
               } else if (var8 instanceof IsoThumpable var12 && !var12.open) {
                  var12.ToggleDoor(this.chr);
                  if (!var12.open) {
                     return true;
                  }
               }

               IsoWindow var13 = var4.getWindowTo(var5);
               if (var13 != null) {
                  if (var13.canClimbThrough(this.chr) && (!var13.isSmashed() || var13.isGlassRemoved())) {
                     this.chr.climbThroughWindow(var13);
                     return false;
                  } else {
                     return true;
                  }
               } else {
                  IsoThumpable var10 = var4.getWindowThumpableTo(var5);
                  if (var10 == null) {
                     IsoObject var11 = var4.getWindowFrameTo(var5);
                     if (var11 != null) {
                        this.chr.climbThroughWindowFrame(var11);
                        return false;
                     } else {
                        if (var6 > 0 && var5.Is(IsoFlagType.HoppableW)) {
                           this.chr.climbOverFence(IsoDirections.E);
                        } else if (var6 < 0 && var4.Is(IsoFlagType.HoppableW)) {
                           this.chr.climbOverFence(IsoDirections.W);
                        } else if (var7 < 0 && var4.Is(IsoFlagType.HoppableN)) {
                           this.chr.climbOverFence(IsoDirections.N);
                        } else if (var7 > 0 && var5.Is(IsoFlagType.HoppableN)) {
                           this.chr.climbOverFence(IsoDirections.S);
                        }

                        return false;
                     }
                  } else if (var10.isBarricaded()) {
                     return true;
                  } else {
                     this.chr.climbThroughWindow(var10);
                     return false;
                  }
               }
            }
         } else {
            return false;
         }
      }
   }

   private void checkCrawlingTransition(PathNode var1, PathNode var2, float var3) {
      IsoZombie var4 = (IsoZombie)this.chr;
      if (this.pathIndex < this.path.nodes.size() - 2) {
         var1 = (PathNode)this.path.nodes.get(this.pathIndex);
         var2 = (PathNode)this.path.nodes.get(this.pathIndex + 1);
         var3 = IsoUtils.DistanceTo(var2.x, var2.y, this.chr.x, this.chr.y);
      }

      if (var4.isCrawling()) {
         if (!var4.isCanWalk()) {
            return;
         }

         if (var4.isBeingSteppedOn()) {
         }

         if (var4.getStateMachine().getPrevious() == ZombieGetDownState.instance() && ZombieGetDownState.instance().isNearStartXY(var4)) {
            return;
         }

         this.advanceAlongPath(this.chr.x, this.chr.y, this.chr.z, 0.5F, pointOnPath);
         if (!PolygonalMap2.instance.canStandAt(pointOnPath.x, pointOnPath.y, (int)var4.z, null, false, true)) {
            return;
         }

         if (!var2.hasFlag(1) && PolygonalMap2.instance.canStandAt(var4.x, var4.y, (int)var4.z, null, false, true)) {
            var4.setVariable("ShouldStandUp", true);
         }
      } else {
         if (var1.hasFlag(1) && var2.hasFlag(1)) {
            var4.setVariable("ShouldBeCrawling", true);
            ZombieGetDownState.instance().setParams(this.chr);
            return;
         }

         if (var3 < 0.4F && !var1.hasFlag(1) && var2.hasFlag(1)) {
            var4.setVariable("ShouldBeCrawling", true);
            ZombieGetDownState.instance().setParams(this.chr);
         }
      }
   }

   public boolean shouldGetUpFromCrawl() {
      return this.chr.getVariableBoolean("ShouldStandUp");
   }

   public boolean isStrafing() {
      return this.chr.isZombie()
         ? false
         : this.path.nodes.size() == 2
            && IsoUtils.DistanceToSquared(this.startX, this.startY, this.startZ * 3.0F, this.targetX, this.targetY, this.targetZ * 3.0F) < 0.25F;
   }

   public static void closestPointOnPath(float var0, float var1, float var2, IsoMovingObject var3, Path var4, PointOnPath var5) {
      IsoCell var6 = IsoWorld.instance.CurrentCell;
      var5.pathIndex = 0;
      float var7 = Float.MAX_VALUE;

      for (int var8 = 0; var8 < var4.nodes.size() - 1; var8++) {
         PathNode var9 = (PathNode)var4.nodes.get(var8);
         PathNode var10 = (PathNode)var4.nodes.get(var8 + 1);
         if ((int)var9.z == (int)var2 || (int)var10.z == (int)var2) {
            float var11 = var9.x;
            float var12 = var9.y;
            float var13 = var10.x;
            float var14 = var10.y;
            double var15 = ((var0 - var11) * (var13 - var11) + (var1 - var12) * (var14 - var12))
               / (Math.pow(var13 - var11, 2.0) + Math.pow(var14 - var12, 2.0));
            double var17 = var11 + var15 * (var13 - var11);
            double var19 = var12 + var15 * (var14 - var12);
            if (var15 <= 0.0) {
               var17 = var11;
               var19 = var12;
               var15 = 0.0;
            } else if (var15 >= 1.0) {
               var17 = var13;
               var19 = var14;
               var15 = 1.0;
            }

            int var21 = (int)var17 - (int)var0;
            int var22 = (int)var19 - (int)var1;
            if ((var21 != 0 || var22 != 0) && Math.abs(var21) <= 1 && Math.abs(var22) <= 1) {
               IsoGridSquare var23 = var6.getGridSquare((int)var0, (int)var1, (int)var2);
               IsoGridSquare var24 = var6.getGridSquare((int)var17, (int)var19, (int)var2);
               if (var3 instanceof IsoZombie) {
                  boolean var25 = ((IsoZombie)var3).Ghost;
                  ((IsoZombie)var3).Ghost = true;

                  try {
                     if (var23 != null && var24 != null && var23.testCollideAdjacent(var3, var21, var22, 0)) {
                        continue;
                     }
                  } finally {
                     ((IsoZombie)var3).Ghost = var25;
                  }
               } else if (var23 != null && var24 != null && var23.testCollideAdjacent(var3, var21, var22, 0)) {
                  continue;
               }
            }

            float var30 = var2;
            if (Math.abs(var21) <= 1 && Math.abs(var22) <= 1) {
               IsoGridSquare var31 = var6.getGridSquare((int)var9.x, (int)var9.y, (int)var9.z);
               IsoGridSquare var33 = var6.getGridSquare((int)var10.x, (int)var10.y, (int)var10.z);
               float var26 = var31 == null ? var9.z : PolygonalMap2.instance.getApparentZ(var31);
               float var27 = var33 == null ? var10.z : PolygonalMap2.instance.getApparentZ(var33);
               var30 = var26 + (var27 - var26) * (float)var15;
            }

            float var32 = IsoUtils.DistanceToSquared(var0, var1, var2, (float)var17, (float)var19, var30);
            if (var32 < var7) {
               var7 = var32;
               var5.pathIndex = var8;
               var5.dist = var15 == 1.0 ? 1.0F : (float)var15;
               var5.x = (float)var17;
               var5.y = (float)var19;
            }
         }
      }
   }

   void advanceAlongPath(float var1, float var2, float var3, float var4, PointOnPath var5) {
      closestPointOnPath(var1, var2, var3, this.chr, this.path, var5);

      for (int var6 = var5.pathIndex; var6 < this.path.nodes.size() - 1; var6++) {
         PathNode var7 = (PathNode)this.path.nodes.get(var6);
         PathNode var8 = (PathNode)this.path.nodes.get(var6 + 1);
         double var9 = IsoUtils.DistanceTo2D(var1, var2, var8.x, var8.y);
         if (!(var4 > var9)) {
            var5.pathIndex = var6;
            var5.dist = var5.dist + var4 / IsoUtils.DistanceTo2D(var7.x, var7.y, var8.x, var8.y);
            var5.x = var7.x + var5.dist * (var8.x - var7.x);
            var5.y = var7.y + var5.dist * (var8.y - var7.y);
            return;
         }

         var1 = var8.x;
         var2 = var8.y;
         var4 = (float)(var4 - var9);
         var5.dist = 0.0F;
      }

      var5.pathIndex = this.path.nodes.size() - 1;
      var5.dist = 1.0F;
      var5.x = ((PathNode)this.path.nodes.get(var5.pathIndex)).x;
      var5.y = ((PathNode)this.path.nodes.get(var5.pathIndex)).y;
   }

   public void render() {
      if (this.chr.getCurrentState() == WalkTowardState.instance()) {
         WalkTowardState.instance().calculateTargetLocation((IsoZombie)this.chr, tempVector2);
         tempVector2.x = tempVector2.x - this.chr.x;
         tempVector2.y = tempVector2.y - this.chr.y;
         tempVector2.setLength(Math.min(100.0F, tempVector2.getLength()));
         LineDrawer.addLine(
            this.chr.x, this.chr.y, this.chr.z, this.chr.x + tempVector2.x, this.chr.y + tempVector2.y, this.targetZ, 1.0F, 1.0F, 1.0F, null, true
         );
      } else if (this.chr.getPath2() != null) {
         for (int var1 = 0; var1 < this.path.nodes.size() - 1; var1++) {
            PathNode var2 = (PathNode)this.path.nodes.get(var1);
            PathNode var3 = (PathNode)this.path.nodes.get(var1 + 1);
            float var4 = 1.0F;
            float var5 = 1.0F;
            if ((int)var2.z != (int)var3.z) {
               var5 = 0.0F;
            }

            LineDrawer.addLine(var2.x, var2.y, var2.z, var3.x, var3.y, var3.z, var4, var5, 0.0F, null, true);
         }

         for (int var6 = 0; var6 < this.path.nodes.size(); var6++) {
            PathNode var8 = (PathNode)this.path.nodes.get(var6);
            float var10 = 1.0F;
            float var12 = 1.0F;
            float var13 = 0.0F;
            if (var6 == 0) {
               var10 = 0.0F;
               var13 = 1.0F;
            }

            LineDrawer.addLine(var8.x - 0.05F, var8.y - 0.05F, var8.z, var8.x + 0.05F, var8.y + 0.05F, var8.z, var10, var12, var13, null, false);
         }

         closestPointOnPath(this.chr.x, this.chr.y, this.chr.z, this.chr, this.path, pointOnPath);
         LineDrawer.addLine(
            pointOnPath.x - 0.05F, pointOnPath.y - 0.05F, this.chr.z, pointOnPath.x + 0.05F, pointOnPath.y + 0.05F, this.chr.z, 0.0F, 1.0F, 0.0F, null, false
         );

         for (int var7 = 0; var7 < this.actualPos.size() - 1; var7++) {
            DebugPt var9 = this.actualPos.get(var7);
            DebugPt var11 = this.actualPos.get(var7 + 1);
            LineDrawer.addLine(var9.x, var9.y, this.chr.z, var11.x, var11.y, this.chr.z, 1.0F, 1.0F, 1.0F, null, true);
            LineDrawer.addLine(
               var9.x - 0.05F, var9.y - 0.05F, this.chr.z, var9.x + 0.05F, var9.y + 0.05F, this.chr.z, 1.0F, var9.climbing ? 1.0F : 0.0F, 0.0F, null, false
            );
         }
      }
   }

   public void Succeeded(Path var1, Mover var2) {
      this.path.copyFrom(var1);
      if (!this.isCancel) {
         this.chr.setPath2(this.path);
      }

      if (!var1.isEmpty()) {
         PathNode var3 = (PathNode)var1.nodes.get(var1.nodes.size() - 1);
         this.targetX = var3.x;
         this.targetY = var3.y;
         this.targetZ = var3.z;
      }

      this.chr.getFinder().progress = PathFindProgress.found;
   }

   public void Failed(Mover var1) {
      this.chr.getFinder().progress = PathFindProgress.failed;
   }

   public boolean isMovingUsingPathFind() {
      return !this.bStopping && !this.isGoalNone() && !this.isCancel;
   }
}
