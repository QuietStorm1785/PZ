#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {
namespace unmarshaller {

class StAXConnector {
public:
   private StAXConnector$TagNameImpl(StAXConnector var1) {
      this.this$0 = var1;
   }

    std::string getQname() {
      return this.this$0.getCurrentQName();
   }
}
} // namespace unmarshaller
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
