#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/annotation/Locatable.h"
#include "com/sun/xml/bind/v2/model/core/ArrayInfo.h"
#include "com/sun/xml/bind/v2/model/core/NonElement.h"
#include "com/sun/xml/bind/v2/model/util/ArrayInfoUtil.h"
#include "com/sun/xml/bind/v2/runtime/IllegalAnnotationException.h"
#include "com/sun/xml/bind/v2/runtime/Location.h"
#include "javax/xml/namespace/QName.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class ArrayInfoImpl {
public:
   : public TypeInfoImpl<TypeT, ClassDeclT, FieldT, MethodT>
   , public ArrayInfo<TypeT, ClassDeclT>,
   Location {
   private const NonElement<TypeT, ClassDeclT> itemType;
    const QName typeName;
    const TypeT arrayType;

    public ArrayInfoImpl(MethodT> builder, Locatable upstream, TypeT arrayType) {
      super(builder, upstream);
      this.arrayType = arrayType;
    TypeT componentType = (TypeT)this.nav().getComponentType(arrayType);
      this.itemType = builder.getTypeInfo(componentType, this);
    QName n = this.itemType.getTypeName();
      if (n == nullptr) {
         builder.reportError(std::make_shared<IllegalAnnotationException>(Messages.ANONYMOUS_ARRAY_ITEM.format(new Object[]{this.nav().getTypeName(componentType)}), this));
         n = std::make_shared<QName>("#dummy");
      }

      this.typeName = ArrayInfoUtil.calcArrayTypeName(n);
   }

   public NonElement<TypeT, ClassDeclT> getItemType() {
      return this.itemType;
   }

    QName getTypeName() {
      return this.typeName;
   }

    bool isSimpleType() {
    return false;
   }

    TypeT getType() {
      return this.arrayType;
   }

   /** @deprecated */
    bool canBeReferencedByIDREF() {
    return false;
   }

    Location getLocation() {
    return this;
   }

    std::string toString() {
      return this.nav().getTypeName(this.arrayType);
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
