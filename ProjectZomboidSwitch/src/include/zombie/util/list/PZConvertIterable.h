#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/list/PZConvertIterable/1.h"
#include <algorithm>
#include <iterator>

namespace zombie {
namespace util {
namespace list {


class PZConvertIterable {
public:
   private const Iterable<S> m_srcIterable;
   private const Function<S, T> m_converter;

    public PZConvertIterable(Iterable<S> var1, T> var2) {
      this.m_srcIterable = var1;
      this.m_converter = var2;
   }

   public Iterator<T> iterator() {
      return std::make_shared<1>(this);
   }
}
} // namespace list
} // namespace util
} // namespace zombie
