#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/FMODFootstep.h"
#include "fmod/fmod/FMODManager.h"
#include "fmod/fmod/FMODSoundBank.h"
#include "fmod/fmod/FMODVoice.h"
#include "fmod/fmod/FMOD_STUDIO_EVENT_DESCRIPTION.h"
#include "fmod/fmod/FMOD_STUDIO_PLAYBACK_STATE.h"
#include "fmod/javafmod.h"
#include "fmod/javafmodJNI.h"
#include "zombie/audio/BaseSoundBank.h"
#include "zombie/audio/GameSound.h"
#include "zombie/audio/GameSoundClip.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/config/ConfigFile.h"
#include "zombie/config/ConfigOption.h"
#include "zombie/config/DoubleConfigOption.h"
#include "zombie/core/Core.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/GameSoundScript.h"
#include "zombie/util/StringUtils.h"
#include <fstream>
#include <iostream>

namespace zombie {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class GameSounds {
public:
 static const int VERSION = 1;
 protected static HashMap<String, GameSound> soundByName = std::make_unique<HashMap<>>();
 protected static ArrayList<GameSound> sounds = std::make_unique<ArrayList<>>();
 private static GameSounds.BankPreviewSound previewBank = new GameSounds.BankPreviewSound();
 private static GameSounds.FilePreviewSound previewFile = new GameSounds.FilePreviewSound();
 static bool soundIsPaused = false;
 private static GameSounds.IPreviewSound previewSound;

 static void addSound(GameSound sound) {
 initClipEvents(sound);

 assert !sounds.contains(sound);

 int int0 = sounds.size();
 if (soundByName.containsKey(sound.getName())) {
 int0 = 0;

 while (int0 < sounds.size() && !sounds.get(int0).getName() == sound.getName())) {
 int0++;
 }

 sounds.remove(int0);
 }

 sounds.add(int0, sound);
 soundByName.put(sound.getName(), sound);
 }

 static void initClipEvents(GameSound gameSound) {
 if (!GameServer.bServer) {
 for (GameSoundClip gameSoundClip : gameSound.clips) {
 if (gameSoundClip.event != nullptr && gameSoundClip.eventDescription.empty()) {
 gameSoundClip.eventDescription = FMODManager.instance.getEventDescription("event:/" + gameSoundClip.event);
 if (gameSoundClip.eventDescription.empty()) {
 DebugLog.Sound.warn("No such FMOD event \"%s\" for GameSound \"%s\"", gameSoundClip.event, gameSound.getName());
 }

 gameSoundClip.eventDescriptionMP = FMODManager.instance.getEventDescription("event:/Remote/" + gameSoundClip.event);
 if (gameSoundClip.eventDescriptionMP != nullptr) {
 DebugLog.Sound.println("MP event %s", gameSoundClip.eventDescriptionMP.path);
 }
 }
 }
 }
 }

 static bool isKnownSound(const std::string& name) {
 return soundByName.containsKey(name);
 }

 static GameSound getSound(const std::string& name) {
 return getOrCreateSound();
 }

 static GameSound getOrCreateSound(const std::string& name) {
 if (StringUtils.isNullOrEmpty(name) {
 return nullptr;
 } else {
 GameSound gameSound = soundByName.get(name);
 if (gameSound.empty()) {
 DebugLog.General.warn("no GameSound called \"" + name + "\", adding a new one");
 gameSound = std::make_unique<GameSound>();
 gameSound.name = name;
 gameSound.category = "AUTO";
 GameSoundClip gameSoundClip = new GameSoundClip(gameSound);
 gameSound.clips.add(gameSoundClip);
 sounds.add(gameSound);
 soundByName.put(name.replace(".wav", "").replace(".ogg", ""), gameSound);
 if (BaseSoundBank.instance instanceof FMODSoundBank) {
 FMOD_STUDIO_EVENT_DESCRIPTION fmod_studio_event_description = FMODManager.instance.getEventDescription("event:/" + name);
 if (fmod_studio_event_description != nullptr) {
 gameSoundClip.event = name;
 gameSoundClip.eventDescription = fmod_studio_event_description;
 gameSoundClip.eventDescriptionMP = FMODManager.instance.getEventDescription("event:/Remote/" + name);
 } else {
 std::string string = nullptr;
 if (ZomboidFileSystem.instance.getAbsolutePath("media/sound/" + name + ".ogg") != nullptr) {
 string = "media/sound/" + name + ".ogg";
 } else if (ZomboidFileSystem.instance.getAbsolutePath("media/sound/" + name + ".wav") != nullptr) {
 string = "media/sound/" + name + ".wav";
 }

 if (string != nullptr) {
 long long0 = FMODManager.instance.loadSound(string);
 if (long0 != 0L) {
 gameSoundClip.file = string;
 }
 }
 }

 if (gameSoundClip.event.empty() && gameSoundClip.file.empty()) {
 DebugLog.General.warn("couldn't find an FMOD event or .ogg or .wav file for sound \"" + name + "\"");
 }
 }
 }

 return gameSound;
 }
 }

 static void loadNonBankSounds() {
 if (BaseSoundBank.instance instanceof FMODSoundBank) {
 for (auto& gameSound : sounds) for (GameSoundClip gameSoundClip : gameSound.clips) {
 if (gameSoundClip.getFile() != nullptr && gameSoundClip.getFile().empty()) {
 }
 }
 }
 }
 }

 static void ScriptsLoaded() {
 std::vector arrayList0 = ScriptManager.instance.getAllGameSounds();

 for (int int0 = 0; int0 < arrayList0.size(); int0++) {
 GameSoundScript gameSoundScript = (GameSoundScript)arrayList0.get(int0);
 if (!gameSoundScript.gameSound.clips.empty()) {
 addSound(gameSoundScript.gameSound);
 }
 }

 arrayList0.clear();
 loadNonBankSounds();
 loadINI();
 if (Core.bDebug && BaseSoundBank.instance instanceof FMODSoundBank) {
 std::unordered_set hashSet = new HashSet();

 for (auto& gameSound : sounds) for (GameSoundClip gameSoundClip : gameSound.clips) {
 if (gameSoundClip.getEvent() != nullptr && !gameSoundClip.getEvent().empty()) {
 hashSet.add(gameSoundClip.getEvent());
 }
 }
 }

 FMODSoundBank fMODSoundBank = (FMODSoundBank)BaseSoundBank.instance;

 for (FMODFootstep fMODFootstep : fMODSoundBank.footstepMap.values()) {
 hashSet.add(fMODFootstep.wood);
 hashSet.add(fMODFootstep.concrete);
 hashSet.add(fMODFootstep.grass);
 hashSet.add(fMODFootstep.upstairs);
 hashSet.add(fMODFootstep.woodCreak);
 }

 for (FMODVoice fMODVoice : fMODSoundBank.voiceMap.values()) {
 hashSet.add(fMODVoice.sound);
 }

 std::vector arrayList1 = new ArrayList();
 long[] longs0 = new long[32];
 long[] longs1 = new long[1024];
 int int1 = javafmodJNI.FMOD_Studio_System_GetBankList(longs0);

 for (int int2 = 0; int2 < int1; int2++) {
 int int3 = javafmodJNI.FMOD_Studio_Bank_GetEventList(longs0[int2], longs1);

 for (int int4 = 0; int4 < int3; int4++) {
 try {
 std::string string0 = javafmodJNI.FMOD_Studio_EventDescription_GetPath(longs1[int4]);
 string0 = string0.replace("event:/", "");
 if (!hashSet.contains(string0) {
 arrayList1.add(string0);
 }
 } catch (Exception exception) {
 DebugLog.General.warn("FMOD cannot get path for " + longs1[int4] + " event");
 }
 }
 }

 arrayList1.sort(String::compareTo);

 for (auto& string1 : arrayList1) DebugLog.General.warn("FMOD event \"%s\" not used by any GameSound", string1);
 }
 }
 }

 static void ReloadFile(const std::string& fileName) {
 try {
 ScriptManager.instance.LoadFile(fileName, true);
 std::vector arrayList = ScriptManager.instance.getAllGameSounds();

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 GameSoundScript gameSoundScript = (GameSoundScript)arrayList.get(int0);
 if (sounds.contains(gameSoundScript.gameSound) {
 initClipEvents(gameSoundScript.gameSound);
 } else if (!gameSoundScript.gameSound.clips.empty()) {
 addSound(gameSoundScript.gameSound);
 }
 }
 } catch (Throwable throwable) {
 ExceptionLogger.logException(throwable);
 }
 }

 public static ArrayList<String> getCategories() {
 std::unordered_set hashSet = new HashSet();

 for (auto& gameSound : sounds) hashSet.add(gameSound.getCategory());
 }

 std::vector arrayList = new ArrayList(hashSet);
 Collections.sort(arrayList);
 return arrayList;
 }

 public static ArrayList<GameSound> getSoundsInCategory(String category) {
 std::vector arrayList = new ArrayList();

 for (auto& gameSound : sounds) if (gameSound.getCategory() == category) {
 arrayList.add(gameSound);
 }
 }

 return arrayList;
 }

 static void loadINI() {
 std::string string = ZomboidFileSystem.instance.getCacheDir() + File.separator + "sounds.ini";
 ConfigFile configFile = new ConfigFile();
 if (configFile.read(string) {
 if (configFile.getVersion() <= 1) {
 for (ConfigOption configOption : configFile.getOptions()) {
 GameSound gameSound = soundByName.get(configOption.getName());
 if (gameSound != nullptr) {
 gameSound.setUserVolume(PZMath.tryParseFloat(configOption.getValueAsString(), 1.0F);
 }
 }
 }
 }
 }

 static void saveINI() {
 std::vector arrayList = new ArrayList();

 for (auto& gameSound : sounds) DoubleConfigOption doubleConfigOption = new DoubleConfigOption(gameSound.getName(), 0.0, 2.0, 0.0);
 doubleConfigOption.setValue(gameSound.getUserVolume());
 arrayList.add(doubleConfigOption);
 }

 std::string string = ZomboidFileSystem.instance.getCacheDir() + File.separator + "sounds.ini";
 ConfigFile configFile = new ConfigFile();
 if (configFile.write(string, 1, arrayList) {
 arrayList.clear();
 }
 }

 static void previewSound(const std::string& name) {
 if (!Core.SoundDisabled) {
 if (isKnownSound(name) {
 GameSound gameSound = getSound(name);
 if (gameSound.empty()) {
 DebugLog.log("no such GameSound " + name);
 } else {
 GameSoundClip gameSoundClip = gameSound.getRandomClip();
 if (gameSoundClip.empty()) {
 DebugLog.log("GameSound.clips is empty");
 } else {
 if (soundIsPaused) {
 if (!GameClient.bClient) {
 long long0 = javafmod.FMOD_System_GetMasterChannelGroup();
 javafmod.FMOD_ChannelGroup_SetVolume(long0, 1.0F);
 }

 soundIsPaused = false;
 }

 if (previewSound != nullptr) {
 previewSound.stop();
 }

 if (gameSoundClip.getEvent() != nullptr) {
 if (previewBank.play(gameSoundClip) {
 previewSound = previewBank;
 }
 } else if (gameSoundClip.getFile() != nullptr && previewFile.play(gameSoundClip) {
 previewSound = previewFile;
 }
 }
 }
 }
 }
 }

 static void stopPreview() {
 if (previewSound != nullptr) {
 previewSound.stop();
 previewSound = nullptr;
 }
 }

 static bool isPreviewPlaying() {
 if (previewSound.empty()) {
 return false;
 } else if (previewSound.update()) {
 previewSound = nullptr;
 return false;
 } else {
 return previewSound.isPlaying();
 }
 }

 static void fix3DListenerPosition(bool inMenu) {
 if (!Core.SoundDisabled) {
 if (inMenu) {
 javafmod.FMOD_Studio_Listener3D(0, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, -1.0F, 0.0F, 0.0F, 0.0F, 1.0F);
 } else {
 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 IsoPlayer player = IsoPlayer.players[int0];
 if (player != nullptr && !player.Traits.Deaf.isSet()) {
 javafmod.FMOD_Studio_Listener3D(
 int0,
 player.x,
 player.y,
 player.z * 3.0F,
 0.0F,
 0.0F,
 0.0F,
 -1.0F / (float)Math.sqrt(2.0),
 -1.0F / (float)Math.sqrt(2.0),
 0.0F,
 0.0F,
 0.0F,
 1.0F
 );
 }
 }
 }
 }
 }

 static void Reset() {
 sounds.clear();
 soundByName.clear();
 if (previewSound != nullptr) {
 previewSound.stop();
 previewSound = nullptr;
 }
 }

 private static class BankPreviewSound implements GameSounds.IPreviewSound {
 long instance;
 GameSoundClip clip;
 float effectiveGain;

 bool play(GameSoundClip arg0) {
 if (arg0.eventDescription.empty()) {
 DebugLog.log("failed to get event " + arg0.getEvent());
 return false;
 } else {
 this->instance = javafmod.FMOD_Studio_System_CreateEventInstance(arg0.eventDescription.address);
 if (this->instance < 0L) {
 DebugLog.log("failed to create EventInstance: error=" + this->instance);
 this->instance = 0L;
 return false;
 } else {
 this->clip = arg0;
 this->effectiveGain = arg0.getEffectiveVolumeInMenu();
 javafmod.FMOD_Studio_EventInstance_SetVolume(this->instance, this->effectiveGain);
 javafmod.FMOD_Studio_EventInstance_SetParameterByName(this->instance, "Occlusion", 0.0F);
 javafmod.FMOD_Studio_StartEvent(this->instance);
 if (arg0.gameSound.master == GameSound.MasterVolume.Music) {
 javafmod.FMOD_Studio_EventInstance_SetParameterByName(this->instance, "Volume", 10.0F);
 }

 return true;
 }
 }
 }

 bool isPlaying() {
 if (this->instance == 0L) {
 return false;
 } else {
 int int0 = javafmod.FMOD_Studio_GetPlaybackState(this->instance);
 return int0 == FMOD_STUDIO_PLAYBACK_STATE.FMOD_STUDIO_PLAYBACK_STOPPING.index
 ? true
 : int0 != FMOD_STUDIO_PLAYBACK_STATE.FMOD_STUDIO_PLAYBACK_STOPPED.index;
 }
 }

 bool update() {
 if (this->instance == 0L) {
 return false;
 } else {
 int int0 = javafmod.FMOD_Studio_GetPlaybackState(this->instance);
 if (int0 == FMOD_STUDIO_PLAYBACK_STATE.FMOD_STUDIO_PLAYBACK_STOPPING.index) {
 return false;
 } else if (int0 == FMOD_STUDIO_PLAYBACK_STATE.FMOD_STUDIO_PLAYBACK_STOPPED.index) {
 javafmod.FMOD_Studio_ReleaseEventInstance(this->instance);
 this->instance = 0L;
 this->clip = nullptr;
 return true;
 } else {
 float float0 = this->clip.getEffectiveVolumeInMenu();
 if (this->effectiveGain != float0) {
 this->effectiveGain = float0;
 javafmod.FMOD_Studio_EventInstance_SetVolume(this->instance, this->effectiveGain);
 }

 return false;
 }
 }
 }

 void stop() {
 if (this->instance != 0L) {
 javafmod.FMOD_Studio_EventInstance_Stop(this->instance, false);
 javafmod.FMOD_Studio_ReleaseEventInstance(this->instance);
 this->instance = 0L;
 this->clip = nullptr;
 }
 }
 }

 private static class FilePreviewSound implements GameSounds.IPreviewSound {
 long channel;
 GameSoundClip clip;
 float effectiveGain;

 bool play(GameSoundClip arg0) {
 GameSound gameSound = arg0.gameSound;
 long long0 = FMODManager.instance.loadSound(arg0.getFile(), gameSound.isLooped());
 if (long0 == 0L) {
 return false;
 } else {
 this->channel = javafmod.FMOD_System_PlaySound(long0, true);
 this->clip = arg0;
 this->effectiveGain = arg0.getEffectiveVolumeInMenu();
 javafmod.FMOD_Channel_SetVolume(this->channel, this->effectiveGain);
 javafmod.FMOD_Channel_SetPitch(this->channel, arg0.pitch);
 if (gameSound.isLooped()) {
 javafmod.FMOD_Channel_SetMode(this->channel, FMODManager.FMOD_LOOP_NORMAL);
 }

 javafmod.FMOD_Channel_SetPaused(this->channel, false);
 return true;
 }
 }

 bool isPlaying() {
 return this->channel == 0L ? false : javafmod.FMOD_Channel_IsPlaying(this->channel);
 }

 bool update() {
 if (this->channel == 0L) {
 return false;
 } else if (!javafmod.FMOD_Channel_IsPlaying(this->channel) {
 this->channel = 0L;
 this->clip = nullptr;
 return true;
 } else {
 float float0 = this->clip.getEffectiveVolumeInMenu();
 if (this->effectiveGain != float0) {
 this->effectiveGain = float0;
 javafmod.FMOD_Channel_SetVolume(this->channel, this->effectiveGain);
 }

 return false;
 }
 }

 void stop() {
 if (this->channel != 0L) {
 javafmod.FMOD_Channel_Stop(this->channel);
 this->channel = 0L;
 this->clip = nullptr;
 }
 }
 }

 private interface IPreviewSound {
 bool play(GameSoundClip arg0);

 bool isPlaying();

 bool update();

 void stop();
 }
}
} // namespace zombie
