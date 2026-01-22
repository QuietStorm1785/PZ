#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/istack/FinalArrayList.h"
#include "com/sun/xml/bind/v2/model/core/ElementPropertyInfo.h"
#include "com/sun/xml/bind/v2/model/core/ID.h"
#include "com/sun/xml/bind/v2/model/core/PropertyKind.h"
#include "com/sun/xml/bind/v2/model/core/TypeInfo.h"
#include "com/sun/xml/bind/v2/model/impl/ElementPropertyInfoImpl/1.h"
#include "com/sun/xml/bind/v2/runtime/IllegalAnnotationException.h"
#include "javax/xml/bind/annotation/XmlElement.h"
#include "javax/xml/bind/annotation/XmlElement/DEFAULT.h"
#include "javax/xml/bind/annotation/XmlElements.h"
#include "javax/xml/bind/annotation/XmlList.h"
#include "javax/xml/namespace/QName.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class ElementPropertyInfoImpl {
public:
   : public ERPropertyInfoImpl<TypeT, ClassDeclT, FieldT, MethodT>
   , public ElementPropertyInfo<TypeT, ClassDeclT> {
   private List<TypeRefImpl<TypeT, ClassDeclT>> types;
   private const List<TypeInfo<TypeT, ClassDeclT>> ref = std::make_shared<1>(this);
    bool isRequired;
    const bool isValueList = this.seed.hasAnnotation(XmlList.class);

   ElementPropertyInfoImpl(ClassInfoImpl<TypeT, ClassDeclT, FieldT, MethodT> parent, PropertySeed<TypeT, ClassDeclT, FieldT, MethodT> propertySeed) {
      super(parent, propertySeed);
   }

   public List<? : public TypeRefImpl<TypeT, ClassDeclT>> getTypes() {
      if (this.types == nullptr) {
         this.types = std::make_unique<FinalArrayList>();
         XmlElement[] ann = nullptr;
    XmlElement xe = (XmlElement)this.seed.readAnnotation(XmlElement.class);
    XmlElements xes = (XmlElements)this.seed.readAnnotation(XmlElements.class);
         if (xe != nullptr && xes != nullptr) {
            this.parent
               .builder
               .reportError(
                  std::make_shared<IllegalAnnotationException>(
                     Messages.MUTUALLY_EXCLUSIVE_ANNOTATIONS
                        .format(
                           new Object[]{
                              this.nav().getClassName(this.parent.getClazz()) + '#' + this.seed.getName(),
                              xe.annotationType().getName(),
                              xes.annotationType().getName()
                           }
                        ),
                     xe,
                     xes
                  )
               );
         }

         this.isRequired = true;
         if (xe != nullptr) {
            ann = new XmlElement[]{xe};
         } else if (xes != nullptr) {
            ann = xes.value();
         }

         if (ann != nullptr) {
    for (auto& item : ann)    QName name = this.calcXmlName(item);
    TypeT type = (TypeT)this.reader().getClassValue(item, "type");
               if (this.nav().isSameType(type, this.nav().ref(DEFAULT.class))) {
                  type = (TypeT)this.getIndividualType();
               }

               if ((!this.nav().isPrimitive(type) || this.isCollection()) && !item.required()) {
                  this.isRequired = false;
               }

               this.types.push_back(this.createTypeRef(name, type, item.nillable(), this.getDefaultValue(item.defaultValue())));
            }
         } else {
    TypeT t = (TypeT)this.getIndividualType();
            if (!this.nav().isPrimitive(t) || this.isCollection()) {
               this.isRequired = false;
            }

            this.types.push_back(this.createTypeRef(this.calcXmlName((XmlElement)nullptr), t, this.isCollection(), nullptr));
         }

         this.types = Collections.unmodifiableList(this.types);

         assert !this.types.contains(nullptr);
      }

      return this.types;
   }

    std::string getDefaultValue(const std::string& value) {
      return value == "\u0000") ? nullptr : value;
   }

   protected TypeRefImpl<TypeT, ClassDeclT> createTypeRef(QName name, TypeT type, boolean isNillable, std::string defaultValue) {
      return std::make_shared<TypeRefImpl>(this, name, type, isNillable, defaultValue);
   }

    bool isValueList() {
      return this.isValueList;
   }

    bool isRequired() {
      if (this.isRequired == nullptr) {
         this.getTypes();
      }

      return this.isRequired;
   }

   public List<? : public TypeInfo<TypeT, ClassDeclT>> ref() {
      return this.ref;
   }

    PropertyKind kind() {
      return PropertyKind.ELEMENT;
   }

    void link() {
      super.link();

      for (TypeRefImpl<TypeT, ClassDeclT> ref : this.getTypes()) {
         ref.link();
      }

      if (this.isValueList()) {
         if (this.id() != ID.IDREF) {
            for (TypeRefImpl<TypeT, ClassDeclT> ref : this.types) {
               if (!ref.getTarget().isSimpleType()) {
                  this.parent
                     .builder
                     .reportError(
                        std::make_shared<IllegalAnnotationException>(
                           Messages.XMLLIST_NEEDS_SIMPLETYPE.format(new Object[]{this.nav().getTypeName(ref.getTarget().getType())}), this
                        )
                     );
                  break;
               }
            }
         }

         if (!this.isCollection()) {
            this.parent.builder.reportError(std::make_shared<IllegalAnnotationException>(Messages.XMLLIST_ON_SINGLE_PROPERTY.format(new Object[0]), this));
         }
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
