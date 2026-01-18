#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace zombie {
namespace core {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class TilePropertyAliasMap {
public:
 static const TilePropertyAliasMap instance = new TilePropertyAliasMap();
 public HashMap<String, Integer> PropertyToID = std::make_unique<HashMap<>>();
 public ArrayList<TilePropertyAliasMap.TileProperty> Properties = std::make_unique<ArrayList<>>();

 void Generate(ArrayList<String>> hashMap) {
 this->Properties.clear();
 this->PropertyToID.clear();

 for (Entry entry : hashMap.entrySet()) {
 std::string string0 = (String)entry.getKey();
 std::vector arrayList0 = (ArrayList)entry.getValue();
 this->PropertyToID.put(string0, this->Properties.size());
 TilePropertyAliasMap.TileProperty tileProperty = new TilePropertyAliasMap.TileProperty();
 this->Properties.add(tileProperty);
 tileProperty.propertyName = string0;
 tileProperty.possibleValues.addAll(arrayList0);
 std::vector arrayList1 = tileProperty.possibleValues;

 for (int int0 = 0; int0 < arrayList1.size(); int0++) {
 std::string string1 = (String)arrayList1.get(int0);
 tileProperty.idMap.put(string1, int0);
 }
 }
 }

 int getIDFromPropertyName(const std::string& string) {
 return !this->PropertyToID.containsKey(string) ? -1 : this->PropertyToID.get(string);
 }

 int getIDFromPropertyValue(int int0, const std::string& string) {
 TilePropertyAliasMap.TileProperty tileProperty = this->Properties.get(int0);
 if (tileProperty.possibleValues.empty()) {
 return 0;
 } else {
 return !tileProperty.idMap.containsKey(string) ? 0 : tileProperty.idMap.get(string);
 }
 }

 std::string getPropertyValueString(int int0, int int1) {
 TilePropertyAliasMap.TileProperty tileProperty = this->Properties.get(int0);
 return tileProperty.possibleValues.empty() ? "" : tileProperty.possibleValues.get(int1);
 }

 public static class TileProperty {
 std::string propertyName;
 public ArrayList<String> possibleValues = std::make_unique<ArrayList<>>();
 public HashMap<String, Integer> idMap = std::make_unique<HashMap<>>();
 }
}
} // namespace core
} // namespace zombie
