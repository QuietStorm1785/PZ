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
#include "zombie/SandboxOptions.h"
#include "zombie/SystemDisabler.h"
#include "zombie/WorldSoundManager.h"
#include "zombie/ai/states/ThumpState.h"
#include "zombie/characters/BaseCharacterSoundEmitter.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoSurvivor.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/characters/skills/PerkFactory.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/Translator.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/opengl/Shader.h"
#include "zombie/core/properties/PropertyContainer.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/core/textures/TextureDraw.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/inventory/types/Key.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
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
#include "zombie/iso/weather/fx/WeatherFxMask.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/PacketTypes.h"
#include "zombie/network/ServerMap.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/Type.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/PolygonalMap2.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {
namespace objects {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class IsoDoor : public IsoObject {
public:
 int Health = 500;
 bool lockedByKey = false;
 bool haveKey = false;
 bool Locked = false;
 int MaxHealth = 500;
 int PushedMaxStrength = 0;
 int PushedStrength = 0;
 public IsoDoor.DoorType type = IsoDoor.DoorType.WeakWooden;
 IsoSprite closedSprite;
 bool north = false;
 int gid = -1;
 bool open = false;
 IsoSprite openSprite;
 bool destroyed = false;
 bool bHasCurtain;
 bool bCurtainInside;
 bool bCurtainOpen;
 KahluaTable table;
 static const Vector2 tempo = new Vector2();
 IsoSprite curtainN;
 IsoSprite curtainS;
 IsoSprite curtainW;
 IsoSprite curtainE;
 IsoSprite curtainNopen;
 IsoSprite curtainSopen;
 IsoSprite curtainWopen;
 IsoSprite curtainEopen;
 private static int[] DoubleDoorNorthSpriteOffset = new int[]{5, 3, 4, 4};
 private static int[] DoubleDoorWestSpriteOffset = new int[]{4, 4, 5, 3};
 private static int[] DoubleDoorNorthClosedXOffset = new int[]{0, 1, 2, 3};
 private static int[] DoubleDoorNorthOpenXOffset = new int[]{0, 0, 3, 3};
 private static int[] DoubleDoorNorthClosedYOffset = new int[]{0, 0, 0, 0};
 private static int[] DoubleDoorNorthOpenYOffset = new int[]{0, 1, 1, 0};
 private static int[] DoubleDoorWestClosedXOffset = new int[]{0, 0, 0, 0};
 private static int[] DoubleDoorWestOpenXOffset = new int[]{0, 1, 1, 0};
 private static int[] DoubleDoorWestClosedYOffset = new int[]{0, -1, -2, -3};
 private static int[] DoubleDoorWestOpenYOffset = new int[]{0, 0, -3, -3};

 public IsoDoor(IsoCell cell) {
 super(cell);
 }

 std::string getObjectName() {
 return "Door";
 }

 void render(float x, float y, float z, ColorInfo info, bool bDoAttached, bool bWallLightingPass, Shader shader) {
 this->checkKeyHighlight(x, y);
 if (!this->bHasCurtain) {
 super.render(x, y, z, info, bDoAttached, bWallLightingPass, shader);
 } else {
 this->initCurtainSprites();
 IsoDirections directions = this->getSpriteEdge(false);
 this->prerender(x, y, z, info, bDoAttached, bWallLightingPass, directions);
 super.render(x, y, z, info, bDoAttached, bWallLightingPass, shader);
 this->postrender(x, y, z, info, bDoAttached, bWallLightingPass, directions);
 }
 }

 public void renderWallTile(
 float x, float y, float z, ColorInfo col, boolean bDoAttached, boolean bWallLightingPass, Shader shader, Consumer<TextureDraw> texdModifier
 ) {
 this->checkKeyHighlight(x, y);
 if (!this->bHasCurtain) {
 super.renderWallTile(x, y, z, col, bDoAttached, bWallLightingPass, shader, texdModifier);
 } else {
 this->initCurtainSprites();
 IsoDirections directions = this->getSpriteEdge(false);
 this->prerender(x, y, z, col, bDoAttached, bWallLightingPass, directions);
 super.renderWallTile(x, y, z, col, bDoAttached, bWallLightingPass, shader, texdModifier);
 this->postrender(x, y, z, col, bDoAttached, bWallLightingPass, directions);
 }
 }

 void checkKeyHighlight(float float1, float float0) {
 int int0 = IsoCamera.frameState.playerIndex;
 IsoGameCharacter character = IsoCamera.frameState.CamCharacter;
 Key key = Key.highlightDoor[int0];
 if (key != nullptr
 && float1 >= character.getX() - 20.0F
 && float0 >= character.getY() - 20.0F
 && float1 < character.getX() + 20.0F
 && float0 < character.getY() + 20.0F) {
 bool boolean0 = this->square.isSeen(int0);
 if (!boolean0) {
 IsoGridSquare square = this->getOppositeSquare();
 boolean0 = square != nullptr && square.isSeen(int0);
 }

 if (boolean0) {
 this->checkKeyId();
 if (this->getKeyId() == key.getKeyId()) {
 this->setHighlighted(true);
 }
 }
 }
 }

 void prerender(float float0, float float1, float float2, ColorInfo colorInfo, bool boolean0, bool boolean1, IsoDirections directions) {
 if (Core.TileScale == 1) {
 switch (directions) {
 case N:
 this->prerender1xN(float0, float1, float2, colorInfo, boolean0, boolean1, nullptr);
 break;
 case S:
 this->prerender1xS(float0, float1, float2, colorInfo, boolean0, boolean1, nullptr);
 break;
 case W:
 this->prerender1xW(float0, float1, float2, colorInfo, boolean0, boolean1, nullptr);
 break;
 case E:
 this->prerender1xE(float0, float1, float2, colorInfo, boolean0, boolean1, nullptr);
 }
 } else {
 switch (directions) {
 case N:
 this->prerender2xN(float0, float1, float2, colorInfo, boolean0, boolean1, nullptr);
 break;
 case S:
 this->prerender2xS(float0, float1, float2, colorInfo, boolean0, boolean1, nullptr);
 break;
 case W:
 this->prerender2xW(float0, float1, float2, colorInfo, boolean0, boolean1, nullptr);
 break;
 case E:
 this->prerender2xE(float0, float1, float2, colorInfo, boolean0, boolean1, nullptr);
 }
 }
 }

 void postrender(float float0, float float1, float float2, ColorInfo colorInfo, bool boolean0, bool boolean1, IsoDirections directions) {
 if (Core.TileScale == 1) {
 switch (directions) {
 case N:
 this->postrender1xN(float0, float1, float2, colorInfo, boolean0, boolean1, nullptr);
 break;
 case S:
 this->postrender1xS(float0, float1, float2, colorInfo, boolean0, boolean1, nullptr);
 break;
 case W:
 this->postrender1xW(float0, float1, float2, colorInfo, boolean0, boolean1, nullptr);
 break;
 case E:
 this->postrender1xE(float0, float1, float2, colorInfo, boolean0, boolean1, nullptr);
 }
 } else {
 switch (directions) {
 case N:
 this->postrender2xN(float0, float1, float2, colorInfo, boolean0, boolean1, nullptr);
 break;
 case S:
 this->postrender2xS(float0, float1, float2, colorInfo, boolean0, boolean1, nullptr);
 break;
 case W:
 this->postrender2xW(float0, float1, float2, colorInfo, boolean0, boolean1, nullptr);
 break;
 case E:
 this->postrender2xE(float0, float1, float2, colorInfo, boolean0, boolean1, nullptr);
 }
 }
 }

 void prerender1xN(float float0, float float2, float float1, ColorInfo colorInfo, bool var5, bool var6, Shader var7) {
 if (this->bCurtainInside) {
 if (!this->north && this->open) {
 (this->bCurtainOpen ? this->curtainSopen : this->curtainS)
 .render(nullptr, float0, float2 - 1.0F, float1, this->dir, this->offsetX + 3.0F, this->offsetY + (this->bCurtainOpen ? -14 : -14), colorInfo, true);
 }
 } else if (this->north && !this->open) {
 (this->bCurtainOpen ? this->curtainSopen : this->curtainS)
 .render(nullptr, float0, float2 - 1.0F, float1, this->dir, this->offsetX - 1.0F - 1.0F, this->offsetY + -15.0F, colorInfo, true);
 }
 }

 void postrender1xN(float float0, float float1, float float2, ColorInfo colorInfo, bool var5, bool var6, Shader var7) {
 if (this->bCurtainInside) {
 if (this->north && !this->open) {
 (this->bCurtainOpen ? this->curtainNopen : this->curtainN)
 .render(nullptr, float0, float1, float2, this->dir, this->offsetX - 10.0F - 1.0F, this->offsetY + -10.0F, colorInfo, true);
 }
 } else if (!this->north && this->open) {
 (this->bCurtainOpen ? this->curtainNopen : this->curtainN)
 .render(nullptr, float0, float1, float2, this->dir, this->offsetX - 4.0F, this->offsetY + (this->bCurtainOpen ? -10 : -10), colorInfo, true);
 }
 }

 void prerender1xS(float float0, float float1, float float2, ColorInfo colorInfo, bool var5, bool var6, Shader var7) {
 assert !this->north && this->open;

 if (!this->bCurtainInside) {
 (this->bCurtainOpen ? this->curtainSopen : this->curtainS)
 .render(
 nullptr,
 float0,
 float1,
 float2,
 this->dir,
 this->offsetX + (this->bCurtainOpen ? -14 : -14) / 2,
 this->offsetY + (this->bCurtainOpen ? -16 : -16) / 2,
 colorInfo,
 true
 );
 }
 }

 void postrender1xS(float float0, float float2, float float1, ColorInfo colorInfo, bool var5, bool var6, Shader var7) {
 assert !this->north && this->open;

 if (this->bCurtainInside) {
 (this->bCurtainOpen ? this->curtainNopen : this->curtainN)
 .render(
 nullptr,
 float0,
 float2 + 1.0F,
 float1,
 this->dir,
 this->offsetX + (this->bCurtainOpen ? -28 : -28) / 2,
 this->offsetY + (this->bCurtainOpen ? -8 : -8) / 2,
 colorInfo,
 true
 );
 }
 }

 void prerender1xW(float float2, float float0, float float1, ColorInfo colorInfo, bool var5, bool var6, Shader var7) {
 if (this->bCurtainInside) {
 if (this->north && this->open) {
 (this->bCurtainOpen ? this->curtainEopen : this->curtainE)
 .render(
 nullptr,
 float2 - 1.0F,
 float0,
 float1,
 this->dir,
 this->offsetX + (this->bCurtainOpen ? -16 : -18),
 this->offsetY + (this->bCurtainOpen ? -14 : -15),
 colorInfo,
 true
 );
 }

 if (!this->north && this->open) {
 (this->bCurtainOpen ? this->curtainSopen : this->curtainS)
 .render(nullptr, float2, float0 - 1.0F, float1, this->dir, this->offsetX + 3.0F, this->offsetY + (this->bCurtainOpen ? -14 : -14), colorInfo, true);
 }
 } else {
 if (this->north && !this->open) {
 (this->bCurtainOpen ? this->curtainSopen : this->curtainS)
 .render(nullptr, float2, float0 - 1.0F, float1, this->dir, this->offsetX - 1.0F - 1.0F, this->offsetY + -15.0F, colorInfo, true);
 }

 if (!this->north && !this->open) {
 (this->bCurtainOpen ? this->curtainEopen : this->curtainE)
 .render(
 nullptr,
 float2 - 1.0F,
 float0,
 float1,
 this->dir,
 this->offsetX + (this->bCurtainOpen ? -12 : -14),
 this->offsetY + (this->bCurtainOpen ? -14 : -15),
 colorInfo,
 true
 );
 }
 }
 }

 void postrender1xW(float float0, float float1, float float2, ColorInfo colorInfo, bool var5, bool var6, Shader var7) {
 if (this->bCurtainInside) {
 if (this->north && !this->open) {
 (this->bCurtainOpen ? this->curtainNopen : this->curtainN)
 .render(nullptr, float0, float1, float2, this->dir, this->offsetX - 10.0F - 1.0F, this->offsetY + -10.0F, colorInfo, true);
 }

 if (!this->north && !this->open) {
 (this->bCurtainOpen ? this->curtainWopen : this->curtainW)
 .render(nullptr, float0, float1, float2, this->dir, this->offsetX - 2.0F - 1.0F, this->offsetY + -10.0F, colorInfo, true);
 }
 } else {
 if (this->north && this->open) {
 (this->bCurtainOpen ? this->curtainWopen : this->curtainW)
 .render(nullptr, float0, float1, float2, this->dir, this->offsetX - 9.0F, this->offsetY + -10.0F, colorInfo, true);
 }

 if (!this->north && this->open) {
 (this->bCurtainOpen ? this->curtainNopen : this->curtainN)
 .render(nullptr, float0, float1, float2, this->dir, this->offsetX - 4.0F, this->offsetY + (this->bCurtainOpen ? -10 : -10), colorInfo, true);
 }
 }
 }

 void prerender1xE(float float0, float float1, float float2, ColorInfo colorInfo, bool var5, bool var6, Shader var7) {
 assert this->north && this->open;

 if (!this->bCurtainInside) {
 (this->bCurtainOpen ? this->curtainEopen : this->curtainE)
 .render(
 nullptr,
 float0,
 float1,
 float2,
 this->dir,
 this->offsetX + (this->bCurtainOpen ? -13 : -18) / 2,
 this->offsetY + (this->bCurtainOpen ? -15 : -18) / 2,
 colorInfo,
 true
 );
 }
 }

 void postrender1xE(float float2, float float0, float float1, ColorInfo colorInfo, bool var5, bool var6, Shader var7) {
 assert this->north && this->open;

 if (this->bCurtainInside) {
 (this->bCurtainOpen ? this->curtainWopen : this->curtainW)
 .render(
 nullptr,
 float2 + 1.0F,
 float0,
 float1,
 this->dir,
 this->offsetX + (this->bCurtainOpen ? 0 : 0),
 this->offsetY + (this->bCurtainOpen ? 0 : 0),
 colorInfo,
 true
 );
 }
 }

 void prerender2xN(float float0, float float2, float float1, ColorInfo colorInfo, bool var5, bool var6, Shader var7) {
 if (this->bCurtainInside) {
 if (!this->north && this->open) {
 (this->bCurtainOpen ? this->curtainSopen : this->curtainS)
 .render(nullptr, float0, float2 - 1.0F, float1, this->dir, this->offsetX + 7.0F, this->offsetY + (this->bCurtainOpen ? -28 : -28), colorInfo, true);
 }
 } else if (this->north && !this->open) {
 (this->bCurtainOpen ? this->curtainSopen : this->curtainS)
 .render(nullptr, float0, float2 - 1.0F, float1, this->dir, this->offsetX - 3.0F, this->offsetY + (this->bCurtainOpen ? -30 : -30), colorInfo, true);
 }
 }

 void postrender2xN(float float0, float float1, float float2, ColorInfo colorInfo, bool var5, bool var6, Shader var7) {
 if (this->bCurtainInside) {
 if (this->north && !this->open) {
 (this->bCurtainOpen ? this->curtainNopen : this->curtainN)
 .render(nullptr, float0, float1, float2, this->dir, this->offsetX - 20.0F, this->offsetY + (this->bCurtainOpen ? -20 : -20), colorInfo, true);
 }
 } else if (!this->north && this->open) {
 (this->bCurtainOpen ? this->curtainNopen : this->curtainN)
 .render(nullptr, float0, float1, float2, this->dir, this->offsetX - 8.0F, this->offsetY + (this->bCurtainOpen ? -20 : -20), colorInfo, true);
 }
 }

 void prerender2xS(float float0, float float1, float float2, ColorInfo colorInfo, bool var5, bool var6, Shader var7) {
 assert !this->north && this->open;

 if (!this->bCurtainInside) {
 (this->bCurtainOpen ? this->curtainSopen : this->curtainS)
 .render(
 nullptr,
 float0,
 float1,
 float2,
 this->dir,
 this->offsetX + (this->bCurtainOpen ? -14 : -14),
 this->offsetY + (this->bCurtainOpen ? -16 : -16),
 colorInfo,
 true
 );
 }
 }

 void postrender2xS(float float0, float float2, float float1, ColorInfo colorInfo, bool var5, bool var6, Shader var7) {
 assert !this->north && this->open;

 if (this->bCurtainInside) {
 (this->bCurtainOpen ? this->curtainNopen : this->curtainN)
 .render(
 nullptr,
 float0,
 float2 + 1.0F,
 float1,
 this->dir,
 this->offsetX + (this->bCurtainOpen ? -28 : -28),
 this->offsetY + (this->bCurtainOpen ? -8 : -8),
 colorInfo,
 true
 );
 }
 }

 void prerender2xW(float float2, float float0, float float1, ColorInfo colorInfo, bool var5, bool var6, Shader var7) {
 if (this->bCurtainInside) {
 if (this->north && this->open) {
 (this->bCurtainOpen ? this->curtainEopen : this->curtainE)
 .render(
 nullptr,
 float2 - 1.0F,
 float0,
 float1,
 this->dir,
 this->offsetX + (this->bCurtainOpen ? -32 : -37),
 this->offsetY + (this->bCurtainOpen ? -28 : -31),
 colorInfo,
 true
 );
 }
 } else if (!this->north && !this->open) {
 (this->bCurtainOpen ? this->curtainEopen : this->curtainE)
 .render(
 nullptr,
 float2 - 1.0F,
 float0,
 float1,
 this->dir,
 this->offsetX + (this->bCurtainOpen ? -22 : -26),
 this->offsetY + (this->bCurtainOpen ? -28 : -31),
 colorInfo,
 true
 );
 }
 }

 void postrender2xW(float float0, float float1, float float2, ColorInfo colorInfo, bool var5, bool var6, Shader var7) {
 if (this->bCurtainInside) {
 if (!this->north && !this->open) {
 (this->bCurtainOpen ? this->curtainWopen : this->curtainW)
 .render(nullptr, float0, float1, float2, this->dir, this->offsetX - 5.0F, this->offsetY + (this->bCurtainOpen ? -20 : -20), colorInfo, true);
 }
 } else if (this->north && this->open) {
 (this->bCurtainOpen ? this->curtainWopen : this->curtainW)
 .render(nullptr, float0, float1, float2, this->dir, this->offsetX - 19.0F, this->offsetY + (this->bCurtainOpen ? -20 : -20), colorInfo, true);
 }
 }

 void prerender2xE(float float0, float float1, float float2, ColorInfo colorInfo, bool var5, bool var6, Shader var7) {
 assert this->north && this->open;

 if (!this->bCurtainInside) {
 (this->bCurtainOpen ? this->curtainEopen : this->curtainE)
 .render(
 nullptr,
 float0,
 float1,
 float2,
 this->dir,
 this->offsetX + (this->bCurtainOpen ? -13 : -18),
 this->offsetY + (this->bCurtainOpen ? -15 : -18),
 colorInfo,
 true
 );
 }
 }

 void postrender2xE(float float2, float float0, float float1, ColorInfo colorInfo, bool var5, bool var6, Shader var7) {
 assert this->north && this->open;

 if (this->bCurtainInside) {
 (this->bCurtainOpen ? this->curtainWopen : this->curtainW)
 .render(
 nullptr,
 float2 + 1.0F,
 float0,
 float1,
 this->dir,
 this->offsetX + (this->bCurtainOpen ? 0 : 0),
 this->offsetY + (this->bCurtainOpen ? 0 : 0),
 colorInfo,
 true
 );
 }
 }

 IsoDirections getSpriteEdge(bool ignoreOpen) {
 if (this->open && !ignoreOpen) {
 PropertyContainer propertyContainer = this->getProperties();
 if (propertyContainer != nullptr && propertyContainer.Is("GarageDoor")) {
 return this->north ? IsoDirections.N : IsoDirections.W;
 } else if (propertyContainer != nullptr && propertyContainer.Is(IsoFlagType.attachedE) {
 return IsoDirections.E;
 } else if (propertyContainer != nullptr && propertyContainer.Is(IsoFlagType.attachedS) {
 return IsoDirections.S;
 } else {
 return this->north ? IsoDirections.W : IsoDirections.N;
 }
 } else {
 return this->north ? IsoDirections.N : IsoDirections.W;
 }
 }

 public IsoDoor(IsoCell cell, IsoGridSquare gridSquare, IsoSprite _gid, bool _north) {
 this->open = _gid.getProperties().Is(IsoFlagType.open);
 this->OutlineOnMouseover = true;
 this->PushedMaxStrength = this->PushedStrength = 2500;
 uint8_t byte0 = 2;
 if (_gid.getProperties().Is("DoubleDoor")) {
 byte0 = 4;
 }

 if (_gid.getProperties().Is("GarageDoor")) {
 byte0 = 8;
 }

 this->closedSprite = this->open ? IsoSprite.getSprite(IsoSpriteManager.instance, _gid, -byte0) : _gid;
 this->openSprite = this->open ? _gid : IsoSprite.getSprite(IsoSpriteManager.instance, _gid, byte0);
 this->sprite = this->open ? this->openSprite : this->closedSprite;
 this->square = gridSquare;
 this->north = _north;
 switch (this->type) {
 case WeakWooden:
 this->MaxHealth = this->Health = 500;
 break;
 case StrongWooden:
 this->MaxHealth = this->Health = 800;
 }

 if (this->getSprite().getName() != nullptr && this->getSprite().getName().contains("fences")) {
 this->MaxHealth = this->Health = 100;
 }

 uint8_t byte1 = 69;
 if (SandboxOptions.instance.LockedHouses.getValue() == 1) {
 byte1 = -1;
 } else if (SandboxOptions.instance.LockedHouses.getValue() == 2) {
 byte1 = 5;
 } else if (SandboxOptions.instance.LockedHouses.getValue() == 3) {
 byte1 = 10;
 } else if (SandboxOptions.instance.LockedHouses.getValue() == 4) {
 byte1 = 50;
 } else if (SandboxOptions.instance.LockedHouses.getValue() == 5) {
 byte1 = 60;
 } else if (SandboxOptions.instance.LockedHouses.getValue() == 6) {
 byte1 = 70;
 }

 if (byte1 > -1) {
 this->Locked = Rand.Next(100) < byte1;
 if (this->Locked && Rand.Next(3) == 0) {
 this->lockedByKey = true;
 }
 }

 if (this->getProperties().Is("forceLocked")) {
 this->Locked = true;
 this->lockedByKey = true;
 }

 if (this->open) {
 this->Locked = false;
 this->lockedByKey = false;
 }
 }

 public IsoDoor(IsoCell cell, IsoGridSquare gridSquare, const std::string& _gid, bool _north) {
 this->OutlineOnMouseover = true;
 this->PushedMaxStrength = this->PushedStrength = 2500;
 this->closedSprite = IsoSprite.getSprite(IsoSpriteManager.instance, _gid, 0);
 this->openSprite = IsoSprite.getSprite(IsoSpriteManager.instance, _gid, 2);
 this->sprite = this->closedSprite;
 std::string string = this->closedSprite.getProperties().Val("GarageDoor");
 if (string != nullptr) {
 int int0 = Integer.parseInt(string);
 if (int0 <= 3) {
 this->openSprite = IsoSprite.getSprite(IsoSpriteManager.instance, _gid, 8);
 } else {
 this->openSprite = this->sprite;
 this->closedSprite = IsoSprite.getSprite(IsoSpriteManager.instance, _gid, -8);
 }
 }

 this->square = gridSquare;
 this->north = _north;
 switch (this->type) {
 case WeakWooden:
 this->MaxHealth = this->Health = 500;
 break;
 case StrongWooden:
 this->MaxHealth = this->Health = 800;
 }

 if (this->getSprite().getName() != nullptr && this->getSprite().getName().contains("fences")) {
 this->MaxHealth = this->Health = 100;
 }
 }

 public IsoDoor(IsoCell cell, IsoGridSquare gridSquare, const std::string& _gid, bool _north, KahluaTable _table) {
 this->OutlineOnMouseover = true;
 this->PushedMaxStrength = this->PushedStrength = 2500;
 this->closedSprite = IsoSprite.getSprite(IsoSpriteManager.instance, _gid, 0);
 this->openSprite = IsoSprite.getSprite(IsoSpriteManager.instance, _gid, 2);
 this->table = _table;
 this->sprite = this->closedSprite;
 std::string string = this->sprite.getProperties().Val("GarageDoor");
 if (string != nullptr) {
 int int0 = Integer.parseInt(string);
 if (int0 <= 3) {
 this->openSprite = IsoSprite.getSprite(IsoSpriteManager.instance, _gid, 8);
 } else {
 this->openSprite = this->sprite;
 this->closedSprite = IsoSprite.getSprite(IsoSpriteManager.instance, _gid, -8);
 }
 }

 this->square = gridSquare;
 this->north = _north;
 switch (this->type) {
 case WeakWooden:
 this->MaxHealth = this->Health = 500;
 break;
 case StrongWooden:
 this->MaxHealth = this->Health = 800;
 }

 if (this->getSprite().getName() != nullptr && this->getSprite().getName().contains("fences")) {
 this->MaxHealth = this->Health = 100;
 }
 }

 void load(ByteBuffer input, int WorldVersion, bool IS_DEBUG_SAVE) {
 super.load(input, WorldVersion, IS_DEBUG_SAVE);
 this->open = input.get() == 1;
 this->Locked = input.get() == 1;
 this->north = input.get() == 1;
 this->Health = input.getInt();
 this->MaxHealth = input.getInt();
 this->closedSprite = IsoSprite.getSprite(IsoSpriteManager.instance, input.getInt());
 this->openSprite = IsoSprite.getSprite(IsoSpriteManager.instance, input.getInt());
 this->OutlineOnMouseover = true;
 this->PushedMaxStrength = this->PushedStrength = 2500;
 if (WorldVersion >= 57) {
 this->keyId = input.getInt();
 this->lockedByKey = input.get() == 1;
 }

 if (WorldVersion >= 80) {
 uint8_t byte0 = input.get();
 if ((byte0 & 1) != 0) {
 this->bHasCurtain = true;
 this->bCurtainOpen = (byte0 & 2) != 0;
 this->bCurtainInside = (byte0 & 4) != 0;
 }
 }

 if (SystemDisabler.doObjectStateSyncEnable && GameClient.bClient) {
 GameClient.instance.objectSyncReq.putRequestLoad(this->square);
 }
 }

 void save(ByteBuffer output, bool IS_DEBUG_SAVE) {
 super.save(output, IS_DEBUG_SAVE);
 output.put((byte)(this->open ? 1 : 0);
 output.put((byte)(this->Locked ? 1 : 0);
 output.put((byte)(this->north ? 1 : 0);
 output.putInt(this->Health);
 output.putInt(this->MaxHealth);
 output.putInt(this->closedSprite.ID);
 output.putInt(this->openSprite.ID);
 output.putInt(this->getKeyId());
 output.put((byte)(this->isLockedByKey() ? 1 : 0);
 uint8_t byte0 = 0;
 if (this->bHasCurtain) {
 byte0 = (byte)(byte0 | 1);
 if (this->bCurtainOpen) {
 byte0 = (byte)(byte0 | 2);
 }

 if (this->bCurtainInside) {
 byte0 = (byte)(byte0 | 4);
 }
 }

 output.put(byte0);
 }

 void saveState(ByteBuffer bb) {
 bb.put((byte)(this->open ? 1 : 0);
 bb.put((byte)(this->Locked ? 1 : 0);
 bb.put((byte)(this->lockedByKey ? 1 : 0);
 }

 void loadState(ByteBuffer bb) {
 bool boolean0 = bb.get() == 1;
 bool boolean1 = bb.get() == 1;
 bool boolean2 = bb.get() == 1;
 if (boolean0 != this->open) {
 this->open = boolean0;
 this->sprite = boolean0 ? this->openSprite : this->closedSprite;
 }

 if (boolean1 != this->Locked) {
 this->Locked = boolean1;
 }

 if (boolean2 != this->lockedByKey) {
 this->lockedByKey = boolean2;
 }
 }

 bool isDestroyed() {
 return this->destroyed;
 }

 bool IsOpen() {
 return this->open;
 }

 bool IsStrengthenedByPushedItems() {
 return false;
 }

 bool onMouseLeftClick(int x, int y) {
 return false;
 }

 bool TestPathfindCollide(IsoMovingObject obj, IsoGridSquare from, IsoGridSquare to) {
 bool boolean0 = this->north;
 if (!this->isBarricaded()) {
 return false;
 } else if (obj instanceof IsoSurvivor && ((IsoSurvivor)obj).getInventory().contains("Hammer")) {
 return false;
 } else {
 if (this->open) {
 boolean0 = !boolean0;
 }

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
 bool boolean0 = this->north;
 if (this->open) {
 return false;
 } else {
 if (from == this->square) {
 if (boolean0 && to.getY() < from.getY()) {
 if (obj != nullptr) {
 obj.collideWith(this);
 }

 return true;
 }

 if (!boolean0 && to.getX() < from.getX()) {
 if (obj != nullptr) {
 obj.collideWith(this);
 }

 return true;
 }
 } else {
 if (boolean0 && to.getY() > from.getY()) {
 if (obj != nullptr) {
 obj.collideWith(this);
 }

 return true;
 }

 if (!boolean0 && to.getX() > from.getX()) {
 if (obj != nullptr) {
 obj.collideWith(this);
 }

 return true;
 }
 }

 return false;
 }
 }

 public IsoObject.VisionResult TestVision(IsoGridSquare from, IsoGridSquare to) {
 bool boolean0 = this->sprite != nullptr && this->sprite.getProperties().Is("doorTrans");
 if (this->sprite != nullptr && this->sprite.getProperties().Is("GarageDoor") && this->open) {
 boolean0 = true;
 }

 if (this->open) {
 boolean0 = true;
 } else if (this->bHasCurtain && !this->bCurtainOpen) {
 boolean0 = false;
 }

 bool boolean1 = this->north;
 if (this->open) {
 boolean1 = !boolean1;
 }

 if (to.getZ() != from.getZ()) {
 return IsoObject.VisionResult.NoEffect;
 } else {
 if (from == this->square) {
 if (boolean1 && to.getY() < from.getY()) {
 if (boolean0) {
 return IsoObject.VisionResult.Unblocked;
 }

 return IsoObject.VisionResult.Blocked;
 }

 if (!boolean1 && to.getX() < from.getX()) {
 if (boolean0) {
 return IsoObject.VisionResult.Unblocked;
 }

 return IsoObject.VisionResult.Blocked;
 }
 } else {
 if (boolean1 && to.getY() > from.getY()) {
 if (boolean0) {
 return IsoObject.VisionResult.Unblocked;
 }

 return IsoObject.VisionResult.Blocked;
 }

 if (!boolean1 && to.getX() > from.getX()) {
 if (boolean0) {
 return IsoObject.VisionResult.Unblocked;
 }

 return IsoObject.VisionResult.Blocked;
 }
 }

 return IsoObject.VisionResult.NoEffect;
 }
 }

 void Thump(IsoMovingObject thumper) {
 if (!this->isDestroyed()) {
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
 if (((IsoZombie)thumper).cognition == 1
 && !this->open
 && (!this->Locked || thumper.getCurrentSquare() != nullptr && !thumper.getCurrentSquare().Is(IsoFlagType.exterior) {
 this->ToggleDoor((IsoGameCharacter)thumper);
 if (this->open) {
 return;
 }
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

 int int1 = ThumpState.getFastForwardDamageMultiplier();
 int int2 = ((IsoZombie)thumper).strength;
 if (int0 >= 2) {
 this->DirtySlice();
 this->Damage(((IsoZombie)thumper).strength * int1);
 if (SandboxOptions.instance.Lore.Strength.getValue() == 1) {
 this->Damage(int0 * 2 * int1);
 }
 }

 if (Core.GameMode == "LastStand")) {
 this->Damage(1 * int1);
 }

 WorldSoundManager.instance.addSound(thumper, this->square.getX(), this->square.getY(), this->square.getZ(), 20, 20, true, 4.0F, 15.0F);
 this->setRenderEffect(RenderEffectType.Hit_Door, true);
 }

 if (this->Health <= 0) {
 if (this->getSquare().getBuilding() != nullptr) {
 this->getSquare().getBuilding().forceAwake();
 }

 this->playDoorSound(((IsoGameCharacter)thumper).getEmitter(), "Break");
 if (GameServer.bServer) {
 GameServer.PlayWorldSoundServer((IsoGameCharacter)thumper, "BreakDoor", false, thumper.getCurrentSquare(), 0.2F, 20.0F, 1.1F, true);
 }

 WorldSoundManager.instance.addSound(nullptr, this->square.getX(), this->square.getY(), this->square.getZ(), 10, 20, true, 4.0F, 15.0F);
 thumper.setThumpTarget(nullptr);
 if (destroyDoubleDoor(this) {
 return;
 }

 if (destroyGarageDoor(this) {
 return;
 }

 this->destroy();
 }
 }
 }

 Thumpable getThumpableFor(IsoGameCharacter chr) {
 IsoBarricade barricade = this->getBarricadeForCharacter(chr);
 if (barricade != nullptr) {
 return barricade;
 } else {
 barricade = this->getBarricadeOppositeCharacter(chr);
 if (barricade != nullptr) {
 return barricade;
 } else {
 return !this->isDestroyed() && !this->IsOpen() ? this : nullptr;
 }
 }
 }

 float getThumpCondition() {
 return this->getMaxHealth() <= 0 ? 0.0F : (float)PZMath.clamp(this->getHealth(), 0, this->getMaxHealth()) / this->getMaxHealth();
 }

 void WeaponHit(IsoGameCharacter owner, HandWeapon weapon) {
 IsoPlayer player = Type.tryCastTo(owner, IsoPlayer.class);
 if (GameClient.bClient) {
 if (player != nullptr) {
 GameClient.instance.sendWeaponHit(player, weapon, this);
 }

 this->setRenderEffect(RenderEffectType.Hit_Door, true);
 } else {
 Thumpable thumpable = this->getThumpableFor(owner);
 if (thumpable != nullptr) {
 if (thumpable instanceof IsoBarricade) {
 ((IsoBarricade)thumpable).WeaponHit(owner, weapon);
 } else {
 LuaEventManager.triggerEvent("OnWeaponHitThumpable", owner, weapon, this);
 if (!this->open) {
 if (!this->isDestroyed()) {
 int int0 = owner.getPerkLevel(PerkFactory.Perks.Strength);
 float float0 = 1.0F;
 if (int0 == 0) {
 float0 = 0.5F;
 } else if (int0 == 1) {
 float0 = 0.63F;
 } else if (int0 == 2) {
 float0 = 0.76F;
 } else if (int0 == 3) {
 float0 = 0.89F;
 } else if (int0 == 4) {
 float0 = 1.02F;
 }

 if (int0 == 6) {
 float0 = 1.15F;
 } else if (int0 == 7) {
 float0 = 1.27F;
 } else if (int0 == 8) {
 float0 = 1.3F;
 } else if (int0 == 9) {
 float0 = 1.45F;
 } else if (int0 == 10) {
 float0 = 1.7F;
 }

 this->Damage((int)(weapon.getDoorDamage() * 2.0F * float0);
 this->setRenderEffect(RenderEffectType.Hit_Door, true);
 if (Rand.Next(10) == 0) {
 this->Damage((int)(weapon.getDoorDamage() * 6.0F * float0);
 }

 float float1 = GameTime.getInstance().getMultiplier() / 1.6F;
 switch (owner.getPerkLevel(PerkFactory.Perks.Fitness) {
 case 0:
 owner.exert(0.01F * float1);
 break;
 case 1:
 owner.exert(0.007F * float1);
 break;
 case 2:
 owner.exert(0.0065F * float1);
 break;
 case 3:
 owner.exert(0.006F * float1);
 break;
 case 4:
 owner.exert(0.005F * float1);
 break;
 case 5:
 owner.exert(0.004F * float1);
 break;
 case 6:
 owner.exert(0.0035F * float1);
 break;
 case 7:
 owner.exert(0.003F * float1);
 break;
 case 8:
 owner.exert(0.0025F * float1);
 break;
 case 9:
 owner.exert(0.002F * float1);
 }

 this->DirtySlice();
 if (weapon.getDoorHitSound() != nullptr) {
 if (player != nullptr) {
 player.setMeleeHitSurface(this->getSoundPrefix());
 }

 owner.getEmitter().playSound(weapon.getDoorHitSound(), this);
 if (GameServer.bServer) {
 GameServer.PlayWorldSoundServer(owner, weapon.getDoorHitSound(), false, this->getSquare(), 1.0F, 20.0F, 2.0F, false);
 }
 }

 WorldSoundManager.instance.addSound(owner, this->square.getX(), this->square.getY(), this->square.getZ(), 20, 20, false, 0.0F, 15.0F);
 if (!this->IsStrengthenedByPushedItems() && this->Health <= 0
 || this->IsStrengthenedByPushedItems() && this->Health <= -this->PushedMaxStrength) {
 this->playDoorSound(owner.getEmitter(), "Break");
 if (GameServer.bServer) {
 GameServer.PlayWorldSoundServer(owner, "BreakDoor", false, this->getSquare(), 0.2F, 20.0F, 1.1F, true);
 }

 WorldSoundManager.instance
 .addSound(owner, this->square.getX(), this->square.getY(), this->square.getZ(), 20, 20, false, 0.0F, 15.0F);
 if (destroyDoubleDoor(this) {
 return;
 }

 if (destroyGarageDoor(this) {
 return;
 }

 this->destroy();
 LuaEventManager.triggerEvent("OnContainerUpdate");
 }
 }
 }
 }
 }
 }
 }

 void destroy() {
 if (this->sprite != nullptr && this->sprite.getProperties().Is("GarageDoor")) {
 this->destroyed = true;
 this->square.transmitRemoveItemFromSquare(this);
 } else {
 PropertyContainer propertyContainer = this->getProperties();
 if (propertyContainer != nullptr) {
 std::string string0 = propertyContainer.Val("Material");
 std::string string1 = propertyContainer.Val("Material2");
 std::string string2 = propertyContainer.Val("Material3");
 if (StringUtils.isNullOrEmpty(string0) && StringUtils.isNullOrEmpty(string1) && StringUtils.isNullOrEmpty(string2) {
 int int0 = Rand.Next(2) + 1;

 for (int int1 = 0; int1 < int0; int1++) {
 this->square.AddWorldInventoryItem("Base.Plank", 0.0F, 0.0F, 0.0F);
 }
 } else {
 this->addItemsFromProperties();
 }

 InventoryItem item = InventoryItemFactory.CreateItem("Base.Doorknob");
 item.setKeyId(this->checkKeyId());
 this->square.AddWorldInventoryItem(item, 0.0F, 0.0F, 0.0F);
 int int2 = Rand.Next(3);

 for (int int3 = 0; int3 < int2; int3++) {
 this->square.AddWorldInventoryItem("Base.Hinge", 0.0F, 0.0F, 0.0F);
 }

 if (this->bHasCurtain) {
 this->square.AddWorldInventoryItem("Base.Sheet", 0.0F, 0.0F, 0.0F);
 }

 this->destroyed = true;
 this->square.transmitRemoveItemFromSquare(this);
 }
 }
 }

 IsoGridSquare getOtherSideOfDoor(IsoGameCharacter chr) {
 if (this->north) {
 return chr.getCurrentSquare().getRoom() == this->square.getRoom()
 ? IsoWorld.instance.CurrentCell.getGridSquare(this->square.getX(), this->square.getY() - 1, this->square.getZ())
 : IsoWorld.instance.CurrentCell.getGridSquare(this->square.getX(), this->square.getY(), this->square.getZ());
 } else {
 return chr.getCurrentSquare().getRoom() == this->square.getRoom()
 ? IsoWorld.instance.CurrentCell.getGridSquare(this->square.getX() - 1, this->square.getY(), this->square.getZ())
 : IsoWorld.instance.CurrentCell.getGridSquare(this->square.getX(), this->square.getY(), this->square.getZ());
 }
 }

 bool isExteriorDoor(IsoGameCharacter chr) {
 return this->isExterior();
 }

 bool isExterior() {
 IsoGridSquare square0 = this->getSquare();
 IsoGridSquare square1 = this->getOppositeSquare();
 if (square1.empty()) {
 return false;
 } else {
 return square0.Is(IsoFlagType.exterior) && square1.getBuilding() != nullptr && square1.getBuilding().getDef() != nullptr
 ? true
 : square0.getBuilding() != nullptr && square0.getBuilding().getDef() != nullptr && square1.Is(IsoFlagType.exterior);
 }
 }

 bool isHoppable() {
 if (this->IsOpen()) {
 return false;
 } else if (this->closedSprite.empty()) {
 return false;
 } else {
 PropertyContainer propertyContainer = this->closedSprite.getProperties();
 return propertyContainer.Is(IsoFlagType.HoppableN) || propertyContainer.Is(IsoFlagType.HoppableW);
 }
 }

 bool canClimbOver(IsoGameCharacter chr) {
 if (this->square.empty()) {
 return false;
 } else {
 return !this->isHoppable() ? false : chr.empty() || IsoWindow.canClimbThroughHelper(chr, this->getSquare(), this->getOppositeSquare(), this->north);
 }
 }

 void ToggleDoorActual(IsoGameCharacter chr) {
 if (Core.bDebug && DebugOptions.instance.CheatDoorUnlock.getValue()) {
 this->Locked = false;
 this->setLockedByKey(false);
 }

 if (this->isHoppable()) {
 this->Locked = false;
 this->setLockedByKey(false);
 }

 if (this->isBarricaded()) {
 if (chr != nullptr) {
 this->playDoorSound(chr.getEmitter(), "Blocked");
 chr.setHaloNote(Translator.getText("IGUI_PlayerText_DoorBarricaded"), 255, 255, 255, 256.0F);
 this->setRenderEffect(RenderEffectType.Hit_Door, true);
 }
 } else {
 this->checkKeyId();
 if (this->Locked && !this->lockedByKey && this->getKeyId() != -1) {
 this->lockedByKey = true;
 }

 if (!this->open && chr instanceof IsoPlayer) {
 ((IsoPlayer)chr).TimeSinceOpenDoor = 0.0F;
 }

 this->DirtySlice();
 IsoGridSquare.RecalcLightTime = -1;
 GameTime.instance.lightSourceUpdate = 100.0F;
 this->square.InvalidateSpecialObjectPaths();
 if (this->isLockedByKey()
 && chr != nullptr
 && chr instanceof IsoPlayer
 && (
 chr.getCurrentSquare().Is(IsoFlagType.exterior)
 || this->getProperties().Is("forceLocked")
 || this->getModData().rawget("CustomLock") != nullptr
 && this->getModData().rawget("CustomLock") instanceof Boolean
 && (Boolean)this->getModData().rawget("CustomLock")
 )
 && !this->open) {
 if (chr.getInventory().haveThisKeyId(this->getKeyId()) == nullptr) {
 this->playDoorSound(chr.getEmitter(), "Locked");
 this->setRenderEffect(RenderEffectType.Hit_Door, true);
 return;
 }

 this->playDoorSound(chr.getEmitter(), "Unlock");
 this->playDoorSound(chr.getEmitter(), "Open");
 this->Locked = false;
 this->setLockedByKey(false);
 }

 bool boolean0 = chr instanceof IsoPlayer && !chr.getCurrentSquare().isOutside();
 if ("Tutorial" == Core.getInstance().getGameMode()) && this->isLockedByKey()) {
 boolean0 = false;
 }

 if (chr instanceof IsoPlayer && this->getSprite().getProperties().Is("GarageDoor")) {
 bool boolean1 = this->getSprite().getProperties().Is("InteriorSide");
 if (boolean1) {
 boolean0 = this->north ? chr.getY() >= this->getY() : chr.getX() >= this->getX();
 } else {
 boolean0 = this->north ? chr.getY() < this->getY() : chr.getX() < this->getX();
 }
 }

 if (this->Locked && !boolean0 && !this->open) {
 this->playDoorSound(chr.getEmitter(), "Locked");
 this->setRenderEffect(RenderEffectType.Hit_Door, true);
 } else if (this->getSprite().getProperties().Is("DoubleDoor")) {
 if (isDoubleDoorObstructed(this) {
 if (chr != nullptr) {
 this->playDoorSound(chr.getEmitter(), "Blocked");
 chr.setHaloNote(Translator.getText("IGUI_PlayerText_DoorBlocked"), 255, 255, 255, 256.0F);
 }
 } else {
 bool boolean2 = this->open;
 toggleDoubleDoor(this, true);
 if (boolean2 != this->open) {
 this->playDoorSound(chr.getEmitter(), this->open ? "Open" : "Close");
 }
 }
 } else if (this->getSprite().getProperties().Is("GarageDoor")) {
 if (isGarageDoorObstructed(this) {
 if (chr != nullptr) {
 this->playDoorSound(chr.getEmitter(), "Blocked");
 chr.setHaloNote(Translator.getText("IGUI_PlayerText_DoorBlocked"), 255, 255, 255, 256.0F);
 }
 } else {
 bool boolean3 = this->open;
 toggleGarageDoor(this, true);
 if (boolean3 != this->open) {
 this->playDoorSound(chr.getEmitter(), this->open ? "Open" : "Close");
 }
 }
 } else if (this->isObstructed()) {
 if (chr != nullptr) {
 this->playDoorSound(chr.getEmitter(), "Blocked");
 chr.setHaloNote(Translator.getText("IGUI_PlayerText_DoorBlocked"), 255, 255, 255, 256.0F);
 }
 } else {
 this->Locked = false;
 this->setLockedByKey(false);
 if (chr instanceof IsoPlayer) {
 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 LosUtil.cachecleared[int0] = true;
 }

 IsoGridSquare.setRecalcLightTime(-1);
 }

 this->open = !this->open;
 WeatherFxMask.forceMaskUpdateAll();
 this->sprite = this->closedSprite;
 if (this->open) {
 if (chr != nullptr) {
 this->playDoorSound(chr.getEmitter(), "Open");
 }

 this->sprite = this->openSprite;
 } else if (chr != nullptr) {
 this->playDoorSound(chr.getEmitter(), "Close");
 }

 this->square.RecalcProperties();
 this->syncIsoObject(false, (byte)(this->open ? 1 : 0), nullptr, nullptr);
 PolygonalMap2.instance.squareChanged(this->square);
 LuaEventManager.triggerEvent("OnContainerUpdate");
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
 b.putByte((byte)0);
 b.putBoolean(this->open);
 b.putBoolean(this->Locked);
 b.putBoolean(this->lockedByKey);
 }

 void syncIsoObject(bool bRemote, uint8_t val, UdpConnection source, ByteBuffer bb) {
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
 bool boolean0 = bb != nullptr && bb.get() == 1;
 bool boolean1 = bb != nullptr && bb.get() == 1;
 bool boolean2 = bb != nullptr && bb.get() == 1;
 short short0 = -1;
 if ((GameServer.bServer || GameClient.bClient) && bb != nullptr) {
 short0 = bb.getShort();
 }

 if (GameClient.bClient && !bRemote) {
 short0 = IsoPlayer.getInstance().getOnlineID();
 ByteBufferWriter byteBufferWriter0 = GameClient.connection.startPacket();
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

 if (getDoubleDoorIndex(this) != -1) {
 if (boolean0 != this->open) {
 toggleDoubleDoor(this, false);
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
 for (UdpConnection udpConnection1 : GameServer.udpEngine.connections) {
 if (source != nullptr && udpConnection1.getConnectedGUID() != source.getConnectedGUID() || source.empty()) {
 ByteBufferWriter byteBufferWriter2 = udpConnection1.startPacket();
 PacketTypes.PacketType.SyncIsoObject.doPacket(byteBufferWriter2);
 this->syncIsoObjectSend(byteBufferWriter2);
 byteBufferWriter2.putShort(short0);
 PacketTypes.PacketType.SyncIsoObject.send(udpConnection1);
 }
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
 WeatherFxMask.forceMaskUpdateAll();
 }
 }

 void ToggleDoor(IsoGameCharacter chr) {
 this->ToggleDoorActual(chr);
 }

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

 void Damage(int int0) {
 this->DirtySlice();
 this->Health -= int0;
 }

 IsoBarricade getBarricadeOnSameSquare() {
 return IsoBarricade.GetBarricadeOnSquare(this->square, this->north ? IsoDirections.N : IsoDirections.W);
 }

 IsoBarricade getBarricadeOnOppositeSquare() {
 return IsoBarricade.GetBarricadeOnSquare(this->getOppositeSquare(), this->north ? IsoDirections.S : IsoDirections.E);
 }

 bool isBarricaded() {
 IsoBarricade barricade = this->getBarricadeOnSameSquare();
 if (barricade.empty()) {
 barricade = this->getBarricadeOnOppositeSquare();
 }

 return barricade != nullptr;
 }

 bool isBarricadeAllowed() {
 return this->getSprite() != nullptr && !this->getSprite().getProperties().Is("DoubleDoor") && !this->getSprite().getProperties().Is("GarageDoor");
 }

 IsoBarricade getBarricadeForCharacter(IsoGameCharacter chr) {
 return IsoBarricade.GetBarricadeForCharacter(this, chr);
 }

 IsoBarricade getBarricadeOppositeCharacter(IsoGameCharacter chr) {
 return IsoBarricade.GetBarricadeOppositeCharacter(this, chr);
 }

 bool isLocked() {
 return this->Locked;
 }

 void setLocked(bool bLocked) {
 this->Locked = bLocked;
 }

 bool getNorth() {
 return this->north;
 }

 Vector2 getFacingPosition(Vector2 pos) {
 if (this->square.empty()) {
 return pos.set(0.0F, 0.0F);
 } else {
 return this->north ? pos.set(this->getX() + 0.5F, this->getY()) : pos.set(this->getX(), this->getY() + 0.5F);
 }
 }

 Vector2 getFacingPositionAlt(Vector2 pos) {
 if (this->square.empty()) {
 return pos.set(0.0F, 0.0F);
 } else {
 switch (this->getSpriteEdge(false) {
 case N:
 return pos.set(this->getX() + 0.5F, this->getY());
 case S:
 return pos.set(this->getX() + 0.5F, this->getY() + 1.0F);
 case W:
 return pos.set(this->getX(), this->getY() + 0.5F);
 case E:
 return pos.set(this->getX() + 1.0F, this->getY() + 0.5F);
 default:
 throw std::make_unique<IllegalStateException>();
 }
 }
 }

 void setIsLocked(bool lock) {
 this->Locked = lock;
 }

 IsoSprite getOpenSprite() {
 return this->openSprite;
 }

 void setOpenSprite(IsoSprite sprite) {
 this->openSprite = sprite;
 }

 int getKeyId() {
 return this->keyId;
 }

 void syncDoorKey() {
 ByteBufferWriter byteBufferWriter = GameClient.connection.startPacket();
 PacketTypes.PacketType.SyncDoorKey.doPacket(byteBufferWriter);
 byteBufferWriter.putInt(this->square.getX());
 byteBufferWriter.putInt(this->square.getY());
 byteBufferWriter.putInt(this->square.getZ());
 uint8_t byte0 = (byte)this->square.getObjects().indexOf(this);
 if (byte0 == -1) {
 System.out.println("ERROR: Door not found on square " + this->square.getX() + ", " + this->square.getY() + ", " + this->square.getZ());
 GameClient.connection.cancelPacket();
 } else {
 byteBufferWriter.putByte(byte0);
 byteBufferWriter.putInt(this->getKeyId());
 PacketTypes.PacketType.SyncDoorKey.send(GameClient.connection);
 }
 }

 void setKeyId(int keyId) {
 if (this->keyId != keyId && GameClient.bClient) {
 this->keyId = keyId;
 this->syncDoorKey();
 } else {
 this->keyId = keyId;
 }
 }

 bool isLockedByKey() {
 return this->lockedByKey;
 }

 void setLockedByKey(bool _lockedByKey) {
 bool boolean0 = _lockedByKey != this->lockedByKey;
 this->lockedByKey = _lockedByKey;
 this->Locked = _lockedByKey;
 if (!GameServer.bServer && boolean0) {
 if (_lockedByKey) {
 this->syncIsoObject(false, (byte)3, nullptr, nullptr);
 } else {
 this->syncIsoObject(false, (byte)4, nullptr, nullptr);
 }
 }
 }

 bool haveKey() {
 return this->haveKey;
 }

 void setHaveKey(bool _haveKey) {
 this->haveKey = _haveKey;
 if (!GameServer.bServer) {
 if (_haveKey) {
 this->syncIsoObject(false, (byte)-1, nullptr, nullptr);
 } else {
 this->syncIsoObject(false, (byte)-2, nullptr, nullptr);
 }
 }
 }

 IsoGridSquare getOppositeSquare() {
 return this->getNorth()
 ? this->getCell().getGridSquare((double)this->getX(), (double)(this->getY() - 1.0F), (double)this->getZ())
 : this->getCell().getGridSquare((double)(this->getX() - 1.0F), (double)this->getY(), (double)this->getZ());
 }

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
 if (!square1.isWallTo(_square2)
 && !square1.isWindowTo(_square2)
 && !square1.hasDoorOnEdge(IsoDirections.E, false)
 && !_square2.hasDoorOnEdge(IsoDirections.W, false) {
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
 if (!square3.isWallTo(_square2)
 && !square3.isWindowTo(_square2)
 && !square3.hasDoorOnEdge(IsoDirections.W, false)
 && !_square2.hasDoorOnEdge(IsoDirections.E, false) {
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
 if (!square4.isWallTo(square0)
 && !square4.isWindowTo(square0)
 && !square4.hasDoorOnEdge(IsoDirections.E, false)
 && !square0.hasDoorOnEdge(IsoDirections.W, false) {
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
 if (!square5.isWallTo(square0)
 && !square5.isWindowTo(square0)
 && !square5.hasDoorOnEdge(IsoDirections.W, false)
 && !square0.hasDoorOnEdge(IsoDirections.E, false) {
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
 if (!square4.isWallTo(square0)
 && !square4.isWindowTo(square0)
 && !square4.hasDoorOnEdge(IsoDirections.E, false)
 && !square0.hasDoorOnEdge(IsoDirections.W, false) {
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
 if (!square5.isWallTo(square0)
 && !square5.isWindowTo(square0)
 && !square5.hasDoorOnEdge(IsoDirections.W, false)
 && !square0.hasDoorOnEdge(IsoDirections.E, false) {
 if (boolean0 && square0.hasOpenDoorOnEdge(IsoDirections.S) {
 return false;
 }

 return true;
 }

 return false;
 }

 if (square2 == square6) {
 if (!square6.isWallTo(square7)
 && !square6.isWindowTo(square7)
 && !square6.hasDoorOnEdge(IsoDirections.E, false)
 && !square7.hasDoorOnEdge(IsoDirections.W, false) {
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
 if (!square8.isWallTo(square7)
 && !square8.isWindowTo(square7)
 && !square8.hasDoorOnEdge(IsoDirections.W, false)
 && !square7.hasDoorOnEdge(IsoDirections.E, false) {
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
 if (!square1.isWallTo(square4)
 && !square1.isWindowTo(square4)
 && !square1.hasDoorOnEdge(IsoDirections.S, false)
 && !square4.hasDoorOnEdge(IsoDirections.N, false) {
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
 if (!square6.isWallTo(square4)
 && !square6.isWindowTo(square4)
 && !square6.hasDoorOnEdge(IsoDirections.N, false)
 && !square4.hasDoorOnEdge(IsoDirections.S, false) {
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
 if (!_square2.isWallTo(square0)
 && !_square2.isWindowTo(square0)
 && !_square2.hasDoorOnEdge(IsoDirections.S, false)
 && !square0.hasDoorOnEdge(IsoDirections.N, false) {
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
 if (!square7.isWallTo(square0)
 && !square7.isWindowTo(square0)
 && !square7.hasDoorOnEdge(IsoDirections.N, false)
 && !square0.hasDoorOnEdge(IsoDirections.S, false) {
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
 if (!_square2.isWallTo(square0)
 && !_square2.isWindowTo(square0)
 && !_square2.hasDoorOnEdge(IsoDirections.S, false)
 && !square0.hasDoorOnEdge(IsoDirections.N, false) {
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
 if (!square7.isWallTo(square0)
 && !square7.isWindowTo(square0)
 && !square7.hasDoorOnEdge(IsoDirections.N, false)
 && !square0.hasDoorOnEdge(IsoDirections.S, false) {
 if (boolean0 && square0.hasOpenDoorOnEdge(IsoDirections.E) {
 return false;
 }

 return true;
 }

 return false;
 }

 if (square2 == square3) {
 if (!square3.isWallTo(square5)
 && !square3.isWindowTo(square5)
 && !square3.hasDoorOnEdge(IsoDirections.S, false)
 && !square4.hasDoorOnEdge(IsoDirections.N, false) {
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
 if (!square8.isWallTo(square5)
 && !square8.isWindowTo(square5)
 && !square8.hasDoorOnEdge(IsoDirections.N, false)
 && !square5.hasDoorOnEdge(IsoDirections.S, false) {
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

 int checkKeyId() {
 if (this->getKeyId() != -1) {
 return this->getKeyId();
 } else {
 IsoGridSquare square0 = this->getSquare();
 IsoGridSquare square1 = this->getOppositeSquare();
 if (square0 != nullptr && square1 != nullptr) {
 BuildingDef buildingDef0 = square0.getBuilding() == nullptr ? nullptr : square0.getBuilding().getDef();
 BuildingDef buildingDef1 = square1.getBuilding() == nullptr ? nullptr : square1.getBuilding().getDef();
 if (buildingDef0.empty() && buildingDef1 != nullptr) {
 this->setKeyId(buildingDef1.getKeyId());
 } else if (buildingDef0 != nullptr && buildingDef1.empty()) {
 this->setKeyId(buildingDef0.getKeyId());
 } else if (this->getProperties().Is("forceLocked") && buildingDef0 != nullptr) {
 this->setKeyId(buildingDef0.getKeyId());
 }

 if (this->Locked && !this->lockedByKey && this->getKeyId() != -1) {
 this->lockedByKey = true;
 }

 return this->getKeyId();
 } else {
 return -1;
 }
 }
 }

 void setHealth(int _Health) {
 this->Health = _Health;
 }

 void initCurtainSprites() {
 if (this->curtainN.empty()) {
 this->curtainW = IsoSprite.CreateSprite(IsoSpriteManager.instance);
 this->curtainW.LoadFramesNoDirPageSimple("fixtures_windows_curtains_01_16");
 this->curtainW.def.setScale(0.8F, 0.8F);
 this->curtainWopen = IsoSprite.CreateSprite(IsoSpriteManager.instance);
 this->curtainWopen.LoadFramesNoDirPageSimple("fixtures_windows_curtains_01_20");
 this->curtainWopen.def.setScale(0.8F, 0.8F);
 this->curtainE = IsoSprite.CreateSprite(IsoSpriteManager.instance);
 this->curtainE.LoadFramesNoDirPageSimple("fixtures_windows_curtains_01_17");
 this->curtainE.def.setScale(0.8F, 0.8F);
 this->curtainEopen = IsoSprite.CreateSprite(IsoSpriteManager.instance);
 this->curtainEopen.LoadFramesNoDirPageSimple("fixtures_windows_curtains_01_21");
 this->curtainEopen.def.setScale(0.8F, 0.8F);
 this->curtainN = IsoSprite.CreateSprite(IsoSpriteManager.instance);
 this->curtainN.LoadFramesNoDirPageSimple("fixtures_windows_curtains_01_18");
 this->curtainN.def.setScale(0.8F, 0.8F);
 this->curtainNopen = IsoSprite.CreateSprite(IsoSpriteManager.instance);
 this->curtainNopen.LoadFramesNoDirPageSimple("fixtures_windows_curtains_01_22");
 this->curtainNopen.def.setScale(0.8F, 0.8F);
 this->curtainS = IsoSprite.CreateSprite(IsoSpriteManager.instance);
 this->curtainS.LoadFramesNoDirPageSimple("fixtures_windows_curtains_01_19");
 this->curtainS.def.setScale(0.8F, 0.8F);
 this->curtainSopen = IsoSprite.CreateSprite(IsoSpriteManager.instance);
 this->curtainSopen.LoadFramesNoDirPageSimple("fixtures_windows_curtains_01_23");
 this->curtainSopen.def.setScale(0.8F, 0.8F);
 }
 }

 IsoDoor HasCurtains() {
 return this->bHasCurtain ? this : nullptr;
 }

 bool isCurtainOpen() {
 return this->bHasCurtain && this->bCurtainOpen;
 }

 void setCurtainOpen(bool _open) {
 if (this->bHasCurtain) {
 this->bCurtainOpen = _open;
 if (!GameServer.bServer) {
 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 LosUtil.cachecleared[int0] = true;
 }

 GameTime.instance.lightSourceUpdate = 100.0F;
 IsoGridSquare.setRecalcLightTime(-1);
 if (this->square != nullptr) {
 this->square.RecalcProperties();
 this->square.RecalcAllWithNeighbours(true);
 }
 }
 }
 }

 void transmitSetCurtainOpen(bool _open) {
 if (this->bHasCurtain) {
 if (GameServer.bServer) {
 this->sendObjectChange("setCurtainOpen", new Object[]{"open", _open});
 }

 if (GameClient.bClient) {
 GameClient.instance
 .sendClientCommandV(
 nullptr,
 "object",
 "openCloseCurtain",
 "x",
 this->getX(),
 "y",
 this->getY(),
 "z",
 this->getZ(),
 "index",
 this->getObjectIndex(),
 "open",
 !this->bCurtainOpen
 );
 }
 }
 }

 void toggleCurtain() {
 if (this->bHasCurtain) {
 if (GameClient.bClient) {
 this->transmitSetCurtainOpen(!this->isCurtainOpen());
 } else {
 this->setCurtainOpen(!this->isCurtainOpen());
 if (GameServer.bServer) {
 this->transmitSetCurtainOpen(this->isCurtainOpen());
 }
 }
 }
 }

 void addSheet(IsoGameCharacter chr) {
 if (!this->bHasCurtain && chr != nullptr && chr.getCurrentSquare() != nullptr) {
 IsoGridSquare square0 = chr.getCurrentSquare();
 IsoGridSquare square1 = this->getSquare();

 this->addSheet(switch (this->getSpriteEdge(false) {
 case N -> this->north == square0.getY() >= square1.getY();
 case S -> square0.getY() > square1.getY();
 case W -> this->north == square0.getX() < square1.getX();
 case E -> square0.getX() > square1.getX();
 default -> throw std::make_unique<IllegalStateException>();
 }, chr);
 }
 }

 void addSheet(bool inside, IsoGameCharacter chr) {
 if (!this->bHasCurtain) {
 this->bHasCurtain = true;
 this->bCurtainInside = inside;
 this->bCurtainOpen = true;
 if (GameServer.bServer) {
 this->sendObjectChange("addSheet", new Object[]{"inside", inside});
 if (chr != nullptr) {
 chr.sendObjectChange("removeOneOf", new Object[]{"type", "Sheet"});
 }
 } else if (chr != nullptr) {
 chr.getInventory().RemoveOneOf("Sheet");

 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 LosUtil.cachecleared[int0] = true;
 }

 GameTime.instance.lightSourceUpdate = 100.0F;
 IsoGridSquare.setRecalcLightTime(-1);
 if (this->square != nullptr) {
 this->square.RecalcProperties();
 }
 }
 }
 }

 void removeSheet(IsoGameCharacter chr) {
 if (this->bHasCurtain) {
 this->bHasCurtain = false;
 if (GameServer.bServer) {
 this->sendObjectChange("removeSheet");
 if (chr != nullptr) {
 chr.sendObjectChange("addItemOfType", new Object[]{"type", "Base.Sheet"});
 }
 } else if (chr != nullptr) {
 chr.getInventory().AddItem("Base.Sheet");

 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 LosUtil.cachecleared[int0] = true;
 }

 GameTime.instance.lightSourceUpdate = 100.0F;
 IsoGridSquare.setRecalcLightTime(-1);
 if (this->square != nullptr) {
 this->square.RecalcProperties();
 }
 }
 }
 }

 /**
 * Returns the square the player should stand on to add a sheet.
 */
 IsoGridSquare getAddSheetSquare(IsoGameCharacter chr) {
 if (chr != nullptr && chr.getCurrentSquare() != nullptr) {
 IsoGridSquare square0 = chr.getCurrentSquare();
 IsoGridSquare square1 = this->getSquare();
 switch (this->getSpriteEdge(false) {
 case N:
 return square0.getY() >= square1.getY() ? square1 : this->getCell().getGridSquare(square1.x, square1.y - 1, square1.z);
 case S:
 return square0.getY() <= square1.getY() ? square1 : this->getCell().getGridSquare(square1.x, square1.y + 1, square1.z);
 case W:
 return square0.getX() >= square1.getX() ? square1 : this->getCell().getGridSquare(square1.x - 1, square1.y, square1.z);
 case E:
 return square0.getX() <= square1.getX() ? square1 : this->getCell().getGridSquare(square1.x + 1, square1.y, square1.z);
 default:
 throw std::make_unique<IllegalStateException>();
 }
 } else {
 return nullptr;
 }
 }

 /**
 * Returns the square the player should stand on to open/close/remove a sheet.
 */
 IsoGridSquare getSheetSquare() {
 if (!this->bHasCurtain) {
 return nullptr;
 } else {
 switch (this->getSpriteEdge(false) {
 case N:
 if (this->open) {
 return this->bCurtainInside
 ? this->getCell().getGridSquare((double)this->getX(), (double)(this->getY() - 1.0F), (double)this->getZ())
 : this->getSquare();
 }

 return this->bCurtainInside
 ? this->getSquare()
 : this->getCell().getGridSquare((double)this->getX(), (double)(this->getY() - 1.0F), (double)this->getZ());
 case S:
 return this->bCurtainInside
 ? this->getCell().getGridSquare((double)this->getX(), (double)(this->getY() + 1.0F), (double)this->getZ())
 : this->getSquare();
 case W:
 if (this->open) {
 return this->bCurtainInside
 ? this->getCell().getGridSquare((double)(this->getX() - 1.0F), (double)this->getY(), (double)this->getZ())
 : this->getSquare();
 }

 return this->bCurtainInside
 ? this->getSquare()
 : this->getCell().getGridSquare((double)(this->getX() - 1.0F), (double)this->getY(), (double)this->getZ());
 case E:
 return this->bCurtainInside
 ? this->getCell().getGridSquare((double)(this->getX() + 1.0F), (double)this->getY(), (double)this->getZ())
 : this->getSquare();
 default:
 throw std::make_unique<IllegalStateException>();
 }
 }
 }

 int getHealth() {
 return this->Health;
 }

 int getMaxHealth() {
 return this->MaxHealth;
 }

 bool isFacingSheet(IsoGameCharacter chr) {
 if (this->bHasCurtain && chr != nullptr && chr.getCurrentSquare() == this->getSheetSquare()) {
 IsoDirections directions0;
 if (this->bCurtainInside) {
 if (this->open) {
 if (this->north) {
 directions0 = IsoDirections.E;
 } else {
 directions0 = IsoDirections.S;
 }
 } else if (this->north) {
 directions0 = IsoDirections.N;
 } else {
 directions0 = IsoDirections.W;
 }
 } else if (this->open) {
 if (this->north) {
 directions0 = IsoDirections.W;
 } else {
 directions0 = IsoDirections.N;
 }
 } else if (this->north) {
 directions0 = IsoDirections.S;
 } else {
 directions0 = IsoDirections.E;
 }

 IsoDirections directions1 = this->getSpriteEdge(false);
 if (directions1 == IsoDirections.E) {
 directions0 = this->bCurtainInside ? IsoDirections.W : IsoDirections.E;
 }

 if (directions1 == IsoDirections.S) {
 directions0 = this->bCurtainInside ? IsoDirections.N : IsoDirections.S;
 }

 return chr.getDir() == directions0 || chr.getDir() == IsoDirections.RotLeft(directions0) || chr.getDir() == IsoDirections.RotRight(directions0);
 } else {
 return false;
 }
 }

 void saveChange(const std::string& change, KahluaTable tbl, ByteBuffer bb) {
 if ("addSheet" == change) {
 if (tbl != nullptr && tbl.rawget("inside") instanceof Boolean) {
 bb.put((byte)(tbl.rawget("inside") ? 1 : 0);
 }
 } else if (!"removeSheet" == change) {
 if ("setCurtainOpen" == change) {
 if (tbl != nullptr && tbl.rawget("open") instanceof Boolean) {
 bb.put((byte)(tbl.rawget("open") ? 1 : 0);
 }
 } else {
 super.saveChange(change, tbl, bb);
 }
 }
 }

 void loadChange(const std::string& change, ByteBuffer bb) {
 if ("addSheet" == change) {
 this->addSheet(bb.get() == 1, nullptr);
 } else if ("removeSheet" == change) {
 this->removeSheet(nullptr);
 } else if ("setCurtainOpen" == change) {
 this->setCurtainOpen(bb.get() == 1);
 } else {
 super.loadChange(change, bb);
 }
 }

 void addRandomBarricades() {
 IsoGridSquare square = this->square.getRoom() == nullptr ? this->square : this->getOppositeSquare();
 if (square != nullptr && square.getRoom() == nullptr) {
 bool boolean0 = square != this->square;
 IsoBarricade barricade = IsoBarricade.AddBarricadeToObject(this, boolean0);
 if (barricade != nullptr) {
 int int0 = Rand.Next(1, 4);

 for (int int1 = 0; int1 < int0; int1++) {
 barricade.addPlank(nullptr, nullptr);
 }
 }
 }
 }

 bool isObstructed() {
 return isDoorObstructed();
 }

 static bool isDoorObstructed(IsoObject object) {
 IsoDoor door = object instanceof IsoDoor ? (IsoDoor)object : nullptr;
 IsoThumpable thumpable = object instanceof IsoThumpable ? (IsoThumpable)object : nullptr;
 if (door.empty() && thumpable.empty()) {
 return false;
 } else {
 IsoGridSquare square = object.getSquare();
 if (square.empty()) {
 return false;
 } else if (!square.isSolid() && !square.isSolidTrans() && !square.Has(IsoObjectType.tree) {
 int int0 = (square.x - 1) / 10;
 int int1 = (square.y - 1) / 10;
 int int2 = (int)Math.ceil((square.x + 1.0F) / 10.0F);
 int int3 = (int)Math.ceil((square.y + 1.0F) / 10.0F);

 for (int int4 = int1; int4 <= int3; int4++) {
 for (int int5 = int0; int5 <= int2; int5++) {
 IsoChunk chunk = GameServer.bServer ? ServerMap.instance.getChunk(int5, int4) : IsoWorld.instance.CurrentCell.getChunk(int5, int4);
 if (chunk != nullptr) {
 for (int int6 = 0; int6 < chunk.vehicles.size(); int6++) {
 BaseVehicle vehicle = chunk.vehicles.get(int6);
 if (vehicle.isIntersectingSquareWithShadow(square.x, square.y, square.z) {
 return true;
 }
 }
 }
 }
 }

 return false;
 } else {
 return true;
 }
 }
 }

 static void toggleDoubleDoor(IsoObject oneOfFour, bool doSync) {
 int int0 = getDoubleDoorIndex(oneOfFour);
 if (int0 != -1) {
 IsoDoor door = oneOfFour instanceof IsoDoor ? (IsoDoor)oneOfFour : nullptr;
 IsoThumpable thumpable = oneOfFour instanceof IsoThumpable ? (IsoThumpable)oneOfFour : nullptr;
 if (door != nullptr) {
 ;
 }

 bool boolean0 = door.empty() ? thumpable.open : door.open;
 IsoObject object0 = getDoubleDoorObject(oneOfFour, 1);
 IsoObject object1 = getDoubleDoorObject(oneOfFour, 2);
 IsoObject object2 = getDoubleDoorObject(oneOfFour, 3);
 IsoObject object3 = getDoubleDoorObject(oneOfFour, 4);
 if (object0 != nullptr) {
 toggleDoubleDoorObject(object0);
 }

 if (object1 != nullptr) {
 toggleDoubleDoorObject(object1);
 }

 if (object2 != nullptr) {
 toggleDoubleDoorObject(object2);
 }

 if (object3 != nullptr) {
 toggleDoubleDoorObject(object3);
 }

 LuaEventManager.triggerEvent("OnContainerUpdate");
 if (doSync) {
 if (object0 != nullptr) {
 object0.syncIsoObject(false, (byte)(boolean0 ? 1 : 0), nullptr, nullptr);
 } else if (object3 != nullptr) {
 object3.syncIsoObject(false, (byte)(boolean0 ? 1 : 0), nullptr, nullptr);
 }
 }
 }
 }

 static void toggleDoubleDoorObject(IsoObject object) {
 int int0 = getDoubleDoorIndex(object);
 if (int0 != -1) {
 IsoDoor door0 = object instanceof IsoDoor ? (IsoDoor)object : nullptr;
 IsoThumpable thumpable0 = object instanceof IsoThumpable ? (IsoThumpable)object : nullptr;
 bool boolean0 = door0.empty() ? thumpable0.north : door0.north;
 bool boolean1 = door0.empty() ? thumpable0.open : door0.open;
 int int1 = -1;
 if (door0 != nullptr) {
 door0.open = !boolean1;
 door0.setLockedByKey(false);
 int1 = door0.checkKeyId();
 }

 if (thumpable0 != nullptr) {
 thumpable0.open = !boolean1;
 thumpable0.setLockedByKey(false);
 int1 = thumpable0.getKeyId();
 }

 IsoSprite sprite = object.getSprite();
 int int2 = boolean0 ? DoubleDoorNorthSpriteOffset[int0 - 1] : DoubleDoorWestSpriteOffset[int0 - 1];
 if (boolean1) {
 int2 *= -1;
 }

 object.sprite = IsoSprite.getSprite(IsoSpriteManager.instance, sprite.getName(), int2);
 object.getSquare().RecalcAllWithNeighbours(true);
 if (int0 != 2 && int0 != 3) {
 PolygonalMap2.instance.squareChanged(object.getSquare());
 } else {
 IsoGridSquare square = object.getSquare();
 int[] ints0;
 int[] ints1;
 int[] ints2;
 int[] ints3;
 if (boolean0) {
 if (boolean1) {
 ints0 = DoubleDoorNorthOpenXOffset;
 ints1 = DoubleDoorNorthOpenYOffset;
 ints2 = DoubleDoorNorthClosedXOffset;
 ints3 = DoubleDoorNorthClosedYOffset;
 } else {
 ints0 = DoubleDoorNorthClosedXOffset;
 ints1 = DoubleDoorNorthClosedYOffset;
 ints2 = DoubleDoorNorthOpenXOffset;
 ints3 = DoubleDoorNorthOpenYOffset;
 }
 } else if (boolean1) {
 ints0 = DoubleDoorWestOpenXOffset;
 ints1 = DoubleDoorWestOpenYOffset;
 ints2 = DoubleDoorWestClosedXOffset;
 ints3 = DoubleDoorWestClosedYOffset;
 } else {
 ints0 = DoubleDoorWestClosedXOffset;
 ints1 = DoubleDoorWestClosedYOffset;
 ints2 = DoubleDoorWestOpenXOffset;
 ints3 = DoubleDoorWestOpenYOffset;
 }

 int int3 = square.getX() - ints0[int0 - 1];
 int int4 = square.getY() - ints1[int0 - 1];
 int int5 = int3 + ints2[int0 - 1];
 int int6 = int4 + ints3[int0 - 1];
 square.RemoveTileObject(object);
 PolygonalMap2.instance.squareChanged(square);
 square = IsoWorld.instance.CurrentCell.getGridSquare(int5, int6, square.getZ());
 if (square.empty()) {
 return;
 }

 if (thumpable0 != nullptr) {
 IsoThumpable thumpable1 = new IsoThumpable(square.getCell(), square, object.getSprite().getName(), boolean0, thumpable0.getTable());
 thumpable1.setModData(thumpable0.getModData());
 thumpable1.setCanBeLockByPadlock(thumpable0.canBeLockByPadlock());
 thumpable1.setCanBePlastered(thumpable0.canBePlastered());
 thumpable1.setIsHoppable(thumpable0.isHoppable());
 thumpable1.setIsDismantable(thumpable0.isDismantable());
 thumpable1.setName(thumpable0.getName());
 thumpable1.setIsDoor(true);
 thumpable1.setIsThumpable(thumpable0.isThumpable());
 thumpable1.setThumpDmg(thumpable0.getThumpDmg());
 thumpable1.setThumpSound(thumpable0.getThumpSound());
 thumpable1.open = !boolean1;
 thumpable1.keyId = int1;
 square.AddSpecialObject(thumpable1);
 } else {
 IsoDoor door1 = new IsoDoor(square.getCell(), square, object.getSprite().getName(), boolean0);
 door1.open = !boolean1;
 door1.keyId = int1;
 square.getObjects().add(door1);
 square.getSpecialObjects().add(door1);
 square.RecalcProperties();
 }

 if (!GameClient.bClient) {
 square.restackSheetRope();
 }

 PolygonalMap2.instance.squareChanged(square);
 }
 }
 }

 static int getDoubleDoorIndex(IsoObject oneOfFour) {
 if (oneOfFour != nullptr && oneOfFour.getSquare() != nullptr) {
 PropertyContainer propertyContainer = oneOfFour.getProperties();
 if (propertyContainer != nullptr && propertyContainer.Is("DoubleDoor")) {
 int int0 = Integer.parseInt(propertyContainer.Val("DoubleDoor"));
 if (int0 >= 1 && int0 <= 8) {
 IsoDoor door = oneOfFour instanceof IsoDoor ? (IsoDoor)oneOfFour : nullptr;
 IsoThumpable thumpable = oneOfFour instanceof IsoThumpable ? (IsoThumpable)oneOfFour : nullptr;
 if (door.empty() && thumpable.empty()) {
 return -1;
 } else {
 bool boolean0 = door.empty() ? thumpable.open : door.open;
 if (!boolean0) {
 return int0;
 } else {
 return int0 >= 5 ? int0 - 4 : -1;
 }
 }
 } else {
 return -1;
 }
 } else {
 return -1;
 }
 } else {
 return -1;
 }
 }

 static IsoObject getDoubleDoorObject(IsoObject oneOfFour, int index) {
 int int0 = getDoubleDoorIndex(oneOfFour);
 if (int0 == -1) {
 return nullptr;
 } else {
 IsoDoor door = oneOfFour instanceof IsoDoor ? (IsoDoor)oneOfFour : nullptr;
 IsoThumpable thumpable = oneOfFour instanceof IsoThumpable ? (IsoThumpable)oneOfFour : nullptr;
 bool boolean0 = door.empty() ? thumpable.north : door.north;
 bool boolean1 = door.empty() ? thumpable.open : door.open;
 IsoGridSquare square = oneOfFour.getSquare();
 int[] ints0;
 int[] ints1;
 if (boolean0) {
 if (boolean1) {
 ints0 = DoubleDoorNorthOpenXOffset;
 ints1 = DoubleDoorNorthOpenYOffset;
 } else {
 ints0 = DoubleDoorNorthClosedXOffset;
 ints1 = DoubleDoorNorthClosedYOffset;
 }
 } else if (boolean1) {
 ints0 = DoubleDoorWestOpenXOffset;
 ints1 = DoubleDoorWestOpenYOffset;
 } else {
 ints0 = DoubleDoorWestClosedXOffset;
 ints1 = DoubleDoorWestClosedYOffset;
 }

 int int1 = square.getX() - ints0[int0 - 1];
 int int2 = square.getY() - ints1[int0 - 1];
 int int3 = int1 + ints0[index - 1];
 int int4 = int2 + ints1[index - 1];
 square = IsoWorld.instance.CurrentCell.getGridSquare(int3, int4, square.getZ());
 if (square.empty()) {
 return nullptr;
 } else {
 std::vector arrayList = square.getSpecialObjects();
 if (door != nullptr) {
 for (int int5 = 0; int5 < arrayList.size(); int5++) {
 IsoObject object0 = (IsoObject)arrayList.get(int5);
 if (object0 instanceof IsoDoor && ((IsoDoor)object0).north == boolean0 && getDoubleDoorIndex(object0) == index) {
 return object0;
 }
 }
 }

 if (thumpable != nullptr) {
 for (int int6 = 0; int6 < arrayList.size(); int6++) {
 IsoObject object1 = (IsoObject)arrayList.get(int6);
 if (object1 instanceof IsoThumpable && ((IsoThumpable)object1).north == boolean0 && getDoubleDoorIndex(object1) == index) {
 return object1;
 }
 }
 }

 return nullptr;
 }
 }
 }

 static bool isDoubleDoorObstructed(IsoObject oneOfFour) {
 int int0 = getDoubleDoorIndex(oneOfFour);
 if (int0 == -1) {
 return false;
 } else {
 IsoDoor door = oneOfFour instanceof IsoDoor ? (IsoDoor)oneOfFour : nullptr;
 IsoThumpable thumpable = oneOfFour instanceof IsoThumpable ? (IsoThumpable)oneOfFour : nullptr;
 bool boolean0 = door.empty() ? thumpable.north : door.north;
 bool boolean1 = door.empty() ? thumpable.open : door.open;
 IsoGridSquare square0 = oneOfFour.getSquare();
 int[] ints0;
 int[] ints1;
 if (boolean0) {
 if (boolean1) {
 ints0 = DoubleDoorNorthOpenXOffset;
 ints1 = DoubleDoorNorthOpenYOffset;
 } else {
 ints0 = DoubleDoorNorthClosedXOffset;
 ints1 = DoubleDoorNorthClosedYOffset;
 }
 } else if (boolean1) {
 ints0 = DoubleDoorWestOpenXOffset;
 ints1 = DoubleDoorWestOpenYOffset;
 } else {
 ints0 = DoubleDoorWestClosedXOffset;
 ints1 = DoubleDoorWestClosedYOffset;
 }

 int int1 = square0.getX() - ints0[int0 - 1];
 int int2 = square0.getY() - ints1[int0 - 1];
 int int3 = int1;
 int int4 = int2 + (boolean0 ? 0 : -3);
 int int5 = int1 + (boolean0 ? 4 : 2);
 int int6 = int4 + (boolean0 ? 2 : 4);
 int int7 = square0.getZ();

 for (int int8 = int4; int8 < int6; int8++) {
 for (int int9 = int3; int9 < int5; int9++) {
 IsoGridSquare square1 = IsoWorld.instance.CurrentCell.getGridSquare(int9, int8, int7);
 if (square1 != nullptr && (square1.isSolid() || square1.isSolidTrans() || square1.Has(IsoObjectType.tree) {
 return true;
 }
 }
 }

 if (boolean0) {
 if (hasSomething4x4(int1, int2, int1 + 1, int2 + 1, int7) {
 return true;
 }

 if (hasSomething4x4(int1 + 2, int2, int1 + 3, int2 + 1, int7) {
 return true;
 }
 } else {
 if (hasSomething4x4(int1, int2 - 1, int1 + 1, int2, int7) {
 return true;
 }

 if (hasSomething4x4(int1, int2 - 3, int1 + 1, int2 - 2, int7) {
 return true;
 }
 }

 int int10 = (int3 - 4) / 10;
 int int11 = (int4 - 4) / 10;
 int int12 = (int)Math.ceil((int5 + 4) / 10);
 int int13 = (int)Math.ceil((int6 + 4) / 10);

 for (int int14 = int11; int14 <= int13; int14++) {
 for (int int15 = int10; int15 <= int12; int15++) {
 IsoChunk chunk = GameServer.bServer ? ServerMap.instance.getChunk(int15, int14) : IsoWorld.instance.CurrentCell.getChunk(int15, int14);
 if (chunk != nullptr) {
 for (int int16 = 0; int16 < chunk.vehicles.size(); int16++) {
 BaseVehicle vehicle = chunk.vehicles.get(int16);

 for (int int17 = int4; int17 < int6; int17++) {
 for (int int18 = int3; int18 < int5; int18++) {
 if (vehicle.isIntersectingSquare(int18, int17, int7) {
 return true;
 }
 }
 }
 }
 }
 }
 }

 return false;
 }
 }

 static bool isSomethingTo(IsoGridSquare square1, IsoGridSquare square0) {
 if (square1 != nullptr && square0 != nullptr) {
 if (square0 != square1.getAdjacentSquare(IsoDirections.E)
 || !square1.hasDoorOnEdge(IsoDirections.E, false)
 && !square0.hasDoorOnEdge(IsoDirections.W, false)
 && !square0.getProperties().Is(IsoFlagType.DoorWallW) {
 if (square0 != square1.getAdjacentSquare(IsoDirections.SE)
 || !square1.hasDoorOnEdge(IsoDirections.E, false)
 && !square1.hasDoorOnEdge(IsoDirections.S, false)
 && !square0.hasDoorOnEdge(IsoDirections.W, false)
 && !square0.hasDoorOnEdge(IsoDirections.N, false)
 && !square0.getProperties().Is(IsoFlagType.DoorWallN)
 && !square0.getProperties().Is(IsoFlagType.DoorWallW) {
 return square0 != square1.getAdjacentSquare(IsoDirections.S)
 || !square1.hasDoorOnEdge(IsoDirections.S, false)
 && !square0.hasDoorOnEdge(IsoDirections.N, false)
 && !square0.getProperties().Is(IsoFlagType.DoorWallN)
 ? square1.isWallTo(square0) || square1.isWindowTo(square0)
 : true;
 } else {
 return true;
 }
 } else {
 return true;
 }
 } else {
 return false;
 }
 }

 static bool hasSomething4x4(int int0, int int1, int int3, int int4, int int2) {
 IsoGridSquare square0 = IsoWorld.instance.CurrentCell.getGridSquare(int0, int1, int2);
 IsoGridSquare square1 = IsoWorld.instance.CurrentCell.getGridSquare(int3, int1, int2);
 IsoGridSquare square2 = IsoWorld.instance.CurrentCell.getGridSquare(int3, int4, int2);
 IsoGridSquare square3 = IsoWorld.instance.CurrentCell.getGridSquare(int0, int4, int2);
 if (isSomethingTo(square0, square1) {
 return true;
 } else {
 return isSomethingTo();
 }
 }

 static bool destroyDoubleDoor(IsoObject oneOfFour) {
 int int0 = getDoubleDoorIndex(oneOfFour);
 if (int0 == -1) {
 return false;
 } else {
 if (int0 == 1 || int0 == 4) {
 IsoObject object = getDoubleDoorObject(oneOfFour, int0 == 1 ? 2 : 3);
 if (object instanceof IsoDoor) {
 ((IsoDoor)object).destroy();
 } else if (object instanceof IsoThumpable) {
 ((IsoThumpable)object).destroy();
 }
 }

 if (oneOfFour instanceof IsoDoor) {
 ((IsoDoor)oneOfFour).destroy();
 } else if (oneOfFour instanceof IsoThumpable) {
 ((IsoThumpable)oneOfFour).destroy();
 }

 LuaEventManager.triggerEvent("OnContainerUpdate");
 return true;
 }
 }

 static int getGarageDoorIndex(IsoObject oneOfThree) {
 if (oneOfThree != nullptr && oneOfThree.getSquare() != nullptr) {
 PropertyContainer propertyContainer = oneOfThree.getProperties();
 if (propertyContainer != nullptr && propertyContainer.Is("GarageDoor")) {
 int int0 = Integer.parseInt(propertyContainer.Val("GarageDoor"));
 if (int0 >= 1 && int0 <= 6) {
 IsoDoor door = oneOfThree instanceof IsoDoor ? (IsoDoor)oneOfThree : nullptr;
 IsoThumpable thumpable = oneOfThree instanceof IsoThumpable ? (IsoThumpable)oneOfThree : nullptr;
 if (door.empty() && thumpable.empty()) {
 return -1;
 } else {
 bool boolean0 = door.empty() ? thumpable.open : door.open;
 if (!boolean0) {
 return int0;
 } else {
 return int0 >= 4 ? int0 - 3 : -1;
 }
 }
 } else {
 return -1;
 }
 } else {
 return -1;
 }
 } else {
 return -1;
 }
 }

 static IsoObject getGarageDoorPrev(IsoObject oneOfThree) {
 int int0 = getGarageDoorIndex(oneOfThree);
 if (int0 == -1) {
 return nullptr;
 } else if (int0 == 1) {
 return nullptr;
 } else {
 IsoDoor door = oneOfThree instanceof IsoDoor ? (IsoDoor)oneOfThree : nullptr;
 IsoThumpable thumpable = oneOfThree instanceof IsoThumpable ? (IsoThumpable)oneOfThree : nullptr;
 bool boolean0 = door.empty() ? thumpable.north : door.north;
 IsoGridSquare square = oneOfThree.getSquare();
 int int1 = square.x - (boolean0 ? 1 : 0);
 int int2 = square.y + (boolean0 ? 0 : 1);
 square = IsoWorld.instance.CurrentCell.getGridSquare(int1, int2, square.getZ());
 if (square.empty()) {
 return nullptr;
 } else {
 std::vector arrayList = square.getSpecialObjects();
 if (door != nullptr) {
 for (int int3 = 0; int3 < arrayList.size(); int3++) {
 IsoObject object0 = (IsoObject)arrayList.get(int3);
 if (object0 instanceof IsoDoor && ((IsoDoor)object0).north == boolean0 && getGarageDoorIndex(object0) <= int0) {
 return object0;
 }
 }
 }

 if (thumpable != nullptr) {
 for (int int4 = 0; int4 < arrayList.size(); int4++) {
 IsoObject object1 = (IsoObject)arrayList.get(int4);
 if (object1 instanceof IsoThumpable && ((IsoThumpable)object1).north == boolean0 && getGarageDoorIndex(object1) <= int0) {
 return object1;
 }
 }
 }

 return nullptr;
 }
 }
 }

 static IsoObject getGarageDoorNext(IsoObject oneOfThree) {
 int int0 = getGarageDoorIndex(oneOfThree);
 if (int0 == -1) {
 return nullptr;
 } else if (int0 == 3) {
 return nullptr;
 } else {
 IsoDoor door = oneOfThree instanceof IsoDoor ? (IsoDoor)oneOfThree : nullptr;
 IsoThumpable thumpable = oneOfThree instanceof IsoThumpable ? (IsoThumpable)oneOfThree : nullptr;
 bool boolean0 = door.empty() ? thumpable.north : door.north;
 IsoGridSquare square = oneOfThree.getSquare();
 int int1 = square.x + (boolean0 ? 1 : 0);
 int int2 = square.y - (boolean0 ? 0 : 1);
 square = IsoWorld.instance.CurrentCell.getGridSquare(int1, int2, square.getZ());
 if (square.empty()) {
 return nullptr;
 } else {
 std::vector arrayList = square.getSpecialObjects();
 if (door != nullptr) {
 for (int int3 = 0; int3 < arrayList.size(); int3++) {
 IsoObject object0 = (IsoObject)arrayList.get(int3);
 if (object0 instanceof IsoDoor && ((IsoDoor)object0).north == boolean0 && getGarageDoorIndex(object0) >= int0) {
 return object0;
 }
 }
 }

 if (thumpable != nullptr) {
 for (int int4 = 0; int4 < arrayList.size(); int4++) {
 IsoObject object1 = (IsoObject)arrayList.get(int4);
 if (object1 instanceof IsoThumpable && ((IsoThumpable)object1).north == boolean0 && getGarageDoorIndex(object1) >= int0) {
 return object1;
 }
 }
 }

 return nullptr;
 }
 }
 }

 static IsoObject getGarageDoorFirst(IsoObject oneOfThree) {
 int int0 = getGarageDoorIndex(oneOfThree);
 if (int0 == -1) {
 return nullptr;
 } else if (int0 == 1) {
 return oneOfThree;
 } else {
 for (IsoObject object = getGarageDoorPrev(oneOfThree); object != nullptr; object = getGarageDoorPrev(object) {
 if (getGarageDoorIndex(object) == 1) {
 return object;
 }
 }

 return oneOfThree;
 }
 }

 static void toggleGarageDoorObject(IsoObject object) {
 int int0 = getGarageDoorIndex(object);
 if (int0 != -1) {
 IsoDoor door = object instanceof IsoDoor ? (IsoDoor)object : nullptr;
 IsoThumpable thumpable = object instanceof IsoThumpable ? (IsoThumpable)object : nullptr;
 bool boolean0 = door.empty() ? thumpable.open : door.open;
 if (door != nullptr) {
 door.open = !boolean0;
 door.setLockedByKey(false);
 door.sprite = door.open ? door.openSprite : door.closedSprite;
 }

 if (thumpable != nullptr) {
 thumpable.open = !boolean0;
 thumpable.setLockedByKey(false);
 thumpable.sprite = thumpable.open ? thumpable.openSprite : thumpable.closedSprite;
 }

 object.getSquare().RecalcAllWithNeighbours(true);
 object.syncIsoObject(false, (byte)(boolean0 ? 0 : 1), nullptr, nullptr);
 PolygonalMap2.instance.squareChanged(object.getSquare());
 }
 }

 static void toggleGarageDoor(IsoObject oneOfThree, bool doSync) {
 int int0 = getGarageDoorIndex(oneOfThree);
 if (int0 != -1) {
 toggleGarageDoorObject(oneOfThree);

 for (IsoObject object0 = getGarageDoorPrev(oneOfThree); object0 != nullptr; object0 = getGarageDoorPrev(object0) {
 toggleGarageDoorObject(object0);
 }

 for (IsoObject object1 = getGarageDoorNext(oneOfThree); object1 != nullptr; object1 = getGarageDoorNext(object1) {
 toggleGarageDoorObject(object1);
 }

 for (int int1 = 0; int1 < IsoPlayer.numPlayers; int1++) {
 LosUtil.cachecleared[int1] = true;
 }

 IsoGridSquare.setRecalcLightTime(-1);
 LuaEventManager.triggerEvent("OnContainerUpdate");
 }
 }

 static bool isGarageDoorObstructed(IsoObject object0) {
 int int0 = getGarageDoorIndex(object0);
 if (int0 == -1) {
 return false;
 } else {
 IsoDoor door = object0 instanceof IsoDoor ? (IsoDoor)object0 : nullptr;
 IsoThumpable thumpable = object0 instanceof IsoThumpable ? (IsoThumpable)object0 : nullptr;
 bool boolean0 = door.empty() ? thumpable.north : door.north;
 bool boolean1 = door.empty() ? thumpable.open : door.open;
 if (!boolean1) {
 return false;
 } else {
 int int1 = object0.square.x;
 int int2 = object0.square.y;
 int int3 = int1;
 int int4 = int2;
 if (boolean0) {
 for (IsoObject object1 = getGarageDoorPrev(object0); object1 != nullptr; object1 = getGarageDoorPrev(object1) {
 int1--;
 }

 for (IsoObject object2 = getGarageDoorNext(object0); object2 != nullptr; object2 = getGarageDoorNext(object2) {
 int3++;
 }
 } else {
 for (IsoObject object3 = getGarageDoorPrev(object0); object3 != nullptr; object3 = getGarageDoorPrev(object3) {
 int4++;
 }

 for (IsoObject object4 = getGarageDoorNext(object0); object4 != nullptr; object4 = getGarageDoorNext(object4) {
 int2--;
 }
 }

 int int5 = (int1 - 4) / 10;
 int int6 = (int2 - 4) / 10;
 int int7 = (int)Math.ceil((int3 + 4) / 10);
 int int8 = (int)Math.ceil((int4 + 4) / 10);
 int int9 = object0.square.z;

 for (int int10 = int6; int10 <= int8; int10++) {
 for (int int11 = int5; int11 <= int7; int11++) {
 IsoChunk chunk = GameServer.bServer ? ServerMap.instance.getChunk(int11, int10) : IsoWorld.instance.CurrentCell.getChunk(int11, int10);
 if (chunk != nullptr) {
 for (int int12 = 0; int12 < chunk.vehicles.size(); int12++) {
 BaseVehicle vehicle = chunk.vehicles.get(int12);

 for (int int13 = int2; int13 <= int4; int13++) {
 for (int int14 = int1; int14 <= int3; int14++) {
 if (vehicle.isIntersectingSquare(int14, int13, int9)
 && vehicle.isIntersectingSquare(int14 - (boolean0 ? 0 : 1), int13 - (boolean0 ? 1 : 0), int9) {
 return true;
 }
 }
 }
 }
 }
 }
 }

 return false;
 }
 }
 }

 static bool destroyGarageDoor(IsoObject oneOfThree) {
 int int0 = getGarageDoorIndex(oneOfThree);
 if (int0 == -1) {
 return false;
 } else {
 IsoObject object0 = getGarageDoorPrev(oneOfThree);

 while (object0 != nullptr) {
 IsoObject object1 = getGarageDoorPrev(object0);
 if (object0 instanceof IsoDoor) {
 ((IsoDoor)object0).destroy();
 } else if (object0 instanceof IsoThumpable) {
 ((IsoThumpable)object0).destroy();
 }

 object0 = object1;
 }

 IsoObject object2 = getGarageDoorNext(oneOfThree);

 while (object2 != nullptr) {
 IsoObject object3 = getGarageDoorNext(object2);
 if (object2 instanceof IsoDoor) {
 ((IsoDoor)object2).destroy();
 } else if (object2 instanceof IsoThumpable) {
 ((IsoThumpable)object2).destroy();
 }

 object2 = object3;
 }

 if (oneOfThree instanceof IsoDoor) {
 ((IsoDoor)oneOfThree).destroy();
 } else if (oneOfThree instanceof IsoThumpable) {
 ((IsoThumpable)oneOfThree).destroy();
 }

 LuaEventManager.triggerEvent("OnContainerUpdate");
 return true;
 }
 }

 IsoObject getRenderEffectMaster() {
 int int0 = getDoubleDoorIndex(this);
 if (int0 != -1) {
 IsoObject object0 = nullptr;
 if (int0 == 2) {
 object0 = getDoubleDoorObject(this, 1);
 } else if (int0 == 3) {
 object0 = getDoubleDoorObject(this, 4);
 }

 if (object0 != nullptr) {
 return object0;
 }
 } else {
 IsoObject object1 = getGarageDoorFirst(this);
 if (object1 != nullptr) {
 return object1;
 }
 }

 return this;
 }

 std::string getThumpSound() {
 std::string string = this->getSoundPrefix();
 switch (string) {
 case "GarageDoor":
 return "ZombieThumpGarageDoor";
 case "MetalDoor":
 case "MetalGate":
 case "PrisonMetalDoor":
 return "ZombieThumpMetal";
 case "SlidingGlassDoor":
 return "ZombieThumpWindow";
 default:
 return "ZombieThumpGeneric";
 }
 }

 std::string getSoundPrefix() {
 if (this->closedSprite.empty()) {
 return "WoodDoor";
 } else {
 PropertyContainer propertyContainer = this->closedSprite.getProperties();
 return propertyContainer.Is("DoorSound") ? propertyContainer.Val("DoorSound") : "WoodDoor";
 }
 }

 void playDoorSound(BaseCharacterSoundEmitter baseCharacterSoundEmitter, const std::string& string) {
 baseCharacterSoundEmitter.playSound(this->getSoundPrefix() + string, this);
 }

 public static enum DoorType {
 WeakWooden,
 StrongWooden;
 }
}
} // namespace objects
} // namespace iso
} // namespace zombie
