#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class ComputationException : public RuntimeException {
public:
    static const long serialVersionUID = 0L;

    public ComputationException(@Nullable Throwable) {
      super(cause);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
