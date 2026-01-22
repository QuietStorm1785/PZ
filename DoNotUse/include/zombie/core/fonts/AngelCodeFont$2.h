#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/list/array/TShortArrayList.h"
#include "gnu/trove/procedure/TShortObjectProcedure.h"
#include "zombie/core/fonts/AngelCodeFont/CharDef.h"
#include <algorithm>

namespace zombie {
namespace core {
namespace fonts {


class AngelCodeFont {
public:
   AngelCodeFont$2(AngelCodeFont var1) {
      this.this$0 = var1;
   }

    bool execute(short var1, TShortArrayList var2) {
    CharDef var3 = this.this$0.chars[var1];
      var3.kerningSecond = new short[var2.size() / 2];
      var3.kerningAmount = new short[var2.size() / 2];
    int var4 = 0;

      for (byte var5 = 0; var5 < var2.size(); var5 += 2) {
         var3.kerningSecond[var4] = var2.get(var5);
         var3.kerningAmount[var4] = var2.get(var5 + 1);
         var4++;
      }

      short[] var9 = Arrays.copyOf(var3.kerningSecond, var3.kerningSecond.length);
      short[] var6 = Arrays.copyOf(var3.kerningAmount, var3.kerningAmount.length);
      Arrays.sort(var9);

      for (int var7 = 0; var7 < var9.length; var7++) {
         for (int var8 = 0; var8 < var3.kerningSecond.length; var8++) {
            if (var3.kerningSecond[var8] == var9[var7]) {
               var3.kerningAmount[var7] = var6[var8];
               break;
            }
         }
      }

      var3.kerningSecond = var9;
    return true;
   }
}
} // namespace fonts
} // namespace core
} // namespace zombie
