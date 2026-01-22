#pragma once
#include <list>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class LinkedListMultimap {
public:
    const K key;
    V value;
   LinkedListMultimap$Node<K, V> next;
   LinkedListMultimap$Node<K, V> previous;
   LinkedListMultimap$Node<K, V> nextSibling;
   LinkedListMultimap$Node<K, V> previousSibling;

   LinkedListMultimap$Node(@Nullable K key, @Nullable V value) {
      this.key = key;
      this.value = value;
   }

    K getKey() {
      return this.key;
   }

    V getValue() {
      return this.value;
   }

    V setValue(@Nullable V) {
    V result = this.value;
      this.value = newValue;
    return result;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
