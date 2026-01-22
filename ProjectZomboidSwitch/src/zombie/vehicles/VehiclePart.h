#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/SandboxOptions.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/chat/ChatElement.h"
#include "zombie/chat/ChatElementOwner.h"
#include "zombie/core/Rand.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/inventory/types/Drainable.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/radio/devices/DeviceData.h"
#include "zombie/radio/devices/WaveSignalDevice.h"
#include "zombie/scripting/objects/VehicleScript.h"
#include "zombie/scripting/objects/VehicleScript/Anim.h"
#include "zombie/scripting/objects/VehicleScript/Model.h"
#include "zombie/scripting/objects/VehicleScript/Part.h"
#include "zombie/scripting/objects/VehicleScript/Wheel.h"
#include "zombie/ui/UIFont.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace vehicles {


class VehiclePart {
public:
    BaseVehicle vehicle;
    bool bCreated;
    std::string partId;
    Part scriptPart;
    ItemContainer container;
    InventoryItem item;
    KahluaTable modData;
    float lastUpdated = -1.0F;
    short updateFlags;
    VehiclePart parent;
    VehicleDoor door;
    VehicleWindow window;
   protected std::vector<VehiclePart> children;
    std::string category;
    int condition = -1;
    bool specificItem = true;
    float wheelFriction = 0.0F;
    int mechanicSkillInstaller = 0;
    float suspensionDamping = 0.0F;
    float suspensionCompression = 0.0F;
    float engineLoudness = 0.0F;
    VehicleLight light;
    DeviceData deviceData;
    ChatElement chatElement;
    bool hasPlayerInRange;

    public VehiclePart(BaseVehicle var1) {
      this.vehicle = var1;
   }

    BaseVehicle getVehicle() {
      return this.vehicle;
   }

    void setScriptPart(Part var1) {
      this.scriptPart = var1;
   }

    Part getScriptPart() {
      return this.scriptPart;
   }

    ItemContainer getItemContainer() {
      return this.container;
   }

    void setItemContainer(ItemContainer var1) {
      if (var1 != nullptr) {
         var1.parent = this.getVehicle();
         var1.vehiclePart = this;
      }

      this.container = var1;
   }

    bool hasModData() {
      return this.modData != nullptr && !this.modData.empty();
   }

    KahluaTable getModData() {
      if (this.modData == nullptr) {
         this.modData = LuaManager.platform.newTable();
      }

      return this.modData;
   }

    float getLastUpdated() {
      return this.lastUpdated;
   }

    void setLastUpdated(float var1) {
      this.lastUpdated = var1;
   }

    std::string getId() {
      return this.scriptPart == nullptr ? this.partId : this.scriptPart.id;
   }

    int getIndex() {
      return this.vehicle.parts.indexOf(this);
   }

    std::string getArea() {
      return this.scriptPart == nullptr ? nullptr : this.scriptPart.area;
   }

   public std::vector<std::string> getItemType() {
      return this.scriptPart == nullptr ? nullptr : this.scriptPart.itemType;
   }

    KahluaTable getTable(const std::string& var1) {
      if (this.scriptPart != nullptr && this.scriptPart.tables != nullptr) {
    KahluaTable var2 = (KahluaTable)this.scriptPart.tables.get(var1);
    return var2 = = nullptr ? nullptr : LuaManager.copyTable(var2);
      } else {
    return nullptr;
      }
   }

    InventoryItem getInventoryItem() {
      return this.item;
   }

    void setInventoryItem(InventoryItem var1, int var2) {
      this.item = var1;
      this.doInventoryItemStats(var1, var2);
      this.getVehicle().updateTotalMass();
      this.getVehicle().bDoDamageOverlay = true;
      if (this.isSetAllModelsVisible()) {
         this.setAllModelsVisible(var1 != nullptr);
      }

      this.getVehicle().updatePartStats();
      if (!GameServer.bServer) {
         this.getVehicle().updateBulletStats();
      }
   }

    void setInventoryItem(InventoryItem var1) {
      this.setInventoryItem(var1, 0);
   }

    bool isInventoryItemUninstalled() {
      return this.getItemType() != nullptr && !this.getItemType().empty() && this.getInventoryItem() == nullptr;
   }

    bool isSetAllModelsVisible() {
      return this.scriptPart != nullptr && this.scriptPart.bSetAllModelsVisible;
   }

    void setAllModelsVisible(bool var1) {
      if (this.scriptPart != nullptr && this.scriptPart.models != nullptr && !this.scriptPart.models.empty()) {
         for (int var2 = 0; var2 < this.scriptPart.models.size(); var2++) {
    Model var3 = (Model)this.scriptPart.models.get(var2);
            this.vehicle.setModelVisible(this, var3, var1);
         }
      }
   }

    void doInventoryItemStats(InventoryItem var1, int var2) {
      if (var1 != nullptr) {
         if (this.isContainer()) {
            if (var1.getMaxCapacity() > 0 && this.getScriptPart().container.conditionAffectsCapacity) {
               this.setContainerCapacity((int)getNumberByCondition(var1.getMaxCapacity(), var1.getCondition(), 5.0F));
            } else if (var1.getMaxCapacity() > 0) {
               this.setContainerCapacity(var1.getMaxCapacity());
            }

            this.setContainerContentAmount(var1.getItemCapacity());
         }

         this.setSuspensionCompression(getNumberByCondition(var1.getSuspensionCompression(), var1.getCondition(), 0.6F));
         this.setSuspensionDamping(getNumberByCondition(var1.getSuspensionDamping(), var1.getCondition(), 0.6F));
         if (var1.getEngineLoudness() > 0.0F) {
            this.setEngineLoudness(getNumberByCondition(var1.getEngineLoudness(), var1.getCondition(), 10.0F));
         }

         this.setCondition(var1.getCondition());
         this.setMechanicSkillInstaller(var2);
      } else {
         if (this.scriptPart != nullptr && this.scriptPart.container != nullptr) {
            if (this.scriptPart.container.capacity > 0) {
               this.setContainerCapacity(this.scriptPart.container.capacity);
            } else {
               this.setContainerCapacity(0);
            }
         }

         this.setMechanicSkillInstaller(0);
         this.setContainerContentAmount(0.0F);
         this.setSuspensionCompression(0.0F);
         this.setSuspensionDamping(0.0F);
         this.setWheelFriction(0.0F);
         this.setEngineLoudness(0.0F);
      }
   }

    void setRandomCondition(InventoryItem var1) {
    VehicleType var2 = VehicleType.getTypeFromName(this.getVehicle().getVehicleType());
      if (this.getVehicle().isGoodCar()) {
    int var6 = 100;
         if (var1 != nullptr) {
            var6 = var1.getConditionMax();
         }

         this.setCondition(Rand.Next(var6 - var6 / 3, var6));
         if (var1 != nullptr) {
            var1.setCondition(this.getCondition());
         }
      } else {
    int var3 = 100;
         if (var1 != nullptr) {
            var3 = var1.getConditionMax();
         }

         if (var2 != nullptr) {
            var3 = (int)(var3 * var2.getRandomBaseVehicleQuality());
         }

    float var4 = 100.0F;
         if (var1 != nullptr) {
    int var5 = var1.getChanceToSpawnDamaged();
            if (var2 != nullptr) {
               var5 += var2.chanceToPartDamage;
            }

            if (var5 > 0 && Rand.Next(100) < var5) {
               var4 = Rand.Next(var3 - var3 / 2, var3);
            }
         } else {
    int var9 = 30;
            if (var2 != nullptr) {
               var9 += var2.chanceToPartDamage;
            }

            if (Rand.Next(100) < var9) {
               var4 = Rand.Next(var3 * 0.5F, var3);
            }
         }

         switch (SandboxOptions.instance.CarGeneralCondition.getValue()) {
            case 1:
               var4 -= Rand.Next(var4 * 0.3F, Rand.Next(var4 * 0.3F, var4 * 0.9F));
               break;
            case 2:
               var4 -= Rand.Next(var4 * 0.1F, var4 * 0.3F);
            case 3:
            default:
               break;
            case 4:
               var4 += Rand.Next(var4 * 0.2F, var4 * 0.4F);
               break;
            case 5:
               var4 += Rand.Next(var4 * 0.5F, var4 * 0.9F);
         }

         var4 = Math.max(0.0F, var4);
         var4 = Math.min(100.0F, var4);
         this.setCondition((int)var4);
         if (var1 != nullptr) {
            var1.setCondition(this.getCondition());
         }
      }
   }

    void setGeneralCondition(InventoryItem var1, float var2, float var3) {
    int var4 = 100;
      var4 = (int)(var4 * var2);
    float var5 = 100.0F;
      if (var1 != nullptr) {
    int var6 = var1.getChanceToSpawnDamaged();
         var6 = (int)(var6 + var3);
         if (var6 > 0 && Rand.Next(100) < var6) {
            var5 = Rand.Next(var4 - var4 / 2, var4);
         }
      } else {
    int var11 = 30;
         var11 = (int)(var11 + var3);
         if (Rand.Next(100) < var11) {
            var5 = Rand.Next(var4 * 0.5F, var4);
         }
      }

      switch (SandboxOptions.instance.CarGeneralCondition.getValue()) {
         case 1:
            var5 -= Rand.Next(var5 * 0.3F, Rand.Next(var5 * 0.3F, var5 * 0.9F));
            break;
         case 2:
            var5 -= Rand.Next(var5 * 0.1F, var5 * 0.3F);
         case 3:
         default:
            break;
         case 4:
            var5 += Rand.Next(var5 * 0.2F, var5 * 0.4F);
            break;
         case 5:
            var5 += Rand.Next(var5 * 0.5F, var5 * 0.9F);
      }

      var5 = Math.max(0.0F, var5);
      var5 = Math.min(100.0F, var5);
      this.setCondition((int)var5);
      if (var1 != nullptr) {
         var1.setCondition(this.getCondition());
      }
   }

    static float getNumberByCondition(float var0, float var1, float var2) {
      var1 += 20.0F * (100.0F - var1) / 100.0F;
    float var3 = var1 / 100.0F;
      return Math.round(Math.max(var2, var0 * var3) * 100.0F) / 100.0F;
   }

    bool isContainer() {
      return this.scriptPart == nullptr ? false : this.scriptPart.container != nullptr;
   }

    int getContainerCapacity() {
      return this.getContainerCapacity(nullptr);
   }

    int getContainerCapacity(IsoGameCharacter var1) {
      if (!this.isContainer()) {
    return 0;
      } else if (this.getItemContainer() != nullptr) {
    return var1 = = nullptr ? this.getItemContainer().getCapacity() : this.getItemContainer().getEffectiveCapacity(var1);
      } else if (this.getInventoryItem() != nullptr) {
         return this.scriptPart.container.conditionAffectsCapacity
            ? (int)getNumberByCondition(this.getInventoryItem().getMaxCapacity(), this.getCondition(), 5.0F)
            : this.getInventoryItem().getMaxCapacity();
      } else {
         return this.scriptPart.container.capacity;
      }
   }

    void setContainerCapacity(int var1) {
      if (this.isContainer()) {
         if (this.getItemContainer() != nullptr) {
            this.getItemContainer().Capacity = var1;
         }
      }
   }

    std::string getContainerContentType() {
      return !this.isContainer() ? nullptr : this.scriptPart.container.contentType;
   }

    float getContainerContentAmount() {
      if (!this.isContainer()) {
         return 0.0F;
      } else {
         if (this.hasModData()) {
    void* var1 = this.getModData().rawget("contentAmount");
            if (dynamic_cast<double*>(var1) != nullptr) {
               return ((double)var1).floatValue();
            }
         }

         return 0.0F;
      }
   }

    void setContainerContentAmount(float var1) {
      this.setContainerContentAmount(var1, false, false);
   }

    void setContainerContentAmount(float var1, bool var2, bool var3) {
      if (this.isContainer()) {
    int var4 = this.scriptPart.container.capacity;
         if (this.getInventoryItem() != nullptr) {
            var4 = this.getInventoryItem().getMaxCapacity();
         }

         if (!var2) {
            var1 = Math.min(var1, (float)var4);
         }

         var1 = Math.max(var1, 0.0F);
         this.getModData().rawset("contentAmount", (double)var1);
         if (this.getInventoryItem() != nullptr) {
            this.getInventoryItem().setItemCapacity(var1);
         }

         if (!var3) {
            this.getVehicle().updateTotalMass();
         }
      }
   }

    int getContainerSeatNumber() {
      return !this.isContainer() ? -1 : this.scriptPart.container.seat;
   }

    std::string getLuaFunction(const std::string& var1) {
      return this.scriptPart != nullptr && this.scriptPart.luaFunctions != nullptr ? (std::string)this.scriptPart.luaFunctions.get(var1) : nullptr;
   }

    Model getScriptModelById(const std::string& var1) {
      if (this.scriptPart != nullptr && this.scriptPart.models != nullptr) {
         for (int var2 = 0; var2 < this.scriptPart.models.size(); var2++) {
    Model var3 = (Model)this.scriptPart.models.get(var2);
            if (var1 == var3.id)) {
    return var3;
            }
         }

    return nullptr;
      } else {
    return nullptr;
      }
   }

    void setModelVisible(const std::string& var1, bool var2) {
    Model var3 = this.getScriptModelById(var1);
      if (var3 != nullptr) {
         this.vehicle.setModelVisible(this, var3, var2);
      }
   }

    VehiclePart getParent() {
      return this.parent;
   }

    void addChild(VehiclePart var1) {
      if (this.children == nullptr) {
         this.children = std::make_unique<std::vector<>>();
      }

      this.children.push_back(var1);
   }

    int getChildCount() {
      return this.children == nullptr ? 0 : this.children.size();
   }

    VehiclePart getChild(int var1) {
      return this.children != nullptr && var1 >= 0 && var1 < this.children.size() ? this.children.get(var1) : nullptr;
   }

    VehicleDoor getDoor() {
      return this.door;
   }

    VehicleWindow getWindow() {
      return this.window;
   }

    VehiclePart getChildWindow() {
      for (int var1 = 0; var1 < this.getChildCount(); var1++) {
    VehiclePart var2 = this.getChild(var1);
         if (var2.getWindow() != nullptr) {
    return var2;
         }
      }

    return nullptr;
   }

    VehicleWindow findWindow() {
    VehiclePart var1 = this.getChildWindow();
    return var1 = = nullptr ? nullptr : var1.getWindow();
   }

    Anim getAnimById(const std::string& var1) {
      if (this.scriptPart != nullptr && this.scriptPart.anims != nullptr) {
         for (int var2 = 0; var2 < this.scriptPart.anims.size(); var2++) {
    Anim var3 = (Anim)this.scriptPart.anims.get(var2);
            if (var3.id == var1)) {
    return var3;
            }
         }

    return nullptr;
      } else {
    return nullptr;
      }
   }

    void save(ByteBuffer var1) {
      GameWindow.WriteStringUTF(var1, this.getId());
      var1.put((byte)(this.bCreated ? 1 : 0));
      var1.putFloat(this.lastUpdated);
      if (this.getInventoryItem() == nullptr) {
         var1.put((byte)0);
      } else {
         var1.put((byte)1);
         this.getInventoryItem().saveWithSize(var1, false);
      }

      if (this.getItemContainer() == nullptr) {
         var1.put((byte)0);
      } else {
         var1.put((byte)1);
         this.getItemContainer().save(var1);
      }

      if (this.hasModData() && !this.getModData().empty()) {
         var1.put((byte)1);
         this.getModData().save(var1);
      } else {
         var1.put((byte)0);
      }

      if (this.getDeviceData() == nullptr) {
         var1.put((byte)0);
      } else {
         var1.put((byte)1);
         this.getDeviceData().save(var1, false);
      }

      if (this.light == nullptr) {
         var1.put((byte)0);
      } else {
         var1.put((byte)1);
         this.light.save(var1);
      }

      if (this.door == nullptr) {
         var1.put((byte)0);
      } else {
         var1.put((byte)1);
         this.door.save(var1);
      }

      if (this.window == nullptr) {
         var1.put((byte)0);
      } else {
         var1.put((byte)1);
         this.window.save(var1);
      }

      var1.putInt(this.condition);
      var1.putFloat(this.wheelFriction);
      var1.putInt(this.mechanicSkillInstaller);
      var1.putFloat(this.suspensionCompression);
      var1.putFloat(this.suspensionDamping);
   }

    void load(ByteBuffer var1, int var2) {
      this.partId = GameWindow.ReadStringUTF(var1);
      this.bCreated = var1.get() == 1;
      this.lastUpdated = var1.getFloat();
      if (var1.get() == 1) {
    InventoryItem var3 = InventoryItem.loadItem(var1, var2);
         this.item = var3;
      }

      if (var1.get() == 1) {
         if (this.container == nullptr) {
            this.container = std::make_unique<ItemContainer>();
            this.container.parent = this.getVehicle();
            this.container.vehiclePart = this;
         }

         this.container.getItems().clear();
         this.container.ID = 0;
         this.container.load(var1, var2);
      }

      if (var1.get() == 1) {
         this.getModData().load(var1, var2);
      }

      if (var1.get() == 1) {
         if (this.getDeviceData() == nullptr) {
            this.createSignalDevice();
         }

         this.getDeviceData().load(var1, var2, false);
      }

      if (var1.get() == 1) {
         if (this.light == nullptr) {
            this.light = std::make_unique<VehicleLight>();
         }

         this.light.load(var1, var2);
      }

      if (var1.get() == 1) {
         if (this.door == nullptr) {
            this.door = std::make_shared<VehicleDoor>(this);
         }

         this.door.load(var1, var2);
      }

      if (var1.get() == 1) {
         if (this.window == nullptr) {
            this.window = std::make_shared<VehicleWindow>(this);
         }

         this.window.load(var1, var2);
      }

      if (var2 >= 116) {
         this.setCondition(var1.getInt());
      }

      if (var2 >= 118) {
         this.setWheelFriction(var1.getFloat());
         this.setMechanicSkillInstaller(var1.getInt());
      }

      if (var2 >= 119) {
         this.setSuspensionCompression(var1.getFloat());
         this.setSuspensionDamping(var1.getFloat());
      }
   }

    int getWheelIndex() {
      if (this.scriptPart != nullptr && this.scriptPart.wheel != nullptr) {
         for (int var1 = 0; var1 < this.vehicle.script.getWheelCount(); var1++) {
    Wheel var2 = this.vehicle.script.getWheel(var1);
            if (this.scriptPart.wheel == var2.id)) {
    return var1;
            }
         }

         return -1;
      } else {
         return -1;
      }
   }

    void createSpotLight(float var1, float var2, float var3, float var4, float var5, int var6) {
      this.light = this.light == nullptr ? std::make_unique<VehicleLight>() : this.light;
      this.light.offset.set(var1, var2, 0.0F);
      this.light.dist = var3;
      this.light.intensity = var4;
      this.light.dot = var5;
      this.light.focusing = var6;
   }

    VehicleLight getLight() {
      return this.light;
   }

    float getLightDistance() {
      return this.light == nullptr ? 0.0F : 8.0F + 16.0F * this.getCondition() / 100.0F;
   }

    float getLightIntensity() {
      return this.light == nullptr ? 0.0F : 0.5F + 0.25F * this.getCondition() / 100.0F;
   }

    float getLightFocusing() {
      return this.light == nullptr ? 0.0F : 10 + (int)(90.0F * (1.0F - this.getCondition() / 100.0F));
   }

    void setLightActive(bool var1) {
      if (this.light != nullptr && this.light.active != var1) {
         this.light.active = var1;
         if (GameServer.bServer) {
            this.vehicle.updateFlags = (short)(this.vehicle.updateFlags | 8);
         }
      }
   }

    DeviceData createSignalDevice() {
      if (this.deviceData == nullptr) {
         this.deviceData = std::make_shared<DeviceData>(this);
      }

      if (this.chatElement == nullptr) {
         this.chatElement = std::make_shared<ChatElement>(this, 5, "device");
      }

      return this.deviceData;
   }

    bool hasDevicePower() {
      return this.vehicle.getBatteryCharge() > 0.0F;
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

    float getDelta() {
      return this.deviceData != nullptr ? this.deviceData.getPower() : 0.0F;
   }

    void setDelta(float var1) {
      if (this.deviceData != nullptr) {
         this.deviceData.setPower(var1);
      }
   }

    float getX() {
      return this.vehicle.getX();
   }

    float getY() {
      return this.vehicle.getY();
   }

    float getZ() {
      return this.vehicle.getZ();
   }

    IsoGridSquare getSquare() {
      return this.vehicle.getSquare();
   }

    void AddDeviceText(const std::string& var1, float var2, float var3, float var4, const std::string& var5, const std::string& var6, int var7) {
      if (this.deviceData != nullptr && this.deviceData.getIsTurnedOn()) {
         this.deviceData.doReceiveSignal(var7);
         if (this.deviceData.getDeviceVolume() > 0.0F) {
            this.chatElement
               .addChatLine(var1, var2, var3, var4, UIFont.Medium, this.deviceData.getDeviceVolumeRange(), "default", true, true, true, true, true, true);
            if (var6 != nullptr) {
               LuaEventManager.triggerEvent("OnDeviceText", var5, var6, this.getX(), this.getY(), this.getZ(), var1, this);
            }
         }
      }
   }

    bool HasPlayerInRange() {
      return this.hasPlayerInRange;
   }

    bool playerWithinBounds(IsoPlayer var1, float var2) {
      return var1 != nullptr && !var1.isDead()
         ? (var1.getX() > this.getX() - var2 || this.getX() < this.getX() + var2) && (var1.getY() > this.getY() - var2 || this.getY() < this.getY() + var2)
         : false;
   }

    void updateSignalDevice() {
      if (this.deviceData != nullptr) {
         if (this.deviceData.getIsTurnedOn() && this.isInventoryItemUninstalled()) {
            this.deviceData.setIsTurnedOn(false);
         }

         if (GameClient.bClient) {
            this.deviceData.updateSimple();
         } else {
            this.deviceData.update(true, this.hasPlayerInRange);
         }

         if (!GameServer.bServer) {
            this.hasPlayerInRange = false;
            if (this.deviceData.getIsTurnedOn()) {
               for (int var1 = 0; var1 < IsoPlayer.numPlayers; var1++) {
    IsoPlayer var2 = IsoPlayer.players[var1];
                  if (this.playerWithinBounds(var2, this.deviceData.getDeviceVolumeRange() * 0.6F)) {
                     this.hasPlayerInRange = true;
                     break;
                  }
               }
            }

            this.chatElement.setHistoryRange(this.deviceData.getDeviceVolumeRange() * 0.6F);
            this.chatElement.update();
         } else {
            this.hasPlayerInRange = false;
         }
      }
   }

    std::string getCategory() {
      return this.category;
   }

    void setCategory(const std::string& var1) {
      this.category = var1;
   }

    int getCondition() {
      return this.condition;
   }

    void setCondition(int var1) {
      var1 = Math.min(100, var1);
      var1 = Math.max(0, var1);
      if (this.getVehicle().getDriver() != nullptr) {
         if (this.condition > 60 && var1 < 60 && var1 > 40) {
            LuaEventManager.triggerEvent("OnVehicleDamageTexture", this.getVehicle().getDriver());
         }

         if (this.condition > 40 && var1 < 40) {
            LuaEventManager.triggerEvent("OnVehicleDamageTexture", this.getVehicle().getDriver());
         }
      }

      this.condition = var1;
      if (this.getInventoryItem() != nullptr) {
         this.getInventoryItem().setCondition(var1);
      }

      this.getVehicle().bDoDamageOverlay = true;
      if ("lightbar" == this.getId())) {
         this.getVehicle().lightbarLightsMode.set(0);
         this.getVehicle().setLightbarSirenMode(0);
      }

      if (this.scriptPart != nullptr && this.scriptPart.id != nullptr && this.scriptPart.id == "TrailerTrunk")) {
         this.getItemContainer().setCapacity(Math.max(80, var1));
      }
   }

    void damage(int var1) {
      if (this.getWindow() != nullptr) {
         this.getWindow().damage(var1);
      } else {
         this.setCondition(this.getCondition() - var1);
         this.getVehicle().transmitPartCondition(this);
      }
   }

    bool isSpecificItem() {
      return this.specificItem;
   }

    void setSpecificItem(bool var1) {
      this.specificItem = var1;
   }

    float getWheelFriction() {
      return this.wheelFriction;
   }

    void setWheelFriction(float var1) {
      this.wheelFriction = var1;
   }

    int getMechanicSkillInstaller() {
      return this.mechanicSkillInstaller;
   }

    void setMechanicSkillInstaller(int var1) {
      this.mechanicSkillInstaller = var1;
   }

    float getSuspensionDamping() {
      return this.suspensionDamping;
   }

    void setSuspensionDamping(float var1) {
      this.suspensionDamping = var1;
   }

    float getSuspensionCompression() {
      return this.suspensionCompression;
   }

    void setSuspensionCompression(float var1) {
      this.suspensionCompression = var1;
   }

    float getEngineLoudness() {
      return this.engineLoudness;
   }

    void setEngineLoudness(float var1) {
      this.engineLoudness = var1;
   }

    void repair() {
    VehicleScript var1 = this.vehicle.getScript();
    float var2 = this.getContainerContentAmount();
      if (this.isInventoryItemUninstalled()) {
    std::string var3 = this.getItemType().get(Rand.Next(this.getItemType().size()));
         if (var3 != nullptr && !var3.empty()) {
    InventoryItem var4 = InventoryItemFactory.CreateItem(var3);
            if (var4 != nullptr) {
               this.setInventoryItem(var4);
               if (var4.getMaxCapacity() > 0) {
                  var4.setItemCapacity(var4.getMaxCapacity());
               }

               this.vehicle.transmitPartItem(this);
               this.callLuaVoid(this.getLuaFunction("init"), this.vehicle, this);
            }
         }
      }

      if (this.getDoor() != nullptr && this.getDoor().isLockBroken()) {
         this.getDoor().setLockBroken(false);
         this.vehicle.transmitPartDoor(this);
      }

      if (this.getCondition() != 100) {
         this.setCondition(100);
         if (this.getInventoryItem() != nullptr) {
            this.doInventoryItemStats(this.getInventoryItem(), this.getMechanicSkillInstaller());
         }

         this.vehicle.transmitPartCondition(this);
      }

      if (this.isContainer() && this.getItemContainer() == nullptr && var2 != this.getContainerCapacity()) {
         this.setContainerContentAmount(this.getContainerCapacity());
         this.vehicle.transmitPartModData(this);
      }

      if (this.getInventoryItem() instanceof Drainable && ((Drainable)this.getInventoryItem()).getUsedDelta() < 1.0F) {
         ((Drainable)this.getInventoryItem()).setUsedDelta(1.0F);
         this.vehicle.transmitPartUsedDelta(this);
      }

      if ("Engine".equalsIgnoreCase(this.getId())) {
    uint8_t var6 = 100;
    int var7 = (int)(var1.getEngineLoudness() * SandboxOptions.getInstance().ZombieAttractionMultiplier.getValue());
    int var5 = (int)var1.getEngineForce();
         this.vehicle.setEngineFeature(var6, var7, var5);
         this.vehicle.transmitEngine();
      }

      this.vehicle.updatePartStats();
      this.vehicle.updateBulletStats();
   }

    void callLuaVoid(const std::string& var1, void* var2, void* var3) {
    void* var4 = LuaManager.getFunctionObject(var1);
      if (var4 != nullptr) {
         LuaManager.caller.protectedCallVoid(LuaManager.thread, var4, var2, var3);
      }
   }

    ChatElement getChatElement() {
      return this.chatElement;
   }
}
} // namespace vehicles
} // namespace zombie
