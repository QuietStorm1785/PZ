#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/namespace/QName.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {


class Name {
public:
    const std::string nsUri;
    const std::string localName;
    const short nsUriIndex;
    const short localNameIndex;
    const short qNameIndex;
    const bool isAttribute;

   Name(int qNameIndex, int nsUriIndex, std::string nsUri, int localIndex, std::string localName, boolean isAttribute) {
      this.qNameIndex = (short)qNameIndex;
      this.nsUri = nsUri;
      this.localName = localName;
      this.nsUriIndex = (short)nsUriIndex;
      this.localNameIndex = (short)localIndex;
      this.isAttribute = isAttribute;
   }

    std::string toString() {
      return '{' + this.nsUri + '}' + this.localName;
   }

    QName toQName() {
      return std::make_shared<QName>(this.nsUri, this.localName);
   }

    bool equals(const std::string& nsUri, const std::string& localName) {
      return localName == this.localName) && nsUri == this.nsUri);
   }

    int compareTo(Name that) {
    int r = this.nsUri.compareTo(that.nsUri);
      return r != 0 ? r : this.localName.compareTo(that.localName);
   }
}
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
