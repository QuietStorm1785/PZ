#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/collect/Serialization/FieldSetter.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class ConcurrentHashMultiset {
public:
   static const FieldSetter<ConcurrentHashMultiset> COUNT_MAP_FIELD_SETTER = Serialization.getFieldSetter(ConcurrentHashMultiset.class, "countMap");

   private ConcurrentHashMultiset$FieldSettersHolder() {
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
