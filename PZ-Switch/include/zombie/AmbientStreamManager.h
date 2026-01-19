#pragma once
#include "fmod/fmod/FMODSoundEmitter.h"
#include "fmod/fmod/FMOD_STUDIO_EVENT_CALLBACK.h"
#include "fmod/fmod/FMOD_STUDIO_EVENT_CALLBACK_TYPE.h"
#include "fmod/javafmod.h"
#include "org/joml/Vector2f.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/audio/parameters/ParameterCameraZoom.h"
#include "zombie/audio/parameters/ParameterClosestWallDistance.h"
#include "zombie/audio/parameters/ParameterFogIntensity.h"
#include "zombie/audio/parameters/ParameterHardOfHearing.h"
#include "zombie/audio/parameters/ParameterInside.h"
#include "zombie/audio/parameters/ParameterMoodlePanic.h"
#include "zombie/audio/parameters/ParameterPowerSupply.h"
#include "zombie/audio/parameters/ParameterRainIntensity.h"
#include "zombie/audio/parameters/ParameterRoomSize.h"
#include "zombie/audio/parameters/ParameterRoomType.h"
#include "zombie/audio/parameters/ParameterSeason.h"
#include "zombie/audio/parameters/ParameterSnowIntensity.h"
#include "zombie/audio/parameters/ParameterStorm.h"
#include "zombie/audio/parameters/ParameterTemperature.h"
#include "zombie/audio/parameters/ParameterTimeOfDay.h"
#include "zombie/audio/parameters/ParameterWaterSupply.h"
#include "zombie/audio/parameters/ParameterWeatherEvent.h"
#include "zombie/audio/parameters/ParameterWindIntensity.h"
#include "zombie/audio/parameters/ParameterZone.h"
#include "zombie/audio/parameters/ParameterZoneWaterSide.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/input/Mouse.h"
#include "zombie/iso/Alarm.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoChunkMap.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMetaCell.h"
#include "zombie/iso/IsoMetaGrid.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/RoomDef.h"
#include "zombie/iso/Vector2.h"
#include "zombie/iso/objects/RainManager.h"
#include "zombie/iso/weather/ClimateManager.h"
#include "zombie/network/GameClient.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class AmbientStreamManager : public BaseAmbientStreamManager {
public:
 static int OneInAmbienceChance = 2500;
 static int MaxAmbientCount = 20;
 static float MaxRange = 1000.0F;
private
 ArrayList<Alarm> alarmList = std::make_unique<ArrayList<>>();
 static BaseAmbientStreamManager instance;
public
 ArrayList<AmbientStreamManager.Ambient> ambient =
 std::make_unique<ArrayList<>>();
public
 ArrayList<AmbientStreamManager.WorldSoundEmitter> worldEmitters =
 std::make_unique<ArrayList<>>();
public
 ArrayDeque<AmbientStreamManager.WorldSoundEmitter> freeEmitters =
 std::make_unique<ArrayDeque<>>();
public
 ArrayList<AmbientStreamManager.AmbientLoop> allAmbient =
 std::make_unique<ArrayList<>>();
public
 ArrayList<AmbientStreamManager.AmbientLoop> nightAmbient =
 std::make_unique<ArrayList<>>();
public
 ArrayList<AmbientStreamManager.AmbientLoop> dayAmbient =
 std::make_unique<ArrayList<>>();
public
 ArrayList<AmbientStreamManager.AmbientLoop> rainAmbient =
 std::make_unique<ArrayList<>>();
public
 ArrayList<AmbientStreamManager.AmbientLoop> indoorAmbient =
 std::make_unique<ArrayList<>>();
public
 ArrayList<AmbientStreamManager.AmbientLoop> outdoorAmbient =
 std::make_unique<ArrayList<>>();
public
 ArrayList<AmbientStreamManager.AmbientLoop> windAmbient =
 std::make_unique<ArrayList<>>();
 bool initialized = false;
 FMODSoundEmitter electricityShutOffEmitter = nullptr;
 long electricityShutOffEvent = 0L;
 int electricityShutOffState = -1;
 const ParameterFogIntensity parameterFogIntensity =
 new ParameterFogIntensity();
 const ParameterRainIntensity parameterRainIntensity =
 new ParameterRainIntensity();
 const ParameterSeason parameterSeason = new ParameterSeason();
 const ParameterSnowIntensity parameterSnowIntensity =
 new ParameterSnowIntensity();
 const ParameterStorm parameterStorm = new ParameterStorm();
 const ParameterTimeOfDay parameterTimeOfDay = new ParameterTimeOfDay();
 const ParameterTemperature parameterTemperature = new ParameterTemperature();
 const ParameterWeatherEvent parameterWeatherEvent =
 new ParameterWeatherEvent();
 const ParameterWindIntensity parameterWindIntensity =
 new ParameterWindIntensity();
 const ParameterZone parameterZoneDeepForest =
 new ParameterZone("ZoneDeepForest", "DeepForest");
 const ParameterZone parameterZoneFarm = new ParameterZone("ZoneFarm", "Farm");
 const ParameterZone parameterZoneForest =
 new ParameterZone("ZoneForest", "Forest");
 const ParameterZone parameterZoneNav = new ParameterZone("ZoneNav", "Nav");
 const ParameterZone parameterZoneTown =
 new ParameterZone("ZoneTown", "TownZone");
 const ParameterZone parameterZoneTrailerPark =
 new ParameterZone("ZoneTrailerPark", "TrailerPark");
 const ParameterZone parameterZoneVegetation =
 new ParameterZone("ZoneVegetation", "Vegitation");
 const ParameterZoneWaterSide parameterZoneWaterSide =
 new ParameterZoneWaterSide();
 const ParameterCameraZoom parameterCameraZoom = new ParameterCameraZoom();
 const ParameterClosestWallDistance parameterClosestWallDistance =
 new ParameterClosestWallDistance();
 const ParameterHardOfHearing parameterHardOfHearing =
 new ParameterHardOfHearing();
 const ParameterInside parameterInside = new ParameterInside();
 const ParameterMoodlePanic parameterMoodlePanic = new ParameterMoodlePanic();
 const ParameterPowerSupply parameterPowerSupply = new ParameterPowerSupply();
 const ParameterRoomSize parameterRoomSize = new ParameterRoomSize();
 const ParameterRoomType parameterRoomType = new ParameterRoomType();
 const ParameterWaterSupply parameterWaterSupply = new ParameterWaterSupply();
 const Vector2 tempo = new Vector2();
private
 FMOD_STUDIO_EVENT_CALLBACK electricityShutOffEventCallback =
 std::make_unique<FMOD_STUDIO_EVENT_CALLBACK>(){
 void timelineMarker(long var1, std::string_view string, int int0){
 DebugLog.Sound.debugln("timelineMarker %s %d", string, int0);
 if ("ElectricityOff" == string) {
 IsoWorld.instance.setHydroPowerOn(false);
 AmbientStreamManager.this->checkHaveElectricity();
 }
}
}; // namespace zombie

static BaseAmbientStreamManager getInstance() { return instance; }

void update() {
 if (this->initialized) {
 if (!GameTime.isGamePaused()) {
 if (IsoPlayer.getInstance() != nullptr) {
 if (IsoPlayer.getInstance().getCurrentSquare() != nullptr) {
 this->updatePowerSupply();
 this->parameterFogIntensity.update();
 this->parameterRainIntensity.update();
 this->parameterSeason.update();
 this->parameterSnowIntensity.update();
 this->parameterStorm.update();
 this->parameterTemperature.update();
 this->parameterTimeOfDay.update();
 this->parameterWeatherEvent.update();
 this->parameterWindIntensity.update();
 this->parameterZoneDeepForest.update();
 this->parameterZoneFarm.update();
 this->parameterZoneForest.update();
 this->parameterZoneNav.update();
 this->parameterZoneVegetation.update();
 this->parameterZoneTown.update();
 this->parameterZoneTrailerPark.update();
 this->parameterZoneWaterSide.update();
 this->parameterCameraZoom.update();
 this->parameterClosestWallDistance.update();
 this->parameterHardOfHearing.update();
 this->parameterInside.update();
 this->parameterMoodlePanic.update();
 this->parameterPowerSupply.update();
 this->parameterRoomSize.update();
 this->parameterRoomType.update();
 this->parameterWaterSupply.update();
 float float0 = GameTime.instance.getTimeOfDay();

 for (int int0 = 0; int0 < this->worldEmitters.size(); int0++) {
 AmbientStreamManager.WorldSoundEmitter worldSoundEmitter =
 this->worldEmitters.get(int0);
 if (worldSoundEmitter.daytime != nullptr) {
 IsoGridSquare square0 =
 IsoWorld.instance.CurrentCell.getGridSquare(
 (double)worldSoundEmitter.x, (double)worldSoundEmitter.y,
 (double)worldSoundEmitter.z);
 if (square0.empty()) {
 worldSoundEmitter.fmodEmitter.stopAll();
 SoundManager.instance.unregisterEmitter(
 worldSoundEmitter.fmodEmitter);
 this->worldEmitters.remove(worldSoundEmitter);
 this->freeEmitters.add(worldSoundEmitter);
 int0--;
 } else {
 if (float0 > worldSoundEmitter.dawn &&
 float0 < worldSoundEmitter.dusk) {
 if (worldSoundEmitter.fmodEmitter.empty()) {
 worldSoundEmitter.channel =
 worldSoundEmitter.fmodEmitter.playAmbientLoopedImpl(
 worldSoundEmitter.daytime);
 }
 } else if (!worldSoundEmitter.fmodEmitter.empty()) {
 worldSoundEmitter.fmodEmitter.stopSound(
 worldSoundEmitter.channel);
 worldSoundEmitter.channel = 0L;
 }

 if (!worldSoundEmitter.fmodEmitter.empty() &&
 (IsoWorld.instance.emitterUpdate ||
 worldSoundEmitter.fmodEmitter.hasSoundsToStart())) {
 worldSoundEmitter.fmodEmitter.tick();
 }
 }
 } else if (IsoPlayer.getInstance() != nullptr &&
 IsoPlayer.getInstance().Traits.Deaf.isSet()) {
 worldSoundEmitter.fmodEmitter.stopAll();
 SoundManager.instance.unregisterEmitter(
 worldSoundEmitter.fmodEmitter);
 this->worldEmitters.remove(worldSoundEmitter);
 this->freeEmitters.add(worldSoundEmitter);
 int0--;
 } else {
 IsoGridSquare square1 =
 IsoWorld.instance.CurrentCell.getGridSquare(
 (double)worldSoundEmitter.x, (double)worldSoundEmitter.y,
 (double)worldSoundEmitter.z);
 if (square1 != nullptr &&
 !worldSoundEmitter.fmodEmitter.empty()) {
 worldSoundEmitter.fmodEmitter.x = worldSoundEmitter.x;
 worldSoundEmitter.fmodEmitter.y = worldSoundEmitter.y;
 worldSoundEmitter.fmodEmitter.z = worldSoundEmitter.z;
 if (IsoWorld.instance.emitterUpdate ||
 worldSoundEmitter.fmodEmitter.hasSoundsToStart()) {
 worldSoundEmitter.fmodEmitter.tick();
 }
 } else {
 worldSoundEmitter.fmodEmitter.stopAll();
 SoundManager.instance.unregisterEmitter(
 worldSoundEmitter.fmodEmitter);
 this->worldEmitters.remove(worldSoundEmitter);
 this->freeEmitters.add(worldSoundEmitter);
 int0--;
 }
 }
 }

 float float1 = GameTime.instance.getNight();
 bool boolean0 =
 IsoPlayer.getInstance().getCurrentSquare().isInARoom();
 bool boolean1 = RainManager.isRaining();

 for (int int1 = 0; int1 < this->allAmbient.size(); int1++) {
 this->allAmbient.get(int1).targVol = 1.0F;
 }

 for (int int2 = 0; int2 < this->nightAmbient.size(); int2++) {
 this->nightAmbient.get(int2).targVol *= float1;
 }

 for (int int3 = 0; int3 < this->dayAmbient.size(); int3++) {
 this->dayAmbient.get(int3).targVol *= 1.0F - float1;
 }

 for (int int4 = 0; int4 < this->indoorAmbient.size(); int4++) {
 this->indoorAmbient.get(int4).targVol *= boolean0 ? 0.8F : 0.0F;
 }

 for (int int5 = 0; int5 < this->outdoorAmbient.size(); int5++) {
 this->outdoorAmbient.get(int5).targVol *= boolean0 ? 0.15F : 0.8F;
 }

 for (int int6 = 0; int6 < this->rainAmbient.size(); int6++) {
 this->rainAmbient.get(int6).targVol *= boolean1 ? 1.0F : 0.0F;
 if (this->rainAmbient.get(int6).channel != 0L) {
 javafmod.FMOD_Studio_EventInstance_SetParameterByName(
 this->rainAmbient.get(int6).channel, "RainIntensity",
 ClimateManager.getInstance().getPrecipitationIntensity());
 }
 }

 for (int int7 = 0; int7 < this->allAmbient.size(); int7++) {
 this->allAmbient.get(int7).update();
 }

 for (int int8 = 0; int8 < this->alarmList.size(); int8++) {
 this->alarmList.get(int8).update();
 if (this->alarmList.get(int8).finished) {
 this->alarmList.remove(int8);
 int8--;
 }
 }

 this->doOneShotAmbients();
 }
 }
 }
 }
}

void doOneShotAmbients() {
 for (int int0 = 0; int0 < this->ambient.size(); int0++) {
 AmbientStreamManager.Ambient ambientx = this->ambient.get(int0);
 if (ambientx.finished()) {
 DebugLog.log(DebugType.Sound,
 "ambient: removing ambient sound " + ambientx.name);
 this->ambient.remove(int0--);
 } else {
 ambientx.update();
 }
 }
}

void addRandomAmbient() {
 if (!Core.GameMode == "LastStand") && !Core.GameMode == "Tutorial")) {
 std::vector arrayList = new ArrayList();

 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 IsoPlayer player0 = IsoPlayer.players[int0];
 if (player0 != nullptr && player0.isAlive()) {
 arrayList.add(player0);
 }
 }

 if (!arrayList.empty()) {
 IsoPlayer player1 =
 (IsoPlayer)arrayList.get(Rand.Next(arrayList.size()));
 std::string string = "";
 if (GameTime.instance.getHour() > 7 &&
 GameTime.instance.getHour() < 21) {
 switch (Rand.Next(3) {
 case 0:
 if (Rand.Next(10) < 2) {
 string = "MetaDogBark";
 }
 break;
 case 1:
 if (Rand.Next(10) < 3) {
 string = "MetaScream";
 }
 }
 } else {
 switch (Rand.Next(5) {
 case 0:
 if (Rand.Next(10) < 2) {
 string = "MetaDogBark";
 }
 break;
 case 1:
 if (Rand.Next(13) < 3) {
 string = "MetaScream";
 }
 break;
 case 2:
 string = "MetaOwl";
 break;
 case 3:
 string = "MetaWolfHowl";
 }
 }

 if (!string.empty()) {
 float float0 = player1.x;
 float float1 = player1.y;
 double double0 = Rand.Next((float)-Math.PI, (float)Math.PI);
 this->tempo.x = (float)Math.cos(double0);
 this->tempo.y = (float)Math.sin(double0);
 this->tempo.setLength(1000.0F);
 float0 += this->tempo.x;
 float1 += this->tempo.y;
 if (!GameClient.bClient) {
 System.out.println("playing ambient: " + string +
 " at dist: " + Math.abs(float0 - player1.x) +
 "," + Math.abs(float1 - player1.y);
 AmbientStreamManager.Ambient ambientx =
 new AmbientStreamManager.Ambient(string, float0, float1, 50.0F,
 Rand.Next(0.2F, 0.5F);
 this->ambient.add(ambientx);
 }
 }
 }
 }
}

void addBlend(std::string_view name, float vol, bool bIndoors, bool bRain,
 bool bNight, bool bDay) {
 AmbientStreamManager.AmbientLoop ambientLoop =
 new AmbientStreamManager.AmbientLoop(0.0F, name, vol);
 this->allAmbient.add(ambientLoop);
 if (bIndoors) {
 this->indoorAmbient.add(ambientLoop);
 } else {
 this->outdoorAmbient.add(ambientLoop);
 }

 if (bRain) {
 this->rainAmbient.add(ambientLoop);
 }

 if (bNight) {
 this->nightAmbient.add(ambientLoop);
 }

 if (bDay) {
 this->dayAmbient.add(ambientLoop);
 }
}

void init() {
 if (!this->initialized) {
 this->initialized = true;
 }
}

void doGunEvent() {
 std::vector arrayList = new ArrayList();

 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 IsoPlayer player0 = IsoPlayer.players[int0];
 if (player0 != nullptr && player0.isAlive()) {
 arrayList.add(player0);
 }
 }

 if (!arrayList.empty()) {
 IsoPlayer player1 = (IsoPlayer)arrayList.get(Rand.Next(arrayList.size()));
 std::string string = nullptr;
 switch (Rand.Next(6) {
 case 0:
 string = "MetaAssaultRifle1";
 break;
 case 1:
 string = "MetaPistol1";
 break;
 case 2:
 string = "MetaShotgun1";
 break;
 case 3:
 string = "MetaPistol2";
 break;
 case 4:
 string = "MetaPistol3";
 break;
 case 5:
 string = "MetaShotgun1";
 }

 float float0 = player1.x;
 float float1 = player1.y;
 short short0 = 600;
 double double0 = Rand.Next((float)-Math.PI, (float)Math.PI);
 this->tempo.x = (float)Math.cos(double0);
 this->tempo.y = (float)Math.sin(double0);
 this->tempo.setLength(short0 - 100);
 float0 += this->tempo.x;
 float1 += this->tempo.y;
 WorldSoundManager.instance.addSound(nullptr, (int)float0, (int)float1, 0,
 short0, short0);
 float float2 = 1.0F;
 AmbientStreamManager.Ambient ambientx = new AmbientStreamManager.Ambient(
 string, float0, float1, 700.0F, float2);
 this->ambient.add(ambientx);
 }
}

void doAlarm(RoomDef room) {
 if (room != nullptr && room.building != nullptr && room.building.bAlarmed) {
 room.building.bAlarmed = false;
 room.building.setAllExplored(true);
 this->alarmList.add(
 new Alarm(room.x + room.getW() / 2, room.y + room.getH() / 2);
 }
}

void stop() {
 for (AmbientStreamManager.AmbientLoop ambientLoop : this->allAmbient) {
 ambientLoop.stop();
 }

 this->allAmbient.clear();
 this->ambient.clear();
 this->dayAmbient.clear();
 this->indoorAmbient.clear();
 this->nightAmbient.clear();
 this->outdoorAmbient.clear();
 this->rainAmbient.clear();
 this->windAmbient.clear();
 this->alarmList.clear();
 if (this->electricityShutOffEmitter != nullptr) {
 this->electricityShutOffEmitter.stopAll();
 this->electricityShutOffEvent = 0L;
 }

 this->electricityShutOffState = -1;
 this->initialized = false;
}

void addAmbient(std::string_view name, int x, int y, int radius,
 float volume) {
 if (GameClient.bClient) {
 AmbientStreamManager.Ambient ambientx =
 new AmbientStreamManager.Ambient(name, x, y, radius, volume, true);
 this->ambient.add(ambientx);
 }
}

void addAmbientEmitter(float x, float y, int z, std::string_view name) {
 AmbientStreamManager.WorldSoundEmitter worldSoundEmitter =
 this->freeEmitters.empty() ? new AmbientStreamManager.WorldSoundEmitter()
 : this->freeEmitters.pop();
 worldSoundEmitter.x = x;
 worldSoundEmitter.y = y;
 worldSoundEmitter.z = z;
 worldSoundEmitter.daytime = nullptr;
 if (worldSoundEmitter.fmodEmitter.empty()) {
 worldSoundEmitter.fmodEmitter = std::make_unique<FMODSoundEmitter>();
 }

 worldSoundEmitter.fmodEmitter.x = x;
 worldSoundEmitter.fmodEmitter.y = y;
 worldSoundEmitter.fmodEmitter.z = z;
 worldSoundEmitter.channel =
 worldSoundEmitter.fmodEmitter.playAmbientLoopedImpl(name);
 worldSoundEmitter.fmodEmitter.randomStart();
 SoundManager.instance.registerEmitter(worldSoundEmitter.fmodEmitter);
 this->worldEmitters.add(worldSoundEmitter);
}

void addDaytimeAmbientEmitter(float x, float y, int z,
 std::string_view name) {
 AmbientStreamManager.WorldSoundEmitter worldSoundEmitter =
 this->freeEmitters.empty() ? new AmbientStreamManager.WorldSoundEmitter()
 : this->freeEmitters.pop();
 worldSoundEmitter.x = x;
 worldSoundEmitter.y = y;
 worldSoundEmitter.z = z;
 if (worldSoundEmitter.fmodEmitter.empty()) {
 worldSoundEmitter.fmodEmitter = std::make_unique<FMODSoundEmitter>();
 }

 worldSoundEmitter.fmodEmitter.x = x;
 worldSoundEmitter.fmodEmitter.y = y;
 worldSoundEmitter.fmodEmitter.z = z;
 worldSoundEmitter.daytime = name;
 worldSoundEmitter.dawn = Rand.Next(7.0F, 8.0F);
 worldSoundEmitter.dusk = Rand.Next(19.0F, 20.0F);
 SoundManager.instance.registerEmitter(worldSoundEmitter.fmodEmitter);
 this->worldEmitters.add(worldSoundEmitter);
}

void updatePowerSupply() {
 bool boolean0 = GameTime.getInstance().NightsSurvived <
 SandboxOptions.getInstance().getElecShutModifier();
 if (this->electricityShutOffState == -1) {
 IsoWorld.instance.setHydroPowerOn(boolean0);
 }

 if (this->electricityShutOffState == 0 && boolean0) {
 IsoWorld.instance.setHydroPowerOn(true);
 this->checkHaveElectricity();
 }

 if (this->electricityShutOffState == 1 && !boolean0) {
 if (this->electricityShutOffEmitter.empty()) {
 this->electricityShutOffEmitter = std::make_unique<FMODSoundEmitter>();
 }

 if (!this->electricityShutOffEmitter.isPlaying(
 this->electricityShutOffEvent) {
 Vector2f vector2f = new Vector2f();
 this->getListenerPos(vector2f);
 BuildingDef buildingDef =
 this->getNearestBuilding(vector2f.x, vector2f.y, vector2f);
 if (buildingDef.empty()) {
 this->electricityShutOffEmitter.setPos(-1000.0F, -1000.0F, 0.0F);
 } else {
 this->electricityShutOffEmitter.setPos(vector2f.x, vector2f.y, 0.0F);
 }

 this->electricityShutOffEvent = this->electricityShutOffEmitter.playSound(
 "WorldEventElectricityShutdown");
 if (this->electricityShutOffEvent != 0L) {
 javafmod.FMOD_Studio_EventInstance_SetCallback(
 this->electricityShutOffEvent, this->electricityShutOffEventCallback,
 FMOD_STUDIO_EVENT_CALLBACK_TYPE
 .FMOD_STUDIO_EVENT_CALLBACK_TIMELINE_MARKER.bit);
 }
 }
 }

 this->electricityShutOffState = boolean0 ? 1 : 0;
 if (this->electricityShutOffEmitter != nullptr) {
 this->electricityShutOffEmitter.tick();
 }
}

void checkHaveElectricity() {
 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 IsoChunkMap chunkMap = IsoWorld.instance.CurrentCell.ChunkMap[int0];
 if (!chunkMap.ignore) {
 for (int int1 = 0; int1 < 8; int1++) {
 for (int int2 = chunkMap.getWorldYMinTiles();
 int2 <= chunkMap.getWorldYMaxTiles(); int2++) {
 for (int int3 = chunkMap.getWorldXMinTiles();
 int3 <= chunkMap.getWorldXMaxTiles(); int3++) {
 IsoGridSquare square =
 IsoWorld.instance.CurrentCell.getGridSquare(int3, int2, int1);
 if (square != nullptr) {
 for (int int4 = 0; int4 < square.getObjects().size(); int4++) {
 IsoObject object = square.getObjects().get(int4);
 object.checkHaveElectricity();
 }
 }
 }
 }
 }
 }
 }
}

BuildingDef getNearestBuilding(float px, float py, Vector2f closestXY) {
 IsoMetaGrid metaGrid = IsoWorld.instance.getMetaGrid();
 int int0 = PZMath.fastfloor(px / 300.0F);
 int int1 = PZMath.fastfloor(py / 300.0F);
 BuildingDef buildingDef0 = nullptr;
 float float0 = Float.MAX_VALUE;
 closestXY.set(0.0F);
 Vector2f vector2f = new Vector2f();

 for (int int2 = int1 - 1; int2 <= int1 + 1; int2++) {
 for (int int3 = int0 - 1; int3 <= int0 + 1; int3++) {
 IsoMetaCell metaCell = metaGrid.getCellData(int3, int2);
 if (metaCell != nullptr && metaCell.info != nullptr) {
 for (BuildingDef buildingDef1 : metaCell.info.Buildings) {
 float float1 = buildingDef1.getClosestPoint(px, py, vector2f);
 if (float1 < float0) {
 float0 = float1;
 buildingDef0 = buildingDef1;
 closestXY.set(vector2f);
 }
 }
 }
 }
 }

 return buildingDef0;
}

void getListenerPos(Vector2f vector2f) {
 IsoPlayer player0 = nullptr;
 vector2f.set(0.0F);

 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 IsoPlayer player1 = IsoPlayer.players[int0];
 if (player1 != nullptr &&
 (player0.empty() || player0.isDead() && player1.isAlive() ||
 player0.Traits.Deaf.isSet() && !player1.Traits.Deaf.isSet())) {
 player0 = player1;
 vector2f.set(player1.getX(), player1.getY());
 }
 }
}

public
static class Ambient {
 float x;
 float y;
 std::string name;
 float radius;
 float volume;
 int worldSoundRadius;
 int worldSoundVolume;
 bool trackMouse = false;
 const FMODSoundEmitter emitter = new FMODSoundEmitter();

public
 Ambient(std::string_view string, float float0, float float1, float float2,
 float float3) {
 this(string, float0, float1, float2, float3, false);
 }

public
 Ambient(std::string_view string, float float0, float float1, float float2,
 float float3, bool var6) {
 this->name = string;
 this->x = float0;
 this->y = float1;
 this->radius = float2;
 this->volume = float3;
 this->emitter.x = float0;
 this->emitter.y = float1;
 this->emitter.z = 0.0F;
 this->emitter.playAmbientSound(string);
 this->update();
 LuaEventManager.triggerEvent("OnAmbientSound", string, float0, float1);
 }

 bool finished() { return this->emitter.empty(); }

 void update() {
 this->emitter.tick();
 if (this->trackMouse && IsoPlayer.getInstance() != nullptr) {
 float float0 = Mouse.getXA();
 float float1 = Mouse.getYA();
 float0 -= IsoCamera.getScreenLeft(IsoPlayer.getPlayerIndex());
 float1 -= IsoCamera.getScreenTop(IsoPlayer.getPlayerIndex());
 float0 *= Core.getInstance().getZoom(IsoPlayer.getPlayerIndex());
 float1 *= Core.getInstance().getZoom(IsoPlayer.getPlayerIndex());
 int int0 = (int)IsoPlayer.getInstance().getZ();
 this->emitter.x = (int)IsoUtils.XToIso(float0, float1, int0);
 this->emitter.y = (int)IsoUtils.YToIso(float0, float1, int0);
 }

 if (!GameClient.bClient && this->worldSoundRadius > 0 &&
 this->worldSoundVolume > 0) {
 WorldSoundManager.instance.addSound(nullptr, (int)this->x, (int)this->y, 0,
 this->worldSoundRadius,
 this->worldSoundVolume);
 }
 }

 void repeatWorldSounds(int int0, int int1) {
 this->worldSoundRadius = int0;
 this->worldSoundVolume = int1;
 }

 IsoGameCharacter getClosestListener(float float4, float float5) {
 IsoPlayer player0 = nullptr;
 float float0 = Float.MAX_VALUE;

 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 IsoPlayer player1 = IsoPlayer.players[int0];
 if (player1 != nullptr && player1.getCurrentSquare() != nullptr) {
 float float1 = player1.getX();
 float float2 = player1.getY();
 float float3 =
 IsoUtils.DistanceToSquared(float1, float2, float4, float5);
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

 return player0;
 }
}

public static class AmbientLoop {
 static float volChangeAmount = 0.01F;
 float targVol;
 float currVol;
 std::string name;
 float volumedelta = 1.0F;
 long channel = -1L;
 const FMODSoundEmitter emitter = new FMODSoundEmitter();

public
 AmbientLoop(float float1, std::string_view string, float float0) {
 this->volumedelta = float0;
 this->channel = this->emitter.playAmbientLoopedImpl(string);
 this->targVol = float1;
 this->currVol = 0.0F;
 this->update();
 }

 void update() {
 if (this->targVol > this->currVol) {
 this->currVol = this->currVol + volChangeAmount;
 if (this->currVol > this->targVol) {
 this->currVol = this->targVol;
 }
 }

 if (this->targVol < this->currVol) {
 this->currVol = this->currVol - volChangeAmount;
 if (this->currVol < this->targVol) {
 this->currVol = this->targVol;
 }
 }

 this->emitter.setVolumeAll(this->currVol * this->volumedelta);
 this->emitter.tick();
 }

 void stop() { this->emitter.stopAll(); }
}

public static class WorldSoundEmitter {
 FMODSoundEmitter fmodEmitter;
 float x;
 float y;
 float z;
 long channel = -1L;
 std::string daytime;
 float dawn;
 float dusk;
}
}
} // namespace zombie
