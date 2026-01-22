#pragma once
#include <list>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/SystemDisabler.h"
#include "zombie/ai/states/CollideWithWallState.h"
#include "zombie/characters/NetworkCharacter/Transform.h"
#include "zombie/core/Rand.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/utils/UpdateTimer.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/input/GameKeyboard.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/Vector2.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/NetworkVariables/PredictionTypes.h"
#include "zombie/network/packets/EventPacket.h"
#include "zombie/network/packets/PlayerPacket.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/Recipe.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/PathFindBehavior2.h"
#include "zombie/vehicles/PolygonalMap2.h"
#include "zombie/vehicles/VehicleManager.h"
#include <algorithm>

namespace zombie {
namespace characters {


class NetworkPlayerAI : public NetworkCharacterAI {
public:
   public const std::list<EventPacket> events = std::make_unique<std::list<>>();
    IsoPlayer player;
    PathFindBehavior2 pfb2 = nullptr;
    const UpdateTimer timer = std::make_shared<UpdateTimer>();
    uint8_t lastDirection = 0;
    bool needUpdate = false;
    bool blockUpdate = false;
    bool usePathFind = false;
    float collidePointX;
    float collidePointY;
    float targetX = 0.0F;
    float targetY = 0.0F;
    int targetZ = 0;
    bool needToMovingUsingPathFinder = false;
    bool forcePathFinder = false;
    Vector2 direction = std::make_shared<Vector2>();
    Vector2 distance = std::make_shared<Vector2>();
    bool moving = false;
    uint8_t footstepSoundRadius = 0;
    int lastBooleanVariables = 0;
    float lastForwardDirection = 0.0F;
    float lastPlayerMoveDirLen = 0.0F;
    bool pressedMovement = false;
    bool pressedCancelAction = false;
    bool climbFenceOutcomeFall = false;
    long accessLevelTimestamp = 0L;
    bool wasNonPvpZone = false;
    Vector2 tempo = std::make_shared<Vector2>();
    static const int predictInterval = 1000;

    public NetworkPlayerAI(IsoGameCharacter var1) {
      super(var1);
      this.player = (IsoPlayer)var1;
      this.pfb2 = this.player.getPathFindBehavior2();
      var1.ulBeatenVehicle.Reset(200L);
      this.collidePointX = -1.0F;
      this.collidePointY = -1.0F;
      this.wasNonPvpZone = false;
   }

    void needToUpdate() {
      this.needUpdate = true;
   }

    void setBlockUpdate(bool var1) {
      this.blockUpdate = var1;
   }

    bool isNeedToUpdate() {
    int var1 = NetworkPlayerVariables.getBooleanVariables(this.player);
    uint8_t var2 = (byte)(this.player.playerMoveDir.getDirection() * 10.0F);
      if ((!this.timer.check() && var1 == this.lastBooleanVariables && this.lastDirection == var2 || this.blockUpdate) && !this.needUpdate) {
    return false;
      } else {
         this.lastDirection = var2;
         this.needUpdate = false;
    return true;
      }
   }

    void setUpdateTimer(float var1) {
      this.timer.reset(PZMath.clamp((int)var1, 200, 3800));
   }

    void setUsingCollide(PlayerPacket var1, int var2) {
      if (SystemDisabler.useNetworkCharacter) {
         this.player.networkCharacter.checkResetPlayer(var2);
      }

      var1.x = this.player.getCurrentSquare().getX();
      var1.y = this.player.getCurrentSquare().getY();
      var1.z = (byte)this.player.getCurrentSquare().getZ();
      var1.usePathFinder = false;
      var1.moveType = PredictionTypes.Thump;
   }

    void setUsingExtrapolation(PlayerPacket var1, int var2, int var3) {
    Vector2 var4 = this.player.dir.ToVector();
      if (SystemDisabler.useNetworkCharacter) {
         this.player.networkCharacter.checkResetPlayer(var2);
      }

      if (!this.player.isPlayerMoving()) {
         var1.x = this.player.x;
         var1.y = this.player.y;
         var1.z = (byte)this.player.z;
         var1.usePathFinder = false;
         var1.moveType = PredictionTypes.Static;
      } else {
    Vector2 var5 = this.tempo;
         if (SystemDisabler.useNetworkCharacter) {
    Transform var6 = this.player.networkCharacter.predict(var3, var2, this.player.x, this.player.y, var4.x, var4.y);
            var5.x = var6.position.x;
            var5.y = var6.position.y;
         } else {
            this.player.getDeferredMovement(var5);
            var5.x = this.player.x + var5.x * 0.03F * var3;
            var5.y = this.player.y + var5.y * 0.03F * var3;
         }

         if (this.player.z == this.pfb2.getTargetZ()
            && !PolygonalMap2.instance.lineClearCollide(this.player.x, this.player.y, var5.x, var5.y, (int)this.player.z, nullptr)) {
            var1.x = var5.x;
            var1.y = var5.y;
            var1.z = (byte)this.pfb2.getTargetZ();
         } else {
    Vector2 var7 = PolygonalMap2.instance.getCollidepoint(this.player.x, this.player.y, var5.x, var5.y, (int)this.player.z, nullptr, 2);
            var1.collidePointX = var7.x;
            var1.collidePointY = var7.y;
            var1.x = var7.x
               + (
                  this.player.dir != IsoDirections.N && this.player.dir != IsoDirections.S
                     ? (this.player.dir.index() >= IsoDirections.NW.index() && this.player.dir.index() <= IsoDirections.SW.index() ? -1.0F : 1.0F)
                     : 0.0F
               );
            var1.y = var7.y
               + (
                  this.player.dir != IsoDirections.W && this.player.dir != IsoDirections.E
                     ? (this.player.dir.index() >= IsoDirections.SW.index() && this.player.dir.index() <= IsoDirections.SE.index() ? 1.0F : -1.0F)
                     : 0.0F
               );
            var1.z = (byte)this.player.z;
         }

         var1.usePathFinder = false;
         var1.moveType = PredictionTypes.Moving;
      }
   }

    void setUsingPathFindState(PlayerPacket var1, int var2) {
      if (SystemDisabler.useNetworkCharacter) {
         this.player.networkCharacter.checkResetPlayer(var2);
      }

      var1.x = this.pfb2.pathNextX;
      var1.y = this.pfb2.pathNextY;
      var1.z = (byte)this.player.z;
      var1.usePathFinder = true;
      var1.moveType = PredictionTypes.PathFind;
   }

    bool set(PlayerPacket var1) {
    int var2 = (int)(GameTime.getServerTime() / 1000000L);
      var1.realx = this.player.x;
      var1.realy = this.player.y;
      var1.realz = (byte)this.player.z;
      var1.realdir = (byte)this.player.dir.index();
      var1.realt = var2;
      if (this.player.vehicle == nullptr) {
         var1.VehicleID = -1;
         var1.VehicleSeat = -1;
      } else {
         var1.VehicleID = this.player.vehicle.VehicleID;
         var1.VehicleSeat = (short)this.player.vehicle.getSeat(this.player);
      }

    bool var3 = this.timer.check();
      var1.collidePointX = -1.0F;
      var1.collidePointY = -1.0F;
      if (var3) {
         this.setUpdateTimer(600.0F);
      }

      if (this.player.getCurrentState() == CollideWithWallState.instance()) {
         this.setUsingCollide(var1, var2);
      } else if (this.pfb2.isMovingUsingPathFind()) {
         this.setUsingPathFindState(var1, var2);
      } else {
         this.setUsingExtrapolation(var1, var2, 1000);
      }

    bool var4 = this.player.playerMoveDir.getLength() < 0.01 && this.lastPlayerMoveDirLen > 0.01F;
      this.lastPlayerMoveDirLen = this.player.playerMoveDir.getLength();
      var1.booleanVariables = NetworkPlayerVariables.getBooleanVariables(this.player);
    bool var5 = this.lastBooleanVariables != var1.booleanVariables;
      this.lastBooleanVariables = var1.booleanVariables;
      var1.direction = this.player.getForwardDirection().getDirection();
    bool var6 = Math.abs(this.lastForwardDirection - var1.direction) > 0.2F;
      this.lastForwardDirection = var1.direction;
      var1.footstepSoundRadius = this.footstepSoundRadius;
      return var3 || var5 || var6 || this.player.isJustMoved() || var4;
   }

    void parse(PlayerPacket var1) {
      if (!this.player.isTeleporting()) {
         this.targetX = PZMath.roundFromEdges(var1.x);
         this.targetY = PZMath.roundFromEdges(var1.y);
         this.targetZ = var1.z;
         this.predictionType = var1.moveType;
         this.needToMovingUsingPathFinder = var1.usePathFinder;
         this.direction.set((float)Math.cos(var1.direction), (float)Math.sin(var1.direction));
         this.distance.set(var1.x - this.player.x, var1.y - this.player.y);
         if (this.usePathFind) {
            this.pfb2.pathToLocationF(var1.x, var1.y, var1.z);
            this.pfb2.walkingOnTheSpot.reset(this.player.x, this.player.y);
         }

    BaseVehicle var2 = VehicleManager.instance.getVehicleByID(var1.VehicleID);
         NetworkPlayerVariables.setBooleanVariables(this.player, var1.booleanVariables);
         this.player.setbSeenThisFrame(false);
         this.player.setbCouldBeSeenThisFrame(false);
         this.player.TimeSinceLastNetData = 0;
         this.player.ensureOnTile();
         this.player.realx = var1.realx;
         this.player.realy = var1.realy;
         this.player.realz = var1.realz;
         this.player.realdir = IsoDirections.fromIndex(var1.realdir);
         if (GameServer.bServer) {
            this.player.setForwardDirection(this.direction);
         }

         this.collidePointX = var1.collidePointX;
         this.collidePointY = var1.collidePointY;
         var1.variables.apply(this.player);
         this.footstepSoundRadius = var1.footstepSoundRadius;
         if (this.player.getVehicle() == nullptr) {
            if (var2 != nullptr) {
               if (var1.VehicleSeat >= 0 && var1.VehicleSeat < var2.getMaxPassengers()) {
    IsoGameCharacter var3 = var2.getCharacter(var1.VehicleSeat);
                  if (var3 == nullptr) {
                     if (GameServer.bDebug) {
                        DebugLog.log(this.player.getUsername() + " got in vehicle " + var2.VehicleID + " seat " + var1.VehicleSeat);
                     }

                     var2.enterRSync(var1.VehicleSeat, this.player, var2);
                  } else if (var3 != this.player) {
                     DebugLog.log(this.player.getUsername() + " got in same seat as " + ((IsoPlayer)var3).getUsername());
                     this.player.sendObjectChange("exitVehicle");
                  }
               } else {
                  DebugLog.log(this.player.getUsername() + " invalid seat vehicle " + var2.VehicleID + " seat " + var1.VehicleSeat);
               }
            }
         } else if (var2 != nullptr) {
            if (var2 == this.player.getVehicle() && this.player.getVehicle().getSeat(this.player) != -1) {
    IsoGameCharacter var4 = var2.getCharacter(var1.VehicleSeat);
               if (var4 == nullptr) {
                  if (var2.getSeat(this.player) != var1.VehicleSeat) {
                     var2.switchSeat(this.player, var1.VehicleSeat);
                  }
               } else if (var4 != this.player) {
                  DebugLog.log(this.player.getUsername() + " switched to same seat as " + ((IsoPlayer)var4).getUsername());
                  this.player.sendObjectChange("exitVehicle");
               }
            } else {
               DebugLog.log(
                  this.player.getUsername()
                     + " vehicle/seat remote "
                     + var2.VehicleID
                     + "/"
                     + var1.VehicleSeat
                     + " local "
                     + this.player.getVehicle().VehicleID
                     + "/"
                     + this.player.getVehicle().getSeat(this.player)
               );
               this.player.sendObjectChange("exitVehicle");
            }
         } else {
            this.player.getVehicle().exitRSync(this.player);
            this.player.setVehicle(nullptr);
         }

         this.setPressedMovement(false);
         this.setPressedCancelAction(false);
      }
   }

    bool isPressedMovement() {
      return this.pressedMovement;
   }

    void setPressedMovement(bool var1) {
    bool var2 = !this.pressedMovement && var1;
      this.pressedMovement = var1;
      if (this.player.isLocal() && var2) {
         GameClient.sendEvent(this.player, "Update");
      }
   }

    bool isPressedCancelAction() {
      return this.pressedCancelAction;
   }

    void setPressedCancelAction(bool var1) {
    bool var2 = !this.pressedCancelAction && var1;
      this.pressedCancelAction = var1;
      if (this.player.isLocal() && var2) {
         GameClient.sendEvent(this.player, "Update");
      }
   }

    void setCheckAccessLevelDelay(long var1) {
      this.accessLevelTimestamp = System.currentTimeMillis() + var1;
   }

    bool doCheckAccessLevel() {
      if (this.accessLevelTimestamp == 0L) {
    return true;
      } else if (System.currentTimeMillis() > this.accessLevelTimestamp) {
         this.accessLevelTimestamp = 0L;
    return true;
      } else {
    return false;
      }
   }

    void update() {
      if (DebugOptions.instance.MultiplayerHotKey.getValue() && GameKeyboard.isKeyPressed(45) && GameKeyboard.isKeyDown(56)) {
         DebugLog.Multiplayer.noise("multiplayer hot key pressed");
    std::vector var1 = ScriptManager.instance.getAllRecipes();
    Recipe var2 = (Recipe)var1.get(Rand.Next(var1.size()));
         var2.TimeToMake = Rand.Next(32767);
         DebugLog.Multiplayer.debugln("Failed recipe \"%s\"", var2.getOriginalname());
      }
   }

    bool isDismantleAllowed() {
    return true;
   }
}
} // namespace characters
} // namespace zombie
