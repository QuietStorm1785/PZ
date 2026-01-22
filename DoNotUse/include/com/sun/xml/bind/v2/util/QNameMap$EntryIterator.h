#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/util/QNameMap/Entry.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace util {


class QNameMap {
public:
   private QNameMap$EntryIterator(QNameMap var1) {
      super(var1);
      this.this$0 = var1;
   }

   public Entry<V> next() {
      return this.nextEntry();
   }
}
} // namespace util
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
