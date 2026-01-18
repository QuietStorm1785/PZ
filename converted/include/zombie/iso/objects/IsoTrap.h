#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/SandboxOptions.h"
#include "zombie/WorldSoundManager.h"
#include "zombie/audio/BaseSoundEmitter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/PerformanceSettings.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/network/GameServer.h"
#include "zombie/util/StringUtils.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {
namespace objects {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class IsoTrap : public IsoObject {
public:
 int timerBeforeExplosion = 0;
 int FPS;
 int sensorRange = 0;
 int firePower = 0;
 int fireRange = 0;
 int explosionPower = 0;
 int explosionRange = 0;
 int smokeRange = 0;
 int noiseRange = 0;
 int noiseDuration = 0;
 float noiseStartTime = 0.0F;
 float lastWorldSoundTime = 0.0F;
 float extraDamage = 0.0F;
 int remoteControlID = -1;
 std::string countDownSound = nullptr;
 std::string explosionSound = nullptr;
 int lastBeep = 0;
 HandWeapon weapon;
 bool instantExplosion;

 public IsoTrap(IsoCell cell) {
 super(cell);
 this->FPS = GameServer.bServer ? 10 : PerformanceSettings.getLockFPS();
 }

 public IsoTrap(HandWeapon _weapon, IsoCell cell, IsoGridSquare sq) {
 this->square = sq;
 this->initSprite(_weapon);
 this->setSensorRange(_weapon.getSensorRange());
 this->setFireRange(_weapon.getFireRange());
 this->setFirePower(_weapon.getFirePower());
 this->setExplosionPower(_weapon.getExplosionPower());
 this->setExplosionRange(_weapon.getExplosionRange());
 this->setSmokeRange(_weapon.getSmokeRange());
 this->setNoiseRange(_weapon.getNoiseRange());
 this->setNoiseDuration(_weapon.getNoiseDuration());
 this->setExtraDamage(_weapon.getExtraDamage());
 this->setRemoteControlID(_weapon.getRemoteControlID());
 this->setCountDownSound(_weapon.getCountDownSound());
 this->setExplosionSound(_weapon.getExplosionSound());
 this->FPS = GameServer.bServer ? 10 : PerformanceSettings.getLockFPS();
 if (_weapon.getExplosionTimer() > 0) {
 this->timerBeforeExplosion = _weapon.getExplosionTimer() * this->FPS - 1;
 } else if (!_weapon.canBeRemote()) {
 this->timerBeforeExplosion = 1;
 }

 if (_weapon.canBePlaced()) {
 this->weapon = _weapon;
 }

 this->instantExplosion = _weapon.isInstantExplosion();
 }

 void initSprite(HandWeapon weaponx) {
 if (weaponx != nullptr) {
 std::string string;
 if (weaponx.getPlacedSprite() != nullptr && !weaponx.getPlacedSprite().empty()) {
 string = weaponx.getPlacedSprite();
 } else if (weaponx.getTex() != nullptr && weaponx.getTex().getName() != nullptr) {
 string = weaponx.getTex().getName();
 } else {
 string = "media/inventory/world/WItem_Sack.png";
 }

 this->sprite = IsoSprite.CreateSprite(IsoSpriteManager.instance);
 Texture texture = this->sprite.LoadFrameExplicit(string);
 if (string.startsWith("Item_") && texture != nullptr) {
 if (weaponx.getScriptItem() == nullptr) {
 this->sprite.def.scaleAspect(texture.getWidthOrig(), texture.getHeightOrig(), 16 * Core.TileScale, 16 * Core.TileScale);
 } else {
 float float0 = Core.TileScale;
 float float1 = weaponx.getScriptItem().ScaleWorldIcon * (float0 / 2.0F);
 this->sprite.def.setScale(float1, float1);
 }
 }
 }
 }

 void update() {
 if (this->timerBeforeExplosion > 0) {
 if (this->timerBeforeExplosion / this->FPS + 1 != this->lastBeep) {
 this->lastBeep = this->timerBeforeExplosion / this->FPS + 1;
 if (!GameServer.bServer && this->getObjectIndex() != -1) {
 this->getOrCreateEmitter();
 if (!StringUtils.isNullOrWhitespace(this->getCountDownSound())) {
 this->emitter.playSound(this->getCountDownSound());
 } else if (this->lastBeep == 1) {
 this->emitter.playSound("TrapTimerExpired");
 } else {
 this->emitter.playSound("TrapTimerLoop");
 }
 }
 }

 this->timerBeforeExplosion--;
 if (this->timerBeforeExplosion == 0) {
 this->triggerExplosion(this->getSensorRange() > 0);
 }
 }

 this->updateSounds();
 }

 void updateSounds() {
 if (this->noiseStartTime > 0.0F) {
 float float0 = (float)GameTime.getInstance().getWorldAgeHours();
 this->noiseStartTime = PZMath.min(this->noiseStartTime, float0);
 this->lastWorldSoundTime = PZMath.min(this->lastWorldSoundTime, float0);
 float float1 = 60.0F / SandboxOptions.getInstance().getDayLengthMinutes();
 float float2 = 60.0F;
 if (float0 - this->noiseStartTime > this->getNoiseDuration() / float2 * float1) {
 this->noiseStartTime = 0.0F;
 if (this->emitter != nullptr) {
 this->emitter.stopAll();
 }
 } else {
 if (!GameServer.bServer && (this->emitter.empty() || !this->emitter.isPlaying(this->getExplosionSound()))) {
 BaseSoundEmitter baseSoundEmitter = this->getOrCreateEmitter();
 if (baseSoundEmitter != nullptr) {
 baseSoundEmitter.playSound(this->getExplosionSound());
 }
 }

 if (float0 - this->lastWorldSoundTime > 1.0F / float2 * float1 && this->getObjectIndex() != -1) {
 this->lastWorldSoundTime = float0;
 WorldSoundManager.instance
 .addSoundRepeating(nullptr, this->getSquare().getX(), this->getSquare().getY(), this->getSquare().getZ(), this->getNoiseRange(), 1, true);
 }
 }
 }

 if (this->emitter != nullptr) {
 this->emitter.tick();
 }
 }

 void render(float x, float y, float z, ColorInfo col, bool bDoChild, bool bWallLightingPass, Shader shader) {
 if (this->sprite.CurrentAnim != nullptr && !this->sprite.CurrentAnim.Frames.empty()) {
 Texture texture = this->sprite.CurrentAnim.Frames.get(0).getTexture(this->dir);
 if (texture != nullptr) {
 if (texture.getName().startsWith("Item_")) {
 float float0 = texture.getWidthOrig() * this->sprite.def.getScaleX() / 2.0F;
 float float1 = texture.getHeightOrig() * this->sprite.def.getScaleY() * 3.0F / 4.0F;
 this->setAlphaAndTarget(1.0F);
 this->offsetX = 0.0F;
 this->offsetY = 0.0F;
 this->sx = 0.0F;
 this->sprite.render(this, x + 0.5F, y + 0.5F, z, this->dir, this->offsetX + float0, this->offsetY + float1, col, true);
 } else {
 this->offsetX = 32 * Core.TileScale;
 this->offsetY = 96 * Core.TileScale;
 this->sx = 0.0F;
 super.render(x, y, z, col, bDoChild, bWallLightingPass, shader);
 }
 }
 }
 }

 void triggerExplosion(bool sensor) {
 LuaEventManager.triggerEvent("OnThrowableExplode", this, this->square);
 if (sensor) {
 if (this->getSensorRange() > 0) {
 this->square.setTrapPositionX(this->square.getX());
 this->square.setTrapPositionY(this->square.getY());
 this->square.setTrapPositionZ(this->square.getZ());
 this->square.drawCircleExplosion(this->getSensorRange(), this, IsoTrap.ExplosionMode.Sensor);
 }
 } else {
 if (this->getExplosionSound() != nullptr) {
 this->playExplosionSound();
 }

 if (this->getNoiseRange() > 0) {
 WorldSoundManager.instance.addSound(nullptr, (int)this->getX(), (int)this->getY(), (int)this->getZ(), this->getNoiseRange(), 1);
 } else if (this->getExplosionSound() != nullptr) {
 WorldSoundManager.instance.addSound(nullptr, (int)this->getX(), (int)this->getY(), (int)this->getZ(), 50, 1);
 }

 if (this->getExplosionRange() > 0) {
 this->square.drawCircleExplosion(this->getExplosionRange(), this, IsoTrap.ExplosionMode.Explosion);
 }

 if (this->getFireRange() > 0) {
 this->square.drawCircleExplosion(this->getFireRange(), this, IsoTrap.ExplosionMode.Fire);
 }

 if (this->getSmokeRange() > 0) {
 this->square.drawCircleExplosion(this->getSmokeRange(), this, IsoTrap.ExplosionMode.Smoke);
 }

 if (this->weapon.empty() || !this->weapon.canBeReused()) {
 if (GameServer.bServer) {
 GameServer.RemoveItemFromMap(this);
 } else {
 this->removeFromWorld();
 this->removeFromSquare();
 }
 }
 }
 }

 BaseSoundEmitter getOrCreateEmitter() {
 if (this->getObjectIndex() == -1) {
 return nullptr;
 } else {
 if (this->emitter.empty()) {
 this->emitter = IsoWorld.instance.getFreeEmitter(this->getX() + 0.5F, this->getY() + 0.5F, this->getZ());
 IsoWorld.instance.takeOwnershipOfEmitter(this->emitter);
 }

 return this->emitter;
 }
 }

 void playExplosionSound() {
 if (!StringUtils.isNullOrWhitespace(this->getExplosionSound())) {
 if (this->getObjectIndex() != -1) {
 if (this->getNoiseRange() > 0 && this->getNoiseDuration() > 0.0F) {
 this->noiseStartTime = (float)GameTime.getInstance().getWorldAgeHours();
 }

 if (!GameServer.bServer) {
 this->getOrCreateEmitter();
 if (!this->emitter.isPlaying(this->getExplosionSound())) {
 this->emitter.playSoundImpl(this->getExplosionSound(), (IsoObject)nullptr);
 }
 }
 }
 }
 }

 void load(ByteBuffer input, int WorldVersion, bool IS_DEBUG_SAVE) {
 super.load(input, WorldVersion, IS_DEBUG_SAVE);
 this->sensorRange = input.getInt();
 this->firePower = input.getInt();
 this->fireRange = input.getInt();
 this->explosionPower = input.getInt();
 this->explosionRange = input.getInt();
 this->smokeRange = input.getInt();
 this->noiseRange = input.getInt();
 if (WorldVersion >= 180) {
 this->noiseDuration = input.getInt();
 this->noiseStartTime = input.getFloat();
 }

 this->extraDamage = input.getFloat();
 this->remoteControlID = input.getInt();
 if (WorldVersion >= 78) {
 this->timerBeforeExplosion = input.getInt() * this->FPS;
 this->countDownSound = GameWindow.ReadStringUTF(input);
 this->explosionSound = GameWindow.ReadStringUTF(input);
 if ("bigExplosion" == this->explosionSound) {
 this->explosionSound = "BigExplosion";
 }

 if ("smallExplosion" == this->explosionSound) {
 this->explosionSound = "SmallExplosion";
 }

 if ("feedback" == this->explosionSound) {
 this->explosionSound = "NoiseTrapExplosion";
 }
 }

 if (WorldVersion >= 82) {
 bool boolean0 = input.get() == 1;
 if (boolean0) {
 InventoryItem item = InventoryItem.loadItem(input, WorldVersion);
 if (item instanceof HandWeapon) {
 this->weapon = (HandWeapon)item;
 this->initSprite(this->weapon);
 }
 }
 }
 }

 void save(ByteBuffer output, bool IS_DEBUG_SAVE) {
 super.save(output, IS_DEBUG_SAVE);
 output.putInt(this->sensorRange);
 output.putInt(this->firePower);
 output.putInt(this->fireRange);
 output.putInt(this->explosionPower);
 output.putInt(this->explosionRange);
 output.putInt(this->smokeRange);
 output.putInt(this->noiseRange);
 output.putInt(this->noiseDuration);
 output.putFloat(this->noiseStartTime);
 output.putFloat(this->extraDamage);
 output.putInt(this->remoteControlID);
 output.putInt(this->timerBeforeExplosion > 1 ? Math.max(this->timerBeforeExplosion / this->FPS, 1) : 0);
 GameWindow.WriteStringUTF(output, this->countDownSound);
 GameWindow.WriteStringUTF(output, this->explosionSound);
 if (this->weapon != nullptr) {
 output.put((byte)1);
 this->weapon.saveWithSize(output, false);
 } else {
 output.put((byte)0);
 }
 }

 void addToWorld() {
 this->getCell().addToProcessIsoObject(this);
 }

 void removeFromWorld() {
 if (this->emitter != nullptr) {
 if (this->noiseStartTime > 0.0F) {
 this->emitter.stopAll();
 }

 IsoWorld.instance.returnOwnershipOfEmitter(this->emitter);
 this->emitter = nullptr;
 }

 super.removeFromWorld();
 }

 int getTimerBeforeExplosion() {
 return this->timerBeforeExplosion;
 }

 void setTimerBeforeExplosion(int _timerBeforeExplosion) {
 this->timerBeforeExplosion = _timerBeforeExplosion;
 }

 int getSensorRange() {
 return this->sensorRange;
 }

 void setSensorRange(int _sensorRange) {
 this->sensorRange = _sensorRange;
 }

 int getFireRange() {
 return this->fireRange;
 }

 void setFireRange(int _fireRange) {
 this->fireRange = _fireRange;
 }

 int getFirePower() {
 return this->firePower;
 }

 void setFirePower(int _firePower) {
 this->firePower = _firePower;
 }

 int getExplosionPower() {
 return this->explosionPower;
 }

 void setExplosionPower(int _explosionPower) {
 this->explosionPower = _explosionPower;
 }

 int getNoiseDuration() {
 return this->noiseDuration;
 }

 void setNoiseDuration(int _noiseDuration) {
 this->noiseDuration = _noiseDuration;
 }

 int getNoiseRange() {
 return this->noiseRange;
 }

 void setNoiseRange(int _noiseRange) {
 this->noiseRange = _noiseRange;
 }

 int getExplosionRange() {
 return this->explosionRange;
 }

 void setExplosionRange(int _explosionRange) {
 this->explosionRange = _explosionRange;
 }

 int getSmokeRange() {
 return this->smokeRange;
 }

 void setSmokeRange(int _smokeRange) {
 this->smokeRange = _smokeRange;
 }

 float getExtraDamage() {
 return this->extraDamage;
 }

 void setExtraDamage(float _extraDamage) {
 this->extraDamage = _extraDamage;
 }

 std::string getObjectName() {
 return "IsoTrap";
 }

 int getRemoteControlID() {
 return this->remoteControlID;
 }

 void setRemoteControlID(int _remoteControlID) {
 this->remoteControlID = _remoteControlID;
 }

 std::string getCountDownSound() {
 return this->countDownSound;
 }

 void setCountDownSound(const std::string& sound) {
 this->countDownSound = sound;
 }

 std::string getExplosionSound() {
 return this->explosionSound;
 }

 void setExplosionSound(const std::string& _explosionSound) {
 this->explosionSound = _explosionSound;
 }

 InventoryItem getItem() {
 return this->weapon;
 }

 static void triggerRemote(IsoPlayer player, int remoteID, int range) {
 int int0 = (int)player.getX();
 int int1 = (int)player.getY();
 int int2 = (int)player.getZ();
 int int3 = Math.max(int2 - range / 2, 0);
 int int4 = Math.min(int2 + range / 2, 8);
 IsoCell cell = IsoWorld.instance.CurrentCell;

 for (int int5 = int3; int5 < int4; int5++) {
 for (int int6 = int1 - range; int6 < int1 + range; int6++) {
 for (int int7 = int0 - range; int7 < int0 + range; int7++) {
 IsoGridSquare square = cell.getGridSquare(int7, int6, int5);
 if (square != nullptr) {
 for (int int8 = square.getObjects().size() - 1; int8 >= 0; int8--) {
 IsoObject object = square.getObjects().get(int8);
 if (object instanceof IsoTrap && ((IsoTrap)object).getRemoteControlID() == remoteID) {
 ((IsoTrap)object).triggerExplosion(false);
 }
 }
 }
 }
 }
 }
 }

 bool isInstantExplosion() {
 return this->instantExplosion;
 }

 public static enum ExplosionMode {
 Explosion,
 Fire,
 Smoke,
 Sensor;
 }
}
} // namespace objects
} // namespace iso
} // namespace zombie
