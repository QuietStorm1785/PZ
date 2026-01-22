#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace utils {

class FibonacciHeap {
public:
    int mDegree = 0;
    bool mIsMarked = false;
   private FibonacciHeap$Entry<T> mNext;
   private FibonacciHeap$Entry<T> mPrev;
   private FibonacciHeap$Entry<T> mParent;
   private FibonacciHeap$Entry<T> mChild;
    T mElem;
    double mPriority;

    T getValue() {
      return this.mElem;
   }

    void setValue(T var1) {
      this.mElem = (T)var1;
   }

    double getPriority() {
      return this.mPriority;
   }

   private FibonacciHeap$Entry(T var1, double var2) {
      this.mNext = this.mPrev = this;
      this.mElem = (T)var1;
      this.mPriority = var2;
   }
}
} // namespace utils
} // namespace core
} // namespace zombie
