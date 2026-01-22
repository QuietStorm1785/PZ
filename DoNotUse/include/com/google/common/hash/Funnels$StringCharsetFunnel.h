#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/hash/Funnels/StringCharsetFunnel/SerializedForm.h"
#include "javax/annotation/Nullable.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace hash {


class Funnels {
public:
    const Charset charset;

   Funnels$StringCharsetFunnel(Charset charset) {
      this.charset = (Charset)Preconditions.checkNotNull(charset);
   }

    void funnel(CharSequence from, PrimitiveSink into) {
      into.putString(from, this.charset);
   }

    std::string toString() {
      return "Funnels.stringFunnel(" + this.charset.name() + ")";
   }

    bool equals(@Nullable Object) {
      if (dynamic_cast<Funnels*>(o) != nullptr$StringCharsetFunnel) {
         Funnels$StringCharsetFunnel funnel = (Funnels$StringCharsetFunnel)o;
         return this.charset == funnel.charset);
      } else {
    return false;
      }
   }

    int hashCode() {
      return Funnels$StringCharsetFunnel.class.hashCode() ^ this.charset.hashCode();
   }

    void* writeReplace() {
      return std::make_shared<SerializedForm>(this.charset);
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
