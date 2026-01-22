#pragma once
#include <list>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace gnu {
namespace trove {
namespace list {
namespace linked {

class TLongLinkedList {
public:
    long value;
   TLongLinkedList$TLongLink previous;
   TLongLinkedList$TLongLink next;

   TLongLinkedList$TLongLink(long value) {
      this.value = value;
   }

    long getValue() {
      return this.value;
   }

    void setValue(long value) {
      this.value = value;
   }

   public TLongLinkedList$TLongLink getPrevious() {
      return this.previous;
   }

    void setPrevious(TLongLinkedList$TLongLink previous) {
      this.previous = previous;
   }

   public TLongLinkedList$TLongLink getNext() {
      return this.next;
   }

    void setNext(TLongLinkedList$TLongLink next) {
      this.next = next;
   }
}
} // namespace linked
} // namespace list
} // namespace trove
} // namespace gnu
