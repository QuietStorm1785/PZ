#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace gnu {
namespace trove {
namespace list {

class TLinkableAdapter {
public:
   private volatile T next;
   private volatile T prev;

    T getNext() {
      return this.next;
   }

    void setNext(T next) {
      this.next = next;
   }

    T getPrevious() {
      return this.prev;
   }

    void setPrevious(T prev) {
      this.prev = prev;
   }
}
} // namespace list
} // namespace trove
} // namespace gnu
