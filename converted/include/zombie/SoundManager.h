#pragma once
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
#include "zombie/audio/BaseSoundEmitter.h"
#include "zombie/audio/FMODParameter.h"
#include "zombie/audio/FMODParameterList.h"
#include "zombie/audio/GameSound.h"
#include "zombie/audio/GameSoundClip.h"
#include "zombie/audio/parameters/ParameterMusicActionStyle.h"
#include "zombie/audio/parameters/ParameterMusicLibrary.h"
#include "zombie/audio/parameters/ParameterMusicState.h"
#include "zombie/audio/parameters/ParameterMusicWakeState.h"
#include "zombie/audio/parameters/ParameterMusicZombiesTargeting.h"
#include "zombie/audio/parameters/ParameterMusicZombiesVisible.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/gameStates/MainScreenState.h"
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
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class SoundManager : public BaseSoundManager {
public:
  float SoundVolume = 0.8F;
  float MusicVolume = 0.36F;
  float AmbientVolume = 0.8F;
  float VehicleEngineVolume = 0.5F;
  const ParameterMusicActionStyle parameterMusicActionStyle =
      new ParameterMusicActionStyle();
  const ParameterMusicLibrary parameterMusicLibrary =
      new ParameterMusicLibrary();
  const ParameterMusicState parameterMusicState = new ParameterMusicState();
  const ParameterMusicWakeState parameterMusicWakeState =
      new ParameterMusicWakeState();
  const ParameterMusicZombiesTargeting parameterMusicZombiesTargeting =
      new ParameterMusicZombiesTargeting();
  const ParameterMusicZombiesVisible parameterMusicZombiesVisible =
      new ParameterMusicZombiesVisible();
  const FMODParameterList fmodParameters = new FMODParameterList();
  bool initialized = false;
  long inGameGroupBus = 0L;
  long musicGroupBus = 0L;
  FMODSoundEmitter musicEmitter = null;
  long musicCombinedEvent = 0L;
  FMODSoundEmitter uiEmitter = null;
private
  final SoundManager.Music music = new SoundManager.Music();
public
  ArrayList<Audio> ambientPieces = std::make_unique<ArrayList<>>();
  bool muted = false;
private
  long[] bankList = new long[32];
private
  long[] eventDescList = new long[256];
private
  long[] eventInstList = new long[256];
private
  long[] pausedEventInstances = new long[128];
private
  float[] pausedEventVolumes = new float[128];
  int pausedEventCount;
private
  final HashSet<BaseSoundEmitter> emitters = std::make_unique<HashSet<>>();
private
  static ArrayList<SoundManager.AmbientSoundEffect> ambientSoundEffects =
      std::make_unique<ArrayList<>>();
  static BaseSoundManager instance;
  std::string currentMusicName;
  std::string currentMusicLibrary;
private
  final FMOD_STUDIO_EVENT_CALLBACK musicEventCallback =
      std::make_unique<FMOD_STUDIO_EVENT_CALLBACK>(){
          void timelineMarker(long var1, const std::string &string, int int0){
              DebugLog.Sound.debugln("timelineMarker %s %d", string, int0);
  if ("Lightning" == string)) {
                MainScreenState.getInstance().lightningTimelineMarker = true;
            }
}
}; // namespace zombie

FMODParameterList getFMODParameters() { return this.fmodParameters; }

void startEvent(long eventInstance, GameSoundClip clip, BitSet parameterSet) {
  FMODParameterList fMODParameterList = this.getFMODParameters();
  std::vector arrayList = clip.eventDescription.parameters;

  for (int int0 = 0; int0 < arrayList.size(); int0++) {
    FMOD_STUDIO_PARAMETER_DESCRIPTION fmod_studio_parameter_description =
        (FMOD_STUDIO_PARAMETER_DESCRIPTION)arrayList.get(int0);
    if (!parameterSet.get(fmod_studio_parameter_description.globalIndex)) {
      FMODParameter fMODParameter =
          fMODParameterList.get(fmod_studio_parameter_description);
      if (fMODParameter != nullptr) {
        fMODParameter.startEventInstance(eventInstance);
      }
    }
  }
}

void updateEvent(long eventInstance, GameSoundClip clip) {}

void stopEvent(long eventInstance, GameSoundClip clip, BitSet parameterSet) {
  FMODParameterList fMODParameterList = this.getFMODParameters();
  std::vector arrayList = clip.eventDescription.parameters;

  for (int int0 = 0; int0 < arrayList.size(); int0++) {
    FMOD_STUDIO_PARAMETER_DESCRIPTION fmod_studio_parameter_description =
        (FMOD_STUDIO_PARAMETER_DESCRIPTION)arrayList.get(int0);
    if (!parameterSet.get(fmod_studio_parameter_description.globalIndex)) {
      FMODParameter fMODParameter =
          fMODParameterList.get(fmod_studio_parameter_description);
      if (fMODParameter != nullptr) {
        fMODParameter.stopEventInstance(eventInstance);
      }
    }
  }
}

bool isRemastered() {
  int int0 = Core.getInstance().getOptionMusicLibrary();
  return int0 = = 1 || int0 == 3 && Rand.Next(2) == 0;
}

void BlendVolume(Audio audio, float targetVolume) {}

void BlendVolume(Audio audio, float targetVolume, float blendSpeedAlpha) {}

Audio BlendThenStart(Audio musicTrack, float f, const std::string &PrefMusic) {
  return null;
}

void FadeOutMusic(const std::string &name, int milli) {}

void PlayAsMusic(const std::string &name, Audio musicTrack, float volume,
                 bool bloop) {}

long playUISound(const std::string &name) {
  GameSound gameSound = GameSounds.getSound(name);
  if (gameSound != nullptr && !gameSound.clips.isEmpty()) {
    GameSoundClip gameSoundClip = gameSound.getRandomClip();
    long long0 = this.uiEmitter.playClip(gameSoundClip, null);
    this.uiEmitter.tick();
    javafmod.FMOD_System_Update();
    return long0;
  } else {
    return 0L;
  }
}

bool isPlayingUISound(const std::string &name) {
  return this.uiEmitter.isPlaying(name);
}

bool isPlayingUISound(long eventInstance) {
  return this.uiEmitter.isPlaying(eventInstance);
}

void stopUISound(long eventInstance) {
  this.uiEmitter.stopSound(eventInstance);
}

bool IsMusicPlaying() { return false; }

bool isPlayingMusic() { return this.music.isPlaying(); }

public
ArrayList<Audio> getAmbientPieces() { return this.ambientPieces; }

void gatherInGameEventInstances() {
  this.pausedEventCount = 0;
  int int0 = javafmodJNI.FMOD_Studio_System_GetBankCount();
  if (this.bankList.length < int0) {
    this.bankList = new long[int0];
  }

  int0 = javafmodJNI.FMOD_Studio_System_GetBankList(this.bankList);

  for (int int1 = 0; int1 < int0; int1++) {
    int int2 = javafmodJNI.FMOD_Studio_Bank_GetEventCount(this.bankList[int1]);
    if (this.eventDescList.length < int2) {
      this.eventDescList = new long[int2];
    }

    int2 = javafmodJNI.FMOD_Studio_Bank_GetEventList(this.bankList[int1],
                                                     this.eventDescList);

    for (int int3 = 0; int3 < int2; int3++) {
      int int4 = javafmodJNI.FMOD_Studio_EventDescription_GetInstanceCount(
          this.eventDescList[int3]);
      if (this.eventInstList.length < int4) {
        this.eventInstList = new long[int4];
      }

      int4 = javafmodJNI.FMOD_Studio_EventDescription_GetInstanceList(
          this.eventDescList[int3], this.eventInstList);

      for (int int5 = 0; int5 < int4; int5++) {
        int int6 =
            javafmod.FMOD_Studio_GetPlaybackState(this.eventInstList[int5]);
        if (int6 !=
            FMOD_STUDIO_PLAYBACK_STATE.FMOD_STUDIO_PLAYBACK_STOPPED.index) {
          bool boolean0 = javafmodJNI.FMOD_Studio_EventInstance_GetPaused(
              this.eventInstList[int5]);
          if (!boolean0) {
            if (this.pausedEventInstances.length < this.pausedEventCount + 1) {
              this.pausedEventInstances = Arrays.copyOf(
                  this.pausedEventInstances, this.pausedEventCount + 128);
              this.pausedEventVolumes = Arrays.copyOf(
                  this.pausedEventVolumes, this.pausedEventInstances.length);
            }

            this.pausedEventInstances[this.pausedEventCount] =
                this.eventInstList[int5];
            this.pausedEventVolumes[this.pausedEventCount] =
                javafmodJNI.FMOD_Studio_EventInstance_GetVolume(
                    this.eventInstList[int5]);
            this.pausedEventCount++;
          }
        }
      }
    }
  }
}

void pauseSoundAndMusic() {
  bool boolean0 = true;
  if (GameClient.bClient) {
    this.muted = true;
    if (boolean0) {
      javafmod.FMOD_Studio_Bus_SetMute(this.inGameGroupBus, true);
      javafmod.FMOD_Studio_Bus_SetMute(this.musicGroupBus, true);
    } else {
      this.setSoundVolume(0.0F);
      this.setMusicVolume(0.0F);
      this.setAmbientVolume(0.0F);
      this.setVehicleEngineVolume(0.0F);
    }

    GameSounds.soundIsPaused = true;
  } else if (boolean0) {
    javafmod.FMOD_Studio_Bus_SetPaused(this.inGameGroupBus, true);
    javafmod.FMOD_Studio_Bus_SetPaused(this.musicGroupBus, true);
    javafmod.FMOD_Channel_SetPaused(
        FMODManager.instance.channelGroupInGameNonBankSounds, true);
    GameSounds.soundIsPaused = true;
  } else {
    long long0 = javafmod.FMOD_System_GetMasterChannelGroup();
    javafmod.FMOD_ChannelGroup_SetPaused(long0, true);
    javafmod.FMOD_ChannelGroup_SetVolume(long0, 0.0F);
    javafmodJNI.FMOD_Studio_System_FlushCommands();
    this.gatherInGameEventInstances();

    for (int int0 = 0; int0 < this.pausedEventCount; int0++) {
      javafmodJNI.FMOD_Studio_EventInstance_SetPaused(
          this.pausedEventInstances[int0], true);
    }

    javafmod.FMOD_Channel_SetPaused(
        FMODManager.instance.channelGroupInGameNonBankSounds, true);
    javafmod.FMOD_ChannelGroup_SetPaused(long0, false);
    javafmodJNI.FMOD_Studio_System_FlushCommands();
    javafmod.FMOD_ChannelGroup_SetVolume(long0, 1.0F);
    GameSounds.soundIsPaused = true;
  }
}

void resumeSoundAndMusic() {
  bool boolean0 = true;
  if (this.muted) {
    this.muted = false;
    if (boolean0) {
      javafmod.FMOD_Studio_Bus_SetMute(this.inGameGroupBus, false);
      javafmod.FMOD_Studio_Bus_SetMute(this.musicGroupBus, false);
      javafmod.FMOD_ChannelGroup_SetPaused(
          FMODManager.instance.channelGroupInGameNonBankSounds, false);
    } else {
      this.setSoundVolume(Core.getInstance().getOptionSoundVolume() / 10.0F);
      this.setMusicVolume(Core.getInstance().getOptionMusicVolume() / 10.0F);
      this.setAmbientVolume(Core.getInstance().getOptionAmbientVolume() /
                            10.0F);
      this.setVehicleEngineVolume(
          Core.getInstance().getOptionVehicleEngineVolume() / 10.0F);
    }

    GameSounds.soundIsPaused = false;
  } else if (boolean0) {
    javafmod.FMOD_Studio_Bus_SetPaused(this.inGameGroupBus, false);
    javafmod.FMOD_Studio_Bus_SetPaused(this.musicGroupBus, false);
    javafmod.FMOD_ChannelGroup_SetPaused(
        FMODManager.instance.channelGroupInGameNonBankSounds, false);
    GameSounds.soundIsPaused = false;
  } else {
    long long0 = javafmod.FMOD_System_GetMasterChannelGroup();
    javafmod.FMOD_ChannelGroup_SetPaused(long0, true);
    javafmodJNI.FMOD_Studio_System_FlushCommands();

    for (int int0 = 0; int0 < this.pausedEventCount; int0++) {
      try {
        javafmodJNI.FMOD_Studio_EventInstance_SetPaused(
            this.pausedEventInstances[int0], false);
      } catch (Throwable throwable) {
        throwable.printStackTrace();
      }
    }

    this.pausedEventCount = 0;
    javafmod.FMOD_ChannelGroup_SetPaused(long0, false);
    javafmod.FMOD_ChannelGroup_SetVolume(long0, 1.0F);
    javafmod.FMOD_ChannelGroup_SetPaused(
        FMODManager.instance.channelGroupInGameNonBankSounds, false);
    GameSounds.soundIsPaused = false;
  }
}

void debugScriptSound(Item item, const std::string &string) {
  if (string != nullptr && !string.isEmpty()) {
    if (!GameSounds.isKnownSound(string)) {
      DebugLog.General.warn("no such sound \"" + string + "\" in item " +
                            item.getFullName());
    }
  }
}

void debugScriptSounds() {
  if (Core.bDebug) {
    for (ScriptModule scriptModule :
         ScriptManager.instance.ModuleMap.values()) {
      for (Item item : scriptModule.ItemMap.values()) {
        this.debugScriptSound(item, item.getBreakSound());
        this.debugScriptSound(item, item.getBulletOutSound());
        this.debugScriptSound(item, item.getCloseSound());
        this.debugScriptSound(item, item.getCustomEatSound());
        this.debugScriptSound(item, item.getDoorHitSound());
        this.debugScriptSound(item, item.getCountDownSound());
        this.debugScriptSound(item, item.getExplosionSound());
        this.debugScriptSound(item, item.getImpactSound());
        this.debugScriptSound(item, item.getOpenSound());
        this.debugScriptSound(item, item.getPutInSound());
        this.debugScriptSound(item, item.getPlaceOneSound());
        this.debugScriptSound(item, item.getPlaceMultipleSound());
        this.debugScriptSound(item, item.getShellFallSound());
        this.debugScriptSound(item, item.getSwingSound());
        this.debugScriptSound(item, item.getInsertAmmoSound());
        this.debugScriptSound(item, item.getInsertAmmoStartSound());
        this.debugScriptSound(item, item.getInsertAmmoStopSound());
        this.debugScriptSound(item, item.getEjectAmmoSound());
        this.debugScriptSound(item, item.getEjectAmmoStartSound());
        this.debugScriptSound(item, item.getEjectAmmoStopSound());
      }
    }
  }
}

void registerEmitter(BaseSoundEmitter emitter) { this.emitters.add(emitter); }

void unregisterEmitter(BaseSoundEmitter emitter) {
  this.emitters.remove(emitter);
}

bool isListenerInRange(float x, float y, float range) {
  if (GameServer.bServer) {
    return false;
  } else {
    for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
      IsoPlayer player = IsoPlayer.players[int0];
      if (player != nullptr && !player.Traits.Deaf.isSet() &&
          IsoUtils.DistanceToSquared(player.x, player.y, x, y) <
              range * range) {
        return true;
      }
    }

    return false;
  }
}

void playNightAmbient(const std::string &choice) {
  DebugLog.log("playNightAmbient: " + choice);

  for (int int0 = 0; int0 < ambientSoundEffects.size(); int0++) {
    SoundManager.AmbientSoundEffect ambientSoundEffect0 =
        ambientSoundEffects.get(int0);
    if (ambientSoundEffect0.getName() == choice)) {
        ambientSoundEffect0.setVolume(Rand.Next(700, 1500) / 1000.0F);
        ambientSoundEffect0.start();
        this.ambientPieces.add(ambientSoundEffect0);
        return;
      }
  }

  SoundManager.AmbientSoundEffect ambientSoundEffect1 =
      new SoundManager.AmbientSoundEffect(choice);
  ambientSoundEffect1.setVolume(Rand.Next(700, 1500) / 1000.0F);
  ambientSoundEffect1.setName(choice);
  ambientSoundEffect1.start();
  this.ambientPieces.add(ambientSoundEffect1);
  ambientSoundEffects.add(ambientSoundEffect1);
}

void playMusic(const std::string &name) { this.DoMusic(name, false); }

void playAmbient(const std::string &name) {}

void playMusicNonTriggered(const std::string &name, float gain) {}

void stopMusic(const std::string &name) {
  if (this.isPlayingMusic()) {
    if (StringUtils.isNullOrWhitespace(name) ||
        name.equalsIgnoreCase(this.getCurrentMusicName())) {
      this.StopMusic();
    }
  }
}

void CheckDoMusic() {}

float getMusicPosition() {
  return this.isPlayingMusic() ? this.music.getPosition() : 0.0F;
}

void DoMusic(const std::string &name, bool bLoop) {
  if (this.AllowMusic && Core.getInstance().getOptionMusicVolume() != 0) {
    if (this.isPlayingMusic()) {
      this.StopMusic();
    }

    int int0 = Core.getInstance().getOptionMusicLibrary();
    bool boolean0 = int0 == 1;
    GameSound gameSound = GameSounds.getSound(name);
    GameSoundClip gameSoundClip = null;
    if (gameSound != nullptr && !gameSound.clips.isEmpty()) {
      gameSoundClip = gameSound.getRandomClip();
    }

    if (gameSoundClip != nullptr && gameSoundClip.getEvent() != nullptr) {
      if (gameSoundClip.eventDescription != nullptr) {
        long long0 = gameSoundClip.eventDescription.address;
        javafmod.FMOD_Studio_LoadEventSampleData(long0);
        this.music.instance =
            javafmod.FMOD_Studio_System_CreateEventInstance(long0);
        this.music.clip = gameSoundClip;
        this.music.effectiveVolume = gameSoundClip.getEffectiveVolume();
        javafmod.FMOD_Studio_EventInstance_SetParameterByName(
            this.music.instance, "Volume", 10.0F);
        javafmod.FMOD_Studio_EventInstance_SetVolume(
            this.music.instance, this.music.effectiveVolume);
        javafmod.FMOD_Studio_StartEvent(this.music.instance);
      }
    } else if (gameSoundClip != nullptr && gameSoundClip.getFile() != nullptr) {
      long long1 = FMODManager.instance.loadSound(gameSoundClip.getFile());
      if (long1 > 0L) {
        this.music.channel = javafmod.FMOD_System_PlaySound(long1, true);
        this.music.clip = gameSoundClip;
        this.music.effectiveVolume = gameSoundClip.getEffectiveVolume();
        javafmod.FMOD_Channel_SetVolume(this.music.channel,
                                        this.music.effectiveVolume);
        javafmod.FMOD_Channel_SetPitch(this.music.channel, gameSoundClip.pitch);
        javafmod.FMOD_Channel_SetPaused(this.music.channel, false);
      }
    }

    this.currentMusicName = name;
    this.currentMusicLibrary = boolean0 ? "official" : "earlyaccess";
  }
}

void PlayAsMusic(const std::string &name, Audio musicTrack, bool loop,
                 float volume) {}

void setMusicState(const std::string &stateName) {
  switch (stateName) {
  case "MainMenu":
    this.parameterMusicState.setState(ParameterMusicState.State.MainMenu);
    break;
  case "Loading":
    this.parameterMusicState.setState(ParameterMusicState.State.Loading);
    break;
  case "InGame":
    this.parameterMusicState.setState(ParameterMusicState.State.InGame);
    break;
  case "PauseMenu":
    this.parameterMusicState.setState(ParameterMusicState.State.PauseMenu);
    break;
  case "Tutorial":
    this.parameterMusicState.setState(ParameterMusicState.State.Tutorial);
    break;
  default:
    DebugLog.General.warn("unknown MusicState \"%s\"", stateName);
  }
}

void setMusicWakeState(IsoPlayer player, const std::string &stateName) {
  switch (stateName) {
  case "Awake":
    this.parameterMusicWakeState.setState(player,
                                          ParameterMusicWakeState.State.Awake);
    break;
  case "Sleeping":
    this.parameterMusicWakeState.setState(
        player, ParameterMusicWakeState.State.Sleeping);
    break;
  case "WakeNormal":
    this.parameterMusicWakeState.setState(
        player, ParameterMusicWakeState.State.WakeNormal);
    break;
  case "WakeNightmare":
    this.parameterMusicWakeState.setState(
        player, ParameterMusicWakeState.State.WakeNightmare);
    break;
  case "WakeZombies":
    this.parameterMusicWakeState.setState(
        player, ParameterMusicWakeState.State.WakeZombies);
    break;
  default:
    DebugLog.General.warn("unknown MusicWakeState \"%s\"", stateName);
  }
}

Audio PlayMusic(const std::string &n, const std::string &name, bool loop,
                float maxGain) {
  return null;
}

Audio PlaySound(const std::string &name, bool loop, float maxGain,
                float pitchVar) {
  return null;
}

Audio PlaySound(const std::string &name, bool loop, float maxGain) {
  if (GameServer.bServer) {
    return null;
  } else if (IsoWorld.instance == nullptr) {
    return null;
  } else {
    BaseSoundEmitter baseSoundEmitter = IsoWorld.instance.getFreeEmitter();
    baseSoundEmitter.setPos(0.0F, 0.0F, 0.0F);
    long long0 = baseSoundEmitter.playSound(name);
    return long0 != 0L ? new FMODAudio(baseSoundEmitter) : nullptr;
  }
}

Audio PlaySoundEvenSilent(const std::string &name, bool loop, float maxGain) {
  return null;
}

Audio PlayJukeboxSound(const std::string &name, bool loop, float maxGain) {
  return null;
}

Audio PlaySoundWav(const std::string &name, bool loop, float maxGain,
                   float pitchVar) {
  return null;
}

Audio PlaySoundWav(const std::string &name, bool loop, float maxGain) {
  return null;
}

Audio PlaySoundWav(const std::string &name, int variations, bool loop,
                   float maxGain) {
  return null;
}

void update3D() {}

Audio PlayWorldSound(const std::string &name, IsoGridSquare source,
                     float pitchVar, float radius, float maxGain,
                     bool ignoreOutside) {
  return this.PlayWorldSound(name, false, source, pitchVar, radius, maxGain,
                             ignoreOutside);
}

Audio PlayWorldSound(const std::string &name, bool loop, IsoGridSquare source,
                     float pitchVar, float radius, float maxGain,
                     bool ignoreOutside) {
  if (!GameServer.bServer && source != nullptr) {
    if (GameClient.bClient) {
      GameClient.instance.PlayWorldSound(name, source.x, source.y,
                                         (byte)source.z);
    }

    return this.PlayWorldSoundImpl(name, loop, source.getX(), source.getY(),
                                   source.getZ(), pitchVar, radius, maxGain,
                                   ignoreOutside);
  } else {
    return null;
  }
}

Audio PlayWorldSoundImpl(const std::string &name, bool loop, int sx, int sy,
                         int sz, float pitchVar, float radius, float maxGain,
                         bool ignoreOutside) {
  BaseSoundEmitter baseSoundEmitter =
      IsoWorld.instance.getFreeEmitter(sx + 0.5F, sy + 0.5F, sz);
  long long0 = baseSoundEmitter.playSoundImpl(name, (IsoObject)null);
  return new FMODAudio(baseSoundEmitter);
}

Audio PlayWorldSound(const std::string &name, IsoGridSquare source,
                     float pitchVar, float radius, float maxGain, int choices,
                     bool ignoreOutside) {
  return this.PlayWorldSound(name, source, pitchVar, radius, maxGain,
                             ignoreOutside);
}

Audio PlayWorldSoundWav(const std::string &name, IsoGridSquare source,
                        float pitchVar, float radius, float maxGain,
                        bool ignoreOutside) {
  return this.PlayWorldSoundWav(name, false, source, pitchVar, radius, maxGain,
                                ignoreOutside);
}

Audio PlayWorldSoundWav(const std::string &name, bool loop,
                        IsoGridSquare source, float pitchVar, float radius,
                        float maxGain, bool ignoreOutside) {
  if (!GameServer.bServer && source != nullptr) {
    if (GameClient.bClient) {
      GameClient.instance.PlayWorldSound(name, source.getX(), source.getY(),
                                         (byte)source.getZ());
    }

    return this.PlayWorldSoundWavImpl(name, loop, source, pitchVar, radius,
                                      maxGain, ignoreOutside);
  } else {
    return null;
  }
}

Audio PlayWorldSoundWavImpl(const std::string &name, bool loop,
                            IsoGridSquare source, float pitchVar, float radius,
                            float maxGain, bool ignoreOutside) {
  BaseSoundEmitter baseSoundEmitter = IsoWorld.instance.getFreeEmitter(
      source.getX() + 0.5F, source.getY() + 0.5F, source.getZ());
  baseSoundEmitter.playSound(name);
  return new FMODAudio(baseSoundEmitter);
}

void PlayWorldSoundWav(const std::string &name, IsoGridSquare source,
                       float pitchVar, float radius, float maxGain, int choices,
                       bool ignoreOutside) {
  int integer = Rand.Next(choices) + 1;
  this.PlayWorldSoundWav(name + integer.toString(), source, pitchVar, radius,
                         maxGain, ignoreOutside);
}

Audio PrepareMusic(const std::string &name) { return null; }

Audio Start(Audio musicTrack, float f, const std::string &PrefMusic) {
  return null;
}

void Update() {
  if (!this.initialized) {
    this.initialized = true;
    this.inGameGroupBus = javafmod.FMOD_Studio_System_GetBus("bus:/InGame");
    this.musicGroupBus = javafmod.FMOD_Studio_System_GetBus("bus:/Music");
    this.musicEmitter = std::make_unique<FMODSoundEmitter>();
    this.unregisterEmitter(this.musicEmitter);
    this.musicEmitter.parameterUpdater = this;
    this.fmodParameters.add(this.parameterMusicActionStyle);
    this.fmodParameters.add(this.parameterMusicLibrary);
    this.fmodParameters.add(this.parameterMusicState);
    this.fmodParameters.add(this.parameterMusicWakeState);
    this.fmodParameters.add(this.parameterMusicZombiesTargeting);
    this.fmodParameters.add(this.parameterMusicZombiesVisible);
    this.uiEmitter = std::make_unique<FMODSoundEmitter>();
  }

  FMODSoundEmitter.update();
  this.updateMusic();
  this.uiEmitter.tick();

  for (int int0 = 0; int0 < this.ambientPieces.size(); int0++) {
    Audio audio = this.ambientPieces.get(int0);
    if (IsoPlayer.allPlayersDead()) {
      audio.stop();
    }

    if (!audio.isPlaying()) {
      audio.stop();
      this.ambientPieces.remove(audio);
      int0--;
    } else if (audio instanceof SoundManager.AmbientSoundEffect) {
      ((SoundManager.AmbientSoundEffect)audio).update();
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

bool HasMusic(Audio var1) { return false; }

void Purge() {}

void stop() {
  for (BaseSoundEmitter baseSoundEmitter : this.emitters) {
    baseSoundEmitter.stopAll();
  }

  this.emitters.clear();
  long long0 = javafmod.FMOD_System_GetMasterChannelGroup();
  javafmod.FMOD_ChannelGroup_Stop(long0);
  this.pausedEventCount = 0;
}

void StopMusic() { this.music.stop(); }

void StopSound(Audio SoundEffect) { SoundEffect.stop(); }

void CacheSound(const std::string &file) {}

void update4() {}

void update2() {}

void update3() {}

void update1() {}

void setSoundVolume(float volume) { this.SoundVolume = volume; }

float getSoundVolume() { return this.SoundVolume; }

void setAmbientVolume(float volume) { this.AmbientVolume = volume; }

float getAmbientVolume() { return this.AmbientVolume; }

void setMusicVolume(float volume) {
  this.MusicVolume = volume;
  if (!this.muted) {
    ;
  }
}

float getMusicVolume() { return this.MusicVolume; }

void setVehicleEngineVolume(float volume) { this.VehicleEngineVolume = volume; }

float getVehicleEngineVolume() { return this.VehicleEngineVolume; }

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
    this.musicCombinedEvent =
        this.musicEmitter.playSoundImpl("MusicCombined", (IsoObject) nullptr);
    if (this.musicCombinedEvent != 0L &&
        !System.getProperty("os.name").contains("OS X")) {
      javafmod.FMOD_Studio_EventInstance_SetCallback(
          this.musicCombinedEvent, this.musicEventCallback,
          FMOD_STUDIO_EVENT_CALLBACK_TYPE
              .FMOD_STUDIO_EVENT_CALLBACK_TIMELINE_MARKER.bit);
    }
  }

  if (this.musicEmitter.isPlaying(this.musicCombinedEvent)) {
    this.musicEmitter.setVolume(this.musicCombinedEvent,
                                this.AllowMusic ? 1.0F : 0.0F);
  }

  this.musicEmitter.tick();
}

public
static final class AmbientSoundEffect implements Audio {
  std::string name;
  long eventInstance;
  float gain;
  GameSoundClip clip;
  float effectiveVolume;

public
  AmbientSoundEffect(const std::string &_name) {
    GameSound gameSound = GameSounds.getSound(_name);
    if (gameSound != nullptr && !gameSound.clips.isEmpty()) {
      GameSoundClip gameSoundClip = gameSound.getRandomClip();
      if (gameSoundClip.getEvent() != nullptr) {
        if (gameSoundClip.eventDescription != nullptr) {
          this.eventInstance = javafmod.FMOD_Studio_System_CreateEventInstance(
              gameSoundClip.eventDescription.address);
          if (this.eventInstance >= 0L) {
            this.clip = gameSoundClip;
          }
        }
      }
    }
  }

  void setVolume(float volume) {
    if (this.eventInstance > 0L) {
      this.gain = volume;
      this.effectiveVolume = this.clip.getEffectiveVolume();
      javafmod.FMOD_Studio_EventInstance_SetVolume(
          this.eventInstance, this.gain * this.effectiveVolume);
    }
  }

  void start() {
    if (this.eventInstance > 0L) {
      javafmod.FMOD_Studio_StartEvent(this.eventInstance);
    }
  }

  void pause() {}

  void stop() {
    DebugLog.log("stop ambient " + this.name);
    if (this.eventInstance > 0L) {
      javafmod.FMOD_Studio_EventInstance_Stop(this.eventInstance, false);
    }
  }

  bool isPlaying() {
    if (this.eventInstance <= 0L) {
      return false;
    } else {
      int int0 = javafmod.FMOD_Studio_GetPlaybackState(this.eventInstance);
      return int0 == FMOD_STUDIO_PLAYBACK_STATE.FMOD_STUDIO_PLAYBACK_STARTING
                         .index ||
             int0 == FMOD_STUDIO_PLAYBACK_STATE.FMOD_STUDIO_PLAYBACK_PLAYING
                         .index ||
             int0 == FMOD_STUDIO_PLAYBACK_STATE.FMOD_STUDIO_PLAYBACK_SUSTAINING
                         .index;
    }
  }

  void setName(const std::string &choice) { this.name = choice; }

  std::string getName() { return this.name; }

  void update() {
    if (this.clip != nullptr) {
      this.clip = this.clip.checkReloaded();
      float float0 = this.clip.getEffectiveVolume();
      if (this.effectiveVolume != float0) {
        this.effectiveVolume = float0;
        javafmod.FMOD_Studio_EventInstance_SetVolume(
            this.eventInstance, this.gain * this.effectiveVolume);
      }
    }
  }
}

private static final class Music {
  GameSoundClip clip;
  long instance;
  long channel;
  long sound;
  float effectiveVolume;

  bool isPlaying() {
    if (this.instance != 0L) {
      int int0 = javafmod.FMOD_Studio_GetPlaybackState(this.instance);
      return int0 != FMOD_STUDIO_PLAYBACK_STATE.FMOD_STUDIO_PLAYBACK_STOPPED
                         .index &&
             int0 !=
                 FMOD_STUDIO_PLAYBACK_STATE.FMOD_STUDIO_PLAYBACK_STOPPING.index;
    } else {
      return this.channel != 0L &&
             javafmod.FMOD_Channel_IsPlaying(this.channel);
    }
  }

  void update() {
    this.clip = this.clip.checkReloaded();
    float float0 = this.clip.getEffectiveVolume();
    if (this.effectiveVolume != float0) {
      this.effectiveVolume = float0;
      if (this.instance != 0L) {
        javafmod.FMOD_Studio_EventInstance_SetVolume(this.instance,
                                                     this.effectiveVolume);
      }

      if (this.channel != 0L) {
        javafmod.FMOD_Channel_SetVolume(this.channel, this.effectiveVolume);
      }
    }
  }

  float getPosition() {
    if (this.instance != 0L) {
      long long0 = javafmod.FMOD_Studio_GetTimelinePosition(this.instance);
      return (float)long0;
    } else if (this.channel != 0L) {
      long long1 = javafmod.FMOD_Channel_GetPosition(
          this.channel, FMODManager.FMOD_TIMEUNIT_MS);
      return (float)long1;
    } else {
      return 0.0F;
    }
  }

  void stop() {
    if (this.instance != 0L) {
      javafmod.FMOD_Studio_EventInstance_Stop(this.instance, false);
      javafmod.FMOD_Studio_ReleaseEventInstance(this.instance);
      this.instance = 0L;
    }

    if (this.channel != 0L) {
      javafmod.FMOD_Channel_Stop(this.channel);
      this.channel = 0L;
      javafmod.FMOD_Sound_Release(this.sound);
      this.sound = 0L;
    }
  }
}
}
} // namespace zombie
