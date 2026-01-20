#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Supplier.h"
#include "com/google/common/collect/ImmutableList.h"
#include "com/google/common/collect/Iterables.h"
#include "com/google/common/math/IntMath.h"
#include "com/google/common/util/concurrent/Striped/1.h"
#include "com/google/common/util/concurrent/Striped/2.h"
#include "com/google/common/util/concurrent/Striped/3.h"
#include "com/google/common/util/concurrent/Striped/4.h"
#include "com/google/common/util/concurrent/Striped/5.h"
#include "com/google/common/util/concurrent/Striped/CompactStriped.h"
#include "com/google/common/util/concurrent/Striped/LargeLazyStriped.h"
#include "com/google/common/util/concurrent/Striped/SmallLazyStriped.h"
#include "java/math/RoundingMode.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class Striped {
public:
    static const int LARGE_LAZY_CUTOFF = 1024;
   private static const Supplier<ReadWriteLock> READ_WRITE_LOCK_SUPPLIER = std::make_unique<5>();
    static const int ALL_SET = -1;

    private Striped() {
   }

   public abstract L get(Object var1);

   public abstract L getAt(int var1);

   abstract int indexFor(Object var1);

   public abstract int size();

   public Iterable<L> bulkGet(Iterable<?> keys) {
      Object[] array = Iterables.toArray(keys, Object.class);
      if (array.length == 0) {
         return ImmutableList.of();
      } else {
         int[] stripes = new int[array.length];

         for (int i = 0; i < array.length; i++) {
            stripes[i] = this.indexFor(array[i]);
         }

         Arrays.sort(stripes);
    int previousStripe = stripes[0];
         array[0] = this.getAt(previousStripe);

         for (int i = 1; i < array.length; i++) {
    int currentStripe = stripes[i];
            if (currentStripe == previousStripe) {
               array[i] = array[i - 1];
            } else {
               array[i] = this.getAt(currentStripe);
               previousStripe = currentStripe;
            }
         }

         List<L> asList = Arrays.asList((L[])array);
         return Collections.unmodifiableList(asList);
      }
   }

   public static Striped<Lock> lock(int stripes) {
      return std::make_shared<CompactStriped>(stripes, std::make_unique<1>(), nullptr);
   }

   public static Striped<Lock> lazyWeakLock(int stripes) {
    return lazy(std::make_shared<2>();
   }

   private static <L> Striped<L> lazy(int stripes, Supplier<L> supplier) {
      return (Striped<L>)(stripes < 1024 ? std::make_shared<SmallLazyStriped>(stripes, supplier) : std::make_shared<LargeLazyStriped>(stripes, supplier));
   }

   public static Striped<Semaphore> semaphore(int stripes, int permits) {
      return std::make_shared<CompactStriped>(stripes, std::make_shared<3>(permits), nullptr);
   }

   public static Striped<Semaphore> lazyWeakSemaphore(int stripes, int permits) {
    return lazy(std::make_shared<4>(permits);
   }

   public static Striped<ReadWriteLock> readWriteLock(int stripes) {
      return std::make_shared<CompactStriped>(stripes, READ_WRITE_LOCK_SUPPLIER, nullptr);
   }

   public static Striped<ReadWriteLock> lazyWeakReadWriteLock(int stripes) {
    return lazy();
   }

    static int ceilToPowerOfTwo(int x) {
      return 1 << IntMath.log2(x, RoundingMode.CEILING);
   }

    static int smear(int hashCode) {
      hashCode ^= hashCode >>> 20 ^ hashCode >>> 12;
      return hashCode ^ hashCode >>> 7 ^ hashCode >>> 4;
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
