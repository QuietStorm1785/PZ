#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/core/ElementInfo.h"
#include "javax/xml/bind/JAXBElement.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace runtime {


class RuntimeElementInfo {
public:
    virtual ~RuntimeElementInfo() = default;
    RuntimeClassInfo getScope();

    RuntimeElementPropertyInfo getProperty();

   Class<? : public JAXBElement> getType();

    RuntimeNonElement getContentType();
}
} // namespace runtime
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
