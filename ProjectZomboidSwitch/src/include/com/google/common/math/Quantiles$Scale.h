#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/math/Quantiles/ScaleAndIndex.h"
#include "com/google/common/math/Quantiles/ScaleAndIndexes.h"
#include "com/google/common/primitives/Ints.h"

namespace com {
namespace google {
namespace common {
namespace math {


class Quantiles {
public:
    const int scale;

   private Quantiles$Scale(int scale) {
      Preconditions.checkArgument(scale > 0, "Quantile scale must be positive");
      this.scale = scale;
   }

    ScaleAndIndex index(int index) {
      return std::make_shared<ScaleAndIndex>(this.scale, index, nullptr);
   }

    ScaleAndIndexes indexes(int... indexes) {
      return std::make_shared<ScaleAndIndexes>(this.scale, (int[])indexes.clone(), nullptr);
   }

    ScaleAndIndexes indexes(Collection<int> indexes) {
      return std::make_shared<ScaleAndIndexes>(this.scale, Ints.toArray(indexes), nullptr);
   }
}
} // namespace math
} // namespace common
} // namespace google
} // namespace com
