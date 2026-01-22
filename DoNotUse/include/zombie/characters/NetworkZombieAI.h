#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/ai/states/ClimbOverFenceState.h"
#include "zombie/ai/states/ClimbOverWallState.h"
#include "zombie/ai/states/ClimbThroughWindowState.h"
#include "zombie/ai/states/LungeState.h"
#include "zombie/ai/states/PathFindState.h"
#include "zombie/ai/states/ThumpState.h"
#include "zombie/ai/states/WalkTowardState.h"
#include "zombie/characters/NetworkCharacter/Transform.h"
#include "zombie/characters/NetworkTeleport/Type.h"
#include "zombie/core/Core.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/utils/UpdateTimer.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/debug/DebugType.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/Vector2.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/NetworkVariables/PredictionTypes.h"
#include "zombie/network/NetworkVariables/WalkType.h"
#include "zombie/network/NetworkVariables/ZombieState.h"
#include "zombie/network/packets/ZombiePacket.h"
#include "zombie/popman/NetworkZombieSimulator.h"
#include "zombie/vehicles/PathFindBehavior2.h"

namespace zombie {
namespace characters {


class NetworkZombieAI : public NetworkCharacterAI {
public:
    const UpdateTimer timer;
    const PathFindBehavior2 pfb2;
    const IsoZombie zombie;
    bool usePathFind = false;
    float targetX = 0.0F;
    float targetY = 0.0F;
    int targetZ = 0;
    bool isClimbing;
    uint8_t flags;
    uint8_t direction;
    const NetworkZombieMind mindSync;
    short reanimatedBodyID;
    bool DebugInterfaceActive = false;

    public NetworkZombieAI(IsoGameCharacter var1) {
      super(var1);
      this.zombie = (IsoZombie)var1;
      this.isClimbing = false;
      this.flags = 0;
      this.pfb2 = this.zombie.getPathFindBehavior2();
      this.timer = std::make_unique<UpdateTimer>();
      this.mindSync = std::make_shared<NetworkZombieMind>(this.zombie);
      var1.ulBeatenVehicle.Reset(400L);
      this.reanimatedBodyID = -1;
   }

    void reset() {
      super.reset();
      this.usePathFind = true;
      this.targetX = this.zombie.getX();
      this.targetY = this.zombie.getY();
      this.targetZ = (byte)this.zombie.getZ();
      this.isClimbing = false;
      this.flags = 0;
      this.zombie.getHitDir().set(0.0F, 0.0F);
      this.reanimatedBodyID = -1;
   }

    void extraUpdate() {
      NetworkZombieSimulator.getInstance().addExtraUpdate(this.zombie);
   }

    long getUpdateTime() {
      return this.timer.getTime();
   }

    void setUpdateTimer(float var1) {
      this.timer.reset(PZMath.clamp((int)var1, 200, 3800));
   }

    void setUsingExtrapolation(ZombiePacket var1, int var2) {
      if (this.zombie.isMoving()) {
    Vector2 var3 = this.zombie.dir.ToVector();
         this.zombie.networkCharacter.checkReset(var2);
    Transform var4 = this.zombie.networkCharacter.predict(500, var2, this.zombie.x, this.zombie.y, var3.x, var3.y);
         var1.x = var4.position.x;
         var1.y = var4.position.y;
         var1.z = (byte)this.zombie.z;
         var1.moveType = PredictionTypes.Moving;
         this.setUpdateTimer(300.0F);
      } else {
         var1.x = this.zombie.x;
         var1.y = this.zombie.y;
         var1.z = (byte)this.zombie.z;
         var1.moveType = PredictionTypes.Static;
         this.setUpdateTimer(2280.0F);
      }
   }

    void setUsingThump(ZombiePacket var1) {
      var1.x = ((IsoObject)this.zombie.getThumpTarget()).getX();
      var1.y = ((IsoObject)this.zombie.getThumpTarget()).getY();
      var1.z = (byte)((IsoObject)this.zombie.getThumpTarget()).getZ();
      var1.moveType = PredictionTypes.Thump;
      this.setUpdateTimer(2280.0F);
   }

    void setUsingClimb(ZombiePacket var1) {
      var1.x = this.zombie.getTarget().getX();
      var1.y = this.zombie.getTarget().getY();
      var1.z = (byte)this.zombie.getTarget().getZ();
      var1.moveType = PredictionTypes.Climb;
      this.setUpdateTimer(2280.0F);
   }

    void setUsingLungeState(ZombiePacket var1, long var2) {
      if (this.zombie.target == nullptr) {
         this.setUsingExtrapolation(var1, (int)var2);
      } else {
    float var4 = IsoUtils.DistanceTo(this.zombie.target.x, this.zombie.target.y, this.zombie.x, this.zombie.y);
         if (var4 > 5.0F) {
            var1.x = (this.zombie.x + this.zombie.target.x) * 0.5F;
            var1.y = (this.zombie.y + this.zombie.target.y) * 0.5F;
            var1.z = (byte)this.zombie.target.z;
    float var5 = var4 * 0.5F / 5.0E-4F * this.zombie.speedMod;
            var1.moveType = PredictionTypes.LungeHalf;
            this.setUpdateTimer(var5 * 0.6F);
         } else {
            var1.x = this.zombie.target.x;
            var1.y = this.zombie.target.y;
            var1.z = (byte)this.zombie.target.z;
    float var6 = var4 / 5.0E-4F * this.zombie.speedMod;
            var1.moveType = PredictionTypes.Lunge;
            this.setUpdateTimer(var6 * 0.6F);
         }
      }
   }

    void setUsingWalkTowardState(ZombiePacket var1) {
    float var2;
      if (this.zombie.getPath2() == nullptr) {
    float var3 = this.pfb2.getPathLength();
         if (var3 > 5.0F) {
            var1.x = (this.zombie.x + this.pfb2.getTargetX()) * 0.5F;
            var1.y = (this.zombie.y + this.pfb2.getTargetY()) * 0.5F;
            var1.z = (byte)this.pfb2.getTargetZ();
            var2 = var3 * 0.5F / 5.0E-4F * this.zombie.speedMod;
            var1.moveType = PredictionTypes.WalkHalf;
         } else {
            var1.x = this.pfb2.getTargetX();
            var1.y = this.pfb2.getTargetY();
            var1.z = (byte)this.pfb2.getTargetZ();
            var2 = var3 / 5.0E-4F * this.zombie.speedMod;
            var1.moveType = PredictionTypes.Walk;
         }
      } else {
         var1.x = this.pfb2.pathNextX;
         var1.y = this.pfb2.pathNextY;
         var1.z = (byte)this.zombie.z;
         var2 = IsoUtils.DistanceTo(this.zombie.x, this.zombie.y, this.pfb2.pathNextX, this.pfb2.pathNextY) / 5.0E-4F * this.zombie.speedMod;
         var1.moveType = PredictionTypes.Walk;
      }

      this.setUpdateTimer(var2 * 0.6F);
   }

    void setUsingPathFindState(ZombiePacket var1) {
      var1.x = this.pfb2.pathNextX;
      var1.y = this.pfb2.pathNextY;
      var1.z = (byte)this.zombie.z;
    float var2 = IsoUtils.DistanceTo(this.zombie.x, this.zombie.y, this.pfb2.pathNextX, this.pfb2.pathNextY) / 5.0E-4F * this.zombie.speedMod;
      var1.moveType = PredictionTypes.PathFind;
      this.setUpdateTimer(var2 * 0.6F);
   }

    void set(ZombiePacket var1) {
    int var2 = (int)(GameTime.getServerTime() / 1000000L);
      var1.booleanVariables = NetworkZombieVariables.getBooleanVariables(this.zombie);
      var1.realHealth = (short)NetworkZombieVariables.getInt(this.zombie, (short)0);
      var1.target = (short)NetworkZombieVariables.getInt(this.zombie, (short)1);
      var1.speedMod = (short)NetworkZombieVariables.getInt(this.zombie, (short)2);
      var1.timeSinceSeenFlesh = NetworkZombieVariables.getInt(this.zombie, (short)3);
      var1.smParamTargetAngle = NetworkZombieVariables.getInt(this.zombie, (short)4);
      var1.walkType = WalkType.fromString(this.zombie.getVariableString("zombieWalkType"));
      var1.realX = this.zombie.x;
      var1.realY = this.zombie.y;
      var1.realZ = (byte)this.zombie.z;
      this.zombie.realState = ZombieState.fromString(this.zombie.getAdvancedAnimator().getCurrentStateName());
      var1.realState = this.zombie.realState;
      var1.reanimatedBodyID = this.reanimatedBodyID;
      if (this.zombie.getThumpTarget() != nullptr && this.zombie.getCurrentState() == ThumpState.instance()) {
         this.setUsingThump(var1);
      } else if (this.zombie.getTarget() == nullptr
         || this.isClimbing
         || this.zombie.getCurrentState() != ClimbOverFenceState.instance()
            && this.zombie.getCurrentState() != ClimbOverWallState.instance()
            && this.zombie.getCurrentState() != ClimbThroughWindowState.instance()) {
         if (this.zombie.getCurrentState() == WalkTowardState.instance()) {
            this.setUsingWalkTowardState(var1);
         } else if (this.zombie.getCurrentState() == LungeState.instance()) {
            this.setUsingLungeState(var1, var2);
         } else if (this.zombie.getCurrentState() == PathFindState.instance() && this.zombie.isMoving()) {
            this.setUsingPathFindState(var1);
         } else {
            this.setUsingExtrapolation(var1, var2);
         }
      } else {
         this.setUsingClimb(var1);
         this.isClimbing = true;
      }

    Vector2 var3 = this.zombie.dir.ToVector();
      this.zombie.networkCharacter.updateExtrapolationPoint(var2, this.zombie.x, this.zombie.y, var3.x, var3.y);
      if (DebugOptions.instance.MultiplayerLogPrediction.getValue() && Core.bDebug) {
         DebugLog.log(DebugType.Multiplayer, getPredictionDebug(this.zombie, var1, var2, this.getUpdateTime()));
      }
   }

    void parse(ZombiePacket var1) {
    int var2 = (int)(GameTime.getServerTime() / 1000000L);
      if (DebugOptions.instance.MultiplayerLogPrediction.getValue()) {
         this.zombie.getNetworkCharacterAI().addTeleportData(var2, getPredictionDebug(this.zombie, var1, var2, var2));
      }

      if (this.usePathFind) {
         this.pfb2.pathToLocationF(var1.x, var1.y, var1.z);
         this.pfb2.walkingOnTheSpot.reset(this.zombie.x, this.zombie.y);
      }

      this.targetX = var1.x;
      this.targetY = var1.y;
      this.targetZ = var1.z;
      this.predictionType = var1.moveType;
      NetworkZombieVariables.setInt(this.zombie, (short)1, var1.target);
      NetworkZombieVariables.setInt(this.zombie, (short)3, var1.timeSinceSeenFlesh);
      if (this.zombie.isRemoteZombie()) {
         NetworkZombieVariables.setInt(this.zombie, (short)2, var1.speedMod);
         NetworkZombieVariables.setInt(this.zombie, (short)4, var1.smParamTargetAngle);
         NetworkZombieVariables.setBooleanVariables(this.zombie, var1.booleanVariables);
         this.zombie.setWalkType(var1.walkType);
         this.zombie.realState = var1.realState;
      }

      this.zombie.realx = var1.realX;
      this.zombie.realy = var1.realY;
      this.zombie.realz = var1.realZ;
      if ((IsoUtils.DistanceToSquared(this.zombie.x, this.zombie.y, this.zombie.realx, this.zombie.realy) > 9.0F || this.zombie.z != this.zombie.realz)
         && (
            this.zombie.isRemoteZombie()
               || IsoPlayer.getInstance() != nullptr
                  && IsoUtils.DistanceToSquared(this.zombie.x, this.zombie.y, IsoPlayer.getInstance().x, IsoPlayer.getInstance().y) > 2.0F
         )) {
         NetworkTeleport.teleport(this.zombie, Type.teleportation, this.zombie.realx, this.zombie.realy, this.zombie.realz, 1.0F);
      }
   }

    void preupdate() {
      if (GameClient.bClient) {
         if (this.zombie.target != nullptr) {
            this.zombie.setTargetSeenTime(this.zombie.getTargetSeenTime() + GameTime.getInstance().getRealworldSecondsSinceLastUpdate());
         }
      } else if (GameServer.bServer) {
    uint8_t var1 = (byte)((this.zombie.getVariableBoolean("bMoving") ? 1 : 0) | (this.zombie.getVariableBoolean("bPathfind") ? 2 : 0));
         if (this.flags != var1) {
            this.flags = var1;
            this.extraUpdate();
         }

    uint8_t var2 = (byte)IsoDirections.fromAngleActual(this.zombie.getForwardDirection()).index();
         if (this.direction != var2) {
            this.direction = var2;
            this.extraUpdate();
         }
      }
   }

    static std::string getPredictionDebug(IsoGameCharacter var0, ZombiePacket var1, int var2, long var3) {
      return std::string.format(
         "Prediction Z_%d [type=%s, distance=%f], time [current=%d, next=%d], states [current=%s, previous=%s]",
         var1.id,
         var1.moveType,
         IsoUtils.DistanceTo(var0.x, var0.y, var1.x, var1.y),
         var2,
         var3 - var2,
         var0.getCurrentStateName(),
         var0.getPreviousStateName()
      );
   }
}
} // namespace characters
} // namespace zombie
