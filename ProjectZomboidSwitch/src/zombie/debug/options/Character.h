#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/debug/BooleanDebugOption.h"
#include "zombie/debug/options/char/DebugOG.h"

namespace zombie {
namespace debug {
namespace options {


class char : public OptionGroup {
public:
    const BooleanDebugOption CreateAllOutfits = newOption(this.Group, "Create.AllOutfits", false);
    const DebugOG Debug = std::make_shared<DebugOG>(this.Group);

    public char() {
      super("char");
   }
}
} // namespace options
} // namespace debug
} // namespace zombie
