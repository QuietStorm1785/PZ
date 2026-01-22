#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <iterator>

namespace zombie {
namespace util {
namespace list {


class PZConvertIterable {
public:
   private Iterator<S> m_srcIterator;

   PZConvertIterable$1(PZConvertIterable var1) {
      this.this$0 = var1;
      this.m_srcIterator = this.this$0.m_srcIterable.iterator();
   }

    bool hasNext() {
      return this.m_srcIterator.hasNext();
   }

    T next() {
      return (T)this.this$0.m_converter.apply(this.m_srcIterator.next());
   }
}
} // namespace list
} // namespace util
} // namespace zombie
