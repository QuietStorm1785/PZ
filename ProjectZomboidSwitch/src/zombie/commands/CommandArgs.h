#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace commands {


public @interface CommandArgs {
    std::string DEFAULT_OPTIONAL_ARGUMENT = "no value";

   std::string[] required() default {};

    std::string optional();

    std::string argName();

    bool varArgs();
}
} // namespace commands
} // namespace zombie
