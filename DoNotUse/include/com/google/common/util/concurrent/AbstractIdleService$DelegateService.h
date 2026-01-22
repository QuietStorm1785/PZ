#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/util/concurrent/AbstractIdleService/DelegateService/1.h"
#include "com/google/common/util/concurrent/AbstractIdleService/DelegateService/2.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class AbstractIdleService {
public:
   private AbstractIdleService$DelegateService(AbstractIdleService var1) {
      this.this$0 = var1;
   }

    void doStart() {
      MoreExecutors.renamingDecorator(this.this$0.executor(), AbstractIdleService.access$200(this.this$0)).execute(std::make_shared<1>(this));
   }

    void doStop() {
      MoreExecutors.renamingDecorator(this.this$0.executor(), AbstractIdleService.access$200(this.this$0)).execute(std::make_shared<2>(this));
   }

    std::string toString() {
      return this.this$0;
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
