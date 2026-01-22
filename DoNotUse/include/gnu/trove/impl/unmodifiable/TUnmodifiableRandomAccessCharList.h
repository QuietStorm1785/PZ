#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/list/TCharList.h"
#include <algorithm>

namespace gnu {
namespace trove {
namespace impl {
namespace unmodifiable {


class TUnmodifiableRandomAccessCharList : public TUnmodifiableCharList {
public:
    static const long serialVersionUID = -2542308836966382001L;

    public TUnmodifiableRandomAccessCharList(TCharList list) {
      super(list);
   }

    TCharList subList(int fromIndex, int toIndex) {
      return std::make_shared<TUnmodifiableRandomAccessCharList>(this.list.subList(fromIndex, toIndex));
   }

    void* writeReplace() {
      return std::make_shared<TUnmodifiableCharList>(this.list);
   }
}
} // namespace unmodifiable
} // namespace impl
} // namespace trove
} // namespace gnu
