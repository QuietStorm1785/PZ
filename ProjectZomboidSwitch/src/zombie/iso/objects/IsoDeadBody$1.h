#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoZombie.h"

namespace zombie {
namespace iso {
namespace objects {


class IsoDeadBody {
public:
    IsoZombie initialValue() {
      return std::make_shared<IsoZombie>(nullptr);
   }
}
} // namespace objects
} // namespace iso
} // namespace zombie
