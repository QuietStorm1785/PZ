#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/Talker.h"
#include "zombie/chat/ChatManager.h"
#include "zombie/chat/ChatMessage.h"
#include "zombie/core/properties/PropertyContainer.h"
#include "zombie/interfaces/IUpdater.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/radio/ZomboidRadio.h"
#include "zombie/radio/devices/DeviceData.h"
#include "zombie/radio/devices/WaveSignalDevice.h"
#include "zombie/scripting/objects/Item/Type.h"
#include "zombie/ui/UIFont.h"
#include "zombie/util/StringUtils.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace inventory {
namespace types {


class Radio : public Moveable {
public:
    DeviceData deviceData = nullptr;
    GameTime gameTime;
    int lastMin = 0;
    bool doPowerTick = false;
    int listenCnt = 0;

    public Radio(const std::string& var1, const std::string& var2, const std::string& var3, const std::string& var4) {
      super(var1, var2, var3, var4);
      this.deviceData = std::make_shared<DeviceData>(this);
      this.gameTime = GameTime.getInstance();
      this.canBeDroppedOnFloor = true;
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

    void doReceiveSignal(int var1) {
      if (this.deviceData != nullptr) {
         this.deviceData.doReceiveSignal(var1);
      }
   }

    void AddDeviceText(const std::string& var1, float var2, float var3, float var4, const std::string& var5, const std::string& var6, int var7) {
      if (!ZomboidRadio.isStaticSound(var1)) {
         this.doReceiveSignal(var7);
      }

    IsoPlayer var8 = this.getPlayer();
      if (var8 != nullptr && this.deviceData != nullptr && this.deviceData.getDeviceVolume() > 0.0F && !var8.Traits.Deaf.isSet()) {
         var8.SayRadio(var1, var2, var3, var4, UIFont.Medium, this.deviceData.getDeviceVolumeRange(), this.deviceData.getChannel(), "radio");
         if (var6 != nullptr) {
            LuaEventManager.triggerEvent("OnDeviceText", var5, var6, -1, -1, -1, var1, this);
         }
      }
   }

    void AddDeviceText(ChatMessage var1, float var2, float var3, float var4, const std::string& var5, const std::string& var6, int var7) {
      if (!ZomboidRadio.isStaticSound(var1.getText())) {
         this.doReceiveSignal(var7);
      }

    IsoPlayer var8 = this.getPlayer();
      if (var8 != nullptr && this.deviceData != nullptr && this.deviceData.getDeviceVolume() > 0.0F) {
         ChatManager.getInstance().showRadioMessage(var1);
         if (var6 != nullptr) {
            LuaEventManager.triggerEvent("OnDeviceText", var5, var6, -1, -1, -1, var1, this);
         }
      }
   }

    bool HasPlayerInRange() {
    return false;
   }

    bool ReadFromWorldSprite(const std::string& var1) {
      if (StringUtils.isNullOrWhitespace(var1)) {
    return false;
      } else {
    IsoSprite var2 = (IsoSprite)IsoSpriteManager.instance.NamedMap.get(var1);
         if (var2 != nullptr) {
    PropertyContainer var3 = var2.getProperties();
            if (var3.Is("IsMoveAble")) {
               if (var3.Is("CustomItem")) {
                  this.customItem = var3.Val("CustomItem");
               }

               this.worldSprite = var1;
    return true;
            }
         }

         System.out.println("Warning: Radio worldsprite not valid, sprite = " + (var1 == nullptr ? "nullptr" : var1));
    return false;
      }
   }

    int getSaveType() {
      return Type.Radio.ordinal();
   }

    float getDelta() {
      return this.deviceData != nullptr ? this.deviceData.getPower() : 0.0F;
   }

    void setDelta(float var1) {
      if (this.deviceData != nullptr) {
         this.deviceData.setPower(var1);
      }
   }

    IsoGridSquare getSquare() {
      return this.container != nullptr && this.container.parent != nullptr && this.container.dynamic_cast<IsoPlayer*>(parent) != nullptr ? this.container.parent.getSquare() : nullptr;
   }

    float getX() {
    IsoGridSquare var1 = this.getSquare();
    return var1 = = nullptr ? 0.0F : var1.getX();
   }

    float getY() {
    IsoGridSquare var1 = this.getSquare();
    return var1 = = nullptr ? 0.0F : var1.getY();
   }

    float getZ() {
    IsoGridSquare var1 = this.getSquare();
    return var1 = = nullptr ? 0.0F : var1.getZ();
   }

    IsoPlayer getPlayer() {
      return this.container != nullptr && this.container.parent != nullptr && this.container.dynamic_cast<IsoPlayer*>(parent) != nullptr ? (IsoPlayer)this.container.parent : nullptr;
   }

    void render() {
   }

    void renderlast() {
   }

    void update() {
      if (this.deviceData != nullptr) {
         if (!GameServer.bServer && !GameClient.bClient || GameClient.bClient) {
    bool var1 = false;

            for (int var2 = 0; var2 < IsoPlayer.numPlayers; var2++) {
    IsoPlayer var3 = IsoPlayer.players[var2];
               if (var3 != nullptr && var3.getEquipedRadio() == this) {
                  var1 = true;
                  break;
               }
            }

            if (var1) {
               this.deviceData.update(false, true);
            } else {
               this.deviceData.cleanSoundsAndEmitter();
            }
         }
      }
   }

    bool IsSpeaking() {
    return false;
   }

    void Say(const std::string& var1) {
   }

    std::string getSayLine() {
    return nullptr;
   }

    std::string getTalkerType() {
      return "radio";
   }

    void save(ByteBuffer var1, bool var2) {
      super.save(var1, var2);
      if (this.deviceData != nullptr) {
         var1.put((byte)1);
         this.deviceData.save(var1, var2);
      } else {
         var1.put((byte)0);
      }
   }

    void load(ByteBuffer var1, int var2) {
      super.load(var1, var2);
      if (this.deviceData == nullptr) {
         this.deviceData = std::make_shared<DeviceData>(this);
      }

      if (var1.get() == 1) {
         this.deviceData.load(var1, var2, false);
      }

      this.deviceData.setParent(this);
   }
}
} // namespace types
} // namespace inventory
} // namespace zombie
