#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/FMODSoundBuffer.h"
#include "fmod/FMOD_RESULT.h"
#include "fmod/fmod/FMODManager.h"
#include "fmod/javafmod.h"
#include "fmod/javafmodJNI.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/Platform.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/VoiceManager/1.h"
#include "zombie/core/raknet/VoiceManager/2.h"
#include "zombie/core/raknet/VoiceManager/3.h"
#include "zombie/core/raknet/VoiceManager/4.h"
#include "zombie/core/raknet/VoiceManagerData/RadioData.h"
#include "zombie/core/raknet/VoiceManagerData/VoiceDataSource.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/LogSeverity.h"
#include "zombie/input/GameKeyboard.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/types/Radio.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/objects/IsoRadio.h"
#include "zombie/iso/objects/IsoWorldInventoryObject.h"
#include "zombie/network/FakeClientManager.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/MPStatistics.h"
#include "zombie/network/PacketTypes/PacketType.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/radio/devices/DeviceData.h"
#include "zombie/vehicles/VehiclePart.h"
#include <algorithm>
#include <filesystem>

namespace zombie {
namespace core {
namespace raknet {


class VoiceManager {
public:
    static const int FMOD_SOUND_MODE = FMODManager.FMOD_OPENUSER | FMODManager.FMOD_LOOP_NORMAL | FMODManager.FMOD_CREATESTREAM;
    static const int modePPT = 1;
    static const int modeVAD = 2;
    static const int modeMute = 3;
    static const int VADModeQuality = 1;
    static const int VADModeLowBitrate = 2;
    static const int VADModeAggressive = 3;
    static const int VADModeVeryAggressive = 4;
    static const int AGCModeAdaptiveAnalog = 1;
    static const int AGCModeAdaptiveDigital = 2;
    static const int AGCModeFixedDigital = 3;
    static const int bufferSize = 192;
    static const int complexity = 1;
    static bool serverVOIPEnable = true;
    static int sampleRate = 16000;
    static int period = 300;
    static int buffering = 8000;
    static float minDistance;
    static float maxDistance;
    static bool is3D = false;
    bool isEnable = true;
    bool isModeVAD = false;
    bool isModePPT = false;
    int vadMode = 3;
    int agcMode = 2;
    int volumeMic;
    int volumePlayers;
    static bool VoipDisabled = false;
    bool isServer;
    static FMODSoundBuffer FMODReceiveBuffer;
    int FMODVoiceRecordDriverId;
    long FMODChannelGroup = 0L;
    long FMODRecordSound = 0L;
    Semaphore recDevSemaphore;
    bool initialiseRecDev = false;
    bool initialisedRecDev = false;
    long indicatorIsVoice = 0L;
    Thread thread;
    bool bQuit;
    long timeLast;
    bool isDebug = false;
    bool isDebugLoopback = false;
    bool isDebugLoopbackLong = false;
    static VoiceManager instance = std::make_shared<VoiceManager>();
   byte[] buf = new byte[192];
    const void* notifier = std::make_shared<Object>();
    bool bIsClient = false;
    bool bTestingMicrophone = false;
    long testingMicrophoneMS = 0L;
    const long recBuf_Current_read = std::make_shared<int64_t>(0L);
    static long timestamp = 0L;

    static VoiceManager getInstance() {
    return instance;
   }

    void DeinitRecSound() {
      this.initialisedRecDev = false;
      if (this.FMODRecordSound != 0L) {
         javafmod.FMOD_RecordSound_Release(this.FMODRecordSound);
         this.FMODRecordSound = 0L;
      }

      FMODReceiveBuffer = nullptr;
   }

    void ResetRecSound() {
      if (this.initialisedRecDev && this.FMODRecordSound != 0L) {
    int var1 = javafmod.FMOD_System_RecordStop(this.FMODVoiceRecordDriverId);
         if (var1 != FMOD_RESULT.FMOD_OK.ordinal()) {
            DebugLog.Voice.warn("FMOD_System_RecordStop result=%d", new Object[]{var1});
         }
      }

      this.DeinitRecSound();
      this.FMODRecordSound = javafmod.FMOD_System_CreateRecordSound(
         this.FMODVoiceRecordDriverId,
         FMODManager.FMOD_2D | FMODManager.FMOD_OPENUSER | FMODManager.FMOD_SOFTWARE,
         FMODManager.FMOD_SOUND_FORMAT_PCM16,
         sampleRate,
         this.agcMode
      );
      if (this.FMODRecordSound == 0L) {
         DebugLog.Voice.warn("FMOD_System_CreateSound result=%d", new Object[]{this.FMODRecordSound});
      }

      javafmod.FMOD_System_SetRecordVolume(1L - Math.round(Math.pow(1.4, 11 - this.volumeMic)));
      if (this.initialiseRecDev) {
    int var2 = javafmod.FMOD_System_RecordStart(this.FMODVoiceRecordDriverId, this.FMODRecordSound, true);
         if (var2 != FMOD_RESULT.FMOD_OK.ordinal()) {
            DebugLog.Voice.warn("FMOD_System_RecordStart result=%d", new Object[]{var2});
         }
      }

      javafmod.FMOD_System_SetVADMode(this.vadMode - 1);
      FMODReceiveBuffer = std::make_shared<FMODSoundBuffer>(this.FMODRecordSound);
      this.initialisedRecDev = true;
   }

    void VoiceRestartClient(bool var1) {
      if (GameClient.connection != nullptr) {
         if (var1) {
            this.loadConfig();
            this.VoiceConnectReq(GameClient.connection.getConnectedGUID());
         } else {
            this.threadSafeCode(this::DeinitRecSound);
            this.VoiceConnectClose(GameClient.connection.getConnectedGUID());
            this.loadConfig();
         }
      } else {
         this.loadConfig();
         if (var1) {
            this.InitRecDeviceForTest();
         } else {
            this.threadSafeCode(this::DeinitRecSound);
         }
      }
   }

    void VoiceInitClient() {
      this.isServer = false;
      this.recDevSemaphore = std::make_shared<Semaphore>(1);
      FMODReceiveBuffer = nullptr;
      RakVoice.RVInit(192);
      RakVoice.SetComplexity(1);
   }

    void VoiceInitServer(bool var1, int var2, int var3, int var4, int var5, double var6, double var8, bool var10) {
      this.isServer = true;
      if (!(var3 == 2 | var3 == 5 | var3 == 10 | var3 == 20 | var3 == 40 | var3 == 60)) {
         DebugLog.Voice.error("Invalid period=%d", new Object[]{var3});
      } else if (!(var2 == 8000 | var2 == 16000 | var2 == 24000)) {
         DebugLog.Voice.error("Invalid sample rate=%d", new Object[]{var2});
      } else if (var4 < 0 | var4 > 10) {
         DebugLog.Voice.error("Invalid quality=%d", new Object[]{var4});
      } else if (var5 < 0 | var5 > 32000) {
         DebugLog.Voice.error("Invalid buffering=%d", new Object[]{var5});
      } else {
         sampleRate = var2;
         RakVoice.RVInitServer(var1, var2, var3, var4, var5, (float)var6, (float)var8, var10);
      }
   }

    void VoiceConnectAccept(long var1) {
      if (this.isEnable) {
         DebugLog.Voice.debugln("uuid=%x", var1);
      }
   }

    void InitRecDeviceForTest() {
      this.threadSafeCode(this::ResetRecSound);
   }

    void VoiceOpenChannelReply(long var1, ByteBuffer var3) {
      if (this.isEnable) {
         DebugLog.Voice.debugln("uuid=%d", var1);
         if (this.isServer) {
            return;
         }

         try {
            if (GameClient.bClient) {
               serverVOIPEnable = var3.getInt() != 0;
               sampleRate = var3.getInt();
               period = var3.getInt();
               var3.getInt();
               buffering = var3.getInt();
               minDistance = var3.getFloat();
               maxDistance = var3.getFloat();
               is3D = var3.getInt() != 0;
            } else {
               serverVOIPEnable = RakVoice.GetServerVOIPEnable();
               sampleRate = RakVoice.GetSampleRate();
               period = RakVoice.GetSendFramePeriod();
               buffering = RakVoice.GetBuffering();
               minDistance = RakVoice.GetMinDistance();
               maxDistance = RakVoice.GetMaxDistance();
               is3D = RakVoice.GetIs3D();
            }
         } catch (Exception var8) {
            DebugLog.Voice.printException(var8, "RakVoice params set failed", LogSeverity.Error);
            return;
         }

         DebugLog.Voice
            .debugln("enabled=%b, sample-rate=%d, period=%d, complexity=%d, buffering=%d, is3D=%b", serverVOIPEnable, sampleRate, period, 1, buffering, is3D);

         try {
            this.recDevSemaphore.acquire();
         } catch (InterruptedException var7) {
            var7.printStackTrace();
         }

    int var4 = is3D ? FMODManager.FMOD_3D | FMOD_SOUND_MODE : FMOD_SOUND_MODE;

         for (VoiceManagerData var6 : VoiceManagerData.data) {
            if (var6.userplaysound != 0L) {
               javafmod.FMOD_Sound_SetMode(var6.userplaysound, var4);
            }
         }

    long var9 = javafmod.FMOD_System_SetRawPlayBufferingPeriod(buffering);
         if (var9 != FMOD_RESULT.FMOD_OK.ordinal()) {
            DebugLog.Voice.warn("FMOD_System_SetRawPlayBufferingPeriod result=%d", new Object[]{var9});
         }

         this.ResetRecSound();
         this.recDevSemaphore.release();
         if (this.isDebug) {
            VoiceDebug.createAndShowGui();
         }
      }
   }

    void VoiceConnectReq(long var1) {
      if (this.isEnable) {
         DebugLog.Voice.debugln("uuid=%x", var1);
         VoiceManagerData.data.clear();
         RakVoice.RequestVoiceChannel(var1);
      }
   }

    void VoiceConnectClose(long var1) {
      if (this.isEnable) {
         DebugLog.Voice.debugln("uuid=%x", var1);
         RakVoice.CloseVoiceChannel(var1);
      }
   }

    void setMode(int var1) {
      if (var1 == 3) {
         this.isModeVAD = false;
         this.isModePPT = false;
      } else if (var1 == 1) {
         this.isModeVAD = false;
         this.isModePPT = true;
      } else if (var1 == 2) {
         this.isModeVAD = true;
         this.isModePPT = false;
      }
   }

    void setVADMode(int var1) {
      if (!(var1 < 1 | var1 > 4)) {
         this.vadMode = var1;
         if (this.initialisedRecDev) {
            this.threadSafeCode(() -> javafmod.FMOD_System_SetVADMode(this.vadMode - 1));
         }
      }
   }

    void setAGCMode(int var1) {
      if (!(var1 < 1 | var1 > 3)) {
         this.agcMode = var1;
         if (this.initialisedRecDev) {
            this.threadSafeCode(this::ResetRecSound);
         }
      }
   }

    void setVolumePlayers(int var1) {
      if (!(var1 < 0 | var1 > 11)) {
         if (var1 <= 10) {
            this.volumePlayers = var1;
         } else {
            this.volumePlayers = 12;
         }

         if (this.initialisedRecDev) {
    std::vector var2 = VoiceManagerData.data;

            for (int var3 = 0; var3 < var2.size(); var3++) {
    VoiceManagerData var4 = (VoiceManagerData)var2.get(var3);
               if (var4 != nullptr && var4.userplaychannel != 0L) {
                  javafmod.FMOD_Channel_SetVolume(var4.userplaychannel, (float)(this.volumePlayers * 0.2));
               }
            }
         }
      }
   }

    void setVolumeMic(int var1) {
      if (!(var1 < 0 | var1 > 11)) {
         if (var1 <= 10) {
            this.volumeMic = var1;
         } else {
            this.volumeMic = 12;
         }

         if (this.initialisedRecDev) {
            this.threadSafeCode(() -> javafmod.FMOD_System_SetRecordVolume(1L - Math.round(Math.pow(1.4, 11 - this.volumeMic))));
         }
      }
   }

    static void playerSetMute(const std::string& var0) {
    std::vector var1 = GameClient.instance.getPlayers();

      for (int var2 = 0; var2 < var1.size(); var2++) {
    IsoPlayer var3 = (IsoPlayer)var1.get(var2);
         if (var0 == var3.username)) {
    VoiceManagerData var4 = VoiceManagerData.get(var3.OnlineID);
            var4.userplaymute = !var4.userplaymute;
            var3.isVoiceMute = var4.userplaymute;
            break;
         }
      }
   }

    static bool playerGetMute(const std::string& var0) {
    std::vector var2 = GameClient.instance.getPlayers();

      for (int var3 = 0; var3 < var2.size(); var3++) {
    IsoPlayer var4 = (IsoPlayer)var2.get(var3);
         if (var0 == var4.username)) {
            return VoiceManagerData.get(var4.OnlineID).userplaymute;
         }
      }

    return true;
   }

    void LuaRegister(Platform var1, KahluaTable var2) {
    KahluaTable var3 = var1.newTable();
      var3.rawset("playerSetMute", std::make_shared<1>(this));
      var3.rawset("playerGetMute", std::make_shared<2>(this));
      var3.rawset("RecordDevices", std::make_shared<3>(this));
      var2.rawset("VoiceManager", var3);
   }

    void setUserPlaySound(long var1, float var3) {
      var3 = IsoUtils.clamp(var3 * IsoUtils.lerp(this.volumePlayers, 0.0F, 12.0F), 0.0F, 1.0F);
      javafmod.FMOD_Channel_SetVolume(var1, var3);
   }

    long getUserPlaySound(short var1) {
    VoiceManagerData var2 = VoiceManagerData.get(var1);
      if (var2.userplaychannel == 0L) {
         var2.userplaysound = 0L;
    int var3 = is3D ? FMODManager.FMOD_3D | FMOD_SOUND_MODE : FMOD_SOUND_MODE;
         var2.userplaysound = javafmod.FMOD_System_CreateRAWPlaySound(var3, FMODManager.FMOD_SOUND_FORMAT_PCM16, sampleRate);
         if (var2.userplaysound == 0L) {
            DebugLog.Voice.warn("FMOD_System_CreateSound result=%d", new Object[]{var2.userplaysound});
         }

         var2.userplaychannel = javafmod.FMOD_System_PlaySound(var2.userplaysound, false);
         if (var2.userplaychannel == 0L) {
            DebugLog.Voice.warn("FMOD_System_PlaySound result=%d", new Object[]{var2.userplaychannel});
         }

         javafmod.FMOD_Channel_SetVolume(var2.userplaychannel, (float)(this.volumePlayers * 0.2));
         if (is3D) {
            javafmod.FMOD_Channel_Set3DMinMaxDistance(var2.userplaychannel, minDistance / 2.0F, maxDistance);
         }

         javafmod.FMOD_Channel_SetChannelGroup(var2.userplaychannel, this.FMODChannelGroup);
      }

      return var2.userplaysound;
   }

    void InitVMClient() {
      if (!Core.SoundDisabled && !VoipDisabled) {
    int var1 = javafmod.FMOD_System_GetRecordNumDrivers();
         this.FMODVoiceRecordDriverId = Core.getInstance().getOptionVoiceRecordDevice() - 1;
         if (this.FMODVoiceRecordDriverId < 0 && var1 > 0) {
            Core.getInstance().setOptionVoiceRecordDevice(1);
            this.FMODVoiceRecordDriverId = Core.getInstance().getOptionVoiceRecordDevice() - 1;
         }

         if (var1 < 1) {
            DebugLog.Voice.debugln("Microphone not found");
            this.initialiseRecDev = false;
         } else if (this.FMODVoiceRecordDriverId < 0 | this.FMODVoiceRecordDriverId >= var1) {
            DebugLog.Voice.warn("Invalid record device");
            this.initialiseRecDev = false;
         } else {
            this.initialiseRecDev = true;
         }

         this.isEnable = Core.getInstance().getOptionVoiceEnable();
         this.setMode(Core.getInstance().getOptionVoiceMode());
         this.vadMode = Core.getInstance().getOptionVoiceVADMode();
         this.volumeMic = Core.getInstance().getOptionVoiceVolumeMic();
         this.volumePlayers = Core.getInstance().getOptionVoiceVolumePlayers();
         this.FMODChannelGroup = javafmod.FMOD_System_CreateChannelGroup("VOIP");
         this.VoiceInitClient();
         this.FMODRecordSound = 0L;
         if (this.isEnable) {
            this.InitRecDeviceForTest();
         }

         if (this.isDebug) {
            VoiceDebug.createAndShowGui();
         }

         this.timeLast = System.currentTimeMillis();
         this.bQuit = false;
         this.thread = std::make_shared<4>(this);
         this.thread.setName("VoiceManagerClient");
         this.thread.start();
      } else {
         this.isEnable = false;
         this.initialiseRecDev = false;
         this.initialisedRecDev = false;
         DebugLog.Voice.debugln("Disabled");
      }
   }

    void loadConfig() {
      this.isEnable = Core.getInstance().getOptionVoiceEnable();
      this.setMode(Core.getInstance().getOptionVoiceMode());
      this.vadMode = Core.getInstance().getOptionVoiceVADMode();
      this.volumeMic = Core.getInstance().getOptionVoiceVolumeMic();
      this.volumePlayers = Core.getInstance().getOptionVoiceVolumePlayers();
   }

    void UpdateRecordDevice() {
      if (this.initialisedRecDev) {
         this.threadSafeCode(this::UpdateRecordDeviceInternal);
      }
   }

    void UpdateRecordDeviceInternal() {
    int var1 = javafmod.FMOD_System_RecordStop(this.FMODVoiceRecordDriverId);
      if (var1 != FMOD_RESULT.FMOD_OK.ordinal()) {
         DebugLog.Voice.warn("FMOD_System_RecordStop result=%d", new Object[]{var1});
      }

      this.FMODVoiceRecordDriverId = Core.getInstance().getOptionVoiceRecordDevice() - 1;
      if (this.FMODVoiceRecordDriverId < 0) {
         DebugLog.Voice.error("No record device found");
      } else {
         var1 = javafmod.FMOD_System_RecordStart(this.FMODVoiceRecordDriverId, this.FMODRecordSound, true);
         if (var1 != FMOD_RESULT.FMOD_OK.ordinal()) {
            DebugLog.Voice.warn("FMOD_System_RecordStart result=%d", new Object[]{var1});
         }
      }
   }

    void DeinitVMClient() {
      if (this.thread != nullptr) {
         this.bQuit = true;
         /* synchronized - TODO: add std::mutex */ (this.notifier) {
            this.notifier.notify();
         }

         while (this.thread.isAlive()) {
            try {
               Thread.sleep(10L);
            } catch (InterruptedException var4) {
            }
         }

         this.thread = nullptr;
      }

      this.DeinitRecSound();
    std::vector var6 = VoiceManagerData.data;

      for (int var2 = 0; var2 < var6.size(); var2++) {
    VoiceManagerData var3 = (VoiceManagerData)var6.get(var2);
         if (var3.userplaychannel != 0L) {
            javafmod.FMOD_Channel_Stop(var3.userplaychannel);
         }

         if (var3.userplaysound != 0L) {
            javafmod.FMOD_RAWPlaySound_Release(var3.userplaysound);
            var3.userplaysound = 0L;
         }
      }

      VoiceManagerData.data.clear();
   }

    void setTestingMicrophone(bool var1) {
      if (var1) {
         this.testingMicrophoneMS = System.currentTimeMillis();
      }

      if (var1 != this.bTestingMicrophone) {
         this.bTestingMicrophone = var1;
         this.notifyThread();
      }
   }

    void notifyThread() {
      /* synchronized - TODO: add std::mutex */ (this.notifier) {
         this.notifier.notify();
      }
   }

    void update() {
      if (!GameServer.bServer) {
         if (this.bTestingMicrophone) {
    long var1 = System.currentTimeMillis();
            if (var1 - this.testingMicrophoneMS > 1000L) {
               this.setTestingMicrophone(false);
            }
         }

         if ((!GameClient.bClient || GameClient.connection == nullptr) && !FakeClientManager.isVOIPEnabled()) {
            if (this.bIsClient) {
               this.bIsClient = false;
               this.notifyThread();
            }
         } else if (!this.bIsClient) {
            this.bIsClient = true;
            this.notifyThread();
         }
      }
   }

    float getCanHearAllVolume(float var1) {
      return var1 > minDistance ? IsoUtils.clamp(1.0F - IsoUtils.lerp(var1, minDistance, maxDistance), 0.2F, 1.0F) : 1.0F;
   }

    void threadSafeCode(Runnable var1) {
      while (true) {
         try {
            this.recDevSemaphore.acquire();
         } catch (InterruptedException var7) {
            continue;
         }

         try {
            var1.run();
         } finally {
            this.recDevSemaphore.release();
         }

         return;
      }
   }

   /* synchronized - TODO: add std::mutex */ void UpdateVMClient() throws InterruptedException {
      while (!this.bQuit && !this.bIsClient && !this.bTestingMicrophone) {
         /* synchronized - TODO: add std::mutex */ (this.notifier) {
            try {
               this.notifier.wait();
            } catch (InterruptedException var13) {
            }
         }
      }

      if (serverVOIPEnable) {
         if (IsoPlayer.getInstance() != nullptr) {
            IsoPlayer.getInstance().isSpeek = System.currentTimeMillis() - this.indicatorIsVoice <= 300L;
         }

         if (this.initialiseRecDev) {
            this.recDevSemaphore.acquire();
            javafmod.FMOD_System_GetRecordPosition(this.FMODVoiceRecordDriverId, this.recBuf_Current_read);
            if (FMODReceiveBuffer != nullptr) {
               while (FMODReceiveBuffer.pull(this.recBuf_Current_read)) {
                  if (IsoPlayer.getInstance() != nullptr && GameClient.connection != nullptr || FakeClientManager.isVOIPEnabled()) {
                     if (is3D && IsoPlayer.getInstance().isDead()) {
                        continue;
                     }

                     if (this.isModePPT) {
                        if (GameKeyboard.isKeyDown(Core.getInstance().getKey("Enable voice transmit"))) {
                           RakVoice.SendFrame(
                              GameClient.connection.connectedGUID, IsoPlayer.getInstance().OnlineID, FMODReceiveBuffer.buf(), FMODReceiveBuffer.get_size()
                           );
                           this.indicatorIsVoice = System.currentTimeMillis();
                        } else if (FakeClientManager.isVOIPEnabled()) {
                           RakVoice.SendFrame(
                              FakeClientManager.getConnectedGUID(), FakeClientManager.getOnlineID(), FMODReceiveBuffer.buf(), FMODReceiveBuffer.get_size()
                           );
                           this.indicatorIsVoice = System.currentTimeMillis();
                        }
                     }

                     if (this.isModeVAD && FMODReceiveBuffer.get_vad() != 0L) {
                        RakVoice.SendFrame(
                           GameClient.connection.connectedGUID, IsoPlayer.getInstance().OnlineID, FMODReceiveBuffer.buf(), FMODReceiveBuffer.get_size()
                        );
                        this.indicatorIsVoice = System.currentTimeMillis();
                     }
                  }

                  if (this.isDebug) {
                     if (GameClient.IDToPlayerMap.values().size() > 0) {
                        VoiceDebug.updateGui(nullptr, FMODReceiveBuffer);
                     } else if (this.isDebugLoopback) {
                        VoiceDebug.updateGui(nullptr, FMODReceiveBuffer);
                     } else {
                        VoiceDebug.updateGui(nullptr, FMODReceiveBuffer);
                     }
                  }

                  if (this.isDebugLoopback) {
                     javafmod.FMOD_System_RAWPlayData(this.getUserPlaySound((short)0), FMODReceiveBuffer.buf(), FMODReceiveBuffer.get_size());
                  }
               }
            }

            this.recDevSemaphore.release();
         }

    std::vector var15 = GameClient.instance.getPlayers();
    std::vector var2 = VoiceManagerData.data;

         for (int var3 = 0; var3 < var2.size(); var3++) {
    VoiceManagerData var4 = (VoiceManagerData)var2.get(var3);
    bool var5 = false;

            for (int var6 = 0; var6 < var15.size(); var6++) {
    IsoPlayer var7 = (IsoPlayer)var15.get(var6);
               if (var7.OnlineID == var4.index) {
                  var5 = true;
                  break;
               }
            }

            if (this.isDebugLoopback & var4.index == 0) {
               break;
            }

            if (var4.userplaychannel != 0L & !var5) {
               javafmod.FMOD_Channel_Stop(var4.userplaychannel);
               var4.userplaychannel = 0L;
            }
         }

    long var16 = System.currentTimeMillis() - this.timeLast;
         if (var16 >= period) {
            this.timeLast += var16;
            if (IsoPlayer.getInstance() == nullptr) {
               return;
            }

    VoiceDataSource var17 = VoiceDataSource.Unknown;
    int var18 = 0;

    for (auto& var8 : var15)    IsoPlayer var9 = IsoPlayer.getInstance();
               if (var8 != var9 && var8.getOnlineID() != -1) {
    VoiceManagerData var10 = VoiceManagerData.get(var8.getOnlineID());

                  while (RakVoice.ReceiveFrame(var8.getOnlineID(), this.buf)) {
                     var10.voicetimeout = 10L;
                     if (!var10.userplaymute) {
    float var11 = IsoUtils.DistanceTo(var9.getX(), var9.getY(), var8.getX(), var8.getY());
                        if (var9.isCanHearAll()) {
                           javafmodJNI.FMOD_Channel_Set3DLevel(var10.userplaychannel, 0.0F);
                           javafmod.FMOD_Channel_Set3DAttributes(var10.userplaychannel, var9.x, var9.y, var9.z, 0.0F, 0.0F, 0.0F);
                           this.setUserPlaySound(var10.userplaychannel, this.getCanHearAllVolume(var11));
                           var17 = VoiceDataSource.Cheat;
                           var18 = 0;
                        } else {
    RadioData var12 = this.checkForNearbyRadios(var10);
                           if (var12 != nullptr && var12.deviceData != nullptr) {
                              javafmodJNI.FMOD_Channel_Set3DLevel(var10.userplaychannel, 0.0F);
                              javafmod.FMOD_Channel_Set3DAttributes(var10.userplaychannel, var9.x, var9.y, var9.z, 0.0F, 0.0F, 0.0F);
                              this.setUserPlaySound(var10.userplaychannel, var12.deviceData.getDeviceVolume());
                              var12.deviceData.doReceiveMPSignal(var12.lastReceiveDistance);
                              var17 = VoiceDataSource.Radio;
                              var18 = var12.freq;
                           } else {
                              if (var12 == nullptr) {
                                 javafmodJNI.FMOD_Channel_Set3DLevel(var10.userplaychannel, 0.0F);
                                 javafmod.FMOD_Channel_Set3DAttributes(var10.userplaychannel, var9.x, var9.y, var9.z, 0.0F, 0.0F, 0.0F);
                                 javafmod.FMOD_Channel_SetVolume(var10.userplaychannel, 0.0F);
                                 var17 = VoiceDataSource.Unknown;
                              } else {
                                 if (is3D) {
                                    javafmodJNI.FMOD_Channel_Set3DLevel(var10.userplaychannel, IsoUtils.lerp(var11, 0.0F, minDistance));
                                    javafmod.FMOD_Channel_Set3DAttributes(var10.userplaychannel, var8.x, var8.y, var8.z, 0.0F, 0.0F, 0.0F);
                                 } else {
                                    javafmodJNI.FMOD_Channel_Set3DLevel(var10.userplaychannel, 0.0F);
                                    javafmod.FMOD_Channel_Set3DAttributes(var10.userplaychannel, var9.x, var9.y, var9.z, 0.0F, 0.0F, 0.0F);
                                 }

                                 this.setUserPlaySound(var10.userplaychannel, IsoUtils.smoothstep(maxDistance, minDistance, var12.lastReceiveDistance));
                                 var17 = VoiceDataSource.Voice;
                              }

                              var18 = 0;
                              if (var11 > maxDistance) {
                                 logFrame(var9, var8, var11);
                              }
                           }
                        }

                        javafmod.FMOD_System_RAWPlayData(this.getUserPlaySound(var8.getOnlineID()), this.buf, this.buf.length);
                        if (this.isDebugLoopbackLong) {
                           RakVoice.SendFrame(GameClient.connection.connectedGUID, var9.getOnlineID(), this.buf, this.buf.length);
                        }
                     }
                  }

                  if (var10.voicetimeout == 0L) {
                     var8.isSpeek = false;
                  } else {
                     var10.voicetimeout--;
                     var8.isSpeek = true;
                  }
               }
            }

            MPStatistics.setVOIPSource(var17, var18);
         }
      }
   }

    static void logFrame(IsoPlayer var0, IsoPlayer var1, float var2) {
    long var3 = System.currentTimeMillis();
      if (var3 > timestamp) {
         timestamp = var3 + 5000L;
         DebugLog.Multiplayer
            .warn(
               std::string.format(
                  "\"%s\" (%b) received VOIP frame from \"%s\" (%b) at distance=%f",
                  var0.getUsername(),
                  var0.isCanHearAll(),
                  var1.getUsername(),
                  var1.isCanHearAll(),
                  var2
               )
            );
      }
   }

    RadioData checkForNearbyRadios(VoiceManagerData var1) {
    IsoPlayer var2 = IsoPlayer.getInstance();
    VoiceManagerData var3 = VoiceManagerData.get(var2.OnlineID);
      if (var3.isCanHearAll) {
         ((RadioData)var3.radioData.get(0)).lastReceiveDistance = 0.0F;
         return (RadioData)var3.radioData.get(0);
      } else {
         /* synchronized - TODO: add std::mutex */ (var3.radioData) {
            for (int var5 = 1; var5 < var3.radioData.size(); var5++) {
               /* synchronized - TODO: add std::mutex */ (var1.radioData) {
                  for (int var7 = 1; var7 < var1.radioData.size(); var7++) {
                     if (((RadioData)var3.radioData.get(var5)).freq == ((RadioData)var1.radioData.get(var7)).freq) {
    float var8 = ((RadioData)var3.radioData.get(var5)).x - ((RadioData)var1.radioData.get(var7)).x;
    float var9 = ((RadioData)var3.radioData.get(var5)).y - ((RadioData)var1.radioData.get(var7)).y;
                        ((RadioData)var3.radioData.get(var5)).lastReceiveDistance = (float)Math.sqrt(var8 * var8 + var9 * var9);
                        if (((RadioData)var3.radioData.get(var5)).lastReceiveDistance < ((RadioData)var1.radioData.get(var7)).distance) {
                           return (RadioData)var3.radioData.get(var5);
                        }
                     }
                  }
               }
            }
         }

         /* synchronized - TODO: add std::mutex */ (var3.radioData) {
            /* synchronized - TODO: add std::mutex */ (var1.radioData) {
               if (!var1.radioData.empty() && !var3.radioData.empty()) {
    float var20 = ((RadioData)var3.radioData.get(0)).x - ((RadioData)var1.radioData.get(0)).x;
    float var21 = ((RadioData)var3.radioData.get(0)).y - ((RadioData)var1.radioData.get(0)).y;
                  ((RadioData)var3.radioData.get(0)).lastReceiveDistance = (float)Math.sqrt(var20 * var20 + var21 * var21);
                  if (((RadioData)var3.radioData.get(0)).lastReceiveDistance < ((RadioData)var1.radioData.get(0)).distance) {
                     return (RadioData)var3.radioData.get(0);
                  }
               }
            }

    return nullptr;
         }
      }
   }

    void UpdateChannelsRoaming(UdpConnection var1) {
    IsoPlayer var2 = IsoPlayer.getInstance();
      if (var2.OnlineID != -1) {
    VoiceManagerData var3 = VoiceManagerData.get(var2.OnlineID);
    bool var4 = false;
         /* synchronized - TODO: add std::mutex */ (var3.radioData) {
            var3.radioData.clear();

            for (int var6 = 0; var6 < IsoPlayer.numPlayers; var6++) {
    IsoPlayer var7 = IsoPlayer.players[var6];
               if (var7 != nullptr) {
                  var4 |= var7.isCanHearAll();
                  var3.radioData.push_back(std::make_shared<RadioData>(RakVoice.GetMaxDistance(), var7.x, var7.y));

                  for (int var8 = 0; var8 < var7.getInventory().getItems().size(); var8++) {
    InventoryItem var9 = (InventoryItem)var7.getInventory().getItems().get(var8);
                     if (dynamic_cast<Radio*>(var9) != nullptr) {
    DeviceData var10 = ((Radio)var9).getDeviceData();
                        if (var10 != nullptr && var10.getIsTurnedOn()) {
                           var3.radioData.push_back(std::make_shared<RadioData>(var10, var7.x, var7.y));
                        }
                     }
                  }

                  for (int var20 = (int)var7.getX() - 4; var20 < var7.getX() + 5.0F; var20++) {
                     for (int var21 = (int)var7.getY() - 4; var21 < var7.getY() + 5.0F; var21++) {
                        for (int var22 = (int)var7.getZ() - 1; var22 < var7.getZ() + 1.0F; var22++) {
    IsoGridSquare var11 = IsoCell.getInstance().getGridSquare(var20, var21, var22);
                           if (var11 != nullptr) {
                              if (var11.getObjects() != nullptr) {
                                 for (int var12 = 0; var12 < var11.getObjects().size(); var12++) {
    IsoObject var13 = (IsoObject)var11.getObjects().get(var12);
                                    if (dynamic_cast<IsoRadio*>(var13) != nullptr) {
    DeviceData var14 = ((IsoRadio)var13).getDeviceData();
                                       if (var14 != nullptr && var14.getIsTurnedOn()) {
                                          var3.radioData.push_back(std::make_shared<RadioData>(var14, var11.x, var11.y));
                                       }
                                    }
                                 }
                              }

                              if (var11.getWorldObjects() != nullptr) {
                                 for (int var23 = 0; var23 < var11.getWorldObjects().size(); var23++) {
    IsoWorldInventoryObject var25 = (IsoWorldInventoryObject)var11.getWorldObjects().get(var23);
                                    if (var25.getItem() != nullptr && var25.getItem() instanceof Radio) {
    DeviceData var27 = ((Radio)var25.getItem()).getDeviceData();
                                       if (var27 != nullptr && var27.getIsTurnedOn()) {
                                          var3.radioData.push_back(std::make_shared<RadioData>(var27, var11.x, var11.y));
                                       }
                                    }
                                 }
                              }

                              if (var11.getVehicleContainer() != nullptr && var11 == var11.getVehicleContainer().getSquare()) {
    VehiclePart var24 = var11.getVehicleContainer().getPartById("Radio");
                                 if (var24 != nullptr) {
    DeviceData var26 = var24.getDeviceData();
                                    if (var26 != nullptr && var26.getIsTurnedOn()) {
                                       var3.radioData.push_back(std::make_shared<RadioData>(var26, var11.x, var11.y));
                                    }
                                 }
                              }
                           }
                        }
                     }
                  }
               }
            }
         }

    ByteBufferWriter var17 = var1.startPacket();
         PacketType.SyncRadioData.doPacket(var17);
         var17.putByte((byte)(var4 ? 1 : 0));
         var17.putInt(var3.radioData.size() * 4);

         for (RadioData var19 : var3.radioData) {
            var17.putInt(var19.freq);
            var17.putInt((int)var19.distance);
            var17.putInt(var19.x);
            var17.putInt(var19.y);
         }

         PacketType.SyncRadioData.send(var1);
      }
   }

    void InitVMServer() {
      this.VoiceInitServer(
         ServerOptions.instance.VoiceEnable.getValue(),
         24000,
         20,
         5,
         8000,
         ServerOptions.instance.VoiceMinDistance.getValue(),
         ServerOptions.instance.VoiceMaxDistance.getValue(),
         ServerOptions.instance.Voice3D.getValue()
      );
   }

    int getMicVolumeIndicator() {
    return FMODReceiveBuffer = = nullptr ? 0 : (int)FMODReceiveBuffer.get_loudness();
   }

    bool getMicVolumeError() {
    return FMODReceiveBuffer = = nullptr ? true : FMODReceiveBuffer.get_interror();
   }

    bool getServerVOIPEnable() {
    return serverVOIPEnable;
   }

    void VMServerBan(short var1, bool var2) {
      RakVoice.SetVoiceBan(var1, var2);
   }
}
} // namespace raknet
} // namespace core
} // namespace zombie
