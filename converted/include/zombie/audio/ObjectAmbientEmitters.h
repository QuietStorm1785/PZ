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
#include "zombie/GameSounds.h"
#include "zombie/audio/parameters/ParameterCurrentZone.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/properties/PropertyContainer.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/debug/LineDrawer.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoChunkMap.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/Vector2.h"
#include "zombie/iso/objects/IsoDoor.h"
#include "zombie/iso/objects/IsoWindow.h"
#include "zombie/network/GameServer.h"
#include "zombie/popman/ObjectPool.h"
#include "zombie/util/Type.h"
#include "zombie/util/list/PZArrayUtil.h"
#include <algorithm>

namespace zombie {
namespace audio {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ObjectAmbientEmitters {
public:
 private HashMap<String, ObjectAmbientEmitters.PowerPolicy> powerPolicyMap = std::make_unique<HashMap<>>();
 static ObjectAmbientEmitters instance = nullptr;
 static const Vector2 tempVector2 = new Vector2();
 private HashMap<IsoObject, ObjectAmbientEmitters.ObjectWithDistance> m_added = std::make_unique<HashMap<>>();
 private ObjectPool<ObjectAmbientEmitters.ObjectWithDistance> m_objectPool = new ObjectPool<>(ObjectAmbientEmitters.ObjectWithDistance::new);
 private ArrayList<ObjectAmbientEmitters.ObjectWithDistance> m_objects = std::make_unique<ArrayList<>>();
 private ObjectAmbientEmitters.Slot[] m_slots;
 private Comparator<ObjectAmbientEmitters.ObjectWithDistance> comp = new Comparator<ObjectAmbientEmitters.ObjectWithDistance>() {
 int compare(ObjectAmbientEmitters.ObjectWithDistance objectWithDistance1, ObjectAmbientEmitters.ObjectWithDistance objectWithDistance0) {
 return Float.compare(objectWithDistance1.distSq, objectWithDistance0.distSq);
 }
 };

 static ObjectAmbientEmitters getInstance() {
 if (instance == nullptr) {
 instance = std::make_unique<ObjectAmbientEmitters>();
 }

 return instance;
 }

 private ObjectAmbientEmitters() {
 uint8_t byte0 = 16;
 this->m_slots = PZArrayUtil.newInstance(ObjectAmbientEmitters.Slot.class, byte0, ObjectAmbientEmitters.Slot::new);
 this->powerPolicyMap.put("FactoryMachineAmbiance", ObjectAmbientEmitters.PowerPolicy.InteriorHydro);
 this->powerPolicyMap.put("HotdogMachineAmbiance", ObjectAmbientEmitters.PowerPolicy.InteriorHydro);
 this->powerPolicyMap.put("PayPhoneAmbiance", ObjectAmbientEmitters.PowerPolicy.ExteriorOK);
 this->powerPolicyMap.put("StreetLightAmbiance", ObjectAmbientEmitters.PowerPolicy.ExteriorOK);
 this->powerPolicyMap.put("NeonLightAmbiance", ObjectAmbientEmitters.PowerPolicy.ExteriorOK);
 this->powerPolicyMap.put("NeonSignAmbiance", ObjectAmbientEmitters.PowerPolicy.ExteriorOK);
 this->powerPolicyMap.put("JukeboxAmbiance", ObjectAmbientEmitters.PowerPolicy.InteriorHydro);
 this->powerPolicyMap.put("ControlStationAmbiance", ObjectAmbientEmitters.PowerPolicy.InteriorHydro);
 this->powerPolicyMap.put("ClockAmbiance", ObjectAmbientEmitters.PowerPolicy.InteriorHydro);
 this->powerPolicyMap.put("GasPumpAmbiance", ObjectAmbientEmitters.PowerPolicy.ExteriorOK);
 this->powerPolicyMap.put("LightBulbAmbiance", ObjectAmbientEmitters.PowerPolicy.InteriorHydro);
 this->powerPolicyMap.put("ArcadeMachineAmbiance", ObjectAmbientEmitters.PowerPolicy.InteriorHydro);
 }

 void addObject(IsoObject object, ObjectAmbientEmitters.PerObjectLogic perObjectLogic) {
 if (!GameServer.bServer) {
 if (!this->m_added.containsKey(object) {
 bool boolean0 = false;

 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 IsoPlayer player = IsoPlayer.players[int0];
 if (player != nullptr && object.getObjectIndex() != -1) {
 uint8_t byte0 = 15;
 if (perObjectLogic instanceof ObjectAmbientEmitters.DoorLogic || perObjectLogic instanceof ObjectAmbientEmitters.WindowLogic) {
 byte0 = 10;
 }

 if ((
 object.square.z == PZMath.fastfloor(player.getZ())
 || !(perObjectLogic instanceof ObjectAmbientEmitters.DoorLogic)
 && !(perObjectLogic instanceof ObjectAmbientEmitters.WindowLogic)
 )
 && !(player.DistToSquared(object.square.x + 0.5F, object.square.y + 0.5F) > byte0 * byte0) {
 boolean0 = true;
 break;
 }
 }
 }

 if (boolean0) {
 ObjectAmbientEmitters.ObjectWithDistance objectWithDistance = this->m_objectPool.alloc();
 objectWithDistance.object = object;
 objectWithDistance.logic = perObjectLogic;
 this->m_objects.add(objectWithDistance);
 this->m_added.put(object, objectWithDistance);
 }
 }
 }
 }

 void removeObject(IsoObject object) {
 if (!GameServer.bServer) {
 ObjectAmbientEmitters.ObjectWithDistance objectWithDistance = this->m_added.remove(object);
 if (objectWithDistance != nullptr) {
 this->m_objects.remove(objectWithDistance);
 this->m_objectPool.release(objectWithDistance);
 }
 }
 }

 void update() {
 if (!GameServer.bServer) {
 this->addObjectsFromChunks();

 for (int int0 = 0; int0 < this->m_slots.length; int0++) {
 this->m_slots[int0].playing = false;
 }

 if (this->m_objects.empty()) {
 this->stopNotPlaying();
 } else {
 for (int int1 = 0; int1 < this->m_objects.size(); int1++) {
 ObjectAmbientEmitters.ObjectWithDistance objectWithDistance = this->m_objects.get(int1);
 IsoObject object0 = objectWithDistance.object;
 ObjectAmbientEmitters.PerObjectLogic perObjectLogic0 = this->m_objects.get(int1).logic;
 if (!this->shouldPlay(object0, perObjectLogic0) {
 this->m_added.remove(object0);
 this->m_objects.remove(int1--);
 this->m_objectPool.release(objectWithDistance);
 } else {
 object0.getFacingPosition(tempVector2);
 objectWithDistance.distSq = this->getClosestListener(tempVector2.x, tempVector2.y, object0.square.z);
 }
 }

 this->m_objects.sort(this->comp);
 int int2 = Math.min(this->m_objects.size(), this->m_slots.length);

 for (int int3 = 0; int3 < int2; int3++) {
 IsoObject object1 = this->m_objects.get(int3).object;
 ObjectAmbientEmitters.PerObjectLogic perObjectLogic1 = this->m_objects.get(int3).logic;
 if (this->shouldPlay(object1, perObjectLogic1) {
 int int4 = this->getExistingSlot(object1);
 if (int4 != -1) {
 this->m_slots[int4].playSound(object1, perObjectLogic1);
 }
 }
 }

 for (int int5 = 0; int5 < int2; int5++) {
 IsoObject object2 = this->m_objects.get(int5).object;
 ObjectAmbientEmitters.PerObjectLogic perObjectLogic2 = this->m_objects.get(int5).logic;
 if (this->shouldPlay(object2, perObjectLogic2) {
 int int6 = this->getExistingSlot(object2);
 if (int6 == -1) {
 int6 = this->getFreeSlot();
 if (this->m_slots[int6].object != nullptr) {
 this->m_slots[int6].stopPlaying();
 this->m_slots[int6].object = nullptr;
 }

 this->m_slots[int6].playSound(object2, perObjectLogic2);
 }
 }
 }

 this->stopNotPlaying();
 this->m_added.clear();
 this->m_objectPool.release(this->m_objects);
 this->m_objects.clear();
 }
 }
 }

 void addObjectsFromChunks() {
 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 IsoChunkMap chunkMap = IsoWorld.instance.CurrentCell.ChunkMap[int0];
 if (!chunkMap.ignore) {
 int int1 = IsoChunkMap.ChunkGridWidth / 2;
 int int2 = IsoChunkMap.ChunkGridWidth / 2;

 for (int int3 = -1; int3 <= 1; int3++) {
 for (int int4 = -1; int4 <= 1; int4++) {
 IsoChunk chunk = chunkMap.getChunk(int1 + int4, int2 + int3);
 if (chunk != nullptr) {
 for (IsoObject object : chunk.m_objectEmitterData.m_objects.keySet()) {
 this->addObject(object, chunk.m_objectEmitterData.m_objects.get(object);
 }
 }
 }
 }
 }
 }
 }

 float getClosestListener(float float5, float float6, float float7) {
 float float0 = Float.MAX_VALUE;

 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 IsoPlayer player = IsoPlayer.players[int0];
 if (player != nullptr && player.getCurrentSquare() != nullptr) {
 float float1 = player.getX();
 float float2 = player.getY();
 float float3 = player.getZ();
 float float4 = IsoUtils.DistanceToSquared(float1, float2, float3 * 3.0F, float5, float6, float7 * 3.0F);
 if (player.Traits.HardOfHearing.isSet()) {
 float4 *= 4.5F;
 }

 if (float4 < float0) {
 float0 = float4;
 }
 }
 }

 return float0;
 }

 bool shouldPlay(IsoObject object, ObjectAmbientEmitters.PerObjectLogic perObjectLogic) {
 if (object == nullptr) {
 return false;
 } else {
 return object.getObjectIndex() == -1 ? false : perObjectLogic.shouldPlaySound();
 }
 }

 int getExistingSlot(IsoObject object) {
 for (int int0 = 0; int0 < this->m_slots.length; int0++) {
 if (this->m_slots[int0].object == object) {
 return int0;
 }
 }

 return -1;
 }

 int getFreeSlot() {
 for (int int0 = 0; int0 < this->m_slots.length; int0++) {
 if (!this->m_slots[int0].playing) {
 return int0;
 }
 }

 return -1;
 }

 void stopNotPlaying() {
 for (int int0 = 0; int0 < this->m_slots.length; int0++) {
 ObjectAmbientEmitters.Slot slot = this->m_slots[int0];
 if (!slot.playing) {
 slot.stopPlaying();
 slot.object = nullptr;
 }
 }
 }

 void render() {
 if (DebugOptions.instance.ObjectAmbientEmitterRender.getValue()) {
 IsoChunkMap chunkMap = IsoWorld.instance.CurrentCell.ChunkMap[IsoCamera.frameState.playerIndex];
 if (!chunkMap.ignore) {
 int int0 = IsoChunkMap.ChunkGridWidth / 2;
 int int1 = IsoChunkMap.ChunkGridWidth / 2;

 for (int int2 = -1; int2 <= 1; int2++) {
 for (int int3 = -1; int3 <= 1; int3++) {
 IsoChunk chunk = chunkMap.getChunk(int0 + int3, int1 + int2);
 if (chunk != nullptr) {
 for (IsoObject object0 : chunk.m_objectEmitterData.m_objects.keySet()) {
 if (object0.square.z == (int)IsoCamera.frameState.CamCharacterZ) {
 object0.getFacingPosition(tempVector2);
 float float0 = tempVector2.x;
 float float1 = tempVector2.y;
 float float2 = object0.square.z;
 LineDrawer.addLine(
 float0 - 0.45F, float1 - 0.45F, float2, float0 + 0.45F, float1 + 0.45F, float2, 0.5F, 0.5F, 0.5F, nullptr, false
 );
 }
 }
 }
 }
 }
 }

 for (int int4 = 0; int4 < this->m_slots.length; int4++) {
 ObjectAmbientEmitters.Slot slot = this->m_slots[int4];
 if (slot.playing) {
 IsoObject object1 = slot.object;
 object1.getFacingPosition(tempVector2);
 float float3 = tempVector2.x;
 float float4 = tempVector2.y;
 float float5 = object1.square.z;
 LineDrawer.addLine(float3 - 0.45F, float4 - 0.45F, float5, float3 + 0.45F, float4 + 0.45F, float5, 0.0F, 0.0F, 1.0F, nullptr, false);
 }
 }
 }
 }

 static void Reset() {
 if (instance != nullptr) {
 for (int int0 = 0; int0 < instance.m_slots.length; int0++) {
 instance.m_slots[int0].stopPlaying();
 instance.m_slots[int0].object = nullptr;
 instance.m_slots[int0].playing = false;
 }
 }
 }

 public static class AmbientSoundLogic extends ObjectAmbientEmitters.PerObjectLogic {
 ObjectAmbientEmitters.PowerPolicy powerPolicy = ObjectAmbientEmitters.PowerPolicy.NotRequired;
 bool bHasGeneratorParameter = false;

 public ObjectAmbientEmitters.PerObjectLogic init(IsoObject object) {
 super.init(object);
 std::string string = this->getSoundName();
 this->powerPolicy = ObjectAmbientEmitters.getInstance().powerPolicyMap.getOrDefault(string, ObjectAmbientEmitters.PowerPolicy.NotRequired);
 if (this->powerPolicy != ObjectAmbientEmitters.PowerPolicy.NotRequired) {
 GameSound gameSound = GameSounds.getSound(string);
 this->bHasGeneratorParameter = gameSound != nullptr && gameSound.numClipsUsingParameter("Generator") > 0;
 }

 return this;
 }

 bool shouldPlaySound() {
 if (this->powerPolicy == ObjectAmbientEmitters.PowerPolicy.InteriorHydro) {
 bool boolean0 = this->object.square.haveElectricity() || IsoWorld.instance.isHydroPowerOn() && this->object.square.getRoom() != nullptr;
 if (!boolean0) {
 return false;
 }
 }

 if (this->powerPolicy == ObjectAmbientEmitters.PowerPolicy.ExteriorOK) {
 bool boolean1 = this->object.square.haveElectricity() || IsoWorld.instance.isHydroPowerOn();
 if (!boolean1) {
 return false;
 }
 }

 if (this->powerPolicy != ObjectAmbientEmitters.PowerPolicy.NotRequired && !IsoWorld.instance.isHydroPowerOn() && !this->bHasGeneratorParameter) {
 return false;
 } else {
 PropertyContainer propertyContainer = this->object.getProperties();
 return propertyContainer != nullptr && propertyContainer.Is("AmbientSound");
 }
 }

 std::string getSoundName() {
 return this->object.getProperties().Val("AmbientSound");
 }

 void startPlaying(BaseSoundEmitter var1, long var2) {
 }

 void stopPlaying(BaseSoundEmitter var1, long var2) {
 this->parameterValue1 = Float.NaN;
 }

 void checkParameters(BaseSoundEmitter baseSoundEmitter, long long0) {
 if (this->powerPolicy != ObjectAmbientEmitters.PowerPolicy.NotRequired) {
 this->setParameterValue1(baseSoundEmitter, long0, "Generator", IsoWorld.instance.isHydroPowerOn() ? 0.0F : 1.0F);
 }
 }
 }

 public static class ChunkData {
 HashMap<IsoObject, ObjectAmbientEmitters.PerObjectLogic> m_objects = std::make_unique<HashMap<>>();

 bool hasObject(IsoObject object) {
 return this->m_objects.containsKey(object);
 }

 void addObject(IsoObject object, ObjectAmbientEmitters.PerObjectLogic logic) {
 if (!this->m_objects.containsKey(object) {
 this->m_objects.put(object, logic);
 }
 }

 void removeObject(IsoObject object) {
 this->m_objects.remove(object);
 }

 void reset() {
 this->m_objects.clear();
 }
 }

 public static class DoorLogic extends ObjectAmbientEmitters.PerObjectLogic {
 bool shouldPlaySound() {
 return true;
 }

 std::string getSoundName() {
 return "DoorAmbiance";
 }

 void startPlaying(BaseSoundEmitter var1, long var2) {
 }

 void stopPlaying(BaseSoundEmitter var1, long var2) {
 this->parameterValue1 = Float.NaN;
 }

 void checkParameters(BaseSoundEmitter baseSoundEmitter, long long0) {
 IsoDoor door = Type.tryCastTo(this->object, IsoDoor.class);
 float float0 = door.IsOpen() ? 1.0F : 0.0F;
 this->setParameterValue1(baseSoundEmitter, long0, "DoorWindowOpen", float0);
 }
 }

 public static class FridgeHumLogic extends ObjectAmbientEmitters.PerObjectLogic {
 bool shouldPlaySound() {
 ItemContainer container = this->object.getContainerByEitherType("fridge", "freezer");
 return container != nullptr && container.isPowered();
 }

 std::string getSoundName() {
 return "FridgeHum";
 }

 void startPlaying(BaseSoundEmitter var1, long var2) {
 }

 void stopPlaying(BaseSoundEmitter var1, long var2) {
 this->parameterValue1 = Float.NaN;
 }

 void checkParameters(BaseSoundEmitter baseSoundEmitter, long long0) {
 this->setParameterValue1(baseSoundEmitter, long0, "Generator", IsoWorld.instance.isHydroPowerOn() ? 0.0F : 1.0F);
 }
 }

 static class ObjectWithDistance {
 IsoObject object;
 ObjectAmbientEmitters.PerObjectLogic logic;
 float distSq;
 }

 public static class PerObjectLogic {
 IsoObject object;
 float parameterValue1 = Float.NaN;

 public ObjectAmbientEmitters.PerObjectLogic init(IsoObject _object) {
 this->object = _object;
 return this;
 }

 void setParameterValue1(BaseSoundEmitter baseSoundEmitter, long long0, const std::string& string, float float0) {
 if (float0 != this->parameterValue1) {
 this->parameterValue1 = float0;
 FMOD_STUDIO_PARAMETER_DESCRIPTION fmod_studio_parameter_description = FMODManager.instance.getParameterDescription(string);
 baseSoundEmitter.setParameterValue(long0, fmod_studio_parameter_description, float0);
 }
 }

 void setParameterValue1(
 BaseSoundEmitter baseSoundEmitter, long long0, FMOD_STUDIO_PARAMETER_DESCRIPTION fmod_studio_parameter_description, float float0
 ) {
 if (float0 != this->parameterValue1) {
 this->parameterValue1 = float0;
 baseSoundEmitter.setParameterValue(long0, fmod_studio_parameter_description, float0);
 }
 }

 public boolean shouldPlaySound();

 public String getSoundName();

 public void startPlaying(BaseSoundEmitter emitter, long instance);

 public void stopPlaying(BaseSoundEmitter emitter, long instance);

 public void checkParameters(BaseSoundEmitter emitter, long instance);
 }

 static enum PowerPolicy {
 NotRequired,
 InteriorHydro,
 ExteriorOK;
 }

 static class Slot {
 IsoObject object = nullptr;
 ObjectAmbientEmitters.PerObjectLogic logic = nullptr;
 BaseSoundEmitter emitter = nullptr;
 long instance = 0L;
 bool playing = false;

 void playSound(IsoObject objectx, ObjectAmbientEmitters.PerObjectLogic perObjectLogic) {
 if (this->emitter == nullptr) {
 this->emitter = (BaseSoundEmitter)(Core.SoundDisabled ? std::make_unique<DummySoundEmitter>() : std::make_unique<FMODSoundEmitter>());
 }

 objectx.getFacingPosition(ObjectAmbientEmitters.tempVector2);
 this->emitter.setPos(ObjectAmbientEmitters.tempVector2.getX(), ObjectAmbientEmitters.tempVector2.getY(), objectx.square.z);
 this->object = objectx;
 this->logic = perObjectLogic;
 std::string string = perObjectLogic.getSoundName();
 if (!this->emitter.isPlaying(string) {
 this->emitter.stopAll();
 FMODSoundEmitter fMODSoundEmitter = Type.tryCastTo(this->emitter, FMODSoundEmitter.class);
 if (fMODSoundEmitter != nullptr) {
 fMODSoundEmitter.clearParameters();
 }

 this->instance = this->emitter.playSoundImpl(string, (IsoObject)nullptr);
 perObjectLogic.startPlaying(this->emitter, this->instance);
 }

 perObjectLogic.checkParameters(this->emitter, this->instance);
 this->playing = true;
 this->emitter.tick();
 }

 void stopPlaying() {
 if (this->emitter != nullptr && this->instance != 0L) {
 this->logic.stopPlaying(this->emitter, this->instance);
 if (this->emitter.hasSustainPoints(this->instance) {
 this->emitter.triggerCue(this->instance);
 this->instance = 0L;
 } else {
 this->emitter.stopAll();
 this->instance = 0L;
 }
 }
 }
 }

 public static class TentAmbianceLogic extends ObjectAmbientEmitters.PerObjectLogic {
 bool shouldPlaySound() {
 return this->object.sprite != nullptr
 && this->object.sprite.getName() != nullptr
 && this->object.sprite.getName().startsWith("camping_01")
 && (this->object.sprite.tileSheetIndex == 0 || this->object.sprite.tileSheetIndex == 3);
 }

 std::string getSoundName() {
 return "TentAmbiance";
 }

 void startPlaying(BaseSoundEmitter var1, long var2) {
 }

 void stopPlaying(BaseSoundEmitter var1, long var2) {
 }

 void checkParameters(BaseSoundEmitter var1, long var2) {
 }
 }

 public static class TreeAmbianceLogic extends ObjectAmbientEmitters.PerObjectLogic {
 bool shouldPlaySound() {
 return true;
 }

 std::string getSoundName() {
 return "TreeAmbiance";
 }

 void startPlaying(BaseSoundEmitter baseSoundEmitter, long var2) {
 FMODSoundEmitter fMODSoundEmitter = Type.tryCastTo(baseSoundEmitter, FMODSoundEmitter.class);
 if (fMODSoundEmitter != nullptr) {
 fMODSoundEmitter.addParameter(new ParameterCurrentZone(this->object);
 }

 baseSoundEmitter.playAmbientLoopedImpl("BirdInTree");
 }

 void stopPlaying(BaseSoundEmitter baseSoundEmitter, long var2) {
 baseSoundEmitter.stopOrTriggerSoundByName("BirdInTree");
 }

 void checkParameters(BaseSoundEmitter var1, long var2) {
 }
 }

 public static class WaterDripLogic extends ObjectAmbientEmitters.PerObjectLogic {
 bool shouldPlaySound() {
 return this->object.sprite != nullptr && this->object.sprite.getProperties().Is(IsoFlagType.waterPiped) && this->object.getWaterAmount() > 0.0F;
 }

 std::string getSoundName() {
 return "WaterDrip";
 }

 void startPlaying(BaseSoundEmitter baseSoundEmitter, long long0) {
 if (this->object.sprite != nullptr && this->object.sprite.getProperties().Is("SinkType")) {
 std::string string = this->object.sprite.getProperties().Val("SinkType");

 byte byte0 = switch (string) {
 case "Ceramic" -> 1;
 case "Metal" -> 2;
 default -> 0;
 };
 this->setParameterValue1(baseSoundEmitter, long0, "SinkType", byte0);
 }
 }

 void stopPlaying(BaseSoundEmitter var1, long var2) {
 this->parameterValue1 = Float.NaN;
 }

 void checkParameters(BaseSoundEmitter var1, long var2) {
 }
 }

 public static class WindowLogic extends ObjectAmbientEmitters.PerObjectLogic {
 bool shouldPlaySound() {
 return true;
 }

 std::string getSoundName() {
 return "WindowAmbiance";
 }

 void startPlaying(BaseSoundEmitter var1, long var2) {
 }

 void stopPlaying(BaseSoundEmitter var1, long var2) {
 this->parameterValue1 = Float.NaN;
 }

 void checkParameters(BaseSoundEmitter baseSoundEmitter, long long0) {
 IsoWindow window = Type.tryCastTo(this->object, IsoWindow.class);
 float float0 = !window.IsOpen() && !window.isDestroyed() ? 0.0F : 1.0F;
 this->setParameterValue1(baseSoundEmitter, long0, "DoorWindowOpen", float0);
 }
 }
}
} // namespace audio
} // namespace zombie
