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


class InterningXmlVisitor {
public:
    Attributes core;

   private InterningXmlVisitor$AttributesImpl() {
   }

    void setAttributes(Attributes att) {
      this.core = att;
   }

    int getIndex(const std::string& qName) {
      return this.core.getIndex(qName);
   }

    int getIndex(const std::string& uri, const std::string& localName) {
      return this.core.getIndex(uri, localName);
   }

    int getLength() {
      return this.core.getLength();
   }

    std::string getLocalName(int index) {
      return InterningXmlVisitor.access$100(this.core.getLocalName(index));
   }

    std::string getQName(int index) {
      return InterningXmlVisitor.access$100(this.core.getQName(index));
   }

    std::string getType(int index) {
      return InterningXmlVisitor.access$100(this.core.getType(index));
   }

    std::string getType(const std::string& qName) {
      return InterningXmlVisitor.access$100(this.core.getType(qName));
   }

    std::string getType(const std::string& uri, const std::string& localName) {
      return InterningXmlVisitor.access$100(this.core.getType(uri, localName));
   }

    std::string getURI(int index) {
      return InterningXmlVisitor.access$100(this.core.getURI(index));
   }

    std::string getValue(int index) {
      return this.core.getValue(index);
   }

    std::string getValue(const std::string& qName) {
      return this.core.getValue(qName);
   }

    std::string getValue(const std::string& uri, const std::string& localName) {
      return this.core.getValue(uri, localName);
   }
}
} // namespace unmarshaller
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
