#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "javax/annotation/Nullable.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class Synchronized {
public:
    const void* delegate;
    const void* mutex;
    static const long serialVersionUID = 0L;

   Synchronized$SynchronizedObject(Object delegate, @Nullable Object mutex) {
      this.delegate = Preconditions.checkNotNull(delegate);
      this.mutex = mutex == nullptr ? this : mutex;
   }

    void* delegate() {
      return this.delegate;
   }

    std::string toString() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.delegate;
      }
   }

    void writeObject(ObjectOutputStream stream) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         stream.defaultWriteObject();
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
