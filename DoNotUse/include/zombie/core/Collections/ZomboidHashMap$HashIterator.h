#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Collections/ZomboidHashMap/Entry.h"
#include <algorithm>
#include <iterator>

namespace zombie {
namespace core {
namespace Collections {


class ZomboidHashMap {
public:
   Entry<K, V> next;
    int expectedModCount;
    int index;
   Entry<K, V> current;

   ZomboidHashMap$HashIterator(ZomboidHashMap var1) {
      this.this$0 = var1;
      this.expectedModCount = var1.modCount;
      if (var1.size > 0) {
         Entry[] var2 = var1.table;

         while (this.index < var2.length && (this.next = var2[this.index++]) == nullptr) {
         }
      }
   }

    bool hasNext() {
      return this.next != nullptr;
   }

   const Entry<K, V> nextEntry() {
      if (this.this$0.modCount != this.expectedModCount) {
         throw std::make_unique<ConcurrentModificationException>();
      } else {
    Entry var1 = this.next;
         if (var1 == nullptr) {
            throw std::make_unique<NoSuchElementException>();
         } else {
            if ((this.next = var1.next) == nullptr) {
               Entry[] var2 = this.this$0.table;

               while (this.index < var2.length && (this.next = var2[this.index++]) == nullptr) {
               }
            }

            this.current = var1;
    return var1;
         }
      }
   }

    void remove() {
      if (this.current == nullptr) {
         throw std::make_unique<IllegalStateException>();
      } else if (this.this$0.modCount != this.expectedModCount) {
         throw std::make_unique<ConcurrentModificationException>();
      } else {
    void* var1 = this.current.key;
         this.current = nullptr;
         this.this$0.removeEntryForKey(var1);
         this.expectedModCount = this.this$0.modCount;
      }
   }
}
} // namespace Collections
} // namespace core
} // namespace zombie
