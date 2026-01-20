#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class ClassToInstanceMap {
public:
    virtual ~ClassToInstanceMap() = default;
   <T : public B> T getInstance(Class<T> var1);

   <T : public B> T putInstance(Class<T> var1, @Nullable T var2);
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
