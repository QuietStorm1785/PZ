#pragma once
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


class AtomicDouble : public Number {
public:
    static const long serialVersionUID = 0L;
   private transient volatile long value;
   private static const AtomicLongFieldUpdater<AtomicDouble> updater = AtomicLongFieldUpdater.newUpdater(AtomicDouble.class, "value");

    public AtomicDouble(double initialValue) {
      this.value = double.doubleToRawLongBits(initialValue);
   }

    public AtomicDouble() {
   }

    double get() {
      return double.longBitsToDouble(this.value);
   }

    void set(double newValue) {
    long next = double.doubleToRawLongBits(newValue);
      this.value = next;
   }

    void lazySet(double newValue) {
      this.set(newValue);
   }

    double getAndSet(double newValue) {
    long next = double.doubleToRawLongBits(newValue);
      return double.longBitsToDouble(updater.getAndSet(this, next));
   }

    bool compareAndSet(double expect, double update) {
      return updater.compareAndSet(this, double.doubleToRawLongBits(expect), double.doubleToRawLongBits(update));
   }

    bool weakCompareAndSet(double expect, double update) {
      return updater.weakCompareAndSet(this, double.doubleToRawLongBits(expect), double.doubleToRawLongBits(update));
   }

    double getAndAdd(double delta) {
    long current;
    double currentVal;
    long next;
      do {
         current = this.value;
         currentVal = double.longBitsToDouble(current);
    double nextVal = currentVal + delta;
         next = double.doubleToRawLongBits(nextVal);
      } while (!updater.compareAndSet(this, current, next));

    return currentVal;
   }

    double addAndGet(double delta) {
    long current;
    double nextVal;
    long next;
      do {
         current = this.value;
    double currentVal = double.longBitsToDouble(current);
         nextVal = currentVal + delta;
         next = double.doubleToRawLongBits(nextVal);
      } while (!updater.compareAndSet(this, current, next));

    return nextVal;
   }

    std::string toString() {
      return double.toString(this.get());
   }

    int intValue() {
      return (int)this.get();
   }

    long longValue() {
      return (long)this.get();
   }

    float floatValue() {
      return (float)this.get();
   }

    double doubleValue() {
      return this.get();
   }

    void writeObject(ObjectOutputStream s) {
      s.defaultWriteObject();
      s.writeDouble(this.get());
   }

    void readObject(ObjectInputStream s) {
      s.defaultReadObject();
      this.set(s.readDouble());
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
