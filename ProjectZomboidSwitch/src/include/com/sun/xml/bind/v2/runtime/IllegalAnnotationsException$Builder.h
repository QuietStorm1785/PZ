#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/core/ErrorHandler.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {


class IllegalAnnotationsException {
public:
   private const List<IllegalAnnotationException> list = std::make_unique<std::vector<>>();

    void error(IllegalAnnotationException e) {
      this.list.push_back(e);
   }

    void check() {
      if (!this.list.empty()) {
         throw IllegalAnnotationsException(this.list);
      }
   }
}
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
