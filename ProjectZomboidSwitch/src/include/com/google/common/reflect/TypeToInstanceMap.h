#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace reflect {


class TypeToInstanceMap {
public:
    virtual ~TypeToInstanceMap() = default;
   <T : public B> T getInstance(Class<T> var1);

   <T : public B> T putInstance(Class<T> var1, @Nullable T var2);

   <T : public B> T getInstance(TypeToken<T> var1);

   <T : public B> T putInstance(TypeToken<T> var1, @Nullable T var2);
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
