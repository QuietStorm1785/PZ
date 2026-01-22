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
namespace episode {


class Bindings {
public:
    virtual ~Bindings() = default;
    Bindings bindings();

    Klass klass();

    Klass typesafeEnumClass();

    SchemaBindings schemaBindings();

    void scd(const std::string& var1);

    void version(const std::string& var1);
}
} // namespace episode
} // namespace schemagen
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
