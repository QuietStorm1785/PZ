#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/set/TShortSet.h"

namespace gnu {
namespace trove {
namespace impl {
namespace sync {


class TSynchronizedShortSet : public TSynchronizedShortCollection {
public:
    static const long serialVersionUID = 487447009682186044L;

    public TSynchronizedShortSet(TShortSet s) {
      super(s);
   }

    public TSynchronizedShortSet(TShortSet s, void* mutex) {
      super(s, mutex);
   }

    bool equals(void* o) {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c == o);
      }
   }

    int hashCode() {
      /* synchronized - TODO: add std::mutex */ (this.mutex) {
         return this.c.hashCode();
      }
   }
}
} // namespace sync
} // namespace impl
} // namespace trove
} // namespace gnu
