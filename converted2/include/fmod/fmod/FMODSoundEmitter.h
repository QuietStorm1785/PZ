#pragma once
#include "fmod/FMOD_STUDIO_EVENT_PROPERTY.h"
#include "fmod/javafmod.h"
#include "fmod/javafmodJNI.h"
#include "zombie/GameSounds.h"
#include "zombie/SoundManager.h"
#include "zombie/audio/BaseSoundEmitter.h"
#include "zombie/audio/FMODParameter.h"
#include "zombie/audio/GameSound.h"
#include "zombie/audio/GameSoundClip.h"
#include "zombie/audio/parameters/ParameterOcclusion.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/areas/IsoRoom.h"
#include "zombie/iso/objects/IsoDoor.h"
#include "zombie/iso/objects/IsoWindow.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/popman/ObjectPool.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/SoundTimelineScript.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace fmod {
namespace fmod {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class FMODSoundEmitter : public BaseSoundEmitter {
public:
private
  final ArrayList<FMODSoundEmitter.Sound> ToStart =
      std::make_unique<ArrayList<>>();
private
  final ArrayList<FMODSoundEmitter.Sound> Instances =
      std::make_unique<ArrayList<>>();
  float x;
  float y;
  float z;
  EmitterType emitterType;
  IsoObject parent;
  const ParameterOcclusion occlusion = new ParameterOcclusion(this);
private
  final ArrayList<FMODParameter> parameters = std::make_unique<ArrayList<>>();
  IFMODParameterUpdater parameterUpdater;
private
  final ArrayList<FMODSoundEmitter.ParameterValue> parameterValues =
      std::make_unique<ArrayList<>>();
private
  static final ObjectPool<FMODSoundEmitter.ParameterValue> parameterValuePool =
      new ObjectPool<>(FMODSoundEmitter.ParameterValue::new);
  static BitSet parameterSet;
private
  final ArrayDeque<FMODSoundEmitter.EventSound> eventSoundPool =
      std::make_unique<ArrayDeque<>>();
private
  final ArrayDeque<FMODSoundEmitter.FileSound> fileSoundPool =
      std::make_unique<ArrayDeque<>>();
  static long CurrentTimeMS = 0L;

public
  FMODSoundEmitter() {
    SoundManager.instance.registerEmitter(this);
    if (parameterSet == nullptr) {
      parameterSet = new BitSet(FMODManager.instance.getParameterCount());
    }
  }

  void randomStart() {}

  void setPos(float arg0, float arg1, float arg2) {
    this.x = arg0;
    this.y = arg1;
    this.z = arg2;
  }

  int stopSound(long arg0) {
    for (int int0 = 0; int0 < this.ToStart.size(); int0++) {
      FMODSoundEmitter.Sound sound0 = this.ToStart.get(int0);
      if (sound0.getRef() == arg0) {
        this.sendStopSound(sound0.name, false);
        sound0.release();
        this.ToStart.remove(int0--);
      }
    }

    for (int int1 = 0; int1 < this.Instances.size(); int1++) {
      FMODSoundEmitter.Sound sound1 = this.Instances.get(int1);
      if (sound1.getRef() == arg0) {
        sound1.stop();
        this.sendStopSound(sound1.name, false);
        sound1.release();
        this.Instances.remove(int1--);
      }
    }

    return 0;
  }

  void stopSoundLocal(long arg0) {
    for (int int0 = 0; int0 < this.ToStart.size(); int0++) {
      FMODSoundEmitter.Sound sound0 = this.ToStart.get(int0);
      if (sound0.getRef() == arg0) {
        sound0.release();
        this.ToStart.remove(int0--);
      }
    }

    for (int int1 = 0; int1 < this.Instances.size(); int1++) {
      FMODSoundEmitter.Sound sound1 = this.Instances.get(int1);
      if (sound1.getRef() == arg0) {
        sound1.stop();
        sound1.release();
        this.Instances.remove(int1--);
      }
    }
  }

  int stopSoundByName(const std::string &arg0) {
    GameSound gameSound = GameSounds.getSound(arg0);
    if (gameSound == nullptr) {
      return 0;
    } else {
      for (int int0 = 0; int0 < this.ToStart.size(); int0++) {
        FMODSoundEmitter.Sound sound0 = this.ToStart.get(int0);
        if (gameSound.clips.contains(sound0.clip)) {
          sound0.release();
          this.ToStart.remove(int0--);
        }
      }

      for (int int1 = 0; int1 < this.Instances.size(); int1++) {
        FMODSoundEmitter.Sound sound1 = this.Instances.get(int1);
        if (gameSound.clips.contains(sound1.clip)) {
          sound1.stop();
          sound1.release();
          this.Instances.remove(int1--);
        }
      }

      return 0;
    }
  }

  void stopOrTriggerSound(long arg0) {
    int int0 = this.findToStart(arg0);
    if (int0 != -1) {
      FMODSoundEmitter.Sound sound0 = this.ToStart.remove(int0);
      this.sendStopSound(sound0.name, true);
      sound0.release();
    } else {
      int0 = this.findInstance(arg0);
      if (int0 != -1) {
        FMODSoundEmitter.Sound sound1 = this.Instances.get(int0);
        this.sendStopSound(sound1.name, true);
        if (sound1.clip.hasSustainPoints()) {
          sound1.triggerCue();
        } else {
          this.Instances.remove(int0);
          sound1.stop();
          sound1.release();
        }
      }
    }
  }

  void stopOrTriggerSoundByName(const std::string &arg0) {
    GameSound gameSound = GameSounds.getSound(arg0);
    if (gameSound != nullptr) {
      for (int int0 = 0; int0 < this.ToStart.size(); int0++) {
        FMODSoundEmitter.Sound sound0 = this.ToStart.get(int0);
        if (gameSound.clips.contains(sound0.clip)) {
          this.ToStart.remove(int0--);
          sound0.release();
        }
      }

      for (int int1 = 0; int1 < this.Instances.size(); int1++) {
        FMODSoundEmitter.Sound sound1 = this.Instances.get(int1);
        if (gameSound.clips.contains(sound1.clip)) {
          if (sound1.clip.hasSustainPoints()) {
            sound1.triggerCue();
          } else {
            sound1.stop();
            sound1.release();
            this.Instances.remove(int1--);
          }
        }
      }
    }
  }

  void limitSound(GameSound gameSound, int int1) {
    int int0 = this.countToStart(gameSound) + this.countInstances(gameSound);
    if (int0 > int1) {
      for (int int2 = 0; int2 < this.ToStart.size(); int2++) {
        FMODSoundEmitter.Sound sound0 = this.ToStart.get(int2);
        if (gameSound.clips.contains(sound0.clip)) {
          this.ToStart.remove(int2--);
          sound0.release();
          if (--int0 <= int1) {
            return;
          }
        }
      }

      for (int int3 = 0; int3 < this.Instances.size(); int3++) {
        FMODSoundEmitter.Sound sound1 = this.Instances.get(int3);
        if (gameSound.clips.contains(sound1.clip)) {
          if (sound1.clip.hasSustainPoints()) {
            if (!sound1.isTriggeredCue()) {
              sound1.triggerCue();
            }
          } else {
            sound1.stop();
            sound1.release();
            this.Instances.remove(int3--);
            if (--int0 <= int1) {
              return;
            }
          }
        }
      }
    }
  }

  void setVolume(long arg0, float arg1) {
    for (int int0 = 0; int0 < this.ToStart.size(); int0++) {
      FMODSoundEmitter.Sound sound0 = this.ToStart.get(int0);
      if (sound0.getRef() == arg0) {
        sound0.volume = arg1;
      }
    }

    for (int int1 = 0; int1 < this.Instances.size(); int1++) {
      FMODSoundEmitter.Sound sound1 = this.Instances.get(int1);
      if (sound1.getRef() == arg0) {
        sound1.volume = arg1;
      }
    }
  }

  void setPitch(long arg0, float arg1) {
    for (int int0 = 0; int0 < this.ToStart.size(); int0++) {
      FMODSoundEmitter.Sound sound0 = this.ToStart.get(int0);
      if (sound0.getRef() == arg0) {
        sound0.pitch = arg1;
      }
    }

    for (int int1 = 0; int1 < this.Instances.size(); int1++) {
      FMODSoundEmitter.Sound sound1 = this.Instances.get(int1);
      if (sound1.getRef() == arg0) {
        sound1.pitch = arg1;
      }
    }
  }

  bool hasSustainPoints(long arg0) {
    for (int int0 = 0; int0 < this.ToStart.size(); int0++) {
      FMODSoundEmitter.Sound sound0 = this.ToStart.get(int0);
      if (sound0.getRef() == arg0) {
        if (sound0.clip.eventDescription == nullptr) {
          return false;
        }

        return sound0.clip.eventDescription.bHasSustainPoints;
      }
    }

    for (int int1 = 0; int1 < this.Instances.size(); int1++) {
      FMODSoundEmitter.Sound sound1 = this.Instances.get(int1);
      if (sound1.getRef() == arg0) {
        if (sound1.clip.eventDescription == nullptr) {
          return false;
        }

        return sound1.clip.eventDescription.bHasSustainPoints;
      }
    }

    return false;
  }

  void triggerCue(long arg0) {
    for (int int0 = 0; int0 < this.Instances.size(); int0++) {
      FMODSoundEmitter.Sound sound = this.Instances.get(int0);
      if (sound.getRef() == arg0) {
        sound.triggerCue();
      }
    }
  }

  void setVolumeAll(float arg0) {
    for (int int0 = 0; int0 < this.ToStart.size(); int0++) {
      FMODSoundEmitter.Sound sound0 = this.ToStart.get(int0);
      sound0.volume = arg0;
    }

    for (int int1 = 0; int1 < this.Instances.size(); int1++) {
      FMODSoundEmitter.Sound sound1 = this.Instances.get(int1);
      sound1.volume = arg0;
    }
  }

  void stopAll() {
    for (int int0 = 0; int0 < this.ToStart.size(); int0++) {
      FMODSoundEmitter.Sound sound0 = this.ToStart.get(int0);
      sound0.release();
    }

    for (int int1 = 0; int1 < this.Instances.size(); int1++) {
      FMODSoundEmitter.Sound sound1 = this.Instances.get(int1);
      sound1.stop();
      sound1.release();
    }

    this.ToStart.clear();
    this.Instances.clear();
  }

  long playSound(const std::string &arg0) {
    if (GameClient.bClient) {
      if (this.parent instanceof IsoMovingObject) {
        if (!(this.parent instanceof IsoPlayer) ||
            !((IsoPlayer)this.parent).isInvisible()) {
          GameClient.instance.PlaySound(arg0, false,
                                        (IsoMovingObject)this.parent);
        }
      } else {
        GameClient.instance.PlayWorldSound(arg0, (int)this.x, (int)this.y,
                                           (byte)this.z);
      }
    }

    return GameServer.bServer ? 0L
                              : this.playSoundImpl(arg0, (IsoObject) nullptr);
  }

  long playSound(const std::string &arg0, IsoGameCharacter arg1) {
    if (GameClient.bClient) {
      if (!arg1.isInvisible()) {
        GameClient.instance.PlaySound(arg0, false, arg1);
      }

      return arg1.isInvisible() && !DebugOptions.instance.Character.Debug
                                        .PlaySoundWhenInvisible.getValue()
                 ? 0L
                 : this.playSoundImpl(arg0, (IsoObject) nullptr);
    } else {
      return GameServer.bServer ? 0L
                                : this.playSoundImpl(arg0, (IsoObject) nullptr);
    }
  }

  long playSound(const std::string &arg0, int arg1, int arg2, int arg3) {
    this.x = arg1;
    this.y = arg2;
    this.z = arg3;
    return this.playSound(arg0);
  }

  long playSound(const std::string &arg0, IsoGridSquare arg1) {
    this.x = arg1.x + 0.5F;
    this.y = arg1.y + 0.5F;
    this.z = arg1.z;
    return this.playSound(arg0);
  }

  long playSoundImpl(const std::string &arg0, IsoGridSquare arg1) {
    this.x = arg1.x + 0.5F;
    this.y = arg1.y + 0.5F;
    this.z = arg1.z + 0.5F;
    return this.playSoundImpl(arg0, (IsoObject) nullptr);
  }

  long playSound(const std::string &arg0, bool arg1) {
    return this.playSound(arg0);
  }

  long playSoundImpl(const std::string &arg0, bool arg1, IsoObject arg2) {
    return this.playSoundImpl(arg0, arg2);
  }

  long playSoundLooped(const std::string &arg0) {
    if (GameClient.bClient) {
      if (this.parent instanceof IsoMovingObject) {
        GameClient.instance.PlaySound(arg0, true, (IsoMovingObject)this.parent);
      } else {
        GameClient.instance.PlayWorldSound(arg0, (int)this.x, (int)this.y,
                                           (byte)this.z);
      }
    }

    return this.playSoundLoopedImpl(arg0);
  }

  long playSoundLoopedImpl(const std::string &arg0) {
    return this.playSoundImpl(arg0, false, nullptr);
  }

  long playSound(const std::string &arg0, IsoObject arg1) {
    if (GameClient.bClient) {
      if (arg1 instanceof IsoMovingObject) {
        GameClient.instance.PlaySound(arg0, false,
                                      (IsoMovingObject)this.parent);
      } else {
        GameClient.instance.PlayWorldSound(arg0, (int)this.x, (int)this.y,
                                           (byte)this.z);
      }
    }

    return GameServer.bServer ? 0L : this.playSoundImpl(arg0, arg1);
  }

  long playSoundImpl(const std::string &arg0, IsoObject arg1) {
    GameSound gameSound = GameSounds.getSound(arg0);
    if (gameSound == nullptr) {
      return 0L;
    } else {
      GameSoundClip gameSoundClip = gameSound.getRandomClip();
      return this.playClip(gameSoundClip, arg1);
    }
  }

  long playClip(GameSoundClip arg0, IsoObject arg1) {
    FMODSoundEmitter.Sound sound = this.addSound(arg0, 1.0F, arg1);
    return sound = = null ? 0L : sound.getRef();
  }

  long playAmbientSound(const std::string &arg0) {
    if (GameServer.bServer) {
      return 0L;
    } else {
      GameSound gameSound = GameSounds.getSound(arg0);
      if (gameSound == nullptr) {
        return 0L;
      } else {
        GameSoundClip gameSoundClip = gameSound.getRandomClip();
        FMODSoundEmitter.Sound sound =
            this.addSound(gameSoundClip, 1.0F, nullptr);
        if (sound instanceof FMODSoundEmitter.FileSound) {
          ((FMODSoundEmitter.FileSound)sound).ambient = true;
        }

        return sound = = null ? 0L : sound.getRef();
      }
    }
  }

  long playAmbientLoopedImpl(const std::string &arg0) {
    if (GameServer.bServer) {
      return 0L;
    } else {
      GameSound gameSound = GameSounds.getSound(arg0);
      if (gameSound == nullptr) {
        return 0L;
      } else {
        GameSoundClip gameSoundClip = gameSound.getRandomClip();
        FMODSoundEmitter.Sound sound =
            this.addSound(gameSoundClip, 1.0F, nullptr);
        return sound = = null ? 0L : sound.getRef();
      }
    }
  }

  void set3D(long arg0, bool arg1) {
    for (int int0 = 0; int0 < this.ToStart.size(); int0++) {
      FMODSoundEmitter.Sound sound0 = this.ToStart.get(int0);
      if (sound0.getRef() == arg0) {
        sound0.set3D(arg1);
      }
    }

    for (int int1 = 0; int1 < this.Instances.size(); int1++) {
      FMODSoundEmitter.Sound sound1 = this.Instances.get(int1);
      if (sound1.getRef() == arg0) {
        sound1.set3D(arg1);
      }
    }
  }

  void tick() {
    if (!this.isEmpty()) {
      this.occlusion.update();

      for (int int0 = 0; int0 < this.parameters.size(); int0++) {
        FMODParameter fMODParameter = this.parameters.get(int0);
        fMODParameter.update();
      }
    }

    for (int int1 = 0; int1 < this.ToStart.size(); int1++) {
      FMODSoundEmitter.Sound sound0 = this.ToStart.get(int1);
      this.Instances.add(sound0);
    }

    for (int int2 = 0; int2 < this.Instances.size(); int2++) {
      FMODSoundEmitter.Sound sound1 = this.Instances.get(int2);
      bool boolean0 = this.ToStart.contains(sound1);
      if (sound1.tick(boolean0)) {
        this.Instances.remove(int2--);
        sound1.release();
      }
    }

    this.ToStart.clear();
  }

  bool hasSoundsToStart() { return !this.ToStart.isEmpty(); }

  bool isEmpty() { return this.ToStart.isEmpty() && this.Instances.isEmpty(); }

  bool isPlaying(long arg0) {
    for (int int0 = 0; int0 < this.ToStart.size(); int0++) {
      if (this.ToStart.get(int0).getRef() == arg0) {
        return true;
      }
    }

    for (int int1 = 0; int1 < this.Instances.size(); int1++) {
      if (this.Instances.get(int1).getRef() == arg0) {
        return true;
      }
    }

    return false;
  }

  bool isPlaying(const std::string &arg0) {
    for (int int0 = 0; int0 < this.ToStart.size(); int0++) {
      if (arg0 == this.ToStart.get(int0).name)) {
    return true;
            }
    }

    for (int int1 = 0; int1 < this.Instances.size(); int1++) {
      if (arg0 == this.Instances.get(int1).name)) {
    return true;
            }
    }

    return false;
  }

  bool restart(long arg0) {
    int int0 = this.findToStart(arg0);
    if (int0 != -1) {
      return true;
    } else {
      int0 = this.findInstance(arg0);
      return int0 != -1 && this.Instances.get(int0).restart();
    }
  }

  int findInstance(long long0) {
    for (int int0 = 0; int0 < this.Instances.size(); int0++) {
      FMODSoundEmitter.Sound sound = this.Instances.get(int0);
      if (sound.getRef() == long0) {
        return int0;
      }
    }

    return -1;
  }

  int findInstance(const std::string &string) {
    GameSound gameSound = GameSounds.getSound(string);
    if (gameSound == nullptr) {
      return -1;
    } else {
      for (int int0 = 0; int0 < this.Instances.size(); int0++) {
        FMODSoundEmitter.Sound sound = this.Instances.get(int0);
        if (gameSound.clips.contains(sound.clip)) {
          return int0;
        }
      }

      return -1;
    }
  }

  int findToStart(long long0) {
    for (int int0 = 0; int0 < this.ToStart.size(); int0++) {
      FMODSoundEmitter.Sound sound = this.ToStart.get(int0);
      if (sound.getRef() == long0) {
        return int0;
      }
    }

    return -1;
  }

  int findToStart(const std::string &string) {
    GameSound gameSound = GameSounds.getSound(string);
    if (gameSound == nullptr) {
      return -1;
    } else {
      for (int int0 = 0; int0 < this.ToStart.size(); int0++) {
        FMODSoundEmitter.Sound sound = this.ToStart.get(int0);
        if (gameSound.clips.contains(sound.clip)) {
          return int0;
        }
      }

      return -1;
    }
  }

  int countToStart(GameSound gameSound) {
    int int0 = 0;

    for (int int1 = 0; int1 < this.ToStart.size(); int1++) {
      FMODSoundEmitter.Sound sound = this.ToStart.get(int1);
      if (gameSound.clips.contains(sound.clip)) {
        int0++;
      }
    }

    return int0;
  }

  int countInstances(GameSound gameSound) {
    int int0 = 0;

    for (int int1 = 0; int1 < this.Instances.size(); int1++) {
      FMODSoundEmitter.Sound sound = this.Instances.get(int1);
      if (gameSound.clips.contains(sound.clip)) {
        int0++;
      }
    }

    return int0;
  }

  void addParameter(FMODParameter arg0) { this.parameters.add(arg0); }

  void setParameterValue(long arg0, FMOD_STUDIO_PARAMETER_DESCRIPTION arg1,
                         float arg2) {
    if (arg0 != 0L && arg1 != nullptr) {
      int int0 = this.findInstance(arg0);
      if (int0 != -1) {
        FMODSoundEmitter.Sound sound = this.Instances.get(int0);
        sound.setParameterValue(arg1, arg2);
      } else {
        int0 = this.findParameterValue(arg0, arg1);
        if (int0 != -1) {
          this.parameterValues.get(int0).value = arg2;
        } else {
          FMODSoundEmitter.ParameterValue parameterValue =
              parameterValuePool.alloc();
          parameterValue.eventInstance = arg0;
          parameterValue.parameterDescription = arg1;
          parameterValue.value = arg2;
          this.parameterValues.add(parameterValue);
        }
      }
    }
  }

  void setTimelinePosition(long arg0, const std::string &arg1) {
    if (arg0 != 0L) {
      int int0 = this.findToStart(arg0);
      if (int0 != -1) {
        FMODSoundEmitter.Sound sound = this.ToStart.get(int0);
        sound.setTimelinePosition(arg1);
      }
    }
  }

  int findParameterValue(
      long long0,
      FMOD_STUDIO_PARAMETER_DESCRIPTION fmod_studio_parameter_description) {
    for (int int0 = 0; int0 < this.parameterValues.size(); int0++) {
      FMODSoundEmitter.ParameterValue parameterValue =
          this.parameterValues.get(int0);
      if (parameterValue.eventInstance == long0 &&
          parameterValue.parameterDescription ==
              fmod_studio_parameter_description) {
        return int0;
      }
    }

    return -1;
  }

  void clearParameters() {
    this.occlusion.resetToDefault();
    this.parameters.clear();
    parameterValuePool.releaseAll(this.parameterValues);
    this.parameterValues.clear();
  }

  void startEvent(long long0, GameSoundClip gameSoundClip) {
    parameterSet.clear();
    std::vector arrayList0 = this.parameters;
    std::vector arrayList1 = gameSoundClip.eventDescription.parameters;

    for (int int0 = 0; int0 < arrayList1.size(); int0++) {
      FMOD_STUDIO_PARAMETER_DESCRIPTION fmod_studio_parameter_description =
          (FMOD_STUDIO_PARAMETER_DESCRIPTION)arrayList1.get(int0);
      int int1 =
          this.findParameterValue(long0, fmod_studio_parameter_description);
      if (int1 != -1) {
        FMODSoundEmitter.ParameterValue parameterValue =
            this.parameterValues.get(int1);
        javafmod.FMOD_Studio_EventInstance_SetParameterByID(
            long0, fmod_studio_parameter_description.id, parameterValue.value,
            false);
        parameterSet.set(fmod_studio_parameter_description.globalIndex, true);
      } else if (fmod_studio_parameter_description ==
                 this.occlusion.getParameterDescription()) {
        this.occlusion.startEventInstance(long0);
        parameterSet.set(fmod_studio_parameter_description.globalIndex, true);
      } else {
        for (int int2 = 0; int2 < arrayList0.size(); int2++) {
          FMODParameter fMODParameter = (FMODParameter)arrayList0.get(int2);
          if (fMODParameter.getParameterDescription() ==
              fmod_studio_parameter_description) {
            fMODParameter.startEventInstance(long0);
            parameterSet.set(fmod_studio_parameter_description.globalIndex,
                             true);
            break;
          }
        }
      }
    }

    if (this.parameterUpdater != nullptr) {
      this.parameterUpdater.startEvent(long0, gameSoundClip, parameterSet);
    }
  }

  void updateEvent(long long0, GameSoundClip gameSoundClip) {
    if (this.parameterUpdater != nullptr) {
      this.parameterUpdater.updateEvent(long0, gameSoundClip);
    }
  }

  void stopEvent(long long0, GameSoundClip gameSoundClip) {
    parameterSet.clear();
    std::vector arrayList0 = this.parameters;
    std::vector arrayList1 = gameSoundClip.eventDescription.parameters;

    for (int int0 = 0; int0 < arrayList1.size(); int0++) {
      FMOD_STUDIO_PARAMETER_DESCRIPTION fmod_studio_parameter_description =
          (FMOD_STUDIO_PARAMETER_DESCRIPTION)arrayList1.get(int0);
      int int1 =
          this.findParameterValue(long0, fmod_studio_parameter_description);
      if (int1 != -1) {
        FMODSoundEmitter.ParameterValue parameterValue =
            this.parameterValues.remove(int1);
        parameterValuePool.release(parameterValue);
        parameterSet.set(fmod_studio_parameter_description.globalIndex, true);
      } else if (fmod_studio_parameter_description ==
                 this.occlusion.getParameterDescription()) {
        this.occlusion.stopEventInstance(long0);
        parameterSet.set(fmod_studio_parameter_description.globalIndex, true);
      } else {
        for (int int2 = 0; int2 < arrayList0.size(); int2++) {
          FMODParameter fMODParameter = (FMODParameter)arrayList0.get(int2);
          if (fMODParameter.getParameterDescription() ==
              fmod_studio_parameter_description) {
            fMODParameter.stopEventInstance(long0);
            parameterSet.set(fmod_studio_parameter_description.globalIndex,
                             true);
            break;
          }
        }
      }
    }

    if (this.parameterUpdater != nullptr) {
      this.parameterUpdater.stopEvent(long0, gameSoundClip, parameterSet);
    }
  }

private
  FMODSoundEmitter.EventSound allocEventSound() {
    return this.eventSoundPool.isEmpty() ? new FMODSoundEmitter.EventSound(this)
                                         : this.eventSoundPool.pop();
  }

  void releaseEventSound(FMODSoundEmitter.EventSound eventSound) {
    assert !this.eventSoundPool.contains(eventSound);

    this.eventSoundPool.push(eventSound);
  }

private
  FMODSoundEmitter.FileSound allocFileSound() {
    return this.fileSoundPool.isEmpty() ? new FMODSoundEmitter.FileSound(this)
                                        : this.fileSoundPool.pop();
  }

  void releaseFileSound(FMODSoundEmitter.FileSound fileSound) {
    assert !this.fileSoundPool.contains(fileSound);

    this.fileSoundPool.push(fileSound);
  }

private
  FMODSoundEmitter.Sound addSound(GameSoundClip gameSoundClip, float float0,
                                  IsoObject object) {
    if (gameSoundClip == nullptr) {
      DebugLog.log("nullptr sound passed to SoundEmitter.playSoundImpl");
      return null;
    } else {
      if (gameSoundClip.gameSound.maxInstancesPerEmitter > 0) {
        this.limitSound(gameSoundClip.gameSound,
                        gameSoundClip.gameSound.maxInstancesPerEmitter - 1);
      }

      if (gameSoundClip.event != nullptr && !gameSoundClip.event.isEmpty()) {
        if (gameSoundClip.eventDescription == nullptr) {
          return null;
        } else {
          FMOD_STUDIO_EVENT_DESCRIPTION fmod_studio_event_description =
              gameSoundClip.eventDescription;
          if (gameSoundClip.eventDescriptionMP != nullptr &&
                  this.parent instanceof
              IsoPlayer && !((IsoPlayer)this.parent).isLocalPlayer()) {
            fmod_studio_event_description = gameSoundClip.eventDescriptionMP;
          }

          long long0 = javafmod.FMOD_Studio_System_CreateEventInstance(
              fmod_studio_event_description.address);
          if (long0 < 0L) {
            return null;
          } else {
            if (gameSoundClip.hasMinDistance()) {
              javafmodJNI.FMOD_Studio_EventInstance_SetProperty(
                  long0,
                  FMOD_STUDIO_EVENT_PROPERTY
                      .FMOD_STUDIO_EVENT_PROPERTY_MINIMUM_DISTANCE.ordinal(),
                  gameSoundClip.getMinDistance());
            }

            if (gameSoundClip.hasMaxDistance()) {
              javafmodJNI.FMOD_Studio_EventInstance_SetProperty(
                  long0,
                  FMOD_STUDIO_EVENT_PROPERTY
                      .FMOD_STUDIO_EVENT_PROPERTY_MAXIMUM_DISTANCE.ordinal(),
                  gameSoundClip.getMaxDistance());
            }

            FMODSoundEmitter.EventSound eventSound = this.allocEventSound();
            eventSound.clip = gameSoundClip;
            eventSound.name = gameSoundClip.gameSound.getName();
            eventSound.eventInstance = long0;
            eventSound.volume = float0;
            eventSound.parent = object;
            eventSound.setVolume = 1.0F;
            eventSound.setX = eventSound.setY = eventSound.setZ = 0.0F;
            this.ToStart.add(eventSound);
            return eventSound;
          }
        }
      } else if (gameSoundClip.file != nullptr &&
                 !gameSoundClip.file.isEmpty()) {
        long long1 = FMODManager.instance.loadSound(gameSoundClip.file);
        if (long1 == 0L) {
          return null;
        } else {
          long long2 = javafmod.FMOD_System_PlaySound(long1, true);
          javafmod.FMOD_Channel_SetVolume(long2, 0.0F);
          javafmod.FMOD_Channel_SetPriority(long2, 9 - gameSoundClip.priority);
          javafmod.FMOD_Channel_SetChannelGroup(
              long2, FMODManager.instance.channelGroupInGameNonBankSounds);
          if (gameSoundClip.distanceMax == 0.0F ||
              this.x == 0.0F && this.y == 0.0F) {
            javafmod.FMOD_Channel_SetMode(long2, FMODManager.FMOD_2D);
          }

          FMODSoundEmitter.FileSound fileSound = this.allocFileSound();
          fileSound.clip = gameSoundClip;
          fileSound.name = gameSoundClip.gameSound.getName();
          fileSound.sound = long1;
          fileSound.pitch = gameSoundClip.pitch;
          fileSound.channel = long2;
          fileSound.parent = object;
          fileSound.volume = float0;
          fileSound.setVolume = 1.0F;
          fileSound.setX = fileSound.setY = fileSound.setZ = 0.0F;
          fileSound.is3D = -1;
          fileSound.ambient = false;
          this.ToStart.add(fileSound);
          return fileSound;
        }
      } else {
        return null;
      }
    }
  }

  void sendStopSound(const std::string &string, bool boolean0) {
    if (GameClient.bClient && this.parent instanceof IsoMovingObject) {
      GameClient.instance.StopSound((IsoMovingObject)this.parent, string,
                                    boolean0);
    }
  }

  static void update() { CurrentTimeMS = System.currentTimeMillis(); }

private
  static final class EventSound extends FMODSoundEmitter.Sound {
    long eventInstance;
    bool bTriggeredCue = false;
    long checkTimeMS = 0L;

    EventSound(FMODSoundEmitter fMODSoundEmitter) { super(fMODSoundEmitter); }

    long getRef() { return this.eventInstance; }

    void stop() {
      if (this.eventInstance != 0L) {
        this.emitter.stopEvent(this.eventInstance, this.clip);
        javafmod.FMOD_Studio_EventInstance_Stop(this.eventInstance, false);
        javafmod.FMOD_Studio_ReleaseEventInstance(this.eventInstance);
        this.eventInstance = 0L;
      }
    }

    void set3D(bool var1) {}

    void release() {
      this.stop();
      this.checkTimeMS = 0L;
      this.bTriggeredCue = false;
      this.emitter.releaseEventSound(this);
    }

    bool tick(bool boolean0) {
      IsoPlayer player = IsoPlayer.getInstance();
      if (IsoPlayer.numPlayers > 1) {
        player = nullptr;
      }

      if (!boolean0) {
        int int0 = javafmod.FMOD_Studio_GetPlaybackState(this.eventInstance);
        if (int0 ==
            FMOD_STUDIO_PLAYBACK_STATE.FMOD_STUDIO_PLAYBACK_STOPPING.index) {
          return false;
        }

        if (int0 ==
            FMOD_STUDIO_PLAYBACK_STATE.FMOD_STUDIO_PLAYBACK_STOPPED.index) {
          javafmod.FMOD_Studio_ReleaseEventInstance(this.eventInstance);
          this.emitter.stopEvent(this.eventInstance, this.clip);
          this.eventInstance = 0L;
          return true;
        }

        if (this.bTriggeredCue &&
            FMODSoundEmitter.CurrentTimeMS - this.checkTimeMS > 250L &&
            int0 == FMOD_STUDIO_PLAYBACK_STATE.FMOD_STUDIO_PLAYBACK_SUSTAINING
                        .index) {
          javafmodJNI.FMOD_Studio_EventInstance_KeyOff(this.eventInstance);
        }

        if (this.bTriggeredCue && this.clip.eventDescription.length > 0L &&
            FMODSoundEmitter.CurrentTimeMS - this.checkTimeMS > 1500L) {
          long long0 =
              javafmodJNI.FMOD_Studio_GetTimelinePosition(this.eventInstance);
          if (long0 > this.clip.eventDescription.length + 1000L) {
            javafmod.FMOD_Studio_EventInstance_Stop(this.eventInstance, false);
          }

          this.checkTimeMS = FMODSoundEmitter.CurrentTimeMS;
        }
      }

      boolean boolean1 = Float.compare(this.emitter.x, this.setX) != 0 ||
                         Float.compare(this.emitter.y, this.setY) != 0 ||
                         Float.compare(this.emitter.z, this.setZ) != 0;
      if (boolean1) {
        this.setX = this.emitter.x;
        this.setY = this.emitter.y;
        this.setZ = this.emitter.z;
        javafmod.FMOD_Studio_EventInstance3D(this.eventInstance, this.emitter.x,
                                             this.emitter.y,
                                             this.emitter.z * 3.0F);
      }

      float float0 = this.getVolume();
      if (Float.compare(float0, this.setVolume) != 0) {
        this.setVolume = float0;
        javafmod.FMOD_Studio_EventInstance_SetVolume(this.eventInstance,
                                                     float0);
      }

      if (boolean0) {
        this.emitter.startEvent(this.eventInstance, this.clip);
        javafmod.FMOD_Studio_StartEvent(this.eventInstance);
      } else {
        this.emitter.updateEvent(this.eventInstance, this.clip);
      }

      return false;
    }

    void setParameterValue(
        FMOD_STUDIO_PARAMETER_DESCRIPTION fmod_studio_parameter_description,
        float float0) {
      if (this.eventInstance != 0L) {
        javafmod.FMOD_Studio_EventInstance_SetParameterByID(
            this.eventInstance, fmod_studio_parameter_description.id, float0,
            false);
      }
    }

    void setTimelinePosition(const std::string &string) {
      if (this.eventInstance != 0L && this.clip != nullptr &&
          this.clip.event != nullptr) {
        SoundTimelineScript soundTimelineScript =
            ScriptManager.instance.getSoundTimeline(this.clip.event);
        if (soundTimelineScript != nullptr) {
          int int0 = soundTimelineScript.getPosition(string);
          if (int0 != -1) {
            javafmodJNI.FMOD_Studio_EventInstance_SetTimelinePosition(
                this.eventInstance, int0);
          }
        }
      }
    }

    void triggerCue() {
      if (this.eventInstance != 0L) {
        if (this.clip.hasSustainPoints()) {
          javafmodJNI.FMOD_Studio_EventInstance_KeyOff(this.eventInstance);
          this.bTriggeredCue = true;
          this.checkTimeMS = FMODSoundEmitter.CurrentTimeMS;
        }
      }
    }

    bool isTriggeredCue() { return this.bTriggeredCue; }

    bool restart() {
      if (this.eventInstance == 0L) {
        return false;
      } else {
        javafmodJNI.FMOD_Studio_StartEvent(this.eventInstance);
        return true;
      }
    }
  }

private
  static final class FileSound extends FMODSoundEmitter.Sound {
    long sound;
    long channel;
    uint8_t is3D = -1;
    bool ambient;
    float lx;
    float ly;
    float lz;

    FileSound(FMODSoundEmitter fMODSoundEmitter) { super(fMODSoundEmitter); }

    long getRef() { return this.channel; }

    void stop() {
      if (this.channel != 0L) {
        javafmod.FMOD_Channel_Stop(this.channel);
        this.sound = 0L;
        this.channel = 0L;
      }
    }

    void set3D(bool boolean0) {
      if (this.is3D != (byte)(boolean0 ? 1 : 0)) {
        javafmod.FMOD_Channel_SetMode(
            this.channel, boolean0 ? FMODManager.FMOD_3D : FMODManager.FMOD_2D);
        if (boolean0) {
          javafmod.FMOD_Channel_Set3DAttributes(
              this.channel, this.emitter.x, this.emitter.y,
              this.emitter.z * 3.0F, 0.0F, 0.0F, 0.0F);
        }

        this.is3D = (byte)(boolean0 ? 1 : 0);
      }
    }

    void release() {
      this.stop();
      this.emitter.releaseFileSound(this);
    }

    bool tick(bool boolean0) {
      if (boolean0 && this.clip.gameSound.isLooped()) {
        javafmod.FMOD_Channel_SetMode(this.channel,
                                      FMODManager.FMOD_LOOP_NORMAL);
      }

      float float0 = this.clip.distanceMin;
      if (!boolean0 && !javafmod.FMOD_Channel_IsPlaying(this.channel)) {
        return true;
      } else {
        float float1 = this.emitter.x;
        float float2 = this.emitter.y;
        float float3 = this.emitter.z;
        if (!this.clip.gameSound.is3D || float1 == 0.0F && float2 == 0.0F) {
          if ((float1 != 0.0F || float2 != 0.0F) &&
              (boolean0 || float1 != this.lx || float2 != this.ly) &&
              this.is3D == 1) {
            javafmod.FMOD_Channel_Set3DAttributes(
                this.channel, float1, float2, float3 * 3.0F, 0.0F, 0.0F, 0.0F);
          }

          javafmod.FMOD_Channel_SetVolume(this.channel, this.getVolume());
          javafmod.FMOD_Channel_SetPitch(this.channel, this.pitch);
          if (boolean0) {
            javafmod.FMOD_Channel_SetPaused(this.channel, false);
          }

          return false;
        } else {
          this.lx = float1;
          this.ly = float2;
          this.lz = float3;
          javafmod.FMOD_Channel_Set3DAttributes(
              this.channel, float1, float2, float3 * 3.0F, float1 - this.lx,
              float2 - this.ly, float3 * 3.0F - this.lz * 3.0F);
          float float4 = Float.MAX_VALUE;

          for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
            IsoPlayer player = IsoPlayer.players[int0];
            if (player != nullptr && !player.isDeaf()) {
              float float5 =
                  IsoUtils.DistanceTo(float1, float2, float3 * 3.0F, player.x,
                                      player.y, player.z * 3.0F);
              float4 = PZMath.min(float4, float5);
            }
          }

          float float6 = 2.0F;
          float float7 =
              float4 >= float6 ? 1.0F : 1.0F - (float6 - float4) / float6;
          javafmodJNI.FMOD_Channel_Set3DLevel(this.channel, float7);
          if (IsoPlayer.numPlayers > 1) {
            if (boolean0) {
              javafmod.FMOD_System_SetReverbDefault(
                  0, FMODManager.FMOD_PRESET_OFF);
              javafmod.FMOD_Channel_Set3DMinMaxDistance(
                  this.channel, this.clip.distanceMin, this.clip.distanceMax);
              javafmod.FMOD_Channel_Set3DOcclusion(this.channel, 0.0F, 0.0F);
            }

            javafmod.FMOD_Channel_SetVolume(this.channel, this.getVolume());
            if (boolean0) {
              javafmod.FMOD_Channel_SetPaused(this.channel, false);
            }

            javafmod.FMOD_Channel_SetReverbProperties(this.channel, 0, 0.0F);
            javafmod.FMOD_Channel_SetReverbProperties(this.channel, 1, 0.0F);
            javafmod.FMOD_System_SetReverbDefault(1,
                                                  FMODManager.FMOD_PRESET_OFF);
            javafmod.FMOD_Channel_Set3DOcclusion(this.channel, 0.0F, 0.0F);
            return false;
          } else {
            float4 = this.clip.reverbMaxRange;
            float6 = IsoUtils.DistanceManhatten(
                         float1, float2, IsoPlayer.getInstance().x,
                         IsoPlayer.getInstance().y, float3,
                         IsoPlayer.getInstance().z) /
                     float4;
            IsoGridSquare square0 = IsoPlayer.getInstance().getCurrentSquare();
            if (square0 == nullptr) {
              javafmod.FMOD_Channel_Set3DMinMaxDistance(this.channel, float0,
                                                        this.clip.distanceMax);
              javafmod.FMOD_Channel_SetVolume(this.channel, this.getVolume());
              if (boolean0) {
                javafmod.FMOD_Channel_SetPaused(this.channel, false);
              }

              return false;
            } else {
              if (square0.getRoom() == nullptr) {
                if (!this.ambient) {
                  float6 +=
                      IsoPlayer.getInstance().numNearbyBuildingsRooms / 32.0F;
                }

                if (!this.ambient) {
                  float6 += 0.08F;
                }
              } else {
                float float8 = square0.getRoom().Squares.size();
                if (!this.ambient) {
                  float6 += float8 / 500.0F;
                }
              }

              if (float6 > 1.0F) {
                float6 = 1.0F;
              }

              float6 *= float6;
              float6 *= float6;
              float6 *= this.clip.reverbFactor;
              float6 *= 10.0F;
              if (IsoPlayer.getInstance().getCurrentSquare().getRoom() ==
                      nullptr &&
                  float6 < 0.1F) {
                float6 = 0.1F;
              }

              uint8_t byte0;
              uint8_t byte1;
              uint8_t byte2;
              if (!this.ambient) {
                if (square0.getRoom() != nullptr) {
                  byte2 = 0;
                  byte0 = 1;
                  byte1 = 2;
                } else {
                  byte2 = 2;
                  byte0 = 0;
                  byte1 = 1;
                }
              } else {
                byte2 = 2;
                byte0 = 0;
                byte1 = 1;
              }

              IsoGridSquare square1 =
                  IsoWorld.instance.CurrentCell.getGridSquare(
                      (double)float1, (double)float2, (double)float3);
              if (square1 != nullptr && square1.getZone() != nullptr &&
                      (square1.getZone().getType() == "Forest") ||
                  square1.getZone().getType() == "DeepForest"))) {
                  byte2 = 1;
                  byte0 = 0;
                  byte1 = 2;
                }

              javafmod.FMOD_Channel_SetReverbProperties(this.channel, byte2,
                                                        0.0F);
              javafmod.FMOD_Channel_SetReverbProperties(this.channel, byte0,
                                                        0.0F);
              javafmod.FMOD_Channel_SetReverbProperties(this.channel, byte1,
                                                        0.0F);
              javafmod.FMOD_Channel_Set3DMinMaxDistance(this.channel, float0,
                                                        this.clip.distanceMax);
              IsoGridSquare square2 =
                  IsoWorld.instance.CurrentCell.getGridSquare(
                      (double)float1, (double)float2, (double)float3);
              float float9 = 0.0F;
              float float10 = 0.0F;
              if (square2 != nullptr) {
                if (this.emitter.parent instanceof
                    IsoWindow || this.emitter.parent instanceof IsoDoor) {
                  IsoRoom room0 =
                      IsoPlayer.getInstance().getCurrentSquare().getRoom();
                  if (room0 != this.emitter.parent.square.getRoom()) {
                    if (room0 != nullptr &&
                        room0.getBuilding() ==
                            this.emitter.parent.square.getBuilding()) {
                      float9 = 0.33F;
                      float10 = 0.33F;
                    } else {
                      void *object = null;
                      if (this.emitter.parent instanceof IsoDoor door) {
                        if (door.north) {
                          object = IsoWorld.instance.CurrentCell.getGridSquare(
                              (double)door.getX(), (double)(door.getY() - 1.0F),
                              (double)door.getZ());
                        } else {
                          object = IsoWorld.instance.CurrentCell.getGridSquare(
                              (double)(door.getX() - 1.0F), (double)door.getY(),
                              (double)door.getZ());
                        }
                      } else {
                        IsoWindow window = (IsoWindow)this.emitter.parent;
                        if (window.north) {
                          object = IsoWorld.instance.CurrentCell.getGridSquare(
                              (double)window.getX(),
                              (double)(window.getY() - 1.0F),
                              (double)window.getZ());
                        } else {
                          object = IsoWorld.instance.CurrentCell.getGridSquare(
                              (double)(window.getX() - 1.0F),
                              (double)window.getY(), (double)window.getZ());
                        }
                      }

                      if (object != nullptr) {
                        IsoRoom room1 = IsoPlayer.getInstance()
                                            .getCurrentSquare()
                                            .getRoom();
                        if (room1 != nullptr ||
                            ((IsoGridSquare)object).getRoom() == nullptr) {
                          if (room1 == nullptr ||
                              ((IsoGridSquare)object).getRoom() == nullptr ||
                              room1.building !=
                                  ((IsoGridSquare)object).getBuilding()) {
                            float9 = 0.33F;
                            float10 = 0.33F;
                          } else if (room1 !=
                                     ((IsoGridSquare)object).getRoom()) {
                            if (room1.def.level ==
                                ((IsoGridSquare)object).getZ()) {
                              float9 = 0.33F;
                              float10 = 0.33F;
                            } else {
                              float9 = 0.6F;
                              float10 = 0.6F;
                            }
                          }
                        }
                      }
                    }
                  }
                } else if (square2.getRoom() != nullptr) {
                  IsoRoom room2 =
                      IsoPlayer.getInstance().getCurrentSquare().getRoom();
                  if (room2 == nullptr) {
                    float9 = 0.33F;
                    float10 = 0.23F;
                  } else if (room2 != square2.getRoom()) {
                    float9 = 0.24F;
                    float10 = 0.24F;
                  }

                  if (room2 != nullptr &&
                      square2.getRoom().getBuilding() != room2.getBuilding()) {
                    float9 = 1.0F;
                    float10 = 0.8F;
                  }

                  if (room2 != nullptr && square2.getRoom().def.level !=
                                              (int)IsoPlayer.getInstance().z) {
                    float9 = 0.6F;
                    float10 = 0.6F;
                  }
                } else {
                  IsoRoom room3 =
                      IsoPlayer.getInstance().getCurrentSquare().getRoom();
                  if (room3 != nullptr) {
                    float9 = 0.79F;
                    float10 = 0.59F;
                  }
                }

                if (!square2.isCouldSee(IsoPlayer.getPlayerIndex()) &&
                    square2 != IsoPlayer.getInstance().getCurrentSquare()) {
                  float9 += 0.4F;
                }
              } else {
                if (IsoWorld.instance.MetaGrid.getRoomAt(
                        (int)float1, (int)float2, (int)float3) != nullptr) {
                  float9 = 1.0F;
                  float10 = 1.0F;
                }

                IsoRoom room4 =
                    IsoPlayer.getInstance().getCurrentSquare().getRoom();
                if (room4 != nullptr) {
                  float9 += 0.94F;
                } else {
                  float9 += 0.6F;
                }
              }

              if (square2 != nullptr &&
                  (int)IsoPlayer.getInstance().z != square2.getZ()) {
                float9 *= 1.3F;
              }

              if (float9 > 0.9F) {
                float9 = 0.9F;
              }

              if (float10 > 0.9F) {
                float10 = 0.9F;
              }

              if (this.emitter.emitterType == EmitterType.Footstep &&
                  float3 > IsoPlayer.getInstance().z &&
                  square2.getBuilding() ==
                      IsoPlayer.getInstance().getBuilding()) {
                float9 = 0.0F;
                float10 = 0.0F;
              }

              if ("HouseAlarm" == this.name)) {
                  float9 = 0.0F;
                  float10 = 0.0F;
                }

              javafmod.FMOD_Channel_Set3DOcclusion(this.channel, float9,
                                                   float10);
              javafmod.FMOD_Channel_SetVolume(this.channel, this.getVolume());
              javafmod.FMOD_Channel_SetPitch(this.channel, this.pitch);
              if (boolean0) {
                javafmod.FMOD_Channel_SetPaused(this.channel, false);
              }

              this.lx = float1;
              this.ly = float2;
              this.lz = float3;
              return false;
            }
          }
        }
      }
    }

    void setParameterValue(FMOD_STUDIO_PARAMETER_DESCRIPTION var1, float var2) {
    }

    void setTimelinePosition(const std::string &var1) {}

    void triggerCue() {}

    bool isTriggeredCue() { return false; }

    bool restart() { return false; }
  }

private
  static final class ParameterValue {
    long eventInstance;
    FMOD_STUDIO_PARAMETER_DESCRIPTION parameterDescription;
    float value;
  }

  private abstract static class Sound {
    FMODSoundEmitter emitter;
    GameSoundClip clip;
    std::string name;
    float volume = 1.0F;
    float pitch = 1.0F;
    IsoObject parent;
    float setVolume = 1.0F;
    float setX = 0.0F;
    float setY = 0.0F;
    float setZ = 0.0F;

    Sound(FMODSoundEmitter fMODSoundEmitter) {
      this.emitter = fMODSoundEmitter;
    }

    abstract long getRef();

    abstract void stop();

    abstract void set3D(boolean var1);

    abstract void release();

    abstract boolean tick(boolean var1);

    float getVolume() {
      this.clip = this.clip.checkReloaded();
      return this.volume * this.clip.getEffectiveVolume();
    }

    abstract void setParameterValue(FMOD_STUDIO_PARAMETER_DESCRIPTION var1,
                                    float var2);

    abstract void setTimelinePosition(String var1);

    abstract void triggerCue();

    abstract boolean isTriggeredCue();

    abstract boolean restart();
  }
}
} // namespace fmod
} // namespace fmod
