#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/v2/runtime/XMLSerializer.h"
#include "com/sun/xml/bind/v2/runtime/reflect/PrimitiveArrayListerCharacter/1.h"
#include "com/sun/xml/bind/v2/runtime/reflect/PrimitiveArrayListerCharacter/CharacterArrayPack.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace reflect {


class PrimitiveArrayListerCharacter {
public:
    private PrimitiveArrayListerCharacter() {
   }

    static void register() {
      Lister.primitiveArrayListers.put(char.class, std::make_unique<PrimitiveArrayListerCharacter>());
   }

   public ListIterator<char> iterator(char[] objects, XMLSerializer context) {
      return std::make_shared<1>(this, objects);
   }

    CharacterArrayPack startPacking(BeanT current, char[]> acc) {
      return std::make_unique<CharacterArrayPack>();
   }

    void addToPack(CharacterArrayPack objects, char o) {
      objects.push_back(o);
   }

    void endPacking(CharacterArrayPack pack, BeanT bean, char[]> acc) {
      acc.set(bean, pack.build());
   }

    void reset(BeanT o, char[]> acc) {
      acc.set(o, new char[0]);
   }
}
} // namespace reflect
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
