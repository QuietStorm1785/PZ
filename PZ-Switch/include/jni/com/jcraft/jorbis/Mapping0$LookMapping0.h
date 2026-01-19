#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/jcraft/jorbis/Mapping0/InfoMapping0.h"

namespace com {
namespace jcraft {
namespace jorbis {


class Mapping0 {
:
    int ch;
   float[][] decay;
   FuncFloor[] floor_func;
   Object[] floor_look;
   Object[] floor_state;
    int lastframe;
    InfoMapping0 map;
    InfoMode mode;
   PsyLook[] psy_look;
   FuncResidue[] residue_func;
   Object[] residue_look;
   FuncTime[] time_func;
   Object[] time_look;

   Mapping0$LookMapping0(Mapping0 var1) {
      this.this$0 = var1;
   }
}
} // namespace jorbis
} // namespace jcraft
} // namespace com
