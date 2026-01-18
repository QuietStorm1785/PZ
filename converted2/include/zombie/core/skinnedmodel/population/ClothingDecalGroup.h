#pragma once
#include "javax/xml/bind/annotation/XmlElement.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace population {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ClothingDecalGroup {
public:
        name = "name"
    )
    std::string m_Name;
        name = "decal"
    )
    public final ArrayList<String> m_Decals = std::make_unique<ArrayList<>>();
        name = "group"
    )
    public final ArrayList<String> m_Groups = std::make_unique<ArrayList<>>();
      private
        final ArrayList<String> tempDecals = std::make_unique<ArrayList<>>();

        std::string getRandomDecal() {
          this.tempDecals.clear();
          this.getDecals(this.tempDecals);
          std::string string = OutfitRNG.pickRandom(this.tempDecals);
          return string = = null ? null : string;
        }

        void getDecals(ArrayList<String> arrayList) {
          arrayList.addAll(this.m_Decals);

          for (int int0 = 0; int0 < this.m_Groups.size(); int0++) {
            ClothingDecalGroup clothingDecalGroup1 =
                ClothingDecals.instance.FindGroup(this.m_Groups.get(int0));
            if (clothingDecalGroup1 != nullptr) {
              clothingDecalGroup1.getDecals(arrayList);
            }
          }
        }
}
} // namespace population
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
