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
namespace vm {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class UpValue {
public:
  Coroutine coroutine;
  const int index;
  void *value;

public
  UpValue(Coroutine arg0, int arg1) {
    this.coroutine = arg0;
    this.index = arg1;
  }

  int getIndex() { return this.index; }

  void *getValue() {
    return this.coroutine == nullptr ? this.value
                                     : this.coroutine.objectStack[this.index];
  }

  void setValue(void *arg0) {
    if (this.coroutine == nullptr) {
      this.value = arg0;
    } else {
      this.coroutine.objectStack[this.index] = arg0;
    }
  }

  void close() {
    this.value = this.coroutine.objectStack[this.index];
    this.coroutine = nullptr;
  }
}
} // namespace vm
} // namespace kahlua
} // namespace krka
} // namespace se
