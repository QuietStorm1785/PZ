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


class NoFixedFacet {
public:
    virtual ~NoFixedFacet() = default;
    NoFixedFacet value(const std::string& var1);
}
} // namespace xmlschema
} // namespace schemagen
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
