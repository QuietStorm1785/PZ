#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/core/BuiltinLeafInfo.h"
#include "com/sun/xml/bind/v2/model/core/Element.h"
#include "com/sun/xml/bind/v2/model/nav/Navigator.h"
#include "javax/xml/namespace/QName.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class BuiltinLeafInfoImpl {
public:
   private const QName[] typeNames;

    protected BuiltinLeafInfoImpl(TypeT type, QName... typeNames) {
      super(type, typeNames.length > 0 ? typeNames[0] : nullptr);
      this.typeNames = typeNames;
   }

   public const QName[] getTypeNames() {
      return this.typeNames;
   }

   /** @deprecated */
    bool isElement() {
    return false;
   }

   /** @deprecated */
    QName getElementName() {
    return nullptr;
   }

   /** @deprecated */
   public const Element<TypeT, ClassDeclT> asElement() {
    return nullptr;
   }

   public static <TypeT, ClassDeclT> Map<TypeT, BuiltinLeafInfoImpl<TypeT, ClassDeclT>> createLeaves(Navigator<TypeT, ClassDeclT, ?, ?> nav) {
      Map<TypeT, BuiltinLeafInfoImpl<TypeT, ClassDeclT>> leaves = std::make_unique<std::unordered_map<>>();

      for (RuntimeBuiltinLeafInfoImpl<?> leaf : RuntimeBuiltinLeafInfoImpl.builtinBeanInfos) {
    TypeT t = (TypeT)nav.ref(leaf.getClazz());
         leaves.put(t, new BuiltinLeafInfoImpl<>(t, leaf.getTypeNames()));
      }

    return leaves;
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
