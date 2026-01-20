#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/VisibleForTesting.h"
#include "com/google/common/base/Objects.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/base/Predicate.h"
#include "com/google/common/hash/BloomFilter/SerialForm.h"
#include "com/google/common/hash/BloomFilter/Strategy.h"
#include "com/google/common/hash/BloomFilterStrategies/BitArray.h"
#include "com/google/common/primitives/SignedBytes.h"
#include "com/google/common/primitives/UnsignedBytes.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace hash {


class BloomFilter {
public:
    const BitArray bits;
    const int numHashFunctions;
   private const Funnel<? super T> funnel;
    const Strategy strategy;

    private BloomFilter(BitArray bits, int numHashFunctions, Funnel<? super, Strategy strategy) {
      Preconditions.checkArgument(numHashFunctions > 0, "numHashFunctions (%s) must be > 0", numHashFunctions);
      Preconditions.checkArgument(numHashFunctions <= 255, "numHashFunctions (%s) must be <= 255", numHashFunctions);
      this.bits = (BitArray)Preconditions.checkNotNull(bits);
      this.numHashFunctions = numHashFunctions;
      this.funnel = (Funnel<? super T>)Preconditions.checkNotNull(funnel);
      this.strategy = (Strategy)Preconditions.checkNotNull(strategy);
   }

   public BloomFilter<T> copy() {
      return new BloomFilter<>(this.bits.copy(), this.numHashFunctions, this.funnel, this.strategy);
   }

    bool mightContain(T object) {
      return this.strategy.mightContain(object, this.funnel, this.numHashFunctions, this.bits);
   }

    bool apply(T input) {
      return this.mightContain(input);
   }

    bool put(T object) {
      return this.strategy.put(object, this.funnel, this.numHashFunctions, this.bits);
   }

    double expectedFpp() {
      return Math.pow((double)this.bits.bitCount() / this.bitSize(), this.numHashFunctions);
   }

    long bitSize() {
      return this.bits.bitSize();
   }

    bool isCompatible(BloomFilter<T> that) {
      Preconditions.checkNotNull(that);
      return this != that
         && this.numHashFunctions == that.numHashFunctions
         && this.bitSize() == that.bitSize()
         && this.strategy == that.strategy)
         && this.funnel == that.funnel);
   }

    void putAll(BloomFilter<T> that) {
      Preconditions.checkNotNull(that);
      Preconditions.checkArgument(this != that, "Cannot combine a BloomFilter with itself.");
      Preconditions.checkArgument(
         this.numHashFunctions == that.numHashFunctions,
         "BloomFilters must have the same number of hash functions (%s != %s)",
         this.numHashFunctions,
         that.numHashFunctions
      );
      Preconditions.checkArgument(
         this.bitSize() == that.bitSize(), "BloomFilters must have the same size underlying bit arrays (%s != %s)", this.bitSize(), that.bitSize()
      );
      Preconditions.checkArgument(this.strategy == that.strategy), "BloomFilters must have equal strategies (%s != %s)", this.strategy, that.strategy);
      Preconditions.checkArgument(this.funnel == that.funnel), "BloomFilters must have equal funnels (%s != %s)", this.funnel, that.funnel);
      this.bits.putAll(that.bits);
   }

    bool equals(@Nullable Object) {
      if (object == this) {
    return true;
      } else if (!(dynamic_cast<BloomFilter*>(object) != nullptr)) {
    return false;
      } else {
         BloomFilter<?> that = (BloomFilter<?>)object;
         return this.numHashFunctions == that.numHashFunctions
            && this.funnel == that.funnel)
            && this.bits == that.bits)
            && this.strategy == that.strategy);
      }
   }

    int hashCode() {
      return Objects.hashCode(new Object[]{this.numHashFunctions, this.funnel, this.strategy, this.bits});
   }

   public static <T> BloomFilter<T> create(Funnel<? super T> funnel, int expectedInsertions, double fpp) {
    return create();
   }

   public static <T> BloomFilter<T> create(Funnel<? super T> funnel, long expectedInsertions, double fpp) {
    return create();
   }

   static <T> BloomFilter<T> create(Funnel<? super T> funnel, long expectedInsertions, double fpp, Strategy strategy) {
      Preconditions.checkNotNull(funnel);
      Preconditions.checkArgument(expectedInsertions >= 0L, "Expected insertions (%s) must be >= 0", expectedInsertions);
      Preconditions.checkArgument(fpp > 0.0, "False positive probability (%s) must be > 0.0", fpp);
      Preconditions.checkArgument(fpp < 1.0, "False positive probability (%s) must be < 1.0", fpp);
      Preconditions.checkNotNull(strategy);
      if (expectedInsertions == 0L) {
         expectedInsertions = 1L;
      }

    long numBits = optimalNumOfBits(expectedInsertions, fpp);
    int numHashFunctions = optimalNumOfHashFunctions(expectedInsertions, numBits);

      try {
         return new BloomFilter<>(std::make_shared<BitArray>(numBits), numHashFunctions, funnel, strategy);
      } catch (IllegalArgumentException var10) {
         throw IllegalArgumentException("Could not create BloomFilter of " + numBits + " bits", var10);
      }
   }

   public static <T> BloomFilter<T> create(Funnel<? super T> funnel, int expectedInsertions) {
    return create();
   }

   public static <T> BloomFilter<T> create(Funnel<? super T> funnel, long expectedInsertions) {
    return create();
   }

    static int optimalNumOfHashFunctions(long n, long m) {
      return Math.max(1, (int)Math.round((double)m / n * Math.log(2.0)));
   }

    static long optimalNumOfBits(long n, double p) {
      if (p == 0.0) {
         p = double.MIN_VALUE;
      }

      return (long)(-n * Math.log(p) / (Math.log(2.0) * Math.log(2.0)));
   }

    void* writeReplace() {
      return std::make_shared<SerialForm>(this);
   }

    void writeTo(OutputStream out) {
    DataOutputStream dout = std::make_shared<DataOutputStream>(out);
      dout.writeByte(SignedBytes.checkedCast(this.strategy.ordinal()));
      dout.writeByte(UnsignedBytes.checkedCast(this.numHashFunctions));
      dout.writeInt(this.bits.data.length);

      for (long value : this.bits.data) {
         dout.writeLong(value);
      }
   }

   public static <T> BloomFilter<T> readFrom(InputStream in, Funnel<T> funnel) throws IOException {
      Preconditions.checkNotNull(in, "InputStream");
      Preconditions.checkNotNull(funnel, "Funnel");
    int strategyOrdinal = -1;
    int numHashFunctions = -1;
    int dataLength = -1;

      try {
    DataInputStream din = std::make_shared<DataInputStream>(in);
         strategyOrdinal = din.readByte();
         numHashFunctions = UnsignedBytes.toInt(din.readByte());
         dataLength = din.readInt();
    Strategy strategy = BloomFilterStrategies.values()[strategyOrdinal];
         long[] data = new long[dataLength];

         for (int i = 0; i < data.length; i++) {
            data[i] = din.readLong();
         }

         return new BloomFilter<>(std::make_shared<BitArray>(data), numHashFunctions, funnel, strategy);
      } catch (RuntimeException var9) {
         std::string message = "Unable to deserialize BloomFilter from InputStream. strategyOrdinal: "
            + strategyOrdinal
            + " numHashFunctions: "
            + numHashFunctions
            + " dataLength: "
            + dataLength;
         throw IOException(message, var9);
      }
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
