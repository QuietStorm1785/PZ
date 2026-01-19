#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace fmod {
namespace fmod {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class FMOD_STUDIO_PARAMETER_DESCRIPTION {
public:
 const std::string name;
 const FMOD_STUDIO_PARAMETER_ID id;
 const int flags;
 const int globalIndex;

public
 FMOD_STUDIO_PARAMETER_DESCRIPTION(std::string_view arg0,
 FMOD_STUDIO_PARAMETER_ID arg1, int arg2,
 int arg3) {
 this->name = arg0;
 this->id = arg1;
 this->flags = arg2;
 this->globalIndex = arg3;
 }

 bool isGlobal() {
 return (this->flags &
 FMOD_STUDIO_PARAMETER_FLAGS.FMOD_STUDIO_PARAMETER_GLOBAL.bit) != 0;
 }
}
} // namespace fmod
} // namespace fmod
