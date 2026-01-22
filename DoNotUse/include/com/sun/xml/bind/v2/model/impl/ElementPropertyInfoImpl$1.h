#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/core/TypeInfo.h"
#include <algorithm>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class ElementPropertyInfoImpl {
public:
   ElementPropertyInfoImpl$1(ElementPropertyInfoImpl this$0) {
      this.this$0 = this$0;
   }

   public TypeInfo<TypeT, ClassDeclT> get(int index) {
      return ((TypeRefImpl)this.this$0.getTypes().get(index)).getTarget();
   }

    int size() {
      return this.this$0.getTypes().size();
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
