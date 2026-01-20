#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/annotation/AnnotationReader.h"
#include "com/sun/xml/bind/v2/model/nav/Navigator.h"
#include "javax/xml/bind/annotation/adapters/XmlAdapter.h"
#include "javax/xml/bind/annotation/adapters/XmlJavaTypeAdapter.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace core {


class Adapter {
public:
    const ClassDeclT adapterType;
    const TypeT defaultType;
    const TypeT customType;

    public Adapter(XmlJavaTypeAdapter spec, ?> reader, ?> nav) {
      this((ClassDeclT)nav.asDecl(reader.getClassValue(spec, "value")), nav);
   }

    public Adapter(ClassDeclT adapterType, ?> nav) {
      this.adapterType = adapterType;
    TypeT baseClass = (TypeT)nav.getBaseClass(nav.use(adapterType), nav.asDecl(XmlAdapter.class));

      assert baseClass != nullptr;

      if (nav.isParameterizedType(baseClass)) {
         this.defaultType = (TypeT)nav.getTypeArgument(baseClass, 0);
      } else {
         this.defaultType = (TypeT)nav.ref(Object.class);
      }

      if (nav.isParameterizedType(baseClass)) {
         this.customType = (TypeT)nav.getTypeArgument(baseClass, 1);
      } else {
         this.customType = (TypeT)nav.ref(Object.class);
      }
   }
}
} // namespace core
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
