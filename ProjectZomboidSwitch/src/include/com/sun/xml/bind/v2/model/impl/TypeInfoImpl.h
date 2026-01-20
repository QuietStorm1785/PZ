#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/api/impl/NameConverter.h"
#include "com/sun/xml/bind/v2/model/annotation/AnnotationReader.h"
#include "com/sun/xml/bind/v2/model/annotation/Locatable.h"
#include "com/sun/xml/bind/v2/model/core/TypeInfo.h"
#include "com/sun/xml/bind/v2/model/nav/Navigator.h"
#include "javax/xml/bind/annotation/XmlRootElement.h"
#include "javax/xml/bind/annotation/XmlSchema.h"
#include "javax/xml/bind/annotation/XmlType.h"
#include "javax/xml/namespace/QName.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class TypeInfoImpl {
public:
    const Locatable upstream;
   protected const TypeInfoSetImpl<TypeT, ClassDeclT, FieldT, MethodT> owner;
   protected ModelBuilder<TypeT, ClassDeclT, FieldT, MethodT> builder;

    protected TypeInfoImpl(MethodT> builder, Locatable upstream) {
      this.builder = builder;
      this.owner = builder.typeInfoSet;
      this.upstream = upstream;
   }

    Locatable getUpstream() {
      return this.upstream;
   }

    void link() {
      this.builder = nullptr;
   }

   protected const Navigator<TypeT, ClassDeclT, FieldT, MethodT> nav() {
      return this.owner.nav;
   }

   protected const AnnotationReader<TypeT, ClassDeclT, FieldT, MethodT> reader() {
      return this.owner.reader;
   }

    QName parseElementName(ClassDeclT clazz) {
    XmlRootElement e = (XmlRootElement)this.reader().getClassAnnotation(XmlRootElement.class, clazz, this);
      if (e == nullptr) {
    return nullptr;
      } else {
    std::string local = e.name();
         if (local == "##default")) {
            local = NameConverter.standard.toVariableName(this.nav().getClassShortName(clazz));
         }

    std::string nsUri = e.namespace();
         if (nsUri == "##default")) {
    XmlSchema xs = (XmlSchema)this.reader().getPackageAnnotation(XmlSchema.class, clazz, this);
            if (xs != nullptr) {
               nsUri = xs.namespace();
            } else {
               nsUri = this.builder.defaultNsUri;
            }
         }

         return std::make_shared<QName>(nsUri.intern(), local.intern());
      }
   }

    QName parseTypeName(ClassDeclT clazz) {
      return this.parseTypeName(clazz, (XmlType)this.reader().getClassAnnotation(XmlType.class, clazz, this));
   }

    QName parseTypeName(ClassDeclT clazz, XmlType t) {
    std::string nsUri = "##default";
    std::string local = "##default";
      if (t != nullptr) {
         nsUri = t.namespace();
         local = t.name();
      }

      if (local.length() == 0) {
    return nullptr;
      } else {
         if (local == "##default")) {
            local = NameConverter.standard.toVariableName(this.nav().getClassShortName(clazz));
         }

         if (nsUri == "##default")) {
    XmlSchema xs = (XmlSchema)this.reader().getPackageAnnotation(XmlSchema.class, clazz, this);
            if (xs != nullptr) {
               nsUri = xs.namespace();
            } else {
               nsUri = this.builder.defaultNsUri;
            }
         }

         return std::make_shared<QName>(nsUri.intern(), local.intern());
      }
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
