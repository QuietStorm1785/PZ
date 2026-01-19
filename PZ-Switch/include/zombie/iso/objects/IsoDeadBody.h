#pragma once
#include "org/joml/Quaternionf.h"
#include "org/joml/Vector3f.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/FliesSound.h"
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/SandboxOptions.h"
#include "zombie/SharedDescriptors.h"
#include "zombie/SoundManager.h"
#include "zombie/audio/parameters/ParameterZombieState.h"
#include "zombie/characters/AttachedItems/AttachedItem.h"
#include "zombie/characters/AttachedItems/AttachedItems.h"
#include "zombie/characters/AttachedItems/AttachedLocationGroup.h"
#include "zombie/characters/AttachedItems/AttachedLocations.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoSurvivor.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/characters/SurvivorDesc.h"
#include "zombie/characters/Talker.h"
#include "zombie/characters/WornItems/BodyLocationGroup.h"
#include "zombie/characters/WornItems/BodyLocations.h"
#include "zombie/characters/WornItems/WornItems.h"
#include "zombie/core/Color.h"
#include "zombie/core/Colors.h"
#include "zombie/core/Core.h"
#include "zombie/core/PerformanceSettings.h"
#include "zombie/core/Rand.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/physics/Transform.h"
#include "zombie/core/skinnedmodel/DeadBodyAtlas.h"
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/core/skinnedmodel/visual/BaseVisual.h"
#include "zombie/core/skinnedmodel/visual/HumanVisual.h"
#include "zombie/core/skinnedmodel/visual/IHumanVisual.h"
#include "zombie/core/skinnedmodel/visual/ItemVisuals.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/debug/LineDrawer.h"
#include "zombie/debug/LogSeverity.h"
#include "zombie/input/Mouse.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/inventory/types/Food.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoObjectPicker.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/Vector2.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/weather/ClimateManager.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/IsoObjectID.h"
#include "zombie/network/ServerGUI.h"
#include "zombie/network/ServerLOS.h"
#include "zombie/network/ServerMap.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/ui/TextManager.h"
#include "zombie/ui/UIFont.h"
#include "zombie/util/Type.h"
#include "zombie/vehicles/BaseVehicle.h"
#include <algorithm>
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

class IsoDeadBody : public IsoMovingObject {
public:
 static const int MAX_ROT_STAGES = 3;
 static const int VISUAL_TYPE_HUMAN = 0;
private
 static IsoObjectID<IsoDeadBody> Bodies =
 new IsoObjectID<>(IsoDeadBody.class);
private
 static ArrayList<IsoDeadBody> tempBodies =
 std::make_unique<ArrayList<>>();
 bool bFemale = false;
 bool wasZombie = false;
 bool bFakeDead = false;
 bool bCrawling = false;
 Color SpeakColor;
 float SpeakTime = 0.0F;
 int m_persistentOutfitID;
 SurvivorDesc desc;
 BaseVisual baseVisual = nullptr;
 WornItems wornItems;
 AttachedItems attachedItems;
 float deathTime = -1.0F;
 float reanimateTime = -1.0F;
 IsoPlayer player;
 bool fallOnFront = false;
 bool wasSkeleton = false;
 InventoryItem primaryHandItem = nullptr;
 InventoryItem secondaryHandItem = nullptr;
 float m_angle;
 int m_zombieRotStageAtDeath = 1;
 short onlineID = -1;
 short objectID = -1;
private
 static ThreadLocal<IsoZombie> tempZombie =
 std::make_unique<ThreadLocal<IsoZombie>>(){
 IsoZombie initialValue(){return new IsoZombie(nullptr);
}
};
static ColorInfo inf = new ColorInfo();
public
DeadBodyAtlas.BodyTexture atlasTex;
static Texture DropShadow = nullptr;
static const float HIT_TEST_WIDTH = 0.3F;
static const float HIT_TEST_HEIGHT = 0.9F;
static const Quaternionf _rotation = new Quaternionf();
static const Transform _transform = new Transform();
static const Vector3f _UNIT_Z = new Vector3f(0.0F, 0.0F, 1.0F);
static const Vector3f _tempVec3f_1 = new Vector3f();
static const Vector3f _tempVec3f_2 = new Vector3f();
float burnTimer = 0.0F;
bool Speaking = false;
std::string sayLine = "";

static bool isDead(short id) {
 float float0 = (float)GameTime.getInstance().getWorldAgeHours();

 for (auto &deadBody : Bodies)
 if (deadBody.onlineID == id && float0 - deadBody.deathTime < 0.1F) {
 return true;
 }
}

return false;
}

std::string getObjectName() { return "DeadBody"; }

public
IsoDeadBody(IsoGameCharacter died) { this(died, false); }

public
IsoDeadBody(IsoGameCharacter died, bool wasCorpseAlready) {
 super(died.getCell(), false);
 IsoZombie zombie0 = Type.tryCastTo(died, IsoZombie.class);
 this->setFallOnFront(died.isFallOnFront());
 if (!GameClient.bClient && !GameServer.bServer && zombie0 != nullptr &&
 zombie0.bCrawling) {
 if (!zombie0.isReanimate()) {
 this->setFallOnFront(true);
 }

 this->bCrawling = true;
 }

 IsoGridSquare square0 = died.getCurrentSquare();
 if (square0 != nullptr) {
 if (died.getZ() < 0.0F) {
 DebugLog.General.error("invalid z-coordinate %d,%d,%d", died.x, died.y,
 died.z);
 died.setZ(0.0F);
 }

 this->square = square0;
 this->current = square0;
 if (died instanceof IsoPlayer) {
 ((IsoPlayer)died).removeSaveFile();
 }

 square0.getStaticMovingObjects().add(this);
 if (died instanceof IsoSurvivor) {
 IsoWorld.instance.TotalSurvivorNights =
 IsoWorld.instance.TotalSurvivorNights +
 ((IsoSurvivor)died).nightsSurvived;
 IsoWorld.instance.TotalSurvivorsDead++;
 if (IsoWorld.instance.SurvivorSurvivalRecord <
 ((IsoSurvivor)died).nightsSurvived) {
 IsoWorld.instance.SurvivorSurvivalRecord =
 ((IsoSurvivor)died).nightsSurvived;
 }
 }

 this->bFemale = died.isFemale();
 this->wasZombie = zombie0 != nullptr;
 if (this->wasZombie) {
 this->bFakeDead = zombie0.isFakeDead();
 this->wasSkeleton = zombie0.isSkeleton();
 }

 this->dir = died.dir;
 this->m_angle = died.getAnimAngleRadians();
 this->Collidable = false;
 this->x = died.getX();
 this->y = died.getY();
 this->z = died.getZ();
 this->nx = this->x;
 this->ny = this->y;
 this->offsetX = died.offsetX;
 this->offsetY = died.offsetY;
 this->solid = false;
 this->shootable = false;
 this->onlineID = died.getOnlineID();
 this->OutlineOnMouseover = true;
 this->setContainer(died.getInventory());
 this->setWornItems(died.getWornItems());
 this->setAttachedItems(died.getAttachedItems());
 if (died instanceof IHumanVisual) {
 this->baseVisual = new HumanVisual(this);
 this->baseVisual.copyFrom(((IHumanVisual)died).getHumanVisual());
 this->m_zombieRotStageAtDeath = this->getHumanVisual().zombieRotStage;
 }

 died.setInventory(std::make_unique<ItemContainer>());
 died.clearWornItems();
 died.clearAttachedItems();
 if (!this->container.bExplored) {
 this->container.setExplored(died instanceof IsoPlayer || died instanceof
 IsoZombie &&
 ((IsoZombie)died).isReanimatedPlayer());
 }

 bool boolean0 = died.isOnFire();
 if (died instanceof IsoZombie) {
 this->m_persistentOutfitID = died.getPersistentOutfitID();
 if (!wasCorpseAlready && !GameServer.bServer) {
 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 IsoPlayer playerx = IsoPlayer.players[int0];
 if (playerx != nullptr && playerx.ReanimatedCorpse == died) {
 playerx.ReanimatedCorpse = nullptr;
 playerx.ReanimatedCorpseID = -1;
 }
 }

 if (!GameClient.bClient && died.emitter != nullptr) {
 died.emitter.tick();
 }
 }
 } else {
 if (died instanceof IsoSurvivor) {
 this->getCell().getSurvivorList().remove(died);
 }

 this->desc = new SurvivorDesc(died.getDescriptor());
 if (died instanceof IsoPlayer) {
 if (GameServer.bServer) {
 this->player = (IsoPlayer)died;
 } else if (!GameClient.bClient && ((IsoPlayer)died).isLocalPlayer()) {
 this->player = (IsoPlayer)died;
 }
 }
 }

 LuaManager.copyTable(this->getModData(), died.getModData());
 died.removeFromWorld();
 died.removeFromSquare();
 this->sayLine = died.getSayLine();
 this->SpeakColor = died.getSpeakColour();
 this->SpeakTime = died.getSpeakTime();
 this->Speaking = died.isSpeaking();
 if (boolean0) {
 if (!GameClient.bClient &&
 SandboxOptions.instance.FireSpread.getValue()) {
 IsoFireManager.StartFire(this->getCell(), this->getSquare(), true, 100,
 500);
 }

 this->container.setExplored(true);
 }

 if (!wasCorpseAlready && !GameServer.bServer) {
 LuaEventManager.triggerEvent("OnContainerUpdate", this);
 }

 if (died instanceof IsoPlayer) {
 ((IsoPlayer)died).bDeathFinished = true;
 }

 this->deathTime = (float)GameTime.getInstance().getWorldAgeHours();
 this->setEatingZombies(died.getEatingZombies());
 if (!this->wasZombie) {
 std::vector arrayList = new ArrayList();

 for (int int1 = -2; int1 < 2; int1++) {
 for (int int2 = -2; int2 < 2; int2++) {
 IsoGridSquare square1 = square0.getCell().getGridSquare(
 square0.x + int1, square0.y + int2, square0.z);
 if (square1 != nullptr) {
 for (int int3 = 0; int3 < square1.getMovingObjects().size();
 int3++) {
 if (square1.getMovingObjects().get(int3) instanceof IsoZombie) {
 arrayList.add(square1.getMovingObjects().get(int3);
 }
 }
 }
 }
 }

 for (int int4 = 0; int4 < arrayList.size(); int4++) {
 ((IsoZombie)arrayList.get(int4)
 .pathToLocationF(this->getX() + Rand.Next(-0.3F, 0.3F),
 this->getY() + Rand.Next(-0.3F, 0.3F), this->getZ());
 ((IsoZombie)arrayList.get(int4).bodyToEat = this;
 }
 }

 if (!GameClient.bClient) {
 this->objectID = Bodies.allocateID();
 }

 Bodies.put(this->objectID, this);
 if (!GameServer.bServer) {
 FliesSound.instance.corpseAdded((int)this->getX(), (int)this->getY(),
 (int)this->getZ());
 }

 DebugLog.Death.noise("Corpse created %s", this->getDescription());
 }
}

public
IsoDeadBody(IsoCell cell) {
 super(cell, false);
 this->SpeakColor = Color.white;
 this->solid = false;
 this->shootable = false;
 BodyLocationGroup bodyLocationGroup = BodyLocations.getGroup("Human");
 this->wornItems = new WornItems(bodyLocationGroup);
 AttachedLocationGroup attachedLocationGroup =
 AttachedLocations.getGroup("Human");
 this->attachedItems = new AttachedItems(attachedLocationGroup);
 DebugLog.Death.noise("Corpse created on cell %s", this->getDescription());
}

BaseVisual getVisual() { return this->baseVisual; }

HumanVisual getHumanVisual() {
 return Type.tryCastTo(this->baseVisual, HumanVisual.class);
}

void getItemVisuals(ItemVisuals itemVisuals) {
 this->wornItems.getItemVisuals(itemVisuals);
}

bool isFemale() { return this->bFemale; }

bool isZombie() { return this->wasZombie; }

bool isCrawling() { return this->bCrawling; }

void setCrawling(bool crawling) { this->bCrawling = crawling; }

bool isFakeDead() { return this->bFakeDead; }

void setFakeDead(bool fakeDead) {
 if (!fakeDead ||
 SandboxOptions.instance.Lore.DisableFakeDead.getValue() != 3) {
 this->bFakeDead = fakeDead;
 }
}

bool isSkeleton() { return this->wasSkeleton; }

void setWornItems(WornItems other) { this->wornItems = new WornItems(other); }

WornItems getWornItems() { return this->wornItems; }

void setAttachedItems(AttachedItems other) {
 if (other != nullptr) {
 this->attachedItems = new AttachedItems(other);

 for (int int0 = 0; int0 < this->attachedItems.size(); int0++) {
 AttachedItem attachedItem = this->attachedItems.get(int0);
 InventoryItem item = attachedItem.getItem();
 if (!this->container.contains(item) && !GameClient.bClient &&
 !GameServer.bServer) {
 item.setContainer(this->container);
 this->container.getItems().add(item);
 }
 }
 }
}

AttachedItems getAttachedItems() { return this->attachedItems; }

InventoryItem getItem() {
 InventoryItem item = InventoryItemFactory.CreateItem("Base.CorpseMale");
 item.storeInByteData(this);
 return item;
}

IsoSprite loadSprite(ByteBuffer byteBuffer) {
 std::string string = GameWindow.ReadString(byteBuffer);
 float float0 = byteBuffer.getFloat();
 float float1 = byteBuffer.getFloat();
 float float2 = byteBuffer.getFloat();
 float float3 = byteBuffer.getFloat();
 return nullptr;
}

void load(ByteBuffer input, int WorldVersion, bool IS_DEBUG_SAVE) {
 super.load(input, WorldVersion, IS_DEBUG_SAVE);
 this->bFemale = input.get() == 1;
 this->wasZombie = input.get() == 1;
 if (WorldVersion >= 192) {
 this->objectID = input.getShort();
 } else {
 this->objectID = -1;
 }

 bool boolean0 = input.get() == 1;
 if (WorldVersion >= 171) {
 this->m_persistentOutfitID = input.getInt();
 }

 if (boolean0 && WorldVersion < 171) {
 short short0 = input.getShort();
 }

 if (input.get() == 1) {
 this->desc = new SurvivorDesc(true);
 this->desc.load(input, WorldVersion, nullptr);
 }

 if (WorldVersion >= 190) {
 uint8_t byte0 = input.get();
 switch (byte0) {
 case 0:
 this->baseVisual = new HumanVisual(this);
 this->baseVisual.load(input, WorldVersion);
 break;
 default:
 throw IOException("invalid visualType for corpse");
 }
 } else {
 this->baseVisual = new HumanVisual(this);
 this->baseVisual.load(input, WorldVersion);
 }

 if (input.get() == 1) {
 int int0 = input.getInt();

 try {
 this->setContainer(std::make_unique<ItemContainer>());
 this->container.ID = int0;
 std::vector arrayList = this->container.load(input, WorldVersion);
 uint8_t byte1 = input.get();

 for (int int1 = 0; int1 < byte1; int1++) {
 std::string string0 = GameWindow.ReadString(input);
 short short1 = input.getShort();
 if (short1 >= 0 && short1 < arrayList.size() &&
 this->wornItems.getBodyLocationGroup().getLocation(string0) !=
 nullptr) {
 this->wornItems.setItem(string0, (InventoryItem)arrayList.get(short1);
 }
 }

 uint8_t byte2 = input.get();

 for (int int2 = 0; int2 < byte2; int2++) {
 std::string string1 = GameWindow.ReadString(input);
 short short2 = input.getShort();
 if (short2 >= 0 && short2 < arrayList.size() &&
 this->attachedItems.getGroup().getLocation(string1) != nullptr) {
 this->attachedItems.setItem(string1,
 (InventoryItem)arrayList.get(short2);
 }
 }
 } catch (Exception exception) {
 if (this->container != nullptr) {
 DebugLog.log("Failed to stream in container ID: " + this->container.ID);
 }
 }
 }

 this->deathTime = input.getFloat();
 this->reanimateTime = input.getFloat();
 this->fallOnFront = input.get() == 1;
 if (boolean0 &&
 (GameClient.bClient || GameServer.bServer && ServerGUI.isCreated())) {
 this->checkClothing(nullptr);
 }

 this->wasSkeleton = input.get() == 1;
 if (WorldVersion >= 159) {
 this->m_angle = input.getFloat();
 } else {
 this->m_angle = this->dir.toAngle();
 }

 if (WorldVersion >= 166) {
 this->m_zombieRotStageAtDeath = input.get() & 255;
 }

 if (WorldVersion >= 168) {
 this->bCrawling = input.get() == 1;
 this->bFakeDead = input.get() == 1;
 }
}

void save(ByteBuffer output, bool IS_DEBUG_SAVE) {
 super.save(output, IS_DEBUG_SAVE);
 output.put((byte)(this->bFemale ? 1 : 0);
 output.put((byte)(this->wasZombie ? 1 : 0);
 output.putShort(this->objectID);
 if (!GameServer.bServer && !GameClient.bClient) {
 output.put((byte)0);
 } else {
 output.put((byte)1);
 }

 output.putInt(this->m_persistentOutfitID);
 if (this->desc != nullptr) {
 output.put((byte)1);
 this->desc.save(output);
 } else {
 output.put((byte)0);
 }

 if (this->baseVisual instanceof HumanVisual) {
 output.put((byte)0);
 this->baseVisual.save(output);
 if (this->container != nullptr) {
 output.put((byte)1);
 output.putInt(this->container.ID);
 std::vector arrayList = this->container.save(output);
 if (this->wornItems.size() > 127) {
 throw RuntimeException("too many worn items");
 }

 output.put((byte)this->wornItems.size());
 this->wornItems.forEach(wornItem->{
 GameWindow.WriteString(output, wornItem.getLocation());
 output.putShort((short)arrayList.indexOf(wornItem.getItem()));
 });
 if (this->attachedItems.empty()) {
 output.put((byte)0);
 } else {
 if (this->attachedItems.size() > 127) {
 throw RuntimeException("too many attached items");
 }

 output.put((byte)this->attachedItems.size());
 this->attachedItems.forEach(attachedItem->{
 GameWindow.WriteString(output, attachedItem.getLocation());
 output.putShort((short)arrayList.indexOf(attachedItem.getItem()));
 });
 }
 } else {
 output.put((byte)0);
 }

 output.putFloat(this->deathTime);
 output.putFloat(this->reanimateTime);
 output.put((byte)(this->fallOnFront ? 1 : 0);
 output.put((byte)(this->isSkeleton() ? 1 : 0);
 output.putFloat(this->m_angle);
 output.put((byte)this->m_zombieRotStageAtDeath);
 output.put((byte)(this->bCrawling ? 1 : 0);
 output.put((byte)(this->bFakeDead ? 1 : 0);
 } else {
 throw IllegalStateException("unhandled baseVisual class");
 }
}

void softReset() { this->square.RemoveTileObject(this); }

void saveChange(std::string_view change, KahluaTable tbl, ByteBuffer bb) {
 if ("becomeSkeleton" == change) {
 bb.putInt(this->getHumanVisual().getSkinTextureIndex());
 }
 else if ("zombieRotStage" == change) {
 bb.putInt(this->getHumanVisual().zombieRotStage);
 }
 else {
 super.saveChange(change, tbl, bb);
 }
}

void loadChange(std::string_view change, ByteBuffer bb) {
 if ("becomeSkeleton" == change) {
 int int0 = bb.getInt();
 this->getHumanVisual().setBeardModel("");
 this->getHumanVisual().setHairModel("");
 this->getHumanVisual().setSkinTextureIndex(int0);
 this->wasSkeleton = true;
 this->getWornItems().clear();
 this->getAttachedItems().clear();
 this->getContainer().clear();
 this->atlasTex = nullptr;
 }
 else if ("zombieRotStage" == change) {
 this->getHumanVisual().zombieRotStage = bb.getInt();
 this->atlasTex = nullptr;
 }
 else {
 super.loadChange(change, bb);
 }
}

void renderlast() {
 if (this->Speaking) {
 float float0 = this->sx;
 float float1 = this->sy;
 float0 -= IsoCamera.getOffX();
 float1 -= IsoCamera.getOffY();
 float0 += 8.0F;
 float1 += 32.0F;
 if (this->sayLine != nullptr) {
 TextManager.instance.DrawStringCentre(
 UIFont.Medium, float0, float1, this->sayLine, this->SpeakColor.r,
 this->SpeakColor.g, this->SpeakColor.b, this->SpeakColor.a);
 }
 }
}

void render(float x, float y, float z, ColorInfo col, bool bDoChild,
 bool bWallLightingPass, Shader shader) {
 this->offsetX = 0.0F;
 this->offsetY = 0.0F;
 bool boolean0 = this->isHighlighted();
 if (ModelManager.instance.bDebugEnableModels &&
 ModelManager.instance.isCreated()) {
 if (this->atlasTex.empty()) {
 this->atlasTex = DeadBodyAtlas.instance.getBodyTexture(this);
 DeadBodyAtlas.instance.render();
 }

 if (this->atlasTex != nullptr) {
 if (IsoSprite.globalOffsetX == -1.0F) {
 IsoSprite.globalOffsetX = -IsoCamera.frameState.OffX;
 IsoSprite.globalOffsetY = -IsoCamera.frameState.OffY;
 }

 float float0 = IsoUtils.XToScreen(x, y, z, 0);
 float float1 = IsoUtils.YToScreen(x, y, z, 0);
 this->sx = float0;
 this->sy = float1;
 float0 = this->sx + IsoSprite.globalOffsetX;
 float1 = this->sy + IsoSprite.globalOffsetY;
 if (Core.TileScale == 1) {
 }

 if (boolean0) {
 inf.r = this->getHighlightColor().r;
 inf.g = this->getHighlightColor().g;
 inf.b = this->getHighlightColor().b;
 inf.a = this->getHighlightColor().a;
 } else {
 inf.r = col.r;
 inf.g = col.g;
 inf.b = col.b;
 inf.a = col.a;
 }

 col = inf;
 if (!boolean0 && PerformanceSettings.LightingFrameSkip < 3 &&
 this->getCurrentSquare() != nullptr) {
 this->getCurrentSquare().interpolateLight(
 col, x - this->getCurrentSquare().getX(),
 y - this->getCurrentSquare().getY());
 }

 if (GameServer.bServer && ServerGUI.isCreated()) {
 inf.set(1.0F, 1.0F, 1.0F, 1.0F);
 }

 this->atlasTex.render((int)float0, (int)float1, col.r, col.g, col.b,
 col.a);
 if (Core.bDebug && DebugOptions.instance.DeadBodyAtlasRender.getValue()) {
 LineDrawer.DrawIsoLine(x - 0.5F, y, z, x + 0.5F, y, z, 1.0F, 1.0F, 1.0F,
 0.25F, 1);
 LineDrawer.DrawIsoLine(x, y - 0.5F, z, x, y + 0.5F, z, 1.0F, 1.0F, 1.0F,
 0.25F, 1);
 }

 this->sx = float0;
 this->sy = float1;
 if (IsoObjectPicker.Instance.wasDirty) {
 this->renderObjectPicker(this->getX(), this->getY(), this->getZ(), col);
 }
 }
 }

 if (Core.bDebug && DebugOptions.instance.DeadBodyAtlasRender.getValue()) {
 _rotation.setAngleAxis(this->m_angle + (Math.PI / 2), 0.0, 0.0, 1.0);
 _transform.setRotation(_rotation);
 _transform.origin.set(this->x, this->y, this->z);
 Vector3f vector3f0 = _tempVec3f_1;
 _transform.basis.getColumn(1, vector3f0);
 Vector3f vector3f1 = _tempVec3f_2;
 vector3f0.cross(_UNIT_Z, vector3f1);
 float float2 = 0.3F;
 float float3 = 0.9F;
 vector3f0.x *= float3;
 vector3f0.y *= float3;
 vector3f1.x *= float2;
 vector3f1.y *= float2;
 float float4 = x + vector3f0.x;
 float float5 = y + vector3f0.y;
 float float6 = x - vector3f0.x;
 float float7 = y - vector3f0.y;
 float float8 = float4 - vector3f1.x;
 float float9 = float4 + vector3f1.x;
 float float10 = float6 - vector3f1.x;
 float float11 = float6 + vector3f1.x;
 float float12 = float7 - vector3f1.y;
 float float13 = float7 + vector3f1.y;
 float float14 = float5 - vector3f1.y;
 float float15 = float5 + vector3f1.y;
 float float16 = 1.0F;
 float float17 = 1.0F;
 float float18 = 1.0F;
 if (this->isMouseOver(Mouse.getX(), Mouse.getY())) {
 float18 = 0.0F;
 float16 = 0.0F;
 }

 LineDrawer.addLine(float8, float14, 0.0F, float9, float15, 0.0F, float16,
 float17, float18, nullptr, true);
 LineDrawer.addLine(float8, float14, 0.0F, float10, float12, 0.0F, float16,
 float17, float18, nullptr, true);
 LineDrawer.addLine(float9, float15, 0.0F, float11, float13, 0.0F, float16,
 float17, float18, nullptr, true);
 LineDrawer.addLine(float10, float12, 0.0F, float11, float13, 0.0F, float16,
 float17, float18, nullptr, true);
 }

 if (this->isFakeDead() &&
 DebugOptions.instance.ZombieRenderFakeDead.getValue()) {
 float float19 = IsoUtils.XToScreen(x, y, z, 0) + IsoSprite.globalOffsetX;
 float float20 = IsoUtils.YToScreen(x, y, z, 0) + IsoSprite.globalOffsetY -
 16 * Core.TileScale;
 float float21 = this->getFakeDeadWakeupHours() -
 (float)GameTime.getInstance().getWorldAgeHours();
 float21 = Math.max(float21, 0.0F);
 TextManager.instance.DrawStringCentre(
 UIFont.Medium, float19, float20,
 String.format("FakeDead %.2f", float21), 1.0, 1.0, 1.0, 1.0);
 }

 if (Core.bDebug &&
 DebugOptions.instance.MultiplayerShowZombieOwner.getValue()) {
 Color color = Colors.Yellow;
 float float22 = IsoUtils.XToScreenExact(x + 0.4F, y + 0.4F, z, 0);
 float float23 = IsoUtils.YToScreenExact(x + 0.4F, y - 1.4F, z, 0);
 TextManager.instance.DrawStringCentre(UIFont.DebugConsole, float22, float23,
 this->objectID + " / " +
 this->onlineID + " / " +
 (this->isFemale() ? "F" : "M"),
 color.r, color.g, color.b, color.a);
 TextManager.instance.DrawStringCentre(
 UIFont.DebugConsole, float22, float23 + 10.0F,
 String.format("x=%09.3f ", x) + String.format("y=%09.3f ", y) +
 String.format("z=%d", (byte)z),
 color.r, color.g, color.b, color.a);
 }
}

void renderShadow() {
 _rotation.setAngleAxis(this->m_angle + (Math.PI / 2), 0.0, 0.0, 1.0);
 _transform.setRotation(_rotation);
 _transform.origin.set(this->x, this->y, this->z);
 Vector3f vector3f = _tempVec3f_1;
 _transform.basis.getColumn(1, vector3f);
 float float0 = 0.45F;
 float float1 = 1.4F;
 float float2 = 1.125F;
 int int0 = IsoCamera.frameState.playerIndex;
 ColorInfo colorInfo = this->square.lighting[int0].lightInfo();
 renderShadow(this->x, this->y, this->z, vector3f, float0, float1, float2,
 colorInfo, this->getAlpha(int0);
}

static void renderShadow(float x, float y, float z, Vector3f forward, float w,
 float fm, float bm, ColorInfo lightInfo, float alpha) {
 float float0 = alpha * ((lightInfo.r + lightInfo.g + lightInfo.b) / 3.0F);
 float0 *= 0.66F;
 forward.normalize();
 Vector3f vector3f = _tempVec3f_2;
 forward.cross(_UNIT_Z, vector3f);
 w = Math.max(0.65F, w);
 fm = Math.max(fm, 0.65F);
 bm = Math.max(bm, 0.65F);
 vector3f.x *= w;
 vector3f.y *= w;
 float float1 = x + forward.x * fm;
 float float2 = y + forward.y * fm;
 float float3 = x - forward.x * bm;
 float float4 = y - forward.y * bm;
 float float5 = float1 - vector3f.x;
 float float6 = float1 + vector3f.x;
 float float7 = float3 - vector3f.x;
 float float8 = float3 + vector3f.x;
 float float9 = float4 - vector3f.y;
 float float10 = float4 + vector3f.y;
 float float11 = float2 - vector3f.y;
 float float12 = float2 + vector3f.y;
 float float13 = IsoUtils.XToScreenExact(float5, float11, z, 0);
 float float14 = IsoUtils.YToScreenExact(float5, float11, z, 0);
 float float15 = IsoUtils.XToScreenExact(float6, float12, z, 0);
 float float16 = IsoUtils.YToScreenExact(float6, float12, z, 0);
 float float17 = IsoUtils.XToScreenExact(float8, float10, z, 0);
 float float18 = IsoUtils.YToScreenExact(float8, float10, z, 0);
 float float19 = IsoUtils.XToScreenExact(float7, float9, z, 0);
 float float20 = IsoUtils.YToScreenExact(float7, float9, z, 0);
 if (DropShadow.empty()) {
 DropShadow = Texture.getSharedTexture("media/textures/NewShadow.png");
 }

 SpriteRenderer.instance.renderPoly(DropShadow, float13, float14, float15,
 float16, float17, float18, float19,
 float20, 0.0F, 0.0F, 0.0F, float0);
 if (DebugOptions.instance.IsoSprite.DropShadowEdges.getValue()) {
 LineDrawer.addLine(float5, float11, z, float6, float12, z, 1, 1, 1,
 nullptr);
 LineDrawer.addLine(float6, float12, z, float8, float10, z, 1, 1, 1,
 nullptr);
 LineDrawer.addLine(float8, float10, z, float7, float9, z, 1, 1, 1, nullptr);
 LineDrawer.addLine(float7, float9, z, float5, float11, z, 1, 1, 1, nullptr);
 }
}

void renderObjectPicker(float x, float y, float z, ColorInfo lightInfo) {
 if (this->atlasTex != nullptr) {
 this->atlasTex.renderObjectPicker(this->sx, this->sy, lightInfo, this->square,
 this);
 }
}

bool isMouseOver(float screenX, float screenY) {
 _rotation.setAngleAxis(this->m_angle + (Math.PI / 2), 0.0, 0.0, 1.0);
 _transform.setRotation(_rotation);
 _transform.origin.set(this->x, this->y, this->z);
 _transform.inverse();
 Vector3f vector3f =
 _tempVec3f_1.set(IsoUtils.XToIso(screenX, screenY, this->z),
 IsoUtils.YToIso(screenX, screenY, this->z), this->z);
 _transform.transform(vector3f);
 return vector3f.x >= -0.3F && vector3f.y >= -0.9F && vector3f.x < 0.3F &&
 vector3f.y < 0.9F;
}

void Burn() {
 if (!GameClient.bClient) {
 if (this->getSquare() != nullptr &&
 this->getSquare().getProperties().Is(IsoFlagType.burning) {
 this->burnTimer = this->burnTimer +
 GameTime.instance.getMultipliedSecondsSinceLastUpdate();
 if (this->burnTimer >= 10.0F) {
 bool boolean0 = true;

 for (int int0 = 0; int0 < this->getSquare().getObjects().size();
 int0++) {
 IsoObject object0 = this->getSquare().getObjects().get(int0);
 if (object0.getName() != nullptr &&
 "burnedCorpse" == object0.getName())) {
 boolean0 = false;
 break;
 }
 }

 if (boolean0) {
 IsoObject object1 = new IsoObject(
 this->getSquare(), "floors_burnt_01_" + Rand.Next(1, 3),
 "burnedCorpse");
 this->getSquare().getObjects().add(object1);
 object1.transmitCompleteItemToClients();
 }

 if (GameServer.bServer) {
 GameServer.sendRemoveCorpseFromMap(this);
 }

 this->getSquare().removeCorpse(this, true);
 }
 }
 }
}

/**
 *
 * @param container the container to set
 */
void setContainer(ItemContainer container) {
 super.setContainer(container);
 container.type = this->bFemale ? "inventoryfemale" : "inventorymale";
 container.Capacity = 8;
 container.SourceGrid = this->square;
}

void checkClothing(InventoryItem removedItem) {
 for (int int0 = 0; int0 < this->wornItems.size(); int0++) {
 InventoryItem item0 = this->wornItems.getItemByIndex(int0);
 if (this->container.empty() ||
 this->container.getItems().indexOf(item0) == -1) {
 this->wornItems.remove(item0);
 this->atlasTex = nullptr;
 int0--;
 }
 }

 if (removedItem == this->getPrimaryHandItem()) {
 this->setPrimaryHandItem(nullptr);
 this->atlasTex = nullptr;
 }

 if (removedItem == this->getSecondaryHandItem()) {
 this->setSecondaryHandItem(nullptr);
 this->atlasTex = nullptr;
 }

 for (int int1 = 0; int1 < this->attachedItems.size(); int1++) {
 InventoryItem item1 = this->attachedItems.getItemByIndex(int1);
 if (this->container.empty() ||
 this->container.getItems().indexOf(item1) == -1) {
 this->attachedItems.remove(item1);
 this->atlasTex = nullptr;
 int1--;
 }
 }
}

bool IsSpeaking() { return this->Speaking; }

void Say(std::string_view line) {
 this->SpeakTime = line.length() * 4;
 if (this->SpeakTime < 60.0F) {
 this->SpeakTime = 60.0F;
 }

 this->sayLine = line;
 this->Speaking = true;
}

std::string getSayLine() { return this->sayLine; }

std::string getTalkerType() { return "Talker"; }

void addToWorld() {
 super.addToWorld();
 if (!GameServer.bServer) {
 FliesSound.instance.corpseAdded((int)this->getX(), (int)this->getY(),
 (int)this->getZ());
 }

 if (!GameClient.bClient && this->objectID == -1) {
 this->objectID = Bodies.allocateID();
 }

 Bodies.put(this->objectID, this);
 if (!GameClient.bClient) {
 if (this->reanimateTime > 0.0F) {
 this->getCell().addToStaticUpdaterObjectList(this);
 if (Core.bDebug) {
 DebugLog.log(
 "reanimate: addToWorld reanimateTime=" + this->reanimateTime + this);
 }
 }

 float float0 = (float)GameTime.getInstance().getWorldAgeHours();
 if (this->deathTime < 0.0F) {
 this->deathTime = float0;
 }

 if (this->deathTime > float0) {
 this->deathTime = float0;
 }
 }
}

void removeFromWorld() {
 if (!GameServer.bServer) {
 FliesSound.instance.corpseRemoved((int)this->getX(), (int)this->getY(),
 (int)this->getZ());
 }

 Bodies.remove(this->objectID);
 super.removeFromWorld();
}

static void updateBodies() {
 if (!GameClient.bClient) {
 if (Core.bDebug) {
 }

 bool boolean0 = false;
 float float0 =
 (float)SandboxOptions.instance.HoursForCorpseRemoval.getValue();
 if (!(float0 <= 0.0F) {
 float float1 = float0 / 3.0F;
 float float2 = (float)GameTime.getInstance().getWorldAgeHours();
 tempBodies.clear();
 Bodies.getObjects(tempBodies);

 for (auto &deadBody : tempBodies)
 if (deadBody.getHumanVisual() != nullptr) {
 if (deadBody.deathTime > float2) {
 deadBody.deathTime = float2;
 deadBody.getHumanVisual().zombieRotStage =
 deadBody.m_zombieRotStageAtDeath;
 }

 if (!deadBody.updateFakeDead() &&
 (ServerOptions.instance.RemovePlayerCorpsesOnCorpseRemoval
 .getValue() ||
 deadBody.wasZombie) {
 int int0 = deadBody.getHumanVisual().zombieRotStage;
 deadBody.updateRotting(float2, float1, boolean0);
 if (deadBody.isFakeDead()) {
 }

 int int1 = deadBody.getHumanVisual().zombieRotStage;
 float float3 = float2 - deadBody.deathTime;
 if (!(float3 < float0 + (deadBody.isSkeleton() ? float1 : 0.0F)) {
 if (boolean0) {
 int int2 = (int)(float3 / float1);
 DebugLog.General.debugln(
 "%s REMOVE %d -> %d age=%.2f stages=%d", deadBody, int0,
 int1, float3, int2);
 }

 if (GameServer.bServer) {
 GameServer.sendRemoveCorpseFromMap(deadBody);
 }

 deadBody.removeFromWorld();
 deadBody.removeFromSquare();
 }
 }
 }
 }
 }
}
}

void updateRotting(float float1, float float2, bool boolean0) {
 if (!this->isSkeleton()) {
 float float0 = float1 - this->deathTime;
 int int0 = (int)(float0 / float2);
 int int1 = this->m_zombieRotStageAtDeath + int0;
 if (int0 < 3) {
 int1 = PZMath.clamp(int1, 1, 3);
 }

 if (int1 <= 3 && int1 != this->getHumanVisual().zombieRotStage) {
 int int2 = int1 - this->getHumanVisual().zombieRotStage;
 if (boolean0) {
 DebugLog.General.debugln(
 "%s zombieRotStage %d -> %d age=%.2f stages=%d", this,
 this->getHumanVisual().zombieRotStage, int1, float0, int0);
 }

 this->getHumanVisual().zombieRotStage = int1;
 this->atlasTex = nullptr;
 if (GameServer.bServer) {
 this->sendObjectChange("zombieRotStage");
 }

 if (Rand.Next(100) == 0 && this->wasZombie &&
 SandboxOptions.instance.Lore.DisableFakeDead.getValue() == 2) {
 this->setFakeDead(true);
 if (Rand.Next(5) == 0) {
 this->setCrawling(true);
 }
 }

 std::string string = ClimateManager.getInstance().getSeasonName();
 if (int2 >= 1 && string != "Winter") {
 if (SandboxOptions.instance.MaggotSpawn.getValue() != 3) {
 uint8_t byte0 = 5;
 if (string == "Summer") {
 byte0 = 3;
 }

 for (int int3 = 0; int3 < int2; int3++) {
 if (this->wasZombie) {
 if (Rand.Next((int)byte0) == 0) {
 InventoryItem item0 =
 InventoryItemFactory.CreateItem("Maggots");
 if (item0 != nullptr && this->getContainer() != nullptr) {
 this->getContainer().addItem(item0);
 if (item0 instanceof Food) {
 ((Food)item0).setPoisonPower(5);
 }
 }
 }

 if (Rand.Next(byte0 * 2) == 0 &&
 SandboxOptions.instance.MaggotSpawn.getValue() != 2) {
 InventoryItem item1 =
 InventoryItemFactory.CreateItem("Maggots");
 if (item1 != nullptr && this->getSquare() != nullptr) {
 this->getSquare().AddWorldInventoryItem(
 item1, (float)(Rand.Next(10) / 10),
 (float)(Rand.Next(10) / 10), 0.0F);
 if (item1 instanceof Food) {
 ((Food)item1).setPoisonPower(5);
 }
 }
 }
 } else {
 if (Rand.Next((int)byte0) == 0) {
 InventoryItem item2 =
 InventoryItemFactory.CreateItem("Maggots");
 if (item2 != nullptr && this->getContainer() != nullptr) {
 this->getContainer().addItem(item2);
 }
 }

 if (Rand.Next(byte0 * 2) == 0 &&
 SandboxOptions.instance.MaggotSpawn.getValue() != 2) {
 InventoryItem item3 =
 InventoryItemFactory.CreateItem("Maggots");
 if (item3 != nullptr && this->getSquare() != nullptr) {
 this->getSquare().AddWorldInventoryItem(
 item3, (float)(Rand.Next(10) / 10),
 (float)(Rand.Next(10) / 10), 0.0F);
 }
 }
 }
 }
 }
 }
 } else {
 if (int0 == 3 && Rand.NextBool(7) {
 if (boolean0) {
 DebugLog.General.debugln(
 "%s zombieRotStage %d -> x age=%.2f stages=%d", this,
 this->getHumanVisual().zombieRotStage, float0, int0);
 }

 this->getHumanVisual().setBeardModel("");
 this->getHumanVisual().setHairModel("");
 this->getHumanVisual().setSkinTextureIndex(Rand.Next(1, 3);
 this->wasSkeleton = true;
 this->getWornItems().clear();
 this->getAttachedItems().clear();
 this->getContainer().clear();
 this->atlasTex = nullptr;
 if (GameServer.bServer) {
 this->sendObjectChange("becomeSkeleton");
 }
 }
 }
 }
}

bool updateFakeDead() {
 if (!this->isFakeDead()) {
 return false;
 } else if (this->isSkeleton()) {
 return false;
 } else if (this->getFakeDeadWakeupHours() >
 GameTime.getInstance().getWorldAgeHours()) {
 return false;
 } else if (!this->isPlayerNearby()) {
 return false;
 } else if (SandboxOptions.instance.Lore.DisableFakeDead.getValue() == 3) {
 return false;
 } else {
 this->reanimateNow();
 return true;
 }
}

float getFakeDeadWakeupHours() { return this->deathTime + 0.5F; }

bool isPlayerNearby() {
 if (GameServer.bServer) {
 for (int int0 = 0; int0 < GameServer.Players.size(); int0++) {
 IsoPlayer player0 = GameServer.Players.get(int0);
 bool boolean0 = this->square != nullptr &&
 ServerLOS.instance.isCouldSee(player0, this->square);
 if (this->isPlayerNearby(player0, boolean0) {
 return true;
 }
 }
 } else {
 IsoGridSquare square = this->getSquare();

 for (int int1 = 0; int1 < IsoPlayer.numPlayers; int1++) {
 IsoPlayer player1 = IsoPlayer.players[int1];
 bool boolean1 = square != nullptr && square.isCanSee(int1);
 if (this->isPlayerNearby(player1, boolean1) {
 return true;
 }
 }
 }

 return false;
}

bool isPlayerNearby(IsoPlayer playerx, bool boolean0) {
 if (!boolean0) {
 return false;
 } else if (playerx.empty() || playerx.isDead()) {
 return false;
 } else if (playerx.isGhostMode() || playerx.isInvisible()) {
 return false;
 } else if (playerx.getVehicle() != nullptr) {
 return false;
 } else {
 float float0 = playerx.DistToSquared(this);
 return !(float0 < 4.0F) && !(float0 > 16.0F);
 }
}

float getReanimateTime() { return this->reanimateTime; }

void setReanimateTime(float hours) {
 this->reanimateTime = hours;
 if (!GameClient.bClient) {
 std::vector arrayList =
 IsoWorld.instance.CurrentCell.getStaticUpdaterObjectList();
 if (this->reanimateTime > 0.0F && !arrayList.contains(this) {
 arrayList.add(this);
 } else if (this->reanimateTime <= 0.0F && arrayList.contains(this) {
 arrayList.remove(this);
 }
 }
}

float getReanimateDelay() {
 float float0 = 0.0F;
 float float1 = 0.0F;

 float1 = switch (SandboxOptions.instance.Lore.Reanimate.getValue()) {
 case 2 -> 0.008333334F;
 case 3 -> 0.016666668F;
 case 4 -> 12.0F;
 case 5 -> {
 float0 = 48.0F;
 yield 72.0F;
 }
 case 6 -> {
 float0 = 168.0F;
 yield 336.0F;
 }
 };
 if (Core.bTutorial) {
 float1 = 0.25F;
 }

 return float0 = = float1 ? float0 :
 Rand.Next(float0, float1);
 }

 void reanimateLater() {
 this->setReanimateTime(
 (float)GameTime.getInstance().getWorldAgeHours() +
 this->getReanimateDelay());
 }

 void reanimateNow() {
 this->setReanimateTime(
 (float)GameTime.getInstance().getWorldAgeHours());
 }

 void update() {
 if (this->current.empty()) {
 this->current = IsoWorld.instance.CurrentCell.getGridSquare(
 (double)this->x, (double)this->y, (double)this->z);
 }

 if (!GameClient.bClient) {
 if (this->reanimateTime > 0.0F) {
 float float0 =
 (float)GameTime.getInstance().getWorldAgeHours();
 if (this->reanimateTime <= float0) {
 this->reanimate();
 }
 }
 }
 }

 void reanimate() {
 short short0 = -1;
 if (GameServer.bServer) {
 short0 = ServerMap.instance.getUniqueZombieId();
 if (short0 == -1) {
 return;
 }
 }

 SurvivorDesc survivorDesc = new SurvivorDesc();
 survivorDesc.setFemale(this->isFemale());
 IsoZombie zombie0 = new IsoZombie(IsoWorld.instance.CurrentCell,
 survivorDesc, -1);
 zombie0.setPersistentOutfitID(this->m_persistentOutfitID);
 if (this->container.empty()) {
 this->container = std::make_unique<ItemContainer>();
 }

 zombie0.setInventory(this->container);
 this->container = nullptr;
 zombie0.getHumanVisual().copyFrom(this->getHumanVisual());
 zombie0.getWornItems().copyFrom(this->wornItems);
 this->wornItems.clear();
 zombie0.getAttachedItems().copyFrom(this->attachedItems);
 this->attachedItems.clear();
 zombie0.setX(this->getX());
 zombie0.setY(this->getY());
 zombie0.setZ(this->getZ());
 zombie0.setCurrent(this->getCurrentSquare());
 zombie0.setMovingSquareNow();
 zombie0.setDir(this->dir);
 LuaManager.copyTable(zombie0.getModData(), this->getModData());
 zombie0.getAnimationPlayer().setTargetAngle(this->m_angle);
 zombie0.getAnimationPlayer().setAngleToTarget();
 zombie0.setForwardDirection(
 Vector2.fromLengthDirection(1.0F, this->m_angle);
 zombie0.setAlphaAndTarget(1.0F);
 Arrays.fill(zombie0.IsVisibleToPlayer, true);
 zombie0.setOnFloor(true);
 zombie0.setCrawler(this->bCrawling);
 zombie0.setCanWalk(!this->bCrawling);
 zombie0.walkVariant = "ZombieWalk";
 zombie0.DoZombieStats();
 zombie0.setFallOnFront(this->isFallOnFront());
 if (SandboxOptions.instance.Lore.Toughness.getValue() == 1) {
 zombie0.setHealth(3.5F + Rand.Next(0.0F, 0.3F);
 }

 if (SandboxOptions.instance.Lore.Toughness.getValue() == 2) {
 zombie0.setHealth(1.8F + Rand.Next(0.0F, 0.3F);
 }

 if (SandboxOptions.instance.Lore.Toughness.getValue() == 3) {
 zombie0.setHealth(0.5F + Rand.Next(0.0F, 0.3F);
 }

 if (GameServer.bServer) {
 zombie0.OnlineID = short0;
 ServerMap.instance.ZombieMap.put(zombie0.OnlineID, zombie0);
 }

 if (this->isFakeDead()) {
 zombie0.setWasFakeDead(true);
 } else {
 zombie0.setReanimatedPlayer(true);
 zombie0.getDescriptor().setID(0);
 SharedDescriptors.createPlayerZombieDescriptor(zombie0);
 }

 zombie0.setReanimate(this->bCrawling);
 if (!IsoWorld.instance.CurrentCell.getZombieList().contains(
 zombie0) {
 IsoWorld.instance.CurrentCell.getZombieList().add(zombie0);
 }

 if (!IsoWorld.instance.CurrentCell.getObjectList().contains(
 zombie0) &&
 !IsoWorld.instance.CurrentCell.getAddList().contains(
 zombie0) {
 IsoWorld.instance.CurrentCell.getAddList().add(zombie0);
 }

 if (GameServer.bServer) {
 if (this->player != nullptr) {
 this->player.ReanimatedCorpse = zombie0;
 this->player.ReanimatedCorpseID = zombie0.OnlineID;
 }

 zombie0.networkAI.reanimatedBodyID = this->objectID;
 }

 if (GameServer.bServer) {
 GameServer.sendRemoveCorpseFromMap(this);
 }

 this->removeFromWorld();
 this->removeFromSquare();
 LuaEventManager.triggerEvent("OnContainerUpdate");
 zombie0.setReanimateTimer(0.0F);
 zombie0.onWornItemsChanged();
 if (this->player != nullptr) {
 if (GameServer.bServer) {
 GameServer.sendReanimatedZombieID(this->player, zombie0);
 } else if (!GameClient.bClient && this->player.isLocalPlayer()) {
 this->player.ReanimatedCorpse = zombie0;
 }

 this->player.setLeaveBodyTimedown(3601.0F);
 }

 zombie0.actionContext.update();
 float float0 = GameTime.getInstance().FPSMultiplier;
 GameTime.getInstance().FPSMultiplier = 100.0F;

 try {
 zombie0.advancedAnimator.update();
 } finally {
 GameTime.getInstance().FPSMultiplier = float0;
 }

 if (this->isFakeDead() &&
 SoundManager.instance.isListenerInRange(this->x, this->y,
 20.0F) &&
 !GameServer.bServer) {
 zombie0.parameterZombieState.setState(
 ParameterZombieState.State.Reanimate);
 }

 if (Core.bDebug) {
 DebugLog.Multiplayer.debugln(
 "Reanimate: corpse=%d/%d zombie=%d delay=%f",
 this->getObjectID(), this->getOnlineID(),
 zombie0.getOnlineID(),
 GameTime.getInstance().getWorldAgeHours() -
 this->reanimateTime);
 }
 }

 static void Reset() { Bodies.clear(); }

 void Collision(Vector2 collision, IsoObject object) {
 if (object instanceof BaseVehicle vehicle) {
 float float0 = 15.0F;
 Vector3f vector3f0 = BaseVehicle.TL_vector3f_pool.get().alloc();
 Vector3f vector3f1 = BaseVehicle.TL_vector3f_pool.get().alloc();
 vehicle.getLinearVelocity(vector3f0);
 vector3f0.y = 0.0F;
 vector3f1.set(vehicle.x - this->x, 0.0F, vehicle.z - this->z);
 vector3f1.normalize();
 vector3f0.mul(vector3f1);
 BaseVehicle.TL_vector3f_pool.get().release(vector3f1);
 float float1 = vector3f0.length();
 BaseVehicle.TL_vector3f_pool.get().release(vector3f0);
 float1 = Math.min(float1, float0);
 if (float1 < 0.05F) {
 return;
 }

 if (Math.abs(vehicle.getCurrentSpeedKmHour()) > 20.0F) {
 vehicle.doChrHitImpulse(this);
 }
 }
 }

 bool isFallOnFront() { return this->fallOnFront; }

 void setFallOnFront(bool _fallOnFront) {
 this->fallOnFront = _fallOnFront;
 }

 InventoryItem getPrimaryHandItem() { return this->primaryHandItem; }

 void setPrimaryHandItem(InventoryItem item) {
 this->primaryHandItem = item;
 this->updateContainerWithHandItems();
 }

 void updateContainerWithHandItems() {
 if (this->getContainer() != nullptr) {
 if (this->getPrimaryHandItem() != nullptr) {
 this->getContainer().AddItem(this->getPrimaryHandItem());
 }

 if (this->getSecondaryHandItem() != nullptr) {
 this->getContainer().AddItem(this->getSecondaryHandItem());
 }
 }
 }

 InventoryItem getSecondaryHandItem() {
 return this->secondaryHandItem;
 }

 void setSecondaryHandItem(InventoryItem item) {
 this->secondaryHandItem = item;
 this->updateContainerWithHandItems();
 }

 float getAngle() { return this->m_angle; }

 std::string getOutfitName() {
 return this->getHumanVisual().getOutfit() != nullptr
 ? this->getHumanVisual().getOutfit().m_Name
 : nullptr;
 }

 std::string getDescription() {
 return String.format(
 "object-id=%d online-id=%d bFakeDead=%b bCrawling=%b "
 "isFallOnFront=%b (x=%f,y=%f,z=%f;a=%f) outfit=%d",
 this->objectID, this->onlineID, this->bFakeDead, this->bCrawling,
 this->fallOnFront, this->x, this->y, this->z, this->m_angle,
 this->m_persistentOutfitID);
 }

 std::string readInventory(ByteBuffer b) {
 std::string string0 = GameWindow.ReadString(b);
 if (this->getContainer() != nullptr &&
 this->getWornItems() != nullptr &&
 this->getAttachedItems() != nullptr) {
 this->getContainer().clear();
 this->getWornItems().clear();
 this->getAttachedItems().clear();
 bool boolean0 = b.get() == 1;
 if (boolean0) {
 try {
 std::vector arrayList =
 this->getContainer().load(b, IsoWorld.getWorldVersion());
 this->getContainer().Capacity = 8;
 uint8_t byte0 = b.get();

 for (int int0 = 0; int0 < byte0; int0++) {
 std::string string1 = GameWindow.ReadStringUTF(b);
 short short0 = b.getShort();
 if (short0 >= 0 && short0 < arrayList.size() &&
 this->getWornItems()
 .getBodyLocationGroup()
 .getLocation(string1) != nullptr) {
 this->getWornItems().setItem(
 string1, (InventoryItem)arrayList.get(short0);
 }
 }

 uint8_t byte1 = b.get();

 for (int int1 = 0; int1 < byte1; int1++) {
 std::string string2 = GameWindow.ReadStringUTF(b);
 short short1 = b.getShort();
 if (short1 >= 0 && short1 < arrayList.size() &&
 this->getAttachedItems().getGroup().getLocation(
 string2) != nullptr) {
 this->getAttachedItems().setItem(
 string2, (InventoryItem)arrayList.get(short1);
 }
 }
 } catch (IOException iOException) {
 DebugLog.Multiplayer.printException(
 iOException,
 "ReadDeadBodyInventory error for dead body " +
 this->getOnlineID(),
 LogSeverity.Error);
 }
 }

 return string0;
 } else {
 return string0;
 }
 }

 short getObjectID() { return this->objectID; }

 void setObjectID(short _objectID) { this->objectID = _objectID; }

 short getOnlineID() { return this->onlineID; }

 void setOnlineID(short _onlineID) { this->onlineID = _onlineID; }

 bool isPlayer() { return this->player != nullptr; }

 static IsoDeadBody getDeadBody(short id) { return Bodies.get(id); }

 static void addDeadBodyID(short id, IsoDeadBody deadBody) {
 Bodies.put(id, deadBody);
 }

 static void removeDeadBody(short id) {
 IsoDeadBody deadBody = Bodies.get(id);
 if (deadBody != nullptr) {
 Bodies.remove(id);
 if (deadBody.getSquare() != nullptr) {
 deadBody.getSquare().removeCorpse(deadBody, true);
 }
 }
 }
}
} // namespace objects
} // namespace iso
} // namespace zombie
