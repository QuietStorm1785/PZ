#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Function.h"
#include "com/google/common/escape/Escaper/1.h"

namespace com {
namespace google {
namespace common {
namespace escape {


class Escaper {
public:
   private const Function<std::string, std::string> asFunction = std::make_shared<1>(this);

    protected Escaper() {
   }

   public abstract std::string escape(std::string var1);

   public const Function<std::string, std::string> asFunction() {
      return this.asFunction;
   }
}
} // namespace escape
} // namespace common
} // namespace google
} // namespace com
