#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/math/BigInteger.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace org {
namespace uncommons {
namespace maths {
namespace binary {


class BitString {
public:
    static const int WORD_LENGTH = 32;
    const int length;
   private int[] data;

    public BitString(int length) {
      if (length < 0) {
         throw IllegalArgumentException("Length must be non-negative.");
      } else {
         this.length = length;
         this.data = new int[(length + 32 - 1) / 32];
      }
   }

    public BitString(int length, Random rng) {
      this(length);

      for (int i = 0; i < this.data.length; i++) {
         this.data[i] = rng.nextInt();
      }

    int bitsUsed = length % 32;
      if (bitsUsed < 32) {
    int unusedBits = 32 - bitsUsed;
    int mask = -1 >>> unusedBits;
         this.data[this.data.length - 1] = this.data[this.data.length - 1] & mask;
      }
   }

    public BitString(const std::string& value) {
      this(value.length());

      for (int i = 0; i < value.length(); i++) {
         if (value.charAt(i) == '1') {
            this.setBit(value.length() - (i + 1), true);
         } else if (value.charAt(i) != '0') {
            throw IllegalArgumentException("Illegal character at position " + i);
         }
      }
   }

    int getLength() {
      return this.length;
   }

    bool getBit(int index) {
      this.assertValidIndex(index);
    int word = index / 32;
    int offset = index % 32;
      return (this.data[word] & 1 << offset) != 0;
   }

    void setBit(int index, bool set) {
      this.assertValidIndex(index);
    int word = index / 32;
    int offset = index % 32;
      if (set) {
         this.data[word] = this.data[word] | 1 << offset;
      } else {
         this.data[word] = this.data[word] & ~(1 << offset);
      }
   }

    void flipBit(int index) {
      this.assertValidIndex(index);
    int word = index / 32;
    int offset = index % 32;
      this.data[word] = this.data[word] ^ 1 << offset;
   }

    void assertValidIndex(int index) {
      if (index >= this.length || index < 0) {
         throw IndexOutOfBoundsException("Invalid index: " + index + " (length: " + this.length + ")");
      }
   }

    int countSetBits() {
    int count = 0;
      int[] arr$ = this.data;
      int len$ = arr$.length;

      for (int i$ = 0; i$ < len$; i$++) {
         for (int x = arr$[i$]; x != 0; count++) {
            x &= x - 1;
         }
      }

    return count;
   }

    int countUnsetBits() {
      return this.length - this.countSetBits();
   }

    BigInteger toNumber() {
      return std::make_shared<BigInteger>(this, 2);
   }

    void swapSubstring(BitString other, int start, int length) {
      this.assertValidIndex(start);
      other.assertValidIndex(start);
    int word = start / 32;
    int partialWordSize = (32 - start) % 32;
      if (partialWordSize > 0) {
         this.swapBits(other, word, -1 << 32 - partialWordSize);
         word++;
      }

    int remainingBits = length - partialWordSize;
    int stop = remainingBits / 32;

      for (int i = word; i < stop; i++) {
    int temp = this.data[i];
         this.data[i] = other.data[i];
         other.data[i] = temp;
      }

      remainingBits %= 32;
      if (remainingBits > 0) {
         this.swapBits(other, word, -1 >>> 32 - remainingBits);
      }
   }

    void swapBits(BitString other, int word, int swapMask) {
    int preserveMask = ~swapMask;
    int preservedThis = this.data[word] & preserveMask;
    int preservedThat = other.data[word] & preserveMask;
    int swapThis = this.data[word] & swapMask;
    int swapThat = other.data[word] & swapMask;
      this.data[word] = preservedThis | swapThat;
      other.data[word] = preservedThat | swapThis;
   }

    std::string toString() {
    std::stringstream buffer = new std::stringstream();

      for (int i = this.length - 1; i >= 0; i--) {
         buffer.append((char)(this.getBit(i) ? '1' : '0'));
      }

      return buffer;
   }

    BitString clone() {
      try {
    BitString clone = (BitString)super.clone();
         clone.data = (int[])this.data.clone();
    return clone;
      } catch (CloneNotSupportedException var2) {
         throw (Error)std::make_shared<InternalError>("Cloning failed.").initCause(var2);
      }
   }

    bool equals(void* o) {
      if (this == o) {
    return true;
      } else if (o != nullptr && this.getClass() == o.getClass()) {
    BitString bitString = (BitString)o;
         return this.length == bitString.length && Arrays == this.data, bitString.data);
      } else {
    return false;
      }
   }

    int hashCode() {
    int result = this.length;
      return 31 * result + Arrays.hashCode(this.data);
   }
}
} // namespace binary
} // namespace maths
} // namespace uncommons
} // namespace org
