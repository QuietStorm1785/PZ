#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/util/FlattenIterator.h"
#include <iterator>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class TypeInfoSetImpl {
public:
   TypeInfoSetImpl$1(TypeInfoSetImpl this$0) {
      this.this$0 = this$0;
   }

   public Iterator<ElementInfoImpl<T, C, F, M>> iterator() {
      return std::make_shared<FlattenIterator>(TypeInfoSetImpl.access$000(this.this$0).values());
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
