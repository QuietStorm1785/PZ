#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/map/hash/TIntObjectHashMap.h"
#include "zombie/core/Color.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"

namespace zombie {
namespace iso {
namespace sprite {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class IsoSpriteManager {
public:
 static const IsoSpriteManager instance = new IsoSpriteManager();
 public HashMap<String, IsoSprite> NamedMap = std::make_unique<HashMap<>>();
 public TIntObjectHashMap<IsoSprite> IntMap = std::make_unique<TIntObjectHashMap<>>();
 const IsoSprite emptySprite = new IsoSprite(this);

 public IsoSpriteManager() {
 IsoSprite sprite = this->emptySprite;
 sprite.name = "";
 sprite.ID = -1;
 sprite.Properties.Set(IsoFlagType.invisible);
 sprite.CurrentAnim = std::make_unique<IsoAnim>();
 sprite.CurrentAnim.ID = sprite.AnimStack.size();
 sprite.AnimStack.add(sprite.CurrentAnim);
 sprite.AnimMap.put("default", sprite.CurrentAnim);
 this->NamedMap.put(sprite.name, sprite);
 }

 void Dispose() {
 IsoSprite.DisposeAll();
 IsoAnim.DisposeAll();
 Object[] objects = this->IntMap.values();

 for (int int0 = 0; int0 < objects.length; int0++) {
 IsoSprite sprite = (IsoSprite)objects[int0];
 sprite.Dispose();
 sprite.def = nullptr;
 sprite.parentManager = nullptr;
 }

 this->IntMap.clear();
 this->NamedMap.clear();
 this->NamedMap.put(this->emptySprite.name, this->emptySprite);
 }

 IsoSprite getSprite(int gid) {
 return this->IntMap.containsKey(gid) ? this->IntMap.get(gid) : nullptr;
 }

 IsoSprite getSprite(const std::string& gid) {
 return this->NamedMap.containsKey(gid) ? this->NamedMap.get(gid) : this->AddSprite(gid);
 }

 IsoSprite getOrAddSpriteCache(const std::string& tex) {
 if (this->NamedMap.containsKey(tex) {
 return this->NamedMap.get(tex);
 } else {
 IsoSprite sprite = new IsoSprite(this);
 sprite.LoadFramesNoDirPageSimple(tex);
 this->NamedMap.put(tex, sprite);
 return sprite;
 }
 }

 IsoSprite getOrAddSpriteCache(const std::string& tex, Color col) {
 int int0 = (int)(col.r * 255.0F);
 int int1 = (int)(col.g * 255.0F);
 int int2 = (int)(col.b * 255.0F);
 std::string string = tex + "_" + int0 + "_" + int1 + "_" + int2;
 if (this->NamedMap.containsKey(string) {
 return this->NamedMap.get(string);
 } else {
 IsoSprite sprite = new IsoSprite(this);
 sprite.LoadFramesNoDirPageSimple(tex);
 this->NamedMap.put(string, sprite);
 return sprite;
 }
 }

 IsoSprite AddSprite(const std::string& tex) {
 IsoSprite sprite = new IsoSprite(this);
 sprite.LoadFramesNoDirPageSimple(tex);
 this->NamedMap.put(tex, sprite);
 return sprite;
 }

 IsoSprite AddSprite(const std::string& tex, int ID) {
 IsoSprite sprite = new IsoSprite(this);
 sprite.LoadFramesNoDirPageSimple(tex);
 if (this->NamedMap.containsKey(tex) {
 DebugLog.log("duplicate texture " + tex + " ignore ID=" + ID + ", use ID=" + this->NamedMap.get(tex).ID);
 ID = this->NamedMap.get(tex).ID;
 }

 this->NamedMap.put(tex, sprite);
 sprite.ID = ID;
 this->IntMap.put(ID, sprite);
 return sprite;
 }
}
} // namespace sprite
} // namespace iso
} // namespace zombie
