#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/OpenALSoundEmitter.h"
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "se/krka/kahlua/j2se/KahluaTableImpl.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/Lua/LuaManager/GlobalObject.h"
#include "zombie/SandboxOptions.h"
#include "zombie/SoundManager.h"
#include "zombie/SystemDisabler.h"
#include "zombie/WorldSoundManager.h"
#include "zombie/ai/states/StaggerBackState.h"
#include "zombie/ai/states/ZombieFallDownState.h"
#include "zombie/audio/BaseSoundEmitter.h"
#include "zombie/audio/DummySoundEmitter.h"
#include "zombie/audio/GameSoundClip.h"
#include "zombie/audio/parameters/ParameterVehicleBrake.h"
#include "zombie/audio/parameters/ParameterVehicleEngineCondition.h"
#include "zombie/audio/parameters/ParameterVehicleGear.h"
#include "zombie/audio/parameters/ParameterVehicleLoad.h"
#include "zombie/audio/parameters/ParameterVehicleRPM.h"
#include "zombie/audio/parameters/ParameterVehicleRoadMaterial.h"
#include "zombie/audio/parameters/ParameterVehicleSkid.h"
#include "zombie/audio/parameters/ParameterVehicleSpeed.h"
#include "zombie/audio/parameters/ParameterVehicleSteer.h"
#include "zombie/audio/parameters/ParameterVehicleTireMissing.h"
#include "zombie/characters/BodyDamage/BodyPart.h"
#include "zombie/characters/BodyDamage/BodyPartType.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Color.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/Translator.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/physics/Bullet.h"
#include "zombie/core/physics/CarController.h"
#include "zombie/core/physics/Transform.h"
#include "zombie/core/physics/WorldSimulation.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/core/skinnedmodel/animation/AnimationMultiTrack.h"
#include "zombie/core/skinnedmodel/animation/AnimationPlayer.h"
#include "zombie/core/skinnedmodel/animation/AnimationTrack.h"
#include "zombie/core/skinnedmodel/model/SkinningData.h"
#include "zombie/core/skinnedmodel/model/VehicleModelInstance.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/core/textures/TextureID.h"
#include "zombie/core/utils/UpdateLimit.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/debug/LineDrawer.h"
#include "zombie/input/GameKeyboard.h"
#include "zombie/inventory/CompressIdenticalItems.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/inventory/ItemPickerJava.h"
#include "zombie/inventory/ItemPickerJava/ItemPickerRoom.h"
#include "zombie/inventory/ItemPickerJava/VehicleDistribution.h"
#include "zombie/inventory/types/DrainableComboItem.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/inventory/types/InventoryContainer.h"
#include "zombie/inventory/types/Key.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoChunk/JobType.h"
#include "zombie/iso/IsoChunkMap.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoLightSource.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/SpriteDetails/IsoObjectType.h"
#include "zombie/iso/Vector2.h"
#include "zombie/iso/areas/SafeHouse.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/iso/objects/IsoTree.h"
#include "zombie/iso/objects/IsoWindow.h"
#include "zombie/iso/objects/IsoWorldInventoryObject.h"
#include "zombie/iso/objects/RainManager.h"
#include "zombie/iso/objects/RenderEffectType.h"
#include "zombie/iso/objects/interfaces/Thumpable.h"
#include "zombie/iso/weather/ClimateManager.h"
#include "zombie/network/ClientServerMap.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/PacketTypes/PacketType.h"
#include "zombie/network/PassengerMap.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/radio/ZomboidRadio.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/ModelAttachment.h"
#include "zombie/scripting/objects/VehicleScript.h"
#include "zombie/scripting/objects/VehicleScript/Anim.h"
#include "zombie/scripting/objects/VehicleScript/Area.h"
#include "zombie/scripting/objects/VehicleScript/Model.h"
#include "zombie/scripting/objects/VehicleScript/Part.h"
#include "zombie/scripting/objects/VehicleScript/Passenger/SwitchSeat.h"
#include "zombie/scripting/objects/VehicleScript/Position.h"
#include "zombie/scripting/objects/VehicleScript/Skin.h"
#include "zombie/scripting/objects/VehicleScript/Wheel.h"
#include "zombie/ui/TextManager.h"
#include "zombie/ui/UIManager.h"
#include "zombie/util/Pool.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/Type.h"
#include "zombie/util/list/PZArrayUtil.h"
#include "zombie/vehicles/BaseVehicle/1.h"
#include "zombie/vehicles/BaseVehicle/Authorization.h"
#include "zombie/vehicles/BaseVehicle/HitVars.h"
#include "zombie/vehicles/BaseVehicle/L_testCollisionWithVehicle.h"
#include "zombie/vehicles/BaseVehicle/Matrix4fObjectPool.h"
#include "zombie/vehicles/BaseVehicle/MinMaxPosition.h"
#include "zombie/vehicles/BaseVehicle/ModelInfo.h"
#include "zombie/vehicles/BaseVehicle/Passenger.h"
#include "zombie/vehicles/BaseVehicle/QuaternionfObjectPool.h"
#include "zombie/vehicles/BaseVehicle/ServerVehicleState.h"
#include "zombie/vehicles/BaseVehicle/Vector2ObjectPool.h"
#include "zombie/vehicles/BaseVehicle/Vector2fObjectPool.h"
#include "zombie/vehicles/BaseVehicle/Vector3fObjectPool.h"
#include "zombie/vehicles/BaseVehicle/VehicleImpulse.h"
#include "zombie/vehicles/BaseVehicle/WheelInfo.h"
#include "zombie/vehicles/BaseVehicle/engineStateTypes.h"
#include "zombie/vehicles/PolygonalMap2/VehiclePoly.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace vehicles {


class BaseVehicle : public IsoMovingObject {
public:
    static const float RADIUS = 0.3F;
    static const int FADE_DISTANCE = 15;
    static const int RANDOMIZE_CONTAINER_CHANCE = 100;
    static const uint8_t noAuthorization = -1;
    static const Vector3f _UNIT_Y = std::make_shared<Vector3f>(0.0F, 1.0F, 0.0F);
    static const VehiclePoly tempPoly = std::make_shared<VehiclePoly>();
    static const bool YURI_FORCE_FIELD = false;
    static bool RENDER_TO_TEXTURE = false;
    static float CENTER_OF_MASS_MAGIC = 0.7F;
   private static const float[] wheelParams = new float[24];
   private static const float[] physicsParams = new float[27];
    static const uint8_t POSITION_ORIENTATION_PACKET_SIZE = 102;
    static Texture vehicleShadow = nullptr;
    int justBreakConstraintTimer = 0;
    BaseVehicle wasTowedBy = nullptr;
    static const ColorInfo inf = std::make_shared<ColorInfo>();
   private static const float[] lowRiderParam = new float[4];
    const VehicleImpulse impulseFromServer = std::make_shared<VehicleImpulse>();
   private const VehicleImpulse[] impulseFromSquishedZombie = new VehicleImpulse[4];
   private const std::vector<VehicleImpulse> impulseFromHitZombie = std::make_unique<std::vector<>>();
    const int netPlayerTimeoutMax = 30;
    const Vector4f tempVector4f = std::make_shared<Vector4f>();
   public const std::vector<ModelInfo> models = std::make_unique<std::vector<>>();
    IsoChunk chunk;
    bool polyDirty = true;
    bool polyGarageCheck = true;
    float radiusReductionInGarage = 0.0F;
    short VehicleID = -1;
    int sqlID = -1;
    bool serverRemovedFromWorld = false;
    VehicleInterpolation interpolation = nullptr;
    bool waitFullUpdate;
    float throttle = 0.0F;
    double engineSpeed;
    TransmissionNumber transmissionNumber;
    const UpdateLimit transmissionChangeTime = std::make_shared<UpdateLimit>(1000L);
    bool hasExtendOffset = true;
    bool hasExtendOffsetExiting = false;
    float savedPhysicsZ = float.NaN;
    const Quaternionf savedRot = std::make_shared<Quaternionf>();
    const Transform jniTransform = std::make_shared<Transform>();
    float jniSpeed;
    bool jniIsCollide;
    const Vector3f jniLinearVelocity = std::make_shared<Vector3f>();
    const Vector3f lastLinearVelocity = std::make_shared<Vector3f>();
    Authorization netPlayerAuthorization = Authorization.Server;
    short netPlayerId = -1;
    int netPlayerTimeout = 0;
    int authSimulationHash = 0;
    long authSimulationTime = 0L;
    int frontEndDurability = 100;
    int rearEndDurability = 100;
    float rust = 0.0F;
    float colorHue = 0.0F;
    float colorSaturation = 0.0F;
    float colorValue = 0.0F;
    int currentFrontEndDurability = 100;
    int currentRearEndDurability = 100;
    float collideX = -1.0F;
    float collideY = -1.0F;
    const VehiclePoly shadowCoord = std::make_shared<VehiclePoly>();
    engineStateTypes engineState = engineStateTypes.Idle;
    long engineLastUpdateStateTime;
    static const int MAX_WHEELS = 4;
    static const int PHYSICS_PARAM_COUNT = 27;
   public const WheelInfo[] wheelInfo = new WheelInfo[4];
    bool skidding = false;
    long skidSound;
    long ramSound;
    long ramSoundTime;
    VehicleEngineRPM vehicleEngineRPM = nullptr;
   public const long[] new_EngineSoundId = new long[8];
    long combinedEngineSound = 0L;
    int engineSoundIndex = 0;
    BaseSoundEmitter hornemitter = nullptr;
    float startTime = 0.0F;
    bool headlightsOn = false;
    bool stoplightsOn = false;
    bool windowLightsOn = false;
    bool soundHornOn = false;
    bool soundBackMoveOn = false;
    bool previouslyEntered = false;
    const LightbarLightsMode lightbarLightsMode = std::make_shared<LightbarLightsMode>();
    const LightbarSirenMode lightbarSirenMode = std::make_shared<LightbarSirenMode>();
    const IsoLightSource leftLight1 = std::make_shared<IsoLightSource>(0, 0, 0, 1.0F, 0.0F, 0.0F, 8);
    const IsoLightSource leftLight2 = std::make_shared<IsoLightSource>(0, 0, 0, 1.0F, 0.0F, 0.0F, 8);
    const IsoLightSource rightLight1 = std::make_shared<IsoLightSource>(0, 0, 0, 0.0F, 0.0F, 1.0F, 8);
    const IsoLightSource rightLight2 = std::make_shared<IsoLightSource>(0, 0, 0, 0.0F, 0.0F, 1.0F, 8);
    int leftLightIndex = -1;
    int rightLightIndex = -1;
   public const ServerVehicleState[] connectionState = new ServerVehicleState[512];
   protected Passenger[] passengers = new Passenger[1];
    std::string scriptName;
    VehicleScript script;
   protected const std::vector<VehiclePart> parts = std::make_unique<std::vector<>>();
    VehiclePart battery;
    int engineQuality;
    int engineLoudness;
    int enginePower;
    long engineCheckTime;
   protected const std::vector<VehiclePart> lights = std::make_unique<std::vector<>>();
    bool createdModel = false;
    int skinIndex = -1;
    CarController physics;
    bool bCreated;
    const VehiclePoly poly = std::make_shared<VehiclePoly>();
    const VehiclePoly polyPlusRadius = std::make_shared<VehiclePoly>();
    bool bDoDamageOverlay = false;
    bool loaded = false;
    short updateFlags;
    long updateLockTimeout = 0L;
    const UpdateLimit limitPhysicSend = std::make_shared<UpdateLimit>(300L);
    Vector2 limitPhysicPositionSent = nullptr;
    const UpdateLimit limitPhysicValid = std::make_shared<UpdateLimit>(1000L);
    const UpdateLimit limitCrash = std::make_shared<UpdateLimit>(600L);
    bool addedToWorld = false;
    bool removedFromWorld = false;
    float polyPlusRadiusMinX = -123.0F;
    float polyPlusRadiusMinY;
    float polyPlusRadiusMaxX;
    float polyPlusRadiusMaxY;
    float maxSpeed;
    bool keyIsOnDoor = false;
    bool hotwired = false;
    bool hotwiredBroken = false;
    bool keysInIgnition = false;
    long soundHorn = -1L;
    long soundScrapePastPlant = -1L;
    long soundBackMoveSignal = -1L;
    long soundSirenSignal = -1L;
   private const std::unordered_map<std::string, std::string> choosenParts = std::make_unique<std::unordered_map<>>();
    std::string type = "";
    std::string respawnZone;
    float mass = 0.0F;
    float initialMass = 0.0F;
    float brakingForce = 0.0F;
    float baseQuality = 0.0F;
    float currentSteering = 0.0F;
    bool isBraking = false;
    int mechanicalID = 0;
    bool needPartsUpdate = false;
    bool alarmed = false;
    int alarmTime = -1;
    float alarmAccumulator;
    double sirenStartTime = 0.0;
    bool mechanicUIOpen = false;
    bool isGoodCar = false;
    InventoryItem currentKey = nullptr;
    bool doColor = true;
    float brekingSlowFactor = 0.0F;
   private const std::vector<IsoObject> brekingObjectsList = std::make_unique<std::vector<>>();
    const UpdateLimit limitUpdate = std::make_shared<UpdateLimit>(333L);
    uint8_t keySpawned = 0;
    const Matrix4f vehicleTransform = std::make_shared<Matrix4f>();
    const Matrix4f renderTransform = std::make_shared<Matrix4f>();
    const Matrix4f tempMatrix4fLWJGL_1 = std::make_shared<Matrix4f>();
    const Quaternionf tempQuat4f = std::make_shared<Quaternionf>();
    const Transform tempTransform = std::make_shared<Transform>();
    const Transform tempTransform2 = std::make_shared<Transform>();
    const Transform tempTransform3 = std::make_shared<Transform>();
    BaseSoundEmitter emitter;
    float brakeBetweenUpdatesSpeed = 0.0F;
    long physicActiveCheck = -1L;
    long constraintChangedTime = -1L;
    AnimationPlayer m_animPlayer = nullptr;
    std::string specificDistributionId = nullptr;
    bool bAddThumpWorldSound = false;
    const SurroundVehicle m_surroundVehicle = std::make_shared<SurroundVehicle>(this);
    bool regulator = false;
    float regulatorSpeed = 0.0F;
   private static const std::unordered_map<std::string, int> s_PartToMaskMap = std::make_unique<std::unordered_map<>>();
    static const uint8_t BYTE_ZERO = (byte)0;
   private const std::unordered_map<std::string, uint8_t> bloodIntensity = std::make_unique<std::unordered_map<>>();
    bool OptionBloodDecals = false;
    long createPhysicsTime = -1L;
    BaseVehicle vehicleTowing = nullptr;
    BaseVehicle vehicleTowedBy = nullptr;
    int constraintTowing = -1;
    int vehicleTowingID = -1;
    int vehicleTowedByID = -1;
    std::string towAttachmentSelf = nullptr;
    std::string towAttachmentOther = nullptr;
    float towConstraintZOffset = 0.0F;
    const ParameterVehicleBrake parameterVehicleBrake = std::make_shared<ParameterVehicleBrake>(this);
    const ParameterVehicleEngineCondition parameterVehicleEngineCondition = std::make_shared<ParameterVehicleEngineCondition>(this);
    const ParameterVehicleGear parameterVehicleGear = std::make_shared<ParameterVehicleGear>(this);
    const ParameterVehicleLoad parameterVehicleLoad = std::make_shared<ParameterVehicleLoad>(this);
    const ParameterVehicleRoadMaterial parameterVehicleRoadMaterial = std::make_shared<ParameterVehicleRoadMaterial>(this);
    const ParameterVehicleRPM parameterVehicleRPM = std::make_shared<ParameterVehicleRPM>(this);
    const ParameterVehicleSkid parameterVehicleSkid = std::make_shared<ParameterVehicleSkid>(this);
    const ParameterVehicleSpeed parameterVehicleSpeed = std::make_shared<ParameterVehicleSpeed>(this);
    const ParameterVehicleSteer parameterVehicleSteer = std::make_shared<ParameterVehicleSteer>(this);
    const ParameterVehicleTireMissing parameterVehicleTireMissing = std::make_shared<ParameterVehicleTireMissing>(this);

   // OpenAL migration: vehicle audio parameters
   std::vector<std::shared_ptr<BaseVehicleParameter>> vehicleParameters;

    bool isActive = false;
    bool isStatic = false;
    const UpdateLimit physicReliableLimit = std::make_shared<UpdateLimit>(500L);
    bool isReliable = false;
   public static const ThreadLocal<Vector2ObjectPool> TL_vector2_pool = ThreadLocal.withInitial(Vector2ObjectPool::new);
   public static const ThreadLocal<Vector2fObjectPool> TL_vector2f_pool = ThreadLocal.withInitial(Vector2fObjectPool::new);
   public static const ThreadLocal<Vector3fObjectPool> TL_vector3f_pool = ThreadLocal.withInitial(Vector3fObjectPool::new);
   public static const ThreadLocal<Matrix4fObjectPool> TL_matrix4f_pool = ThreadLocal.withInitial(Matrix4fObjectPool::new);
   public static const ThreadLocal<QuaternionfObjectPool> TL_quaternionf_pool = ThreadLocal.withInitial(QuaternionfObjectPool::new);
    static const float PHYSICS_Z_SCALE = 0.82F;
    static float PLUS_RADIUS = 0.15F;
    int zombiesHits = 0;
    long zombieHitTimestamp = 0L;
    static const int MASK1_FRONT = 0;
    static const int MASK1_REAR = 4;
    static const int MASK1_DOOR_RIGHT_FRONT = 8;
    static const int MASK1_DOOR_RIGHT_REAR = 12;
    static const int MASK1_DOOR_LEFT_FRONT = 1;
    static const int MASK1_DOOR_LEFT_REAR = 5;
    static const int MASK1_WINDOW_RIGHT_FRONT = 9;
    static const int MASK1_WINDOW_RIGHT_REAR = 13;
    static const int MASK1_WINDOW_LEFT_FRONT = 2;
    static const int MASK1_WINDOW_LEFT_REAR = 6;
    static const int MASK1_WINDOW_FRONT = 10;
    static const int MASK1_WINDOW_REAR = 14;
    static const int MASK1_GUARD_RIGHT_FRONT = 3;
    static const int MASK1_GUARD_RIGHT_REAR = 7;
    static const int MASK1_GUARD_LEFT_FRONT = 11;
    static const int MASK1_GUARD_LEFT_REAR = 15;
    static const int MASK2_ROOF = 0;
    static const int MASK2_LIGHT_RIGHT_FRONT = 4;
    static const int MASK2_LIGHT_LEFT_FRONT = 8;
    static const int MASK2_LIGHT_RIGHT_REAR = 12;
    static const int MASK2_LIGHT_LEFT_REAR = 1;
    static const int MASK2_BRAKE_RIGHT = 5;
    static const int MASK2_BRAKE_LEFT = 9;
    static const int MASK2_LIGHTBAR_RIGHT = 13;
    static const int MASK2_LIGHTBAR_LEFT = 2;
    static const int MASK2_HOOD = 6;
    static const int MASK2_BOOT = 10;
    float forcedFriction = -1.0F;
    const HitVars hitVars = std::make_shared<HitVars>();

    int getSqlId() {
      return this.sqlID;
   }

    static Vector2 allocVector2() {
      return (Vector2)TL_vector2_pool.get().alloc();
   }

    static void releaseVector2(Vector2 var0) {
      TL_vector2_pool.get().release(var0);
   }

    static Vector3f allocVector3f() {
      return (Vector3f)TL_vector3f_pool.get().alloc();
   }

    static void releaseVector3f(Vector3f var0) {
      TL_vector3f_pool.get().release(var0);
   }

    public BaseVehicle(IsoCell var1) {
      super(var1, false);
      this.setCollidable(false);
      this.respawnZone = new std::string("");
      this.scriptName = "Base.PickUpTruck";
      this.passengers[0] = std::make_unique<Passenger>();
      this.waitFullUpdate = false;
      this.savedRot.w = 1.0F;

      for (int var2 = 0; var2 < this.wheelInfo.length; var2++) {
         this.wheelInfo[var2] = std::make_unique<WheelInfo>();
      }

      if (GameClient.bClient) {
         this.interpolation = std::make_unique<VehicleInterpolation>();
      }

      this.setKeyId(Rand.Next(100000000));
      this.engineSpeed = 0.0;
      this.transmissionNumber = TransmissionNumber.N;
      this.rust = Rand.Next(0, 2);
      this.jniIsCollide = false;

      for (int var3 = 0; var3 < 4; var3++) {
         lowRiderParam[var3] = 0.0F;
      }

      this.vehicleParameters.push_back(this.parameterVehicleBrake);
      this.vehicleParameters.push_back(this.parameterVehicleEngineCondition);
      this.vehicleParameters.push_back(this.parameterVehicleGear);
      this.vehicleParameters.push_back(this.parameterVehicleLoad);
      this.vehicleParameters.push_back(this.parameterVehicleRPM);
      this.vehicleParameters.push_back(this.parameterVehicleRoadMaterial);
      this.vehicleParameters.push_back(this.parameterVehicleSkid);
      this.vehicleParameters.push_back(this.parameterVehicleSpeed);
      this.vehicleParameters.push_back(this.parameterVehicleSteer);
      this.vehicleParameters.push_back(this.parameterVehicleTireMissing);
   }

    static void LoadAllVehicleTextures() {
      DebugLog.General.println("BaseVehicle.LoadAllVehicleTextures...");

      for (VehicleScript var2 : ScriptManager.instance.getAllVehicleScripts()) {
         LoadVehicleTextures(var2);
      }
   }

    static void LoadVehicleTextures(VehicleScript var0) {
      if (SystemDisabler.doVehiclesWithoutTextures) {
    Skin var1 = var0.getSkin(0);
         var1.textureData = LoadVehicleTexture(var1.texture);
         var1.textureDataMask = LoadVehicleTexture("vehicles_placeholder_mask");
         var1.textureDataDamage1Overlay = LoadVehicleTexture("vehicles_placeholder_damage1overlay");
         var1.textureDataDamage1Shell = LoadVehicleTexture("vehicles_placeholder_damage1shell");
         var1.textureDataDamage2Overlay = LoadVehicleTexture("vehicles_placeholder_damage2overlay");
         var1.textureDataDamage2Shell = LoadVehicleTexture("vehicles_placeholder_damage2shell");
         var1.textureDataLights = LoadVehicleTexture("vehicles_placeholder_lights");
         var1.textureDataRust = LoadVehicleTexture("vehicles_placeholder_rust");
      } else {
         for (int var3 = 0; var3 < var0.getSkinCount(); var3++) {
    Skin var2 = var0.getSkin(var3);
            var2.copyMissingFrom(var0.getTextures());
            LoadVehicleTextures(var2);
         }
      }
   }

    static void LoadVehicleTextures(Skin var0) {
      var0.textureData = LoadVehicleTexture(var0.texture);
      if (var0.textureMask != nullptr) {
    int var1 = 0;
         var1 |= 256;
         var0.textureDataMask = LoadVehicleTexture(var0.textureMask, var1);
      }

      var0.textureDataDamage1Overlay = LoadVehicleTexture(var0.textureDamage1Overlay);
      var0.textureDataDamage1Shell = LoadVehicleTexture(var0.textureDamage1Shell);
      var0.textureDataDamage2Overlay = LoadVehicleTexture(var0.textureDamage2Overlay);
      var0.textureDataDamage2Shell = LoadVehicleTexture(var0.textureDamage2Shell);
      var0.textureDataLights = LoadVehicleTexture(var0.textureLights);
      var0.textureDataRust = LoadVehicleTexture(var0.textureRust);
      var0.textureDataShadow = LoadVehicleTexture(var0.textureShadow);
   }

    static Texture LoadVehicleTexture(const std::string& var0) {
    int var1 = 0;
      var1 |= TextureID.bUseCompression ? 4 : 0;
      var1 |= 256;
    return LoadVehicleTexture();
   }

    static Texture LoadVehicleTexture(const std::string& var0, int var1) {
      return StringUtils.isNullOrWhitespace(var0) ? nullptr : Texture.getSharedTexture("media/textures/" + var0 + ".png", var1);
   }

    void setNetPlayerAuthorization(Authorization var1, int var2) {
      this.netPlayerAuthorization = var1;
      this.netPlayerId = (short)var2;
      this.netPlayerTimeout = var2 == -1 ? 0 : 30;
      if (GameClient.bClient) {
    bool var3 = Authorization.Local == var1) || Authorization.LocalCollide == var1);
         if (this.getVehicleTowing() != nullptr) {
            Bullet.setVehicleStatic(this, !var3);
            Bullet.setVehicleActive(this, var3);
            Bullet.setVehicleStatic(this.getVehicleTowing(), !var3);
            Bullet.setVehicleActive(this.getVehicleTowing(), var3);
         } else if (this.getVehicleTowedBy() != nullptr) {
            Bullet.setVehicleStatic(this, !var3);
            Bullet.setVehicleActive(this, var3);
         } else {
            Bullet.setVehicleStatic(this, !var3);
            Bullet.setVehicleActive(this, var3);
         }
      }

      DebugLog.Vehicle
         .trace("vid%s=%d pid=%d %s", this.getVehicleTowing() != nullptr ? "-a" : (this.getVehicleTowedBy() != nullptr ? "-b" : ""), this.getId(), var2, var1.name());
   }

    bool isNetPlayerAuthorization(Authorization var1) {
      return this.netPlayerAuthorization == var1);
   }

    bool isNetPlayerId(short var1) {
      return this.netPlayerId == var1;
   }

    short getNetPlayerId() {
      return this.netPlayerId;
   }

    std::string getAuthorizationDescription() {
      return std::string.format(
         "vid:%s(%d) pid:(%d) auth=%s static=%b active=%b",
         this.scriptName,
         this.VehicleID,
         this.netPlayerId,
         this.netPlayerAuthorization.name(),
         this.isStatic,
         this.isActive
      );
   }

    static float getFakeSpeedModifier() {
      if (!GameClient.bClient && !GameServer.bServer) {
         return 1.0F;
      } else {
    float var0 = (float)ServerOptions.instance.SpeedLimit.getValue();
         return 120.0F / Math.min(var0, 120.0F);
      }
   }

    bool isLocalPhysicSim() {
      return GameServer.bServer
         ? this.isNetPlayerAuthorization(Authorization.Server)
         : this.isNetPlayerAuthorization(Authorization.LocalCollide) || this.isNetPlayerAuthorization(Authorization.Local);
   }

    void addImpulse(Vector3f var1, Vector3f var2) {
      if (!this.impulseFromServer.enable) {
         this.impulseFromServer.enable = true;
         this.impulseFromServer.impulse.set(var1);
         this.impulseFromServer.rel_pos.set(var2);
      } else if (this.impulseFromServer.impulse.length() < var1.length()) {
         this.impulseFromServer.impulse.set(var1);
         this.impulseFromServer.rel_pos.set(var2);
         this.impulseFromServer.enable = false;
         this.impulseFromServer.release();
      }
   }

    double getEngineSpeed() {
      return this.engineSpeed;
   }

    std::string getTransmissionNumberLetter() {
      return this.transmissionNumber.getString();
   }

    int getTransmissionNumber() {
      return this.transmissionNumber.getIndex();
   }

    void setClientForce(float var1) {
      this.physics.clientForce = var1;
   }

    float getClientForce() {
      return this.physics.clientForce;
   }

    float getForce() {
      return this.physics.EngineForce - this.physics.BrakingForce;
   }

    void doVehicleColor() {
      if (!this.isDoColor()) {
         this.colorSaturation = 0.1F;
         this.colorValue = 0.9F;
      } else {
         this.colorHue = Rand.Next(0.0F, 0.0F);
         this.colorSaturation = 0.5F;
         this.colorValue = Rand.Next(0.3F, 0.6F);
    int var1 = Rand.Next(100);
         if (var1 < 20) {
            this.colorHue = Rand.Next(0.0F, 0.03F);
            this.colorSaturation = Rand.Next(0.85F, 1.0F);
            this.colorValue = Rand.Next(0.55F, 0.85F);
         } else if (var1 < 32) {
            this.colorHue = Rand.Next(0.55F, 0.61F);
            this.colorSaturation = Rand.Next(0.85F, 1.0F);
            this.colorValue = Rand.Next(0.65F, 0.75F);
         } else if (var1 < 67) {
            this.colorHue = 0.15F;
            this.colorSaturation = Rand.Next(0.0F, 0.1F);
            this.colorValue = Rand.Next(0.7F, 0.8F);
         } else if (var1 < 89) {
            this.colorHue = Rand.Next(0.0F, 1.0F);
            this.colorSaturation = Rand.Next(0.0F, 0.1F);
            this.colorValue = Rand.Next(0.1F, 0.25F);
         } else {
            this.colorHue = Rand.Next(0.0F, 1.0F);
            this.colorSaturation = Rand.Next(0.6F, 0.75F);
            this.colorValue = Rand.Next(0.3F, 0.7F);
         }

         if (this.getScript() != nullptr) {
            if (this.getScript().getForcedHue() > -1.0F) {
               this.colorHue = this.getScript().getForcedHue();
            }

            if (this.getScript().getForcedSat() > -1.0F) {
               this.colorSaturation = this.getScript().getForcedSat();
            }

            if (this.getScript().getForcedVal() > -1.0F) {
               this.colorValue = this.getScript().getForcedVal();
            }
         }
      }
   }

    std::string getObjectName() {
      return "Vehicle";
   }

    bool Serialize() {
    return true;
   }

    void createPhysics() {
      if (!GameClient.bClient && this.VehicleID == -1) {
         this.VehicleID = VehicleIDMap.instance.allocateID();
         if (GameServer.bServer) {
            VehicleManager.instance.registerVehicle(this);
         } else {
            VehicleIDMap.instance.put(this.VehicleID, this);
         }
      }

      if (this.script == nullptr) {
         this.setScript(this.scriptName);
      }

      if (this.script != nullptr) {
         if (this.skinIndex == -1) {
            this.setSkinIndex(Rand.Next(this.getSkinCount()));
         }

         if (!GameServer.bServer) {
            WorldSimulation.instance.create();
         }

         this.jniTransform
            .origin
            .set(
               this.getX() - WorldSimulation.instance.offsetX,
               float.isNaN(this.savedPhysicsZ) ? this.getZ() : this.savedPhysicsZ,
               this.getY() - WorldSimulation.instance.offsetY
            );
         this.physics = std::make_shared<CarController>(this);
         this.savedPhysicsZ = float.NaN;
         this.createPhysicsTime = System.currentTimeMillis();
         if (!this.bCreated) {
            this.bCreated = true;
    uint8_t var1 = 30;
            if (SandboxOptions.getInstance().RecentlySurvivorVehicles.getValue() == 1) {
               var1 = 0;
            }

            if (SandboxOptions.getInstance().RecentlySurvivorVehicles.getValue() == 2) {
               var1 = 10;
            }

            if (SandboxOptions.getInstance().RecentlySurvivorVehicles.getValue() == 3) {
               var1 = 30;
            }

            if (SandboxOptions.getInstance().RecentlySurvivorVehicles.getValue() == 4) {
               var1 = 50;
            }

            if (Rand.Next(100) < var1) {
               this.setGoodCar(true);
            }
         }

         this.createParts();
         this.initParts();
         if (!this.createdModel) {
            ModelManager.instance.addVehicle(this);
            this.createdModel = true;
         }

         this.updateTransform();
         this.lights.clear();

         for (int var3 = 0; var3 < this.parts.size(); var3++) {
    VehiclePart var2 = this.parts.get(var3);
            if (var2.getLight() != nullptr) {
               this.lights.push_back(var2);
            }
         }

         this.setMaxSpeed(this.getScript().maxSpeed);
         this.setInitialMass(this.getScript().getMass());
         if (!this.getCell().getVehicles().contains(this) && !this.getCell().addVehicles.contains(this)) {
            this.getCell().addVehicles.push_back(this);
         }

         this.square = this.getCell().getGridSquare(this.x, this.y, this.z);
         this.randomizeContainers();
         if (this.engineState == engineStateTypes.Running) {
            this.engineDoRunning();
         }

         this.updateTotalMass();
         this.bDoDamageOverlay = true;
         this.updatePartStats();
         this.mechanicalID = Rand.Next(100000);
      }
   }

    bool isPreviouslyEntered() {
      return this.previouslyEntered;
   }

    void setPreviouslyEntered(bool var1) {
      this.previouslyEntered = var1;
   }

    int getKeyId() {
      return this.keyId;
   }

    bool getKeySpawned() {
      return this.keySpawned != 0;
   }

    void putKeyToZombie(IsoZombie var1) {
      if (Rand.Next(10) != 1) {
    InventoryItem var2 = this.createVehicleKey();
         var1.getInventory().AddItem(var2);
      } else if (var1.getInventory().AddItem("Base.KeyRing") instanceof InventoryContainer var3) {
    InventoryItem var4 = this.createVehicleKey();
         var3.getInventory().AddItem(var4);
      }
   }

    void putKeyToContainer(ItemContainer var1, IsoGridSquare var2, IsoObject var3) {
    InventoryItem var4 = this.createVehicleKey();
      var1.AddItem(var4);
      if (GameServer.bServer) {
         for (int var5 = 0; var5 < GameServer.udpEngine.connections.size(); var5++) {
    UdpConnection var6 = (UdpConnection)GameServer.udpEngine.connections.get(var5);
            if (var6.RelevantTo(var3.square.x, var3.square.y)) {
    ByteBufferWriter var7 = var6.startPacket();
               PacketType.AddInventoryItemToContainer.doPacket(var7);
               var7.putShort((short)2);
               var7.putInt((int)var3.getX());
               var7.putInt((int)var3.getY());
               var7.putInt((int)var3.getZ());
    int var8 = var2.getObjects().indexOf(var3);
               var7.putByte((byte)var8);
               var7.putByte((byte)var3.getContainerIndex(var1));

               try {
                  CompressIdenticalItems.save(var7.bb, var4);
               } catch (Exception var10) {
                  var10.printStackTrace();
               }

               PacketType.AddInventoryItemToContainer.send(var6);
            }
         }
      }
   }

    void putKeyToWorld(IsoGridSquare var1) {
    InventoryItem var2 = this.createVehicleKey();
      var1.AddWorldInventoryItem(var2, 0.0F, 0.0F, 0.0F);
   }

    void addKeyToWorld() {
      if (this.haveOneDoorUnlocked() && Rand.Next(100) < 30) {
         if (Rand.Next(5) == 0) {
            this.keyIsOnDoor = true;
            this.currentKey = this.createVehicleKey();
         } else {
            this.addKeyToGloveBox();
         }
      } else if (this.haveOneDoorUnlocked() && Rand.Next(100) < 30) {
         this.keysInIgnition = true;
         this.currentKey = this.createVehicleKey();
      } else {
         if (Rand.Next(100) < 50) {
    IsoGridSquare var1 = this.getCell().getGridSquare(this.x, this.y, this.z);
            if (var1 != nullptr) {
               this.addKeyToSquare(var1);
               return;
            }
         }
      }
   }

    void addKeyToGloveBox() {
      if (this.keySpawned == 0) {
         if (this.getPartById("GloveBox") != nullptr) {
    VehiclePart var1 = this.getPartById("GloveBox");
    InventoryItem var2 = this.createVehicleKey();
            var1.container.addItem(var2);
            this.keySpawned = 1;
         }
      }
   }

    InventoryItem createVehicleKey() {
    InventoryItem var1 = InventoryItemFactory.CreateItem("CarKey");
      var1.setKeyId(this.getKeyId());
      var1.setName(Translator.getText("IGUI_CarKey", Translator.getText("IGUI_VehicleName" + this.getScript().getName())));
    Color var2 = Color.HSBtoRGB(this.colorHue, this.colorSaturation * 0.5F, this.colorValue);
      var1.setColor(var2);
      var1.setCustomColor(true);
    return var1;
   }

    bool addKeyToSquare(IsoGridSquare var1) {
    bool var2 = false;
    void* var3 = nullptr;

      for (int var4 = 0; var4 < 3; var4++) {
         for (int var5 = var1.getX() - 10; var5 < var1.getX() + 10; var5++) {
            for (int var6 = var1.getY() - 10; var6 < var1.getY() + 10; var6++) {
               var3 = IsoWorld.instance.getCell().getGridSquare(var5, var6, var4);
               if (var3 != nullptr) {
                  for (int var7 = 0; var7 < var3.getObjects().size(); var7++) {
    IsoObject var8 = (IsoObject)var3.getObjects().get(var7);
                     if (var8.container != nullptr
                        && (
                           var8.container.type == "counter")
                              || var8.container.type == "officedrawers")
                              || var8.container.type == "shelves")
                              || var8.container.type == "desk")
                        )) {
                        this.putKeyToContainer(var8.container, (IsoGridSquare)var3, var8);
                        var2 = true;
                        break;
                     }
                  }

                  for (int var13 = 0; var13 < var3.getMovingObjects().size(); var13++) {
                     if (var3.getMovingObjects().get(var13) instanceof IsoZombie) {
                        ((IsoZombie)var3.getMovingObjects().get(var13)).addItemToSpawnAtDeath(this.createVehicleKey());
                        var2 = true;
                        break;
                     }
                  }
               }

               if (var2) {
                  break;
               }
            }

            if (var2) {
               break;
            }
         }

         if (var2) {
            break;
         }
      }

      if (Rand.Next(10) < 6) {
         while (!var2) {
    int var11 = var1.getX() - 10 + Rand.Next(20);
    int var12 = var1.getY() - 10 + Rand.Next(20);
            var3 = IsoWorld.instance.getCell().getGridSquare(var11, var12, this.z);
            if (var3 != nullptr && !var3.isSolid() && !var3.isSolidTrans() && !var3.HasTree()) {
               this.putKeyToWorld((IsoGridSquare)var3);
               var2 = true;
               break;
            }
         }
      }

    return var2;
   }

    void toggleLockedDoor(VehiclePart var1, IsoGameCharacter var2, bool var3) {
      if (var3) {
         if (!this.canLockDoor(var1, var2)) {
            return;
         }

         var1.getDoor().setLocked(true);
      } else {
         if (!this.canUnlockDoor(var1, var2)) {
            return;
         }

         var1.getDoor().setLocked(false);
      }
   }

    bool canLockDoor(VehiclePart var1, IsoGameCharacter var2) {
      if (var1 == nullptr) {
    return false;
      } else if (var2 == nullptr) {
    return false;
      } else {
    VehicleDoor var3 = var1.getDoor();
         if (var3 == nullptr) {
    return false;
         } else if (var3.lockBroken) {
    return false;
         } else if (var3.locked) {
    return false;
         } else if (this.getSeat(var2) != -1) {
    return true;
         } else if (var2.getInventory().haveThisKeyId(this.getKeyId()) != nullptr) {
    return true;
         } else {
    VehiclePart var4 = var1.getChildWindow();
            if (var4 != nullptr && var4.getInventoryItem() == nullptr) {
    return true;
            } else {
    VehicleWindow var5 = var4 == nullptr ? nullptr : var4.getWindow();
               return var5 != nullptr && (var5.isOpen() || var5.isDestroyed());
            }
         }
      }
   }

    bool canUnlockDoor(VehiclePart var1, IsoGameCharacter var2) {
      if (var1 == nullptr) {
    return false;
      } else if (var2 == nullptr) {
    return false;
      } else {
    VehicleDoor var3 = var1.getDoor();
         if (var3 == nullptr) {
    return false;
         } else if (var3.lockBroken) {
    return false;
         } else if (!var3.locked) {
    return false;
         } else if (this.getSeat(var2) != -1) {
    return true;
         } else if (var2.getInventory().haveThisKeyId(this.getKeyId()) != nullptr) {
    return true;
         } else {
    VehiclePart var4 = var1.getChildWindow();
            if (var4 != nullptr && var4.getInventoryItem() == nullptr) {
    return true;
            } else {
    VehicleWindow var5 = var4 == nullptr ? nullptr : var4.getWindow();
               return var5 != nullptr && (var5.isOpen() || var5.isDestroyed());
            }
         }
      }
   }

    void initParts() {
      for (int var1 = 0; var1 < this.parts.size(); var1++) {
    VehiclePart var2 = this.parts.get(var1);
    std::string var3 = var2.getLuaFunction("init");
         if (var3 != nullptr) {
            this.callLuaVoid(var3, this, var2);
         }
      }
   }

    void setGeneralPartCondition(float var1, float var2) {
      for (int var3 = 0; var3 < this.parts.size(); var3++) {
    VehiclePart var4 = this.parts.get(var3);
         var4.setGeneralCondition(nullptr, var1, var2);
      }
   }

    void createParts() {
      for (int var1 = 0; var1 < this.parts.size(); var1++) {
    VehiclePart var2 = this.parts.get(var1);
    std::vector var3 = var2.getItemType();
         if (var2.bCreated && var3 != nullptr && !var3.empty() && var2.getInventoryItem() == nullptr && var2.getTable("install") == nullptr) {
            var2.bCreated = false;
         } else if ((var3 == nullptr || var3.empty()) && var2.getInventoryItem() != nullptr) {
            var2.item = nullptr;
         }

         if (!var2.bCreated) {
            var2.bCreated = true;
    std::string var4 = var2.getLuaFunction("create");
            if (var4 == nullptr) {
               var2.setRandomCondition(nullptr);
            } else {
               this.callLuaVoid(var4, this, var2);
               if (var2.getCondition() == -1) {
                  var2.setRandomCondition(nullptr);
               }
            }
         }
      }

      if (this.hasLightbar() && this.getScript().rightSirenCol != nullptr && this.getScript().leftSirenCol != nullptr) {
         this.leftLight1.r = this.leftLight2.r = this.getScript().leftSirenCol.r;
         this.leftLight1.g = this.leftLight2.g = this.getScript().leftSirenCol.g;
         this.leftLight1.b = this.leftLight2.b = this.getScript().leftSirenCol.b;
         this.rightLight1.r = this.rightLight2.r = this.getScript().rightSirenCol.r;
         this.rightLight1.g = this.rightLight2.g = this.getScript().rightSirenCol.g;
         this.rightLight1.b = this.rightLight2.b = this.getScript().rightSirenCol.b;
      }
   }

    CarController getController() {
      return this.physics;
   }

    SurroundVehicle getSurroundVehicle() {
      return this.m_surroundVehicle;
   }

    int getSkinCount() {
      return this.script.getSkinCount();
   }

    int getSkinIndex() {
      return this.skinIndex;
   }

    void setSkinIndex(int var1) {
      if (var1 >= 0 && var1 <= this.getSkinCount()) {
         this.skinIndex = var1;
      }
   }

    void updateSkin() {
      if (this.sprite != nullptr && this.sprite.modelSlot != nullptr && this.sprite.modelSlot.model != nullptr) {
    VehicleModelInstance var1 = (VehicleModelInstance)this.sprite.modelSlot.model;
    Skin var2 = this.script.getTextures();
    VehicleScript var3 = this.getScript();
         if (this.getSkinIndex() >= 0 && this.getSkinIndex() < var3.getSkinCount()) {
            var2 = var3.getSkin(this.getSkinIndex());
         }

         var1.LoadTexture(var2.texture);
         var1.tex = var2.textureData;
         var1.textureMask = var2.textureDataMask;
         var1.textureDamage1Overlay = var2.textureDataDamage1Overlay;
         var1.textureDamage1Shell = var2.textureDataDamage1Shell;
         var1.textureDamage2Overlay = var2.textureDataDamage2Overlay;
         var1.textureDamage2Shell = var2.textureDataDamage2Shell;
         var1.textureLights = var2.textureDataLights;
         var1.textureRust = var2.textureDataRust;
         if (var1.tex != nullptr) {
            var1.tex.bindAlways = true;
         } else {
            DebugLog.Animation.error("texture not found:", new Object[]{this.getSkin()});
         }
      }
   }

    Texture getShadowTexture() {
      if (this.getScript() != nullptr) {
    Skin var1 = this.getScript().getTextures();
         if (this.getSkinIndex() >= 0 && this.getSkinIndex() < this.getScript().getSkinCount()) {
            var1 = this.getScript().getSkin(this.getSkinIndex());
         }

         if (var1.textureDataShadow != nullptr) {
            return var1.textureDataShadow;
         }
      }

      if (vehicleShadow == nullptr) {
    int var2 = 0;
         var2 |= TextureID.bUseCompression ? 4 : 0;
         vehicleShadow = Texture.getSharedTexture("media/vehicleShadow.png", var2);
      }

    return vehicleShadow;
   }

    VehicleScript getScript() {
      return this.script;
   }

    void setScript(const std::string& var1) {
      if (!StringUtils.isNullOrWhitespace(var1)) {
         this.scriptName = var1;
    bool var2 = this.script != nullptr;
         this.script = ScriptManager.instance.getVehicle(this.scriptName);
         if (this.script == nullptr) {
    std::vector var3 = ScriptManager.instance.getAllVehicleScripts();
            if (!var3.empty()) {
    std::vector var4 = new std::vector();

               for (int var5 = 0; var5 < var3.size(); var5++) {
    VehicleScript var6 = (VehicleScript)var3.get(var5);
                  if (var6.getWheelCount() == 0) {
                     var4.push_back(var6);
                     var3.remove(var5--);
                  }
               }

    bool var13 = this.loaded && this.parts.empty() || this.scriptName.contains("Burnt");
               if (var13 && !var4.empty()) {
                  this.script = (VehicleScript)var4.get(Rand.Next(var4.size()));
               } else if (!var3.empty()) {
                  this.script = (VehicleScript)var3.get(Rand.Next(var3.size()));
               }

               if (this.script != nullptr) {
                  this.scriptName = this.script.getFullName();
               }
            }
         }

         this.battery = nullptr;
         this.models.clear();
         if (this.script != nullptr) {
            this.scriptName = this.script.getFullName();
            Passenger[] var10 = this.passengers;
            this.passengers = new Passenger[this.script.getPassengerCount()];

            for (int var11 = 0; var11 < this.passengers.length; var11++) {
               if (var11 < var10.length) {
                  this.passengers[var11] = var10[var11];
               } else {
                  this.passengers[var11] = std::make_unique<Passenger>();
               }
            }

    std::vector var12 = new std::vector();
            var12.addAll(this.parts);
            this.parts.clear();

            for (int var14 = 0; var14 < this.script.getPartCount(); var14++) {
    Part var17 = this.script.getPart(var14);
    VehiclePart var7 = nullptr;

               for (int var8 = 0; var8 < var12.size(); var8++) {
    VehiclePart var9 = (VehiclePart)var12.get(var8);
                  if (var9.getScriptPart() != nullptr && var17.id == var9.getScriptPart().id)) {
                     var7 = var9;
                     break;
                  }

                  if (var9.partId != nullptr && var17.id == var9.partId)) {
                     var7 = var9;
                     break;
                  }
               }

               if (var7 == nullptr) {
                  var7 = std::make_shared<VehiclePart>(this);
               }

               var7.setScriptPart(var17);
               var7.category = var17.category;
               var7.specificItem = var17.specificItem;
               if (var17.container != nullptr && var17.container.contentType == nullptr) {
                  if (var7.getItemContainer() == nullptr) {
    ItemContainer var21 = std::make_shared<ItemContainer>(var17.id, nullptr, this);
                     var7.setItemContainer(var21);
                     var21.ID = 0;
                  }

                  var7.getItemContainer().Capacity = var17.container.capacity;
               } else {
                  var7.setItemContainer(nullptr);
               }

               if (var17.door == nullptr) {
                  var7.door = nullptr;
               } else if (var7.door == nullptr) {
                  var7.door = std::make_shared<VehicleDoor>(var7);
                  var7.door.init(var17.door);
               }

               if (var17.window == nullptr) {
                  var7.window = nullptr;
               } else if (var7.window == nullptr) {
                  var7.window = std::make_shared<VehicleWindow>(var7);
                  var7.window.init(var17.window);
               } else {
                  var7.window.openable = var17.window.openable;
               }

               var7.parent = nullptr;
               if (var7.children != nullptr) {
                  var7.children.clear();
               }

               this.parts.push_back(var7);
               if ("Battery" == var7.getId())) {
                  this.battery = var7;
               }
            }

            for (int var15 = 0; var15 < this.script.getPartCount(); var15++) {
    VehiclePart var18 = this.parts.get(var15);
    Part var20 = var18.getScriptPart();
               if (var20.parent != nullptr) {
                  var18.parent = this.getPartById(var20.parent);
                  if (var18.parent != nullptr) {
                     var18.parent.addChild(var18);
                  }
               }
            }

            if (!var2 && !this.loaded) {
               this.frontEndDurability = this.rearEndDurability = 99999;
            }

            this.frontEndDurability = Math.min(this.frontEndDurability, this.script.getFrontEndHealth());
            this.rearEndDurability = Math.min(this.rearEndDurability, this.script.getRearEndHealth());
            this.currentFrontEndDurability = this.frontEndDurability;
            this.currentRearEndDurability = this.rearEndDurability;

            for (int var16 = 0; var16 < this.script.getPartCount(); var16++) {
    VehiclePart var19 = this.parts.get(var16);
               var19.setInventoryItem(var19.item);
            }
         }

         if (!this.loaded || this.colorHue == 0.0F && this.colorSaturation == 0.0F && this.colorValue == 0.0F) {
            this.doVehicleColor();
         }

         this.m_surroundVehicle.reset();
      }
   }

    std::string getScriptName() {
      return this.scriptName;
   }

    void setScriptName(const std::string& var1) {
    assert var1 = = nullptr || var1.contains(".");

      this.scriptName = var1;
   }

    void setScript() {
      this.setScript(this.scriptName);
   }

    void scriptReloaded() {
      this.tempTransform2.setIdentity();
      if (this.physics != nullptr) {
         this.getWorldTransform(this.tempTransform2);
         this.tempTransform2.basis.getUnnormalizedRotation(this.savedRot);
         this.breakConstraint(false, false);
         Bullet.removeVehicle(this.VehicleID);
         this.physics = nullptr;
      }

      if (this.createdModel) {
         ModelManager.instance.Remove(this);
         this.createdModel = false;
      }

      this.vehicleEngineRPM = nullptr;

      for (int var1 = 0; var1 < this.parts.size(); var1++) {
    VehiclePart var2 = this.parts.get(var1);
         var2.setInventoryItem(nullptr);
         var2.bCreated = false;
      }

      this.setScript(this.scriptName);
      this.createPhysics();
      if (this.script != nullptr) {
         for (int var4 = 0; var4 < this.passengers.length; var4++) {
    Passenger var5 = this.passengers[var4];
            if (var5 != nullptr && var5.character != nullptr) {
    Position var3 = this.getPassengerPosition(var4, "inside");
               if (var3 != nullptr) {
                  var5.offset.set(var3.offset);
               }
            }
         }
      }

      this.polyDirty = true;
      if (this.isEngineRunning()) {
         this.engineDoShuttingDown();
         this.engineState = engineStateTypes.Idle;
      }

      if (this.addedToWorld) {
         PolygonalMap2.instance.removeVehicleFromWorld(this);
         PolygonalMap2.instance.addVehicleToWorld(this);
      }
   }

    std::string getSkin() {
      if (this.script != nullptr && this.script.getSkinCount() != 0) {
         if (this.skinIndex < 0 || this.skinIndex >= this.script.getSkinCount()) {
            this.skinIndex = Rand.Next(this.script.getSkinCount());
         }

         return this.script.getSkin(this.skinIndex).texture;
      } else {
         return "BOGUS";
      }
   }

    ModelInfo setModelVisible(VehiclePart var1, Model var2, bool var3) {
      for (int var4 = 0; var4 < this.models.size(); var4++) {
    ModelInfo var5 = this.models.get(var4);
         if (var5.part == var1 && var5.scriptModel == var2) {
            if (var3) {
    return var5;
            }

            if (var5.m_animPlayer != nullptr) {
               var5.m_animPlayer = (AnimationPlayer)Pool.tryRelease(var5.m_animPlayer);
            }

            this.models.remove(var4);
            if (this.createdModel) {
               ModelManager.instance.Remove(this);
               ModelManager.instance.addVehicle(this);
            }

            var1.updateFlags = (short)(var1.updateFlags | 64);
            this.updateFlags = (short)(this.updateFlags | 64);
    return nullptr;
         }
      }

      if (var3) {
    ModelInfo var6 = std::make_shared<ModelInfo>();
         var6.part = var1;
         var6.scriptModel = var2;
         var6.modelScript = ScriptManager.instance.getModelScript(var2.file);
         var6.wheelIndex = var1.getWheelIndex();
         this.models.push_back(var6);
         if (this.createdModel) {
            ModelManager.instance.Remove(this);
            ModelManager.instance.addVehicle(this);
         }

         var1.updateFlags = (short)(var1.updateFlags | 64);
         this.updateFlags = (short)(this.updateFlags | 64);
    return var6;
      } else {
    return nullptr;
      }
   }

    ModelInfo getModelInfoForPart(VehiclePart var1) {
      for (int var2 = 0; var2 < this.models.size(); var2++) {
    ModelInfo var3 = this.models.get(var2);
         if (var3.part == var1) {
    return var3;
         }
      }

    return nullptr;
   }

   protected zombie.scripting.objects.VehicleScript.Passenger getScriptPassenger(int var1) {
      if (this.getScript() == nullptr) {
    return nullptr;
      } else {
         return var1 >= 0 && var1 < this.getScript().getPassengerCount() ? this.getScript().getPassenger(var1) : nullptr;
      }
   }

    int getMaxPassengers() {
      return this.passengers.length;
   }

    bool setPassenger(int var1, IsoGameCharacter var2, Vector3f var3) {
      if (var1 >= 0 && var1 < this.passengers.length) {
         if (var1 == 0) {
            this.setNeedPartsUpdate(true);
         }

         this.passengers[var1].character = var2;
         this.passengers[var1].offset.set(var3);
    return true;
      } else {
    return false;
      }
   }

    bool clearPassenger(int var1) {
      if (var1 >= 0 && var1 < this.passengers.length) {
         this.passengers[var1].character = nullptr;
         this.passengers[var1].offset.set(0.0F, 0.0F, 0.0F);
    return true;
      } else {
    return false;
      }
   }

    Passenger getPassenger(int var1) {
      return var1 >= 0 && var1 < this.passengers.length ? this.passengers[var1] : nullptr;
   }

    IsoGameCharacter getCharacter(int var1) {
    Passenger var2 = this.getPassenger(var1);
      return var2 != nullptr ? var2.character : nullptr;
   }

    int getSeat(IsoGameCharacter var1) {
      for (int var2 = 0; var2 < this.getMaxPassengers(); var2++) {
         if (this.getCharacter(var2) == var1) {
    return var2;
         }
      }

      return -1;
   }

    bool isDriver(IsoGameCharacter var1) {
      return this.getSeat(var1) == 0;
   }

    Vector3f getWorldPos(Vector3f var1, Vector3f var2, VehicleScript var3) {
      return this.getWorldPos(var1.x, var1.y, var1.z, var2, var3);
   }

    Vector3f getWorldPos(float var1, float var2, float var3, Vector3f var4, VehicleScript var5) {
    Transform var6 = this.getWorldTransform(this.tempTransform);
      var6.origin.set(0.0F, 0.0F, 0.0F);
      var4.set(var1, var2, var3);
      var6.transform(var4);
    float var7 = this.jniTransform.origin.x + WorldSimulation.instance.offsetX;
    float var8 = this.jniTransform.origin.z + WorldSimulation.instance.offsetY;
    float var9 = this.jniTransform.origin.y / 2.46F;
      var4.set(var7 + var4.x, var8 + var4.z, var9 + var4.y);
    return var4;
   }

    Vector3f getWorldPos(Vector3f var1, Vector3f var2) {
      return this.getWorldPos(var1.x, var1.y, var1.z, var2, this.getScript());
   }

    Vector3f getWorldPos(float var1, float var2, float var3, Vector3f var4) {
      return this.getWorldPos(var1, var2, var3, var4, this.getScript());
   }

    Vector3f getLocalPos(Vector3f var1, Vector3f var2) {
      return this.getLocalPos(var1.x, var1.y, var1.z, var2);
   }

    Vector3f getLocalPos(float var1, float var2, float var3, Vector3f var4) {
    Transform var5 = this.getWorldTransform(this.tempTransform);
      var5.inverse();
      var4.set(var1 - WorldSimulation.instance.offsetX, 0.0F, var2 - WorldSimulation.instance.offsetY);
      var5.transform(var4);
    return var4;
   }

    Vector3f getPassengerLocalPos(int var1, Vector3f var2) {
    Passenger var3 = this.getPassenger(var1);
    return var3 = = nullptr ? nullptr : var2.set(this.script.getModel().getOffset()).push_back(var3.offset);
   }

    Vector3f getPassengerWorldPos(int var1, Vector3f var2) {
    Passenger var3 = this.getPassenger(var1);
    return var3 = = nullptr ? nullptr : this.getPassengerPositionWorldPos(var3.offset.x, var3.offset.y, var3.offset.z, var2);
   }

    Vector3f getPassengerPositionWorldPos(Position var1, Vector3f var2) {
      return this.getPassengerPositionWorldPos(var1.offset.x, var1.offset.y, var1.offset.z, var2);
   }

    Vector3f getPassengerPositionWorldPos(float var1, float var2, float var3, Vector3f var4) {
      var4.set(this.script.getModel().offset);
      var4.push_back(var1, var2, var3);
      this.getWorldPos(var4.x, var4.y, var4.z, var4);
      var4.z = (int)this.getZ();
    return var4;
   }

    Anim getPassengerAnim(int var1, const std::string& var2) {
      zombie.scripting.objects.VehicleScript.Passenger var3 = this.getScriptPassenger(var1);
      if (var3 == nullptr) {
    return nullptr;
      } else {
         for (int var4 = 0; var4 < var3.anims.size(); var4++) {
    Anim var5 = (Anim)var3.anims.get(var4);
            if (var2 == var5.id)) {
    return var5;
            }
         }

    return nullptr;
      }
   }

    Position getPassengerPosition(int var1, const std::string& var2) {
      zombie.scripting.objects.VehicleScript.Passenger var3 = this.getScriptPassenger(var1);
    return var3 = = nullptr ? nullptr : var3.getPositionById(var2);
   }

    VehiclePart getPassengerDoor(int var1) {
      zombie.scripting.objects.VehicleScript.Passenger var2 = this.getScriptPassenger(var1);
    return var2 = = nullptr ? nullptr : this.getPartById(var2.door);
   }

    VehiclePart getPassengerDoor2(int var1) {
      zombie.scripting.objects.VehicleScript.Passenger var2 = this.getScriptPassenger(var1);
    return var2 = = nullptr ? nullptr : this.getPartById(var2.door2);
   }

    bool isPositionOnLeftOrRight(float var1, float var2) {
    Vector3f var3 = (Vector3f)TL_vector3f_pool.get().alloc();
      this.getLocalPos(var1, var2, 0.0F, var3);
      var1 = var3.x;
      TL_vector3f_pool.get().release(var3);
    Vector3f var4 = this.script.getExtents();
    Vector3f var5 = this.script.getCenterOfMassOffset();
    float var6 = var5.x - var4.x / 2.0F;
    float var7 = var5.x + var4.x / 2.0F;
      return var1 < var6 * 0.98F || var1 > var7 * 0.98F;
   }

    bool haveOneDoorUnlocked() {
      for (int var1 = 0; var1 < this.getPartCount(); var1++) {
    VehiclePart var2 = this.getPartByIndex(var1);
         if (var2.getDoor() != nullptr
            && (var2.getId().contains("Left") || var2.getId().contains("Right"))
            && (!var2.getDoor().isLocked() || var2.getDoor().isOpen())) {
    return true;
         }
      }

    return false;
   }

    std::string getPassengerArea(int var1) {
      zombie.scripting.objects.VehicleScript.Passenger var2 = this.getScriptPassenger(var1);
    return var2 = = nullptr ? nullptr : var2.area;
   }

    void playPassengerAnim(int var1, const std::string& var2) {
    IsoGameCharacter var3 = this.getCharacter(var1);
      this.playPassengerAnim(var1, var2, var3);
   }

    void playPassengerAnim(int var1, const std::string& var2, IsoGameCharacter var3) {
      if (var3 != nullptr) {
    Anim var4 = this.getPassengerAnim(var1, var2);
         if (var4 != nullptr) {
            this.playCharacterAnim(var3, var4, true);
         }
      }
   }

    void playPassengerSound(int var1, const std::string& var2) {
    Anim var3 = this.getPassengerAnim(var1, var2);
      if (var3 != nullptr && var3.sound != nullptr) {
         this.playSound(var3.sound);
      }
   }

    void playPartAnim(VehiclePart var1, const std::string& var2) {
      if (this.parts.contains(var1)) {
    Anim var3 = var1.getAnimById(var2);
         if (var3 != nullptr && !StringUtils.isNullOrWhitespace(var3.anim)) {
    ModelInfo var4 = this.getModelInfoForPart(var1);
            if (var4 != nullptr) {
    AnimationPlayer var5 = var4.getAnimationPlayer();
               if (var5 != nullptr && var5.isReady()) {
                  if (var5.getMultiTrack().getIndexOfTrack(var4.m_track) != -1) {
                     var5.getMultiTrack().removeTrack(var4.m_track);
                  }

                  var4.m_track = nullptr;
    SkinningData var6 = var5.getSkinningData();
                  if (var6 == nullptr || var6.AnimationClips.containsKey(var3.anim)) {
    AnimationTrack var7 = var5.play(var3.anim, var3.bLoop);
                     var4.m_track = var7;
                     if (var7 != nullptr) {
                        var7.setLayerIdx(0);
                        var7.BlendDelta = 1.0F;
                        var7.SpeedDelta = var3.rate;
                        var7.IsPlaying = var3.bAnimate;
                        var7.reverse = var3.bReverse;
                        if (!var4.modelScript.boneWeights.empty()) {
                           var7.setBoneWeights(var4.modelScript.boneWeights);
                           var7.initBoneWeights(var6);
                        }

                        if (var1.getWindow() != nullptr) {
                           var7.setCurrentTimeValue(var7.getDuration() * var1.getWindow().getOpenDelta());
                        }
                     }
                  }
               }
            }
         }
      }
   }

    void playActorAnim(VehiclePart var1, const std::string& var2, IsoGameCharacter var3) {
      if (var3 != nullptr) {
         if (this.parts.contains(var1)) {
    Anim var4 = var1.getAnimById("Actor" + var2);
            if (var4 != nullptr) {
               this.playCharacterAnim(var3, var4, !"EngineDoor" == var1.getId()));
            }
         }
      }
   }

    void playCharacterAnim(IsoGameCharacter var1, Anim var2, bool var3) {
      var1.PlayAnimUnlooped(var2.anim);
      var1.getSpriteDef().setFrameSpeedPerFrame(var2.rate);
      var1.getLegsSprite().Animate = true;
    Vector3f var4 = this.getForwardVector((Vector3f)TL_vector3f_pool.get().alloc());
      if (var2.angle.lengthSquared() != 0.0F) {
    Matrix4f var5 = (Matrix4f)TL_matrix4f_pool.get().alloc();
         var5.rotationXYZ((float)Math.toRadians(var2.angle.x), (float)Math.toRadians(var2.angle.y), (float)Math.toRadians(var2.angle.z));
         var4.rotate(var5.getNormalizedRotation(this.tempQuat4f));
         TL_matrix4f_pool.get().release(var5);
      }

    Vector2 var6 = (Vector2)TL_vector2_pool.get().alloc();
      var6.set(var4.x, var4.z);
      var1.DirectionFromVector(var6);
      TL_vector2_pool.get().release(var6);
      var1.setForwardDirection(var4.x, var4.z);
      if (var1.getAnimationPlayer() != nullptr) {
         var1.getAnimationPlayer().setTargetAngle(var1.getForwardDirection().getDirection());
         if (var3) {
            var1.getAnimationPlayer().setAngleToTarget();
         }
      }

      TL_vector3f_pool.get().release(var4);
   }

    void playPartSound(VehiclePart var1, IsoPlayer var2, const std::string& var3) {
      if (this.parts.contains(var1)) {
    Anim var4 = var1.getAnimById(var3);
         if (var4 != nullptr && var4.sound != nullptr) {
            this.getEmitter().playSound(var4.sound, var2);
         }
      }
   }

    void setCharacterPosition(IsoGameCharacter var1, int var2, const std::string& var3) {
      zombie.scripting.objects.VehicleScript.Passenger var4 = this.getScriptPassenger(var2);
      if (var4 != nullptr) {
    Position var5 = var4.getPositionById(var3);
         if (var5 != nullptr) {
            if (this.getCharacter(var2) == var1) {
               this.passengers[var2].offset.set(var5.offset);
            } else {
    Vector3f var6 = (Vector3f)TL_vector3f_pool.get().alloc();
               if (var5.area == nullptr) {
                  this.getPassengerPositionWorldPos(var5, var6);
               } else {
    Area var7 = this.script.getAreaById(var5.area);
    Vector2 var8 = (Vector2)TL_vector2_pool.get().alloc();
    Vector2 var9 = this.areaPositionWorld4PlayerInteract(var7, var8);
                  var6.x = var9.x;
                  var6.y = var9.y;
                  var6.z = 0.0F;
                  TL_vector2_pool.get().release(var8);
               }

               var1.setX(var6.x);
               var1.setY(var6.y);
               var1.setZ(0.0F);
               TL_vector3f_pool.get().release(var6);
            }

            if (dynamic_cast<IsoPlayer*>(var1) != nullptr && ((IsoPlayer)var1).isLocalPlayer()) {
               ((IsoPlayer)var1).dirtyRecalcGridStackTime = 10.0F;
            }
         }
      }
   }

    void transmitCharacterPosition(int var1, const std::string& var2) {
      if (GameClient.bClient) {
         VehicleManager.instance.sendPassengerPosition(this, var1, var2);
      }
   }

    void setCharacterPositionToAnim(IsoGameCharacter var1, int var2, const std::string& var3) {
    Anim var4 = this.getPassengerAnim(var2, var3);
      if (var4 != nullptr) {
         if (this.getCharacter(var2) == var1) {
            this.passengers[var2].offset.set(var4.offset);
         } else {
    Vector3f var5 = this.getWorldPos(var4.offset, (Vector3f)TL_vector3f_pool.get().alloc());
            var1.setX(var5.x);
            var1.setY(var5.y);
            var1.setZ(0.0F);
            TL_vector3f_pool.get().release(var5);
         }
      }
   }

    int getPassengerSwitchSeatCount(int var1) {
      zombie.scripting.objects.VehicleScript.Passenger var2 = this.getScriptPassenger(var1);
    return var2 = = nullptr ? -1 : var2.switchSeats.size();
   }

    SwitchSeat getPassengerSwitchSeat(int var1, int var2) {
      zombie.scripting.objects.VehicleScript.Passenger var3 = this.getScriptPassenger(var1);
      if (var3 == nullptr) {
    return nullptr;
      } else {
         return var2 >= 0 && var2 < var3.switchSeats.size() ? (SwitchSeat)var3.switchSeats.get(var2) : nullptr;
      }
   }

    SwitchSeat getSwitchSeat(int var1, int var2) {
      zombie.scripting.objects.VehicleScript.Passenger var3 = this.getScriptPassenger(var1);
      if (var3 == nullptr) {
    return nullptr;
      } else {
         for (int var4 = 0; var4 < var3.switchSeats.size(); var4++) {
    SwitchSeat var5 = (SwitchSeat)var3.switchSeats.get(var4);
            if (var5.seat == var2 && this.getPartForSeatContainer(var2) != nullptr && this.getPartForSeatContainer(var2).getInventoryItem() != nullptr) {
    return var5;
            }
         }

    return nullptr;
      }
   }

    std::string getSwitchSeatAnimName(int var1, int var2) {
    SwitchSeat var3 = this.getSwitchSeat(var1, var2);
    return var3 = = nullptr ? nullptr : var3.anim;
   }

    float getSwitchSeatAnimRate(int var1, int var2) {
    SwitchSeat var3 = this.getSwitchSeat(var1, var2);
    return var3 = = nullptr ? 0.0F : var3.rate;
   }

    std::string getSwitchSeatSound(int var1, int var2) {
    SwitchSeat var3 = this.getSwitchSeat(var1, var2);
    return var3 = = nullptr ? nullptr : var3.sound;
   }

    bool canSwitchSeat(int var1, int var2) {
    SwitchSeat var3 = this.getSwitchSeat(var1, var2);
      return var3 != nullptr;
   }

    void switchSeat(IsoGameCharacter var1, int var2) {
    int var3 = this.getSeat(var1);
      if (var3 != -1) {
         this.clearPassenger(var3);
    Position var4 = this.getPassengerPosition(var2, "inside");
         if (var4 == nullptr) {
    Vector3f var5 = (Vector3f)TL_vector3f_pool.get().alloc();
            var5.set(0.0F, 0.0F, 0.0F);
            this.setPassenger(var2, var1, var5);
            TL_vector3f_pool.get().release(var5);
         } else {
            this.setPassenger(var2, var1, var4.offset);
         }
      }
   }

    void playSwitchSeatAnim(int var1, int var2) {
    IsoGameCharacter var3 = this.getCharacter(var1);
      if (var3 != nullptr) {
    SwitchSeat var4 = this.getSwitchSeat(var1, var2);
         if (var4 != nullptr) {
            var3.PlayAnimUnlooped(var4.anim);
            var3.getSpriteDef().setFrameSpeedPerFrame(var4.rate);
            var3.getLegsSprite().Animate = true;
         }
      }
   }

    bool isSeatOccupied(int var1) {
    VehiclePart var2 = this.getPartForSeatContainer(var1);
      return var2 != nullptr && var2.getItemContainer() != nullptr && !var2.getItemContainer().getItems().empty() ? true : this.getCharacter(var1) != nullptr;
   }

    bool isSeatInstalled(int var1) {
    VehiclePart var2 = this.getPartForSeatContainer(var1);
      return var2 != nullptr && var2.getInventoryItem() != nullptr;
   }

    int getBestSeat(IsoGameCharacter var1) {
      if ((int)this.getZ() != (int)var1.getZ()) {
         return -1;
      } else if (var1.DistTo(this) > 5.0F) {
         return -1;
      } else {
    VehicleScript var2 = this.getScript();
         if (var2 == nullptr) {
            return -1;
         } else {
    Vector3f var3 = (Vector3f)TL_vector3f_pool.get().alloc();
    Vector3f var4 = (Vector3f)TL_vector3f_pool.get().alloc();
    Vector2 var5 = (Vector2)TL_vector2_pool.get().alloc();

            for (int var6 = 0; var6 < var2.getPassengerCount(); var6++) {
               if (!this.isEnterBlocked(var1, var6) && !this.isSeatOccupied(var6)) {
    Position var7 = this.getPassengerPosition(var6, "outside");
                  if (var7 != nullptr) {
                     this.getPassengerPositionWorldPos(var7, var3);
    float var8 = var3.x;
    float var9 = var3.y;
                     this.getPassengerPositionWorldPos(0.0F, var7.offset.y, var7.offset.z, var4);
                     var5.set(var4.x - var1.getX(), var4.y - var1.getY());
                     var5.normalize();
    float var10 = var5.dot(var1.getForwardDirection());
                     if (var10 > 0.5F && IsoUtils.DistanceTo(var1.getX(), var1.getY(), var8, var9) < 1.0F) {
                        TL_vector3f_pool.get().release(var3);
                        TL_vector3f_pool.get().release(var4);
                        TL_vector2_pool.get().release(var5);
    return var6;
                     }
                  }

                  var7 = this.getPassengerPosition(var6, "outside2");
                  if (var7 != nullptr) {
                     this.getPassengerPositionWorldPos(var7, var3);
    float var12 = var3.x;
    float var13 = var3.y;
                     this.getPassengerPositionWorldPos(0.0F, var7.offset.y, var7.offset.z, var4);
                     var5.set(var4.x - var1.getX(), var4.y - var1.getY());
                     var5.normalize();
    float var14 = var5.dot(var1.getForwardDirection());
                     if (var14 > 0.5F && IsoUtils.DistanceTo(var1.getX(), var1.getY(), var12, var13) < 1.0F) {
                        TL_vector3f_pool.get().release(var3);
                        TL_vector3f_pool.get().release(var4);
                        TL_vector2_pool.get().release(var5);
    return var6;
                     }
                  }
               }
            }

            TL_vector3f_pool.get().release(var3);
            TL_vector3f_pool.get().release(var4);
            TL_vector2_pool.get().release(var5);
            return -1;
         }
      }
   }

    void updateHasExtendOffsetForExit(IsoGameCharacter var1) {
      this.hasExtendOffsetExiting = true;
      this.updateHasExtendOffset(var1);
      this.getPoly();
   }

    void updateHasExtendOffsetForExitEnd(IsoGameCharacter var1) {
      this.hasExtendOffsetExiting = false;
      this.updateHasExtendOffset(var1);
      this.getPoly();
   }

    void updateHasExtendOffset(IsoGameCharacter var1) {
      this.hasExtendOffset = false;
      this.hasExtendOffsetExiting = false;
   }

    VehiclePart getUseablePart(IsoGameCharacter var1) {
      return this.getUseablePart(var1, true);
   }

    VehiclePart getUseablePart(IsoGameCharacter var1, bool var2) {
      if (var1.getVehicle() != nullptr) {
    return nullptr;
      } else if ((int)this.getZ() != (int)var1.getZ()) {
    return nullptr;
      } else if (var1.DistTo(this) > 6.0F) {
    return nullptr;
      } else {
    VehicleScript var3 = this.getScript();
         if (var3 == nullptr) {
    return nullptr;
         } else {
    Vector3f var4 = var3.getExtents();
    Vector3f var5 = var3.getCenterOfMassOffset();
    float var6 = var5.z - var4.z / 2.0F;
    float var7 = var5.z + var4.z / 2.0F;
    Vector2 var8 = (Vector2)TL_vector2_pool.get().alloc();
    Vector3f var9 = (Vector3f)TL_vector3f_pool.get().alloc();

            for (int var10 = 0; var10 < this.parts.size(); var10++) {
    VehiclePart var11 = this.parts.get(var10);
               if (var11.getArea() != nullptr && this.isInArea(var11.getArea(), var1)) {
    std::string var12 = var11.getLuaFunction("use");
                  if (var12 != nullptr && !var12 == "")) {
    Area var13 = var3.getAreaById(var11.getArea());
                     if (var13 != nullptr) {
    Vector2 var14 = this.areaPositionLocal(var13, var8);
                        if (var14 != nullptr) {
    float var15 = 0.0F;
    float var16 = 0.0F;
    float var17 = 0.0F;
                           if (!(var14.y >= var7) && !(var14.y <= var6)) {
                              var17 = var14.y;
                           } else {
                              var15 = var14.x;
                           }

                           if (!var2) {
    return var11;
                           }

                           this.getWorldPos(var15, var16, var17, var9);
                           var8.set(var9.x - var1.getX(), var9.y - var1.getY());
                           var8.normalize();
    float var19 = var8.dot(var1.getForwardDirection());
                           if (var19 > 0.5F && !PolygonalMap2.instance.lineClearCollide(var1.x, var1.y, var9.x, var9.y, (int)var1.z, this, false, true)) {
                              TL_vector2_pool.get().release(var8);
                              TL_vector3f_pool.get().release(var9);
    return var11;
                           }
                           break;
                        }
                     }
                  }
               }
            }

            TL_vector2_pool.get().release(var8);
            TL_vector3f_pool.get().release(var9);
    return nullptr;
         }
      }
   }

    VehiclePart getClosestWindow(IsoGameCharacter var1) {
      if ((int)this.getZ() != (int)var1.getZ()) {
    return nullptr;
      } else if (var1.DistTo(this) > 5.0F) {
    return nullptr;
      } else {
    Vector3f var2 = this.script.getExtents();
    Vector3f var3 = this.script.getCenterOfMassOffset();
    float var4 = var3.z - var2.z / 2.0F;
    float var5 = var3.z + var2.z / 2.0F;
    Vector2 var6 = (Vector2)TL_vector2_pool.get().alloc();
    Vector3f var7 = (Vector3f)TL_vector3f_pool.get().alloc();

         for (int var8 = 0; var8 < this.parts.size(); var8++) {
    VehiclePart var9 = this.parts.get(var8);
            if (var9.getWindow() != nullptr && var9.getArea() != nullptr && this.isInArea(var9.getArea(), var1)) {
    Area var10 = this.script.getAreaById(var9.getArea());
               if (!(var10.y >= var5) && !(var10.y <= var4)) {
                  var7.set(0.0F, 0.0F, var10.y);
               } else {
                  var7.set(var10.x, 0.0F, 0.0F);
               }

               this.getWorldPos(var7, var7);
               var6.set(var7.x - var1.getX(), var7.y - var1.getY());
               var6.normalize();
    float var12 = var6.dot(var1.getForwardDirection());
               if (var12 > 0.5F) {
                  TL_vector2_pool.get().release(var6);
                  TL_vector3f_pool.get().release(var7);
    return var9;
               }
               break;
            }
         }

         TL_vector2_pool.get().release(var6);
         TL_vector3f_pool.get().release(var7);
    return nullptr;
      }
   }

    void getFacingPosition(IsoGameCharacter var1, Vector2 var2) {
    Vector3f var3 = this.getLocalPos(var1.getX(), var1.getY(), var1.getZ(), (Vector3f)TL_vector3f_pool.get().alloc());
    Vector3f var4 = this.script.getExtents();
    Vector3f var5 = this.script.getCenterOfMassOffset();
    float var6 = var5.x - var4.x / 2.0F;
    float var7 = var5.x + var4.x / 2.0F;
    float var8 = var5.z - var4.z / 2.0F;
    float var9 = var5.z + var4.z / 2.0F;
    float var10 = 0.0F;
    float var11 = 0.0F;
      if (var3.x <= 0.0F && var3.z >= var8 && var3.z <= var9) {
         var11 = var3.z;
      } else if (var3.x > 0.0F && var3.z >= var8 && var3.z <= var9) {
         var11 = var3.z;
      } else if (var3.z <= 0.0F && var3.x >= var6 && var3.x <= var7) {
         var10 = var3.x;
      } else if (var3.z > 0.0F && var3.x >= var6 && var3.x <= var7) {
         var10 = var3.x;
      }

      this.getWorldPos(var10, 0.0F, var11, var3);
      var2.set(var3.x, var3.y);
      TL_vector3f_pool.get().release(var3);
   }

    bool enter(int var1, IsoGameCharacter var2, Vector3f var3) {
      if (!GameClient.bClient) {
         VehiclesDB2.instance.updateVehicleAndTrailer(this);
      }

      if (var2 == nullptr) {
    return false;
      } else if (var2.getVehicle() != nullptr && !var2.getVehicle().exit(var2)) {
    return false;
      } else if (this.setPassenger(var1, var2, var3)) {
         var2.setVehicle(this);
         var2.setCollidable(false);
         if (GameClient.bClient) {
            VehicleManager.instance.sendEnter(GameClient.connection, this, var2, var1);
         }

         if (dynamic_cast<IsoPlayer*>(var2) != nullptr && ((IsoPlayer)var2).isLocalPlayer()) {
            ((IsoPlayer)var2).dirtyRecalcGridStackTime = 10.0F;
         }

    return true;
      } else {
    return false;
      }
   }

    bool enter(int var1, IsoGameCharacter var2) {
      if (this.getPartForSeatContainer(var1) != nullptr && this.getPartForSeatContainer(var1).getInventoryItem() != nullptr) {
    Position var3 = this.getPassengerPosition(var1, "outside");
         return var3 != nullptr ? this.enter(var1, var2, var3.offset) : false;
      } else {
    return false;
      }
   }

    bool enterRSync(int var1, IsoGameCharacter var2, BaseVehicle var3) {
      if (var2 == nullptr) {
    return false;
      } else {
    Position var4 = this.getPassengerPosition(var1, "inside");
         if (var4 != nullptr) {
            if (this.setPassenger(var1, var2, var4.offset)) {
               var2.setVehicle(var3);
               var2.setCollidable(false);
               if (GameClient.bClient) {
                  LuaEventManager.triggerEvent("OnContainerUpdate");
               }

    return true;
            } else {
    return false;
            }
         } else {
    return false;
         }
      }
   }

    bool exit(IsoGameCharacter var1) {
      if (!GameClient.bClient) {
         VehiclesDB2.instance.updateVehicleAndTrailer(this);
      }

      if (var1 == nullptr) {
    return false;
      } else {
    int var2 = this.getSeat(var1);
         if (var2 == -1) {
    return false;
         } else if (this.clearPassenger(var2)) {
            this.enginePower = (int)this.getScript().getEngineForce();
            var1.setVehicle(nullptr);
            var1.savedVehicleSeat = -1;
            var1.setCollidable(true);
            if (GameClient.bClient) {
               VehicleManager.instance.sendExit(GameClient.connection, this, var1, var2);
            }

            if (this.getDriver() == nullptr && this.soundHornOn) {
               this.onHornStop();
            }

            this.polyGarageCheck = true;
            this.polyDirty = true;
    return true;
         } else {
    return false;
         }
      }
   }

    bool exitRSync(IsoGameCharacter var1) {
      if (var1 == nullptr) {
    return false;
      } else {
    int var2 = this.getSeat(var1);
         if (var2 == -1) {
    return false;
         } else if (this.clearPassenger(var2)) {
            var1.setVehicle(nullptr);
            var1.setCollidable(true);
            if (GameClient.bClient) {
               LuaEventManager.triggerEvent("OnContainerUpdate");
            }

    return true;
         } else {
    return false;
         }
      }
   }

    bool hasRoof(int var1) {
      zombie.scripting.objects.VehicleScript.Passenger var2 = this.getScriptPassenger(var1);
    return var2 = = nullptr ? false : var2.hasRoof;
   }

    bool showPassenger(int var1) {
      zombie.scripting.objects.VehicleScript.Passenger var2 = this.getScriptPassenger(var1);
    return var2 = = nullptr ? false : var2.showPassenger;
   }

    bool showPassenger(IsoGameCharacter var1) {
    int var2 = this.getSeat(var1);
      return this.showPassenger(var2);
   }

    void save(ByteBuffer var1, bool var2) {
      if (this.square != nullptr) {
    float var3 = 5.0E-4F;
         this.x = PZMath.clamp(this.x, this.square.x + var3, this.square.x + 1 - var3);
         this.y = PZMath.clamp(this.y, this.square.y + var3, this.square.y + 1 - var3);
      }

      super.save(var1, var2);
    Quaternionf var7 = this.savedRot;
    Transform var4 = this.getWorldTransform(this.tempTransform);
      var1.putFloat(var4.origin.y);
      var4.getRotation(var7);
      var1.putFloat(var7.x);
      var1.putFloat(var7.y);
      var1.putFloat(var7.z);
      var1.putFloat(var7.w);
      GameWindow.WriteStringUTF(var1, this.scriptName);
      var1.putInt(this.skinIndex);
      var1.put((byte)(this.isEngineRunning() ? 1 : 0));
      var1.putInt(this.frontEndDurability);
      var1.putInt(this.rearEndDurability);
      var1.putInt(this.currentFrontEndDurability);
      var1.putInt(this.currentRearEndDurability);
      var1.putInt(this.engineLoudness);
      var1.putInt(this.engineQuality);
      var1.putInt(this.keyId);
      var1.put(this.keySpawned);
      var1.put((byte)(this.headlightsOn ? 1 : 0));
      var1.put((byte)(this.bCreated ? 1 : 0));
      var1.put((byte)(this.soundHornOn ? 1 : 0));
      var1.put((byte)(this.soundBackMoveOn ? 1 : 0));
      var1.put((byte)this.lightbarLightsMode.get());
      var1.put((byte)this.lightbarSirenMode.get());
      var1.putShort((short)this.parts.size());

      for (int var5 = 0; var5 < this.parts.size(); var5++) {
    VehiclePart var6 = this.parts.get(var5);
         var6.save(var1);
      }

      var1.put((byte)(this.keyIsOnDoor ? 1 : 0));
      var1.put((byte)(this.hotwired ? 1 : 0));
      var1.put((byte)(this.hotwiredBroken ? 1 : 0));
      var1.put((byte)(this.keysInIgnition ? 1 : 0));
      var1.putFloat(this.rust);
      var1.putFloat(this.colorHue);
      var1.putFloat(this.colorSaturation);
      var1.putFloat(this.colorValue);
      var1.putInt(this.enginePower);
      var1.putShort(this.VehicleID);
      GameWindow.WriteString(var1, nullptr);
      var1.putInt(this.mechanicalID);
      var1.put((byte)(this.alarmed ? 1 : 0));
      var1.putDouble(this.sirenStartTime);
      if (this.getCurrentKey() != nullptr) {
         var1.put((byte)1);
         this.getCurrentKey().saveWithSize(var1, false);
      } else {
         var1.put((byte)0);
      }

      var1.put((byte)this.bloodIntensity.size());

      for (Entry var9 : this.bloodIntensity.entrySet()) {
         GameWindow.WriteStringUTF(var1, (std::string)var9.getKey());
         var1.put((uint8_t)var9.getValue());
      }

      if (this.vehicleTowingID != -1) {
         var1.put((byte)1);
         var1.putInt(this.vehicleTowingID);
         GameWindow.WriteStringUTF(var1, this.towAttachmentSelf);
         GameWindow.WriteStringUTF(var1, this.towAttachmentOther);
         var1.putFloat(this.towConstraintZOffset);
      } else {
         var1.put((byte)0);
      }

      var1.putFloat(this.getRegulatorSpeed());
      var1.put((byte)(this.previouslyEntered ? 1 : 0));
   }

    void load(ByteBuffer var1, int var2, bool var3) {
      super.load(var1, var2, var3);
      if (this.z < 0.0F) {
         this.z = 0.0F;
      }

      if (var2 >= 173) {
         this.savedPhysicsZ = PZMath.clamp(var1.getFloat(), 0.0F, (int)this.z + 2.4477F);
      }

    float var4 = var1.getFloat();
    float var5 = var1.getFloat();
    float var6 = var1.getFloat();
    float var7 = var1.getFloat();
      this.savedRot.set(var4, var5, var6, var7);
      this.jniTransform
         .origin
         .set(
            this.getX() - WorldSimulation.instance.offsetX,
            float.isNaN(this.savedPhysicsZ) ? this.z : this.savedPhysicsZ,
            this.getY() - WorldSimulation.instance.offsetY
         );
      this.jniTransform.setRotation(this.savedRot);
      this.scriptName = GameWindow.ReadStringUTF(var1);
      this.skinIndex = var1.getInt();
    bool var8 = var1.get() == 1;
      if (var8) {
         this.engineState = engineStateTypes.Running;
      }

      this.frontEndDurability = var1.getInt();
      this.rearEndDurability = var1.getInt();
      this.currentFrontEndDurability = var1.getInt();
      this.currentRearEndDurability = var1.getInt();
      this.engineLoudness = var1.getInt();
      this.engineQuality = var1.getInt();
      this.engineQuality = PZMath.clamp(this.engineQuality, 0, 100);
      this.keyId = var1.getInt();
      this.keySpawned = var1.get();
      this.headlightsOn = var1.get() == 1;
      this.bCreated = var1.get() == 1;
      this.soundHornOn = var1.get() == 1;
      this.soundBackMoveOn = var1.get() == 1;
      this.lightbarLightsMode.set(var1.get());
      this.lightbarSirenMode.set(var1.get());
    short var9 = var1.getShort();

      for (int var10 = 0; var10 < var9; var10++) {
    VehiclePart var11 = std::make_shared<VehiclePart>(this);
         var11.load(var1, var2);
         this.parts.push_back(var11);
      }

      if (var2 >= 112) {
         this.keyIsOnDoor = var1.get() == 1;
         this.hotwired = var1.get() == 1;
         this.hotwiredBroken = var1.get() == 1;
         this.keysInIgnition = var1.get() == 1;
      }

      if (var2 >= 116) {
         this.rust = var1.getFloat();
         this.colorHue = var1.getFloat();
         this.colorSaturation = var1.getFloat();
         this.colorValue = var1.getFloat();
      }

      if (var2 >= 117) {
         this.enginePower = var1.getInt();
      }

      if (var2 >= 120) {
         var1.getShort();
      }

      if (var2 >= 122) {
    std::string var15 = GameWindow.ReadString(var1);
         this.mechanicalID = var1.getInt();
      }

      if (var2 >= 124) {
         this.alarmed = var1.get() == 1;
      }

      if (var2 >= 129) {
         this.sirenStartTime = var1.getDouble();
      }

      if (var2 >= 133 && var1.get() == 1) {
    InventoryItem var16 = nullptr;

         try {
            var16 = InventoryItem.loadItem(var1, var2);
         } catch (Exception var14) {
            var14.printStackTrace();
         }

         if (var16 != nullptr) {
            this.setCurrentKey(var16);
         }
      }

      if (var2 >= 165) {
    uint8_t var17 = var1.get();

         for (int var18 = 0; var18 < var17; var18++) {
    std::string var12 = GameWindow.ReadStringUTF(var1);
    uint8_t var13 = var1.get();
            this.bloodIntensity.put(var12, var13);
         }
      }

      if (var2 >= 174) {
         if (var1.get() == 1) {
            this.vehicleTowingID = var1.getInt();
            this.towAttachmentSelf = GameWindow.ReadStringUTF(var1);
            this.towAttachmentOther = GameWindow.ReadStringUTF(var1);
            this.towConstraintZOffset = var1.getFloat();
         }
      } else if (var2 >= 172) {
         this.vehicleTowingID = var1.getInt();
      }

      if (var2 >= 188) {
         this.setRegulatorSpeed(var1.getFloat());
      }

      if (var2 >= 195) {
         this.previouslyEntered = var1.get() == 1;
      }

      this.loaded = true;
   }

    void softReset() {
      this.keySpawned = 0;
      this.keyIsOnDoor = false;
      this.keysInIgnition = false;
      this.currentKey = nullptr;
      this.previouslyEntered = false;
      this.engineState = engineStateTypes.Idle;
      this.randomizeContainers();
   }

    void trySpawnKey() {
      if (!GameClient.bClient) {
         if (this.script != nullptr && this.script.getPartById("Engine") != nullptr) {
            if (this.keySpawned != 1) {
               if (SandboxOptions.getInstance().VehicleEasyUse.getValue()) {
                  this.addKeyToGloveBox();
               } else {
    VehicleType var1 = VehicleType.getTypeFromName(this.getVehicleType());
    int var2 = var1 == nullptr ? 70 : var1.getChanceToSpawnKey();
                  if (Rand.Next(100) <= var2) {
                     this.addKeyToWorld();
                  }

                  this.keySpawned = 1;
               }
            }
         }
      }
   }

    bool shouldCollideWithCharacters() {
      if (this.vehicleTowedBy != nullptr) {
         return this.vehicleTowedBy.shouldCollideWithCharacters();
      } else {
    float var1 = this.getSpeed2D();
         return this.isEngineRunning() ? var1 > 0.05F : var1 > 1.0F;
      }
   }

    bool shouldCollideWithObjects() {
      return this.vehicleTowedBy != nullptr ? this.vehicleTowedBy.shouldCollideWithObjects() : this.isEngineRunning();
   }

    void brekingObjects() {
    bool var1 = this.shouldCollideWithCharacters();
    bool var2 = this.shouldCollideWithObjects();
      if (var1 || var2) {
    Vector3f var3 = this.script.getExtents();
    Vector2 var4 = (Vector2)TL_vector2_pool.get().alloc();
    float var5 = Math.max(var3.x / 2.0F, var3.z / 2.0F) + 0.3F + 1.0F;
    int var6 = (int)Math.ceil(var5);

         for (int var7 = -var6; var7 < var6; var7++) {
            for (int var8 = -var6; var8 < var6; var8++) {
    IsoGridSquare var9 = this.getCell().getGridSquare(this.x + var8, this.y + var7, this.z);
               if (var9 != nullptr) {
                  if (var2) {
                     for (int var10 = 0; var10 < var9.getObjects().size(); var10++) {
    IsoObject var11 = (IsoObject)var9.getObjects().get(var10);
                        if (!(dynamic_cast<IsoWorldInventoryObject*>(var11) != nullptr)) {
    Vector2 var12 = nullptr;
                           if (!this.brekingObjectsList.contains(var11) && var11 != nullptr && var11.getProperties() != nullptr) {
                              if (var11.getProperties().Is("CarSlowFactor")) {
                                 var12 = this.testCollisionWithObject(var11, 0.3F, var4);
                              }

                              if (var12 != nullptr) {
                                 this.brekingObjectsList.push_back(var11);
                                 if (!GameClient.bClient) {
                                    var11.Collision(var12, this);
                                 }
                              }

                              if (var11.getProperties().Is("HitByCar")) {
                                 var12 = this.testCollisionWithObject(var11, 0.3F, var4);
                              }

                              if (var12 != nullptr && !GameClient.bClient) {
                                 var11.Collision(var12, this);
                              }

                              this.checkCollisionWithPlant(var9, var11, var4);
                           }
                        }
                     }
                  }

                  if (var1) {
                     for (int var17 = 0; var17 < var9.getMovingObjects().size(); var17++) {
    IsoMovingObject var20 = (IsoMovingObject)var9.getMovingObjects().get(var17);
    IsoZombie var22 = (IsoZombie)Type.tryCastTo(var20, IsoZombie.class);
                        if (var22 != nullptr) {
                           if (var22.isProne()) {
                              this.testCollisionWithProneCharacter(var22, false);
                           }

                           var22.setVehicle4TestCollision(this);
                        }

                        if (dynamic_cast<IsoPlayer*>(var20) != nullptr && var20 != this.getDriver()) {
    IsoPlayer var13 = (IsoPlayer)var20;
                           var13.setVehicle4TestCollision(this);
                        }
                     }
                  }

                  if (var2) {
                     for (int var18 = 0; var18 < var9.getStaticMovingObjects().size(); var18++) {
    IsoMovingObject var21 = (IsoMovingObject)var9.getStaticMovingObjects().get(var18);
    IsoDeadBody var23 = (IsoDeadBody)Type.tryCastTo(var21, IsoDeadBody.class);
                        if (var23 != nullptr) {
    int var24 = this.testCollisionWithCorpse(var23, true);
                        }
                     }
                  }
               }
            }
         }

    float var14 = -999.0F;

         for (int var15 = 0; var15 < this.brekingObjectsList.size(); var15++) {
    IsoObject var16 = this.brekingObjectsList.get(var15);
    Vector2 var19 = this.testCollisionWithObject(var16, 1.0F, var4);
            if (var19 == nullptr || !var16.getSquare().getObjects().contains(var16)) {
               this.brekingObjectsList.remove(var16);
               var16.UnCollision(this);
            } else if (var14 < var16.GetVehicleSlowFactor(this)) {
               var14 = var16.GetVehicleSlowFactor(this);
            }
         }

         if (var14 != -999.0F) {
            this.brekingSlowFactor = PZMath.clamp(var14, 0.0F, 34.0F);
         } else {
            this.brekingSlowFactor = 0.0F;
         }

         TL_vector2_pool.get().release(var4);
      }
   }

    void updateVelocityMultiplier() {
      if (this.physics != nullptr && this.getScript() != nullptr) {
    Vector3f var1 = this.getLinearVelocity((Vector3f)TL_vector3f_pool.get().alloc());
         var1.y = 0.0F;
    float var2 = var1.length();
    float var3 = 100000.0F;
    float var4 = 1.0F;
         if (this.getScript().getWheelCount() > 0) {
            if (var2 > 0.0F && var2 > 34.0F - this.brekingSlowFactor) {
               var3 = 34.0F - this.brekingSlowFactor;
               var4 = (34.0F - this.brekingSlowFactor) / var2;
            }
         } else if (this.getVehicleTowedBy() == nullptr) {
            var3 = 0.0F;
            var4 = 0.1F;
         }

         Bullet.setVehicleVelocityMultiplier(this.VehicleID, var3, var4);
         TL_vector3f_pool.get().release(var1);
      }
   }

    void playScrapePastPlantSound(IsoGridSquare var1) {
      if (this.emitter != nullptr && !this.emitter.isPlaying(this.soundScrapePastPlant)) {
         this.emitter.setPos(var1.x + 0.5F, var1.y + 0.5F, var1.z);
         this.soundScrapePastPlant = this.emitter.playSoundImpl("VehicleScrapePastPlant", var1);
      }
   }

    void checkCollisionWithPlant(IsoGridSquare var1, IsoObject var2, Vector2 var3) {
    IsoTree var4 = (IsoTree)Type.tryCastTo(var2, IsoTree.class);
      if (var4 != nullptr || var2.getProperties().Is("Bush")) {
    float var5 = Math.abs(this.getCurrentSpeedKmHour());
         if (!(var5 <= 1.0F)) {
    Vector2 var6 = this.testCollisionWithObject(var2, 0.3F, var3);
            if (var6 != nullptr) {
               if (var4 != nullptr && var4.getSize() == 1) {
                  this.ApplyImpulse4Break(var2, 0.025F);
                  this.playScrapePastPlantSound(var1);
               } else if (this.isPositionOnLeftOrRight(var6.x, var6.y)) {
                  this.ApplyImpulse4Break(var2, 0.025F);
                  this.playScrapePastPlantSound(var1);
               } else if (var5 < 10.0F) {
                  this.ApplyImpulse4Break(var2, 0.025F);
                  this.playScrapePastPlantSound(var1);
               } else {
                  this.ApplyImpulse4Break(var2, 0.1F);
                  this.playScrapePastPlantSound(var1);
               }
            }
         }
      }
   }

    void damageObjects(float var1) {
      if (this.isEngineRunning()) {
    Vector3f var2 = this.script.getExtents();
    Vector2 var3 = (Vector2)TL_vector2_pool.get().alloc();
    float var4 = Math.max(var2.x / 2.0F, var2.z / 2.0F) + 0.3F + 1.0F;
    int var5 = (int)Math.ceil(var4);

         for (int var6 = -var5; var6 < var5; var6++) {
            for (int var7 = -var5; var7 < var5; var7++) {
    IsoGridSquare var8 = this.getCell().getGridSquare(this.x + var7, this.y + var6, this.z);
               if (var8 != nullptr) {
                  for (int var9 = 0; var9 < var8.getObjects().size(); var9++) {
    IsoObject var10 = (IsoObject)var8.getObjects().get(var9);
    Vector2 var11 = nullptr;
                     if (dynamic_cast<IsoTree*>(var10) != nullptr) {
                        var11 = this.testCollisionWithObject(var10, 2.0F, var3);
                        if (var11 != nullptr) {
                           var10.setRenderEffect(RenderEffectType.Hit_Tree_Shudder);
                        }
                     }

                     if (var11 == nullptr && dynamic_cast<IsoWindow*>(var10) != nullptr) {
                        var11 = this.testCollisionWithObject(var10, 1.0F, var3);
                     }

                     if (var11 == nullptr
                        && var10.sprite != nullptr
                        && (var10.sprite.getProperties().Is("HitByCar") || var10.sprite.getProperties().Is("CarSlowFactor"))) {
                        var11 = this.testCollisionWithObject(var10, 1.0F, var3);
                     }

                     if (var11 == nullptr) {
    IsoGridSquare var12 = this.getCell().getGridSquare(this.x + var7, this.y + var6, 1.0);
                        if (var12 != nullptr && var12.getHasTypes().isSet(IsoObjectType.lightswitch)) {
                           var11 = this.testCollisionWithObject(var10, 1.0F, var3);
                        }
                     }

                     if (var11 == nullptr) {
    IsoGridSquare var13 = this.getCell().getGridSquare(this.x + var7, this.y + var6, 0.0);
                        if (var13 != nullptr && var13.getHasTypes().isSet(IsoObjectType.lightswitch)) {
                           var11 = this.testCollisionWithObject(var10, 1.0F, var3);
                        }
                     }

                     if (var11 != nullptr) {
                        var10.Hit(var11, this, var1);
                     }
                  }
               }
            }
         }

         TL_vector2_pool.get().release(var3);
      }
   }

    void update() {
      if (this.removedFromWorld) {
         DebugLog.Vehicle.debugln("vehicle update() removedFromWorld=true id=%d", this.VehicleID);
      } else if (!this.getCell().vehicles.contains(this)) {
         DebugLog.Vehicle.debugln("vehicle update() not in cell.vehicles list id=%d x=%f y=%f %s", this.VehicleID, this.x, this.y, this);
         this.getCell().getRemoveList().push_back(this);
      } else {
         if (this.chunk == nullptr) {
            DebugLog.Vehicle.debugln("vehicle update() chunk=nullptr id=%d x=%f y=%f", this.VehicleID, this.x, this.y);
         } else if (!this.chunk.vehicles.contains(this)) {
            DebugLog.Vehicle.debugln("vehicle update() not in chunk.vehicles list id=%d x=%f y=%f", this.VehicleID, this.x, this.y);
            if (GameClient.bClient) {
               VehicleManager.instance.sendRequestGetPosition(this.VehicleID, PacketType.VehiclesUnreliable);
            }
         } else if (!GameServer.bServer && this.chunk.refs.empty()) {
            DebugLog.Vehicle.debugln("vehicle update() chunk was unloaded id=%d", this.VehicleID);
            this.removeFromWorld();
            return;
         }

         super.update();
         if (GameClient.bClient || GameServer.bServer) {
            this.isReliable = this.physicReliableLimit.Check();
         }

         if (GameClient.bClient && this.hasAuthorization(GameClient.connection)) {
            this.updatePhysicsNetwork();
         }

         if (this.getVehicleTowing() != nullptr && this.getDriver() != nullptr) {
    float var1 = 2.5F;
            if (this.getVehicleTowing().getPartCount() == 0) {
               var1 = 12.0F;
            }

            if (this.getVehicleTowing().scriptName == "Base.Trailer")) {
    VehiclePart var2 = this.getVehicleTowing().getPartById("TrailerTrunk");
               if (this.getCurrentSpeedKmHour() > 30.0F && var2.getCondition() < 50 && !var2.container.Items.empty()) {
    std::vector var3 = new std::vector();

                  for (int var4 = 0; var4 < var2.container.Items.size(); var4++) {
                     if (((InventoryItem)var2.container.Items.get(var4)).getWeight() >= 3.5) {
                        var3.push_back((InventoryItem)var2.container.Items.get(var4));
                     }
                  }

                  if (!var3.empty()) {
    int var28 = var2.getCondition();
    int var5 = 0;
    int var6 = 0;

                     for (int var7 = 0; var7 < this.getVehicleTowing().parts.size(); var7++) {
    VehiclePart var8 = this.getVehicleTowing().getPartByIndex(var7);
                        if (var8 != nullptr && var8.item != nullptr) {
                           if (var8.partId != nullptr && var8.partId.contains("Suspension")) {
                              var5 += var8.getCondition();
                           } else if (var8.partId != nullptr && var8.partId.contains("Tire")) {
                              var6 += var8.getCondition();
                           }
                        }
                     }

    float var37 = this.parameterVehicleSteer.getCurrentValue();
                     int var41 = (int)(
                        Math.pow(100 - var28 * 2, 2.0) * 0.3 * (1.0 + (100 - var5 / 2) * 0.005) * (1.0 + (100 - var5 / 2) * 0.005) * (1.0F + var37 / 3.0F)
                     );
                     if (Rand.Next(0, Math.max(10000 - var41, 1)) == 0) {
    InventoryItem var9 = (InventoryItem)var3.get(Rand.Next(0, var3.size()));
                        var9.setCondition(var9.getCondition() - var9.getConditionMax() / 10);
                        var2.getSquare().AddWorldInventoryItem(var9, Rand.Next(0.0F, 0.5F), Rand.Next(0.0F, 0.5F), 0.0F);
                        var2.container.Items.remove(var9);
                        var2.getSquare().playSound("thumpa2");
                     }
                  }
               }
            }
         }

         if (this.getVehicleTowedBy() != nullptr && this.getDriver() != nullptr) {
    float var19 = 2.5F;
            if (this.getVehicleTowedBy().getPartCount() == 0) {
               var19 = 12.0F;
            }
         }

         if (this.physics != nullptr && this.vehicleTowingID != -1 && this.vehicleTowing == nullptr) {
            this.tryReconnectToTowedVehicle();
         }

    bool var21 = false;
    bool var22 = false;
         if (this.getVehicleTowedBy() != nullptr && this.getVehicleTowedBy().getController() != nullptr) {
            var21 = this.getVehicleTowedBy() != nullptr && this.getVehicleTowedBy().getController().isEnable;
            var22 = this.getVehicleTowing() != nullptr && this.getVehicleTowing().getDriver() != nullptr;
         }

         if (this.physics != nullptr) {
    bool var23 = this.getDriver() != nullptr || var21 || var22;
    long var29 = System.currentTimeMillis();
            if (this.constraintChangedTime != -1L) {
               if (this.constraintChangedTime + 3500L < var29) {
                  this.constraintChangedTime = -1L;
                  if (!var23 && this.physicActiveCheck < var29) {
                     this.setPhysicsActive(false);
                  }
               }
            } else {
               if (this.physicActiveCheck != -1L && (var23 || !this.physics.isEnable)) {
                  this.physicActiveCheck = -1L;
               }

               if (!var23 && this.physics.isEnable && this.physicActiveCheck != -1L && this.physicActiveCheck < var29) {
                  this.physicActiveCheck = -1L;
                  this.setPhysicsActive(false);
               }
            }

            if (this.getVehicleTowedBy() != nullptr && this.getScript().getWheelCount() > 0) {
               this.physics.updateTrailer();
            } else if (this.getDriver() == nullptr && !GameServer.bServer) {
               this.physics.checkShouldBeActive();
            }

            this.doAlarm();
    VehicleImpulse var35 = this.impulseFromServer;
            if (!GameServer.bServer && var35 != nullptr && var35.enable) {
               var35.enable = false;
    float var38 = 1.0F;
               Bullet.applyCentralForceToVehicle(this.VehicleID, var35.impulse.x * var38, var35.impulse.y * var38, var35.impulse.z * var38);
    Vector3f var42 = var35.rel_pos.cross(var35.impulse, (Vector3f)TL_vector3f_pool.get().alloc());
               Bullet.applyTorqueToVehicle(this.VehicleID, var42.x * var38, var42.y * var38, var42.z * var38);
               TL_vector3f_pool.get().release(var42);
            }

            this.applyImpulseFromHitZombies();
            this.applyImpulseFromProneCharacters();
    short var39 = 1000;
            if (System.currentTimeMillis() - this.engineCheckTime > var39 && !GameClient.bClient) {
               this.engineCheckTime = System.currentTimeMillis();
               if (!GameClient.bClient) {
                  if (this.engineState != engineStateTypes.Idle) {
    int var43 = (int)(this.engineLoudness * this.engineSpeed / 2500.0);
    double var47 = Math.min(this.getEngineSpeed(), 2000.0);
                     var43 = (int)(var43 * (1.0 + var47 / 4000.0));
    int var11 = 120;
                     if (GameServer.bServer) {
                        var11 = (int)(var11 * ServerOptions.getInstance().CarEngineAttractionModifier.getValue());
                        var43 = (int)(var43 * ServerOptions.getInstance().CarEngineAttractionModifier.getValue());
                     }

                     if (Rand.Next((int)(var11 * GameTime.instance.getInvMultiplier())) == 0) {
                        WorldSoundManager.instance
                           .addSoundRepeating(this, (int)this.getX(), (int)this.getY(), (int)this.getZ(), Math.max(8, var43), var43 / 40, false);
                     }

                     if (Rand.Next((int)((var11 - 85) * GameTime.instance.getInvMultiplier())) == 0) {
                        WorldSoundManager.instance
                           .addSoundRepeating(this, (int)this.getX(), (int)this.getY(), (int)this.getZ(), Math.max(8, var43 / 2), var43 / 40, false);
                     }

                     if (Rand.Next((int)((var11 - 110) * GameTime.instance.getInvMultiplier())) == 0) {
                        WorldSoundManager.instance
                           .addSoundRepeating(this, (int)this.getX(), (int)this.getY(), (int)this.getZ(), Math.max(8, var43 / 4), var43 / 40, false);
                     }

                     WorldSoundManager.instance
                        .addSoundRepeating(this, (int)this.getX(), (int)this.getY(), (int)this.getZ(), Math.max(8, var43 / 6), var43 / 40, false);
                  }

                  if (this.lightbarSirenMode.isEnable() && this.getBatteryCharge() > 0.0F) {
                     WorldSoundManager.instance.addSoundRepeating(this, (int)this.getX(), (int)this.getY(), (int)this.getZ(), 100, 60, false);
                  }
               }

               if (this.engineState == engineStateTypes.Running && !this.isEngineWorking()) {
                  this.shutOff();
               }

               if (this.engineState == engineStateTypes.Running) {
    VehiclePart var45 = this.getPartById("Engine");
                  if (var45 != nullptr && var45.getCondition() < 50 && Rand.Next(Rand.AdjustForFramerate(var45.getCondition() * 12)) == 0) {
                     this.shutOff();
                  }
               }

               if (this.engineState == engineStateTypes.Starting) {
                  this.updateEngineStarting();
               }

               if (this.engineState == engineStateTypes.RetryingStarting && System.currentTimeMillis() - this.engineLastUpdateStateTime > 10L) {
                  this.engineDoStarting();
               }

               if (this.engineState == engineStateTypes.StartingSuccess && System.currentTimeMillis() - this.engineLastUpdateStateTime > 500L) {
                  this.engineDoRunning();
               }

               if (this.engineState == engineStateTypes.StartingFailed && System.currentTimeMillis() - this.engineLastUpdateStateTime > 500L) {
                  this.engineDoIdle();
               }

               if (this.engineState == engineStateTypes.StartingFailedNoPower && System.currentTimeMillis() - this.engineLastUpdateStateTime > 500L) {
                  this.engineDoIdle();
               }

               if (this.engineState == engineStateTypes.Stalling && System.currentTimeMillis() - this.engineLastUpdateStateTime > 3000L) {
                  this.engineDoIdle();
               }

               if (this.engineState == engineStateTypes.ShutingDown && System.currentTimeMillis() - this.engineLastUpdateStateTime > 2000L) {
                  this.engineDoIdle();
               }
            }

            if (this.getDriver() == nullptr && !var21) {
               this.getController().park();
            }

            this.setX(this.jniTransform.origin.x + WorldSimulation.instance.offsetX);
            this.setY(this.jniTransform.origin.z + WorldSimulation.instance.offsetY);
            this.setZ(0.0F);
    IsoGridSquare var46 = this.getCell().getGridSquare(this.x, this.y, this.z);
            if (var46 == nullptr && !this.chunk.refs.empty()) {
    float var48 = 5.0E-4F;
    int var10 = this.chunk.wx * 10;
    int var52 = this.chunk.wy * 10;
    int var12 = var10 + 10;
    int var13 = var52 + 10;
    float var14 = this.x;
    float var15 = this.y;
               this.x = Math.max(this.x, var10 + var48);
               this.x = Math.min(this.x, var12 - var48);
               this.y = Math.max(this.y, var52 + var48);
               this.y = Math.min(this.y, var13 - var48);
               this.z = 0.2F;
    Transform var16 = this.tempTransform;
    Transform var17 = this.tempTransform2;
               this.getWorldTransform(var16);
               var17.basis.set(var16.basis);
               var17.origin.set(this.x - WorldSimulation.instance.offsetX, this.z, this.y - WorldSimulation.instance.offsetY);
               this.setWorldTransform(var17);
               this.current = this.getCell().getGridSquare(this.x, this.y, this.z);
               DebugLog.Vehicle.debugln("Vehicle vid=%d is moved into an unloaded area (%f;%f)", this.VehicleID, this.x, this.y);
            }

            if (this.current != nullptr && this.current.chunk != nullptr) {
               if (this.current.getChunk() != this.chunk) {
                  assert this.chunk.vehicles.contains(this);

                  this.chunk.vehicles.remove(this);
                  this.chunk = this.current.getChunk();
                  if (!GameServer.bServer && this.chunk.refs.empty()) {
                     DebugLog.Vehicle.debugln("BaseVehicle.update() added to unloaded chunk id=%d", this.VehicleID);
                  }

                  assert !this.chunk.vehicles.contains(this);

                  this.chunk.vehicles.push_back(this);
                  IsoChunk.addFromCheckedVehicles(this);
               }
            } else {
    bool var49 = false;
            }

            this.updateTransform();
    Vector3f var50 = allocVector3f().set(this.jniLinearVelocity);
            if (this.jniIsCollide && this.limitCrash.Check()) {
               this.jniIsCollide = false;
               this.limitCrash.Reset();
    Vector3f var51 = allocVector3f();
               var51.set(var50).sub(this.lastLinearVelocity);
               var51.y = 0.0F;
    float var53 = var51.length();
               DebugLog.Vehicle
                  .debugln(
                     "Vehicle vid=%d velocity last=%s/%f current=%s/%f delta=%f",
                     this.VehicleID,
                     this.lastLinearVelocity,
                     this.lastLinearVelocity.length(),
                     var50,
                     var50.length(),
                     var53
                  );
               if (var50.lengthSquared() > this.lastLinearVelocity.lengthSquared() && var53 > 6.0F) {
                  DebugLog.Vehicle.trace("Vehicle vid=%d got sharp speed increase delta=%f", this.VehicleID, var53);
                  var53 = 6.0F;
               }

               if (var53 > 1.0F) {
                  if (this.lastLinearVelocity.length() < 6.0F) {
                     var53 /= 3.0F;
                  }

                  DebugLog.Vehicle.trace("Vehicle vid=%d crash delta=%f", this.VehicleID, var53);
    Vector3f var54 = this.getForwardVector(allocVector3f());
    float var55 = var51.dot(var54);
                  releaseVector3f(var54);
                  this.crash(var53 * 3.0F, var55 < 0.0F);
                  this.damageObjects(var53 * 30.0F);
               }

               releaseVector3f(var51);
            }

            this.lastLinearVelocity.set(var50);
            releaseVector3f(var50);
         }

         if (this.soundHornOn && this.hornemitter != nullptr) {
            this.hornemitter.setPos(this.getX(), this.getY(), this.getZ());
         }

         for (int var24 = 0; var24 < this.impulseFromSquishedZombie.length; var24++) {
    VehicleImpulse var30 = this.impulseFromSquishedZombie[var24];
            if (var30 != nullptr) {
               var30.enable = false;
            }
         }

         this.updateSounds();
         this.brekingObjects();
         if (this.bAddThumpWorldSound) {
            this.bAddThumpWorldSound = false;
            WorldSoundManager.instance.addSound(this, (int)this.x, (int)this.y, (int)this.z, 20, 20, true);
         }

         if (this.script.getLightbar().enable && this.lightbarLightsMode.isEnable() && this.getBatteryCharge() > 0.0F) {
            this.lightbarLightsMode.update();
         }

         this.updateWorldLights();

         for (int var25 = 0; var25 < IsoPlayer.numPlayers; var25++) {
            if (this.current == nullptr || !this.current.lighting[var25].bCanSee()) {
               this.setTargetAlpha(var25, 0.0F);
            }

    IsoPlayer var31 = IsoPlayer.players[var25];
            if (var31 != nullptr && this.DistToSquared(var31) < 225.0F) {
               this.setTargetAlpha(var25, 1.0F);
            }
         }

         for (int var26 = 0; var26 < this.getScript().getPassengerCount(); var26++) {
            if (this.getCharacter(var26) != nullptr) {
    Vector3f var32 = this.getPassengerWorldPos(var26, (Vector3f)TL_vector3f_pool.get().alloc());
               this.getCharacter(var26).setX(var32.x);
               this.getCharacter(var26).setY(var32.y);
               this.getCharacter(var26).setZ(var32.z * 1.0F);
               TL_vector3f_pool.get().release(var32);
            }
         }

    VehiclePart var27 = this.getPartById("lightbar");
         if (var27 != nullptr && this.lightbarLightsMode.isEnable() && var27.getCondition() == 0 && !GameClient.bClient) {
            this.setLightbarLightsMode(0);
         }

         if (var27 != nullptr && this.lightbarSirenMode.isEnable() && var27.getCondition() == 0 && !GameClient.bClient) {
            this.setLightbarSirenMode(0);
         }

         if (!this.needPartsUpdate() && !this.isMechanicUIOpen()) {
            this.drainBatteryUpdateHack();
         } else {
            this.updateParts();
         }

         if (this.engineState == engineStateTypes.Running || var21) {
            this.updateBulletStats();
         }

         if (this.bDoDamageOverlay) {
            this.bDoDamageOverlay = false;
            this.doDamageOverlay();
         }

         if (GameClient.bClient) {
            this.checkPhysicsValidWithServer();
         }

    VehiclePart var33 = this.getPartById("GasTank");
         if (var33 != nullptr && var33.getContainerContentAmount() > var33.getContainerCapacity()) {
            var33.setContainerContentAmount(var33.getContainerCapacity());
         }

    bool var34 = false;

         for (int var36 = 0; var36 < this.getMaxPassengers(); var36++) {
    Passenger var40 = this.getPassenger(var36);
            if (var40.character != nullptr) {
               var34 = true;
               break;
            }
         }

         if (var34) {
            this.m_surroundVehicle.update();
         }

         if (!GameServer.bServer) {
            if (this.physics != nullptr) {
               Bullet.setVehicleMass(this.VehicleID, this.getFudgedMass());
            }

            this.updateVelocityMultiplier();
         }
      }
   }

    void updateEngineStarting() {
      if (this.getBatteryCharge() <= 0.1F) {
         this.engineDoStartingFailedNoPower();
      } else {
    VehiclePart var1 = this.getPartById("GasTank");
         if (var1 != nullptr && var1.getContainerContentAmount() <= 0.0F) {
            this.engineDoStartingFailed();
         } else {
    int var2 = 0;
    float var3 = ClimateManager.getInstance().getAirTemperatureForSquare(this.getSquare());
            if (this.engineQuality < 65 && var3 <= 2.0F) {
               var2 = Math.min((2 - (int)var3) * 2, 30);
            }

            if (!SandboxOptions.instance.VehicleEasyUse.getValue() && this.engineQuality < 100 && Rand.Next(this.engineQuality + 50 - var2) <= 30) {
               this.engineDoStartingFailed();
            } else {
               if (Rand.Next(this.engineQuality) != 0) {
                  this.engineDoStartingSuccess();
               } else {
                  this.engineDoRetryingStarting();
               }
            }
         }
      }
   }

    void applyImpulseFromHitZombies() {
      if (!this.impulseFromHitZombie.empty()) {
         if ((!GameClient.bClient || this.hasAuthorization(GameClient.connection)) && !GameServer.bServer) {
    Vector3f var7 = ((Vector3f)TL_vector3f_pool.get().alloc()).set(0.0F, 0.0F, 0.0F);
    Vector3f var8 = ((Vector3f)TL_vector3f_pool.get().alloc()).set(0.0F, 0.0F, 0.0F);
    Vector3f var9 = ((Vector3f)TL_vector3f_pool.get().alloc()).set(0.0F, 0.0F, 0.0F);
    int var4 = this.impulseFromHitZombie.size();

            for (int var5 = 0; var5 < var4; var5++) {
    VehicleImpulse var6 = this.impulseFromHitZombie.get(var5);
               var7.push_back(var6.impulse);
               var8.push_back(var6.rel_pos.cross(var6.impulse, var9));
               var6.release();
               var6.enable = false;
            }

            this.impulseFromHitZombie.clear();
    float var10 = 7.0F * this.getFudgedMass();
            if (var7.lengthSquared() > var10 * var10) {
               var7.mul(var10 / var7.length());
            }

    float var11 = 30.0F;
            Bullet.applyCentralForceToVehicle(this.VehicleID, var7.x * var11, var7.y * var11, var7.z * var11);
            Bullet.applyTorqueToVehicle(this.VehicleID, var8.x * var11, var8.y * var11, var8.z * var11);
            if (GameServer.bServer) {
            }

            TL_vector3f_pool.get().release(var7);
            TL_vector3f_pool.get().release(var8);
            TL_vector3f_pool.get().release(var9);
         } else {
    int var1 = 0;

            for (int var2 = this.impulseFromHitZombie.size(); var1 < var2; var1++) {
    VehicleImpulse var3 = this.impulseFromHitZombie.get(var1);
               var3.release();
               var3.enable = false;
            }

            this.impulseFromHitZombie.clear();
         }
      }
   }

    void applyImpulseFromProneCharacters() {
      if ((!GameClient.bClient || this.hasAuthorization(GameClient.connection)) && !GameServer.bServer) {
    bool var1 = PZArrayUtil.contains(this.impulseFromSquishedZombie, var0 -> var0 != nullptr && var0.enable);
         if (var1) {
    Vector3f var2 = ((Vector3f)TL_vector3f_pool.get().alloc()).set(0.0F, 0.0F, 0.0F);
    Vector3f var3 = ((Vector3f)TL_vector3f_pool.get().alloc()).set(0.0F, 0.0F, 0.0F);
    Vector3f var4 = (Vector3f)TL_vector3f_pool.get().alloc();

            for (int var5 = 0; var5 < this.impulseFromSquishedZombie.length; var5++) {
    VehicleImpulse var6 = this.impulseFromSquishedZombie[var5];
               if (var6 != nullptr && var6.enable) {
                  var2.push_back(var6.impulse);
                  var3.push_back(var6.rel_pos.cross(var6.impulse, var4));
                  var6.enable = false;
               }
            }

            if (var2.lengthSquared() > 0.0F) {
    float var7 = this.getFudgedMass() * 0.15F;
               if (var2.lengthSquared() > var7 * var7) {
                  var2.mul(var7 / var2.length());
               }

    float var8 = 30.0F;
               Bullet.applyCentralForceToVehicle(this.VehicleID, var2.x * var8, var2.y * var8, var2.z * var8);
               Bullet.applyTorqueToVehicle(this.VehicleID, var3.x * var8, var3.y * var8, var3.z * var8);
            }

            TL_vector3f_pool.get().release(var2);
            TL_vector3f_pool.get().release(var3);
            TL_vector3f_pool.get().release(var4);
         }
      }
   }

    float getFudgedMass() {
      if (this.getScriptName().contains("Trailer")) {
         return this.getMass();
      } else {
    BaseVehicle var1 = this.getVehicleTowedBy();
         if (var1 != nullptr && var1.getDriver() != nullptr && var1.isEngineRunning()) {
    float var2 = Math.max(250.0F, var1.getMass() / 3.7F);
            if (this.getScript().getWheelCount() == 0) {
               var2 = Math.min(var2, 200.0F);
            }

    return var2;
         } else {
            return this.getMass();
         }
      }
   }

    bool isNullChunk(int var1, int var2) {
      if (!IsoWorld.instance.getMetaGrid().isValidChunk(var1, var2)) {
    return false;
      } else if (GameClient.bClient && !ClientServerMap.isChunkLoaded(var1, var2)) {
    return true;
      } else {
         return GameClient.bClient && !PassengerMap.isChunkLoaded(this, var1, var2) ? true : this.getCell().getChunk(var1, var2) == nullptr;
      }
   }

    bool isInvalidChunkAround() {
    Vector3f var1 = this.getLinearVelocity((Vector3f)TL_vector3f_pool.get().alloc());
    float var2 = Math.abs(var1.x);
    float var3 = Math.abs(var1.z);
    bool var4 = var1.x < 0.0F && var2 > var3;
    bool var5 = var1.x > 0.0F && var2 > var3;
    bool var6 = var1.z < 0.0F && var3 > var2;
    bool var7 = var1.z > 0.0F && var3 > var2;
      TL_vector3f_pool.get().release(var1);
      return this.isInvalidChunkAround(var4, var5, var6, var7);
   }

    bool isInvalidChunkAhead() {
    Vector3f var1 = this.getForwardVector((Vector3f)TL_vector3f_pool.get().alloc());
    bool var2 = var1.x < -0.5F;
    bool var3 = var1.z > 0.5F;
    bool var4 = var1.x > 0.5F;
    bool var5 = var1.z < -0.5F;
      return this.isInvalidChunkAround(var2, var4, var5, var3);
   }

    bool isInvalidChunkBehind() {
    Vector3f var1 = this.getForwardVector((Vector3f)TL_vector3f_pool.get().alloc());
    bool var2 = var1.x < -0.5F;
    bool var3 = var1.z > 0.5F;
    bool var4 = var1.x > 0.5F;
    bool var5 = var1.z < -0.5F;
      return this.isInvalidChunkAround(var4, var2, var3, var5);
   }

    bool isInvalidChunkAround(bool var1, bool var2, bool var3, bool var4) {
      if (IsoChunkMap.ChunkGridWidth > 7) {
         if (var2 && (this.isNullChunk(this.chunk.wx + 1, this.chunk.wy) || this.isNullChunk(this.chunk.wx + 2, this.chunk.wy))) {
    return true;
         }

         if (var1 && (this.isNullChunk(this.chunk.wx - 1, this.chunk.wy) || this.isNullChunk(this.chunk.wx - 2, this.chunk.wy))) {
    return true;
         }

         if (var4 && (this.isNullChunk(this.chunk.wx, this.chunk.wy + 1) || this.isNullChunk(this.chunk.wx, this.chunk.wy + 2))) {
    return true;
         }

         if (var3 && (this.isNullChunk(this.chunk.wx, this.chunk.wy - 1) || this.isNullChunk(this.chunk.wx, this.chunk.wy - 2))) {
    return true;
         }
      } else {
         if (IsoChunkMap.ChunkGridWidth <= 4) {
    return false;
         }

         if (var2 && this.isNullChunk(this.chunk.wx + 1, this.chunk.wy)) {
    return true;
         }

         if (var1 && this.isNullChunk(this.chunk.wx - 1, this.chunk.wy)) {
    return true;
         }

         if (var4 && this.isNullChunk(this.chunk.wx, this.chunk.wy + 1)) {
    return true;
         }

         if (var3 && this.isNullChunk(this.chunk.wx, this.chunk.wy - 1)) {
    return true;
         }
      }

    return false;
   }

    void postupdate() {
      this.current = this.getCell().getGridSquare((int)this.x, (int)this.y, 0);
      if (this.current == nullptr) {
         for (int var1 = (int)this.z; var1 >= 0; var1--) {
            this.current = this.getCell().getGridSquare((int)this.x, (int)this.y, var1);
            if (this.current != nullptr) {
               break;
            }
         }
      }

      if (this.movingSq != nullptr) {
         this.movingSq.getMovingObjects().remove(this);
         this.movingSq = nullptr;
      }

      if (this.current != nullptr && !this.current.getMovingObjects().contains(this)) {
         this.current.getMovingObjects().push_back(this);
         this.movingSq = this.current;
      }

      this.square = this.current;
      if (this.sprite.hasActiveModel()) {
         this.updateAnimationPlayer(this.getAnimationPlayer(), nullptr);

         for (int var3 = 0; var3 < this.models.size(); var3++) {
    ModelInfo var2 = this.models.get(var3);
            this.updateAnimationPlayer(var2.getAnimationPlayer(), var2.part);
         }
      }
   }

    void updateAnimationPlayer(AnimationPlayer var1, VehiclePart var2) {
      if (var1 != nullptr && var1.isReady()) {
    AnimationMultiTrack var3 = var1.getMultiTrack();
    float var4 = 0.016666668F;
         var4 *= 0.8F;
         var4 *= GameTime.instance.getUnmoddedMultiplier();
         var1.Update(var4);

         for (int var5 = 0; var5 < var3.getTrackCount(); var5++) {
    AnimationTrack var6 = (AnimationTrack)var3.getTracks().get(var5);
            if (var6.IsPlaying && var6.isFinished()) {
               var3.removeTrackAt(var5);
               var5--;
            }
         }

         if (var2 != nullptr) {
    ModelInfo var10 = this.getModelInfoForPart(var2);
            if (var10.m_track != nullptr && var3.getIndexOfTrack(var10.m_track) == -1) {
               var10.m_track = nullptr;
            }

            if (var10.m_track != nullptr) {
    VehicleWindow var12 = var2.getWindow();
               if (var12 != nullptr) {
    AnimationTrack var13 = var10.m_track;
                  var13.setCurrentTimeValue(var13.getDuration() * var12.getOpenDelta());
               }
            } else {
    VehicleDoor var11 = var2.getDoor();
               if (var11 != nullptr) {
                  this.playPartAnim(var2, var11.isOpen() ? "Opened" : "Closed");
               }

    VehicleWindow var7 = var2.getWindow();
               if (var7 != nullptr) {
                  this.playPartAnim(var2, "ClosedToOpen");
               }
            }
         }
      }
   }

    void saveChange(const std::string& var1, KahluaTable var2, ByteBuffer var3) {
      super.saveChange(var1, var2, var3);
   }

    void loadChange(const std::string& var1, ByteBuffer var2) {
      super.loadChange(var1, var2);
   }

    void authorizationClientCollide(IsoPlayer var1) {
      if (var1 != nullptr && this.getDriver() == nullptr) {
         this.setNetPlayerAuthorization(Authorization.LocalCollide, var1.getOnlineID());
         this.authSimulationTime = System.currentTimeMillis();
         this.interpolation.clear();
         if (this.getVehicleTowing() != nullptr) {
            this.getVehicleTowing().setNetPlayerAuthorization(Authorization.LocalCollide, var1.getOnlineID());
            this.getVehicleTowing().authSimulationTime = System.currentTimeMillis();
            this.getVehicleTowing().interpolation.clear();
         } else if (this.getVehicleTowedBy() != nullptr) {
            this.getVehicleTowedBy().setNetPlayerAuthorization(Authorization.LocalCollide, var1.getOnlineID());
            this.getVehicleTowedBy().authSimulationTime = System.currentTimeMillis();
            this.getVehicleTowedBy().interpolation.clear();
         }
      }
   }

    void authorizationServerCollide(short var1, bool var2) {
      if (!this.isNetPlayerAuthorization(Authorization.Local)) {
         if (var2) {
            this.setNetPlayerAuthorization(Authorization.LocalCollide, var1);
            if (this.getVehicleTowing() != nullptr) {
               this.getVehicleTowing().setNetPlayerAuthorization(Authorization.LocalCollide, var1);
            } else if (this.getVehicleTowedBy() != nullptr) {
               this.getVehicleTowedBy().setNetPlayerAuthorization(Authorization.LocalCollide, var1);
            }
         } else {
    Authorization var3 = var1 == -1 ? Authorization.Server : Authorization.Local;
            this.setNetPlayerAuthorization(var3, var1);
            if (this.getVehicleTowing() != nullptr) {
               this.getVehicleTowing().setNetPlayerAuthorization(var3, var1);
            } else if (this.getVehicleTowedBy() != nullptr) {
               this.getVehicleTowedBy().setNetPlayerAuthorization(var3, var1);
            }
         }
      }
   }

    void authorizationServerOnSeat(IsoPlayer var1, bool var2) {
    BaseVehicle var3 = this.getVehicleTowing();
    BaseVehicle var4 = this.getVehicleTowedBy();
      if (this.isNetPlayerId((short)-1) && var2) {
         if (var3 != nullptr && var3.getDriver() == nullptr) {
            this.addPointConstraint(nullptr, var3, this.getTowAttachmentSelf(), var3.getTowAttachmentSelf());
         } else if (var4 != nullptr && var4.getDriver() == nullptr) {
            this.addPointConstraint(nullptr, var4, this.getTowAttachmentSelf(), var4.getTowAttachmentSelf());
         } else {
            this.setNetPlayerAuthorization(Authorization.Local, var1.getOnlineID());
         }
      } else if (this.isNetPlayerId(var1.getOnlineID()) && !var2) {
         if (var3 != nullptr && var3.getDriver() != nullptr) {
            var3.addPointConstraint(nullptr, this, var3.getTowAttachmentSelf(), this.getTowAttachmentSelf());
         } else if (var4 != nullptr && var4.getDriver() != nullptr) {
            var4.addPointConstraint(nullptr, this, var4.getTowAttachmentSelf(), this.getTowAttachmentSelf());
         } else {
            this.setNetPlayerAuthorization(Authorization.Server, -1);
            if (var3 != nullptr) {
               var3.setNetPlayerAuthorization(Authorization.Server, -1);
            } else if (var4 != nullptr) {
               var4.setNetPlayerAuthorization(Authorization.Server, -1);
            }
         }
      }
   }

    bool hasAuthorization(UdpConnection var1) {
      if (!this.isNetPlayerId((short)-1) && var1 != nullptr) {
         if (GameServer.bServer) {
            for (int var2 = 0; var2 < var1.players.length; var2++) {
               if (var1.players[var2] != nullptr && this.isNetPlayerId(var1.players[var2].OnlineID)) {
    return true;
               }
            }

    return false;
         } else {
            return this.isNetPlayerId(IsoPlayer.getInstance().getOnlineID());
         }
      } else {
    return false;
      }
   }

    void netPlayerServerSendAuthorisation(ByteBuffer var1) {
      var1.put(this.netPlayerAuthorization.index());
      var1.putShort(this.netPlayerId);
   }

    void netPlayerFromServerUpdate(Authorization var1, short var2) {
      if (!this.isNetPlayerAuthorization(var1) || !this.isNetPlayerId(var2)) {
         if (Authorization.Local == var1)) {
            if (IsoPlayer.getLocalPlayerByOnlineID(var2) != nullptr) {
               this.setNetPlayerAuthorization(Authorization.Local, var2);
            } else {
               this.setNetPlayerAuthorization(Authorization.Remote, var2);
            }
         } else if (Authorization.LocalCollide == var1)) {
            if (IsoPlayer.getLocalPlayerByOnlineID(var2) != nullptr) {
               this.setNetPlayerAuthorization(Authorization.LocalCollide, var2);
            } else {
               this.setNetPlayerAuthorization(Authorization.RemoteCollide, var2);
            }
         } else {
            this.setNetPlayerAuthorization(Authorization.Server, -1);
         }
      }
   }

    Transform getWorldTransform(Transform var1) {
      var1.set(this.jniTransform);
    return var1;
   }

    void setWorldTransform(Transform var1) {
      this.jniTransform.set(var1);
    Quaternionf var2 = this.tempQuat4f;
      var1.getRotation(var2);
      if (!GameServer.bServer) {
         Bullet.teleportVehicle(
            this.VehicleID,
            var1.origin.x + WorldSimulation.instance.offsetX,
            var1.origin.z + WorldSimulation.instance.offsetY,
            var1.origin.y,
            var2.x,
            var2.y,
            var2.z,
            var2.w
         );
      }
   }

    void flipUpright() {
    Transform var1 = this.tempTransform;
      var1.set(this.jniTransform);
    Quaternionf var2 = this.tempQuat4f;
      var2.setAngleAxis(0.0F, _UNIT_Y.x, _UNIT_Y.y, _UNIT_Y.z);
      var1.setRotation(var2);
      this.setWorldTransform(var1);
   }

    void setAngles(float var1, float var2, float var3) {
      if ((int)var1 != (int)this.getAngleX() || (int)var2 != (int)this.getAngleY() || var3 != (int)this.getAngleZ()) {
         this.polyDirty = true;
    float var4 = var1 * (float) (Math.PI / 180.0);
    float var5 = var2 * (float) (Math.PI / 180.0);
    float var6 = var3 * (float) (Math.PI / 180.0);
         this.tempQuat4f.rotationXYZ(var4, var5, var6);
         this.tempTransform.set(this.jniTransform);
         this.tempTransform.setRotation(this.tempQuat4f);
         this.setWorldTransform(this.tempTransform);
      }
   }

    float getAngleX() {
    Vector3f var1 = (Vector3f)TL_vector3f_pool.get().alloc();
      this.jniTransform.getRotation(this.tempQuat4f).getEulerAnglesXYZ(var1);
    float var2 = var1.x * (180.0F / (float)Math.PI);
      TL_vector3f_pool.get().release(var1);
    return var2;
   }

    float getAngleY() {
    Vector3f var1 = (Vector3f)TL_vector3f_pool.get().alloc();
      this.jniTransform.getRotation(this.tempQuat4f).getEulerAnglesXYZ(var1);
    float var2 = var1.y * (180.0F / (float)Math.PI);
      TL_vector3f_pool.get().release(var1);
    return var2;
   }

    float getAngleZ() {
    Vector3f var1 = (Vector3f)TL_vector3f_pool.get().alloc();
      this.jniTransform.getRotation(this.tempQuat4f).getEulerAnglesXYZ(var1);
    float var2 = var1.z * (180.0F / (float)Math.PI);
      TL_vector3f_pool.get().release(var1);
    return var2;
   }

    void setDebugZ(float var1) {
      this.tempTransform.set(this.jniTransform);
      this.tempTransform.origin.y = PZMath.clamp(var1, 0.0F, 1.0F) * 3.0F * 0.82F;
      this.setWorldTransform(this.tempTransform);
   }

    void setPhysicsActive(bool var1) {
      if (this.physics != nullptr && var1 != this.physics.isEnable) {
         this.physics.isEnable = var1;
         if (!GameServer.bServer) {
            Bullet.setVehicleActive(this.VehicleID, var1);
         }

         if (var1) {
            this.physicActiveCheck = System.currentTimeMillis() + 3000L;
         }
      }
   }

    float getDebugZ() {
      return this.jniTransform.origin.y / 2.46F;
   }

    VehiclePoly getPoly() {
      if (this.polyDirty) {
         if (this.polyGarageCheck && this.square != nullptr) {
            if (this.square.getRoom() != nullptr && this.square.getRoom().RoomDef != nullptr && this.square.getRoom().RoomDef.contains("garagestorage")) {
               this.radiusReductionInGarage = -0.3F;
            } else {
               this.radiusReductionInGarage = 0.0F;
            }

            this.polyGarageCheck = false;
         }

         this.poly.init(this, 0.0F);
         this.polyPlusRadius.init(this, PLUS_RADIUS + this.radiusReductionInGarage);
         this.polyDirty = false;
         this.polyPlusRadiusMinX = -123.0F;
         this.initShadowPoly();
      }

      return this.poly;
   }

    VehiclePoly getPolyPlusRadius() {
      if (this.polyDirty) {
         if (this.polyGarageCheck && this.square != nullptr) {
            if (this.square.getRoom() != nullptr && this.square.getRoom().RoomDef != nullptr && this.square.getRoom().RoomDef.contains("garagestorage")) {
               this.radiusReductionInGarage = -0.3F;
            } else {
               this.radiusReductionInGarage = 0.0F;
            }

            this.polyGarageCheck = false;
         }

         this.poly.init(this, 0.0F);
         this.polyPlusRadius.init(this, PLUS_RADIUS + this.radiusReductionInGarage);
         this.polyDirty = false;
         this.polyPlusRadiusMinX = -123.0F;
         this.initShadowPoly();
      }

      return this.polyPlusRadius;
   }

    void initShadowPoly() {
      this.getWorldTransform(this.tempTransform);
    Quaternionf var1 = this.tempTransform.getRotation(this.tempQuat4f);
    Vector2f var2 = this.script.getShadowExtents();
    Vector2f var3 = this.script.getShadowOffset();
    float var4 = var2.x / 2.0F;
    float var5 = var2.y / 2.0F;
    Vector3f var6 = (Vector3f)TL_vector3f_pool.get().alloc();
      if (var1.x < 0.0F) {
         this.getWorldPos(var3.x - var4, 0.0F, var3.y + var5, var6);
         this.shadowCoord.x1 = var6.x;
         this.shadowCoord.y1 = var6.y;
         this.getWorldPos(var3.x + var4, 0.0F, var3.y + var5, var6);
         this.shadowCoord.x2 = var6.x;
         this.shadowCoord.y2 = var6.y;
         this.getWorldPos(var3.x + var4, 0.0F, var3.y - var5, var6);
         this.shadowCoord.x3 = var6.x;
         this.shadowCoord.y3 = var6.y;
         this.getWorldPos(var3.x - var4, 0.0F, var3.y - var5, var6);
         this.shadowCoord.x4 = var6.x;
         this.shadowCoord.y4 = var6.y;
      } else {
         this.getWorldPos(var3.x - var4, 0.0F, var3.y + var5, var6);
         this.shadowCoord.x1 = var6.x;
         this.shadowCoord.y1 = var6.y;
         this.getWorldPos(var3.x + var4, 0.0F, var3.y + var5, var6);
         this.shadowCoord.x2 = var6.x;
         this.shadowCoord.y2 = var6.y;
         this.getWorldPos(var3.x + var4, 0.0F, var3.y - var5, var6);
         this.shadowCoord.x3 = var6.x;
         this.shadowCoord.y3 = var6.y;
         this.getWorldPos(var3.x - var4, 0.0F, var3.y - var5, var6);
         this.shadowCoord.x4 = var6.x;
         this.shadowCoord.y4 = var6.y;
      }

      TL_vector3f_pool.get().release(var6);
   }

    void initPolyPlusRadiusBounds() {
      if (this.polyPlusRadiusMinX == -123.0F) {
    VehiclePoly var1 = this.getPolyPlusRadius();
    Vector3f var10 = (Vector3f)TL_vector3f_pool.get().alloc();
    Vector3f var11 = this.getLocalPos(var1.x1, var1.y1, var1.z, var10);
    float var2 = (int)(var11.x * 100.0F) / 100.0F;
    float var3 = (int)(var11.z * 100.0F) / 100.0F;
         var11 = this.getLocalPos(var1.x2, var1.y2, var1.z, var10);
    float var4 = (int)(var11.x * 100.0F) / 100.0F;
    float var5 = (int)(var11.z * 100.0F) / 100.0F;
         var11 = this.getLocalPos(var1.x3, var1.y3, var1.z, var10);
    float var6 = (int)(var11.x * 100.0F) / 100.0F;
    float var7 = (int)(var11.z * 100.0F) / 100.0F;
         var11 = this.getLocalPos(var1.x4, var1.y4, var1.z, var10);
    float var8 = (int)(var11.x * 100.0F) / 100.0F;
    float var9 = (int)(var11.z * 100.0F) / 100.0F;
         this.polyPlusRadiusMinX = Math.min(var2, Math.min(var4, Math.min(var6, var8)));
         this.polyPlusRadiusMaxX = Math.max(var2, Math.max(var4, Math.max(var6, var8)));
         this.polyPlusRadiusMinY = Math.min(var3, Math.min(var5, Math.min(var7, var9)));
         this.polyPlusRadiusMaxY = Math.max(var3, Math.max(var5, Math.max(var7, var9)));
         TL_vector3f_pool.get().release(var10);
      }
   }

    Vector3f getForwardVector(Vector3f var1) {
    uint8_t var2 = 2;
      return this.jniTransform.basis.getColumn(var2, var1);
   }

    Vector3f getUpVector(Vector3f var1) {
    uint8_t var2 = 1;
      return this.jniTransform.basis.getColumn(var2, var1);
   }

    float getUpVectorDot() {
    Vector3f var1 = this.getUpVector((Vector3f)TL_vector3f_pool.get().alloc());
    float var2 = var1.dot(_UNIT_Y);
      TL_vector3f_pool.get().release(var1);
    return var2;
   }

    bool isStopped() {
      return this.jniSpeed > -0.8F && this.jniSpeed < 0.8F && !this.getController().isGasPedalPressed();
   }

    float getCurrentSpeedKmHour() {
      return this.jniSpeed;
   }

    Vector3f getLinearVelocity(Vector3f var1) {
      return var1.set(this.jniLinearVelocity);
   }

    float getSpeed2D() {
    float var1 = this.jniLinearVelocity.x;
    float var2 = this.jniLinearVelocity.z;
      return (float)Math.sqrt(var1 * var1 + var2 * var2);
   }

    bool isAtRest() {
      if (this.physics == nullptr) {
    return true;
      } else {
    float var1 = this.jniLinearVelocity.y;
         return Math.abs(this.physics.EngineForce) < 0.01F && this.getSpeed2D() < 0.02F && Math.abs(var1) < 0.5F;
      }
   }

    void updateTransform() {
      if (this.sprite.modelSlot != nullptr) {
    float var1 = this.getScript().getModelScale();
    float var2 = 1.0F;
         if (this.sprite.modelSlot != nullptr && this.sprite.modelSlot.model.scale != 1.0F) {
            var2 = this.sprite.modelSlot.model.scale;
         }

    Transform var3 = this.getWorldTransform(this.tempTransform);
    Quaternionf var4 = (Quaternionf)TL_quaternionf_pool.get().alloc();
    Quaternionf var5 = (Quaternionf)TL_quaternionf_pool.get().alloc();
    Matrix4f var6 = (Matrix4f)TL_matrix4f_pool.get().alloc();
         var3.getRotation(var4);
         var4.y *= -1.0F;
         var4.z *= -1.0F;
    Matrix4f var7 = var4.get(var6);
    float var8 = 1.0F;
         if (this.sprite.modelSlot.model.m_modelScript != nullptr) {
            var8 = this.sprite.modelSlot.model.m_modelScript.invertX ? -1.0F : 1.0F;
         }

    Vector3f var9 = this.script.getModel().getOffset();
    Vector3f var10 = this.getScript().getModel().getRotate();
         var5.rotationXYZ(var10.x * (float) (Math.PI / 180.0), var10.y * (float) (Math.PI / 180.0), var10.z * (float) (Math.PI / 180.0));
         this.renderTransform
            .translationRotateScale(var9.x * -1.0F, var9.y, var9.z, var5.x, var5.y, var5.z, var5.w, var1 * var2 * var8, var1 * var2, var1 * var2);
         var7.mul(this.renderTransform, this.renderTransform);
         this.vehicleTransform.translationRotateScale(var9.x * -1.0F, var9.y, var9.z, 0.0F, 0.0F, 0.0F, 1.0F, var1);
         var7.mul(this.vehicleTransform, this.vehicleTransform);

         for (int var22 = 0; var22 < this.models.size(); var22++) {
    ModelInfo var23 = this.models.get(var22);
    Model var24 = var23.scriptModel;
            var10 = var24.getOffset();
    Vector3f var11 = var24.getRotate();
    float var12 = var24.scale;
            var2 = 1.0F;
    float var13 = 1.0F;
            if (var23.modelScript != nullptr) {
               var2 = var23.modelScript.scale;
               var13 = var23.modelScript.invertX ? -1.0F : 1.0F;
            }

            var5.rotationXYZ(var11.x * (float) (Math.PI / 180.0), var11.y * (float) (Math.PI / 180.0), var11.z * (float) (Math.PI / 180.0));
            if (var23.wheelIndex == -1) {
               var23.renderTransform
                  .translationRotateScale(var10.x * -1.0F, var10.y, var10.z, var5.x, var5.y, var5.z, var5.w, var12 * var2 * var13, var12 * var2, var12 * var2);
               this.vehicleTransform.mul(var23.renderTransform, var23.renderTransform);
            } else {
    WheelInfo var14 = this.wheelInfo[var23.wheelIndex];
    float var15 = var14.steering;
    float var16 = var14.rotation;
    Wheel var17 = this.getScript().getWheel(var23.wheelIndex);
    VehicleImpulse var18 = var23.wheelIndex < this.impulseFromSquishedZombie.length ? this.impulseFromSquishedZombie[var23.wheelIndex] : nullptr;
    float var19 = var18 != nullptr && var18.enable ? 0.05F : 0.0F;
               if (var14.suspensionLength == 0.0F) {
                  var6.translation(var17.offset.x / var1 * -1.0F, var17.offset.y / var1, var17.offset.z / var1);
               } else {
                  var6.translation(
                     var17.offset.x / var1 * -1.0F,
                     (var17.offset.y + this.script.getSuspensionRestLength() - var14.suspensionLength) / var1 + var19 * 0.5F,
                     var17.offset.z / var1
                  );
               }

               var23.renderTransform.identity();
               var23.renderTransform.mul(var6);
               var23.renderTransform.rotateY(var15 * -1.0F);
               var23.renderTransform.rotateX(var16);
               var6.translationRotateScale(var10.x * -1.0F, var10.y, var10.z, var5.x, var5.y, var5.z, var5.w, var12 * var2 * var13, var12 * var2, var12 * var2);
               var23.renderTransform.mul(var6);
               this.vehicleTransform.mul(var23.renderTransform, var23.renderTransform);
            }
         }

         TL_matrix4f_pool.get().release(var6);
         TL_quaternionf_pool.get().release(var4);
         TL_quaternionf_pool.get().release(var5);
      }
   }

    void updatePhysics() {
      this.physics.update();
   }

    void updatePhysicsNetwork() {
      if (this.limitPhysicSend.Check()) {
         VehicleManager.instance.sendPhysic(this);
         if (this.limitPhysicPositionSent == nullptr) {
            this.limitPhysicPositionSent = std::make_unique<Vector2>();
         } else if (IsoUtils.DistanceToSquared(this.limitPhysicPositionSent.x, this.limitPhysicPositionSent.y, this.x, this.y) > 0.001F) {
            this.limitPhysicSend.setUpdatePeriod(150L);
         } else {
            this.limitPhysicSend.setSmoothUpdatePeriod(300L);
         }

         this.limitPhysicPositionSent.set(this.x, this.y);
      }
   }

    void checkPhysicsValidWithServer() {
    float var1 = 0.05F;
      if (this.limitPhysicValid.Check() && Bullet.getOwnVehiclePhysics(this.VehicleID, physicsParams) == 0) {
    float var2 = Math.abs(physicsParams[0] - this.x);
    float var3 = Math.abs(physicsParams[1] - this.y);
         if (var2 > var1 || var3 > var1) {
            VehicleManager.instance.sendRequestGetPosition(this.VehicleID, PacketType.Vehicles);
            DebugLog.Vehicle.trace("diff-x=%f diff-y=%f delta=%f", var2, var3, var1);
         }
      }
   }

    void updateControls() {
      if (this.getController() != nullptr) {
         if (this.isOperational()) {
    IsoPlayer var1 = (IsoPlayer)Type.tryCastTo(this.getDriver(), IsoPlayer.class);
            if (var1 == nullptr || !var1.isBlockMovement()) {
               this.getController().updateControls();
            }
         }
      }
   }

    bool isKeyboardControlled() {
    IsoGameCharacter var1 = this.getCharacter(0);
      return var1 != nullptr && var1 == IsoPlayer.players[0] && this.getVehicleTowedBy() == nullptr;
   }

    int getJoypad() {
    IsoGameCharacter var1 = this.getCharacter(0);
      return var1 != nullptr && dynamic_cast<IsoPlayer*>(var1) != nullptr ? ((IsoPlayer)var1).JoypadBind : -1;
   }

    void Damage(float var1) {
      this.crash(var1, true);
   }

    void HitByVehicle(BaseVehicle var1, float var2) {
      this.crash(var2, true);
   }

    void crash(float var1, bool var2) {
      if (GameClient.bClient) {
         SoundManager.instance.PlayWorldSound(this.getCrashSound(var1), this.square, 1.0F, 20.0F, 1.0F, true);
         GameClient.instance.sendClientCommandV(nullptr, "vehicle", "crash", new Object[]{"vehicle", this.getId(), "amount", var1, "front", var2});
      } else {
    float var3 = 1.3F;
         switch (SandboxOptions.instance.CarDamageOnImpact.getValue()) {
            case 1:
               var3 = 1.9F;
               break;
            case 2:
               var3 = 1.6F;
            case 3:
            default:
               break;
            case 4:
               var3 = 1.1F;
               break;
            case 5:
               var3 = 0.9F;
         }

         var1 = Math.abs(var1) / var3;
         if (var2) {
            this.addDamageFront((int)var1);
         } else {
            this.addDamageRear((int)Math.abs(var1 / var3));
         }

         this.damagePlayers(Math.abs(var1));
         SoundManager.instance.PlayWorldSound(this.getCrashSound(var1), this.square, 1.0F, 20.0F, 1.0F, true);
      }
   }

    std::string getCrashSound(float var1) {
      if (var1 < 5.0F) {
         return "VehicleCrash1";
      } else {
         return var1 < 30.0F ? "VehicleCrash2" : "VehicleCrash";
      }
   }

    void addDamageFrontHitAChr(int var1) {
      if (var1 >= 4 || !Rand.NextBool(7)) {
    VehiclePart var2 = this.getPartById("EngineDoor");
         if (var2 != nullptr && var2.getInventoryItem() != nullptr) {
            var2.damage(Rand.Next(Math.max(1, var1 - 10), var1 + 3));
         }

         if (var2 != nullptr && (var2.getCondition() <= 0 || var2.getInventoryItem() == nullptr) && Rand.NextBool(4)) {
            var2 = this.getPartById("Engine");
            if (var2 != nullptr) {
               var2.damage(Rand.Next(2, 4));
            }
         }

         if (var1 > 12) {
            var2 = this.getPartById("Windshield");
            if (var2 != nullptr && var2.getInventoryItem() != nullptr) {
               var2.damage(Rand.Next(Math.max(1, var1 - 10), var1 + 3));
            }
         }

         if (Rand.Next(5) < var1) {
            if (Rand.NextBool(2)) {
               var2 = this.getPartById("TireFrontLeft");
            } else {
               var2 = this.getPartById("TireFrontRight");
            }

            if (var2 != nullptr && var2.getInventoryItem() != nullptr) {
               var2.damage(Rand.Next(1, 3));
            }
         }

         if (Rand.Next(7) < var1) {
            this.damageHeadlight("HeadlightLeft", Rand.Next(1, 4));
         }

         if (Rand.Next(7) < var1) {
            this.damageHeadlight("HeadlightRight", Rand.Next(1, 4));
         }

    float var3 = this.getBloodIntensity("Front");
         this.setBloodIntensity("Front", var3 + 0.01F);
      }
   }

    void addDamageRearHitAChr(int var1) {
      if (var1 >= 4 || !Rand.NextBool(7)) {
    VehiclePart var2 = this.getPartById("TruckBed");
         if (var2 != nullptr && var2.getInventoryItem() != nullptr) {
            var2.setCondition(var2.getCondition() - Rand.Next(Math.max(1, var1 - 10), var1 + 3));
            var2.doInventoryItemStats(var2.getInventoryItem(), 0);
            this.transmitPartCondition(var2);
         }

         var2 = this.getPartById("DoorRear");
         if (var2 != nullptr && var2.getInventoryItem() != nullptr) {
            var2.damage(Rand.Next(Math.max(1, var1 - 10), var1 + 3));
         }

         var2 = this.getPartById("TrunkDoor");
         if (var2 != nullptr && var2.getInventoryItem() != nullptr) {
            var2.damage(Rand.Next(Math.max(1, var1 - 10), var1 + 3));
         }

         if (var1 > 12) {
            var2 = this.getPartById("WindshieldRear");
            if (var2 != nullptr && var2.getInventoryItem() != nullptr) {
               var2.damage(var1);
            }
         }

         if (Rand.Next(5) < var1) {
            if (Rand.NextBool(2)) {
               var2 = this.getPartById("TireRearLeft");
            } else {
               var2 = this.getPartById("TireRearRight");
            }

            if (var2 != nullptr && var2.getInventoryItem() != nullptr) {
               var2.damage(Rand.Next(1, 3));
            }
         }

         if (Rand.Next(7) < var1) {
            this.damageHeadlight("HeadlightRearLeft", Rand.Next(1, 4));
         }

         if (Rand.Next(7) < var1) {
            this.damageHeadlight("HeadlightRearRight", Rand.Next(1, 4));
         }

         if (Rand.Next(6) < var1) {
            var2 = this.getPartById("GasTank");
            if (var2 != nullptr && var2.getInventoryItem() != nullptr) {
               var2.damage(Rand.Next(1, 3));
            }
         }

    float var3 = this.getBloodIntensity("Rear");
         this.setBloodIntensity("Rear", var3 + 0.01F);
      }
   }

    void addDamageFront(int var1) {
      this.currentFrontEndDurability -= var1;
    VehiclePart var2 = this.getPartById("EngineDoor");
      if (var2 != nullptr && var2.getInventoryItem() != nullptr) {
         var2.damage(Rand.Next(Math.max(1, var1 - 5), var1 + 5));
      }

      if (var2 == nullptr || var2.getInventoryItem() == nullptr || var2.getCondition() < 25) {
         var2 = this.getPartById("Engine");
         if (var2 != nullptr) {
            var2.damage(Rand.Next(Math.max(1, var1 - 3), var1 + 3));
         }
      }

      var2 = this.getPartById("Windshield");
      if (var2 != nullptr && var2.getInventoryItem() != nullptr) {
         var2.damage(Rand.Next(Math.max(1, var1 - 5), var1 + 5));
      }

      if (Rand.Next(4) == 0) {
         var2 = this.getPartById("DoorFrontLeft");
         if (var2 != nullptr && var2.getInventoryItem() != nullptr) {
            var2.damage(Rand.Next(Math.max(1, var1 - 5), var1 + 5));
         }

         var2 = this.getPartById("WindowFrontLeft");
         if (var2 != nullptr && var2.getInventoryItem() != nullptr) {
            var2.damage(Rand.Next(Math.max(1, var1 - 5), var1 + 5));
         }
      }

      if (Rand.Next(4) == 0) {
         var2 = this.getPartById("DoorFrontRight");
         if (var2 != nullptr && var2.getInventoryItem() != nullptr) {
            var2.damage(Rand.Next(Math.max(1, var1 - 5), var1 + 5));
         }

         var2 = this.getPartById("WindowFrontRight");
         if (var2 != nullptr && var2.getInventoryItem() != nullptr) {
            var2.damage(Rand.Next(Math.max(1, var1 - 5), var1 + 5));
         }
      }

      if (Rand.Next(20) < var1) {
         this.damageHeadlight("HeadlightLeft", var1);
      }

      if (Rand.Next(20) < var1) {
         this.damageHeadlight("HeadlightRight", var1);
      }
   }

    void addDamageRear(int var1) {
      this.currentRearEndDurability -= var1;
    VehiclePart var2 = this.getPartById("TruckBed");
      if (var2 != nullptr && var2.getInventoryItem() != nullptr) {
         var2.setCondition(var2.getCondition() - Rand.Next(Math.max(1, var1 - 5), var1 + 5));
         var2.doInventoryItemStats(var2.getInventoryItem(), 0);
         this.transmitPartCondition(var2);
      }

      var2 = this.getPartById("DoorRear");
      if (var2 != nullptr && var2.getInventoryItem() != nullptr) {
         var2.damage(Rand.Next(Math.max(1, var1 - 5), var1 + 5));
      }

      var2 = this.getPartById("TrunkDoor");
      if (var2 != nullptr && var2.getInventoryItem() != nullptr) {
         var2.damage(Rand.Next(Math.max(1, var1 - 5), var1 + 5));
      }

      var2 = this.getPartById("WindshieldRear");
      if (var2 != nullptr && var2.getInventoryItem() != nullptr) {
         var2.damage(var1);
      }

      if (Rand.Next(4) == 0) {
         var2 = this.getPartById("DoorRearLeft");
         if (var2 != nullptr && var2.getInventoryItem() != nullptr) {
            var2.damage(Rand.Next(Math.max(1, var1 - 5), var1 + 5));
         }

         var2 = this.getPartById("WindowRearLeft");
         if (var2 != nullptr && var2.getInventoryItem() != nullptr) {
            var2.damage(Rand.Next(Math.max(1, var1 - 5), var1 + 5));
         }
      }

      if (Rand.Next(4) == 0) {
         var2 = this.getPartById("DoorRearRight");
         if (var2 != nullptr && var2.getInventoryItem() != nullptr) {
            var2.damage(Rand.Next(Math.max(1, var1 - 5), var1 + 5));
         }

         var2 = this.getPartById("WindowRearRight");
         if (var2 != nullptr && var2.getInventoryItem() != nullptr) {
            var2.damage(Rand.Next(Math.max(1, var1 - 5), var1 + 5));
         }
      }

      if (Rand.Next(20) < var1) {
         this.damageHeadlight("HeadlightRearLeft", var1);
      }

      if (Rand.Next(20) < var1) {
         this.damageHeadlight("HeadlightRearRight", var1);
      }

      if (Rand.Next(20) < var1) {
         var2 = this.getPartById("Muffler");
         if (var2 != nullptr && var2.getInventoryItem() != nullptr) {
            var2.damage(Rand.Next(Math.max(1, var1 - 5), var1 + 5));
         }
      }
   }

    void damageHeadlight(const std::string& var1, int var2) {
    VehiclePart var3 = this.getPartById(var1);
      if (var3 != nullptr && var3.getInventoryItem() != nullptr) {
         var3.damage(var2);
         if (var3.getCondition() <= 0) {
            var3.setInventoryItem(nullptr);
            this.transmitPartItem(var3);
         }
      }
   }

    float clamp(float var1, float var2, float var3) {
      if (var1 < var2) {
         var1 = var2;
      }

      if (var1 > var3) {
         var1 = var3;
      }

    return var1;
   }

    bool isCharacterAdjacentTo(IsoGameCharacter var1) {
      if ((int)var1.z != (int)this.z) {
    return false;
      } else {
    Transform var2 = this.getWorldTransform(this.tempTransform);
         var2.inverse();
    Vector3f var3 = (Vector3f)TL_vector3f_pool.get().alloc();
         var3.set(var1.x - WorldSimulation.instance.offsetX, 0.0F, var1.y - WorldSimulation.instance.offsetY);
         var2.transform(var3);
    Vector3f var4 = this.script.getExtents();
    Vector3f var5 = this.script.getCenterOfMassOffset();
    float var6 = var5.x - var4.x / 2.0F;
    float var7 = var5.x + var4.x / 2.0F;
    float var8 = var5.z - var4.z / 2.0F;
    float var9 = var5.z + var4.z / 2.0F;
         if (var3.x >= var6 - 0.5F && var3.x < var7 + 0.5F && var3.z >= var8 - 0.5F && var3.z < var9 + 0.5F) {
            TL_vector3f_pool.get().release(var3);
    return true;
         } else {
            TL_vector3f_pool.get().release(var3);
    return false;
         }
      }
   }

    Vector2 testCollisionWithCharacter(IsoGameCharacter var1, float var2, Vector2 var3) {
      if (this.physics == nullptr) {
    return nullptr;
      } else {
    Vector3f var4 = this.script.getExtents();
    Vector3f var5 = this.script.getCenterOfMassOffset();
         if (this.DistToProper(var1) > Math.max(var4.x / 2.0F, var4.z / 2.0F) + var2 + 1.0F) {
    return nullptr;
         } else {
    Vector3f var6 = (Vector3f)TL_vector3f_pool.get().alloc();
            this.getLocalPos(var1.nx, var1.ny, 0.0F, var6);
    float var7 = var5.x - var4.x / 2.0F;
    float var8 = var5.x + var4.x / 2.0F;
    float var9 = var5.z - var4.z / 2.0F;
    float var10 = var5.z + var4.z / 2.0F;
            if (var6.x > var7 && var6.x < var8 && var6.z > var9 && var6.z < var10) {
    float var18 = var6.x - var7;
    float var19 = var8 - var6.x;
    float var20 = var6.z - var9;
    float var21 = var10 - var6.z;
    Vector3f var22 = (Vector3f)TL_vector3f_pool.get().alloc();
               if (var18 < var19 && var18 < var20 && var18 < var21) {
                  var22.set(var7 - var2 - 0.015F, 0.0F, var6.z);
               } else if (var19 < var18 && var19 < var20 && var19 < var21) {
                  var22.set(var8 + var2 + 0.015F, 0.0F, var6.z);
               } else if (var20 < var18 && var20 < var19 && var20 < var21) {
                  var22.set(var6.x, 0.0F, var9 - var2 - 0.015F);
               } else if (var21 < var18 && var21 < var19 && var21 < var20) {
                  var22.set(var6.x, 0.0F, var10 + var2 + 0.015F);
               }

               TL_vector3f_pool.get().release(var6);
    Transform var23 = this.getWorldTransform(this.tempTransform);
               var23.origin.set(0.0F, 0.0F, 0.0F);
               var23.transform(var22);
               var22.x = var22.x + this.getX();
               var22.z = var22.z + this.getY();
               this.collideX = var22.x;
               this.collideY = var22.z;
               var3.set(var22.x, var22.z);
               TL_vector3f_pool.get().release(var22);
    return var3;
            } else {
    float var11 = this.clamp(var6.x, var7, var8);
    float var12 = this.clamp(var6.z, var9, var10);
    float var13 = var6.x - var11;
    float var14 = var6.z - var12;
               TL_vector3f_pool.get().release(var6);
    float var15 = var13 * var13 + var14 * var14;
               if (var15 < var2 * var2) {
                  if (var13 == 0.0F && var14 == 0.0F) {
                     return var3.set(-1.0F, -1.0F);
                  } else {
    Vector3f var16 = (Vector3f)TL_vector3f_pool.get().alloc();
                     var16.set(var13, 0.0F, var14);
                     var16.normalize();
                     var16.mul(var2 + 0.015F);
                     var16.x += var11;
                     var16.z += var12;
    Transform var17 = this.getWorldTransform(this.tempTransform);
                     var17.origin.set(0.0F, 0.0F, 0.0F);
                     var17.transform(var16);
                     var16.x = var16.x + this.getX();
                     var16.z = var16.z + this.getY();
                     this.collideX = var16.x;
                     this.collideY = var16.z;
                     var3.set(var16.x, var16.z);
                     TL_vector3f_pool.get().release(var16);
    return var3;
                  }
               } else {
    return nullptr;
               }
            }
         }
      }
   }

    int testCollisionWithProneCharacter(IsoGameCharacter var1, bool var2) {
    Vector2 var3 = var1.getAnimVector((Vector2)TL_vector2_pool.get().alloc());
    int var4 = this.testCollisionWithProneCharacter(var1, var3.x, var3.y, var2);
      TL_vector2_pool.get().release(var3);
    return var4;
   }

    int testCollisionWithCorpse(IsoDeadBody var1, bool var2) {
    float var3 = (float)Math.cos(var1.getAngle());
    float var4 = (float)Math.sin(var1.getAngle());
      return this.testCollisionWithProneCharacter(var1, var3, var4, var2);
   }

    int testCollisionWithProneCharacter(IsoMovingObject var1, float var2, float var3, bool var4) {
      if (this.physics == nullptr) {
    return 0;
      } else if (GameServer.bServer) {
    return 0;
      } else {
    Vector3f var5 = this.script.getExtents();
    float var6 = 0.3F;
         if (this.DistToProper(var1) > Math.max(var5.x / 2.0F, var5.z / 2.0F) + var6 + 1.0F) {
    return 0;
         } else if (Math.abs(this.jniSpeed) < 3.0F) {
    return 0;
         } else {
    float var7 = var1.x + var2 * 0.65F;
    float var8 = var1.y + var3 * 0.65F;
    float var9 = var1.x - var2 * 0.65F;
    float var10 = var1.y - var3 * 0.65F;
    int var11 = 0;
    Vector3f var12 = (Vector3f)TL_vector3f_pool.get().alloc();
    Vector3f var13 = (Vector3f)TL_vector3f_pool.get().alloc();

            for (int var14 = 0; var14 < this.script.getWheelCount(); var14++) {
    Wheel var15 = this.script.getWheel(var14);
    bool var16 = true;

               for (int var17 = 0; var17 < this.models.size(); var17++) {
    ModelInfo var18 = this.models.get(var17);
                  if (var18.wheelIndex == var14) {
                     this.getWorldPos(var15.offset.x, var15.offset.y - this.wheelInfo[var14].suspensionLength, var15.offset.z, var12);
                     if (var12.z > this.script.getWheel(var14).radius + 0.05F) {
                        var16 = false;
                     }
                     break;
                  }
               }

               if (var16) {
                  this.getWorldPos(var15.offset.x, var15.offset.y, var15.offset.z, var13);
    float var21 = var13.x;
    float var22 = var13.y;
                  double var23 = ((var21 - var9) * (var7 - var9) + (var22 - var10) * (var8 - var10))
                     / (Math.pow(var7 - var9, 2.0) + Math.pow(var8 - var10, 2.0));
    float var25;
    float var26;
                  if (var23 <= 0.0) {
                     var25 = var9;
                     var26 = var10;
                  } else if (var23 >= 1.0) {
                     var25 = var7;
                     var26 = var8;
                  } else {
                     var25 = var9 + (var7 - var9) * (float)var23;
                     var26 = var10 + (var8 - var10) * (float)var23;
                  }

                  if (!(IsoUtils.DistanceToSquared(var13.x, var13.y, var25, var26) > var15.radius * var15.radius)) {
                     if (var4 && Math.abs(this.jniSpeed) > 10.0F) {
                        if (GameServer.bServer && dynamic_cast<IsoZombie*>(var1) != nullptr) {
                           ((IsoZombie)var1).setThumpFlag(1);
                        } else {
                           SoundManager.instance.PlayWorldSound("VehicleRunOverBody", var1.getCurrentSquare(), 0.0F, 20.0F, 0.9F, true);
                        }

                        var4 = false;
                     }

                     if (var14 < this.impulseFromSquishedZombie.length) {
                        if (this.impulseFromSquishedZombie[var14] == nullptr) {
                           this.impulseFromSquishedZombie[var14] = std::make_unique<VehicleImpulse>();
                        }

                        this.impulseFromSquishedZombie[var14].impulse.set(0.0F, 1.0F, 0.0F);
    float var27 = Math.max(Math.abs(this.jniSpeed), 20.0F) / 20.0F;
                        this.impulseFromSquishedZombie[var14].impulse.mul(0.065F * this.getFudgedMass() * var27);
                        this.impulseFromSquishedZombie[var14].rel_pos.set(var13.x - this.x, 0.0F, var13.y - this.y);
                        this.impulseFromSquishedZombie[var14].enable = true;
                        var11++;
                     }
                  }
               }
            }

            TL_vector3f_pool.get().release(var12);
            TL_vector3f_pool.get().release(var13);
    return var11;
         }
      }
   }

    Vector2 testCollisionWithObject(IsoObject var1, float var2, Vector2 var3) {
      if (this.physics == nullptr) {
    return nullptr;
      } else if (var1.square == nullptr) {
    return nullptr;
      } else {
    float var4 = this.getObjectX(var1);
    float var5 = this.getObjectY(var1);
    Vector3f var6 = this.script.getExtents();
    Vector3f var7 = this.script.getCenterOfMassOffset();
    float var8 = Math.max(var6.x / 2.0F, var6.z / 2.0F) + var2 + 1.0F;
         if (this.DistToSquared(var4, var5) > var8 * var8) {
    return nullptr;
         } else {
    Vector3f var9 = (Vector3f)TL_vector3f_pool.get().alloc();
            this.getLocalPos(var4, var5, 0.0F, var9);
    float var10 = var7.x - var6.x / 2.0F;
    float var11 = var7.x + var6.x / 2.0F;
    float var12 = var7.z - var6.z / 2.0F;
    float var13 = var7.z + var6.z / 2.0F;
            if (var9.x > var10 && var9.x < var11 && var9.z > var12 && var9.z < var13) {
    float var21 = var9.x - var10;
    float var22 = var11 - var9.x;
    float var23 = var9.z - var12;
    float var24 = var13 - var9.z;
    Vector3f var25 = (Vector3f)TL_vector3f_pool.get().alloc();
               if (var21 < var22 && var21 < var23 && var21 < var24) {
                  var25.set(var10 - var2 - 0.015F, 0.0F, var9.z);
               } else if (var22 < var21 && var22 < var23 && var22 < var24) {
                  var25.set(var11 + var2 + 0.015F, 0.0F, var9.z);
               } else if (var23 < var21 && var23 < var22 && var23 < var24) {
                  var25.set(var9.x, 0.0F, var12 - var2 - 0.015F);
               } else if (var24 < var21 && var24 < var22 && var24 < var23) {
                  var25.set(var9.x, 0.0F, var13 + var2 + 0.015F);
               }

               TL_vector3f_pool.get().release(var9);
    Transform var26 = this.getWorldTransform(this.tempTransform);
               var26.origin.set(0.0F, 0.0F, 0.0F);
               var26.transform(var25);
               var25.x = var25.x + this.getX();
               var25.z = var25.z + this.getY();
               this.collideX = var25.x;
               this.collideY = var25.z;
               var3.set(var25.x, var25.z);
               TL_vector3f_pool.get().release(var25);
    return var3;
            } else {
    float var14 = this.clamp(var9.x, var10, var11);
    float var15 = this.clamp(var9.z, var12, var13);
    float var16 = var9.x - var14;
    float var17 = var9.z - var15;
               TL_vector3f_pool.get().release(var9);
    float var18 = var16 * var16 + var17 * var17;
               if (var18 < var2 * var2) {
                  if (var16 == 0.0F && var17 == 0.0F) {
                     return var3.set(-1.0F, -1.0F);
                  } else {
    Vector3f var19 = (Vector3f)TL_vector3f_pool.get().alloc();
                     var19.set(var16, 0.0F, var17);
                     var19.normalize();
                     var19.mul(var2 + 0.015F);
                     var19.x += var14;
                     var19.z += var15;
    Transform var20 = this.getWorldTransform(this.tempTransform);
                     var20.origin.set(0.0F, 0.0F, 0.0F);
                     var20.transform(var19);
                     var19.x = var19.x + this.getX();
                     var19.z = var19.z + this.getY();
                     this.collideX = var19.x;
                     this.collideY = var19.z;
                     var3.set(var19.x, var19.z);
                     TL_vector3f_pool.get().release(var19);
    return var3;
                  }
               } else {
    return nullptr;
               }
            }
         }
      }
   }

    bool testCollisionWithVehicle(BaseVehicle var1) {
    VehicleScript var2 = this.script;
      if (var2 == nullptr) {
         var2 = ScriptManager.instance.getVehicle(this.scriptName);
      }

    VehicleScript var3 = var1.script;
      if (var3 == nullptr) {
         var3 = ScriptManager.instance.getVehicle(var1.scriptName);
      }

      if (var2 != nullptr && var3 != nullptr) {
         Vector2[] var4 = L_testCollisionWithVehicle.testVecs1;
         Vector2[] var5 = L_testCollisionWithVehicle.testVecs2;
         if (var4[0] == nullptr) {
            for (int var6 = 0; var6 < var4.length; var6++) {
               var4[var6] = std::make_unique<Vector2>();
               var5[var6] = std::make_unique<Vector2>();
            }
         }

    Vector3f var12 = var2.getExtents();
    Vector3f var7 = var2.getCenterOfMassOffset();
    Vector3f var8 = var3.getExtents();
    Vector3f var9 = var3.getCenterOfMassOffset();
    Vector3f var10 = L_testCollisionWithVehicle.worldPos;
    float var11 = 0.5F;
         this.getWorldPos(var7.x + var12.x * var11, 0.0F, var7.z + var12.z * var11, var10, var2);
         var4[0].set(var10.x, var10.y);
         this.getWorldPos(var7.x - var12.x * var11, 0.0F, var7.z + var12.z * var11, var10, var2);
         var4[1].set(var10.x, var10.y);
         this.getWorldPos(var7.x - var12.x * var11, 0.0F, var7.z - var12.z * var11, var10, var2);
         var4[2].set(var10.x, var10.y);
         this.getWorldPos(var7.x + var12.x * var11, 0.0F, var7.z - var12.z * var11, var10, var2);
         var4[3].set(var10.x, var10.y);
         var1.getWorldPos(var9.x + var8.x * var11, 0.0F, var9.z + var8.z * var11, var10, var3);
         var5[0].set(var10.x, var10.y);
         var1.getWorldPos(var9.x - var8.x * var11, 0.0F, var9.z + var8.z * var11, var10, var3);
         var5[1].set(var10.x, var10.y);
         var1.getWorldPos(var9.x - var8.x * var11, 0.0F, var9.z - var8.z * var11, var10, var3);
         var5[2].set(var10.x, var10.y);
         var1.getWorldPos(var9.x + var8.x * var11, 0.0F, var9.z - var8.z * var11, var10, var3);
         var5[3].set(var10.x, var10.y);
         return QuadranglesIntersection.IsQuadranglesAreIntersected(var4, var5);
      } else {
    return false;
      }
   }

    float getObjectX(IsoObject var1) {
      return dynamic_cast<IsoMovingObject*>(var1) != nullptr ? var1.getX() : var1.getSquare().getX() + 0.5F;
   }

    float getObjectY(IsoObject var1) {
      return dynamic_cast<IsoMovingObject*>(var1) != nullptr ? var1.getY() : var1.getSquare().getY() + 0.5F;
   }

    void ApplyImpulse(IsoObject var1, float var2) {
    float var3 = this.getObjectX(var1);
    float var4 = this.getObjectY(var1);
    VehicleImpulse var5 = VehicleImpulse.alloc();
      var5.impulse.set(this.x - var3, 0.0F, this.y - var4);
      var5.impulse.normalize();
      var5.impulse.mul(var2);
      var5.rel_pos.set(var3 - this.x, 0.0F, var4 - this.y);
      this.impulseFromHitZombie.push_back(var5);
   }

    void ApplyImpulse4Break(IsoObject var1, float var2) {
    float var3 = this.getObjectX(var1);
    float var4 = this.getObjectY(var1);
    VehicleImpulse var5 = VehicleImpulse.alloc();
      this.getLinearVelocity(var5.impulse);
      var5.impulse.mul(-var2 * this.getFudgedMass());
      var5.rel_pos.set(var3 - this.x, 0.0F, var4 - this.y);
      this.impulseFromHitZombie.push_back(var5);
   }

    void hitCharacter(IsoZombie var1) {
    IsoPlayer var2 = (IsoPlayer)Type.tryCastTo(var1, IsoPlayer.class);
    IsoZombie var3 = (IsoZombie)Type.tryCastTo(var1, IsoZombie.class);
      if (var1.getCurrentState() != StaggerBackState.instance() && var1.getCurrentState() != ZombieFallDownState.instance()) {
         if (!(Math.abs(var1.x - this.x) < 0.01F) && !(Math.abs(var1.y - this.y) < 0.01F)) {
    float var4 = 15.0F;
    Vector3f var5 = this.getLinearVelocity((Vector3f)TL_vector3f_pool.get().alloc());
            var5.y = 0.0F;
    float var6 = var5.length();
            var6 = Math.min(var6, var4);
            if (var6 < 0.05F) {
               TL_vector3f_pool.get().release(var5);
            } else {
    Vector3f var7 = (Vector3f)TL_vector3f_pool.get().alloc();
               var7.set(this.x - var1.x, 0.0F, this.y - var1.y);
               var7.normalize();
               var5.normalize();
    float var8 = var5.dot(var7);
               TL_vector3f_pool.get().release(var5);
               if (var8 < 0.0F && !GameServer.bServer) {
                  this.ApplyImpulse(var1, this.getFudgedMass() * 7.0F * var6 / var4 * Math.abs(var8));
               }

               var7.normalize();
               var7.mul(3.0F * var6 / var4);
    Vector2 var9 = (Vector2)TL_vector2_pool.get().alloc();
    float var10 = var6 + this.physics.clientForce / this.getFudgedMass();
               if (var2 != nullptr) {
                  var2.setVehicleHitLocation(this);
               } else if (var3 != nullptr) {
                  var3.setVehicleHitLocation(this);
               }

   BaseSoundEmitter var11 = IsoWorld.instance.getFreeEmitter(var1.x, var1.y, var1.z);
   long var12 = var11.playSound("VehicleHitCharacter");
            var11.setParameterValue(var12, "VehicleSpeed", this.getCurrentSpeedKmHour());
               var1.Hit(this, var10, var8 > 0.0F, var9.set(-var7.x, -var7.z));
               TL_vector2_pool.get().release(var9);
               TL_vector3f_pool.get().release(var7);
    long var19 = System.currentTimeMillis();
    long var13 = (var19 - this.zombieHitTimestamp) / 1000L;
               this.zombiesHits = Math.max(this.zombiesHits - (int)var13, 0);
               if (var19 - this.zombieHitTimestamp > 700L) {
                  this.zombieHitTimestamp = var19;
                  this.zombiesHits++;
                  this.zombiesHits = Math.min(this.zombiesHits, 20);
               }

               if (var6 >= 5.0F || this.zombiesHits > 10) {
                  var6 = this.getCurrentSpeedKmHour() / 5.0F;
    Vector3f var15 = (Vector3f)TL_vector3f_pool.get().alloc();
                  this.getLocalPos(var1.x, var1.y, var1.z, var15);
                  if (var15.z > 0.0F) {
    int var16 = this.caclulateDamageWithBodies(true);
                     this.addDamageFrontHitAChr(var16);
                  } else {
    int var20 = this.caclulateDamageWithBodies(false);
                     this.addDamageRearHitAChr(var20);
                  }

                  TL_vector3f_pool.get().release(var15);
               }
            }
         }
      }
   }

    int caclulateDamageWithBodies(bool var1) {
    bool var2 = this.getCurrentSpeedKmHour() > 0.0F;
    float var3 = Math.abs(this.getCurrentSpeedKmHour());
    float var4 = var3 / 160.0F;
      var4 = PZMath.clamp(var4 * var4, 0.0F, 1.0F);
    float var5 = 60.0F * var4;
    float var6 = PZMath.max(1.0F, this.zombiesHits / 3.0F);
      if (!var1 && !var2) {
         var6 = 1.0F;
      }

      if (this.zombiesHits > 10 && var5 < Math.abs(this.getCurrentSpeedKmHour()) / 5.0F) {
         var5 = Math.abs(this.getCurrentSpeedKmHour()) / 5.0F;
      }

      return (int)(var6 * var5);
   }

    int calculateDamageWithCharacter(IsoGameCharacter var1) {
    Vector3f var2 = (Vector3f)TL_vector3f_pool.get().alloc();
      this.getLocalPos(var1.x, var1.y, var1.z, var2);
    int var3;
      if (var2.z > 0.0F) {
         var3 = this.caclulateDamageWithBodies(true);
      } else {
         var3 = -1 * this.caclulateDamageWithBodies(false);
      }

      TL_vector3f_pool.get().release(var2);
    return var3;
   }

    bool blocked(int var1, int var2, int var3) {
      if (this.removedFromWorld || this.current == nullptr || this.getController() == nullptr) {
    return false;
      } else if (this.getController() == nullptr) {
    return false;
      } else if (var3 != (int)this.getZ()) {
    return false;
      } else if (IsoUtils.DistanceTo2D(var1 + 0.5F, var2 + 0.5F, this.x, this.y) > 5.0F) {
    return false;
      } else {
    float var4 = 0.3F;
    Transform var5 = this.tempTransform3;
         this.getWorldTransform(var5);
         var5.inverse();
    Vector3f var6 = (Vector3f)TL_vector3f_pool.get().alloc();
         var6.set(var1 + 0.5F - WorldSimulation.instance.offsetX, 0.0F, var2 + 0.5F - WorldSimulation.instance.offsetY);
         var5.transform(var6);
    Vector3f var7 = this.script.getExtents();
    Vector3f var8 = this.script.getCenterOfMassOffset();
    float var9 = this.clamp(var6.x, var8.x - var7.x / 2.0F, var8.x + var7.x / 2.0F);
    float var10 = this.clamp(var6.z, var8.z - var7.z / 2.0F, var8.z + var7.z / 2.0F);
    float var11 = var6.x - var9;
    float var12 = var6.z - var10;
         TL_vector3f_pool.get().release(var6);
    float var13 = var11 * var11 + var12 * var12;
         return var13 < var4 * var4;
      }
   }

    bool isIntersectingSquare(int var1, int var2, int var3) {
      if (var3 != (int)this.getZ()) {
    return false;
      } else if (!this.removedFromWorld && this.current != nullptr && this.getController() != nullptr) {
         tempPoly.x1 = tempPoly.x4 = var1;
         tempPoly.y1 = tempPoly.y2 = var2;
         tempPoly.x2 = tempPoly.x3 = var1 + 1;
         tempPoly.y3 = tempPoly.y4 = var2 + 1;
         return PolyPolyIntersect.intersects(tempPoly, this.getPoly());
      } else {
    return false;
      }
   }

    bool isIntersectingSquareWithShadow(int var1, int var2, int var3) {
      if (var3 != (int)this.getZ()) {
    return false;
      } else if (!this.removedFromWorld && this.current != nullptr && this.getController() != nullptr) {
         tempPoly.x1 = tempPoly.x4 = var1;
         tempPoly.y1 = tempPoly.y2 = var2;
         tempPoly.x2 = tempPoly.x3 = var1 + 1;
         tempPoly.y3 = tempPoly.y4 = var2 + 1;
         return PolyPolyIntersect.intersects(tempPoly, this.shadowCoord);
      } else {
    return false;
      }
   }

    bool circleIntersects(float var1, float var2, float var3, float var4) {
      if (this.getController() == nullptr) {
    return false;
      } else if ((int)var3 != (int)this.getZ()) {
    return false;
      } else if (IsoUtils.DistanceTo2D(var1, var2, this.x, this.y) > 5.0F) {
    return false;
      } else {
    Vector3f var5 = this.script.getExtents();
    Vector3f var6 = this.script.getCenterOfMassOffset();
    Vector3f var7 = (Vector3f)TL_vector3f_pool.get().alloc();
         this.getLocalPos(var1, var2, var3, var7);
    float var8 = var6.x - var5.x / 2.0F;
    float var9 = var6.x + var5.x / 2.0F;
    float var10 = var6.z - var5.z / 2.0F;
    float var11 = var6.z + var5.z / 2.0F;
         if (var7.x > var8 && var7.x < var9 && var7.z > var10 && var7.z < var11) {
    return true;
         } else {
    float var12 = this.clamp(var7.x, var8, var9);
    float var13 = this.clamp(var7.z, var10, var11);
    float var14 = var7.x - var12;
    float var15 = var7.z - var13;
            TL_vector3f_pool.get().release(var7);
    float var16 = var14 * var14 + var15 * var15;
            return var16 < var4 * var4;
         }
      }
   }

    void updateLights() {
    VehicleModelInstance var1 = (VehicleModelInstance)this.sprite.modelSlot.model;
      var1.textureRustA = this.rust;
      if (this.script.getWheelCount() == 0) {
         var1.textureRustA = 0.0F;
      }

      var1.painColor.x = this.colorHue;
      var1.painColor.y = this.colorSaturation;
      var1.painColor.z = this.colorValue;
    bool var2 = false;
    bool var3 = false;
    bool var4 = false;
    bool var5 = false;
    bool var6 = false;
    bool var7 = false;
    bool var8 = false;
    bool var9 = false;
      if (this.windowLightsOn) {
    VehiclePart var10 = this.getPartById("Windshield");
         var2 = var10 != nullptr && var10.getInventoryItem() != nullptr;
         var10 = this.getPartById("WindshieldRear");
         var3 = var10 != nullptr && var10.getInventoryItem() != nullptr;
         var10 = this.getPartById("WindowFrontLeft");
         var4 = var10 != nullptr && var10.getInventoryItem() != nullptr;
         var10 = this.getPartById("WindowMiddleLeft");
         var5 = var10 != nullptr && var10.getInventoryItem() != nullptr;
         var10 = this.getPartById("WindowRearLeft");
         var6 = var10 != nullptr && var10.getInventoryItem() != nullptr;
         var10 = this.getPartById("WindowFrontRight");
         var7 = var10 != nullptr && var10.getInventoryItem() != nullptr;
         var10 = this.getPartById("WindowMiddleRight");
         var8 = var10 != nullptr && var10.getInventoryItem() != nullptr;
         var10 = this.getPartById("WindowRearRight");
         var9 = var10 != nullptr && var10.getInventoryItem() != nullptr;
      }

      var1.textureLightsEnables1[10] = var2 ? 1.0F : 0.0F;
      var1.textureLightsEnables1[14] = var3 ? 1.0F : 0.0F;
      var1.textureLightsEnables1[2] = var4 ? 1.0F : 0.0F;
      var1.textureLightsEnables1[6] = var5 | var6 ? 1.0F : 0.0F;
      var1.textureLightsEnables1[9] = var7 ? 1.0F : 0.0F;
      var1.textureLightsEnables1[13] = var8 | var9 ? 1.0F : 0.0F;
    bool var25 = false;
    bool var11 = false;
    bool var12 = false;
    bool var13 = false;
      if (this.headlightsOn && this.getBatteryCharge() > 0.0F) {
    VehiclePart var14 = this.getPartById("HeadlightLeft");
         if (var14 != nullptr && var14.getInventoryItem() != nullptr) {
            var25 = true;
         }

         var14 = this.getPartById("HeadlightRight");
         if (var14 != nullptr && var14.getInventoryItem() != nullptr) {
            var11 = true;
         }

         var14 = this.getPartById("HeadlightRearLeft");
         if (var14 != nullptr && var14.getInventoryItem() != nullptr) {
            var13 = true;
         }

         var14 = this.getPartById("HeadlightRearRight");
         if (var14 != nullptr && var14.getInventoryItem() != nullptr) {
            var12 = true;
         }
      }

      var1.textureLightsEnables2[4] = var11 ? 1.0F : 0.0F;
      var1.textureLightsEnables2[8] = var25 ? 1.0F : 0.0F;
      var1.textureLightsEnables2[12] = var12 ? 1.0F : 0.0F;
      var1.textureLightsEnables2[1] = var13 ? 1.0F : 0.0F;
    bool var29 = this.stoplightsOn && this.getBatteryCharge() > 0.0F;
      if (this.scriptName.contains("Trailer")
         && this.vehicleTowedBy != nullptr
         && this.vehicleTowedBy.stoplightsOn
         && this.vehicleTowedBy.getBatteryCharge() > 0.0F) {
         var29 = true;
      }

      if (var29) {
         var1.textureLightsEnables2[5] = 1.0F;
         var1.textureLightsEnables2[9] = 1.0F;
      } else {
         var1.textureLightsEnables2[5] = 0.0F;
         var1.textureLightsEnables2[9] = 0.0F;
      }

      if (this.script.getLightbar().enable) {
         if (this.lightbarLightsMode.isEnable() && this.getBatteryCharge() > 0.0F) {
            switch (this.lightbarLightsMode.getLightTexIndex()) {
               case 0:
                  var1.textureLightsEnables2[13] = 0.0F;
                  var1.textureLightsEnables2[2] = 0.0F;
                  break;
               case 1:
                  var1.textureLightsEnables2[13] = 0.0F;
                  var1.textureLightsEnables2[2] = 1.0F;
                  break;
               case 2:
                  var1.textureLightsEnables2[13] = 1.0F;
                  var1.textureLightsEnables2[2] = 0.0F;
                  break;
               default:
                  var1.textureLightsEnables2[13] = 0.0F;
                  var1.textureLightsEnables2[2] = 0.0F;
            }
         } else {
            var1.textureLightsEnables2[13] = 0.0F;
            var1.textureLightsEnables2[2] = 0.0F;
         }
      }

      if (DebugOptions.instance.VehicleCycleColor.getValue()) {
    float var15 = (float)(System.currentTimeMillis() % 2000L);
    float var16 = (float)(System.currentTimeMillis() % 7000L);
    float var17 = (float)(System.currentTimeMillis() % 11000L);
         var1.painColor.x = var15 / 2000.0F;
         var1.painColor.y = var16 / 7000.0F;
         var1.painColor.z = var17 / 11000.0F;
      }

      if (DebugOptions.instance.VehicleRenderBlood0.getValue()) {
         Arrays.fill(var1.matrixBlood1Enables1, 0.0F);
         Arrays.fill(var1.matrixBlood1Enables2, 0.0F);
         Arrays.fill(var1.matrixBlood2Enables1, 0.0F);
         Arrays.fill(var1.matrixBlood2Enables2, 0.0F);
      }

      if (DebugOptions.instance.VehicleRenderBlood50.getValue()) {
         Arrays.fill(var1.matrixBlood1Enables1, 0.5F);
         Arrays.fill(var1.matrixBlood1Enables2, 0.5F);
         Arrays.fill(var1.matrixBlood2Enables1, 1.0F);
         Arrays.fill(var1.matrixBlood2Enables2, 1.0F);
      }

      if (DebugOptions.instance.VehicleRenderBlood100.getValue()) {
         Arrays.fill(var1.matrixBlood1Enables1, 1.0F);
         Arrays.fill(var1.matrixBlood1Enables2, 1.0F);
         Arrays.fill(var1.matrixBlood2Enables1, 1.0F);
         Arrays.fill(var1.matrixBlood2Enables2, 1.0F);
      }

      if (DebugOptions.instance.VehicleRenderDamage0.getValue()) {
         Arrays.fill(var1.textureDamage1Enables1, 0.0F);
         Arrays.fill(var1.textureDamage1Enables2, 0.0F);
         Arrays.fill(var1.textureDamage2Enables1, 0.0F);
         Arrays.fill(var1.textureDamage2Enables2, 0.0F);
      }

      if (DebugOptions.instance.VehicleRenderDamage1.getValue()) {
         Arrays.fill(var1.textureDamage1Enables1, 1.0F);
         Arrays.fill(var1.textureDamage1Enables2, 1.0F);
         Arrays.fill(var1.textureDamage2Enables1, 0.0F);
         Arrays.fill(var1.textureDamage2Enables2, 0.0F);
      }

      if (DebugOptions.instance.VehicleRenderDamage2.getValue()) {
         Arrays.fill(var1.textureDamage1Enables1, 0.0F);
         Arrays.fill(var1.textureDamage1Enables2, 0.0F);
         Arrays.fill(var1.textureDamage2Enables1, 1.0F);
         Arrays.fill(var1.textureDamage2Enables2, 1.0F);
      }

      if (DebugOptions.instance.VehicleRenderRust0.getValue()) {
         var1.textureRustA = 0.0F;
      }

      if (DebugOptions.instance.VehicleRenderRust50.getValue()) {
         var1.textureRustA = 0.5F;
      }

      if (DebugOptions.instance.VehicleRenderRust100.getValue()) {
         var1.textureRustA = 1.0F;
      }

      var1.refBody = 0.3F;
      var1.refWindows = 0.4F;
      if (this.rust > 0.8F) {
         var1.refBody = 0.1F;
         var1.refWindows = 0.2F;
      }
   }

    void updateWorldLights() {
      if (!this.script.getLightbar().enable) {
         this.removeWorldLights();
      } else if (!this.lightbarLightsMode.isEnable() || this.getBatteryCharge() <= 0.0F) {
         this.removeWorldLights();
      } else if (this.lightbarLightsMode.getLightTexIndex() == 0) {
         this.removeWorldLights();
      } else {
         this.leftLight1.radius = this.leftLight2.radius = this.rightLight1.radius = this.rightLight2.radius = 8;
         if (this.lightbarLightsMode.getLightTexIndex() == 1) {
    Vector3f var1 = this.getWorldPos(0.4F, 0.0F, 0.0F, (Vector3f)TL_vector3f_pool.get().alloc());
    int var2 = (int)var1.x;
    int var3 = (int)var1.y;
    int var4 = (int)(this.getZ() + 1.0F);
            TL_vector3f_pool.get().release(var1);
    int var5 = this.leftLightIndex;
            if (var5 == 1 && this.leftLight1.x == var2 && this.leftLight1.y == var3 && this.leftLight1.z == var4) {
               return;
            }

            if (var5 == 2 && this.leftLight2.x == var2 && this.leftLight2.y == var3 && this.leftLight2.z == var4) {
               return;
            }

            this.removeWorldLights();
    IsoLightSource var6;
            if (var5 == 1) {
               var6 = this.leftLight2;
               this.leftLightIndex = 2;
            } else {
               var6 = this.leftLight1;
               this.leftLightIndex = 1;
            }

            var6.life = -1;
            var6.x = var2;
            var6.y = var3;
            var6.z = var4;
            IsoWorld.instance.CurrentCell.addLamppost(var6);
         } else {
    Vector3f var7 = this.getWorldPos(-0.4F, 0.0F, 0.0F, (Vector3f)TL_vector3f_pool.get().alloc());
    int var8 = (int)var7.x;
    int var9 = (int)var7.y;
    int var10 = (int)(this.getZ() + 1.0F);
            TL_vector3f_pool.get().release(var7);
    int var11 = this.rightLightIndex;
            if (var11 == 1 && this.rightLight1.x == var8 && this.rightLight1.y == var9 && this.rightLight1.z == var10) {
               return;
            }

            if (var11 == 2 && this.rightLight2.x == var8 && this.rightLight2.y == var9 && this.rightLight2.z == var10) {
               return;
            }

            this.removeWorldLights();
    IsoLightSource var12;
            if (var11 == 1) {
               var12 = this.rightLight2;
               this.rightLightIndex = 2;
            } else {
               var12 = this.rightLight1;
               this.rightLightIndex = 1;
            }

            var12.life = -1;
            var12.x = var8;
            var12.y = var9;
            var12.z = var10;
            IsoWorld.instance.CurrentCell.addLamppost(var12);
         }
      }
   }

    void fixLightbarModelLighting(IsoLightSource var1, Vector3f var2) {
      if (var1 == this.leftLight1 || var1 == this.leftLight2) {
         var2.set(1.0F, 0.0F, 0.0F);
      } else if (var1 == this.rightLight1 || var1 == this.rightLight2) {
         var2.set(-1.0F, 0.0F, 0.0F);
      }
   }

    void removeWorldLights() {
      if (this.leftLightIndex == 1) {
         IsoWorld.instance.CurrentCell.removeLamppost(this.leftLight1);
         this.leftLightIndex = -1;
      }

      if (this.leftLightIndex == 2) {
         IsoWorld.instance.CurrentCell.removeLamppost(this.leftLight2);
         this.leftLightIndex = -1;
      }

      if (this.rightLightIndex == 1) {
         IsoWorld.instance.CurrentCell.removeLamppost(this.rightLight1);
         this.rightLightIndex = -1;
      }

      if (this.rightLightIndex == 2) {
         IsoWorld.instance.CurrentCell.removeLamppost(this.rightLight2);
         this.rightLightIndex = -1;
      }
   }

    void doDamageOverlay() {
      if (this.sprite.modelSlot != nullptr) {
         this.doDoorDamage();
         this.doWindowDamage();
         this.doOtherBodyWorkDamage();
         this.doBloodOverlay();
      }
   }

    void checkDamage(VehiclePart var1, int var2, bool var3) {
      if (var3 && var1 != nullptr && var1.getId().startsWith("Window") && var1.getScriptModelById("Default") != nullptr) {
         var3 = false;
      }

    VehicleModelInstance var4 = (VehicleModelInstance)this.sprite.modelSlot.model;

      try {
         var4.textureDamage1Enables1[var2] = 0.0F;
         var4.textureDamage2Enables1[var2] = 0.0F;
         var4.textureUninstall1[var2] = 0.0F;
         if (var1 != nullptr && var1.getInventoryItem() != nullptr) {
            if (var1.getInventoryItem().getCondition() < 60 && var1.getInventoryItem().getCondition() >= 40) {
               var4.textureDamage1Enables1[var2] = 1.0F;
            }

            if (var1.getInventoryItem().getCondition() < 40) {
               var4.textureDamage2Enables1[var2] = 1.0F;
            }

            if (var1.window != nullptr && var1.window.isOpen() && var3) {
               var4.textureUninstall1[var2] = 1.0F;
            }
         } else if (var1 != nullptr && var3) {
            var4.textureUninstall1[var2] = 1.0F;
         }
      } catch (Exception var6) {
         var6.printStackTrace();
      }
   }

    void checkDamage2(VehiclePart var1, int var2, bool var3) {
    VehicleModelInstance var4 = (VehicleModelInstance)this.sprite.modelSlot.model;

      try {
         var4.textureDamage1Enables2[var2] = 0.0F;
         var4.textureDamage2Enables2[var2] = 0.0F;
         var4.textureUninstall2[var2] = 0.0F;
         if (var1 != nullptr && var1.getInventoryItem() != nullptr) {
            if (var1.getInventoryItem().getCondition() < 60 && var1.getInventoryItem().getCondition() >= 40) {
               var4.textureDamage1Enables2[var2] = 1.0F;
            }

            if (var1.getInventoryItem().getCondition() < 40) {
               var4.textureDamage2Enables2[var2] = 1.0F;
            }

            if (var1.window != nullptr && var1.window.isOpen() && var3) {
               var4.textureUninstall2[var2] = 1.0F;
            }
         } else if (var1 != nullptr && var3) {
            var4.textureUninstall2[var2] = 1.0F;
         }
      } catch (Exception var6) {
         var6.printStackTrace();
      }
   }

    void checkUninstall2(VehiclePart var1, int var2) {
    VehicleModelInstance var3 = (VehicleModelInstance)this.sprite.modelSlot.model;

      try {
         var3.textureUninstall2[var2] = 0.0F;
         if (var1 != nullptr && var1.getInventoryItem() == nullptr) {
            var3.textureUninstall2[var2] = 1.0F;
         }
      } catch (Exception var5) {
         var5.printStackTrace();
      }
   }

    void doOtherBodyWorkDamage() {
      this.checkDamage(this.getPartById("EngineDoor"), 0, false);
      this.checkDamage(this.getPartById("EngineDoor"), 3, false);
      this.checkDamage(this.getPartById("EngineDoor"), 11, false);
      this.checkDamage2(this.getPartById("EngineDoor"), 6, true);
      this.checkDamage(this.getPartById("TruckBed"), 4, false);
      this.checkDamage(this.getPartById("TruckBed"), 7, false);
      this.checkDamage(this.getPartById("TruckBed"), 15, false);
    VehiclePart var1 = this.getPartById("TrunkDoor");
      if (var1 != nullptr) {
         this.checkDamage2(var1, 10, true);
         if (var1.scriptPart.hasLightsRear) {
            this.checkUninstall2(var1, 12);
            this.checkUninstall2(var1, 1);
            this.checkUninstall2(var1, 5);
            this.checkUninstall2(var1, 9);
         }
      } else {
         var1 = this.getPartById("DoorRear");
         if (var1 != nullptr) {
            this.checkDamage2(var1, 10, true);
            if (var1.scriptPart.hasLightsRear) {
               this.checkUninstall2(var1, 12);
               this.checkUninstall2(var1, 1);
               this.checkUninstall2(var1, 5);
               this.checkUninstall2(var1, 9);
            }
         }
      }
   }

    void doWindowDamage() {
      this.checkDamage(this.getPartById("WindowFrontLeft"), 2, true);
      this.checkDamage(this.getPartById("WindowFrontRight"), 9, true);
    VehiclePart var1 = this.getPartById("WindowRearLeft");
      if (var1 != nullptr) {
         this.checkDamage(var1, 6, true);
      } else {
         var1 = this.getPartById("WindowMiddleLeft");
         if (var1 != nullptr) {
            this.checkDamage(var1, 6, true);
         }
      }

      var1 = this.getPartById("WindowRearRight");
      if (var1 != nullptr) {
         this.checkDamage(var1, 13, true);
      } else {
         var1 = this.getPartById("WindowMiddleRight");
         if (var1 != nullptr) {
            this.checkDamage(var1, 13, true);
         }
      }

      this.checkDamage(this.getPartById("Windshield"), 10, true);
      this.checkDamage(this.getPartById("WindshieldRear"), 14, true);
   }

    void doDoorDamage() {
      this.checkDamage(this.getPartById("DoorFrontLeft"), 1, true);
      this.checkDamage(this.getPartById("DoorFrontRight"), 8, true);
    VehiclePart var1 = this.getPartById("DoorRearLeft");
      if (var1 != nullptr) {
         this.checkDamage(var1, 5, true);
      } else {
         var1 = this.getPartById("DoorMiddleLeft");
         if (var1 != nullptr) {
            this.checkDamage(var1, 5, true);
         }
      }

      var1 = this.getPartById("DoorRearRight");
      if (var1 != nullptr) {
         this.checkDamage(var1, 12, true);
      } else {
         var1 = this.getPartById("DoorMiddleRight");
         if (var1 != nullptr) {
            this.checkDamage(var1, 12, true);
         }
      }
   }

    float getBloodIntensity(const std::string& var1) {
      return (this.bloodIntensity.getOrDefault(var1, BYTE_ZERO) & 255) / 100.0F;
   }

    void setBloodIntensity(const std::string& var1, float var2) {
    uint8_t var3 = (byte)(PZMath.clamp(var2, 0.0F, 1.0F) * 100.0F);
      if (!this.bloodIntensity.containsKey(var1) || var3 != this.bloodIntensity.get(var1)) {
         this.bloodIntensity.put(var1, var3);
         this.doBloodOverlay();
         this.transmitBlood();
      }
   }

    void transmitBlood() {
      if (GameServer.bServer) {
         this.updateFlags = (short)(this.updateFlags | 4096);
      }
   }

    void doBloodOverlay() {
      if (this.sprite.modelSlot != nullptr) {
    VehicleModelInstance var1 = (VehicleModelInstance)this.sprite.modelSlot.model;
         Arrays.fill(var1.matrixBlood1Enables1, 0.0F);
         Arrays.fill(var1.matrixBlood1Enables2, 0.0F);
         Arrays.fill(var1.matrixBlood2Enables1, 0.0F);
         Arrays.fill(var1.matrixBlood2Enables2, 0.0F);
         if (Core.getInstance().getOptionBloodDecals() != 0) {
            this.doBloodOverlayFront(var1.matrixBlood1Enables1, var1.matrixBlood1Enables2, this.getBloodIntensity("Front"));
            this.doBloodOverlayRear(var1.matrixBlood1Enables1, var1.matrixBlood1Enables2, this.getBloodIntensity("Rear"));
            this.doBloodOverlayLeft(var1.matrixBlood1Enables1, var1.matrixBlood1Enables2, this.getBloodIntensity("Left"));
            this.doBloodOverlayRight(var1.matrixBlood1Enables1, var1.matrixBlood1Enables2, this.getBloodIntensity("Right"));

            for (Entry var3 : this.bloodIntensity.entrySet()) {
    int var4 = s_PartToMaskMap.get(var3.getKey());
               if (var4 != nullptr) {
                  var1.matrixBlood1Enables1[var4] = ((uint8_t)var3.getValue() & 255) / 100.0F;
               }
            }

            this.doBloodOverlayAux(var1.matrixBlood2Enables1, var1.matrixBlood2Enables2, 1.0F);
         }
      }
   }

    void doBloodOverlayAux(float[] var1, float[] var2, float var3) {
      var1[0] = var3;
      var2[6] = var3;
      var2[4] = var3;
      var2[8] = var3;
      var1[4] = var3;
      var1[7] = var3;
      var1[15] = var3;
      var2[10] = var3;
      var2[12] = var3;
      var2[1] = var3;
      var2[5] = var3;
      var2[9] = var3;
      var1[3] = var3;
      var1[8] = var3;
      var1[12] = var3;
      var1[11] = var3;
      var1[1] = var3;
      var1[5] = var3;
      var2[0] = var3;
      var1[10] = var3;
      var1[14] = var3;
      var1[9] = var3;
      var1[13] = var3;
      var1[2] = var3;
      var1[6] = var3;
   }

    void doBloodOverlayFront(float[] var1, float[] var2, float var3) {
      var1[0] = var3;
      var2[6] = var3;
      var2[4] = var3;
      var2[8] = var3;
      var1[10] = var3;
   }

    void doBloodOverlayRear(float[] var1, float[] var2, float var3) {
      var1[4] = var3;
      var2[10] = var3;
      var2[12] = var3;
      var2[1] = var3;
      var2[5] = var3;
      var2[9] = var3;
      var1[14] = var3;
   }

    void doBloodOverlayLeft(float[] var1, float[] var2, float var3) {
      var1[11] = var3;
      var1[1] = var3;
      var1[5] = var3;
      var1[15] = var3;
      var1[2] = var3;
      var1[6] = var3;
   }

    void doBloodOverlayRight(float[] var1, float[] var2, float var3) {
      var1[3] = var3;
      var1[8] = var3;
      var1[12] = var3;
      var1[7] = var3;
      var1[9] = var3;
      var1[13] = var3;
   }

    void render(float var1, float var2, float var3, ColorInfo var4, bool var5, bool var6, Shader var7) {
      if (this.script != nullptr) {
         if (this.physics != nullptr) {
            this.physics.debug();
         }

    int var8 = IsoCamera.frameState.playerIndex;
    bool var9 = IsoCamera.CamCharacter != nullptr && IsoCamera.CamCharacter.getVehicle() == this;
         if (var9 || this.square.lighting[var8].bSeen()) {
            if (!var9 && !this.square.lighting[var8].bCouldSee()) {
               this.setTargetAlpha(var8, 0.0F);
            } else {
               this.setTargetAlpha(var8, 1.0F);
            }

            if (this.sprite.hasActiveModel()) {
               this.updateLights();
    bool var10 = Core.getInstance().getOptionBloodDecals() != 0;
               if (this.OptionBloodDecals != var10) {
                  this.OptionBloodDecals = var10;
                  this.doBloodOverlay();
               }

               var4.a = this.getAlpha(var8);
               inf.a = var4.a;
               inf.r = var4.r;
               inf.g = var4.g;
               inf.b = var4.b;
               this.sprite.renderVehicle(this.def, this, var1, var2, 0.0F, 0.0F, 0.0F, inf, true);
            }

            this.updateAlpha(var8);
            if (Core.bDebug && DebugOptions.instance.VehicleRenderArea.getValue()) {
               this.renderAreas();
            }

            if (Core.bDebug && DebugOptions.instance.VehicleRenderAttackPositions.getValue()) {
               this.m_surroundVehicle.render();
            }

            if (Core.bDebug && DebugOptions.instance.VehicleRenderExit.getValue()) {
               this.renderExits();
            }

            if (Core.bDebug && DebugOptions.instance.VehicleRenderIntersectedSquares.getValue()) {
               this.renderIntersectedSquares();
            }

            if (Core.bDebug && DebugOptions.instance.VehicleRenderAuthorizations.getValue()) {
               this.renderAuthorizations();
            }

            if (Core.bDebug && DebugOptions.instance.VehicleRenderInterpolateBuffer.getValue()) {
               this.renderInterpolateBuffer();
            }

            if (DebugOptions.instance.VehicleRenderTrailerPositions.getValue()) {
               this.renderTrailerPositions();
            }

            this.renderUsableArea();
         }
      }
   }

    void renderlast() {
    int var1 = IsoCamera.frameState.playerIndex;

      for (int var2 = 0; var2 < this.parts.size(); var2++) {
    VehiclePart var3 = this.parts.get(var2);
         if (var3.chatElement != nullptr && var3.chatElement.getHasChatToDisplay()) {
            if (var3.getDeviceData() != nullptr && !var3.getDeviceData().getIsTurnedOn()) {
               var3.chatElement.clear(var1);
            } else {
    float var4 = IsoUtils.XToScreen(this.getX(), this.getY(), this.getZ(), 0);
    float var5 = IsoUtils.YToScreen(this.getX(), this.getY(), this.getZ(), 0);
               var4 = var4 - IsoCamera.getOffX() - this.offsetX;
               var5 = var5 - IsoCamera.getOffY() - this.offsetY;
               var4 += 32 * Core.TileScale;
               var5 += 20 * Core.TileScale;
               var4 /= Core.getInstance().getZoom(var1);
               var5 /= Core.getInstance().getZoom(var1);
               var3.chatElement.renderBatched(var1, (int)var4, (int)var5);
            }
         }
      }
   }

    void renderShadow() {
      if (this.physics != nullptr) {
         if (this.script != nullptr) {
    int var1 = IsoCamera.frameState.playerIndex;
            if (this.square.lighting[var1].bSeen()) {
               if (this.square.lighting[var1].bCouldSee()) {
                  this.setTargetAlpha(var1, 1.0F);
               } else {
                  this.setTargetAlpha(var1, 0.0F);
               }

    Texture var2 = this.getShadowTexture();
               if (var2 != nullptr && this.getCurrentSquare() != nullptr) {
    float var3 = 0.6F * this.getAlpha(var1);
    ColorInfo var4 = this.getCurrentSquare().lighting[var1].lightInfo();
                  var3 *= (var4.r + var4.g + var4.b) / 3.0F;
                  if (this.polyDirty) {
                     this.getPoly();
                  }

                  SpriteRenderer.instance
                     .renderPoly(
                        var2,
                        (int)IsoUtils.XToScreenExact(this.shadowCoord.x2, this.shadowCoord.y2, 0.0F, 0),
                        (int)IsoUtils.YToScreenExact(this.shadowCoord.x2, this.shadowCoord.y2, 0.0F, 0),
                        (int)IsoUtils.XToScreenExact(this.shadowCoord.x1, this.shadowCoord.y1, 0.0F, 0),
                        (int)IsoUtils.YToScreenExact(this.shadowCoord.x1, this.shadowCoord.y1, 0.0F, 0),
                        (int)IsoUtils.XToScreenExact(this.shadowCoord.x4, this.shadowCoord.y4, 0.0F, 0),
                        (int)IsoUtils.YToScreenExact(this.shadowCoord.x4, this.shadowCoord.y4, 0.0F, 0),
                        (int)IsoUtils.XToScreenExact(this.shadowCoord.x3, this.shadowCoord.y3, 0.0F, 0),
                        (int)IsoUtils.YToScreenExact(this.shadowCoord.x3, this.shadowCoord.y3, 0.0F, 0),
                        1.0F,
                        1.0F,
                        1.0F,
                        0.8F * var3
                     );
               }
            }
         }
      }
   }

    bool isEnterBlocked(IsoGameCharacter var1, int var2) {
      return this.isExitBlocked(var1, var2);
   }

    bool isExitBlocked(int var1) {
    Position var2 = this.getPassengerPosition(var1, "inside");
    Position var3 = this.getPassengerPosition(var1, "outside");
      if (var2 != nullptr && var3 != nullptr) {
    Vector3f var4 = this.getPassengerPositionWorldPos(var3, (Vector3f)TL_vector3f_pool.get().alloc());
         if (var3.area != nullptr) {
    Vector2 var5 = (Vector2)TL_vector2_pool.get().alloc();
    Area var6 = this.script.getAreaById(var3.area);
    Vector2 var7 = this.areaPositionWorld4PlayerInteract(var6, var5);
            if (var7 != nullptr) {
               var4.x = var7.x;
               var4.y = var7.y;
            }

            TL_vector2_pool.get().release(var5);
         }

         var4.z = 0.0F;
    Vector3f var8 = this.getPassengerPositionWorldPos(var2, (Vector3f)TL_vector3f_pool.get().alloc());
    bool var9 = PolygonalMap2.instance.lineClearCollide(var8.x, var8.y, var4.x, var4.y, (int)this.z, this, false, false);
         TL_vector3f_pool.get().release(var4);
         TL_vector3f_pool.get().release(var8);
    return var9;
      } else {
    return true;
      }
   }

    bool isExitBlocked(IsoGameCharacter var1, int var2) {
    Position var3 = this.getPassengerPosition(var2, "inside");
    Position var4 = this.getPassengerPosition(var2, "outside");
      if (var3 != nullptr && var4 != nullptr) {
    Vector3f var5 = this.getPassengerPositionWorldPos(var4, (Vector3f)TL_vector3f_pool.get().alloc());
         if (var4.area != nullptr) {
    Vector2 var6 = (Vector2)TL_vector2_pool.get().alloc();
    Area var7 = this.script.getAreaById(var4.area);
    Vector2 var8 = this.areaPositionWorld4PlayerInteract(var7, var6);
            if (var8 != nullptr) {
               var5.x = var8.x;
               var5.y = var8.y;
            }

            TL_vector2_pool.get().release(var6);
         }

         var5.z = 0.0F;
    Vector3f var9 = this.getPassengerPositionWorldPos(var3, (Vector3f)TL_vector3f_pool.get().alloc());
    bool var10 = PolygonalMap2.instance.lineClearCollide(var9.x, var9.y, var5.x, var5.y, (int)this.z, this, false, false);
         TL_vector3f_pool.get().release(var5);
         TL_vector3f_pool.get().release(var9);
         if (!var10 && GameClient.bClient) {
    IsoGridSquare var11 = IsoWorld.instance.CurrentCell.getGridSquare(var5.x, var5.y, var5.z);
            if (var11 != nullptr && dynamic_cast<IsoPlayer*>(var1) != nullptr && !SafeHouse.isPlayerAllowedOnSquare((IsoPlayer)var1, var11)) {
               var10 = true;
            }
         }

    return var10;
      } else {
    return true;
      }
   }

    bool isPassengerUseDoor2(IsoGameCharacter var1, int var2) {
    Position var3 = this.getPassengerPosition(var2, "outside2");
      if (var3 != nullptr) {
    Vector3f var4 = this.getPassengerPositionWorldPos(var3, (Vector3f)TL_vector3f_pool.get().alloc());
         var4.sub(var1.x, var1.y, var1.z);
    float var5 = var4.length();
         TL_vector3f_pool.get().release(var4);
         if (var5 < 2.0F) {
    return true;
         }
      }

    return false;
   }

    bool isEnterBlocked2(IsoGameCharacter var1, int var2) {
      return this.isExitBlocked2(var2);
   }

    bool isExitBlocked2(int var1) {
    Position var2 = this.getPassengerPosition(var1, "inside");
    Position var3 = this.getPassengerPosition(var1, "outside2");
      if (var2 != nullptr && var3 != nullptr) {
    Vector3f var4 = this.getPassengerPositionWorldPos(var3, (Vector3f)TL_vector3f_pool.get().alloc());
         var4.z = 0.0F;
    Vector3f var5 = this.getPassengerPositionWorldPos(var2, (Vector3f)TL_vector3f_pool.get().alloc());
    bool var6 = PolygonalMap2.instance.lineClearCollide(var5.x, var5.y, var4.x, var4.y, (int)this.z, this, false, false);
    IsoGridSquare var7 = IsoWorld.instance.CurrentCell.getGridSquare(var4.x, var4.y, var4.z);
    IsoGameCharacter var8 = this.getCharacter(var1);
         if (dynamic_cast<IsoPlayer*>(var8) != nullptr && !SafeHouse.isPlayerAllowedOnSquare((IsoPlayer)var8, var7)) {
            var6 = true;
         }

         TL_vector3f_pool.get().release(var4);
         TL_vector3f_pool.get().release(var5);
    return var6;
      } else {
    return true;
      }
   }

    void renderExits() {
    int var1 = Core.TileScale;
    Vector3f var2 = (Vector3f)TL_vector3f_pool.get().alloc();
    Vector3f var3 = (Vector3f)TL_vector3f_pool.get().alloc();

      for (int var4 = 0; var4 < this.getMaxPassengers(); var4++) {
    Position var5 = this.getPassengerPosition(var4, "inside");
    Position var6 = this.getPassengerPosition(var4, "outside");
         if (var5 != nullptr && var6 != nullptr) {
    float var7 = 0.3F;
            this.getPassengerPositionWorldPos(var6, var2);
            this.getPassengerPositionWorldPos(var5, var3);
    int var8 = (int)Math.floor(var2.x - var7);
    int var9 = (int)Math.floor(var2.x + var7);
    int var10 = (int)Math.floor(var2.y - var7);
    int var11 = (int)Math.floor(var2.y + var7);

            for (int var12 = var10; var12 <= var11; var12++) {
               for (int var13 = var8; var13 <= var9; var13++) {
    int var14 = (int)IsoUtils.XToScreenExact(var13, var12 + 1, (int)this.z, 0);
    int var15 = (int)IsoUtils.YToScreenExact(var13, var12 + 1, (int)this.z, 0);
                  SpriteRenderer.instance
                     .renderPoly(
                        var14,
                        var15,
                        var14 + 32 * var1,
                        var15 - 16 * var1,
                        var14 + 64 * var1,
                        var15,
                        var14 + 32 * var1,
                        var15 + 16 * var1,
                        1.0F,
                        1.0F,
                        1.0F,
                        0.5F
                     );
               }
            }

    float var16 = 1.0F;
    float var17 = 1.0F;
    float var18 = 1.0F;
            if (this.isExitBlocked(var4)) {
               var18 = 0.0F;
               var17 = 0.0F;
            }

            this.getController().drawCircle(var3.x, var3.y, var7, 0.0F, 0.0F, 1.0F, 1.0F);
            this.getController().drawCircle(var2.x, var2.y, var7, var16, var17, var18, 1.0F);
         }
      }

      TL_vector3f_pool.get().release(var2);
      TL_vector3f_pool.get().release(var3);
   }

    Vector2 areaPositionLocal(Area var1) {
      return this.areaPositionLocal(var1, std::make_unique<Vector2>());
   }

    Vector2 areaPositionLocal(Area var1, Vector2 var2) {
    Vector2 var3 = this.areaPositionWorld(var1, var2);
    Vector3f var4 = (Vector3f)TL_vector3f_pool.get().alloc();
      this.getLocalPos(var3.x, var3.y, 0.0F, var4);
      var3.set(var4.x, var4.z);
      TL_vector3f_pool.get().release(var4);
    return var3;
   }

    Vector2 areaPositionWorld(Area var1) {
      return this.areaPositionWorld(var1, std::make_unique<Vector2>());
   }

    Vector2 areaPositionWorld(Area var1, Vector2 var2) {
      if (var1 == nullptr) {
    return nullptr;
      } else {
    Vector3f var3 = this.getWorldPos(var1.x, 0.0F, var1.y, (Vector3f)TL_vector3f_pool.get().alloc());
         var2.set(var3.x, var3.y);
         TL_vector3f_pool.get().release(var3);
    return var2;
      }
   }

    Vector2 areaPositionWorld4PlayerInteract(Area var1) {
      return this.areaPositionWorld4PlayerInteract(var1, std::make_unique<Vector2>());
   }

    Vector2 areaPositionWorld4PlayerInteract(Area var1, Vector2 var2) {
    Vector3f var3 = this.script.getExtents();
    Vector3f var4 = this.script.getCenterOfMassOffset();
    Vector2 var5 = this.areaPositionWorld(var1, var2);
    Vector3f var6 = this.getLocalPos(var5.x, var5.y, 0.0F, (Vector3f)TL_vector3f_pool.get().alloc());
      if (!(var1.x > var4.x + var3.x / 2.0F) && !(var1.x < var4.x - var3.x / 2.0F)) {
         if (var1.y > 0.0F) {
            var6.z = var6.z - var1.h * 0.3F;
         } else {
            var6.z = var6.z + var1.h * 0.3F;
         }
      } else if (var1.x > 0.0F) {
         var6.x = var6.x - var1.w * 0.3F;
      } else {
         var6.x = var6.x + var1.w * 0.3F;
      }

      this.getWorldPos(var6, var6);
      var2.set(var6.x, var6.y);
      TL_vector3f_pool.get().release(var6);
    return var2;
   }

    void renderAreas() {
      if (this.getScript() != nullptr) {
    Vector3f var1 = this.getForwardVector((Vector3f)TL_vector3f_pool.get().alloc());
    Vector2 var2 = (Vector2)TL_vector2_pool.get().alloc();

         for (int var3 = 0; var3 < this.parts.size(); var3++) {
    VehiclePart var4 = this.parts.get(var3);
            if (var4.getArea() != nullptr) {
    Area var5 = this.getScript().getAreaById(var4.getArea());
               if (var5 != nullptr) {
    Vector2 var6 = this.areaPositionWorld(var5, var2);
                  if (var6 != nullptr) {
    bool var7 = this.isInArea(var5.id, IsoPlayer.getInstance());
                     this.getController()
                        .drawRect(
                           var1,
                           var6.x - WorldSimulation.instance.offsetX,
                           var6.y - WorldSimulation.instance.offsetY,
                           var5.w,
                           var5.h / 2.0F,
                           var7 ? 0.0F : 0.65F,
                           var7 ? 1.0F : 0.65F,
                           var7 ? 1.0F : 0.65F
                        );
                     var6 = this.areaPositionWorld4PlayerInteract(var5, var2);
                     this.getController()
                        .drawRect(var1, var6.x - WorldSimulation.instance.offsetX, var6.y - WorldSimulation.instance.offsetY, 0.1F, 0.1F, 1.0F, 0.0F, 0.0F);
                  }
               }
            }
         }

         TL_vector3f_pool.get().release(var1);
         TL_vector2_pool.get().release(var2);
         LineDrawer.drawLine(
            IsoUtils.XToScreenExact(this.poly.x1, this.poly.y1, 0.0F, 0),
            IsoUtils.YToScreenExact(this.poly.x1, this.poly.y1, 0.0F, 0),
            IsoUtils.XToScreenExact(this.poly.x2, this.poly.y2, 0.0F, 0),
            IsoUtils.YToScreenExact(this.poly.x2, this.poly.y2, 0.0F, 0),
            1.0F,
            0.5F,
            0.5F,
            1.0F,
            0
         );
         LineDrawer.drawLine(
            IsoUtils.XToScreenExact(this.poly.x2, this.poly.y2, 0.0F, 0),
            IsoUtils.YToScreenExact(this.poly.x2, this.poly.y2, 0.0F, 0),
            IsoUtils.XToScreenExact(this.poly.x3, this.poly.y3, 0.0F, 0),
            IsoUtils.YToScreenExact(this.poly.x3, this.poly.y3, 0.0F, 0),
            1.0F,
            0.5F,
            0.5F,
            1.0F,
            0
         );
         LineDrawer.drawLine(
            IsoUtils.XToScreenExact(this.poly.x3, this.poly.y3, 0.0F, 0),
            IsoUtils.YToScreenExact(this.poly.x3, this.poly.y3, 0.0F, 0),
            IsoUtils.XToScreenExact(this.poly.x4, this.poly.y4, 0.0F, 0),
            IsoUtils.YToScreenExact(this.poly.x4, this.poly.y4, 0.0F, 0),
            1.0F,
            0.5F,
            0.5F,
            1.0F,
            0
         );
         LineDrawer.drawLine(
            IsoUtils.XToScreenExact(this.poly.x4, this.poly.y4, 0.0F, 0),
            IsoUtils.YToScreenExact(this.poly.x4, this.poly.y4, 0.0F, 0),
            IsoUtils.XToScreenExact(this.poly.x1, this.poly.y1, 0.0F, 0),
            IsoUtils.YToScreenExact(this.poly.x1, this.poly.y1, 0.0F, 0),
            1.0F,
            0.5F,
            0.5F,
            1.0F,
            0
         );
         LineDrawer.drawLine(
            IsoUtils.XToScreenExact(this.shadowCoord.x1, this.shadowCoord.y1, 0.0F, 0),
            IsoUtils.YToScreenExact(this.shadowCoord.x1, this.shadowCoord.y1, 0.0F, 0),
            IsoUtils.XToScreenExact(this.shadowCoord.x2, this.shadowCoord.y2, 0.0F, 0),
            IsoUtils.YToScreenExact(this.shadowCoord.x2, this.shadowCoord.y2, 0.0F, 0),
            0.5F,
            1.0F,
            0.5F,
            1.0F,
            0
         );
         LineDrawer.drawLine(
            IsoUtils.XToScreenExact(this.shadowCoord.x2, this.shadowCoord.y2, 0.0F, 0),
            IsoUtils.YToScreenExact(this.shadowCoord.x2, this.shadowCoord.y2, 0.0F, 0),
            IsoUtils.XToScreenExact(this.shadowCoord.x3, this.shadowCoord.y3, 0.0F, 0),
            IsoUtils.YToScreenExact(this.shadowCoord.x3, this.shadowCoord.y3, 0.0F, 0),
            0.5F,
            1.0F,
            0.5F,
            1.0F,
            0
         );
         LineDrawer.drawLine(
            IsoUtils.XToScreenExact(this.shadowCoord.x3, this.shadowCoord.y3, 0.0F, 0),
            IsoUtils.YToScreenExact(this.shadowCoord.x3, this.shadowCoord.y3, 0.0F, 0),
            IsoUtils.XToScreenExact(this.shadowCoord.x4, this.shadowCoord.y4, 0.0F, 0),
            IsoUtils.YToScreenExact(this.shadowCoord.x4, this.shadowCoord.y4, 0.0F, 0),
            0.5F,
            1.0F,
            0.5F,
            1.0F,
            0
         );
         LineDrawer.drawLine(
            IsoUtils.XToScreenExact(this.shadowCoord.x4, this.shadowCoord.y4, 0.0F, 0),
            IsoUtils.YToScreenExact(this.shadowCoord.x4, this.shadowCoord.y4, 0.0F, 0),
            IsoUtils.XToScreenExact(this.shadowCoord.x1, this.shadowCoord.y1, 0.0F, 0),
            IsoUtils.YToScreenExact(this.shadowCoord.x1, this.shadowCoord.y1, 0.0F, 0),
            0.5F,
            1.0F,
            0.5F,
            1.0F,
            0
         );
      }
   }

    void renderInterpolateBuffer() {
      if (this.netPlayerAuthorization == Authorization.Remote) {
    float var1 = IsoUtils.XToScreenExact(this.x, this.y, 0.0F, 0);
    float var2 = IsoUtils.YToScreenExact(this.x, this.y, 0.0F, 0);
    float var3 = var1 - 310.0F;
    float var4 = var2 + 22.0F;
    float var5 = 300.0F;
    float var6 = 150.0F;
    float var7 = 4.0F;
    Color var8 = Color.lightGray;
    Color var9 = Color.green;
    Color var10 = Color.cyan;
    Color var11 = Color.yellow;
    Color var12 = Color.blue;
    Color var13 = Color.red;
         LineDrawer.drawLine(var3, var4, var3 + var5, var4, var8.r, var8.g, var8.b, var8.a, 1);
         LineDrawer.drawLine(var3, var4 + var6, var3 + var5, var4 + var6, var8.r, var8.g, var8.b, var8.a, 1);
    long var14 = GameTime.getServerTimeMills();
    long var16 = var14 - 150L - this.interpolation.history;
    long var18 = var14 + 150L;
         this.renderInterpolateBuffer_drawVertLine(var16, var8, var3, var4, var5, var6, var16, var18, true);
         this.renderInterpolateBuffer_drawVertLine(var18, var8, var3, var4, var5, var6, var16, var18, true);
         this.renderInterpolateBuffer_drawVertLine(var14, var9, var3, var4, var5, var6, var16, var18, true);
         this.renderInterpolateBuffer_drawVertLine(var14 - this.interpolation.delay, var10, var3, var4, var5, var6, var16, var18, true);
         this.renderInterpolateBuffer_drawPoint(
            var14 - this.interpolation.delay, this.x, var12, 5, var3, var4, var5, var6, var16, var18, this.x - var7, this.x + var7
         );
         this.renderInterpolateBuffer_drawPoint(
            var14 - this.interpolation.delay, this.y, var13, 5, var3, var4, var5, var6, var16, var18, this.y - var7, this.y + var7
         );
    long var20 = 0L;
    float var22 = float.NaN;
    float var23 = float.NaN;
    VehicleInterpolationData var25 = std::make_shared<VehicleInterpolationData>();
         var25.time = var14 - this.interpolation.delay;
    VehicleInterpolationData var26 = this.interpolation.buffer.higher(var25);
    VehicleInterpolationData var27 = this.interpolation.buffer.floor(var25);

         for (VehicleInterpolationData var29 : this.interpolation.buffer) {
    bool var24 = (var29.hashCode() & 1) == 0;
            this.renderInterpolateBuffer_drawVertLine(var29.time, var11, var3, var4, var5, var6, var16, var18, var24);
            if (var29 == var26) {
               this.renderInterpolateBuffer_drawTextHL(var29.time, "H", var10, var3, var4, var5, var6, var16, var18);
            }

            if (var29 == var27) {
               this.renderInterpolateBuffer_drawTextHL(var29.time, "L", var10, var3, var4, var5, var6, var16, var18);
            }

            this.renderInterpolateBuffer_drawPoint(var29.time, var29.x, var12, 5, var3, var4, var5, var6, var16, var18, this.x - var7, this.x + var7);
            this.renderInterpolateBuffer_drawPoint(var29.time, var29.y, var13, 5, var3, var4, var5, var6, var16, var18, this.y - var7, this.y + var7);
            if (!float.isNaN(var22)) {
               this.renderInterpolateBuffer_drawLine(
                  var20, var22, var29.time, var29.x, var12, var3, var4, var5, var6, var16, var18, this.x - var7, this.x + var7
               );
               this.renderInterpolateBuffer_drawLine(
                  var20, var23, var29.time, var29.y, var13, var3, var4, var5, var6, var16, var18, this.y - var7, this.y + var7
               );
            }

            var20 = var29.time;
            var22 = var29.x;
            var23 = var29.y;
         }

         float[] var31 = new float[27];
         float[] var32 = new float[2];
    bool var30 = this.interpolation.interpolationDataGet(var31, var32, var14 - this.interpolation.delay);
         TextManager.instance
            .DrawString(var3, var4 + var6 + 20.0F, std::string.format("interpolationDataGet=%s", var30 ? "True" : "False"), var10.r, var10.g, var10.b, var10.a);
         TextManager.instance
            .DrawString(
               var3,
               var4 + var6 + 30.0F,
               std::string.format("buffer.size=%d buffering=%s", this.interpolation.buffer.size(), std::string.valueOf(this.interpolation.buffering)),
               var10.r,
               var10.g,
               var10.b,
               var10.a
            );
         if (this.interpolation.buffer.size() >= 2) {
            TextManager.instance
               .DrawString(
                  var3,
                  var4 + var6 + 40.0F,
                  std::string.format(
                     "last=%d first=%d",
                     ((VehicleInterpolationData)this.interpolation.buffer.last()).time,
                     ((VehicleInterpolationData)this.interpolation.buffer.first()).time
                  ),
                  var10.r,
                  var10.g,
                  var10.b,
                  var10.a
               );
            TextManager.instance
               .DrawString(
                  var3,
                  var4 + var6 + 50.0F,
                  std::string.format(
                     "(last-first).time=%d delay=%d",
                     ((VehicleInterpolationData)this.interpolation.buffer.last()).time - ((VehicleInterpolationData)this.interpolation.buffer.first()).time,
                     this.interpolation.delay
                  ),
                  var10.r,
                  var10.g,
                  var10.b,
                  var10.a
               );
         }
      }
   }

    void renderInterpolateBuffer_drawTextHL(long var1, const std::string& var3, Color var4, float var5, float var6, float var7, float var8, long var9, long var11) {
    float var13 = var7 / (float)(var11 - var9);
    float var14 = (float)(var1 - var9) * var13;
      TextManager.instance.DrawString(var14 + var5, var6, var3, var4.r, var4.g, var4.b, var4.a);
   }

   private void renderInterpolateBuffer_drawVertLine(
      long var1, Color var3, float var4, float var5, float var6, float var7, long var8, long var10, boolean var12
   ) {
    float var13 = var6 / (float)(var10 - var8);
    float var14 = (float)(var1 - var8) * var13;
      LineDrawer.drawLine(var14 + var4, var5, var14 + var4, var5 + var7, var3.r, var3.g, var3.b, var3.a, 1);
      TextManager.instance
         .DrawString(
            var14 + var4,
            var5 + var7 + (var12 ? 0.0F : 10.0F),
            std::string.format("%.1f", (float)(var1 - var1 / 100000L * 100000L) / 1000.0F),
            var3.r,
            var3.g,
            var3.b,
            var3.a
         );
   }

   private void renderInterpolateBuffer_drawLine(
      long var1,
      float var3,
      long var4,
      float var6,
      Color var7,
      float var8,
      float var9,
      float var10,
      float var11,
      long var12,
      long var14,
      float var16,
      float var17
   ) {
    float var18 = var10 / (float)(var14 - var12);
    float var19 = (float)(var1 - var12) * var18;
    float var20 = (float)(var4 - var12) * var18;
    float var21 = var11 / (var17 - var16);
    float var22 = (var3 - var16) * var21;
    float var23 = (var6 - var16) * var21;
      LineDrawer.drawLine(var19 + var8, var22 + var9, var20 + var8, var23 + var9, var7.r, var7.g, var7.b, var7.a, 1);
   }

   private void renderInterpolateBuffer_drawPoint(
      long var1, float var3, Color var4, int var5, float var6, float var7, float var8, float var9, long var10, long var12, float var14, float var15
   ) {
    float var16 = var8 / (float)(var12 - var10);
    float var17 = (float)(var1 - var10) * var16;
    float var18 = var9 / (var15 - var14);
    float var19 = (var3 - var14) * var18;
      LineDrawer.drawCircle(var17 + var6, var19 + var7, var5, 10, var4.r, var4.g, var4.b);
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    void renderAuthorizations() {
    float var1 = 0.3F;
    float var2 = 0.3F;
    float var3 = 0.3F;
    float var4 = 0.5F;
      switch (1.$SwitchMap$zombie$vehicles$BaseVehicle$Authorization[this.netPlayerAuthorization.ordinal()]) {
         case 1:
            var1 = 1.0F;
            break;
         case 2:
            var3 = 1.0F;
            break;
         case 3:
            var2 = 1.0F;
            break;
         case 4:
            var2 = 1.0F;
            var1 = 1.0F;
            break;
         case 5:
            var3 = 1.0F;
            var1 = 1.0F;
      }

      LineDrawer.drawLine(
         IsoUtils.XToScreenExact(this.poly.x1, this.poly.y1, 0.0F, 0),
         IsoUtils.YToScreenExact(this.poly.x1, this.poly.y1, 0.0F, 0),
         IsoUtils.XToScreenExact(this.poly.x2, this.poly.y2, 0.0F, 0),
         IsoUtils.YToScreenExact(this.poly.x2, this.poly.y2, 0.0F, 0),
         var1,
         var2,
         var3,
         var4,
         1
      );
      LineDrawer.drawLine(
         IsoUtils.XToScreenExact(this.poly.x2, this.poly.y2, 0.0F, 0),
         IsoUtils.YToScreenExact(this.poly.x2, this.poly.y2, 0.0F, 0),
         IsoUtils.XToScreenExact(this.poly.x3, this.poly.y3, 0.0F, 0),
         IsoUtils.YToScreenExact(this.poly.x3, this.poly.y3, 0.0F, 0),
         var1,
         var2,
         var3,
         var4,
         1
      );
      LineDrawer.drawLine(
         IsoUtils.XToScreenExact(this.poly.x3, this.poly.y3, 0.0F, 0),
         IsoUtils.YToScreenExact(this.poly.x3, this.poly.y3, 0.0F, 0),
         IsoUtils.XToScreenExact(this.poly.x4, this.poly.y4, 0.0F, 0),
         IsoUtils.YToScreenExact(this.poly.x4, this.poly.y4, 0.0F, 0),
         var1,
         var2,
         var3,
         var4,
         1
      );
      LineDrawer.drawLine(
         IsoUtils.XToScreenExact(this.poly.x4, this.poly.y4, 0.0F, 0),
         IsoUtils.YToScreenExact(this.poly.x4, this.poly.y4, 0.0F, 0),
         IsoUtils.XToScreenExact(this.poly.x1, this.poly.y1, 0.0F, 0),
         IsoUtils.YToScreenExact(this.poly.x1, this.poly.y1, 0.0F, 0),
         var1,
         var2,
         var3,
         var4,
         1
      );
    float var5 = 0.0F;
      if (this.getVehicleTowing() != nullptr) {
    Vector3fObjectPool var6 = TL_vector3f_pool.get();
    Vector3f var7 = (Vector3f)var6.alloc();
    Vector3f var8 = this.getTowingWorldPos(this.getTowAttachmentSelf(), var7);
    Vector3f var9 = (Vector3f)var6.alloc();
    Vector3f var10 = this.getVehicleTowing().getTowingWorldPos(this.getVehicleTowing().getTowAttachmentSelf(), var9);
         if (var8 != nullptr && var10 != nullptr) {
            LineDrawer.DrawIsoLine(var8.x, var8.y, var8.z, var10.x, var10.y, var10.z, var1, var2, var3, var4, 1);
            LineDrawer.DrawIsoCircle(var8.x, var8.y, var8.z, 0.2F, 16, var1, var2, var3, var4);
            var5 = IsoUtils.DistanceTo(var8.x, var8.y, var8.z, var10.x, var10.y, var10.z);
         }

         var6.release(var7);
         var6.release(var9);
      }

      var1 = 1.0F;
      var2 = 1.0F;
      var3 = 0.75F;
      var4 = 1.0F;
    float var15 = 10.0F;
    float var28 = IsoUtils.XToScreenExact(this.x, this.y, 0.0F, 0);
    float var29 = IsoUtils.YToScreenExact(this.x, this.y, 0.0F, 0);
    IsoPlayer var30 = (IsoPlayer)GameClient.IDToPlayerMap.get(this.netPlayerId);
    std::string var31 = (var30 == nullptr ? "@server" : var30.getUsername()) + " ( " + this.netPlayerId + " )";
    float var16;
      TextManager.instance
         .DrawString(var28, var29 + (var16 = var15 + 12.0F), "VID: " + this.getScriptName() + " ( " + this.getId() + " )", var1, var2, var3, var4);
      TextManager.instance.DrawString(var28, var29 + (var15 = var16 + 12.0F), "PID: " + var31, var1, var2, var3, var4);
    float var18;
      TextManager.instance.DrawString(var28, var29 + (var18 = var15 + 12.0F), "Auth: " + this.netPlayerAuthorization.name(), var1, var2, var3, var4);
      TextManager.instance.DrawString(var28, var29 + (var15 = var18 + 12.0F), "Static/active: " + this.isStatic + "/" + this.isActive, var1, var2, var3, var4);
    float var20;
      TextManager.instance.DrawString(var28, var29 + (var20 = var15 + 12.0F), "x=" + this.x + " / y=" + this.y, var1, var2, var3, var4);
      TextManager.instance
         .DrawString(
            var28,
            var29 + (var15 = var20 + 14.0F),
            std::string.format("Passengers: %d/%d", Arrays.stream(this.passengers).filter(var0 -> var0.character != nullptr).count(), this.passengers.length),
            var1,
            var2,
            var3,
            var4
         );
    float var22;
      TextManager.instance
         .DrawString(
            var28,
            var29 + (var22 = var15 + 12.0F),
            std::string.format("Speed: %s%.3f kmph", this.getCurrentSpeedKmHour() >= 0.0F ? "+" : "", this.getCurrentSpeedKmHour()),
            var1,
            var2,
            var3,
            var4
         );
      TextManager.instance.DrawString(var28, var29 + (var15 = var22 + 12.0F), std::string.format("Engine speed: %.3f", this.engineSpeed), var1, var2, var3, var4);
    float var24;
      TextManager.instance
         .DrawString(var28, var29 + (var24 = var15 + 12.0F), std::string.format("Mass: %.3f/%.3f", this.getMass(), this.getFudgedMass()), var1, var2, var3, var4);
      if (var5 > 1.5F) {
         var2 = 0.75F;
      }

      if (this.getVehicleTowing() != nullptr) {
         TextManager.instance.DrawString(var28, var29 + (var15 = var24 + 14.0F), "Towing: " + this.getVehicleTowing().getId(), var1, var2, var3, var4);
         TextManager.instance.DrawString(var28, var29 + (var24 = var15 + 12.0F), std::string.format("Distance: %.3f", var5), var1, var2, var3, var4);
      }

      if (this.getVehicleTowedBy() != nullptr) {
         TextManager.instance.DrawString(var28, var29 + (var15 = var24 + 14.0F), "TowedBy: " + this.getVehicleTowedBy().getId(), var1, var2, var3, var4);
    float var27;
         TextManager.instance.DrawString(var28, var29 + (var27 = var15 + 12.0F), std::string.format("Distance: %.3f", var5), var1, var2, var3, var4);
      }
   }

    void renderUsableArea() {
      if (this.getScript() != nullptr && UIManager.VisibleAllUI) {
    VehiclePart var1 = this.getUseablePart(IsoPlayer.getInstance());
         if (var1 != nullptr) {
    Area var2 = this.getScript().getAreaById(var1.getArea());
            if (var2 != nullptr) {
    Vector2 var3 = (Vector2)TL_vector2_pool.get().alloc();
    Vector2 var4 = this.areaPositionWorld(var2, var3);
               if (var4 == nullptr) {
                  TL_vector2_pool.get().release(var3);
               } else {
    Vector3f var5 = this.getForwardVector((Vector3f)TL_vector3f_pool.get().alloc());
    float var6 = Core.getInstance().getGoodHighlitedColor().getR();
    float var7 = Core.getInstance().getGoodHighlitedColor().getG();
    float var8 = Core.getInstance().getGoodHighlitedColor().getB();
                  this.getController()
                     .drawRect(
                        var5, var4.x - WorldSimulation.instance.offsetX, var4.y - WorldSimulation.instance.offsetY, var2.w, var2.h / 2.0F, var6, var7, var8
                     );
                  var5.x = var5.x * (var2.h / this.script.getModelScale());
                  var5.z = var5.z * (var2.h / this.script.getModelScale());
                  if (var1.getDoor() != nullptr && (var1.getId().contains("Left") || var1.getId().contains("Right"))) {
                     if (var1.getId().contains("Front")) {
                        this.getController()
                           .drawRect(
                              var5,
                              var4.x - WorldSimulation.instance.offsetX + var5.x * var2.h / 2.0F,
                              var4.y - WorldSimulation.instance.offsetY + var5.z * var2.h / 2.0F,
                              var2.w,
                              var2.h / 8.0F,
                              var6,
                              var7,
                              var8
                           );
                     } else if (var1.getId().contains("Rear")) {
                        this.getController()
                           .drawRect(
                              var5,
                              var4.x - WorldSimulation.instance.offsetX - var5.x * var2.h / 2.0F,
                              var4.y - WorldSimulation.instance.offsetY - var5.z * var2.h / 2.0F,
                              var2.w,
                              var2.h / 8.0F,
                              var6,
                              var7,
                              var8
                           );
                     }
                  }

                  TL_vector2_pool.get().release(var3);
                  TL_vector3f_pool.get().release(var5);
               }
            }
         }
      }
   }

    void renderIntersectedSquares() {
    VehiclePoly var1 = this.getPoly();
    float var2 = Math.min(var1.x1, Math.min(var1.x2, Math.min(var1.x3, var1.x4)));
    float var3 = Math.min(var1.y1, Math.min(var1.y2, Math.min(var1.y3, var1.y4)));
    float var4 = Math.max(var1.x1, Math.max(var1.x2, Math.max(var1.x3, var1.x4)));
    float var5 = Math.max(var1.y1, Math.max(var1.y2, Math.max(var1.y3, var1.y4)));

      for (int var6 = (int)var3; var6 < (int)Math.ceil(var5); var6++) {
         for (int var7 = (int)var2; var7 < (int)Math.ceil(var4); var7++) {
            if (this.isIntersectingSquare(var7, var6, (int)this.z)) {
               LineDrawer.addLine(var7, var6, (int)this.z, var7 + 1, var6 + 1, (int)this.z, 1.0F, 1.0F, 1.0F, nullptr, false);
            }
         }
      }
   }

    void renderTrailerPositions() {
      if (this.script != nullptr && this.physics != nullptr) {
    Vector3f var1 = (Vector3f)TL_vector3f_pool.get().alloc();
    Vector3f var2 = (Vector3f)TL_vector3f_pool.get().alloc();
    Vector3f var3 = this.getTowingWorldPos("trailer", var2);
         if (var3 != nullptr) {
            this.physics.drawCircle(var3.x, var3.y, 0.3F, 1.0F, 1.0F, 1.0F, 1.0F);
         }

    Vector3f var4 = this.getPlayerTrailerLocalPos("trailer", false, var1);
         if (var4 != nullptr) {
            this.getWorldPos(var4, var4);
    bool var5 = PolygonalMap2.instance.lineClearCollide(var2.x, var2.y, var4.x, var4.y, (int)this.z, this, false, false);
            this.physics.drawCircle(var4.x, var4.y, 0.3F, 1.0F, var5 ? 0.0F : 1.0F, var5 ? 0.0F : 1.0F, 1.0F);
            if (var5) {
               LineDrawer.addLine(var4.x, var4.y, 0.0F, var2.x, var2.y, 0.0F, 1.0F, 0.0F, 0.0F, 1.0F);
            }
         }

         var4 = this.getPlayerTrailerLocalPos("trailer", true, var1);
         if (var4 != nullptr) {
            this.getWorldPos(var4, var4);
    bool var7 = PolygonalMap2.instance.lineClearCollide(var2.x, var2.y, var4.x, var4.y, (int)this.z, this, false, false);
            this.physics.drawCircle(var4.x, var4.y, 0.3F, 1.0F, var7 ? 0.0F : 1.0F, var7 ? 0.0F : 1.0F, 1.0F);
            if (var7) {
               LineDrawer.addLine(var4.x, var4.y, 0.0F, var2.x, var2.y, 0.0F, 1.0F, 0.0F, 0.0F, 1.0F);
            }
         }

         TL_vector3f_pool.get().release(var1);
         TL_vector3f_pool.get().release(var2);
      }
   }

    void getWheelForwardVector(int var1, Vector3f var2) {
    WheelInfo var3 = this.wheelInfo[var1];
    Matrix4f var4 = (Matrix4f)TL_matrix4f_pool.get().alloc();
      var4.rotationY(var3.steering);
    Matrix4f var5 = this.jniTransform.getMatrix((Matrix4f)TL_matrix4f_pool.get().alloc());
      var5.setTranslation(0.0F, 0.0F, 0.0F);
      var4.mul(var5, var4);
      TL_matrix4f_pool.get().release(var5);
      TL_matrix4f_pool.get().release(var4);
      var4.getColumn(2, this.tempVector4f);
      var2.set(this.tempVector4f.x, 0.0F, this.tempVector4f.z);
   }

    void tryStartEngine(bool var1) {
      if (this.getDriver() == nullptr || !(this.getDriver() instanceof IsoPlayer) || !((IsoPlayer)this.getDriver()).isBlockMovement()) {
         if (this.engineState == engineStateTypes.Idle) {
            if ((!Core.bDebug || !DebugOptions.instance.CheatVehicleStartWithoutKey.getValue())
               && !SandboxOptions.instance.VehicleEasyUse.getValue()
               && !this.isKeysInIgnition()
               && !var1
               && this.getDriver().getInventory().haveThisKeyId(this.getKeyId()) == nullptr
               && !this.isHotwired()) {
               if (GameServer.bServer) {
                  this.getDriver().sendObjectChange("vehicleNoKey");
               } else {
                  this.getDriver().SayDebug(" [img=media/ui/CarKey_none.png]");
               }
            } else {
               this.engineDoStarting();
            }
         }
      }
   }

    void tryStartEngine() {
      this.tryStartEngine(false);
   }

    void engineDoIdle() {
      this.engineState = engineStateTypes.Idle;
      this.engineLastUpdateStateTime = System.currentTimeMillis();
      this.transmitEngine();
   }

    void engineDoStarting() {
      this.engineState = engineStateTypes.Starting;
      this.engineLastUpdateStateTime = System.currentTimeMillis();
      this.transmitEngine();
      this.setKeysInIgnition(true);
   }

    bool isStarting() {
      return this.engineState == engineStateTypes.Starting
         || this.engineState == engineStateTypes.StartingFailed
         || this.engineState == engineStateTypes.StartingSuccess
         || this.engineState == engineStateTypes.StartingFailedNoPower;
   }

    std::string getEngineSound() {
      return this.getScript() != nullptr && this.getScript().getSounds().engine != nullptr ? this.getScript().getSounds().engine : "VehicleEngineDefault";
   }

    std::string getEngineStartSound() {
      return this.getScript() != nullptr && this.getScript().getSounds().engineStart != nullptr ? this.getScript().getSounds().engineStart : "VehicleStarted";
   }

    std::string getEngineTurnOffSound() {
      return this.getScript() != nullptr && this.getScript().getSounds().engineTurnOff != nullptr ? this.getScript().getSounds().engineTurnOff : "VehicleTurnedOff";
   }

    std::string getIgnitionFailSound() {
      return this.getScript() != nullptr && this.getScript().getSounds().ignitionFail != nullptr
         ? this.getScript().getSounds().ignitionFail
         : "VehicleFailingToStart";
   }

    std::string getIgnitionFailNoPowerSound() {
      return this.getScript() != nullptr && this.getScript().getSounds().ignitionFailNoPower != nullptr
         ? this.getScript().getSounds().ignitionFailNoPower
         : "VehicleFailingToStartNoPower";
   }

    void engineDoRetryingStarting() {
      this.getEmitter().stopSoundByName(this.getIgnitionFailSound());
      this.getEmitter().playSoundImpl(this.getIgnitionFailSound(), (IsoObject)nullptr);
      this.engineState = engineStateTypes.RetryingStarting;
      this.engineLastUpdateStateTime = System.currentTimeMillis();
      this.transmitEngine();
   }

    void engineDoStartingSuccess() {
      this.getEmitter().stopSoundByName(this.getIgnitionFailSound());
      this.engineState = engineStateTypes.StartingSuccess;
      this.engineLastUpdateStateTime = System.currentTimeMillis();
      if (this.getEngineStartSound() == this.getEngineSound())) {
         if (!this.getEmitter().isPlaying(this.combinedEngineSound)) {
            this.combinedEngineSound = this.emitter.playSoundImpl(this.getEngineSound(), (IsoObject)nullptr);
         }
      } else {
         this.getEmitter().playSoundImpl(this.getEngineStartSound(), (IsoObject)nullptr);
      }

      this.transmitEngine();
      this.setKeysInIgnition(true);
   }

    void engineDoStartingFailed() {
      this.getEmitter().stopSoundByName(this.getIgnitionFailSound());
      this.getEmitter().playSoundImpl(this.getIgnitionFailSound(), (IsoObject)nullptr);
      this.stopEngineSounds();
      this.engineState = engineStateTypes.StartingFailed;
      this.engineLastUpdateStateTime = System.currentTimeMillis();
      this.transmitEngine();
   }

    void engineDoStartingFailedNoPower() {
      this.getEmitter().stopSoundByName(this.getIgnitionFailNoPowerSound());
      this.getEmitter().playSoundImpl(this.getIgnitionFailNoPowerSound(), (IsoObject)nullptr);
      this.stopEngineSounds();
      this.engineState = engineStateTypes.StartingFailedNoPower;
      this.engineLastUpdateStateTime = System.currentTimeMillis();
      this.transmitEngine();
   }

    void engineDoRunning() {
      this.setNeedPartsUpdate(true);
      this.engineState = engineStateTypes.Running;
      this.engineLastUpdateStateTime = System.currentTimeMillis();
      this.transmitEngine();
   }

    void engineDoStalling() {
      this.getEmitter().playSoundImpl("VehicleRunningOutOfGas", (IsoObject)nullptr);
      this.engineState = engineStateTypes.Stalling;
      this.engineLastUpdateStateTime = System.currentTimeMillis();
      this.stopEngineSounds();
      this.engineSoundIndex = 0;
      this.transmitEngine();
      if (!Core.getInstance().getOptionLeaveKeyInIgnition()) {
         this.setKeysInIgnition(false);
      }
   }

    void engineDoShuttingDown() {
      if (!this.getEngineTurnOffSound() == this.getEngineSound())) {
         this.getEmitter().playSoundImpl(this.getEngineTurnOffSound(), (IsoObject)nullptr);
      }

      this.stopEngineSounds();
      this.engineSoundIndex = 0;
      this.engineState = engineStateTypes.ShutingDown;
      this.engineLastUpdateStateTime = System.currentTimeMillis();
      this.transmitEngine();
      if (!Core.getInstance().getOptionLeaveKeyInIgnition()) {
         this.setKeysInIgnition(false);
      }

    VehiclePart var1 = this.getHeater();
      if (var1 != nullptr) {
         var1.getModData().rawset("active", false);
      }
   }

    void shutOff() {
      if (this.getPartById("GasTank").getContainerContentAmount() == 0.0F) {
         this.engineDoStalling();
      } else {
         this.engineDoShuttingDown();
      }
   }

    void resumeRunningAfterLoad() {
      if (GameClient.bClient) {
    IsoGameCharacter var1 = this.getDriver();
         if (var1 != nullptr) {
    bool var2 = this.getDriver().getInventory().haveThisKeyId(this.getKeyId()) != nullptr ? bool.TRUE : bool.FALSE;
            GameClient.instance.sendClientCommandV((IsoPlayer)this.getDriver(), "vehicle", "startEngine", new Object[]{"haveKey", var2});
         }
      } else if (this.isEngineWorking()) {
         this.getEmitter();
         this.engineDoStartingSuccess();
      }
   }

    bool isEngineStarted() {
      return this.engineState == engineStateTypes.Starting
         || this.engineState == engineStateTypes.StartingFailed
         || this.engineState == engineStateTypes.StartingSuccess
         || this.engineState == engineStateTypes.RetryingStarting;
   }

    bool isEngineRunning() {
      return this.engineState == engineStateTypes.Running;
   }

    bool isEngineWorking() {
      for (int var1 = 0; var1 < this.parts.size(); var1++) {
    VehiclePart var2 = this.parts.get(var1);
    std::string var3 = var2.getLuaFunction("checkEngine");
         if (var3 != nullptr && !bool.TRUE == this.callLuaBoolean(var3, this, var2))) {
    return false;
         }
      }

    return true;
   }

    bool isOperational() {
      for (int var1 = 0; var1 < this.parts.size(); var1++) {
    VehiclePart var2 = this.parts.get(var1);
    std::string var3 = var2.getLuaFunction("checkOperate");
         if (var3 != nullptr && !bool.TRUE == this.callLuaBoolean(var3, this, var2))) {
    return false;
         }
      }

    return true;
   }

    bool isDriveable() {
      return !this.isEngineWorking() ? false : this.isOperational();
   }

    BaseSoundEmitter getEmitter() {
      if (this.emitter == nullptr) {
         if (!Core.SoundDisabled && !GameServer.bServer) {
#if defined(__SWITCH__) || defined(NINTENDO_SWITCH)
            auto var1 = std::make_shared<audio::SDL2SoundEmitter>();
#else
            auto var1 = std::make_shared<OpenALSoundEmitter>();
#endif
            var1->parameterUpdater = this;
            this.emitter = var1;
         } else {
            this.emitter = std::make_unique<DummySoundEmitter>();
         }
      }
      return this.emitter;
   }

    long playSoundImpl(const std::string& var1, IsoObject var2) {
      return this.getEmitter().playSoundImpl(var1, var2);
   }

    int stopSound(long var1) {
      return this.getEmitter().stopSound(var1);
   }

    void playSound(const std::string& var1) {
      this.getEmitter().playSound(var1);
   }

    void updateSounds() {
      if (!GameServer.bServer) {
         if (this.getBatteryCharge() > 0.0F) {
            if (this.lightbarSirenMode.isEnable() && this.soundSirenSignal == -1L) {
               this.setLightbarSirenMode(this.lightbarSirenMode.get());
            }
         } else if (this.soundSirenSignal != -1L) {
            this.getEmitter().stopSound(this.soundSirenSignal);
            this.soundSirenSignal = -1L;
         }
      }

    IsoPlayer var1 = nullptr;
    float var2 = float.MAX_VALUE;

      for (int var3 = 0; var3 < IsoPlayer.numPlayers; var3++) {
    IsoPlayer var4 = IsoPlayer.players[var3];
         if (var4 != nullptr && var4.getCurrentSquare() != nullptr) {
    float var5 = var4.getX();
    float var6 = var4.getY();
    float var7 = IsoUtils.DistanceToSquared(var5, var6, this.x, this.y);
            if (var4.Traits.HardOfHearing.isSet()) {
               var7 *= 4.5F;
            }

            if (var4.Traits.Deaf.isSet()) {
               var7 = float.MAX_VALUE;
            }

            if (var7 < var2) {
               var1 = var4;
               var2 = var7;
            }
         }
      }

      if (var1 == nullptr) {
         if (this.emitter != nullptr) {
            this.emitter.setPos(this.x, this.y, this.z);
            if (!this.emitter.empty()) {
               this.emitter.tick();
            }
         }
      } else {
         if (!GameServer.bServer) {
    float var8 = ClimateManager.getInstance().isRaining() ? ClimateManager.getInstance().getPrecipitationIntensity() : 0.0F;
            if (this.getSquare() != nullptr && this.getSquare().isInARoom()) {
               var8 = 0.0F;
            }

            if (this.getEmitter().isPlaying("VehicleAmbiance")) {
               if (var8 == 0.0F) {
                  this.getEmitter().stopOrTriggerSoundByName("VehicleAmbiance");
               }
            } else if (var8 > 0.0F && var2 < 100.0F) {
               this.emitter.playAmbientLoopedImpl("VehicleAmbiance");
            }

    float var10 = var2;
            if (var2 > 1200.0F) {
               this.stopEngineSounds();
               if (this.emitter != nullptr && !this.emitter.empty()) {
                  this.emitter.setPos(this.x, this.y, this.z);
                  this.emitter.tick();
               }

               return;
            }

            for (int var12 = 0; var12 < this.new_EngineSoundId.length; var12++) {
               if (this.new_EngineSoundId[var12] != 0L) {
                  this.getEmitter().setVolume(this.new_EngineSoundId[var12], 1.0F - var10 / 1200.0F);
               }
            }
         }

         this.startTime = this.startTime - GameTime.instance.getMultiplier();
         if (this.getController() != nullptr) {
            if (!GameServer.bServer) {
               if (this.emitter == nullptr) {
                  if (this.engineState != engineStateTypes.Running) {
                     return;
                  }

                  this.getEmitter();
               }

    bool var9 = this.isAnyListenerInside();
    float var11 = Math.abs(this.getCurrentSpeedKmHour());
               if (this.startTime <= 0.0F && this.engineState == engineStateTypes.Running && !this.getEmitter().isPlaying(this.combinedEngineSound)) {
                  this.combinedEngineSound = this.emitter.playSoundImpl(this.getEngineSound(), (IsoObject)nullptr);
                  if (this.getEngineSound() == this.getEngineStartSound())) {
                     this.emitter.setTimelinePosition(this.combinedEngineSound, "idle");
                  }
               }

    bool var13 = false;
               if (!GameClient.bClient || this.isLocalPhysicSim()) {
                  for (int var14 = 0; var14 < this.script.getWheelCount(); var14++) {
                     if (this.wheelInfo[var14].skidInfo < 0.15F) {
                        var13 = true;
                        break;
                     }
                  }
               }

               if (this.getDriver() == nullptr) {
                  var13 = false;
               }

               if (var13 != this.skidding) {
                  if (var13) {
                     this.skidSound = this.getEmitter().playSoundImpl("VehicleSkid", (IsoObject)nullptr);
                  } else if (this.skidSound != 0L) {
                     this.emitter.stopSound(this.skidSound);
                     this.skidSound = 0L;
                  }

                  this.skidding = var13;
               }

               if (this.soundBackMoveSignal != -1L && this.emitter != nullptr) {
                  this.emitter.set3D(this.soundBackMoveSignal, !var9);
               }

               if (this.soundHorn != -1L && this.emitter != nullptr) {
                  this.emitter.set3D(this.soundHorn, !var9);
               }

               if (this.soundSirenSignal != -1L && this.emitter != nullptr) {
                  this.emitter.set3D(this.soundSirenSignal, !var9);
               }

               if (this.emitter != nullptr && (this.engineState != engineStateTypes.Idle || !this.emitter.empty())) {
                  this.getVehicleParameters().update();
                  this.emitter.setPos(this.x, this.y, this.z);
                  this.emitter.tick();
               }
            }
         }
      }
   }

    bool updatePart(VehiclePart var1) {
      var1.updateSignalDevice();
    VehicleLight var2 = var1.getLight();
      if (var2 != nullptr && var1.getId().contains("Headlight")) {
         var1.setLightActive(this.getHeadlightsOn() && var1.getInventoryItem() != nullptr && this.getBatteryCharge() > 0.0F);
      }

    std::string var3 = var1.getLuaFunction("update");
      if (var3 == nullptr) {
    return false;
      } else {
    float var4 = (float)GameTime.getInstance().getWorldAgeHours();
         if (var1.getLastUpdated() < 0.0F) {
            var1.setLastUpdated(var4);
         } else if (var1.getLastUpdated() > var4) {
            var1.setLastUpdated(var4);
         }

    float var5 = var4 - var1.getLastUpdated();
         if ((int)(var5 * 60.0F) > 0) {
            var1.setLastUpdated(var4);
            this.callLuaVoid(var3, this, var1, (double)(var5 * 60.0F));
    return true;
         } else {
    return false;
         }
      }
   }

    void updateParts() {
      if (!GameClient.bClient) {
    bool var4 = false;

         for (int var5 = 0; var5 < this.getPartCount(); var5++) {
    VehiclePart var3 = this.getPartByIndex(var5);
            if (this.updatePart(var3) && !var4) {
               var4 = true;
            }

            if (var5 == this.getPartCount() - 1 && var4) {
               this.brakeBetweenUpdatesSpeed = 0.0F;
            }
         }
      } else {
         for (int var1 = 0; var1 < this.getPartCount(); var1++) {
    VehiclePart var2 = this.getPartByIndex(var1);
            var2.updateSignalDevice();
         }
      }
   }

    void drainBatteryUpdateHack() {
    bool var1 = this.isEngineRunning();
      if (!var1) {
         for (int var2 = 0; var2 < this.parts.size(); var2++) {
    VehiclePart var3 = this.parts.get(var2);
            if (var3.getDeviceData() != nullptr && var3.getDeviceData().getIsTurnedOn()) {
               this.updatePart(var3);
            } else if (var3.getLight() != nullptr && var3.getLight().getActive()) {
               this.updatePart(var3);
            }
         }

         if (this.hasLightbar() && (this.lightbarLightsMode.isEnable() || this.lightbarSirenMode.isEnable()) && this.getBattery() != nullptr) {
            this.updatePart(this.getBattery());
         }
      }
   }

    bool getHeadlightsOn() {
      return this.headlightsOn;
   }

    void setHeadlightsOn(bool var1) {
      if (this.headlightsOn != var1) {
         this.headlightsOn = var1;
         if (GameServer.bServer) {
            this.updateFlags = (short)(this.updateFlags | 8);
         } else {
            this.playSound(this.headlightsOn ? "VehicleHeadlightsOn" : "VehicleHeadlightsOff");
         }
      }
   }

    bool getWindowLightsOn() {
      return this.windowLightsOn;
   }

    void setWindowLightsOn(bool var1) {
      this.windowLightsOn = var1;
   }

    bool getHeadlightCanEmmitLight() {
      if (this.getBatteryCharge() <= 0.0F) {
    return false;
      } else {
    VehiclePart var1 = this.getPartById("HeadlightLeft");
         if (var1 != nullptr && var1.getInventoryItem() != nullptr) {
    return true;
         } else {
            var1 = this.getPartById("HeadlightRight");
            return var1 != nullptr && var1.getInventoryItem() != nullptr;
         }
      }
   }

    bool getStoplightsOn() {
      return this.stoplightsOn;
   }

    void setStoplightsOn(bool var1) {
      if (this.stoplightsOn != var1) {
         this.stoplightsOn = var1;
         if (GameServer.bServer) {
            this.updateFlags = (short)(this.updateFlags | 8);
         }
      }
   }

    bool hasHeadlights() {
      return this.getLightCount() > 0;
   }

    void addToWorld() {
      if (this.addedToWorld) {
         DebugLog.General.error("added vehicle twice " + this + " id=" + this.VehicleID);
      } else {
         VehiclesDB2.instance.setVehicleLoaded(this);
         this.addedToWorld = true;
         this.removedFromWorld = false;
         super.addToWorld();
         this.createPhysics();

         for (int var1 = 0; var1 < this.parts.size(); var1++) {
    VehiclePart var2 = this.parts.get(var1);
            if (var2.getItemContainer() != nullptr) {
               var2.getItemContainer().addItemsToProcessItems();
            }

            if (var2.getDeviceData() != nullptr && !GameServer.bServer) {
               ZomboidRadio.getInstance().RegisterDevice(var2);
            }
         }

         if (this.lightbarSirenMode.isEnable()) {
            this.setLightbarSirenMode(this.lightbarSirenMode.get());
            if (this.sirenStartTime <= 0.0) {
               this.sirenStartTime = GameTime.instance.getWorldAgeHours();
            }
         }

         if (this.chunk != nullptr && this.chunk.jobType != JobType.SoftReset) {
            PolygonalMap2.instance.addVehicleToWorld(this);
         }

         if (this.engineState != engineStateTypes.Idle) {
            this.engineSpeed = this.getScript() == nullptr ? 1000.0 : this.getScript().getEngineIdleSpeed();
         }

         if (this.chunk != nullptr && this.chunk.jobType != JobType.SoftReset) {
            this.trySpawnKey();
         }

         if (this.emitter != nullptr) {
            SoundManager.instance.registerEmitter(this.emitter);
         }
      }
   }

    void removeFromWorld() {
      this.breakConstraint(false, false);
      VehiclesDB2.instance.setVehicleUnloaded(this);

      for (int var1 = 0; var1 < this.passengers.length; var1++) {
         if (this.getPassenger(var1).character != nullptr) {
            for (int var2 = 0; var2 < 4; var2++) {
               if (this.getPassenger(var1).character == IsoPlayer.players[var2]) {
                  return;
               }
            }
         }
      }

      IsoChunk.removeFromCheckedVehicles(this);
      DebugLog.Vehicle.trace("BaseVehicle.removeFromWorld() %s id=%d", this, this.VehicleID);
      if (!this.removedFromWorld) {
         if (!this.addedToWorld) {
            DebugLog.Vehicle.debugln("ERROR: removing vehicle but addedToWorld=false %s id=%d", this, this.VehicleID);
         }

         this.removedFromWorld = true;
         this.addedToWorld = false;

         for (int var3 = 0; var3 < this.parts.size(); var3++) {
    VehiclePart var4 = this.parts.get(var3);
            if (var4.getItemContainer() != nullptr) {
               var4.getItemContainer().removeItemsFromProcessItems();
            }

            if (var4.getDeviceData() != nullptr && !GameServer.bServer) {
               ZomboidRadio.getInstance().UnRegisterDevice(var4);
            }
         }

         if (this.emitter != nullptr) {
            this.emitter.stopAll();
            SoundManager.instance.unregisterEmitter(this.emitter);
            this.emitter = nullptr;
         }

         if (this.hornemitter != nullptr && this.soundHorn != -1L) {
            this.hornemitter.stopAll();
            this.soundHorn = -1L;
         }

         if (this.createdModel) {
            ModelManager.instance.Remove(this);
            this.createdModel = false;
         }

         this.releaseAnimationPlayers();
         if (this.getController() != nullptr) {
            if (!GameServer.bServer) {
               Bullet.removeVehicle(this.VehicleID);
            }

            this.physics = nullptr;
         }

         if (GameServer.bServer || GameClient.bClient) {
            VehicleManager.instance.removeFromWorld(this);
         } else if (this.VehicleID != -1) {
            VehicleIDMap.instance.remove(this.VehicleID);
         }

         IsoWorld.instance.CurrentCell.addVehicles.remove(this);
         IsoWorld.instance.CurrentCell.vehicles.remove(this);
         PolygonalMap2.instance.removeVehicleFromWorld(this);
         if (GameClient.bClient) {
            this.chunk.vehicles.remove(this);
         }

         this.m_surroundVehicle.reset();
         this.removeWorldLights();
         super.removeFromWorld();
      }
   }

    void permanentlyRemove() {
      for (int var1 = 0; var1 < this.getMaxPassengers(); var1++) {
    IsoGameCharacter var2 = this.getCharacter(var1);
         if (var2 != nullptr) {
            if (GameServer.bServer) {
               var2.sendObjectChange("exitVehicle");
            }

            this.exit(var2);
         }
      }

      this.breakConstraint(true, false);
      this.removeFromWorld();
      this.removeFromSquare();
      if (this.chunk != nullptr) {
         this.chunk.vehicles.remove(this);
      }

      VehiclesDB2.instance.removeVehicle(this);
   }

    VehiclePart getBattery() {
      return this.battery;
   }

    void setEngineFeature(int var1, int var2, int var3) {
      this.engineQuality = PZMath.clamp(var1, 0, 100);
      this.engineLoudness = (int)(var2 / 2.7F);
      this.enginePower = var3;
   }

    int getEngineQuality() {
      return this.engineQuality;
   }

    int getEngineLoudness() {
      return this.engineLoudness;
   }

    int getEnginePower() {
      return this.enginePower;
   }

    float getBatteryCharge() {
    VehiclePart var1 = this.getBattery();
      return var1 != nullptr && var1.getInventoryItem() instanceof DrainableComboItem ? ((DrainableComboItem)var1.getInventoryItem()).getUsedDelta() : 0.0F;
   }

    int getPartCount() {
      return this.parts.size();
   }

    VehiclePart getPartByIndex(int var1) {
      return var1 >= 0 && var1 < this.parts.size() ? this.parts.get(var1) : nullptr;
   }

    VehiclePart getPartById(const std::string& var1) {
      if (var1 == nullptr) {
    return nullptr;
      } else {
         for (int var2 = 0; var2 < this.parts.size(); var2++) {
    VehiclePart var3 = this.parts.get(var2);
    Part var4 = var3.getScriptPart();
            if (var4 != nullptr && var1 == var4.id)) {
    return var3;
            }
         }

    return nullptr;
      }
   }

    int getNumberOfPartsWithContainers() {
      if (this.getScript() == nullptr) {
    return 0;
      } else {
    int var1 = 0;

         for (int var2 = 0; var2 < this.getScript().getPartCount(); var2++) {
            if (this.getScript().getPart(var2).container != nullptr) {
               var1++;
            }
         }

    return var1;
      }
   }

    VehiclePart getPartForSeatContainer(int var1) {
      if (this.getScript() != nullptr && var1 >= 0 && var1 < this.getMaxPassengers()) {
         for (int var2 = 0; var2 < this.getPartCount(); var2++) {
    VehiclePart var3 = this.getPartByIndex(var2);
            if (var3.getContainerSeatNumber() == var1) {
    return var3;
            }
         }

    return nullptr;
      } else {
    return nullptr;
      }
   }

    void transmitPartCondition(VehiclePart var1) {
      if (GameServer.bServer) {
         if (this.parts.contains(var1)) {
            var1.updateFlags = (short)(var1.updateFlags | 2048);
            this.updateFlags = (short)(this.updateFlags | 2048);
         }
      }
   }

    void transmitPartItem(VehiclePart var1) {
      if (GameServer.bServer) {
         if (this.parts.contains(var1)) {
            var1.updateFlags = (short)(var1.updateFlags | 128);
            this.updateFlags = (short)(this.updateFlags | 128);
         }
      }
   }

    void transmitPartModData(VehiclePart var1) {
      if (GameServer.bServer) {
         if (this.parts.contains(var1)) {
            var1.updateFlags = (short)(var1.updateFlags | 16);
            this.updateFlags = (short)(this.updateFlags | 16);
         }
      }
   }

    void transmitPartUsedDelta(VehiclePart var1) {
      if (GameServer.bServer) {
         if (this.parts.contains(var1)) {
            if (var1.getInventoryItem() instanceof DrainableComboItem) {
               var1.updateFlags = (short)(var1.updateFlags | 32);
               this.updateFlags = (short)(this.updateFlags | 32);
            }
         }
      }
   }

    void transmitPartDoor(VehiclePart var1) {
      if (GameServer.bServer) {
         if (this.parts.contains(var1)) {
            if (var1.getDoor() != nullptr) {
               var1.updateFlags = (short)(var1.updateFlags | 512);
               this.updateFlags = (short)(this.updateFlags | 512);
            }
         }
      }
   }

    void transmitPartWindow(VehiclePart var1) {
      if (GameServer.bServer) {
         if (this.parts.contains(var1)) {
            if (var1.getWindow() != nullptr) {
               var1.updateFlags = (short)(var1.updateFlags | 256);
               this.updateFlags = (short)(this.updateFlags | 256);
            }
         }
      }
   }

    int getLightCount() {
      return this.lights.size();
   }

    VehiclePart getLightByIndex(int var1) {
      return var1 >= 0 && var1 < this.lights.size() ? this.lights.get(var1) : nullptr;
   }

    std::string getZone() {
      return this.respawnZone;
   }

    void setZone(const std::string& var1) {
      this.respawnZone = var1;
   }

    bool isInArea(const std::string& var1, IsoGameCharacter var2) {
      if (var1 != nullptr && this.getScript() != nullptr) {
    Area var3 = this.getScript().getAreaById(var1);
         if (var3 == nullptr) {
    return false;
         } else {
    Vector2 var4 = (Vector2)TL_vector2_pool.get().alloc();
    Vector2 var5 = this.areaPositionLocal(var3, var4);
            if (var5 == nullptr) {
               TL_vector2_pool.get().release(var4);
    return false;
            } else {
    Vector3f var6 = (Vector3f)TL_vector3f_pool.get().alloc();
               this.getLocalPos(var2.x, var2.y, this.z, var6);
    float var7 = var5.x - var3.w / 2.0F;
    float var8 = var5.y - var3.h / 2.0F;
    float var9 = var5.x + var3.w / 2.0F;
    float var10 = var5.y + var3.h / 2.0F;
               TL_vector2_pool.get().release(var4);
    bool var11 = var6.x >= var7 && var6.x < var9 && var6.z >= var8 && var6.z < var10;
               TL_vector3f_pool.get().release(var6);
    return var11;
            }
         }
      } else {
    return false;
      }
   }

    float getAreaDist(const std::string& var1, IsoGameCharacter var2) {
      if (var1 != nullptr && this.getScript() != nullptr) {
    Area var3 = this.getScript().getAreaById(var1);
         if (var3 != nullptr) {
    Vector3f var4 = this.getLocalPos(var2.x, var2.y, this.z, (Vector3f)TL_vector3f_pool.get().alloc());
    float var5 = Math.abs(var3.x - var3.w / 2.0F);
    float var6 = Math.abs(var3.y - var3.h / 2.0F);
    float var7 = Math.abs(var3.x + var3.w / 2.0F);
    float var8 = Math.abs(var3.y + var3.h / 2.0F);
    float var9 = Math.abs(var4.x + var5) + Math.abs(var4.z + var6);
            TL_vector3f_pool.get().release(var4);
    return var9;
         } else {
            return 999.0F;
         }
      } else {
         return 999.0F;
      }
   }

    Vector2 getAreaCenter(const std::string& var1) {
      return this.getAreaCenter(var1, std::make_unique<Vector2>());
   }

    Vector2 getAreaCenter(const std::string& var1, Vector2 var2) {
      if (var1 != nullptr && this.getScript() != nullptr) {
    Area var3 = this.getScript().getAreaById(var1);
    return var3 = = nullptr ? nullptr : this.areaPositionWorld(var3, var2);
      } else {
    return nullptr;
      }
   }

    bool isInBounds(float var1, float var2) {
      return this.getPoly().containsPoint(var1, var2);
   }

    bool canAccessContainer(int var1, IsoGameCharacter var2) {
    VehiclePart var3 = this.getPartByIndex(var1);
      if (var3 == nullptr) {
    return false;
      } else {
    Part var4 = var3.getScriptPart();
         if (var4 == nullptr) {
    return false;
         } else if (var4.container == nullptr) {
    return false;
         } else if (var3.isInventoryItemUninstalled() && var4.container.capacity == 0) {
    return false;
         } else {
            return var4.container.luaTest != nullptr && !var4.container.luaTest.empty()
               ? bool.TRUE == this.callLuaBoolean(var4.container.luaTest, this, var3, var2))
               : true;
         }
      }
   }

    bool canInstallPart(IsoGameCharacter var1, VehiclePart var2) {
      if (!this.parts.contains(var2)) {
    return false;
      } else {
    KahluaTable var3 = var2.getTable("install");
         return var3 != nullptr && var3.rawget("test") instanceof std::string
            ? bool.TRUE == this.callLuaBoolean((std::string)var3.rawget("test"), this, var2, var1))
            : false;
      }
   }

    bool canUninstallPart(IsoGameCharacter var1, VehiclePart var2) {
      if (!this.parts.contains(var2)) {
    return false;
      } else {
    KahluaTable var3 = var2.getTable("uninstall");
         return var3 != nullptr && var3.rawget("test") instanceof std::string
            ? bool.TRUE == this.callLuaBoolean((std::string)var3.rawget("test"), this, var2, var1))
            : false;
      }
   }

    void callLuaVoid(const std::string& var1, void* var2, void* var3) {
    void* var4 = LuaManager.getFunctionObject(var1);
      if (var4 != nullptr) {
         LuaManager.caller.protectedCallVoid(LuaManager.thread, var4, var2, var3);
      }
   }

    void callLuaVoid(const std::string& var1, void* var2, void* var3, void* var4) {
    void* var5 = LuaManager.getFunctionObject(var1);
      if (var5 != nullptr) {
         LuaManager.caller.protectedCallVoid(LuaManager.thread, var5, var2, var3, var4);
      }
   }

    bool callLuaBoolean(const std::string& var1, void* var2, void* var3) {
    void* var4 = LuaManager.getFunctionObject(var1);
    return var4 = = nullptr ? nullptr : LuaManager.caller.protectedCallBoolean(LuaManager.thread, var4, var2, var3);
   }

    bool callLuaBoolean(const std::string& var1, void* var2, void* var3, void* var4) {
    void* var5 = LuaManager.getFunctionObject(var1);
    return var5 = = nullptr ? nullptr : LuaManager.caller.protectedCallBoolean(LuaManager.thread, var5, var2, var3, var4);
   }

    short getId() {
      return this.VehicleID;
   }

    void setTireInflation(int var1, float var2) {
   }

    void setTireRemoved(int var1, bool var2) {
      if (!GameServer.bServer) {
         Bullet.setTireRemoved(this.VehicleID, var1, var2);
      }
   }

    Vector3f chooseBestAttackPosition(IsoGameCharacter var1, IsoGameCharacter var2, Vector3f var3) {
    Vector2f var4 = (Vector2f)TL_vector2f_pool.get().alloc();
    Vector2f var5 = var1.getVehicle().getSurroundVehicle().getPositionForZombie((IsoZombie)var2, var4);
    float var6 = var4.x;
    float var7 = var4.y;
      TL_vector2f_pool.get().release(var4);
      return var5 != nullptr ? var3.set(var6, var7, this.z) : nullptr;
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    MinMaxPosition getMinMaxPosition() {
    MinMaxPosition var1 = std::make_shared<MinMaxPosition>();
    float var2 = this.getX();
    float var3 = this.getY();
    Vector3f var4 = this.getScript().getExtents();
    float var5 = var4.x;
    float var6 = var4.z;
    IsoDirections var7 = this.getDir();
      switch (1.$SwitchMap$zombie$iso$IsoDirections[var7.ordinal()]) {
         case 1:
         case 2:
            var1.minX = var2 - var5 / 2.0F;
            var1.maxX = var2 + var5 / 2.0F;
            var1.minY = var3 - var6 / 2.0F;
            var1.maxY = var3 + var6 / 2.0F;
            break;
         case 3:
         case 4:
            var1.minX = var2 - var6 / 2.0F;
            var1.maxX = var2 + var6 / 2.0F;
            var1.minY = var3 - var5 / 2.0F;
            var1.maxY = var3 + var5 / 2.0F;
            break;
         default:
    return nullptr;
      }

    return var1;
   }

    std::string getVehicleType() {
      return this.type;
   }

    void setVehicleType(const std::string& var1) {
      this.type = var1;
   }

    float getMaxSpeed() {
      return this.maxSpeed;
   }

    void setMaxSpeed(float var1) {
      this.maxSpeed = var1;
   }

    void lockServerUpdate(long var1) {
      this.updateLockTimeout = System.currentTimeMillis() + var1;
   }

    void changeTransmission(TransmissionNumber var1) {
      this.transmissionNumber = var1;
   }

    void tryHotwire(int var1) {
    int var2 = Math.max(100 - this.getEngineQuality(), 5);
      var2 = Math.min(var2, 50);
    int var3 = var1 * 4;
    int var4 = var2 + var3;
    bool var5 = false;
    void* var6 = nullptr;
      if (Rand.Next(100) <= 11 - var1 && this.alarmed) {
         this.triggerAlarm();
      }

      if (Rand.Next(100) <= var4) {
         this.setHotwired(true);
         var5 = true;
         var6 = "VehicleHotwireSuccess";
      } else if (Rand.Next(100) <= 10 - var1) {
         this.setHotwiredBroken(true);
         var5 = true;
         var6 = "VehicleHotwireFail";
      } else {
         var6 = "VehicleHotwireFail";
      }

      if (var6 != nullptr) {
         if (GameServer.bServer) {
            GlobalObject.playServerSound((std::string)var6, this.square);
         } else if (this.getDriver() != nullptr) {
            this.getDriver().getEmitter().playSound((std::string)var6);
         }
      }

      if (var5 && GameServer.bServer) {
         this.updateFlags = (short)(this.updateFlags | 4096);
      }
   }

    void cheatHotwire(bool var1, bool var2) {
      if (var1 != this.hotwired || var2 != this.hotwiredBroken) {
         this.hotwired = var1;
         this.hotwiredBroken = var2;
         if (GameServer.bServer) {
            this.updateFlags = (short)(this.updateFlags | 4096);
         }
      }
   }

    bool isKeyIsOnDoor() {
      return this.keyIsOnDoor;
   }

    void setKeyIsOnDoor(bool var1) {
      this.keyIsOnDoor = var1;
   }

    bool isHotwired() {
      return this.hotwired;
   }

    void setHotwired(bool var1) {
      this.hotwired = var1;
   }

    bool isHotwiredBroken() {
      return this.hotwiredBroken;
   }

    void setHotwiredBroken(bool var1) {
      this.hotwiredBroken = var1;
   }

    IsoGameCharacter getDriver() {
    Passenger var1 = this.getPassenger(0);
    return var1 = = nullptr ? nullptr : var1.character;
   }

    bool isKeysInIgnition() {
      return this.keysInIgnition;
   }

    void setKeysInIgnition(bool var1) {
    IsoGameCharacter var2 = this.getDriver();
      if (var2 != nullptr) {
         this.setAlarmed(false);
         if (!GameClient.bClient || dynamic_cast<IsoPlayer*>(var2) != nullptr && ((IsoPlayer)var2).isLocalPlayer()) {
            if (!this.isHotwired()) {
               if (!GameServer.bServer && var1 && !this.keysInIgnition) {
    InventoryItem var3 = this.getDriver().getInventory().haveThisKeyId(this.getKeyId());
                  if (var3 != nullptr) {
                     this.setCurrentKey(var3);
    InventoryItem var4 = var3.getContainer().getContainingItem();
                     if (dynamic_cast<InventoryContainer*>(var4) != nullptr && "KeyRing" == var4.getType())) {
                        var3.getModData().rawset("keyRing", (double)var4.getID());
                     } else if (var3.hasModData()) {
                        var3.getModData().rawset("keyRing", nullptr);
                     }

                     var3.getContainer().DoRemoveItem(var3);
                     this.keysInIgnition = var1;
                     if (GameClient.bClient) {
                        GameClient.instance.sendClientCommandV((IsoPlayer)this.getDriver(), "vehicle", "putKeyInIgnition", new Object[]{"key", var3});
                     }
                  }
               }

               if (!var1 && this.keysInIgnition && !GameServer.bServer) {
                  if (this.currentKey == nullptr) {
                     this.currentKey = this.createVehicleKey();
                  }

    InventoryItem var7 = this.getCurrentKey();
    ItemContainer var8 = this.getDriver().getInventory();
                  if (var7.hasModData() && var7.getModData().rawget("keyRing") instanceof double) {
    double var5 = (double)var7.getModData().rawget("keyRing");
    InventoryItem var6 = var8.getItemWithID(var5.intValue());
                     if (dynamic_cast<InventoryContainer*>(var6) != nullptr && "KeyRing" == var6.getType())) {
                        var8 = ((InventoryContainer)var6).getInventory();
                     }

                     var7.getModData().rawset("keyRing", nullptr);
                  }

                  var8.addItem(var7);
                  this.setCurrentKey(nullptr);
                  this.keysInIgnition = var1;
                  if (GameClient.bClient) {
                     GameClient.instance.sendClientCommand((IsoPlayer)this.getDriver(), "vehicle", "removeKeyFromIgnition", (KahluaTable)nullptr);
                  }
               }
            }
         }
      }
   }

    void putKeyInIgnition(InventoryItem var1) {
      if (GameServer.bServer) {
         if (dynamic_cast<Key*>(var1) != nullptr) {
            if (!this.keysInIgnition) {
               this.keysInIgnition = true;
               this.keyIsOnDoor = false;
               this.currentKey = var1;
               this.updateFlags = (short)(this.updateFlags | 4096);
            }
         }
      }
   }

    void removeKeyFromIgnition() {
      if (GameServer.bServer) {
         if (this.keysInIgnition) {
            this.keysInIgnition = false;
            this.currentKey = nullptr;
            this.updateFlags = (short)(this.updateFlags | 4096);
         }
      }
   }

    void putKeyOnDoor(InventoryItem var1) {
      if (GameServer.bServer) {
         if (dynamic_cast<Key*>(var1) != nullptr) {
            if (!this.keyIsOnDoor) {
               this.keyIsOnDoor = true;
               this.keysInIgnition = false;
               this.currentKey = var1;
               this.updateFlags = (short)(this.updateFlags | 4096);
            }
         }
      }
   }

    void removeKeyFromDoor() {
      if (GameServer.bServer) {
         if (this.keyIsOnDoor) {
            this.keyIsOnDoor = false;
            this.currentKey = nullptr;
            this.updateFlags = (short)(this.updateFlags | 4096);
         }
      }
   }

    void syncKeyInIgnition(bool var1, bool var2, InventoryItem var3) {
      if (GameClient.bClient) {
         if (!(this.getDriver() instanceof IsoPlayer) || !((IsoPlayer)this.getDriver()).isLocalPlayer()) {
            this.keysInIgnition = var1;
            this.keyIsOnDoor = var2;
            this.currentKey = var3;
         }
      }
   }

    void randomizeContainers() {
      if (!GameClient.bClient) {
    bool var1 = true;
    std::string var2 = this.getScriptName().substr(this.getScriptName().indexOf(46) + 1);
    VehicleDistribution var3 = (VehicleDistribution)ItemPickerJava.VehicleDistributions.get(var2 + this.getSkinIndex());
         if (var3 != nullptr) {
            var1 = false;
         } else {
            var3 = (VehicleDistribution)ItemPickerJava.VehicleDistributions.get(var2);
         }

         if (var3 == nullptr) {
            for (int var7 = 0; var7 < this.parts.size(); var7++) {
    VehiclePart var9 = this.parts.get(var7);
               if (var9.getItemContainer() != nullptr) {
                  if (Core.bDebug) {
                     DebugLog.log("VEHICLE MISSING CONT DISTRIBUTION: " + var2);
                  }

                  return;
               }
            }
         } else {
    ItemPickerRoom var4;
            if (var1 && Rand.Next(100) <= 8 && !var3.Specific.empty()) {
               var4 = (ItemPickerRoom)PZArrayUtil.pickRandom(var3.Specific);
            } else {
               var4 = var3.Normal;
            }

            if (!StringUtils.isNullOrWhitespace(this.specificDistributionId)) {
               for (int var5 = 0; var5 < var3.Specific.size(); var5++) {
    ItemPickerRoom var6 = (ItemPickerRoom)var3.Specific.get(var5);
                  if (this.specificDistributionId == var6.specificId)) {
                     var4 = var6;
                     break;
                  }
               }
            }

            for (int var8 = 0; var8 < this.parts.size(); var8++) {
    VehiclePart var10 = this.parts.get(var8);
               if (var10.getItemContainer() != nullptr) {
                  if (GameServer.bServer && GameServer.bSoftReset) {
                     var10.getItemContainer().setExplored(false);
                  }

                  if (!var10.getItemContainer().bExplored) {
                     var10.getItemContainer().clear();
                     if (Rand.Next(100) <= 100) {
                        this.randomizeContainer(var10, var4);
                        LuaEventManager.triggerEvent("OnFillContainer", var2, var10.getItemContainer().getType(), var10.getItemContainer());
                     }

                     var10.getItemContainer().setExplored(true);
                  }
               }
            }
         }
      }
   }

    void randomizeContainer(VehiclePart var1, ItemPickerRoom var2) {
      if (!GameClient.bClient) {
         if (var2 != nullptr) {
            if (!var1.getId().contains("Seat") && !var2.Containers.containsKey(var1.getId())) {
               DebugLog.log("NO CONT DISTRIB FOR PART: " + var1.getId() + " CAR: " + this.getScriptName().replaceFirst("Base.", ""));
            }

            ItemPickerJava.fillContainerType(var2, var1.getItemContainer(), "", nullptr);
            if (GameServer.bServer && !var1.getItemContainer().getItems().empty()) {
            }
         }
      }
   }

    bool hasHorn() {
      return this.script.getSounds().hornEnable;
   }

    bool hasLightbar() {
    VehiclePart var1 = this.getPartById("lightbar");
      return this.script.getLightbar().enable;
   }

    void onHornStart() {
      this.soundHornOn = true;
      if (GameServer.bServer) {
         this.updateFlags = (short)(this.updateFlags | 1024);
         if (this.script.getSounds().hornEnable) {
            WorldSoundManager.instance.addSound(this, (int)this.getX(), (int)this.getY(), (int)this.getZ(), 150, 150, false);
         }
      } else {
         if (this.soundHorn != -1L) {
            this.hornemitter.stopSound(this.soundHorn);
         }

         if (this.script.getSounds().hornEnable) {
            this.hornemitter = IsoWorld.instance.getFreeEmitter(this.getX(), this.getY(), (int)this.getZ());
            this.soundHorn = this.hornemitter.playSoundLoopedImpl(this.script.getSounds().horn);
            this.hornemitter.set3D(this.soundHorn, !this.isAnyListenerInside());
            this.hornemitter.setVolume(this.soundHorn, 1.0F);
            this.hornemitter.setPitch(this.soundHorn, 1.0F);
            if (!GameClient.bClient) {
               WorldSoundManager.instance.addSound(this, (int)this.getX(), (int)this.getY(), (int)this.getZ(), 150, 150, false);
            }
         }
      }
   }

    void onHornStop() {
      this.soundHornOn = false;
      if (GameServer.bServer) {
         this.updateFlags = (short)(this.updateFlags | 1024);
      } else {
         if (this.script.getSounds().hornEnable && this.soundHorn != -1L) {
            this.hornemitter.stopSound(this.soundHorn);
            this.soundHorn = -1L;
         }
      }
   }

    bool hasBackSignal() {
      return this.script != nullptr && this.script.getSounds().backSignalEnable;
   }

    bool isBackSignalEmitting() {
      return this.soundBackMoveSignal != -1L;
   }

    void onBackMoveSignalStart() {
      this.soundBackMoveOn = true;
      if (GameServer.bServer) {
         this.updateFlags = (short)(this.updateFlags | 1024);
      } else {
         if (this.soundBackMoveSignal != -1L) {
            this.emitter.stopSound(this.soundBackMoveSignal);
         }

         if (this.script.getSounds().backSignalEnable) {
            this.soundBackMoveSignal = this.emitter.playSoundLoopedImpl(this.script.getSounds().backSignal);
            this.emitter.set3D(this.soundBackMoveSignal, !this.isAnyListenerInside());
         }
      }
   }

    void onBackMoveSignalStop() {
      this.soundBackMoveOn = false;
      if (GameServer.bServer) {
         this.updateFlags = (short)(this.updateFlags | 1024);
      } else {
         if (this.script.getSounds().backSignalEnable && this.soundBackMoveSignal != -1L) {
            this.emitter.stopSound(this.soundBackMoveSignal);
            this.soundBackMoveSignal = -1L;
         }
      }
   }

    int getLightbarLightsMode() {
      return this.lightbarLightsMode.get();
   }

    void setLightbarLightsMode(int var1) {
      this.lightbarLightsMode.set(var1);
      if (GameServer.bServer) {
         this.updateFlags = (short)(this.updateFlags | 1024);
      }
   }

    int getLightbarSirenMode() {
      return this.lightbarSirenMode.get();
   }

    void setLightbarSirenMode(int var1) {
      if (this.soundSirenSignal != -1L) {
         this.getEmitter().stopSound(this.soundSirenSignal);
         this.soundSirenSignal = -1L;
      }

      this.lightbarSirenMode.set(var1);
      if (GameServer.bServer) {
         this.updateFlags = (short)(this.updateFlags | 1024);
      } else {
         if (this.lightbarSirenMode.isEnable() && this.getBatteryCharge() > 0.0F) {
            this.soundSirenSignal = this.getEmitter().playSoundLoopedImpl(this.lightbarSirenMode.getSoundName(this.script.getLightbar()));
            this.getEmitter().set3D(this.soundSirenSignal, !this.isAnyListenerInside());
         }
      }
   }

   public std::unordered_map<std::string, std::string> getChoosenParts() {
      return this.choosenParts;
   }

    float getMass() {
    float var1 = this.mass;
      if (var1 < 0.0F) {
         var1 = 1.0F;
      }

    return var1;
   }

    void setMass(float var1) {
      this.mass = var1;
   }

    float getInitialMass() {
      return this.initialMass;
   }

    void setInitialMass(float var1) {
      this.initialMass = var1;
   }

    void updateTotalMass() {
    float var1 = 0.0F;

      for (int var2 = 0; var2 < this.parts.size(); var2++) {
    VehiclePart var3 = this.parts.get(var2);
         if (var3.getItemContainer() != nullptr) {
            var1 += var3.getItemContainer().getCapacityWeight();
         }

         if (var3.getInventoryItem() != nullptr) {
            var1 += var3.getInventoryItem().getWeight();
         }
      }

      this.setMass(Math.round(this.getInitialMass() + var1));
      if (this.physics != nullptr && !GameServer.bServer) {
         Bullet.setVehicleMass(this.VehicleID, this.getMass());
      }
   }

    float getBrakingForce() {
      return this.brakingForce;
   }

    void setBrakingForce(float var1) {
      this.brakingForce = var1;
   }

    float getBaseQuality() {
      return this.baseQuality;
   }

    void setBaseQuality(float var1) {
      this.baseQuality = var1;
   }

    float getCurrentSteering() {
      return this.currentSteering;
   }

    void setCurrentSteering(float var1) {
      this.currentSteering = var1;
   }

    bool isDoingOffroad() {
      if (this.getCurrentSquare() == nullptr) {
    return false;
      } else {
    IsoObject var1 = this.getCurrentSquare().getFloor();
         if (var1 != nullptr && var1.getSprite() != nullptr) {
    std::string var2 = var1.getSprite().getName();
    return var2 = = nullptr ? false : !var2.contains("carpentry_02") && !var2.contains("blends_street") && !var2.contains("floors_exterior_street");
         } else {
    return false;
         }
      }
   }

    bool isBraking() {
      return this.isBraking;
   }

    void setBraking(bool var1) {
      this.isBraking = var1;
      if (var1 && this.brakeBetweenUpdatesSpeed == 0.0F) {
         this.brakeBetweenUpdatesSpeed = Math.abs(this.getCurrentSpeedKmHour());
      }
   }

    void updatePartStats() {
      this.setBrakingForce(0.0F);
      this.engineLoudness = (int)(this.getScript().getEngineLoudness() * SandboxOptions.instance.ZombieAttractionMultiplier.getValue() / 2.0);
    bool var1 = false;

      for (int var2 = 0; var2 < this.getPartCount(); var2++) {
    VehiclePart var3 = this.getPartByIndex(var2);
         if (var3.getInventoryItem() != nullptr) {
            if (var3.getInventoryItem().getBrakeForce() > 0.0F) {
    float var4 = VehiclePart.getNumberByCondition(var3.getInventoryItem().getBrakeForce(), var3.getInventoryItem().getCondition(), 5.0F);
               var4 += var4 / 50.0F * var3.getMechanicSkillInstaller();
               this.setBrakingForce(this.getBrakingForce() + var4);
            }

            if (var3.getInventoryItem().getWheelFriction() > 0.0F) {
               var3.setWheelFriction(0.0F);
    float var6 = VehiclePart.getNumberByCondition(var3.getInventoryItem().getWheelFriction(), var3.getInventoryItem().getCondition(), 0.2F);
               var6 += 0.1F * var3.getMechanicSkillInstaller();
               var6 = Math.min(2.3F, var6);
               var3.setWheelFriction(var6);
            }

            if (var3.getInventoryItem().getSuspensionCompression() > 0.0F) {
               var3.setSuspensionCompression(
                  VehiclePart.getNumberByCondition(var3.getInventoryItem().getSuspensionCompression(), var3.getInventoryItem().getCondition(), 0.6F)
               );
               var3.setSuspensionDamping(
                  VehiclePart.getNumberByCondition(var3.getInventoryItem().getSuspensionDamping(), var3.getInventoryItem().getCondition(), 0.6F)
               );
            }

            if (var3.getInventoryItem().getEngineLoudness() > 0.0F) {
               var3.setEngineLoudness(
                  VehiclePart.getNumberByCondition(var3.getInventoryItem().getEngineLoudness(), var3.getInventoryItem().getCondition(), 10.0F)
               );
               this.engineLoudness = (int)(this.engineLoudness * (1.0F + (100.0F - var3.getEngineLoudness()) / 100.0F));
               var1 = true;
            }
         }
      }

      if (!var1) {
         this.engineLoudness *= 2;
      }
   }

    void transmitEngine() {
      if (GameServer.bServer) {
         this.updateFlags = (short)(this.updateFlags | 4);
      }
   }

    void setRust(float var1) {
      this.rust = PZMath.clamp(var1, 0.0F, 1.0F);
   }

    float getRust() {
      return this.rust;
   }

    void transmitRust() {
      if (GameServer.bServer) {
         this.updateFlags = (short)(this.updateFlags | 4096);
      }
   }

    void transmitColorHSV() {
      if (GameServer.bServer) {
         this.updateFlags = (short)(this.updateFlags | 4096);
      }
   }

    void transmitSkinIndex() {
      if (GameServer.bServer) {
         this.updateFlags = (short)(this.updateFlags | 4096);
      }
   }

    void updateBulletStats() {
      if (!this.getScriptName().contains("Burnt") && WorldSimulation.instance.created) {
         float[] var1 = wheelParams;
    double var4 = 2.4;
    uint8_t var6 = 5;
    double var2;
    float var7;
         if (this.isInForest() && this.isDoingOffroad() && Math.abs(this.getCurrentSpeedKmHour()) > 1.0F) {
            var2 = Rand.Next(0.08F, 0.18F);
            var7 = 0.7F;
            var6 = 3;
         } else if (this.isDoingOffroad() && Math.abs(this.getCurrentSpeedKmHour()) > 1.0F) {
            var2 = Rand.Next(0.05F, 0.15F);
            var7 = 0.7F;
         } else {
            if (Math.abs(this.getCurrentSpeedKmHour()) > 1.0F && Rand.Next(100) < 10) {
               var2 = Rand.Next(0.05F, 0.15F);
            } else {
               var2 = 0.0;
            }

            var7 = 1.0F;
         }

         if (RainManager.isRaining()) {
            var7 -= 0.3F;
         }

    Vector3f var8 = (Vector3f)TL_vector3f_pool.get().alloc();

         for (int var9 = 0; var9 < this.script.getWheelCount(); var9++) {
            this.updateBulletStatsWheel(var9, var1, var8, var7, var6, var4, var2);
         }

         TL_vector3f_pool.get().release(var8);
         if (SystemDisabler.getdoVehicleLowRider() && this.isKeyboardControlled()) {
    float var11 = 1.6F;
    float var10 = 1.0F;
            if (GameKeyboard.isKeyDown(79)) {
               lowRiderParam[0] = lowRiderParam[0] + (var11 - lowRiderParam[0]) * var10;
            } else {
               lowRiderParam[0] = lowRiderParam[0] + (0.0F - lowRiderParam[0]) * 0.05F;
            }

            if (GameKeyboard.isKeyDown(80)) {
               lowRiderParam[1] = lowRiderParam[1] + (var11 - lowRiderParam[1]) * var10;
            } else {
               lowRiderParam[1] = lowRiderParam[1] + (0.0F - lowRiderParam[1]) * 0.05F;
            }

            if (GameKeyboard.isKeyDown(75)) {
               lowRiderParam[2] = lowRiderParam[2] + (var11 - lowRiderParam[2]) * var10;
            } else {
               lowRiderParam[2] = lowRiderParam[2] + (0.0F - lowRiderParam[2]) * 0.05F;
            }

            if (GameKeyboard.isKeyDown(76)) {
               lowRiderParam[3] = lowRiderParam[3] + (var11 - lowRiderParam[3]) * var10;
            } else {
               lowRiderParam[3] = lowRiderParam[3] + (0.0F - lowRiderParam[3]) * 0.05F;
            }

            var1[23] = lowRiderParam[0];
            var1[22] = lowRiderParam[1];
            var1[21] = lowRiderParam[2];
            var1[20] = lowRiderParam[3];
         }

         Bullet.setVehicleParams(this.VehicleID, var1);
      }
   }

    void updateBulletStatsWheel(int var1, float[] var2, Vector3f var3, float var4, int var5, double var6, double var8) {
    int var10 = var1 * 6;
    Wheel var11 = this.script.getWheel(var1);
    Vector3f var12 = this.getWorldPos(var11.offset.x, var11.offset.y, var11.offset.z, var3);
    VehiclePart var13 = this.getPartById("Tire" + var11.getId());
    VehiclePart var14 = this.getPartById("Suspension" + var11.getId());
      if (var13 != nullptr && var13.getInventoryItem() != nullptr) {
         var2[var10 + 0] = 1.0F;
         var2[var10 + 1] = Math.min(var13.getContainerContentAmount() / (var13.getContainerCapacity() - 10), 1.0F);
         var2[var10 + 2] = var4 * var13.getWheelFriction();
         if (var14 != nullptr && var14.getInventoryItem() != nullptr) {
            var2[var10 + 3] = var14.getSuspensionDamping();
            var2[var10 + 4] = var14.getSuspensionCompression();
         } else {
            var2[var10 + 3] = 0.1F;
            var2[var10 + 4] = 0.1F;
         }

         if (Rand.Next(var5) == 0) {
            var2[var10 + 5] = (float)(Math.sin(var6 * var12.x()) * Math.sin(var6 * var12.y()) * var8);
         } else {
            var2[var10 + 5] = 0.0F;
         }
      } else {
         var2[var10 + 0] = 0.0F;
         var2[var10 + 1] = 30.0F;
         var2[var10 + 2] = 0.0F;
         var2[var10 + 3] = 2.88F;
         var2[var10 + 4] = 3.83F;
         if (Rand.Next(var5) == 0) {
            var2[var10 + 5] = (float)(Math.sin(var6 * var12.x()) * Math.sin(var6 * var12.y()) * var8);
         } else {
            var2[var10 + 5] = 0.0F;
         }
      }

      if (this.forcedFriction > -1.0F) {
         var2[var10 + 2] = this.forcedFriction;
      }
   }

    void setActiveInBullet(bool var1) {
      if (var1 || !this.isEngineRunning()) {
         ;
      }
   }

    bool areAllDoorsLocked() {
      for (int var1 = 0; var1 < this.getMaxPassengers(); var1++) {
    VehiclePart var2 = this.getPassengerDoor(var1);
         if (var2 != nullptr && var2.getDoor() != nullptr && !var2.getDoor().isLocked()) {
    return false;
         }
      }

    return true;
   }

    bool isAnyDoorLocked() {
      for (int var1 = 0; var1 < this.getMaxPassengers(); var1++) {
    VehiclePart var2 = this.getPassengerDoor(var1);
         if (var2 != nullptr && var2.getDoor() != nullptr && var2.getDoor().isLocked()) {
    return true;
         }
      }

    return false;
   }

    float getRemainingFuelPercentage() {
    VehiclePart var1 = this.getPartById("GasTank");
    return var1 = = nullptr ? 0.0F : var1.getContainerContentAmount() / var1.getContainerCapacity() * 100.0F;
   }

    int getMechanicalID() {
      return this.mechanicalID;
   }

    void setMechanicalID(int var1) {
      this.mechanicalID = var1;
   }

    bool needPartsUpdate() {
      return this.needPartsUpdate;
   }

    void setNeedPartsUpdate(bool var1) {
      this.needPartsUpdate = var1;
   }

    VehiclePart getHeater() {
      return this.getPartById("Heater");
   }

    int windowsOpen() {
    int var1 = 0;

      for (int var2 = 0; var2 < this.getPartCount(); var2++) {
    VehiclePart var3 = this.getPartByIndex(var2);
         if (var3.window != nullptr && var3.window.open) {
            var1++;
         }
      }

    return var1;
   }

    bool isAlarmed() {
      return this.alarmed;
   }

    void setAlarmed(bool var1) {
      this.alarmed = var1;
      if (var1) {
         this.setPreviouslyEntered(false);
      }
   }

    void triggerAlarm() {
      if (this.alarmed) {
         this.alarmed = false;
         this.alarmTime = Rand.Next(1500, 3000);
         this.alarmAccumulator = 0.0F;
      }
   }

    void doAlarm() {
      if (this.alarmTime > 0) {
         if (this.getBatteryCharge() <= 0.0F) {
            if (this.soundHornOn) {
               this.onHornStop();
            }

            this.alarmTime = -1;
            return;
         }

         this.alarmAccumulator = this.alarmAccumulator + GameTime.instance.getMultiplier() / 1.6F;
         if (this.alarmAccumulator >= this.alarmTime) {
            this.onHornStop();
            this.setHeadlightsOn(false);
            this.alarmTime = -1;
            return;
         }

    int var1 = (int)this.alarmAccumulator / 20;
         if (!this.soundHornOn && var1 % 2 == 0) {
            this.onHornStart();
            this.setHeadlightsOn(true);
         }

         if (this.soundHornOn && var1 % 2 == 1) {
            this.onHornStop();
            this.setHeadlightsOn(false);
         }
      }
   }

    bool isMechanicUIOpen() {
      return this.mechanicUIOpen;
   }

    void setMechanicUIOpen(bool var1) {
      this.mechanicUIOpen = var1;
   }

    void damagePlayers(float var1) {
      if (SandboxOptions.instance.PlayerDamageFromCrash.getValue()) {
         if (!GameClient.bClient) {
            for (int var2 = 0; var2 < this.passengers.length; var2++) {
               if (this.getPassenger(var2).character != nullptr) {
    IsoGameCharacter var3 = this.getPassenger(var2).character;
                  if (GameServer.bServer && dynamic_cast<IsoPlayer*>(var3) != nullptr) {
                     GameServer.sendPlayerDamagedByCarCrash((IsoPlayer)var3, var1);
                  } else {
                     this.addRandomDamageFromCrash(var3, var1);
                     LuaEventManager.triggerEvent("OnPlayerGetDamage", var3, "CARCRASHDAMAGE", var1);
                  }
               }
            }
         }
      }
   }

    void addRandomDamageFromCrash(IsoGameCharacter var1, float var2) {
    int var3 = 1;
      if (var2 > 40.0F) {
         var3 = Rand.Next(1, 3);
      }

      if (var2 > 70.0F) {
         var3 = Rand.Next(2, 4);
      }

    int var4 = 0;

      for (int var5 = 0; var5 < var1.getVehicle().getPartCount(); var5++) {
    VehiclePart var6 = var1.getVehicle().getPartByIndex(var5);
         if (var6.window != nullptr && var6.getCondition() < 15) {
            var4++;
         }
      }

      for (int var9 = 0; var9 < var3; var9++) {
    int var10 = Rand.Next(BodyPartType.ToIndex(BodyPartType.Hand_L), BodyPartType.ToIndex(BodyPartType.MAX));
    BodyPart var7 = var1.getBodyDamage().getBodyPart(BodyPartType.FromIndex(var10));
    float var8 = Math.max(Rand.Next(var2 - 15.0F, var2), 5.0F);
         if (var1.Traits.FastHealer.isSet()) {
            var8 = (float)(var8 * 0.8);
         } else if (var1.Traits.SlowHealer.isSet()) {
            var8 = (float)(var8 * 1.2);
         }

         switch (SandboxOptions.instance.InjurySeverity.getValue()) {
            case 1:
               var8 *= 0.5F;
               break;
            case 3:
               var8 *= 1.5F;
         }

         var8 *= this.getScript().getPlayerDamageProtection();
         var8 = (float)(var8 * 0.9);
         var7.AddDamage(var8);
         if (var8 > 40.0F && Rand.Next(12) == 0) {
            var7.generateDeepWound();
         } else if (var8 > 50.0F && Rand.Next(10) == 0 && SandboxOptions.instance.BoneFracture.getValue()) {
            if (var7.getType() != BodyPartType.Neck && var7.getType() != BodyPartType.Groin) {
               var7.setFractureTime(Rand.Next(Rand.Next(10.0F, var8 + 10.0F), Rand.Next(var8 + 20.0F, var8 + 30.0F)));
            } else {
               var7.generateDeepWound();
            }
         }

         if (var8 > 30.0F && Rand.Next(12 - var4) == 0) {
            var7 = var1.getBodyDamage().setScratchedWindow();
            if (Rand.Next(5) == 0) {
               var7.generateDeepWound();
               var7.setHaveGlass(true);
            }
         }
      }
   }

    void hitVehicle(IsoGameCharacter var1, HandWeapon var2) {
    float var3 = 1.0F;
      if (var2 == nullptr) {
         var2 = (HandWeapon)InventoryItemFactory.CreateItem("Base.BareHands");
      }

      var3 = var2.getDoorDamage();
      if (var1.isCriticalHit()) {
         var3 *= 10.0F;
      }

    VehiclePart var4 = this.getNearestBodyworkPart(var1);
      if (var4 != nullptr) {
    VehicleWindow var5 = var4.getWindow();

         for (int var6 = 0; var6 < var4.getChildCount(); var6++) {
    VehiclePart var7 = var4.getChild(var6);
            if (var7.getWindow() != nullptr) {
               var5 = var7.getWindow();
               break;
            }
         }

         if (var5 != nullptr && var5.getHealth() > 0) {
            var5.damage((int)var3);
            this.transmitPartWindow(var4);
            if (var5.getHealth() == 0) {
               VehicleManager.sendSoundFromServer(this, (byte)1);
            }
         } else {
            var4.setCondition(var4.getCondition() - (int)var3);
            this.transmitPartItem(var4);
         }

         var4.updateFlags = (short)(var4.updateFlags | 2048);
         this.updateFlags = (short)(this.updateFlags | 2048);
      } else {
    Vector3f var9 = (Vector3f)TL_vector3f_pool.get().alloc();
         this.getLocalPos(var1.getX(), var1.getY(), var1.getZ(), var9);
    bool var10 = var9.x > 0.0F;
         TL_vector3f_pool.get().release(var9);
         if (var10) {
            this.addDamageFront((int)var3);
         } else {
            this.addDamageRear((int)var3);
         }

         this.updateFlags = (short)(this.updateFlags | 2048);
      }
   }

    bool isTrunkLocked() {
    VehiclePart var1 = this.getPartById("TrunkDoor");
      if (var1 == nullptr) {
         var1 = this.getPartById("DoorRear");
      }

      return var1 != nullptr && var1.getDoor() != nullptr && var1.getInventoryItem() != nullptr ? var1.getDoor().isLocked() : false;
   }

    void setTrunkLocked(bool var1) {
    VehiclePart var2 = this.getPartById("TrunkDoor");
      if (var2 == nullptr) {
         var2 = this.getPartById("DoorRear");
      }

      if (var2 != nullptr && var2.getDoor() != nullptr && var2.getInventoryItem() != nullptr) {
         var2.getDoor().setLocked(var1);
         if (GameServer.bServer) {
            this.transmitPartDoor(var2);
         }
      }
   }

    VehiclePart getNearestBodyworkPart(IsoGameCharacter var1) {
      for (int var2 = 0; var2 < this.getPartCount(); var2++) {
    VehiclePart var3 = this.getPartByIndex(var2);
         if (("door" == var3.getCategory()) || "bodywork" == var3.getCategory())) && this.isInArea(var3.getArea(), var1) && var3.getCondition() > 0) {
    return var3;
         }
      }

    return nullptr;
   }

    double getSirenStartTime() {
      return this.sirenStartTime;
   }

    void setSirenStartTime(double var1) {
      this.sirenStartTime = var1;
   }

    bool sirenShutoffTimeExpired() {
    double var1 = SandboxOptions.instance.SirenShutoffHours.getValue();
      if (var1 <= 0.0) {
    return false;
      } else {
    double var3 = GameTime.instance.getWorldAgeHours();
         if (this.sirenStartTime > var3) {
            this.sirenStartTime = var3;
         }

         return this.sirenStartTime + var1 < var3;
      }
   }

    void repair() {
      for (int var1 = 0; var1 < this.getPartCount(); var1++) {
    VehiclePart var2 = this.getPartByIndex(var1);
         var2.repair();
      }

      this.rust = 0.0F;
      this.transmitRust();
      this.bloodIntensity.clear();
      this.transmitBlood();
      this.doBloodOverlay();
   }

    bool isAnyListenerInside() {
      for (int var1 = 0; var1 < this.getMaxPassengers(); var1++) {
    IsoGameCharacter var2 = this.getCharacter(var1);
         if (dynamic_cast<IsoPlayer*>(var2) != nullptr && ((IsoPlayer)var2).isLocalPlayer() && !var2.Traits.Deaf.isSet()) {
    return true;
         }
      }

    return false;
   }

    bool couldCrawlerAttackPassenger(IsoGameCharacter var1) {
    int var2 = this.getSeat(var1);
    return var2 = = -1 ? false : false;
   }

    bool isGoodCar() {
      return this.isGoodCar;
   }

    void setGoodCar(bool var1) {
      this.isGoodCar = var1;
   }

    InventoryItem getCurrentKey() {
      return this.currentKey;
   }

    void setCurrentKey(InventoryItem var1) {
      this.currentKey = var1;
   }

    bool isInForest() {
      return this.getSquare() != nullptr
         && this.getSquare().getZone() != nullptr
         && (
            "Forest" == this.getSquare().getZone().getType())
               || "DeepForest" == this.getSquare().getZone().getType())
               || "FarmLand" == this.getSquare().getZone().getType())
         );
   }

    float getOffroadEfficiency() {
      return this.isInForest() ? this.script.getOffroadEfficiency() * 1.5F : this.script.getOffroadEfficiency() * 2.0F;
   }

    void doChrHitImpulse(IsoObject var1) {
    float var2 = 22.0F;
    Vector3f var3 = this.getLinearVelocity((Vector3f)TL_vector3f_pool.get().alloc());
      var3.y = 0.0F;
    Vector3f var4 = (Vector3f)TL_vector3f_pool.get().alloc();
      var4.set(this.x - var1.getX(), 0.0F, this.z - var1.getY());
      var4.normalize();
      var3.mul(var4);
      TL_vector3f_pool.get().release(var4);
    float var5 = var3.length();
      var5 = Math.min(var5, var2);
      if (var5 < 0.05F) {
         TL_vector3f_pool.get().release(var3);
      } else {
         if (GameServer.bServer) {
            if (dynamic_cast<IsoZombie*>(var1) != nullptr) {
               ((IsoZombie)var1).setThumpFlag(1);
            }
         } else {
            SoundManager.instance.PlayWorldSound("ZombieThumpGeneric", var1.square, 0.0F, 20.0F, 0.9F, true);
         }

    Vector3f var6 = (Vector3f)TL_vector3f_pool.get().alloc();
         var6.set(this.x - var1.getX(), 0.0F, this.y - var1.getY());
         var6.normalize();
         var3.normalize();
    float var7 = var3.dot(var6);
         TL_vector3f_pool.get().release(var3);
         TL_vector3f_pool.get().release(var6);
         this.ApplyImpulse(var1, this.getFudgedMass() * 3.0F * var5 / var2 * Math.abs(var7));
      }
   }

    bool isDoColor() {
      return this.doColor;
   }

    void setDoColor(bool var1) {
      this.doColor = var1;
   }

    float getBrakeSpeedBetweenUpdate() {
      return this.brakeBetweenUpdatesSpeed;
   }

    IsoGridSquare getSquare() {
      return this.getCell().getGridSquare(this.x, this.y, this.z);
   }

    void setColor(float var1, float var2, float var3) {
      this.colorValue = var1;
      this.colorSaturation = var2;
      this.colorHue = var3;
   }

    void setColorHSV(float var1, float var2, float var3) {
      this.colorHue = var1;
      this.colorSaturation = var2;
      this.colorValue = var3;
   }

    float getColorHue() {
      return this.colorHue;
   }

    float getColorSaturation() {
      return this.colorSaturation;
   }

    float getColorValue() {
      return this.colorValue;
   }

    bool isRemovedFromWorld() {
      return this.removedFromWorld;
   }

    float getInsideTemperature() {
    VehiclePart var1 = this.getPartById("PassengerCompartment");
    float var2 = 0.0F;
      if (var1 != nullptr && var1.getModData() != nullptr) {
         if (var1.getModData().rawget("temperature") != nullptr) {
            var2 += ((double)var1.getModData().rawget("temperature")).floatValue();
         }

         if (var1.getModData().rawget("windowtemperature") != nullptr) {
            var2 += ((double)var1.getModData().rawget("windowtemperature")).floatValue();
         }
      }

    return var2;
   }

    AnimationPlayer getAnimationPlayer() {
    std::string var1 = this.getScript().getModel().file;
      zombie.core.skinnedmodel.model.Model var2 = ModelManager.instance.getLoadedModel(var1);
      if (var2 != nullptr && !var2.bStatic) {
         if (this.m_animPlayer != nullptr && this.m_animPlayer.getModel() != var2) {
            this.m_animPlayer = (AnimationPlayer)Pool.tryRelease(this.m_animPlayer);
         }

         if (this.m_animPlayer == nullptr) {
            this.m_animPlayer = AnimationPlayer.alloc(var2);
         }

         return this.m_animPlayer;
      } else {
    return nullptr;
      }
   }

    void releaseAnimationPlayers() {
      this.m_animPlayer = (AnimationPlayer)Pool.tryRelease(this.m_animPlayer);
      PZArrayUtil.forEach(this.models, ModelInfo::releaseAnimationPlayer);
   }

    void setAddThumpWorldSound(bool var1) {
      this.bAddThumpWorldSound = var1;
   }

    void Thump(IsoMovingObject var1) {
    VehiclePart var2 = this.getPartById("lightbar");
      if (var2 != nullptr) {
         if (var2.getCondition() <= 0) {
            var1.setThumpTarget(nullptr);
         }

    VehiclePart var3 = this.getUseablePart((IsoGameCharacter)var1);
         if (var3 != nullptr) {
            var3.setCondition(var3.getCondition() - Rand.Next(1, 5));
         }

         var2.setCondition(var2.getCondition() - Rand.Next(1, 5));
      }
   }

    void WeaponHit(IsoGameCharacter var1, HandWeapon var2) {
   }

    Thumpable getThumpableFor(IsoGameCharacter var1) {
    return nullptr;
   }

    float getThumpCondition() {
      return 1.0F;
   }

    bool isRegulator() {
      return this.regulator;
   }

    void setRegulator(bool var1) {
      this.regulator = var1;
   }

    float getRegulatorSpeed() {
      return this.regulatorSpeed;
   }

    void setRegulatorSpeed(float var1) {
      this.regulatorSpeed = var1;
   }

    float getCurrentSpeedForRegulator() {
      return (float)Math.max(5.0 * Math.floor(this.jniSpeed / 5.0F), 5.0);
   }

    void setVehicleTowing(BaseVehicle var1, const std::string& var2, const std::string& var3) {
      this.vehicleTowing = var1;
      this.vehicleTowingID = this.vehicleTowing == nullptr ? -1 : this.vehicleTowing.getSqlId();
      this.towAttachmentSelf = var2;
      this.towAttachmentOther = var3;
      this.towConstraintZOffset = 0.0F;
   }

    void setVehicleTowedBy(BaseVehicle var1, const std::string& var2, const std::string& var3) {
      this.vehicleTowedBy = var1;
      this.vehicleTowedByID = this.vehicleTowedBy == nullptr ? -1 : this.vehicleTowedBy.getSqlId();
      this.towAttachmentSelf = var3;
      this.towAttachmentOther = var2;
      this.towConstraintZOffset = 0.0F;
   }

    BaseVehicle getVehicleTowing() {
      return this.vehicleTowing;
   }

    BaseVehicle getVehicleTowedBy() {
      return this.vehicleTowedBy;
   }

    bool attachmentExist(const std::string& var1) {
    VehicleScript var2 = this.getScript();
      if (var2 == nullptr) {
    return false;
      } else {
    ModelAttachment var3 = var2.getAttachmentById(var1);
         return var3 != nullptr;
      }
   }

    Vector3f getAttachmentLocalPos(const std::string& var1, Vector3f var2) {
    VehicleScript var3 = this.getScript();
      if (var3 == nullptr) {
    return nullptr;
      } else {
    ModelAttachment var4 = var3.getAttachmentById(var1);
         if (var4 == nullptr) {
    return nullptr;
         } else {
            var2.set(var4.getOffset());
            return var3.getModel() == nullptr ? var2 : var2.push_back(var3.getModel().getOffset());
         }
      }
   }

    Vector3f getAttachmentWorldPos(const std::string& var1, Vector3f var2) {
      var2 = this.getAttachmentLocalPos(var1, var2);
    return var2 = = nullptr ? nullptr : this.getWorldPos(var2, var2);
   }

    void setForceBrake() {
      this.getController().clientControls.forceBrake = System.currentTimeMillis();
   }

    Vector3f getTowingLocalPos(const std::string& var1, Vector3f var2) {
      return this.getAttachmentLocalPos(var1, var2);
   }

    Vector3f getTowedByLocalPos(const std::string& var1, Vector3f var2) {
      return this.getAttachmentLocalPos(var1, var2);
   }

    Vector3f getTowingWorldPos(const std::string& var1, Vector3f var2) {
      var2 = this.getTowingLocalPos(var1, var2);
    return var2 = = nullptr ? nullptr : this.getWorldPos(var2, var2);
   }

    Vector3f getTowedByWorldPos(const std::string& var1, Vector3f var2) {
      var2 = this.getTowedByLocalPos(var1, var2);
    return var2 = = nullptr ? nullptr : this.getWorldPos(var2, var2);
   }

    Vector3f getPlayerTrailerLocalPos(const std::string& var1, bool var2, Vector3f var3) {
    ModelAttachment var4 = this.getScript().getAttachmentById(var1);
      if (var4 == nullptr) {
    return nullptr;
      } else {
    Vector3f var5 = this.getScript().getExtents();
    Vector3f var6 = this.getScript().getCenterOfMassOffset();
    float var7 = var6.x + var5.x / 2.0F + 0.3F + 0.05F;
         if (!var2) {
            var7 *= -1.0F;
         }

         return var4.getOffset().z > 0.0F
            ? var3.set(var7, 0.0F, var6.z + var5.z / 2.0F + 0.3F + 0.05F)
            : var3.set(var7, 0.0F, var6.z - (var5.z / 2.0F + 0.3F + 0.05F));
      }
   }

    Vector3f getPlayerTrailerWorldPos(const std::string& var1, bool var2, Vector3f var3) {
      var3 = this.getPlayerTrailerLocalPos(var1, var2, var3);
      if (var3 == nullptr) {
    return nullptr;
      } else {
         this.getWorldPos(var3, var3);
         var3.z = (int)this.z;
    Vector3f var4 = this.getTowingWorldPos(var1, (Vector3f)TL_vector3f_pool.get().alloc());
    bool var5 = PolygonalMap2.instance.lineClearCollide(var3.x, var3.y, var4.x, var4.y, (int)this.z, this, false, false);
         TL_vector3f_pool.get().release(var4);
         return var5 ? nullptr : var3;
      }
   }

    void drawTowingRope() {
    BaseVehicle var1 = this.getVehicleTowing();
      if (var1 != nullptr) {
    Vector3fObjectPool var2 = TL_vector3f_pool.get();
    Vector3f var3 = this.getAttachmentWorldPos("trailer", (Vector3f)var2.alloc());
    Vector3f var4 = this.getAttachmentWorldPos("trailerfront", (Vector3f)var2.alloc());
    ModelAttachment var5 = this.script.getAttachmentById("trailerfront");
         if (var5 != nullptr) {
            var4.set(var5.getOffset());
         }

    Vector2 var6 = std::make_shared<Vector2>();
         var6.x = var1.x;
         var6.y = var1.y;
         var6.x = var6.x - this.x;
         var6.y = var6.y - this.y;
         var6.setLength(2.0F);
         this.drawDirectionLine(var6, var6.getLength(), 1.0F, 0.5F, 0.5F);
      }
   }

    void drawDirectionLine(Vector2 var1, float var2, float var3, float var4, float var5) {
    float var6 = this.x + var1.x * var2;
    float var7 = this.y + var1.y * var2;
    float var8 = IsoUtils.XToScreenExact(this.x, this.y, this.z, 0);
    float var9 = IsoUtils.YToScreenExact(this.x, this.y, this.z, 0);
    float var10 = IsoUtils.XToScreenExact(var6, var7, this.z, 0);
    float var11 = IsoUtils.YToScreenExact(var6, var7, this.z, 0);
      LineDrawer.drawLine(var8, var9, var10, var11, var3, var4, var5, 0.5F, 1);
   }

    void addPointConstraint(IsoPlayer var1, BaseVehicle var2, const std::string& var3, const std::string& var4) {
      this.addPointConstraint(var1, var2, var3, var4, false);
   }

    void addPointConstraint(IsoPlayer var1, BaseVehicle var2, const std::string& var3, const std::string& var4, bool var5) {
      if (var2 == nullptr
         || var1 != nullptr
            && (IsoUtils.DistanceToSquared(var1.x, var1.y, this.x, this.y) > 100.0F || IsoUtils.DistanceToSquared(var1.x, var1.y, var2.x, var2.y) > 100.0F)) {
         DebugLog.General.warn("The " + var1.getUsername() + " user attached vehicles at a long distance");
      }

      this.breakConstraint(true, var5);
      var2.breakConstraint(true, var5);
    Vector3fObjectPool var7 = TL_vector3f_pool.get();
    Vector3f var8 = this.getTowingLocalPos(var3, (Vector3f)var7.alloc());
    Vector3f var9 = var2.getTowedByLocalPos(var4, (Vector3f)var7.alloc());
      if (var8 != nullptr && var9 != nullptr) {
         if (!GameServer.bServer) {
            if (!this.getScriptName().contains("Trailer") && !var2.getScriptName().contains("Trailer")) {
               this.constraintTowing = Bullet.addRopeConstraint(this.VehicleID, var2.VehicleID, var8.x, var8.y, var8.z, var9.x, var9.y, var9.z, 1.5F);
            } else {
               this.constraintTowing = Bullet.addPointConstraint(this.VehicleID, var2.VehicleID, var8.x, var8.y, var8.z, var9.x, var9.y, var9.z);
            }
         }

         var2.constraintTowing = this.constraintTowing;
         this.setVehicleTowing(var2, var3, var4);
         var2.setVehicleTowedBy(this, var3, var4);
         var7.release(var8);
         var7.release(var9);
         this.constraintChanged();
         var2.constraintChanged();
         if (GameServer.bServer && var1 != nullptr && this.netPlayerAuthorization == Authorization.Server && var2.netPlayerAuthorization == Authorization.Server) {
            this.setNetPlayerAuthorization(Authorization.LocalCollide, var1.OnlineID);
            this.authSimulationTime = System.currentTimeMillis();
            var2.setNetPlayerAuthorization(Authorization.LocalCollide, var1.OnlineID);
            var2.authSimulationTime = System.currentTimeMillis();
         }

         if (GameServer.bServer && !var5) {
            VehicleManager.instance.sendTowing(this, var2, var3, var4);
         }
      } else {
         if (var8 != nullptr) {
            var7.release(var8);
         }

         if (var9 != nullptr) {
            var7.release(var9);
         }
      }
   }

    void authorizationChanged(IsoGameCharacter var1) {
      if (var1 != nullptr) {
         this.setNetPlayerAuthorization(Authorization.Local, var1.getOnlineID());
      } else {
         this.setNetPlayerAuthorization(Authorization.Server, -1);
      }
   }

    void constraintChanged() {
    long var1 = System.currentTimeMillis();
      this.setPhysicsActive(true);
      this.constraintChangedTime = var1;
      if (GameServer.bServer) {
         if (this.getVehicleTowing() != nullptr) {
            this.authorizationChanged(this.getDriver());
            this.getVehicleTowing().authorizationChanged(this.getDriver());
         } else if (this.getVehicleTowedBy() != nullptr) {
            this.authorizationChanged(this.getVehicleTowedBy().getDriver());
            this.getVehicleTowedBy().authorizationChanged(this.getVehicleTowedBy().getDriver());
         } else {
            this.authorizationChanged(this.getDriver());
         }
      }
   }

    void breakConstraint(bool var1, bool var2) {
      if (GameServer.bServer || this.constraintTowing != -1) {
         if (!GameServer.bServer) {
            Bullet.removeConstraint(this.constraintTowing);
         }

         this.constraintTowing = -1;
         if (this.vehicleTowing != nullptr) {
            if (GameServer.bServer && !var2) {
               VehicleManager.instance.sendDetachTowing(this, this.vehicleTowing);
            }

            this.vehicleTowing.vehicleTowedBy = nullptr;
            this.vehicleTowing.constraintTowing = -1;
            if (var1) {
               this.vehicleTowingID = -1;
               this.vehicleTowing.vehicleTowedByID = -1;
            }

            this.vehicleTowing.constraintChanged();
            this.vehicleTowing = nullptr;
         }

         if (this.vehicleTowedBy != nullptr) {
            if (GameServer.bServer && !var2) {
               VehicleManager.instance.sendDetachTowing(this.vehicleTowedBy, this);
            }

            this.vehicleTowedBy.vehicleTowing = nullptr;
            this.vehicleTowedBy.constraintTowing = -1;
            if (var1) {
               this.vehicleTowedBy.vehicleTowingID = -1;
               this.vehicleTowedByID = -1;
            }

            this.vehicleTowedBy.constraintChanged();
            this.vehicleTowedBy = nullptr;
         }

         this.constraintChanged();
      }
   }

    bool canAttachTrailer(BaseVehicle var1, const std::string& var2, const std::string& var3) {
      return this.canAttachTrailer(var1, var2, var3, false);
   }

    bool canAttachTrailer(BaseVehicle var1, const std::string& var2, const std::string& var3, bool var4) {
      if (this == var1 || this.physics == nullptr || this.constraintTowing != -1) {
    return false;
      } else if (var1 != nullptr && var1.physics != nullptr && var1.constraintTowing == -1) {
    Vector3fObjectPool var6 = TL_vector3f_pool.get();
    Vector3f var7 = this.getTowingWorldPos(var2, (Vector3f)var6.alloc());
    Vector3f var8 = var1.getTowedByWorldPos(var3, (Vector3f)var6.alloc());
         if (var7 != nullptr && var8 != nullptr) {
    float var9 = IsoUtils.DistanceToSquared(var7.x, var7.y, 0.0F, var8.x, var8.y, 0.0F);
            var6.release(var7);
            var6.release(var8);
    ModelAttachment var10 = this.script.getAttachmentById(var2);
    ModelAttachment var11 = var1.script.getAttachmentById(var3);
            if (var10 != nullptr && var10.getCanAttach() != nullptr && !var10.getCanAttach().contains(var3)) {
    return false;
            } else if (var11 != nullptr && var11.getCanAttach() != nullptr && !var11.getCanAttach().contains(var2)) {
    return false;
            } else {
               DebugLog.Vehicle.trace("vidA=%d (%s) vidB=%d (%s) dist: %f", this.getId(), var2, var1.getId(), var3, var9);
    bool var12 = this.getScriptName().contains("Trailer") || var1.getScriptName().contains("Trailer");
               return var9 < (var4 ? 10.0F : (var12 ? 1.0F : 4.0F));
            }
         } else {
    return false;
         }
      } else {
    return false;
      }
   }

    void tryReconnectToTowedVehicle() {
      if (GameClient.bClient) {
    short var5 = VehicleManager.instance.getTowedVehicleID(this.VehicleID);
         if (var5 != -1) {
    BaseVehicle var6 = VehicleManager.instance.getVehicleByID(var5);
            if (var6 != nullptr) {
               if (this.canAttachTrailer(var6, this.towAttachmentSelf, this.towAttachmentOther, true)) {
                  this.addPointConstraint(nullptr, var6, this.towAttachmentSelf, this.towAttachmentOther, true);
               }
            }
         }
      } else if (this.vehicleTowing == nullptr) {
         if (this.vehicleTowingID != -1) {
    BaseVehicle var1 = nullptr;
    std::vector var2 = IsoWorld.instance.CurrentCell.getVehicles();

            for (int var3 = 0; var3 < var2.size(); var3++) {
    BaseVehicle var4 = (BaseVehicle)var2.get(var3);
               if (var4.getSqlId() == this.vehicleTowingID) {
                  var1 = var4;
                  break;
               }
            }

            if (var1 != nullptr) {
               if (this.canAttachTrailer(var1, this.towAttachmentSelf, this.towAttachmentOther, true)) {
                  this.addPointConstraint(nullptr, var1, this.towAttachmentSelf, this.towAttachmentOther, false);
               }
            }
         }
      }
   }

    void positionTrailer(BaseVehicle var1) {
      if (var1 != nullptr) {
    Vector3fObjectPool var2 = TL_vector3f_pool.get();
    Vector3f var3 = this.getTowingWorldPos("trailer", (Vector3f)var2.alloc());
    Vector3f var4 = var1.getTowedByWorldPos("trailer", (Vector3f)var2.alloc());
         if (var3 != nullptr && var4 != nullptr) {
            var4.sub(var1.x, var1.y, var1.z);
            var3.sub(var4);
    Transform var5 = var1.getWorldTransform(this.tempTransform);
            var5.origin.set(var3.x - WorldSimulation.instance.offsetX, var1.jniTransform.origin.y, var3.y - WorldSimulation.instance.offsetY);
            var1.setWorldTransform(var5);
            var1.setX(var3.x);
            var1.setLx(var3.x);
            var1.setY(var3.y);
            var1.setLy(var3.y);
            var1.setCurrent(this.getCell().getGridSquare(var3.x, var3.y, 0.0));
            this.addPointConstraint(nullptr, var1, "trailer", "trailer");
            var2.release(var3);
            var2.release(var4);
         }
      }
   }

    std::string getTowAttachmentSelf() {
      return this.towAttachmentSelf;
   }

    std::string getTowAttachmentOther() {
      return this.towAttachmentOther;
   }

    VehicleEngineRPM getVehicleEngineRPM() {
      if (this.vehicleEngineRPM == nullptr) {
         this.vehicleEngineRPM = ScriptManager.instance.getVehicleEngineRPM(this.getScript().getEngineRPMType());
         if (this.vehicleEngineRPM == nullptr) {
            DebugLog.General.warn("unknown vehicleEngineRPM \"%s\"", new Object[]{this.getScript().getEngineRPMType()});
            this.vehicleEngineRPM = std::make_unique<VehicleEngineRPM>();
         }
      }

      return this.vehicleEngineRPM;
   }



    std::vector<std::shared_ptr<BaseVehicleParameter>>& getVehicleParameters() {
      return this.vehicleParameters;
    }

      void startEvent(long var1, GameSoundClip var3, BitSet var4) {
         // OpenAL: Implement event start logic as needed
      }

    void updateEvent(long var1, GameSoundClip var3) {
      // OpenAL: setParameterValue("VehicleSpeed", this.getCurrentSpeedKmHour());
    }

      void stopEvent(long var1, GameSoundClip var3, BitSet var4) {
         // OpenAL: Implement event stop logic as needed
      }

    void stopEngineSounds() {
      if (this.emitter != nullptr) {
         for (int var1 = 0; var1 < this.new_EngineSoundId.length; var1++) {
            if (this.new_EngineSoundId[var1] != 0L) {
               this.getEmitter().stopSound(this.new_EngineSoundId[var1]);
               this.new_EngineSoundId[var1] = 0L;
            }
         }

         if (this.combinedEngineSound != 0L) {
            if (this.getEmitter().hasSustainPoints(this.combinedEngineSound)) {
               this.getEmitter().triggerCue(this.combinedEngineSound);
            } else {
               this.getEmitter().stopSound(this.combinedEngineSound);
            }

            this.combinedEngineSound = 0L;
         }
      }
   }

    BaseVehicle setSmashed(const std::string& var1) {
      return this.setSmashed(var1, false);
   }

    BaseVehicle setSmashed(const std::string& var1, bool var2) {
    std::string var3 = nullptr;
    int var4 = nullptr;
    KahluaTableImpl var5 = (KahluaTableImpl)LuaManager.env.rawget("SmashedCarDefinitions");
      if (var5 != nullptr) {
    KahluaTableImpl var6 = (KahluaTableImpl)var5.rawget("cars");
         if (var6 != nullptr) {
    KahluaTableImpl var7 = (KahluaTableImpl)var6.rawget(this.getScriptName());
            if (var7 != nullptr) {
               var3 = var7.rawgetStr(var1.toLowerCase());
               var4 = var7.rawgetInt("skin");
               if (var4 == -1) {
                  var4 = this.getSkinIndex();
               }
            }
         }
      }

    int var9 = this.getKeyId();
      if (var3 != nullptr) {
         this.removeFromWorld();
         this.permanentlyRemove();
    BaseVehicle var10 = std::make_shared<BaseVehicle>(IsoWorld.instance.CurrentCell);
         var10.setScriptName(var3);
         var10.setScript();
         var10.setSkinIndex(var4);
         var10.setX(this.x);
         var10.setY(this.y);
         var10.setZ(this.z);
         var10.setDir(this.getDir());
         var10.savedRot.set(this.savedRot);
         if (var2) {
    float var8 = this.getAngleY();
            var10.savedRot.rotationXYZ(0.0F, var8 * (float) (Math.PI / 180.0), (float) Math.PI);
         }

         var10.jniTransform.setRotation(var10.savedRot);
         if (IsoChunk.doSpawnedVehiclesInInvalidPosition(var10)) {
            var10.setSquare(this.square);
            var10.square.chunk.vehicles.push_back(var10);
            var10.chunk = var10.square.chunk;
            var10.addToWorld();
            VehiclesDB2.instance.addVehicle(var10);
         }

         var10.setGeneralPartCondition(0.5F, 60.0F);
    VehiclePart var11 = var10.getPartById("Engine");
         if (var11 != nullptr) {
            var11.setCondition(0);
         }

         var10.engineQuality = 0;
         var10.setKeyId(var9);
    return var10;
      } else {
    return this;
      }
   }

    bool isCollided(IsoGameCharacter var1) {
      if (GameClient.bClient && this.getDriver() != nullptr && !this.getDriver().isLocal()) {
    return true;
      } else {
    Vector2 var2 = this.testCollisionWithCharacter(var1, 0.20000002F, this.hitVars.collision);
         return var2 != nullptr && var2.x != -1.0F;
      }
   }

    HitVars checkCollision(IsoGameCharacter var1) {
      if (var1.isProne()) {
    int var2 = this.testCollisionWithProneCharacter(var1, true);
         if (var2 > 0) {
            this.hitVars.calc(var1, this);
            this.hitCharacter(var1, this.hitVars);
            return this.hitVars;
         } else {
    return nullptr;
         }
      } else {
         this.hitVars.calc(var1, this);
         this.hitCharacter(var1, this.hitVars);
         return this.hitVars;
      }
   }

    bool updateHitByVehicle(IsoGameCharacter var1) {
      if (var1.isVehicleCollisionActive(this) && (this.isCollided(var1) || var1.isCollidedWithVehicle()) && this.physics != nullptr) {
    HitVars var2 = this.checkCollision(var1);
         if (var2 != nullptr) {
            var1.doHitByVehicle(this, var2);
    return true;
         }
      }

    return false;
   }

    void hitCharacter(IsoGameCharacter var1, HitVars var2) {
      if (var2.dot < 0.0F && !GameServer.bServer) {
         this.ApplyImpulse(var1, var2.vehicleImpulse);
      }

    long var3 = System.currentTimeMillis();
    long var5 = (var3 - this.zombieHitTimestamp) / 1000L;
      this.zombiesHits = Math.max(this.zombiesHits - (int)var5, 0);
      if (var3 - this.zombieHitTimestamp > 700L) {
         this.zombieHitTimestamp = var3;
         this.zombiesHits++;
         this.zombiesHits = Math.min(this.zombiesHits, 20);
      }

      if (dynamic_cast<IsoPlayer*>(var1) != nullptr) {
         ((IsoPlayer)var1).setVehicleHitLocation(this);
      } else if (dynamic_cast<IsoZombie*>(var1) != nullptr) {
         ((IsoZombie)var1).setVehicleHitLocation(this);
      }

      if (var2.vehicleSpeed >= 5.0F || this.zombiesHits > 10) {
         var2.vehicleSpeed = this.getCurrentSpeedKmHour() / 5.0F;
    Vector3f var7 = (Vector3f)TL_vector3f_pool.get().alloc();
         this.getLocalPos(var1.x, var1.y, var1.z, var7);
         if (var7.z > 0.0F) {
    int var8 = this.caclulateDamageWithBodies(true);
            if (!GameClient.bClient) {
               this.addDamageFrontHitAChr(var8);
            }

            DebugLog.Vehicle.trace("Damage car front hits=%d damage=%d", this.zombiesHits, var8);
            var2.vehicleDamage = var8;
            var2.isVehicleHitFromFront = true;
         } else {
    int var9 = this.caclulateDamageWithBodies(false);
            if (!GameClient.bClient) {
               this.addDamageRearHitAChr(var9);
            }

            DebugLog.Vehicle.trace("Damage car rear hits=%d damage=%d", this.zombiesHits, var9);
            var2.vehicleDamage = var9;
            var2.isVehicleHitFromFront = false;
         }

         TL_vector3f_pool.get().release(var7);
      }
   }
}
} // namespace vehicles
} // namespace zombie
