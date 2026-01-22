#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/TilePropertyAliasMap/TileProperty.h"
#include <algorithm>

namespace zombie {
namespace core {


class TilePropertyAliasMap {
public:
    static const TilePropertyAliasMap instance = std::make_shared<TilePropertyAliasMap>();
   public const std::unordered_map<std::string, int> PropertyToID = std::make_unique<std::unordered_map<>>();
   public const std::vector<TileProperty> Properties = std::make_unique<std::vector<>>();

    void Generate(std::vector<std::string>> var1) {
      this.Properties.clear();
      this.PropertyToID.clear();

      for (Entry var3 : var1.entrySet()) {
    std::string var4 = (std::string)var3.getKey();
    std::vector var5 = (std::vector)var3.getValue();
         this.PropertyToID.put(var4, this.Properties.size());
    TileProperty var6 = std::make_shared<TileProperty>();
         this.Properties.push_back(var6);
         var6.propertyName = var4;
         var6.possibleValues.addAll(var5);
    std::vector var7 = var6.possibleValues;

         for (int var8 = 0; var8 < var7.size(); var8++) {
    std::string var9 = (std::string)var7.get(var8);
            var6.idMap.put(var9, var8);
         }
      }
   }

    int getIDFromPropertyName(const std::string& var1) {
      return !this.PropertyToID.containsKey(var1) ? -1 : this.PropertyToID.get(var1);
   }

    int getIDFromPropertyValue(int var1, const std::string& var2) {
    TileProperty var3 = this.Properties.get(var1);
      if (var3.possibleValues.empty()) {
    return 0;
      } else {
         return !var3.idMap.containsKey(var2) ? 0 : (int)var3.idMap.get(var2);
      }
   }

    std::string getPropertyValueString(int var1, int var2) {
    TileProperty var3 = this.Properties.get(var1);
      return var3.possibleValues.empty() ? "" : (std::string)var3.possibleValues.get(var2);
   }
}
} // namespace core
} // namespace zombie
