#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/core/ID.h"
#include "com/sun/xml/bind/v2/model/core/PropertyKind.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeAttributePropertyInfo.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeElementPropertyInfo.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeNonElement.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimePropertyInfo.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeTypeInfo.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeValuePropertyInfo.h"
#include "com/sun/xml/bind/v2/runtime/JAXBContextImpl.h"
#include "com/sun/xml/bind/v2/runtime/property/PropertyFactory/1.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace property {


class PropertyFactory {
public:
   private static const Constructor<? : public Property>[] propImpls;

    private PropertyFactory() {
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    static Property create(JAXBContextImpl grammar, RuntimePropertyInfo info) {
    PropertyKind kind = info.kind();
      switch (1.$SwitchMap$com$sun$xml$bind$v2$model$core$PropertyKind[kind.ordinal()]) {
         case 1:
            return std::make_shared<AttributeProperty>(grammar, (RuntimeAttributePropertyInfo)info);
         case 2:
            return std::make_shared<ValueProperty>(grammar, (RuntimeValuePropertyInfo)info);
         case 3:
            if (((RuntimeElementPropertyInfo)info).isValueList()) {
               return std::make_shared<ListElementProperty>(grammar, (RuntimeElementPropertyInfo)info);
            }
         case 4:
         case 5:
            break;
         default:
    assert false;
      }

    bool isCollection = info.isCollection();
    bool isLeaf = isLeaf(info);
      Constructor<? : public Property> c = propImpls[(isLeaf ? 0 : 6) + (isCollection ? 3 : 0) + kind.propertyIndex];

      try {
         return c.newInstance(grammar, info);
      } catch (InstantiationException var8) {
         throw InstantiationError(var8.getMessage());
      } catch (IllegalAccessException var9) {
         throw IllegalAccessError(var9.getMessage());
      } catch (InvocationTargetException var10) {
    std::exception t = var10.getCause();
         if (dynamic_cast<Error*>(t) != nullptr) {
            throw (Error)t;
         } else if (dynamic_cast<RuntimeException*>(t) != nullptr) {
            throw (RuntimeException)t;
         } else {
            throw AssertionError(t);
         }
      }
   }

    static bool isLeaf(RuntimePropertyInfo info) {
      Collection<? : public RuntimeTypeInfo> types = info.ref();
      if (types.size() != 1) {
    return false;
      } else {
    RuntimeTypeInfo rti = types.iterator().next();
         if (!(dynamic_cast<RuntimeNonElement*>(rti) != nullptr)) {
    return false;
         } else if (info.id() == ID.IDREF) {
    return true;
         } else {
            return ((RuntimeNonElement)rti).getTransducer() == nullptr ? false : info.getIndividualType() == rti.getType());
         }
      }
   }

   static {
      Class<? : public Property>[] implClasses = new Class[]{
         SingleElementLeafProperty.class,
         nullptr,
         nullptr,
         ArrayElementLeafProperty.class,
         nullptr,
         nullptr,
         SingleElementNodeProperty.class,
         SingleReferenceNodeProperty.class,
         SingleMapNodeProperty.class,
         ArrayElementNodeProperty.class,
         ArrayReferenceNodeProperty.class,
         nullptr
      };
      propImpls = new Constructor[implClasses.length];

      for (int i = 0; i < propImpls.length; i++) {
         if (implClasses[i] != nullptr) {
            propImpls[i] = (Constructor<? : public Property>)implClasses[i].getConstructors()[0];
         }
      }
   }
}
} // namespace property
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
