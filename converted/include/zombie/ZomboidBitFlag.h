#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/SpriteDetails/IsoObjectType.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ZomboidBitFlag {
public:
 EnumSet<IsoFlagType> isoFlagTypeES = EnumSet.noneOf(IsoFlagType.class);

 public ZomboidBitFlag(int size) {
 }

 public ZomboidBitFlag(ZomboidBitFlag fl) {
 if (fl != nullptr) {
 this->isoFlagTypeES.addAll(fl.isoFlagTypeES);
 }
 }

 void set(int off, bool b) {
 if (off < IsoFlagType.MAX.index()) {
 if (b) {
 this->isoFlagTypeES.add(IsoFlagType.fromIndex(off);
 } else {
 this->isoFlagTypeES.remove(IsoFlagType.fromIndex(off);
 }
 }
 }

 void clear() {
 this->isoFlagTypeES.clear();
 }

 bool isSet(int off) {
 return this->isoFlagTypeES.contains(IsoFlagType.fromIndex(off);
 }

 bool isSet(IsoFlagType flag) {
 return this->isoFlagTypeES.contains(flag);
 }

 void set(IsoFlagType flag, bool b) {
 if (b) {
 this->isoFlagTypeES.add(flag);
 } else {
 this->isoFlagTypeES.remove(flag);
 }
 }

 bool isSet(IsoObjectType flag) {
 return this->isSet(flag.index());
 }

 void set(IsoObjectType flag, bool b) {
 this->set(flag.index(), b);
 }

 void Or(ZomboidBitFlag zomboidBitFlag0) {
 this->isoFlagTypeES.addAll(zomboidBitFlag0.isoFlagTypeES);
 }

 void save(DataOutputStream output) {
 }

 void load(DataInputStream input) {
 }

 void getFromLong(long l) {
 }
}
} // namespace zombie
