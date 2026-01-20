#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/uncommons/maths/Maths.h"
#include "org/uncommons/maths/combinatorics/PermutationGenerator/1.h"
#include <iterator>

namespace org {
namespace uncommons {
namespace maths {
namespace combinatorics {


template<typename T>
class PermutationGenerator {
public:
   std::vector<T> elements;
   std::vector<int> permutationIndices;
   int64_t remainingPermutations = 0;
   int64_t totalPermutations = 0;

   PermutationGenerator(const std::vector<T>& elems) {
      if (elems.size() > 20) {
         throw std::invalid_argument("Size must be less than or equal to 20.");
      }
      elements = elems;
      permutationIndices.resize(elems.size());
      totalPermutations = Maths::factorial(static_cast<int>(elems.size()));
      reset();
   }

   void reset() {
      for (size_t i = 0; i < permutationIndices.size(); ++i) {
         permutationIndices[i] = static_cast<int>(i);
      }
      remainingPermutations = totalPermutations;
   }

   int64_t getRemainingPermutations() const {
      return remainingPermutations;
   }

   int64_t getTotalPermutations() const {
      return totalPermutations;
   }

   bool hasMore() const {
      return remainingPermutations > 0;
   }

   public T[] nextPermutationAsArray() {
      T[] permutation = (T[])((Object[])Array.newInstance(this.elements.getClass().getComponentType(), this.permutationIndices.length));
      return this.nextPermutationAsArray(permutation);
   }

   public T[] nextPermutationAsArray(T[] destination) {
      if (destination.length != this.elements.length) {
         throw IllegalArgumentException("Destination array must be the same length as permutations.");
      } else {
         this.generateNextPermutationIndices();

         for (int i = 0; i < this.permutationIndices.length; i++) {
            destination[i] = this.elements[this.permutationIndices[i]];
         }

    return destination;
      }
   }

   public List<T> nextPermutationAsList() {
      List<T> permutation = new std::vector<>(this.elements.length);
      return this.nextPermutationAsList(permutation);
   }

   public List<T> nextPermutationAsList(List<T> destination) {
      this.generateNextPermutationIndices();
      destination.clear();

      for (int i : this.permutationIndices) {
         destination.push_back(this.elements[i]);
      }

    return destination;
   }

    void generateNextPermutationIndices() {
      if (this.remainingPermutations == 0L) {
         throw IllegalStateException("There are no permutations remaining.  Generator must be reset to continue using.");
      } else {
         if (this.remainingPermutations < this.totalPermutations) {
    int j = this.permutationIndices.length - 2;

            while (this.permutationIndices[j] > this.permutationIndices[j + 1]) {
               j--;
            }

    int k = this.permutationIndices.length - 1;

            while (this.permutationIndices[j] > this.permutationIndices[k]) {
               k--;
            }

    int temp = this.permutationIndices[k];
            this.permutationIndices[k] = this.permutationIndices[j];
            this.permutationIndices[j] = temp;
    int r = this.permutationIndices.length - 1;

            for (int s = j + 1; r > s; s++) {
               temp = this.permutationIndices[s];
               this.permutationIndices[s] = this.permutationIndices[r];
               this.permutationIndices[r] = temp;
               r--;
            }
         }

         this.remainingPermutations--;
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
