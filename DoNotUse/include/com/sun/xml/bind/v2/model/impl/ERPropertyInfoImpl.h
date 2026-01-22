#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/runtime/IllegalAnnotationException.h"
#include "javax/xml/bind/annotation/XmlElementWrapper.h"
#include "javax/xml/namespace/QName.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class ERPropertyInfoImpl {
public:
    const QName xmlName;
    const bool wrapperNillable;
    const bool wrapperRequired;

    public ERPropertyInfoImpl(MethodT> classInfo, MethodT> propertySeed) {
      super(classInfo, propertySeed);
    XmlElementWrapper e = (XmlElementWrapper)this.seed.readAnnotation(XmlElementWrapper.class);
    bool nil = false;
    bool required = false;
      if (!this.isCollection()) {
         this.xmlName = nullptr;
         if (e != nullptr) {
            classInfo.builder
               .reportError(
                  std::make_shared<IllegalAnnotationException>(
                     Messages.XML_ELEMENT_WRAPPER_ON_NON_COLLECTION
                        .format(new Object[]{this.nav().getClassName(this.parent.getClazz()) + '.' + this.seed.getName()}),
                     e
                  )
               );
         }
      } else if (e != nullptr) {
         this.xmlName = this.calcXmlName(e);
         nil = e.nillable();
         required = e.required();
      } else {
         this.xmlName = nullptr;
      }

      this.wrapperNillable = nil;
      this.wrapperRequired = required;
   }

    QName getXmlName() {
      return this.xmlName;
   }

    bool isCollectionNillable() {
      return this.wrapperNillable;
   }

    bool isCollectionRequired() {
      return this.wrapperRequired;
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
