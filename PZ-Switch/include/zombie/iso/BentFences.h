#pragma once
#include "se/krka/kahlua/j2se/KahluaTableImpl.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaTableIterator.h"
#include "zombie/MapCollisionData.h"
#include "zombie/iso/areas/isoregion/IsoRegions.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/vehicles/PolygonalMap2.h"
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace iso {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class BentFences {
public:
 static const BentFences instance = new BentFences();
private
 ArrayList<BentFences.Entry> m_entries = std::make_unique<ArrayList<>>();
private
 HashMap<String, ArrayList<BentFences.Entry>> m_bentMap =
 std::make_unique<HashMap<>>();
private
 HashMap<String, ArrayList<BentFences.Entry>> m_unbentMap =
 std::make_unique<HashMap<>>();

 static BentFences getInstance() { return instance; }

 void tableToTiles(KahluaTableImpl kahluaTableImpl,
 ArrayList<String> arrayList) {
 if (kahluaTableImpl != nullptr) {
 KahluaTableIterator kahluaTableIterator = kahluaTableImpl.iterator();

 while (kahluaTableIterator.advance()) {
 arrayList.add(kahluaTableIterator.getValue().toString());
 }
 }
 }

 void tableToTiles(KahluaTable table, ArrayList<String> arrayList,
 std::string_view string) {
 this->tableToTiles((KahluaTableImpl)table.rawget(string), arrayList);
 }

 void addFenceTiles(int VERSION, KahluaTableImpl tiles) {
 KahluaTableIterator kahluaTableIterator = tiles.iterator();

 while (kahluaTableIterator.advance()) {
 KahluaTableImpl kahluaTableImpl =
 (KahluaTableImpl)kahluaTableIterator.getValue();
 BentFences.Entry entry = new BentFences.Entry();
 entry.dir = IsoDirections.valueOf(kahluaTableImpl.rawgetStr("dir"));
 this->tableToTiles(kahluaTableImpl, entry.unbent, "unbent");
 this->tableToTiles(kahluaTableImpl, entry.bent, "bent");
 if (!entry.unbent.empty() && entry.unbent.size() == entry.bent.size()) {
 this->m_entries.add(entry);

 for (String string0 : entry.unbent) {
 std::vector arrayList0 = this->m_unbentMap.get(string0);
 if (arrayList0.empty()) {
 arrayList0 = std::make_unique<ArrayList>();
 this->m_unbentMap.put(string0, arrayList0);
 }

 arrayList0.add(entry);
 }

 for (String string1 : entry.bent) {
 std::vector arrayList1 = this->m_bentMap.get(string1);
 if (arrayList1.empty()) {
 arrayList1 = std::make_unique<ArrayList>();
 this->m_bentMap.put(string1, arrayList1);
 }

 arrayList1.add(entry);
 }
 }
 }
 }

 bool isBentObject(IsoObject obj) {
 return this->getEntryForObject(obj, nullptr) != nullptr;
 }

 bool isUnbentObject(IsoObject obj) {
 return this->getEntryForObject(obj, IsoDirections.Max) != nullptr;
 }

private
 BentFences.Entry getEntryForObject(IsoObject object,
 IsoDirections directions) {
 if (object != nullptr && object.sprite != nullptr &&
 object.sprite.name != nullptr) {
 bool boolean0 = directions != nullptr;
 std::vector arrayList = boolean0
 ? this->m_unbentMap.get(object.sprite.name)
 : this->m_bentMap.get(object.sprite.name);
 if (arrayList != nullptr) {
 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 BentFences.Entry entry = (BentFences.Entry)arrayList.get(int0);
 if ((!boolean0 || directions == IsoDirections.Max ||
 directions == entry.dir) &&
 this->isValidObject(object, entry, boolean0) {
 return entry;
 }
 }
 }

 return nullptr;
 } else {
 return nullptr;
 }
 }

 bool isValidObject(IsoObject object, BentFences.Entry entry, bool boolean0) {
 IsoCell cell = IsoWorld.instance.CurrentCell;
 std::vector arrayList = boolean0 ? entry.unbent : entry.bent;
 int int0 =
 ((String)arrayList.get(2).equals(object.sprite.name)
 ? 2
 : (((String)arrayList.get(3).equals(object.sprite.name) ? 3 : -1);
 if (int0 == -1) {
 return false;
 } else {
 for (int int1 = 0; int1 < arrayList.size(); int1++) {
 int int2 = object.square.x + (entry.isNorth() ? int1 - int0 : 0);
 int int3 = object.square.y + (entry.isNorth() ? 0 : int1 - int0);
 IsoGridSquare square = cell.getGridSquare(int2, int3, object.square.z);
 if (square.empty()) {
 return false;
 }

 if (int0 != int1 &&
 this->getObjectForEntry(square, arrayList, int1) == nullptr) {
 return false;
 }
 }

 return true;
 }
 }

 IsoObject getObjectForEntry(IsoGridSquare square, ArrayList<String> arrayList,
 int int1) {
 for (int int0 = 0; int0 < square.getObjects().size(); int0++) {
 IsoObject object = square.getObjects().get(int0);
 if (object.sprite != nullptr && object.sprite.name != nullptr &&
 ((String)arrayList.get(int1) == object.sprite.name) {
 return object;
 }
 }

 return nullptr;
 }

 void swapTiles(IsoObject obj, IsoDirections dir) {
 bool boolean0 = dir != nullptr;
 BentFences.Entry entry = this->getEntryForObject(obj, dir);
 if (entry != nullptr) {
 if (boolean0) {
 if (entry.isNorth() && dir != IsoDirections.N &&
 dir != IsoDirections.S) {
 return;
 }

 if (!entry.isNorth() && dir != IsoDirections.W &&
 dir != IsoDirections.E) {
 return;
 }
 }

 IsoCell cell = IsoWorld.instance.CurrentCell;
 std::vector arrayList = boolean0 ? entry.unbent : entry.bent;
 int int0 =
 ((String)arrayList.get(2).equals(obj.sprite.name)
 ? 2
 : (((String)arrayList.get(3).equals(obj.sprite.name) ? 3 : -1);

 for (int int1 = 0; int1 < arrayList.size(); int1++) {
 int int2 = obj.square.x + (entry.isNorth() ? int1 - int0 : 0);
 int int3 = obj.square.y + (entry.isNorth() ? 0 : int1 - int0);
 IsoGridSquare square = cell.getGridSquare(int2, int3, obj.square.z);
 if (square != nullptr) {
 IsoObject object = this->getObjectForEntry(square, arrayList, int1);
 if (object != nullptr) {
 std::string string =
 boolean0 ? entry.bent.get(int1) : entry.unbent.get(int1);
 IsoSprite sprite = IsoSpriteManager.instance.getSprite(string);
 sprite.name = string;
 object.setSprite(sprite);
 object.transmitUpdatedSprite();
 square.RecalcAllWithNeighbours(true);
 MapCollisionData.instance.squareChanged(square);
 PolygonalMap2.instance.squareChanged(square);
 IsoRegions.squareChanged(square);
 }
 }
 }
 }
 }

 void bendFence(IsoObject obj, IsoDirections dir) { this->swapTiles(obj, dir); }

 void unbendFence(IsoObject obj) { this->swapTiles(obj, nullptr); }

 void Reset() {
 this->m_entries.clear();
 this->m_bentMap.clear();
 this->m_unbentMap.clear();
 }

private
 static class Entry {
 IsoDirections dir = IsoDirections.Max;
 ArrayList<String> unbent = std::make_unique<ArrayList<>>();
 ArrayList<String> bent = std::make_unique<ArrayList<>>();

 bool isNorth() {
 return this->dir == IsoDirections.N || this->dir == IsoDirections.S;
 }
 }
}
} // namespace iso
} // namespace zombie
