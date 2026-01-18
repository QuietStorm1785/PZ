#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/map/hash/THashMap.h"
#include "se/krka/kahlua/j2se/KahluaTableImpl.h"
#include "se/krka/kahlua/vm/KahluaTableIterator.h"
#include "zombie/core/Core.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteInstance.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/network/GameServer.h"
#include "zombie/util/LocationRNG.h"
#include "zombie/util/StringUtils.h"

namespace zombie {
namespace iso {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class TileOverlays {
public:
 static const TileOverlays instance = new TileOverlays();
 private static THashMap<String, TileOverlays.TileOverlay> overlayMap = std::make_unique<THashMap<>>();
 private static ArrayList<TileOverlays.TileOverlayEntry> tempEntries = std::make_unique<ArrayList<>>();

 void addOverlays(KahluaTableImpl _overlayMap) {
 KahluaTableIterator kahluaTableIterator0 = _overlayMap.iterator();

 while (kahluaTableIterator0.advance()) {
 std::string string0 = kahluaTableIterator0.getKey().toString();
 if (!"VERSION".equalsIgnoreCase(string0) {
 TileOverlays.TileOverlay tileOverlay = new TileOverlays.TileOverlay();
 tileOverlay.tile = string0;
 KahluaTableImpl kahluaTableImpl0 = (KahluaTableImpl)kahluaTableIterator0.getValue();
 KahluaTableIterator kahluaTableIterator1 = kahluaTableImpl0.iterator();

 while (kahluaTableIterator1.advance()) {
 KahluaTableImpl kahluaTableImpl1 = (KahluaTableImpl)kahluaTableIterator1.getValue();
 TileOverlays.TileOverlayEntry tileOverlayEntry = new TileOverlays.TileOverlayEntry();
 tileOverlayEntry.room = kahluaTableImpl1.rawgetStr("name");
 tileOverlayEntry.chance = kahluaTableImpl1.rawgetInt("chance");
 tileOverlayEntry.usage.parse(kahluaTableImpl1.rawgetStr("usage"));
 KahluaTableImpl kahluaTableImpl2 = (KahluaTableImpl)kahluaTableImpl1.rawget("tiles");
 KahluaTableIterator kahluaTableIterator2 = kahluaTableImpl2.iterator();

 while (kahluaTableIterator2.advance()) {
 std::string string1 = kahluaTableIterator2.getValue().toString();
 if (StringUtils.isNullOrWhitespace(string1) || "none".equalsIgnoreCase(string1) {
 string1 = "";
 } else if (Core.bDebug && !GameServer.bServer && Texture.getSharedTexture(string1) == nullptr) {
 System.out.println("BLANK OVERLAY TEXTURE. Set it to \"none\".: " + string1);
 }

 tileOverlayEntry.tiles.add(string1);
 }

 tileOverlay.entries.add(tileOverlayEntry);
 }

 overlayMap.put(tileOverlay.tile, tileOverlay);
 }
 }
 }

 bool hasOverlays(IsoObject obj) {
 return obj != nullptr && obj.sprite != nullptr && obj.sprite.name != nullptr && overlayMap.containsKey(obj.sprite.name);
 }

 void updateTileOverlaySprite(IsoObject obj) {
 if (obj != nullptr) {
 IsoGridSquare square = obj.getSquare();
 if (square != nullptr) {
 std::string string0 = nullptr;
 float float0 = -1.0F;
 float float1 = -1.0F;
 float float2 = -1.0F;
 float float3 = -1.0F;
 if (obj.sprite != nullptr && obj.sprite.name != nullptr) {
 TileOverlays.TileOverlay tileOverlay = overlayMap.get(obj.sprite.name);
 if (tileOverlay != nullptr) {
 std::string string1 = "other";
 if (square.getRoom() != nullptr) {
 string1 = square.getRoom().getName();
 }

 TileOverlays.TileOverlayEntry tileOverlayEntry = tileOverlay.pickRandom(string1, square);
 if (tileOverlayEntry.empty()) {
 tileOverlayEntry = tileOverlay.pickRandom("other", square);
 }

 if (tileOverlayEntry != nullptr) {
 if (tileOverlayEntry.usage.bTableTop && this->hasObjectOnTop(obj) {
 return;
 }

 string0 = tileOverlayEntry.pickRandom(square.x, square.y, square.z);
 if (tileOverlayEntry.usage.alpha >= 0.0F) {
 float2 = 1.0F;
 float1 = 1.0F;
 float0 = 1.0F;
 float3 = tileOverlayEntry.usage.alpha;
 }
 }
 }
 }

 if (!StringUtils.isNullOrWhitespace(string0) && !GameServer.bServer && Texture.getSharedTexture(string0) == nullptr) {
 string0 = nullptr;
 }

 if (!StringUtils.isNullOrWhitespace(string0) {
 if (obj.AttachedAnimSprite.empty()) {
 obj.AttachedAnimSprite = new ArrayList<>(4);
 }

 IsoSprite sprite = IsoSpriteManager.instance.getSprite(string0);
 sprite.name = string0;
 IsoSpriteInstance spriteInstance = IsoSpriteInstance.get(sprite);
 if (float3 > 0.0F) {
 spriteInstance.tintr = float0;
 spriteInstance.tintg = float1;
 spriteInstance.tintb = float2;
 spriteInstance.alpha = float3;
 }

 spriteInstance.bCopyTargetAlpha = false;
 spriteInstance.bMultiplyObjectAlpha = true;
 obj.AttachedAnimSprite.add(spriteInstance);
 }
 }
 }
 }

 bool hasObjectOnTop(IsoObject object0) {
 if (!object0.isTableSurface()) {
 return false;
 } else {
 IsoGridSquare square = object0.getSquare();

 for (int int0 = object0.getObjectIndex() + 1; int0 < square.getObjects().size(); int0++) {
 IsoObject object1 = square.getObjects().get(int0);
 if (object1.isTableTopObject() || object1.isTableSurface()) {
 return true;
 }
 }

 return false;
 }
 }

 void fixTableTopOverlays(IsoGridSquare square) {
 if (square != nullptr && !square.getObjects().empty()) {
 bool boolean0 = false;

 for (int int0 = square.getObjects().size() - 1; int0 >= 0; int0--) {
 IsoObject object = square.getObjects().get(int0);
 if (boolean0 && object.isTableSurface()) {
 this->removeTableTopOverlays(object);
 }

 if (object.isTableSurface() || object.isTableTopObject()) {
 boolean0 = true;
 }
 }
 }
 }

 void removeTableTopOverlays(IsoObject object) {
 if (object != nullptr && object.isTableSurface()) {
 if (object.sprite != nullptr && object.sprite.name != nullptr) {
 if (object.AttachedAnimSprite != nullptr && !object.AttachedAnimSprite.empty()) {
 TileOverlays.TileOverlay tileOverlay = overlayMap.get(object.sprite.name);
 if (tileOverlay != nullptr) {
 int int0 = object.AttachedAnimSprite.size();

 for (int int1 = 0; int1 < tileOverlay.entries.size(); int1++) {
 TileOverlays.TileOverlayEntry tileOverlayEntry = tileOverlay.entries.get(int1);
 if (tileOverlayEntry.usage.bTableTop) {
 for (int int2 = 0; int2 < tileOverlayEntry.tiles.size(); int2++) {
 this->tryRemoveAttachedSprite(object.AttachedAnimSprite, tileOverlayEntry.tiles.get(int2);
 }
 }
 }

 if (int0 != object.AttachedAnimSprite.size()) {
 }
 }
 }
 }
 }
 }

 void tryRemoveAttachedSprite(ArrayList<IsoSpriteInstance> arrayList, const std::string& string) {
 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 IsoSpriteInstance spriteInstance = (IsoSpriteInstance)arrayList.get(int0);
 if (string == spriteInstance.getName())) {
 arrayList.remove(int0--);
 IsoSpriteInstance.add(spriteInstance);
 }
 }
 }

 void Reset() {
 overlayMap.clear();
 }

 private static class TileOverlay {
 std::string tile;
 public ArrayList<TileOverlays.TileOverlayEntry> entries = std::make_unique<ArrayList<>>();

 void getEntries(const std::string& string, IsoGridSquare square, ArrayList<TileOverlays.TileOverlayEntry> arrayList) {
 arrayList.clear();

 for (int int0 = 0; int0 < this->entries.size(); int0++) {
 TileOverlays.TileOverlayEntry tileOverlayEntry = this->entries.get(int0);
 if (tileOverlayEntry.room.equalsIgnoreCase(string) && tileOverlayEntry.matchUsage(square) {
 arrayList.add(tileOverlayEntry);
 }
 }
 }

 public TileOverlays.TileOverlayEntry pickRandom(String string, IsoGridSquare square) {
 this->getEntries(string, square, TileOverlays.tempEntries);
 if (TileOverlays.tempEntries.empty()) {
 return nullptr;
 } else {
 int int0 = LocationRNG.instance.nextInt(TileOverlays.tempEntries.size(), square.x, square.y, square.z);
 return TileOverlays.tempEntries.get(int0);
 }
 }
 }

 private static class TileOverlayEntry {
 std::string room;
 int chance;
 public ArrayList<String> tiles = std::make_unique<ArrayList<>>();
 public TileOverlays.TileOverlayUsage usage = new TileOverlays.TileOverlayUsage();

 bool matchUsage(IsoGridSquare square) {
 return this->usage.match(square);
 }

 std::string pickRandom(int int1, int int2, int int3) {
 int int0 = LocationRNG.instance.nextInt(this->chance, int1, int2, int3);
 if (int0 == 0 && !this->tiles.empty()) {
 int0 = LocationRNG.instance.nextInt(this->tiles.size());
 return this->tiles.get(int0);
 } else {
 return nullptr;
 }
 }
 }

 private static class TileOverlayUsage {
 std::string usage;
 int zOnly = -1;
 int zGreaterThan = -1;
 float alpha = -1.0F;
 bool bTableTop = false;

 bool parse(const std::string& string0) {
 this->usage = string0.trim();
 if (StringUtils.isNullOrWhitespace(this->usage) {
 return true;
 } else {
 String[] strings = string0.split(";");

 for (int int0 = 0; int0 < strings.length; int0++) {
 std::string string1 = strings[int0];
 if (string1.startsWith("z=")) {
 this->zOnly = Integer.parseInt(string1.substring(2);
 } else if (string1.startsWith("z>")) {
 this->zGreaterThan = Integer.parseInt(string1.substring(2);
 } else if (string1.startsWith("alpha=")) {
 this->alpha = Float.parseFloat(string1.substring(6);
 this->alpha = PZMath.clamp(this->alpha, 0.0F, 1.0F);
 } else {
 if (!string1.startsWith("tabletop")) {
 return false;
 }

 this->bTableTop = true;
 }
 }

 return true;
 }
 }

 bool match(IsoGridSquare square) {
 return this->zOnly != -1 && square.z != this->zOnly ? false : this->zGreaterThan == -1 || square.z > this->zGreaterThan;
 }
 }
}
} // namespace iso
} // namespace zombie
