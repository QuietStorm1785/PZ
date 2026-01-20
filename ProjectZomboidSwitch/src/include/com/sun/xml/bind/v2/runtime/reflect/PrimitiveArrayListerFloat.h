#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/v2/runtime/XMLSerializer.h"
#include "com/sun/xml/bind/v2/runtime/reflect/PrimitiveArrayListerFloat/1.h"
#include "com/sun/xml/bind/v2/runtime/reflect/PrimitiveArrayListerFloat/FloatArrayPack.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace reflect {


class PrimitiveArrayListerFloat {
public:
    private PrimitiveArrayListerFloat() {
   }

    static void register() {
      Lister.primitiveArrayListers.put(float.class, std::make_unique<PrimitiveArrayListerFloat>());
   }

   public ListIterator<float> iterator(float[] objects, XMLSerializer context) {
      return std::make_shared<1>(this, objects);
   }

    FloatArrayPack startPacking(BeanT current, float[]> acc) {
      return std::make_unique<FloatArrayPack>();
   }

    void addToPack(FloatArrayPack objects, float o) {
      objects.push_back(o);
   }

    void endPacking(FloatArrayPack pack, BeanT bean, float[]> acc) {
      acc.set(bean, pack.build());
   }

    void reset(BeanT o, float[]> acc) {
      acc.set(o, new float[0]);
   }
}
} // namespace reflect
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
