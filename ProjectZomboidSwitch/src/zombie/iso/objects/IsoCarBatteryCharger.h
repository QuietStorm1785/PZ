#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/core/Core.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/skinnedmodel/model/WorldItemModelDrawer.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/types/DrainableComboItem.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/sprite/IsoDirectionFrame.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/PacketTypes/PacketType.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {
namespace objects {


class IsoCarBatteryCharger : public IsoObject {
public:
    InventoryItem item;
    InventoryItem battery;
    bool activated;
    float lastUpdate = -1.0F;
    float chargeRate = 0.16666667F;
    IsoSprite chargerSprite;
    IsoSprite batterySprite;
    long sound = 0L;

    public IsoCarBatteryCharger(IsoCell var1) {
      super(var1);
   }

    public IsoCarBatteryCharger(InventoryItem var1, IsoCell var2, IsoGridSquare var3) {
      super(var2, var3, (IsoSprite)nullptr);
      if (var1 == nullptr) {
         throw NullPointerException("item is nullptr");
      } else {
         this.item = var1;
      }
   }

    std::string getObjectName() {
      return "IsoCarBatteryCharger";
   }

    void load(ByteBuffer var1, int var2, bool var3) {
      super.load(var1, var2, var3);
      if (var1.get() == 1) {
         try {
            this.item = InventoryItem.loadItem(var1, var2);
         } catch (Exception var6) {
            var6.printStackTrace();
         }
      }

      if (var1.get() == 1) {
         try {
            this.battery = InventoryItem.loadItem(var1, var2);
         } catch (Exception var5) {
            var5.printStackTrace();
         }
      }

      this.activated = var1.get() == 1;
      this.lastUpdate = var1.getFloat();
      this.chargeRate = var1.getFloat();
   }

    void save(ByteBuffer var1, bool var2) {
      super.save(var1, var2);
      if (this.item == nullptr) {
    assert false;

         var1.put((byte)0);
      } else {
         var1.put((byte)1);
         this.item.saveWithSize(var1, false);
      }

      if (this.battery == nullptr) {
         var1.put((byte)0);
      } else {
         var1.put((byte)1);
         this.battery.saveWithSize(var1, false);
      }

      var1.put((byte)(this.activated ? 1 : 0));
      var1.putFloat(this.lastUpdate);
      var1.putFloat(this.chargeRate);
   }

    void addToWorld() {
      super.addToWorld();
      this.getCell().addToProcessIsoObject(this);
   }

    void removeFromWorld() {
      this.stopChargingSound();
      super.removeFromWorld();
   }

    void update() {
      super.update();
      if (!(this.dynamic_cast<DrainableComboItem*>(battery) != nullptr)) {
         this.battery = nullptr;
      }

      if (this.battery == nullptr) {
         this.lastUpdate = -1.0F;
         this.activated = false;
         this.stopChargingSound();
      } else {
    bool var1 = this.square != nullptr && (this.square.haveElectricity() || IsoWorld.instance.isHydroPowerOn() && this.square.getRoom() != nullptr);
         if (!var1) {
            this.activated = false;
         }

         if (!this.activated) {
            this.lastUpdate = -1.0F;
            this.stopChargingSound();
         } else {
            this.startChargingSound();
    DrainableComboItem var2 = (DrainableComboItem)this.battery;
            if (!(var2.getUsedDelta() >= 1.0F)) {
    float var3 = (float)GameTime.getInstance().getWorldAgeHours();
               if (this.lastUpdate < 0.0F) {
                  this.lastUpdate = var3;
               }

               if (this.lastUpdate > var3) {
                  this.lastUpdate = var3;
               }

    float var4 = var3 - this.lastUpdate;
               if (var4 > 0.0F) {
                  var2.setUsedDelta(Math.min(1.0F, var2.getUsedDelta() + this.chargeRate * var4));
                  this.lastUpdate = var3;
               }
            }
         }
      }
   }

    void render(float var1, float var2, float var3, ColorInfo var4, bool var5, bool var6, Shader var7) {
      this.chargerSprite = this.configureSprite(this.item, this.chargerSprite);
      if (this.chargerSprite.CurrentAnim != nullptr && !this.chargerSprite.CurrentAnim.Frames.empty()) {
    Texture var8 = ((IsoDirectionFrame)this.chargerSprite.CurrentAnim.Frames.get(0)).getTexture(this.dir);
         if (var8 != nullptr) {
    float var9 = var8.getWidthOrig() * this.chargerSprite.def.getScaleX() / 2.0F;
    float var10 = var8.getHeightOrig() * this.chargerSprite.def.getScaleY() * 3.0F / 4.0F;
            this.offsetX = this.offsetY = 0.0F;
            this.setAlpha(IsoCamera.frameState.playerIndex, 1.0F);
    float var11 = 0.5F;
    float var12 = 0.5F;
    float var13 = 0.0F;
            this.sx = 0.0F;
            this.item.setWorldZRotation(315);
            if (!WorldItemModelDrawer.renderMain(this.getItem(), this.getSquare(), this.getX() + var11, this.getY() + var12, this.getZ() + var13, -1.0F)) {
               this.chargerSprite
                  .render(
                     this,
                     var1 + var11,
                     var2 + var12,
                     var3 + var13,
                     this.dir,
                     this.offsetX + var9 + 8 * Core.TileScale,
                     this.offsetY + var10 + 4 * Core.TileScale,
                     var4,
                     true
                  );
            }

            if (this.battery != nullptr) {
               this.batterySprite = this.configureSprite(this.battery, this.batterySprite);
               if (this.batterySprite != nullptr && this.batterySprite.CurrentAnim != nullptr && !this.batterySprite.CurrentAnim.Frames.empty()) {
                  this.sx = 0.0F;
                  this.getBattery().setWorldZRotation(90);
                  if (!WorldItemModelDrawer.renderMain(
                     this.getBattery(), this.getSquare(), this.getX() + 0.75F, this.getY() + 0.75F, this.getZ() + var13, -1.0F
                  )) {
                     this.batterySprite
                        .render(
                           this,
                           var1 + var11,
                           var2 + var12,
                           var3 + var13,
                           this.dir,
                           this.offsetX + var9 - 8.0F + Core.TileScale,
                           this.offsetY + var10 - 4 * Core.TileScale,
                           var4,
                           true
                        );
                  }
               }
            }
         }
      }
   }

    void renderObjectPicker(float var1, float var2, float var3, ColorInfo var4) {
   }

    IsoSprite configureSprite(InventoryItem var1, IsoSprite var2) {
    std::string var4 = var1.getWorldTexture();

      try {
    Texture var3 = Texture.getSharedTexture(var4);
         if (var3 == nullptr) {
            var4 = var1.getTex().getName();
         }
      } catch (Exception var7) {
         var4 = "media/inventory/world/WItem_Sack.png";
      }

    Texture var8 = Texture.getSharedTexture(var4);
    bool var5 = false;
      if (var2 == nullptr) {
         var2 = IsoSprite.CreateSprite(IsoSpriteManager.instance);
      }

      if (var2.CurrentAnim == nullptr) {
         var2.LoadFramesNoDirPageSimple(var4);
         var2.CurrentAnim.name = var4;
         var5 = true;
      } else if (!var4 == var2.CurrentAnim.name)) {
         var2.ReplaceCurrentAnimFrames(var4);
         var2.CurrentAnim.name = var4;
         var5 = true;
      }

      if (var5) {
         if (var1.getScriptItem() == nullptr) {
            var2.def.scaleAspect(var8.getWidthOrig(), var8.getHeightOrig(), 16 * Core.TileScale, 16 * Core.TileScale);
         } else if (this.battery != nullptr && this.battery.getScriptItem() != nullptr) {
    float var10001 = Core.TileScale;
    float var6 = this.battery.getScriptItem().ScaleWorldIcon * (var10001 / 2.0F);
            var2.def.setScale(var6, var6);
         }
      }

    return var2;
   }

    void syncIsoObjectSend(ByteBufferWriter var1) {
    uint8_t var2 = (byte)this.getObjectIndex();
      var1.putInt(this.square.getX());
      var1.putInt(this.square.getY());
      var1.putInt(this.square.getZ());
      var1.putByte(var2);
      var1.putByte((byte)1);
      var1.putByte((byte)0);
      if (this.battery == nullptr) {
         var1.putByte((byte)0);
      } else {
         var1.putByte((byte)1);

         try {
            this.battery.saveWithSize(var1.bb, false);
         } catch (IOException var4) {
            var4.printStackTrace();
         }
      }

      var1.putBoolean(this.activated);
      var1.putFloat(this.chargeRate);
   }

    void syncIsoObject(bool var1, uint8_t var2, UdpConnection var3, ByteBuffer var4) {
      if (GameClient.bClient && !var1) {
    ByteBufferWriter var10 = GameClient.connection.startPacket();
         PacketType.SyncIsoObject.doPacket(var10);
         this.syncIsoObjectSend(var10);
         PacketType.SyncIsoObject.send(GameClient.connection);
      } else if (GameServer.bServer && !var1) {
         for (UdpConnection var11 : GameServer.udpEngine.connections) {
    ByteBufferWriter var12 = var11.startPacket();
            PacketType.SyncIsoObject.doPacket(var12);
            this.syncIsoObjectSend(var12);
            PacketType.SyncIsoObject.send(var11);
         }
      } else if (var1) {
         if (var4.get() == 1) {
            try {
               this.battery = InventoryItem.loadItem(var4, 195);
            } catch (Exception var8) {
               var8.printStackTrace();
            }
         } else {
            this.battery = nullptr;
         }

         this.activated = var4.get() == 1;
         this.chargeRate = var4.getFloat();
         if (GameServer.bServer) {
            for (UdpConnection var6 : GameServer.udpEngine.connections) {
               if (var3 != nullptr && var6 != var3) {
    ByteBufferWriter var7 = var6.startPacket();
                  PacketType.SyncIsoObject.doPacket(var7);
                  this.syncIsoObjectSend(var7);
                  PacketType.SyncIsoObject.send(var6);
               }
            }
         }
      }
   }

    void sync() {
      this.syncIsoObject(false, (byte)0, nullptr, nullptr);
   }

    InventoryItem getItem() {
      return this.item;
   }

    InventoryItem getBattery() {
      return this.battery;
   }

    void setBattery(InventoryItem var1) {
      if (var1 != nullptr) {
         if (!(dynamic_cast<DrainableComboItem*>(var1) != nullptr)) {
            throw IllegalArgumentException("battery isn't DrainableComboItem");
         }

         if (this.battery != nullptr) {
            throw IllegalStateException("battery already inserted");
         }
      }

      this.battery = var1;
   }

    bool isActivated() {
      return this.activated;
   }

    void setActivated(bool var1) {
      this.activated = var1;
   }

    float getChargeRate() {
      return this.chargeRate;
   }

    void setChargeRate(float var1) {
      if (var1 <= 0.0F) {
         throw IllegalArgumentException("chargeRate <= 0.0f");
      } else {
         this.chargeRate = var1;
      }
   }

    void startChargingSound() {
      if (!GameServer.bServer) {
         if (this.getObjectIndex() != -1) {
            if (this.sound != -1L) {
               if (this.emitter == nullptr) {
                  this.emitter = IsoWorld.instance.getFreeEmitter(this.square.x + 0.5F, this.square.y + 0.5F, this.square.z);
                  IsoWorld.instance.takeOwnershipOfEmitter(this.emitter);
               }

               if (!this.emitter.isPlaying(this.sound)) {
                  this.sound = this.emitter.playSound("CarBatteryChargerRunning");
                  if (this.sound == 0L) {
                     this.sound = -1L;
                  }
               }

               this.emitter.tick();
            }
         }
      }
   }

    void stopChargingSound() {
      if (!GameServer.bServer) {
         if (this.emitter != nullptr) {
            this.emitter.stopOrTriggerSound(this.sound);
            this.sound = 0L;
            IsoWorld.instance.returnOwnershipOfEmitter(this.emitter);
            this.emitter = nullptr;
         }
      }
   }
}
} // namespace objects
} // namespace iso
} // namespace zombie
