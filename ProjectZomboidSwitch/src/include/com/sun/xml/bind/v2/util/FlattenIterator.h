#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>
#include <iterator>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace util {


class FlattenIterator {
public:
   private const Iterator<? : public Map<?, ? : public T>> parent;
   private Iterator<? : public T> child = nullptr;
    T next;

    public FlattenIterator(Iterable<? extends, ? extends) {
      this.parent = core.iterator();
   }

    void remove() {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool hasNext() {
      this.getNext();
      return this.next != nullptr;
   }

    T next() {
    T r = this.next;
      this.next = nullptr;
      if (r == nullptr) {
         throw std::make_unique<NoSuchElementException>();
      } else {
    return r;
      }
   }

    void getNext() {
      if (this.next == nullptr) {
         if (this.child != nullptr && this.child.hasNext()) {
            this.next = (T)this.child.next();
         } else {
            if (this.parent.hasNext()) {
               this.child = this.parent.next().values().iterator();
               this.getNext();
            }
         }
      }
   }
}
} // namespace util
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
