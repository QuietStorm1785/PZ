#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Function.h"
#include "com/google/common/collect/ImmutableMultiset.h"

namespace com {
namespace google {
namespace common {
namespace net {


class MediaType {
public:
   MediaType$1(MediaType var1) {
      this.this$0 = var1;
   }

   public ImmutableMultiset<std::string> apply(Collection<std::string> input) {
      return ImmutableMultiset.copyOf(input);
   }
}
} // namespace net
} // namespace common
} // namespace google
} // namespace com
