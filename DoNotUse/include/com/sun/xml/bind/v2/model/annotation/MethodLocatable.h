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


class MethodLocatable {
public:
    const Locatable upstream;
    const M method;
   private const Navigator<?, ?, ?, M> nav;

    public MethodLocatable(Locatable upstream, M method, M> nav) {
      this.upstream = upstream;
      this.method = method;
      this.nav = nav;
   }

    Locatable getUpstream() {
      return this.upstream;
   }

    Location getLocation() {
      return this.nav.getMethodLocation(this.method);
   }
}
} // namespace annotation
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
