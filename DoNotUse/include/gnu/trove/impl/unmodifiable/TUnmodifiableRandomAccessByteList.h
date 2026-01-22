#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/list/TByteList.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableRandomAccessByteList : public TUnmodifiableByteList {
public:
    static const long serialVersionUID = -2542308836966382001L;

    public TUnmodifiableRandomAccessByteList(TByteList list) {
      super(list);
   }

    TByteList subList(int fromIndex, int toIndex) {
      return std::make_shared<TUnmodifiableRandomAccessByteList>(this.list.subList(fromIndex, toIndex));
   }

    void* writeReplace() {
      return std::make_shared<TUnmodifiableByteList>(this.list);
   }
}
} // namespace unmodifiable
} // namespace impl
} // namespace trove
} // namespace gnu
