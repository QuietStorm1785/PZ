#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace base {


class Splitter {
public:
   Splitter$5(Splitter var1, CharSequence var2) {
      this.this$0 = var1;
      this.val$sequence = var2;
   }

   public Iterator<std::string> iterator() {
      return Splitter.access$000(this.this$0, this.val$sequence);
   }

    std::string toString() {
      return Joiner.on(", ").appendTo(std::make_unique<std::stringstream>().append('['), this).append(']');
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
