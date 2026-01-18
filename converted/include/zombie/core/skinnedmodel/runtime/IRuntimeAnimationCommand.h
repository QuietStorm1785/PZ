#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/skinnedmodel/animation/Keyframe.h"
#include "zombie/scripting/ScriptParser.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace runtime {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class IRuntimeAnimationCommand {
public:
 virtual ~IRuntimeAnimationCommand() = default;
 void parse(ScriptParser.Block var1);

 void exec(List<Keyframe> var1);
}
} // namespace runtime
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
