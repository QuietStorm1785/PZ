#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/utils/FibonacciHeap/Entry.h"
#include "zombie/iso/IsoGridSquare.h"
#include <algorithm>

namespace zombie {
namespace core {
namespace utils {


class FibonacciHeap {
public:
   private Entry<T> mMin = nullptr;
    int mSize = 0;
   List<Entry<T>> treeTable = new std::vector<>(300);
   List<Entry<T>> toVisit = new std::vector<>(300);

    void empty() {
      this.mMin = nullptr;
      this.mSize = 0;
   }

   public Entry<T> enqueue(T var1, double var2) {
      this.checkPriority(var2);
    Entry var4 = std::make_shared<Entry>(var1, var2);
      this.mMin = mergeLists(this.mMin, var4);
      this.mSize++;
    return var4;
   }

   public Entry<T> min() {
      if (this.empty()) {
         throw NoSuchElementException("Heap is empty.");
      } else {
         return this.mMin;
      }
   }

    bool isEmpty() {
      return this.mMin == nullptr;
   }

    int size() {
      return this.mSize;
   }

   public static <T> FibonacciHeap<T> merge(FibonacciHeap<T> var0, FibonacciHeap<T> var1) {
    FibonacciHeap var2 = std::make_shared<FibonacciHeap>();
      var2.mMin = mergeLists(var0.mMin, var1.mMin);
      var2.mSize = var0.mSize + var1.mSize;
      var0.mSize = var1.mSize = 0;
      var0.mMin = nullptr;
      var1.mMin = nullptr;
    return var2;
   }

   public Entry<T> dequeueMin() {
      if (this.empty()) {
         throw NoSuchElementException("Heap is empty.");
      } else {
         this.mSize--;
    Entry var1 = this.mMin;
         if (this.mMin.mNext == this.mMin) {
            this.mMin = nullptr;
         } else {
            this.mMin.mPrev.mNext = this.mMin.mNext;
            this.mMin.mNext.mPrev = this.mMin.mPrev;
            this.mMin = this.mMin.mNext;
         }

         if (var1.mChild != nullptr) {
    Entry var2 = var1.mChild;

            do {
               var2.mParent = nullptr;
               var2 = var2.mNext;
            } while (var2 != var1.mChild);
         }

         this.mMin = mergeLists(this.mMin, var1.mChild);
         if (this.mMin == nullptr) {
    return var1;
         } else {
            this.treeTable.clear();
            this.toVisit.clear();

            for (Entry var7 = this.mMin; this.toVisit.empty() || this.toVisit.get(0) != var7; var7 = var7.mNext) {
               this.toVisit.push_back(var7);
            }

            label57:
            for (Entry var3 : this.toVisit) {
               while (true) {
                  while (var3.mDegree < this.treeTable.size()) {
                     if (this.treeTable.get(var3.mDegree) == nullptr) {
                        this.treeTable.set(var3.mDegree, var3);
                        if (var3.mPriority <= this.mMin.mPriority) {
                           this.mMin = var3;
                        }
    continue label57;
                     }

    Entry var4 = this.treeTable.get(var3.mDegree);
                     this.treeTable.set(var3.mDegree, nullptr);
    Entry var5 = var4.mPriority < var3.mPriority ? var4 : var3;
    Entry var6 = var4.mPriority < var3.mPriority ? var3 : var4;
                     var6.mNext.mPrev = var6.mPrev;
                     var6.mPrev.mNext = var6.mNext;
                     var6.mNext = var6.mPrev = var6;
                     var5.mChild = mergeLists(var5.mChild, var6);
                     var6.mParent = var5;
                     var6.mIsMarked = false;
                     var5.mDegree++;
                     var3 = var5;
                  }

                  this.treeTable.push_back(nullptr);
               }
            }

    return var1;
         }
      }
   }

    void decreaseKey(Entry<T> var1, double var2) {
      this.checkPriority(var2);
      if (var2 > var1.mPriority) {
         throw IllegalArgumentException("New priority exceeds old.");
      } else {
         this.decreaseKeyUnchecked(var1, var2);
      }
   }

    void delete(Entry<T> var1) {
      this.decreaseKeyUnchecked(var1, double.NEGATIVE_INFINITY);
      this.dequeueMin();
   }

    void delete(int var1, IsoGridSquare var2) {
   }

    void checkPriority(double var1) {
      if (double.isNaN(var1)) {
         throw IllegalArgumentException(var1 + " is invalid.");
      }
   }

   private static <T> Entry<T> mergeLists(Entry<T> var0, Entry<T> var1) {
      if (var0 == nullptr && var1 == nullptr) {
    return nullptr;
      } else if (var0 != nullptr && var1 == nullptr) {
    return var0;
      } else if (var0 == nullptr && var1 != nullptr) {
    return var1;
      } else {
    Entry var2 = var0.mNext;
         var0.mNext = var1.mNext;
         var0.mNext.mPrev = var0;
         var1.mNext = var2;
         var1.mNext.mPrev = var1;
         return var0.mPriority < var1.mPriority ? var0 : var1;
      }
   }

    void decreaseKeyUnchecked(Entry<T> var1, double var2) {
      var1.mPriority = var2;
      if (var1.mParent != nullptr && var1.mPriority <= var1.mParent.mPriority) {
         this.cutNode(var1);
      }

      if (var1.mPriority <= this.mMin.mPriority) {
         this.mMin = var1;
      }
   }

    void decreaseKeyUncheckedNode(Entry<IsoGridSquare> var1, double var2) {
      var1.mPriority = var2;
      if (var1.mParent != nullptr && var1.mPriority <= var1.mParent.mPriority) {
         this.cutNodeNode(var1);
      }

      if (var1.mPriority <= this.mMin.mPriority) {
         this.mMin = var1;
      }
   }

    void cutNode(Entry<T> var1) {
      var1.mIsMarked = false;
      if (var1.mParent != nullptr) {
         if (var1.mNext != var1) {
            var1.mNext.mPrev = var1.mPrev;
            var1.mPrev.mNext = var1.mNext;
         }

         if (var1.mParent.mChild == var1) {
            if (var1.mNext != var1) {
               var1.mParent.mChild = var1.mNext;
            } else {
               var1.mParent.mChild = nullptr;
            }
         }

         var1.mParent.mDegree--;
         var1.mPrev = var1.mNext = var1;
         this.mMin = mergeLists(this.mMin, var1);
         if (var1.mParent.mIsMarked) {
            this.cutNode(var1.mParent);
         } else {
            var1.mParent.mIsMarked = true;
         }

         var1.mParent = nullptr;
      }
   }

    void cutNodeNode(Entry<IsoGridSquare> var1) {
      var1.mIsMarked = false;
      if (var1.mParent != nullptr) {
         if (var1.mNext != var1) {
            var1.mNext.mPrev = var1.mPrev;
            var1.mPrev.mNext = var1.mNext;
         }

         if (var1.mParent.mChild == var1) {
            if (var1.mNext != var1) {
               var1.mParent.mChild = var1.mNext;
            } else {
               var1.mParent.mChild = nullptr;
            }
         }

         var1.mParent.mDegree--;
         var1.mPrev = var1.mNext = var1;
         this.mMin = mergeLists(this.mMin, var1);
         if (var1.mParent.mIsMarked) {
            this.cutNode(var1.mParent);
         } else {
            var1.mParent.mIsMarked = true;
         }

         var1.mParent = nullptr;
      }
   }
}
} // namespace utils
} // namespace core
} // namespace zombie
