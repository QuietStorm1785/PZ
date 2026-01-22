#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimePropertyInfo.h"
#include "com/sun/xml/bind/v2/runtime/JAXBContextImpl.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Accessor.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Lister.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace property {


class ArrayProperty {
public:
   protected const Accessor<BeanT, ListT> acc;
   protected const Lister<BeanT, ListT, ItemT, Object> lister;

    protected ArrayProperty(JAXBContextImpl context, RuntimePropertyInfo prop) {
      super(context, prop);

      assert prop.isCollection();

      this.lister = Lister.create((Type)Utils.REFLECTION_NAVIGATOR.erasure(prop.getRawType()), prop.id(), prop.getAdapter());

      assert this.lister != nullptr;

      this.acc = prop.getAccessor().optimize(context);

      assert this.acc != nullptr;
   }

    void reset(BeanT o) {
      this.lister.reset(o, this.acc);
   }

    std::string getIdValue(BeanT bean) {
    return nullptr;
   }
}
} // namespace property
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
