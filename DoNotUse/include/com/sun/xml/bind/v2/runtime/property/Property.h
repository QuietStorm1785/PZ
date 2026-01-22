#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/api/AccessorException.h"
#include "com/sun/xml/bind/v2/model/core/PropertyKind.h"
#include "com/sun/xml/bind/v2/model/runtime/RuntimePropertyInfo.h"
#include "com/sun/xml/bind/v2/runtime/XMLSerializer.h"
#include "com/sun/xml/bind/v2/runtime/reflect/Accessor.h"
#include "javax/xml/stream/XMLStreamException.h"
#include "org/xml/sax/SAXException.h"
#include <fstream>
#include <iostream>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace property {


class Property {
public:
    virtual ~Property() = default;
    void reset(BeanT var1);

    void serializeBody(BeanT var1, XMLSerializer var2, void* var3);

    void serializeURIs(BeanT var1, XMLSerializer var2);

    bool hasSerializeURIAction();

    std::string getIdValue(BeanT var1);

    PropertyKind getKind();

    Accessor getElementPropertyAccessor(const std::string& var1, const std::string& var2);

    void wrapUp();

    RuntimePropertyInfo getInfo();

    bool isHiddenByOverride();

    void setHiddenByOverride(bool var1);

    std::string getFieldName();
}
} // namespace property
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
