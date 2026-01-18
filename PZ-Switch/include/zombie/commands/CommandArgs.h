#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace commands {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

public
@interface CommandArgs {
 std::string DEFAULT_OPTIONAL_ARGUMENT = "no value";

 String[] required() default {};

 std::string optional();

 std::string argName();

 bool varArgs();
}
} // namespace commands
} // namespace zombie
