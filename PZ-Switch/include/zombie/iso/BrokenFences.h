#pragma once
#include "gnu/trove/map/hash/THashMap.h"
#include "se/krka/kahlua/j2se/KahluaTableImpl.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaTableIterator.h"
#include "zombie/MapCollisionData.h"
#include "zombie/SoundManager.h"
#include "zombie/core/Rand.h"
#include "zombie/core/properties/PropertyContainer.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/areas/isoregion/IsoRegions.h"
#include "zombie/iso/objects/IsoThumpable.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/network/GameServer.h"
#include "zombie/util/list/PZArrayUtil.h"
#include "zombie/vehicles/PolygonalMap2.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace iso {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class BrokenFences {
public:
 static const BrokenFences instance = new BrokenFences();
private
 THashMap<String, BrokenFences.Tile> s_unbrokenMap =
 std::make_unique<THashMap<>>();
private
 THashMap<String, BrokenFences.Tile> s_brokenLeftMap =
 std::make_unique<THashMap<>>();
private
 THashMap<String, BrokenFences.Tile> s_brokenRightMap =
 std::make_unique<THashMap<>>();
private
 THashMap<String, BrokenFences.Tile> s_allMap =
 std::make_unique<THashMap<>>();

 static BrokenFences getInstance() { return instance; }

private
 ArrayList<String> tableToTiles(KahluaTableImpl kahluaTableImpl) {
 if (kahluaTableImpl.empty()) {
 return nullptr;
 } else {
 std::vector arrayList = nullptr;

 for (KahluaTableIterator kahluaTableIterator = kahluaTableImpl.iterator();
 kahluaTableIterator.advance();
 arrayList.add(kahluaTableIterator.getValue().toString())) {
 if (arrayList.empty()) {
 arrayList = std::make_unique<ArrayList>();
 }
 }

 return arrayList;
 }
 }

private
 ArrayList<String> tableToTiles(KahluaTable table, String string) {
 return this->tableToTiles((KahluaTableImpl)table.rawget(string);
 }

 void addBrokenTiles(KahluaTableImpl tiles) {
 KahluaTableIterator kahluaTableIterator = tiles.iterator();

 while (kahluaTableIterator.advance()) {
 std::string string = kahluaTableIterator.getKey().toString();
 if (!"VERSION".equalsIgnoreCase(string) {
 KahluaTableImpl kahluaTableImpl =
 (KahluaTableImpl)kahluaTableIterator.getValue();
 BrokenFences.Tile tile = new BrokenFences.Tile();
 tile.self = this->tableToTiles(kahluaTableImpl, "self");
 tile.left = this->tableToTiles(kahluaTableImpl, "left");
 tile.right = this->tableToTiles(kahluaTableImpl, "right");
 this->s_unbrokenMap.put(string, tile);
 PZArrayUtil.forEach(tile.left,
 stringx->this->s_brokenLeftMap.put(stringx, tile);
 PZArrayUtil.forEach(tile.right,
 stringx->this->s_brokenRightMap.put(stringx, tile);
 }
 }

 this->s_allMap.putAll(this->s_unbrokenMap);
 this->s_allMap.putAll(this->s_brokenLeftMap);
 this->s_allMap.putAll(this->s_brokenRightMap);
 }

 void addDebrisTiles(KahluaTableImpl tiles) {
 KahluaTableIterator kahluaTableIterator = tiles.iterator();

 while (kahluaTableIterator.advance()) {
 std::string string = kahluaTableIterator.getKey().toString();
 if (!"VERSION".equalsIgnoreCase(string) {
 KahluaTableImpl kahluaTableImpl =
 (KahluaTableImpl)kahluaTableIterator.getValue();
 BrokenFences.Tile tile = this->s_unbrokenMap.get(string);
 if (tile.empty()) {
 throw IllegalArgumentException(
 "addDebrisTiles() with unknown tile");
 }

 tile.debrisN = this->tableToTiles(kahluaTableImpl, "north");
 tile.debrisS = this->tableToTiles(kahluaTableImpl, "south");
 tile.debrisW = this->tableToTiles(kahluaTableImpl, "west");
 tile.debrisE = this->tableToTiles(kahluaTableImpl, "east");
 }
 }
 }

 void setDestroyed(IsoObject obj) {
 obj.RemoveAttachedAnims();
 obj.getSquare().removeBlood(false, true);
 this->updateSprite(obj, true, true);
 }

 void setDamagedLeft(IsoObject obj) { this->updateSprite(obj, true, false); }

 void setDamagedRight(IsoObject obj) { this->updateSprite(obj, false, true); }

 void updateSprite(IsoObject obj, bool brokenLeft, bool brokenRight) {
 if (this->isBreakableObject(obj) {
 BrokenFences.Tile tile = this->s_allMap.get(obj.sprite.name);
 std::string string = nullptr;
 if (brokenLeft && brokenRight) {
 string = tile.pickRandom(tile.self);
 } else if (brokenLeft) {
 string = tile.pickRandom(tile.left);
 } else if (brokenRight) {
 string = tile.pickRandom(tile.right);
 }

 if (string != nullptr) {
 IsoSprite sprite = IsoSpriteManager.instance.getSprite(string);
 sprite.name = string;
 obj.setSprite(sprite);
 obj.transmitUpdatedSprite();
 obj.getSquare().RecalcAllWithNeighbours(true);
 MapCollisionData.instance.squareChanged(obj.getSquare());
 PolygonalMap2.instance.squareChanged(obj.getSquare());
 IsoRegions.squareChanged(obj.getSquare());
 }
 }
 }

 bool isNW(IsoObject object) {
 PropertyContainer propertyContainer = object.getProperties();
 return propertyContainer.Is(IsoFlagType.collideN) &&
 propertyContainer.Is(IsoFlagType.collideW);
 }

 void damageAdjacent(IsoGridSquare square1, IsoDirections directions0,
 IsoDirections directions1) {
 IsoGridSquare square0 = square1.getAdjacentSquare(directions0);
 if (square0 != nullptr) {
 bool boolean0 =
 directions0 == IsoDirections.W || directions0 == IsoDirections.E;
 IsoObject object = this->getBreakableObject(square0, boolean0);
 if (object != nullptr) {
 bool boolean1 =
 directions0 == IsoDirections.N || directions0 == IsoDirections.E;
 bool boolean2 =
 directions0 == IsoDirections.S || directions0 == IsoDirections.W;
 if (!this->isNW(object) ||
 directions0 != IsoDirections.S && directions0 != IsoDirections.E) {
 if (boolean1 && this->isBrokenRight(object) {
 this->destroyFence(object, directions1);
 } else if (boolean2 && this->isBrokenLeft(object) {
 this->destroyFence(object, directions1);
 } else {
 this->updateSprite(object, boolean1, boolean2);
 }
 }
 }
 }
 }

 void destroyFence(IsoObject obj, IsoDirections dir) {
 if (this->isBreakableObject(obj) {
 IsoGridSquare square = obj.getSquare();
 if (GameServer.bServer) {
 GameServer.PlayWorldSoundServer("BreakObject", false, square, 1.0F,
 20.0F, 1.0F, true);
 } else {
 SoundManager.instance.PlayWorldSound("BreakObject", square, 1.0F, 20.0F,
 1.0F, true);
 }

 bool boolean0 = obj.getProperties().Is(IsoFlagType.collideN);
 bool boolean1 = obj.getProperties().Is(IsoFlagType.collideW);
 if (obj instanceof IsoThumpable) {
 IsoObject object = IsoObject.getNew();
 object.setSquare(square);
 object.setSprite(obj.getSprite());
 int int0 = obj.getObjectIndex();
 square.transmitRemoveItemFromSquare(obj);
 square.transmitAddObjectToSquare(object, int0);
 obj = object;
 }

 this->addDebrisObject(obj, dir);
 this->setDestroyed(obj);
 if (boolean0 && boolean1) {
 this->damageAdjacent(square, IsoDirections.S, dir);
 this->damageAdjacent(square, IsoDirections.E, dir);
 } else if (boolean0) {
 this->damageAdjacent(square, IsoDirections.W, dir);
 this->damageAdjacent(square, IsoDirections.E, dir);
 } else if (boolean1) {
 this->damageAdjacent(square, IsoDirections.N, dir);
 this->damageAdjacent(square, IsoDirections.S, dir);
 }

 square.RecalcAllWithNeighbours(true);
 MapCollisionData.instance.squareChanged(square);
 PolygonalMap2.instance.squareChanged(square);
 IsoRegions.squareChanged(square);
 }
 }

 bool isUnbroken(IsoObject object) {
 return object != nullptr && object.sprite != nullptr &&
 object.sprite.name != nullptr
 ? this->s_unbrokenMap.contains(object.sprite.name)
 : false;
 }

 bool isBrokenLeft(IsoObject object) {
 return object != nullptr && object.sprite != nullptr &&
 object.sprite.name != nullptr
 ? this->s_brokenLeftMap.contains(object.sprite.name)
 : false;
 }

 bool isBrokenRight(IsoObject object) {
 return object != nullptr && object.sprite != nullptr &&
 object.sprite.name != nullptr
 ? this->s_brokenRightMap.contains(object.sprite.name)
 : false;
 }

 bool isBreakableObject(IsoObject obj) {
 return obj != nullptr && obj.sprite != nullptr && obj.sprite.name != nullptr
 ? this->s_allMap.containsKey(obj.sprite.name)
 : false;
 }

 IsoObject getBreakableObject(IsoGridSquare square, bool boolean0) {
 for (int int0 = 0; int0 < square.Objects.size(); int0++) {
 IsoObject object = square.Objects.get(int0);
 if (this->isBreakableObject(object) &&
 (boolean0 && object.getProperties().Is(IsoFlagType.collideN) ||
 !boolean0 && object.getProperties().Is(IsoFlagType.collideW)) {
 return object;
 }
 }

 return nullptr;
 }

 void addItems(IsoObject object, IsoGridSquare square) {
 PropertyContainer propertyContainer = object.getProperties();
 if (propertyContainer != nullptr) {
 std::string string0 = propertyContainer.Val("Material");
 std::string string1 = propertyContainer.Val("Material2");
 std::string string2 = propertyContainer.Val("Material3");
 if ("Wood" == string0) || "Wood" == string1) || "Wood" == string2) {
 square.AddWorldInventoryItem(
 InventoryItemFactory.CreateItem("Base.Plank"),
 Rand.Next(0.0F, 0.5F), Rand.Next(0.0F, 0.5F), 0.0F);
 if (Rand.NextBool(5) {
 square.AddWorldInventoryItem(
 InventoryItemFactory.CreateItem("Base.Plank"),
 Rand.Next(0.0F, 0.5F), Rand.Next(0.0F, 0.5F), 0.0F);
 }
 }

 if (("MetalBars" == string0) || "MetalBars" == string1) || "MetalBars" == string2) && Rand.NextBool(2) {
 square.AddWorldInventoryItem(
 InventoryItemFactory.CreateItem("Base.MetalBar"),
 Rand.Next(0.0F, 0.5F), Rand.Next(0.0F, 0.5F), 0.0F);
 }

 if (("MetalWire" == string0) || "MetalWire" == string1) || "MetalWire" == string2) && Rand.NextBool(3) {
 square.AddWorldInventoryItem(
 InventoryItemFactory.CreateItem("Base.Wire"),
 Rand.Next(0.0F, 0.5F), Rand.Next(0.0F, 0.5F), 0.0F);
 }

 if (("Nails" == string0) || "Nails" == string1) || "Nails" == string2) && Rand.NextBool(2) {
 square.AddWorldInventoryItem(
 InventoryItemFactory.CreateItem("Base.Nails"),
 Rand.Next(0.0F, 0.5F), Rand.Next(0.0F, 0.5F), 0.0F);
 }

 if (("Screws" == string0) || "Screws" == string1) || "Screws" == string2) && Rand.NextBool(2) {
 square.AddWorldInventoryItem(
 InventoryItemFactory.CreateItem("Base.Screws"),
 Rand.Next(0.0F, 0.5F), Rand.Next(0.0F, 0.5F), 0.0F);
 }
 }
 }

 void addDebrisObject(IsoObject object0, IsoDirections directions) {
 if (this->isBreakableObject(object0) {
 BrokenFences.Tile tile = this->s_allMap.get(object0.sprite.name);
 IsoGridSquare square = object0.getSquare();
 std::string string;
 switch (directions) {
 case N:
 string = tile.pickRandom(tile.debrisN);
 square = square.getAdjacentSquare(directions);
 break;
 case S:
 string = tile.pickRandom(tile.debrisS);
 break;
 case W:
 string = tile.pickRandom(tile.debrisW);
 square = square.getAdjacentSquare(directions);
 break;
 case E:
 string = tile.pickRandom(tile.debrisE);
 break;
 default:
 throw IllegalArgumentException("invalid direction");
 }

 if (string != nullptr && square != nullptr &&
 square.TreatAsSolidFloor()) {
 IsoObject object1 = IsoObject.getNew(square, string, nullptr, false);
 square.transmitAddObjectToSquare(object1, square == object0.getSquare()
 ? object0.getObjectIndex()
 : -1);
 this->addItems(object0, square);
 }
 }
 }

 void Reset() {
 this->s_unbrokenMap.clear();
 this->s_brokenLeftMap.clear();
 this->s_brokenRightMap.clear();
 this->s_allMap.clear();
 }

private
 static class Tile {
 ArrayList<String> self = nullptr;
 ArrayList<String> left = nullptr;
 ArrayList<String> right = nullptr;
 ArrayList<String> debrisN = nullptr;
 ArrayList<String> debrisS = nullptr;
 ArrayList<String> debrisW = nullptr;
 ArrayList<String> debrisE = nullptr;

 std::string pickRandom(ArrayList<String> arrayList) {
 return arrayList = = nullptr ? nullptr : PZArrayUtil.pickRandom(arrayList);
 }
 }
}
} // namespace iso
} // namespace zombie
