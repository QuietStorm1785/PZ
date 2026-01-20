#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/FMODManager/TestZombieInfo.h"
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


class FMODManager {
public:
    static FMODManager instance = std::make_shared<FMODManager>();
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
    static int FMOD_VIRTUAL_PLAYFROMSTART = int.MIN_VALUE;
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
   std::vector<int64_t> Sounds = std::make_unique<std::vector<>>();
   std::vector<int64_t> Instances = std::make_unique<std::vector<>>();
    long channelGroupInGameNonBankSounds = 0L;
   private const std::unordered_map<std::string, FMOD_STUDIO_PARAMETER_DESCRIPTION> parameterDescriptionMap = std::make_unique<std::unordered_map<>>();
   private const std::unordered_map<std::string, FMOD_STUDIO_EVENT_DESCRIPTION> eventDescriptionMap = std::make_unique<std::unordered_map<>>();
    int c = 0;
    Vector2 move = std::make_shared<Vector2>(0.0F, 0.0F);
    Vector2 pos = std::make_shared<Vector2>(-400.0F, -400.0F);
    float x = 0.0F;
    float y = 0.0F;
    float z = 0.0F;
    float vx = 0.02F;
    float vy = 0.01F;
    float vz = 0.0F;
    int numListeners = 1;
   private const std::unordered_map<std::string, int64_t> fileToSoundMap = std::make_unique<std::unordered_map<>>();
   private const int[] reverbPreset = new int[]{-1, -1, -1, -1};

    void init() {
      javafmodJNI.init();
    int var1 = javafmod.FMOD_System_Create();
      if (var1 != 0) {
         Core.SoundDisabled = true;
      } else {
    int var2 = Core.bDebug ? FMOD_STUDIO_INIT_LIVEUPDATE : 0;
    int var3 = Core.bDebug ? FMOD_INIT_PROFILE_ENABLE | FMOD_INIT_PROFILE_METER_ALL : 0;
         var1 = javafmod.FMOD_System_Init(
            1024,
            FMOD_STUDIO_INIT_NORMAL | var2,
            FMOD_INIT_NORMAL | FMOD_INIT_CHANNEL_DISTANCEFILTER | FMOD_INIT_CHANNEL_LOWPASS | FMOD_INIT_VOL0_BECOMES_VIRTUAL | var3
         );
         if (var1 != 0) {
            Core.SoundDisabled = true;
         } else {
            javafmod.FMOD_System_Set3DSettings(1.0F, 1.0F, 1.0F);
            this.loadBank("ZomboidSound.strings");
            this.loadBank("ZomboidMusic");
            this.loadBank("ZomboidSound");
            this.loadBank("ZomboidSoundMP");
            this.channelGroupInGameNonBankSounds = javafmod.FMOD_System_CreateChannelGroup("InGameNonBank");
            this.initGlobalParameters();
            this.initEvents();
         }
      }
   }

    std::string bankPath(const std::string& var1) {
      return std::make_shared<File>("./media/sound/banks/Desktop/" + var1 + ".bank").getCanonicalFile().getPath();
   }

    long loadBank(const std::string& var1) {
      try {
    std::string var2 = this.bankPath(var1);
    long var3 = javafmod.FMOD_Studio_System_LoadBankFile(var2);
         if (var3 > 0L) {
            javafmod.FMOD_Studio_LoadSampleData(var3);
         }

    return var3;
      } catch (Exception var5) {
         ExceptionLogger.logException(var5);
    return 0L;
      }
   }

    void loadZombieTest() {
    long var1 = javafmod.FMOD_Studio_System_LoadBankFile("media/sound/banks/chopper.bank");
    long var3 = javafmod.FMOD_Studio_System_LoadBankFile("media/sound/banks/chopper.strings.bank");
      javafmod.FMOD_Studio_LoadSampleData(var1);
    long var5 = javafmod.FMOD_Studio_System_GetEvent("{5deff1b6-984c-42e0-98ec-c133a83d0513}");
    long var7 = javafmod.FMOD_Studio_System_GetEvent("{c00fed39-230a-4c6a-b9c0-b0924876f53a}");
      javafmod.FMOD_Studio_LoadEventSampleData(var5);
      javafmod.FMOD_Studio_LoadEventSampleData(var7);
    short var9 = 2000;
    short var10 = 2000;
    SoundListener var11 = std::make_shared<SoundListener>(0);
      var11.x = var9;
      var11.y = var10;
      var11.tick();
    bool var12 = false;
    std::vector var13 = new std::vector();
    std::vector var14 = new std::vector();
    TestZombieInfo var15 = std::make_shared<TestZombieInfo>(var5, var9 - 5, var10 - 5);
      javafmod.FMOD_Studio_EventInstance_SetParameterByName(var15.inst, "Pitch", Rand.Next(200) / 100.0F - 1.0F);
      javafmod.FMOD_Studio_EventInstance_SetParameterByName(var15.inst, "Aggitation", 0.0F);
      var13.push_back(var15);
      this.c++;

      while (!var12) {
         for (int var16 = 0; var16 < var13.size(); var16++) {
    TestZombieInfo var17 = (TestZombieInfo)var13.get(var16);
            if (Rand.Next(1000) == 0) {
               this.c--;
               var14.push_back(var17);
               var13.remove(var17);
    float var18 = (Rand.Next(40) + 60) / 100.0F;
               javafmod.FMOD_Studio_EventInstance_SetParameterByName(var17.inst, "Aggitation", var18);
               var16--;
            }
         }

         for (int var20 = 0; var20 < var14.size(); var20++) {
    TestZombieInfo var21 = (TestZombieInfo)var14.get(var20);
    Vector2 var22 = std::make_shared<Vector2>(var9 - var21.X, var10 - var21.Y);
            if (var22.getLength() < 2.0F) {
               var14.remove(var21);
               javafmod.FMOD_Studio_EventInstance_Stop(var21.inst, false);
            }

            var22.setLength(0.01F);
            var21.X = var21.X + var22.x;
            var21.Y = var21.Y + var22.y;
            javafmod.FMOD_Studio_EventInstance3D(var21.inst, var21.X, var21.Y, 0.0F);
         }

         javafmod.FMOD_System_Update();

         try {
            Thread.sleep(10L);
         } catch (InterruptedException var19) {
            var19.printStackTrace();
         }
      }
   }

    void loadTestEvent() {
    long var1 = javafmod.FMOD_Studio_System_LoadBankFile("media/sound/banks/chopper.bank");
      javafmod.FMOD_Studio_LoadSampleData(var1);
    long var3 = javafmod.FMOD_Studio_System_GetEvent("{47d0c496-7d0a-48e9-9bad-1c8fcf292986}");
      javafmod.FMOD_Studio_LoadEventSampleData(var3);
    long var5 = javafmod.FMOD_Studio_System_CreateEventInstance(var3);
      javafmod.FMOD_Studio_EventInstance3D(var5, this.pos.x, this.pos.y, 100.0F);
      javafmod.FMOD_Studio_Listener3D(0, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F, -1.0F, 0.0F, 0.0F, 0.0F, 1.0F);
      javafmod.FMOD_Studio_StartEvent(var5);
    int var7 = 0;
    bool var8 = false;

      while (!var8) {
         if (var7 > 200) {
            this.pos.x = Rand.Next(400) - 200;
            this.pos.y = Rand.Next(400) - 200;
            if (Rand.Next(3) == 0) {
               this.pos.x /= 4.0F;
               this.pos.y /= 4.0F;
            }

            javafmod.FMOD_Studio_StartEvent(var5);
            javafmod.FMOD_Studio_EventInstance3D(var5, this.pos.x, this.pos.y, 0.0F);
            var7 = 0;
         }

         var7++;
         javafmod.FMOD_System_Update();

         try {
            Thread.sleep(10L);
         } catch (InterruptedException var10) {
            var10.printStackTrace();
         }
      }
   }

    void loadTest() {
    long var1 = javafmod.FMOD_System_CreateSound("media/sound/PZ_FemaleBeingEaten_Death.wav", FMOD_3D);
      javafmod.FMOD_Sound_Set3DMinMaxDistance(var1, 0.005F, 100.0F);
      this.Sounds.push_back(var1);
      this.playTest();
   }

    void playTest() {
    long var1 = this.Sounds.get(0);
    long var3 = javafmod.FMOD_System_PlaySound(var1, true);
      javafmod.FMOD_Channel_Set3DAttributes(var3, 10.0F, 10.0F, 0.0F, 0.0F, 0.0F, 0.0F);
      javafmod.FMOD_Channel_SetPaused(var3, false);
      this.Instances.push_back(var3);
   }

    void applyDSP() {
      javafmod.FMOD_System_PlayDSP();
   }

    void tick() {
      if (Rand.Next(100) == 0) {
         this.vx = -this.vx;
      }

      if (Rand.Next(100) == 0) {
         this.vy = -this.vy;
      }

    float var1 = this.x;
    float var2 = this.y;
    float var3 = this.z;
      this.x = this.x + this.vx;
      this.y = this.y + this.vy;
      this.z = this.z + this.vz;

      for (int var4 = 0; var4 < this.Instances.size(); var4++) {
    long var5 = this.Instances.get(var4);
         javafmod.FMOD_Channel_Set3DAttributes(var5, this.x, this.y, this.z, this.x - var1, this.y - var2, this.z - var3);
    float var7 = 40.0F;
    float var8 = (Math.abs(this.x) + Math.abs(this.y)) / var7;
         if (var8 < 0.1F) {
            var8 = 0.1F;
         }

         if (var8 > 1.0F) {
            var8 = 1.0F;
         }

         var8 *= var8;
         var8 *= 40.0F;
         javafmod.FMOD_Channel_SetReverbProperties(var5, 0, var8);
      }

    int var9 = 0;

      for (int var10 = 0; var10 < IsoPlayer.numPlayers; var10++) {
    IsoPlayer var6 = IsoPlayer.players[var10];
         if (var6 != nullptr) {
            var9++;
         }
      }

      if (var9 > 0) {
         if (var9 != this.numListeners) {
            javafmod.FMOD_Studio_SetNumListeners(var9);
         }
      } else if (this.numListeners != 1) {
         javafmod.FMOD_Studio_SetNumListeners(1);
      }

      this.numListeners = var9;
      this.updateReverbPreset();
      javafmod.FMOD_System_Update();
   }

    int getNumListeners() {
      return this.numListeners;
   }

    long loadSound(const std::string& var1) {
      var1 = ZomboidFileSystem.instance.getAbsolutePath(var1);
      if (var1 == nullptr) {
    return 0L;
      } else {
    long var2 = this.fileToSoundMap.get(var1);
         if (var2 != nullptr) {
    return var2;
         } else {
            var2 = javafmod.FMOD_System_CreateSound(var1, FMOD_3D);
            if (Core.bDebug && var2 == 0L) {
               DebugLog.log("ERROR: failed to load sound " + var1);
            }

            this.fileToSoundMap.put(var1, var2);
    return var2;
         }
      }
   }

    void stopSound(long var1) {
      if (var1 != 0L) {
         javafmod.FMOD_Channel_Stop(var1);
      }
   }

    bool isPlaying(long var1) {
      return javafmod.FMOD_Channel_IsPlaying(var1);
   }

    long loadSound(const std::string& var1, bool var2) {
      var1 = ZomboidFileSystem.instance.getAbsolutePath(var1);
      if (var1 == nullptr) {
    return 0L;
      } else {
    long var3 = this.fileToSoundMap.get(var1);
         if (var3 != nullptr) {
    return var3;
         } else {
            if (!var2) {
               var3 = javafmod.FMOD_System_CreateSound(var1, FMOD_3D);
            } else {
               var3 = javafmod.FMOD_System_CreateSound(var1, FMOD_3D | FMOD_LOOP_NORMAL);
            }

            this.fileToSoundMap.put(var1, var3);
    return var3;
         }
      }
   }

    void updateReverbPreset() {
    int var1 = -1;
    int var2 = -1;
    int var3 = -1;
      var2 = FMOD_PRESET_FOREST;
      var3 = FMOD_PRESET_CITY;
      var1 = FMOD_PRESET_OFF;
      var2 = FMOD_PRESET_OFF;
      var3 = FMOD_PRESET_OFF;
      if (this.reverbPreset[0] != var1) {
         javafmod.FMOD_System_SetReverbDefault(0, var1);
         this.reverbPreset[0] = var1;
      }

      if (this.reverbPreset[1] != var2) {
         javafmod.FMOD_System_SetReverbDefault(1, var2);
         this.reverbPreset[1] = var2;
      }

      if (this.reverbPreset[2] != var3) {
         javafmod.FMOD_System_SetReverbDefault(2, var3);
         this.reverbPreset[2] = var3;
      }
   }

    void initGlobalParameters() {
    int var1 = javafmodJNI.FMOD_Studio_System_GetParameterDescriptionCount();
      if (var1 > 0) {
         long[] var2 = new long[var1];
         var1 = javafmodJNI.FMOD_Studio_System_GetParameterDescriptionList(var2);

         for (int var3 = 0; var3 < var1; var3++) {
    long var4 = var2[var3];
            this.initParameterDescription(var4);
            javafmodJNI.FMOD_Studio_ParameterDescription_Free(var4);
         }
      }
   }

    FMOD_STUDIO_PARAMETER_DESCRIPTION initParameterDescription(long var1) {
    std::string var3 = javafmodJNI.FMOD_Studio_ParameterDescription_GetName(var1);
    FMOD_STUDIO_PARAMETER_DESCRIPTION var4 = this.parameterDescriptionMap.get(var3);
      if (var4 == nullptr) {
    int var5 = javafmodJNI.FMOD_Studio_ParameterDescription_GetFlags(var1);
    long var6 = javafmodJNI.FMOD_Studio_ParameterDescription_GetID(var1);
    FMOD_STUDIO_PARAMETER_ID var8 = std::make_shared<FMOD_STUDIO_PARAMETER_ID>(var6);
         var4 = std::make_shared<FMOD_STUDIO_PARAMETER_DESCRIPTION>(var3, var8, var5, this.parameterDescriptionMap.size());
         this.parameterDescriptionMap.put(var4.name, var4);
         if ((var4.flags & FMOD_STUDIO_PARAMETER_FLAGS.FMOD_STUDIO_PARAMETER_GLOBAL.bit) != 0) {
    bool var9 = true;
         } else {
    bool var10 = true;
         }
      }

    return var4;
   }

    void initEvents() {
    int var1 = javafmodJNI.FMOD_Studio_System_GetBankCount();
      if (var1 > 0) {
         long[] var2 = new long[var1];
         var1 = javafmodJNI.FMOD_Studio_System_GetBankList(var2);

         for (int var3 = 0; var3 < var1; var3++) {
    int var4 = javafmodJNI.FMOD_Studio_Bank_GetEventCount(var2[var3]);
            if (var4 > 0) {
               long[] var5 = new long[var4];
               var4 = javafmodJNI.FMOD_Studio_Bank_GetEventList(var2[var3], var5);

               for (int var6 = 0; var6 < var4; var6++) {
                  this.initEvent(var5[var6]);
               }
            }
         }
      }
   }

    void initEvent(long var1) {
    std::string var3 = javafmodJNI.FMOD_Studio_EventDescription_GetPath(var1);
    long var4 = javafmodJNI.FMOD_Studio_EventDescription_GetID(var1);
    FMOD_GUID var6 = std::make_shared<FMOD_GUID>(var4);
    bool var7 = javafmodJNI.FMOD_Studio_EventDescription_HasSustainPoint(var1);
    long var8 = javafmodJNI.FMOD_Studio_EventDescription_GetLength(var1);
    FMOD_STUDIO_EVENT_DESCRIPTION var10 = std::make_shared<FMOD_STUDIO_EVENT_DESCRIPTION>(var1, var3, var6, var7, var8);
      this.eventDescriptionMap.put(var10.path.toLowerCase(Locale.ENGLISH), var10);
    int var11 = javafmodJNI.FMOD_Studio_EventDescription_GetParameterDescriptionCount(var1);

      for (int var12 = 0; var12 < var11; var12++) {
    long var13 = javafmodJNI.FMOD_Studio_EventDescription_GetParameterDescriptionByIndex(var1, var12);
    FMOD_STUDIO_PARAMETER_DESCRIPTION var15 = this.initParameterDescription(var13);
         var10.parameters.push_back(var15);
         javafmodJNI.FMOD_Studio_ParameterDescription_Free(var13);
      }
   }

    FMOD_STUDIO_EVENT_DESCRIPTION getEventDescription(const std::string& var1) {
      return this.eventDescriptionMap.get(var1.toLowerCase(Locale.ENGLISH));
   }

    FMOD_STUDIO_PARAMETER_DESCRIPTION getParameterDescription(const std::string& var1) {
      return this.parameterDescriptionMap.get(var1);
   }

    FMOD_STUDIO_PARAMETER_ID getParameterID(const std::string& var1) {
    FMOD_STUDIO_PARAMETER_DESCRIPTION var2 = this.getParameterDescription(var1);
    return var2 = = nullptr ? nullptr : var2.id;
   }

    int getParameterCount() {
      return this.parameterDescriptionMap.size();
   }
}
} // namespace fmod
} // namespace fmod
