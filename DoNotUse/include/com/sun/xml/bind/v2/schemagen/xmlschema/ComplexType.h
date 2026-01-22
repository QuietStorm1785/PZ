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


class ComplexType {
public:
    virtual ~ComplexType() = default;
    ComplexType _final(std::string[] var1);

    ComplexType _final(const std::string& var1);

    ComplexType block(std::string[] var1);

    ComplexType block(const std::string& var1);

    ComplexType _abstract(bool var1);

    ComplexType name(const std::string& var1);
}
} // namespace xmlschema
} // namespace schemagen
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
