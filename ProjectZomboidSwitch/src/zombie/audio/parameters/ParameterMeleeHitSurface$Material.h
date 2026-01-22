#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace audio {
namespace parameters {

enum class ParameterMeleeHitSurface {
   Default(0),
   Body(1),
   Fabric(2),
   Glass(3),
   Head(4),
   Metal(5),
   Plastic(6),
   Stone(7),
   Wood(8),
   GarageDoor(9),
   MetalDoor(10),
   MetalGate(11),
   PrisonMetalDoor(12),
   SlidingGlassDoor(13),
   WoodDoor(14),
   WoodGate(15),
   Tree(16);

    const int label;

   private ParameterMeleeHitSurface$Material(int var3) {
      this.label = var3;
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
