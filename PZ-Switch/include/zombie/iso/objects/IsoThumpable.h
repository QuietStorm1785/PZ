#pragma once
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/SandboxOptions.h"
#include "zombie/SystemDisabler.h"
#include "zombie/WorldSoundManager.h"
#include "zombie/ai/states/ThumpState.h"
#include "zombie/characters/BaseCharacterSoundEmitter.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoSurvivor.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Translator.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/properties/PropertyContainer.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/inventory/types/DrainableComboItem.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/iso/BrokenFences.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoLightSource.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/LosUtil.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/SpriteDetails/IsoObjectType.h"
#include "zombie/iso/Vector2.h"
#include "zombie/iso/objects/interfaces/BarricadeAble.h"
#include "zombie/iso/objects/interfaces/Thumpable.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/PacketTypes.h"
#include "zombie/util/Type.h"
#include "zombie/util/io/BitHeader.h"
#include "zombie/util/io/BitHeaderRead.h"
#include "zombie/util/io/BitHeaderWrite.h"
#include "zombie/world/WorldDictionary.h"
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace iso {
namespace objects {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class IsoThumpable : public IsoObject {
public:
 KahluaTable table;
 KahluaTable modData;
 bool isDoor = false;
 bool isDoorFrame = false;
 std::string breakSound = "BreakObject";
 bool isCorner = false;
 bool isFloor = false;
 bool blockAllTheSquare = false;
 bool Locked = false;
 int MaxHealth = 500;
 int Health = 500;
 int PushedMaxStrength = 0;
 int PushedStrength = 0;
 IsoSprite closedSprite;
 bool north = false;
 int thumpDmg = 8;
 float crossSpeed = 1.0F;
 bool open = false;
 IsoSprite openSprite;
 bool destroyed = false;
 bool canBarricade = false;
 bool canPassThrough = false;
 bool isStairs = false;
 bool isContainer = false;
 bool dismantable = false;
 bool canBePlastered = false;
 bool paintable = false;
 bool isThumpable = true;
 bool isHoppable = false;
 int lightSourceRadius = -1;
 int lightSourceLife = -1;
 int lightSourceXOffset = 0;
 int lightSourceYOffset = 0;
 bool lightSourceOn = false;
 IsoLightSource lightSource = nullptr;
 std::string lightSourceFuel = nullptr;
 float lifeLeft = -1.0F;
 float lifeDelta = 0.0F;
 bool haveFuel = false;
 float updateAccumulator = 0.0F;
 float lastUpdateHours = -1.0F;
 int keyId = -1;
 bool lockedByKey = false;
 bool lockedByPadlock = false;
 bool canBeLockByPadlock = false;
 int lockedByCode = 0;
 int OldNumPlanks = 0;
 std::string thumpSound = "ZombieThumpGeneric";
 static const Vector2 tempo = new Vector2();

 KahluaTable getModData() {
 if (this->modData.empty()) {
 this->modData = LuaManager.platform.newTable();
 }

 return this->modData;
 }

 void setModData(KahluaTable _modData) { this->modData = _modData; }

 bool hasModData() {
 return this->modData != nullptr && !this->modData.empty();
 }

 /**
 * Can you pass through the item, if false we gonna test the collide default
 * to false (so it collide)
 */
 bool isCanPassThrough() { return this->canPassThrough; }

 void setCanPassThrough(bool pCanPassThrough) {
 this->canPassThrough = pCanPassThrough;
 }

 bool isBlockAllTheSquare() { return this->blockAllTheSquare; }

 void setBlockAllTheSquare(bool _blockAllTheSquare) {
 this->blockAllTheSquare = _blockAllTheSquare;
 }

 void setIsDismantable(bool _dismantable) { this->dismantable = _dismantable; }

 bool isDismantable() { return this->dismantable; }

 float getCrossSpeed() { return this->crossSpeed; }

 void setCrossSpeed(float pCrossSpeed) { this->crossSpeed = pCrossSpeed; }

 void setIsFloor(bool pIsFloor) { this->isFloor = pIsFloor; }

 bool isCorner() { return this->isCorner; }

 bool isFloor() { return this->isFloor; }

 void setIsContainer(bool pIsContainer) {
 this->isContainer = pIsContainer;
 if (pIsContainer) {
 this->container = new ItemContainer("crate", this->square, this);
 if (this->sprite.getProperties().Is("ContainerCapacity")) {
 this->container.Capacity = Integer.parseInt(
 this->sprite.getProperties().Val("ContainerCapacity"));
 }

 this->container.setExplored(true);
 }
 }

 void setIsStairs(bool pStairs) { this->isStairs = pStairs; }

 bool isStairs() { return this->isStairs; }

 bool isWindow() {
 return this->sprite != nullptr &&
 (this->sprite.getProperties().Is(IsoFlagType.WindowN) ||
 this->sprite.getProperties().Is(IsoFlagType.WindowW);
 }

 std::string getObjectName() { return "Thumpable"; }

public
 IsoThumpable(IsoCell cell) { super(cell); }

 void setCorner(bool pCorner) { this->isCorner = pCorner; }

 /**
 * Can you barricade/unbarricade the item default true
 */
 void setCanBarricade(bool pCanBarricade) {
 this->canBarricade = pCanBarricade;
 }

 /**
 * Can you barricade/unbarricade the item
 */
 bool getCanBarricade() { return this->canBarricade; }

 void setHealth(int health) { this->Health = health; }

 int getHealth() { return this->Health; }

 void setMaxHealth(int maxHealth) { this->MaxHealth = maxHealth; }

 int getMaxHealth() { return this->MaxHealth; }

 /**
 * Numbers of zeds need to hurt the object default 8
 */
 void setThumpDmg(int pThumpDmg) { this->thumpDmg = pThumpDmg; }

 int getThumpDmg() { return this->thumpDmg; }

 /**
 * The sound that be played if this object is broken default "BreakDoor"
 */
 void setBreakSound(std::string_view pBreakSound) {
 this->breakSound = pBreakSound;
 }

 std::string getBreakSound() { return this->breakSound; }

 bool isDoor() { return this->isDoor; }

 bool getNorth() { return this->north; }

 Vector2 getFacingPosition(Vector2 pos) {
 if (this->square.empty()) {
 return pos.set(0.0F, 0.0F);
 } else if (this->isDoor || this->isDoorFrame || this->isWindow() ||
 this->isHoppable ||
 this->getProperties() != nullptr &&
 (this->getProperties().Is(IsoFlagType.collideN) ||
 this->getProperties().Is(IsoFlagType.collideW)) {
 return this->north ? pos.set(this->getX() + 0.5F, this->getY())
 : pos.set(this->getX(), this->getY() + 0.5F);
 } else {
 return pos.set(this->getX() + 0.5F, this->getY() + 0.5F);
 }
 }

 bool isDoorFrame() { return this->isDoorFrame; }

 void setIsDoor(bool pIsDoor) { this->isDoor = pIsDoor; }

 void setIsDoorFrame(bool pIsDoorFrame) { this->isDoorFrame = pIsDoorFrame; }

 void setSprite(std::string_view sprite) {
 this->closedSprite = IsoSpriteManager.instance.getSprite(sprite);
 this->sprite = this->closedSprite;
 }

 void setSpriteFromName(std::string_view name) {
 this->sprite = IsoSpriteManager.instance.getSprite(name);
 }

 void setClosedSprite(IsoSprite sprite) {
 this->closedSprite = sprite;
 this->sprite = this->closedSprite;
 }

 void setOpenSprite(IsoSprite sprite) { this->openSprite = sprite; }

 /**
 * Create an object than can be interacted by you, survivor or zombie
 * (destroy, barricade, etc.) This one have a closed/openSprite so it can be a
 * door for example
 */
public
 IsoThumpable(IsoCell cell, IsoGridSquare gridSquare,
 std::string_view _closedSprite, std::string_view _openSprite,
 bool _north, KahluaTable _table) {
 this->OutlineOnMouseover = true;
 this->PushedMaxStrength = this->PushedStrength = 2500;
 this->openSprite = IsoSpriteManager.instance.getSprite(_openSprite);
 this->closedSprite = IsoSpriteManager.instance.getSprite(_closedSprite);
 this->table = _table;
 this->sprite = this->closedSprite;
 this->square = gridSquare;
 this->north = _north;
 }

 /**
 * Create an object than can be interacted by you, survivor or zombie
 * (destroy, barricade, etc.) This one can be a wall, a fence, etc.
 */
public
 IsoThumpable(IsoCell cell, IsoGridSquare gridSquare,
 std::string_view sprite, bool _north, KahluaTable _table) {
 this->OutlineOnMouseover = true;
 this->PushedMaxStrength = this->PushedStrength = 2500;
 this->closedSprite = IsoSpriteManager.instance.getSprite(sprite);
 this->table = _table;
 this->sprite = this->closedSprite;
 this->square = gridSquare;
 this->north = _north;
 }

 void load(ByteBuffer input, int WorldVersion, bool IS_DEBUG_SAVE) {
 super.load(input, WorldVersion, IS_DEBUG_SAVE);
 BitHeaderRead bitHeaderRead =
 BitHeader.allocRead(BitHeader.HeaderSize.Long, input);
 this->OutlineOnMouseover = true;
 this->PushedMaxStrength = this->PushedStrength = 2500;
 if (!bitHeaderRead == 0) {
 this->open = bitHeaderRead.hasFlags(1);
 this->Locked = bitHeaderRead.hasFlags(2);
 this->north = bitHeaderRead.hasFlags(4);
 if (bitHeaderRead.hasFlags(8) {
 this->MaxHealth = input.getInt();
 }

 if (bitHeaderRead.hasFlags(16) {
 this->Health = input.getInt();
 } else {
 this->Health = this->MaxHealth;
 }

 if (bitHeaderRead.hasFlags(32) {
 this->closedSprite =
 IsoSprite.getSprite(IsoSpriteManager.instance, input.getInt());
 }

 if (bitHeaderRead.hasFlags(64) {
 this->openSprite =
 IsoSprite.getSprite(IsoSpriteManager.instance, input.getInt());
 }

 if (bitHeaderRead.hasFlags(128) {
 this->thumpDmg = input.getInt();
 }

 this->isDoor = bitHeaderRead.hasFlags(512);
 this->isDoorFrame = bitHeaderRead.hasFlags(1024);
 this->isCorner = bitHeaderRead.hasFlags(2048);
 this->isStairs = bitHeaderRead.hasFlags(4096);
 this->isContainer = bitHeaderRead.hasFlags(8192);
 this->isFloor = bitHeaderRead.hasFlags(16384);
 this->canBarricade = bitHeaderRead.hasFlags(32768);
 this->canPassThrough = bitHeaderRead.hasFlags(65536);
 this->dismantable = bitHeaderRead.hasFlags(131072);
 this->canBePlastered = bitHeaderRead.hasFlags(262144);
 this->paintable = bitHeaderRead.hasFlags(524288);
 if (bitHeaderRead.hasFlags(1048576) {
 this->crossSpeed = input.getFloat();
 }

 if (bitHeaderRead.hasFlags(2097152) {
 if (this->table.empty()) {
 this->table = LuaManager.platform.newTable();
 }

 this->table.load(input, WorldVersion);
 }

 if (bitHeaderRead.hasFlags(4194304) {
 if (this->modData.empty()) {
 this->modData = LuaManager.platform.newTable();
 }

 this->modData.load(input, WorldVersion);
 }

 this->blockAllTheSquare = bitHeaderRead.hasFlags(8388608);
 this->isThumpable = bitHeaderRead.hasFlags(16777216);
 this->isHoppable = bitHeaderRead.hasFlags(33554432);
 if (bitHeaderRead.hasFlags(67108864) {
 this->setLightSourceLife(input.getInt());
 }

 if (bitHeaderRead.hasFlags(134217728) {
 this->setLightSourceRadius(input.getInt());
 }

 if (bitHeaderRead.hasFlags(268435456) {
 this->setLightSourceXOffset(input.getInt());
 }

 if (bitHeaderRead.hasFlags(536870912) {
 this->setLightSourceYOffset(input.getInt());
 }

 if (bitHeaderRead.hasFlags(1073741824) {
 this->setLightSourceFuel(
 WorldDictionary.getItemTypeFromID(input.getShort()));
 }

 if (bitHeaderRead.hasFlags(2147483648L) {
 this->setLifeDelta(input.getFloat());
 }

 if (bitHeaderRead.hasFlags(4294967296L) {
 this->setLifeLeft(input.getFloat());
 }

 if (bitHeaderRead.hasFlags(8589934592L) {
 this->keyId = input.getInt();
 }

 this->lockedByKey = bitHeaderRead.hasFlags(17179869184L);
 this->lockedByPadlock = bitHeaderRead.hasFlags(34359738368L);
 this->canBeLockByPadlock = bitHeaderRead.hasFlags(68719476736L);
 if (bitHeaderRead.hasFlags(137438953472L) {
 this->lockedByCode = input.getInt();
 }

 if (bitHeaderRead.hasFlags(274877906944L) {
 this->thumpSound = GameWindow.ReadString(input);
 if ("thumpa2" == this->thumpSound) {
 this->thumpSound = "ZombieThumpGeneric";
 }

 if ("metalthump" == this->thumpSound) {
 this->thumpSound = "ZombieThumpMetal";
 }
 }

 if (bitHeaderRead.hasFlags(549755813888L) {
 this->lastUpdateHours = input.getFloat();
 }

 if (WorldVersion >= 183) {
 if (bitHeaderRead.hasFlags(1099511627776L) {
 this->haveFuel = true;
 }

 if (bitHeaderRead.hasFlags(2199023255552L) {
 this->lightSourceOn = true;
 }
 }
 }

 bitHeaderRead.release();
 if (this->getLightSourceFuel() != nullptr) {
 bool boolean0 = this->isLightSourceOn();
 this->createLightSource(
 this->getLightSourceRadius(), this->getLightSourceXOffset(),
 this->getLightSourceYOffset(), 0, this->getLightSourceLife(),
 this->getLightSourceFuel(), nullptr, nullptr);
 if (this->lightSource != nullptr) {
 this->getLightSource().setActive(boolean0);
 }

 this->setLightSourceOn(boolean0);
 }

 if (SystemDisabler.doObjectStateSyncEnable && GameClient.bClient) {
 GameClient.instance.objectSyncReq.putRequestLoad(this->square);
 }
 }

 void save(ByteBuffer output, bool IS_DEBUG_SAVE) {
 super.save(output, IS_DEBUG_SAVE);
 BitHeaderWrite bitHeaderWrite =
 BitHeader.allocWrite(BitHeader.HeaderSize.Long, output);
 if (this->open) {
 bitHeaderWrite.addFlags(1);
 }

 if (this->Locked) {
 bitHeaderWrite.addFlags(2);
 }

 if (this->north) {
 bitHeaderWrite.addFlags(4);
 }

 if (this->MaxHealth != 500) {
 bitHeaderWrite.addFlags(8);
 output.putInt(this->MaxHealth);
 }

 if (this->Health != this->MaxHealth) {
 bitHeaderWrite.addFlags(16);
 output.putInt(this->Health);
 }

 if (this->closedSprite != nullptr) {
 bitHeaderWrite.addFlags(32);
 output.putInt(this->closedSprite.ID);
 }

 if (this->openSprite != nullptr) {
 bitHeaderWrite.addFlags(64);
 output.putInt(this->openSprite.ID);
 }

 if (this->thumpDmg != 8) {
 bitHeaderWrite.addFlags(128);
 output.putInt(this->thumpDmg);
 }

 if (this->isDoor) {
 bitHeaderWrite.addFlags(512);
 }

 if (this->isDoorFrame) {
 bitHeaderWrite.addFlags(1024);
 }

 if (this->isCorner) {
 bitHeaderWrite.addFlags(2048);
 }

 if (this->isStairs) {
 bitHeaderWrite.addFlags(4096);
 }

 if (this->isContainer) {
 bitHeaderWrite.addFlags(8192);
 }

 if (this->isFloor) {
 bitHeaderWrite.addFlags(16384);
 }

 if (this->canBarricade) {
 bitHeaderWrite.addFlags(32768);
 }

 if (this->canPassThrough) {
 bitHeaderWrite.addFlags(65536);
 }

 if (this->dismantable) {
 bitHeaderWrite.addFlags(131072);
 }

 if (this->canBePlastered) {
 bitHeaderWrite.addFlags(262144);
 }

 if (this->paintable) {
 bitHeaderWrite.addFlags(524288);
 }

 if (this->crossSpeed != 1.0F) {
 bitHeaderWrite.addFlags(1048576);
 output.putFloat(this->crossSpeed);
 }

 if (this->table != nullptr && !this->table.empty()) {
 bitHeaderWrite.addFlags(2097152);
 this->table.save(output);
 }

 if (this->modData != nullptr && !this->modData.empty()) {
 bitHeaderWrite.addFlags(4194304);
 this->modData.save(output);
 }

 if (this->blockAllTheSquare) {
 bitHeaderWrite.addFlags(8388608);
 }

 if (this->isThumpable) {
 bitHeaderWrite.addFlags(16777216);
 }

 if (this->isHoppable) {
 bitHeaderWrite.addFlags(33554432);
 }

 if (this->getLightSourceLife() != -1) {
 bitHeaderWrite.addFlags(67108864);
 output.putInt(this->getLightSourceLife());
 }

 if (this->getLightSourceRadius() != -1) {
 bitHeaderWrite.addFlags(134217728);
 output.putInt(this->getLightSourceRadius());
 }

 if (this->getLightSourceXOffset() != 0) {
 bitHeaderWrite.addFlags(268435456);
 output.putInt(this->getLightSourceXOffset());
 }

 if (this->getLightSourceYOffset() != 0) {
 bitHeaderWrite.addFlags(536870912);
 output.putInt(this->getLightSourceYOffset());
 }

 if (this->getLightSourceFuel() != nullptr) {
 bitHeaderWrite.addFlags(1073741824);
 output.putShort(
 WorldDictionary.getItemRegistryID(this->getLightSourceFuel()));
 }

 if (this->getLifeDelta() != 0.0F) {
 bitHeaderWrite.addFlags(2147483648L);
 output.putFloat(this->getLifeDelta());
 }

 if (this->getLifeLeft() != -1.0F) {
 bitHeaderWrite.addFlags(4294967296L);
 output.putFloat(this->getLifeLeft());
 }

 if (this->keyId != -1) {
 bitHeaderWrite.addFlags(8589934592L);
 output.putInt(this->keyId);
 }

 if (this->isLockedByKey()) {
 bitHeaderWrite.addFlags(17179869184L);
 }

 if (this->isLockedByPadlock()) {
 bitHeaderWrite.addFlags(34359738368L);
 }

 if (this->canBeLockByPadlock()) {
 bitHeaderWrite.addFlags(68719476736L);
 }

 if (this->getLockedByCode() != 0) {
 bitHeaderWrite.addFlags(137438953472L);
 output.putInt(this->getLockedByCode());
 }

 if (!this->thumpSound == "ZombieThumbGeneric")) {
 bitHeaderWrite.addFlags(274877906944L);
 GameWindow.WriteString(output, this->thumpSound);
 }

 if (this->lastUpdateHours != -1.0F) {
 bitHeaderWrite.addFlags(549755813888L);
 output.putFloat(this->lastUpdateHours);
 }

 if (this->haveFuel) {
 bitHeaderWrite.addFlags(1099511627776L);
 }

 if (this->lightSourceOn) {
 bitHeaderWrite.addFlags(2199023255552L);
 }

 bitHeaderWrite.write();
 bitHeaderWrite.release();
 }

 bool isDestroyed() { return this->destroyed; }

 bool IsOpen() { return this->open; }

 bool IsStrengthenedByPushedItems() { return false; }

 bool onMouseLeftClick(int x, int y) { return false; }

 bool TestPathfindCollide(IsoMovingObject obj, IsoGridSquare from,
 IsoGridSquare to) {
 bool boolean0 = this->north;
 if (obj instanceof
 IsoSurvivor && ((IsoSurvivor)obj).getInventory().contains("Hammer")) {
 return false;
 } else if (this->open) {
 return false;
 } else {
 if (from == this->square) {
 if (boolean0 && to.getY() < from.getY()) {
 return true;
 }

 if (!boolean0 && to.getX() < from.getX()) {
 return true;
 }
 } else {
 if (boolean0 && to.getY() > from.getY()) {
 return true;
 }

 if (!boolean0 && to.getX() > from.getX()) {
 return true;
 }
 }

 return false;
 }
 }

 bool TestCollide(IsoMovingObject obj, IsoGridSquare from, IsoGridSquare to) {
 if (obj instanceof IsoPlayer && ((IsoPlayer)obj).isNoClip()) {
 return false;
 } else {
 bool boolean0 = this->north;
 if (this->open) {
 return false;
 } else if (this->blockAllTheSquare) {
 if (from != this->square) {
 if (obj != nullptr) {
 obj.collideWith(this);
 }

 return true;
 } else {
 return false;
 }
 } else {
 if (from == this->square) {
 if (boolean0 && to.getY() < from.getY()) {
 if (obj != nullptr) {
 obj.collideWith(this);
 }

 if (!this->canPassThrough && !this->isStairs && !this->isCorner) {
 return true;
 }
 }

 if (!boolean0 && to.getX() < from.getX()) {
 if (obj != nullptr) {
 obj.collideWith(this);
 }

 if (!this->canPassThrough && !this->isStairs && !this->isCorner) {
 return true;
 }
 }
 } else {
 if (boolean0 && to.getY() > from.getY()) {
 if (obj != nullptr) {
 obj.collideWith(this);
 }

 if (!this->canPassThrough && !this->isStairs && !this->isCorner) {
 return true;
 }
 }

 if (!boolean0 && to.getX() > from.getX()) {
 if (obj != nullptr) {
 obj.collideWith(this);
 }

 if (!this->canPassThrough && !this->isStairs && !this->isCorner) {
 return true;
 }
 }
 }

 if (this->isCorner) {
 if (to.getY() < from.getY() && to.getX() < from.getX()) {
 if (obj != nullptr) {
 obj.collideWith(this);
 }

 if (!this->canPassThrough) {
 return true;
 }
 }

 if (to.getY() > from.getY() && to.getX() > from.getX()) {
 if (obj != nullptr) {
 obj.collideWith(this);
 }

 if (!this->canPassThrough) {
 return true;
 }
 }
 }

 return false;
 }
 }
 }

public
 IsoObject.VisionResult TestVision(IsoGridSquare from, IsoGridSquare to) {
 if (this->canPassThrough) {
 return IsoObject.VisionResult.NoEffect;
 } else {
 bool boolean0 = this->north;
 if (this->open) {
 boolean0 = !boolean0;
 }

 if (to.getZ() != from.getZ()) {
 return IsoObject.VisionResult.NoEffect;
 } else {
 bool boolean1 =
 this->sprite != nullptr && this->sprite.getProperties().Is("doorTrans");
 if (from == this->square) {
 if (boolean0 && to.getY() < from.getY()) {
 if (boolean1) {
 return IsoObject.VisionResult.Unblocked;
 }

 if (this->isWindow()) {
 return IsoObject.VisionResult.Unblocked;
 }

 return IsoObject.VisionResult.Blocked;
 }

 if (!boolean0 && to.getX() < from.getX()) {
 if (boolean1) {
 return IsoObject.VisionResult.Unblocked;
 }

 if (this->isWindow()) {
 return IsoObject.VisionResult.Unblocked;
 }

 return IsoObject.VisionResult.Blocked;
 }
 } else {
 if (boolean0 && to.getY() > from.getY()) {
 if (boolean1) {
 return IsoObject.VisionResult.Unblocked;
 }

 if (this->isWindow()) {
 return IsoObject.VisionResult.Unblocked;
 }

 return IsoObject.VisionResult.Blocked;
 }

 if (!boolean0 && to.getX() > from.getX()) {
 if (boolean1) {
 return IsoObject.VisionResult.Unblocked;
 }

 if (this->isWindow()) {
 return IsoObject.VisionResult.Unblocked;
 }

 return IsoObject.VisionResult.Blocked;
 }
 }

 return IsoObject.VisionResult.NoEffect;
 }
 }
 }

 void Thump(IsoMovingObject thumper) {
 if (SandboxOptions.instance.Lore.ThumpOnConstruction.getValue()) {
 if (thumper instanceof IsoGameCharacter) {
 Thumpable thumpable = this->getThumpableFor((IsoGameCharacter)thumper);
 if (thumpable.empty()) {
 return;
 }

 if (thumpable != this) {
 thumpable.Thump(thumper);
 return;
 }
 }

 bool boolean0 = BrokenFences.getInstance().isBreakableObject(this);
 if (thumper instanceof IsoZombie) {
 if (((IsoZombie)thumper).cognition == 1 && this->isDoor() &&
 !this->IsOpen() && !this->isLocked()) {
 this->ToggleDoor((IsoGameCharacter)thumper);
 return;
 }

 int int0 = thumper.getCurrentSquare().getMovingObjects().size();
 if (thumper.getCurrentSquare().getW() != nullptr) {
 int0 += thumper.getCurrentSquare().getW().getMovingObjects().size();
 }

 if (thumper.getCurrentSquare().getE() != nullptr) {
 int0 += thumper.getCurrentSquare().getE().getMovingObjects().size();
 }

 if (thumper.getCurrentSquare().getS() != nullptr) {
 int0 += thumper.getCurrentSquare().getS().getMovingObjects().size();
 }

 if (thumper.getCurrentSquare().getN() != nullptr) {
 int0 += thumper.getCurrentSquare().getN().getMovingObjects().size();
 }

 int int1 = this->thumpDmg;
 if (int0 >= int1) {
 int int2 = 1 * ThumpState.getFastForwardDamageMultiplier();
 this->Health -= int2;
 } else {
 this->partialThumpDmg =
 this->partialThumpDmg +
 (float)int0 / int1 * ThumpState.getFastForwardDamageMultiplier();
 if ((int)this->partialThumpDmg > 0) {
 int int3 = (int)this->partialThumpDmg;
 this->Health -= int3;
 this->partialThumpDmg -= int3;
 }
 }

 WorldSoundManager.instance.addSound(
 thumper, this->square.getX(), this->square.getY(), this->square.getZ(),
 20, 20, true, 4.0F, 15.0F);
 if (this->isDoor()) {
 this->setRenderEffect(RenderEffectType.Hit_Door, true);
 }
 }

 if (this->Health <= 0) {
 ((IsoGameCharacter)thumper)
 .getEmitter()
 .playSound(this->breakSound, this);
 if (GameServer.bServer) {
 GameServer.PlayWorldSoundServer(
 (IsoGameCharacter)thumper, this->breakSound, false,
 thumper.getCurrentSquare(), 0.2F, 20.0F, 1.1F, true);
 }

 WorldSoundManager.instance.addSound(
 nullptr, this->square.getX(), this->square.getY(), this->square.getZ(),
 10, 20, true, 4.0F, 15.0F);
 thumper.setThumpTarget(nullptr);
 if (IsoDoor.destroyDoubleDoor(this) {
 return;
 }

 if (IsoDoor.destroyGarageDoor(this) {
 return;
 }

 if (boolean0) {
 PropertyContainer propertyContainer = this->getProperties();
 IsoDirections directions;
 if (propertyContainer.Is(IsoFlagType.collideN) &&
 propertyContainer.Is(IsoFlagType.collideW) {
 directions = thumper.getY() >= this->getY() ? IsoDirections.N
 : IsoDirections.S;
 } else if (propertyContainer.Is(IsoFlagType.collideN) {
 directions = thumper.getY() >= this->getY() ? IsoDirections.N
 : IsoDirections.S;
 } else {
 directions = thumper.getX() >= this->getX() ? IsoDirections.W
 : IsoDirections.E;
 }

 BrokenFences.getInstance().destroyFence(this, directions);
 return;
 }

 this->destroy();
 }
 }
 }

 Thumpable getThumpableFor(IsoGameCharacter chr) {
 if (this->isDoor() || this->isWindow()) {
 IsoBarricade barricade = this->getBarricadeForCharacter(chr);
 if (barricade != nullptr) {
 return barricade;
 }

 barricade = this->getBarricadeOppositeCharacter(chr);
 if (barricade != nullptr) {
 return barricade;
 }
 }

 bool boolean0 = this->isThumpable;
 bool boolean1 = chr instanceof IsoZombie && ((IsoZombie)chr).isCrawling();
 if (!boolean0 && boolean1 &&
 BrokenFences.getInstance().isBreakableObject(this) {
 boolean0 = true;
 }

 if (!boolean0 && boolean1 && this->isHoppable()) {
 boolean0 = true;
 }

 if (boolean0 && !this->isDestroyed()) {
 if ((!this->isDoor() || !this->IsOpen()) && !this->isWindow()) {
 return !boolean1 && this->isHoppable() ? nullptr : this;
 } else {
 return nullptr;
 }
 } else {
 return nullptr;
 }
 }

 float getThumpCondition() {
 return (float)PZMath.clamp(this->Health, 0, this->MaxHealth) / this->MaxHealth;
 }

 void WeaponHit(IsoGameCharacter owner, HandWeapon weapon) {
 IsoPlayer player = Type.tryCastTo(owner, IsoPlayer.class);
 if (GameClient.bClient) {
 if (player != nullptr) {
 GameClient.instance.sendWeaponHit(player, weapon, this);
 }

 if (this->isDoor()) {
 this->setRenderEffect(RenderEffectType.Hit_Door, true);
 }
 } else {
 Thumpable thumpable = this->getThumpableFor(owner);
 if (thumpable != nullptr) {
 if (thumpable instanceof IsoBarricade) {
 ((IsoBarricade)thumpable).WeaponHit(owner, weapon);
 } else {
 LuaEventManager.triggerEvent("OnWeaponHitThumpable", owner, weapon,
 this);
 this->Damage(weapon.getDoorDamage());
 if (weapon.getDoorHitSound() != nullptr) {
 if (player != nullptr) {
 player.setMeleeHitSurface(this->getSoundPrefix());
 }

 owner.getEmitter().playSound(weapon.getDoorHitSound(), this);
 if (GameServer.bServer) {
 GameServer.PlayWorldSoundServer(owner, weapon.getDoorHitSound(),
 false, this->getSquare(), 0.2F,
 20.0F, 1.0F, false);
 }
 }

 WorldSoundManager.instance.addSound(
 owner, this->square.getX(), this->square.getY(), this->square.getZ(),
 20, 20, false, 0.0F, 15.0F);
 if (this->isDoor()) {
 this->setRenderEffect(RenderEffectType.Hit_Door, true);
 }

 if (!this->IsStrengthenedByPushedItems() && this->Health <= 0 ||
 this->IsStrengthenedByPushedItems() &&
 this->Health <= -this->PushedMaxStrength) {
 owner.getEmitter().playSound(this->breakSound, this);
 WorldSoundManager.instance.addSound(
 owner, this->square.getX(), this->square.getY(),
 this->square.getZ(), 20, 20, false, 0.0F, 15.0F);
 if (GameClient.bClient) {
 GameClient.instance.sendClientCommandV(
 nullptr, "object", "OnDestroyIsoThumpable", "x",
 (int)this->getX(), "y", (int)this->getY(), "z",
 (int)this->getZ(), "index", this->getObjectIndex());
 }

 LuaEventManager.triggerEvent("OnDestroyIsoThumpable", this,
 nullptr);
 if (IsoDoor.destroyDoubleDoor(this) {
 return;
 }

 if (IsoDoor.destroyGarageDoor(this) {
 return;
 }

 this->destroyed = true;
 if (this->getObjectIndex() != -1) {
 this->square.transmitRemoveItemFromSquare(this);
 }
 }
 }
 }
 }
 }

 IsoGridSquare getOtherSideOfDoor(IsoGameCharacter chr) {
 if (this->north) {
 return chr.getCurrentSquare().getRoom() == this->square.getRoom()
 ? IsoWorld.instance.CurrentCell.getGridSquare(
 this->square.getX(), this->square.getY() - 1,
 this->square.getZ())
 : IsoWorld.instance.CurrentCell.getGridSquare(
 this->square.getX(), this->square.getY(),
 this->square.getZ());
 } else {
 return chr.getCurrentSquare().getRoom() == this->square.getRoom()
 ? IsoWorld.instance.CurrentCell.getGridSquare(
 this->square.getX() - 1, this->square.getY(),
 this->square.getZ())
 : IsoWorld.instance.CurrentCell.getGridSquare(
 this->square.getX(), this->square.getY(),
 this->square.getZ());
 }
 }

 void ToggleDoorActual(IsoGameCharacter chr) {
 if (this->isBarricaded()) {
 if (chr != nullptr) {
 this->playDoorSound(chr.getEmitter(), "Blocked");
 chr.setHaloNote(Translator.getText("IGUI_PlayerText_DoorBarricaded"),
 255, 255, 255, 256.0F);
 this->setRenderEffect(RenderEffectType.Hit_Door, true);
 }
 } else if (this->isLockedByKey() && chr instanceof
 IsoPlayer && chr.getCurrentSquare().Is(IsoFlagType.exterior) &&
 chr.getInventory().haveThisKeyId(this->getKeyId()) ==
 nullptr) {
 this->playDoorSound(chr.getEmitter(), "Locked");
 this->setRenderEffect(RenderEffectType.Hit_Door, true);
 } else {
 if (this->isLockedByKey() && chr instanceof
 IsoPlayer &&
 chr.getInventory().haveThisKeyId(this->getKeyId()) != nullptr) {
 this->playDoorSound(chr.getEmitter(), "Unlock");
 this->setIsLocked(false);
 this->setLockedByKey(false);
 }

 this->DirtySlice();
 this->square.InvalidateSpecialObjectPaths();
 if (this->Locked && chr instanceof
 IsoPlayer && chr.getCurrentSquare().Is(IsoFlagType.exterior) &&
 !this->open) {
 this->playDoorSound(chr.getEmitter(), "Locked");
 this->setRenderEffect(RenderEffectType.Hit_Door, true);
 } else {
 if (chr instanceof IsoPlayer) {
 }

 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 LosUtil.cachecleared[int0] = true;
 }

 IsoGridSquare.setRecalcLightTime(-1);
 GameTime.instance.lightSourceUpdate = 100.0F;
 if (this->getSprite().getProperties().Is("DoubleDoor")) {
 if (IsoDoor.isDoubleDoorObstructed(this) {
 if (chr != nullptr) {
 this->playDoorSound(chr.getEmitter(), "Blocked");
 chr.setHaloNote(Translator.getText("IGUI_PlayerText_DoorBlocked"),
 255, 255, 255, 256.0F);
 }
 } else {
 bool boolean0 = this->open;
 IsoDoor.toggleDoubleDoor(this, true);
 if (boolean0 != this->open) {
 this->playDoorSound(chr.getEmitter(),
 this->open ? "Open" : "Close");
 }
 }
 } else if (this->isObstructed()) {
 if (chr != nullptr) {
 this->playDoorSound(chr.getEmitter(), "Blocked");
 chr.setHaloNote(Translator.getText("IGUI_PlayerText_DoorBlocked"),
 255, 255, 255, 256.0F);
 }
 } else {
 this->sprite = this->closedSprite;
 this->open = !this->open;
 this->setLockedByKey(false);
 if (this->open) {
 this->playDoorSound(chr.getEmitter(), "Open");
 this->sprite = this->openSprite;
 } else {
 this->playDoorSound(chr.getEmitter(), "Close");
 }

 this->square.RecalcProperties();
 this->syncIsoObject(false, (byte)(this->open ? 1 : 0), nullptr,
 nullptr);
 LuaEventManager.triggerEvent("OnContainerUpdate");
 }
 }
 }
 }

 void ToggleDoor(IsoGameCharacter chr) { this->ToggleDoorActual(chr); }

 void ToggleDoorSilent() {
 if (!this->isBarricaded()) {
 this->square.InvalidateSpecialObjectPaths();

 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 LosUtil.cachecleared[int0] = true;
 }

 IsoGridSquare.setRecalcLightTime(-1);
 this->open = !this->open;
 this->sprite = this->closedSprite;
 if (this->open) {
 this->sprite = this->openSprite;
 }
 }
 }

 bool isObstructed() { return IsoDoor.isDoorObstructed(this); }

 bool haveSheetRope() {
 return IsoWindow.isTopOfSheetRopeHere(this->square, this->north);
 }

 int countAddSheetRope() {
 return !this->isHoppable() && !this->isWindow()
 ? 0
 : IsoWindow.countAddSheetRope(this->square, this->north);
 }

 bool canAddSheetRope() {
 return !this->isHoppable() && !this->isWindow()
 ? false
 : IsoWindow.canAddSheetRope(this->square, this->north);
 }

 bool addSheetRope(IsoPlayer player, std::string_view itemType) {
 return !this->canAddSheetRope()
 ? false
 : IsoWindow.addSheetRope(player, this->square, this->north,
 itemType);
 }

 bool removeSheetRope(IsoPlayer player) {
 return this->haveSheetRope()
 ? IsoWindow.removeSheetRope(player, this->square, this->north)
 : false;
 }

public
 void createLightSource(int radius, int offsetX, int offsetY, int offsetZ,
 int life, String _lightSourceFuel,
 InventoryItem baseItem, IsoGameCharacter chr) {
 this->setLightSourceXOffset(offsetX);
 this->setLightSourceYOffset(offsetY);
 this->setLightSourceRadius(radius);
 this->setLightSourceFuel(_lightSourceFuel);
 if (baseItem != nullptr) {
 if (!(baseItem instanceof DrainableComboItem) {
 this->setLifeLeft(1.0F);
 this->setHaveFuel(true);
 } else {
 this->setLifeLeft(((DrainableComboItem)baseItem).getUsedDelta());
 this->setLifeDelta(((DrainableComboItem)baseItem).getUseDelta());
 this->setHaveFuel(!"Base.Torch" == baseItem.getFullType()) || ((DrainableComboItem)baseItem).getUsedDelta() > 0.0F);
 }

 chr.removeFromHands(baseItem);
 IsoWorldInventoryObject worldInventoryObject = baseItem.getWorldItem();
 if (worldInventoryObject != nullptr) {
 if (worldInventoryObject.getSquare() != nullptr) {
 worldInventoryObject.getSquare().transmitRemoveItemFromSquare(
 worldInventoryObject);
 LuaEventManager.triggerEvent("OnContainerUpdate");
 }
 } else if (baseItem.getContainer() != nullptr) {
 baseItem.getContainer().Remove(baseItem);
 }
 }

 this->setLightSourceOn(this->haveFuel);
 if (this->lightSource != nullptr) {
 this->lightSource.setActive(this->isLightSourceOn());
 }
 }

 InventoryItem insertNewFuel(InventoryItem item, IsoGameCharacter chr) {
 if (item != nullptr) {
 InventoryItem _item = this->removeCurrentFuel(chr);
 if (chr != nullptr) {
 chr.removeFromHands(item);
 chr.getInventory().Remove(item);
 }

 if (item instanceof DrainableComboItem) {
 this->setLifeLeft(((DrainableComboItem)item).getUsedDelta());
 this->setLifeDelta(((DrainableComboItem)item).getUseDelta());
 } else {
 this->setLifeLeft(1.0F);
 }

 this->setHaveFuel(true);
 this->toggleLightSource(true);
 return _item;
 } else {
 return nullptr;
 }
 }

 InventoryItem removeCurrentFuel(IsoGameCharacter chr) {
 if (this->haveFuel()) {
 InventoryItem item =
 InventoryItemFactory.CreateItem(this->getLightSourceFuel());
 if (item instanceof DrainableComboItem) {
 ((DrainableComboItem)item).setUsedDelta(this->getLifeLeft());
 }

 if (chr != nullptr) {
 chr.getInventory().AddItem(item);
 }

 this->setLifeLeft(0.0F);
 this->setLifeDelta(-1.0F);
 this->toggleLightSource(false);
 this->setHaveFuel(false);
 return item;
 } else {
 return nullptr;
 }
 }

 int calcLightSourceX() {
 int int0 = (int)this->getX();
 int int1 = (int)this->getY();
 if (this->lightSourceXOffset != 0) {
 for (int int2 = 1; int2 <= Math.abs(this->lightSourceXOffset); int2++) {
 int int3 = this->lightSourceXOffset > 0 ? 1 : -1;
 LosUtil.TestResults testResults = LosUtil.lineClear(
 this->getCell(), (int)this->getX(), (int)this->getY(),
 (int)this->getZ(), int0 + int3, int1, (int)this->getZ(), false);
 if (testResults == LosUtil.TestResults.Blocked ||
 testResults == LosUtil.TestResults.ClearThroughWindow) {
 break;
 }

 int0 += int3;
 }
 }

 return int0;
 }

 int calcLightSourceY() {
 int int0 = (int)this->getX();
 int int1 = (int)this->getY();
 if (this->lightSourceYOffset != 0) {
 for (int int2 = 1; int2 <= Math.abs(this->lightSourceYOffset); int2++) {
 int int3 = this->lightSourceYOffset > 0 ? 1 : -1;
 LosUtil.TestResults testResults = LosUtil.lineClear(
 this->getCell(), (int)this->getX(), (int)this->getY(),
 (int)this->getZ(), int0, int1 + int3, (int)this->getZ(), false);
 if (testResults == LosUtil.TestResults.Blocked ||
 testResults == LosUtil.TestResults.ClearThroughWindow) {
 break;
 }

 int1 += int3;
 }
 }

 return int1;
 }

 void update() {
 if (this->getObjectIndex() != -1) {
 if (!GameServer.bServer) {
 if (this->lightSource != nullptr && !this->lightSource.isInBounds()) {
 this->lightSource = nullptr;
 }

 if (this->lightSourceFuel != nullptr &&
 !this->lightSourceFuel.empty() && this->lightSource.empty() &&
 this->square != nullptr) {
 uint8_t byte0 = 0;
 int int0 = this->calcLightSourceX();
 int int1 = this->calcLightSourceY();
 if (IsoWorld.instance.CurrentCell.isInChunkMap(int0, int1) {
 int int2 = this->getLightSourceLife();
 this->setLightSource(new IsoLightSource(););
 this->lightSource.setActive(this->isLightSourceOn());
 IsoWorld.instance.getCell().getLamppostPositions().add(
 this->getLightSource());
 }
 }

 if (this->lightSource != nullptr && this->lightSource.isActive()) {
 uint8_t byte1 = 0;
 int int3 = this->calcLightSourceX();
 int int4 = this->calcLightSourceY();
 if (int3 != this->lightSource.x || int4 != this->lightSource.y) {
 this->getCell().removeLamppost(this->lightSource);
 int int5 = this->getLightSourceLife();
 this->setLightSource(new IsoLightSource(););
 this->lightSource.setActive(this->isLightSourceOn());
 IsoWorld.instance.getCell().getLamppostPositions().add(
 this->getLightSource());
 }
 }
 }

 if (this->getLifeLeft() > -1.0F) {
 float float0 = (float)GameTime.getInstance().getWorldAgeHours();
 if (this->lastUpdateHours == -1.0F) {
 this->lastUpdateHours = float0;
 } else if (this->lastUpdateHours > float0) {
 this->lastUpdateHours = float0;
 }

 float float1 = float0 - this->lastUpdateHours;
 this->lastUpdateHours = float0;
 if (this->isLightSourceOn()) {
 this->updateAccumulator += float1;
 int int6 = (int)Math.floor(this->updateAccumulator / 0.004166667F);
 if (int6 > 0) {
 this->updateAccumulator -= 0.004166667F * int6;
 this->setLifeLeft(this->getLifeLeft() - this->getLifeDelta() * int6);
 if (this->getLifeLeft() <= 0.0F) {
 this->setLifeLeft(0.0F);
 this->toggleLightSource(false);
 }
 }
 } else {
 this->updateAccumulator = 0.0F;
 }
 }
 }
 }

 void Damage(int int0) {
 if (this->isThumpable()) {
 this->DirtySlice();
 this->Health -= int0;
 }
 }

 void destroy() {
 if (!this->destroyed) {
 if (this->getObjectIndex() != -1) {
 if (GameClient.bClient) {
 GameClient.instance.sendClientCommandV(
 nullptr, "object", "OnDestroyIsoThumpable", "x",
 this->square.getX(), "y", this->square.getY(), "z",
 this->square.getZ(), "index", this->getObjectIndex());
 }

 LuaEventManager.triggerEvent("OnDestroyIsoThumpable", this, nullptr);
 this->Health = 0;
 this->destroyed = true;
 if (this->getObjectIndex() != -1) {
 this->square.transmitRemoveItemFromSquare(this);
 }
 }
 }
 }

 IsoBarricade getBarricadeOnSameSquare() {
 return IsoBarricade.GetBarricadeOnSquare(
 this->square, this->north ? IsoDirections.N : IsoDirections.W);
 }

 IsoBarricade getBarricadeOnOppositeSquare() {
 return IsoBarricade.GetBarricadeOnSquare(this->getOppositeSquare(),
 this->north ? IsoDirections.S
 : IsoDirections.E);
 }

 bool isBarricaded() {
 IsoBarricade barricade = this->getBarricadeOnSameSquare();
 if (barricade.empty()) {
 barricade = this->getBarricadeOnOppositeSquare();
 }

 return barricade != nullptr;
 }

 bool isBarricadeAllowed() { return this->canBarricade; }

 IsoBarricade getBarricadeForCharacter(IsoGameCharacter chr) {
 return IsoBarricade.GetBarricadeForCharacter(this, chr);
 }

 IsoBarricade getBarricadeOppositeCharacter(IsoGameCharacter chr) {
 return IsoBarricade.GetBarricadeOppositeCharacter(this, chr);
 }

 void setIsDoor(bool pIsDoor) { this->isDoor = pIsDoor; }

 /**
 * @return the table
 */
 KahluaTable getTable() { return this->table; }

 /**
 *
 * @param _table the table to set
 */
 void setTable(KahluaTable _table) { this->table = _table; }

 bool canBePlastered() { return this->canBePlastered; }

 void setCanBePlastered(bool _canBePlastered) {
 this->canBePlastered = _canBePlastered;
 }

 bool isPaintable() { return this->paintable; }

 void setPaintable(bool _paintable) { this->paintable = _paintable; }

 bool isLocked() { return this->Locked; }

 void setIsLocked(bool lock) { this->Locked = lock; }

 bool isThumpable() { return this->isBarricaded() ? true : this->isThumpable; }

 void setIsThumpable(bool thumpable) { this->isThumpable = thumpable; }

 void setIsHoppable(bool _isHoppable) { this->setHoppable(_isHoppable); }

 IsoSprite getOpenSprite() { return this->openSprite; }

 bool isHoppable() {
 if (this->isDoor() && !this->IsOpen() && this->closedSprite != nullptr) {
 PropertyContainer propertyContainer = this->closedSprite.getProperties();
 return propertyContainer.Is(IsoFlagType.HoppableN) ||
 propertyContainer.Is(IsoFlagType.HoppableW);
 } else {
 return this->sprite.empty() ||
 !this->sprite.getProperties().Is(IsoFlagType.HoppableN) &&
 !this->sprite.getProperties().Is(IsoFlagType.HoppableW)
 ? this->isHoppable
 : true;
 }
 }

 void setHoppable(bool _isHoppable) { this->isHoppable = _isHoppable; }

 int getLightSourceRadius() { return this->lightSourceRadius; }

 void setLightSourceRadius(int _lightSourceRadius) {
 this->lightSourceRadius = _lightSourceRadius;
 }

 int getLightSourceXOffset() { return this->lightSourceXOffset; }

 void setLightSourceXOffset(int _lightSourceXOffset) {
 this->lightSourceXOffset = _lightSourceXOffset;
 }

 int getLightSourceYOffset() { return this->lightSourceYOffset; }

 void setLightSourceYOffset(int _lightSourceYOffset) {
 this->lightSourceYOffset = _lightSourceYOffset;
 }

 int getLightSourceLife() { return this->lightSourceLife; }

 void setLightSourceLife(int _lightSourceLife) {
 this->lightSourceLife = _lightSourceLife;
 }

 bool isLightSourceOn() { return this->lightSourceOn; }

 void setLightSourceOn(bool _lightSourceOn) {
 this->lightSourceOn = _lightSourceOn;
 }

 IsoLightSource getLightSource() { return this->lightSource; }

 void setLightSource(IsoLightSource _lightSource) {
 this->lightSource = _lightSource;
 }

 void toggleLightSource(bool toggle) {
 this->setLightSourceOn(toggle);
 if (this->lightSource != nullptr) {
 this->getLightSource().setActive(toggle);
 IsoGridSquare.setRecalcLightTime(-1);
 GameTime.instance.lightSourceUpdate = 100.0F;
 }
 }

 std::string getLightSourceFuel() { return this->lightSourceFuel; }

 void setLightSourceFuel(std::string_view _lightSourceFuel) {
 if (_lightSourceFuel != nullptr && _lightSourceFuel.empty()) {
 _lightSourceFuel = nullptr;
 }

 this->lightSourceFuel = _lightSourceFuel;
 }

 float getLifeLeft() { return this->lifeLeft; }

 void setLifeLeft(float _lifeLeft) { this->lifeLeft = _lifeLeft; }

 float getLifeDelta() { return this->lifeDelta; }

 void setLifeDelta(float _lifeDelta) { this->lifeDelta = _lifeDelta; }

 bool haveFuel() { return this->haveFuel; }

 void setHaveFuel(bool _haveFuel) { this->haveFuel = _haveFuel; }

 void syncIsoObjectSend(ByteBufferWriter b) {
 b.putInt(this->square.getX());
 b.putInt(this->square.getY());
 b.putInt(this->square.getZ());
 uint8_t byte0 = (byte)this->square.getObjects().indexOf(this);
 b.putByte(byte0);
 b.putByte((byte)1);
 b.putByte((byte)0);
 b.putBoolean(this->open);
 b.putBoolean(this->Locked);
 b.putBoolean(this->lockedByKey);
 }

 void syncIsoObject(bool bRemote, uint8_t val, UdpConnection source,
 ByteBuffer bb) {
 if (this->square.empty()) {
 System.out.println("ERROR: " + this->getClass().getSimpleName() +
 " square is nullptr");
 } else if (this->getObjectIndex() == -1) {
 System.out.println("ERROR: " + this->getClass().getSimpleName() +
 " not found on square " + this->square.getX() + "," +
 this->square.getY() + "," + this->square.getZ());
 } else if (this->isDoor()) {
 bool boolean0 = bb != nullptr && bb.get() == 1;
 bool boolean1 = bb != nullptr && bb.get() == 1;
 bool boolean2 = bb != nullptr && bb.get() == 1;
 short short0 = -1;
 if ((GameServer.bServer || GameClient.bClient) && bb != nullptr) {
 short0 = bb.getShort();
 }

 if (GameClient.bClient && !bRemote) {
 short0 = IsoPlayer.getInstance().getOnlineID();
 ByteBufferWriter byteBufferWriter0 =
 GameClient.connection.startPacket();
 PacketTypes.PacketType.SyncIsoObject.doPacket(byteBufferWriter0);
 this->syncIsoObjectSend(byteBufferWriter0);
 byteBufferWriter0.putShort(short0);
 PacketTypes.PacketType.SyncIsoObject.send(GameClient.connection);
 } else if (GameServer.bServer && !bRemote) {
 for (UdpConnection udpConnection0 : GameServer.udpEngine.connections) {
 ByteBufferWriter byteBufferWriter1 = udpConnection0.startPacket();
 PacketTypes.PacketType.SyncIsoObject.doPacket(byteBufferWriter1);
 this->syncIsoObjectSend(byteBufferWriter1);
 byteBufferWriter1.putShort(short0);
 PacketTypes.PacketType.SyncIsoObject.send(udpConnection0);
 }
 } else if (bRemote) {
 if (GameClient.bClient && short0 != -1) {
 IsoPlayer player = GameClient.IDToPlayerMap.get(short0);
 if (player != nullptr) {
 player.networkAI.setNoCollision(1000L);
 }
 }

 if (IsoDoor.getDoubleDoorIndex(this) != -1) {
 if (boolean0 != this->open) {
 IsoDoor.toggleDoubleDoor(this, false);
 }
 } else if (boolean0) {
 this->open = true;
 this->sprite = this->openSprite;
 } else {
 this->open = false;
 this->sprite = this->closedSprite;
 }

 this->Locked = boolean1;
 this->lockedByKey = boolean2;
 if (GameServer.bServer) {
 for (UdpConnection udpConnection1 :
 GameServer.udpEngine.connections) {
 if (source != nullptr && udpConnection1.getConnectedGUID() !=
 source.getConnectedGUID()) {
 ByteBufferWriter byteBufferWriter2 = udpConnection1.startPacket();
 PacketTypes.PacketType.SyncIsoObject.doPacket(byteBufferWriter2);
 this->syncIsoObjectSend(byteBufferWriter2);
 byteBufferWriter2.putShort(short0);
 PacketTypes.PacketType.SyncIsoObject.send(udpConnection1);
 }
 }
 }

 this->square.InvalidateSpecialObjectPaths();
 this->square.RecalcProperties();
 this->square.RecalcAllWithNeighbours(true);

 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 LosUtil.cachecleared[int0] = true;
 }

 IsoGridSquare.setRecalcLightTime(-1);
 GameTime.instance.lightSourceUpdate = 100.0F;
 LuaEventManager.triggerEvent("OnContainerUpdate");
 }
 }
 }

 void addToWorld() {
 super.addToWorld();
 this->getCell().addToProcessIsoObject(this);
 }

 void removeFromWorld() {
 if (this->lightSource != nullptr) {
 IsoWorld.instance.CurrentCell.removeLamppost(this->lightSource);
 }

 super.removeFromWorld();
 }

 void saveChange(std::string_view change, KahluaTable tbl, ByteBuffer bb) {
 super.saveChange(change, tbl, bb);
 if ("lightSource" == change) {
 bb.put((byte)(this->lightSourceOn ? 1 : 0);
 bb.put((byte)(this->haveFuel ? 1 : 0);
 bb.putFloat(this->lifeLeft);
 bb.putFloat(this->lifeDelta);
 }
 else if ("paintable" == change) {
 bb.put((byte)(this->isPaintable() ? 1 : 0);
 }
 }

 void loadChange(std::string_view change, ByteBuffer bb) {
 super.loadChange(change, bb);
 if ("lightSource" == change) {
 bool boolean0 = bb.get() == 1;
 this->haveFuel = bb.get() == 1;
 this->lifeLeft = bb.getFloat();
 this->lifeDelta = bb.getFloat();
 if (boolean0 != this->lightSourceOn) {
 this->toggleLightSource(boolean0);
 }
 }
 else if ("paintable" == change) {
 this->setPaintable(bb.get() == 1);
 }
 }

 IsoCurtain HasCurtains() {
 IsoGridSquare square = this->getOppositeSquare();
 if (square != nullptr) {
 IsoCurtain curtain = square.getCurtain(
 this->getNorth() ? IsoObjectType.curtainS : IsoObjectType.curtainE);
 if (curtain != nullptr) {
 return curtain;
 }
 }

 return this->getSquare().getCurtain(
 this->getNorth() ? IsoObjectType.curtainN : IsoObjectType.curtainW);
 }

 IsoGridSquare getInsideSquare() {
 return this->north
 ? this->square.getCell().getGridSquare(this->square.getX(),
 this->square.getY() - 1,
 this->square.getZ())
 : this->square.getCell().getGridSquare(this->square.getX() - 1,
 this->square.getY(),
 this->square.getZ());
 }

 IsoGridSquare getOppositeSquare() { return this->getInsideSquare(); }

 bool isAdjacentToSquare(IsoGridSquare square2) {
 IsoGridSquare square0 = this->getSquare();
 if (square0 != nullptr && square2 != nullptr) {
 bool boolean0 = !this->IsOpen();
 IsoGridSquare square1 = square0.getAdjacentSquare(IsoDirections.NW);
 IsoGridSquare _square2 = square0.getAdjacentSquare(IsoDirections.N);
 IsoGridSquare square3 = square0.getAdjacentSquare(IsoDirections.NE);
 IsoGridSquare square4 = square0.getAdjacentSquare(IsoDirections.W);
 IsoGridSquare square5 = square0.getAdjacentSquare(IsoDirections.E);
 IsoGridSquare square6 = square0.getAdjacentSquare(IsoDirections.SW);
 IsoGridSquare square7 = square0.getAdjacentSquare(IsoDirections.S);
 IsoGridSquare square8 = square0.getAdjacentSquare(IsoDirections.SE);
 switch (this->getSpriteEdge(false) {
 case N:
 if (square2 == square1) {
 if (!square1.isWallTo(_square2) && !square1.isWindowTo(_square2) &&
 !square1.hasDoorOnEdge(IsoDirections.E, false) &&
 !_square2.hasDoorOnEdge(IsoDirections.W, false) {
 if (_square2.hasDoorOnEdge(IsoDirections.S, false) {
 return false;
 }

 if (this->IsOpen() && square0.hasClosedDoorOnEdge(IsoDirections.N) {
 return false;
 }

 return true;
 }

 return false;
 }

 if (square2 == _square2) {
 if (_square2.hasDoorOnEdge(IsoDirections.S, false) {
 return false;
 }

 if (this->IsOpen() && square0.hasClosedDoorOnEdge(IsoDirections.N) {
 return false;
 }

 return true;
 }

 if (square2 == square3) {
 if (!square3.isWallTo(_square2) && !square3.isWindowTo(_square2) &&
 !square3.hasDoorOnEdge(IsoDirections.W, false) &&
 !_square2.hasDoorOnEdge(IsoDirections.E, false) {
 if (_square2.hasDoorOnEdge(IsoDirections.S, false) {
 return false;
 }

 if (this->IsOpen() && square0.hasClosedDoorOnEdge(IsoDirections.N) {
 return false;
 }

 return true;
 }

 return false;
 }

 if (square2 == square4) {
 if (!square4.isWallTo(square0) && !square4.isWindowTo(square0) &&
 !square4.hasDoorOnEdge(IsoDirections.E, false) &&
 !square0.hasDoorOnEdge(IsoDirections.W, false) {
 if (boolean0 && square0.hasOpenDoorOnEdge(IsoDirections.N) {
 return false;
 }

 return true;
 }

 return false;
 }

 if (square2 == square0) {
 if (boolean0 && square0.hasOpenDoorOnEdge(IsoDirections.N) {
 return false;
 }

 return true;
 }

 if (square2 == square5) {
 if (!square5.isWallTo(square0) && !square5.isWindowTo(square0) &&
 !square5.hasDoorOnEdge(IsoDirections.W, false) &&
 !square0.hasDoorOnEdge(IsoDirections.E, false) {
 if (boolean0 && square0.hasOpenDoorOnEdge(IsoDirections.N) {
 return false;
 }

 return true;
 }

 return false;
 }
 break;
 case S:
 if (square2 == square4) {
 if (!square4.isWallTo(square0) && !square4.isWindowTo(square0) &&
 !square4.hasDoorOnEdge(IsoDirections.E, false) &&
 !square0.hasDoorOnEdge(IsoDirections.W, false) {
 if (boolean0 && square0.hasOpenDoorOnEdge(IsoDirections.S) {
 return false;
 }

 return true;
 }

 return false;
 }

 if (square2 == square0) {
 if (boolean0 && square0.hasOpenDoorOnEdge(IsoDirections.S) {
 return false;
 }

 return true;
 }

 if (square2 == square5) {
 if (!square5.isWallTo(square0) && !square5.isWindowTo(square0) &&
 !square5.hasDoorOnEdge(IsoDirections.W, false) &&
 !square0.hasDoorOnEdge(IsoDirections.E, false) {
 if (boolean0 && square0.hasOpenDoorOnEdge(IsoDirections.S) {
 return false;
 }

 return true;
 }

 return false;
 }

 if (square2 == square6) {
 if (!square6.isWallTo(square7) && !square6.isWindowTo(square7) &&
 !square6.hasDoorOnEdge(IsoDirections.E, false) &&
 !square7.hasDoorOnEdge(IsoDirections.W, false) {
 if (square7.hasDoorOnEdge(IsoDirections.N, false) {
 return false;
 }

 return true;
 }

 return false;
 }

 if (square2 == square7) {
 if (square7.hasDoorOnEdge(IsoDirections.N, false) {
 return false;
 }

 return true;
 }

 if (square2 == square8) {
 if (!square8.isWallTo(square7) && !square8.isWindowTo(square7) &&
 !square8.hasDoorOnEdge(IsoDirections.W, false) &&
 !square7.hasDoorOnEdge(IsoDirections.E, false) {
 if (square7.hasDoorOnEdge(IsoDirections.N, false) {
 return false;
 }

 return true;
 }

 return false;
 }
 break;
 case W:
 if (square2 == square1) {
 if (!square1.isWallTo(square4) && !square1.isWindowTo(square4) &&
 !square1.hasDoorOnEdge(IsoDirections.S, false) &&
 !square4.hasDoorOnEdge(IsoDirections.N, false) {
 if (boolean0 && square4.hasDoorOnEdge(IsoDirections.E, false) {
 return false;
 }

 if (this->IsOpen() && square0.hasClosedDoorOnEdge(IsoDirections.W) {
 return false;
 }

 return true;
 }

 return false;
 }

 if (square2 == square4) {
 if (boolean0 && square4.hasDoorOnEdge(IsoDirections.E, false) {
 return false;
 }

 if (this->IsOpen() && square0.hasClosedDoorOnEdge(IsoDirections.W) {
 return false;
 }

 return true;
 }

 if (square2 == square6) {
 if (!square6.isWallTo(square4) && !square6.isWindowTo(square4) &&
 !square6.hasDoorOnEdge(IsoDirections.N, false) &&
 !square4.hasDoorOnEdge(IsoDirections.S, false) {
 if (boolean0 && square4.hasDoorOnEdge(IsoDirections.E, false) {
 return false;
 }

 if (this->IsOpen() && square0.hasClosedDoorOnEdge(IsoDirections.W) {
 return false;
 }

 return true;
 }

 return false;
 }

 if (square2 == _square2) {
 if (!_square2.isWallTo(square0) && !_square2.isWindowTo(square0) &&
 !_square2.hasDoorOnEdge(IsoDirections.S, false) &&
 !square0.hasDoorOnEdge(IsoDirections.N, false) {
 if (boolean0 && square0.hasOpenDoorOnEdge(IsoDirections.W) {
 return false;
 }

 return true;
 }

 return false;
 }

 if (square2 == square0) {
 if (boolean0 && square0.hasOpenDoorOnEdge(IsoDirections.W) {
 return false;
 }

 return true;
 }

 if (square2 == square7) {
 if (!square7.isWallTo(square0) && !square7.isWindowTo(square0) &&
 !square7.hasDoorOnEdge(IsoDirections.N, false) &&
 !square0.hasDoorOnEdge(IsoDirections.S, false) {
 if (boolean0 && square0.hasOpenDoorOnEdge(IsoDirections.W) {
 return false;
 }

 return true;
 }

 return false;
 }
 break;
 case E:
 if (square2 == _square2) {
 if (!_square2.isWallTo(square0) && !_square2.isWindowTo(square0) &&
 !_square2.hasDoorOnEdge(IsoDirections.S, false) &&
 !square0.hasDoorOnEdge(IsoDirections.N, false) {
 if (boolean0 && square0.hasOpenDoorOnEdge(IsoDirections.E) {
 return false;
 }

 return true;
 }

 return false;
 }

 if (square2 == square0) {
 if (boolean0 && square0.hasOpenDoorOnEdge(IsoDirections.E) {
 return false;
 }

 return true;
 }

 if (square2 == square7) {
 if (!square7.isWallTo(square0) && !square7.isWindowTo(square0) &&
 !square7.hasDoorOnEdge(IsoDirections.N, false) &&
 !square0.hasDoorOnEdge(IsoDirections.S, false) {
 if (boolean0 && square0.hasOpenDoorOnEdge(IsoDirections.E) {
 return false;
 }

 return true;
 }

 return false;
 }

 if (square2 == square3) {
 if (!square3.isWallTo(square5) && !square3.isWindowTo(square5) &&
 !square3.hasDoorOnEdge(IsoDirections.S, false) &&
 !square4.hasDoorOnEdge(IsoDirections.N, false) {
 if (square5.hasDoorOnEdge(IsoDirections.W, false) {
 return false;
 }

 return true;
 }

 return false;
 }

 if (square2 == square5) {
 if (square5.hasDoorOnEdge(IsoDirections.W, false) {
 return false;
 }

 return true;
 }

 if (square2 == square8) {
 if (!square8.isWallTo(square5) && !square8.isWindowTo(square5) &&
 !square8.hasDoorOnEdge(IsoDirections.N, false) &&
 !square5.hasDoorOnEdge(IsoDirections.S, false) {
 if (square5.hasDoorOnEdge(IsoDirections.E, false) {
 return false;
 }

 return true;
 }

 return false;
 }
 break;
 default:
 return false;
 }

 return false;
 } else {
 return false;
 }
 }

 IsoGridSquare getAddSheetSquare(IsoGameCharacter chr) {
 if (chr != nullptr && chr.getCurrentSquare() != nullptr) {
 IsoGridSquare square0 = chr.getCurrentSquare();
 IsoGridSquare square1 = this->getSquare();
 if (this->north) {
 return square0.getY() < square1.getY()
 ? this->getCell().getGridSquare(square1.x, square1.y - 1,
 square1.z)
 : square1;
 } else {
 return square0.getX() < square1.getX()
 ? this->getCell().getGridSquare(square1.x - 1, square1.y,
 square1.z)
 : square1;
 }
 } else {
 return nullptr;
 }
 }

 void addSheet(IsoGameCharacter chr) {
 IsoGridSquare square = this->getIndoorSquare();
 IsoObjectType objectType;
 if (this->north) {
 objectType = IsoObjectType.curtainN;
 if (square != this->square) {
 objectType = IsoObjectType.curtainS;
 }
 } else {
 objectType = IsoObjectType.curtainW;
 if (square != this->square) {
 objectType = IsoObjectType.curtainE;
 }
 }

 if (chr != nullptr) {
 if (this->north) {
 if (chr.getY() < this->getY()) {
 square = this->getCell().getGridSquare((double)this->getX(),
 (double)(this->getY() - 1.0F),
 (double)this->getZ());
 objectType = IsoObjectType.curtainS;
 } else {
 square = this->getSquare();
 objectType = IsoObjectType.curtainN;
 }
 } else if (chr.getX() < this->getX()) {
 square = this->getCell().getGridSquare((double)(this->getX() - 1.0F),
 (double)this->getY(),
 (double)this->getZ());
 objectType = IsoObjectType.curtainE;
 } else {
 square = this->getSquare();
 objectType = IsoObjectType.curtainW;
 }
 }

 if (square != nullptr) {
 if (square.getCurtain(objectType) == nullptr) {
 if (square != nullptr) {
 int int0 = 16;
 if (objectType == IsoObjectType.curtainE) {
 int0++;
 }

 if (objectType == IsoObjectType.curtainS) {
 int0 += 3;
 }

 if (objectType == IsoObjectType.curtainN) {
 int0 += 2;
 }

 int0 += 4;
 IsoCurtain curtain = new IsoCurtain(
 this->getCell(), square, "fixtures_windows_curtains_01_" + int0,
 this->north);
 square.AddSpecialTileObject(curtain);
 if (GameServer.bServer) {
 curtain.transmitCompleteItemToClients();
 chr.sendObjectChange("removeOneOf", new Object[]{"type", "Sheet"});
 } else {
 chr.getInventory().RemoveOneOf("Sheet");
 }
 }
 }
 }
 }

 IsoGridSquare getIndoorSquare() {
 if (this->square.getRoom() != nullptr) {
 return this->square;
 } else {
 IsoGridSquare square;
 if (this->north) {
 square = IsoWorld.instance.CurrentCell.getGridSquare(
 this->square.getX(), this->square.getY() - 1, this->square.getZ());
 } else {
 square = IsoWorld.instance.CurrentCell.getGridSquare(
 this->square.getX() - 1, this->square.getY(), this->square.getZ());
 }

 if (square.empty() || square.getFloor() == nullptr) {
 return this->square;
 } else if (square.getRoom() != nullptr) {
 return square;
 } else if (this->square.getFloor() == nullptr) {
 return square;
 } else {
 std::string string = square.getFloor().getSprite().getName();
 return string != nullptr && string.startsWith("carpentry_02_")
 ? square
 : this->square;
 }
 }
 }

 int getKeyId() { return this->keyId; }

 void setKeyId(int _keyId, bool doNetwork) {
 if (doNetwork && this->keyId != _keyId && GameClient.bClient) {
 this->keyId = _keyId;
 this->syncIsoThumpable();
 } else {
 this->keyId = _keyId;
 }
 }

 void setKeyId(int _keyId) { this->setKeyId(_keyId, true); }

 bool isLockedByKey() { return this->lockedByKey; }

 void setLockedByKey(bool _lockedByKey) {
 bool boolean0 = _lockedByKey != this->lockedByKey;
 this->lockedByKey = _lockedByKey;
 this->setIsLocked(_lockedByKey);
 if (!GameServer.bServer && boolean0) {
 if (_lockedByKey) {
 this->syncIsoObject(false, (byte)3, nullptr, nullptr);
 } else {
 this->syncIsoObject(false, (byte)4, nullptr, nullptr);
 }
 }
 }

 bool isLockedByPadlock() { return this->lockedByPadlock; }

 void syncIsoThumpable() {
 ByteBufferWriter byteBufferWriter = GameClient.connection.startPacket();
 PacketTypes.PacketType.SyncThumpable.doPacket(byteBufferWriter);
 byteBufferWriter.putInt(this->square.getX());
 byteBufferWriter.putInt(this->square.getY());
 byteBufferWriter.putInt(this->square.getZ());
 uint8_t byte0 = (byte)this->square.getObjects().indexOf(this);
 if (byte0 == -1) {
 System.out.println("ERROR: Thumpable door not found on square " +
 this->square.getX() + ", " + this->square.getY() + ", " +
 this->square.getZ());
 GameClient.connection.cancelPacket();
 } else {
 byteBufferWriter.putByte(byte0);
 byteBufferWriter.putInt(this->getLockedByCode());
 byteBufferWriter.putByte((byte)(this->lockedByPadlock ? 1 : 0);
 byteBufferWriter.putInt(this->getKeyId());
 PacketTypes.PacketType.SyncThumpable.send(GameClient.connection);
 }
 }

 void setLockedByPadlock(bool _lockedByPadlock) {
 if (this->lockedByPadlock != _lockedByPadlock && GameClient.bClient) {
 this->lockedByPadlock = _lockedByPadlock;
 this->syncIsoThumpable();
 } else {
 this->lockedByPadlock = _lockedByPadlock;
 }
 }

 bool canBeLockByPadlock() { return this->canBeLockByPadlock; }

 void setCanBeLockByPadlock(bool _canBeLockByPadlock) {
 this->canBeLockByPadlock = _canBeLockByPadlock;
 }

 int getLockedByCode() { return this->lockedByCode; }

 void setLockedByCode(int _lockedByCode) {
 if (this->lockedByCode != _lockedByCode && GameClient.bClient) {
 this->lockedByCode = _lockedByCode;
 this->syncIsoThumpable();
 } else {
 this->lockedByCode = _lockedByCode;
 }
 }

 bool isLockedToCharacter(IsoGameCharacter chr) {
 if (GameClient.bClient && chr instanceof
 IsoPlayer && !((IsoPlayer)chr).accessLevel == "")) {
 return false;
 }
 else {
 return this->getLockedByCode() > 0
 ? true
 : this->isLockedByPadlock() &&
 (chr.getInventory() == nullptr ||
 chr.getInventory().haveThisKeyId(this->getKeyId()) ==
 nullptr);
 }
 }

 bool canClimbOver(IsoGameCharacter chr) {
 if (this->square.empty()) {
 return false;
 } else {
 return !this->isHoppable()
 ? false
 : chr.empty() || IsoWindow.canClimbThroughHelper(
 chr, this->getSquare(),
 this->getOppositeSquare(), this->north);
 }
 }

 bool canClimbThrough(IsoGameCharacter chr) {
 if (this->square.empty()) {
 return false;
 } else if (!this->isWindow()) {
 return false;
 } else {
 return this->isBarricaded()
 ? false
 : chr.empty() || IsoWindow.canClimbThroughHelper(
 chr, this->getSquare(),
 this->getOppositeSquare(), this->north);
 }
 }

 std::string getThumpSound() { return this->thumpSound; }

 void setThumpSound(std::string_view _thumpSound) {
 this->thumpSound = _thumpSound;
 }

 IsoObject getRenderEffectMaster() {
 int int0 = IsoDoor.getDoubleDoorIndex(this);
 if (int0 != -1) {
 IsoObject object0 = nullptr;
 if (int0 == 2) {
 object0 = IsoDoor.getDoubleDoorObject(this, 1);
 } else if (int0 == 3) {
 object0 = IsoDoor.getDoubleDoorObject(this, 4);
 }

 if (object0 != nullptr) {
 return object0;
 }
 } else {
 IsoObject object1 = IsoDoor.getGarageDoorFirst(this);
 if (object1 != nullptr) {
 return object1;
 }
 }

 return this;
 }

 IsoDirections getSpriteEdge(bool ignoreOpen) {
 if (!this->isDoor() && !this->isWindow()) {
 return nullptr;
 } else if (this->open && !ignoreOpen) {
 PropertyContainer propertyContainer = this->getProperties();
 if (propertyContainer != nullptr &&
 propertyContainer.Is(IsoFlagType.attachedE) {
 return IsoDirections.E;
 } else if (propertyContainer != nullptr &&
 propertyContainer.Is(IsoFlagType.attachedS) {
 return IsoDirections.S;
 } else {
 return this->north ? IsoDirections.W : IsoDirections.N;
 }
 } else {
 return this->north ? IsoDirections.N : IsoDirections.W;
 }
 }

 std::string getSoundPrefix() {
 if (this->closedSprite.empty()) {
 return "WoodDoor";
 } else {
 PropertyContainer propertyContainer = this->closedSprite.getProperties();
 return propertyContainer.Is("DoorSound")
 ? propertyContainer.Val("DoorSound")
 : "WoodDoor";
 }
 }

 void playDoorSound(BaseCharacterSoundEmitter baseCharacterSoundEmitter,
 std::string_view string) {
 baseCharacterSoundEmitter.playSound(this->getSoundPrefix() + string, this);
 }
}
} // namespace objects
} // namespace iso
} // namespace zombie
