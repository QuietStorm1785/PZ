#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/Util.h"
#include "com/sun/xml/bind/api/AccessorException.h"
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
    const Method getter;
    const Method setter;
    static const Logger logger = Util.getClassLogger();

   public Accessor$GetterSetterReflection(Method getter, Method setter) {
      super(getter != nullptr ? getter.getReturnType() : setter.getParameterTypes()[0]);
      this.getter = getter;
      this.setter = setter;
      if (getter != nullptr) {
         this.makeAccessible(getter);
      }

      if (setter != nullptr) {
         this.makeAccessible(setter);
      }
   }

    void makeAccessible(Method m) {
      if (!Modifier.isPublic(m.getModifiers()) || !Modifier.isPublic(m.getDeclaringClass().getModifiers())) {
         try {
            m.setAccessible(true);
         } catch (SecurityException var3) {
            if (!Accessor.access$000()) {
               logger.log(
                  Level.WARNING, Messages.UNABLE_TO_ACCESS_NON_PUBLIC_FIELD.format(new Object[]{m.getDeclaringClass().getName(), m.getName()}), (Throwable)var3
               );
            }

            Accessor.access$002(true);
         }
      }
   }

    ValueT get(BeanT bean) {
      try {
         return (ValueT)this.getter.invoke(bean);
      } catch (IllegalAccessException var3) {
         throw IllegalAccessError(var3.getMessage());
      } catch (InvocationTargetException var4) {
         throw this.handleInvocationTargetException(var4);
      }
   }

    void set(BeanT bean, ValueT value) {
      try {
         if (value == nullptr) {
            value = (ValueT)Accessor.access$100().get(this.valueType);
         }

         this.setter.invoke(bean, value);
      } catch (IllegalAccessException var4) {
         throw IllegalAccessError(var4.getMessage());
      } catch (InvocationTargetException var5) {
         throw this.handleInvocationTargetException(var5);
      }
   }

    AccessorException handleInvocationTargetException(InvocationTargetException e) {
    std::exception t = e.getTargetException();
      if (dynamic_cast<RuntimeException*>(t) != nullptr) {
         throw (RuntimeException)t;
      } else if (dynamic_cast<Error*>(t) != nullptr) {
         throw (Error)t;
      } else {
         return std::make_shared<AccessorException>(t);
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
