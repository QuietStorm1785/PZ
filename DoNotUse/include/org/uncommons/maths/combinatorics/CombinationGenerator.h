#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/math/BigInteger.h"
#include "org/uncommons/maths/Maths.h"
#include "org/uncommons/maths/combinatorics/CombinationGenerator/1.h"
#include <iterator>

namespace org {
namespace uncommons {
namespace maths {
namespace combinatorics {


class CombinationGenerator {
public:
   private const T[] elements;
   private const int[] combinationIndices;
    long remainingCombinations;
    long totalCombinations;

    public CombinationGenerator(T[] elements, int combinationLength) {
      if (combinationLength > elements.length) {
         throw IllegalArgumentException("Combination length cannot be greater than set size.");
      } else {
         this.elements = (T[])((Object[])elements.clone());
         this.combinationIndices = new int[combinationLength];
    BigInteger sizeFactorial = Maths.bigFactorial(elements.length);
    BigInteger lengthFactorial = Maths.bigFactorial(combinationLength);
    BigInteger differenceFactorial = Maths.bigFactorial(elements.length - combinationLength);
    BigInteger total = sizeFactorial.divide(differenceFactorial.multiply(lengthFactorial));
         if (total.compareTo(BigInteger.valueOf(int64_t.MAX_VALUE)) > 0) {
            throw IllegalArgumentException("Total number of combinations must not be more than 2^63.");
         } else {
            this.totalCombinations = total.longValue();
            this.reset();
         }
      }
   }

    public CombinationGenerator(Collection<T> elements, int combinationLength) {
      this((T[])elements.toArray(new Object[elements.size()]), combinationLength);
   }

    void reset() {
    int i = 0;

      while (i < this.combinationIndices.length) {
         this.combinationIndices[i] = i++;
      }

      this.remainingCombinations = this.totalCombinations;
   }

    long getRemainingCombinations() {
      return this.remainingCombinations;
   }

    bool hasMore() {
      return this.remainingCombinations > 0L;
   }

    long getTotalCombinations() {
      return this.totalCombinations;
   }

   public T[] nextCombinationAsArray() {
      T[] combination = (T[])((Object[])Array.newInstance(this.elements.getClass().getComponentType(), this.combinationIndices.length));
      return this.nextCombinationAsArray(combination);
   }

   public T[] nextCombinationAsArray(T[] destination) {
      if (destination.length != this.combinationIndices.length) {
         throw IllegalArgumentException("Destination array must be the same length as combinations.");
      } else {
         this.generateNextCombinationIndices();

         for (int i = 0; i < this.combinationIndices.length; i++) {
            destination[i] = this.elements[this.combinationIndices[i]];
         }

    return destination;
      }
   }

   public List<T> nextCombinationAsList() {
      return this.nextCombinationAsList(new std::vector<>(this.elements.length));
   }

   public List<T> nextCombinationAsList(List<T> destination) {
      this.generateNextCombinationIndices();
      destination.clear();

      for (int i : this.combinationIndices) {
         destination.push_back(this.elements[i]);
      }

    return destination;
   }

    void generateNextCombinationIndices() {
      if (this.remainingCombinations == 0L) {
         throw IllegalStateException("There are no combinations remaining.  Generator must be reset to continue using.");
      } else {
         if (this.remainingCombinations < this.totalCombinations) {
    int i = this.combinationIndices.length - 1;

            while (this.combinationIndices[i] == this.elements.length - this.combinationIndices.length + i) {
               i--;
            }

            this.combinationIndices[i]++;

            for (int j = i + 1; j < this.combinationIndices.length; j++) {
               this.combinationIndices[j] = this.combinationIndices[i] + j - i;
            }
         }

         this.remainingCombinations--;
      }
   }

   public Iterator<List<T>> iterator() {
      return std::make_shared<1>(this);
   }
}
} // namespace combinatorics
} // namespace maths
} // namespace uncommons
} // namespace org
