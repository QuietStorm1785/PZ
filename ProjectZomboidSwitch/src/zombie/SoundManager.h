#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/Audio.h"
#include "fmod/fmod/FMODAudio.h"
#include "fmod/fmod/FMODManager.h"
#include "fmod/fmod/FMODSoundEmitter.h"
#include "fmod/fmod/FMOD_STUDIO_EVENT_CALLBACK.h"
#include "fmod/fmod/FMOD_STUDIO_EVENT_CALLBACK_TYPE.h"
#include "fmod/fmod/FMOD_STUDIO_PARAMETER_DESCRIPTION.h"
#include "fmod/fmod/FMOD_STUDIO_PLAYBACK_STATE.h"
#include "fmod/fmod/IFMODParameterUpdater.h"
#include "fmod/javafmod.h"
#include "fmod/javafmodJNI.h"
#include "zombie/SoundManager/1.h"
#include "zombie/SoundManager/AmbientSoundEffect.h"
#include "zombie/SoundManager/Music.h"
#include "zombie/audio/BaseSoundEmitter.h"
#include "zombie/audio/FMODParameter.h"
#include "zombie/audio/FMODParameterList.h"
#include "zombie/audio/GameSound.h"
#include "zombie/audio/GameSoundClip.h"
#include "zombie/audio/parameters/ParameterMusicActionStyle.h"
#include "zombie/audio/parameters/ParameterMusicLibrary.h"
#include "zombie/audio/parameters/ParameterMusicState.h"
#include "zombie/audio/parameters/ParameterMusicState/State.h"
#include "zombie/audio/parameters/ParameterMusicWakeState.h"
#include "zombie/audio/parameters/ParameterMusicZombiesTargeting.h"
#include "zombie/audio/parameters/ParameterMusicZombiesVisible.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/input/GameKeyboard.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/Item.h"
#include "zombie/scripting/objects/ScriptModule.h"
#include "zombie/ui/TutorialManager.h"
#include "zombie/util/StringUtils.h"
#include <algorithm>

namespace zombie {


class SoundManager : public BaseSoundManager {
public:
    float SoundVolume = 0.8F;
    float MusicVolume = 0.36F;
    float AmbientVolume = 0.8F;
    float VehicleEngineVolume = 0.5F;
    const ParameterMusicActionStyle parameterMusicActionStyle = std::make_shared<ParameterMusicActionStyle>();
    const ParameterMusicLibrary parameterMusicLibrary = std::make_shared<ParameterMusicLibrary>();
    const ParameterMusicState parameterMusicState = std::make_shared<ParameterMusicState>();
    const ParameterMusicWakeState parameterMusicWakeState = std::make_shared<ParameterMusicWakeState>();
    const ParameterMusicZombiesTargeting parameterMusicZombiesTargeting = std::make_shared<ParameterMusicZombiesTargeting>();
    const ParameterMusicZombiesVisible parameterMusicZombiesVisible = std::make_shared<ParameterMusicZombiesVisible>();
    const FMODParameterList fmodParameters = std::make_shared<FMODParameterList>();
    bool initialized = false;
    long inGameGroupBus = 0L;
    long musicGroupBus = 0L;
    FMODSoundEmitter musicEmitter = nullptr;
    long musicCombinedEvent = 0L;
    FMODSoundEmitter uiEmitter = nullptr;
    const Music music = std::make_shared<Music>();
   public std::vector<Audio> ambientPieces = std::make_unique<std::vector<>>();
    bool muted = false;
   private long[] bankList = new long[32];
   private long[] eventDescList = new long[256];
   private long[] eventInstList = new long[256];
   private long[] pausedEventInstances = new long[128];
   private float[] pausedEventVolumes = new float[128];
    int pausedEventCount;
   private const std::unordered_set<BaseSoundEmitter> emitters = std::make_unique<std::unordered_set<>>();
   private static std::vector<AmbientSoundEffect> ambientSoundEffects = std::make_unique<std::vector<>>();
    static BaseSoundManager instance;
    std::string currentMusicName;
    std::string currentMusicLibrary;
    const FMOD_STUDIO_EVENT_CALLBACK musicEventCallback = std::make_shared<1>(this);

    FMODParameterList getFMODParameters() {
      return this.fmodParameters;
   }

    void startEvent(long var1, GameSoundClip var3, BitSet var4) {
    FMODParameterList var5 = this.getFMODParameters();
    std::vector var6 = var3.eventDescription.parameters;

      for (int var7 = 0; var7 < var6.size(); var7++) {
    FMOD_STUDIO_PARAMETER_DESCRIPTION var8 = (FMOD_STUDIO_PARAMETER_DESCRIPTION)var6.get(var7);
         if (!var4.get(var8.globalIndex)) {
    FMODParameter var9 = var5.get(var8);
            if (var9 != nullptr) {
               var9.startEventInstance(var1);
            }
         }
      }
   }

    void updateEvent(long var1, GameSoundClip var3) {
   }

    void stopEvent(long var1, GameSoundClip var3, BitSet var4) {
    FMODParameterList var5 = this.getFMODParameters();
    std::vector var6 = var3.eventDescription.parameters;

      for (int var7 = 0; var7 < var6.size(); var7++) {
    FMOD_STUDIO_PARAMETER_DESCRIPTION var8 = (FMOD_STUDIO_PARAMETER_DESCRIPTION)var6.get(var7);
         if (!var4.get(var8.globalIndex)) {
    FMODParameter var9 = var5.get(var8);
            if (var9 != nullptr) {
               var9.stopEventInstance(var1);
            }
         }
      }
   }

    bool isRemastered() {
    int var1 = Core.getInstance().getOptionMusicLibrary();
    return var1 = = 1 || var1 == 3 && Rand.Next(2) == 0;
   }

    void BlendVolume(Audio var1, float var2) {
   }

    void BlendVolume(Audio var1, float var2, float var3) {
   }

    Audio BlendThenStart(Audio var1, float var2, const std::string& var3) {
    return nullptr;
   }

    void FadeOutMusic(const std::string& var1, int var2) {
   }

    void PlayAsMusic(const std::string& var1, Audio var2, float var3, bool var4) {
   }

    long playUISound(const std::string& var1) {
    GameSound var2 = GameSounds.getSound(var1);
      if (var2 != nullptr && !var2.clips.empty()) {
    GameSoundClip var3 = var2.getRandomClip();
    long var4 = this.uiEmitter.playClip(var3, nullptr);
         this.uiEmitter.tick();
         javafmod.FMOD_System_Update();
    return var4;
      } else {
    return 0L;
      }
   }

    bool isPlayingUISound(const std::string& var1) {
      return this.uiEmitter.isPlaying(var1);
   }

    bool isPlayingUISound(long var1) {
      return this.uiEmitter.isPlaying(var1);
   }

    void stopUISound(long var1) {
      this.uiEmitter.stopSound(var1);
   }

    bool IsMusicPlaying() {
    return false;
   }

    bool isPlayingMusic() {
      return this.music.isPlaying();
   }

   public std::vector<Audio> getAmbientPieces() {
      return this.ambientPieces;
   }

    void gatherInGameEventInstances() {
      this.pausedEventCount = 0;
    int var1 = javafmodJNI.FMOD_Studio_System_GetBankCount();
      if (this.bankList.length < var1) {
         this.bankList = new long[var1];
      }

      var1 = javafmodJNI.FMOD_Studio_System_GetBankList(this.bankList);

      for (int var2 = 0; var2 < var1; var2++) {
    int var3 = javafmodJNI.FMOD_Studio_Bank_GetEventCount(this.bankList[var2]);
         if (this.eventDescList.length < var3) {
            this.eventDescList = new long[var3];
         }

         var3 = javafmodJNI.FMOD_Studio_Bank_GetEventList(this.bankList[var2], this.eventDescList);

         for (int var4 = 0; var4 < var3; var4++) {
    int var5 = javafmodJNI.FMOD_Studio_EventDescription_GetInstanceCount(this.eventDescList[var4]);
            if (this.eventInstList.length < var5) {
               this.eventInstList = new long[var5];
            }

            var5 = javafmodJNI.FMOD_Studio_EventDescription_GetInstanceList(this.eventDescList[var4], this.eventInstList);

            for (int var6 = 0; var6 < var5; var6++) {
    int var7 = javafmod.FMOD_Studio_GetPlaybackState(this.eventInstList[var6]);
               if (var7 != FMOD_STUDIO_PLAYBACK_STATE.FMOD_STUDIO_PLAYBACK_STOPPED.index) {
    bool var8 = javafmodJNI.FMOD_Studio_EventInstance_GetPaused(this.eventInstList[var6]);
                  if (!var8) {
                     if (this.pausedEventInstances.length < this.pausedEventCount + 1) {
                        this.pausedEventInstances = Arrays.copyOf(this.pausedEventInstances, this.pausedEventCount + 128);
                        this.pausedEventVolumes = Arrays.copyOf(this.pausedEventVolumes, this.pausedEventInstances.length);
                     }

                     this.pausedEventInstances[this.pausedEventCount] = this.eventInstList[var6];
                     this.pausedEventVolumes[this.pausedEventCount] = javafmodJNI.FMOD_Studio_EventInstance_GetVolume(this.eventInstList[var6]);
                     this.pausedEventCount++;
                  }
               }
            }
         }
      }
   }

    void pauseSoundAndMusic() {
    bool var1 = true;
      if (GameClient.bClient) {
         this.muted = true;
         if (var1) {
            javafmod.FMOD_Studio_Bus_SetMute(this.inGameGroupBus, true);
            javafmod.FMOD_Studio_Bus_SetMute(this.musicGroupBus, true);
         } else {
            this.setSoundVolume(0.0F);
            this.setMusicVolume(0.0F);
            this.setAmbientVolume(0.0F);
            this.setVehicleEngineVolume(0.0F);
         }

         GameSounds.soundIsPaused = true;
      } else if (var1) {
         javafmod.FMOD_Studio_Bus_SetPaused(this.inGameGroupBus, true);
         javafmod.FMOD_Studio_Bus_SetPaused(this.musicGroupBus, true);
         javafmod.FMOD_Channel_SetPaused(FMODManager.instance.channelGroupInGameNonBankSounds, true);
         GameSounds.soundIsPaused = true;
      } else {
    long var2 = javafmod.FMOD_System_GetMasterChannelGroup();
         javafmod.FMOD_ChannelGroup_SetPaused(var2, true);
         javafmod.FMOD_ChannelGroup_SetVolume(var2, 0.0F);
         javafmodJNI.FMOD_Studio_System_FlushCommands();
         this.gatherInGameEventInstances();

         for (int var4 = 0; var4 < this.pausedEventCount; var4++) {
            javafmodJNI.FMOD_Studio_EventInstance_SetPaused(this.pausedEventInstances[var4], true);
         }

         javafmod.FMOD_Channel_SetPaused(FMODManager.instance.channelGroupInGameNonBankSounds, true);
         javafmod.FMOD_ChannelGroup_SetPaused(var2, false);
         javafmodJNI.FMOD_Studio_System_FlushCommands();
         javafmod.FMOD_ChannelGroup_SetVolume(var2, 1.0F);
         GameSounds.soundIsPaused = true;
      }
   }

    void resumeSoundAndMusic() {
    bool var1 = true;
      if (this.muted) {
         this.muted = false;
         if (var1) {
            javafmod.FMOD_Studio_Bus_SetMute(this.inGameGroupBus, false);
            javafmod.FMOD_Studio_Bus_SetMute(this.musicGroupBus, false);
            javafmod.FMOD_ChannelGroup_SetPaused(FMODManager.instance.channelGroupInGameNonBankSounds, false);
         } else {
            this.setSoundVolume(Core.getInstance().getOptionSoundVolume() / 10.0F);
            this.setMusicVolume(Core.getInstance().getOptionMusicVolume() / 10.0F);
            this.setAmbientVolume(Core.getInstance().getOptionAmbientVolume() / 10.0F);
            this.setVehicleEngineVolume(Core.getInstance().getOptionVehicleEngineVolume() / 10.0F);
         }

         GameSounds.soundIsPaused = false;
      } else if (var1) {
         javafmod.FMOD_Studio_Bus_SetPaused(this.inGameGroupBus, false);
         javafmod.FMOD_Studio_Bus_SetPaused(this.musicGroupBus, false);
         javafmod.FMOD_ChannelGroup_SetPaused(FMODManager.instance.channelGroupInGameNonBankSounds, false);
         GameSounds.soundIsPaused = false;
      } else {
    long var2 = javafmod.FMOD_System_GetMasterChannelGroup();
         javafmod.FMOD_ChannelGroup_SetPaused(var2, true);
         javafmodJNI.FMOD_Studio_System_FlushCommands();

         for (int var4 = 0; var4 < this.pausedEventCount; var4++) {
            try {
               javafmodJNI.FMOD_Studio_EventInstance_SetPaused(this.pausedEventInstances[var4], false);
            } catch (Throwable var6) {
               var6.printStackTrace();
            }
         }

         this.pausedEventCount = 0;
         javafmod.FMOD_ChannelGroup_SetPaused(var2, false);
         javafmod.FMOD_ChannelGroup_SetVolume(var2, 1.0F);
         javafmod.FMOD_ChannelGroup_SetPaused(FMODManager.instance.channelGroupInGameNonBankSounds, false);
         GameSounds.soundIsPaused = false;
      }
   }

    void debugScriptSound(Item var1, const std::string& var2) {
      if (var2 != nullptr && !var2.empty()) {
         if (!GameSounds.isKnownSound(var2)) {
            DebugLog.General.warn("no such sound \"" + var2 + "\" in item " + var1.getFullName());
         }
      }
   }

    void debugScriptSounds() {
      if (Core.bDebug) {
         for (ScriptModule var2 : ScriptManager.instance.ModuleMap.values()) {
            for (Item var4 : var2.ItemMap.values()) {
               this.debugScriptSound(var4, var4.getBreakSound());
               this.debugScriptSound(var4, var4.getBulletOutSound());
               this.debugScriptSound(var4, var4.getCloseSound());
               this.debugScriptSound(var4, var4.getCustomEatSound());
               this.debugScriptSound(var4, var4.getDoorHitSound());
               this.debugScriptSound(var4, var4.getCountDownSound());
               this.debugScriptSound(var4, var4.getExplosionSound());
               this.debugScriptSound(var4, var4.getImpactSound());
               this.debugScriptSound(var4, var4.getOpenSound());
               this.debugScriptSound(var4, var4.getPutInSound());
               this.debugScriptSound(var4, var4.getPlaceOneSound());
               this.debugScriptSound(var4, var4.getPlaceMultipleSound());
               this.debugScriptSound(var4, var4.getShellFallSound());
               this.debugScriptSound(var4, var4.getSwingSound());
               this.debugScriptSound(var4, var4.getInsertAmmoSound());
               this.debugScriptSound(var4, var4.getInsertAmmoStartSound());
               this.debugScriptSound(var4, var4.getInsertAmmoStopSound());
               this.debugScriptSound(var4, var4.getEjectAmmoSound());
               this.debugScriptSound(var4, var4.getEjectAmmoStartSound());
               this.debugScriptSound(var4, var4.getEjectAmmoStopSound());
            }
         }
      }
   }

    void registerEmitter(BaseSoundEmitter var1) {
      this.emitters.push_back(var1);
   }

    void unregisterEmitter(BaseSoundEmitter var1) {
      this.emitters.remove(var1);
   }

    bool isListenerInRange(float var1, float var2, float var3) {
      if (GameServer.bServer) {
    return false;
      } else {
         for (int var4 = 0; var4 < IsoPlayer.numPlayers; var4++) {
    IsoPlayer var5 = IsoPlayer.players[var4];
            if (var5 != nullptr && !var5.Traits.Deaf.isSet() && IsoUtils.DistanceToSquared(var5.x, var5.y, var1, var2) < var3 * var3) {
    return true;
            }
         }

    return false;
      }
   }

    void playNightAmbient(const std::string& var1) {
      DebugLog.log("playNightAmbient: " + var1);

      for (int var2 = 0; var2 < ambientSoundEffects.size(); var2++) {
    AmbientSoundEffect var3 = ambientSoundEffects.get(var2);
         if (var3.getName() == var1)) {
            var3.setVolume(Rand.Next(700, 1500) / 1000.0F);
            var3.start();
            this.ambientPieces.push_back(var3);
            return;
         }
      }

    AmbientSoundEffect var4 = std::make_shared<AmbientSoundEffect>(var1);
      var4.setVolume(Rand.Next(700, 1500) / 1000.0F);
      var4.setName(var1);
      var4.start();
      this.ambientPieces.push_back(var4);
      ambientSoundEffects.push_back(var4);
   }

    void playMusic(const std::string& var1) {
      this.DoMusic(var1, false);
   }

    void playAmbient(const std::string& var1) {
   }

    void playMusicNonTriggered(const std::string& var1, float var2) {
   }

    void stopMusic(const std::string& var1) {
      if (this.isPlayingMusic()) {
         if (StringUtils.isNullOrWhitespace(var1) || var1.equalsIgnoreCase(this.getCurrentMusicName())) {
            this.StopMusic();
         }
      }
   }

    void CheckDoMusic() {
   }

    float getMusicPosition() {
      return this.isPlayingMusic() ? this.music.getPosition() : 0.0F;
   }

    void DoMusic(const std::string& var1, bool var2) {
      if (this.AllowMusic && Core.getInstance().getOptionMusicVolume() != 0) {
         if (this.isPlayingMusic()) {
            this.StopMusic();
         }

    int var3 = Core.getInstance().getOptionMusicLibrary();
    bool var4 = var3 == 1;
    GameSound var5 = GameSounds.getSound(var1);
    GameSoundClip var6 = nullptr;
         if (var5 != nullptr && !var5.clips.empty()) {
            var6 = var5.getRandomClip();
         }

         if (var6 != nullptr && var6.getEvent() != nullptr) {
            if (var6.eventDescription != nullptr) {
    long var9 = var6.eventDescription.address;
               javafmod.FMOD_Studio_LoadEventSampleData(var9);
               this.music.instance = javafmod.FMOD_Studio_System_CreateEventInstance(var9);
               this.music.clip = var6;
               this.music.effectiveVolume = var6.getEffectiveVolume();
               javafmod.FMOD_Studio_EventInstance_SetParameterByName(this.music.instance, "Volume", 10.0F);
               javafmod.FMOD_Studio_EventInstance_SetVolume(this.music.instance, this.music.effectiveVolume);
               javafmod.FMOD_Studio_StartEvent(this.music.instance);
            }
         } else if (var6 != nullptr && var6.getFile() != nullptr) {
    long var7 = FMODManager.instance.loadSound(var6.getFile());
            if (var7 > 0L) {
               this.music.channel = javafmod.FMOD_System_PlaySound(var7, true);
               this.music.clip = var6;
               this.music.effectiveVolume = var6.getEffectiveVolume();
               javafmod.FMOD_Channel_SetVolume(this.music.channel, this.music.effectiveVolume);
               javafmod.FMOD_Channel_SetPitch(this.music.channel, var6.pitch);
               javafmod.FMOD_Channel_SetPaused(this.music.channel, false);
            }
         }

         this.currentMusicName = var1;
         this.currentMusicLibrary = var4 ? "official" : "earlyaccess";
      }
   }

    void PlayAsMusic(const std::string& var1, Audio var2, bool var3, float var4) {
   }

    void setMusicState(const std::string& var1) {
      switch (var1) {
         case "MainMenu":
            this.parameterMusicState.setState(State.MainMenu);
            break;
         case "Loading":
            this.parameterMusicState.setState(State.Loading);
            break;
         case "InGame":
            this.parameterMusicState.setState(State.InGame);
            break;
         case "PauseMenu":
            this.parameterMusicState.setState(State.PauseMenu);
            break;
         case "Tutorial":
            this.parameterMusicState.setState(State.Tutorial);
            break;
         default:
            DebugLog.General.warn("unknown MusicState \"%s\"", new Object[]{var1});
      }
   }

    void setMusicWakeState(IsoPlayer var1, const std::string& var2) {
      switch (var2) {
         case "Awake":
            this.parameterMusicWakeState.setState(var1, zombie.audio.parameters.ParameterMusicWakeState.State.Awake);
            break;
         case "Sleeping":
            this.parameterMusicWakeState.setState(var1, zombie.audio.parameters.ParameterMusicWakeState.State.Sleeping);
            break;
         case "WakeNormal":
            this.parameterMusicWakeState.setState(var1, zombie.audio.parameters.ParameterMusicWakeState.State.WakeNormal);
            break;
         case "WakeNightmare":
            this.parameterMusicWakeState.setState(var1, zombie.audio.parameters.ParameterMusicWakeState.State.WakeNightmare);
            break;
         case "WakeZombies":
            this.parameterMusicWakeState.setState(var1, zombie.audio.parameters.ParameterMusicWakeState.State.WakeZombies);
            break;
         default:
            DebugLog.General.warn("unknown MusicWakeState \"%s\"", new Object[]{var2});
      }
   }

    Audio PlayMusic(const std::string& var1, const std::string& var2, bool var3, float var4) {
    return nullptr;
   }

    Audio PlaySound(const std::string& var1, bool var2, float var3, float var4) {
    return nullptr;
   }

    Audio PlaySound(const std::string& var1, bool var2, float var3) {
      if (GameServer.bServer) {
    return nullptr;
      } else if (IsoWorld.instance == nullptr) {
    return nullptr;
      } else {
    BaseSoundEmitter var4 = IsoWorld.instance.getFreeEmitter();
         var4.setPos(0.0F, 0.0F, 0.0F);
    long var5 = var4.playSound(var1);
         return var5 != 0L ? std::make_shared<FMODAudio>(var4) : nullptr;
      }
   }

    Audio PlaySoundEvenSilent(const std::string& var1, bool var2, float var3) {
    return nullptr;
   }

    Audio PlayJukeboxSound(const std::string& var1, bool var2, float var3) {
    return nullptr;
   }

    Audio PlaySoundWav(const std::string& var1, bool var2, float var3, float var4) {
    return nullptr;
   }

    Audio PlaySoundWav(const std::string& var1, bool var2, float var3) {
    return nullptr;
   }

    Audio PlaySoundWav(const std::string& var1, int var2, bool var3, float var4) {
    return nullptr;
   }

    void update3D() {
   }

    Audio PlayWorldSound(const std::string& var1, IsoGridSquare var2, float var3, float var4, float var5, bool var6) {
      return this.PlayWorldSound(var1, false, var2, var3, var4, var5, var6);
   }

    Audio PlayWorldSound(const std::string& var1, bool var2, IsoGridSquare var3, float var4, float var5, float var6, bool var7) {
      if (!GameServer.bServer && var3 != nullptr) {
         if (GameClient.bClient) {
            GameClient.instance.PlayWorldSound(var1, var3.x, var3.y, (byte)var3.z);
         }

         return this.PlayWorldSoundImpl(var1, var2, var3.getX(), var3.getY(), var3.getZ(), var4, var5, var6, var7);
      } else {
    return nullptr;
      }
   }

    Audio PlayWorldSoundImpl(const std::string& var1, bool var2, int var3, int var4, int var5, float var6, float var7, float var8, bool var9) {
    BaseSoundEmitter var10 = IsoWorld.instance.getFreeEmitter(var3 + 0.5F, var4 + 0.5F, var5);
    long var11 = var10.playSoundImpl(var1, (IsoObject)nullptr);
      return std::make_shared<FMODAudio>(var10);
   }

    Audio PlayWorldSound(const std::string& var1, IsoGridSquare var2, float var3, float var4, float var5, int var6, bool var7) {
      return this.PlayWorldSound(var1, var2, var3, var4, var5, var7);
   }

    Audio PlayWorldSoundWav(const std::string& var1, IsoGridSquare var2, float var3, float var4, float var5, bool var6) {
      return this.PlayWorldSoundWav(var1, false, var2, var3, var4, var5, var6);
   }

    Audio PlayWorldSoundWav(const std::string& var1, bool var2, IsoGridSquare var3, float var4, float var5, float var6, bool var7) {
      if (!GameServer.bServer && var3 != nullptr) {
         if (GameClient.bClient) {
            GameClient.instance.PlayWorldSound(var1, var3.getX(), var3.getY(), (byte)var3.getZ());
         }

         return this.PlayWorldSoundWavImpl(var1, var2, var3, var4, var5, var6, var7);
      } else {
    return nullptr;
      }
   }

    Audio PlayWorldSoundWavImpl(const std::string& var1, bool var2, IsoGridSquare var3, float var4, float var5, float var6, bool var7) {
    BaseSoundEmitter var8 = IsoWorld.instance.getFreeEmitter(var3.getX() + 0.5F, var3.getY() + 0.5F, var3.getZ());
      var8.playSound(var1);
      return std::make_shared<FMODAudio>(var8);
   }

    void PlayWorldSoundWav(const std::string& var1, IsoGridSquare var2, float var3, float var4, float var5, int var6, bool var7) {
    int var8 = Rand.Next(var6) + 1;
      this.PlayWorldSoundWav(var1 + var8, var2, var3, var4, var5, var7);
   }

    Audio PrepareMusic(const std::string& var1) {
    return nullptr;
   }

    Audio Start(Audio var1, float var2, const std::string& var3) {
    return nullptr;
   }

    void Update() {
      if (!this.initialized) {
         this.initialized = true;
         this.inGameGroupBus = javafmod.FMOD_Studio_System_GetBus("bus:/InGame");
         this.musicGroupBus = javafmod.FMOD_Studio_System_GetBus("bus:/Music");
         this.musicEmitter = std::make_unique<FMODSoundEmitter>();
         this.unregisterEmitter(this.musicEmitter);
         this.musicEmitter.parameterUpdater = this;
         this.fmodParameters.push_back(this.parameterMusicActionStyle);
         this.fmodParameters.push_back(this.parameterMusicLibrary);
         this.fmodParameters.push_back(this.parameterMusicState);
         this.fmodParameters.push_back(this.parameterMusicWakeState);
         this.fmodParameters.push_back(this.parameterMusicZombiesTargeting);
         this.fmodParameters.push_back(this.parameterMusicZombiesVisible);
         this.uiEmitter = std::make_unique<FMODSoundEmitter>();
      }

      FMODSoundEmitter.update();
      this.updateMusic();
      this.uiEmitter.tick();

      for (int var1 = 0; var1 < this.ambientPieces.size(); var1++) {
    Audio var2 = this.ambientPieces.get(var1);
         if (IsoPlayer.allPlayersDead()) {
            var2.stop();
         }

         if (!var2.isPlaying()) {
            var2.stop();
            this.ambientPieces.remove(var2);
            var1--;
         } else if (dynamic_cast<AmbientSoundEffect*>(var2) != nullptr) {
            ((AmbientSoundEffect)var2).update();
         }
      }

      AmbientStreamManager.instance.update();
      if (!this.AllowMusic) {
         this.StopMusic();
      }

      if (this.music.isPlaying()) {
         this.music.update();
      }

      FMODManager.instance.tick();
   }

    bool HasMusic(Audio var1) {
    return false;
   }

    void Purge() {
   }

    void stop() {
      for (BaseSoundEmitter var2 : this.emitters) {
         var2.stopAll();
      }

      this.emitters.clear();
    long var3 = javafmod.FMOD_System_GetMasterChannelGroup();
      javafmod.FMOD_ChannelGroup_Stop(var3);
      this.pausedEventCount = 0;
   }

    void StopMusic() {
      this.music.stop();
   }

    void StopSound(Audio var1) {
      var1.stop();
   }

    void CacheSound(const std::string& var1) {
   }

    void update4() {
   }

    void update2() {
   }

    void update3() {
   }

    void update1() {
   }

    void setSoundVolume(float var1) {
      this.SoundVolume = var1;
   }

    float getSoundVolume() {
      return this.SoundVolume;
   }

    void setAmbientVolume(float var1) {
      this.AmbientVolume = var1;
   }

    float getAmbientVolume() {
      return this.AmbientVolume;
   }

    void setMusicVolume(float var1) {
      this.MusicVolume = var1;
      if (!this.muted) {
         ;
      }
   }

    float getMusicVolume() {
      return this.MusicVolume;
   }

    void setVehicleEngineVolume(float var1) {
      this.VehicleEngineVolume = var1;
   }

    float getVehicleEngineVolume() {
      return this.VehicleEngineVolume;
   }

    std::string getCurrentMusicName() {
      return this.isPlayingMusic() ? this.currentMusicName : nullptr;
   }

    std::string getCurrentMusicLibrary() {
      return this.isPlayingMusic() ? this.currentMusicLibrary : nullptr;
   }

    void updateMusic() {
      this.fmodParameters.update();
      if (GameKeyboard.isKeyPressed(Core.getInstance().getKey("Toggle Music"))) {
         this.AllowMusic = !this.AllowMusic;
         if (!this.AllowMusic) {
            this.StopMusic();
            TutorialManager.instance.PrefMusic = nullptr;
         }
      }

      if (!this.musicEmitter.isPlaying(this.musicCombinedEvent)) {
         this.musicCombinedEvent = this.musicEmitter.playSoundImpl("MusicCombined", (IsoObject)nullptr);
         if (this.musicCombinedEvent != 0L && !System.getProperty("os.name").contains("OS X")) {
            javafmod.FMOD_Studio_EventInstance_SetCallback(
               this.musicCombinedEvent, this.musicEventCallback, FMOD_STUDIO_EVENT_CALLBACK_TYPE.FMOD_STUDIO_EVENT_CALLBACK_TIMELINE_MARKER.bit
            );
         }
      }

      if (this.musicEmitter.isPlaying(this.musicCombinedEvent)) {
         this.musicEmitter.setVolume(this.musicCombinedEvent, this.AllowMusic ? 1.0F : 0.0F);
      }

      this.musicEmitter.tick();
   }
}
} // namespace zombie
