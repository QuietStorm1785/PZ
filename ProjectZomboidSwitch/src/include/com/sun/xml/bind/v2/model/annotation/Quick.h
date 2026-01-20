#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/runtime/Location.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace annotation {


class Quick {
public:
    const Locatable upstream;

    protected Quick(Locatable upstream) {
      this.upstream = upstream;
   }

   protected abstract Annotation getAnnotation();

   protected abstract Quick newInstance(Locatable var1, Annotation var2);

    Location getLocation() {
    return this;
   }

    Locatable getUpstream() {
      return this.upstream;
   }

    std::string toString() {
      return this.getAnnotation();
   }
}
} // namespace annotation
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
