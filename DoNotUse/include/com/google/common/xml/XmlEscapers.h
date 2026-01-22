#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/escape/Escaper.h"
#include "com/google/common/escape/Escapers.h"
#include "com/google/common/escape/Escapers/Builder.h"

namespace com {
namespace google {
namespace common {
namespace xml {


class XmlEscapers {
public:
    static const char MIN_ASCII_CONTROL_CHAR = '\u0000';
    static const char MAX_ASCII_CONTROL_CHAR = '\u001f';
    static const Escaper XML_ESCAPER;
    static const Escaper XML_CONTENT_ESCAPER;
    static const Escaper XML_ATTRIBUTE_ESCAPER;

    private XmlEscapers() {
   }

    static Escaper xmlContentEscaper() {
    return XML_CONTENT_ESCAPER;
   }

    static Escaper xmlAttributeEscaper() {
    return XML_ATTRIBUTE_ESCAPER;
   }

   static {
    Builder builder = Escapers.builder();
      builder.setSafeRange('\u0000', '�');
      builder.setUnsafeReplacement("�");

      for (char c = 0; c <= 31; c++) {
         if (c != '\t' && c != '\n' && c != '\r') {
            builder.addEscape(c, "�");
         }
      }

      builder.addEscape('&', "&amp;");
      builder.addEscape('<', "&lt;");
      builder.addEscape('>', "&gt;");
      XML_CONTENT_ESCAPER = builder.build();
      builder.addEscape('\'', "&apos;");
      builder.addEscape('"', "&quot;");
      XML_ESCAPER = builder.build();
      builder.addEscape('\t', "&#x9;");
      builder.addEscape('\n', "&#xA;");
      builder.addEscape('\r', "&#xD;");
      XML_ATTRIBUTE_ESCAPER = builder.build();
   }
}
} // namespace xml
} // namespace common
} // namespace google
} // namespace com
