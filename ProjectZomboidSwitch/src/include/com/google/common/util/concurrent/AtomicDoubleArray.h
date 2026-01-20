#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class AtomicDoubleArray {
public:
    static const long serialVersionUID = 0L;
   private transient AtomicLongArray longs;

    public AtomicDoubleArray(int length) {
      this.longs = std::make_shared<AtomicLongArray>(length);
   }

    public AtomicDoubleArray(double[] array) {
    int len = array.length;
      long[] longArray = new long[len];

      for (int i = 0; i < len; i++) {
         longArray[i] = double.doubleToRawLongBits(array[i]);
      }

      this.longs = std::make_shared<AtomicLongArray>(longArray);
   }

    int length() {
      return this.longs.length();
   }

    double get(int i) {
      return double.longBitsToDouble(this.longs.get(i));
   }

    void set(int i, double newValue) {
    long next = double.doubleToRawLongBits(newValue);
      this.longs.set(i, next);
   }

    void lazySet(int i, double newValue) {
      this.set(i, newValue);
   }

    double getAndSet(int i, double newValue) {
    long next = double.doubleToRawLongBits(newValue);
      return double.longBitsToDouble(this.longs.getAndSet(i, next));
   }

    bool compareAndSet(int i, double expect, double update) {
      return this.longs.compareAndSet(i, double.doubleToRawLongBits(expect), double.doubleToRawLongBits(update));
   }

    bool weakCompareAndSet(int i, double expect, double update) {
      return this.longs.weakCompareAndSet(i, double.doubleToRawLongBits(expect), double.doubleToRawLongBits(update));
   }

    double getAndAdd(int i, double delta) {
    long current;
    double currentVal;
    long next;
      do {
         current = this.longs.get(i);
         currentVal = double.longBitsToDouble(current);
    double nextVal = currentVal + delta;
         next = double.doubleToRawLongBits(nextVal);
      } while (!this.longs.compareAndSet(i, current, next));

    return currentVal;
   }

    double addAndGet(int i, double delta) {
    long current;
    double nextVal;
    long next;
      do {
         current = this.longs.get(i);
    double currentVal = double.longBitsToDouble(current);
         nextVal = currentVal + delta;
         next = double.doubleToRawLongBits(nextVal);
      } while (!this.longs.compareAndSet(i, current, next));

    return nextVal;
   }

    std::string toString() {
    int iMax = this.length() - 1;
      if (iMax == -1) {
         return "[]";
      } else {
    std::stringstream b = new std::stringstream(19 * (iMax + 1));
         b.append('[');
    int i = 0;

         while (true) {
            b.append(double.longBitsToDouble(this.longs.get(i)));
            if (i == iMax) {
               return b.append(']');
            }

            b.append(',').append(' ');
            i++;
         }
      }
   }

    void writeObject(ObjectOutputStream s) {
      s.defaultWriteObject();
    int length = this.length();
      s.writeInt(length);

      for (int i = 0; i < length; i++) {
         s.writeDouble(this.get(i));
      }
   }

    void readObject(ObjectInputStream s) {
      s.defaultReadObject();
    int length = s.readInt();
      this.longs = std::make_shared<AtomicLongArray>(length);

      for (int i = 0; i < length; i++) {
         this.set(i, s.readDouble());
      }
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
