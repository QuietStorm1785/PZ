#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/professions/ProfessionFactory/Profession.h"
#include <algorithm>

namespace zombie {
namespace characters {
namespace professions {


class ProfessionFactory {
public:
   public static LinkedHashMap<std::string, Profession> ProfessionMap = std::make_unique<LinkedHashMap<>>();

    static void init() {
   }

    static Profession addProfession(const std::string& var0, const std::string& var1, const std::string& var2, int var3) {
    Profession var4 = std::make_shared<Profession>(var0, var1, var2, var3, "");
      ProfessionMap.put(var0, var4);
    return var4;
   }

    static Profession getProfession(const std::string& var0) {
      for (Profession var2 : ProfessionMap.values()) {
         if (var2.type == var0)) {
    return var2;
         }
      }

    return nullptr;
   }

   public static std::vector<Profession> getProfessions() {
    std::vector var0 = new std::vector();

      for (Profession var2 : ProfessionMap.values()) {
         var0.push_back(var2);
      }

    return var0;
   }

    static void Reset() {
      ProfessionMap.clear();
   }
}
} // namespace professions
} // namespace characters
} // namespace zombie
