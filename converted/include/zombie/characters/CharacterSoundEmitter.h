#pragma once
#include "fmod/fmod/EmitterType.h"
#include "fmod/fmod/FMODManager.h"
#include "fmod/fmod/FMODSoundBank.h"
#include "fmod/fmod/FMODSoundEmitter.h"
#include "fmod/fmod/FMODVoice.h"
#include "fmod/fmod/FMOD_STUDIO_PARAMETER_DESCRIPTION.h"
#include "zombie/SoundManager.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/debug/DebugType.h"
#include "zombie/interfaces/ICommonSoundEmitter.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/network/GameServer.h"
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

/**
 * Created by LEMMYMAIN on 18/09/2014.
 */
class CharacterSoundEmitter : public BaseCharacterSoundEmitter {
public:
  float currentPriority;
  const FMODSoundEmitter vocals = new FMODSoundEmitter();
  const FMODSoundEmitter footsteps = new FMODSoundEmitter();
  const FMODSoundEmitter extra = new FMODSoundEmitter();
  long footstep1 = 0L;
  long footstep2 = 0L;

public
  CharacterSoundEmitter(IsoGameCharacter chr) {
    super(chr);
    this.vocals.emitterType = EmitterType.Voice;
    this.vocals.parent = this.character;
    this.vocals.parameterUpdater = chr;
    this.footsteps.emitterType = EmitterType.Footstep;
    this.footsteps.parent = this.character;
    this.footsteps.parameterUpdater = chr;
    this.extra.emitterType = EmitterType.Extra;
    this.extra.parent = this.character;
    this.extra.parameterUpdater = chr;
  }

  void register() {
    SoundManager.instance.registerEmitter(this.vocals);
    SoundManager.instance.registerEmitter(this.footsteps);
    SoundManager.instance.registerEmitter(this.extra);
  }

  void unregister() {
    SoundManager.instance.unregisterEmitter(this.vocals);
    SoundManager.instance.unregisterEmitter(this.footsteps);
    SoundManager.instance.unregisterEmitter(this.extra);
  }

  long playVocals(const std::string &file) {
    if (GameServer.bServer) {
      return 0L;
    } else {
      FMODVoice fMODVoice = FMODSoundBank.instance.getVoice(file);
      if (fMODVoice == nullptr) {
        return this.vocals.playSoundImpl(file, false, nullptr);
      } else {
        float float0 = fMODVoice.priority;
        long long0 = this.vocals.playSound(fMODVoice.sound, this.character);
        this.currentPriority = float0;
        return long0;
      }
    }
  }

  CharacterSoundEmitter.footstep getFootstepToPlay() {
    if (FMODManager.instance.getNumListeners() == 1) {
      for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
        IsoPlayer player = IsoPlayer.players[int0];
        if (player != nullptr && player != this.character &&
            !player.Traits.Deaf.isSet()) {
          if ((int)player.getZ() < (int)this.character.getZ()) {
            return CharacterSoundEmitter.footstep.upstairs;
          }
          break;
        }
      }
    }

    IsoObject object = this.character.getCurrentSquare().getFloor();
    if (object != nullptr && object.getSprite() != nullptr &&
        object.getSprite().getName() != nullptr) {
      std::string string = object.getSprite().getName();
      if (string.endsWith("blends_natural_01_5") ||
          string.endsWith("blends_natural_01_6") ||
          string.endsWith("blends_natural_01_7") ||
          string.endsWith("blends_natural_01_0")) {
        return CharacterSoundEmitter.footstep.gravel;
      } else if (string.endsWith("blends_street_01_48") ||
                 string.endsWith("blends_street_01_53") ||
                 string.endsWith("blends_street_01_54") ||
                 string.endsWith("blends_street_01_55")) {
        return CharacterSoundEmitter.footstep.gravel;
      } else if (string.startsWith("blends_natural_01")) {
        return CharacterSoundEmitter.footstep.grass;
      } else if (string.startsWith("floors_interior_tilesandwood_01_")) {
        int int1 = Integer.parseInt(
            string.replaceFirst("floors_interior_tilesandwood_01_", ""));
        return int1 > 40 && int1 < 48 ? CharacterSoundEmitter.footstep.wood
                                      : CharacterSoundEmitter.footstep.concrete;
      } else if (string.startsWith("carpentry_02_")) {
        return CharacterSoundEmitter.footstep.wood;
      } else {
        return string.startsWith("floors_interior_carpet_")
                   ? CharacterSoundEmitter.footstep.wood
                   : CharacterSoundEmitter.footstep.concrete;
      }
    } else {
      return CharacterSoundEmitter.footstep.concrete;
    }
  }

  void playFootsteps(const std::string &file, float volume) {
    if (!GameServer.bServer) {
      bool boolean0 = this.footsteps.isPlaying(this.footstep1);
      bool boolean1 = this.footsteps.isPlaying(this.footstep2);
      if (boolean0 && boolean1) {
        long long0 = this.footstep1;
        this.footstep1 = this.footstep2;
        this.footstep2 = long0;
        if (this.footsteps.restart(this.footstep2)) {
          return;
        }

        this.footsteps.stopSoundLocal(this.footstep2);
        this.footstep2 = 0L;
      } else if (boolean1) {
        this.footstep1 = this.footstep2;
        this.footstep2 = 0L;
        boolean0 = true;
        boolean1 = false;
      }

      long long1 = this.footsteps.playSoundImpl(file, false, null);
      if (!boolean0) {
        this.footstep1 = long1;
      } else {
        this.footstep2 = long1;
      }
    }
  }

  long playSound(const std::string &file) {
    if (this.character.isInvisible() &&
        !DebugOptions.instance.Character.Debug.PlaySoundWhenInvisible
             .getValue()) {
      return 0L;
    } else {
      if (DebugLog.isEnabled(DebugType.Sound)) {
        DebugLog.Sound.debugln(
            "Playing sound: " + file +
            (this.character.isZombie() ? " for zombie" : " for player"));
      }

      return this.extra.playSound(file);
    }
  }

  long playSound(const std::string &file, bool doWorldSound) {
    if (this.character.isInvisible() &&
        !DebugOptions.instance.Character.Debug.PlaySoundWhenInvisible
             .getValue()) {
      return 0L;
    } else {
      if (DebugLog.isEnabled(DebugType.Sound)) {
        DebugLog.Sound.debugln(
            "Playing sound: " + file +
            (this.character.isZombie() ? " for zombie" : " for player"));
      }

      return this.extra.playSound(file, doWorldSound);
    }
  }

  long playSound(const std::string &file, IsoObject proxy) {
    if (this.character.isInvisible() &&
        !DebugOptions.instance.Character.Debug.PlaySoundWhenInvisible
             .getValue()) {
      return 0L;
    } else {
      if (DebugLog.isEnabled(DebugType.Sound)) {
        DebugLog.Sound.debugln(
            "Playing sound: " + file +
            (this.character.isZombie() ? " for zombie" : " for player"));
      }

      return GameServer.bServer ? 0L : this.extra.playSound(file, proxy);
    }
  }

  long playSoundImpl(const std::string &file, IsoObject proxy) {
    if (this.character instanceof IsoPlayer &&
                                      ((IsoPlayer)this.character).bRemote &&
                                      this.character.isInvisible()) {
      return 0L;
    } else {
      if (DebugLog.isEnabled(DebugType.Sound)) {
        DebugLog.Sound.debugln(
            "Playing sound: " + file +
            (this.character.isZombie() ? " for zombie" : " for player"));
      }

      return this.extra.playSoundImpl(file, false, proxy);
    }
  }

  void tick() {
    this.vocals.tick();
    this.footsteps.tick();
    this.extra.tick();
  }

  void setPos(float x, float y, float z) { this.set(x, y, z); }

  void set(float x, float y, float z) {
    this.vocals.x = this.footsteps.x = this.extra.x = x;
    this.vocals.y = this.footsteps.y = this.extra.y = y;
    this.vocals.z = this.footsteps.z = this.extra.z = z;
  }

  bool isEmpty() { return this.isClear(); }

  bool isClear() {
    return this.vocals.isEmpty() && this.footsteps.isEmpty() &&
           this.extra.isEmpty();
  }

  void setPitch(long handle, float pitch) {
    this.extra.setPitch(handle, pitch);
    this.footsteps.setPitch(handle, pitch);
    this.vocals.setPitch(handle, pitch);
  }

  void setVolume(long handle, float volume) {
    this.extra.setVolume(handle, volume);
    this.footsteps.setVolume(handle, volume);
    this.vocals.setVolume(handle, volume);
  }

  bool hasSustainPoints(long handle) {
    if (this.extra.isPlaying(handle)) {
      return this.extra.hasSustainPoints(handle);
    } else if (this.footsteps.isPlaying(handle)) {
      return this.footsteps.hasSustainPoints(handle);
    } else {
      return this.vocals.isPlaying(handle)
                 ? this.vocals.hasSustainPoints(handle)
                 : false;
    }
  }

  void triggerCue(long handle) {
    if (this.extra.isPlaying(handle)) {
      this.extra.triggerCue(handle);
    } else if (this.footsteps.isPlaying(handle)) {
      this.footsteps.triggerCue(handle);
    } else if (this.vocals.isPlaying(handle)) {
      this.vocals.triggerCue(handle);
    }
  }

  int stopSound(long eventInstance) {
    this.extra.stopSound(eventInstance);
    this.footsteps.stopSound(eventInstance);
    this.vocals.stopSound(eventInstance);
    return 0;
  }

  void stopSoundLocal(long handle) {
    this.extra.stopSoundLocal(handle);
    this.footsteps.stopSoundLocal(handle);
    this.vocals.stopSoundLocal(handle);
  }

  void stopOrTriggerSound(long eventInstance) {
    this.extra.stopOrTriggerSound(eventInstance);
    this.footsteps.stopOrTriggerSound(eventInstance);
    this.vocals.stopOrTriggerSound(eventInstance);
  }

  void stopOrTriggerSoundByName(const std::string &name) {
    this.extra.stopOrTriggerSoundByName(name);
    this.footsteps.stopOrTriggerSoundByName(name);
    this.vocals.stopOrTriggerSoundByName(name);
  }

  void stopAll() {
    this.extra.stopAll();
    this.footsteps.stopAll();
    this.vocals.stopAll();
  }

  int stopSoundByName(const std::string &soundName) {
    this.extra.stopSoundByName(soundName);
    this.footsteps.stopSoundByName(soundName);
    this.vocals.stopSoundByName(soundName);
    return 0;
  }

  bool hasSoundsToStart() {
    return this.extra.hasSoundsToStart() || this.footsteps.hasSoundsToStart() ||
           this.vocals.hasSoundsToStart();
  }

  bool isPlaying(long eventInstance) {
    return this.extra.isPlaying(eventInstance) ||
           this.footsteps.isPlaying(eventInstance) ||
           this.vocals.isPlaying(eventInstance);
  }

  bool isPlaying(const std::string &alias) {
    return this.extra.isPlaying(alias) || this.footsteps.isPlaying(alias) ||
           this.vocals.isPlaying(alias);
  }

  void setParameterValue(long soundRef,
                         FMOD_STUDIO_PARAMETER_DESCRIPTION parameterDescription,
                         float value) {
    this.extra.setParameterValue(soundRef, parameterDescription, value);
  }

  static enum footstep { upstairs, grass, wood, concrete, gravel, snow; }
}
} // namespace characters
} // namespace zombie
