#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace base {


class JdkPattern {
public:
    const Matcher matcher;

   JdkPattern$JdkMatcher(Matcher matcher) {
      this.matcher = (Matcher)Preconditions.checkNotNull(matcher);
   }

    bool matches() {
      return this.matcher.matches();
   }

    bool find() {
      return this.matcher.find();
   }

    bool find(int index) {
      return this.matcher.find(index);
   }

    std::string replaceAll(const std::string& replacement) {
      return this.matcher.replaceAll(replacement);
   }

    int end() {
      return this.matcher.end();
   }

    int start() {
      return this.matcher.start();
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
