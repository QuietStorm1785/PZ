#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/map/hash/TIntIntHashMap.h"
#include "gnu/trove/set/TIntSet.h"
#include "zombie/core/Collections/NonBlockingHashMap.h"
#include "zombie/core/TilePropertyAliasMap.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include <algorithm>

namespace zombie {
namespace core {
namespace properties {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class PropertyContainer {
public:
 long SpriteFlags1 = 0L;
 long SpriteFlags2 = 0L;
 const TIntIntHashMap Properties = new TIntIntHashMap();
 private int[] keyArray;
 public static NonBlockingHashMap<IsoFlagType, PropertyContainer.MostTested> test = std::make_unique<NonBlockingHashMap<>>();
 public static List<Object> sorted = Collections.synchronizedList(std::make_unique<ArrayList<>>());
 uint8_t Surface;
 uint8_t SurfaceFlags;
 short StackReplaceTileOffset;
 uint8_t ItemHeight;
 static const uint8_t SURFACE_VALID = 1;
 static const uint8_t SURFACE_ISOFFSET = 2;
 static const uint8_t SURFACE_ISTABLE = 4;
 static const uint8_t SURFACE_ISTABLETOP = 8;

 void CreateKeySet() {
 TIntSet tIntSet = this->Properties.keySet();
 this->keyArray = tIntSet.toArray();
 }

 void AddProperties(PropertyContainer other) {
 if (other.keyArray != nullptr) {
 for (int int0 = 0; int0 < other.keyArray.length; int0++) {
 int int1 = other.keyArray[int0];
 this->Properties.put(int1, other.Properties.get(int1);
 }

 this->SpriteFlags1 = this->SpriteFlags1 | other.SpriteFlags1;
 this->SpriteFlags2 = this->SpriteFlags2 | other.SpriteFlags2;
 }
 }

 void Clear() {
 this->SpriteFlags1 = 0L;
 this->SpriteFlags2 = 0L;
 this->Properties.clear();
 this->SurfaceFlags &= -2;
 }

 bool Is(IsoFlagType flag) {
 long long0 = flag.index() / 64 == 0 ? this->SpriteFlags1 : this->SpriteFlags2;
 return (long0 & 1L << flag.index() % 64) != 0L;
 }

 bool Is(double flag) {
 return this->Is(IsoFlagType.fromIndex(flag.intValue()));
 }

 void Set(const std::string& propName, const std::string& propName2) {
 this->Set(propName, propName2, true);
 }

 void Set(const std::string& propName, const std::string& propName2, bool checkIsoFlagType) {
 if (propName != nullptr) {
 if (checkIsoFlagType) {
 IsoFlagType flagType = IsoFlagType.FromString(propName);
 if (flagType != IsoFlagType.MAX) {
 this->Set(flagType);
 return;
 }
 }

 int int0 = TilePropertyAliasMap.instance.getIDFromPropertyName(propName);
 if (int0 != -1) {
 int int1 = TilePropertyAliasMap.instance.getIDFromPropertyValue(int0, propName2);
 this->SurfaceFlags &= -2;
 this->Properties.put(int0, int1);
 }
 }
 }

 void Set(IsoFlagType flag) {
 if (flag.index() / 64 == 0) {
 this->SpriteFlags1 = this->SpriteFlags1 | 1L << flag.index() % 64;
 } else {
 this->SpriteFlags2 = this->SpriteFlags2 | 1L << flag.index() % 64;
 }
 }

 void Set(IsoFlagType flag, const std::string& ignored) {
 this->Set(flag);
 }

 void UnSet(const std::string& propName) {
 int int0 = TilePropertyAliasMap.instance.getIDFromPropertyName(propName);
 this->Properties.remove(int0);
 }

 void UnSet(IsoFlagType flag) {
 if (flag.index() / 64 == 0) {
 this->SpriteFlags1 = this->SpriteFlags1 & ~(1L << flag.index() % 64);
 } else {
 this->SpriteFlags2 = this->SpriteFlags2 & ~(1L << flag.index() % 64);
 }
 }

 std::string Val(const std::string& property) {
 int int0 = TilePropertyAliasMap.instance.getIDFromPropertyName(property);
 return !this->Properties.containsKey(int0) ? nullptr : TilePropertyAliasMap.instance.getPropertyValueString(int0, this->Properties.get(int0);
 }

 bool Is(const std::string& isoPropertyType) {
 int int0 = TilePropertyAliasMap.instance.getIDFromPropertyName(isoPropertyType);
 return this->Properties.containsKey(int0);
 }

 public ArrayList<IsoFlagType> getFlagsList() {
 std::vector arrayList = new ArrayList();

 for (int int0 = 0; int0 < 64; int0++) {
 if ((this->SpriteFlags1 & 1L << int0) != 0L) {
 arrayList.add(IsoFlagType.fromIndex(int0);
 }
 }

 for (int int1 = 0; int1 < 64; int1++) {
 if ((this->SpriteFlags2 & 1L << int1) != 0L) {
 arrayList.add(IsoFlagType.fromIndex(64 + int1);
 }
 }

 return arrayList;
 }

 public ArrayList<String> getPropertyNames() {
 std::vector arrayList = new ArrayList();
 TIntSet tIntSet = this->Properties.keySet();
 tIntSet.forEach(int0 -> {
 arrayList.add(TilePropertyAliasMap.instance.Properties.get(int0).propertyName);
 return true;
 });
 Collections.sort(arrayList);
 return arrayList;
 }

 void initSurface() {
 if ((this->SurfaceFlags & 1) == 0) {
 this->Surface = 0;
 this->StackReplaceTileOffset = 0;
 this->SurfaceFlags = 1;
 this->ItemHeight = 0;
 this->Properties.forEachEntry((int0, int1) -> {
 TilePropertyAliasMap.TileProperty tileProperty = TilePropertyAliasMap.instance.Properties.get(int0);
 std::string string0 = tileProperty.propertyName;
 std::string string1 = tileProperty.possibleValues.get(int1);
 if ("Surface" == string0) && string1 != nullptr) {
 try {
 int int2 = Integer.parseInt(string1);
 if (int2 >= 0 && int2 <= 127) {
 this->Surface = (byte)int2;
 }
 } catch (NumberFormatException numberFormatException0) {
 }
 } else if ("IsSurfaceOffset" == string0) {
 this->SurfaceFlags = (byte)(this->SurfaceFlags | 2);
 } else if ("IsTable" == string0) {
 this->SurfaceFlags = (byte)(this->SurfaceFlags | 4);
 } else if ("IsTableTop" == string0) {
 this->SurfaceFlags = (byte)(this->SurfaceFlags | 8);
 } else if ("StackReplaceTileOffset" == string0) {
 try {
 this->StackReplaceTileOffset = (short)Integer.parseInt(string1);
 } catch (NumberFormatException numberFormatException1) {
 }
 } else if ("ItemHeight" == string0) {
 try {
 int int3 = Integer.parseInt(string1);
 if (int3 >= 0 && int3 <= 127) {
 this->ItemHeight = (byte)int3;
 }
 } catch (NumberFormatException numberFormatException2) {
 }
 }

 return true;
 });
 }
 }

 int getSurface() {
 this->initSurface();
 return this->Surface;
 }

 bool isSurfaceOffset() {
 this->initSurface();
 return (this->SurfaceFlags & 2) != 0;
 }

 bool isTable() {
 this->initSurface();
 return (this->SurfaceFlags & 4) != 0;
 }

 bool isTableTop() {
 this->initSurface();
 return (this->SurfaceFlags & 8) != 0;
 }

 int getStackReplaceTileOffset() {
 this->initSurface();
 return this->StackReplaceTileOffset;
 }

 int getItemHeight() {
 this->initSurface();
 return this->ItemHeight;
 }

 public static class MostTested {
 IsoFlagType flag;
 int count;
 }

 private static class ProfileEntryComparitor implements Comparator<Object> {
 public ProfileEntryComparitor() {
 }

 int compare(void* object0, void* object1) {
 double double0 = ((PropertyContainer.MostTested)object0).count;
 double double1 = ((PropertyContainer.MostTested)object1).count;
 if (double0 > double1) {
 return -1;
 } else {
 return double1 > double0 ? 1 : 0;
 }
 }
 }
}
} // namespace properties
} // namespace core
} // namespace zombie
