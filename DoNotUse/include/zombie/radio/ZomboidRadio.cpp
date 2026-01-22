#pragma once
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/SandboxOptions.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/chat/ChatElement.h"
#include "zombie/chat/ChatMessage.h"
#include "zombie/core/Color.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/VoiceManagerData.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/inventory/types/Radio.h"
#include "zombie/iso/weather/ClimateManager.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/radio/StorySounds/SLSoundManager.h"
#include "zombie/radio/ZomboidRadio/FreqListEntry.h"
#include "zombie/radio/devices/DeviceData.h"
#include "zombie/radio/devices/WaveSignalDevice.h"
#include "zombie/radio/media/RecordedMedia.h"
#include "zombie/radio/scripting/RadioChannel.h"
#include "zombie/radio/scripting/RadioScript.h"
#include "zombie/radio/scripting/RadioScriptManager.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace radio {


class ZomboidRadio {
public:
    static const std::string SAVE_FILE = "RADIO_SAVE.txt";
   private const std::vector<WaveSignalDevice> devices = std::make_unique<std::vector<>>();
   private const std::vector<WaveSignalDevice> broadcastDevices = std::make_unique<std::vector<>>();
    RadioScriptManager scriptManager;
    int DaysSinceStart = 0;
    int lastRecordedHour;
   private const std::string[] playerLastLine = new std::string[4];
   private const Map<int, std::string> channelNames = std::make_unique<std::unordered_map<>>();
   private const Map<std::string, Map<int, std::string>> categorizedChannels = std::make_unique<std::unordered_map<>>();
   private const List<int> knownFrequencies = std::make_unique<std::vector<>>();
    RadioDebugConsole debugConsole;
    bool hasRecievedServerData = false;
    SLSoundManager storySoundManager = nullptr;
   private static const std::string[] staticSounds = new std::string[]{"<bzzt>", "<fzzt>", "<wzzt>", "<szzt>"};
    static bool DEBUG_MODE = false;
    static bool DEBUG_XML = false;
    static bool DEBUG_SOUND = false;
    static bool POST_RADIO_SILENCE = false;
    static bool DISABLE_BROADCASTING = false;
    static ZomboidRadio instance;
    static RecordedMedia recordedMedia;
    static bool LOUISVILLE_OBFUSCATION = false;
    std::string lastSaveFile;
    std::string lastSaveContent;
   private std::unordered_map<int, FreqListEntry> freqlist = std::make_unique<std::unordered_map<>>();
    bool hasAppliedRangeDistortion = false;
    std::stringstream stringBuilder = new std::stringstream();
    bool hasAppliedInterference = false;
   private static int[] obfuscateChannels = new int[]{200, 201, 204, 93200, 98000, 101200};

    static bool hasInstance() {
      return instance != nullptr;
   }

    static ZomboidRadio getInstance() {
      if (instance == nullptr) {
         instance = std::make_unique<ZomboidRadio>();
      }

    return instance;
   }

    private ZomboidRadio() {
      this.lastRecordedHour = GameTime.instance.getHour();
      SLSoundManager.DEBUG = DEBUG_SOUND;

      for (int var1 = 0; var1 < staticSounds.length; var1++) {
         ChatElement.addNoLogText(staticSounds[var1]);
      }

      ChatElement.addNoLogText("~");
      recordedMedia = std::make_unique<RecordedMedia>();
   }

    static bool isStaticSound(const std::string& var0) {
      if (var0 != nullptr) {
    for (auto& var4 : staticSounds)            if (var0 == var4)) {
    return true;
            }
         }
      }

    return false;
   }

    RadioScriptManager getScriptManager() {
      return this.scriptManager;
   }

    int getDaysSinceStart() {
      return this.DaysSinceStart;
   }

   public std::vector<WaveSignalDevice> getDevices() {
      return this.devices;
   }

   public std::vector<WaveSignalDevice> getBroadcastDevices() {
      return this.broadcastDevices;
   }

    void setHasRecievedServerData(bool var1) {
      this.hasRecievedServerData = var1;
   }

    void addChannelName(const std::string& var1, int var2, const std::string& var3) {
      this.addChannelName(var1, var2, var3, true);
   }

    void addChannelName(const std::string& var1, int var2, const std::string& var3, bool var4) {
      if (var4 || !this.channelNames.containsKey(var2)) {
         if (!this.categorizedChannels.containsKey(var3)) {
            this.categorizedChannels.put(var3, std::make_unique<std::unordered_map<>>());
         }

         this.categorizedChannels.get(var3).put(var2, var1);
         this.channelNames.put(var2, var1);
         this.knownFrequencies.push_back(var2);
      }
   }

    void removeChannelName(int var1) {
      if (this.channelNames.containsKey(var1)) {
         this.channelNames.remove(var1);

         for (Entry var3 : this.categorizedChannels.entrySet()) {
            if (((Map)var3.getValue()).containsKey(var1)) {
               ((Map)var3.getValue()).remove(var1);
            }
         }
      }
   }

   public Map<int, std::string> GetChannelList(std::string var1) {
      return this.categorizedChannels.containsKey(var1) ? this.categorizedChannels.get(var1) : nullptr;
   }

    std::string getChannelName(int var1) {
      return this.channelNames.containsKey(var1) ? this.channelNames.get(var1) : nullptr;
   }

    int getRandomFrequency() {
      return this.getRandomFrequency(88000, 108000);
   }

    int getRandomFrequency(int var1, int var2) {
    int var3 = 91100;

      do {
         var3 = Rand.Next(var1, var2);
         var3 /= 200;
         var3 *= 200;
      } while (this.knownFrequencies.contains(var3));

    return var3;
   }

   public Map<std::string, Map<int, std::string>> getFullChannelList() {
      return this.categorizedChannels;
   }

    void WriteRadioServerDataPacket(ByteBufferWriter var1) {
      var1.putInt(this.categorizedChannels.size());

      for (Entry var3 : this.categorizedChannels.entrySet()) {
         GameWindow.WriteString(var1.bb, (std::string)var3.getKey());
         var1.putInt(((Map)var3.getValue()).size());

         for (Entry var5 : ((Map)var3.getValue()).entrySet()) {
            var1.putInt((int)var5.getKey());
            GameWindow.WriteString(var1.bb, (std::string)var5.getValue());
         }
      }

      var1.putByte((byte)(POST_RADIO_SILENCE ? 1 : 0));
   }

    void Init(int var1) {
      POST_RADIO_SILENCE = false;
    bool var2 = false;
    bool var3 = DebugLog.isEnabled(DebugType.Radio);
      if (var3) {
         DebugLog.Radio.println("");
         DebugLog.Radio.println("################## Radio Init ##################");
      }

      RadioAPI.getInstance();
      recordedMedia.init();
      this.lastRecordedHour = GameTime.instance.getHour();
    GameMode var4 = this.getGameMode();
      if (DEBUG_MODE && !var4 == GameMode.Server)) {
         DebugLog.setLogEnabled(DebugType.Radio, true);
         this.debugConsole = std::make_unique<RadioDebugConsole>();
      }

      if (var4 == GameMode.Client)) {
         GameClient.sendRadioServerDataRequest();
         if (var3) {
            DebugLog.Radio.println("Radio (Client) loaded.");
            DebugLog.Radio.println("################################################");
         }

         this.scriptManager = nullptr;
      } else {
         this.scriptManager = RadioScriptManager.getInstance();
         this.scriptManager.init(var1);

         try {
            if (!Core.getInstance().isNoSave()) {
               ZomboidFileSystem.instance.getFileInCurrentSave("radio", "data").mkdirs();
            }

            for (RadioData var7 : RadioData.fetchAllRadioData()) {
               for (RadioChannel var9 : var7.getRadioChannels()) {
                  ObfuscateChannelCheck(var9);
    RadioChannel var10 = nullptr;
                  if (this.scriptManager.getChannels().containsKey(var9.GetFrequency())) {
                     var10 = (RadioChannel)this.scriptManager.getChannels().get(var9.GetFrequency());
                  }

                  if (var10 != nullptr && (!var10.getRadioData().isVanilla() || var9.getRadioData().isVanilla())) {
                     if (var3) {
                        DebugLog.Radio.println("Unable to add channel: " + var9.GetName() + ", frequency '" + var9.GetFrequency() + "' taken.");
                     }
                  } else {
                     this.scriptManager.AddChannel(var9, true);
                  }
               }
            }

            LuaEventManager.triggerEvent("OnLoadRadioScripts", this.scriptManager, var1 == -1);
            if (var1 == -1) {
               if (var3) {
                  DebugLog.Radio.println("Radio setting new game start times");
               }

    SandboxOptions var12 = SandboxOptions.instance;
    int var14 = var12.TimeSinceApo.getValue() - 1;
               if (var14 < 0) {
                  var14 = 0;
               }

               if (var3) {
                  DebugLog.log(DebugType.Radio, "Time since the apocalypse: " + var12.TimeSinceApo.getValue());
               }

               if (var14 > 0) {
                  this.DaysSinceStart = (int)(var14 * 30.5F);
                  if (var3) {
                     DebugLog.Radio.println("Time since the apocalypse in days: " + this.DaysSinceStart);
                  }

                  this.scriptManager.simulateScriptsUntil(this.DaysSinceStart, true);
               }

               this.checkGameModeSpecificStart();
            } else {
    bool var13 = this.Load();
               if (!var13) {
    SandboxOptions var15 = SandboxOptions.instance;
    int var16 = var15.TimeSinceApo.getValue() - 1;
                  if (var16 < 0) {
                     var16 = 0;
                  }

                  this.DaysSinceStart = (int)(var16 * 30.5F);
                  this.DaysSinceStart = this.DaysSinceStart + GameTime.instance.getNightsSurvived();
               }

               if (this.DaysSinceStart > 0) {
                  this.scriptManager.simulateScriptsUntil(this.DaysSinceStart, false);
               }
            }

            var2 = true;
         } catch (Exception var11) {
            ExceptionLogger.logException(var11);
         }

         if (var3) {
            if (var2) {
               DebugLog.Radio.println("Radio loaded.");
            }

            DebugLog.Radio.println("################################################");
            DebugLog.Radio.println("");
         }
      }
   }

    void checkGameModeSpecificStart() {
      if (Core.GameMode == "Initial Infection")) {
         for (Entry var2 : this.scriptManager.getChannels().entrySet()) {
    RadioScript var3 = ((RadioChannel)var2.getValue()).getRadioScript("init_infection");
            if (var3 != nullptr) {
               var3.clearExitOptions();
               var3.AddExitOption(((RadioChannel)var2.getValue()).getCurrentScript().GetName(), 100, 0);
               ((RadioChannel)var2.getValue()).setActiveScript("init_infection", this.DaysSinceStart);
            } else {
               ((RadioChannel)var2.getValue()).getCurrentScript().setStartDayStamp(this.DaysSinceStart + 1);
            }
         }
      } else if (Core.GameMode == "Six Months Later")) {
         for (Entry var5 : this.scriptManager.getChannels().entrySet()) {
            if (((RadioChannel)var5.getValue()).GetName() == "Classified M1A1")) {
               ((RadioChannel)var5.getValue()).setActiveScript("numbers", this.DaysSinceStart);
            } else if (((RadioChannel)var5.getValue()).GetName() == "NNR Radio")) {
               ((RadioChannel)var5.getValue()).setActiveScript("pastor", this.DaysSinceStart);
            }
         }
      }
   }

    void Save() {
      if (!Core.getInstance().isNoSave()) {
    GameMode var1 = this.getGameMode();
         if ((var1 == GameMode.Server) || var1 == GameMode.SinglePlayer)) && this.scriptManager != nullptr) {
    File var2 = ZomboidFileSystem.instance.getFileInCurrentSave("radio", "data");
            if (var2.exists() && var2.isDirectory()) {
    std::string var3 = ZomboidFileSystem.instance.getFileNameInCurrentSave("radio", "data", "RADIO_SAVE.txt");

    std::string var4;
               try (StringWriter var5 = std::make_shared<StringWriter>(1024)) {
                  var5.write("DaysSinceStart = " + this.DaysSinceStart + System.lineSeparator());
                  var5.write("LvObfuscation = " + LOUISVILLE_OBFUSCATION + System.lineSeparator());
                  this.scriptManager.Save(var5);
                  var4 = var5;
               } catch (IOException var15) {
                  ExceptionLogger.logException(var15);
                  return;
               }

               if (var3 == this.lastSaveFile) && var4 == this.lastSaveContent)) {
                  return;
               }

               this.lastSaveFile = var3;
               this.lastSaveContent = var4;
    File var16 = std::make_shared<File>(var3);
               if (DebugLog.isEnabled(DebugType.Radio)) {
                  DebugLog.Radio.println("Saving radio: " + var3);
               }

               try (FileWriter var6 = std::make_shared<FileWriter>(var16, false)) {
                  var6.write(var4);
               } catch (Exception var13) {
                  ExceptionLogger.logException(var13);
               }
            }
         }

         if (recordedMedia != nullptr) {
            try {
               recordedMedia.save();
            } catch (Exception var10) {
               var10.printStackTrace();
            }
         }
      }
   }

    bool Load() {
    bool var1 = false;
    GameMode var2 = this.getGameMode();
      if (var2 == GameMode.Server) || var2 == GameMode.SinglePlayer)) {
         for (Entry var4 : this.scriptManager.getChannels().entrySet()) {
            ((RadioChannel)var4.getValue()).setActiveScriptNull();
         }

    std::vector var26 = new std::vector();
    std::string var27 = ZomboidFileSystem.instance.getFileNameInCurrentSave("radio", "data", "RADIO_SAVE.txt");
    File var5 = std::make_shared<File>(var27);
         if (!var5.exists()) {
    return false;
         } else {
            if (DebugLog.isEnabled(DebugType.Radio)) {
               DebugLog.log(DebugType.Radio, "Loading radio save:" + var27);
            }

    std::string var8;
            try (
    FileReader var6 = std::make_shared<FileReader>(var5);
    BufferedReader var7 = std::make_shared<BufferedReader>(var6);
            ) {
               while ((var8 = var7.readLine()) != nullptr) {
                  var8 = var8.trim();
                  if (!var8.startsWith("DaysSinceStart") && !var8.startsWith("LvObfuscation")) {
                     var26.push_back(var8);
                  } else {
                     if (var8.startsWith("DaysSinceStart")) {
                        std::string[] var9 = var8.split("=");
                        this.DaysSinceStart = int.parseInt(var9[1].trim());
                     }

                     if (var8.startsWith("LvObfuscation")) {
                        std::string[] var30 = var8.split("=");
                        LOUISVILLE_OBFUSCATION = bool.parseBoolean(var30[1].trim());
                     }
                  }
               }
            } catch (Exception var24) {
               var24.printStackTrace();
    return false;
            }

    bool var28;
            try {
               DebugLog.log("Radio Loading channels...");
               this.scriptManager.Load(var26);
    return var1;
            } catch (Exception var20) {
               var20.printStackTrace();
               var28 = false;
            } finally {
               var1 = true;
            }

    return var28;
         }
      } else {
    return var1;
      }
   }

    void Reset() {
      instance = nullptr;
      if (this.scriptManager != nullptr) {
         this.scriptManager.reset();
      }
   }

    void UpdateScripts(int var1, int var2) {
    GameMode var3 = this.getGameMode();
      if (var3 == GameMode.Server) || var3 == GameMode.SinglePlayer)) {
         if (var1 == 0 && this.lastRecordedHour != 0) {
            this.DaysSinceStart++;
         }

         this.lastRecordedHour = var1;
         if (this.scriptManager != nullptr) {
            this.scriptManager.UpdateScripts(this.DaysSinceStart, var1, var2);
         }

         try {
            this.Save();
         } catch (Exception var6) {
            System.out.println(var6.getMessage());
         }
      }

      if (var3 == GameMode.Client) || var3 == GameMode.SinglePlayer)) {
         for (int var4 = 0; var4 < this.devices.size(); var4++) {
    WaveSignalDevice var5 = this.devices.get(var4);
            if (var5.getDeviceData().getIsTurnedOn() && var5.HasPlayerInRange()) {
               var5.getDeviceData().TriggerPlayerListening(true);
            }
         }
      }

      if (var3 == GameMode.Client) && !this.hasRecievedServerData) {
         GameClient.sendRadioServerDataRequest();
      }
   }

    void render() {
    GameMode var1 = this.getGameMode();
      if (DEBUG_MODE && !var1 == GameMode.Server) && this.debugConsole != nullptr) {
         this.debugConsole.render();
      }

      if (!var1 == GameMode.Server) && this.storySoundManager != nullptr) {
         this.storySoundManager.render();
      }
   }

    void addFrequencyListEntry(bool var1, DeviceData var2, int var3, int var4) {
      if (var2 != nullptr) {
         if (!this.freqlist.containsKey(var2.getChannel())) {
            this.freqlist.put(var2.getChannel(), std::make_shared<FreqListEntry>(var1, var2, var3, var4));
         } else if (this.freqlist.get(var2.getChannel()).deviceData.getTransmitRange() < var2.getTransmitRange()) {
    FreqListEntry var5 = this.freqlist.get(var2.getChannel());
            var5.isInvItem = var1;
            var5.deviceData = var2;
            var5.sourceX = var3;
            var5.sourceY = var4;
         }
      }
   }

    void update() {
      this.LouisvilleObfuscationCheck();
      if (DEBUG_MODE && this.debugConsole != nullptr) {
         this.debugConsole.update();
      }

    GameMode var1 = this.getGameMode();
      if ((var1 == GameMode.Server) || var1 == GameMode.SinglePlayer)) && this.DaysSinceStart > 14 && !POST_RADIO_SILENCE) {
         POST_RADIO_SILENCE = true;
         if (GameServer.bServer) {
            GameServer.sendRadioPostSilence();
         }
      }

      if (!var1 == GameMode.Server) && this.storySoundManager != nullptr) {
         this.storySoundManager.update(this.DaysSinceStart, GameTime.instance.getHour(), GameTime.instance.getMinutes());
      }

      if ((var1 == GameMode.Server) || var1 == GameMode.SinglePlayer)) && this.scriptManager != nullptr) {
         this.scriptManager.update();
      }

      if (var1 == GameMode.SinglePlayer) || var1 == GameMode.Client)) {
         for (int var2 = 0; var2 < IsoPlayer.numPlayers; var2++) {
    IsoPlayer var3 = IsoPlayer.players[var2];
            if (var3 != nullptr
               && var3.getLastSpokenLine() != nullptr
               && (this.playerLastLine[var2] == nullptr || !this.playerLastLine[var2] == var3.getLastSpokenLine()))) {
    std::string var4 = var3.getLastSpokenLine();
               this.playerLastLine[var2] = var4;
               if (!var1 == GameMode.Client)
                  || (
                        !var3.accessLevel == "admin")
                              && !var3.accessLevel == "gm")
                              && !var3.accessLevel == "overseer")
                              && !var3.accessLevel == "moderator")
                           || !ServerOptions.instance.DisableRadioStaff.getValue()
                              && (!ServerOptions.instance.DisableRadioAdmin.getValue() || !var3.accessLevel == "admin"))
                              && (!ServerOptions.instance.DisableRadioGM.getValue() || !var3.accessLevel == "gm"))
                              && (!ServerOptions.instance.DisableRadioOverseer.getValue() || !var3.accessLevel == "overseer"))
                              && (!ServerOptions.instance.DisableRadioModerator.getValue() || !var3.accessLevel == "moderator"))
                     )
                     && (!ServerOptions.instance.DisableRadioInvisible.getValue() || !var3.isInvisible())) {
                  this.freqlist.clear();
                  if (!GameClient.bClient && !GameServer.bServer) {
                     for (int var9 = 0; var9 < IsoPlayer.numPlayers; var9++) {
                        this.checkPlayerForDevice(IsoPlayer.players[var9], var3);
                     }
                  } else if (GameClient.bClient) {
    std::vector var5 = GameClient.instance.getPlayers();

                     for (int var6 = 0; var6 < var5.size(); var6++) {
                        this.checkPlayerForDevice((IsoPlayer)var5.get(var6), var3);
                     }
                  }

                  for (WaveSignalDevice var12 : this.broadcastDevices) {
                     if (var12 != nullptr
                        && var12.getDeviceData() != nullptr
                        && var12.getDeviceData().getIsTurnedOn()
                        && var12.getDeviceData().getIsTwoWay()
                        && var12.HasPlayerInRange()
                        && !var12.getDeviceData().getMicIsMuted()
                        && this.GetDistance((int)var3.getX(), (int)var3.getY(), (int)var12.getX(), (int)var12.getY()) < var12.getDeviceData().getMicRange()) {
                        this.addFrequencyListEntry(true, var12.getDeviceData(), (int)var12.getX(), (int)var12.getY());
                     }
                  }

                  if (this.freqlist.size() > 0) {
    Color var11 = var3.getSpeakColour();

                     for (Entry var7 : this.freqlist.entrySet()) {
    FreqListEntry var8 = (FreqListEntry)var7.getValue();
                        this.SendTransmission(
                           var8.sourceX,
                           var8.sourceY,
                           (int)var7.getKey(),
                           this.playerLastLine[var2],
                           nullptr,
                           nullptr,
                           var11.r,
                           var11.g,
                           var11.b,
                           var8.deviceData.getTransmitRange(),
                           false
                        );
                     }
                  }
               }
            }
         }
      }
   }

    void checkPlayerForDevice(IsoPlayer var1, IsoPlayer var2) {
    bool var3 = var1 == var2;
      if (var1 != nullptr) {
    Radio var4 = var1.getEquipedRadio();
         if (var4 != nullptr
            && var4.getDeviceData() != nullptr
            && var4.getDeviceData().getIsPortable()
            && var4.getDeviceData().getIsTwoWay()
            && var4.getDeviceData().getIsTurnedOn()
            && !var4.getDeviceData().getMicIsMuted()
            && (var3 || this.GetDistance((int)var2.getX(), (int)var2.getY(), (int)var1.getX(), (int)var1.getY()) < var4.getDeviceData().getMicRange())) {
            this.addFrequencyListEntry(true, var4.getDeviceData(), (int)var1.getX(), (int)var1.getY());
         }
      }
   }

    bool DeviceInRange(int var1, int var2, int var3, int var4, int var5) {
      return var1 > var3 - var5
         && var1 < var3 + var5
         && var2 > var4 - var5
         && var2 < var4 + var5
         && Math.sqrt(Math.pow(var1 - var3, 2.0) + Math.pow(var2 - var4, 2.0)) < var5;
   }

    int GetDistance(int var1, int var2, int var3, int var4) {
      return (int)Math.sqrt(Math.pow(var1 - var3, 2.0) + Math.pow(var2 - var4, 2.0));
   }

   private void DistributeToPlayerOnClient(
      IsoPlayer var1, int var2, int var3, int var4, std::string var5, std::string var6, std::string var7, float var8, float var9, float var10, int var11, boolean var12
   ) {
      if (var1 != nullptr && var1.getOnlineID() != -1) {
    VoiceManagerData var13 = VoiceManagerData.get(var1.getOnlineID());
         /* synchronized - TODO: add std::mutex */ (var13.radioData) {
            for (zombie.core.raknet.VoiceManagerData.RadioData var16 : var13.radioData) {
               if (var16.isReceivingAvailable(var4)) {
                  this.DistributeToPlayerInternal(var16.getDeviceData().getParent(), var1, var2, var3, var5, var6, var7, var8, var9, var10, var11);
               }
            }
         }
      }
   }

   private void DistributeToPlayer(
      IsoPlayer var1, int var2, int var3, int var4, std::string var5, std::string var6, std::string var7, float var8, float var9, float var10, int var11, boolean var12
   ) {
      if (var1 != nullptr) {
    Radio var13 = var1.getEquipedRadio();
         if (var13 != nullptr
            && var13.getDeviceData() != nullptr
            && var13.getDeviceData().getIsPortable()
            && var13.getDeviceData().getIsTurnedOn()
            && var13.getDeviceData().getChannel() == var4) {
            if (var13.getDeviceData().getDeviceVolume() <= 0.0F) {
               return;
            }

            if (var13.getDeviceData().isPlayingMedia() || var13.getDeviceData().isNoTransmit()) {
               return;
            }

            this.DistributeToPlayerInternal(var13, var1, var2, var3, var5, var6, var7, var8, var9, var10, var11);
         }
      }
   }

   private void DistributeToPlayerInternal(
      WaveSignalDevice var1, IsoPlayer var2, int var3, int var4, std::string var5, std::string var6, std::string var7, float var8, float var9, float var10, int var11
   ) {
    bool var12 = false;
    int var13 = -1;
      if (var11 < 0) {
         var12 = true;
      } else {
         var13 = this.GetDistance((int)var2.getX(), (int)var2.getY(), var3, var4);
         if (var13 > 3 && var13 < var11) {
            var12 = true;
         }
      }

      if (var12) {
         if (var11 > 0) {
            this.hasAppliedRangeDistortion = false;
            var5 = this.doDeviceRangeDistortion(var5, var11, var13);
         }

         if (!this.hasAppliedRangeDistortion) {
            var1.AddDeviceText(var2, var5, var8, var9, var10, var6, var7, var13);
         } else {
            var1.AddDeviceText(var5, 0.5F, 0.5F, 0.5F, var6, var7, var13);
         }
      }
   }

   private void DistributeTransmission(
      int var1, int var2, int var3, std::string var4, std::string var5, std::string var6, float var7, float var8, float var9, int var10, boolean var11
   ) {
      if (!var11) {
         if (!GameClient.bClient && !GameServer.bServer) {
            for (int var16 = 0; var16 < IsoPlayer.numPlayers; var16++) {
               this.DistributeToPlayer(IsoPlayer.players[var16], var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11);
            }
         } else if (GameClient.bClient) {
            for (IsoPlayer var15 : IsoPlayer.players) {
               this.DistributeToPlayerOnClient(var15, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11);
            }

            return;
         }
      }

      if (this.devices.size() != 0) {
         for (int var17 = 0; var17 < this.devices.size(); var17++) {
    WaveSignalDevice var18 = this.devices.get(var17);
            if (var18 != nullptr && var18.getDeviceData() != nullptr && var18.getDeviceData().getIsTurnedOn() && var11 == var18.getDeviceData().getIsTelevision()) {
               if (var18.getDeviceData().isPlayingMedia() || var18.getDeviceData().isNoTransmit()) {
                  return;
               }

               if (var3 == var18.getDeviceData().getChannel()) {
    bool var19 = false;
                  if (var10 == -1) {
                     var19 = true;
                  } else if (var1 != (int)var18.getX() && var2 != (int)var18.getY()) {
                     var19 = true;
                  }

                  if (var19) {
    int var20 = -1;
                     if (var10 > 0) {
                        this.hasAppliedRangeDistortion = false;
                        var20 = this.GetDistance((int)var18.getX(), (int)var18.getY(), var1, var2);
                        var4 = this.doDeviceRangeDistortion(var4, var10, var20);
                     }

                     if (!this.hasAppliedRangeDistortion) {
                        var18.AddDeviceText(var4, var7, var8, var9, var5, var6, var20);
                     } else {
                        var18.AddDeviceText(var4, 0.5F, 0.5F, 0.5F, var5, var6, var20);
                     }
                  }
               }
            }
         }
      }
   }

    std::string doDeviceRangeDistortion(const std::string& var1, int var2, int var3) {
    float var4 = var2 * 0.9F;
      if (var4 < var2 && var3 > var4) {
    float var5 = 100.0F * ((var3 - var4) / (var2 - var4));
         var1 = this.scrambleString(var1, (int)var5, false);
         this.hasAppliedRangeDistortion = true;
      }

    return var1;
   }

    GameMode getGameMode() {
      if (!GameClient.bClient && !GameServer.bServer) {
         return GameMode.SinglePlayer;
      } else {
         return GameServer.bServer ? GameMode.Server : GameMode.Client;
      }
   }

    std::string getRandomBzztFzzt() {
    int var1 = Rand.Next(staticSounds.length);
      return staticSounds[var1];
   }

    std::string applyWeatherInterference(const std::string& var1, int var2) {
      if (ClimateManager.getInstance().getWeatherInterference() <= 0.0F) {
    return var1;
      } else {
    int var3 = (int)(ClimateManager.getInstance().getWeatherInterference() * 100.0F);
         return this.scrambleString(var1, var3, var2 == -1);
      }
   }

    std::string scrambleString(const std::string& var1, int var2, bool var3) {
      return this.scrambleString(var1, var2, var3, nullptr);
   }

    std::string scrambleString(const std::string& var1, int var2, bool var3, const std::string& var4) {
      this.hasAppliedInterference = false;
    std::stringstream var5 = this.stringBuilder;
      var5.setLength(0);
      if (var2 <= 0) {
    return var1;
      } else if (var2 >= 100) {
         return var4 != nullptr ? var4 : this.getRandomBzztFzzt();
      } else {
         this.hasAppliedInterference = true;
         if (var3) {
            char[] var6 = var1.toCharArray();
    bool var7 = false;
    bool var8 = false;
    std::string var9 = "";

            for (int var10 = 0; var10 < var6.length; var10++) {
    char var11 = var6[var10];
               if (var8) {
                  var9 = var9 + var11;
                  if (var11 == ']') {
                     var5.append(var9);
                     var9 = "";
                     var8 = false;
                  }
               } else if (var11 == '[' || char.isWhitespace(var11) && var10 > 0 && !char.isWhitespace(var6[var10 - 1])) {
    int var12 = Rand.Next(100);
                  if (var12 > var2) {
                     var5.append(var9).append(" ");
                     var7 = false;
                  } else if (!var7) {
                     var5.append(var4 != nullptr ? var4 : this.getRandomBzztFzzt()).append(" ");
                     var7 = true;
                  }

                  if (var11 == '[') {
                     var9 = "[";
                     var8 = true;
                  } else {
                     var9 = "";
                  }
               } else {
                  var9 = var9 + var11;
               }
            }

            if (var9 != nullptr && var9.length() > 0) {
               var5.append(var9);
            }
         } else {
    bool var13 = false;
            std::string[] var14 = var1.split("\\s+");

            for (int var15 = 0; var15 < var14.length; var15++) {
    std::string var16 = var14[var15];
    int var17 = Rand.Next(100);
               if (var17 > var2) {
                  var5.append(var16).append(" ");
                  var13 = false;
               } else if (!var13) {
                  var5.append(var4 != nullptr ? var4 : this.getRandomBzztFzzt()).append(" ");
                  var13 = true;
               }
            }
         }

         return var5;
      }
   }

   public void ReceiveTransmission(
      int var1, int var2, int var3, std::string var4, std::string var5, std::string var6, float var7, float var8, float var9, int var10, boolean var11
   ) {
    GameMode var12 = this.getGameMode();
      if (var12 == GameMode.Server)) {
         this.SendTransmission(var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11);
      } else {
         this.DistributeTransmission(var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11);
      }
   }

    void SendTransmission(int var1, int var2, ChatMessage var3, int var4) {
    Color var5 = var3.getTextColor();
    int var6 = var3.getRadioChannel();
      this.SendTransmission(var1, var2, var6, var3.getText(), nullptr, nullptr, var5.r, var5.g, var5.b, var4, false);
   }

   public void SendTransmission(
      int var1, int var2, int var3, std::string var4, std::string var5, std::string var6, float var7, float var8, float var9, int var10, boolean var11
   ) {
      this.SendTransmission(-1L, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11);
   }

   public void SendTransmission(
      long var1, int var3, int var4, int var5, std::string var6, std::string var7, std::string var8, float var9, float var10, float var11, int var12, boolean var13
   ) {
    GameMode var14 = this.getGameMode();
      if (!var13 && (var14 == GameMode.Server || var14 == GameMode.SinglePlayer)) {
         this.hasAppliedInterference = false;
         var6 = this.applyWeatherInterference(var6, var12);
         if (this.hasAppliedInterference) {
            var9 = 0.5F;
            var10 = 0.5F;
            var11 = 0.5F;
            var8 = "";
         }
      }

      if (var14 == GameMode.SinglePlayer)) {
         this.ReceiveTransmission(var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13);
      } else if (var14 == GameMode.Server)) {
         GameServer.sendIsoWaveSignal(var1, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13);
      } else if (var14 == GameMode.Client)) {
         GameClient.sendIsoWaveSignal(var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13);
      }
   }

    void PlayerListensChannel(int var1, bool var2, bool var3) {
    GameMode var4 = this.getGameMode();
      if (!var4 == GameMode.SinglePlayer) && !var4 == GameMode.Server)) {
         if (var4 == GameMode.Client)) {
            GameClient.sendPlayerListensChannel(var1, var2, var3);
         }
      } else if (this.scriptManager != nullptr) {
         this.scriptManager.PlayerListensChannel(var1, var2, var3);
      }
   }

    void RegisterDevice(WaveSignalDevice var1) {
      if (var1 != nullptr) {
         if (!GameServer.bServer && !this.devices.contains(var1)) {
            this.devices.push_back(var1);
         }

         if (!GameServer.bServer && var1.getDeviceData().getIsTwoWay() && !this.broadcastDevices.contains(var1)) {
            this.broadcastDevices.push_back(var1);
         }
      }
   }

    void UnRegisterDevice(WaveSignalDevice var1) {
      if (var1 != nullptr) {
         if (!GameServer.bServer && this.devices.contains(var1)) {
            this.devices.remove(var1);
         }

         if (!GameServer.bServer && var1.getDeviceData().getIsTwoWay() && this.broadcastDevices.contains(var1)) {
            this.broadcastDevices.remove(var1);
         }
      }
   }

    void* clone() {
    return nullptr;
   }

    std::string computerize(const std::string& var1) {
    std::stringstream var2 = this.stringBuilder;
      var2.setLength(0);

      for (char var6 : var1.toCharArray()) {
         if (char.isLetter(var6)) {
            var2.append(Rand.NextBool(2) ? char.toLowerCase(var6) : char.toUpperCase(var6));
         } else {
            var2.append(var6);
         }
      }

      return var2;
   }

    RecordedMedia getRecordedMedia() {
    return recordedMedia;
   }

    void setDisableBroadcasting(bool var1) {
      DISABLE_BROADCASTING = var1;
   }

    bool getDisableBroadcasting() {
    return DISABLE_BROADCASTING;
   }

    void setDisableMediaLineLearning(bool var1) {
      RecordedMedia.DISABLE_LINE_LEARNING = var1;
   }

    bool getDisableMediaLineLearning() {
      return RecordedMedia.DISABLE_LINE_LEARNING;
   }

    void LouisvilleObfuscationCheck() {
      if (!GameClient.bClient && !GameServer.bServer) {
    IsoPlayer var1 = IsoPlayer.getInstance();
         if (var1 != nullptr && var1.getY() < 3550.0F) {
            LOUISVILLE_OBFUSCATION = true;
         }
      }
   }

    static void ObfuscateChannelCheck(RadioChannel var0) {
      if (var0.isVanilla()) {
    int var1 = var0.GetFrequency();

         for (int var2 = 0; var2 < obfuscateChannels.length; var2++) {
            if (var1 == obfuscateChannels[var2]) {
               var0.setLouisvilleObfuscate(true);
            }
         }
      }
   }
}
} // namespace radio
} // namespace zombie
