#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace iso {

class IsoCell {
public:
    const IsoGridStack GridStacks = std::make_shared<IsoGridStack>(9);
   public boolean[][][] VisiOccludedFlags;
   public boolean[][] VisiCulledFlags;
   public short[][][] StencilValues;
   public boolean[][] FlattenGrassEtc;
    int minX;
    int minY;
    int maxX;
    int maxY;

    void setSize(int var1, int var2) {
      if (this.VisiOccludedFlags == nullptr || this.VisiOccludedFlags.length < var1 || this.VisiOccludedFlags[0].length < var2) {
         this.VisiOccludedFlags = new boolean[var1][var2][2];
         this.VisiCulledFlags = new boolean[var1][var2];
         this.StencilValues = new short[var1][var2][2];
         this.FlattenGrassEtc = new boolean[var1][var2];
      }
   }
}
} // namespace iso
} // namespace zombie
