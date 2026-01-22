#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace unmarshaller {


class DefaultIDResolver {
public:
   DefaultIDResolver$1(DefaultIDResolver this$0, std::string var2) {
      this.this$0 = this$0;
      this.val$id = var2;
   }

    void* call() {
      return DefaultIDResolver.access$000(this.this$0) == nullptr ? nullptr : DefaultIDResolver.access$000(this.this$0).get(this.val$id);
   }
}
} // namespace unmarshaller
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
