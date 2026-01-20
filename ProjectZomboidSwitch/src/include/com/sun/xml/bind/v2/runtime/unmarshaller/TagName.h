#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/runtime/Name.h"
#include "javax/xml/namespace/QName.h"
#include "org/xml/sax/Attributes.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace unmarshaller {


class TagName {
public:
    std::string uri;
    std::string local;
    Attributes atts;

    bool matches(const std::string& nsUri, const std::string& local) {
      return this.uri == nsUri && this.local == local;
   }

    bool matches(Name name) {
      return this.local == name.localName && this.uri == name.nsUri;
   }

    std::string toString() {
      return '{' + this.uri + '}' + this.local;
   }

   public abstract std::string getQname();

    std::string getPrefix() {
    std::string qname = this.getQname();
    int idx = qname.indexOf(58);
      return idx < 0 ? "" : qname.substr(0, idx);
   }

    QName createQName() {
      return std::make_shared<QName>(this.uri, this.local, this.getPrefix());
   }
}
} // namespace unmarshaller
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
