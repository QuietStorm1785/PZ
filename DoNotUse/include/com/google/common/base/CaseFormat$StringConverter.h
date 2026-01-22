#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/annotation/Nullable.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace base {


class CaseFormat {
public:
    const CaseFormat sourceFormat;
    const CaseFormat targetFormat;
    static const long serialVersionUID = 0L;

   CaseFormat$StringConverter(CaseFormat sourceFormat, CaseFormat targetFormat) {
      this.sourceFormat = (CaseFormat)Preconditions.checkNotNull(sourceFormat);
      this.targetFormat = (CaseFormat)Preconditions.checkNotNull(targetFormat);
   }

    std::string doForward(const std::string& s) {
      return this.sourceFormat.to(this.targetFormat, s);
   }

    std::string doBackward(const std::string& s) {
      return this.targetFormat.to(this.sourceFormat, s);
   }

    bool equals(@Nullable Object) {
      if (!(dynamic_cast<CaseFormat*>(object) != nullptr$StringConverter)) {
    return false;
      } else {
         CaseFormat$StringConverter that = (CaseFormat$StringConverter)object;
         return this.sourceFormat == that.sourceFormat) && this.targetFormat == that.targetFormat);
      }
   }

    int hashCode() {
      return this.sourceFormat.hashCode() ^ this.targetFormat.hashCode();
   }

    std::string toString() {
      return this.sourceFormat + ".converterTo(" + this.targetFormat + ")";
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
