#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/core/TypeInfoSet.h"
#include "javax/xml/namespace/QName.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace runtime {


class RuntimeTypeInfoSet {
public:
    virtual ~RuntimeTypeInfoSet() = default;
   Map<Class, ? : public RuntimeArrayInfo> arrays();

   Map<Class, ? : public RuntimeClassInfo> beans();

   Map<Type, ? : public RuntimeBuiltinLeafInfo> builtins();

   Map<Class, ? : public RuntimeEnumLeafInfo> enums();

    RuntimeNonElement getTypeInfo(Type var1);

    RuntimeNonElement getAnyTypeInfo();

    RuntimeNonElement getClassInfo(Class var1);

    RuntimeElementInfo getElementInfo(Class var1, QName var2);

   Map<QName, ? : public RuntimeElementInfo> getElementMappings(Class var1);

   Iterable<? : public RuntimeElementInfo> getAllElements();
}
} // namespace runtime
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
