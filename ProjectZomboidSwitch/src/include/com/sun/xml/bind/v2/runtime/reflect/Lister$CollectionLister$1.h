#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/runtime/reflect/Lister/CollectionLister.h"
#include <iterator>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace reflect {


class Lister {
public:
   Lister$CollectionLister$1(CollectionLister this$0, Iterator var2) {
      this.this$0 = this$0;
      this.val$itr = var2;
   }

    bool hasNext() {
      return this.val$itr.hasNext();
   }

    void* next() {
      return this.val$itr.next();
   }
}
} // namespace reflect
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
