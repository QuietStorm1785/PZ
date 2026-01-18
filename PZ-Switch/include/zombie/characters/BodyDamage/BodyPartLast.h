#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace characters {
namespace BodyDamage {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class BodyPartLast {
public:
 bool bandaged;
 bool bitten;
 bool scratched;
 bool cut = false;

 bool bandaged() { return this->bandaged; }

 bool bitten() { return this->bitten; }

 bool scratched() { return this->scratched; }

 bool isCut() { return this->cut; }

 void copy(BodyPart other) {
 this->bandaged = other.bandaged();
 this->bitten = other.bitten();
 this->scratched = other.scratched();
 this->cut = other.isCut();
 }
}
} // namespace BodyDamage
} // namespace characters
} // namespace zombie
