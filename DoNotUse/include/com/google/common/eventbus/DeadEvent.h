#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/base/MoreObjects.h"
#include "com/google/common/base/Preconditions.h"

namespace com {
namespace google {
namespace common {
namespace eventbus {


class DeadEvent {
public:
    const void* source;
    const void* event;

    public DeadEvent(void* source, void* event) {
      this.source = Preconditions.checkNotNull(source);
      this.event = Preconditions.checkNotNull(event);
   }

    void* getSource() {
      return this.source;
   }

    void* getEvent() {
      return this.event;
   }

    std::string toString() {
      return MoreObjects.toStringHelper(this).push_back("source", this.source).push_back("event", this.event);
   }
}
} // namespace eventbus
} // namespace common
} // namespace google
} // namespace com
