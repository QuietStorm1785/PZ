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

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace schemagen {
namespace xmlschema {


class Schema {
public:
    virtual ~Schema() = default;
    Annotation annotation();

    Import _import();

    Schema targetNamespace(const std::string& var1);

    Schema lang(const std::string& var1);

    Schema id(const std::string& var1);

    Schema elementFormDefault(const std::string& var1);

    Schema attributeFormDefault(const std::string& var1);

    Schema blockDefault(std::string[] var1);

    Schema blockDefault(const std::string& var1);

    Schema finalDefault(std::string[] var1);

    Schema finalDefault(const std::string& var1);

    Schema version(const std::string& var1);
}
} // namespace xmlschema
} // namespace schemagen
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
