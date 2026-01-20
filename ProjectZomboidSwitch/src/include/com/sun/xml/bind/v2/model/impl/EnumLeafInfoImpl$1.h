#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <iterator>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class EnumLeafInfoImpl {
public:
   private EnumConstantImpl<T, C, F, M> next;

   EnumLeafInfoImpl$1(EnumLeafInfoImpl this$0) {
      this.this$0 = this$0;
      this.next = EnumLeafInfoImpl.access$000(this.this$0);
   }

    bool hasNext() {
      return this.next != nullptr;
   }

   public EnumConstantImpl<T, C, F, M> next() {
      EnumConstantImpl<T, C, F, M> r = this.next;
      this.next = this.next.next;
    return r;
   }

    void remove() {
      throw std::make_unique<UnsupportedOperationException>();
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
