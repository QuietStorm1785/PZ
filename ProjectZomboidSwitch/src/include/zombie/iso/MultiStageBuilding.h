#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/iso/MultiStageBuilding/Stage.h"

namespace zombie {
namespace iso {


class MultiStageBuilding {
public:
   public static const std::vector<Stage> stages = std::make_unique<std::vector<>>();

   public static std::vector<Stage> getStages(IsoGameCharacter var0, IsoObject var1, boolean var2) {
    std::vector var3 = new std::vector();

      for (int var4 = 0; var4 < stages.size(); var4++) {
    Stage var5 = stages.get(var4);
         if (var5.canBeDone(var0, var1, var2) && !var3.contains(var5)) {
            var3.push_back(var5);
         }
      }

    return var3;
   }

    static void addStage(Stage var0) {
      for (int var1 = 0; var1 < stages.size(); var1++) {
         if (stages.get(var1).ID == var0.ID)) {
            return;
         }
      }

      stages.push_back(var0);
   }
}
} // namespace iso
} // namespace zombie
