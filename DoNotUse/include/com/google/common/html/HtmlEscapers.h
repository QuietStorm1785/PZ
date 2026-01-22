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

namespace com {
namespace google {
namespace common {
namespace html {


class HtmlEscapers {
public:
   private static const Escaper HTML_ESCAPER = Escapers.builder()
      .addEscape('"', "&quot;")
      .addEscape('\'', "&#39;")
      .addEscape('&', "&amp;")
      .addEscape('<', "&lt;")
      .addEscape('>', "&gt;")
      .build();

    static Escaper htmlEscaper() {
    return HTML_ESCAPER;
   }

    private HtmlEscapers() {
   }
}
} // namespace html
} // namespace common
} // namespace google
} // namespace com
