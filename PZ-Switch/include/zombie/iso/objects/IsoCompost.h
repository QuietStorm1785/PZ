#pragma once
#include "zombie/GameTime.h"
#include "zombie/SandboxOptions.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/core/Rand.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/inventory/types/Food.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/objects/interfaces/Thumpable.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
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
namespace iso {
namespace objects {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class IsoCompost : public IsoObject {
public:
 float compost = 0.0F;
 float LastUpdated = -1.0F;

public
 IsoCompost(IsoCell cell) { super(cell); }

public
 IsoCompost(IsoCell cell, IsoGridSquare sq) {
 super(cell, sq, IsoSpriteManager.instance.getSprite("camping_01_19"));
 this->sprite = IsoSpriteManager.instance.getSprite("camping_01_19");
 this->square = sq;
 this->container = std::make_unique<ItemContainer>();
 this->container.setType("composter");
 this->container.setParent(this);
 this->container.bExplored = true;
 }

 void update() {
 if (!GameClient.bClient && this->container != nullptr) {
 float float0 = (float)GameTime.getInstance().getWorldAgeHours();
 if (this->LastUpdated < 0.0F) {
 this->LastUpdated = float0;
 } else if (this->LastUpdated > float0) {
 this->LastUpdated = float0;
 }

 float float1 = float0 - this->LastUpdated;
 if (!(float1 <= 0.0F) {
 this->LastUpdated = float0;
 int int0 = SandboxOptions.instance.getCompostHours();

 for (int int1 = 0; int1 < this->container.getItems().size(); int1++) {
 InventoryItem item0 = this->container.getItems().get(int1);
 if (item0 instanceof Food food) {
 if (GameServer.bServer) {
 food.updateAge();
 }

 if (food.isRotten()) {
 if (this->getCompost() < 100.0F) {
 food.setRottenTime(0.0F);
 food.setCompostTime(food.getCompostTime() + float1);
 }

 if (food.getCompostTime() >= int0) {
 this->setCompost(this->getCompost() +
 Math.abs(food.getHungChange()) * 2.0F);
 if (this->getCompost() > 100.0F) {
 this->setCompost(100.0F);
 }

 if (GameServer.bServer) {
 GameServer.sendCompost(this, nullptr);
 GameServer.sendRemoveItemFromContainer(this->container, item0);
 }

 if (Rand.Next(10) == 0) {
 InventoryItem item1 = this->container.AddItem("Base.Worm");
 if (GameServer.bServer && item1 != nullptr) {
 GameServer.sendAddItemToContainer(this->container, item1);
 }
 }

 item0.Use();
 IsoWorld.instance.CurrentCell.addToProcessItemsRemove(item0);
 }
 }
 }
 }

 this->updateSprite();
 }
 }
 }

 void updateSprite() {
 if (this->getCompost() >= 10.0F && this->sprite.getName() == "camping_01_19")) {
 this->sprite = IsoSpriteManager.instance.getSprite("camping_01_20");
 this->transmitUpdatedSpriteToClients();
 }
 else if (this->getCompost() < 10.0F &&
 this->sprite.getName() == "camping_01_20")) {
 this->sprite = IsoSpriteManager.instance.getSprite("camping_01_19");
 this->transmitUpdatedSpriteToClients();
 }
 }

 void syncCompost() {
 if (GameClient.bClient) {
 GameClient.sendCompost(this);
 }
 }

 void load(ByteBuffer input, int WorldVersion, bool IS_DEBUG_SAVE) {
 super.load(input, WorldVersion, IS_DEBUG_SAVE);
 if (this->container != nullptr) {
 this->container.setType("composter");
 }

 this->compost = input.getFloat();
 if (WorldVersion >= 130) {
 this->LastUpdated = input.getFloat();
 }
 }

 void save(ByteBuffer output, bool IS_DEBUG_SAVE) {
 super.save(output, IS_DEBUG_SAVE);
 output.putFloat(this->compost);
 output.putFloat(this->LastUpdated);
 }

 std::string getObjectName() { return "IsoCompost"; }

 float getCompost() { return this->compost; }

 void setCompost(float _compost) {
 this->compost = PZMath.clamp(_compost, 0.0F, 100.0F);
 }

 void remove() {
 if (this->getSquare() != nullptr) {
 this->getSquare().transmitRemoveItemFromSquare(this);
 }
 }

 void addToWorld() { this->getCell().addToProcessIsoObject(this); }

 Thumpable getThumpableFor(IsoGameCharacter chr) {
 return this->isDestroyed() ? nullptr : this;
 }
}
} // namespace objects
} // namespace iso
} // namespace zombie
