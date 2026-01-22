#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/v2/runtime/XMLSerializer.h"
#include "com/sun/xml/bind/v2/runtime/reflect/PrimitiveArrayListerBoolean/1.h"
#include "com/sun/xml/bind/v2/runtime/reflect/PrimitiveArrayListerBoolean/BooleanArrayPack.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace reflect {


class PrimitiveArrayListerBoolean {
public:
    private PrimitiveArrayListerBoolean() {
   }

    static void register() {
      Lister.primitiveArrayListers.put(boolean.class, std::make_unique<PrimitiveArrayListerBoolean>());
   }

   public ListIterator<bool> iterator(boolean[] objects, XMLSerializer context) {
      return std::make_shared<1>(this, objects);
   }

    BooleanArrayPack startPacking(BeanT current, boolean[]> acc) {
      return std::make_unique<BooleanArrayPack>();
   }

    void addToPack(BooleanArrayPack objects, bool o) {
      objects.push_back(o);
   }

    void endPacking(BooleanArrayPack pack, BeanT bean, boolean[]> acc) {
      acc.set(bean, pack.build());
   }

    void reset(BeanT o, boolean[]> acc) {
      acc.set(o, new boolean[0]);
   }
}
} // namespace reflect
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
