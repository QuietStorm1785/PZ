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

class TShortLinkedList {
public:
    short value;
   TShortLinkedList$TShortLink previous;
   TShortLinkedList$TShortLink next;

   TShortLinkedList$TShortLink(short value) {
      this.value = value;
   }

    short getValue() {
      return this.value;
   }

    void setValue(short value) {
      this.value = value;
   }

   public TShortLinkedList$TShortLink getPrevious() {
      return this.previous;
   }

    void setPrevious(TShortLinkedList$TShortLink previous) {
      this.previous = previous;
   }

   public TShortLinkedList$TShortLink getNext() {
      return this.next;
   }

    void setNext(TShortLinkedList$TShortLink next) {
      this.next = next;
   }
}
} // namespace linked
} // namespace list
} // namespace trove
} // namespace gnu
