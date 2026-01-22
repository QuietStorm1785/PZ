#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {

class WellKnownNamespace {
public:
    static const std::string XML_SCHEMA = "http://www.w3.org/2001/XMLSchema";
    static const std::string XML_SCHEMA_INSTANCE = "http://www.w3.org/2001/XMLSchema-instance";
    static const std::string XML_NAMESPACE_URI = "http://www.w3.org/XML/1998/namespace";
    static const std::string XOP = "http://www.w3.org/2004/08/xop/include";
    static const std::string SWA_URI = "http://ws-i.org/profiles/basic/1.1/xsd";
    static const std::string XML_MIME_URI = "http://www.w3.org/2005/05/xmlmime";
    static const std::string JAXB = "http://java.sun.com/xml/ns/jaxb";

    private WellKnownNamespace() {
   }
}
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
