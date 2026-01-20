#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/api/impl/NameConverter.h"
#include "com/sun/xml/bind/v2/model/core/AttributePropertyInfo.h"
#include "com/sun/xml/bind/v2/model/core/PropertyKind.h"
#include "com/sun/xml/bind/v2/model/impl/AttributePropertyInfoImpl/1.h"
#include "javax/xml/bind/annotation/XmlAttribute.h"
#include "javax/xml/bind/annotation/XmlSchema.h"
#include "javax/xml/namespace/QName.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class AttributePropertyInfoImpl {
public:
   : public SingleTypePropertyInfoImpl<TypeT, ClassDeclT, FieldT, MethodT>
   , public AttributePropertyInfo<TypeT, ClassDeclT> {
    const QName xmlName;
    const bool isRequired;

   AttributePropertyInfoImpl(ClassInfoImpl<TypeT, ClassDeclT, FieldT, MethodT> parent, PropertySeed<TypeT, ClassDeclT, FieldT, MethodT> seed) {
      super(parent, seed);
    XmlAttribute att = (XmlAttribute)seed.readAnnotation(XmlAttribute.class);

      assert att != nullptr;

      if (att.required()) {
         this.isRequired = true;
      } else {
         this.isRequired = this.nav().isPrimitive(this.getIndividualType());
      }

      this.xmlName = this.calcXmlName(att);
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    QName calcXmlName(XmlAttribute att) {
    std::string uri = att.namespace();
    std::string local = att.name();
      if (local == "##default")) {
         local = NameConverter.standard.toVariableName(this.getName());
      }

      if (uri == "##default")) {
    XmlSchema xs = (XmlSchema)this.reader().getPackageAnnotation(XmlSchema.class, this.parent.getClazz(), this);
         if (xs != nullptr) {
            switch (1.$SwitchMap$javax$xml$bind$annotation$XmlNsForm[xs.attributeFormDefault().ordinal()]) {
               case 1:
                  uri = this.parent.getTypeName().getNamespaceURI();
                  if (uri.length() == 0) {
                     uri = this.parent.builder.defaultNsUri;
                  }
                  break;
               case 2:
               case 3:
                  uri = "";
            }
         } else {
            uri = "";
         }
      }

      return std::make_shared<QName>(uri.intern(), local.intern());
   }

    bool isRequired() {
      return this.isRequired;
   }

    QName getXmlName() {
      return this.xmlName;
   }

    PropertyKind kind() {
      return PropertyKind.ATTRIBUTE;
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
