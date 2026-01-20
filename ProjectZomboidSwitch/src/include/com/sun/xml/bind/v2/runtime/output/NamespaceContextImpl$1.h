#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/marshaller/NamespacePrefixMapper.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace output {


class NamespaceContextImpl {
public:
    std::string getPreferredPrefix(const std::string& namespaceUri, const std::string& suggestion, bool requirePrefix) {
      if (namespaceUri == "http://www.w3.org/2001/XMLSchema-instance")) {
         return "xsi";
      } else if (namespaceUri == "http://www.w3.org/2001/XMLSchema")) {
         return "xs";
      } else {
         return namespaceUri == "http://www.w3.org/2005/05/xmlmime") ? "xmime" : suggestion;
      }
   }
}
} // namespace output
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
