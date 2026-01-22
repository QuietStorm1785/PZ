#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/annotation/Locatable.h"
#include "com/sun/xml/bind/v2/model/core/ClassInfo.h"
#include "com/sun/xml/bind/v2/model/core/Element.h"
#include "com/sun/xml/bind/v2/model/core/EnumLeafInfo.h"
#include "com/sun/xml/bind/v2/model/core/NonElement.h"
#include "com/sun/xml/bind/v2/model/impl/EnumLeafInfoImpl/1.h"
#include "com/sun/xml/bind/v2/runtime/Location.h"
#include "javax/xml/bind/annotation/XmlEnum.h"
#include "javax/xml/bind/annotation/XmlEnumValue.h"
#include "javax/xml/bind/annotation/XmlSchemaType.h"
#include "javax/xml/namespace/QName.h"
#include <iterator>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class EnumLeafInfoImpl {
public:
    const C clazz;
   NonElement<T, C> baseType;
    const T type;
    const QName typeName;
   private EnumConstantImpl<T, C, F, M> firstConstant;
    QName elementName;
    bool tokenStringType;

    public EnumLeafInfoImpl(M> builder, Locatable upstream, C clazz, T type) {
      super(builder, upstream);
      this.clazz = clazz;
      this.type = type;
      this.elementName = this.parseElementName(clazz);
      this.typeName = this.parseTypeName(clazz);
    XmlEnum xe = (XmlEnum)builder.reader.getClassAnnotation(XmlEnum.class, clazz, this);
      if (xe != nullptr) {
    T base = (T)builder.reader.getClassValue(xe, "value");
         this.baseType = builder.getTypeInfo(base, this);
      } else {
         this.baseType = builder.getTypeInfo(builder.nav.ref(std::string.class), this);
      }
   }

    void calcConstants() {
      EnumConstantImpl<T, C, F, M> last = nullptr;

      for (F f : this.nav().getDeclaredFields(this.clazz)) {
         if (this.nav().isSameType(this.nav().getFieldType(f), this.nav().ref(std::string.class))) {
    XmlSchemaType schemaTypeAnnotation = (XmlSchemaType)this.builder.reader.getFieldAnnotation(XmlSchemaType.class, f, this);
            if (schemaTypeAnnotation != nullptr && "token" == schemaTypeAnnotation.name())) {
               this.tokenStringType = true;
               break;
            }
         }
      }

      F[] constants = (F[])this.nav().getEnumConstants(this.clazz);

      for (int i = constants.length - 1; i >= 0; i--) {
    F constant = constants[i];
    std::string name = this.nav().getFieldName(constant);
    XmlEnumValue xev = (XmlEnumValue)this.builder.reader.getFieldAnnotation(XmlEnumValue.class, constant, this);
    std::string literal;
         if (xev == nullptr) {
            literal = name;
         } else {
            literal = xev.value();
         }

         last = this.createEnumConstant(name, literal, constant, last);
      }

      this.firstConstant = last;
   }

   protected EnumConstantImpl<T, C, F, M> createEnumConstant(std::string name, std::string literal, F constant, EnumConstantImpl<T, C, F, M> last) {
      return std::make_shared<EnumConstantImpl>(this, name, literal, last);
   }

    T getType() {
      return this.type;
   }

    bool isToken() {
      return this.tokenStringType;
   }

   /** @deprecated */
    bool canBeReferencedByIDREF() {
    return false;
   }

    QName getTypeName() {
      return this.typeName;
   }

    C getClazz() {
      return this.clazz;
   }

   public NonElement<T, C> getBaseType() {
      return this.baseType;
   }

    bool isSimpleType() {
    return true;
   }

    Location getLocation() {
      return this.nav().getClassLocation(this.clazz);
   }

   public Iterable<? : public EnumConstantImpl<T, C, F, M>> getConstants() {
      if (this.firstConstant == nullptr) {
         this.calcConstants();
      }

    return this;
   }

    void link() {
      this.getConstants();
      super.link();
   }

   /** @deprecated */
   public Element<T, C> getSubstitutionHead() {
    return nullptr;
   }

    QName getElementName() {
      return this.elementName;
   }

    bool isElement() {
      return this.elementName != nullptr;
   }

   public Element<T, C> asElement() {
      return this.isElement() ? this : nullptr;
   }

   /** @deprecated */
   public ClassInfo<T, C> getScope() {
    return nullptr;
   }

   public Iterator<EnumConstantImpl<T, C, F, M>> iterator() {
      return std::make_shared<1>(this);
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
