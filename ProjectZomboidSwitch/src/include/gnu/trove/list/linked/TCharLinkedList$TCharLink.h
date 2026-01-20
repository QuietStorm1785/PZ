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

class TCharLinkedList {
public:
    char value;
   TCharLinkedList$TCharLink previous;
   TCharLinkedList$TCharLink next;

   TCharLinkedList$TCharLink(char value) {
      this.value = value;
   }

    char getValue() {
      return this.value;
   }

    void setValue(char value) {
      this.value = value;
   }

   public TCharLinkedList$TCharLink getPrevious() {
      return this.previous;
   }

    void setPrevious(TCharLinkedList$TCharLink previous) {
      this.previous = previous;
   }

   public TCharLinkedList$TCharLink getNext() {
      return this.next;
   }

    void setNext(TCharLinkedList$TCharLink next) {
      this.next = next;
   }
}
} // namespace linked
} // namespace list
} // namespace trove
} // namespace gnu
