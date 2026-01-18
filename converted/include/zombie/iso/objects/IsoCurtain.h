#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/SystemDisabler.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/properties/PropertyContainer.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/LosUtil.h"
#include "zombie/iso/SpriteDetails/IsoObjectType.h"
#include "zombie/iso/Vector2.h"
#include "zombie/iso/objects/interfaces/BarricadeAble.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/PacketTypes.h"
#include "zombie/util/Type.h"
#include "zombie/util/list/PZArrayList.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {
namespace objects {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class IsoCurtain : public IsoObject {
public:
 bool Barricaded = false;
 int BarricideMaxStrength = 0;
 int BarricideStrength = 0;
 int Health = 1000;
 bool Locked = false;
 int MaxHealth = 1000;
 int PushedMaxStrength = 0;
 int PushedStrength = 0;
 IsoSprite closedSprite;
 bool north = false;
 bool open = false;
 IsoSprite openSprite;
 bool destroyed = false;

 void removeSheet(IsoGameCharacter chr) {
 this->square.transmitRemoveItemFromSquare(this);
 if (GameServer.bServer) {
 chr.sendObjectChange("addItemOfType", new Object[]{"type", "Base.Sheet"});
 } else {
 chr.getInventory().AddItem("Base.Sheet");
 }

 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 LosUtil.cachecleared[int0] = true;
 }

 GameTime.instance.lightSourceUpdate = 100.0F;
 IsoGridSquare.setRecalcLightTime(-1);
 }

 public IsoCurtain(IsoCell cell, IsoGridSquare gridSquare, IsoSprite gid, bool _north, bool spriteclosed) {
 this->OutlineOnMouseover = true;
 this->PushedMaxStrength = this->PushedStrength = 2500;
 if (spriteclosed) {
 this->openSprite = IsoSprite.getSprite(IsoSpriteManager.instance, gid, 4);
 this->closedSprite = gid;
 } else {
 this->closedSprite = IsoSprite.getSprite(IsoSpriteManager.instance, gid, -4);
 this->openSprite = gid;
 }

 this->open = true;
 this->sprite = this->openSprite;
 this->square = gridSquare;
 this->north = _north;
 this->DirtySlice();
 }

 public IsoCurtain(IsoCell cell, IsoGridSquare gridSquare, const std::string& gid, bool _north) {
 this->OutlineOnMouseover = true;
 this->PushedMaxStrength = this->PushedStrength = 2500;
 this->closedSprite = IsoSprite.getSprite(IsoSpriteManager.instance, gid, -4);
 this->openSprite = IsoSprite.getSprite(IsoSpriteManager.instance, gid, 0);
 this->open = true;
 this->sprite = this->openSprite;
 this->square = gridSquare;
 this->north = _north;
 this->DirtySlice();
 }

 public IsoCurtain(IsoCell cell) {
 super(cell);
 }

 std::string getObjectName() {
 return "Curtain";
 }

 Vector2 getFacingPosition(Vector2 pos) {
 if (this->square.empty()) {
 return pos.set(0.0F, 0.0F);
 } else if (this->getType() == IsoObjectType.curtainS) {
 return pos.set(this->getX() + 0.5F, this->getY() + 1.0F);
 } else if (this->getType() == IsoObjectType.curtainE) {
 return pos.set(this->getX() + 1.0F, this->getY() + 0.5F);
 } else {
 return this->north ? pos.set(this->getX() + 0.5F, this->getY()) : pos.set(this->getX(), this->getY() + 0.5F);
 }
 }

 void load(ByteBuffer input, int WorldVersion, bool IS_DEBUG_SAVE) {
 super.load(input, WorldVersion, IS_DEBUG_SAVE);
 this->open = input.get() == 1;
 this->north = input.get() == 1;
 this->Health = input.getInt();
 this->BarricideStrength = input.getInt();
 if (this->open) {
 this->closedSprite = IsoSprite.getSprite(IsoSpriteManager.instance, input.getInt());
 this->openSprite = this->sprite;
 } else {
 this->openSprite = IsoSprite.getSprite(IsoSpriteManager.instance, input.getInt());
 this->closedSprite = this->sprite;
 }

 if (SystemDisabler.doObjectStateSyncEnable && GameClient.bClient) {
 GameClient.instance.objectSyncReq.putRequestLoad(this->square);
 }
 }

 void save(ByteBuffer output, bool IS_DEBUG_SAVE) {
 super.save(output, IS_DEBUG_SAVE);
 output.put((byte)(this->open ? 1 : 0);
 output.put((byte)(this->north ? 1 : 0);
 output.putInt(this->Health);
 output.putInt(this->BarricideStrength);
 if (this->open) {
 output.putInt(this->closedSprite.ID);
 } else {
 output.putInt(this->openSprite.ID);
 }
 }

 bool getNorth() {
 return this->north;
 }

 bool IsOpen() {
 return this->open;
 }

 bool onMouseLeftClick(int x, int y) {
 return false;
 }

 bool canInteractWith(IsoGameCharacter chr) {
 if (chr != nullptr && chr.getCurrentSquare() != nullptr) {
 IsoGridSquare square = chr.getCurrentSquare();
 return (this->isAdjacentToSquare(square) || square == this->getOppositeSquare()) && !this->getSquare().isBlockedTo(square);
 } else {
 return false;
 }
 }

 IsoGridSquare getOppositeSquare() {
 if (this->getType() == IsoObjectType.curtainN) {
 return this->getCell().getGridSquare((double)this->getX(), (double)(this->getY() - 1.0F), (double)this->getZ());
 } else if (this->getType() == IsoObjectType.curtainS) {
 return this->getCell().getGridSquare((double)this->getX(), (double)(this->getY() + 1.0F), (double)this->getZ());
 } else if (this->getType() == IsoObjectType.curtainW) {
 return this->getCell().getGridSquare((double)(this->getX() - 1.0F), (double)this->getY(), (double)this->getZ());
 } else {
 return this->getType() == IsoObjectType.curtainE
 ? this->getCell().getGridSquare((double)(this->getX() + 1.0F), (double)this->getY(), (double)this->getZ())
 : nullptr;
 }
 }

 bool isAdjacentToSquare(IsoGridSquare square1, IsoGridSquare square2) {
 if (square1 != nullptr && square2 != nullptr) {
 return this->getType() != IsoObjectType.curtainN && this->getType() != IsoObjectType.curtainS
 ? square1.x == square2.x && Math.abs(square1.y - square2.y) <= 1
 : square1.y == square2.y && Math.abs(square1.x - square2.x) <= 1;
 } else {
 return false;
 }
 }

 bool isAdjacentToSquare(IsoGridSquare square2) {
 return this->isAdjacentToSquare(this->getSquare(), square2);
 }

 public IsoObject.VisionResult TestVision(IsoGridSquare from, IsoGridSquare to) {
 if (to.getZ() != from.getZ()) {
 return IsoObject.VisionResult.NoEffect;
 } else {
 if (from == this->square && (this->getType() == IsoObjectType.curtainW || this->getType() == IsoObjectType.curtainN)
 || from != this->square && (this->getType() == IsoObjectType.curtainE || this->getType() == IsoObjectType.curtainS) {
 if (this->north && to.getY() < from.getY() && !this->open) {
 return IsoObject.VisionResult.Blocked;
 }

 if (!this->north && to.getX() < from.getX() && !this->open) {
 return IsoObject.VisionResult.Blocked;
 }
 } else {
 if (this->north && to.getY() > from.getY() && !this->open) {
 return IsoObject.VisionResult.Blocked;
 }

 if (!this->north && to.getX() > from.getX() && !this->open) {
 return IsoObject.VisionResult.Blocked;
 }
 }

 return IsoObject.VisionResult.NoEffect;
 }
 }

 void ToggleDoor(IsoGameCharacter chr) {
 if (!this->Barricaded) {
 this->DirtySlice();
 if (!this->Locked || chr.empty() || chr.getCurrentSquare().getRoom() != nullptr || this->open) {
 this->open = !this->open;
 this->sprite = this->closedSprite;
 if (this->open) {
 this->sprite = this->openSprite;
 if (chr != nullptr) {
 chr.playSound(this->getSoundPrefix() + "Open");
 }
 } else if (chr != nullptr) {
 chr.playSound(this->getSoundPrefix() + "Close");
 }

 this->syncIsoObject(false, (byte)(this->open ? 1 : 0), nullptr);
 }
 }
 }

 void ToggleDoorSilent() {
 if (!this->Barricaded) {
 this->DirtySlice();

 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 LosUtil.cachecleared[int0] = true;
 }

 GameTime.instance.lightSourceUpdate = 100.0F;
 IsoGridSquare.setRecalcLightTime(-1);
 this->open = !this->open;
 this->sprite = this->closedSprite;
 if (this->open) {
 this->sprite = this->openSprite;
 }

 this->syncIsoObject(false, (byte)(this->open ? 1 : 0), nullptr);
 }
 }

 void render(float x, float y, float z, ColorInfo col, bool bDoAttached, bool bWallLightingPass, Shader shader) {
 int int0 = IsoCamera.frameState.playerIndex;
 IsoObject object = this->getObjectAttachedTo();
 if (object != nullptr && this->getSquare().getTargetDarkMulti(int0) <= object.getSquare().getTargetDarkMulti(int0) {
 col = object.getSquare().lighting[int0].lightInfo();
 this->setTargetAlpha(int0, object.getTargetAlpha(int0);
 }

 super.render(x, y, z, col, bDoAttached, bWallLightingPass, shader);
 }

 void syncIsoObjectSend(ByteBufferWriter b) {
 b.putInt(this->square.getX());
 b.putInt(this->square.getY());
 b.putInt(this->square.getZ());
 uint8_t byte0 = (byte)this->square.getObjects().indexOf(this);
 b.putByte(byte0);
 b.putByte((byte)1);
 b.putByte((byte)(this->open ? 1 : 0);
 }

 void syncIsoObject(bool bRemote, uint8_t val, UdpConnection source, ByteBuffer bb) {
 this->syncIsoObject(bRemote, val, source);
 }

 void syncIsoObject(bool bRemote, uint8_t val, UdpConnection source) {
 if (this->square.empty()) {
 System.out.println("ERROR: " + this->getClass().getSimpleName() + " square is nullptr");
 } else if (this->getObjectIndex() == -1) {
 System.out
 .println(
 "ERROR: "
 + this->getClass().getSimpleName()
 + " not found on square "
 + this->square.getX()
 + ","
 + this->square.getY()
 + ","
 + this->square.getZ()
 );
 } else {
 if (GameClient.bClient && !bRemote) {
 ByteBufferWriter byteBufferWriter0 = GameClient.connection.startPacket();
 PacketTypes.PacketType.SyncIsoObject.doPacket(byteBufferWriter0);
 this->syncIsoObjectSend(byteBufferWriter0);
 PacketTypes.PacketType.SyncIsoObject.send(GameClient.connection);
 } else if (bRemote) {
 if (val == 1) {
 this->open = true;
 this->sprite = this->openSprite;
 } else {
 this->open = false;
 this->sprite = this->closedSprite;
 }

 if (GameServer.bServer) {
 for (UdpConnection udpConnection : GameServer.udpEngine.connections) {
 if (source != nullptr && udpConnection.getConnectedGUID() != source.getConnectedGUID()) {
 ByteBufferWriter byteBufferWriter1 = udpConnection.startPacket();
 PacketTypes.PacketType.SyncIsoObject.doPacket(byteBufferWriter1);
 this->syncIsoObjectSend(byteBufferWriter1);
 PacketTypes.PacketType.SyncIsoObject.send(udpConnection);
 }
 }
 }
 }

 this->square.RecalcProperties();
 this->square.RecalcAllWithNeighbours(true);

 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 LosUtil.cachecleared[int0] = true;
 }

 IsoGridSquare.setRecalcLightTime(-1);
 GameTime.instance.lightSourceUpdate = 100.0F;
 LuaEventManager.triggerEvent("OnContainerUpdate");
 if (this->square != nullptr) {
 this->square.RecalcProperties();
 }
 }
 }

 IsoObject getObjectAttachedTo() {
 int int0 = this->getObjectIndex();
 if (int0 == -1) {
 return nullptr;
 } else {
 PZArrayList pZArrayList = this->getSquare().getObjects();
 if (this->getType() != IsoObjectType.curtainW && this->getType() != IsoObjectType.curtainN) {
 if (this->getType() == IsoObjectType.curtainE || this->getType() == IsoObjectType.curtainS) {
 IsoGridSquare square = this->getOppositeSquare();
 if (square != nullptr) {
 bool boolean0 = this->getType() == IsoObjectType.curtainS;
 pZArrayList = square.getObjects();

 for (int int1 = pZArrayList.size() - 1; int1 >= 0; int1--) {
 BarricadeAble barricadeAble0 = Type.tryCastTo((IsoObject)pZArrayList.get(int1), BarricadeAble.class);
 if (barricadeAble0 != nullptr && boolean0 == barricadeAble0.getNorth()) {
 return (IsoObject)pZArrayList.get(int1);
 }
 }
 }
 }
 } else {
 bool boolean1 = this->getType() == IsoObjectType.curtainN;

 for (int int2 = int0 - 1; int2 >= 0; int2--) {
 BarricadeAble barricadeAble1 = Type.tryCastTo((IsoObject)pZArrayList.get(int2), BarricadeAble.class);
 if (barricadeAble1 != nullptr && boolean1 == barricadeAble1.getNorth()) {
 return (IsoObject)pZArrayList.get(int2);
 }
 }
 }

 return nullptr;
 }
 }

 std::string getSoundPrefix() {
 if (this->closedSprite.empty()) {
 return "CurtainShort";
 } else {
 PropertyContainer propertyContainer = this->closedSprite.getProperties();
 return propertyContainer.Is("CurtainSound") ? "Curtain" + propertyContainer.Val("CurtainSound") : "CurtainShort";
 }
 }

 static bool isSheet(IsoObject curtain) {
 if (curtain instanceof IsoDoor) {
 curtain = ((IsoDoor)curtain).HasCurtains();
 }

 if (curtain instanceof IsoThumpable) {
 curtain = ((IsoThumpable)curtain).HasCurtains();
 }

 if (curtain instanceof IsoWindow) {
 curtain = ((IsoWindow)curtain).HasCurtains();
 }

 if (curtain != nullptr && ((IsoObject)curtain).getSprite() != nullptr) {
 IsoSprite sprite = ((IsoObject)curtain).getSprite();
 return sprite.getProperties().Is("CurtainSound") ? "Sheet" == sprite.getProperties().Val("CurtainSound")) : false;
 } else {
 return false;
 }
 }
}
} // namespace objects
} // namespace iso
} // namespace zombie
