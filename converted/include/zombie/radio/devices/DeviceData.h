#pragma once
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/WorldSoundManager.h"
#include "zombie/audio/BaseSoundEmitter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Color.h"
#include "zombie/core/Rand.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/raknet/VoiceManager.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/inventory/ItemUser.h"
#include "zombie/inventory/types/DrainableComboItem.h"
#include "zombie/inventory/types/Radio.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/objects/IsoGenerator.h"
#include "zombie/iso/objects/IsoWaveSignal.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/PacketTypes.h"
#include "zombie/radio/ZomboidRadio.h"
#include "zombie/radio/media/MediaData.h"
#include "zombie/vehicles/VehiclePart.h"
#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace radio {
namespace devices {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * Turbo  Stores shared data for devices (used in iso and item)
 */
class DeviceData {
public:
  static const float deviceSpeakerSoundMod = 0.4F;
  static const float deviceButtonSoundVol = 0.05F;
  std::string deviceName = "WaveSignalDevice";
  bool twoWay = false;
  int transmitRange = 1000;
  int micRange = 5;
  bool micIsMuted = false;
  float baseVolumeRange = 15.0F;
  float deviceVolume = 1.0F;
  bool isPortable = false;
  bool isTelevision = false;
  bool isHighTier = false;
  bool isTurnedOn = false;
  int channel = 88000;
  int minChannelRange = 200;
  int maxChannelRange = 1000000;
  DevicePresets presets = null;
  bool isBatteryPowered = true;
  bool hasBattery = true;
  float powerDelta = 1.0F;
  float useDelta = 0.001F;
  int lastRecordedDistance = -1;
  int headphoneType = -1;
  WaveSignalDevice parent = null;
  GameTime gameTime = null;
  bool channelChangedRecently = false;
  BaseSoundEmitter emitter = null;
protected
  ArrayList<Long> soundIDs = std::make_unique<ArrayList<>>();
  short mediaIndex = -1;
  uint8_t mediaType = -1;
  std::string mediaItem = null;
  MediaData playingMedia = null;
  bool isPlayingMedia = false;
  int mediaLineIndex = 0;
  float lineCounter = 0.0F;
  std::string currentMediaLine = null;
  Color currentMediaColor = null;
  bool isStoppingMedia = false;
  float stopMediaCounter = 0.0F;
  bool noTransmit = false;
  float soundCounterStatic = 0.0F;
  long radioLoopSound = 0L;
  bool doTriggerWorldSound = false;
  long lastMinuteStamp = -1L;
  int listenCnt = 0;
  float nextStaticSound = 0.0F;
  float voipCounter = 0.0F;
  float signalCounter = 0.0F;
  float soundCounter = 0.0F;
  float minmod = 1.5F;
  float maxmod = 5.0F;

public
  DeviceData() { this(nullptr); }

public
  DeviceData(WaveSignalDevice _parent) {
    this.parent = _parent;
    this.presets = std::make_unique<DevicePresets>();
    this.gameTime = GameTime.getInstance();
  }

  void generatePresets() {
    if (this.presets == nullptr) {
      this.presets = std::make_unique<DevicePresets>();
    }

    this.presets.clearPresets();
    if (this.isTelevision) {
      std::unordered_map map0 =
          ZomboidRadio.getInstance().GetChannelList("Television");
      if (map0 != nullptr) {
        for (Entry entry0 : map0.entrySet()) {
          if ((Integer)entry0.getKey() >= this.minChannelRange &&
              (Integer)entry0.getKey() <= this.maxChannelRange) {
            this.presets.addPreset((String)entry0.getValue(),
                                   (Integer)entry0.getKey());
          }
        }
      }
    } else {
      int int0 = this.twoWay ? 100 : 300;
      if (this.isHighTier) {
        int0 = 800;
      }

      std::unordered_map map1 =
          ZomboidRadio.getInstance().GetChannelList("Emergency");
      if (map1 != nullptr) {
        for (Entry entry1 : map1.entrySet()) {
          if ((Integer)entry1.getKey() >= this.minChannelRange &&
              (Integer)entry1.getKey() <= this.maxChannelRange &&
              Rand.Next(1000) < int0) {
            this.presets.addPreset((String)entry1.getValue(),
                                   (Integer)entry1.getKey());
          }
        }
      }

      int0 = this.twoWay ? 100 : 800;
      map1 = ZomboidRadio.getInstance().GetChannelList("Radio");
      if (map1 != nullptr) {
        for (Entry entry2 : map1.entrySet()) {
          if ((Integer)entry2.getKey() >= this.minChannelRange &&
              (Integer)entry2.getKey() <= this.maxChannelRange &&
              Rand.Next(1000) < int0) {
            this.presets.addPreset((String)entry2.getValue(),
                                   (Integer)entry2.getKey());
          }
        }
      }

      if (this.twoWay) {
        map1 = ZomboidRadio.getInstance().GetChannelList("Amateur");
        if (map1 != nullptr) {
          for (Entry entry3 : map1.entrySet()) {
            if ((Integer)entry3.getKey() >= this.minChannelRange &&
                (Integer)entry3.getKey() <= this.maxChannelRange &&
                Rand.Next(1000) < int0) {
              this.presets.addPreset((String)entry3.getValue(),
                                     (Integer)entry3.getKey());
            }
          }
        }
      }

      if (this.isHighTier) {
        map1 = ZomboidRadio.getInstance().GetChannelList("Military");
        if (map1 != nullptr) {
          for (Entry entry4 : map1.entrySet()) {
            if ((Integer)entry4.getKey() >= this.minChannelRange &&
                (Integer)entry4.getKey() <= this.maxChannelRange &&
                Rand.Next(1000) < 10) {
              this.presets.addPreset((String)entry4.getValue(),
                                     (Integer)entry4.getKey());
            }
          }
        }
      }
    }
  }

  void *clone() {
    DeviceData deviceData0 = (DeviceData)super.clone();
    deviceData0.setDevicePresets((DevicePresets)this.presets.clone());
    deviceData0.setParent(nullptr);
    return deviceData0;
  }

  DeviceData getClone() {
    DeviceData deviceData0;
    try {
      deviceData0 = (DeviceData)this.clone();
    } catch (Exception exception) {
      System.out.println(exception.getMessage());
      deviceData0 = std::make_unique<DeviceData>();
    }

    return deviceData0;
  }

  WaveSignalDevice getParent() { return this.parent; }

  void setParent(WaveSignalDevice p) { this.parent = p; }

  DevicePresets getDevicePresets() { return this.presets; }

  void setDevicePresets(DevicePresets p) {
    if (p == nullptr) {
      p = std::make_unique<DevicePresets>();
    }

    this.presets = p;
  }

  void cloneDevicePresets(DevicePresets p) {
    this.presets.clearPresets();
    if (p != nullptr) {
      for (int int0 = 0; int0 < p.presets.size(); int0++) {
        PresetEntry presetEntry = p.presets.get(int0);
        this.presets.addPreset(presetEntry.name, presetEntry.frequency);
      }
    }
  }

  int getMinChannelRange() { return this.minChannelRange; }

  void setMinChannelRange(int i) {
    this.minChannelRange = i >= 200 && i <= 1000000 ? i : 200;
  }

  int getMaxChannelRange() { return this.maxChannelRange; }

  void setMaxChannelRange(int i) {
    this.maxChannelRange = i >= 200 && i <= 1000000 ? i : 1000000;
  }

  bool getIsHighTier() { return this.isHighTier; }

  void setIsHighTier(bool b) { this.isHighTier = b; }

  bool getIsBatteryPowered() { return this.isBatteryPowered; }

  void setIsBatteryPowered(bool b) { this.isBatteryPowered = b; }

  bool getHasBattery() { return this.hasBattery; }

  void setHasBattery(bool b) { this.hasBattery = b; }

  void addBattery(DrainableComboItem bat) {
    if (!this.hasBattery && bat != nullptr &&
        bat.getFullType() == "Base.Battery")) {
        ItemContainer container = bat.getContainer();
        if (container != nullptr) {
          if (container.getType() == "floor") && bat.getWorldItem() != nullptr && bat.getWorldItem().getSquare() != nullptr) {
              bat.getWorldItem().getSquare().transmitRemoveItemFromSquare(
                  bat.getWorldItem());
              bat.getWorldItem().getSquare().getWorldObjects().remove(
                  bat.getWorldItem());
              bat.getWorldItem().getSquare().chunk.recalcHashCodeObjects();
              bat.getWorldItem().getSquare().getObjects().remove(
                  bat.getWorldItem());
              bat.setWorldItem(nullptr);
            }

          this.powerDelta = bat.getDelta();
          container.DoRemoveItem(bat);
          this.hasBattery = true;
          this.transmitDeviceDataState((short)2);
        }
      }
  }

  InventoryItem getBattery(ItemContainer inventory) {
    if (this.hasBattery) {
      DrainableComboItem drainableComboItem =
          (DrainableComboItem)InventoryItemFactory.CreateItem("Base.Battery");
      drainableComboItem.setDelta(this.powerDelta);
      this.powerDelta = 0.0F;
      inventory.AddItem(drainableComboItem);
      this.hasBattery = false;
      this.transmitDeviceDataState((short)2);
      return drainableComboItem;
    } else {
      return null;
    }
  }

  void transmitBattryChange() { this.transmitDeviceDataState((short)2); }

  void addHeadphones(InventoryItem headphones) {
    if (this.headphoneType < 0 &&
            (headphones.getFullType() == "Base.Headphones") ||
        headphones.getFullType() == "Base.Earbuds"))) {
        ItemContainer container = headphones.getContainer();
        if (container != nullptr) {
          if (container.getType() == "floor") && headphones.getWorldItem() != nullptr && headphones.getWorldItem().getSquare() != nullptr) {
              headphones.getWorldItem()
                  .getSquare()
                  .transmitRemoveItemFromSquare(headphones.getWorldItem());
              headphones.getWorldItem().getSquare().getWorldObjects().remove(
                  headphones.getWorldItem());
              headphones.getWorldItem()
                  .getSquare()
                  .chunk.recalcHashCodeObjects();
              headphones.getWorldItem().getSquare().getObjects().remove(
                  headphones.getWorldItem());
              headphones.setWorldItem(nullptr);
            }

          int int0 = headphones.getFullType().equals("Base.Headphones") ? 0 : 1;
          container.DoRemoveItem(headphones);
          this.setHeadphoneType(int0);
          this.transmitDeviceDataState((short)6);
        }
      }
  }

  InventoryItem getHeadphones(ItemContainer inventory) {
    if (this.headphoneType >= 0) {
      InventoryItem item = null;
      if (this.headphoneType == 0) {
        item = InventoryItemFactory.CreateItem("Base.Headphones");
      } else if (this.headphoneType == 1) {
        item = InventoryItemFactory.CreateItem("Base.Earbuds");
      }

      if (item != nullptr) {
        inventory.AddItem(item);
      }

      this.setHeadphoneType(-1);
      this.transmitDeviceDataState((short)6);
    }

    return null;
  }

  int getMicRange() { return this.micRange; }

  void setMicRange(int i) { this.micRange = i; }

  bool getMicIsMuted() { return this.micIsMuted; }

  void setMicIsMuted(bool b) {
    this.micIsMuted = b;
    if (this.getParent() != nullptr && this.getParent() instanceof
        Radio && ((Radio)this.getParent()).getEquipParent() != nullptr &&
            ((Radio)this.getParent()).getEquipParent()
            instanceof IsoPlayer) {
      IsoPlayer player = (IsoPlayer)((Radio)this.getParent()).getEquipParent();
      player.updateEquippedRadioFreq();
    }
  }

  int getHeadphoneType() { return this.headphoneType; }

  void setHeadphoneType(int i) { this.headphoneType = i; }

  float getBaseVolumeRange() { return this.baseVolumeRange; }

  void setBaseVolumeRange(float f) { this.baseVolumeRange = f; }

  float getDeviceVolume() { return this.deviceVolume; }

  void setDeviceVolume(float f) {
    this.deviceVolume = f < 0.0F ? 0.0F : (f > 1.0F ? 1.0F : f);
    this.transmitDeviceDataState((short)4);
  }

  void setDeviceVolumeRaw(float f) {
    this.deviceVolume = f < 0.0F ? 0.0F : (f > 1.0F ? 1.0F : f);
  }

  bool getIsTelevision() { return this.isTelevision; }

  void setIsTelevision(bool b) { this.isTelevision = b; }

  std::string getDeviceName() { return this.deviceName; }

  void setDeviceName(const std::string &name) { this.deviceName = name; }

  bool getIsTwoWay() { return this.twoWay; }

  void setIsTwoWay(bool b) { this.twoWay = b; }

  int getTransmitRange() { return this.transmitRange; }

  void setTransmitRange(int range) {
    this.transmitRange = range > 0 ? range : 0;
  }

  bool getIsPortable() { return this.isPortable; }

  void setIsPortable(bool b) { this.isPortable = b; }

  bool getIsTurnedOn() { return this.isTurnedOn; }

  void setIsTurnedOn(bool b) {
    if (this.canBePoweredHere()) {
      if (this.isBatteryPowered && !(this.powerDelta > 0.0F)) {
        this.isTurnedOn = false;
      } else {
        this.isTurnedOn = b;
      }

      this.playSoundSend("RadioButton", false);
      this.transmitDeviceDataState((short)0);
    } else if (this.isTurnedOn) {
      this.isTurnedOn = false;
      this.playSoundSend("RadioButton", false);
      this.transmitDeviceDataState((short)0);
    }

    if (this.getParent() != nullptr && this.getParent() instanceof
        Radio && ((Radio)this.getParent()).getEquipParent() != nullptr &&
            ((Radio)this.getParent()).getEquipParent()
            instanceof IsoPlayer) {
      IsoPlayer player = (IsoPlayer)((Radio)this.getParent()).getEquipParent();
      player.updateEquippedRadioFreq();
    }

    IsoGenerator.updateGenerator(this.getParent().getSquare());
  }

  void setTurnedOnRaw(bool b) {
    this.isTurnedOn = b;
    if (this.getParent() != nullptr && this.getParent() instanceof
        Radio && ((Radio)this.getParent()).getEquipParent() != nullptr &&
            ((Radio)this.getParent()).getEquipParent()
            instanceof IsoPlayer) {
      IsoPlayer player = (IsoPlayer)((Radio)this.getParent()).getEquipParent();
      player.updateEquippedRadioFreq();
    }
  }

  bool canBePoweredHere() {
    if (this.isBatteryPowered) {
      return true;
    } else if (this.parent instanceof VehiclePart part) {
      return part.isInventoryItemUninstalled() ? false : part.hasDevicePower();
    } else {
      bool boolean0 = false;
      if (IsoWorld.instance.isHydroPowerOn()) {
        boolean0 = true;
      }

      if (this.parent == nullptr || this.parent.getSquare() == nullptr) {
        boolean0 = false;
      } else if (this.parent.getSquare().haveElectricity()) {
        boolean0 = true;
      } else if (this.parent.getSquare().getRoom() == nullptr) {
        boolean0 = false;
      }

      return boolean0;
    }
  }

  void setRandomChannel() {
    if (this.presets != nullptr && this.presets.getPresets().size() > 0) {
      int int0 = Rand.Next(0, this.presets.getPresets().size());
      this.channel = this.presets.getPresets().get(int0).getFrequency();
    } else {
      this.channel = Rand.Next(this.minChannelRange, this.maxChannelRange);
      this.channel = this.channel - this.channel % 200;
    }
  }

  int getChannel() { return this.channel; }

  void setChannel(int c) { this.setChannel(c, true); }

  void setChannel(int chan, bool setislistening) {
    if (chan >= this.minChannelRange && chan <= this.maxChannelRange) {
      this.channel = chan;
      this.playSoundSend("RadioButton", false);
      if (this.isTelevision) {
        this.playSoundSend("TelevisionZap", true);
      } else {
        this.playSoundSend("RadioZap", true);
      }

      if (this.radioLoopSound > 0L) {
        this.emitter.stopSound(this.radioLoopSound);
        this.radioLoopSound = 0L;
      }

      this.transmitDeviceDataState((short)1);
      if (setislistening) {
        this.TriggerPlayerListening(true);
      }
    }
  }

  void setChannelRaw(int chan) { this.channel = chan; }

  float getUseDelta() { return this.useDelta; }

  void setUseDelta(float f) { this.useDelta = f / 60.0F; }

  float getPower() { return this.powerDelta; }

  void setPower(float p) {
    if (p > 1.0F) {
      p = 1.0F;
    }

    if (p < 0.0F) {
      p = 0.0F;
    }

    this.powerDelta = p;
  }

  void setInitialPower() {
    this.lastMinuteStamp = this.gameTime.getMinutesStamp();
    this.setPower(this.powerDelta -
                  this.useDelta * (float)this.lastMinuteStamp);
  }

  void TriggerPlayerListening(bool listening) {
    if (this.isTurnedOn) {
      ZomboidRadio.getInstance().PlayerListensChannel(this.channel, true,
                                                      this.isTelevision);
    }
  }

  void playSoundSend(const std::string &soundname, bool useDeviceVolume) {
    this.playSound(soundname,
                   useDeviceVolume ? this.deviceVolume * 0.4F : 0.05F, true);
  }

  void playSoundLocal(const std::string &soundname, bool useDeviceVolume) {
    this.playSound(soundname,
                   useDeviceVolume ? this.deviceVolume * 0.4F : 0.05F, false);
  }

  void playSound(const std::string &soundname, float volume, bool transmit) {
    if (!GameServer.bServer) {
      this.setEmitterAndPos();
      if (this.emitter != nullptr) {
        long long0 =
            transmit ? this.emitter.playSound(soundname)
                     : this.emitter.playSoundImpl(soundname, (IsoObject)null);
        this.emitter.setVolume(long0, volume);
      }
    }
  }

  void cleanSoundsAndEmitter() {
    if (this.emitter != nullptr) {
      this.emitter.stopAll();
      IsoWorld.instance.returnOwnershipOfEmitter(this.emitter);
      this.emitter = nullptr;
      this.radioLoopSound = 0L;
    }
  }

  void setEmitterAndPos() {
    void *object = null;
    if (this.parent != nullptr && this.parent instanceof IsoObject) {
      object = (IsoObject)this.parent;
    } else if (this.parent != nullptr && this.parent instanceof Radio) {
      object = IsoPlayer.getInstance();
    }

    if (object != nullptr) {
      if (this.emitter == nullptr) {
        this.emitter = IsoWorld.instance.getFreeEmitter(
            ((IsoObject)object).getX() + 0.5F,
            ((IsoObject)object).getY() + 0.5F, (int)((IsoObject)object).getZ());
        IsoWorld.instance.takeOwnershipOfEmitter(this.emitter);
      } else {
        this.emitter.setPos(((IsoObject)object).getX() + 0.5F,
                            ((IsoObject)object).getY() + 0.5F,
                            (int)((IsoObject)object).getZ());
      }

      if (this.radioLoopSound != 0L) {
        this.emitter.setVolume(this.radioLoopSound, this.deviceVolume * 0.4F);
      }
    }
  }

  void updateEmitter() {
    if (!GameServer.bServer) {
      if (!this.isTurnedOn) {
        if (this.emitter != nullptr && this.emitter.isPlaying("RadioButton")) {
          if (this.radioLoopSound > 0L) {
            this.emitter.stopSound(this.radioLoopSound);
          }

          this.setEmitterAndPos();
          this.emitter.tick();
        } else {
          this.cleanSoundsAndEmitter();
        }
      } else {
        this.setEmitterAndPos();
        if (this.emitter != nullptr) {
          if (this.signalCounter > 0.0F &&
              !this.emitter.isPlaying("RadioTalk")) {
            if (this.radioLoopSound > 0L) {
              this.emitter.stopSound(this.radioLoopSound);
            }

            this.radioLoopSound =
                this.emitter.playSoundImpl("RadioTalk", (IsoObject) nullptr);
            this.emitter.setVolume(this.radioLoopSound,
                                   this.deviceVolume * 0.4F);
          }

          std::string string =
              !this.isTelevision ? "RadioStatic" : "TelevisionTestBeep";
          if (this.radioLoopSound == 0L ||
              this.signalCounter <= 0.0F && !this.emitter.isPlaying(string)) {
            if (this.radioLoopSound > 0L) {
              this.emitter.stopSound(this.radioLoopSound);
              if (this.isTelevision) {
                this.playSoundLocal("TelevisionZap", true);
              } else {
                this.playSoundLocal("RadioZap", true);
              }
            }

            this.radioLoopSound =
                this.emitter.playSoundImpl(string, (IsoObject) nullptr);
            this.emitter.setVolume(this.radioLoopSound,
                                   this.deviceVolume * 0.4F);
          }

          this.emitter.tick();
        }
      }
    }
  }

  BaseSoundEmitter getEmitter() { return this.emitter; }

  void update(bool isIso, bool playerInRange) {
    if (this.lastMinuteStamp == -1L) {
      this.lastMinuteStamp = this.gameTime.getMinutesStamp();
    }

    if (this.gameTime.getMinutesStamp() > this.lastMinuteStamp) {
      long long0 = this.gameTime.getMinutesStamp() - this.lastMinuteStamp;
      this.lastMinuteStamp = this.gameTime.getMinutesStamp();
      this.listenCnt = (int)(this.listenCnt + long0);
      if (this.listenCnt >= 10) {
        this.listenCnt = 0;
      }

      if (!GameServer.bServer && this.isTurnedOn && playerInRange &&
          (this.listenCnt == 0 || this.listenCnt == 5)) {
        this.TriggerPlayerListening(true);
      }

      if (this.isTurnedOn && this.isBatteryPowered && this.powerDelta > 0.0F) {
        float float0 = this.powerDelta - this.powerDelta % 0.01F;
        this.setPower(this.powerDelta - this.useDelta * (float)long0);
        if (this.listenCnt == 0 || this.powerDelta == 0.0F ||
            this.powerDelta < float0) {
          if (isIso && GameServer.bServer) {
            this.transmitDeviceDataStateServer((short)3, nullptr);
          } else if (!isIso && GameClient.bClient) {
            this.transmitDeviceDataState((short)3);
          }
        }
      }
    }

    if (this.isTurnedOn && (this.isBatteryPowered && this.powerDelta <= 0.0F ||
                            !this.canBePoweredHere())) {
      this.isTurnedOn = false;
      if (isIso && GameServer.bServer) {
        this.transmitDeviceDataStateServer((short)0, nullptr);
      } else if (!isIso && GameClient.bClient) {
        this.transmitDeviceDataState((short)0);
      }
    }

    this.updateMediaPlaying();
    this.updateEmitter();
    this.updateSimple();
  }

  void updateSimple() {
    if (this.voipCounter >= 0.0F) {
      this.voipCounter =
          this.voipCounter - 1.25F * GameTime.getInstance().getMultiplier();
    }

    if (this.signalCounter >= 0.0F) {
      this.signalCounter =
          this.signalCounter - 1.25F * GameTime.getInstance().getMultiplier();
    }

    if (this.soundCounter >= 0.0F) {
      this.soundCounter =
          (float)(this.soundCounter -
                  1.25 * GameTime.getInstance().getMultiplier());
    }

    if (this.signalCounter <= 0.0F && this.voipCounter <= 0.0F &&
        this.lastRecordedDistance >= 0) {
      this.lastRecordedDistance = -1;
    }

    this.updateStaticSounds();
    if (GameClient.bClient) {
      this.updateEmitter();
    }

    if (this.doTriggerWorldSound && this.soundCounter <= 0.0F) {
      if (this.isTurnedOn && this.deviceVolume > 0.0F &&
          (!this.isInventoryDevice() || this.headphoneType < 0) &&
          (!GameClient.bClient && !GameServer.bServer ||
           GameClient.bClient && this.isInventoryDevice() ||
           GameServer.bServer && !this.isInventoryDevice())) {
        void *object = null;
        if (this.parent != nullptr && this.parent instanceof IsoObject) {
          object = (IsoObject)this.parent;
        } else if (this.parent != nullptr && this.parent instanceof Radio) {
          object = IsoPlayer.getInstance();
        } else if (this.parent instanceof VehiclePart) {
          object = ((VehiclePart)this.parent).getVehicle();
        }

        if (object != nullptr) {
          int int0 = (int)(100.0F * this.deviceVolume);
          int int1 = this.getDeviceSoundVolumeRange();
          WorldSoundManager.instance.addSoundRepeating(
              object, (int)((IsoObject)object).getX(),
              (int)((IsoObject)object).getY(), (int)((IsoObject)object).getZ(),
              int1, int0, int0 > 50);
        }
      }

      this.doTriggerWorldSound = false;
      this.soundCounter = 300 + Rand.Next(0, 300);
    }
  }

  void updateStaticSounds() {
    if (this.isTurnedOn) {
      float float0 = GameTime.getInstance().getMultiplier();
      this.nextStaticSound -= float0;
      if (this.nextStaticSound <= 0.0F) {
        if (this.parent != nullptr && this.signalCounter <= 0.0F &&
            !this.isNoTransmit() && !this.isPlayingMedia()) {
          this.parent.AddDeviceText(
              ZomboidRadio.getInstance().getRandomBzztFzzt(), 1.0F, 1.0F, 1.0F,
              nullptr, nullptr, -1);
          this.doTriggerWorldSound = true;
        }

        this.setNextStaticSound();
      }
    }
  }

  void setNextStaticSound() {
    this.nextStaticSound = Rand.Next(250.0F, 1500.0F);
  }

  int getDeviceVolumeRange() {
    return 5 + (int)(this.baseVolumeRange * this.deviceVolume);
  }

  int getDeviceSoundVolumeRange() {
    if (this.isInventoryDevice()) {
      Radio radio = (Radio)this.getParent();
      return radio.getPlayer() != nullptr &&
                     radio.getPlayer().getSquare() != nullptr &&
                     radio.getPlayer().getSquare().getRoom() != nullptr
                 ? 3 + (int)(this.baseVolumeRange * 0.4F * this.deviceVolume)
                 : 5 + (int)(this.baseVolumeRange * this.deviceVolume);
    } else if (this.isIsoDevice()) {
      IsoWaveSignal waveSignal = (IsoWaveSignal)this.getParent();
      return waveSignal.getSquare() != nullptr &&
                     waveSignal.getSquare().getRoom() != nullptr
                 ? 3 + (int)(this.baseVolumeRange * 0.5F * this.deviceVolume)
                 : 5 + (int)(this.baseVolumeRange * 0.75F * this.deviceVolume);
    } else {
      return 5 + (int)(this.baseVolumeRange / 2.0F * this.deviceVolume);
    }
  }

  void doReceiveSignal(int distance) {
    if (this.isTurnedOn) {
      this.lastRecordedDistance = distance;
      if (this.deviceVolume > 0.0F &&
          (this.isIsoDevice() || this.headphoneType < 0)) {
        void *object = null;
        if (this.parent != nullptr && this.parent instanceof IsoObject) {
          object = (IsoObject)this.parent;
        } else if (this.parent != nullptr && this.parent instanceof Radio) {
          object = IsoPlayer.getInstance();
        } else if (this.parent instanceof VehiclePart) {
          object = ((VehiclePart)this.parent).getVehicle();
        }

        if (object != nullptr && this.soundCounter <= 0.0F) {
          int int0 = (int)(100.0F * this.deviceVolume);
          int int1 = this.getDeviceSoundVolumeRange();
          WorldSoundManager.instance.addSound(
              object, (int)((IsoObject)object).getX(),
              (int)((IsoObject)object).getY(), (int)((IsoObject)object).getZ(),
              int1, int0, int0 > 50);
          this.soundCounter = 120.0F;
        }
      }

      this.signalCounter = 300.0F;
      this.doTriggerWorldSound = true;
      this.setNextStaticSound();
    }
  }

  void doReceiveMPSignal(float distance) {
    this.lastRecordedDistance = (int)distance;
    this.voipCounter = 10.0F;
  }

  bool isReceivingSignal() {
    return this.signalCounter > 0.0F || this.voipCounter > 0.0F;
  }

  int getLastRecordedDistance() { return this.lastRecordedDistance; }

  bool isIsoDevice() {
    return this.getParent() != nullptr && this.getParent() instanceof
        IsoWaveSignal;
  }

  bool isInventoryDevice() {
    return this.getParent() != nullptr && this.getParent() instanceof Radio;
  }

  bool isVehicleDevice() { return this.getParent() instanceof VehiclePart; }

  void transmitPresets() { this.transmitDeviceDataState((short)5); }

  void transmitDeviceDataState(short short0) {
    if (GameClient.bClient) {
      try {
        VoiceManager.getInstance().UpdateChannelsRoaming(GameClient.connection);
        this.sendDeviceDataStatePacket(GameClient.connection, short0);
      } catch (Exception exception) {
        System.out.print(exception.getMessage());
      }
    }
  }

  void transmitDeviceDataStateServer(short short0,
                                     UdpConnection udpConnection1) {
    if (GameServer.bServer) {
      try {
        for (int int0 = 0; int0 < GameServer.udpEngine.connections.size();
             int0++) {
          UdpConnection udpConnection0 =
              GameServer.udpEngine.connections.get(int0);
          if (udpConnection1 == nullptr || udpConnection1 != udpConnection0) {
            this.sendDeviceDataStatePacket(udpConnection0, short0);
          }
        }
      } catch (Exception exception) {
        System.out.print(exception.getMessage());
      }
    }
  }

  void sendDeviceDataStatePacket(UdpConnection udpConnection, short short0) {
    ByteBufferWriter byteBufferWriter = udpConnection.startPacket();
    PacketTypes.PacketType.RadioDeviceDataState.doPacket(byteBufferWriter);
    bool boolean0 = false;
    if (this.isIsoDevice()) {
      IsoWaveSignal waveSignal = (IsoWaveSignal)this.getParent();
      IsoGridSquare square = waveSignal.getSquare();
      if (square != nullptr) {
        byteBufferWriter.putByte((byte)1);
        byteBufferWriter.putInt(square.getX());
        byteBufferWriter.putInt(square.getY());
        byteBufferWriter.putInt(square.getZ());
        byteBufferWriter.putInt(square.getObjects().indexOf(waveSignal));
        boolean0 = true;
      }
    } else if (this.isInventoryDevice()) {
      Radio radio = (Radio)this.getParent();
      IsoPlayer player = null;
      if (radio.getEquipParent() != nullptr && radio.getEquipParent() instanceof
          IsoPlayer) {
        player = (IsoPlayer)radio.getEquipParent();
      }

      if (player != nullptr) {
        byteBufferWriter.putByte((byte)0);
        if (GameServer.bServer) {
          byteBufferWriter.putShort(player != nullptr ? player.OnlineID : -1);
        } else {
          byteBufferWriter.putByte((byte)player.PlayerIndex);
        }

        if (player.getPrimaryHandItem() == radio) {
          byteBufferWriter.putByte((byte)1);
        } else if (player.getSecondaryHandItem() == radio) {
          byteBufferWriter.putByte((byte)2);
        } else {
          byteBufferWriter.putByte((byte)0);
        }

        boolean0 = true;
      }
    } else if (this.isVehicleDevice()) {
      VehiclePart part = (VehiclePart)this.getParent();
      byteBufferWriter.putByte((byte)2);
      byteBufferWriter.putShort(part.getVehicle().VehicleID);
      byteBufferWriter.putShort((short)part.getIndex());
      boolean0 = true;
    }

    if (boolean0) {
      byteBufferWriter.putShort(short0);
      switch (short0) {
      case 0:
        byteBufferWriter.putByte((byte)(this.isTurnedOn ? 1 : 0));
        break;
      case 1:
        byteBufferWriter.putInt(this.channel);
        break;
      case 2:
        byteBufferWriter.putByte((byte)(this.hasBattery ? 1 : 0));
        byteBufferWriter.putFloat(this.powerDelta);
        break;
      case 3:
        byteBufferWriter.putFloat(this.powerDelta);
        break;
      case 4:
        byteBufferWriter.putFloat(this.deviceVolume);
        break;
      case 5:
        byteBufferWriter.putInt(this.presets.getPresets().size());

        for (PresetEntry presetEntry : this.presets.getPresets()) {
          GameWindow.WriteString(byteBufferWriter.bb, presetEntry.getName());
          byteBufferWriter.putInt(presetEntry.getFrequency());
        }
        break;
      case 6:
        byteBufferWriter.putInt(this.headphoneType);
        break;
      case 7:
        byteBufferWriter.putShort(this.mediaIndex);
        byteBufferWriter.putByte((byte)(this.mediaItem != nullptr ? 1 : 0));
        if (this.mediaItem != nullptr) {
          GameWindow.WriteString(byteBufferWriter.bb, this.mediaItem);
        }
        break;
      case 8:
        if (GameServer.bServer) {
          byteBufferWriter.putShort(this.mediaIndex);
          byteBufferWriter.putByte((byte)(this.mediaItem != nullptr ? 1 : 0));
          if (this.mediaItem != nullptr) {
            GameWindow.WriteString(byteBufferWriter.bb, this.mediaItem);
          }
        }
      case 9:
      default:
        break;
      case 10:
        if (GameServer.bServer) {
          byteBufferWriter.putShort(this.mediaIndex);
          byteBufferWriter.putInt(this.mediaLineIndex);
        }
      }

      PacketTypes.PacketType.RadioDeviceDataState.send(udpConnection);
    } else {
      udpConnection.cancelPacket();
    }
  }

  void receiveDeviceDataStatePacket(ByteBuffer bb,
                                    UdpConnection ignoreConnection) {
    if (GameClient.bClient || GameServer.bServer) {
      bool boolean0 = GameServer.bServer;
      bool boolean1 = this.isIsoDevice() || this.isVehicleDevice();
      short short0 = bb.getShort();
      switch (short0) {
      case 0:
        if (boolean0 && boolean1) {
          this.setIsTurnedOn(bb.get() == 1);
        } else {
          this.isTurnedOn = bb.get() == 1;
        }

        if (boolean0) {
          this.transmitDeviceDataStateServer(
              short0, !boolean1 ? ignoreConnection : nullptr);
        }
        break;
      case 1:
        int int1 = bb.getInt();
        if (boolean0 && boolean1) {
          this.setChannel(int1);
        } else {
          this.channel = int1;
        }

        if (boolean0) {
          this.transmitDeviceDataStateServer(
              short0, !boolean1 ? ignoreConnection : nullptr);
        }
        break;
      case 2:
        bool boolean2 = bb.get() == 1;
        float float0 = bb.getFloat();
        if (boolean0 && boolean1) {
          this.hasBattery = boolean2;
          this.setPower(float0);
        } else {
          this.hasBattery = boolean2;
          this.powerDelta = float0;
        }

        if (boolean0) {
          this.transmitDeviceDataStateServer(
              short0, !boolean1 ? ignoreConnection : nullptr);
        }
        break;
      case 3:
        float float1 = bb.getFloat();
        if (boolean0 && boolean1) {
          this.setPower(float1);
        } else {
          this.powerDelta = float1;
        }

        if (boolean0) {
          this.transmitDeviceDataStateServer(
              short0, !boolean1 ? ignoreConnection : nullptr);
        }
        break;
      case 4:
        float float2 = bb.getFloat();
        if (boolean0 && boolean1) {
          this.setDeviceVolume(float2);
        } else {
          this.deviceVolume = float2;
        }

        if (boolean0) {
          this.transmitDeviceDataStateServer(
              short0, !boolean1 ? ignoreConnection : nullptr);
        }
        break;
      case 5:
        int int2 = bb.getInt();

        for (int int3 = 0; int3 < int2; int3++) {
          std::string string3 = GameWindow.ReadString(bb);
          int int4 = bb.getInt();
          if (int3 < this.presets.getPresets().size()) {
            PresetEntry presetEntry = this.presets.getPresets().get(int3);
            if (!presetEntry.getName() == string3) || presetEntry.getFrequency() != int4) {
                presetEntry.setName(string3);
                presetEntry.setFrequency(int4);
              }
          } else {
            this.presets.addPreset(string3, int4);
          }
        }

        if (boolean0) {
          this.transmitDeviceDataStateServer(
              (short)5, !boolean1 ? ignoreConnection : nullptr);
        }
        break;
      case 6:
        this.headphoneType = bb.getInt();
        if (boolean0) {
          this.transmitDeviceDataStateServer(
              short0, !boolean1 ? ignoreConnection : nullptr);
        }
        break;
      case 7:
        this.mediaIndex = bb.getShort();
        if (bb.get() == 1) {
          this.mediaItem = GameWindow.ReadString(bb);
        }

        if (boolean0) {
          this.transmitDeviceDataStateServer(
              short0, !boolean1 ? ignoreConnection : nullptr);
        }
        break;
      case 8:
        if (GameServer.bServer) {
          this.StartPlayMedia();
        } else {
          this.mediaIndex = bb.getShort();
          if (bb.get() == 1) {
            this.mediaItem = GameWindow.ReadString(bb);
          }

          this.isPlayingMedia = true;
          this.televisionMediaSwitch();
        }
        break;
      case 9:
        if (GameServer.bServer) {
          this.StopPlayMedia();
        } else {
          this.isPlayingMedia = false;
          this.televisionMediaSwitch();
        }
        break;
      case 10:
        if (GameClient.bClient) {
          this.mediaIndex = bb.getShort();
          int int0 = bb.getInt();
          MediaData mediaData = this.getMediaData();
          if (mediaData != nullptr && int0 >= 0 &&
              int0 < mediaData.getLineCount()) {
            MediaData.MediaLineData mediaLineData = mediaData.getLine(int0);
            std::string string0 = mediaLineData.getTranslatedText();
            Color color = mediaLineData.getColor();
            std::string string1 = mediaLineData.getTextGuid();
            std::string string2 = mediaLineData.getCodes();
            this.parent.AddDeviceText(string0, color.r, color.g, color.b,
                                      string1, string2, 0);
          }
        }
      }
    }
  }

  void save(ByteBuffer output, bool net) {
    GameWindow.WriteString(output, this.deviceName);
    output.put((byte)(this.twoWay ? 1 : 0));
    output.putInt(this.transmitRange);
    output.putInt(this.micRange);
    output.put((byte)(this.micIsMuted ? 1 : 0));
    output.putFloat(this.baseVolumeRange);
    output.putFloat(this.deviceVolume);
    output.put((byte)(this.isPortable ? 1 : 0));
    output.put((byte)(this.isTelevision ? 1 : 0));
    output.put((byte)(this.isHighTier ? 1 : 0));
    output.put((byte)(this.isTurnedOn ? 1 : 0));
    output.putInt(this.channel);
    output.putInt(this.minChannelRange);
    output.putInt(this.maxChannelRange);
    output.put((byte)(this.isBatteryPowered ? 1 : 0));
    output.put((byte)(this.hasBattery ? 1 : 0));
    output.putFloat(this.powerDelta);
    output.putFloat(this.useDelta);
    output.putInt(this.headphoneType);
    if (this.presets != nullptr) {
      output.put((byte)1);
      this.presets.save(output, net);
    } else {
      output.put((byte)0);
    }

    output.putShort(this.mediaIndex);
    output.put(this.mediaType);
    output.put((byte)(this.mediaItem != nullptr ? 1 : 0));
    if (this.mediaItem != nullptr) {
      GameWindow.WriteString(output, this.mediaItem);
    }

    output.put((byte)(this.noTransmit ? 1 : 0));
  }

  void load(ByteBuffer input, int WorldVersion, bool net) {
    if (this.presets == nullptr) {
      this.presets = std::make_unique<DevicePresets>();
    }

    if (WorldVersion >= 69) {
      this.deviceName = GameWindow.ReadString(input);
      this.twoWay = input.get() == 1;
      this.transmitRange = input.getInt();
      this.micRange = input.getInt();
      this.micIsMuted = input.get() == 1;
      this.baseVolumeRange = input.getFloat();
      this.deviceVolume = input.getFloat();
      this.isPortable = input.get() == 1;
      this.isTelevision = input.get() == 1;
      this.isHighTier = input.get() == 1;
      this.isTurnedOn = input.get() == 1;
      this.channel = input.getInt();
      this.minChannelRange = input.getInt();
      this.maxChannelRange = input.getInt();
      this.isBatteryPowered = input.get() == 1;
      this.hasBattery = input.get() == 1;
      this.powerDelta = input.getFloat();
      this.useDelta = input.getFloat();
      this.headphoneType = input.getInt();
      if (input.get() == 1) {
        this.presets.load(input, WorldVersion, net);
      }
    }

    if (WorldVersion >= 181) {
      this.mediaIndex = input.getShort();
      this.mediaType = input.get();
      if (input.get() == 1) {
        this.mediaItem = GameWindow.ReadString(input);
      }

      this.noTransmit = input.get() == 1;
    }
  }

  bool hasMedia() { return this.mediaIndex >= 0; }

  short getMediaIndex() { return this.mediaIndex; }

  void setMediaIndex(short _mediaIndex) { this.mediaIndex = _mediaIndex; }

  uint8_t getMediaType() { return this.mediaType; }

  void setMediaType(uint8_t _mediaType) { this.mediaType = _mediaType; }

  void addMediaItem(InventoryItem media) {
    if (this.mediaIndex < 0 && media.isRecordedMedia() &&
        media.getMediaType() == this.mediaType) {
      ItemContainer container = media.getContainer();
      if (container != nullptr) {
        this.mediaIndex = media.getRecordedMediaIndex();
        this.mediaItem = media.getFullType();
        ItemUser.RemoveItem(media);
        this.transmitDeviceDataState((short)7);
      }
    }
  }

  InventoryItem removeMediaItem(ItemContainer inventory) {
    if (this.hasMedia()) {
      InventoryItem item = InventoryItemFactory.CreateItem(this.mediaItem);
      item.setRecordedMediaIndex(this.mediaIndex);
      inventory.AddItem(item);
      this.mediaIndex = -1;
      this.mediaItem = nullptr;
      if (this.isPlayingMedia()) {
        this.StopPlayMedia();
      }

      this.transmitDeviceDataState((short)7);
      return item;
    } else {
      return null;
    }
  }

  bool isPlayingMedia() { return this.isPlayingMedia; }

  void StartPlayMedia() {
    if (GameClient.bClient) {
      this.transmitDeviceDataState((short)8);
    } else if (!this.isPlayingMedia() && this.getIsTurnedOn() &&
               this.hasMedia()) {
      this.playingMedia =
          ZomboidRadio.getInstance().getRecordedMedia().getMediaDataFromIndex(
              this.mediaIndex);
      if (this.playingMedia != nullptr) {
        this.isPlayingMedia = true;
        this.mediaLineIndex = 0;
        this.prePlayingMedia();
        if (GameServer.bServer) {
          this.transmitDeviceDataStateServer((short)8, nullptr);
        }
      }
    }
  }

  void prePlayingMedia() {
    this.lineCounter = 60.0F * this.maxmod * 0.5F;
    this.televisionMediaSwitch();
  }

  void postPlayingMedia() {
    this.isStoppingMedia = true;
    this.stopMediaCounter = 60.0F * this.maxmod * 0.5F;
    this.televisionMediaSwitch();
  }

  void televisionMediaSwitch() {
    if (this.mediaType == 1) {
      ZomboidRadio.getInstance().getRandomBzztFzzt();
      this.parent.AddDeviceText(ZomboidRadio.getInstance().getRandomBzztFzzt(),
                                0.5F, 0.5F, 0.5F, nullptr, nullptr, 0);
      this.playSoundLocal("TelevisionZap", true);
    }
  }

  void StopPlayMedia() {
    if (GameClient.bClient) {
      this.transmitDeviceDataState((short)9);
    } else {
      this.playingMedia = nullptr;
      this.postPlayingMedia();
      if (GameServer.bServer) {
        this.transmitDeviceDataStateServer((short)9, nullptr);
      }
    }
  }

  void updateMediaPlaying() {
    if (!GameClient.bClient) {
      if (this.isStoppingMedia) {
        this.stopMediaCounter = this.stopMediaCounter -
                                1.25F * GameTime.getInstance().getMultiplier();
        if (this.stopMediaCounter <= 0.0F) {
          this.isPlayingMedia = false;
          this.isStoppingMedia = false;
        }
      } else {
        if (this.hasMedia() && this.isPlayingMedia()) {
          if (!this.getIsTurnedOn()) {
            this.StopPlayMedia();
            return;
          }

          if (this.playingMedia != nullptr) {
            this.lineCounter = this.lineCounter -
                               1.25F * GameTime.getInstance().getMultiplier();
            if (this.lineCounter <= 0.0F) {
              MediaData.MediaLineData mediaLineData =
                  this.playingMedia.getLine(this.mediaLineIndex);
              if (mediaLineData != nullptr) {
                std::string string0 = mediaLineData.getTranslatedText();
                Color color = mediaLineData.getColor();
                this.lineCounter = string0.length() / 10.0F * 60.0F;
                if (this.lineCounter < 60.0F * this.minmod) {
                  this.lineCounter = 60.0F * this.minmod;
                } else if (this.lineCounter > 60.0F * this.maxmod) {
                  this.lineCounter = 60.0F * this.maxmod;
                }

                if (GameServer.bServer) {
                  this.currentMediaLine = string0;
                  this.currentMediaColor = color;
                  this.transmitDeviceDataStateServer((short)10, nullptr);
                } else {
                  std::string string1 = mediaLineData.getTextGuid();
                  std::string string2 = mediaLineData.getCodes();
                  this.parent.AddDeviceText(string0, color.r, color.g, color.b,
                                            string1, string2, 0);
                }

                this.mediaLineIndex++;
              } else {
                this.StopPlayMedia();
              }
            }
          }
        }
      }
    }
  }

  MediaData getMediaData() {
    return this.mediaIndex >= 0 ? ZomboidRadio.getInstance()
                                      .getRecordedMedia()
                                      .getMediaDataFromIndex(this.mediaIndex)
                                : nullptr;
  }

  bool isNoTransmit() { return this.noTransmit; }

  void setNoTransmit(bool _noTransmit) { this.noTransmit = _noTransmit; }
}
} // namespace devices
} // namespace radio
} // namespace zombie
