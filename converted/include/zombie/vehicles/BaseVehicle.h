#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/FMODManager.h"
#include "fmod/fmod/FMODSoundEmitter.h"
#include "fmod/fmod/FMOD_STUDIO_PARAMETER_DESCRIPTION.h"
#include "fmod/fmod/IFMODParameterUpdater.h"
#include "org/joml/Matrix4f.h"
#include "org/joml/Quaternionf.h"
#include "org/joml/Vector2f.h"
#include "org/joml/Vector3f.h"
#include "org/joml/Vector4f.h"
#include "se/krka/kahlua/j2se/KahluaTableImpl.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/SandboxOptions.h"
#include "zombie/SoundManager.h"
#include "zombie/SystemDisabler.h"
#include "zombie/WorldSoundManager.h"
#include "zombie/ai/states/StaggerBackState.h"
#include "zombie/ai/states/ZombieFallDownState.h"
#include "zombie/audio/BaseSoundEmitter.h"
#include "zombie/audio/DummySoundEmitter.h"
#include "zombie/audio/FMODParameter.h"
#include "zombie/audio/FMODParameterList.h"
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
#include "zombie/core/skinnedmodel/model/Model.h"
#include "zombie/core/skinnedmodel/model/SkinningData.h"
#include "zombie/core/skinnedmodel/model/VehicleModelInstance.h"
#include "zombie/core/skinnedmodel/model/VehicleSubModelInstance.h"
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
#include "zombie/inventory/types/DrainableComboItem.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/inventory/types/InventoryContainer.h"
#include "zombie/inventory/types/Key.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoChunk.h"
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
#include "zombie/network/PacketTypes.h"
#include "zombie/network/PassengerMap.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/popman/ObjectPool.h"
#include "zombie/radio/ZomboidRadio.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/ModelAttachment.h"
#include "zombie/scripting/objects/ModelScript.h"
#include "zombie/scripting/objects/VehicleScript.h"
#include "zombie/ui/TextManager.h"
#include "zombie/ui/UIManager.h"
#include "zombie/util/Pool.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/Type.h"
#include "zombie/util/list/PZArrayUtil.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace vehicles {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class BaseVehicle : public IsoMovingObject {
public:
 static const float RADIUS = 0.3F;
 static const int FADE_DISTANCE = 15;
 static const int RANDOMIZE_CONTAINER_CHANCE = 100;
 static const uint8_t noAuthorization = -1;
 static const Vector3f _UNIT_Y = new Vector3f(0.0F, 1.0F, 0.0F);
 private static PolygonalMap2.VehiclePoly tempPoly = new PolygonalMap2.VehiclePoly();
 static const bool YURI_FORCE_FIELD = false;
 static bool RENDER_TO_TEXTURE = false;
 static float CENTER_OF_MASS_MAGIC = 0.7F;
 private static float[] wheelParams = new float[24];
 private static float[] physicsParams = new float[27];
 static const uint8_t POSITION_ORIENTATION_PACKET_SIZE = 102;
 static Texture vehicleShadow = nullptr;
 int justBreakConstraintTimer = 0;
 BaseVehicle wasTowedBy = nullptr;
 static const ColorInfo inf = new ColorInfo();
 private static float[] lowRiderParam = new float[4];
 private BaseVehicle.VehicleImpulse impulseFromServer = new BaseVehicle.VehicleImpulse();
 private BaseVehicle.VehicleImpulse[] impulseFromSquishedZombie = new BaseVehicle.VehicleImpulse[4];
 private ArrayList<BaseVehicle.VehicleImpulse> impulseFromHitZombie = std::make_unique<ArrayList<>>();
 const int netPlayerTimeoutMax = 30;
 const Vector4f tempVector4f = new Vector4f();
 public ArrayList<BaseVehicle.ModelInfo> models = std::make_unique<ArrayList<>>();
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
 const UpdateLimit transmissionChangeTime = new UpdateLimit(1000L);
 bool hasExtendOffset = true;
 bool hasExtendOffsetExiting = false;
 float savedPhysicsZ = Float.NaN;
 const Quaternionf savedRot = new Quaternionf();
 const Transform jniTransform = new Transform();
 float jniSpeed;
 bool jniIsCollide;
 const Vector3f jniLinearVelocity = new Vector3f();
 const Vector3f lastLinearVelocity = new Vector3f();
 public BaseVehicle.Authorization netPlayerAuthorization = BaseVehicle.Authorization.Server;
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
 public PolygonalMap2.VehiclePoly shadowCoord = new PolygonalMap2.VehiclePoly();
 public BaseVehicle.engineStateTypes engineState = BaseVehicle.engineStateTypes.Idle;
 long engineLastUpdateStateTime;
 static const int MAX_WHEELS = 4;
 static const int PHYSICS_PARAM_COUNT = 27;
 public BaseVehicle.WheelInfo[] wheelInfo = new BaseVehicle.WheelInfo[4];
 bool skidding = false;
 long skidSound;
 long ramSound;
 long ramSoundTime;
 VehicleEngineRPM vehicleEngineRPM = nullptr;
 public long[] new_EngineSoundId = new long[8];
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
 const LightbarLightsMode lightbarLightsMode = new LightbarLightsMode();
 const LightbarSirenMode lightbarSirenMode = new LightbarSirenMode();
 const IsoLightSource leftLight1 = new IsoLightSource(0, 0, 0, 1.0F, 0.0F, 0.0F, 8);
 const IsoLightSource leftLight2 = new IsoLightSource(0, 0, 0, 1.0F, 0.0F, 0.0F, 8);
 const IsoLightSource rightLight1 = new IsoLightSource(0, 0, 0, 0.0F, 0.0F, 1.0F, 8);
 const IsoLightSource rightLight2 = new IsoLightSource(0, 0, 0, 0.0F, 0.0F, 1.0F, 8);
 int leftLightIndex = -1;
 int rightLightIndex = -1;
 public BaseVehicle.ServerVehicleState[] connectionState = new BaseVehicle.ServerVehicleState[512];
 protected BaseVehicle.Passenger[] passengers = new BaseVehicle.Passenger[1];
 std::string scriptName;
 VehicleScript script;
 protected ArrayList<VehiclePart> parts = std::make_unique<ArrayList<>>();
 VehiclePart battery;
 int engineQuality;
 int engineLoudness;
 int enginePower;
 long engineCheckTime;
 protected ArrayList<VehiclePart> lights = std::make_unique<ArrayList<>>();
 bool createdModel = false;
 int skinIndex = -1;
 CarController physics;
 bool bCreated;
 protected PolygonalMap2.VehiclePoly poly = new PolygonalMap2.VehiclePoly();
 protected PolygonalMap2.VehiclePoly polyPlusRadius = new PolygonalMap2.VehiclePoly();
 bool bDoDamageOverlay = false;
 bool loaded = false;
 short updateFlags;
 long updateLockTimeout = 0L;
 const UpdateLimit limitPhysicSend = new UpdateLimit(300L);
 Vector2 limitPhysicPositionSent = nullptr;
 const UpdateLimit limitPhysicValid = new UpdateLimit(1000L);
 const UpdateLimit limitCrash = new UpdateLimit(600L);
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
 private HashMap<String, String> choosenParts = std::make_unique<HashMap<>>();
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
 private ArrayList<IsoObject> brekingObjectsList = std::make_unique<ArrayList<>>();
 const UpdateLimit limitUpdate = new UpdateLimit(333L);
 uint8_t keySpawned = 0;
 const Matrix4f vehicleTransform = new Matrix4f();
 const Matrix4f renderTransform = new Matrix4f();
 const Matrix4f tempMatrix4fLWJGL_1 = new Matrix4f();
 const Quaternionf tempQuat4f = new Quaternionf();
 const Transform tempTransform = new Transform();
 const Transform tempTransform2 = new Transform();
 const Transform tempTransform3 = new Transform();
 BaseSoundEmitter emitter;
 float brakeBetweenUpdatesSpeed = 0.0F;
 long physicActiveCheck = -1L;
 long constraintChangedTime = -1L;
 AnimationPlayer m_animPlayer = nullptr;
 std::string specificDistributionId = nullptr;
 bool bAddThumpWorldSound = false;
 const SurroundVehicle m_surroundVehicle = new SurroundVehicle(this);
 bool regulator = false;
 float regulatorSpeed = 0.0F;
 private static HashMap<String, Integer> s_PartToMaskMap = std::make_unique<HashMap<>>();
 static const uint8_t BYTE_ZERO = (byte)0;
 private HashMap<String, Byte> bloodIntensity = std::make_unique<HashMap<>>();
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
 const ParameterVehicleBrake parameterVehicleBrake = new ParameterVehicleBrake(this);
 const ParameterVehicleEngineCondition parameterVehicleEngineCondition = new ParameterVehicleEngineCondition(this);
 const ParameterVehicleGear parameterVehicleGear = new ParameterVehicleGear(this);
 const ParameterVehicleLoad parameterVehicleLoad = new ParameterVehicleLoad(this);
 const ParameterVehicleRoadMaterial parameterVehicleRoadMaterial = new ParameterVehicleRoadMaterial(this);
 const ParameterVehicleRPM parameterVehicleRPM = new ParameterVehicleRPM(this);
 const ParameterVehicleSkid parameterVehicleSkid = new ParameterVehicleSkid(this);
 const ParameterVehicleSpeed parameterVehicleSpeed = new ParameterVehicleSpeed(this);
 const ParameterVehicleSteer parameterVehicleSteer = new ParameterVehicleSteer(this);
 const ParameterVehicleTireMissing parameterVehicleTireMissing = new ParameterVehicleTireMissing(this);
 const FMODParameterList fmodParameters = new FMODParameterList();
 bool isActive = false;
 bool isStatic = false;
 const UpdateLimit physicReliableLimit = new UpdateLimit(500L);
 bool isReliable = false;
 public static ThreadLocal<BaseVehicle.Vector2ObjectPool> TL_vector2_pool = ThreadLocal.withInitial(BaseVehicle.Vector2ObjectPool::new);
 public static ThreadLocal<BaseVehicle.Vector2fObjectPool> TL_vector2f_pool = ThreadLocal.withInitial(BaseVehicle.Vector2fObjectPool::new);
 public static ThreadLocal<BaseVehicle.Vector3fObjectPool> TL_vector3f_pool = ThreadLocal.withInitial(BaseVehicle.Vector3fObjectPool::new);
 public static ThreadLocal<BaseVehicle.Matrix4fObjectPool> TL_matrix4f_pool = ThreadLocal.withInitial(BaseVehicle.Matrix4fObjectPool::new);
 public static ThreadLocal<BaseVehicle.QuaternionfObjectPool> TL_quaternionf_pool = ThreadLocal.withInitial(BaseVehicle.QuaternionfObjectPool::new);
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
 protected BaseVehicle.HitVars hitVars = new BaseVehicle.HitVars();

 int getSqlId() {
 return this->sqlID;
 }

 static Vector2 allocVector2() {
 return TL_vector2_pool.get().alloc();
 }

 static void releaseVector2(Vector2 v) {
 TL_vector2_pool.get().release(v);
 }

 static Vector3f allocVector3f() {
 return TL_vector3f_pool.get().alloc();
 }

 static void releaseVector3f(Vector3f vector3f) {
 TL_vector3f_pool.get().release(vector3f);
 }

 public BaseVehicle(IsoCell cell) {
 super(cell, false);
 this->setCollidable(false);
 this->respawnZone = new String("");
 this->scriptName = "Base.PickUpTruck";
 this->passengers[0] = new BaseVehicle.Passenger();
 this->waitFullUpdate = false;
 this->savedRot.w = 1.0F;

 for (int int0 = 0; int0 < this->wheelInfo.length; int0++) {
 this->wheelInfo[int0] = new BaseVehicle.WheelInfo();
 }

 if (GameClient.bClient) {
 this->interpolation = std::make_unique<VehicleInterpolation>();
 }

 this->setKeyId(Rand.Next(100000000);
 this->engineSpeed = 0.0;
 this->transmissionNumber = TransmissionNumber.N;
 this->rust = Rand.Next(0, 2);
 this->jniIsCollide = false;

 for (int int1 = 0; int1 < 4; int1++) {
 lowRiderParam[int1] = 0.0F;
 }

 this->fmodParameters.add(this->parameterVehicleBrake);
 this->fmodParameters.add(this->parameterVehicleEngineCondition);
 this->fmodParameters.add(this->parameterVehicleGear);
 this->fmodParameters.add(this->parameterVehicleLoad);
 this->fmodParameters.add(this->parameterVehicleRPM);
 this->fmodParameters.add(this->parameterVehicleRoadMaterial);
 this->fmodParameters.add(this->parameterVehicleSkid);
 this->fmodParameters.add(this->parameterVehicleSpeed);
 this->fmodParameters.add(this->parameterVehicleSteer);
 this->fmodParameters.add(this->parameterVehicleTireMissing);
 }

 static void LoadAllVehicleTextures() {
 DebugLog.General.println("BaseVehicle.LoadAllVehicleTextures...");

 for (VehicleScript vehicleScript : ScriptManager.instance.getAllVehicleScripts()) {
 LoadVehicleTextures(vehicleScript);
 }
 }

 static void LoadVehicleTextures(VehicleScript _script) {
 if (SystemDisabler.doVehiclesWithoutTextures) {
 VehicleScript.Skin skin0 = _script.getSkin(0);
 skin0.textureData = LoadVehicleTexture(skin0.texture);
 skin0.textureDataMask = LoadVehicleTexture("vehicles_placeholder_mask");
 skin0.textureDataDamage1Overlay = LoadVehicleTexture("vehicles_placeholder_damage1overlay");
 skin0.textureDataDamage1Shell = LoadVehicleTexture("vehicles_placeholder_damage1shell");
 skin0.textureDataDamage2Overlay = LoadVehicleTexture("vehicles_placeholder_damage2overlay");
 skin0.textureDataDamage2Shell = LoadVehicleTexture("vehicles_placeholder_damage2shell");
 skin0.textureDataLights = LoadVehicleTexture("vehicles_placeholder_lights");
 skin0.textureDataRust = LoadVehicleTexture("vehicles_placeholder_rust");
 } else {
 for (int int0 = 0; int0 < _script.getSkinCount(); int0++) {
 VehicleScript.Skin skin1 = _script.getSkin(int0);
 skin1.copyMissingFrom(_script.getTextures());
 LoadVehicleTextures(skin1);
 }
 }
 }

 static void LoadVehicleTextures(VehicleScript.Skin skin) {
 skin.textureData = LoadVehicleTexture(skin.texture);
 if (skin.textureMask != nullptr) {
 int int0 = 0;
 int0 |= 256;
 skin.textureDataMask = LoadVehicleTexture(skin.textureMask, int0);
 }

 skin.textureDataDamage1Overlay = LoadVehicleTexture(skin.textureDamage1Overlay);
 skin.textureDataDamage1Shell = LoadVehicleTexture(skin.textureDamage1Shell);
 skin.textureDataDamage2Overlay = LoadVehicleTexture(skin.textureDamage2Overlay);
 skin.textureDataDamage2Shell = LoadVehicleTexture(skin.textureDamage2Shell);
 skin.textureDataLights = LoadVehicleTexture(skin.textureLights);
 skin.textureDataRust = LoadVehicleTexture(skin.textureRust);
 skin.textureDataShadow = LoadVehicleTexture(skin.textureShadow);
 }

 static Texture LoadVehicleTexture(const std::string& name) {
 int int0 = 0;
 int0 |= TextureID.bUseCompression ? 4 : 0;
 int0 |= 256;
 return LoadVehicleTexture();
 }

 static Texture LoadVehicleTexture(const std::string& name, int flags) {
 return StringUtils.isNullOrWhitespace(name) ? nullptr : Texture.getSharedTexture("media/textures/" + name + ".png", flags);
 }

 void setNetPlayerAuthorization(BaseVehicle.Authorization _netPlayerAuthorization, int _netPlayerId) {
 this->netPlayerAuthorization = _netPlayerAuthorization;
 this->netPlayerId = (short)_netPlayerId;
 this->netPlayerTimeout = _netPlayerId == -1 ? 0 : 30;
 if (GameClient.bClient) {
 boolean boolean0 = BaseVehicle.Authorization.Local == _netPlayerAuthorization)
 || BaseVehicle.Authorization.LocalCollide == _netPlayerAuthorization);
 if (this->getVehicleTowing() != nullptr) {
 Bullet.setVehicleStatic(this, !boolean0);
 Bullet.setVehicleActive(this, boolean0);
 Bullet.setVehicleStatic(this->getVehicleTowing(), !boolean0);
 Bullet.setVehicleActive(this->getVehicleTowing(), boolean0);
 } else if (this->getVehicleTowedBy() != nullptr) {
 Bullet.setVehicleStatic(this, !boolean0);
 Bullet.setVehicleActive(this, boolean0);
 } else {
 Bullet.setVehicleStatic(this, !boolean0);
 Bullet.setVehicleActive(this, boolean0);
 }
 }

 DebugLog.Vehicle
 .trace(
 "vid%s=%d pid=%d %s",
 this->getVehicleTowing() != nullptr ? "-a" : (this->getVehicleTowedBy() != nullptr ? "-b" : ""),
 this->getId(),
 _netPlayerId,
 _netPlayerAuthorization.name()
 );
 }

 bool isNetPlayerAuthorization(BaseVehicle.Authorization _netPlayerAuthorization) {
 return this->netPlayerAuthorization == _netPlayerAuthorization);
 }

 bool isNetPlayerId(short _netPlayerId) {
 return this->netPlayerId == _netPlayerId;
 }

 short getNetPlayerId() {
 return this->netPlayerId;
 }

 std::string getAuthorizationDescription() {
 return String.format(
 "vid:%s(%d) pid:(%d) auth=%s static=%b active=%b",
 this->scriptName,
 this->VehicleID,
 this->netPlayerId,
 this->netPlayerAuthorization.name(),
 this->isStatic,
 this->isActive
 );
 }

 static float getFakeSpeedModifier() {
 if (!GameClient.bClient && !GameServer.bServer) {
 return 1.0F;
 } else {
 float float0 = (float)ServerOptions.instance.SpeedLimit.getValue();
 return 120.0F / Math.min(float0, 120.0F);
 }
 }

 bool isLocalPhysicSim() {
 return GameServer.bServer
 ? this->isNetPlayerAuthorization(BaseVehicle.Authorization.Server)
 : this->isNetPlayerAuthorization(BaseVehicle.Authorization.LocalCollide) || this->isNetPlayerAuthorization(BaseVehicle.Authorization.Local);
 }

 void addImpulse(Vector3f impulse, Vector3f rel_pos) {
 if (!this->impulseFromServer.enable) {
 this->impulseFromServer.enable = true;
 this->impulseFromServer.impulse.set(impulse);
 this->impulseFromServer.rel_pos.set(rel_pos);
 } else if (this->impulseFromServer.impulse.length() < impulse.length()) {
 this->impulseFromServer.impulse.set(impulse);
 this->impulseFromServer.rel_pos.set(rel_pos);
 this->impulseFromServer.enable = false;
 this->impulseFromServer.release();
 }
 }

 double getEngineSpeed() {
 return this->engineSpeed;
 }

 std::string getTransmissionNumberLetter() {
 return this->transmissionNumber.getString();
 }

 int getTransmissionNumber() {
 return this->transmissionNumber.getIndex();
 }

 void setClientForce(float force) {
 this->physics.clientForce = force;
 }

 float getClientForce() {
 return this->physics.clientForce;
 }

 float getForce() {
 return this->physics.EngineForce - this->physics.BrakingForce;
 }

 void doVehicleColor() {
 if (!this->isDoColor()) {
 this->colorSaturation = 0.1F;
 this->colorValue = 0.9F;
 } else {
 this->colorHue = Rand.Next(0.0F, 0.0F);
 this->colorSaturation = 0.5F;
 this->colorValue = Rand.Next(0.3F, 0.6F);
 int int0 = Rand.Next(100);
 if (int0 < 20) {
 this->colorHue = Rand.Next(0.0F, 0.03F);
 this->colorSaturation = Rand.Next(0.85F, 1.0F);
 this->colorValue = Rand.Next(0.55F, 0.85F);
 } else if (int0 < 32) {
 this->colorHue = Rand.Next(0.55F, 0.61F);
 this->colorSaturation = Rand.Next(0.85F, 1.0F);
 this->colorValue = Rand.Next(0.65F, 0.75F);
 } else if (int0 < 67) {
 this->colorHue = 0.15F;
 this->colorSaturation = Rand.Next(0.0F, 0.1F);
 this->colorValue = Rand.Next(0.7F, 0.8F);
 } else if (int0 < 89) {
 this->colorHue = Rand.Next(0.0F, 1.0F);
 this->colorSaturation = Rand.Next(0.0F, 0.1F);
 this->colorValue = Rand.Next(0.1F, 0.25F);
 } else {
 this->colorHue = Rand.Next(0.0F, 1.0F);
 this->colorSaturation = Rand.Next(0.6F, 0.75F);
 this->colorValue = Rand.Next(0.3F, 0.7F);
 }

 if (this->getScript() != nullptr) {
 if (this->getScript().getForcedHue() > -1.0F) {
 this->colorHue = this->getScript().getForcedHue();
 }

 if (this->getScript().getForcedSat() > -1.0F) {
 this->colorSaturation = this->getScript().getForcedSat();
 }

 if (this->getScript().getForcedVal() > -1.0F) {
 this->colorValue = this->getScript().getForcedVal();
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
 if (!GameClient.bClient && this->VehicleID == -1) {
 this->VehicleID = VehicleIDMap.instance.allocateID();
 if (GameServer.bServer) {
 VehicleManager.instance.registerVehicle(this);
 } else {
 VehicleIDMap.instance.put(this->VehicleID, this);
 }
 }

 if (this->script == nullptr) {
 this->setScript(this->scriptName);
 }

 if (this->script != nullptr) {
 if (this->skinIndex == -1) {
 this->setSkinIndex(Rand.Next(this->getSkinCount()));
 }

 if (!GameServer.bServer) {
 WorldSimulation.instance.create();
 }

 this->jniTransform
 .origin
 .set(
 this->getX() - WorldSimulation.instance.offsetX,
 Float.isNaN(this->savedPhysicsZ) ? this->getZ() : this->savedPhysicsZ,
 this->getY() - WorldSimulation.instance.offsetY
 );
 this->physics = new CarController(this);
 this->savedPhysicsZ = Float.NaN;
 this->createPhysicsTime = System.currentTimeMillis();
 if (!this->bCreated) {
 this->bCreated = true;
 uint8_t byte0 = 30;
 if (SandboxOptions.getInstance().RecentlySurvivorVehicles.getValue() == 1) {
 byte0 = 0;
 }

 if (SandboxOptions.getInstance().RecentlySurvivorVehicles.getValue() == 2) {
 byte0 = 10;
 }

 if (SandboxOptions.getInstance().RecentlySurvivorVehicles.getValue() == 3) {
 byte0 = 30;
 }

 if (SandboxOptions.getInstance().RecentlySurvivorVehicles.getValue() == 4) {
 byte0 = 50;
 }

 if (Rand.Next(100) < byte0) {
 this->setGoodCar(true);
 }
 }

 this->createParts();
 this->initParts();
 if (!this->createdModel) {
 ModelManager.instance.addVehicle(this);
 this->createdModel = true;
 }

 this->updateTransform();
 this->lights.clear();

 for (int int0 = 0; int0 < this->parts.size(); int0++) {
 VehiclePart part = this->parts.get(int0);
 if (part.getLight() != nullptr) {
 this->lights.add(part);
 }
 }

 this->setMaxSpeed(this->getScript().maxSpeed);
 this->setInitialMass(this->getScript().getMass());
 if (!this->getCell().getVehicles().contains(this) && !this->getCell().addVehicles.contains(this) {
 this->getCell().addVehicles.add(this);
 }

 this->square = this->getCell().getGridSquare((double)this->x, (double)this->y, (double)this->z);
 this->randomizeContainers();
 if (this->engineState == BaseVehicle.engineStateTypes.Running) {
 this->engineDoRunning();
 }

 this->updateTotalMass();
 this->bDoDamageOverlay = true;
 this->updatePartStats();
 this->mechanicalID = Rand.Next(100000);
 }
 }

 bool isPreviouslyEntered() {
 return this->previouslyEntered;
 }

 void setPreviouslyEntered(bool boolean0) {
 this->previouslyEntered = boolean0;
 }

 int getKeyId() {
 return this->keyId;
 }

 bool getKeySpawned() {
 return this->keySpawned != 0;
 }

 void putKeyToZombie(IsoZombie zombie) {
 if (Rand.Next(10) != 1) {
 InventoryItem item0 = this->createVehicleKey();
 zombie.getInventory().AddItem(item0);
 } else if (zombie.getInventory().AddItem("Base.KeyRing") instanceof InventoryContainer inventoryContainer) {
 InventoryItem item1 = this->createVehicleKey();
 inventoryContainer.getInventory().AddItem(item1);
 }
 }

 void putKeyToContainer(ItemContainer container, IsoGridSquare sq, IsoObject obj) {
 InventoryItem item = this->createVehicleKey();
 container.AddItem(item);
 if (GameServer.bServer) {
 for (int int0 = 0; int0 < GameServer.udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection = GameServer.udpEngine.connections.get(int0);
 if (udpConnection.RelevantTo(obj.square.x, obj.square.y) {
 ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
 PacketTypes.PacketType.AddInventoryItemToContainer.doPacket(byteBufferWriter);
 byteBufferWriter.putShort((short)2);
 byteBufferWriter.putInt((int)obj.getX());
 byteBufferWriter.putInt((int)obj.getY());
 byteBufferWriter.putInt((int)obj.getZ());
 int int1 = sq.getObjects().indexOf(obj);
 byteBufferWriter.putByte((byte)int1);
 byteBufferWriter.putByte((byte)obj.getContainerIndex(container);

 try {
 CompressIdenticalItems.save(byteBufferWriter.bb, item);
 } catch (Exception exception) {
 exception.printStackTrace();
 }

 PacketTypes.PacketType.AddInventoryItemToContainer.send(udpConnection);
 }
 }
 }
 }

 void putKeyToWorld(IsoGridSquare sq) {
 InventoryItem item = this->createVehicleKey();
 sq.AddWorldInventoryItem(item, 0.0F, 0.0F, 0.0F);
 }

 void addKeyToWorld() {
 if (this->haveOneDoorUnlocked() && Rand.Next(100) < 30) {
 if (Rand.Next(5) == 0) {
 this->keyIsOnDoor = true;
 this->currentKey = this->createVehicleKey();
 } else {
 this->addKeyToGloveBox();
 }
 } else if (this->haveOneDoorUnlocked() && Rand.Next(100) < 30) {
 this->keysInIgnition = true;
 this->currentKey = this->createVehicleKey();
 } else {
 if (Rand.Next(100) < 50) {
 IsoGridSquare square = this->getCell().getGridSquare((double)this->x, (double)this->y, (double)this->z);
 if (square != nullptr) {
 this->addKeyToSquare(square);
 return;
 }
 }
 }
 }

 void addKeyToGloveBox() {
 if (this->keySpawned == 0) {
 if (this->getPartById("GloveBox") != nullptr) {
 VehiclePart part = this->getPartById("GloveBox");
 InventoryItem item = this->createVehicleKey();
 part.container.addItem(item);
 this->keySpawned = 1;
 }
 }
 }

 InventoryItem createVehicleKey() {
 InventoryItem item = InventoryItemFactory.CreateItem("CarKey");
 item.setKeyId(this->getKeyId());
 item.setName(Translator.getText("IGUI_CarKey", Translator.getText("IGUI_VehicleName" + this->getScript().getName())));
 Color color = Color.HSBtoRGB(this->colorHue, this->colorSaturation * 0.5F, this->colorValue);
 item.setColor(color);
 item.setCustomColor(true);
 return item;
 }

 bool addKeyToSquare(IsoGridSquare sq) {
 bool boolean0 = false;
 void* object0 = nullptr;

 for (int int0 = 0; int0 < 3; int0++) {
 for (int int1 = sq.getX() - 10; int1 < sq.getX() + 10; int1++) {
 for (int int2 = sq.getY() - 10; int2 < sq.getY() + 10; int2++) {
 object0 = IsoWorld.instance.getCell().getGridSquare(int1, int2, int0);
 if (object0 != nullptr) {
 for (int int3 = 0; int3 < ((IsoGridSquare)object0).getObjects().size(); int3++) {
 IsoObject object1 = ((IsoGridSquare)object0).getObjects().get(int3);
 if (object1.container != nullptr
 && (
 object1.container.type == "counter")
 || object1.container.type == "officedrawers")
 || object1.container.type == "shelves")
 || object1.container.type == "desk")
 )) {
 this->putKeyToContainer(object1.container, (IsoGridSquare)object0, object1);
 boolean0 = true;
 break;
 }
 }

 for (int int4 = 0; int4 < ((IsoGridSquare)object0).getMovingObjects().size(); int4++) {
 if (((IsoGridSquare)object0).getMovingObjects().get(int4) instanceof IsoZombie) {
 ((IsoZombie)((IsoGridSquare)object0).getMovingObjects().get(int4).addItemToSpawnAtDeath(this->createVehicleKey());
 boolean0 = true;
 break;
 }
 }
 }

 if (boolean0) {
 break;
 }
 }

 if (boolean0) {
 break;
 }
 }

 if (boolean0) {
 break;
 }
 }

 if (Rand.Next(10) < 6) {
 while (!boolean0) {
 int int5 = sq.getX() - 10 + Rand.Next(20);
 int int6 = sq.getY() - 10 + Rand.Next(20);
 object0 = IsoWorld.instance.getCell().getGridSquare((double)int5, (double)int6, (double)this->z);
 if (object0 != nullptr && !((IsoGridSquare)object0).isSolid() && !((IsoGridSquare)object0).isSolidTrans() && !((IsoGridSquare)object0).HasTree()) {
 this->putKeyToWorld((IsoGridSquare)object0);
 boolean0 = true;
 break;
 }
 }
 }

 return boolean0;
 }

 void toggleLockedDoor(VehiclePart part, IsoGameCharacter chr, bool locked) {
 if (locked) {
 if (!this->canLockDoor(part, chr) {
 return;
 }

 part.getDoor().setLocked(true);
 } else {
 if (!this->canUnlockDoor(part, chr) {
 return;
 }

 part.getDoor().setLocked(false);
 }
 }

 bool canLockDoor(VehiclePart part, IsoGameCharacter chr) {
 if (part == nullptr) {
 return false;
 } else if (chr == nullptr) {
 return false;
 } else {
 VehicleDoor vehicleDoor = part.getDoor();
 if (vehicleDoor == nullptr) {
 return false;
 } else if (vehicleDoor.lockBroken) {
 return false;
 } else if (vehicleDoor.locked) {
 return false;
 } else if (this->getSeat(chr) != -1) {
 return true;
 } else if (chr.getInventory().haveThisKeyId(this->getKeyId()) != nullptr) {
 return true;
 } else {
 VehiclePart _part = part.getChildWindow();
 if (_part != nullptr && _part.getInventoryItem() == nullptr) {
 return true;
 } else {
 VehicleWindow vehicleWindow = _part == nullptr ? nullptr : _part.getWindow();
 return vehicleWindow != nullptr && (vehicleWindow.isOpen() || vehicleWindow.isDestroyed());
 }
 }
 }
 }

 bool canUnlockDoor(VehiclePart part, IsoGameCharacter chr) {
 if (part == nullptr) {
 return false;
 } else if (chr == nullptr) {
 return false;
 } else {
 VehicleDoor vehicleDoor = part.getDoor();
 if (vehicleDoor == nullptr) {
 return false;
 } else if (vehicleDoor.lockBroken) {
 return false;
 } else if (!vehicleDoor.locked) {
 return false;
 } else if (this->getSeat(chr) != -1) {
 return true;
 } else if (chr.getInventory().haveThisKeyId(this->getKeyId()) != nullptr) {
 return true;
 } else {
 VehiclePart _part = part.getChildWindow();
 if (_part != nullptr && _part.getInventoryItem() == nullptr) {
 return true;
 } else {
 VehicleWindow vehicleWindow = _part == nullptr ? nullptr : _part.getWindow();
 return vehicleWindow != nullptr && (vehicleWindow.isOpen() || vehicleWindow.isDestroyed());
 }
 }
 }
 }

 void initParts() {
 for (int int0 = 0; int0 < this->parts.size(); int0++) {
 VehiclePart part = this->parts.get(int0);
 std::string string = part.getLuaFunction("init");
 if (string != nullptr) {
 this->callLuaVoid(string, this, part);
 }
 }
 }

 void setGeneralPartCondition(float _baseQuality, float chanceToSpawnDamaged) {
 for (int int0 = 0; int0 < this->parts.size(); int0++) {
 VehiclePart part = this->parts.get(int0);
 part.setGeneralCondition(nullptr, _baseQuality, chanceToSpawnDamaged);
 }
 }

 void createParts() {
 for (int int0 = 0; int0 < this->parts.size(); int0++) {
 VehiclePart part = this->parts.get(int0);
 std::vector arrayList = part.getItemType();
 if (part.bCreated && arrayList != nullptr && !arrayList.empty() && part.getInventoryItem() == nullptr && part.getTable("install") == nullptr) {
 part.bCreated = false;
 } else if ((arrayList == nullptr || arrayList.empty()) && part.getInventoryItem() != nullptr) {
 part.item = nullptr;
 }

 if (!part.bCreated) {
 part.bCreated = true;
 std::string string = part.getLuaFunction("create");
 if (string == nullptr) {
 part.setRandomCondition(nullptr);
 } else {
 this->callLuaVoid(string, this, part);
 if (part.getCondition() == -1) {
 part.setRandomCondition(nullptr);
 }
 }
 }
 }

 if (this->hasLightbar() && this->getScript().rightSirenCol != nullptr && this->getScript().leftSirenCol != nullptr) {
 this->leftLight1.r = this->leftLight2.r = this->getScript().leftSirenCol.r;
 this->leftLight1.g = this->leftLight2.g = this->getScript().leftSirenCol.g;
 this->leftLight1.b = this->leftLight2.b = this->getScript().leftSirenCol.b;
 this->rightLight1.r = this->rightLight2.r = this->getScript().rightSirenCol.r;
 this->rightLight1.g = this->rightLight2.g = this->getScript().rightSirenCol.g;
 this->rightLight1.b = this->rightLight2.b = this->getScript().rightSirenCol.b;
 }
 }

 CarController getController() {
 return this->physics;
 }

 SurroundVehicle getSurroundVehicle() {
 return this->m_surroundVehicle;
 }

 int getSkinCount() {
 return this->script.getSkinCount();
 }

 int getSkinIndex() {
 return this->skinIndex;
 }

 void setSkinIndex(int index) {
 if (index >= 0 && index <= this->getSkinCount()) {
 this->skinIndex = index;
 }
 }

 void updateSkin() {
 if (this->sprite != nullptr && this->sprite.modelSlot != nullptr && this->sprite.modelSlot.model != nullptr) {
 VehicleModelInstance vehicleModelInstance = (VehicleModelInstance)this->sprite.modelSlot.model;
 VehicleScript.Skin skin = this->script.getTextures();
 VehicleScript vehicleScript = this->getScript();
 if (this->getSkinIndex() >= 0 && this->getSkinIndex() < vehicleScript.getSkinCount()) {
 skin = vehicleScript.getSkin(this->getSkinIndex());
 }

 vehicleModelInstance.LoadTexture(skin.texture);
 vehicleModelInstance.tex = skin.textureData;
 vehicleModelInstance.textureMask = skin.textureDataMask;
 vehicleModelInstance.textureDamage1Overlay = skin.textureDataDamage1Overlay;
 vehicleModelInstance.textureDamage1Shell = skin.textureDataDamage1Shell;
 vehicleModelInstance.textureDamage2Overlay = skin.textureDataDamage2Overlay;
 vehicleModelInstance.textureDamage2Shell = skin.textureDataDamage2Shell;
 vehicleModelInstance.textureLights = skin.textureDataLights;
 vehicleModelInstance.textureRust = skin.textureDataRust;
 if (vehicleModelInstance.tex != nullptr) {
 vehicleModelInstance.tex.bindAlways = true;
 } else {
 DebugLog.Animation.error("texture not found:", this->getSkin());
 }
 }
 }

 Texture getShadowTexture() {
 if (this->getScript() != nullptr) {
 VehicleScript.Skin skin = this->getScript().getTextures();
 if (this->getSkinIndex() >= 0 && this->getSkinIndex() < this->getScript().getSkinCount()) {
 skin = this->getScript().getSkin(this->getSkinIndex());
 }

 if (skin.textureDataShadow != nullptr) {
 return skin.textureDataShadow;
 }
 }

 if (vehicleShadow == nullptr) {
 int int0 = 0;
 int0 |= TextureID.bUseCompression ? 4 : 0;
 vehicleShadow = Texture.getSharedTexture("media/vehicleShadow.png", int0);
 }

 return vehicleShadow;
 }

 VehicleScript getScript() {
 return this->script;
 }

 void setScript(const std::string& name) {
 if (!StringUtils.isNullOrWhitespace(name) {
 this->scriptName = name;
 bool boolean0 = this->script != nullptr;
 this->script = ScriptManager.instance.getVehicle(this->scriptName);
 if (this->script == nullptr) {
 std::vector arrayList0 = ScriptManager.instance.getAllVehicleScripts();
 if (!arrayList0.empty()) {
 std::vector arrayList1 = new ArrayList();

 for (int int0 = 0; int0 < arrayList0.size(); int0++) {
 VehicleScript vehicleScript = (VehicleScript)arrayList0.get(int0);
 if (vehicleScript.getWheelCount() == 0) {
 arrayList1.add(vehicleScript);
 arrayList0.remove(int0--);
 }
 }

 bool boolean1 = this->loaded && this->parts.empty() || this->scriptName.contains("Burnt");
 if (boolean1 && !arrayList1.empty()) {
 this->script = (VehicleScript)arrayList1.get(Rand.Next(arrayList1.size()));
 } else if (!arrayList0.empty()) {
 this->script = (VehicleScript)arrayList0.get(Rand.Next(arrayList0.size()));
 }

 if (this->script != nullptr) {
 this->scriptName = this->script.getFullName();
 }
 }
 }

 this->battery = nullptr;
 this->models.clear();
 if (this->script != nullptr) {
 this->scriptName = this->script.getFullName();
 BaseVehicle.Passenger[] passengersx = this->passengers;
 this->passengers = new BaseVehicle.Passenger[this->script.getPassengerCount()];

 for (int int1 = 0; int1 < this->passengers.length; int1++) {
 if (int1 < passengersx.length) {
 this->passengers[int1] = passengersx[int1];
 } else {
 this->passengers[int1] = new BaseVehicle.Passenger();
 }
 }

 std::vector arrayList2 = new ArrayList();
 arrayList2.addAll(this->parts);
 this->parts.clear();

 for (int int2 = 0; int2 < this->script.getPartCount(); int2++) {
 VehicleScript.Part part0 = this->script.getPart(int2);
 VehiclePart part1 = nullptr;

 for (int int3 = 0; int3 < arrayList2.size(); int3++) {
 VehiclePart part2 = (VehiclePart)arrayList2.get(int3);
 if (part2.getScriptPart() != nullptr && part0.id == part2.getScriptPart().id) {
 part1 = part2;
 break;
 }

 if (part2.partId != nullptr && part0.id == part2.partId) {
 part1 = part2;
 break;
 }
 }

 if (part1 == nullptr) {
 part1 = new VehiclePart(this);
 }

 part1.setScriptPart(part0);
 part1.category = part0.category;
 part1.specificItem = part0.specificItem;
 if (part0.container != nullptr && part0.container.contentType == nullptr) {
 if (part1.getItemContainer() == nullptr) {
 ItemContainer container = new ItemContainer(part0.id, nullptr, this);
 part1.setItemContainer(container);
 container.ID = 0;
 }

 part1.getItemContainer().Capacity = part0.container.capacity;
 } else {
 part1.setItemContainer(nullptr);
 }

 if (part0.door == nullptr) {
 part1.door = nullptr;
 } else if (part1.door == nullptr) {
 part1.door = new VehicleDoor(part1);
 part1.door.init(part0.door);
 }

 if (part0.window == nullptr) {
 part1.window = nullptr;
 } else if (part1.window == nullptr) {
 part1.window = new VehicleWindow(part1);
 part1.window.init(part0.window);
 } else {
 part1.window.openable = part0.window.openable;
 }

 part1.parent = nullptr;
 if (part1.children != nullptr) {
 part1.children.clear();
 }

 this->parts.add(part1);
 if ("Battery" == part1.getId())) {
 this->battery = part1;
 }
 }

 for (int int4 = 0; int4 < this->script.getPartCount(); int4++) {
 VehiclePart part3 = this->parts.get(int4);
 VehicleScript.Part part4 = part3.getScriptPart();
 if (part4.parent != nullptr) {
 part3.parent = this->getPartById(part4.parent);
 if (part3.parent != nullptr) {
 part3.parent.addChild(part3);
 }
 }
 }

 if (!boolean0 && !this->loaded) {
 this->frontEndDurability = this->rearEndDurability = 99999;
 }

 this->frontEndDurability = Math.min(this->frontEndDurability, this->script.getFrontEndHealth());
 this->rearEndDurability = Math.min(this->rearEndDurability, this->script.getRearEndHealth());
 this->currentFrontEndDurability = this->frontEndDurability;
 this->currentRearEndDurability = this->rearEndDurability;

 for (int int5 = 0; int5 < this->script.getPartCount(); int5++) {
 VehiclePart part5 = this->parts.get(int5);
 part5.setInventoryItem(part5.item);
 }
 }

 if (!this->loaded || this->colorHue == 0.0F && this->colorSaturation == 0.0F && this->colorValue == 0.0F) {
 this->doVehicleColor();
 }

 this->m_surroundVehicle.reset();
 }
 }

 std::string getScriptName() {
 return this->scriptName;
 }

 void setScriptName(const std::string& name) {
 assert name = = nullptr || name.contains(".");

 this->scriptName = name;
 }

 void setScript() {
 this->setScript(this->scriptName);
 }

 void scriptReloaded() {
 this->tempTransform2.setIdentity();
 if (this->physics != nullptr) {
 this->getWorldTransform(this->tempTransform2);
 this->tempTransform2.basis.getUnnormalizedRotation(this->savedRot);
 this->breakConstraint(false, false);
 Bullet.removeVehicle(this->VehicleID);
 this->physics = nullptr;
 }

 if (this->createdModel) {
 ModelManager.instance.Remove(this);
 this->createdModel = false;
 }

 this->vehicleEngineRPM = nullptr;

 for (int int0 = 0; int0 < this->parts.size(); int0++) {
 VehiclePart part = this->parts.get(int0);
 part.setInventoryItem(nullptr);
 part.bCreated = false;
 }

 this->setScript(this->scriptName);
 this->createPhysics();
 if (this->script != nullptr) {
 for (int int1 = 0; int1 < this->passengers.length; int1++) {
 BaseVehicle.Passenger passenger = this->passengers[int1];
 if (passenger != nullptr && passenger.character != nullptr) {
 VehicleScript.Position position = this->getPassengerPosition(int1, "inside");
 if (position != nullptr) {
 passenger.offset.set(position.offset);
 }
 }
 }
 }

 this->polyDirty = true;
 if (this->isEngineRunning()) {
 this->engineDoShuttingDown();
 this->engineState = BaseVehicle.engineStateTypes.Idle;
 }

 if (this->addedToWorld) {
 PolygonalMap2.instance.removeVehicleFromWorld(this);
 PolygonalMap2.instance.addVehicleToWorld(this);
 }
 }

 std::string getSkin() {
 if (this->script != nullptr && this->script.getSkinCount() != 0) {
 if (this->skinIndex < 0 || this->skinIndex >= this->script.getSkinCount()) {
 this->skinIndex = Rand.Next(this->script.getSkinCount());
 }

 return this->script.getSkin(this->skinIndex).texture;
 } else {
 return "BOGUS";
 }
 }

 protected BaseVehicle.ModelInfo setModelVisible(VehiclePart part, VehicleScript.Model model, boolean boolean0) {
 for (int int0 = 0; int0 < this->models.size(); int0++) {
 BaseVehicle.ModelInfo modelInfo0 = this->models.get(int0);
 if (modelInfo0.part == part && modelInfo0.scriptModel == model) {
 if (boolean0) {
 return modelInfo0;
 }

 if (modelInfo0.m_animPlayer != nullptr) {
 modelInfo0.m_animPlayer = Pool.tryRelease(modelInfo0.m_animPlayer);
 }

 this->models.remove(int0);
 if (this->createdModel) {
 ModelManager.instance.Remove(this);
 ModelManager.instance.addVehicle(this);
 }

 part.updateFlags = (short)(part.updateFlags | 64);
 this->updateFlags = (short)(this->updateFlags | 64);
 return nullptr;
 }
 }

 if (boolean0) {
 BaseVehicle.ModelInfo modelInfo1 = new BaseVehicle.ModelInfo();
 modelInfo1.part = part;
 modelInfo1.scriptModel = model;
 modelInfo1.modelScript = ScriptManager.instance.getModelScript(model.file);
 modelInfo1.wheelIndex = part.getWheelIndex();
 this->models.add(modelInfo1);
 if (this->createdModel) {
 ModelManager.instance.Remove(this);
 ModelManager.instance.addVehicle(this);
 }

 part.updateFlags = (short)(part.updateFlags | 64);
 this->updateFlags = (short)(this->updateFlags | 64);
 return modelInfo1;
 } else {
 return nullptr;
 }
 }

 protected BaseVehicle.ModelInfo getModelInfoForPart(VehiclePart part) {
 for (int int0 = 0; int0 < this->models.size(); int0++) {
 BaseVehicle.ModelInfo modelInfo = this->models.get(int0);
 if (modelInfo.part == part) {
 return modelInfo;
 }
 }

 return nullptr;
 }

 protected VehicleScript.Passenger getScriptPassenger(int int0) {
 if (this->getScript() == nullptr) {
 return nullptr;
 } else {
 return int0 >= 0 && int0 < this->getScript().getPassengerCount() ? this->getScript().getPassenger(int0) : nullptr;
 }
 }

 int getMaxPassengers() {
 return this->passengers.length;
 }

 bool setPassenger(int seat, IsoGameCharacter chr, Vector3f offset) {
 if (seat >= 0 && seat < this->passengers.length) {
 if (seat == 0) {
 this->setNeedPartsUpdate(true);
 }

 this->passengers[seat].character = chr;
 this->passengers[seat].offset.set(offset);
 return true;
 } else {
 return false;
 }
 }

 bool clearPassenger(int seat) {
 if (seat >= 0 && seat < this->passengers.length) {
 this->passengers[seat].character = nullptr;
 this->passengers[seat].offset.set(0.0F, 0.0F, 0.0F);
 return true;
 } else {
 return false;
 }
 }

 public BaseVehicle.Passenger getPassenger(int seat) {
 return seat >= 0 && seat < this->passengers.length ? this->passengers[seat] : nullptr;
 }

 IsoGameCharacter getCharacter(int seat) {
 BaseVehicle.Passenger passenger = this->getPassenger(seat);
 return passenger != nullptr ? passenger.character : nullptr;
 }

 int getSeat(IsoGameCharacter chr) {
 for (int int0 = 0; int0 < this->getMaxPassengers(); int0++) {
 if (this->getCharacter(int0) == chr) {
 return int0;
 }
 }

 return -1;
 }

 bool isDriver(IsoGameCharacter chr) {
 return this->getSeat(chr) == 0;
 }

 Vector3f getWorldPos(Vector3f localPos, Vector3f worldPos, VehicleScript _script) {
 return this->getWorldPos(localPos.x, localPos.y, localPos.z, worldPos, _script);
 }

 Vector3f getWorldPos(float localX, float localY, float localZ, Vector3f worldPos, VehicleScript _script) {
 Transform transform = this->getWorldTransform(this->tempTransform);
 transform.origin.set(0.0F, 0.0F, 0.0F);
 worldPos.set(localX, localY, localZ);
 transform.transform(worldPos);
 float float0 = this->jniTransform.origin.x + WorldSimulation.instance.offsetX;
 float float1 = this->jniTransform.origin.z + WorldSimulation.instance.offsetY;
 float float2 = this->jniTransform.origin.y / 2.46F;
 worldPos.set(float0 + worldPos.x, float1 + worldPos.z, float2 + worldPos.y);
 return worldPos;
 }

 Vector3f getWorldPos(Vector3f localPos, Vector3f worldPos) {
 return this->getWorldPos(localPos.x, localPos.y, localPos.z, worldPos, this->getScript());
 }

 Vector3f getWorldPos(float localX, float localY, float localZ, Vector3f worldPos) {
 return this->getWorldPos(localX, localY, localZ, worldPos, this->getScript());
 }

 Vector3f getLocalPos(Vector3f worldPos, Vector3f localPos) {
 return this->getLocalPos(worldPos.x, worldPos.y, worldPos.z, localPos);
 }

 Vector3f getLocalPos(float worldX, float worldY, float worldZ, Vector3f localPos) {
 Transform transform = this->getWorldTransform(this->tempTransform);
 transform.inverse();
 localPos.set(worldX - WorldSimulation.instance.offsetX, 0.0F, worldY - WorldSimulation.instance.offsetY);
 transform.transform(localPos);
 return localPos;
 }

 Vector3f getPassengerLocalPos(int seat, Vector3f v) {
 BaseVehicle.Passenger passenger = this->getPassenger(seat);
 return passenger = = nullptr ? nullptr : v.set(this->script.getModel().getOffset()).add(passenger.offset);
 }

 Vector3f getPassengerWorldPos(int seat, Vector3f out) {
 BaseVehicle.Passenger passenger = this->getPassenger(seat);
 return passenger = = nullptr ? nullptr : this->getPassengerPositionWorldPos(passenger.offset.x, passenger.offset.y, passenger.offset.z, out);
 }

 Vector3f getPassengerPositionWorldPos(VehicleScript.Position posn, Vector3f out) {
 return this->getPassengerPositionWorldPos(posn.offset.x, posn.offset.y, posn.offset.z, out);
 }

 Vector3f getPassengerPositionWorldPos(float x, float y, float z, Vector3f out) {
 out.set(this->script.getModel().offset);
 out.add(x, y, z);
 this->getWorldPos(out.x, out.y, out.z, out);
 out.z = (int)this->getZ();
 return out;
 }

 public VehicleScript.Anim getPassengerAnim(int seat, String id) {
 VehicleScript.Passenger passenger = this->getScriptPassenger(seat);
 if (passenger == nullptr) {
 return nullptr;
 } else {
 for (int int0 = 0; int0 < passenger.anims.size(); int0++) {
 VehicleScript.Anim anim = passenger.anims.get(int0);
 if (id == anim.id) {
 return anim;
 }
 }

 return nullptr;
 }
 }

 public VehicleScript.Position getPassengerPosition(int seat, String id) {
 VehicleScript.Passenger passenger = this->getScriptPassenger(seat);
 return passenger = = nullptr ? nullptr : passenger.getPositionById(id);
 }

 VehiclePart getPassengerDoor(int seat) {
 VehicleScript.Passenger passenger = this->getScriptPassenger(seat);
 return passenger = = nullptr ? nullptr : this->getPartById(passenger.door);
 }

 VehiclePart getPassengerDoor2(int seat) {
 VehicleScript.Passenger passenger = this->getScriptPassenger(seat);
 return passenger = = nullptr ? nullptr : this->getPartById(passenger.door2);
 }

 bool isPositionOnLeftOrRight(float x, float y) {
 Vector3f vector3f0 = TL_vector3f_pool.get().alloc();
 this->getLocalPos(x, y, 0.0F, vector3f0);
 x = vector3f0.x;
 TL_vector3f_pool.get().release(vector3f0);
 Vector3f vector3f1 = this->script.getExtents();
 Vector3f vector3f2 = this->script.getCenterOfMassOffset();
 float float0 = vector3f2.x - vector3f1.x / 2.0F;
 float float1 = vector3f2.x + vector3f1.x / 2.0F;
 return x < float0 * 0.98F || x > float1 * 0.98F;
 }

 /**
 * Check if one of the seat door is unlocked
 */
 bool haveOneDoorUnlocked() {
 for (int int0 = 0; int0 < this->getPartCount(); int0++) {
 VehiclePart part = this->getPartByIndex(int0);
 if (part.getDoor() != nullptr
 && (part.getId().contains("Left") || part.getId().contains("Right"))
 && (!part.getDoor().isLocked() || part.getDoor().isOpen())) {
 return true;
 }
 }

 return false;
 }

 std::string getPassengerArea(int seat) {
 VehicleScript.Passenger passenger = this->getScriptPassenger(seat);
 return passenger = = nullptr ? nullptr : passenger.area;
 }

 void playPassengerAnim(int seat, const std::string& animId) {
 IsoGameCharacter character = this->getCharacter(seat);
 this->playPassengerAnim(seat, animId, character);
 }

 void playPassengerAnim(int seat, const std::string& animId, IsoGameCharacter chr) {
 if (chr != nullptr) {
 VehicleScript.Anim anim = this->getPassengerAnim(seat, animId);
 if (anim != nullptr) {
 this->playCharacterAnim(chr, anim, true);
 }
 }
 }

 void playPassengerSound(int seat, const std::string& animId) {
 VehicleScript.Anim anim = this->getPassengerAnim(seat, animId);
 if (anim != nullptr && anim.sound != nullptr) {
 this->playSound(anim.sound);
 }
 }

 void playPartAnim(VehiclePart part, const std::string& animId) {
 if (this->parts.contains(part) {
 VehicleScript.Anim anim = part.getAnimById(animId);
 if (anim != nullptr && !StringUtils.isNullOrWhitespace(anim.anim) {
 BaseVehicle.ModelInfo modelInfo = this->getModelInfoForPart(part);
 if (modelInfo != nullptr) {
 AnimationPlayer animationPlayer = modelInfo.getAnimationPlayer();
 if (animationPlayer != nullptr && animationPlayer.isReady()) {
 if (animationPlayer.getMultiTrack().getIndexOfTrack(modelInfo.m_track) != -1) {
 animationPlayer.getMultiTrack().removeTrack(modelInfo.m_track);
 }

 modelInfo.m_track = nullptr;
 SkinningData skinningData = animationPlayer.getSkinningData();
 if (skinningData == nullptr || skinningData.AnimationClips.containsKey(anim.anim) {
 AnimationTrack animationTrack = animationPlayer.play(anim.anim, anim.bLoop);
 modelInfo.m_track = animationTrack;
 if (animationTrack != nullptr) {
 animationTrack.setLayerIdx(0);
 animationTrack.BlendDelta = 1.0F;
 animationTrack.SpeedDelta = anim.rate;
 animationTrack.IsPlaying = anim.bAnimate;
 animationTrack.reverse = anim.bReverse;
 if (!modelInfo.modelScript.boneWeights.empty()) {
 animationTrack.setBoneWeights(modelInfo.modelScript.boneWeights);
 animationTrack.initBoneWeights(skinningData);
 }

 if (part.getWindow() != nullptr) {
 animationTrack.setCurrentTimeValue(animationTrack.getDuration() * part.getWindow().getOpenDelta());
 }
 }
 }
 }
 }
 }
 }
 }

 void playActorAnim(VehiclePart part, const std::string& animId, IsoGameCharacter chr) {
 if (chr != nullptr) {
 if (this->parts.contains(part) {
 VehicleScript.Anim anim = part.getAnimById("Actor" + animId);
 if (anim != nullptr) {
 this->playCharacterAnim(chr, anim, !"EngineDoor" == part.getId()));
 }
 }
 }
 }

 void playCharacterAnim(IsoGameCharacter character, VehicleScript.Anim anim, bool boolean0) {
 character.PlayAnimUnlooped(anim.anim);
 character.getSpriteDef().setFrameSpeedPerFrame(anim.rate);
 character.getLegsSprite().Animate = true;
 Vector3f vector3f = this->getForwardVector(TL_vector3f_pool.get().alloc());
 if (anim.angle.lengthSquared() != 0.0F) {
 Matrix4f matrix4f = TL_matrix4f_pool.get().alloc();
 matrix4f.rotationXYZ((float)Math.toRadians(anim.angle.x), (float)Math.toRadians(anim.angle.y), (float)Math.toRadians(anim.angle.z);
 vector3f.rotate(matrix4f.getNormalizedRotation(this->tempQuat4f);
 TL_matrix4f_pool.get().release(matrix4f);
 }

 Vector2 vector = TL_vector2_pool.get().alloc();
 vector.set(vector3f.x, vector3f.z);
 character.DirectionFromVector(vector);
 TL_vector2_pool.get().release(vector);
 character.setForwardDirection(vector3f.x, vector3f.z);
 if (character.getAnimationPlayer() != nullptr) {
 character.getAnimationPlayer().setTargetAngle(character.getForwardDirection().getDirection());
 if (boolean0) {
 character.getAnimationPlayer().setAngleToTarget();
 }
 }

 TL_vector3f_pool.get().release(vector3f);
 }

 void playPartSound(VehiclePart part, IsoPlayer player, const std::string& animId) {
 if (this->parts.contains(part) {
 VehicleScript.Anim anim = part.getAnimById(animId);
 if (anim != nullptr && anim.sound != nullptr) {
 this->getEmitter().playSound(anim.sound, (IsoGameCharacter)player);
 }
 }
 }

 void setCharacterPosition(IsoGameCharacter chr, int seat, const std::string& positionId) {
 VehicleScript.Passenger passenger = this->getScriptPassenger(seat);
 if (passenger != nullptr) {
 VehicleScript.Position position = passenger.getPositionById(positionId);
 if (position != nullptr) {
 if (this->getCharacter(seat) == chr) {
 this->passengers[seat].offset.set(position.offset);
 } else {
 Vector3f vector3f = TL_vector3f_pool.get().alloc();
 if (position.area == nullptr) {
 this->getPassengerPositionWorldPos(position, vector3f);
 } else {
 VehicleScript.Area area = this->script.getAreaById(position.area);
 Vector2 vector0 = TL_vector2_pool.get().alloc();
 Vector2 vector1 = this->areaPositionWorld4PlayerInteract(area, vector0);
 vector3f.x = vector1.x;
 vector3f.y = vector1.y;
 vector3f.z = 0.0F;
 TL_vector2_pool.get().release(vector0);
 }

 chr.setX(vector3f.x);
 chr.setY(vector3f.y);
 chr.setZ(0.0F);
 TL_vector3f_pool.get().release(vector3f);
 }

 if (chr instanceof IsoPlayer && ((IsoPlayer)chr).isLocalPlayer()) {
 ((IsoPlayer)chr).dirtyRecalcGridStackTime = 10.0F;
 }
 }
 }
 }

 void transmitCharacterPosition(int seat, const std::string& positionId) {
 if (GameClient.bClient) {
 VehicleManager.instance.sendPassengerPosition(this, seat, positionId);
 }
 }

 void setCharacterPositionToAnim(IsoGameCharacter chr, int seat, const std::string& animId) {
 VehicleScript.Anim anim = this->getPassengerAnim(seat, animId);
 if (anim != nullptr) {
 if (this->getCharacter(seat) == chr) {
 this->passengers[seat].offset.set(anim.offset);
 } else {
 Vector3f vector3f = this->getWorldPos(anim.offset, TL_vector3f_pool.get().alloc());
 chr.setX(vector3f.x);
 chr.setY(vector3f.y);
 chr.setZ(0.0F);
 TL_vector3f_pool.get().release(vector3f);
 }
 }
 }

 int getPassengerSwitchSeatCount(int seat) {
 VehicleScript.Passenger passenger = this->getScriptPassenger(seat);
 return passenger = = nullptr ? -1 : passenger.switchSeats.size();
 }

 public VehicleScript.Passenger.SwitchSeat getPassengerSwitchSeat(int seat, int index) {
 VehicleScript.Passenger passenger = this->getScriptPassenger(seat);
 if (passenger == nullptr) {
 return nullptr;
 } else {
 return index >= 0 && index < passenger.switchSeats.size() ? passenger.switchSeats.get(index) : nullptr;
 }
 }

 private VehicleScript.Passenger.SwitchSeat getSwitchSeat(int int0, int int2) {
 VehicleScript.Passenger passenger = this->getScriptPassenger(int0);
 if (passenger == nullptr) {
 return nullptr;
 } else {
 for (int int1 = 0; int1 < passenger.switchSeats.size(); int1++) {
 VehicleScript.Passenger.SwitchSeat switchSeat = passenger.switchSeats.get(int1);
 if (switchSeat.seat == int2 && this->getPartForSeatContainer(int2) != nullptr && this->getPartForSeatContainer(int2).getInventoryItem() != nullptr) {
 return switchSeat;
 }
 }

 return nullptr;
 }
 }

 std::string getSwitchSeatAnimName(int seatFrom, int seatTo) {
 VehicleScript.Passenger.SwitchSeat switchSeat = this->getSwitchSeat(seatFrom, seatTo);
 return switchSeat = = nullptr ? nullptr : switchSeat.anim;
 }

 float getSwitchSeatAnimRate(int seatFrom, int seatTo) {
 VehicleScript.Passenger.SwitchSeat switchSeat = this->getSwitchSeat(seatFrom, seatTo);
 return switchSeat = = nullptr ? 0.0F : switchSeat.rate;
 }

 std::string getSwitchSeatSound(int seatFrom, int seatTo) {
 VehicleScript.Passenger.SwitchSeat switchSeat = this->getSwitchSeat(seatFrom, seatTo);
 return switchSeat = = nullptr ? nullptr : switchSeat.sound;
 }

 bool canSwitchSeat(int seatFrom, int seatTo) {
 VehicleScript.Passenger.SwitchSeat switchSeat = this->getSwitchSeat(seatFrom, seatTo);
 return switchSeat != nullptr;
 }

 void switchSeat(IsoGameCharacter chr, int seatTo) {
 int int0 = this->getSeat(chr);
 if (int0 != -1) {
 this->clearPassenger(int0);
 VehicleScript.Position position = this->getPassengerPosition(seatTo, "inside");
 if (position == nullptr) {
 Vector3f vector3f = TL_vector3f_pool.get().alloc();
 vector3f.set(0.0F, 0.0F, 0.0F);
 this->setPassenger(seatTo, chr, vector3f);
 TL_vector3f_pool.get().release(vector3f);
 } else {
 this->setPassenger(seatTo, chr, position.offset);
 }
 }
 }

 void playSwitchSeatAnim(int seatFrom, int seatTo) {
 IsoGameCharacter character = this->getCharacter(seatFrom);
 if (character != nullptr) {
 VehicleScript.Passenger.SwitchSeat switchSeat = this->getSwitchSeat(seatFrom, seatTo);
 if (switchSeat != nullptr) {
 character.PlayAnimUnlooped(switchSeat.anim);
 character.getSpriteDef().setFrameSpeedPerFrame(switchSeat.rate);
 character.getLegsSprite().Animate = true;
 }
 }
 }

 bool isSeatOccupied(int seat) {
 VehiclePart part = this->getPartForSeatContainer(seat);
 return part != nullptr && part.getItemContainer() != nullptr && !part.getItemContainer().getItems().empty() ? true : this->getCharacter(seat) != nullptr;
 }

 bool isSeatInstalled(int seat) {
 VehiclePart part = this->getPartForSeatContainer(seat);
 return part != nullptr && part.getInventoryItem() != nullptr;
 }

 int getBestSeat(IsoGameCharacter chr) {
 if ((int)this->getZ() != (int)chr.getZ()) {
 return -1;
 } else if (chr.DistTo(this) > 5.0F) {
 return -1;
 } else {
 VehicleScript vehicleScript = this->getScript();
 if (vehicleScript == nullptr) {
 return -1;
 } else {
 Vector3f vector3f0 = TL_vector3f_pool.get().alloc();
 Vector3f vector3f1 = TL_vector3f_pool.get().alloc();
 Vector2 vector = TL_vector2_pool.get().alloc();

 for (int int0 = 0; int0 < vehicleScript.getPassengerCount(); int0++) {
 if (!this->isEnterBlocked(chr, int0) && !this->isSeatOccupied(int0) {
 VehicleScript.Position position = this->getPassengerPosition(int0, "outside");
 if (position != nullptr) {
 this->getPassengerPositionWorldPos(position, vector3f0);
 float float0 = vector3f0.x;
 float float1 = vector3f0.y;
 this->getPassengerPositionWorldPos(0.0F, position.offset.y, position.offset.z, vector3f1);
 vector.set(vector3f1.x - chr.getX(), vector3f1.y - chr.getY());
 vector.normalize();
 float float2 = vector.dot(chr.getForwardDirection());
 if (float2 > 0.5F && IsoUtils.DistanceTo(chr.getX(), chr.getY(), float0, float1) < 1.0F) {
 TL_vector3f_pool.get().release(vector3f0);
 TL_vector3f_pool.get().release(vector3f1);
 TL_vector2_pool.get().release(vector);
 return int0;
 }
 }

 position = this->getPassengerPosition(int0, "outside2");
 if (position != nullptr) {
 this->getPassengerPositionWorldPos(position, vector3f0);
 float float3 = vector3f0.x;
 float float4 = vector3f0.y;
 this->getPassengerPositionWorldPos(0.0F, position.offset.y, position.offset.z, vector3f1);
 vector.set(vector3f1.x - chr.getX(), vector3f1.y - chr.getY());
 vector.normalize();
 float float5 = vector.dot(chr.getForwardDirection());
 if (float5 > 0.5F && IsoUtils.DistanceTo(chr.getX(), chr.getY(), float3, float4) < 1.0F) {
 TL_vector3f_pool.get().release(vector3f0);
 TL_vector3f_pool.get().release(vector3f1);
 TL_vector2_pool.get().release(vector);
 return int0;
 }
 }
 }
 }

 TL_vector3f_pool.get().release(vector3f0);
 TL_vector3f_pool.get().release(vector3f1);
 TL_vector2_pool.get().release(vector);
 return -1;
 }
 }
 }

 void updateHasExtendOffsetForExit(IsoGameCharacter chr) {
 this->hasExtendOffsetExiting = true;
 this->updateHasExtendOffset(chr);
 this->getPoly();
 }

 void updateHasExtendOffsetForExitEnd(IsoGameCharacter chr) {
 this->hasExtendOffsetExiting = false;
 this->updateHasExtendOffset(chr);
 this->getPoly();
 }

 void updateHasExtendOffset(IsoGameCharacter chr) {
 this->hasExtendOffset = false;
 this->hasExtendOffsetExiting = false;
 }

 VehiclePart getUseablePart(IsoGameCharacter chr) {
 return this->getUseablePart(chr, true);
 }

 VehiclePart getUseablePart(IsoGameCharacter chr, bool checkDir) {
 if (chr.getVehicle() != nullptr) {
 return nullptr;
 } else if ((int)this->getZ() != (int)chr.getZ()) {
 return nullptr;
 } else if (chr.DistTo(this) > 6.0F) {
 return nullptr;
 } else {
 VehicleScript vehicleScript = this->getScript();
 if (vehicleScript == nullptr) {
 return nullptr;
 } else {
 Vector3f vector3f0 = vehicleScript.getExtents();
 Vector3f vector3f1 = vehicleScript.getCenterOfMassOffset();
 float float0 = vector3f1.z - vector3f0.z / 2.0F;
 float float1 = vector3f1.z + vector3f0.z / 2.0F;
 Vector2 vector0 = TL_vector2_pool.get().alloc();
 Vector3f vector3f2 = TL_vector3f_pool.get().alloc();

 for (int int0 = 0; int0 < this->parts.size(); int0++) {
 VehiclePart part = this->parts.get(int0);
 if (part.getArea() != nullptr && this->isInArea(part.getArea(), chr) {
 std::string string = part.getLuaFunction("use");
 if (string != nullptr && !string == "")) {
 VehicleScript.Area area = vehicleScript.getAreaById(part.getArea());
 if (area != nullptr) {
 Vector2 vector1 = this->areaPositionLocal(area, vector0);
 if (vector1 != nullptr) {
 float float2 = 0.0F;
 float float3 = 0.0F;
 float float4 = 0.0F;
 if (!(vector1.y >= float1) && !(vector1.y <= float0) {
 float4 = vector1.y;
 } else {
 float2 = vector1.x;
 }

 if (!checkDir) {
 return part;
 }

 this->getWorldPos(float2, float3, float4, vector3f2);
 vector0.set(vector3f2.x - chr.getX(), vector3f2.y - chr.getY());
 vector0.normalize();
 float float5 = vector0.dot(chr.getForwardDirection());
 if (float5 > 0.5F
 && !PolygonalMap2.instance.lineClearCollide(chr.x, chr.y, vector3f2.x, vector3f2.y, (int)chr.z, this, false, true) {
 TL_vector2_pool.get().release(vector0);
 TL_vector3f_pool.get().release(vector3f2);
 return part;
 }
 break;
 }
 }
 }
 }
 }

 TL_vector2_pool.get().release(vector0);
 TL_vector3f_pool.get().release(vector3f2);
 return nullptr;
 }
 }
 }

 VehiclePart getClosestWindow(IsoGameCharacter chr) {
 if ((int)this->getZ() != (int)chr.getZ()) {
 return nullptr;
 } else if (chr.DistTo(this) > 5.0F) {
 return nullptr;
 } else {
 Vector3f vector3f0 = this->script.getExtents();
 Vector3f vector3f1 = this->script.getCenterOfMassOffset();
 float float0 = vector3f1.z - vector3f0.z / 2.0F;
 float float1 = vector3f1.z + vector3f0.z / 2.0F;
 Vector2 vector = TL_vector2_pool.get().alloc();
 Vector3f vector3f2 = TL_vector3f_pool.get().alloc();

 for (int int0 = 0; int0 < this->parts.size(); int0++) {
 VehiclePart part = this->parts.get(int0);
 if (part.getWindow() != nullptr && part.getArea() != nullptr && this->isInArea(part.getArea(), chr) {
 VehicleScript.Area area = this->script.getAreaById(part.getArea());
 if (!(area.y >= float1) && !(area.y <= float0) {
 vector3f2.set(0.0F, 0.0F, area.y);
 } else {
 vector3f2.set(area.x, 0.0F, 0.0F);
 }

 this->getWorldPos(vector3f2, vector3f2);
 vector.set(vector3f2.x - chr.getX(), vector3f2.y - chr.getY());
 vector.normalize();
 float float2 = vector.dot(chr.getForwardDirection());
 if (float2 > 0.5F) {
 TL_vector2_pool.get().release(vector);
 TL_vector3f_pool.get().release(vector3f2);
 return part;
 }
 break;
 }
 }

 TL_vector2_pool.get().release(vector);
 TL_vector3f_pool.get().release(vector3f2);
 return nullptr;
 }
 }

 void getFacingPosition(IsoGameCharacter chr, Vector2 out) {
 Vector3f vector3f0 = this->getLocalPos(chr.getX(), chr.getY(), chr.getZ(), TL_vector3f_pool.get().alloc());
 Vector3f vector3f1 = this->script.getExtents();
 Vector3f vector3f2 = this->script.getCenterOfMassOffset();
 float float0 = vector3f2.x - vector3f1.x / 2.0F;
 float float1 = vector3f2.x + vector3f1.x / 2.0F;
 float float2 = vector3f2.z - vector3f1.z / 2.0F;
 float float3 = vector3f2.z + vector3f1.z / 2.0F;
 float float4 = 0.0F;
 float float5 = 0.0F;
 if (vector3f0.x <= 0.0F && vector3f0.z >= float2 && vector3f0.z <= float3) {
 float5 = vector3f0.z;
 } else if (vector3f0.x > 0.0F && vector3f0.z >= float2 && vector3f0.z <= float3) {
 float5 = vector3f0.z;
 } else if (vector3f0.z <= 0.0F && vector3f0.x >= float0 && vector3f0.x <= float1) {
 float4 = vector3f0.x;
 } else if (vector3f0.z > 0.0F && vector3f0.x >= float0 && vector3f0.x <= float1) {
 float4 = vector3f0.x;
 }

 this->getWorldPos(float4, 0.0F, float5, vector3f0);
 out.set(vector3f0.x, vector3f0.y);
 TL_vector3f_pool.get().release(vector3f0);
 }

 bool enter(int seat, IsoGameCharacter chr, Vector3f offset) {
 if (!GameClient.bClient) {
 VehiclesDB2.instance.updateVehicleAndTrailer(this);
 }

 if (chr == nullptr) {
 return false;
 } else if (chr.getVehicle() != nullptr && !chr.getVehicle().exit(chr) {
 return false;
 } else if (this->setPassenger(seat, chr, offset) {
 chr.setVehicle(this);
 chr.setCollidable(false);
 if (GameClient.bClient) {
 VehicleManager.instance.sendEnter(GameClient.connection, this, chr, seat);
 }

 if (chr instanceof IsoPlayer && ((IsoPlayer)chr).isLocalPlayer()) {
 ((IsoPlayer)chr).dirtyRecalcGridStackTime = 10.0F;
 }

 return true;
 } else {
 return false;
 }
 }

 bool enter(int seat, IsoGameCharacter chr) {
 if (this->getPartForSeatContainer(seat) != nullptr && this->getPartForSeatContainer(seat).getInventoryItem() != nullptr) {
 VehicleScript.Position position = this->getPassengerPosition(seat, "outside");
 return position != nullptr ? this->enter(seat, chr, position.offset) : false;
 } else {
 return false;
 }
 }

 bool enterRSync(int seat, IsoGameCharacter chr, BaseVehicle v) {
 if (chr == nullptr) {
 return false;
 } else {
 VehicleScript.Position position = this->getPassengerPosition(seat, "inside");
 if (position != nullptr) {
 if (this->setPassenger(seat, chr, position.offset) {
 chr.setVehicle(v);
 chr.setCollidable(false);
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

 bool exit(IsoGameCharacter chr) {
 if (!GameClient.bClient) {
 VehiclesDB2.instance.updateVehicleAndTrailer(this);
 }

 if (chr == nullptr) {
 return false;
 } else {
 int int0 = this->getSeat(chr);
 if (int0 == -1) {
 return false;
 } else if (this->clearPassenger(int0) {
 this->enginePower = (int)this->getScript().getEngineForce();
 chr.setVehicle(nullptr);
 chr.savedVehicleSeat = -1;
 chr.setCollidable(true);
 if (GameClient.bClient) {
 VehicleManager.instance.sendExit(GameClient.connection, this, chr, int0);
 }

 if (this->getDriver() == nullptr && this->soundHornOn) {
 this->onHornStop();
 }

 this->polyGarageCheck = true;
 this->polyDirty = true;
 return true;
 } else {
 return false;
 }
 }
 }

 bool exitRSync(IsoGameCharacter chr) {
 if (chr == nullptr) {
 return false;
 } else {
 int int0 = this->getSeat(chr);
 if (int0 == -1) {
 return false;
 } else if (this->clearPassenger(int0) {
 chr.setVehicle(nullptr);
 chr.setCollidable(true);
 if (GameClient.bClient) {
 LuaEventManager.triggerEvent("OnContainerUpdate");
 }

 return true;
 } else {
 return false;
 }
 }
 }

 bool hasRoof(int seat) {
 VehicleScript.Passenger passenger = this->getScriptPassenger(seat);
 return passenger = = nullptr ? false : passenger.hasRoof;
 }

 bool showPassenger(int seat) {
 VehicleScript.Passenger passenger = this->getScriptPassenger(seat);
 return passenger = = nullptr ? false : passenger.showPassenger;
 }

 bool showPassenger(IsoGameCharacter chr) {
 int int0 = this->getSeat(chr);
 return this->showPassenger(int0);
 }

 void save(ByteBuffer output, bool IS_DEBUG_SAVE) {
 if (this->square != nullptr) {
 float float0 = 5.0E-4F;
 this->x = PZMath.clamp(this->x, this->square.x + float0, this->square.x + 1 - float0);
 this->y = PZMath.clamp(this->y, this->square.y + float0, this->square.y + 1 - float0);
 }

 super.save(output, IS_DEBUG_SAVE);
 Quaternionf quaternionf = this->savedRot;
 Transform transform = this->getWorldTransform(this->tempTransform);
 output.putFloat(transform.origin.y);
 transform.getRotation(quaternionf);
 output.putFloat(quaternionf.x);
 output.putFloat(quaternionf.y);
 output.putFloat(quaternionf.z);
 output.putFloat(quaternionf.w);
 GameWindow.WriteStringUTF(output, this->scriptName);
 output.putInt(this->skinIndex);
 output.put((byte)(this->isEngineRunning() ? 1 : 0);
 output.putInt(this->frontEndDurability);
 output.putInt(this->rearEndDurability);
 output.putInt(this->currentFrontEndDurability);
 output.putInt(this->currentRearEndDurability);
 output.putInt(this->engineLoudness);
 output.putInt(this->engineQuality);
 output.putInt(this->keyId);
 output.put(this->keySpawned);
 output.put((byte)(this->headlightsOn ? 1 : 0);
 output.put((byte)(this->bCreated ? 1 : 0);
 output.put((byte)(this->soundHornOn ? 1 : 0);
 output.put((byte)(this->soundBackMoveOn ? 1 : 0);
 output.put((byte)this->lightbarLightsMode.get());
 output.put((byte)this->lightbarSirenMode.get());
 output.putShort((short)this->parts.size());

 for (int int0 = 0; int0 < this->parts.size(); int0++) {
 VehiclePart part = this->parts.get(int0);
 part.save(output);
 }

 output.put((byte)(this->keyIsOnDoor ? 1 : 0);
 output.put((byte)(this->hotwired ? 1 : 0);
 output.put((byte)(this->hotwiredBroken ? 1 : 0);
 output.put((byte)(this->keysInIgnition ? 1 : 0);
 output.putFloat(this->rust);
 output.putFloat(this->colorHue);
 output.putFloat(this->colorSaturation);
 output.putFloat(this->colorValue);
 output.putInt(this->enginePower);
 output.putShort(this->VehicleID);
 GameWindow.WriteString(output, nullptr);
 output.putInt(this->mechanicalID);
 output.put((byte)(this->alarmed ? 1 : 0);
 output.putDouble(this->sirenStartTime);
 if (this->getCurrentKey() != nullptr) {
 output.put((byte)1);
 this->getCurrentKey().saveWithSize(output, false);
 } else {
 output.put((byte)0);
 }

 output.put((byte)this->bloodIntensity.size());

 for (Entry entry : this->bloodIntensity.entrySet()) {
 GameWindow.WriteStringUTF(output, (String)entry.getKey());
 output.put((Byte)entry.getValue());
 }

 if (this->vehicleTowingID != -1) {
 output.put((byte)1);
 output.putInt(this->vehicleTowingID);
 GameWindow.WriteStringUTF(output, this->towAttachmentSelf);
 GameWindow.WriteStringUTF(output, this->towAttachmentOther);
 output.putFloat(this->towConstraintZOffset);
 } else {
 output.put((byte)0);
 }

 output.putFloat(this->getRegulatorSpeed());
 output.put((byte)(this->previouslyEntered ? 1 : 0);
 }

 void load(ByteBuffer input, int WorldVersion, bool IS_DEBUG_SAVE) {
 super.load(input, WorldVersion, IS_DEBUG_SAVE);
 if (this->z < 0.0F) {
 this->z = 0.0F;
 }

 if (WorldVersion >= 173) {
 this->savedPhysicsZ = PZMath.clamp(input.getFloat(), 0.0F, (int)this->z + 2.4477F);
 }

 float float0 = input.getFloat();
 float float1 = input.getFloat();
 float float2 = input.getFloat();
 float float3 = input.getFloat();
 this->savedRot.set(float0, float1, float2, float3);
 this->jniTransform
 .origin
 .set(
 this->getX() - WorldSimulation.instance.offsetX,
 Float.isNaN(this->savedPhysicsZ) ? this->z : this->savedPhysicsZ,
 this->getY() - WorldSimulation.instance.offsetY
 );
 this->jniTransform.setRotation(this->savedRot);
 this->scriptName = GameWindow.ReadStringUTF(input);
 this->skinIndex = input.getInt();
 bool boolean0 = input.get() == 1;
 if (boolean0) {
 this->engineState = BaseVehicle.engineStateTypes.Running;
 }

 this->frontEndDurability = input.getInt();
 this->rearEndDurability = input.getInt();
 this->currentFrontEndDurability = input.getInt();
 this->currentRearEndDurability = input.getInt();
 this->engineLoudness = input.getInt();
 this->engineQuality = input.getInt();
 this->engineQuality = PZMath.clamp(this->engineQuality, 0, 100);
 this->keyId = input.getInt();
 this->keySpawned = input.get();
 this->headlightsOn = input.get() == 1;
 this->bCreated = input.get() == 1;
 this->soundHornOn = input.get() == 1;
 this->soundBackMoveOn = input.get() == 1;
 this->lightbarLightsMode.set(input.get());
 this->lightbarSirenMode.set(input.get());
 short short0 = input.getShort();

 for (int int0 = 0; int0 < short0; int0++) {
 VehiclePart part = new VehiclePart(this);
 part.load(input, WorldVersion);
 this->parts.add(part);
 }

 if (WorldVersion >= 112) {
 this->keyIsOnDoor = input.get() == 1;
 this->hotwired = input.get() == 1;
 this->hotwiredBroken = input.get() == 1;
 this->keysInIgnition = input.get() == 1;
 }

 if (WorldVersion >= 116) {
 this->rust = input.getFloat();
 this->colorHue = input.getFloat();
 this->colorSaturation = input.getFloat();
 this->colorValue = input.getFloat();
 }

 if (WorldVersion >= 117) {
 this->enginePower = input.getInt();
 }

 if (WorldVersion >= 120) {
 input.getShort();
 }

 if (WorldVersion >= 122) {
 std::string string0 = GameWindow.ReadString(input);
 this->mechanicalID = input.getInt();
 }

 if (WorldVersion >= 124) {
 this->alarmed = input.get() == 1;
 }

 if (WorldVersion >= 129) {
 this->sirenStartTime = input.getDouble();
 }

 if (WorldVersion >= 133 && input.get() == 1) {
 InventoryItem item = nullptr;

 try {
 item = InventoryItem.loadItem(input, WorldVersion);
 } catch (Exception exception) {
 exception.printStackTrace();
 }

 if (item != nullptr) {
 this->setCurrentKey(item);
 }
 }

 if (WorldVersion >= 165) {
 uint8_t byte0 = input.get();

 for (int int1 = 0; int1 < byte0; int1++) {
 std::string string1 = GameWindow.ReadStringUTF(input);
 uint8_t byte1 = input.get();
 this->bloodIntensity.put(string1, byte1);
 }
 }

 if (WorldVersion >= 174) {
 if (input.get() == 1) {
 this->vehicleTowingID = input.getInt();
 this->towAttachmentSelf = GameWindow.ReadStringUTF(input);
 this->towAttachmentOther = GameWindow.ReadStringUTF(input);
 this->towConstraintZOffset = input.getFloat();
 }
 } else if (WorldVersion >= 172) {
 this->vehicleTowingID = input.getInt();
 }

 if (WorldVersion >= 188) {
 this->setRegulatorSpeed(input.getFloat());
 }

 if (WorldVersion >= 195) {
 this->previouslyEntered = input.get() == 1;
 }

 this->loaded = true;
 }

 void softReset() {
 this->keySpawned = 0;
 this->keyIsOnDoor = false;
 this->keysInIgnition = false;
 this->currentKey = nullptr;
 this->previouslyEntered = false;
 this->engineState = BaseVehicle.engineStateTypes.Idle;
 this->randomizeContainers();
 }

 void trySpawnKey() {
 if (!GameClient.bClient) {
 if (this->script != nullptr && this->script.getPartById("Engine") != nullptr) {
 if (this->keySpawned != 1) {
 if (SandboxOptions.getInstance().VehicleEasyUse.getValue()) {
 this->addKeyToGloveBox();
 } else {
 VehicleType vehicleType = VehicleType.getTypeFromName(this->getVehicleType());
 int int0 = vehicleType == nullptr ? 70 : vehicleType.getChanceToSpawnKey();
 if (Rand.Next(100) <= int0) {
 this->addKeyToWorld();
 }

 this->keySpawned = 1;
 }
 }
 }
 }
 }

 bool shouldCollideWithCharacters() {
 if (this->vehicleTowedBy != nullptr) {
 return this->vehicleTowedBy.shouldCollideWithCharacters();
 } else {
 float float0 = this->getSpeed2D();
 return this->isEngineRunning() ? float0 > 0.05F : float0 > 1.0F;
 }
 }

 bool shouldCollideWithObjects() {
 return this->vehicleTowedBy != nullptr ? this->vehicleTowedBy.shouldCollideWithObjects() : this->isEngineRunning();
 }

 void brekingObjects() {
 bool boolean0 = this->shouldCollideWithCharacters();
 bool boolean1 = this->shouldCollideWithObjects();
 if (boolean0 || boolean1) {
 Vector3f vector3f = this->script.getExtents();
 Vector2 vector0 = TL_vector2_pool.get().alloc();
 float float0 = Math.max(vector3f.x / 2.0F, vector3f.z / 2.0F) + 0.3F + 1.0F;
 int int0 = (int)Math.ceil(float0);

 for (int int1 = -int0; int1 < int0; int1++) {
 for (int int2 = -int0; int2 < int0; int2++) {
 IsoGridSquare square = this->getCell().getGridSquare((double)(this->x + int2), (double)(this->y + int1), (double)this->z);
 if (square != nullptr) {
 if (boolean1) {
 for (int int3 = 0; int3 < square.getObjects().size(); int3++) {
 IsoObject object0 = square.getObjects().get(int3);
 if (!(object0 instanceof IsoWorldInventoryObject) {
 Vector2 vector1 = nullptr;
 if (!this->brekingObjectsList.contains(object0) && object0 != nullptr && object0.getProperties() != nullptr) {
 if (object0.getProperties().Is("CarSlowFactor")) {
 vector1 = this->testCollisionWithObject(object0, 0.3F, vector0);
 }

 if (vector1 != nullptr) {
 this->brekingObjectsList.add(object0);
 if (!GameClient.bClient) {
 object0.Collision(vector1, this);
 }
 }

 if (object0.getProperties().Is("HitByCar")) {
 vector1 = this->testCollisionWithObject(object0, 0.3F, vector0);
 }

 if (vector1 != nullptr && !GameClient.bClient) {
 object0.Collision(vector1, this);
 }

 this->checkCollisionWithPlant(square, object0, vector0);
 }
 }
 }
 }

 if (boolean0) {
 for (int int4 = 0; int4 < square.getMovingObjects().size(); int4++) {
 IsoMovingObject movingObject0 = square.getMovingObjects().get(int4);
 IsoZombie zombie0 = Type.tryCastTo(movingObject0, IsoZombie.class);
 if (zombie0 != nullptr) {
 if (zombie0.isProne()) {
 this->testCollisionWithProneCharacter(zombie0, false);
 }

 zombie0.setVehicle4TestCollision(this);
 }

 if (movingObject0 instanceof IsoPlayer && movingObject0 != this->getDriver()) {
 IsoPlayer player = (IsoPlayer)movingObject0;
 player.setVehicle4TestCollision(this);
 }
 }
 }

 if (boolean1) {
 for (int int5 = 0; int5 < square.getStaticMovingObjects().size(); int5++) {
 IsoMovingObject movingObject1 = square.getStaticMovingObjects().get(int5);
 IsoDeadBody deadBody = Type.tryCastTo(movingObject1, IsoDeadBody.class);
 if (deadBody != nullptr) {
 int int6 = this->testCollisionWithCorpse(deadBody, true);
 }
 }
 }
 }
 }
 }

 float float1 = -999.0F;

 for (int int7 = 0; int7 < this->brekingObjectsList.size(); int7++) {
 IsoObject object1 = this->brekingObjectsList.get(int7);
 Vector2 vector2 = this->testCollisionWithObject(object1, 1.0F, vector0);
 if (vector2 == nullptr || !object1.getSquare().getObjects().contains(object1) {
 this->brekingObjectsList.remove(object1);
 object1.UnCollision(this);
 } else if (float1 < object1.GetVehicleSlowFactor(this) {
 float1 = object1.GetVehicleSlowFactor(this);
 }
 }

 if (float1 != -999.0F) {
 this->brekingSlowFactor = PZMath.clamp(float1, 0.0F, 34.0F);
 } else {
 this->brekingSlowFactor = 0.0F;
 }

 TL_vector2_pool.get().release(vector0);
 }
 }

 void updateVelocityMultiplier() {
 if (this->physics != nullptr && this->getScript() != nullptr) {
 Vector3f vector3f = this->getLinearVelocity(TL_vector3f_pool.get().alloc());
 vector3f.y = 0.0F;
 float float0 = vector3f.length();
 float float1 = 100000.0F;
 float float2 = 1.0F;
 if (this->getScript().getWheelCount() > 0) {
 if (float0 > 0.0F && float0 > 34.0F - this->brekingSlowFactor) {
 float1 = 34.0F - this->brekingSlowFactor;
 float2 = (34.0F - this->brekingSlowFactor) / float0;
 }
 } else if (this->getVehicleTowedBy() == nullptr) {
 float1 = 0.0F;
 float2 = 0.1F;
 }

 Bullet.setVehicleVelocityMultiplier(this->VehicleID, float1, float2);
 TL_vector3f_pool.get().release(vector3f);
 }
 }

 void playScrapePastPlantSound(IsoGridSquare square) {
 if (this->emitter != nullptr && !this->emitter.isPlaying(this->soundScrapePastPlant) {
 this->emitter.setPos(square.x + 0.5F, square.y + 0.5F, square.z);
 this->soundScrapePastPlant = this->emitter.playSoundImpl("VehicleScrapePastPlant", square);
 }
 }

 void checkCollisionWithPlant(IsoGridSquare square, IsoObject object, Vector2 vector1) {
 IsoTree tree = Type.tryCastTo(object, IsoTree.class);
 if (tree != nullptr || object.getProperties().Is("Bush")) {
 float float0 = Math.abs(this->getCurrentSpeedKmHour());
 if (!(float0 <= 1.0F) {
 Vector2 vector0 = this->testCollisionWithObject(object, 0.3F, vector1);
 if (vector0 != nullptr) {
 if (tree != nullptr && tree.getSize() == 1) {
 this->ApplyImpulse4Break(object, 0.025F);
 this->playScrapePastPlantSound(square);
 } else if (this->isPositionOnLeftOrRight(vector0.x, vector0.y) {
 this->ApplyImpulse4Break(object, 0.025F);
 this->playScrapePastPlantSound(square);
 } else if (float0 < 10.0F) {
 this->ApplyImpulse4Break(object, 0.025F);
 this->playScrapePastPlantSound(square);
 } else {
 this->ApplyImpulse4Break(object, 0.1F);
 this->playScrapePastPlantSound(square);
 }
 }
 }
 }
 }

 void damageObjects(float damage) {
 if (this->isEngineRunning()) {
 Vector3f vector3f = this->script.getExtents();
 Vector2 vector0 = TL_vector2_pool.get().alloc();
 float float0 = Math.max(vector3f.x / 2.0F, vector3f.z / 2.0F) + 0.3F + 1.0F;
 int int0 = (int)Math.ceil(float0);

 for (int int1 = -int0; int1 < int0; int1++) {
 for (int int2 = -int0; int2 < int0; int2++) {
 IsoGridSquare square0 = this->getCell().getGridSquare((double)(this->x + int2), (double)(this->y + int1), (double)this->z);
 if (square0 != nullptr) {
 for (int int3 = 0; int3 < square0.getObjects().size(); int3++) {
 IsoObject object = square0.getObjects().get(int3);
 Vector2 vector1 = nullptr;
 if (object instanceof IsoTree) {
 vector1 = this->testCollisionWithObject(object, 2.0F, vector0);
 if (vector1 != nullptr) {
 object.setRenderEffect(RenderEffectType.Hit_Tree_Shudder);
 }
 }

 if (vector1 == nullptr && object instanceof IsoWindow) {
 vector1 = this->testCollisionWithObject(object, 1.0F, vector0);
 }

 if (vector1 == nullptr
 && object.sprite != nullptr
 && (object.sprite.getProperties().Is("HitByCar") || object.sprite.getProperties().Is("CarSlowFactor"))) {
 vector1 = this->testCollisionWithObject(object, 1.0F, vector0);
 }

 if (vector1 == nullptr) {
 IsoGridSquare square1 = this->getCell().getGridSquare((double)(this->x + int2), (double)(this->y + int1), 1.0);
 if (square1 != nullptr && square1.getHasTypes().isSet(IsoObjectType.lightswitch) {
 vector1 = this->testCollisionWithObject(object, 1.0F, vector0);
 }
 }

 if (vector1 == nullptr) {
 IsoGridSquare square2 = this->getCell().getGridSquare((double)(this->x + int2), (double)(this->y + int1), 0.0);
 if (square2 != nullptr && square2.getHasTypes().isSet(IsoObjectType.lightswitch) {
 vector1 = this->testCollisionWithObject(object, 1.0F, vector0);
 }
 }

 if (vector1 != nullptr) {
 object.Hit(vector1, this, damage);
 }
 }
 }
 }
 }

 TL_vector2_pool.get().release(vector0);
 }
 }

 void update() {
 if (this->removedFromWorld) {
 DebugLog.Vehicle.debugln("vehicle update() removedFromWorld=true id=%d", this->VehicleID);
 } else if (!this->getCell().vehicles.contains(this) {
 DebugLog.Vehicle.debugln("vehicle update() not in cell.vehicles list id=%d x=%f y=%f %s", this->VehicleID, this->x, this->y, this);
 this->getCell().getRemoveList().add(this);
 } else {
 if (this->chunk == nullptr) {
 DebugLog.Vehicle.debugln("vehicle update() chunk=nullptr id=%d x=%f y=%f", this->VehicleID, this->x, this->y);
 } else if (!this->chunk.vehicles.contains(this) {
 DebugLog.Vehicle.debugln("vehicle update() not in chunk.vehicles list id=%d x=%f y=%f", this->VehicleID, this->x, this->y);
 if (GameClient.bClient) {
 VehicleManager.instance.sendRequestGetPosition(this->VehicleID, PacketTypes.PacketType.VehiclesUnreliable);
 }
 } else if (!GameServer.bServer && this->chunk.refs.empty()) {
 DebugLog.Vehicle.debugln("vehicle update() chunk was unloaded id=%d", this->VehicleID);
 this->removeFromWorld();
 return;
 }

 super.update();
 if (GameClient.bClient || GameServer.bServer) {
 this->isReliable = this->physicReliableLimit.Check();
 }

 if (GameClient.bClient && this->hasAuthorization(GameClient.connection) {
 this->updatePhysicsNetwork();
 }

 if (this->getVehicleTowing() != nullptr && this->getDriver() != nullptr) {
 float float0 = 2.5F;
 if (this->getVehicleTowing().getPartCount() == 0) {
 float0 = 12.0F;
 }

 if (this->getVehicleTowing().scriptName == "Base.Trailer")) {
 VehiclePart part0 = this->getVehicleTowing().getPartById("TrailerTrunk");
 if (this->getCurrentSpeedKmHour() > 30.0F && part0.getCondition() < 50 && !part0.container.Items.empty()) {
 std::vector arrayList = new ArrayList();

 for (int int0 = 0; int0 < part0.container.Items.size(); int0++) {
 if (part0.container.Items.get(int0).getWeight() >= 3.5) {
 arrayList.add(part0.container.Items.get(int0);
 }
 }

 if (!arrayList.empty()) {
 int int1 = part0.getCondition();
 int int2 = 0;
 int int3 = 0;

 for (int int4 = 0; int4 < this->getVehicleTowing().parts.size(); int4++) {
 VehiclePart part1 = this->getVehicleTowing().getPartByIndex(int4);
 if (part1 != nullptr && part1.item != nullptr) {
 if (part1.partId != nullptr && part1.partId.contains("Suspension")) {
 int2 += part1.getCondition();
 } else if (part1.partId != nullptr && part1.partId.contains("Tire")) {
 int3 += part1.getCondition();
 }
 }
 }

 float float1 = this->parameterVehicleSteer.getCurrentValue();
 int int5 = (int)(
 Math.pow(100 - int1 * 2, 2.0)
 * 0.3
 * (1.0 + (100 - int2 / 2) * 0.005)
 * (1.0 + (100 - int2 / 2) * 0.005)
 * (1.0F + float1 / 3.0F)
 );
 if (Rand.Next(0, Math.max(10000 - int5, 1) == 0) {
 InventoryItem item = (InventoryItem)arrayList.get(Rand.Next(0, arrayList.size()));
 item.setCondition(item.getCondition() - item.getConditionMax() / 10);
 part0.getSquare().AddWorldInventoryItem(item, Rand.Next(0.0F, 0.5F), Rand.Next(0.0F, 0.5F), 0.0F);
 part0.container.Items.remove(item);
 part0.getSquare().playSound("thumpa2");
 }
 }
 }
 }
 }

 if (this->getVehicleTowedBy() != nullptr && this->getDriver() != nullptr) {
 float float2 = 2.5F;
 if (this->getVehicleTowedBy().getPartCount() == 0) {
 float2 = 12.0F;
 }
 }

 if (this->physics != nullptr && this->vehicleTowingID != -1 && this->vehicleTowing == nullptr) {
 this->tryReconnectToTowedVehicle();
 }

 bool boolean0 = false;
 bool boolean1 = false;
 if (this->getVehicleTowedBy() != nullptr && this->getVehicleTowedBy().getController() != nullptr) {
 boolean0 = this->getVehicleTowedBy() != nullptr && this->getVehicleTowedBy().getController().isEnable;
 boolean1 = this->getVehicleTowing() != nullptr && this->getVehicleTowing().getDriver() != nullptr;
 }

 if (this->physics != nullptr) {
 bool boolean2 = this->getDriver() != nullptr || boolean0 || boolean1;
 long long0 = System.currentTimeMillis();
 if (this->constraintChangedTime != -1L) {
 if (this->constraintChangedTime + 3500L < long0) {
 this->constraintChangedTime = -1L;
 if (!boolean2 && this->physicActiveCheck < long0) {
 this->setPhysicsActive(false);
 }
 }
 } else {
 if (this->physicActiveCheck != -1L && (boolean2 || !this->physics.isEnable) {
 this->physicActiveCheck = -1L;
 }

 if (!boolean2 && this->physics.isEnable && this->physicActiveCheck != -1L && this->physicActiveCheck < long0) {
 this->physicActiveCheck = -1L;
 this->setPhysicsActive(false);
 }
 }

 if (this->getVehicleTowedBy() != nullptr && this->getScript().getWheelCount() > 0) {
 this->physics.updateTrailer();
 } else if (this->getDriver() == nullptr && !GameServer.bServer) {
 this->physics.checkShouldBeActive();
 }

 this->doAlarm();
 BaseVehicle.VehicleImpulse vehicleImpulse0 = this->impulseFromServer;
 if (!GameServer.bServer && vehicleImpulse0 != nullptr && vehicleImpulse0.enable) {
 vehicleImpulse0.enable = false;
 float float3 = 1.0F;
 Bullet.applyCentralForceToVehicle(
 this->VehicleID, vehicleImpulse0.impulse.x * float3, vehicleImpulse0.impulse.y * float3, vehicleImpulse0.impulse.z * float3
 );
 Vector3f vector3f0 = vehicleImpulse0.rel_pos.cross(vehicleImpulse0.impulse, TL_vector3f_pool.get().alloc());
 Bullet.applyTorqueToVehicle(this->VehicleID, vector3f0.x * float3, vector3f0.y * float3, vector3f0.z * float3);
 TL_vector3f_pool.get().release(vector3f0);
 }

 this->applyImpulseFromHitZombies();
 this->applyImpulseFromProneCharacters();
 short short0 = 1000;
 if (System.currentTimeMillis() - this->engineCheckTime > short0 && !GameClient.bClient) {
 this->engineCheckTime = System.currentTimeMillis();
 if (!GameClient.bClient) {
 if (this->engineState != BaseVehicle.engineStateTypes.Idle) {
 int int6 = (int)(this->engineLoudness * this->engineSpeed / 2500.0);
 double double0 = Math.min(this->getEngineSpeed(), 2000.0);
 int6 = (int)(int6 * (1.0 + double0 / 4000.0);
 int int7 = 120;
 if (GameServer.bServer) {
 int7 = (int)(int7 * ServerOptions.getInstance().CarEngineAttractionModifier.getValue());
 int6 = (int)(int6 * ServerOptions.getInstance().CarEngineAttractionModifier.getValue());
 }

 if (Rand.Next((int)(int7 * GameTime.instance.getInvMultiplier())) == 0) {
 WorldSoundManager.instance
 .addSoundRepeating(this, (int)this->getX(), (int)this->getY(), (int)this->getZ(), Math.max(8, int6), int6 / 40, false);
 }

 if (Rand.Next((int)((int7 - 85) * GameTime.instance.getInvMultiplier())) == 0) {
 WorldSoundManager.instance
 .addSoundRepeating(this, (int)this->getX(), (int)this->getY(), (int)this->getZ(), Math.max(8, int6 / 2), int6 / 40, false);
 }

 if (Rand.Next((int)((int7 - 110) * GameTime.instance.getInvMultiplier())) == 0) {
 WorldSoundManager.instance
 .addSoundRepeating(this, (int)this->getX(), (int)this->getY(), (int)this->getZ(), Math.max(8, int6 / 4), int6 / 40, false);
 }

 WorldSoundManager.instance
 .addSoundRepeating(this, (int)this->getX(), (int)this->getY(), (int)this->getZ(), Math.max(8, int6 / 6), int6 / 40, false);
 }

 if (this->lightbarSirenMode.isEnable() && this->getBatteryCharge() > 0.0F) {
 WorldSoundManager.instance.addSoundRepeating(this, (int)this->getX(), (int)this->getY(), (int)this->getZ(), 100, 60, false);
 }
 }

 if (this->engineState == BaseVehicle.engineStateTypes.Running && !this->isEngineWorking()) {
 this->shutOff();
 }

 if (this->engineState == BaseVehicle.engineStateTypes.Running) {
 VehiclePart part2 = this->getPartById("Engine");
 if (part2 != nullptr && part2.getCondition() < 50 && Rand.Next(Rand.AdjustForFramerate(part2.getCondition() * 12) == 0) {
 this->shutOff();
 }
 }

 if (this->engineState == BaseVehicle.engineStateTypes.Starting) {
 this->updateEngineStarting();
 }

 if (this->engineState == BaseVehicle.engineStateTypes.RetryingStarting && System.currentTimeMillis() - this->engineLastUpdateStateTime > 10L) {
 this->engineDoStarting();
 }

 if (this->engineState == BaseVehicle.engineStateTypes.StartingSuccess && System.currentTimeMillis() - this->engineLastUpdateStateTime > 500L) {
 this->engineDoRunning();
 }

 if (this->engineState == BaseVehicle.engineStateTypes.StartingFailed && System.currentTimeMillis() - this->engineLastUpdateStateTime > 500L) {
 this->engineDoIdle();
 }

 if (this->engineState == BaseVehicle.engineStateTypes.StartingFailedNoPower
 && System.currentTimeMillis() - this->engineLastUpdateStateTime > 500L) {
 this->engineDoIdle();
 }

 if (this->engineState == BaseVehicle.engineStateTypes.Stalling && System.currentTimeMillis() - this->engineLastUpdateStateTime > 3000L) {
 this->engineDoIdle();
 }

 if (this->engineState == BaseVehicle.engineStateTypes.ShutingDown && System.currentTimeMillis() - this->engineLastUpdateStateTime > 2000L) {
 this->engineDoIdle();
 }
 }

 if (this->getDriver() == nullptr && !boolean0) {
 this->getController().park();
 }

 this->setX(this->jniTransform.origin.x + WorldSimulation.instance.offsetX);
 this->setY(this->jniTransform.origin.z + WorldSimulation.instance.offsetY);
 this->setZ(0.0F);
 IsoGridSquare square = this->getCell().getGridSquare((double)this->x, (double)this->y, (double)this->z);
 if (square == nullptr && !this->chunk.refs.empty()) {
 float float4 = 5.0E-4F;
 int int8 = this->chunk.wx * 10;
 int int9 = this->chunk.wy * 10;
 int int10 = int8 + 10;
 int int11 = int9 + 10;
 float float5 = this->x;
 float float6 = this->y;
 this->x = Math.max(this->x, int8 + float4);
 this->x = Math.min(this->x, int10 - float4);
 this->y = Math.max(this->y, int9 + float4);
 this->y = Math.min(this->y, int11 - float4);
 this->z = 0.2F;
 Transform transform0 = this->tempTransform;
 Transform transform1 = this->tempTransform2;
 this->getWorldTransform(transform0);
 transform1.basis.set(transform0.basis);
 transform1.origin.set(this->x - WorldSimulation.instance.offsetX, this->z, this->y - WorldSimulation.instance.offsetY);
 this->setWorldTransform(transform1);
 this->current = this->getCell().getGridSquare((double)this->x, (double)this->y, (double)this->z);
 DebugLog.Vehicle.debugln("Vehicle vid=%d is moved into an unloaded area (%f;%f)", this->VehicleID, this->x, this->y);
 }

 if (this->current != nullptr && this->current.chunk != nullptr) {
 if (this->current.getChunk() != this->chunk) {
 assert this->chunk.vehicles.contains(this);

 this->chunk.vehicles.remove(this);
 this->chunk = this->current.getChunk();
 if (!GameServer.bServer && this->chunk.refs.empty()) {
 DebugLog.Vehicle.debugln("BaseVehicle.update() added to unloaded chunk id=%d", this->VehicleID);
 }

 assert !this->chunk.vehicles.contains(this);

 this->chunk.vehicles.add(this);
 IsoChunk.addFromCheckedVehicles(this);
 }
 } else {
 bool boolean3 = false;
 }

 this->updateTransform();
 Vector3f vector3f1 = allocVector3f().set(this->jniLinearVelocity);
 if (this->jniIsCollide && this->limitCrash.Check()) {
 this->jniIsCollide = false;
 this->limitCrash.Reset();
 Vector3f vector3f2 = allocVector3f();
 vector3f2.set(vector3f1).sub(this->lastLinearVelocity);
 vector3f2.y = 0.0F;
 float float7 = vector3f2.length();
 DebugLog.Vehicle
 .debugln(
 "Vehicle vid=%d velocity last=%s/%f current=%s/%f delta=%f",
 this->VehicleID,
 this->lastLinearVelocity,
 this->lastLinearVelocity.length(),
 vector3f1,
 vector3f1.length(),
 float7
 );
 if (vector3f1.lengthSquared() > this->lastLinearVelocity.lengthSquared() && float7 > 6.0F) {
 DebugLog.Vehicle.trace("Vehicle vid=%d got sharp speed increase delta=%f", this->VehicleID, float7);
 float7 = 6.0F;
 }

 if (float7 > 1.0F) {
 if (this->lastLinearVelocity.length() < 6.0F) {
 float7 /= 3.0F;
 }

 DebugLog.Vehicle.trace("Vehicle vid=%d crash delta=%f", this->VehicleID, float7);
 Vector3f vector3f3 = this->getForwardVector(allocVector3f());
 float float8 = vector3f2.dot(vector3f3);
 releaseVector3f(vector3f3);
 this->crash(float7 * 3.0F, float8 < 0.0F);
 this->damageObjects(float7 * 30.0F);
 }

 releaseVector3f(vector3f2);
 }

 this->lastLinearVelocity.set(vector3f1);
 releaseVector3f(vector3f1);
 }

 if (this->soundHornOn && this->hornemitter != nullptr) {
 this->hornemitter.setPos(this->getX(), this->getY(), this->getZ());
 }

 for (int int12 = 0; int12 < this->impulseFromSquishedZombie.length; int12++) {
 BaseVehicle.VehicleImpulse vehicleImpulse1 = this->impulseFromSquishedZombie[int12];
 if (vehicleImpulse1 != nullptr) {
 vehicleImpulse1.enable = false;
 }
 }

 this->updateSounds();
 this->brekingObjects();
 if (this->bAddThumpWorldSound) {
 this->bAddThumpWorldSound = false;
 WorldSoundManager.instance.addSound(this, (int)this->x, (int)this->y, (int)this->z, 20, 20, true);
 }

 if (this->script.getLightbar().enable && this->lightbarLightsMode.isEnable() && this->getBatteryCharge() > 0.0F) {
 this->lightbarLightsMode.update();
 }

 this->updateWorldLights();

 for (int int13 = 0; int13 < IsoPlayer.numPlayers; int13++) {
 if (this->current == nullptr || !this->current.lighting[int13].bCanSee()) {
 this->setTargetAlpha(int13, 0.0F);
 }

 IsoPlayer player = IsoPlayer.players[int13];
 if (player != nullptr && this->DistToSquared(player) < 225.0F) {
 this->setTargetAlpha(int13, 1.0F);
 }
 }

 for (int int14 = 0; int14 < this->getScript().getPassengerCount(); int14++) {
 if (this->getCharacter(int14) != nullptr) {
 Vector3f vector3f4 = this->getPassengerWorldPos(int14, TL_vector3f_pool.get().alloc());
 this->getCharacter(int14).setX(vector3f4.x);
 this->getCharacter(int14).setY(vector3f4.y);
 this->getCharacter(int14).setZ(vector3f4.z * 1.0F);
 TL_vector3f_pool.get().release(vector3f4);
 }
 }

 VehiclePart part3 = this->getPartById("lightbar");
 if (part3 != nullptr && this->lightbarLightsMode.isEnable() && part3.getCondition() == 0 && !GameClient.bClient) {
 this->setLightbarLightsMode(0);
 }

 if (part3 != nullptr && this->lightbarSirenMode.isEnable() && part3.getCondition() == 0 && !GameClient.bClient) {
 this->setLightbarSirenMode(0);
 }

 if (!this->needPartsUpdate() && !this->isMechanicUIOpen()) {
 this->drainBatteryUpdateHack();
 } else {
 this->updateParts();
 }

 if (this->engineState == BaseVehicle.engineStateTypes.Running || boolean0) {
 this->updateBulletStats();
 }

 if (this->bDoDamageOverlay) {
 this->bDoDamageOverlay = false;
 this->doDamageOverlay();
 }

 if (GameClient.bClient) {
 this->checkPhysicsValidWithServer();
 }

 VehiclePart part4 = this->getPartById("GasTank");
 if (part4 != nullptr && part4.getContainerContentAmount() > part4.getContainerCapacity()) {
 part4.setContainerContentAmount(part4.getContainerCapacity());
 }

 bool boolean4 = false;

 for (int int15 = 0; int15 < this->getMaxPassengers(); int15++) {
 BaseVehicle.Passenger passenger = this->getPassenger(int15);
 if (passenger.character != nullptr) {
 boolean4 = true;
 break;
 }
 }

 if (boolean4) {
 this->m_surroundVehicle.update();
 }

 if (!GameServer.bServer) {
 if (this->physics != nullptr) {
 Bullet.setVehicleMass(this->VehicleID, this->getFudgedMass());
 }

 this->updateVelocityMultiplier();
 }
 }
 }

 void updateEngineStarting() {
 if (this->getBatteryCharge() <= 0.1F) {
 this->engineDoStartingFailedNoPower();
 } else {
 VehiclePart part = this->getPartById("GasTank");
 if (part != nullptr && part.getContainerContentAmount() <= 0.0F) {
 this->engineDoStartingFailed();
 } else {
 int int0 = 0;
 float float0 = ClimateManager.getInstance().getAirTemperatureForSquare(this->getSquare());
 if (this->engineQuality < 65 && float0 <= 2.0F) {
 int0 = Math.min((2 - (int)float0) * 2, 30);
 }

 if (!SandboxOptions.instance.VehicleEasyUse.getValue() && this->engineQuality < 100 && Rand.Next(this->engineQuality + 50 - int0) <= 30) {
 this->engineDoStartingFailed();
 } else {
 if (Rand.Next(this->engineQuality) != 0) {
 this->engineDoStartingSuccess();
 } else {
 this->engineDoRetryingStarting();
 }
 }
 }
 }
 }

 void applyImpulseFromHitZombies() {
 if (!this->impulseFromHitZombie.empty()) {
 if ((!GameClient.bClient || this->hasAuthorization(GameClient.connection) && !GameServer.bServer) {
 Vector3f vector3f0 = TL_vector3f_pool.get().alloc().set(0.0F, 0.0F, 0.0F);
 Vector3f vector3f1 = TL_vector3f_pool.get().alloc().set(0.0F, 0.0F, 0.0F);
 Vector3f vector3f2 = TL_vector3f_pool.get().alloc().set(0.0F, 0.0F, 0.0F);
 int int0 = this->impulseFromHitZombie.size();

 for (int int1 = 0; int1 < int0; int1++) {
 BaseVehicle.VehicleImpulse vehicleImpulse0 = this->impulseFromHitZombie.get(int1);
 vector3f0.add(vehicleImpulse0.impulse);
 vector3f1.add(vehicleImpulse0.rel_pos.cross(vehicleImpulse0.impulse, vector3f2);
 vehicleImpulse0.release();
 vehicleImpulse0.enable = false;
 }

 this->impulseFromHitZombie.clear();
 float float0 = 7.0F * this->getFudgedMass();
 if (vector3f0.lengthSquared() > float0 * float0) {
 vector3f0.mul(float0 / vector3f0.length());
 }

 float float1 = 30.0F;
 Bullet.applyCentralForceToVehicle(this->VehicleID, vector3f0.x * float1, vector3f0.y * float1, vector3f0.z * float1);
 Bullet.applyTorqueToVehicle(this->VehicleID, vector3f1.x * float1, vector3f1.y * float1, vector3f1.z * float1);
 if (GameServer.bServer) {
 }

 TL_vector3f_pool.get().release(vector3f0);
 TL_vector3f_pool.get().release(vector3f1);
 TL_vector3f_pool.get().release(vector3f2);
 } else {
 int int2 = 0;

 for (int int3 = this->impulseFromHitZombie.size(); int2 < int3; int2++) {
 BaseVehicle.VehicleImpulse vehicleImpulse1 = this->impulseFromHitZombie.get(int2);
 vehicleImpulse1.release();
 vehicleImpulse1.enable = false;
 }

 this->impulseFromHitZombie.clear();
 }
 }
 }

 void applyImpulseFromProneCharacters() {
 if ((!GameClient.bClient || this->hasAuthorization(GameClient.connection) && !GameServer.bServer) {
 bool boolean0 = PZArrayUtil.contains(this->impulseFromSquishedZombie, vehicleImpulsex -> vehicleImpulsex != nullptr && vehicleImpulsex.enable);
 if (boolean0) {
 Vector3f vector3f0 = TL_vector3f_pool.get().alloc().set(0.0F, 0.0F, 0.0F);
 Vector3f vector3f1 = TL_vector3f_pool.get().alloc().set(0.0F, 0.0F, 0.0F);
 Vector3f vector3f2 = TL_vector3f_pool.get().alloc();

 for (int int0 = 0; int0 < this->impulseFromSquishedZombie.length; int0++) {
 BaseVehicle.VehicleImpulse vehicleImpulse = this->impulseFromSquishedZombie[int0];
 if (vehicleImpulse != nullptr && vehicleImpulse.enable) {
 vector3f0.add(vehicleImpulse.impulse);
 vector3f1.add(vehicleImpulse.rel_pos.cross(vehicleImpulse.impulse, vector3f2);
 vehicleImpulse.enable = false;
 }
 }

 if (vector3f0.lengthSquared() > 0.0F) {
 float float0 = this->getFudgedMass() * 0.15F;
 if (vector3f0.lengthSquared() > float0 * float0) {
 vector3f0.mul(float0 / vector3f0.length());
 }

 float float1 = 30.0F;
 Bullet.applyCentralForceToVehicle(this->VehicleID, vector3f0.x * float1, vector3f0.y * float1, vector3f0.z * float1);
 Bullet.applyTorqueToVehicle(this->VehicleID, vector3f1.x * float1, vector3f1.y * float1, vector3f1.z * float1);
 }

 TL_vector3f_pool.get().release(vector3f0);
 TL_vector3f_pool.get().release(vector3f1);
 TL_vector3f_pool.get().release(vector3f2);
 }
 }
 }

 float getFudgedMass() {
 if (this->getScriptName().contains("Trailer")) {
 return this->getMass();
 } else {
 BaseVehicle vehicle1 = this->getVehicleTowedBy();
 if (vehicle1 != nullptr && vehicle1.getDriver() != nullptr && vehicle1.isEngineRunning()) {
 float float0 = Math.max(250.0F, vehicle1.getMass() / 3.7F);
 if (this->getScript().getWheelCount() == 0) {
 float0 = Math.min(float0, 200.0F);
 }

 return float0;
 } else {
 return this->getMass();
 }
 }
 }

 bool isNullChunk(int int0, int int1) {
 if (!IsoWorld.instance.getMetaGrid().isValidChunk(int0, int1) {
 return false;
 } else if (GameClient.bClient && !ClientServerMap.isChunkLoaded(int0, int1) {
 return true;
 } else {
 return GameClient.bClient && !PassengerMap.isChunkLoaded(this, int0, int1) ? true : this->getCell().getChunk(int0, int1) == nullptr;
 }
 }

 bool isInvalidChunkAround() {
 Vector3f vector3f = this->getLinearVelocity(TL_vector3f_pool.get().alloc());
 float float0 = Math.abs(vector3f.x);
 float float1 = Math.abs(vector3f.z);
 bool boolean0 = vector3f.x < 0.0F && float0 > float1;
 bool boolean1 = vector3f.x > 0.0F && float0 > float1;
 bool boolean2 = vector3f.z < 0.0F && float1 > float0;
 bool boolean3 = vector3f.z > 0.0F && float1 > float0;
 TL_vector3f_pool.get().release(vector3f);
 return this->isInvalidChunkAround(boolean0, boolean1, boolean2, boolean3);
 }

 bool isInvalidChunkAhead() {
 Vector3f vector3f = this->getForwardVector(TL_vector3f_pool.get().alloc());
 bool boolean0 = vector3f.x < -0.5F;
 bool boolean1 = vector3f.z > 0.5F;
 bool boolean2 = vector3f.x > 0.5F;
 bool boolean3 = vector3f.z < -0.5F;
 return this->isInvalidChunkAround(boolean0, boolean2, boolean3, boolean1);
 }

 bool isInvalidChunkBehind() {
 Vector3f vector3f = this->getForwardVector(TL_vector3f_pool.get().alloc());
 bool boolean0 = vector3f.x < -0.5F;
 bool boolean1 = vector3f.z > 0.5F;
 bool boolean2 = vector3f.x > 0.5F;
 bool boolean3 = vector3f.z < -0.5F;
 return this->isInvalidChunkAround(boolean2, boolean0, boolean1, boolean3);
 }

 bool isInvalidChunkAround(bool moveW, bool moveE, bool moveN, bool moveS) {
 if (IsoChunkMap.ChunkGridWidth > 7) {
 if (moveE && (this->isNullChunk(this->chunk.wx + 1, this->chunk.wy) || this->isNullChunk(this->chunk.wx + 2, this->chunk.wy) {
 return true;
 }

 if (moveW && (this->isNullChunk(this->chunk.wx - 1, this->chunk.wy) || this->isNullChunk(this->chunk.wx - 2, this->chunk.wy) {
 return true;
 }

 if (moveS && (this->isNullChunk(this->chunk.wx, this->chunk.wy + 1) || this->isNullChunk(this->chunk.wx, this->chunk.wy + 2) {
 return true;
 }

 if (moveN && (this->isNullChunk(this->chunk.wx, this->chunk.wy - 1) || this->isNullChunk(this->chunk.wx, this->chunk.wy - 2) {
 return true;
 }
 } else {
 if (IsoChunkMap.ChunkGridWidth <= 4) {
 return false;
 }

 if (moveE && this->isNullChunk(this->chunk.wx + 1, this->chunk.wy) {
 return true;
 }

 if (moveW && this->isNullChunk(this->chunk.wx - 1, this->chunk.wy) {
 return true;
 }

 if (moveS && this->isNullChunk(this->chunk.wx, this->chunk.wy + 1) {
 return true;
 }

 if (moveN && this->isNullChunk(this->chunk.wx, this->chunk.wy - 1) {
 return true;
 }
 }

 return false;
 }

 void postupdate() {
 this->current = this->getCell().getGridSquare((int)this->x, (int)this->y, 0);
 if (this->current == nullptr) {
 for (int int0 = (int)this->z; int0 >= 0; int0--) {
 this->current = this->getCell().getGridSquare((int)this->x, (int)this->y, int0);
 if (this->current != nullptr) {
 break;
 }
 }
 }

 if (this->movingSq != nullptr) {
 this->movingSq.getMovingObjects().remove(this);
 this->movingSq = nullptr;
 }

 if (this->current != nullptr && !this->current.getMovingObjects().contains(this) {
 this->current.getMovingObjects().add(this);
 this->movingSq = this->current;
 }

 this->square = this->current;
 if (this->sprite.hasActiveModel()) {
 this->updateAnimationPlayer(this->getAnimationPlayer(), nullptr);

 for (int int1 = 0; int1 < this->models.size(); int1++) {
 BaseVehicle.ModelInfo modelInfo = this->models.get(int1);
 this->updateAnimationPlayer(modelInfo.getAnimationPlayer(), modelInfo.part);
 }
 }
 }

 void updateAnimationPlayer(AnimationPlayer animationPlayer, VehiclePart part) {
 if (animationPlayer != nullptr && animationPlayer.isReady()) {
 AnimationMultiTrack animationMultiTrack = animationPlayer.getMultiTrack();
 float float0 = 0.016666668F;
 float0 *= 0.8F;
 float0 *= GameTime.instance.getUnmoddedMultiplier();
 animationPlayer.Update(float0);

 for (int int0 = 0; int0 < animationMultiTrack.getTrackCount(); int0++) {
 AnimationTrack animationTrack0 = animationMultiTrack.getTracks().get(int0);
 if (animationTrack0.IsPlaying && animationTrack0.isFinished()) {
 animationMultiTrack.removeTrackAt(int0);
 int0--;
 }
 }

 if (part != nullptr) {
 BaseVehicle.ModelInfo modelInfo = this->getModelInfoForPart(part);
 if (modelInfo.m_track != nullptr && animationMultiTrack.getIndexOfTrack(modelInfo.m_track) == -1) {
 modelInfo.m_track = nullptr;
 }

 if (modelInfo.m_track != nullptr) {
 VehicleWindow vehicleWindow0 = part.getWindow();
 if (vehicleWindow0 != nullptr) {
 AnimationTrack animationTrack1 = modelInfo.m_track;
 animationTrack1.setCurrentTimeValue(animationTrack1.getDuration() * vehicleWindow0.getOpenDelta());
 }
 } else {
 VehicleDoor vehicleDoor = part.getDoor();
 if (vehicleDoor != nullptr) {
 this->playPartAnim(part, vehicleDoor.isOpen() ? "Opened" : "Closed");
 }

 VehicleWindow vehicleWindow1 = part.getWindow();
 if (vehicleWindow1 != nullptr) {
 this->playPartAnim(part, "ClosedToOpen");
 }
 }
 }
 }
 }

 void saveChange(const std::string& change, KahluaTable tbl, ByteBuffer bb) {
 super.saveChange(change, tbl, bb);
 }

 void loadChange(const std::string& change, ByteBuffer bb) {
 super.loadChange(change, bb);
 }

 void authorizationClientCollide(IsoPlayer driver) {
 if (driver != nullptr && this->getDriver() == nullptr) {
 this->setNetPlayerAuthorization(BaseVehicle.Authorization.LocalCollide, driver.getOnlineID());
 this->authSimulationTime = System.currentTimeMillis();
 this->interpolation.clear();
 if (this->getVehicleTowing() != nullptr) {
 this->getVehicleTowing().setNetPlayerAuthorization(BaseVehicle.Authorization.LocalCollide, driver.getOnlineID());
 this->getVehicleTowing().authSimulationTime = System.currentTimeMillis();
 this->getVehicleTowing().interpolation.clear();
 } else if (this->getVehicleTowedBy() != nullptr) {
 this->getVehicleTowedBy().setNetPlayerAuthorization(BaseVehicle.Authorization.LocalCollide, driver.getOnlineID());
 this->getVehicleTowedBy().authSimulationTime = System.currentTimeMillis();
 this->getVehicleTowedBy().interpolation.clear();
 }
 }
 }

 void authorizationServerCollide(short PlayerID, bool isCollide) {
 if (!this->isNetPlayerAuthorization(BaseVehicle.Authorization.Local) {
 if (isCollide) {
 this->setNetPlayerAuthorization(BaseVehicle.Authorization.LocalCollide, PlayerID);
 if (this->getVehicleTowing() != nullptr) {
 this->getVehicleTowing().setNetPlayerAuthorization(BaseVehicle.Authorization.LocalCollide, PlayerID);
 } else if (this->getVehicleTowedBy() != nullptr) {
 this->getVehicleTowedBy().setNetPlayerAuthorization(BaseVehicle.Authorization.LocalCollide, PlayerID);
 }
 } else {
 BaseVehicle.Authorization authorization = PlayerID == -1 ? BaseVehicle.Authorization.Server : BaseVehicle.Authorization.Local;
 this->setNetPlayerAuthorization(authorization, PlayerID);
 if (this->getVehicleTowing() != nullptr) {
 this->getVehicleTowing().setNetPlayerAuthorization(authorization, PlayerID);
 } else if (this->getVehicleTowedBy() != nullptr) {
 this->getVehicleTowedBy().setNetPlayerAuthorization(authorization, PlayerID);
 }
 }
 }
 }

 void authorizationServerOnSeat(IsoPlayer player, bool enter) {
 BaseVehicle vehicle0 = this->getVehicleTowing();
 BaseVehicle vehicle1 = this->getVehicleTowedBy();
 if (this->isNetPlayerId((short)-1) && enter) {
 if (vehicle0 != nullptr && vehicle0.getDriver() == nullptr) {
 this->addPointConstraint(nullptr, vehicle0, this->getTowAttachmentSelf(), vehicle0.getTowAttachmentSelf());
 } else if (vehicle1 != nullptr && vehicle1.getDriver() == nullptr) {
 this->addPointConstraint(nullptr, vehicle1, this->getTowAttachmentSelf(), vehicle1.getTowAttachmentSelf());
 } else {
 this->setNetPlayerAuthorization(BaseVehicle.Authorization.Local, player.getOnlineID());
 }
 } else if (this->isNetPlayerId(player.getOnlineID()) && !enter) {
 if (vehicle0 != nullptr && vehicle0.getDriver() != nullptr) {
 vehicle0.addPointConstraint(nullptr, this, vehicle0.getTowAttachmentSelf(), this->getTowAttachmentSelf());
 } else if (vehicle1 != nullptr && vehicle1.getDriver() != nullptr) {
 vehicle1.addPointConstraint(nullptr, this, vehicle1.getTowAttachmentSelf(), this->getTowAttachmentSelf());
 } else {
 this->setNetPlayerAuthorization(BaseVehicle.Authorization.Server, -1);
 if (vehicle0 != nullptr) {
 vehicle0.setNetPlayerAuthorization(BaseVehicle.Authorization.Server, -1);
 } else if (vehicle1 != nullptr) {
 vehicle1.setNetPlayerAuthorization(BaseVehicle.Authorization.Server, -1);
 }
 }
 }
 }

 bool hasAuthorization(UdpConnection connection) {
 if (!this->isNetPlayerId((short)-1) && connection != nullptr) {
 if (GameServer.bServer) {
 for (int int0 = 0; int0 < connection.players.length; int0++) {
 if (connection.players[int0] != nullptr && this->isNetPlayerId(connection.players[int0].OnlineID) {
 return true;
 }
 }

 return false;
 } else {
 return this->isNetPlayerId(IsoPlayer.getInstance().getOnlineID());
 }
 } else {
 return false;
 }
 }

 void netPlayerServerSendAuthorisation(ByteBuffer bb) {
 bb.put(this->netPlayerAuthorization.index());
 bb.putShort(this->netPlayerId);
 }

 void netPlayerFromServerUpdate(BaseVehicle.Authorization authorization, short authorizationPlayer) {
 if (!this->isNetPlayerAuthorization(authorization) || !this->isNetPlayerId(authorizationPlayer) {
 if (BaseVehicle.Authorization.Local == authorization) {
 if (IsoPlayer.getLocalPlayerByOnlineID(authorizationPlayer) != nullptr) {
 this->setNetPlayerAuthorization(BaseVehicle.Authorization.Local, authorizationPlayer);
 } else {
 this->setNetPlayerAuthorization(BaseVehicle.Authorization.Remote, authorizationPlayer);
 }
 } else if (BaseVehicle.Authorization.LocalCollide == authorization) {
 if (IsoPlayer.getLocalPlayerByOnlineID(authorizationPlayer) != nullptr) {
 this->setNetPlayerAuthorization(BaseVehicle.Authorization.LocalCollide, authorizationPlayer);
 } else {
 this->setNetPlayerAuthorization(BaseVehicle.Authorization.RemoteCollide, authorizationPlayer);
 }
 } else {
 this->setNetPlayerAuthorization(BaseVehicle.Authorization.Server, -1);
 }
 }
 }

 Transform getWorldTransform(Transform out) {
 out.set(this->jniTransform);
 return out;
 }

 void setWorldTransform(Transform __in__) {
 this->jniTransform.set(__in__);
 Quaternionf quaternionf = this->tempQuat4f;
 __in__.getRotation(quaternionf);
 if (!GameServer.bServer) {
 Bullet.teleportVehicle(
 this->VehicleID,
 __in__.origin.x + WorldSimulation.instance.offsetX,
 __in__.origin.z + WorldSimulation.instance.offsetY,
 __in__.origin.y,
 quaternionf.x,
 quaternionf.y,
 quaternionf.z,
 quaternionf.w
 );
 }
 }

 void flipUpright() {
 Transform transform = this->tempTransform;
 transform.set(this->jniTransform);
 Quaternionf quaternionf = this->tempQuat4f;
 quaternionf.setAngleAxis(0.0F, _UNIT_Y.x, _UNIT_Y.y, _UNIT_Y.z);
 transform.setRotation(quaternionf);
 this->setWorldTransform(transform);
 }

 void setAngles(float degreesX, float degreesY, float degreesZ) {
 if ((int)degreesX != (int)this->getAngleX() || (int)degreesY != (int)this->getAngleY() || degreesZ != (int)this->getAngleZ()) {
 this->polyDirty = true;
 float float0 = degreesX * (float) (Math.PI / 180.0);
 float float1 = degreesY * (float) (Math.PI / 180.0);
 float float2 = degreesZ * (float) (Math.PI / 180.0);
 this->tempQuat4f.rotationXYZ(float0, float1, float2);
 this->tempTransform.set(this->jniTransform);
 this->tempTransform.setRotation(this->tempQuat4f);
 this->setWorldTransform(this->tempTransform);
 }
 }

 float getAngleX() {
 Vector3f vector3f = TL_vector3f_pool.get().alloc();
 this->jniTransform.getRotation(this->tempQuat4f).getEulerAnglesXYZ(vector3f);
 float float0 = vector3f.x * (180.0F / (float)Math.PI);
 TL_vector3f_pool.get().release(vector3f);
 return float0;
 }

 float getAngleY() {
 Vector3f vector3f = TL_vector3f_pool.get().alloc();
 this->jniTransform.getRotation(this->tempQuat4f).getEulerAnglesXYZ(vector3f);
 float float0 = vector3f.y * (180.0F / (float)Math.PI);
 TL_vector3f_pool.get().release(vector3f);
 return float0;
 }

 float getAngleZ() {
 Vector3f vector3f = TL_vector3f_pool.get().alloc();
 this->jniTransform.getRotation(this->tempQuat4f).getEulerAnglesXYZ(vector3f);
 float float0 = vector3f.z * (180.0F / (float)Math.PI);
 TL_vector3f_pool.get().release(vector3f);
 return float0;
 }

 void setDebugZ(float z) {
 this->tempTransform.set(this->jniTransform);
 this->tempTransform.origin.y = PZMath.clamp(z, 0.0F, 1.0F) * 3.0F * 0.82F;
 this->setWorldTransform(this->tempTransform);
 }

 void setPhysicsActive(bool active) {
 if (this->physics != nullptr && active != this->physics.isEnable) {
 this->physics.isEnable = active;
 if (!GameServer.bServer) {
 Bullet.setVehicleActive(this->VehicleID, active);
 }

 if (active) {
 this->physicActiveCheck = System.currentTimeMillis() + 3000L;
 }
 }
 }

 float getDebugZ() {
 return this->jniTransform.origin.y / 2.46F;
 }

 public PolygonalMap2.VehiclePoly getPoly() {
 if (this->polyDirty) {
 if (this->polyGarageCheck && this->square != nullptr) {
 if (this->square.getRoom() != nullptr && this->square.getRoom().RoomDef != nullptr && this->square.getRoom().RoomDef.contains("garagestorage")) {
 this->radiusReductionInGarage = -0.3F;
 } else {
 this->radiusReductionInGarage = 0.0F;
 }

 this->polyGarageCheck = false;
 }

 this->poly.init(this, 0.0F);
 this->polyPlusRadius.init(this, PLUS_RADIUS + this->radiusReductionInGarage);
 this->polyDirty = false;
 this->polyPlusRadiusMinX = -123.0F;
 this->initShadowPoly();
 }

 return this->poly;
 }

 public PolygonalMap2.VehiclePoly getPolyPlusRadius() {
 if (this->polyDirty) {
 if (this->polyGarageCheck && this->square != nullptr) {
 if (this->square.getRoom() != nullptr && this->square.getRoom().RoomDef != nullptr && this->square.getRoom().RoomDef.contains("garagestorage")) {
 this->radiusReductionInGarage = -0.3F;
 } else {
 this->radiusReductionInGarage = 0.0F;
 }

 this->polyGarageCheck = false;
 }

 this->poly.init(this, 0.0F);
 this->polyPlusRadius.init(this, PLUS_RADIUS + this->radiusReductionInGarage);
 this->polyDirty = false;
 this->polyPlusRadiusMinX = -123.0F;
 this->initShadowPoly();
 }

 return this->polyPlusRadius;
 }

 void initShadowPoly() {
 this->getWorldTransform(this->tempTransform);
 Quaternionf quaternionf = this->tempTransform.getRotation(this->tempQuat4f);
 Vector2f vector2f0 = this->script.getShadowExtents();
 Vector2f vector2f1 = this->script.getShadowOffset();
 float float0 = vector2f0.x / 2.0F;
 float float1 = vector2f0.y / 2.0F;
 Vector3f vector3f = TL_vector3f_pool.get().alloc();
 if (quaternionf.x < 0.0F) {
 this->getWorldPos(vector2f1.x - float0, 0.0F, vector2f1.y + float1, vector3f);
 this->shadowCoord.x1 = vector3f.x;
 this->shadowCoord.y1 = vector3f.y;
 this->getWorldPos(vector2f1.x + float0, 0.0F, vector2f1.y + float1, vector3f);
 this->shadowCoord.x2 = vector3f.x;
 this->shadowCoord.y2 = vector3f.y;
 this->getWorldPos(vector2f1.x + float0, 0.0F, vector2f1.y - float1, vector3f);
 this->shadowCoord.x3 = vector3f.x;
 this->shadowCoord.y3 = vector3f.y;
 this->getWorldPos(vector2f1.x - float0, 0.0F, vector2f1.y - float1, vector3f);
 this->shadowCoord.x4 = vector3f.x;
 this->shadowCoord.y4 = vector3f.y;
 } else {
 this->getWorldPos(vector2f1.x - float0, 0.0F, vector2f1.y + float1, vector3f);
 this->shadowCoord.x1 = vector3f.x;
 this->shadowCoord.y1 = vector3f.y;
 this->getWorldPos(vector2f1.x + float0, 0.0F, vector2f1.y + float1, vector3f);
 this->shadowCoord.x2 = vector3f.x;
 this->shadowCoord.y2 = vector3f.y;
 this->getWorldPos(vector2f1.x + float0, 0.0F, vector2f1.y - float1, vector3f);
 this->shadowCoord.x3 = vector3f.x;
 this->shadowCoord.y3 = vector3f.y;
 this->getWorldPos(vector2f1.x - float0, 0.0F, vector2f1.y - float1, vector3f);
 this->shadowCoord.x4 = vector3f.x;
 this->shadowCoord.y4 = vector3f.y;
 }

 TL_vector3f_pool.get().release(vector3f);
 }

 void initPolyPlusRadiusBounds() {
 if (this->polyPlusRadiusMinX == -123.0F) {
 PolygonalMap2.VehiclePoly vehiclePoly = this->getPolyPlusRadius();
 Vector3f vector3f0 = TL_vector3f_pool.get().alloc();
 Vector3f vector3f1 = this->getLocalPos(vehiclePoly.x1, vehiclePoly.y1, vehiclePoly.z, vector3f0);
 float float0 = (int)(vector3f1.x * 100.0F) / 100.0F;
 float float1 = (int)(vector3f1.z * 100.0F) / 100.0F;
 vector3f1 = this->getLocalPos(vehiclePoly.x2, vehiclePoly.y2, vehiclePoly.z, vector3f0);
 float float2 = (int)(vector3f1.x * 100.0F) / 100.0F;
 float float3 = (int)(vector3f1.z * 100.0F) / 100.0F;
 vector3f1 = this->getLocalPos(vehiclePoly.x3, vehiclePoly.y3, vehiclePoly.z, vector3f0);
 float float4 = (int)(vector3f1.x * 100.0F) / 100.0F;
 float float5 = (int)(vector3f1.z * 100.0F) / 100.0F;
 vector3f1 = this->getLocalPos(vehiclePoly.x4, vehiclePoly.y4, vehiclePoly.z, vector3f0);
 float float6 = (int)(vector3f1.x * 100.0F) / 100.0F;
 float float7 = (int)(vector3f1.z * 100.0F) / 100.0F;
 this->polyPlusRadiusMinX = Math.min(float0, Math.min(float2, Math.min(float4, float6);
 this->polyPlusRadiusMaxX = Math.max(float0, Math.max(float2, Math.max(float4, float6);
 this->polyPlusRadiusMinY = Math.min(float1, Math.min(float3, Math.min(float5, float7);
 this->polyPlusRadiusMaxY = Math.max(float1, Math.max(float3, Math.max(float5, float7);
 TL_vector3f_pool.get().release(vector3f0);
 }
 }

 Vector3f getForwardVector(Vector3f out) {
 uint8_t byte0 = 2;
 return this->jniTransform.basis.getColumn(byte0, out);
 }

 Vector3f getUpVector(Vector3f out) {
 uint8_t byte0 = 1;
 return this->jniTransform.basis.getColumn(byte0, out);
 }

 float getUpVectorDot() {
 Vector3f vector3f = this->getUpVector(TL_vector3f_pool.get().alloc());
 float float0 = vector3f.dot(_UNIT_Y);
 TL_vector3f_pool.get().release(vector3f);
 return float0;
 }

 bool isStopped() {
 return this->jniSpeed > -0.8F && this->jniSpeed < 0.8F && !this->getController().isGasPedalPressed();
 }

 float getCurrentSpeedKmHour() {
 return this->jniSpeed;
 }

 Vector3f getLinearVelocity(Vector3f out) {
 return out.set(this->jniLinearVelocity);
 }

 float getSpeed2D() {
 float float0 = this->jniLinearVelocity.x;
 float float1 = this->jniLinearVelocity.z;
 return (float)Math.sqrt(float0 * float0 + float1 * float1);
 }

 bool isAtRest() {
 if (this->physics == nullptr) {
 return true;
 } else {
 float float0 = this->jniLinearVelocity.y;
 return Math.abs(this->physics.EngineForce) < 0.01F && this->getSpeed2D() < 0.02F && Math.abs(float0) < 0.5F;
 }
 }

 void updateTransform() {
 if (this->sprite.modelSlot != nullptr) {
 float float0 = this->getScript().getModelScale();
 float float1 = 1.0F;
 if (this->sprite.modelSlot != nullptr && this->sprite.modelSlot.model.scale != 1.0F) {
 float1 = this->sprite.modelSlot.model.scale;
 }

 Transform transform = this->getWorldTransform(this->tempTransform);
 Quaternionf quaternionf0 = TL_quaternionf_pool.get().alloc();
 Quaternionf quaternionf1 = TL_quaternionf_pool.get().alloc();
 Matrix4f matrix4f0 = TL_matrix4f_pool.get().alloc();
 transform.getRotation(quaternionf0);
 quaternionf0.y *= -1.0F;
 quaternionf0.z *= -1.0F;
 Matrix4f matrix4f1 = quaternionf0.get(matrix4f0);
 float float2 = 1.0F;
 if (this->sprite.modelSlot.model.m_modelScript != nullptr) {
 float2 = this->sprite.modelSlot.model.m_modelScript.invertX ? -1.0F : 1.0F;
 }

 Vector3f vector3f0 = this->script.getModel().getOffset();
 Vector3f vector3f1 = this->getScript().getModel().getRotate();
 quaternionf1.rotationXYZ(vector3f1.x * (float) (Math.PI / 180.0), vector3f1.y * (float) (Math.PI / 180.0), vector3f1.z * (float) (Math.PI / 180.0);
 this->renderTransform
 .translationRotateScale(
 vector3f0.x * -1.0F,
 vector3f0.y,
 vector3f0.z,
 quaternionf1.x,
 quaternionf1.y,
 quaternionf1.z,
 quaternionf1.w,
 float0 * float1 * float2,
 float0 * float1,
 float0 * float1
 );
 matrix4f1.mul(this->renderTransform, this->renderTransform);
 this->vehicleTransform.translationRotateScale(vector3f0.x * -1.0F, vector3f0.y, vector3f0.z, 0.0F, 0.0F, 0.0F, 1.0F, float0);
 matrix4f1.mul(this->vehicleTransform, this->vehicleTransform);

 for (int int0 = 0; int0 < this->models.size(); int0++) {
 BaseVehicle.ModelInfo modelInfo = this->models.get(int0);
 VehicleScript.Model model = modelInfo.scriptModel;
 vector3f1 = model.getOffset();
 Vector3f vector3f2 = model.getRotate();
 float float3 = model.scale;
 float1 = 1.0F;
 float float4 = 1.0F;
 if (modelInfo.modelScript != nullptr) {
 float1 = modelInfo.modelScript.scale;
 float4 = modelInfo.modelScript.invertX ? -1.0F : 1.0F;
 }

 quaternionf1.rotationXYZ(
 vector3f2.x * (float) (Math.PI / 180.0), vector3f2.y * (float) (Math.PI / 180.0), vector3f2.z * (float) (Math.PI / 180.0)
 );
 if (modelInfo.wheelIndex == -1) {
 modelInfo.renderTransform
 .translationRotateScale(
 vector3f1.x * -1.0F,
 vector3f1.y,
 vector3f1.z,
 quaternionf1.x,
 quaternionf1.y,
 quaternionf1.z,
 quaternionf1.w,
 float3 * float1 * float4,
 float3 * float1,
 float3 * float1
 );
 this->vehicleTransform.mul(modelInfo.renderTransform, modelInfo.renderTransform);
 } else {
 BaseVehicle.WheelInfo wheelInfox = this->wheelInfo[modelInfo.wheelIndex];
 float float5 = wheelInfox.steering;
 float float6 = wheelInfox.rotation;
 VehicleScript.Wheel wheel = this->getScript().getWheel(modelInfo.wheelIndex);
 BaseVehicle.VehicleImpulse vehicleImpulse = modelInfo.wheelIndex < this->impulseFromSquishedZombie.length
 ? this->impulseFromSquishedZombie[modelInfo.wheelIndex]
 : nullptr;
 float float7 = vehicleImpulse != nullptr && vehicleImpulse.enable ? 0.05F : 0.0F;
 if (wheelInfox.suspensionLength == 0.0F) {
 matrix4f0.translation(wheel.offset.x / float0 * -1.0F, wheel.offset.y / float0, wheel.offset.z / float0);
 } else {
 matrix4f0.translation(
 wheel.offset.x / float0 * -1.0F,
 (wheel.offset.y + this->script.getSuspensionRestLength() - wheelInfox.suspensionLength) / float0 + float7 * 0.5F,
 wheel.offset.z / float0
 );
 }

 modelInfo.renderTransform.identity();
 modelInfo.renderTransform.mul(matrix4f0);
 modelInfo.renderTransform.rotateY(float5 * -1.0F);
 modelInfo.renderTransform.rotateX(float6);
 matrix4f0.translationRotateScale(
 vector3f1.x * -1.0F,
 vector3f1.y,
 vector3f1.z,
 quaternionf1.x,
 quaternionf1.y,
 quaternionf1.z,
 quaternionf1.w,
 float3 * float1 * float4,
 float3 * float1,
 float3 * float1
 );
 modelInfo.renderTransform.mul(matrix4f0);
 this->vehicleTransform.mul(modelInfo.renderTransform, modelInfo.renderTransform);
 }
 }

 TL_matrix4f_pool.get().release(matrix4f0);
 TL_quaternionf_pool.get().release(quaternionf0);
 TL_quaternionf_pool.get().release(quaternionf1);
 }
 }

 void updatePhysics() {
 this->physics.update();
 }

 void updatePhysicsNetwork() {
 if (this->limitPhysicSend.Check()) {
 VehicleManager.instance.sendPhysic(this);
 if (this->limitPhysicPositionSent == nullptr) {
 this->limitPhysicPositionSent = std::make_unique<Vector2>();
 } else if (IsoUtils.DistanceToSquared(this->limitPhysicPositionSent.x, this->limitPhysicPositionSent.y, this->x, this->y) > 0.001F) {
 this->limitPhysicSend.setUpdatePeriod(150L);
 } else {
 this->limitPhysicSend.setSmoothUpdatePeriod(300L);
 }

 this->limitPhysicPositionSent.set(this->x, this->y);
 }
 }

 void checkPhysicsValidWithServer() {
 float float0 = 0.05F;
 if (this->limitPhysicValid.Check() && Bullet.getOwnVehiclePhysics(this->VehicleID, physicsParams) == 0) {
 float float1 = Math.abs(physicsParams[0] - this->x);
 float float2 = Math.abs(physicsParams[1] - this->y);
 if (float1 > float0 || float2 > float0) {
 VehicleManager.instance.sendRequestGetPosition(this->VehicleID, PacketTypes.PacketType.Vehicles);
 DebugLog.Vehicle.trace("diff-x=%f diff-y=%f delta=%f", float1, float2, float0);
 }
 }
 }

 void updateControls() {
 if (this->getController() != nullptr) {
 if (this->isOperational()) {
 IsoPlayer player = Type.tryCastTo(this->getDriver(), IsoPlayer.class);
 if (player == nullptr || !player.isBlockMovement()) {
 this->getController().updateControls();
 }
 }
 }
 }

 bool isKeyboardControlled() {
 IsoGameCharacter character = this->getCharacter(0);
 return character != nullptr && character == IsoPlayer.players[0] && this->getVehicleTowedBy() == nullptr;
 }

 int getJoypad() {
 IsoGameCharacter character = this->getCharacter(0);
 return character != nullptr && character instanceof IsoPlayer ? ((IsoPlayer)character).JoypadBind : -1;
 }

 void Damage(float amount) {
 this->crash(amount, true);
 }

 void HitByVehicle(BaseVehicle vehicle, float amount) {
 this->crash(amount, true);
 }

 void crash(float delta, bool front) {
 if (GameClient.bClient) {
 SoundManager.instance.PlayWorldSound(this->getCrashSound(delta), this->square, 1.0F, 20.0F, 1.0F, true);
 GameClient.instance.sendClientCommandV(nullptr, "vehicle", "crash", "vehicle", this->getId(), "amount", delta, "front", front);
 } else {
 float float0 = 1.3F;
 switch (SandboxOptions.instance.CarDamageOnImpact.getValue()) {
 case 1:
 float0 = 1.9F;
 break;
 case 2:
 float0 = 1.6F;
 case 3:
 default:
 break;
 case 4:
 float0 = 1.1F;
 break;
 case 5:
 float0 = 0.9F;
 }

 delta = Math.abs(delta) / float0;
 if (front) {
 this->addDamageFront((int)delta);
 } else {
 this->addDamageRear((int)Math.abs(delta / float0);
 }

 this->damagePlayers(Math.abs(delta);
 SoundManager.instance.PlayWorldSound(this->getCrashSound(delta), this->square, 1.0F, 20.0F, 1.0F, true);
 }
 }

 std::string getCrashSound(float float0) {
 if (float0 < 5.0F) {
 return "VehicleCrash1";
 } else {
 return float0 < 30.0F ? "VehicleCrash2" : "VehicleCrash";
 }
 }

 /**
 * When hitting a character (zombie or player) damage aren't the same as hitting a wall. damaged will be mainly focus on windshield/hood, not on doors/windows like when hitting a wall.
 */
 void addDamageFrontHitAChr(int dmg) {
 if (dmg >= 4 || !Rand.NextBool(7) {
 VehiclePart part = this->getPartById("EngineDoor");
 if (part != nullptr && part.getInventoryItem() != nullptr) {
 part.damage(Rand.Next(Math.max(1, dmg - 10), dmg + 3);
 }

 if (part != nullptr && (part.getCondition() <= 0 || part.getInventoryItem() == nullptr) && Rand.NextBool(4) {
 part = this->getPartById("Engine");
 if (part != nullptr) {
 part.damage(Rand.Next(2, 4);
 }
 }

 if (dmg > 12) {
 part = this->getPartById("Windshield");
 if (part != nullptr && part.getInventoryItem() != nullptr) {
 part.damage(Rand.Next(Math.max(1, dmg - 10), dmg + 3);
 }
 }

 if (Rand.Next(5) < dmg) {
 if (Rand.NextBool(2) {
 part = this->getPartById("TireFrontLeft");
 } else {
 part = this->getPartById("TireFrontRight");
 }

 if (part != nullptr && part.getInventoryItem() != nullptr) {
 part.damage(Rand.Next(1, 3);
 }
 }

 if (Rand.Next(7) < dmg) {
 this->damageHeadlight("HeadlightLeft", Rand.Next(1, 4);
 }

 if (Rand.Next(7) < dmg) {
 this->damageHeadlight("HeadlightRight", Rand.Next(1, 4);
 }

 float float0 = this->getBloodIntensity("Front");
 this->setBloodIntensity("Front", float0 + 0.01F);
 }
 }

 /**
 * When hitting a character (zombie or player) damage aren't the same as hitting a wall. damaged will be mainly focus on windshield/truckbed, not on doors/windows like when hitting a wall.
 */
 void addDamageRearHitAChr(int dmg) {
 if (dmg >= 4 || !Rand.NextBool(7) {
 VehiclePart part = this->getPartById("TruckBed");
 if (part != nullptr && part.getInventoryItem() != nullptr) {
 part.setCondition(part.getCondition() - Rand.Next(Math.max(1, dmg - 10), dmg + 3);
 part.doInventoryItemStats(part.getInventoryItem(), 0);
 this->transmitPartCondition(part);
 }

 part = this->getPartById("DoorRear");
 if (part != nullptr && part.getInventoryItem() != nullptr) {
 part.damage(Rand.Next(Math.max(1, dmg - 10), dmg + 3);
 }

 part = this->getPartById("TrunkDoor");
 if (part != nullptr && part.getInventoryItem() != nullptr) {
 part.damage(Rand.Next(Math.max(1, dmg - 10), dmg + 3);
 }

 if (dmg > 12) {
 part = this->getPartById("WindshieldRear");
 if (part != nullptr && part.getInventoryItem() != nullptr) {
 part.damage(dmg);
 }
 }

 if (Rand.Next(5) < dmg) {
 if (Rand.NextBool(2) {
 part = this->getPartById("TireRearLeft");
 } else {
 part = this->getPartById("TireRearRight");
 }

 if (part != nullptr && part.getInventoryItem() != nullptr) {
 part.damage(Rand.Next(1, 3);
 }
 }

 if (Rand.Next(7) < dmg) {
 this->damageHeadlight("HeadlightRearLeft", Rand.Next(1, 4);
 }

 if (Rand.Next(7) < dmg) {
 this->damageHeadlight("HeadlightRearRight", Rand.Next(1, 4);
 }

 if (Rand.Next(6) < dmg) {
 part = this->getPartById("GasTank");
 if (part != nullptr && part.getInventoryItem() != nullptr) {
 part.damage(Rand.Next(1, 3);
 }
 }

 float float0 = this->getBloodIntensity("Rear");
 this->setBloodIntensity("Rear", float0 + 0.01F);
 }
 }

 void addDamageFront(int int0) {
 this->currentFrontEndDurability -= int0;
 VehiclePart part = this->getPartById("EngineDoor");
 if (part != nullptr && part.getInventoryItem() != nullptr) {
 part.damage(Rand.Next(Math.max(1, int0 - 5), int0 + 5);
 }

 if (part == nullptr || part.getInventoryItem() == nullptr || part.getCondition() < 25) {
 part = this->getPartById("Engine");
 if (part != nullptr) {
 part.damage(Rand.Next(Math.max(1, int0 - 3), int0 + 3);
 }
 }

 part = this->getPartById("Windshield");
 if (part != nullptr && part.getInventoryItem() != nullptr) {
 part.damage(Rand.Next(Math.max(1, int0 - 5), int0 + 5);
 }

 if (Rand.Next(4) == 0) {
 part = this->getPartById("DoorFrontLeft");
 if (part != nullptr && part.getInventoryItem() != nullptr) {
 part.damage(Rand.Next(Math.max(1, int0 - 5), int0 + 5);
 }

 part = this->getPartById("WindowFrontLeft");
 if (part != nullptr && part.getInventoryItem() != nullptr) {
 part.damage(Rand.Next(Math.max(1, int0 - 5), int0 + 5);
 }
 }

 if (Rand.Next(4) == 0) {
 part = this->getPartById("DoorFrontRight");
 if (part != nullptr && part.getInventoryItem() != nullptr) {
 part.damage(Rand.Next(Math.max(1, int0 - 5), int0 + 5);
 }

 part = this->getPartById("WindowFrontRight");
 if (part != nullptr && part.getInventoryItem() != nullptr) {
 part.damage(Rand.Next(Math.max(1, int0 - 5), int0 + 5);
 }
 }

 if (Rand.Next(20) < int0) {
 this->damageHeadlight("HeadlightLeft", int0);
 }

 if (Rand.Next(20) < int0) {
 this->damageHeadlight("HeadlightRight", int0);
 }
 }

 void addDamageRear(int int0) {
 this->currentRearEndDurability -= int0;
 VehiclePart part = this->getPartById("TruckBed");
 if (part != nullptr && part.getInventoryItem() != nullptr) {
 part.setCondition(part.getCondition() - Rand.Next(Math.max(1, int0 - 5), int0 + 5);
 part.doInventoryItemStats(part.getInventoryItem(), 0);
 this->transmitPartCondition(part);
 }

 part = this->getPartById("DoorRear");
 if (part != nullptr && part.getInventoryItem() != nullptr) {
 part.damage(Rand.Next(Math.max(1, int0 - 5), int0 + 5);
 }

 part = this->getPartById("TrunkDoor");
 if (part != nullptr && part.getInventoryItem() != nullptr) {
 part.damage(Rand.Next(Math.max(1, int0 - 5), int0 + 5);
 }

 part = this->getPartById("WindshieldRear");
 if (part != nullptr && part.getInventoryItem() != nullptr) {
 part.damage(int0);
 }

 if (Rand.Next(4) == 0) {
 part = this->getPartById("DoorRearLeft");
 if (part != nullptr && part.getInventoryItem() != nullptr) {
 part.damage(Rand.Next(Math.max(1, int0 - 5), int0 + 5);
 }

 part = this->getPartById("WindowRearLeft");
 if (part != nullptr && part.getInventoryItem() != nullptr) {
 part.damage(Rand.Next(Math.max(1, int0 - 5), int0 + 5);
 }
 }

 if (Rand.Next(4) == 0) {
 part = this->getPartById("DoorRearRight");
 if (part != nullptr && part.getInventoryItem() != nullptr) {
 part.damage(Rand.Next(Math.max(1, int0 - 5), int0 + 5);
 }

 part = this->getPartById("WindowRearRight");
 if (part != nullptr && part.getInventoryItem() != nullptr) {
 part.damage(Rand.Next(Math.max(1, int0 - 5), int0 + 5);
 }
 }

 if (Rand.Next(20) < int0) {
 this->damageHeadlight("HeadlightRearLeft", int0);
 }

 if (Rand.Next(20) < int0) {
 this->damageHeadlight("HeadlightRearRight", int0);
 }

 if (Rand.Next(20) < int0) {
 part = this->getPartById("Muffler");
 if (part != nullptr && part.getInventoryItem() != nullptr) {
 part.damage(Rand.Next(Math.max(1, int0 - 5), int0 + 5);
 }
 }
 }

 void damageHeadlight(const std::string& string, int int0) {
 VehiclePart part = this->getPartById(string);
 if (part != nullptr && part.getInventoryItem() != nullptr) {
 part.damage(int0);
 if (part.getCondition() <= 0) {
 part.setInventoryItem(nullptr);
 this->transmitPartItem(part);
 }
 }
 }

 float clamp(float float0, float float1, float float2) {
 if (float0 < float1) {
 float0 = float1;
 }

 if (float0 > float2) {
 float0 = float2;
 }

 return float0;
 }

 bool isCharacterAdjacentTo(IsoGameCharacter chr) {
 if ((int)chr.z != (int)this->z) {
 return false;
 } else {
 Transform transform = this->getWorldTransform(this->tempTransform);
 transform.inverse();
 Vector3f vector3f0 = TL_vector3f_pool.get().alloc();
 vector3f0.set(chr.x - WorldSimulation.instance.offsetX, 0.0F, chr.y - WorldSimulation.instance.offsetY);
 transform.transform(vector3f0);
 Vector3f vector3f1 = this->script.getExtents();
 Vector3f vector3f2 = this->script.getCenterOfMassOffset();
 float float0 = vector3f2.x - vector3f1.x / 2.0F;
 float float1 = vector3f2.x + vector3f1.x / 2.0F;
 float float2 = vector3f2.z - vector3f1.z / 2.0F;
 float float3 = vector3f2.z + vector3f1.z / 2.0F;
 if (vector3f0.x >= float0 - 0.5F && vector3f0.x < float1 + 0.5F && vector3f0.z >= float2 - 0.5F && vector3f0.z < float3 + 0.5F) {
 TL_vector3f_pool.get().release(vector3f0);
 return true;
 } else {
 TL_vector3f_pool.get().release(vector3f0);
 return false;
 }
 }
 }

 Vector2 testCollisionWithCharacter(IsoGameCharacter chr, float circleRadius, Vector2 out) {
 if (this->physics == nullptr) {
 return nullptr;
 } else {
 Vector3f vector3f0 = this->script.getExtents();
 Vector3f vector3f1 = this->script.getCenterOfMassOffset();
 if (this->DistToProper(chr) > Math.max(vector3f0.x / 2.0F, vector3f0.z / 2.0F) + circleRadius + 1.0F) {
 return nullptr;
 } else {
 Vector3f vector3f2 = TL_vector3f_pool.get().alloc();
 this->getLocalPos(chr.nx, chr.ny, 0.0F, vector3f2);
 float float0 = vector3f1.x - vector3f0.x / 2.0F;
 float float1 = vector3f1.x + vector3f0.x / 2.0F;
 float float2 = vector3f1.z - vector3f0.z / 2.0F;
 float float3 = vector3f1.z + vector3f0.z / 2.0F;
 if (vector3f2.x > float0 && vector3f2.x < float1 && vector3f2.z > float2 && vector3f2.z < float3) {
 float float4 = vector3f2.x - float0;
 float float5 = float1 - vector3f2.x;
 float float6 = vector3f2.z - float2;
 float float7 = float3 - vector3f2.z;
 Vector3f vector3f3 = TL_vector3f_pool.get().alloc();
 if (float4 < float5 && float4 < float6 && float4 < float7) {
 vector3f3.set(float0 - circleRadius - 0.015F, 0.0F, vector3f2.z);
 } else if (float5 < float4 && float5 < float6 && float5 < float7) {
 vector3f3.set(float1 + circleRadius + 0.015F, 0.0F, vector3f2.z);
 } else if (float6 < float4 && float6 < float5 && float6 < float7) {
 vector3f3.set(vector3f2.x, 0.0F, float2 - circleRadius - 0.015F);
 } else if (float7 < float4 && float7 < float5 && float7 < float6) {
 vector3f3.set(vector3f2.x, 0.0F, float3 + circleRadius + 0.015F);
 }

 TL_vector3f_pool.get().release(vector3f2);
 Transform transform0 = this->getWorldTransform(this->tempTransform);
 transform0.origin.set(0.0F, 0.0F, 0.0F);
 transform0.transform(vector3f3);
 vector3f3.x = vector3f3.x + this->getX();
 vector3f3.z = vector3f3.z + this->getY();
 this->collideX = vector3f3.x;
 this->collideY = vector3f3.z;
 out.set(vector3f3.x, vector3f3.z);
 TL_vector3f_pool.get().release(vector3f3);
 return out;
 } else {
 float float8 = this->clamp(vector3f2.x, float0, float1);
 float float9 = this->clamp(vector3f2.z, float2, float3);
 float float10 = vector3f2.x - float8;
 float float11 = vector3f2.z - float9;
 TL_vector3f_pool.get().release(vector3f2);
 float float12 = float10 * float10 + float11 * float11;
 if (float12 < circleRadius * circleRadius) {
 if (float10 == 0.0F && float11 == 0.0F) {
 return out.set(-1.0F, -1.0F);
 } else {
 Vector3f vector3f4 = TL_vector3f_pool.get().alloc();
 vector3f4.set(float10, 0.0F, float11);
 vector3f4.normalize();
 vector3f4.mul(circleRadius + 0.015F);
 vector3f4.x += float8;
 vector3f4.z += float9;
 Transform transform1 = this->getWorldTransform(this->tempTransform);
 transform1.origin.set(0.0F, 0.0F, 0.0F);
 transform1.transform(vector3f4);
 vector3f4.x = vector3f4.x + this->getX();
 vector3f4.z = vector3f4.z + this->getY();
 this->collideX = vector3f4.x;
 this->collideY = vector3f4.z;
 out.set(vector3f4.x, vector3f4.z);
 TL_vector3f_pool.get().release(vector3f4);
 return out;
 }
 } else {
 return nullptr;
 }
 }
 }
 }
 }

 int testCollisionWithProneCharacter(IsoGameCharacter chr, bool doSound) {
 Vector2 vector = chr.getAnimVector(TL_vector2_pool.get().alloc());
 int int0 = this->testCollisionWithProneCharacter(chr, vector.x, vector.y, doSound);
 TL_vector2_pool.get().release(vector);
 return int0;
 }

 int testCollisionWithCorpse(IsoDeadBody body, bool doSound) {
 float float0 = (float)Math.cos(body.getAngle());
 float float1 = (float)Math.sin(body.getAngle());
 return this->testCollisionWithProneCharacter(body, float0, float1, doSound);
 }

 int testCollisionWithProneCharacter(IsoMovingObject chr, float angleX, float angleY, bool doSound) {
 if (this->physics == nullptr) {
 return 0;
 } else if (GameServer.bServer) {
 return 0;
 } else {
 Vector3f vector3f0 = this->script.getExtents();
 float float0 = 0.3F;
 if (this->DistToProper(chr) > Math.max(vector3f0.x / 2.0F, vector3f0.z / 2.0F) + float0 + 1.0F) {
 return 0;
 } else if (Math.abs(this->jniSpeed) < 3.0F) {
 return 0;
 } else {
 float float1 = chr.x + angleX * 0.65F;
 float float2 = chr.y + angleY * 0.65F;
 float float3 = chr.x - angleX * 0.65F;
 float float4 = chr.y - angleY * 0.65F;
 int int0 = 0;
 Vector3f vector3f1 = TL_vector3f_pool.get().alloc();
 Vector3f vector3f2 = TL_vector3f_pool.get().alloc();

 for (int int1 = 0; int1 < this->script.getWheelCount(); int1++) {
 VehicleScript.Wheel wheel = this->script.getWheel(int1);
 bool boolean0 = true;

 for (int int2 = 0; int2 < this->models.size(); int2++) {
 BaseVehicle.ModelInfo modelInfo = this->models.get(int2);
 if (modelInfo.wheelIndex == int1) {
 this->getWorldPos(wheel.offset.x, wheel.offset.y - this->wheelInfo[int1].suspensionLength, wheel.offset.z, vector3f1);
 if (vector3f1.z > this->script.getWheel(int1).radius + 0.05F) {
 boolean0 = false;
 }
 break;
 }
 }

 if (boolean0) {
 this->getWorldPos(wheel.offset.x, wheel.offset.y, wheel.offset.z, vector3f2);
 float float5 = vector3f2.x;
 float float6 = vector3f2.y;
 double double0 = ((float5 - float3) * (float1 - float3) + (float6 - float4) * (float2 - float4)
 / (Math.pow(float1 - float3, 2.0) + Math.pow(float2 - float4, 2.0);
 float float7;
 float float8;
 if (double0 <= 0.0) {
 float7 = float3;
 float8 = float4;
 } else if (double0 >= 1.0) {
 float7 = float1;
 float8 = float2;
 } else {
 float7 = float3 + (float1 - float3) * (float)double0;
 float8 = float4 + (float2 - float4) * (float)double0;
 }

 if (!(IsoUtils.DistanceToSquared(vector3f2.x, vector3f2.y, float7, float8) > wheel.radius * wheel.radius) {
 if (doSound && Math.abs(this->jniSpeed) > 10.0F) {
 if (GameServer.bServer && chr instanceof IsoZombie) {
 ((IsoZombie)chr).setThumpFlag(1);
 } else {
 SoundManager.instance.PlayWorldSound("VehicleRunOverBody", chr.getCurrentSquare(), 0.0F, 20.0F, 0.9F, true);
 }

 doSound = false;
 }

 if (int1 < this->impulseFromSquishedZombie.length) {
 if (this->impulseFromSquishedZombie[int1] == nullptr) {
 this->impulseFromSquishedZombie[int1] = new BaseVehicle.VehicleImpulse();
 }

 this->impulseFromSquishedZombie[int1].impulse.set(0.0F, 1.0F, 0.0F);
 float float9 = Math.max(Math.abs(this->jniSpeed), 20.0F) / 20.0F;
 this->impulseFromSquishedZombie[int1].impulse.mul(0.065F * this->getFudgedMass() * float9);
 this->impulseFromSquishedZombie[int1].rel_pos.set(vector3f2.x - this->x, 0.0F, vector3f2.y - this->y);
 this->impulseFromSquishedZombie[int1].enable = true;
 int0++;
 }
 }
 }
 }

 TL_vector3f_pool.get().release(vector3f1);
 TL_vector3f_pool.get().release(vector3f2);
 return int0;
 }
 }
 }

 Vector2 testCollisionWithObject(IsoObject obj, float circleRadius, Vector2 out) {
 if (this->physics == nullptr) {
 return nullptr;
 } else if (obj.square == nullptr) {
 return nullptr;
 } else {
 float float0 = this->getObjectX(obj);
 float float1 = this->getObjectY(obj);
 Vector3f vector3f0 = this->script.getExtents();
 Vector3f vector3f1 = this->script.getCenterOfMassOffset();
 float float2 = Math.max(vector3f0.x / 2.0F, vector3f0.z / 2.0F) + circleRadius + 1.0F;
 if (this->DistToSquared(float0, float1) > float2 * float2) {
 return nullptr;
 } else {
 Vector3f vector3f2 = TL_vector3f_pool.get().alloc();
 this->getLocalPos(float0, float1, 0.0F, vector3f2);
 float float3 = vector3f1.x - vector3f0.x / 2.0F;
 float float4 = vector3f1.x + vector3f0.x / 2.0F;
 float float5 = vector3f1.z - vector3f0.z / 2.0F;
 float float6 = vector3f1.z + vector3f0.z / 2.0F;
 if (vector3f2.x > float3 && vector3f2.x < float4 && vector3f2.z > float5 && vector3f2.z < float6) {
 float float7 = vector3f2.x - float3;
 float float8 = float4 - vector3f2.x;
 float float9 = vector3f2.z - float5;
 float float10 = float6 - vector3f2.z;
 Vector3f vector3f3 = TL_vector3f_pool.get().alloc();
 if (float7 < float8 && float7 < float9 && float7 < float10) {
 vector3f3.set(float3 - circleRadius - 0.015F, 0.0F, vector3f2.z);
 } else if (float8 < float7 && float8 < float9 && float8 < float10) {
 vector3f3.set(float4 + circleRadius + 0.015F, 0.0F, vector3f2.z);
 } else if (float9 < float7 && float9 < float8 && float9 < float10) {
 vector3f3.set(vector3f2.x, 0.0F, float5 - circleRadius - 0.015F);
 } else if (float10 < float7 && float10 < float8 && float10 < float9) {
 vector3f3.set(vector3f2.x, 0.0F, float6 + circleRadius + 0.015F);
 }

 TL_vector3f_pool.get().release(vector3f2);
 Transform transform0 = this->getWorldTransform(this->tempTransform);
 transform0.origin.set(0.0F, 0.0F, 0.0F);
 transform0.transform(vector3f3);
 vector3f3.x = vector3f3.x + this->getX();
 vector3f3.z = vector3f3.z + this->getY();
 this->collideX = vector3f3.x;
 this->collideY = vector3f3.z;
 out.set(vector3f3.x, vector3f3.z);
 TL_vector3f_pool.get().release(vector3f3);
 return out;
 } else {
 float float11 = this->clamp(vector3f2.x, float3, float4);
 float float12 = this->clamp(vector3f2.z, float5, float6);
 float float13 = vector3f2.x - float11;
 float float14 = vector3f2.z - float12;
 TL_vector3f_pool.get().release(vector3f2);
 float float15 = float13 * float13 + float14 * float14;
 if (float15 < circleRadius * circleRadius) {
 if (float13 == 0.0F && float14 == 0.0F) {
 return out.set(-1.0F, -1.0F);
 } else {
 Vector3f vector3f4 = TL_vector3f_pool.get().alloc();
 vector3f4.set(float13, 0.0F, float14);
 vector3f4.normalize();
 vector3f4.mul(circleRadius + 0.015F);
 vector3f4.x += float11;
 vector3f4.z += float12;
 Transform transform1 = this->getWorldTransform(this->tempTransform);
 transform1.origin.set(0.0F, 0.0F, 0.0F);
 transform1.transform(vector3f4);
 vector3f4.x = vector3f4.x + this->getX();
 vector3f4.z = vector3f4.z + this->getY();
 this->collideX = vector3f4.x;
 this->collideY = vector3f4.z;
 out.set(vector3f4.x, vector3f4.z);
 TL_vector3f_pool.get().release(vector3f4);
 return out;
 }
 } else {
 return nullptr;
 }
 }
 }
 }
 }

 bool testCollisionWithVehicle(BaseVehicle obj) {
 VehicleScript vehicleScript0 = this->script;
 if (vehicleScript0 == nullptr) {
 vehicleScript0 = ScriptManager.instance.getVehicle(this->scriptName);
 }

 VehicleScript vehicleScript1 = obj.script;
 if (vehicleScript1 == nullptr) {
 vehicleScript1 = ScriptManager.instance.getVehicle(obj.scriptName);
 }

 if (vehicleScript0 != nullptr && vehicleScript1 != nullptr) {
 Vector2[] vectors0 = BaseVehicle.L_testCollisionWithVehicle.testVecs1;
 Vector2[] vectors1 = BaseVehicle.L_testCollisionWithVehicle.testVecs2;
 if (vectors0[0] == nullptr) {
 for (int int0 = 0; int0 < vectors0.length; int0++) {
 vectors0[int0] = std::make_unique<Vector2>();
 vectors1[int0] = std::make_unique<Vector2>();
 }
 }

 Vector3f vector3f0 = vehicleScript0.getExtents();
 Vector3f vector3f1 = vehicleScript0.getCenterOfMassOffset();
 Vector3f vector3f2 = vehicleScript1.getExtents();
 Vector3f vector3f3 = vehicleScript1.getCenterOfMassOffset();
 Vector3f vector3f4 = BaseVehicle.L_testCollisionWithVehicle.worldPos;
 float float0 = 0.5F;
 this->getWorldPos(vector3f1.x + vector3f0.x * float0, 0.0F, vector3f1.z + vector3f0.z * float0, vector3f4, vehicleScript0);
 vectors0[0].set(vector3f4.x, vector3f4.y);
 this->getWorldPos(vector3f1.x - vector3f0.x * float0, 0.0F, vector3f1.z + vector3f0.z * float0, vector3f4, vehicleScript0);
 vectors0[1].set(vector3f4.x, vector3f4.y);
 this->getWorldPos(vector3f1.x - vector3f0.x * float0, 0.0F, vector3f1.z - vector3f0.z * float0, vector3f4, vehicleScript0);
 vectors0[2].set(vector3f4.x, vector3f4.y);
 this->getWorldPos(vector3f1.x + vector3f0.x * float0, 0.0F, vector3f1.z - vector3f0.z * float0, vector3f4, vehicleScript0);
 vectors0[3].set(vector3f4.x, vector3f4.y);
 obj.getWorldPos(vector3f3.x + vector3f2.x * float0, 0.0F, vector3f3.z + vector3f2.z * float0, vector3f4, vehicleScript1);
 vectors1[0].set(vector3f4.x, vector3f4.y);
 obj.getWorldPos(vector3f3.x - vector3f2.x * float0, 0.0F, vector3f3.z + vector3f2.z * float0, vector3f4, vehicleScript1);
 vectors1[1].set(vector3f4.x, vector3f4.y);
 obj.getWorldPos(vector3f3.x - vector3f2.x * float0, 0.0F, vector3f3.z - vector3f2.z * float0, vector3f4, vehicleScript1);
 vectors1[2].set(vector3f4.x, vector3f4.y);
 obj.getWorldPos(vector3f3.x + vector3f2.x * float0, 0.0F, vector3f3.z - vector3f2.z * float0, vector3f4, vehicleScript1);
 vectors1[3].set(vector3f4.x, vector3f4.y);
 return QuadranglesIntersection.IsQuadranglesAreIntersected(vectors0, vectors1);
 } else {
 return false;
 }
 }

 float getObjectX(IsoObject object) {
 return object instanceof IsoMovingObject ? object.getX() : object.getSquare().getX() + 0.5F;
 }

 float getObjectY(IsoObject object) {
 return object instanceof IsoMovingObject ? object.getY() : object.getSquare().getY() + 0.5F;
 }

 void ApplyImpulse(IsoObject obj, float mul) {
 float float0 = this->getObjectX(obj);
 float float1 = this->getObjectY(obj);
 BaseVehicle.VehicleImpulse vehicleImpulse = BaseVehicle.VehicleImpulse.alloc();
 vehicleImpulse.impulse.set(this->x - float0, 0.0F, this->y - float1);
 vehicleImpulse.impulse.normalize();
 vehicleImpulse.impulse.mul(mul);
 vehicleImpulse.rel_pos.set(float0 - this->x, 0.0F, float1 - this->y);
 this->impulseFromHitZombie.add(vehicleImpulse);
 }

 void ApplyImpulse4Break(IsoObject obj, float mul) {
 float float0 = this->getObjectX(obj);
 float float1 = this->getObjectY(obj);
 BaseVehicle.VehicleImpulse vehicleImpulse = BaseVehicle.VehicleImpulse.alloc();
 this->getLinearVelocity(vehicleImpulse.impulse);
 vehicleImpulse.impulse.mul(-mul * this->getFudgedMass());
 vehicleImpulse.rel_pos.set(float0 - this->x, 0.0F, float1 - this->y);
 this->impulseFromHitZombie.add(vehicleImpulse);
 }

 void hitCharacter(IsoZombie chr) {
 IsoPlayer player = Type.tryCastTo(chr, IsoPlayer.class);
 IsoZombie zombie0 = Type.tryCastTo(chr, IsoZombie.class);
 if (chr.getCurrentState() != StaggerBackState.instance() && chr.getCurrentState() != ZombieFallDownState.instance()) {
 if (!(Math.abs(chr.x - this->x) < 0.01F) && !(Math.abs(chr.y - this->y) < 0.01F) {
 float float0 = 15.0F;
 Vector3f vector3f0 = this->getLinearVelocity(TL_vector3f_pool.get().alloc());
 vector3f0.y = 0.0F;
 float float1 = vector3f0.length();
 float1 = Math.min(float1, float0);
 if (float1 < 0.05F) {
 TL_vector3f_pool.get().release(vector3f0);
 } else {
 Vector3f vector3f1 = TL_vector3f_pool.get().alloc();
 vector3f1.set(this->x - chr.x, 0.0F, this->y - chr.y);
 vector3f1.normalize();
 vector3f0.normalize();
 float float2 = vector3f0.dot(vector3f1);
 TL_vector3f_pool.get().release(vector3f0);
 if (float2 < 0.0F && !GameServer.bServer) {
 this->ApplyImpulse(chr, this->getFudgedMass() * 7.0F * float1 / float0 * Math.abs(float2);
 }

 vector3f1.normalize();
 vector3f1.mul(3.0F * float1 / float0);
 Vector2 vector = TL_vector2_pool.get().alloc();
 float float3 = float1 + this->physics.clientForce / this->getFudgedMass();
 if (player != nullptr) {
 player.setVehicleHitLocation(this);
 } else if (zombie0 != nullptr) {
 zombie0.setVehicleHitLocation(this);
 }

 BaseSoundEmitter baseSoundEmitter = IsoWorld.instance.getFreeEmitter(chr.x, chr.y, chr.z);
 long long0 = baseSoundEmitter.playSound("VehicleHitCharacter");
 baseSoundEmitter.setParameterValue(long0, FMODManager.instance.getParameterDescription("VehicleSpeed"), this->getCurrentSpeedKmHour());
 chr.Hit(this, float3, float2 > 0.0F, vector.set(-vector3f1.x, -vector3f1.z);
 TL_vector2_pool.get().release(vector);
 TL_vector3f_pool.get().release(vector3f1);
 long long1 = System.currentTimeMillis();
 long long2 = (long1 - this->zombieHitTimestamp) / 1000L;
 this->zombiesHits = Math.max(this->zombiesHits - (int)long2, 0);
 if (long1 - this->zombieHitTimestamp > 700L) {
 this->zombieHitTimestamp = long1;
 this->zombiesHits++;
 this->zombiesHits = Math.min(this->zombiesHits, 20);
 }

 if (float1 >= 5.0F || this->zombiesHits > 10) {
 float1 = this->getCurrentSpeedKmHour() / 5.0F;
 Vector3f vector3f2 = TL_vector3f_pool.get().alloc();
 this->getLocalPos(chr.x, chr.y, chr.z, vector3f2);
 if (vector3f2.z > 0.0F) {
 int int0 = this->caclulateDamageWithBodies(true);
 this->addDamageFrontHitAChr(int0);
 } else {
 int int1 = this->caclulateDamageWithBodies(false);
 this->addDamageRearHitAChr(int1);
 }

 TL_vector3f_pool.get().release(vector3f2);
 }
 }
 }
 }
 }

 int caclulateDamageWithBodies(bool boolean1) {
 bool boolean0 = this->getCurrentSpeedKmHour() > 0.0F;
 float float0 = Math.abs(this->getCurrentSpeedKmHour());
 float float1 = float0 / 160.0F;
 float1 = PZMath.clamp(float1 * float1, 0.0F, 1.0F);
 float float2 = 60.0F * float1;
 float float3 = PZMath.max(1.0F, this->zombiesHits / 3.0F);
 if (!boolean1 && !boolean0) {
 float3 = 1.0F;
 }

 if (this->zombiesHits > 10 && float2 < Math.abs(this->getCurrentSpeedKmHour()) / 5.0F) {
 float2 = Math.abs(this->getCurrentSpeedKmHour()) / 5.0F;
 }

 return (int)(float3 * float2);
 }

 int calculateDamageWithCharacter(IsoGameCharacter chr) {
 Vector3f vector3f = TL_vector3f_pool.get().alloc();
 this->getLocalPos(chr.x, chr.y, chr.z, vector3f);
 int int0;
 if (vector3f.z > 0.0F) {
 int0 = this->caclulateDamageWithBodies(true);
 } else {
 int0 = -1 * this->caclulateDamageWithBodies(false);
 }

 TL_vector3f_pool.get().release(vector3f);
 return int0;
 }

 bool blocked(int x, int y, int z) {
 if (this->removedFromWorld || this->current == nullptr || this->getController() == nullptr) {
 return false;
 } else if (this->getController() == nullptr) {
 return false;
 } else if (z != (int)this->getZ()) {
 return false;
 } else if (IsoUtils.DistanceTo2D(x + 0.5F, y + 0.5F, this->x, this->y) > 5.0F) {
 return false;
 } else {
 float float0 = 0.3F;
 Transform transform = this->tempTransform3;
 this->getWorldTransform(transform);
 transform.inverse();
 Vector3f vector3f0 = TL_vector3f_pool.get().alloc();
 vector3f0.set(x + 0.5F - WorldSimulation.instance.offsetX, 0.0F, y + 0.5F - WorldSimulation.instance.offsetY);
 transform.transform(vector3f0);
 Vector3f vector3f1 = this->script.getExtents();
 Vector3f vector3f2 = this->script.getCenterOfMassOffset();
 float float1 = this->clamp(vector3f0.x, vector3f2.x - vector3f1.x / 2.0F, vector3f2.x + vector3f1.x / 2.0F);
 float float2 = this->clamp(vector3f0.z, vector3f2.z - vector3f1.z / 2.0F, vector3f2.z + vector3f1.z / 2.0F);
 float float3 = vector3f0.x - float1;
 float float4 = vector3f0.z - float2;
 TL_vector3f_pool.get().release(vector3f0);
 float float5 = float3 * float3 + float4 * float4;
 return float5 < float0 * float0;
 }
 }

 bool isIntersectingSquare(int x, int y, int z) {
 if (z != (int)this->getZ()) {
 return false;
 } else if (!this->removedFromWorld && this->current != nullptr && this->getController() != nullptr) {
 tempPoly.x1 = tempPoly.x4 = x;
 tempPoly.y1 = tempPoly.y2 = y;
 tempPoly.x2 = tempPoly.x3 = x + 1;
 tempPoly.y3 = tempPoly.y4 = y + 1;
 return PolyPolyIntersect.intersects(tempPoly, this->getPoly());
 } else {
 return false;
 }
 }

 bool isIntersectingSquareWithShadow(int x, int y, int z) {
 if (z != (int)this->getZ()) {
 return false;
 } else if (!this->removedFromWorld && this->current != nullptr && this->getController() != nullptr) {
 tempPoly.x1 = tempPoly.x4 = x;
 tempPoly.y1 = tempPoly.y2 = y;
 tempPoly.x2 = tempPoly.x3 = x + 1;
 tempPoly.y3 = tempPoly.y4 = y + 1;
 return PolyPolyIntersect.intersects(tempPoly, this->shadowCoord);
 } else {
 return false;
 }
 }

 bool circleIntersects(float x, float y, float z, float radius) {
 if (this->getController() == nullptr) {
 return false;
 } else if ((int)z != (int)this->getZ()) {
 return false;
 } else if (IsoUtils.DistanceTo2D(x, y, this->x, this->y) > 5.0F) {
 return false;
 } else {
 Vector3f vector3f0 = this->script.getExtents();
 Vector3f vector3f1 = this->script.getCenterOfMassOffset();
 Vector3f vector3f2 = TL_vector3f_pool.get().alloc();
 this->getLocalPos(x, y, z, vector3f2);
 float float0 = vector3f1.x - vector3f0.x / 2.0F;
 float float1 = vector3f1.x + vector3f0.x / 2.0F;
 float float2 = vector3f1.z - vector3f0.z / 2.0F;
 float float3 = vector3f1.z + vector3f0.z / 2.0F;
 if (vector3f2.x > float0 && vector3f2.x < float1 && vector3f2.z > float2 && vector3f2.z < float3) {
 return true;
 } else {
 float float4 = this->clamp(vector3f2.x, float0, float1);
 float float5 = this->clamp(vector3f2.z, float2, float3);
 float float6 = vector3f2.x - float4;
 float float7 = vector3f2.z - float5;
 TL_vector3f_pool.get().release(vector3f2);
 float float8 = float6 * float6 + float7 * float7;
 return float8 < radius * radius;
 }
 }
 }

 void updateLights() {
 VehicleModelInstance vehicleModelInstance = (VehicleModelInstance)this->sprite.modelSlot.model;
 vehicleModelInstance.textureRustA = this->rust;
 if (this->script.getWheelCount() == 0) {
 vehicleModelInstance.textureRustA = 0.0F;
 }

 vehicleModelInstance.painColor.x = this->colorHue;
 vehicleModelInstance.painColor.y = this->colorSaturation;
 vehicleModelInstance.painColor.z = this->colorValue;
 bool boolean0 = false;
 bool boolean1 = false;
 bool boolean2 = false;
 bool boolean3 = false;
 bool boolean4 = false;
 bool boolean5 = false;
 bool boolean6 = false;
 bool boolean7 = false;
 if (this->windowLightsOn) {
 VehiclePart part0 = this->getPartById("Windshield");
 boolean0 = part0 != nullptr && part0.getInventoryItem() != nullptr;
 part0 = this->getPartById("WindshieldRear");
 boolean1 = part0 != nullptr && part0.getInventoryItem() != nullptr;
 part0 = this->getPartById("WindowFrontLeft");
 boolean2 = part0 != nullptr && part0.getInventoryItem() != nullptr;
 part0 = this->getPartById("WindowMiddleLeft");
 boolean3 = part0 != nullptr && part0.getInventoryItem() != nullptr;
 part0 = this->getPartById("WindowRearLeft");
 boolean4 = part0 != nullptr && part0.getInventoryItem() != nullptr;
 part0 = this->getPartById("WindowFrontRight");
 boolean5 = part0 != nullptr && part0.getInventoryItem() != nullptr;
 part0 = this->getPartById("WindowMiddleRight");
 boolean6 = part0 != nullptr && part0.getInventoryItem() != nullptr;
 part0 = this->getPartById("WindowRearRight");
 boolean7 = part0 != nullptr && part0.getInventoryItem() != nullptr;
 }

 vehicleModelInstance.textureLightsEnables1[10] = boolean0 ? 1.0F : 0.0F;
 vehicleModelInstance.textureLightsEnables1[14] = boolean1 ? 1.0F : 0.0F;
 vehicleModelInstance.textureLightsEnables1[2] = boolean2 ? 1.0F : 0.0F;
 vehicleModelInstance.textureLightsEnables1[6] = boolean3 | boolean4 ? 1.0F : 0.0F;
 vehicleModelInstance.textureLightsEnables1[9] = boolean5 ? 1.0F : 0.0F;
 vehicleModelInstance.textureLightsEnables1[13] = boolean6 | boolean7 ? 1.0F : 0.0F;
 bool boolean8 = false;
 bool boolean9 = false;
 bool boolean10 = false;
 bool boolean11 = false;
 if (this->headlightsOn && this->getBatteryCharge() > 0.0F) {
 VehiclePart part1 = this->getPartById("HeadlightLeft");
 if (part1 != nullptr && part1.getInventoryItem() != nullptr) {
 boolean8 = true;
 }

 part1 = this->getPartById("HeadlightRight");
 if (part1 != nullptr && part1.getInventoryItem() != nullptr) {
 boolean9 = true;
 }

 part1 = this->getPartById("HeadlightRearLeft");
 if (part1 != nullptr && part1.getInventoryItem() != nullptr) {
 boolean11 = true;
 }

 part1 = this->getPartById("HeadlightRearRight");
 if (part1 != nullptr && part1.getInventoryItem() != nullptr) {
 boolean10 = true;
 }
 }

 vehicleModelInstance.textureLightsEnables2[4] = boolean9 ? 1.0F : 0.0F;
 vehicleModelInstance.textureLightsEnables2[8] = boolean8 ? 1.0F : 0.0F;
 vehicleModelInstance.textureLightsEnables2[12] = boolean10 ? 1.0F : 0.0F;
 vehicleModelInstance.textureLightsEnables2[1] = boolean11 ? 1.0F : 0.0F;
 bool boolean12 = this->stoplightsOn && this->getBatteryCharge() > 0.0F;
 if (this->scriptName.contains("Trailer")
 && this->vehicleTowedBy != nullptr
 && this->vehicleTowedBy.stoplightsOn
 && this->vehicleTowedBy.getBatteryCharge() > 0.0F) {
 boolean12 = true;
 }

 if (boolean12) {
 vehicleModelInstance.textureLightsEnables2[5] = 1.0F;
 vehicleModelInstance.textureLightsEnables2[9] = 1.0F;
 } else {
 vehicleModelInstance.textureLightsEnables2[5] = 0.0F;
 vehicleModelInstance.textureLightsEnables2[9] = 0.0F;
 }

 if (this->script.getLightbar().enable) {
 if (this->lightbarLightsMode.isEnable() && this->getBatteryCharge() > 0.0F) {
 switch (this->lightbarLightsMode.getLightTexIndex()) {
 case 0:
 vehicleModelInstance.textureLightsEnables2[13] = 0.0F;
 vehicleModelInstance.textureLightsEnables2[2] = 0.0F;
 break;
 case 1:
 vehicleModelInstance.textureLightsEnables2[13] = 0.0F;
 vehicleModelInstance.textureLightsEnables2[2] = 1.0F;
 break;
 case 2:
 vehicleModelInstance.textureLightsEnables2[13] = 1.0F;
 vehicleModelInstance.textureLightsEnables2[2] = 0.0F;
 break;
 default:
 vehicleModelInstance.textureLightsEnables2[13] = 0.0F;
 vehicleModelInstance.textureLightsEnables2[2] = 0.0F;
 }
 } else {
 vehicleModelInstance.textureLightsEnables2[13] = 0.0F;
 vehicleModelInstance.textureLightsEnables2[2] = 0.0F;
 }
 }

 if (DebugOptions.instance.VehicleCycleColor.getValue()) {
 float float0 = (float)(System.currentTimeMillis() % 2000L);
 float float1 = (float)(System.currentTimeMillis() % 7000L);
 float float2 = (float)(System.currentTimeMillis() % 11000L);
 vehicleModelInstance.painColor.x = float0 / 2000.0F;
 vehicleModelInstance.painColor.y = float1 / 7000.0F;
 vehicleModelInstance.painColor.z = float2 / 11000.0F;
 }

 if (DebugOptions.instance.VehicleRenderBlood0.getValue()) {
 Arrays.fill(vehicleModelInstance.matrixBlood1Enables1, 0.0F);
 Arrays.fill(vehicleModelInstance.matrixBlood1Enables2, 0.0F);
 Arrays.fill(vehicleModelInstance.matrixBlood2Enables1, 0.0F);
 Arrays.fill(vehicleModelInstance.matrixBlood2Enables2, 0.0F);
 }

 if (DebugOptions.instance.VehicleRenderBlood50.getValue()) {
 Arrays.fill(vehicleModelInstance.matrixBlood1Enables1, 0.5F);
 Arrays.fill(vehicleModelInstance.matrixBlood1Enables2, 0.5F);
 Arrays.fill(vehicleModelInstance.matrixBlood2Enables1, 1.0F);
 Arrays.fill(vehicleModelInstance.matrixBlood2Enables2, 1.0F);
 }

 if (DebugOptions.instance.VehicleRenderBlood100.getValue()) {
 Arrays.fill(vehicleModelInstance.matrixBlood1Enables1, 1.0F);
 Arrays.fill(vehicleModelInstance.matrixBlood1Enables2, 1.0F);
 Arrays.fill(vehicleModelInstance.matrixBlood2Enables1, 1.0F);
 Arrays.fill(vehicleModelInstance.matrixBlood2Enables2, 1.0F);
 }

 if (DebugOptions.instance.VehicleRenderDamage0.getValue()) {
 Arrays.fill(vehicleModelInstance.textureDamage1Enables1, 0.0F);
 Arrays.fill(vehicleModelInstance.textureDamage1Enables2, 0.0F);
 Arrays.fill(vehicleModelInstance.textureDamage2Enables1, 0.0F);
 Arrays.fill(vehicleModelInstance.textureDamage2Enables2, 0.0F);
 }

 if (DebugOptions.instance.VehicleRenderDamage1.getValue()) {
 Arrays.fill(vehicleModelInstance.textureDamage1Enables1, 1.0F);
 Arrays.fill(vehicleModelInstance.textureDamage1Enables2, 1.0F);
 Arrays.fill(vehicleModelInstance.textureDamage2Enables1, 0.0F);
 Arrays.fill(vehicleModelInstance.textureDamage2Enables2, 0.0F);
 }

 if (DebugOptions.instance.VehicleRenderDamage2.getValue()) {
 Arrays.fill(vehicleModelInstance.textureDamage1Enables1, 0.0F);
 Arrays.fill(vehicleModelInstance.textureDamage1Enables2, 0.0F);
 Arrays.fill(vehicleModelInstance.textureDamage2Enables1, 1.0F);
 Arrays.fill(vehicleModelInstance.textureDamage2Enables2, 1.0F);
 }

 if (DebugOptions.instance.VehicleRenderRust0.getValue()) {
 vehicleModelInstance.textureRustA = 0.0F;
 }

 if (DebugOptions.instance.VehicleRenderRust50.getValue()) {
 vehicleModelInstance.textureRustA = 0.5F;
 }

 if (DebugOptions.instance.VehicleRenderRust100.getValue()) {
 vehicleModelInstance.textureRustA = 1.0F;
 }

 vehicleModelInstance.refBody = 0.3F;
 vehicleModelInstance.refWindows = 0.4F;
 if (this->rust > 0.8F) {
 vehicleModelInstance.refBody = 0.1F;
 vehicleModelInstance.refWindows = 0.2F;
 }
 }

 void updateWorldLights() {
 if (!this->script.getLightbar().enable) {
 this->removeWorldLights();
 } else if (!this->lightbarLightsMode.isEnable() || this->getBatteryCharge() <= 0.0F) {
 this->removeWorldLights();
 } else if (this->lightbarLightsMode.getLightTexIndex() == 0) {
 this->removeWorldLights();
 } else {
 this->leftLight1.radius = this->leftLight2.radius = this->rightLight1.radius = this->rightLight2.radius = 8;
 if (this->lightbarLightsMode.getLightTexIndex() == 1) {
 Vector3f vector3f0 = this->getWorldPos(0.4F, 0.0F, 0.0F, TL_vector3f_pool.get().alloc());
 int int0 = (int)vector3f0.x;
 int int1 = (int)vector3f0.y;
 int int2 = (int)(this->getZ() + 1.0F);
 TL_vector3f_pool.get().release(vector3f0);
 int int3 = this->leftLightIndex;
 if (int3 == 1 && this->leftLight1.x == int0 && this->leftLight1.y == int1 && this->leftLight1.z == int2) {
 return;
 }

 if (int3 == 2 && this->leftLight2.x == int0 && this->leftLight2.y == int1 && this->leftLight2.z == int2) {
 return;
 }

 this->removeWorldLights();
 IsoLightSource lightSource0;
 if (int3 == 1) {
 lightSource0 = this->leftLight2;
 this->leftLightIndex = 2;
 } else {
 lightSource0 = this->leftLight1;
 this->leftLightIndex = 1;
 }

 lightSource0.life = -1;
 lightSource0.x = int0;
 lightSource0.y = int1;
 lightSource0.z = int2;
 IsoWorld.instance.CurrentCell.addLamppost(lightSource0);
 } else {
 Vector3f vector3f1 = this->getWorldPos(-0.4F, 0.0F, 0.0F, TL_vector3f_pool.get().alloc());
 int int4 = (int)vector3f1.x;
 int int5 = (int)vector3f1.y;
 int int6 = (int)(this->getZ() + 1.0F);
 TL_vector3f_pool.get().release(vector3f1);
 int int7 = this->rightLightIndex;
 if (int7 == 1 && this->rightLight1.x == int4 && this->rightLight1.y == int5 && this->rightLight1.z == int6) {
 return;
 }

 if (int7 == 2 && this->rightLight2.x == int4 && this->rightLight2.y == int5 && this->rightLight2.z == int6) {
 return;
 }

 this->removeWorldLights();
 IsoLightSource lightSource1;
 if (int7 == 1) {
 lightSource1 = this->rightLight2;
 this->rightLightIndex = 2;
 } else {
 lightSource1 = this->rightLight1;
 this->rightLightIndex = 1;
 }

 lightSource1.life = -1;
 lightSource1.x = int4;
 lightSource1.y = int5;
 lightSource1.z = int6;
 IsoWorld.instance.CurrentCell.addLamppost(lightSource1);
 }
 }
 }

 void fixLightbarModelLighting(IsoLightSource ls, Vector3f lightPos) {
 if (ls == this->leftLight1 || ls == this->leftLight2) {
 lightPos.set(1.0F, 0.0F, 0.0F);
 } else if (ls == this->rightLight1 || ls == this->rightLight2) {
 lightPos.set(-1.0F, 0.0F, 0.0F);
 }
 }

 void removeWorldLights() {
 if (this->leftLightIndex == 1) {
 IsoWorld.instance.CurrentCell.removeLamppost(this->leftLight1);
 this->leftLightIndex = -1;
 }

 if (this->leftLightIndex == 2) {
 IsoWorld.instance.CurrentCell.removeLamppost(this->leftLight2);
 this->leftLightIndex = -1;
 }

 if (this->rightLightIndex == 1) {
 IsoWorld.instance.CurrentCell.removeLamppost(this->rightLight1);
 this->rightLightIndex = -1;
 }

 if (this->rightLightIndex == 2) {
 IsoWorld.instance.CurrentCell.removeLamppost(this->rightLight2);
 this->rightLightIndex = -1;
 }
 }

 void doDamageOverlay() {
 if (this->sprite.modelSlot != nullptr) {
 this->doDoorDamage();
 this->doWindowDamage();
 this->doOtherBodyWorkDamage();
 this->doBloodOverlay();
 }
 }

 void checkDamage(VehiclePart part, int int0, bool boolean0) {
 if (boolean0 && part != nullptr && part.getId().startsWith("Window") && part.getScriptModelById("Default") != nullptr) {
 boolean0 = false;
 }

 VehicleModelInstance vehicleModelInstance = (VehicleModelInstance)this->sprite.modelSlot.model;

 try {
 vehicleModelInstance.textureDamage1Enables1[int0] = 0.0F;
 vehicleModelInstance.textureDamage2Enables1[int0] = 0.0F;
 vehicleModelInstance.textureUninstall1[int0] = 0.0F;
 if (part != nullptr && part.getInventoryItem() != nullptr) {
 if (part.getInventoryItem().getCondition() < 60 && part.getInventoryItem().getCondition() >= 40) {
 vehicleModelInstance.textureDamage1Enables1[int0] = 1.0F;
 }

 if (part.getInventoryItem().getCondition() < 40) {
 vehicleModelInstance.textureDamage2Enables1[int0] = 1.0F;
 }

 if (part.window != nullptr && part.window.isOpen() && boolean0) {
 vehicleModelInstance.textureUninstall1[int0] = 1.0F;
 }
 } else if (part != nullptr && boolean0) {
 vehicleModelInstance.textureUninstall1[int0] = 1.0F;
 }
 } catch (Exception exception) {
 exception.printStackTrace();
 }
 }

 void checkDamage2(VehiclePart part, int int0, bool boolean0) {
 VehicleModelInstance vehicleModelInstance = (VehicleModelInstance)this->sprite.modelSlot.model;

 try {
 vehicleModelInstance.textureDamage1Enables2[int0] = 0.0F;
 vehicleModelInstance.textureDamage2Enables2[int0] = 0.0F;
 vehicleModelInstance.textureUninstall2[int0] = 0.0F;
 if (part != nullptr && part.getInventoryItem() != nullptr) {
 if (part.getInventoryItem().getCondition() < 60 && part.getInventoryItem().getCondition() >= 40) {
 vehicleModelInstance.textureDamage1Enables2[int0] = 1.0F;
 }

 if (part.getInventoryItem().getCondition() < 40) {
 vehicleModelInstance.textureDamage2Enables2[int0] = 1.0F;
 }

 if (part.window != nullptr && part.window.isOpen() && boolean0) {
 vehicleModelInstance.textureUninstall2[int0] = 1.0F;
 }
 } else if (part != nullptr && boolean0) {
 vehicleModelInstance.textureUninstall2[int0] = 1.0F;
 }
 } catch (Exception exception) {
 exception.printStackTrace();
 }
 }

 void checkUninstall2(VehiclePart part, int int0) {
 VehicleModelInstance vehicleModelInstance = (VehicleModelInstance)this->sprite.modelSlot.model;

 try {
 vehicleModelInstance.textureUninstall2[int0] = 0.0F;
 if (part != nullptr && part.getInventoryItem() == nullptr) {
 vehicleModelInstance.textureUninstall2[int0] = 1.0F;
 }
 } catch (Exception exception) {
 exception.printStackTrace();
 }
 }

 void doOtherBodyWorkDamage() {
 this->checkDamage(this->getPartById("EngineDoor"), 0, false);
 this->checkDamage(this->getPartById("EngineDoor"), 3, false);
 this->checkDamage(this->getPartById("EngineDoor"), 11, false);
 this->checkDamage2(this->getPartById("EngineDoor"), 6, true);
 this->checkDamage(this->getPartById("TruckBed"), 4, false);
 this->checkDamage(this->getPartById("TruckBed"), 7, false);
 this->checkDamage(this->getPartById("TruckBed"), 15, false);
 VehiclePart part = this->getPartById("TrunkDoor");
 if (part != nullptr) {
 this->checkDamage2(part, 10, true);
 if (part.scriptPart.hasLightsRear) {
 this->checkUninstall2(part, 12);
 this->checkUninstall2(part, 1);
 this->checkUninstall2(part, 5);
 this->checkUninstall2(part, 9);
 }
 } else {
 part = this->getPartById("DoorRear");
 if (part != nullptr) {
 this->checkDamage2(part, 10, true);
 if (part.scriptPart.hasLightsRear) {
 this->checkUninstall2(part, 12);
 this->checkUninstall2(part, 1);
 this->checkUninstall2(part, 5);
 this->checkUninstall2(part, 9);
 }
 }
 }
 }

 void doWindowDamage() {
 this->checkDamage(this->getPartById("WindowFrontLeft"), 2, true);
 this->checkDamage(this->getPartById("WindowFrontRight"), 9, true);
 VehiclePart part = this->getPartById("WindowRearLeft");
 if (part != nullptr) {
 this->checkDamage(part, 6, true);
 } else {
 part = this->getPartById("WindowMiddleLeft");
 if (part != nullptr) {
 this->checkDamage(part, 6, true);
 }
 }

 part = this->getPartById("WindowRearRight");
 if (part != nullptr) {
 this->checkDamage(part, 13, true);
 } else {
 part = this->getPartById("WindowMiddleRight");
 if (part != nullptr) {
 this->checkDamage(part, 13, true);
 }
 }

 this->checkDamage(this->getPartById("Windshield"), 10, true);
 this->checkDamage(this->getPartById("WindshieldRear"), 14, true);
 }

 void doDoorDamage() {
 this->checkDamage(this->getPartById("DoorFrontLeft"), 1, true);
 this->checkDamage(this->getPartById("DoorFrontRight"), 8, true);
 VehiclePart part = this->getPartById("DoorRearLeft");
 if (part != nullptr) {
 this->checkDamage(part, 5, true);
 } else {
 part = this->getPartById("DoorMiddleLeft");
 if (part != nullptr) {
 this->checkDamage(part, 5, true);
 }
 }

 part = this->getPartById("DoorRearRight");
 if (part != nullptr) {
 this->checkDamage(part, 12, true);
 } else {
 part = this->getPartById("DoorMiddleRight");
 if (part != nullptr) {
 this->checkDamage(part, 12, true);
 }
 }
 }

 float getBloodIntensity(const std::string& id) {
 return (this->bloodIntensity.getOrDefault(id, BYTE_ZERO) & 255) / 100.0F;
 }

 void setBloodIntensity(const std::string& id, float intensity) {
 uint8_t byte0 = (byte)(PZMath.clamp(intensity, 0.0F, 1.0F) * 100.0F);
 if (!this->bloodIntensity.containsKey(id) || byte0 != this->bloodIntensity.get(id) {
 this->bloodIntensity.put(id, byte0);
 this->doBloodOverlay();
 this->transmitBlood();
 }
 }

 void transmitBlood() {
 if (GameServer.bServer) {
 this->updateFlags = (short)(this->updateFlags | 4096);
 }
 }

 void doBloodOverlay() {
 if (this->sprite.modelSlot != nullptr) {
 VehicleModelInstance vehicleModelInstance = (VehicleModelInstance)this->sprite.modelSlot.model;
 Arrays.fill(vehicleModelInstance.matrixBlood1Enables1, 0.0F);
 Arrays.fill(vehicleModelInstance.matrixBlood1Enables2, 0.0F);
 Arrays.fill(vehicleModelInstance.matrixBlood2Enables1, 0.0F);
 Arrays.fill(vehicleModelInstance.matrixBlood2Enables2, 0.0F);
 if (Core.getInstance().getOptionBloodDecals() != 0) {
 this->doBloodOverlayFront(vehicleModelInstance.matrixBlood1Enables1, vehicleModelInstance.matrixBlood1Enables2, this->getBloodIntensity("Front"));
 this->doBloodOverlayRear(vehicleModelInstance.matrixBlood1Enables1, vehicleModelInstance.matrixBlood1Enables2, this->getBloodIntensity("Rear"));
 this->doBloodOverlayLeft(vehicleModelInstance.matrixBlood1Enables1, vehicleModelInstance.matrixBlood1Enables2, this->getBloodIntensity("Left"));
 this->doBloodOverlayRight(vehicleModelInstance.matrixBlood1Enables1, vehicleModelInstance.matrixBlood1Enables2, this->getBloodIntensity("Right"));

 for (Entry entry : this->bloodIntensity.entrySet()) {
 int integer = s_PartToMaskMap.get(entry.getKey());
 if (integer != nullptr) {
 vehicleModelInstance.matrixBlood1Enables1[integer] = ((Byte)entry.getValue() & 255) / 100.0F;
 }
 }

 this->doBloodOverlayAux(vehicleModelInstance.matrixBlood2Enables1, vehicleModelInstance.matrixBlood2Enables2, 1.0F);
 }
 }
 }

 void doBloodOverlayAux(float[] floats0, float[] floats1, float float0) {
 floats0[0] = float0;
 floats1[6] = float0;
 floats1[4] = float0;
 floats1[8] = float0;
 floats0[4] = float0;
 floats0[7] = float0;
 floats0[15] = float0;
 floats1[10] = float0;
 floats1[12] = float0;
 floats1[1] = float0;
 floats1[5] = float0;
 floats1[9] = float0;
 floats0[3] = float0;
 floats0[8] = float0;
 floats0[12] = float0;
 floats0[11] = float0;
 floats0[1] = float0;
 floats0[5] = float0;
 floats1[0] = float0;
 floats0[10] = float0;
 floats0[14] = float0;
 floats0[9] = float0;
 floats0[13] = float0;
 floats0[2] = float0;
 floats0[6] = float0;
 }

 void doBloodOverlayFront(float[] floats0, float[] floats1, float float0) {
 floats0[0] = float0;
 floats1[6] = float0;
 floats1[4] = float0;
 floats1[8] = float0;
 floats0[10] = float0;
 }

 void doBloodOverlayRear(float[] floats0, float[] floats1, float float0) {
 floats0[4] = float0;
 floats1[10] = float0;
 floats1[12] = float0;
 floats1[1] = float0;
 floats1[5] = float0;
 floats1[9] = float0;
 floats0[14] = float0;
 }

 void doBloodOverlayLeft(float[] floats, float[] var2, float float0) {
 floats[11] = float0;
 floats[1] = float0;
 floats[5] = float0;
 floats[15] = float0;
 floats[2] = float0;
 floats[6] = float0;
 }

 void doBloodOverlayRight(float[] floats, float[] var2, float float0) {
 floats[3] = float0;
 floats[8] = float0;
 floats[12] = float0;
 floats[7] = float0;
 floats[9] = float0;
 floats[13] = float0;
 }

 void render(float x, float y, float z, ColorInfo col, bool bDoAttached, bool bWallLightingPass, Shader shader) {
 if (this->script != nullptr) {
 if (this->physics != nullptr) {
 this->physics.debug();
 }

 int int0 = IsoCamera.frameState.playerIndex;
 bool boolean0 = IsoCamera.CamCharacter != nullptr && IsoCamera.CamCharacter.getVehicle() == this;
 if (boolean0 || this->square.lighting[int0].bSeen()) {
 if (!boolean0 && !this->square.lighting[int0].bCouldSee()) {
 this->setTargetAlpha(int0, 0.0F);
 } else {
 this->setTargetAlpha(int0, 1.0F);
 }

 if (this->sprite.hasActiveModel()) {
 this->updateLights();
 bool boolean1 = Core.getInstance().getOptionBloodDecals() != 0;
 if (this->OptionBloodDecals != boolean1) {
 this->OptionBloodDecals = boolean1;
 this->doBloodOverlay();
 }

 col.a = this->getAlpha(int0);
 inf.a = col.a;
 inf.r = col.r;
 inf.g = col.g;
 inf.b = col.b;
 this->sprite.renderVehicle(this->def, this, x, y, 0.0F, 0.0F, 0.0F, inf, true);
 }

 this->updateAlpha(int0);
 if (Core.bDebug && DebugOptions.instance.VehicleRenderArea.getValue()) {
 this->renderAreas();
 }

 if (Core.bDebug && DebugOptions.instance.VehicleRenderAttackPositions.getValue()) {
 this->m_surroundVehicle.render();
 }

 if (Core.bDebug && DebugOptions.instance.VehicleRenderExit.getValue()) {
 this->renderExits();
 }

 if (Core.bDebug && DebugOptions.instance.VehicleRenderIntersectedSquares.getValue()) {
 this->renderIntersectedSquares();
 }

 if (Core.bDebug && DebugOptions.instance.VehicleRenderAuthorizations.getValue()) {
 this->renderAuthorizations();
 }

 if (Core.bDebug && DebugOptions.instance.VehicleRenderInterpolateBuffer.getValue()) {
 this->renderInterpolateBuffer();
 }

 if (DebugOptions.instance.VehicleRenderTrailerPositions.getValue()) {
 this->renderTrailerPositions();
 }

 this->renderUsableArea();
 }
 }
 }

 void renderlast() {
 int int0 = IsoCamera.frameState.playerIndex;

 for (int int1 = 0; int1 < this->parts.size(); int1++) {
 VehiclePart part = this->parts.get(int1);
 if (part.chatElement != nullptr && part.chatElement.getHasChatToDisplay()) {
 if (part.getDeviceData() != nullptr && !part.getDeviceData().getIsTurnedOn()) {
 part.chatElement.clear(int0);
 } else {
 float float0 = IsoUtils.XToScreen(this->getX(), this->getY(), this->getZ(), 0);
 float float1 = IsoUtils.YToScreen(this->getX(), this->getY(), this->getZ(), 0);
 float0 = float0 - IsoCamera.getOffX() - this->offsetX;
 float1 = float1 - IsoCamera.getOffY() - this->offsetY;
 float0 += 32 * Core.TileScale;
 float1 += 20 * Core.TileScale;
 float0 /= Core.getInstance().getZoom(int0);
 float1 /= Core.getInstance().getZoom(int0);
 part.chatElement.renderBatched(int0, (int)float0, (int)float1);
 }
 }
 }
 }

 void renderShadow() {
 if (this->physics != nullptr) {
 if (this->script != nullptr) {
 int int0 = IsoCamera.frameState.playerIndex;
 if (this->square.lighting[int0].bSeen()) {
 if (this->square.lighting[int0].bCouldSee()) {
 this->setTargetAlpha(int0, 1.0F);
 } else {
 this->setTargetAlpha(int0, 0.0F);
 }

 Texture texture = this->getShadowTexture();
 if (texture != nullptr && this->getCurrentSquare() != nullptr) {
 float float0 = 0.6F * this->getAlpha(int0);
 ColorInfo colorInfo = this->getCurrentSquare().lighting[int0].lightInfo();
 float0 *= (colorInfo.r + colorInfo.g + colorInfo.b) / 3.0F;
 if (this->polyDirty) {
 this->getPoly();
 }

 SpriteRenderer.instance
 .renderPoly(
 texture,
 (int)IsoUtils.XToScreenExact(this->shadowCoord.x2, this->shadowCoord.y2, 0.0F, 0),
 (int)IsoUtils.YToScreenExact(this->shadowCoord.x2, this->shadowCoord.y2, 0.0F, 0),
 (int)IsoUtils.XToScreenExact(this->shadowCoord.x1, this->shadowCoord.y1, 0.0F, 0),
 (int)IsoUtils.YToScreenExact(this->shadowCoord.x1, this->shadowCoord.y1, 0.0F, 0),
 (int)IsoUtils.XToScreenExact(this->shadowCoord.x4, this->shadowCoord.y4, 0.0F, 0),
 (int)IsoUtils.YToScreenExact(this->shadowCoord.x4, this->shadowCoord.y4, 0.0F, 0),
 (int)IsoUtils.XToScreenExact(this->shadowCoord.x3, this->shadowCoord.y3, 0.0F, 0),
 (int)IsoUtils.YToScreenExact(this->shadowCoord.x3, this->shadowCoord.y3, 0.0F, 0),
 1.0F,
 1.0F,
 1.0F,
 0.8F * float0
 );
 }
 }
 }
 }
 }

 bool isEnterBlocked(IsoGameCharacter chr, int seat) {
 return this->isExitBlocked(chr, seat);
 }

 bool isExitBlocked(int seat) {
 VehicleScript.Position position0 = this->getPassengerPosition(seat, "inside");
 VehicleScript.Position position1 = this->getPassengerPosition(seat, "outside");
 if (position0 != nullptr && position1 != nullptr) {
 Vector3f vector3f0 = this->getPassengerPositionWorldPos(position1, TL_vector3f_pool.get().alloc());
 if (position1.area != nullptr) {
 Vector2 vector0 = TL_vector2_pool.get().alloc();
 VehicleScript.Area area = this->script.getAreaById(position1.area);
 Vector2 vector1 = this->areaPositionWorld4PlayerInteract(area, vector0);
 if (vector1 != nullptr) {
 vector3f0.x = vector1.x;
 vector3f0.y = vector1.y;
 }

 TL_vector2_pool.get().release(vector0);
 }

 vector3f0.z = 0.0F;
 Vector3f vector3f1 = this->getPassengerPositionWorldPos(position0, TL_vector3f_pool.get().alloc());
 bool boolean0 = PolygonalMap2.instance.lineClearCollide(vector3f1.x, vector3f1.y, vector3f0.x, vector3f0.y, (int)this->z, this, false, false);
 TL_vector3f_pool.get().release(vector3f0);
 TL_vector3f_pool.get().release(vector3f1);
 return boolean0;
 } else {
 return true;
 }
 }

 bool isExitBlocked(IsoGameCharacter chr, int seat) {
 VehicleScript.Position position0 = this->getPassengerPosition(seat, "inside");
 VehicleScript.Position position1 = this->getPassengerPosition(seat, "outside");
 if (position0 != nullptr && position1 != nullptr) {
 Vector3f vector3f0 = this->getPassengerPositionWorldPos(position1, TL_vector3f_pool.get().alloc());
 if (position1.area != nullptr) {
 Vector2 vector0 = TL_vector2_pool.get().alloc();
 VehicleScript.Area area = this->script.getAreaById(position1.area);
 Vector2 vector1 = this->areaPositionWorld4PlayerInteract(area, vector0);
 if (vector1 != nullptr) {
 vector3f0.x = vector1.x;
 vector3f0.y = vector1.y;
 }

 TL_vector2_pool.get().release(vector0);
 }

 vector3f0.z = 0.0F;
 Vector3f vector3f1 = this->getPassengerPositionWorldPos(position0, TL_vector3f_pool.get().alloc());
 bool boolean0 = PolygonalMap2.instance.lineClearCollide(vector3f1.x, vector3f1.y, vector3f0.x, vector3f0.y, (int)this->z, this, false, false);
 TL_vector3f_pool.get().release(vector3f0);
 TL_vector3f_pool.get().release(vector3f1);
 if (!boolean0 && GameClient.bClient) {
 IsoGridSquare square = IsoWorld.instance.CurrentCell.getGridSquare((double)vector3f0.x, (double)vector3f0.y, (double)vector3f0.z);
 if (square != nullptr && chr instanceof IsoPlayer && !SafeHouse.isPlayerAllowedOnSquare((IsoPlayer)chr, square) {
 boolean0 = true;
 }
 }

 return boolean0;
 } else {
 return true;
 }
 }

 bool isPassengerUseDoor2(IsoGameCharacter chr, int seat) {
 VehicleScript.Position position = this->getPassengerPosition(seat, "outside2");
 if (position != nullptr) {
 Vector3f vector3f = this->getPassengerPositionWorldPos(position, TL_vector3f_pool.get().alloc());
 vector3f.sub(chr.x, chr.y, chr.z);
 float float0 = vector3f.length();
 TL_vector3f_pool.get().release(vector3f);
 if (float0 < 2.0F) {
 return true;
 }
 }

 return false;
 }

 bool isEnterBlocked2(IsoGameCharacter chr, int seat) {
 return this->isExitBlocked2(seat);
 }

 bool isExitBlocked2(int seat) {
 VehicleScript.Position position0 = this->getPassengerPosition(seat, "inside");
 VehicleScript.Position position1 = this->getPassengerPosition(seat, "outside2");
 if (position0 != nullptr && position1 != nullptr) {
 Vector3f vector3f0 = this->getPassengerPositionWorldPos(position1, TL_vector3f_pool.get().alloc());
 vector3f0.z = 0.0F;
 Vector3f vector3f1 = this->getPassengerPositionWorldPos(position0, TL_vector3f_pool.get().alloc());
 bool boolean0 = PolygonalMap2.instance.lineClearCollide(vector3f1.x, vector3f1.y, vector3f0.x, vector3f0.y, (int)this->z, this, false, false);
 IsoGridSquare square = IsoWorld.instance.CurrentCell.getGridSquare((double)vector3f0.x, (double)vector3f0.y, (double)vector3f0.z);
 IsoGameCharacter character = this->getCharacter(seat);
 if (character instanceof IsoPlayer && !SafeHouse.isPlayerAllowedOnSquare((IsoPlayer)character, square) {
 boolean0 = true;
 }

 TL_vector3f_pool.get().release(vector3f0);
 TL_vector3f_pool.get().release(vector3f1);
 return boolean0;
 } else {
 return true;
 }
 }

 void renderExits() {
 int int0 = Core.TileScale;
 Vector3f vector3f0 = TL_vector3f_pool.get().alloc();
 Vector3f vector3f1 = TL_vector3f_pool.get().alloc();

 for (int int1 = 0; int1 < this->getMaxPassengers(); int1++) {
 VehicleScript.Position position0 = this->getPassengerPosition(int1, "inside");
 VehicleScript.Position position1 = this->getPassengerPosition(int1, "outside");
 if (position0 != nullptr && position1 != nullptr) {
 float float0 = 0.3F;
 this->getPassengerPositionWorldPos(position1, vector3f0);
 this->getPassengerPositionWorldPos(position0, vector3f1);
 int int2 = (int)Math.floor(vector3f0.x - float0);
 int int3 = (int)Math.floor(vector3f0.x + float0);
 int int4 = (int)Math.floor(vector3f0.y - float0);
 int int5 = (int)Math.floor(vector3f0.y + float0);

 for (int int6 = int4; int6 <= int5; int6++) {
 for (int int7 = int2; int7 <= int3; int7++) {
 int int8 = (int)IsoUtils.XToScreenExact(int7, int6 + 1, (int)this->z, 0);
 int int9 = (int)IsoUtils.YToScreenExact(int7, int6 + 1, (int)this->z, 0);
 SpriteRenderer.instance
 .renderPoly(
 int8,
 int9,
 int8 + 32 * int0,
 int9 - 16 * int0,
 int8 + 64 * int0,
 int9,
 int8 + 32 * int0,
 int9 + 16 * int0,
 1.0F,
 1.0F,
 1.0F,
 0.5F
 );
 }
 }

 float float1 = 1.0F;
 float float2 = 1.0F;
 float float3 = 1.0F;
 if (this->isExitBlocked(int1) {
 float3 = 0.0F;
 float2 = 0.0F;
 }

 this->getController().drawCircle(vector3f1.x, vector3f1.y, float0, 0.0F, 0.0F, 1.0F, 1.0F);
 this->getController().drawCircle(vector3f0.x, vector3f0.y, float0, float1, float2, float3, 1.0F);
 }
 }

 TL_vector3f_pool.get().release(vector3f0);
 TL_vector3f_pool.get().release(vector3f1);
 }

 Vector2 areaPositionLocal(VehicleScript.Area area) {
 return this->areaPositionLocal(area, std::make_unique<Vector2>());
 }

 Vector2 areaPositionLocal(VehicleScript.Area area, Vector2 vector1) {
 Vector2 vector0 = this->areaPositionWorld(area, vector1);
 Vector3f vector3f = TL_vector3f_pool.get().alloc();
 this->getLocalPos(vector0.x, vector0.y, 0.0F, vector3f);
 vector0.set(vector3f.x, vector3f.z);
 TL_vector3f_pool.get().release(vector3f);
 return vector0;
 }

 Vector2 areaPositionWorld(VehicleScript.Area area) {
 return this->areaPositionWorld(area, std::make_unique<Vector2>());
 }

 Vector2 areaPositionWorld(VehicleScript.Area area, Vector2 out) {
 if (area == nullptr) {
 return nullptr;
 } else {
 Vector3f vector3f = this->getWorldPos(area.x, 0.0F, area.y, TL_vector3f_pool.get().alloc());
 out.set(vector3f.x, vector3f.y);
 TL_vector3f_pool.get().release(vector3f);
 return out;
 }
 }

 Vector2 areaPositionWorld4PlayerInteract(VehicleScript.Area area) {
 return this->areaPositionWorld4PlayerInteract(area, std::make_unique<Vector2>());
 }

 Vector2 areaPositionWorld4PlayerInteract(VehicleScript.Area area, Vector2 out) {
 Vector3f vector3f0 = this->script.getExtents();
 Vector3f vector3f1 = this->script.getCenterOfMassOffset();
 Vector2 vector = this->areaPositionWorld(area, out);
 Vector3f vector3f2 = this->getLocalPos(vector.x, vector.y, 0.0F, TL_vector3f_pool.get().alloc());
 if (!(area.x > vector3f1.x + vector3f0.x / 2.0F) && !(area.x < vector3f1.x - vector3f0.x / 2.0F) {
 if (area.y > 0.0F) {
 vector3f2.z = vector3f2.z - area.h * 0.3F;
 } else {
 vector3f2.z = vector3f2.z + area.h * 0.3F;
 }
 } else if (area.x > 0.0F) {
 vector3f2.x = vector3f2.x - area.w * 0.3F;
 } else {
 vector3f2.x = vector3f2.x + area.w * 0.3F;
 }

 this->getWorldPos(vector3f2, vector3f2);
 out.set(vector3f2.x, vector3f2.y);
 TL_vector3f_pool.get().release(vector3f2);
 return out;
 }

 void renderAreas() {
 if (this->getScript() != nullptr) {
 Vector3f vector3f = this->getForwardVector(TL_vector3f_pool.get().alloc());
 Vector2 vector0 = TL_vector2_pool.get().alloc();

 for (int int0 = 0; int0 < this->parts.size(); int0++) {
 VehiclePart part = this->parts.get(int0);
 if (part.getArea() != nullptr) {
 VehicleScript.Area area = this->getScript().getAreaById(part.getArea());
 if (area != nullptr) {
 Vector2 vector1 = this->areaPositionWorld(area, vector0);
 if (vector1 != nullptr) {
 bool boolean0 = this->isInArea(area.id, IsoPlayer.getInstance());
 this->getController()
 .drawRect(
 vector3f,
 vector1.x - WorldSimulation.instance.offsetX,
 vector1.y - WorldSimulation.instance.offsetY,
 area.w,
 area.h / 2.0F,
 boolean0 ? 0.0F : 0.65F,
 boolean0 ? 1.0F : 0.65F,
 boolean0 ? 1.0F : 0.65F
 );
 vector1 = this->areaPositionWorld4PlayerInteract(area, vector0);
 this->getController()
 .drawRect(
 vector3f,
 vector1.x - WorldSimulation.instance.offsetX,
 vector1.y - WorldSimulation.instance.offsetY,
 0.1F,
 0.1F,
 1.0F,
 0.0F,
 0.0F
 );
 }
 }
 }
 }

 TL_vector3f_pool.get().release(vector3f);
 TL_vector2_pool.get().release(vector0);
 LineDrawer.drawLine(
 IsoUtils.XToScreenExact(this->poly.x1, this->poly.y1, 0.0F, 0),
 IsoUtils.YToScreenExact(this->poly.x1, this->poly.y1, 0.0F, 0),
 IsoUtils.XToScreenExact(this->poly.x2, this->poly.y2, 0.0F, 0),
 IsoUtils.YToScreenExact(this->poly.x2, this->poly.y2, 0.0F, 0),
 1.0F,
 0.5F,
 0.5F,
 1.0F,
 0
 );
 LineDrawer.drawLine(
 IsoUtils.XToScreenExact(this->poly.x2, this->poly.y2, 0.0F, 0),
 IsoUtils.YToScreenExact(this->poly.x2, this->poly.y2, 0.0F, 0),
 IsoUtils.XToScreenExact(this->poly.x3, this->poly.y3, 0.0F, 0),
 IsoUtils.YToScreenExact(this->poly.x3, this->poly.y3, 0.0F, 0),
 1.0F,
 0.5F,
 0.5F,
 1.0F,
 0
 );
 LineDrawer.drawLine(
 IsoUtils.XToScreenExact(this->poly.x3, this->poly.y3, 0.0F, 0),
 IsoUtils.YToScreenExact(this->poly.x3, this->poly.y3, 0.0F, 0),
 IsoUtils.XToScreenExact(this->poly.x4, this->poly.y4, 0.0F, 0),
 IsoUtils.YToScreenExact(this->poly.x4, this->poly.y4, 0.0F, 0),
 1.0F,
 0.5F,
 0.5F,
 1.0F,
 0
 );
 LineDrawer.drawLine(
 IsoUtils.XToScreenExact(this->poly.x4, this->poly.y4, 0.0F, 0),
 IsoUtils.YToScreenExact(this->poly.x4, this->poly.y4, 0.0F, 0),
 IsoUtils.XToScreenExact(this->poly.x1, this->poly.y1, 0.0F, 0),
 IsoUtils.YToScreenExact(this->poly.x1, this->poly.y1, 0.0F, 0),
 1.0F,
 0.5F,
 0.5F,
 1.0F,
 0
 );
 LineDrawer.drawLine(
 IsoUtils.XToScreenExact(this->shadowCoord.x1, this->shadowCoord.y1, 0.0F, 0),
 IsoUtils.YToScreenExact(this->shadowCoord.x1, this->shadowCoord.y1, 0.0F, 0),
 IsoUtils.XToScreenExact(this->shadowCoord.x2, this->shadowCoord.y2, 0.0F, 0),
 IsoUtils.YToScreenExact(this->shadowCoord.x2, this->shadowCoord.y2, 0.0F, 0),
 0.5F,
 1.0F,
 0.5F,
 1.0F,
 0
 );
 LineDrawer.drawLine(
 IsoUtils.XToScreenExact(this->shadowCoord.x2, this->shadowCoord.y2, 0.0F, 0),
 IsoUtils.YToScreenExact(this->shadowCoord.x2, this->shadowCoord.y2, 0.0F, 0),
 IsoUtils.XToScreenExact(this->shadowCoord.x3, this->shadowCoord.y3, 0.0F, 0),
 IsoUtils.YToScreenExact(this->shadowCoord.x3, this->shadowCoord.y3, 0.0F, 0),
 0.5F,
 1.0F,
 0.5F,
 1.0F,
 0
 );
 LineDrawer.drawLine(
 IsoUtils.XToScreenExact(this->shadowCoord.x3, this->shadowCoord.y3, 0.0F, 0),
 IsoUtils.YToScreenExact(this->shadowCoord.x3, this->shadowCoord.y3, 0.0F, 0),
 IsoUtils.XToScreenExact(this->shadowCoord.x4, this->shadowCoord.y4, 0.0F, 0),
 IsoUtils.YToScreenExact(this->shadowCoord.x4, this->shadowCoord.y4, 0.0F, 0),
 0.5F,
 1.0F,
 0.5F,
 1.0F,
 0
 );
 LineDrawer.drawLine(
 IsoUtils.XToScreenExact(this->shadowCoord.x4, this->shadowCoord.y4, 0.0F, 0),
 IsoUtils.YToScreenExact(this->shadowCoord.x4, this->shadowCoord.y4, 0.0F, 0),
 IsoUtils.XToScreenExact(this->shadowCoord.x1, this->shadowCoord.y1, 0.0F, 0),
 IsoUtils.YToScreenExact(this->shadowCoord.x1, this->shadowCoord.y1, 0.0F, 0),
 0.5F,
 1.0F,
 0.5F,
 1.0F,
 0
 );
 }
 }

 void renderInterpolateBuffer() {
 if (this->netPlayerAuthorization == BaseVehicle.Authorization.Remote) {
 float float0 = IsoUtils.XToScreenExact(this->x, this->y, 0.0F, 0);
 float float1 = IsoUtils.YToScreenExact(this->x, this->y, 0.0F, 0);
 float float2 = float0 - 310.0F;
 float float3 = float1 + 22.0F;
 float float4 = 300.0F;
 float float5 = 150.0F;
 float float6 = 4.0F;
 Color color0 = Color.lightGray;
 Color color1 = Color.green;
 Color color2 = Color.cyan;
 Color color3 = Color.yellow;
 Color color4 = Color.blue;
 Color color5 = Color.red;
 LineDrawer.drawLine(float2, float3, float2 + float4, float3, color0.r, color0.g, color0.b, color0.a, 1);
 LineDrawer.drawLine(float2, float3 + float5, float2 + float4, float3 + float5, color0.r, color0.g, color0.b, color0.a, 1);
 long long0 = GameTime.getServerTimeMills();
 long long1 = long0 - 150L - this->interpolation.history;
 long long2 = long0 + 150L;
 this->renderInterpolateBuffer_drawVertLine(long1, color0, float2, float3, float4, float5, long1, long2, true);
 this->renderInterpolateBuffer_drawVertLine(long2, color0, float2, float3, float4, float5, long1, long2, true);
 this->renderInterpolateBuffer_drawVertLine(long0, color1, float2, float3, float4, float5, long1, long2, true);
 this->renderInterpolateBuffer_drawVertLine(long0 - this->interpolation.delay, color2, float2, float3, float4, float5, long1, long2, true);
 this->renderInterpolateBuffer_drawPoint(
 long0 - this->interpolation.delay, this->x, color4, 5, float2, float3, float4, float5, long1, long2, this->x - float6, this->x + float6
 );
 this->renderInterpolateBuffer_drawPoint(
 long0 - this->interpolation.delay, this->y, color5, 5, float2, float3, float4, float5, long1, long2, this->y - float6, this->y + float6
 );
 long long3 = 0L;
 float float7 = Float.NaN;
 float float8 = Float.NaN;
 VehicleInterpolationData vehicleInterpolationData0 = new VehicleInterpolationData();
 vehicleInterpolationData0.time = long0 - this->interpolation.delay;
 VehicleInterpolationData vehicleInterpolationData1 = this->interpolation.buffer.higher(vehicleInterpolationData0);
 VehicleInterpolationData vehicleInterpolationData2 = this->interpolation.buffer.floor(vehicleInterpolationData0);

 for (VehicleInterpolationData vehicleInterpolationData3 : this->interpolation.buffer) {
 bool boolean0 = (vehicleInterpolationData3.hashCode() & 1) == 0;
 this->renderInterpolateBuffer_drawVertLine(vehicleInterpolationData3.time, color3, float2, float3, float4, float5, long1, long2, boolean0);
 if (vehicleInterpolationData3 == vehicleInterpolationData1) {
 this->renderInterpolateBuffer_drawTextHL(vehicleInterpolationData3.time, "H", color2, float2, float3, float4, float5, long1, long2);
 }

 if (vehicleInterpolationData3 == vehicleInterpolationData2) {
 this->renderInterpolateBuffer_drawTextHL(vehicleInterpolationData3.time, "L", color2, float2, float3, float4, float5, long1, long2);
 }

 this->renderInterpolateBuffer_drawPoint(
 vehicleInterpolationData3.time,
 vehicleInterpolationData3.x,
 color4,
 5,
 float2,
 float3,
 float4,
 float5,
 long1,
 long2,
 this->x - float6,
 this->x + float6
 );
 this->renderInterpolateBuffer_drawPoint(
 vehicleInterpolationData3.time,
 vehicleInterpolationData3.y,
 color5,
 5,
 float2,
 float3,
 float4,
 float5,
 long1,
 long2,
 this->y - float6,
 this->y + float6
 );
 if (!Float.isNaN(float7) {
 this->renderInterpolateBuffer_drawLine(
 long3,
 float7,
 vehicleInterpolationData3.time,
 vehicleInterpolationData3.x,
 color4,
 float2,
 float3,
 float4,
 float5,
 long1,
 long2,
 this->x - float6,
 this->x + float6
 );
 this->renderInterpolateBuffer_drawLine(
 long3,
 float8,
 vehicleInterpolationData3.time,
 vehicleInterpolationData3.y,
 color5,
 float2,
 float3,
 float4,
 float5,
 long1,
 long2,
 this->y - float6,
 this->y + float6
 );
 }

 long3 = vehicleInterpolationData3.time;
 float7 = vehicleInterpolationData3.x;
 float8 = vehicleInterpolationData3.y;
 }

 float[] floats0 = new float[27];
 float[] floats1 = new float[2];
 bool boolean1 = this->interpolation.interpolationDataGet(floats0, floats1, long0 - this->interpolation.delay);
 TextManager.instance
 .DrawString(
 float2,
 float3 + float5 + 20.0F,
 String.format("interpolationDataGet=%s", boolean1 ? "True" : "False"),
 color2.r,
 color2.g,
 color2.b,
 color2.a
 );
 TextManager.instance
 .DrawString(
 float2,
 float3 + float5 + 30.0F,
 String.format("buffer.size=%d buffering=%s", this->interpolation.buffer.size(), String.valueOf(this->interpolation.buffering),
 color2.r,
 color2.g,
 color2.b,
 color2.a
 );
 if (this->interpolation.buffer.size() >= 2) {
 TextManager.instance
 .DrawString(
 float2,
 float3 + float5 + 40.0F,
 String.format("last=%d first=%d", this->interpolation.buffer.last().time, this->interpolation.buffer.first().time),
 color2.r,
 color2.g,
 color2.b,
 color2.a
 );
 TextManager.instance
 .DrawString(
 float2,
 float3 + float5 + 50.0F,
 String.format(
 "(last-first).time=%d delay=%d",
 this->interpolation.buffer.last().time - this->interpolation.buffer.first().time,
 this->interpolation.delay
 ),
 color2.r,
 color2.g,
 color2.b,
 color2.a
 );
 }
 }
 }

 private void renderInterpolateBuffer_drawTextHL(
 long long2, String string, Color color, float float4, float float3, float float1, float var8, long long1, long long0
 ) {
 float float0 = float1 / (float)(long0 - long1);
 float float2 = (float)(long2 - long1) * float0;
 TextManager.instance.DrawString(float2 + float4, float3, string, color.r, color.g, color.b, color.a);
 }

 private void renderInterpolateBuffer_drawVertLine(
 long long2, Color color, float float5, float float3, float float1, float float4, long long1, long long0, boolean boolean0
 ) {
 float float0 = float1 / (float)(long0 - long1);
 float float2 = (float)(long2 - long1) * float0;
 LineDrawer.drawLine(float2 + float5, float3, float2 + float5, float3 + float4, color.r, color.g, color.b, color.a, 1);
 TextManager.instance
 .DrawString(
 float2 + float5,
 float3 + float4 + (boolean0 ? 0.0F : 10.0F),
 String.format("%.1f", (float)(long2 - long2 / 100000L * 100000L) / 1000.0F),
 color.r,
 color.g,
 color.b,
 color.a
 );
 }

 private void renderInterpolateBuffer_drawLine(
 long long2,
 float float9,
 long long3,
 float float11,
 Color color,
 float float13,
 float float12,
 float float1,
 float float5,
 long long1,
 long long0,
 float float7,
 float float6
 ) {
 float float0 = float1 / (float)(long0 - long1);
 float float2 = (float)(long2 - long1) * float0;
 float float3 = (float)(long3 - long1) * float0;
 float float4 = float5 / (float6 - float7);
 float float8 = (float9 - float7) * float4;
 float float10 = (float11 - float7) * float4;
 LineDrawer.drawLine(float2 + float13, float8 + float12, float3 + float13, float10 + float12, color.r, color.g, color.b, color.a, 1);
 }

 private void renderInterpolateBuffer_drawPoint(
 long long2,
 float float8,
 Color color,
 int int0,
 float float10,
 float float9,
 float float1,
 float float4,
 long long1,
 long long0,
 float float6,
 float float5
 ) {
 float float0 = float1 / (float)(long0 - long1);
 float float2 = (float)(long2 - long1) * float0;
 float float3 = float4 / (float5 - float6);
 float float7 = (float8 - float6) * float3;
 LineDrawer.drawCircle(float2 + float10, float7 + float9, int0, 10, color.r, color.g, color.b);
 }

 void renderAuthorizations() {
 float float0 = 0.3F;
 float float1 = 0.3F;
 float float2 = 0.3F;
 float float3 = 0.5F;
 switch (this->netPlayerAuthorization) {
 case Server:
 float0 = 1.0F;
 break;
 case LocalCollide:
 float2 = 1.0F;
 break;
 case Local:
 float1 = 1.0F;
 break;
 case Remote:
 float1 = 1.0F;
 float0 = 1.0F;
 break;
 case RemoteCollide:
 float2 = 1.0F;
 float0 = 1.0F;
 }

 LineDrawer.drawLine(
 IsoUtils.XToScreenExact(this->poly.x1, this->poly.y1, 0.0F, 0),
 IsoUtils.YToScreenExact(this->poly.x1, this->poly.y1, 0.0F, 0),
 IsoUtils.XToScreenExact(this->poly.x2, this->poly.y2, 0.0F, 0),
 IsoUtils.YToScreenExact(this->poly.x2, this->poly.y2, 0.0F, 0),
 float0,
 float1,
 float2,
 float3,
 1
 );
 LineDrawer.drawLine(
 IsoUtils.XToScreenExact(this->poly.x2, this->poly.y2, 0.0F, 0),
 IsoUtils.YToScreenExact(this->poly.x2, this->poly.y2, 0.0F, 0),
 IsoUtils.XToScreenExact(this->poly.x3, this->poly.y3, 0.0F, 0),
 IsoUtils.YToScreenExact(this->poly.x3, this->poly.y3, 0.0F, 0),
 float0,
 float1,
 float2,
 float3,
 1
 );
 LineDrawer.drawLine(
 IsoUtils.XToScreenExact(this->poly.x3, this->poly.y3, 0.0F, 0),
 IsoUtils.YToScreenExact(this->poly.x3, this->poly.y3, 0.0F, 0),
 IsoUtils.XToScreenExact(this->poly.x4, this->poly.y4, 0.0F, 0),
 IsoUtils.YToScreenExact(this->poly.x4, this->poly.y4, 0.0F, 0),
 float0,
 float1,
 float2,
 float3,
 1
 );
 LineDrawer.drawLine(
 IsoUtils.XToScreenExact(this->poly.x4, this->poly.y4, 0.0F, 0),
 IsoUtils.YToScreenExact(this->poly.x4, this->poly.y4, 0.0F, 0),
 IsoUtils.XToScreenExact(this->poly.x1, this->poly.y1, 0.0F, 0),
 IsoUtils.YToScreenExact(this->poly.x1, this->poly.y1, 0.0F, 0),
 float0,
 float1,
 float2,
 float3,
 1
 );
 float float4 = 0.0F;
 if (this->getVehicleTowing() != nullptr) {
 BaseVehicle.Vector3fObjectPool vector3fObjectPool = TL_vector3f_pool.get();
 Vector3f vector3f0 = vector3fObjectPool.alloc();
 Vector3f vector3f1 = this->getTowingWorldPos(this->getTowAttachmentSelf(), vector3f0);
 Vector3f vector3f2 = vector3fObjectPool.alloc();
 Vector3f vector3f3 = this->getVehicleTowing().getTowingWorldPos(this->getVehicleTowing().getTowAttachmentSelf(), vector3f2);
 if (vector3f1 != nullptr && vector3f3 != nullptr) {
 LineDrawer.DrawIsoLine(vector3f1.x, vector3f1.y, vector3f1.z, vector3f3.x, vector3f3.y, vector3f3.z, float0, float1, float2, float3, 1);
 LineDrawer.DrawIsoCircle(vector3f1.x, vector3f1.y, vector3f1.z, 0.2F, 16, float0, float1, float2, float3);
 float4 = IsoUtils.DistanceTo(vector3f1.x, vector3f1.y, vector3f1.z, vector3f3.x, vector3f3.y, vector3f3.z);
 }

 vector3fObjectPool.release(vector3f0);
 vector3fObjectPool.release(vector3f2);
 }

 float0 = 1.0F;
 float1 = 1.0F;
 float2 = 0.75F;
 float3 = 1.0F;
 float float5 = 10.0F;
 float float6 = IsoUtils.XToScreenExact(this->x, this->y, 0.0F, 0);
 float float7 = IsoUtils.YToScreenExact(this->x, this->y, 0.0F, 0);
 IsoPlayer player = GameClient.IDToPlayerMap.get(this->netPlayerId);
 std::string string = (player == nullptr ? "@server" : player.getUsername()) + " ( " + this->netPlayerId + " )";
 float float8;
 TextManager.instance
 .DrawString(
 float6, float7 + (float8 = float5 + 12.0F), "VID: " + this->getScriptName() + " ( " + this->getId() + " )", float0, float1, float2, float3
 );
 TextManager.instance.DrawString(float6, float7 + (float5 = float8 + 12.0F), "PID: " + string, float0, float1, float2, float3);
 float float9;
 TextManager.instance
 .DrawString(float6, float7 + (float9 = float5 + 12.0F), "Auth: " + this->netPlayerAuthorization.name(), float0, float1, float2, float3);
 TextManager.instance
 .DrawString(float6, float7 + (float5 = float9 + 12.0F), "Static/active: " + this->isStatic + "/" + this->isActive, float0, float1, float2, float3);
 float float10;
 TextManager.instance.DrawString(float6, float7 + (float10 = float5 + 12.0F), "x=" + this->x + " / y=" + this->y, float0, float1, float2, float3);
 TextManager.instance
 .DrawString(
 float6,
 float7 + (float5 = float10 + 14.0F),
 String.format(
 "Passengers: %d/%d", Arrays.stream(this->passengers).filter(passenger -> passenger.character != nullptr).count(), this->passengers.length
 ),
 float0,
 float1,
 float2,
 float3
 );
 float float11;
 TextManager.instance
 .DrawString(
 float6,
 float7 + (float11 = float5 + 12.0F),
 String.format("Speed: %s%.3f kmph", this->getCurrentSpeedKmHour() >= 0.0F ? "+" : "", this->getCurrentSpeedKmHour()),
 float0,
 float1,
 float2,
 float3
 );
 TextManager.instance
 .DrawString(float6, float7 + (float5 = float11 + 12.0F), String.format("Engine speed: %.3f", this->engineSpeed), float0, float1, float2, float3);
 float float12;
 TextManager.instance
 .DrawString(
 float6,
 float7 + (float12 = float5 + 12.0F),
 String.format("Mass: %.3f/%.3f", this->getMass(), this->getFudgedMass()),
 float0,
 float1,
 float2,
 float3
 );
 if (float4 > 1.5F) {
 float1 = 0.75F;
 }

 if (this->getVehicleTowing() != nullptr) {
 TextManager.instance
 .DrawString(float6, float7 + (float5 = float12 + 14.0F), "Towing: " + this->getVehicleTowing().getId(), float0, float1, float2, float3);
 TextManager.instance
 .DrawString(float6, float7 + (float12 = float5 + 12.0F), String.format("Distance: %.3f", float4), float0, float1, float2, float3);
 }

 if (this->getVehicleTowedBy() != nullptr) {
 TextManager.instance
 .DrawString(float6, float7 + (float5 = float12 + 14.0F), "TowedBy: " + this->getVehicleTowedBy().getId(), float0, float1, float2, float3);
 float float13;
 TextManager.instance
 .DrawString(float6, float7 + (float13 = float5 + 12.0F), String.format("Distance: %.3f", float4), float0, float1, float2, float3);
 }
 }

 void renderUsableArea() {
 if (this->getScript() != nullptr && UIManager.VisibleAllUI) {
 VehiclePart part = this->getUseablePart(IsoPlayer.getInstance());
 if (part != nullptr) {
 VehicleScript.Area area = this->getScript().getAreaById(part.getArea());
 if (area != nullptr) {
 Vector2 vector0 = TL_vector2_pool.get().alloc();
 Vector2 vector1 = this->areaPositionWorld(area, vector0);
 if (vector1 == nullptr) {
 TL_vector2_pool.get().release(vector0);
 } else {
 Vector3f vector3f = this->getForwardVector(TL_vector3f_pool.get().alloc());
 float float0 = Core.getInstance().getGoodHighlitedColor().getR();
 float float1 = Core.getInstance().getGoodHighlitedColor().getG();
 float float2 = Core.getInstance().getGoodHighlitedColor().getB();
 this->getController()
 .drawRect(
 vector3f,
 vector1.x - WorldSimulation.instance.offsetX,
 vector1.y - WorldSimulation.instance.offsetY,
 area.w,
 area.h / 2.0F,
 float0,
 float1,
 float2
 );
 vector3f.x = vector3f.x * (area.h / this->script.getModelScale());
 vector3f.z = vector3f.z * (area.h / this->script.getModelScale());
 if (part.getDoor() != nullptr && (part.getId().contains("Left") || part.getId().contains("Right"))) {
 if (part.getId().contains("Front")) {
 this->getController()
 .drawRect(
 vector3f,
 vector1.x - WorldSimulation.instance.offsetX + vector3f.x * area.h / 2.0F,
 vector1.y - WorldSimulation.instance.offsetY + vector3f.z * area.h / 2.0F,
 area.w,
 area.h / 8.0F,
 float0,
 float1,
 float2
 );
 } else if (part.getId().contains("Rear")) {
 this->getController()
 .drawRect(
 vector3f,
 vector1.x - WorldSimulation.instance.offsetX - vector3f.x * area.h / 2.0F,
 vector1.y - WorldSimulation.instance.offsetY - vector3f.z * area.h / 2.0F,
 area.w,
 area.h / 8.0F,
 float0,
 float1,
 float2
 );
 }
 }

 TL_vector2_pool.get().release(vector0);
 TL_vector3f_pool.get().release(vector3f);
 }
 }
 }
 }
 }

 void renderIntersectedSquares() {
 PolygonalMap2.VehiclePoly vehiclePoly = this->getPoly();
 float float0 = Math.min(vehiclePoly.x1, Math.min(vehiclePoly.x2, Math.min(vehiclePoly.x3, vehiclePoly.x4);
 float float1 = Math.min(vehiclePoly.y1, Math.min(vehiclePoly.y2, Math.min(vehiclePoly.y3, vehiclePoly.y4);
 float float2 = Math.max(vehiclePoly.x1, Math.max(vehiclePoly.x2, Math.max(vehiclePoly.x3, vehiclePoly.x4);
 float float3 = Math.max(vehiclePoly.y1, Math.max(vehiclePoly.y2, Math.max(vehiclePoly.y3, vehiclePoly.y4);

 for (int int0 = (int)float1; int0 < (int)Math.ceil(float3); int0++) {
 for (int int1 = (int)float0; int1 < (int)Math.ceil(float2); int1++) {
 if (this->isIntersectingSquare(int1, int0, (int)this->z) {
 LineDrawer.addLine(int1, int0, (int)this->z, int1 + 1, int0 + 1, (int)this->z, 1.0F, 1.0F, 1.0F, nullptr, false);
 }
 }
 }
 }

 void renderTrailerPositions() {
 if (this->script != nullptr && this->physics != nullptr) {
 Vector3f vector3f0 = TL_vector3f_pool.get().alloc();
 Vector3f vector3f1 = TL_vector3f_pool.get().alloc();
 Vector3f vector3f2 = this->getTowingWorldPos("trailer", vector3f1);
 if (vector3f2 != nullptr) {
 this->physics.drawCircle(vector3f2.x, vector3f2.y, 0.3F, 1.0F, 1.0F, 1.0F, 1.0F);
 }

 Vector3f vector3f3 = this->getPlayerTrailerLocalPos("trailer", false, vector3f0);
 if (vector3f3 != nullptr) {
 this->getWorldPos(vector3f3, vector3f3);
 bool boolean0 = PolygonalMap2.instance.lineClearCollide(vector3f1.x, vector3f1.y, vector3f3.x, vector3f3.y, (int)this->z, this, false, false);
 this->physics.drawCircle(vector3f3.x, vector3f3.y, 0.3F, 1.0F, boolean0 ? 0.0F : 1.0F, boolean0 ? 0.0F : 1.0F, 1.0F);
 if (boolean0) {
 LineDrawer.addLine(vector3f3.x, vector3f3.y, 0.0F, vector3f1.x, vector3f1.y, 0.0F, 1.0F, 0.0F, 0.0F, 1.0F);
 }
 }

 vector3f3 = this->getPlayerTrailerLocalPos("trailer", true, vector3f0);
 if (vector3f3 != nullptr) {
 this->getWorldPos(vector3f3, vector3f3);
 bool boolean1 = PolygonalMap2.instance.lineClearCollide(vector3f1.x, vector3f1.y, vector3f3.x, vector3f3.y, (int)this->z, this, false, false);
 this->physics.drawCircle(vector3f3.x, vector3f3.y, 0.3F, 1.0F, boolean1 ? 0.0F : 1.0F, boolean1 ? 0.0F : 1.0F, 1.0F);
 if (boolean1) {
 LineDrawer.addLine(vector3f3.x, vector3f3.y, 0.0F, vector3f1.x, vector3f1.y, 0.0F, 1.0F, 0.0F, 0.0F, 1.0F);
 }
 }

 TL_vector3f_pool.get().release(vector3f0);
 TL_vector3f_pool.get().release(vector3f1);
 }
 }

 void getWheelForwardVector(int wheelIndex, Vector3f out) {
 BaseVehicle.WheelInfo wheelInfox = this->wheelInfo[wheelIndex];
 Matrix4f matrix4f0 = TL_matrix4f_pool.get().alloc();
 matrix4f0.rotationY(wheelInfox.steering);
 Matrix4f matrix4f1 = this->jniTransform.getMatrix(TL_matrix4f_pool.get().alloc());
 matrix4f1.setTranslation(0.0F, 0.0F, 0.0F);
 matrix4f0.mul(matrix4f1, matrix4f0);
 TL_matrix4f_pool.get().release(matrix4f1);
 TL_matrix4f_pool.get().release(matrix4f0);
 matrix4f0.getColumn(2, this->tempVector4f);
 out.set(this->tempVector4f.x, 0.0F, this->tempVector4f.z);
 }

 void tryStartEngine(bool haveKey) {
 if (this->getDriver() == nullptr || !(this->getDriver() instanceof IsoPlayer) || !((IsoPlayer)this->getDriver()).isBlockMovement()) {
 if (this->engineState == BaseVehicle.engineStateTypes.Idle) {
 if ((!Core.bDebug || !DebugOptions.instance.CheatVehicleStartWithoutKey.getValue())
 && !SandboxOptions.instance.VehicleEasyUse.getValue()
 && !this->isKeysInIgnition()
 && !haveKey
 && this->getDriver().getInventory().haveThisKeyId(this->getKeyId()) == nullptr
 && !this->isHotwired()) {
 if (GameServer.bServer) {
 this->getDriver().sendObjectChange("vehicleNoKey");
 } else {
 this->getDriver().SayDebug(" [img=media/ui/CarKey_none.png]");
 }
 } else {
 this->engineDoStarting();
 }
 }
 }
 }

 void tryStartEngine() {
 this->tryStartEngine(false);
 }

 void engineDoIdle() {
 this->engineState = BaseVehicle.engineStateTypes.Idle;
 this->engineLastUpdateStateTime = System.currentTimeMillis();
 this->transmitEngine();
 }

 void engineDoStarting() {
 this->engineState = BaseVehicle.engineStateTypes.Starting;
 this->engineLastUpdateStateTime = System.currentTimeMillis();
 this->transmitEngine();
 this->setKeysInIgnition(true);
 }

 bool isStarting() {
 return this->engineState == BaseVehicle.engineStateTypes.Starting
 || this->engineState == BaseVehicle.engineStateTypes.StartingFailed
 || this->engineState == BaseVehicle.engineStateTypes.StartingSuccess
 || this->engineState == BaseVehicle.engineStateTypes.StartingFailedNoPower;
 }

 std::string getEngineSound() {
 return this->getScript() != nullptr && this->getScript().getSounds().engine != nullptr ? this->getScript().getSounds().engine : "VehicleEngineDefault";
 }

 std::string getEngineStartSound() {
 return this->getScript() != nullptr && this->getScript().getSounds().engineStart != nullptr ? this->getScript().getSounds().engineStart : "VehicleStarted";
 }

 std::string getEngineTurnOffSound() {
 return this->getScript() != nullptr && this->getScript().getSounds().engineTurnOff != nullptr ? this->getScript().getSounds().engineTurnOff : "VehicleTurnedOff";
 }

 std::string getIgnitionFailSound() {
 return this->getScript() != nullptr && this->getScript().getSounds().ignitionFail != nullptr
 ? this->getScript().getSounds().ignitionFail
 : "VehicleFailingToStart";
 }

 std::string getIgnitionFailNoPowerSound() {
 return this->getScript() != nullptr && this->getScript().getSounds().ignitionFailNoPower != nullptr
 ? this->getScript().getSounds().ignitionFailNoPower
 : "VehicleFailingToStartNoPower";
 }

 void engineDoRetryingStarting() {
 this->getEmitter().stopSoundByName(this->getIgnitionFailSound());
 this->getEmitter().playSoundImpl(this->getIgnitionFailSound(), (IsoObject)nullptr);
 this->engineState = BaseVehicle.engineStateTypes.RetryingStarting;
 this->engineLastUpdateStateTime = System.currentTimeMillis();
 this->transmitEngine();
 }

 void engineDoStartingSuccess() {
 this->getEmitter().stopSoundByName(this->getIgnitionFailSound());
 this->engineState = BaseVehicle.engineStateTypes.StartingSuccess;
 this->engineLastUpdateStateTime = System.currentTimeMillis();
 if (this->getEngineStartSound() == this->getEngineSound())) {
 if (!this->getEmitter().isPlaying(this->combinedEngineSound) {
 this->combinedEngineSound = this->emitter.playSoundImpl(this->getEngineSound(), (IsoObject)nullptr);
 }
 } else {
 this->getEmitter().playSoundImpl(this->getEngineStartSound(), (IsoObject)nullptr);
 }

 this->transmitEngine();
 this->setKeysInIgnition(true);
 }

 void engineDoStartingFailed() {
 this->getEmitter().stopSoundByName(this->getIgnitionFailSound());
 this->getEmitter().playSoundImpl(this->getIgnitionFailSound(), (IsoObject)nullptr);
 this->stopEngineSounds();
 this->engineState = BaseVehicle.engineStateTypes.StartingFailed;
 this->engineLastUpdateStateTime = System.currentTimeMillis();
 this->transmitEngine();
 }

 void engineDoStartingFailedNoPower() {
 this->getEmitter().stopSoundByName(this->getIgnitionFailNoPowerSound());
 this->getEmitter().playSoundImpl(this->getIgnitionFailNoPowerSound(), (IsoObject)nullptr);
 this->stopEngineSounds();
 this->engineState = BaseVehicle.engineStateTypes.StartingFailedNoPower;
 this->engineLastUpdateStateTime = System.currentTimeMillis();
 this->transmitEngine();
 }

 void engineDoRunning() {
 this->setNeedPartsUpdate(true);
 this->engineState = BaseVehicle.engineStateTypes.Running;
 this->engineLastUpdateStateTime = System.currentTimeMillis();
 this->transmitEngine();
 }

 void engineDoStalling() {
 this->getEmitter().playSoundImpl("VehicleRunningOutOfGas", (IsoObject)nullptr);
 this->engineState = BaseVehicle.engineStateTypes.Stalling;
 this->engineLastUpdateStateTime = System.currentTimeMillis();
 this->stopEngineSounds();
 this->engineSoundIndex = 0;
 this->transmitEngine();
 if (!Core.getInstance().getOptionLeaveKeyInIgnition()) {
 this->setKeysInIgnition(false);
 }
 }

 void engineDoShuttingDown() {
 if (!this->getEngineTurnOffSound() == this->getEngineSound())) {
 this->getEmitter().playSoundImpl(this->getEngineTurnOffSound(), (IsoObject)nullptr);
 }

 this->stopEngineSounds();
 this->engineSoundIndex = 0;
 this->engineState = BaseVehicle.engineStateTypes.ShutingDown;
 this->engineLastUpdateStateTime = System.currentTimeMillis();
 this->transmitEngine();
 if (!Core.getInstance().getOptionLeaveKeyInIgnition()) {
 this->setKeysInIgnition(false);
 }

 VehiclePart part = this->getHeater();
 if (part != nullptr) {
 part.getModData().rawset("active", false);
 }
 }

 void shutOff() {
 if (this->getPartById("GasTank").getContainerContentAmount() == 0.0F) {
 this->engineDoStalling();
 } else {
 this->engineDoShuttingDown();
 }
 }

 void resumeRunningAfterLoad() {
 if (GameClient.bClient) {
 IsoGameCharacter character = this->getDriver();
 if (character != nullptr) {
 bool boolean0 = this->getDriver().getInventory().haveThisKeyId(this->getKeyId()) != nullptr ? Boolean.TRUE : Boolean.FALSE;
 GameClient.instance.sendClientCommandV((IsoPlayer)this->getDriver(), "vehicle", "startEngine", "haveKey", boolean0);
 }
 } else if (this->isEngineWorking()) {
 this->getEmitter();
 this->engineDoStartingSuccess();
 }
 }

 bool isEngineStarted() {
 return this->engineState == BaseVehicle.engineStateTypes.Starting
 || this->engineState == BaseVehicle.engineStateTypes.StartingFailed
 || this->engineState == BaseVehicle.engineStateTypes.StartingSuccess
 || this->engineState == BaseVehicle.engineStateTypes.RetryingStarting;
 }

 bool isEngineRunning() {
 return this->engineState == BaseVehicle.engineStateTypes.Running;
 }

 bool isEngineWorking() {
 for (int int0 = 0; int0 < this->parts.size(); int0++) {
 VehiclePart part = this->parts.get(int0);
 std::string string = part.getLuaFunction("checkEngine");
 if (string != nullptr && !Boolean.TRUE == this->callLuaBoolean(string, this, part) {
 return false;
 }
 }

 return true;
 }

 bool isOperational() {
 for (int int0 = 0; int0 < this->parts.size(); int0++) {
 VehiclePart part = this->parts.get(int0);
 std::string string = part.getLuaFunction("checkOperate");
 if (string != nullptr && !Boolean.TRUE == this->callLuaBoolean(string, this, part) {
 return false;
 }
 }

 return true;
 }

 bool isDriveable() {
 return !this->isEngineWorking() ? false : this->isOperational();
 }

 BaseSoundEmitter getEmitter() {
 if (this->emitter == nullptr) {
 if (!Core.SoundDisabled && !GameServer.bServer) {
 FMODSoundEmitter fMODSoundEmitter = new FMODSoundEmitter();
 fMODSoundEmitter.parameterUpdater = this;
 this->emitter = fMODSoundEmitter;
 } else {
 this->emitter = std::make_unique<DummySoundEmitter>();
 }
 }

 return this->emitter;
 }

 long playSoundImpl(const std::string& file, IsoObject parent) {
 return this->getEmitter().playSoundImpl(file, parent);
 }

 int stopSound(long channel) {
 return this->getEmitter().stopSound(channel);
 }

 void playSound(const std::string& sound) {
 this->getEmitter().playSound(sound);
 }

 void updateSounds() {
 if (!GameServer.bServer) {
 if (this->getBatteryCharge() > 0.0F) {
 if (this->lightbarSirenMode.isEnable() && this->soundSirenSignal == -1L) {
 this->setLightbarSirenMode(this->lightbarSirenMode.get());
 }
 } else if (this->soundSirenSignal != -1L) {
 this->getEmitter().stopSound(this->soundSirenSignal);
 this->soundSirenSignal = -1L;
 }
 }

 IsoPlayer player0 = nullptr;
 float float0 = Float.MAX_VALUE;

 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 IsoPlayer player1 = IsoPlayer.players[int0];
 if (player1 != nullptr && player1.getCurrentSquare() != nullptr) {
 float float1 = player1.getX();
 float float2 = player1.getY();
 float float3 = IsoUtils.DistanceToSquared(float1, float2, this->x, this->y);
 if (player1.Traits.HardOfHearing.isSet()) {
 float3 *= 4.5F;
 }

 if (player1.Traits.Deaf.isSet()) {
 float3 = Float.MAX_VALUE;
 }

 if (float3 < float0) {
 player0 = player1;
 float0 = float3;
 }
 }
 }

 if (player0 == nullptr) {
 if (this->emitter != nullptr) {
 this->emitter.setPos(this->x, this->y, this->z);
 if (!this->emitter.empty()) {
 this->emitter.tick();
 }
 }
 } else {
 if (!GameServer.bServer) {
 float float4 = ClimateManager.getInstance().isRaining() ? ClimateManager.getInstance().getPrecipitationIntensity() : 0.0F;
 if (this->getSquare() != nullptr && this->getSquare().isInARoom()) {
 float4 = 0.0F;
 }

 if (this->getEmitter().isPlaying("VehicleAmbiance")) {
 if (float4 == 0.0F) {
 this->getEmitter().stopOrTriggerSoundByName("VehicleAmbiance");
 }
 } else if (float4 > 0.0F && float0 < 100.0F) {
 this->emitter.playAmbientLoopedImpl("VehicleAmbiance");
 }

 float float5 = float0;
 if (float0 > 1200.0F) {
 this->stopEngineSounds();
 if (this->emitter != nullptr && !this->emitter.empty()) {
 this->emitter.setPos(this->x, this->y, this->z);
 this->emitter.tick();
 }

 return;
 }

 for (int int1 = 0; int1 < this->new_EngineSoundId.length; int1++) {
 if (this->new_EngineSoundId[int1] != 0L) {
 this->getEmitter().setVolume(this->new_EngineSoundId[int1], 1.0F - float5 / 1200.0F);
 }
 }
 }

 this->startTime = this->startTime - GameTime.instance.getMultiplier();
 if (this->getController() != nullptr) {
 if (!GameServer.bServer) {
 if (this->emitter == nullptr) {
 if (this->engineState != BaseVehicle.engineStateTypes.Running) {
 return;
 }

 this->getEmitter();
 }

 bool boolean0 = this->isAnyListenerInside();
 float float6 = Math.abs(this->getCurrentSpeedKmHour());
 if (this->startTime <= 0.0F
 && this->engineState == BaseVehicle.engineStateTypes.Running
 && !this->getEmitter().isPlaying(this->combinedEngineSound) {
 this->combinedEngineSound = this->emitter.playSoundImpl(this->getEngineSound(), (IsoObject)nullptr);
 if (this->getEngineSound() == this->getEngineStartSound())) {
 this->emitter.setTimelinePosition(this->combinedEngineSound, "idle");
 }
 }

 bool boolean1 = false;
 if (!GameClient.bClient || this->isLocalPhysicSim()) {
 for (int int2 = 0; int2 < this->script.getWheelCount(); int2++) {
 if (this->wheelInfo[int2].skidInfo < 0.15F) {
 boolean1 = true;
 break;
 }
 }
 }

 if (this->getDriver() == nullptr) {
 boolean1 = false;
 }

 if (boolean1 != this->skidding) {
 if (boolean1) {
 this->skidSound = this->getEmitter().playSoundImpl("VehicleSkid", (IsoObject)nullptr);
 } else if (this->skidSound != 0L) {
 this->emitter.stopSound(this->skidSound);
 this->skidSound = 0L;
 }

 this->skidding = boolean1;
 }

 if (this->soundBackMoveSignal != -1L && this->emitter != nullptr) {
 this->emitter.set3D(this->soundBackMoveSignal, !boolean0);
 }

 if (this->soundHorn != -1L && this->emitter != nullptr) {
 this->emitter.set3D(this->soundHorn, !boolean0);
 }

 if (this->soundSirenSignal != -1L && this->emitter != nullptr) {
 this->emitter.set3D(this->soundSirenSignal, !boolean0);
 }

 if (this->emitter != nullptr && (this->engineState != BaseVehicle.engineStateTypes.Idle || !this->emitter.empty())) {
 this->getFMODParameters().update();
 this->emitter.setPos(this->x, this->y, this->z);
 this->emitter.tick();
 }
 }
 }
 }
 }

 bool updatePart(VehiclePart part) {
 part.updateSignalDevice();
 VehicleLight vehicleLight = part.getLight();
 if (vehicleLight != nullptr && part.getId().contains("Headlight")) {
 part.setLightActive(this->getHeadlightsOn() && part.getInventoryItem() != nullptr && this->getBatteryCharge() > 0.0F);
 }

 std::string string = part.getLuaFunction("update");
 if (string == nullptr) {
 return false;
 } else {
 float float0 = (float)GameTime.getInstance().getWorldAgeHours();
 if (part.getLastUpdated() < 0.0F) {
 part.setLastUpdated(float0);
 } else if (part.getLastUpdated() > float0) {
 part.setLastUpdated(float0);
 }

 float float1 = float0 - part.getLastUpdated();
 if ((int)(float1 * 60.0F) > 0) {
 part.setLastUpdated(float0);
 this->callLuaVoid(string, this, part, (double)(float1 * 60.0F);
 return true;
 } else {
 return false;
 }
 }
 }

 void updateParts() {
 if (!GameClient.bClient) {
 bool boolean0 = false;

 for (int int0 = 0; int0 < this->getPartCount(); int0++) {
 VehiclePart part0 = this->getPartByIndex(int0);
 if (this->updatePart(part0) && !boolean0) {
 boolean0 = true;
 }

 if (int0 == this->getPartCount() - 1 && boolean0) {
 this->brakeBetweenUpdatesSpeed = 0.0F;
 }
 }
 } else {
 for (int int1 = 0; int1 < this->getPartCount(); int1++) {
 VehiclePart part1 = this->getPartByIndex(int1);
 part1.updateSignalDevice();
 }
 }
 }

 void drainBatteryUpdateHack() {
 bool boolean0 = this->isEngineRunning();
 if (!boolean0) {
 for (int int0 = 0; int0 < this->parts.size(); int0++) {
 VehiclePart part = this->parts.get(int0);
 if (part.getDeviceData() != nullptr && part.getDeviceData().getIsTurnedOn()) {
 this->updatePart(part);
 } else if (part.getLight() != nullptr && part.getLight().getActive()) {
 this->updatePart(part);
 }
 }

 if (this->hasLightbar() && (this->lightbarLightsMode.isEnable() || this->lightbarSirenMode.isEnable()) && this->getBattery() != nullptr) {
 this->updatePart(this->getBattery());
 }
 }
 }

 bool getHeadlightsOn() {
 return this->headlightsOn;
 }

 void setHeadlightsOn(bool on) {
 if (this->headlightsOn != on) {
 this->headlightsOn = on;
 if (GameServer.bServer) {
 this->updateFlags = (short)(this->updateFlags | 8);
 } else {
 this->playSound(this->headlightsOn ? "VehicleHeadlightsOn" : "VehicleHeadlightsOff");
 }
 }
 }

 bool getWindowLightsOn() {
 return this->windowLightsOn;
 }

 void setWindowLightsOn(bool on) {
 this->windowLightsOn = on;
 }

 bool getHeadlightCanEmmitLight() {
 if (this->getBatteryCharge() <= 0.0F) {
 return false;
 } else {
 VehiclePart part = this->getPartById("HeadlightLeft");
 if (part != nullptr && part.getInventoryItem() != nullptr) {
 return true;
 } else {
 part = this->getPartById("HeadlightRight");
 return part != nullptr && part.getInventoryItem() != nullptr;
 }
 }
 }

 bool getStoplightsOn() {
 return this->stoplightsOn;
 }

 void setStoplightsOn(bool on) {
 if (this->stoplightsOn != on) {
 this->stoplightsOn = on;
 if (GameServer.bServer) {
 this->updateFlags = (short)(this->updateFlags | 8);
 }
 }
 }

 bool hasHeadlights() {
 return this->getLightCount() > 0;
 }

 void addToWorld() {
 if (this->addedToWorld) {
 DebugLog.General.error("added vehicle twice " + this + " id=" + this->VehicleID);
 } else {
 VehiclesDB2.instance.setVehicleLoaded(this);
 this->addedToWorld = true;
 this->removedFromWorld = false;
 super.addToWorld();
 this->createPhysics();

 for (int int0 = 0; int0 < this->parts.size(); int0++) {
 VehiclePart part = this->parts.get(int0);
 if (part.getItemContainer() != nullptr) {
 part.getItemContainer().addItemsToProcessItems();
 }

 if (part.getDeviceData() != nullptr && !GameServer.bServer) {
 ZomboidRadio.getInstance().RegisterDevice(part);
 }
 }

 if (this->lightbarSirenMode.isEnable()) {
 this->setLightbarSirenMode(this->lightbarSirenMode.get());
 if (this->sirenStartTime <= 0.0) {
 this->sirenStartTime = GameTime.instance.getWorldAgeHours();
 }
 }

 if (this->chunk != nullptr && this->chunk.jobType != IsoChunk.JobType.SoftReset) {
 PolygonalMap2.instance.addVehicleToWorld(this);
 }

 if (this->engineState != BaseVehicle.engineStateTypes.Idle) {
 this->engineSpeed = this->getScript() == nullptr ? 1000.0 : this->getScript().getEngineIdleSpeed();
 }

 if (this->chunk != nullptr && this->chunk.jobType != IsoChunk.JobType.SoftReset) {
 this->trySpawnKey();
 }

 if (this->emitter != nullptr) {
 SoundManager.instance.registerEmitter(this->emitter);
 }
 }
 }

 void removeFromWorld() {
 this->breakConstraint(false, false);
 VehiclesDB2.instance.setVehicleUnloaded(this);

 for (int int0 = 0; int0 < this->passengers.length; int0++) {
 if (this->getPassenger(int0).character != nullptr) {
 for (int int1 = 0; int1 < 4; int1++) {
 if (this->getPassenger(int0).character == IsoPlayer.players[int1]) {
 return;
 }
 }
 }
 }

 IsoChunk.removeFromCheckedVehicles(this);
 DebugLog.Vehicle.trace("BaseVehicle.removeFromWorld() %s id=%d", this, this->VehicleID);
 if (!this->removedFromWorld) {
 if (!this->addedToWorld) {
 DebugLog.Vehicle.debugln("ERROR: removing vehicle but addedToWorld=false %s id=%d", this, this->VehicleID);
 }

 this->removedFromWorld = true;
 this->addedToWorld = false;

 for (int int2 = 0; int2 < this->parts.size(); int2++) {
 VehiclePart part = this->parts.get(int2);
 if (part.getItemContainer() != nullptr) {
 part.getItemContainer().removeItemsFromProcessItems();
 }

 if (part.getDeviceData() != nullptr && !GameServer.bServer) {
 ZomboidRadio.getInstance().UnRegisterDevice(part);
 }
 }

 if (this->emitter != nullptr) {
 this->emitter.stopAll();
 SoundManager.instance.unregisterEmitter(this->emitter);
 this->emitter = nullptr;
 }

 if (this->hornemitter != nullptr && this->soundHorn != -1L) {
 this->hornemitter.stopAll();
 this->soundHorn = -1L;
 }

 if (this->createdModel) {
 ModelManager.instance.Remove(this);
 this->createdModel = false;
 }

 this->releaseAnimationPlayers();
 if (this->getController() != nullptr) {
 if (!GameServer.bServer) {
 Bullet.removeVehicle(this->VehicleID);
 }

 this->physics = nullptr;
 }

 if (GameServer.bServer || GameClient.bClient) {
 VehicleManager.instance.removeFromWorld(this);
 } else if (this->VehicleID != -1) {
 VehicleIDMap.instance.remove(this->VehicleID);
 }

 IsoWorld.instance.CurrentCell.addVehicles.remove(this);
 IsoWorld.instance.CurrentCell.vehicles.remove(this);
 PolygonalMap2.instance.removeVehicleFromWorld(this);
 if (GameClient.bClient) {
 this->chunk.vehicles.remove(this);
 }

 this->m_surroundVehicle.reset();
 this->removeWorldLights();
 super.removeFromWorld();
 }
 }

 void permanentlyRemove() {
 for (int int0 = 0; int0 < this->getMaxPassengers(); int0++) {
 IsoGameCharacter character = this->getCharacter(int0);
 if (character != nullptr) {
 if (GameServer.bServer) {
 character.sendObjectChange("exitVehicle");
 }

 this->exit(character);
 }
 }

 this->breakConstraint(true, false);
 this->removeFromWorld();
 this->removeFromSquare();
 if (this->chunk != nullptr) {
 this->chunk.vehicles.remove(this);
 }

 VehiclesDB2.instance.removeVehicle(this);
 }

 VehiclePart getBattery() {
 return this->battery;
 }

 void setEngineFeature(int quality, int loudness, int engineForce) {
 this->engineQuality = PZMath.clamp(quality, 0, 100);
 this->engineLoudness = (int)(loudness / 2.7F);
 this->enginePower = engineForce;
 }

 int getEngineQuality() {
 return this->engineQuality;
 }

 int getEngineLoudness() {
 return this->engineLoudness;
 }

 int getEnginePower() {
 return this->enginePower;
 }

 float getBatteryCharge() {
 VehiclePart part = this->getBattery();
 return part != nullptr && part.getInventoryItem() instanceof DrainableComboItem ? ((DrainableComboItem)part.getInventoryItem()).getUsedDelta() : 0.0F;
 }

 int getPartCount() {
 return this->parts.size();
 }

 VehiclePart getPartByIndex(int index) {
 return index >= 0 && index < this->parts.size() ? this->parts.get(index) : nullptr;
 }

 VehiclePart getPartById(const std::string& id) {
 if (id == nullptr) {
 return nullptr;
 } else {
 for (int int0 = 0; int0 < this->parts.size(); int0++) {
 VehiclePart part0 = this->parts.get(int0);
 VehicleScript.Part part1 = part0.getScriptPart();
 if (part1 != nullptr && id == part1.id) {
 return part0;
 }
 }

 return nullptr;
 }
 }

 int getNumberOfPartsWithContainers() {
 if (this->getScript() == nullptr) {
 return 0;
 } else {
 int int0 = 0;

 for (int int1 = 0; int1 < this->getScript().getPartCount(); int1++) {
 if (this->getScript().getPart(int1).container != nullptr) {
 int0++;
 }
 }

 return int0;
 }
 }

 VehiclePart getPartForSeatContainer(int seat) {
 if (this->getScript() != nullptr && seat >= 0 && seat < this->getMaxPassengers()) {
 for (int int0 = 0; int0 < this->getPartCount(); int0++) {
 VehiclePart part = this->getPartByIndex(int0);
 if (part.getContainerSeatNumber() == seat) {
 return part;
 }
 }

 return nullptr;
 } else {
 return nullptr;
 }
 }

 void transmitPartCondition(VehiclePart part) {
 if (GameServer.bServer) {
 if (this->parts.contains(part) {
 part.updateFlags = (short)(part.updateFlags | 2048);
 this->updateFlags = (short)(this->updateFlags | 2048);
 }
 }
 }

 void transmitPartItem(VehiclePart part) {
 if (GameServer.bServer) {
 if (this->parts.contains(part) {
 part.updateFlags = (short)(part.updateFlags | 128);
 this->updateFlags = (short)(this->updateFlags | 128);
 }
 }
 }

 void transmitPartModData(VehiclePart part) {
 if (GameServer.bServer) {
 if (this->parts.contains(part) {
 part.updateFlags = (short)(part.updateFlags | 16);
 this->updateFlags = (short)(this->updateFlags | 16);
 }
 }
 }

 void transmitPartUsedDelta(VehiclePart part) {
 if (GameServer.bServer) {
 if (this->parts.contains(part) {
 if (part.getInventoryItem() instanceof DrainableComboItem) {
 part.updateFlags = (short)(part.updateFlags | 32);
 this->updateFlags = (short)(this->updateFlags | 32);
 }
 }
 }
 }

 void transmitPartDoor(VehiclePart part) {
 if (GameServer.bServer) {
 if (this->parts.contains(part) {
 if (part.getDoor() != nullptr) {
 part.updateFlags = (short)(part.updateFlags | 512);
 this->updateFlags = (short)(this->updateFlags | 512);
 }
 }
 }
 }

 void transmitPartWindow(VehiclePart part) {
 if (GameServer.bServer) {
 if (this->parts.contains(part) {
 if (part.getWindow() != nullptr) {
 part.updateFlags = (short)(part.updateFlags | 256);
 this->updateFlags = (short)(this->updateFlags | 256);
 }
 }
 }
 }

 int getLightCount() {
 return this->lights.size();
 }

 VehiclePart getLightByIndex(int index) {
 return index >= 0 && index < this->lights.size() ? this->lights.get(index) : nullptr;
 }

 std::string getZone() {
 return this->respawnZone;
 }

 void setZone(const std::string& name) {
 this->respawnZone = name;
 }

 bool isInArea(const std::string& areaId, IsoGameCharacter chr) {
 if (areaId != nullptr && this->getScript() != nullptr) {
 VehicleScript.Area area = this->getScript().getAreaById(areaId);
 if (area == nullptr) {
 return false;
 } else {
 Vector2 vector0 = TL_vector2_pool.get().alloc();
 Vector2 vector1 = this->areaPositionLocal(area, vector0);
 if (vector1 == nullptr) {
 TL_vector2_pool.get().release(vector0);
 return false;
 } else {
 Vector3f vector3f = TL_vector3f_pool.get().alloc();
 this->getLocalPos(chr.x, chr.y, this->z, vector3f);
 float float0 = vector1.x - area.w / 2.0F;
 float float1 = vector1.y - area.h / 2.0F;
 float float2 = vector1.x + area.w / 2.0F;
 float float3 = vector1.y + area.h / 2.0F;
 TL_vector2_pool.get().release(vector0);
 bool boolean0 = vector3f.x >= float0 && vector3f.x < float2 && vector3f.z >= float1 && vector3f.z < float3;
 TL_vector3f_pool.get().release(vector3f);
 return boolean0;
 }
 }
 } else {
 return false;
 }
 }

 float getAreaDist(const std::string& areaId, IsoGameCharacter chr) {
 if (areaId != nullptr && this->getScript() != nullptr) {
 VehicleScript.Area area = this->getScript().getAreaById(areaId);
 if (area != nullptr) {
 Vector3f vector3f = this->getLocalPos(chr.x, chr.y, this->z, TL_vector3f_pool.get().alloc());
 float float0 = Math.abs(area.x - area.w / 2.0F);
 float float1 = Math.abs(area.y - area.h / 2.0F);
 float float2 = Math.abs(area.x + area.w / 2.0F);
 float float3 = Math.abs(area.y + area.h / 2.0F);
 float float4 = Math.abs(vector3f.x + float0) + Math.abs(vector3f.z + float1);
 TL_vector3f_pool.get().release(vector3f);
 return float4;
 } else {
 return 999.0F;
 }
 } else {
 return 999.0F;
 }
 }

 Vector2 getAreaCenter(const std::string& areaId) {
 return this->getAreaCenter(areaId, std::make_unique<Vector2>());
 }

 Vector2 getAreaCenter(const std::string& areaId, Vector2 out) {
 if (areaId != nullptr && this->getScript() != nullptr) {
 VehicleScript.Area area = this->getScript().getAreaById(areaId);
 return area = = nullptr ? nullptr : this->areaPositionWorld(area, out);
 } else {
 return nullptr;
 }
 }

 bool isInBounds(float worldX, float worldY) {
 return this->getPoly().containsPoint(worldX, worldY);
 }

 bool canAccessContainer(int partIndex, IsoGameCharacter chr) {
 VehiclePart part0 = this->getPartByIndex(partIndex);
 if (part0 == nullptr) {
 return false;
 } else {
 VehicleScript.Part part1 = part0.getScriptPart();
 if (part1 == nullptr) {
 return false;
 } else if (part1.container == nullptr) {
 return false;
 } else if (part0.isInventoryItemUninstalled() && part1.container.capacity == 0) {
 return false;
 } else {
 return part1.container.luaTest != nullptr && !part1.container.luaTest.empty()
 ? Boolean.TRUE == this->callLuaBoolean(part1.container.luaTest, this, part0, chr)
 : true;
 }
 }
 }

 bool canInstallPart(IsoGameCharacter chr, VehiclePart part) {
 if (!this->parts.contains(part) {
 return false;
 } else {
 KahluaTable table = part.getTable("install");
 return table != nullptr && table.rawget("test") instanceof String
 ? Boolean.TRUE == this->callLuaBoolean((String)table.rawget("test"), this, part, chr)
 : false;
 }
 }

 bool canUninstallPart(IsoGameCharacter chr, VehiclePart part) {
 if (!this->parts.contains(part) {
 return false;
 } else {
 KahluaTable table = part.getTable("uninstall");
 return table != nullptr && table.rawget("test") instanceof String
 ? Boolean.TRUE == this->callLuaBoolean((String)table.rawget("test"), this, part, chr)
 : false;
 }
 }

 void callLuaVoid(const std::string& string, void* object1, void* object2) {
 void* object0 = LuaManager.getFunctionObject(string);
 if (object0 != nullptr) {
 LuaManager.caller.protectedCallVoid(LuaManager.thread, object0, object1, object2);
 }
 }

 void callLuaVoid(const std::string& string, void* object1, void* object2, void* object3) {
 void* object0 = LuaManager.getFunctionObject(string);
 if (object0 != nullptr) {
 LuaManager.caller.protectedCallVoid(LuaManager.thread, object0, object1, object2, object3);
 }
 }

 bool callLuaBoolean(const std::string& string, void* object1, void* object2) {
 void* object0 = LuaManager.getFunctionObject(string);
 return object0 = = nullptr ? nullptr : LuaManager.caller.protectedCallBoolean(LuaManager.thread, object0, object1, object2);
 }

 bool callLuaBoolean(const std::string& string, void* object1, void* object2, void* object3) {
 void* object0 = LuaManager.getFunctionObject(string);
 return object0 = = nullptr ? nullptr : LuaManager.caller.protectedCallBoolean(LuaManager.thread, object0, object1, object2, object3);
 }

 short getId() {
 return this->VehicleID;
 }

 void setTireInflation(int wheelIndex, float inflation) {
 }

 void setTireRemoved(int wheelIndex, bool removed) {
 if (!GameServer.bServer) {
 Bullet.setTireRemoved(this->VehicleID, wheelIndex, removed);
 }
 }

 Vector3f chooseBestAttackPosition(IsoGameCharacter target, IsoGameCharacter attacker, Vector3f worldPos) {
 Vector2f vector2f0 = TL_vector2f_pool.get().alloc();
 Vector2f vector2f1 = target.getVehicle().getSurroundVehicle().getPositionForZombie((IsoZombie)attacker, vector2f0);
 float float0 = vector2f0.x;
 float float1 = vector2f0.y;
 TL_vector2f_pool.get().release(vector2f0);
 return vector2f1 != nullptr ? worldPos.set(float0, float1, this->z) : nullptr;
 }

 public BaseVehicle.MinMaxPosition getMinMaxPosition() {
 BaseVehicle.MinMaxPosition minMaxPosition = new BaseVehicle.MinMaxPosition();
 float float0 = this->getX();
 float float1 = this->getY();
 Vector3f vector3f = this->getScript().getExtents();
 float float2 = vector3f.x;
 float float3 = vector3f.z;
 IsoDirections directions = this->getDir();
 switch (directions) {
 case E:
 case W:
 minMaxPosition.minX = float0 - float2 / 2.0F;
 minMaxPosition.maxX = float0 + float2 / 2.0F;
 minMaxPosition.minY = float1 - float3 / 2.0F;
 minMaxPosition.maxY = float1 + float3 / 2.0F;
 break;
 case N:
 case S:
 minMaxPosition.minX = float0 - float3 / 2.0F;
 minMaxPosition.maxX = float0 + float3 / 2.0F;
 minMaxPosition.minY = float1 - float2 / 2.0F;
 minMaxPosition.maxY = float1 + float2 / 2.0F;
 break;
 default:
 return nullptr;
 }

 return minMaxPosition;
 }

 std::string getVehicleType() {
 return this->type;
 }

 void setVehicleType(const std::string& _type) {
 this->type = _type;
 }

 float getMaxSpeed() {
 return this->maxSpeed;
 }

 void setMaxSpeed(float _maxSpeed) {
 this->maxSpeed = _maxSpeed;
 }

 void lockServerUpdate(long lockTimeMs) {
 this->updateLockTimeout = System.currentTimeMillis() + lockTimeMs;
 }

 /**
 * Change transmission, slow down the car if you change shift for a superior one
 */
 void changeTransmission(TransmissionNumber newTransmission) {
 this->transmissionNumber = newTransmission;
 }

 /**
 * Try to hotwire a car Calcul is: 100-Engine quality (capped to 5) + Skill modifier: electricityLvl * 4 % of hotwiring the car Failing may cause the ignition to break
 */
 void tryHotwire(int electricityLevel) {
 int int0 = Math.max(100 - this->getEngineQuality(), 5);
 int0 = Math.min(int0, 50);
 int int1 = electricityLevel * 4;
 int int2 = int0 + int1;
 bool boolean0 = false;
 void* object = nullptr;
 if (Rand.Next(100) <= 11 - electricityLevel && this->alarmed) {
 this->triggerAlarm();
 }

 if (Rand.Next(100) <= int2) {
 this->setHotwired(true);
 boolean0 = true;
 object = "VehicleHotwireSuccess";
 } else if (Rand.Next(100) <= 10 - electricityLevel) {
 this->setHotwiredBroken(true);
 boolean0 = true;
 object = "VehicleHotwireFail";
 } else {
 object = "VehicleHotwireFail";
 }

 if (object != nullptr) {
 if (GameServer.bServer) {
 LuaManager.GlobalObject.playServerSound((String)object, this->square);
 } else if (this->getDriver() != nullptr) {
 this->getDriver().getEmitter().playSound((String)object);
 }
 }

 if (boolean0 && GameServer.bServer) {
 this->updateFlags = (short)(this->updateFlags | 4096);
 }
 }

 void cheatHotwire(bool _hotwired, bool broken) {
 if (_hotwired != this->hotwired || broken != this->hotwiredBroken) {
 this->hotwired = _hotwired;
 this->hotwiredBroken = broken;
 if (GameServer.bServer) {
 this->updateFlags = (short)(this->updateFlags | 4096);
 }
 }
 }

 bool isKeyIsOnDoor() {
 return this->keyIsOnDoor;
 }

 void setKeyIsOnDoor(bool _keyIsOnDoor) {
 this->keyIsOnDoor = _keyIsOnDoor;
 }

 bool isHotwired() {
 return this->hotwired;
 }

 void setHotwired(bool _hotwired) {
 this->hotwired = _hotwired;
 }

 bool isHotwiredBroken() {
 return this->hotwiredBroken;
 }

 void setHotwiredBroken(bool _hotwiredBroken) {
 this->hotwiredBroken = _hotwiredBroken;
 }

 IsoGameCharacter getDriver() {
 BaseVehicle.Passenger passenger = this->getPassenger(0);
 return passenger = = nullptr ? nullptr : passenger.character;
 }

 bool isKeysInIgnition() {
 return this->keysInIgnition;
 }

 void setKeysInIgnition(bool keysOnContact) {
 IsoGameCharacter character = this->getDriver();
 if (character != nullptr) {
 this->setAlarmed(false);
 if (!GameClient.bClient || character instanceof IsoPlayer && ((IsoPlayer)character).isLocalPlayer()) {
 if (!this->isHotwired()) {
 if (!GameServer.bServer && keysOnContact && !this->keysInIgnition) {
 InventoryItem item0 = this->getDriver().getInventory().haveThisKeyId(this->getKeyId());
 if (item0 != nullptr) {
 this->setCurrentKey(item0);
 InventoryItem item1 = item0.getContainer().getContainingItem();
 if (item1 instanceof InventoryContainer && "KeyRing" == item1.getType())) {
 item0.getModData().rawset("keyRing", (double)item1.getID());
 } else if (item0.hasModData()) {
 item0.getModData().rawset("keyRing", nullptr);
 }

 item0.getContainer().DoRemoveItem(item0);
 this->keysInIgnition = keysOnContact;
 if (GameClient.bClient) {
 GameClient.instance.sendClientCommandV((IsoPlayer)this->getDriver(), "vehicle", "putKeyInIgnition", "key", item0);
 }
 }
 }

 if (!keysOnContact && this->keysInIgnition && !GameServer.bServer) {
 if (this->currentKey == nullptr) {
 this->currentKey = this->createVehicleKey();
 }

 InventoryItem item2 = this->getCurrentKey();
 ItemContainer container = this->getDriver().getInventory();
 if (item2.hasModData() && item2.getModData().rawget("keyRing") instanceof Double) {
 double double0 = (Double)item2.getModData().rawget("keyRing");
 InventoryItem item3 = container.getItemWithID(double0.intValue());
 if (item3 instanceof InventoryContainer && "KeyRing" == item3.getType())) {
 container = ((InventoryContainer)item3).getInventory();
 }

 item2.getModData().rawset("keyRing", nullptr);
 }

 container.addItem(item2);
 this->setCurrentKey(nullptr);
 this->keysInIgnition = keysOnContact;
 if (GameClient.bClient) {
 GameClient.instance.sendClientCommand((IsoPlayer)this->getDriver(), "vehicle", "removeKeyFromIgnition", (KahluaTable)nullptr);
 }
 }
 }
 }
 }
 }

 void putKeyInIgnition(InventoryItem key) {
 if (GameServer.bServer) {
 if (key instanceof Key) {
 if (!this->keysInIgnition) {
 this->keysInIgnition = true;
 this->keyIsOnDoor = false;
 this->currentKey = key;
 this->updateFlags = (short)(this->updateFlags | 4096);
 }
 }
 }
 }

 void removeKeyFromIgnition() {
 if (GameServer.bServer) {
 if (this->keysInIgnition) {
 this->keysInIgnition = false;
 this->currentKey = nullptr;
 this->updateFlags = (short)(this->updateFlags | 4096);
 }
 }
 }

 void putKeyOnDoor(InventoryItem key) {
 if (GameServer.bServer) {
 if (key instanceof Key) {
 if (!this->keyIsOnDoor) {
 this->keyIsOnDoor = true;
 this->keysInIgnition = false;
 this->currentKey = key;
 this->updateFlags = (short)(this->updateFlags | 4096);
 }
 }
 }
 }

 void removeKeyFromDoor() {
 if (GameServer.bServer) {
 if (this->keyIsOnDoor) {
 this->keyIsOnDoor = false;
 this->currentKey = nullptr;
 this->updateFlags = (short)(this->updateFlags | 4096);
 }
 }
 }

 void syncKeyInIgnition(bool inIgnition, bool onDoor, InventoryItem key) {
 if (GameClient.bClient) {
 if (!(this->getDriver() instanceof IsoPlayer) || !((IsoPlayer)this->getDriver()).isLocalPlayer()) {
 this->keysInIgnition = inIgnition;
 this->keyIsOnDoor = onDoor;
 this->currentKey = key;
 }
 }
 }

 void randomizeContainers() {
 if (!GameClient.bClient) {
 bool boolean0 = true;
 std::string string = this->getScriptName().substring(this->getScriptName().indexOf(46) + 1);
 ItemPickerJava.VehicleDistribution vehicleDistribution = ItemPickerJava.VehicleDistributions.get(string + this->getSkinIndex());
 if (vehicleDistribution != nullptr) {
 boolean0 = false;
 } else {
 vehicleDistribution = ItemPickerJava.VehicleDistributions.get(string);
 }

 if (vehicleDistribution == nullptr) {
 for (int int0 = 0; int0 < this->parts.size(); int0++) {
 VehiclePart part0 = this->parts.get(int0);
 if (part0.getItemContainer() != nullptr) {
 if (Core.bDebug) {
 DebugLog.log("VEHICLE MISSING CONT DISTRIBUTION: " + string);
 }

 return;
 }
 }
 } else {
 ItemPickerJava.ItemPickerRoom itemPickerRoom0;
 if (boolean0 && Rand.Next(100) <= 8 && !vehicleDistribution.Specific.empty()) {
 itemPickerRoom0 = PZArrayUtil.pickRandom(vehicleDistribution.Specific);
 } else {
 itemPickerRoom0 = vehicleDistribution.Normal;
 }

 if (!StringUtils.isNullOrWhitespace(this->specificDistributionId) {
 for (int int1 = 0; int1 < vehicleDistribution.Specific.size(); int1++) {
 ItemPickerJava.ItemPickerRoom itemPickerRoom1 = vehicleDistribution.Specific.get(int1);
 if (this->specificDistributionId == itemPickerRoom1.specificId) {
 itemPickerRoom0 = itemPickerRoom1;
 break;
 }
 }
 }

 for (int int2 = 0; int2 < this->parts.size(); int2++) {
 VehiclePart part1 = this->parts.get(int2);
 if (part1.getItemContainer() != nullptr) {
 if (GameServer.bServer && GameServer.bSoftReset) {
 part1.getItemContainer().setExplored(false);
 }

 if (!part1.getItemContainer().bExplored) {
 part1.getItemContainer().clear();
 if (Rand.Next(100) <= 100) {
 this->randomizeContainer(part1, itemPickerRoom0);
 LuaEventManager.triggerEvent("OnFillContainer", string, part1.getItemContainer().getType(), part1.getItemContainer());
 }

 part1.getItemContainer().setExplored(true);
 }
 }
 }
 }
 }
 }

 void randomizeContainer(VehiclePart part, ItemPickerJava.ItemPickerRoom itemPickerRoom) {
 if (!GameClient.bClient) {
 if (itemPickerRoom != nullptr) {
 if (!part.getId().contains("Seat") && !itemPickerRoom.Containers.containsKey(part.getId())) {
 DebugLog.log("NO CONT DISTRIB FOR PART: " + part.getId() + " CAR: " + this->getScriptName().replaceFirst("Base.", ""));
 }

 ItemPickerJava.fillContainerType(itemPickerRoom, part.getItemContainer(), "", nullptr);
 if (GameServer.bServer && !part.getItemContainer().getItems().empty()) {
 }
 }
 }
 }

 bool hasHorn() {
 return this->script.getSounds().hornEnable;
 }

 bool hasLightbar() {
 VehiclePart part = this->getPartById("lightbar");
 return this->script.getLightbar().enable;
 }

 void onHornStart() {
 this->soundHornOn = true;
 if (GameServer.bServer) {
 this->updateFlags = (short)(this->updateFlags | 1024);
 if (this->script.getSounds().hornEnable) {
 WorldSoundManager.instance.addSound(this, (int)this->getX(), (int)this->getY(), (int)this->getZ(), 150, 150, false);
 }
 } else {
 if (this->soundHorn != -1L) {
 this->hornemitter.stopSound(this->soundHorn);
 }

 if (this->script.getSounds().hornEnable) {
 this->hornemitter = IsoWorld.instance.getFreeEmitter(this->getX(), this->getY(), (int)this->getZ());
 this->soundHorn = this->hornemitter.playSoundLoopedImpl(this->script.getSounds().horn);
 this->hornemitter.set3D(this->soundHorn, !this->isAnyListenerInside());
 this->hornemitter.setVolume(this->soundHorn, 1.0F);
 this->hornemitter.setPitch(this->soundHorn, 1.0F);
 if (!GameClient.bClient) {
 WorldSoundManager.instance.addSound(this, (int)this->getX(), (int)this->getY(), (int)this->getZ(), 150, 150, false);
 }
 }
 }
 }

 void onHornStop() {
 this->soundHornOn = false;
 if (GameServer.bServer) {
 this->updateFlags = (short)(this->updateFlags | 1024);
 } else {
 if (this->script.getSounds().hornEnable && this->soundHorn != -1L) {
 this->hornemitter.stopSound(this->soundHorn);
 this->soundHorn = -1L;
 }
 }
 }

 bool hasBackSignal() {
 return this->script != nullptr && this->script.getSounds().backSignalEnable;
 }

 bool isBackSignalEmitting() {
 return this->soundBackMoveSignal != -1L;
 }

 void onBackMoveSignalStart() {
 this->soundBackMoveOn = true;
 if (GameServer.bServer) {
 this->updateFlags = (short)(this->updateFlags | 1024);
 } else {
 if (this->soundBackMoveSignal != -1L) {
 this->emitter.stopSound(this->soundBackMoveSignal);
 }

 if (this->script.getSounds().backSignalEnable) {
 this->soundBackMoveSignal = this->emitter.playSoundLoopedImpl(this->script.getSounds().backSignal);
 this->emitter.set3D(this->soundBackMoveSignal, !this->isAnyListenerInside());
 }
 }
 }

 void onBackMoveSignalStop() {
 this->soundBackMoveOn = false;
 if (GameServer.bServer) {
 this->updateFlags = (short)(this->updateFlags | 1024);
 } else {
 if (this->script.getSounds().backSignalEnable && this->soundBackMoveSignal != -1L) {
 this->emitter.stopSound(this->soundBackMoveSignal);
 this->soundBackMoveSignal = -1L;
 }
 }
 }

 int getLightbarLightsMode() {
 return this->lightbarLightsMode.get();
 }

 void setLightbarLightsMode(int mode) {
 this->lightbarLightsMode.set(mode);
 if (GameServer.bServer) {
 this->updateFlags = (short)(this->updateFlags | 1024);
 }
 }

 int getLightbarSirenMode() {
 return this->lightbarSirenMode.get();
 }

 void setLightbarSirenMode(int mode) {
 if (this->soundSirenSignal != -1L) {
 this->getEmitter().stopSound(this->soundSirenSignal);
 this->soundSirenSignal = -1L;
 }

 this->lightbarSirenMode.set(mode);
 if (GameServer.bServer) {
 this->updateFlags = (short)(this->updateFlags | 1024);
 } else {
 if (this->lightbarSirenMode.isEnable() && this->getBatteryCharge() > 0.0F) {
 this->soundSirenSignal = this->getEmitter().playSoundLoopedImpl(this->lightbarSirenMode.getSoundName(this->script.getLightbar()));
 this->getEmitter().set3D(this->soundSirenSignal, !this->isAnyListenerInside());
 }
 }
 }

 public HashMap<String, String> getChoosenParts() {
 return this->choosenParts;
 }

 float getMass() {
 float float0 = this->mass;
 if (float0 < 0.0F) {
 float0 = 1.0F;
 }

 return float0;
 }

 void setMass(float _mass) {
 this->mass = _mass;
 }

 float getInitialMass() {
 return this->initialMass;
 }

 void setInitialMass(float _initialMass) {
 this->initialMass = _initialMass;
 }

 void updateTotalMass() {
 float float0 = 0.0F;

 for (int int0 = 0; int0 < this->parts.size(); int0++) {
 VehiclePart part = this->parts.get(int0);
 if (part.getItemContainer() != nullptr) {
 float0 += part.getItemContainer().getCapacityWeight();
 }

 if (part.getInventoryItem() != nullptr) {
 float0 += part.getInventoryItem().getWeight();
 }
 }

 this->setMass(Math.round(this->getInitialMass() + float0);
 if (this->physics != nullptr && !GameServer.bServer) {
 Bullet.setVehicleMass(this->VehicleID, this->getMass());
 }
 }

 float getBrakingForce() {
 return this->brakingForce;
 }

 void setBrakingForce(float _brakingForce) {
 this->brakingForce = _brakingForce;
 }

 float getBaseQuality() {
 return this->baseQuality;
 }

 void setBaseQuality(float _baseQuality) {
 this->baseQuality = _baseQuality;
 }

 float getCurrentSteering() {
 return this->currentSteering;
 }

 void setCurrentSteering(float _currentSteering) {
 this->currentSteering = _currentSteering;
 }

 bool isDoingOffroad() {
 if (this->getCurrentSquare() == nullptr) {
 return false;
 } else {
 IsoObject object = this->getCurrentSquare().getFloor();
 if (object != nullptr && object.getSprite() != nullptr) {
 std::string string = object.getSprite().getName();
 return string == nullptr
 ? false
 : !string.contains("carpentry_02") && !string.contains("blends_street") && !string.contains("floors_exterior_street");
 } else {
 return false;
 }
 }
 }

 bool isBraking() {
 return this->isBraking;
 }

 void setBraking(bool _isBraking) {
 this->isBraking = _isBraking;
 if (_isBraking && this->brakeBetweenUpdatesSpeed == 0.0F) {
 this->brakeBetweenUpdatesSpeed = Math.abs(this->getCurrentSpeedKmHour());
 }
 }

 /**
 * Update the stats of the part depending on condition
 */
 void updatePartStats() {
 this->setBrakingForce(0.0F);
 this->engineLoudness = (int)(this->getScript().getEngineLoudness() * SandboxOptions.instance.ZombieAttractionMultiplier.getValue() / 2.0);
 bool boolean0 = false;

 for (int int0 = 0; int0 < this->getPartCount(); int0++) {
 VehiclePart part = this->getPartByIndex(int0);
 if (part.getInventoryItem() != nullptr) {
 if (part.getInventoryItem().getBrakeForce() > 0.0F) {
 float float0 = VehiclePart.getNumberByCondition(part.getInventoryItem().getBrakeForce(), part.getInventoryItem().getCondition(), 5.0F);
 float0 += float0 / 50.0F * part.getMechanicSkillInstaller();
 this->setBrakingForce(this->getBrakingForce() + float0);
 }

 if (part.getInventoryItem().getWheelFriction() > 0.0F) {
 part.setWheelFriction(0.0F);
 float float1 = VehiclePart.getNumberByCondition(part.getInventoryItem().getWheelFriction(), part.getInventoryItem().getCondition(), 0.2F);
 float1 += 0.1F * part.getMechanicSkillInstaller();
 float1 = Math.min(2.3F, float1);
 part.setWheelFriction(float1);
 }

 if (part.getInventoryItem().getSuspensionCompression() > 0.0F) {
 part.setSuspensionCompression(
 VehiclePart.getNumberByCondition(part.getInventoryItem().getSuspensionCompression(), part.getInventoryItem().getCondition(), 0.6F)
 );
 part.setSuspensionDamping(
 VehiclePart.getNumberByCondition(part.getInventoryItem().getSuspensionDamping(), part.getInventoryItem().getCondition(), 0.6F)
 );
 }

 if (part.getInventoryItem().getEngineLoudness() > 0.0F) {
 part.setEngineLoudness(
 VehiclePart.getNumberByCondition(part.getInventoryItem().getEngineLoudness(), part.getInventoryItem().getCondition(), 10.0F)
 );
 this->engineLoudness = (int)(this->engineLoudness * (1.0F + (100.0F - part.getEngineLoudness()) / 100.0F);
 boolean0 = true;
 }
 }
 }

 if (!boolean0) {
 this->engineLoudness *= 2;
 }
 }

 void transmitEngine() {
 if (GameServer.bServer) {
 this->updateFlags = (short)(this->updateFlags | 4);
 }
 }

 void setRust(float _rust) {
 this->rust = PZMath.clamp(_rust, 0.0F, 1.0F);
 }

 float getRust() {
 return this->rust;
 }

 void transmitRust() {
 if (GameServer.bServer) {
 this->updateFlags = (short)(this->updateFlags | 4096);
 }
 }

 void transmitColorHSV() {
 if (GameServer.bServer) {
 this->updateFlags = (short)(this->updateFlags | 4096);
 }
 }

 void transmitSkinIndex() {
 if (GameServer.bServer) {
 this->updateFlags = (short)(this->updateFlags | 4096);
 }
 }

 void updateBulletStats() {
 if (!this->getScriptName().contains("Burnt") && WorldSimulation.instance.created) {
 float[] floats = wheelParams;
 double double0 = 2.4;
 uint8_t byte0 = 5;
 double double1;
 float float0;
 if (this->isInForest() && this->isDoingOffroad() && Math.abs(this->getCurrentSpeedKmHour()) > 1.0F) {
 double1 = Rand.Next(0.08F, 0.18F);
 float0 = 0.7F;
 byte0 = 3;
 } else if (this->isDoingOffroad() && Math.abs(this->getCurrentSpeedKmHour()) > 1.0F) {
 double1 = Rand.Next(0.05F, 0.15F);
 float0 = 0.7F;
 } else {
 if (Math.abs(this->getCurrentSpeedKmHour()) > 1.0F && Rand.Next(100) < 10) {
 double1 = Rand.Next(0.05F, 0.15F);
 } else {
 double1 = 0.0;
 }

 float0 = 1.0F;
 }

 if (RainManager.isRaining()) {
 float0 -= 0.3F;
 }

 Vector3f vector3f = TL_vector3f_pool.get().alloc();

 for (int int0 = 0; int0 < this->script.getWheelCount(); int0++) {
 this->updateBulletStatsWheel(int0, floats, vector3f, float0, byte0, double0, double1);
 }

 TL_vector3f_pool.get().release(vector3f);
 if (SystemDisabler.getdoVehicleLowRider() && this->isKeyboardControlled()) {
 float float1 = 1.6F;
 float float2 = 1.0F;
 if (GameKeyboard.isKeyDown(79) {
 lowRiderParam[0] = lowRiderParam[0] + (float1 - lowRiderParam[0]) * float2;
 } else {
 lowRiderParam[0] = lowRiderParam[0] + (0.0F - lowRiderParam[0]) * 0.05F;
 }

 if (GameKeyboard.isKeyDown(80) {
 lowRiderParam[1] = lowRiderParam[1] + (float1 - lowRiderParam[1]) * float2;
 } else {
 lowRiderParam[1] = lowRiderParam[1] + (0.0F - lowRiderParam[1]) * 0.05F;
 }

 if (GameKeyboard.isKeyDown(75) {
 lowRiderParam[2] = lowRiderParam[2] + (float1 - lowRiderParam[2]) * float2;
 } else {
 lowRiderParam[2] = lowRiderParam[2] + (0.0F - lowRiderParam[2]) * 0.05F;
 }

 if (GameKeyboard.isKeyDown(76) {
 lowRiderParam[3] = lowRiderParam[3] + (float1 - lowRiderParam[3]) * float2;
 } else {
 lowRiderParam[3] = lowRiderParam[3] + (0.0F - lowRiderParam[3]) * 0.05F;
 }

 floats[23] = lowRiderParam[0];
 floats[22] = lowRiderParam[1];
 floats[21] = lowRiderParam[2];
 floats[20] = lowRiderParam[3];
 }

 Bullet.setVehicleParams(this->VehicleID, floats);
 }
 }

 void updateBulletStatsWheel(int int1, float[] floats, Vector3f vector3f1, float float0, int int2, double double1, double double0) {
 int int0 = int1 * 6;
 VehicleScript.Wheel wheel = this->script.getWheel(int1);
 Vector3f vector3f0 = this->getWorldPos(wheel.offset.x, wheel.offset.y, wheel.offset.z, vector3f1);
 VehiclePart part0 = this->getPartById("Tire" + wheel.getId());
 VehiclePart part1 = this->getPartById("Suspension" + wheel.getId());
 if (part0 != nullptr && part0.getInventoryItem() != nullptr) {
 floats[int0 + 0] = 1.0F;
 floats[int0 + 1] = Math.min(part0.getContainerContentAmount() / (part0.getContainerCapacity() - 10), 1.0F);
 floats[int0 + 2] = float0 * part0.getWheelFriction();
 if (part1 != nullptr && part1.getInventoryItem() != nullptr) {
 floats[int0 + 3] = part1.getSuspensionDamping();
 floats[int0 + 4] = part1.getSuspensionCompression();
 } else {
 floats[int0 + 3] = 0.1F;
 floats[int0 + 4] = 0.1F;
 }

 if (Rand.Next(int2) == 0) {
 floats[int0 + 5] = (float)(Math.sin(double1 * vector3f0.x()) * Math.sin(double1 * vector3f0.y()) * double0);
 } else {
 floats[int0 + 5] = 0.0F;
 }
 } else {
 floats[int0 + 0] = 0.0F;
 floats[int0 + 1] = 30.0F;
 floats[int0 + 2] = 0.0F;
 floats[int0 + 3] = 2.88F;
 floats[int0 + 4] = 3.83F;
 if (Rand.Next(int2) == 0) {
 floats[int0 + 5] = (float)(Math.sin(double1 * vector3f0.x()) * Math.sin(double1 * vector3f0.y()) * double0);
 } else {
 floats[int0 + 5] = 0.0F;
 }
 }

 if (this->forcedFriction > -1.0F) {
 floats[int0 + 2] = this->forcedFriction;
 }
 }

 /**
 * Used in mechanics UI, we enable the vehicle in Bullet when starting mechanics so physic will be updated. When we close the UI, we should disable it in Bullet, expect if the engine is running.
 */
 void setActiveInBullet(bool active) {
 if (active || !this->isEngineRunning()) {
 ;
 }
 }

 bool areAllDoorsLocked() {
 for (int int0 = 0; int0 < this->getMaxPassengers(); int0++) {
 VehiclePart part = this->getPassengerDoor(int0);
 if (part != nullptr && part.getDoor() != nullptr && !part.getDoor().isLocked()) {
 return false;
 }
 }

 return true;
 }

 bool isAnyDoorLocked() {
 for (int int0 = 0; int0 < this->getMaxPassengers(); int0++) {
 VehiclePart part = this->getPassengerDoor(int0);
 if (part != nullptr && part.getDoor() != nullptr && part.getDoor().isLocked()) {
 return true;
 }
 }

 return false;
 }

 float getRemainingFuelPercentage() {
 VehiclePart part = this->getPartById("GasTank");
 return part = = nullptr ? 0.0F : part.getContainerContentAmount() / part.getContainerCapacity() * 100.0F;
 }

 int getMechanicalID() {
 return this->mechanicalID;
 }

 void setMechanicalID(int _mechanicalID) {
 this->mechanicalID = _mechanicalID;
 }

 bool needPartsUpdate() {
 return this->needPartsUpdate;
 }

 void setNeedPartsUpdate(bool _needPartsUpdate) {
 this->needPartsUpdate = _needPartsUpdate;
 }

 VehiclePart getHeater() {
 return this->getPartById("Heater");
 }

 int windowsOpen() {
 int int0 = 0;

 for (int int1 = 0; int1 < this->getPartCount(); int1++) {
 VehiclePart part = this->getPartByIndex(int1);
 if (part.window != nullptr && part.window.open) {
 int0++;
 }
 }

 return int0;
 }

 bool isAlarmed() {
 return this->alarmed;
 }

 void setAlarmed(bool _alarmed) {
 this->alarmed = _alarmed;
 if (_alarmed) {
 this->setPreviouslyEntered(false);
 }
 }

 void triggerAlarm() {
 if (this->alarmed) {
 this->alarmed = false;
 this->alarmTime = Rand.Next(1500, 3000);
 this->alarmAccumulator = 0.0F;
 }
 }

 void doAlarm() {
 if (this->alarmTime > 0) {
 if (this->getBatteryCharge() <= 0.0F) {
 if (this->soundHornOn) {
 this->onHornStop();
 }

 this->alarmTime = -1;
 return;
 }

 this->alarmAccumulator = this->alarmAccumulator + GameTime.instance.getMultiplier() / 1.6F;
 if (this->alarmAccumulator >= this->alarmTime) {
 this->onHornStop();
 this->setHeadlightsOn(false);
 this->alarmTime = -1;
 return;
 }

 int int0 = (int)this->alarmAccumulator / 20;
 if (!this->soundHornOn && int0 % 2 == 0) {
 this->onHornStart();
 this->setHeadlightsOn(true);
 }

 if (this->soundHornOn && int0 % 2 == 1) {
 this->onHornStop();
 this->setHeadlightsOn(false);
 }
 }
 }

 bool isMechanicUIOpen() {
 return this->mechanicUIOpen;
 }

 void setMechanicUIOpen(bool _mechanicUIOpen) {
 this->mechanicUIOpen = _mechanicUIOpen;
 }

 void damagePlayers(float damage) {
 if (SandboxOptions.instance.PlayerDamageFromCrash.getValue()) {
 if (!GameClient.bClient) {
 for (int int0 = 0; int0 < this->passengers.length; int0++) {
 if (this->getPassenger(int0).character != nullptr) {
 IsoGameCharacter character = this->getPassenger(int0).character;
 if (GameServer.bServer && character instanceof IsoPlayer) {
 GameServer.sendPlayerDamagedByCarCrash((IsoPlayer)character, damage);
 } else {
 this->addRandomDamageFromCrash(character, damage);
 LuaEventManager.triggerEvent("OnPlayerGetDamage", character, "CARCRASHDAMAGE", damage);
 }
 }
 }
 }
 }
 }

 void addRandomDamageFromCrash(IsoGameCharacter chr, float damage) {
 int int0 = 1;
 if (damage > 40.0F) {
 int0 = Rand.Next(1, 3);
 }

 if (damage > 70.0F) {
 int0 = Rand.Next(2, 4);
 }

 int int1 = 0;

 for (int int2 = 0; int2 < chr.getVehicle().getPartCount(); int2++) {
 VehiclePart part = chr.getVehicle().getPartByIndex(int2);
 if (part.window != nullptr && part.getCondition() < 15) {
 int1++;
 }
 }

 for (int int3 = 0; int3 < int0; int3++) {
 int int4 = Rand.Next(BodyPartType.ToIndex(BodyPartType.Hand_L), BodyPartType.ToIndex(BodyPartType.MAX);
 BodyPart bodyPart = chr.getBodyDamage().getBodyPart(BodyPartType.FromIndex(int4);
 float float0 = Math.max(Rand.Next(damage - 15.0F, damage), 5.0F);
 if (chr.Traits.FastHealer.isSet()) {
 float0 = (float)(float0 * 0.8);
 } else if (chr.Traits.SlowHealer.isSet()) {
 float0 = (float)(float0 * 1.2);
 }

 switch (SandboxOptions.instance.InjurySeverity.getValue()) {
 case 1:
 float0 *= 0.5F;
 break;
 case 3:
 float0 *= 1.5F;
 }

 float0 *= this->getScript().getPlayerDamageProtection();
 float0 = (float)(float0 * 0.9);
 bodyPart.AddDamage(float0);
 if (float0 > 40.0F && Rand.Next(12) == 0) {
 bodyPart.generateDeepWound();
 } else if (float0 > 50.0F && Rand.Next(10) == 0 && SandboxOptions.instance.BoneFracture.getValue()) {
 if (bodyPart.getType() != BodyPartType.Neck && bodyPart.getType() != BodyPartType.Groin) {
 bodyPart.setFractureTime(Rand.Next(Rand.Next(10.0F, float0 + 10.0F), Rand.Next(float0 + 20.0F, float0 + 30.0F);
 } else {
 bodyPart.generateDeepWound();
 }
 }

 if (float0 > 30.0F && Rand.Next(12 - int1) == 0) {
 bodyPart = chr.getBodyDamage().setScratchedWindow();
 if (Rand.Next(5) == 0) {
 bodyPart.generateDeepWound();
 bodyPart.setHaveGlass(true);
 }
 }
 }
 }

 void hitVehicle(IsoGameCharacter attacker, HandWeapon weapon) {
 float float0 = 1.0F;
 if (weapon == nullptr) {
 weapon = (HandWeapon)InventoryItemFactory.CreateItem("Base.BareHands");
 }

 float0 = weapon.getDoorDamage();
 if (attacker.isCriticalHit()) {
 float0 *= 10.0F;
 }

 VehiclePart part0 = this->getNearestBodyworkPart(attacker);
 if (part0 != nullptr) {
 VehicleWindow vehicleWindow = part0.getWindow();

 for (int int0 = 0; int0 < part0.getChildCount(); int0++) {
 VehiclePart part1 = part0.getChild(int0);
 if (part1.getWindow() != nullptr) {
 vehicleWindow = part1.getWindow();
 break;
 }
 }

 if (vehicleWindow != nullptr && vehicleWindow.getHealth() > 0) {
 vehicleWindow.damage((int)float0);
 this->transmitPartWindow(part0);
 if (vehicleWindow.getHealth() == 0) {
 VehicleManager.sendSoundFromServer(this, (byte)1);
 }
 } else {
 part0.setCondition(part0.getCondition() - (int)float0);
 this->transmitPartItem(part0);
 }

 part0.updateFlags = (short)(part0.updateFlags | 2048);
 this->updateFlags = (short)(this->updateFlags | 2048);
 } else {
 Vector3f vector3f = TL_vector3f_pool.get().alloc();
 this->getLocalPos(attacker.getX(), attacker.getY(), attacker.getZ(), vector3f);
 bool boolean0 = vector3f.x > 0.0F;
 TL_vector3f_pool.get().release(vector3f);
 if (boolean0) {
 this->addDamageFront((int)float0);
 } else {
 this->addDamageRear((int)float0);
 }

 this->updateFlags = (short)(this->updateFlags | 2048);
 }
 }

 bool isTrunkLocked() {
 VehiclePart part = this->getPartById("TrunkDoor");
 if (part == nullptr) {
 part = this->getPartById("DoorRear");
 }

 return part != nullptr && part.getDoor() != nullptr && part.getInventoryItem() != nullptr ? part.getDoor().isLocked() : false;
 }

 void setTrunkLocked(bool locked) {
 VehiclePart part = this->getPartById("TrunkDoor");
 if (part == nullptr) {
 part = this->getPartById("DoorRear");
 }

 if (part != nullptr && part.getDoor() != nullptr && part.getInventoryItem() != nullptr) {
 part.getDoor().setLocked(locked);
 if (GameServer.bServer) {
 this->transmitPartDoor(part);
 }
 }
 }

 VehiclePart getNearestBodyworkPart(IsoGameCharacter chr) {
 for (int int0 = 0; int0 < this->getPartCount(); int0++) {
 VehiclePart part = this->getPartByIndex(int0);
 if (("door" == part.getCategory()) || "bodywork" == part.getCategory())) && this->isInArea(part.getArea(), chr) && part.getCondition() > 0) {
 return part;
 }
 }

 return nullptr;
 }

 double getSirenStartTime() {
 return this->sirenStartTime;
 }

 void setSirenStartTime(double worldAgeHours) {
 this->sirenStartTime = worldAgeHours;
 }

 bool sirenShutoffTimeExpired() {
 double double0 = SandboxOptions.instance.SirenShutoffHours.getValue();
 if (double0 <= 0.0) {
 return false;
 } else {
 double double1 = GameTime.instance.getWorldAgeHours();
 if (this->sirenStartTime > double1) {
 this->sirenStartTime = double1;
 }

 return this->sirenStartTime + double0 < double1;
 }
 }

 void repair() {
 for (int int0 = 0; int0 < this->getPartCount(); int0++) {
 VehiclePart part = this->getPartByIndex(int0);
 part.repair();
 }

 this->rust = 0.0F;
 this->transmitRust();
 this->bloodIntensity.clear();
 this->transmitBlood();
 this->doBloodOverlay();
 }

 bool isAnyListenerInside() {
 for (int int0 = 0; int0 < this->getMaxPassengers(); int0++) {
 IsoGameCharacter character = this->getCharacter(int0);
 if (character instanceof IsoPlayer && ((IsoPlayer)character).isLocalPlayer() && !character.Traits.Deaf.isSet()) {
 return true;
 }
 }

 return false;
 }

 bool couldCrawlerAttackPassenger(IsoGameCharacter chr) {
 int int0 = this->getSeat(chr);
 return int0 = = -1 ? false : false;
 }

 bool isGoodCar() {
 return this->isGoodCar;
 }

 void setGoodCar(bool _isGoodCar) {
 this->isGoodCar = _isGoodCar;
 }

 InventoryItem getCurrentKey() {
 return this->currentKey;
 }

 void setCurrentKey(InventoryItem _currentKey) {
 this->currentKey = _currentKey;
 }

 bool isInForest() {
 return this->getSquare() != nullptr
 && this->getSquare().getZone() != nullptr
 && (
 "Forest" == this->getSquare().getZone().getType())
 || "DeepForest" == this->getSquare().getZone().getType())
 || "FarmLand" == this->getSquare().getZone().getType())
 );
 }

 /**
 * Give the offroad efficiency of the car, based on car's script + where the vehicle is (in forest you get more damage than vegitation) Currently x2 to balance things
 */
 float getOffroadEfficiency() {
 return this->isInForest() ? this->script.getOffroadEfficiency() * 1.5F : this->script.getOffroadEfficiency() * 2.0F;
 }

 void doChrHitImpulse(IsoObject chr) {
 float float0 = 22.0F;
 Vector3f vector3f0 = this->getLinearVelocity(TL_vector3f_pool.get().alloc());
 vector3f0.y = 0.0F;
 Vector3f vector3f1 = TL_vector3f_pool.get().alloc();
 vector3f1.set(this->x - chr.getX(), 0.0F, this->z - chr.getY());
 vector3f1.normalize();
 vector3f0.mul(vector3f1);
 TL_vector3f_pool.get().release(vector3f1);
 float float1 = vector3f0.length();
 float1 = Math.min(float1, float0);
 if (float1 < 0.05F) {
 TL_vector3f_pool.get().release(vector3f0);
 } else {
 if (GameServer.bServer) {
 if (chr instanceof IsoZombie) {
 ((IsoZombie)chr).setThumpFlag(1);
 }
 } else {
 SoundManager.instance.PlayWorldSound("ZombieThumpGeneric", chr.square, 0.0F, 20.0F, 0.9F, true);
 }

 Vector3f vector3f2 = TL_vector3f_pool.get().alloc();
 vector3f2.set(this->x - chr.getX(), 0.0F, this->y - chr.getY());
 vector3f2.normalize();
 vector3f0.normalize();
 float float2 = vector3f0.dot(vector3f2);
 TL_vector3f_pool.get().release(vector3f0);
 TL_vector3f_pool.get().release(vector3f2);
 this->ApplyImpulse(chr, this->getFudgedMass() * 3.0F * float1 / float0 * Math.abs(float2);
 }
 }

 bool isDoColor() {
 return this->doColor;
 }

 void setDoColor(bool _doColor) {
 this->doColor = _doColor;
 }

 float getBrakeSpeedBetweenUpdate() {
 return this->brakeBetweenUpdatesSpeed;
 }

 IsoGridSquare getSquare() {
 return this->getCell().getGridSquare((double)this->x, (double)this->y, (double)this->z);
 }

 void setColor(float value, float saturation, float hue) {
 this->colorValue = value;
 this->colorSaturation = saturation;
 this->colorHue = hue;
 }

 void setColorHSV(float hue, float saturation, float value) {
 this->colorHue = hue;
 this->colorSaturation = saturation;
 this->colorValue = value;
 }

 float getColorHue() {
 return this->colorHue;
 }

 float getColorSaturation() {
 return this->colorSaturation;
 }

 float getColorValue() {
 return this->colorValue;
 }

 bool isRemovedFromWorld() {
 return this->removedFromWorld;
 }

 float getInsideTemperature() {
 VehiclePart part = this->getPartById("PassengerCompartment");
 float float0 = 0.0F;
 if (part != nullptr && part.getModData() != nullptr) {
 if (part.getModData().rawget("temperature") != nullptr) {
 float0 += ((Double)part.getModData().rawget("temperature")).floatValue();
 }

 if (part.getModData().rawget("windowtemperature") != nullptr) {
 float0 += ((Double)part.getModData().rawget("windowtemperature")).floatValue();
 }
 }

 return float0;
 }

 AnimationPlayer getAnimationPlayer() {
 std::string string = this->getScript().getModel().file;
 Model model = ModelManager.instance.getLoadedModel(string);
 if (model != nullptr && !model.bStatic) {
 if (this->m_animPlayer != nullptr && this->m_animPlayer.getModel() != model) {
 this->m_animPlayer = Pool.tryRelease(this->m_animPlayer);
 }

 if (this->m_animPlayer == nullptr) {
 this->m_animPlayer = AnimationPlayer.alloc(model);
 }

 return this->m_animPlayer;
 } else {
 return nullptr;
 }
 }

 void releaseAnimationPlayers() {
 this->m_animPlayer = Pool.tryRelease(this->m_animPlayer);
 PZArrayUtil.forEach(this->models, BaseVehicle.ModelInfo::releaseAnimationPlayer);
 }

 void setAddThumpWorldSound(bool add) {
 this->bAddThumpWorldSound = add;
 }

 void Thump(IsoMovingObject thumper) {
 VehiclePart part0 = this->getPartById("lightbar");
 if (part0 != nullptr) {
 if (part0.getCondition() <= 0) {
 thumper.setThumpTarget(nullptr);
 }

 VehiclePart part1 = this->getUseablePart((IsoGameCharacter)thumper);
 if (part1 != nullptr) {
 part1.setCondition(part1.getCondition() - Rand.Next(1, 5);
 }

 part0.setCondition(part0.getCondition() - Rand.Next(1, 5);
 }
 }

 void WeaponHit(IsoGameCharacter chr, HandWeapon weapon) {
 }

 Thumpable getThumpableFor(IsoGameCharacter chr) {
 return nullptr;
 }

 float getThumpCondition() {
 return 1.0F;
 }

 bool isRegulator() {
 return this->regulator;
 }

 void setRegulator(bool _regulator) {
 this->regulator = _regulator;
 }

 float getRegulatorSpeed() {
 return this->regulatorSpeed;
 }

 void setRegulatorSpeed(float _regulatorSpeed) {
 this->regulatorSpeed = _regulatorSpeed;
 }

 float getCurrentSpeedForRegulator() {
 return (float)Math.max(5.0 * Math.floor(this->jniSpeed / 5.0F), 5.0);
 }

 void setVehicleTowing(BaseVehicle vehicleB, const std::string& attachmentA, const std::string& attachmentB) {
 this->vehicleTowing = vehicleB;
 this->vehicleTowingID = this->vehicleTowing == nullptr ? -1 : this->vehicleTowing.getSqlId();
 this->towAttachmentSelf = attachmentA;
 this->towAttachmentOther = attachmentB;
 this->towConstraintZOffset = 0.0F;
 }

 void setVehicleTowedBy(BaseVehicle vehicleA, const std::string& attachmentA, const std::string& attachmentB) {
 this->vehicleTowedBy = vehicleA;
 this->vehicleTowedByID = this->vehicleTowedBy == nullptr ? -1 : this->vehicleTowedBy.getSqlId();
 this->towAttachmentSelf = attachmentB;
 this->towAttachmentOther = attachmentA;
 this->towConstraintZOffset = 0.0F;
 }

 BaseVehicle getVehicleTowing() {
 return this->vehicleTowing;
 }

 BaseVehicle getVehicleTowedBy() {
 return this->vehicleTowedBy;
 }

 bool attachmentExist(const std::string& attachmentName) {
 VehicleScript vehicleScript = this->getScript();
 if (vehicleScript == nullptr) {
 return false;
 } else {
 ModelAttachment modelAttachment = vehicleScript.getAttachmentById(attachmentName);
 return modelAttachment != nullptr;
 }
 }

 Vector3f getAttachmentLocalPos(const std::string& attachmentName, Vector3f v) {
 VehicleScript vehicleScript = this->getScript();
 if (vehicleScript == nullptr) {
 return nullptr;
 } else {
 ModelAttachment modelAttachment = vehicleScript.getAttachmentById(attachmentName);
 if (modelAttachment == nullptr) {
 return nullptr;
 } else {
 v.set(modelAttachment.getOffset());
 return vehicleScript.getModel() == nullptr ? v : v.add(vehicleScript.getModel().getOffset());
 }
 }
 }

 Vector3f getAttachmentWorldPos(const std::string& attachmentName, Vector3f v) {
 v = this->getAttachmentLocalPos(attachmentName, v);
 return v = = nullptr ? nullptr : this->getWorldPos(v, v);
 }

 void setForceBrake() {
 this->getController().clientControls.forceBrake = System.currentTimeMillis();
 }

 Vector3f getTowingLocalPos(const std::string& attachmentName, Vector3f v) {
 return this->getAttachmentLocalPos(attachmentName, v);
 }

 Vector3f getTowedByLocalPos(const std::string& attachmentName, Vector3f v) {
 return this->getAttachmentLocalPos(attachmentName, v);
 }

 Vector3f getTowingWorldPos(const std::string& attachmentName, Vector3f v) {
 v = this->getTowingLocalPos(attachmentName, v);
 return v = = nullptr ? nullptr : this->getWorldPos(v, v);
 }

 Vector3f getTowedByWorldPos(const std::string& attachmentName, Vector3f v) {
 v = this->getTowedByLocalPos(attachmentName, v);
 return v = = nullptr ? nullptr : this->getWorldPos(v, v);
 }

 Vector3f getPlayerTrailerLocalPos(const std::string& attachmentName, bool left, Vector3f v) {
 ModelAttachment modelAttachment = this->getScript().getAttachmentById(attachmentName);
 if (modelAttachment == nullptr) {
 return nullptr;
 } else {
 Vector3f vector3f0 = this->getScript().getExtents();
 Vector3f vector3f1 = this->getScript().getCenterOfMassOffset();
 float float0 = vector3f1.x + vector3f0.x / 2.0F + 0.3F + 0.05F;
 if (!left) {
 float0 *= -1.0F;
 }

 return modelAttachment.getOffset().z > 0.0F
 ? v.set(float0, 0.0F, vector3f1.z + vector3f0.z / 2.0F + 0.3F + 0.05F)
 : v.set(float0, 0.0F, vector3f1.z - (vector3f0.z / 2.0F + 0.3F + 0.05F);
 }
 }

 Vector3f getPlayerTrailerWorldPos(const std::string& attachmentName, bool left, Vector3f v) {
 v = this->getPlayerTrailerLocalPos(attachmentName, left, v);
 if (v == nullptr) {
 return nullptr;
 } else {
 this->getWorldPos(v, v);
 v.z = (int)this->z;
 Vector3f vector3f = this->getTowingWorldPos(attachmentName, TL_vector3f_pool.get().alloc());
 bool boolean0 = PolygonalMap2.instance.lineClearCollide(v.x, v.y, vector3f.x, vector3f.y, (int)this->z, this, false, false);
 TL_vector3f_pool.get().release(vector3f);
 return boolean0 ? nullptr : v;
 }
 }

 void drawTowingRope() {
 BaseVehicle vehicle0 = this->getVehicleTowing();
 if (vehicle0 != nullptr) {
 BaseVehicle.Vector3fObjectPool vector3fObjectPool = TL_vector3f_pool.get();
 Vector3f vector3f0 = this->getAttachmentWorldPos("trailer", vector3fObjectPool.alloc());
 Vector3f vector3f1 = this->getAttachmentWorldPos("trailerfront", vector3fObjectPool.alloc());
 ModelAttachment modelAttachment = this->script.getAttachmentById("trailerfront");
 if (modelAttachment != nullptr) {
 vector3f1.set(modelAttachment.getOffset());
 }

 Vector2 vector = new Vector2();
 vector.x = vehicle0.x;
 vector.y = vehicle0.y;
 vector.x = vector.x - this->x;
 vector.y = vector.y - this->y;
 vector.setLength(2.0F);
 this->drawDirectionLine(vector, vector.getLength(), 1.0F, 0.5F, 0.5F);
 }
 }

 void drawDirectionLine(Vector2 dir, float length, float r, float g, float b) {
 float float0 = this->x + dir.x * length;
 float float1 = this->y + dir.y * length;
 float float2 = IsoUtils.XToScreenExact(this->x, this->y, this->z, 0);
 float float3 = IsoUtils.YToScreenExact(this->x, this->y, this->z, 0);
 float float4 = IsoUtils.XToScreenExact(float0, float1, this->z, 0);
 float float5 = IsoUtils.YToScreenExact(float0, float1, this->z, 0);
 LineDrawer.drawLine(float2, float3, float4, float5, r, g, b, 0.5F, 1);
 }

 void addPointConstraint(IsoPlayer player, BaseVehicle vehicleB, const std::string& attachmentA, const std::string& attachmentB) {
 this->addPointConstraint(player, vehicleB, attachmentA, attachmentB, false);
 }

 void addPointConstraint(IsoPlayer player, BaseVehicle vehicleB, const std::string& attachmentA, const std::string& attachmentB, bool remote) {
 if (vehicleB == nullptr
 || player != nullptr
 && (
 IsoUtils.DistanceToSquared(player.x, player.y, this->x, this->y) > 100.0F
 || IsoUtils.DistanceToSquared(player.x, player.y, vehicleB.x, vehicleB.y) > 100.0F
 )) {
 DebugLog.General.warn("The " + player.getUsername() + " user attached vehicles at a long distance");
 }

 this->breakConstraint(true, remote);
 vehicleB.breakConstraint(true, remote);
 BaseVehicle.Vector3fObjectPool vector3fObjectPool = TL_vector3f_pool.get();
 Vector3f vector3f0 = this->getTowingLocalPos(attachmentA, vector3fObjectPool.alloc());
 Vector3f vector3f1 = vehicleB.getTowedByLocalPos(attachmentB, vector3fObjectPool.alloc());
 if (vector3f0 != nullptr && vector3f1 != nullptr) {
 if (!GameServer.bServer) {
 if (!this->getScriptName().contains("Trailer") && !vehicleB.getScriptName().contains("Trailer")) {
 this->constraintTowing = Bullet.addRopeConstraint(
 this->VehicleID, vehicleB.VehicleID, vector3f0.x, vector3f0.y, vector3f0.z, vector3f1.x, vector3f1.y, vector3f1.z, 1.5F
 );
 } else {
 this->constraintTowing = Bullet.addPointConstraint(
 this->VehicleID, vehicleB.VehicleID, vector3f0.x, vector3f0.y, vector3f0.z, vector3f1.x, vector3f1.y, vector3f1.z
 );
 }
 }

 vehicleB.constraintTowing = this->constraintTowing;
 this->setVehicleTowing(vehicleB, attachmentA, attachmentB);
 vehicleB.setVehicleTowedBy(this, attachmentA, attachmentB);
 vector3fObjectPool.release(vector3f0);
 vector3fObjectPool.release(vector3f1);
 this->constraintChanged();
 vehicleB.constraintChanged();
 if (GameServer.bServer
 && player != nullptr
 && this->netPlayerAuthorization == BaseVehicle.Authorization.Server
 && vehicleB.netPlayerAuthorization == BaseVehicle.Authorization.Server) {
 this->setNetPlayerAuthorization(BaseVehicle.Authorization.LocalCollide, player.OnlineID);
 this->authSimulationTime = System.currentTimeMillis();
 vehicleB.setNetPlayerAuthorization(BaseVehicle.Authorization.LocalCollide, player.OnlineID);
 vehicleB.authSimulationTime = System.currentTimeMillis();
 }

 if (GameServer.bServer && !remote) {
 VehicleManager.instance.sendTowing(this, vehicleB, attachmentA, attachmentB);
 }
 } else {
 if (vector3f0 != nullptr) {
 vector3fObjectPool.release(vector3f0);
 }

 if (vector3f1 != nullptr) {
 vector3fObjectPool.release(vector3f1);
 }
 }
 }

 void authorizationChanged(IsoGameCharacter character) {
 if (character != nullptr) {
 this->setNetPlayerAuthorization(BaseVehicle.Authorization.Local, character.getOnlineID());
 } else {
 this->setNetPlayerAuthorization(BaseVehicle.Authorization.Server, -1);
 }
 }

 void constraintChanged() {
 long long0 = System.currentTimeMillis();
 this->setPhysicsActive(true);
 this->constraintChangedTime = long0;
 if (GameServer.bServer) {
 if (this->getVehicleTowing() != nullptr) {
 this->authorizationChanged(this->getDriver());
 this->getVehicleTowing().authorizationChanged(this->getDriver());
 } else if (this->getVehicleTowedBy() != nullptr) {
 this->authorizationChanged(this->getVehicleTowedBy().getDriver());
 this->getVehicleTowedBy().authorizationChanged(this->getVehicleTowedBy().getDriver());
 } else {
 this->authorizationChanged(this->getDriver());
 }
 }
 }

 void breakConstraint(bool forgetID, bool remote) {
 if (GameServer.bServer || this->constraintTowing != -1) {
 if (!GameServer.bServer) {
 Bullet.removeConstraint(this->constraintTowing);
 }

 this->constraintTowing = -1;
 if (this->vehicleTowing != nullptr) {
 if (GameServer.bServer && !remote) {
 VehicleManager.instance.sendDetachTowing(this, this->vehicleTowing);
 }

 this->vehicleTowing.vehicleTowedBy = nullptr;
 this->vehicleTowing.constraintTowing = -1;
 if (forgetID) {
 this->vehicleTowingID = -1;
 this->vehicleTowing.vehicleTowedByID = -1;
 }

 this->vehicleTowing.constraintChanged();
 this->vehicleTowing = nullptr;
 }

 if (this->vehicleTowedBy != nullptr) {
 if (GameServer.bServer && !remote) {
 VehicleManager.instance.sendDetachTowing(this->vehicleTowedBy, this);
 }

 this->vehicleTowedBy.vehicleTowing = nullptr;
 this->vehicleTowedBy.constraintTowing = -1;
 if (forgetID) {
 this->vehicleTowedBy.vehicleTowingID = -1;
 this->vehicleTowedByID = -1;
 }

 this->vehicleTowedBy.constraintChanged();
 this->vehicleTowedBy = nullptr;
 }

 this->constraintChanged();
 }
 }

 bool canAttachTrailer(BaseVehicle vehicleB, const std::string& attachmentA, const std::string& attachmentB) {
 return this->canAttachTrailer(vehicleB, attachmentA, attachmentB, false);
 }

 bool canAttachTrailer(BaseVehicle vehicleB, const std::string& attachmentA, const std::string& attachmentB, bool reconnect) {
 if (this == vehicleB || this->physics == nullptr || this->constraintTowing != -1) {
 return false;
 } else if (vehicleB != nullptr && vehicleB.physics != nullptr && vehicleB.constraintTowing == -1) {
 BaseVehicle.Vector3fObjectPool vector3fObjectPool = TL_vector3f_pool.get();
 Vector3f vector3f0 = this->getTowingWorldPos(attachmentA, vector3fObjectPool.alloc());
 Vector3f vector3f1 = vehicleB.getTowedByWorldPos(attachmentB, vector3fObjectPool.alloc());
 if (vector3f0 != nullptr && vector3f1 != nullptr) {
 float float0 = IsoUtils.DistanceToSquared(vector3f0.x, vector3f0.y, 0.0F, vector3f1.x, vector3f1.y, 0.0F);
 vector3fObjectPool.release(vector3f0);
 vector3fObjectPool.release(vector3f1);
 ModelAttachment modelAttachment0 = this->script.getAttachmentById(attachmentA);
 ModelAttachment modelAttachment1 = vehicleB.script.getAttachmentById(attachmentB);
 if (modelAttachment0 != nullptr && modelAttachment0.getCanAttach() != nullptr && !modelAttachment0.getCanAttach().contains(attachmentB) {
 return false;
 } else if (modelAttachment1 != nullptr && modelAttachment1.getCanAttach() != nullptr && !modelAttachment1.getCanAttach().contains(attachmentA) {
 return false;
 } else {
 DebugLog.Vehicle.trace("vidA=%d (%s) vidB=%d (%s) dist: %f", this->getId(), attachmentA, vehicleB.getId(), attachmentB, float0);
 bool boolean0 = this->getScriptName().contains("Trailer") || vehicleB.getScriptName().contains("Trailer");
 return float0 < (reconnect ? 10.0F : (boolean0 ? 1.0F : 4.0F);
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
 short short0 = VehicleManager.instance.getTowedVehicleID(this->VehicleID);
 if (short0 != -1) {
 BaseVehicle vehicle1 = VehicleManager.instance.getVehicleByID(short0);
 if (vehicle1 != nullptr) {
 if (this->canAttachTrailer(vehicle1, this->towAttachmentSelf, this->towAttachmentOther, true) {
 this->addPointConstraint(nullptr, vehicle1, this->towAttachmentSelf, this->towAttachmentOther, true);
 }
 }
 }
 } else if (this->vehicleTowing == nullptr) {
 if (this->vehicleTowingID != -1) {
 BaseVehicle vehicle2 = nullptr;
 std::vector arrayList = IsoWorld.instance.CurrentCell.getVehicles();

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 BaseVehicle vehicle3 = (BaseVehicle)arrayList.get(int0);
 if (vehicle3.getSqlId() == this->vehicleTowingID) {
 vehicle2 = vehicle3;
 break;
 }
 }

 if (vehicle2 != nullptr) {
 if (this->canAttachTrailer(vehicle2, this->towAttachmentSelf, this->towAttachmentOther, true) {
 this->addPointConstraint(nullptr, vehicle2, this->towAttachmentSelf, this->towAttachmentOther, false);
 }
 }
 }
 }
 }

 void positionTrailer(BaseVehicle trailer) {
 if (trailer != nullptr) {
 BaseVehicle.Vector3fObjectPool vector3fObjectPool = TL_vector3f_pool.get();
 Vector3f vector3f0 = this->getTowingWorldPos("trailer", vector3fObjectPool.alloc());
 Vector3f vector3f1 = trailer.getTowedByWorldPos("trailer", vector3fObjectPool.alloc());
 if (vector3f0 != nullptr && vector3f1 != nullptr) {
 vector3f1.sub(trailer.x, trailer.y, trailer.z);
 vector3f0.sub(vector3f1);
 Transform transform = trailer.getWorldTransform(this->tempTransform);
 transform.origin
 .set(vector3f0.x - WorldSimulation.instance.offsetX, trailer.jniTransform.origin.y, vector3f0.y - WorldSimulation.instance.offsetY);
 trailer.setWorldTransform(transform);
 trailer.setX(vector3f0.x);
 trailer.setLx(vector3f0.x);
 trailer.setY(vector3f0.y);
 trailer.setLy(vector3f0.y);
 trailer.setCurrent(this->getCell().getGridSquare((double)vector3f0.x, (double)vector3f0.y, 0.0);
 this->addPointConstraint(nullptr, trailer, "trailer", "trailer");
 vector3fObjectPool.release(vector3f0);
 vector3fObjectPool.release(vector3f1);
 }
 }
 }

 std::string getTowAttachmentSelf() {
 return this->towAttachmentSelf;
 }

 std::string getTowAttachmentOther() {
 return this->towAttachmentOther;
 }

 VehicleEngineRPM getVehicleEngineRPM() {
 if (this->vehicleEngineRPM == nullptr) {
 this->vehicleEngineRPM = ScriptManager.instance.getVehicleEngineRPM(this->getScript().getEngineRPMType());
 if (this->vehicleEngineRPM == nullptr) {
 DebugLog.General.warn("unknown vehicleEngineRPM \"%s\"", this->getScript().getEngineRPMType());
 this->vehicleEngineRPM = std::make_unique<VehicleEngineRPM>();
 }
 }

 return this->vehicleEngineRPM;
 }

 FMODParameterList getFMODParameters() {
 return this->fmodParameters;
 }

 void startEvent(long eventInstance, GameSoundClip clip, BitSet parameterSet) {
 FMODParameterList fMODParameterList = this->getFMODParameters();
 std::vector arrayList = clip.eventDescription.parameters;

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 FMOD_STUDIO_PARAMETER_DESCRIPTION fmod_studio_parameter_description = (FMOD_STUDIO_PARAMETER_DESCRIPTION)arrayList.get(int0);
 if (!parameterSet.get(fmod_studio_parameter_description.globalIndex) {
 FMODParameter fMODParameter = fMODParameterList.get(fmod_studio_parameter_description);
 if (fMODParameter != nullptr) {
 fMODParameter.startEventInstance(eventInstance);
 }
 }
 }
 }

 void updateEvent(long eventInstance, GameSoundClip clip) {
 }

 void stopEvent(long eventInstance, GameSoundClip clip, BitSet parameterSet) {
 FMODParameterList fMODParameterList = this->getFMODParameters();
 std::vector arrayList = clip.eventDescription.parameters;

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 FMOD_STUDIO_PARAMETER_DESCRIPTION fmod_studio_parameter_description = (FMOD_STUDIO_PARAMETER_DESCRIPTION)arrayList.get(int0);
 if (!parameterSet.get(fmod_studio_parameter_description.globalIndex) {
 FMODParameter fMODParameter = fMODParameterList.get(fmod_studio_parameter_description);
 if (fMODParameter != nullptr) {
 fMODParameter.stopEventInstance(eventInstance);
 }
 }
 }
 }

 void stopEngineSounds() {
 if (this->emitter != nullptr) {
 for (int int0 = 0; int0 < this->new_EngineSoundId.length; int0++) {
 if (this->new_EngineSoundId[int0] != 0L) {
 this->getEmitter().stopSound(this->new_EngineSoundId[int0]);
 this->new_EngineSoundId[int0] = 0L;
 }
 }

 if (this->combinedEngineSound != 0L) {
 if (this->getEmitter().hasSustainPoints(this->combinedEngineSound) {
 this->getEmitter().triggerCue(this->combinedEngineSound);
 } else {
 this->getEmitter().stopSound(this->combinedEngineSound);
 }

 this->combinedEngineSound = 0L;
 }
 }
 }

 BaseVehicle setSmashed(const std::string& location) {
 return this->setSmashed(location, false);
 }

 BaseVehicle setSmashed(const std::string& location, bool flipped) {
 std::string string = nullptr;
 int integer = nullptr;
 KahluaTableImpl kahluaTableImpl0 = (KahluaTableImpl)LuaManager.env.rawget("SmashedCarDefinitions");
 if (kahluaTableImpl0 != nullptr) {
 KahluaTableImpl kahluaTableImpl1 = (KahluaTableImpl)kahluaTableImpl0.rawget("cars");
 if (kahluaTableImpl1 != nullptr) {
 KahluaTableImpl kahluaTableImpl2 = (KahluaTableImpl)kahluaTableImpl1.rawget(this->getScriptName());
 if (kahluaTableImpl2 != nullptr) {
 string = kahluaTableImpl2.rawgetStr(location.toLowerCase());
 integer = kahluaTableImpl2.rawgetInt("skin");
 if (integer == -1) {
 integer = this->getSkinIndex();
 }
 }
 }
 }

 int int0 = this->getKeyId();
 if (string != nullptr) {
 this->removeFromWorld();
 this->permanentlyRemove();
 BaseVehicle vehicle = new BaseVehicle(IsoWorld.instance.CurrentCell);
 vehicle.setScriptName(string);
 vehicle.setScript();
 vehicle.setSkinIndex(integer);
 vehicle.setX(this->x);
 vehicle.setY(this->y);
 vehicle.setZ(this->z);
 vehicle.setDir(this->getDir());
 vehicle.savedRot.set(this->savedRot);
 if (flipped) {
 float float0 = this->getAngleY();
 vehicle.savedRot.rotationXYZ(0.0F, float0 * (float) (Math.PI / 180.0), (float) Math.PI);
 }

 vehicle.jniTransform.setRotation(vehicle.savedRot);
 if (IsoChunk.doSpawnedVehiclesInInvalidPosition(vehicle) {
 vehicle.setSquare(this->square);
 vehicle.square.chunk.vehicles.add(vehicle);
 vehicle.chunk = vehicle.square.chunk;
 vehicle.addToWorld();
 VehiclesDB2.instance.addVehicle(vehicle);
 }

 vehicle.setGeneralPartCondition(0.5F, 60.0F);
 VehiclePart part = vehicle.getPartById("Engine");
 if (part != nullptr) {
 part.setCondition(0);
 }

 vehicle.engineQuality = 0;
 vehicle.setKeyId(int0);
 return vehicle;
 } else {
 return this;
 }
 }

 bool isCollided(IsoGameCharacter character) {
 if (GameClient.bClient && this->getDriver() != nullptr && !this->getDriver().isLocal()) {
 return true;
 } else {
 Vector2 vector = this->testCollisionWithCharacter(character, 0.20000002F, this->hitVars.collision);
 return vector != nullptr && vector.x != -1.0F;
 }
 }

 public BaseVehicle.HitVars checkCollision(IsoGameCharacter target) {
 if (target.isProne()) {
 int int0 = this->testCollisionWithProneCharacter(target, true);
 if (int0 > 0) {
 this->hitVars.calc(target, this);
 this->hitCharacter(target, this->hitVars);
 return this->hitVars;
 } else {
 return nullptr;
 }
 } else {
 this->hitVars.calc(target, this);
 this->hitCharacter(target, this->hitVars);
 return this->hitVars;
 }
 }

 bool updateHitByVehicle(IsoGameCharacter target) {
 if (target.isVehicleCollisionActive(this) && (this->isCollided(target) || target.isCollidedWithVehicle()) && this->physics != nullptr) {
 BaseVehicle.HitVars hitVarsx = this->checkCollision(target);
 if (hitVarsx != nullptr) {
 target.doHitByVehicle(this, hitVarsx);
 return true;
 }
 }

 return false;
 }

 void hitCharacter(IsoGameCharacter character, BaseVehicle.HitVars vars) {
 if (vars.dot < 0.0F && !GameServer.bServer) {
 this->ApplyImpulse(character, vars.vehicleImpulse);
 }

 long long0 = System.currentTimeMillis();
 long long1 = (long0 - this->zombieHitTimestamp) / 1000L;
 this->zombiesHits = Math.max(this->zombiesHits - (int)long1, 0);
 if (long0 - this->zombieHitTimestamp > 700L) {
 this->zombieHitTimestamp = long0;
 this->zombiesHits++;
 this->zombiesHits = Math.min(this->zombiesHits, 20);
 }

 if (character instanceof IsoPlayer) {
 ((IsoPlayer)character).setVehicleHitLocation(this);
 } else if (character instanceof IsoZombie) {
 ((IsoZombie)character).setVehicleHitLocation(this);
 }

 if (vars.vehicleSpeed >= 5.0F || this->zombiesHits > 10) {
 vars.vehicleSpeed = this->getCurrentSpeedKmHour() / 5.0F;
 Vector3f vector3f = TL_vector3f_pool.get().alloc();
 this->getLocalPos(character.x, character.y, character.z, vector3f);
 if (vector3f.z > 0.0F) {
 int int0 = this->caclulateDamageWithBodies(true);
 if (!GameClient.bClient) {
 this->addDamageFrontHitAChr(int0);
 }

 DebugLog.Vehicle.trace("Damage car front hits=%d damage=%d", this->zombiesHits, int0);
 vars.vehicleDamage = int0;
 vars.isVehicleHitFromFront = true;
 } else {
 int int1 = this->caclulateDamageWithBodies(false);
 if (!GameClient.bClient) {
 this->addDamageRearHitAChr(int1);
 }

 DebugLog.Vehicle.trace("Damage car rear hits=%d damage=%d", this->zombiesHits, int1);
 vars.vehicleDamage = int1;
 vars.isVehicleHitFromFront = false;
 }

 TL_vector3f_pool.get().release(vector3f);
 }
 }

 public static enum Authorization {
 Server,
 LocalCollide,
 RemoteCollide,
 Local,
 Remote;

 private static HashMap<Byte, BaseVehicle.Authorization> authorizations = std::make_unique<HashMap<>>();

 public static BaseVehicle.Authorization valueOf(byte byte0) {
 return authorizations.getOrDefault(byte0, Server);
 }

 uint8_t index() {
 return (byte)this->ordinal();
 }

 static {
 Arrays.stream(values()).forEach(authorization -> authorizations.put(authorization.index(), authorization);
 }
 }

 public static class HitVars {
 static const float speedCap = 10.0F;
 const Vector3f velocity = new Vector3f();
 const Vector2 collision = new Vector2();
 float dot;
 float vehicleImpulse;
 float vehicleSpeed;
 const Vector3f targetImpulse = new Vector3f();
 bool isVehicleHitFromFront;
 bool isTargetHitFromBehind;
 int vehicleDamage;
 float hitSpeed;

 void calc(IsoGameCharacter target, BaseVehicle vehicle) {
 vehicle.getLinearVelocity(this->velocity);
 this->velocity.y = 0.0F;
 if (target instanceof IsoZombie) {
 this->vehicleSpeed = Math.min(this->velocity.length(), 10.0F);
 this->hitSpeed = this->vehicleSpeed + vehicle.getClientForce() / vehicle.getFudgedMass();
 } else {
 this->vehicleSpeed = (float)Math.sqrt(this->velocity.x * this->velocity.x + this->velocity.z * this->velocity.z);
 if (target.isOnFloor()) {
 this->hitSpeed = Math.max(this->vehicleSpeed * 6.0F, 5.0F);
 } else {
 this->hitSpeed = Math.max(this->vehicleSpeed * 2.0F, 5.0F);
 }
 }

 this->targetImpulse.set(vehicle.x - target.x, 0.0F, vehicle.y - target.y);
 this->targetImpulse.normalize();
 this->velocity.normalize();
 this->dot = this->velocity.dot(this->targetImpulse);
 this->targetImpulse.normalize();
 this->targetImpulse.mul(3.0F * this->vehicleSpeed / 10.0F);
 this->targetImpulse.set(this->targetImpulse.x, this->targetImpulse.y, this->targetImpulse.z);
 this->vehicleImpulse = vehicle.getFudgedMass() * 7.0F * this->vehicleSpeed / 10.0F * Math.abs(this->dot);
 this->isTargetHitFromBehind = "BEHIND" == target.testDotSide(vehicle);
 }
 }

 private static class L_testCollisionWithVehicle {
 static Vector2[] testVecs1 = new Vector2[4];
 static Vector2[] testVecs2 = new Vector2[4];
 static const Vector3f worldPos = new Vector3f();
 }

 public static class Matrix4fObjectPool extends ObjectPool<Matrix4f> {
 int allocated = 0;

 Matrix4fObjectPool() {
 super(Matrix4f::new);
 }

 Matrix4f makeObject() {
 this->allocated++;
 return (Matrix4f)super.makeObject();
 }
 }

 public static class MinMaxPosition {
 float minX;
 float maxX;
 float minY;
 float maxY;
 }

 public static class ModelInfo {
 VehiclePart part;
 public VehicleScript.Model scriptModel;
 ModelScript modelScript;
 int wheelIndex;
 const Matrix4f renderTransform = new Matrix4f();
 VehicleSubModelInstance modelInstance;
 AnimationPlayer m_animPlayer;
 AnimationTrack m_track;

 AnimationPlayer getAnimationPlayer() {
 if (this->part != nullptr && this->part.getParent() != nullptr) {
 BaseVehicle.ModelInfo modelInfo1 = this->part.getVehicle().getModelInfoForPart(this->part.getParent());
 if (modelInfo1 != nullptr) {
 return modelInfo1.getAnimationPlayer();
 }
 }

 std::string string = this->scriptModel.file;
 Model model = ModelManager.instance.getLoadedModel(string);
 if (model != nullptr && !model.bStatic) {
 if (this->m_animPlayer != nullptr && this->m_animPlayer.getModel() != model) {
 this->m_animPlayer = Pool.tryRelease(this->m_animPlayer);
 }

 if (this->m_animPlayer == nullptr) {
 this->m_animPlayer = AnimationPlayer.alloc(model);
 }

 return this->m_animPlayer;
 } else {
 return nullptr;
 }
 }

 void releaseAnimationPlayer() {
 this->m_animPlayer = Pool.tryRelease(this->m_animPlayer);
 }
 }

 public static class Passenger {
 IsoGameCharacter character;
 const Vector3f offset = new Vector3f();
 }

 public static class QuaternionfObjectPool extends ObjectPool<Quaternionf> {
 int allocated = 0;

 QuaternionfObjectPool() {
 super(Quaternionf::new);
 }

 Quaternionf makeObject() {
 this->allocated++;
 return (Quaternionf)super.makeObject();
 }
 }

 public static class ServerVehicleState {
 float x = -1.0F;
 float y;
 float z;
 Quaternionf orient = new Quaternionf();
 short flags;
 public BaseVehicle.Authorization netPlayerAuthorization = BaseVehicle.Authorization.Server;
 short netPlayerId = 0;

 public ServerVehicleState() {
 this->flags = 0;
 }

 void setAuthorization(BaseVehicle vehicle) {
 this->netPlayerAuthorization = vehicle.netPlayerAuthorization;
 this->netPlayerId = vehicle.netPlayerId;
 }

 bool shouldSend(BaseVehicle vehicle) {
 if (vehicle.getController() == nullptr) {
 return false;
 } else if (vehicle.updateLockTimeout > System.currentTimeMillis()) {
 return false;
 } else {
 this->flags = (short)(this->flags & 1);
 if (!vehicle.isNetPlayerAuthorization(this->netPlayerAuthorization) || !vehicle.isNetPlayerId(this->netPlayerId) {
 this->flags = (short)(this->flags | 16384);
 }

 this->flags = (short)(this->flags | vehicle.updateFlags);
 return this->flags != 0;
 }
 }
 }

 protected static class UpdateFlags {
 static const short Full = 1;
 static const short PositionOrientation = 2;
 static const short Engine = 4;
 static const short Lights = 8;
 static const short PartModData = 16;
 static const short PartUsedDelta = 32;
 static const short PartModels = 64;
 static const short PartItem = 128;
 static const short PartWindow = 256;
 static const short PartDoor = 512;
 static const short Sounds = 1024;
 static const short PartCondition = 2048;
 static const short UpdateCarProperties = 4096;
 static const short Authorization = 16384;
 static const short AllPartFlags = 19440;
 }

 public static class Vector2ObjectPool extends ObjectPool<Vector2> {
 int allocated = 0;

 Vector2ObjectPool() {
 super(Vector2::new);
 }

 Vector2 makeObject() {
 this->allocated++;
 return (Vector2)super.makeObject();
 }
 }

 public static class Vector2fObjectPool extends ObjectPool<Vector2f> {
 int allocated = 0;

 Vector2fObjectPool() {
 super(Vector2f::new);
 }

 Vector2f makeObject() {
 this->allocated++;
 return (Vector2f)super.makeObject();
 }
 }

 public static class Vector3fObjectPool extends ObjectPool<Vector3f> {
 int allocated = 0;

 Vector3fObjectPool() {
 super(Vector3f::new);
 }

 Vector3f makeObject() {
 this->allocated++;
 return (Vector3f)super.makeObject();
 }
 }

 private static class VehicleImpulse {
 static ArrayDeque<BaseVehicle.VehicleImpulse> pool = std::make_unique<ArrayDeque<>>();
 const Vector3f impulse = new Vector3f();
 const Vector3f rel_pos = new Vector3f();
 bool enable = false;

 static BaseVehicle.VehicleImpulse alloc() {
 return pool.empty() ? new BaseVehicle.VehicleImpulse() : pool.pop();
 }

 void release() {
 pool.push(this);
 }
 }

 public static class WheelInfo {
 float steering;
 float rotation;
 float skidInfo;
 float suspensionLength;
 }

 public static enum engineStateTypes {
 Idle,
 Starting,
 RetryingStarting,
 StartingSuccess,
 StartingFailed,
 Running,
 Stalling,
 ShutingDown,
 StartingFailedNoPower;

 public static BaseVehicle.engineStateTypes[] Values = values();
 }
}
} // namespace vehicles
} // namespace zombie
