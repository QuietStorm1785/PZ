#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/AbstractIterator/1.h"
#include "com/google/common/base/AbstractIterator/State.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace base {


class AbstractIterator {
public:
    State state = State.NOT_READY;
    T next;

    protected AbstractIterator() {
   }

   protected abstract T computeNext();

    T endOfData() {
      this.state = State.DONE;
    return nullptr;
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    bool hasNext() {
      Preconditions.checkState(this.state != State.FAILED);
      switch (1.$SwitchMap$com$google$common$base$AbstractIterator$State[this.state.ordinal()]) {
         case 1:
    return true;
         case 2:
    return false;
         default:
            return this.tryToComputeNext();
      }
   }

    bool tryToComputeNext() {
      this.state = State.FAILED;
      this.next = this.computeNext();
      if (this.state != State.DONE) {
         this.state = State.READY;
    return true;
      } else {
    return false;
      }
   }

    T next() {
      if (!this.hasNext()) {
         throw std::make_unique<NoSuchElementException>();
      } else {
         this.state = State.NOT_READY;
    T result = this.next;
         this.next = nullptr;
    return result;
      }
   }

    void remove() {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
