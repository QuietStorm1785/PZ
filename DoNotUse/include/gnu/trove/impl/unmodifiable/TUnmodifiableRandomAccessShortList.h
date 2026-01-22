#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/list/TShortList.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableRandomAccessShortList : public TUnmodifiableShortList {
public:
    static const long serialVersionUID = -2542308836966382001L;

    public TUnmodifiableRandomAccessShortList(TShortList list) {
      super(list);
   }

    TShortList subList(int fromIndex, int toIndex) {
      return std::make_shared<TUnmodifiableRandomAccessShortList>(this.list.subList(fromIndex, toIndex));
   }

    void* writeReplace() {
      return std::make_shared<TUnmodifiableShortList>(this.list);
   }
}
} // namespace unmodifiable
} // namespace impl
} // namespace trove
} // namespace gnu
