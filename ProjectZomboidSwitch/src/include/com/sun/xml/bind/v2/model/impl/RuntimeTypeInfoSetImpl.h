#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/annotation/AnnotationReader.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeNonElement.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimeTypeInfoSet.h"
#include "javax/xml/namespace/QName.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class RuntimeTypeInfoSetImpl : public TypeInfoSetImpl {
public:
    public RuntimeTypeInfoSetImpl(Method> reader) {
      super(Utils.REFLECTION_NAVIGATOR, reader, RuntimeBuiltinLeafInfoImpl.LEAVES);
   }

    RuntimeNonElement createAnyType() {
      return RuntimeAnyTypeImpl.theInstance;
   }

    RuntimeNonElement getTypeInfo(Type type) {
      return (RuntimeNonElement)super.getTypeInfo(type);
   }

    RuntimeNonElement getAnyTypeInfo() {
      return (RuntimeNonElement)super.getAnyTypeInfo();
   }

    RuntimeNonElement getClassInfo(Class clazz) {
      return (RuntimeNonElement)super.getClassInfo(clazz);
   }

   public Map<Class, RuntimeClassInfoImpl> beans() {
      return super.beans();
   }

   public Map<Type, RuntimeBuiltinLeafInfoImpl<?>> builtins() {
      return super.builtins();
   }

   public Map<Class, RuntimeEnumLeafInfoImpl<?, ?>> enums() {
      return super.enums();
   }

   public Map<Class, RuntimeArrayInfoImpl> arrays() {
      return super.arrays();
   }

    RuntimeElementInfoImpl getElementInfo(Class scope, QName name) {
      return (RuntimeElementInfoImpl)super.getElementInfo(scope, name);
   }

   public Map<QName, RuntimeElementInfoImpl> getElementMappings(Class scope) {
      return super.getElementMappings(scope);
   }

   public Iterable<RuntimeElementInfoImpl> getAllElements() {
      return super.getAllElements();
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
