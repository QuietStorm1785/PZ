#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/impl/ClassInfoImpl/PropertySorter.h"
#include <algorithm>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class ClassInfoImpl {
public:
   ClassInfoImpl$PropertySorter$1(PropertySorter this$1) {
      this.this$1 = this$1;
   }

    std::string get(int index) {
      return ((PropertyInfoImpl)ClassInfoImpl.access$200(this.this$1.this$0).get(index)).getName();
   }

    int size() {
      return ClassInfoImpl.access$200(this.this$1.this$0).size();
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
