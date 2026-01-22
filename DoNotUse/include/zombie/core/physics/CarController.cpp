#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Vector3f.h"
#include "zombie/GameTime.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/Moodles/MoodleType.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/physics/CarController/1.h"
#include "zombie/core/physics/CarController/BulletVariables.h"
#include "zombie/core/physics/CarController/ClientControls.h"
#include "zombie/core/physics/CarController/ControlState.h"
#include "zombie/core/physics/CarController/GearInfo.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/debug/LineDrawer.h"
#include "zombie/input/GameKeyboard.h"
#include "zombie/input/JoypadManager.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/Vector2.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/scripting/objects/VehicleScript.h"
#include "zombie/scripting/objects/VehicleScript/Wheel.h"
#include "zombie/ui/UIManager.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/BaseVehicle/Authorization.h"
#include "zombie/vehicles/BaseVehicle/engineStateTypes.h"
#include "zombie/vehicles/EngineRPMData.h"
#include "zombie/vehicles/PolygonalMap2/VehiclePoly.h"
#include "zombie/vehicles/TransmissionNumber.h"

namespace zombie {
namespace core {
namespace physics {


class CarController {
public:
    const BaseVehicle vehicleObject;
    float clientForce = 0.0F;
    float EngineForce = 0.0F;
    float BrakingForce = 0.0F;
    float VehicleSteering = 0.0F;
    bool isGas = false;
    bool isGasR = false;
    bool isBreak = false;
    float atRestTimer = -1.0F;
    float regulatorTimer = 0.0F;
    bool isEnable = false;
    const Transform tempXfrm = std::make_shared<Transform>();
    const Vector2 tempVec2 = std::make_shared<Vector2>();
    const Vector3f tempVec3f = std::make_shared<Vector3f>();
    const Vector3f tempVec3f_2 = std::make_shared<Vector3f>();
    const Vector3f tempVec3f_3 = std::make_shared<Vector3f>();
    static const Vector3f _UNIT_Y = std::make_shared<Vector3f>(0.0F, 1.0F, 0.0F);
    bool acceleratorOn = false;
    bool brakeOn = false;
    float speed = 0.0F;
   public static GearInfo[] gears = new GearInfo[3];
    const ClientControls clientControls = std::make_shared<ClientControls>();
    bool engineStartingFromKeyboard;
    static const BulletVariables bulletVariables = std::make_shared<BulletVariables>();
    float drunkDelayCommandTimer = 0.0F;
    bool wasBreaking = false;
    bool wasGas = false;
    bool wasGasR = false;
    bool wasSteering = false;

    public CarController(BaseVehicle var1) {
      this.vehicleObject = var1;
      this.engineStartingFromKeyboard = false;
    VehicleScript var2 = var1.getScript();
    float var3 = var1.savedPhysicsZ;
      if (float.isNaN(var3)) {
    float var4 = Math.max((float)((int)var1.z), 0.0F);
         if (var2.getWheelCount() > 0) {
    Vector3f var5 = var2.getModelOffset();
            var4 += var5.y();
            var4 += var2.getWheel(0).getOffset().y() - var2.getWheel(0).radius;
         }

    float var7 = var2.getCenterOfMassOffset().y() - var2.getExtents().y() / 2.0F;
         var3 = 0.0F - Math.min(var4, var7);
         var1.jniTransform.origin.y = var3;
      }

      if (!GameServer.bServer) {
         Bullet.addVehicle(var1.VehicleID, var1.x, var1.y, var3, var1.savedRot.x, var1.savedRot.y, var1.savedRot.z, var1.savedRot.w, var2.getFullName());
         Bullet.setVehicleStatic(var1, var1.isNetPlayerAuthorization(Authorization.Remote));
         DebugLog.Vehicle
            .debugln(
               "Vehicle vid=%d type=%s has been added at (%f;%f;%f) auth=%s",
               var1.VehicleID,
               var2.getFullName(),
               var1.x,
               var1.y,
               var3,
               var1.getAuthorizationDescription()
            );
      }
   }

    GearInfo findGear(float var1) {
      for (int var2 = 0; var2 < gears.length; var2++) {
         if (var1 >= gears[var2].minSpeed && var1 < gears[var2].maxSpeed) {
            return gears[var2];
         }
      }

    return nullptr;
   }

    void accelerator(bool var1) {
      this.acceleratorOn = var1;
   }

    void brake(bool var1) {
      this.brakeOn = var1;
   }

    ClientControls getClientControls() {
      return this.clientControls;
   }

    void update() {
      if (this.vehicleObject.getVehicleTowedBy() == nullptr) {
    VehicleScript var1 = this.vehicleObject.getScript();
         this.speed = this.vehicleObject.getCurrentSpeedKmHour();
    bool var2 = this.vehicleObject.getDriver() != nullptr && this.vehicleObject.getDriver().getMoodles().getMoodleLevel(MoodleType.Drunk) > 1;
    float var3 = 0.0F;
    Vector3f var4 = this.vehicleObject.getLinearVelocity(this.tempVec3f_2);
         var4.y = 0.0F;
         if (var4.length() > 0.5) {
            var4.normalize();
    Vector3f var5 = this.tempVec3f;
            this.vehicleObject.getForwardVector(var5);
            var3 = var4.dot(var5);
         }

    float var15 = 1.0F;
         if (GameClient.bClient) {
    float var6 = this.vehicleObject.jniSpeed / Math.min(120.0F, (float)ServerOptions.instance.SpeedLimit.getValue());
            var6 *= var6;
            var15 = GameTime.getInstance().Lerp(1.0F, BaseVehicle.getFakeSpeedModifier(), var6);
         }

    float var17 = this.vehicleObject.getCurrentSpeedKmHour() * var15;
         this.isGas = false;
         this.isGasR = false;
         this.isBreak = false;
         if (this.clientControls.forward) {
            if (var3 < 0.0F) {
               this.isBreak = true;
            }

            if (var3 >= 0.0F) {
               this.isGas = true;
            }

            this.isGasR = false;
         }

         if (this.clientControls.backward) {
            if (var3 > 0.0F) {
               this.isBreak = true;
            }

            if (var3 <= 0.0F) {
               this.isGasR = true;
            }

            this.isGas = false;
         }

         if (this.clientControls.brake) {
            this.isBreak = true;
            this.isGas = false;
            this.isGasR = false;
         }

         if (this.clientControls.forward && this.clientControls.backward) {
            this.isBreak = true;
            this.isGas = false;
            this.isGasR = false;
         }

         if (var2 && this.vehicleObject.engineState != engineStateTypes.Idle) {
            if (this.isBreak && !this.wasBreaking) {
               this.isBreak = this.delayCommandWhileDrunk(this.isBreak);
            }

            if (this.isGas && !this.wasGas) {
               this.isGas = this.delayCommandWhileDrunk(this.isGas);
            }

            if (this.isGasR && !this.wasGasR) {
               this.isGasR = this.delayCommandWhileDrunk(this.isGas);
            }

            if (this.clientControls.steering != 0.0F && !this.wasSteering) {
               this.clientControls.steering = this.delayCommandWhileDrunk(this.clientControls.steering);
            }
         }

         this.updateRegulator();
         this.wasBreaking = this.isBreak;
         this.wasGas = this.isGas;
         this.wasGasR = this.isGasR;
         this.wasSteering = this.clientControls.steering != 0.0F;
         if (!this.isGasR && this.vehicleObject.isInvalidChunkAhead()) {
            this.isBreak = true;
            this.isGas = false;
            this.isGasR = false;
         } else if (!this.isGas && this.vehicleObject.isInvalidChunkBehind()) {
            this.isBreak = true;
            this.isGas = false;
            this.isGasR = false;
         }

         if (this.clientControls.shift) {
            this.isGas = false;
            this.isBreak = false;
            this.isGasR = false;
            this.clientControls.wasUsingParkingBrakes = false;
         }

    float var7 = this.vehicleObject.throttle;
         if (!this.isGas && !this.isGasR) {
            var7 -= GameTime.getInstance().getMultiplier() / 30.0F;
         } else {
            var7 += GameTime.getInstance().getMultiplier() / 30.0F;
         }

         if (var7 < 0.0F) {
            var7 = 0.0F;
         }

         if (var7 > 1.0F) {
            var7 = 1.0F;
         }

         if (this.vehicleObject.isRegulator() && !this.isGas && !this.isGasR) {
            var7 = 0.5F;
            if (var17 < this.vehicleObject.getRegulatorSpeed()) {
               this.isGas = true;
            }
         }

         this.vehicleObject.throttle = var7;
    float var8 = GameTime.getInstance().getMultiplier() / 0.8F;
    ControlState var9 = ControlState.NoControl;
         if (this.isBreak) {
            var9 = ControlState.Braking;
         } else if (this.isGas && !this.isGasR) {
            var9 = ControlState.Forward;
         } else if (!this.isGas && this.isGasR) {
            var9 = ControlState.Reverse;
         }

         if (var9 != ControlState.NoControl) {
            UIManager.speedControls.SetCurrentGameSpeed(1);
         }

         if (var9 == ControlState.NoControl) {
            this.control_NoControl();
         }

         if (var9 == ControlState.Reverse) {
            this.control_Reverse(var17);
         }

         if (var9 == ControlState.Forward) {
            this.control_ForwardNew(var17);
         }

         this.updateBackSignal();
         if (var9 == ControlState.Braking) {
            this.control_Braking();
         }

         this.updateBrakeLights();
    BaseVehicle var10 = this.vehicleObject.getVehicleTowedBy();
         if (var10 != nullptr && var10.getDriver() == nullptr && this.vehicleObject.getDriver() != nullptr && !GameClient.bClient) {
            this.vehicleObject.addPointConstraint(nullptr, var10, this.vehicleObject.getTowAttachmentSelf(), var10.getTowAttachmentSelf());
         }

         this.updateRammingSound(var17);
         if (Math.abs(this.clientControls.steering) > 0.1F) {
    float var11 = 1.0F - this.speed / this.vehicleObject.getMaxSpeed();
            if (var11 < 0.1F) {
               var11 = 0.1F;
            }

            this.VehicleSteering = this.VehicleSteering - (this.clientControls.steering + this.VehicleSteering) * 0.06F * var8 * var11;
         } else if (Math.abs(this.VehicleSteering) <= 0.04) {
            this.VehicleSteering = 0.0F;
         } else if (this.VehicleSteering > 0.0F) {
            this.VehicleSteering -= 0.04F * var8;
            this.VehicleSteering = Math.max(this.VehicleSteering, 0.0F);
         } else {
            this.VehicleSteering += 0.04F * var8;
            this.VehicleSteering = Math.min(this.VehicleSteering, 0.0F);
         }

    float var19 = var1.getSteeringClamp(this.speed);
         this.VehicleSteering = PZMath.clamp(this.VehicleSteering, -var19, var19);
    BulletVariables var12 = bulletVariables.set(this.vehicleObject, this.EngineForce, this.BrakingForce, this.VehicleSteering);
         this.checkTire(var12);
         this.EngineForce = var12.engineForce;
         this.BrakingForce = var12.brakingForce;
         this.VehicleSteering = var12.vehicleSteering;
         if (this.vehicleObject.isDoingOffroad()) {
    int var13 = this.vehicleObject.getTransmissionNumber();
            if (var13 <= 0) {
               var13 = 1;
            }

            this.EngineForce = (float)(this.EngineForce / (var13 * 1.5));
         }

         this.vehicleObject.setCurrentSteering(this.VehicleSteering);
         this.vehicleObject.setBraking(this.isBreak);
         if (!GameServer.bServer) {
            this.checkShouldBeActive();
            Bullet.controlVehicle(this.vehicleObject.VehicleID, this.EngineForce, this.BrakingForce, this.VehicleSteering);
            if (this.EngineForce > 0.0F && this.vehicleObject.engineState == engineStateTypes.Idle && !this.engineStartingFromKeyboard) {
               this.engineStartingFromKeyboard = true;
               if (GameClient.bClient) {
                  bool var14 = this.vehicleObject.getDriver().getInventory().haveThisKeyId(this.vehicleObject.getKeyId()) != nullptr
                     ? bool.TRUE
                     : bool.FALSE;
                  GameClient.instance.sendClientCommandV((IsoPlayer)this.vehicleObject.getDriver(), "vehicle", "startEngine", new Object[]{"haveKey", var14});
               } else {
                  this.vehicleObject.tryStartEngine();
               }
            }

            if (this.engineStartingFromKeyboard && this.EngineForce == 0.0F) {
               this.engineStartingFromKeyboard = false;
            }
         }

         if (this.vehicleObject.engineState != engineStateTypes.Running) {
            this.acceleratorOn = false;
            if (!GameServer.bServer && this.vehicleObject.jniSpeed > 5.0F && this.vehicleObject.getScript().getWheelCount() > 0) {
               Bullet.controlVehicle(this.vehicleObject.VehicleID, 0.0F, this.BrakingForce, this.VehicleSteering);
            } else {
               this.park();
            }
         }
      }
   }

    void updateTrailer() {
    BaseVehicle var1 = this.vehicleObject.getVehicleTowedBy();
      if (var1 != nullptr) {
         if (GameServer.bServer) {
            if (var1.getDriver() == nullptr && this.vehicleObject.getDriver() != nullptr) {
               this.vehicleObject.addPointConstraint(nullptr, var1, this.vehicleObject.getTowAttachmentSelf(), var1.getTowAttachmentSelf());
            }
         } else {
            this.speed = this.vehicleObject.getCurrentSpeedKmHour();
            this.isGas = false;
            this.isGasR = false;
            this.isBreak = false;
            this.wasGas = false;
            this.wasGasR = false;
            this.wasBreaking = false;
            this.vehicleObject.throttle = 0.0F;
            if (var1.getDriver() == nullptr && this.vehicleObject.getDriver() != nullptr && !GameClient.bClient) {
               this.vehicleObject.addPointConstraint(nullptr, var1, this.vehicleObject.getTowAttachmentSelf(), var1.getTowAttachmentSelf());
            } else {
               this.checkShouldBeActive();
               this.EngineForce = 0.0F;
               this.BrakingForce = 0.0F;
               this.VehicleSteering = 0.0F;
               if (!this.vehicleObject.getScriptName().contains("Trailer")) {
                  this.BrakingForce = 10.0F;
               }

               Bullet.controlVehicle(this.vehicleObject.VehicleID, this.EngineForce, this.BrakingForce, this.VehicleSteering);
            }
         }
      }
   }

    void updateRegulator() {
      if (this.regulatorTimer > 0.0F) {
         this.regulatorTimer = this.regulatorTimer - GameTime.getInstance().getMultiplier() / 1.6F;
      }

      if (this.clientControls.shift) {
         if (this.clientControls.forward && this.regulatorTimer <= 0.0F) {
            if (this.vehicleObject.getRegulatorSpeed() < this.vehicleObject.getMaxSpeed() + 20.0F
               && (!this.vehicleObject.isRegulator() && this.vehicleObject.getRegulatorSpeed() == 0.0F || this.vehicleObject.isRegulator())) {
               if (this.vehicleObject.getRegulatorSpeed() == 0.0F && this.vehicleObject.getCurrentSpeedForRegulator() != this.vehicleObject.getRegulatorSpeed()
                  )
                {
                  this.vehicleObject.setRegulatorSpeed(this.vehicleObject.getCurrentSpeedForRegulator());
               } else {
                  this.vehicleObject.setRegulatorSpeed(this.vehicleObject.getRegulatorSpeed() + 5.0F);
               }
            }

            this.vehicleObject.setRegulator(true);
            this.regulatorTimer = 20.0F;
         } else if (this.clientControls.backward && this.regulatorTimer <= 0.0F) {
            this.regulatorTimer = 20.0F;
            if (this.vehicleObject.getRegulatorSpeed() >= 5.0F
               && (!this.vehicleObject.isRegulator() && this.vehicleObject.getRegulatorSpeed() == 0.0F || this.vehicleObject.isRegulator())) {
               this.vehicleObject.setRegulatorSpeed(this.vehicleObject.getRegulatorSpeed() - 5.0F);
            }

            this.vehicleObject.setRegulator(true);
            if (this.vehicleObject.getRegulatorSpeed() <= 0.0F) {
               this.vehicleObject.setRegulatorSpeed(0.0F);
               this.vehicleObject.setRegulator(false);
            }
         }
      } else if (this.isGasR || this.isBreak) {
         this.vehicleObject.setRegulator(false);
      }
   }

    void control_NoControl() {
    float var1 = GameTime.getInstance().getMultiplier() / 0.8F;
      if (!this.vehicleObject.isEngineRunning()) {
         if (this.vehicleObject.engineSpeed > 0.0) {
            this.vehicleObject.engineSpeed = Math.max(this.vehicleObject.engineSpeed - 50.0F * var1, 0.0);
         }
      } else if (this.vehicleObject.engineSpeed > this.vehicleObject.getScript().getEngineIdleSpeed()) {
         if (!this.vehicleObject.isRegulator()) {
            this.vehicleObject.engineSpeed -= 20.0F * var1;
         }
      } else {
         this.vehicleObject.engineSpeed += 20.0F * var1;
      }

      if (!this.vehicleObject.isRegulator()) {
         this.vehicleObject.transmissionNumber = TransmissionNumber.N;
      }

      this.EngineForce = 0.0F;
      if (this.vehicleObject.engineSpeed > 1000.0) {
         this.BrakingForce = 15.0F;
      } else {
         this.BrakingForce = 10.0F;
      }
   }

    void control_Braking() {
    float var1 = GameTime.getInstance().getMultiplier() / 0.8F;
      if (this.vehicleObject.engineSpeed > this.vehicleObject.getScript().getEngineIdleSpeed()) {
         this.vehicleObject.engineSpeed = this.vehicleObject.engineSpeed - Rand.Next(10, 30) * var1;
      } else {
         this.vehicleObject.engineSpeed = this.vehicleObject.engineSpeed + Rand.Next(20) * var1;
      }

      this.vehicleObject.transmissionNumber = TransmissionNumber.N;
      this.EngineForce = 0.0F;
      this.BrakingForce = this.vehicleObject.getBrakingForce();
      if (this.clientControls.brake) {
         this.BrakingForce *= 13.0F;
      }
   }

    void control_Forward(float var1) {
    float var2 = GameTime.getInstance().getMultiplier() / 0.8F;
    IsoGameCharacter var3 = this.vehicleObject.getDriver();
    bool var4 = var3 != nullptr && var3.Traits.SpeedDemon.isSet();
    bool var5 = var3 != nullptr && var3.Traits.SundayDriver.isSet();
    int var6 = this.vehicleObject.getScript().gearRatioCount;
    float var7 = 0.0F;
      if (this.vehicleObject.transmissionNumber == TransmissionNumber.N) {
         this.vehicleObject.transmissionNumber = TransmissionNumber.Speed1;
    bool var8 = false;

         while (true) {
            if (this.vehicleObject.transmissionNumber == TransmissionNumber.Speed1) {
               var7 = 3000.0F * var1 / 30.0F;
            }

            if (this.vehicleObject.transmissionNumber == TransmissionNumber.Speed2) {
               var7 = 3000.0F * var1 / 40.0F;
            }

            if (this.vehicleObject.transmissionNumber == TransmissionNumber.Speed3) {
               var7 = 3000.0F * var1 / 60.0F;
            }

            if (this.vehicleObject.transmissionNumber == TransmissionNumber.Speed4) {
               var7 = 3000.0F * var1 / 85.0F;
            }

            if (this.vehicleObject.transmissionNumber == TransmissionNumber.Speed5) {
               var7 = 3000.0F * var1 / 105.0F;
            }

            if (this.vehicleObject.transmissionNumber == TransmissionNumber.Speed6) {
               var7 = 3000.0F * var1 / 130.0F;
            }

            if (this.vehicleObject.transmissionNumber == TransmissionNumber.Speed7) {
               var7 = 3000.0F * var1 / 160.0F;
            }

            if (this.vehicleObject.transmissionNumber == TransmissionNumber.Speed8) {
               var7 = 3000.0F * var1 / 200.0F;
            }

            if (var4) {
               if (var7 > 6000.0F) {
                  this.vehicleObject.changeTransmission(this.vehicleObject.transmissionNumber.getNext(var6));
                  var8 = true;
               }
            } else if (var7 > 3000.0F) {
               this.vehicleObject.changeTransmission(this.vehicleObject.transmissionNumber.getNext(var6));
               var8 = true;
            }

            if (!var8 || this.vehicleObject.transmissionNumber.getIndex() >= var6) {
               break;
            }

            var8 = false;
         }
      }

      if (var4) {
         if (this.vehicleObject.engineSpeed > 6000.0 && this.vehicleObject.transmissionChangeTime.Check()) {
            this.vehicleObject.changeTransmission(this.vehicleObject.transmissionNumber.getNext(var6));
         }
      } else if (this.vehicleObject.engineSpeed > 3000.0 && this.vehicleObject.transmissionChangeTime.Check()) {
         this.vehicleObject.changeTransmission(this.vehicleObject.transmissionNumber.getNext(var6));
      }

      if (this.vehicleObject.transmissionNumber == TransmissionNumber.Speed1) {
         var7 = 3000.0F * var1 / 30.0F;
      }

      if (this.vehicleObject.transmissionNumber == TransmissionNumber.Speed2) {
         var7 = 3000.0F * var1 / 40.0F;
      }

      if (this.vehicleObject.transmissionNumber == TransmissionNumber.Speed3) {
         var7 = 3000.0F * var1 / 60.0F;
      }

      if (this.vehicleObject.transmissionNumber == TransmissionNumber.Speed4) {
         var7 = 3000.0F * var1 / 85.0F;
      }

      if (this.vehicleObject.transmissionNumber == TransmissionNumber.Speed5) {
         var7 = 3000.0F * var1 / 105.0F;
      }

      if (this.vehicleObject.transmissionNumber == TransmissionNumber.Speed6) {
         var7 = 3000.0F * var1 / 130.0F;
      }

      if (this.vehicleObject.transmissionNumber == TransmissionNumber.Speed7) {
         var7 = 3000.0F * var1 / 160.0F;
      }

      if (this.vehicleObject.transmissionNumber == TransmissionNumber.Speed8) {
         var7 = 3000.0F * var1 / 200.0F;
      }

      this.vehicleObject.engineSpeed = this.vehicleObject.engineSpeed - Math.min(0.5 * (this.vehicleObject.engineSpeed - var7), 100.0) * var2;
      if (var4) {
         if (var1 < 50.0F) {
            this.vehicleObject.engineSpeed = this.vehicleObject.engineSpeed
               - Math.min(0.06 * (this.vehicleObject.engineSpeed - 7000.0), (double)(30.0F - var1)) * var2;
         }
      } else if (var1 < 30.0F) {
         this.vehicleObject.engineSpeed = this.vehicleObject.engineSpeed
            - Math.min(0.02 * (this.vehicleObject.engineSpeed - 7000.0), (double)(30.0F - var1)) * var2;
      }

      this.EngineForce = (float)(this.vehicleObject.getEnginePower() * (0.5 + this.vehicleObject.engineSpeed / 24000.0));
      this.EngineForce = this.EngineForce - this.EngineForce * (var1 / 200.0F);
    bool var9 = false;
      if (this.vehicleObject.transmissionNumber == TransmissionNumber.Speed1 && this.vehicleObject.getVehicleTowedBy() != nullptr) {
         if (this.vehicleObject.getVehicleTowedBy().getScript().getPassengerCount() == 0
            && this.vehicleObject.getVehicleTowedBy().getScript().getMass() > 200.0F) {
            var9 = true;
         }

         if (var1 < (var9 ? 20 : 5)) {
            this.EngineForce = this.EngineForce * Math.min(1.2F, this.vehicleObject.getVehicleTowedBy().getMass() / 500.0F);
            if (var9) {
               this.EngineForce *= 4.0F;
            }
         }
      }

      if (this.vehicleObject.engineSpeed > 6000.0) {
         this.EngineForce = (float)(this.EngineForce * ((7000.0 - this.vehicleObject.engineSpeed) / 1000.0));
      }

      if (var5) {
         this.EngineForce *= 0.6F;
         if (var1 > 20.0F) {
            this.EngineForce *= (40.0F - var1) / 20.0F;
         }
      }

      if (var4) {
         if (var1 > this.vehicleObject.getMaxSpeed() * 1.15F) {
            this.EngineForce = this.EngineForce * ((this.vehicleObject.getMaxSpeed() * 1.15F + 20.0F - var1) / 20.0F);
         }
      } else if (var1 > this.vehicleObject.getMaxSpeed()) {
         this.EngineForce = this.EngineForce * ((this.vehicleObject.getMaxSpeed() + 20.0F - var1) / 20.0F);
      }

      this.BrakingForce = 0.0F;
      if (this.clientControls.wasUsingParkingBrakes) {
         this.clientControls.wasUsingParkingBrakes = false;
         this.EngineForce *= 8.0F;
      }

      if (GameClient.bClient && this.vehicleObject.jniSpeed >= ServerOptions.instance.SpeedLimit.getValue()) {
         this.EngineForce = 0.0F;
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    void control_ForwardNew(float var1) {
    float var2 = GameTime.getInstance().getMultiplier() / 0.8F;
    IsoGameCharacter var3 = this.vehicleObject.getDriver();
    bool var4 = var3 != nullptr && var3.Traits.SpeedDemon.isSet();
    bool var5 = var3 != nullptr && var3.Traits.SundayDriver.isSet();
    int var6 = this.vehicleObject.getScript().gearRatioCount;
    float var7 = 0.0F;
      EngineRPMData[] var8 = this.vehicleObject.getVehicleEngineRPM().m_rpmData;
    float var9 = this.vehicleObject.getMaxSpeed() / var6;
    float var10 = PZMath.clamp(var1, 0.0F, this.vehicleObject.getMaxSpeed());
    int var11 = (int)PZMath.floor(var10 / var9) + 1;
      var11 = PZMath.min(var11, var6);
      var7 = var8[var11 - 1].gearChange;
    TransmissionNumber var12 = TransmissionNumber.Speed1;
      switch (var11) {
         case 1:
            var12 = TransmissionNumber.Speed1;
            break;
         case 2:
            var12 = TransmissionNumber.Speed2;
            break;
         case 3:
            var12 = TransmissionNumber.Speed3;
            break;
         case 4:
            var12 = TransmissionNumber.Speed4;
            break;
         case 5:
            var12 = TransmissionNumber.Speed5;
            break;
         case 6:
            var12 = TransmissionNumber.Speed6;
            break;
         case 7:
            var12 = TransmissionNumber.Speed7;
            break;
         case 8:
            var12 = TransmissionNumber.Speed8;
      }

      if (this.vehicleObject.transmissionNumber == TransmissionNumber.N) {
         this.vehicleObject.transmissionNumber = var12;
      } else if (this.vehicleObject.transmissionNumber.getIndex() - 1 >= 0
         && this.vehicleObject.transmissionNumber.getIndex() < var12.getIndex()
         && this.vehicleObject.getEngineSpeed() >= var8[this.vehicleObject.transmissionNumber.getIndex() - 1].gearChange
         && var1 >= var9 * this.vehicleObject.transmissionNumber.getIndex()) {
         this.vehicleObject.transmissionNumber = var12;
         this.vehicleObject.engineSpeed = var8[this.vehicleObject.transmissionNumber.getIndex() - 1].afterGearChange;
      }

      if (this.vehicleObject.transmissionNumber.getIndex() < var6 && this.vehicleObject.transmissionNumber.getIndex() - 1 >= 0) {
         this.vehicleObject.engineSpeed = Math.min(
            this.vehicleObject.engineSpeed, (double)(var8[this.vehicleObject.transmissionNumber.getIndex() - 1].gearChange + 100.0F)
         );
      }

      if (this.vehicleObject.engineSpeed > var7) {
         this.vehicleObject.engineSpeed = this.vehicleObject.engineSpeed - Math.min(0.5 * (this.vehicleObject.engineSpeed - var7), 10.0) * var2;
      } else {
         float var13 = switch (1.$SwitchMap$zombie$vehicles$TransmissionNumber[this.vehicleObject.transmissionNumber.ordinal()]) {
            case 1 -> 10.0F;
            case 2 -> 8.0F;
            case 3 -> 7.0F;
            case 4 -> 6.0F;
            case 5 -> 5.0F;
            default -> 4.0F;
         };
         this.vehicleObject.engineSpeed += var13 * var2;
      }

    float var17 = this.vehicleObject.getEnginePower();
      var17 = this.vehicleObject.getScript().getEngineForce();

      var17 *= switch (1.$SwitchMap$zombie$vehicles$TransmissionNumber[this.vehicleObject.transmissionNumber.ordinal()]) {
         case 1 -> 1.5F;
         default -> 1.0F;
      };
      this.EngineForce = (float)(var17 * (0.3F + this.vehicleObject.engineSpeed / 30000.0));
      this.EngineForce = this.EngineForce - this.EngineForce * (var1 / 200.0F);
    bool var14 = false;
      if (this.vehicleObject.transmissionNumber == TransmissionNumber.Speed1 && this.vehicleObject.getVehicleTowedBy() != nullptr) {
         if (this.vehicleObject.getVehicleTowedBy().getScript().getPassengerCount() == 0
            && this.vehicleObject.getVehicleTowedBy().getScript().getMass() > 200.0F) {
            var14 = true;
         }

         if (var1 < (var14 ? 20 : 5)) {
            this.EngineForce = this.EngineForce * Math.min(1.2F, this.vehicleObject.getVehicleTowedBy().getMass() / 500.0F);
            if (var14) {
               this.EngineForce *= 4.0F;
            }
         }
      }

      if (this.vehicleObject.engineSpeed > 6000.0) {
         this.EngineForce = (float)(this.EngineForce * ((7000.0 - this.vehicleObject.engineSpeed) / 1000.0));
      }

      if (var5) {
         this.EngineForce *= 0.6F;
         if (var1 > 20.0F) {
            this.EngineForce *= (40.0F - var1) / 20.0F;
         }
      }

      if (var4) {
         if (var1 > this.vehicleObject.getMaxSpeed() * 1.15F) {
            this.EngineForce = this.EngineForce * ((this.vehicleObject.getMaxSpeed() * 1.15F + 20.0F - var1) / 20.0F);
         }
      } else if (var1 > this.vehicleObject.getMaxSpeed()) {
         this.EngineForce = this.EngineForce * ((this.vehicleObject.getMaxSpeed() + 20.0F - var1) / 20.0F);
      }

      this.BrakingForce = 0.0F;
      if (this.clientControls.wasUsingParkingBrakes) {
         this.clientControls.wasUsingParkingBrakes = false;
         this.EngineForce *= 8.0F;
      }

      if (GameClient.bClient && this.vehicleObject.jniSpeed >= ServerOptions.instance.SpeedLimit.getValue()) {
         this.EngineForce = 0.0F;
      }
   }

    void control_Reverse(float var1) {
    float var2 = GameTime.getInstance().getMultiplier() / 0.8F;
      var1 *= 1.5F;
    IsoGameCharacter var3 = this.vehicleObject.getDriver();
    bool var4 = var3 != nullptr && var3.Traits.SpeedDemon.isSet();
    bool var5 = var3 != nullptr && var3.Traits.SundayDriver.isSet();
      this.vehicleObject.transmissionNumber = TransmissionNumber.R;
    float var6 = 1000.0F * var1 / 30.0F;
      this.vehicleObject.engineSpeed = this.vehicleObject.engineSpeed - Math.min(0.5 * (this.vehicleObject.engineSpeed - var6), 100.0) * var2;
      if (var4) {
         this.vehicleObject.engineSpeed = this.vehicleObject.engineSpeed
            - Math.min(0.06 * (this.vehicleObject.engineSpeed - 7000.0), (double)(30.0F - var1)) * var2;
      } else {
         this.vehicleObject.engineSpeed = this.vehicleObject.engineSpeed
            - Math.min(0.02 * (this.vehicleObject.engineSpeed - 7000.0), (double)(30.0F - var1)) * var2;
      }

      this.EngineForce = (float)(-1.0F * this.vehicleObject.getEnginePower() * (0.75 + this.vehicleObject.engineSpeed / 24000.0));
      if (this.vehicleObject.engineSpeed > 6000.0) {
         this.EngineForce = (float)(this.EngineForce * ((7000.0 - this.vehicleObject.engineSpeed) / 1000.0));
      }

      if (var5) {
         this.EngineForce *= 0.7F;
         if (var1 < -5.0F) {
            this.EngineForce *= (15.0F + var1) / 10.0F;
         }
      }

      if (var1 < -30.0F) {
         this.EngineForce *= (40.0F + var1) / 10.0F;
      }

      this.BrakingForce = 0.0F;
   }

    void updateRammingSound(float var1) {
      if (this.vehicleObject.isEngineRunning()
         && (
            var1 < 1.0F && this.EngineForce > this.vehicleObject.getScript().getEngineIdleSpeed() * 2.0F
               || var1 > -0.5F && this.EngineForce < this.vehicleObject.getScript().getEngineIdleSpeed() * -2.0F
         )) {
         if (this.vehicleObject.ramSound == 0L) {
            this.vehicleObject.ramSound = this.vehicleObject.playSoundImpl("VehicleSkid", (IsoObject)nullptr);
            this.vehicleObject.ramSoundTime = System.currentTimeMillis() + 1000L + Rand.Next(2000);
         }

         if (this.vehicleObject.ramSound != 0L && this.vehicleObject.ramSoundTime < System.currentTimeMillis()) {
            this.vehicleObject.stopSound(this.vehicleObject.ramSound);
            this.vehicleObject.ramSound = 0L;
         }
      } else if (this.vehicleObject.ramSound != 0L) {
         this.vehicleObject.stopSound(this.vehicleObject.ramSound);
         this.vehicleObject.ramSound = 0L;
      }
   }

    void updateBackSignal() {
      if (this.isGasR && this.vehicleObject.isEngineRunning() && this.vehicleObject.hasBackSignal() && !this.vehicleObject.isBackSignalEmitting()) {
         if (GameClient.bClient) {
            GameClient.instance.sendClientCommandV((IsoPlayer)this.vehicleObject.getDriver(), "vehicle", "onBackSignal", new Object[]{"state", "start"});
         } else {
            this.vehicleObject.onBackMoveSignalStart();
         }
      }

      if (!this.isGasR && this.vehicleObject.isBackSignalEmitting()) {
         if (GameClient.bClient) {
            GameClient.instance.sendClientCommandV((IsoPlayer)this.vehicleObject.getDriver(), "vehicle", "onBackSignal", new Object[]{"state", "stop"});
         } else {
            this.vehicleObject.onBackMoveSignalStop();
         }
      }
   }

    void updateBrakeLights() {
      if (this.isBreak) {
         if (this.vehicleObject.getStoplightsOn()) {
            return;
         }

         if (GameClient.bClient) {
            GameClient.instance.sendClientCommandV((IsoPlayer)this.vehicleObject.getDriver(), "vehicle", "setStoplightsOn", new Object[]{"on", bool.TRUE});
         }

         if (!GameServer.bServer) {
            this.vehicleObject.setStoplightsOn(true);
         }
      } else {
         if (!this.vehicleObject.getStoplightsOn()) {
            return;
         }

         if (GameClient.bClient) {
            GameClient.instance.sendClientCommandV((IsoPlayer)this.vehicleObject.getDriver(), "vehicle", "setStoplightsOn", new Object[]{"on", bool.FALSE});
         }

         if (!GameServer.bServer) {
            this.vehicleObject.setStoplightsOn(false);
         }
      }
   }

    bool delayCommandWhileDrunk(bool var1) {
      this.drunkDelayCommandTimer = this.drunkDelayCommandTimer + GameTime.getInstance().getMultiplier();
      if (Rand.AdjustForFramerate(4 * this.vehicleObject.getDriver().getMoodles().getMoodleLevel(MoodleType.Drunk)) < this.drunkDelayCommandTimer) {
         this.drunkDelayCommandTimer = 0.0F;
    return true;
      } else {
    return false;
      }
   }

    float delayCommandWhileDrunk(float var1) {
      this.drunkDelayCommandTimer = this.drunkDelayCommandTimer + GameTime.getInstance().getMultiplier();
      if (Rand.AdjustForFramerate(4 * this.vehicleObject.getDriver().getMoodles().getMoodleLevel(MoodleType.Drunk)) < this.drunkDelayCommandTimer) {
         this.drunkDelayCommandTimer = 0.0F;
    return var1;
      } else {
         return 0.0F;
      }
   }

    void checkTire(BulletVariables var1) {
      if (this.vehicleObject.getPartById("TireFrontLeft") == nullptr || this.vehicleObject.getPartById("TireFrontLeft").getInventoryItem() == nullptr) {
         var1.brakingForce = (float)(var1.brakingForce / 1.2);
         var1.engineForce = (float)(var1.engineForce / 1.2);
      }

      if (this.vehicleObject.getPartById("TireFrontRight") == nullptr || this.vehicleObject.getPartById("TireFrontRight").getInventoryItem() == nullptr) {
         var1.brakingForce = (float)(var1.brakingForce / 1.2);
         var1.engineForce = (float)(var1.engineForce / 1.2);
      }

      if (this.vehicleObject.getPartById("TireRearLeft") == nullptr || this.vehicleObject.getPartById("TireRearLeft").getInventoryItem() == nullptr) {
         var1.brakingForce = (float)(var1.brakingForce / 1.3);
         var1.engineForce = (float)(var1.engineForce / 1.3);
      }

      if (this.vehicleObject.getPartById("TireRearRight") == nullptr || this.vehicleObject.getPartById("TireRearRight").getInventoryItem() == nullptr) {
         var1.brakingForce = (float)(var1.brakingForce / 1.3);
         var1.engineForce = (float)(var1.engineForce / 1.3);
      }
   }

    void updateControls() {
      if (!GameServer.bServer) {
         if (this.vehicleObject.isKeyboardControlled()) {
    bool var1 = GameKeyboard.isKeyDown(Core.getInstance().getKey("Left"));
    bool var2 = GameKeyboard.isKeyDown(Core.getInstance().getKey("Right"));
    bool var3 = GameKeyboard.isKeyDown(Core.getInstance().getKey("Forward"));
    bool var4 = GameKeyboard.isKeyDown(Core.getInstance().getKey("Backward"));
    bool var5 = GameKeyboard.isKeyDown(57);
    bool var6 = GameKeyboard.isKeyDown(42);
            this.clientControls.steering = 0.0F;
            if (var1) {
               this.clientControls.steering--;
            }

            if (var2) {
               this.clientControls.steering++;
            }

            this.clientControls.forward = var3;
            this.clientControls.backward = var4;
            this.clientControls.brake = var5;
            this.clientControls.shift = var6;
            if (this.clientControls.brake) {
               this.clientControls.wasUsingParkingBrakes = true;
            }
         }

    int var8 = this.vehicleObject.getJoypad();
         if (var8 != -1) {
    bool var9 = JoypadManager.instance.isLeftPressed(var8);
    bool var11 = JoypadManager.instance.isRightPressed(var8);
    bool var12 = JoypadManager.instance.isRTPressed(var8);
    bool var13 = JoypadManager.instance.isLTPressed(var8);
    bool var14 = JoypadManager.instance.isBPressed(var8);
    float var7 = JoypadManager.instance.getMovementAxisX(var8);
            this.clientControls.steering = var7;
            this.clientControls.forward = var12;
            this.clientControls.backward = var13;
            this.clientControls.brake = var14;
         }

         if (this.clientControls.forceBrake != 0L) {
    long var10 = System.currentTimeMillis() - this.clientControls.forceBrake;
            if (var10 > 0L && var10 < 1000L) {
               this.clientControls.brake = true;
               this.clientControls.shift = false;
            }
         }
      }
   }

    void park() {
      if (!GameServer.bServer && this.vehicleObject.getScript().getWheelCount() > 0) {
         Bullet.controlVehicle(this.vehicleObject.VehicleID, 0.0F, this.vehicleObject.getBrakingForce(), 0.0F);
      }

      this.isGas = this.wasGas = false;
      this.isGasR = this.wasGasR = false;
      this.clientControls.reset();
      this.vehicleObject.transmissionNumber = TransmissionNumber.N;
      if (this.vehicleObject.getVehicleTowing() != nullptr) {
         this.vehicleObject.getVehicleTowing().getController().park();
      }
   }

    bool shouldBeActive() {
      if (this.vehicleObject.physicActiveCheck != -1L) {
    return true;
      } else {
    BaseVehicle var1 = this.vehicleObject.getVehicleTowedBy();
         if (var1 == nullptr) {
    float var2 = this.vehicleObject.isEngineRunning() ? this.EngineForce : 0.0F;
            return Math.abs(var2) > 0.01F;
         } else {
            return var1.getController() == nullptr ? false : var1.getController().shouldBeActive();
         }
      }
   }

    void checkShouldBeActive() {
      if (this.shouldBeActive()) {
         if (!this.isEnable) {
            Bullet.setVehicleActive(this.vehicleObject.VehicleID, true);
            this.isEnable = true;
         }

         this.atRestTimer = 1.0F;
      } else if (this.isEnable && this.vehicleObject.isAtRest()) {
         if (this.atRestTimer > 0.0F) {
            this.atRestTimer = this.atRestTimer - GameTime.getInstance().getTimeDelta();
         }

         if (this.atRestTimer <= 0.0F) {
            Bullet.setVehicleActive(this.vehicleObject.VehicleID, false);
            this.isEnable = false;
         }
      }
   }

    bool isGasPedalPressed() {
      return this.isGas || this.isGasR;
   }

    bool isBrakePedalPressed() {
      return this.isBreak;
   }

    void debug() {
      if (Core.bDebug && DebugOptions.instance.VehicleRenderOutline.getValue()) {
    VehicleScript var1 = this.vehicleObject.getScript();
    Vector3f var2 = this.tempVec3f;
         this.vehicleObject.getForwardVector(var2);
    Transform var3 = this.tempXfrm;
         this.vehicleObject.getWorldTransform(var3);
    VehiclePoly var4 = this.vehicleObject.getPoly();
         LineDrawer.addLine(var4.x1, var4.y1, 0.0F, var4.x2, var4.y2, 0.0F, 1.0F, 1.0F, 1.0F, nullptr, true);
         LineDrawer.addLine(var4.x2, var4.y2, 0.0F, var4.x3, var4.y3, 0.0F, 1.0F, 1.0F, 1.0F, nullptr, true);
         LineDrawer.addLine(var4.x3, var4.y3, 0.0F, var4.x4, var4.y4, 0.0F, 1.0F, 1.0F, 1.0F, nullptr, true);
         LineDrawer.addLine(var4.x4, var4.y4, 0.0F, var4.x1, var4.y1, 0.0F, 1.0F, 1.0F, 1.0F, nullptr, true);
         _UNIT_Y.set(0.0F, 1.0F, 0.0F);

         for (int var9 = 0; var9 < this.vehicleObject.getScript().getWheelCount(); var9++) {
    Wheel var5 = var1.getWheel(var9);
            this.tempVec3f.set(var5.getOffset());
            if (var1.getModel() != nullptr) {
               this.tempVec3f.push_back(var1.getModelOffset());
            }

            this.vehicleObject.getWorldPos(this.tempVec3f, this.tempVec3f);
    float var6 = this.tempVec3f.x;
    float var7 = this.tempVec3f.y;
            this.vehicleObject.getWheelForwardVector(var9, this.tempVec3f);
            LineDrawer.addLine(var6, var7, 0.0F, var6 + this.tempVec3f.x, var7 + this.tempVec3f.z, 0.0F, 1.0F, 1.0F, 1.0F, nullptr, true);
            this.drawRect(this.tempVec3f, var6 - WorldSimulation.instance.offsetX, var7 - WorldSimulation.instance.offsetY, var5.width, var5.radius);
         }

         if (this.vehicleObject.collideX != -1.0F) {
            this.vehicleObject.getForwardVector(var2);
            this.drawCircle(this.vehicleObject.collideX, this.vehicleObject.collideY, 0.3F);
            this.vehicleObject.collideX = -1.0F;
            this.vehicleObject.collideY = -1.0F;
         }

    int var10 = this.vehicleObject.getJoypad();
         if (var10 != -1) {
    float var11 = JoypadManager.instance.getMovementAxisX(var10);
    float var13 = JoypadManager.instance.getMovementAxisY(var10);
    float var15 = JoypadManager.instance.getDeadZone(var10, 0);
            if (Math.abs(var13) > var15 || Math.abs(var11) > var15) {
    Vector2 var8 = this.tempVec2.set(var11, var13);
               var8.setLength(4.0F);
               var8.rotate((float) (-Math.PI / 4));
               LineDrawer.addLine(
                  this.vehicleObject.getX(),
                  this.vehicleObject.getY(),
                  this.vehicleObject.z,
                  this.vehicleObject.getX() + var8.x,
                  this.vehicleObject.getY() + var8.y,
                  this.vehicleObject.z,
                  1.0F,
                  1.0F,
                  1.0F,
                  nullptr,
                  true
               );
            }
         }

    float var12 = this.vehicleObject.x;
    float var14 = this.vehicleObject.y;
    float var16 = this.vehicleObject.z;
         LineDrawer.DrawIsoLine(var12 - 0.5F, var14, var16, var12 + 0.5F, var14, var16, 1.0F, 1.0F, 1.0F, 0.25F, 1);
         LineDrawer.DrawIsoLine(var12, var14 - 0.5F, var16, var12, var14 + 0.5F, var16, 1.0F, 1.0F, 1.0F, 0.25F, 1);
      }
   }

    void drawRect(Vector3f var1, float var2, float var3, float var4, float var5) {
      this.drawRect(var1, var2, var3, var4, var5, 1.0F, 1.0F, 1.0F);
   }

    void drawRect(Vector3f var1, float var2, float var3, float var4, float var5, float var6, float var7, float var8) {
    float var9 = var1.x;
    float var10 = var1.y;
    float var11 = var1.z;
    Vector3f var12 = this.tempVec3f_3;
      var1.cross(_UNIT_Y, var12);
    float var13 = 1.0F;
      var1.x *= var13 * var5;
      var1.z *= var13 * var5;
      var12.x *= var13 * var4;
      var12.z *= var13 * var4;
    float var14 = var2 + var1.x;
    float var15 = var3 + var1.z;
    float var16 = var2 - var1.x;
    float var17 = var3 - var1.z;
    float var18 = var14 - var12.x / 2.0F;
    float var19 = var14 + var12.x / 2.0F;
    float var20 = var16 - var12.x / 2.0F;
    float var21 = var16 + var12.x / 2.0F;
    float var22 = var17 - var12.z / 2.0F;
    float var23 = var17 + var12.z / 2.0F;
    float var24 = var15 - var12.z / 2.0F;
    float var25 = var15 + var12.z / 2.0F;
      var18 += WorldSimulation.instance.offsetX;
      var24 += WorldSimulation.instance.offsetY;
      var19 += WorldSimulation.instance.offsetX;
      var25 += WorldSimulation.instance.offsetY;
      var20 += WorldSimulation.instance.offsetX;
      var22 += WorldSimulation.instance.offsetY;
      var21 += WorldSimulation.instance.offsetX;
      var23 += WorldSimulation.instance.offsetY;
      LineDrawer.addLine(var18, var24, 0.0F, var19, var25, 0.0F, var6, var7, var8, nullptr, true);
      LineDrawer.addLine(var18, var24, 0.0F, var20, var22, 0.0F, var6, var7, var8, nullptr, true);
      LineDrawer.addLine(var19, var25, 0.0F, var21, var23, 0.0F, var6, var7, var8, nullptr, true);
      LineDrawer.addLine(var20, var22, 0.0F, var21, var23, 0.0F, var6, var7, var8, nullptr, true);
      var1.set(var9, var10, var11);
   }

    void drawCircle(float var1, float var2, float var3) {
      this.drawCircle(var1, var2, var3, 1.0F, 1.0F, 1.0F, 1.0F);
   }

    void drawCircle(float var1, float var2, float var3, float var4, float var5, float var6, float var7) {
      LineDrawer.DrawIsoCircle(var1, var2, 0.0F, var3, 16, var4, var5, var6, var7);
   }

   static {
      gears[0] = std::make_shared<GearInfo>(0, 25, 0.0F);
      gears[1] = std::make_shared<GearInfo>(25, 50, 0.5F);
      gears[2] = std::make_shared<GearInfo>(50, 1000, 0.5F);
   }
}
} // namespace physics
} // namespace core
} // namespace zombie
