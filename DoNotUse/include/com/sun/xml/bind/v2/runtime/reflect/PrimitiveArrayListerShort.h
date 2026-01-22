#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/v2/runtime/XMLSerializer.h"
#include "com/sun/xml/bind/v2/runtime/reflect/PrimitiveArrayListerShort/1.h"
#include "com/sun/xml/bind/v2/runtime/reflect/PrimitiveArrayListerShort/ShortArrayPack.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace reflect {


class PrimitiveArrayListerShort {
public:
    private PrimitiveArrayListerShort() {
   }

    static void register() {
      Lister.primitiveArrayListers.put(short.class, std::make_unique<PrimitiveArrayListerShort>());
   }

   public ListIterator<int16_t> iterator(short[] objects, XMLSerializer context) {
      return std::make_shared<1>(this, objects);
   }

    ShortArrayPack startPacking(BeanT current, short[]> acc) {
      return std::make_unique<ShortArrayPack>();
   }

    void addToPack(ShortArrayPack objects, short o) {
      objects.push_back(o);
   }

    void endPacking(ShortArrayPack pack, BeanT bean, short[]> acc) {
      acc.set(bean, pack.build());
   }

    void reset(BeanT o, short[]> acc) {
      acc.set(o, new short[0]);
   }
}
} // namespace reflect
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
