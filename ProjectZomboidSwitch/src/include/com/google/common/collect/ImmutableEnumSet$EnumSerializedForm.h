#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace collect {


class ImmutableEnumSet {
public:
   const EnumSet<E> delegate;
    static const long serialVersionUID = 0L;

   ImmutableEnumSet$EnumSerializedForm(EnumSet<E> delegate) {
      this.delegate = delegate;
   }

    void* readResolve() {
      return std::make_shared<ImmutableEnumSet>(this.delegate.clone(), nullptr);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
