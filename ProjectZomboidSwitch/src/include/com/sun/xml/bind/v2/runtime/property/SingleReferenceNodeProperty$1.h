#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/v2/runtime/ElementBeanInfoImpl.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Accessor.h"
#include "javax/xml/bind/JAXBElement.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace property {


class SingleReferenceNodeProperty {
public:
   SingleReferenceNodeProperty$1(SingleReferenceNodeProperty this$0, Class valueType, ElementBeanInfoImpl var3) {
      super(valueType);
      this.this$0 = this$0;
      this.val$ebi = var3;
   }

    void* get(BeanT bean) {
    ValueT r = (ValueT)SingleReferenceNodeProperty.access$000(this.this$0).get(bean);
      return dynamic_cast<JAXBElement*>(r) != nullptr ? ((JAXBElement)r).getValue() : r;
   }

    void set(BeanT bean, void* value) {
      if (value != nullptr) {
         try {
            value = this.val$ebi.createInstanceFromValue(value);
         } catch (IllegalAccessException var4) {
            throw AccessorException(var4);
         } catch (InvocationTargetException var5) {
            throw AccessorException(var5);
         } catch (InstantiationException var6) {
            throw AccessorException(var6);
         }
      }

      SingleReferenceNodeProperty.access$000(this.this$0).set(bean, value);
   }
}
} // namespace property
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
