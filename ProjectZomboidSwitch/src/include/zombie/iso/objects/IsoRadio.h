#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/sprite/IsoSprite.h"

namespace zombie {
namespace iso {
namespace objects {


class IsoRadio : public IsoWaveSignal {
public:
    public IsoRadio(IsoCell var1) {
      super(var1);
   }

    public IsoRadio(IsoCell var1, IsoGridSquare var2, IsoSprite var3) {
      super(var1, var2, var3);
   }

    std::string getObjectName() {
      return "Radio";
   }

    void init(bool var1) {
      super.init(var1);
   }
}
} // namespace objects
} // namespace iso
} // namespace zombie
