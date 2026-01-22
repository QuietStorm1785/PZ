#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class EmptyImmutableSetMultimap : public ImmutableSetMultimap {
public:
    static const EmptyImmutableSetMultimap INSTANCE = std::make_shared<EmptyImmutableSetMultimap>();
    static const long serialVersionUID = 0L;

    private EmptyImmutableSetMultimap() {
      super(ImmutableMap.of(), 0, nullptr);
   }

    void* readResolve() {
    return INSTANCE;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
