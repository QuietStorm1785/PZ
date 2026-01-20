#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace reflect {


enum class Types {
   Class<?> getOwnerType(Class<?> rawType) {
      return rawType.isLocalClass() ? nullptr : rawType.getEnclosingClass();
   }
}
} // namespace reflect
} // namespace common
} // namespace google
} // namespace com
