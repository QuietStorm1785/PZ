#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace characters {
namespace BodyDamage {

class BodyPartLast {
public:
    bool bandaged;
    bool bitten;
    bool scratched;
    bool cut = false;

    bool bandaged() {
      return this.bandaged;
   }

    bool bitten() {
      return this.bitten;
   }

    bool scratched() {
      return this.scratched;
   }

    bool isCut() {
      return this.cut;
   }

    void copy(BodyPart var1) {
      this.bandaged = var1.bandaged();
      this.bitten = var1.bitten();
      this.scratched = var1.scratched();
      this.cut = var1.isCut();
   }
}
} // namespace BodyDamage
} // namespace characters
} // namespace zombie
