#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/FMODLocalParameter.h"

namespace zombie {
namespace audio {
namespace parameters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ParameterFireSize : public FMODLocalParameter {
public:
 int size = 0;

 public ParameterFireSize() {
 super("FireSize");
 }

 float calculateCurrentValue() {
 return this->size;
 }

 void setSize(int _size) {
 this->size = _size;
 }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
