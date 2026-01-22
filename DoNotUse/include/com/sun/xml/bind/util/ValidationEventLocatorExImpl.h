#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/ValidationEventLocatorEx.h"
#include "javax/xml/bind/helpers/ValidationEventLocatorImpl.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace util {


class ValidationEventLocatorExImpl : public ValidationEventLocatorImpl {
public:
    const std::string fieldName;

    public ValidationEventLocatorExImpl(void* target, const std::string& fieldName) {
      super(target);
      this.fieldName = fieldName;
   }

    std::string getFieldName() {
      return this.fieldName;
   }

    std::string toString() {
    std::stringstream buf = new std::stringstream();
      buf.append("[url=");
      buf.append(this.getURL());
      buf.append(",line=");
      buf.append(this.getLineNumber());
      buf.append(",column=");
      buf.append(this.getColumnNumber());
      buf.append(",node=");
      buf.append(this.getNode());
      buf.append(",object=");
      buf.append(this.getObject());
      buf.append(",field=");
      buf.append(this.getFieldName());
      buf.append("]");
      return buf;
   }
}
} // namespace util
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
