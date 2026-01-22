#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/escape/Escaper.h"

namespace com {
namespace google {
namespace common {
namespace net {


class UrlEscapers {
public:
    static const std::string URL_FORM_PARAMETER_OTHER_SAFE_CHARS = "-_.*";
    static const std::string URL_PATH_OTHER_SAFE_CHARS_LACKING_PLUS = "-._~!$'()*,;
    static const Escaper URL_FORM_PARAMETER_ESCAPER = std::make_shared<PercentEscaper>("-_.*", true);
    static const Escaper URL_PATH_SEGMENT_ESCAPER = std::make_shared<PercentEscaper>("-._~!$'()*,;
    static const Escaper URL_FRAGMENT_ESCAPER = std::make_shared<PercentEscaper>("-._~!$'()*,;

    private UrlEscapers() {
   }

    static Escaper urlFormParameterEscaper() {
    return URL_FORM_PARAMETER_ESCAPER;
   }

    static Escaper urlPathSegmentEscaper() {
    return URL_PATH_SEGMENT_ESCAPER;
   }

    static Escaper urlFragmentEscaper() {
    return URL_FRAGMENT_ESCAPER;
   }
}
} // namespace net
} // namespace common
} // namespace google
} // namespace com
