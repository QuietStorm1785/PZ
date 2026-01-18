#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/debug/BooleanDebugOption.h"

namespace zombie {
namespace debug {
namespace options {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class Weather : public OptionGroup {
public:
 const BooleanDebugOption Fx = newDebugOnlyOption(this->Group, "Fx", true);
 const BooleanDebugOption Snow = newDebugOnlyOption(this->Group, "Snow", true);
 const BooleanDebugOption WaterPuddles = newDebugOnlyOption(this->Group, "WaterPuddles", true);

 public Weather() {
 super("Weather");
 }
}
} // namespace options
} // namespace debug
} // namespace zombie
