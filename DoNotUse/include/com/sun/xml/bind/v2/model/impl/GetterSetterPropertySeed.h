#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/annotation/Locatable.h"
#include "com/sun/xml/bind/v2/runtime/Location.h"
#include "java/beans/Introspector.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class GetterSetterPropertySeed {
public:
    const MethodT getter;
    const MethodT setter;
   private ClassInfoImpl<TypeT, ClassDeclT, FieldT, MethodT> parent;

   GetterSetterPropertySeed(ClassInfoImpl<TypeT, ClassDeclT, FieldT, MethodT> parent, MethodT getter, MethodT setter) {
      this.parent = parent;
      this.getter = getter;
      this.setter = setter;
      if (getter == nullptr && setter == nullptr) {
         throw std::make_unique<IllegalArgumentException>();
      }
   }

    TypeT getRawType() {
      return (TypeT)(this.getter != nullptr ? this.parent.nav().getReturnType(this.getter) : this.parent.nav().getMethodParameters(this.setter)[0]);
   }

   public <A : public Annotation> A readAnnotation(Class<A> annotation) {
      return (A)this.parent.reader().getMethodAnnotation(annotation, this.getter, this.setter, this);
   }

    bool hasAnnotation(Class<? extends) {
      return this.parent.reader().hasMethodAnnotation(annotationType, this.getName(), this.getter, this.setter, this);
   }

    std::string getName() {
      return this.getter != nullptr ? this.getName(this.getter) : this.getName(this.setter);
   }

    std::string getName(MethodT m) {
    std::string seed = this.parent.nav().getMethodName(m);
    std::string lseed = seed.toLowerCase();
      if (lseed.startsWith("get") || lseed.startsWith("set")) {
    return camelize();
      } else {
         return lseed.startsWith("is") ? camelize(seed.substr(2)) : seed;
      }
   }

    static std::string camelize(const std::string& s) {
      return Introspector.decapitalize(s);
   }

    Locatable getUpstream() {
      return this.parent;
   }

    Location getLocation() {
      return this.getter != nullptr ? this.parent.nav().getMethodLocation(this.getter) : this.parent.nav().getMethodLocation(this.setter);
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
