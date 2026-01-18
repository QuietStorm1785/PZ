#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoSurvivor.h"
#include "zombie/core/Core.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/input/Mouse.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/SpriteDetails/IsoObjectType.h"
#include "zombie/iso/objects/IsoCurtain.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/iso/objects/IsoDoor.h"
#include "zombie/iso/objects/IsoLightSwitch.h"
#include "zombie/iso/objects/IsoThumpable.h"
#include "zombie/iso/objects/IsoTree.h"
#include "zombie/iso/objects/IsoWaveSignal.h"
#include "zombie/iso/objects/IsoWindow.h"
#include "zombie/iso/objects/IsoWindowFrame.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/util/Type.h"
#include "zombie/vehicles/BaseVehicle.h"
#include <algorithm>

namespace zombie {
namespace iso {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class IsoObjectPicker {
public:
 static const IsoObjectPicker Instance = new IsoObjectPicker();
 static ArrayList<IsoObjectPicker.ClickObject> choices = std::make_unique<ArrayList<>>();
 static const Vector2 tempo = new Vector2();
 static const Vector2 tempo2 = new Vector2();
 static Comparator<IsoObjectPicker.ClickObject> comp = new Comparator<IsoObjectPicker.ClickObject>() {
 int compare(IsoObjectPicker.ClickObject clickObject0, IsoObjectPicker.ClickObject clickObject1) {
 int int0 = clickObject0.getScore();
 int int1 = clickObject1.getScore();
 if (int0 > int1) {
 return 1;
 } else if (int0 < int1) {
 return -1;
 } else {
 return clickObject0.tile != nullptr
 && clickObject0.tile.square != nullptr
 && clickObject1.tile != nullptr
 && clickObject0.tile.square == clickObject1.tile.square
 ? clickObject0.tile.getObjectIndex() - clickObject1.tile.getObjectIndex()
 : 0;
 }
 }
 };
 public IsoObjectPicker.ClickObject[] ClickObjectStore = new IsoObjectPicker.ClickObject[15000];
 int count = 0;
 int counter = 0;
 int maxcount = 0;
 public ArrayList<IsoObjectPicker.ClickObject> ThisFrame = std::make_unique<ArrayList<>>();
 bool dirty = true;
 float xOffSinceDirty = 0.0F;
 float yOffSinceDirty = 0.0F;
 bool wasDirty = false;
 IsoObjectPicker.ClickObject LastPickObject = nullptr;
 float lx = 0.0F;
 float ly = 0.0F;

 IsoObjectPicker getInstance() {
 return Instance;
 }

 void Add(int x, int y, int width, int height, IsoGridSquare gridSquare, IsoObject tile, bool flip, float scaleX, float scaleY) {
 if (!(x + width <= this->lx - 32.0F) && !(x >= this->lx + 32.0F) && !(y + height <= this->ly - 32.0F) && !(y >= this->ly + 32.0F) {
 if (this->ThisFrame.size() < 15000) {
 if (!tile.NoPicking) {
 if (tile instanceof IsoSurvivor) {
 bool boolean0 = false;
 }

 if (tile instanceof IsoDoor) {
 bool boolean1 = false;
 }

 if (x <= Core.getInstance().getOffscreenWidth(0) {
 if (y <= Core.getInstance().getOffscreenHeight(0) {
 if (x + width >= 0) {
 if (y + height >= 0) {
 IsoObjectPicker.ClickObject clickObject = this->ClickObjectStore[this->ThisFrame.size()];
 this->ThisFrame.add(clickObject);
 this->count = this->ThisFrame.size();
 clickObject.x = x;
 clickObject.y = y;
 clickObject.width = width;
 clickObject.height = height;
 clickObject.square = gridSquare;
 clickObject.tile = tile;
 clickObject.flip = flip;
 clickObject.scaleX = scaleX;
 clickObject.scaleY = scaleY;
 if (clickObject.tile instanceof IsoGameCharacter) {
 clickObject.flip = false;
 }

 if (this->count > this->maxcount) {
 this->maxcount = this->count;
 }
 }
 }
 }
 }
 }
 }
 }
 }

 void Init() {
 this->ThisFrame.clear();
 this->LastPickObject = nullptr;

 for (int int0 = 0; int0 < 15000; int0++) {
 this->ClickObjectStore[int0] = new IsoObjectPicker.ClickObject();
 }
 }

 public IsoObjectPicker.ClickObject ContextPick(int screenX, int screenY) {
 float float0 = screenX * Core.getInstance().getZoom(0);
 float float1 = screenY * Core.getInstance().getZoom(0);
 choices.clear();
 this->counter++;

 for (int int0 = this->ThisFrame.size() - 1; int0 >= 0; int0--) {
 IsoObjectPicker.ClickObject clickObject0 = this->ThisFrame.get(int0);
 if ((!(clickObject0.tile instanceof IsoPlayer) || clickObject0.tile != IsoPlayer.players[0])
 && (
 clickObject0.tile.sprite.empty()
 || clickObject0.tile.getTargetAlpha(0) != 0.0F
 && (
 !clickObject0.tile.sprite.Properties.Is(IsoFlagType.cutW) && !clickObject0.tile.sprite.Properties.Is(IsoFlagType.cutN)
 || clickObject0.tile instanceof IsoWindow
 || !(clickObject0.tile.getTargetAlpha(0) < 1.0F)
 )
 )) {
 if (clickObject0.tile != nullptr && clickObject0.tile.sprite != nullptr) {
 }

 if (float0 > clickObject0.x
 && float1 > clickObject0.y
 && float0 <= clickObject0.x + clickObject0.width
 && float1 <= clickObject0.y + clickObject0.height) {
 if (clickObject0.tile instanceof IsoPlayer) {
 if (clickObject0.tile.sprite.empty()
 || clickObject0.tile.sprite.def.empty()
 || clickObject0.tile.sprite.CurrentAnim.empty()
 || clickObject0.tile.sprite.CurrentAnim.Frames.empty()
 || clickObject0.tile.sprite.def.Frame < 0.0F
 || clickObject0.tile.sprite.def.Frame >= clickObject0.tile.sprite.CurrentAnim.Frames.size()) {
 continue;
 }

 int int1 = (int)(float0 - clickObject0.x);
 int int2 = (int)(float1 - clickObject0.y);
 Texture texture = clickObject0.tile.sprite.CurrentAnim.Frames.get((int)clickObject0.tile.sprite.def.Frame).directions[clickObject0.tile
 .dir
 .index()];
 int int3 = Core.TileScale;
 if (clickObject0.flip) {
 int2 = (int)(int2 - texture.offsetY);
 int1 = texture.getWidth() - int2;
 } else {
 int1 = (int)(int1 - texture.offsetX * int3);
 int2 = (int)(int2 - texture.offsetY * int3);
 }

 if (int1 >= 0 && int2 >= 0 && int1 <= texture.getWidth() * int3 && int2 <= texture.getHeight() * int3) {
 clickObject0.lx = (int)float0 - clickObject0.x;
 clickObject0.ly = (int)float1 - clickObject0.y;
 this->LastPickObject = clickObject0;
 choices.clear();
 choices.add(clickObject0);
 break;
 }
 }

 if (clickObject0.scaleX == 1.0F && clickObject0.scaleY == 1.0F) {
 if (clickObject0.tile.isMaskClicked((int)(float0 - clickObject0.x), (int)(float1 - clickObject0.y), clickObject0.flip) {
 if (clickObject0.tile.rerouteMask != nullptr) {
 clickObject0.tile = clickObject0.tile.rerouteMask;
 }

 clickObject0.lx = (int)float0 - clickObject0.x;
 clickObject0.ly = (int)float1 - clickObject0.y;
 this->LastPickObject = clickObject0;
 choices.add(clickObject0);
 }
 } else {
 float float2 = clickObject0.x + (float0 - clickObject0.x) / clickObject0.scaleX;
 float float3 = clickObject0.y + (float1 - clickObject0.y) / clickObject0.scaleY;
 if (clickObject0.tile.isMaskClicked((int)(float2 - clickObject0.x), (int)(float3 - clickObject0.y), clickObject0.flip) {
 if (clickObject0.tile.rerouteMask != nullptr) {
 clickObject0.tile = clickObject0.tile.rerouteMask;
 }

 clickObject0.lx = (int)float0 - clickObject0.x;
 clickObject0.ly = (int)float1 - clickObject0.y;
 this->LastPickObject = clickObject0;
 choices.add(clickObject0);
 }
 }
 }
 }
 }

 if (choices.empty()) {
 return nullptr;
 } else {
 for (int int4 = 0; int4 < choices.size(); int4++) {
 IsoObjectPicker.ClickObject clickObject1 = choices.get(int4);
 clickObject1.score = clickObject1.calculateScore();
 }

 try {
 Collections.sort(choices, comp);
 } catch (IllegalArgumentException illegalArgumentException) {
 if (Core.bDebug) {
 ExceptionLogger.logException(illegalArgumentException);
 }

 return nullptr;
 }

 return choices.get(choices.size() - 1);
 }
 }

 public IsoObjectPicker.ClickObject Pick(int xx, int yy) {
 float float0 = xx;
 float float1 = yy;
 float float2 = Core.getInstance().getScreenWidth();
 float float3 = Core.getInstance().getScreenHeight();
 float float4 = float2 * Core.getInstance().getZoom(0);
 float float5 = float3 * Core.getInstance().getZoom(0);
 float float6 = Core.getInstance().getOffscreenWidth(0);
 float float7 = Core.getInstance().getOffscreenHeight(0);
 float float8 = float6 / float4;
 float float9 = float7 / float5;
 float0 -= float2 / 2.0F;
 float1 -= float3 / 2.0F;
 float0 /= float8;
 float1 /= float9;
 float0 += float2 / 2.0F;
 float1 += float3 / 2.0F;
 this->counter++;

 for (int int0 = this->ThisFrame.size() - 1; int0 >= 0; int0--) {
 IsoObjectPicker.ClickObject clickObject = this->ThisFrame.get(int0);
 if (clickObject.tile.square != nullptr) {
 }

 if (!(clickObject.tile instanceof IsoPlayer) && (clickObject.tile.sprite.empty() || clickObject.tile.getTargetAlpha(0) != 0.0F) {
 if (clickObject.tile != nullptr && clickObject.tile.sprite != nullptr) {
 }

 if (float0 > clickObject.x
 && float1 > clickObject.y
 && float0 <= clickObject.x + clickObject.width
 && float1 <= clickObject.y + clickObject.height) {
 if (clickObject.tile instanceof IsoSurvivor) {
 bool boolean0 = false;
 } else if (clickObject.tile.isMaskClicked((int)(float0 - clickObject.x), (int)(float1 - clickObject.y), clickObject.flip) {
 if (clickObject.tile.rerouteMask != nullptr) {
 clickObject.tile = clickObject.tile.rerouteMask;
 }

 clickObject.lx = (int)float0 - clickObject.x;
 clickObject.ly = (int)float1 - clickObject.y;
 this->LastPickObject = clickObject;
 return clickObject;
 }
 }
 }
 }

 return nullptr;
 }

 void StartRender() {
 float float0 = Mouse.getX();
 float float1 = Mouse.getY();
 if (float0 != this->lx || float1 != this->ly) {
 this->dirty = true;
 }

 this->lx = float0;
 this->ly = float1;
 if (this->dirty) {
 this->ThisFrame.clear();
 this->count = 0;
 this->wasDirty = true;
 this->dirty = false;
 this->xOffSinceDirty = 0.0F;
 this->yOffSinceDirty = 0.0F;
 } else {
 this->wasDirty = false;
 }
 }

 IsoMovingObject PickTarget(int xx, int yy) {
 float float0 = xx;
 float float1 = yy;
 float float2 = Core.getInstance().getScreenWidth();
 float float3 = Core.getInstance().getScreenHeight();
 float float4 = float2 * Core.getInstance().getZoom(0);
 float float5 = float3 * Core.getInstance().getZoom(0);
 float float6 = Core.getInstance().getOffscreenWidth(0);
 float float7 = Core.getInstance().getOffscreenHeight(0);
 float float8 = float6 / float4;
 float float9 = float7 / float5;
 float0 -= float2 / 2.0F;
 float1 -= float3 / 2.0F;
 float0 /= float8;
 float1 /= float9;
 float0 += float2 / 2.0F;
 float1 += float3 / 2.0F;
 this->counter++;

 for (int int0 = this->ThisFrame.size() - 1; int0 >= 0; int0--) {
 IsoObjectPicker.ClickObject clickObject = this->ThisFrame.get(int0);
 if (clickObject.tile.square != nullptr) {
 }

 if (clickObject.tile != IsoPlayer.getInstance() && (clickObject.tile.sprite.empty() || clickObject.tile.getTargetAlpha() != 0.0F) {
 if (clickObject.tile != nullptr && clickObject.tile.sprite != nullptr) {
 }

 if (float0 > clickObject.x
 && float1 > clickObject.y
 && float0 <= clickObject.x + clickObject.width
 && float1 <= clickObject.y + clickObject.height
 && clickObject.tile instanceof IsoMovingObject
 && clickObject.tile.isMaskClicked((int)(float0 - clickObject.x), (int)(float1 - clickObject.y), clickObject.flip) {
 if (clickObject.tile.rerouteMask != nullptr) {
 }

 clickObject.lx = (int)(float0 - clickObject.x);
 clickObject.ly = (int)(float1 - clickObject.y);
 this->LastPickObject = clickObject;
 return (IsoMovingObject)clickObject.tile;
 }
 }
 }

 return nullptr;
 }

 IsoObject PickDoor(int screenX, int screenY, bool bTransparent) {
 float float0 = screenX * Core.getInstance().getZoom(0);
 float float1 = screenY * Core.getInstance().getZoom(0);
 int int0 = IsoPlayer.getPlayerIndex();

 for (int int1 = this->ThisFrame.size() - 1; int1 >= 0; int1--) {
 IsoObjectPicker.ClickObject clickObject = this->ThisFrame.get(int1);
 if (clickObject.tile instanceof IsoDoor
 && clickObject.tile.getTargetAlpha(int0) != 0.0F
 && bTransparent == clickObject.tile.getTargetAlpha(int0) < 1.0F
 && float0 >= clickObject.x
 && float1 >= clickObject.y
 && float0 < clickObject.x + clickObject.width
 && float1 < clickObject.y + clickObject.height) {
 int int2 = (int)(float0 - clickObject.x);
 int int3 = (int)(float1 - clickObject.y);
 if (clickObject.tile.isMaskClicked(int2, int3, clickObject.flip) {
 return clickObject.tile;
 }
 }
 }

 return nullptr;
 }

 IsoObject PickWindow(int screenX, int screenY) {
 float float0 = screenX * Core.getInstance().getZoom(0);
 float float1 = screenY * Core.getInstance().getZoom(0);

 for (int int0 = this->ThisFrame.size() - 1; int0 >= 0; int0--) {
 IsoObjectPicker.ClickObject clickObject = this->ThisFrame.get(int0);
 if ((clickObject.tile instanceof IsoWindow || clickObject.tile instanceof IsoCurtain)
 && (clickObject.tile.sprite.empty() || clickObject.tile.getTargetAlpha() != 0.0F)
 && float0 >= clickObject.x
 && float1 >= clickObject.y
 && float0 < clickObject.x + clickObject.width
 && float1 < clickObject.y + clickObject.height) {
 int int1 = (int)(float0 - clickObject.x);
 int int2 = (int)(float1 - clickObject.y);
 if (clickObject.tile.isMaskClicked(int1, int2, clickObject.flip) {
 return clickObject.tile;
 }

 if (clickObject.tile instanceof IsoWindow) {
 bool boolean0 = false;
 bool boolean1 = false;

 for (int int3 = int2; int3 >= 0; int3--) {
 if (clickObject.tile.isMaskClicked(int1, int3) {
 boolean0 = true;
 break;
 }
 }

 for (int int4 = int2; int4 < clickObject.height; int4++) {
 if (clickObject.tile.isMaskClicked(int1, int4) {
 boolean1 = true;
 break;
 }
 }

 if (boolean0 && boolean1) {
 return clickObject.tile;
 }
 }
 }
 }

 return nullptr;
 }

 IsoObject PickWindowFrame(int screenX, int screenY) {
 float float0 = screenX * Core.getInstance().getZoom(0);
 float float1 = screenY * Core.getInstance().getZoom(0);

 for (int int0 = this->ThisFrame.size() - 1; int0 >= 0; int0--) {
 IsoObjectPicker.ClickObject clickObject = this->ThisFrame.get(int0);
 if (IsoWindowFrame.isWindowFrame(clickObject.tile)
 && (clickObject.tile.sprite.empty() || clickObject.tile.getTargetAlpha() != 0.0F)
 && float0 >= clickObject.x
 && float1 >= clickObject.y
 && float0 < clickObject.x + clickObject.width
 && float1 < clickObject.y + clickObject.height) {
 int int1 = (int)(float0 - clickObject.x);
 int int2 = (int)(float1 - clickObject.y);
 if (clickObject.tile.isMaskClicked(int1, int2, clickObject.flip) {
 return clickObject.tile;
 }

 bool boolean0 = false;
 bool boolean1 = false;

 for (int int3 = int2; int3 >= 0; int3--) {
 if (clickObject.tile.isMaskClicked(int1, int3) {
 boolean0 = true;
 break;
 }
 }

 for (int int4 = int2; int4 < clickObject.height; int4++) {
 if (clickObject.tile.isMaskClicked(int1, int4) {
 boolean1 = true;
 break;
 }
 }

 if (boolean0 && boolean1) {
 return clickObject.tile;
 }
 }
 }

 return nullptr;
 }

 IsoObject PickThumpable(int screenX, int screenY) {
 float float0 = screenX * Core.getInstance().getZoom(0);
 float float1 = screenY * Core.getInstance().getZoom(0);

 for (int int0 = this->ThisFrame.size() - 1; int0 >= 0; int0--) {
 IsoObjectPicker.ClickObject clickObject = this->ThisFrame.get(int0);
 if (clickObject.tile instanceof IsoThumpable thumpable
 && (clickObject.tile.sprite.empty() || clickObject.tile.getTargetAlpha() != 0.0F)
 && float0 >= clickObject.x
 && float1 >= clickObject.y
 && float0 < clickObject.x + clickObject.width
 && float1 < clickObject.y + clickObject.height) {
 int int1 = (int)(float0 - clickObject.x);
 int int2 = (int)(float1 - clickObject.y);
 if (clickObject.tile.isMaskClicked(int1, int2, clickObject.flip) {
 return clickObject.tile;
 }
 }
 }

 return nullptr;
 }

 IsoObject PickHoppable(int screenX, int screenY) {
 float float0 = screenX * Core.getInstance().getZoom(0);
 float float1 = screenY * Core.getInstance().getZoom(0);

 for (int int0 = this->ThisFrame.size() - 1; int0 >= 0; int0--) {
 IsoObjectPicker.ClickObject clickObject = this->ThisFrame.get(int0);
 if (clickObject.tile.isHoppable()
 && (clickObject.tile.sprite.empty() || clickObject.tile.getTargetAlpha() != 0.0F)
 && float0 >= clickObject.x
 && float1 >= clickObject.y
 && float0 < clickObject.x + clickObject.width
 && float1 < clickObject.y + clickObject.height) {
 int int1 = (int)(float0 - clickObject.x);
 int int2 = (int)(float1 - clickObject.y);
 if (clickObject.tile.isMaskClicked(int1, int2, clickObject.flip) {
 return clickObject.tile;
 }
 }
 }

 return nullptr;
 }

 IsoObject PickCorpse(int screenX, int screenY) {
 float float0 = screenX * Core.getInstance().getZoom(0);
 float float1 = screenY * Core.getInstance().getZoom(0);

 for (int int0 = this->ThisFrame.size() - 1; int0 >= 0; int0--) {
 IsoObjectPicker.ClickObject clickObject = this->ThisFrame.get(int0);
 if (float0 >= clickObject.x
 && float1 >= clickObject.y
 && float0 < clickObject.x + clickObject.width
 && float1 < clickObject.y + clickObject.height
 && !(clickObject.tile.getTargetAlpha() < 1.0F) {
 if (clickObject.tile.isMaskClicked((int)(float0 - clickObject.x), (int)(float1 - clickObject.y), clickObject.flip)
 && !(clickObject.tile instanceof IsoWindow) {
 return nullptr;
 }

 if (clickObject.tile instanceof IsoDeadBody && ((IsoDeadBody)clickObject.tile).isMouseOver(float0, float1) {
 return clickObject.tile;
 }
 }
 }

 return nullptr;
 }

 IsoObject PickTree(int screenX, int screenY) {
 float float0 = screenX * Core.getInstance().getZoom(0);
 float float1 = screenY * Core.getInstance().getZoom(0);

 for (int int0 = this->ThisFrame.size() - 1; int0 >= 0; int0--) {
 IsoObjectPicker.ClickObject clickObject = this->ThisFrame.get(int0);
 if (clickObject.tile instanceof IsoTree
 && (clickObject.tile.sprite.empty() || clickObject.tile.getTargetAlpha() != 0.0F)
 && float0 >= clickObject.x
 && float1 >= clickObject.y
 && float0 < clickObject.x + clickObject.width
 && float1 < clickObject.y + clickObject.height) {
 int int1 = (int)(float0 - clickObject.x);
 int int2 = (int)(float1 - clickObject.y);
 if (clickObject.tile.isMaskClicked(int1, int2, clickObject.flip) {
 return clickObject.tile;
 }
 }
 }

 return nullptr;
 }

 BaseVehicle PickVehicle(int screenX, int screenY) {
 float float0 = IsoUtils.XToIso(screenX, screenY, 0.0F);
 float float1 = IsoUtils.YToIso(screenX, screenY, 0.0F);

 for (int int0 = 0; int0 < IsoWorld.instance.CurrentCell.getVehicles().size(); int0++) {
 BaseVehicle vehicle = IsoWorld.instance.CurrentCell.getVehicles().get(int0);
 if (vehicle.isInBounds(float0, float1) {
 return vehicle;
 }
 }

 return nullptr;
 }

 public static class ClickObject {
 int height;
 IsoGridSquare square;
 IsoObject tile;
 int width;
 int x;
 int y;
 int lx;
 int ly;
 float scaleX;
 float scaleY;
 bool flip;
 int score;

 int calculateScore() {
 float float0 = 1.0F;
 IsoPlayer player = IsoPlayer.getInstance();
 IsoGridSquare square0 = player.getCurrentSquare();
 IsoObjectPicker.tempo.x = this->square.getX() + 0.5F;
 IsoObjectPicker.tempo.y = this->square.getY() + 0.5F;
 IsoObjectPicker.tempo.x = IsoObjectPicker.tempo.x - player.getX();
 IsoObjectPicker.tempo.y = IsoObjectPicker.tempo.y - player.getY();
 IsoObjectPicker.tempo.normalize();
 Vector2 vector = player.getVectorFromDirection(IsoObjectPicker.tempo2);
 float float1 = vector.dot(IsoObjectPicker.tempo);
 float0 += Math.abs(float1 * 4.0F);
 IsoGridSquare square1 = this->square;
 IsoObject object = this->tile;
 IsoSprite sprite = object.sprite;
 IsoDoor door = Type.tryCastTo(object, IsoDoor.class);
 IsoThumpable thumpable = Type.tryCastTo(object, IsoThumpable.class);
 if (door.empty() && (thumpable.empty() || !thumpable.isDoor())) {
 if (object instanceof IsoWindow) {
 float0 += 4.0F;
 if (player.getZ() > square1.getZ()) {
 float0 -= 1000.0F;
 }
 } else {
 if (square0 != nullptr && square1.getRoom() == square0.getRoom()) {
 float0++;
 } else {
 float0 -= 100000.0F;
 }

 if (player.getZ() > square1.getZ()) {
 float0 -= 1000.0F;
 }

 if (object instanceof IsoPlayer) {
 float0 -= 100000.0F;
 } else if (object instanceof IsoThumpable
 && object.getTargetAlpha() < 0.99F
 && (object.getTargetAlpha() < 0.5F || object.getContainer() == nullptr) {
 float0 -= 100000.0F;
 }

 if (object instanceof IsoCurtain) {
 float0 += 3.0F;
 } else if (object instanceof IsoLightSwitch) {
 float0 += 20.0F;
 } else if (sprite.Properties.Is(IsoFlagType.bed) {
 float0 += 2.0F;
 } else if (object.container != nullptr) {
 float0 += 10.0F;
 } else if (object instanceof IsoWaveSignal) {
 float0 += 20.0F;
 } else if (thumpable != nullptr && thumpable.getLightSource() != nullptr) {
 float0 += 3.0F;
 } else if (sprite.Properties.Is(IsoFlagType.waterPiped) {
 float0 += 3.0F;
 } else if (sprite.Properties.Is(IsoFlagType.solidfloor) {
 float0 -= 100.0F;
 } else if (sprite.getType() == IsoObjectType.WestRoofB) {
 float0 -= 100.0F;
 } else if (sprite.getType() == IsoObjectType.WestRoofM) {
 float0 -= 100.0F;
 } else if (sprite.getType() == IsoObjectType.WestRoofT) {
 float0 -= 100.0F;
 } else if (sprite.Properties.Is(IsoFlagType.cutW) || sprite.Properties.Is(IsoFlagType.cutN) {
 float0 -= 2.0F;
 }
 }
 } else {
 float0 += 6.0F;
 if (door != nullptr && door.isAdjacentToSquare(square0) || thumpable != nullptr && thumpable.isAdjacentToSquare(square0) {
 float0++;
 }

 if (player.getZ() > square1.getZ()) {
 float0 -= 1000.0F;
 }
 }

 float float2 = IsoUtils.DistanceManhatten(square1.getX() + 0.5F, square1.getY() + 0.5F, player.getX(), player.getY());
 float0 -= float2 / 2.0F;
 return (int)float0;
 }

 int getScore() {
 return this->score;
 }
 }
}
} // namespace iso
} // namespace zombie
