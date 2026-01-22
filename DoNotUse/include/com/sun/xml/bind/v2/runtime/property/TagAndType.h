#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/runtime/JaxBeanInfo.h"
#include "com/sun/xml/bind/v2/runtime/Name.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace property {


class TagAndType {
public:
    const Name tagName;
    const JaxBeanInfo beanInfo;

   TagAndType(Name tagName, JaxBeanInfo beanInfo) {
      this.tagName = tagName;
      this.beanInfo = beanInfo;
   }
}
} // namespace property
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
