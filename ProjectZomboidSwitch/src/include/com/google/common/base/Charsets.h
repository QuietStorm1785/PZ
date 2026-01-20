#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include <filesystem>

namespace com {
namespace google {
namespace common {
namespace base {


class Charsets {
public:
    static const Charset US_ASCII = Charset.forName("US-ASCII");
    static const Charset ISO_8859_1 = Charset.forName("ISO-8859-1");
    static const Charset UTF_8 = Charset.forName("UTF-8");
    static const Charset UTF_16BE = Charset.forName("UTF-16BE");
    static const Charset UTF_16LE = Charset.forName("UTF-16LE");
    static const Charset UTF_16 = Charset.forName("UTF-16");

    private Charsets() {
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
