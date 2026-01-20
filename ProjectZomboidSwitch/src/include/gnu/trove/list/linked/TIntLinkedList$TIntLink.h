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

class TIntLinkedList {
public:
    int value;
   TIntLinkedList$TIntLink previous;
   TIntLinkedList$TIntLink next;

   TIntLinkedList$TIntLink(int value) {
      this.value = value;
   }

    int getValue() {
      return this.value;
   }

    void setValue(int value) {
      this.value = value;
   }

   public TIntLinkedList$TIntLink getPrevious() {
      return this.previous;
   }

    void setPrevious(TIntLinkedList$TIntLink previous) {
      this.previous = previous;
   }

   public TIntLinkedList$TIntLink getNext() {
      return this.next;
   }

    void setNext(TIntLinkedList$TIntLink next) {
      this.next = next;
   }
}
} // namespace linked
} // namespace list
} // namespace trove
} // namespace gnu
