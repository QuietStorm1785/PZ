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

class TDoubleLinkedList {
public:
    double value;
   TDoubleLinkedList$TDoubleLink previous;
   TDoubleLinkedList$TDoubleLink next;

   TDoubleLinkedList$TDoubleLink(double value) {
      this.value = value;
   }

    double getValue() {
      return this.value;
   }

    void setValue(double value) {
      this.value = value;
   }

   public TDoubleLinkedList$TDoubleLink getPrevious() {
      return this.previous;
   }

    void setPrevious(TDoubleLinkedList$TDoubleLink previous) {
      this.previous = previous;
   }

   public TDoubleLinkedList$TDoubleLink getNext() {
      return this.next;
   }

    void setNext(TDoubleLinkedList$TDoubleLink next) {
      this.next = next;
   }
}
} // namespace linked
} // namespace list
} // namespace trove
} // namespace gnu
