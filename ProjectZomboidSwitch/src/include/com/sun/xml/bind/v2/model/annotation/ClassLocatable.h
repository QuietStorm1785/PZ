#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/nav/Navigator.h"
#include "com/sun/xml/bind/v2/runtime/Location.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace annotation {


class ClassLocatable {
public:
    const Locatable upstream;
    const C clazz;
   private const Navigator<?, C, ?, ?> nav;

    public ClassLocatable(Locatable upstream, C clazz, ?> nav) {
      this.upstream = upstream;
      this.clazz = clazz;
      this.nav = nav;
   }

    Locatable getUpstream() {
      return this.upstream;
   }

    Location getLocation() {
      return this.nav.getClassLocation(this.clazz);
   }
}
} // namespace annotation
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
