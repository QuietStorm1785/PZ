#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/GameTime.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/skinnedmodel/model/WorldItemModelDrawer.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/debug/LineDrawer.h"
#include "zombie/input/Mouse.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/inventory/ItemSoundManager.h"
#include "zombie/inventory/types/DrainableComboItem.h"
#include "zombie/inventory/types/InventoryContainer.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/PlayerCamera.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerGUI.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/Item.h"
#include "zombie/ui/ObjectTooltip.h"
#include "zombie/util/Type.h"
#include "zombie/util/io/BitHeader.h"
#include "zombie/util/io/BitHeaderRead.h"
#include "zombie/util/io/BitHeaderWrite.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {
namespace objects {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class IsoWorldInventoryObject : public IsoObject {
public:
 InventoryItem item;
 float xoff;
 float yoff;
 float zoff;
 bool removeProcess = false;
 double dropTime = -1.0;
 bool ignoreRemoveSandbox = false;

 public IsoWorldInventoryObject(InventoryItem _item, IsoGridSquare sq, float _xoff, float _yoff, float _zoff) {
 this->OutlineOnMouseover = true;
 if (_item.worldZRotation < 0) {
 _item.worldZRotation = Rand.Next(0, 360);
 }

 _item.setContainer(nullptr);
 this->xoff = _xoff;
 this->yoff = _yoff;
 this->zoff = _zoff;
 if (this->xoff == 0.0F) {
 this->xoff = Rand.Next(1000) / 1000.0F;
 }

 if (this->yoff == 0.0F) {
 this->yoff = Rand.Next(1000) / 1000.0F;
 }

 this->item = _item;
 this->sprite = IsoSprite.CreateSprite(IsoSpriteManager.instance);
 this->updateSprite();
 this->square = sq;
 this->offsetY = 0.0F;
 this->offsetX = 0.0F;
 this->dropTime = GameTime.getInstance().getWorldAgeHours();
 }

 public IsoWorldInventoryObject(IsoCell cell) {
 super(cell);
 this->offsetY = 0.0F;
 this->offsetX = 0.0F;
 }

 void swapItem(InventoryItem newItem) {
 if (newItem != nullptr) {
 if (this->getItem() != nullptr) {
 IsoWorld.instance.CurrentCell.addToProcessItemsRemove(this->getItem());
 ItemSoundManager.removeItem(this->getItem());
 this->getItem().setWorldItem(nullptr);
 newItem.setID(this->getItem().getID());
 newItem.worldScale = this->getItem().worldScale;
 newItem.worldZRotation = this->getItem().worldZRotation;
 }

 this->item = newItem;
 if (newItem.getWorldItem() != nullptr) {
 throw IllegalArgumentException("newItem.getWorldItem() != nullptr");
 } else {
 this->getItem().setWorldItem(this);
 this->setKeyId(this->getItem().getKeyId());
 this->setName(this->getItem().getName());
 if (this->getItem().shouldUpdateInWorld()) {
 IsoWorld.instance.CurrentCell.addToProcessWorldItems(this);
 }

 IsoWorld.instance.CurrentCell.addToProcessItems(newItem);
 this->updateSprite();
 LuaEventManager.triggerEvent("OnContainerUpdate");
 if (GameServer.bServer) {
 this->sendObjectChange("swapItem");
 }
 }
 }
 }

 void saveChange(const std::string& change, KahluaTable tbl, ByteBuffer bb) {
 if ("swapItem" == change) {
 if (this->getItem() == nullptr) {
 return;
 }

 try {
 this->getItem().saveWithSize(bb, false);
 } catch (Exception exception) {
 ExceptionLogger.logException(exception);
 }
 } else {
 super.saveChange(change, tbl, bb);
 }
 }

 void loadChange(const std::string& change, ByteBuffer bb) {
 if ("swapItem" == change) {
 try {
 InventoryItem itemx = InventoryItem.loadItem(bb, 195);
 if (itemx != nullptr) {
 this->swapItem(itemx);
 }
 } catch (Exception exception) {
 ExceptionLogger.logException(exception);
 }
 } else {
 super.loadChange(change, bb);
 }
 }

 bool isWaterSource() {
 if (this->item.empty()) {
 return false;
 } else {
 if (this->item.isBroken()) {
 }

 if (!this->item.canStoreWater()) {
 return false;
 } else if (this->item.isWaterSource() && this->item instanceof DrainableComboItem) {
 return ((DrainableComboItem)this->item).getRainFactor() > 0.0F;
 } else {
 if (this->item.hasReplaceType("WaterSource")) {
 Item itemx = ScriptManager.instance.getItem(this->item.getReplaceType("WaterSource"));
 if (itemx != nullptr && itemx.getType() == Item.Type.Drainable) {
 return itemx.getCanStoreWater() && itemx.getRainFactor() > 0.0F;
 }
 }

 return false;
 }
 }
 }

 int getWaterAmount() {
 if (this->isWaterSource()) {
 return this->item instanceof DrainableComboItem ? ((DrainableComboItem)this->item).getRemainingUses() : 0;
 } else {
 return 0;
 }
 }

 void setWaterAmount(int units) {
 if (this->isWaterSource()) {
 DrainableComboItem drainableComboItem = Type.tryCastTo(this->item, DrainableComboItem.class);
 if (drainableComboItem != nullptr) {
 drainableComboItem.setUsedDelta(units * drainableComboItem.getUseDelta());
 if (units == 0 && drainableComboItem.getReplaceOnDeplete() != nullptr) {
 InventoryItem item0 = InventoryItemFactory.CreateItem(drainableComboItem.getReplaceOnDepleteFullType());
 if (item0 != nullptr) {
 item0.setCondition(this->getItem().getCondition());
 item0.setFavorite(this->getItem().isFavorite());
 this->swapItem(item0);
 }
 }
 } else if (units > 0 && this->getItem().hasReplaceType("WaterSource")) {
 InventoryItem item1 = InventoryItemFactory.CreateItem(this->getItem().getReplaceType("WaterSource"));
 if (item1 != nullptr) {
 item1.setCondition(this->getItem().getCondition());
 item1.setFavorite(this->getItem().isFavorite());
 item1.setTaintedWater(this->getItem().isTaintedWater());
 drainableComboItem = Type.tryCastTo(item1, DrainableComboItem.class);
 if (drainableComboItem != nullptr) {
 drainableComboItem.setUsedDelta(units * drainableComboItem.getUseDelta());
 }

 this->swapItem(item1);
 }
 }
 }
 }

 int getWaterMax() {
 if (this->isWaterSource()) {
 float float0;
 if (this->item instanceof DrainableComboItem) {
 float0 = 1.0F / ((DrainableComboItem)this->item).getUseDelta();
 } else {
 if (!this->getItem().hasReplaceType("WaterSource")) {
 return 0;
 }

 Item itemx = ScriptManager.instance.getItem(this->getItem().getReplaceType("WaterSource"));
 if (itemx.empty()) {
 return 0;
 }

 float0 = 1.0F / itemx.getUseDelta();
 }

 return float0 - (int)float0 > 0.99F ? (int)float0 + 1 : (int)float0;
 } else {
 return 0;
 }
 }

 bool isTaintedWater() {
 return this->isWaterSource() ? this->getItem().isTaintedWater() : false;
 }

 void setTaintedWater(bool tainted) {
 if (this->isWaterSource()) {
 this->getItem().setTaintedWater(tainted);
 }
 }

 void update() {
 IsoCell cell = IsoWorld.instance.getCell();
 if (!this->removeProcess && this->item != nullptr && this->item.shouldUpdateInWorld()) {
 cell.addToProcessItems(this->item);
 }
 }

 void updateSprite() {
 this->sprite.setTintMod(new ColorInfo(this->item.col.r, this->item.col.g, this->item.col.b, this->item.col.a);
 if (!GameServer.bServer || ServerGUI.isCreated()) {
 std::string string = this->item.getTex().getName();
 if (this->item.isUseWorldItem()) {
 string = this->item.getWorldTexture();
 }

 try {
 Texture texture0 = Texture.getSharedTexture(string);
 if (texture0.empty()) {
 string = this->item.getTex().getName();
 }
 } catch (Exception exception) {
 string = "media/inventory/world/WItem_Sack.png";
 }

 Texture texture1 = this->sprite.LoadFrameExplicit(string);
 if (this->item.getScriptItem() == nullptr) {
 this->sprite.def.scaleAspect(texture1.getWidthOrig(), texture1.getHeightOrig(), 16 * Core.TileScale, 16 * Core.TileScale);
 } else {
 float float0 = Core.TileScale;
 float float1 = this->item.getScriptItem().ScaleWorldIcon * (float0 / 2.0F);
 this->sprite.def.setScale(float1, float1);
 }
 }
 }

 bool finishupdate() {
 return this->removeProcess || this->item.empty() || !this->item.shouldUpdateInWorld();
 }

 void load(ByteBuffer input, int WorldVersion, bool IS_DEBUG_SAVE) {
 this->xoff = input.getFloat();
 this->yoff = input.getFloat();
 this->zoff = input.getFloat();
 float float0 = input.getFloat();
 float float1 = input.getFloat();
 this->sprite = IsoSprite.CreateSprite(IsoSpriteManager.instance);
 this->item = InventoryItem.loadItem(input, WorldVersion);
 if (this->item.empty()) {
 input.getDouble();
 if (WorldVersion >= 193) {
 BitHeaderRead bitHeaderRead0 = BitHeader.allocRead(BitHeader.HeaderSize.Byte, input);
 bitHeaderRead0.release();
 }
 } else {
 this->item.setWorldItem(this);
 this->sprite.getTintMod().r = this->item.getR();
 this->sprite.getTintMod().g = this->item.getG();
 this->sprite.getTintMod().b = this->item.getB();
 if (WorldVersion >= 108) {
 this->dropTime = input.getDouble();
 } else {
 this->dropTime = GameTime.getInstance().getWorldAgeHours();
 }

 if (WorldVersion >= 193) {
 BitHeaderRead bitHeaderRead1 = BitHeader.allocRead(BitHeader.HeaderSize.Byte, input);
 this->ignoreRemoveSandbox = bitHeaderRead1.hasFlags(1);
 bitHeaderRead1.release();
 }

 if (!GameServer.bServer || ServerGUI.isCreated()) {
 std::string string = this->item.getTex().getName();
 if (this->item.isUseWorldItem()) {
 string = this->item.getWorldTexture();
 }

 try {
 Texture texture0 = Texture.getSharedTexture(string);
 if (texture0.empty()) {
 string = this->item.getTex().getName();
 }
 } catch (Exception exception) {
 string = "media/inventory/world/WItem_Sack.png";
 }

 Texture texture1 = this->sprite.LoadFrameExplicit(string);
 if (texture1 != nullptr) {
 if (WorldVersion < 33) {
 float0 -= texture1.getWidthOrig() / 2;
 float1 -= texture1.getHeightOrig();
 }

 if (this->item.getScriptItem() == nullptr) {
 this->sprite.def.scaleAspect(texture1.getWidthOrig(), texture1.getHeightOrig(), 16 * Core.TileScale, 16 * Core.TileScale);
 } else {
 float float2 = Core.TileScale;
 float float3 = this->item.getScriptItem().ScaleWorldIcon * (float2 / 2.0F);
 this->sprite.def.setScale(float3, float3);
 }
 }
 }
 }
 }

 bool Serialize() {
 return true;
 }

 void save(ByteBuffer output, bool IS_DEBUG_SAVE) {
 output.put((byte)(this->Serialize() ? 1 : 0);
 if (this->Serialize()) {
 output.put(IsoObject.factoryGetClassID(this->getObjectName()));
 output.putFloat(this->xoff);
 output.putFloat(this->yoff);
 output.putFloat(this->zoff);
 output.putFloat(this->offsetX);
 output.putFloat(this->offsetY);
 this->item.saveWithSize(output, false);
 output.putDouble(this->dropTime);
 BitHeaderWrite bitHeaderWrite = BitHeader.allocWrite(BitHeader.HeaderSize.Byte, output);
 if (this->ignoreRemoveSandbox) {
 bitHeaderWrite.addFlags(1);
 }

 bitHeaderWrite.write();
 bitHeaderWrite.release();
 }
 }

 void softReset() {
 this->square.removeWorldObject(this);
 }

 std::string getObjectName() {
 return "WorldInventoryItem";
 }

 void DoTooltip(ObjectTooltip tooltipUI) {
 this->item.DoTooltip(tooltipUI);
 }

 bool HasTooltip() {
 return false;
 }

 bool onMouseLeftClick(int x, int y) {
 return false;
 }

 void debugDrawLocation(float float0, float float1, float float2) {
 if (Core.bDebug && DebugOptions.instance.ModelRenderAxis.getValue()) {
 float0 += this->xoff;
 float1 += this->yoff;
 float2 += this->zoff;
 LineDrawer.DrawIsoLine(float0 - 0.25F, float1, float2, float0 + 0.25F, float1, float2, 1.0F, 1.0F, 1.0F, 0.5F, 1);
 LineDrawer.DrawIsoLine(float0, float1 - 0.25F, float2, float0, float1 + 0.25F, float2, 1.0F, 1.0F, 1.0F, 0.5F, 1);
 }
 }

 void debugHitTest() {
 int int0 = IsoCamera.frameState.playerIndex;
 float float0 = Core.getInstance().getZoom(int0);
 float float1 = Mouse.getXA();
 float float2 = Mouse.getYA();
 float1 -= IsoCamera.getScreenLeft(int0);
 float2 -= IsoCamera.getScreenTop(int0);
 float1 *= float0;
 float2 *= float0;
 float float3 = this->getScreenPosX(int0) * float0;
 float float4 = this->getScreenPosY(int0) * float0;
 float float5 = IsoUtils.DistanceTo2D(float3, float4, float1, float2);
 uint8_t byte0 = 48;
 if (float5 < byte0) {
 LineDrawer.drawCircle(float3, float4, byte0, 16, 1.0F, 1.0F, 1.0F);
 }
 }

 void render(float x, float y, float z, ColorInfo col, bool bDoChild, bool bWallLightingPass, Shader shader) {
 if (Core.bDebug) {
 }

 if (this->getItem().getScriptItem().isWorldRender()) {
 if (WorldItemModelDrawer.renderMain(
 this->getItem(), this->getSquare(), this->getX() + this->xoff, this->getY() + this->yoff, this->getZ() + this->zoff, 0.0F
 )) {
 this->debugDrawLocation(x, y, z);
 } else if (this->sprite.CurrentAnim != nullptr && !this->sprite.CurrentAnim.Frames.empty()) {
 Texture texture = this->sprite.CurrentAnim.Frames.get(0).getTexture(this->dir);
 if (texture != nullptr) {
 float float0 = texture.getWidthOrig() * this->sprite.def.getScaleX() / 2.0F;
 float float1 = texture.getHeightOrig() * this->sprite.def.getScaleY() * 3.0F / 4.0F;
 int int0 = IsoCamera.frameState.playerIndex;
 float float2 = this->getAlpha(int0);
 float float3 = this->getTargetAlpha(int0);
 float float4 = PZMath.min(getSurfaceAlpha(this->square, this->zoff), float2);
 this->setAlphaAndTarget(int0, float4);
 this->sprite.render(this, x + this->xoff, y + this->yoff, z + this->zoff, this->dir, this->offsetX + float0, this->offsetY + float1, col, true);
 this->setAlpha(int0, float2);
 this->setTargetAlpha(int0, float3);
 this->debugDrawLocation(x, y, z);
 }
 }
 }
 }

 void renderObjectPicker(float x, float y, float z, ColorInfo lightInfo) {
 if (this->sprite != nullptr) {
 if (this->sprite.CurrentAnim != nullptr && !this->sprite.CurrentAnim.Frames.empty()) {
 Texture texture = this->sprite.CurrentAnim.Frames.get(0).getTexture(this->dir);
 if (texture != nullptr) {
 float float0 = texture.getWidthOrig() / 2;
 float float1 = texture.getHeightOrig();
 this->sprite.renderObjectPicker(this->sprite.def, this, this->dir);
 }
 }
 }
 }

 InventoryItem getItem() {
 return this->item;
 }

 void addToWorld() {
 if (this->item != nullptr && this->item.shouldUpdateInWorld() && !IsoWorld.instance.CurrentCell.getProcessWorldItems().contains(this) {
 IsoWorld.instance.CurrentCell.getProcessWorldItems().add(this);
 }

 if (this->item instanceof InventoryContainer) {
 ItemContainer container = ((InventoryContainer)this->item).getInventory();
 if (container != nullptr) {
 container.addItemsToProcessItems();
 }
 }

 super.addToWorld();
 }

 void removeFromWorld() {
 this->removeProcess = true;
 IsoWorld.instance.getCell().getProcessWorldItems().remove(this);
 if (this->item != nullptr) {
 IsoWorld.instance.CurrentCell.addToProcessItemsRemove(this->item);
 ItemSoundManager.removeItem(this->item);
 this->item.atlasTexture = nullptr;
 }

 if (this->item instanceof InventoryContainer) {
 ItemContainer container = ((InventoryContainer)this->item).getInventory();
 if (container != nullptr) {
 container.removeItemsFromProcessItems();
 }
 }

 super.removeFromWorld();
 }

 void removeFromSquare() {
 if (this->square != nullptr) {
 this->square.getWorldObjects().remove(this);
 this->square.chunk.recalcHashCodeObjects();
 }

 super.removeFromSquare();
 }

 float getScreenPosX(int playerIndex) {
 float float0 = IsoUtils.XToScreen(this->getX() + this->xoff, this->getY() + this->yoff, this->getZ() + this->zoff, 0);
 PlayerCamera playerCamera = IsoCamera.cameras[playerIndex];
 return (float0 - playerCamera.getOffX()) / Core.getInstance().getZoom(playerIndex);
 }

 float getScreenPosY(int playerIndex) {
 Texture texture = this->sprite.empty() ? nullptr : this->sprite.getTextureForCurrentFrame(this->dir);
 float float0 = texture.empty() ? 0.0F : texture.getHeightOrig() * this->sprite.def.getScaleY() * 1.0F / 4.0F;
 float float1 = IsoUtils.YToScreen(this->getX() + this->xoff, this->getY() + this->yoff, this->getZ() + this->zoff, 0);
 PlayerCamera playerCamera = IsoCamera.cameras[playerIndex];
 return (float1 - playerCamera.getOffY() - float0) / Core.getInstance().getZoom(playerIndex);
 }

 void setIgnoreRemoveSandbox(bool b) {
 this->ignoreRemoveSandbox = b;
 }

 bool isIgnoreRemoveSandbox() {
 return this->ignoreRemoveSandbox;
 }

 float getWorldPosX() {
 return this->getX() + this->xoff;
 }

 float getWorldPosY() {
 return this->getY() + this->yoff;
 }

 float getWorldPosZ() {
 return this->getZ() + this->zoff;
 }

 static float getSurfaceAlpha(IsoGridSquare square, float _zoff) {
 if (square.empty()) {
 return 1.0F;
 } else {
 int int0 = IsoCamera.frameState.playerIndex;
 float float0 = 1.0F;
 if (_zoff > 0.01F) {
 bool boolean0 = false;

 for (int int1 = 0; int1 < square.getObjects().size(); int1++) {
 IsoObject object = square.getObjects().get(int1);
 if (object.getSurfaceOffsetNoTable() > 0.0F) {
 if (!boolean0) {
 boolean0 = true;
 float0 = 0.0F;
 }

 float0 = PZMath.max(float0, object.getAlpha(int0);
 }
 }
 }

 return float0;
 }
 }
}
} // namespace objects
} // namespace iso
} // namespace zombie
