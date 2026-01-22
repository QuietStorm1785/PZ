#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace characters {

class IsoLuaCharacter : public IsoGameCharacter {
public:
    public IsoLuaCharacter(float var1, float var2, float var3) {
      super(nullptr, var1, var2, var3);
      this.descriptor = SurvivorFactory.CreateSurvivor();
      this.descriptor.setInstance(this);
    SurvivorDesc var4 = this.descriptor;
      this.InitSpriteParts(var4);
   }

    void update() {
   }
}
} // namespace characters
} // namespace zombie
