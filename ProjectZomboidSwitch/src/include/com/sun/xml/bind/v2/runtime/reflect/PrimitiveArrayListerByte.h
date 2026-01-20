#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/v2/runtime/XMLSerializer.h"
#include "com/sun/xml/bind/v2/runtime/reflect/PrimitiveArrayListerByte/1.h"
#include "com/sun/xml/bind/v2/runtime/reflect/PrimitiveArrayListerByte/ByteArrayPack.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace reflect {


class PrimitiveArrayListerByte {
public:
    private PrimitiveArrayListerByte() {
   }

    static void register() {
      Lister.primitiveArrayListers.put(byte.class, std::make_unique<PrimitiveArrayListerByte>());
   }

   public ListIterator<uint8_t> iterator(byte[] objects, XMLSerializer context) {
      return std::make_shared<1>(this, objects);
   }

    ByteArrayPack startPacking(BeanT current, byte[]> acc) {
      return std::make_unique<ByteArrayPack>();
   }

    void addToPack(ByteArrayPack objects, uint8_t o) {
      objects.push_back(o);
   }

    void endPacking(ByteArrayPack pack, BeanT bean, byte[]> acc) {
      acc.set(bean, pack.build());
   }

    void reset(BeanT o, byte[]> acc) {
      acc.set(o, new byte[0]);
   }
}
} // namespace reflect
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
