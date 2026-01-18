#pragma once
#include "org/joml/Vector3f.h"
#include "zombie/GameTime.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/Moodles/MoodleType.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/math/PZMath.h"
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
#include "zombie/ui/UIManager.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/EngineRPMData.h"
#include "zombie/vehicles/PolygonalMap2.h"
#include "zombie/vehicles/TransmissionNumber.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace physics {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * Created by LEMMYCOOLER on 17/04/14.
 */
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
  const Transform tempXfrm = new Transform();
  const Vector2 tempVec2 = new Vector2();
  const Vector3f tempVec3f = new Vector3f();
  const Vector3f tempVec3f_2 = new Vector3f();
  const Vector3f tempVec3f_3 = new Vector3f();
  static const Vector3f _UNIT_Y = new Vector3f(0.0F, 1.0F, 0.0F);
  bool acceleratorOn = false;
  bool brakeOn = false;
  float speed = 0.0F;
public
  static CarController.GearInfo[] gears = new CarController.GearInfo[3];
public
  final CarController.ClientControls clientControls =
      new CarController.ClientControls();
  bool engineStartingFromKeyboard;
private
  static final CarController.BulletVariables bulletVariables =
      new CarController.BulletVariables();
  float drunkDelayCommandTimer = 0.0F;
  bool wasBreaking = false;
  bool wasGas = false;
  bool wasGasR = false;
  bool wasSteering = false;

public
  CarController(BaseVehicle _vehicleObject) {
    this.vehicleObject = _vehicleObject;
    this.engineStartingFromKeyboard = false;
    VehicleScript vehicleScript = _vehicleObject.getScript();
    float float0 = _vehicleObject.savedPhysicsZ;
    if (Float.isNaN(float0)) {
      float float1 = Math.max((float)((int)_vehicleObject.z), 0.0F);
      if (vehicleScript.getWheelCount() > 0) {
        Vector3f vector3f = vehicleScript.getModelOffset();
        float1 += vector3f.y();
        float1 += vehicleScript.getWheel(0).getOffset().y() -
                  vehicleScript.getWheel(0).radius;
      }

      float float2 = vehicleScript.getCenterOfMassOffset().y() -
                     vehicleScript.getExtents().y() / 2.0F;
      float0 = 0.0F - Math.min(float1, float2);
      _vehicleObject.jniTransform.origin.y = float0;
    }

    if (!GameServer.bServer) {
      Bullet.addVehicle(_vehicleObject.VehicleID, _vehicleObject.x,
                        _vehicleObject.y, float0, _vehicleObject.savedRot.x,
                        _vehicleObject.savedRot.y, _vehicleObject.savedRot.z,
                        _vehicleObject.savedRot.w, vehicleScript.getFullName());
      Bullet.setVehicleStatic(_vehicleObject,
                              _vehicleObject.isNetPlayerAuthorization(
                                  BaseVehicle.Authorization.Remote));
      DebugLog.Vehicle.debugln(
          "Vehicle vid=%d type=%s has been added at (%f;%f;%f) auth=%s",
          _vehicleObject.VehicleID, vehicleScript.getFullName(),
          _vehicleObject.x, _vehicleObject.y, float0,
          _vehicleObject.getAuthorizationDescription());
    }
  }

public
  CarController.GearInfo findGear(float _speed) {
    for (int int0 = 0; int0 < gears.length; int0++) {
      if (_speed >= gears[int0].minSpeed && _speed < gears[int0].maxSpeed) {
        return gears[int0];
      }
    }

    return null;
  }

  void accelerator(bool apply) { this.acceleratorOn = apply; }

  void brake(bool apply) { this.brakeOn = apply; }

public
  CarController.ClientControls getClientControls() {
    return this.clientControls;
  }

  void update() {
    if (this.vehicleObject.getVehicleTowedBy() == nullptr) {
      VehicleScript vehicleScript = this.vehicleObject.getScript();
      this.speed = this.vehicleObject.getCurrentSpeedKmHour();
      bool boolean0 =
          this.vehicleObject.getDriver() != null &&
          this.vehicleObject.getDriver().getMoodles().getMoodleLevel(
              MoodleType.Drunk) > 1;
      float float0 = 0.0F;
      Vector3f vector3f0 =
          this.vehicleObject.getLinearVelocity(this.tempVec3f_2);
      vector3f0.y = 0.0F;
      if (vector3f0.length() > 0.5) {
        vector3f0.normalize();
        Vector3f vector3f1 = this.tempVec3f;
        this.vehicleObject.getForwardVector(vector3f1);
        float0 = vector3f0.dot(vector3f1);
      }

      float float1 = 1.0F;
      if (GameClient.bClient) {
        float float2 =
            this.vehicleObject.jniSpeed /
            Math.min(120.0F,
                     (float)ServerOptions.instance.SpeedLimit.getValue());
        float2 *= float2;
        float1 = GameTime.getInstance().Lerp(
            1.0F, BaseVehicle.getFakeSpeedModifier(), float2);
      }

      float float3 = this.vehicleObject.getCurrentSpeedKmHour() * float1;
      this.isGas = false;
      this.isGasR = false;
      this.isBreak = false;
      if (this.clientControls.forward) {
        if (float0 < 0.0F) {
          this.isBreak = true;
        }

        if (float0 >= 0.0F) {
          this.isGas = true;
        }

        this.isGasR = false;
      }

      if (this.clientControls.backward) {
        if (float0 > 0.0F) {
          this.isBreak = true;
        }

        if (float0 <= 0.0F) {
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

      if (boolean0 &&
          this.vehicleObject.engineState != BaseVehicle.engineStateTypes.Idle) {
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
          this.clientControls.steering =
              this.delayCommandWhileDrunk(this.clientControls.steering);
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

      float float4 = this.vehicleObject.throttle;
      if (!this.isGas && !this.isGasR) {
        float4 -= GameTime.getInstance().getMultiplier() / 30.0F;
      } else {
        float4 += GameTime.getInstance().getMultiplier() / 30.0F;
      }

      if (float4 < 0.0F) {
        float4 = 0.0F;
      }

      if (float4 > 1.0F) {
        float4 = 1.0F;
      }

      if (this.vehicleObject.isRegulator() && !this.isGas && !this.isGasR) {
        float4 = 0.5F;
        if (float3 < this.vehicleObject.getRegulatorSpeed()) {
          this.isGas = true;
        }
      }

      this.vehicleObject.throttle = float4;
      float float5 = GameTime.getInstance().getMultiplier() / 0.8F;
      CarController.ControlState controlState =
          CarController.ControlState.NoControl;
      if (this.isBreak) {
        controlState = CarController.ControlState.Braking;
      } else if (this.isGas && !this.isGasR) {
        controlState = CarController.ControlState.Forward;
      } else if (!this.isGas && this.isGasR) {
        controlState = CarController.ControlState.Reverse;
      }

      if (controlState != CarController.ControlState.NoControl) {
        UIManager.speedControls.SetCurrentGameSpeed(1);
      }

      if (controlState == CarController.ControlState.NoControl) {
        this.control_NoControl();
      }

      if (controlState == CarController.ControlState.Reverse) {
        this.control_Reverse(float3);
      }

      if (controlState == CarController.ControlState.Forward) {
        this.control_ForwardNew(float3);
      }

      this.updateBackSignal();
      if (controlState == CarController.ControlState.Braking) {
        this.control_Braking();
      }

      this.updateBrakeLights();
      BaseVehicle vehicle = this.vehicleObject.getVehicleTowedBy();
      if (vehicle != nullptr && vehicle.getDriver() == nullptr &&
          this.vehicleObject.getDriver() != nullptr && !GameClient.bClient) {
        this.vehicleObject.addPointConstraint(
            nullptr, vehicle, this.vehicleObject.getTowAttachmentSelf(),
            vehicle.getTowAttachmentSelf());
      }

      this.updateRammingSound(float3);
      if (Math.abs(this.clientControls.steering) > 0.1F) {
        float float6 = 1.0F - this.speed / this.vehicleObject.getMaxSpeed();
        if (float6 < 0.1F) {
          float6 = 0.1F;
        }

        this.VehicleSteering =
            this.VehicleSteering -
            (this.clientControls.steering + this.VehicleSteering) * 0.06F *
                float5 * float6;
      } else if (Math.abs(this.VehicleSteering) <= 0.04) {
        this.VehicleSteering = 0.0F;
      } else if (this.VehicleSteering > 0.0F) {
        this.VehicleSteering -= 0.04F * float5;
        this.VehicleSteering = Math.max(this.VehicleSteering, 0.0F);
      } else {
        this.VehicleSteering += 0.04F * float5;
        this.VehicleSteering = Math.min(this.VehicleSteering, 0.0F);
      }

      float float7 = vehicleScript.getSteeringClamp(this.speed);
      this.VehicleSteering =
          PZMath.clamp(this.VehicleSteering, -float7, float7);
      CarController.BulletVariables bulletVariablesx =
          bulletVariables.set(this.vehicleObject, this.EngineForce,
                              this.BrakingForce, this.VehicleSteering);
      this.checkTire(bulletVariablesx);
      this.EngineForce = bulletVariablesx.engineForce;
      this.BrakingForce = bulletVariablesx.brakingForce;
      this.VehicleSteering = bulletVariablesx.vehicleSteering;
      if (this.vehicleObject.isDoingOffroad()) {
        int int0 = this.vehicleObject.getTransmissionNumber();
        if (int0 <= 0) {
          int0 = 1;
        }

        this.EngineForce = (float)(this.EngineForce / (int0 * 1.5));
      }

      this.vehicleObject.setCurrentSteering(this.VehicleSteering);
      this.vehicleObject.setBraking(this.isBreak);
      if (!GameServer.bServer) {
        this.checkShouldBeActive();
        Bullet.controlVehicle(this.vehicleObject.VehicleID, this.EngineForce,
                              this.BrakingForce, this.VehicleSteering);
        if (this.EngineForce > 0.0F &&
            this.vehicleObject.engineState ==
                BaseVehicle.engineStateTypes.Idle &&
            !this.engineStartingFromKeyboard) {
          this.engineStartingFromKeyboard = true;
          if (GameClient.bClient) {
            Boolean boolean1 =
                this.vehicleObject.getDriver().getInventory().haveThisKeyId(
                    this.vehicleObject.getKeyId()) != nullptr
                    ? Boolean.TRUE
                    : Boolean.FALSE;
            GameClient.instance.sendClientCommandV(
                (IsoPlayer)this.vehicleObject.getDriver(), "vehicle",
                "startEngine", "haveKey", boolean1);
          } else {
            this.vehicleObject.tryStartEngine();
          }
        }

        if (this.engineStartingFromKeyboard && this.EngineForce == 0.0F) {
          this.engineStartingFromKeyboard = false;
        }
      }

      if (this.vehicleObject.engineState !=
          BaseVehicle.engineStateTypes.Running) {
        this.acceleratorOn = false;
        if (!GameServer.bServer && this.vehicleObject.jniSpeed > 5.0F &&
            this.vehicleObject.getScript().getWheelCount() > 0) {
          Bullet.controlVehicle(this.vehicleObject.VehicleID, 0.0F,
                                this.BrakingForce, this.VehicleSteering);
        } else {
          this.park();
        }
      }
    }
  }

  void updateTrailer() {
    BaseVehicle vehicle = this.vehicleObject.getVehicleTowedBy();
    if (vehicle != nullptr) {
      if (GameServer.bServer) {
        if (vehicle.getDriver() == nullptr &&
            this.vehicleObject.getDriver() != nullptr) {
          this.vehicleObject.addPointConstraint(
              nullptr, vehicle, this.vehicleObject.getTowAttachmentSelf(),
              vehicle.getTowAttachmentSelf());
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
        if (vehicle.getDriver() == nullptr &&
            this.vehicleObject.getDriver() != nullptr && !GameClient.bClient) {
          this.vehicleObject.addPointConstraint(
              nullptr, vehicle, this.vehicleObject.getTowAttachmentSelf(),
              vehicle.getTowAttachmentSelf());
        } else {
          this.checkShouldBeActive();
          this.EngineForce = 0.0F;
          this.BrakingForce = 0.0F;
          this.VehicleSteering = 0.0F;
          if (!this.vehicleObject.getScriptName().contains("Trailer")) {
            this.BrakingForce = 10.0F;
          }

          Bullet.controlVehicle(this.vehicleObject.VehicleID, this.EngineForce,
                                this.BrakingForce, this.VehicleSteering);
        }
      }
    }
  }

  void updateRegulator() {
    if (this.regulatorTimer > 0.0F) {
      this.regulatorTimer =
          this.regulatorTimer - GameTime.getInstance().getMultiplier() / 1.6F;
    }

    if (this.clientControls.shift) {
      if (this.clientControls.forward && this.regulatorTimer <= 0.0F) {
        if (this.vehicleObject.getRegulatorSpeed() <
                this.vehicleObject.getMaxSpeed() + 20.0F &&
            (!this.vehicleObject.isRegulator() &&
                 this.vehicleObject.getRegulatorSpeed() == 0.0F ||
             this.vehicleObject.isRegulator())) {
          if (this.vehicleObject.getRegulatorSpeed() == 0.0F &&
              this.vehicleObject.getCurrentSpeedForRegulator() !=
                  this.vehicleObject.getRegulatorSpeed()) {
            this.vehicleObject.setRegulatorSpeed(
                this.vehicleObject.getCurrentSpeedForRegulator());
          } else {
            this.vehicleObject.setRegulatorSpeed(
                this.vehicleObject.getRegulatorSpeed() + 5.0F);
          }
        }

        this.vehicleObject.setRegulator(true);
        this.regulatorTimer = 20.0F;
      } else if (this.clientControls.backward && this.regulatorTimer <= 0.0F) {
        this.regulatorTimer = 20.0F;
        if (this.vehicleObject.getRegulatorSpeed() >= 5.0F &&
            (!this.vehicleObject.isRegulator() &&
                 this.vehicleObject.getRegulatorSpeed() == 0.0F ||
             this.vehicleObject.isRegulator())) {
          this.vehicleObject.setRegulatorSpeed(
              this.vehicleObject.getRegulatorSpeed() - 5.0F);
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
    float float0 = GameTime.getInstance().getMultiplier() / 0.8F;
    if (!this.vehicleObject.isEngineRunning()) {
      if (this.vehicleObject.engineSpeed > 0.0) {
        this.vehicleObject.engineSpeed =
            Math.max(this.vehicleObject.engineSpeed - 50.0F * float0, 0.0);
      }
    } else if (this.vehicleObject.engineSpeed >
               this.vehicleObject.getScript().getEngineIdleSpeed()) {
      if (!this.vehicleObject.isRegulator()) {
        this.vehicleObject.engineSpeed -= 20.0F * float0;
      }
    } else {
      this.vehicleObject.engineSpeed += 20.0F * float0;
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
    float float0 = GameTime.getInstance().getMultiplier() / 0.8F;
    if (this.vehicleObject.engineSpeed >
        this.vehicleObject.getScript().getEngineIdleSpeed()) {
      this.vehicleObject.engineSpeed =
          this.vehicleObject.engineSpeed - Rand.Next(10, 30) * float0;
    } else {
      this.vehicleObject.engineSpeed =
          this.vehicleObject.engineSpeed + Rand.Next(20) * float0;
    }

    this.vehicleObject.transmissionNumber = TransmissionNumber.N;
    this.EngineForce = 0.0F;
    this.BrakingForce = this.vehicleObject.getBrakingForce();
    if (this.clientControls.brake) {
      this.BrakingForce *= 13.0F;
    }
  }

  void control_Forward(float float2) {
    float float0 = GameTime.getInstance().getMultiplier() / 0.8F;
    IsoGameCharacter character = this.vehicleObject.getDriver();
    bool boolean0 = character != null && character.Traits.SpeedDemon.isSet();
    bool boolean1 = character != null && character.Traits.SundayDriver.isSet();
    int int0 = this.vehicleObject.getScript().gearRatioCount;
    float float1 = 0.0F;
    if (this.vehicleObject.transmissionNumber == TransmissionNumber.N) {
      this.vehicleObject.transmissionNumber = TransmissionNumber.Speed1;
      bool boolean2 = false;

      while (true) {
        if (this.vehicleObject.transmissionNumber ==
            TransmissionNumber.Speed1) {
          float1 = 3000.0F * float2 / 30.0F;
        }

        if (this.vehicleObject.transmissionNumber ==
            TransmissionNumber.Speed2) {
          float1 = 3000.0F * float2 / 40.0F;
        }

        if (this.vehicleObject.transmissionNumber ==
            TransmissionNumber.Speed3) {
          float1 = 3000.0F * float2 / 60.0F;
        }

        if (this.vehicleObject.transmissionNumber ==
            TransmissionNumber.Speed4) {
          float1 = 3000.0F * float2 / 85.0F;
        }

        if (this.vehicleObject.transmissionNumber ==
            TransmissionNumber.Speed5) {
          float1 = 3000.0F * float2 / 105.0F;
        }

        if (this.vehicleObject.transmissionNumber ==
            TransmissionNumber.Speed6) {
          float1 = 3000.0F * float2 / 130.0F;
        }

        if (this.vehicleObject.transmissionNumber ==
            TransmissionNumber.Speed7) {
          float1 = 3000.0F * float2 / 160.0F;
        }

        if (this.vehicleObject.transmissionNumber ==
            TransmissionNumber.Speed8) {
          float1 = 3000.0F * float2 / 200.0F;
        }

        if (boolean0) {
          if (float1 > 6000.0F) {
            this.vehicleObject.changeTransmission(
                this.vehicleObject.transmissionNumber.getNext(int0));
            boolean2 = true;
          }
        } else if (float1 > 3000.0F) {
          this.vehicleObject.changeTransmission(
              this.vehicleObject.transmissionNumber.getNext(int0));
          boolean2 = true;
        }

        if (!boolean2 ||
            this.vehicleObject.transmissionNumber.getIndex() >= int0) {
          break;
        }

        boolean2 = false;
      }
    }

    if (boolean0) {
      if (this.vehicleObject.engineSpeed > 6000.0 &&
          this.vehicleObject.transmissionChangeTime.Check()) {
        this.vehicleObject.changeTransmission(
            this.vehicleObject.transmissionNumber.getNext(int0));
      }
    } else if (this.vehicleObject.engineSpeed > 3000.0 &&
               this.vehicleObject.transmissionChangeTime.Check()) {
      this.vehicleObject.changeTransmission(
          this.vehicleObject.transmissionNumber.getNext(int0));
    }

    if (this.vehicleObject.transmissionNumber == TransmissionNumber.Speed1) {
      float1 = 3000.0F * float2 / 30.0F;
    }

    if (this.vehicleObject.transmissionNumber == TransmissionNumber.Speed2) {
      float1 = 3000.0F * float2 / 40.0F;
    }

    if (this.vehicleObject.transmissionNumber == TransmissionNumber.Speed3) {
      float1 = 3000.0F * float2 / 60.0F;
    }

    if (this.vehicleObject.transmissionNumber == TransmissionNumber.Speed4) {
      float1 = 3000.0F * float2 / 85.0F;
    }

    if (this.vehicleObject.transmissionNumber == TransmissionNumber.Speed5) {
      float1 = 3000.0F * float2 / 105.0F;
    }

    if (this.vehicleObject.transmissionNumber == TransmissionNumber.Speed6) {
      float1 = 3000.0F * float2 / 130.0F;
    }

    if (this.vehicleObject.transmissionNumber == TransmissionNumber.Speed7) {
      float1 = 3000.0F * float2 / 160.0F;
    }

    if (this.vehicleObject.transmissionNumber == TransmissionNumber.Speed8) {
      float1 = 3000.0F * float2 / 200.0F;
    }

    this.vehicleObject.engineSpeed =
        this.vehicleObject.engineSpeed -
        Math.min(0.5 * (this.vehicleObject.engineSpeed - float1), 100.0) *
            float0;
    if (boolean0) {
      if (float2 < 50.0F) {
        this.vehicleObject.engineSpeed =
            this.vehicleObject.engineSpeed -
            Math.min(0.06 * (this.vehicleObject.engineSpeed - 7000.0),
                     (double)(30.0F - float2)) *
                float0;
      }
    } else if (float2 < 30.0F) {
      this.vehicleObject.engineSpeed =
          this.vehicleObject.engineSpeed -
          Math.min(0.02 * (this.vehicleObject.engineSpeed - 7000.0),
                   (double)(30.0F - float2)) *
              float0;
    }

    this.EngineForce =
        (float)(this.vehicleObject.getEnginePower() *
                (0.5 + this.vehicleObject.engineSpeed / 24000.0));
    this.EngineForce = this.EngineForce - this.EngineForce * (float2 / 200.0F);
    bool boolean3 = false;
    if (this.vehicleObject.transmissionNumber == TransmissionNumber.Speed1 &&
        this.vehicleObject.getVehicleTowedBy() != nullptr) {
      if (this.vehicleObject.getVehicleTowedBy()
                  .getScript()
                  .getPassengerCount() == 0 &&
          this.vehicleObject.getVehicleTowedBy().getScript().getMass() >
              200.0F) {
        boolean3 = true;
      }

      if (float2 < (boolean3 ? 20 : 5)) {
        this.EngineForce =
            this.EngineForce *
            Math.min(1.2F,
                     this.vehicleObject.getVehicleTowedBy().getMass() / 500.0F);
        if (boolean3) {
          this.EngineForce *= 4.0F;
        }
      }
    }

    if (this.vehicleObject.engineSpeed > 6000.0) {
      this.EngineForce =
          (float)(this.EngineForce *
                  ((7000.0 - this.vehicleObject.engineSpeed) / 1000.0));
    }

    if (boolean1) {
      this.EngineForce *= 0.6F;
      if (float2 > 20.0F) {
        this.EngineForce *= (40.0F - float2) / 20.0F;
      }
    }

    if (boolean0) {
      if (float2 > this.vehicleObject.getMaxSpeed() * 1.15F) {
        this.EngineForce =
            this.EngineForce *
            ((this.vehicleObject.getMaxSpeed() * 1.15F + 20.0F - float2) /
             20.0F);
      }
    } else if (float2 > this.vehicleObject.getMaxSpeed()) {
      this.EngineForce =
          this.EngineForce *
          ((this.vehicleObject.getMaxSpeed() + 20.0F - float2) / 20.0F);
    }

    this.BrakingForce = 0.0F;
    if (this.clientControls.wasUsingParkingBrakes) {
      this.clientControls.wasUsingParkingBrakes = false;
      this.EngineForce *= 8.0F;
    }

    if (GameClient.bClient &&
        this.vehicleObject.jniSpeed >=
            ServerOptions.instance.SpeedLimit.getValue()) {
      this.EngineForce = 0.0F;
    }
  }

  void control_ForwardNew(float float4) {
    float float0 = GameTime.getInstance().getMultiplier() / 0.8F;
    IsoGameCharacter character = this.vehicleObject.getDriver();
    bool boolean0 = character != null && character.Traits.SpeedDemon.isSet();
    bool boolean1 = character != null && character.Traits.SundayDriver.isSet();
    int int0 = this.vehicleObject.getScript().gearRatioCount;
    float float1 = 0.0F;
    EngineRPMData[] engineRPMDatas =
        this.vehicleObject.getVehicleEngineRPM().m_rpmData;
    float float2 = this.vehicleObject.getMaxSpeed() / int0;
    float float3 = PZMath.clamp(float4, 0.0F, this.vehicleObject.getMaxSpeed());
    int int1 = (int)PZMath.floor(float3 / float2) + 1;
    int1 = PZMath.min(int1, int0);
    float1 = engineRPMDatas[int1 - 1].gearChange;
    TransmissionNumber transmissionNumber = TransmissionNumber.Speed1;
    switch (int1) {
    case 1:
      transmissionNumber = TransmissionNumber.Speed1;
      break;
    case 2:
      transmissionNumber = TransmissionNumber.Speed2;
      break;
    case 3:
      transmissionNumber = TransmissionNumber.Speed3;
      break;
    case 4:
      transmissionNumber = TransmissionNumber.Speed4;
      break;
    case 5:
      transmissionNumber = TransmissionNumber.Speed5;
      break;
    case 6:
      transmissionNumber = TransmissionNumber.Speed6;
      break;
    case 7:
      transmissionNumber = TransmissionNumber.Speed7;
      break;
    case 8:
      transmissionNumber = TransmissionNumber.Speed8;
    }

    if (this.vehicleObject.transmissionNumber == TransmissionNumber.N) {
      this.vehicleObject.transmissionNumber = transmissionNumber;
    } else if (this.vehicleObject.transmissionNumber.getIndex() - 1 >= 0 &&
               this.vehicleObject.transmissionNumber.getIndex() <
                   transmissionNumber.getIndex() &&
               this.vehicleObject.getEngineSpeed() >=
                   engineRPMDatas
                       [this.vehicleObject.transmissionNumber.getIndex() - 1]
                           .gearChange &&
               float4 >=
                   float2 * this.vehicleObject.transmissionNumber.getIndex()) {
      this.vehicleObject.transmissionNumber = transmissionNumber;
      this.vehicleObject.engineSpeed =
          engineRPMDatas[this.vehicleObject.transmissionNumber.getIndex() - 1]
              .afterGearChange;
    }

    if (this.vehicleObject.transmissionNumber.getIndex() < int0 &&
        this.vehicleObject.transmissionNumber.getIndex() - 1 >= 0) {
      this.vehicleObject.engineSpeed = Math.min(
          this.vehicleObject.engineSpeed,
          (double)(engineRPMDatas
                       [this.vehicleObject.transmissionNumber.getIndex() - 1]
                           .gearChange +
                   100.0F));
    }

    if (this.vehicleObject.engineSpeed > float1) {
      this.vehicleObject.engineSpeed =
          this.vehicleObject.engineSpeed -
          Math.min(0.5 * (this.vehicleObject.engineSpeed - float1), 10.0) *
              float0;
    } else {
      float float5 = switch (this.vehicleObject.transmissionNumber) {
                case Speed1 -> 10.0F;
                case Speed2 -> 8.0F;
                case Speed3 -> 7.0F;
                case Speed4 -> 6.0F;
                case Speed5 -> 5.0F;
                default -> 4.0F;
            };
            this.vehicleObject.engineSpeed += float5 * float0;
        }

    float float6 = this.vehicleObject.getEnginePower();
        float6 = this.vehicleObject.getScript().getEngineForce();

        float6 *= switch (this.vehicleObject.transmissionNumber) {
            case Speed1 -> 1.5F;
            default -> 1.0F;
        };
        this.EngineForce = (float)(float6 * (0.3F + this.vehicleObject.engineSpeed / 30000.0));
        this.EngineForce = this.EngineForce - this.EngineForce * (float4 / 200.0F);
    bool boolean2 = false;
        if (this.vehicleObject.transmissionNumber == TransmissionNumber.Speed1 && this.vehicleObject.getVehicleTowedBy() != nullptr) {
            if (this.vehicleObject.getVehicleTowedBy().getScript().getPassengerCount() == 0
                && this.vehicleObject.getVehicleTowedBy().getScript().getMass() > 200.0F) {
                boolean2 = true;
            }

            if (float4 < (boolean2 ? 20 : 5)) {
                    this.EngineForce =
                        this.EngineForce *
                        Math.min(
                            1.2F,
                            this.vehicleObject.getVehicleTowedBy().getMass() /
                                500.0F);
                    if (boolean2) {
                      this.EngineForce *= 4.0F;
                    }
                  }
                }

                if (this.vehicleObject.engineSpeed > 6000.0) {
                  this.EngineForce =
                      (float)(this.EngineForce *
                              ((7000.0 - this.vehicleObject.engineSpeed) /
                               1000.0));
                }

                if (boolean1) {
                  this.EngineForce *= 0.6F;
                  if (float4 > 20.0F) {
                    this.EngineForce *= (40.0F - float4) / 20.0F;
                  }
                }

                if (boolean0) {
                  if (float4 > this.vehicleObject.getMaxSpeed() * 1.15F) {
                    this.EngineForce =
                        this.EngineForce *
                        ((this.vehicleObject.getMaxSpeed() * 1.15F + 20.0F -
                          float4) /
                         20.0F);
                  }
                } else if (float4 > this.vehicleObject.getMaxSpeed()) {
                  this.EngineForce =
                      this.EngineForce *
                      ((this.vehicleObject.getMaxSpeed() + 20.0F - float4) /
                       20.0F);
                }

                this.BrakingForce = 0.0F;
                if (this.clientControls.wasUsingParkingBrakes) {
                  this.clientControls.wasUsingParkingBrakes = false;
                  this.EngineForce *= 8.0F;
                }

                if (GameClient.bClient &&
                    this.vehicleObject.jniSpeed >=
                        ServerOptions.instance.SpeedLimit.getValue()) {
                  this.EngineForce = 0.0F;
                }
    }

    void control_Reverse(float float1) {
      float float0 = GameTime.getInstance().getMultiplier() / 0.8F;
      float1 *= 1.5F;
      IsoGameCharacter character = this.vehicleObject.getDriver();
      bool boolean0 = character != null && character.Traits.SpeedDemon.isSet();
      bool boolean1 =
          character != null && character.Traits.SundayDriver.isSet();
      this.vehicleObject.transmissionNumber = TransmissionNumber.R;
      float float2 = 1000.0F * float1 / 30.0F;
      this.vehicleObject.engineSpeed =
          this.vehicleObject.engineSpeed -
          Math.min(0.5 * (this.vehicleObject.engineSpeed - float2), 100.0) *
              float0;
      if (boolean0) {
        this.vehicleObject.engineSpeed =
            this.vehicleObject.engineSpeed -
            Math.min(0.06 * (this.vehicleObject.engineSpeed - 7000.0),
                     (double)(30.0F - float1)) *
                float0;
      } else {
        this.vehicleObject.engineSpeed =
            this.vehicleObject.engineSpeed -
            Math.min(0.02 * (this.vehicleObject.engineSpeed - 7000.0),
                     (double)(30.0F - float1)) *
                float0;
      }

      this.EngineForce =
          (float)(-1.0F * this.vehicleObject.getEnginePower() *
                  (0.75 + this.vehicleObject.engineSpeed / 24000.0));
      if (this.vehicleObject.engineSpeed > 6000.0) {
        this.EngineForce =
            (float)(this.EngineForce *
                    ((7000.0 - this.vehicleObject.engineSpeed) / 1000.0));
      }

      if (boolean1) {
        this.EngineForce *= 0.7F;
        if (float1 < -5.0F) {
          this.EngineForce *= (15.0F + float1) / 10.0F;
        }
      }

      if (float1 < -30.0F) {
        this.EngineForce *= (40.0F + float1) / 10.0F;
      }

      this.BrakingForce = 0.0F;
    }

    void updateRammingSound(float float0) {
      if (this.vehicleObject.isEngineRunning() &&
          (float0 < 1.0F &&
               this.EngineForce >
                   this.vehicleObject.getScript().getEngineIdleSpeed() * 2.0F ||
           float0 > -0.5F &&
               this.EngineForce <
                   this.vehicleObject.getScript().getEngineIdleSpeed() *
                       -2.0F)) {
        if (this.vehicleObject.ramSound == 0L) {
          this.vehicleObject.ramSound = this.vehicleObject.playSoundImpl(
              "VehicleSkid", (IsoObject) nullptr);
          this.vehicleObject.ramSoundTime =
              System.currentTimeMillis() + 1000L + Rand.Next(2000);
        }

        if (this.vehicleObject.ramSound != 0L &&
            this.vehicleObject.ramSoundTime < System.currentTimeMillis()) {
          this.vehicleObject.stopSound(this.vehicleObject.ramSound);
          this.vehicleObject.ramSound = 0L;
        }
      } else if (this.vehicleObject.ramSound != 0L) {
        this.vehicleObject.stopSound(this.vehicleObject.ramSound);
        this.vehicleObject.ramSound = 0L;
      }
    }

    void updateBackSignal() {
      if (this.isGasR && this.vehicleObject.isEngineRunning() &&
          this.vehicleObject.hasBackSignal() &&
          !this.vehicleObject.isBackSignalEmitting()) {
        if (GameClient.bClient) {
          GameClient.instance.sendClientCommandV(
              (IsoPlayer)this.vehicleObject.getDriver(), "vehicle",
              "onBackSignal", "state", "start");
        } else {
          this.vehicleObject.onBackMoveSignalStart();
        }
      }

      if (!this.isGasR && this.vehicleObject.isBackSignalEmitting()) {
        if (GameClient.bClient) {
          GameClient.instance.sendClientCommandV(
              (IsoPlayer)this.vehicleObject.getDriver(), "vehicle",
              "onBackSignal", "state", "stop");
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
          GameClient.instance.sendClientCommandV(
              (IsoPlayer)this.vehicleObject.getDriver(), "vehicle",
              "setStoplightsOn", "on", Boolean.TRUE);
        }

        if (!GameServer.bServer) {
          this.vehicleObject.setStoplightsOn(true);
        }
      } else {
        if (!this.vehicleObject.getStoplightsOn()) {
          return;
        }

        if (GameClient.bClient) {
          GameClient.instance.sendClientCommandV(
              (IsoPlayer)this.vehicleObject.getDriver(), "vehicle",
              "setStoplightsOn", "on", Boolean.FALSE);
        }

        if (!GameServer.bServer) {
          this.vehicleObject.setStoplightsOn(false);
        }
      }
    }

    bool delayCommandWhileDrunk(bool var1) {
      this.drunkDelayCommandTimer =
          this.drunkDelayCommandTimer + GameTime.getInstance().getMultiplier();
      if (Rand.AdjustForFramerate(
              4 * this.vehicleObject.getDriver().getMoodles().getMoodleLevel(
                      MoodleType.Drunk)) < this.drunkDelayCommandTimer) {
        this.drunkDelayCommandTimer = 0.0F;
        return true;
      } else {
        return false;
      }
    }

    float delayCommandWhileDrunk(float float0) {
      this.drunkDelayCommandTimer =
          this.drunkDelayCommandTimer + GameTime.getInstance().getMultiplier();
      if (Rand.AdjustForFramerate(
              4 * this.vehicleObject.getDriver().getMoodles().getMoodleLevel(
                      MoodleType.Drunk)) < this.drunkDelayCommandTimer) {
        this.drunkDelayCommandTimer = 0.0F;
        return float0;
      } else {
        return 0.0F;
      }
    }

    void checkTire(CarController.BulletVariables bulletVariablesx) {
      if (this.vehicleObject.getPartById("TireFrontLeft") == nullptr ||
          this.vehicleObject.getPartById("TireFrontLeft").getInventoryItem() ==
              nullptr) {
        bulletVariablesx.brakingForce =
            (float)(bulletVariablesx.brakingForce / 1.2);
        bulletVariablesx.engineForce =
            (float)(bulletVariablesx.engineForce / 1.2);
      }

      if (this.vehicleObject.getPartById("TireFrontRight") == nullptr ||
          this.vehicleObject.getPartById("TireFrontRight").getInventoryItem() ==
              nullptr) {
        bulletVariablesx.brakingForce =
            (float)(bulletVariablesx.brakingForce / 1.2);
        bulletVariablesx.engineForce =
            (float)(bulletVariablesx.engineForce / 1.2);
      }

      if (this.vehicleObject.getPartById("TireRearLeft") == nullptr ||
          this.vehicleObject.getPartById("TireRearLeft").getInventoryItem() ==
              nullptr) {
        bulletVariablesx.brakingForce =
            (float)(bulletVariablesx.brakingForce / 1.3);
        bulletVariablesx.engineForce =
            (float)(bulletVariablesx.engineForce / 1.3);
      }

      if (this.vehicleObject.getPartById("TireRearRight") == nullptr ||
          this.vehicleObject.getPartById("TireRearRight").getInventoryItem() ==
              nullptr) {
        bulletVariablesx.brakingForce =
            (float)(bulletVariablesx.brakingForce / 1.3);
        bulletVariablesx.engineForce =
            (float)(bulletVariablesx.engineForce / 1.3);
      }
    }

    void updateControls() {
      if (!GameServer.bServer) {
        if (this.vehicleObject.isKeyboardControlled()) {
          bool boolean0 =
              GameKeyboard.isKeyDown(Core.getInstance().getKey("Left"));
          bool boolean1 =
              GameKeyboard.isKeyDown(Core.getInstance().getKey("Right"));
          bool boolean2 =
              GameKeyboard.isKeyDown(Core.getInstance().getKey("Forward"));
          bool boolean3 =
              GameKeyboard.isKeyDown(Core.getInstance().getKey("Backward"));
          bool boolean4 = GameKeyboard.isKeyDown(57);
          bool boolean5 = GameKeyboard.isKeyDown(42);
          this.clientControls.steering = 0.0F;
          if (boolean0) {
            this.clientControls.steering--;
          }

          if (boolean1) {
            this.clientControls.steering++;
          }

          this.clientControls.forward = boolean2;
          this.clientControls.backward = boolean3;
          this.clientControls.brake = boolean4;
          this.clientControls.shift = boolean5;
          if (this.clientControls.brake) {
            this.clientControls.wasUsingParkingBrakes = true;
          }
        }

        int int0 = this.vehicleObject.getJoypad();
        if (int0 != -1) {
          bool boolean6 = JoypadManager.instance.isLeftPressed(int0);
          bool boolean7 = JoypadManager.instance.isRightPressed(int0);
          bool boolean8 = JoypadManager.instance.isRTPressed(int0);
          bool boolean9 = JoypadManager.instance.isLTPressed(int0);
          bool boolean10 = JoypadManager.instance.isBPressed(int0);
          float float0 = JoypadManager.instance.getMovementAxisX(int0);
          this.clientControls.steering = float0;
          this.clientControls.forward = boolean8;
          this.clientControls.backward = boolean9;
          this.clientControls.brake = boolean10;
        }

        if (this.clientControls.forceBrake != 0L) {
          long long0 =
              System.currentTimeMillis() - this.clientControls.forceBrake;
          if (long0 > 0L && long0 < 1000L) {
            this.clientControls.brake = true;
            this.clientControls.shift = false;
          }
        }
      }
    }

    void park() {
      if (!GameServer.bServer &&
          this.vehicleObject.getScript().getWheelCount() > 0) {
        Bullet.controlVehicle(this.vehicleObject.VehicleID, 0.0F,
                              this.vehicleObject.getBrakingForce(), 0.0F);
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
        BaseVehicle vehicle = this.vehicleObject.getVehicleTowedBy();
        if (vehicle == nullptr) {
          float float0 =
              this.vehicleObject.isEngineRunning() ? this.EngineForce : 0.0F;
          return Math.abs(float0) > 0.01F;
        } else {
          return vehicle.getController() == nullptr
                     ? false
                     : vehicle.getController().shouldBeActive();
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
          this.atRestTimer =
              this.atRestTimer - GameTime.getInstance().getTimeDelta();
        }

        if (this.atRestTimer <= 0.0F) {
          Bullet.setVehicleActive(this.vehicleObject.VehicleID, false);
          this.isEnable = false;
        }
      }
    }

    bool isGasPedalPressed() { return this.isGas || this.isGasR; }

    bool isBrakePedalPressed() { return this.isBreak; }

    void debug() {
      if (Core.bDebug &&
          DebugOptions.instance.VehicleRenderOutline.getValue()) {
        VehicleScript vehicleScript = this.vehicleObject.getScript();
        Vector3f vector3f = this.tempVec3f;
        this.vehicleObject.getForwardVector(vector3f);
        Transform transform = this.tempXfrm;
        this.vehicleObject.getWorldTransform(transform);
        PolygonalMap2.VehiclePoly vehiclePoly = this.vehicleObject.getPoly();
        LineDrawer.addLine(vehiclePoly.x1, vehiclePoly.y1, 0.0F, vehiclePoly.x2,
                           vehiclePoly.y2, 0.0F, 1.0F, 1.0F, 1.0F, nullptr,
                           true);
        LineDrawer.addLine(vehiclePoly.x2, vehiclePoly.y2, 0.0F, vehiclePoly.x3,
                           vehiclePoly.y3, 0.0F, 1.0F, 1.0F, 1.0F, nullptr,
                           true);
        LineDrawer.addLine(vehiclePoly.x3, vehiclePoly.y3, 0.0F, vehiclePoly.x4,
                           vehiclePoly.y4, 0.0F, 1.0F, 1.0F, 1.0F, nullptr,
                           true);
        LineDrawer.addLine(vehiclePoly.x4, vehiclePoly.y4, 0.0F, vehiclePoly.x1,
                           vehiclePoly.y1, 0.0F, 1.0F, 1.0F, 1.0F, nullptr,
                           true);
        _UNIT_Y.set(0.0F, 1.0F, 0.0F);

        for (int int0 = 0;
             int0 < this.vehicleObject.getScript().getWheelCount(); int0++) {
          VehicleScript.Wheel wheel = vehicleScript.getWheel(int0);
          this.tempVec3f.set(wheel.getOffset());
          if (vehicleScript.getModel() != nullptr) {
            this.tempVec3f.add(vehicleScript.getModelOffset());
          }

          this.vehicleObject.getWorldPos(this.tempVec3f, this.tempVec3f);
          float float0 = this.tempVec3f.x;
          float float1 = this.tempVec3f.y;
          this.vehicleObject.getWheelForwardVector(int0, this.tempVec3f);
          LineDrawer.addLine(float0, float1, 0.0F, float0 + this.tempVec3f.x,
                             float1 + this.tempVec3f.z, 0.0F, 1.0F, 1.0F, 1.0F,
                             nullptr, true);
          this.drawRect(this.tempVec3f,
                        float0 - WorldSimulation.instance.offsetX,
                        float1 - WorldSimulation.instance.offsetY, wheel.width,
                        wheel.radius);
        }

        if (this.vehicleObject.collideX != -1.0F) {
          this.vehicleObject.getForwardVector(vector3f);
          this.drawCircle(this.vehicleObject.collideX,
                          this.vehicleObject.collideY, 0.3F);
          this.vehicleObject.collideX = -1.0F;
          this.vehicleObject.collideY = -1.0F;
        }

        int int1 = this.vehicleObject.getJoypad();
        if (int1 != -1) {
          float float2 = JoypadManager.instance.getMovementAxisX(int1);
          float float3 = JoypadManager.instance.getMovementAxisY(int1);
          float float4 = JoypadManager.instance.getDeadZone(int1, 0);
          if (Math.abs(float3) > float4 || Math.abs(float2) > float4) {
            Vector2 vector = this.tempVec2.set(float2, float3);
            vector.setLength(4.0F);
            vector.rotate((float)(-Math.PI / 4));
            LineDrawer.addLine(
                this.vehicleObject.getX(), this.vehicleObject.getY(),
                this.vehicleObject.z, this.vehicleObject.getX() + vector.x,
                this.vehicleObject.getY() + vector.y, this.vehicleObject.z,
                1.0F, 1.0F, 1.0F, nullptr, true);
          }
        }

        float float5 = this.vehicleObject.x;
        float float6 = this.vehicleObject.y;
        float float7 = this.vehicleObject.z;
        LineDrawer.DrawIsoLine(float5 - 0.5F, float6, float7, float5 + 0.5F,
                               float6, float7, 1.0F, 1.0F, 1.0F, 0.25F, 1);
        LineDrawer.DrawIsoLine(float5, float6 - 0.5F, float7, float5,
                               float6 + 0.5F, float7, 1.0F, 1.0F, 1.0F, 0.25F,
                               1);
      }
    }

    void drawRect(Vector3f vec, float x, float y, float w, float h) {
      this.drawRect(vec, x, y, w, h, 1.0F, 1.0F, 1.0F);
    }

    void drawRect(Vector3f vec, float x, float y, float w, float h, float r,
                  float g, float b) {
      float float0 = vec.x;
      float float1 = vec.y;
      float float2 = vec.z;
      Vector3f vector3f = this.tempVec3f_3;
      vec.cross(_UNIT_Y, vector3f);
      float float3 = 1.0F;
      vec.x *= float3 * h;
      vec.z *= float3 * h;
      vector3f.x *= float3 * w;
      vector3f.z *= float3 * w;
      float float4 = x + vec.x;
      float float5 = y + vec.z;
      float float6 = x - vec.x;
      float float7 = y - vec.z;
      float float8 = float4 - vector3f.x / 2.0F;
      float float9 = float4 + vector3f.x / 2.0F;
      float float10 = float6 - vector3f.x / 2.0F;
      float float11 = float6 + vector3f.x / 2.0F;
      float float12 = float7 - vector3f.z / 2.0F;
      float float13 = float7 + vector3f.z / 2.0F;
      float float14 = float5 - vector3f.z / 2.0F;
      float float15 = float5 + vector3f.z / 2.0F;
      float8 += WorldSimulation.instance.offsetX;
      float14 += WorldSimulation.instance.offsetY;
      float9 += WorldSimulation.instance.offsetX;
      float15 += WorldSimulation.instance.offsetY;
      float10 += WorldSimulation.instance.offsetX;
      float12 += WorldSimulation.instance.offsetY;
      float11 += WorldSimulation.instance.offsetX;
      float13 += WorldSimulation.instance.offsetY;
      LineDrawer.addLine(float8, float14, 0.0F, float9, float15, 0.0F, r, g, b,
                         nullptr, true);
      LineDrawer.addLine(float8, float14, 0.0F, float10, float12, 0.0F, r, g, b,
                         nullptr, true);
      LineDrawer.addLine(float9, float15, 0.0F, float11, float13, 0.0F, r, g, b,
                         nullptr, true);
      LineDrawer.addLine(float10, float12, 0.0F, float11, float13, 0.0F, r, g,
                         b, nullptr, true);
      vec.set(float0, float1, float2);
    }

    void drawCircle(float x, float y, float radius) {
      this.drawCircle(x, y, radius, 1.0F, 1.0F, 1.0F, 1.0F);
    }

    void drawCircle(float x, float y, float radius, float r, float g, float b,
                    float a) {
      LineDrawer.DrawIsoCircle(x, y, 0.0F, radius, 16, r, g, b, a);
    }

    static {
      gears[0] = new CarController.GearInfo(0, 25, 0.0F);
      gears[1] = new CarController.GearInfo(25, 50, 0.5F);
      gears[2] = new CarController.GearInfo(50, 1000, 0.5F);
    }

  public
    static final class BulletVariables {
      float engineForce;
      float brakingForce;
      float vehicleSteering;
      BaseVehicle vehicle;

      CarController.BulletVariables set(BaseVehicle vehiclex, float float0,
                                        float float1, float float2) {
        this.vehicle = vehiclex;
        this.engineForce = float0;
        this.brakingForce = float1;
        this.vehicleSteering = float2;
        return this;
      }
    }

    public static final class ClientControls {
      float steering;
      bool forward;
      bool backward;
      bool brake;
      bool shift;
      bool wasUsingParkingBrakes;
      long forceBrake = 0L;

      void reset() {
        this.steering = 0.0F;
        this.forward = false;
        this.backward = false;
        this.brake = false;
        this.shift = false;
        this.wasUsingParkingBrakes = false;
        this.forceBrake = 0L;
      }
    }

    static enum ControlState {
      NoControl, Braking, Forward, Reverse;
    }

    public static final class GearInfo {
      int minSpeed;
      int maxSpeed;
      float minRPM;

      GearInfo(int int0, int int1, float float0) {
        this.minSpeed = int0;
        this.maxSpeed = int1;
        this.minRPM = float0;
      }
    }
  }
} // namespace physics
} // namespace physics
} // namespace core
