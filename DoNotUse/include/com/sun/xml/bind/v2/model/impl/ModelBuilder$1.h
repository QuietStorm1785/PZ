#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/core/ErrorHandler.h"
#include "com/sun/xml/bind/v2/runtime/IllegalAnnotationException.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class ModelBuilder {
public:
   ModelBuilder$1(ModelBuilder this$0) {
      this.this$0 = this$0;
   }

    void error(IllegalAnnotationException e) {
      this.this$0.reportError(e);
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
