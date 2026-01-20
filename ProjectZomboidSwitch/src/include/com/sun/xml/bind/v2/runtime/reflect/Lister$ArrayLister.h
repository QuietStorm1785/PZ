#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/v2/runtime/XMLSerializer.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Lister/ArrayLister/1.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Lister/Pack.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace reflect {


class Lister {
public:
   private const Class<ItemT> itemType;

   public Lister$ArrayLister(Class<ItemT> itemType) {
      this.itemType = itemType;
   }

   public ListIterator<ItemT> iterator(ItemT[] objects, XMLSerializer context) {
      return std::make_shared<1>(this, objects);
   }

    Pack startPacking(BeanT current, ItemT[]> acc) {
      return std::make_shared<Pack>(this.itemType);
   }

    void addToPack(Pack<ItemT> objects, ItemT o) {
      objects.push_back(o);
   }

    void endPacking(Pack<ItemT> pack, BeanT bean, ItemT[]> acc) {
      acc.set(bean, pack.build());
   }

    void reset(BeanT o, ItemT[]> acc) {
      acc.set(o, (Object[])Array.newInstance(this.itemType, 0));
   }
}
} // namespace reflect
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
