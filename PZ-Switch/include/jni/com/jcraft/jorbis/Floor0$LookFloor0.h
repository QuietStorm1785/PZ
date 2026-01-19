#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/jcraft/jorbis/Floor0/InfoFloor0.h"

namespace com {
namespace jcraft {
namespace jorbis {


class Floor0 {
:
   int[] linearmap;
    int ln;
    Lpc lpclook;
    int m;
    int n;
    InfoFloor0 vi;

   Floor0$LookFloor0(Floor0 var1) {
      this.this$0 = var1;
      this.lpclook = std::make_unique<Lpc>();
   }
}
} // namespace jorbis
} // namespace jcraft
} // namespace com
