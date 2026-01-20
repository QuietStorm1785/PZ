#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/list/TLongList.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableRandomAccessLongList : public TUnmodifiableLongList {
public:
    static const long serialVersionUID = -2542308836966382001L;

    public TUnmodifiableRandomAccessLongList(TLongList list) {
      super(list);
   }

    TLongList subList(int fromIndex, int toIndex) {
      return std::make_shared<TUnmodifiableRandomAccessLongList>(this.list.subList(fromIndex, toIndex));
   }

    void* writeReplace() {
      return std::make_shared<TUnmodifiableLongList>(this.list);
   }
}
} // namespace unmodifiable
} // namespace impl
} // namespace trove
} // namespace gnu
