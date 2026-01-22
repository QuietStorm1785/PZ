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

enum class Thermoregulator_tryouts {
   Default,
   MetabolicRateInc,
   MetabolicRateDec,
   BodyHeat,
   CoreHeatExpand,
   CoreHeatContract,
   SkinCelcius,
   SkinCelciusContract,
   SkinCelciusExpand,
   PrimaryDelta,
   SecondaryDelta;
}
} // namespace BodyDamage
} // namespace characters
} // namespace zombie
