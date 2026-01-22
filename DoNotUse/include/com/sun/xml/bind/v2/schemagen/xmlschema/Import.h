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


class Import {
public:
    virtual ~Import() = default;
    Import namespace(const std::string& var1);

    Import schemaLocation(const std::string& var1);
}
} // namespace xmlschema
} // namespace schemagen
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
