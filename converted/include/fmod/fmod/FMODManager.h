#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/javafmod.h"
#include "fmod/javafmodJNI.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/Vector2.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace fmod {
namespace fmod {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class FMODManager {
public:
 static FMODManager instance = new FMODManager();
 static int FMOD_STUDIO_INIT_NORMAL = 0;
 static int FMOD_STUDIO_INIT_LIVEUPDATE = 1;
 static int FMOD_STUDIO_INIT_ALLOW_MISSING_PLUGINS = 2;
 static int FMOD_STUDIO_INIT_SYNCHRONOUS_UPDATE = 4;
 static int FMOD_STUDIO_INIT_DEFERRED_CALLBACKS = 8;
 static int FMOD_INIT_NORMAL = 0;
 static int FMOD_INIT_STREAM_FROM_UPDATE = 1;
 static int FMOD_INIT_MIX_FROM_UPDATE = 2;
 static int FMOD_INIT_3D_RIGHTHANDED = 4;
 static int FMOD_INIT_CHANNEL_LOWPASS = 256;
 static int FMOD_INIT_CHANNEL_DISTANCEFILTER = 512;
 static int FMOD_INIT_PROFILE_ENABLE = 65536;
 static int FMOD_INIT_VOL0_BECOMES_VIRTUAL = 131072;
 static int FMOD_INIT_GEOMETRY_USECLOSEST = 262144;
 static int FMOD_INIT_PREFER_DOLBY_DOWNMIX = 524288;
 static int FMOD_INIT_THREAD_UNSAFE = 1048576;
 static int FMOD_INIT_PROFILE_METER_ALL = 2097152;
 static int FMOD_DEFAULT = 0;
 static int FMOD_LOOP_OFF = 1;
 static int FMOD_LOOP_NORMAL = 2;
 static int FMOD_LOOP_BIDI = 4;
 static int FMOD_2D = 8;
 static int FMOD_3D = 16;
 static int FMOD_HARDWARE = 32;
 static int FMOD_SOFTWARE = 64;
 static int FMOD_CREATESTREAM = 128;
 static int FMOD_CREATESAMPLE = 256;
 static int FMOD_CREATECOMPRESSEDSAMPLE = 512;
 static int FMOD_OPENUSER = 1024;
 static int FMOD_OPENMEMORY = 2048;
 static int FMOD_OPENMEMORY_POINT = 268435456;
 static int FMOD_OPENRAW = 4096;
 static int FMOD_OPENONLY = 8192;
 static int FMOD_ACCURATETIME = 16384;
 static int FMOD_MPEGSEARCH = 32768;
 static int FMOD_NONBLOCKING = 65536;
 static int FMOD_UNIQUE = 131072;
 static int FMOD_3D_HEADRELATIVE = 262144;
 static int FMOD_3D_WORLDRELATIVE = 524288;
 static int FMOD_3D_INVERSEROLLOFF = 1048576;
 static int FMOD_3D_LINEARROLLOFF = 2097152;
 static int FMOD_3D_LINEARSQUAREROLLOFF = 4194304;
 static int FMOD_3D_INVERSETAPEREDROLLOFF = 8388608;
 static int FMOD_3D_CUSTOMROLLOFF = 67108864;
 static int FMOD_3D_IGNOREGEOMETRY = 1073741824;
 static int FMOD_IGNORETAGS = 33554432;
 static int FMOD_LOWMEM = 134217728;
 static int FMOD_LOADSECONDARYRAM = 536870912;
 static int FMOD_VIRTUAL_PLAYFROMSTART = Integer.MIN_VALUE;
 static int FMOD_PRESET_OFF = 0;
 static int FMOD_PRESET_GENERIC = 1;
 static int FMOD_PRESET_PADDEDCELL = 2;
 static int FMOD_PRESET_ROOM = 3;
 static int FMOD_PRESET_BATHROOM = 4;
 static int FMOD_PRESET_LIVINGROOM = 5;
 static int FMOD_PRESET_STONEROOM = 6;
 static int FMOD_PRESET_AUDITORIUM = 7;
 static int FMOD_PRESET_CONCERTHALL = 8;
 static int FMOD_PRESET_CAVE = 9;
 static int FMOD_PRESET_ARENA = 10;
 static int FMOD_PRESET_HANGAR = 11;
 static int FMOD_PRESET_CARPETTEDHALLWAY = 12;
 static int FMOD_PRESET_HALLWAY = 13;
 static int FMOD_PRESET_STONECORRIDOR = 14;
 static int FMOD_PRESET_ALLEY = 15;
 static int FMOD_PRESET_FOREST = 16;
 static int FMOD_PRESET_CITY = 17;
 static int FMOD_PRESET_MOUNTAINS = 18;
 static int FMOD_PRESET_QUARRY = 19;
 static int FMOD_PRESET_PLAIN = 20;
 static int FMOD_PRESET_PARKINGLOT = 21;
 static int FMOD_PRESET_SEWERPIPE = 22;
 static int FMOD_PRESET_UNDERWATER = 23;
 static int FMOD_TIMEUNIT_MS = 1;
 static int FMOD_TIMEUNIT_PCM = 2;
 static int FMOD_TIMEUNIT_PCMBYTES = 4;
 static int FMOD_STUDIO_PLAYBACK_PLAYING = 0;
 static int FMOD_STUDIO_PLAYBACK_SUSTAINING = 1;
 static int FMOD_STUDIO_PLAYBACK_STOPPED = 2;
 static int FMOD_STUDIO_PLAYBACK_STARTING = 3;
 static int FMOD_STUDIO_PLAYBACK_STOPPING = 4;
 static int FMOD_SOUND_FORMAT_NONE = 0;
 static int FMOD_SOUND_FORMAT_PCM8 = 1;
 static int FMOD_SOUND_FORMAT_PCM16 = 2;
 static int FMOD_SOUND_FORMAT_PCM24 = 3;
 static int FMOD_SOUND_FORMAT_PCM32 = 4;
 static int FMOD_SOUND_FORMAT_PCMFLOAT = 5;
 static int FMOD_SOUND_FORMAT_BITSTREAM = 6;
 ArrayList<Long> Sounds = std::make_unique<ArrayList<>>();
 ArrayList<Long> Instances = std::make_unique<ArrayList<>>();
 long channelGroupInGameNonBankSounds = 0L;
 private HashMap<String, FMOD_STUDIO_PARAMETER_DESCRIPTION> parameterDescriptionMap = std::make_unique<HashMap<>>();
 private HashMap<String, FMOD_STUDIO_EVENT_DESCRIPTION> eventDescriptionMap = std::make_unique<HashMap<>>();
 int c = 0;
 Vector2 move = new Vector2(0.0F, 0.0F);
 Vector2 pos = new Vector2(-400.0F, -400.0F);
 float x = 0.0F;
 float y = 0.0F;
 float z = 0.0F;
 float vx = 0.02F;
 float vy = 0.01F;
 float vz = 0.0F;
 int numListeners = 1;
 private HashMap<String, Long> fileToSoundMap = std::make_unique<HashMap<>>();
 private int[] reverbPreset = new int[]{-1, -1, -1, -1};

 void init() {
 javafmodJNI.init();
 int int0 = javafmod.FMOD_System_Create();
 if (int0 != 0) {
 Core.SoundDisabled = true;
 } else {
 int int1 = Core.bDebug ? FMOD_STUDIO_INIT_LIVEUPDATE : 0;
 int int2 = Core.bDebug ? FMOD_INIT_PROFILE_ENABLE | FMOD_INIT_PROFILE_METER_ALL : 0;
 int0 = javafmod.FMOD_System_Init(
 1024,
 FMOD_STUDIO_INIT_NORMAL | int1,
 FMOD_INIT_NORMAL | FMOD_INIT_CHANNEL_DISTANCEFILTER | FMOD_INIT_CHANNEL_LOWPASS | FMOD_INIT_VOL0_BECOMES_VIRTUAL | int2
 );
 if (int0 != 0) {
 Core.SoundDisabled = true;
 } else {
 javafmod.FMOD_System_Set3DSettings(1.0F, 1.0F, 1.0F);
 this->loadBank("ZomboidSound.strings");
 this->loadBank("ZomboidMusic");
 this->loadBank("ZomboidSound");
 this->loadBank("ZomboidSoundMP");
 this->channelGroupInGameNonBankSounds = javafmod.FMOD_System_CreateChannelGroup("InGameNonBank");
 this->initGlobalParameters();
 this->initEvents();
 }
 }
 }

 std::string bankPath(const std::string& string) {
 return new File("./media/sound/banks/Desktop/" + string + ".bank").getCanonicalFile().getPath();
 }

 long loadBank(const std::string& string1) {
 try {
 std::string string0 = this->bankPath(string1);
 long long0 = javafmod.FMOD_Studio_System_LoadBankFile(string0);
 if (long0 > 0L) {
 javafmod.FMOD_Studio_LoadSampleData(long0);
 }

 return long0;
 } catch (Exception exception) {
 ExceptionLogger.logException(exception);
 return 0L;
 }
 }

 void loadZombieTest() {
 long long0 = javafmod.FMOD_Studio_System_LoadBankFile("media/sound/banks/chopper.bank");
 long long1 = javafmod.FMOD_Studio_System_LoadBankFile("media/sound/banks/chopper.strings.bank");
 javafmod.FMOD_Studio_LoadSampleData(long0);
 long long2 = javafmod.FMOD_Studio_System_GetEvent("{5deff1b6-984c-42e0-98ec-c133a83d0513}");
 long long3 = javafmod.FMOD_Studio_System_GetEvent("{c00fed39-230a-4c6a-b9c0-b0924876f53a}");
 javafmod.FMOD_Studio_LoadEventSampleData(long2);
 javafmod.FMOD_Studio_LoadEventSampleData(long3);
 short short0 = 2000;
 short short1 = 2000;
 SoundListener soundListener = new SoundListener(0);
 soundListener.x = short0;
 soundListener.y = short1;
 soundListener.tick();
 bool boolean0 = false;
 std::vector arrayList0 = new ArrayList();
 std::vector arrayList1 = new ArrayList();
 FMODManager.TestZombieInfo testZombieInfo0 = new FMODManager.TestZombieInfo(long2, short0 - 5, short1 - 5);
 javafmod.FMOD_Studio_EventInstance_SetParameterByName(testZombieInfo0.inst, "Pitch", Rand.Next(200) / 100.0F - 1.0F);
 javafmod.FMOD_Studio_EventInstance_SetParameterByName(testZombieInfo0.inst, "Aggitation", 0.0F);
 arrayList0.add(testZombieInfo0);
 this->c++;

 while (!boolean0) {
 for (int int0 = 0; int0 < arrayList0.size(); int0++) {
 FMODManager.TestZombieInfo testZombieInfo1 = (FMODManager.TestZombieInfo)arrayList0.get(int0);
 if (Rand.Next(1000) == 0) {
 this->c--;
 arrayList1.add(testZombieInfo1);
 arrayList0.remove(testZombieInfo1);
 float float0 = (Rand.Next(40) + 60) / 100.0F;
 javafmod.FMOD_Studio_EventInstance_SetParameterByName(testZombieInfo1.inst, "Aggitation", float0);
 int0--;
 }
 }

 for (int int1 = 0; int1 < arrayList1.size(); int1++) {
 FMODManager.TestZombieInfo testZombieInfo2 = (FMODManager.TestZombieInfo)arrayList1.get(int1);
 Vector2 vector = new Vector2(short0 - testZombieInfo2.X, short1 - testZombieInfo2.Y);
 if (vector.getLength() < 2.0F) {
 arrayList1.remove(testZombieInfo2);
 javafmod.FMOD_Studio_EventInstance_Stop(testZombieInfo2.inst, false);
 }

 vector.setLength(0.01F);
 testZombieInfo2.X = testZombieInfo2.X + vector.x;
 testZombieInfo2.Y = testZombieInfo2.Y + vector.y;
 javafmod.FMOD_Studio_EventInstance3D(testZombieInfo2.inst, testZombieInfo2.X, testZombieInfo2.Y, 0.0F);
 }

 javafmod.FMOD_System_Update();

 try {
 Thread.sleep(10L);
 } catch (InterruptedException interruptedException) {
 interruptedException.printStackTrace();
 }
 }
 }

 void loadTestEvent() {
 long long0 = javafmod.FMOD_Studio_System_LoadBankFile("media/sound/banks/chopper.bank");
 javafmod.FMOD_Studio_LoadSampleData(long0);
 long long1 = javafmod.FMOD_Studio_System_GetEvent("{47d0c496-7d0a-48e9-9bad-1c8fcf292986}");
 javafmod.FMOD_Studio_LoadEventSampleData(long1);
 long long2 = javafmod.FMOD_Studio_System_CreateEventInstance(long1);
 javafmod.FMOD_Studio_EventInstance3D(long2, this->pos.x, this->pos.y, 100.0F);
 javafmod.FMOD_Studio_Listener3D(0, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, -1.0F, 0.0F, 0.0F, 0.0F, 1.0F);
 javafmod.FMOD_Studio_StartEvent(long2);
 int int0 = 0;
 bool boolean0 = false;

 while (!boolean0) {
 if (int0 > 200) {
 this->pos.x = Rand.Next(400) - 200;
 this->pos.y = Rand.Next(400) - 200;
 if (Rand.Next(3) == 0) {
 this->pos.x /= 4.0F;
 this->pos.y /= 4.0F;
 }

 javafmod.FMOD_Studio_StartEvent(long2);
 javafmod.FMOD_Studio_EventInstance3D(long2, this->pos.x, this->pos.y, 0.0F);
 int0 = 0;
 }

 int0++;
 javafmod.FMOD_System_Update();

 try {
 Thread.sleep(10L);
 } catch (InterruptedException interruptedException) {
 interruptedException.printStackTrace();
 }
 }
 }

 void loadTest() {
 long long0 = javafmod.FMOD_System_CreateSound("media/sound/PZ_FemaleBeingEaten_Death.wav", FMOD_3D);
 javafmod.FMOD_Sound_Set3DMinMaxDistance(long0, 0.005F, 100.0F);
 this->Sounds.add(long0);
 this->playTest();
 }

 void playTest() {
 long long0 = this->Sounds.get(0);
 long long1 = javafmod.FMOD_System_PlaySound(long0, true);
 javafmod.FMOD_Channel_Set3DAttributes(long1, 10.0F, 10.0F, 0.0F, 0.0F, 0.0F, 0.0F);
 javafmod.FMOD_Channel_SetPaused(long1, false);
 this->Instances.add(long1);
 }

 void applyDSP() {
 javafmod.FMOD_System_PlayDSP();
 }

 void tick() {
 if (Rand.Next(100) == 0) {
 this->vx = -this->vx;
 }

 if (Rand.Next(100) == 0) {
 this->vy = -this->vy;
 }

 float float0 = this->x;
 float float1 = this->y;
 float float2 = this->z;
 this->x = this->x + this->vx;
 this->y = this->y + this->vy;
 this->z = this->z + this->vz;

 for (int int0 = 0; int0 < this->Instances.size(); int0++) {
 long long0 = this->Instances.get(int0);
 javafmod.FMOD_Channel_Set3DAttributes(long0, this->x, this->y, this->z, this->x - float0, this->y - float1, this->z - float2);
 float float3 = 40.0F;
 float float4 = (Math.abs(this->x) + Math.abs(this->y) / float3;
 if (float4 < 0.1F) {
 float4 = 0.1F;
 }

 if (float4 > 1.0F) {
 float4 = 1.0F;
 }

 float4 *= float4;
 float4 *= 40.0F;
 javafmod.FMOD_Channel_SetReverbProperties(long0, 0, float4);
 }

 int int1 = 0;

 for (int int2 = 0; int2 < IsoPlayer.numPlayers; int2++) {
 IsoPlayer player = IsoPlayer.players[int2];
 if (player != nullptr) {
 int1++;
 }
 }

 if (int1 > 0) {
 if (int1 != this->numListeners) {
 javafmod.FMOD_Studio_SetNumListeners(int1);
 }
 } else if (this->numListeners != 1) {
 javafmod.FMOD_Studio_SetNumListeners(1);
 }

 this->numListeners = int1;
 this->updateReverbPreset();
 javafmod.FMOD_System_Update();
 }

 int getNumListeners() {
 return this->numListeners;
 }

 long loadSound(const std::string& string) {
 string = ZomboidFileSystem.instance.getAbsolutePath(string);
 if (string.empty()) {
 return 0L;
 } else {
 long long0 = this->fileToSoundMap.get(string);
 if (long0 != nullptr) {
 return long0;
 } else {
 long0 = javafmod.FMOD_System_CreateSound(string, FMOD_3D);
 if (Core.bDebug && long0 == 0L) {
 DebugLog.log("ERROR: failed to load sound " + string);
 }

 this->fileToSoundMap.put(string, long0);
 return long0;
 }
 }
 }

 void stopSound(long long0) {
 if (long0 != 0L) {
 javafmod.FMOD_Channel_Stop(long0);
 }
 }

 bool isPlaying(long long0) {
 return javafmod.FMOD_Channel_IsPlaying(long0);
 }

 long loadSound(const std::string& string, bool boolean0) {
 string = ZomboidFileSystem.instance.getAbsolutePath(string);
 if (string.empty()) {
 return 0L;
 } else {
 long long0 = this->fileToSoundMap.get(string);
 if (long0 != nullptr) {
 return long0;
 } else {
 if (!boolean0) {
 long0 = javafmod.FMOD_System_CreateSound(string, FMOD_3D);
 } else {
 long0 = javafmod.FMOD_System_CreateSound(string, FMOD_3D | FMOD_LOOP_NORMAL);
 }

 this->fileToSoundMap.put(string, long0);
 return long0;
 }
 }
 }

 void updateReverbPreset() {
 int int0 = -1;
 int int1 = -1;
 int int2 = -1;
 int1 = FMOD_PRESET_FOREST;
 int2 = FMOD_PRESET_CITY;
 int0 = FMOD_PRESET_OFF;
 int1 = FMOD_PRESET_OFF;
 int2 = FMOD_PRESET_OFF;
 if (this->reverbPreset[0] != int0) {
 javafmod.FMOD_System_SetReverbDefault(0, int0);
 this->reverbPreset[0] = int0;
 }

 if (this->reverbPreset[1] != int1) {
 javafmod.FMOD_System_SetReverbDefault(1, int1);
 this->reverbPreset[1] = int1;
 }

 if (this->reverbPreset[2] != int2) {
 javafmod.FMOD_System_SetReverbDefault(2, int2);
 this->reverbPreset[2] = int2;
 }
 }

 void initGlobalParameters() {
 int int0 = javafmodJNI.FMOD_Studio_System_GetParameterDescriptionCount();
 if (int0 > 0) {
 long[] longs = new long[int0];
 int0 = javafmodJNI.FMOD_Studio_System_GetParameterDescriptionList(longs);

 for (int int1 = 0; int1 < int0; int1++) {
 long long0 = longs[int1];
 this->initParameterDescription(long0);
 javafmodJNI.FMOD_Studio_ParameterDescription_Free(long0);
 }
 }
 }

 FMOD_STUDIO_PARAMETER_DESCRIPTION initParameterDescription(long long0) {
 std::string string = javafmodJNI.FMOD_Studio_ParameterDescription_GetName(long0);
 FMOD_STUDIO_PARAMETER_DESCRIPTION fmod_studio_parameter_description = this->parameterDescriptionMap.get(string);
 if (fmod_studio_parameter_description.empty()) {
 int int0 = javafmodJNI.FMOD_Studio_ParameterDescription_GetFlags(long0);
 long long1 = javafmodJNI.FMOD_Studio_ParameterDescription_GetID(long0);
 FMOD_STUDIO_PARAMETER_ID fmod_studio_parameter_id = new FMOD_STUDIO_PARAMETER_ID(long1);
 fmod_studio_parameter_description = new FMOD_STUDIO_PARAMETER_DESCRIPTION(
 string, fmod_studio_parameter_id, int0, this->parameterDescriptionMap.size()
 );
 this->parameterDescriptionMap.put(fmod_studio_parameter_description.name, fmod_studio_parameter_description);
 if ((fmod_studio_parameter_description.flags & FMOD_STUDIO_PARAMETER_FLAGS.FMOD_STUDIO_PARAMETER_GLOBAL.bit) != 0) {
 bool boolean0 = true;
 } else {
 bool boolean1 = true;
 }
 }

 return fmod_studio_parameter_description;
 }

 void initEvents() {
 int int0 = javafmodJNI.FMOD_Studio_System_GetBankCount();
 if (int0 > 0) {
 long[] longs0 = new long[int0];
 int0 = javafmodJNI.FMOD_Studio_System_GetBankList(longs0);

 for (int int1 = 0; int1 < int0; int1++) {
 int int2 = javafmodJNI.FMOD_Studio_Bank_GetEventCount(longs0[int1]);
 if (int2 > 0) {
 long[] longs1 = new long[int2];
 int2 = javafmodJNI.FMOD_Studio_Bank_GetEventList(longs0[int1], longs1);

 for (int int3 = 0; int3 < int2; int3++) {
 this->initEvent(longs1[int3]);
 }
 }
 }
 }
 }

 void initEvent(long long0) {
 std::string string = javafmodJNI.FMOD_Studio_EventDescription_GetPath(long0);
 long long1 = javafmodJNI.FMOD_Studio_EventDescription_GetID(long0);
 FMOD_GUID fmod_guid = new FMOD_GUID(long1);
 bool boolean0 = javafmodJNI.FMOD_Studio_EventDescription_HasSustainPoint(long0);
 long long2 = javafmodJNI.FMOD_Studio_EventDescription_GetLength(long0);
 FMOD_STUDIO_EVENT_DESCRIPTION fmod_studio_event_description = new FMOD_STUDIO_EVENT_DESCRIPTION(long0, string, fmod_guid, boolean0, long2);
 this->eventDescriptionMap.put(fmod_studio_event_description.path.toLowerCase(Locale.ENGLISH), fmod_studio_event_description);
 int int0 = javafmodJNI.FMOD_Studio_EventDescription_GetParameterDescriptionCount(long0);

 for (int int1 = 0; int1 < int0; int1++) {
 long long3 = javafmodJNI.FMOD_Studio_EventDescription_GetParameterDescriptionByIndex(long0, int1);
 FMOD_STUDIO_PARAMETER_DESCRIPTION fmod_studio_parameter_description = this->initParameterDescription(long3);
 fmod_studio_event_description.parameters.add(fmod_studio_parameter_description);
 javafmodJNI.FMOD_Studio_ParameterDescription_Free(long3);
 }
 }

 FMOD_STUDIO_EVENT_DESCRIPTION getEventDescription(const std::string& string) {
 return this->eventDescriptionMap.get(string.toLowerCase(Locale.ENGLISH);
 }

 FMOD_STUDIO_PARAMETER_DESCRIPTION getParameterDescription(const std::string& string) {
 return this->parameterDescriptionMap.get(string);
 }

 FMOD_STUDIO_PARAMETER_ID getParameterID(const std::string& string) {
 FMOD_STUDIO_PARAMETER_DESCRIPTION fmod_studio_parameter_description = this->getParameterDescription(string);
 return fmod_studio_parameter_description = = nullptr ? nullptr : fmod_studio_parameter_description.id;
 }

 int getParameterCount() {
 return this->parameterDescriptionMap.size();
 }

 public static class TestZombieInfo {
 float X;
 float Y;
 long event;
 long inst;

 public TestZombieInfo(long long0, float float0, float float1) {
 this->createZombieInstance(long0, float0, float1);
 }

 long createZombieInstance(long long1, float float0, float float1) {
 long long0 = javafmod.FMOD_Studio_System_CreateEventInstance(long1);
 javafmod.FMOD_Studio_EventInstance3D(long0, float0, float1, 0.0F);
 javafmod.FMOD_Studio_StartEvent(long0);
 this->X = float0;
 this->Y = float1;
 this->event = long1;
 this->inst = long0;
 return long0;
 }
 }
}
} // namespace fmod
} // namespace fmod
