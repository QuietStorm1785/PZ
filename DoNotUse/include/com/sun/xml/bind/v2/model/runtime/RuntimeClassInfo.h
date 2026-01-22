#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/core/ClassInfo.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Accessor.h"
#include "javax/xml/namespace/QName.h"
#include "org/xml/sax/Locator.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace runtime {


class RuntimeClassInfo {
public:
    virtual ~RuntimeClassInfo() = default;
    RuntimeClassInfo getBaseClass();

   List<? : public RuntimePropertyInfo> getProperties();

    RuntimePropertyInfo getProperty(const std::string& var1);

    Method getFactoryMethod();

   <BeanT> Accessor<BeanT, Map<QName, std::string>> getAttributeWildcard();

   <BeanT> Accessor<BeanT, Locator> getLocatorField();
}
} // namespace runtime
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
