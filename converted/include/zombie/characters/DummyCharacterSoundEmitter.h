#pragma once
#include "fmod/fmod/FMOD_STUDIO_PARAMETER_DESCRIPTION.h"
#include "zombie/core/Rand.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/network/GameClient.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace characters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class DummyCharacterSoundEmitter : public BaseCharacterSoundEmitter {
public:
  float x;
  float y;
  float z;
private
  final HashMap<Long, String> sounds = std::make_unique<HashMap<>>();

public
  DummyCharacterSoundEmitter(IsoGameCharacter chr) { super(chr); }

  void register() {}

  void unregister() {}

  long playVocals(const std::string &file) { return 0L; }

  void playFootsteps(const std::string &file, float volume) {}

  long playSound(const std::string &file) {
    long long0 = Rand.Next(Integer.MAX_VALUE);
    this.sounds.put(long0, file);
    if (GameClient.bClient) {
      GameClient.instance.PlaySound(file, false, this.character);
    }

    return long0;
  }

  long playSound(const std::string &file, IsoObject proxy) {
    return this.playSound(file);
  }

  long playSoundImpl(const std::string &file, IsoObject proxy) {
    long long0 = Rand.Next(Long.MAX_VALUE);
    this.sounds.put(long0, file);
    return long0;
  }

  void tick() {}

  void set(float _x, float _y, float _z) {
    this.x = _x;
    this.y = _y;
    this.z = _z;
  }

  bool isClear() { return this.sounds.isEmpty(); }

  void setPitch(long handle, float pitch) {}

  void setVolume(long handle, float volume) {}

  int stopSound(long channel) {
    if (GameClient.bClient) {
      GameClient.instance.StopSound(this.character, this.sounds.get(channel),
                                    false);
    }

    this.sounds.remove(channel);
    return 0;
  }

  void stopSoundLocal(long handle) { this.sounds.remove(handle); }

  void stopOrTriggerSound(long handle) {
    if (GameClient.bClient) {
      GameClient.instance.StopSound(this.character, this.sounds.get(handle),
                                    true);
    }

    this.sounds.remove(handle);
  }

  void stopOrTriggerSoundByName(const std::string &name) {
    this.sounds.values().remove(name);
  }

  void stopAll() {
    if (GameClient.bClient) {
      for (String string : this.sounds.values()) {
        GameClient.instance.StopSound(this.character, string, false);
      }
    }

    this.sounds.clear();
  }

  int stopSoundByName(const std::string &soundName) {
    this.sounds.values().remove(soundName);
    return 0;
  }

  bool hasSoundsToStart() { return false; }

  bool isPlaying(long channel) { return this.sounds.containsKey(channel); }

  bool isPlaying(const std::string &alias) {
    return this.sounds.containsValue(alias);
  }

  void setParameterValue(long soundRef,
                         FMOD_STUDIO_PARAMETER_DESCRIPTION parameterDescription,
                         float value) {}

  bool hasSustainPoints(long handle) { return false; }
}
} // namespace characters
} // namespace zombie
