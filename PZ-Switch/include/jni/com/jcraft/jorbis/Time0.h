#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/jcraft/jogg/Buffer.h"

namespace com {
namespace jcraft {
namespace jorbis {


class Time0 :  FuncTime {
:
    void free_info(void* var1) {
   }

    void free_look(void* var1) {
   }

    int inverse(Block var1, void* var2, float[] var3, float[] var4) {
    return 0;
   }

    void* look(DspState var1, InfoMode var2, void* var3) {
      return "";
   }

    void pack(void* var1, Buffer var2) {
   }

    void* unpack(Info var1, Buffer var2) {
      return "";
   }
}
} // namespace jorbis
} // namespace jcraft
} // namespace com
