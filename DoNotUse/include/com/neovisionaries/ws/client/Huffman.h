#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace neovisionaries {
namespace ws {
namespace client {

class Huffman {
public:
    const int mMinCodeLen;
    const int mMaxCodeLen;
   private const int[] mMaxCodeValsFromCodeLen;
   private const int[] mSymsFromCodeVal;

    public Huffman(int[] codeLensFromSym) {
      this.mMinCodeLen = Math.max(Misc.min(codeLensFromSym), 1);
      this.mMaxCodeLen = Misc.max(codeLensFromSym);
      int[] countsFromCodeLen = createCountsFromCodeLen(codeLensFromSym, this.mMaxCodeLen);
      Object[] out = new Object[2];
      this.mMaxCodeValsFromCodeLen = createMaxCodeValsFromCodeLen(countsFromCodeLen, this.mMaxCodeLen, out);
      int[] codeValsFromCodeLen = (int[])out[0];
    int maxCodeVal = (int)out[1];
      this.mSymsFromCodeVal = createSymsFromCodeVal(codeLensFromSym, codeValsFromCodeLen, maxCodeVal);
   }

   private static int[] createIntArray(int size, int initialValue) {
      int[] array = new int[size];

      for (int i = 0; i < size; i++) {
         array[i] = initialValue;
      }

    return array;
   }

   private static int[] createCountsFromCodeLen(int[] codeLensFromSym, int maxCodeLen) {
      int[] countsFromCodeLen = new int[maxCodeLen + 1];

      for (int symbol = 0; symbol < codeLensFromSym.length; symbol++) {
    int codeLength = codeLensFromSym[symbol];
         countsFromCodeLen[codeLength]++;
      }

    return countsFromCodeLen;
   }

   private static int[] createMaxCodeValsFromCodeLen(int[] countsFromCodeLen, int maxCodeLen, Object[] out) {
      int[] maxCodeValsFromCodeLen = createIntArray(maxCodeLen + 1, -1);
    int minCodeVal = 0;
    int maxCodeVal = 0;
      countsFromCodeLen[0] = 0;
      int[] codeValsFromCodeLen = new int[maxCodeLen + 1];

      for (int codeLen = 1; codeLen < countsFromCodeLen.length; codeLen++) {
    int prevCount = countsFromCodeLen[codeLen - 1];
         minCodeVal = minCodeVal + prevCount << 1;
         codeValsFromCodeLen[codeLen] = minCodeVal;
         maxCodeVal = minCodeVal + countsFromCodeLen[codeLen] - 1;
         maxCodeValsFromCodeLen[codeLen] = maxCodeVal;
      }

      out[0] = codeValsFromCodeLen;
      out[1] = maxCodeVal;
    return maxCodeValsFromCodeLen;
   }

   private static int[] createSymsFromCodeVal(int[] codeLensFromSym, int[] codeValsFromCodeLen, int maxCodeVal) {
      int[] symsFromCodeVal = new int[maxCodeVal + 1];

      for (int sym = 0; sym < codeLensFromSym.length; sym++) {
    int codeLen = codeLensFromSym[sym];
         if (codeLen != 0) {
    int codeVal = (int)(codeValsFromCodeLen[codeLen]++);
            symsFromCodeVal[codeVal] = sym;
         }
      }

    return symsFromCodeVal;
   }

    int readSym(ByteArray data, int[] bitIndex) {
      for (int codeLen = this.mMinCodeLen; codeLen <= this.mMaxCodeLen; codeLen++) {
    int maxCodeVal = this.mMaxCodeValsFromCodeLen[codeLen];
         if (maxCodeVal >= 0) {
    int codeVal = data.getHuffmanBits(bitIndex[0], codeLen);
            if (maxCodeVal >= codeVal) {
    int sym = this.mSymsFromCodeVal[codeVal];
               bitIndex[0] += codeLen;
    return sym;
            }
         }
      }

    std::string message = std::string.format("[%s] Bad code at the bit index '%d'.", this.getClass().getSimpleName(), bitIndex[0]);
      throw FormatException(message);
   }
}
} // namespace client
} // namespace ws
} // namespace neovisionaries
} // namespace com
