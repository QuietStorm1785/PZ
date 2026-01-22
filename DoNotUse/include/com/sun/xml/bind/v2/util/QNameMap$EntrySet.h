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
   private QNameMap$EntrySet(QNameMap var1) {
      this.this$0 = var1;
   }

   public Iterator<Entry<V>> iterator() {
      return QNameMap.access$200(this.this$0);
   }

    bool contains(void* o) {
      if (!(dynamic_cast<Entry*>(o) != nullptr)) {
    return false;
      } else {
         Entry<V> e = (Entry<V>)o;
         Entry<V> candidate = QNameMap.access$300(this.this$0, e.nsUri, e.localName);
         return candidate != nullptr && candidate == e);
      }
   }

    bool remove(void* o) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    int size() {
      return this.this$0.size;
   }
}
} // namespace util
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
