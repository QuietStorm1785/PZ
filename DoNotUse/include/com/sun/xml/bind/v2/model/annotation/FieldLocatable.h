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


class FieldLocatable {
public:
    const Locatable upstream;
    const F field;
   private const Navigator<?, ?, F, ?> nav;

    public FieldLocatable(Locatable upstream, F field, ?> nav) {
      this.upstream = upstream;
      this.field = field;
      this.nav = nav;
   }

    Locatable getUpstream() {
      return this.upstream;
   }

    Location getLocation() {
      return this.nav.getFieldLocation(this.field);
   }
}
} // namespace annotation
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
