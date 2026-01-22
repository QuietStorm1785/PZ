#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/SandboxOptions.h"
#include "zombie/SystemDisabler.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/core/Color.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/inventory/types/DrainableComboItem.h"
#include "zombie/inventory/types/Moveable.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoLightSource.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoRoomLight.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/areas/IsoRoom.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/PacketTypes/PacketType.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {
namespace objects {


class IsoLightSwitch : public IsoObject {
public:
    bool Activated = false;
   public const std::vector<IsoLightSource> lights = std::make_unique<std::vector<>>();
    bool lightRoom = false;
    int RoomID = -1;
    bool bStreetLight = false;
    bool canBeModified = false;
    bool useBattery = false;
    bool hasBattery = false;
    std::string bulbItem = "Base.LightBulb";
    float power = 0.0F;
    float delta = 2.5E-4F;
    float primaryR = 1.0F;
    float primaryG = 1.0F;
    float primaryB = 1.0F;
    long lastMinuteStamp = -1L;
    int bulbBurnMinutes = -1;
    int lastMin = 0;
    int nextBreakUpdate = 60;

    std::string getObjectName() {
      return "LightSwitch";
   }

    public IsoLightSwitch(IsoCell var1) {
      super(var1);
   }

    public IsoLightSwitch(IsoCell var1, IsoGridSquare var2, IsoSprite var3, int var4) {
      super(var1, var2, var3);
      this.RoomID = var4;
      if (var3 != nullptr && var3.getProperties().Is("lightR")) {
         if (var3.getProperties().Is("IsMoveAble")) {
            this.canBeModified = true;
         }

         this.primaryR = float.parseFloat(var3.getProperties().Val("lightR")) / 255.0F;
         this.primaryG = float.parseFloat(var3.getProperties().Val("lightG")) / 255.0F;
         this.primaryB = float.parseFloat(var3.getProperties().Val("lightB")) / 255.0F;
      } else {
         this.lightRoom = true;
      }

      this.bStreetLight = var3 != nullptr && var3.getProperties().Is("streetlight");
    IsoRoom var5 = this.square.getRoom();
      if (var5 != nullptr && this.lightRoom) {
         if (!var2.haveElectricity() && !IsoWorld.instance.isHydroPowerOn()) {
            var5.def.bLightsActive = false;
         }

         this.Activated = var5.def.bLightsActive;
         var5.lightSwitches.push_back(this);
      } else {
         this.Activated = true;
      }
   }

    void addLightSourceFromSprite() {
      if (this.sprite != nullptr && this.sprite.getProperties().Is("lightR")) {
    float var1 = float.parseFloat(this.sprite.getProperties().Val("lightR")) / 255.0F;
    float var2 = float.parseFloat(this.sprite.getProperties().Val("lightG")) / 255.0F;
    float var3 = float.parseFloat(this.sprite.getProperties().Val("lightB")) / 255.0F;
         this.Activated = false;
         this.setActive(true, true);
    int var4 = 10;
         if (this.sprite.getProperties().Is("LightRadius") && int.parseInt(this.sprite.getProperties().Val("LightRadius")) > 0) {
            var4 = int.parseInt(this.sprite.getProperties().Val("LightRadius"));
         }

    IsoLightSource var5 = std::make_shared<IsoLightSource>(this.square.getX(), this.square.getY(), this.square.getZ(), var1, var2, var3, var4);
         var5.bActive = this.Activated;
         var5.bHydroPowered = true;
         var5.switches.push_back(this);
         this.lights.push_back(var5);
      }
   }

    bool getCanBeModified() {
      return this.canBeModified;
   }

    float getPower() {
      return this.power;
   }

    void setPower(float var1) {
      this.power = var1;
   }

    void setDelta(float var1) {
      this.delta = var1;
   }

    float getDelta() {
      return this.delta;
   }

    void setUseBattery(bool var1) {
      this.setActive(false);
      this.useBattery = var1;
      if (GameClient.bClient) {
         this.syncCustomizedSettings(nullptr);
      }
   }

    bool getUseBattery() {
      return this.useBattery;
   }

    bool getHasBattery() {
      return this.hasBattery;
   }

    void setHasBatteryRaw(bool var1) {
      this.hasBattery = var1;
   }

    void addBattery(IsoGameCharacter var1, InventoryItem var2) {
      if (this.canBeModified && this.useBattery && !this.hasBattery && var2 != nullptr && var2.getFullType() == "Base.Battery")) {
         this.power = ((DrainableComboItem)var2).getUsedDelta();
         this.hasBattery = true;
         var1.removeFromHands(var2);
         var1.getInventory().Remove(var2);
         if (GameClient.bClient) {
            this.syncCustomizedSettings(nullptr);
         }
      }
   }

    DrainableComboItem removeBattery(IsoGameCharacter var1) {
      if (this.canBeModified && this.useBattery && this.hasBattery) {
    DrainableComboItem var2 = (DrainableComboItem)InventoryItemFactory.CreateItem("Base.Battery");
         if (var2 != nullptr) {
            this.hasBattery = false;
            var2.setUsedDelta(this.power >= 0.0F ? this.power : 0.0F);
            this.power = 0.0F;
            this.setActive(false, false, true);
            var1.getInventory().AddItem(var2);
            if (GameClient.bClient) {
               this.syncCustomizedSettings(nullptr);
            }

    return var2;
         }
      }

    return nullptr;
   }

    bool hasLightBulb() {
      return this.bulbItem != nullptr;
   }

    std::string getBulbItem() {
      return this.bulbItem;
   }

    void setBulbItemRaw(const std::string& var1) {
      this.bulbItem = var1;
   }

    void addLightBulb(IsoGameCharacter var1, InventoryItem var2) {
      if (!this.hasLightBulb() && var2 != nullptr && var2.getType().startsWith("LightBulb")) {
    IsoLightSource var3 = this.getPrimaryLight();
         if (var3 != nullptr) {
            this.setPrimaryR(var2.getColorRed());
            this.setPrimaryG(var2.getColorGreen());
            this.setPrimaryB(var2.getColorBlue());
            this.bulbItem = var2.getFullType();
            var1.removeFromHands(var2);
            var1.getInventory().Remove(var2);
            if (GameClient.bClient) {
               this.syncCustomizedSettings(nullptr);
            }
         }
      }
   }

    InventoryItem removeLightBulb(IsoGameCharacter var1) {
    IsoLightSource var2 = this.getPrimaryLight();
      if (var2 != nullptr && this.hasLightBulb()) {
    InventoryItem var3 = InventoryItemFactory.CreateItem(this.bulbItem);
         if (var3 != nullptr) {
            var3.setColorRed(this.getPrimaryR());
            var3.setColorGreen(this.getPrimaryG());
            var3.setColorBlue(this.getPrimaryB());
            var3.setColor(std::make_shared<Color>(var2.r, var2.g, var2.b));
            this.bulbItem = nullptr;
            var1.getInventory().AddItem(var3);
            this.setActive(false, false, true);
            if (GameClient.bClient) {
               this.syncCustomizedSettings(nullptr);
            }

    return var3;
         }
      }

    return nullptr;
   }

    IsoLightSource getPrimaryLight() {
      return this.lights.size() > 0 ? this.lights.get(0) : nullptr;
   }

    float getPrimaryR() {
      return this.getPrimaryLight() != nullptr ? this.getPrimaryLight().r : this.primaryR;
   }

    float getPrimaryG() {
      return this.getPrimaryLight() != nullptr ? this.getPrimaryLight().g : this.primaryG;
   }

    float getPrimaryB() {
      return this.getPrimaryLight() != nullptr ? this.getPrimaryLight().b : this.primaryB;
   }

    void setPrimaryR(float var1) {
      this.primaryR = var1;
      if (this.getPrimaryLight() != nullptr) {
         this.getPrimaryLight().r = var1;
      }
   }

    void setPrimaryG(float var1) {
      this.primaryG = var1;
      if (this.getPrimaryLight() != nullptr) {
         this.getPrimaryLight().g = var1;
      }
   }

    void setPrimaryB(float var1) {
      this.primaryB = var1;
      if (this.getPrimaryLight() != nullptr) {
         this.getPrimaryLight().b = var1;
      }
   }

    void load(ByteBuffer var1, int var2, bool var3) {
      super.load(var1, var2, var3);
      this.lightRoom = var1.get() == 1;
      this.RoomID = var1.getInt();
      this.Activated = var1.get() == 1;
      if (var2 >= 76) {
         this.canBeModified = var1.get() == 1;
         if (this.canBeModified) {
            this.useBattery = var1.get() == 1;
            this.hasBattery = var1.get() == 1;
            if (var1.get() == 1) {
               this.bulbItem = GameWindow.ReadString(var1);
            } else {
               this.bulbItem = nullptr;
            }

            this.power = var1.getFloat();
            this.delta = var1.getFloat();
            this.setPrimaryR(var1.getFloat());
            this.setPrimaryG(var1.getFloat());
            this.setPrimaryB(var1.getFloat());
         }
      }

      if (var2 >= 79) {
         this.lastMinuteStamp = var1.getLong();
         this.bulbBurnMinutes = var1.getInt();
      }

      this.bStreetLight = this.sprite != nullptr && this.sprite.getProperties().Is("streetlight");
      if (this.square != nullptr) {
    IsoRoom var4 = this.square.getRoom();
         if (var4 != nullptr && this.lightRoom) {
            this.Activated = var4.def.bLightsActive;
            var4.lightSwitches.push_back(this);
         } else {
    float var5 = 0.9F;
    float var6 = 0.8F;
    float var7 = 0.7F;
            if (this.sprite != nullptr && this.sprite.getProperties().Is("lightR")) {
               if (var2 >= 76 && this.canBeModified) {
                  var5 = this.primaryR;
                  var6 = this.primaryG;
                  var7 = this.primaryB;
               } else {
                  var5 = float.parseFloat(this.sprite.getProperties().Val("lightR")) / 255.0F;
                  var6 = float.parseFloat(this.sprite.getProperties().Val("lightG")) / 255.0F;
                  var7 = float.parseFloat(this.sprite.getProperties().Val("lightB")) / 255.0F;
                  this.primaryR = var5;
                  this.primaryG = var6;
                  this.primaryB = var7;
               }
            }

    int var8 = 8;
            if (this.sprite.getProperties().Is("LightRadius") && int.parseInt(this.sprite.getProperties().Val("LightRadius")) > 0) {
               var8 = int.parseInt(this.sprite.getProperties().Val("LightRadius"));
            }

    IsoLightSource var9 = std::make_shared<IsoLightSource>((int)this.getX(), (int)this.getY(), (int)this.getZ(), var5, var6, var7, var8);
            var9.bActive = this.Activated;
            var9.bWasActive = var9.bActive;
            var9.bHydroPowered = true;
            var9.switches.push_back(this);
            this.lights.push_back(var9);
         }

         if (SystemDisabler.doObjectStateSyncEnable && GameClient.bClient) {
            GameClient.instance.objectSyncReq.putRequestLoad(this.square);
         }
      }
   }

    void save(ByteBuffer var1, bool var2) {
      super.save(var1, var2);
      var1.put((byte)(this.lightRoom ? 1 : 0));
      var1.putInt(this.RoomID);
      var1.put((byte)(this.Activated ? 1 : 0));
      var1.put((byte)(this.canBeModified ? 1 : 0));
      if (this.canBeModified) {
         var1.put((byte)(this.useBattery ? 1 : 0));
         var1.put((byte)(this.hasBattery ? 1 : 0));
         var1.put((byte)(this.hasLightBulb() ? 1 : 0));
         if (this.hasLightBulb()) {
            GameWindow.WriteString(var1, this.bulbItem);
         }

         var1.putFloat(this.power);
         var1.putFloat(this.delta);
         var1.putFloat(this.getPrimaryR());
         var1.putFloat(this.getPrimaryG());
         var1.putFloat(this.getPrimaryB());
      }

      var1.putLong(this.lastMinuteStamp);
      var1.putInt(this.bulbBurnMinutes);
   }

    bool onMouseLeftClick(int var1, int var2) {
    return false;
   }

    bool canSwitchLight() {
      if (this.bulbItem != nullptr) {
    bool var1 = IsoWorld.instance.isHydroPowerOn();
    bool var2 = var1 ? this.square.getRoom() != nullptr || this.bStreetLight : this.square.haveElectricity();
         if (!var2 && this.getCell() != nullptr) {
            for (int var3 = 0; var3 >= (this.getZ() >= 1.0F ? -1 : 0); var3--) {
               for (int var4 = -1; var4 < 2; var4++) {
                  for (int var5 = -1; var5 < 2; var5++) {
                     if (var4 != 0 || var5 != 0 || var3 != 0) {
    IsoGridSquare var6 = this.getCell().getGridSquare(this.getX() + var4, this.getY() + var5, this.getZ() + var3);
                        if (var6 != nullptr && (var1 && var6.getRoom() != nullptr || var6.haveElectricity())) {
                           var2 = true;
                           break;
                        }
                     }
                  }

                  if (var2) {
                     break;
                  }
               }
            }
         }

         if (!this.useBattery && var2 || this.canBeModified && this.useBattery && this.hasBattery && this.power > 0.0F) {
    return true;
         }
      }

    return false;
   }

    bool setActive(bool var1) {
      return this.setActive(var1, false, false);
   }

    bool setActive(bool var1, bool var2) {
      return this.setActive(var1, var2, false);
   }

    bool setActive(bool var1, bool var2, bool var3) {
      if (this.bulbItem == nullptr) {
         var1 = false;
      }

      if (var1 == this.Activated) {
         return this.Activated;
      } else if (this.square.getRoom() == nullptr && !this.canBeModified) {
         return this.Activated;
      } else {
         if (var3 || this.canSwitchLight()) {
            this.Activated = var1;
            if (!var2) {
               IsoWorld.instance.getFreeEmitter().playSound("LightSwitch", this.square);
               this.switchLight(this.Activated);
               this.syncIsoObject(false, (byte)(this.Activated ? 1 : 0), nullptr);
            }
         }

         return this.Activated;
      }
   }

    bool toggle() {
      return this.setActive(!this.Activated);
   }

    void switchLight(bool var1) {
      if (this.lightRoom && this.square.getRoom() != nullptr) {
         this.square.getRoom().def.bLightsActive = var1;

         for (int var2 = 0; var2 < this.square.getRoom().lightSwitches.size(); var2++) {
            ((IsoLightSwitch)this.square.getRoom().lightSwitches.get(var2)).Activated = var1;
         }

         if (GameServer.bServer) {
    int var5 = this.square.getX() / 300;
    int var3 = this.square.getY() / 300;
    int var4 = this.square.getRoom().def.ID;
            GameServer.sendMetaGrid(var5, var3, var4);
         }
      }

      for (int var6 = 0; var6 < this.lights.size(); var6++) {
    IsoLightSource var7 = this.lights.get(var6);
         var7.bActive = var1;
      }

      IsoGridSquare.RecalcLightTime = -1;
      GameTime.instance.lightSourceUpdate = 100.0F;
      IsoGenerator.updateGenerator(this.getSquare());
   }

    void getCustomSettingsFromItem(InventoryItem var1) {
      if (dynamic_cast<Moveable*>(var1) != nullptr var2 && var2.isLight()) {
         this.useBattery = var2.isLightUseBattery();
         this.hasBattery = var2.isLightHasBattery();
         this.bulbItem = var2.getLightBulbItem();
         this.power = var2.getLightPower();
         this.delta = var2.getLightDelta();
         this.setPrimaryR(var2.getLightR());
         this.setPrimaryG(var2.getLightG());
         this.setPrimaryB(var2.getLightB());
      }
   }

    void setCustomSettingsToItem(InventoryItem var1) {
      if (dynamic_cast<Moveable*>(var1) != nullptr var2) {
         var2.setLightUseBattery(this.useBattery);
         var2.setLightHasBattery(this.hasBattery);
         var2.setLightBulbItem(this.bulbItem);
         var2.setLightPower(this.power);
         var2.setLightDelta(this.delta);
         var2.setLightR(this.primaryR);
         var2.setLightG(this.primaryG);
         var2.setLightB(this.primaryB);
      }
   }

    void syncCustomizedSettings(UdpConnection var1) {
      if (GameClient.bClient) {
         this.writeCustomizedSettingsPacket(GameClient.connection);
      } else if (GameServer.bServer) {
         for (UdpConnection var3 : GameServer.udpEngine.connections) {
            if (var1 == nullptr || var3.getConnectedGUID() != var1.getConnectedGUID()) {
               this.writeCustomizedSettingsPacket(var3);
            }
         }
      }
   }

    void writeCustomizedSettingsPacket(UdpConnection var1) {
      if (var1 != nullptr) {
    ByteBufferWriter var2 = var1.startPacket();
         PacketType.SyncCustomLightSettings.doPacket(var2);
         this.writeLightSwitchObjectHeader(var2, (byte)(this.Activated ? 1 : 0));
         var2.putBoolean(this.canBeModified);
         var2.putBoolean(this.useBattery);
         var2.putBoolean(this.hasBattery);
         var2.putByte((byte)(this.bulbItem != nullptr ? 1 : 0));
         if (this.bulbItem != nullptr) {
            GameWindow.WriteString(var2.bb, this.bulbItem);
         }

         var2.putFloat(this.power);
         var2.putFloat(this.delta);
         var2.putFloat(this.primaryR);
         var2.putFloat(this.primaryG);
         var2.putFloat(this.primaryB);
         PacketType.SyncCustomLightSettings.send(var1);
      }
   }

    void readCustomizedSettingsPacket(ByteBuffer var1) {
      this.Activated = var1.get() == 1;
      this.canBeModified = var1.get() == 1;
      this.useBattery = var1.get() == 1;
      this.hasBattery = var1.get() == 1;
      if (var1.get() == 1) {
         this.bulbItem = GameWindow.ReadString(var1);
      } else {
         this.bulbItem = nullptr;
      }

      this.power = var1.getFloat();
      this.delta = var1.getFloat();
      this.setPrimaryR(var1.getFloat());
      this.setPrimaryG(var1.getFloat());
      this.setPrimaryB(var1.getFloat());
   }

    void receiveSyncCustomizedSettings(ByteBuffer var1, UdpConnection var2) {
      if (GameClient.bClient) {
         this.readCustomizedSettingsPacket(var1);
      } else if (GameServer.bServer) {
         this.readCustomizedSettingsPacket(var1);
         this.syncCustomizedSettings(var2);
      }

      this.switchLight(this.Activated);
   }

    void writeLightSwitchObjectHeader(ByteBufferWriter var1, uint8_t var2) {
      var1.putInt(this.square.getX());
      var1.putInt(this.square.getY());
      var1.putInt(this.square.getZ());
      var1.putByte((byte)this.square.getObjects().indexOf(this));
      var1.putByte(var2);
   }

    void syncIsoObjectSend(ByteBufferWriter var1) {
      var1.putInt(this.square.getX());
      var1.putInt(this.square.getY());
      var1.putInt(this.square.getZ());
    uint8_t var2 = (byte)this.square.getObjects().indexOf(this);
      var1.putByte(var2);
      var1.putByte((byte)1);
      var1.putByte((byte)(this.Activated ? 1 : 0));
   }

    void syncIsoObject(bool var1, uint8_t var2, UdpConnection var3, ByteBuffer var4) {
      this.syncIsoObject(var1, var2, var3);
   }

    void syncIsoObject(bool var1, uint8_t var2, UdpConnection var3) {
      if (this.square == nullptr) {
         System.out.println("ERROR: " + this.getClass().getSimpleName() + " square is nullptr");
      } else if (this.getObjectIndex() == -1) {
         System.out
            .println(
               "ERROR: " + this.getClass().getSimpleName() + " not found on square " + this.square.getX() + "," + this.square.getY() + "," + this.square.getZ()
            );
      } else {
         if (GameClient.bClient && !var1) {
    ByteBufferWriter var8 = GameClient.connection.startPacket();
            PacketType.SyncIsoObject.doPacket(var8);
            this.syncIsoObjectSend(var8);
            PacketType.SyncIsoObject.send(GameClient.connection);
         } else if (var1) {
            if (var2 == 1) {
               this.switchLight(true);
               this.Activated = true;
            } else {
               this.switchLight(false);
               this.Activated = false;
            }

            if (GameServer.bServer) {
               for (UdpConnection var5 : GameServer.udpEngine.connections) {
                  if (var3 != nullptr) {
                     if (var5.getConnectedGUID() != var3.getConnectedGUID()) {
    ByteBufferWriter var6 = var5.startPacket();
                        PacketType.SyncIsoObject.doPacket(var6);
                        this.syncIsoObjectSend(var6);
                        PacketType.SyncIsoObject.send(var5);
                     }
                  } else if (var5.RelevantTo(this.square.x, this.square.y)) {
    ByteBufferWriter var9 = var5.startPacket();
                     PacketType.SyncIsoObject.doPacket(var9);
                     var9.putInt(this.square.getX());
                     var9.putInt(this.square.getY());
                     var9.putInt(this.square.getZ());
    uint8_t var7 = (byte)this.square.getObjects().indexOf(this);
                     if (var7 != -1) {
                        var9.putByte(var7);
                     } else {
                        var9.putByte((byte)this.square.getObjects().size());
                     }

                     var9.putByte((byte)1);
                     var9.putByte((byte)(this.Activated ? 1 : 0));
                     PacketType.SyncIsoObject.send(var5);
                  }
               }
            }
         }
      }
   }

    void update() {
      if (!GameServer.bServer && !GameClient.bClient || GameServer.bServer) {
    bool var1 = false;
         if (!this.Activated) {
            this.lastMinuteStamp = -1L;
         }

         if (!this.lightRoom && this.canBeModified && this.Activated) {
            if (this.lastMinuteStamp == -1L) {
               this.lastMinuteStamp = GameTime.instance.getMinutesStamp();
            }

            if (GameTime.instance.getMinutesStamp() > this.lastMinuteStamp) {
               if (this.bulbBurnMinutes == -1) {
    int var2 = SandboxOptions.instance.getElecShutModifier() * 24 * 60;
                  if (this.lastMinuteStamp < var2) {
                     this.bulbBurnMinutes = (int)this.lastMinuteStamp;
                  } else {
                     this.bulbBurnMinutes = var2;
                  }
               }

    long var13 = GameTime.instance.getMinutesStamp() - this.lastMinuteStamp;
               this.lastMinuteStamp = GameTime.instance.getMinutesStamp();
    bool var4 = false;
    bool var5 = IsoWorld.instance.isHydroPowerOn();
    bool var6 = var5 ? this.square.getRoom() != nullptr : this.square.haveElectricity();
    bool var7 = this.useBattery && this.hasBattery && this.power > 0.0F;
               if (var7 || !this.useBattery && var6) {
                  var4 = true;
               }

    double var8 = SandboxOptions.instance.LightBulbLifespan.getValue();
               if (var8 <= 0.0) {
                  var4 = false;
               }

               if (this.Activated && this.hasLightBulb() && var4) {
                  this.bulbBurnMinutes = (int)(this.bulbBurnMinutes + var13);
               }

               this.nextBreakUpdate = (int)(this.nextBreakUpdate - var13);
               if (this.nextBreakUpdate <= 0) {
                  if (this.Activated && this.hasLightBulb() && var4) {
    int var10 = (int)(1000.0 * var8);
                     if (var10 < 1) {
                        var10 = 1;
                     }

    int var11 = Rand.Next(0, var10);
    int var12 = this.bulbBurnMinutes / 10000;
                     if (var11 < var12) {
                        this.bulbBurnMinutes = 0;
                        this.setActive(false, true, true);
                        this.bulbItem = nullptr;
                        IsoWorld.instance.getFreeEmitter().playSound("LightbulbBurnedOut", this.square);
                        var1 = true;
                        if (Core.bDebug) {
                           System.out.println("broke bulb at x=" + this.getX() + ", y=" + this.getY() + ", z=" + this.getZ());
                        }
                     }
                  }

                  this.nextBreakUpdate = 60;
               }

               if (this.Activated && var7 && this.hasLightBulb()) {
    float var14 = this.power - this.power % 0.01F;
                  this.power = this.power - this.delta * (float)var13;
                  if (this.power < 0.0F) {
                     this.power = 0.0F;
                  }

                  if (var13 == 1L || this.power < var14) {
                     var1 = true;
                  }
               }
            }

            if (this.useBattery && this.Activated && (this.power <= 0.0F || !this.hasBattery)) {
               this.power = 0.0F;
               this.setActive(false, true, true);
               var1 = true;
            }
         }

         if (this.Activated && !this.hasLightBulb()) {
            this.setActive(false, true, true);
            var1 = true;
         }

         if (var1 && GameServer.bServer) {
            this.syncCustomizedSettings(nullptr);
         }
      }
   }

    bool isActivated() {
      return this.Activated;
   }

    void addToWorld() {
      if (!this.Activated) {
         this.lastMinuteStamp = -1L;
      }

      if (!this.lightRoom && !this.lights.empty()) {
         for (int var1 = 0; var1 < this.lights.size(); var1++) {
            IsoWorld.instance.CurrentCell.getLamppostPositions().push_back(this.lights.get(var1));
         }
      }

      if (this.getCell() != nullptr && this.canBeModified && !this.lightRoom && (!GameServer.bServer && !GameClient.bClient || GameServer.bServer)) {
         this.getCell().addToStaticUpdaterObjectList(this);
      }

      this.checkAmbientSound();
   }

    void removeFromWorld() {
      if (!this.lightRoom && !this.lights.empty()) {
         for (int var1 = 0; var1 < this.lights.size(); var1++) {
            this.lights.get(var1).setActive(false);
            IsoWorld.instance.CurrentCell.removeLamppost(this.lights.get(var1));
         }

         this.lights.clear();
      }

      if (this.square != nullptr && this.lightRoom) {
    IsoRoom var2 = this.square.getRoom();
         if (var2 != nullptr) {
            var2.lightSwitches.remove(this);
         }
      }

      super.removeFromWorld();
   }

    static void chunkLoaded(IsoChunk var0) {
    std::vector var1 = new std::vector();

      for (int var2 = 0; var2 < 10; var2++) {
         for (int var3 = 0; var3 < 10; var3++) {
            for (int var4 = 0; var4 < 8; var4++) {
    IsoGridSquare var5 = var0.getGridSquare(var2, var3, var4);
               if (var5 != nullptr) {
    IsoRoom var6 = var5.getRoom();
                  if (var6 != nullptr && var6.hasLightSwitches() && !var1.contains(var6)) {
                     var1.push_back(var6);
                  }
               }
            }
         }
      }

      for (int var7 = 0; var7 < var1.size(); var7++) {
    IsoRoom var8 = (IsoRoom)var1.get(var7);
         var8.createLights(var8.def.bLightsActive);

         for (int var9 = 0; var9 < var8.roomLights.size(); var9++) {
    IsoRoomLight var10 = (IsoRoomLight)var8.roomLights.get(var9);
            if (!var0.roomLights.contains(var10)) {
               var0.roomLights.push_back(var10);
            }
         }
      }
   }

   public std::vector<IsoLightSource> getLights() {
      return this.lights;
   }
}
} // namespace objects
} // namespace iso
} // namespace zombie
