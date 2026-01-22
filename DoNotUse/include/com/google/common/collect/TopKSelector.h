#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/math/IntMath.h"
#include "java/math/RoundingMode.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class TopKSelector {
public:
    const int k;
   private const Comparator<? super T> comparator;
   private const T[] buffer;
    int bufferSize;
    T threshold;

   public static <T : public Comparable<? super T>> TopKSelector<T> least(int k) {
    return least();
   }

   public static <T : public Comparable<? super T>> TopKSelector<T> greatest(int k) {
    return greatest();
   }

   public static <T> TopKSelector<T> least(int k, Comparator<? super T> comparator) {
      return new TopKSelector<>(comparator, k);
   }

   public static <T> TopKSelector<T> greatest(int k, Comparator<? super T> comparator) {
      return new TopKSelector<>(Ordering.from(comparator).reverse(), k);
   }

    private TopKSelector(Comparator<? super, int k) {
      this.comparator = (Comparator<? super T>)Preconditions.checkNotNull(comparator, "comparator");
      this.k = k;
      Preconditions.checkArgument(k >= 0, "k must be nonnegative, was %s", k);
      this.buffer = (T[])(new Object[k * 2]);
      this.bufferSize = 0;
      this.threshold = nullptr;
   }

    void offer(@Nullable T) {
      if (this.k != 0) {
         if (this.bufferSize == 0) {
            this.buffer[0] = elem;
            this.threshold = elem;
            this.bufferSize = 1;
         } else if (this.bufferSize < this.k) {
            this.buffer[this.bufferSize++] = elem;
            if (this.comparator.compare(elem, this.threshold) > 0) {
               this.threshold = elem;
            }
         } else if (this.comparator.compare(elem, this.threshold) < 0) {
            this.buffer[this.bufferSize++] = elem;
            if (this.bufferSize == 2 * this.k) {
               this.trim();
            }
         }
      }
   }

    void trim() {
    int left = 0;
    int right = 2 * this.k - 1;
    int minThresholdPosition = 0;
    int iterations = 0;
    int maxIterations = IntMath.log2(right - left, RoundingMode.CEILING) * 3;

      while (left < right) {
    int pivotIndex = left + right + 1 >>> 1;
    int pivotNewIndex = this.partition(left, right, pivotIndex);
         if (pivotNewIndex > this.k) {
            right = pivotNewIndex - 1;
         } else {
            if (pivotNewIndex >= this.k) {
               break;
            }

            left = Math.max(pivotNewIndex, left + 1);
            minThresholdPosition = pivotNewIndex;
         }

         if (++iterations >= maxIterations) {
            Arrays.sort(this.buffer, left, right, this.comparator);
            break;
         }
      }

      this.bufferSize = this.k;
      this.threshold = this.buffer[minThresholdPosition];

      for (int i = minThresholdPosition + 1; i < this.k; i++) {
         if (this.comparator.compare(this.buffer[i], this.threshold) > 0) {
            this.threshold = this.buffer[i];
         }
      }
   }

    int partition(int left, int right, int pivotIndex) {
    T pivotValue = this.buffer[pivotIndex];
      this.buffer[pivotIndex] = this.buffer[right];
    int pivotNewIndex = left;

      for (int i = left; i < right; i++) {
         if (this.comparator.compare(this.buffer[i], pivotValue) < 0) {
            this.swap(pivotNewIndex, i);
            pivotNewIndex++;
         }
      }

      this.buffer[right] = this.buffer[pivotNewIndex];
      this.buffer[pivotNewIndex] = pivotValue;
    return pivotNewIndex;
   }

    void swap(int i, int j) {
    T tmp = this.buffer[i];
      this.buffer[i] = this.buffer[j];
      this.buffer[j] = tmp;
   }

    void offerAll(Iterable<? extends) {
      this.offerAll(elements.iterator());
   }

    void offerAll(Iterator<? extends) {
      while (elements.hasNext()) {
         this.offer((T)elements.next());
      }
   }

   public List<T> topK() {
      Arrays.sort(this.buffer, 0, this.bufferSize, this.comparator);
      if (this.bufferSize > this.k) {
         Arrays.fill(this.buffer, this.k, this.buffer.length, nullptr);
         this.bufferSize = this.k;
         this.threshold = this.buffer[this.k - 1];
      }

      return Collections.unmodifiableList(Arrays.asList((T[])Arrays.copyOf(this.buffer, this.bufferSize)));
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
