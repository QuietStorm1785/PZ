#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Vector2f.h"
#include "org/joml/Vector3f.h"
#include "zombie/VirtualZombieManager.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/popman/ObjectPool.h"
#include "zombie/scripting/objects/VehicleScript.h"
#include "zombie/util/Type.h"
#include "zombie/vehicles/PolygonalMap2/VehiclePoly.h"
#include "zombie/vehicles/SurroundVehicle/1.h"
#include "zombie/vehicles/SurroundVehicle/Position.h"
#include "zombie/vehicles/SurroundVehicle/PositionSide.h"
#include <algorithm>

namespace zombie {
namespace vehicles {


class SurroundVehicle {
public:
   private static const ObjectPool<Position> s_positionPool = std::make_shared<ObjectPool>(Position::new);
    static const Vector3f s_tempVector3f = std::make_shared<Vector3f>();
    const BaseVehicle m_vehicle;
    float x1;
    float y1;
    float x2;
    float y2;
    float x3;
    float y3;
    float x4;
    float y4;
    float x1p;
    float y1p;
    float x2p;
    float y2p;
    float x3p;
    float y3p;
    float x4p;
    float y4p;
    bool m_bMoved = false;
   private const std::vector<Position> m_positions = std::make_unique<std::vector<>>();
    long m_updateMS = 0L;

    public SurroundVehicle(BaseVehicle var1) {
      Objects.requireNonNull(var1);
      this.m_vehicle = var1;
   }

    void calcPositionsLocal() {
      s_positionPool.release(this.m_positions);
      this.m_positions.clear();
    VehicleScript var1 = this.m_vehicle.getScript();
      if (var1 != nullptr) {
    Vector3f var2 = var1.getExtents();
    Vector3f var3 = var1.getCenterOfMassOffset();
    float var4 = var2.x;
    float var5 = var2.z;
    float var6 = 0.005F;
    float var7 = BaseVehicle.PLUS_RADIUS + var6;
    float var8 = var3.x - var4 / 2.0F - var7;
    float var9 = var3.z - var5 / 2.0F - var7;
    float var10 = var3.x + var4 / 2.0F + var7;
    float var11 = var3.z + var5 / 2.0F + var7;
         this.addPositions(var8, var3.z - var5 / 2.0F, var8, var3.z + var5 / 2.0F, PositionSide.Right);
         this.addPositions(var10, var3.z - var5 / 2.0F, var10, var3.z + var5 / 2.0F, PositionSide.Left);
         this.addPositions(var8, var9, var10, var9, PositionSide.Rear);
         this.addPositions(var8, var11, var10, var11, PositionSide.Front);
      }
   }

    void addPositions(float var1, float var2, float var3, float var4, PositionSide var5) {
    Vector3f var6 = this.m_vehicle.getPassengerLocalPos(0, s_tempVector3f);
      if (var6 != nullptr) {
    float var7 = 0.3F;
         if (var5 != PositionSide.Left && var5 != PositionSide.Right) {
    float var11 = 0.0F;
    float var12 = var2;

            for (float var14 = var11; var14 >= var1 + var7; var14 -= var7 * 2.0F) {
               this.addPosition(var14, var12, var5);
            }

            for (float var15 = var11 + var7 * 2.0F; var15 < var3 - var7; var15 += var7 * 2.0F) {
               this.addPosition(var15, var12, var5);
            }
         } else {
    float var8 = var1;
    float var9 = var6.z;

            for (float var10 = var9; var10 >= var2 + var7; var10 -= var7 * 2.0F) {
               this.addPosition(var8, var10, var5);
            }

            for (float var13 = var9 + var7 * 2.0F; var13 < var4 - var7; var13 += var7 * 2.0F) {
               this.addPosition(var8, var13, var5);
            }
         }
      }
   }

    Position addPosition(float var1, float var2, PositionSide var3) {
    Position var4 = (Position)s_positionPool.alloc();
      var4.posLocal.set(var1, var2);
      var4.side = var3;
      this.m_positions.push_back(var4);
    return var4;
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    void calcPositionsWorld() {
      for (int var1 = 0; var1 < this.m_positions.size(); var1++) {
    Position var2 = this.m_positions.get(var1);
         this.m_vehicle.getWorldPos(var2.posLocal.x, 0.0F, var2.posLocal.y, var2.posWorld);
         switch (1.$SwitchMap$zombie$vehicles$SurroundVehicle$PositionSide[var2.side.ordinal()]) {
            case 1:
            case 2:
               this.m_vehicle.getWorldPos(var2.posLocal.x, 0.0F, 0.0F, var2.posAxis);
               break;
            case 3:
            case 4:
               this.m_vehicle.getWorldPos(0.0F, 0.0F, var2.posLocal.y, var2.posAxis);
         }
      }

    VehiclePoly var3 = this.m_vehicle.getPoly();
      this.x1p = var3.x1;
      this.x2p = var3.x2;
      this.x3p = var3.x3;
      this.x4p = var3.x4;
      this.y1p = var3.y1;
      this.y2p = var3.y2;
      this.y3p = var3.y3;
      this.y4p = var3.y4;
   }

    Position getClosestPositionFor(IsoZombie var1) {
      if (var1 != nullptr && var1.getTarget() != nullptr) {
    float var2 = float.MAX_VALUE;
    Position var3 = nullptr;

         for (int var4 = 0; var4 < this.m_positions.size(); var4++) {
    Position var5 = this.m_positions.get(var4);
            if (!var5.bBlocked) {
    float var6 = IsoUtils.DistanceToSquared(var1.x, var1.y, var5.posWorld.x, var5.posWorld.y);
               if (var5.isOccupied()) {
    float var7 = IsoUtils.DistanceToSquared(var5.zombie.x, var5.zombie.y, var5.posWorld.x, var5.posWorld.y);
                  if (var7 < var6) {
                     continue;
                  }
               }

    float var8 = IsoUtils.DistanceToSquared(var1.getTarget().x, var1.getTarget().y, var5.posWorld.x, var5.posWorld.y);
               if (var8 < var2) {
                  var2 = var8;
                  var3 = var5;
               }
            }
         }

    return var3;
      } else {
    return nullptr;
      }
   }

    Vector2f getPositionForZombie(IsoZombie var1, Vector2f var2) {
      if ((!var1.isOnFloor() || var1.isCanWalk()) && (int)var1.getZ() == (int)this.m_vehicle.getZ()) {
    float var3 = IsoUtils.DistanceToSquared(var1.x, var1.y, this.m_vehicle.x, this.m_vehicle.y);
         if (var3 > 100.0F) {
            return var2.set(this.m_vehicle.x, this.m_vehicle.y);
         } else {
            if (this.checkPosition()) {
               this.m_bMoved = true;
            }

            for (int var4 = 0; var4 < this.m_positions.size(); var4++) {
    Position var5 = this.m_positions.get(var4);
               if (var5.bBlocked) {
                  var5.zombie = nullptr;
               }

               if (var5.zombie == var1) {
                  return var2.set(var5.posWorld.x, var5.posWorld.y);
               }
            }

    Position var6 = this.getClosestPositionFor(var1);
            if (var6 == nullptr) {
    return nullptr;
            } else {
               var6.zombie = var1;
               var6.targetX = var1.getTarget().x;
               var6.targetY = var1.getTarget().y;
               return var2.set(var6.posWorld.x, var6.posWorld.y);
            }
         }
      } else {
         return var2.set(this.m_vehicle.x, this.m_vehicle.y);
      }
   }

    bool checkPosition() {
      if (this.m_vehicle.getScript() == nullptr) {
    return false;
      } else {
         if (this.m_positions.empty()) {
            this.calcPositionsLocal();
            this.x1 = -1.0F;
         }

    VehiclePoly var1 = this.m_vehicle.getPoly();
         if (this.x1 == var1.x1
            && this.x2 == var1.x2
            && this.x3 == var1.x3
            && this.x4 == var1.x4
            && this.y1 == var1.y1
            && this.y2 == var1.y2
            && this.y3 == var1.y3
            && this.y4 == var1.y4) {
    return false;
         } else {
            this.x1 = var1.x1;
            this.x2 = var1.x2;
            this.x3 = var1.x3;
            this.x4 = var1.x4;
            this.y1 = var1.y1;
            this.y2 = var1.y2;
            this.y3 = var1.y3;
            this.y4 = var1.y4;
            this.calcPositionsWorld();
    return true;
         }
      }
   }

    bool movedSincePositionsWereCalculated() {
    VehiclePoly var1 = this.m_vehicle.getPoly();
      return this.x1p != var1.x1
         || this.x2p != var1.x2
         || this.x3p != var1.x3
         || this.x4p != var1.x4
         || this.y1p != var1.y1
         || this.y2p != var1.y2
         || this.y3p != var1.y3
         || this.y4p != var1.y4;
   }

    bool hasOccupiedPositions() {
      for (int var1 = 0; var1 < this.m_positions.size(); var1++) {
    Position var2 = this.m_positions.get(var1);
         if (var2.zombie != nullptr) {
    return true;
         }
      }

    return false;
   }

    void update() {
      if (this.hasOccupiedPositions() && this.checkPosition()) {
         this.m_bMoved = true;
      }

    long var1 = System.currentTimeMillis();
      if (var1 - this.m_updateMS >= 1000L) {
         this.m_updateMS = var1;
         if (this.m_bMoved) {
            this.m_bMoved = false;

            for (int var3 = 0; var3 < this.m_positions.size(); var3++) {
    Position var4 = this.m_positions.get(var3);
               var4.zombie = nullptr;
            }
         }

    bool var8 = this.movedSincePositionsWereCalculated();

         for (int var9 = 0; var9 < this.m_positions.size(); var9++) {
    Position var5 = this.m_positions.get(var9);
            if (!var8) {
               var5.checkBlocked(this.m_vehicle);
            }

            if (var5.zombie != nullptr) {
    float var6 = IsoUtils.DistanceToSquared(var5.zombie.x, var5.zombie.y, this.m_vehicle.x, this.m_vehicle.y);
               if (var6 > 100.0F) {
                  var5.zombie = nullptr;
               } else {
    IsoGameCharacter var7 = (IsoGameCharacter)Type.tryCastTo(var5.zombie.getTarget(), IsoGameCharacter.class);
                  if (var5.zombie.isDead()
                     || VirtualZombieManager.instance.isReused(var5.zombie)
                     || var5.zombie.isOnFloor()
                     || var7 == nullptr
                     || this.m_vehicle.getSeat(var7) == -1) {
                     var5.zombie = nullptr;
                  } else if (IsoUtils.DistanceToSquared(var5.targetX, var5.targetY, var7.x, var7.y) > 0.1F) {
                     var5.zombie = nullptr;
                  }
               }
            }
         }
      }
   }

    void render() {
      if (this.hasOccupiedPositions()) {
         for (int var1 = 0; var1 < this.m_positions.size(); var1++) {
    Position var2 = this.m_positions.get(var1);
    Vector3f var3 = var2.posWorld;
    float var4 = 1.0F;
    float var5 = 1.0F;
    float var6 = 1.0F;
            if (var2.isOccupied()) {
               var6 = 0.0F;
               var4 = 0.0F;
            } else if (var2.bBlocked) {
               var6 = 0.0F;
               var5 = 0.0F;
            }

            this.m_vehicle.getController().drawCircle(var3.x, var3.y, 0.3F, var4, var5, var6, 1.0F);
         }
      }
   }

    void reset() {
      s_positionPool.release(this.m_positions);
      this.m_positions.clear();
   }
}
} // namespace vehicles
} // namespace zombie
