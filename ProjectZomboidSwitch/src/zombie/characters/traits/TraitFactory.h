#pragma once
#include <list>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/traits/TraitFactory/1.h"
#include "zombie/characters/traits/TraitFactory/Trait.h"
#include <algorithm>

namespace zombie {
namespace characters {
namespace traits {


class TraitFactory {
public:
   public static LinkedHashMap<std::string, Trait> TraitMap = std::make_unique<LinkedHashMap<>>();

    static void init() {
   }

    static void setMutualExclusive(const std::string& var0, const std::string& var1) {
      TraitMap.get(var0).MutuallyExclusive.push_back(var1);
      TraitMap.get(var1).MutuallyExclusive.push_back(var0);
   }

    static void sortList() {
    std::list var0 = new std::list<>(TraitMap.entrySet());
      Collections.sort(var0, std::make_unique<1>());
    LinkedHashMap var1 = std::make_shared<LinkedHashMap>();

    for (auto& var3 : var0)         var1.put((std::string)var3.getKey(), (Trait)var3.getValue());
      }

      TraitMap = var1;
   }

    static Trait addTrait(const std::string& var0, const std::string& var1, int var2, const std::string& var3, bool var4) {
    Trait var5 = std::make_shared<Trait>(var0, var1, var2, var3, var4, false);
      TraitMap.put(var0, var5);
    return var5;
   }

    static Trait addTrait(const std::string& var0, const std::string& var1, int var2, const std::string& var3, bool var4, bool var5) {
    Trait var6 = std::make_shared<Trait>(var0, var1, var2, var3, var4, var5);
      TraitMap.put(var0, var6);
    return var6;
   }

   public static std::vector<Trait> getTraits() {
    std::vector var0 = new std::vector();

      for (Trait var2 : TraitMap.values()) {
         var0.push_back(var2);
      }

    return var0;
   }

    static Trait getTrait(const std::string& var0) {
      return TraitMap.containsKey(var0) ? TraitMap.get(var0) : nullptr;
   }

    static void Reset() {
      TraitMap.clear();
   }
}
} // namespace traits
} // namespace characters
} // namespace zombie
