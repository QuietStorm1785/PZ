#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/FMODManager.h"
#include "fmod/fmod/FMOD_STUDIO_EVENT_DESCRIPTION.h"
#include "fmod/javafmod.h"
#include "zombie/GameSounds.h"
#include "zombie/GameTime.h"
#include "zombie/SoundManager.h"
#include "zombie/WorldSoundManager.h"
#include "zombie/audio/GameSound.h"
#include "zombie/audio/GameSoundClip.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"

namespace zombie {
namespace iso {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class Helicopter {
public:
 static float MAX_BOTHER_SECONDS = 60.0F;
 static float MAX_UNSEEN_SECONDS = 15.0F;
 static int RADIUS_HOVER = 50;
 static int RADIUS_SEARCH = 100;
 protected Helicopter.State state;
 IsoGameCharacter target;
 float timeSinceChopperSawPlayer;
 float hoverTime;
 float searchTime;
 float x;
 float y;
 float targetX;
 float targetY;
 Vector2 move = new Vector2();
 bool bActive;
 static long inst;
 static FMOD_STUDIO_EVENT_DESCRIPTION event;
 bool bSoundStarted;
 float volume;
 float occlusion;

 void pickRandomTarget() {
 std::vector arrayList;
 if (GameServer.bServer) {
 arrayList = GameServer.getPlayers();
 } else {
 if (GameClient.bClient) {
 throw IllegalStateException("can't call this on the client");
 }

 arrayList = std::make_unique<ArrayList>();

 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 IsoPlayer player = IsoPlayer.players[int0];
 if (player != nullptr && player.isAlive()) {
 arrayList.add(player);
 }
 }
 }

 if (arrayList.empty()) {
 this->bActive = false;
 this->target = nullptr;
 } else {
 this->setTarget((IsoGameCharacter)arrayList.get(Rand.Next(arrayList.size())));
 }
 }

 void setTarget(IsoGameCharacter chr) {
 this->target = chr;
 this->x = this->target.x + 1000.0F;
 this->y = this->target.y + 1000.0F;
 this->targetX = this->target.x;
 this->targetY = this->target.y;
 this->move.x = this->targetX - this->x;
 this->move.y = this->targetY - this->y;
 this->move.normalize();
 this->move.setLength(0.5F);
 this->state = Helicopter.State.Arriving;
 this->bActive = true;
 DebugLog.log("chopper: activated");
 }

 void changeState(Helicopter.State statex) {
 DebugLog.log("chopper: state " + this->state + " -> " + statex);
 this->state = statex;
 }

 void update() {
 if (this->bActive) {
 if (GameClient.bClient) {
 this->updateSound();
 } else {
 float float0 = 1.0F;
 if (GameServer.bServer) {
 if (!GameServer.Players.contains(this->target) {
 this->target = nullptr;
 }
 } else {
 float0 = GameTime.getInstance().getTrueMultiplier();
 }

 switch (this->state) {
 case Arriving:
 if (this->target != nullptr && !this->target.isDead()) {
 if (IsoUtils.DistanceToSquared(this->x, this->y, this->targetX, this->targetY) < 4.0F) {
 this->changeState(Helicopter.State.Hovering);
 this->hoverTime = 0.0F;
 this->searchTime = 0.0F;
 this->timeSinceChopperSawPlayer = 0.0F;
 } else {
 this->targetX = this->target.x;
 this->targetY = this->target.y;
 this->move.x = this->targetX - this->x;
 this->move.y = this->targetY - this->y;
 this->move.normalize();
 this->move.setLength(0.75F);
 }
 } else {
 this->changeState(Helicopter.State.Leaving);
 }
 break;
 case Hovering:
 if (this->target != nullptr && !this->target.isDead()) {
 this->hoverTime = this->hoverTime + GameTime.getInstance().getRealworldSecondsSinceLastUpdate() * float0;
 if (this->hoverTime + this->searchTime > MAX_BOTHER_SECONDS) {
 this->changeState(Helicopter.State.Leaving);
 } else {
 if (!this->isTargetVisible()) {
 this->timeSinceChopperSawPlayer = this->timeSinceChopperSawPlayer
 + GameTime.getInstance().getRealworldSecondsSinceLastUpdate() * float0;
 if (this->timeSinceChopperSawPlayer > MAX_UNSEEN_SECONDS) {
 this->changeState(Helicopter.State.Searching);
 break;
 }
 }

 if (IsoUtils.DistanceToSquared(this->x, this->y, this->targetX, this->targetY) < 1.0F) {
 this->targetX = this->target.x + (Rand.Next(RADIUS_HOVER * 2) - RADIUS_HOVER);
 this->targetY = this->target.y + (Rand.Next(RADIUS_HOVER * 2) - RADIUS_HOVER);
 this->move.x = this->targetX - this->x;
 this->move.y = this->targetY - this->y;
 this->move.normalize();
 this->move.setLength(0.5F);
 }
 }
 } else {
 this->changeState(Helicopter.State.Leaving);
 }
 break;
 case Searching:
 if (this->target != nullptr && !this->target.isDead()) {
 this->searchTime = this->searchTime + GameTime.getInstance().getRealworldSecondsSinceLastUpdate() * float0;
 if (this->hoverTime + this->searchTime > MAX_BOTHER_SECONDS) {
 this->changeState(Helicopter.State.Leaving);
 } else if (this->isTargetVisible()) {
 this->timeSinceChopperSawPlayer = 0.0F;
 this->changeState(Helicopter.State.Hovering);
 } else if (IsoUtils.DistanceToSquared(this->x, this->y, this->targetX, this->targetY) < 1.0F) {
 this->targetX = this->target.x + (Rand.Next(RADIUS_SEARCH * 2) - RADIUS_SEARCH);
 this->targetY = this->target.y + (Rand.Next(RADIUS_SEARCH * 2) - RADIUS_SEARCH);
 this->move.x = this->targetX - this->x;
 this->move.y = this->targetY - this->y;
 this->move.normalize();
 this->move.setLength(0.5F);
 }
 } else {
 this->state = Helicopter.State.Leaving;
 }
 break;
 case Leaving:
 bool boolean0 = false;
 if (GameServer.bServer) {
 std::vector arrayList = GameServer.getPlayers();

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 IsoPlayer player0 = (IsoPlayer)arrayList.get(int0);
 if (IsoUtils.DistanceToSquared(this->x, this->y, player0.getX(), player0.getY()) < 1000000.0F) {
 boolean0 = true;
 break;
 }
 }
 } else {
 for (int int1 = 0; int1 < IsoPlayer.numPlayers; int1++) {
 IsoPlayer player1 = IsoPlayer.players[int1];
 if (player1 != nullptr && IsoUtils.DistanceToSquared(this->x, this->y, player1.getX(), player1.getY()) < 1000000.0F) {
 boolean0 = true;
 break;
 }
 }
 }

 if (!boolean0) {
 this->deactivate();
 return;
 }
 }

 if (Rand.Next(Rand.AdjustForFramerate(300) == 0) {
 WorldSoundManager.instance.addSound(nullptr, (int)this->x, (int)this->y, 0, 500, 500);
 }

 float float1 = this->move.x * (GameTime.getInstance().getMultiplier() / 1.6F);
 float float2 = this->move.y * (GameTime.getInstance().getMultiplier() / 1.6F);
 if (this->state != Helicopter.State.Leaving
 && IsoUtils.DistanceToSquared(this->x + float1, this->y + float2, this->targetX, this->targetY)
 > IsoUtils.DistanceToSquared(this->x, this->y, this->targetX, this->targetY) {
 this->x = this->targetX;
 this->y = this->targetY;
 } else {
 this->x += float1;
 this->y += float2;
 }

 if (GameServer.bServer) {
 GameServer.sendHelicopter(this->x, this->y, this->bActive);
 }

 this->updateSound();
 }
 }
 }

 void updateSound() {
 if (!GameServer.bServer) {
 if (!Core.SoundDisabled) {
 if (FMODManager.instance.getNumListeners() != 0) {
 GameSound gameSound = GameSounds.getSound("Helicopter");
 if (gameSound != nullptr && !gameSound.clips.empty()) {
 if (inst == 0L) {
 GameSoundClip gameSoundClip = gameSound.getRandomClip();
 event = gameSoundClip.eventDescription;
 if (event != nullptr) {
 javafmod.FMOD_Studio_LoadEventSampleData(event.address);
 inst = javafmod.FMOD_Studio_System_CreateEventInstance(event.address);
 }
 }

 if (inst != 0L) {
 float float0 = SoundManager.instance.getSoundVolume();
 float0 *= gameSound.getUserVolume();
 if (float0 != this->volume) {
 javafmod.FMOD_Studio_EventInstance_SetVolume(inst, float0);
 this->volume = float0;
 }

 javafmod.FMOD_Studio_EventInstance3D(inst, this->x, this->y, 200.0F);
 float float1 = 0.0F;
 if (IsoPlayer.numPlayers == 1) {
 IsoGridSquare square = IsoPlayer.getInstance().getCurrentSquare();
 if (square != nullptr && !square.Is(IsoFlagType.exterior) {
 float1 = 1.0F;
 }
 }

 if (this->occlusion != float1) {
 this->occlusion = float1;
 javafmod.FMOD_Studio_EventInstance_SetParameterByName(inst, "Occlusion", this->occlusion);
 }

 if (!this->bSoundStarted) {
 javafmod.FMOD_Studio_StartEvent(inst);
 this->bSoundStarted = true;
 }
 }
 }
 }
 }
 }
 }

 bool isTargetVisible() {
 if (this->target != nullptr && !this->target.isDead()) {
 IsoGridSquare square = this->target.getCurrentSquare();
 if (square == nullptr) {
 return false;
 } else if (!square.getProperties().Is(IsoFlagType.exterior) {
 return false;
 } else {
 IsoMetaGrid.Zone zone = square.getZone();
 return zone = = nullptr ? true : !"Forest".equals(zone.getType()) && !"DeepForest".equals(zone.getType());
 }
 } else {
 return false;
 }
 }

 void deactivate() {
 if (this->bActive) {
 this->bActive = false;
 if (this->bSoundStarted) {
 javafmod.FMOD_Studio_EventInstance_Stop(inst, false);
 this->bSoundStarted = false;
 }

 if (GameServer.bServer) {
 GameServer.sendHelicopter(this->x, this->y, this->bActive);
 }

 DebugLog.log("chopper: deactivated");
 }
 }

 bool isActive() {
 return this->bActive;
 }

 void clientSync(float _x, float _y, bool active) {
 if (GameClient.bClient) {
 this->x = _x;
 this->y = _y;
 if (!active) {
 this->deactivate();
 }

 this->bActive = active;
 }
 }

 private static enum State {
 Arriving,
 Hovering,
 Searching,
 Leaving;
 }
}
} // namespace iso
} // namespace zombie
