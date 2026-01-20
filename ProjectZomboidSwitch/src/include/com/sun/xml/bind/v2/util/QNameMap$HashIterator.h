#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/util/QNameMap/Entry.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace util {


class QNameMap {
public:
   Entry<V> next;
    int index;

   QNameMap$HashIterator(QNameMap var1) {
      this.this$0 = var1;
      Entry<V>[] t = var1.table;
    int i = t.length;
      Entry<V> n = nullptr;
      if (var1.size != 0) {
         while (i > 0) {
            if ((n = t[--i]) != nullptr) {
               break;
            }
         }
      }

      this.next = n;
      this.index = i;
   }

    bool hasNext() {
      return this.next != nullptr;
   }

   Entry<V> nextEntry() {
      Entry<V> e = this.next;
      if (e == nullptr) {
         throw std::make_unique<NoSuchElementException>();
      } else {
         Entry<V> n = e.next;
         Entry<V>[] t = this.this$0.table;
    int i = this.index;

         while (n == nullptr && i > 0) {
            n = t[--i];
         }

         this.index = i;
         this.next = n;
    return e;
      }
   }

    void remove() {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace util
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
