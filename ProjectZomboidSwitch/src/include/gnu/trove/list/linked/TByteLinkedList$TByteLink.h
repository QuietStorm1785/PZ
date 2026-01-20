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

class TByteLinkedList {
public:
    uint8_t value;
   TByteLinkedList$TByteLink previous;
   TByteLinkedList$TByteLink next;

   TByteLinkedList$TByteLink(byte value) {
      this.value = value;
   }

    uint8_t getValue() {
      return this.value;
   }

    void setValue(uint8_t value) {
      this.value = value;
   }

   public TByteLinkedList$TByteLink getPrevious() {
      return this.previous;
   }

    void setPrevious(TByteLinkedList$TByteLink previous) {
      this.previous = previous;
   }

   public TByteLinkedList$TByteLink getNext() {
      return this.next;
   }

    void setNext(TByteLinkedList$TByteLink next) {
      this.next = next;
   }
}
} // namespace linked
} // namespace list
} // namespace trove
} // namespace gnu
