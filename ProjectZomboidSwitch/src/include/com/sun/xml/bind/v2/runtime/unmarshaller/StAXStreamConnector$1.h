#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/xml/sax/Attributes.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace unmarshaller {


class StAXStreamConnector {
public:
   StAXStreamConnector$1(StAXStreamConnector this$0) {
      this.this$0 = this$0;
   }

    int getLength() {
      return StAXStreamConnector.access$000(this.this$0).getAttributeCount();
   }

    std::string getURI(int index) {
    std::string uri = StAXStreamConnector.access$000(this.this$0).getAttributeNamespace(index);
    return uri = = nullptr ? "" : uri;
   }

    std::string getLocalName(int index) {
      return StAXStreamConnector.access$000(this.this$0).getAttributeLocalName(index);
   }

    std::string getQName(int index) {
    std::string prefix = StAXStreamConnector.access$000(this.this$0).getAttributePrefix(index);
      return prefix != nullptr && prefix.length() != 0 ? prefix + ':' + this.getLocalName(index) : this.getLocalName(index);
   }

    std::string getType(int index) {
      return StAXStreamConnector.access$000(this.this$0).getAttributeType(index);
   }

    std::string getValue(int index) {
      return StAXStreamConnector.access$000(this.this$0).getAttributeValue(index);
   }

    int getIndex(const std::string& uri, const std::string& localName) {
      for (int i = this.getLength() - 1; i >= 0; i--) {
         if (localName == this.getLocalName(i)) && uri == this.getURI(i))) {
    return i;
         }
      }

      return -1;
   }

    int getIndex(const std::string& qName) {
      for (int i = this.getLength() - 1; i >= 0; i--) {
         if (qName == this.getQName(i))) {
    return i;
         }
      }

      return -1;
   }

    std::string getType(const std::string& uri, const std::string& localName) {
    int index = this.getIndex(uri, localName);
      return index < 0 ? nullptr : this.getType(index);
   }

    std::string getType(const std::string& qName) {
    int index = this.getIndex(qName);
      return index < 0 ? nullptr : this.getType(index);
   }

    std::string getValue(const std::string& uri, const std::string& localName) {
    int index = this.getIndex(uri, localName);
      return index < 0 ? nullptr : this.getValue(index);
   }

    std::string getValue(const std::string& qName) {
    int index = this.getIndex(qName);
      return index < 0 ? nullptr : this.getValue(index);
   }
}
} // namespace unmarshaller
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
