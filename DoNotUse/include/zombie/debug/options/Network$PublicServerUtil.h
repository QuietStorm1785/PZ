#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/debug/BooleanDebugOption.h"

namespace zombie {
namespace debug {
namespace options {


class Network {
public:
    const BooleanDebugOption Enabled;

   public Network$PublicServerUtil(Network var1, IDebugOptionGroup var2) {
      super(var2, "PublicServerUtil");
      this.this$0 = var1;
      this.Enabled = newDebugOnlyOption(this.Group, "Enabled", true);
   }
}
} // namespace options
} // namespace debug
} // namespace zombie
