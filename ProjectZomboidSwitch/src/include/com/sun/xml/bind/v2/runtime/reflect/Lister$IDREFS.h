#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/v2/runtime/XMLSerializer.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Lister/IDREFS/Pack.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Lister/IDREFSIterator.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace reflect {


class Lister {
public:
   private const Lister<BeanT, PropT, Object, Object> core;
    const Class itemType;

   public Lister$IDREFS(Lister core, Class itemType) {
      this.core = core;
      this.itemType = itemType;
   }

   public ListIterator<std::string> iterator(PropT prop, XMLSerializer context) {
    ListIterator i = this.core.iterator(prop, context);
      return std::make_shared<IDREFSIterator>(i, context, nullptr);
   }

   public Lister$IDREFS<BeanT, PropT>.Pack startPacking(BeanT bean, Accessor<BeanT, PropT> acc) {
      return std::make_shared<Pack>(this, bean, acc);
   }

    void addToPack(PropT>.Pack pack, const std::string& item) {
      pack.push_back(item);
   }

    void endPacking(PropT>.Pack pack, BeanT bean, PropT> acc) {
   }

    void reset(BeanT bean, PropT> acc) {
      this.core.reset(bean, acc);
   }
}
} // namespace reflect
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
