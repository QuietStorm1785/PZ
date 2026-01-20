#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/annotation/Locatable.h"
#include "com/sun/xml/bind/v2/runtime/Location.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class FieldPropertySeed {
public:
    const FieldT field;
   private ClassInfoImpl<TypeT, ClassDeclT, FieldT, MethodT> parent;

   FieldPropertySeed(ClassInfoImpl<TypeT, ClassDeclT, FieldT, MethodT> classInfo, FieldT field) {
      this.parent = classInfo;
      this.field = field;
   }

   public <A : public Annotation> A readAnnotation(Class<A> a) {
      return (A)this.parent.reader().getFieldAnnotation(a, this.field, this);
   }

    bool hasAnnotation(Class<? extends) {
      return this.parent.reader().hasFieldAnnotation(annotationType, this.field);
   }

    std::string getName() {
      return this.parent.nav().getFieldName(this.field);
   }

    TypeT getRawType() {
      return (TypeT)this.parent.nav().getFieldType(this.field);
   }

    Locatable getUpstream() {
      return this.parent;
   }

    Location getLocation() {
      return this.parent.nav().getFieldLocation(this.field);
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
