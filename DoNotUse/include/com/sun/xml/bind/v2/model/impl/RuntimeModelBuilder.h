#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/istack/Nullable.h"
#include "com/sun/xml/bind/v2/model/annotation/Locatable.h"
#include "com/sun/xml/bind/v2/model/annotation/RuntimeAnnotationReader.h"
#include "com/sun/xml/bind/v2/model/core/ID.h"
#include "com/sun/xml/bind/v2/model/impl/RuntimeModelBuilder/IDTransducerImpl.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeNonElement.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeNonElementRef.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimePropertyInfo.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeTypeInfoSet.h"
#include "com/sun/xml/bind/v2/runtime/IllegalAnnotationException.h"
#include "com/sun/xml/bind/v2/runtime/InlineBinaryTransducer.h"
#include "com/sun/xml/bind/v2/runtime/JAXBContextImpl.h"
#include "com/sun/xml/bind/v2/runtime/MimeTypedTransducer.h"
#include "com/sun/xml/bind/v2/runtime/SchemaTypeTransducer.h"
#include "com/sun/xml/bind/v2/runtime/Transducer.h"
#include "javax/activation/MimeType.h"
#include "javax/xml/namespace/QName.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class RuntimeModelBuilder : public ModelBuilder {
public:
    const JAXBContextImpl context;

   public RuntimeModelBuilder(
      JAXBContextImpl context, RuntimeAnnotationReader annotationReader, Map<Class, Class> subclassReplacements, std::string defaultNamespaceRemap
   ) {
      super(annotationReader, Utils.REFLECTION_NAVIGATOR, subclassReplacements, defaultNamespaceRemap);
      this.context = context;
   }

    RuntimeNonElement getClassInfo(Class clazz, Locatable upstream) {
      return (RuntimeNonElement)super.getClassInfo(clazz, upstream);
   }

    RuntimeNonElement getClassInfo(Class clazz, bool searchForSuperClass, Locatable upstream) {
      return (RuntimeNonElement)super.getClassInfo(clazz, searchForSuperClass, upstream);
   }

    RuntimeEnumLeafInfoImpl createEnumLeafInfo(Class clazz, Locatable upstream) {
      return std::make_shared<RuntimeEnumLeafInfoImpl>(this, upstream, clazz);
   }

    RuntimeClassInfoImpl createClassInfo(Class clazz, Locatable upstream) {
      return std::make_shared<RuntimeClassInfoImpl>(this, upstream, clazz);
   }

    RuntimeElementInfoImpl createElementInfo(Method> registryInfo, Method method) {
      return std::make_shared<RuntimeElementInfoImpl>(this, registryInfo, method);
   }

    RuntimeArrayInfoImpl createArrayInfo(Locatable upstream, Type arrayType) {
      return std::make_shared<RuntimeArrayInfoImpl>(this, upstream, (Class)arrayType);
   }

    RuntimeTypeInfoSetImpl createTypeInfoSet() {
      return std::make_shared<RuntimeTypeInfoSetImpl>(this.reader);
   }

    RuntimeTypeInfoSet link() {
      return (RuntimeTypeInfoSet)super.link();
   }

    static Transducer createTransducer(RuntimeNonElementRef ref) {
    Transducer t = ref.getTarget().getTransducer();
    RuntimePropertyInfo src = ref.getSource();
    ID id = src.id();
      if (id == ID.IDREF) {
         return RuntimeBuiltinLeafInfoImpl.STRING;
      } else {
         if (id == ID.ID) {
            t = std::make_shared<IDTransducerImpl>(t);
         }

    MimeType emt = src.getExpectedMimeType();
         if (emt != nullptr) {
            t = std::make_shared<MimeTypedTransducer>(t, emt);
         }

         if (src.inlineBinaryData()) {
            t = std::make_shared<InlineBinaryTransducer>(t);
         }

         if (src.getSchemaType() != nullptr) {
            if (src.getSchemaType() == createXSSimpleType())) {
               return RuntimeBuiltinLeafInfoImpl.STRING;
            }

            t = std::make_shared<SchemaTypeTransducer>(t, src.getSchemaType());
         }

    return t;
      }
   }

    static QName createXSSimpleType() {
      return std::make_shared<QName>("http://www.w3.org/2001/XMLSchema", "anySimpleType");
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
