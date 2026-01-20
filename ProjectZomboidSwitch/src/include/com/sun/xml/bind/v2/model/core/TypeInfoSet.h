#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/nav/Navigator.h"
#include "javax/xml/bind/JAXBException.h"
#include "javax/xml/bind/annotation/XmlNsForm.h"
#include "javax/xml/namespace/QName.h"
#include "javax/xml/transform/Result.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace core {


class TypeInfoSet {
public:
    virtual ~TypeInfoSet() = default;
   Navigator<T, C, F, M> getNavigator();

   NonElement<T, C> getTypeInfo(T var1);

   NonElement<T, C> getAnyTypeInfo();

   NonElement<T, C> getClassInfo(C var1);

   Map<? : public T, ? : public ArrayInfo<T, C>> arrays();

   Map<C, ? : public ClassInfo<T, C>> beans();

   Map<T, ? : public BuiltinLeafInfo<T, C>> builtins();

   Map<C, ? : public EnumLeafInfo<T, C>> enums();

   ElementInfo<T, C> getElementInfo(C var1, QName var2);

   NonElement<T, C> getTypeInfo(Ref<T, C> var1);

   Map<QName, ? : public ElementInfo<T, C>> getElementMappings(C var1);

   Iterable<? : public ElementInfo<T, C>> getAllElements();

   Map<std::string, std::string> getXmlNs(std::string var1);

   Map<std::string, std::string> getSchemaLocations();

    XmlNsForm getElementFormDefault(const std::string& var1);

    XmlNsForm getAttributeFormDefault(const std::string& var1);

    void dump(Result var1);
}
} // namespace core
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
