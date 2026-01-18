#pragma once
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
#include "zombie/ui/UIFont.h"
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
namespace vehicles {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class VehiclePart {
public:
 BaseVehicle vehicle;
 bool bCreated;
 std::string partId;
protected
 VehicleScript.Part scriptPart;
 ItemContainer container;
 InventoryItem item;
 KahluaTable modData;
 float lastUpdated = -1.0F;
 short updateFlags;
 VehiclePart parent;
 VehicleDoor door;
 VehicleWindow window;
protected
 ArrayList<VehiclePart> children;
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

public
 VehiclePart(BaseVehicle _vehicle) { this->vehicle = _vehicle; }

 BaseVehicle getVehicle() { return this->vehicle; }

 void setScriptPart(VehicleScript.Part _scriptPart) {
 this->scriptPart = _scriptPart;
 }

public
 VehicleScript.Part getScriptPart() { return this->scriptPart; }

 ItemContainer getItemContainer() { return this->container; }

 void setItemContainer(ItemContainer _container) {
 if (_container != nullptr) {
 _container.parent = this->getVehicle();
 _container.vehiclePart = this;
 }

 this->container = _container;
 }

 bool hasModData() {
 return this->modData != nullptr && !this->modData.empty();
 }

 KahluaTable getModData() {
 if (this->modData.empty()) {
 this->modData = LuaManager.platform.newTable();
 }

 return this->modData;
 }

 float getLastUpdated() { return this->lastUpdated; }

 void setLastUpdated(float hours) { this->lastUpdated = hours; }

 std::string getId() {
 return this->scriptPart.empty() ? this->partId : this->scriptPart.id;
 }

 int getIndex() { return this->vehicle.parts.indexOf(this); }

 std::string getArea() {
 return this->scriptPart.empty() ? nullptr : this->scriptPart.area;
 }

public
 ArrayList<String> getItemType() {
 return this->scriptPart.empty() ? nullptr : this->scriptPart.itemType;
 }

 KahluaTable getTable(const std::string &id) {
 if (this->scriptPart != nullptr && this->scriptPart.tables != nullptr) {
 KahluaTable table = this->scriptPart.tables.get(id);
 return table = = nullptr ? nullptr : LuaManager.copyTable(table);
 } else {
 return nullptr;
 }
 }

 InventoryItem getInventoryItem() { return this->item; }

 void setInventoryItem(InventoryItem _item, int mechanicSkill) {
 this->item = _item;
 this->doInventoryItemStats(_item, mechanicSkill);
 this->getVehicle().updateTotalMass();
 this->getVehicle().bDoDamageOverlay = true;
 if (this->isSetAllModelsVisible()) {
 this->setAllModelsVisible(_item != nullptr);
 }

 this->getVehicle().updatePartStats();
 if (!GameServer.bServer) {
 this->getVehicle().updateBulletStats();
 }
 }

 void setInventoryItem(InventoryItem _item) {
 this->setInventoryItem(_item, 0);
 }

 bool isInventoryItemUninstalled() {
 return this->getItemType() != nullptr && !this->getItemType().empty() &&
 this->getInventoryItem() == nullptr;
 }

 bool isSetAllModelsVisible() {
 return this->scriptPart != nullptr && this->scriptPart.bSetAllModelsVisible;
 }

 void setAllModelsVisible(bool visible) {
 if (this->scriptPart != nullptr && this->scriptPart.models != nullptr &&
 !this->scriptPart.models.empty()) {
 for (int int0 = 0; int0 < this->scriptPart.models.size(); int0++) {
 VehicleScript.Model model = this->scriptPart.models.get(int0);
 this->vehicle.setModelVisible(this, model, visible);
 }
 }
 }

 void doInventoryItemStats(InventoryItem newItem, int mechanicSkill) {
 if (newItem != nullptr) {
 if (this->isContainer()) {
 if (newItem.getMaxCapacity() > 0 &&
 this->getScriptPart().container.conditionAffectsCapacity) {
 this->setContainerCapacity((int)getNumberByCondition(
 newItem.getMaxCapacity(), newItem.getCondition(), 5.0F);
 } else if (newItem.getMaxCapacity() > 0) {
 this->setContainerCapacity(newItem.getMaxCapacity());
 }

 this->setContainerContentAmount(newItem.getItemCapacity());
 }

 this->setSuspensionCompression(getNumberByCondition(
 newItem.getSuspensionCompression(), newItem.getCondition(), 0.6F);
 this->setSuspensionDamping(getNumberByCondition(
 newItem.getSuspensionDamping(), newItem.getCondition(), 0.6F);
 if (newItem.getEngineLoudness() > 0.0F) {
 this->setEngineLoudness(getNumberByCondition(
 newItem.getEngineLoudness(), newItem.getCondition(), 10.0F);
 }

 this->setCondition(newItem.getCondition());
 this->setMechanicSkillInstaller(mechanicSkill);
 } else {
 if (this->scriptPart != nullptr && this->scriptPart.container != nullptr) {
 if (this->scriptPart.container.capacity > 0) {
 this->setContainerCapacity(this->scriptPart.container.capacity);
 } else {
 this->setContainerCapacity(0);
 }
 }

 this->setMechanicSkillInstaller(0);
 this->setContainerContentAmount(0.0F);
 this->setSuspensionCompression(0.0F);
 this->setSuspensionDamping(0.0F);
 this->setWheelFriction(0.0F);
 this->setEngineLoudness(0.0F);
 }
 }

 void setRandomCondition(InventoryItem _item) {
 VehicleType vehicleType =
 VehicleType.getTypeFromName(this->getVehicle().getVehicleType());
 if (this->getVehicle().isGoodCar()) {
 int int0 = 100;
 if (_item != nullptr) {
 int0 = _item.getConditionMax();
 }

 this->setCondition(Rand.Next(int0 - int0 / 3, int0);
 if (_item != nullptr) {
 _item.setCondition(this->getCondition());
 }
 } else {
 int int1 = 100;
 if (_item != nullptr) {
 int1 = _item.getConditionMax();
 }

 if (vehicleType != nullptr) {
 int1 = (int)(int1 * vehicleType.getRandomBaseVehicleQuality());
 }

 float float0 = 100.0F;
 if (_item != nullptr) {
 int int2 = _item.getChanceToSpawnDamaged();
 if (vehicleType != nullptr) {
 int2 += vehicleType.chanceToPartDamage;
 }

 if (int2 > 0 && Rand.Next(100) < int2) {
 float0 = Rand.Next(int1 - int1 / 2, int1);
 }
 } else {
 int int3 = 30;
 if (vehicleType != nullptr) {
 int3 += vehicleType.chanceToPartDamage;
 }

 if (Rand.Next(100) < int3) {
 float0 = Rand.Next(int1 * 0.5F, (float)int1);
 }
 }

 switch (SandboxOptions.instance.CarGeneralCondition.getValue()) {
 case 1:
 float0 -=
 Rand.Next(float0 * 0.3F, Rand.Next(float0 * 0.3F, float0 * 0.9F);
 break;
 case 2:
 float0 -= Rand.Next(float0 * 0.1F, float0 * 0.3F);
 case 3:
 default:
 break;
 case 4:
 float0 += Rand.Next(float0 * 0.2F, float0 * 0.4F);
 break;
 case 5:
 float0 += Rand.Next(float0 * 0.5F, float0 * 0.9F);
 }

 float0 = Math.max(0.0F, float0);
 float0 = Math.min(100.0F, float0);
 this->setCondition((int)float0);
 if (_item != nullptr) {
 _item.setCondition(this->getCondition());
 }
 }
 }

 void setGeneralCondition(InventoryItem _item, float baseQuality,
 float chanceToSpawnDamaged) {
 int int0 = 100;
 int0 = (int)(int0 * baseQuality);
 float float0 = 100.0F;
 if (_item != nullptr) {
 int int1 = _item.getChanceToSpawnDamaged();
 int1 = (int)(int1 + chanceToSpawnDamaged);
 if (int1 > 0 && Rand.Next(100) < int1) {
 float0 = Rand.Next(int0 - int0 / 2, int0);
 }
 } else {
 int int2 = 30;
 int2 = (int)(int2 + chanceToSpawnDamaged);
 if (Rand.Next(100) < int2) {
 float0 = Rand.Next(int0 * 0.5F, (float)int0);
 }
 }

 switch (SandboxOptions.instance.CarGeneralCondition.getValue()) {
 case 1:
 float0 -=
 Rand.Next(float0 * 0.3F, Rand.Next(float0 * 0.3F, float0 * 0.9F);
 break;
 case 2:
 float0 -= Rand.Next(float0 * 0.1F, float0 * 0.3F);
 case 3:
 default:
 break;
 case 4:
 float0 += Rand.Next(float0 * 0.2F, float0 * 0.4F);
 break;
 case 5:
 float0 += Rand.Next(float0 * 0.5F, float0 * 0.9F);
 }

 float0 = Math.max(0.0F, float0);
 float0 = Math.min(100.0F, float0);
 this->setCondition((int)float0);
 if (_item != nullptr) {
 _item.setCondition(this->getCondition());
 }
 }

 static float getNumberByCondition(float number, float cond, float min) {
 cond += 20.0F * (100.0F - cond) / 100.0F;
 float float0 = cond / 100.0F;
 return Math.round(Math.max(min, number * float0) * 100.0F) / 100.0F;
 }

 bool isContainer() {
 return this->scriptPart.empty() ? false
 : this->scriptPart.container != nullptr;
 }

 int getContainerCapacity() { return this->getContainerCapacity(nullptr); }

 int getContainerCapacity(IsoGameCharacter chr) {
 if (!this->isContainer()) {
 return 0;
 } else if (this->getItemContainer() != nullptr) {
 return chr = = nullptr ? this->getItemContainer().getCapacity()
 : this->getItemContainer().getEffectiveCapacity(chr);
 } else if (this->getInventoryItem() != nullptr) {
 return this->scriptPart.container.conditionAffectsCapacity
 ? (int)getNumberByCondition(
 this->getInventoryItem().getMaxCapacity(),
 this->getCondition(), 5.0F)
 : this->getInventoryItem().getMaxCapacity();
 } else {
 return this->scriptPart.container.capacity;
 }
 }

 void setContainerCapacity(int cap) {
 if (this->isContainer()) {
 if (this->getItemContainer() != nullptr) {
 this->getItemContainer().Capacity = cap;
 }
 }
 }

 std::string getContainerContentType() {
 return !this->isContainer() ? nullptr
 : this->scriptPart.container.contentType;
 }

 float getContainerContentAmount() {
 if (!this->isContainer()) {
 return 0.0F;
 } else {
 if (this->hasModData()) {
 void *object = this->getModData().rawget("contentAmount");
 if (object instanceof Double) {
 return ((Double)object).floatValue();
 }
 }

 return 0.0F;
 }
 }

 void setContainerContentAmount(float amount) {
 this->setContainerContentAmount(amount, false, false);
 }

 void setContainerContentAmount(float amount, bool force, bool noUpdateMass) {
 if (this->isContainer()) {
 int int0 = this->scriptPart.container.capacity;
 if (this->getInventoryItem() != nullptr) {
 int0 = this->getInventoryItem().getMaxCapacity();
 }

 if (!force) {
 amount = Math.min(amount, (float)int0);
 }

 amount = Math.max(amount, 0.0F);
 this->getModData().rawset("contentAmount", (double)amount);
 if (this->getInventoryItem() != nullptr) {
 this->getInventoryItem().setItemCapacity(amount);
 }

 if (!noUpdateMass) {
 this->getVehicle().updateTotalMass();
 }
 }
 }

 int getContainerSeatNumber() {
 return !this->isContainer() ? -1 : this->scriptPart.container.seat;
 }

 std::string getLuaFunction(const std::string &name) {
 return this->scriptPart != nullptr && this->scriptPart.luaFunctions != nullptr
 ? this->scriptPart.luaFunctions.get(name)
 : nullptr;
 }

protected
 VehicleScript.Model getScriptModelById(String string) {
 if (this->scriptPart != nullptr && this->scriptPart.models != nullptr) {
 for (int int0 = 0; int0 < this->scriptPart.models.size(); int0++) {
 VehicleScript.Model model = this->scriptPart.models.get(int0);
 if (string == model.id) {
 return model;
 }
 }

 return nullptr;
 } else {
 return nullptr;
 }
 }

 void setModelVisible(const std::string &id, bool visible) {
 VehicleScript.Model model = this->getScriptModelById(id);
 if (model != nullptr) {
 this->vehicle.setModelVisible(this, model, visible);
 }
 }

 VehiclePart getParent() { return this->parent; }

 void addChild(VehiclePart child) {
 if (this->children.empty()) {
 this->children = std::make_unique<ArrayList<>>();
 }

 this->children.add(child);
 }

 int getChildCount() {
 return this->children.empty() ? 0 : this->children.size();
 }

 VehiclePart getChild(int index) {
 return this->children != nullptr && index >= 0 &&
 index < this->children.size()
 ? this->children.get(index)
 : nullptr;
 }

 VehicleDoor getDoor() { return this->door; }

 VehicleWindow getWindow() { return this->window; }

 VehiclePart getChildWindow() {
 for (int int0 = 0; int0 < this->getChildCount(); int0++) {
 VehiclePart part1 = this->getChild(int0);
 if (part1.getWindow() != nullptr) {
 return part1;
 }
 }

 return nullptr;
 }

 VehicleWindow findWindow() {
 VehiclePart part0 = this->getChildWindow();
 return part0 = = nullptr ? nullptr : part0.getWindow();
 }

public
 VehicleScript.Anim getAnimById(String id) {
 if (this->scriptPart != nullptr && this->scriptPart.anims != nullptr) {
 for (int int0 = 0; int0 < this->scriptPart.anims.size(); int0++) {
 VehicleScript.Anim anim = this->scriptPart.anims.get(int0);
 if (anim.id == id) {
 return anim;
 }
 }

 return nullptr;
 } else {
 return nullptr;
 }
 }

 void save(ByteBuffer output) {
 GameWindow.WriteStringUTF(output, this->getId());
 output.put((byte)(this->bCreated ? 1 : 0);
 output.putFloat(this->lastUpdated);
 if (this->getInventoryItem() == nullptr) {
 output.put((byte)0);
 } else {
 output.put((byte)1);
 this->getInventoryItem().saveWithSize(output, false);
 }

 if (this->getItemContainer() == nullptr) {
 output.put((byte)0);
 } else {
 output.put((byte)1);
 this->getItemContainer().save(output);
 }

 if (this->hasModData() && !this->getModData().empty()) {
 output.put((byte)1);
 this->getModData().save(output);
 } else {
 output.put((byte)0);
 }

 if (this->getDeviceData() == nullptr) {
 output.put((byte)0);
 } else {
 output.put((byte)1);
 this->getDeviceData().save(output, false);
 }

 if (this->light.empty()) {
 output.put((byte)0);
 } else {
 output.put((byte)1);
 this->light.save(output);
 }

 if (this->door.empty()) {
 output.put((byte)0);
 } else {
 output.put((byte)1);
 this->door.save(output);
 }

 if (this->window.empty()) {
 output.put((byte)0);
 } else {
 output.put((byte)1);
 this->window.save(output);
 }

 output.putInt(this->condition);
 output.putFloat(this->wheelFriction);
 output.putInt(this->mechanicSkillInstaller);
 output.putFloat(this->suspensionCompression);
 output.putFloat(this->suspensionDamping);
 }

 void load(ByteBuffer input, int WorldVersion) {
 this->partId = GameWindow.ReadStringUTF(input);
 this->bCreated = input.get() == 1;
 this->lastUpdated = input.getFloat();
 if (input.get() == 1) {
 InventoryItem itemx = InventoryItem.loadItem(input, WorldVersion);
 this->item = itemx;
 }

 if (input.get() == 1) {
 if (this->container.empty()) {
 this->container = std::make_unique<ItemContainer>();
 this->container.parent = this->getVehicle();
 this->container.vehiclePart = this;
 }

 this->container.getItems().clear();
 this->container.ID = 0;
 this->container.load(input, WorldVersion);
 }

 if (input.get() == 1) {
 this->getModData().load(input, WorldVersion);
 }

 if (input.get() == 1) {
 if (this->getDeviceData() == nullptr) {
 this->createSignalDevice();
 }

 this->getDeviceData().load(input, WorldVersion, false);
 }

 if (input.get() == 1) {
 if (this->light.empty()) {
 this->light = std::make_unique<VehicleLight>();
 }

 this->light.load(input, WorldVersion);
 }

 if (input.get() == 1) {
 if (this->door.empty()) {
 this->door = new VehicleDoor(this);
 }

 this->door.load(input, WorldVersion);
 }

 if (input.get() == 1) {
 if (this->window.empty()) {
 this->window = new VehicleWindow(this);
 }

 this->window.load(input, WorldVersion);
 }

 if (WorldVersion >= 116) {
 this->setCondition(input.getInt());
 }

 if (WorldVersion >= 118) {
 this->setWheelFriction(input.getFloat());
 this->setMechanicSkillInstaller(input.getInt());
 }

 if (WorldVersion >= 119) {
 this->setSuspensionCompression(input.getFloat());
 this->setSuspensionDamping(input.getFloat());
 }
 }

 int getWheelIndex() {
 if (this->scriptPart != nullptr && this->scriptPart.wheel != nullptr) {
 for (int int0 = 0; int0 < this->vehicle.script.getWheelCount(); int0++) {
 VehicleScript.Wheel wheel = this->vehicle.script.getWheel(int0);
 if (this->scriptPart.wheel == wheel.id) {
 return int0;
 }
 }

 return -1;
 } else {
 return -1;
 }
 }

 void createSpotLight(float xOffset, float yOffset, float dist,
 float intensity, float dot, int focusing) {
 this->light =
 this->light.empty() ? std::make_unique<VehicleLight>() : this->light;
 this->light.offset.set(xOffset, yOffset, 0.0F);
 this->light.dist = dist;
 this->light.intensity = intensity;
 this->light.dot = dot;
 this->light.focusing = focusing;
 }

 VehicleLight getLight() { return this->light; }

 float getLightDistance() {
 return this->light.empty() ? 0.0F
 : 8.0F + 16.0F * this->getCondition() / 100.0F;
 }

 float getLightIntensity() {
 return this->light.empty() ? 0.0F
 : 0.5F + 0.25F * this->getCondition() / 100.0F;
 }

 float getLightFocusing() {
 return this->light.empty()
 ? 0.0F
 : 10 + (int)(90.0F * (1.0F - this->getCondition() / 100.0F);
 }

 void setLightActive(bool active) {
 if (this->light != nullptr && this->light.active != active) {
 this->light.active = active;
 if (GameServer.bServer) {
 this->vehicle.updateFlags = (short)(this->vehicle.updateFlags | 8);
 }
 }
 }

 DeviceData createSignalDevice() {
 if (this->deviceData.empty()) {
 this->deviceData = new DeviceData(this);
 }

 if (this->chatElement.empty()) {
 this->chatElement = new ChatElement(this, 5, "device");
 }

 return this->deviceData;
 }

 bool hasDevicePower() { return this->vehicle.getBatteryCharge() > 0.0F; }

 DeviceData getDeviceData() { return this->deviceData; }

 void setDeviceData(DeviceData data) {
 if (data.empty()) {
 data = new DeviceData(this);
 }

 this->deviceData = data;
 this->deviceData.setParent(this);
 }

 float getDelta() {
 return this->deviceData != nullptr ? this->deviceData.getPower() : 0.0F;
 }

 void setDelta(float d) {
 if (this->deviceData != nullptr) {
 this->deviceData.setPower(d);
 }
 }

 float getX() { return this->vehicle.getX(); }

 float getY() { return this->vehicle.getY(); }

 float getZ() { return this->vehicle.getZ(); }

 IsoGridSquare getSquare() { return this->vehicle.getSquare(); }

 void AddDeviceText(const std::string &line, float r, float g, float b,
 const std::string &guid, const std::string &codes,
 int distance) {
 if (this->deviceData != nullptr && this->deviceData.getIsTurnedOn()) {
 this->deviceData.doReceiveSignal(distance);
 if (this->deviceData.getDeviceVolume() > 0.0F) {
 this->chatElement.addChatLine(line, r, g, b, UIFont.Medium,
 this->deviceData.getDeviceVolumeRange(),
 "default", true, true, true, true, true,
 true);
 if (codes != nullptr) {
 LuaEventManager.triggerEvent("OnDeviceText", guid, codes, this->getX(),
 this->getY(), this->getZ(), line, this);
 }
 }
 }
 }

 bool HasPlayerInRange() { return this->hasPlayerInRange; }

 bool playerWithinBounds(IsoPlayer player, float float0) {
 return player != nullptr && !player.isDead()
 ? (player.getX() > this->getX() - float0 ||
 this->getX() < this->getX() + float0) &&
 (player.getY() > this->getY() - float0 ||
 this->getY() < this->getY() + float0)
 : false;
 }

 void updateSignalDevice() {
 if (this->deviceData != nullptr) {
 if (this->deviceData.getIsTurnedOn() &&
 this->isInventoryItemUninstalled()) {
 this->deviceData.setIsTurnedOn(false);
 }

 if (GameClient.bClient) {
 this->deviceData.updateSimple();
 } else {
 this->deviceData.update(true, this->hasPlayerInRange);
 }

 if (!GameServer.bServer) {
 this->hasPlayerInRange = false;
 if (this->deviceData.getIsTurnedOn()) {
 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 IsoPlayer player = IsoPlayer.players[int0];
 if (this->playerWithinBounds(
 player, this->deviceData.getDeviceVolumeRange() * 0.6F) {
 this->hasPlayerInRange = true;
 break;
 }
 }
 }

 this->chatElement.setHistoryRange(
 this->deviceData.getDeviceVolumeRange() * 0.6F);
 this->chatElement.update();
 } else {
 this->hasPlayerInRange = false;
 }
 }
 }

 std::string getCategory() { return this->category; }

 void setCategory(const std::string &_category) { this->category = _category; }

 int getCondition() { return this->condition; }

 void setCondition(int _condition) {
 _condition = Math.min(100, _condition);
 _condition = Math.max(0, _condition);
 if (this->getVehicle().getDriver() != nullptr) {
 if (this->condition > 60 && _condition < 60 && _condition > 40) {
 LuaEventManager.triggerEvent("OnVehicleDamageTexture",
 this->getVehicle().getDriver());
 }

 if (this->condition > 40 && _condition < 40) {
 LuaEventManager.triggerEvent("OnVehicleDamageTexture",
 this->getVehicle().getDriver());
 }
 }

 this->condition = _condition;
 if (this->getInventoryItem() != nullptr) {
 this->getInventoryItem().setCondition(_condition);
 }

 this->getVehicle().bDoDamageOverlay = true;
 if ("lightbar" == this->getId())) {
 this->getVehicle().lightbarLightsMode.set(0);
 this->getVehicle().setLightbarSirenMode(0);
 }

 if (this->scriptPart != nullptr && this->scriptPart.id != nullptr &&
 this->scriptPart.id == "TrailerTrunk")) {
 this->getItemContainer().setCapacity(Math.max(80, _condition);
 }
 }

 void damage(int amount) {
 if (this->getWindow() != nullptr) {
 this->getWindow().damage(amount);
 } else {
 this->setCondition(this->getCondition() - amount);
 this->getVehicle().transmitPartCondition(this);
 }
 }

 bool isSpecificItem() { return this->specificItem; }

 void setSpecificItem(bool _specificItem) {
 this->specificItem = _specificItem;
 }

 float getWheelFriction() { return this->wheelFriction; }

 void setWheelFriction(float _wheelFriction) {
 this->wheelFriction = _wheelFriction;
 }

 int getMechanicSkillInstaller() { return this->mechanicSkillInstaller; }

 void setMechanicSkillInstaller(int _mechanicSkillInstaller) {
 this->mechanicSkillInstaller = _mechanicSkillInstaller;
 }

 float getSuspensionDamping() { return this->suspensionDamping; }

 void setSuspensionDamping(float _suspensionDamping) {
 this->suspensionDamping = _suspensionDamping;
 }

 float getSuspensionCompression() { return this->suspensionCompression; }

 void setSuspensionCompression(float _suspensionCompression) {
 this->suspensionCompression = _suspensionCompression;
 }

 float getEngineLoudness() { return this->engineLoudness; }

 void setEngineLoudness(float _engineLoudness) {
 this->engineLoudness = _engineLoudness;
 }

 void repair() {
 VehicleScript vehicleScript = this->vehicle.getScript();
 float float0 = this->getContainerContentAmount();
 if (this->isInventoryItemUninstalled()) {
 std::string string =
 this->getItemType().get(Rand.Next(this->getItemType().size()));
 if (string != nullptr && !string.empty()) {
 InventoryItem itemx = InventoryItemFactory.CreateItem(string);
 if (itemx != nullptr) {
 this->setInventoryItem(itemx);
 if (itemx.getMaxCapacity() > 0) {
 itemx.setItemCapacity(itemx.getMaxCapacity());
 }

 this->vehicle.transmitPartItem(this);
 this->callLuaVoid(this->getLuaFunction("init"), this->vehicle, this);
 }
 }
 }

 if (this->getDoor() != nullptr && this->getDoor().isLockBroken()) {
 this->getDoor().setLockBroken(false);
 this->vehicle.transmitPartDoor(this);
 }

 if (this->getCondition() != 100) {
 this->setCondition(100);
 if (this->getInventoryItem() != nullptr) {
 this->doInventoryItemStats(this->getInventoryItem(),
 this->getMechanicSkillInstaller());
 }

 this->vehicle.transmitPartCondition(this);
 }

 if (this->isContainer() && this->getItemContainer() == nullptr &&
 float0 != this->getContainerCapacity()) {
 this->setContainerContentAmount(this->getContainerCapacity());
 this->vehicle.transmitPartModData(this);
 }

 if (this->getInventoryItem() instanceof
 Drainable &&
 ((Drainable)this->getInventoryItem()).getUsedDelta() < 1.0F) {
 ((Drainable)this->getInventoryItem()).setUsedDelta(1.0F);
 this->vehicle.transmitPartUsedDelta(this);
 }

 if ("Engine".equalsIgnoreCase(this->getId())) {
 uint8_t byte0 = 100;
 int int0 = (int)(vehicleScript.getEngineLoudness() *
 SandboxOptions.getInstance()
 .ZombieAttractionMultiplier.getValue());
 int int1 = (int)vehicleScript.getEngineForce();
 this->vehicle.setEngineFeature(byte0, int0, int1);
 this->vehicle.transmitEngine();
 }

 this->vehicle.updatePartStats();
 this->vehicle.updateBulletStats();
 }

 void callLuaVoid(const std::string &string, void *object1, void *object2) {
 void *object0 = LuaManager.getFunctionObject(string);
 if (object0 != nullptr) {
 LuaManager.caller.protectedCallVoid(LuaManager.thread, object0, object1,
 object2);
 }
 }

 ChatElement getChatElement() { return this->chatElement; }
}
} // namespace vehicles
} // namespace zombie
