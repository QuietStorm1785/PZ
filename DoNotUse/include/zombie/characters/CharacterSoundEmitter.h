#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/EmitterType.h"
#include "fmod/fmod/FMODManager.h"
#include "fmod/fmod/FMODSoundBank.h"
#include "fmod/fmod/FMODSoundEmitter.h"
#include "fmod/fmod/FMODVoice.h"
#include "fmod/fmod/FMOD_STUDIO_PARAMETER_DESCRIPTION.h"
#include "zombie/SoundManager.h"
#include "zombie/characters/CharacterSoundEmitter/footstep.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/debug/DebugType.h"
#include "zombie/interfaces/ICommonSoundEmitter.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/network/GameServer.h"

namespace zombie {
namespace characters {


class CharacterSoundEmitter : public BaseCharacterSoundEmitter {
public:
    float currentPriority;
    const FMODSoundEmitter vocals = std::make_shared<FMODSoundEmitter>();
    const FMODSoundEmitter footsteps = std::make_shared<FMODSoundEmitter>();
    const FMODSoundEmitter extra = std::make_shared<FMODSoundEmitter>();
    long footstep1 = 0L;
    long footstep2 = 0L;

    public CharacterSoundEmitter(IsoGameCharacter var1) {
      super(var1);
      this.vocals.emitterType = EmitterType.Voice;
      this.vocals.parent = this.character;
      this.vocals.parameterUpdater = var1;
      this.footsteps.emitterType = EmitterType.Footstep;
      this.footsteps.parent = this.character;
      this.footsteps.parameterUpdater = var1;
      this.extra.emitterType = EmitterType.Extra;
      this.extra.parent = this.character;
      this.extra.parameterUpdater = var1;
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

    long playVocals(const std::string& var1) {
      if (GameServer.bServer) {
    return 0L;
      } else {
    FMODVoice var2 = FMODSoundBank.instance.getVoice(var1);
         if (var2 == nullptr) {
            return this.vocals.playSoundImpl(var1, false, nullptr);
         } else {
    float var3 = var2.priority;
    long var4 = this.vocals.playSound(var2.sound, this.character);
            this.currentPriority = var3;
    return var4;
         }
      }
   }

    footstep getFootstepToPlay() {
      if (FMODManager.instance.getNumListeners() == 1) {
         for (int var1 = 0; var1 < IsoPlayer.numPlayers; var1++) {
    IsoPlayer var2 = IsoPlayer.players[var1];
            if (var2 != nullptr && var2 != this.character && !var2.Traits.Deaf.isSet()) {
               if ((int)var2.getZ() < (int)this.character.getZ()) {
                  return footstep.upstairs;
               }
               break;
            }
         }
      }

    IsoObject var4 = this.character.getCurrentSquare().getFloor();
      if (var4 != nullptr && var4.getSprite() != nullptr && var4.getSprite().getName() != nullptr) {
    std::string var5 = var4.getSprite().getName();
         if (var5.endsWith("blends_natural_01_5")
            || var5.endsWith("blends_natural_01_6")
            || var5.endsWith("blends_natural_01_7")
            || var5.endsWith("blends_natural_01_0")) {
            return footstep.gravel;
         } else if (var5.endsWith("blends_street_01_48")
            || var5.endsWith("blends_street_01_53")
            || var5.endsWith("blends_street_01_54")
            || var5.endsWith("blends_street_01_55")) {
            return footstep.gravel;
         } else if (var5.startsWith("blends_natural_01")) {
            return footstep.grass;
         } else if (var5.startsWith("floors_interior_tilesandwood_01_")) {
    int var3 = int.parseInt(var5.replaceFirst("floors_interior_tilesandwood_01_", ""));
            return var3 > 40 && var3 < 48 ? footstep.wood : footstep.concrete;
         } else if (var5.startsWith("carpentry_02_")) {
            return footstep.wood;
         } else {
            return var5.startsWith("floors_interior_carpet_") ? footstep.wood : footstep.concrete;
         }
      } else {
         return footstep.concrete;
      }
   }

    void playFootsteps(const std::string& var1, float var2) {
      if (!GameServer.bServer) {
    bool var3 = this.footsteps.isPlaying(this.footstep1);
    bool var4 = this.footsteps.isPlaying(this.footstep2);
         if (var3 && var4) {
    long var5 = this.footstep1;
            this.footstep1 = this.footstep2;
            this.footstep2 = var5;
            if (this.footsteps.restart(this.footstep2)) {
               return;
            }

            this.footsteps.stopSoundLocal(this.footstep2);
            this.footstep2 = 0L;
         } else if (var4) {
            this.footstep1 = this.footstep2;
            this.footstep2 = 0L;
            var3 = true;
            var4 = false;
         }

    long var8 = this.footsteps.playSoundImpl(var1, false, nullptr);
         if (!var3) {
            this.footstep1 = var8;
         } else {
            this.footstep2 = var8;
         }
      }
   }

    long playSound(const std::string& var1) {
      if (this.character.isInvisible() && !DebugOptions.instance.char.Debug.PlaySoundWhenInvisible.getValue()) {
    return 0L;
      } else {
         if (DebugLog.isEnabled(DebugType.Sound)) {
            DebugLog.Sound.debugln("Playing sound: " + var1 + (this.character.isZombie() ? " for zombie" : " for player"));
         }

         return this.extra.playSound(var1);
      }
   }

    long playSound(const std::string& var1, bool var2) {
      if (this.character.isInvisible() && !DebugOptions.instance.char.Debug.PlaySoundWhenInvisible.getValue()) {
    return 0L;
      } else {
         if (DebugLog.isEnabled(DebugType.Sound)) {
            DebugLog.Sound.debugln("Playing sound: " + var1 + (this.character.isZombie() ? " for zombie" : " for player"));
         }

         return this.extra.playSound(var1, var2);
      }
   }

    long playSound(const std::string& var1, IsoObject var2) {
      if (this.character.isInvisible() && !DebugOptions.instance.char.Debug.PlaySoundWhenInvisible.getValue()) {
    return 0L;
      } else {
         if (DebugLog.isEnabled(DebugType.Sound)) {
            DebugLog.Sound.debugln("Playing sound: " + var1 + (this.character.isZombie() ? " for zombie" : " for player"));
         }

         return GameServer.bServer ? 0L : this.extra.playSound(var1, var2);
      }
   }

    long playSoundImpl(const std::string& var1, IsoObject var2) {
      if (this.dynamic_cast<IsoPlayer*>(character) != nullptr && ((IsoPlayer)this.character).bRemote && this.character.isInvisible()) {
    return 0L;
      } else {
         if (DebugLog.isEnabled(DebugType.Sound)) {
            DebugLog.Sound.debugln("Playing sound: " + var1 + (this.character.isZombie() ? " for zombie" : " for player"));
         }

         return this.extra.playSoundImpl(var1, false, var2);
      }
   }

    void tick() {
      this.vocals.tick();
      this.footsteps.tick();
      this.extra.tick();
   }

    void setPos(float var1, float var2, float var3) {
      this.set(var1, var2, var3);
   }

    void set(float var1, float var2, float var3) {
      this.vocals.x = this.footsteps.x = this.extra.x = var1;
      this.vocals.y = this.footsteps.y = this.extra.y = var2;
      this.vocals.z = this.footsteps.z = this.extra.z = var3;
   }

    bool isEmpty() {
      return this.isClear();
   }

    bool isClear() {
      return this.vocals.empty() && this.footsteps.empty() && this.extra.empty();
   }

    void setPitch(long var1, float var3) {
      this.extra.setPitch(var1, var3);
      this.footsteps.setPitch(var1, var3);
      this.vocals.setPitch(var1, var3);
   }

    void setVolume(long var1, float var3) {
      this.extra.setVolume(var1, var3);
      this.footsteps.setVolume(var1, var3);
      this.vocals.setVolume(var1, var3);
   }

    bool hasSustainPoints(long var1) {
      if (this.extra.isPlaying(var1)) {
         return this.extra.hasSustainPoints(var1);
      } else if (this.footsteps.isPlaying(var1)) {
         return this.footsteps.hasSustainPoints(var1);
      } else {
         return this.vocals.isPlaying(var1) ? this.vocals.hasSustainPoints(var1) : false;
      }
   }

    void triggerCue(long var1) {
      if (this.extra.isPlaying(var1)) {
         this.extra.triggerCue(var1);
      } else if (this.footsteps.isPlaying(var1)) {
         this.footsteps.triggerCue(var1);
      } else if (this.vocals.isPlaying(var1)) {
         this.vocals.triggerCue(var1);
      }
   }

    int stopSound(long var1) {
      this.extra.stopSound(var1);
      this.footsteps.stopSound(var1);
      this.vocals.stopSound(var1);
    return 0;
   }

    void stopSoundLocal(long var1) {
      this.extra.stopSoundLocal(var1);
      this.footsteps.stopSoundLocal(var1);
      this.vocals.stopSoundLocal(var1);
   }

    void stopOrTriggerSound(long var1) {
      this.extra.stopOrTriggerSound(var1);
      this.footsteps.stopOrTriggerSound(var1);
      this.vocals.stopOrTriggerSound(var1);
   }

    void stopOrTriggerSoundByName(const std::string& var1) {
      this.extra.stopOrTriggerSoundByName(var1);
      this.footsteps.stopOrTriggerSoundByName(var1);
      this.vocals.stopOrTriggerSoundByName(var1);
   }

    void stopAll() {
      this.extra.stopAll();
      this.footsteps.stopAll();
      this.vocals.stopAll();
   }

    int stopSoundByName(const std::string& var1) {
      this.extra.stopSoundByName(var1);
      this.footsteps.stopSoundByName(var1);
      this.vocals.stopSoundByName(var1);
    return 0;
   }

    bool hasSoundsToStart() {
      return this.extra.hasSoundsToStart() || this.footsteps.hasSoundsToStart() || this.vocals.hasSoundsToStart();
   }

    bool isPlaying(long var1) {
      return this.extra.isPlaying(var1) || this.footsteps.isPlaying(var1) || this.vocals.isPlaying(var1);
   }

    bool isPlaying(const std::string& var1) {
      return this.extra.isPlaying(var1) || this.footsteps.isPlaying(var1) || this.vocals.isPlaying(var1);
   }

    void setParameterValue(long var1, FMOD_STUDIO_PARAMETER_DESCRIPTION var3, float var4) {
      this.extra.setParameterValue(var1, var3, var4);
   }
}
} // namespace characters
} // namespace zombie
