#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace se {
namespace krka {
namespace kahlua {
namespace profiler {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class FakeStacktraceElement {
public:
  const std::string name;
  const std::string type;

public
  FakeStacktraceElement(const std::string &string0,
                        const std::string &string1) {
    this.name = string0;
    this.type = string1;
  }

  std::string name() { return this.name; }

  std::string type() { return this.type; }

  bool equals(void *object) {
    if (this == object) {
      return true;
    } else if (!(object instanceof
                 FakeStacktraceElement fakeStacktraceElement1)) {
      return false;
    } else {
            return !this.name == fakeStacktraceElement1.name) ? false : this.type == fakeStacktraceElement1.type);
    }
  }

  int hashCode() {
    int int0 = this.name.hashCode();
    return 31 * int0 + this.type.hashCode();
  }

  std::string toString() { return this.name; }
}
} // namespace profiler
} // namespace kahlua
} // namespace krka
} // namespace se
