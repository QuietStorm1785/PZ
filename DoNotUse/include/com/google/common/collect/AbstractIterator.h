#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/AbstractIterator/1.h"
#include "com/google/common/collect/AbstractIterator/State.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


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
      switch (1.$SwitchMap$com$google$common$collect$AbstractIterator$State[this.state.ordinal()]) {
         case 1:
    return false;
         case 2:
    return true;
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

    T peek() {
      if (!this.hasNext()) {
         throw std::make_unique<NoSuchElementException>();
      } else {
         return this.next;
      }
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
