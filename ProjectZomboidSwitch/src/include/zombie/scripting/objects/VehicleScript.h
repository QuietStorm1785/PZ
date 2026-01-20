#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/list/array/TFloatArrayList.h"
#include "org/joml/Vector2f.h"
#include "org/joml/Vector2i.h"
#include "org/joml/Vector3f.h"
#include "org/joml/Vector4f.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/SystemDisabler.h"
#include "zombie/core/ImmutableColor.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/physics/Bullet.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/GameServer.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/ScriptParser.h"
#include "zombie/scripting/ScriptParser/Block.h"
#include "zombie/scripting/ScriptParser/BlockElement.h"
#include "zombie/scripting/ScriptParser/Value.h"
#include "zombie/scripting/objects/VehicleScript/Anim.h"
#include "zombie/scripting/objects/VehicleScript/Area.h"
#include "zombie/scripting/objects/VehicleScript/Container.h"
#include "zombie/scripting/objects/VehicleScript/Door.h"
#include "zombie/scripting/objects/VehicleScript/LightBar.h"
#include "zombie/scripting/objects/VehicleScript/Model.h"
#include "zombie/scripting/objects/VehicleScript/Part.h"
#include "zombie/scripting/objects/VehicleScript/Passenger.h"
#include "zombie/scripting/objects/VehicleScript/Passenger/SwitchSeat.h"
#include "zombie/scripting/objects/VehicleScript/PhysicsShape.h"
#include "zombie/scripting/objects/VehicleScript/Position.h"
#include "zombie/scripting/objects/VehicleScript/Skin.h"
#include "zombie/scripting/objects/VehicleScript/Sounds.h"
#include "zombie/scripting/objects/VehicleScript/Wheel.h"
#include "zombie/scripting/objects/VehicleScript/Window.h"
#include "zombie/util/StringUtils.h"
#include "zombie/vehicles/BaseVehicle.h"
#include <algorithm>

namespace zombie {
namespace scripting {
namespace objects {


class VehicleScript : public BaseScriptObject {
public:
    std::string fileName;
    std::string name;
   private const std::vector<Model> models = std::make_unique<std::vector<>>();
   public const std::vector<ModelAttachment> m_attachments = std::make_unique<std::vector<>>();
    float mass = 800.0F;
    const Vector3f centerOfMassOffset = std::make_shared<Vector3f>();
    float engineForce = 3000.0F;
    float engineIdleSpeed = 750.0F;
    float steeringIncrement = 0.04F;
    float steeringClamp = 0.4F;
    float steeringClampMax = 0.9F;
    float wheelFriction = 800.0F;
    float stoppingMovementForce = 1.0F;
    float suspensionStiffness = 20.0F;
    float suspensionDamping = 2.3F;
    float suspensionCompression = 4.4F;
    float suspensionRestLength = 0.6F;
    float maxSuspensionTravelCm = 500.0F;
    float rollInfluence = 0.1F;
    const Vector3f extents = std::make_shared<Vector3f>(0.75F, 0.5F, 2.0F);
    const Vector2f shadowExtents = std::make_shared<Vector2f>(0.0F, 0.0F);
    const Vector2f shadowOffset = std::make_shared<Vector2f>(0.0F, 0.0F);
    bool bHadShadowOExtents = false;
    bool bHadShadowOffset = false;
    const Vector2f extentsOffset = std::make_shared<Vector2f>(0.5F, 0.5F);
    const Vector3f physicsChassisShape = std::make_shared<Vector3f>(0.75F, 0.5F, 1.0F);
   private const std::vector<PhysicsShape> m_physicsShapes = std::make_unique<std::vector<>>();
   private const std::vector<Wheel> wheels = std::make_unique<std::vector<>>();
   private const std::vector<Passenger> passengers = std::make_unique<std::vector<>>();
    float maxSpeed = 20.0F;
    bool isSmallVehicle = true;
    float spawnOffsetY = 0.0F;
    int frontEndHealth = 100;
    int rearEndHealth = 100;
    int storageCapacity = 100;
    int engineLoudness = 100;
    int engineQuality = 100;
    int seats = 2;
    int mechanicType;
    int engineRepairLevel;
    float playerDamageProtection;
    float forcedHue = -1.0F;
    float forcedSat = -1.0F;
    float forcedVal = -1.0F;
    ImmutableColor leftSirenCol;
    ImmutableColor rightSirenCol;
    std::string engineRPMType = "jeep";
    float offroadEfficiency = 1.0F;
    const TFloatArrayList crawlOffsets = std::make_shared<TFloatArrayList>();
    int gearRatioCount = 0;
   public const float[] gearRatio = new float[9];
    const Skin textures = std::make_shared<Skin>();
   private const std::vector<Skin> skins = std::make_unique<std::vector<>>();
   private const std::vector<Area> areas = std::make_unique<std::vector<>>();
   private const std::vector<Part> parts = std::make_unique<std::vector<>>();
    bool hasSiren = false;
    const LightBar lightbar = std::make_shared<LightBar>();
    const Sounds sound = std::make_shared<Sounds>();
    bool textureMaskEnable = false;
    static const int PHYSICS_SHAPE_BOX = 1;
    static const int PHYSICS_SHAPE_SPHERE = 2;

    public VehicleScript() {
      this.gearRatioCount = 4;
      this.gearRatio[0] = 7.09F;
      this.gearRatio[1] = 6.44F;
      this.gearRatio[2] = 4.1F;
      this.gearRatio[3] = 2.29F;
      this.gearRatio[4] = 1.47F;
      this.gearRatio[5] = 1.0F;
   }

    void Load(const std::string& var1, const std::string& var2) {
    ScriptManager var3 = ScriptManager.instance;
      this.fileName = var3.currentFileName;
      if (!var3.scriptsWithVehicles.contains(this.fileName)) {
         var3.scriptsWithVehicles.push_back(this.fileName);
      }

      this.name = var1;
    Block var4 = ScriptParser.parse(var2);
      var4 = (Block)var4.children.get(0);

      for (BlockElement var6 : var4.elements) {
         if (var6.asValue() != nullptr) {
            std::string[] var14 = var6.asValue().string.split("=");
    std::string var20 = var14[0].trim();
    std::string var24 = var14[1].trim();
            if ("extents" == var20)) {
               this.LoadVector3f(var24, this.extents);
            } else if ("shadowExtents" == var20)) {
               this.LoadVector2f(var24, this.shadowExtents);
               this.bHadShadowOExtents = true;
            } else if ("shadowOffset" == var20)) {
               this.LoadVector2f(var24, this.shadowOffset);
               this.bHadShadowOffset = true;
            } else if ("physicsChassisShape" == var20)) {
               this.LoadVector3f(var24, this.physicsChassisShape);
            } else if ("extentsOffset" == var20)) {
               this.LoadVector2f(var24, this.extentsOffset);
            } else if ("mass" == var20)) {
               this.mass = float.parseFloat(var24);
            } else if ("offRoadEfficiency".equalsIgnoreCase(var20)) {
               this.offroadEfficiency = float.parseFloat(var24);
            } else if ("centerOfMassOffset" == var20)) {
               this.LoadVector3f(var24, this.centerOfMassOffset);
            } else if ("engineForce" == var20)) {
               this.engineForce = float.parseFloat(var24);
            } else if ("engineIdleSpeed" == var20)) {
               this.engineIdleSpeed = float.parseFloat(var24);
            } else if ("gearRatioCount" == var20)) {
               this.gearRatioCount = int.parseInt(var24);
            } else if ("gearRatioR" == var20)) {
               this.gearRatio[0] = float.parseFloat(var24);
            } else if ("gearRatio1" == var20)) {
               this.gearRatio[1] = float.parseFloat(var24);
            } else if ("gearRatio2" == var20)) {
               this.gearRatio[2] = float.parseFloat(var24);
            } else if ("gearRatio3" == var20)) {
               this.gearRatio[3] = float.parseFloat(var24);
            } else if ("gearRatio4" == var20)) {
               this.gearRatio[4] = float.parseFloat(var24);
            } else if ("gearRatio5" == var20)) {
               this.gearRatio[5] = float.parseFloat(var24);
            } else if ("gearRatio6" == var20)) {
               this.gearRatio[6] = float.parseFloat(var24);
            } else if ("gearRatio7" == var20)) {
               this.gearRatio[7] = float.parseFloat(var24);
            } else if ("gearRatio8" == var20)) {
               this.gearRatio[8] = float.parseFloat(var24);
            } else if ("textureMaskEnable" == var20)) {
               this.textureMaskEnable = bool.parseBoolean(var24);
            } else if ("textureRust" == var20)) {
               this.textures.textureRust = StringUtils.discardNullOrWhitespace(var24);
            } else if ("textureMask" == var20)) {
               this.textures.textureMask = StringUtils.discardNullOrWhitespace(var24);
            } else if ("textureLights" == var20)) {
               this.textures.textureLights = StringUtils.discardNullOrWhitespace(var24);
            } else if ("textureDamage1Overlay" == var20)) {
               this.textures.textureDamage1Overlay = StringUtils.discardNullOrWhitespace(var24);
            } else if ("textureDamage1Shell" == var20)) {
               this.textures.textureDamage1Shell = StringUtils.discardNullOrWhitespace(var24);
            } else if ("textureDamage2Overlay" == var20)) {
               this.textures.textureDamage2Overlay = StringUtils.discardNullOrWhitespace(var24);
            } else if ("textureDamage2Shell" == var20)) {
               this.textures.textureDamage2Shell = StringUtils.discardNullOrWhitespace(var24);
            } else if ("textureShadow" == var20)) {
               this.textures.textureShadow = StringUtils.discardNullOrWhitespace(var24);
            } else if ("rollInfluence" == var20)) {
               this.rollInfluence = float.parseFloat(var24);
            } else if ("steeringIncrement" == var20)) {
               this.steeringIncrement = float.parseFloat(var24);
            } else if ("steeringClamp" == var20)) {
               this.steeringClamp = float.parseFloat(var24);
            } else if ("suspensionStiffness" == var20)) {
               this.suspensionStiffness = float.parseFloat(var24);
            } else if ("suspensionDamping" == var20)) {
               this.suspensionDamping = float.parseFloat(var24);
            } else if ("suspensionCompression" == var20)) {
               this.suspensionCompression = float.parseFloat(var24);
            } else if ("suspensionRestLength" == var20)) {
               this.suspensionRestLength = float.parseFloat(var24);
            } else if ("maxSuspensionTravelCm" == var20)) {
               this.maxSuspensionTravelCm = float.parseFloat(var24);
            } else if ("wheelFriction" == var20)) {
               this.wheelFriction = float.parseFloat(var24);
            } else if ("stoppingMovementForce" == var20)) {
               this.stoppingMovementForce = float.parseFloat(var24);
            } else if ("maxSpeed" == var20)) {
               this.maxSpeed = float.parseFloat(var24);
            } else if ("isSmallVehicle" == var20)) {
               this.isSmallVehicle = bool.parseBoolean(var24);
            } else if ("spawnOffsetY" == var20)) {
               this.spawnOffsetY = float.parseFloat(var24) - 0.995F;
            } else if ("frontEndDurability" == var20)) {
               this.frontEndHealth = int.parseInt(var24);
            } else if ("rearEndDurability" == var20)) {
               this.rearEndHealth = int.parseInt(var24);
            } else if ("storageCapacity" == var20)) {
               this.storageCapacity = int.parseInt(var24);
            } else if ("engineLoudness" == var20)) {
               this.engineLoudness = int.parseInt(var24);
            } else if ("engineQuality" == var20)) {
               this.engineQuality = int.parseInt(var24);
            } else if ("seats" == var20)) {
               this.seats = int.parseInt(var24);
            } else if ("hasSiren" == var20)) {
               this.hasSiren = bool.parseBoolean(var24);
            } else if ("mechanicType" == var20)) {
               this.mechanicType = int.parseInt(var24);
            } else if ("forcedColor" == var20)) {
               std::string[] var28 = var24.split(" ");
               this.setForcedHue(float.parseFloat(var28[0]));
               this.setForcedSat(float.parseFloat(var28[1]));
               this.setForcedVal(float.parseFloat(var28[2]));
            } else if ("engineRPMType" == var20)) {
               this.engineRPMType = var24.trim();
            } else if ("template" == var20)) {
               this.LoadTemplate(var24);
            } else if ("template!" == var20)) {
    VehicleTemplate var30 = ScriptManager.instance.getVehicleTemplate(var24);
               if (var30 == nullptr) {
                  DebugLog.log("ERROR: template \"" + var24 + "\" not found");
               } else {
                  this.Load(var1, var30.body);
               }
            } else if ("engineRepairLevel" == var20)) {
               this.engineRepairLevel = int.parseInt(var24);
            } else if ("playerDamageProtection" == var20)) {
               this.setPlayerDamageProtection(float.parseFloat(var24));
            }
         } else {
    Block var7 = var6.asBlock();
            if ("area" == var7.type)) {
               this.LoadArea(var7);
            } else if ("attachment" == var7.type)) {
               this.LoadAttachment(var7);
            } else if ("model" == var7.type)) {
               this.LoadModel(var7, this.models);
            } else if ("part" == var7.type)) {
               if (var7.id != nullptr && var7.id.contains("*")) {
    std::string var19 = var7.id;

                  for (Part var27 : this.parts) {
                     if (this.globMatch(var19, var27.id)) {
                        var7.id = var27.id;
                        this.LoadPart(var7);
                     }
                  }
               } else {
                  this.LoadPart(var7);
               }
            } else if ("passenger" == var7.type)) {
               if (var7.id != nullptr && var7.id.contains("*")) {
    std::string var18 = var7.id;

                  for (Passenger var26 : this.passengers) {
                     if (this.globMatch(var18, var26.id)) {
                        var7.id = var26.id;
                        this.LoadPassenger(var7);
                     }
                  }
               } else {
                  this.LoadPassenger(var7);
               }
            } else if ("physics" == var7.type)) {
    PhysicsShape var17 = this.LoadPhysicsShape(var7);
               if (var17 != nullptr && this.m_physicsShapes.size() < 10) {
                  this.m_physicsShapes.push_back(var17);
               }
            } else if ("skin" == var7.type)) {
    Skin var16 = this.LoadSkin(var7);
               if (!StringUtils.isNullOrWhitespace(var16.texture)) {
                  this.skins.push_back(var16);
               }
            } else if ("wheel" == var7.type)) {
               this.LoadWheel(var7);
            } else if ("lightbar" == var7.type)) {
               for (Value var21 : var7.values) {
    std::string var25 = var21.getKey().trim();
    std::string var29 = var21.getValue().trim();
                  if ("soundSiren" == var25)) {
                     this.lightbar.soundSiren0 = var29 + "Yelp";
                     this.lightbar.soundSiren1 = var29 + "Wall";
                     this.lightbar.soundSiren2 = var29 + "Alarm";
                  }

                  if ("soundSiren0" == var25)) {
                     this.lightbar.soundSiren0 = var29;
                  }

                  if ("soundSiren1" == var25)) {
                     this.lightbar.soundSiren1 = var29;
                  }

                  if ("soundSiren2" == var25)) {
                     this.lightbar.soundSiren2 = var29;
                  }

                  if ("leftCol" == var25)) {
                     std::string[] var12 = var29.split(";");
                     this.leftSirenCol = std::make_shared<ImmutableColor>(float.parseFloat(var12[0]), float.parseFloat(var12[1]), float.parseFloat(var12[2]));
                  }

                  if ("rightCol" == var25)) {
                     std::string[] var31 = var29.split(";");
                     this.rightSirenCol = std::make_shared<ImmutableColor>(float.parseFloat(var31[0]), float.parseFloat(var31[1]), float.parseFloat(var31[2]));
                  }

                  this.lightbar.enable = true;
                  if (this.getPartById("lightbar") == nullptr) {
    Part var32 = std::make_shared<Part>();
                     var32.id = "lightbar";
                     this.parts.push_back(var32);
                  }
               }
            } else if ("sound" == var7.type)) {
               for (Value var9 : var7.values) {
    std::string var10 = var9.getKey().trim();
    std::string var11 = var9.getValue().trim();
                  if ("backSignal" == var10)) {
                     this.sound.backSignal = StringUtils.discardNullOrWhitespace(var11);
                     this.sound.backSignalEnable = this.sound.backSignal != nullptr;
                  } else if ("engine" == var10)) {
                     this.sound.engine = StringUtils.discardNullOrWhitespace(var11);
                  } else if ("engineStart" == var10)) {
                     this.sound.engineStart = StringUtils.discardNullOrWhitespace(var11);
                  } else if ("engineTurnOff" == var10)) {
                     this.sound.engineTurnOff = StringUtils.discardNullOrWhitespace(var11);
                  } else if ("horn" == var10)) {
                     this.sound.horn = StringUtils.discardNullOrWhitespace(var11);
                     this.sound.hornEnable = this.sound.horn != nullptr;
                  } else if ("ignitionFail" == var10)) {
                     this.sound.ignitionFail = StringUtils.discardNullOrWhitespace(var11);
                  } else if ("ignitionFailNoPower" == var10)) {
                     this.sound.ignitionFailNoPower = StringUtils.discardNullOrWhitespace(var11);
                  }
               }
            }
         }
      }
   }

    std::string getFileName() {
      return this.fileName;
   }

    void Loaded() {
    float var1 = this.getModelScale();
      this.extents.mul(var1);
      this.maxSuspensionTravelCm *= var1;
      this.suspensionRestLength *= var1;
      this.centerOfMassOffset.mul(var1);
      this.physicsChassisShape.mul(var1);
      if (this.bHadShadowOExtents) {
         this.shadowExtents.mul(var1);
      } else {
         this.shadowExtents.set(this.extents.x(), this.extents.z());
      }

      if (this.bHadShadowOffset) {
         this.shadowOffset.mul(var1);
      } else {
         this.shadowOffset.set(this.centerOfMassOffset.x(), this.centerOfMassOffset.z());
      }

      for (Model var3 : this.models) {
         var3.offset.mul(var1);
      }

      for (ModelAttachment var12 : this.m_attachments) {
         var12.getOffset().mul(var1);
      }

      for (PhysicsShape var13 : this.m_physicsShapes) {
         var13.offset.mul(var1);
         switch (var13.type) {
            case 1:
               var13.extents.mul(var1);
               break;
            case 2:
               var13.radius *= var1;
         }
      }

      for (Wheel var14 : this.wheels) {
         var14.radius *= var1;
         var14.offset.mul(var1);
      }

      for (Area var15 : this.areas) {
         var15.x *= var1;
         var15.y *= var1;
         var15.w *= var1;
         var15.h *= var1;
      }

      if (!this.extents == this.physicsChassisShape)) {
         DebugLog.Script.warn("vehicle \"" + this.name + "\" extents != physicsChassisShape");
      }

      for (int var10 = 0; var10 < this.passengers.size(); var10++) {
    Passenger var16 = this.passengers.get(var10);

         for (int var4 = 0; var4 < var16.getPositionCount(); var4++) {
    Position var5 = var16.getPosition(var4);
            var5.getOffset().mul(var1);
         }

         for (int var18 = 0; var18 < var16.switchSeats.size(); var18++) {
    SwitchSeat var20 = (SwitchSeat)var16.switchSeats.get(var18);
            var20.seat = this.getPassengerIndex(var20.id);

            assert var20.seat != -1;
         }
      }

      for (int var11 = 0; var11 < this.parts.size(); var11++) {
    Part var17 = this.parts.get(var11);
         if (var17.container != nullptr && var17.container.seatID != nullptr && !var17.container.seatID.empty()) {
            var17.container.seat = this.getPassengerIndex(var17.container.seatID);
         }

         if (var17.specificItem && var17.itemType != nullptr) {
            for (int var19 = 0; var19 < var17.itemType.size(); var19++) {
               var17.itemType.set(var19, (std::string)var17.itemType.get(var19) + this.mechanicType);
            }
         }
      }

      this.initCrawlOffsets();
      if (!GameServer.bServer) {
         this.toBullet();
      }
   }

    void toBullet() {
      float[] var1 = new float[200];
    int var2 = 0;
      var1[var2++] = this.getModelScale();
      var1[var2++] = this.extents.x;
      var1[var2++] = this.extents.y;
      var1[var2++] = this.extents.z;
      var1[var2++] = this.physicsChassisShape.x;
      var1[var2++] = this.physicsChassisShape.y;
      var1[var2++] = this.physicsChassisShape.z;
      var1[var2++] = this.mass;
      var1[var2++] = this.centerOfMassOffset.x;
      var1[var2++] = this.centerOfMassOffset.y;
      var1[var2++] = this.centerOfMassOffset.z;
      var1[var2++] = this.rollInfluence;
      var1[var2++] = this.suspensionStiffness;
      var1[var2++] = this.suspensionCompression;
      var1[var2++] = this.suspensionDamping;
      var1[var2++] = this.maxSuspensionTravelCm;
      var1[var2++] = this.suspensionRestLength;
      if (SystemDisabler.getdoHighFriction()) {
         var1[var2++] = this.wheelFriction * 100.0F;
      } else {
         var1[var2++] = this.wheelFriction;
      }

      var1[var2++] = this.stoppingMovementForce;
      var1[var2++] = this.getWheelCount();

      for (int var3 = 0; var3 < this.getWheelCount(); var3++) {
    Wheel var4 = this.getWheel(var3);
         var1[var2++] = var4.front ? 1.0F : 0.0F;
         var1[var2++] = var4.offset.x + this.getModel().offset.x - 0.0F * this.centerOfMassOffset.x;
         var1[var2++] = var4.offset.y + this.getModel().offset.y - 0.0F * this.centerOfMassOffset.y + 1.0F * this.suspensionRestLength;
         var1[var2++] = var4.offset.z + this.getModel().offset.z - 0.0F * this.centerOfMassOffset.z;
         var1[var2++] = var4.radius;
      }

      var1[var2++] = this.m_physicsShapes.size() + 1;
      var1[var2++] = 1.0F;
      var1[var2++] = this.centerOfMassOffset.x;
      var1[var2++] = this.centerOfMassOffset.y;
      var1[var2++] = this.centerOfMassOffset.z;
      var1[var2++] = this.physicsChassisShape.x;
      var1[var2++] = this.physicsChassisShape.y;
      var1[var2++] = this.physicsChassisShape.z;
      var1[var2++] = 0.0F;
      var1[var2++] = 0.0F;
      var1[var2++] = 0.0F;

      for (int var48 = 0; var48 < this.m_physicsShapes.size(); var48++) {
    PhysicsShape var49 = this.m_physicsShapes.get(var48);
         var1[var2++] = var49.type;
         var1[var2++] = var49.offset.x;
         var1[var2++] = var49.offset.y;
         var1[var2++] = var49.offset.z;
         if (var49.type == 1) {
            var1[var2++] = var49.extents.x;
            var1[var2++] = var49.extents.y;
            var1[var2++] = var49.extents.z;
            var1[var2++] = var49.rotate.x;
            var1[var2++] = var49.rotate.y;
            var1[var2++] = var49.rotate.z;
         } else if (var49.type == 2) {
            var1[var2++] = var49.radius;
         }
      }

      Bullet.defineVehicleScript(this.getFullName(), var1);
   }

    void LoadVector2f(const std::string& var1, Vector2f var2) {
      std::string[] var3 = var1.split(" ");
      var2.set(float.parseFloat(var3[0]), float.parseFloat(var3[1]));
   }

    void LoadVector3f(const std::string& var1, Vector3f var2) {
      std::string[] var3 = var1.split(" ");
      var2.set(float.parseFloat(var3[0]), float.parseFloat(var3[1]), float.parseFloat(var3[2]));
   }

    void LoadVector4f(const std::string& var1, Vector4f var2) {
      std::string[] var3 = var1.split(" ");
      var2.set(float.parseFloat(var3[0]), float.parseFloat(var3[1]), float.parseFloat(var3[2]), float.parseFloat(var3[3]));
   }

    void LoadVector2i(const std::string& var1, Vector2i var2) {
      std::string[] var3 = var1.split(" ");
      var2.set(int.parseInt(var3[0]), int.parseInt(var3[1]));
   }

    ModelAttachment LoadAttachment(Block var1) {
    ModelAttachment var2 = this.getAttachmentById(var1.id);
      if (var2 == nullptr) {
         var2 = std::make_shared<ModelAttachment>(var1.id);
         this.m_attachments.push_back(var2);
      }

      for (Value var4 : var1.values) {
    std::string var5 = var4.getKey().trim();
    std::string var6 = var4.getValue().trim();
         if ("bone" == var5)) {
            var2.setBone(var6);
         } else if ("offset" == var5)) {
            this.LoadVector3f(var6, var2.getOffset());
         } else if ("rotate" == var5)) {
            this.LoadVector3f(var6, var2.getRotate());
         } else if ("canAttach" == var5)) {
            var2.setCanAttach(new std::vector<>(Arrays.asList(var6.split(","))));
         } else if ("zoffset" == var5)) {
            var2.setZOffset(float.parseFloat(var6));
         } else if ("updateconstraint" == var5)) {
            var2.setUpdateConstraint(bool.parseBoolean(var6));
         }
      }

    return var2;
   }

    Model LoadModel(Block var1, std::vector<Model> var2) {
    Model var3 = this.getModelById(var1.id, var2);
      if (var3 == nullptr) {
         var3 = std::make_unique<Model>();
         var3.id = var1.id;
         var2.push_back(var3);
      }

      for (Value var5 : var1.values) {
    std::string var6 = var5.getKey().trim();
    std::string var7 = var5.getValue().trim();
         if ("file" == var6)) {
            var3.file = var7;
         } else if ("offset" == var6)) {
            this.LoadVector3f(var7, var3.offset);
         } else if ("rotate" == var6)) {
            this.LoadVector3f(var7, var3.rotate);
         } else if ("scale" == var6)) {
            var3.scale = float.parseFloat(var7);
         }
      }

    return var3;
   }

    Skin LoadSkin(Block var1) {
    Skin var2 = std::make_shared<Skin>();

      for (Value var4 : var1.values) {
    std::string var5 = var4.getKey().trim();
    std::string var6 = var4.getValue().trim();
         if ("texture" == var5)) {
            var2.texture = StringUtils.discardNullOrWhitespace(var6);
         } else if ("textureRust" == var5)) {
            var2.textureRust = StringUtils.discardNullOrWhitespace(var6);
         } else if ("textureMask" == var5)) {
            var2.textureMask = StringUtils.discardNullOrWhitespace(var6);
         } else if ("textureLights" == var5)) {
            var2.textureLights = StringUtils.discardNullOrWhitespace(var6);
         } else if ("textureDamage1Overlay" == var5)) {
            var2.textureDamage1Overlay = StringUtils.discardNullOrWhitespace(var6);
         } else if ("textureDamage1Shell" == var5)) {
            var2.textureDamage1Shell = StringUtils.discardNullOrWhitespace(var6);
         } else if ("textureDamage2Overlay" == var5)) {
            var2.textureDamage2Overlay = StringUtils.discardNullOrWhitespace(var6);
         } else if ("textureDamage2Shell" == var5)) {
            var2.textureDamage2Shell = StringUtils.discardNullOrWhitespace(var6);
         } else if ("textureShadow" == var5)) {
            var2.textureShadow = StringUtils.discardNullOrWhitespace(var6);
         }
      }

    return var2;
   }

    Wheel LoadWheel(Block var1) {
    Wheel var2 = this.getWheelById(var1.id);
      if (var2 == nullptr) {
         var2 = std::make_unique<Wheel>();
         var2.id = var1.id;
         this.wheels.push_back(var2);
      }

      for (Value var4 : var1.values) {
    std::string var5 = var4.getKey().trim();
    std::string var6 = var4.getValue().trim();
         if ("model" == var5)) {
            var2.model = var6;
         } else if ("front" == var5)) {
            var2.front = bool.parseBoolean(var6);
         } else if ("offset" == var5)) {
            this.LoadVector3f(var6, var2.offset);
         } else if ("radius" == var5)) {
            var2.radius = float.parseFloat(var6);
         } else if ("width" == var5)) {
            var2.width = float.parseFloat(var6);
         }
      }

    return var2;
   }

    Passenger LoadPassenger(Block var1) {
    Passenger var2 = this.getPassengerById(var1.id);
      if (var2 == nullptr) {
         var2 = std::make_unique<Passenger>();
         var2.id = var1.id;
         this.passengers.push_back(var2);
      }

      for (Value var4 : var1.values) {
    std::string var5 = var4.getKey().trim();
    std::string var6 = var4.getValue().trim();
         if ("area" == var5)) {
            var2.area = var6;
         } else if ("door" == var5)) {
            var2.door = var6;
         } else if ("door2" == var5)) {
            var2.door2 = var6;
         } else if ("hasRoof" == var5)) {
            var2.hasRoof = bool.parseBoolean(var6);
         } else if ("showPassenger" == var5)) {
            var2.showPassenger = bool.parseBoolean(var6);
         }
      }

      for (Block var8 : var1.children) {
         if ("anim" == var8.type)) {
            this.LoadAnim(var8, var2.anims);
         } else if ("position" == var8.type)) {
            this.LoadPosition(var8, var2.positions);
         } else if ("switchSeat" == var8.type)) {
            this.LoadPassengerSwitchSeat(var8, var2);
         }
      }

    return var2;
   }

    Anim LoadAnim(Block var1, std::vector<Anim> var2) {
    Anim var3 = this.getAnimationById(var1.id, var2);
      if (var3 == nullptr) {
         var3 = std::make_unique<Anim>();
         var3.id = var1.id;
         var2.push_back(var3);
      }

      for (Value var5 : var1.values) {
    std::string var6 = var5.getKey().trim();
    std::string var7 = var5.getValue().trim();
         if ("angle" == var6)) {
            this.LoadVector3f(var7, var3.angle);
         } else if ("anim" == var6)) {
            var3.anim = var7;
         } else if ("animate" == var6)) {
            var3.bAnimate = bool.parseBoolean(var7);
         } else if ("loop" == var6)) {
            var3.bLoop = bool.parseBoolean(var7);
         } else if ("reverse" == var6)) {
            var3.bReverse = bool.parseBoolean(var7);
         } else if ("rate" == var6)) {
            var3.rate = float.parseFloat(var7);
         } else if ("offset" == var6)) {
            this.LoadVector3f(var7, var3.offset);
         } else if ("sound" == var6)) {
            var3.sound = var7;
         }
      }

    return var3;
   }

    SwitchSeat LoadPassengerSwitchSeat(Block var1, Passenger var2) {
    SwitchSeat var3 = var2.getSwitchSeatById(var1.id);
      if (var1.empty()) {
         if (var3 != nullptr) {
            var2.switchSeats.remove(var3);
         }

    return nullptr;
      } else {
         if (var3 == nullptr) {
            var3 = std::make_unique<SwitchSeat>();
            var3.id = var1.id;
            var2.switchSeats.push_back(var3);
         }

         for (Value var5 : var1.values) {
    std::string var6 = var5.getKey().trim();
    std::string var7 = var5.getValue().trim();
            if ("anim" == var6)) {
               var3.anim = var7;
            } else if ("rate" == var6)) {
               var3.rate = float.parseFloat(var7);
            } else if ("sound" == var6)) {
               var3.sound = var7.empty() ? nullptr : var7;
            }
         }

    return var3;
      }
   }

    Area LoadArea(Block var1) {
    Area var2 = this.getAreaById(var1.id);
      if (var2 == nullptr) {
         var2 = std::make_unique<Area>();
         var2.id = var1.id;
         this.areas.push_back(var2);
      }

      for (Value var4 : var1.values) {
    std::string var5 = var4.getKey().trim();
    std::string var6 = var4.getValue().trim();
         if ("xywh" == var5)) {
            std::string[] var7 = var6.split(" ");
            var2.x = float.parseFloat(var7[0]);
            var2.y = float.parseFloat(var7[1]);
            var2.w = float.parseFloat(var7[2]);
            var2.h = float.parseFloat(var7[3]);
         }
      }

    return var2;
   }

    Part LoadPart(Block var1) {
    Part var2 = this.getPartById(var1.id);
      if (var2 == nullptr) {
         var2 = std::make_unique<Part>();
         var2.id = var1.id;
         this.parts.push_back(var2);
      }

      for (Value var4 : var1.values) {
    std::string var5 = var4.getKey().trim();
    std::string var6 = var4.getValue().trim();
         if ("area" == var5)) {
            var2.area = var6.empty() ? nullptr : var6;
         } else if ("itemType" == var5)) {
            var2.itemType = std::make_unique<std::vector>();
            std::string[] var7 = var6.split(";");

    for (auto& var11 : var7)               var2.itemType.push_back(var11);
            }
         } else if ("parent" == var5)) {
            var2.parent = var6.empty() ? nullptr : var6;
         } else if ("mechanicRequireKey" == var5)) {
            var2.mechanicRequireKey = bool.parseBoolean(var6);
         } else if ("repairMechanic" == var5)) {
            var2.setRepairMechanic(bool.parseBoolean(var6));
         } else if ("setAllModelsVisible" == var5)) {
            var2.bSetAllModelsVisible = bool.parseBoolean(var6);
         } else if ("wheel" == var5)) {
            var2.wheel = var6;
         } else if ("category" == var5)) {
            var2.category = var6;
         } else if ("specificItem" == var5)) {
            var2.specificItem = bool.parseBoolean(var6);
         } else if ("hasLightsRear" == var5)) {
            var2.hasLightsRear = bool.parseBoolean(var6);
         }
      }

      for (Block var13 : var1.children) {
         if ("anim" == var13.type)) {
            if (var2.anims == nullptr) {
               var2.anims = std::make_unique<std::vector>();
            }

            this.LoadAnim(var13, var2.anims);
         } else if ("container" == var13.type)) {
            var2.container = this.LoadContainer(var13, var2.container);
         } else if ("door" == var13.type)) {
            var2.door = this.LoadDoor(var13);
         } else if ("lua" == var13.type)) {
            var2.luaFunctions = this.LoadLuaFunctions(var13);
         } else if ("model" == var13.type)) {
            if (var2.models == nullptr) {
               var2.models = std::make_unique<std::vector>();
            }

            this.LoadModel(var13, var2.models);
         } else if ("table" == var13.type)) {
    void* var14 = var2.tables == nullptr ? nullptr : var2.tables.get(var13.id);
    KahluaTable var15 = this.LoadTable(var13, dynamic_cast<KahluaTable*>(var14) != nullptr ? (KahluaTable)var14 : nullptr);
            if (var2.tables == nullptr) {
               var2.tables = std::make_unique<std::unordered_map>();
            }

            var2.tables.put(var13.id, var15);
         } else if ("window" == var13.type)) {
            var2.window = this.LoadWindow(var13);
         }
      }

    return var2;
   }

    PhysicsShape LoadPhysicsShape(Block var1) {
    uint8_t var2 = -1;
    std::string var3 = var1.id;
      switch (var3) {
         case "box":
            var2 = 1;
            break;
         case "sphere":
            var2 = 2;
            break;
         default:
    return nullptr;
      }

    PhysicsShape var9 = std::make_shared<PhysicsShape>();
      var9.type = var2;

      for (Value var5 : var1.values) {
    std::string var6 = var5.getKey().trim();
    std::string var7 = var5.getValue().trim();
         if ("extents".equalsIgnoreCase(var6)) {
            this.LoadVector3f(var7, var9.extents);
         } else if ("offset".equalsIgnoreCase(var6)) {
            this.LoadVector3f(var7, var9.offset);
         } else if ("radius".equalsIgnoreCase(var6)) {
            var9.radius = float.parseFloat(var7);
         } else if ("rotate".equalsIgnoreCase(var6)) {
            this.LoadVector3f(var7, var9.rotate);
         }
      }

      switch (var9.type) {
         case 1:
            if (var9.extents.x() <= 0.0F || var9.extents.y() <= 0.0F || var9.extents.z() <= 0.0F) {
    return nullptr;
            }
            break;
         case 2:
            if (var9.radius <= 0.0F) {
    return nullptr;
            }
      }

    return var9;
   }

    Door LoadDoor(Block var1) {
    Door var2 = std::make_shared<Door>();

      for (Value var4 : var1.values) {
    std::string var5 = var4.getKey().trim();
    std::string var6 = var4.getValue().trim();
      }

    return var2;
   }

    Window LoadWindow(Block var1) {
    Window var2 = std::make_shared<Window>();

      for (Value var4 : var1.values) {
    std::string var5 = var4.getKey().trim();
    std::string var6 = var4.getValue().trim();
         if ("openable" == var5)) {
            var2.openable = bool.parseBoolean(var6);
         }
      }

    return var2;
   }

    Container LoadContainer(Block var1, Container var2) {
    Container var3 = var2 == nullptr ? std::make_shared<Container>() : var2;

      for (Value var5 : var1.values) {
    std::string var6 = var5.getKey().trim();
    std::string var7 = var5.getValue().trim();
         if ("capacity" == var6)) {
            var3.capacity = int.parseInt(var7);
         } else if ("conditionAffectsCapacity" == var6)) {
            var3.conditionAffectsCapacity = bool.parseBoolean(var7);
         } else if ("contentType" == var6)) {
            var3.contentType = var7;
         } else if ("seat" == var6)) {
            var3.seatID = var7;
         } else if ("test" == var6)) {
            var3.luaTest = var7;
         }
      }

    return var3;
   }

   private std::unordered_map<std::string, std::string> LoadLuaFunctions(Block var1) {
    std::unordered_map var2 = new std::unordered_map();

      for (Value var4 : var1.values) {
         if (var4.string.indexOf(61) == -1) {
            throw RuntimeException("expected \"key = value\", got \"" + var4.string.trim() + "\" in " + this.getFullName());
         }

    std::string var5 = var4.getKey().trim();
    std::string var6 = var4.getValue().trim();
         var2.put(var5, var6);
      }

    return var2;
   }

    void* checkIntegerKey(void* var1) {
      if (!(dynamic_cast<std*>(var1) != nullptr::string var2)) {
    return var1;
      } else {
         for (int var3 = 0; var3 < var2.length(); var3++) {
            if (!char.isDigit(var2.charAt(var3))) {
    return var1;
            }
         }

         return double.valueOf(var2);
      }
   }

    KahluaTable LoadTable(Block var1, KahluaTable var2) {
    KahluaTable var3 = var2 == nullptr ? LuaManager.platform.newTable() : var2;

      for (Value var5 : var1.values) {
    std::string var6 = var5.getKey().trim();
    std::string var7 = var5.getValue().trim();
         if (var7.empty()) {
            var7 = nullptr;
         }

         var3.rawset(this.checkIntegerKey(var6), var7);
      }

      for (Block var9 : var1.children) {
    void* var10 = var3.rawget(var9.type);
    KahluaTable var11 = this.LoadTable(var9, dynamic_cast<KahluaTable*>(var10) != nullptr ? (KahluaTable)var10 : nullptr);
         var3.rawset(this.checkIntegerKey(var9.type), var11);
      }

    return var3;
   }

    void LoadTemplate(const std::string& var1) {
      if (var1.contains("/")) {
         std::string[] var2 = var1.split("/");
         if (var2.length == 0 || var2.length > 3) {
            DebugLog.log("ERROR: template \"" + var1 + "\"");
            return;
         }

         for (int var3 = 0; var3 < var2.length; var3++) {
            var2[var3] = var2[var3].trim();
            if (var2[var3].empty()) {
               DebugLog.log("ERROR: template \"" + var1 + "\"");
               return;
            }
         }

    std::string var9 = var2[0];
    VehicleTemplate var4 = ScriptManager.instance.getVehicleTemplate(var9);
         if (var4 == nullptr) {
            DebugLog.log("ERROR: template \"" + var1 + "\" not found");
            return;
         }

    VehicleScript var5 = var4.getScript();
    std::string var6 = var2[1];
         switch (var6) {
            case "area":
               if (var2.length == 2) {
                  DebugLog.log("ERROR: template \"" + var1 + "\"");
                  return;
               }

               this.copyAreasFrom(var5, var2[2]);
               break;
            case "part":
               if (var2.length == 2) {
                  DebugLog.log("ERROR: template \"" + var1 + "\"");
                  return;
               }

               this.copyPartsFrom(var5, var2[2]);
               break;
            case "passenger":
               if (var2.length == 2) {
                  DebugLog.log("ERROR: template \"" + var1 + "\"");
                  return;
               }

               this.copyPassengersFrom(var5, var2[2]);
               break;
            case "wheel":
               if (var2.length == 2) {
                  DebugLog.log("ERROR: template \"" + var1 + "\"");
                  return;
               }

               this.copyWheelsFrom(var5, var2[2]);
               break;
            default:
               DebugLog.log("ERROR: template \"" + var1 + "\"");
               return;
         }
      } else {
    std::string var8 = var1.trim();
    VehicleTemplate var10 = ScriptManager.instance.getVehicleTemplate(var8);
         if (var10 == nullptr) {
            DebugLog.log("ERROR: template \"" + var1 + "\" not found");
            return;
         }

    VehicleScript var11 = var10.getScript();
         this.copyAreasFrom(var11, "*");
         this.copyPartsFrom(var11, "*");
         this.copyPassengersFrom(var11, "*");
         this.copyWheelsFrom(var11, "*");
      }
   }

    void copyAreasFrom(VehicleScript var1, const std::string& var2) {
      if ("*" == var2)) {
         for (int var3 = 0; var3 < var1.getAreaCount(); var3++) {
    Area var4 = var1.getArea(var3);
    int var5 = this.getIndexOfAreaById(var4.id);
            if (var5 == -1) {
               this.areas.push_back(var4.makeCopy());
            } else {
               this.areas.set(var5, var4.makeCopy());
            }
         }
      } else {
    Area var6 = var1.getAreaById(var2);
         if (var6 == nullptr) {
            DebugLog.log("ERROR: area \"" + var2 + "\" not found");
            return;
         }

    int var7 = this.getIndexOfAreaById(var6.id);
         if (var7 == -1) {
            this.areas.push_back(var6.makeCopy());
         } else {
            this.areas.set(var7, var6.makeCopy());
         }
      }
   }

    void copyPartsFrom(VehicleScript var1, const std::string& var2) {
      if ("*" == var2)) {
         for (int var3 = 0; var3 < var1.getPartCount(); var3++) {
    Part var4 = var1.getPart(var3);
    int var5 = this.getIndexOfPartById(var4.id);
            if (var5 == -1) {
               this.parts.push_back(var4.makeCopy());
            } else {
               this.parts.set(var5, var4.makeCopy());
            }
         }
      } else {
    Part var6 = var1.getPartById(var2);
         if (var6 == nullptr) {
            DebugLog.log("ERROR: part \"" + var2 + "\" not found");
            return;
         }

    int var7 = this.getIndexOfPartById(var6.id);
         if (var7 == -1) {
            this.parts.push_back(var6.makeCopy());
         } else {
            this.parts.set(var7, var6.makeCopy());
         }
      }
   }

    void copyPassengersFrom(VehicleScript var1, const std::string& var2) {
      if ("*" == var2)) {
         for (int var3 = 0; var3 < var1.getPassengerCount(); var3++) {
    Passenger var4 = var1.getPassenger(var3);
    int var5 = this.getPassengerIndex(var4.id);
            if (var5 == -1) {
               this.passengers.push_back(var4.makeCopy());
            } else {
               this.passengers.set(var5, var4.makeCopy());
            }
         }
      } else {
    Passenger var6 = var1.getPassengerById(var2);
         if (var6 == nullptr) {
            DebugLog.log("ERROR: passenger \"" + var2 + "\" not found");
            return;
         }

    int var7 = this.getPassengerIndex(var6.id);
         if (var7 == -1) {
            this.passengers.push_back(var6.makeCopy());
         } else {
            this.passengers.set(var7, var6.makeCopy());
         }
      }
   }

    void copyWheelsFrom(VehicleScript var1, const std::string& var2) {
      if ("*" == var2)) {
         for (int var3 = 0; var3 < var1.getWheelCount(); var3++) {
    Wheel var4 = var1.getWheel(var3);
    int var5 = this.getIndexOfWheelById(var4.id);
            if (var5 == -1) {
               this.wheels.push_back(var4.makeCopy());
            } else {
               this.wheels.set(var5, var4.makeCopy());
            }
         }
      } else {
    Wheel var6 = var1.getWheelById(var2);
         if (var6 == nullptr) {
            DebugLog.log("ERROR: wheel \"" + var2 + "\" not found");
            return;
         }

    int var7 = this.getIndexOfWheelById(var6.id);
         if (var7 == -1) {
            this.wheels.push_back(var6.makeCopy());
         } else {
            this.wheels.set(var7, var6.makeCopy());
         }
      }
   }

    Position LoadPosition(Block var1, std::vector<Position> var2) {
    Position var3 = this.getPositionById(var1.id, var2);
      if (var1.empty()) {
         if (var3 != nullptr) {
            var2.remove(var3);
         }

    return nullptr;
      } else {
         if (var3 == nullptr) {
            var3 = std::make_unique<Position>();
            var3.id = var1.id;
            var2.push_back(var3);
         }

         for (Value var5 : var1.values) {
    std::string var6 = var5.getKey().trim();
    std::string var7 = var5.getValue().trim();
            if ("rotate" == var6)) {
               this.LoadVector3f(var7, var3.rotate);
            } else if ("offset" == var6)) {
               this.LoadVector3f(var7, var3.offset);
            } else if ("area" == var6)) {
               var3.area = var7.empty() ? nullptr : var7;
            }
         }

    return var3;
      }
   }

    void initCrawlOffsets() {
      for (int var1 = 0; var1 < this.getWheelCount(); var1++) {
    Wheel var2 = this.getWheel(var1);
         if (var2.id.contains("Left")) {
            this.initCrawlOffsets(var2);
         }
      }

    float var6 = this.extents.z + BaseVehicle.PLUS_RADIUS * 2.0F;

      for (int var7 = 0; var7 < this.crawlOffsets.size(); var7++) {
         this.crawlOffsets.set(var7, (this.extents.z / 2.0F + BaseVehicle.PLUS_RADIUS + this.crawlOffsets.get(var7) - this.centerOfMassOffset.z) / var6);
      }

      this.crawlOffsets.sort();

      for (int var8 = 0; var8 < this.crawlOffsets.size(); var8++) {
    float var3 = this.crawlOffsets.get(var8);

         for (int var4 = var8 + 1; var4 < this.crawlOffsets.size(); var4++) {
    float var5 = this.crawlOffsets.get(var4);
            if ((var5 - var3) * var6 < 0.15F) {
               this.crawlOffsets.removeAt(var4--);
            }
         }
      }
   }

    void initCrawlOffsets(Wheel var1) {
    float var2 = 0.3F;
    float var3 = this.getModel() == nullptr ? 0.0F : this.getModel().getOffset().z;
    float var4 = this.centerOfMassOffset.z + this.extents.z / 2.0F;
    float var5 = this.centerOfMassOffset.z - this.extents.z / 2.0F;

      for (int var6 = 0; var6 < 10; var6++) {
    float var7 = var3 + var1.offset.z + var1.radius + var2 + var2 * var6;
         if (var7 + var2 <= var4 && !this.isOverlappingWheel(var7)) {
            this.crawlOffsets.push_back(var7);
         }

         var7 = var3 + var1.offset.z - var1.radius - var2 - var2 * var6;
         if (var7 - var2 >= var5 && !this.isOverlappingWheel(var7)) {
            this.crawlOffsets.push_back(var7);
         }
      }
   }

    bool isOverlappingWheel(float var1) {
    float var2 = 0.3F;
    float var3 = this.getModel() == nullptr ? 0.0F : this.getModel().getOffset().z;

      for (int var4 = 0; var4 < this.getWheelCount(); var4++) {
    Wheel var5 = this.getWheel(var4);
         if (var5.id.contains("Left") && Math.abs(var3 + var5.offset.z - var1) < (var5.radius + var2) * 0.99F) {
    return true;
         }
      }

    return false;
   }

    std::string getName() {
      return this.name;
   }

    std::string getFullName() {
      return this.getModule().getName() + "." + this.getName();
   }

    Model getModel() {
      return this.models.empty() ? nullptr : this.models.get(0);
   }

    Vector3f getModelOffset() {
      return this.getModel() == nullptr ? nullptr : this.getModel().getOffset();
   }

    float getModelScale() {
      return this.getModel() == nullptr ? 1.0F : this.getModel().scale;
   }

    void setModelScale(float var1) {
    Model var2 = this.getModel();
      if (var2 != nullptr) {
    float var3 = var2.scale;
         var2.scale = 1.0F / var3;
         this.Loaded();
         var2.scale = PZMath.clamp(var1, 0.01F, 100.0F);
         this.Loaded();
      }
   }

    int getModelCount() {
      return this.models.size();
   }

    Model getModelByIndex(int var1) {
      return this.models.get(var1);
   }

    Model getModelById(const std::string& var1, std::vector<Model> var2) {
      for (int var3 = 0; var3 < var2.size(); var3++) {
    Model var4 = (Model)var2.get(var3);
         if (StringUtils.isNullOrWhitespace(var4.id) && StringUtils.isNullOrWhitespace(var1)) {
    return var4;
         }

         if (var4.id != nullptr && var4.id == var1)) {
    return var4;
         }
      }

    return nullptr;
   }

    Model getModelById(const std::string& var1) {
      return this.getModelById(var1, this.models);
   }

    int getAttachmentCount() {
      return this.m_attachments.size();
   }

    ModelAttachment getAttachment(int var1) {
      return this.m_attachments.get(var1);
   }

    ModelAttachment getAttachmentById(const std::string& var1) {
      for (int var2 = 0; var2 < this.m_attachments.size(); var2++) {
    ModelAttachment var3 = this.m_attachments.get(var2);
         if (var3.getId() == var1)) {
    return var3;
         }
      }

    return nullptr;
   }

    ModelAttachment addAttachment(ModelAttachment var1) {
      this.m_attachments.push_back(var1);
    return var1;
   }

    ModelAttachment removeAttachment(ModelAttachment var1) {
      this.m_attachments.remove(var1);
    return var1;
   }

    ModelAttachment addAttachmentAt(int var1, ModelAttachment var2) {
      this.m_attachments.push_back(var1, var2);
    return var2;
   }

    ModelAttachment removeAttachment(int var1) {
      return this.m_attachments.remove(var1);
   }

    LightBar getLightbar() {
      return this.lightbar;
   }

    Sounds getSounds() {
      return this.sound;
   }

    bool getHasSiren() {
      return this.hasSiren;
   }

    Vector3f getExtents() {
      return this.extents;
   }

    Vector3f getPhysicsChassisShape() {
      return this.physicsChassisShape;
   }

    Vector2f getShadowExtents() {
      return this.shadowExtents;
   }

    Vector2f getShadowOffset() {
      return this.shadowOffset;
   }

    Vector2f getExtentsOffset() {
      return this.extentsOffset;
   }

    float getMass() {
      return this.mass;
   }

    Vector3f getCenterOfMassOffset() {
      return this.centerOfMassOffset;
   }

    float getEngineForce() {
      return this.engineForce;
   }

    float getEngineIdleSpeed() {
      return this.engineIdleSpeed;
   }

    int getEngineQuality() {
      return this.engineQuality;
   }

    int getEngineLoudness() {
      return this.engineLoudness;
   }

    float getRollInfluence() {
      return this.rollInfluence;
   }

    float getSteeringIncrement() {
      return this.steeringIncrement;
   }

    float getSteeringClamp(float var1) {
      var1 = Math.abs(var1);
    float var2 = var1 / this.maxSpeed;
      if (var2 > 1.0F) {
         var2 = 1.0F;
      }

      var2 = 1.0F - var2;
      return (this.steeringClampMax - this.steeringClamp) * var2 + this.steeringClamp;
   }

    float getSuspensionStiffness() {
      return this.suspensionStiffness;
   }

    float getSuspensionDamping() {
      return this.suspensionDamping;
   }

    float getSuspensionCompression() {
      return this.suspensionCompression;
   }

    float getSuspensionRestLength() {
      return this.suspensionRestLength;
   }

    float getSuspensionTravel() {
      return this.maxSuspensionTravelCm;
   }

    float getWheelFriction() {
      return this.wheelFriction;
   }

    int getWheelCount() {
      return this.wheels.size();
   }

    Wheel getWheel(int var1) {
      return this.wheels.get(var1);
   }

    Wheel getWheelById(const std::string& var1) {
      for (int var2 = 0; var2 < this.wheels.size(); var2++) {
    Wheel var3 = this.wheels.get(var2);
         if (var3.id != nullptr && var3.id == var1)) {
    return var3;
         }
      }

    return nullptr;
   }

    int getIndexOfWheelById(const std::string& var1) {
      for (int var2 = 0; var2 < this.wheels.size(); var2++) {
    Wheel var3 = this.wheels.get(var2);
         if (var3.id != nullptr && var3.id == var1)) {
    return var2;
         }
      }

      return -1;
   }

    int getPassengerCount() {
      return this.passengers.size();
   }

    Passenger getPassenger(int var1) {
      return this.passengers.get(var1);
   }

    Passenger getPassengerById(const std::string& var1) {
      for (int var2 = 0; var2 < this.passengers.size(); var2++) {
    Passenger var3 = this.passengers.get(var2);
         if (var3.id != nullptr && var3.id == var1)) {
    return var3;
         }
      }

    return nullptr;
   }

    int getPassengerIndex(const std::string& var1) {
      for (int var2 = 0; var2 < this.passengers.size(); var2++) {
    Passenger var3 = this.passengers.get(var2);
         if (var3.id != nullptr && var3.id == var1)) {
    return var2;
         }
      }

      return -1;
   }

    int getPhysicsShapeCount() {
      return this.m_physicsShapes.size();
   }

    PhysicsShape getPhysicsShape(int var1) {
      return var1 >= 0 && var1 < this.m_physicsShapes.size() ? this.m_physicsShapes.get(var1) : nullptr;
   }

    int getFrontEndHealth() {
      return this.frontEndHealth;
   }

    int getRearEndHealth() {
      return this.rearEndHealth;
   }

    int getStorageCapacity() {
      return this.storageCapacity;
   }

    Skin getTextures() {
      return this.textures;
   }

    int getSkinCount() {
      return this.skins.size();
   }

    Skin getSkin(int var1) {
      return this.skins.get(var1);
   }

    int getAreaCount() {
      return this.areas.size();
   }

    Area getArea(int var1) {
      return this.areas.get(var1);
   }

    Area getAreaById(const std::string& var1) {
      for (int var2 = 0; var2 < this.areas.size(); var2++) {
    Area var3 = this.areas.get(var2);
         if (var3.id != nullptr && var3.id == var1)) {
    return var3;
         }
      }

    return nullptr;
   }

    int getIndexOfAreaById(const std::string& var1) {
      for (int var2 = 0; var2 < this.areas.size(); var2++) {
    Area var3 = this.areas.get(var2);
         if (var3.id != nullptr && var3.id == var1)) {
    return var2;
         }
      }

      return -1;
   }

    int getPartCount() {
      return this.parts.size();
   }

    Part getPart(int var1) {
      return this.parts.get(var1);
   }

    Part getPartById(const std::string& var1) {
      for (int var2 = 0; var2 < this.parts.size(); var2++) {
    Part var3 = this.parts.get(var2);
         if (var3.id != nullptr && var3.id == var1)) {
    return var3;
         }
      }

    return nullptr;
   }

    int getIndexOfPartById(const std::string& var1) {
      for (int var2 = 0; var2 < this.parts.size(); var2++) {
    Part var3 = this.parts.get(var2);
         if (var3.id != nullptr && var3.id == var1)) {
    return var2;
         }
      }

      return -1;
   }

    Anim getAnimationById(const std::string& var1, std::vector<Anim> var2) {
      for (int var3 = 0; var3 < var2.size(); var3++) {
    Anim var4 = (Anim)var2.get(var3);
         if (var4.id != nullptr && var4.id == var1)) {
    return var4;
         }
      }

    return nullptr;
   }

    Position getPositionById(const std::string& var1, std::vector<Position> var2) {
      for (int var3 = 0; var3 < var2.size(); var3++) {
    Position var4 = (Position)var2.get(var3);
         if (var4.id != nullptr && var4.id == var1)) {
    return var4;
         }
      }

    return nullptr;
   }

    bool globMatch(const std::string& var1, const std::string& var2) {
    Pattern var3 = Pattern.compile(var1.replaceAll("\\*", ".*"));
      return var3.matcher(var2).matches();
   }

    int getGearRatioCount() {
      return this.gearRatioCount;
   }

    int getSeats() {
      return this.seats;
   }

    void setSeats(int var1) {
      this.seats = var1;
   }

    int getMechanicType() {
      return this.mechanicType;
   }

    void setMechanicType(int var1) {
      this.mechanicType = var1;
   }

    int getEngineRepairLevel() {
      return this.engineRepairLevel;
   }

    int getHeadlightConfigLevel() {
    return 2;
   }

    void setEngineRepairLevel(int var1) {
      this.engineRepairLevel = var1;
   }

    float getPlayerDamageProtection() {
      return this.playerDamageProtection;
   }

    void setPlayerDamageProtection(float var1) {
      this.playerDamageProtection = var1;
   }

    float getForcedHue() {
      return this.forcedHue;
   }

    void setForcedHue(float var1) {
      this.forcedHue = var1;
   }

    float getForcedSat() {
      return this.forcedSat;
   }

    void setForcedSat(float var1) {
      this.forcedSat = var1;
   }

    float getForcedVal() {
      return this.forcedVal;
   }

    void setForcedVal(float var1) {
      this.forcedVal = var1;
   }

    std::string getEngineRPMType() {
      return this.engineRPMType;
   }

    void setEngineRPMType(const std::string& var1) {
      this.engineRPMType = var1;
   }

    float getOffroadEfficiency() {
      return this.offroadEfficiency;
   }

    void setOffroadEfficiency(float var1) {
      this.offroadEfficiency = var1;
   }

    TFloatArrayList getCrawlOffsets() {
      return this.crawlOffsets;
   }
}
} // namespace objects
} // namespace scripting
} // namespace zombie
