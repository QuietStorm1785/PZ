#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace sixlegs {
namespace png {

class StateMachine {
public:
    static const int STATE_START = 0;
    static const int STATE_SAW_IHDR = 1;
    static const int STATE_SAW_IHDR_NO_PLTE = 2;
    static const int STATE_SAW_PLTE = 3;
    static const int STATE_IN_IDAT = 4;
    static const int STATE_AFTER_IDAT = 5;
    static const int STATE_END = 6;
    PngImage png;
    int state = 0;
    int type;

    public StateMachine(PngImage var1) {
      this.png = var1;
   }

    int getState() {
      return this.state;
   }

    int getType() {
      return this.type;
   }

    void nextState(int var1) {
      this.state = nextState(this.png, this.state, this.type = var1);
   }

    static int nextState(PngImage var0, int var1, int var2) {
      for (int var3 = 0; var3 < 4; var3++) {
    int var4 = 0xFF & var2 >>> 8 * var3;
         if (var4 < 65 || var4 > 90 && var4 < 97 || var4 > 122) {
            throw PngException("Corrupted chunk type: 0x" + int.toHexString(var2), true);
         }
      }

      if (PngConstants.isPrivate(var2) && !PngConstants.isAncillary(var2)) {
         throw PngException("Private critical chunk encountered: " + PngConstants.getChunkName(var2), true);
      } else {
         switch (var1) {
            case 0:
               if (var2 == 1229472850) {
    return 1;
               }

               throw PngException("IHDR chunk must be first chunk", true);
            case 1:
            case 2:
               switch (var2) {
                  case 1229209940:
                     errorIfPaletted(var0);
    return 4;
                  case 1347179589:
    return 3;
                  case 1649100612:
    return 2;
                  case 1749635924:
                     throw PngException("PLTE must precede hIST", true);
                  case 1951551059:
                     errorIfPaletted(var0);
    return 2;
                  default:
    return var1;
               }
            case 3:
               switch (var2) {
                  case 1229209940:
    return 4;
                  case 1229278788:
                     throw PngException("Required data chunk(s) not found", true);
                  case 1665684045:
                  case 1732332865:
                  case 1766015824:
                  case 1933723988:
                  case 1934772034:
                     throw PngException(PngConstants.getChunkName(var2) + " cannot appear after PLTE", true);
                  default:
    return 3;
               }
            default:
               switch (var2) {
                  case 1229209940:
                     if (var1 == 4) {
    return 4;
                     }

                     throw PngException("IDAT chunks must be consecutive", true);
                  case 1229278788:
    return 6;
                  case 1347179589:
                  case 1649100612:
                  case 1665684045:
                  case 1732332865:
                  case 1749635924:
                  case 1766015824:
                  case 1866876531:
                  case 1883455820:
                  case 1883789683:
                  case 1933723988:
                  case 1933787468:
                  case 1934642260:
                  case 1934772034:
                  case 1934902610:
                  case 1951551059:
                     throw PngException(PngConstants.getChunkName(var2) + " cannot appear after IDAT", true);
                  default:
    return 5;
               }
         }
      }
   }

    static void errorIfPaletted(PngImage var0) {
      if (var0.getColorType() == 3) {
         throw PngException("Required PLTE chunk not found", true);
      }
   }
}
} // namespace png
} // namespace sixlegs
} // namespace com
