#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/schemagen/xmlschema/Schema.h"
#include "javax/xml/bind/annotation/XmlNsForm.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace schemagen {


enum class Form {
   Form$2(XmlNsForm xnf, boolean effectivelyQualified) {
   }

    void declare(const std::string& attName, Schema schema) {
      schema._attribute(attName, "unqualified");
   }
}
} // namespace schemagen
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
