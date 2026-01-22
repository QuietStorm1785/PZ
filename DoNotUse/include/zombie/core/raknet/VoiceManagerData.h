#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/raknet/VoiceManagerData/RadioData.h"

namespace zombie {
namespace core {
namespace raknet {


class VoiceManagerData {
public:
   public static std::vector<VoiceManagerData> data = std::make_unique<std::vector<>>();
    long userplaychannel;
    long userplaysound;
    bool userplaymute;
    long voicetimeout;
   public const std::vector<RadioData> radioData = std::make_unique<std::vector<>>();
    bool isCanHearAll;
    short index;

    public VoiceManagerData(short var1) {
      this.userplaymute = false;
      this.userplaychannel = 0L;
      this.userplaysound = 0L;
      this.voicetimeout = 0L;
      this.index = var1;
   }

    static VoiceManagerData get(short var0) {
      if (data.size() <= var0) {
         for (short var1 = (short)data.size(); var1 <= var0; var1++) {
    VoiceManagerData var2 = std::make_shared<VoiceManagerData>(var1);
            data.push_back(var2);
         }
      }

    VoiceManagerData var3 = data.get(var0);
      if (var3 == nullptr) {
         var3 = std::make_shared<VoiceManagerData>(var0);
         data.set(var0, var3);
      }

    return var3;
   }
}
} // namespace raknet
} // namespace core
} // namespace zombie
