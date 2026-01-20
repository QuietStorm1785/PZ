#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/v2/runtime/XMLSerializer.h"
#include "com/sun/xml/bind/v2/runtime/reflect/PrimitiveArrayListerDouble/1.h"
#include "com/sun/xml/bind/v2/runtime/reflect/PrimitiveArrayListerDouble/DoubleArrayPack.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace reflect {


class PrimitiveArrayListerDouble {
public:
    private PrimitiveArrayListerDouble() {
   }

    static void register() {
      Lister.primitiveArrayListers.put(double.class, std::make_unique<PrimitiveArrayListerDouble>());
   }

   public ListIterator<double> iterator(double[] objects, XMLSerializer context) {
      return std::make_shared<1>(this, objects);
   }

    DoubleArrayPack startPacking(BeanT current, double[]> acc) {
      return std::make_unique<DoubleArrayPack>();
   }

    void addToPack(DoubleArrayPack objects, double o) {
      objects.push_back(o);
   }

    void endPacking(DoubleArrayPack pack, BeanT bean, double[]> acc) {
      acc.set(bean, pack.build());
   }

    void reset(BeanT o, double[]> acc) {
      acc.set(o, new double[0]);
   }
}
} // namespace reflect
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
