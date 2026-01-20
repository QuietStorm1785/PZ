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


class EmptyImmutableListMultimap : public ImmutableListMultimap {
public:
    static const EmptyImmutableListMultimap INSTANCE = std::make_shared<EmptyImmutableListMultimap>();
    static const long serialVersionUID = 0L;

    private EmptyImmutableListMultimap() {
      super(ImmutableMap.of(), 0);
   }

    void* readResolve() {
    return INSTANCE;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
