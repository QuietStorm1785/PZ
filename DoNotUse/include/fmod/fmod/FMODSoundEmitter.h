#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/FMOD_STUDIO_EVENT_PROPERTY.h"
#include "fmod/fmod/FMODSoundEmitter/EventSound.h"
#include "fmod/fmod/FMODSoundEmitter/FileSound.h"
#include "fmod/fmod/FMODSoundEmitter/ParameterValue.h"
#include "fmod/fmod/FMODSoundEmitter/Sound.h"
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
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/popman/ObjectPool.h"
#include <algorithm>

namespace fmod {
namespace fmod {


class FMODSoundEmitter : public BaseSoundEmitter {
public:
   private const std::vector<Sound> ToStart = std::make_unique<std::vector<>>();
   private const std::vector<Sound> Instances = std::make_unique<std::vector<>>();
    float x;
    float y;
    float z;
    EmitterType emitterType;
    IsoObject parent;
    const ParameterOcclusion occlusion = std::make_shared<ParameterOcclusion>(this);
   private const std::vector<FMODParameter> parameters = std::make_unique<std::vector<>>();
    IFMODParameterUpdater parameterUpdater;
   private const std::vector<ParameterValue> parameterValues = std::make_unique<std::vector<>>();
   private static const ObjectPool<ParameterValue> parameterValuePool = std::make_shared<ObjectPool>(ParameterValue::new);
    static BitSet parameterSet;
   private const ArrayDeque<EventSound> eventSoundPool = std::make_unique<ArrayDeque<>>();
   private const ArrayDeque<FileSound> fileSoundPool = std::make_unique<ArrayDeque<>>();
    static long CurrentTimeMS = 0L;

    public FMODSoundEmitter() {
      SoundManager.instance.registerEmitter(this);
      if (parameterSet == nullptr) {
         parameterSet = std::make_shared<BitSet>(FMODManager.instance.getParameterCount());
      }
   }

    void randomStart() {
   }

    void setPos(float var1, float var2, float var3) {
      this.x = var1;
      this.y = var2;
      this.z = var3;
   }

    int stopSound(long var1) {
      for (int var3 = 0; var3 < this.ToStart.size(); var3++) {
    Sound var4 = this.ToStart.get(var3);
         if (var4.getRef() == var1) {
            this.sendStopSound(var4.name, false);
            var4.release();
            this.ToStart.remove(var3--);
         }
      }

      for (int var5 = 0; var5 < this.Instances.size(); var5++) {
    Sound var6 = this.Instances.get(var5);
         if (var6.getRef() == var1) {
            var6.stop();
            this.sendStopSound(var6.name, false);
            var6.release();
            this.Instances.remove(var5--);
         }
      }

    return 0;
   }

    void stopSoundLocal(long var1) {
      for (int var3 = 0; var3 < this.ToStart.size(); var3++) {
    Sound var4 = this.ToStart.get(var3);
         if (var4.getRef() == var1) {
            var4.release();
            this.ToStart.remove(var3--);
         }
      }

      for (int var5 = 0; var5 < this.Instances.size(); var5++) {
    Sound var6 = this.Instances.get(var5);
         if (var6.getRef() == var1) {
            var6.stop();
            var6.release();
            this.Instances.remove(var5--);
         }
      }
   }

    int stopSoundByName(const std::string& var1) {
    GameSound var2 = GameSounds.getSound(var1);
      if (var2 == nullptr) {
    return 0;
      } else {
         for (int var3 = 0; var3 < this.ToStart.size(); var3++) {
    Sound var4 = this.ToStart.get(var3);
            if (var2.clips.contains(var4.clip)) {
               var4.release();
               this.ToStart.remove(var3--);
            }
         }

         for (int var5 = 0; var5 < this.Instances.size(); var5++) {
    Sound var6 = this.Instances.get(var5);
            if (var2.clips.contains(var6.clip)) {
               var6.stop();
               var6.release();
               this.Instances.remove(var5--);
            }
         }

    return 0;
      }
   }

    void stopOrTriggerSound(long var1) {
    int var3 = this.findToStart(var1);
      if (var3 != -1) {
    Sound var6 = this.ToStart.remove(var3);
         this.sendStopSound(var6.name, true);
         var6.release();
      } else {
         var3 = this.findInstance(var1);
         if (var3 != -1) {
    Sound var4 = this.Instances.get(var3);
            this.sendStopSound(var4.name, true);
            if (var4.clip.hasSustainPoints()) {
               var4.triggerCue();
            } else {
               this.Instances.remove(var3);
               var4.stop();
               var4.release();
            }
         }
      }
   }

    void stopOrTriggerSoundByName(const std::string& var1) {
    GameSound var2 = GameSounds.getSound(var1);
      if (var2 != nullptr) {
         for (int var3 = 0; var3 < this.ToStart.size(); var3++) {
    Sound var4 = this.ToStart.get(var3);
            if (var2.clips.contains(var4.clip)) {
               this.ToStart.remove(var3--);
               var4.release();
            }
         }

         for (int var5 = 0; var5 < this.Instances.size(); var5++) {
    Sound var6 = this.Instances.get(var5);
            if (var2.clips.contains(var6.clip)) {
               if (var6.clip.hasSustainPoints()) {
                  var6.triggerCue();
               } else {
                  var6.stop();
                  var6.release();
                  this.Instances.remove(var5--);
               }
            }
         }
      }
   }

    void limitSound(GameSound var1, int var2) {
    int var3 = this.countToStart(var1) + this.countInstances(var1);
      if (var3 > var2) {
         for (int var4 = 0; var4 < this.ToStart.size(); var4++) {
    Sound var5 = this.ToStart.get(var4);
            if (var1.clips.contains(var5.clip)) {
               this.ToStart.remove(var4--);
               var5.release();
               if (--var3 <= var2) {
                  return;
               }
            }
         }

         for (int var6 = 0; var6 < this.Instances.size(); var6++) {
    Sound var7 = this.Instances.get(var6);
            if (var1.clips.contains(var7.clip)) {
               if (var7.clip.hasSustainPoints()) {
                  if (!var7.isTriggeredCue()) {
                     var7.triggerCue();
                  }
               } else {
                  var7.stop();
                  var7.release();
                  this.Instances.remove(var6--);
                  if (--var3 <= var2) {
                     return;
                  }
               }
            }
         }
      }
   }

    void setVolume(long var1, float var3) {
      for (int var4 = 0; var4 < this.ToStart.size(); var4++) {
    Sound var5 = this.ToStart.get(var4);
         if (var5.getRef() == var1) {
            var5.volume = var3;
         }
      }

      for (int var6 = 0; var6 < this.Instances.size(); var6++) {
    Sound var7 = this.Instances.get(var6);
         if (var7.getRef() == var1) {
            var7.volume = var3;
         }
      }
   }

    void setPitch(long var1, float var3) {
      for (int var4 = 0; var4 < this.ToStart.size(); var4++) {
    Sound var5 = this.ToStart.get(var4);
         if (var5.getRef() == var1) {
            var5.pitch = var3;
         }
      }

      for (int var6 = 0; var6 < this.Instances.size(); var6++) {
    Sound var7 = this.Instances.get(var6);
         if (var7.getRef() == var1) {
            var7.pitch = var3;
         }
      }
   }

    bool hasSustainPoints(long var1) {
      for (int var3 = 0; var3 < this.ToStart.size(); var3++) {
    Sound var4 = this.ToStart.get(var3);
         if (var4.getRef() == var1) {
            if (var4.clip.eventDescription == nullptr) {
    return false;
            }

            return var4.clip.eventDescription.bHasSustainPoints;
         }
      }

      for (int var5 = 0; var5 < this.Instances.size(); var5++) {
    Sound var6 = this.Instances.get(var5);
         if (var6.getRef() == var1) {
            if (var6.clip.eventDescription == nullptr) {
    return false;
            }

            return var6.clip.eventDescription.bHasSustainPoints;
         }
      }

    return false;
   }

    void triggerCue(long var1) {
      for (int var3 = 0; var3 < this.Instances.size(); var3++) {
    Sound var4 = this.Instances.get(var3);
         if (var4.getRef() == var1) {
            var4.triggerCue();
         }
      }
   }

    void setVolumeAll(float var1) {
      for (int var2 = 0; var2 < this.ToStart.size(); var2++) {
    Sound var3 = this.ToStart.get(var2);
         var3.volume = var1;
      }

      for (int var4 = 0; var4 < this.Instances.size(); var4++) {
    Sound var5 = this.Instances.get(var4);
         var5.volume = var1;
      }
   }

    void stopAll() {
      for (int var1 = 0; var1 < this.ToStart.size(); var1++) {
    Sound var2 = this.ToStart.get(var1);
         var2.release();
      }

      for (int var3 = 0; var3 < this.Instances.size(); var3++) {
    Sound var4 = this.Instances.get(var3);
         var4.stop();
         var4.release();
      }

      this.ToStart.clear();
      this.Instances.clear();
   }

    long playSound(const std::string& var1) {
      if (GameClient.bClient) {
         if (this.dynamic_cast<IsoMovingObject*>(parent) != nullptr) {
            if (!(this.dynamic_cast<IsoPlayer*>(parent) != nullptr) || !((IsoPlayer)this.parent).isInvisible()) {
               GameClient.instance.PlaySound(var1, false, (IsoMovingObject)this.parent);
            }
         } else {
            GameClient.instance.PlayWorldSound(var1, (int)this.x, (int)this.y, (byte)this.z);
         }
      }

      return GameServer.bServer ? 0L : this.playSoundImpl(var1, (IsoObject)nullptr);
   }

    long playSound(const std::string& var1, IsoGameCharacter var2) {
      if (GameClient.bClient) {
         if (!var2.isInvisible()) {
            GameClient.instance.PlaySound(var1, false, var2);
         }

         return var2.isInvisible() && !DebugOptions.instance.char.Debug.PlaySoundWhenInvisible.getValue() ? 0L : this.playSoundImpl(var1, (IsoObject)nullptr);
      } else {
         return GameServer.bServer ? 0L : this.playSoundImpl(var1, (IsoObject)nullptr);
      }
   }

    long playSound(const std::string& var1, int var2, int var3, int var4) {
      this.x = var2;
      this.y = var3;
      this.z = var4;
      return this.playSound(var1);
   }

    long playSound(const std::string& var1, IsoGridSquare var2) {
      this.x = var2.x + 0.5F;
      this.y = var2.y + 0.5F;
      this.z = var2.z;
      return this.playSound(var1);
   }

    long playSoundImpl(const std::string& var1, IsoGridSquare var2) {
      this.x = var2.x + 0.5F;
      this.y = var2.y + 0.5F;
      this.z = var2.z + 0.5F;
      return this.playSoundImpl(var1, (IsoObject)nullptr);
   }

    long playSound(const std::string& var1, bool var2) {
      return this.playSound(var1);
   }

    long playSoundImpl(const std::string& var1, bool var2, IsoObject var3) {
      return this.playSoundImpl(var1, var3);
   }

    long playSoundLooped(const std::string& var1) {
      if (GameClient.bClient) {
         if (this.dynamic_cast<IsoMovingObject*>(parent) != nullptr) {
            GameClient.instance.PlaySound(var1, true, (IsoMovingObject)this.parent);
         } else {
            GameClient.instance.PlayWorldSound(var1, (int)this.x, (int)this.y, (byte)this.z);
         }
      }

      return this.playSoundLoopedImpl(var1);
   }

    long playSoundLoopedImpl(const std::string& var1) {
      return this.playSoundImpl(var1, false, nullptr);
   }

    long playSound(const std::string& var1, IsoObject var2) {
      if (GameClient.bClient) {
         if (dynamic_cast<IsoMovingObject*>(var2) != nullptr) {
            GameClient.instance.PlaySound(var1, false, (IsoMovingObject)this.parent);
         } else {
            GameClient.instance.PlayWorldSound(var1, (int)this.x, (int)this.y, (byte)this.z);
         }
      }

      return GameServer.bServer ? 0L : this.playSoundImpl(var1, var2);
   }

    long playSoundImpl(const std::string& var1, IsoObject var2) {
    GameSound var3 = GameSounds.getSound(var1);
      if (var3 == nullptr) {
    return 0L;
      } else {
    GameSoundClip var4 = var3.getRandomClip();
         return this.playClip(var4, var2);
      }
   }

    long playClip(GameSoundClip var1, IsoObject var2) {
    Sound var3 = this.addSound(var1, 1.0F, var2);
    return var3 = = nullptr ? 0L : var3.getRef();
   }

    long playAmbientSound(const std::string& var1) {
      if (GameServer.bServer) {
    return 0L;
      } else {
    GameSound var2 = GameSounds.getSound(var1);
         if (var2 == nullptr) {
    return 0L;
         } else {
    GameSoundClip var3 = var2.getRandomClip();
    Sound var4 = this.addSound(var3, 1.0F, nullptr);
            if (dynamic_cast<FileSound*>(var4) != nullptr) {
               ((FileSound)var4).ambient = true;
            }

    return var4 = = nullptr ? 0L : var4.getRef();
         }
      }
   }

    long playAmbientLoopedImpl(const std::string& var1) {
      if (GameServer.bServer) {
    return 0L;
      } else {
    GameSound var2 = GameSounds.getSound(var1);
         if (var2 == nullptr) {
    return 0L;
         } else {
    GameSoundClip var3 = var2.getRandomClip();
    Sound var4 = this.addSound(var3, 1.0F, nullptr);
    return var4 = = nullptr ? 0L : var4.getRef();
         }
      }
   }

    void set3D(long var1, bool var3) {
      for (int var4 = 0; var4 < this.ToStart.size(); var4++) {
    Sound var5 = this.ToStart.get(var4);
         if (var5.getRef() == var1) {
            var5.set3D(var3);
         }
      }

      for (int var6 = 0; var6 < this.Instances.size(); var6++) {
    Sound var7 = this.Instances.get(var6);
         if (var7.getRef() == var1) {
            var7.set3D(var3);
         }
      }
   }

    void tick() {
      if (!this.empty()) {
         this.occlusion.update();

         for (int var1 = 0; var1 < this.parameters.size(); var1++) {
    FMODParameter var2 = this.parameters.get(var1);
            var2.update();
         }
      }

      for (int var4 = 0; var4 < this.ToStart.size(); var4++) {
    Sound var6 = this.ToStart.get(var4);
         this.Instances.push_back(var6);
      }

      for (int var5 = 0; var5 < this.Instances.size(); var5++) {
    Sound var7 = this.Instances.get(var5);
    bool var3 = this.ToStart.contains(var7);
         if (var7.tick(var3)) {
            this.Instances.remove(var5--);
            var7.release();
         }
      }

      this.ToStart.clear();
   }

    bool hasSoundsToStart() {
      return !this.ToStart.empty();
   }

    bool isEmpty() {
      return this.ToStart.empty() && this.Instances.empty();
   }

    bool isPlaying(long var1) {
      for (int var3 = 0; var3 < this.ToStart.size(); var3++) {
         if (this.ToStart.get(var3).getRef() == var1) {
    return true;
         }
      }

      for (int var4 = 0; var4 < this.Instances.size(); var4++) {
         if (this.Instances.get(var4).getRef() == var1) {
    return true;
         }
      }

    return false;
   }

    bool isPlaying(const std::string& var1) {
      for (int var2 = 0; var2 < this.ToStart.size(); var2++) {
         if (var1 == this.ToStart.get(var2).name)) {
    return true;
         }
      }

      for (int var3 = 0; var3 < this.Instances.size(); var3++) {
         if (var1 == this.Instances.get(var3).name)) {
    return true;
         }
      }

    return false;
   }

    bool restart(long var1) {
    int var3 = this.findToStart(var1);
      if (var3 != -1) {
    return true;
      } else {
         var3 = this.findInstance(var1);
         return var3 != -1 && this.Instances.get(var3).restart();
      }
   }

    int findInstance(long var1) {
      for (int var3 = 0; var3 < this.Instances.size(); var3++) {
    Sound var4 = this.Instances.get(var3);
         if (var4.getRef() == var1) {
    return var3;
         }
      }

      return -1;
   }

    int findInstance(const std::string& var1) {
    GameSound var2 = GameSounds.getSound(var1);
      if (var2 == nullptr) {
         return -1;
      } else {
         for (int var3 = 0; var3 < this.Instances.size(); var3++) {
    Sound var4 = this.Instances.get(var3);
            if (var2.clips.contains(var4.clip)) {
    return var3;
            }
         }

         return -1;
      }
   }

    int findToStart(long var1) {
      for (int var3 = 0; var3 < this.ToStart.size(); var3++) {
    Sound var4 = this.ToStart.get(var3);
         if (var4.getRef() == var1) {
    return var3;
         }
      }

      return -1;
   }

    int findToStart(const std::string& var1) {
    GameSound var2 = GameSounds.getSound(var1);
      if (var2 == nullptr) {
         return -1;
      } else {
         for (int var3 = 0; var3 < this.ToStart.size(); var3++) {
    Sound var4 = this.ToStart.get(var3);
            if (var2.clips.contains(var4.clip)) {
    return var3;
            }
         }

         return -1;
      }
   }

    int countToStart(GameSound var1) {
    int var2 = 0;

      for (int var3 = 0; var3 < this.ToStart.size(); var3++) {
    Sound var4 = this.ToStart.get(var3);
         if (var1.clips.contains(var4.clip)) {
            var2++;
         }
      }

    return var2;
   }

    int countInstances(GameSound var1) {
    int var2 = 0;

      for (int var3 = 0; var3 < this.Instances.size(); var3++) {
    Sound var4 = this.Instances.get(var3);
         if (var1.clips.contains(var4.clip)) {
            var2++;
         }
      }

    return var2;
   }

    void addParameter(FMODParameter var1) {
      this.parameters.push_back(var1);
   }

    void setParameterValue(long var1, FMOD_STUDIO_PARAMETER_DESCRIPTION var3, float var4) {
      if (var1 != 0L && var3 != nullptr) {
    int var5 = this.findInstance(var1);
         if (var5 != -1) {
    Sound var8 = this.Instances.get(var5);
            var8.setParameterValue(var3, var4);
         } else {
            var5 = this.findParameterValue(var1, var3);
            if (var5 != -1) {
               this.parameterValues.get(var5).value = var4;
            } else {
    ParameterValue var6 = (ParameterValue)parameterValuePool.alloc();
               var6.eventInstance = var1;
               var6.parameterDescription = var3;
               var6.value = var4;
               this.parameterValues.push_back(var6);
            }
         }
      }
   }

    void setTimelinePosition(long var1, const std::string& var3) {
      if (var1 != 0L) {
    int var4 = this.findToStart(var1);
         if (var4 != -1) {
    Sound var5 = this.ToStart.get(var4);
            var5.setTimelinePosition(var3);
         }
      }
   }

    int findParameterValue(long var1, FMOD_STUDIO_PARAMETER_DESCRIPTION var3) {
      for (int var4 = 0; var4 < this.parameterValues.size(); var4++) {
    ParameterValue var5 = this.parameterValues.get(var4);
         if (var5.eventInstance == var1 && var5.parameterDescription == var3) {
    return var4;
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

    void startEvent(long var1, GameSoundClip var3) {
      parameterSet.clear();
    std::vector var4 = this.parameters;
    std::vector var5 = var3.eventDescription.parameters;

      for (int var6 = 0; var6 < var5.size(); var6++) {
    FMOD_STUDIO_PARAMETER_DESCRIPTION var7 = (FMOD_STUDIO_PARAMETER_DESCRIPTION)var5.get(var6);
    int var8 = this.findParameterValue(var1, var7);
         if (var8 != -1) {
    ParameterValue var11 = this.parameterValues.get(var8);
            javafmod.FMOD_Studio_EventInstance_SetParameterByID(var1, var7.id, var11.value, false);
            parameterSet.set(var7.globalIndex, true);
         } else if (var7 == this.occlusion.getParameterDescription()) {
            this.occlusion.startEventInstance(var1);
            parameterSet.set(var7.globalIndex, true);
         } else {
            for (int var9 = 0; var9 < var4.size(); var9++) {
    FMODParameter var10 = (FMODParameter)var4.get(var9);
               if (var10.getParameterDescription() == var7) {
                  var10.startEventInstance(var1);
                  parameterSet.set(var7.globalIndex, true);
                  break;
               }
            }
         }
      }

      if (this.parameterUpdater != nullptr) {
         this.parameterUpdater.startEvent(var1, var3, parameterSet);
      }
   }

    void updateEvent(long var1, GameSoundClip var3) {
      if (this.parameterUpdater != nullptr) {
         this.parameterUpdater.updateEvent(var1, var3);
      }
   }

    void stopEvent(long var1, GameSoundClip var3) {
      parameterSet.clear();
    std::vector var4 = this.parameters;
    std::vector var5 = var3.eventDescription.parameters;

      for (int var6 = 0; var6 < var5.size(); var6++) {
    FMOD_STUDIO_PARAMETER_DESCRIPTION var7 = (FMOD_STUDIO_PARAMETER_DESCRIPTION)var5.get(var6);
    int var8 = this.findParameterValue(var1, var7);
         if (var8 != -1) {
    ParameterValue var11 = this.parameterValues.remove(var8);
            parameterValuePool.release(var11);
            parameterSet.set(var7.globalIndex, true);
         } else if (var7 == this.occlusion.getParameterDescription()) {
            this.occlusion.stopEventInstance(var1);
            parameterSet.set(var7.globalIndex, true);
         } else {
            for (int var9 = 0; var9 < var4.size(); var9++) {
    FMODParameter var10 = (FMODParameter)var4.get(var9);
               if (var10.getParameterDescription() == var7) {
                  var10.stopEventInstance(var1);
                  parameterSet.set(var7.globalIndex, true);
                  break;
               }
            }
         }
      }

      if (this.parameterUpdater != nullptr) {
         this.parameterUpdater.stopEvent(var1, var3, parameterSet);
      }
   }

    EventSound allocEventSound() {
      return this.eventSoundPool.empty() ? std::make_shared<EventSound>(this) : this.eventSoundPool.pop();
   }

    void releaseEventSound(EventSound var1) {
      assert !this.eventSoundPool.contains(var1);

      this.eventSoundPool.push(var1);
   }

    FileSound allocFileSound() {
      return this.fileSoundPool.empty() ? std::make_shared<FileSound>(this) : this.fileSoundPool.pop();
   }

    void releaseFileSound(FileSound var1) {
      assert !this.fileSoundPool.contains(var1);

      this.fileSoundPool.push(var1);
   }

    Sound addSound(GameSoundClip var1, float var2, IsoObject var3) {
      if (var1 == nullptr) {
         DebugLog.log("nullptr sound passed to SoundEmitter.playSoundImpl");
    return nullptr;
      } else {
         if (var1.gameSound.maxInstancesPerEmitter > 0) {
            this.limitSound(var1.gameSound, var1.gameSound.maxInstancesPerEmitter - 1);
         }

         if (var1.event != nullptr && !var1.event.empty()) {
            if (var1.eventDescription == nullptr) {
    return nullptr;
            } else {
    FMOD_STUDIO_EVENT_DESCRIPTION var9 = var1.eventDescription;
               if (var1.eventDescriptionMP != nullptr && this.dynamic_cast<IsoPlayer*>(parent) != nullptr && !((IsoPlayer)this.parent).isLocalPlayer()) {
                  var9 = var1.eventDescriptionMP;
               }

    long var5 = javafmod.FMOD_Studio_System_CreateEventInstance(var9.address);
               if (var5 < 0L) {
    return nullptr;
               } else {
                  if (var1.hasMinDistance()) {
                     javafmodJNI.FMOD_Studio_EventInstance_SetProperty(
                        var5, FMOD_STUDIO_EVENT_PROPERTY.FMOD_STUDIO_EVENT_PROPERTY_MINIMUM_DISTANCE.ordinal(), var1.getMinDistance()
                     );
                  }

                  if (var1.hasMaxDistance()) {
                     javafmodJNI.FMOD_Studio_EventInstance_SetProperty(
                        var5, FMOD_STUDIO_EVENT_PROPERTY.FMOD_STUDIO_EVENT_PROPERTY_MAXIMUM_DISTANCE.ordinal(), var1.getMaxDistance()
                     );
                  }

    EventSound var7 = this.allocEventSound();
                  var7.clip = var1;
                  var7.name = var1.gameSound.getName();
                  var7.eventInstance = var5;
                  var7.volume = var2;
                  var7.parent = var3;
                  var7.setVolume = 1.0F;
                  var7.setX = var7.setY = var7.setZ = 0.0F;
                  this.ToStart.push_back(var7);
    return var7;
               }
            }
         } else if (var1.file != nullptr && !var1.file.empty()) {
    long var4 = FMODManager.instance.loadSound(var1.file);
            if (var4 == 0L) {
    return nullptr;
            } else {
    long var6 = javafmod.FMOD_System_PlaySound(var4, true);
               javafmod.FMOD_Channel_SetVolume(var6, 0.0F);
               javafmod.FMOD_Channel_SetPriority(var6, 9 - var1.priority);
               javafmod.FMOD_Channel_SetChannelGroup(var6, FMODManager.instance.channelGroupInGameNonBankSounds);
               if (var1.distanceMax == 0.0F || this.x == 0.0F && this.y == 0.0F) {
                  javafmod.FMOD_Channel_SetMode(var6, FMODManager.FMOD_2D);
               }

    FileSound var8 = this.allocFileSound();
               var8.clip = var1;
               var8.name = var1.gameSound.getName();
               var8.sound = var4;
               var8.pitch = var1.pitch;
               var8.channel = var6;
               var8.parent = var3;
               var8.volume = var2;
               var8.setVolume = 1.0F;
               var8.setX = var8.setY = var8.setZ = 0.0F;
               var8.is3D = -1;
               var8.ambient = false;
               this.ToStart.push_back(var8);
    return var8;
            }
         } else {
    return nullptr;
         }
      }
   }

    void sendStopSound(const std::string& var1, bool var2) {
      if (GameClient.bClient && this.dynamic_cast<IsoMovingObject*>(parent) != nullptr) {
         GameClient.instance.StopSound((IsoMovingObject)this.parent, var1, var2);
      }
   }

    static void update() {
      CurrentTimeMS = System.currentTimeMillis();
   }
}
} // namespace fmod
} // namespace fmod
