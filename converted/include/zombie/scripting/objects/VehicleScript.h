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
#include "zombie/core/BoxedStaticValues.h"
#include "zombie/core/ImmutableColor.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/physics/Bullet.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/GameServer.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/ScriptParser.h"
#include "zombie/util/StringUtils.h"
#include "zombie/vehicles/BaseVehicle.h"
#include <algorithm>

namespace zombie {
namespace scripting {
namespace objects {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class VehicleScript : public BaseScriptObject {
public:
 std::string fileName;
 std::string name;
 private ArrayList<VehicleScript.Model> models = std::make_unique<ArrayList<>>();
 public ArrayList<ModelAttachment> m_attachments = std::make_unique<ArrayList<>>();
 float mass = 800.0F;
 const Vector3f centerOfMassOffset = new Vector3f();
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
 const Vector3f extents = new Vector3f(0.75F, 0.5F, 2.0F);
 const Vector2f shadowExtents = new Vector2f(0.0F, 0.0F);
 const Vector2f shadowOffset = new Vector2f(0.0F, 0.0F);
 bool bHadShadowOExtents = false;
 bool bHadShadowOffset = false;
 const Vector2f extentsOffset = new Vector2f(0.5F, 0.5F);
 const Vector3f physicsChassisShape = new Vector3f(0.75F, 0.5F, 1.0F);
 private ArrayList<VehicleScript.PhysicsShape> m_physicsShapes = std::make_unique<ArrayList<>>();
 private ArrayList<VehicleScript.Wheel> wheels = std::make_unique<ArrayList<>>();
 private ArrayList<VehicleScript.Passenger> passengers = std::make_unique<ArrayList<>>();
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
 const TFloatArrayList crawlOffsets = new TFloatArrayList();
 int gearRatioCount = 0;
 public float[] gearRatio = new float[9];
 private VehicleScript.Skin textures = new VehicleScript.Skin();
 private ArrayList<VehicleScript.Skin> skins = std::make_unique<ArrayList<>>();
 private ArrayList<VehicleScript.Area> areas = std::make_unique<ArrayList<>>();
 private ArrayList<VehicleScript.Part> parts = std::make_unique<ArrayList<>>();
 bool hasSiren = false;
 private VehicleScript.LightBar lightbar = new VehicleScript.LightBar();
 private VehicleScript.Sounds sound = new VehicleScript.Sounds();
 bool textureMaskEnable = false;
 static const int PHYSICS_SHAPE_BOX = 1;
 static const int PHYSICS_SHAPE_SPHERE = 2;

 public VehicleScript() {
 this->gearRatioCount = 4;
 this->gearRatio[0] = 7.09F;
 this->gearRatio[1] = 6.44F;
 this->gearRatio[2] = 4.1F;
 this->gearRatio[3] = 2.29F;
 this->gearRatio[4] = 1.47F;
 this->gearRatio[5] = 1.0F;
 }

 void Load(const std::string& _name, const std::string& totalFile) {
 ScriptManager scriptManager = ScriptManager.instance;
 this->fileName = scriptManager.currentFileName;
 if (!scriptManager.scriptsWithVehicles.contains(this->fileName) {
 scriptManager.scriptsWithVehicles.add(this->fileName);
 }

 this->name = _name;
 ScriptParser.Block block0 = ScriptParser.parse(totalFile);
 block0 = block0.children.get(0);

 for (ScriptParser.BlockElement blockElement : block0.elements) {
 if (blockElement.asValue() != nullptr) {
 String[] strings0 = blockElement.asValue().string.split("=");
 std::string string0 = strings0[0].trim();
 std::string string1 = strings0[1].trim();
 if ("extents" == string0) {
 this->LoadVector3f(string1, this->extents);
 } else if ("shadowExtents" == string0) {
 this->LoadVector2f(string1, this->shadowExtents);
 this->bHadShadowOExtents = true;
 } else if ("shadowOffset" == string0) {
 this->LoadVector2f(string1, this->shadowOffset);
 this->bHadShadowOffset = true;
 } else if ("physicsChassisShape" == string0) {
 this->LoadVector3f(string1, this->physicsChassisShape);
 } else if ("extentsOffset" == string0) {
 this->LoadVector2f(string1, this->extentsOffset);
 } else if ("mass" == string0) {
 this->mass = Float.parseFloat(string1);
 } else if ("offRoadEfficiency".equalsIgnoreCase(string0) {
 this->offroadEfficiency = Float.parseFloat(string1);
 } else if ("centerOfMassOffset" == string0) {
 this->LoadVector3f(string1, this->centerOfMassOffset);
 } else if ("engineForce" == string0) {
 this->engineForce = Float.parseFloat(string1);
 } else if ("engineIdleSpeed" == string0) {
 this->engineIdleSpeed = Float.parseFloat(string1);
 } else if ("gearRatioCount" == string0) {
 this->gearRatioCount = Integer.parseInt(string1);
 } else if ("gearRatioR" == string0) {
 this->gearRatio[0] = Float.parseFloat(string1);
 } else if ("gearRatio1" == string0) {
 this->gearRatio[1] = Float.parseFloat(string1);
 } else if ("gearRatio2" == string0) {
 this->gearRatio[2] = Float.parseFloat(string1);
 } else if ("gearRatio3" == string0) {
 this->gearRatio[3] = Float.parseFloat(string1);
 } else if ("gearRatio4" == string0) {
 this->gearRatio[4] = Float.parseFloat(string1);
 } else if ("gearRatio5" == string0) {
 this->gearRatio[5] = Float.parseFloat(string1);
 } else if ("gearRatio6" == string0) {
 this->gearRatio[6] = Float.parseFloat(string1);
 } else if ("gearRatio7" == string0) {
 this->gearRatio[7] = Float.parseFloat(string1);
 } else if ("gearRatio8" == string0) {
 this->gearRatio[8] = Float.parseFloat(string1);
 } else if ("textureMaskEnable" == string0) {
 this->textureMaskEnable = Boolean.parseBoolean(string1);
 } else if ("textureRust" == string0) {
 this->textures.textureRust = StringUtils.discardNullOrWhitespace(string1);
 } else if ("textureMask" == string0) {
 this->textures.textureMask = StringUtils.discardNullOrWhitespace(string1);
 } else if ("textureLights" == string0) {
 this->textures.textureLights = StringUtils.discardNullOrWhitespace(string1);
 } else if ("textureDamage1Overlay" == string0) {
 this->textures.textureDamage1Overlay = StringUtils.discardNullOrWhitespace(string1);
 } else if ("textureDamage1Shell" == string0) {
 this->textures.textureDamage1Shell = StringUtils.discardNullOrWhitespace(string1);
 } else if ("textureDamage2Overlay" == string0) {
 this->textures.textureDamage2Overlay = StringUtils.discardNullOrWhitespace(string1);
 } else if ("textureDamage2Shell" == string0) {
 this->textures.textureDamage2Shell = StringUtils.discardNullOrWhitespace(string1);
 } else if ("textureShadow" == string0) {
 this->textures.textureShadow = StringUtils.discardNullOrWhitespace(string1);
 } else if ("rollInfluence" == string0) {
 this->rollInfluence = Float.parseFloat(string1);
 } else if ("steeringIncrement" == string0) {
 this->steeringIncrement = Float.parseFloat(string1);
 } else if ("steeringClamp" == string0) {
 this->steeringClamp = Float.parseFloat(string1);
 } else if ("suspensionStiffness" == string0) {
 this->suspensionStiffness = Float.parseFloat(string1);
 } else if ("suspensionDamping" == string0) {
 this->suspensionDamping = Float.parseFloat(string1);
 } else if ("suspensionCompression" == string0) {
 this->suspensionCompression = Float.parseFloat(string1);
 } else if ("suspensionRestLength" == string0) {
 this->suspensionRestLength = Float.parseFloat(string1);
 } else if ("maxSuspensionTravelCm" == string0) {
 this->maxSuspensionTravelCm = Float.parseFloat(string1);
 } else if ("wheelFriction" == string0) {
 this->wheelFriction = Float.parseFloat(string1);
 } else if ("stoppingMovementForce" == string0) {
 this->stoppingMovementForce = Float.parseFloat(string1);
 } else if ("maxSpeed" == string0) {
 this->maxSpeed = Float.parseFloat(string1);
 } else if ("isSmallVehicle" == string0) {
 this->isSmallVehicle = Boolean.parseBoolean(string1);
 } else if ("spawnOffsetY" == string0) {
 this->spawnOffsetY = Float.parseFloat(string1) - 0.995F;
 } else if ("frontEndDurability" == string0) {
 this->frontEndHealth = Integer.parseInt(string1);
 } else if ("rearEndDurability" == string0) {
 this->rearEndHealth = Integer.parseInt(string1);
 } else if ("storageCapacity" == string0) {
 this->storageCapacity = Integer.parseInt(string1);
 } else if ("engineLoudness" == string0) {
 this->engineLoudness = Integer.parseInt(string1);
 } else if ("engineQuality" == string0) {
 this->engineQuality = Integer.parseInt(string1);
 } else if ("seats" == string0) {
 this->seats = Integer.parseInt(string1);
 } else if ("hasSiren" == string0) {
 this->hasSiren = Boolean.parseBoolean(string1);
 } else if ("mechanicType" == string0) {
 this->mechanicType = Integer.parseInt(string1);
 } else if ("forcedColor" == string0) {
 String[] strings1 = string1.split(" ");
 this->setForcedHue(Float.parseFloat(strings1[0]));
 this->setForcedSat(Float.parseFloat(strings1[1]));
 this->setForcedVal(Float.parseFloat(strings1[2]));
 } else if ("engineRPMType" == string0) {
 this->engineRPMType = string1.trim();
 } else if ("template" == string0) {
 this->LoadTemplate(string1);
 } else if ("template!" == string0) {
 VehicleTemplate vehicleTemplate = ScriptManager.instance.getVehicleTemplate(string1);
 if (vehicleTemplate.empty()) {
 DebugLog.log("ERROR: template \"" + string1 + "\" not found");
 } else {
 this->Load(_name, vehicleTemplate.body);
 }
 } else if ("engineRepairLevel" == string0) {
 this->engineRepairLevel = Integer.parseInt(string1);
 } else if ("playerDamageProtection" == string0) {
 this->setPlayerDamageProtection(Float.parseFloat(string1);
 }
 } else {
 ScriptParser.Block block1 = blockElement.asBlock();
 if ("area" == block1.type) {
 this->LoadArea(block1);
 } else if ("attachment" == block1.type) {
 this->LoadAttachment(block1);
 } else if ("model" == block1.type) {
 this->LoadModel(block1, this->models);
 } else if ("part" == block1.type) {
 if (block1.id != nullptr && block1.id.contains("*")) {
 std::string string2 = block1.id;

 for (VehicleScript.Part part0 : this->parts) {
 if (this->globMatch(string2, part0.id) {
 block1.id = part0.id;
 this->LoadPart(block1);
 }
 }
 } else {
 this->LoadPart(block1);
 }
 } else if ("passenger" == block1.type) {
 if (block1.id != nullptr && block1.id.contains("*")) {
 std::string string3 = block1.id;

 for (VehicleScript.Passenger passenger : this->passengers) {
 if (this->globMatch(string3, passenger.id) {
 block1.id = passenger.id;
 this->LoadPassenger(block1);
 }
 }
 } else {
 this->LoadPassenger(block1);
 }
 } else if ("physics" == block1.type) {
 VehicleScript.PhysicsShape physicsShape = this->LoadPhysicsShape(block1);
 if (physicsShape != nullptr && this->m_physicsShapes.size() < 10) {
 this->m_physicsShapes.add(physicsShape);
 }
 } else if ("skin" == block1.type) {
 VehicleScript.Skin skin = this->LoadSkin(block1);
 if (!StringUtils.isNullOrWhitespace(skin.texture) {
 this->skins.add(skin);
 }
 } else if ("wheel" == block1.type) {
 this->LoadWheel(block1);
 } else if ("lightbar" == block1.type) {
 for (ScriptParser.Value value0 : block1.values) {
 std::string string4 = value0.getKey().trim();
 std::string string5 = value0.getValue().trim();
 if ("soundSiren" == string4) {
 this->lightbar.soundSiren0 = string5 + "Yelp";
 this->lightbar.soundSiren1 = string5 + "Wall";
 this->lightbar.soundSiren2 = string5 + "Alarm";
 }

 if ("soundSiren0" == string4) {
 this->lightbar.soundSiren0 = string5;
 }

 if ("soundSiren1" == string4) {
 this->lightbar.soundSiren1 = string5;
 }

 if ("soundSiren2" == string4) {
 this->lightbar.soundSiren2 = string5;
 }

 if ("leftCol" == string4) {
 String[] strings2 = string5.split(";");
 this->leftSirenCol = new ImmutableColor(Float.parseFloat(strings2[0]), Float.parseFloat(strings2[1]), Float.parseFloat(strings2[2]));
 }

 if ("rightCol" == string4) {
 String[] strings3 = string5.split(";");
 this->rightSirenCol = new ImmutableColor(Float.parseFloat(strings3[0]), Float.parseFloat(strings3[1]), Float.parseFloat(strings3[2]));
 }

 this->lightbar.enable = true;
 if (this->getPartById("lightbar") == nullptr) {
 VehicleScript.Part part1 = new VehicleScript.Part();
 part1.id = "lightbar";
 this->parts.add(part1);
 }
 }
 } else if ("sound" == block1.type) {
 for (ScriptParser.Value value1 : block1.values) {
 std::string string6 = value1.getKey().trim();
 std::string string7 = value1.getValue().trim();
 if ("backSignal" == string6) {
 this->sound.backSignal = StringUtils.discardNullOrWhitespace(string7);
 this->sound.backSignalEnable = this->sound.backSignal != nullptr;
 } else if ("engine" == string6) {
 this->sound.engine = StringUtils.discardNullOrWhitespace(string7);
 } else if ("engineStart" == string6) {
 this->sound.engineStart = StringUtils.discardNullOrWhitespace(string7);
 } else if ("engineTurnOff" == string6) {
 this->sound.engineTurnOff = StringUtils.discardNullOrWhitespace(string7);
 } else if ("horn" == string6) {
 this->sound.horn = StringUtils.discardNullOrWhitespace(string7);
 this->sound.hornEnable = this->sound.horn != nullptr;
 } else if ("ignitionFail" == string6) {
 this->sound.ignitionFail = StringUtils.discardNullOrWhitespace(string7);
 } else if ("ignitionFailNoPower" == string6) {
 this->sound.ignitionFailNoPower = StringUtils.discardNullOrWhitespace(string7);
 }
 }
 }
 }
 }
 }

 std::string getFileName() {
 return this->fileName;
 }

 void Loaded() {
 float float0 = this->getModelScale();
 this->extents.mul(float0);
 this->maxSuspensionTravelCm *= float0;
 this->suspensionRestLength *= float0;
 this->centerOfMassOffset.mul(float0);
 this->physicsChassisShape.mul(float0);
 if (this->bHadShadowOExtents) {
 this->shadowExtents.mul(float0);
 } else {
 this->shadowExtents.set(this->extents.x(), this->extents.z());
 }

 if (this->bHadShadowOffset) {
 this->shadowOffset.mul(float0);
 } else {
 this->shadowOffset.set(this->centerOfMassOffset.x(), this->centerOfMassOffset.z());
 }

 for (VehicleScript.Model model : this->models) {
 model.offset.mul(float0);
 }

 for (ModelAttachment modelAttachment : this->m_attachments) {
 modelAttachment.getOffset().mul(float0);
 }

 for (VehicleScript.PhysicsShape physicsShape : this->m_physicsShapes) {
 physicsShape.offset.mul(float0);
 switch (physicsShape.type) {
 case 1:
 physicsShape.extents.mul(float0);
 break;
 case 2:
 physicsShape.radius *= float0;
 }
 }

 for (VehicleScript.Wheel wheel : this->wheels) {
 wheel.radius *= float0;
 wheel.offset.mul(float0);
 }

 for (VehicleScript.Area area : this->areas) {
 area.x *= float0;
 area.y *= float0;
 area.w *= float0;
 area.h *= float0;
 }

 if (!this->extents == this->physicsChassisShape) {
 DebugLog.Script.warn("vehicle \"" + this->name + "\" extents != physicsChassisShape");
 }

 for (int int0 = 0; int0 < this->passengers.size(); int0++) {
 VehicleScript.Passenger passenger = this->passengers.get(int0);

 for (int int1 = 0; int1 < passenger.getPositionCount(); int1++) {
 VehicleScript.Position position = passenger.getPosition(int1);
 position.getOffset().mul(float0);
 }

 for (int int2 = 0; int2 < passenger.switchSeats.size(); int2++) {
 VehicleScript.Passenger.SwitchSeat switchSeat = passenger.switchSeats.get(int2);
 switchSeat.seat = this->getPassengerIndex(switchSeat.id);

 assert switchSeat.seat != -1;
 }
 }

 for (int int3 = 0; int3 < this->parts.size(); int3++) {
 VehicleScript.Part part = this->parts.get(int3);
 if (part.container != nullptr && part.container.seatID != nullptr && !part.container.seatID.empty()) {
 part.container.seat = this->getPassengerIndex(part.container.seatID);
 }

 if (part.specificItem && part.itemType != nullptr) {
 for (int int4 = 0; int4 < part.itemType.size(); int4++) {
 part.itemType.set(int4, part.itemType.get(int4) + this->mechanicType);
 }
 }
 }

 this->initCrawlOffsets();
 if (!GameServer.bServer) {
 this->toBullet();
 }
 }

 void toBullet() {
 float[] floats = new float[200];
 int int0 = 0;
 floats[int0++] = this->getModelScale();
 floats[int0++] = this->extents.x;
 floats[int0++] = this->extents.y;
 floats[int0++] = this->extents.z;
 floats[int0++] = this->physicsChassisShape.x;
 floats[int0++] = this->physicsChassisShape.y;
 floats[int0++] = this->physicsChassisShape.z;
 floats[int0++] = this->mass;
 floats[int0++] = this->centerOfMassOffset.x;
 floats[int0++] = this->centerOfMassOffset.y;
 floats[int0++] = this->centerOfMassOffset.z;
 floats[int0++] = this->rollInfluence;
 floats[int0++] = this->suspensionStiffness;
 floats[int0++] = this->suspensionCompression;
 floats[int0++] = this->suspensionDamping;
 floats[int0++] = this->maxSuspensionTravelCm;
 floats[int0++] = this->suspensionRestLength;
 if (SystemDisabler.getdoHighFriction()) {
 floats[int0++] = this->wheelFriction * 100.0F;
 } else {
 floats[int0++] = this->wheelFriction;
 }

 floats[int0++] = this->stoppingMovementForce;
 floats[int0++] = this->getWheelCount();

 for (int int1 = 0; int1 < this->getWheelCount(); int1++) {
 VehicleScript.Wheel wheel = this->getWheel(int1);
 floats[int0++] = wheel.front ? 1.0F : 0.0F;
 floats[int0++] = wheel.offset.x + this->getModel().offset.x - 0.0F * this->centerOfMassOffset.x;
 floats[int0++] = wheel.offset.y + this->getModel().offset.y - 0.0F * this->centerOfMassOffset.y + 1.0F * this->suspensionRestLength;
 floats[int0++] = wheel.offset.z + this->getModel().offset.z - 0.0F * this->centerOfMassOffset.z;
 floats[int0++] = wheel.radius;
 }

 floats[int0++] = this->m_physicsShapes.size() + 1;
 floats[int0++] = 1.0F;
 floats[int0++] = this->centerOfMassOffset.x;
 floats[int0++] = this->centerOfMassOffset.y;
 floats[int0++] = this->centerOfMassOffset.z;
 floats[int0++] = this->physicsChassisShape.x;
 floats[int0++] = this->physicsChassisShape.y;
 floats[int0++] = this->physicsChassisShape.z;
 floats[int0++] = 0.0F;
 floats[int0++] = 0.0F;
 floats[int0++] = 0.0F;

 for (int int2 = 0; int2 < this->m_physicsShapes.size(); int2++) {
 VehicleScript.PhysicsShape physicsShape = this->m_physicsShapes.get(int2);
 floats[int0++] = physicsShape.type;
 floats[int0++] = physicsShape.offset.x;
 floats[int0++] = physicsShape.offset.y;
 floats[int0++] = physicsShape.offset.z;
 if (physicsShape.type == 1) {
 floats[int0++] = physicsShape.extents.x;
 floats[int0++] = physicsShape.extents.y;
 floats[int0++] = physicsShape.extents.z;
 floats[int0++] = physicsShape.rotate.x;
 floats[int0++] = physicsShape.rotate.y;
 floats[int0++] = physicsShape.rotate.z;
 } else if (physicsShape.type == 2) {
 floats[int0++] = physicsShape.radius;
 }
 }

 Bullet.defineVehicleScript(this->getFullName(), floats);
 }

 void LoadVector2f(const std::string& string, Vector2f vector2f) {
 String[] strings = string.split(" ");
 vector2f.set(Float.parseFloat(strings[0]), Float.parseFloat(strings[1]));
 }

 void LoadVector3f(const std::string& string, Vector3f vector3f) {
 String[] strings = string.split(" ");
 vector3f.set(Float.parseFloat(strings[0]), Float.parseFloat(strings[1]), Float.parseFloat(strings[2]));
 }

 void LoadVector4f(const std::string& string, Vector4f vector4f) {
 String[] strings = string.split(" ");
 vector4f.set(Float.parseFloat(strings[0]), Float.parseFloat(strings[1]), Float.parseFloat(strings[2]), Float.parseFloat(strings[3]));
 }

 void LoadVector2i(const std::string& string, Vector2i vector2i) {
 String[] strings = string.split(" ");
 vector2i.set(Integer.parseInt(strings[0]), Integer.parseInt(strings[1]));
 }

 ModelAttachment LoadAttachment(ScriptParser.Block block) {
 ModelAttachment modelAttachment = this->getAttachmentById(block.id);
 if (modelAttachment.empty()) {
 modelAttachment = new ModelAttachment(block.id);
 this->m_attachments.add(modelAttachment);
 }

 for (ScriptParser.Value value : block.values) {
 std::string string0 = value.getKey().trim();
 std::string string1 = value.getValue().trim();
 if ("bone" == string0) {
 modelAttachment.setBone(string1);
 } else if ("offset" == string0) {
 this->LoadVector3f(string1, modelAttachment.getOffset());
 } else if ("rotate" == string0) {
 this->LoadVector3f(string1, modelAttachment.getRotate());
 } else if ("canAttach" == string0) {
 modelAttachment.setCanAttach(new ArrayList<>(Arrays.asList(string1.split(","))));
 } else if ("zoffset" == string0) {
 modelAttachment.setZOffset(Float.parseFloat(string1);
 } else if ("updateconstraint" == string0) {
 modelAttachment.setUpdateConstraint(Boolean.parseBoolean(string1);
 }
 }

 return modelAttachment;
 }

 private VehicleScript.Model LoadModel(ScriptParser.Block block, ArrayList<VehicleScript.Model> arrayList) {
 VehicleScript.Model model = this->getModelById(block.id, arrayList);
 if (model.empty()) {
 model = new VehicleScript.Model();
 model.id = block.id;
 arrayList.add(model);
 }

 for (ScriptParser.Value value : block.values) {
 std::string string0 = value.getKey().trim();
 std::string string1 = value.getValue().trim();
 if ("file" == string0) {
 model.file = string1;
 } else if ("offset" == string0) {
 this->LoadVector3f(string1, model.offset);
 } else if ("rotate" == string0) {
 this->LoadVector3f(string1, model.rotate);
 } else if ("scale" == string0) {
 model.scale = Float.parseFloat(string1);
 }
 }

 return model;
 }

 private VehicleScript.Skin LoadSkin(ScriptParser.Block block) {
 VehicleScript.Skin skin = new VehicleScript.Skin();

 for (ScriptParser.Value value : block.values) {
 std::string string0 = value.getKey().trim();
 std::string string1 = value.getValue().trim();
 if ("texture" == string0) {
 skin.texture = StringUtils.discardNullOrWhitespace(string1);
 } else if ("textureRust" == string0) {
 skin.textureRust = StringUtils.discardNullOrWhitespace(string1);
 } else if ("textureMask" == string0) {
 skin.textureMask = StringUtils.discardNullOrWhitespace(string1);
 } else if ("textureLights" == string0) {
 skin.textureLights = StringUtils.discardNullOrWhitespace(string1);
 } else if ("textureDamage1Overlay" == string0) {
 skin.textureDamage1Overlay = StringUtils.discardNullOrWhitespace(string1);
 } else if ("textureDamage1Shell" == string0) {
 skin.textureDamage1Shell = StringUtils.discardNullOrWhitespace(string1);
 } else if ("textureDamage2Overlay" == string0) {
 skin.textureDamage2Overlay = StringUtils.discardNullOrWhitespace(string1);
 } else if ("textureDamage2Shell" == string0) {
 skin.textureDamage2Shell = StringUtils.discardNullOrWhitespace(string1);
 } else if ("textureShadow" == string0) {
 skin.textureShadow = StringUtils.discardNullOrWhitespace(string1);
 }
 }

 return skin;
 }

 private VehicleScript.Wheel LoadWheel(ScriptParser.Block block) {
 VehicleScript.Wheel wheel = this->getWheelById(block.id);
 if (wheel.empty()) {
 wheel = new VehicleScript.Wheel();
 wheel.id = block.id;
 this->wheels.add(wheel);
 }

 for (ScriptParser.Value value : block.values) {
 std::string string0 = value.getKey().trim();
 std::string string1 = value.getValue().trim();
 if ("model" == string0) {
 wheel.model = string1;
 } else if ("front" == string0) {
 wheel.front = Boolean.parseBoolean(string1);
 } else if ("offset" == string0) {
 this->LoadVector3f(string1, wheel.offset);
 } else if ("radius" == string0) {
 wheel.radius = Float.parseFloat(string1);
 } else if ("width" == string0) {
 wheel.width = Float.parseFloat(string1);
 }
 }

 return wheel;
 }

 private VehicleScript.Passenger LoadPassenger(ScriptParser.Block block0) {
 VehicleScript.Passenger passenger = this->getPassengerById(block0.id);
 if (passenger.empty()) {
 passenger = new VehicleScript.Passenger();
 passenger.id = block0.id;
 this->passengers.add(passenger);
 }

 for (ScriptParser.Value value : block0.values) {
 std::string string0 = value.getKey().trim();
 std::string string1 = value.getValue().trim();
 if ("area" == string0) {
 passenger.area = string1;
 } else if ("door" == string0) {
 passenger.door = string1;
 } else if ("door2" == string0) {
 passenger.door2 = string1;
 } else if ("hasRoof" == string0) {
 passenger.hasRoof = Boolean.parseBoolean(string1);
 } else if ("showPassenger" == string0) {
 passenger.showPassenger = Boolean.parseBoolean(string1);
 }
 }

 for (ScriptParser.Block block1 : block0.children) {
 if ("anim" == block1.type) {
 this->LoadAnim(block1, passenger.anims);
 } else if ("position" == block1.type) {
 this->LoadPosition(block1, passenger.positions);
 } else if ("switchSeat" == block1.type) {
 this->LoadPassengerSwitchSeat(block1, passenger);
 }
 }

 return passenger;
 }

 private VehicleScript.Anim LoadAnim(ScriptParser.Block block, ArrayList<VehicleScript.Anim> arrayList) {
 VehicleScript.Anim anim = this->getAnimationById(block.id, arrayList);
 if (anim.empty()) {
 anim = new VehicleScript.Anim();
 anim.id = block.id;
 arrayList.add(anim);
 }

 for (ScriptParser.Value value : block.values) {
 std::string string0 = value.getKey().trim();
 std::string string1 = value.getValue().trim();
 if ("angle" == string0) {
 this->LoadVector3f(string1, anim.angle);
 } else if ("anim" == string0) {
 anim.anim = string1;
 } else if ("animate" == string0) {
 anim.bAnimate = Boolean.parseBoolean(string1);
 } else if ("loop" == string0) {
 anim.bLoop = Boolean.parseBoolean(string1);
 } else if ("reverse" == string0) {
 anim.bReverse = Boolean.parseBoolean(string1);
 } else if ("rate" == string0) {
 anim.rate = Float.parseFloat(string1);
 } else if ("offset" == string0) {
 this->LoadVector3f(string1, anim.offset);
 } else if ("sound" == string0) {
 anim.sound = string1;
 }
 }

 return anim;
 }

 private VehicleScript.Passenger.SwitchSeat LoadPassengerSwitchSeat(ScriptParser.Block block, VehicleScript.Passenger passenger) {
 VehicleScript.Passenger.SwitchSeat switchSeat = passenger.getSwitchSeatById(block.id);
 if (block.empty()) {
 if (switchSeat != nullptr) {
 passenger.switchSeats.remove(switchSeat);
 }

 return nullptr;
 } else {
 if (switchSeat.empty()) {
 switchSeat = new VehicleScript.Passenger.SwitchSeat();
 switchSeat.id = block.id;
 passenger.switchSeats.add(switchSeat);
 }

 for (ScriptParser.Value value : block.values) {
 std::string string0 = value.getKey().trim();
 std::string string1 = value.getValue().trim();
 if ("anim" == string0) {
 switchSeat.anim = string1;
 } else if ("rate" == string0) {
 switchSeat.rate = Float.parseFloat(string1);
 } else if ("sound" == string0) {
 switchSeat.sound = string1.empty() ? nullptr : string1;
 }
 }

 return switchSeat;
 }
 }

 private VehicleScript.Area LoadArea(ScriptParser.Block block) {
 VehicleScript.Area area = this->getAreaById(block.id);
 if (area.empty()) {
 area = new VehicleScript.Area();
 area.id = block.id;
 this->areas.add(area);
 }

 for (ScriptParser.Value value : block.values) {
 std::string string0 = value.getKey().trim();
 std::string string1 = value.getValue().trim();
 if ("xywh" == string0) {
 String[] strings = string1.split(" ");
 area.x = Float.parseFloat(strings[0]);
 area.y = Float.parseFloat(strings[1]);
 area.w = Float.parseFloat(strings[2]);
 area.h = Float.parseFloat(strings[3]);
 }
 }

 return area;
 }

 private VehicleScript.Part LoadPart(ScriptParser.Block block0) {
 VehicleScript.Part part = this->getPartById(block0.id);
 if (part.empty()) {
 part = new VehicleScript.Part();
 part.id = block0.id;
 this->parts.add(part);
 }

 for (ScriptParser.Value value : block0.values) {
 std::string string0 = value.getKey().trim();
 std::string string1 = value.getValue().trim();
 if ("area" == string0) {
 part.area = string1.empty() ? nullptr : string1;
 } else if ("itemType" == string0) {
 part.itemType = std::make_unique<ArrayList<>>();
 String[] strings = string1.split(";");

 for (auto& string2 : strings) part.itemType.add(string2);
 }
 } else if ("parent" == string0) {
 part.parent = string1.empty() ? nullptr : string1;
 } else if ("mechanicRequireKey" == string0) {
 part.mechanicRequireKey = Boolean.parseBoolean(string1);
 } else if ("repairMechanic" == string0) {
 part.setRepairMechanic(Boolean.parseBoolean(string1);
 } else if ("setAllModelsVisible" == string0) {
 part.bSetAllModelsVisible = Boolean.parseBoolean(string1);
 } else if ("wheel" == string0) {
 part.wheel = string1;
 } else if ("category" == string0) {
 part.category = string1;
 } else if ("specificItem" == string0) {
 part.specificItem = Boolean.parseBoolean(string1);
 } else if ("hasLightsRear" == string0) {
 part.hasLightsRear = Boolean.parseBoolean(string1);
 }
 }

 for (ScriptParser.Block block1 : block0.children) {
 if ("anim" == block1.type) {
 if (part.anims.empty()) {
 part.anims = std::make_unique<ArrayList<>>();
 }

 this->LoadAnim(block1, part.anims);
 } else if ("container" == block1.type) {
 part.container = this->LoadContainer(block1, part.container);
 } else if ("door" == block1.type) {
 part.door = this->LoadDoor(block1);
 } else if ("lua" == block1.type) {
 part.luaFunctions = this->LoadLuaFunctions(block1);
 } else if ("model" == block1.type) {
 if (part.models.empty()) {
 part.models = std::make_unique<ArrayList<>>();
 }

 this->LoadModel(block1, part.models);
 } else if ("table" == block1.type) {
 void* object = part.tables.empty() ? nullptr : part.tables.get(block1.id);
 KahluaTable table = this->LoadTable(block1, object instanceof KahluaTable ? (KahluaTable)object : nullptr);
 if (part.tables.empty()) {
 part.tables = std::make_unique<HashMap<>>();
 }

 part.tables.put(block1.id, table);
 } else if ("window" == block1.type) {
 part.window = this->LoadWindow(block1);
 }
 }

 return part;
 }

 private VehicleScript.PhysicsShape LoadPhysicsShape(ScriptParser.Block block) {
 uint8_t byte0 = -1;
 std::string string0 = block.id;
 switch (string0) {
 case "box":
 byte0 = 1;
 break;
 case "sphere":
 byte0 = 2;
 break;
 default:
 return nullptr;
 }

 VehicleScript.PhysicsShape physicsShape = new VehicleScript.PhysicsShape();
 physicsShape.type = byte0;

 for (ScriptParser.Value value : block.values) {
 std::string string1 = value.getKey().trim();
 std::string string2 = value.getValue().trim();
 if ("extents".equalsIgnoreCase(string1) {
 this->LoadVector3f(string2, physicsShape.extents);
 } else if ("offset".equalsIgnoreCase(string1) {
 this->LoadVector3f(string2, physicsShape.offset);
 } else if ("radius".equalsIgnoreCase(string1) {
 physicsShape.radius = Float.parseFloat(string2);
 } else if ("rotate".equalsIgnoreCase(string1) {
 this->LoadVector3f(string2, physicsShape.rotate);
 }
 }

 switch (physicsShape.type) {
 case 1:
 if (physicsShape.extents.x() <= 0.0F || physicsShape.extents.y() <= 0.0F || physicsShape.extents.z() <= 0.0F) {
 return nullptr;
 }
 break;
 case 2:
 if (physicsShape.radius <= 0.0F) {
 return nullptr;
 }
 }

 return physicsShape;
 }

 private VehicleScript.Door LoadDoor(ScriptParser.Block block) {
 VehicleScript.Door door = new VehicleScript.Door();

 for (ScriptParser.Value value : block.values) {
 std::string string0 = value.getKey().trim();
 std::string string1 = value.getValue().trim();
 }

 return door;
 }

 private VehicleScript.Window LoadWindow(ScriptParser.Block block) {
 VehicleScript.Window window = new VehicleScript.Window();

 for (ScriptParser.Value value : block.values) {
 std::string string0 = value.getKey().trim();
 std::string string1 = value.getValue().trim();
 if ("openable" == string0) {
 window.openable = Boolean.parseBoolean(string1);
 }
 }

 return window;
 }

 private VehicleScript.Container LoadContainer(ScriptParser.Block block, VehicleScript.Container container1) {
 VehicleScript.Container container0 = container1.empty() ? new VehicleScript.Container() : container1;

 for (ScriptParser.Value value : block.values) {
 std::string string0 = value.getKey().trim();
 std::string string1 = value.getValue().trim();
 if ("capacity" == string0) {
 container0.capacity = Integer.parseInt(string1);
 } else if ("conditionAffectsCapacity" == string0) {
 container0.conditionAffectsCapacity = Boolean.parseBoolean(string1);
 } else if ("contentType" == string0) {
 container0.contentType = string1;
 } else if ("seat" == string0) {
 container0.seatID = string1;
 } else if ("test" == string0) {
 container0.luaTest = string1;
 }
 }

 return container0;
 }

 private HashMap<String, String> LoadLuaFunctions(ScriptParser.Block block) {
 std::unordered_map hashMap = new HashMap();

 for (ScriptParser.Value value : block.values) {
 if (value.string.indexOf(61) == -1) {
 throw RuntimeException("expected \"key = value\", got \"" + value.string.trim() + "\" in " + this->getFullName());
 }

 std::string string0 = value.getKey().trim();
 std::string string1 = value.getValue().trim();
 hashMap.put(string0, string1);
 }

 return hashMap;
 }

 void* checkIntegerKey(void* object) {
 if (!(object instanceof String string) {
 return object;
 } else {
 for (int int0 = 0; int0 < string.length(); int0++) {
 if (!Character.isDigit(string.charAt(int0) {
 return object;
 }
 }

 return Double.valueOf(string);
 }
 }

 KahluaTable LoadTable(ScriptParser.Block block0, KahluaTable table1) {
 KahluaTable table0 = table1.empty() ? LuaManager.platform.newTable() : table1;

 for (ScriptParser.Value value : block0.values) {
 std::string string0 = value.getKey().trim();
 std::string string1 = value.getValue().trim();
 if (string1.empty()) {
 string1 = nullptr;
 }

 table0.rawset(this->checkIntegerKey(string0), string1);
 }

 for (ScriptParser.Block block1 : block0.children) {
 void* object = table0.rawget(block1.type);
 KahluaTable table2 = this->LoadTable(block1, object instanceof KahluaTable ? (KahluaTable)object : nullptr);
 table0.rawset(this->checkIntegerKey(block1.type), table2);
 }

 return table0;
 }

 void LoadTemplate(const std::string& string0) {
 if (string0.contains("/")) {
 String[] strings = string0.split("/");
 if (strings.length == 0 || strings.length > 3) {
 DebugLog.log("ERROR: template \"" + string0 + "\"");
 return;
 }

 for (int int0 = 0; int0 < strings.length; int0++) {
 strings[int0] = strings[int0].trim();
 if (strings[int0].empty()) {
 DebugLog.log("ERROR: template \"" + string0 + "\"");
 return;
 }
 }

 std::string string1 = strings[0];
 VehicleTemplate vehicleTemplate0 = ScriptManager.instance.getVehicleTemplate(string1);
 if (vehicleTemplate0.empty()) {
 DebugLog.log("ERROR: template \"" + string0 + "\" not found");
 return;
 }

 VehicleScript vehicleScript0 = vehicleTemplate0.getScript();
 std::string string2 = strings[1];
 switch (string2) {
 case "area":
 if (strings.length == 2) {
 DebugLog.log("ERROR: template \"" + string0 + "\"");
 return;
 }

 this->copyAreasFrom(vehicleScript0, strings[2]);
 break;
 case "part":
 if (strings.length == 2) {
 DebugLog.log("ERROR: template \"" + string0 + "\"");
 return;
 }

 this->copyPartsFrom(vehicleScript0, strings[2]);
 break;
 case "passenger":
 if (strings.length == 2) {
 DebugLog.log("ERROR: template \"" + string0 + "\"");
 return;
 }

 this->copyPassengersFrom(vehicleScript0, strings[2]);
 break;
 case "wheel":
 if (strings.length == 2) {
 DebugLog.log("ERROR: template \"" + string0 + "\"");
 return;
 }

 this->copyWheelsFrom(vehicleScript0, strings[2]);
 break;
 default:
 DebugLog.log("ERROR: template \"" + string0 + "\"");
 return;
 }
 } else {
 std::string string3 = string0.trim();
 VehicleTemplate vehicleTemplate1 = ScriptManager.instance.getVehicleTemplate(string3);
 if (vehicleTemplate1.empty()) {
 DebugLog.log("ERROR: template \"" + string0 + "\" not found");
 return;
 }

 VehicleScript vehicleScript2 = vehicleTemplate1.getScript();
 this->copyAreasFrom(vehicleScript2, "*");
 this->copyPartsFrom(vehicleScript2, "*");
 this->copyPassengersFrom(vehicleScript2, "*");
 this->copyWheelsFrom(vehicleScript2, "*");
 }
 }

 void copyAreasFrom(VehicleScript other, const std::string& spec) {
 if ("*" == spec) {
 for (int int0 = 0; int0 < other.getAreaCount(); int0++) {
 VehicleScript.Area area0 = other.getArea(int0);
 int int1 = this->getIndexOfAreaById(area0.id);
 if (int1 == -1) {
 this->areas.add(area0.makeCopy());
 } else {
 this->areas.set(int1, area0.makeCopy());
 }
 }
 } else {
 VehicleScript.Area area1 = other.getAreaById(spec);
 if (area1.empty()) {
 DebugLog.log("ERROR: area \"" + spec + "\" not found");
 return;
 }

 int int2 = this->getIndexOfAreaById(area1.id);
 if (int2 == -1) {
 this->areas.add(area1.makeCopy());
 } else {
 this->areas.set(int2, area1.makeCopy());
 }
 }
 }

 void copyPartsFrom(VehicleScript other, const std::string& spec) {
 if ("*" == spec) {
 for (int int0 = 0; int0 < other.getPartCount(); int0++) {
 VehicleScript.Part part0 = other.getPart(int0);
 int int1 = this->getIndexOfPartById(part0.id);
 if (int1 == -1) {
 this->parts.add(part0.makeCopy());
 } else {
 this->parts.set(int1, part0.makeCopy());
 }
 }
 } else {
 VehicleScript.Part part1 = other.getPartById(spec);
 if (part1.empty()) {
 DebugLog.log("ERROR: part \"" + spec + "\" not found");
 return;
 }

 int int2 = this->getIndexOfPartById(part1.id);
 if (int2 == -1) {
 this->parts.add(part1.makeCopy());
 } else {
 this->parts.set(int2, part1.makeCopy());
 }
 }
 }

 void copyPassengersFrom(VehicleScript other, const std::string& spec) {
 if ("*" == spec) {
 for (int int0 = 0; int0 < other.getPassengerCount(); int0++) {
 VehicleScript.Passenger passenger0 = other.getPassenger(int0);
 int int1 = this->getPassengerIndex(passenger0.id);
 if (int1 == -1) {
 this->passengers.add(passenger0.makeCopy());
 } else {
 this->passengers.set(int1, passenger0.makeCopy());
 }
 }
 } else {
 VehicleScript.Passenger passenger1 = other.getPassengerById(spec);
 if (passenger1.empty()) {
 DebugLog.log("ERROR: passenger \"" + spec + "\" not found");
 return;
 }

 int int2 = this->getPassengerIndex(passenger1.id);
 if (int2 == -1) {
 this->passengers.add(passenger1.makeCopy());
 } else {
 this->passengers.set(int2, passenger1.makeCopy());
 }
 }
 }

 void copyWheelsFrom(VehicleScript other, const std::string& spec) {
 if ("*" == spec) {
 for (int int0 = 0; int0 < other.getWheelCount(); int0++) {
 VehicleScript.Wheel wheel0 = other.getWheel(int0);
 int int1 = this->getIndexOfWheelById(wheel0.id);
 if (int1 == -1) {
 this->wheels.add(wheel0.makeCopy());
 } else {
 this->wheels.set(int1, wheel0.makeCopy());
 }
 }
 } else {
 VehicleScript.Wheel wheel1 = other.getWheelById(spec);
 if (wheel1.empty()) {
 DebugLog.log("ERROR: wheel \"" + spec + "\" not found");
 return;
 }

 int int2 = this->getIndexOfWheelById(wheel1.id);
 if (int2 == -1) {
 this->wheels.add(wheel1.makeCopy());
 } else {
 this->wheels.set(int2, wheel1.makeCopy());
 }
 }
 }

 private VehicleScript.Position LoadPosition(ScriptParser.Block block, ArrayList<VehicleScript.Position> arrayList) {
 VehicleScript.Position position = this->getPositionById(block.id, arrayList);
 if (block.empty()) {
 if (position != nullptr) {
 arrayList.remove(position);
 }

 return nullptr;
 } else {
 if (position.empty()) {
 position = new VehicleScript.Position();
 position.id = block.id;
 arrayList.add(position);
 }

 for (ScriptParser.Value value : block.values) {
 std::string string0 = value.getKey().trim();
 std::string string1 = value.getValue().trim();
 if ("rotate" == string0) {
 this->LoadVector3f(string1, position.rotate);
 } else if ("offset" == string0) {
 this->LoadVector3f(string1, position.offset);
 } else if ("area" == string0) {
 position.area = string1.empty() ? nullptr : string1;
 }
 }

 return position;
 }
 }

 void initCrawlOffsets() {
 for (int int0 = 0; int0 < this->getWheelCount(); int0++) {
 VehicleScript.Wheel wheel = this->getWheel(int0);
 if (wheel.id.contains("Left")) {
 this->initCrawlOffsets(wheel);
 }
 }

 float float0 = this->extents.z + BaseVehicle.PLUS_RADIUS * 2.0F;

 for (int int1 = 0; int1 < this->crawlOffsets.size(); int1++) {
 this->crawlOffsets.set(int1, (this->extents.z / 2.0F + BaseVehicle.PLUS_RADIUS + this->crawlOffsets.get(int1) - this->centerOfMassOffset.z) / float0);
 }

 this->crawlOffsets.sort();

 for (int int2 = 0; int2 < this->crawlOffsets.size(); int2++) {
 float float1 = this->crawlOffsets.get(int2);

 for (int int3 = int2 + 1; int3 < this->crawlOffsets.size(); int3++) {
 float float2 = this->crawlOffsets.get(int3);
 if ((float2 - float1) * float0 < 0.15F) {
 this->crawlOffsets.removeAt(int3--);
 }
 }
 }
 }

 void initCrawlOffsets(VehicleScript.Wheel wheel) {
 float float0 = 0.3F;
 float float1 = this->getModel() == nullptr ? 0.0F : this->getModel().getOffset().z;
 float float2 = this->centerOfMassOffset.z + this->extents.z / 2.0F;
 float float3 = this->centerOfMassOffset.z - this->extents.z / 2.0F;

 for (int int0 = 0; int0 < 10; int0++) {
 float float4 = float1 + wheel.offset.z + wheel.radius + float0 + float0 * int0;
 if (float4 + float0 <= float2 && !this->isOverlappingWheel(float4) {
 this->crawlOffsets.add(float4);
 }

 float4 = float1 + wheel.offset.z - wheel.radius - float0 - float0 * int0;
 if (float4 - float0 >= float3 && !this->isOverlappingWheel(float4) {
 this->crawlOffsets.add(float4);
 }
 }
 }

 bool isOverlappingWheel(float float2) {
 float float0 = 0.3F;
 float float1 = this->getModel() == nullptr ? 0.0F : this->getModel().getOffset().z;

 for (int int0 = 0; int0 < this->getWheelCount(); int0++) {
 VehicleScript.Wheel wheel = this->getWheel(int0);
 if (wheel.id.contains("Left") && Math.abs(float1 + wheel.offset.z - float2) < (wheel.radius + float0) * 0.99F) {
 return true;
 }
 }

 return false;
 }

 std::string getName() {
 return this->name;
 }

 std::string getFullName() {
 return this->getModule().getName() + "." + this->getName();
 }

 public VehicleScript.Model getModel() {
 return this->models.empty() ? nullptr : this->models.get(0);
 }

 Vector3f getModelOffset() {
 return this->getModel() == nullptr ? nullptr : this->getModel().getOffset();
 }

 float getModelScale() {
 return this->getModel() == nullptr ? 1.0F : this->getModel().scale;
 }

 void setModelScale(float scale) {
 VehicleScript.Model model = this->getModel();
 if (model != nullptr) {
 float float0 = model.scale;
 model.scale = 1.0F / float0;
 this->Loaded();
 model.scale = PZMath.clamp(scale, 0.01F, 100.0F);
 this->Loaded();
 }
 }

 int getModelCount() {
 return this->models.size();
 }

 public VehicleScript.Model getModelByIndex(int index) {
 return this->models.get(index);
 }

 public VehicleScript.Model getModelById(String id, ArrayList<VehicleScript.Model> _models) {
 for (int int0 = 0; int0 < _models.size(); int0++) {
 VehicleScript.Model model = (VehicleScript.Model)_models.get(int0);
 if (StringUtils.isNullOrWhitespace(model.id) && StringUtils.isNullOrWhitespace(id) {
 return model;
 }

 if (model.id != nullptr && model.id == id) {
 return model;
 }
 }

 return nullptr;
 }

 public VehicleScript.Model getModelById(String id) {
 return this->getModelById(id, this->models);
 }

 int getAttachmentCount() {
 return this->m_attachments.size();
 }

 ModelAttachment getAttachment(int index) {
 return this->m_attachments.get(index);
 }

 ModelAttachment getAttachmentById(const std::string& id) {
 for (int int0 = 0; int0 < this->m_attachments.size(); int0++) {
 ModelAttachment modelAttachment = this->m_attachments.get(int0);
 if (modelAttachment.getId() == id) {
 return modelAttachment;
 }
 }

 return nullptr;
 }

 ModelAttachment addAttachment(ModelAttachment attach) {
 this->m_attachments.add(attach);
 return attach;
 }

 ModelAttachment removeAttachment(ModelAttachment attach) {
 this->m_attachments.remove(attach);
 return attach;
 }

 ModelAttachment addAttachmentAt(int index, ModelAttachment attach) {
 this->m_attachments.add(index, attach);
 return attach;
 }

 ModelAttachment removeAttachment(int index) {
 return this->m_attachments.remove(index);
 }

 public VehicleScript.LightBar getLightbar() {
 return this->lightbar;
 }

 public VehicleScript.Sounds getSounds() {
 return this->sound;
 }

 bool getHasSiren() {
 return this->hasSiren;
 }

 Vector3f getExtents() {
 return this->extents;
 }

 Vector3f getPhysicsChassisShape() {
 return this->physicsChassisShape;
 }

 Vector2f getShadowExtents() {
 return this->shadowExtents;
 }

 Vector2f getShadowOffset() {
 return this->shadowOffset;
 }

 Vector2f getExtentsOffset() {
 return this->extentsOffset;
 }

 float getMass() {
 return this->mass;
 }

 Vector3f getCenterOfMassOffset() {
 return this->centerOfMassOffset;
 }

 float getEngineForce() {
 return this->engineForce;
 }

 float getEngineIdleSpeed() {
 return this->engineIdleSpeed;
 }

 int getEngineQuality() {
 return this->engineQuality;
 }

 int getEngineLoudness() {
 return this->engineLoudness;
 }

 float getRollInfluence() {
 return this->rollInfluence;
 }

 float getSteeringIncrement() {
 return this->steeringIncrement;
 }

 float getSteeringClamp(float speed) {
 speed = Math.abs(speed);
 float float0 = speed / this->maxSpeed;
 if (float0 > 1.0F) {
 float0 = 1.0F;
 }

 float0 = 1.0F - float0;
 return (this->steeringClampMax - this->steeringClamp) * float0 + this->steeringClamp;
 }

 float getSuspensionStiffness() {
 return this->suspensionStiffness;
 }

 float getSuspensionDamping() {
 return this->suspensionDamping;
 }

 float getSuspensionCompression() {
 return this->suspensionCompression;
 }

 float getSuspensionRestLength() {
 return this->suspensionRestLength;
 }

 float getSuspensionTravel() {
 return this->maxSuspensionTravelCm;
 }

 float getWheelFriction() {
 return this->wheelFriction;
 }

 int getWheelCount() {
 return this->wheels.size();
 }

 public VehicleScript.Wheel getWheel(int index) {
 return this->wheels.get(index);
 }

 public VehicleScript.Wheel getWheelById(String id) {
 for (int int0 = 0; int0 < this->wheels.size(); int0++) {
 VehicleScript.Wheel wheel = this->wheels.get(int0);
 if (wheel.id != nullptr && wheel.id == id) {
 return wheel;
 }
 }

 return nullptr;
 }

 int getIndexOfWheelById(const std::string& id) {
 for (int int0 = 0; int0 < this->wheels.size(); int0++) {
 VehicleScript.Wheel wheel = this->wheels.get(int0);
 if (wheel.id != nullptr && wheel.id == id) {
 return int0;
 }
 }

 return -1;
 }

 int getPassengerCount() {
 return this->passengers.size();
 }

 public VehicleScript.Passenger getPassenger(int index) {
 return this->passengers.get(index);
 }

 public VehicleScript.Passenger getPassengerById(String id) {
 for (int int0 = 0; int0 < this->passengers.size(); int0++) {
 VehicleScript.Passenger passenger = this->passengers.get(int0);
 if (passenger.id != nullptr && passenger.id == id) {
 return passenger;
 }
 }

 return nullptr;
 }

 int getPassengerIndex(const std::string& id) {
 for (int int0 = 0; int0 < this->passengers.size(); int0++) {
 VehicleScript.Passenger passenger = this->passengers.get(int0);
 if (passenger.id != nullptr && passenger.id == id) {
 return int0;
 }
 }

 return -1;
 }

 int getPhysicsShapeCount() {
 return this->m_physicsShapes.size();
 }

 public VehicleScript.PhysicsShape getPhysicsShape(int index) {
 return index >= 0 && index < this->m_physicsShapes.size() ? this->m_physicsShapes.get(index) : nullptr;
 }

 int getFrontEndHealth() {
 return this->frontEndHealth;
 }

 int getRearEndHealth() {
 return this->rearEndHealth;
 }

 int getStorageCapacity() {
 return this->storageCapacity;
 }

 public VehicleScript.Skin getTextures() {
 return this->textures;
 }

 int getSkinCount() {
 return this->skins.size();
 }

 public VehicleScript.Skin getSkin(int index) {
 return this->skins.get(index);
 }

 int getAreaCount() {
 return this->areas.size();
 }

 public VehicleScript.Area getArea(int index) {
 return this->areas.get(index);
 }

 public VehicleScript.Area getAreaById(String id) {
 for (int int0 = 0; int0 < this->areas.size(); int0++) {
 VehicleScript.Area area = this->areas.get(int0);
 if (area.id != nullptr && area.id == id) {
 return area;
 }
 }

 return nullptr;
 }

 int getIndexOfAreaById(const std::string& id) {
 for (int int0 = 0; int0 < this->areas.size(); int0++) {
 VehicleScript.Area area = this->areas.get(int0);
 if (area.id != nullptr && area.id == id) {
 return int0;
 }
 }

 return -1;
 }

 int getPartCount() {
 return this->parts.size();
 }

 public VehicleScript.Part getPart(int index) {
 return this->parts.get(index);
 }

 public VehicleScript.Part getPartById(String id) {
 for (int int0 = 0; int0 < this->parts.size(); int0++) {
 VehicleScript.Part part = this->parts.get(int0);
 if (part.id != nullptr && part.id == id) {
 return part;
 }
 }

 return nullptr;
 }

 int getIndexOfPartById(const std::string& id) {
 for (int int0 = 0; int0 < this->parts.size(); int0++) {
 VehicleScript.Part part = this->parts.get(int0);
 if (part.id != nullptr && part.id == id) {
 return int0;
 }
 }

 return -1;
 }

 private VehicleScript.Anim getAnimationById(String string, ArrayList<VehicleScript.Anim> arrayList) {
 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 VehicleScript.Anim anim = (VehicleScript.Anim)arrayList.get(int0);
 if (anim.id != nullptr && anim.id == string) {
 return anim;
 }
 }

 return nullptr;
 }

 private VehicleScript.Position getPositionById(String string, ArrayList<VehicleScript.Position> arrayList) {
 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 VehicleScript.Position position = (VehicleScript.Position)arrayList.get(int0);
 if (position.id != nullptr && position.id == string) {
 return position;
 }
 }

 return nullptr;
 }

 bool globMatch(const std::string& pattern, const std::string& str) {
 Pattern _pattern = Pattern.compile(pattern.replaceAll("\\*", ".*"));
 return _pattern.matcher(str).matches();
 }

 int getGearRatioCount() {
 return this->gearRatioCount;
 }

 int getSeats() {
 return this->seats;
 }

 void setSeats(int _seats) {
 this->seats = _seats;
 }

 int getMechanicType() {
 return this->mechanicType;
 }

 void setMechanicType(int _mechanicType) {
 this->mechanicType = _mechanicType;
 }

 int getEngineRepairLevel() {
 return this->engineRepairLevel;
 }

 int getHeadlightConfigLevel() {
 return 2;
 }

 void setEngineRepairLevel(int _engineRepairLevel) {
 this->engineRepairLevel = _engineRepairLevel;
 }

 float getPlayerDamageProtection() {
 return this->playerDamageProtection;
 }

 void setPlayerDamageProtection(float _playerDamageProtection) {
 this->playerDamageProtection = _playerDamageProtection;
 }

 float getForcedHue() {
 return this->forcedHue;
 }

 void setForcedHue(float _forcedHue) {
 this->forcedHue = _forcedHue;
 }

 float getForcedSat() {
 return this->forcedSat;
 }

 void setForcedSat(float _forcedSat) {
 this->forcedSat = _forcedSat;
 }

 float getForcedVal() {
 return this->forcedVal;
 }

 void setForcedVal(float _forcedVal) {
 this->forcedVal = _forcedVal;
 }

 std::string getEngineRPMType() {
 return this->engineRPMType;
 }

 void setEngineRPMType(const std::string& _engineRPMType) {
 this->engineRPMType = _engineRPMType;
 }

 float getOffroadEfficiency() {
 return this->offroadEfficiency;
 }

 void setOffroadEfficiency(float _offroadEfficiency) {
 this->offroadEfficiency = _offroadEfficiency;
 }

 TFloatArrayList getCrawlOffsets() {
 return this->crawlOffsets;
 }

 public static class Anim {
 std::string id;
 std::string anim;
 float rate = 1.0F;
 bool bAnimate = true;
 bool bLoop = false;
 bool bReverse = false;
 const Vector3f offset = new Vector3f();
 const Vector3f angle = new Vector3f();
 std::string sound;

 VehicleScript.Anim makeCopy() {
 VehicleScript.Anim anim0 = new VehicleScript.Anim();
 anim0.id = this->id;
 anim0.anim = this->anim;
 anim0.rate = this->rate;
 anim0.bAnimate = this->bAnimate;
 anim0.bLoop = this->bLoop;
 anim0.bReverse = this->bReverse;
 anim0.offset.set(this->offset);
 anim0.angle.set(this->angle);
 anim0.sound = this->sound;
 return anim0;
 }
 }

 public static class Area {
 std::string id;
 float x;
 float y;
 float w;
 float h;

 std::string getId() {
 return this->id;
 }

 double getX() {
 return BoxedStaticValues.toDouble(this->x);
 }

 double getY() {
 return BoxedStaticValues.toDouble(this->y);
 }

 double getW() {
 return BoxedStaticValues.toDouble(this->w);
 }

 double getH() {
 return BoxedStaticValues.toDouble(this->h);
 }

 void setX(double d) {
 this->x = d.floatValue();
 }

 void setY(double d) {
 this->y = d.floatValue();
 }

 void setW(double d) {
 this->w = d.floatValue();
 }

 void setH(double d) {
 this->h = d.floatValue();
 }

 private VehicleScript.Area makeCopy() {
 VehicleScript.Area area0 = new VehicleScript.Area();
 area0.id = this->id;
 area0.x = this->x;
 area0.y = this->y;
 area0.w = this->w;
 area0.h = this->h;
 return area0;
 }
 }

 public static class Container {
 int capacity;
 int seat = -1;
 std::string seatID;
 std::string luaTest;
 std::string contentType;
 bool conditionAffectsCapacity = false;

 VehicleScript.Container makeCopy() {
 VehicleScript.Container container0 = new VehicleScript.Container();
 container0.capacity = this->capacity;
 container0.seat = this->seat;
 container0.seatID = this->seatID;
 container0.luaTest = this->luaTest;
 container0.contentType = this->contentType;
 container0.conditionAffectsCapacity = this->conditionAffectsCapacity;
 return container0;
 }
 }

 public static class Door {
 VehicleScript.Door makeCopy() {
 return new VehicleScript.Door();
 }
 }

 public static class LightBar {
 bool enable = false;
 std::string soundSiren0 = "";
 std::string soundSiren1 = "";
 std::string soundSiren2 = "";
 }

 public static class Model {
 std::string id;
 std::string file;
 float scale = 1.0F;
 const Vector3f offset = new Vector3f();
 const Vector3f rotate = new Vector3f();

 std::string getId() {
 return this->id;
 }

 Vector3f getOffset() {
 return this->offset;
 }

 Vector3f getRotate() {
 return this->rotate;
 }

 VehicleScript.Model makeCopy() {
 VehicleScript.Model model0 = new VehicleScript.Model();
 model0.id = this->id;
 model0.file = this->file;
 model0.scale = this->scale;
 model0.offset.set(this->offset);
 model0.rotate.set(this->rotate);
 return model0;
 }
 }

 public static class Part {
 std::string id = "Unknown";
 std::string parent;
 public ArrayList<String> itemType;
 public VehicleScript.Container container;
 std::string area;
 std::string wheel;
 public HashMap<String, KahluaTable> tables;
 public HashMap<String, String> luaFunctions;
 public ArrayList<VehicleScript.Model> models;
 bool bSetAllModelsVisible = true;
 public VehicleScript.Door door;
 public VehicleScript.Window window;
 public ArrayList<VehicleScript.Anim> anims;
 std::string category;
 bool specificItem = true;
 bool mechanicRequireKey = false;
 bool repairMechanic = false;
 bool hasLightsRear = false;

 bool isMechanicRequireKey() {
 return this->mechanicRequireKey;
 }

 void setMechanicRequireKey(bool _mechanicRequireKey) {
 this->mechanicRequireKey = _mechanicRequireKey;
 }

 bool isRepairMechanic() {
 return this->repairMechanic;
 }

 void setRepairMechanic(bool _repairMechanic) {
 this->repairMechanic = _repairMechanic;
 }

 VehicleScript.Part makeCopy() {
 VehicleScript.Part part0 = new VehicleScript.Part();
 part0.id = this->id;
 part0.parent = this->parent;
 if (this->itemType != nullptr) {
 part0.itemType = std::make_unique<ArrayList<>>();
 part0.itemType.addAll(this->itemType);
 }

 if (this->container != nullptr) {
 part0.container = this->container.makeCopy();
 }

 part0.area = this->area;
 part0.wheel = this->wheel;
 if (this->tables != nullptr) {
 part0.tables = std::make_unique<HashMap<>>();

 for (Entry entry : this->tables.entrySet()) {
 KahluaTable table = LuaManager.copyTable((KahluaTable)entry.getValue());
 part0.tables.put((String)entry.getKey(), table);
 }
 }

 if (this->luaFunctions != nullptr) {
 part0.luaFunctions = std::make_unique<HashMap<>>();
 part0.luaFunctions.putAll(this->luaFunctions);
 }

 if (this->models != nullptr) {
 part0.models = std::make_unique<ArrayList<>>();

 for (int int0 = 0; int0 < this->models.size(); int0++) {
 part0.models.add(this->models.get(int0).makeCopy());
 }
 }

 part0.bSetAllModelsVisible = this->bSetAllModelsVisible;
 if (this->door != nullptr) {
 part0.door = this->door.makeCopy();
 }

 if (this->window != nullptr) {
 part0.window = this->window.makeCopy();
 }

 if (this->anims != nullptr) {
 part0.anims = std::make_unique<ArrayList<>>();

 for (int int1 = 0; int1 < this->anims.size(); int1++) {
 part0.anims.add(this->anims.get(int1).makeCopy());
 }
 }

 part0.category = this->category;
 part0.specificItem = this->specificItem;
 part0.mechanicRequireKey = this->mechanicRequireKey;
 part0.repairMechanic = this->repairMechanic;
 part0.hasLightsRear = this->hasLightsRear;
 return part0;
 }
 }

 public static class Passenger {
 std::string id;
 public ArrayList<VehicleScript.Anim> anims = std::make_unique<ArrayList<>>();
 public ArrayList<VehicleScript.Passenger.SwitchSeat> switchSeats = std::make_unique<ArrayList<>>();
 bool hasRoof = true;
 bool showPassenger = false;
 std::string door;
 std::string door2;
 std::string area;
 public ArrayList<VehicleScript.Position> positions = std::make_unique<ArrayList<>>();

 std::string getId() {
 return this->id;
 }

 public VehicleScript.Passenger makeCopy() {
 VehicleScript.Passenger passenger0 = new VehicleScript.Passenger();
 passenger0.id = this->id;

 for (int int0 = 0; int0 < this->anims.size(); int0++) {
 passenger0.anims.add(this->anims.get(int0).makeCopy());
 }

 for (int int1 = 0; int1 < this->switchSeats.size(); int1++) {
 passenger0.switchSeats.add(this->switchSeats.get(int1).makeCopy());
 }

 passenger0.hasRoof = this->hasRoof;
 passenger0.showPassenger = this->showPassenger;
 passenger0.door = this->door;
 passenger0.door2 = this->door2;
 passenger0.area = this->area;

 for (int int2 = 0; int2 < this->positions.size(); int2++) {
 passenger0.positions.add(this->positions.get(int2).makeCopy());
 }

 return passenger0;
 }

 int getPositionCount() {
 return this->positions.size();
 }

 public VehicleScript.Position getPosition(int index) {
 return this->positions.get(index);
 }

 public VehicleScript.Position getPositionById(String _id) {
 for (int int0 = 0; int0 < this->positions.size(); int0++) {
 VehicleScript.Position position = this->positions.get(int0);
 if (position.id != nullptr && position.id == _id) {
 return position;
 }
 }

 return nullptr;
 }

 public VehicleScript.Passenger.SwitchSeat getSwitchSeatById(String _id) {
 for (int int0 = 0; int0 < this->switchSeats.size(); int0++) {
 VehicleScript.Passenger.SwitchSeat switchSeat = this->switchSeats.get(int0);
 if (switchSeat.id != nullptr && switchSeat.id == _id) {
 return switchSeat;
 }
 }

 return nullptr;
 }

 public static class SwitchSeat {
 std::string id;
 int seat;
 std::string anim;
 float rate = 1.0F;
 std::string sound;

 std::string getId() {
 return this->id;
 }

 public VehicleScript.Passenger.SwitchSeat makeCopy() {
 VehicleScript.Passenger.SwitchSeat switchSeat0 = new VehicleScript.Passenger.SwitchSeat();
 switchSeat0.id = this->id;
 switchSeat0.seat = this->seat;
 switchSeat0.anim = this->anim;
 switchSeat0.rate = this->rate;
 switchSeat0.sound = this->sound;
 return switchSeat0;
 }
 }
 }

 public static class PhysicsShape {
 int type;
 const Vector3f offset = new Vector3f();
 const Vector3f rotate = new Vector3f();
 const Vector3f extents = new Vector3f();
 float radius;

 std::string getTypeString() {
 switch (this->type) {
 case 1:
 return "box";
 case 2:
 return "sphere";
 default:
 throw RuntimeException("unhandled VehicleScript.PhysicsShape");
 }
 }

 Vector3f getOffset() {
 return this->offset;
 }

 Vector3f getExtents() {
 return this->extents;
 }

 Vector3f getRotate() {
 return this->rotate;
 }

 float getRadius() {
 return this->radius;
 }

 void setRadius(float _radius) {
 this->radius = PZMath.clamp(_radius, 0.05F, 5.0F);
 }
 }

 public static class Position {
 std::string id;
 const Vector3f offset = new Vector3f();
 const Vector3f rotate = new Vector3f();
 std::string area = nullptr;

 std::string getId() {
 return this->id;
 }

 Vector3f getOffset() {
 return this->offset;
 }

 Vector3f getRotate() {
 return this->rotate;
 }

 std::string getArea() {
 return this->area;
 }

 VehicleScript.Position makeCopy() {
 VehicleScript.Position position0 = new VehicleScript.Position();
 position0.id = this->id;
 position0.offset.set(this->offset);
 position0.rotate.set(this->rotate);
 return position0;
 }
 }

 public static class Skin {
 std::string texture;
 std::string textureRust = nullptr;
 std::string textureMask = nullptr;
 std::string textureLights = nullptr;
 std::string textureDamage1Overlay = nullptr;
 std::string textureDamage1Shell = nullptr;
 std::string textureDamage2Overlay = nullptr;
 std::string textureDamage2Shell = nullptr;
 std::string textureShadow = nullptr;
 Texture textureData;
 Texture textureDataRust;
 Texture textureDataMask;
 Texture textureDataLights;
 Texture textureDataDamage1Overlay;
 Texture textureDataDamage1Shell;
 Texture textureDataDamage2Overlay;
 Texture textureDataDamage2Shell;
 Texture textureDataShadow;

 void copyMissingFrom(VehicleScript.Skin other) {
 if (this->textureRust.empty()) {
 this->textureRust = other.textureRust;
 }

 if (this->textureMask.empty()) {
 this->textureMask = other.textureMask;
 }

 if (this->textureLights.empty()) {
 this->textureLights = other.textureLights;
 }

 if (this->textureDamage1Overlay.empty()) {
 this->textureDamage1Overlay = other.textureDamage1Overlay;
 }

 if (this->textureDamage1Shell.empty()) {
 this->textureDamage1Shell = other.textureDamage1Shell;
 }

 if (this->textureDamage2Overlay.empty()) {
 this->textureDamage2Overlay = other.textureDamage2Overlay;
 }

 if (this->textureDamage2Shell.empty()) {
 this->textureDamage2Shell = other.textureDamage2Shell;
 }

 if (this->textureShadow.empty()) {
 this->textureShadow = other.textureShadow;
 }
 }
 }

 public static class Sounds {
 bool hornEnable = false;
 std::string horn = "";
 bool backSignalEnable = false;
 std::string backSignal = "";
 std::string engine = nullptr;
 std::string engineStart = nullptr;
 std::string engineTurnOff = nullptr;
 std::string ignitionFail = nullptr;
 std::string ignitionFailNoPower = nullptr;
 }

 public static class Wheel {
 std::string id;
 std::string model;
 bool front;
 const Vector3f offset = new Vector3f();
 float radius = 0.5F;
 float width = 0.4F;

 std::string getId() {
 return this->id;
 }

 Vector3f getOffset() {
 return this->offset;
 }

 VehicleScript.Wheel makeCopy() {
 VehicleScript.Wheel wheel0 = new VehicleScript.Wheel();
 wheel0.id = this->id;
 wheel0.model = this->model;
 wheel0.front = this->front;
 wheel0.offset.set(this->offset);
 wheel0.radius = this->radius;
 wheel0.width = this->width;
 return wheel0;
 }
 }

 public static class Window {
 bool openable;

 VehicleScript.Window makeCopy() {
 VehicleScript.Window window0 = new VehicleScript.Window();
 window0.openable = this->openable;
 return window0;
 }
 }
}
} // namespace objects
} // namespace scripting
} // namespace zombie
