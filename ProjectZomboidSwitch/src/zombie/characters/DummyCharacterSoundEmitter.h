#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/FMOD_STUDIO_PARAMETER_DESCRIPTION.h"
#include "zombie/core/Rand.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/network/GameClient.h"

namespace zombie {
namespace characters {


class DummyCharacterSoundEmitter : public BaseCharacterSoundEmitter {
public:
    float x;
    float y;
    float z;
   private const std::unordered_map<int64_t, std::string> sounds = std::make_unique<std::unordered_map<>>();

    public DummyCharacterSoundEmitter(IsoGameCharacter var1) {
      super(var1);
   }

    void register() {
   }

    void unregister() {
   }

    long playVocals(const std::string& var1) {
    return 0L;
   }

    void playFootsteps(const std::string& var1, float var2) {
   }

    long playSound(const std::string& var1) {
    long var2 = Rand.Next(int.MAX_VALUE);
      this.sounds.put(var2, var1);
      if (GameClient.bClient) {
         GameClient.instance.PlaySound(var1, false, this.character);
      }

    return var2;
   }

    long playSound(const std::string& var1, IsoObject var2) {
      return this.playSound(var1);
   }

    long playSoundImpl(const std::string& var1, IsoObject var2) {
    long var3 = Rand.Next(int64_t.MAX_VALUE);
      this.sounds.put(var3, var1);
    return var3;
   }

    void tick() {
   }

    void set(float var1, float var2, float var3) {
      this.x = var1;
      this.y = var2;
      this.z = var3;
   }

    bool isClear() {
      return this.sounds.empty();
   }

    void setPitch(long var1, float var3) {
   }

    void setVolume(long var1, float var3) {
   }

    int stopSound(long var1) {
      if (GameClient.bClient) {
         GameClient.instance.StopSound(this.character, this.sounds.get(var1), false);
      }

      this.sounds.remove(var1);
    return 0;
   }

    void stopSoundLocal(long var1) {
      this.sounds.remove(var1);
   }

    void stopOrTriggerSound(long var1) {
      if (GameClient.bClient) {
         GameClient.instance.StopSound(this.character, this.sounds.get(var1), true);
      }

      this.sounds.remove(var1);
   }

    void stopOrTriggerSoundByName(const std::string& var1) {
      this.sounds.values().remove(var1);
   }

    void stopAll() {
      if (GameClient.bClient) {
         for (std::string var2 : this.sounds.values()) {
            GameClient.instance.StopSound(this.character, var2, false);
         }
      }

      this.sounds.clear();
   }

    int stopSoundByName(const std::string& var1) {
      this.sounds.values().remove(var1);
    return 0;
   }

    bool hasSoundsToStart() {
    return false;
   }

    bool isPlaying(long var1) {
      return this.sounds.containsKey(var1);
   }

    bool isPlaying(const std::string& var1) {
      return this.sounds.containsValue(var1);
   }

    void setParameterValue(long var1, FMOD_STUDIO_PARAMETER_DESCRIPTION var3, float var4) {
   }

    bool hasSustainPoints(long var1) {
    return false;
   }
}
} // namespace characters
} // namespace zombie
