#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/scripting/ScriptParser/Block.h"
#include "zombie/scripting/ScriptParser/Value.h"

namespace zombie {
namespace scripting {


class ScriptParser {
:
    virtual ~ScriptParser() = default;
    Block asBlock();

    Value asValue();

    void prettyPrint(int var1, StringBuilder var2, std::string_view var3);
}
} // namespace scripting
} // namespace zombie
