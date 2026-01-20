#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/core/NonElement.h"
#include "com/sun/xml/bind/v2/model/core/PropertyInfo.h"
#include "com/sun/xml/bind/v2/model/core/TypeRef.h"
#include "javax/xml/namespace/QName.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class TypeRefImpl {
public:
    const QName elementName;
    const TypeT type;
   protected const ElementPropertyInfoImpl<TypeT, ClassDeclT, ?, ?> owner;
   private NonElement<TypeT, ClassDeclT> ref;
    const bool isNillable;
    std::string defaultValue;

    public TypeRefImpl(?> owner, QName elementName, TypeT type, bool isNillable, const std::string& defaultValue) {
      this.owner = owner;
      this.elementName = elementName;
      this.type = type;
      this.isNillable = isNillable;
      this.defaultValue = defaultValue;

      assert owner != nullptr;

      assert elementName != nullptr;

      assert type != nullptr;
   }

   public NonElement<TypeT, ClassDeclT> getTarget() {
      if (this.ref == nullptr) {
         this.calcRef();
      }

      return this.ref;
   }

    QName getTagName() {
      return this.elementName;
   }

    bool isNillable() {
      return this.isNillable;
   }

    std::string getDefaultValue() {
      return this.defaultValue;
   }

    void link() {
      this.calcRef();
   }

    void calcRef() {
      this.ref = this.owner.parent.builder.getTypeInfo(this.type, this.owner);

      assert this.ref != nullptr;
   }

   public PropertyInfo<TypeT, ClassDeclT> getSource() {
      return this.owner;
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
