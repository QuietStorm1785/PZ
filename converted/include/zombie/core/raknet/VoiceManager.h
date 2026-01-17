#pragma once
#include "fmod/FMODSoundBuffer.h"
#include "fmod/FMOD_DriverInfo.h"
#include "fmod/FMOD_RESULT.h"
#include "fmod/fmod/FMODManager.h"
#include "fmod/javafmod.h"
#include "fmod/javafmodJNI.h"
#include "se/krka/kahlua/vm/JavaFunction.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/LuaCallFrame.h"
#include "se/krka/kahlua/vm/Platform.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/network/ByteBufferWriter.h"
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
#include "zombie/network/PacketTypes.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/radio/devices/DeviceData.h"
#include "zombie/vehicles/VehiclePart.h"
#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace raknet {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class VoiceManager {
public:
  static const int FMOD_SOUND_MODE = FMODManager.FMOD_OPENUSER |
                                     FMODManager.FMOD_LOOP_NORMAL |
                                     FMODManager.FMOD_CREATESTREAM;
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
  static VoiceManager instance = new VoiceManager();
  byte[] buf = new byte[192];
  const void *notifier = new Object();
  bool bIsClient = false;
  bool bTestingMicrophone = false;
  long testingMicrophoneMS = 0L;
  const long recBuf_Current_read = new Long(0L);
  static long timestamp = 0L;

  static VoiceManager getInstance() { return instance; }

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
      int int0 = javafmod.FMOD_System_RecordStop(this.FMODVoiceRecordDriverId);
      if (int0 != FMOD_RESULT.FMOD_OK.ordinal()) {
        DebugLog.Voice.warn("FMOD_System_RecordStop result=%d", int0);
      }
    }

    this.DeinitRecSound();
    this.FMODRecordSound = javafmod.FMOD_System_CreateRecordSound(
        this.FMODVoiceRecordDriverId,
        FMODManager.FMOD_2D | FMODManager.FMOD_OPENUSER |
            FMODManager.FMOD_SOFTWARE,
        FMODManager.FMOD_SOUND_FORMAT_PCM16, sampleRate, this.agcMode);
    if (this.FMODRecordSound == 0L) {
      DebugLog.Voice.warn("FMOD_System_CreateSound result=%d",
                          this.FMODRecordSound);
    }

    javafmod.FMOD_System_SetRecordVolume(
        1L - Math.round(Math.pow(1.4, 11 - this.volumeMic)));
    if (this.initialiseRecDev) {
      int int1 = javafmod.FMOD_System_RecordStart(this.FMODVoiceRecordDriverId,
                                                  this.FMODRecordSound, true);
      if (int1 != FMOD_RESULT.FMOD_OK.ordinal()) {
        DebugLog.Voice.warn("FMOD_System_RecordStart result=%d", int1);
      }
    }

    javafmod.FMOD_System_SetVADMode(this.vadMode - 1);
    FMODReceiveBuffer = new FMODSoundBuffer(this.FMODRecordSound);
    this.initialisedRecDev = true;
  }

  void VoiceRestartClient(bool boolean0) {
    if (GameClient.connection != nullptr) {
      if (boolean0) {
        this.loadConfig();
        this.VoiceConnectReq(GameClient.connection.getConnectedGUID());
      } else {
        this.threadSafeCode(this ::DeinitRecSound);
        this.VoiceConnectClose(GameClient.connection.getConnectedGUID());
        this.loadConfig();
      }
    } else {
      this.loadConfig();
      if (boolean0) {
        this.InitRecDeviceForTest();
      } else {
        this.threadSafeCode(this ::DeinitRecSound);
      }
    }
  }

  void VoiceInitClient() {
    this.isServer = false;
    this.recDevSemaphore = new Semaphore(1);
    FMODReceiveBuffer = nullptr;
    RakVoice.RVInit(192);
    RakVoice.SetComplexity(1);
  }

  void VoiceInitServer(bool boolean0, int int1, int int0, int int2, int int3,
                       double double1, double double0, bool boolean1) {
    this.isServer = true;
    if (!(int0 == 2 | int0 == 5 | int0 == 10 | int0 == 20 | int0 == 40 |
          int0 == 60)) {
      DebugLog.Voice.error("Invalid period=%d", int0);
    } else if (!(int1 == 8000 | int1 == 16000 | int1 == 24000)) {
      DebugLog.Voice.error("Invalid sample rate=%d", int1);
    } else if (int2 < 0 | int2 > 10) {
      DebugLog.Voice.error("Invalid quality=%d", int2);
    } else if (int3 < 0 | int3 > 32000) {
      DebugLog.Voice.error("Invalid buffering=%d", int3);
    } else {
      sampleRate = int1;
      RakVoice.RVInitServer(boolean0, int1, int0, int2, int3, (float)double1,
                            (float)double0, boolean1);
    }
  }

  void VoiceConnectAccept(long long0) {
    if (this.isEnable) {
      DebugLog.Voice.debugln("uuid=%x", long0);
    }
  }

  void InitRecDeviceForTest() { this.threadSafeCode(this ::ResetRecSound); }

  void VoiceOpenChannelReply(long long0, ByteBuffer byteBuffer) {
    if (this.isEnable) {
      DebugLog.Voice.debugln("uuid=%d", long0);
      if (this.isServer) {
        return;
      }

      try {
        if (GameClient.bClient) {
          serverVOIPEnable = byteBuffer.getInt() != 0;
          sampleRate = byteBuffer.getInt();
          period = byteBuffer.getInt();
          byteBuffer.getInt();
          buffering = byteBuffer.getInt();
          minDistance = byteBuffer.getFloat();
          maxDistance = byteBuffer.getFloat();
          is3D = byteBuffer.getInt() != 0;
        } else {
          serverVOIPEnable = RakVoice.GetServerVOIPEnable();
          sampleRate = RakVoice.GetSampleRate();
          period = RakVoice.GetSendFramePeriod();
          buffering = RakVoice.GetBuffering();
          minDistance = RakVoice.GetMinDistance();
          maxDistance = RakVoice.GetMaxDistance();
          is3D = RakVoice.GetIs3D();
        }
      } catch (Exception exception) {
        DebugLog.Voice.printException(exception, "RakVoice params set failed",
                                      LogSeverity.Error);
        return;
      }

      DebugLog.Voice.debugln("enabled=%b, sample-rate=%d, period=%d, "
                             "complexity=%d, buffering=%d, is3D=%b",
                             serverVOIPEnable, sampleRate, period, 1, buffering,
                             is3D);

      try {
        this.recDevSemaphore.acquire();
      } catch (InterruptedException interruptedException) {
        interruptedException.printStackTrace();
      }

      int int0 = is3D ? FMODManager.FMOD_3D | FMOD_SOUND_MODE : FMOD_SOUND_MODE;

      for (VoiceManagerData voiceManagerData : VoiceManagerData.data) {
        if (voiceManagerData.userplaysound != 0L) {
          javafmod.FMOD_Sound_SetMode(voiceManagerData.userplaysound, int0);
        }
      }

      long long1 = javafmod.FMOD_System_SetRawPlayBufferingPeriod(buffering);
      if (long1 != FMOD_RESULT.FMOD_OK.ordinal()) {
        DebugLog.Voice.warn("FMOD_System_SetRawPlayBufferingPeriod result=%d",
                            long1);
      }

      this.ResetRecSound();
      this.recDevSemaphore.release();
      if (this.isDebug) {
        VoiceDebug.createAndShowGui();
      }
    }
  }

  void VoiceConnectReq(long long0) {
    if (this.isEnable) {
      DebugLog.Voice.debugln("uuid=%x", long0);
      VoiceManagerData.data.clear();
      RakVoice.RequestVoiceChannel(long0);
    }
  }

  void VoiceConnectClose(long long0) {
    if (this.isEnable) {
      DebugLog.Voice.debugln("uuid=%x", long0);
      RakVoice.CloseVoiceChannel(long0);
    }
  }

  void setMode(int int0) {
    if (int0 == 3) {
      this.isModeVAD = false;
      this.isModePPT = false;
    } else if (int0 == 1) {
      this.isModeVAD = false;
      this.isModePPT = true;
    } else if (int0 == 2) {
      this.isModeVAD = true;
      this.isModePPT = false;
    }
  }

  void setVADMode(int int0) {
    if (!(int0 < 1 | int0 > 4)) {
      this.vadMode = int0;
      if (this.initialisedRecDev) {
        this.threadSafeCode(
            ()->javafmod.FMOD_System_SetVADMode(this.vadMode - 1));
      }
    }
  }

  void setAGCMode(int int0) {
    if (!(int0 < 1 | int0 > 3)) {
      this.agcMode = int0;
      if (this.initialisedRecDev) {
        this.threadSafeCode(this ::ResetRecSound);
      }
    }
  }

  void setVolumePlayers(int int0) {
    if (!(int0 < 0 | int0 > 11)) {
      if (int0 <= 10) {
        this.volumePlayers = int0;
      } else {
        this.volumePlayers = 12;
      }

      if (this.initialisedRecDev) {
        std::vector arrayList = VoiceManagerData.data;

        for (int int1 = 0; int1 < arrayList.size(); int1++) {
          VoiceManagerData voiceManagerData =
              (VoiceManagerData)arrayList.get(int1);
          if (voiceManagerData != nullptr &&
              voiceManagerData.userplaychannel != 0L) {
            javafmod.FMOD_Channel_SetVolume(voiceManagerData.userplaychannel,
                                            (float)(this.volumePlayers * 0.2));
          }
        }
      }
    }
  }

  void setVolumeMic(int int0) {
    if (!(int0 < 0 | int0 > 11)) {
      if (int0 <= 10) {
        this.volumeMic = int0;
      } else {
        this.volumeMic = 12;
      }

      if (this.initialisedRecDev) {
        this.threadSafeCode(()->javafmod.FMOD_System_SetRecordVolume(
            1L - Math.round(Math.pow(1.4, 11 - this.volumeMic))));
      }
    }
  }

  static void playerSetMute(const std::string &string) {
    std::vector arrayList = GameClient.instance.getPlayers();

    for (int int0 = 0; int0 < arrayList.size(); int0++) {
      IsoPlayer player = (IsoPlayer)arrayList.get(int0);
      if (string == player.username)) {
          VoiceManagerData voiceManagerData =
              VoiceManagerData.get(player.OnlineID);
          voiceManagerData.userplaymute = !voiceManagerData.userplaymute;
          player.isVoiceMute = voiceManagerData.userplaymute;
          break;
        }
    }
  }

  static bool playerGetMute(const std::string &string) {
    std::vector arrayList = GameClient.instance.getPlayers();

    for (int int0 = 0; int0 < arrayList.size(); int0++) {
      IsoPlayer player = (IsoPlayer)arrayList.get(int0);
      if (string == player.username)) {
                return VoiceManagerData.get(player.OnlineID).userplaymute;
            }
    }

    return true;
  }

  void LuaRegister(Platform platform, KahluaTable table1) {
    KahluaTable table0 = platform.newTable();
        table0.rawset("playerSetMute", std::make_unique<JavaFunction>() {
    int call(LuaCallFrame luaCallFrame, int var2) {
    void* object = luaCallFrame.get(1);
                VoiceManager.playerSetMute((String)object);
    return 1;
  }
        });
        table0.rawset("playerGetMute", std::make_unique<JavaFunction>() {
    int call(LuaCallFrame luaCallFrame, int var2) {
    void* object = luaCallFrame.get(1);
                luaCallFrame.push(VoiceManager.playerGetMute((String)object));
    return 1;
        }
        });
        table0.rawset("RecordDevices", std::make_unique<JavaFunction>() {
    int call(LuaCallFrame luaCallFrame, int var2) {
                if (!Core.SoundDisabled && !VoiceManager.VoipDisabled) {
    int int0 = javafmod.FMOD_System_GetRecordNumDrivers();
    KahluaTable table0 = luaCallFrame.getPlatform().newTable();

                    for (int int1 = 0; int1 < int0; int1++) {
  FMOD_DriverInfo fMOD_DriverInfo = new FMOD_DriverInfo();
  javafmod.FMOD_System_GetRecordDriverInfo(int1, fMOD_DriverInfo);
  table0.rawset(int1 + 1, fMOD_DriverInfo.name);
                    }

                    luaCallFrame.push(table0);
    return 1;
        }
        else {
          KahluaTable table1 = luaCallFrame.getPlatform().newTable();
          luaCallFrame.push(table1);
          return 1;
        }
        }
        });
        table1.rawset("VoiceManager", table0);
        }

        void setUserPlaySound(long long0, float float0) {
          float0 = IsoUtils.clamp(
              float0 * IsoUtils.lerp(this.volumePlayers, 0.0F, 12.0F), 0.0F,
              1.0F);
          javafmod.FMOD_Channel_SetVolume(long0, float0);
        }

        long getUserPlaySound(short short0) {
          VoiceManagerData voiceManagerData = VoiceManagerData.get(short0);
          if (voiceManagerData.userplaychannel == 0L) {
            voiceManagerData.userplaysound = 0L;
            int int0 =
                is3D ? FMODManager.FMOD_3D | FMOD_SOUND_MODE : FMOD_SOUND_MODE;
            voiceManagerData.userplaysound =
                javafmod.FMOD_System_CreateRAWPlaySound(
                    int0, FMODManager.FMOD_SOUND_FORMAT_PCM16, sampleRate);
            if (voiceManagerData.userplaysound == 0L) {
              DebugLog.Voice.warn("FMOD_System_CreateSound result=%d",
                                  voiceManagerData.userplaysound);
            }

            voiceManagerData.userplaychannel = javafmod.FMOD_System_PlaySound(
                voiceManagerData.userplaysound, false);
            if (voiceManagerData.userplaychannel == 0L) {
              DebugLog.Voice.warn("FMOD_System_PlaySound result=%d",
                                  voiceManagerData.userplaychannel);
            }

            javafmod.FMOD_Channel_SetVolume(voiceManagerData.userplaychannel,
                                            (float)(this.volumePlayers * 0.2));
            if (is3D) {
              javafmod.FMOD_Channel_Set3DMinMaxDistance(
                  voiceManagerData.userplaychannel, minDistance / 2.0F,
                  maxDistance);
            }

            javafmod.FMOD_Channel_SetChannelGroup(
                voiceManagerData.userplaychannel, this.FMODChannelGroup);
          }

          return voiceManagerData.userplaysound;
        }

        void InitVMClient() {
          if (!Core.SoundDisabled && !VoipDisabled) {
            int int0 = javafmod.FMOD_System_GetRecordNumDrivers();
            this.FMODVoiceRecordDriverId =
                Core.getInstance().getOptionVoiceRecordDevice() - 1;
            if (this.FMODVoiceRecordDriverId < 0 && int0 > 0) {
              Core.getInstance().setOptionVoiceRecordDevice(1);
              this.FMODVoiceRecordDriverId =
                  Core.getInstance().getOptionVoiceRecordDevice() - 1;
            }

            if (int0 < 1) {
              DebugLog.Voice.debugln("Microphone not found");
              this.initialiseRecDev = false;
            } else if (this.FMODVoiceRecordDriverId < 0 |
                       this.FMODVoiceRecordDriverId >= int0) {
              DebugLog.Voice.warn("Invalid record device");
              this.initialiseRecDev = false;
            } else {
              this.initialiseRecDev = true;
            }

            this.isEnable = Core.getInstance().getOptionVoiceEnable();
            this.setMode(Core.getInstance().getOptionVoiceMode());
            this.vadMode = Core.getInstance().getOptionVoiceVADMode();
            this.volumeMic = Core.getInstance().getOptionVoiceVolumeMic();
            this.volumePlayers =
                Core.getInstance().getOptionVoiceVolumePlayers();
            this.FMODChannelGroup =
                javafmod.FMOD_System_CreateChannelGroup("VOIP");
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
            this.thread = std::make_unique<Thread>(){
                void run(){while (!VoiceManager.this.bQuit){
                    try {VoiceManager.this.UpdateVMClient();
            sleep(VoiceManager.period / 2);
          }
          catch (Exception exception) {
            exception.printStackTrace();
          }
        }
        }
        }
        ;
        this.thread.setName("VoiceManagerClient");
        this.thread.start();
        }
        else {
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
            this.threadSafeCode(this ::UpdateRecordDeviceInternal);
          }
        }

        void UpdateRecordDeviceInternal() {
          int int0 =
              javafmod.FMOD_System_RecordStop(this.FMODVoiceRecordDriverId);
          if (int0 != FMOD_RESULT.FMOD_OK.ordinal()) {
            DebugLog.Voice.warn("FMOD_System_RecordStop result=%d", int0);
          }

          this.FMODVoiceRecordDriverId =
              Core.getInstance().getOptionVoiceRecordDevice() - 1;
          if (this.FMODVoiceRecordDriverId < 0) {
            DebugLog.Voice.error("No record device found");
          } else {
            int0 = javafmod.FMOD_System_RecordStart(
                this.FMODVoiceRecordDriverId, this.FMODRecordSound, true);
            if (int0 != FMOD_RESULT.FMOD_OK.ordinal()) {
              DebugLog.Voice.warn("FMOD_System_RecordStart result=%d", int0);
            }
          }
        }

        void DeinitVMClient() {
          if (this.thread != nullptr) {
            this.bQuit = true;
            synchronized(this.notifier) { this.notifier.notify(); }

            while (this.thread.isAlive()) {
              try {
                Thread.sleep(10L);
              } catch (InterruptedException interruptedException) {
              }
            }

            this.thread = nullptr;
          }

          this.DeinitRecSound();
          std::vector arrayList = VoiceManagerData.data;

          for (int int0 = 0; int0 < arrayList.size(); int0++) {
            VoiceManagerData voiceManagerData =
                (VoiceManagerData)arrayList.get(int0);
            if (voiceManagerData.userplaychannel != 0L) {
              javafmod.FMOD_Channel_Stop(voiceManagerData.userplaychannel);
            }

            if (voiceManagerData.userplaysound != 0L) {
              javafmod.FMOD_RAWPlaySound_Release(
                  voiceManagerData.userplaysound);
              voiceManagerData.userplaysound = 0L;
            }
          }

          VoiceManagerData.data.clear();
        }

        void setTestingMicrophone(bool boolean0) {
          if (boolean0) {
            this.testingMicrophoneMS = System.currentTimeMillis();
          }

          if (boolean0 != this.bTestingMicrophone) {
            this.bTestingMicrophone = boolean0;
            this.notifyThread();
          }
        }

        void notifyThread() {
          synchronized(this.notifier) { this.notifier.notify(); }
        }

        void update() {
          if (!GameServer.bServer) {
            if (this.bTestingMicrophone) {
              long long0 = System.currentTimeMillis();
              if (long0 - this.testingMicrophoneMS > 1000L) {
                this.setTestingMicrophone(false);
              }
            }

            if ((!GameClient.bClient || GameClient.connection == nullptr) &&
                !FakeClientManager.isVOIPEnabled()) {
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

        float getCanHearAllVolume(float float0) {
          return float0 > minDistance
                     ? IsoUtils.clamp(1.0F - IsoUtils.lerp(float0, minDistance,
                                                           maxDistance),
                                      0.2F, 1.0F)
                     : 1.0F;
        }

        void threadSafeCode(Runnable runnable) {
          while (true) {
            try {
              this.recDevSemaphore.acquire();
            } catch (InterruptedException interruptedException) {
              continue;
            }

            try {
              runnable.run();
            } finally {
              this.recDevSemaphore.release();
            }

            return;
          }
        }

        synchronized void UpdateVMClient() throws InterruptedException {
          while (!this.bQuit && !this.bIsClient && !this.bTestingMicrophone) {
            synchronized(this.notifier) {
              try {
                this.notifier.wait();
              } catch (InterruptedException interruptedException) {
              }
            }
          }

          if (serverVOIPEnable) {
            if (IsoPlayer.getInstance() != nullptr) {
              IsoPlayer.getInstance().isSpeek =
                  System.currentTimeMillis() - this.indicatorIsVoice <= 300L;
            }

            if (this.initialiseRecDev) {
              this.recDevSemaphore.acquire();
              javafmod.FMOD_System_GetRecordPosition(
                  this.FMODVoiceRecordDriverId, this.recBuf_Current_read);
              if (FMODReceiveBuffer != nullptr) {
                while (FMODReceiveBuffer.pull(this.recBuf_Current_read)) {
                  if (IsoPlayer.getInstance() != nullptr &&
                          GameClient.connection != nullptr ||
                      FakeClientManager.isVOIPEnabled()) {
                    if (is3D && IsoPlayer.getInstance().isDead()) {
                      continue;
                    }

                    if (this.isModePPT) {
                      if (GameKeyboard.isKeyDown(Core.getInstance().getKey(
                              "Enable voice transmit"))) {
                        RakVoice.SendFrame(GameClient.connection.connectedGUID,
                                           IsoPlayer.getInstance().OnlineID,
                                           FMODReceiveBuffer.buf(),
                                           FMODReceiveBuffer.get_size());
                        this.indicatorIsVoice = System.currentTimeMillis();
                      } else if (FakeClientManager.isVOIPEnabled()) {
                        RakVoice.SendFrame(FakeClientManager.getConnectedGUID(),
                                           FakeClientManager.getOnlineID(),
                                           FMODReceiveBuffer.buf(),
                                           FMODReceiveBuffer.get_size());
                        this.indicatorIsVoice = System.currentTimeMillis();
                      }
                    }

                    if (this.isModeVAD && FMODReceiveBuffer.get_vad() != 0L) {
                      RakVoice.SendFrame(GameClient.connection.connectedGUID,
                                         IsoPlayer.getInstance().OnlineID,
                                         FMODReceiveBuffer.buf(),
                                         FMODReceiveBuffer.get_size());
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
                    javafmod.FMOD_System_RAWPlayData(
                        this.getUserPlaySound((short)0),
                        FMODReceiveBuffer.buf(), FMODReceiveBuffer.get_size());
                  }
                }
              }

              this.recDevSemaphore.release();
            }

            std::vector arrayList0 = GameClient.instance.getPlayers();
            std::vector arrayList1 = VoiceManagerData.data;

            for (int int0 = 0; int0 < arrayList1.size(); int0++) {
              VoiceManagerData voiceManagerData0 =
                  (VoiceManagerData)arrayList1.get(int0);
              bool boolean0 = false;

              for (int int1 = 0; int1 < arrayList0.size(); int1++) {
                IsoPlayer player0 = (IsoPlayer)arrayList0.get(int1);
                if (player0.OnlineID == voiceManagerData0.index) {
                  boolean0 = true;
                  break;
                }
              }

              if (this.isDebugLoopback & voiceManagerData0.index == 0) {
                break;
              }

              if (voiceManagerData0.userplaychannel != 0L & !boolean0) {
                javafmod.FMOD_Channel_Stop(voiceManagerData0.userplaychannel);
                voiceManagerData0.userplaychannel = 0L;
              }
            }

            long long0 = System.currentTimeMillis() - this.timeLast;
            if (long0 >= period) {
              this.timeLast += long0;
              if (IsoPlayer.getInstance() == nullptr) {
                return;
              }

              VoiceManagerData.VoiceDataSource voiceDataSource =
                  VoiceManagerData.VoiceDataSource.Unknown;
              int int2 = 0;

              for (auto &player1 : arrayList0)
                IsoPlayer player2 = IsoPlayer.getInstance();
              if (player1 != player2 && player1.getOnlineID() != -1) {
                VoiceManagerData voiceManagerData1 =
                    VoiceManagerData.get(player1.getOnlineID());

                while (RakVoice.ReceiveFrame(player1.getOnlineID(), this.buf)) {
                  voiceManagerData1.voicetimeout = 10L;
                  if (!voiceManagerData1.userplaymute) {
                    float float0 =
                        IsoUtils.DistanceTo(player2.getX(), player2.getY(),
                                            player1.getX(), player1.getY());
                    if (player2.isCanHearAll()) {
                      javafmodJNI.FMOD_Channel_Set3DLevel(
                          voiceManagerData1.userplaychannel, 0.0F);
                      javafmod.FMOD_Channel_Set3DAttributes(
                          voiceManagerData1.userplaychannel, player2.x,
                          player2.y, player2.z, 0.0F, 0.0F, 0.0F);
                      this.setUserPlaySound(voiceManagerData1.userplaychannel,
                                            this.getCanHearAllVolume(float0));
                      voiceDataSource = VoiceManagerData.VoiceDataSource.Cheat;
                      int2 = 0;
                    } else {
                      VoiceManagerData.RadioData radioData =
                          this.checkForNearbyRadios(voiceManagerData1);
                      if (radioData != nullptr &&
                          radioData.deviceData != nullptr) {
                        javafmodJNI.FMOD_Channel_Set3DLevel(
                            voiceManagerData1.userplaychannel, 0.0F);
                        javafmod.FMOD_Channel_Set3DAttributes(
                            voiceManagerData1.userplaychannel, player2.x,
                            player2.y, player2.z, 0.0F, 0.0F, 0.0F);
                        this.setUserPlaySound(
                            voiceManagerData1.userplaychannel,
                            radioData.deviceData.getDeviceVolume());
                        radioData.deviceData.doReceiveMPSignal(
                            radioData.lastReceiveDistance);
                        voiceDataSource =
                            VoiceManagerData.VoiceDataSource.Radio;
                        int2 = radioData.freq;
                      } else {
                        if (radioData == nullptr) {
                          javafmodJNI.FMOD_Channel_Set3DLevel(
                              voiceManagerData1.userplaychannel, 0.0F);
                          javafmod.FMOD_Channel_Set3DAttributes(
                              voiceManagerData1.userplaychannel, player2.x,
                              player2.y, player2.z, 0.0F, 0.0F, 0.0F);
                          javafmod.FMOD_Channel_SetVolume(
                              voiceManagerData1.userplaychannel, 0.0F);
                          voiceDataSource =
                              VoiceManagerData.VoiceDataSource.Unknown;
                        } else {
                          if (is3D) {
                            javafmodJNI.FMOD_Channel_Set3DLevel(
                                voiceManagerData1.userplaychannel,
                                IsoUtils.lerp(float0, 0.0F, minDistance));
                            javafmod.FMOD_Channel_Set3DAttributes(
                                voiceManagerData1.userplaychannel, player1.x,
                                player1.y, player1.z, 0.0F, 0.0F, 0.0F);
                          } else {
                            javafmodJNI.FMOD_Channel_Set3DLevel(
                                voiceManagerData1.userplaychannel, 0.0F);
                            javafmod.FMOD_Channel_Set3DAttributes(
                                voiceManagerData1.userplaychannel, player2.x,
                                player2.y, player2.z, 0.0F, 0.0F, 0.0F);
                          }

                          this.setUserPlaySound(
                              voiceManagerData1.userplaychannel,
                              IsoUtils.smoothstep(
                                  maxDistance, minDistance,
                                  radioData.lastReceiveDistance));
                          voiceDataSource =
                              VoiceManagerData.VoiceDataSource.Voice;
                        }

                        int2 = 0;
                        if (float0 > maxDistance) {
                          logFrame(player2, player1, float0);
                        }
                      }
                    }

                    javafmod.FMOD_System_RAWPlayData(
                        this.getUserPlaySound(player1.getOnlineID()), this.buf,
                        (long)this.buf.length);
                    if (this.isDebugLoopbackLong) {
                      RakVoice.SendFrame(GameClient.connection.connectedGUID,
                                         player2.getOnlineID(), this.buf,
                                         this.buf.length);
                    }
                  }
                }

                if (voiceManagerData1.voicetimeout == 0L) {
                  player1.isSpeek = false;
                } else {
                  voiceManagerData1.voicetimeout--;
                  player1.isSpeek = true;
                }
              }
            }

            MPStatistics.setVOIPSource(voiceDataSource, int2);
          }
        }
        }

        static void logFrame(IsoPlayer player1, IsoPlayer player0,
                             float float0) {
          long long0 = System.currentTimeMillis();
          if (long0 > timestamp) {
            timestamp = long0 + 5000L;
            DebugLog.Multiplayer.warn(String.format(
                "\"%s\" (%b) received VOIP frame from \"%s\" (%b) at "
                "distance=%f",
                player1.getUsername(), player1.isCanHearAll(),
                player0.getUsername(), player0.isCanHearAll(), float0));
          }
        }

      private
        VoiceManagerData.RadioData
        checkForNearbyRadios(VoiceManagerData voiceManagerData1) {
          IsoPlayer player = IsoPlayer.getInstance();
          VoiceManagerData voiceManagerData0 =
              VoiceManagerData.get(player.OnlineID);
          if (voiceManagerData0.isCanHearAll) {
            voiceManagerData0.radioData.get(0).lastReceiveDistance = 0.0F;
            return voiceManagerData0.radioData.get(0);
          } else {
            synchronized(voiceManagerData0.radioData) {
              for (int int0 = 1; int0 < voiceManagerData0.radioData.size();
                   int0++) {
                synchronized(voiceManagerData1.radioData) {
                  for (int int1 = 1; int1 < voiceManagerData1.radioData.size();
                       int1++) {
                    if (voiceManagerData0.radioData.get(int0).freq ==
                        voiceManagerData1.radioData.get(int1).freq) {
                      float float0 = voiceManagerData0.radioData.get(int0).x -
                                     voiceManagerData1.radioData.get(int1).x;
                      float float1 = voiceManagerData0.radioData.get(int0).y -
                                     voiceManagerData1.radioData.get(int1).y;
                      voiceManagerData0.radioData.get(int0)
                          .lastReceiveDistance =
                          (float)Math.sqrt(float0 * float0 + float1 * float1);
                      if (voiceManagerData0.radioData.get(int0)
                              .lastReceiveDistance <
                          voiceManagerData1.radioData.get(int1).distance) {
                        return voiceManagerData0.radioData.get(int0);
                      }
                    }
                  }
                }
              }
            }

            synchronized(voiceManagerData0.radioData) {
              synchronized(voiceManagerData1.radioData) {
                if (!voiceManagerData1.radioData.isEmpty() &&
                    !voiceManagerData0.radioData.isEmpty()) {
                  float float2 = voiceManagerData0.radioData.get(0).x -
                                 voiceManagerData1.radioData.get(0).x;
                  float float3 = voiceManagerData0.radioData.get(0).y -
                                 voiceManagerData1.radioData.get(0).y;
                  voiceManagerData0.radioData.get(0).lastReceiveDistance =
                      (float)Math.sqrt(float2 * float2 + float3 * float3);
                  if (voiceManagerData0.radioData.get(0).lastReceiveDistance <
                      voiceManagerData1.radioData.get(0).distance) {
                    return voiceManagerData0.radioData.get(0);
                  }
                }
              }

              return null;
            }
          }
        }

        void UpdateChannelsRoaming(UdpConnection udpConnection) {
          IsoPlayer player0 = IsoPlayer.getInstance();
          if (player0.OnlineID != -1) {
            VoiceManagerData voiceManagerData =
                VoiceManagerData.get(player0.OnlineID);
            bool boolean0 = false;
            synchronized(voiceManagerData.radioData) {
              voiceManagerData.radioData.clear();

              for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
                IsoPlayer player1 = IsoPlayer.players[int0];
                if (player1 != nullptr) {
                  boolean0 |= player1.isCanHearAll();
                  voiceManagerData.radioData.add(new VoiceManagerData.RadioData(
                      RakVoice.GetMaxDistance(), player1.x, player1.y));

                  for (int int1 = 0;
                       int1 < player1.getInventory().getItems().size();
                       int1++) {
                    InventoryItem item =
                        player1.getInventory().getItems().get(int1);
                    if (item instanceof Radio) {
                      DeviceData deviceData0 = ((Radio)item).getDeviceData();
                      if (deviceData0 != nullptr &&
                          deviceData0.getIsTurnedOn()) {
                        voiceManagerData.radioData.add(
                            new VoiceManagerData.RadioData(
                                deviceData0, player1.x, player1.y));
                      }
                    }
                  }

                  for (int int2 = (int)player1.getX() - 4;
                       int2 < player1.getX() + 5.0F; int2++) {
                    for (int int3 = (int)player1.getY() - 4;
                         int3 < player1.getY() + 5.0F; int3++) {
                      for (int int4 = (int)player1.getZ() - 1;
                           int4 < player1.getZ() + 1.0F; int4++) {
                        IsoGridSquare square =
                            IsoCell.getInstance().getGridSquare(int2, int3,
                                                                int4);
                        if (square != nullptr) {
                          if (square.getObjects() != nullptr) {
                            for (int int5 = 0;
                                 int5 < square.getObjects().size(); int5++) {
                              IsoObject object = square.getObjects().get(int5);
                              if (object instanceof IsoRadio) {
                                DeviceData deviceData1 =
                                    ((IsoRadio)object).getDeviceData();
                                if (deviceData1 != nullptr &&
                                    deviceData1.getIsTurnedOn()) {
                                  voiceManagerData.radioData.add(
                                      new VoiceManagerData.RadioData(
                                          deviceData1, square.x, square.y));
                                }
                              }
                            }
                          }

                          if (square.getWorldObjects() != nullptr) {
                            for (int int6 = 0;
                                 int6 < square.getWorldObjects().size();
                                 int6++) {
                              IsoWorldInventoryObject worldInventoryObject =
                                  square.getWorldObjects().get(int6);
                              if (worldInventoryObject.getItem() != nullptr &&
                                      worldInventoryObject.getItem()
                                      instanceof Radio) {
                                DeviceData deviceData2 =
                                    ((Radio)worldInventoryObject.getItem())
                                        .getDeviceData();
                                if (deviceData2 != nullptr &&
                                    deviceData2.getIsTurnedOn()) {
                                  voiceManagerData.radioData.add(
                                      new VoiceManagerData.RadioData(
                                          deviceData2, square.x, square.y));
                                }
                              }
                            }
                          }

                          if (square.getVehicleContainer() != nullptr &&
                              square ==
                                  square.getVehicleContainer().getSquare()) {
                            VehiclePart part =
                                square.getVehicleContainer().getPartById(
                                    "Radio");
                            if (part != nullptr) {
                              DeviceData deviceData3 = part.getDeviceData();
                              if (deviceData3 != nullptr &&
                                  deviceData3.getIsTurnedOn()) {
                                voiceManagerData.radioData.add(
                                    new VoiceManagerData.RadioData(
                                        deviceData3, square.x, square.y));
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

            ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
            PacketTypes.PacketType.SyncRadioData.doPacket(byteBufferWriter);
            byteBufferWriter.putByte((byte)(boolean0 ? 1 : 0));
            byteBufferWriter.putInt(voiceManagerData.radioData.size() * 4);

            for (VoiceManagerData.RadioData radioData :
                 voiceManagerData.radioData) {
              byteBufferWriter.putInt(radioData.freq);
              byteBufferWriter.putInt((int)radioData.distance);
              byteBufferWriter.putInt(radioData.x);
              byteBufferWriter.putInt(radioData.y);
            }

            PacketTypes.PacketType.SyncRadioData.send(udpConnection);
          }
        }

        void InitVMServer() {
          this.VoiceInitServer(
              ServerOptions.instance.VoiceEnable.getValue(), 24000, 20, 5, 8000,
              ServerOptions.instance.VoiceMinDistance.getValue(),
              ServerOptions.instance.VoiceMaxDistance.getValue(),
              ServerOptions.instance.Voice3D.getValue());
        }

        int getMicVolumeIndicator() {
          return FMODReceiveBuffer = =
                     null ? 0 : (int)FMODReceiveBuffer.get_loudness();
        }

        bool getMicVolumeError() {
          return FMODReceiveBuffer = =
                     null ? true : FMODReceiveBuffer.get_interror();
        }

        bool getServerVOIPEnable() { return serverVOIPEnable; }

        void VMServerBan(short short0, bool boolean0) {
          RakVoice.SetVoiceBan(short0, boolean0);
        }
        }
        } // namespace raknet
        } // namespace core
        } // namespace zombie
