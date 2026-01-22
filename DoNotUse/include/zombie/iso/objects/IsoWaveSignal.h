#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/Talker.h"
#include "zombie/chat/ChatElement.h"
#include "zombie/chat/ChatElementOwner.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/properties/PropertyContainer.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/inventory/types/Radio.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoLightSource.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/radio/ZomboidRadio.h"
#include "zombie/radio/devices/DeviceData.h"
#include "zombie/radio/devices/PresetEntry.h"
#include "zombie/radio/devices/WaveSignalDevice.h"
#include "zombie/ui/UIFont.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {
namespace objects {


class IsoWaveSignal : public IsoObject {
public:
    IsoLightSource lightSource = nullptr;
    bool lightWasRemoved = false;
    int lightSourceRadius = 4;
    float nextLightUpdate = 0.0F;
    float lightUpdateCnt = 0.0F;
    DeviceData deviceData = nullptr;
    bool displayRange = false;
    bool hasPlayerInRange = false;
    GameTime gameTime;
    ChatElement chatElement;
    std::string talkerType = "device";
   protected static Map<std::string, DeviceData> deviceDataCache = std::make_unique<std::unordered_map<>>();

    public IsoWaveSignal(IsoCell var1) {
      super(var1);
      this.init(true);
   }

    public IsoWaveSignal(IsoCell var1, IsoGridSquare var2, IsoSprite var3) {
      super(var1, var2, var3);
      this.init(false);
   }

    void init(bool var1) {
      this.chatElement = std::make_shared<ChatElement>(this, 5, this.talkerType);
      this.gameTime = GameTime.getInstance();
      if (!var1) {
         if (this.sprite != nullptr && this.sprite.getProperties() != nullptr) {
    PropertyContainer var2 = this.sprite.getProperties();
            if (var2.Is("CustomItem") && var2.Val("CustomItem") != nullptr) {
               this.deviceData = this.cloneDeviceDataFromItem(var2.Val("CustomItem"));
            }
         }

         if (!GameClient.bClient && this.deviceData != nullptr) {
            this.deviceData.generatePresets();
            this.deviceData.setDeviceVolume(Rand.Next(0.1F, 1.0F));
            this.deviceData.setRandomChannel();
            if (Rand.Next(100) <= 35 && !"Tutorial" == Core.GameMode)) {
               this.deviceData.setTurnedOnRaw(true);
               if (dynamic_cast<IsoRadio*>(this) != nullptr) {
                  this.deviceData.setInitialPower();
                  if (this.deviceData.getIsBatteryPowered() && this.deviceData.getPower() <= 0.0F) {
                     this.deviceData.setTurnedOnRaw(false);
                  }
               }
            }
         }
      }

      if (this.deviceData == nullptr) {
         this.deviceData = std::make_shared<DeviceData>(this);
      }

      this.deviceData.setParent(this);
   }

    DeviceData cloneDeviceDataFromItem(const std::string& var1) {
      if (var1 != nullptr) {
         if (deviceDataCache.containsKey(var1) && deviceDataCache.get(var1) != nullptr) {
            return deviceDataCache.get(var1).getClone();
         }

    InventoryItem var2 = InventoryItemFactory.CreateItem(var1);
         if (var2 != nullptr && dynamic_cast<Radio*>(var2) != nullptr) {
    DeviceData var3 = ((Radio)var2).getDeviceData();
            if (var3 != nullptr) {
               deviceDataCache.put(var1, var3);
               return var3.getClone();
            }
         }
      }

    return nullptr;
   }

    bool hasChatToDisplay() {
      return this.chatElement.getHasChatToDisplay();
   }

    bool HasPlayerInRange() {
      return this.hasPlayerInRange;
   }

    float getDelta() {
      return this.deviceData != nullptr ? this.deviceData.getPower() : 0.0F;
   }

    void setDelta(float var1) {
      if (this.deviceData != nullptr) {
         this.deviceData.setPower(var1);
      }
   }

    DeviceData getDeviceData() {
      return this.deviceData;
   }

    void setDeviceData(DeviceData var1) {
      if (var1 == nullptr) {
         var1 = std::make_shared<DeviceData>(this);
      }

      this.deviceData = var1;
      this.deviceData.setParent(this);
   }

    bool IsSpeaking() {
      return this.chatElement.IsSpeaking();
   }

    std::string getTalkerType() {
      return this.chatElement.getTalkerType();
   }

    void setTalkerType(const std::string& var1) {
      this.talkerType = var1 == nullptr ? "" : var1;
      this.chatElement.setTalkerType(this.talkerType);
   }

    std::string getSayLine() {
      return this.chatElement.getSayLine();
   }

    void Say(const std::string& var1) {
      this.AddDeviceText(var1, 1.0F, 1.0F, 1.0F, nullptr, nullptr, -1, false);
   }

    void AddDeviceText(const std::string& var1, float var2, float var3, float var4, const std::string& var5, const std::string& var6, int var7) {
      this.AddDeviceText(var1, var2, var3, var4, var5, var6, var7, true);
   }

    void AddDeviceText(const std::string& var1, int var2, int var3, int var4, const std::string& var5, const std::string& var6, int var7) {
      this.AddDeviceText(var1, var2 / 255.0F, var3 / 255.0F, var4 / 255.0F, var5, var6, var7, true);
   }

    void AddDeviceText(const std::string& var1, int var2, int var3, int var4, const std::string& var5, const std::string& var6, int var7, bool var8) {
      this.AddDeviceText(var1, var2 / 255.0F, var3 / 255.0F, var4 / 255.0F, var5, var6, var7, var8);
   }

    void AddDeviceText(const std::string& var1, float var2, float var3, float var4, const std::string& var5, const std::string& var6, int var7, bool var8) {
      if (this.deviceData != nullptr && this.deviceData.getIsTurnedOn()) {
         if (!ZomboidRadio.isStaticSound(var1)) {
            this.deviceData.doReceiveSignal(var7);
         }

         if (this.deviceData.getDeviceVolume() > 0.0F) {
            this.chatElement
               .addChatLine(var1, var2, var3, var4, UIFont.Medium, this.deviceData.getDeviceVolumeRange(), "default", true, true, true, true, true, true);
            if (var6 != nullptr) {
               LuaEventManager.triggerEvent("OnDeviceText", var5, var6, this.getX(), this.getY(), this.getZ(), var1, this);
            }
         }
      }
   }

    void renderlast() {
      if (this.chatElement.getHasChatToDisplay()) {
         if (this.getDeviceData() != nullptr && !this.getDeviceData().getIsTurnedOn()) {
            this.chatElement.clear(IsoCamera.frameState.playerIndex);
            return;
         }

    float var1 = IsoUtils.XToScreen(this.getX(), this.getY(), this.getZ(), 0);
    float var2 = IsoUtils.YToScreen(this.getX(), this.getY(), this.getZ(), 0);
         var1 = var1 - IsoCamera.getOffX() - this.offsetX;
         var2 = var2 - IsoCamera.getOffY() - this.offsetY;
         var1 += 32 * Core.TileScale;
         var2 += 50 * Core.TileScale;
         var1 /= Core.getInstance().getZoom(IsoPlayer.getPlayerIndex());
         var2 /= Core.getInstance().getZoom(IsoPlayer.getPlayerIndex());
         this.chatElement.renderBatched(IsoPlayer.getPlayerIndex(), (int)var1, (int)var2);
      }
   }

    void renderlastold2() {
      if (this.chatElement.getHasChatToDisplay()) {
    float var1 = IsoUtils.XToScreen(this.getX(), this.getY(), this.getZ(), 0);
    float var2 = IsoUtils.YToScreen(this.getX(), this.getY(), this.getZ(), 0);
         var1 = var1 - IsoCamera.getOffX() - this.offsetX;
         var2 = var2 - IsoCamera.getOffY() - this.offsetY;
         var1 += 28.0F;
         var2 += 180.0F;
         var1 /= Core.getInstance().getZoom(IsoPlayer.getPlayerIndex());
         var2 /= Core.getInstance().getZoom(IsoPlayer.getPlayerIndex());
         var1 += IsoCamera.getScreenLeft(IsoPlayer.getPlayerIndex());
         var2 += IsoCamera.getScreenTop(IsoPlayer.getPlayerIndex());
         this.chatElement.renderBatched(IsoPlayer.getPlayerIndex(), (int)var1, (int)var2);
      }
   }

    bool playerWithinBounds(IsoPlayer var1, float var2) {
      return var1 == nullptr
         ? false
         : (var1.getX() > this.getX() - var2 || var1.getX() < this.getX() + var2) && (var1.getY() > this.getY() - var2 || var1.getY() < this.getY() + var2);
   }

    void update() {
      if (this.deviceData != nullptr) {
         if ((GameServer.bServer || GameClient.bClient) && !GameServer.bServer) {
            this.deviceData.updateSimple();
         } else {
            this.deviceData.update(true, this.hasPlayerInRange);
         }

         if (!GameServer.bServer) {
            this.hasPlayerInRange = false;
            if (this.deviceData.getIsTurnedOn()) {
    IsoPlayer var1 = IsoPlayer.getInstance();
               if (this.playerWithinBounds(var1, this.deviceData.getDeviceVolumeRange() * 0.6F)) {
                  this.hasPlayerInRange = true;
               }

               this.updateLightSource();
            } else {
               this.removeLightSourceFromWorld();
            }

            this.chatElement.setHistoryRange(this.deviceData.getDeviceVolumeRange() * 0.6F);
            this.chatElement.update();
         } else {
            this.hasPlayerInRange = false;
         }
      }
   }

    void updateLightSource() {
   }

    void removeLightSourceFromWorld() {
      if (this.lightSource != nullptr) {
         IsoWorld.instance.CurrentCell.removeLamppost(this.lightSource);
         this.lightSource = nullptr;
      }
   }

    void load(ByteBuffer var1, int var2, bool var3) {
      super.load(var1, var2, var3);
      if (this.deviceData == nullptr) {
         this.deviceData = std::make_shared<DeviceData>(this);
      }

      if (var1.get() == 1) {
         this.deviceData.load(var1, var2, true);
      }

      this.deviceData.setParent(this);
   }

    void save(ByteBuffer var1, bool var2) {
      super.save(var1, var2);
      if (this.deviceData != nullptr) {
         var1.put((byte)1);
         this.deviceData.save(var1, true);
      } else {
         var1.put((byte)0);
      }
   }

    void addToWorld() {
      if (!GameServer.bServer) {
         ZomboidRadio.getInstance().RegisterDevice(this);
      }

      if (this.getCell() != nullptr) {
         this.getCell().addToStaticUpdaterObjectList(this);
      }

      super.addToWorld();
   }

    void removeFromWorld() {
      if (!GameServer.bServer) {
         ZomboidRadio.getInstance().UnRegisterDevice(this);
      }

      this.removeLightSourceFromWorld();
      this.lightSource = nullptr;
      if (this.deviceData != nullptr) {
         this.deviceData.cleanSoundsAndEmitter();
      }

      super.removeFromWorld();
   }

    void removeFromSquare() {
      super.removeFromSquare();
      this.square = nullptr;
   }

    void saveState(ByteBuffer var1) {
      if (this.deviceData != nullptr) {
    std::vector var2 = this.deviceData.getDevicePresets().getPresets();
         var1.putInt(var2.size());

         for (int var3 = 0; var3 < var2.size(); var3++) {
    PresetEntry var4 = (PresetEntry)var2.get(var3);
            GameWindow.WriteString(var1, var4.getName());
            var1.putInt(var4.getFrequency());
         }

         var1.put((byte)(this.deviceData.getIsTurnedOn() ? 1 : 0));
         var1.putInt(this.deviceData.getChannel());
         var1.putFloat(this.deviceData.getDeviceVolume());
      }
   }

    void loadState(ByteBuffer var1) {
    std::vector var2 = this.deviceData.getDevicePresets().getPresets();
    int var3 = var1.getInt();

      for (int var4 = 0; var4 < var3; var4++) {
    std::string var5 = GameWindow.ReadString(var1);
    int var6 = var1.getInt();
         if (var4 < var2.size()) {
    PresetEntry var7 = (PresetEntry)var2.get(var4);
            var7.setName(var5);
            var7.setFrequency(var6);
         } else {
            this.deviceData.getDevicePresets().addPreset(var5, var6);
         }
      }

      while (var2.size() > var3) {
         this.deviceData.getDevicePresets().removePreset(var3);
      }

      this.deviceData.setTurnedOnRaw(var1.get() == 1);
      this.deviceData.setChannelRaw(var1.getInt());
      this.deviceData.setDeviceVolumeRaw(var1.getFloat());
   }

    ChatElement getChatElement() {
      return this.chatElement;
   }

    static void Reset() {
      deviceDataCache.clear();
   }
}
} // namespace objects
} // namespace iso
} // namespace zombie
