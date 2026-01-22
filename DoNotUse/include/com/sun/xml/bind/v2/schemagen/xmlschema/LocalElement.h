#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/txw2/TypedXmlWriter.h"
#include "com/sun/xml/txw2/annotation/XmlAttribute.h"
#include "com/sun/xml/txw2/annotation/XmlElement.h"
#include "javax/xml/namespace/QName.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace schemagen {
namespace xmlschema {


class LocalElement {
public:
    virtual ~LocalElement() = default;
    LocalElement form(const std::string& var1);

    LocalElement name(const std::string& var1);

    LocalElement ref(QName var1);
}
} // namespace xmlschema
} // namespace schemagen
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
