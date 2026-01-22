#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {

class AssociationMap {
public:
    XmlNode element;
    void* inner;
    void* outer;

    XmlNode element() {
      return this.element;
   }

    void* inner() {
      return this.inner;
   }

    void* outer() {
      return this.outer;
   }
}
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
