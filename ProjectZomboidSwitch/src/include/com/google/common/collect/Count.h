#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "javax/annotation/Nullable.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class Count {
public:
    int value;

   Count(int value) {
      this.value = value;
   }

    int get() {
      return this.value;
   }

    void add(int delta) {
      this.value += delta;
   }

    int addAndGet(int delta) {
      return this.value += delta;
   }

    void set(int newValue) {
      this.value = newValue;
   }

    int getAndSet(int newValue) {
    int result = this.value;
      this.value = newValue;
    return result;
   }

    int hashCode() {
      return this.value;
   }

    bool equals(@Nullable Object) {
      return dynamic_cast<Count*>(obj) != nullptr && ((Count)obj).value == this.value;
   }

    std::string toString() {
      return int.toString(this.value);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
