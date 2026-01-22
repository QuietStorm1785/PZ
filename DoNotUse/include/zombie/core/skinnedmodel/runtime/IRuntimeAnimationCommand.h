#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/skinnedmodel/animation/Keyframe.h"
#include "zombie/scripting/ScriptParser/Block.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace runtime {


class IRuntimeAnimationCommand {
public:
    virtual ~IRuntimeAnimationCommand() = default;
    void parse(Block var1);

    void exec(List<Keyframe> var1);
}
} // namespace runtime
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
