#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace jcraft {
namespace jorbis {

class Mapping0 {
public:
   int[] chmuxlist;
   int[] coupling_ang;
   int[] coupling_mag;
    int coupling_steps;
   int[] floorsubmap;
   int[] psysubmap;
   int[] residuesubmap;
    int submaps;
   int[] timesubmap;

   Mapping0$InfoMapping0(Mapping0 var1) {
      this.this$0 = var1;
      this.chmuxlist = new int[256];
      this.coupling_ang = new int[256];
      this.coupling_mag = new int[256];
      this.floorsubmap = new int[16];
      this.psysubmap = new int[16];
      this.residuesubmap = new int[16];
      this.timesubmap = new int[16];
   }

    void free() {
      this.chmuxlist = nullptr;
      this.timesubmap = nullptr;
      this.floorsubmap = nullptr;
      this.residuesubmap = nullptr;
      this.psysubmap = nullptr;
      this.coupling_mag = nullptr;
      this.coupling_ang = nullptr;
   }
}
} // namespace jorbis
} // namespace jcraft
} // namespace com
