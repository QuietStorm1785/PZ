#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/list/PZPrimitiveArrayIterable/1/1.h"
#include <iterator>

namespace zombie {
namespace util {
namespace list {


class PZPrimitiveArrayIterable {
public:
   private const float[] m_list;

   PZPrimitiveArrayIterable$1(float[] var1) {
      this.val$list = var1;
      this.m_list = this.val$list;
   }

   public Iterator<float> iterator() {
      return std::make_shared<1>(this);
   }
}
} // namespace list
} // namespace util
} // namespace zombie
