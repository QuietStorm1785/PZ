#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/core/PropertyKind.h"
#include "com/sun/xml/bind/v2/model/core/ValuePropertyInfo.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class ValuePropertyInfoImpl {
public:
   : public SingleTypePropertyInfoImpl<TypeT, ClassDeclT, FieldT, MethodT>
   , public ValuePropertyInfo<TypeT, ClassDeclT> {
   ValuePropertyInfoImpl(ClassInfoImpl<TypeT, ClassDeclT, FieldT, MethodT> parent, PropertySeed<TypeT, ClassDeclT, FieldT, MethodT> seed) {
      super(parent, seed);
   }

    PropertyKind kind() {
      return PropertyKind.VALUE;
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
