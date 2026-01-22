#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/v2/runtime/XMLSerializer.h"
#include "com/sun/xml/bind/v2/runtime/reflect/PrimitiveArrayListerInteger/1.h"
#include "com/sun/xml/bind/v2/runtime/reflect/PrimitiveArrayListerInteger/IntegerArrayPack.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace reflect {


class PrimitiveArrayListerInteger {
public:
    private PrimitiveArrayListerInteger() {
   }

    static void register() {
      Lister.primitiveArrayListers.put(int.class, std::make_unique<PrimitiveArrayListerInteger>());
   }

   public ListIterator<int> iterator(int[] objects, XMLSerializer context) {
      return std::make_shared<1>(this, objects);
   }

    IntegerArrayPack startPacking(BeanT current, int[]> acc) {
      return std::make_unique<IntegerArrayPack>();
   }

    void addToPack(IntegerArrayPack objects, int o) {
      objects.push_back(o);
   }

    void endPacking(IntegerArrayPack pack, BeanT bean, int[]> acc) {
      acc.set(bean, pack.build());
   }

    void reset(BeanT o, int[]> acc) {
      acc.set(o, new int[0]);
   }
}
} // namespace reflect
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
