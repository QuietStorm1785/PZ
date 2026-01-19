#pragma once
#include "zombie/AmbientStreamManager.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/SandboxOptions.h"
#include "zombie/SoundManager.h"
#include "zombie/SystemDisabler.h"
#include "zombie/WorldSoundManager.h"
#include "zombie/ai/states/ThumpState.h"
#include "zombie/audio/parameters/ParameterMeleeHitSurface.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoLivingCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/properties/PropertyContainer.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/RoomDef.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/SpriteDetails/IsoObjectType.h"
#include "zombie/iso/Vector2.h"
#include "zombie/iso/areas/IsoRoom.h"
#include "zombie/iso/areas/SafeHouse.h"
#include "zombie/iso/objects/interfaces/BarricadeAble.h"
#include "zombie/iso/objects/interfaces/Thumpable.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/PacketTypes.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/util/Type.h"
#include "zombie/vehicles/PolygonalMap2.h"
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

class IsoWindow : public IsoObject {
public:
 int Health = 75;
 int MaxHealth = 75;
public
 IsoWindow.WindowType type = IsoWindow.WindowType.SinglePane;
 IsoSprite closedSprite;
 IsoSprite smashedSprite;
 bool north = false;
 bool Locked = false;
 bool PermaLocked = false;
 bool open = false;
 IsoSprite openSprite;
 bool destroyed = false;
 bool glassRemoved = false;
 IsoSprite glassRemovedSprite;
 int OldNumPlanks;

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

 IsoGridSquare getIndoorSquare() {
 if (this->square.getRoom() != nullptr) {
 return this->square;
 } else {
 if (this->north) {
 IsoGridSquare square0 = IsoWorld.instance.CurrentCell.getGridSquare(
 this->square.getX(), this->square.getY() - 1, this->square.getZ());
 if (square0 != nullptr && square0.getRoom() != nullptr) {
 return square0;
 }
 } else {
 IsoGridSquare square1 = IsoWorld.instance.CurrentCell.getGridSquare(
 this->square.getX() - 1, this->square.getY(), this->square.getZ());
 if (square1 != nullptr && square1.getRoom() != nullptr) {
 return square1;
 }
 }

 return nullptr;
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

 void AttackObject(IsoGameCharacter owner) {
 super.AttackObject(owner);
 IsoObject object = this->square.getWall(this->north);
 if (object != nullptr) {
 object.AttackObject(owner);
 }
 }

 IsoGridSquare getInsideSquare() {
 if (this->square.empty()) {
 return nullptr;
 } else {
 return this->north ? this->getCell().getGridSquare(this->square.getX(),
 this->square.getY() - 1,
 this->square.getZ())
 : this->getCell().getGridSquare(this->square.getX() - 1,
 this->square.getY(),
 this->square.getZ());
 }
 }

 IsoGridSquare getOppositeSquare() { return this->getInsideSquare(); }

 bool isExterior() {
 IsoGridSquare square0 = this->getSquare();
 IsoGridSquare square1 = this->getOppositeSquare();
 return square1 = =
 nullptr ? false : square0.isInARoom() != square1.isInARoom();
 }

public
 IsoWindow(IsoCell cell) { super(cell); }

 std::string getObjectName() { return "Window"; }

 void WeaponHit(IsoGameCharacter owner, HandWeapon weapon) {
 IsoPlayer player = Type.tryCastTo(owner, IsoPlayer.class);
 if (GameClient.bClient) {
 if (player != nullptr) {
 GameClient.instance.sendWeaponHit(player, weapon, this);
 }
 } else {
 Thumpable thumpable = this->getThumpableFor(owner);
 if (thumpable != nullptr) {
 if (thumpable instanceof IsoBarricade) {
 ((IsoBarricade)thumpable).WeaponHit(owner, weapon);
 } else {
 LuaEventManager.triggerEvent("OnWeaponHitThumpable", owner, weapon,
 this);
 if (weapon == ((IsoLivingCharacter)owner).bareHands) {
 if (player != nullptr) {
 player.setMeleeHitSurface(
 ParameterMeleeHitSurface.Material.Glass);
 player.getEmitter().playSound(weapon.getDoorHitSound(), this);
 }
 } else {
 if (weapon != nullptr) {
 this->Damage(weapon.getDoorDamage() * 5, owner);
 } else {
 this->Damage(100.0F, owner);
 }

 this->DirtySlice();
 if (weapon != nullptr && weapon.getDoorHitSound() != nullptr) {
 if (player != nullptr) {
 player.setMeleeHitSurface(
 ParameterMeleeHitSurface.Material.Glass);
 }

 owner.getEmitter().playSound(weapon.getDoorHitSound(), this);
 if (GameServer.bServer) {
 GameServer.PlayWorldSoundServer(owner, weapon.getDoorHitSound(),
 false, this->getSquare(), 1.0F,
 20.0F, 2.0F, false);
 }
 }

 WorldSoundManager.instance.addSound(
 owner, this->square.getX(), this->square.getY(),
 this->square.getZ(), 20, 20, false, 0.0F, 15.0F);
 if (!this->isDestroyed() && this->Health <= 0) {
 this->smashWindow();
 this->addBrokenGlass(owner);
 }
 }
 }
 }
 }
 }

 void smashWindow(bool bRemote, bool doAlarm) {
 if (!this->destroyed) {
 if (GameClient.bClient && !bRemote) {
 GameClient.instance.smashWindow(this, 1);
 }

 if (!bRemote) {
 if (GameServer.bServer) {
 GameServer.PlayWorldSoundServer("SmashWindow", false, this->square,
 0.2F, 20.0F, 1.1F, true);
 } else {
 SoundManager.instance.PlayWorldSound("SmashWindow", this->square, 0.2F,
 20.0F, 1.0F, true);
 }

 WorldSoundManager.instance.addSound(
 nullptr, this->square.getX(), this->square.getY(), this->square.getZ(),
 10, 20, true, 4.0F, 15.0F);
 }

 this->destroyed = true;
 this->sprite = this->smashedSprite;
 if (this->getAttachedAnimSprite() != nullptr) {
 this->getSquare().removeBlood(false, true);
 System.out.println(this->wallBloodSplats);

 for (int int0 = 0; int0 < this->getAttachedAnimSprite().size(); int0++) {
 IsoSprite sprite =
 this->getAttachedAnimSprite().get(int0).parentSprite;
 if (sprite != nullptr &&
 sprite.getProperties().Is("AttachedToGlass")) {
 this->getAttachedAnimSprite().remove(int0);
 int0--;
 }
 }
 }

 this->getSquare().removeLightSwitch();
 if (doAlarm) {
 this->handleAlarm();
 }

 if (GameServer.bServer && !bRemote) {
 GameServer.smashWindow(this, 1);
 }

 this->square.InvalidateSpecialObjectPaths();
 }
 }

 void smashWindow(bool bRemote) { this->smashWindow(bRemote, true); }

 void smashWindow() { this->smashWindow(false, true); }

 void addBrokenGlass(IsoMovingObject chr) {
 if (chr != nullptr) {
 if (this->getSquare() != nullptr) {
 if (this->getNorth()) {
 this->addBrokenGlass(chr.getY() >= this->getSquare().getY());
 } else {
 this->addBrokenGlass(chr.getX() >= this->getSquare().getX());
 }
 }
 }
 }

 void addBrokenGlass(bool onOppositeSquare) {
 IsoGridSquare square =
 onOppositeSquare ? this->getOppositeSquare() : this->getSquare();
 if (square != nullptr) {
 square.addBrokenGlass();
 }
 }

 void handleAlarm() {
 if (!GameClient.bClient) {
 IsoGridSquare square = this->getIndoorSquare();
 if (square != nullptr) {
 IsoRoom room = square.getRoom();
 RoomDef roomDef = room.def;
 if (roomDef.building.bAlarmed && !GameClient.bClient) {
 AmbientStreamManager.instance.doAlarm(roomDef);
 }
 }
 }
 }

public
 IsoWindow(IsoCell cell, IsoGridSquare gridSquare, IsoSprite gid,
 bool _north) {
 gid.getProperties().UnSet(IsoFlagType.cutN);
 gid.getProperties().UnSet(IsoFlagType.cutW);
 int int0 = 0;
 if (gid.getProperties().Is("OpenTileOffset")) {
 int0 = Integer.parseInt(gid.getProperties().Val("OpenTileOffset"));
 }

 int int1 = 0;
 this->PermaLocked = gid.getProperties().Is("WindowLocked");
 if (gid.getProperties().Is("SmashedTileOffset")) {
 int1 = Integer.parseInt(gid.getProperties().Val("SmashedTileOffset"));
 }

 this->closedSprite = gid;
 if (_north) {
 this->closedSprite.getProperties().Set(IsoFlagType.cutN);
 this->closedSprite.getProperties().Set(IsoFlagType.windowN);
 } else {
 this->closedSprite.getProperties().Set(IsoFlagType.cutW);
 this->closedSprite.getProperties().Set(IsoFlagType.windowW);
 }

 this->openSprite = IsoSprite.getSprite(IsoSpriteManager.instance, gid, int0);
 this->smashedSprite =
 IsoSprite.getSprite(IsoSpriteManager.instance, gid, int1);
 if (this->closedSprite.getProperties().Is("GlassRemovedOffset")) {
 int int2 = Integer.parseInt(
 this->closedSprite.getProperties().Val("GlassRemovedOffset"));
 this->glassRemovedSprite = IsoSprite.getSprite(IsoSpriteManager.instance,
 this->closedSprite, int2);
 } else {
 this->glassRemovedSprite = this->smashedSprite;
 }

 if (this->smashedSprite != this->closedSprite &&
 this->smashedSprite != nullptr) {
 this->smashedSprite.AddProperties(this->closedSprite);
 this->smashedSprite.setType(this->closedSprite.getType());
 }

 if (this->openSprite != this->closedSprite && this->openSprite != nullptr) {
 this->openSprite.AddProperties(this->closedSprite);
 this->openSprite.setType(this->closedSprite.getType());
 }

 if (this->glassRemovedSprite != this->closedSprite &&
 this->glassRemovedSprite != nullptr) {
 this->glassRemovedSprite.AddProperties(this->closedSprite);
 this->glassRemovedSprite.setType(this->closedSprite.getType());
 }

 this->sprite = this->closedSprite;
 IsoObject object = gridSquare.getWall(_north);
 if (object != nullptr) {
 object.rerouteCollide = this;
 }

 this->square = gridSquare;
 this->north = _north;
 switch (this->type) {
 case SinglePane:
 this->MaxHealth = this->Health = 50;
 break;
 case DoublePane:
 this->MaxHealth = this->Health = 150;
 }

 uint8_t byte0 = 69;
 if (SandboxOptions.instance.LockedHouses.getValue() == 1) {
 byte0 = -1;
 } else if (SandboxOptions.instance.LockedHouses.getValue() == 2) {
 byte0 = 5;
 } else if (SandboxOptions.instance.LockedHouses.getValue() == 3) {
 byte0 = 10;
 } else if (SandboxOptions.instance.LockedHouses.getValue() == 4) {
 byte0 = 50;
 } else if (SandboxOptions.instance.LockedHouses.getValue() == 5) {
 byte0 = 60;
 } else if (SandboxOptions.instance.LockedHouses.getValue() == 6) {
 byte0 = 70;
 }

 if (byte0 > -1) {
 this->Locked = Rand.Next(100) < byte0;
 }
 }

 bool isDestroyed() { return this->destroyed; }

 bool IsOpen() { return this->open; }

 bool onMouseLeftClick(int x, int y) { return false; }

 bool TestCollide(IsoMovingObject obj, IsoGridSquare from, IsoGridSquare to) {
 if (from == this->square) {
 if (this->north && to.getY() < from.getY()) {
 if (obj != nullptr) {
 obj.collideWith(this);
 }

 return true;
 }

 if (!this->north && to.getX() < from.getX()) {
 if (obj != nullptr) {
 obj.collideWith(this);
 }

 return true;
 }
 } else {
 if (this->north && to.getY() > from.getY()) {
 if (obj != nullptr) {
 obj.collideWith(this);
 }

 return true;
 }

 if (!this->north && to.getX() > from.getX()) {
 if (obj != nullptr) {
 obj.collideWith(this);
 }

 return true;
 }
 }

 return false;
 }

public
 IsoObject.VisionResult TestVision(IsoGridSquare from, IsoGridSquare to) {
 if (to.getZ() != from.getZ()) {
 return IsoObject.VisionResult.NoEffect;
 } else {
 if (from == this->square) {
 if (this->north && to.getY() < from.getY()) {
 return IsoObject.VisionResult.Unblocked;
 }

 if (!this->north && to.getX() < from.getX()) {
 return IsoObject.VisionResult.Unblocked;
 }
 } else {
 if (this->north && to.getY() > from.getY()) {
 return IsoObject.VisionResult.Unblocked;
 }

 if (!this->north && to.getX() > from.getX()) {
 return IsoObject.VisionResult.Unblocked;
 }
 }

 return IsoObject.VisionResult.NoEffect;
 }
 }

 void Thump(IsoMovingObject thumper) {
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

 if (thumper instanceof IsoZombie) {
 if (((IsoZombie)thumper).cognition == 1 &&
 !this->canClimbThrough((IsoZombie)thumper) && !this->isInvincible() &&
 (!this->Locked ||
 thumper.getCurrentSquare() != nullptr &&
 !thumper.getCurrentSquare().Is(IsoFlagType.exterior)) {
 this->ToggleWindow((IsoGameCharacter)thumper);
 if (this->canClimbThrough((IsoZombie)thumper) {
 return;
 }
 }

 int int0 = ThumpState.getFastForwardDamageMultiplier();
 this->DirtySlice();
 this->Damage(((IsoZombie)thumper).strength * int0, thumper);
 WorldSoundManager.instance.addSound(
 thumper, this->square.getX(), this->square.getY(), this->square.getZ(),
 20, 20, true, 4.0F, 15.0F);
 }

 if (!this->isDestroyed() && this->Health <= 0) {
 if (this->getSquare().getBuilding() != nullptr) {
 this->getSquare().getBuilding().forceAwake();
 }

 if (GameServer.bServer) {
 GameServer.smashWindow(this, 1);
 GameServer.PlayWorldSoundServer(
 (IsoGameCharacter)thumper, "SmashWindow", false,
 thumper.getCurrentSquare(), 0.2F, 20.0F, 1.1F, true);
 }

 ((IsoGameCharacter)thumper).getEmitter().playSound("SmashWindow", this);
 WorldSoundManager.instance.addSound(
 nullptr, this->square.getX(), this->square.getY(), this->square.getZ(),
 10, 20, true, 4.0F, 15.0F);
 thumper.setThumpTarget(nullptr);
 this->destroyed = true;
 this->sprite = this->smashedSprite;
 this->square.InvalidateSpecialObjectPaths();
 this->addBrokenGlass(thumper);
 if (thumper instanceof
 IsoZombie && this->getThumpableFor((IsoZombie)thumper) != nullptr) {
 thumper.setThumpTarget(this->getThumpableFor((IsoZombie)thumper);
 }
 }
 }

 Thumpable getThumpableFor(IsoGameCharacter chr) {
 IsoBarricade barricade = this->getBarricadeForCharacter(chr);
 if (barricade != nullptr) {
 return barricade;
 } else if (!this->isDestroyed() && !this->IsOpen()) {
 return this;
 } else {
 barricade = this->getBarricadeOppositeCharacter(chr);
 return barricade != nullptr ? barricade : nullptr;
 }
 }

 float getThumpCondition() {
 return (float)PZMath.clamp(this->Health, 0, this->MaxHealth) / this->MaxHealth;
 }

 void load(ByteBuffer input, int WorldVersion, bool IS_DEBUG_SAVE) {
 super.load(input, WorldVersion, IS_DEBUG_SAVE);
 this->open = input.get() == 1;
 this->north = input.get() == 1;
 if (WorldVersion >= 87) {
 this->Health = input.getInt();
 } else {
 int int0 = input.getInt();
 this->Health = input.getInt();
 int int1 = input.getInt();
 if (WorldVersion >= 49) {
 short short0 = input.getShort();
 } else {
 int int2 = Math.max(int1, int0 * 1000);
 }

 this->OldNumPlanks = int0;
 }

 this->Locked = input.get() == 1;
 this->PermaLocked = input.get() == 1;
 this->destroyed = input.get() == 1;
 if (WorldVersion >= 64) {
 this->glassRemoved = input.get() == 1;
 if (input.get() == 1) {
 this->openSprite =
 IsoSprite.getSprite(IsoSpriteManager.instance, input.getInt());
 }

 if (input.get() == 1) {
 this->closedSprite =
 IsoSprite.getSprite(IsoSpriteManager.instance, input.getInt());
 }

 if (input.get() == 1) {
 this->smashedSprite =
 IsoSprite.getSprite(IsoSpriteManager.instance, input.getInt());
 }

 if (input.get() == 1) {
 this->glassRemovedSprite =
 IsoSprite.getSprite(IsoSpriteManager.instance, input.getInt());
 }
 } else {
 if (input.getInt() == 1) {
 this->openSprite =
 IsoSprite.getSprite(IsoSpriteManager.instance, input.getInt());
 }

 if (input.getInt() == 1) {
 this->closedSprite =
 IsoSprite.getSprite(IsoSpriteManager.instance, input.getInt());
 }

 if (input.getInt() == 1) {
 this->smashedSprite =
 IsoSprite.getSprite(IsoSpriteManager.instance, input.getInt());
 }

 if (this->closedSprite != nullptr) {
 if (this->destroyed &&
 this->closedSprite.getProperties().Is("SmashedTileOffset")) {
 int int3 = Integer.parseInt(
 this->closedSprite.getProperties().Val("SmashedTileOffset"));
 this->closedSprite = IsoSprite.getSprite(IsoSpriteManager.instance,
 this->closedSprite, -int3);
 }

 if (this->closedSprite.getProperties().Is("GlassRemovedOffset")) {
 int int4 = Integer.parseInt(
 this->closedSprite.getProperties().Val("GlassRemovedOffset"));
 this->glassRemovedSprite = IsoSprite.getSprite(
 IsoSpriteManager.instance, this->closedSprite, int4);
 }
 }

 if (this->glassRemovedSprite.empty()) {
 this->glassRemovedSprite = this->smashedSprite != nullptr
 ? this->smashedSprite
 : this->closedSprite;
 }
 }

 this->MaxHealth = input.getInt();
 if (this->closedSprite != nullptr) {
 if (this->north) {
 this->closedSprite.getProperties().Set(IsoFlagType.cutN);
 this->closedSprite.getProperties().Set(IsoFlagType.windowN);
 } else {
 this->closedSprite.getProperties().Set(IsoFlagType.cutW);
 this->closedSprite.getProperties().Set(IsoFlagType.windowW);
 }

 if (this->smashedSprite != this->closedSprite &&
 this->smashedSprite != nullptr) {
 this->smashedSprite.AddProperties(this->closedSprite);
 this->smashedSprite.setType(this->closedSprite.getType());
 }

 if (this->openSprite != this->closedSprite && this->openSprite != nullptr) {
 this->openSprite.AddProperties(this->closedSprite);
 this->openSprite.setType(this->closedSprite.getType());
 }

 if (this->glassRemovedSprite != this->closedSprite &&
 this->glassRemovedSprite != nullptr) {
 this->glassRemovedSprite.AddProperties(this->closedSprite);
 this->glassRemovedSprite.setType(this->closedSprite.getType());
 }
 }

 if (SystemDisabler.doObjectStateSyncEnable && GameClient.bClient) {
 GameClient.instance.objectSyncReq.putRequestLoad(this->square);
 }
 }

 void addToWorld() {
 super.addToWorld();
 this->getCell().addToWindowList(this);
 }

 void removeFromWorld() {
 super.removeFromWorld();
 this->getCell().removeFromWindowList(this);
 }

 void save(ByteBuffer output, bool IS_DEBUG_SAVE) {
 super.save(output, IS_DEBUG_SAVE);
 output.put((byte)(this->open ? 1 : 0);
 output.put((byte)(this->north ? 1 : 0);
 output.putInt(this->Health);
 output.put((byte)(this->Locked ? 1 : 0);
 output.put((byte)(this->PermaLocked ? 1 : 0);
 output.put((byte)(this->destroyed ? 1 : 0);
 output.put((byte)(this->glassRemoved ? 1 : 0);
 if (this->openSprite != nullptr) {
 output.put((byte)1);
 output.putInt(this->openSprite.ID);
 } else {
 output.put((byte)0);
 }

 if (this->closedSprite != nullptr) {
 output.put((byte)1);
 output.putInt(this->closedSprite.ID);
 } else {
 output.put((byte)0);
 }

 if (this->smashedSprite != nullptr) {
 output.put((byte)1);
 output.putInt(this->smashedSprite.ID);
 } else {
 output.put((byte)0);
 }

 if (this->glassRemovedSprite != nullptr) {
 output.put((byte)1);
 output.putInt(this->glassRemovedSprite.ID);
 } else {
 output.put((byte)0);
 }

 output.putInt(this->MaxHealth);
 }

 void saveState(ByteBuffer bb) { bb.put((byte)(this->Locked ? 1 : 0); }

 void loadState(ByteBuffer bb) {
 bool boolean0 = bb.get() == 1;
 if (boolean0 != this->Locked) {
 this->Locked = boolean0;
 }
 }

 void render(float x, float y, float z, ColorInfo col, bool bDoAttached,
 bool bWallLightingPass, Shader shader) {
 super.render(x, y, z, col, bDoAttached, bWallLightingPass, shader);
 }

 void openCloseCurtain(IsoGameCharacter chr) {
 if (chr == IsoPlayer.getInstance()) {
 void *object0 = nullptr;
 void *object1 = nullptr;
 IsoDirections directions = IsoDirections.N;
 if (this->north) {
 IsoGridSquare square0 = this->square;
 directions = IsoDirections.N;
 if (square0.getRoom() == nullptr) {
 square0 = this->getCell().getGridSquare(
 square0.getX(), square0.getY() - 1, square0.getZ());
 directions = IsoDirections.S;
 }

 object1 = object0;
 object0 = square0;
 } else {
 IsoGridSquare square1 = this->square;
 directions = IsoDirections.W;
 if (square1.getRoom() == nullptr) {
 square1 = this->getCell().getGridSquare(
 square1.getX() - 1, square1.getY(), square1.getZ());
 directions = IsoDirections.E;
 }

 object1 = object0;
 object0 = square1;
 }

 if (object0 != nullptr) {
 for (int int0 = 0;
 int0 < ((IsoGridSquare)object0).getSpecialObjects().size();
 int0++) {
 if (((IsoGridSquare)object0).getSpecialObjects().get(int0) instanceof
 IsoCurtain) {
 ((IsoCurtain)((IsoGridSquare)object0).getSpecialObjects().get(int0)
 .ToggleDoorSilent();
 return;
 }
 }
 }

 if (object1 != nullptr) {
 for (int int1 = 0;
 int1 < ((IsoGridSquare)object1).getSpecialObjects().size();
 int1++) {
 if (((IsoGridSquare)object1).getSpecialObjects().get(int1) instanceof
 IsoCurtain) {
 ((IsoCurtain)((IsoGridSquare)object1).getSpecialObjects().get(int1)
 .ToggleDoorSilent();
 return;
 }
 }
 }
 }
 }

 void removeSheet(IsoGameCharacter chr) {
 IsoGridSquare square0 = nullptr;
 IsoDirections directions = IsoDirections.N;
 if (this->north) {
 IsoGridSquare square1 = this->square;
 directions = IsoDirections.N;
 if (square1.getRoom() == nullptr) {
 square1 = this->getCell().getGridSquare(
 square1.getX(), square1.getY() - 1, square1.getZ());
 directions = IsoDirections.S;
 }

 square0 = square1;
 } else {
 IsoGridSquare square2 = this->square;
 directions = IsoDirections.W;
 if (square2.getRoom() == nullptr) {
 square2 = this->getCell().getGridSquare(square2.getX() - 1,
 square2.getY(), square2.getZ());
 directions = IsoDirections.E;
 }

 square0 = square2;
 }

 for (int int0 = 0; int0 < square0.getSpecialObjects().size(); int0++) {
 IsoObject object = square0.getSpecialObjects().get(int0);
 if (object instanceof IsoCurtain) {
 square0.transmitRemoveItemFromSquare(object);
 if (chr != nullptr) {
 if (GameServer.bServer) {
 chr.sendObjectChange("addItemOfType",
 new Object[]{"type", object.getName()});
 } else {
 chr.getInventory().AddItem(object.getName());
 }
 }
 break;
 }
 }
 }

 void addSheet(IsoGameCharacter chr) {
 IsoGridSquare square0 = nullptr;
 IsoObjectType objectType;
 if (this->north) {
 IsoGridSquare square1 = this->square;
 objectType = IsoObjectType.curtainN;
 if (chr != nullptr) {
 if (chr.getY() < this->getY()) {
 square1 = this->getCell().getGridSquare(
 square1.getX(), square1.getY() - 1, square1.getZ());
 objectType = IsoObjectType.curtainS;
 }
 } else if (square1.getRoom() == nullptr) {
 square1 = this->getCell().getGridSquare(
 square1.getX(), square1.getY() - 1, square1.getZ());
 objectType = IsoObjectType.curtainS;
 }

 square0 = square1;
 } else {
 IsoGridSquare square2 = this->square;
 objectType = IsoObjectType.curtainW;
 if (chr != nullptr) {
 if (chr.getX() < this->getX()) {
 square2 = this->getCell().getGridSquare(
 square2.getX() - 1, square2.getY(), square2.getZ());
 objectType = IsoObjectType.curtainE;
 }
 } else if (square2.getRoom() == nullptr) {
 square2 = this->getCell().getGridSquare(square2.getX() - 1,
 square2.getY(), square2.getZ());
 objectType = IsoObjectType.curtainE;
 }

 square0 = square2;
 }

 if (square0.getCurtain(objectType) == nullptr) {
 if (square0 != nullptr) {
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
 IsoCurtain curtain =
 new IsoCurtain(this->getCell(), square0,
 "fixtures_windows_curtains_01_" + int0, this->north);
 square0.AddSpecialTileObject(curtain);
 if (!curtain.open) {
 curtain.ToggleDoorSilent();
 }

 if (GameServer.bServer) {
 curtain.transmitCompleteItemToClients();
 if (chr != nullptr) {
 chr.sendObjectChange("removeOneOf", new Object[]{"type", "Sheet"});
 }
 } else if (chr != nullptr) {
 chr.getInventory().RemoveOneOf("Sheet");
 }
 }
 }
 }

 void ToggleWindow(IsoGameCharacter chr) {
 this->DirtySlice();
 IsoGridSquare.setRecalcLightTime(-1);
 if (!this->PermaLocked) {
 if (!this->destroyed) {
 if (chr.empty() || this->getBarricadeForCharacter(chr) == nullptr) {
 this->Locked = false;
 this->open = !this->open;
 this->sprite = this->closedSprite;
 this->square.InvalidateSpecialObjectPaths();
 if (this->open) {
 if (!(chr instanceof IsoZombie) ||
 SandboxOptions.getInstance()
 .Lore.TriggerHouseAlarm.getValue()) {
 this->handleAlarm();
 }

 this->sprite = this->openSprite;
 }

 this->square.RecalcProperties();
 this->syncIsoObject(false, (byte)(this->open ? 1 : 0), nullptr,
 nullptr);
 PolygonalMap2.instance.squareChanged(this->square);
 LuaEventManager.triggerEvent("OnContainerUpdate");
 }
 }
 }
 }

 void syncIsoObjectSend(ByteBufferWriter b) {
 b.putInt(this->square.getX());
 b.putInt(this->square.getY());
 b.putInt(this->square.getZ());
 uint8_t byte0 = (byte)this->square.getObjects().indexOf(this);
 b.putByte(byte0);
 b.putByte((byte)1);
 b.putByte((byte)(this->open ? 1 : 0);
 b.putByte((byte)(this->destroyed ? 1 : 0);
 b.putByte((byte)(this->Locked ? 1 : 0);
 b.putByte((byte)(this->PermaLocked ? 1 : 0);
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
 } else {
 if (GameClient.bClient && !bRemote) {
 ByteBufferWriter byteBufferWriter0 =
 GameClient.connection.startPacket();
 PacketTypes.PacketType.SyncIsoObject.doPacket(byteBufferWriter0);
 this->syncIsoObjectSend(byteBufferWriter0);
 PacketTypes.PacketType.SyncIsoObject.send(GameClient.connection);
 } else if (GameServer.bServer && !bRemote) {
 for (UdpConnection udpConnection0 : GameServer.udpEngine.connections) {
 ByteBufferWriter byteBufferWriter1 = udpConnection0.startPacket();
 PacketTypes.PacketType.SyncIsoObject.doPacket(byteBufferWriter1);
 this->syncIsoObjectSend(byteBufferWriter1);
 PacketTypes.PacketType.SyncIsoObject.send(udpConnection0);
 }
 } else if (bRemote) {
 bool boolean0 = bb.get() == 1;
 bool boolean1 = bb.get() == 1;
 bool boolean2 = bb.get() == 1;
 if (val == 1) {
 this->open = true;
 this->sprite = this->openSprite;
 } else if (val == 0) {
 this->open = false;
 this->sprite = this->closedSprite;
 }

 if (boolean0) {
 this->destroyed = true;
 this->sprite = this->smashedSprite;
 }

 this->Locked = boolean1;
 this->PermaLocked = boolean2;
 if (GameServer.bServer) {
 for (UdpConnection udpConnection1 :
 GameServer.udpEngine.connections) {
 if (source != nullptr && udpConnection1.getConnectedGUID() !=
 source.getConnectedGUID()) {
 ByteBufferWriter byteBufferWriter2 = udpConnection1.startPacket();
 PacketTypes.PacketType.SyncIsoObject.doPacket(byteBufferWriter2);
 this->syncIsoObjectSend(byteBufferWriter2);
 PacketTypes.PacketType.SyncIsoObject.send(udpConnection1);
 }
 }
 }

 this->square.RecalcProperties();
 LuaEventManager.triggerEvent("OnContainerUpdate");
 }
 }
 }

 static bool isTopOfSheetRopeHere(IsoGridSquare sq) {
 return sq.empty() ? false
 : sq.Is(IsoFlagType.climbSheetTopN) ||
 sq.Is(IsoFlagType.climbSheetTopS) ||
 sq.Is(IsoFlagType.climbSheetTopW) ||
 sq.Is(IsoFlagType.climbSheetTopE);
 }

 static bool isTopOfSheetRopeHere(IsoGridSquare sq, bool _north) {
 if (sq.empty()) {
 return false;
 } else {
 if (_north) {
 if (sq.Is(IsoFlagType.climbSheetTopN) {
 return true;
 }

 if (sq.nav[IsoDirections.N.index()] != nullptr &&
 sq.nav[IsoDirections.N.index()].Is(IsoFlagType.climbSheetTopS) {
 return true;
 }
 } else {
 if (sq.Is(IsoFlagType.climbSheetTopW) {
 return true;
 }

 if (sq.nav[IsoDirections.W.index()] != nullptr &&
 sq.nav[IsoDirections.W.index()].Is(IsoFlagType.climbSheetTopE) {
 return true;
 }
 }

 return false;
 }
 }

 bool haveSheetRope() { return isTopOfSheetRopeHere(); }

 static bool isSheetRopeHere(IsoGridSquare sq) {
 return sq.empty() ? false
 : sq.Is(IsoFlagType.climbSheetTopW) ||
 sq.Is(IsoFlagType.climbSheetTopN) ||
 sq.Is(IsoFlagType.climbSheetTopE) ||
 sq.Is(IsoFlagType.climbSheetTopS) ||
 sq.Is(IsoFlagType.climbSheetW) ||
 sq.Is(IsoFlagType.climbSheetN) ||
 sq.Is(IsoFlagType.climbSheetE) ||
 sq.Is(IsoFlagType.climbSheetS);
 }

 static bool canClimbHere(IsoGridSquare sq) {
 if (sq.empty()) {
 return false;
 } else if (sq.getProperties().Is(IsoFlagType.solid) {
 return false;
 } else {
 return sq.Has(IsoObjectType.stairsBN) || sq.Has(IsoObjectType.stairsMN) ||
 sq.Has(IsoObjectType.stairsTN)
 ? false
 : !sq.Has(IsoObjectType.stairsBW) &&
 !sq.Has(IsoObjectType.stairsMW) &&
 !sq.Has(IsoObjectType.stairsTW);
 }
 }

 static int countAddSheetRope(IsoGridSquare sq, bool _north) {
 if (isTopOfSheetRopeHere(sq, _north) {
 return 0;
 } else {
 IsoCell cell = IsoWorld.instance.CurrentCell;
 if (sq.TreatAsSolidFloor()) {
 if (_north) {
 IsoGridSquare square0 =
 cell.getOrCreateGridSquare(sq.getX(), sq.getY() - 1, sq.getZ());
 if (square0.empty() || square0.TreatAsSolidFloor() ||
 isSheetRopeHere(square0) || !canClimbHere(square0) {
 return 0;
 }

 sq = square0;
 } else {
 IsoGridSquare square1 =
 cell.getOrCreateGridSquare(sq.getX() - 1, sq.getY(), sq.getZ());
 if (square1.empty() || square1.TreatAsSolidFloor() ||
 isSheetRopeHere(square1) || !canClimbHere(square1) {
 return 0;
 }

 sq = square1;
 }
 }

 for (int int0 = 1; sq != nullptr; int0++) {
 if (!canClimbHere(sq) {
 return 0;
 }

 if (sq.TreatAsSolidFloor()) {
 return int0;
 }

 if (sq.getZ() == 0) {
 return int0;
 }

 sq = cell.getOrCreateGridSquare(sq.getX(), sq.getY(), sq.getZ() - 1);
 }

 return 0;
 }
 }

 int countAddSheetRope() { return countAddSheetRope(); }

 static bool canAddSheetRope(IsoGridSquare sq, bool _north) {
 return countAddSheetRope();
 }

 bool canAddSheetRope() {
 return !this->canClimbThrough(nullptr)
 ? false
 : canAddSheetRope(this->square, this->north);
 }

 bool addSheetRope(IsoPlayer player, std::string_view itemType) {
 return !this->canAddSheetRope()
 ? false
 : addSheetRope(player, this->square, this->north, itemType);
 }

 static bool addSheetRope(IsoPlayer player, IsoGridSquare sq, bool _north,
 std::string_view itemType) {
 bool boolean0 = false;
 int int0 = 0;
 uint8_t byte0 = 0;
 if (_north) {
 byte0 = 1;
 }

 bool boolean1 = false;
 bool boolean2 = false;
 IsoGridSquare square0 = nullptr;
 IsoGridSquare square1 = nullptr;
 IsoCell cell = IsoWorld.instance.CurrentCell;
 if (sq.TreatAsSolidFloor()) {
 if (!_north) {
 square0 = cell.getGridSquare(sq.getX() - 1, sq.getY(), sq.getZ());
 if (square0 != nullptr) {
 boolean2 = true;
 byte0 = 3;
 }
 } else {
 square1 = cell.getGridSquare(sq.getX(), sq.getY() - 1, sq.getZ());
 if (square1 != nullptr) {
 boolean1 = true;
 byte0 = 4;
 }
 }
 }

 if (sq.getProperties().Is(IsoFlagType.solidfloor) {
 }

 while (sq != nullptr &&
 (GameServer.bServer || player.getInventory().contains(itemType)) {
 std::string string = "crafted_01_" + byte0;
 if (int0 > 0) {
 if (boolean2) {
 string = "crafted_01_10";
 } else if (boolean1) {
 string = "crafted_01_13";
 } else {
 string = "crafted_01_" + (byte0 + 8);
 }
 }

 IsoObject object = new IsoObject(cell, sq, string);
 object.setName(itemType);
 object.sheetRope = true;
 sq.getObjects().add(object);
 object.transmitCompleteItemToClients();
 sq.haveSheetRope = true;
 if (boolean1 && int0 == 0) {
 sq = square1;
 object = new IsoObject(cell, square1, "crafted_01_5");
 object.setName(itemType);
 object.sheetRope = true;
 square1.getObjects().add(object);
 object.transmitCompleteItemToClients();
 }

 if (boolean2 && int0 == 0) {
 sq = square0;
 object = new IsoObject(cell, square0, "crafted_01_2");
 object.setName(itemType);
 object.sheetRope = true;
 square0.getObjects().add(object);
 object.transmitCompleteItemToClients();
 }

 sq.RecalcProperties();
 sq.getProperties().UnSet(IsoFlagType.solidtrans);
 if (GameServer.bServer) {
 if (int0 == 0) {
 player.sendObjectChange("removeOneOf", new Object[]{"type", "Nails"});
 }

 player.sendObjectChange("removeOneOf", new Object[]{"type", itemType});
 } else {
 if (int0 == 0) {
 player.getInventory().RemoveOneOf("Nails");
 }

 player.getInventory().RemoveOneOf(itemType);
 }

 int0++;
 if (boolean0) {
 break;
 }

 sq = cell.getOrCreateGridSquare(sq.getX(), sq.getY(), sq.getZ() - 1);
 if (sq != nullptr && sq.TreatAsSolidFloor()) {
 boolean0 = true;
 }
 }

 return true;
 }

 bool removeSheetRope(IsoPlayer player) {
 return !this->haveSheetRope()
 ? false
 : removeSheetRope(player, this->square, this->north);
 }

 static bool removeSheetRope(IsoPlayer player, IsoGridSquare square,
 bool _north) {
 if (square.empty()) {
 return false;
 } else {
 IsoGridSquare _square = square;
 square.haveSheetRope = false;
 IsoFlagType flagType0;
 IsoFlagType flagType1;
 if (_north) {
 if (square.Is(IsoFlagType.climbSheetTopN) {
 flagType0 = IsoFlagType.climbSheetTopN;
 flagType1 = IsoFlagType.climbSheetN;
 } else {
 if (square.nav[IsoDirections.N.index()] == nullptr ||
 !square.nav[IsoDirections.N.index()].Is(
 IsoFlagType.climbSheetTopS) {
 return false;
 }

 flagType0 = IsoFlagType.climbSheetTopS;
 flagType1 = IsoFlagType.climbSheetS;
 std::string string0 = "crafted_01_4";

 for (int int0 = 0; int0 < _square.getObjects().size(); int0++) {
 IsoObject object0 = _square.getObjects().get(int0);
 if (object0.sprite != nullptr &&
 object0.sprite.getName() != nullptr &&
 object0.sprite.getName() == string0) {
 _square.transmitRemoveItemFromSquare(object0);
 break;
 }
 }

 _square = square.nav[IsoDirections.N.index()];
 }
 } else if (square.Is(IsoFlagType.climbSheetTopW) {
 flagType0 = IsoFlagType.climbSheetTopW;
 flagType1 = IsoFlagType.climbSheetW;
 } else {
 if (square.nav[IsoDirections.W.index()] == nullptr ||
 !square.nav[IsoDirections.W.index()].Is(
 IsoFlagType.climbSheetTopE) {
 return false;
 }

 flagType0 = IsoFlagType.climbSheetTopE;
 flagType1 = IsoFlagType.climbSheetE;
 std::string string1 = "crafted_01_3";

 for (int int1 = 0; int1 < _square.getObjects().size(); int1++) {
 IsoObject object1 = _square.getObjects().get(int1);
 if (object1.sprite != nullptr &&
 object1.sprite.getName() != nullptr &&
 object1.sprite.getName() == string1) {
 _square.transmitRemoveItemFromSquare(object1);
 break;
 }
 }

 _square = square.nav[IsoDirections.W.index()];
 }

 while (_square != nullptr) {
 bool boolean0 = false;

 for (int int2 = 0; int2 < _square.getObjects().size(); int2++) {
 IsoObject object2 = _square.getObjects().get(int2);
 if (object2.getProperties() != nullptr &&
 (object2.getProperties().Is(flagType0) ||
 object2.getProperties().Is(flagType1)) {
 _square.transmitRemoveItemFromSquare(object2);
 if (GameServer.bServer) {
 if (player != nullptr) {
 player.sendObjectChange(
 "addItemOfType", new Object[]{"type", object2.getName()});
 }
 } else if (player != nullptr) {
 player.getInventory().AddItem(object2.getName());
 }

 boolean0 = true;
 break;
 }
 }

 if (!boolean0 || _square.getZ() == 0) {
 break;
 }

 _square = _square.getCell().getGridSquare(
 _square.getX(), _square.getY(), _square.getZ() - 1);
 }

 return true;
 }
 }

 void Damage(float amount) { this->Damage(amount, false); }

 void Damage(float amount, bool isZombie) {
 if (!this->isInvincible() && !"Tutorial" == Core.GameMode) {
 this->DirtySlice();
 this->Health = (int)(this->Health - amount);
 if (this->Health < 0) {
 this->Health = 0;
 }

 if (!this->isDestroyed() && this->Health == 0) {
 this->smashWindow(false,
 !isZombie || SandboxOptions.getInstance()
 .Lore.TriggerHouseAlarm.getValue());
 if (this->getSquare().getBuilding() != nullptr) {
 this->getSquare().getBuilding().forceAwake();
 }
 }
 }
 }

 void Damage(float amount, IsoMovingObject chr) {
 if (!this->isInvincible() && !"Tutorial" == Core.GameMode) {
 this->Health = (int)(this->Health - amount);
 if (this->Health < 0) {
 this->Health = 0;
 }

 if (!this->isDestroyed() && this->Health == 0) {
 bool boolean0 =
 !(chr instanceof IsoZombie) ||
 SandboxOptions.getInstance().Lore.TriggerHouseAlarm.getValue();
 this->smashWindow(false, boolean0);
 this->addBrokenGlass(chr);
 }
 }
 }

 bool isLocked() { return this->Locked; }

 bool isSmashed() { return this->destroyed; }

 bool isInvincible() {
 if (this->square != nullptr &&
 this->square.Is(IsoFlagType.makeWindowInvincible) {
 int int0 = this->getObjectIndex();
 if (int0 != -1) {
 IsoObject[] objects = this->square.getObjects().getElements();
 int int1 = this->square.getObjects().size();

 for (int int2 = 0; int2 < int1; int2++) {
 if (int2 != int0) {
 IsoObject object = objects[int2];
 PropertyContainer propertyContainer = object.getProperties();
 if (propertyContainer != nullptr &&
 propertyContainer.Is(this->getNorth() ? IsoFlagType.cutN
 : IsoFlagType.cutW) &&
 propertyContainer.Is(IsoFlagType.makeWindowInvincible) {
 return true;
 }
 }
 }
 }

 return this->sprite != nullptr &&
 this->sprite.getProperties().Is(IsoFlagType.makeWindowInvincible);
 } else {
 return false;
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

 bool isBarricadeAllowed() { return true; }

 IsoBarricade getBarricadeForCharacter(IsoGameCharacter chr) {
 return IsoBarricade.GetBarricadeForCharacter(this, chr);
 }

 IsoBarricade getBarricadeOppositeCharacter(IsoGameCharacter chr) {
 return IsoBarricade.GetBarricadeOppositeCharacter(this, chr);
 }

 bool getNorth() { return this->north; }

 Vector2 getFacingPosition(Vector2 pos) {
 if (this->square.empty()) {
 return pos.set(0.0F, 0.0F);
 } else {
 return this->north ? pos.set(this->getX() + 0.5F, this->getY())
 : pos.set(this->getX(), this->getY() + 0.5F);
 }
 }

 void setIsLocked(bool lock) { this->Locked = lock; }

 IsoSprite getOpenSprite() { return this->openSprite; }

 void setOpenSprite(IsoSprite sprite) { this->openSprite = sprite; }

 void setSmashed(bool _destroyed) {
 if (_destroyed) {
 this->destroyed = true;
 this->sprite = this->smashedSprite;
 } else {
 this->destroyed = false;
 this->sprite = this->open ? this->openSprite : this->closedSprite;
 this->Health = this->MaxHealth;
 }

 this->glassRemoved = false;
 }

 IsoSprite getSmashedSprite() { return this->smashedSprite; }

 void setSmashedSprite(IsoSprite sprite) { this->smashedSprite = sprite; }

 void setPermaLocked(bool permaLock) { this->PermaLocked = permaLock; }

 bool isPermaLocked() { return this->PermaLocked; }

 static bool canClimbThroughHelper(IsoGameCharacter chr, IsoGridSquare sq,
 IsoGridSquare oppositeSq, bool _north) {
 IsoGridSquare square = sq;
 float float0 = 0.5F;
 float float1 = 0.5F;
 if (_north) {
 if (chr.getY() >= sq.getY()) {
 square = oppositeSq;
 float1 = 0.7F;
 } else {
 float1 = 0.3F;
 }
 } else if (chr.getX() >= sq.getX()) {
 square = oppositeSq;
 float0 = 0.7F;
 } else {
 float0 = 0.3F;
 }

 if (square.empty()) {
 return false;
 } else if (square.isSolid()) {
 return false;
 } else if (square.Is(IsoFlagType.water) {
 return false;
 } else {
 return !chr.canClimbDownSheetRope(square) && !square.HasStairsBelow() &&
 !PolygonalMap2.instance.canStandAt(square.x + float0,
 square.y + float1,
 square.z, nullptr, 19)
 ? !square.TreatAsSolidFloor()
 : !GameClient.bClient || !(chr instanceof IsoPlayer) ||
 SafeHouse.isSafeHouse(square,
 ((IsoPlayer)chr).getUsername(),
 true) == nullptr ||
 ServerOptions.instance.SafehouseAllowTrepass.getValue();
 }
 }

 bool canClimbThrough(IsoGameCharacter chr) {
 if (this->square.empty() || this->isInvincible()) {
 return false;
 } else if (this->isBarricaded()) {
 return false;
 } else if (chr != nullptr &&
 !canClimbThroughHelper(chr, this->getSquare(),
 this->getOppositeSquare(), this->north) {
 return false;
 } else {
 IsoGameCharacter character = this->getFirstCharacterClosing();
 if (character != nullptr &&
 character.isVariable("CloseWindowOutcome", "success")) {
 return false;
 } else {
 return this->Health > 0 && !this->destroyed ? this->open : true;
 }
 }
 }

 IsoGameCharacter getFirstCharacterClimbingThrough() {
 IsoGameCharacter character =
 this->getFirstCharacterClimbingThrough(this->getSquare());
 return character != nullptr ? character
 : this->getFirstCharacterClimbingThrough(
 this->getOppositeSquare());
 }

 IsoGameCharacter getFirstCharacterClimbingThrough(IsoGridSquare square) {
 if (square.empty()) {
 return nullptr;
 } else {
 for (int int0 = 0; int0 < square.getMovingObjects().size(); int0++) {
 IsoGameCharacter character = Type.tryCastTo(
 square.getMovingObjects().get(int0), IsoGameCharacter.class);
 if (character != nullptr && character.isClimbingThroughWindow(this) {
 return character;
 }
 }

 return nullptr;
 }
 }

 IsoGameCharacter getFirstCharacterClosing() {
 IsoGameCharacter character =
 this->getFirstCharacterClosing(this->getSquare());
 return character != nullptr
 ? character
 : this->getFirstCharacterClosing(this->getOppositeSquare());
 }

 IsoGameCharacter getFirstCharacterClosing(IsoGridSquare square) {
 if (square.empty()) {
 return nullptr;
 } else {
 for (int int0 = 0; int0 < square.getMovingObjects().size(); int0++) {
 IsoGameCharacter character = Type.tryCastTo(
 square.getMovingObjects().get(int0), IsoGameCharacter.class);
 if (character != nullptr && character.isClosingWindow(this) {
 return character;
 }
 }

 return nullptr;
 }
 }

 bool isGlassRemoved() { return this->glassRemoved; }

 void setGlassRemoved(bool removed) {
 if (this->destroyed) {
 if (removed) {
 this->sprite = this->glassRemovedSprite;
 this->glassRemoved = true;
 } else {
 this->sprite = this->smashedSprite;
 this->glassRemoved = false;
 }

 if (this->getObjectIndex() != -1) {
 PolygonalMap2.instance.squareChanged(this->square);
 }
 }
 }

 void removeBrokenGlass() {
 if (GameClient.bClient) {
 GameClient.instance.smashWindow(this, 2);
 } else {
 this->setGlassRemoved(true);
 }
 }

 IsoBarricade addBarricadesDebug(int numPlanks, bool metal) {
 IsoGridSquare square =
 this->square.getRoom() == nullptr ? this->square : this->getOppositeSquare();
 bool boolean0 = square != this->square;
 IsoBarricade barricade = IsoBarricade.AddBarricadeToObject(this, boolean0);
 if (barricade != nullptr) {
 for (int int0 = 0; int0 < numPlanks; int0++) {
 if (metal) {
 barricade.addMetalBar(nullptr, nullptr);
 } else {
 barricade.addPlank(nullptr, nullptr);
 }
 }
 }

 return barricade;
 }

 void addRandomBarricades() {
 IsoGridSquare square =
 this->square.getRoom() == nullptr ? this->square : this->getOppositeSquare();
 if (this->getZ() == 0.0F && square != nullptr &&
 square.getRoom() == nullptr) {
 bool boolean0 = square != this->square;
 IsoBarricade barricade =
 IsoBarricade.AddBarricadeToObject(this, boolean0);
 if (barricade != nullptr) {
 int int0 = Rand.Next(1, 4);

 for (int int1 = 0; int1 < int0; int1++) {
 barricade.addPlank(nullptr, nullptr);
 }

 if (GameServer.bServer) {
 barricade.transmitCompleteItemToClients();
 }
 }
 } else {
 this->addSheet(nullptr);
 this->HasCurtains().ToggleDoor(nullptr);
 }
 }

public
 static enum WindowType { SinglePane, DoublePane; }
}
} // namespace objects
} // namespace iso
} // namespace zombie
