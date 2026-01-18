#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/FMODGlobalParameter.h"
#include "zombie/core/Core.h"

namespace zombie {
namespace audio {
namespace parameters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ParameterMusicLibrary : public FMODGlobalParameter {
public:
 public ParameterMusicLibrary() {
 super("MusicLibrary");
 }

 float calculateCurrentValue() {
 return switch() {
 case 2 -> ParameterMusicLibrary.Library.EarlyAccess.label;
 case 3 -> ParameterMusicLibrary.Library.Random.label;
 default -> ParameterMusicLibrary.Library.Official.label;
 };
 }

 public static enum Library {
 Official(0),
 EarlyAccess(1),
 Random(2);

 const int label;

 private Library(int int1) {
 this->label = int1;
 }
 }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
