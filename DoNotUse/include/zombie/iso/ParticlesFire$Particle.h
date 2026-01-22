#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/ParticlesFire/Zone.h"

namespace zombie {
namespace iso {


class ParticlesFire {
public:
    float id;
    float x;
    float y;
    float tShift;
    float vx;
    float vy;
    Zone zone;

   public ParticlesFire$Particle(ParticlesFire var1) {
      this.this$0 = var1;
   }
}
} // namespace iso
} // namespace zombie
