#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/CharMatcher/RangesMatcher.h"

namespace com {
namespace google {
namespace common {
namespace base {


class CharMatcher {
public:
   static const CharMatcher$SingleWidth INSTANCE = new CharMatcher$SingleWidth();

   private CharMatcher$SingleWidth() {
      super("CharMatcher.singleWidth()", "\u0000־א׳\u0600ݐ\u0e00Ḁ℀ﭐﹰ｡".toCharArray(), "ӹ־ת״ۿݿ\u0e7f₯℺﷿\ufeffￜ".toCharArray());
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
