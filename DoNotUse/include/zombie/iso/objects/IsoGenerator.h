#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/SandboxOptions.h"
#include "zombie/WorldSoundManager.h"
#include "zombie/core/Rand.h"
#include "zombie/core/Translator.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/properties/PropertyContainer.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/inventory/types/Food.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/PacketTypes/PacketType.h"
#include "zombie/network/ServerMap.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {
namespace objects {


class IsoGenerator : public IsoObject {
public:
    float fuel = 0.0F;
    bool activated = false;
    int condition = 0;
    int lastHour = -1;
    bool connected = false;
    int numberOfElectricalItems = 0;
    bool updateSurrounding = false;
   private const std::unordered_map<std::string, std::string> itemsPowered = std::make_unique<std::unordered_map<>>();
    float totalPowerUsing = 0.0F;
   private static const std::vector<IsoGenerator> AllGenerators = std::make_unique<std::vector<>>();
    static const int GENERATOR_RADIUS = 20;

    public IsoGenerator(IsoCell var1) {
      super(var1);
   }

    public IsoGenerator(InventoryItem var1, IsoCell var2, IsoGridSquare var3) {
      super(var2, var3, IsoSpriteManager.instance.getSprite("appliances_misc_01_0"));
      if (var1 != nullptr) {
         this.setInfoFromItem(var1);
      }

      this.sprite = IsoSpriteManager.instance.getSprite("appliances_misc_01_0");
      this.square = var3;
      var3.AddSpecialObject(this);
      if (GameClient.bClient) {
         this.transmitCompleteItemToServer();
      }
   }

    public IsoGenerator(InventoryItem var1, IsoCell var2, IsoGridSquare var3, bool var4) {
      super(var2, var3, IsoSpriteManager.instance.getSprite("appliances_misc_01_0"));
      if (var1 != nullptr) {
         this.setInfoFromItem(var1);
      }

      this.sprite = IsoSpriteManager.instance.getSprite("appliances_misc_01_0");
      this.square = var3;
      var3.AddSpecialObject(this);
      if (GameClient.bClient && !var4) {
         this.transmitCompleteItemToServer();
      }
   }

    void setInfoFromItem(InventoryItem var1) {
      this.condition = var1.getCondition();
      if (var1.getModData().rawget("fuel") instanceof double) {
         this.fuel = ((double)var1.getModData().rawget("fuel")).floatValue();
      }
   }

    void update() {
      if (this.updateSurrounding && this.getSquare() != nullptr) {
         this.setSurroundingElectricity();
         this.updateSurrounding = false;
      }

      if (this.isActivated()) {
         if (!GameServer.bServer && (this.emitter == nullptr || !this.emitter.isPlaying("GeneratorLoop"))) {
            if (this.emitter == nullptr) {
               this.emitter = IsoWorld.instance.getFreeEmitter(this.getX() + 0.5F, this.getY() + 0.5F, (int)this.getZ());
               IsoWorld.instance.takeOwnershipOfEmitter(this.emitter);
            }

            this.emitter.playSoundLoopedImpl("GeneratorLoop");
         }

         if (GameClient.bClient) {
            this.emitter.tick();
            return;
         }

         WorldSoundManager.instance.addSoundRepeating(this, (int)this.getX(), (int)this.getY(), (int)this.getZ(), 20, 1, false);
         if ((int)GameTime.getInstance().getWorldAgeHours() != this.lastHour) {
            if (!this.getSquare().getProperties().Is(IsoFlagType.exterior) && this.getSquare().getBuilding() != nullptr) {
               this.getSquare().getBuilding().setToxic(false);
               this.getSquare().getBuilding().setToxic(this.isActivated());
            }

    int var1 = (int)GameTime.getInstance().getWorldAgeHours() - this.lastHour;
    float var2 = 0.0F;
    int var3 = 0;

            for (int var4 = 0; var4 < var1; var4++) {
    float var5 = this.totalPowerUsing;
               var5 = (float)(var5 * SandboxOptions.instance.GeneratorFuelConsumption.getValue());
               var2 += var5;
               if (Rand.Next(30) == 0) {
                  var3 += Rand.Next(2) + 1;
               }

               if (this.fuel - var2 <= 0.0F || this.condition - var3 <= 0) {
                  break;
               }
            }

            this.fuel -= var2;
            if (this.fuel <= 0.0F) {
               this.setActivated(false);
               this.fuel = 0.0F;
            }

            this.condition -= var3;
            if (this.condition <= 0) {
               this.setActivated(false);
               this.condition = 0;
            }

            if (this.condition <= 20) {
               if (Rand.Next(10) == 0) {
                  IsoFireManager.StartFire(this.getCell(), this.square, true, 1000);
                  this.condition = 0;
                  this.setActivated(false);
               } else if (Rand.Next(20) == 0) {
                  this.square.explode();
                  this.condition = 0;
                  this.setActivated(false);
               }
            }

            this.lastHour = (int)GameTime.getInstance().getWorldAgeHours();
            if (GameServer.bServer) {
               this.syncIsoObject(false, (byte)0, nullptr, nullptr);
            }
         }
      }

      if (this.emitter != nullptr) {
         this.emitter.tick();
      }
   }

    void setSurroundingElectricity() {
      this.itemsPowered.clear();
      this.totalPowerUsing = 0.02F;
      this.numberOfElectricalItems = 1;
      if (this.square != nullptr && this.square.chunk != nullptr) {
    int var1 = this.square.chunk.wx;
    int var2 = this.square.chunk.wy;

         for (int var3 = -2; var3 <= 2; var3++) {
            for (int var4 = -2; var4 <= 2; var4++) {
               IsoChunk var5 = GameServer.bServer
                  ? ServerMap.instance.getChunk(var1 + var4, var2 + var3)
                  : IsoWorld.instance.CurrentCell.getChunk(var1 + var4, var2 + var3);
               if (var5 != nullptr && this.touchesChunk(var5)) {
                  if (this.isActivated()) {
                     var5.addGeneratorPos(this.square.x, this.square.y, this.square.z);
                  } else {
                     var5.removeGeneratorPos(this.square.x, this.square.y, this.square.z);
                  }
               }
            }
         }

    bool var19 = SandboxOptions.getInstance().AllowExteriorGenerator.getValue();
    int var20 = this.square.getX() - 20;
    int var21 = this.square.getX() + 20;
    int var6 = this.square.getY() - 20;
    int var7 = this.square.getY() + 20;
    int var8 = Math.max(0, this.getSquare().getZ() - 3);
    int var9 = Math.min(8, this.getSquare().getZ() + 3);

         for (int var10 = var8; var10 < var9; var10++) {
            for (int var11 = var20; var11 <= var21; var11++) {
               for (int var12 = var6; var12 <= var7; var12++) {
                  if (!(IsoUtils.DistanceToSquared(var11 + 0.5F, var12 + 0.5F, this.getSquare().getX() + 0.5F, this.getSquare().getY() + 0.5F) > 400.0F)) {
    IsoGridSquare var13 = this.getCell().getGridSquare(var11, var12, var10);
                     if (var13 != nullptr) {
    bool var14 = this.isActivated();
                        if (!var19 && var13.Is(IsoFlagType.exterior)) {
                           var14 = false;
                        }

                        var13.setHaveElectricity(var14);

                        for (int var15 = 0; var15 < var13.getObjects().size(); var15++) {
    IsoObject var16 = (IsoObject)var13.getObjects().get(var15);
                           if (var16 != nullptr && !(dynamic_cast<IsoWorldInventoryObject*>(var16) != nullptr)) {
                              if (dynamic_cast<IsoClothingDryer*>(var16) != nullptr && ((IsoClothingDryer)var16).isActivated()) {
                                 this.addPoweredItem(var16, 0.09F);
                              }

                              if (dynamic_cast<IsoClothingWasher*>(var16) != nullptr && ((IsoClothingWasher)var16).isActivated()) {
                                 this.addPoweredItem(var16, 0.09F);
                              }

                              if (dynamic_cast<IsoCombinationWasherDryer*>(var16) != nullptr && ((IsoCombinationWasherDryer)var16).isActivated()) {
                                 this.addPoweredItem(var16, 0.09F);
                              }

                              if (dynamic_cast<IsoStackedWasherDryer*>(var16) != nullptr var17) {
    float var18 = 0.0F;
                                 if (var17.isDryerActivated()) {
                                    var18 += 0.9F;
                                 }

                                 if (var17.isWasherActivated()) {
                                    var18 += 0.9F;
                                 }

                                 if (var18 > 0.0F) {
                                    this.addPoweredItem(var16, var18);
                                 }
                              }

                              if (dynamic_cast<IsoTelevision*>(var16) != nullptr && ((IsoTelevision)var16).getDeviceData().getIsTurnedOn()) {
                                 this.addPoweredItem(var16, 0.03F);
                              }

                              if (dynamic_cast<IsoRadio*>(var16) != nullptr
                                 && ((IsoRadio)var16).getDeviceData().getIsTurnedOn()
                                 && !((IsoRadio)var16).getDeviceData().getIsBatteryPowered()) {
                                 this.addPoweredItem(var16, 0.01F);
                              }

                              if (dynamic_cast<IsoStove*>(var16) != nullptr && ((IsoStove)var16).Activated()) {
                                 this.addPoweredItem(var16, 0.09F);
                              }

    bool var22 = var16.getContainerByType("fridge") != nullptr;
    bool var23 = var16.getContainerByType("freezer") != nullptr;
                              if (var22 && var23) {
                                 this.addPoweredItem(var16, 0.13F);
                              } else if (var22 || var23) {
                                 this.addPoweredItem(var16, 0.08F);
                              }

                              if (dynamic_cast<IsoLightSwitch*>(var16) != nullptr && ((IsoLightSwitch)var16).Activated) {
                                 this.addPoweredItem(var16, 0.002F);
                              }

                              var16.checkHaveElectricity();
                           }
                        }
                     }
                  }
               }
            }
         }
      }
   }

    void addPoweredItem(IsoObject var1, float var2) {
    std::string var3 = Translator.getText("IGUI_VehiclePartCatOther");
    PropertyContainer var4 = var1.getProperties();
      if (var4 != nullptr && var4.Is("CustomName")) {
    std::string var5 = "Moveable Object";
         if (var4.Is("CustomName")) {
            if (var4.Is("GroupName")) {
               var5 = var4.Val("GroupName") + " " + var4.Val("CustomName");
            } else {
               var5 = var4.Val("CustomName");
            }
         }

         var3 = Translator.getMoveableDisplayName(var5);
      }

      if (dynamic_cast<IsoLightSwitch*>(var1) != nullptr) {
         var3 = Translator.getText("IGUI_Lights");
      }

      this.totalPowerUsing -= var2;
    int var9 = 1;

      for (std::string var7 : this.itemsPowered.keySet()) {
         if (var7.startsWith(var3)) {
            var9 = int.parseInt(var7.replaceAll("[\\D]", ""));
            var9++;
            this.itemsPowered.remove(var7);
            break;
         }
      }

      this.itemsPowered.put(var3 + " x" + var9, std::string.format(" (%.2f L/h)", var2 * var9));
      if (var9 == 1) {
         this.totalPowerUsing += var2 * (var9 + 1);
      } else {
         this.totalPowerUsing += var2 * var9;
      }
   }

    void updateFridgeFreezerItems(IsoObject var1) {
      for (int var2 = 0; var2 < var1.getContainerCount(); var2++) {
    ItemContainer var3 = var1.getContainerByIndex(var2);
         if ("fridge" == var3.getType()) || "freezer" == var3.getType())) {
    std::vector var4 = var3.getItems();

            for (int var5 = 0; var5 < var4.size(); var5++) {
    InventoryItem var6 = (InventoryItem)var4.get(var5);
               if (dynamic_cast<Food*>(var6) != nullptr) {
                  var6.updateAge();
               }
            }
         }
      }
   }

    void updateFridgeFreezerItems(IsoGridSquare var1) {
    int var2 = var1.getObjects().size();
      IsoObject[] var3 = (IsoObject[])var1.getObjects().getElements();

      for (int var4 = 0; var4 < var2; var4++) {
    IsoObject var5 = var3[var4];
         this.updateFridgeFreezerItems(var5);
      }
   }

    void updateFridgeFreezerItems() {
      if (this.square != nullptr) {
    int var1 = this.square.getX() - 20;
    int var2 = this.square.getX() + 20;
    int var3 = this.square.getY() - 20;
    int var4 = this.square.getY() + 20;
    int var5 = Math.max(0, this.square.getZ() - 3);
    int var6 = Math.min(8, this.square.getZ() + 3);

         for (int var7 = var5; var7 < var6; var7++) {
            for (int var8 = var1; var8 <= var2; var8++) {
               for (int var9 = var3; var9 <= var4; var9++) {
                  if (IsoUtils.DistanceToSquared(var8, var9, this.square.x, this.square.y) <= 400.0F) {
    IsoGridSquare var10 = this.getCell().getGridSquare(var8, var9, var7);
                     if (var10 != nullptr) {
                        this.updateFridgeFreezerItems(var10);
                     }
                  }
               }
            }
         }
      }
   }

    void load(ByteBuffer var1, int var2, bool var3) {
      super.load(var1, var2, var3);
      this.connected = var1.get() == 1;
      this.activated = var1.get() == 1;
      if (var2 < 138) {
         this.fuel = var1.getInt();
      } else {
         this.fuel = var1.getFloat();
      }

      this.condition = var1.getInt();
      this.lastHour = var1.getInt();
      this.numberOfElectricalItems = var1.getInt();
      this.updateSurrounding = true;
   }

    void save(ByteBuffer var1, bool var2) {
      super.save(var1, var2);
      var1.put((byte)(this.isConnected() ? 1 : 0));
      var1.put((byte)(this.isActivated() ? 1 : 0));
      var1.putFloat(this.getFuel());
      var1.putInt(this.getCondition());
      var1.putInt(this.lastHour);
      var1.putInt(this.numberOfElectricalItems);
   }

    void remove() {
      if (this.getSquare() != nullptr) {
         this.getSquare().transmitRemoveItemFromSquare(this);
      }
   }

    void addToWorld() {
      this.getCell().addToProcessIsoObject(this);
      if (!AllGenerators.contains(this)) {
         AllGenerators.push_back(this);
      }

      if (GameClient.bClient) {
         GameClient.instance.objectSyncReq.putRequest(this.square, this);
      }
   }

    void removeFromWorld() {
      AllGenerators.remove(this);
      if (this.emitter != nullptr) {
         this.emitter.stopAll();
         IsoWorld.instance.returnOwnershipOfEmitter(this.emitter);
         this.emitter = nullptr;
      }

      super.removeFromWorld();
   }

    std::string getObjectName() {
      return "IsoGenerator";
   }

    float getFuel() {
      return this.fuel;
   }

    void setFuel(float var1) {
      this.fuel = var1;
      if (this.fuel > 100.0F) {
         this.fuel = 100.0F;
      }

      if (this.fuel < 0.0F) {
         this.fuel = 0.0F;
      }

      if (GameServer.bServer) {
         this.syncIsoObject(false, (byte)0, nullptr, nullptr);
      }

      if (GameClient.bClient) {
         this.syncIsoObject(false, (byte)0, nullptr, nullptr);
      }
   }

    bool isActivated() {
      return this.activated;
   }

    void setActivated(bool var1) {
      if (var1 != this.activated) {
         if (!this.getSquare().getProperties().Is(IsoFlagType.exterior) && this.getSquare().getBuilding() != nullptr) {
            this.getSquare().getBuilding().setToxic(false);
            this.getSquare().getBuilding().setToxic(var1);
         }

         if (!GameServer.bServer && this.emitter == nullptr) {
            this.emitter = IsoWorld.instance.getFreeEmitter(this.getX() + 0.5F, this.getY() + 0.5F, this.getZ());
            IsoWorld.instance.takeOwnershipOfEmitter(this.emitter);
         }

         if (var1) {
            this.lastHour = (int)GameTime.getInstance().getWorldAgeHours();
            if (this.emitter != nullptr) {
               this.emitter.playSound("GeneratorStarting");
            }
         } else if (this.emitter != nullptr) {
            if (!this.emitter.empty()) {
               this.emitter.stopAll();
            }

            this.emitter.playSound("GeneratorStopping");
         }

         try {
            this.updateFridgeFreezerItems();
         } catch (Throwable var3) {
            ExceptionLogger.logException(var3);
         }

         this.activated = var1;
         this.setSurroundingElectricity();
         if (GameClient.bClient) {
            this.syncIsoObject(false, (byte)0, nullptr, nullptr);
         }

         if (GameServer.bServer) {
            this.syncIsoObject(false, (byte)0, nullptr, nullptr);
         }
      }
   }

    void failToStart() {
      if (!GameServer.bServer) {
         if (this.emitter == nullptr) {
            this.emitter = IsoWorld.instance.getFreeEmitter(this.getX() + 0.5F, this.getY() + 0.5F, this.getZ());
            IsoWorld.instance.takeOwnershipOfEmitter(this.emitter);
         }

         this.emitter.playSound("GeneratorFailedToStart");
      }
   }

    int getCondition() {
      return this.condition;
   }

    void setCondition(int var1) {
      this.condition = var1;
      if (this.condition > 100) {
         this.condition = 100;
      }

      if (this.condition < 0) {
         this.condition = 0;
      }

      if (GameServer.bServer) {
         this.syncIsoObject(false, (byte)0, nullptr, nullptr);
      }

      if (GameClient.bClient) {
         this.syncIsoObject(false, (byte)0, nullptr, nullptr);
      }
   }

    bool isConnected() {
      return this.connected;
   }

    void setConnected(bool var1) {
      this.connected = var1;
      if (GameClient.bClient) {
         this.syncIsoObject(false, (byte)0, nullptr, nullptr);
      }
   }

    void syncIsoObjectSend(ByteBufferWriter var1) {
    uint8_t var2 = (byte)this.getObjectIndex();
      var1.putInt(this.square.getX());
      var1.putInt(this.square.getY());
      var1.putInt(this.square.getZ());
      var1.putByte(var2);
      var1.putByte((byte)1);
      var1.putByte((byte)0);
      var1.putFloat(this.fuel);
      var1.putInt(this.condition);
      var1.putByte((byte)(this.activated ? 1 : 0));
      var1.putByte((byte)(this.connected ? 1 : 0));
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
    ByteBufferWriter var13 = GameClient.connection.startPacket();
            PacketType.SyncIsoObject.doPacket(var13);
            this.syncIsoObjectSend(var13);
            PacketType.SyncIsoObject.send(GameClient.connection);
         } else if (GameServer.bServer && !var1) {
            for (UdpConnection var14 : GameServer.udpEngine.connections) {
    ByteBufferWriter var15 = var14.startPacket();
               PacketType.SyncIsoObject.doPacket(var15);
               this.syncIsoObjectSend(var15);
               PacketType.SyncIsoObject.send(var14);
            }
         } else if (var1) {
    float var5 = var4.getFloat();
    int var6 = var4.getInt();
    bool var7 = var4.get() == 1;
    bool var8 = var4.get() == 1;
            this.sync(var5, var6, var8, var7);
            if (GameServer.bServer) {
               for (UdpConnection var10 : GameServer.udpEngine.connections) {
                  if (var3 != nullptr && var10.getConnectedGUID() != var3.getConnectedGUID()) {
    ByteBufferWriter var11 = var10.startPacket();
                     PacketType.SyncIsoObject.doPacket(var11);
                     this.syncIsoObjectSend(var11);
                     PacketType.SyncIsoObject.send(var10);
                  }
               }
            }
         }
      }
   }

    void sync(float var1, int var2, bool var3, bool var4) {
      this.fuel = var1;
      this.condition = var2;
      this.connected = var3;
      if (this.activated != var4) {
         try {
            this.updateFridgeFreezerItems();
         } catch (Throwable var6) {
            ExceptionLogger.logException(var6);
         }

         this.activated = var4;
         if (var4) {
            this.lastHour = (int)GameTime.getInstance().getWorldAgeHours();
         } else if (this.emitter != nullptr) {
            this.emitter.stopAll();
         }

         this.setSurroundingElectricity();
      }
   }

    bool touchesChunk(IsoChunk var1) {
    IsoGridSquare var2 = this.getSquare();

      assert var2 != nullptr;

      if (var2 == nullptr) {
    return false;
      } else {
    int var3 = var1.wx * 10;
    int var4 = var1.wy * 10;
    int var5 = var3 + 10 - 1;
    int var6 = var4 + 10 - 1;
         if (var2.x - 20 > var5) {
    return false;
         } else if (var2.x + 20 < var3) {
    return false;
         } else {
            return var2.y - 20 > var6 ? false : var2.y + 20 >= var4;
         }
      }
   }

    static void chunkLoaded(IsoChunk var0) {
      var0.checkForMissingGenerators();

      for (int var1 = -2; var1 <= 2; var1++) {
         for (int var2 = -2; var2 <= 2; var2++) {
            if (var2 != 0 || var1 != 0) {
               IsoChunk var3 = GameServer.bServer
                  ? ServerMap.instance.getChunk(var0.wx + var2, var0.wy + var1)
                  : IsoWorld.instance.CurrentCell.getChunk(var0.wx + var2, var0.wy + var1);
               if (var3 != nullptr) {
                  var3.checkForMissingGenerators();
               }
            }
         }
      }

      for (int var4 = 0; var4 < AllGenerators.size(); var4++) {
    IsoGenerator var5 = AllGenerators.get(var4);
         if (!var5.updateSurrounding && var5.touchesChunk(var0)) {
            var5.updateSurrounding = true;
         }
      }
   }

    static void updateSurroundingNow() {
      for (int var0 = 0; var0 < AllGenerators.size(); var0++) {
    IsoGenerator var1 = AllGenerators.get(var0);
         if (var1.updateSurrounding && var1.getSquare() != nullptr) {
            var1.updateSurrounding = false;
            var1.setSurroundingElectricity();
         }
      }
   }

    static void updateGenerator(IsoGridSquare var0) {
      if (var0 != nullptr) {
         for (int var1 = 0; var1 < AllGenerators.size(); var1++) {
    IsoGenerator var2 = AllGenerators.get(var1);
            if (var2.getSquare() != nullptr) {
    float var3 = IsoUtils.DistanceToSquared(var0.x + 0.5F, var0.y + 0.5F, var2.getSquare().getX() + 0.5F, var2.getSquare().getY() + 0.5F);
               if (var3 <= 400.0F) {
                  var2.updateSurrounding = true;
               }
            }
         }
      }
   }

    static void Reset() {
      assert AllGenerators.empty();

      AllGenerators.clear();
   }

    static bool isPoweringSquare(int var0, int var1, int var2, int var3, int var4, int var5) {
    int var6 = Math.max(0, var2 - 3);
    int var7 = Math.min(8, var2 + 3);
      return var5 >= var6 && var5 < var7 ? IsoUtils.DistanceToSquared(var0 + 0.5F, var1 + 0.5F, var3 + 0.5F, var4 + 0.5F) <= 400.0F : false;
   }

   public std::vector<std::string> getItemsPowered() {
    std::vector var1 = new std::vector();

      for (std::string var3 : this.itemsPowered.keySet()) {
         var1.push_back(var3 + this.itemsPowered.get(var3));
      }

      var1.sort(std::string::compareToIgnoreCase);
    return var1;
   }

    float getTotalPowerUsing() {
      return this.totalPowerUsing;
   }

    void setTotalPowerUsing(float var1) {
      this.totalPowerUsing = var1;
   }
}
} // namespace objects
} // namespace iso
} // namespace zombie
