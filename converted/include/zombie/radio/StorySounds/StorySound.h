#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/iso/Vector2.h"

namespace zombie {
namespace radio {
namespace StorySounds {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


/**
 * Turbo
 */
class StorySound {
public:
 std::string name = nullptr;
 float baseVolume = 1.0F;

 public StorySound(const std::string& _name, float baseVol) {
 this->name = _name;
 this->baseVolume = baseVol;
 }

 long playSound() {
 Vector2 vector = SLSoundManager.getInstance().getRandomBorderPosition();
 return SLSoundManager.Emitter
 .playSound(this->name, this->baseVolume, vector.x, vector.y, 0.0F, 100.0F, SLSoundManager.getInstance().getRandomBorderRange());
 }

 long playSound(float volumeOverride) {
 return SLSoundManager.Emitter
 .playSound(this->name, volumeOverride, IsoPlayer.getInstance().x, IsoPlayer.getInstance().y, IsoPlayer.getInstance().z, 10.0F, 50.0F);
 }

 long playSound(float x, float y, float z, float minRange, float maxRange) {
 return this->playSound(this->baseVolume, x, y, z, minRange, maxRange);
 }

 long playSound(float volumeMod, float x, float y, float z, float minRange, float maxRange) {
 return SLSoundManager.Emitter.playSound(this->name, this->baseVolume * volumeMod, x, y, z, minRange, maxRange);
 }

 std::string getName() {
 return this->name;
 }

 void setName(const std::string& _name) {
 this->name = _name;
 }

 float getBaseVolume() {
 return this->baseVolume;
 }

 void setBaseVolume(float _baseVolume) {
 this->baseVolume = _baseVolume;
 }

 StorySound getClone() {
 return new StorySound(this->name, this->baseVolume);
 }
}
} // namespace StorySounds
} // namespace radio
} // namespace zombie
