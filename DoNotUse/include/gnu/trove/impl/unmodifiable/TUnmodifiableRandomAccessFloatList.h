#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/list/TFloatList.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableRandomAccessFloatList : public TUnmodifiableFloatList {
public:
    static const long serialVersionUID = -2542308836966382001L;

    public TUnmodifiableRandomAccessFloatList(TFloatList list) {
      super(list);
   }

    TFloatList subList(int fromIndex, int toIndex) {
      return std::make_shared<TUnmodifiableRandomAccessFloatList>(this.list.subList(fromIndex, toIndex));
   }

    void* writeReplace() {
      return std::make_shared<TUnmodifiableFloatList>(this.list);
   }
}
} // namespace unmodifiable
} // namespace impl
} // namespace trove
} // namespace gnu
