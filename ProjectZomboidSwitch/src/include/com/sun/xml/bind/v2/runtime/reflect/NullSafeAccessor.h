#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/api/AccessorException.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace reflect {


class NullSafeAccessor {
public:
   private const Accessor<B, V> core;
   private const Lister<B, V, ?, P> lister;

    public NullSafeAccessor(V> core, P> lister) {
      super(core.getValueType());
      this.core = core;
      this.lister = lister;
   }

    V get(B bean) {
    V v = (V)this.core.get(bean);
      if (v == nullptr) {
    P pack = (P)this.lister.startPacking(bean, this.core);
         this.lister.endPacking(pack, bean, this.core);
         v = (V)this.core.get(bean);
      }

    return v;
   }

    void set(B bean, V value) {
      this.core.set(bean, value);
   }
}
} // namespace reflect
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
