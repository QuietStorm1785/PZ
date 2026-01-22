#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/IsoCamera.h"

namespace zombie {
namespace characters {


class IsoDummyCameraCharacter : public IsoGameCharacter {
public:
    public IsoDummyCameraCharacter(float var1, float var2, float var3) {
      super(nullptr, var1, var2, var3);
      IsoCamera.CamCharacter = this;
   }

    void update() {
   }
}
} // namespace characters
} // namespace zombie
