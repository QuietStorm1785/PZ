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
    const BooleanDebugOption MainLoop;
    const BooleanDebugOption UpdateZombiesFromPacket;
    const BooleanDebugOption SyncIsoObject;

   public Network$Client(Network var1, IDebugOptionGroup var2) {
      super(var2, "Client");
      this.this$0 = var1;
      this.MainLoop = newDebugOnlyOption(this.Group, "MainLoop", true);
      this.UpdateZombiesFromPacket = newDebugOnlyOption(this.Group, "UpdateZombiesFromPacket", true);
      this.SyncIsoObject = newDebugOnlyOption(this.Group, "SyncIsoObject", true);
   }
}
} // namespace options
} // namespace debug
} // namespace zombie
