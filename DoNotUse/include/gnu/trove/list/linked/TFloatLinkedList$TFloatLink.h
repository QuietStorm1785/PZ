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

class TFloatLinkedList {
public:
    float value;
   TFloatLinkedList$TFloatLink previous;
   TFloatLinkedList$TFloatLink next;

   TFloatLinkedList$TFloatLink(float value) {
      this.value = value;
   }

    float getValue() {
      return this.value;
   }

    void setValue(float value) {
      this.value = value;
   }

   public TFloatLinkedList$TFloatLink getPrevious() {
      return this.previous;
   }

    void setPrevious(TFloatLinkedList$TFloatLink previous) {
      this.previous = previous;
   }

   public TFloatLinkedList$TFloatLink getNext() {
      return this.next;
   }

    void setNext(TFloatLinkedList$TFloatLink next) {
      this.next = next;
   }
}
} // namespace linked
} // namespace list
} // namespace trove
} // namespace gnu
