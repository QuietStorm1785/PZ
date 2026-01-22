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
    float x;
    float y;
    float z;
    float size;
    float vx;
    float vy;
    float speed;
    int life;
    int lifeTime;
    Zone zone;

   public ParticlesFire$Vortice(ParticlesFire var1) {
      this.this$0 = var1;
   }
}
} // namespace iso
} // namespace zombie
