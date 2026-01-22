#pragma once
#include <sstream>
#include <string>
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
public:
    virtual ~ScriptParser() = default;
    Block asBlock();

    Value asValue();

    void prettyPrint(int var1, std::stringstream var2, const std::string& var3);
}
} // namespace scripting
} // namespace zombie
