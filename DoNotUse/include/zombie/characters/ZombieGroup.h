#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/SandboxOptions.h"
#include "zombie/ai/ZombieGroupManager.h"
#include "zombie/iso/IsoUtils.h"

namespace zombie {
namespace characters {


class ZombieGroup {
public:
   private const std::vector<IsoZombie> members = std::make_unique<std::vector<>>();
    float lastSpreadOutTime;

    ZombieGroup reset() {
      this.members.clear();
      this.lastSpreadOutTime = -1.0F;
    return this;
   }

    void add(IsoZombie var1) {
      if (!this.members.contains(var1)) {
         if (var1.group != nullptr) {
            var1.group.remove(var1);
         }

         this.members.push_back(var1);
         var1.group = this;
      }
   }

    void remove(IsoZombie var1) {
      this.members.remove(var1);
      var1.group = nullptr;
   }

    IsoZombie getLeader() {
      return this.members.empty() ? nullptr : this.members.get(0);
   }

    bool isEmpty() {
      return this.members.empty();
   }

    int size() {
      return this.members.size();
   }

    void update() {
    int var1 = SandboxOptions.instance.zombieConfig.RallyTravelDistance.getValue();

      for (int var2 = 0; var2 < this.members.size(); var2++) {
    IsoZombie var3 = this.members.get(var2);
    float var4 = 0.0F;
         if (var2 > 0) {
            var4 = IsoUtils.DistanceToSquared(this.members.get(0).getX(), this.members.get(0).getY(), var3.getX(), var3.getY());
         }

         if (var3.group != this || var4 > var1 * var1 || !ZombieGroupManager.instance.shouldBeInGroup(var3)) {
            if (var3.group == this) {
               var3.group = nullptr;
            }

            this.members.remove(var2--);
         }
      }
   }
}
} // namespace characters
} // namespace zombie
