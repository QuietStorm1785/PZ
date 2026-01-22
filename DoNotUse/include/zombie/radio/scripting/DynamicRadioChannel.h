#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/radio/ChannelCategory.h"

namespace zombie {
namespace radio {
namespace scripting {


class DynamicRadioChannel : public RadioChannel {
public:
    public DynamicRadioChannel(const std::string& var1, int var2, ChannelCategory var3) {
      super(var1, var2, var3);
   }

    public DynamicRadioChannel(const std::string& var1, int var2, ChannelCategory var3, const std::string& var4) {
      super(var1, var2, var3, var4);
   }

    void LoadAiringBroadcast(const std::string& var1, int var2) {
   }
}
} // namespace scripting
} // namespace radio
} // namespace zombie
