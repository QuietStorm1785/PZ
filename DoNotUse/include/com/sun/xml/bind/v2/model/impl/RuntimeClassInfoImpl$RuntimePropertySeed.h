#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/annotation/Locatable.h"
#include "com/sun/xml/bind/v2/runtime/Location.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Accessor.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class RuntimeClassInfoImpl {
public:
    const Accessor acc;
   private const PropertySeed<Type, Class, Field, Method> core;

   public RuntimeClassInfoImpl$RuntimePropertySeed(PropertySeed<Type, Class, Field, Method> core, Accessor acc) {
      this.core = core;
      this.acc = acc;
   }

    std::string getName() {
      return this.core.getName();
   }

   public <A : public Annotation> A readAnnotation(Class<A> annotationType) {
      return (A)this.core.readAnnotation(annotationType);
   }

    bool hasAnnotation(Class<? extends) {
      return this.core.hasAnnotation(annotationType);
   }

    Type getRawType() {
      return (Type)this.core.getRawType();
   }

    Location getLocation() {
      return this.core.getLocation();
   }

    Locatable getUpstream() {
      return this.core.getUpstream();
   }

    Accessor getAccessor() {
      return this.acc;
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
