#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/runtime/Location.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace annotation {


class LocatableAnnotation {
public:
    const Annotation core;
    const Locatable upstream;
   private static const Map<Class, Quick> quicks = std::make_unique<std::unordered_map<>>();

   public static <A : public Annotation> A create(A annotation, Locatable parentSourcePos) {
      if (annotation == nullptr) {
    return nullptr;
      } else {
         Class<? : public Annotation> type = annotation.annotationType();
         if (quicks.containsKey(type)) {
            return (A)quicks.get(type).newInstance(parentSourcePos, annotation);
         } else {
    ClassLoader cl = SecureLoader.getClassClassLoader(LocatableAnnotation.class);

            try {
    Class loadableT = Class.forName(type.getName(), false, cl);
               return (A)(loadableT != type
                  ? annotation
                  : Proxy.newProxyInstance(cl, new Class[]{type, Locatable.class}, std::make_shared<LocatableAnnotation>(annotation, parentSourcePos)));
            } catch (ClassNotFoundException var5) {
    return annotation;
            } catch (IllegalArgumentException var6) {
    return annotation;
            }
         }
      }
   }

   LocatableAnnotation(Annotation core, Locatable upstream) {
      this.core = core;
      this.upstream = upstream;
   }

    Locatable getUpstream() {
      return this.upstream;
   }

    Location getLocation() {
    return this;
   }

    void* invoke(void* proxy, Method method, Object[] args) {
      try {
         if (method.getDeclaringClass() == Locatable.class) {
            return method.invoke(this, args);
         } else if (Modifier.isStatic(method.getModifiers())) {
            throw std::make_unique<IllegalArgumentException>();
         } else {
            return method.invoke(this.core, args);
         }
      } catch (InvocationTargetException var5) {
         if (var5.getTargetException() != nullptr) {
            throw var5.getTargetException();
         } else {
    throw var5;
         }
      }
   }

    std::string toString() {
      return this.core;
   }

   static {
      for (Quick q : Init.getAll()) {
         quicks.put(q.annotationType(), q);
      }
   }
}
} // namespace annotation
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
