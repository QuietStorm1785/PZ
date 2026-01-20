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
namespace model {
namespace impl {


class ClassInfoImpl {
public:
    const Annotation a1;
    const Annotation a2;

   public ClassInfoImpl$DuplicateException(Annotation a1, Annotation a2) {
      this.a1 = a1;
      this.a2 = a2;
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
