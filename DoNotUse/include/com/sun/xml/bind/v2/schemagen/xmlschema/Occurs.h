#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/txw2/TypedXmlWriter.h"
#include "com/sun/xml/txw2/annotation/XmlAttribute.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace schemagen {
namespace xmlschema {


class Occurs {
public:
    virtual ~Occurs() = default;
    Occurs minOccurs(int var1);

    Occurs maxOccurs(const std::string& var1);

    Occurs maxOccurs(int var1);
}
} // namespace xmlschema
} // namespace schemagen
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
