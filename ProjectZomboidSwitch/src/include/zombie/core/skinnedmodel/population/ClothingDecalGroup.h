#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/annotation/XmlElement.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace population {


class ClothingDecalGroup {
public:
    std::string m_Name;
   public const std::vector<std::string> m_Decals = std::make_unique<std::vector<>>();
   public const std::vector<std::string> m_Groups = std::make_unique<std::vector<>>();
   private const std::vector<std::string> tempDecals = std::make_unique<std::vector<>>();

    std::string getRandomDecal() {
      this.tempDecals.clear();
      this.getDecals(this.tempDecals);
    std::string var1 = (std::string)OutfitRNG.pickRandom(this.tempDecals);
    return var1 = = nullptr ? nullptr : var1;
   }

    void getDecals(std::vector<std::string> var1) {
      var1.addAll(this.m_Decals);

      for (int var2 = 0; var2 < this.m_Groups.size(); var2++) {
    ClothingDecalGroup var3 = ClothingDecals.instance.FindGroup(this.m_Groups.get(var2));
         if (var3 != nullptr) {
            var3.getDecals(var1);
         }
      }
   }
}
} // namespace population
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
