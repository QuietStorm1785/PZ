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
namespace model {
namespace annotation {

class Init {
public:
   static Quick[] getAll() {
      return new Quick[]{
    std::make_shared<XmlAttributeQuick>();
    std::make_shared<XmlElementQuick>();
    std::make_shared<XmlElementDeclQuick>();
    std::make_shared<XmlElementRefQuick>();
    std::make_shared<XmlElementRefsQuick>();
    std::make_shared<XmlEnumQuick>();
    std::make_shared<XmlRootElementQuick>();
    std::make_shared<XmlSchemaQuick>();
    std::make_shared<XmlSchemaTypeQuick>();
    std::make_shared<XmlTransientQuick>();
    std::make_shared<XmlTypeQuick>();
    std::make_shared<XmlValueQuick>();
      };
   }
}
} // namespace annotation
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
