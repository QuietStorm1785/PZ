#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/set/TCharSet.h"
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableCharSet : public TUnmodifiableCharCollection {
public:
    static const long serialVersionUID = -9215047833775013803L;

    public TUnmodifiableCharSet(TCharSet s) {
      super(s);
   }

    bool equals(void* o) {
    return o = = this || this.c == o);
   }

    int hashCode() {
      return this.c.hashCode();
   }
}
} // namespace unmodifiable
} // namespace impl
} // namespace trove
} // namespace gnu
