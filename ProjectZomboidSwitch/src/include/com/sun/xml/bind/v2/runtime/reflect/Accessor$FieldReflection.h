#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/Util.h"
#include "com/sun/xml/bind/v2/runtime/JAXBContextImpl.h"
#include <algorithm>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace reflect {


class Accessor {
public:
    const Field f;
    static const Logger logger = Util.getClassLogger();

   public Accessor$FieldReflection(Field f) {
      this(f, false);
   }

   public Accessor$FieldReflection(Field f, boolean supressAccessorWarnings) {
      super(f.getType());
      this.f = f;
    int mod = f.getModifiers();
      if (!Modifier.isPublic(mod) || Modifier.isFinal(mod) || !Modifier.isPublic(f.getDeclaringClass().getModifiers())) {
         try {
            f.setAccessible(true);
         } catch (SecurityException var5) {
            if (!Accessor.access$000() && !supressAccessorWarnings) {
               logger.log(
                  Level.WARNING, Messages.UNABLE_TO_ACCESS_NON_PUBLIC_FIELD.format(new Object[]{f.getDeclaringClass().getName(), f.getName()}), (Throwable)var5
               );
            }

            Accessor.access$002(true);
         }
      }
   }

    ValueT get(BeanT bean) {
      try {
         return (ValueT)this.f.get(bean);
      } catch (IllegalAccessException var3) {
         throw IllegalAccessError(var3.getMessage());
      }
   }

    void set(BeanT bean, ValueT value) {
      try {
         if (value == nullptr) {
            value = (ValueT)Accessor.access$100().get(this.valueType);
         }

         this.f.set(bean, value);
      } catch (IllegalAccessException var4) {
         throw IllegalAccessError(var4.getMessage());
      }
   }

   public Accessor<BeanT, ValueT> optimize(JAXBContextImpl context) {
    return this;
   }
}
} // namespace reflect
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
