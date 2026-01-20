#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/SoundManager.h"
#include "zombie/SystemDisabler.h"
#include "zombie/audio/BaseSoundEmitter.h"
#include "zombie/core/Rand.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/objects/interfaces/Activatable.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteGrid.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/PacketTypes/PacketType.h"
#include "zombie/util/Type.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {
namespace objects {


class IsoStove : public IsoObject {
public:
   private static const std::vector<IsoObject> s_tempObjects = std::make_unique<std::vector<>>();
    bool activated = false;
    long soundInstance = -1L;
    float maxTemperature = 0.0F;
    double stopTime;
    double startTime;
    float currentTemperature = 0.0F;
    int secondsTimer = -1;
    bool firstTurnOn = true;
    bool broken = false;
    bool hasMetal = false;

    public IsoStove(IsoCell var1, IsoGridSquare var2, IsoSprite var3) {
      super(var1, var2, var3);
   }

    std::string getObjectName() {
      return "Stove";
   }

    public IsoStove(IsoCell var1) {
      super(var1);
   }

    bool Activated() {
      return this.activated;
   }

    void update() {
      if (this.Activated() && (this.container == nullptr || !this.container.isPowered())) {
         this.setActivated(false);
         if (this.container != nullptr) {
            this.container.addItemsToProcessItems();
         }
      }

      if (this.Activated() && this.isMicrowave() && this.stopTime > 0.0 && this.stopTime < GameTime.instance.getWorldAgeHours()) {
         this.setActivated(false);
      }

    bool var1 = GameServer.bServer || !GameClient.bClient && !GameServer.bServer;
      if (var1 && this.Activated() && this.hasMetal && Rand.Next(Rand.AdjustForFramerate(200)) == 100) {
         IsoFireManager.StartFire(this.container.SourceGrid.getCell(), this.container.SourceGrid, true, 10000);
         this.setBroken(true);
         this.activated = false;
         this.stopTime = 0.0;
         this.startTime = 0.0;
         this.secondsTimer = -1;
      }

      if (!GameServer.bServer) {
         if (this.Activated()) {
            if (this.stopTime > 0.0 && this.stopTime < GameTime.instance.getWorldAgeHours()) {
               if (!this.isMicrowave() && "stove" == this.container.getType()) && this.isSpriteGridOriginObject()) {
    BaseSoundEmitter var2 = IsoWorld.instance.getFreeEmitter(this.getX() + 0.5F, this.getY() + 0.5F, (int)this.getZ());
                  var2.playSoundImpl("StoveTimerExpired", this);
               }

               this.stopTime = 0.0;
               this.startTime = 0.0;
               this.secondsTimer = -1;
            }

            if (this.getMaxTemperature() > 0.0F && this.currentTemperature < this.getMaxTemperature()) {
    float var3 = (this.getMaxTemperature() - this.currentTemperature) / 700.0F;
               if (var3 < 0.05F) {
                  var3 = 0.05F;
               }

               this.currentTemperature = this.currentTemperature + var3 * GameTime.instance.getMultiplier();
               if (this.currentTemperature > this.getMaxTemperature()) {
                  this.currentTemperature = this.getMaxTemperature();
               }
            } else if (this.currentTemperature > this.getMaxTemperature()) {
               this.currentTemperature = this.currentTemperature
                  - (this.currentTemperature - this.getMaxTemperature()) / 1000.0F * GameTime.instance.getMultiplier();
               if (this.currentTemperature < 0.0F) {
                  this.currentTemperature = 0.0F;
               }
            }
         } else if (this.currentTemperature > 0.0F) {
            this.currentTemperature = this.currentTemperature - 0.1F * GameTime.instance.getMultiplier();
            this.currentTemperature = Math.max(this.currentTemperature, 0.0F);
         }

         if (this.container != nullptr && this.isMicrowave()) {
            if (this.Activated()) {
               this.currentTemperature = this.getMaxTemperature();
            } else {
               this.currentTemperature = 0.0F;
            }
         }

         if (this.isSpriteGridOriginObject() && this.emitter != nullptr) {
            if (this.Activated() && this.secondsTimer > 0) {
               if (!this.emitter.isPlaying("StoveTimer")) {
                  this.emitter.playSoundImpl("StoveTimer", this);
               }
            } else if (this.emitter.isPlaying("StoveTimer")) {
               this.emitter.stopSoundByName("StoveTimer");
            }
         }
      }
   }

    void load(ByteBuffer var1, int var2, bool var3) {
      super.load(var1, var2, var3);
      if (var2 >= 28) {
         this.activated = var1.get() == 1;
      }

      if (var2 >= 106) {
         this.secondsTimer = var1.getInt();
         this.maxTemperature = var1.getFloat();
         this.firstTurnOn = var1.get() == 1;
         this.broken = var1.get() == 1;
      }

      if (SystemDisabler.doObjectStateSyncEnable && GameClient.bClient) {
         GameClient.instance.objectSyncReq.putRequestLoad(this.square);
      }
   }

    void save(ByteBuffer var1, bool var2) {
      super.save(var1, var2);
      var1.put((byte)(this.activated ? 1 : 0));
      var1.putInt(this.secondsTimer);
      var1.putFloat(this.maxTemperature);
      var1.put((byte)(this.firstTurnOn ? 1 : 0));
      var1.put((byte)(this.broken ? 1 : 0));
   }

    void addToWorld() {
      if (this.container != nullptr) {
    IsoCell var1 = this.getCell();
         var1.addToProcessIsoObject(this);
         this.container.addItemsToProcessItems();
         this.setActivated(this.activated);
      }
   }

    void Toggle() {
      SoundManager.instance.PlayWorldSound(this.isMicrowave() ? "ToggleMicrowave" : "ToggleStove", this.getSquare(), 1.0F, 1.0F, 1.0F, false);
      this.setActivated(!this.activated);
      this.container.addItemsToProcessItems();
      IsoGenerator.updateGenerator(this.square);
      this.syncIsoObject(false, (byte)(this.activated ? 1 : 0), nullptr, nullptr);
      this.syncSpriteGridObjects(true, true);
   }

    void sync() {
      this.syncIsoObject(false, (byte)(this.activated ? 1 : 0), nullptr, nullptr);
   }

    void doSound() {
      if (GameServer.bServer) {
         this.hasMetal();
      } else if (this.isSpriteGridOriginObject()) {
         if (this.isMicrowave()) {
            if (this.activated) {
               if (this.emitter != nullptr) {
                  if (this.soundInstance != -1L) {
                     this.emitter.stopSound(this.soundInstance);
                  }

                  this.emitter.stopSoundByName("StoveTimer");
               }

               this.emitter = IsoWorld.instance.getFreeEmitter(this.getX() + 0.5F, this.getY() + 0.5F, (int)this.getZ());
               IsoWorld.instance.setEmitterOwner(this.emitter, this);
               if (this.hasMetal()) {
                  this.soundInstance = this.emitter.playSoundLoopedImpl("MicrowaveCookingMetal");
               } else {
                  this.soundInstance = this.emitter.playSoundLoopedImpl("MicrowaveRunning");
               }
            } else if (this.soundInstance != -1L) {
               if (this.emitter != nullptr) {
                  this.emitter.stopSound(this.soundInstance);
                  this.emitter.stopSoundByName("StoveTimer");
                  this.emitter = nullptr;
               }

               this.soundInstance = -1L;
               if (this.container != nullptr && this.container.isPowered()) {
    BaseSoundEmitter var1 = IsoWorld.instance.getFreeEmitter(this.getX() + 0.5F, this.getY() + 0.5F, (int)this.getZ());
                  var1.playSoundImpl("MicrowaveTimerExpired", this);
               }
            }
         } else if (this.getContainer() != nullptr && "stove" == this.container.getType())) {
            if (this.Activated()) {
               if (this.emitter == nullptr) {
                  this.emitter = IsoWorld.instance.getFreeEmitter(this.getX() + 0.5F, this.getY() + 0.5F, (int)this.getZ());
                  IsoWorld.instance.setEmitterOwner(this.emitter, this);
                  this.soundInstance = this.emitter.playSoundLoopedImpl("StoveRunning");
               } else if (!this.emitter.isPlaying("StoveRunning")) {
                  this.soundInstance = this.emitter.playSoundLoopedImpl("StoveRunning");
               }
            } else if (this.soundInstance != -1L) {
               if (this.emitter != nullptr) {
                  this.emitter.stopSound(this.soundInstance);
                  this.emitter.stopSoundByName("StoveTimer");
                  this.emitter = nullptr;
               }

               this.soundInstance = -1L;
            }
         }
      }
   }

    bool hasMetal() {
    int var1 = this.getContainer().getItems().size();

      for (int var2 = 0; var2 < var1; var2++) {
    InventoryItem var3 = (InventoryItem)this.getContainer().getItems().get(var2);
         if (var3.getMetalValue() > 0.0F || var3.hasTag("HasMetal")) {
            this.hasMetal = true;
    return true;
         }
      }

      this.hasMetal = false;
    return false;
   }

    std::string getActivatableType() {
      return "stove";
   }

    void syncIsoObjectSend(ByteBufferWriter var1) {
      var1.putInt(this.square.getX());
      var1.putInt(this.square.getY());
      var1.putInt(this.square.getZ());
    uint8_t var2 = (byte)this.square.getObjects().indexOf(this);
      var1.putByte(var2);
      var1.putByte((byte)1);
      var1.putByte((byte)(this.activated ? 1 : 0));
      var1.putInt(this.secondsTimer);
      var1.putFloat(this.maxTemperature);
   }

    void syncIsoObject(bool var1, uint8_t var2, UdpConnection var3, ByteBuffer var4) {
      if (this.square == nullptr) {
         System.out.println("ERROR: " + this.getClass().getSimpleName() + " square is nullptr");
      } else if (this.getObjectIndex() == -1) {
         System.out
            .println(
               "ERROR: " + this.getClass().getSimpleName() + " not found on square " + this.square.getX() + "," + this.square.getY() + "," + this.square.getZ()
            );
      } else {
         if (GameClient.bClient && !var1) {
    ByteBufferWriter var9 = GameClient.connection.startPacket();
            PacketType.SyncIsoObject.doPacket(var9);
            this.syncIsoObjectSend(var9);
            PacketType.SyncIsoObject.send(GameClient.connection);
         } else if (var1) {
    bool var5 = var2 == 1;
            this.secondsTimer = var4.getInt();
            this.maxTemperature = var4.getFloat();
            this.setActivated(var5);
            this.container.addItemsToProcessItems();
            if (GameServer.bServer) {
               for (UdpConnection var7 : GameServer.udpEngine.connections) {
                  if (var3 == nullptr || var7.getConnectedGUID() != var3.getConnectedGUID()) {
    ByteBufferWriter var8 = var7.startPacket();
                     PacketType.SyncIsoObject.doPacket(var8);
                     this.syncIsoObjectSend(var8);
                     PacketType.SyncIsoObject.send(var7);
                  }
               }
            }
         }
      }
   }

    void setActivated(bool var1) {
      if (!this.isBroken()) {
         this.activated = var1;
         if (this.firstTurnOn && this.getMaxTemperature() == 0.0F) {
            if (this.isMicrowave() && this.secondsTimer < 0) {
               this.maxTemperature = 100.0F;
            }

            if ("stove" == this.getContainer().getType()) && this.secondsTimer < 0) {
               this.maxTemperature = 200.0F;
            }
         }

         if (this.firstTurnOn) {
            this.firstTurnOn = false;
         }

         if (this.activated) {
            if (this.isMicrowave() && this.secondsTimer < 0) {
               this.secondsTimer = 3600;
            }

            if (this.secondsTimer > 0) {
               this.startTime = GameTime.instance.getWorldAgeHours();
               this.stopTime = this.startTime + this.secondsTimer / 3600.0;
            }
         } else {
            this.stopTime = 0.0;
            this.startTime = 0.0;
            this.hasMetal = false;
         }

         this.doSound();
         this.doOverlay();
      }
   }

    void doOverlay() {
      if (this.Activated() && this.getOverlaySprite() == nullptr) {
         std::string[] var1 = this.getSprite().getName().split("_");
    std::string var2 = var1[0] + "_" + var1[1] + "_ON_" + var1[2] + "_" + var1[3];
         this.setOverlaySprite(var2);
      } else if (!this.Activated()) {
         this.setOverlaySprite(nullptr);
      }
   }

    void setTimer(int var1) {
      this.secondsTimer = var1;
      if (this.activated && this.secondsTimer > 0) {
         this.startTime = GameTime.instance.getWorldAgeHours();
         this.stopTime = this.startTime + this.secondsTimer / 3600.0;
      }
   }

    int getTimer() {
      return this.secondsTimer;
   }

    float getMaxTemperature() {
      return this.maxTemperature;
   }

    void setMaxTemperature(float var1) {
      this.maxTemperature = var1;
   }

    bool isMicrowave() {
      return this.getContainer() != nullptr && this.getContainer().isMicrowave();
   }

    int isRunningFor() {
      return this.startTime == 0.0 ? 0 : (int)((GameTime.instance.getWorldAgeHours() - this.startTime) * 3600.0);
   }

    float getCurrentTemperature() {
      return this.currentTemperature + 100.0F;
   }

    bool isTemperatureChanging() {
      return this.currentTemperature != (this.activated ? this.maxTemperature : 0.0F);
   }

    bool isBroken() {
      return this.broken;
   }

    void setBroken(bool var1) {
      this.broken = var1;
   }

    bool isSpriteGridOriginObject() {
    IsoSprite var1 = this.getSprite();
      if (var1 == nullptr) {
    return false;
      } else {
    IsoSpriteGrid var2 = var1.getSpriteGrid();
         if (var2 == nullptr) {
    return true;
         } else {
    int var3 = var2.getSpriteGridPosX(var1);
    int var4 = var2.getSpriteGridPosY(var1);
    return var3 = = 0 && var4 == 0;
         }
      }
   }

    void syncSpriteGridObjects(bool var1, bool var2) {
      this.getSpriteGridObjects(s_tempObjects);

      for (int var3 = s_tempObjects.size() - 1; var3 >= 0; var3--) {
    IsoStove var4 = (IsoStove)Type.tryCastTo(s_tempObjects.get(var3), IsoStove.class);
         if (var4 != nullptr && var4 != this) {
            var4.activated = this.activated;
            var4.maxTemperature = this.maxTemperature;
            var4.firstTurnOn = this.firstTurnOn;
            var4.secondsTimer = this.secondsTimer;
            var4.startTime = this.startTime;
            var4.stopTime = this.stopTime;
            var4.hasMetal = this.hasMetal;
            var4.doOverlay();
            var4.doSound();
            if (var1) {
               if (var4.container != nullptr) {
                  var4.container.addItemsToProcessItems();
               }

               IsoGenerator.updateGenerator(var4.square);
            }

            if (var2) {
               var4.sync();
            }
         }
      }
   }
}
} // namespace objects
} // namespace iso
} // namespace zombie
