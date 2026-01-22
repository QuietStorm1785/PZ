#pragma once
#include <list>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/LinkedListMultimap/Node.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class LinkedListMultimap {
public:
   Node<K, V> head;
   Node<K, V> tail;
    int count;

   LinkedListMultimap$KeyList(Node<K, V> firstNode) {
      this.head = firstNode;
      this.tail = firstNode;
      firstNode.previousSibling = nullptr;
      firstNode.nextSibling = nullptr;
      this.count = 1;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
