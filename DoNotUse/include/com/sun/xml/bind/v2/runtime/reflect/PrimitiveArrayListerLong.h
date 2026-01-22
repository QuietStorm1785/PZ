#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/v2/runtime/XMLSerializer.h"
#include "com/sun/xml/bind/v2/runtime/reflect/PrimitiveArrayListerLong/1.h"
#include "com/sun/xml/bind/v2/runtime/reflect/PrimitiveArrayListerLong/LongArrayPack.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace reflect {


class PrimitiveArrayListerLong {
public:
    private PrimitiveArrayListerLong() {
   }

    static void register() {
      Lister.primitiveArrayListers.put(long.class, std::make_unique<PrimitiveArrayListerLong>());
   }

   public ListIterator<int64_t> iterator(long[] objects, XMLSerializer context) {
      return std::make_shared<1>(this, objects);
   }

    LongArrayPack startPacking(BeanT current, long[]> acc) {
      return std::make_unique<LongArrayPack>();
   }

    void addToPack(LongArrayPack objects, long o) {
      objects.push_back(o);
   }

    void endPacking(LongArrayPack pack, BeanT bean, long[]> acc) {
      acc.set(bean, pack.build());
   }

    void reset(BeanT o, long[]> acc) {
      acc.set(o, new long[0]);
   }
}
} // namespace reflect
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
